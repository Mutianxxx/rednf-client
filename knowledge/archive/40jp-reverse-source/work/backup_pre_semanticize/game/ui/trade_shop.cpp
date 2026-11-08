// ============================================================
// 【40JP逆向源代码工程】ui/trade_shop.cpp
// 模块: 0x54 区块 —— 摆摊/物品栏/交易/技能栏/状态窗/世界地图/PVP 结算
// 来源: work/dump_uilogin.txt  区块: 0x540000-0x550000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
// 函数数: 235
// ------------------------------------------------------------
// ★ 窗口族与资源证据：
//   CNRDPrivateStoreWindow 摆摊（+_Display/_Buy/_Sell 三个子窗口，单例登记
//   dword_9B8034，日志 "Another private shop created!"）；CNRDMakePriceWindow
//   定价；CNRDCursor 摆摊光标（Character/Common/PrivateStore/Donkey/Store.img
//   小毛驴）；CNRDItemInventoryWindow 物品栏 / CNRDAvatarInventoryWindow 时装栏
//   / CNRDSkillInventoryWindow 技能栏（ICON_DROP 拖入）/ CNRDItemTradeWindow
//   交易（Interface/ItemTradeWindowReady.img）/ CNRDStatusWindow 状态（570 行
//   构造）/ CNRDItemToolWindow 物品工具；CNRDSelectWarRoomArea+worldmap/arad.img
//   世界地图选区域；CNRDTutorial 新手引导（MOVE_ARROW 指引箭头）；CNRDPVPResult
//   PVP 结算（VICTORY_UP_LOOP/DEFEAT_DOWN_LOOP/RANK_UP/RESULT_CHARACTER）。
// ------------------------------------------------------------
// ★ 窗口系统交互约定（全文件通用，证据见各 vmt8）：
//   vmtC=打开/刷新(44BBA0=WINDOW_SHOW)、vmt8=逐帧 Update(悬停判定
//   dword_79BE34=鼠标X、CLICK_BUTTON2=按钮点击音)、vmt10=状态切换(44AB50=
//   页签切换)、vmt14=关闭清理(44BC30)、vmt1C=内容刷新、vmt18=按钮动作、
//   vmt0=构造/主虚表、vmt4=标量删除析构；422E70=字符串表取串；69A5F0/69A840=
//   控件定位/隐藏。
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】窗口基类槽与公共辅助（0x5401A0-0x5404F0）
// IRDWindow__vmt2C=页签显示(44AB50 id=12)；540420=按钮点击处理
// （CLICK_BUTTON2 + 44E8D0/44E850 对象状态切换）。
// ============================================================
// ------------------------------------------------------------
// 0x5401A0 sub_5401A0 —— PVP 结算联动（4D7080 对象查询 + 497E70），被 0x5500B0 等外部调用
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5401A0(int this, unsigned int a2)
{
  int v3; // ecx
  int v4; // ebx
  unsigned int result; // eax
  char *v6; // edi
  int v7; // eax
  int v8; // [esp-18h] [ebp-38h]
  int v9; // [esp-14h] [ebp-34h]
  int v10; // [esp+0h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-14h]
  int *v12; // [esp+10h] [ebp-10h]
  int v13; // [esp+1Ch] [ebp-4h]
  size_t v14; // [esp+28h] [ebp+8h]

  v12 = &v10;
  if ( a2 > 0x3FFFFFFF )
    sub_4D7080(this);
  v3 = *(uint32_t *)(this + 4);
  v4 = 0;
  if ( v3 != 0 )
    result = (*(uint32_t *)(this + 12) - v3) >> 2;
  else
    result = 0;
  if ( result < a2 )
  {
    v14 = 4 * a2;
    v6 = (char *)operator new(v14);
    v9 = *(uint32_t *)(this + 8);
    v8 = *(uint32_t *)(this + 4);
    Block = v6;
    v13 = 0;
    sub_497E70(v8, v9, v6);
    v7 = *(uint32_t *)(this + 4);
    if ( v7 != 0 )
    {
      v4 = (*(uint32_t *)(this + 8) - v7) >> 2;
      j__free(*(void **)(this + 4));
    }
    *(uint32_t *)(this + 12) = &v6[v14];
    *(uint32_t *)(this + 8) = &v6[4 * v4];
    *(uint32_t *)(this + 4) = v6;
    return (unsigned int)&v6[v14];
  }
  return result;
}



// ------------------------------------------------------------
// 0x540280 sub_540280 —— 窗口数据准备（53FFC0）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_540280(int *this, int *a2)
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
    return sub_53FFC0((int)this, *(this + 2), 1u, a2);
  v4 = (int *)*(this + 2);
  *v4 = *a2;
  result = (unsigned int)(v4 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x5402D0 sub_5402D0 —— 窗口数据准备中层（转发 540280）
// ------------------------------------------------------------
int /*thiscall*/ sub_5402D0(int *this, int a2)
{
  uint32_t *v3; // edx
  int result; // eax
  int v5; // esi
  int v6; // ecx

  v3 = (uint32_t *)*(this + 1);
  if ( v3 != nullptr )
    result = (*(this + 2) - (int)v3) >> 2;
  else
    result = 0;
  v5 = a2;
  v6 = 0;
  if ( result <= 0 )
  {
LABEL_7:
    sub_540280(this, &a2);
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)v5 + 68))(v5, this);
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 76))(v5, 1);
  }
  else
  {
    while ( *v3 != a2 )
    {
      ++v6;
      ++v3;
      if ( v6 >= result )
        goto LABEL_7;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x540330 sub_540330 —— 13 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_540330(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x540340 sub_540340 —— 12 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_540340(uint32_t *this, int a2, int a3)
{
  *(this + 2) = a2;
  *(this + 3) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x540360 IRDWindow__vmt2C —— IRDWindow__vmt2C 页签显示：44AB50(this+8, this+12, 12)——把 12 号子页设为当前
// ------------------------------------------------------------
int /*thiscall*/ IRDWindow__vmt2C(int this)
{
  return sub_44AB50(*(uint32_t **)(this + 8), *(uint32_t *)(this + 12), 12);
}



// ------------------------------------------------------------
// 0x540370 sub_540370 —— 窗口状态复位（+1/+5/+7 清零、+8=-1）
// ------------------------------------------------------------
int /*thiscall*/ sub_540370(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 5) = 0;
  *(this + 7) = 0;
  *(this + 8) = -1;
  return 0;
}



// ------------------------------------------------------------
// 0x540390 sub_540390 —— 子窗口释放链：依次 vf+0 销毁 *(this+1)/(+5)/(+6) 三个子窗口
// ------------------------------------------------------------
int /*thiscall*/ sub_540390(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 1) = 0;
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 5) = 0;
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  *(this + 6) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5403D0 sub_5403D0 —— 对象状态切换（44E850）——区域选择联动
// ------------------------------------------------------------
char /*thiscall*/ sub_5403D0(uint32_t *this, int a2)
{
  int v2; // eax
  int v3; // edx

  LOBYTE(v2) = a2;
  v3 = *(this + 7);
  *(this + 7) = a2;
  if ( a2 != 0 )
  {
    LOBYTE(v2) = a2 - 1;
    if ( a2 == 1 )
    {
      v2 = *(this + 1);
      *(this + 8) = -1;
      *(uint8_t *)(v2 + 16) = 1;
    }
  }
  else
  {
    *(uint8_t *)(*(this + 1) + 16) = 0;
    if ( v3 == 1 )
    {
      sub_44E850(dword_8F8528, 63);
      LOBYTE(v2) = sub_44E850(dword_8F8528, 62);
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x540420 sub_540420 —— 按钮点击处理：CLICK_BUTTON2 音 + 44E8D0/44E850 对象登记/切换（53 行）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_540420(uint32_t *this)
{
  uint8_t *result; // eax
  int v3; // edx
  int v4; // esi
  uint32_t *v5; // ecx
  int v6; // eax
  int v7; // ecx

  result = (uint8_t *)*(this + 1);
  if ( result[16] != 0 )
  {
    v3 = dword_79BE34;
    v4 = 0;
    v5 = this + 5;
    while ( *(uint8_t *)(*v5 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*v5 + 12) )
    {
      ++v4;
      ++v5;
      if ( v4 >= 1 )
        goto LABEL_9;
    }
    if ( dword_9B9454 == 0 )
    {
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      sub_44E8D0((char *)dword_8F8528, (void *)0x3E, 0, v4);
      *(this + 8) = v4;
      v3 = dword_79BE34;
    }
LABEL_9:
    result = (uint8_t *)*(this + 6);
    if ( result[17] != 0 && v3 == *((uint32_t *)result + 3) )
    {
      v6 = *(this + 7);
      v7 = *(this + 1);
      *(this + 7) = 0;
      *(uint8_t *)(v7 + 16) = 0;
      if ( v6 == 1 )
      {
        sub_44E850(dword_8F8528, 63);
        sub_44E850(dword_8F8528, 62);
      }
      return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
  }
  return result;
}



// ============================================================
// 【分区 2】世界地图与战争房间区域选择（0x5404F0-0x540830）
// 资源 worldmap/arad.img 世界地图由 0x540670 绘制；0x540810 =
// CNRDSelectWarRoomArea__vmt0 构造（转发 5404F0 列表构建）。
// ============================================================
// ------------------------------------------------------------
// 0x5404F0 sub_5404F0 —— 战争房间区域列表构建（418DD0 取控件 + 491530/491630 绘制批次）
// ------------------------------------------------------------
int /*thiscall*/ sub_5404F0(uint32_t *this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // esi
  int v5; // eax
  int v6; // esi
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // esi
  int v11; // ebx
  int v12; // eax
  int v13; // ecx
  int v14; // esi
  int result; // eax
  DWORD v16; // esi
  int v17; // edi
  int v18; // ebx
  int v19; // edi
  int v20; // eax

  v2 = sub_418DD0(0);
  if ( v2 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v2 + 152))(v2, 0, 0, dword_79C0B0);
  v3 = *(this + 6);
  if ( *(uint8_t *)(v3 + 17) != 0 )
  {
    v4 = *(uint32_t *)(v3 + 12);
    if ( dword_79BE3C == v4 || dword_79BE34 == v4 || dword_79BE38 == v4 )
    {
      sub_491530(2, 0);
      v5 = *(this + 6);
      v6 = *(uint32_t *)(v5 + 24);
      v7 = *(uint32_t *)(v5 + 20);
      v8 = sub_418DD0(22);
      if ( v8 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, v7, v6, dword_79C0B0);
      sub_491630(2);
    }
  }
  v9 = *(this + 5);
  v10 = *(uint32_t *)(v9 + 24);
  v11 = *(uint32_t *)(v9 + 20);
  v12 = sub_418DD0(42);
  if ( v12 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(v12, v11 + 37, v10 - 28, dword_79C0B0);
  v13 = *(this + 5);
  if ( *(uint8_t *)(v13 + 17) != 0
    && ((v14 = *(uint32_t *)(v13 + 12), dword_79BE3C == v14) || dword_79BE34 == v14 || dword_79BE38 == v14)
    || (result = *(this + 8)) == 0 )
  {
    v16 = GetTickCount() % 0x320 / 0x64 + 114;
    sub_491530(2, 0);
    v17 = *(this + 5);
    v18 = *(uint32_t *)(v17 + 24);
    v19 = *(uint32_t *)(v17 + 20);
    v20 = sub_418DD0(v16);
    if ( v20 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v20 + 152))(v20, v19 - 16, v18 - 48, dword_79C0B0);
    return sub_491630(2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x540670 sub_540670 —— 世界地图绘制：资源 worldmap/arad.img（426BD0 图像 + 69C780/69A5F0/69A840 定位）
// ------------------------------------------------------------
int /*thiscall*/ sub_540670(uint32_t *this)
{
  uint8_t *v2; // eax
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  uint32_t *v5; // edi
  int v6; // ebx
  uint32_t *v7; // ecx
  uint8_t *v8; // eax
  uint32_t *v9; // edi
  int v10; // ebx
  uint32_t *v11; // ecx
  int result; // eax

  v2 = operator new(0x68u);
  if ( v2 != nullptr )
    v3 = sub_426BD0(v2);
  else
    v3 = nullptr;
  *(this + 1) = v3;
  *((uint32_t *)v3 + 7) = 640;
  *((uint32_t *)v3 + 8) = 480;
  *(uint32_t *)(*(this + 1) + 68) = this;
  *(this + 2) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 76);
  *(this + 3) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 196);
  v4 = operator new(0x84u);
  v5 = v4;
  if ( v4 != nullptr )
  {
    v6 = *(this + 3);
    sub_426BD0(v4);
    *v5 = &vftbl_nengine__CNButton;
    sub_69C780(v5);
    nengine__CNButton__vmt20(v6, 43, 43, 44, -1, 0, 0);
    v7 = v5;
  }
  else
  {
    v7 = nullptr;
  }
  *(this + 5) = v7;
  sub_69A5F0(v7, 52, 231);
  *(uint32_t *)(*(this + 5) + 68) = this;
  sub_69A840(*(this + 5));
  v8 = operator new(0x84u);
  v9 = v8;
  if ( v8 != nullptr )
  {
    v10 = *(this + 2);
    sub_426BD0(v8);
    *v9 = &vftbl_nengine__CNButton;
    sub_69C780(v9);
    nengine__CNButton__vmt20(v10, 20, 21, 21, 20, 0, 0);
    v11 = v9;
  }
  else
  {
    v11 = nullptr;
  }
  *(this + 6) = v11;
  sub_69A5F0(v11, 463, 400);
  *(uint32_t *)(*(this + 6) + 68) = this;
  sub_69A840(*(this + 6));
  result = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "worldmap/arad.img");
  *(this + 8) = -1;
  *(this + 4) = result;
  return result;
}



// ------------------------------------------------------------
// 0x540810 CNRDSelectWarRoomArea__vmt0 —— CNRDSelectWarRoomArea__vmt0 构造（转发 5404F0 列表构建）
// ------------------------------------------------------------
int /*thiscall*/ CNRDSelectWarRoomArea__vmt0(int *this, int a2)
{
  int result; // eax

  result = *(this + 1);
  if ( *(uint8_t *)(result + 16) != 0 && a2 == result )
    return sub_5404F0(this);
  return result;
}



// ============================================================
// 【分区 3】堆叠数量指定控件（0x540830-0x540A10）
// IRDStackCountReceiver 接口 + CNRDStackNumberSet vmt8/vmt4；
// 数量确认见 0x5409C0（CLICK_BUTTON2 + 54A200 交易窗联动）。
// ============================================================
// ------------------------------------------------------------
// 0x540830 IRDStackCountReceiver__vmt0 —— IRDStackCountReceiver__vmt0 接口槽（11 行）
// ------------------------------------------------------------
int /*stdcall*/ IRDStackCountReceiver__vmt0(int a1)
{
  dword_9B8030 = a1;
  return a1;
}



// ------------------------------------------------------------
// 0x540840 CNRDStackNumberSet__vmt8 —— CNRDStackNumberSet__vmt8 Update 槽（14 行）
// ------------------------------------------------------------
int /*stdcall*/ CNRDStackNumberSet__vmt8(int a1)
{
  int result; // eax

  if ( dword_9B8030 != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_9B8030 + 12))(dword_9B8030, a1);
  return result;
}



// ------------------------------------------------------------
// 0x540860 CNRDStackNumberSet__vmt4 —— CNRDStackNumberSet__vmt4 标量删除析构
// ------------------------------------------------------------
void CNRDStackNumberSet__vmt4()
{
  dword_9B8030 = 0;
}



// ------------------------------------------------------------
// 0x540870 sub_540870 —— 数量窗口打开（69BCC0/402AE0 控件显示）
// ------------------------------------------------------------
int /*thiscall*/ sub_540870(void *this, int a2)
{
  sub_69BCC0(this);
  return sub_402AE0(a2);
}



// ------------------------------------------------------------
// 0x540890 sub_540890 —— 数量输入辅助（28 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_540890(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 8) = 0;
  *(this + 7) = 0;
  *(this + 9) = 0;
  *(this + 10) = 6;
  *(this + 11) = 7;
  *(this + 13) = 0;
  *(this + 12) = 7;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  *(this + 17) = 0xFFFF;
  *(this + 18) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5408E0 sub_5408E0 —— 数量输入辅助 2（50 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5408E0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  int (/*thiscall*/ ****v7)(uint32_t, int); // esi
  int i; // edi
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v10)(uint32_t, int); // ecx
  bool v11; // zf

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 4);
  *(this + 3) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 4) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  *(this + 5) = 0;
  v7 = (int (/*thiscall*/ ****)(uint32_t, int))(this + 8);
  for ( i = 2; i != 0; --i )
  {
    v9 = *(v7 - 2);
    if ( v9 != nullptr )
      result = (**v9)(v9, 1);
    v10 = *v7;
    v11 = *v7 == nullptr;
    *(v7 - 2) = nullptr;
    if ( !v11 )
      result = (**v10)(v10, 1);
    *v7++ = nullptr;
  }
  return result;
}



// ------------------------------------------------------------
// 0x540960 sub_540960 —— 数量输入框刷新（24 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_540960(uint32_t *this)
{
  int v2; // eax

  if ( dword_79BE54 == *(uint32_t *)(*(this + 3) + 12) )
  {
    v2 = *(uint32_t *)(*(this + 1) + 28);
    if ( *(uint8_t *)(v2 + 256) == 0 )
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v2 + 124) + 12);
      dword_79BE54 = dword_79BE4C;
    }
  }
  *(uint8_t *)(*(this + 2) + 16) = 0;
  *(this + 10) = 6;
  CNCommandChecker__vmt40(0, 1);
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 4))(this);
}



// ------------------------------------------------------------
// 0x5409C0 sub_5409C0 —— 数量确认：CLICK_BUTTON2 音 + 54A200 交易窗联动 + 540960 刷新
// ------------------------------------------------------------
int /*thiscall*/ sub_5409C0(uint32_t *this)
{
  if ( *(this + 11) == 0
    && *(this + 13) == 0
    && *(this + 12) == 4
    && *(this + 14) == 0
    && *(uint32_t *)(*(this + 1) + 64) != 0 )
  {
    sub_54A200(1);
  }
  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  return sub_540960(this);
}



// ============================================================
// 【分区 4】摆摊窗口私有实现（0x540A10-0x541900）
// 摊位列表构建 0x540DE0（203 行）；摊位物品操作 0x541190（237 行：登记/
// 取出/44A980 数组访问）；0x541620=摊位点击（CLICK_BUTTON2 + 5409C0）。
// ============================================================
// ------------------------------------------------------------
// 0x540A10 sub_540A10 —— 摊位数据访问辅助（30 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_540A10(uint32_t *this)
{
  int v1; // eax
  int *v2; // edx
  int *v3; // esi
  int v4; // ecx
  int result; // eax

  v1 = *(this + 1);
  v2 = *(int **)(v1 + 664);
  v3 = *(int **)(v1 + 668);
  if ( v2 == v3 )
    return 0;
  v4 = *(this + 17);
  while ( 1 )
  {
    result = *v2;
    if ( *(uint32_t *)(*v2 + 48) == v4 && *(uint8_t *)(result + 200) != 0 )
      break;
    if ( ++v2 == v3 )
      return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x540A50 sub_540A50 —— 摊位条目文本组装（541A30/541B20 + 432F00 全局窗口获取，50 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_540A50(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // eax
  int v8; // ecx
  int v9; // edx
  unsigned int v10; // esi
  uint32_t *v11; // eax
  int v12; // esi

  v3 = *(this + 10);
  if ( v3 == 2 )
  {
    if ( *(this + 11) == 5 )
    {
      v4 = *(this + 13);
      v5 = sub_541A30();
      v6 = sub_541B20(v5);
      if ( v4 < *(uint32_t *)(v6 + 8) )
        return *(uint32_t *)(*(uint32_t *)(v6 + 12) + 4 * v4);
    }
    else
    {
      v8 = *(uint32_t *)(*(this + 1) + 80);
      v9 = *(uint32_t *)(v8 + 96);
      v10 = *(this + 13);
      if ( v9 != 0 && v10 < (*(uint32_t *)(v8 + 100) - v9) >> 2 )
        return *(uint32_t *)(v9 + 4 * v10);
    }
  }
  else if ( v3 != 5 )
  {
    v11 = sub_432F00(*(this + 11));
    if ( v11 != nullptr )
    {
      v12 = *(this + 13);
      if ( v12 < v11[2] )
        return *(uint32_t *)(v11[3] + 4 * v12);
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x540AE0 sub_540AE0 —— 摊位展示绘制（126 行：43C250/43C060/43C410 列表控件 + 426BD0/69C780 图像 + 4BF300）
// ------------------------------------------------------------
int /*thiscall*/ sub_540AE0(int *this, void *Block)
{
  int v3; // edi
  uint8_t *v4; // eax
  uint8_t *v5; // eax
  void *v6; // eax
  int v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  int v12; // ebx
  uint8_t *v13; // eax
  uint32_t *v14; // edi
  uint32_t *v15; // ecx
  uint8_t *v16; // eax
  uint32_t *v17; // edi
  uint32_t *v18; // ecx
  bool v19; // cc
  int v20; // eax
  int v22; // [esp+Ch] [ebp-18h]
  int v23; // [esp+10h] [ebp-14h]
  int v24; // [esp+14h] [ebp-10h]
  int *Blocka; // [esp+2Ch] [ebp+8h]

  *(this + 1) = (int)Block;
  v3 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  v22 = v3;
  v4 = operator new(0x6Cu);
  if ( v4 != nullptr )
    v5 = sub_43C250(v4, v3, 50);
  else
    v5 = nullptr;
  *(this + 2) = (int)v5;
  v6 = operator new(0xE4u);
  if ( v6 != nullptr )
    v7 = sub_43C060((int)v6, 10, 70);
  else
    v7 = 0;
  *(this + 3) = v7;
  dword_9D3BD8 = dword_99FCCC;
  *(uint32_t *)(*(this + 3) + 128) = -5512193;
  sub_69A5F0((uint32_t *)*(this + 3), 38, 17);
  sub_69A840((uint32_t *)*(this + 2), *(this + 3));
  v8 = operator new(0x84u);
  if ( v8 != nullptr )
    v9 = sub_43C410(v8, v3, 9, 10, 11, 9, 0, 0);
  else
    v9 = nullptr;
  *(this + 4) = (int)v9;
  sub_69A5F0(v9, 25, 41);
  sub_69A840((uint32_t *)*(this + 2), *(this + 4));
  v10 = operator new(0x84u);
  if ( v10 != nullptr )
    v11 = sub_43C410(v10, v3, 12, 13, 14, 12, 0, 0);
  else
    v11 = nullptr;
  *(this + 5) = (int)v11;
  sub_69A5F0(v11, 86, 41);
  sub_69A840((uint32_t *)*(this + 2), *(this + 5));
  v23 = 8;
  v24 = 15;
  v12 = 51;
  Blocka = this + 8;
  do
  {
    v13 = operator new(0x84u);
    v14 = v13;
    if ( v13 != nullptr )
    {
      sub_426BD0(v13);
      *v14 = &nengine::CNButton::`vftable';
      sub_69C780((int)v14);
      sub_69C7B0((int)v14, v22, v12, v12 + 1, v12 + 2, v12, 0, 0);
      v15 = v14;
    }
    else
    {
      v15 = nullptr;
    }
    *(Blocka - 2) = (int)v15;
    sub_69A5F0(v15, 115, v24);
    sub_69A840((uint32_t *)*(this + 2), *(Blocka - 2));
    v16 = operator new(0x84u);
    v17 = v16;
    if ( v16 != nullptr )
    {
      sub_426BD0(v16);
      *v17 = &nengine::CNButton::`vftable';
      sub_69C780((int)v17);
      sub_69C7B0((int)v17, v22, v12 + 6, v12 + 7, v12 + 8, v12 + 6, 0, 0);
      v18 = v17;
    }
    else
    {
      v18 = nullptr;
    }
    *Blocka = (int)v18;
    sub_69A5F0(v18, 130, v23);
    sub_69A840((uint32_t *)*(this + 2), *Blocka);
    v12 += 3;
    v19 = v24 + 8 < 31;
    ++Blocka;
    v24 += 8;
    v23 += 14;
  }
  while ( v19 );
  if ( dword_79BE54 == *(uint32_t *)(*(this + 3) + 12) )
  {
    v20 = *(uint32_t *)(*(this + 1) + 28);
    if ( *(uint8_t *)(v20 + 256) == 0 )
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v20 + 124) + 12);
      dword_79BE54 = dword_79BE4C;
    }
  }
  *(uint8_t *)(*(this + 2) + 16) = 0;
  *(this + 10) = 6;
  sub_4BF300(0, 1);
  return (*(int (/*thiscall*/ **)(int *))(*this + 4))(this);
}


// ------------------------------------------------------------
// 0x540DE0 sub_540DE0 —— 摊位列表构建（203 行：540A10/62EE70/540A50/541A30/542AB0 + 484FA0/48FCA0/48FD70 窗口件）
// ------------------------------------------------------------
int /*thiscall*/ sub_540DE0(int *this, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
  int v8; // ebx
  int result; // eax
  int v11; // edi
  int v12; // ebx
  int v13; // edi
  int v14; // eax
  bool v15; // zf
  unsigned int v16; // ebx
  unsigned int v17; // eax
  int v18; // eax
  unsigned int v19; // ebx
  unsigned int v20; // ebx
  unsigned int v21; // eax
  int v22; // ecx
  int v23; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // edi
  int v27; // ebx
  int v28; // ebx
  int v29; // eax
  int v30; // edx
  int v31; // ecx
  int v32; // eax
  int v33; // edx
  int v34; // edx
  char Buffer[32]; // [esp+Ch] [ebp-24h] BYREF
  int v36; // [esp+2Ch] [ebp-4h]
  unsigned int v37; // [esp+44h] [ebp+14h]
  int v38; // [esp+44h] [ebp+14h]

  v8 = a2;
  v36 = dword_796E50;
  *(this + 11) = a3;
  *(this + 13) = a4;
  *(this + 14) = a6;
  *(this + 16) = a8;
  *(this + 10) = a2;
  *(this + 12) = a5;
  *(this + 15) = a7;
  if ( a2 == 5 )
  {
    *(this + 17) = a7;
    result = sub_540A10();
    if ( result == 0 )
      return result;
    result = sub_62EE70(result + 64);
    *(this + 18) = result;
    if ( result == 0 )
      return result;
    goto LABEL_41;
  }
  result = sub_540A50(1);
  v11 = result;
  if ( result == 0 )
    return result;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 20))(result, 1);
  if ( (uint8_t)result == 0 )
    return result;
  *(this + 17) = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11) + 4);
  if ( a2 != 1 )
  {
    if ( a2 != 2 )
      goto LABEL_43;
    v15 = *(this + 11) == 5;
    *(this + 18) = 1;
    if ( v15 )
    {
      sub_541A30();
      v16 = sub_542AB0(v11);
      if ( v16 == 0 )
      {
LABEL_35:
        v26 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11) + 56);
        if ( v26 != 0 )
        {
          v27 = *(this + 18);
          v38 = *((uint32_t *)dword_8F852C + 1);
          if ( (sub_484FA0() - v38) / v26 >= v27 )
          {
            v29 = v27;
          }
          else
          {
            v28 = *((uint32_t *)dword_8F852C + 1);
            v29 = (sub_484FA0() - v28) / v26;
          }
          *(this + 18) = v29;
        }
        v8 = a2;
        result = 1;
        goto LABEL_41;
      }
      v17 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));
      if ( v17 / v16 >= (*(int (/*fastcall*/ **)(int, unsigned int))(*(uint32_t *)v11 + 44))(v11, v17 % v16) )
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 44))(v11);
      else
        v18 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3))
            / v16;
    }
    else
    {
      v19 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11) + 36);
      if ( v19 != 0 )
        *(this + 18) = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C
                                                                                                 + 3))
                     / v19;
      v20 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11) + 44);
      if ( v20 != 0 )
      {
        v37 = *(this + 18);
        if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8))
           / v20 >= v37 )
          v21 = v37;
        else
          v21 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8))
              / v20;
        *(this + 18) = v21;
      }
      v22 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11) + 40);
      if ( v22 != 0 )
      {
        v23 = dword_8F7C0C / v22;
        if ( dword_8F7C0C / v22 >= *(this + 18) )
          v23 = *(this + 18);
        *(this + 18) = v23;
      }
      v24 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11) + 52);
      if ( v24 == 0 )
        goto LABEL_35;
      v25 = sub_48FCA0();
      v18 = sub_48FD70(v25) / v24;
    }
    *(this + 18) = v18;
    goto LABEL_35;
  }
  result = a3;
  if ( (a3 == 4 || a5 == 4) && *(uint32_t *)(dword_8F8538 + 8) == 1 )
    return result;
  if ( a3 == 0 && a5 == 4 && a4 == 0 )
  {
    v12 = **(uint32_t **)(*(uint32_t *)(dword_8F8538 + 16) + 12);
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 44))(v11);
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 44))(v12);
    v8 = a2;
    *(this + 18) = v14 + v13;
LABEL_47:
    result = (*(int (/*thiscall*/ **)(uint32_t))(***(uint32_t ***)(*(uint32_t *)(dword_8F8538 + 16) + 12) + 44))(**(uint32_t **)(*(uint32_t *)(dword_8F8538 + 16) + 12));
    goto LABEL_41;
  }
LABEL_43:
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 44))(v11);
  *(this + 18) = result;
  if ( a2 == 1 && a3 == 0 && a5 == 4 && a4 == 0 )
    goto LABEL_47;
LABEL_41:
  sprintf(Buffer, "%d", result);
  sub_69BCC0(*(this + 3));
  sub_402AE0(Buffer);
  if ( v8 == 2 )
  {
    v30 = *(this + 2);
    v31 = pt.x - (*(uint32_t *)(v30 + 28) >> 1);
    v32 = pt.y - (*(uint32_t *)(v30 + 32) >> 1);
  }
  else
  {
    v31 = pt.x - 51;
    v32 = pt.y - 53;
  }
  if ( v31 >= 0 )
  {
    v33 = *(uint32_t *)(*(this + 2) + 28);
    if ( (unsigned int)(v33 + v31) > 0x280 )
      v31 = 640 - v33;
  }
  else
  {
    v31 = 0;
  }
  if ( v32 >= 0 )
  {
    v34 = *(uint32_t *)(*(this + 2) + 32);
    if ( (unsigned int)(v34 + v32) > 0x1E0 )
      v32 = 480 - v34;
  }
  else
  {
    v32 = 0;
  }
  *(uint8_t *)(*(this + 2) + 16) = 1;
  sub_69A5F0((uint32_t *)*(this + 2), v31, v32);
  dword_79BE4C = *(uint32_t *)(*(this + 3) + 12);
  dword_79BE54 = dword_79BE4C;
  return sub_4BF300(0, 0);
}


// ------------------------------------------------------------
// 0x541190 sub_541190 —— 摊位物品操作（237 行：44E8D0 登记 + 44A980 数组访问 + 50D660/547170/563E90/62F530/44E340/5634F0）
// ------------------------------------------------------------
void /*thiscall*/ sub_541190(void *this)
{
  int v2; // eax
  int v3; // edi
  const char *v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  char v13; // al
  uint32_t *v14; // eax
  int *v15; // eax
  int v16; // edx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // [esp-14h] [ebp-44h]
  uint32_t *v24; // [esp-Ch] [ebp-3Ch]
  signed int v25; // [esp-8h] [ebp-38h]
  void *v26[4]; // [esp+8h] [ebp-28h] BYREF
  int v27; // [esp+18h] [ebp-18h] BYREF
  int v28; // [esp+1Ch] [ebp-14h]
  int v29; // [esp+20h] [ebp-10h]
  int v30; // [esp+2Ch] [ebp-4h]

  v2 = *((uint32_t *)this + 10);
  v3 = 0;
  v29 = 0;
  if ( v2 == 5 )
  {
    v29 = sub_540A10();
    if ( v29 == 0 )
    {
      sub_540960(this);
      return;
    }
  }
  else
  {
    v3 = sub_540A50(0);
    if ( v3 == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 16))(v3) + 4) != *((uint32_t *)this + 17) )
    {
      v22 = sub_422E70(492);
      sub_44E8D0(*((char **)this + 1), (void *)0x1B, v22, 0);
      sub_540960(this);
      return;
    }
  }
  v4 = (const char *)sub_69B740(*((uint32_t *)this + 3));
  v5 = j__atol(v4);
  if ( *((uint32_t *)this + 10) == 1
    && *((uint32_t *)this + 11) == 0
    && *((uint32_t *)this + 12) == 4
    && *((uint32_t *)this + 13) == 0 )
  {
    v5 -= (*(int (/*thiscall*/ **)(uint32_t))(***(uint32_t ***)(*(uint32_t *)(dword_8F8538 + 16) + 12) + 44))(**(uint32_t **)(*(uint32_t *)(dword_8F8538 + 16) + 12));
    if ( v5 < 0 )
    {
      *((uint32_t *)this + 11) = 4;
      *((uint32_t *)this + 12) = 0;
      *((uint32_t *)this + 14) = 0;
      v3 = **(uint32_t **)(*(uint32_t *)(dword_8F8538 + 16) + 12);
      v5 = -v5;
    }
  }
  if ( v5 == 0 )
    goto LABEL_29;
  v6 = *((uint32_t *)this + 10);
  if ( v6 != 2 && v6 != 5 && v5 > (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 44))(v3)
    || *((uint32_t *)this + 11) == 5 && v5 > (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 44))(v3) )
  {
    v7 = sub_422E70(493);
    sub_44E8D0(*((char **)this + 1), (void *)0x1B, v7, 0);
    return;
  }
  v8 = *((uint32_t *)this + 10);
  if ( v8 == 0 )
  {
    sub_44E8D0(*((char **)this + 1), (void *)0x15, v3, v5);
    sub_540960(this);
    return;
  }
  if ( v8 == 1 )
  {
    v9 = *((uint32_t *)this + 11);
    if ( (v9 != 0 || *((uint32_t *)this + 12) != 2) && (v9 != 2 || *((uint32_t *)this + 12) != 0) )
    {
      if ( v9 != 0 || *((uint32_t *)this + 12) != 4 )
      {
        if ( v9 != 4 || *((uint32_t *)this + 12) != 0 )
        {
          if ( v9 == 0 )
          {
            if ( *((uint32_t *)this + 12) == 5 )
            {
              v19 = sub_541A30();
              (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v19 + 60))(
                v19,
                *((uint32_t *)this + 13),
                *((uint32_t *)this + 14),
                *((uint32_t *)this + 11),
                *((uint32_t *)this + 15),
                v5);
            }
            else if ( *((uint32_t *)this + 12) == 6 )
            {
              (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 8))(this, v5);
            }
          }
        }
        else
        {
          v15 = (int *)sub_44A980(*((uint32_t *)this + 14));
          v29 = (int)v15;
          if ( v15 == nullptr
            || (v16 = *(uint32_t *)v3,
                v28 = *v15,
                v17 = (*(int (/*thiscall*/ **)(int))(v16 + 16))(v3),
                (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(v28 + 60))(v29, *(uint32_t *)(v17 + 4)) != 0) )
          {
            sub_484AF0(dword_8F8538, *((uint32_t *)this + 13), v5, *((uint32_t *)this + 12), *((uint32_t *)this + 14));
          }
          else
          {
            v18 = sub_422E70(494);
            sub_44E8D0(*((char **)this + 1), (void *)0x1B, v18, 0);
          }
        }
      }
      else
      {
        sub_4848E0(dword_8F8538, v5, 0, *((uint32_t *)this + 13), v5);
      }
      goto LABEL_29;
    }
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 16))(v3);
    v11 = *((uint32_t *)this + 12);
    v12 = v5 * *(uint32_t *)(v10 + 56);
    if ( v11 != 0 )
    {
      if ( v11 != 2 )
        goto LABEL_32;
      v13 = sub_50D660(v12, 1);
    }
    else
    {
      v13 = sub_547170(v12, 1);
    }
    if ( v13 == 1 )
    {
LABEL_29:
      sub_540960(this);
      return;
    }
LABEL_32:
    v25 = *((uint32_t *)this + 14);
    v24 = (uint32_t *)sub_432F00(*((uint32_t *)this + 12));
    v23 = *((uint32_t *)this + 13);
    v14 = (uint32_t *)sub_432F00(*((uint32_t *)this + 11));
    sub_4866D0(v14, v23, v5, v24, v25);
    goto LABEL_29;
  }
  if ( v8 != 2 )
  {
    switch ( v8 )
    {
      case 3:
        if ( *((uint32_t *)this + 16) == 1 )
        {
          byte_9B888A = *((uint32_t *)this + 15) != 0;
          sub_44E8D0(*((char **)this + 1), (void *)0x14, v3, v5);
        }
        else
        {
          sub_563E90(v3, v5, *((uint32_t *)this + 1));
          if ( *((uint32_t *)this + 15) == 1 )
            sub_44ABE0(5);
        }
        break;
      case 4:
        if ( *((uint32_t *)this + 11) == 0 )
          sub_486330(dword_8F852C, *((uint32_t *)this + 13), v5);
        break;
      case 5:
        sub_62F530(v5);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v29 + 32))(v29);
        break;
      default:
        break;
    }
    goto LABEL_29;
  }
  if ( *((uint32_t *)this + 11) == 5 )
  {
    v20 = sub_541A30();
    (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v20 + 96))(v20, *((uint32_t *)this + 13), v5);
    goto LABEL_29;
  }
  memset(&v26[1], 0, 12);
  v30 = 0;
  v27 = v3;
  v28 = v5;
  sub_44E340(&v27);
  if ( (uint8_t)sub_5634F0(v26, 1) != 0 )
  {
    if ( *((uint32_t *)this + 16) == 1 )
    {
      byte_9B8889 = *((uint32_t *)this + 15) != 0;
      sub_44E8D0(*((char **)this + 1), (void *)0x13, v3, v5);
      v30 = -1;
      sub_5E5260(v26);
    }
    else
    {
      v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 16))(v3);
      sub_563410(*(uint32_t *)(v21 + 4), v5);
      if ( *((uint32_t *)this + 15) == 1 )
        sub_44ABE0(4);
      v30 = -1;
      sub_5E5260(v26);
    }
    goto LABEL_29;
  }
  sub_5E5260(v26);
}


// ------------------------------------------------------------
// 0x541620 sub_541620 —— 摊位点击处理：CLICK_BUTTON2 + 69A650 显示 + 69B740/69BD90 输入 + 541190/5409C0 联动
// ------------------------------------------------------------
char /*thiscall*/ sub_541620(int *this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // edi
  const char *v8; // eax
  const char *v9; // eax
  int v10; // eax
  int v11; // eax
  const char *v12; // eax
  const char *v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edi
  const char *v17; // eax
  const char *v18; // eax
  int v19; // eax
  int v20; // eax
  const char *v21; // eax
  const char *v22; // eax
  int v23; // eax
  const char *v24; // eax
  int v25; // eax
  int v26; // ecx
  int v27; // eax
  int v28; // eax
  char v29; // cl
  int v30; // eax
  char Buffer[16]; // [esp+4h] [ebp-14h] BYREF
  int v33; // [esp+14h] [ebp-4h]

  v2 = *(this + 2);
  v33 = dword_796E50;
  LOBYTE(v3) = *(uint8_t *)(v2 + 16);
  if ( (uint8_t)v3 == 0 )
    return v3;
  sub_69A650(v2);
  v4 = *(this + 2);
  v5 = dword_79BE34;
  if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) )
  {
    dword_79BE4C = *(uint32_t *)(*(this + 3) + 12);
    dword_79BE54 = dword_79BE4C;
  }
  v6 = *(this + 6);
  if ( *(uint8_t *)(v6 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v6 + 12) )
  {
    v7 = *(this + 18);
    v8 = (const char *)sub_69B740(*(this + 3));
    if ( j__atol(v8) + 1 >= v7 )
    {
      v10 = v7;
    }
    else
    {
      v9 = (const char *)sub_69B740(*(this + 3));
      v10 = j__atol(v9) + 1;
    }
    sprintf(Buffer, "%d", v10);
    sub_69BD90(*(this + 3), Buffer);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v5 = dword_79BE34;
  }
  v11 = *(this + 7);
  if ( *(uint8_t *)(v11 + 17) != 0 && v5 == *(uint32_t *)(v11 + 12) )
  {
    v12 = (const char *)sub_69B740(*(this + 3));
    if ( j__atol(v12) - 1 <= 0 )
    {
      v14 = 0;
    }
    else
    {
      v13 = (const char *)sub_69B740(*(this + 3));
      v14 = j__atol(v13) - 1;
    }
    sprintf(Buffer, "%d", v14);
    sub_69BD90(*(this + 3), Buffer);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v5 = dword_79BE34;
  }
  v15 = *(this + 8);
  if ( *(uint8_t *)(v15 + 17) != 0 && v5 == *(uint32_t *)(v15 + 12) )
  {
    v16 = *(this + 18);
    v17 = (const char *)sub_69B740(*(this + 3));
    if ( j__atol(v17) + 10 >= v16 )
    {
      v19 = v16;
    }
    else
    {
      v18 = (const char *)sub_69B740(*(this + 3));
      v19 = j__atol(v18) + 10;
    }
    sprintf(Buffer, "%d", v19);
    sub_69BD90(*(this + 3), Buffer);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v5 = dword_79BE34;
  }
  v20 = *(this + 9);
  if ( *(uint8_t *)(v20 + 17) != 0 && v5 == *(uint32_t *)(v20 + 12) )
  {
    v21 = (const char *)sub_69B740(*(this + 3));
    if ( j__atol(v21) - 10 <= 0 )
    {
      v23 = 0;
    }
    else
    {
      v22 = (const char *)sub_69B740(*(this + 3));
      v23 = j__atol(v22) - 10;
    }
    sprintf(Buffer, "%d", v23);
    sub_69BD90(*(this + 3), Buffer);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v24 = (const char *)sub_69B740(*(this + 3));
  v25 = j__atol(v24);
  if ( v25 < 0 )
  {
    v26 = 0;
    goto LABEL_32;
  }
  v26 = *(this + 18);
  if ( v25 > v26 )
  {
LABEL_32:
    if ( v26 != v25 )
    {
      sprintf(Buffer, "%d", v26);
      sub_69BD90(*(this + 3), Buffer);
    }
  }
  v27 = *(this + 4);
  if ( *(uint8_t *)(v27 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v27 + 12)
    || (v28 = *(this + 3), v29 = *(uint8_t *)(v28 + 116), *(uint8_t *)(v28 + 116) = 0, v29 != 0) )
  {
    sub_541190(this);
  }
  v30 = *(this + 4);
  if ( *(uint8_t *)(v30 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v30 + 12) )
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  v3 = *(this + 5);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
    LOBYTE(v3) = sub_5409C0(this);
  return v3;
}


// ============================================================
// 【分区 5】CNRDPrivateStoreWindow 摆摊窗口族（0x541900-0x544960）
// 基类 + _Display(展示)/_Buy(收购)/_Sell(出售) 三个子窗口；
// vmt0(0x543BB0, 220 行)=构造与单例登记 dword_9B8034，日志
// "Another private shop created!"；vmt68=页绘制(69A5F0/43C250)。
// ============================================================
// ------------------------------------------------------------
// 0x541900 CNRDPrivateStoreWindow__vmt64 —— CNRDPrivateStoreWindow__vmt64 子窗口槽（15 行）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow__vmt64(uint32_t *this)
{
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 9) = 0;
  *(this + 8) = 2;
  *(this + 6) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x541920 CNRDPrivateStoreWindow__vmtC —— CNRDPrivateStoreWindow__vmtC 打开槽（44BBA0=WINDOW_SHOW）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreWindow__vmtC(uint32_t **this)
{
  sub_44BBA0(*(this + 2), 0, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x541930 CNRDPrivateStoreWindow__vmt1C —— CNRDPrivateStoreWindow__vmt1C 关闭/刷新槽（13 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNRDPrivateStoreWindow__vmt1C(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 1);
  return *(uint8_t *)(v1 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v1 + 12);
}



// ------------------------------------------------------------
// 0x541950 CNRDPrivateStoreWindow__vmt10 —— CNRDPrivateStoreWindow__vmt10 状态切换槽（44ABE0/44E850 + 540960 输入框刷新）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow__vmt10(uint32_t *this)
{
  uint32_t *v2; // ecx
  int v3; // eax
  uint32_t *v4; // ecx
  int result; // eax

  v2 = (uint32_t *)*(this + 2);
  v3 = v2[626];
  if ( v3 == 4 || v3 == 5 || v3 == 6 || v3 == 7 )
    sub_44ABE0(v2, 0);
  sub_44E850((uint32_t *)*(this + 2), 19);
  sub_44E850((uint32_t *)*(this + 2), 20);
  sub_44E850((uint32_t *)*(this + 2), 22);
  if ( dword_9B88D0 != 0 && dword_795378 == 9 )
    sub_44E850((uint32_t *)*(this + 2), 26);
  v4 = *(uint32_t **)(*(this + 2) + 116);
  result = v4[10];
  if ( result == 2 || result == 3 )
    result = sub_540960(v4);
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5419E0 CNRDPrivateStoreWindow__vmt6C —— CNRDPrivateStoreWindow__vmt6C 槽（10 行）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow__vmt6C(uint32_t *this)
{
  return *(this + 8);
}



// ------------------------------------------------------------
// 0x5419F0 sub_5419F0 —— 摊位动画辅助（429830）
// ------------------------------------------------------------
int /*thiscall*/ sub_5419F0(uint32_t *this, int a2)
{
  int result; // eax

  result = sub_429830((uint32_t *)dword_8F8500, a2);
  if ( result != 0 )
  {
    result = *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, a2) + 192);
    *(this + 4) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x541A30 sub_541A30 —— 摊位条目名取串（10 行）
// ------------------------------------------------------------
int sub_541A30()
{
  return *(uint32_t *)dword_9B8038;
}



// ------------------------------------------------------------
// 0x541A40 sub_541A40 —— 摊位结构初始化（18 行）
// ------------------------------------------------------------
int sub_541A40()
{
  int result; // eax

  result = 0;
  while ( *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * result) )
  {
    if ( ++result >= 3 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x541A60 sub_541A60 —— 摊位子页切换（44AB50 + 44E850 + 44BBA0）
// ------------------------------------------------------------
uint8_t /*cdecl*/ sub_541A60(int a1)
{
  byte_9B804C = a1 == 1;
  sub_44AB50(dword_8F8528, 0, 12);
  *(uint32_t *)dword_9B8038 = *(uint32_t *)(dword_9B8034 + 4 * a1);
  if ( byte_9B804C != 0 )
    byte_9B804C = 0;
  else
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)dword_9B8038 + 76))(*(uint32_t *)dword_9B8038);
  sub_44E850(dword_8F8528, 71);
  return sub_44BBA0(dword_8F8528, 9, 0);
}



// ------------------------------------------------------------
// 0x541AF0 sub_541AF0 —— 摊位辅助（20 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_541AF0(uint32_t *this)
{
  int v1; // ecx
  int result; // eax

  v1 = *(this + 9);
  result = 0;
  while ( result < *(uint32_t *)(v1 + 8) && *(uint32_t *)(*(uint32_t *)(v1 + 12) + 4 * result) != 0 )
  {
    if ( ++result >= 14 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x541B30 sub_541B30 —— 摊位条目详情（4F2CE0/422E70 取串 + 44E8D0）
// ------------------------------------------------------------
int /*cdecl*/ sub_541B30(int a1, int a2, int a3, int a4, int a5, int a6)
{
  char *v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // edx
  int v10; // esi
  int i; // eax
  int result; // eax
  int v13; // [esp-10h] [ebp-120h]
  char Buffer[256]; // [esp+Ch] [ebp-104h] BYREF
  int v15; // [esp+10Ch] [ebp-4h]

  v15 = dword_796E50;
  memset(Buffer, 0, 255);
  v13 = sub_4F2CE0(a1);
  v6 = sub_422E70(1338);
  sprintf(Buffer, v6, v13, a3, a4, a5);
  v7 = 0;
  while ( *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * v7) )
  {
    if ( ++v7 >= 3 )
    {
      v8 = -1;
      goto LABEL_5;
    }
  }
  v8 = v7;
LABEL_5:
  *(uint32_t *)dword_9B8038 = *(uint32_t *)(dword_9B8034 + 4);
  (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)dword_9B8038 + 68))(*(uint32_t *)dword_9B8038, a2, a6);
  v9 = *(uint32_t *)(dword_9B8040 + 8);
  v10 = 0;
  for ( i = 0; i < 14; i += 2 )
  {
    if ( i < v9 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * i) != 0 )
      ++v10;
    if ( i + 1 < v9 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * i + 4) != 0 )
      ++v10;
  }
  if ( v10 == 0 )
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)dword_9B8038 + 84))(*(uint32_t *)dword_9B8038);
  sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);
  result = dword_9B8038;
  *(uint32_t *)dword_9B8038 = *(uint32_t *)(dword_9B8034 + 4 * v8);
  return result;
}



// ------------------------------------------------------------
// 0x541C60 sub_541C60 —— 摊位登记提交（522300/4F2D40/484F40 + 47CD00 音效）
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_541C60(int ArgList, void *a2, int a3, int a4, int a5)
{
  int v5; // eax
  int v6; // esi
  int v7; // eax
  uint32_t *v8; // ecx
  int *v9; // edi
  char v10; // al
  int v11; // edx
  int v12; // eax
  void *v13; // eax
  bool v15; // [esp+Fh] [ebp-1h]

  v5 = sub_522300(a2, a3, a4, 0, a5, 1);
  v6 = v5;
  v15 = false;
  if ( v5 != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 16))(v5);
    if ( sub_4F2D40(*(uint32_t *)(v7 + 4)) == 2 )
      v15 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 172))(v6) <= 7;
  }
  v8 = dword_8F852C;
  if ( v15 )
    v8 = dword_8F8534;
  if ( ArgList < v8[2] && (v9 = *(int **)(v8[3] + 4 * ArgList)) != nullptr )
  {
    v10 = (*(int (/*thiscall*/ **)(int *, void *))(*v9 + 60))(v9, a2);
    v11 = *v9;
    if ( v10 != 0 )
    {
      (*(void (/*thiscall*/ **)(int *, int))(v11 + 48))(v9, a3);
    }
    else
    {
      v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 16))(v9);
      off_77F3FC((char *)&byte_7246D4, ArgList, *(uint32_t *)(v12 + 4));
    }
  }
  else
  {
    sub_484F40(ArgList, v6, 1);
  }
  if ( v6 != 0 )
  {
    v13 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 56))(v6);
    sub_432EA0(v13, -1, 0, 0);
    if ( !v15 && *((uint32_t *)dword_8F8528 + 27) == 0 && ArgList >= 9 )
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 14) + 56) = (ArgList - 9) / 32;
  }
  return sub_47CD00((uint32_t *)dword_8F8540);
}



// ------------------------------------------------------------
// 0x541D80 sub_541D80 —— 摊位物品上架（45E510/45E550 查询 + 423200/423290/423380 参数串 + 44ABF0）
// ------------------------------------------------------------
int sub_541D80()
{
  int v0; // esi
  uint32_t *v1; // edi
  int result; // eax
  uint32_t *v3; // esi
  char *v4; // eax
  int v5; // ecx
  int *v6; // eax
  int v7; // eax
  int v8; // [esp+8h] [ebp-10h] BYREF
  int v9; // [esp+Ch] [ebp-Ch] BYREF
  int v10; // [esp+10h] [ebp-8h] BYREF
  char v11[4]; // [esp+14h] [ebp-4h] BYREF

  v0 = dword_8F7C08;
  v1 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C08 + 80))(dword_8F7C08);
  v10 = sub_45E510(v1, pt.x, 1);
  v9 = sub_45E550(v1, pt.y, 0, 1);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v0 + 136))(v0, v10, v9, 0) != 0
    || (uint8_t)(result = (*(int (/*thiscall*/ **)(int, int *, int *, int, int, int, uint32_t, int))(*(uint32_t *)v0 + 140))(
                          v0,
                          &v10,
                          &v9,
                          v10,
                          v9,
                          100,
                          0,
                          1)) != 0 )
  {
    v3 = (uint32_t *)dword_8F7C08;
    sub_423200(dword_8F7B08, 88);
    v11[0] = *(uint8_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 100);
    sub_423290(dword_8F7B08, (int)v11, 1);
    v4 = *(char **)(*(uint32_t *)(dword_8F7A24 + 20) + 104);
    if ( v4 != nullptr )
      v11[0] = *v4;
    else
      v11[0] = -1;
    sub_423290(dword_8F7B08, (int)v11, 1);
    v8 = v10;
    sub_423290(dword_8F7B08, (int)&v8, 2);
    v8 = v9;
    sub_423290(dword_8F7B08, (int)&v8, 2);
    sub_423380(dword_8F7B08);
    v5 = *(uint32_t *)(dword_8F7A24 + 20);
    v6 = *(int **)(v5 + 104);
    if ( v6 != nullptr )
      v7 = *v6;
    else
      v7 = -1;
    sub_42FBB0(v3, *(uint32_t *)(v5 + 100), v7, v10, v9);
    return sub_44ABF0(dword_8F8528);
  }
  return result;
}



// ------------------------------------------------------------
// 0x541ED0 sub_541ED0 —— 上架参数写入 2（423200/423290/423380 + 44ABF0）
// ------------------------------------------------------------
int /*cdecl*/ sub_541ED0(int a1)
{
  sub_423200(dword_8F7B08, 86);
  sub_423290(dword_8F7B08, (int)&a1, 4);
  sub_423380(dword_8F7B08);
  return sub_44ABF0(dword_8F8528);
}



// ------------------------------------------------------------
// 0x541F10 sub_541F10 —— 上架参数写入 3（423200/423380 + 44ABF0）
// ------------------------------------------------------------
int sub_541F10()
{
  sub_423200(dword_8F7B08, 91);
  sub_423380(dword_8F7B08);
  return sub_44ABF0(dword_8F8528);
}



// ------------------------------------------------------------
// 0x541F40 CNRDPrivateStoreWindow__vmt50 —— CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
// ------------------------------------------------------------
int /*stdcall*/ CNRDPrivateStoreWindow__vmt50(int a1, int a2)
{
  sub_423200(dword_8F7B08, 85);
  sub_423290(dword_8F7B08, (int)&a1, 2);
  a1 = a2;
  sub_423290(dword_8F7B08, (int)&a1, 4);
  sub_423380(dword_8F7B08);
  return sub_44ABF0(dword_8F8528);
}



// ------------------------------------------------------------
// 0x541FA0 CNRDPrivateStoreWindow__vmt54 —— CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
// ------------------------------------------------------------
int CNRDPrivateStoreWindow__vmt54()
{
  sub_423200(dword_8F7B08, 89);
  sub_423380(dword_8F7B08);
  return sub_44ABF0(dword_8F8528);
}



// ------------------------------------------------------------
// 0x541FD0 CNRDPrivateStoreWindow__vmt58 —— CNRDPrivateStoreWindow__vmt58 槽（16 行）
// ------------------------------------------------------------
int CNRDPrivateStoreWindow__vmt58()
{
  int result; // eax

  sub_423200(dword_8F7B08, 87);
  result = sub_423380(dword_8F7B08);
  if ( result == 1 )
    return sub_44ABF0(dword_8F8528);
  return result;
}



// ------------------------------------------------------------
// 0x542000 sub_542000 —— 摊位条目查询（422E70 取串 + 44E8D0，46 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_542000(int a1)
{
  int result; // eax
  char *v2; // eax

  result = a1;
  switch ( a1 )
  {
    case 53:
      v2 = sub_422E70(1325);
      break;
    case 52:
      v2 = sub_422E70(1326);
      break;
    case 17:
      v2 = sub_422E70(1327);
      break;
    case 22:
      v2 = sub_422E70(1328);
      break;
    case 10:
      v2 = sub_422E70(1329);
      break;
    case 4:
      v2 = sub_422E70(1330);
      break;
    case 1:
      v2 = sub_422E70(1331);
      break;
    case 55:
      v2 = sub_422E70(1342);
      break;
    case 21:
      v2 = sub_422E70(1355);
      break;
    default:
      return result;
  }
  return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);
}



// ------------------------------------------------------------
// 0x5420A0 sub_5420A0 —— 摊位条目查询 2（+43BEE0 图标 + 44ABE0）
// ------------------------------------------------------------
int /*cdecl*/ sub_5420A0(int a1)
{
  int result; // eax
  char *v2; // eax
  char *v3; // eax
  uint32_t *v4; // esi
  char *v5; // eax
  char *v6; // eax

  result = a1;
  switch ( a1 )
  {
    case 53:
      v2 = sub_422E70(1321);
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);
      return off_77F3FC((char *)&byte_724748);
    case 20:
      v3 = sub_422E70(1322);
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);
      return off_77F3FC((char *)&byte_724728);
    case 51:
      v4 = *((uint32_t **)dword_8F8528 + 7);
      v5 = sub_422E70(1323);
      sub_43BEE0(v4, (int)v5, -6567706, 0, -1);
      sub_44ABE0(dword_8F8528, 16);
      return off_77F3FC((char *)&byte_724708);
    case 57:
      v6 = sub_422E70(1351);
      break;
    case 58:
      v6 = sub_422E70(1352);
      break;
    default:
      return result;
  }
  return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v6, 0);
}



// ------------------------------------------------------------
// 0x542190 sub_542190 —— 摊位条目查询 3（+44AB50 页切换）
// ------------------------------------------------------------
int /*cdecl*/ sub_542190(int a1)
{
  int result; // eax
  char *v2; // eax
  char *v3; // eax
  char *v4; // eax

  result = a1;
  switch ( a1 )
  {
    case 53:
      v2 = sub_422E70(1325);
      return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);
    case 54:
      v3 = sub_422E70(1326);
      return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);
    case 22:
      sub_44AB50(dword_8F8528, 1, 12);
      v4 = sub_422E70(1324);
      return sub_44E8D0((char *)dword_8F8528, (void *)0x40, (int)v4, 0);
    default:
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x542220 sub_542220 —— 摊位条目查询 4（28 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_542220(int a1)
{
  int result; // eax
  char *v2; // eax

  result = a1;
  switch ( a1 )
  {
    case 53:
      v2 = sub_422E70(1325);
      break;
    case 52:
      v2 = sub_422E70(1326);
      break;
    case 17:
      v2 = sub_422E70(1332);
      break;
    default:
      return result;
  }
  return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);
}



// ------------------------------------------------------------
// 0x542270 sub_542270 —— 输入框联动（69B740/69BD90）
// ------------------------------------------------------------
int /*thiscall*/ sub_542270(int *this)
{
  int v2; // ecx
  const char *v3; // edi
  int result; // eax
  char v5; // [esp+0h] [ebp-4h]

  if ( sub_69B740(*(this + 15)) != 0 )
  {
    v2 = *(this + 15);
    if ( *(uint32_t *)(v2 + 192) != 0 && *(uint32_t *)(v2 + 188) != 0 )
    {
      if ( *(uint32_t *)(v2 + 192) != 0 )
        v3 = *(const char **)(v2 + 188);
      else
        v3 = nullptr;
      if ( strcmp(v3, (const char *)sub_69B740(v2)) == 0 )
        sub_69BD90(*(this + 15), (char *)szPassword, v5);
    }
  }
  result = *(uint32_t *)(*(this + 15) + 12);
  dword_79BE4C = result;
  dword_79BE54 = result;
  return result;
}



// ------------------------------------------------------------
// 0x542310 sub_542310 —— 22 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_542310(uint32_t *this)
{
  int v2; // eax
  int result; // eax

  v2 = *(uint32_t *)(*(this + 2) + 28);
  if ( *(uint8_t *)(v2 + 256) == 0 )
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v2 + 124) + 12);
    dword_79BE54 = dword_79BE4C;
  }
  CNCommandChecker__vmt40(0, 1);
  result = *(uint32_t *)(*(this + 2) + 28);
  *(uint8_t *)(*(uint32_t *)(result + 136) + 17) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x542360 CNRDPrivateStoreWindow_Display__vmt64 —— CNRDPrivateStoreWindow_Display__vmt64 槽（16 行）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt64(uint32_t *this)
{
  *(this + 14) = 0;
  *(this + 13) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 15) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x542380 CNRDPrivateStoreWindow_Display__vmtC —— CNRDPrivateStoreWindow_Display__vmtC 打开槽（44BBA0 + 69BCC0/402AE0 展示）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreWindow_Display__vmtC(int this)
{
  char *v2; // ebx

  sub_44BBA0(*(uint32_t **)(this + 8), 0, 0);
  v2 = sub_422E70(1334);
  sub_69BCC0(*(uint32_t *)(this + 60));
  sub_402AE0(v2);
  dword_79BE4C = *(uint32_t *)(*(uint32_t *)(this + 60) + 12);
  dword_79BE54 = dword_79BE4C;
  return 1;
}



// ------------------------------------------------------------
// 0x5423D0 CNRDPrivateStoreWindow_Display__vmt10 —— CNRDPrivateStoreWindow_Display__vmt10 状态切换（540960 输入框 + 544A10）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt10(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // ecx
  char result; // al
  int v5; // eax
  int i; // esi

  CNRDPrivateStoreWindow__vmt10(this);
  v2 = *(uint32_t *)(*(this + 2) + 28);
  if ( *(uint8_t *)(v2 + 256) == 0 )
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v2 + 124) + 12);
    dword_79BE54 = dword_79BE4C;
  }
  CNCommandChecker__vmt40(0, 1);
  *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(*(this + 2) + 28) + 136) + 17) = 1;
  v3 = *(uint32_t **)(*(this + 2) + 116);
  if ( v3[10] == 1 )
    sub_540960(v3);
  sub_544A10(dword_9B8050);
  result = byte_9B804C;
  if ( byte_9B804C == 0 )
  {
    v5 = dword_9B8040;
    for ( i = 0; i < 14; ++i )
    {
      if ( i < *(uint32_t *)(v5 + 8) && *(uint32_t *)(*(uint32_t *)(v5 + 12) + 4 * i) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 72))(this, i);
        v5 = dword_9B8040;
      }
    }
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x542490 sub_542490 —— 展示子窗口辅助（16 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_542490(int a1)
{
  int result; // eax
  int i; // ecx

  result = a1;
  for ( i = *(uint32_t *)(a1 + 8); *(uint8_t *)(i + 21) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x5424B0 sub_5424B0 —— 展示子窗口公共更新（25 行——基类/Buy/Sell 共用）
// ------------------------------------------------------------
int /*thiscall*/ sub_5424B0(void *this)
{
  int v1; // edi
  int v2; // ecx

  v1 = 7 * (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 108))(this);
  v2 = 0;
  if ( v1 <= 0 )
    return -1;
  while ( pt.x < 32 * (v2 % 7) + 61
       || pt.x >= 32 * (v2 % 7) + 89
       || pt.y < 32 * (v2 / 7) + 291
       || pt.y >= 32 * (v2 / 7) + 319 )
  {
    if ( ++v2 >= v1 )
      return -1;
  }
  return v2;
}



// ------------------------------------------------------------
// 0x542520 CNRDPrivateStoreWindow_Display__vmt1C —— CNRDPrivateStoreWindow_Display__vmt1C 刷新槽（5424B0 + 432F00）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt1C(uint32_t *this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  uint32_t *v6; // esi
  uint32_t *v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // eax

  v2 = *(this + 1);
  if ( *(uint8_t *)(v2 + 17) == 0 || dword_79BE34 != *(uint32_t *)(v2 + 12) )
    return 0;
  v3 = *((uint32_t *)dword_8F8528 + 626);
  if ( v3 == 15 )
  {
    v4 = sub_5424B0(this);
    if ( v4 != -1 && v4 < *(uint32_t *)(dword_9B8040 + 8) && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * v4) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 72))(this, v4);
      return 1;
    }
  }
  else if ( v3 == 2 )
  {
    v6 = (char *)dword_8F8528 + 2508;
    v7 = sub_432F00(0);
    if ( *v6 == 3 )
    {
      v8 = v6[2];
      if ( v8 < v7[2] )
      {
        v9 = *(uint32_t *)(v7[3] + 4 * v8);
        if ( v9 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 16))(v9) + 4) == v6[1] )
        {
          v10 = sub_5424B0(this);
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t))(*this + 64))(this, v6[2], v10, 0);
          return 1;
        }
      }
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x5425E0 CNRDPrivateStoreWindow_Display__vmt14 —— CNRDPrivateStoreWindow_Display__vmt14 关闭槽（5424B0 + 44BC30）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt14(uint32_t *this)
{
  int v2; // edi
  void *v3; // esi
  int v4; // eax
  int v5; // eax
  int v7; // [esp-8h] [ebp-14h]

  v2 = sub_5424B0(this);
  if ( v2 == -1 )
    return 0;
  if ( v2 >= *(uint32_t *)(dword_9B8040 + 8) )
    return 0;
  v3 = *(void **)(*(uint32_t *)(dword_9B8040 + 12) + 4 * v2);
  if ( v3 == nullptr )
    return 0;
  v4 = *(uint32_t *)(*(this + 2) + 2504);
  if ( v4 != 14 && v4 != 15 )
  {
    v7 = *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v3 + 16))(v3) + 68);
    v5 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v3 + 16))(v3);
    sub_44BC30((uint32_t *)*(this + 2), (void *)2, 10, *(uint32_t *)(v5 + 4), v2, v7, v3);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x542650 CNRDPrivateStoreWindow__vmt8 —— CNRDPrivateStoreWindow__vmt8 Update 槽（57 行：5424B0 + 44E8D0/44E850）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreWindow__vmt8(int this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // edi
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // edi
  int v11; // ebx

  v2 = *(uint32_t *)(*(uint32_t *)(this + 8) + 2504);
  if ( v2 == 1 )
    goto LABEL_12;
  if ( v2 == 2 )
    goto LABEL_12;
  v3 = *(uint32_t *)(this + 4);
  if ( *(uint8_t *)(v3 + 17) == 0 )
    goto LABEL_12;
  v4 = *(uint32_t *)(v3 + 12);
  if ( dword_79BE3C != v4 && dword_79BE34 != v4 && dword_79BE38 != v4 )
    goto LABEL_12;
  v5 = sub_5424B0((void *)this);
  if ( v5 != -1
    && ((v6 = *(uint32_t *)(this + 36), v5 >= *(uint32_t *)(v6 + 8))
      ? (v7 = 0)
      : (v7 = *(uint32_t *)(*(uint32_t *)(v6 + 12) + 4 * v5)),
        v8 = 32 * (v5 % 7) + 61,
        v9 = 32 * (v5 / 7) + 291,
        v10 = v8,
        v11 = v9,
        v7 != 0) )
  {
    if ( dword_9B88D0 != v7 || dword_795378 != 9 )
    {
      v9 = sub_44E8D0(*(char **)(this + 8), (void *)0x1A, v7, 9);
      if ( v9 != 0 )
        LOBYTE(v9) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v9 + 48))(v9, v10, v11, 28, 28);
    }
  }
  else
  {
LABEL_12:
    LOBYTE(v9) = dword_9B88D0;
    if ( dword_9B88D0 != 0 && dword_795378 == 9 )
      LOBYTE(v9) = sub_44E850(*(uint32_t **)(this + 8), 26);
  }
  return v9;
}



// ------------------------------------------------------------
// 0x542730 CNRDPrivateStoreWindow_Display__vmt8 —— CNRDPrivateStoreWindow_Display__vmt8 Update 槽（83 行：542310/542270 + 42FC00/44ABE0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt8(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // edi
  int i; // eax
  char *v9; // eax
  int result; // eax
  int v11; // eax

  CNRDPrivateStoreWindow__vmt8(this);
  if ( *(uint32_t *)(*(uint32_t *)(this + 60) + 12) == dword_79BE4C )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 16) != 0 )
    {
      sub_542310((uint32_t *)this);
    }
    else
    {
      CNCommandChecker__vmt40(0, 0);
      *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 8) + 28) + 136) + 17) = 0;
    }
  }
  else
  {
    v2 = **(uint32_t **)(this + 28);
    if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
      sub_542270((int *)this);
  }
  v3 = *(uint32_t *)(this + 56);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    v4 = *(uint32_t *)(this + 60);
    v5 = v4 + 160;
    if ( *(uint32_t *)(v4 + 192) != 0 )
      v5 = v4 + 180;
    if ( *(uint32_t *)(v5 + 12) == 0 || *(uint32_t *)(v4 + 192) != 0 && *(uint32_t *)(v4 + 188) != 0 )
    {
      v9 = sub_422E70(1334);
      return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v9, 0);
    }
    v6 = *(uint32_t *)(dword_9B8040 + 8);
    v7 = 0;
    for ( i = 0; i < 14; i += 2 )
    {
      if ( i < v6 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * i) != 0 )
        ++v7;
      if ( i + 1 < v6 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * i + 4) != 0 )
        ++v7;
    }
    if ( v7 == 0 )
    {
      v9 = sub_422E70(1350);
      return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v9, 0);
    }
    sub_42FC00((int *)dword_8F7C08, *(void **)(v5 + 8));
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 92))(this);
  }
  else
  {
    v11 = *(uint32_t *)(this + 40);
    if ( *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v11 + 12) )
    {
      return sub_44ABE0(dword_8F8528, 14);
    }
    else
    {
      result = *(uint32_t *)(this + 44);
      if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
        return sub_44ABE0(dword_8F8528, 15);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5428D0 CNRDPrivateStoreWindow_Sell__vmt8 —— CNRDPrivateStoreWindow_Sell__vmt8 Update 槽（转发 522C60）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow_Sell__vmt8(int *this)
{
  int result; // eax

  CNRDPrivateStoreWindow__vmt8((int)this);
  result = *(this + 10);
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
  {
    result = sub_522C60(*(uint32_t *)(*(this + 9) + 4));
    if ( (uint8_t)result == 0 )
      return (*(int (/*thiscall*/ **)(int *))(*this + 84))(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x542910 CNRDPrivateStoreWindow_Buy__vmt8 —— CNRDPrivateStoreWindow_Buy__vmt8 Update 槽（44ABE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreWindow_Buy__vmt8(uint32_t *this)
{
  int v2; // esi
  char result; // al

  CNRDPrivateStoreWindow__vmt8((int)this);
  v2 = *(this + 10);
  result = *(uint8_t *)(v2 + 17);
  if ( result != 0 )
  {
    result = dword_79BE34;
    if ( dword_79BE34 == *(uint32_t *)(v2 + 12) )
      return sub_44ABE0(dword_8F8528, 4);
  }
  return result;
}



// ------------------------------------------------------------
// 0x542940 sub_542940 —— 收购/出售子窗口公共辅助（23 行）
// ------------------------------------------------------------
char /*stdcall*/ sub_542940(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_542940(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x542980 sub_542980 —— 摊位条目操作（61 行：4F36B0 + 44E8D0）
// ------------------------------------------------------------
char /*cdecl*/ sub_542980(int a1)
{
  char v1; // bl
  int v2; // esi
  const char *p_Block; // eax
  const char *v4; // edx
  unsigned int v5; // eax
  char *v6; // edi
  char v7; // cl
  char *v8; // ecx
  unsigned int v9; // eax
  char *v10; // esi
  char *v11; // edi
  char v12; // cl
  char v14; // [esp+7h] [ebp-ADh] BYREF
  char v15[128]; // [esp+8h] [ebp-ACh] BYREF
  uint8_t v16[4]; // [esp+88h] [ebp-2Ch] BYREF
  void *Block; // [esp+8Ch] [ebp-28h] BYREF
  unsigned int v18; // [esp+A0h] [ebp-14h]
  int v19; // [esp+A4h] [ebp-10h]
  int v20; // [esp+B0h] [ebp-4h]

  v19 = dword_796E50;
  v1 = 0;
  v2 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) - a1;
  if ( v2 < 0 )
  {
    strcpy(v15, sub_422E70(952));
    sub_4F36B0(v16, -v2, 0, 0, 0);
    p_Block = (const char *)Block;
    v20 = 0;
    if ( v18 < 0x10 )
      p_Block = (const char *)&Block;
    v4 = p_Block;
    v5 = strlen(p_Block) + 1;
    v6 = &v14;
    do
      v7 = *++v6;
    while ( v7 != 0 );
    qmemcpy(v6, v4, v5);
    v8 = sub_422E70(953);
    v9 = strlen(v8) + 1;
    v10 = v8;
    v11 = &v14;
    do
      v12 = *++v11;
    while ( v12 != 0 );
    qmemcpy(v11, v10, v9);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v15, 0);
    v1 = 1;
    if ( v18 >= 0x10 )
      j__free(Block);
  }
  return v1;
}



// ------------------------------------------------------------
// 0x542AB0 sub_542AB0 —— 摊位数据释放（4BE520）
// ------------------------------------------------------------
int /*thiscall*/ sub_542AB0(void *this, char a2)
{
  void *v3; // [esp+0h] [ebp-4h] BYREF

  v3 = this;
  return *(uint32_t *)(*(uint32_t *)sub_4BE520(&v3, &a2) + 16);
}



// ------------------------------------------------------------
// 0x542AD0 sub_542AD0 —— 摊位页切换（44AB50 + 542940，60 行）
// ------------------------------------------------------------
int sub_542AD0()
{
  int v0; // ecx
  int v1; // eax
  int v2; // eax
  char *v3; // eax
  char *v5; // esi
  uint32_t *v6; // edi
  uint32_t *v7; // eax
  int v8; // esi
  int v9; // edi
  uint32_t *v10; // eax

  v0 = *(uint32_t *)dword_9B8038;
  v1 = 0;
  while ( v0 != *(uint32_t *)(dword_9B8034 + 4 * v1) )
  {
    if ( ++v1 >= 3 )
      goto LABEL_4;
  }
  if ( v1 == 2 )
  {
    v3 = sub_422E70(1336);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);
    return sub_44AB50(dword_8F8528, 1, 12);
  }
LABEL_4:
  v2 = 0;
  while ( v0 != *(uint32_t *)(dword_9B8034 + 4 * v2) )
  {
    if ( ++v2 >= 3 )
      return sub_44AB50(dword_8F8528, 1, 12);
  }
  if ( v2 == 1 )
  {
    v5 = (char *)dword_9B8044 + 4;
    v6 = dword_9B8044;
    sub_542940(*(void ***)(*((uint32_t *)dword_9B8044 + 1) + 4));
    *(uint32_t *)(*(uint32_t *)v5 + 4) = *(uint32_t *)v5;
    v7 = *(uint32_t **)v5;
    v6[2] = 0;
    *v7 = v7;
    *(uint32_t *)(*(uint32_t *)v5 + 8) = *(uint32_t *)v5;
    v8 = dword_9B8048 + 4;
    v9 = dword_9B8048;
    sub_542940(*(void ***)(*(uint32_t *)(dword_9B8048 + 4) + 4));
    *(uint32_t *)(*(uint32_t *)v8 + 4) = *(uint32_t *)v8;
    v10 = *(uint32_t **)v8;
    *(uint32_t *)(v9 + 8) = 0;
    *v10 = v10;
    *(uint32_t *)(*(uint32_t *)v8 + 8) = *(uint32_t *)v8;
  }
  return sub_44AB50(dword_8F8528, 1, 12);
}



// ------------------------------------------------------------
// 0x542BB0 CNRDPrivateStoreWindow__vmt4C —— CNRDPrivateStoreWindow__vmt4C 槽（542940 + 485020）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow__vmt4C(uint32_t *this)
{
  int v2; // eax
  int v3; // esi
  int v4; // edi
  uint32_t *v5; // eax
  int v6; // esi
  uint32_t *v7; // eax

  v2 = 0;
  while ( *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * v2) )
  {
    if ( ++v2 >= 3 )
      goto LABEL_7;
  }
  if ( v2 == 0 )
  {
    v3 = dword_9B8048 + 4;
    v4 = dword_9B8048;
    sub_542940(*(void ***)(*(uint32_t *)(dword_9B8048 + 4) + 4));
    *(uint32_t *)(*(uint32_t *)v3 + 4) = *(uint32_t *)v3;
    v5 = *(uint32_t **)v3;
    *(uint32_t *)(v4 + 8) = 0;
    *v5 = v5;
    *(uint32_t *)(*(uint32_t *)v3 + 8) = *(uint32_t *)v3;
  }
LABEL_7:
  v6 = *(this + 6);
  sub_542940(*(void ***)(*(uint32_t *)(v6 + 4) + 4));
  *(uint32_t *)(*(uint32_t *)(v6 + 4) + 4) = *(uint32_t *)(v6 + 4);
  v7 = *(uint32_t **)(v6 + 4);
  *(uint32_t *)(v6 + 8) = 0;
  *v7 = v7;
  *(uint32_t *)(*(uint32_t *)(v6 + 4) + 8) = *(uint32_t *)(v6 + 4);
  return sub_485020(*(this + 9));
}



// ------------------------------------------------------------
// 0x542C40 CNRDPrivateStoreWindow__vmt60 —— CNRDPrivateStoreWindow__vmt60 槽（4BE520 + 44E8D0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow__vmt60(int this, int a2, char a3)
{
  int v4; // eax
  int v5; // eax
  uint32_t v7[2]; // [esp+4h] [ebp-10h] BYREF
  uint8_t v8[4]; // [esp+Ch] [ebp-8h] BYREF
  int v9; // [esp+10h] [ebp-4h] BYREF

  v4 = *(uint32_t *)(this + 36);
  if ( a2 >= *(uint32_t *)(v4 + 8) )
    v9 = 0;
  else
    v9 = *(uint32_t *)(*(uint32_t *)(v4 + 12) + 4 * a2);
  v7[0] = &a2;
  v7[1] = &a3;
  v5 = sub_4BE520(v8, &v9);
  return sub_44E8D0(*(char **)(this + 8), (void *)0x41, (int)v7, *(uint32_t *)(*(uint32_t *)v5 + 16));
}



// ------------------------------------------------------------
// 0x542CA0 CNRDPrivateStoreWindow_Display__vmt40 —— CNRDPrivateStoreWindow_Display__vmt40 确认动作槽（88 行：544AC0 + 540DE0 重建）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt40(char **this, int a2, int a3, int a4)
{
  uint32_t *v5; // eax
  int v6; // ebx
  int v7; // ecx
  int *v8; // edi
  int v9; // esi
  int v10; // eax
  bool v11; // zf
  int result; // eax
  int v13; // esi
  int v14; // ecx
  int v15; // ebx
  int v16; // ebx
  char *v17; // eax
  uint8_t v18[4]; // [esp+Ch] [ebp-8h] BYREF
  char **v19; // [esp+10h] [ebp-4h]

  v19 = this;
  v5 = sub_432F00(a4);
  v6 = a2;
  if ( a2 < v5[2]
    && (v7 = v5[3], (v8 = *(int **)(v7 + 4 * a2)) != nullptr)
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*v8 + 80))(*(uint32_t *)(v7 + 4 * a2)) != 0 )
  {
    v9 = *v8;
    v10 = (*(int (/*thiscall*/ **)(int *))(*v8 + 16))(v8);
    v11 = (*(uint8_t (/*thiscall*/ **)(int *, uint32_t))(v9 + 60))(v8, *(uint32_t *)(v10 + 4)) == 0;
    result = dword_9B8040;
    if ( v11 )
    {
LABEL_11:
      if ( a3 >= *(uint32_t *)(result + 8) || *(uint32_t *)(*(uint32_t *)(result + 12) + 4 * a3) == 0 )
        return sub_544AC0(v6, a3, a4);
    }
    else
    {
      v13 = 0;
      while ( 1 )
      {
        if ( v13 < *(uint32_t *)(result + 8) )
        {
          v14 = *(uint32_t *)(*(uint32_t *)(result + 12) + 4 * v13);
          if ( v14 != 0 )
          {
            v15 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 16))(v14) + 4);
            v11 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*v8 + 16))(v8) + 4) == v15;
            result = dword_9B8040;
            if ( v11 )
              break;
          }
        }
        if ( ++v13 >= 14 )
        {
          v6 = a2;
          goto LABEL_11;
        }
      }
      if ( v13 >= *(uint32_t *)(dword_9B8040 + 8) )
        a3 = 0;
      else
        a3 = *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * v13);
      v16 = *(uint32_t *)(*(uint32_t *)sub_4BE520(v18, &a3) + 16);
      if ( (unsigned int)(*(int (/*thiscall*/ **)(int *))(*v8 + 44))(v8) <= 1 )
        return (*(int (/*thiscall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)dword_9B8038 + 60))(
                 *(uint32_t *)dword_9B8038,
                 a2,
                 v13,
                 a4,
                 v16,
                 1);
      else
        return sub_540DE0(*((int **)v19[2] + 29), 1, a4, a2, 5, v13, v16, 0);
    }
  }
  else
  {
    v17 = sub_422E70(422);
    return sub_44E8D0(*(this + 2), (void *)0x1B, (int)v17, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x542E10 CNRDPrivateStoreWindow_Display__vmt5C —— CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：423200/423290/423380 参数 + 69B740 输入）
// ------------------------------------------------------------
int /*fastcall*/ CNRDPrivateStoreWindow_Display__vmt5C(int a1)
{
  int v2; // edi
  const char *v3; // eax
  int v4; // esi
  char *v5; // eax
  int v6; // edx
  int v7; // ebx
  int i; // eax
  int v9; // eax
  int j; // edi
  int v11; // esi
  int v12; // ebx
  int v13; // eax
  int v14; // esi
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  uint8_t v19[4]; // [esp+Ch] [ebp-20h] BYREF
  uint8_t v20[4]; // [esp+10h] [ebp-1Ch] BYREF
  uint8_t v21[4]; // [esp+14h] [ebp-18h] BYREF
  uint8_t v22[4]; // [esp+18h] [ebp-14h] BYREF
  uint32_t v23[2]; // [esp+1Ch] [ebp-10h] BYREF
  int v24; // [esp+24h] [ebp-8h] BYREF
  uint8_t v25[4]; // [esp+28h] [ebp-4h] BYREF

  v23[1] = a1;
  sub_423200(dword_8F7B08, 90);
  v2 = dword_8F7B08;
  v3 = (const char *)sub_69B740(*(uint32_t *)(a1 + 60));
  v4 = (int)v3;
  if ( v3 != nullptr )
  {
    v24 = strlen(v3);
    sub_423290(v2, (int)&v24, 4);
    sub_423290(v2, v4, v24);
  }
  v5 = (char *)sub_69B740(*(uint32_t *)(a1 + 60));
  off_77F3FC(v5);
  v6 = *(uint32_t *)(dword_9B8040 + 8);
  v7 = 0;
  for ( i = 0; i < 14; i += 2 )
  {
    if ( i < v6 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * i) != 0 )
      ++v7;
    if ( i + 1 < v6 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * i + 4) != 0 )
      ++v7;
  }
  v25[0] = v7;
  sub_423290(dword_8F7B08, (int)v25, 1);
  off_77F3FC("%d", v7);
  v9 = dword_9B8040;
  for ( j = 0; j < 14; ++j )
  {
    if ( j < *(uint32_t *)(v9 + 8) )
    {
      v24 = *(uint32_t *)(*(uint32_t *)(v9 + 12) + 4 * j);
      v11 = v24;
      if ( v24 != 0 )
      {
        v23[0] = j;
        sub_423290(dword_8F7B08, (int)v23, 2);
        v23[0] = *(uint32_t *)(*(uint32_t *)sub_4BE520(v22, &v24) + 16);
        sub_423290(dword_8F7B08, (int)v23, 4);
        v25[0] = 0;
        sub_423290(dword_8F7B08, (int)v25, 1);
        v23[0] = *(uint16_t *)(*(uint32_t *)sub_4BE520(v21, &v24) + 16);
        sub_423290(dword_8F7B08, (int)v23, 2);
        v12 = *(uint32_t *)v11;
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11);
        if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(v12 + 60))(v11, *(uint32_t *)(v13 + 4)) != 0 )
        {
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 44))(v11);
        }
        else if ( (**(int (/*thiscall*/ ***)(int))v11)(v11) == 2 )
        {
          v14 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 188))(v11);
        }
        else
        {
          v14 = 0;
        }
        v23[0] = v14;
        sub_423290(dword_8F7B08, (int)v23, 4);
        v15 = sub_4BE520(v20, &v24);
        v16 = sub_4BE520(v19, &v24);
        off_77F3FC("%d, %d, %d, %d", j, *(uint32_t *)(*(uint32_t *)v16 + 16), *(uint32_t *)(*(uint32_t *)v15 + 16), v14);
        v9 = dword_9B8040;
      }
    }
  }
  v17 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));
  off_77F3FC("money : %d", v17);
  sub_423380(dword_8F7B08);
  return sub_44ABF0(dword_8F8528);
}



// ------------------------------------------------------------
// 0x543060 CNRDPrivateStoreWindow_Buy__vmt1C —— CNRDPrivateStoreWindow_Buy__vmt1C 刷新槽（46 行：522C60/542980/540DE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreWindow_Buy__vmt1C(uint32_t *this)
{
  int v2; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  uint8_t v10[4]; // [esp+4h] [ebp-8h] BYREF
  int v11; // [esp+8h] [ebp-4h] BYREF

  v2 = *(this + 1);
  if ( *(uint8_t *)(v2 + 17) == 0 || dword_79BE34 != *(uint32_t *)(v2 + 12) )
    return 0;
  v4 = *(uint32_t *)(*(this + 2) + 2504);
  if ( v4 != 4 && v4 != 0 )
    return 0;
  v5 = sub_5424B0(this);
  if ( v5 == -1 )
    return 0;
  v6 = *(this + 9);
  if ( v5 >= *(uint32_t *)(v6 + 8) )
    return 0;
  v11 = *(uint32_t *)(*(uint32_t *)(v6 + 12) + 4 * v5);
  v7 = v11;
  if ( v11 == 0 )
    return 0;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11);
  if ( (uint8_t)sub_522C60(*(uint32_t *)(v8 + 56)) != 0 )
    return 0;
  v9 = sub_4BE520(v10, &v11);
  if ( sub_542980(*(uint32_t *)(*(uint32_t *)v9 + 16)) != 0 )
    return 0;
  if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 44))(v7) <= 1 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 96))(this, v5, 1);
  else
    sub_540DE0(*(int **)(*(this + 2) + 116), 2, 5, v5, 7, 0, 0, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x543150 CNRDPrivateStoreWindow_Buy__vmt10 —— CNRDPrivateStoreWindow_Buy__vmt10 状态切换槽（转发 542940）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow_Buy__vmt10(uint32_t *this)
{
  int v2; // esi
  uint32_t *v3; // eax

  CNRDPrivateStoreWindow__vmt10(this);
  v2 = *(this + 6);
  sub_542940(*(void ***)(*(uint32_t *)(v2 + 4) + 4));
  *(uint32_t *)(*(uint32_t *)(v2 + 4) + 4) = *(uint32_t *)(v2 + 4);
  v3 = *(uint32_t **)(v2 + 4);
  *(uint32_t *)(v2 + 8) = 0;
  *v3 = v3;
  *(uint32_t *)(*(uint32_t *)(v2 + 4) + 8) = *(uint32_t *)(v2 + 4);
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
}



// ------------------------------------------------------------
// 0x543190 CNRDPrivateStoreWindow_Display__vmt68 —— CNRDPrivateStoreWindow_Display__vmt68 页绘制（114 行：43C250/69A5F0/43C410/43C060 + 69BCC0/402AE0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt68(int this)
{
  uint32_t *v2; // ecx
  int v3; // ebx
  uint8_t *v4; // eax
  uint8_t *v5; // eax
  uint8_t *v6; // eax
  uint8_t *v7; // eax
  uint8_t *v8; // eax
  uint8_t *v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  uint32_t *v14; // eax
  uint32_t *v15; // eax
  uint32_t *v16; // eax
  uint32_t *v17; // eax
  void *v18; // eax
  int v19; // eax
  char *v20; // ebx
  int result; // eax
  int v22; // [esp+10h] [ebp-14h]
  int v23; // [esp+14h] [ebp-10h]

  v2 = *(uint32_t **)(this + 4);
  v22 = v2[5];
  v23 = v2[6];
  sub_69A5F0(v2, 0, 0);
  v3 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 204);
  v4 = operator new(0x6Cu);
  if ( v4 != nullptr )
    v5 = sub_43C250(v4, v3, 2);
  else
    v5 = nullptr;
  **(uint32_t **)(this + 28) = v5;
  v6 = operator new(0x6Cu);
  if ( v6 != nullptr )
    v7 = sub_43C250(v6, v3, 4);
  else
    v7 = nullptr;
  *(uint32_t *)(*(uint32_t *)(this + 28) + 4) = v7;
  v8 = operator new(0x6Cu);
  if ( v8 != nullptr )
    v9 = sub_43C250(v8, v3, 6);
  else
    v9 = nullptr;
  *(uint32_t *)(*(uint32_t *)(this + 28) + 8) = v9;
  sub_69A5F0(**(uint32_t ***)(this + 28), 105, 59);
  sub_69A5F0(*(uint32_t **)(*(uint32_t *)(this + 28) + 4), 101, 189);
  sub_69A5F0(*(uint32_t **)(*(uint32_t *)(this + 28) + 8), 58, 224);
  sub_69A840(**(uint32_t **)(this + 28));
  sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 4));
  sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 8));
  v10 = operator new(0x84u);
  if ( v10 != nullptr )
    v11 = sub_43C410(v10, v3, 20, 21, 22, 23, 0, 0);
  else
    v11 = nullptr;
  *(uint32_t *)(this + 56) = v11;
  sub_69A5F0(v11, 64, 230);
  sub_69A840(*(uint32_t *)(this + 56));
  v12 = operator new(0x84u);
  if ( v12 != nullptr )
    v13 = sub_43C410(v12, v3, 24, 25, 26, 27, 0, 0);
  else
    v13 = nullptr;
  *(uint32_t *)(this + 52) = v13;
  sub_69A5F0(v13, 150, 230);
  *(uint8_t *)(*(uint32_t *)(this + 52) + 17) = 0;
  sub_69A840(*(uint32_t *)(this + 52));
  v14 = operator new(0x84u);
  if ( v14 != nullptr )
    v15 = sub_43C410(v14, v3, 12, 13, 14, 15, 0, 0);
  else
    v15 = nullptr;
  *(uint32_t *)(this + 40) = v15;
  sub_69A5F0(v15, 107, 192);
  sub_69A840(*(uint32_t *)(this + 40));
  v16 = operator new(0x84u);
  if ( v16 != nullptr )
    v17 = sub_43C410(v16, v3, 16, 17, 18, 19, 0, 0);
  else
    v17 = nullptr;
  *(uint32_t *)(this + 44) = v17;
  sub_69A5F0(v17, 149, 192);
  sub_69A840(*(uint32_t *)(this + 44));
  v18 = operator new(0xE4u);
  if ( v18 != nullptr )
    v19 = sub_43C060((int)v18, 39, 140);
  else
    v19 = 0;
  *(uint32_t *)(this + 60) = v19;
  dword_9D3BD8 = dword_99FCCC;
  sub_69A5F0(*(uint32_t **)(this + 60), 110, 66);
  v20 = sub_422E70(1334);
  sub_69BCC0(*(uint32_t *)(this + 60));
  sub_402AE0(v20);
  sub_69A840(*(uint32_t *)(this + 60));
  sub_69A5F0(*(uint32_t **)(this + 4), v22, v23);
  if ( *(uint32_t *)dword_9B8034 != 0 )
    off_77F3FC("Another private shop created!");
  result = dword_9B8034;
  *(uint32_t *)dword_9B8034 = this;
  *(uint32_t *)(this + 36) = dword_9B8040;
  *(uint32_t *)(this + 24) = dword_9B8044;
  return result;
}



// ------------------------------------------------------------
// 0x5434F0 CNRDPrivateStoreWindow_Sell__vmt68 —— CNRDPrivateStoreWindow_Sell__vmt68 页绘制（80 行：43C250/69A5F0/69A840/43C410）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow_Sell__vmt68(int this)
{
  uint32_t *v2; // ecx
  int v3; // edi
  uint8_t *v4; // eax
  uint8_t *v5; // eax
  uint8_t *v6; // eax
  uint8_t *v7; // eax
  uint8_t *v8; // eax
  uint8_t *v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  int result; // eax
  int v15; // [esp+Ch] [ebp-14h]
  int v16; // [esp+10h] [ebp-10h]

  v2 = *(uint32_t **)(this + 4);
  v15 = v2[5];
  v16 = v2[6];
  sub_69A5F0(v2, 0, 0);
  v3 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 204);
  v4 = operator new(0x6Cu);
  if ( v4 != nullptr )
    v5 = sub_43C250(v4, v3, 2);
  else
    v5 = nullptr;
  **(uint32_t **)(this + 28) = v5;
  v6 = operator new(0x6Cu);
  if ( v6 != nullptr )
    v7 = sub_43C250(v6, v3, 3);
  else
    v7 = nullptr;
  *(uint32_t *)(*(uint32_t *)(this + 28) + 4) = v7;
  v8 = operator new(0x6Cu);
  if ( v8 != nullptr )
    v9 = sub_43C250(v8, v3, 6);
  else
    v9 = nullptr;
  *(uint32_t *)(*(uint32_t *)(this + 28) + 8) = v9;
  sub_69A5F0(**(uint32_t ***)(this + 28), 105, 59);
  sub_69A5F0(*(uint32_t **)(*(uint32_t *)(this + 28) + 4), 101, 189);
  sub_69A5F0(*(uint32_t **)(*(uint32_t *)(this + 28) + 8), 58, 224);
  *(uint8_t *)(**(uint32_t **)(this + 28) + 16) = 0;
  sub_69A840(**(uint32_t **)(this + 28));
  sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 4));
  sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 8));
  v10 = operator new(0x84u);
  if ( v10 != nullptr )
    v11 = sub_43C410(v10, v3, 20, 21, 22, 23, 0, 0);
  else
    v11 = nullptr;
  *(uint32_t *)(this + 44) = v11;
  sub_69A5F0(v11, 64, 230);
  *(uint8_t *)(*(uint32_t *)(this + 44) + 17) = 0;
  sub_69A840(*(uint32_t *)(this + 44));
  v12 = operator new(0x84u);
  if ( v12 != nullptr )
    v13 = sub_43C410(v12, v3, 24, 25, 26, 27, 0, 0);
  else
    v13 = nullptr;
  *(uint32_t *)(this + 40) = v13;
  sub_69A5F0(v13, 150, 230);
  sub_69A840(*(uint32_t *)(this + 40));
  sub_69A5F0(*(uint32_t **)(this + 4), v15, v16);
  if ( *(uint32_t *)(dword_9B8034 + 4) != 0 )
    off_77F3FC("Another private shop created!");
  *(uint32_t *)(dword_9B8034 + 4) = this;
  result = dword_9B8040;
  *(uint32_t *)(this + 36) = dword_9B8040;
  *(uint32_t *)(this + 24) = dword_9B8044;
  return result;
}



// ------------------------------------------------------------
// 0x543740 sub_543740 —— 摊位标题/描述文本（4015C0/401740 + 5648C0/433130/4296E0，113 行）
// ------------------------------------------------------------
int */*thiscall*/ sub_543740(int **this, int *a2, char a3, int *a4, int a5)
{
  int v6; // ecx
  int *v7; // eax
  int *v8; // eax
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
  int v21; // [esp+70h] [ebp+14h]

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
  v6 = sub_5648C0(*(this + 1), a4, *(this + 1), a5, 0);
  v7 = *(this + 1);
  v21 = v6;
  *(this + 2) = (int *)((char *)*(this + 2) + 1);
  if ( a4 == v7 )
  {
    v7[1] = v6;
    **(this + 1) = v6;
    (*(this + 1))[2] = v6;
  }
  else if ( a3 != 0 )
  {
    *a4 = v6;
    v8 = *(this + 1);
    if ( a4 == (int *)*v8 )
      *v8 = v6;
  }
  else
  {
    a4[2] = v6;
    v9 = (int)*(this + 1);
    if ( a4 == *(int **)(v9 + 8) )
      *(uint32_t *)(v9 + 8) = v6;
  }
  v10 = (int *)(v6 + 4);
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
  *(uint8_t *)((*(this + 1))[1] + 20) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x5438F0 sub_5438F0 —— 摊位登记文本构建（218 行：41C5E0 + 52E300/542490/433130/4296E0）
// ------------------------------------------------------------
int ***/*thiscall*/ sub_5438F0(uint32_t *this, int ***a2, int **a3)
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
  if ( *((uint8_t *)a3 + 21) != 0 )
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
  sub_41C5E0(&a3);
  if ( *((uint8_t *)*v3 + 21) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
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
      if ( *((uint8_t *)v4 + 21) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_52E300(v4);
        v7 = v25;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_542490(v4);
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
  v14 = *((uint8_t *)v5 + 20);
  *((uint8_t *)v5 + 20) = *((uint8_t *)v3 + 20);
  *((uint8_t *)v3 + 20) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 20) == 1 )
  {
    v15 = v25;
    if ( v4 != *(int **)(v25[1] + 4) )
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
            v15 = v25;
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
            v15 = v25;
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
  v17 = v25[2];
  if ( v17 != 0 )
    v25[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x543BB0 CNRDPrivateStoreWindow__vmt0 —— CNRDPrivateStoreWindow__vmt0 构造（220 行：45E680 物品枚举 + 4BD630/4BD650 + 5515A0 + 5424B0；尾缀登记单例 dword_9B8034）
// ------------------------------------------------------------
// 日志证据："Another private shop created!"——本窗口成为当前摆摊单例。
char /*userpurge*/ sub_543BB0@<al>(uint32_t *a1@<ecx>, int a2@<esi>, int a3)
{
  int v3; // eax
  int v4; // ebx
  int v6; // ecx
  int v7; // eax
  int v8; // edx
  int v9; // esi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // esi
  int v14; // eax
  char *v15; // eax
  char *v16; // esi
  int v17; // edx
  int v18; // esi
  int v19; // ebx
  uint32_t *v20; // ecx
  int v21; // esi
  char *v22; // eax
  uint32_t *v23; // eax
  unsigned int v24; // eax
  size_t *v25; // eax
  size_t *v26; // eax
  int v27; // edx
  int v28; // esi
  int v29; // ebx
  uint32_t *v30; // ecx
  int i; // esi
  int v32; // eax
  int v33; // ecx
  int v35; // [esp-Ch] [ebp-9Ch]
  uint8_t v37[28]; // [esp+8h] [ebp-88h] BYREF
  uint8_t v38[28]; // [esp+24h] [ebp-6Ch] BYREF
  uint8_t v39[4]; // [esp+40h] [ebp-50h] BYREF
  uint32_t v40[6]; // [esp+44h] [ebp-4Ch] BYREF
  size_t v41; // [esp+5Ch] [ebp-34h] BYREF
  uint32_t v42[5]; // [esp+60h] [ebp-30h] BYREF
  unsigned int v43; // [esp+74h] [ebp-1Ch]
  uint8_t Buffer[5]; // [esp+78h] [ebp-18h] BYREF
  char v45; // [esp+7Dh] [ebp-13h]
  int v46; // [esp+80h] [ebp-10h]
  int v47; // [esp+8Ch] [ebp-4h]

  LOBYTE(v3) = dword_796E50;
  v4 = a3;
  v46 = dword_796E50;
  if ( a3 == a1[1] )
  {
    v6 = a1[5];
    if ( v6 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(
        v6,
        *(uint32_t *)(a3 + 20) + 28,
        *(uint32_t *)(a3 + 24) + 29,
        dword_79C0B0);
      v4 = a3;
    }
    else
    {
      a1[5] = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 204), 1u);
    }
    if ( a1[4] == 0 )
    {
      v7 = 0;
      while ( *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * v7) )
      {
        if ( ++v7 >= 3 )
          goto LABEL_11;
      }
      if ( v7 != 1 )
      {
LABEL_11:
        if ( sub_541A40() != 0 )
          goto LABEL_13;
      }
      a1[4] = dword_8F7C08;
    }
LABEL_13:
    if ( a1[4] != 0 && a1[5] != 0 && (uint8_t)sub_45E680(a1[4]) != 0 )
    {
      v8 = *(uint32_t *)(v4 + 20) + 28;
      v9 = *(uint32_t *)(v4 + 24) + 29;
      v10 = a1[5];
      v35 = *(uint32_t *)(v10 + 24);
      *(uint32_t *)Buffer = *(uint32_t *)(v10 + 20);
      (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)a1[4] + 384))(
        a1[4],
        v8,
        v9,
        *(uint32_t *)Buffer,
        v35,
        1065353216);
      v4 = a3;
    }
    if ( a1[4] != 0 )
    {
      v11 = 0;
      while ( *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * v11) )
      {
        if ( ++v11 >= 3 )
          goto LABEL_23;
      }
      if ( v11 == 0 )
        goto LABEL_30;
LABEL_23:
      if ( (uint8_t)sub_45E680(a1[4]) != 0 )
      {
        v12 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)a1[4] + 52))(a1[4], a2);
        v13 = sub_429830(v12);
        memset(Buffer, 0, sizeof(Buffer));
        v45 = 0;
        sub_401710((int)v39, "Lv.");
        v47 = 0;
        v14 = sub_41A5E0(v13 + 53);
        v15 = _itoa(v14, Buffer, 10);
        sub_402410((std::_String_base *)v39, v15);
        sub_402410((std::_String_base *)v39, " ");
        if ( *(uint32_t *)(v13 + 40) < 0x10u )
          v16 = (char *)(v13 + 20);
        else
          v16 = *(char **)(v13 + 20);
        sub_402410((std::_String_base *)v39, v16);
        v17 = a1[7];
        v18 = *(uint32_t *)(*(uint32_t *)v17 + 20) + 10;
        v19 = *(uint32_t *)(*(uint32_t *)v17 + 24) - 20;
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_77F8FC);
        v20 = (uint32_t *)v40[0];
        if ( v40[5] < 0x10u )
          v20 = v40;
        (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v18,
          v19,
          -1,
          v20);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        v47 = -1;
        sub_501490(v39);
        v4 = a3;
      }
    }
LABEL_30:
    v21 = a1[4];
    if ( v21 != 0 && *(uint32_t *)(v21 + 648) != 0 && sub_541A40() != 0 && (uint8_t)sub_45E680(v21) != 0 )
    {
      v22 = (char *)sub_4BD630(*(uint32_t **)(a1[4] + 648));
      sub_401710((int)&v41, v22);
      v47 = 1;
      if ( v42[4] > 0x18u )
      {
        v23 = (uint32_t *)v42[0];
        if ( v43 < 0x10 )
          v23 = v42;
        v24 = sub_5515A0(v23, 24);
        v25 = (size_t *)sub_4BD650(&v41, (int)v37, 0, v24);
        LOBYTE(v47) = 2;
        v26 = (size_t *)sub_4E70B0((int)v38, v25, "...");
        LOBYTE(v47) = 3;
        sub_4014D0(&v41, v26, 0, 0xFFFFFFFF);
        sub_501490(v38);
        LOBYTE(v47) = 1;
        sub_501490(v37);
      }
      v27 = a1[7];
      v28 = *(uint32_t *)(*(uint32_t *)v27 + 20) + 10;
      v29 = *(uint32_t *)(*(uint32_t *)v27 + 24) + 10;
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_77F8FC);
      v30 = (uint32_t *)v42[0];
      if ( v43 < 0x10 )
        v30 = v42;
      (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v28,
        v29,
        -1,
        v30);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v47 = -1;
      sub_501490(&v41);
      v4 = a3;
    }
    for ( i = 0; i < 14; ++i )
    {
      v32 = a1[9];
      if ( i < *(uint32_t *)(v32 + 8) )
      {
        v33 = *(uint32_t *)(*(uint32_t *)(v32 + 12) + 4 * i);
        if ( v33 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, uint32_t, int))(*(uint32_t *)v33 + 8))(
            v33,
            32 * (i % 7u) + 61,
            32 * (i / 7u) + 291,
            0,
            1);
          v4 = a3;
        }
      }
    }
    LOBYTE(v3) = *(uint8_t *)(v4 + 17);
    if ( (uint8_t)v3 != 0
      && (dword_79BE3C == *(uint32_t *)(v4 + 12)
       || dword_79BE34 == *(uint32_t *)(v4 + 12)
       || dword_79BE38 == *(uint32_t *)(v4 + 12)) )
    {
      v3 = sub_5424B0(a1);
      if ( v3 != -1 )
        LOBYTE(v3) = sub_4F2E40(32 * (v3 % 7) + 61, 32 * (v3 / 7) + 291);
    }
  }
  return v3;
}


// ------------------------------------------------------------
// 0x543FD0 sub_543FD0 —— 摊位确认流程 1（543740 文本 + 4A3B30）
// ------------------------------------------------------------
int /*thiscall*/ sub_543FD0(int **this, int a2, int *a3)
{
  int *v3; // ebx
  int *v5; // esi
  int v6; // eax
  bool v7; // cl
  unsigned int v8; // edx
  int *v9; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  v3 = a3;
  v5 = *(this + 1);
  v6 = v5[1];
  v7 = true;
  v13 = 1;
  if ( *(uint8_t *)(v6 + 21) == 0 )
  {
    v8 = *a3;
    do
    {
      v7 = v8 < *(uint32_t *)(v6 + 12);
      v5 = (int *)v6;
      v13 = v7;
      if ( v8 >= *(uint32_t *)(v6 + 12) )
        v6 = *(uint32_t *)(v6 + 8);
      else
        v6 = *(uint32_t *)v6;
    }
    while ( *(uint8_t *)(v6 + 21) == 0 );
  }
  v9 = v5;
  a3 = v5;
  if ( v7 )
  {
    if ( v5 == (int *)**(this + 1) )
    {
      v10 = *sub_543740(this, (int *)&a3, 1, v5, (int)v3);
      *(uint8_t *)(a2 + 4) = 1;
      *(uint32_t *)a2 = v10;
      return a2;
    }
    sub_4A3B30(&a3);
    v9 = a3;
  }
  if ( v9[3] >= (unsigned int)*v3 )
  {
    *(uint8_t *)(a2 + 4) = 0;
    *(uint32_t *)a2 = v9;
    return a2;
  }
  else
  {
    v12 = *sub_543740(this, (int *)&a3, v13, v5, (int)v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x544090 sub_544090 —— 摊位确认流程 2（542940 + 5438F0 文本）
// ------------------------------------------------------------
int */*thiscall*/ sub_544090(int **this, int *a2, int a3, int a4)
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
    sub_542940(*(void ***)(v7 + 4));
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
        sub_5438F0(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x544150 CNRDPrivateStoreWindow__vmt38 —— CNRDPrivateStoreWindow__vmt38 确认动作槽（522300 + 543FD0 + 484F40）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow__vmt38(int ***this, int a2, int a3, void *a4, int a5, int a6, int a7)
{
  int v8; // edi
  int **v9; // ecx
  uint8_t v11[8]; // [esp+8h] [ebp-10h] BYREF
  int v12[2]; // [esp+10h] [ebp-8h] BYREF

  v8 = sub_522300(a4, a5, a6, 0, a7, 1);
  v12[1] = a3;
  v9 = *(this + 6);
  v12[0] = v8;
  sub_543FD0(v9, (int)v11, v12);
  return sub_484F40(a2, v8, 1);
}



// ------------------------------------------------------------
// 0x5441B0 sub_5441B0 —— 摊位确认动作实现（614180 + 41C5E0 + 544090，32 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5441B0(int **this, uint32_t *a2)
{
  int v3; // eax
  int v4; // edi
  int v5; // esi
  uint32_t *v7; // [esp+Ch] [ebp-8h] BYREF
  int v8; // [esp+10h] [ebp-4h]

  sub_614180(this, &v7, a2);
  v3 = (int)v7;
  v4 = v8;
  v5 = 0;
  a2 = v7;
  if ( v7 != (uint32_t *)v8 )
  {
    do
    {
      ++v5;
      sub_41C5E0(&a2);
    }
    while ( a2 != (uint32_t *)v4 );
    v3 = (int)v7;
  }
  sub_544090(this, (int *)&a2, v3, v4);
  return v5;
}



// ------------------------------------------------------------
// 0x544210 sub_544210 —— 摊位确认转发（544090）
// ------------------------------------------------------------
int /*thiscall*/ sub_544210(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_544090((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x544250 CNRDPrivateStoreWindow__vmt68 —— CNRDPrivateStoreWindow__vmt68 页绘制（93 行：43C250/69A5F0 + 4354D0/433AC0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDPrivateStoreWindow__vmt68(uint32_t *this)
{
  int v1; // ebx
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  void *v5; // eax
  uint32_t *v6; // ecx
  uint32_t *result; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // esi
  uint32_t *v10; // eax
  int v11; // esi
  uint32_t *v12; // eax

  v1 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 204);
  v3 = operator new(0x6Cu);
  if ( v3 != nullptr )
    v4 = sub_43C250(v3, v1, 0);
  else
    v4 = nullptr;
  *(this + 1) = v4;
  *((uint32_t *)v4 + 17) = this;
  v5 = operator new(0xCu);
  v6 = (uint32_t *)*(this + 1);
  *(this + 7) = v5;
  result = sub_69A5F0(v6, 29, 168);
  if ( dword_9B8034 == 0 )
  {
    result = operator new(0xCu);
    dword_9B8034 = (int)result;
    *result = 0;
    *(uint32_t *)(dword_9B8034 + 4) = 0;
    *(uint32_t *)(dword_9B8034 + 8) = 0;
  }
  if ( dword_9B8040 == 0 )
  {
    v8 = operator new(0x20u);
    if ( v8 != nullptr )
      result = sub_4354D0(v8, (void *)5, 14);
    else
      result = nullptr;
    dword_9B8040 = (int)result;
  }
  if ( dword_9B8044 == nullptr )
  {
    result = operator new(0xCu);
    v9 = result;
    if ( result != nullptr )
    {
      v10 = sub_433AC0();
      v9[1] = v10;
      *((uint8_t *)v10 + 21) = 1;
      *(uint32_t *)(v9[1] + 4) = v9[1];
      *(uint32_t *)v9[1] = v9[1];
      result = (uint32_t *)v9[1];
      result[2] = result;
      v9[2] = 0;
    }
    else
    {
      v9 = nullptr;
    }
    dword_9B8044 = v9;
  }
  if ( dword_9B8048 == 0 )
  {
    result = operator new(0xCu);
    v11 = (int)result;
    if ( result != nullptr )
    {
      v12 = sub_433AC0();
      *(uint32_t *)(v11 + 4) = v12;
      *((uint8_t *)v12 + 21) = 1;
      *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) = *(uint32_t *)(v11 + 4);
      **(uint32_t **)(v11 + 4) = *(uint32_t *)(v11 + 4);
      result = *(uint32_t **)(v11 + 4);
      result[2] = result;
      *(uint32_t *)(v11 + 8) = 0;
    }
    else
    {
      v11 = 0;
    }
    dword_9B8048 = v11;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5443F0 CNRDPrivateStoreWindow__vmt44 —— CNRDPrivateStoreWindow__vmt44 槽（484880 + 5441B0 + 4850B0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow__vmt44(int this, int a2, int a3)
{
  int result; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // eax
  int *v8; // [esp+4h] [ebp-4h] BYREF

  result = a2;
  v5 = *(uint32_t *)(this + 36);
  if ( a2 < *(uint32_t *)(v5 + 8) )
  {
    v8 = *(int **)(*(uint32_t *)(v5 + 12) + 4 * a2);
    if ( v8 != nullptr )
    {
      sub_484880(6);
      v6 = *v8;
      v7 = (*(int (/*thiscall*/ **)(int *))(*v8 + 16))(v8);
      if ( (*(uint8_t (/*thiscall*/ **)(int *, uint32_t))(v6 + 60))(v8, *(uint32_t *)(v7 + 4)) == 0
        || (*(int (/*thiscall*/ **)(int *))(*v8 + 44))(v8) == a3 )
      {
        sub_5441B0(*(int ***)(this + 24), &v8);
      }
      return sub_4850B0(a2, a3);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x544460 CNRDPrivateStoreWindow_Display__vmt3C —— CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行：4BE520 + 484880/485330 + 543FD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt3C(uint32_t *this, unsigned int a2, int a3, int a4, int64_t a5)
{
  int v5; // ebx
  int v6; // eax
  int v7; // edi
  int v8; // esi
  uint64_t v9; // rax
  char *v10; // eax
  int result; // eax
  uint32_t *v12; // eax
  int v13; // ecx
  int v14; // ecx
  unsigned int v15; // edi
  int **v16; // ecx
  uint64_t v17; // [esp+Ch] [ebp-18h] BYREF
  uint8_t v18[4]; // [esp+14h] [ebp-10h] BYREF
  uint8_t v19[4]; // [esp+18h] [ebp-Ch] BYREF
  int v20; // [esp+1Ch] [ebp-8h] BYREF
  uint32_t *v21; // [esp+20h] [ebp-4h]

  v5 = 0;
  v21 = this;
  v17 = 0;
  do
  {
    v6 = *(this + 9);
    if ( v5 < *(uint32_t *)(v6 + 8) )
    {
      v20 = *(uint32_t *)(*(uint32_t *)(v6 + 12) + 4 * v5);
      v7 = v20;
      if ( v20 != 0 )
      {
        v8 = *(uint32_t *)sub_4BE520(v19, &v20) + 12;
        v17 += (unsigned int)(*(uint32_t *)(v8 + 4) * (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 44))(v7));
        this = v21;
      }
    }
    ++v5;
  }
  while ( v5 < 14 );
  v9 = v17 + (int)a5 * (int64_t)SHIDWORD(a5);
  HIDWORD(v17) = HIDWORD(v9);
  if ( v9 <= 0x7FFFFFFF )
  {
    v12 = sub_432F00(a4);
    v13 = v12[5];
    if ( v13 == 0 || (result = (v12[6] - v13) >> 2) <= 0 )
    {
      v14 = *(uint32_t *)(dword_9B8040 + 20);
      if ( v14 == 0 || (result = (*(uint32_t *)(dword_9B8040 + 24) - v14) >> 2) <= 0 )
      {
        sub_484880(6);
        sub_484880(6);
        sub_485330(a2, HIDWORD(a5), dword_9B8040, a3);
        if ( a3 >= *(uint32_t *)(dword_9B8040 + 8) )
          v15 = 0;
        else
          v15 = *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * a3);
        v16 = (int **)v21[6];
        v17 = __PAIR64__(a5, v15);
        sub_543FD0(v16, (int)v18, (int *)&v17);
        v17 = __PAIR64__(a2, v15);
        return sub_543FD0((int **)dword_9B8048, (int)v18, (int *)&v17);
      }
    }
  }
  else
  {
    v10 = sub_422E70(1356);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v10, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5445E0 CNRDPrivateStoreWindow_Display__vmt48 —— CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520/4F2D40 + 484880/5441B0/485330）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt48(int ***this, int a2)
{
  int v2; // edx
  int v3; // edi
  bool v4; // bl
  int v5; // eax
  uint32_t *v6; // esi
  int v7; // ecx
  int result; // eax
  int v9; // ecx
  int v10; // edi
  int v11; // [esp+Ch] [ebp-Ch] BYREF
  int ***v12; // [esp+10h] [ebp-8h]
  int v13; // [esp+14h] [ebp-4h] BYREF

  v2 = *(uint32_t *)(dword_9B8040 + 8);
  v12 = this;
  if ( a2 >= v2 )
    v3 = 0;
  else
    v3 = *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * a2);
  v13 = v3;
  v4 = false;
  v11 = *(uint32_t *)(*(uint32_t *)sub_4BE520(&v11, &v13) + 16);
  if ( v3 != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 16))(v3);
    if ( sub_4F2D40(*(uint32_t *)(v5 + 4)) == 2 )
      v4 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 172))(v3) <= 7;
  }
  v6 = dword_8F852C;
  if ( v4 )
    v6 = dword_8F8534;
  v7 = v6[5];
  if ( v7 == 0 || (result = (v6[6] - v7) >> 2) <= 0 )
  {
    v9 = *(uint32_t *)(dword_9B8040 + 20);
    if ( v9 == 0 || (result = (*(uint32_t *)(dword_9B8040 + 24) - v9) >> 2) <= 0 )
    {
      sub_484880(6);
      sub_484880(6);
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 44))(v3);
      sub_5441B0(v12[6], &v13);
      sub_5441B0((int **)dword_9B8048, &v13);
      return sub_485330(a2, v10, v6, v11);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5446F0 CNRDPrivateStoreWindow_Buy__vmt68 —— CNRDPrivateStoreWindow_Buy__vmt68 页绘制（94 行：43C250/69A5F0/69A840/43C410 + 4354D0/433AC0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPrivateStoreWindow_Buy__vmt68(int this)
{
  uint32_t *v2; // ecx
  int v3; // edi
  uint8_t *v4; // eax
  uint8_t *v5; // eax
  uint8_t *v6; // eax
  uint8_t *v7; // eax
  uint8_t *v8; // eax
  uint8_t *v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  uint32_t *v14; // edi
  uint32_t *v15; // eax
  int result; // eax
  int v17; // [esp+Ch] [ebp-14h]
  int v18; // [esp+10h] [ebp-10h]

  v2 = *(uint32_t **)(this + 4);
  v17 = v2[5];
  v18 = v2[6];
  sub_69A5F0(v2, 0, 0);
  v3 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 204);
  v4 = operator new(0x6Cu);
  if ( v4 != nullptr )
    v5 = sub_43C250(v4, v3, 2);
  else
    v5 = nullptr;
  **(uint32_t **)(this + 28) = v5;
  v6 = operator new(0x6Cu);
  if ( v6 != nullptr )
    v7 = sub_43C250(v6, v3, 5);
  else
    v7 = nullptr;
  *(uint32_t *)(*(uint32_t *)(this + 28) + 4) = v7;
  v8 = operator new(0x6Cu);
  if ( v8 != nullptr )
    v9 = sub_43C250(v8, v3, 7);
  else
    v9 = nullptr;
  *(uint32_t *)(*(uint32_t *)(this + 28) + 8) = v9;
  sub_69A5F0(**(uint32_t ***)(this + 28), 105, 59);
  sub_69A5F0(*(uint32_t **)(*(uint32_t *)(this + 28) + 4), 101, 189);
  sub_69A5F0(*(uint32_t **)(*(uint32_t *)(this + 28) + 8), 58, 224);
  *(uint8_t *)(**(uint32_t **)(this + 28) + 16) = 0;
  sub_69A840(**(uint32_t **)(this + 28));
  sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 4));
  sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 8));
  v10 = operator new(0x84u);
  if ( v10 != nullptr )
    v11 = sub_43C410(v10, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 32), 4, 5, 6, 4, 0, 0);
  else
    v11 = nullptr;
  *(uint32_t *)(this + 40) = v11;
  sub_69A5F0(v11, 128, 192);
  sub_69A840(*(uint32_t *)(this + 40));
  sub_69A5F0(*(uint32_t **)(this + 4), v17, v18);
  if ( *(uint32_t *)(dword_9B8034 + 8) != 0 )
    off_77F3FC("Another private shop created!");
  *(uint32_t *)(dword_9B8034 + 8) = this;
  v12 = operator new(0x20u);
  if ( v12 != nullptr )
    v13 = sub_4354D0(v12, (void *)5, 14);
  else
    v13 = nullptr;
  *(uint32_t *)(this + 36) = v13;
  v14 = operator new(0xCu);
  if ( v14 != nullptr )
  {
    v15 = sub_433AC0();
    v14[1] = v15;
    *((uint8_t *)v15 + 21) = 1;
    *(uint32_t *)(v14[1] + 4) = v14[1];
    *(uint32_t *)v14[1] = v14[1];
    result = v14[1];
    *(uint32_t *)(result + 8) = result;
    v14[2] = 0;
    *(uint32_t *)(this + 24) = v14;
  }
  else
  {
    *(uint32_t *)(this + 24) = 0;
    return 0;
  }
  return result;
}



// ============================================================
// 【分区 6】摆摊定价窗口（0x544960-0x545070）
// CNRDMakePriceWindow__vmt18=定价确认（转发 544D10，CLICK_BUTTON2）。
// ============================================================
// ------------------------------------------------------------
// 0x544960 sub_544960 —— 收购子窗口辅助（23 行，转发 544210）
// ------------------------------------------------------------
void /*thiscall*/ sub_544960(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void *v3; // esi

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 1) = 0;
  if ( dword_9B8044 != nullptr )
  {
    v3 = dword_9B8044;
    sub_544210((int)dword_9B8044);
    j__free(v3);
  }
  dword_9B8044 = nullptr;
}



// ------------------------------------------------------------
// 0x5449A0 sub_5449A0 —— 18 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_5449A0(uint32_t *this)
{
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  *(this + 33) = 0;
  *(this + 32) = 0;
  *(this + 35) = 999999999;
  return 0;
}



// ------------------------------------------------------------
// 0x5449D0 sub_5449D0 —— 数量/价格辅助（28 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5449D0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 29);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 30);
  *(this + 29) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 31);
  *(this + 30) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  *(this + 31) = 0;
  dword_9B8050 = 0;
  return result;
}



// ------------------------------------------------------------
// 0x544A10 sub_544A10 —— 输入框取值（22 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_544A10(uint32_t *this)
{
  int v1; // eax

  if ( dword_79BE54 == *(uint32_t *)(*(this + 29) + 12) )
  {
    v1 = *(uint32_t *)(*(this + 27) + 28);
    if ( *(uint8_t *)(v1 + 256) == 0 )
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v1 + 124) + 12);
      dword_79BE54 = dword_79BE4C;
    }
  }
  *(uint8_t *)(*(this + 28) + 16) = 0;
  return CNCommandChecker__vmt40(0, 1);
}



// ------------------------------------------------------------
// 0x544A60 sub_544A60 —— 点击音效（CLICK_BUTTON2）
// ------------------------------------------------------------
int /*thiscall*/ sub_544A60(uint32_t *this)
{
  int v2; // eax

  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  if ( dword_79BE54 == *(uint32_t *)(*(this + 29) + 12) )
  {
    v2 = *(uint32_t *)(*(this + 27) + 28);
    if ( *(uint8_t *)(v2 + 256) == 0 )
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v2 + 124) + 12);
      dword_79BE54 = dword_79BE4C;
    }
  }
  *(uint8_t *)(*(this + 28) + 16) = 0;
  return CNCommandChecker__vmt40(0, 1);
}



// ------------------------------------------------------------
// 0x544AC0 sub_544AC0 —— 展示列表刷新（432F00 + 69BCC0/402AE0/69A5F0，65 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_544AC0(uint32_t *this, int a2, int a3, int a4)
{
  uint32_t *result; // eax
  int v6; // ecx
  int v7; // edx
  unsigned int v8; // edi
  int v9; // eax
  int v10; // ecx
  int v11; // edi
  int v12; // [esp+Ch] [ebp+8h]

  *(this + 33) = a2;
  *(this + 32) = a3;
  *(this + 36) = a4;
  result = sub_432F00(a4);
  if ( result != nullptr )
  {
    v6 = *(this + 33);
    if ( v6 < result[2] )
    {
      v12 = *(uint32_t *)(result[3] + 4 * v6);
      if ( v12 != 0 )
      {
        sub_69BCC0(*(this + 29));
        sub_402AE0(szPassword);
        v7 = *(this + 28);
        v8 = *(uint32_t *)(v7 + 28);
        v9 = pt.x - (v8 >> 1);
        v10 = pt.y - (*(uint32_t *)(v7 + 32) >> 1);
        if ( v9 >= 0 )
        {
          if ( v8 + v9 > 0x280 )
            v9 = 640 - v8;
        }
        else
        {
          v9 = 0;
        }
        if ( v10 >= 0 )
        {
          v11 = *(uint32_t *)(v7 + 32);
          if ( (unsigned int)(v11 + v10) > 0x1E0 )
            v10 = 480 - v11;
        }
        else
        {
          v10 = 0;
        }
        *(uint8_t *)(v7 + 16) = 1;
        sub_69A5F0((uint32_t *)*(this + 28), v9, v10);
        dword_79BE4C = *(uint32_t *)(*(this + 29) + 12);
        dword_79BE54 = dword_79BE4C;
        *(this + 34) = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 16))(v12) + 4);
        return (uint32_t *)CNCommandChecker__vmt40(0, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x544BD0 sub_544BD0 —— 收购确认处理（69B740 输入 + 541A30/540DE0 + 44E8D0，74 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_544BD0(int this)
{
  uint32_t *v2; // eax
  int v3; // ecx
  int v4; // edx
  int v5; // edi
  const char *v6; // eax
  int result; // eax
  int v8; // ebx
  int v9; // eax
  char *v10; // eax
  int v11; // eax

  v2 = sub_432F00(*(uint32_t *)(this + 144));
  if ( v2 != nullptr
    && (v3 = *(uint32_t *)(this + 132)) < v2[2]
    && (v4 = v2[3], (v5 = *(uint32_t *)(v4 + 4 * v3)) != 0)
    && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v5 + 16))(*(uint32_t *)(v4 + 4 * v3)) + 4) == *(uint32_t *)(this + 136) )
  {
    v6 = (const char *)sub_69B740(*(uint32_t *)(this + 116));
    result = j__atol(v6);
    v8 = result;
    if ( result > 0 )
    {
      if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 44))(v5) <= 1 )
      {
        v9 = sub_541A30();
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, int))(*(uint32_t *)v9 + 60))(
          v9,
          *(uint32_t *)(this + 132),
          *(uint32_t *)(this + 128),
          *(uint32_t *)(this + 144),
          v8,
          1);
      }
      else
      {
        sub_540DE0(
          *(int **)(*(uint32_t *)(this + 108) + 116),
          1,
          *(uint32_t *)(this + 144),
          *(uint32_t *)(this + 132),
          5,
          *(uint32_t *)(this + 128),
          v8,
          0);
      }
      return sub_544A10((uint32_t *)this);
    }
  }
  else
  {
    v10 = sub_422E70(492);
    sub_44E8D0(*(char **)(this + 108), (void *)0x1B, (int)v10, 0);
    if ( dword_79BE54 == *(uint32_t *)(*(uint32_t *)(this + 116) + 12) )
    {
      v11 = *(uint32_t *)(*(uint32_t *)(this + 108) + 28);
      if ( *(uint8_t *)(v11 + 256) == 0 )
      {
        dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v11 + 124) + 12);
        dword_79BE54 = dword_79BE4C;
      }
    }
    *(uint8_t *)(*(uint32_t *)(this + 112) + 16) = 0;
    return CNCommandChecker__vmt40(0, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x544D10 sub_544D10 —— 定价确认：CLICK_BUTTON2 + 69A650/69B740/69BD90 输入 + 544BD0 提交 + 544A60 音
// ------------------------------------------------------------
char /*thiscall*/ sub_544D10(int *this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // eax
  const char *v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  char v10; // cl
  int v11; // eax
  char v13; // [esp-Ch] [ebp-24h]
  char Buffer[16]; // [esp+4h] [ebp-14h] BYREF
  int v15; // [esp+14h] [ebp-4h]

  v2 = *(this + 28);
  v15 = dword_796E50;
  LOBYTE(v3) = *(uint8_t *)(v2 + 16);
  if ( (uint8_t)v3 == 0 )
    return v3;
  sub_69A650(v2);
  v4 = *(this + 28);
  if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) )
  {
    dword_79BE4C = *(uint32_t *)(*(this + 29) + 12);
    dword_79BE54 = dword_79BE4C;
  }
  v5 = (const char *)sub_69B740(*(this + 29));
  v6 = j__atol(v5);
  if ( v6 < 0 )
  {
    v7 = 0;
    goto LABEL_8;
  }
  v7 = *(this + 35);
  if ( v6 > v7 )
  {
LABEL_8:
    if ( v7 != v6 )
    {
      sprintf(Buffer, "%d", v7);
      sub_69BD90(*(this + 29), Buffer, v13);
    }
  }
  v8 = *(this + 30);
  if ( *(uint8_t *)(v8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v8 + 12)
    || (v9 = *(this + 29), v10 = *(uint8_t *)(v9 + 116), *(uint8_t *)(v9 + 116) = 0, v10 != 0) )
  {
    sub_544BD0((int)this);
  }
  v11 = *(this + 30);
  if ( *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v11 + 12) )
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  v3 = *(this + 31);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
    LOBYTE(v3) = sub_544A60(this);
  return v3;
}



// ------------------------------------------------------------
// 0x544E20 CNRDMakePriceWindow__vmt18 —— CNRDMakePriceWindow__vmt18 定价确认槽（转发 544D10）
// ------------------------------------------------------------
void /*thiscall*/ CNRDMakePriceWindow__vmt18(Concurrency::details::ExternalContextBase *this)
{
  if ( *(uint8_t *)(*((uint32_t *)this + 28) + 16) != 0 )
  {
    sub_544D10((int *)this);
    Concurrency::details::ExternalContextBase::SpinYield(this);
  }
}



// ------------------------------------------------------------
// 0x544E40 sub_544E40 —— 定价窗口绘制（43C060/69A5F0/69A840/43C410 + 544A10，55 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_544E40(uint32_t *this, void *Block)
{
  int result; // eax
  int v4; // edi
  void *v5; // eax
  int v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // eax

  result = dword_9B8050;
  if ( dword_9B8050 == 0 )
  {
    *(this + 27) = Block;
    v4 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
    nengine__CNFrame__vmt20(v4, 211);
    *(this + 28) = this;
    v5 = operator new(0xE4u);
    if ( v5 != nullptr )
      v6 = sub_43C060((int)v5, 9, -1);
    else
      v6 = 0;
    *(this + 29) = v6;
    dword_9D3BD8 = dword_99FCCC;
    *(uint32_t *)(*(this + 29) + 128) = -5512193;
    sub_69A5F0((uint32_t *)*(this + 29), 38, 17);
    sub_69A840(*(this + 29));
    v7 = operator new(0x84u);
    if ( v7 != nullptr )
      v8 = sub_43C410(v7, v4, 9, 10, 11, 9, 0, 0);
    else
      v8 = nullptr;
    *(this + 30) = v8;
    sub_69A5F0(v8, 25, 41);
    sub_69A840(*(this + 30));
    v9 = operator new(0x84u);
    if ( v9 != nullptr )
      v10 = sub_43C410(v9, v4, 12, 13, 14, 12, 0, 0);
    else
      v10 = nullptr;
    *(this + 31) = v10;
    sub_69A5F0(v10, 86, 41);
    sub_69A840(*(this + 31));
    dword_9B8050 = (int)this;
    return sub_544A10(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x544FC0 sub_544FC0 —— 18 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_544FC0(int this)
{
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint8_t *)(this + 44) = 1;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 255;
  return 0;
}



// ------------------------------------------------------------
// 0x544FE0 sub_544FE0 —— 光标辅助（699000 时钟）
// ------------------------------------------------------------
int /*thiscall*/ sub_544FE0(int this)
{
  bool v2; // zf
  LONG y; // ecx
  int v4; // eax
  int v5; // eax
  int result; // eax

  v2 = *(uint32_t *)(this + 48) == pt.x;
  y = pt.y;
  if ( !v2 || *(uint32_t *)(this + 52) != pt.y )
  {
    *(uint32_t *)(this + 48) = pt.x;
    *(uint32_t *)(this + 52) = y;
LABEL_12:
    *(uint32_t *)(this + 56) = sub_699000(this + 12);
    goto LABEL_13;
  }
  if ( byte_89D274 != 0 )
    goto LABEL_12;
  if ( byte_89D275 != 0 )
    goto LABEL_12;
  v4 = *(uint32_t *)(this + 40);
  if ( *(uint32_t *)(v4 + 104) != 12 )
    goto LABEL_12;
  if ( *(uint32_t *)(v4 + 108) != 12 )
    goto LABEL_12;
  v5 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v5 == 5 || v5 == 0 || v5 == 2 )
    goto LABEL_12;
LABEL_13:
  result = sub_699000(this + 12);
  *(uint8_t *)(this + 44) = result < *(uint32_t *)(this + 56) + 2000;
  return result;
}



// ============================================================
// 【分区 7】摆摊光标 CNRDCursor（0x545070-0x545400）
// vmt0 加载 Character/Common/PrivateStore/Donkey/Store.img（小毛驴商店贴图）。
// ============================================================
// ------------------------------------------------------------
// 0x545070 sub_545070 —— 光标列表构建（45B1C0 + 699000 + 418DD0，105 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_545070(uint8_t *this, int a2, int a3, int a4)
{
  int v4; // esi
  int v6; // eax
  int v7; // esi
  int v8; // edi
  int result; // eax

  v4 = 0;
  if ( a4 == 0 )
  {
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 && sub_45B1C0(*(uint32_t **)(dword_8F7A24 + 20)) != 0 )
    {
      v6 = sub_45B1C0(*(uint32_t **)(dword_8F7A24 + 20));
      v7 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 40))(v6, 18) != 0 ? 124 : 120;
      v4 = sub_699000((int)(this + 12)) / 180 % 4 + v7;
      goto LABEL_42;
    }
  }
  else if ( a4 != 16 && a4 != 1 && a4 != 2 )
  {
    if ( a4 == 6 )
    {
      v4 = 9;
    }
    else if ( a4 == 17 )
    {
      v4 = sub_699000((int)(this + 12)) / 180 % 5 + 4;
    }
    else
    {
      switch ( a4 )
      {
        case 3:
        case 4:
          v4 = 67;
          break;
        case 5:
          v4 = 71;
          break;
        case 7:
          v4 = 117;
          break;
        case 8:
          v4 = 134;
          break;
        case 9:
          v4 = 113;
          break;
        case 10:
          v4 = 160;
          break;
        case 11:
          v4 = 164;
          break;
        case 12:
          v4 = 172;
          break;
        case 13:
          v4 = 168;
          break;
        case 14:
          v4 = 196;
          break;
        case 15:
          v4 = 200;
          break;
        case 18:
          v4 = 208;
          break;
        case 19:
          v4 = 204;
          break;
        default:
          break;
      }
      if ( dword_89D26C != 1 )
        v4 += dword_724798[sub_699000((int)(this + 12)) / 100 % 10];
    }
LABEL_42:
    v8 = (*(this + 60) << 24) | 0xFFFFFF;
    result = sub_418DD0(v4);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
               result,
               a2,
               a3,
               dword_79C0B0,
               1065353216,
               1065353216,
               0,
               v8,
               1333788672,
               1333788672);
    return result;
  }
  v4 = 63 - (dword_89D26C != 1);
  goto LABEL_42;
}



// ------------------------------------------------------------
// 0x545290 CNRDCursor__vmt0 —— CNRDCursor__vmt0 构造：加载 Character/Common/PrivateStore/Donkey/Store.img 小毛驴贴图（418DD0/43B560）
// ------------------------------------------------------------
char /*thiscall*/ CNRDCursor__vmt0(int this, int a2)
{
  char result; // al
  uint8_t *v3; // ebx
  int v4; // eax
  int v5; // ecx
  LONG x; // esi
  LONG y; // edi
  uint8_t v8; // bl
  int v9; // eax
  uint32_t *v10; // edx
  int v12; // [esp+8h] [ebp-4h]

  result = a2;
  v3 = (uint8_t *)this;
  if ( a2 == *(uint32_t *)(this + 4) )
  {
    result = *(uint8_t *)(this + 44);
    if ( result != 0 )
    {
      v4 = *(uint32_t *)(this + 40);
      v5 = *(uint32_t *)(v4 + 2504);
      x = pt.x;
      y = pt.y;
      v12 = v5;
      if ( v5 == 1 || v5 == 2 )
      {
        v10 = *(uint32_t **)(v4 + 2520);
        if ( v10 == nullptr )
          return sub_545070(v3, x, y, v5);
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(*v10 + 152))(
          v10,
          pt.x - (v10[9] >> 1),
          pt.y - (*(uint32_t *)(*(uint32_t *)(v4 + 2520) + 40) >> 1),
          dword_79C0B0);
      }
      else
      {
        if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 || v5 != 16 )
          return sub_545070(v3, x, y, v5);
        v8 = (uint64_t)(sin((double)(sub_699000((int)(v3 + 12)) / 25 % 36) * 0.1745329251994444) * 50.0 + 150.0);
        (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
          dword_8F84B8,
          "Character/Common/PrivateStore/Donkey/Store.img");
        v9 = sub_418DD0(3);
        sub_43B560(
          (void *)dword_79C0B0,
          x - (*(uint32_t *)(v9 + 20) >> 1),
          y - ((unsigned int)(3 * *(uint32_t *)(v9 + 24)) >> 1),
          v9,
          1065353216,
          1065353216,
          0,
          (v8 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
        v3 = (uint8_t *)this;
      }
      v5 = v12;
      return sub_545070(v3, x, y, v5);
    }
  }
  return result;
}



// ============================================================
// 【分区 8】摆摊辅助与社区菜单（0x545400-0x546030）
// 输入框取值/判定 0x545510/0x545590（供各窗口 vmt8 调用）；
// 社区菜单绘制 CNRDCommunityMenu__vmt0 在 0x5458F0（186 行）。
// ============================================================
// ------------------------------------------------------------
// 0x545400 sub_545400 —— 光标数据清理（426BD0 + 698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_545400(uint32_t *this, int a2)
{
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  char result; // al

  v3 = operator new(0x68u);
  if ( v3 != nullptr )
    v4 = sub_426BD0(v3);
  else
    v4 = nullptr;
  *(this + 1) = v4;
  *((uint32_t *)v4 + 17) = this;
  *(this + 2) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 12);
  result = sub_698F90((int)(this + 3), 0, 0);
  *(this + 10) = a2;
  return result;
}



// ------------------------------------------------------------
// 0x545480 sub_545480 —— 31 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_545480(uint32_t *this)
{
  int result; // eax
  uint32_t *v2; // esi
  uint8_t *v3; // edx

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  result = 0;
  v2 = this + 4;
  v3 = (char *)this + 106;
  do
  {
    *v2 = 0;
    *(v3 - 1) = 0;
    *v3 = 0;
    *((uint8_t *)this + result++ + 232) = 0;
    ++v2;
    v3 += 28;
  }
  while ( result < 5 );
  *(this + 22) = 5;
  return result;
}



// ------------------------------------------------------------
// 0x5454C0 sub_5454C0 —— 31 行小辅助 2
// ------------------------------------------------------------
int /*thiscall*/ sub_5454C0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  uint32_t *v5; // esi
  int i; // edi

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 3) = 0;
  v5 = this + 4;
  for ( i = 5; i != 0; --i )
  {
    if ( *v5 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v5)(*v5, 1);
    *v5++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x545510 sub_545510 —— 输入框取值（25 行——社区/摆摊/组队窗口共用的文本框读取）
// ------------------------------------------------------------
bool /*stdcall*/ sub_545510(int a1)
{
  switch ( a1 )
  {
    case 2:
      return dword_9B9460 != 0;
    case 0:
      return dword_9B945C != 0;
    case 3:
      return dword_9B9458 != 0;
    case 4:
      return dword_9B88C0 != 0;
    case 1:
      return *(uint32_t *)(*((uint32_t *)dword_8F8528 + 633) + 28) == 1;
    default:
      break;
  }
  return false;
}



// ------------------------------------------------------------
// 0x545590 sub_545590 —— 输入判定（44E850，28 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_545590(uint32_t **this, int a2)
{
  char result; // al

  result = a2;
  switch ( a2 )
  {
    case 2:
      return sub_44E850(*(this + 1), 1);
    case 0:
      return sub_44E850(*(this + 1), 54);
    case 3:
      return sub_44E850(*(this + 1), 5);
    case 4:
      return sub_44E850(*(this + 1), 12);
    case 1:
      return sub_44E850(*(this + 1), 61);
    default:
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x545610 sub_545610 —— 输入框刷新（545510/545590 + 422E70/44E8D0，69 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_545610(int this, int a2)
{
  int v3; // eax
  int i; // esi
  char *v5; // eax

  LOBYTE(v3) = sub_545510(a2);
  if ( (uint8_t)v3 == 0 )
  {
    for ( i = 0; i < 5; ++i )
      sub_545590((uint32_t **)this, i);
    LOBYTE(v3) = dword_8F7C08;
    if ( dword_8F7C08 != 0 )
    {
      v3 = *(uint32_t *)(dword_8F7C08 + 648);
      if ( v3 != 0 && *(uint8_t *)(v3 + 284) != 0 )
      {
        switch ( a2 )
        {
          case 0:
            v5 = sub_422E70(1346);
LABEL_13:
            LOBYTE(v3) = sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v5, 0);
            return v3;
          case 3:
            v5 = sub_422E70(1344);
            goto LABEL_13;
          case 1:
            v5 = sub_422E70(1901);
            goto LABEL_13;
          default:
            break;
        }
      }
    }
    if ( a2 == 2 )
    {
      LOBYTE(v3) = sub_44E8D0(*(char **)(this + 4), (void *)1, 0, 0);
    }
    else if ( a2 != 0 )
    {
      switch ( a2 )
      {
        case 3:
          LOBYTE(v3) = sub_44E8D0(*(char **)(this + 4), (void *)5, 0, 0);
          break;
        case 4:
          LOBYTE(v3) = sub_44E8D0(*(char **)(this + 4), (void *)0xC, 0, 0);
          break;
        case 1:
          LOBYTE(v3) = sub_44E8D0(*(char **)(this + 4), (void *)0x3D, 0, 0);
          break;
        default:
          break;
      }
    }
    else
    {
      LOBYTE(v3) = sub_44E8D0(*(char **)(this + 4), (void *)0x36, 0, 0);
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x545730 sub_545730 —— 输入框打开（41C590 + 545610 + 49EC10 + 69A5F0 定位）
// ------------------------------------------------------------
uint8_t /*thiscall*/ sub_545730(int *this)
{
  uint32_t *v2; // edi
  int v3; // esi
  int v4; // esi
  uint32_t **v5; // edi
  int v6; // esi
  int i; // ebx
  uint8_t result; // al
  uint32_t **v9; // [esp+Ch] [ebp-4h]

  v2 = this + 4;
  v3 = 0;
  v9 = (uint32_t **)(this + 4);
  do
  {
    *(uint8_t *)(*v2 + 16) = (uint8_t)sub_41C590(dword_8F7A24) == 0 || v3 != 3 && v3 != 1;
    ++v3;
    ++v2;
  }
  while ( v3 < 5 );
  if ( (uint8_t)sub_41C590(dword_8F7A24) == 0 )
  {
    v4 = 0;
    while ( !sub_545510(v4) )
    {
      if ( ++v4 >= 5 )
      {
        if ( *(this + 22) != 5 )
          sub_545610((int)this, *(this + 22));
        break;
      }
    }
  }
  if ( sub_49EC10(dword_8F8508) == 0 )
    *(uint8_t *)(*(this + 5) + 16) = 0;
  v5 = v9;
  *(uint8_t *)(*(this + 5) + 16) = 0;
  v6 = 26;
  for ( i = 5; i != 0; --i )
  {
    result = *((uint8_t *)*v5 + 16);
    if ( result != 0 )
    {
      result = (uint8_t)sub_69A5F0(*v5, 547, v6);
      v6 += 28;
    }
    ++v5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x545800 sub_545800 —— 输入确认（CLICK_BUTTON1 音 + 545510/545590/545610）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_545800(uint32_t **this)
{
  int v2; // esi
  uint32_t **v3; // ebx
  uint32_t *result; // eax

  v2 = 0;
  v3 = this + 4;
  do
  {
    result = *v3;
    if ( *((uint8_t *)*v3 + 17) != 0 && dword_79BE34 == result[3] )
    {
      if ( sub_545510(v2) )
        sub_545590(this, v2);
      else
        sub_545610((int)this, v2);
      result = sub_432EA0("CLICK_BUTTON1", -1, 0, 0);
    }
    ++v2;
    ++v3;
  }
  while ( v2 < 5 );
  return result;
}



// ------------------------------------------------------------
// 0x545860 sub_545860 —— 输入处理（545730 打开 + 44E850 状态）
// ------------------------------------------------------------
char /*thiscall*/ sub_545860(int this, int a2, int a3)
{
  int v4; // edi
  bool v5; // zf
  char result; // al

  if ( a2 == 1 )
  {
    v4 = 0;
    while ( !sub_545510(v4) )
    {
      if ( ++v4 >= 5 )
      {
        v4 = 5;
        break;
      }
    }
    *(uint32_t *)(this + 88) = v4;
  }
  else
  {
    v5 = a3 == 1;
    if ( a3 != 1 )
      goto LABEL_10;
    sub_545730((int *)this);
  }
  v5 = a3 == 1;
LABEL_10:
  result = v5;
  *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = v5;
  if ( a3 != 1 )
  {
    sub_44E850(*(uint32_t **)(this + 4), 54);
    sub_44E850(*(uint32_t **)(this + 4), 1);
    sub_44E850(*(uint32_t **)(this + 4), 5);
    sub_44E850(*(uint32_t **)(this + 4), 12);
    return sub_44E850(*(uint32_t **)(this + 4), 61);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5458F0 CNRDCommunityMenu__vmt0 —— CNRDCommunityMenu__vmt0 构造（186 行：568A70 + 69A4D0/491630 绘制 + 422E70 取串）
// ------------------------------------------------------------
int /*thiscall*/ sub_5458F0(uint32_t *this, int a2)
{
  uint32_t *v2; // esi
  int v4; // eax
  const char *v5; // eax
  int result; // eax
  int v7; // ebx
  int v8; // eax
  unsigned int v9; // ecx
  long double v10; // st7
  int v11; // eax
  char v12; // al
  int v13; // esi
  int v14; // eax
  int v15; // edx
  int v16; // esi
  int v17; // eax
  int v18; // ecx
  int v19; // esi
  int v20; // ebx
  int v21; // eax
  int *v22; // [esp+10h] [ebp-9Ch]
  int v23; // [esp+10h] [ebp-9Ch]
  int v25; // [esp+18h] [ebp-94h]
  int v26; // [esp+18h] [ebp-94h]
  int v27; // [esp+1Ch] [ebp-90h]
  int v28; // [esp+20h] [ebp-8Ch]
  int v29; // [esp+20h] [ebp-8Ch]
  int v30; // [esp+24h] [ebp-88h]
  int v31; // [esp+24h] [ebp-88h]
  int v32; // [esp+24h] [ebp-88h]
  char Buffer[128]; // [esp+28h] [ebp-84h] BYREF
  int v34; // [esp+A8h] [ebp-4h]
  uint32_t *v35; // [esp+B4h] [ebp+8h]
  int *v36; // [esp+B4h] [ebp+8h]

  v2 = this;
  v34 = dword_796E50;
  if ( a2 == *(this + 3) )
  {
    v4 = sub_568A70((uint8_t)byte_99FCD0, (uint8_t)byte_99FCD1);
    if ( v4 != 0 )
    {
      if ( *(uint32_t *)(v4 + 24) < 0x10u )
        v5 = (const char *)(v4 + 4);
      else
        v5 = *(const char **)(v4 + 4);
      sprintf(Buffer, "ch%02d.%s", (uint8_t)byte_99FCD1, v5);
    }
    else
    {
      sprintf(Buffer, "ch%02d.", (uint8_t)byte_99FCD1);
    }
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v2 + 9);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      474,
      6,
      -6567706,
      Buffer);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  }
  else
  {
    v7 = 0;
    v25 = 0;
    v22 = this + 4;
    v35 = this + 4;
    v27 = (int)(this + 23);
    do
    {
      if ( a2 == *v35 )
      {
        sub_491530(2, 0);
        v8 = sub_699000(v27);
        v28 = v8;
        if ( *(uint8_t *)(*v35 + 17) != 0 && dword_79BE3C == *(uint32_t *)(*v35 + 12) )
        {
          if ( v8 == 0 )
          {
            sub_698F90(v27, 0, 0);
            v8 = v28;
          }
          v9 = *((uint8_t *)v2 + v7 + 232) + 10;
          if ( v9 >= 0xD7 )
            LOBYTE(v9) = -41;
          *((uint8_t *)v2 + v7 + 232) = v9;
          v10 = sin((double)(unsigned int)v8 * 0.006283185307179587) * 35.0 + (double)(uint8_t)v9;
        }
        else
        {
          if ( v8 != 0 )
          {
            *(uint8_t *)(v27 + 13) = 0;
            *(uint8_t *)(v27 + 14) = 0;
            *((uint8_t *)v2 + v7 + 232) = -76;
          }
          else
          {
            *((uint8_t *)v2 + v7 + 232) = (*((uint8_t *)v2 + v7 + 232) - 10)
                                      & ((*((uint8_t *)v2 + v7 + 232) <= 0xAu) - 1);
          }
          v10 = (double)*((uint8_t *)v2 + v7 + 232);
        }
        if ( v10 > 0.0 )
        {
          v29 = *(uint32_t *)(a2 + 24);
          v30 = *(uint32_t *)(a2 + 20);
          v11 = sub_418DD0(dword_7247D8[v7]);
          if ( v11 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v11 + 128))(
              v11,
              v30 - 44,
              v29 - 5,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              ((uint8_t)(uint64_t)v10 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
            v7 = v25;
          }
        }
        v12 = sub_69A4D0(*v35);
        v13 = *(uint32_t *)(a2 + 24);
        v31 = *(uint32_t *)(a2 + 20);
        if ( v12 == 1 )
          v14 = sub_418DD0(dword_7247EC[v7]);
        else
          v14 = sub_418DD0(dword_724800[v7]);
        if ( v14 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v14 + 152))(v14, v31, v13, dword_79C0B0);
        sub_491630(2);
        if ( (uint8_t)sub_69A4D0(*v35) == 1 )
        {
          v15 = dword_724814[v7];
        }
        else if ( *(uint8_t *)(*v35 + 17) != 0 && dword_79BE3C == *(uint32_t *)(*v35 + 12) )
        {
          v15 = dword_724828[v7];
        }
        else
        {
          v15 = dword_72483C[v7];
        }
        v16 = *(uint32_t *)(a2 + 24);
        v32 = *(uint32_t *)(a2 + 20);
        v17 = sub_418DD0(v15);
        if ( v17 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v17 + 152))(v17, v32, v16, dword_79C0B0);
        v2 = this;
      }
      v25 = ++v7;
      v27 += 28;
      ++v35;
    }
    while ( v7 < 5 );
    v18 = 0;
    v26 = 0;
    v36 = v22;
    do
    {
      result = *v36;
      if ( a2 == *v36 && *(uint8_t *)(result + 17) != 0 && dword_79BE3C == *(uint32_t *)(result + 12) )
      {
        v19 = *(uint32_t *)(result + 20);
        v23 = *(uint32_t *)(result + 24);
        v20 = sub_422E70(v18 + 2190);
        v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v20);
        result = sub_4649B0(v19 - v21 - 10, v23 + 14, -1, -16777216, 4, v20, 0, 0, 1600, 0);
        v18 = v26;
      }
      v26 = ++v18;
      ++v36;
    }
    while ( v18 < 5 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x545D80 sub_545D80 —— 社区菜单页绘制（43C250/69A5F0 + 426BD0/69A840/43C410，114 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_545D80(int this, int a2)
{
  int v3; // edi
  uint8_t *v4; // eax
  uint8_t *v5; // eax
  uint8_t *v6; // eax
  uint8_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  uint32_t *v14; // eax
  uint32_t *v15; // eax
  uint32_t *v16; // eax
  uint32_t *v17; // eax
  uint32_t *v18; // edi
  bool v19; // zf
  int result; // eax
  int v21; // [esp-4h] [ebp-20h]
  int Block; // [esp+Ch] [ebp-10h]
  int v23; // [esp+24h] [ebp+8h]

  *(uint32_t *)(this + 4) = a2;
  v3 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v4 = operator new(0x6Cu);
  if ( v4 != nullptr )
    v5 = sub_43C250(v4, v3, 206);
  else
    v5 = nullptr;
  *(uint32_t *)(this + 12) = v5;
  *((uint32_t *)v5 + 17) = this;
  sub_69A5F0(*(uint32_t **)(this + 12), 456, 0);
  v6 = operator new(0x68u);
  if ( v6 != nullptr )
    v7 = sub_426BD0(v6);
  else
    v7 = nullptr;
  v21 = *(uint32_t *)(this + 12);
  *(uint32_t *)(this + 8) = v7;
  sub_69A840(v21);
  *(uint8_t *)(this + 36) = 0;
  *(uint8_t *)(this + 37) = 0;
  *(uint8_t *)(this + 38) = 0;
  *(uint8_t *)(this + 39) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 6;
  *(uint32_t *)(this + 56) = 12;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 1600;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 84) = dword_99FCCC;
  *(uint32_t *)(this + 64) = 125;
  *(uint32_t *)(this + 48) = 2;
  v8 = operator new(0x84u);
  if ( v8 != nullptr )
    v9 = sub_43C410(v8, v3, 207, 219, 194, -1, 0, 0);
  else
    v9 = nullptr;
  *(uint32_t *)(this + 16) = v9;
  v10 = operator new(0x84u);
  if ( v10 != nullptr )
    v11 = sub_43C410(v10, v3, 279, 280, 281, -1, 0, 0);
  else
    v11 = nullptr;
  *(uint32_t *)(this + 20) = v11;
  v12 = operator new(0x84u);
  if ( v12 != nullptr )
    v13 = sub_43C410(v12, v3, 208, 220, 195, -1, 0, 0);
  else
    v13 = nullptr;
  *(uint32_t *)(this + 24) = v13;
  v14 = operator new(0x84u);
  if ( v14 != nullptr )
    v15 = sub_43C410(v14, v3, 209, 221, 196, -1, 0, 0);
  else
    v15 = nullptr;
  *(uint32_t *)(this + 28) = v15;
  v16 = operator new(0x84u);
  if ( v16 != nullptr )
    v17 = sub_43C410(v16, v3, 210, 222, 197, -1, 0, 0);
  else
    v17 = nullptr;
  *(uint32_t *)(this + 32) = v17;
  v23 = 26;
  v18 = (uint32_t *)(this + 16);
  Block = 5;
  do
  {
    *(uint32_t *)(*v18 + 68) = this;
    *(uint8_t *)(*v18 + 16) = 0;
    sub_69A840(*v18);
    sub_69A5F0((uint32_t *)*v18++, 547, v23);
    v19 = Block == 1;
    v23 += 28;
    --Block;
  }
  while ( !v19 );
  result = *(uint32_t *)(this + 16);
  *(uint8_t *)(result + 17) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 20) + 17) = 0;
  return result;
}



// ============================================================
// 【分区 9】新手引导 CNRDTutorial（0x546030-0x5470A0）
// 指引箭头绘制 0x5464C0（MOVE_ARROW 音效）；引导主状态 CNRDTutorial__vmt0 在 0x5468B0；
// 引导主状态（241 行）；0x546E10=引导步骤推进。
// ============================================================
// ------------------------------------------------------------
// 0x546030 sub_546030 —— 22 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_546030(int this)
{
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 11;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 53) = 0;
  *(uint32_t *)(this + 57) = 0;
  *(uint16_t *)(this + 61) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint8_t *)(this + 64) = 0;
  *(uint8_t *)(this + 65) = 0;
  *(uint8_t *)(this + 52) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x546060 sub_546060 —— 17 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_546060(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 2) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x546080 sub_546080 —— 10 行小辅助
// ------------------------------------------------------------
bool /*stdcall*/ sub_546080(int a1)
{
  return a1 == 1016;
}



// ------------------------------------------------------------
// 0x5460A0 sub_5460A0 —— 引导辅助（44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ sub_5460A0(char **this, int a2, int a3)
{
  if ( a2 == 1 )
  {
    if ( a3 == 1 )
    {
      sub_44E8D0(*(this + 1), nullptr, 0, 0);
      return 1;
    }
  }
  else if ( a2 == 2 && a3 == 1 )
  {
    sub_44E8D0(*(this + 1), nullptr, 0, 4);
    return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x5460F0 sub_5460F0 —— 引导辅助 2（44E8D0）
// ------------------------------------------------------------
char /*stdcall*/ sub_5460F0(int a1)
{
  if ( a1 != 2 )
    return 0;
  sub_44E8D0((char *)dword_8F8528, nullptr, 0, 3);
  return 1;
}



// ------------------------------------------------------------
// 0x546120 sub_546120 —— 引导辅助 3（429830 + 41A5E0 + 44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ sub_546120(uint8_t *this)
{
  int v2; // eax

  v2 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  if ( sub_41A5E0(v2 + 53) > 6 || *(this + 64) != 0 )
    return 0;
  sub_44E8D0((char *)dword_8F8528, nullptr, 0, 5);
  *(this + 64) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x546170 sub_546170 —— 引导辅助 4（429830 + 41A5E0 + 44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ sub_546170(uint8_t *this)
{
  int v2; // eax

  v2 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  if ( sub_41A5E0(v2 + 53) > 6 || *(this + 65) != 0 )
    return 0;
  sub_44E8D0((char *)dword_8F8528, nullptr, 0, 6);
  *(this + 65) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x5461C0 sub_5461C0 —— 引导文本复位（698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_5461C0(uint32_t *this, int a2)
{
  int v3; // ecx
  char result; // al

  v3 = (int)(this + 5);
  *(this + 4) = a2;
  *(uint8_t *)(v3 + 13) = 0;
  *(uint8_t *)(v3 + 14) = 0;
  result = sub_698F90(v3, 0, 0);
  *(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5461F0 sub_5461F0 —— 引导气泡绘制（45E490/45E4D0 + 491530/491630 批次，103 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5461F0(void *this, int a2)
{
  uint64_t v2; // rax
  int v3; // esi
  int v4; // eax
  int v5; // edi
  int v6; // esi
  int v7; // eax
  int v8; // esi
  int v9; // esi
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // et2
  double v14; // st7
  int v15; // eax
  int v17; // [esp-18h] [ebp-1Ch]
  int v18; // [esp-14h] [ebp-18h]
  int v19; // [esp-10h] [ebp-14h]

  LODWORD(v2) = dword_8F7C08;
  if ( dword_8F7C08 == 0 )
    return v2;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  v3 = dword_8F7C08;
  v19 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C08 + 36))() + 8);
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 120))(v3);
  v5 = sub_45E490(v4, v19) - 46;
  v6 = dword_8F7C08;
  v18 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C08 + 36))() + 8);
  v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 128))(v6);
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 124))(v6);
  v8 = sub_45E4D0(v7, v17, v18, 1.0);
  v9 = -110 - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C08 + 192))(dword_8F7C08) + v8;
  v10 = sub_418DD0(14);
  if ( v10 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(v10, v5, v9, dword_79C0B0);
  LOBYTE(v11) = -1;
  v12 = sub_699000((int)this + 20);
  v13 = v12 % 2000;
  LODWORD(v2) = v12 / 2000;
  HIDWORD(v2) = v13;
  if ( v13 < 500 )
  {
    v14 = sub_4049C0(0.0, 255.0, SHIDWORD(v2), 500);
LABEL_9:
    v2 = (uint64_t)v14;
    v11 = (uint64_t)v14;
    if ( v11 == 0 )
      return v2;
    goto LABEL_10;
  }
  if ( SHIDWORD(v2) >= 1100 )
  {
    if ( SHIDWORD(v2) >= 1600 )
      return v2;
    v14 = sub_4049C0(255.0, 0.0, HIDWORD(v2) - 1100, 500);
    goto LABEL_9;
  }
LABEL_10:
  switch ( a2 )
  {
    case 0:
      v5 += 9;
      goto LABEL_15;
    case 1:
      v5 += 59;
      goto LABEL_15;
    case 2:
      v5 += 34;
      v9 += 8;
      break;
    case 3:
      v5 += 34;
LABEL_15:
      v9 += 33;
      break;
    default:
      break;
  }
  sub_491530(2, 0);
  v15 = sub_418DD0(21);
  if ( v15 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v15 + 128))(
      v15,
      v5,
      v9,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)v11 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  LODWORD(v2) = sub_491630(2);
  return v2;
}



// ------------------------------------------------------------
// 0x5463C0 sub_5463C0 —— 引导指示绘制（699000 + 4049C0 + 491530/491630，42 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5463C0(void *this, int a2, int a3)
{
  int v3; // edx
  double v4; // st7
  int v5; // eax
  int v6; // eax
  int result; // eax

  v3 = sub_699000((int)this + 20) % 1000;
  if ( v3 >= 500 )
    v4 = sub_4049C0(255.0, 100.0, v3 - 500, 500);
  else
    v4 = sub_4049C0(100.0, 255.0, v3, 500);
  v5 = sub_418DD0(26);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 152))(v5, a2, a3, dword_79C0B0);
  sub_491530(2, 0);
  v6 = sub_418DD0(25);
  if ( v6 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
      v6,
      a2,
      a3,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)(uint64_t)v4 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  sub_491630(2);
  result = sub_418DD0(24);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(result, a2, a3, dword_79C0B0);
  return result;
}



// ------------------------------------------------------------
// 0x5464C0 sub_5464C0 —— 指引箭头绘制：MOVE_ARROW 事件音（432EA0）+ 4049C0/418DD0 精灵
// ------------------------------------------------------------
char */*thiscall*/ sub_5464C0(char **this, int a2, int a3, int a4)
{
  int v4; // esi
  int v5; // ebx
  int v6; // edi
  int v7; // esi
  char *result; // eax

  v4 = (int)(this + 5);
  v5 = 255;
  v6 = sub_699000((int)(this + 5)) % 2000;
  v7 = sub_699000(v4) / 2000;
  if ( v6 >= 500 )
  {
    if ( v6 >= 1100 )
    {
      if ( v6 >= 1600 )
        v5 = 0;
      else
        v5 = (uint64_t)sub_4049C0(255.0, 0.0, v6 - 1100, 500);
    }
    else
    {
      ++v7;
    }
  }
  else
  {
    v5 = (uint64_t)sub_4049C0(0.0, 255.0, v6, 500);
  }
  result = *(this + 12);
  if ( (int)result < v7 )
  {
    *(this + 12) = result + 1;
    result = (char *)sub_432EA0("MOVE_ARROW", -1, 0, 0);
  }
  if ( v5 != 0 )
  {
    result = (char *)sub_418DD0(a2);
    if ( result != nullptr )
      return (char *)(*(int (/*thiscall*/ **)(char *, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
                       result,
                       0,
                       0,
                       dword_79C0B0,
                       1065353216,
                       1065353216,
                       0,
                       ((uint8_t)v5 << 24) | 0xFFFFFF,
                       1333788672,
                       1333788672);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5465E0 sub_5465E0 —— 引导辅助（698F90）
// ------------------------------------------------------------
int /*thiscall*/ sub_5465E0(int this)
{
  int v2; // ecx

  v2 = this + 20;
  *(uint32_t *)(this + 16) = 1;
  *(uint8_t *)(v2 + 13) = 0;
  *(uint8_t *)(v2 + 14) = 0;
  sub_698F90(v2, 0, 0);
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 53) = 0;
  *(uint32_t *)(this + 57) = 0;
  *(uint16_t *)(this + 61) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint8_t *)(this + 64) = 0;
  *(uint8_t *)(this + 65) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x546620 sub_546620 —— 引导步骤查询（47B8D0 + 698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_546620(int this, int a2)
{
  if ( a2 == 1016 )
  {
    sub_47B8D0((uint32_t *)dword_8F8540, 1016, 0);
    return 1;
  }
  else
  {
    if ( *(uint32_t *)(this + 16) == 4 )
    {
      *(uint32_t *)(this + 16) = 5;
      *(uint8_t *)(this + 33) = 0;
      *(uint8_t *)(this + 34) = 0;
      sub_698F90(this + 20, 0, 0);
      *(uint32_t *)(this + 48) = 0;
      *(uint8_t *)(this + 57) = 1;
    }
    return 0;
  }
}



// ------------------------------------------------------------
// 0x546680 sub_546680 —— 引导辅助 2（698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_546680(int this, int a2)
{
  char result; // al

  if ( a2 == 1016 && *(uint32_t *)(this + 16) == 2 )
  {
    *(uint32_t *)(this + 16) = 3;
    *(uint8_t *)(this + 33) = 0;
    *(uint8_t *)(this + 34) = 0;
    result = sub_698F90(this + 20, 0, 0);
    *(uint32_t *)(this + 48) = 0;
    *(uint8_t *)(this + 55) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5466C0 sub_5466C0 —— 引导辅助 3（698F90，40 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_5466C0(int this, int a2, int a3)
{
  int v4; // eax
  int v5; // ecx
  char result; // al

  v4 = *(uint32_t *)(this + 16);
  v5 = 0;
  if ( v4 == 1 )
  {
    v5 = 1;
  }
  else if ( a3 == 2 )
  {
    if ( v4 == 6 )
    {
      *(uint8_t *)(this + 59) = 1;
    }
    else if ( v4 == 9 )
    {
      *(uint8_t *)(this + 62) = 1;
    }
  }
  else if ( a3 == 3 && *(uint8_t *)(this + 60) == 0 )
  {
    v5 = 7;
  }
  *(uint32_t *)(this + 16) = v5;
  *(uint8_t *)(this + 33) = 0;
  *(uint8_t *)(this + 34) = 0;
  result = sub_698F90(this + 20, 0, 0);
  *(uint32_t *)(this + 48) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x546730 sub_546730 —— 引导步骤推进（45AFD0 + 698F90，93 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_546730(int this)
{
  int v1; // eax
  int v3; // ecx
  int *v4; // eax
  int v5; // eax
  int v6; // edi
  int v7; // ecx
  int v8; // eax
  char result; // al

  v1 = *(uint32_t *)(dword_8F7A24 + 20);
  v3 = *(uint32_t *)(v1 + 100);
  v4 = *(int **)(v1 + 104);
  if ( v4 != nullptr )
    v5 = *v4;
  else
    v5 = -1;
  v6 = 0;
  if ( v3 == 1 )
  {
    v7 = *(uint32_t *)(this + 16);
    if ( v7 == 8 || v7 == 10 || v7 == 9 )
    {
      v6 = *(uint32_t *)(this + 16);
    }
    else if ( v5 == 1 )
    {
      if ( *(uint8_t *)(this + 55) == 0 )
        v6 = 2;
    }
    else if ( v5 != 0 )
    {
      if ( v5 == 2 )
      {
        if ( *(uint8_t *)(this + 59) != 0 )
        {
          if ( !sub_45AFD0(1) )
            v6 = 7;
          *(uint8_t *)(this + 58) = 1;
        }
        else
        {
          v6 = 6;
          *(uint8_t *)(this + 58) = 1;
        }
      }
    }
    else if ( *(uint8_t *)(this + 57) != 0 )
    {
      if ( *(uint8_t *)(this + 58) == 0 )
        v6 = 5;
      *(uint8_t *)(this + 56) = 1;
    }
    else
    {
      v6 = 4;
      *(uint8_t *)(this + 56) = 1;
    }
  }
  else if ( v3 == 2 )
  {
    *(uint8_t *)(this + 63) = 1;
  }
  if ( *(uint32_t *)(this + 16) == 7 )
  {
    v8 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 24) + 220);
    if ( v8 != 1 && v8 != 2 )
    {
      *(uint32_t *)(this + 16) = 0;
      *(uint8_t *)(this + 33) = 0;
      *(uint8_t *)(this + 34) = 0;
      sub_698F90(this + 20, 0, 0);
      *(uint32_t *)(this + 48) = 0;
      *(uint32_t *)(this + 53) = 16843009;
      *(uint32_t *)(this + 57) = 16843009;
      *(uint16_t *)(this + 61) = 257;
      *(uint8_t *)(this + 63) = 1;
    }
  }
  *(uint32_t *)(this + 16) = v6;
  *(uint8_t *)(this + 33) = 0;
  *(uint8_t *)(this + 34) = 0;
  result = sub_698F90(this + 20, 0, 0);
  *(uint32_t *)(this + 48) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x546840 sub_546840 —— 引导触发（56CFE0 频道选择 + 551500 + 44BBA0 显示）
// ------------------------------------------------------------
char /*thiscall*/ sub_546840(int this, int a2)
{
  int v3; // eax

  if ( *(uint32_t *)(this + 16) != 8 || a2 != 1 )
    return 0;
  v3 = sub_56CFE0(1);
  sub_551500(v3);
  sub_44BBA0(*(uint32_t **)(this + 4), 3, 0);
  *(uint32_t *)(this + 16) = 0;
  *(uint8_t *)(this + 33) = 0;
  *(uint8_t *)(this + 34) = 0;
  sub_698F90(this + 20, 0, 0);
  *(uint32_t *)(this + 48) = 0;
  *(uint8_t *)(this + 61) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x5468B0 CNRDTutorial__vmt0 —— CNRDTutorial__vmt0 引导主状态（241 行：5463C0/5464C0/5461F0 绘制 + 425100/425A00 + 416D10/416CD0/416D50 文本）
// ------------------------------------------------------------
char /*thiscall*/ sub_5468B0(int *this, int a2)
{
  int v2; // eax
  bool v4; // zf
  int v5; // eax
  int v6; // edi
  int v7; // ebx
  int v8; // esi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // esi
  int v13; // eax
  int *v14; // edi
  int v15; // esi
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // edx
  int v20; // et2
  int v21; // esi
  int v22; // eax
  int v23; // eax
  int v24; // eax
  bool v25; // cc
  int v26; // eax
  int v27; // eax
  int *v28; // eax
  int v29; // esi
  int v31; // [esp-10h] [ebp-58h]
  char v32[4]; // [esp+4h] [ebp-44h] BYREF
  int v33; // [esp+8h] [ebp-40h]
  int v34; // [esp+34h] [ebp-14h]
  int *v35; // [esp+38h] [ebp-10h]
  int v36; // [esp+44h] [ebp-4h]
  char v37; // [esp+53h] [ebp+Bh]

  LOBYTE(v2) = a2;
  v4 = a2 == *(this + 2);
  v35 = this;
  if ( !v4 )
    return v2;
  v2 = *(this + 4);
  switch ( v2 )
  {
    case 2:
      LOBYTE(v2) = sub_5463C0(this, 243, 106);
      return v2;
    case 3:
      sub_5464C0(0, 1, 2);
      LOBYTE(v2) = sub_5461F0(this, 3);
      return v2;
    case 4:
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
      v5 = sub_48C1C0(1);
      sub_5463C0(this, 452 - v5, 141);
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C08 + 120))(dword_8F7C08);
      if ( v2 >= 520 )
        LOBYTE(v2) = sub_5461F0(this, 0);
      return v2;
    case 5:
      sub_5464C0(11, 12, 13);
LABEL_11:
      LOBYTE(v2) = sub_5461F0(this, 1);
      return v2;
    case 6:
      sub_5464C0(7, 8, 9);
      goto LABEL_11;
    default:
      break;
  }
  if ( v2 != 7 )
  {
    if ( v2 != 8 )
    {
      if ( v2 == 10 )
      {
        v2 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 104);
        if ( v2 != 0 )
        {
          v2 = *(uint32_t *)v2;
          if ( v2 == 0 || v2 == 2 )
            LOBYTE(v2) = sub_5464C0(6, 4, 5);
        }
      }
      else if ( v2 == 9 )
      {
        v2 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 104);
        if ( v2 != 0 )
        {
          v2 = *(uint32_t *)v2;
          if ( v2 == 0 || v2 == 2 )
            LOBYTE(v2) = sub_5464C0(10, 8, 9);
        }
      }
      return v2;
    }
    v28 = *(int **)(*(uint32_t *)(dword_8F7A24 + 20) + 104);
    if ( v28 != nullptr )
      v29 = *v28;
    else
      v29 = -1;
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    v2 = sub_48C1C0(1);
    if ( v29 != 0 )
    {
      if ( v29 == 2 )
        goto LABEL_57;
    }
    else if ( v2 < 472 )
    {
      LOBYTE(v2) = sub_5463C0(this, 452 - v2, 141);
      return v2;
    }
    if ( v2 < 400 || v29 != 0 )
      return v2;
LABEL_57:
    LOBYTE(v2) = sub_5464C0(3, 4, 5);
    return v2;
  }
  v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);
  v7 = sub_425100(v6);
  v8 = 0;
  v37 = 0;
  if ( v7 > 0 )
  {
    do
    {
      v9 = sub_425A00(v8);
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 40))(v9, 289) != 0 )
        v37 = 1;
      ++v8;
    }
    while ( v8 < v7 );
    if ( v37 != 0 )
    {
      v10 = sub_418DD0(17);
      sub_40FC80(90, 90, v10);
      v11 = sub_418DD0(16);
      sub_40FC80(90, 90, v11);
      sub_416D10(v32);
      v36 = 0;
      sub_416CD0(v32);
      v34 = dword_99FCCC;
      v33 = -16777216;
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v32);
      v12 = *(uint32_t *)dword_79C0B0;
      v13 = sub_422E70(500);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(v12 + 80))(dword_79C0B0, 270, 185, -1, v13);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v36 = -1;
      sub_416D50(v32);
    }
  }
  v14 = v35;
  v15 = (int)(v35 + 5);
  if ( sub_699000((int)(v35 + 5)) < 500 && *((uint8_t *)v14 + 52) == 0 )
  {
    v16 = sub_418DD0(23);
    LOBYTE(v2) = sub_40FC80(0, 0, v16);
    return v2;
  }
  if ( sub_699000(v15) < 13100 && *((uint8_t *)v14 + 52) == 0 )
  {
    v17 = sub_418DD0(23);
    sub_40FC80(0, 0, v17);
    v18 = sub_699000(v15);
    v20 = (v18 - 500) / 300 % 14;
    v2 = (v18 - 500) / 300 / 14;
    v19 = v20;
    if ( v20 != 0 )
    {
      if ( v19 == 2 )
      {
        v21 = 1;
        v22 = 15;
      }
      else
      {
        if ( v19 != 4 )
        {
          switch ( v19 )
          {
            case 6:
              v21 = 3;
              break;
            case 8:
              v21 = 4;
              break;
            case 10:
              v21 = 5;
              break;
            case 12:
              v21 = 6;
              break;
            default:
              return v2;
          }
          goto LABEL_29;
        }
        v21 = 2;
        v22 = 20;
      }
    }
    else
    {
      v21 = 0;
      v22 = 22;
    }
    v23 = sub_418DD0(v22);
    sub_40FC80(0, 0, v23);
LABEL_29:
    sub_491530(2, 0);
    v24 = sub_418DD0(21);
    sub_40FC80(dword_724858[2 * v21], dword_72485C[2 * v21], v24);
    LOBYTE(v2) = sub_491630(2);
    return v2;
  }
  v25 = sub_699000(v15) < 14100;
  LOBYTE(v2) = *((uint8_t *)v14 + 52);
  if ( v25 )
  {
    if ( (uint8_t)v2 == 0 )
    {
      v26 = sub_699000(v15);
      v31 = ((uint8_t)sub_423A80(255, 0, v26 - 13600, 500) << 24) | 0xFFFFFF;
      v27 = sub_418DD0(23);
      LOBYTE(v2) = sub_43B560(0, 0, v27, 1065353216, 1065353216, 0, v31, 1333788672, 1333788672);
    }
  }
  else if ( (uint8_t)v2 == 0 )
  {
    *((uint8_t *)v14 + 52) = 1;
  }
  return v2;
}


// ------------------------------------------------------------
// 0x546E10 sub_546E10 —— 引导步骤推进（472F90/472E30/47C080/47B6F0/461730/47B560，59 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_546E10(int this)
{
  char result; // al
  int v3; // eax
  int v4; // edi
  uint32_t *v5; // edi
  int *v6; // [esp+8h] [ebp-8h] BYREF
  int v7; // [esp+Ch] [ebp-4h] BYREF

  if ( sub_472F90(1) >= 1 )
  {
    *(uint32_t *)(this + 16) = 0;
    *(uint8_t *)(this + 33) = 0;
    *(uint8_t *)(this + 34) = 0;
    sub_698F90(this + 20, 0, 0);
    *(uint32_t *)(this + 48) = 0;
    *(uint32_t *)(this + 53) = 16843009;
    *(uint32_t *)(this + 57) = 16843009;
    *(uint16_t *)(this + 61) = 257;
    *(uint8_t *)(this + 63) = 1;
    return this + 53;
  }
  v3 = sub_4CE8A0(1016);
  if ( v3 != 0
    && (v4 = *(uint32_t *)(dword_8F7A24 + 20),
        v7 = *(uint32_t *)(v3 + 124),
        *sub_472E30((int **)(v4 + 88), &v6, &v7) == *(int **)(v4 + 92)) )
  {
    if ( sub_47C080((uint32_t *)dword_8F8540, 1016) != 0 )
      return sub_5461C0((uint32_t *)this, 2);
    if ( sub_47B6F0((uint32_t *)dword_8F8540, 1016) != 0 )
    {
      v5 = (uint32_t *)dword_8F8540;
      if ( sub_461730((int *)dword_8F8540) < 3 )
      {
        sub_47B560(v5, 1016);
        return sub_5461C0((uint32_t *)this, 2);
      }
    }
    result = sub_5461C0((uint32_t *)this, 3);
    *(uint8_t *)(this + 55) = 1;
  }
  else
  {
    *(uint32_t *)(this + 16) = 3;
    *(uint8_t *)(this + 33) = 0;
    *(uint8_t *)(this + 34) = 0;
    result = sub_698F90(this + 20, 0, 0);
    *(uint32_t *)(this + 48) = 0;
    *(uint8_t *)(this + 55) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x546F30 sub_546F30 —— 引导清理（426BD0 + 698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_546F30(int this, void *Block)
{
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  char result; // al

  *(uint32_t *)(this + 4) = Block;
  *(uint32_t *)(this + 12) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 112);
  v3 = operator new(0x68u);
  if ( v3 != nullptr )
    v4 = sub_426BD0(v3);
  else
    v4 = nullptr;
  *(uint32_t *)(this + 8) = v4;
  *((uint32_t *)v4 + 17) = this;
  *(uint32_t *)(this + 16) = 1;
  *(uint8_t *)(this + 33) = 0;
  *(uint8_t *)(this + 34) = 0;
  result = sub_698F90(this + 20, 0, 0);
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 53) = 0;
  *(uint32_t *)(this + 57) = 0;
  *(uint16_t *)(this + 61) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint8_t *)(this + 64) = 0;
  *(uint8_t *)(this + 65) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x546FD0 sub_546FD0 —— 21 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_546FD0(uint32_t *this)
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
  return 0;
}



// ------------------------------------------------------------
// 0x547000 sub_547000 —— 引导数据（52 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_547000(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  uint32_t *v4; // edi
  int i; // ebx
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 1) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(this + 5) = 0;
  v4 = this + 6;
  for ( i = 4; i != 0; --i )
  {
    if ( *v4 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v4)(*v4, 1);
    *v4++ = 0;
  }
  v6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( v6 != nullptr )
    (**v6)(v6, 1);
  v7 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( v7 != nullptr )
    (**v7)(v7, 1);
  v8 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  *(this + 11) = 0;
  if ( v8 != nullptr )
    (**v8)(v8, 1);
  v9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  result = 0;
  *(this + 12) = 0;
  if ( v9 != nullptr )
    result = (**v9)(v9, 1);
  *(this + 13) = 0;
  return result;
}



// ============================================================
// 【分区 10】物品栏 CNRDItemInventoryWindow（0x5470A0-0x548D40）
// vmt8=Update（CLICK_BUTTON2/WINDOW_CLOSE）、vmt1C=内容刷新（318 行，
// 44F2E0/44F400/44F580/44F670 格子系列）、vmt18=按钮动作、vmt0=构造（202 行）。
// ============================================================
// ------------------------------------------------------------
// 0x5470A0 CNRDItemInventoryWindow__vmtC —— CNRDItemInventoryWindow__vmtC 打开槽（10 行）
// ------------------------------------------------------------
bool CNRDItemInventoryWindow__vmtC()
{
  return dword_8F7C04 != 0;
}



// ------------------------------------------------------------
// 0x5470B0 sub_5470B0 —— 物品栏格子参数（37 行）
// ------------------------------------------------------------
int /*stdcall*/ sub_5470B0(char a1)
{
  int v1; // edi
  LONG v2; // esi
  LONG v3; // eax
  int v4; // ecx

  v1 = 0;
  while ( 1 )
  {
    if ( a1 != 0 )
    {
      v2 = 32 * (v1 % 8) + 339;
      v3 = 32 * (v1 / 8) + 210;
    }
    else
    {
      v2 = 32 * (v1 % 8) + 337;
      v3 = 32 * (v1 / 8) + 208;
    }
    if ( pt.x >= v2 )
    {
      v4 = 4 * (a1 == 0) + 28;
      if ( pt.x < v4 + v2 && pt.y >= v3 && pt.y < v3 + v4 )
        break;
    }
    if ( ++v1 >= 32 )
      return -1;
  }
  return v1;
}



// ------------------------------------------------------------
// 0x547170 sub_547170 —— 物品格子查询（484FA0 + 422E70/44E8D0）
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_547170(int a1, char a2)
{
  int v2; // edi
  int v3; // esi
  char *v4; // eax
  char Buffer[1024]; // [esp+10h] [ebp-404h] BYREF
  int v7; // [esp+410h] [ebp-4h]

  v2 = *((uint32_t *)dword_8F852C + 1);
  v7 = dword_796E50;
  v3 = sub_484FA0() - v2 - a1;
  if ( v3 < 0 && a2 != 0 )
  {
    v4 = sub_422E70(412);
    sprintf(Buffer, v4, (double)(int)abs32(v3) * 0.001);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);
  }
  return v3 < 0;
}



// ------------------------------------------------------------
// 0x547210 CNRDItemInventoryWindow__vmt10 —— CNRDItemInventoryWindow__vmt10 状态切换（44AB50 + 5653D0 + 44E850 + 540960）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemInventoryWindow__vmt10(uint32_t *this)
{
  uint32_t *v2; // ecx
  int v3; // esi
  int v4; // ebx

  v2 = (uint32_t *)*(this + 2);
  v3 = v2[26];
  v4 = v2[27];
  if ( v3 == 6 || v3 == 9 || v3 == 10 )
    sub_44AB50(v2, 0, 12);
  if ( v3 == 2 )
  {
    if ( v4 != 1 )
      sub_44AB50((uint32_t *)*(this + 2), 0, 12);
  }
  else if ( v3 == 6 )
  {
    sub_5653D0(*(uint32_t *)(*(this + 2) + 80));
  }
  if ( dword_9B88D0 != 0 && dword_795378 == 1 )
    sub_44E850((uint32_t *)*(this + 2), 26);
  return sub_540960(*(uint32_t **)(*(this + 2) + 116));
}



// ------------------------------------------------------------
// 0x547290 sub_547290 —— 10 行小辅助
// ------------------------------------------------------------
int /*stdcall*/ sub_547290(int a1)
{
  return dword_724880[a1];
}



// ------------------------------------------------------------
// 0x5472B0 sub_5472B0 —— 10 行小辅助 2
// ------------------------------------------------------------
int /*stdcall*/ sub_5472B0(int a1)
{
  return dword_7248A8[a1];
}



// ------------------------------------------------------------
// 0x5472D0 sub_5472D0 —— 10 行小辅助 3
// ------------------------------------------------------------
bool sub_5472D0()
{
  return pt.x >= 332 && pt.x < 598 && pt.y >= 75 && pt.y < 178;
}



// ------------------------------------------------------------
// 0x547300 sub_547300 —— 物品栏数据（33 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_547300(int a1)
{
  int result; // eax

  switch ( a1 )
  {
    case 0:
      result = 9;
      break;
    case 1:
      result = 41;
      break;
    case 2:
      result = 73;
      break;
    case 3:
      result = 105;
      break;
    case 4:
      result = 137;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x547350 sub_547350 —— 物品栏条目（25 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_547350(int a1)
{
  int v1; // eax

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 16))(a1) + 4) <= 2u )
    return -1;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 20))(a1, 1) == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 20))(a1, 2) != 0 )
      return (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 172))(a1) > 7) - 1;
    return -1;
  }
  v1 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 132))(a1) - 1;
  if ( v1 == 0 )
    return 2;
  if ( v1 == 5 )
    return 3;
  return 1;
}



// ------------------------------------------------------------
// 0x5473D0 sub_5473D0 —— 物品栏辅助（484ED0）
// ------------------------------------------------------------
int /*thiscall*/ sub_5473D0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // edx
  int v5; // ecx

  result = sub_484ED0(a2);
  v4 = 3;
  while ( 1 )
  {
    switch ( v4 )
    {
      case 0:
        v5 = 9;
        break;
      case 1:
        v5 = 41;
        break;
      case 2:
        v5 = 73;
        break;
      case 3:
        v5 = 105;
        break;
      case 4:
        v5 = 137;
        break;
      default:
        v5 = 0;
        break;
    }
    if ( result >= v5 )
      break;
    if ( --v4 < 0 )
      return result;
  }
  *(this + 14) = v4;
  return result;
}



// ------------------------------------------------------------
// 0x547450 sub_547450 —— 物品栏格子重建（28 行）
// ------------------------------------------------------------
int sub_547450()
{
  int result; // eax
  int v1; // ecx
  LONG v2; // edx
  LONG v3; // esi

  result = 8;
  v1 = 0;
  while ( 1 )
  {
    v2 = dword_7248A0[v1];
    v3 = dword_7248C8[v1];
    if ( pt.x >= v2 && pt.x < v2 + 28 && pt.y >= v3 && pt.y < v3 + 28 )
      break;
    ++v1;
    ++result;
    if ( v1 >= 10 )
      return 18;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5474B0 CNRDItemInventoryWindow__vmt14 —— CNRDItemInventoryWindow__vmt14 关闭槽（87 行：5470B0/547300/541A30/541AF0/547450 + 44BC30/44A980）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemInventoryWindow__vmt14(int this)
{
  int v1; // edi
  int v4; // edi
  int v5; // eax
  uint32_t *v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  void *v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  void *v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // [esp-Ch] [ebp-18h]
  int v21; // [esp-Ch] [ebp-18h]
  int v22; // [esp+8h] [ebp-4h]

  v1 = dword_8F7C04;
  if ( dword_8F7C04 == 0 )
    return 0;
  if ( *(uint32_t *)(*(uint32_t *)(this + 8) + 2504) == 14 )
  {
    v4 = sub_5470B0(1);
    if ( v4 != -1 )
    {
      v5 = v4 + sub_547300(*(uint32_t *)(this + 56));
      if ( v5 < *((uint32_t *)dword_8F852C + 2) && *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v5) != 0 )
      {
        v6 = (uint32_t *)sub_541A30();
        v7 = sub_541AF0(v6);
        sub_541A30();
        v8 = sub_547300(*(uint32_t *)(this + 56));
        (*(void (/*stdcall*/ **)(int, int, uint32_t))(v9 + 64))(v4 + v8, v7, 0);
        sub_44ABE0(*(uint32_t **)(this + 8), 0);
        return 1;
      }
    }
    return 0;
  }
  v10 = *(uint32_t *)(this + 4);
  if ( *(uint8_t *)(v10 + 17) == 0 || dword_79BE3C != *(uint32_t *)(v10 + 12) )
    return 0;
  v11 = sub_547450();
  v12 = v11;
  if ( v11 != 18 )
  {
    v13 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v1 + 792))(v1, v11);
    if ( v13 != nullptr )
    {
      v14 = *(uint32_t *)(*(uint32_t *)(this + 8) + 2504);
      if ( v14 != 5 && v14 != 6 && v14 != 7 && v14 != 18 )
      {
        v20 = *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v13 + 16))(v13) + 68);
        v15 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v13 + 16))(v13);
        sub_44BC30(*(uint32_t **)(this + 8), (void *)2, 2, *(uint32_t *)(v15 + 4), v12, v20, v13);
      }
      return 1;
    }
  }
  v16 = sub_5470B0(1);
  if ( v16 == -1 )
    return 0;
  v22 = sub_547300(*(uint32_t *)(this + 56));
  v17 = (void *)sub_44A980(dword_8F852C, v16 + v22);
  if ( v17 == nullptr )
    return 0;
  v18 = *(uint32_t *)(*(uint32_t *)(this + 8) + 2504);
  if ( v18 != 5 && v18 != 6 && v18 != 7 && v18 != 18 )
  {
    v21 = *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v17 + 16))(v17) + 68);
    v19 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v17 + 16))(v17);
    sub_44BC30(*(uint32_t **)(this + 8), (void *)2, 3, *(uint32_t *)(v19 + 4), v16 + v22, v21, v17);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x547670 CNRDItemInventoryWindow__vmt18 —— CNRDItemInventoryWindow__vmt18 按钮动作（CLICK_BUTTON2 + 44BBA0 显示）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemInventoryWindow__vmt18(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // eax
  int v4; // eax
  int v5; // eax
  char result; // al

  if ( dword_8F7C04 == 0 )
    return 0;
  v2 = *(this + 1);
  if ( *(uint8_t *)(v2 + 17) == 0 )
    return 0;
  if ( dword_79BE3C != *(uint32_t *)(v2 + 12) )
    return 0;
  v3 = (uint32_t *)*(this + 2);
  if ( v3[626] != 2 )
    return 0;
  switch ( v3[627] )
  {
    case 2:
      v4 = (*(int (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(v3[629]);
      goto LABEL_10;
    case 3:
    case 4:
      v4 = sub_44A980(dword_8F852C, v3[629]);
      goto LABEL_10;
    case 5:
      v4 = sub_44A980(*(uint32_t **)(dword_8F8538 + 16), v3[629]);
      goto LABEL_10;
    case 8:
      v4 = sub_44A980(dword_8F8530, v3[629]);
LABEL_10:
      if ( v4 == 0 )
        goto LABEL_15;
      v5 = sub_547350(v4);
      if ( v5 == -1 )
      {
        sub_44BBA0((uint32_t *)*(this + 2), 1, 0);
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
      else if ( v5 != *(this + 14) )
      {
        *(this + 14) = v5;
        return 1;
      }
LABEL_15:
      result = 1;
      break;
    default:
      goto LABEL_15;
  }
  return result;
}



// ------------------------------------------------------------
// 0x547770 CNRDItemInventoryWindow__vmt1C —— CNRDItemInventoryWindow__vmt1C 内容刷新（318 行：44F2E0/44F400/44F580/44F670 格子系列 + 486820/486530 + 540DE0）
// ------------------------------------------------------------
char /*thiscall*/ sub_547770(int this)
{
  int v2; // eax
  uint32_t *v4; // ebx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // ebx
  int *v10; // eax
  int v11; // eax
  int v12; // esi
  int *v13; // eax
  int v14; // eax
  int v15; // edi
  int v16; // eax
  unsigned int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // edi
  int v21; // edi
  int v22; // esi
  int v23; // ebx
  int v24; // eax
  int v25; // eax
  int v26; // ebx
  int v27; // ebx
  int v28; // eax
  int v29; // eax
  int v30; // ebx
  int v31; // eax
  unsigned int v32; // eax
  int v33; // eax
  int v34; // edi
  int v35; // eax
  int *v36; // eax
  int v37; // eax
  int v38; // ebx
  int v39; // ecx
  int v40; // eax
  int v41; // eax
  int v42; // ebx
  int v43; // eax
  int v44; // eax
  int v45; // ecx
  int v46; // eax
  int v47; // eax
  uint32_t *v48; // [esp-10h] [ebp-28h]
  int v49; // [esp-Ch] [ebp-24h]
  uint32_t *v50; // [esp+4h] [ebp-14h]
  int v51; // [esp+4h] [ebp-14h]
  int v52; // [esp+4h] [ebp-14h]
  int v53; // [esp+8h] [ebp-10h]
  int v54; // [esp+Ch] [ebp-Ch]
  int v55; // [esp+Ch] [ebp-Ch]
  int v56; // [esp+10h] [ebp-8h]
  signed int v57; // [esp+10h] [ebp-8h]
  int v58; // [esp+10h] [ebp-8h]
  int v59; // [esp+10h] [ebp-8h]
  char v60; // [esp+17h] [ebp-1h]

  if ( dword_8F7C04 == 0 )
    return 0;
  v2 = *(uint32_t *)(this + 4);
  if ( *(uint8_t *)(v2 + 17) == 0 || dword_79BE34 != *(uint32_t *)(v2 + 12) )
    return 0;
  v4 = *(uint32_t **)(this + 8);
  v5 = v4[626];
  v50 = v4;
  if ( v5 == 5 || v5 == 6 || v5 == 7 || v5 == 18 )
  {
    v41 = sub_547450(this);
    v42 = v41;
    if ( v41 == 18 )
    {
      if ( sub_5470B0(1) == -1 )
        return 0;
      v44 = sub_547300(*(uint32_t *)(this + 56));
      v46 = v45 + v44;
      if ( v46 >= *((uint32_t *)dword_8F852C + 2) )
        return 0;
      v43 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v46);
    }
    else
    {
      v43 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, v41);
    }
    if ( v43 == 0 )
      return 0;
    switch ( v5 )
    {
      case 5:
        sub_44F2E0(v43, 1);
        return 1;
      case 6:
        sub_44F400(v43, 1);
        return 1;
      case 7:
        if ( v42 == 18 )
        {
          sub_44F580(v43, 1);
          return 1;
        }
        v47 = sub_422E70(413);
        break;
      default:
        if ( v42 == 18 )
        {
          sub_44F670(v43, 1);
          return 1;
        }
        v47 = sub_422E70(1651);
        break;
    }
    sub_44E8D0(*(char **)(this + 8), (void *)0x1B, v47, 0);
    return 1;
  }
  if ( v5 != 2 )
    return 0;
  v60 = sub_5472D0(this);
  v6 = v4[627];
  switch ( v6 )
  {
    case 2:
      v7 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, v4[629]);
      v8 = v7;
      if ( v7 == 0 )
        return 0;
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 16))(v7) + 4) != v4[628] )
        return 0;
      v9 = sub_5470B0(0);
      if ( v9 == -1 )
        return 0;
      v51 = sub_547300(*(uint32_t *)(this + 56));
      v10 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 172))(v8);
      if ( sub_486820((int *)dword_8F852C, v9 + v51, *v10, 1) == 0 )
      {
        v11 = sub_547300(*(uint32_t *)(this + 56));
        v12 = v11 + v9;
        v52 = v11;
        if ( sub_44A980(v11 + v9) != 0 )
        {
          v54 = 0;
          while ( sub_44A980(v12) != 0 )
          {
            if ( ++v54 >= 32 )
              return 0;
          }
          v13 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 172))(v8);
          sub_486820((int *)dword_8F852C, v9 + v52, *v13, 1);
          return 1;
        }
        return 0;
      }
      return 1;
    case 3:
    case 4:
      v34 = sub_44A980(v4[629]);
      if ( v34 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v34 + 16))(v34) + 4) == v4[628] )
      {
        if ( v60 != 0 )
        {
          v35 = __RTDynamicCast(v34, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
          if ( v35 != 0 && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v35 + 172))(v35) >= 8 )
          {
            v36 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v34 + 172))(v34);
            sub_486820((int *)dword_8F852C, v4[629], *v36, 1);
            return 1;
          }
        }
        else if ( sub_5470B0(0) != -1 )
        {
          v37 = sub_547300(*(uint32_t *)(this + 56));
          v38 = v4[629];
          v40 = v39 + v37;
          if ( v40 != v38 )
          {
            sub_486530(dword_8F852C, v40, v38, 1);
            return 1;
          }
        }
      }
      return 0;
    case 8:
      v14 = sub_44A980(v4[629]);
      v15 = v14;
      if ( v14 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 16))(v14) + 4) == v4[628] && v60 != 1 )
      {
        v56 = sub_5470B0(0);
        if ( v56 != -1 )
        {
          v57 = sub_547300(*(uint32_t *)(this + 56)) + v56;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 20))(v15, 1) != 0
            && (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 44))(v15) > 1 )
          {
            sub_540DE0(1, 2, v4[629], 0, v57, 0, 0);
            return 1;
          }
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 36))(v15);
          if ( (uint8_t)sub_547170(v16, 1) != 1 )
          {
            v48 = dword_8F852C;
            v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 44))(v15);
            sub_4866D0(dword_8F8530, v4[629], v17, v48, v57);
            return 1;
          }
        }
      }
      return 0;
    case 9:
      return 0;
    default:
      break;
  }
  if ( v6 != 5 )
  {
    if ( v6 == 10 )
    {
      v33 = sub_541A30();
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v33 + 72))(v33, v4[629]);
      return 0;
    }
    return 0;
  }
  v18 = sub_44A980(v4[629]);
  if ( v18 == 0 )
    return 0;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 16))(v18) + 4) != v4[628] )
    return 0;
  v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 16))(v18);
  if ( sub_4F2D40(*(uint32_t *)(v19 + 4)) == 2 && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 172))(v18) <= 7 )
    return 0;
  if ( v60 == 0 || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v18 + 20))(v18, 2) == 0 )
  {
    v23 = sub_5470B0(0);
    v55 = v23;
    if ( v23 != -1 )
    {
      v24 = sub_547300(*(uint32_t *)(this + 56));
      v25 = sub_44A980(v23 + v24);
      if ( v25 != 0 )
      {
        v26 = v25;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v25 + 20))(v25, 1) == 0
          || *(uint32_t *)((v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v26 + 16))(v26)) + 4) != *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 16))(v18) + 4) )
        {
          v23 = -1;
          v55 = -1;
          goto LABEL_54;
        }
        v23 = v55;
      }
LABEL_65:
      if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 44))(v18) <= 1 )
      {
        v49 = v23 + sub_547300(*(uint32_t *)(this + 56));
        v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 44))(v18);
        sub_484AF0(dword_8F8538, v50[629], v32, 0, v49);
      }
      else
      {
        v31 = sub_547300(*(uint32_t *)(this + 56));
        sub_540DE0(1, 4, v50[629], 0, v23 + v31, 0, 0);
      }
      return 1;
    }
LABEL_54:
    v59 = 0;
    while ( 1 )
    {
      v28 = sub_547300(*(uint32_t *)(this + 56));
      v29 = sub_44A980(v23 + v28);
      v53 = v29;
      if ( v29 == 0 )
        break;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v29 + 20))(v29, 1) != 0 )
      {
        v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 16))(v18);
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v53 + 16))(v53) + 4) == *(uint32_t *)(v30 + 4) )
          break;
        v23 = v55;
      }
      if ( ++v59 >= 32 )
        goto LABEL_62;
    }
    v23 = v59;
LABEL_62:
    if ( v23 == -1 )
      return 0;
    goto LABEL_65;
  }
  v20 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 172))(v18);
  v58 = v20;
  if ( v20 < 8 )
    return 0;
  if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, v20) != 0 )
  {
    v21 = 0;
    v22 = sub_547300(*(uint32_t *)(this + 56));
    while ( sub_44A980(v22 + v21) != 0 )
    {
      if ( ++v21 >= 32 )
      {
        sub_484AF0(dword_8F8538, v4[629], 1u, 3u, v58);
        return 1;
      }
    }
    sub_486820((int *)dword_8F852C, v21 + v22, v58, 1);
    v20 = v58;
  }
  sub_484AF0(dword_8F8538, v4[629], 1u, 3u, v20);
  return 1;
}


// ------------------------------------------------------------
// 0x547E80 CNRDItemInventoryWindow__vmt28 —— CNRDItemInventoryWindow__vmt28 槽（4872A0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemInventoryWindow__vmt28(int *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ecx

  v2 = *(this + 1);
  if ( *(uint8_t *)(v2 + 17) == 0
    || dword_79BE38 != *(uint32_t *)(v2 + 12)
    || *(uint32_t *)(*(this + 2) + 2504) != 0
    || sub_5470B0(1) == -1 )
  {
    return 0;
  }
  v3 = sub_547300(*(this + 14));
  sub_4872A0(v4 + v3);
  return 1;
}



// ------------------------------------------------------------
// 0x547EE0 CNRDItemInventoryWindow__vmt8 —— CNRDItemInventoryWindow__vmt8 Update（134 行：CLICK_BUTTON2/WINDOW_CLOSE + 486C40/540DE0 格子点击）
// ------------------------------------------------------------
char /*thiscall*/ sub_547EE0(char *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // esi
  int v5; // edx
  char *v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // ebx
  int64_t v14; // rax
  int v15; // ecx
  int v16; // esi
  int v17; // ebx
  int v18; // eax
  int v19; // ebx

  if ( dword_8F7C04 != 0 )
  {
    v3 = *((uint32_t *)this + 5);
    v4 = dword_79BE34;
    if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
    {
      (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 44))(this);
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      LOBYTE(v2) = (uint8_t)sub_432EA0("WINDOW_CLOSE", -1, 0, 0);
    }
    else
    {
      v5 = 0;
      v6 = this + 24;
      while ( *(uint8_t *)(*(uint32_t *)v6 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*(uint32_t *)v6 + 12) )
      {
        ++v5;
        v6 += 4;
        if ( v5 >= 4 )
          goto LABEL_12;
      }
      *((uint32_t *)this + 14) = v5;
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      v4 = dword_79BE34;
LABEL_12:
      v7 = *((uint32_t *)this + 10);
      if ( *(uint8_t *)(v7 + 17) != 0 && v4 == *(uint32_t *)(v7 + 12) )
      {
        sub_44BBA0(1, 0);
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        v4 = dword_79BE34;
      }
      v8 = *((uint32_t *)this + 11);
      if ( *(uint8_t *)(v8 + 17) != 0 && v4 == *(uint32_t *)(v8 + 12) )
      {
        sub_486C40(dword_8F852C, v5);
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        v4 = dword_79BE34;
      }
      v9 = *((uint32_t *)this + 12);
      if ( *(uint8_t *)(v9 + 17) != 0 && v4 == *(uint32_t *)(v9 + 12) )
      {
        v10 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v10 == 1 || v10 == 4 || v10 == 6 )
        {
          sub_540DE0(0, 0, 0, 7, 0, 0, 0);
        }
        else if ( v10 == 3 )
        {
          sub_540DE0(4, 0, 0, 7, 0, 0, 0);
        }
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        v4 = dword_79BE34;
      }
      v11 = *(uint32_t *)(*((uint32_t *)this + 2) + 2504);
      if ( v11 == 1 )
        goto LABEL_40;
      if ( v11 == 2 )
        goto LABEL_40;
      v12 = *((uint32_t *)this + 1);
      if ( *(uint8_t *)(v12 + 17) == 0 )
        goto LABEL_40;
      v13 = *(uint32_t *)(v12 + 12);
      if ( dword_79BE3C != v13 && v4 != v13 && dword_79BE38 != v13 )
        goto LABEL_40;
      if ( sub_5470B0(1) != -1 )
      {
        v14 = sub_547300(*((uint32_t *)this + 14));
        LODWORD(v14) = HIDWORD(v14) + v14;
        v15 = (int)v14 >= *((uint32_t *)dword_8F852C + 2) ? 0 : *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v14);
        v2 = ((SHIDWORD(v14) >> 31) & 7) + HIDWORD(v14);
        v16 = 32 * (SHIDWORD(v14) % 8) + 339;
        v17 = 32 * (SHIDWORD(v14) / 8) + 210;
        if ( v15 != 0 )
          goto LABEL_50;
      }
      v18 = sub_547450(this);
      v19 = v18;
      if ( v18 != 18
        && (v2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, v18),
            v16 = dword_724880[v19],
            v17 = dword_7248A8[v19],
            v15 = v2,
            v2 != 0) )
      {
LABEL_50:
        if ( dword_9B88D0 != v15 || dword_795378 != 1 )
        {
          v2 = sub_44E8D0(*((char **)this + 2), (void *)0x1A, v15, 1);
          if ( v2 != 0 )
            LOBYTE(v2) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v2 + 48))(v2, v16, v17, 28, 28);
        }
      }
      else
      {
LABEL_40:
        LOBYTE(v2) = dword_9B88D0;
        if ( dword_9B88D0 != 0 && dword_795378 == 1 )
          LOBYTE(v2) = sub_44E850(*((uint32_t **)this + 2), 26);
      }
    }
  }
  else
  {
    LOBYTE(v2) = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 44))(this);
  }
  return v2;
}


// ------------------------------------------------------------
// 0x5481A0 sub_5481A0 —— 物品栏页绘制（153 行：43C250/43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0 + 699E20/699E40）
// ------------------------------------------------------------
char /*thiscall*/ sub_5481A0(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int v5; // ebx
  uint32_t *v6; // edi
  uint8_t *v7; // eax
  uint8_t *v8; // eax
  uint8_t *v9; // eax
  uint32_t *v10; // edi
  int v11; // ebx
  uint8_t *v12; // eax
  uint32_t *v13; // edi
  int v14; // ebx
  uint8_t *v15; // edi
  int v16; // ebx
  uint8_t *v17; // eax
  uint8_t *v18; // edi
  int v19; // ebx
  char result; // al
  void *Block; // [esp+10h] [ebp-10h]

  *(this + 4) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 16);
  if ( operator new(0x6Cu) != nullptr )
    v2 = sub_43C250(*(this + 4), 0);
  else
    v2 = 0;
  *(this + 1) = v2;
  *(uint32_t *)(v2 + 28) = *(uint32_t *)(v2 + 28);
  *(uint32_t *)(v2 + 32) = 383;
  *(uint32_t *)(*(this + 1) + 68) = this;
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 11, 12, 13, 11, 0, 0);
  else
    v4 = nullptr;
  *(this + 5) = v4;
  sub_69A5F0(v4, 51, 383);
  sub_69A840(*(this + 5));
  v5 = 19;
  v6 = this + 6;
  do
  {
    v7 = operator new(0x68u);
    if ( v7 != nullptr )
      v8 = sub_426BD0(v7);
    else
      v8 = nullptr;
    *v6 = v8;
    *((uint32_t *)v8 + 7) = 64;
    *((uint32_t *)v8 + 8) = 20;
    sub_69A5F0((uint32_t *)*v6, v5, 153);
    sub_69A840(*v6);
    v5 += 64;
    ++v6;
  }
  while ( v5 < 275 );
  v9 = operator new(0x84u);
  v10 = v9;
  if ( v9 != nullptr )
  {
    v11 = *(this + 4);
    sub_426BD0(v9);
    *v10 = &nengine::CNButton::`vftable';
    sub_69C780(v10);
    sub_69C7B0(v11, 7, 8, 8, 7, 0, 0);
  }
  else
  {
    v10 = nullptr;
  }
  *(this + 10) = v10;
  sub_69A5F0(v10, 10, 0);
  sub_69A840(*(this + 10));
  v12 = operator new(0x84u);
  v13 = v12;
  if ( v12 != nullptr )
  {
    v14 = *(this + 4);
    sub_426BD0(v12);
    *v13 = &nengine::CNButton::`vftable';
    sub_69C780(v13);
    sub_69C7B0(v14, 1, 2, 3, 1, 0, 0);
  }
  else
  {
    v13 = nullptr;
  }
  *(this + 11) = v13;
  sub_69A5F0(v13, 229, 309);
  sub_69A840(*(this + 11));
  v15 = operator new(0x84u);
  if ( v15 != nullptr )
  {
    v16 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 24);
    sub_426BD0(v15);
    *(uint32_t *)v15 = &nengine::CNButton::`vftable';
    sub_69C780(v15);
    sub_69C7B0(v16, 1, 2, 3, 7, 0, 0);
  }
  else
  {
    v15 = nullptr;
  }
  *(this + 12) = v15;
  sub_69A5F0(v15, 19, 344);
  sub_69A840(*(this + 12));
  sub_69A5F0((uint32_t *)*(this + 1), 320, 33);
  v17 = operator new(0x2Cu);
  v18 = v17;
  if ( v17 != nullptr )
  {
    v19 = *(this + 4);
    Block = (void *)dword_79C0B0;
    v17[4] = 0;
    *(uint32_t *)v17 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v17);
    sub_699E40(Block, v19, 25, 4);
  }
  else
  {
    v18 = nullptr;
  }
  *(this + 13) = v18;
  v18[24] = 1;
  result = byte_9B8054;
  if ( byte_9B8054 == 0 )
  {
    byte_7947AC = 0;
    byte_7947AD = 0;
    byte_7947AE = 0;
    byte_7947AF = 0;
    dword_7947BC = 6;
    dword_7947C0 = 12;
    dword_7947C4 = 0;
    dword_7947CC = 0;
    dword_7947D0 = 0;
    dword_7947D4 = 0;
    dword_7947D8 = 0;
    dword_7947DC = dword_99FCCC;
    dword_7947B8 = 2;
    dword_7947C8 = 120;
    byte_9B8054 = 1;
    return 0;
  }
  return result;
}


// ------------------------------------------------------------
// 0x548540 sub_548540 —— 物品栏文本（4015C0/401740）
// ------------------------------------------------------------
int /*thiscall*/ sub_548540(uint32_t *this, unsigned int a2)
{
  int v2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  v2 = *(this + 2);
  if ( 0x7FFFFFF - v2 < a2 )
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);
    v8 = 0;
    sub_401740(v5);
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = a2 + v2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x5485D0 sub_5485D0 —— 物品栏辅助（5014C0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5485D0(uint32_t *this)
{
  uint32_t **v2; // eax
  uint32_t *v3; // esi
  uint32_t *result; // eax
  bool v5; // zf
  uint32_t *v6; // ebx

  v2 = (uint32_t **)*(this + 1);
  v3 = *v2;
  *v2 = v2;
  result = (uint32_t *)*(this + 1);
  result[1] = result;
  v5 = v3 == (uint32_t *)*(this + 1);
  *(this + 2) = 0;
  if ( !v5 )
  {
    do
    {
      v6 = (uint32_t *)*v3;
      sub_5014C0(v3);
      j__free(v3);
      result = (uint32_t *)*(this + 1);
      v3 = v6;
    }
    while ( v6 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x548610 sub_548610 —— 物品栏文本 2（4014D0）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_548610(int a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // eax
  uint32_t *v4; // esi
  void *v6[9]; // [esp+0h] [ebp-24h] BYREF

  v6[5] = v6;
  v3 = operator new(0x28u);
  v4 = v3;
  v6[4] = v3;
  v6[8] = (void *)1;
  v6[3] = v3;
  if ( v3 != nullptr )
  {
    *v3 = a1;
    v3[1] = a2;
    v3[2] = *a3;
    v3[9] = 15;
    v3[8] = 0;
    *((uint8_t *)v3 + 16) = 0;
    sub_4014D0((std::_String_base *)(v3 + 3), a3 + 1, 0, -1);
  }
  return v4;
}



// ------------------------------------------------------------
// 0x5486B0 sub_5486B0 —— 物品栏标题组装（4015C0/4014D0/548610/548540，113 行）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_5486B0(int a1)
{
  uint32_t *v1; // eax
  unsigned int v2; // edx
  signed int v3; // ecx
  int v4; // edi
  signed int i; // esi
  int v7; // esi
  uint32_t *v8; // edi
  void *v9; // esi
  int v10; // [esp-14h] [ebp-C4h]
  int v11; // [esp-10h] [ebp-C0h]
  int v12; // [esp+4h] [ebp-ACh] BYREF
  uint8_t v13[4]; // [esp+8h] [ebp-A8h] BYREF
  void *Block; // [esp+Ch] [ebp-A4h]
  int v15; // [esp+1Ch] [ebp-94h]
  unsigned int v16; // [esp+20h] [ebp-90h]
  uint8_t v17[4]; // [esp+24h] [ebp-8Ch] BYREF
  void *v18; // [esp+28h] [ebp-88h]
  int v19; // [esp+38h] [ebp-78h]
  unsigned int v20; // [esp+3Ch] [ebp-74h]
  char Src[64]; // [esp+40h] [ebp-70h] BYREF
  char Buffer[32]; // [esp+80h] [ebp-30h] BYREF
  int v23; // [esp+A0h] [ebp-10h]
  int v24; // [esp+ACh] [ebp-4h]

  v23 = dword_796E50;
  v1 = *(uint32_t **)dword_9B805C;
  if ( *(uint32_t *)dword_9B805C == dword_9B805C )
  {
LABEL_4:
    sprintf(Buffer, "%d", a1);
    v2 = (strlen(Buffer) - 1) / 3;
    Src[v2 + strlen(Buffer)] = 0;
    v3 = strlen(Buffer) + v2 - 1;
    v4 = 0;
    for ( i = strlen(Buffer) - 1; v3 >= 0; ++v4 )
    {
      if ( i < 0 )
        break;
      if ( v4 % 4 == 3 )
        Src[v3] = 44;
      else
        Src[v3] = Buffer[i--];
      --v3;
    }
    v20 = 15;
    v19 = 0;
    LOBYTE(v18) = 0;
    sub_4015C0(Src, strlen(Src));
    v12 = a1;
    v24 = 0;
    v16 = 15;
    v15 = 0;
    LOBYTE(Block) = 0;
    sub_4014D0((std::_String_base *)v13, v17, 0, -1);
    v7 = *(uint32_t *)dword_9B805C;
    v11 = *(uint32_t *)(*(uint32_t *)dword_9B805C + 4);
    v10 = *(uint32_t *)dword_9B805C;
    LOBYTE(v24) = 1;
    v8 = sub_548610(v10, v11, &v12);
    sub_548540(&dword_9B8058, 1u);
    *(uint32_t *)(v7 + 4) = v8;
    *(uint32_t *)v8[1] = v8;
    if ( v16 >= 0x10 )
      j__free(Block);
    v16 = 15;
    v15 = 0;
    LOBYTE(Block) = 0;
    v24 = -1;
    if ( v20 >= 0x10 )
      j__free(v18);
    v20 = 15;
    v19 = 0;
    LOBYTE(v18) = 0;
    if ( (unsigned int)dword_9B8060 > 0xA )
    {
      v9 = *(void **)(dword_9B805C + 4);
      if ( v9 != (void *)dword_9B805C )
      {
        **((uint32_t **)v9 + 1) = *(uint32_t *)v9;
        *(uint32_t *)(*(uint32_t *)v9 + 4) = *((uint32_t *)v9 + 1);
        if ( *((uint32_t *)v9 + 9) >= 0x10u )
          j__free(*((void **)v9 + 4));
        *((uint32_t *)v9 + 9) = 15;
        *((uint32_t *)v9 + 8) = 0;
        *((uint8_t *)v9 + 16) = 0;
        j__free(v9);
        --dword_9B8060;
      }
    }
    return (uint32_t *)sub_5486B0(a1);
  }
  else
  {
    while ( v1[2] != a1 )
    {
      v1 = (uint32_t *)*v1;
      if ( v1 == (uint32_t *)dword_9B805C )
        goto LABEL_4;
    }
    if ( v1[9] < 0x10u )
      return v1 + 4;
    else
      return (uint32_t *)v1[4];
  }
}



// ------------------------------------------------------------
// 0x548930 CNRDItemInventoryWindow__vmt0 —— CNRDItemInventoryWindow__vmt0 构造（202 行：4CE8A0 + 547450/4F2E40/5470B0/5486B0 + 69A110/484FA0/488670）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_548930(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  uint32_t *v3; // edx
  int v4; // eax
  int v5; // ecx
  int *v6; // esi
  unsigned int v7; // ecx
  int v8; // edi
  int v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // edi
  int j; // esi
  int v14; // eax
  int v15; // ebx
  uint32_t *v16; // edi
  int v17; // eax
  int v18; // eax
  int v19; // eax
  uint32_t *v20; // edx
  int k; // esi
  int v22; // eax
  int v23; // eax
  int v24; // ecx
  int v25; // ecx
  int v26; // eax
  int v27; // esi
  int v28; // eax
  int v29; // eax
  int v30; // esi
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // esi
  int v35; // eax
  uint64_t v36; // rax
  uint32_t *v37; // ecx
  int v38; // eax
  int i; // [esp+0h] [ebp-10h]
  int v40; // [esp+4h] [ebp-Ch]
  int v41; // [esp+8h] [ebp-8h]

  result = (uint32_t *)dword_8F7C04;
  v3 = this;
  if ( dword_8F7C04 == 0 )
    return result;
  result = (uint32_t *)a2;
  if ( a2 != *(this + 1) )
    return result;
  v4 = -12 - (uint32_t)this;
  v5 = -14 - (uint32_t)this;
  v41 = 0;
  v6 = v3 + 6;
  v40 = -12 - (uint32_t)v3;
  for ( i = -14 - (uint32_t)v3; ; v5 = i )
  {
    v7 = (unsigned int)v6 + v5;
    if ( v3[14] != v41 )
      v7 = (unsigned int)v6 + v4;
    v8 = *v6;
    if ( *(uint8_t *)(*v6 + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(v8 + 12)
       || dword_79BE34 == *(uint32_t *)(v8 + 12)
       || dword_79BE38 == *(uint32_t *)(v8 + 12)) )
    {
      ++v7;
    }
    v9 = *(uint32_t *)(*v6 + 24);
    v10 = *(uint32_t *)(*v6 + 20);
    v11 = sub_418DD0((uint32_t *)v3[4], v7);
    if ( v11 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(v11, v10, v9, dword_79C0B0);
    ++v6;
    if ( ++v41 >= 4 )
      break;
    v4 = v40;
    v3 = this;
  }
  v12 = 8;
  for ( j = 0; j < 10; ++j )
  {
    v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, v12);
    if ( v14 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)v14 + 8))(
        v14,
        dword_7248A0[j],
        dword_7248C8[j],
        0,
        1);
    ++v12;
  }
  if ( pt.x < 332 || pt.x >= 598 || pt.y < 75 || pt.y >= 178 )
  {
    v15 = a2;
  }
  else
  {
    v15 = a2;
    if ( *(uint8_t *)(a2 + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(a2 + 12)
       || dword_79BE34 == *(uint32_t *)(a2 + 12)
       || dword_79BE38 == *(uint32_t *)(a2 + 12)) )
    {
      v16 = this;
      v17 = *(this + 2);
      if ( *(uint32_t *)(v17 + 2504) != 2
        || (v18 = sub_4CE8A0((uint32_t *)dword_8F84D0, *(uint32_t *)(v17 + 2512))) == 0
        || (v19 = *(uint32_t *)(v18 + 92)) < 8 )
      {
        v19 = sub_547450(this);
      }
      if ( v19 != 18 )
        sub_4F2E40(dword_724880[v19], dword_7248A8[v19]);
      goto LABEL_35;
    }
  }
  v16 = this;
LABEL_35:
  v20 = dword_8F852C;
  for ( k = 0; k < 32; ++k )
  {
    switch ( v16[14] )
    {
      case 0:
        v22 = 9;
        break;
      case 1:
        v22 = 41;
        break;
      case 2:
        v22 = 73;
        break;
      case 3:
        v22 = 105;
        break;
      case 4:
        v22 = 137;
        break;
      default:
        v22 = 0;
        break;
    }
    v23 = k + v22;
    if ( v23 < v20[2] )
    {
      v24 = *(uint32_t *)(v20[3] + 4 * v23);
      if ( v24 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, unsigned int, uint32_t, int))(*(uint32_t *)v24 + 8))(
          v24,
          32 * (k & 7) + 339,
          32 * ((unsigned int)k >> 3) + 210,
          0,
          1);
        v20 = dword_8F852C;
      }
    }
  }
  if ( *(uint8_t *)(v15 + 17) != 0 )
  {
    if ( dword_79BE3C == *(uint32_t *)(v15 + 12)
      || (v25 = *(uint32_t *)(v15 + 12), dword_79BE34 == v25)
      || dword_79BE38 == v25 )
    {
      v26 = sub_5470B0(1);
      if ( v26 != -1 )
        sub_4F2E40(32 * (v26 % 8) + 339, 32 * (v26 / 8) + 210);
    }
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);
  v27 = *(uint32_t *)dword_79C0B0;
  v28 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));
  v29 = sub_5486B0(v28);
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(v27 + 80))(dword_79C0B0, 333, 382, -4265479, v29);
  v30 = *(uint32_t *)dword_79C0B0;
  v31 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8));
  v32 = sub_5486B0(v31);
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(v30 + 80))(dword_79C0B0, 462, 382, -4265479, v32);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  v33 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(
          *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4),
          -1);
  sub_69A110(366, 347, v33, (int)&byte_7947AC);
  v34 = *((uint32_t *)dword_8F852C + 1);
  v35 = sub_484FA0();
  v36 = (uint64_t)sub_4049C0(0.0, 90.0, v34, v35);
  v37 = (uint32_t *)dword_79C0B0;
  *(uint32_t *)(dword_79C0B0 + 48) = 0;
  v37[13] = 0;
  v37[14] = v36 + 445;
  v37[15] = 480;
  v38 = sub_418DD0((uint32_t *)v16[4], 5u);
  if ( v38 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v38 + 152))(v38, 445, 349, dword_79C0B0);
  return sub_488670((uint32_t *)dword_79C0B0);
}


// ============================================================
// 【分区 11】时装栏 CNRDAvatarInventoryWindow（0x548D40-0x549AC0）
// 结构与物品栏同构：vmt1C=刷新（182 行）、vmt8=Update（CLICK_BUTTON2/
// WINDOW_CLOSE）、vmt14=关闭清理（44BC30）。
// ============================================================
// ------------------------------------------------------------
// 0x548D40 sub_548D40 —— 52 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_548D40(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  uint32_t *v6; // edi
  int i; // ebx
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 4);
  *(this + 1) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 4) = 0;
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  *(this + 5) = 0;
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  *(this + 6) = 0;
  v6 = this + 7;
  for ( i = 2; i != 0; --i )
  {
    if ( *v6 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v6)(*v6, 1);
    *v6++ = 0;
  }
  v8 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( v8 != nullptr )
    (**v8)(v8, 1);
  v9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  result = 0;
  *(this + 9) = 0;
  if ( v9 != nullptr )
    result = (**v9)(v9, 1);
  *(this + 10) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x548DE0 CNRDAvatarInventoryWindow__vmtC —— CNRDAvatarInventoryWindow__vmtC 打开槽（429830 + 42B340）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAvatarInventoryWindow__vmtC(int this)
{
  bool v1; // zf
  int v4; // eax

  v1 = dword_8F7C04 == 0;
  *(uint32_t *)(this + 44) = dword_8F7C04;
  if ( v1 )
    return 0;
  v4 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  sub_42B340(v4);
  (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 40) + 32))(*(uint32_t *)(this + 40), 12);
  return 1;
}



// ------------------------------------------------------------
// 0x548E20 sub_548E20 —— 时装栏数据（44 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_548E20(uint32_t *this, char a2)
{
  LONG x; // ebx
  int v3; // edi
  int v4; // eax
  int v5; // edx
  LONG v6; // edx
  LONG v7; // eax
  int v8; // esi

  x = pt.x;
  v3 = 0;
  while ( 1 )
  {
    v4 = v3 / 7;
    v5 = 32 * (v3 % 7);
    if ( a2 != 0 )
    {
      v6 = v5 + 349;
      v7 = 32 * v4 + 243;
    }
    else
    {
      v6 = v5 + 347;
      v7 = 32 * v4 + 241;
    }
    if ( x >= v6 )
    {
      v8 = 4 * (a2 == 0) + 28;
      x = pt.x;
      if ( pt.x < v8 + v6 && pt.y >= v7 && pt.y < v7 + v8 )
        break;
    }
    if ( ++v3 >= 21 )
      return -1;
  }
  return v3 + 7 * *(this + 12);
}



// ------------------------------------------------------------
// 0x548EC0 CNRDAvatarInventoryWindow__vmt10 —— CNRDAvatarInventoryWindow__vmt10 状态切换（44AB50 + 44E850 + 540960）
// ------------------------------------------------------------
int /*thiscall*/ CNRDAvatarInventoryWindow__vmt10(uint32_t *this)
{
  uint32_t *v2; // ecx
  int v3; // eax
  int result; // eax

  v2 = (uint32_t *)*(this + 2);
  v3 = v2[26];
  if ( (v3 == 9 || v3 == 2) && v2[27] != 0 )
    sub_44AB50(v2, 0, 12);
  if ( dword_9B88D0 != 0 && dword_795378 == 2 )
    sub_44E850((uint32_t *)*(this + 2), 26);
  result = sub_540960(*(uint32_t **)(*(this + 2) + 116));
  *(this + 11) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x548F20 sub_548F20 —— 10 行小辅助
// ------------------------------------------------------------
bool sub_548F20()
{
  return pt.x >= 332 && pt.x < 599 && pt.y >= 74 && pt.y < 232;
}



// ------------------------------------------------------------
// 0x548F50 CNRDAvatarInventoryWindow__vmt18 —— CNRDAvatarInventoryWindow__vmt18 按钮动作（CLICK_BUTTON2 + 44BBA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAvatarInventoryWindow__vmt18(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // esi
  int v8; // eax

  if ( dword_8F7C04 == 0 )
    return 0;
  v2 = *(this + 1);
  if ( *(uint8_t *)(v2 + 17) == 0 )
    return 0;
  if ( dword_79BE3C != *(uint32_t *)(v2 + 12) )
    return 0;
  v3 = (uint32_t *)*(this + 2);
  if ( v3[626] != 2 )
    return 0;
  if ( v3[627] == 5 )
  {
    v4 = *(uint32_t *)(dword_8F8538 + 16);
    v5 = v3[629];
    if ( v5 < *(uint32_t *)(v4 + 8) )
    {
      v6 = *(uint32_t *)(v4 + 12);
      v7 = *(uint32_t *)(v6 + 4 * v5);
      if ( v7 != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v7 + 16))(*(uint32_t *)(v6 + 4 * v5));
        if ( sub_4F2D40(*(uint32_t *)(v8 + 4)) != 2 || *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 172))(v7) > 7 )
        {
          sub_44BBA0((uint32_t *)*(this + 2), 0, 0);
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        }
      }
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x549000 sub_549000 —— 时装栏数据 2（24 行）
// ------------------------------------------------------------
int sub_549000()
{
  int result; // eax
  LONG v1; // ecx
  LONG v2; // edx

  result = 0;
  while ( 1 )
  {
    v1 = dword_724904[result];
    v2 = dword_724924[result];
    if ( pt.x >= v1 && pt.x < v1 + 28 && pt.y >= v2 && pt.y < v2 + 28 )
      break;
    if ( ++result > 7 )
      return 18;
  }
  return result;
}



// ------------------------------------------------------------
// 0x549050 CNRDAvatarInventoryWindow__vmt14 —— CNRDAvatarInventoryWindow__vmt14 关闭槽（549000 + 44BC30 + 548E20）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAvatarInventoryWindow__vmt14(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ebx
  int v5; // eax
  void *v6; // esi
  int v7; // eax
  int v9; // ebx
  int v10; // ecx
  int v11; // esi
  int v12; // eax
  int v13; // [esp-8h] [ebp-14h]
  int v14; // [esp-8h] [ebp-14h]
  void *v15; // [esp-4h] [ebp-10h]

  v2 = *(uint32_t *)(this + 4);
  if ( *(uint8_t *)(v2 + 17) == 0 || dword_79BE3C != *(uint32_t *)(v2 + 12) )
    return 0;
  v3 = sub_549000();
  v4 = v3;
  if ( v3 != 18 )
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 44) + 792))(*(uint32_t *)(this + 44), v3);
    v6 = (void *)v5;
    if ( v5 != 0 )
    {
      v13 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 16))(v5) + 68);
      v7 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v6 + 16))(v6);
      sub_44BC30(*(uint32_t **)(this + 8), (void *)2, 6, *(uint32_t *)(v7 + 4), v4, v13, v6);
      return 1;
    }
  }
  v9 = sub_548E20((uint32_t *)this, 1);
  if ( v9 == -1 )
    return 0;
  if ( v9 >= *((uint32_t *)dword_8F8534 + 2) )
    return 0;
  v10 = *((uint32_t *)dword_8F8534 + 3);
  v11 = *(uint32_t *)(v10 + 4 * v9);
  if ( v11 == 0 )
    return 0;
  v15 = *(void **)(v10 + 4 * v9);
  v14 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11) + 68);
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 16))(v11);
  sub_44BC30(*(uint32_t **)(this + 8), (void *)2, 7, *(uint32_t *)(v12 + 4), v9, v14, v15);
  return 1;
}



// ------------------------------------------------------------
// 0x549110 CNRDAvatarInventoryWindow__vmt1C —— CNRDAvatarInventoryWindow__vmt1C 内容刷新（182 行：486820/44A980/548F20/484AF0/540DE0/486530）
// ------------------------------------------------------------
char /*thiscall*/ sub_549110(int this)
{
  int v2; // eax
  uint32_t *v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // esi
  int v8; // edi
  uint32_t *v9; // eax
  int v10; // edi
  uint32_t *v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // esi
  uint32_t *v16; // eax
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // esi
  int v21; // eax
  int v22; // esi
  uint32_t *v23; // eax
  int v24; // eax
  int v25; // ebx
  int v26; // eax
  int v27; // edi
  int v28; // eax
  int v29; // edi
  int v30; // eax
  uint32_t *v31; // [esp+8h] [ebp-Ch]
  int v32; // [esp+Ch] [ebp-8h]
  int v33; // [esp+10h] [ebp-4h]
  int v34; // [esp+10h] [ebp-4h]

  v2 = *(uint32_t *)(this + 4);
  if ( *(uint8_t *)(v2 + 17) == 0 || dword_79BE34 != *(uint32_t *)(v2 + 12) )
    return 0;
  v4 = *(uint32_t **)(this + 8);
  v31 = v4;
  if ( v4[626] != 2 )
    return 0;
  v5 = v4[627];
  if ( v5 == 6 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 44) + 792))(*(uint32_t *)(this + 44), v4[629]);
    v7 = v6;
    if ( v6 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 16))(v6) + 4) == v4[628] )
    {
      v8 = sub_548E20(0);
      if ( v8 != -1 )
      {
        v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 172))(v7);
        if ( (uint8_t)sub_486820(v8, *v9, 1) != 0 )
          return 1;
        if ( sub_44A980(v8) != 0 )
        {
          v10 = 0;
          while ( sub_44A980(v10) != 0 )
          {
            if ( ++v10 >= 21 )
              return 0;
          }
          v11 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 172))(v7);
          sub_486820(v10, *v11, 1);
          return 1;
        }
      }
    }
    return 0;
  }
  if ( v5 != 7 )
  {
    if ( v5 != 5 )
      return 0;
    v19 = sub_44A980(v4[629]);
    v20 = v19;
    if ( v19 == 0
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 16))(v19) + 4) != v4[628]
      || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v20 + 20))(v20, 2) == 0
      || *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 172))(v20) > 7 )
    {
      return 0;
    }
    if ( (uint8_t)sub_548F20(this) != 0 )
    {
      v21 = __RTDynamicCast(v20, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
      v22 = v21;
      if ( v21 == 0 || *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v21 + 172))(v21) > 7 )
        return 0;
      v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v22 + 172))(v22);
      sub_484AF0(v4[629], 1, 3, *v23);
      return 1;
    }
    v24 = sub_548E20(0);
    v25 = v24;
    if ( v24 != -1 )
    {
      v26 = sub_44A980(v24);
      v33 = v26;
      if ( v26 == 0 )
      {
LABEL_52:
        if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 44))(v20) <= 1 )
        {
          v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 44))(v20);
          sub_484AF0(v4[629], v30, 1, v25);
        }
        else
        {
          sub_540DE0(1, 4, v4[629], 1, v25, 0, 0);
        }
        return 1;
      }
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v26 + 20))(v26, 1) != 0 )
      {
        v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v33 + 16))(v33);
        if ( *(uint32_t *)(v27 + 4) == *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 16))(v20) + 4) )
        {
LABEL_51:
          v4 = v31;
          goto LABEL_52;
        }
      }
      v25 = -1;
    }
    v34 = 0;
    while ( 1 )
    {
      v28 = sub_44A980(v25);
      v29 = v28;
      if ( v28 == 0 )
        break;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v28 + 20))(v28, 1) != 0 )
      {
        v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 16))(v20);
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v29 + 16))(v29) + 4) == *(uint32_t *)(v32 + 4) )
          break;
      }
      if ( ++v34 >= 105 )
        goto LABEL_50;
    }
    v25 = v34;
LABEL_50:
    if ( v25 == -1 )
      return 0;
    goto LABEL_51;
  }
  v12 = v4[629];
  if ( v12 >= *((uint32_t *)dword_8F8534 + 2) )
    v13 = 0;
  else
    v13 = *(uint32_t *)(*((uint32_t *)dword_8F8534 + 3) + 4 * v12);
  v14 = __RTDynamicCast(v13, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
  v15 = v14;
  if ( v14 == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 16))(v14) + 4) != v4[628] )
    return 0;
  if ( (uint8_t)sub_548F20(this) != 0 )
  {
    if ( *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 172))(v15) > 7 )
      return 0;
    v16 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 172))(v15);
    sub_486820(v4[629], *v16, 1);
    return 1;
  }
  else
  {
    v17 = sub_548E20(0);
    if ( v17 == -1 )
      return 0;
    v18 = v4[629];
    if ( v17 == v18 )
      return 0;
    sub_486530(v17, v18, 1);
    return 1;
  }
}


// ------------------------------------------------------------
// 0x5494C0 CNRDAvatarInventoryWindow__vmt28 —— CNRDAvatarInventoryWindow__vmt28 槽（548E20/4872A0/549000/486820）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAvatarInventoryWindow__vmt28(int this)
{
  int v2; // eax
  int v3; // eax
  int v5; // eax
  int v6; // eax
  int v7; // esi
  uint32_t *v8; // eax

  v2 = *(uint32_t *)(this + 4);
  if ( *(uint8_t *)(v2 + 17) == 0
    || dword_79BE38 != *(uint32_t *)(v2 + 12)
    || *(uint32_t *)(*(uint32_t *)(this + 8) + 2504) != 0 )
  {
    return 0;
  }
  v3 = sub_548E20((uint32_t *)this, 1);
  if ( v3 != -1 )
  {
    sub_4872A0(v3);
    return 1;
  }
  v5 = sub_549000();
  if ( v5 == 18 )
    return 0;
  v6 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 44) + 792))(*(uint32_t *)(this + 44), v5);
  if ( v6 == 0 )
    return 0;
  v7 = 0;
  while ( v7 < *((uint32_t *)dword_8F8534 + 2) && *(uint32_t *)(*((uint32_t *)dword_8F8534 + 3) + 4 * v7) != 0 )
  {
    if ( ++v7 >= 21 )
      return 1;
  }
  v8 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 172))(v6);
  sub_486820(v7, *v8, 1);
  return 1;
}



// ------------------------------------------------------------
// 0x549580 CNRDAvatarInventoryWindow__vmt8 —— CNRDAvatarInventoryWindow__vmt8 Update（93 行：CLICK_BUTTON2/WINDOW_CLOSE + 69C690/560610）
// ------------------------------------------------------------
int /*thiscall*/ CNRDAvatarInventoryWindow__vmt8(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // eax
  int v8; // ecx
  int v9; // ebx
  int v10; // edi
  int v11; // eax
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int result; // eax

  v2 = *(uint32_t *)(this + 16);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 44))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    sub_432EA0("WINDOW_CLOSE", -1, 0, 0);
  }
  v3 = *(uint32_t *)(this + 20);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    sub_44BBA0(*(uint32_t **)(this + 8), 0, 0);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v4 = *(uint32_t *)(*(uint32_t *)(this + 8) + 2504);
  if ( v4 == 1 )
    goto LABEL_21;
  if ( v4 == 2 )
    goto LABEL_21;
  v5 = *(uint32_t *)(this + 4);
  if ( *(uint8_t *)(v5 + 17) == 0 )
    goto LABEL_21;
  v6 = *(uint32_t *)(v5 + 12);
  if ( dword_79BE3C != v6 && dword_79BE34 != v6 && dword_79BE38 != v6 )
    goto LABEL_21;
  v7 = sub_548E20((uint32_t *)this, 1);
  if ( v7 != -1 )
  {
    v8 = v7 >= *((uint32_t *)dword_8F8534 + 2) ? 0 : *(uint32_t *)(*((uint32_t *)dword_8F8534 + 3) + 4 * v7);
    v9 = 32 * (v7 % 7) + 349;
    v10 = 32 * (v7 / 7) + 243;
    if ( v8 != 0 )
      goto LABEL_38;
  }
  v11 = sub_549000();
  v12 = v11;
  if ( v11 != 18
    && (v13 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 44) + 792))(*(uint32_t *)(this + 44), v11),
        v9 = dword_724904[v12],
        v10 = dword_724924[v12],
        v8 = v13,
        v13 != 0) )
  {
LABEL_38:
    if ( dword_9B88D0 != v8 || dword_795378 != 2 )
    {
      v14 = sub_44E8D0(*(char **)(this + 8), (void *)0x1A, v8, 2);
      if ( v14 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v14 + 48))(v14, v9, v10, 28, 28);
    }
  }
  else
  {
LABEL_21:
    if ( dword_9B88D0 != 0 && dword_795378 == 2 )
      sub_44E850(*(uint32_t **)(this + 8), 26);
  }
  v15 = *(uint32_t *)(this + 28);
  if ( *(uint8_t *)(v15 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v15 + 12) )
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  v16 = *(uint32_t *)(this + 32);
  if ( *(uint8_t *)(v16 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v16 + 12) )
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  *(uint32_t *)(this + 48) = sub_69C690(*(uint32_t *)(this + 40));
  result = *(uint32_t *)(this + 24);
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
    return sub_560610(1);
  return result;
}



// ------------------------------------------------------------
// 0x5497A0 CNRDAvatarInventoryWindow__vmt0 —— CNRDAvatarInventoryWindow__vmt0 构造（141 行：4CE8A0/549000/4F2E40/548E20/4938F0/491D00/422E70）
// ------------------------------------------------------------
int /*thiscall*/ sub_5497A0(int this, int a2)
{
  int result; // eax
  int v3; // ebx
  int i; // esi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // esi
  int v11; // edx
  uint32_t *v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // edx
  int v16; // esi
  const char *v17; // eax
  const char *v18; // eax
  const char *v19; // eax
  int v20; // [esp-8h] [ebp-7Ch]
  int v21; // [esp-8h] [ebp-7Ch]
  int v22; // [esp-8h] [ebp-7Ch]
  int v23; // [esp+8h] [ebp-6Ch]
  char Buffer[100]; // [esp+Ch] [ebp-68h] BYREF
  int v25; // [esp+70h] [ebp-4h]
  int v26; // [esp+7Ch] [ebp+8h]

  result = dword_796E50;
  v3 = a2;
  v25 = dword_796E50;
  if ( a2 == *(uint32_t *)(this + 4) )
  {
    for ( i = 0; i < 8; ++i )
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 44) + 792))(*(uint32_t *)(this + 44), i);
      if ( v6 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)v6 + 8))(
          v6,
          dword_724904[i],
          dword_724924[i],
          0,
          1);
    }
    if ( pt.x >= 332
      && pt.x < 599
      && pt.y >= 74
      && pt.y < 232
      && *(uint8_t *)(a2 + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(a2 + 12)
       || dword_79BE34 == *(uint32_t *)(a2 + 12)
       || dword_79BE38 == *(uint32_t *)(a2 + 12))
      && (*(uint32_t *)((v7 = *(uint32_t *)(this + 8)) + 2504) == 2
       && (v8 = sub_4CE8A0(*(uint32_t *)(v7 + 2512))) != 0
       && (v9 = *(uint32_t *)(v8 + 92)) <= 7
       || (v9 = sub_549000(this)) != 18) )
    {
      sub_4F2E40(dword_724904[v9], dword_724924[v9]);
    }
    v10 = 7 * *(uint32_t *)(this + 48);
    v11 = v10 + 21;
    v23 = v10 + 21;
    if ( !__OFSUB__(v10, v10 + 21) )
    {
      v12 = dword_8F8534;
      do
      {
        if ( v10 < v12[2] )
        {
          v13 = *(uint32_t *)(v12[3] + 4 * v10);
          if ( v13 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)v13 + 8))(
              v13,
              32 * (v10 % 7) + 349,
              32 * (v10 / 7 - *(uint32_t *)(this + 48)) + 243,
              0,
              1);
            v12 = dword_8F8534;
            v3 = a2;
            v11 = v23;
          }
        }
        ++v10;
      }
      while ( v10 < v11 );
    }
    if ( *(uint8_t *)(v3 + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(v3 + 12)
       || dword_79BE34 == *(uint32_t *)(v3 + 12)
       || dword_79BE38 == *(uint32_t *)(v3 + 12)) )
    {
      v14 = sub_548E20(1);
      if ( v14 != -1 )
        sub_4F2E40(32 * (v14 % 7) + 349, 32 * (v14 / 7 - *(uint32_t *)(this + 48)) + 243);
    }
    v15 = dword_77F6DC;
    dword_77F6DC = 1065353216;
    v26 = v15;
    v16 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C08 + 344))(dword_8F7C08);
    sub_4938F0(v16);
    sub_491D00(dword_79C0B0, 465, 213, 0.0);
    dword_77F6DC = v26;
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_7947AC);
    v20 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));
    v17 = (const char *)sub_422E70(180);
    sprintf(Buffer, v17, v20);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *, int))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      459,
      355,
      -4265479,
      Buffer,
      2);
    v21 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8));
    v18 = (const char *)sub_422E70(181);
    sprintf(Buffer, v18, v21);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *, int))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      459,
      372,
      -4265479,
      Buffer,
      2);
    v22 = dword_8F7C0C;
    v19 = (const char *)sub_422E70(182);
    sprintf(Buffer, v19, v22);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      459,
      389,
      -4265479,
      Buffer);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  }
  return result;
}


// ============================================================
// 【分区 12】面对面交易窗口 CNRDItemTradeWindow（0x549AC0-0x54AC70）
// vmt1C=刷新（83 行）、vmt8=Update（CLICK_BUTTON2/WINDOW_CLOSE + 50EB10
// 交易状态）、vmt0=构造（154 行）；0x54A930=交易就绪绘制
// （Interface/ItemTradeWindowReady.img）。
// ============================================================
// ------------------------------------------------------------
// 0x549AC0 sub_549AC0 —— 时装栏页绘制（94 行：43C250/43C410/69A5F0/69A840 + 69C980/43C4D0/43C630）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_549AC0(int *this)
{
  uint8_t *v2; // eax
  uint8_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  uint8_t *v14; // edi
  uint8_t *v15; // eax
  uint8_t *v16; // eax

  v2 = operator new(0x6Cu);
  if ( v2 != nullptr )
    v3 = sub_43C250(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 20), 0);
  else
    v3 = nullptr;
  *(this + 1) = (int)v3;
  *((uint32_t *)v3 + 7) = *((uint32_t *)v3 + 7);
  *((uint32_t *)v3 + 8) = 383;
  *(uint32_t *)(*(this + 1) + 68) = this;
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 11, 12, 13, 11, 0, 0);
  else
    v5 = nullptr;
  *(this + 4) = (int)v5;
  sub_69A5F0(v5, 51, 383);
  sub_69A840(*(this + 4));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 20), 1, 2, 2, 1, 0, 0);
  else
    v7 = nullptr;
  *(this + 5) = (int)v7;
  sub_69A5F0(v7, 149, 0);
  sub_69A840(*(this + 5));
  v8 = operator new(0x84u);
  if ( v8 != nullptr )
    v9 = sub_43C410(v8, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 20), 4, 5, 6, -1, 0, 0);
  else
    v9 = nullptr;
  *(this + 6) = (int)v9;
  sub_69A5F0(v9, 24, 315);
  sub_69A840(*(this + 6));
  sub_69C980(*(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 20), 4, 4, 4, 4, 0, 0);
  *(uint8_t *)(*(this + 6) + 17) = 0;
  v10 = operator new(0x84u);
  if ( v10 != nullptr )
    v11 = sub_43C410(v10, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 4, 4, 5, 4, 0, 0);
  else
    v11 = nullptr;
  *(this + 7) = (int)v11;
  *((uint8_t *)v11 + 16) = 1;
  v12 = operator new(0x84u);
  if ( v12 != nullptr )
    v13 = sub_43C410(v12, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 6, 6, 7, 6, 0, 0);
  else
    v13 = nullptr;
  *(this + 8) = (int)v13;
  *((uint8_t *)v13 + 16) = 1;
  v14 = operator new(0x88u);
  if ( v14 != nullptr )
  {
    sub_43C4D0(v14, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 20), 7, 13);
    *(uint32_t *)v14 = &vftbl_nengine__CNVSlider;
  }
  else
  {
    v14 = nullptr;
  }
  *(this + 9) = (int)v14;
  v15 = operator new(0x74u);
  if ( v15 != nullptr )
    v16 = sub_43C630(v15, *(this + 7), *(this + 8), *(this + 9));
  else
    v16 = nullptr;
  *(this + 10) = (int)v16;
  sub_69A5F0(v16, 254, 207);
  sub_69A840(*(this + 10));
  return sub_69A5F0((uint32_t *)*(this + 1), 320, 33);
}



// ------------------------------------------------------------
// 0x549DC0 sub_549DC0 —— 23 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_549DC0(int this)
{
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint16_t *)(this + 148) = 48;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint16_t *)(this + 180) = 48;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 224) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x549E10 CNRDItemTradeWindow__vmt1C —— CNRDItemTradeWindow__vmt1C 刷新槽（83 行：4848E0/422E70/44E8D0/432F00/540DE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemTradeWindow__vmt1C(int this)
{
  int v1; // eax
  uint32_t *v2; // esi
  int v4; // eax
  int v5; // edi
  char *v6; // eax
  int v7; // ebx
  int v8; // edi
  uint32_t *v9; // eax
  int v10; // edi
  unsigned int v11; // eax
  int v12; // ecx
  char *v13; // eax

  v1 = *(uint32_t *)(this + 4);
  if ( *(uint8_t *)(v1 + 17) == 0 )
    return 0;
  if ( dword_79BE34 != *(uint32_t *)(v1 + 12) )
    return 0;
  v2 = *(uint32_t **)(this + 8);
  if ( v2[626] != 2 )
    return 0;
  v4 = v2[627];
  if ( v4 == 3 || v4 == 4 )
  {
    v7 = 0;
  }
  else
  {
    if ( v4 != 7 )
    {
      if ( v4 == 2 || v4 == 6 )
      {
        v5 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, v2[629]);
        if ( v5 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 16))(v5) + 4) == v2[628] )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 80))(v5) != 0 )
          {
            sub_4848E0(3, v2[629], 1);
          }
          else
          {
            v6 = sub_422E70(423);
            sub_44E8D0(*(char **)(this + 8), (void *)0x1B, (int)v6, 0);
          }
          return 1;
        }
      }
      return 0;
    }
    v7 = 1;
  }
  v8 = v2[629];
  v9 = sub_432F00(v7);
  if ( v8 >= v9[2] )
    return 0;
  v10 = *(uint32_t *)(v9[3] + 4 * v8);
  if ( v10 == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 16))(v10) + 4) != v2[628] )
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 80))(v10) != 0 )
  {
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 44))(v10);
    v12 = v2[629];
    if ( v11 <= 1 )
      sub_4848E0(v7, v12, 1);
    else
      sub_540DE0(*(int **)(*(uint32_t *)(this + 8) + 116), 1, v7, v12, 4, 0, 0, 0);
    return 1;
  }
  else
  {
    v13 = sub_422E70(422);
    sub_44E8D0(*(char **)(this + 8), (void *)0x1B, (int)v13, 0);
    return 1;
  }
}



// ------------------------------------------------------------
// 0x549FD0 sub_549FD0 —— 交易窗公共更新（40 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_549FD0(uint32_t *this)
{
  int v1; // eax
  int v2; // edi
  int i; // ecx
  int v5; // [esp+Ch] [ebp-Ch]
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v1 = *(this + 1);
  v2 = 0;
  v7 = 0;
  v6 = *(uint32_t *)(v1 + 20);
  v5 = *(uint32_t *)(v1 + 24);
  while ( 2 )
  {
    for ( i = 0; i < 24; ++i )
    {
      if ( pt.x >= 32 * (i % 8) + v6 + 19
        && pt.x < 32 * (i % 8) + v6 + 47
        && pt.y >= 32 * (i / 8) - v2 + v5 + 231
        && pt.y < 32 * (i / 8) - v2 + v5 + 259 )
      {
        return i + 24 * v7;
      }
    }
    v2 += 174;
    ++v7;
    if ( v2 < 348 )
      continue;
    break;
  }
  return -1;
}



// ------------------------------------------------------------
// 0x54A080 CNRDItemTradeWindow__vmt10 —— CNRDItemTradeWindow__vmt10 状态切换（44E850 + 484600 + 540960）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemTradeWindow__vmt10(uint32_t **this)
{
  if ( dword_9B88D0 != 0 && dword_795378 == 3 )
    sub_44E850(*(this + 2), 26);
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
    sub_484600();
  sub_540960((uint32_t *)(*(this + 2))[29]);
  sub_44E850(dword_8F8528, 66);
  return sub_44E850(dword_8F8528, 27);
}



// ------------------------------------------------------------
// 0x54A0E0 sub_54A0E0 —— 交易窗数据（44 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_54A0E0(uint32_t *this, int a2, int a3)
{
  int v3; // edi
  int v5; // ecx
  unsigned int v6; // esi
  signed int v7; // esi
  signed int v8; // eax
  int v9; // edx
  int i; // [esp+Ch] [ebp-28h]
  char Buffer[32]; // [esp+10h] [ebp-24h] BYREF
  int v13; // [esp+30h] [ebp-4h]

  v3 = a2;
  v5 = *(this + a2 + 53);
  v13 = dword_796E50;
  if ( a3 != v5 )
  {
    sprintf(Buffer, "%d", a3);
    v6 = (strlen(Buffer) - 1) / 3;
    *((uint8_t *)this + 32 * a2 + v6 + strlen(Buffer) + 148) = 0;
    v7 = strlen(Buffer) + v6 - 1;
    v8 = strlen(Buffer) - 1;
    for ( i = 0; v7 >= 0; ++i )
    {
      if ( v8 < 0 )
        break;
      v9 = 32 * a2 + v7;
      if ( i % 4 == 3 )
        *((uint8_t *)this + v9 + 148) = 44;
      else
        *((uint8_t *)this + v9 + 148) = Buffer[v8--];
      --v7;
    }
    *(this + a2 + 53) = a3;
    v3 = a2;
  }
  return (int)(this + 8 * v3 + 37);
}



// ------------------------------------------------------------
// 0x54A200 sub_54A200 —— 交易窗数量联动（14 行，被 5409C0 调用）
// ------------------------------------------------------------
int /*thiscall*/ sub_54A200(uint32_t *this, char a2)
{
  int result; // eax

  result = *(this + 5);
  *(uint8_t *)(result + 17) = a2;
  return result;
}



// ------------------------------------------------------------
// 0x54A210 CNRDItemTradeWindow__vmt8 —— CNRDItemTradeWindow__vmt8 Update（103 行：CLICK_BUTTON2/WINDOW_CLOSE + 4844E0/50EB10/549FD0 交易状态）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemTradeWindow__vmt8(uint32_t *this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // eax
  bool v5; // al
  int v6; // eax
  bool v7; // al
  int v8; // eax
  uint32_t *v9; // edi
  int i; // ebx
  char *v11; // edi
  int v12; // eax
  int v13; // ecx
  int v14; // ebx
  int v15; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // eax
  int v19; // ebx
  int v20; // edi
  int v21; // esi
  int v23; // [esp+4h] [ebp-8h]
  char *v24; // [esp+8h] [ebp-4h]

  v2 = dword_8F8538;
  if ( *(uint16_t *)(dword_8F8538 + 4) == 0xFFFF )
  {
    LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 44))(this);
    return v3;
  }
  v4 = *(this + 4);
  if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 44))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    sub_432EA0("WINDOW_CLOSE", -1, 0, 0);
    v2 = dword_8F8538;
  }
  v5 = *(uint32_t *)(v2 + 8) != 1 && (*(uint8_t *)(v2 + 64) == 0 || sub_699000(v2 + 52) > 2000);
  *(uint8_t *)(*(this + 5) + 16) = v5;
  v6 = *(this + 5);
  if ( *(uint8_t *)(v6 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v6 + 12) )
    sub_540DE0(*(int **)(*(this + 2) + 116), 1, 0, 0, 4, 0, 0, 0);
  v7 = *(uint32_t *)(dword_8F8538 + 8) != 1
    && (*(uint8_t *)(dword_8F8538 + 36) == 0 || sub_699000(dword_8F8538 + 24) > 1000);
  *(uint8_t *)(*(this + 6) + 17) = v7;
  v8 = *(this + 6);
  if ( *(uint8_t *)(v8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v8 + 12) )
    sub_4844E0(1);
  v9 = this + 55;
  for ( i = 2; i != 0; --i )
    sub_50EB10(*v9++);
  v11 = (char *)*(this + 2);
  v12 = *((uint32_t *)v11 + 626);
  v24 = v11;
  if ( v12 == 1 )
    goto LABEL_36;
  if ( v12 == 2 )
    goto LABEL_36;
  v13 = *(this + 1);
  if ( *(uint8_t *)(v13 + 17) == 0 )
    goto LABEL_36;
  v14 = *(uint32_t *)(v13 + 12);
  if ( dword_79BE3C != v14 && dword_79BE34 != v14 && dword_79BE38 != v14 )
    goto LABEL_36;
  v15 = sub_549FD0(this);
  if ( v15 == -1 )
    goto LABEL_36;
  v16 = v15 % 24;
  v17 = v15 / 24;
  v18 = *(uint32_t *)(dword_8F8538 + 4 * (v15 / 24) + 16);
  if ( v16 + 3 >= *(uint32_t *)(v18 + 8) )
    v19 = 0;
  else
    v19 = *(uint32_t *)(*(uint32_t *)(v18 + 12) + 4 * (v16 + 3));
  v20 = *(this + 1);
  v23 = 32 * (v16 % 8) + *(uint32_t *)(v20 + 20) + 19;
  v3 = *(uint32_t *)(v20 + 24);
  v21 = v3 + 32 * (v16 / 8) - 174 * v17 + 231;
  if ( v19 == 0 )
  {
    v11 = v24;
LABEL_36:
    LOBYTE(v3) = dword_9B88D0;
    if ( dword_9B88D0 != 0 && dword_795378 == 3 )
      LOBYTE(v3) = sub_44E850(v11, 26);
    return v3;
  }
  if ( dword_9B88D0 != v19 || dword_795378 != 3 )
  {
    v3 = sub_44E8D0(v24, (void *)0x1A, v19, 3);
    if ( v3 != 0 )
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v3 + 48))(v3, v23, v21, 28, 28);
  }
  return v3;
}



// ------------------------------------------------------------
// 0x54A480 CNRDItemTradeWindow__vmt0 —— CNRDItemTradeWindow__vmt0 构造（154 行：42B340/4924C0/4938F0/491D00 + 54A0E0/50EB40）
// ------------------------------------------------------------
int /*userpurge*/ sub_54A480@<eax>(int a1@<ecx>, int a2@<esi>, int a3)
{
  int v3; // ebx
  int result; // eax
  int v5; // edi
  int v6; // eax
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int v10; // eax
  int v11; // edi
  unsigned int v12; // edi
  int v13; // eax
  unsigned int v14; // ecx
  int v15; // eax
  int v16; // ecx
  int v17; // ecx
  int v18; // edi
  int v19; // eax
  int v20; // eax
  unsigned int v21; // edi
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v25; // edi
  int v26; // eax
  int v27; // eax
  int v30; // [esp+10h] [ebp-10h]
  int v31; // [esp+10h] [ebp-10h]
  int v32; // [esp+10h] [ebp-10h]
  int v33; // [esp+10h] [ebp-10h]
  int v34; // [esp+10h] [ebp-10h]
  int v35; // [esp+14h] [ebp-Ch]
  int v36; // [esp+18h] [ebp-8h]

  v3 = a1;
  result = *(uint32_t *)(a1 + 4);
  v5 = a3;
  if ( a3 == result )
  {
    v6 = *(uint32_t *)(a1 + 20);
    if ( *(uint8_t *)(v6 + 16) == 0 )
    {
      v7 = *(uint32_t *)(v6 + 24);
      v30 = *(uint32_t *)(v6 + 20);
      v8 = sub_418DD0(1);
      if ( v8 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, v30, v7, dword_79C0B0);
    }
    v9 = 1;
    while ( 1 )
    {
      v35 = *(uint32_t *)(v5 + 20) + 15;
      if ( v9 != 0 )
        v36 = *(uint32_t *)(v5 + 24) + 24;
      else
        v36 = *(uint32_t *)(v5 + 24) + 198;
      v10 = sub_42B340(*(uint32_t *)(v3 + 4 * v9 + 140));
      v11 = v10;
      if ( v10 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)v10 + 384))(
          v10,
          v35 + 3,
          v36 + 4,
          24,
          24,
          1065353216);
      v31 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 360))(v11, a2);
      if ( v31 != 0 )
      {
        v12 = *(uint32_t *)(*(uint32_t *)sub_4924C0(0) + 36);
        sub_4938F0(v31);
        sub_491D00(dword_79C0B0, v35 - (v12 >> 1) + 69, v36 + 1, 0.0);
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v3 + 28);
      v13 = *(uint32_t *)(v3 + 4 * v9 + 140);
      v14 = *(uint32_t *)(v13 + 40);
      v15 = v13 + 16;
      v16 = v14 < 0x10 ? v15 + 4 : *(uint32_t *)(v15 + 4);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v35 + 24,
        v36 + 17,
        -1,
        v16);
      v17 = **(uint32_t **)(*(uint32_t *)(dword_8F8538 + 4 * v9 + 16) + 12);
      v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 44))(v17);
      a2 = v3 + 80;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0);
      v32 = *(uint32_t *)dword_79C0B0;
      v19 = sub_54A0E0(v9, v18);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(v32 + 80))(dword_79C0B0, v35 + 126, v36 + 11, -4265479, v19);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v20 = 12;
      v21 = 0;
      v33 = 12;
      do
      {
        v22 = *(uint32_t *)(dword_8F8538 + 4 * v9 + 16);
        if ( (signed int)(v21 + 3) < *(uint32_t *)(v22 + 8) )
        {
          v23 = *(uint32_t *)(v20 + *(uint32_t *)(v22 + 12));
          if ( v23 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, uint32_t, uint32_t))(*(uint32_t *)v23 + 8))(
              v23,
              32 * (v21 & 7) + *(uint32_t *)(*(uint32_t *)(v3 + 4) + 20) + 19,
              *(uint32_t *)(*(uint32_t *)(v3 + 4) + 24) + 32 * (v21 >> 3) - 174 * v9 + 231,
              0,
              0);
            v20 = v33;
            v3 = a1;
          }
        }
        v20 += 4;
        ++v21;
        v33 = v20;
      }
      while ( v20 < 108 );
      if ( *(uint32_t *)(dword_8F8538 + 4 * v9 + 8) == 1 )
      {
        v24 = *(uint32_t *)(a3 + 20);
        if ( v9 != 0 )
        {
          v34 = v24 + 152;
          v25 = *(uint32_t *)(a3 + 24) + 155;
        }
        else
        {
          v34 = v24 + 96;
          v25 = *(uint32_t *)(a3 + 24) + 165;
        }
        v26 = sub_418DD0((v9 != 0) + 4);
        if ( v26 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v26 + 152))(v26, v34, v25, dword_79C0B0);
        sub_491530(2, 0);
        v27 = sub_418DD0(1 - v9);
        if ( v27 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v27 + 152))(v27, 0, 0, dword_79C0B0);
        sub_491630(2);
      }
      result = sub_50EB40(v35 + 14, v36 + 4, 255);
      if ( --v9 < 0 )
        break;
      v5 = a3;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x54A7A0 CNRDItemTradeWindow__vmtC —— CNRDItemTradeWindow__vmtC 打开槽（44BBA0 + 429830）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemTradeWindow__vmtC(int this)
{
  int v2; // eax
  int v3; // ecx

  sub_44BBA0(*(uint32_t **)(this + 8), 0, 0);
  *(uint32_t *)(this + 140) = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  v2 = sub_429830((uint32_t *)dword_8F8500, *(uint16_t *)(dword_8F8538 + 4));
  v3 = *(uint32_t *)(this + 140);
  *(uint32_t *)(this + 144) = v2;
  if ( v3 == 0 || v2 == 0 )
    return 0;
  *(uint8_t *)(*(uint32_t *)(this + 220) + 40) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 224) + 40) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 20) + 17) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x54A820 CNRDItemTradeWindow__vmt14 —— CNRDItemTradeWindow__vmt14 关闭槽（549FD0 + 44BC30）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemTradeWindow__vmt14(int this)
{
  int v1; // esi
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // edi
  int v8; // edx
  int v9; // esi
  int v10; // eax
  int v11; // [esp-Ch] [ebp-14h]
  void *v12; // [esp-8h] [ebp-10h]

  v1 = dword_8F8538;
  if ( *(uint32_t *)(dword_8F8538 + 8) == 1 )
    return 0;
  v4 = *(uint32_t *)(this + 4);
  if ( *(uint8_t *)(v4 + 17) == 0 )
    return 0;
  if ( dword_79BE3C != *(uint32_t *)(v4 + 12) )
    return 0;
  v5 = sub_549FD0((uint32_t *)this);
  if ( v5 == -1 )
    return 0;
  if ( v5 >= 24 )
    return 0;
  v6 = *(uint32_t *)(v1 + 16);
  v7 = v5 + 3;
  if ( v5 + 3 >= *(uint32_t *)(v6 + 8) )
    return 0;
  v8 = *(uint32_t *)(v6 + 12);
  v9 = *(uint32_t *)(v8 + 4 * v7);
  if ( v9 == 0 )
    return 0;
  v12 = *(void **)(v8 + 4 * v7);
  v11 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 16))(v9) + 68);
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 16))(v9);
  sub_44BC30(*(uint32_t **)(this + 8), (void *)2, 5, *(uint32_t *)(v10 + 4), v7, v11, v12);
  return 1;
}



// ------------------------------------------------------------
// 0x54A8B0 sub_54A8B0 —— 交易辅助（4999D0）
// ------------------------------------------------------------
void /*thiscall*/ sub_54A8B0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  uint32_t *v6; // esi
  int i; // ebx
  void *v8; // edi

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 4);
  *(this + 1) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 4) = 0;
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  *(this + 5) = 0;
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  *(this + 6) = 0;
  v6 = this + 55;
  for ( i = 2; i != 0; --i )
  {
    v8 = (void *)*v6;
    if ( *v6 != 0 )
    {
      sub_4999D0(*v6);
      j__free(v8);
    }
    *v6++ = 0;
  }
}



// ------------------------------------------------------------
// 0x54A930 sub_54A930 —— 交易就绪绘制：资源 Interface/ItemTradeWindowReady.img（43C250/43C410/69A5F0/69A840 + 499960）
// ------------------------------------------------------------
int /*thiscall*/ sub_54A930(int this)
{
  uint8_t *v2; // eax
  uint8_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  int v10; // edi
  int *v11; // esi
  int result; // eax

  *(uint32_t *)(this + 132) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 24);
  *(uint32_t *)(this + 136) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                              dword_8F84B8,
                              "Interface/ItemTradeWindowReady.img");
  v2 = operator new(0x6Cu);
  if ( v2 != nullptr )
    v3 = sub_43C250(v2, *(uint32_t *)(this + 132), 0);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 4) = v3;
  *((uint32_t *)v3 + 7) = *((uint32_t *)v3 + 7);
  *((uint32_t *)v3 + 8) = 353;
  *(uint32_t *)(*(uint32_t *)(this + 4) + 68) = this;
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 11, 12, 13, 11, 0, 0);
  else
    v5 = nullptr;
  *(uint32_t *)(this + 16) = v5;
  sub_69A5F0(v5, 221, 353);
  sub_69A840(*(uint32_t *)(this + 16));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(uint32_t *)(this + 132), 1, 2, 3, 1, 0, 0);
  else
    v7 = nullptr;
  *(uint32_t *)(this + 20) = v7;
  sub_69A5F0(v7, 132, 203);
  sub_69A840(*(uint32_t *)(this + 20));
  v8 = operator new(0x84u);
  if ( v8 != nullptr )
    v9 = sub_43C410(v8, *(uint32_t *)(this + 132), 6, 7, 8, 9, 0, 0);
  else
    v9 = nullptr;
  *(uint32_t *)(this + 24) = v9;
  sub_69A5F0(v9, 117, 332);
  sub_69A840(*(uint32_t *)(this + 24));
  sub_69A5F0(*(uint32_t **)(this + 4), 29, 63);
  *(uint32_t *)(this + 44) = 6;
  *(uint8_t *)(this + 28) = 0;
  *(uint8_t *)(this + 29) = 0;
  *(uint8_t *)(this + 30) = 0;
  *(uint8_t *)(this + 31) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 56) = 1600;
  *(uint32_t *)(this + 48) = 12;
  *(uint32_t *)(this + 76) = dword_99FCCC;
  *(uint32_t *)(this + 40) = 1;
  *(uint32_t *)(this + 56) = 90;
  *(uint32_t *)(this + 96) = 6;
  *(uint8_t *)(this + 80) = 0;
  *(uint8_t *)(this + 81) = 0;
  *(uint8_t *)(this + 82) = 0;
  *(uint8_t *)(this + 83) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 100) = 12;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 1600;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  v10 = 2;
  *(uint32_t *)(this + 128) = dword_99FCCC;
  *(uint32_t *)(this + 92) = 2;
  *(uint32_t *)(this + 108) = 120;
  v11 = (int *)(this + 220);
  do
  {
    if ( operator new(0x44u) != nullptr )
      result = sub_499960(nullptr, 120, 0);
    else
      result = 0;
    *v11++ = result;
    --v10;
  }
  while ( v10 != 0 );
  return result;
}



// ------------------------------------------------------------
// 0x54ABC0 sub_54ABC0 —— 19 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_54ABC0(uint32_t *this)
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
  return 0;
}



// ------------------------------------------------------------
// 0x54ABE0 sub_54ABE0 —— 交易条目（47 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_54ABE0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  uint32_t *v5; // edi
  int i; // ebx
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 4);
  *(this + 1) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 4) = 0;
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  *(this + 5) = 0;
  v5 = this + 6;
  for ( i = 5; i != 0; --i )
  {
    if ( *v5 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v5)(*v5, 1);
    *v5++ = 0;
  }
  v7 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  if ( v7 != nullptr )
    (**v7)(v7, 1);
  v8 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  result = 0;
  *(this + 11) = 0;
  if ( v8 != nullptr )
    result = (**v8)(v8, 1);
  *(this + 12) = 0;
  return result;
}



// ============================================================
// 【分区 13】技能栏 CNRDSkillInventoryWindow（0x54AC70-0x54B780）
// vmt1C=刷新（ICON_DROP 技能图标拖入音效 432EA0）、vmt8=Update（CLICK_BUTTON2/
// WINDOW_CLOSE）、vmt18=页签切换（44AB90=TAB_SELECT 音）。
// ============================================================
// ------------------------------------------------------------
// 0x54AC70 CNRDSkillInventoryWindow__vmt10 —— CNRDSkillInventoryWindow__vmt10 状态切换（44ABE0 + 550C40 + 44AB50 + 44E850）
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillInventoryWindow__vmt10(uint32_t *this)
{
  uint32_t *v2; // ecx
  int v3; // eax
  int v4; // eax
  char result; // al

  v2 = (uint32_t *)*(this + 2);
  v3 = v2[626];
  if ( v3 == 10 || v3 == 11 )
    sub_44ABE0(v2, 0);
  v4 = *(this + 2);
  if ( *(uint32_t *)(v4 + 104) == 3 )
  {
    sub_550C40(*(uint32_t *)(v4 + 68));
    sub_44AB50((uint32_t *)*(this + 2), 0, 12);
  }
  result = dword_9B88CC;
  if ( dword_9B88CC != 0 && dword_795374 == 1 )
    return sub_44E850((uint32_t *)*(this + 2), 18);
  return result;
}



// ------------------------------------------------------------
// 0x54ACD0 sub_54ACD0 —— 技能栏数据（40 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_54ACD0(uint32_t *this, char a2)
{
  int v2; // edi
  int v3; // esi
  LONG v4; // edx
  LONG v5; // ebx
  int v6; // eax
  int i; // [esp+Ch] [ebp-4h]

  v2 = 0;
  for ( i = 42 * *(uint32_t *)(*(this + 5) + 104) + 6; ; ++i )
  {
    v3 = *(this + 1);
    if ( a2 != 0 )
    {
      v4 = *(uint32_t *)(v3 + 20) + 37 * (v2 % 6) + 39;
      v5 = 37 * (v2 / 6) + *(uint32_t *)(v3 + 24) + 57;
    }
    else
    {
      v4 = *(uint32_t *)(v3 + 20) + 37 * (v2 % 6) + 35;
      v5 = 37 * (v2 / 6) + *(uint32_t *)(v3 + 24) + 53;
    }
    if ( pt.x >= v4 )
    {
      v6 = a2 != 0 ? 28 : 37;
      if ( pt.x < v6 + v4 && pt.y >= v5 && pt.y < v5 + v6 )
        break;
    }
    if ( ++v2 >= 42 )
      return -1;
  }
  return i;
}



// ------------------------------------------------------------
// 0x54AD80 CNRDSkillInventoryWindow__vmt14 —— CNRDSkillInventoryWindow__vmt14 关闭槽（54ACD0 + 41A5E0 + 44BC30）
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillInventoryWindow__vmt14(uint32_t *this)
{
  int v2; // eax
  int v4; // edi
  int *v5; // esi
  int v6; // eax
  int v7; // eax

  v2 = *(this + 1);
  if ( *(uint8_t *)(v2 + 17) == 0 || dword_79BE3C != *(uint32_t *)(v2 + 12) )
    return 0;
  v4 = sub_54ACD0(this, 1);
  if ( v4 == -1 )
    return 0;
  if ( v4 >= *(uint32_t *)dword_8F853C )
    return 0;
  v5 = *(int **)(*((uint32_t *)dword_8F853C + 1) + 4 * v4);
  if ( v5 == nullptr )
    return 0;
  v6 = *(uint32_t *)(*(this + 2) + 2504);
  if ( v6 == 10 || v6 == 11 )
    return 0;
  v7 = sub_41A5E0((unsigned int)(v5 + 1));
  sub_44BC30((uint32_t *)*(this + 2), (void *)1, 0, v7, v4, v5[95], v5);
  return 1;
}



// ------------------------------------------------------------
// 0x54AE10 CNRDSkillInventoryWindow__vmt1C —— CNRDSkillInventoryWindow__vmt1C 刷新槽（109 行：ICON_DROP 图标拖入事件 432EA0 + 460570/483E70/47E7A0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillInventoryWindow__vmt1C(uint32_t *this)
{
  int v2; // eax
  uint32_t *v4; // ebx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // edi
  unsigned int v13; // edi
  int v14; // esi
  int i; // edi
  int v16; // eax
  int *v17; // ecx
  int v18; // [esp+4h] [ebp-4h]
  int v19; // [esp+4h] [ebp-4h]

  v2 = *(this + 1);
  if ( *(uint8_t *)(v2 + 17) == 0 || dword_79BE34 != *(uint32_t *)(v2 + 12) )
    return 0;
  v4 = (uint32_t *)*(this + 2);
  v5 = v4[626];
  if ( v5 != 10 && v5 != 11 )
  {
    if ( v5 == 1 )
    {
      v6 = v4[627];
      if ( v6 != 0 )
      {
        if ( v6 == 1 )
        {
          v11 = sub_460570(dword_8F853C, v4[629]);
          v12 = v11;
          if ( v11 != 0 && sub_41A5E0(v11 + 4) == v4[628] )
          {
            v19 = *(uint32_t *)(*(this + 5) + 104);
            v13 = v12 + 128;
            if ( v19 == sub_41A5E0(v13) )
            {
              v14 = sub_54ACD0(this, 0);
              if ( v14 != -1 )
                goto LABEL_23;
            }
            v14 = 42 * sub_41A5E0(v13) + 6;
            for ( i = 0; i < 42; ++i )
            {
              if ( sub_460570(dword_8F853C, v14) == 0 )
                break;
              ++v14;
            }
            if ( v14 != -1 )
            {
LABEL_23:
              sub_483E70(v4[629], v14, 1);
              goto LABEL_24;
            }
          }
        }
      }
      else
      {
        v7 = sub_460570(dword_8F853C, v4[629]);
        v8 = v7;
        if ( v7 != 0 && sub_41A5E0(v7 + 4) == v4[628] )
        {
          v18 = *(uint32_t *)(*(this + 5) + 104);
          if ( v18 == sub_41A5E0(v8 + 128) )
          {
            v9 = sub_54ACD0(this, 1);
            if ( v9 != -1 )
            {
              v10 = v4[629];
              if ( v10 != v9 )
              {
                sub_483E70(v10, v9, 1);
LABEL_24:
                sub_432EA0("ICON_DROP", -1, 0, 0);
                return 1;
              }
            }
          }
        }
      }
    }
    return 0;
  }
  v16 = sub_54ACD0(this, 1);
  if ( v16 == -1 )
    return 0;
  if ( v16 >= *(uint32_t *)dword_8F853C )
    return 0;
  v17 = *(int **)(*((uint32_t *)dword_8F853C + 1) + 4 * v16);
  if ( v17 == nullptr )
    return 0;
  if ( v5 == 10 )
    sub_47E7A0(v17, 1u, 1);
  else
    sub_47E7A0(v17, 0, 1);
  return 1;
}



// ------------------------------------------------------------
// 0x54AFF0 CNRDSkillInventoryWindow__vmt18 —— CNRDSkillInventoryWindow__vmt18 页签动作（41A5E0 + 44AB90=TAB_SELECT 音）
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillInventoryWindow__vmt18(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // eax
  int v4; // eax
  int v5; // eax
  unsigned int v6; // esi
  void *v7; // eax

  v2 = *(this + 1);
  if ( *(uint8_t *)(v2 + 17) == 0 )
    return 0;
  if ( dword_79BE3C != *(uint32_t *)(v2 + 12) )
    return 0;
  v3 = (uint32_t *)*(this + 2);
  if ( v3[626] != 1 || v3[627] != 1 )
    return 0;
  v4 = v3[629];
  if ( v4 < *(uint32_t *)dword_8F853C )
  {
    v5 = *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * v4);
    if ( v5 != 0 )
    {
      v6 = v5 + 128;
      if ( sub_41A5E0(v5 + 128) != *(uint32_t *)(*(this + 5) + 104) )
      {
        v7 = (void *)sub_41A5E0(v6);
        sub_44AB90((uint32_t *)*(this + 2), v7);
      }
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x54B070 CNRDSkillInventoryWindow__vmt8 —— CNRDSkillInventoryWindow__vmt8 Update（73 行：CLICK_BUTTON2/WINDOW_CLOSE + 54ACD0/44AB90/44ABE0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDSkillInventoryWindow__vmt8(int *this)
{
  int v2; // ebx
  int v3; // eax
  int v4; // ecx
  int v5; // edi
  int v6; // edi
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  uint32_t *v11; // edx
  int v12; // eax
  int result; // eax

  v2 = *(this + 2);
  v3 = *(uint32_t *)(v2 + 2504);
  if ( v3 != 1
    && v3 != 2
    && *(uint8_t *)((v4 = *(this + 1)) + 17) != 0
    && ((v5 = *(uint32_t *)(v4 + 12), dword_79BE3C == v5) || dword_79BE34 == v5 || dword_79BE38 == v5)
    && (v6 = sub_54ACD0(this, 1)) != -1
    && v6 < *(uint32_t *)dword_8F853C
    && (v7 = *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * v6)) != 0 )
  {
    if ( dword_9B88CC != v7 || dword_795374 != 1 )
    {
      v8 = sub_44E8D0((char *)v2, (void *)0x12, v7, 1);
      if ( v8 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v8 + 48))(
          v8,
          37 * ((v6 - 42 * *(uint32_t *)(*(this + 5) + 104) - 6) % 6) + *(uint32_t *)(*(this + 1) + 20) + 39,
          37 * ((v6 - 42 * *(uint32_t *)(*(this + 5) + 104) - 6) / 6) + *(uint32_t *)(*(this + 1) + 24) + 57,
          28,
          28);
    }
  }
  else if ( dword_9B88CC != 0 && dword_795374 == 1 )
  {
    sub_44E850((uint32_t *)v2, 18);
  }
  v9 = *(this + 4);
  if ( *(uint8_t *)(v9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v9 + 12) )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 44))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    sub_432EA0("WINDOW_CLOSE", -1, 0, 0);
  }
  v10 = 0;
  v11 = this + 6;
  while ( *(uint8_t *)(*v11 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*v11 + 12) )
  {
    ++v10;
    ++v11;
    if ( v10 >= 5 )
      goto LABEL_26;
  }
  sub_44AB90((uint32_t *)*(this + 2), (void *)v10);
LABEL_26:
  v12 = *(this + 11);
  if ( *(uint8_t *)(v12 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v12 + 12) )
    sub_44ABE0((uint32_t *)*(this + 2), 10);
  result = *(this + 12);
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
    return sub_44ABE0((uint32_t *)*(this + 2), 11);
  return result;
}



// ------------------------------------------------------------
// 0x54B210 CNRDSkillInventoryWindow__vmt0 —— CNRDSkillInventoryWindow__vmt0 构造（47DF50 + 54ACD0 + 4F2E40）
// ------------------------------------------------------------
void /*thiscall*/ CNRDSkillInventoryWindow__vmt0(uint32_t *this, int a2)
{
  int v2; // ebx
  uint32_t *v3; // esi
  int *v4; // edx
  int v5; // edi
  int v6; // eax
  uint32_t *v7; // ecx
  int v8; // ecx
  int v9; // eax
  int v11; // [esp+Ch] [ebp-4h]

  v2 = a2;
  v3 = this;
  if ( a2 == *(this + 1) )
  {
    v4 = (int *)dword_8F853C;
    v5 = 0;
    v6 = 42 * *(uint32_t *)(*(this + 5) + 104) + 6;
    v11 = v6;
    do
    {
      if ( v6 < *v4 )
      {
        v7 = *(uint32_t **)(v4[1] + 4 * v6);
        if ( v7 != nullptr )
        {
          sub_47DF50(
            v7,
            *(uint32_t *)(v3[1] + 20) + 37 * (v5 % 6u) + 39,
            *(uint32_t *)(v3[1] + 24) + 37 * (v5 / 6u) + 57,
            -1,
            0,
            0,
            1,
            1);
          v4 = (int *)dword_8F853C;
          v3 = this;
          v2 = a2;
          v6 = v11;
        }
      }
      ++v5;
      v11 = ++v6;
    }
    while ( v5 < 42 );
    if ( *(uint8_t *)(v2 + 17) != 0 )
    {
      if ( dword_79BE3C == *(uint32_t *)(v2 + 12) || (v8 = *(uint32_t *)(v2 + 12), dword_79BE34 == v8) || dword_79BE38 == v8 )
      {
        v9 = sub_54ACD0(v3, 1);
        if ( v9 != -1 )
          sub_4F2E40(
            *(uint32_t *)(v3[1] + 20) + 37 * ((-6 - 42 * *(uint32_t *)(v3[5] + 104) + v9) % 6) + 39,
            *(uint32_t *)(v3[1] + 24) + 37 * ((-6 - 42 * *(uint32_t *)(v3[5] + 104) + v9) / 6) + 57);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x54B320 CNRDSkillInventoryWindow__vmt28 —— CNRDSkillInventoryWindow__vmt28 槽（54ACD0 + 41A5E0 + 47E7A0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillInventoryWindow__vmt28(uint32_t *this)
{
  int v1; // eax
  int v2; // eax
  int *v3; // esi
  int v4; // eax

  v1 = *(this + 1);
  if ( *(uint8_t *)(v1 + 17) == 0 )
    return 0;
  if ( dword_79BE38 != *(uint32_t *)(v1 + 12) )
    return 0;
  if ( *(uint32_t *)(*(this + 2) + 2504) != 0 )
    return 0;
  v2 = sub_54ACD0(this, 1);
  if ( v2 == -1 )
    return 0;
  if ( v2 < *(uint32_t *)dword_8F853C )
  {
    v3 = *(int **)(*((uint32_t *)dword_8F853C + 1) + 4 * v2);
    if ( v3 != nullptr )
    {
      v4 = sub_41A5E0((unsigned int)v3 + 558);
      sub_47E7A0(v3, v4 == 0, 1);
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x54B390 CNRDSkillInventoryWindow__vmtC —— CNRDSkillInventoryWindow__vmtC 打开槽（69C980 + 69A5F0 定位）
// ------------------------------------------------------------
char /*thiscall*/ CNRDSkillInventoryWindow__vmtC(char *this)
{
  char *v1; // ebx
  int v3; // ecx
  int v4; // edi
  int v5; // esi
  char *v6; // ebx
  int v7; // esi
  char *v8; // ebx
  int v9; // esi
  char *v10; // ebx
  int v11; // esi
  char *v12; // ebx
  uint32_t **v13; // edi
  int v14; // esi
  int i; // ebx

  v1 = this;
  if ( dword_8F7C04 == 0 )
    return 0;
  v3 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);
  v4 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
  if ( v3 != 0 )
  {
    switch ( v3 )
    {
      case 1:
        v7 = 33;
        v8 = v1 + 24;
        do
        {
          sub_69C980(v4, v7, v7, v7 - 1, -1, 0, 0);
          v7 += 2;
          v8 += 4;
        }
        while ( v7 < 41 );
        break;
      case 2:
        v9 = 98;
        v10 = v1 + 24;
        do
        {
          sub_69C980(v4, v9, v9, v9 - 1, -1, 0, 0);
          v9 += 2;
          v10 += 4;
        }
        while ( v9 < 108 );
        goto LABEL_19;
      case 3:
        v11 = 119;
        v12 = v1 + 24;
        do
        {
          sub_69C980(v4, v11, v11, v11 - 1, -1, 0, 0);
          v11 += 2;
          v12 += 4;
        }
        while ( v11 < 127 );
        break;
      default:
        goto LABEL_20;
    }
  }
  else
  {
    v5 = 25;
    v6 = v1 + 24;
    do
    {
      sub_69C980(v4, v5, v5, v5 - 1, -1, 0, 0);
      v5 += 2;
      v6 += 4;
    }
    while ( v5 < 33 );
  }
  sub_69C980(v4, 95, 95, 94, -1, 0, 0);
LABEL_19:
  v1 = this;
LABEL_20:
  v13 = (uint32_t **)(v1 + 24);
  v14 = 337;
  for ( i = 5; i != 0; --i )
  {
    sub_69A5F0(*v13, v14, 80);
    v14 += (*v13++)[7];
  }
  return 1;
}



// ------------------------------------------------------------
// 0x54B4E0 sub_54B4E0 —— 技能栏页绘制（98 行：43C250/43C410/69A5F0/69A840 + 46F7A0/46F880 + 69CE50/426BD0/69C780）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_54B4E0(uint32_t *this)
{
  uint8_t *v2; // eax
  uint8_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint8_t *v6; // eax
  uint8_t *v7; // eax
  uint32_t *v8; // edi
  uint8_t *v9; // eax
  uint8_t *v10; // eax
  uint8_t *v11; // edi
  int v12; // ebx
  uint32_t *v13; // ecx
  uint8_t *v14; // edi
  int v15; // ebx
  void *Block; // [esp+10h] [ebp-14h]
  int i; // [esp+14h] [ebp-10h]

  v2 = operator new(0x6Cu);
  if ( v2 != nullptr )
    v3 = sub_43C250(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 48), 0);
  else
    v3 = nullptr;
  *(this + 1) = v3;
  *((uint32_t *)v3 + 7) = *((uint32_t *)v3 + 7);
  *((uint32_t *)v3 + 8) = 353;
  *(uint32_t *)(*(this + 1) + 68) = this;
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 11, 12, 13, 11, 0, 0);
  else
    v5 = nullptr;
  *(this + 4) = v5;
  sub_69A5F0(v5, 51, 353);
  sub_69A840(*(this + 4));
  Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
  v6 = operator new(0x70u);
  if ( v6 != nullptr )
    v7 = sub_46F7A0(v6, 0);
  else
    v7 = nullptr;
  *(this + 5) = v7;
  v8 = this + 6;
  for ( i = 5; i != 0; --i )
  {
    v9 = operator new(0x88u);
    if ( v9 != nullptr )
      v10 = sub_46F880(v9, (int)Block, 95, 95, 94, -1, 0, 0);
    else
      v10 = nullptr;
    *v8 = v10;
    sub_69A840(v10);
    ++v8;
  }
  sub_69CE50(0);
  sub_69A840(*(this + 5));
  v11 = operator new(0x84u);
  if ( v11 != nullptr )
  {
    v12 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 48);
    sub_426BD0(v11);
    *(uint32_t *)v11 = &vftbl_nengine__CNButton;
    sub_69C780(v11);
    nengine__CNButton__vmt20(v12, 1, 2, 3, 1, 0, 0);
    v13 = v11;
  }
  else
  {
    v13 = nullptr;
  }
  *(this + 11) = v13;
  sub_69A5F0(v13, 80, 332);
  sub_69A840(*(this + 11));
  v14 = operator new(0x84u);
  if ( v14 != nullptr )
  {
    v15 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 48);
    sub_426BD0(v14);
    *(uint32_t *)v14 = &vftbl_nengine__CNButton;
    sub_69C780(v14);
    nengine__CNButton__vmt20(v15, 4, 5, 6, 4, 0, 0);
  }
  else
  {
    v14 = nullptr;
  }
  *(this + 12) = v14;
  sub_69A5F0(v14, 163, 332);
  sub_69A840(*(this + 12));
  return sub_69A5F0((uint32_t *)*(this + 1), 320, 63);
}



// ============================================================
// 【分区 14】状态窗口 CNRDStatusWindow（0x54B780-0x54C8B0）
// vmt0=构造（570 行：4938F0/491D00 部件 + 4E66B0/4DA0F0 属性面板装配）；
// vmt8=Update（CLICK_BUTTON2/WINDOW_CLOSE）。
// ============================================================
// ------------------------------------------------------------
// 0x54B780 sub_54B780 —— 技能栏辅助（22 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_54B780(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 4);
  *(this + 1) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x54B7B0 CNRDStatusWindow__vmt8 —— CNRDStatusWindow__vmt8 Update（CLICK_BUTTON2/WINDOW_CLOSE 音效）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDStatusWindow__vmt8(uint32_t *this)
{
  uint8_t *result; // eax

  if ( *(this + 5) == 0 )
    *(this + 5) = dword_8F7C04;
  result = (uint8_t *)*(this + 4);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 44))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    return sub_432EA0("WINDOW_CLOSE", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x54B800 CNRDStatusWindow__vmtC —— CNRDStatusWindow__vmtC 打开槽（418DD0）
// ------------------------------------------------------------
BOOL /*thiscall*/ CNRDStatusWindow__vmtC(uint32_t *this)
{
  int v2; // ecx
  bool v3; // zf
  uint32_t *v4; // eax

  v2 = dword_8F7C04;
  v3 = dword_8F7C04 == 0;
  *(this + 5) = dword_8F7C04;
  if ( !v3 )
  {
    v4 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 1032))(v2);
    *(this + 6) = sub_418DD0(*v4);
  }
  return *(this + 5) != 0;
}



// ------------------------------------------------------------
// 0x54B850 sub_54B850 —— 状态窗数据（418DD0，27 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_54B850(uint32_t *a1, int a2, int a3)
{
  if ( a2 >= a3 )
  {
    if ( a2 <= a3 )
    {
      *a1 = -1;
      return 0;
    }
    else
    {
      *a1 = -13487361;
      return sub_418DD0(2);
    }
  }
  else
  {
    *a1 = -14745706;
    return sub_418DD0(1);
  }
}



// ------------------------------------------------------------
// 0x54B8B0 sub_54B8B0 —— 状态窗页绘制（53 行：43C250/43C410/69A5F0/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_54B8B0(int this)
{
  uint8_t *v2; // eax
  uint8_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  int result; // eax

  v2 = operator new(0x6Cu);
  if ( v2 != nullptr )
    v3 = sub_43C250(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 52), 0);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 4) = v3;
  *((uint32_t *)v3 + 7) = *((uint32_t *)v3 + 7);
  *((uint32_t *)v3 + 8) = 353;
  *(uint32_t *)(*(uint32_t *)(this + 4) + 68) = this;
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 11, 12, 13, 11, 0, 0);
  else
    v5 = nullptr;
  *(uint32_t *)(this + 16) = v5;
  sub_69A5F0(v5, 221, 353);
  sub_69A840(*(uint32_t *)(this + 16));
  sub_69A5F0(*(uint32_t **)(this + 4), 29, 63);
  *(uint8_t *)(this + 28) = 0;
  *(uint8_t *)(this + 29) = 0;
  *(uint8_t *)(this + 30) = 0;
  *(uint8_t *)(this + 31) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 44) = 6;
  *(uint32_t *)(this + 48) = 12;
  *(uint32_t *)(this + 56) = 1600;
  result = dword_99FCCC;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 76) = result;
  *(uint32_t *)(this + 56) = 120;
  *(uint32_t *)(this + 40) = 2;
  return result;
}



// ------------------------------------------------------------
// 0x54B9F0 CNRDStatusWindow__vmt0 —— CNRDStatusWindow__vmt0 构造（570 行：4938F0/491D00/4924C0 部件 + 433F60/4176A0 + 4E66B0/4DA0F0 属性面板装配）
// ------------------------------------------------------------
int /*userpurge*/ sub_54B9F0@<eax>(float *a1@<ecx>, int a2@<ebx>, int a3@<edi>, uint32_t *a4)
{
  uint32_t *v5; // ecx
  int result; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // ebx
  int v10; // eax
  int v11; // ecx
  uint32_t *v12; // edi
  int v13; // eax
  int v14; // eax
  unsigned int v15; // ecx
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  unsigned int v19; // ecx
  int v20; // eax
  int v21; // eax
  int v22; // ebx
  char *v23; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // ebx
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // edx
  double v34; // st7
  float v35; // eax
  int v36; // ecx
  int v37; // eax
  int v38; // ebx
  int v39; // eax
  int v40; // eax
  int v41; // eax
  int v42; // eax
  int v43; // edx
  double v44; // st7
  int v45; // eax
  int v46; // eax
  int v47; // edx
  double v48; // st7
  int v49; // eax
  double v50; // st7
  int v51; // eax
  int v52; // ecx
  int v53; // ebx
  int v54; // eax
  int v55; // eax
  int v56; // eax
  double v57; // st7
  int v58; // eax
  int v59; // ecx
  int v60; // ebx
  int v61; // eax
  int v62; // eax
  int v63; // ebx
  int v64; // eax
  double v65; // st7
  int v66; // eax
  int v67; // eax
  int v68; // ebx
  int v69; // eax
  double v70; // st7
  int v71; // eax
  int v72; // esi
  int v73; // eax
  int v74; // eax
  int v75; // eax
  int v76; // eax
  int v77; // esi
  int v78; // eax
  int v79; // eax
  int v80; // esi
  int v81; // eax
  int v82; // eax
  int v83; // eax
  int v84; // eax
  int v85; // esi
  int v86; // eax
  int v87; // eax
  int v88; // ebx
  int v89; // eax
  int v90; // [esp-18h] [ebp-84h]
  uint32_t *v91; // [esp-14h] [ebp-80h]
  int v92; // [esp-10h] [ebp-7Ch]
  uint32_t *v93; // [esp-Ch] [ebp-78h]
  uint32_t *v94; // [esp-Ch] [ebp-78h]
  uint32_t *v95; // [esp-Ch] [ebp-78h]
  int v96; // [esp-Ch] [ebp-78h]
  int v97; // [esp-Ch] [ebp-78h]
  int v98; // [esp-Ch] [ebp-78h]
  int v99; // [esp-Ch] [ebp-78h]
  int v100; // [esp-Ch] [ebp-78h]
  int v101; // [esp-8h] [ebp-74h]
  int v103; // [esp-4h] [ebp-70h]
  int v104; // [esp-4h] [ebp-70h]
  int v105; // [esp+4h] [ebp-68h] BYREF
  int v106; // [esp+8h] [ebp-64h] BYREF
  float v107; // [esp+Ch] [ebp-60h]
  int v108; // [esp+10h] [ebp-5Ch]
  float v109; // [esp+14h] [ebp-58h]
  int v110; // [esp+18h] [ebp-54h]
  float v111; // [esp+1Ch] [ebp-50h]
  int v112; // [esp+20h] [ebp-4Ch]
  float v113; // [esp+24h] [ebp-48h]
  char Buffer[64]; // [esp+28h] [ebp-44h] BYREF
  int v115; // [esp+68h] [ebp-4h]

  v5 = *((uint32_t **)a1 + 1);
  v115 = dword_796E50;
  result = (int)a4;
  if ( a4 == v5 && *((uint32_t *)a1 + 5) != 0 )
  {
    v7 = *((uint32_t *)a1 + 6);
    v8 = a4[5];
    v9 = a4[6];
    v110 = v8;
    v112 = v9;
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v8 + 19, v9 + 22, dword_79C0B0);
    v10 = (*(int (/*thiscall*/ **)(uint32_t, int, int, int))(**((uint32_t **)a1 + 5) + 672))(*((uint32_t *)a1 + 5), 1, a3, a2);
    v11 = *((uint32_t *)a1 + 5);
    v108 = v10;
    v12 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 672))(v11, 3);
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
    v13 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)a1 + 5) + 832))(*((uint32_t *)a1 + 5));
    v111 = *(float *)&v13;
    a4 = (uint32_t *)(v110 + 130);
    if ( v13 != 0 )
    {
      sub_4938F0(v13);
      sub_491D00(dword_79C0B0, (int)a4 - 2, v9 + 24, 0.0);
      a4 = (uint32_t *)((char *)a4 + *(uint32_t *)(*(uint32_t *)sub_4924C0(0) + 36) - 1);
    }
    v14 = *((uint32_t *)a1 + 5);
    v15 = *(uint32_t *)(v14 + 312);
    v16 = v14 + 288;
    if ( v15 < 0x10 )
      v17 = v16 + 4;
    else
      v17 = *(uint32_t *)(v16 + 4);
    (*(void (/*cdecl*/ **)(int, uint32_t *, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      a4,
      v9 + 27,
      -1,
      v17);
    v18 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)a1 + 5) + 1032))(*((uint32_t *)a1 + 5));
    v19 = *(uint32_t *)(v18 + 36);
    v20 = v18 + 12;
    if ( v19 < 0x10 )
      v21 = v20 + 4;
    else
      v21 = *(uint32_t *)(v20 + 4);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v110 + 130,
      v9 + 48,
      -1,
      v21);
    (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v110 + 143,
      v9 + 69,
      -1,
      "Lv.%2d",
      *v12);
    v22 = *(uint32_t *)dword_79C0B0;
    v103 = dword_8F7C1C;
    v101 = dword_8F7C18;
    v23 = sub_422E70(499);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *, int, int))(v22 + 80))(
      dword_79C0B0,
      v110 + 130,
      v112 + 90,
      -1,
      v23,
      v101,
      v103);
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, (uint32_t *)a1 + 7);
    v24 = *(uint32_t *)dword_79C0B0;
    a4 = *((uint32_t **)a1 + 5);
    v25 = (*(int (**)(void))(*a4 + 1032))();
    v26 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*a4 + 1032))(a4, *(uint32_t *)(v25 + 44));
    (*(void (/*cdecl*/ **)(int, int, int, int, const char *, uint32_t))(v24 + 80))(
      dword_79C0B0,
      v110 + 148,
      v112 + 69,
      -1,
      "%d / %d",
      *(uint32_t *)(v26 + 40));
    a4 = nullptr;
    v111 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 1)));
    v107 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 18));
    v109 = COERCE_FLOAT(sub_41A5E0(v108 + 4));
    v113 = COERCE_FLOAT(sub_41A5E0(v108 + 18));
    v27 = sub_54B850(
            &a4,
            (uint64_t)((double)SLODWORD(v109) * v113),
            (uint64_t)((double)SLODWORD(v111) * v107));
    if ( v27 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v27 + 152))(v27, v110 + 82, v112 + 129, dword_79C0B0);
    v28 = *(uint32_t *)dword_79C0B0;
    v113 = a1[5];
    v29 = (*(int (**)(void))(*(uint32_t *)LODWORD(v113) + 740))();
    v30 = (*(int (/*thiscall*/ **)(float, int))(*(uint32_t *)LODWORD(v113) + 736))(COERCE_FLOAT(LODWORD(v113)), v29);
    (*(void (/*cdecl*/ **)(int, int, int, uint32_t *, const char *, int))(v28 + 80))(
      dword_79C0B0,
      v110 + 17,
      v112 + 128,
      a4,
      "%d/%d",
      v30);
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 15)));
    v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 74));
    v107 = COERCE_FLOAT(sub_41A5E0(v108 + 60));
    v111 = COERCE_FLOAT(sub_41A5E0(v108 + 74));
    v31 = sub_54B850(
            &a4,
            (uint64_t)((double)SLODWORD(v107) * v111),
            (uint64_t)((double)SLODWORD(v113) * v109));
    if ( v31 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v31 + 152))(v31, v110 + 82, v112 + 156, dword_79C0B0);
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 15)));
    v32 = sub_41A5E0((unsigned int)v12 + 74);
    v33 = *((uint32_t *)a1 + 5);
    v109 = *(float *)&v32;
    v34 = sub_433F60(v33, 3);
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v110 + 17,
      v112 + 155,
      a4,
      "%d",
      (unsigned int)(uint64_t)(v34 * (double)(int)(uint64_t)((double)SLODWORD(v113) * v109)));
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 29)));
    v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 130));
    v107 = COERCE_FLOAT(sub_41A5E0(v108 + 116));
    v111 = COERCE_FLOAT(sub_41A5E0(v108 + 130));
    v107 = COERCE_FLOAT(
             sub_54B850(
               &a4,
               (uint64_t)((double)SLODWORD(v107) * v111),
               (uint64_t)((double)SLODWORD(v113) * v109)));
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 29)));
    v35 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 130));
    v36 = *((uint32_t *)a1 + 5);
    v109 = v35;
    v113 = sub_433F60(v36, 5) * (double)(int)(uint64_t)((double)SLODWORD(v113) * v35);
    if ( v107 != 0.0 )
      (*(void (/*thiscall*/ **)(float, int, int, int))(*(uint32_t *)LODWORD(v107) + 152))(
        COERCE_FLOAT(LODWORD(v107)),
        v110 + 82,
        v112 + 183,
        dword_79C0B0);
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v110 + 17,
      v112 + 182,
      a4,
      "%d",
      (unsigned int)(uint64_t)v113);
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 8)));
    v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 46));
    v107 = COERCE_FLOAT(sub_41A5E0(v108 + 32));
    v111 = COERCE_FLOAT(sub_41A5E0(v108 + 46));
    v37 = sub_54B850(
            &a4,
            (uint64_t)((double)SLODWORD(v107) * v111),
            (uint64_t)((double)SLODWORD(v113) * v109));
    if ( v37 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v37 + 152))(v37, v110 + 211, v112 + 129, dword_79C0B0);
    v38 = *(uint32_t *)dword_79C0B0;
    v113 = a1[5];
    v39 = (*(int (**)(void))(*(uint32_t *)LODWORD(v113) + 756))();
    v40 = (*(int (/*thiscall*/ **)(float, int))(*(uint32_t *)LODWORD(v113) + 752))(COERCE_FLOAT(LODWORD(v113)), v39);
    (*(void (/*cdecl*/ **)(int, int, int, uint32_t *, const char *, int))(v38 + 80))(
      dword_79C0B0,
      v110 + 148,
      v112 + 128,
      a4,
      "%d/%d",
      v40);
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 22)));
    v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 102));
    v107 = COERCE_FLOAT(sub_41A5E0(v108 + 88));
    v111 = COERCE_FLOAT(sub_41A5E0(v108 + 102));
    v41 = sub_54B850(
            &a4,
            (uint64_t)((double)SLODWORD(v107) * v111),
            (uint64_t)((double)SLODWORD(v113) * v109));
    if ( v41 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v41 + 152))(v41, v110 + 211, v112 + 156, dword_79C0B0);
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 22)));
    v42 = sub_41A5E0((unsigned int)v12 + 102);
    v43 = *((uint32_t *)a1 + 5);
    v109 = *(float *)&v42;
    v44 = sub_433F60(v43, 4);
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v110 + 148,
      v112 + 155,
      a4,
      "%d",
      (unsigned int)(uint64_t)(v44 * (double)(int)(uint64_t)((double)SLODWORD(v113) * v109)));
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 36)));
    v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 158));
    v107 = COERCE_FLOAT(sub_41A5E0(v108 + 144));
    v111 = COERCE_FLOAT(sub_41A5E0(v108 + 158));
    v45 = sub_54B850(
            &a4,
            (uint64_t)((double)SLODWORD(v107) * v111),
            (uint64_t)((double)SLODWORD(v113) * v109));
    if ( v45 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v45 + 152))(v45, v110 + 211, v112 + 183, dword_79C0B0);
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 36)));
    v46 = sub_41A5E0((unsigned int)v12 + 158);
    v47 = *((uint32_t *)a1 + 5);
    v109 = *(float *)&v46;
    v48 = sub_433F60(v47, 6);
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v110 + 148,
      v112 + 182,
      a4,
      "%d",
      (unsigned int)(uint64_t)(v48 * (double)(int)(uint64_t)((double)SLODWORD(v113) * v109)));
    LODWORD(v113) = v108 + 1124;
    if ( sub_41A5E0(v108 + 1124) != 0 || sub_41A5E0((unsigned int)(v12 + 281)) != 0 )
    {
      v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 281)));
      v49 = sub_41A5E0(LODWORD(v113));
      sub_54B850(&a4, v49, LODWORD(v109));
      v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 281)));
      v50 = sub_433F60(*((uint32_t *)a1 + 5), 7) * (double)SLODWORD(v113);
      sprintf(Buffer, off_724968, (unsigned int)(uint64_t)v50);
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t *, char *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v110 + 17,
        v112 + 216,
        a4,
        Buffer);
    }
    else
    {
      Buffer[0] = 0;
    }
    v51 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, int))(**((uint32_t **)a1 + 5) + 708))(*((uint32_t *)a1 + 5), 0, 1);
    v52 = *((uint32_t *)a1 + 5);
    v111 = *(float *)&v51;
    v53 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v52 + 708))(v52, 0, 3);
    v54 = sub_54B850(&a4, LODWORD(v111), v53);
    if ( v54 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v54 + 152))(v54, v110 + 82, v112 + 217, dword_79C0B0);
    v93 = a4;
    v113 = *(float *)dword_79C0B0;
    v55 = sub_4176A0(Buffer);
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(LODWORD(v113) + 80))(
      dword_79C0B0,
      v110 - v55 + 17,
      v112 + 216,
      v93,
      "%d",
      v53);
    LODWORD(v113) = v108 + 1166;
    if ( sub_41A5E0(v108 + 1166) != 0 || sub_41A5E0((unsigned int)v12 + 1166) != 0 )
    {
      v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 1166));
      v56 = sub_41A5E0(LODWORD(v113));
      sub_54B850(&a4, v56, LODWORD(v109));
      v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 1166));
      v57 = sub_433F60(*((uint32_t *)a1 + 5), 9) * (double)SLODWORD(v113);
      sprintf(Buffer, off_724968, (unsigned int)(uint64_t)v57);
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t *, char *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v110 + 17,
        v112 + 242,
        a4,
        Buffer);
    }
    else
    {
      Buffer[0] = 0;
    }
    v58 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**((uint32_t **)a1 + 5) + 708))(*((uint32_t *)a1 + 5), 1, 1);
    v59 = *((uint32_t *)a1 + 5);
    v111 = *(float *)&v58;
    v60 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v59 + 708))(v59, 1, 3);
    v61 = sub_54B850(&a4, LODWORD(v111), v60);
    if ( v61 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v61 + 152))(v61, v110 + 82, v112 + 243, dword_79C0B0);
    v94 = a4;
    v113 = *(float *)dword_79C0B0;
    v62 = sub_4176A0(Buffer);
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(LODWORD(v113) + 80))(
      dword_79C0B0,
      v110 - v62 + 17,
      v112 + 242,
      v94,
      "%d",
      v60);
    v105 = 0;
    v106 = 0;
    v111 = COERCE_FLOAT(sub_4E66B0(0));
    if ( sub_41A5E0(v108 + 1138) != 0 || sub_41A5E0((unsigned int)v12 + 1138) != 0 )
    {
      v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 1138));
      v64 = sub_41A5E0(v108 + 1138);
      sub_54B850(&a4, v64, LODWORD(v113));
      v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 1138));
      v65 = sub_433F60(*((uint32_t *)a1 + 5), 8) * (double)SLODWORD(v113);
      sprintf(Buffer, off_724968, (unsigned int)(uint64_t)v65);
      v63 = v112;
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t *, char *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v110 + 148,
        v112 + 216,
        a4,
        Buffer);
    }
    else
    {
      v63 = v112;
      Buffer[0] = 0;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int *, float, uint32_t, int))(**((uint32_t **)a1 + 5) + 712))(
      *((uint32_t *)a1 + 5),
      &v105,
      COERCE_FLOAT(LODWORD(v111)),
      0,
      1);
    (*(void (/*thiscall*/ **)(uint32_t, int *, float, uint32_t, int))(**((uint32_t **)a1 + 5) + 712))(
      *((uint32_t *)a1 + 5),
      &v106,
      COERCE_FLOAT(LODWORD(v111)),
      0,
      3);
    v66 = sub_54B850(&a4, v105, v106);
    if ( v66 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v66 + 152))(v66, v110 + 211, v63 + 217, dword_79C0B0);
    v104 = v106;
    v95 = a4;
    v92 = v63 + 216;
    v113 = *(float *)dword_79C0B0;
    v67 = sub_4176A0(Buffer);
    v68 = v110;
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(LODWORD(v113) + 80))(
      dword_79C0B0,
      v110 - v67 + 148,
      v92,
      v95,
      "%d",
      v104);
    if ( sub_41A5E0(v108 + 1180) != 0 || sub_41A5E0((unsigned int)(v12 + 295)) != 0 )
    {
      v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 295)));
      v69 = sub_41A5E0(v108 + 1180);
      sub_54B850(&a4, v69, LODWORD(v113));
      v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 295)));
      v70 = sub_433F60(*((uint32_t *)a1 + 5), 10);
      sprintf(Buffer, off_724968, (unsigned int)(uint64_t)(v70 * (double)SLODWORD(v113)));
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t *, char *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v68 + 148,
        v112 + 242,
        a4,
        Buffer);
    }
    else
    {
      Buffer[0] = 0;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int *, float))(**((uint32_t **)a1 + 5) + 712))(
      *((uint32_t *)a1 + 5),
      &v105,
      COERCE_FLOAT(LODWORD(v111)));
    (*(void (/*thiscall*/ **)(uint32_t, int *, float, int, int))(**((uint32_t **)a1 + 5) + 712))(
      *((uint32_t *)a1 + 5),
      &v106,
      COERCE_FLOAT(LODWORD(v111)),
      1,
      3);
    v71 = sub_54B850(&a4, v105, v106);
    if ( v71 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v71 + 152))(v71, v68 + 211, v112 + 243, dword_79C0B0);
    v72 = *(uint32_t *)dword_79C0B0;
    v96 = v106;
    v91 = a4;
    v90 = v112 + 242;
    v73 = sub_4176A0(Buffer);
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(v72 + 80))(
      dword_79C0B0,
      v68 - v73 + 148,
      v90,
      v91,
      "%d",
      v96);
    v97 = sub_4DA0F0(0);
    v74 = sub_4DA0F0(0);
    v75 = sub_54B850(&a4, v74, v97);
    if ( v75 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v75 + 152))(v75, v68 + 79, v112 + 299, dword_79C0B0);
    v113 = *(float *)dword_79C0B0;
    v76 = sub_4DA0F0(0);
    v77 = v112;
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(LODWORD(v113) + 80))(
      dword_79C0B0,
      v68 + 17,
      v112 + 298,
      a4,
      "%d",
      v76);
    v98 = sub_4DA0F0(3);
    v78 = sub_4DA0F0(3);
    v79 = sub_54B850(&a4, v78, v98);
    if ( v79 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v79 + 152))(v79, v68 + 79, v77 + 326, dword_79C0B0);
    LODWORD(v111) = v77 + 325;
    v80 = *(uint32_t *)dword_79C0B0;
    v81 = sub_4DA0F0(3);
    (*(void (**)(int, int, float, uint32_t *, const char *, ...))(v80 + 80))(
      dword_79C0B0,
      v68 + 17,
      COERCE_FLOAT(LODWORD(v111)),
      a4,
      "%d",
      v81);
    v99 = sub_4DA0F0(1);
    v82 = sub_4DA0F0(1);
    v83 = sub_54B850(&a4, v82, v99);
    if ( v83 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v83 + 152))(v83, v68 + 210, v112 + 299, dword_79C0B0);
    v113 = *(float *)dword_79C0B0;
    v84 = sub_4DA0F0(1);
    v85 = v68 + 148;
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(LODWORD(v113) + 80))(
      dword_79C0B0,
      v68 + 148,
      v112 + 298,
      a4,
      "%d",
      v84);
    v100 = sub_4DA0F0(2);
    v86 = sub_4DA0F0(2);
    v87 = sub_54B850(&a4, v86, v100);
    if ( v87 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v87 + 152))(v87, v68 + 210, v112 + 326, dword_79C0B0);
    v88 = *(uint32_t *)dword_79C0B0;
    v89 = sub_4DA0F0(2);
    (*(void (**)(int, int, float, uint32_t *, const char *, ...))(v88 + 80))(
      dword_79C0B0,
      v85,
      COERCE_FLOAT(LODWORD(v111)),
      a4,
      "%d",
      v89);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  }
  return result;
}


// ============================================================
// 【分区 15】物品工具窗 CNRDItemToolWindow（0x54C8B0-0x54D6E0）
// 工具面板绘制 0x54CA00/0x54CC00；vmt1C=刷新（44F580/44F670 格子）;
// vmt8=Update（CLICK_BUTTON2 + 486E00/486E80 格子操作）。
// ============================================================
// ------------------------------------------------------------
// 0x54C8B0 sub_54C8B0 —— 24 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_54C8B0(uint32_t *this)
{
  *(this + 4) = 0;
  *(this + 8) = 0;
  *(this + 31) = 0;
  *(this + 32) = 0;
  *(this + 33) = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
  *(this + 6) = 0;
  *(this + 5) = 0;
  *(this + 7) = 0;
  *(this + 16) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 30) = -1;
  return 0;
}



// ------------------------------------------------------------
// 0x54C8F0 sub_54C8F0 —— 状态窗辅助（47 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_54C8F0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 31);
  *(this + 1) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 32);
  *(this + 31) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 33);
  *(this + 32) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  v7 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 34);
  *(this + 33) = 0;
  if ( v7 != nullptr )
    result = (**v7)(v7, 1);
  v8 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 37);
  *(this + 34) = 0;
  if ( v8 != nullptr )
    result = (**v8)(v8, 1);
  v9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 36);
  *(this + 37) = 0;
  if ( v9 != nullptr )
    result = (**v9)(v9, 1);
  *(this + 36) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x54C990 sub_54C990 —— 状态窗联动（56CFE0 频道选择复用）
// ------------------------------------------------------------
int /*thiscall*/ sub_54C990(uint32_t *this, int a2)
{
  int result; // eax

  if ( a2 != 0 )
  {
    result = a2 - 1;
    if ( a2 == 1 )
    {
      *(uint8_t *)(*(this + 37) + 16) = 1;
      *(uint8_t *)(*(this + 36) + 16) = 0;
      result = sub_56CFE0(13);
      *(this + 4) = 1;
      *(this + 6) = result;
    }
  }
  else
  {
    *(uint8_t *)(*(this + 37) + 16) = 0;
    *(uint8_t *)(*(this + 36) + 16) = 1;
    result = sub_56CFE0(17);
    *(this + 6) = result;
    *(this + 4) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x54CA00 sub_54CA00 —— 工具窗面板绘制（491530/491630 批次 + 418DD0，100 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_54CA00(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  unsigned int v5; // ecx
  int v6; // eax
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  unsigned int v17; // [esp+Ch] [ebp-Ch]
  int v18; // [esp+10h] [ebp-8h]
  unsigned int v19; // [esp+14h] [ebp-4h]
  uint8_t v20; // [esp+24h] [ebp+Ch]

  v4 = sub_699000((int)(this + 9));
  v5 = *(this + 7);
  v17 = v4;
  v18 = v5 & 1;
  v19 = v5 % 3;
  if ( *(this + 5) != 0 )
  {
    v10 = sub_418DD0(v5 % 3 + 20);
    v7 = a3;
    v8 = a2;
    if ( v10 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(v10, a2 + 232, a3 + 127, dword_79C0B0);
    v9 = sub_418DD0(v19 + 17);
  }
  else
  {
    v6 = sub_418DD0(20);
    v7 = a3;
    v8 = a2;
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, a2 + 232, a3 + 127, dword_79C0B0);
    v9 = sub_418DD0(17);
  }
  if ( v9 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, v8 + 34, v7 + 127, dword_79C0B0);
  v11 = sub_418DD0(v19 + 34);
  if ( v11 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(v11, v8 + 87, v7 + 150, dword_79C0B0);
  v12 = sub_418DD0(30);
  if ( v12 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(v12, v8 + 61, v7 + 127, dword_79C0B0);
  sub_491530(2, 0);
  if ( *(this + 5) != 0 )
  {
    v13 = sub_418DD0(v19 + 31);
    if ( v13 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v13 + 152))(v13, v8 + 83, v7 + 127, dword_79C0B0);
  }
  if ( v17 > 0x7D0 )
  {
    if ( v17 <= 0x8CF )
    {
      v14 = sub_418DD0(v18 + 15);
      if ( v14 != 0 )
      {
        v15 = (uint8_t)(-49 - v17);
        goto LABEL_25;
      }
    }
  }
  else
  {
    v20 = v17;
    if ( v17 >= 0xFF )
      v20 = -1;
    v14 = sub_418DD0(v18 + 15);
    if ( v14 != 0 )
    {
      v15 = v20;
LABEL_25:
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
        v14,
        v8 + 72,
        v7 + 127,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (v15 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    }
  }
  return sub_491630(2);
}



// ------------------------------------------------------------
// 0x54CC00 sub_54CC00 —— 工具窗面板绘制 2（164 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_54CC00(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // eax
  unsigned int v12; // edi
  int result; // eax
  int v14; // esi
  uint64_t v15; // rax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  uint32_t v20[5]; // [esp+Ch] [ebp-20h]
  unsigned int v21; // [esp+20h] [ebp-Ch]
  uint32_t *v22; // [esp+24h] [ebp-8h]
  uint8_t v23; // [esp+29h] [ebp-3h]
  uint8_t v24; // [esp+2Ah] [ebp-2h]
  uint8_t v25; // [esp+2Bh] [ebp-1h]

  v4 = *(this + 5);
  v22 = this;
  if ( v4 != 0 )
    v5 = *(this + 7) & 1;
  else
    v5 = 0;
  v21 = *(this + 7) % 7u;
  v6 = sub_418DD0(v5 != 0 ? 4 : 1);
  if ( v6 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, a2 + 34, a3 + 127, dword_79C0B0);
  v7 = sub_418DD0(v5 != 0 ? 6 : 3);
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, a2 + 190, a3 + 127, dword_79C0B0);
  v8 = sub_418DD0(5);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, a2 + 100, a3 + 127, dword_79C0B0);
  v9 = *(this + 18);
  if ( v9 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, a2 + 131, a3 + 154, dword_79C0B0);
  sub_491530(2, 0);
  v10 = sub_418DD0(v21 + 8);
  if ( v10 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(v10, a2 + 113, a3 + 137, dword_79C0B0);
  sub_491630(2);
  v11 = sub_418DD0(2);
  if ( v11 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(v11, a2 + 100, a3 + 127, dword_79C0B0);
  v12 = sub_699000((int)(this + 9));
  result = sub_699000((int)(this + 9));
  if ( result <= 5900 )
  {
    v20[0] = 1000;
    v20[1] = 500;
    v20[2] = 250;
    v20[3] = 125;
    v20[4] = 0;
    if ( v12 >= 0xFA0 )
    {
      if ( v12 >= 0x1004 )
      {
        if ( v12 >= 0x1130 )
        {
          v21 = v12 - 4400;
          v23 = (uint64_t)((1.0 - sin((double)(v12 - 4400) * 0.001047197551196598)) * 255.0);
        }
        else
        {
          v23 = -1;
        }
        v25 = 0;
        v24 = 0;
      }
      else
      {
        v21 = v12 - 3900;
        v23 = (uint64_t)((1.0 - sin((double)(v12 - 3900) * 0.01570796326794897)) * 255.0);
        v25 = 127;
        v24 = 127;
      }
    }
    else
    {
      v21 = v12;
      v23 = 0;
      v14 = (uint8_t)(v12 / 0x3E8);
      v15 = (uint64_t)((sin((double)v12 * 6.283185307179586 / (double)(unsigned int)v20[v14]) + 1.0) * 127.0);
      if ( (uint8_t)(v12 / 0x3E8) != 0 && v22[30] != 0 )
      {
        v25 = (-46 - 45 * v14 - v15) & ((210 - 45 * v14 - (uint8_t)v15 <= 0) - 1);
        v24 = v15;
      }
      else
      {
        v25 = v15;
        v24 = (-46 - 45 * v14 - v15) & ((210 - 45 * v14 - (uint8_t)v15 <= 0) - 1);
      }
    }
    sub_491530(2, 0);
    v16 = sub_418DD0(7);
    if ( v16 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v16 + 128))(
        v16,
        a2 + 100,
        a3 + 127,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (v23 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v17 = sub_418DD0(55);
    if ( v17 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v17 + 128))(
        v17,
        a2 + 187,
        a3 + 154,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (v25 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v18 = sub_418DD0(54);
    if ( v18 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v18 + 128))(
        v18,
        a2 + 167,
        a3 + 154,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (v24 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v19 = sub_418DD0(56);
    if ( v19 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v19 + 128))(
        v19,
        a2 + 167,
        a3 + 154,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (v23 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    return sub_491630(2);
  }
  return result;
}


// ------------------------------------------------------------
// 0x54D020 CNRDItemToolWindow__vmt0 —— CNRDItemToolWindow__vmt0 构造（54CA00 + 54CC00）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemToolWindow__vmt0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // ecx
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // eax
  int v10; // [esp+Ch] [ebp+8h]

  result = a2;
  if ( a2 == *(this + 1) )
  {
    v4 = *(uint32_t *)(a2 + 24);
    v5 = *(uint32_t *)(a2 + 20);
    v6 = *(this + 6);
    v10 = v4;
    if ( v6 != 0 )
    {
      v7 = *(uint32_t *)(v6 + 60);
      if ( v7 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v5 + 28, v4 + 26, dword_79C0B0);
    }
    v8 = *(this + 5);
    *(this + 7) = timeGetTime() / (v8 != 0 ? 100 : 300);
    v9 = *(this + 4);
    if ( v9 != 0 )
    {
      result = v9 - 1;
      if ( result == 0 )
        return sub_54CA00(this, v5, v10);
    }
    else
    {
      return sub_54CC00(this, v5, v10);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x54D0C0 sub_54D0C0 —— 工具窗动画切换（69C340/69C360/69C500）——强化结果窗 0x63AC20 复用
// ------------------------------------------------------------
int /*thiscall*/ sub_54D0C0(int **this, int a2)
{
  unsigned int v3; // eax
  int *v4; // ecx
  int v5; // edi
  int v6; // eax

  sub_69C340(-1);
  sub_69C360(a2, 0);
  v3 = sub_69C500(*(this + 31));
  v4 = *(this + 35);
  if ( v3 <= 5 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*v4 + 32))(v4, 0);
  v5 = *v4;
  v6 = sub_69C500(*(this + 31));
  return (*(int (/*thiscall*/ **)(uint32_t, int))(v5 + 32))(*(this + 35), v6 - 5);
}



// ------------------------------------------------------------
// 0x54D120 sub_54D120 —— 工具窗条目（422E70/44E8D0 + 484ED0）
// ------------------------------------------------------------
char /*thiscall*/ sub_54D120(uint32_t *this)
{
  char *v2; // eax

  if ( (unsigned int)(*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C
                                                                                               + 3)) < *(this + 29) )
  {
    v2 = sub_422E70(1660);
LABEL_9:
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);
    return 0;
  }
  if ( sub_484ED0(*(this + 17)) == -1
    || (unsigned int)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 17) + 44))(*(this + 17)) >= *(this + 28) )
  {
    if ( (int)sub_484ED0(*(this + 16)) < 0 )
    {
      v2 = sub_422E70(1658);
      goto LABEL_9;
    }
    if ( (int)sub_484ED0(*(this + 17)) >= 0 )
      return 1;
  }
  v2 = sub_422E70(1661);
  goto LABEL_9;
}



// ------------------------------------------------------------
// 0x54D1C0 CNRDItemToolWindow__vmt1C —— CNRDItemToolWindow__vmt1C 刷新槽（44F580/44F670 格子）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemToolWindow__vmt1C(int *this)
{
  int v2; // eax
  uint32_t *v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // esi
  int v8; // eax

  v2 = *(this + 1);
  if ( *(uint8_t *)(v2 + 17) == 0 || dword_79BE34 != *(uint32_t *)(v2 + 12) )
    return 0;
  v4 = (uint32_t *)*(this + 2);
  if ( v4[626] != 2 )
    return 0;
  v5 = v4[627];
  if ( v5 != 3 && v5 != 4 )
    return 0;
  v6 = v4[629];
  if ( v6 >= *((uint32_t *)dword_8F852C + 2) )
    return 0;
  v7 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v6);
  if ( v7 == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 16))(v7) + 4) != v4[628] )
    return 0;
  v8 = *(this + 4);
  if ( v8 != 0 )
  {
    if ( v8 == 1 )
    {
      sub_44F580(*(this + 2), v7, 1);
      return 1;
    }
  }
  else
  {
    sub_44F670(*(this + 2), v7, 1);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x54D260 CNRDItemToolWindow__vmt10 —— CNRDItemToolWindow__vmt10 状态切换（44ABE0 + 44E850）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemToolWindow__vmt10(uint32_t *this)
{
  uint32_t *v2; // ecx
  int v3; // eax
  char result; // al

  v2 = (uint32_t *)*(this + 2);
  v3 = v2[626];
  if ( v3 == 18 || v3 == 7 )
    sub_44ABE0(v2, 0);
  sub_44E850((uint32_t *)*(this + 2), 23);
  result = sub_44E850((uint32_t *)*(this + 2), 59);
  *(this + 16) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x54D2B0 sub_54D2B0 —— 21 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_54D2B0(uint32_t *this, int a2)
{
  int result; // eax

  if ( *(this + 5) == 2 )
  {
    *(this + 5) = 0;
    *(this + 16) = 0;
    *(this + 17) = 0;
    *(this + 18) = 0;
    *(this + 30) = -1;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x54D600 CNRDItemToolWindow__vmt8 —— CNRDItemToolWindow__vmt8 Update（98 行：CLICK_BUTTON2 + 69C690/69C400 + 486E00/486E80/54D120）
// ------------------------------------------------------------
char /*thiscall*/ CNRDItemToolWindow__vmt8(int this)
{
  int v1; // eax
  char *v2; // eax
  int v3; // edi
  int v4; // eax
  char *v5; // eax
  int v7; // eax
  int v8; // edi
  int i; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax

  v7 = sub_69C690(*(uint32_t *)(this + 140));
  sub_69C400(v7);
  v8 = this + 128;
  for ( i = 2; i != 0; --i )
  {
    if ( *(uint8_t *)(*(uint32_t *)v8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(*(uint32_t *)v8 + 12) )
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    v8 += 4;
  }
  v10 = *(uint32_t *)(this + 148);
  if ( *(uint8_t *)(v10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v10 + 12) )
  {
    sub_44ABE0(*(uint32_t **)(this + 8), 7);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v11 = *(uint32_t *)(this + 144);
  if ( *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v11 + 12) )
  {
    sub_44ABE0(*(uint32_t **)(this + 8), 18);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v12 = *(uint32_t *)(this + 16);
  if ( v12 != 0 )
  {
    if ( --v12 == 0 && *(uint32_t *)(this + 20) == 1 )
    {
      v12 = sub_699000(this + 36);
      if ( v12 > 2000 )
      {
        v1 = sub_484ED0(*(uint32_t *)(this + 64));
        if ( v1 >= 0 )
        {
          LOBYTE(v12) = sub_486E00(v1);
          if ( (uint8_t)v12 != 0 )
          {
            *(uint32_t *)(this + 20) = 2;
            return v12;
          }
          v2 = sub_422E70(1659);
        }
        else
        {
          v2 = sub_422E70(1658);
        }
        LOBYTE(v12) = sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);
        *(uint32_t *)(this + 20) = 0;
        *(uint32_t *)(this + 64) = 0;
      }
    }
  }
  else if ( *(uint32_t *)(this + 20) == 1 )
  {
    v12 = sub_699000(this + 36);
    if ( v12 > 5900 )
    {
      LOBYTE(v12) = sub_54D120((uint32_t *)this);
      if ( (uint8_t)v12 == 1 )
      {
        v3 = sub_484ED0(*(uint32_t *)(this + 64));
        v4 = sub_484ED0(*(uint32_t *)(this + 68));
        LOBYTE(v12) = sub_486E80(v3, v4);
        if ( (uint8_t)v12 != 0 )
        {
          *(uint32_t *)(this + 20) = 2;
          return v12;
        }
        v5 = sub_422E70(1659);
        LOBYTE(v12) = sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v5, 0);
      }
      *(uint32_t *)(this + 64) = 0;
      *(uint32_t *)(this + 68) = 0;
      *(uint32_t *)(this + 72) = 0;
      *(uint32_t *)(this + 20) = 0;
      *(uint32_t *)(this + 120) = -1;
    }
  }
  return v12;
}



// ============================================================
// 【分区 16】PVP 结算界面 CNRDPVPResult（0x54D6E0-0x54FFB0）
// 结算动画事件 0x54F540（MAP_APPEAR/M_RESULT/RESULT_COME）；
// vmt0(0x54F9E0, 160 行)=结算构造（VICTORY_UP_LOOP 胜利抬头 /
// DEFEAT_DOWN_LOOP 失败低头 / RANK_UP 升段 / RESULT_CHARACTER 角色展示）；
// 结算窗口入队 0x54FFB0（被 cashshop.cpp 0x550020 调用）。
// ============================================================
// ------------------------------------------------------------
// 0x54D6E0 sub_54D6E0 —— 工具窗页绘制（106 行：43C250/43C330 + 69C440/69C420/69C3E0/69C4C0 + 56CFE0）
// ------------------------------------------------------------
char /*thiscall*/ sub_54D6E0(int this)
{
  uint8_t *v2; // eax
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  uint8_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint8_t *v10; // edi
  uint8_t *v11; // eax
  uint8_t *v12; // eax
  uint8_t *v13; // eax
  uint32_t *v14; // eax
  uint32_t *v15; // eax
  uint32_t *v16; // eax
  uint32_t *v17; // eax

  *(uint32_t *)(this + 32) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 36);
  v2 = operator new(0x6Cu);
  if ( v2 != nullptr )
    v3 = sub_43C250(v2, *(uint32_t *)(this + 32), 0);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 4) = v3;
  *((uint32_t *)v3 + 7) = *((uint32_t *)v3 + 7);
  *((uint32_t *)v3 + 8) = 250;
  *(uint32_t *)(*(uint32_t *)(this + 4) + 68) = this;
  v4 = operator new(0x6Cu);
  if ( v4 != nullptr )
    v5 = sub_43C330(v4, 130, 2048);
  else
    v5 = nullptr;
  *(uint32_t *)(this + 124) = v5;
  sub_69C440(-4265479);
  sub_69C420(2);
  sub_69C3E0(5);
  sub_69C4C0(dword_99FCCC);
  sub_69A5F0(*(uint32_t **)(this + 124), 110, 31);
  sub_69A840(*(uint32_t *)(this + 124));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 4, 4, 5, 4, 0, 0);
  else
    v7 = nullptr;
  *(uint32_t *)(this + 128) = v7;
  v8 = operator new(0x84u);
  if ( v8 != nullptr )
    v9 = sub_43C410(v8, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 6, 6, 7, 6, 0, 0);
  else
    v9 = nullptr;
  *(uint32_t *)(this + 132) = v9;
  v10 = operator new(0x88u);
  if ( v10 != nullptr )
  {
    sub_43C4D0(v10, *(uint32_t *)(this + 32), 29, 27);
    *(uint32_t *)v10 = &vftbl_nengine__CNVSlider;
    v11 = v10;
  }
  else
  {
    v11 = nullptr;
  }
  *(uint32_t *)(this + 136) = v11;
  v12 = operator new(0x74u);
  if ( v12 != nullptr )
    v13 = sub_43C630(v12, *(uint32_t *)(this + 128), *(uint32_t *)(this + 132), *(uint32_t *)(this + 136));
  else
    v13 = nullptr;
  *(uint32_t *)(this + 140) = v13;
  sub_69A5F0(v13, 249, 27);
  sub_69A840(*(uint32_t *)(this + 140));
  v14 = operator new(0x84u);
  if ( v14 != nullptr )
    v15 = sub_43C410(v14, *(uint32_t *)(this + 32), 40, 41, 42, 40, 0, 0);
  else
    v15 = nullptr;
  *(uint32_t *)(this + 148) = v15;
  sub_69A5F0(v15, 116, 215);
  *(uint8_t *)(*(uint32_t *)(this + 148) + 16) = 0;
  sub_69A840(*(uint32_t *)(this + 148));
  v16 = operator new(0x84u);
  if ( v16 != nullptr )
    v17 = sub_43C410(v16, *(uint32_t *)(this + 32), 37, 38, 39, 37, 0, 0);
  else
    v17 = nullptr;
  *(uint32_t *)(this + 144) = v17;
  sub_69A5F0(v17, 116, 215);
  *(uint8_t *)(*(uint32_t *)(this + 144) + 16) = 0;
  sub_69A840(*(uint32_t *)(this + 144));
  sub_69A5F0(*(uint32_t **)(this + 4), 29, 193);
  *(uint8_t *)(*(uint32_t *)(this + 148) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 144) + 16) = 1;
  *(uint32_t *)(this + 24) = sub_56CFE0(17);
  *(uint32_t *)(this + 16) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  return sub_698F90(this + 36, 0, 0);
}



// ------------------------------------------------------------
// 0x54DA10 sub_54DA10 —— PVP 结算辅助（22 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_54DA10(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 17);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 32);
  *(this + 17) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 32) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x54DA50 sub_54DA50 —— PVP 结算背景绘制（206 行：48F620 + 418DD0/4049F0/43B560）
// ------------------------------------------------------------
char /*thiscall*/ sub_54DA50(int this, int a2, char a3)
{
  void *v4; // edi
  uint8_t v5; // bl
  int v6; // eax
  unsigned int v7; // ebx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  uint8_t v11; // bl
  int v12; // edi
  int v13; // eax
  int v14; // ebx
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // eax
  void *v20; // [esp+Ch] [ebp-4h]

  if ( a3 == 1 )
  {
    v4 = (void *)sub_699000(this + 12);
    v20 = v4;
  }
  else
  {
    v20 = &unk_989680;
    v4 = &unk_989680;
  }
  if ( sub_48F620((uint32_t *)dword_99FEC0) )
  {
    v5 = a2;
    if ( a2 >= 90 )
      v5 = 90;
    v6 = sub_418DD0(*(uint32_t **)(this + 72), 0x56u);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
        v6,
        0,
        0,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (v5 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v7 = 2 * (*(uint32_t *)(this + 132) != 0) + 80;
    v8 = (uint64_t)sub_4049F0(-239.0, 127.0, (int)v4, 300, 1);
    v9 = sub_418DD0(*(uint32_t **)(this + 72), v7);
    if ( v9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 128))(
        v9,
        v8,
        179,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)a2 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    if ( v8 == 127 && a3 != 0 && (v10 = sub_418DD0(*(uint32_t **)(this + 72), v7 + 1)) != 0 )
    {
      v11 = a2;
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 128))(
        v10,
        127,
        179,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)a2 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    }
    else
    {
      v11 = a2;
    }
    v12 = (uint64_t)sub_4049F0(640.0, 170.0, (int)v20, 300, 1);
    v13 = sub_418DD0(*(uint32_t **)(this + 72), 0x4Eu);
    if ( v13 != 0 )
      LOBYTE(v13) = (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
                      v13,
                      v12,
                      215,
                      dword_79C0B0,
                      1065353216,
                      1065353216,
                      0,
                      (v11 << 24) | 0xFFFFFF,
                      1333788672,
                      1333788672);
    if ( v12 == 170 )
    {
      LOBYTE(v13) = a3;
      if ( a3 != 0 )
      {
        v13 = sub_418DD0(*(uint32_t **)(this + 72), 0x4Fu);
        if ( v13 != 0 )
          LOBYTE(v13) = (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
                          v13,
                          170,
                          215,
                          dword_79C0B0,
                          1065353216,
                          1065353216,
                          0,
                          (v11 << 24) | 0xFFFFFF,
                          1333788672,
                          1333788672);
      }
    }
  }
  else
  {
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);
    if ( v13 != 2 )
    {
      v14 = a2;
      if ( a2 >= 90 )
        LOBYTE(a2) = 90;
      v15 = sub_418DD0(*(uint32_t **)(this + 72), 0x56u);
      if ( v15 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v15 + 128))(
          v15,
          0,
          0,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)a2 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      if ( *(uint32_t *)(this + 132) == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) )
      {
        v16 = (uint64_t)sub_4049F0(640.0, 167.0, (int)v4, 300, 1);
        v13 = sub_418DD0(*(uint32_t **)(this + 72), 0x4Eu);
        if ( v13 != 0 )
          LOBYTE(v13) = (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
                          v13,
                          v16,
                          197,
                          dword_79C0B0,
                          1065353216,
                          1065353216,
                          0,
                          ((uint8_t)v14 << 24) | 0xFFFFFF,
                          1333788672,
                          1333788672);
        if ( v16 == 167 )
        {
          LOBYTE(v13) = a3;
          if ( a3 != 0 )
          {
            v17 = sub_418DD0(*(uint32_t **)(this + 72), 0x4Fu);
            LOBYTE(v13) = sub_43B560(
                            167,
                            197,
                            v17,
                            1065353216,
                            1065353216,
                            0,
                            ((uint8_t)v14 << 24) | 0xFFFFFF,
                            1333788672,
                            1333788672);
          }
        }
      }
      else
      {
        v13 = sub_418DD0(*(uint32_t **)(this + 72), 0x54u);
        if ( v13 != 0 )
          LOBYTE(v13) = (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
                          v13,
                          219,
                          193,
                          dword_79C0B0,
                          1065353216,
                          1065353216,
                          0,
                          ((uint8_t)v14 << 24) | 0xFFFFFF,
                          1333788672,
                          1333788672);
        if ( v14 == 255 )
        {
          LOBYTE(v13) = a3;
          if ( a3 != 0 )
          {
            v18 = sub_418DD0(*(uint32_t **)(this + 72), 0x55u);
            LOBYTE(v13) = sub_43B560(219, 193, v18, 1065353216, 1065353216, 0, -1, 1333788672, 1333788672);
          }
        }
      }
    }
  }
  return v13;
}


// ------------------------------------------------------------
// 0x54DE80 sub_54DE80 —— 结算辅助（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ sub_54DE80(int *this, int a2, uint8_t a3)
{
  int v4; // eax
  int v5; // eax
  int result; // eax

  v4 = *(this + 35);
  if ( v4 >= 30 )
  {
    v5 = sub_418DD0(v4 + 16);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v5 + 128))(
        v5,
        0,
        0,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (a3 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
  }
  result = sub_418DD0(*(this + 35));
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
             result,
             0,
             0,
             dword_79C0B0,
             1065353216,
             1065353216,
             0,
             (a3 << 24) | 0xFFFFFF,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x54DF30 sub_54DF30 —— 13 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_54DF30(uint32_t *this, int a2, int a3, int a4)
{
  *(this + 43) = a2;
  *(this + 44) = a3;
  *(this + 45) = a4;
  return a4;
}



// ------------------------------------------------------------
// 0x54DF60 sub_54DF60 —— 结算文字（699000 + 4049C0，107 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_54DF60(int this)
{
  int v2; // edi
  int v3; // ebx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  double v7; // st7
  double v8; // st6
  int v9; // eax
  int v10; // eax
  int64_t v11; // rax
  int v12; // eax
  double v13; // st7
  int v14; // ecx
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int v19; // [esp-8h] [ebp-28h]
  int v20; // [esp-8h] [ebp-28h]
  int v21; // [esp-8h] [ebp-28h]
  float v22; // [esp+10h] [ebp-10h]
  float v23; // [esp+14h] [ebp-Ch]
  float v24; // [esp+18h] [ebp-8h]
  float v25; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04) + 52);
  v3 = *(uint32_t *)(this + 172);
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);
  v5 = *(uint32_t *)dword_8F7C04;
  v23 = *(float *)(v4 + 56);
  v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(v5 + 1032))(dword_8F7C04) + 60);
  v7 = (double)(LODWORD(v23) - v6);
  v8 = (double)(v2 - v6);
  LODWORD(v25) = v3 - *(uint32_t *)(this + 176);
  v9 = *(uint32_t *)(this + 8) - 10;
  v22 = (float)SLODWORD(v25);
  v25 = 1.0 / v7;
  v23 = 1.0 / v7 * v8;
  v24 = v25 * v22;
  if ( v9 == 0 )
    return (uint64_t)(*(&v23 + (*(uint32_t *)(this + 136) != 0)) * 129.0);
  v10 = v9 - 1;
  if ( v10 == 0 )
  {
    v12 = *(uint32_t *)(this + 136);
    v13 = 0.0;
    if ( v12 == -1 )
    {
      v16 = this + 12;
      if ( *(uint8_t *)(this + 184) != 0 )
      {
        v21 = sub_699000(v16);
        v13 = sub_4049C0(1.0, v24, v21, 300);
      }
      else
      {
        v17 = sub_699000(v16);
        v13 = sub_4049C0(v23, 0.0, v17, 300);
        if ( v13 <= 0.0 )
        {
          *(uint8_t *)(this + 184) = 1;
          return (uint64_t)(v13 * 129.0);
        }
      }
    }
    else if ( v12 != 0 )
    {
      if ( v12 == 1 )
      {
        v14 = this + 12;
        if ( *(uint8_t *)(this + 184) != 0 )
        {
          v19 = sub_699000(v14);
          v13 = sub_4049C0(0.0, v23, v19, 300);
        }
        else
        {
          v15 = sub_699000(v14);
          v13 = sub_4049C0(v24, 1.0, v15, 300);
          if ( v13 >= 1.0 )
          {
            *(uint8_t *)(this + 184) = 1;
            return (uint64_t)(v13 * 129.0);
          }
        }
      }
    }
    else
    {
      v20 = sub_699000(this + 12);
      v13 = sub_4049C0(v23, v23, v20, 600);
    }
    return (uint64_t)(v13 * 129.0);
  }
  if ( v10 == 1 )
    return (uint64_t)(v23 * 129.0);
  else
    LODWORD(v11) = 0;
  return v11;
}



// ------------------------------------------------------------
// 0x54E160 sub_54E160 —— 17 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_54E160(uint32_t *this, int a2)
{
  int v3; // esi

  v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8));
  (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 40))(
    *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8),
    a2);
  *(this + 37) = a2 - v3;
  return off_77F3FC(aPvp_4, v3, a2);
}



// ------------------------------------------------------------
// 0x54E1B0 sub_54E1B0 —— 结算辅助 2（26 行）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_54E1B0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax
  uint32_t *v5; // edi
  int v6; // esi

  v3 = a1;
  for ( result = a3; v3 != a2; v5[3] = v6 )
  {
    v5 = result;
    *result = *v3;
    result[1] = v3[1];
    result[2] = v3[2];
    v6 = v3[3];
    v3 += 4;
    result += 4;
  }
  return result;
}



// ------------------------------------------------------------
// 0x54E1F0 sub_54E1F0 —— 结算 UI 构建（219 行：48F5A0/48F690 + 42A410/42A430 + 54DF60/488670/54DE80）
// ------------------------------------------------------------
int /*thiscall*/ sub_54E1F0(int *this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  char *v7; // eax
  int v8; // esi
  int v9; // eax
  int v10; // eax
  char *v11; // eax
  int v12; // eax
  int v13; // ebx
  int v14; // ebx
  int v15; // eax
  uint32_t *v16; // ecx
  int v17; // eax
  int v18; // eax
  int result; // eax
  int v20; // eax
  int v21; // [esp-4h] [ebp-88h]
  int v22; // [esp-4h] [ebp-88h]
  uint8_t v23; // [esp+Ch] [ebp-78h]
  int v24; // [esp+Ch] [ebp-78h]
  char Buffer[112]; // [esp+10h] [ebp-74h] BYREF
  int v26; // [esp+80h] [ebp-4h]

  v26 = dword_796E50;
  v23 = a2;
  if ( a2 >= 150 )
    v23 = -106;
  v3 = sub_418DD0(35);
  if ( v3 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v3 + 128))(
      v3,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (v23 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  v4 = sub_418DD0(36);
  if ( v4 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v4 + 128))(
      v4,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)a2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  v5 = sub_418DD0(39);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v5 + 128))(
      v5,
      236,
      223,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)a2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  v6 = sub_418DD0(38);
  if ( v6 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
      v6,
      235,
      222,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)a2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 19);
  v21 = *(this + 37);
  v7 = sub_422E70(458);
  sprintf(Buffer, v7, v21);
  v8 = ((uint8_t)a2 << 24) | 0xFFFFFF;
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 281, 232, v8, Buffer);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  v9 = sub_418DD0(37);
  if ( v9 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 128))(
      v9,
      235,
      268,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      v8,
      1333788672,
      1333788672);
  v10 = sub_418DD0(38);
  if ( v10 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 128))(
      v10,
      235,
      268,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      v8,
      1333788672,
      1333788672);
  (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 19);
  v22 = *(this + 36);
  v11 = sub_422E70(459);
  sprintf(Buffer, v11, v22);
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 282, 280, v8, Buffer);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  v12 = sub_48F5A0();
  v13 = sub_48F690(v12);
  if ( v13 != 0 && dword_8F7C04 != 0 )
  {
    v24 = sub_42A410(v13);
    v14 = sub_42A430(v13);
    if ( v24 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v24 + 128))(
        v24,
        228,
        305,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v8,
        1333788672,
        1333788672);
    if ( v14 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
        v14,
        228,
        305,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v8,
        1333788672,
        1333788672);
    v15 = sub_54DF60(this);
    v16 = (uint32_t *)dword_79C0B0;
    *(uint32_t *)(dword_79C0B0 + 48) = 0;
    v16[13] = 0;
    v16[14] = v15 + 280;
    v16[15] = 480;
    v17 = sub_418DD0(91);
    if ( v17 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v17 + 128))(
        v17,
        281,
        307,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v8,
        1333788672,
        1333788672);
    sub_488670(dword_79C0B0);
  }
  if ( *(this + 33) == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) )
    v18 = sub_418DD0(45);
  else
    v18 = sub_418DD0(44);
  if ( v18 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v18 + 128))(
      v18,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      v8,
      1333788672,
      1333788672);
  result = *(this + 34);
  if ( result == -1 )
  {
    v20 = sub_418DD0(42);
  }
  else
  {
    if ( result != 1 )
      return result;
    v20 = sub_418DD0(43);
  }
  if ( v20 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v20 + 128))(
      v20,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      v8,
      1333788672,
      1333788672);
  return sub_54DE80(*(this + 35), a2);
}


// ------------------------------------------------------------
// 0x54E660 sub_54E660 —— 结算转发（54E1B0）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_54E660(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_54E1B0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x54E680 sub_54E680 —— 结算转发 2（602460）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_54E680(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_602460(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x54E6A0 sub_54E6A0 —— 结算徽章绘制（418DD0 + 491530/491630，50 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_54E6A0(void *this, int a2)
{
  uint8_t v4; // bl
  int v5; // eax
  uint8_t v6; // bl
  int v7; // eax
  float v9; // [esp+14h] [ebp+8h]

  v4 = a2;
  if ( a2 >= 220 )
    v4 = -36;
  v5 = sub_418DD0(33);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v5 + 128))(
      v5,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (v4 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  v9 = (double)sub_699000((int)this + 40) * 0.000033333334;
  sub_491530(2, 0);
  v6 = a2;
  if ( a2 >= 120 )
    v6 = 120;
  v7 = sub_418DD0(1);
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, float, int, int, int))(*(uint32_t *)v7 + 128))(
      v7,
      111,
      31,
      dword_79C0B0,
      1065353216,
      1065353216,
      COERCE_FLOAT(LODWORD(v9)),
      (v6 << 24) | 0xFFFFFF,
      1129447424,
      1129447424);
  return sub_491630(2);
}



// ------------------------------------------------------------
// 0x54E7B0 sub_54E7B0 —— PVP 结算主绘制（451 行：491530/491630 + 429830/48F620 + 42B340/42A410/42A430 + 69A110）
// ------------------------------------------------------------
int /*thiscall*/ sub_54E7B0(uint32_t *this, int a2)
{
  int v2; // eax
  int v3; // edi
  int v4; // esi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // eax
  int v11; // ecx
  int result; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int v17; // esi
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // ecx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // esi
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // ecx
  int v35; // eax
  int v36; // edx
  int v37; // esi
  int v38; // edi
  bool v39; // cc
  int v40; // [esp+10h] [ebp-2Ch]
  int i; // [esp+14h] [ebp-28h]
  uint8_t v42; // [esp+14h] [ebp-28h]
  uint8_t v43; // [esp+14h] [ebp-28h]
  int v44; // [esp+14h] [ebp-28h]
  int v45; // [esp+18h] [ebp-24h]
  int v46; // [esp+1Ch] [ebp-20h]
  int v47; // [esp+20h] [ebp-1Ch]
  int v48; // [esp+24h] [ebp-18h]
  int v49; // [esp+28h] [ebp-14h]
  int v50; // [esp+2Ch] [ebp-10h]
  int v51; // [esp+30h] [ebp-Ch]
  int v52; // [esp+34h] [ebp-8h]
  uint8_t v54; // [esp+44h] [ebp+8h]
  uint8_t v55; // [esp+44h] [ebp+8h]
  int v56; // [esp+44h] [ebp+8h]

  v2 = *(this + 39);
  if ( v2 != 0 )
    v3 = (*(this + 40) - v2) >> 4;
  else
    v3 = 0;
  v4 = dword_7249C4[v3];
  v40 = v3;
  v5 = sub_418DD0(12);
  v6 = a2;
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v5 + 128))(
      v5,
      269,
      v4 - 45,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)a2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  if ( a2 >= 150 )
    LOBYTE(a2) = -106;
  v7 = sub_418DD0(73);
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v7 + 128))(
      v7,
      127,
      v4,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)a2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  v8 = 0;
  v9 = v4 + 70;
  for ( i = 0; i < v3 - 1; ++i )
  {
    if ( v8 == v3 - 2 )
    {
      v54 = v6;
      if ( v6 >= 150 )
        v54 = -106;
      v10 = sub_418DD0(75);
      if ( v10 == 0 )
        goto LABEL_21;
      v11 = v54;
    }
    else
    {
      v55 = v6;
      if ( v6 >= 150 )
        v55 = -106;
      v10 = sub_418DD0(74);
      if ( v10 == 0 )
        goto LABEL_21;
      v11 = v55;
    }
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 128))(
      v10,
      127,
      v9,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (v11 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
LABEL_21:
    v8 = i + 1;
    v9 += 43;
  }
  result = dword_7249C4[v3];
  v52 = result;
  v45 = 0;
  if ( v3 > 0 )
  {
    v46 = result + 13;
    v47 = result + 14;
    v56 = result + 26;
    v48 = result + 7;
    v50 = result + 10;
    v49 = result + 3;
    v51 = result + 21;
    while ( v45 == 0 )
    {
      sub_491530(2, 0);
      v42 = v6;
      if ( v6 >= 70 )
        v42 = 70;
      v13 = sub_418DD0(77);
      if ( v13 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
          v13,
          141,
          v47,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          (v42 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_491630(2);
      v14 = sub_418DD0(51);
      if ( v14 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
          v14,
          447,
          v56,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v6 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v15 = sub_429830(*(uint16_t *)*(this + 39));
      v16 = v15;
      if ( v15 != 0 )
        v17 = *(uint32_t *)(v15 + 196);
      else
        v17 = 0;
      if ( v15 != 0 && v17 != 0 )
      {
        if ( (uint8_t)sub_48F620(dword_99FEC0) != 0 )
        {
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 376))(v17) != 0 )
            v18 = sub_418DD0(88);
          else
            v18 = sub_418DD0(87);
        }
        else
        {
          v18 = sub_418DD0(59);
        }
        if ( v18 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v18 + 128))(
            v18,
            206,
            v51,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)v6 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        v19 = sub_42B340(v16);
        if ( v19 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)v19 + 384))(
            v19,
            216,
            v52 + 32,
            24,
            24,
            1065353216);
          v20 = sub_42A410(v16);
          if ( v20 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v20 + 128))(
              v20,
              254,
              v56,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              ((uint8_t)v6 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          v21 = sub_42A430(v16);
          if ( v21 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v21 + 128))(
              v21,
              254,
              v56,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              ((uint8_t)v6 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 19);
          if ( *(uint32_t *)(v16 + 40) < 0x10u )
            v22 = v16 + 20;
          else
            v22 = *(uint32_t *)(v16 + 20);
          (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            256,
            v52 + 45,
            ((uint8_t)v6 << 24) | 0xFFFFFF,
            v22);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        }
      }
      sub_69A110(405, v52 + 31, *(uint32_t *)(*(this + 39) + 4), v6);
      v23 = sub_418DD0(71);
      if ( v23 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v23 + 128))(
          v23,
          405,
          v52 + 30,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v6 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v24 = 70;
      v52 += 70;
LABEL_91:
      v50 += v24;
      v49 += v24;
      v51 += v24;
      v36 = v24 + v47;
      v37 = v24 + v56;
      v38 = v24 + v48;
      v46 += v24;
      result = v45 + 1;
      v39 = v45 + 1 < v40;
      v48 = v38;
      v56 = v37;
      v47 = v36;
      ++v45;
      if ( !v39 )
        return result;
    }
    sub_491530(2, 0);
    v43 = v6;
    if ( v6 >= 200 )
      v43 = -56;
    v25 = sub_418DD0(76);
    if ( v25 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v25 + 128))(
        v25,
        127,
        v52,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (v43 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491630(2);
    v26 = sub_418DD0(v45 + 51);
    if ( v26 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v26 + 128))(
        v26,
        447,
        v52 + 12,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)v6 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v27 = sub_429830(*(uint16_t *)(16 * v45 + *(this + 39)));
    v44 = v27;
    if ( v27 != 0 )
      v28 = *(uint32_t *)(v27 + 196);
    else
      v28 = 0;
    if ( v27 == 0 || v28 == 0 )
    {
LABEL_88:
      sub_69A110(405, v47, *(uint32_t *)(16 * v45 + *(this + 39) + 4), v6);
      v35 = sub_418DD0(71);
      if ( v35 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v35 + 128))(
          v35,
          405,
          v46,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v6 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v24 = 43;
      v52 += 43;
      goto LABEL_91;
    }
    if ( (uint8_t)sub_48F620(dword_99FEC0) != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v28 + 376))(v28) == *(this + 33) )
      {
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v28 + 376))(v28) != 0 )
          v29 = sub_418DD0(93);
        else
          v29 = sub_418DD0(92);
        if ( v29 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v29 + 128))(
            v29,
            206,
            v49,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)v6 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
LABEL_79:
        v31 = sub_42B340(v44);
        if ( v31 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)v31 + 384))(
            v31,
            216,
            v46,
            24,
            24,
            1065353216);
          v32 = sub_42A410(v44);
          if ( v32 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v32 + 128))(
              v32,
              254,
              v48,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              ((uint8_t)v6 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          v33 = sub_42A430(v44);
          if ( v33 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v33 + 128))(
              v33,
              254,
              v48,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              ((uint8_t)v6 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 19);
          if ( *(uint32_t *)(v44 + 40) < 0x10u )
            v34 = v44 + 20;
          else
            v34 = *(uint32_t *)(v44 + 20);
          (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            256,
            v56,
            ((uint8_t)v6 << 24) | 0xFFFFFF,
            v34);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        }
        goto LABEL_88;
      }
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v28 + 376))(v28) != 0 )
        v30 = sub_418DD0(90);
      else
        v30 = sub_418DD0(89);
    }
    else
    {
      v30 = sub_418DD0(60);
    }
    if ( v30 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v30 + 128))(
        v30,
        213,
        v50,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)v6 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    goto LABEL_79;
  }
  return result;
}


// ------------------------------------------------------------
// 0x54F050 sub_54F050 —— 结算数字绘制（158 行：4049F0/4049C0 + 491530/418DD0/491630）
// ------------------------------------------------------------
int /*userpurge*/ sub_54F050@<eax>(uint32_t *a1@<ecx>, double a2@<st0>, uint8_t a3)
{
  uint32_t *v3; // ebx
  int v4; // ecx
  int v5; // edi
  unsigned int v6; // esi
  int result; // eax
  int v8; // edx
  int v9; // ecx
  float v10; // edi
  int v11; // edi
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  int v20; // edx
  bool v21; // cc
  int v22; // [esp+Ch] [ebp-20h]
  uint32_t *v23; // [esp+10h] [ebp-1Ch]
  int v24; // [esp+14h] [ebp-18h]
  int v25; // [esp+18h] [ebp-14h]
  int v26; // [esp+1Ch] [ebp-10h]
  int v27; // [esp+20h] [ebp-Ch]
  int v28; // [esp+24h] [ebp-8h]
  float v29; // [esp+28h] [ebp-4h]

  v3 = a1;
  v4 = a1[39];
  v23 = v3;
  if ( v4 != 0 )
    v24 = (v3[40] - v4) >> 4;
  else
    v24 = 0;
  v5 = dword_7249C4[v24];
  v6 = sub_699000((int)(v3 + 3));
  sub_4049F0(3.0, 0.94999999, v6, 200, 1);
  result = 0;
  v22 = 0;
  if ( v24 > 0 )
  {
    v8 = v5 - 57;
    v25 = v5 + 5;
    v9 = v5 + 22;
    v28 = v5 - 44;
    v29 = a2;
    v10 = v29;
    v26 = v8;
    v27 = v9;
    do
    {
      if ( result != 0 )
      {
        if ( v3[33] == *(uint32_t *)(16 * result + v3[39] + 12) )
        {
          if ( v6 >= 0xC8 )
          {
            v6 -= 200;
            v16 = (uint64_t)sub_4049C0(87.0, 93.0, v6, 200);
            v17 = (uint64_t)sub_4049C0(255.0, 0.0, v6, 200);
            sub_491530(2, 0);
            v18 = sub_418DD0(v16);
            if ( v18 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v18 + 128))(
                v18,
                98,
                v26,
                dword_79C0B0,
                1065353216,
                1065353216,
                0,
                ((uint8_t)v17 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
            sub_491630(2);
            v10 = 1.0;
            v3 = v23;
          }
          v19 = sub_418DD0(95);
          if ( v19 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, float, float, uint32_t, int, int, int))(*(uint32_t *)v19 + 156))(
              v19,
              156,
              v25,
              dword_79C0B0,
              COERCE_FLOAT(LODWORD(v10)),
              COERCE_FLOAT(LODWORD(v10)),
              0,
              (a3 << 24) | 0xFFFFFF,
              1101529088,
              1100480512);
        }
        v15 = 43;
      }
      else
      {
        if ( v3[33] == *(uint32_t *)(v3[39] + 12) )
        {
          if ( v6 >= 0xC8 )
          {
            v6 -= 200;
            v11 = (uint64_t)sub_4049C0(87.0, 93.0, v6, 200);
            v12 = (uint64_t)sub_4049C0(255.0, 0.0, v6, 200);
            sub_491530(2, 0);
            v13 = sub_418DD0(v11);
            if ( v13 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
                v13,
                98,
                v28,
                dword_79C0B0,
                1065353216,
                1065353216,
                0,
                ((uint8_t)v12 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
            sub_491630(2);
            v10 = 1.0;
            v3 = v23;
          }
          v14 = sub_418DD0(95);
          if ( v14 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, float, float, uint32_t, int, int, int))(*(uint32_t *)v14 + 156))(
              v14,
              156,
              v27,
              dword_79C0B0,
              COERCE_FLOAT(LODWORD(v10)),
              COERCE_FLOAT(LODWORD(v10)),
              0,
              (a3 << 24) | 0xFFFFFF,
              1101529088,
              1100480512);
        }
        v15 = 70;
      }
      v27 += v15;
      v28 += v15;
      v20 = v15 + v26;
      v25 += v15;
      result = v22 + 1;
      v21 = v22 + 1 < v24;
      v26 = v20;
      ++v22;
    }
    while ( v21 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x54F370 sub_54F370 —— 结算文本（418DD0，83 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_54F370(uint32_t *this, uint8_t a2)
{
  int v3; // eax
  int result; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // [esp+4h] [ebp-Ch]
  int v11; // [esp+8h] [ebp-8h]
  int v12; // [esp+Ch] [ebp-4h]

  v3 = *(this + 39);
  if ( v3 != 0 )
    v11 = (*(this + 40) - v3) >> 4;
  else
    v11 = 0;
  result = dword_7249C4[v11];
  v5 = 0;
  v10 = 0;
  if ( v11 > 0 )
  {
    v12 = result + 5;
    v6 = result + 22;
    do
    {
      if ( v5 != 0 )
      {
        if ( *(this + 33) == *(uint32_t *)(16 * v5 + *(this + 39) + 12) )
        {
          v9 = sub_418DD0(95);
          if ( v9 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 128))(
              v9,
              156,
              v12,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              (a2 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
        }
        v6 += 43;
        v8 = v12 + 43;
      }
      else
      {
        if ( *(this + 33) == *(uint32_t *)(*(this + 39) + 12) )
        {
          v7 = sub_418DD0(95);
          if ( v7 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v7 + 128))(
              v7,
              156,
              v6,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              (a2 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
        }
        v6 += 70;
        v8 = v12 + 70;
      }
      v12 = v8;
      result = v11;
      v5 = ++v10;
    }
    while ( v10 < v11 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x54F4C0 sub_54F4C0 —— 结算事件复位（698F90）
// ------------------------------------------------------------
void /*thiscall*/ sub_54F4C0(int this)
{
  int v2; // ecx

  v2 = this + 40;
  *(uint32_t *)(this + 132) = -1;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint8_t *)(v2 + 13) = 0;
  *(uint8_t *)(v2 + 14) = 0;
  sub_698F90(v2, 0, 0);
  if ( *(uint32_t *)(this + 156) != 0 )
    j__free(*(void **)(this + 156));
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint8_t *)(this + 184) = 0;
  *(uint32_t *)(this + 168) = -1;
}



// ------------------------------------------------------------
// 0x54F530 sub_54F530 —— 转发 54F4C0
// ------------------------------------------------------------
void /*thiscall*/ sub_54F530(int this)
{
  *(uint32_t *)(this + 128) = 0;
  sub_54F4C0(this);
}



// ------------------------------------------------------------
// 0x54F540 sub_54F540 —— 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432EE0/65DC70/432EA0）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_54F540(uint32_t *this, int a2)
{
  int v3; // ecx
  uint8_t *result; // eax
  int i; // esi
  int v6; // esi

  v3 = (int)(this + 3);
  *(this + 2) = a2;
  *(uint8_t *)(v3 + 13) = 0;
  *(uint8_t *)(v3 + 14) = 0;
  sub_698F90(v3, 0, 0);
  if ( *(this + 2) != 0 )
  {
    if ( a2 == 1 )
    {
      *(uint8_t *)(*(this + 17) + 16) = 0;
      for ( i = 0; i < 4; ++i )
        result = (uint8_t *)sub_432EE0(i);
    }
    else
    {
      if ( *(uint8_t *)(*(this + 17) + 16) == 0 )
      {
        sub_65DC70(lpCriticalSection);
        sub_432EA0("M_RESULT", -1, 0, 0);
      }
      result = (uint8_t *)*(this + 17);
      result[16] = 1;
      v6 = *(this + 2);
      if ( v6 == 2 )
      {
        return sub_432EA0("RESULT_COME", -1, 0, 0);
      }
      else if ( v6 == 6 )
      {
        return sub_432EA0("MAP_APPEAR", -1, 0, 0);
      }
    }
  }
  else
  {
    sub_54F4C0((int)this);
    result = (uint8_t *)*(this + 17);
    result[16] = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x54F610 sub_54F610 —— PVP 结算窗口入队实现（44CAB0/602460 + 4BF320/453C20/504650/4BF340，121 行）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_54F610(int this, int a2, unsigned int a3, uint32_t *Block)
{
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  unsigned int result; // eax
  int v10; // ecx
  int v11; // ecx
  unsigned int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ebx
  int v16; // ecx
  int v17; // eax
  unsigned int v18; // edi
  char *v19; // eax
  int v20; // edi
  char *v21; // edi
  int v22; // [esp-18h] [ebp-44h]
  int v23; // [esp-Ch] [ebp-38h]
  unsigned int v24; // [esp-8h] [ebp-34h]
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
  v7 = *(uint32_t *)(this + 4);
  v26[4] = &v25;
  v26[2] = v6;
  if ( v7 != 0 )
    result = (*(uint32_t *)(this + 12) - v7) >> 4;
  else
    result = 0;
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v7) >> 4;
    else
      v10 = 0;
    if ( 0xFFFFFFF - v10 < a3 )
      sub_44CAB0(this);
    if ( v7 != 0 )
      v11 = (*(uint32_t *)(this + 8) - v7) >> 4;
    else
      v11 = 0;
    if ( result >= a3 + v11 )
    {
      v19 = *(char **)(this + 8);
      Blockb = v19;
      if ( (int)&v19[-a2] >> 4 >= a3 )
      {
        v21 = &v19[-16 * a3];
        *(uint32_t *)(this + 8) = sub_602460(v21, v19, v19);
        sub_4BF320(a2, v21, Blockb);
        return sub_453C20(a2, a2 + 16 * a3, v26);
      }
      else
      {
        sub_602460(a2, v19, a2 + 16 * a3);
        v24 = a3 - ((*(uint32_t *)(this + 8) - a2) >> 4);
        v23 = *(uint32_t *)(this + 8);
        v27 = 2;
        sub_504650(v23, v24, v26);
        v20 = 16 * a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v20;
        return sub_453C20(a2, v20 - 16 * a3, v26);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (result >> 1) >= result )
        v12 = (result >> 1) + result;
      else
        v12 = 0;
      if ( v7 != 0 )
        v13 = (*(uint32_t *)(this + 8) - v7) >> 4;
      else
        v13 = 0;
      if ( v12 < a3 + v13 )
      {
        if ( v7 != 0 )
          v14 = (*(uint32_t *)(this + 8) - v7) >> 4;
        else
          v14 = 0;
        v12 = a3 + v14;
      }
      v28 = 16 * v12;
      Blocka = (char *)operator new(16 * v12);
      v22 = *(uint32_t *)(this + 4);
      v27 = 0;
      v15 = sub_602460(v22, a2, Blocka);
      sub_4BF340(v15, a3, v26);
      sub_602460(a2, *(uint32_t *)(this + 8), 16 * a3 + v15);
      v16 = *(uint32_t *)(this + 4);
      if ( v16 != 0 )
        v17 = (*(uint32_t *)(this + 8) - v16) >> 4;
      else
        v17 = 0;
      v18 = v17 + a3;
      if ( v16 != 0 )
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
// 0x54F870 sub_54F870 —— 结算触发（426BD0/423B30 + 54F540）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_54F870(int this, void *Block)
{
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  uint8_t *v5; // eax
  uint8_t *v6; // eax

  *(uint32_t *)(this + 4) = Block;
  *(uint32_t *)(this + 72) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 132);
  v3 = operator new(0x68u);
  if ( v3 != nullptr )
    v4 = sub_426BD0(v3);
  else
    v4 = nullptr;
  *(uint32_t *)(this + 68) = v4;
  *((uint32_t *)v4 + 7) = 640;
  *((uint32_t *)v4 + 8) = 480;
  *(uint32_t *)(*(uint32_t *)(this + 68) + 68) = this;
  *(uint8_t *)(this + 76) = 0;
  *(uint8_t *)(this + 77) = 0;
  *(uint8_t *)(this + 78) = 0;
  *(uint8_t *)(this + 79) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 6;
  *(uint32_t *)(this + 96) = 12;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 1600;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 124) = dword_99FCCC;
  *(uint32_t *)(this + 104) = 180;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 80) = -16777216;
  v5 = operator new(0x2Cu);
  if ( v5 != nullptr )
    v6 = sub_423B30(v5, dword_79C0B0, *(uint32_t *)(this + 72), 60, 7);
  else
    v6 = nullptr;
  *(uint32_t *)(this + 128) = v6;
  *((uint32_t *)v6 + 10) = -3;
  *(uint32_t *)(*(uint32_t *)(this + 128) + 36) = 2;
  *(uint8_t *)(*(uint32_t *)(this + 128) + 24) = 0;
  return sub_54F540((uint32_t *)this, 0);
}



// ------------------------------------------------------------
// 0x54F9B0 sub_54F9B0 —— 结算触发 2（699000 + 54F540）
// ------------------------------------------------------------
int /*thiscall*/ sub_54F9B0(int *this)
{
  int result; // eax

  result = *(this + 2);
  if ( result != 0 && --result == 0 )
  {
    result = sub_699000((int)(this + 3));
    if ( result >= 2000 )
      return (int)sub_54F540(this, *(this + 2) + 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x54F9E0 CNRDPVPResult__vmt0 —— CNRDPVPResult__vmt0 构造（160 行：54DA50 背景 + 54F540 事件 + 54E6A0/54E7B0/54F050/54F370/54E1F0 结算件；标签 VICTORY_UP_LOOP/DEFEAT_DOWN_LOOP/RANK_UP/RESULT_CHARACTER）
// ------------------------------------------------------------
int /*userpurge*/ sub_54F9E0@<eax>(uint32_t *a1@<ecx>, double a2@<st0>, int a3)
{
  int result; // eax
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  uint64_t v8; // rax
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // edi
  int v16; // eax
  double v17; // st7
  int v18; // eax
  double v19; // st7

  result = a3;
  if ( a3 == a1[17] )
  {
    if ( a1[2] == 2 )
    {
      v5 = sub_699000((int)(a1 + 3));
      a2 = sub_4049C0(0.0, 255.0, v5, 180);
      sub_54DA50((uint64_t)a2, 1);
      if ( a1[2] == 2 && sub_699000((int)(a1 + 3)) >= 350 )
        return sub_54F540(a1[2] + 1);
    }
    if ( a1[2] == 3 )
    {
      sub_54DA50(255, 0);
      if ( a1[2] == 3 && sub_699000((int)(a1 + 3)) >= 1500 )
        return sub_54F540(a1[2] + 1);
    }
    if ( a1[2] == 4 )
    {
      v6 = sub_699000((int)(a1 + 3));
      a2 = sub_4049C0(255.0, 0.0, v6, 200);
      sub_54DA50((uint64_t)a2, 0);
      if ( a1[2] == 4 && sub_699000((int)(a1 + 3)) >= 300 )
        return sub_54F540(a1[2] + 1);
    }
    v7 = a1[2];
    if ( v7 >= 5 )
    {
      LODWORD(v8) = 255;
      if ( v7 == 5 )
      {
        v9 = sub_699000((int)(a1 + 3));
        a2 = sub_4049C0(0.0, 255.0, v9, 500);
        v8 = (uint64_t)a2;
      }
      else if ( v7 == 12 )
      {
        v10 = sub_699000((int)(a1 + 3));
        LODWORD(v8) = sub_423A80(255, 0, v10, 250);
      }
      sub_54E6A0(a1, v8);
      if ( a1[2] == 5 && sub_699000((int)(a1 + 3)) >= 500 )
      {
        v11 = a1[39];
        if ( v11 != 0 && (a1[40] - v11) >> 4 != 0 )
          return sub_54F540(a1[2] + 1);
        return sub_54F540(0);
      }
    }
    if ( a1[2] == 6 )
    {
      v12 = sub_699000((int)(a1 + 3));
      a2 = sub_4049C0(0.0, 255.0, v12, 500);
      sub_54E7B0(a1, (uint64_t)a2);
      if ( a1[2] == 6 && sub_699000((int)(a1 + 3)) >= 800 )
        return sub_54F540(a1[2] + 1);
    }
    if ( a1[2] == 7 )
    {
      sub_54E7B0(a1, 255);
      sub_54F050(a1, a2, 0xFFu);
      if ( a1[2] == 7 && sub_699000((int)(a1 + 3)) >= 400 )
      {
        sub_432EA0("RESULT_CHARACTER", -1, 0, 0);
        return sub_54F540(a1[2] + 1);
      }
    }
    if ( a1[2] == 8 )
    {
      sub_54E7B0(a1, 255);
      sub_54F370(255);
      v13 = 4000;
      if ( dword_8F7C04 != 0 && *(uint8_t *)(dword_8F7C04 + 8052) != 0 )
        v13 = 10000;
      if ( a1[2] == 8 && sub_699000((int)(a1 + 3)) >= v13 )
      {
        if ( dword_8F7C04 == 0 || *(uint8_t *)(dword_8F7C04 + 8052) == 0 )
          return sub_54F540(a1[2] + 1);
        return sub_54F540(0);
      }
    }
    if ( a1[2] == 9 )
    {
      v14 = sub_699000((int)(a1 + 3));
      v15 = (uint64_t)sub_4049C0(255.0, 0.0, v14, 500);
      sub_54E7B0(a1, v15);
      sub_54F370(v15);
      if ( a1[2] == 9 && sub_699000((int)(a1 + 3)) >= 500 )
        return sub_54F540(a1[2] + 1);
    }
    if ( a1[2] == 10
      && (v16 = sub_699000((int)(a1 + 3)),
          v17 = sub_4049C0(0.0, 255.0, v16, 500),
          sub_54E1F0((uint64_t)v17),
          a1[2] == 10)
      && sub_699000((int)(a1 + 3)) >= 500 )
    {
      sub_54F540(a1[2] + 1);
      result = a1[36];
      if ( result <= 0 )
      {
        if ( result < 0 )
          return (int)sub_432EA0("DEFEAT_DOWN_LOOP", -1, 0, 0);
      }
      else
      {
        if ( a1[34] != 0 )
          sub_432EA0("RANK_UP", -1, 0, 0);
        return (int)sub_432EA0("VICTORY_UP_LOOP", -1, 0, 0);
      }
    }
    else
    {
      if ( a1[2] == 11 )
      {
        sub_54E1F0(255);
        if ( a1[2] == 11 && sub_699000((int)(a1 + 3)) >= 4000 )
          return sub_54F540(a1[2] + 1);
      }
      result = a1[2];
      if ( result >= 12 )
      {
        v18 = sub_699000((int)(a1 + 3));
        v19 = sub_4049C0(255.0, 0.0, v18, 500);
        result = sub_54E1F0((uint64_t)v19);
        if ( a1[2] == 12 )
        {
          result = sub_699000((int)(a1 + 3));
          if ( result >= 500 )
            return sub_54F540(0);
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x54FE50 sub_54FE50 —— 结算收尾（54E1B0 + 44CF50 + 54E680/54E660/602460）
// ------------------------------------------------------------
int /*thiscall*/ sub_54FE50(int this, int a2)
{
  uint32_t *v3; // ebx
  unsigned int v4; // eax
  uint32_t *v6; // ecx
  unsigned int v7; // edx
  int v8; // eax
  int v9; // edi
  unsigned int v10; // edx
  int v11; // eax
  uint32_t *v12; // ebx
  int v13; // ecx
  unsigned int v14; // eax

  if ( this == a2 )
    return this;
  v3 = *(uint32_t **)(a2 + 4);
  if ( v3 == nullptr || (v4 = (*(uint32_t *)(a2 + 8) - (int)v3) >> 4) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  v6 = *(uint32_t **)(this + 4);
  if ( v6 != nullptr )
    v7 = (*(uint32_t *)(this + 8) - (int)v6) >> 4;
  else
    v7 = 0;
  if ( v4 <= v7 )
  {
    sub_54E1B0(v3, *(uint32_t **)(a2 + 8), v6);
    v8 = *(uint32_t *)(a2 + 4);
    if ( v8 != 0 )
      v9 = *(uint32_t *)(this + 4) + 16 * ((*(uint32_t *)(a2 + 8) - v8) >> 4);
    else
      v9 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = v9;
    return this;
  }
  if ( v6 != nullptr )
    v10 = (*(uint32_t *)(this + 12) - (int)v6) >> 4;
  else
    v10 = 0;
  if ( v4 > v10 )
  {
    if ( v6 != nullptr )
      j__free(*(void **)(this + 4));
    v13 = *(uint32_t *)(a2 + 4);
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(a2 + 8) - v13) >> 4;
    else
      v14 = 0;
    if ( sub_44CF50((uint32_t *)this, v14) != 0 )
      *(uint32_t *)(this + 8) = sub_54E680(*(uint32_t **)(a2 + 4), *(uint32_t **)(a2 + 8), *(uint32_t **)(this + 4));
    return this;
  }
  if ( v6 != nullptr )
    v11 = (*(uint32_t *)(this + 8) - (int)v6) >> 4;
  else
    v11 = 0;
  v12 = (uint32_t *)(*(uint32_t *)(a2 + 4) + 16 * v11);
  sub_54E660(*(uint32_t **)(a2 + 4), v12, *(uint32_t **)(this + 4));
  *(uint32_t *)(this + 8) = sub_602460(v12, *(uint32_t **)(a2 + 8), *(uint32_t **)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x54FFB0 sub_54FFB0 —— PVP 结算窗口入队（54F610 + 4BF340，23 行——被 cashshop.cpp 0x550020 调用）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_54FFB0(int this, uint32_t *Block)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi
  unsigned int result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 4;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) >> 4 )
    return sub_54F610(this, *(char **)(this + 8), 1u, Block);
  v5 = *(uint32_t *)(this + 8);
  result = sub_4BF340(v5, 1, Block);
  *(uint32_t *)(this + 8) = v5 + 16;
  return result;
}


