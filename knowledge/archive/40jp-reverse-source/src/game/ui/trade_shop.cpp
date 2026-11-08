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
// 大白话：std::vector<int> 的扩容例程【推断】：元素数不足 uArg2 时按 4*uArg2 字节
// 新建缓冲、经 497E70 搬旧元素、free 旧块并更新 begin/end/cap 三指针(this+4/+8/+12)；
// uArg2 超过 0x3FFFFFFF 时走 4D7080 抛 "vector too long"。PVP 结算入队前靠它保证容量。
unsigned int /*thiscall*/ sub_5401A0(int this, unsigned int uArg2)  // 函数: PVP 结算联动（4D7080 对象查询 + 497E70），被 0x5500B0 等外部调用
{
  int oldBeg; // ecx
  int oldCount; // ebx
  unsigned int result; // eax
  char *pMem; // edi
  int oldBeg2; // eax
  int oldBeg3; // [esp-18h] [ebp-38h]
  int oldEnd; // [esp-14h] [ebp-34h]
  int v10; // [esp+0h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-14h]
  int *v12; // [esp+10h] [ebp-10h]
  int v13; // [esp+1Ch] [ebp-4h]
  size_t cbNew; // [esp+28h] [ebp+8h]

  v12 = &v10;
  if ( uArg2 > 0x3FFFFFFF )  // 若 uArg2 > 0x3FFFFFFF
    sub_4D7080(this);  // 调 sub_4D7080
  oldBeg = *(uint32_t *)(this + 4);  // oldBeg = this+4
  oldCount = 0;
  if ( oldBeg != 0 )  // 若 oldBeg != 0
    result = (*(uint32_t *)(this + 12) - oldBeg) >> 2;  // this+12 物品类型号
  else
    result = 0;
  if ( result < uArg2 )  // 若 result < uArg2
  {
    cbNew = 4 * uArg2;
    pMem = (char *)operator new(cbNew);
    oldEnd = *(uint32_t *)(this + 8);  // oldEnd = this+8
    oldBeg3 = *(uint32_t *)(this + 4);  // oldBeg3 = this+4
    Block = pMem;
    v13 = 0;
    sub_497E70(oldBeg3, oldEnd, pMem);  // uint32 区间逐元素拷贝
    oldBeg2 = *(uint32_t *)(this + 4);  // oldBeg2 = this+4
    if ( oldBeg2 != 0 )  // 若 oldBeg2 != 0
    {
      oldCount = (*(uint32_t *)(this + 8) - oldBeg2) >> 2;  // this+8 物品 id
      j__free(*(void **)(this + 4));  // 调 j__free
    }
    *(uint32_t *)(this + 12) = &pMem[cbNew];  // this+12 = &pMem[cbNew]
    *(uint32_t *)(this + 8) = &pMem[4 * oldCount];  // this+8 = &pMem[4 * oldCount]
    *(uint32_t *)(this + 4) = pMem;  // this+4 = pMem
    return (unsigned int)&pMem[cbNew];
  }
  return result;
}



// ------------------------------------------------------------
// 0x540280 sub_540280 —— 窗口数据准备（53FFC0）
// ------------------------------------------------------------
// 大白话：std::vector<int>::push_back【推断】：容量够(end<cap)直接尾插一个元素，
// 不够则转 53FFC0 扩容后再插。this+1/+2/+3 = begin/end/cap。
unsigned int /*thiscall*/ sub_540280(int *this, int *pDwArg2)  // 函数: 窗口数据准备（53FFC0）
{
  int oldBeg; // esi
  unsigned int curSize; // edx
  int *pEnd; // eax
  unsigned int result; // eax

  oldBeg = *(this + 1);  // oldBeg = this+1
  if ( oldBeg != 0 )  // 若 oldBeg != 0
    curSize = (*(this + 2) - oldBeg) >> 2;  // oldBeg=this+4 宿主对象
  else
    curSize = 0;
  if ( oldBeg == 0 || curSize >= (*(this + 3) - oldBeg) >> 2 )  // 若 oldBeg == 0 || curSize >= (*(this + 3) - oldBeg) >> 2
    return sub_53FFC0((int)this, *(this + 2), 1u, pDwArg2);  // 调 sub_53FFC0
  pEnd = (int *)*(this + 2);
  *pEnd = *pDwArg2;  // *pEnd 写入 *pDwArg2
  result = (unsigned int)(pEnd + 1);
  *(this + 2) = result;  // this+8 = result
  return result;
}



// ------------------------------------------------------------
// 0x5402D0 sub_5402D0 —— 窗口数据准备中层（转发 540280）
// ------------------------------------------------------------
// 大白话：对象登记辅助【推断】： pObjNew 尚未登记进 vector(this+1..+3) 时，
// 经 540280 尾插，再调该对象虚表 +68（把宿主 vector 交给它）与 +76(1)（登记确认）。
int /*thiscall*/ sub_5402D0(int *this, int pObjNew)  // 函数: 窗口数据准备中层（转发 540280）
{
  uint32_t *pVecEnd_7; // edx
  int result; // eax
  int pObj; // esi
  int v6; // ecx

  pVecEnd_7 = (uint32_t *)*(this + 1);
  if ( pVecEnd_7 != nullptr )  // 若 fld_e1 非空
    result = (*(this + 2) - (int)pVecEnd_7) >> 2;
  else
    result = 0;
  pObj = pObjNew;
  v6 = 0;
  if ( result <= 0 )  // 若 result <= 0
  {
LABEL_7:
    sub_540280(this, &pObjNew);  // 窗口数据准备（53FFC0）
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 68))(pObj, this);  // 调用虚函数槽 +68
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 76))(pObj, 1);  // 调用虚函数槽 +76
  }
  else
  {
    while ( *pVecEnd_7 != pObjNew )  // 当 *fld_e1 != pObjNew 循环
    {
      ++v6;  // 自增v6
      ++pVecEnd_7;  // 自增fld_e1
      if ( v6 >= result )  // 若 v6 >= result
        goto LABEL_7;  // 跳转 LABEL_7
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x540330 sub_540330 —— 13 行小辅助
// ------------------------------------------------------------
// 大白话：vector 清空【推断】：begin/end/cap(this+1/+2/+3) 三指针全部归零（不释放内存）。
int /*thiscall*/ sub_540330(uint32_t *this)  // 函数: 13 行小辅助
{
  *(this + 1) = 0;  // this+4 = 0
  *(this + 2) = 0;  // this+8 = 0
  *(this + 3) = 0;  // this+12 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x540340 sub_540340 —— 12 行小辅助
// ------------------------------------------------------------
// 大白话：vector 范围设定【推断】：直接写入 end=+2、cap=+3（配合外部预置缓冲使用）。
int /*thiscall*/ sub_540340(uint32_t *this, int nArg2, int nArg3)  // 函数: 12 行小辅助
{
  *(this + 2) = nArg2;  // this+8 = nArg2
  *(this + 3) = nArg3;  // this+12 = nArg3
  return nArg2;
}



// ------------------------------------------------------------
// 0x540360 IRDWindow__vmt2C —— IRDWindow__vmt2C 页签显示：44AB50(this+8, this+12, 12)——把 12 号子页设为当前
// ------------------------------------------------------------
// 大白话：窗口基类通用槽：调 44AB50（页签切换）把宿主(this+8)的第 12 号子页置为当前。
int /*thiscall*/ IRDWindow__vmt2C(int this)  // 函数: IRDWindow__vmt2C 页签显示：44AB50(this+8, this+12, 12)——把 12 号子页设为当前
{
  return sub_44AB50(*(uint32_t **)(this + 8), *(uint32_t *)(this + 12), 12);  // 页签切换
}



// ------------------------------------------------------------
// 0x540370 sub_540370 —— 窗口状态复位（+1/+5/+7 清零、+8=-1）
// ------------------------------------------------------------
// 大白话：区域选择窗状态复位：选中标记(+1/+5/+7)清零、当前条目索引(+8)=-1（无选中）。
int /*thiscall*/ sub_540370(uint32_t *this)  // 函数: 窗口状态复位（+1/+5/+7 清零、+8=-1）
{
  *(this + 1) = 0;  // this+4 = 0
  *(this + 5) = 0;  // this+20 = 0
  *(this + 7) = 0;  // this+28 = 0
  *(this + 8) = -1;  // this+32 = -1
  return 0;
}



// ------------------------------------------------------------
// 0x540390 sub_540390 —— 子窗口释放链：依次 vf+0 销毁 *(this+1)/(+5)/(+6) 三个子窗口
// ------------------------------------------------------------
// 大白话：析构辅助：对挂在本窗 +1/+5/+6 上的三个子窗口对象逐个调虚表槽0（标量删除，
// 参数 1）并清空指针。
int /*thiscall*/ sub_540390(uint32_t *this)  // 函数: 子窗口释放链：依次 vf+0 销毁 *(this+1)/(+5)/(+6) 三个子窗口
{
  int (/*thiscall*/ ***fld_e1)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e6)(uint32_t, int); // ecx

  fld_e1 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( fld_e1 != nullptr )  // 若 fld_e1 非空
    result = (**fld_e1)(fld_e1, 1);
  *(this + 1) = 0;  // this+4 = 0
  fld_e5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  if ( fld_e5 != nullptr )  // 若 fld_e5 非空
    result = (**fld_e5)(fld_e5, 1);
  *(this + 5) = 0;  // this+20 = 0
  fld_e6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  if ( fld_e6 != nullptr )  // 若 fld_e6 非空
    result = (**fld_e6)(fld_e6, 1);
  *(this + 6) = 0;  // this+24 = 0
  return result;
}



// ------------------------------------------------------------
// 0x5403D0 sub_5403D0 —— 对象状态切换（44E850）——区域选择联动
// ------------------------------------------------------------
// 大白话：区域选择开/关：开(+7=1)时把主条目(+1)的 +16 选中标记置 1、+8 索引复位 -1；
// 关时清标记，若之前是选中态再向全局窗口管理器 dword_8F8528 解除 63/62 两个对象登记。
char /*thiscall*/ sub_5403D0(uint32_t *this, int nArg2)  // 函数: 对象状态切换（44E850）——区域选择联动
{
  int nRet; // eax
  int prevState; // edx

  LOBYTE(nRet) = nArg2;
  prevState = *(this + 7);  // prevState = this+7
  *(this + 7) = nArg2;  // this+28 = nArg2
  if ( nArg2 != 0 )  // 若 nArg2 != 0
  {
    LOBYTE(nRet) = nArg2 - 1;
    if ( nArg2 == 1 )  // 若 nArg2 == 1
    {
      nRet = *(this + 1);  // nRet = this+1
      *(this + 8) = -1;  // this+32 = -1
      *(uint8_t *)(nRet + 16) = 1;  // nRet+16 = 1
    }
  }
  else
  {
    *(uint8_t *)(*(this + 1) + 16) = 0;
    if ( prevState == 1 )  // 若 prevState == 1
    {
      sub_44E850(dword_8F8528, 63);  // 按池号批量回收活动对象
      LOBYTE(nRet) = sub_44E850(dword_8F8528, 62);  // 按池号批量回收活动对象
    }
  }
  return nRet;  // nRet=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x540420 sub_540420 —— 按钮点击处理：CLICK_BUTTON2 音 + 44E8D0/44E850 对象登记/切换（53 行）
// ------------------------------------------------------------
// 大白话：区域选择列表点击：鼠标悬停命中条目（dword_79BE34 鼠标X == 条目+12）时
// 播 CLICK_BUTTON2 按钮音并 44E8D0 登记 0x3E(62) 号对象、记下选中索引(+8)；
// 点到已选条目(+6)则取消选中并解除 63/62 对象登记。
uint8_t */*thiscall*/ sub_540420(uint32_t *this)  // 按钮点击处理：CLICK_BUTTON2 音 + 44E8D0/44E850 对象登记/切换
{
  uint8_t *result; // eax
  int dword_79BE342; // edx
  int iHit; // esi
  uint32_t *pThis_5; // ecx
  int prevState; // eax
  int pMain; // ecx

  result = (uint8_t *)*(this + 1);
  if ( result[16] != 0 )  // 若 result[16] != 0
  {
    dword_79BE342 = dword_79BE34;
    iHit = 0;
    pThis_5 = this + 5;
    while ( *(uint8_t *)(*pThis_5 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*pThis_5 + 12) )  // 当 *(uint8_t *)(*pThis_5 + 17) == 0 || dword_79BE34 != *(uint32_t.. 循环
    {
      ++iHit;  // 自增iHit
      ++pThis_5;  // 自增pThis_5
      if ( iHit >= 1 )  // 若 iHit >= 1
        goto LABEL_9;  // 跳转 LABEL_9
    }
    if ( dword_9B9454 == 0 )  // 若 dword_9B9454 == 0
    {
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
      sub_44E8D0((char *)dword_8F8528, (void *)0x3E, 0, iHit);  // 对象池借出（按池号取可用对象）
      *(this + 8) = iHit;  // this+32 = iHit
      dword_79BE342 = dword_79BE34;
    }
LABEL_9:
    result = (uint8_t *)*(this + 6);
    if ( result[17] != 0 && dword_79BE342 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE342 == *((uint32_t *)result + 3)
    {
      prevState = *(this + 7);  // prevState = this+7
      pMain = *(this + 1);  // pMain = this+1
      *(this + 7) = 0;  // this+28 = 0
      *(uint8_t *)(pMain + 16) = 0;  // pMain+16 = 0
      if ( prevState == 1 )  // 若 prevState == 1
      {
        sub_44E850(dword_8F8528, 63);  // 按池号批量回收活动对象
        sub_44E850(dword_8F8528, 62);  // 按池号批量回收活动对象
      }
      return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
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
// 大白话：画战争房间区域选择地图：先画底图(418DD0(0))；悬停区域条目(+6)时在
// 批次 2 里叠加 22 号图块高亮；再对选中条目(+5)在其右上(+37,-28)画 42 号图钉；
// 无选中或悬停(+5)时在其上方(-16,-48)画 114~121 号 8 帧闪烁标记
// （帧号 = GetTickCount()%800/100+114，每 100ms 一帧）。+20/+24 = 条目X/Y。
int /*thiscall*/ sub_5404F0(uint32_t *this)  // 函数: 战争房间区域列表构建（418DD0 取控件 + 491530/491630 绘制批次）
{
  int pSprite0; // eax
  int fld_e6; // ecx
  int v4; // esi
  int fld_e62; // eax
  int areaY; // esi
  int areaX; // ebx
  int pSprite22; // eax
  int fld_e5; // eax
  int pinY; // esi
  int pinX; // ebx
  int pSprite42; // eax
  int fld_e52; // ecx
  int fld_e8; // esi
  int result; // eax
  DWORD dwNow; // esi
  int fld_e53; // edi
  int blinkY; // ebx
  int blinkX; // edi
  int pSpriteAnim; // eax

  pSprite0 = sub_418DD0(0);  // 调 sub_418DD0
  if ( pSprite0 != 0 )  // 若 pSprite0 != 0
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pSprite0 + 152))(pSprite0, 0, 0, dword_79C0B0);  // 调用虚函数槽 +152
  fld_e6 = *(this + 6);  // fld_e6 = this+6
  if ( *(uint8_t *)(fld_e6 + 17) != 0 )  // 若 *(uint8_t *)(fld_e6 + 17) != 0
  {
    v4 = *(uint32_t *)(fld_e6 + 12);  // v4 = fld_e6+12
    if ( dword_79BE3C == v4 || dword_79BE34 == v4 || dword_79BE38 == v4 )  // 若 dword_79BE3C == v4 || dword_79BE34 == v4 || dword_79BE38 == v4
    {
      sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      fld_e62 = *(this + 6);  // fld_e62 = this+6
      areaY = *(uint32_t *)(fld_e62 + 24);  // areaY = fld_e62+24
      areaX = *(uint32_t *)(fld_e62 + 20);  // areaX = fld_e62+20
      pSprite22 = sub_418DD0(22);  // 调 sub_418DD0
      if ( pSprite22 != 0 )  // 若 pSprite22 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pSprite22 + 152))(pSprite22, areaX, areaY, dword_79C0B0);  // 调用虚函数槽 +152
      sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
    }
  }
  fld_e5 = *(this + 5);  // fld_e5 = this+5
  pinY = *(uint32_t *)(fld_e5 + 24);  // pinY = fld_e5+24
  pinX = *(uint32_t *)(fld_e5 + 20);  // pinX = fld_e5+20
  pSprite42 = sub_418DD0(42);  // 调 sub_418DD0
  if ( pSprite42 != 0 )  // 若 pSprite42 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pSprite42 + 152))(pSprite42, pinX + 37, pinY - 28, dword_79C0B0);  // 调用虚函数槽 +152
  fld_e52 = *(this + 5);  // fld_e52 = this+5
  if ( *(uint8_t *)(fld_e52 + 17) != 0  // fld_e52=this+20 频道页号
    && ((fld_e8 = *(uint32_t *)(fld_e52 + 12), dword_79BE3C == fld_e8) || dword_79BE34 == fld_e8 || dword_79BE38 == fld_e8)  // 战争房间区域列表构建（418DD0 取控件 + 491530/491630 绘制批次）
    || (result = *(this + 8)) == 0 )
  {
    dwNow = GetTickCount() % 0x320 / 0x64 + 114;  // 调 GetTickCount（取系统运行毫秒数）
    sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    fld_e53 = *(this + 5);  // fld_e53 = this+5
    blinkY = *(uint32_t *)(fld_e53 + 24);  // blinkY = fld_e53+24
    blinkX = *(uint32_t *)(fld_e53 + 20);  // blinkX = fld_e53+20
    pSpriteAnim = sub_418DD0(dwNow);  // 调 sub_418DD0
    if ( pSpriteAnim != 0 )  // 若 pSpriteAnim != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pSpriteAnim + 152))(pSpriteAnim, blinkX - 16, blinkY - 48, dword_79C0B0);  // 调用虚函数槽 +152
    return sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
  }
  return result;
}



// ------------------------------------------------------------
// 0x540670 sub_540670 —— 世界地图绘制：资源 worldmap/arad.img（426BD0 图像 + 69C780/69A5F0/69A840 定位）
// ------------------------------------------------------------
// 大白话：装配世界地图窗：新建 640x480 底图并回挂宿主(+68)；从全局 dword_99FCC8+20
// （当前城镇状态）取 +76/+196 作按钮图基址，建两个 CNButton（图组 43/44 与 20/21）
// 分别定位 (52,231) 与 (463,400)，最后加载 worldmap/arad.img、选中索引(+8)复位 -1。
int /*thiscall*/ sub_540670(uint32_t *this)  // 函数: 世界地图绘制：资源 worldmap/arad.img（426BD0 图像 + 69C780/69A5F0/69A840 定位）
{
  uint8_t *pMapImg; // eax
  uint8_t *pMapImg2; // eax
  uint8_t *pBtnMem; // eax
  uint32_t *pBtn1; // edi
  int imgBase1; // ebx
  uint32_t *pBtnMem2; // ecx
  uint8_t *pBtnMem3; // eax
  uint32_t *pBtn2; // edi
  int imgBase2; // ebx
  uint32_t *pBtnMem22; // ecx
  int result; // eax

  pMapImg = operator new(0x68u);  // 堆分配 104 字节对象
  if ( pMapImg != nullptr )  // 若 pMapImg 非空
    pMapImg2 = sub_426BD0(pMapImg);  // 结果 = nengine::IControl 构造
  else
    pMapImg2 = nullptr;  // pMapImg2 = nullptr 空指针
  *(this + 1) = pMapImg2;  // this+4 = pMapImg2
  *((uint32_t *)pMapImg2 + 7) = 640;
  *((uint32_t *)pMapImg2 + 8) = 480;
  *(uint32_t *)(*(this + 1) + 68) = this;
  *(this + 2) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 76);  // this+8 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  *(this + 3) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 196);  // this+12 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pBtnMem = operator new(0x84u);  // 堆分配 132 字节对象
  pBtn1 = pBtnMem;
  if ( pBtnMem != nullptr )  // 若 pBtnMem 非空
  {
    imgBase1 = *(this + 3);  // imgBase1 = this+3
    sub_426BD0(pBtnMem);  // nengine::IControl 构造
    *pBtn1 = &vftbl_nengine__CNButton;  // *pBtn1 写入 &vftbl_nengine__CNButton
    sub_69C780(pBtn1);  // 调 sub_69C780
    nengine__CNButton__vmt20(imgBase1, 43, 43, 44, -1, 0, 0);  // imgBase1=this+12 物品类型号
    pBtnMem2 = pBtn1;
  }
  else
  {
    pBtnMem2 = nullptr;  // pBtnMem2 = nullptr 空指针
  }
  *(this + 5) = pBtnMem2;  // this+20 = pBtnMem2
  sub_69A5F0(pBtnMem2, 52, 231);  // 调 sub_69A5F0
  *(uint32_t *)(*(this + 5) + 68) = this;
  sub_69A840(*(this + 5));  // 调 sub_69A840
  pBtnMem3 = operator new(0x84u);  // 堆分配 132 字节对象
  pBtn2 = pBtnMem3;
  if ( pBtnMem3 != nullptr )  // 若 pBtnMem3 非空
  {
    imgBase2 = *(this + 2);  // imgBase2 = this+2
    sub_426BD0(pBtnMem3);  // nengine::IControl 构造
    *pBtn2 = &vftbl_nengine__CNButton;  // *pBtn2 写入 &vftbl_nengine__CNButton
    sub_69C780(pBtn2);  // 调 sub_69C780
    nengine__CNButton__vmt20(imgBase2, 20, 21, 21, 20, 0, 0);  // imgBase2=this+8 物品 id
    pBtnMem22 = pBtn2;
  }
  else
  {
    pBtnMem22 = nullptr;  // pBtnMem22 = nullptr 空指针
  }
  *(this + 6) = pBtnMem22;  // this+24 = pBtnMem22
  sub_69A5F0(pBtnMem22, 463, 400);  // 调 sub_69A5F0
  *(uint32_t *)(*(this + 6) + 68) = this;
  sub_69A840(*(this + 6));  // 调 sub_69A840
  result = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "worldmap/arad.img");  // 字符串 “worldmap/arad.img”
  *(this + 8) = -1;  // this+32 = -1
  *(this + 4) = result;  // this+16 = result
  return result;
}



// ------------------------------------------------------------
// 0x540810 CNRDSelectWarRoomArea__vmt0 —— CNRDSelectWarRoomArea__vmt0 构造（转发 5404F0 列表构建）
// ------------------------------------------------------------
// 大白话：区域选择窗主槽：仅当窗口已激活（+1 条目的 +16 选中标记非 0）且传入对象
// 就是该条目时，重建区域列表（5404F0）。
int /*thiscall*/ CNRDSelectWarRoomArea__vmt0(int *this, int nArg2)  // 函数: CNRDSelectWarRoomArea__vmt0 构造（转发 5404F0 列表构建）
{
  int result; // eax

  result = *(this + 1);  // result = this+1
  if ( *(uint8_t *)(result + 16) != 0 && nArg2 == result )  // 若 *(uint8_t *)(result + 16) != 0 && nArg2 == result
    return sub_5404F0(this);  // 战争房间区域列表构建（418DD0 取控件 + 491530/491630 绘制批次）
  return result;  // result=this+4 宿主对象
}



// ============================================================
// 【分区 3】堆叠数量指定控件（0x540830-0x540A10）
// IRDStackCountReceiver 接口 + CNRDStackNumberSet vmt8/vmt4；
// 数量确认见 0x5409C0（CLICK_BUTTON2 + 54A200 交易窗联动）。
// ============================================================
// ------------------------------------------------------------
// 0x540830 IRDStackCountReceiver__vmt0 —— IRDStackCountReceiver__vmt0 接口槽（11 行）
// ------------------------------------------------------------
// 大白话：堆叠数量接收者接口的单例登记：把接收者对象存入全局 dword_9B8030，
// 供数量指定窗（CNRDStackNumberSet）回调。
int /*stdcall*/ IRDStackCountReceiver__vmt0(int nArg1)  // 函数: IRDStackCountReceiver__vmt0 接口槽（11 行）
{
  dword_9B8030 = nArg1;
  return nArg1;
}



// ------------------------------------------------------------
// 0x540840 CNRDStackNumberSet__vmt8 —— CNRDStackNumberSet__vmt8 Update 槽（14 行）
// ------------------------------------------------------------
// 大白话：数量指定窗逐帧 Update：已登记接收者(dword_9B8030)时把消息转发到其虚表 +12。
int /*stdcall*/ CNRDStackNumberSet__vmt8(int nArg1)  // 函数: CNRDStackNumberSet__vmt8 Update 槽（14 行）
{
  int result; // eax

  if ( dword_9B8030 != 0 )  // 若 dword_9B8030 != 0
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_9B8030 + 12))(dword_9B8030, nArg1);  // 调用虚函数槽 +12
  return result;
}



// ------------------------------------------------------------
// 0x540860 CNRDStackNumberSet__vmt4 —— CNRDStackNumberSet__vmt4 标量删除析构
// ------------------------------------------------------------
// 大白话：数量指定窗析构：清掉接收者单例 dword_9B8030。
void CNRDStackNumberSet__vmt4()  // CNRDStackNumberSet__vmt4 标量删除析构
{
  dword_9B8030 = 0;
}



// ------------------------------------------------------------
// 0x540870 sub_540870 —— 数量窗口打开（69BCC0/402AE0 控件显示）
// ------------------------------------------------------------
// 大白话：打开数量指定窗：69BCC0 定位/挂载窗口控件，402AE0 按参数显示对应子页。
int /*thiscall*/ sub_540870(void *this, int nArg2)  // 函数: 数量窗口打开（69BCC0/402AE0 控件显示）
{
  sub_69BCC0(this);  // 调 sub_69BCC0
  return sub_402AE0(nArg2);  // 字符串包赋值 C 串（按需扩容后 qmemcpy + 尾 NUL + +4 置有效）
}



// ------------------------------------------------------------
// 0x540890 sub_540890 —— 数量输入辅助（28 行）
// ------------------------------------------------------------
// 大白话：数量指定窗状态初始化：+1..+9 各状态清零，+10=6/+11=7/+12=7 为默认
// 最小/最大/步进数量档位【推断】，+17=0xFFFF 输入上限复位。
int /*thiscall*/ sub_540890(uint32_t *this)  // 函数: 数量输入辅助（28 行）
{
  *(this + 1) = 0;  // this+4 = 0
  *(this + 2) = 0;  // this+8 = 0
  *(this + 3) = 0;  // this+12 = 0
  *(this + 4) = 0;  // this+16 = 0
  *(this + 5) = 0;  // this+20 = 0
  *(this + 6) = 0;  // this+24 = 0
  *(this + 8) = 0;  // this+32 = 0
  *(this + 7) = 0;  // this+28 = 0
  *(this + 9) = 0;  // this+36 = 0
  *(this + 10) = 6;  // this+40 = 6
  *(this + 11) = 7;  // this+44 = 7
  *(this + 13) = 0;  // this+52 = 0
  *(this + 12) = 7;  // this+48 = 7
  *(this + 14) = 0;  // this+56 = 0
  *(this + 15) = 0;  // this+60 = 0
  *(this + 16) = 0;  // this+64 = 0
  *(this + 17) = 0xFFFF;  // this+68 = 0xFFFF
  *(this + 18) = 0;  // this+72 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x5408E0 sub_5408E0 —— 数量输入辅助 2（50 行）
// ------------------------------------------------------------
// 大白话：数量指定窗析构辅助：对 +2..+5 与 +6..+9 挂着的全部子对象逐个调虚表槽0
// （标量删除）并清空指针。
int /*thiscall*/ sub_5408E0(uint32_t *this)  // 函数: 数量输入辅助 2（50 行）
{
  int (/*thiscall*/ ***fld_e2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e5)(uint32_t, int); // ecx
  int (/*thiscall*/ ****pThis_8)(uint32_t, int); // esi
  int i; // edi
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v10)(uint32_t, int); // ecx
  bool v11; // zf

  fld_e2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  if ( fld_e2 != nullptr )  // 若 fld_e2 非空
    result = (**fld_e2)(fld_e2, 1);
  fld_e3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;  // this+8 = 0
  if ( fld_e3 != nullptr )  // 若 fld_e3 非空
    result = (**fld_e3)(fld_e3, 1);
  fld_e4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 4);  // this+4 宿主对象
  *(this + 3) = 0;  // this+12 = 0
  if ( fld_e4 != nullptr )  // 若 fld_e4 非空
    result = (**fld_e4)(fld_e4, 1);
  fld_e5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 4) = 0;  // this+16 = 0
  if ( fld_e5 != nullptr )  // 若 fld_e5 非空
    result = (**fld_e5)(fld_e5, 1);
  *(this + 5) = 0;  // this+20 = 0
  pThis_8 = (int (/*thiscall*/ ****)(uint32_t, int))(this + 8);  // this+8 物品 id
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
  {
    v9 = *(pThis_8 - 2);
    if ( v9 != nullptr )  // 若 v9 非空
      result = (**v9)(v9, 1);
    v10 = *pThis_8;
    v11 = *pThis_8 == nullptr;
    *(pThis_8 - 2) = nullptr;
    if ( !v11 )  // 若 !v11
      result = (**v10)(v10, 1);
    *pThis_8++ = nullptr;  // *pThis_8++ 写入 nullptr
  }
  return result;
}



// ------------------------------------------------------------
// 0x540960 sub_540960 —— 数量输入框刷新（24 行）
// ------------------------------------------------------------
// 大白话：数量输入框刷新：当前悬停控件(dword_79BE54 == 挂件+12)未进入输入态
// （+256 标记为 0）时，把其标题文本(+124→+12)同步到全局 dword_79BE4C/54；
// 随后清 +2 挂件标记、+10 复位 6、调 CNCommandChecker__vmt40(0,1) 并走本窗 vmt4。
int /*thiscall*/ sub_540960(uint32_t *this)  // 函数: 数量输入框刷新（24 行）
{
  int fld_e1; // eax

  if ( dword_79BE54 == *(uint32_t *)(*(this + 3) + 12) )  // 若 dword_79BE54 == *(uint32_t *)(*(this + 3) + 12)
  {
    fld_e1 = *(uint32_t *)(*(this + 1) + 28);
    if ( *(uint8_t *)(fld_e1 + 256) == 0 )  // 若 *(uint8_t *)(fld_e1 + 256) == 0
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(fld_e1 + 124) + 12);
      dword_79BE54 = dword_79BE4C;
    }
  }
  *(uint8_t *)(*(this + 2) + 16) = 0;
  *(this + 10) = 6;  // this+40 = 6
  CNCommandChecker__vmt40(0, 1);
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 4))(this);  // 虚调用 vt+4
}



// ------------------------------------------------------------
// 0x5409C0 sub_5409C0 —— 数量确认：CLICK_BUTTON2 音 + 54A200 交易窗联动 + 540960 刷新
// ------------------------------------------------------------
// 大白话：数量确认按钮：各档位状态合法（+11/+13/+14 为 0、+12==4、挂件+64 有效）时
// 调 54A200(1) 把数量回传交易窗；随后播 CLICK_BUTTON2 确认音并刷新输入框。
int /*thiscall*/ sub_5409C0(uint32_t *this)  // 函数: 数量确认：CLICK_BUTTON2 音 + 54A200 交易窗联动 + 540960 刷新
{
  if ( *(this + 11) == 0
    && *(this + 13) == 0
    && *(this + 12) == 4  // this+12 物品类型号
    && *(this + 14) == 0
    && *(uint32_t *)(*(this + 1) + 64) != 0 )  // 数量确认：CLICK_BUTTON2 音 + 54A200 交易窗联动 + 540960 刷新
  {
    sub_54A200(1);  // 交易窗数量联动
  }
  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  return sub_540960(this);  // 数量输入框刷新
}



// ============================================================
// 【分区 4】摆摊窗口私有实现（0x540A10-0x541900）
// 摊位列表构建 0x540DE0（203 行）；摊位物品操作 0x541190（237 行：登记/
// 取出/44A980 数组访问）；0x541620=摊位点击（CLICK_BUTTON2 + 5409C0）。
// ============================================================
// ------------------------------------------------------------
// 0x540A10 sub_540A10 —— 摊位数据访问辅助（30 行）
// ------------------------------------------------------------
// 大白话：取当前摆摊对象：遍历摆摊单例(+1→+664..+668 的对象数组)，找到
// 编号(+48) == 本窗记录(+17) 且 +200 标记置位的对象返回；没有则返回 0。
int /*thiscall*/ sub_540A10(uint32_t *this)  // 函数: 摊位数据访问辅助（30 行）
{
  int fld_e1; // eax
  int *v2; // edx
  int *v3; // esi
  int fld_e17; // ecx
  int result; // eax

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  v2 = *(int **)(fld_e1 + 664);  // fld_e1=this+4 宿主对象
  v3 = *(int **)(fld_e1 + 668);  // fld_e1=this+4 宿主对象
  if ( v2 == v3 )  // 若 v2 == v3
    return 0;
  fld_e17 = *(this + 17);  // fld_e17 = this+17
  while ( 1 )  // 当 1 循环
  {
    result = *v2;
    if ( *(uint32_t *)(*v2 + 48) == fld_e17 && *(uint8_t *)(result + 200) != 0 )  // 若 *(uint32_t *)(*v2 + 48) == fld_e17 && *(uint8_t *)(result + 20..
      break;
    if ( ++v2 == v3 )  // 若 ++v2 == v3
      return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x540A50 sub_540A50 —— 摊位条目文本组装（541A30/541B20 + 432F00 全局窗口获取，50 行）
// ------------------------------------------------------------
// 大白话：按当前页签(+10)与来源(+11)取第 +13 行的条目：来源 5 走摆摊单例列表
// (541A30/541B20)，来源 2 走挂件(+1→+80)的数组(+96..+100)，其余按 +11 从
// 432F00 全局窗口表取数组；越界一律返回 0。
int /*thiscall*/ sub_540A50(uint32_t *this, int nArg2)  // 函数: 摊位条目文本组装（541A30/541B20 + 432F00 全局窗口获取，50 行）
{
  int fld_e10; // eax
  int fld_e13; // esi
  int v5; // eax
  int v6; // eax
  int fld_e1; // ecx
  int v9; // edx
  unsigned int fld_e132; // esi
  uint32_t *fld_e11; // eax
  int fld_e133; // esi

  fld_e10 = *(this + 10);  // fld_e10 = this+10
  if ( fld_e10 == 2 )  // 若 fld_e10 == 2
  {
    if ( *(this + 11) == 5 )  // 若 *(this + 11) == 5
    {
      fld_e13 = *(this + 13);  // fld_e13 = this+13
      v5 = sub_541A30();  // 结果 = 摊位条目名取串
      v6 = sub_541B20(v5);  // 调 sub_541B20
      if ( fld_e13 < *(uint32_t *)(v6 + 8) )  // 若 fld_e13 < *(uint32_t *)(v6 + 8)
        return *(uint32_t *)(*(uint32_t *)(v6 + 12) + 4 * fld_e13);  // fld_e13=this+52 光环状态字节
    }
    else
    {
      fld_e1 = *(uint32_t *)(*(this + 1) + 80);
      v9 = *(uint32_t *)(fld_e1 + 96);  // v9 = fld_e1+96
      fld_e132 = *(this + 13);  // fld_e132 = this+13
      if ( v9 != 0 && fld_e132 < (*(uint32_t *)(fld_e1 + 100) - v9) >> 2 )  // 若 v9 != 0 && fld_e132 < (*(uint32_t *)(fld_e1 + 100) - v9) >> 2
        return *(uint32_t *)(v9 + 4 * fld_e132);  // fld_e132=this+52 光环状态字节
    }
  }
  else if ( fld_e10 != 5 )  // 否则若 fld_e10 != 5
  {
    fld_e11 = sub_432F00(*(this + 11));  // 结果 = 按类型取全局列表对象
    if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    {
      fld_e133 = *(this + 13);  // fld_e133 = this+13
      if ( fld_e133 < fld_e11[2] )  // 若 fld_e133 < fld_e11[2]
        return *(uint32_t *)(fld_e11[3] + 4 * fld_e133);  // fld_e133=this+52 光环状态字节
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x540AE0 sub_540AE0 —— 摊位展示绘制（126 行：43C250/43C060/43C410 列表控件 + 426BD0/69C780 图像 + 4BF300）
// ------------------------------------------------------------
int /*thiscall*/ sub_540AE0(int *this, void *Block)  // 函数: 摊位展示绘制（126 行：43C250/43C060/43C410 列表控件 + 426BD0/69C780 图像 + 4BF300）
{
  int v3; // edi
  uint8_t *pMem; // eax
  uint8_t *v5; // eax
  void *pMem2; // eax
  int v7; // eax
  uint32_t *pMem3; // eax
  uint32_t *v9; // eax
  uint32_t *pMem4; // eax
  uint32_t *v11; // eax
  int v12; // ebx
  uint8_t *pMem5; // eax
  uint32_t *pMem52; // edi
  uint32_t *pMem522; // ecx
  uint8_t *pMem6; // eax
  uint32_t *pMem62; // edi
  uint32_t *pMem622; // ecx
  bool v19; // cc
  int fld_e1; // eax
  int v22; // [esp+Ch] [ebp-18h]
  int v23; // [esp+10h] [ebp-14h]
  int v24; // [esp+14h] [ebp-10h]
  int *Blocka; // [esp+2Ch] [ebp+8h]

  *(this + 1) = (int)Block;  // this+4 = (int)Block
  v3 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  v22 = v3;
  pMem = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v5 = sub_43C250(pMem, v3, 50);  // 结果 = nengine::CNFrame 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 2) = (int)v5;  // this+8 = (int)v5
  pMem2 = operator new(0xE4u);  // 堆分配 228 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v7 = sub_43C060((int)pMem2, 10, 70);  // 结果 = nengine::CNEdit 构造
  else
    v7 = 0;
  *(this + 3) = v7;  // this+12 = v7
  dword_9D3BD8 = dword_99FCCC;
  *(uint32_t *)(*(this + 3) + 128) = -5512193;
  sub_69A5F0((uint32_t *)*(this + 3), 38, 17);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 3));  // 调 sub_69A840
  pMem3 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    v9 = sub_43C410(pMem3, v3, 9, 10, 11, 9, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v9 = nullptr;  // v9 = nullptr 空指针
  *(this + 4) = (int)v9;  // this+16 = (int)v9
  sub_69A5F0(v9, 25, 41);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 4));  // 调 sub_69A840
  pMem4 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    v11 = sub_43C410(pMem4, v3, 12, 13, 14, 12, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v11 = nullptr;  // v11 = nullptr 空指针
  *(this + 5) = (int)v11;  // this+20 = (int)v11
  sub_69A5F0(v11, 86, 41);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 5));  // 调 sub_69A840
  v23 = 8;
  v24 = 15;
  v12 = 51;
  Blocka = this + 8;  // this+8 物品 id
  do
  {
    pMem5 = operator new(0x84u);  // 堆分配 132 字节对象
    pMem52 = pMem5;
    if ( pMem5 != nullptr )  // 若 pMem5 非空
    {
      sub_426BD0(pMem5);  // nengine::IControl 构造
      *pMem52 = &nengine::CNButton::`vftable';
      sub_69C780((int)v14);  // 调 sub_69C780
      sub_69C7B0((int)v14, v22, v12, v12 + 1, v12 + 2, v12, 0, 0);  // 调 sub_69C7B0
      v15 = v14;
    }
    else
    {
      v15 = nullptr;  // v15 = nullptr 空指针
    }
    *(Blocka - 2) = (int)v15;  // Blocka=this+8 物品 id
    sub_69A5F0(v15, 115, v24);  // 调 sub_69A5F0
    sub_69A840((uint32_t *)*(this + 2), *(Blocka - 2));  // 调 sub_69A840
    v16 = operator new(0x84u);  // 堆分配 132 字节对象
    v17 = v16;
    if ( v16 != nullptr )  // 若 v16 非空
    {
      sub_426BD0(v16);  // nengine::IControl 构造
      *v17 = &nengine::CNButton::`vftable';
      sub_69C780((int)pMem62);  // 调 sub_69C780
      sub_69C7B0((int)pMem62, v22, v12 + 6, v12 + 7, v12 + 8, v12 + 6, 0, 0);  // 调 sub_69C7B0
      pMem622 = pMem62;
    }
    else
    {
      pMem622 = nullptr;  // pMem622 = nullptr 空指针
    }
    *Blocka = (int)pMem622;  // *Blocka 写入 (int)pMem622
    sub_69A5F0(pMem622, 130, v23);  // 调 sub_69A5F0
    sub_69A840((uint32_t *)*(this + 2), *Blocka);  // 调 sub_69A840
    v12 += 3;
    v19 = v24 + 8 < 31;
    ++Blocka;  // 自增Blocka
    v24 += 8;
    v23 += 14;
  }
  while ( v19 );  // 当 v19 循环
  if ( dword_79BE54 == *(uint32_t *)(*(this + 3) + 12) )  // 若 dword_79BE54 == *(uint32_t *)(*(this + 3) + 12)
  {
    fld_e1 = *(uint32_t *)(*(this + 1) + 28);
    if ( *(uint8_t *)(fld_e1 + 256) == 0 )  // 若 *(uint8_t *)(fld_e1 + 256) == 0
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(fld_e1 + 124) + 12);
      dword_79BE54 = dword_79BE4C;
    }
  }
  *(uint8_t *)(*(this + 2) + 16) = 0;
  *(this + 10) = 6;  // this+40 = 6
  sub_4BF300(0, 1);  // 槽写侧（+64 + 索引）
  return (*(int (/*thiscall*/ **)(int *))(*this + 4))(this);  // 虚调用 vt+4
}


// ------------------------------------------------------------
// 0x540DE0 sub_540DE0 —— 摊位列表构建（203 行：540A10/62EE70/540A50/541A30/542AB0 + 484FA0/48FCA0/48FD70 窗口件）
// ------------------------------------------------------------
int /*thiscall*/ sub_540DE0(int *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7, int nArg8)  // 函数: 摊位列表构建（203 行：540A10/62EE70/540A50/541A30/542AB0 + 484FA0/48FCA0/48FD70 窗口件）
{
  int nArg22; // ebx
  int result; // eax
  int pObj2; // edi
  int pObj; // ebx
  int v13; // edi
  int v14; // eax
  bool fld_e11; // zf
  unsigned int v16; // ebx
  unsigned int v17; // eax
  int v18; // eax
  unsigned int v19; // ebx
  unsigned int v20; // ebx
  unsigned int fld_e1822; // eax
  int v22; // ecx
  int fld_e183; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // edi
  int fld_e18; // ebx
  int v28; // ebx
  int fld_e184; // eax
  int pHostCtrl; // edx
  int v31; // ecx
  int v32; // eax
  int fld_e22; // edx
  int fld_e23; // edx
  char Buffer[32]; // [esp+Ch] [ebp-24h] BYREF
  int dword_796E502; // [esp+2Ch] [ebp-4h]
  unsigned int fld_e182; // [esp+44h] [ebp+14h]
  int v38; // [esp+44h] [ebp+14h]

  nArg22 = nArg2;
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  *(this + 11) = nArg3;  // this+44 = nArg3
  *(this + 13) = nArg4;  // this+52 = nArg4
  *(this + 14) = nArg6;  // this+56 = nArg6
  *(this + 16) = nArg8;  // this+64 = nArg8
  *(this + 10) = nArg2;  // this+40 = nArg2
  *(this + 12) = nArg5;  // this+48 = nArg5
  *(this + 15) = nArg7;  // this+60 = nArg7
  if ( nArg2 == 5 )  // 若 nArg2 == 5
  {
    *(this + 17) = nArg7;  // this+68 = nArg7
    result = sub_540A10();  // 结果 = 摊位数据访问辅助
    if ( result == 0 )  // 若 result == 0
      return result;
    result = sub_62EE70(result + 64);  // 结果 = 可合成次数上限计算
    *(this + 18) = result;  // this+72 = result
    if ( result == 0 )  // 若 result == 0
      return result;
    goto LABEL_41;  // 跳转 LABEL_41
  }
  result = sub_540A50(1);  // 结果 = 摊位条目文本组装
  pObj2 = result;
  if ( result == 0 )  // 若 result == 0
    return result;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 20))(result, 1);  // 调用虚函数槽 +20
  if ( (uint8_t)result == 0 )  // 若 (uint8_t)result == 0
    return result;
  *(this + 17) = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 4);  // this+17 激活/可命中标志
  if ( nArg2 != 1 )  // 若 nArg2 != 1
  {
    if ( nArg2 != 2 )  // 若 nArg2 != 2
      goto LABEL_43;  // 跳转 LABEL_43
    fld_e11 = *(this + 11) == 5;
    *(this + 18) = 1;  // this+72 = 1
    if ( fld_e11 )  // 若 fld_e11
    {
      sub_541A30();  // 摊位条目名取串
      v16 = sub_542AB0(pObj2);  // 结果 = 摊位数据释放（4BE520）
      if ( v16 == 0 )  // 若 v16 == 0
      {
LABEL_35:
        v26 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 56);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
        if ( v26 != 0 )  // 若 v26 != 0
        {
          fld_e18 = *(this + 18);  // fld_e18 = this+18
          v38 = *((uint32_t *)dword_8F852C + 1);  // 全局 dword_8F852C = 角色/物品栏管理器
          if ( (sub_484FA0() - v38) / v26 >= fld_e18 )  // 全局时间系数计算（+732 与 +746 相乘）
          {
            fld_e184 = fld_e18;  // fld_e18=this+72 快照槽（0x6491A0：*(this+72) …
          }
          else
          {
            v28 = *((uint32_t *)dword_8F852C + 1);  // 全局 dword_8F852C = 角色/物品栏管理器
            fld_e184 = (sub_484FA0() - v28) / v26;  // 结果 = 全局时间系数计算（+732 与 +746 相乘）
          }
          *(this + 18) = fld_e184;  // this+72 = fld_e184
        }
        nArg22 = nArg2;
        result = 1;
        goto LABEL_41;  // 跳转 LABEL_41
      }
      v17 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));  // 全局 dword_8F852C = 角色/物品栏管理器
      if ( v17 / v16 >= (*(int (/*fastcall*/ **)(int, unsigned int))(*(uint32_t *)pObj2 + 44))(pObj2, v17 % v16) )  // 虚槽+44 IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 + 69A5F0/69A8
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2);  // 调用虚函数槽 +44
      else
        v18 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3))  // 全局 dword_8F852C = 角色/物品栏管理器
            / v16;
    }
    else
    {
      v19 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 36);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
      if ( v19 != 0 )  // 若 v19 != 0
        *(this + 18) = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C  // 全局 dword_8F852C = 角色/物品栏管理器
                                                                                                 + 3))
                     / v19;
      v20 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 44);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
      if ( v20 != 0 )  // 若 v20 != 0
      {
        fld_e182 = *(this + 18);  // fld_e182 = this+18
        if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8))  // 全局 dword_8F852C = 角色/物品栏管理器
           / v20 >= fld_e182 )  // fld_e182=this+72 快照槽（0x6491A0：*(this+72) …
          fld_e1822 = fld_e182;  // fld_e182=this+72 快照槽（0x6491A0：*(this+72) …
        else
          fld_e1822 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8))  // 全局 dword_8F852C = 角色/物品栏管理器
              / v20;
        *(this + 18) = fld_e1822;  // this+72 = fld_e1822
      }
      v22 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 40);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
      if ( v22 != 0 )  // 若 v22 != 0
      {
        fld_e183 = dword_8F7C0C / v22;  // 全局 dword_8F7C0C = 现金(Cash)
        if ( dword_8F7C0C / v22 >= *(this + 18) )  // 全局 dword_8F7C0C = 现金(Cash)
          fld_e183 = *(this + 18);  // fld_e183 = this+18
        *(this + 18) = fld_e183;  // this+72 = fld_e183
      }
      v24 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 52);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
      if ( v24 == 0 )  // 若 v24 == 0
        goto LABEL_35;  // 跳转 LABEL_35
      v25 = sub_48FCA0();  // 结果 = 自身座位下标查找（表 dword_99FF08）
      v18 = sub_48FD70(v25) / v24;  // 结果 = 槽字段读取·第二组（基址 +112）
    }
    *(this + 18) = v18;  // this+72 = v18
    goto LABEL_35;  // 跳转 LABEL_35
  }
  result = nArg3;
  if ( (nArg3 == 4 || nArg5 == 4) && *(uint32_t *)(dword_8F8538 + 8) == 1 )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return result;
  if ( nArg3 == 0 && nArg5 == 4 && nArg4 == 0 )  // 若 nArg3 == 0 && nArg5 == 4 && nArg4 == 0
  {
    pObj = **(uint32_t **)(*(uint32_t *)(dword_8F8538 + 16) + 12);  // 全局 dword_8F8538 = 随身影身/占位管理器
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2);  // 调用虚函数槽 +44
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj);  // 调用虚函数槽 +44
    nArg22 = nArg2;
    *(this + 18) = v14 + v13;  // this+72 = v14 + v13
LABEL_47:
    result = (*(int (/*thiscall*/ **)(uint32_t))(***(uint32_t ***)(*(uint32_t *)(dword_8F8538 + 16) + 12) + 44))(**(uint32_t **)(*(uint32_t *)(dword_8F8538 + 16) + 12));  // 全局 dword_8F8538 = 随身影身/占位管理器
    goto LABEL_41;  // 跳转 LABEL_41
  }
LABEL_43:
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2);  // 调用虚函数槽 +44
  *(this + 18) = result;  // this+72 = result
  if ( nArg2 == 1 && nArg3 == 0 && nArg5 == 4 && nArg4 == 0 )  // 若 nArg2 == 1 && nArg3 == 0 && nArg5 == 4 && nArg4 == 0
    goto LABEL_47;  // 跳转 LABEL_47
LABEL_41:
  sprintf(Buffer, "%d", result);  // 字符串 “%d”
  sub_69BCC0(*(this + 3));  // 调 sub_69BCC0
  sub_402AE0(Buffer);  // 字符串包赋值 C 串（按需扩容后 qmemcpy + 尾 NUL + +4 置有效）
  if ( nArg22 == 2 )  // 若 nArg22 == 2
  {
    pHostCtrl = *(this + 2);  // fld_e2 = this+2
    v31 = pt.x - (*(uint32_t *)(pHostCtrl + 28) >> 1);  // fld_e2=this+8 物品 id
    v32 = pt.y - (*(uint32_t *)(pHostCtrl + 32) >> 1);  // fld_e2=this+8 物品 id
  }
  else
  {
    v31 = pt.x - 51;
    v32 = pt.y - 53;
  }
  if ( v31 >= 0 )  // 若 v31 >= 0
  {
    fld_e22 = *(uint32_t *)(*(this + 2) + 28);
    if ( (unsigned int)(fld_e22 + v31) > 0x280 )  // 若 (unsigned int)(fld_e22 + v31) > 0x280
      v31 = 640 - fld_e22;
  }
  else
  {
    v31 = 0;
  }
  if ( v32 >= 0 )  // 若 v32 >= 0
  {
    fld_e23 = *(uint32_t *)(*(this + 2) + 32);
    if ( (unsigned int)(fld_e23 + v32) > 0x1E0 )  // 若 (unsigned int)(fld_e23 + v32) > 0x1E0
      v32 = 480 - fld_e23;
  }
  else
  {
    v32 = 0;
  }
  *(uint8_t *)(*(this + 2) + 16) = 1;
  sub_69A5F0((uint32_t *)*(this + 2), v31, v32);  // 调 sub_69A5F0
  dword_79BE4C = *(uint32_t *)(*(this + 3) + 12);
  dword_79BE54 = dword_79BE4C;
  return sub_4BF300(0, 0);  // 槽写侧（+64 + 索引）
}


// ------------------------------------------------------------
// 0x541190 sub_541190 —— 摊位物品操作（237 行：44E8D0 登记 + 44A980 数组访问 + 50D660/547170/563E90/62F530/44E340/5634F0）
// ------------------------------------------------------------
void /*thiscall*/ sub_541190(void *this)  // 函数: 摊位物品操作（237 行：44E8D0 登记 + 44A980 数组访问 + 50D660/547170/563E90/62F530/44E340/5634F0）
{
  int pThis_A; // eax
  int pObj2; // edi
  const char *pThis_3; // eax
  int v5; // ebx
  int pThis_A2; // eax
  int v7; // eax
  int pThis_A3; // eax
  int pThis_B; // eax
  int v10; // eax
  int pThis_C; // ecx
  int v12; // eax
  char v13; // al
  uint32_t *pThis_B2; // eax
  int *pThis_E; // eax
  int v16; // edx
  int v17; // eax
  int v18; // eax
  int pObj3; // eax
  int pObj4; // eax
  int v21; // eax
  int v22; // eax
  int pThis_D; // [esp-14h] [ebp-44h]
  uint32_t *pThis_C2; // [esp-Ch] [ebp-3Ch]
  signed int pThis_E2; // [esp-8h] [ebp-38h]
  void *pBuf[4]; // [esp+8h] [ebp-28h] BYREF
  int pObj22; // [esp+18h] [ebp-18h] BYREF
  int v28; // [esp+1Ch] [ebp-14h]
  int pObj; // [esp+20h] [ebp-10h]
  int v30; // [esp+2Ch] [ebp-4h]

  pThis_A = *((uint32_t *)this + 10);  // pThis_A=this+40 物品状态附属标志
  pObj2 = 0;
  pObj = 0;
  if ( pThis_A == 5 )  // 若 pThis_A == 5
  {
    pObj = sub_540A10();  // 结果 = 摊位数据访问辅助
    if ( pObj == 0 )  // 若 pObj == 0
    {
      sub_540960(this);  // 数量输入框刷新
      return;
    }
  }
  else
  {
    pObj2 = sub_540A50(0);  // 结果 = 摊位条目文本组装
    if ( pObj2 == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 4) != *((uint32_t *)this + 17) )  // this+17 激活/可命中标志
    {
      v22 = sub_422E70(492);  // 调 sub_422E70
      sub_44E8D0(*((char **)this + 1), (void *)0x1B, v22, 0);  // 对象池借出（按池号取可用对象）
      sub_540960(this);  // 数量输入框刷新
      return;
    }
  }
  pThis_3 = (const char *)sub_69B740(*((uint32_t *)this + 3));
  v5 = j__atol(pThis_3);  // 调 j__atol
  if ( *((uint32_t *)this + 10) == 1
    && *((uint32_t *)this + 11) == 0
    && *((uint32_t *)this + 12) == 4  // this+12 物品类型号
    && *((uint32_t *)this + 13) == 0 )  // 摊位物品操作（237 行：44E8D0 登记 + 44A980 数组访问 + 50D660/547170/563E90/62F530/44E340/5634F0）
  {
    v5 -= (*(int (/*thiscall*/ **)(uint32_t))(***(uint32_t ***)(*(uint32_t *)(dword_8F8538 + 16) + 12) + 44))(**(uint32_t **)(*(uint32_t *)(dword_8F8538 + 16) + 12));  // 全局 dword_8F8538 = 随身影身/占位管理器
    if ( v5 < 0 )  // 若 v5 < 0
    {
      *((uint32_t *)this + 11) = 4;  // this+44 = 4
      *((uint32_t *)this + 12) = 0;  // this+48 = 0
      *((uint32_t *)this + 14) = 0;  // this+56 = 0
      pObj2 = **(uint32_t **)(*(uint32_t *)(dword_8F8538 + 16) + 12);  // 全局 dword_8F8538 = 随身影身/占位管理器
      v5 = -v5;
    }
  }
  if ( v5 == 0 )  // 若 v5 == 0
    goto LABEL_29;  // 跳转 LABEL_29
  pThis_A2 = *((uint32_t *)this + 10);  // pThis_A2=this+40 物品状态附属标志
  if ( pThis_A2 != 2 && pThis_A2 != 5 && v5 > (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2)  // 若 pThis_A2 != 2 && pThis_A2 != 5 && v5 > (unsigned int)(*(int (/..
    || *((uint32_t *)this + 11) == 5 && v5 > (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2) )
  {
    v7 = sub_422E70(493);  // 调 sub_422E70
    sub_44E8D0(*((char **)this + 1), (void *)0x1B, v7, 0);  // 对象池借出（按池号取可用对象）
    return;
  }
  pThis_A3 = *((uint32_t *)this + 10);  // pThis_A3=this+40 物品状态附属标志
  if ( pThis_A3 == 0 )  // 若 pThis_A3 == 0
  {
    sub_44E8D0(*((char **)this + 1), (void *)0x15, pObj2, v5);  // 对象池借出（按池号取可用对象）
    sub_540960(this);  // 数量输入框刷新
    return;
  }
  if ( pThis_A3 == 1 )  // 若 pThis_A3 == 1
  {
    pThis_B = *((uint32_t *)this + 11);  // pThis_B=this+44 剩余时间 ms
    if ( (pThis_B != 0 || *((uint32_t *)this + 12) != 2) && (pThis_B != 2 || *((uint32_t *)this + 12) != 0) )  // 若 (pThis_B != 0 || *((uint32_t *)this + 12) != 2) && (pThis_B !=..
    {
      if ( pThis_B != 0 || *((uint32_t *)this + 12) != 4 )  // 若 pThis_B != 0 || *((uint32_t *)this + 12) != 4
      {
        if ( pThis_B != 4 || *((uint32_t *)this + 12) != 0 )  // 若 pThis_B != 4 || *((uint32_t *)this + 12) != 0
        {
          if ( pThis_B == 0 )  // 若 pThis_B == 0
          {
            if ( *((uint32_t *)this + 12) == 5 )  // 若 *((uint32_t *)this + 12) == 5
            {
              pObj3 = sub_541A30();  // 结果 = 摊位条目名取串
              (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj3 + 60))(  // 虚槽+60 CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行：4BE520 + 48
                pObj3,
                *((uint32_t *)this + 13),
                *((uint32_t *)this + 14),
                *((uint32_t *)this + 11),
                *((uint32_t *)this + 15),
                v5);
            }
            else if ( *((uint32_t *)this + 12) == 6 )  // 否则若 *((uint32_t *)this + 12) == 6
            {
              (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 8))(this, v5);  // 调用虚函数槽 +8
            }
          }
        }
        else
        {
          pThis_E = (int *)sub_44A980(*((uint32_t *)this + 14));  // 结果 = 带界索引 getter
          pObj = (int)pThis_E;
          if ( pThis_E == nullptr
            || (v16 = *(uint32_t *)pObj2,
                v28 = *pThis_E,
                v17 = (*(int (/*thiscall*/ **)(int))(v16 + 16))(pObj2),
                (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(v28 + 60))(pObj, *(uint32_t *)(v17 + 4)) != 0) )
          {
            sub_484AF0(dword_8F8538, *((uint32_t *)this + 13), v5, *((uint32_t *)this + 12), *((uint32_t *)this + 14));  // 技能施放请求（包 op 19 变体：槽/参数/来源字段序不同）
          }
          else
          {
            v18 = sub_422E70(494);  // 调 sub_422E70
            sub_44E8D0(*((char **)this + 1), (void *)0x1B, v18, 0);  // 对象池借出（按池号取可用对象）
          }
        }
      }
      else
      {
        sub_4848E0(dword_8F8538, v5, 0, *((uint32_t *)this + 13), v5);  // 技能施放请求（包 op 19：来源/槽/参数，前置等级与占用校验）
      }
      goto LABEL_29;  // 跳转 LABEL_29
    }
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2);  // 调用虚函数槽 +16
    pThis_C = *((uint32_t *)this + 12);  // this+12 物品类型号
    v12 = v5 * *(uint32_t *)(v10 + 56);
    if ( pThis_C != 0 )  // 若 pThis_C != 0
    {
      if ( pThis_C != 2 )  // 若 pThis_C != 2
        goto LABEL_32;  // 跳转 LABEL_32
      v13 = sub_50D660(v12, 1);  // 结果 = 冷却时间比较器（剩余毫秒 ×0.001 秒上屏）
    }
    else
    {
      v13 = sub_547170(v12, 1);  // 结果 = 物品格子查询（484FA0 + 422E70/44E8D0）
    }
    if ( v13 == 1 )  // 若 v13 == 1
    {
LABEL_29:
      sub_540960(this);  // 数量输入框刷新
      return;
    }
LABEL_32:
    pThis_E2 = *((uint32_t *)this + 14);  // pThis_E2=this+56 键盘输入使能
    pThis_C2 = (uint32_t *)sub_432F00(*((uint32_t *)this + 12));  // 结果 = 按类型取全局列表对象
    pThis_D = *((uint32_t *)this + 13);  // pThis_D=this+52 光环状态字节
    pThis_B2 = (uint32_t *)sub_432F00(*((uint32_t *)this + 11));  // 结果 = 按类型取全局列表对象
    sub_4866D0(pThis_B2, pThis_D, v5, pThis_C2, pThis_E2);  // 请求 op 19 带来源对象（等级 + 来源容器）
    goto LABEL_29;  // 跳转 LABEL_29
  }
  if ( pThis_A3 != 2 )  // 若 pThis_A3 != 2
  {
    switch ( pThis_A3 )  // 分支：按 pThis_A3 分派
    {
      case 3:  // case 3
        if ( *((uint32_t *)this + 16) == 1 )  // 若 *((uint32_t *)this + 16) == 1
        {
          byte_9B888A = *((uint32_t *)this + 15) != 0;
          sub_44E8D0(*((char **)this + 1), (void *)0x14, pObj2, v5);  // 对象池借出（按池号取可用对象）
        }
        else
        {
          sub_563E90(pObj2, v5, *((uint32_t *)this + 1));  // 出售执行
          if ( *((uint32_t *)this + 15) == 1 )  // 若 *((uint32_t *)this + 15) == 1
            sub_44ABE0(5);  // 选中索引 setter
        }
        break;
      case 4:  // case 4
        if ( *((uint32_t *)this + 11) == 0 )  // 若 *((uint32_t *)this + 11) == 0
          sub_486330(dword_8F852C, *((uint32_t *)this + 13), v5);  // 请求 op 50（含本地玩家两字段）【推断：宠物/召唤或技能升阶】
        break;
      case 5:  // case 5
        sub_62F530(v5);  // 合成请求发包（27 号包）
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 32))(pObj);  // 调用虚函数槽 +32
        break;
      default:
        break;
    }
    goto LABEL_29;  // 跳转 LABEL_29
  }
  if ( *((uint32_t *)this + 11) == 5 )  // 若 *((uint32_t *)this + 11) == 5
  {
    pObj4 = sub_541A30();  // 结果 = 摊位条目名取串
    (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj4 + 96))(pObj4, *((uint32_t *)this + 13), v5);  // 调用虚函数槽 +96
    goto LABEL_29;  // 跳转 LABEL_29
  }
  memset(&pBuf[1], 0, 12);  // 清零 12 字节块
  v30 = 0;
  pObj22 = pObj2;
  v28 = v5;
  sub_44E340(&pObj22);  // 8 字节元素容器尾插单值
  if ( (uint8_t)sub_5634F0(pBuf, 1) != 0 )  // 购买执行
  {
    if ( *((uint32_t *)this + 16) == 1 )  // 若 *((uint32_t *)this + 16) == 1
    {
      byte_9B8889 = *((uint32_t *)this + 15) != 0;
      sub_44E8D0(*((char **)this + 1), (void *)0x13, pObj2, v5);  // 对象池借出（按池号取可用对象）
      v30 = -1;
      sub_5E5260(pBuf);  // 调 sub_5E5260
    }
    else
    {
      v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2);  // 调用虚函数槽 +16
      sub_563410(*(uint32_t *)(v21 + 4), v5);  // 确认参数（423200/423290/423380）
      if ( *((uint32_t *)this + 15) == 1 )  // 若 *((uint32_t *)this + 15) == 1
        sub_44ABE0(4);  // 选中索引 setter
      v30 = -1;
      sub_5E5260(pBuf);  // 调 sub_5E5260
    }
    goto LABEL_29;  // 跳转 LABEL_29
  }
  sub_5E5260(pBuf);  // 调 sub_5E5260
}


// ------------------------------------------------------------
// 0x541620 sub_541620 —— 摊位点击处理：CLICK_BUTTON2 + 69A650 显示 + 69B740/69BD90 输入 + 541190/5409C0 联动
// ------------------------------------------------------------
// 大白话：数量弹出窗的按钮分发：+6/+7/+8/+9 四枚挂件是数量步进按钮 +1/-1/+10/-10
// （读输入框文本 atol 后改写，夹在 0 与上限 +18 之间，回写 sprintf "%d"）；
// +4 挂件悬停（或输入框 +116 确认标记）→ 541190 执行存取并 CLICK_BUTTON2；
// +5 挂件悬停 → 5409C0 数量确认。69A650=弹出显示。
char /*thiscall*/ sub_541620(int *this)  // 函数: 摊位点击处理：CLICK_BUTTON2 + 69A650 显示 + 69B740/69BD90 输入 + 541190/5409C0 联动
{
  int fld_e2; // ecx
  int fld_e5; // eax
  int fld_e22; // eax
  int dword_79BE342; // ecx
  int fld_e6; // eax
  int fld_e18; // edi
  const char *fld_e3; // eax
  const char *fld_e32; // eax
  int fld_e184; // eax
  int fld_e7; // eax
  const char *fld_e33; // eax
  const char *fld_e34; // eax
  int v14; // eax
  int fld_e8; // eax
  int fld_e182; // edi
  const char *fld_e35; // eax
  const char *fld_e36; // eax
  int fld_e1822; // eax
  int fld_e9; // eax
  const char *fld_e37; // eax
  const char *fld_e38; // eax
  int v23; // eax
  const char *fld_e39; // eax
  int v25; // eax
  int fld_e183; // ecx
  int fld_e4; // eax
  int fld_e310; // eax
  char v29; // cl
  int fld_e42; // eax
  char Buffer[16]; // [esp+4h] [ebp-14h] BYREF
  int dword_796E502; // [esp+14h] [ebp-4h]

  fld_e2 = *(this + 2);  // fld_e2 = this+2
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  LOBYTE(fld_e5) = *(uint8_t *)(fld_e2 + 16);  // fld_e2=this+8 物品 id
  if ( (uint8_t)fld_e5 == 0 )  // 若 (uint8_t)fld_e5 == 0
    return fld_e5;
  sub_69A650(fld_e2);  // 调 sub_69A650
  fld_e22 = *(this + 2);  // fld_e22 = this+2
  dword_79BE342 = dword_79BE34;
  if ( *(uint8_t *)(fld_e22 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e22 + 12) )  // 若 *(uint8_t *)(fld_e22 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    dword_79BE4C = *(uint32_t *)(*(this + 3) + 12);
    dword_79BE54 = dword_79BE4C;
  }
  fld_e6 = *(this + 6);  // fld_e6 = this+6
  if ( *(uint8_t *)(fld_e6 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e6 + 12) )  // 若 *(uint8_t *)(fld_e6 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    fld_e18 = *(this + 18);  // fld_e18 = this+18
    fld_e3 = (const char *)sub_69B740(*(this + 3));
    if ( j__atol(fld_e3) + 1 >= fld_e18 )  // +1 按钮：数量+1，钳到上限
    {
      fld_e184 = fld_e18;  // fld_e18=this+72 快照槽（0x6491A0：*(this+72) …
    }
    else
    {
      fld_e32 = (const char *)sub_69B740(*(this + 3));
      fld_e184 = j__atol(fld_e32) + 1;
    }
    sprintf(Buffer, "%d", fld_e184);  // 字符串 “%d”
    sub_69BD90(*(this + 3), Buffer);  // 调 sub_69BD90
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    dword_79BE342 = dword_79BE34;
  }
  fld_e7 = *(this + 7);  // fld_e7 = this+7
  if ( *(uint8_t *)(fld_e7 + 17) != 0 && dword_79BE342 == *(uint32_t *)(fld_e7 + 12) )  // 若 *(uint8_t *)(fld_e7 + 17) != 0 && dword_79BE342 == *(uint32_t ..
  {
    fld_e33 = (const char *)sub_69B740(*(this + 3));
    if ( j__atol(fld_e33) - 1 <= 0 )  // -1 按钮：数量-1，下限 0
    {
      v14 = 0;
    }
    else
    {
      fld_e34 = (const char *)sub_69B740(*(this + 3));
      v14 = j__atol(fld_e34) - 1;
    }
    sprintf(Buffer, "%d", v14);  // 字符串 “%d”
    sub_69BD90(*(this + 3), Buffer);  // 调 sub_69BD90
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    dword_79BE342 = dword_79BE34;
  }
  fld_e8 = *(this + 8);  // fld_e8 = this+8
  if ( *(uint8_t *)(fld_e8 + 17) != 0 && dword_79BE342 == *(uint32_t *)(fld_e8 + 12) )  // 若 *(uint8_t *)(fld_e8 + 17) != 0 && dword_79BE342 == *(uint32_t ..
  {
    fld_e182 = *(this + 18);  // fld_e182 = this+18
    fld_e35 = (const char *)sub_69B740(*(this + 3));
    if ( j__atol(fld_e35) + 10 >= fld_e182 )  // +10 按钮：数量+10，钳到上限
    {
      fld_e1822 = fld_e182;  // fld_e182=this+72 快照槽（0x6491A0：*(this+72) …
    }
    else
    {
      fld_e36 = (const char *)sub_69B740(*(this + 3));
      fld_e1822 = j__atol(fld_e36) + 10;
    }
    sprintf(Buffer, "%d", fld_e1822);  // 字符串 “%d”
    sub_69BD90(*(this + 3), Buffer);  // 调 sub_69BD90
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    dword_79BE342 = dword_79BE34;
  }
  fld_e9 = *(this + 9);  // fld_e9 = this+9
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE342 == *(uint32_t *)(fld_e9 + 12) )  // 若 *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE342 == *(uint32_t ..
  {
    fld_e37 = (const char *)sub_69B740(*(this + 3));
    if ( j__atol(fld_e37) - 10 <= 0 )  // -10 按钮：数量-10，下限 0
    {
      v23 = 0;
    }
    else
    {
      fld_e38 = (const char *)sub_69B740(*(this + 3));
      v23 = j__atol(fld_e38) - 10;
    }
    sprintf(Buffer, "%d", v23);  // 字符串 “%d”
    sub_69BD90(*(this + 3), Buffer);  // 调 sub_69BD90
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  fld_e39 = (const char *)sub_69B740(*(this + 3));
  v25 = j__atol(fld_e39);  // 调 j__atol
  if ( v25 < 0 )  // 若 v25 < 0
  {
    fld_e183 = 0;
    goto LABEL_32;  // 跳转 LABEL_32
  }
  fld_e183 = *(this + 18);  // fld_e183 = this+18
  if ( v25 > fld_e183 )  // 若 v25 > fld_e183
  {
LABEL_32:
    if ( fld_e183 != v25 )  // 若 fld_e183 != v25
    {
      sprintf(Buffer, "%d", fld_e183);  // 字符串 “%d”
      sub_69BD90(*(this + 3), Buffer);  // 调 sub_69BD90
    }
  }
  fld_e4 = *(this + 4);  // fld_e4 = this+4
  if ( *(uint8_t *)(fld_e4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e4 + 12)  // 若 *(uint8_t *)(fld_e4 + 17) != 0 && dword_79BE34 == *(uint32_t *..
    || (fld_e310 = *(this + 3), v29 = *(uint8_t *)(fld_e310 + 116), *(uint8_t *)(fld_e310 + 116) = 0, v29 != 0) )  // 摊位点击处理：CLICK_BUTTON2 + 69A650 显示 + 69B740/69BD90 输入 + 541190/5409C0 联动
  {
    sub_541190(this);  // 摊位物品操作
  }
  fld_e42 = *(this + 4);  // fld_e42 = this+4
  if ( *(uint8_t *)(fld_e42 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e42 + 12) )  // 若 *(uint8_t *)(fld_e42 + 17) != 0 && dword_79BE34 == *(uint32_t ..
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  fld_e5 = *(this + 5);  // fld_e5 = this+5
  if ( *(uint8_t *)(fld_e5 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e5 + 12) )  // 若 *(uint8_t *)(fld_e5 + 17) != 0 && dword_79BE34 == *(uint32_t *..
    LOBYTE(fld_e5) = sub_5409C0(this);  // 数量确认：CLICK_BUTTON2 音 + 54A200 交易窗联动 + 540960 刷
  return fld_e5;  // fld_e5=this+20 频道页号
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
// 大白话：摆摊窗子窗口槽：清 +4/+5/+9/+6，+8 置 2（默认子页=展示页【推断】）。
int /*thiscall*/ CNRDPrivateStoreWindow__vmt64(uint32_t *this)  // 函数: CNRDPrivateStoreWindow__vmt64 子窗口槽（15 行）
{
  *(this + 4) = 0;  // this+16 = 0
  *(this + 5) = 0;  // this+20 = 0
  *(this + 9) = 0;  // this+36 = 0
  *(this + 8) = 2;  // this+32 = 2
  *(this + 6) = 0;  // this+24 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x541920 CNRDPrivateStoreWindow__vmtC —— CNRDPrivateStoreWindow__vmtC 打开槽（44BBA0=WINDOW_SHOW）
// ------------------------------------------------------------
// 大白话：摆摊窗打开：44BBA0(WINDOW_SHOW) 显示挂件 +2。
char /*thiscall*/ CNRDPrivateStoreWindow__vmtC(uint32_t **this)  // 函数: CNRDPrivateStoreWindow__vmtC 打开槽（44BBA0=WINDOW_SHOW）
{
  sub_44BBA0(*(this + 2), 0, 0);  // 窗口显示切换（WINDOW_SHOW 音效）
  return 1;
}



// ------------------------------------------------------------
// 0x541930 CNRDPrivateStoreWindow__vmt1C —— CNRDPrivateStoreWindow__vmt1C 关闭/刷新槽（13 行）
// ------------------------------------------------------------
// 大白话：摆摊窗悬停查询：+1 挂件可见(+17)且鼠标X(dword_79BE34)命中其+12 才返回真。
bool /*thiscall*/ CNRDPrivateStoreWindow__vmt1C(uint32_t *this)  // 函数: CNRDPrivateStoreWindow__vmt1C 关闭/刷新槽（13 行）
{
  int pOwnerWnd; // eax  | +0x0004 → ★ 宿主/父窗口（0x542650: fld_4 = *(this+4)；vmt10 末尾复位 0）（CNRDPrivateStoreWindow；va=00542650）

  pOwnerWnd = *(this + 1);  // fld_e1 = this+1
  return *(uint8_t *)(pOwnerWnd + 17) != 0 && dword_79BE34 == *(uint32_t *)(pOwnerWnd + 12);  // fld_e1=this+4 pOwnerWnd
}



// ------------------------------------------------------------
// 0x541950 CNRDPrivateStoreWindow__vmt10 —— CNRDPrivateStoreWindow__vmt10 状态切换槽（44ABE0/44E850 + 540960 输入框刷新）
// ------------------------------------------------------------
// 大白话：摆摊窗状态切换：页签值(+626)为 4~7 时 44ABE0 收起；依次解除 19/20/22 号
// 对象登记（dword_9B88D0 非空且 dword_795378==9 时再加 26）；+116 挂件的页签为
// 2/3 时刷新数量输入框(540960)；+4 动作复位 0。
int /*thiscall*/ CNRDPrivateStoreWindow__vmt10(uint32_t *this)  // 函数: CNRDPrivateStoreWindow__vmt10 状态切换槽（44ABE0/44E850 + 540960 输入框刷新）
{
  uint32_t *pHostCtrl; // ecx
  int v3; // eax
  uint32_t *fld_e22; // ecx
  int result; // eax

  pHostCtrl = (uint32_t *)*(this + 2);
  v3 = pHostCtrl[626];
  if ( v3 == 4 || v3 == 5 || v3 == 6 || v3 == 7 )  // 若 v3 == 4 || v3 == 5 || v3 == 6 || v3 == 7
    sub_44ABE0(pHostCtrl, 0);  // 选中索引 setter
  sub_44E850((uint32_t *)*(this + 2), 19);  // 按池号批量回收活动对象
  sub_44E850((uint32_t *)*(this + 2), 20);  // 按池号批量回收活动对象
  sub_44E850((uint32_t *)*(this + 2), 22);  // 按池号批量回收活动对象
  if ( dword_9B88D0 != 0 && dword_795378 == 9 )  // 若 dword_9B88D0 != 0 && dword_795378 == 9
    sub_44E850((uint32_t *)*(this + 2), 26);  // 按池号批量回收活动对象
  fld_e22 = *(uint32_t **)(*(this + 2) + 116);
  result = fld_e22[10];
  if ( result == 2 || result == 3 )  // 若 result == 2 || result == 3
    result = sub_540960(fld_e22);  // 结果 = 数量输入框刷新
  *(this + 4) = 0;  // this+16 = 0
  return result;
}



// ------------------------------------------------------------
// 0x5419E0 CNRDPrivateStoreWindow__vmt6C —— CNRDPrivateStoreWindow__vmt6C 槽（10 行）
// ------------------------------------------------------------
// 大白话：摆摊窗取当前子页号（+8，见 vmt64 默认 2）。
int /*thiscall*/ CNRDPrivateStoreWindow__vmt6C(uint32_t *this)  // 函数: CNRDPrivateStoreWindow__vmt6C 槽（10 行）
{
  return *(this + 8);  // this+8 pHostCtrl
}



// ------------------------------------------------------------
// 0x5419F0 sub_5419F0 —— 摊位动画辅助（429830）
// ------------------------------------------------------------
int /*thiscall*/ sub_5419F0(uint32_t *this, int nArg2)  // 函数: 摊位动画辅助（429830）
{
  int result; // eax

  result = sub_429830((uint32_t *)dword_8F8500, nArg2);  // 结果 = 表按键查找（uint16）
  if ( result != 0 )  // 若 result != 0
  {
    result = *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, nArg2) + 192);  // 结果 = 表按键查找（uint16）
    *(this + 4) = result;  // this+16 = result
  }
  return result;
}



// ------------------------------------------------------------
// 0x541A30 sub_541A30 —— 摊位条目名取串（10 行）
// ------------------------------------------------------------
// 大白话：取当前活动摆摊子窗口指针（解引用单例 dword_9B8038）。
int sub_541A30()  // 摊位条目名取串
{
  return *(uint32_t *)dword_9B8038;
}



// ------------------------------------------------------------
// 0x541A40 sub_541A40 —— 摊位结构初始化（18 行）
// ------------------------------------------------------------
// 大白话：查当前活动子窗口(*dword_9B8038)在 dword_9B8034[3] 窗口数组中的下标
// （0~2），找不到返回 -1。
int sub_541A40()  // 摊位结构初始化
{
  int result; // eax

  result = 0;
  while ( *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * result) )  // 当 *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * .. 循环
  {
    if ( ++result >= 3 )  // 若 ++result >= 3
      return -1;  // 返回 -1（0xFFFFFFFF）
  }
  return result;
}



// ------------------------------------------------------------
// 0x541A60 sub_541A60 —— 摊位子页切换（44AB50 + 44E850 + 44BBA0）
// ------------------------------------------------------------
// 大白话：切换摆摊子页：44AB50(全局窗,0,12) 页签切换；dword_9B8038 ← dword_9B8034[nArg1]
// （nArg1=0/1/2 对应展示/收购/出售【推断】）；byte_9B804C = (nArg1==1)，
// 非 1 时调新子窗 vmt+76 登记；44E850(71) 解除 71 号对象、44BBA0(全局,9,0) 显示 9 号页。
uint8_t /*cdecl*/ sub_541A60(int nArg1)  // 函数: 摊位子页切换（44AB50 + 44E850 + 44BBA0）
{
  byte_9B804C = nArg1 == 1;
  sub_44AB50(dword_8F8528, 0, 12);  // 页签切换
  *(uint32_t *)dword_9B8038 = *(uint32_t *)(dword_9B8034 + 4 * nArg1);
  if ( byte_9B804C != 0 )  // 若 byte_9B804C != 0
    byte_9B804C = 0;
  else
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)dword_9B8038 + 76))(*(uint32_t *)dword_9B8038);  // 调用虚函数槽 +76
  sub_44E850(dword_8F8528, 71);  // 按池号批量回收活动对象
  return sub_44BBA0(dword_8F8528, 9, 0);  // 窗口显示切换（WINDOW_SHOW 音效）
}



// ------------------------------------------------------------
// 0x541AF0 sub_541AF0 —— 摊位辅助（20 行）
// ------------------------------------------------------------
// 大白话：上架空槽探测：在活动子窗(+9→数量+8/数组+12)里找第一个空位下标，
// 14 格全满返回 -1（摆摊最多上架 14 件）。
int /*thiscall*/ sub_541AF0(uint32_t *this)  // 函数: 摊位辅助（20 行）
{
  int fld_e9; // ecx
  int result; // eax

  fld_e9 = *(this + 9);  // fld_e9 = this+9
  result = 0;
  while ( result < *(uint32_t *)(fld_e9 + 8) && *(uint32_t *)(*(uint32_t *)(fld_e9 + 12) + 4 * result) != 0 )  // 当 result < *(uint32_t *)(fld_e9 + 8) && *(uint32_t *)(*(uint32_t.. 循环
  {
    if ( ++result >= 14 )  // 若 ++result >= 14
      return -1;  // 返回 -1（0xFFFFFFFF）
  }
  return result;
}



// ------------------------------------------------------------
// 0x541B30 sub_541B30 —— 摊位条目详情（4F2CE0/422E70 取串 + 44E8D0）
// ------------------------------------------------------------
// 大白话：条目详情弹窗：4F2CE0 解析物品、用串表 1338 的格式串 sprintf 详情文本；
// 临时把活动子窗切到 dword_9B8034[1]（展示页）调 vmt+68 登记条目，扫描 14 格
// （两列）统计上架数、为 0 时调 vmt+84 收起；44E8D0 消息 0x1B 弹出文本后恢复原子窗。
int /*cdecl*/ sub_541B30(int nArg1, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数: 摊位条目详情（4F2CE0/422E70 取串 + 44E8D0）
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
  int dword_796E502; // [esp+10Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  memset(Buffer, 0, 255);  // 清零 255 字节块
  v13 = sub_4F2CE0(nArg1);  // 调 sub_4F2CE0
  v6 = sub_422E70(1338);  // 调 sub_422E70
  sprintf(Buffer, v6, v13, nArg3, nArg4, nArg5);  // 调 sprintf 格式化
  v7 = 0;
  while ( *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * v7) )  // 当 *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * .. 循环
  {
    if ( ++v7 >= 3 )  // 若 ++v7 >= 3
    {
      v8 = -1;
      goto LABEL_5;  // 跳转 LABEL_5
    }
  }
  v8 = v7;
LABEL_5:
  *(uint32_t *)dword_9B8038 = *(uint32_t *)(dword_9B8034 + 4);
  (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)dword_9B8038 + 68))(*(uint32_t *)dword_9B8038, nArg2, nArg6);  // 调用虚函数槽 +68
  v9 = *(uint32_t *)(dword_9B8040 + 8);  // v9 = dword_9B8040+8
  v10 = 0;
  for ( i = 0; i < 14; i += 2 )  // 循环：i = 0; i < 14; i += 2
  {
    if ( i < v9 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * i) != 0 )  // 若 i < v9 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 *..
      ++v10;  // 自增v10
    if ( i + 1 < v9 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * i + 4) != 0 )  // 虚调用 vt+4
      ++v10;  // 自增v10
  }
  if ( v10 == 0 )  // 若 v10 == 0
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)dword_9B8038 + 84))(*(uint32_t *)dword_9B8038);  // 调用虚函数槽 +84
  sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);  // 对象池借出（按池号取可用对象）
  result = dword_9B8038;
  *(uint32_t *)dword_9B8038 = *(uint32_t *)(dword_9B8034 + 4 * v8);
  return result;
}



// ------------------------------------------------------------
// 0x541C60 sub_541C60 —— 摊位登记提交（522300/4F2D40/484F40 + 47CD00 音效）
// ------------------------------------------------------------
// 大白话：上架条目本地登记：522300 生成条目对象；4F2D40 判类型 2 且数量(虚表+172)
// <=7 时选 dword_8F8534 为目标列表（否则 dword_8F852C）；槽位有效则放入
// （虚表+60 同类合并→虚表+48 改数量，合并不上走日志 off_77F3FC），无效槽走 484F40；
// 最后按条目音效名(虚表+56)播 432EA0、ArgList>=9 时全局窗 +14 控件 +56 写分页号
// (ArgList-9)/32【推断】，47CD00 播收尾音。
unsigned int /*cdecl*/ sub_541C60(int ArgList, void *pArg2, int nArg3, int nArg4, int nArg5)  // 摊位登记提交（522300/4F2D40/484F40 + 47CD00 音效）
{
  int pObj; // eax
  int pObj2; // esi
  int v7; // eax
  uint32_t *dword_8F852C2; // ecx
  int *v9; // edi
  char v10; // al
  int v11; // edx
  int v12; // eax
  void *v13; // eax
  bool v15; // [esp+Fh] [ebp-1h]

  pObj = sub_522300(pArg2, nArg3, nArg4, 0, nArg5, 1);  // 调 sub_522300
  pObj2 = pObj;
  v15 = false;
  if ( pObj != 0 )  // 若 pObj != 0
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);  // 调用虚函数槽 +16
    if ( sub_4F2D40(*(uint32_t *)(v7 + 4)) == 2 )  // 若 sub_4F2D40(*(uint32_t *)(v7 + 4)) == 2
      v15 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 172))(pObj2) <= 7;  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
  }
  dword_8F852C2 = dword_8F852C;  // 全局 dword_8F852C = 角色/物品栏管理器
  if ( v15 )  // 若 v15
    dword_8F852C2 = dword_8F8534;  // dword_8F8534（技能槽装载对象）
  if ( ArgList < dword_8F852C2[2] && (v9 = *(int **)(dword_8F852C2[3] + 4 * ArgList)) != nullptr )  // 若 ArgList < dword_8F852C2[2] && (v9 = *(int **)(dword_8F852C2[3]..
  {
    v10 = (*(int (/*thiscall*/ **)(int *, void *))(*v9 + 60))(v9, pArg2);  // 结果 = 虚调用 vt+60
    v11 = *v9;
    if ( v10 != 0 )  // 若 v10 != 0
    {
      (*(void (/*thiscall*/ **)(int *, int))(v11 + 48))(v9, nArg3);  // 调用虚函数槽 +48
    }
    else
    {
      v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 16))(v9);  // 调用虚函数槽 +16
      off_77F3FC((char *)&byte_7246D4, ArgList, *(uint32_t *)(v12 + 4));  // off_77F3FC（引擎日志输出函数）
    }
  }
  else
  {
    sub_484F40(ArgList, pObj2, 1);  // 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
  }
  if ( pObj2 != 0 )  // 若 pObj2 != 0
  {
    v13 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 56))(pObj2);  // 虚槽+56 CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认动作：+84 标志时 4
    sub_432EA0(v13, -1, 0, 0);  // 音效播放包装（非空判定）
    if ( !v15 && *((uint32_t *)dword_8F8528 + 27) == 0 && ArgList >= 9 )  // 全局 dword_8F8528 = 消息/弹窗管理器
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 14) + 56) = (ArgList - 9) / 32;  // 全局 dword_8F8528 = 消息/弹窗管理器
  }
  return sub_47CD00((uint32_t *)dword_8F8540);  // 调 sub_47CD00
}



// ------------------------------------------------------------
// 0x541D80 sub_541D80 —— 摊位物品上架（45E510/45E550 查询 + 423200/423290/423380 参数串 + 44ABF0）
// ------------------------------------------------------------
// 大白话：申请开设摆摊：把鼠标点(pt)经 45E510/45E550 映射成背包槽列/行，角色对象
// （dword_8F7C08，虚表+136/+140）校验通过后发送 88=CREATE_PRIVATE_STORE（docs/24）：
// 1 字节 用户对象+100、1 字节 +104 字符串首字符（无则 0xFF）、2 字节槽列、2 字节槽行；
// 随后以同样四参在本地 42FBB0 登记摊位【推断】并 44ABF0 刷新窗口。
int sub_541D80()  // 摊位物品上架（45E510/45E550 查询 + 423200/423290/423380
{
  int pObj; // esi
  uint32_t *pInv; // edi
  int result; // eax
  uint32_t *pStore; // esi
  char *pszName; // eax
  int pUser; // ecx
  int *psz2; // eax
  int nameChar; // eax
  int appendVal; // [esp+8h] [ebp-10h] BYREF
  int slotY; // [esp+Ch] [ebp-Ch] BYREF
  int slotX; // [esp+10h] [ebp-8h] BYREF
  char v11[4]; // [esp+14h] [ebp-4h] BYREF

  pObj = dword_8F7C08;  // dword_8F7C08（副玩家/观战者）
  pInv = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C08 + 80))(dword_8F7C08);  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  slotX = sub_45E510(pInv, pt.x, 1);  // 结果 = 与 ·sub_45E490 反向（层坐标 → 屏幕 y）
  slotY = sub_45E550(pInv, pt.y, 0, 1);  // 结果 = 与 ·sub_45E4D0 配对的回换算（nArg2 + nArg3 - 120）
  if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 136))(pObj, slotX, slotY, 0) != 0  // 虚槽+136 CNProvocationDollAura__vmt88 槽（10 行）
    || (uint8_t)(result = (*(int (/*thiscall*/ **)(int, int *, int *, int, int, int, uint32_t, int))(*(uint32_t *)pObj + 140))(  // 虚槽+140 CNProvocationDollAura__vmt8C 槽（17 行）
                          pObj,
                          &slotX,
                          &slotY,
                          slotX,
                          slotY,
                          100,
                          0,
                          1)) != 0 )
  {
    pStore = (uint32_t *)dword_8F7C08;  // dword_8F7C08（副玩家/观战者）
    sub_423200(dword_8F7B08, 88);  // 【发送网络包API】88=ENUM_CMDPACKET_CREATE_PRIVATE_STORE 创建摆摊
    v11[0] = *(uint8_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 100);  // 全局 dword_8F7A24 = 登录/选区管理器
    sub_423290(dword_8F7B08, (int)v11, 1);  // 调 sub_423290
    pszName = *(char **)(*(uint32_t *)(dword_8F7A24 + 20) + 104);  // 全局 dword_8F7A24 = 登录/选区管理器
    if ( pszName != nullptr )  // 若 pszName 非空
      v11[0] = *pszName;  // v11[0] 写入 *pszName
    else
      v11[0] = -1;
    sub_423290(dword_8F7B08, (int)v11, 1);  // 调 sub_423290
    appendVal = slotX;
    sub_423290(dword_8F7B08, (int)&appendVal, 2);  // 调 sub_423290
    appendVal = slotY;
    sub_423290(dword_8F7B08, (int)&appendVal, 2);  // 调 sub_423290
    sub_423380(dword_8F7B08);  // 发包提交：Commit()
    pUser = *(uint32_t *)(dword_8F7A24 + 20);  // 全局 dword_8F7A24 = 登录/选区管理器
    psz2 = *(int **)(pUser + 104);
    if ( psz2 != nullptr )  // 若 psz2 非空
      nameChar = *psz2;
    else
      nameChar = -1;
    sub_42FBB0(pStore, *(uint32_t *)(pUser + 100), nameChar, slotX, slotY);  // 个人商店准备
    return sub_44ABF0(dword_8F8528);  // 选中索引置 17
  }
  return result;
}



// ------------------------------------------------------------
// 0x541ED0 sub_541ED0 —— 上架参数写入 2（423200/423290/423380 + 44ABF0）
// ------------------------------------------------------------
// 大白话：发送 86=ENUM_CMDPACKET_ENTER_PRIVATE_STORE 进入他人摆摊（docs/24），
// 包体 4 字节 = 摊主对象编号 nArg1【推断】，随后 44ABF0 刷新窗口。
int /*cdecl*/ sub_541ED0(int nArg1)  // 函数: 上架参数写入 2（423200/423290/423380 + 44ABF0）
{
  sub_423200(dword_8F7B08, 86);  // 【发送网络包API】86=ENUM_CMDPACKET_ENTER_PRIVATE_STORE 进入摆摊
  sub_423290(dword_8F7B08, (int)&nArg1, 4);  // 调 sub_423290
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  return sub_44ABF0(dword_8F8528);  // 选中索引置 17
}



// ------------------------------------------------------------
// 0x541F10 sub_541F10 —— 上架参数写入 3（423200/423380 + 44ABF0）
// ------------------------------------------------------------
// 大白话：发送 91=ENUM_CMDPACKET_MOVE_TO_GATE 走向传送门（回城确认，docs/24），
// 空包体；被回城确认窗 CNRDMoveToHomeConfirmWindow__vmt14(window_party.cpp 0x6394D0)
// 关闭时调用——确认回城/走向传送门。
int sub_541F10()  // 上架参数写入 3（423200/423380 + 44ABF0）
{
  sub_423200(dword_8F7B08, 91);  // 【发送网络包API】91=ENUM_CMDPACKET_MOVE_TO_GATE 走向传送门(回城确认)
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  return sub_44ABF0(dword_8F8528);  // 选中索引置 17
}



// ------------------------------------------------------------
// 0x541F40 CNRDPrivateStoreWindow__vmt50 —— CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
// ------------------------------------------------------------
// 大白话：发送 85=ENUM_CMDPACKET_BUY_PRIVATE_STORE_ITEM 买摆摊物品（docs/24）：
// 包体 2 字节槽位 nArg1 + 4 字节价格/数量 nArg2【推断】，随后 44ABF0 刷新窗口。
int /*stdcall*/ CNRDPrivateStoreWindow__vmt50(int nArg1, int nArg2)  // 函数: CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
{
  sub_423200(dword_8F7B08, 85);  // 【发送网络包API】85=ENUM_CMDPACKET_BUY_PRIVATE_STORE_ITEM 买摆摊物品
  sub_423290(dword_8F7B08, (int)&nArg1, 2);  // 调 sub_423290
  nArg1 = nArg2;
  sub_423290(dword_8F7B08, (int)&nArg1, 4);  // 调 sub_423290
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  return sub_44ABF0(dword_8F8528);  // 选中索引置 17
}



// ------------------------------------------------------------
// 0x541FA0 CNRDPrivateStoreWindow__vmt54 —— CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
// ------------------------------------------------------------
// 大白话：发送 89=ENUM_CMDPACKET_REMOVE_PRIVATE_STORE 拆除摆摊（docs/24），空包体。
int CNRDPrivateStoreWindow__vmt54()  // CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
{
  sub_423200(dword_8F7B08, 89);  // 【发送网络包API】89=ENUM_CMDPACKET_REMOVE_PRIVATE_STORE 拆除摆摊
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  return sub_44ABF0(dword_8F8528);  // 选中索引置 17
}



// ------------------------------------------------------------
// 0x541FD0 CNRDPrivateStoreWindow__vmt58 —— CNRDPrivateStoreWindow__vmt58 槽（16 行）
// ------------------------------------------------------------
// 大白话：发送 87=ENUM_CMDPACKET_EXIT_PRIVATE_STORE 退出摆摊（docs/24），空包体；
// 提交成功(423380 返回 1)才刷新窗口。
int CNRDPrivateStoreWindow__vmt58()  // CNRDPrivateStoreWindow__vmt58 槽（16 行）
{
  int result; // eax

  sub_423200(dword_8F7B08, 87);  // 【发送网络包API】87=ENUM_CMDPACKET_EXIT_PRIVATE_STORE 退出摆摊
  result = sub_423380(dword_8F7B08);  // 结果 = 发包提交：Commit()
  if ( result == 1 )  // 若 result == 1
    return sub_44ABF0(dword_8F8528);  // 选中索引置 17
  return result;
}



// ------------------------------------------------------------
// 0x542000 sub_542000 —— 摊位条目查询（422E70 取串 + 44E8D0，46 行）
// ------------------------------------------------------------
// 大白话：摆摊错误码弹提示：按服务器错误码 nArg1 查串表取文案
// （53→1325、52→1326、17→1327、22→1328、10→1329、4→1330、1→1331、55→1342、
// 21→1355），再 44E8D0 消息 0x1B 弹出（0x1B=弹消息框【推断】）。
int /*cdecl*/ sub_542000(int nArg1)  // 函数: 摊位条目查询（422E70 取串 + 44E8D0，46 行）
{
  int result; // eax
  char *v2; // eax

  result = nArg1;
  switch ( nArg1 )  // 分支：按 nArg1 分派
  {
    case 53:  // case 53
      v2 = sub_422E70(1325);  // 调 sub_422E70
      break;
    case 52:  // case 52
      v2 = sub_422E70(1326);  // 调 sub_422E70
      break;
    case 17:  // case 17
      v2 = sub_422E70(1327);  // 调 sub_422E70
      break;
    case 22:  // case 22
      v2 = sub_422E70(1328);  // 调 sub_422E70
      break;
    case 10:  // case 10
      v2 = sub_422E70(1329);  // 调 sub_422E70
      break;
    case 4:  // case 4
      v2 = sub_422E70(1330);  // 调 sub_422E70
      break;
    case 1:  // case 1
      v2 = sub_422E70(1331);  // 调 sub_422E70
      break;
    case 55:  // case 55
      v2 = sub_422E70(1342);  // 调 sub_422E70
      break;
    case 21:  // case 21
      v2 = sub_422E70(1355);  // 调 sub_422E70
      break;
    default:
      return result;
  }
  return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);  // 对象池借出（按池号取可用对象）
}



// ------------------------------------------------------------
// 0x5420A0 sub_5420A0 —— 摊位条目查询 2（+43BEE0 图标 + 44ABE0）
// ------------------------------------------------------------
// 大白话：另一组摆摊错误码：53→1321、20→1322 弹消息(0x1B)并写日志；51→1323 时
// 43BEE0 以色值 -6567706 打公告横幅并 44ABE0(16) 收起面板；57→1351、58→1352 弹消息。
int /*cdecl*/ sub_5420A0(int nArg1)  // 函数: 摊位条目查询 2（+43BEE0 图标 + 44ABE0）
{
  int result; // eax
  char *v2; // eax
  char *v3; // eax
  uint32_t *v4; // esi
  char *v5; // eax
  char *v6; // eax

  result = nArg1;
  switch ( nArg1 )  // 分支：按 nArg1 分派
  {
    case 53:  // case 53
      v2 = sub_422E70(1321);  // 调 sub_422E70
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);  // 对象池借出（按池号取可用对象）
      return off_77F3FC((char *)&byte_724748);  // off_77F3FC（引擎日志输出函数）
    case 20:  // case 20
      v3 = sub_422E70(1322);  // 调 sub_422E70
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);  // 对象池借出（按池号取可用对象）
      return off_77F3FC((char *)&byte_724728);  // off_77F3FC（引擎日志输出函数）
    case 51:  // case 51
      v4 = *((uint32_t **)dword_8F8528 + 7);  // 全局 dword_8F8528 = 消息/弹窗管理器
      v5 = sub_422E70(1323);  // 调 sub_422E70
      sub_43BEE0(v4, (int)v5, -6567706, 0, -1);  // 调 sub_43BEE0
      sub_44ABE0(dword_8F8528, 16);  // 选中索引 setter
      return off_77F3FC((char *)&byte_724708);  // off_77F3FC（引擎日志输出函数）
    case 57:  // case 57
      v6 = sub_422E70(1351);  // 调 sub_422E70
      break;
    case 58:  // case 58
      v6 = sub_422E70(1352);  // 调 sub_422E70
      break;
    default:
      return result;
  }
  return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v6, 0);  // 对象池借出（按池号取可用对象）
}



// ------------------------------------------------------------
// 0x542190 sub_542190 —— 摊位条目查询 3（+44AB50 页切换）
// ------------------------------------------------------------
// 大白话：摆摊错误码 53/54 弹消息(0x1B, 串 1325/1326)；错误码 22 时先
// 44AB50(全局窗,1,12) 切子页 1，再以消息 0x40 弹串 1324（0x40=确认框【推断】）。
int /*cdecl*/ sub_542190(int nArg1)  // 函数: 摊位条目查询 3（+44AB50 页切换）
{
  int result; // eax
  char *v2; // eax
  char *v3; // eax
  char *v4; // eax

  result = nArg1;
  switch ( nArg1 )  // 分支：按 nArg1 分派
  {
    case 53:  // case 53
      v2 = sub_422E70(1325);  // 调 sub_422E70
      return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);  // 对象池借出（按池号取可用对象）
    case 54:  // case 54
      v3 = sub_422E70(1326);  // 调 sub_422E70
      return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);  // 对象池借出（按池号取可用对象）
    case 22:  // case 22
      sub_44AB50(dword_8F8528, 1, 12);  // 页签切换
      v4 = sub_422E70(1324);  // 调 sub_422E70
      return sub_44E8D0((char *)dword_8F8528, (void *)0x40, (int)v4, 0);  // 对象池借出（按池号取可用对象）
    default:
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x542220 sub_542220 —— 摊位条目查询 4（28 行）
// ------------------------------------------------------------
// 大白话：摆摊错误码 53→1325、52→1326、17→1332 弹消息(0x1B)。
int /*cdecl*/ sub_542220(int nArg1)  // 函数: 摊位条目查询 4（28 行）
{
  int result; // eax
  char *v2; // eax

  result = nArg1;
  switch ( nArg1 )  // 分支：按 nArg1 分派
  {
    case 53:  // case 53
      v2 = sub_422E70(1325);  // 调 sub_422E70
      break;
    case 52:  // case 52
      v2 = sub_422E70(1326);  // 调 sub_422E70
      break;
    case 17:  // case 17
      v2 = sub_422E70(1332);  // 调 sub_422E70
      break;
    default:
      return result;
  }
  return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);  // 对象池借出（按池号取可用对象）
}



// ------------------------------------------------------------
// 0x542270 sub_542270 —— 输入框联动（69B740/69BD90）
// ------------------------------------------------------------
int /*thiscall*/ sub_542270(int *this)  // 函数: 输入框联动（69B740/69BD90）
{
  int fld_e15; // ecx
  const char *psz; // edi
  int result; // eax
  char v5; // [esp+0h] [ebp-4h]

  if ( sub_69B740(*(this + 15)) != 0 )  // 若 sub_69B740(*(this + 15)) != 0
  {
    fld_e15 = *(this + 15);  // fld_e15 = this+15
    if ( *(uint32_t *)(fld_e15 + 192) != 0 && *(uint32_t *)(fld_e15 + 188) != 0 )  // 若 *(uint32_t *)(fld_e15 + 192) != 0 && *(uint32_t *)(fld_e15 + 1..
    {
      if ( *(uint32_t *)(fld_e15 + 192) != 0 )  // 若 *(uint32_t *)(fld_e15 + 192) != 0
        psz = *(const char **)(fld_e15 + 188);  // fld_e15=this+60 fade 值
      else
        psz = nullptr;  // psz = nullptr 空指针
      if ( strcmp(psz, (const char *)sub_69B740(fld_e15)) == 0 )  // 若 strcmp(psz, (const char *)sub_69B740(fld_e15)) == 0
        sub_69BD90(*(this + 15), (char *)szPassword, v5);  // 调 sub_69BD90
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
int /*thiscall*/ sub_542310(uint32_t *this)  // 函数: 22 行小辅助
{
  int fld_e2; // eax
  int result; // eax

  fld_e2 = *(uint32_t *)(*(this + 2) + 28);
  if ( *(uint8_t *)(fld_e2 + 256) == 0 )  // 若 *(uint8_t *)(fld_e2 + 256) == 0
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(fld_e2 + 124) + 12);
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
// 大白话：展示子窗（Display）状态清零：+10..+15 各字段复位（上架编辑状态）。
int /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt64(uint32_t *this)  // 函数: CNRDPrivateStoreWindow_Display__vmt64 槽（16 行）
{
  *(this + 14) = 0;  // this+56 = 0
  *(this + 13) = 0;  // 写 this+52 = 0（0x543190 装配槽）
  *(this + 10) = 0;  // this+40 = 0
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 15) = 0;  // this+60 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x542380 CNRDPrivateStoreWindow_Display__vmtC —— CNRDPrivateStoreWindow_Display__vmtC 打开槽（44BBA0 + 69BCC0/402AE0 展示）
// ------------------------------------------------------------
// 大白话：展示子窗打开：44BBA0 显示挂件 +8；把店铺名输入框(+60)设为串表 1334 的
// 默认文案并同步到全局输入焦点(dword_79BE4C/54)。
char /*thiscall*/ CNRDPrivateStoreWindow_Display__vmtC(int this)  // 函数: CNRDPrivateStoreWindow_Display__vmtC 打开槽（44BBA0 + 69BCC0/402AE0 展示）
{
  char *v2; // ebx

  sub_44BBA0(*(uint32_t **)(this + 8), 0, 0);  // 窗口显示切换（WINDOW_SHOW 音效）
  v2 = sub_422E70(1334);  // 调 sub_422E70
  sub_69BCC0(*(uint32_t *)(this + 60));  // 调 sub_69BCC0
  sub_402AE0(v2);  // 字符串包赋值 C 串（按需扩容后 qmemcpy + 尾 NUL + +4 置有效）
  dword_79BE4C = *(uint32_t *)(*(uint32_t *)(this + 60) + 12);  // this+60 pShopNameEdit
  dword_79BE54 = dword_79BE4C;
  return 1;
}



// ------------------------------------------------------------
// 0x5423D0 CNRDPrivateStoreWindow_Display__vmt10 —— CNRDPrivateStoreWindow_Display__vmt10 状态切换（540960 输入框 + 544A10）
// ------------------------------------------------------------
// 大白话：展示子窗状态切换：先走基类 vmt10；若不是收起状态(byte_9B804C==0)
// 则把 dword_9B8040 上架列表里每件非空物品经本窗虚表+72 重新登记，最后虚表+84 收尾。
char /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt10(uint32_t *this)  // 函数: CNRDPrivateStoreWindow_Display__vmt10 状态切换（540960 输入框 + 544A10）
{
  int pStoreWnd; // eax  | +0x0008 → ★ 摆摊主窗体（CNRDPrivateStoreWindow_Display；va=00542730）
  uint32_t *fld_e22; // ecx
  char result; // al
  int dword_9B80402; // eax
  int i; // esi

  CNRDPrivateStoreWindow__vmt10(this);  // 调 CNRDPrivateStoreWindow__vmt10 状态切换槽
  pStoreWnd = *(uint32_t *)(*(this + 2) + 28);
  if ( *(uint8_t *)(pStoreWnd + 256) == 0 )  // 若 *(uint8_t *)(fld_e2 + 256) == 0
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(pStoreWnd + 124) + 12);
    dword_79BE54 = dword_79BE4C;
  }
  CNCommandChecker__vmt40(0, 1);
  *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(*(this + 2) + 28) + 136) + 17) = 1;
  fld_e22 = *(uint32_t **)(*(this + 2) + 116);
  if ( fld_e22[10] == 1 )  // 若 fld_e22[10] == 1
    sub_540960(fld_e22);  // 数量输入框刷新
  sub_544A10(dword_9B8050);  // 输入框取值
  result = byte_9B804C;
  if ( byte_9B804C == 0 )  // 若 byte_9B804C == 0
  {
    dword_9B80402 = dword_9B8040;
    for ( i = 0; i < 14; ++i )  // 循环：i = 0; i < 14; ++i
    {
      if ( i < *(uint32_t *)(dword_9B80402 + 8) && *(uint32_t *)(*(uint32_t *)(dword_9B80402 + 12) + 4 * i) != 0 )  // 若 i < *(uint32_t *)(dword_9B80402 + 8) && *(uint32_t *)(*(uint32..
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 72))(this, i);  // 虚调用 vt+72
        dword_9B80402 = dword_9B8040;
      }
    }
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);  // 虚调用 vt+84
  }
  return result;
}



// ------------------------------------------------------------
// 0x542490 sub_542490 —— 展示子窗口辅助（16 行）
// ------------------------------------------------------------
// 大白话：沿 +8 链向上找最后一个 +21 标记为 0 的节点（子窗口链尾探测【推断】）。
int /*cdecl*/ sub_542490(int pArg1)  // 函数: 展示子窗口辅助（16 行）
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 21) == 0; i = *(uint32_t *)(i + 8) )  // 循环：i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 21) == 0; i =
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x5424B0 sub_5424B0 —— 展示子窗口公共更新（25 行——基类/Buy/Sell 共用）
// ------------------------------------------------------------
// 大白话：摆摊 7 列格子的鼠标悬停探测：列数 = 虚表+108 返回值×7，格子 32x32，
// 起点 (61,291)（格宽 32、每行 7 格），返回鼠标所在格下标，不在格内返回 -1。
int /*thiscall*/ sub_5424B0(void *this)  // 函数: 展示子窗口公共更新（25 行——基类/Buy/Sell 共用）
{
  int pThis_6C; // edi
  int v2; // ecx

  pThis_6C = 7 * (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 108))(this);  // this+108 第 1 组·宿主属性 +886 增量
  v2 = 0;
  if ( pThis_6C <= 0 )  // 若 pThis_6C <= 0
    return -1;  // 返回 -1（0xFFFFFFFF）
  while ( pt.x < 32 * (v2 % 7) + 61
       || pt.x >= 32 * (v2 % 7) + 89
       || pt.y < 32 * (v2 / 7) + 291
       || pt.y >= 32 * (v2 / 7) + 319 )  // 展示子窗口公共更新（25 行——基类/Buy/Sell 共用）
  {
    if ( ++v2 >= pThis_6C )  // 若 ++v2 >= pThis_6C
      return -1;  // 返回 -1（0xFFFFFFFF）
  }
  return v2;
}



// ------------------------------------------------------------
// 0x542520 CNRDPrivateStoreWindow_Display__vmt1C —— CNRDPrivateStoreWindow_Display__vmt1C 刷新槽（5424B0 + 432F00）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt1C(uint32_t *this)  // 函数: CNRDPrivateStoreWindow_Display__vmt1C 刷新槽（5424B0 + 432F00）
{
  int pOwnerWnd; // eax  | +0x0004 → ★ 宿主/父窗口（0x542650: fld_4 = *(this+4)；vmt10 末尾复位 0）（CNRDPrivateStoreWindow·基类；va=00542650）
  int v3; // ecx
  int v4; // eax
  uint32_t *v6; // esi
  uint32_t *v7; // eax
  int v8; // ecx
  int pObj; // ecx
  int v10; // eax

  pOwnerWnd = *(this + 1);  // fld_e1 = this+1
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0 || dword_79BE34 != *(uint32_t *)(pOwnerWnd + 12) )  // 若 *(uint8_t *)(fld_e1 + 17) == 0 || dword_79BE34 != *(uint32_t *..
    return 0;
  v3 = *((uint32_t *)dword_8F8528 + 626);  // 全局 dword_8F8528 = 消息/弹窗管理器
  if ( v3 == 15 )  // 若 v3 == 15
  {
    v4 = sub_5424B0(this);  // 结果 = 基类/Buy/Sell 共用
    if ( v4 != -1 && v4 < *(uint32_t *)(dword_9B8040 + 8) && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * v4) != 0 )  // 若 v4 != -1 && v4 < *(uint32_t *)(dword_9B8040 + 8) && *(uint32_t..
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 72))(this, v4);  // 虚调用 vt+72
      return 1;
    }
  }
  else if ( v3 == 2 )  // 否则若 v3 == 2
  {
    v6 = (char *)dword_8F8528 + 2508;  // 全局 dword_8F8528 = 消息/弹窗管理器
    v7 = sub_432F00(0);  // 结果 = 按类型取全局列表对象
    if ( *v6 == 3 )  // 若 *v6 == 3
    {
      v8 = v6[2];
      if ( v8 < v7[2] )  // 若 v8 < v7[2]
      {
        pObj = *(uint32_t *)(v7[3] + 4 * v8);
        if ( pObj != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 4) == v6[1] )  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
        {
          v10 = sub_5424B0(this);  // 结果 = 基类/Buy/Sell 共用
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t))(*this + 64))(this, v6[2], v10, 0);  // 虚调用 vt+64
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
// 大白话：展示子窗撤销上架：鼠标命中的格子(5424B0)里有已登记物品且宿主页签
// (+2504)不是 14/15 时，调 44BC30 把物品退回（参数含物品编号+4、格下标、剩余量+68）。
char /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt14(uint32_t *this)  // 函数: CNRDPrivateStoreWindow_Display__vmt14 关闭槽（5424B0 + 44BC30）
{
  int v2; // edi
  void *pObj; // esi
  int pStoreWnd; // eax  | +0x0008 → ★ 摆摊主窗体（CNRDPrivateStoreWindow_Display；va=00542730）
  int v5; // eax
  int v7; // [esp-8h] [ebp-14h]

  v2 = sub_5424B0(this);  // 结果 = 基类/Buy/Sell 共用
  if ( v2 == -1 )  // 若 v2 == -1
    return 0;
  if ( v2 >= *(uint32_t *)(dword_9B8040 + 8) )  // 若 v2 >= *(uint32_t *)(dword_9B8040 + 8)
    return 0;
  pObj = *(void **)(*(uint32_t *)(dword_9B8040 + 12) + 4 * v2);
  if ( pObj == nullptr )  // 若 pObj 为空
    return 0;
  pStoreWnd = *(uint32_t *)(*(this + 2) + 2504);
  if ( pStoreWnd != 14 && pStoreWnd != 15 )  // 若 fld_e2 != 14 && fld_e2 != 15
  {
    v7 = *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pObj + 16))(pObj) + 68);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
    v5 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pObj + 16))(pObj);  // 调用虚函数槽 +16
    sub_44BC30((uint32_t *)*(this + 2), (void *)2, 10, *(uint32_t *)(v5 + 4), v2, v7, pObj);  // 拾取模式状态 + ICON_PICK/ITEM_PICK 音效
  }
  return 1;
}



// ------------------------------------------------------------
// 0x542650 CNRDPrivateStoreWindow__vmt8 —— CNRDPrivateStoreWindow__vmt8 Update 槽（57 行：5424B0 + 44E8D0/44E850）
// ------------------------------------------------------------
// 大白话：摆摊基窗逐帧 Update：悬停格子里有上架物品时 44E8D0 消息 0x1A 请求物品
// 说明（虚表+48 设 28x28 提示框位置在格子左上角）；页签为 1/2 或未悬停且
// dword_9B88D0 非空、dword_795378==9（处于查看他人摊状态【推断】）时解除 26 号对象。
char /*thiscall*/ CNRDPrivateStoreWindow__vmt8(int this)  // 函数: CNRDPrivateStoreWindow__vmt8 Update 槽（57 行：5424B0 + 44E8D0/44E850）
{
  int pHostCtrl; // eax  | +0x0008 → ★ 宿主控件（CNRDPrivateStoreWindow；va=00542650）
  int pOwnerWnd; // ecx  | +0x0004 → ★ 宿主/父窗口（0x542650: fld_4 = *(this+4)；vmt10 末尾复位 0）（CNRDPrivateStoreWindow；va=00542650）
  int v4; // edi
  int v5; // eax
  int pSellEntryList; // ecx  | +0x0024 → ★ 上架条目挂链（CNRDPrivateStoreWindow；va=00542650）
  int v7; // ecx
  int v8; // edx
  int fld_82; // eax  | +0x0008 → ★ 宿主控件（CNRDPrivateStoreWindow；va=00542650）
  int v10; // edi
  int v11; // ebx

  pHostCtrl = *(uint32_t *)(*(uint32_t *)(this + 8) + 2504);  // this+8 pHostCtrl
  if ( pHostCtrl == 1 )  // 若 fld_8 == 1
    goto LABEL_12;  // 跳转 LABEL_12
  if ( pHostCtrl == 2 )  // 若 fld_8 == 2
    goto LABEL_12;  // 跳转 LABEL_12
  pOwnerWnd = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0 )  // 若 *(uint8_t *)(fld_4 + 17) == 0
    goto LABEL_12;  // 跳转 LABEL_12
  v4 = *(uint32_t *)(pOwnerWnd + 12);  // v4 = fld_4+12
  if ( dword_79BE3C != v4 && dword_79BE34 != v4 && dword_79BE38 != v4 )  // 若 dword_79BE3C != v4 && dword_79BE34 != v4 && dword_79BE38 != v4
    goto LABEL_12;  // 跳转 LABEL_12
  v5 = sub_5424B0((void *)this);  // 结果 = 基类/Buy/Sell 共用
  if ( v5 != -1
    && ((pSellEntryList = *(uint32_t *)(this + 36), v5 >= *(uint32_t *)(pSellEntryList + 8))  // CNRDPrivateStoreWindow__vmt8 Update 槽（57 行：5424B0 + 44E8D0/44E850）
      ? (v7 = 0)
      : (v7 = *(uint32_t *)(*(uint32_t *)(pSellEntryList + 12) + 4 * v5)),
        v8 = 32 * (v5 % 7) + 61,
        fld_82 = 32 * (v5 / 7) + 291,
        v10 = v8,
        v11 = fld_82,
        v7 != 0) )
  {
    if ( dword_9B88D0 != v7 || dword_795378 != 9 )  // 若 dword_9B88D0 != v7 || dword_795378 != 9
    {
      fld_82 = sub_44E8D0(*(char **)(this + 8), (void *)0x1A, v7, 9);  // 结果 = 对象池借出（按池号取可用对象）
      if ( fld_82 != 0 )  // 若 fld_82 != 0
        LOBYTE(fld_82) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)fld_82 + 48))(fld_82, v10, v11, 28, 28);  // 虚槽+48 CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0）
    }
  }
  else
  {
LABEL_12:
    LOBYTE(fld_82) = dword_9B88D0;
    if ( dword_9B88D0 != 0 && dword_795378 == 9 )  // 若 dword_9B88D0 != 0 && dword_795378 == 9
      LOBYTE(fld_82) = sub_44E850(*(uint32_t **)(this + 8), 26);  // 按池号批量回收活动对象
  }
  return fld_82;  // +0x0008 → ★ 宿主控件（CNRDPrivateStoreWindow；va=00542650）
}



// ------------------------------------------------------------
// 0x542730 CNRDPrivateStoreWindow_Display__vmt8 —— CNRDPrivateStoreWindow_Display__vmt8 Update 槽（83 行：542310/542270 + 42FC00/44ABE0）
// ------------------------------------------------------------
// 大白话：展示子窗逐帧 Update：店铺名输入框(+60)持焦点时按 79C0B4 键盘态分派
// 542310/清输入；标题按钮(+28)悬停→542270 联动；登记按钮(+56)悬停：无店名→弹串
// 1334、14 格全空→弹串 1350，否则 42FC00 本地建摊并走虚表+92（发 90 包前的确认【推断】）；
// 收购/出售页按钮(+40/+44)悬停→44ABE0(14)/(15) 切页。
int /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt8(int this)  // 函数: CNRDPrivateStoreWindow_Display__vmt8 Update 槽（83 行：542310/542270 + 42FC00/44ABE0）
{
  int pSellEntryVec; // eax  | +0x001C → ★ 出售条目数组（CNRDPrivateStoreWindow_Display；va=00543190）
  int pRegBtn; // eax  | +0x0038 → ★ 登记（开店）按钮（CNRDPrivateStoreWindow_Display；va=00542730）
  int pShopNameEdit; // eax  | +0x003C → ★ 店铺名输入框（CNRDPrivateStoreWindow_Display；va=00542730）
  int v5; // ecx
  int v6; // edx
  int v7; // edi
  int i; // eax
  char *v9; // eax
  int result; // eax
  int pBuyTabBtn; // eax  | +0x0028 → ★ 收购页按钮（0x542730: 悬停 → 44ABE0(14) 切到收购页；542270 联动）（CNRDPrivateStoreWindow_Display；va=00542730）

  CNRDPrivateStoreWindow__vmt8(this);  // 调 CNRDPrivateStoreWindow__vmt8 Update 槽
  if ( *(uint32_t *)(*(uint32_t *)(this + 60) + 12) == dword_79BE4C )  // 若 *(uint32_t *)(*(uint32_t *)(this + 60) + 12) == dword_79BE4C
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 16) != 0 )  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
    {
      sub_542310((uint32_t *)this);  // 22 行小辅助
    }
    else
    {
      CNCommandChecker__vmt40(0, 0);
      *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 8) + 28) + 136) + 17) = 0;  // this+8 pStoreWnd
    }
  }
  else
  {
    pSellEntryVec = **(uint32_t **)(this + 28);  // this+28 pSellEntryVec
    if ( *(uint8_t *)(pSellEntryVec + 17) != 0 && dword_79BE34 == *(uint32_t *)(pSellEntryVec + 12) )  // 若 *(uint8_t *)(fld_1C + 17) != 0 && dword_79BE34 == *(uint32_t *..
      sub_542270((int *)this);  // 输入框联动（69B740/69BD90）
  }
  pRegBtn = *(uint32_t *)(this + 56);  // fld_38 = this+56
  if ( *(uint8_t *)(pRegBtn + 17) != 0 && dword_79BE34 == *(uint32_t *)(pRegBtn + 12) )  // 若 *(uint8_t *)(fld_38 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    pShopNameEdit = *(uint32_t *)(this + 60);  // fld_3C = this+60
    v5 = pShopNameEdit + 160;  // fld_3C=this+60 pShopNameEdit
    if ( *(uint32_t *)(pShopNameEdit + 192) != 0 )  // 若 *(uint32_t *)(fld_3C + 192) != 0
      v5 = pShopNameEdit + 180;  // fld_3C=this+60 pShopNameEdit
    if ( *(uint32_t *)(v5 + 12) == 0 || *(uint32_t *)(pShopNameEdit + 192) != 0 && *(uint32_t *)(pShopNameEdit + 188) != 0 )  // 若 *(uint32_t *)(v5 + 12) == 0 || *(uint32_t *)(fld_3C + 192) != ..
    {
      v9 = sub_422E70(1334);  // 调 sub_422E70
      return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v9, 0);  // 对象池借出（按池号取可用对象）
    }
    v6 = *(uint32_t *)(dword_9B8040 + 8);  // v6 = dword_9B8040+8
    v7 = 0;
    for ( i = 0; i < 14; i += 2 )  // 循环：i = 0; i < 14; i += 2
    {
      if ( i < v6 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * i) != 0 )  // 若 i < v6 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 *..
        ++v7;  // 自增v7
      if ( i + 1 < v6 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * i + 4) != 0 )  // 虚调用 vt+4
        ++v7;  // 自增v7
    }
    if ( v7 == 0 )  // 若 v7 == 0
    {
      v9 = sub_422E70(1350);  // 调 sub_422E70
      return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v9, 0);  // 对象池借出（按池号取可用对象）
    }
    sub_42FC00((int *)dword_8F7C08, *(void **)(v5 + 8));  // 商店操作转发
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 92))(this);  // 调用虚函数槽 +92
  }
  else
  {
    pBuyTabBtn = *(uint32_t *)(this + 40);  // fld_28 = this+40
    if ( *(uint8_t *)(pBuyTabBtn + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBuyTabBtn + 12) )  // 若 *(uint8_t *)(fld_28 + 17) != 0 && dword_79BE34 == *(uint32_t *..
    {
      return sub_44ABE0(dword_8F8528, 14);  // 选中索引 setter
    }
    else
    {
      result = *(uint32_t *)(this + 44);  // result = this+44
      if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 若 *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *..
        return sub_44ABE0(dword_8F8528, 15);  // 选中索引 setter
    }
  }
  return result;  // result=this+44 pSellTabBtn
}



// ------------------------------------------------------------
// 0x5428D0 CNRDPrivateStoreWindow_Sell__vmt8 —— CNRDPrivateStoreWindow_Sell__vmt8 Update 槽（转发 522C60）
// ------------------------------------------------------------
// 大白话：出售子窗逐帧 Update：+10 按钮悬停时把选中物品(+9→+4)交给 522C60 处理，
// 失败则走虚表+84 收尾。
int /*thiscall*/ CNRDPrivateStoreWindow_Sell__vmt8(int *this)  // 函数: CNRDPrivateStoreWindow_Sell__vmt8 Update 槽（转发 522C60）
{
  int result; // eax

  CNRDPrivateStoreWindow__vmt8((int)this);  // 调 CNRDPrivateStoreWindow__vmt8 Update 槽
  result = *(this + 10);  // 读 result = this+40（出售按钮 A）
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 若 *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    result = sub_522C60(*(uint32_t *)(*(this + 9) + 4));  // 调 sub_522C60
    if ( (uint8_t)result == 0 )  // 若 (uint8_t)result == 0
      return (*(int (/*thiscall*/ **)(int *))(*this + 84))(this);  // 虚调用 vt+84
  }
  return result;  // result=this+40 pSellBtnA
}



// ------------------------------------------------------------
// 0x542910 CNRDPrivateStoreWindow_Buy__vmt8 —— CNRDPrivateStoreWindow_Buy__vmt8 Update 槽（44ABE0）
// ------------------------------------------------------------
// 大白话：收购子窗逐帧 Update：+10 按钮悬停时 44ABE0(4) 切回页签 4。
char /*thiscall*/ CNRDPrivateStoreWindow_Buy__vmt8(uint32_t *this)  // 函数: CNRDPrivateStoreWindow_Buy__vmt8 Update 槽（44ABE0）
{
  int pBuyBtn; // esi  | +0x0028 → 收购按钮（0x5446F0: *(this+40)=sub_43C410(帧 4..6)，位于 (128,192)）（CNRDPrivateStoreWindow_Buy；va=005446F0）
  char result; // al

  CNRDPrivateStoreWindow__vmt8((int)this);  // 调 CNRDPrivateStoreWindow__vmt8 Update 槽
  pBuyBtn = *(this + 10);  // 读 fld_e10 = this+40（收购按钮）
  result = *(uint8_t *)(pBuyBtn + 17);  // result = fld_e10+17
  if ( result != 0 )  // 若 result != 0
  {
    result = dword_79BE34;
    if ( dword_79BE34 == *(uint32_t *)(pBuyBtn + 12) )  // 若 dword_79BE34 == *(uint32_t *)(fld_e10 + 12)
      return sub_44ABE0(dword_8F8528, 4);  // 选中索引 setter
  }
  return result;
}



// ------------------------------------------------------------
// 0x542940 sub_542940 —— 收购/出售子窗口公共辅助（23 行）
// ------------------------------------------------------------
// 大白话：链表递归释放：从 Block 起沿 +0 链逐节点先递归处理 +2 分支再 free，
// 直到节点 +21 标记非 0（哨兵）为止。
char /*stdcall*/ sub_542940(void **Block)  // 函数: 收购/出售子窗口公共辅助（23 行）
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )  // 循环：i = Block; result == 0; Block2 = i
  {
    sub_542940(i[2]);  // 收购/出售子窗口公共辅助
    i = (void **)*i;
    j__free(Block2);  // 调 j__free
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x542980 sub_542980 —— 摊位条目操作（61 行：4F36B0 + 44E8D0）
// ------------------------------------------------------------
// 大白话：收购校验：持有金币(全局对象虚表+44)减 nArg1 后不足时弹"钱不够"提示——
// 串 952 前缀 + 4F36B0 格式化差额 + 串 953 后缀拼进 pBuf，44E8D0 消息 0x1B 弹出，
// 返回 1 表示拦截。
char /*cdecl*/ sub_542980(int nArg1)  // 函数: 摊位条目操作（61 行：4F36B0 + 44E8D0）
{
  char v1; // bl
  int v2; // esi
  const char *p_Block; // eax
  const char *v4; // edx
  unsigned int nLen; // eax
  char *v6; // edi
  char v7; // cl
  char *psz; // ecx
  unsigned int nLen2; // eax
  char *psz2; // esi
  char *v11; // edi
  char v12; // cl
  char v14; // [esp+7h] [ebp-ADh] BYREF
  char pBuf[128]; // [esp+8h] [ebp-ACh] BYREF
  uint8_t v16[4]; // [esp+88h] [ebp-2Ch] BYREF
  void *Block; // [esp+8Ch] [ebp-28h] BYREF
  unsigned int v18; // [esp+A0h] [ebp-14h]
  int dword_796E502; // [esp+A4h] [ebp-10h]
  int v20; // [esp+B0h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v1 = 0;
  v2 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) - nArg1;  // 全局 dword_8F852C = 角色/物品栏管理器
  if ( v2 < 0 )  // 若 v2 < 0
  {
    strcpy(pBuf, sub_422E70(952));  // 调 strcpy 串拷贝
    sub_4F36B0(v16, -v2, 0, 0, 0);  // 调 sub_4F36B0
    p_Block = (const char *)Block;
    v20 = 0;
    if ( v18 < 0x10 )  // 若 v18 < 0x10
      p_Block = (const char *)&Block;
    v4 = p_Block;
    nLen = strlen(p_Block) + 1;  // 调 strlen（求串长）
    v6 = &v14;
    do
      v7 = *++v6;
    while ( v7 != 0 );  // 当 v7 != 0 循环
    qmemcpy(v6, v4, nLen);  // 调 qmemcpy 内联块拷贝
    psz = sub_422E70(953);  // 调 sub_422E70
    nLen2 = strlen(psz) + 1;  // 调 strlen（求串长）
    psz2 = psz;
    v11 = &v14;
    do
      v12 = *++v11;
    while ( v12 != 0 );  // 当 v12 != 0 循环
    qmemcpy(v11, psz2, nLen2);  // 调 qmemcpy 内联块拷贝
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)pBuf, 0);  // 对象池借出（按池号取可用对象）
    v1 = 1;
    if ( v18 >= 0x10 )  // 若 v18 >= 0x10
      j__free(Block);  // 调 j__free
  }
  return v1;
}



// ------------------------------------------------------------
// 0x542AB0 sub_542AB0 —— 摊位数据释放（4BE520）
// ------------------------------------------------------------
// 大白话：4BE520 按(this, pszArg2)查条目，返回其 +16 字段（物品编号/数量【推断】）。
int /*thiscall*/ sub_542AB0(void *this, char pszArg2)  // 函数: 摊位数据释放（4BE520）
{
  void *pThis; // [esp+0h] [ebp-4h] BYREF

  pThis = this;
  return *(uint32_t *)(*(uint32_t *)sub_4BE520(&pThis, &pszArg2) + 16);  // 映射下界查找（lower_bound）
}



// ------------------------------------------------------------
// 0x542AD0 sub_542AD0 —— 摊位页切换（44AB50 + 542940，60 行）
// ------------------------------------------------------------
// 大白话：摆摊页签复位：当前活动子窗(*dword_9B8038)为 dword_9B8034[2] 时弹串 1336；
// 为 dword_9B8034[1] 时清空 dword_9B8044/dword_9B8048 两条挂链清单（542940 释放
// 节点、头结点自指、计数归零）；最后 44AB50(全局窗,1,12) 切回页签 1。
int sub_542AD0()  // 摊位页切换
{
  int v0; // ecx
  int v1; // eax
  int v2; // eax
  char *v3; // eax
  char *pObj; // esi
  uint32_t *dword_9B80442; // edi
  uint32_t *v7; // eax
  int pObj2; // esi
  int dword_9B80482; // edi
  uint32_t *v10; // eax

  v0 = *(uint32_t *)dword_9B8038;  // v0 = dword_9B8038
  v1 = 0;
  while ( v0 != *(uint32_t *)(dword_9B8034 + 4 * v1) )  // 当 v0 != *(uint32_t *)(dword_9B8034 + 4 * v1) 循环
  {
    if ( ++v1 >= 3 )  // 若 ++v1 >= 3
      goto LABEL_4;  // 跳转 LABEL_4
  }
  if ( v1 == 2 )  // 若 v1 == 2
  {
    v3 = sub_422E70(1336);  // 调 sub_422E70
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);  // 对象池借出（按池号取可用对象）
    return sub_44AB50(dword_8F8528, 1, 12);  // 页签切换
  }
LABEL_4:
  v2 = 0;
  while ( v0 != *(uint32_t *)(dword_9B8034 + 4 * v2) )  // 当 v0 != *(uint32_t *)(dword_9B8034 + 4 * v2) 循环
  {
    if ( ++v2 >= 3 )  // 若 ++v2 >= 3
      return sub_44AB50(dword_8F8528, 1, 12);  // 页签切换
  }
  if ( v2 == 1 )  // 若 v2 == 1
  {
    pObj = (char *)dword_9B8044 + 4;
    dword_9B80442 = dword_9B8044;
    sub_542940(*(void ***)(*((uint32_t *)dword_9B8044 + 1) + 4));  // 收购/出售子窗口公共辅助
    *(uint32_t *)(*(uint32_t *)pObj + 4) = *(uint32_t *)pObj;
    v7 = *(uint32_t **)pObj;
    dword_9B80442[2] = 0;
    *v7 = v7;  // *v7 写入 v7
    *(uint32_t *)(*(uint32_t *)pObj + 8) = *(uint32_t *)pObj;
    pObj2 = dword_9B8048 + 4;
    dword_9B80482 = dword_9B8048;
    sub_542940(*(void ***)(*(uint32_t *)(dword_9B8048 + 4) + 4));  // 收购/出售子窗口公共辅助
    *(uint32_t *)(*(uint32_t *)pObj2 + 4) = *(uint32_t *)pObj2;
    v10 = *(uint32_t **)pObj2;
    *(uint32_t *)(dword_9B80482 + 8) = 0;  // dword_9B80482+8 = 0
    *v10 = v10;  // *v10 写入 v10
    *(uint32_t *)(*(uint32_t *)pObj2 + 8) = *(uint32_t *)pObj2;
  }
  return sub_44AB50(dword_8F8528, 1, 12);  // 页签切换
}



// ------------------------------------------------------------
// 0x542BB0 CNRDPrivateStoreWindow__vmt4C —— CNRDPrivateStoreWindow__vmt4C 槽（542940 + 485020）
// ------------------------------------------------------------
// 大白话：清单清空槽：当前活动子窗为 dword_9B8034[0] 时先清 dword_9B8048 挂链，
// 再清本窗 +6 挂的挂链（542940 释放、头自指、计数归零），485020 收尾刷新。
int /*thiscall*/ CNRDPrivateStoreWindow__vmt4C(uint32_t *this)  // 函数: CNRDPrivateStoreWindow__vmt4C 槽（542940 + 485020）
{
  int v2; // eax
  int pObj; // esi
  int dword_9B80482; // edi
  uint32_t *v5; // eax
  int fld_e6; // esi
  uint32_t *v7; // eax

  v2 = 0;
  while ( *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * v2) )  // 当 *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * .. 循环
  {
    if ( ++v2 >= 3 )  // 若 ++v2 >= 3
      goto LABEL_7;  // 跳转 LABEL_7
  }
  if ( v2 == 0 )  // 若 v2 == 0
  {
    pObj = dword_9B8048 + 4;
    dword_9B80482 = dword_9B8048;
    sub_542940(*(void ***)(*(uint32_t *)(dword_9B8048 + 4) + 4));  // 收购/出售子窗口公共辅助
    *(uint32_t *)(*(uint32_t *)pObj + 4) = *(uint32_t *)pObj;
    v5 = *(uint32_t **)pObj;
    *(uint32_t *)(dword_9B80482 + 8) = 0;  // dword_9B80482+8 = 0
    *v5 = v5;  // *v5 写入 v5
    *(uint32_t *)(*(uint32_t *)pObj + 8) = *(uint32_t *)pObj;
  }
LABEL_7:
  fld_e6 = *(this + 6);  // fld_e6 = this+6
  sub_542940(*(void ***)(*(uint32_t *)(fld_e6 + 4) + 4));  // 收购/出售子窗口公共辅助
  *(uint32_t *)(*(uint32_t *)(fld_e6 + 4) + 4) = *(uint32_t *)(fld_e6 + 4);  // fld_e6=this+24 页数上限
  v7 = *(uint32_t **)(fld_e6 + 4);  // fld_e6=this+24 页数上限
  *(uint32_t *)(fld_e6 + 8) = 0;  // fld_e6+8 = 0
  *v7 = v7;  // *v7 写入 v7
  *(uint32_t *)(*(uint32_t *)(fld_e6 + 4) + 8) = *(uint32_t *)(fld_e6 + 4);  // fld_e6=this+24 页数上限
  return sub_485020(*(this + 9));  // 技能槽容器整体释放（模式 0/4 跳过前 3 槽）
}



// ------------------------------------------------------------
// 0x542C40 CNRDPrivateStoreWindow__vmt60 —— CNRDPrivateStoreWindow__vmt60 槽（4BE520 + 44E8D0）
// ------------------------------------------------------------
// 大白话：条目菜单请求：从挂链(+36→数量+8/数组+12)取第 nArg2 个条目，4BE520 解出
// 物品后 44E8D0 消息 0x41 带菜单参数(v7：&nArg2/&pszArg3)与其 +16 字段弹出菜单。
int /*thiscall*/ CNRDPrivateStoreWindow__vmt60(int this, int nArg2, char pszArg3)  // 函数: CNRDPrivateStoreWindow__vmt60 槽（4BE520 + 44E8D0）
{
  int pSellEntryList; // eax  | +0x0024 → ★ 上架条目挂链（CNRDPrivateStoreWindow；va=00542650）
  int pObj; // eax
  uint32_t v7[2]; // [esp+4h] [ebp-10h] BYREF
  uint8_t v8[4]; // [esp+Ch] [ebp-8h] BYREF
  int v9; // [esp+10h] [ebp-4h] BYREF

  pSellEntryList = *(uint32_t *)(this + 36);  // fld_24 = this+36
  if ( nArg2 >= *(uint32_t *)(pSellEntryList + 8) )  // 若 nArg2 >= *(uint32_t *)(fld_24 + 8)
    v9 = 0;
  else
    v9 = *(uint32_t *)(*(uint32_t *)(pSellEntryList + 12) + 4 * nArg2);  // fld_24=this+36 pSellEntryList
  v7[0] = &nArg2;
  v7[1] = &pszArg3;
  pObj = sub_4BE520(v8, &v9);  // 结果 = 映射下界查找（lower_bound）
  return sub_44E8D0(*(char **)(this + 8), (void *)0x41, (int)v7, *(uint32_t *)(*(uint32_t *)pObj + 16));  // 对象池借出（按池号取可用对象）
}



// ------------------------------------------------------------
// 0x542CA0 CNRDPrivateStoreWindow_Display__vmt40 —— CNRDPrivateStoreWindow_Display__vmt40 确认动作槽（88 行：544AC0 + 540DE0 重建）
// ------------------------------------------------------------
// 大白话：上架格子放物品：源列表(432F00(nArg4))第 nArg2 格的物品经虚表+80 校验、
// 虚表+60 同类判定后挂到上架列表 dword_9B8040 的 nArg3 格（同类可堆叠则按虚表+44
// 数量合并，多件走 540DE0 弹数量窗选择）；格子无效/为空时弹串 422 提示。
int /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt40(char **this, int nArg2, int nArg3, int nArg4)  // 函数: CNRDPrivateStoreWindow_Display__vmt40 确认动作槽（88 行：544AC0 + 540DE0 重建）
{
  uint32_t *v5; // eax
  int nArg22; // ebx
  int v7; // ecx
  int *v8; // edi
  int v9; // esi
  int v10; // eax
  bool v11; // zf
  int result; // eax
  int v13; // esi
  int pObj; // ecx
  int v15; // ebx
  int v16; // ebx
  char *v17; // eax
  uint8_t v18[4]; // [esp+Ch] [ebp-8h] BYREF
  char **pThis; // [esp+10h] [ebp-4h]

  pThis = this;
  v5 = sub_432F00(nArg4);  // 结果 = 按类型取全局列表对象
  nArg22 = nArg2;
  if ( nArg2 < v5[2]
    && (v7 = v5[3], (v8 = *(int **)(v7 + 4 * nArg2)) != nullptr)  // CNRDPrivateStoreWindow_Display__vmt40 确认动作槽（88 行：544AC0 + 540DE0 重建）
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*v8 + 80))(*(uint32_t *)(v7 + 4 * nArg2)) != 0 )  // 虚调用 vt+80
  {
    v9 = *v8;
    v10 = (*(int (/*thiscall*/ **)(int *))(*v8 + 16))(v8);  // 结果 = 虚调用 vt+16
    v11 = (*(uint8_t (/*thiscall*/ **)(int *, uint32_t))(v9 + 60))(v8, *(uint32_t *)(v10 + 4)) == 0;
    result = dword_9B8040;
    if ( v11 )  // 若 v11
    {
LABEL_11:
      if ( nArg3 >= *(uint32_t *)(result + 8) || *(uint32_t *)(*(uint32_t *)(result + 12) + 4 * nArg3) == 0 )  // 若 nArg3 >= *(uint32_t *)(result + 8) || *(uint32_t *)(*(uint32_t..
        return sub_544AC0(nArg22, nArg3, nArg4);  // 展示列表刷新
    }
    else
    {
      v13 = 0;
      while ( 1 )  // 当 1 循环
      {
        if ( v13 < *(uint32_t *)(result + 8) )  // 若 v13 < *(uint32_t *)(result + 8)
        {
          pObj = *(uint32_t *)(*(uint32_t *)(result + 12) + 4 * v13);
          if ( pObj != 0 )  // 若 pObj != 0
          {
            v15 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 4);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
            v11 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*v8 + 16))(v8) + 4) == v15;  // 结果 = 虚调用 vt+16
            result = dword_9B8040;
            if ( v11 )  // 若 v11
              break;
          }
        }
        if ( ++v13 >= 14 )  // 若 ++v13 >= 14
        {
          nArg22 = nArg2;
          goto LABEL_11;  // 跳转 LABEL_11
        }
      }
      if ( v13 >= *(uint32_t *)(dword_9B8040 + 8) )  // 若 v13 >= *(uint32_t *)(dword_9B8040 + 8)
        nArg3 = 0;
      else
        nArg3 = *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * v13);
      v16 = *(uint32_t *)(*(uint32_t *)sub_4BE520(v18, &nArg3) + 16);  // 结果 = 映射下界查找（lower_bound）
      if ( (unsigned int)(*(int (/*thiscall*/ **)(int *))(*v8 + 44))(v8) <= 1 )  // 虚调用 vt+44
        return (*(int (/*thiscall*/ **)(uint32_t, int, int, int, int, int))(**(uint32_t **)dword_9B8038 + 60))(
                 *(uint32_t *)dword_9B8038,
                 nArg2,
                 v13,
                 nArg4,
                 v16,
                 1);
      else
        return sub_540DE0(*((int **)pThis[2] + 29), 1, nArg4, nArg2, 5, v13, v16, 0);  // 摊位列表构建
    }
  }
  else
  {
    v17 = sub_422E70(422);  // 调 sub_422E70
    return sub_44E8D0(*(this + 2), (void *)0x1B, (int)v17, 0);  // 对象池借出（按池号取可用对象）
  }
  return result;
}



// ------------------------------------------------------------
// 0x542E10 CNRDPrivateStoreWindow_Display__vmt5C —— CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：423200/423290/423380 参数 + 69B740 输入）
// ------------------------------------------------------------
// 大白话：提交摆摊展示内容——发送 90=ENUM_CMDPACKET_COMPLETE_DISPLAY 完成展示
// （docs/24）：4 字节店名长度 + 店名（输入框 +60 经 69B740 取文本）+ 1 字节上架
// 件数（14 格两列扫 dword_9B8040），再逐件附 2 字节槽位、4 字节物品编号(+16)、
// 1 字节 0、2 字节(+16 截断)、4 字节售价（虚表+60/+44/+188 计算）；尾段日志
// "money : %d"，44ABF0 刷新窗口。
int /*fastcall*/ CNRDPrivateStoreWindow_Display__vmt5C(int pArg1)  // CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：423200/423290/423380 参数 + 69B740 输入）
{
  int pSock2; // edi
  const char *psz; // eax
  int pszTitle; // esi
  char *pszTitle2; // eax
  int v6; // edx
  int nShown; // ebx
  int i; // eax
  int pList; // eax
  int j; // edi
  int pEntryObj; // esi
  int pEntryVt; // ebx
  int pEntryInfo; // eax
  int nPrice; // esi
  int pDatum1; // ebx
  int pDatum2; // eax
  int nMoney; // eax
  uint8_t tmpD[4]; // [esp+Ch] [ebp-20h] BYREF
  uint8_t tmpC[4]; // [esp+10h] [ebp-1Ch] BYREF
  uint8_t tmpB[4]; // [esp+14h] [ebp-18h] BYREF
  uint8_t tmpA[4]; // [esp+18h] [ebp-14h] BYREF
  uint32_t pktWord[2]; // [esp+1Ch] [ebp-10h] BYREF
  int nLen; // [esp+24h] [ebp-8h] BYREF
  uint8_t pktByte[4]; // [esp+28h] [ebp-4h] BYREF

  pktWord[1] = pArg1;
  sub_423200(dword_8F7B08, 90);  // 【发送网络包API】90=ENUM_CMDPACKET_COMPLETE_DISPLAY 完成展示
  pSock2 = dword_8F7B08;  // 全局 dword_8F7B08 = 全局 socket 对象
  psz = (const char *)sub_69B740(*(uint32_t *)(pArg1 + 60));
  pszTitle = (int)psz;
  if ( psz != nullptr )  // 若 psz 非空
  {
    nLen = strlen(psz);  // 调 _strlen 取字符串长度
    sub_423290(pSock2, (int)&nLen, 4);  // 调 sub_423290
    sub_423290(pSock2, pszTitle, nLen);  // 调 sub_423290
  }
  pszTitle2 = (char *)sub_69B740(*(uint32_t *)(pArg1 + 60));
  off_77F3FC(pszTitle2);  // off_77F3FC（引擎日志输出函数）
  v6 = *(uint32_t *)(dword_9B8040 + 8);  // v6 = dword_9B8040+8
  nShown = 0;
  for ( i = 0; i < 14; i += 2 )  // 循环：i = 0; i < 14; i += 2
  {
    if ( i < v6 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * i) != 0 )  // 若 i < v6 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 *..
      ++nShown;  // 自增nShown
    if ( i + 1 < v6 && *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * i + 4) != 0 )  // 虚调用 vt+4
      ++nShown;  // 自增nShown
  }
  pktByte[0] = nShown;
  sub_423290(dword_8F7B08, (int)pktByte, 1);  // 调 sub_423290
  off_77F3FC("%d", nShown);  // 字符串 “%d”
  pList = dword_9B8040;
  for ( j = 0; j < 14; ++j )  // 循环：j = 0; j < 14; ++j
  {
    if ( j < *(uint32_t *)(pList + 8) )  // 若 j < *(uint32_t *)(pList + 8)
    {
      nLen = *(uint32_t *)(*(uint32_t *)(pList + 12) + 4 * j);
      pEntryObj = nLen;
      if ( nLen != 0 )  // 若 nLen != 0
      {
        pktWord[0] = j;
        sub_423290(dword_8F7B08, (int)pktWord, 2);  // 调 sub_423290
        pktWord[0] = *(uint32_t *)(*(uint32_t *)sub_4BE520(tmpA, &nLen) + 16);  // 结果 = 映射下界查找（lower_bound）
        sub_423290(dword_8F7B08, (int)pktWord, 4);  // 调 sub_423290
        pktByte[0] = 0;
        sub_423290(dword_8F7B08, (int)pktByte, 1);  // 调 sub_423290
        pktWord[0] = *(uint16_t *)(*(uint32_t *)sub_4BE520(tmpB, &nLen) + 16);  // 结果 = 映射下界查找（lower_bound）
        sub_423290(dword_8F7B08, (int)pktWord, 2);  // 调 sub_423290
        pEntryVt = *(uint32_t *)pEntryObj;  // pEntryVt = pEntryObj
        pEntryInfo = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pEntryObj + 16))(pEntryObj);  // 调用虚函数槽 +16
        if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(pEntryVt + 60))(pEntryObj, *(uint32_t *)(pEntryInfo + 4)) != 0 )
        {
          nPrice = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pEntryObj + 44))(pEntryObj);  // 调用虚函数槽 +44
        }
        else if ( (**(int (/*thiscall*/ ***)(int))pEntryObj)(pEntryObj) == 2 )
        {
          nPrice = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pEntryObj + 188))(pEntryObj);  // 虚槽+188 动画对象 z 倾斜转状态码
        }
        else
        {
          nPrice = 0;
        }
        pktWord[0] = nPrice;
        sub_423290(dword_8F7B08, (int)pktWord, 4);  // 调 sub_423290
        pDatum1 = sub_4BE520(tmpC, &nLen);  // 结果 = 映射下界查找（lower_bound）
        pDatum2 = sub_4BE520(tmpD, &nLen);  // 结果 = 映射下界查找（lower_bound）
        off_77F3FC("%d, %d, %d, %d", j, *(uint32_t *)(*(uint32_t *)pDatum2 + 16), *(uint32_t *)(*(uint32_t *)pDatum1 + 16), nPrice);  // 字符串 “%d, %d, %d, %d”
        pList = dword_9B8040;
      }
    }
  }
  nMoney = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));  // 全局 dword_8F852C = 角色/物品栏管理器
  off_77F3FC("money : %d", nMoney);  // 字符串 “money : %d”
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  return sub_44ABF0(dword_8F8528);  // 选中索引置 17
}



// ------------------------------------------------------------
// 0x543060 CNRDPrivateStoreWindow_Buy__vmt1C —— CNRDPrivateStoreWindow_Buy__vmt1C 刷新槽（46 行：522C60/542980/540DE0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPrivateStoreWindow_Buy__vmt1C(uint32_t *this)  // 函数: CNRDPrivateStoreWindow_Buy__vmt1C 刷新槽（46 行：522C60/542980/540DE0）
{
  int pOwnerWnd; // eax  | +0x0004 → ★ 宿主/父窗口（0x542650: fld_4 = *(this+4)；vmt10 末尾复位 0）（CNRDPrivateStoreWindow·基类；va=00542650）
  int fld_e2; // eax  | +0x0008 → ★ 宿主控件（CNRDPrivateStoreWindow·基类；va=00542650）
  int v5; // edi
  int pBuyListItem; // eax  | +0x0024 → 收购列表件（0x5446F0: *(this+36)=sub_4354D0(5,14)）（CNRDPrivateStoreWindow_Buy；va=005443F0）
  int pObj3; // ebx
  int v8; // eax
  int pObj; // eax
  uint8_t v10[4]; // [esp+4h] [ebp-8h] BYREF
  int pObj2; // [esp+8h] [ebp-4h] BYREF

  pOwnerWnd = *(this + 1);  // fld_e1 = this+1
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0 || dword_79BE34 != *(uint32_t *)(pOwnerWnd + 12) )  // 若 *(uint8_t *)(fld_e1 + 17) == 0 || dword_79BE34 != *(uint32_t *..
    return 0;
  fld_e2 = *(uint32_t *)(*(this + 2) + 2504);
  if ( fld_e2 != 4 && fld_e2 != 0 )  // 若 fld_e2 != 4 && fld_e2 != 0
    return 0;
  v5 = sub_5424B0(this);  // 结果 = 基类/Buy/Sell 共用
  if ( v5 == -1 )  // 若 v5 == -1
    return 0;
  pBuyListItem = *(this + 9);  // 读 fld_e9 = this+36（收购列表件）
  if ( v5 >= *(uint32_t *)(pBuyListItem + 8) )  // 若 v5 >= *(uint32_t *)(fld_e9 + 8)
    return 0;
  pObj2 = *(uint32_t *)(*(uint32_t *)(pBuyListItem + 12) + 4 * v5);  // fld_e9=this+36 pBuyListItem
  pObj3 = pObj2;
  if ( pObj2 == 0 )  // 若 pObj2 == 0
    return 0;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2);  // 调用虚函数槽 +16
  if ( (uint8_t)sub_522C60(*(uint32_t *)(v8 + 56)) != 0 )  // 若 (uint8_t)sub_522C60(*(uint32_t *)(v8 + 56)) != 0
    return 0;
  pObj = sub_4BE520(v10, &pObj2);  // 结果 = 映射下界查找（lower_bound）
  if ( sub_542980(*(uint32_t *)(*(uint32_t *)pObj + 16)) != 0 )  // 摊位条目操作
    return 0;
  if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 44))(pObj3) <= 1 )  // 虚槽+44 IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 + 69A5F0/69A8
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 96))(this, v5, 1);  // 虚调用 vt+96
  else
    sub_540DE0(*(int **)(*(this + 2) + 116), 2, 5, v5, 7, 0, 0, 0);  // 摊位列表构建
  return 1;
}



// ------------------------------------------------------------
// 0x543150 CNRDPrivateStoreWindow_Buy__vmt10 —— CNRDPrivateStoreWindow_Buy__vmt10 状态切换槽（转发 542940）
// ------------------------------------------------------------
// 大白话：收购子窗状态切换：走基类 vmt10 后清空本窗 +6 挂链（542940 释放、
// 头自指、计数归零），再走虚表+88 收尾。
int /*thiscall*/ CNRDPrivateStoreWindow_Buy__vmt10(uint32_t *this)  // 函数: CNRDPrivateStoreWindow_Buy__vmt10 状态切换槽（转发 542940）
{
  int pBuyListVec; // esi  | +0x0018 → 收购清单向量（0x5446F0: *(this+24)=sub_433AC0 建链；+0/+4/+8 三端点）（CNRDPrivateStoreWindow_Buy；va=005446F0）
  uint32_t *v3; // eax

  CNRDPrivateStoreWindow__vmt10(this);  // 调 CNRDPrivateStoreWindow__vmt10 状态切换槽
  pBuyListVec = *(this + 6);  // 读 fld_e6 = this+24（收购清单向量）
  sub_542940(*(void ***)(*(uint32_t *)(pBuyListVec + 4) + 4));  // 收购/出售子窗口公共辅助
  *(uint32_t *)(*(uint32_t *)(pBuyListVec + 4) + 4) = *(uint32_t *)(pBuyListVec + 4);  // fld_e6=this+24 pBuyListVec
  v3 = *(uint32_t **)(pBuyListVec + 4);  // fld_e6=this+24 pBuyListVec
  *(uint32_t *)(pBuyListVec + 8) = 0;  // fld_e6+8 = 0
  *v3 = v3;  // *v3 写入 v3
  *(uint32_t *)(*(uint32_t *)(pBuyListVec + 4) + 8) = *(uint32_t *)(pBuyListVec + 4);  // fld_e6=this+24 pBuyListVec
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);  // 虚调用 vt+88
}



// ------------------------------------------------------------
// 0x543190 CNRDPrivateStoreWindow_Display__vmt68 —— CNRDPrivateStoreWindow_Display__vmt68 页绘制（114 行：43C250/69A5F0/43C410/43C060 + 69BCC0/402AE0）
// ------------------------------------------------------------
// 大白话：展示页装配：以城镇对象(+20→+204)为图基址建三块面板(43C250 图 2/4/6)
// 定位 (105,59)/(101,189)/(58,224)；上架按钮(43C410 图 20-23 于 64,230)、商店名
// 按钮(24-27 于 150,230，+17 置隐藏)、切页按钮(12-15 于 107,192、16-19 于 149,192)；
// 店名输入框(43C060 39x140 于 110,66)填默认文案串 1334；dword_9B8034 已有值时
// 日志 "Another private shop created!"，随后登记单例并把 +36/+24 接上
// 上架列表 dword_9B8040 与挂链 dword_9B8044。
int /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt68(int this)  // CNRDPrivateStoreWindow_Display__vmt68 页绘制（114 行：43C250/69A5F0/43C410/43C060 + 69BCC0/402AE0）
{
  uint32_t *pOwnerWnd; // ecx
  int v3; // ebx
  uint8_t *pMem; // eax
  uint8_t *v5; // eax
  uint8_t *pMem2; // eax
  uint8_t *v7; // eax
  uint8_t *pMem3; // eax
  uint8_t *v9; // eax
  uint32_t *pMem4; // eax
  uint32_t *v11; // eax
  uint32_t *pMem5; // eax
  uint32_t *v13; // eax
  uint32_t *pMem6; // eax
  uint32_t *v15; // eax
  uint32_t *pMem7; // eax
  uint32_t *v17; // eax
  void *pMem8; // eax
  int v19; // eax
  char *v20; // ebx
  int result; // eax
  int v22; // [esp+10h] [ebp-14h]
  int v23; // [esp+14h] [ebp-10h]

  pOwnerWnd = *(uint32_t **)(this + 4);  // this+4 宿主对象
  v22 = pOwnerWnd[5];  // fld_4=this+4 宿主对象
  v23 = pOwnerWnd[6];  // fld_4=this+4 宿主对象
  sub_69A5F0(pOwnerWnd, 0, 0);  // 调 sub_69A5F0
  v3 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 204);
  pMem = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v5 = sub_43C250(pMem, v3, 2);  // 结果 = nengine::CNFrame 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  **(uint32_t **)(this + 28) = v5;  // this+28 pSellEntryVec
  pMem2 = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v7 = sub_43C250(pMem2, v3, 4);  // 结果 = nengine::CNFrame 构造
  else
    v7 = nullptr;  // v7 = nullptr 空指针
  *(uint32_t *)(*(uint32_t *)(this + 28) + 4) = v7;  // this+28 pSellEntryVec
  pMem3 = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    v9 = sub_43C250(pMem3, v3, 6);  // 结果 = nengine::CNFrame 构造
  else
    v9 = nullptr;  // v9 = nullptr 空指针
  *(uint32_t *)(*(uint32_t *)(this + 28) + 8) = v9;  // this+28 pSellEntryVec
  sub_69A5F0(**(uint32_t ***)(this + 28), 105, 59);  // 调 sub_69A5F0
  sub_69A5F0(*(uint32_t **)(*(uint32_t *)(this + 28) + 4), 101, 189);  // 调 sub_69A5F0
  sub_69A5F0(*(uint32_t **)(*(uint32_t *)(this + 28) + 8), 58, 224);  // 调 sub_69A5F0
  sub_69A840(**(uint32_t **)(this + 28));  // 调 sub_69A840
  sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 4));  // 调 sub_69A840
  sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 8));  // 调 sub_69A840
  pMem4 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    v11 = sub_43C410(pMem4, v3, 20, 21, 22, 23, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v11 = nullptr;  // v11 = nullptr 空指针
  *(uint32_t *)(this + 56) = v11;  // this+56 = v11
  sub_69A5F0(v11, 64, 230);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 56));  // 调 sub_69A840
  pMem5 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem5 != nullptr )  // 若 pMem5 非空
    v13 = sub_43C410(pMem5, v3, 24, 25, 26, 27, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v13 = nullptr;  // v13 = nullptr 空指针
  *(uint32_t *)(this + 52) = v13;  // 写 this+52 = v13（0x543190 装配槽）
  sub_69A5F0(v13, 150, 230);  // 调 sub_69A5F0
  *(uint8_t *)(*(uint32_t *)(this + 52) + 17) = 0;  // this+52 pAssistCtrl
  sub_69A840(*(uint32_t *)(this + 52));  // 调 sub_69A840
  pMem6 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem6 != nullptr )  // 若 pMem6 非空
    v15 = sub_43C410(pMem6, v3, 12, 13, 14, 15, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v15 = nullptr;  // v15 = nullptr 空指针
  *(uint32_t *)(this + 40) = v15;  // this+40 = v15
  sub_69A5F0(v15, 107, 192);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 40));  // 调 sub_69A840
  pMem7 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem7 != nullptr )  // 若 pMem7 非空
    v17 = sub_43C410(pMem7, v3, 16, 17, 18, 19, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v17 = nullptr;  // v17 = nullptr 空指针
  *(uint32_t *)(this + 44) = v17;  // this+44 = v17
  sub_69A5F0(v17, 149, 192);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 44));  // 调 sub_69A840
  pMem8 = operator new(0xE4u);  // 堆分配 228 字节对象
  if ( pMem8 != nullptr )  // 若 pMem8 非空
    v19 = sub_43C060((int)pMem8, 39, 140);  // 结果 = nengine::CNEdit 构造
  else
    v19 = 0;
  *(uint32_t *)(this + 60) = v19;  // this+60 = v19
  dword_9D3BD8 = dword_99FCCC;
  sub_69A5F0(*(uint32_t **)(this + 60), 110, 66);  // 调 sub_69A5F0
  v20 = sub_422E70(1334);  // 调 sub_422E70
  sub_69BCC0(*(uint32_t *)(this + 60));  // 调 sub_69BCC0
  sub_402AE0(v20);  // 字符串包赋值 C 串（按需扩容后 qmemcpy + 尾 NUL + +4 置有效）
  sub_69A840(*(uint32_t *)(this + 60));  // 调 sub_69A840
  sub_69A5F0(*(uint32_t **)(this + 4), v22, v23);  // 调 sub_69A5F0
  if ( *(uint32_t *)dword_9B8034 != 0 )  // 若 *(uint32_t *)dword_9B8034 != 0
    off_77F3FC("Another private shop created!");  // 字符串 “Another private shop created!”
  result = dword_9B8034;
  *(uint32_t *)dword_9B8034 = this;
  *(uint32_t *)(this + 36) = dword_9B8040;  // this+36 = dword_9B8040
  *(uint32_t *)(this + 24) = dword_9B8044;  // this+24 = dword_9B8044
  return result;
}



// ------------------------------------------------------------
// 0x5434F0 CNRDPrivateStoreWindow_Sell__vmt68 —— CNRDPrivateStoreWindow_Sell__vmt68 页绘制（80 行：43C250/69A5F0/69A840/43C410）
// ------------------------------------------------------------
// 大白话：出售页装配：与展示页同构（43C250 图 2/3/6 + 43C410 按钮），差异是
// 第二面板用图 3 且首面板 +16 置隐藏。
int /*thiscall*/ CNRDPrivateStoreWindow_Sell__vmt68(int this)  // 函数: CNRDPrivateStoreWindow_Sell__vmt68 页绘制（80 行：43C250/69A5F0/69A840/43C410）
{
  uint32_t *pOwnerWnd; // ecx
  int v3; // edi
  uint8_t *pMem; // eax
  uint8_t *v5; // eax
  uint8_t *pMem2; // eax
  uint8_t *v7; // eax
  uint8_t *pMem3; // eax
  uint8_t *v9; // eax
  uint32_t *pMem4; // eax
  uint32_t *v11; // eax
  uint32_t *pMem5; // eax
  uint32_t *v13; // eax
  int result; // eax
  int v15; // [esp+Ch] [ebp-14h]
  int v16; // [esp+10h] [ebp-10h]

  pOwnerWnd = *(uint32_t **)(this + 4);  // this+4 宿主对象
  v15 = pOwnerWnd[5];  // fld_4=this+4 宿主对象
  v16 = pOwnerWnd[6];  // fld_4=this+4 宿主对象
  sub_69A5F0(pOwnerWnd, 0, 0);  // 调 sub_69A5F0
  v3 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 204);
  pMem = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v5 = sub_43C250(pMem, v3, 2);  // 结果 = nengine::CNFrame 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  **(uint32_t **)(this + 28) = v5;  // this+28 pPanelVec
  pMem2 = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v7 = sub_43C250(pMem2, v3, 3);  // 结果 = nengine::CNFrame 构造
  else
    v7 = nullptr;  // v7 = nullptr 空指针
  *(uint32_t *)(*(uint32_t *)(this + 28) + 4) = v7;  // this+28 pPanelVec
  pMem3 = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    v9 = sub_43C250(pMem3, v3, 6);  // 结果 = nengine::CNFrame 构造
  else
    v9 = nullptr;  // v9 = nullptr 空指针
  *(uint32_t *)(*(uint32_t *)(this + 28) + 8) = v9;  // this+28 pPanelVec
  sub_69A5F0(**(uint32_t ***)(this + 28), 105, 59);  // 调 sub_69A5F0
  sub_69A5F0(*(uint32_t **)(*(uint32_t *)(this + 28) + 4), 101, 189);  // 调 sub_69A5F0
  sub_69A5F0(*(uint32_t **)(*(uint32_t *)(this + 28) + 8), 58, 224);  // 调 sub_69A5F0
  *(uint8_t *)(**(uint32_t **)(this + 28) + 16) = 0;  // this+28 pPanelVec
  sub_69A840(**(uint32_t **)(this + 28));  // 调 sub_69A840
  sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 4));  // 调 sub_69A840
  sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 8));  // 调 sub_69A840
  pMem4 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    v11 = sub_43C410(pMem4, v3, 20, 21, 22, 23, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v11 = nullptr;  // v11 = nullptr 空指针
  *(uint32_t *)(this + 44) = v11;  // 写 this+44 = v11（出售按钮 B）
  sub_69A5F0(v11, 64, 230);  // 调 sub_69A5F0
  *(uint8_t *)(*(uint32_t *)(this + 44) + 17) = 0;  // this+44 pSellBtnB
  sub_69A840(*(uint32_t *)(this + 44));  // 调 sub_69A840
  pMem5 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem5 != nullptr )  // 若 pMem5 非空
    v13 = sub_43C410(pMem5, v3, 24, 25, 26, 27, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v13 = nullptr;  // v13 = nullptr 空指针
  *(uint32_t *)(this + 40) = v13;  // 写 this+40 = v13（出售按钮 A）
  sub_69A5F0(v13, 150, 230);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 40));  // 调 sub_69A840
  sub_69A5F0(*(uint32_t **)(this + 4), v15, v16);  // 调 sub_69A5F0
  if ( *(uint32_t *)(dword_9B8034 + 4) != 0 )  // 若 *(uint32_t *)(dword_9B8034 + 4) != 0
    off_77F3FC("Another private shop created!");  // 字符串 “Another private shop created!”
  *(uint32_t *)(dword_9B8034 + 4) = this;  // dword_9B8034+4 = this
  result = dword_9B8040;
  *(uint32_t *)(this + 36) = dword_9B8040;  // 写 this+36 = dword_9B8040（摆摊状态）
  *(uint32_t *)(this + 24) = dword_9B8044;  // 写 this+24 = dword_9B8044（出售清单 id）
  return result;
}



// ------------------------------------------------------------
// 0x543740 sub_543740 —— 摊位标题/描述文本（4015C0/401740 + 5648C0/433130/4296E0，113 行）
// ------------------------------------------------------------
// 大白话：把摆摊条目聚合成描述文本：内部用 std::map/set 索引（越界走
// "map/set<T> too long"/"invalid map/set<T> iterator" 崩溃路径），逐条目拼
// "Lv." 等前缀，超长以 "..." 截断，供确认框展示。
int */*thiscall*/ sub_543740(int **this, int *pDwArg2, char pszArg3, int *pDwArg4, int nArg5)  // 摊位标题/描述文本
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

  if ( (unsigned int)*(this + 2) >= 0x1FFFFFFE )  // 若 (unsigned int)*(this + 2) >= 0x1FFFFFFE
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v20 = 0;
    sub_401740(v17);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_5648C0(*(this + 1), pDwArg4, *(this + 1), nArg5, 0);  // 结果 = 商店文本
  fld_e12 = *(this + 1);  // fld_e12 = this+1
  fld_e15 = fld_e1;
  *(this + 2) = (int *)((char *)*(this + 2) + 1);  // this+8 = (int *)((char *)*(this + 2) + 1)
  if ( pDwArg4 == fld_e12 )  // 若 pDwArg4 == fld_e12
  {
    fld_e12[1] = fld_e1;
    **(this + 1) = fld_e1;
    (*(this + 1))[2] = fld_e1;
  }
  else if ( pszArg3 != 0 )  // 否则若 pszArg3 != 0
  {
    *pDwArg4 = fld_e1;  // *pDwArg4 写入 fld_e1
    fld_e13 = *(this + 1);  // fld_e13 = this+1
    if ( pDwArg4 == (int *)*fld_e13 )  // 若 pDwArg4 == (int *)*fld_e13
      *fld_e13 = fld_e1;  // *fld_e13 写入 fld_e1
  }
  else
  {
    pDwArg4[2] = fld_e1;
    fld_e14 = (int)*(this + 1);
    if ( pDwArg4 == *(int **)(fld_e14 + 8) )  // 若 pDwArg4 == *(int **)(fld_e14 + 8)
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // fld_e14+8 = fld_e1
  }
  v10 = (int *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 20) == 0 )  // 若 *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 20) == 0
  {
    while ( 1 )  // 当 1 循环
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )  // 若 *v10 == *v13
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 20) != 0 )  // 若 *(uint8_t *)(v14 + 20) != 0
        {
          if ( fld_e16 == v12[2] )  // 若 fld_e16 == v12[2]
          {
            fld_e16 = *v10;
            sub_433130(this, *v10);  // 红黑树左旋（节点 0x18 版）
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(this, *(uint32_t **)(*(uint32_t *)(fld_e16 + 4) + 4));  // STL 内联红黑树节点摘除重连
          goto LABEL_21;  // 跳转 LABEL_21
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )  // 否则若 *(uint8_t *)(v14 + 20) != 0
      {
        if ( fld_e16 == *v12 )  // 若 fld_e16 == *v12
        {
          fld_e16 = *v10;
          sub_4296E0(this, (uint32_t *)*v10);  // STL 内联红黑树节点摘除重连
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(this, *(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // 红黑树左旋（节点 0x18 版）
        goto LABEL_21;  // 跳转 LABEL_21
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;  // v14+20 = 1
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;  // 虚调用 vt+4
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) != 0 )  // 若 *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) != 0
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)((*(this + 1))[1] + 20) = 1;
  *pDwArg2 = fld_e1;  // *pDwArg2 写入 fld_e1
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x5438F0 sub_5438F0 —— 摊位登记文本构建（218 行：41C5E0 + 52E300/542490/433130/4296E0）
// ------------------------------------------------------------
// 大白话：确认框第二段文本构建：遍历挂链清单（542490 找链尾）把每件条目写成
// 一行明细，供上架确认弹窗展示。
int ***/*thiscall*/ sub_5438F0(uint32_t *this, int ***uArg2, int **pDwArg3)  // 摊位登记文本构建
{
  int **pDwArg32; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *pThis2; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *pThis3; // ecx
  uint32_t *v16; // eax
  int v17; // eax
  void **pExceptionObject; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v20[20]; // [esp+34h] [ebp-34h] BYREF
  int v21; // [esp+48h] [ebp-20h]
  int v22; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v26; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 21) != 0 )  // 若 *((uint8_t *)pDwArg3 + 21) != 0
  {
    v22 = 15;
    v21 = 0;
    v20[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v26 = 0;
    sub_401740(v20);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
    pExceptionObject = &std::out_of_range::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C5E0(&pDwArg3);  // 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
  if ( *((uint8_t *)*pDwArg32 + 21) != 0 )  // 若 *((uint8_t *)*pDwArg32 + 21) != 0
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 21) == 0 )  // 若 *((uint8_t *)v4 + 21) == 0
      v4[1] = (int)v6;  // v4[1] 写入 (int)v6
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )  // 若 *(int ***)(v8 + 4) == pDwArg32
    {
      *(uint32_t *)(v8 + 4) = v4;  // v8+4 = v4
    }
    else if ( (int **)*v6 == pDwArg32 )  // 否则若 (int **)*v6 == pDwArg32
    {
      *v6 = (int)v4;  // *v6 写入 (int)v4
    }
    else
    {
      v6[2] = (int)v4;  // v6[2] 写入 (int)v4
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )  // 若 *(int ***)pThis2[1] == pDwArg32
    {
      if ( *((uint8_t *)v4 + 21) != 0 )  // 若 *((uint8_t *)v4 + 21) != 0
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_52E300(v4);  // 调 容器辅助（16L cdecl）
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v23 = v10;
    if ( v11 )  // 若 v11
    {
      if ( *((uint8_t *)v4 + 21) != 0 )  // 若 *((uint8_t *)v4 + 21) != 0
        *(uint32_t *)(v10 + 8) = v6;  // v10+8 = v6
      else
        *(uint32_t *)(v23 + 8) = sub_542490(v4);  // 展示子窗口辅助
    }
    goto LABEL_35;  // 跳转 LABEL_35
  }
  if ( *((uint8_t *)pDwArg32[2] + 21) != 0 )  // 若 *((uint8_t *)pDwArg32[2] + 21) != 0
  {
    v4 = *pDwArg32;
    goto LABEL_8;  // 跳转 LABEL_8
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )  // 若 pDwArg3 == pDwArg32
    goto LABEL_8;  // 跳转 LABEL_8
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;  // *v5 写入 (int)*pDwArg32
  if ( v5 == pDwArg32[2] )  // 若 v5 == pDwArg32[2]
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 21) == 0 )  // 若 *((uint8_t *)v4 + 21) == 0
      v4[1] = (int)v6;  // v4[1] 写入 (int)v6
    *v6 = (int)v4;  // *v6 写入 (int)v4
    v5[2] = (int)pDwArg32[2];  // v5[2] 写入 (int)pDwArg32[2]
    pDwArg32[2][1] = (int)v5;  // pDwArg32[2][1] 写入 (int)v5
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )  // 若 *(int ***)(v12 + 4) == pDwArg32
  {
    *(uint32_t *)(v12 + 4) = v5;  // v12+4 = v5
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )  // 若 *v13 == (int *)pDwArg32
      *v13 = v5;  // *v13 写入 v5
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];  // v5[1] 写入 (int)pDwArg32[1]
  v14 = *((uint8_t *)v5 + 20);
  *((uint8_t *)v5 + 20) = *((uint8_t *)pDwArg32 + 20);
  *((uint8_t *)pDwArg32 + 20) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 20) == 1 )  // 若 *((uint8_t *)Block + 20) == 1
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )  // 若 v4 != *(int **)(pThis[1] + 4)
    {
      do
      {
        if ( *((uint8_t *)v4 + 20) != 1 )  // 若 *((uint8_t *)v4 + 20) != 1
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )  // 若 v4 == (int *)*v6
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 20) == 0 )  // 若 *((uint8_t *)v16 + 20) == 0
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_433130(v6);  // 红黑树左旋（节点 0x18 版）
            v16 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )  // 若 *((uint8_t *)v16 + 21) != 0
            goto LABEL_53;  // 跳转 LABEL_53
          if ( *(uint8_t *)(*v16 + 20) != 1 || *(uint8_t *)(v16[2] + 20) != 1 )  // 若 *(uint8_t *)(*v16 + 20) != 1 || *(uint8_t *)(v16[2] + 20) != 1
          {
            if ( *(uint8_t *)(v16[2] + 20) == 1 )  // 若 *(uint8_t *)(v16[2] + 20) == 1
            {
              *(uint8_t *)(*v16 + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;
              sub_4296E0(v16);  // STL 内联红黑树节点摘除重连
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(v16[2] + 20) = 1;
            sub_433130(v6);  // 红黑树左旋（节点 0x18 版）
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 20) == 0 )  // 若 *((uint8_t *)v16 + 20) == 0
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_4296E0(v6);  // STL 内联红黑树节点摘除重连
            v16 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )  // 若 *((uint8_t *)v16 + 21) != 0
            goto LABEL_53;  // 跳转 LABEL_53
          if ( *(uint8_t *)(v16[2] + 20) != 1 || *(uint8_t *)(*v16 + 20) != 1 )  // 若 *(uint8_t *)(v16[2] + 20) != 1 || *(uint8_t *)(*v16 + 20) != 1
          {
            if ( *(uint8_t *)(*v16 + 20) == 1 )  // 若 *(uint8_t *)(*v16 + 20) == 1
            {
              *(uint8_t *)(v16[2] + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;
              sub_433130(v16);  // 红黑树左旋（节点 0x18 版）
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(*v16 + 20) = 1;
            sub_4296E0(v6);  // STL 内联红黑树节点摘除重连
            break;
          }
        }
        *((uint8_t *)v16 + 20) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );  // 当 !v11 循环
    }
    *((uint8_t *)v4 + 20) = 1;
  }
  j__free(Block);  // 调 j__free
  v17 = pThis[2];
  if ( v17 != 0 )  // 若 v17 != 0
    pThis[2] = v17 - 1;  // pThis[2] 写入 v17 - 1
  *uArg2 = pDwArg3;  // *uArg2 写入 pDwArg3
  return uArg2;
}


// ------------------------------------------------------------
// 0x543BB0 CNRDPrivateStoreWindow__vmt0 —— CNRDPrivateStoreWindow__vmt0 构造（220 行：45E680 物品枚举 + 4BD630/4BD650 + 5515A0 + 5424B0；尾缀登记单例 dword_9B8034）
// ------------------------------------------------------------
// 日志证据："Another private shop created!"——本窗口成为当前摆摊单例。
// 大白话：摆摊窗主构造：枚举背包物品(45E680)建缓存、装配条目行（"Lv." 等）
// 并登记为摆摊单例 dword_9B8034。
char /*userpurge*/ sub_543BB0@<al>(uint32_t *pArg1@<ecx>, int nArg2@<esi>, int pArg3)  // 函数: CNRDPrivateStoreWindow__vmt0 构造（220 行：45E680 物品枚举 + 4BD630/4BD650 + 5515A0 + 5424B0；尾缀登记单例 dword_9B8034）
{
  int v3; // eax
  int pArg32; // ebx
  int pObj4; // ecx
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
  int pObj; // edx
  int v18; // esi
  int v19; // ebx
  uint32_t *v20; // ecx
  int v21; // esi
  char *v22; // eax
  uint32_t *v23; // eax
  unsigned int v24; // eax
  size_t *v25; // eax
  size_t *v26; // eax
  int pObj3; // edx
  int v28; // esi
  int v29; // ebx
  uint32_t *v30; // ecx
  int i; // esi
  int v32; // eax
  int pObj2; // ecx
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
  int dword_796E502; // [esp+80h] [ebp-10h]
  int v47; // [esp+8Ch] [ebp-4h]

  LOBYTE(v3) = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  pArg32 = pArg3;
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  if ( pArg3 == pArg1[1] )  // 若 pArg3 == pArg1[1]
  {
    pObj4 = pArg1[5];
    if ( pObj4 != 0 )  // 若 pObj4 != 0
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(  // 虚槽+152 效果通道 3
        pObj4,
        *(uint32_t *)(pArg3 + 20) + 28,
        *(uint32_t *)(pArg3 + 24) + 29,
        dword_79C0B0);  // dword_79C0B0（文本/图像绘制对象）
      pArg32 = pArg3;
    }
    else
    {
      pArg1[5] = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 204), 1u);  // 调 sub_418DD0
    }
    if ( pArg1[4] == 0 )  // 若 pArg1[4] == 0
    {
      v7 = 0;
      while ( *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * v7) )  // 当 *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * .. 循环
      {
        if ( ++v7 >= 3 )  // 若 ++v7 >= 3
          goto LABEL_11;  // 跳转 LABEL_11
      }
      if ( v7 != 1 )  // 若 v7 != 1
      {
LABEL_11:
        if ( sub_541A40() != 0 )  // 摊位结构初始化
          goto LABEL_13;  // 跳转 LABEL_13
      }
      pArg1[4] = dword_8F7C08;
    }
LABEL_13:
    if ( pArg1[4] != 0 && pArg1[5] != 0 && (uint8_t)sub_45E680(pArg1[4]) != 0 )  // 对象表归属判定
    {
      v8 = *(uint32_t *)(pArg32 + 20) + 28;
      v9 = *(uint32_t *)(pArg32 + 24) + 29;
      v10 = pArg1[5];
      v35 = *(uint32_t *)(v10 + 24);  // v35 = v10+24
      *(uint32_t *)Buffer = *(uint32_t *)(v10 + 20);
      (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)pArg1[4] + 384))(
        pArg1[4],
        v8,
        v9,
        *(uint32_t *)Buffer,
        v35,
        1065353216);
      pArg32 = pArg3;
    }
    if ( pArg1[4] != 0 )  // 若 pArg1[4] != 0
    {
      v11 = 0;
      while ( *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * v11) )  // 当 *(uint32_t *)dword_9B8038 != *(uint32_t *)(dword_9B8034 + 4 * .. 循环
      {
        if ( ++v11 >= 3 )  // 若 ++v11 >= 3
          goto LABEL_23;  // 跳转 LABEL_23
      }
      if ( v11 == 0 )  // 若 v11 == 0
        goto LABEL_30;  // 跳转 LABEL_30
LABEL_23:
      if ( (uint8_t)sub_45E680(pArg1[4]) != 0 )  // 对象表归属判定
      {
        v12 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pArg1[4] + 52))(pArg1[4], nArg2);  // 调用虚函数槽 +52
        v13 = sub_429830(v12);  // 结果 = 表按键查找（uint16）
        memset(Buffer, 0, sizeof(Buffer));  // 调 memset 按字节填充
        v45 = 0;
        sub_401710((int)v39, "Lv.");  // 字符串 “Lv.”
        v47 = 0;
        v14 = sub_41A5E0(v13 + 53);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        v15 = _itoa(v14, Buffer, 10);
        sub_402410((std::_String_base *)v39, v15);  // std::string::insert(pos, C串) 薄封装（strlen + ·sub
        sub_402410((std::_String_base *)v39, " ");  // std::string::insert(pos, C串) 薄封装（strlen + ·sub
        if ( *(uint32_t *)(v13 + 40) < 0x10u )  // 若 *(uint32_t *)(v13 + 40) < 0x10u
          v16 = (char *)(v13 + 20);
        else
          v16 = *(char **)(v13 + 20);
        sub_402410((std::_String_base *)v39, v16);  // std::string::insert(pos, C串) 薄封装（strlen + ·sub
        pObj = pArg1[7];
        v18 = *(uint32_t *)(*(uint32_t *)pObj + 20) + 10;
        v19 = *(uint32_t *)(*(uint32_t *)pObj + 24) - 20;
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_77F8FC);  // 调用虚函数槽 +72
        v20 = (uint32_t *)v40[0];
        if ( v40[5] < 0x10u )  // 若 v40[5] < 0x10u
          v20 = v40;
        (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          v18,
          v19,
          -1,
          v20);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
        v47 = -1;
        sub_501490(v39);  // 调 sub_501490
        pArg32 = pArg3;
      }
    }
LABEL_30:
    v21 = pArg1[4];
    if ( v21 != 0 && *(uint32_t *)(v21 + 648) != 0 && sub_541A40() != 0 && (uint8_t)sub_45E680(v21) != 0 )  // 摊位结构初始化
    {
      v22 = (char *)sub_4BD630(*(uint32_t **)(pArg1[4] + 648));  // 结果 = 主人名字取值（+304 串槽，空返回 szPassword）
      sub_401710((int)&v41, v22);  // std::string 复位并赋值 C 串（+24=15/+20=0/+4=0 → ·sub
      v47 = 1;
      if ( v42[4] > 0x18u )  // 若 v42[4] > 0x18u
      {
        v23 = (uint32_t *)v42[0];
        if ( v43 < 0x10 )  // 若 v43 < 0x10
          v23 = v42;
        v24 = sub_5515A0(v23, 24);  // 结果 = 任务文本辅助
        v25 = (size_t *)sub_4BD650(&v41, (int)v37, 0, v24);  // 结果 = std::string 拷贝构造到 pArg2
        LOBYTE(v47) = 2;
        v26 = (size_t *)sub_4E70B0((int)v38, v25, "...");  // 结果 = std::string 拼接构造（拷贝 + 插入）
        LOBYTE(v47) = 3;
        sub_4014D0(&v41, v26, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
        sub_501490(v38);  // 调 sub_501490
        LOBYTE(v47) = 1;
        sub_501490(v37);  // 调 sub_501490
      }
      pObj3 = pArg1[7];
      v28 = *(uint32_t *)(*(uint32_t *)pObj3 + 20) + 10;
      v29 = *(uint32_t *)(*(uint32_t *)pObj3 + 24) + 10;
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_77F8FC);  // 调用虚函数槽 +72
      v30 = (uint32_t *)v42[0];
      if ( v43 < 0x10 )  // 若 v43 < 0x10
        v30 = v42;
      (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        v28,
        v29,
        -1,
        v30);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
      v47 = -1;
      sub_501490(&v41);  // 调 sub_501490
      pArg32 = pArg3;
    }
    for ( i = 0; i < 14; ++i )  // 循环：i = 0; i < 14; ++i
    {
      v32 = pArg1[9];
      if ( i < *(uint32_t *)(v32 + 8) )  // 若 i < *(uint32_t *)(v32 + 8)
      {
        pObj2 = *(uint32_t *)(*(uint32_t *)(v32 + 12) + 4 * i);
        if ( pObj2 != 0 )  // 若 pObj2 != 0
        {
          (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, uint32_t, int))(*(uint32_t *)pObj2 + 8))(  // 虚槽+8 CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTTON2/DISSOLVE
            pObj2,
            32 * (i % 7u) + 61,
            32 * (i / 7u) + 291,
            0,
            1);
          pArg32 = pArg3;
        }
      }
    }
    LOBYTE(v3) = *(uint8_t *)(pArg32 + 17);
    if ( (uint8_t)v3 != 0
      && (dword_79BE3C == *(uint32_t *)(pArg32 + 12)  // CNRDPrivateStoreWindow__vmt0 构造（220 行：45E680 物品枚举 + 4BD630/4BD650 + 5515A0 + 5424B0；尾缀登记单例 dword_9B8034）
       || dword_79BE34 == *(uint32_t *)(pArg32 + 12)
       || dword_79BE38 == *(uint32_t *)(pArg32 + 12)) )
    {
      v3 = sub_5424B0(pArg1);  // 结果 = 基类/Buy/Sell 共用
      if ( v3 != -1 )  // 若 v3 != -1
        LOBYTE(v3) = sub_4F2E40(32 * (v3 % 7) + 61, 32 * (v3 / 7) + 291);
    }
  }
  return v3;
}


// ------------------------------------------------------------
// 0x543FD0 sub_543FD0 —— 摊位确认流程 1（543740 文本 + 4A3B30）
// ------------------------------------------------------------
// 大白话：上架确认第一步：用 543740 生成汇总文本并 4A3B30 弹确认框（【推断】
// 确认型对话框），根据选项结果走 543740 第二次生成明细。
int /*thiscall*/ sub_543FD0(int **this, int pArg2, int *pDwArg3)  // 函数: 摊位确认流程 1（543740 文本 + 4A3B30）
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
  fld_e1 = *(this + 1);  // fld_e1 = this+1
  v6 = fld_e1[1];  // fld_e1=this+4 宿主对象
  v7 = true;
  v13 = 1;
  if ( *(uint8_t *)(v6 + 21) == 0 )  // 若 *(uint8_t *)(v6 + 21) == 0
  {
    v8 = *pDwArg3;
    do
    {
      v7 = v8 < *(uint32_t *)(v6 + 12);
      fld_e1 = (int *)v6;  // fld_e1=this+4 宿主对象
      v13 = v7;
      if ( v8 >= *(uint32_t *)(v6 + 12) )  // 若 v8 >= *(uint32_t *)(v6 + 12)
        v6 = *(uint32_t *)(v6 + 8);  // v6 = v6+8
      else
        v6 = *(uint32_t *)v6;  // v6 = v6
    }
    while ( *(uint8_t *)(v6 + 21) == 0 );  // 当 *(uint8_t *)(v6 + 21) == 0 循环
  }
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  pDwArg3 = fld_e1;  // fld_e1=this+4 宿主对象
  if ( v7 )  // 若 v7
  {
    if ( fld_e1 == (int *)**(this + 1) )  // 若 fld_e1 == (int *)**(this + 1)
    {
      v10 = *sub_543740(this, (int *)&pDwArg3, 1, fld_e1, (int)pDwArg32);  // 结果 = 摊位标题/描述文本
      *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4 = 1
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4A3B30(&pDwArg3);  // 调 sub_4A3B30
    fld_e12 = pDwArg3;
  }
  if ( fld_e12[3] >= (unsigned int)*pDwArg32 )  // 若 fld_e12[3] >= (unsigned int)*pDwArg32
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // pArg2+4 = 0
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else
  {
    v12 = *sub_543740(this, (int *)&pDwArg3, v13, fld_e1, (int)pDwArg32);  // 结果 = 摊位标题/描述文本
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4 = 1
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x544090 sub_544090 —— 摊位确认流程 2（542940 + 5438F0 文本）
// ------------------------------------------------------------
// 大白话：上架确认第二步：542940 清挂链后用 5438F0 构建明细文本展示。
int */*thiscall*/ sub_544090(int **this, int *pDwArg2, int nArg3, int nArg4)  // 摊位确认流程 2（542940 + 5438F0 文本）
{
  int nArg42; // ebx
  int nArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int nArg322; // ecx
  int v11; // eax
  int j; // eax
  int i; // eax

  nArg42 = nArg4;
  nArg32 = nArg3;
  fld_e1 = (int)*(this + 1);
  if ( nArg3 == *(uint32_t *)fld_e1 && nArg4 == fld_e1 )  // 若 nArg3 == *(uint32_t *)fld_e1 && nArg4 == fld_e1
  {
    sub_542940(*(void ***)(fld_e1 + 4));  // 收购/出售子窗口公共辅助
    (*(this + 1))[1] = (int)*(this + 1);
    fld_e12 = *(this + 1);  // fld_e12 = this+1
    *(this + 2) = nullptr;  // this+8 = nullptr
    *fld_e12 = fld_e12;  // *fld_e12 写入 fld_e12
    (*(this + 1))[2] = (int)*(this + 1);
    *pDwArg2 = **(this + 1);  // *pDwArg2 写入 **(this + 1)
    return pDwArg2;
  }
  else
  {
    if ( nArg3 != nArg4 )  // 若 nArg3 != nArg4
    {
      do
      {
        nArg322 = nArg32;
        if ( *(uint8_t *)(nArg32 + 21) == 0 )  // 若 *(uint8_t *)(nArg32 + 21) == 0
        {
          v11 = *(uint32_t *)(nArg32 + 8);  // v11 = nArg32+8
          if ( *(uint8_t *)(v11 + 21) != 0 )  // 若 *(uint8_t *)(v11 + 21) != 0
          {
            for ( i = *(uint32_t *)(nArg32 + 4); *(uint8_t *)(i + 21) == 0; i = *(uint32_t *)(i + 4) )  // 循环：i = *(uint32_t *)(nArg32 + 4); *(uint8_t *)(i + 21) == 0; i 
            {
              if ( nArg32 != *(uint32_t *)(i + 8) )  // 若 nArg32 != *(uint32_t *)(i + 8)
                break;
              nArg32 = i;
            }
            nArg32 = i;
          }
          else
          {
            nArg32 = *(uint32_t *)(nArg32 + 8);  // nArg32 = nArg32+8
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 21) == 0; j = *(uint32_t *)j )  // 循环：j = *(uint32_t *)v11; *(uint8_t *)(j + 21) == 0; j = *(uint3
              nArg32 = j;
          }
        }
        sub_5438F0(this, &nArg3, nArg322);  // 摊位登记文本构建
      }
      while ( nArg32 != nArg42 );  // 当 nArg32 != nArg42 循环
    }
    *pDwArg2 = nArg32;  // *pDwArg2 写入 nArg32
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x544150 CNRDPrivateStoreWindow__vmt38 —— CNRDPrivateStoreWindow__vmt38 确认动作槽（522300 + 543FD0 + 484F40）
// ------------------------------------------------------------
// 大白话：摆摊确认按钮动作：522300 生成条目、543FD0 走确认弹窗、484F40 兜底登记。
int /*thiscall*/ CNRDPrivateStoreWindow__vmt38(int ***this, int nArg2, int nArg3, void *pArg4, int nArg5, int nArg6, int nArg7)  // 函数: CNRDPrivateStoreWindow__vmt38 确认动作槽（522300 + 543FD0 + 484F40）
{
  int v8; // edi
  int **fld_e6; // ecx
  uint8_t v11[8]; // [esp+8h] [ebp-10h] BYREF
  int v12[2]; // [esp+10h] [ebp-8h] BYREF

  v8 = sub_522300(pArg4, nArg5, nArg6, 0, nArg7, 1);  // 调 sub_522300
  v12[1] = nArg3;
  fld_e6 = *(this + 6);  // fld_e6 = this+6
  v12[0] = v8;
  sub_543FD0(fld_e6, (int)v11, v12);  // 摊位确认流程 1（543740 文本 + 4A3B30）
  return sub_484F40(nArg2, v8, 1);  // 技能槽装载（写槽 + 虚表 +28 反向绑定 + 重算）
}



// ------------------------------------------------------------
// 0x5441B0 sub_5441B0 —— 摊位确认动作实现（614180 + 41C5E0 + 544090，32 行）
// ------------------------------------------------------------
// 大白话：确认动作实现：614180/41C5E0 处理前置状态后走 544090 完成明细展示。
int /*thiscall*/ sub_5441B0(int **this, uint32_t *uArg2)  // 函数: 摊位确认动作实现（614180 + 41C5E0 + 544090，32 行）
{
  int v3; // eax
  int v4; // edi
  int v5; // esi
  uint32_t *v7; // [esp+Ch] [ebp-8h] BYREF
  int v8; // [esp+10h] [ebp-4h]

  sub_614180(this, &v7, uArg2);  // 调 sub_614180
  v3 = (int)v7;
  v4 = v8;
  v5 = 0;
  uArg2 = v7;
  if ( v7 != (uint32_t *)v8 )  // 若 v7 != (uint32_t *)v8
  {
    do
    {
      ++v5;  // 自增v5
      sub_41C5E0(&uArg2);  // 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
    }
    while ( uArg2 != (uint32_t *)v4 );  // 当 uArg2 != (uint32_t *)v4 循环
    v3 = (int)v7;
  }
  sub_544090(this, (int *)&uArg2, v3, v4);  // 摊位确认流程 2（542940 + 5438F0 文本）
  return v5;
}



// ------------------------------------------------------------
// 0x544210 sub_544210 —— 摊位确认转发（544090）
// ------------------------------------------------------------
// 大白话：确认动作薄转发：直接调 544090。
int /*thiscall*/ sub_544210(int this)  // 函数: 摊位确认转发（544090）
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_544090((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));  // 摊位确认流程 2（542940 + 5438F0 文本）
  j__free(*(void **)(this + 4));  // 调 j__free
  *(uint32_t *)(this + 4) = 0;  // this+4 = 0
  *(uint32_t *)(this + 8) = 0;  // this+8 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x544250 CNRDPrivateStoreWindow__vmt68 —— CNRDPrivateStoreWindow__vmt68 页绘制（93 行：43C250/69A5F0 + 4354D0/433AC0）
// ------------------------------------------------------------
// 大白话：确认/收购子页装配：43C250 面板 + 4354D0/433AC0 列表件，布局同族窗口。
uint32_t */*thiscall*/ CNRDPrivateStoreWindow__vmt68(uint32_t *this)  // CNRDPrivateStoreWindow__vmt68 页绘制（93 行：43C250/69A5F0 + 4354D0/433AC0）
{
  int v1; // ebx
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  void *pMem2; // eax
  uint32_t *pOwnerWnd; // ecx
  uint32_t *result; // eax
  uint32_t *pMem3; // eax
  uint32_t *v9; // esi
  uint32_t *v10; // eax
  int v11; // esi
  uint32_t *v12; // eax

  v1 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 204);
  pMem = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v4 = sub_43C250(pMem, v1, 0);  // 结果 = nengine::CNFrame 构造
  else
    v4 = nullptr;  // v4 = nullptr 空指针
  *(this + 1) = v4;  // this+4 = v4
  *((uint32_t *)v4 + 17) = this;
  pMem2 = operator new(0xCu);  // 堆分配 12 字节对象
  pOwnerWnd = (uint32_t *)*(this + 1);
  *(this + 7) = pMem2;  // this+28 = pMem2
  result = sub_69A5F0(pOwnerWnd, 29, 168);  // 调 sub_69A5F0
  if ( dword_9B8034 == 0 )  // 若 dword_9B8034 == 0
  {
    result = operator new(0xCu);  // 堆分配 12 字节对象
    dword_9B8034 = (int)result;
    *result = 0;  // *result 写入 0
    *(uint32_t *)(dword_9B8034 + 4) = 0;  // dword_9B8034+4 = 0
    *(uint32_t *)(dword_9B8034 + 8) = 0;  // dword_9B8034+8 = 0
  }
  if ( dword_9B8040 == 0 )  // 若 dword_9B8040 == 0
  {
    pMem3 = operator new(0x20u);  // 堆分配 32 字节对象
    if ( pMem3 != nullptr )  // 若 pMem3 非空
      result = sub_4354D0(pMem3, (void *)5, 14);  // 结果 = 32 字节技能槽对象构造
    else
      result = nullptr;  // result = nullptr 空指针
    dword_9B8040 = (int)result;
  }
  if ( dword_9B8044 == nullptr )  // 若 dword_9B8044 为空
  {
    result = operator new(0xCu);  // 堆分配 12 字节对象
    v9 = result;
    if ( result != nullptr )  // 若 result 非空
    {
      v10 = sub_433AC0();  // 结果 = map 节点分配（0x18）
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
      v9 = nullptr;  // v9 = nullptr 空指针
    }
    dword_9B8044 = v9;
  }
  if ( dword_9B8048 == 0 )  // 若 dword_9B8048 == 0
  {
    result = operator new(0xCu);  // 堆分配 12 字节对象
    v11 = (int)result;
    if ( result != nullptr )  // 若 result 非空
    {
      v12 = sub_433AC0();  // 结果 = map 节点分配（0x18）
      *(uint32_t *)(v11 + 4) = v12;  // v11+4 = v12
      *((uint8_t *)v12 + 21) = 1;
      *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) = *(uint32_t *)(v11 + 4);
      **(uint32_t **)(v11 + 4) = *(uint32_t *)(v11 + 4);
      result = *(uint32_t **)(v11 + 4);
      result[2] = result;
      *(uint32_t *)(v11 + 8) = 0;  // v11+8 = 0
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
// 大白话：条目动作槽：484880 取挂件、5441B0 执行确认、4850B0 收尾刷新。
int /*thiscall*/ CNRDPrivateStoreWindow__vmt44(int this, int nArg2, int nArg3)  // 函数: CNRDPrivateStoreWindow__vmt44 槽（484880 + 5441B0 + 4850B0）
{
  int result; // eax
  int pSellEntryList; // ecx  | +0x0024 → ★ 上架条目挂链（CNRDPrivateStoreWindow；va=00542650）
  int v6; // edi
  int v7; // eax
  int *v8; // [esp+4h] [ebp-4h] BYREF

  result = nArg2;
  pSellEntryList = *(uint32_t *)(this + 36);  // fld_24 = this+36
  if ( nArg2 < *(uint32_t *)(pSellEntryList + 8) )  // 若 nArg2 < *(uint32_t *)(fld_24 + 8)
  {
    v8 = *(int **)(*(uint32_t *)(pSellEntryList + 12) + 4 * nArg2);  // fld_24=this+36 pSellEntryList
    if ( v8 != nullptr )  // 若 v8 非空
    {
      sub_484880(6);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
      v6 = *v8;
      v7 = (*(int (/*thiscall*/ **)(int *))(*v8 + 16))(v8);  // 结果 = 虚调用 vt+16
      if ( (*(uint8_t (/*thiscall*/ **)(int *, uint32_t))(v6 + 60))(v8, *(uint32_t *)(v7 + 4)) == 0
        || (*(int (/*thiscall*/ **)(int *))(*v8 + 44))(v8) == nArg3 )  // 虚调用 vt+44
      {
        sub_5441B0(*(int ***)(this + 24), &v8);  // 摊位确认动作实现
      }
      return sub_4850B0(nArg2, nArg3);  // 本地命令 0 执行：槽值设置或扣减（op 18）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x544460 CNRDPrivateStoreWindow_Display__vmt3C —— CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行：4BE520 + 484880/485330 + 543FD0）
// ------------------------------------------------------------
// 大白话：展示页取消动作：沿列表(+9)扫描条目(4BE520 解包)，484880/485330
// 撤销登记后走 543FD0 弹确认。
int /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt3C(uint32_t *this, unsigned int uArg2, int nArg3, int nArg4, int64_t uArg5)  // 函数: CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行：4BE520 + 484880/485330 + 543FD0）
{
  int v5; // ebx
  int nAvatarListId; // eax  | +0x0024 → ★ 物品清单 id（0x543190: *(this+36) = dword_9B8040；= 背包上架源列表）（CNRDPrivateStoreWindow_Display；va=005443F0）
  int pObj; // edi
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
  uint32_t *pThis; // [esp+20h] [ebp-4h]

  v5 = 0;
  pThis = this;
  v17 = 0;
  do
  {
    nAvatarListId = *(this + 9);  // fld_e9 = this+9
    if ( v5 < *(uint32_t *)(nAvatarListId + 8) )  // 若 v5 < *(uint32_t *)(fld_e9 + 8)
    {
      v20 = *(uint32_t *)(*(uint32_t *)(nAvatarListId + 12) + 4 * v5);  // fld_e9=this+36 nAvatarListId
      pObj = v20;
      if ( v20 != 0 )  // 若 v20 != 0
      {
        v8 = *(uint32_t *)sub_4BE520(v19, &v20) + 12;  // 结果 = 映射下界查找（lower_bound）
        v17 += (unsigned int)(*(uint32_t *)(v8 + 4) * (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj));  // 虚槽+44 IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 + 69A5F0/69A8
        this = pThis;
      }
    }
    ++v5;  // 自增v5
  }
  while ( v5 < 14 );  // 当 v5 < 14 循环
  v9 = v17 + (int)uArg5 * (int64_t)SHIDWORD(uArg5);  // 调 SHIDWORD（取 64 位值高 32 位(带符号)）
  HIDWORD(v17) = HIDWORD(v9);
  if ( v9 <= 0x7FFFFFFF )  // 若 v9 <= 0x7FFFFFFF
  {
    v12 = sub_432F00(nArg4);  // 结果 = 按类型取全局列表对象
    v13 = v12[5];
    if ( v13 == 0 || (result = (v12[6] - v13) >> 2) <= 0 )  // 若 v13 == 0 || (result = (v12[6] - v13) >> 2) <= 0
    {
      v14 = *(uint32_t *)(dword_9B8040 + 20);  // v14 = dword_9B8040+20
      if ( v14 == 0 || (result = (*(uint32_t *)(dword_9B8040 + 24) - v14) >> 2) <= 0 )  // 若 v14 == 0 || (result = (*(uint32_t *)(dword_9B8040 + 24) - v14)..
      {
        sub_484880(6);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
        sub_484880(6);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
        sub_485330(uArg2, HIDWORD(uArg5), dword_9B8040, nArg3);  // 技能槽命令处理（+44/+48/+52/+56 槽位字段；音效 sub_432EA0）
        if ( nArg3 >= *(uint32_t *)(dword_9B8040 + 8) )  // 若 nArg3 >= *(uint32_t *)(dword_9B8040 + 8)
          v15 = 0;
        else
          v15 = *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * nArg3);
        v16 = (int **)pThis[6];
        v17 = __PAIR64__(uArg5, v15);  // 调 __PAIR64__（拼装 64 位值(高32,低32)）
        sub_543FD0(v16, (int)v18, (int *)&v17);  // 摊位确认流程 1（543740 文本 + 4A3B30）
        v17 = __PAIR64__(uArg2, v15);  // 调 __PAIR64__（拼装 64 位值(高32,低32)）
        return sub_543FD0((int **)dword_9B8048, (int)v18, (int *)&v17);  // 摊位确认流程 1（543740 文本 + 4A3B30）
      }
    }
  }
  else
  {
    v10 = sub_422E70(1356);  // 调 sub_422E70
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v10, 0);  // 对象池借出（按池号取可用对象）
  }
  return result;
}



// ------------------------------------------------------------
// 0x5445E0 CNRDPrivateStoreWindow_Display__vmt48 —— CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520/4F2D40 + 484880/5441B0/485330）
// ------------------------------------------------------------
// 大白话：展示页动作槽：4BE520/4F2D40 解析条目，484880/5441B0/485330 走确认链。
int /*thiscall*/ CNRDPrivateStoreWindow_Display__vmt48(int ***this, int nArg2)  // 函数: CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520/4F2D40 + 484880/5441B0/485330）
{
  int v2; // edx
  int pObj; // edi
  bool v4; // bl
  int v5; // eax
  uint32_t *dword_8F852C2; // esi
  int v7; // ecx
  int result; // eax
  int v9; // ecx
  int v10; // edi
  int v11; // [esp+Ch] [ebp-Ch] BYREF
  int ***pThis; // [esp+10h] [ebp-8h]
  int pObj2; // [esp+14h] [ebp-4h] BYREF

  v2 = *(uint32_t *)(dword_9B8040 + 8);  // v2 = dword_9B8040+8
  pThis = this;
  if ( nArg2 >= v2 )  // 若 nArg2 >= v2
    pObj = 0;
  else
    pObj = *(uint32_t *)(*(uint32_t *)(dword_9B8040 + 12) + 4 * nArg2);
  pObj2 = pObj;
  v4 = false;
  v11 = *(uint32_t *)(*(uint32_t *)sub_4BE520(&v11, &pObj2) + 16);  // 结果 = 映射下界查找（lower_bound）
  if ( pObj != 0 )  // 若 pObj != 0
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);  // 调用虚函数槽 +16
    if ( sub_4F2D40(*(uint32_t *)(v5 + 4)) == 2 )  // 若 sub_4F2D40(*(uint32_t *)(v5 + 4)) == 2
      v4 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj) <= 7;  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
  }
  dword_8F852C2 = dword_8F852C;  // 全局 dword_8F852C = 角色/物品栏管理器
  if ( v4 )  // 若 v4
    dword_8F852C2 = dword_8F8534;  // dword_8F8534（技能槽装载对象）
  v7 = dword_8F852C2[5];
  if ( v7 == 0 || (result = (dword_8F852C2[6] - v7) >> 2) <= 0 )  // 若 v7 == 0 || (result = (dword_8F852C2[6] - v7) >> 2) <= 0
  {
    v9 = *(uint32_t *)(dword_9B8040 + 20);  // v9 = dword_9B8040+20
    if ( v9 == 0 || (result = (*(uint32_t *)(dword_9B8040 + 24) - v9) >> 2) <= 0 )  // 若 v9 == 0 || (result = (*(uint32_t *)(dword_9B8040 + 24) - v9) >..
    {
      sub_484880(6);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
      sub_484880(6);  // 4 字节列表尾插（容量不足回落 ·sub_430C80）
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj);  // 调用虚函数槽 +44
      sub_5441B0(pThis[6], &pObj2);  // 摊位确认动作实现
      sub_5441B0((int **)dword_9B8048, &pObj2);  // 摊位确认动作实现
      return sub_485330(nArg2, v10, dword_8F852C2, v11);  // 技能槽命令处理（+44/+48/+52/+56 槽位字段；音效 sub_432EA0）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5446F0 CNRDPrivateStoreWindow_Buy__vmt68 —— CNRDPrivateStoreWindow_Buy__vmt68 页绘制（94 行：43C250/69A5F0/69A840/43C410 + 4354D0/433AC0）
// ------------------------------------------------------------
// 大白话：收购页装配：43C250/69A5F0/69A840/43C410 布件 + 4354D0/433AC0 列表件。
int /*thiscall*/ CNRDPrivateStoreWindow_Buy__vmt68(int this)  // 函数: CNRDPrivateStoreWindow_Buy__vmt68 页绘制（94 行：43C250/69A5F0/69A840/43C410 + 4354D0/433AC0）
{
  uint32_t *bInited; // ecx
  int v3; // edi
  uint8_t *pMem; // eax
  uint8_t *v5; // eax
  uint8_t *pMem2; // eax
  uint8_t *v7; // eax
  uint8_t *pMem3; // eax
  uint8_t *v9; // eax
  uint32_t *pMem4; // eax
  uint32_t *v11; // eax
  uint32_t *pMem5; // eax
  uint32_t *v13; // eax
  uint32_t *pMem6; // edi
  uint32_t *v15; // eax
  int result; // eax
  int v17; // [esp+Ch] [ebp-14h]
  int v18; // [esp+10h] [ebp-10h]

  bInited = *(uint32_t **)(this + 4);  // this+4 宿主对象
  v17 = bInited[5];  // fld_4=this+4 宿主对象
  v18 = bInited[6];  // fld_4=this+4 宿主对象
  sub_69A5F0(bInited, 0, 0);  // 调 sub_69A5F0
  v3 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 204);
  pMem = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v5 = sub_43C250(pMem, v3, 2);  // 结果 = nengine::CNFrame 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  **(uint32_t **)(this + 28) = v5;  // this+28 pPanelVec
  pMem2 = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v7 = sub_43C250(pMem2, v3, 5);  // 结果 = nengine::CNFrame 构造
  else
    v7 = nullptr;  // v7 = nullptr 空指针
  *(uint32_t *)(*(uint32_t *)(this + 28) + 4) = v7;  // this+28 pPanelVec
  pMem3 = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    v9 = sub_43C250(pMem3, v3, 7);  // 结果 = nengine::CNFrame 构造
  else
    v9 = nullptr;  // v9 = nullptr 空指针
  *(uint32_t *)(*(uint32_t *)(this + 28) + 8) = v9;  // this+28 pPanelVec
  sub_69A5F0(**(uint32_t ***)(this + 28), 105, 59);  // 调 sub_69A5F0
  sub_69A5F0(*(uint32_t **)(*(uint32_t *)(this + 28) + 4), 101, 189);  // 调 sub_69A5F0
  sub_69A5F0(*(uint32_t **)(*(uint32_t *)(this + 28) + 8), 58, 224);  // 调 sub_69A5F0
  *(uint8_t *)(**(uint32_t **)(this + 28) + 16) = 0;  // this+28 pPanelVec
  sub_69A840(**(uint32_t **)(this + 28));  // 调 sub_69A840
  sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 4));  // 调 sub_69A840
  sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 8));  // 调 sub_69A840
  pMem4 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    v11 = sub_43C410(pMem4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 32), 4, 5, 6, 4, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v11 = nullptr;  // v11 = nullptr 空指针
  *(uint32_t *)(this + 40) = v11;  // 写 this+40 = v11（收购按钮）
  sub_69A5F0(v11, 128, 192);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 40));  // 调 sub_69A840
  sub_69A5F0(*(uint32_t **)(this + 4), v17, v18);  // 调 sub_69A5F0
  if ( *(uint32_t *)(dword_9B8034 + 8) != 0 )  // 若 *(uint32_t *)(dword_9B8034 + 8) != 0
    off_77F3FC("Another private shop created!");  // 字符串 “Another private shop created!”
  *(uint32_t *)(dword_9B8034 + 8) = this;  // dword_9B8034+8 = this
  pMem5 = operator new(0x20u);  // 堆分配 32 字节对象
  if ( pMem5 != nullptr )  // 若 pMem5 非空
    v13 = sub_4354D0(pMem5, (void *)5, 14);  // 结果 = 32 字节技能槽对象构造
  else
    v13 = nullptr;  // v13 = nullptr 空指针
  *(uint32_t *)(this + 36) = v13;  // 写 this+36 = v13（收购列表件）
  pMem6 = operator new(0xCu);  // 堆分配 12 字节对象
  if ( pMem6 != nullptr )  // 若 pMem6 非空
  {
    v15 = sub_433AC0();  // 结果 = map 节点分配（0x18）
    pMem6[1] = v15;
    *((uint8_t *)v15 + 21) = 1;
    *(uint32_t *)(pMem6[1] + 4) = pMem6[1];
    *(uint32_t *)pMem6[1] = pMem6[1];
    result = pMem6[1];
    *(uint32_t *)(result + 8) = result;  // result+8 = result
    pMem6[2] = 0;
    *(uint32_t *)(this + 24) = pMem6;  // 写 this+24 = pMem6（收购清单向量）
  }
  else
  {
    *(uint32_t *)(this + 24) = 0;  // 写 this+24 = 0（收购清单向量）
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
// 大白话：收购子窗辅助：转发 544210 确认动作。
void /*thiscall*/ sub_544960(uint32_t *this)  // 函数: 收购子窗口辅助（23 行，转发 544210）
{
  void (/*thiscall*/ ***fld_e1)(uint32_t, int); // ecx
  void *dword_9B80442; // esi

  fld_e1 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( fld_e1 != nullptr )  // 若 fld_e1 非空
    (**fld_e1)(fld_e1, 1);
  *(this + 1) = 0;  // this+4 = 0
  if ( dword_9B8044 != nullptr )  // 若 dword_9B8044 非空
  {
    dword_9B80442 = dword_9B8044;
    sub_544210((int)dword_9B8044);  // 摊位确认转发（544090）
    j__free(dword_9B80442);  // 调 j__free
  }
  dword_9B8044 = nullptr;  // dword_9B8044 = nullptr 空指针
}



// ------------------------------------------------------------
// 0x5449A0 sub_5449A0 —— 18 行小辅助
// ------------------------------------------------------------
// 大白话：收购/定价子窗状态复位：+27..+33 各挂件清零，+35 = 999999999 为
// 价格输入上限。
int /*thiscall*/ sub_5449A0(uint32_t *this)  // 函数: 18 行小辅助
{
  *(this + 27) = 0;  // this+108 = 0
  *(this + 28) = 0;  // this+112 = 0
  *(this + 29) = 0;  // this+116 = 0
  *(this + 30) = 0;  // this+120 = 0
  *(this + 31) = 0;  // this+124 = 0
  *(this + 33) = 0;  // this+132 = 0
  *(this + 32) = 0;  // this+128 = 0
  *(this + 35) = 999999999;  // this+140 = 999999999
  return 0;
}



// ------------------------------------------------------------
// 0x5449D0 sub_5449D0 —— 数量/价格辅助（28 行）
// ------------------------------------------------------------
// 大白话：子窗清理：对 +29/+30/+31 挂的子对象逐个调虚表槽0（标量删除）并清零，
// dword_9B8050 复位 0。
int /*thiscall*/ sub_5449D0(uint32_t *this)  // 函数: 数量/价格辅助（28 行）
{
  int (/*thiscall*/ ***fld_e29)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e30)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e31)(uint32_t, int); // ecx

  fld_e29 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 29);  // this+29 pSessionCtx
  if ( fld_e29 != nullptr )  // 若 fld_e29 非空
    result = (**fld_e29)(fld_e29, 1);
  fld_e30 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 30);  // this+30 pAnimObj
  *(this + 29) = 0;  // this+116 = 0
  if ( fld_e30 != nullptr )  // 若 fld_e30 非空
    result = (**fld_e30)(fld_e30, 1);
  fld_e31 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 31);
  *(this + 30) = 0;  // this+120 = 0
  if ( fld_e31 != nullptr )  // 若 fld_e31 非空
    result = (**fld_e31)(fld_e31, 1);
  *(this + 31) = 0;  // this+124 = 0
  dword_9B8050 = 0;
  return result;
}



// ------------------------------------------------------------
// 0x544A10 sub_544A10 —— 输入框取值（22 行）
// ------------------------------------------------------------
// 大白话：输入框焦点同步（同 540960 模式）：+29 挂件持焦点且未进入输入态时把
// 标题文本同步到全局 dword_79BE4C/54，清 +28 标记后调 CNCommandChecker__vmt40(0,1)。
int /*thiscall*/ sub_544A10(uint32_t *this)  // 函数: 输入框取值（22 行）
{
  int fld_e27; // eax

  if ( dword_79BE54 == *(uint32_t *)(*(this + 29) + 12) )  // 若 dword_79BE54 == *(uint32_t *)(*(this + 29) + 12)
  {
    fld_e27 = *(uint32_t *)(*(this + 27) + 28);
    if ( *(uint8_t *)(fld_e27 + 256) == 0 )  // 若 *(uint8_t *)(fld_e27 + 256) == 0
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(fld_e27 + 124) + 12);
      dword_79BE54 = dword_79BE4C;
    }
  }
  *(uint8_t *)(*(this + 28) + 16) = 0;  // this+28 逐帧驱动对象
  return CNCommandChecker__vmt40(0, 1);
}



// ------------------------------------------------------------
// 0x544A60 sub_544A60 —— 点击音效（CLICK_BUTTON2）
// ------------------------------------------------------------
// 大白话：点击音效 + 焦点同步：播 CLICK_BUTTON2 后做与 544A10 相同的输入框
// 焦点同步（+29 持焦点 → 标题同步 dword_79BE4C/54，清 +28，CNCommandChecker__vmt40(0,1)）。
int /*thiscall*/ sub_544A60(uint32_t *this)  // 函数: 点击音效（CLICK_BUTTON2）
{
  int fld_e27; // eax

  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  if ( dword_79BE54 == *(uint32_t *)(*(this + 29) + 12) )  // 若 dword_79BE54 == *(uint32_t *)(*(this + 29) + 12)
  {
    fld_e27 = *(uint32_t *)(*(this + 27) + 28);
    if ( *(uint8_t *)(fld_e27 + 256) == 0 )  // 若 *(uint8_t *)(fld_e27 + 256) == 0
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(fld_e27 + 124) + 12);
      dword_79BE54 = dword_79BE4C;
    }
  }
  *(uint8_t *)(*(this + 28) + 16) = 0;  // this+28 逐帧驱动对象
  return CNCommandChecker__vmt40(0, 1);
}



// ------------------------------------------------------------
// 0x544AC0 sub_544AC0 —— 展示列表刷新（432F00 + 69BCC0/402AE0/69A5F0，65 行）
// ------------------------------------------------------------
// 大白话：展示列表刷新：432F00 取源列表后按 69BCC0/402AE0/69A5F0 重排展示格。
uint32_t */*thiscall*/ sub_544AC0(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 展示列表刷新
{
  uint32_t *result; // eax
  int fld_e33; // ecx
  int pHostComp; // edx
  unsigned int v8; // edi
  int v9; // eax
  int v10; // ecx
  int v11; // edi
  int pObj; // [esp+Ch] [ebp+8h]

  *(this + 33) = nArg2;  // this+132 = nArg2
  *(this + 32) = nArg3;  // this+128 = nArg3
  *(this + 36) = nArg4;  // this+144 = nArg4
  result = sub_432F00(nArg4);  // 结果 = 按类型取全局列表对象
  if ( result != nullptr )  // 若 result 非空
  {
    fld_e33 = *(this + 33);  // fld_e33 = this+33
    if ( fld_e33 < result[2] )  // 若 fld_e33 < result[2]
    {
      pObj = *(uint32_t *)(result[3] + 4 * fld_e33);  // fld_e33=this+132 第 3 组·+60 增量项
      if ( pObj != 0 )  // 若 pObj != 0
      {
        sub_69BCC0(*(this + 29));  // 调 sub_69BCC0
        sub_402AE0(szPassword);  // 字符串包赋值 C 串（按需扩容后 qmemcpy + 尾 NUL + +4 置有效）
        pHostComp = *(this + 28);  // fld_e28 = this+28
        v8 = *(uint32_t *)(pHostComp + 28);  // v8 = fld_e28+28
        v9 = pt.x - (v8 >> 1);
        v10 = pt.y - (*(uint32_t *)(pHostComp + 32) >> 1);  // fld_e28=this+112 第 1 组·宿主属性 +46 增量子倍率
        if ( v9 >= 0 )  // 若 v9 >= 0
        {
          if ( v8 + v9 > 0x280 )  // 若 v8 + v9 > 0x280
            v9 = 640 - v8;
        }
        else
        {
          v9 = 0;
        }
        if ( v10 >= 0 )  // 若 v10 >= 0
        {
          v11 = *(uint32_t *)(pHostComp + 32);  // v11 = fld_e28+32
          if ( (unsigned int)(v11 + v10) > 0x1E0 )  // 若 (unsigned int)(v11 + v10) > 0x1E0
            v10 = 480 - v11;
        }
        else
        {
          v10 = 0;
        }
        *(uint8_t *)(pHostComp + 16) = 1;  // fld_e28+16 = 1
        sub_69A5F0((uint32_t *)*(this + 28), v9, v10);  // 调 sub_69A5F0
        dword_79BE4C = *(uint32_t *)(*(this + 29) + 12);  // this+29 pSessionCtx
        dword_79BE54 = dword_79BE4C;
        *(this + 34) = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 4);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
        return (uint32_t *)CNCommandChecker__vmt40(0, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x544BD0 sub_544BD0 —— 收购确认处理（69B740 输入 + 541A30/540DE0 + 44E8D0，74 行）
// ------------------------------------------------------------
// 大白话：收购确认：读 69B740 输入框数量/价格，541A30/540DE0 联动登记并 44E8D0 弹提示。
int /*thiscall*/ sub_544BD0(int this)  // 函数: 收购确认处理（69B740 输入 + 541A30/540DE0 + 44E8D0，74 行）
{
  uint32_t *fld_90; // eax
  int fld_84; // ecx
  int v4; // edx
  int pObj; // edi
  const char *fld_74; // eax
  int result; // eax
  int v8; // ebx
  int pObj2; // eax
  char *v10; // eax
  int fld_6C; // eax

  fld_90 = sub_432F00(*(uint32_t *)(this + 144));  // 结果 = 按类型取全局列表对象
  if ( fld_90 != nullptr
    && (fld_84 = *(uint32_t *)(this + 132)) < fld_90[2]  // this+132 第 3 组·+60 增量项
    && (v4 = fld_90[3], (pObj = *(uint32_t *)(v4 + 4 * fld_84)) != 0)  // 收购确认处理（69B740 输入 + 541A30/540DE0 + 44E8D0，74 行）
    && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj + 16))(*(uint32_t *)(v4 + 4 * fld_84)) + 4) == *(uint32_t *)(this + 136) )
  {
    fld_74 = (const char *)sub_69B740(*(uint32_t *)(this + 116));  // this+116 观察者 vector 尾针
    result = j__atol(fld_74);  // 调 j__atol
    v8 = result;
    if ( result > 0 )  // 若 result > 0
    {
      if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj) <= 1 )  // 虚槽+44 IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 + 69A5F0/69A8
      {
        pObj2 = sub_541A30();  // 结果 = 摊位条目名取串
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, int))(*(uint32_t *)pObj2 + 60))(  // 虚槽+60 CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行：4BE520 + 48
          pObj2,
          *(uint32_t *)(this + 132),  // this+132 第 3 组·+60 增量项
          *(uint32_t *)(this + 128),  // this+128 第 2 组·+1208 增量子倍率
          *(uint32_t *)(this + 144),  // this+144 第 4 组·+1040 增量子倍率
          v8,
          1);
      }
      else
      {
        sub_540DE0(  // 摊位列表构建
          *(int **)(*(uint32_t *)(this + 108) + 116),  // this+108 第 1 组·宿主属性 +886 增量
          1,
          *(uint32_t *)(this + 144),  // this+144 第 4 组·+1040 增量子倍率
          *(uint32_t *)(this + 132),  // this+132 第 3 组·+60 增量项
          5,
          *(uint32_t *)(this + 128),  // this+128 第 2 组·+1208 增量子倍率
          v8,
          0);
      }
      return sub_544A10((uint32_t *)this);  // 输入框取值
    }
  }
  else
  {
    v10 = sub_422E70(492);  // 调 sub_422E70
    sub_44E8D0(*(char **)(this + 108), (void *)0x1B, (int)v10, 0);  // 对象池借出（按池号取可用对象）
    if ( dword_79BE54 == *(uint32_t *)(*(uint32_t *)(this + 116) + 12) )  // 若 dword_79BE54 == *(uint32_t *)(*(uint32_t *)(this + 116) + 12)
    {
      fld_6C = *(uint32_t *)(*(uint32_t *)(this + 108) + 28);  // this+108 第 1 组·宿主属性 +886 增量
      if ( *(uint8_t *)(fld_6C + 256) == 0 )  // 若 *(uint8_t *)(fld_6C + 256) == 0
      {
        dword_79BE4C = *(uint32_t *)(*(uint32_t *)(fld_6C + 124) + 12);
        dword_79BE54 = dword_79BE4C;
      }
    }
    *(uint8_t *)(*(uint32_t *)(this + 112) + 16) = 0;  // this+112 第 1 组·宿主属性 +46 增量子倍率
    return CNCommandChecker__vmt40(0, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x544D10 sub_544D10 —— 定价确认：CLICK_BUTTON2 + 69A650/69B740/69BD90 输入 + 544BD0 提交 + 544A60 音
// ------------------------------------------------------------
// 大白话：定价确认按钮：悬停/回车时读 69A650/69B740/69BD90 输入，调 544BD0 提交，
// 播 CLICK_BUTTON2 确认音。
char /*thiscall*/ sub_544D10(int *this)  // 函数: 定价确认：CLICK_BUTTON2 + 69A650/69B740/69BD90 输入 + 544BD0 提交 + 544A60 音
{
  int fld_e28; // ecx
  int fld_e31; // eax
  int fld_e282; // eax
  const char *fld_e29; // eax
  int v6; // eax
  int fld_e35; // ecx
  int fld_e30; // eax
  int fld_e292; // eax
  char v10; // cl
  int fld_e302; // eax
  char v13; // [esp-Ch] [ebp-24h]
  char Buffer[16]; // [esp+4h] [ebp-14h] BYREF
  int dword_796E502; // [esp+14h] [ebp-4h]

  fld_e28 = *(this + 28);  // fld_e28 = this+28
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  LOBYTE(fld_e31) = *(uint8_t *)(fld_e28 + 16);  // fld_e28=this+112 第 1 组·宿主属性 +46 增量子倍率
  if ( (uint8_t)fld_e31 == 0 )  // 若 (uint8_t)fld_e31 == 0
    return fld_e31;
  sub_69A650(fld_e28);  // 调 sub_69A650
  fld_e282 = *(this + 28);  // fld_e282 = this+28
  if ( *(uint8_t *)(fld_e282 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e282 + 12) )  // 若 *(uint8_t *)(fld_e282 + 17) != 0 && dword_79BE34 == *(uint32_t..
  {
    dword_79BE4C = *(uint32_t *)(*(this + 29) + 12);  // this+29 pSessionCtx
    dword_79BE54 = dword_79BE4C;
  }
  fld_e29 = (const char *)sub_69B740(*(this + 29));  // this+29 pSessionCtx
  v6 = j__atol(fld_e29);  // 调 j__atol
  if ( v6 < 0 )  // 若 v6 < 0
  {
    fld_e35 = 0;
    goto LABEL_8;  // 跳转 LABEL_8
  }
  fld_e35 = *(this + 35);  // fld_e35 = this+35
  if ( v6 > fld_e35 )  // 若 v6 > fld_e35
  {
LABEL_8:
    if ( fld_e35 != v6 )  // 若 fld_e35 != v6
    {
      sprintf(Buffer, "%d", fld_e35);  // 字符串 “%d”
      sub_69BD90(*(this + 29), Buffer, v13);  // 调 sub_69BD90
    }
  }
  fld_e30 = *(this + 30);  // fld_e30 = this+30
  if ( *(uint8_t *)(fld_e30 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e30 + 12)  // 若 *(uint8_t *)(fld_e30 + 17) != 0 && dword_79BE34 == *(uint32_t ..
    || (fld_e292 = *(this + 29), v10 = *(uint8_t *)(fld_e292 + 116), *(uint8_t *)(fld_e292 + 116) = 0, v10 != 0) )  // 定价确认：CLICK_BUTTON2 + 69A650/69B740/69BD90 输入 + 544BD0 提交 + 544A60 音
  {
    sub_544BD0((int)this);  // 收购确认处理
  }
  fld_e302 = *(this + 30);  // fld_e302 = this+30
  if ( *(uint8_t *)(fld_e302 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e302 + 12) )  // 若 *(uint8_t *)(fld_e302 + 17) != 0 && dword_79BE34 == *(uint32_t..
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  fld_e31 = *(this + 31);  // fld_e31 = this+31
  if ( *(uint8_t *)(fld_e31 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e31 + 12) )  // 若 *(uint8_t *)(fld_e31 + 17) != 0 && dword_79BE34 == *(uint32_t ..
    LOBYTE(fld_e31) = sub_544A60(this);  // 点击音效（CLICK_BUTTON2）
  return fld_e31;  // fld_e31=this+124 第 2 组·+858/+1292 增量
}



// ------------------------------------------------------------
// 0x544E20 CNRDMakePriceWindow__vmt18 —— CNRDMakePriceWindow__vmt18 定价确认槽（转发 544D10）
// ------------------------------------------------------------
// 大白话：定价窗（CNRDMakePriceWindow）确认槽：转发 544D10。
void /*thiscall*/ CNRDMakePriceWindow__vmt18(Concurrency::details::ExternalContextBase *this)  // 函数: CNRDMakePriceWindow__vmt18 定价确认槽（转发 544D10）
{
  if ( *(uint8_t *)(*((uint32_t *)this + 28) + 16) != 0 )  // 若 *(uint8_t *)(*((uint32_t *)this + 28) + 16) != 0
  {
    sub_544D10((int *)this);  // 定价确认：CLICK_BUTTON2 + 69A650/69B740/69BD90 输入 +
    Concurrency::details::ExternalContextBase::SpinYield(this);
  }
}



// ------------------------------------------------------------
// 0x544E40 sub_544E40 —— 定价窗口绘制（43C060/69A5F0/69A840/43C410 + 544A10，55 行）
// ------------------------------------------------------------
// 大白话：定价窗页绘制：43C060/69A5F0/69A840/43C410 布件 + 544A10 回显数值。
int /*thiscall*/ sub_544E40(uint32_t *this, void *Block)  // 函数: 定价窗口绘制（43C060/69A5F0/69A840/43C410 + 544A10，55 行）
{
  int result; // eax
  int v4; // edi
  void *pMem; // eax
  int v6; // eax
  uint32_t *pMem2; // eax
  uint32_t *v8; // eax
  uint32_t *pMem3; // eax
  uint32_t *v10; // eax

  result = dword_9B8050;
  if ( dword_9B8050 == 0 )  // 若 dword_9B8050 == 0
  {
    *(this + 27) = Block;  // this+108 = Block
    v4 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
    nengine__CNFrame__vmt20(v4, 211);
    *(this + 28) = this;  // this+112 = this
    pMem = operator new(0xE4u);  // 堆分配 228 字节对象
    if ( pMem != nullptr )  // 若 pMem 非空
      v6 = sub_43C060((int)pMem, 9, -1);  // 结果 = nengine::CNEdit 构造
    else
      v6 = 0;
    *(this + 29) = v6;  // this+116 = v6
    dword_9D3BD8 = dword_99FCCC;
    *(uint32_t *)(*(this + 29) + 128) = -5512193;  // this+29 pSessionCtx
    sub_69A5F0((uint32_t *)*(this + 29), 38, 17);  // 调 sub_69A5F0
    sub_69A840(*(this + 29));  // 调 sub_69A840
    pMem2 = operator new(0x84u);  // 堆分配 132 字节对象
    if ( pMem2 != nullptr )  // 若 pMem2 非空
      v8 = sub_43C410(pMem2, v4, 9, 10, 11, 9, 0, 0);  // 结果 = nengine::CNButton 构造
    else
      v8 = nullptr;  // v8 = nullptr 空指针
    *(this + 30) = v8;  // this+120 = v8
    sub_69A5F0(v8, 25, 41);  // 调 sub_69A5F0
    sub_69A840(*(this + 30));  // 调 sub_69A840
    pMem3 = operator new(0x84u);  // 堆分配 132 字节对象
    if ( pMem3 != nullptr )  // 若 pMem3 非空
      v10 = sub_43C410(pMem3, v4, 12, 13, 14, 12, 0, 0);  // 结果 = nengine::CNButton 构造
    else
      v10 = nullptr;  // v10 = nullptr 空指针
    *(this + 31) = v10;  // this+124 = v10
    sub_69A5F0(v10, 86, 41);  // 调 sub_69A5F0
    sub_69A840(*(this + 31));  // 调 sub_69A840
    dword_9B8050 = (int)this;
    return sub_544A10(this);  // 输入框取值
  }
  return result;
}



// ------------------------------------------------------------
// 0x544FC0 sub_544FC0 —— 18 行小辅助
// ------------------------------------------------------------
// 大白话：摆摊光标状态复位：+44 可见标记置 1、+60=255（透明度/帧参数【推断】），其余状态清零。
int /*thiscall*/ sub_544FC0(int this)  // 函数: 18 行小辅助
{
  *(uint32_t *)(this + 4) = 0;  // this+4 = 0
  *(uint32_t *)(this + 8) = 0;  // this+8 = 0
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint8_t *)(this + 44) = 1;  // this+44 = 1
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  *(uint32_t *)(this + 52) = 0;  // this+52 = 0
  *(uint32_t *)(this + 56) = 0;  // this+56 = 0
  *(uint32_t *)(this + 60) = 255;  // this+60 = 255
  return 0;
}



// ------------------------------------------------------------
// 0x544FE0 sub_544FE0 —— 光标辅助（699000 时钟）
// ------------------------------------------------------------
// 大白话：光标逐帧更新：鼠标位置(+48/+52)变化（或按键/场景态满足）时重置 699000 时钟；
// +44 = 距上次移动不足 2000ms（静止提示光标窗口期【推断】）。
int /*thiscall*/ sub_544FE0(int this)  // 函数: 光标辅助（699000 时钟）
{
  bool fld_30; // zf
  LONG y; // ecx
  int fld_28; // eax
  int v5; // eax
  int result; // eax

  fld_30 = *(uint32_t *)(this + 48) == pt.x;  // this+48 UDP 上报使能位
  y = pt.y;
  if ( !fld_30 || *(uint32_t *)(this + 52) != pt.y )  // 若 !fld_30 || *(uint32_t *)(this + 52) != pt.y
  {
    *(uint32_t *)(this + 48) = pt.x;  // this+48 = pt.x
    *(uint32_t *)(this + 52) = y;  // this+52 = y
LABEL_12:
    *(uint32_t *)(this + 56) = sub_699000(this + 12);  // clock_now(clk)
    goto LABEL_13;  // 跳转 LABEL_13
  }
  if ( byte_89D274 != 0 )  // 若 byte_89D274 != 0
    goto LABEL_12;  // 跳转 LABEL_12
  if ( byte_89D275 != 0 )  // 若 byte_89D275 != 0
    goto LABEL_12;  // 跳转 LABEL_12
  fld_28 = *(uint32_t *)(this + 40);  // fld_28 = this+40
  if ( *(uint32_t *)(fld_28 + 104) != 12 )  // 若 *(uint32_t *)(fld_28 + 104) != 12
    goto LABEL_12;  // 跳转 LABEL_12
  if ( *(uint32_t *)(fld_28 + 108) != 12 )  // 若 *(uint32_t *)(fld_28 + 108) != 12
    goto LABEL_12;  // 跳转 LABEL_12
  v5 = *(uint32_t *)(dword_8F7A24 + 12);  // 全局 dword_8F7A24 = 登录/选区管理器
  if ( v5 == 5 || v5 == 0 || v5 == 2 )  // 若 v5 == 5 || v5 == 0 || v5 == 2
    goto LABEL_12;  // 跳转 LABEL_12
LABEL_13:
  result = sub_699000(this + 12);  // 【clock_now(clk)】
  *(uint8_t *)(this + 44) = result < *(uint32_t *)(this + 56) + 2000;  // this+44 = result < *(uint32_t *)(this + 56) + 2000
  return result;
}



// ============================================================
// 【分区 7】摆摊光标 CNRDCursor（0x545070-0x545400）
// vmt0 加载 Character/Common/PrivateStore/Donkey/Store.img（小毛驴商店贴图）。
// ============================================================
// ------------------------------------------------------------
// 0x545070 sub_545070 —— 光标列表构建（45B1C0 + 699000 + 418DD0，105 行）
// ------------------------------------------------------------
// 大白话：按状态 nArg4 选光标精灵号：城镇摆摊可交易态(45B1C0 命中)→120~123 动画帧
// （699000 时钟/180ms 取模 4 帧；虚表+40(18) 判定用 124），17→4~8 帧、6→9、3/4→67、5→71 等。
int /*thiscall*/ sub_545070(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 光标列表构建（45B1C0 + 699000 + 418DD0，105 行）
{
  int pThis_C; // esi
  int pObj; // eax
  int v7; // esi
  int fld_e60; // edi
  int result; // eax

  pThis_C = 0;
  if ( nArg4 == 0 )  // 若 nArg4 == 0
  {
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 && sub_45B1C0(*(uint32_t **)(dword_8F7A24 + 20)) != 0 )  // 取 ·+152 登记对象（失联则清零）
    {
      pObj = sub_45B1C0(*(uint32_t **)(dword_8F7A24 + 20));  // 结果 = 取 ·+152 登记对象（失联则清零）
      v7 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 18) != 0 ? 124 : 120;  // 虚槽+40 CNRDAvatarInventoryWindow__vmt28 槽（548E20/4872A0/549000/4868
      pThis_C = sub_699000((int)(this + 12)) / 180 % 4 + v7;  // 【clock_now(clk)】
      goto LABEL_42;  // 跳转 LABEL_42
    }
  }
  else if ( nArg4 != 16 && nArg4 != 1 && nArg4 != 2 )  // 否则若 nArg4 != 16 && nArg4 != 1 && nArg4 != 2
  {
    if ( nArg4 == 6 )  // 若 nArg4 == 6
    {
      pThis_C = 9;
    }
    else if ( nArg4 == 17 )  // 否则若 nArg4 == 17
    {
      pThis_C = sub_699000((int)(this + 12)) / 180 % 5 + 4;  // 【clock_now(clk)】
    }
    else
    {
      switch ( nArg4 )  // 分支：按 nArg4 分派
      {
        case 3:  // case 3
        case 4:  // case 4
          pThis_C = 67;
          break;
        case 5:  // case 5
          pThis_C = 71;
          break;
        case 7:  // case 7
          pThis_C = 117;
          break;
        case 8:  // case 8
          pThis_C = 134;
          break;
        case 9:  // case 9
          pThis_C = 113;
          break;
        case 10:  // case 10
          pThis_C = 160;
          break;
        case 11:  // case 11
          pThis_C = 164;
          break;
        case 12:  // case 12
          pThis_C = 172;
          break;
        case 13:  // case 13
          pThis_C = 168;
          break;
        case 14:  // case 14
          pThis_C = 196;
          break;
        case 15:  // case 15
          pThis_C = 200;
          break;
        case 18:  // case 18
          pThis_C = 208;
          break;
        case 19:  // case 19
          pThis_C = 204;
          break;
        default:
          break;
      }
      if ( dword_89D26C != 1 )  // 若 dword_89D26C != 1
        pThis_C += dword_724798[sub_699000((int)(this + 12)) / 100 % 10];  // 【clock_now(clk)】
    }
LABEL_42:
    fld_e60 = (*(this + 60) << 24) | 0xFFFFFF;  // this+60 fade 值
    result = sub_418DD0(pThis_C);  // 调 sub_418DD0
    if ( result != 0 )  // 若 result != 0
      return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
               result,
               nArg2,
               nArg3,
               dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
               1065353216,
               1065353216,
               0,
               fld_e60,
               1333788672,
               1333788672);
    return result;
  }
  pThis_C = 63 - (dword_89D26C != 1);
  goto LABEL_42;  // 跳转 LABEL_42
}



// ------------------------------------------------------------
// 0x545290 CNRDCursor__vmt0 —— CNRDCursor__vmt0 构造：加载 Character/Common/PrivateStore/Donkey/Store.img 小毛驴贴图（418DD0/43B560）
// ------------------------------------------------------------
// 大白话：摆摊光标构造：加载 Character/Common/PrivateStore/Donkey/Store.img 小毛驴商店贴图。
char /*thiscall*/ CNRDCursor__vmt0(int this, int nArg2)  // 函数: CNRDCursor__vmt0 构造：加载 Character/Common/PrivateStore/Donkey/Store.img 小毛驴贴图（418DD0/43B560）
{
  char result; // al
  uint8_t *pThis; // ebx
  int pDragObj; // eax  | +0x0028 → 拖动对象（CNRDCursor；va=00545290）
  int v5; // ecx
  LONG x; // esi
  LONG y; // edi
  uint8_t v8; // bl
  int v9; // eax
  uint32_t *v10; // edx
  int v12; // [esp+8h] [ebp-4h]

  result = nArg2;
  pThis = (uint8_t *)this;
  if ( nArg2 == *(uint32_t *)(this + 4) )  // 判定 “+4 宿主窗口”
  {
    result = *(uint8_t *)(this + 44);  // 读 result = this+44（光标激活位）
    if ( result != 0 )  // 若 result != 0
    {
      pDragObj = *(uint32_t *)(this + 40);  // 读 fld_28 = this+40（拖动对象）
      v5 = *(uint32_t *)(pDragObj + 2504);  // v5 = fld_28+2504
      x = pt.x;
      y = pt.y;
      v12 = v5;
      if ( v5 == 1 || v5 == 2 )  // 若 v5 == 1 || v5 == 2
      {
        v10 = *(uint32_t **)(pDragObj + 2520);  // fld_28=this+40 pDragObj
        if ( v10 == nullptr )  // 若 v10 为空
          return sub_545070(pThis, x, y, v5);  // 光标列表构建
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(*v10 + 152))(  // 虚调用 vt+152
          v10,
          pt.x - (v10[9] >> 1),
          pt.y - (*(uint32_t *)(*(uint32_t *)(pDragObj + 2520) + 40) >> 1),  // fld_28=this+40 pDragObj
          dword_79C0B0);  // dword_79C0B0（文本/图像绘制对象）
      }
      else
      {
        if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 || v5 != 16 )  // 全局 dword_8F7A24 = 登录/选区管理器
          return sub_545070(pThis, x, y, v5);  // 光标列表构建
        v8 = (uint64_t)(sin((double)(sub_699000((int)(pThis + 12)) / 25 % 36) * 0.1745329251994444) * 50.0 + 150.0);  // 【clock_now(clk)】
        (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚槽+60 CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行：4BE520 + 48
          dword_8F84B8,
          "Character/Common/PrivateStore/Donkey/Store.img");  // 字符串 “Character/Common/PrivateStore/Donkey/Store.i”
        v9 = sub_418DD0(3);  // 调 sub_418DD0
        sub_43B560(  // 绘制转发（vt+128）
          (void *)dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          x - (*(uint32_t *)(v9 + 20) >> 1),
          y - ((unsigned int)(3 * *(uint32_t *)(v9 + 24)) >> 1),
          v9,
          1065353216,
          1065353216,
          0,
          (v8 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
        pThis = (uint8_t *)this;
      }
      v5 = v12;
      return sub_545070(pThis, x, y, v5);  // 光标列表构建
    }
  }
  return result;  // result=this+44 bCursorOn
}



// ============================================================
// 【分区 8】摆摊辅助与社区菜单（0x545400-0x546030）
// 输入框取值/判定 0x545510/0x545590（供各窗口 vmt8 调用）；
// 社区菜单绘制 CNRDCommunityMenu__vmt0 在 0x5458F0（186 行）。
// ============================================================
// ------------------------------------------------------------
// 0x545400 sub_545400 —— 光标数据清理（426BD0 + 698F90）
// ------------------------------------------------------------
// 大白话：光标对象释放：426BD0 析构 + 698F90 清动画事件标记。
char /*thiscall*/ sub_545400(uint32_t *this, int nArg2)  // 函数: 光标数据清理（426BD0 + 698F90）
{
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  char result; // al

  pMem = operator new(0x68u);  // 堆分配 104 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v4 = sub_426BD0(pMem);  // 结果 = nengine::IControl 构造
  else
    v4 = nullptr;  // v4 = nullptr 空指针
  *(this + 1) = v4;  // this+4 = v4
  *((uint32_t *)v4 + 17) = this;
  *(this + 2) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 12);  // this+8 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  result = sub_698F90((int)(this + 3), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(this + 10) = nArg2;  // this+40 = nArg2
  return result;
}



// ------------------------------------------------------------
// 0x545480 sub_545480 —— 31 行小辅助
// ------------------------------------------------------------
int /*thiscall*/ sub_545480(uint32_t *this)  // 函数: 31 行小辅助
{
  int result; // eax
  uint32_t *pThis_4; // esi
  uint8_t *pThis_6A; // edx

  *(this + 1) = 0;  // this+4 = 0
  *(this + 2) = 0;  // this+8 = 0
  *(this + 3) = 0;  // this+12 = 0
  result = 0;
  pThis_4 = this + 4;  // this+4 宿主对象
  pThis_6A = (char *)this + 106;  // this+106 模块时钟解冻门
  do
  {
    *pThis_4 = 0;  // *pThis_4 写入 0
    *(pThis_6A - 1) = 0;  // pThis_6A=this+106 模块时钟解冻门
    *pThis_6A = 0;  // *pThis_6A 写入 0
    *((uint8_t *)this + result++ + 232) = 0;
    ++pThis_4;  // 自增pThis_4
    pThis_6A += 28;  // pThis_6A=this+106 模块时钟解冻门
  }
  while ( result < 5 );  // 当 result < 5 循环
  *(this + 22) = 5;  // this+88 = 5
  return result;
}



// ------------------------------------------------------------
// 0x5454C0 sub_5454C0 —— 31 行小辅助 2
// ------------------------------------------------------------
int /*thiscall*/ sub_5454C0(uint32_t *this)  // 函数: 31 行小辅助 2
{
  int (/*thiscall*/ ***fld_e2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e3)(uint32_t, int); // ecx
  uint32_t *pThis_4; // esi
  int i; // edi

  fld_e2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  if ( fld_e2 != nullptr )  // 若 fld_e2 非空
    result = (**fld_e2)(fld_e2, 1);
  fld_e3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  *(this + 2) = 0;  // this+8 = 0
  if ( fld_e3 != nullptr )  // 若 fld_e3 非空
    result = (**fld_e3)(fld_e3, 1);
  *(this + 3) = 0;  // this+12 = 0
  pThis_4 = this + 4;  // this+4 宿主对象
  for ( i = 5; i != 0; --i )  // 循环：i = 5; i != 0; --i
  {
    if ( *pThis_4 != 0 )  // 若 *pThis_4 != 0
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_4)(*pThis_4, 1);  // pThis_4=this+4 宿主对象
    *pThis_4++ = 0;  // *pThis_4++ 写入 0
  }
  return result;
}



// ------------------------------------------------------------
// 0x545510 sub_545510 —— 输入框取值（25 行——社区/摆摊/组队窗口共用的文本框读取）
// ------------------------------------------------------------
// 大白话：文本框输入合法性判定（社区/摆摊/组队窗共用，按 nArg1 字符过滤）。
bool /*stdcall*/ sub_545510(int nArg1)  // 函数: 输入框取值（25 行——社区/摆摊/组队窗口共用的文本框读取）
{
  switch ( nArg1 )  // 分支：按 nArg1 分派
  {
    case 2:  // case 2
      return dword_9B9460 != 0;
    case 0:  // case 0
      return dword_9B945C != 0;
    case 3:  // case 3
      return dword_9B9458 != 0;
    case 4:  // case 4
      return dword_9B88C0 != 0;
    case 1:  // case 1
      return *(uint32_t *)(*((uint32_t *)dword_8F8528 + 633) + 28) == 1;  // 全局 dword_8F8528 = 消息/弹窗管理器
    default:
      break;
  }
  return false;
}



// ------------------------------------------------------------
// 0x545590 sub_545590 —— 输入判定（44E850，28 行）
// ------------------------------------------------------------
// 大白话：输入状态切换：44E850 登记输入焦点对象。
char /*thiscall*/ sub_545590(uint32_t **this, int nArg2)  // 函数: 输入判定（44E850，28 行）
{
  char result; // al

  result = nArg2;
  switch ( nArg2 )  // 分支：按 nArg2 分派
  {
    case 2:  // case 2
      return sub_44E850(*(this + 1), 1);  // 按池号批量回收活动对象
    case 0:  // case 0
      return sub_44E850(*(this + 1), 54);  // 按池号批量回收活动对象
    case 3:  // case 3
      return sub_44E850(*(this + 1), 5);  // 按池号批量回收活动对象
    case 4:  // case 4
      return sub_44E850(*(this + 1), 12);  // 按池号批量回收活动对象
    case 1:  // case 1
      return sub_44E850(*(this + 1), 61);  // 按池号批量回收活动对象
    default:
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x545610 sub_545610 —— 输入框刷新（545510/545590 + 422E70/44E8D0，69 行）
// ------------------------------------------------------------
// 大白话：输入框刷新：545510/545590 判定后 422E70 取串、44E8D0 登记显示。
char /*thiscall*/ sub_545610(int this, int nArg2)  // 函数: 输入框刷新（545510/545590 + 422E70/44E8D0，69 行）
{
  int v3; // eax
  int i; // esi
  char *v5; // eax

  LOBYTE(v3) = sub_545510(nArg2);  // 社区/摆摊/组队窗口共用的文本框读取
  if ( (uint8_t)v3 == 0 )  // 若 (uint8_t)v3 == 0
  {
    for ( i = 0; i < 5; ++i )  // 循环：i = 0; i < 5; ++i
      sub_545590((uint32_t **)this, i);  // 输入判定
    LOBYTE(v3) = dword_8F7C08;
    if ( dword_8F7C08 != 0 )  // 若 dword_8F7C08 != 0
    {
      v3 = *(uint32_t *)(dword_8F7C08 + 648);  // v3 = dword_8F7C08+648
      if ( v3 != 0 && *(uint8_t *)(v3 + 284) != 0 )  // 若 v3 != 0 && *(uint8_t *)(v3 + 284) != 0
      {
        switch ( nArg2 )  // 分支：按 nArg2 分派
        {
          case 0:  // case 0
            v5 = sub_422E70(1346);  // 调 sub_422E70
LABEL_13:
            LOBYTE(v3) = sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v5, 0);  // 对象池借出（按池号取可用对象）
            return v3;
          case 3:  // case 3
            v5 = sub_422E70(1344);  // 调 sub_422E70
            goto LABEL_13;  // 跳转 LABEL_13
          case 1:  // case 1
            v5 = sub_422E70(1901);  // 调 sub_422E70
            goto LABEL_13;  // 跳转 LABEL_13
          default:
            break;
        }
      }
    }
    if ( nArg2 == 2 )  // 若 nArg2 == 2
    {
      LOBYTE(v3) = sub_44E8D0(*(char **)(this + 4), (void *)1, 0, 0);  // 对象池借出（按池号取可用对象）
    }
    else if ( nArg2 != 0 )  // 否则若 nArg2 != 0
    {
      switch ( nArg2 )  // 分支：按 nArg2 分派
      {
        case 3:  // case 3
          LOBYTE(v3) = sub_44E8D0(*(char **)(this + 4), (void *)5, 0, 0);  // 对象池借出（按池号取可用对象）
          break;
        case 4:  // case 4
          LOBYTE(v3) = sub_44E8D0(*(char **)(this + 4), (void *)0xC, 0, 0);  // 对象池借出（按池号取可用对象）
          break;
        case 1:  // case 1
          LOBYTE(v3) = sub_44E8D0(*(char **)(this + 4), (void *)0x3D, 0, 0);  // 对象池借出（按池号取可用对象）
          break;
        default:
          break;
      }
    }
    else
    {
      LOBYTE(v3) = sub_44E8D0(*(char **)(this + 4), (void *)0x36, 0, 0);  // 对象池借出（按池号取可用对象）
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x545730 sub_545730 —— 输入框打开（41C590 + 545610 + 49EC10 + 69A5F0 定位）
// ------------------------------------------------------------
// 大白话：输入框打开：41C590 建控件、545610 刷新、49EC10 挂载、69A5F0 定位。
uint8_t /*thiscall*/ sub_545730(int *this)  // 函数: 输入框打开（41C590 + 545610 + 49EC10 + 69A5F0 定位）
{
  uint32_t *pThis_4; // edi
  int v3; // esi
  int v4; // esi
  uint32_t **pThis_422; // edi
  int v6; // esi
  int i; // ebx
  uint8_t result; // al
  uint32_t **pThis_42; // [esp+Ch] [ebp-4h]

  pThis_4 = this + 4;  // this+4 宿主对象
  v3 = 0;
  pThis_42 = (uint32_t **)(this + 4);  // this+4 宿主对象
  do
  {
    *(uint8_t *)(*pThis_4 + 16) = (uint8_t)sub_41C590(dword_8F7A24) == 0 || v3 != 3 && v3 != 1;  // 状态查询（this+348 == 4）
    ++v3;  // 自增v3
    ++pThis_4;  // 自增pThis_4
  }
  while ( v3 < 5 );  // 当 v3 < 5 循环
  if ( (uint8_t)sub_41C590(dword_8F7A24) == 0 )  // 状态查询（this+348 == 4）
  {
    v4 = 0;
    while ( !sub_545510(v4) )  // 当 !sub_545510(v4) 循环
    {
      if ( ++v4 >= 5 )  // 若 ++v4 >= 5
      {
        if ( *(this + 22) != 5 )  // 若 *(this + 22) != 5
          sub_545610((int)this, *(this + 22));  // 输入框刷新
        break;
      }
    }
  }
  if ( sub_49EC10(dword_8F8508) == 0 )  // 红黑树槽计数求和（12 字节槽取 +8 字段）
    *(uint8_t *)(*(this + 5) + 16) = 0;
  pThis_422 = pThis_42;  // pThis_42=this+4 宿主对象
  *(uint8_t *)(*(this + 5) + 16) = 0;
  v6 = 26;
  for ( i = 5; i != 0; --i )  // 循环：i = 5; i != 0; --i
  {
    result = *((uint8_t *)*pThis_422 + 16);
    if ( result != 0 )  // 若 result != 0
    {
      result = (uint8_t)sub_69A5F0(*pThis_422, 547, v6);  // 调 设位、sub_69A840 登记
      v6 += 28;
    }
    ++pThis_422;  // 自增pThis_422
  }
  return result;
}



// ------------------------------------------------------------
// 0x545800 sub_545800 —— 输入确认（CLICK_BUTTON1 音 + 545510/545590/545610）
// ------------------------------------------------------------
// 大白话：输入确认：播 CLICK_BUTTON1 音并经 545510/545590/545610 完成回显。
uint32_t */*thiscall*/ sub_545800(uint32_t **this)  // 输入确认（CLICK_BUTTON1 音 + 545510/545590/545610）
{
  int v2; // esi
  uint32_t **pThis_4; // ebx
  uint32_t *result; // eax

  v2 = 0;
  pThis_4 = this + 4;  // this+4 宿主对象
  do
  {
    result = *pThis_4;
    if ( *((uint8_t *)*pThis_4 + 17) != 0 && dword_79BE34 == result[3] )  // 若 *((uint8_t *)*pThis_4 + 17) != 0 && dword_79BE34 == result[3]
    {
      if ( sub_545510(v2) )  // 社区/摆摊/组队窗口共用的文本框读取
        sub_545590(this, v2);  // 输入判定
      else
        sub_545610((int)this, v2);  // 输入框刷新
      result = sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 字符串 “CLICK_BUTTON1”
    }
    ++v2;  // 自增v2
    ++pThis_4;  // 自增pThis_4
  }
  while ( v2 < 5 );  // 当 v2 < 5 循环
  return result;
}



// ------------------------------------------------------------
// 0x545860 sub_545860 —— 输入处理（545730 打开 + 44E850 状态）
// ------------------------------------------------------------
// 大白话：输入处理入口：545730 打开输入框，44E850 维护状态。
char /*thiscall*/ sub_545860(int this, int nArg2, int nArg3)  // 函数: 输入处理（545730 打开 + 44E850 状态）
{
  int v4; // edi
  bool v5; // zf
  char result; // al

  if ( nArg2 == 1 )  // 若 nArg2 == 1
  {
    v4 = 0;
    while ( !sub_545510(v4) )  // 当 !sub_545510(v4) 循环
    {
      if ( ++v4 >= 5 )  // 若 ++v4 >= 5
      {
        v4 = 5;
        break;
      }
    }
    *(uint32_t *)(this + 88) = v4;  // this+88 = v4
  }
  else
  {
    v5 = nArg3 == 1;
    if ( nArg3 != 1 )  // 若 nArg3 != 1
      goto LABEL_10;  // 跳转 LABEL_10
    sub_545730((int *)this);  // 输入框打开（41C590 + 545610 + 49EC10 + 69A5F0 定位）
  }
  v5 = nArg3 == 1;
LABEL_10:
  result = v5;
  *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = v5;  // this+12 物品类型号
  if ( nArg3 != 1 )  // 若 nArg3 != 1
  {
    sub_44E850(*(uint32_t **)(this + 4), 54);  // 按池号批量回收活动对象
    sub_44E850(*(uint32_t **)(this + 4), 1);  // 按池号批量回收活动对象
    sub_44E850(*(uint32_t **)(this + 4), 5);  // 按池号批量回收活动对象
    sub_44E850(*(uint32_t **)(this + 4), 12);  // 按池号批量回收活动对象
    return sub_44E850(*(uint32_t **)(this + 4), 61);  // 按池号批量回收活动对象
  }
  return result;
}



// ------------------------------------------------------------
// 0x5458F0 CNRDCommunityMenu__vmt0 —— CNRDCommunityMenu__vmt0 构造（186 行：568A70 + 69A4D0/491630 绘制 + 422E70 取串）
// ------------------------------------------------------------
// 大白话：社区菜单（CNRDCommunityMenu）构造：568A70 建菜单数据、69A4D0/491630 绘制、422E70 取串。
int /*thiscall*/ sub_5458F0(uint32_t *this, int pArg2)  // 【CNRDCommunityMenu__vmt0】
{
  uint32_t *pThis; // esi
  int v4; // eax
  const char *v5; // eax
  int result; // eax
  int v7; // ebx
  int v8; // eax
  unsigned int v9; // ecx
  long double v10; // st7
  int pObj3; // eax
  char v12; // al
  int v13; // esi
  int pObj2; // eax
  int v15; // edx
  int v16; // esi
  int pObj; // eax
  int v18; // ecx
  int v19; // esi
  int v20; // ebx
  int v21; // eax
  int *pThis_4; // [esp+10h] [ebp-9Ch]
  int v23; // [esp+10h] [ebp-9Ch]
  int v25; // [esp+18h] [ebp-94h]
  int v26; // [esp+18h] [ebp-94h]
  int pThis_17; // [esp+1Ch] [ebp-90h]
  int v28; // [esp+20h] [ebp-8Ch]
  int v29; // [esp+20h] [ebp-8Ch]
  int v30; // [esp+24h] [ebp-88h]
  int v31; // [esp+24h] [ebp-88h]
  int v32; // [esp+24h] [ebp-88h]
  char Buffer[128]; // [esp+28h] [ebp-84h] BYREF
  int dword_796E502; // [esp+A8h] [ebp-4h]
  uint32_t *pThis_42; // [esp+B4h] [ebp+8h]
  int *pThis_43; // [esp+B4h] [ebp+8h]

  pThis = this;
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  if ( pArg2 == *(this + 3) )  // 若 pArg2 == *(this + 3)
  {
    v4 = sub_568A70((uint8_t)byte_99FCD0, (uint8_t)byte_99FCD1);  // 结果 = 频道条目组装（568940/568800）
    if ( v4 != 0 )  // 若 v4 != 0
    {
      if ( *(uint32_t *)(v4 + 24) < 0x10u )  // 若 *(uint32_t *)(v4 + 24) < 0x10u
        v5 = (const char *)(v4 + 4);
      else
        v5 = *(const char **)(v4 + 4);
      sprintf(Buffer, "ch%02d.%s", (uint8_t)byte_99FCD1, v5);  // 字符串 “ch%02d.%s”
    }
    else
    {
      sprintf(Buffer, "ch%02d.", (uint8_t)byte_99FCD1);  // 字符串 “ch%02d.”
    }
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pThis + 9);  // 调用虚函数槽 +72
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      474,
      6,
      -6567706,
      Buffer);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
  }
  else
  {
    v7 = 0;
    v25 = 0;
    pThis_4 = this + 4;  // this+4 宿主对象
    pThis_42 = this + 4;  // this+4 宿主对象
    pThis_17 = (int)(this + 23);
    do
    {
      if ( pArg2 == *pThis_42 )  // 若 pArg2 == *pThis_42
      {
        sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
        v8 = sub_699000(pThis_17);  // 【clock_now(clk)】
        v28 = v8;
        if ( *(uint8_t *)(*pThis_42 + 17) != 0 && dword_79BE3C == *(uint32_t *)(*pThis_42 + 12) )  // 若 *(uint8_t *)(*pThis_42 + 17) != 0 && dword_79BE3C == *(uint32_..
        {
          if ( v8 == 0 )  // 若 v8 == 0
          {
            sub_698F90(pThis_17, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
            v8 = v28;
          }
          v9 = *((uint8_t *)pThis + v7 + 232) + 10;
          if ( v9 >= 0xD7 )  // 若 v9 >= 0xD7
            LOBYTE(v9) = -41;
          *((uint8_t *)pThis + v7 + 232) = v9;
          v10 = sin((double)(unsigned int)v8 * 0.006283185307179587) * 35.0 + (double)(uint8_t)v9;  // 调 sin（正弦）
        }
        else
        {
          if ( v8 != 0 )  // 若 v8 != 0
          {
            *(uint8_t *)(pThis_17 + 13) = 0;  // pThis_17+13 = 0
            *(uint8_t *)(pThis_17 + 14) = 0;  // pThis_17+14 = 0
            *((uint8_t *)pThis + v7 + 232) = -76;
          }
          else
          {
            *((uint8_t *)pThis + v7 + 232) = (*((uint8_t *)pThis + v7 + 232) - 10)  // CNRDCommunityMenu__vmt0 构造（186 行：568A70 + 69A4D0/491630 绘制 + 422E70 取串）
                                      & ((*((uint8_t *)pThis + v7 + 232) <= 0xAu) - 1);
          }
          v10 = (double)*((uint8_t *)pThis + v7 + 232);
        }
        if ( v10 > 0.0 )  // 若 v10 > 0.0
        {
          v29 = *(uint32_t *)(pArg2 + 24);  // v29 = pArg2+24
          v30 = *(uint32_t *)(pArg2 + 20);  // v30 = pArg2+20
          pObj3 = sub_418DD0(dword_7247D8[v7]);  // 调 sub_418DD0
          if ( pObj3 != 0 )  // 若 pObj3 != 0
          {
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
              pObj3,
              v30 - 44,
              v29 - 5,
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              1065353216,
              1065353216,
              0,
              ((uint8_t)(uint64_t)v10 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
            v7 = v25;
          }
        }
        v12 = sub_69A4D0(*pThis_42);  // 调 sub_69A4D0
        v13 = *(uint32_t *)(pArg2 + 24);  // v13 = pArg2+24
        v31 = *(uint32_t *)(pArg2 + 20);  // v31 = pArg2+20
        if ( v12 == 1 )  // 若 v12 == 1
          pObj2 = sub_418DD0(dword_7247EC[v7]);  // 调 sub_418DD0
        else
          pObj2 = sub_418DD0(dword_724800[v7]);  // 调 sub_418DD0
        if ( pObj2 != 0 )  // 若 pObj2 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v31, v13, dword_79C0B0);  // 调用虚函数槽 +152
        sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
        if ( (uint8_t)sub_69A4D0(*pThis_42) == 1 )  // 若 (uint8_t)sub_69A4D0(*pThis_42) == 1
        {
          v15 = dword_724814[v7];
        }
        else if ( *(uint8_t *)(*pThis_42 + 17) != 0 && dword_79BE3C == *(uint32_t *)(*pThis_42 + 12) )  // 否则若 *(uint8_t *)(*pThis_42 + 17) != 0 && dword_79BE3C == *(uint32_..
        {
          v15 = dword_724828[v7];
        }
        else
        {
          v15 = dword_72483C[v7];
        }
        v16 = *(uint32_t *)(pArg2 + 24);  // v16 = pArg2+24
        v32 = *(uint32_t *)(pArg2 + 20);  // v32 = pArg2+20
        pObj = sub_418DD0(v15);  // 调 sub_418DD0
        if ( pObj != 0 )  // 若 pObj != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v32, v16, dword_79C0B0);  // 调用虚函数槽 +152
        pThis = this;
      }
      v25 = ++v7;
      pThis_17 += 28;
      ++pThis_42;  // 自增pThis_42
    }
    while ( v7 < 5 );  // 当 v7 < 5 循环
    v18 = 0;
    v26 = 0;
    pThis_43 = pThis_4;  // pThis_4=this+4 宿主对象
    do
    {
      result = *pThis_43;
      if ( pArg2 == *pThis_43 && *(uint8_t *)(result + 17) != 0 && dword_79BE3C == *(uint32_t *)(result + 12) )  // 若 pArg2 == *pThis_43 && *(uint8_t *)(result + 17) != 0 && dword_..
      {
        v19 = *(uint32_t *)(result + 20);  // v19 = result+20
        v23 = *(uint32_t *)(result + 24);  // v23 = result+24
        v20 = sub_422E70(v18 + 2190);  // 调 sub_422E70
        v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v20);  // 调用虚函数槽 +16
        result = sub_4649B0(v19 - v21 - 10, v23 + 14, -1, -16777216, 4, v20, 0, 0, 1600, 0);  // 结果 = 带框文本上屏（静态一次性初始化）
        v18 = v26;
      }
      v26 = ++v18;
      ++pThis_43;  // 自增pThis_43
    }
    while ( v18 < 5 );  // 当 v18 < 5 循环
  }
  return result;
}


// ------------------------------------------------------------
// 0x545D80 sub_545D80 —— 社区菜单页绘制（43C250/69A5F0 + 426BD0/69A840/43C410，114 行）
// ------------------------------------------------------------
// 大白话：社区菜单页绘制：43C250/69A5F0 布局 + 426BD0/69A840/43C410 图像按钮。
int /*thiscall*/ sub_545D80(int this, int nArg2)  // 函数: 社区菜单页绘制（43C250/69A5F0 + 426BD0/69A840/43C410，114 行）
{
  int v3; // edi
  uint8_t *pMem; // eax
  uint8_t *v5; // eax
  uint8_t *pMem2; // eax
  uint8_t *v7; // eax
  uint32_t *pMem3; // eax
  uint32_t *v9; // eax
  uint32_t *pMem4; // eax
  uint32_t *v11; // eax
  uint32_t *pMem5; // eax
  uint32_t *v13; // eax
  uint32_t *pMem6; // eax
  uint32_t *v15; // eax
  uint32_t *pMem7; // eax
  uint32_t *v17; // eax
  uint32_t *pThis_10; // edi
  bool v19; // zf
  int result; // eax
  int fld_C; // [esp-4h] [ebp-20h]
  int Block; // [esp+Ch] [ebp-10h]
  int v23; // [esp+24h] [ebp+8h]

  *(uint32_t *)(this + 4) = nArg2;  // this+4 = nArg2
  v3 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  pMem = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v5 = sub_43C250(pMem, v3, 206);  // 结果 = nengine::CNFrame 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(uint32_t *)(this + 12) = v5;  // this+12 = v5
  *((uint32_t *)v5 + 17) = this;
  sub_69A5F0(*(uint32_t **)(this + 12), 456, 0);  // 调 sub_69A5F0
  pMem2 = operator new(0x68u);  // 堆分配 104 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v7 = sub_426BD0(pMem2);  // 结果 = nengine::IControl 构造
  else
    v7 = nullptr;  // v7 = nullptr 空指针
  fld_C = *(uint32_t *)(this + 12);  // fld_C = this+12
  *(uint32_t *)(this + 8) = v7;  // this+8 = v7
  sub_69A840(fld_C);  // 调 sub_69A840
  *(uint8_t *)(this + 36) = 0;  // this+36 = 0
  *(uint8_t *)(this + 37) = 0;  // this+37 = 0
  *(uint8_t *)(this + 38) = 0;  // this+38 = 0
  *(uint8_t *)(this + 39) = 0;  // this+39 = 0
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  *(uint32_t *)(this + 52) = 6;  // this+52 = 6
  *(uint32_t *)(this + 56) = 12;  // this+56 = 12
  *(uint32_t *)(this + 60) = 0;  // this+60 = 0
  *(uint32_t *)(this + 64) = 1600;  // this+64 = 1600
  *(uint32_t *)(this + 68) = 0;  // this+68 = 0
  *(uint32_t *)(this + 72) = 0;  // this+72 = 0
  *(uint32_t *)(this + 76) = 0;  // this+76 = 0
  *(uint32_t *)(this + 80) = 0;  // this+80 = 0
  *(uint32_t *)(this + 84) = 0;  // this+84 = 0
  *(uint32_t *)(this + 84) = dword_99FCCC;  // this+84 = dword_99FCCC
  *(uint32_t *)(this + 64) = 125;  // this+64 = 125
  *(uint32_t *)(this + 48) = 2;  // this+48 = 2
  pMem3 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    v9 = sub_43C410(pMem3, v3, 207, 219, 194, -1, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v9 = nullptr;  // v9 = nullptr 空指针
  *(uint32_t *)(this + 16) = v9;  // this+16 = v9
  pMem4 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    v11 = sub_43C410(pMem4, v3, 279, 280, 281, -1, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v11 = nullptr;  // v11 = nullptr 空指针
  *(uint32_t *)(this + 20) = v11;  // this+20 = v11
  pMem5 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem5 != nullptr )  // 若 pMem5 非空
    v13 = sub_43C410(pMem5, v3, 208, 220, 195, -1, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v13 = nullptr;  // v13 = nullptr 空指针
  *(uint32_t *)(this + 24) = v13;  // this+24 = v13
  pMem6 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem6 != nullptr )  // 若 pMem6 非空
    v15 = sub_43C410(pMem6, v3, 209, 221, 196, -1, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v15 = nullptr;  // v15 = nullptr 空指针
  *(uint32_t *)(this + 28) = v15;  // this+28 = v15
  pMem7 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem7 != nullptr )  // 若 pMem7 非空
    v17 = sub_43C410(pMem7, v3, 210, 222, 197, -1, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v17 = nullptr;  // v17 = nullptr 空指针
  *(uint32_t *)(this + 32) = v17;  // this+32 = v17
  v23 = 26;
  pThis_10 = (uint32_t *)(this + 16);  // this+16 频道型选中索引
  Block = 5;
  do
  {
    *(uint32_t *)(*pThis_10 + 68) = this;  // pThis_10=this+16 频道型选中索引
    *(uint8_t *)(*pThis_10 + 16) = 0;  // pThis_10=this+16 频道型选中索引
    sub_69A840(*pThis_10);  // 调 sub_69A840
    sub_69A5F0((uint32_t *)*pThis_10++, 547, v23);  // 调 sub_69A5F0
    v19 = Block == 1;
    v23 += 28;
    --Block;  // 自减Block
  }
  while ( !v19 );  // 当 !v19 循环
  result = *(uint32_t *)(this + 16);  // result = this+16
  *(uint8_t *)(result + 17) = 0;  // result+17 = 0
  *(uint8_t *)(*(uint32_t *)(this + 20) + 17) = 0;  // this+20 频道页号
  return result;  // result=this+16 频道型选中索引
}



// ============================================================
// 【分区 9】新手引导 CNRDTutorial（0x546030-0x5470A0）
// 指引箭头绘制 0x5464C0（MOVE_ARROW 音效）；引导主状态 CNRDTutorial__vmt0 在 0x5468B0；
// 引导主状态（241 行）；0x546E10=引导步骤推进。
// ============================================================
// ------------------------------------------------------------
// 0x546030 sub_546030 —— 22 行小辅助
// ------------------------------------------------------------
// 大白话：22 行小辅助（引导状态读写）。
int /*thiscall*/ sub_546030(int this)  // 函数: 22 行小辅助
{
  *(uint32_t *)(this + 4) = 0;  // this+4 = 0
  *(uint32_t *)(this + 8) = 0;  // this+8 = 0
  *(uint32_t *)(this + 12) = 0;  // this+12 = 0
  *(uint32_t *)(this + 16) = 11;  // this+16 = 11
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  *(uint32_t *)(this + 53) = 0;  // this+53 = 0
  *(uint32_t *)(this + 57) = 0;  // this+57 = 0
  *(uint16_t *)(this + 61) = 0;  // this+61 = 0
  *(uint8_t *)(this + 63) = 0;  // this+63 = 0
  *(uint8_t *)(this + 64) = 0;  // this+64 = 0
  *(uint8_t *)(this + 65) = 0;  // this+65 = 0
  *(uint8_t *)(this + 52) = 0;  // this+52 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x546060 sub_546060 —— 17 行小辅助
// ------------------------------------------------------------
// 大白话：17 行小辅助（引导状态读写）。
int /*thiscall*/ sub_546060(uint32_t *this)  // 函数: 17 行小辅助
{
  int (/*thiscall*/ ***fld_e2)(uint32_t, int); // ecx
  int result; // eax

  fld_e2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  if ( fld_e2 != nullptr )  // 若 fld_e2 非空
    result = (**fld_e2)(fld_e2, 1);
  *(this + 2) = 0;  // this+8 = 0
  return result;
}



// ------------------------------------------------------------
// 0x546080 sub_546080 —— 10 行小辅助
// ------------------------------------------------------------
// 大白话：10 行小辅助（引导标记读取）。
bool /*stdcall*/ sub_546080(int nArg1)  // 函数: 10 行小辅助
{
  return nArg1 == 1016;
}



// ------------------------------------------------------------
// 0x5460A0 sub_5460A0 —— 引导辅助（44E8D0）
// ------------------------------------------------------------
// 大白话：引导辅助：44E8D0 登记引导对象。
char /*thiscall*/ sub_5460A0(char **this, int nArg2, int nArg3)  // 函数: 引导辅助（44E8D0）
{
  if ( nArg2 == 1 )  // 若 nArg2 == 1
  {
    if ( nArg3 == 1 )  // 若 nArg3 == 1
    {
      sub_44E8D0(*(this + 1), nullptr, 0, 0);  // 对象池借出（按池号取可用对象）
      return 1;
    }
  }
  else if ( nArg2 == 2 && nArg3 == 1 )  // 否则若 nArg2 == 2 && nArg3 == 1
  {
    sub_44E8D0(*(this + 1), nullptr, 0, 4);  // 对象池借出（按池号取可用对象）
    return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x5460F0 sub_5460F0 —— 引导辅助 2（44E8D0）
// ------------------------------------------------------------
// 大白话：引导辅助 2：44E8D0 登记引导对象（变体）。
char /*stdcall*/ sub_5460F0(int nArg1)  // 函数: 引导辅助 2（44E8D0）
{
  if ( nArg1 != 2 )  // 若 nArg1 != 2
    return 0;
  sub_44E8D0((char *)dword_8F8528, nullptr, 0, 3);  // 对象池借出（按池号取可用对象）
  return 1;
}



// ------------------------------------------------------------
// 0x546120 sub_546120 —— 引导辅助 3（429830 + 41A5E0 + 44E8D0）
// ------------------------------------------------------------
// 大白话：引导辅助 3：429830 动画 + 41A5E0 清理 + 44E8D0 登记。
char /*thiscall*/ sub_546120(uint8_t *this)  // 函数: 引导辅助 3（429830 + 41A5E0 + 44E8D0）
{
  int v2; // eax

  v2 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // 结果 = 表按键查找（uint16）
  if ( sub_41A5E0(v2 + 53) > 6 || *(this + 64) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    return 0;
  sub_44E8D0((char *)dword_8F8528, nullptr, 0, 5);  // 对象池借出（按池号取可用对象）
  *(this + 64) = 1;  // this+256 = 1
  return 1;
}



// ------------------------------------------------------------
// 0x546170 sub_546170 —— 引导辅助 4（429830 + 41A5E0 + 44E8D0）
// ------------------------------------------------------------
// 大白话：引导辅助 4：429830 动画 + 41A5E0 清理 + 44E8D0 登记（变体）。
char /*thiscall*/ sub_546170(uint8_t *this)  // 函数: 引导辅助 4（429830 + 41A5E0 + 44E8D0）
{
  int v2; // eax

  v2 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // 结果 = 表按键查找（uint16）
  if ( sub_41A5E0(v2 + 53) > 6 || *(this + 65) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    return 0;
  sub_44E8D0((char *)dword_8F8528, nullptr, 0, 6);  // 对象池借出（按池号取可用对象）
  *(this + 65) = 1;  // this+260 = 1
  return 1;
}



// ------------------------------------------------------------
// 0x5461C0 sub_5461C0 —— 引导文本复位（698F90）
// ------------------------------------------------------------
// 大白话：引导文本复位：698F90 清文本事件。
char /*thiscall*/ sub_5461C0(uint32_t *this, int nArg2)  // 函数: 引导文本复位（698F90）
{
  int pThis_5; // ecx
  char result; // al

  pThis_5 = (int)(this + 5);
  *(this + 4) = nArg2;  // this+16 = nArg2
  *(uint8_t *)(pThis_5 + 13) = 0;  // pThis_5+13 = 0
  *(uint8_t *)(pThis_5 + 14) = 0;  // pThis_5+14 = 0
  result = sub_698F90(pThis_5, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(this + 12) = 0;  // this+48 = 0
  return result;
}



// ------------------------------------------------------------
// 0x5461F0 sub_5461F0 —— 引导气泡绘制（45E490/45E4D0 + 491530/491630 批次，103 行）
// ------------------------------------------------------------
// 大白话：引导气泡绘制：45E490/45E4D0 建气泡控件，491530/491630 批次渲染。
int /*thiscall*/ sub_5461F0(void *this, int nArg2)  // 函数: 引导气泡绘制（45E490/45E4D0 + 491530/491630 批次，103 行）
{
  uint64_t v2; // rax
  int pObj4; // esi
  int v4; // eax
  int v5; // edi
  int pObj3; // esi
  int v7; // eax
  int v8; // esi
  int v9; // esi
  int pObj; // eax
  int v11; // ebx
  int pThis_14; // eax
  int v13; // et2
  double v14; // st7
  int pObj2; // eax
  int v17; // [esp-18h] [ebp-1Ch]
  int v18; // [esp-14h] [ebp-18h]
  int v19; // [esp-10h] [ebp-14h]

  LODWORD(v2) = dword_8F7C08;
  if ( dword_8F7C08 == 0 )  // 若 dword_8F7C08 == 0
    return v2;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调用虚函数槽 +120
  pObj4 = dword_8F7C08;  // dword_8F7C08（副玩家/观战者）
  v19 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C08 + 36))() + 8);  // 虚槽+36 CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605840/64F340/5C6
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 120))(pObj4);  // 调用虚函数槽 +120
  v5 = sub_45E490(v4, v19) - 46;  // 结果 = 屏幕 y → 演出层坐标（减基线）
  pObj3 = dword_8F7C08;  // dword_8F7C08（副玩家/观战者）
  v18 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C08 + 36))() + 8);  // 虚槽+36 CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605840/64F340/5C6
  v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 128))(pObj3);  // 调用虚函数槽 +128
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 124))(pObj3);  // 调用虚函数槽 +124
  v8 = sub_45E4D0(v7, v17, v18, 1.0);  // 结果 = 带比例的回换算（nArg2 - nArg3*f + 120）
  v9 = -110 - (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C08 + 192))(dword_8F7C08) + v8;  // 调虚函数 vt+192
  pObj = sub_418DD0(14);  // 调 sub_418DD0
  if ( pObj != 0 )  // 若 pObj != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v5, v9, dword_79C0B0);  // 调用虚函数槽 +152
  LOBYTE(v11) = -1;
  pThis_14 = sub_699000((int)this + 20);  // 【clock_now(clk)】
  v13 = pThis_14 % 2000;
  LODWORD(v2) = pThis_14 / 2000;
  HIDWORD(v2) = v13;
  if ( v13 < 500 )  // 若 v13 < 500
  {
    v14 = sub_4049C0(0.0, 255.0, SHIDWORD(v2), 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
LABEL_9:
    v2 = (uint64_t)v14;
    v11 = (uint64_t)v14;
    if ( v11 == 0 )  // 若 v11 == 0
      return v2;
    goto LABEL_10;  // 跳转 LABEL_10
  }
  if ( SHIDWORD(v2) >= 1100 )  // 若 SHIDWORD(v2) >= 1100
  {
    if ( SHIDWORD(v2) >= 1600 )  // 若 SHIDWORD(v2) >= 1600
      return v2;
    v14 = sub_4049C0(255.0, 0.0, HIDWORD(v2) - 1100, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    goto LABEL_9;  // 跳转 LABEL_9
  }
LABEL_10:
  switch ( nArg2 )  // 分支：按 nArg2 分派
  {
    case 0:  // case 0
      v5 += 9;
      goto LABEL_15;  // 跳转 LABEL_15
    case 1:  // case 1
      v5 += 59;
      goto LABEL_15;  // 跳转 LABEL_15
    case 2:  // case 2
      v5 += 34;
      v9 += 8;
      break;
    case 3:  // case 3
      v5 += 34;
LABEL_15:
      v9 += 33;
      break;
    default:
      break;
  }
  sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
  pObj2 = sub_418DD0(21);  // 调 sub_418DD0
  if ( pObj2 != 0 )  // 若 pObj2 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj2,
      v5,
      v9,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      ((uint8_t)v11 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  LODWORD(v2) = sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
  return v2;
}



// ------------------------------------------------------------
// 0x5463C0 sub_5463C0 —— 引导指示绘制（699000 + 4049C0 + 491530/491630，42 行）
// ------------------------------------------------------------
// 大白话：引导指示绘制：699000 时钟选帧 + 4049C0 精灵，491530/491630 批次渲染。
int /*thiscall*/ sub_5463C0(void *this, int nArg2, int nArg3)  // 函数: 引导指示绘制（699000 + 4049C0 + 491530/491630，42 行）
{
  int pThis_14; // edx
  double v4; // st7
  int pObj; // eax
  int pObj2; // eax
  int result; // eax

  pThis_14 = sub_699000((int)this + 20) % 1000;  // 【clock_now(clk)】
  if ( pThis_14 >= 500 )  // 若 pThis_14 >= 500
    v4 = sub_4049C0(255.0, 100.0, pThis_14 - 500, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  else
    v4 = sub_4049C0(100.0, 255.0, pThis_14, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  pObj = sub_418DD0(26);  // 调 sub_418DD0
  if ( pObj != 0 )  // 若 pObj != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, nArg2, nArg3, dword_79C0B0);  // 调用虚函数槽 +152
  sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
  pObj2 = sub_418DD0(25);  // 调 sub_418DD0
  if ( pObj2 != 0 )  // 若 pObj2 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj2,
      nArg2,
      nArg3,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      ((uint8_t)(uint64_t)v4 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
  result = sub_418DD0(24);  // 调 sub_418DD0
  if ( result != 0 )  // 若 result != 0
    return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(result, nArg2, nArg3, dword_79C0B0);  // 调用虚函数槽 +152
  return result;
}



// ------------------------------------------------------------
// 0x5464C0 sub_5464C0 —— 指引箭头绘制：MOVE_ARROW 事件音（432EA0）+ 4049C0/418DD0 精灵
// ------------------------------------------------------------
// 大白话：新手指引箭头绘制：MOVE_ARROW 事件音(432EA0) + 4049C0/418DD0 精灵。
char */*thiscall*/ sub_5464C0(char **this, int nArg2, int nArg3, int nArg4)  // 指引箭头绘制：MOVE_ARROW 事件音（432EA0）+ 4049C0/418DD0 精
{
  int pThis_5; // esi
  int v5; // ebx
  int pThis_52; // edi
  int v7; // esi
  char *result; // eax

  pThis_5 = (int)(this + 5);
  v5 = 255;
  pThis_52 = sub_699000((int)(this + 5)) % 2000;  // 【clock_now(clk)】
  v7 = sub_699000(pThis_5) / 2000;  // 【clock_now(clk)】
  if ( pThis_52 >= 500 )  // 若 pThis_52 >= 500
  {
    if ( pThis_52 >= 1100 )  // 若 pThis_52 >= 1100
    {
      if ( pThis_52 >= 1600 )  // 若 pThis_52 >= 1600
        v5 = 0;
      else
        v5 = (uint64_t)sub_4049C0(255.0, 0.0, pThis_52 - 1100, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    }
    else
    {
      ++v7;  // 自增v7
    }
  }
  else
  {
    v5 = (uint64_t)sub_4049C0(0.0, 255.0, pThis_52, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  }
  result = *(this + 12);  // result = this+12
  if ( (int)result < v7 )  // 若 (int)result < v7
  {
    *(this + 12) = result + 1;  // this+48 = result + 1
    result = (char *)sub_432EA0("MOVE_ARROW", -1, 0, 0);  // 字符串 “MOVE_ARROW”
  }
  if ( v5 != 0 )  // 若 v5 != 0
  {
    result = (char *)sub_418DD0(nArg2);  // 调 资源句柄 (101)
    if ( result != nullptr )  // 若 result 非空
      return (char *)(*(int (/*thiscall*/ **)(char *, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(  // result=this+48 UDP 上报使能位
                       result,  // result=this+48 UDP 上报使能位
                       0,
                       0,
                       dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
                       1065353216,
                       1065353216,
                       0,
                       ((uint8_t)v5 << 24) | 0xFFFFFF,
                       1333788672,
                       1333788672);
  }
  return result;  // result=this+48 UDP 上报使能位
}



// ------------------------------------------------------------
// 0x5465E0 sub_5465E0 —— 引导辅助（698F90）
// ------------------------------------------------------------
// 大白话：引导辅助：698F90 清理。
int /*thiscall*/ sub_5465E0(int this)  // 函数: 引导辅助（698F90）
{
  int pThis_14; // ecx

  pThis_14 = this + 20;  // this+20 频道页号
  *(uint32_t *)(this + 16) = 1;  // this+16 = 1
  *(uint8_t *)(pThis_14 + 13) = 0;  // pThis_14+13 = 0
  *(uint8_t *)(pThis_14 + 14) = 0;  // pThis_14+14 = 0
  sub_698F90(pThis_14, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  *(uint32_t *)(this + 53) = 0;  // this+53 = 0
  *(uint32_t *)(this + 57) = 0;  // this+57 = 0
  *(uint16_t *)(this + 61) = 0;  // this+61 = 0
  *(uint8_t *)(this + 63) = 0;  // this+63 = 0
  *(uint8_t *)(this + 64) = 0;  // this+64 = 0
  *(uint8_t *)(this + 65) = 0;  // this+65 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x546620 sub_546620 —— 引导步骤查询（47B8D0 + 698F90）
// ------------------------------------------------------------
// 大白话：引导步骤查询：47B8D0 取当前步骤 + 698F90。
char /*thiscall*/ sub_546620(int this, int nArg2)  // 函数: 引导步骤查询（47B8D0 + 698F90）
{
  if ( nArg2 == 1016 )  // 若 nArg2 == 1016
  {
    sub_47B8D0((uint32_t *)dword_8F8540, 1016, 0);  // 调 sub_47B8D0
    return 1;
  }
  else
  {
    if ( *(uint32_t *)(this + 16) == 4 )  // 若 *(uint32_t *)(this + 16) == 4
    {
      *(uint32_t *)(this + 16) = 5;  // this+16 = 5
      *(uint8_t *)(this + 33) = 0;  // this+33 = 0
      *(uint8_t *)(this + 34) = 0;  // this+34 = 0
      sub_698F90(this + 20, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      *(uint32_t *)(this + 48) = 0;  // this+48 = 0
      *(uint8_t *)(this + 57) = 1;  // this+57 = 1
    }
    return 0;
  }
}



// ------------------------------------------------------------
// 0x546680 sub_546680 —— 引导辅助 2（698F90）
// ------------------------------------------------------------
// 大白话：引导辅助 2：698F90 清理（变体）。
char /*thiscall*/ sub_546680(int this, int nArg2)  // 函数: 引导辅助 2（698F90）
{
  char result; // al

  if ( nArg2 == 1016 && *(uint32_t *)(this + 16) == 2 )  // 若 nArg2 == 1016 && *(uint32_t *)(this + 16) == 2
  {
    *(uint32_t *)(this + 16) = 3;  // this+16 = 3
    *(uint8_t *)(this + 33) = 0;  // this+33 = 0
    *(uint8_t *)(this + 34) = 0;  // this+34 = 0
    result = sub_698F90(this + 20, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(uint32_t *)(this + 48) = 0;  // this+48 = 0
    *(uint8_t *)(this + 55) = 1;  // this+55 = 1
  }
  return result;
}



// ------------------------------------------------------------
// 0x5466C0 sub_5466C0 —— 引导辅助 3（698F90，40 行）
// ------------------------------------------------------------
// 大白话：引导辅助 3：698F90 清理（40 行，含状态分支）。
char /*thiscall*/ sub_5466C0(int this, int nArg2, int nArg3)  // 函数: 引导辅助 3（698F90，40 行）
{
  int fld_10; // eax
  int v5; // ecx
  char result; // al

  fld_10 = *(uint32_t *)(this + 16);  // fld_10 = this+16
  v5 = 0;
  if ( fld_10 == 1 )  // 若 fld_10 == 1
  {
    v5 = 1;
  }
  else if ( nArg3 == 2 )  // 否则若 nArg3 == 2
  {
    if ( fld_10 == 6 )  // 若 fld_10 == 6
    {
      *(uint8_t *)(this + 59) = 1;  // this+59 = 1
    }
    else if ( fld_10 == 9 )  // 否则若 fld_10 == 9
    {
      *(uint8_t *)(this + 62) = 1;  // this+62 = 1
    }
  }
  else if ( nArg3 == 3 && *(uint8_t *)(this + 60) == 0 )  // 否则若 nArg3 == 3 && *(uint8_t *)(this + 60) == 0
  {
    v5 = 7;
  }
  *(uint32_t *)(this + 16) = v5;  // this+16 = v5
  *(uint8_t *)(this + 33) = 0;  // this+33 = 0
  *(uint8_t *)(this + 34) = 0;  // this+34 = 0
  result = sub_698F90(this + 20, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  return result;
}



// ------------------------------------------------------------
// 0x546730 sub_546730 —— 引导步骤推进（45AFD0 + 698F90，93 行）
// ------------------------------------------------------------
// 大白话：引导步骤推进：45AFD0 触发下一步 + 698F90，93 行含步骤分支。
char /*thiscall*/ sub_546730(int this)  // 函数: 引导步骤推进（45AFD0 + 698F90，93 行）
{
  int v1; // eax
  int v3; // ecx
  int *v4; // eax
  int v5; // eax
  int fld_102; // edi
  int fld_10; // ecx
  int v8; // eax
  char result; // al

  v1 = *(uint32_t *)(dword_8F7A24 + 20);  // 全局 dword_8F7A24 = 登录/选区管理器
  v3 = *(uint32_t *)(v1 + 100);  // v3 = v1+100
  v4 = *(int **)(v1 + 104);
  if ( v4 != nullptr )  // 若 v4 非空
    v5 = *v4;
  else
    v5 = -1;
  fld_102 = 0;
  if ( v3 == 1 )  // 若 v3 == 1
  {
    fld_10 = *(uint32_t *)(this + 16);  // fld_10 = this+16
    if ( fld_10 == 8 || fld_10 == 10 || fld_10 == 9 )  // 若 fld_10 == 8 || fld_10 == 10 || fld_10 == 9
    {
      fld_102 = *(uint32_t *)(this + 16);  // fld_102 = this+16
    }
    else if ( v5 == 1 )  // 否则若 v5 == 1
    {
      if ( *(uint8_t *)(this + 55) == 0 )  // 若 *(uint8_t *)(this + 55) == 0
        fld_102 = 2;  // fld_102=this+16 频道型选中索引
    }
    else if ( v5 != 0 )  // 否则若 v5 != 0
    {
      if ( v5 == 2 )  // 若 v5 == 2
      {
        if ( *(uint8_t *)(this + 59) != 0 )  // 若 *(uint8_t *)(this + 59) != 0
        {
          if ( !sub_45AFD0(1) )  // 对象存在谓词（·sub_472F90(句柄) >= 1）
            fld_102 = 7;  // fld_102=this+16 频道型选中索引
          *(uint8_t *)(this + 58) = 1;  // this+58 = 1
        }
        else
        {
          fld_102 = 6;  // fld_102=this+16 频道型选中索引
          *(uint8_t *)(this + 58) = 1;  // this+58 = 1
        }
      }
    }
    else if ( *(uint8_t *)(this + 57) != 0 )  // 否则若 *(uint8_t *)(this + 57) != 0
    {
      if ( *(uint8_t *)(this + 58) == 0 )  // 若 *(uint8_t *)(this + 58) == 0
        fld_102 = 5;  // fld_102=this+16 频道型选中索引
      *(uint8_t *)(this + 56) = 1;  // this+56 = 1
    }
    else
    {
      fld_102 = 4;  // fld_102=this+16 频道型选中索引
      *(uint8_t *)(this + 56) = 1;  // this+56 = 1
    }
  }
  else if ( v3 == 2 )  // 否则若 v3 == 2
  {
    *(uint8_t *)(this + 63) = 1;  // this+63 = 1
  }
  if ( *(uint32_t *)(this + 16) == 7 )  // 若 *(uint32_t *)(this + 16) == 7
  {
    v8 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 24) + 220);  // 全局 dword_8F7A24 = 登录/选区管理器
    if ( v8 != 1 && v8 != 2 )  // 若 v8 != 1 && v8 != 2
    {
      *(uint32_t *)(this + 16) = 0;  // this+16 = 0
      *(uint8_t *)(this + 33) = 0;  // this+33 = 0
      *(uint8_t *)(this + 34) = 0;  // this+34 = 0
      sub_698F90(this + 20, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      *(uint32_t *)(this + 48) = 0;  // this+48 = 0
      *(uint32_t *)(this + 53) = 16843009;  // this+53 = 16843009
      *(uint32_t *)(this + 57) = 16843009;  // this+57 = 16843009
      *(uint16_t *)(this + 61) = 257;  // this+61 = 257
      *(uint8_t *)(this + 63) = 1;  // this+63 = 1
    }
  }
  *(uint32_t *)(this + 16) = fld_102;  // this+16 = fld_102
  *(uint8_t *)(this + 33) = 0;  // this+33 = 0
  *(uint8_t *)(this + 34) = 0;  // this+34 = 0
  result = sub_698F90(this + 20, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  return result;
}



// ------------------------------------------------------------
// 0x546840 sub_546840 —— 引导触发（56CFE0 频道选择 + 551500 + 44BBA0 显示）
// ------------------------------------------------------------
// 大白话：引导触发：56CFE0 频道选择复用 + 551500 + 44BBA0 显示窗口。
char /*thiscall*/ sub_546840(int this, int nArg2)  // 函数: 引导触发（56CFE0 频道选择 + 551500 + 44BBA0 显示）
{
  int v3; // eax

  if ( *(uint32_t *)(this + 16) != 8 || nArg2 != 1 )  // 若 *(uint32_t *)(this + 16) != 8 || nArg2 != 1
    return 0;
  v3 = sub_56CFE0(1);  // 结果 = 频道选择主入口
  sub_551500(v3);  // 任务文本联动（429830/472E30/5512D0）
  sub_44BBA0(*(uint32_t **)(this + 4), 3, 0);  // 窗口显示切换（WINDOW_SHOW 音效）
  *(uint32_t *)(this + 16) = 0;  // this+16 = 0
  *(uint8_t *)(this + 33) = 0;  // this+33 = 0
  *(uint8_t *)(this + 34) = 0;  // this+34 = 0
  sub_698F90(this + 20, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  *(uint8_t *)(this + 61) = 1;  // this+61 = 1
  return 1;
}



// ------------------------------------------------------------
// 0x5468B0 CNRDTutorial__vmt0 —— CNRDTutorial__vmt0 引导主状态（241 行：5463C0/5464C0/5461F0 绘制 + 425100/425A00 + 416D10/416CD0/416D50 文本）
// ------------------------------------------------------------
char /*thiscall*/ sub_5468B0(int *this, int nArg2)  // 【CNRDTutorial__vmt0】
{
  int fld_e4; // eax
  bool fld_e2; // zf
  int v5; // eax
  int v6; // edi
  int v7; // ebx
  int v8; // esi
  int pObj; // eax
  int v10; // eax
  int v11; // eax
  int v12; // esi
  int v13; // eax
  int *pThis2; // edi
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
  int dword_99FCCC2; // [esp+34h] [ebp-14h]
  int *pThis; // [esp+38h] [ebp-10h]
  int v36; // [esp+44h] [ebp-4h]
  char v37; // [esp+53h] [ebp+Bh]

  LOBYTE(fld_e4) = nArg2;
  fld_e2 = nArg2 == *(this + 2);
  pThis = this;
  if ( !fld_e2 )  // 若 !fld_e2
    return fld_e4;
  fld_e4 = *(this + 4);  // fld_e4 = this+4
  switch ( fld_e4 )  // 分支：按 fld_e4 分派
  {
    case 2:  // case 2
      LOBYTE(fld_e4) = sub_5463C0(this, 243, 106);  // 引导指示绘制
      return fld_e4;  // fld_e4=this+16 频道型选中索引
    case 3:  // case 3
      sub_5464C0(0, 1, 2);  // 指引箭头绘制：MOVE_ARROW 事件音（432EA0）+ 4049C0/418DD0 精
      LOBYTE(fld_e4) = sub_5461F0(this, 3);  // 引导气泡绘制
      return fld_e4;  // fld_e4=this+16 频道型选中索引
    case 4:  // case 4
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调用虚函数槽 +120
      v5 = sub_48C1C0(1);  // 结果 = 演出层纵向基线换算（按类型取字段乘百分位）
      sub_5463C0(this, 452 - v5, 141);  // 引导指示绘制
      fld_e4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C08 + 120))(dword_8F7C08);  // 调用虚函数槽 +120
      if ( fld_e4 >= 520 )  // 若 fld_e4 >= 520
        LOBYTE(fld_e4) = sub_5461F0(this, 0);  // 引导气泡绘制
      return fld_e4;  // fld_e4=this+16 频道型选中索引
    case 5:  // case 5
      sub_5464C0(11, 12, 13);  // 指引箭头绘制：MOVE_ARROW 事件音（432EA0）+ 4049C0/418DD0 精
LABEL_11:
      LOBYTE(fld_e4) = sub_5461F0(this, 1);  // 引导气泡绘制
      return fld_e4;  // fld_e4=this+16 频道型选中索引
    case 6:  // case 6
      sub_5464C0(7, 8, 9);  // 指引箭头绘制：MOVE_ARROW 事件音（432EA0）+ 4049C0/418DD0 精
      goto LABEL_11;  // 跳转 LABEL_11
    default:
      break;
  }
  if ( fld_e4 != 7 )  // 若 fld_e4 != 7
  {
    if ( fld_e4 != 8 )  // 若 fld_e4 != 8
    {
      if ( fld_e4 == 10 )  // 若 fld_e4 == 10
      {
        fld_e4 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 104);  // 全局 dword_8F7A24 = 登录/选区管理器
        if ( fld_e4 != 0 )  // 若 fld_e4 != 0
        {
          fld_e4 = *(uint32_t *)fld_e4;  // fld_e4 = fld_e4
          if ( fld_e4 == 0 || fld_e4 == 2 )  // 若 fld_e4 == 0 || fld_e4 == 2
            LOBYTE(fld_e4) = sub_5464C0(6, 4, 5);  // 指引箭头绘制：MOVE_ARROW 事件音（432EA0）+ 4049C0/418DD0 精
        }
      }
      else if ( fld_e4 == 9 )  // 否则若 fld_e4 == 9
      {
        fld_e4 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 104);  // 全局 dword_8F7A24 = 登录/选区管理器
        if ( fld_e4 != 0 )  // 若 fld_e4 != 0
        {
          fld_e4 = *(uint32_t *)fld_e4;  // fld_e4 = fld_e4
          if ( fld_e4 == 0 || fld_e4 == 2 )  // 若 fld_e4 == 0 || fld_e4 == 2
            LOBYTE(fld_e4) = sub_5464C0(10, 8, 9);  // 指引箭头绘制：MOVE_ARROW 事件音（432EA0）+ 4049C0/418DD0 精
        }
      }
      return fld_e4;  // fld_e4=this+16 频道型选中索引
    }
    v28 = *(int **)(*(uint32_t *)(dword_8F7A24 + 20) + 104);  // 全局 dword_8F7A24 = 登录/选区管理器
    if ( v28 != nullptr )  // 若 v28 非空
      v29 = *v28;
    else
      v29 = -1;
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调用虚函数槽 +120
    fld_e4 = sub_48C1C0(1);  // 结果 = 演出层纵向基线换算（按类型取字段乘百分位）
    if ( v29 != 0 )  // 若 v29 != 0
    {
      if ( v29 == 2 )  // 若 v29 == 2
        goto LABEL_57;  // 跳转 LABEL_57
    }
    else if ( fld_e4 < 472 )  // 否则若 fld_e4 < 472
    {
      LOBYTE(fld_e4) = sub_5463C0(this, 452 - fld_e4, 141);  // 引导指示绘制
      return fld_e4;  // fld_e4=this+16 频道型选中索引
    }
    if ( fld_e4 < 400 || v29 != 0 )  // 若 fld_e4 < 400 || v29 != 0
      return fld_e4;  // fld_e4=this+16 频道型选中索引
LABEL_57:
    LOBYTE(fld_e4) = sub_5464C0(3, 4, 5);  // 指引箭头绘制：MOVE_ARROW 事件音（432EA0）+ 4049C0/418DD0 精
    return fld_e4;  // fld_e4=this+16 频道型选中索引
  }
  v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);  // 虚槽+120 CNAuraMasterATDFSPEEDUp__vmt78 光环生效：AURA_POWER_SET 事件（76 行转发
  v7 = sub_425100(v6);  // 结果 = 容器长度（+30 组）
  v8 = 0;
  v37 = 0;
  if ( v7 > 0 )  // 若 v7 > 0
  {
    do
    {
      pObj = sub_425A00(v8);  // 结果 = 元素取值（+30 组）
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 289) != 0 )  // 虚槽+40 CNRDAvatarInventoryWindow__vmt28 槽（548E20/4872A0/549000/4868
        v37 = 1;
      ++v8;  // 自增v8
    }
    while ( v8 < v7 );  // 当 v8 < v7 循环
    if ( v37 != 0 )  // 若 v37 != 0
    {
      v10 = sub_418DD0(17);  // 调 sub_418DD0
      sub_40FC80(90, 90, v10);  // 贴图转发（目标对象虚发 +152(this, x, y)）
      v11 = sub_418DD0(16);  // 调 sub_418DD0
      sub_40FC80(90, 90, v11);  // 贴图转发（目标对象虚发 +152(this, x, y)）
      sub_416D10(v32);  // 绘制状态结构初始化（void 版）
      v36 = 0;
      sub_416CD0(v32);  // 【GDI 资源清理（DeleteObject 族）】
      dword_99FCCC2 = dword_99FCCC;
      v33 = -16777216;
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v32);  // 调用虚函数槽 +72
      v12 = *(uint32_t *)dword_79C0B0;  // v12 = dword_79C0B0
      v13 = sub_422E70(500);  // 调 sub_422E70
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(v12 + 80))(dword_79C0B0, 270, 185, -1, v13);  // 调用虚函数槽 +80
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
      v36 = -1;
      sub_416D50(v32);  // GDI 句柄释放 + 结构清零
    }
  }
  pThis2 = pThis;
  v15 = (int)(pThis + 5);
  if ( sub_699000((int)(pThis + 5)) < 500 && *((uint8_t *)pThis2 + 52) == 0 )  // 【clock_now(clk)】
  {
    v16 = sub_418DD0(23);  // 调 sub_418DD0
    LOBYTE(fld_e4) = sub_40FC80(0, 0, v16);  // 贴图转发（目标对象虚发 +152(this, x, y)）
    return fld_e4;  // fld_e4=this+16 频道型选中索引
  }
  if ( sub_699000(v15) < 13100 && *((uint8_t *)pThis2 + 52) == 0 )  // 【clock_now(clk)】
  {
    v17 = sub_418DD0(23);  // 调 sub_418DD0
    sub_40FC80(0, 0, v17);  // 贴图转发（目标对象虚发 +152(this, x, y)）
    v18 = sub_699000(v15);  // 【clock_now(clk)】
    v20 = (v18 - 500) / 300 % 14;
    fld_e4 = (v18 - 500) / 300 / 14;  // fld_e4=this+16 频道型选中索引
    v19 = v20;
    if ( v20 != 0 )  // 若 v20 != 0
    {
      if ( v19 == 2 )  // 若 v19 == 2
      {
        v21 = 1;
        v22 = 15;
      }
      else
      {
        if ( v19 != 4 )  // 若 v19 != 4
        {
          switch ( v19 )  // 分支：按 v19 分派
          {
            case 6:  // case 6
              v21 = 3;
              break;
            case 8:  // case 8
              v21 = 4;
              break;
            case 10:  // case 10
              v21 = 5;
              break;
            case 12:  // case 12
              v21 = 6;
              break;
            default:
              return fld_e4;  // fld_e4=this+16 频道型选中索引
          }
          goto LABEL_29;  // 跳转 LABEL_29
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
    v23 = sub_418DD0(v22);  // 调 sub_418DD0
    sub_40FC80(0, 0, v23);  // 贴图转发（目标对象虚发 +152(this, x, y)）
LABEL_29:
    sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    v24 = sub_418DD0(21);  // 调 sub_418DD0
    sub_40FC80(dword_724858[2 * v21], dword_72485C[2 * v21], v24);  // 贴图转发（目标对象虚发 +152(this, x, y)）
    LOBYTE(fld_e4) = sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
    return fld_e4;  // fld_e4=this+16 频道型选中索引
  }
  v25 = sub_699000(v15) < 14100;  // 【clock_now(clk)】
  LOBYTE(fld_e4) = *((uint8_t *)pThis2 + 52);  // fld_e4=this+16 频道型选中索引
  if ( v25 )  // 若 v25
  {
    if ( (uint8_t)fld_e4 == 0 )  // 若 (uint8_t)fld_e4 == 0
    {
      v26 = sub_699000(v15);  // 【clock_now(clk)】
      v31 = ((uint8_t)sub_423A80(255, 0, v26 - 13600, 500) << 24) | 0xFFFFFF;  // 结果 = 同上 int 版（FTOL 截断）
      v27 = sub_418DD0(23);  // 调 sub_418DD0
      LOBYTE(fld_e4) = sub_43B560(0, 0, v27, 1065353216, 1065353216, 0, v31, 1333788672, 1333788672);  // 绘制转发（vt+128）
    }
  }
  else if ( (uint8_t)fld_e4 == 0 )  // 否则若 (uint8_t)fld_e4 == 0
  {
    *((uint8_t *)pThis2 + 52) = 1;
  }
  return fld_e4;  // fld_e4=this+16 频道型选中索引
}


// ------------------------------------------------------------
// 0x546E10 sub_546E10 —— 引导步骤推进（472F90/472E30/47C080/47B6F0/461730/47B560，59 行）
// ------------------------------------------------------------
// 大白话：引导步骤推进实现：472F90/472E30/47C080/47B6F0/461730/47B560 系列状态调用。
char /*thiscall*/ sub_546E10(int this)  // 函数: 引导步骤推进（472F90/472E30/47C080/47B6F0/461730/47B560，59 行）
{
  char result; // al
  int v3; // eax
  int v4; // edi
  uint32_t *v5; // edi
  int *v6; // [esp+8h] [ebp-8h] BYREF
  int v7; // [esp+Ch] [ebp-4h] BYREF

  if ( sub_472F90(1) >= 1 )  // 若 sub_472F90(1) >= 1
  {
    *(uint32_t *)(this + 16) = 0;  // this+16 = 0
    *(uint8_t *)(this + 33) = 0;  // this+33 = 0
    *(uint8_t *)(this + 34) = 0;  // this+34 = 0
    sub_698F90(this + 20, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(uint32_t *)(this + 48) = 0;  // this+48 = 0
    *(uint32_t *)(this + 53) = 16843009;  // this+53 = 16843009
    *(uint32_t *)(this + 57) = 16843009;  // this+57 = 16843009
    *(uint16_t *)(this + 61) = 257;  // this+61 = 257
    *(uint8_t *)(this + 63) = 1;  // this+63 = 1
    return this + 53;
  }
  v3 = sub_4CE8A0(1016);  // 调 sub_4CE8A0
  if ( v3 != 0
    && (v4 = *(uint32_t *)(dword_8F7A24 + 20),  // 全局 dword_8F7A24 = 登录/选区管理器
        v7 = *(uint32_t *)(v3 + 124),
        *sub_472E30((int **)(v4 + 88), &v6, &v7) == *(int **)(v4 + 92)) )  // 引导步骤推进（472F90/472E30/47C080/47B6F0/461730/47B560，59 行）
  {
    if ( sub_47C080((uint32_t *)dword_8F8540, 1016) != 0 )  // 若 sub_47C080((uint32_t *)dword_8F8540, 1016) != 0
      return sub_5461C0((uint32_t *)this, 2);  // 引导文本复位（698F90）
    if ( sub_47B6F0((uint32_t *)dword_8F8540, 1016) != 0 )  // 若 sub_47B6F0((uint32_t *)dword_8F8540, 1016) != 0
    {
      v5 = (uint32_t *)dword_8F8540;  // 全局 dword_8F8540 = 物品栏刷新器
      if ( sub_461730((int *)dword_8F8540) < 3 )  // 20 字节项数组计数
      {
        sub_47B560(v5, 1016);  // 调 sub_47B560
        return sub_5461C0((uint32_t *)this, 2);  // 引导文本复位（698F90）
      }
    }
    result = sub_5461C0((uint32_t *)this, 3);  // 结果 = 引导文本复位（698F90）
    *(uint8_t *)(this + 55) = 1;  // this+55 = 1
  }
  else
  {
    *(uint32_t *)(this + 16) = 3;  // this+16 = 3
    *(uint8_t *)(this + 33) = 0;  // this+33 = 0
    *(uint8_t *)(this + 34) = 0;  // this+34 = 0
    result = sub_698F90(this + 20, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(uint32_t *)(this + 48) = 0;  // this+48 = 0
    *(uint8_t *)(this + 55) = 1;  // this+55 = 1
  }
  return result;
}



// ------------------------------------------------------------
// 0x546F30 sub_546F30 —— 引导清理（426BD0 + 698F90）
// ------------------------------------------------------------
// 大白话：引导清理：426BD0 析构 + 698F90 清事件。
char /*thiscall*/ sub_546F30(int this, void *Block)  // 函数: 引导清理（426BD0 + 698F90）
{
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  char result; // al

  *(uint32_t *)(this + 4) = Block;  // this+4 = Block
  *(uint32_t *)(this + 12) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 112);  // this+12 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x68u);  // 堆分配 104 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v4 = sub_426BD0(pMem);  // 结果 = nengine::IControl 构造
  else
    v4 = nullptr;  // v4 = nullptr 空指针
  *(uint32_t *)(this + 8) = v4;  // this+8 = v4
  *((uint32_t *)v4 + 17) = this;
  *(uint32_t *)(this + 16) = 1;  // this+16 = 1
  *(uint8_t *)(this + 33) = 0;  // this+33 = 0
  *(uint8_t *)(this + 34) = 0;  // this+34 = 0
  result = sub_698F90(this + 20, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  *(uint32_t *)(this + 53) = 0;  // this+53 = 0
  *(uint32_t *)(this + 57) = 0;  // this+57 = 0
  *(uint16_t *)(this + 61) = 0;  // this+61 = 0
  *(uint8_t *)(this + 63) = 0;  // this+63 = 0
  *(uint8_t *)(this + 64) = 0;  // this+64 = 0
  *(uint8_t *)(this + 65) = 0;  // this+65 = 0
  return result;
}



// ------------------------------------------------------------
// 0x546FD0 sub_546FD0 —— 21 行小辅助
// ------------------------------------------------------------
// 大白话：21 行小辅助（引导收尾）。
int /*thiscall*/ sub_546FD0(uint32_t *this)  // 函数: 21 行小辅助
{
  *(this + 4) = 0;  // this+16 = 0
  *(this + 5) = 0;  // this+20 = 0
  *(this + 6) = 0;  // this+24 = 0
  *(this + 7) = 0;  // this+28 = 0
  *(this + 8) = 0;  // this+32 = 0
  *(this + 9) = 0;  // this+36 = 0
  *(this + 10) = 0;  // this+40 = 0
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 13) = 0;  // this+52 = 0
  *(this + 14) = 0;  // this+56 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x547000 sub_547000 —— 引导数据（52 行）
// ------------------------------------------------------------
// 大白话：引导数据装配：52 行，装载引导步骤所需数据。
int /*thiscall*/ sub_547000(uint32_t *this)  // 函数: 引导数据（52 行）
{
  void (/*thiscall*/ ***fld_e1)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e5)(uint32_t, int); // ecx
  uint32_t *pThis_6; // edi
  int i; // ebx
  void (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  int result; // eax

  fld_e1 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( fld_e1 != nullptr )  // 若 fld_e1 非空
    (**fld_e1)(fld_e1, 1);
  fld_e5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 1) = 0;  // this+4 = 0
  if ( fld_e5 != nullptr )  // 若 fld_e5 非空
    (**fld_e5)(fld_e5, 1);
  *(this + 5) = 0;  // this+20 = 0
  pThis_6 = this + 6;
  for ( i = 4; i != 0; --i )  // 循环：i = 4; i != 0; --i
  {
    if ( *pThis_6 != 0 )  // 若 *pThis_6 != 0
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_6)(*pThis_6, 1);
    *pThis_6++ = 0;  // *pThis_6++ 写入 0
  }
  fld_e10 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    (**fld_e10)(fld_e10, 1);
  fld_e11 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;  // this+40 = 0
  if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    (**fld_e11)(fld_e11, 1);
  fld_e12 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 12);  // this+12 物品类型号
  *(this + 11) = 0;  // this+44 = 0
  if ( fld_e12 != nullptr )  // 若 fld_e12 非空
    (**fld_e12)(fld_e12, 1);
  fld_e13 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  result = 0;
  *(this + 12) = 0;  // this+48 = 0
  if ( fld_e13 != nullptr )  // 若 fld_e13 非空
    result = (**fld_e13)(fld_e13, 1);
  *(this + 13) = 0;  // this+52 = 0
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
// 大白话：物品栏打开槽（10 行）。
bool CNRDItemInventoryWindow__vmtC()  // CNRDItemInventoryWindow__vmtC 打开槽（10 行）
{
  return dword_8F7C04 != 0;  // 全局 dword_8F7C04 = 本机角色对象
}



// ------------------------------------------------------------
// 0x5470B0 sub_5470B0 —— 物品栏格子参数（37 行）
// ------------------------------------------------------------
// 大白话：物品栏格子参数：返回当前页起格/容量换算（37 行，页内偏移算术）。
int /*stdcall*/ sub_5470B0(char pszArg1)  // 函数: 物品栏格子参数（37 行）
{
  int v1; // edi
  LONG v2; // esi
  LONG v3; // eax
  int v4; // ecx

  v1 = 0;
  while ( 1 )  // 当 1 循环
  {
    if ( pszArg1 != 0 )  // 若 pszArg1 != 0
    {
      v2 = 32 * (v1 % 8) + 339;
      v3 = 32 * (v1 / 8) + 210;
    }
    else
    {
      v2 = 32 * (v1 % 8) + 337;
      v3 = 32 * (v1 / 8) + 208;
    }
    if ( pt.x >= v2 )  // 若 pt.x >= v2
    {
      v4 = 4 * (pszArg1 == 0) + 28;
      if ( pt.x < v4 + v2 && pt.y >= v3 && pt.y < v3 + v4 )  // 若 pt.x < v4 + v2 && pt.y >= v3 && pt.y < v3 + v4
        break;
    }
    if ( ++v1 >= 32 )  // 若 ++v1 >= 32
      return -1;  // 返回 -1（0xFFFFFFFF）
  }
  return v1;
}



// ------------------------------------------------------------
// 0x547170 sub_547170 —— 物品格子查询（484FA0 + 422E70/44E8D0）
// ------------------------------------------------------------
// 大白话：物品格查询：484FA0 取数据 + 422E70/44E8D0 显示条目。
BOOL /*cdecl*/ sub_547170(int nArg1, char pszArg2)  // 函数: 物品格子查询（484FA0 + 422E70/44E8D0）
{
  int v2; // edi
  int v3; // esi
  char *v4; // eax
  char Buffer[1024]; // [esp+10h] [ebp-404h] BYREF
  int dword_796E502; // [esp+410h] [ebp-4h]

  v2 = *((uint32_t *)dword_8F852C + 1);  // 全局 dword_8F852C = 角色/物品栏管理器
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v3 = sub_484FA0() - v2 - nArg1;  // 结果 = 全局时间系数计算（+732 与 +746 相乘）
  if ( v3 < 0 && pszArg2 != 0 )  // 若 v3 < 0 && pszArg2 != 0
  {
    v4 = sub_422E70(412);  // 调 sub_422E70
    sprintf(Buffer, v4, (double)(int)abs32(v3) * 0.001);  // 调 sprintf 格式化
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);  // 对象池借出（按池号取可用对象）
  }
  return v3 < 0;
}



// ------------------------------------------------------------
// 0x547210 CNRDItemInventoryWindow__vmt10 —— CNRDItemInventoryWindow__vmt10 状态切换（44AB50 + 5653D0 + 44E850 + 540960）
// ------------------------------------------------------------
// 大白话：物品栏状态切换：44AB50 页签 + 5653D0 + 44E850 + 540960 输入框刷新。
int /*thiscall*/ CNRDItemInventoryWindow__vmt10(uint32_t *this)  // 函数: CNRDItemInventoryWindow__vmt10 状态切换（44AB50 + 5653D0 + 44E850 + 540960）
{
  uint32_t *pHostCtrl; // ecx
  int v3; // esi
  int v4; // ebx

  pHostCtrl = (uint32_t *)*(this + 2);
  v3 = pHostCtrl[26];
  v4 = pHostCtrl[27];
  if ( v3 == 6 || v3 == 9 || v3 == 10 )  // 若 v3 == 6 || v3 == 9 || v3 == 10
    sub_44AB50(pHostCtrl, 0, 12);  // 页签切换
  if ( v3 == 2 )  // 若 v3 == 2
  {
    if ( v4 != 1 )  // 若 v4 != 1
      sub_44AB50((uint32_t *)*(this + 2), 0, 12);  // 页签切换
  }
  else if ( v3 == 6 )  // 否则若 v3 == 6
  {
    sub_5653D0(*(uint32_t *)(*(this + 2) + 80));  // 商店格子（4CE8A0）
  }
  if ( dword_9B88D0 != 0 && dword_795378 == 1 )  // 若 dword_9B88D0 != 0 && dword_795378 == 1
    sub_44E850((uint32_t *)*(this + 2), 26);  // 按池号批量回收活动对象
  return sub_540960(*(uint32_t **)(*(this + 2) + 116));  // 数量输入框刷新
}



// ------------------------------------------------------------
// 0x547290 sub_547290 —— 10 行小辅助
// ------------------------------------------------------------
// 大白话：10 行小辅助（物品栏）。
int /*stdcall*/ sub_547290(int nArg1)  // 函数: 10 行小辅助
{
  return dword_724880[nArg1];
}



// ------------------------------------------------------------
// 0x5472B0 sub_5472B0 —— 10 行小辅助 2
// ------------------------------------------------------------
// 大白话：10 行小辅助（物品栏，变体 2）。
int /*stdcall*/ sub_5472B0(int nArg1)  // 函数: 10 行小辅助 2
{
  return dword_7248A8[nArg1];
}



// ------------------------------------------------------------
// 0x5472D0 sub_5472D0 —— 10 行小辅助 3
// ------------------------------------------------------------
// 大白话：10 行小辅助（物品栏，变体 3）。
bool sub_5472D0()  // 10 行小辅助 3
{
  return pt.x >= 332 && pt.x < 598 && pt.y >= 75 && pt.y < 178;
}



// ------------------------------------------------------------
// 0x547300 sub_547300 —— 物品栏数据（33 行）
// ------------------------------------------------------------
// 大白话：物品栏页基准格号：按页签换算该页首格的全局下标（33 行）。
int /*cdecl*/ sub_547300(int nArg1)  // 函数: 物品栏数据（33 行）
{
  int result; // eax

  switch ( nArg1 )  // 分支：按 nArg1 分派
  {
    case 0:  // case 0
      result = 9;
      break;
    case 1:  // case 1
      result = 41;
      break;
    case 2:  // case 2
      result = 73;
      break;
    case 3:  // case 3
      result = 105;
      break;
    case 4:  // case 4
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
// 大白话：物品栏条目行号：返回物品所在格下标（25 行）。
int /*cdecl*/ sub_547350(int nArg1)  // 函数: 物品栏条目（25 行）
{
  int v1; // eax

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 16))(nArg1) + 4) <= 2u )  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
    return -1;  // 返回 -1（0xFFFFFFFF）
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg1 + 20))(nArg1, 1) == 0 )  // 虚槽+20 CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认购买（541A30/541B
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg1 + 20))(nArg1, 2) != 0 )  // 虚槽+20 CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认购买（541A30/541B
      return (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 172))(nArg1) > 7) - 1;  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
    return -1;  // 返回 -1（0xFFFFFFFF）
  }
  v1 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 132))(nArg1) - 1;  // 虚槽+132 CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉刺王变体，23 行）
  if ( v1 == 0 )  // 若 v1 == 0
    return 2;
  if ( v1 == 5 )  // 若 v1 == 5
    return 3;
  return 1;
}



// ------------------------------------------------------------
// 0x5473D0 sub_5473D0 —— 物品栏辅助（484ED0）
// ------------------------------------------------------------
// 大白话：物品栏辅助：484ED0 数据访问。
int /*thiscall*/ sub_5473D0(uint32_t *this, int nArg2)  // 函数: 物品栏辅助（484ED0）
{
  int result; // eax
  int v4; // edx
  int v5; // ecx

  result = sub_484ED0(nArg2);  // 结果 = 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
  v4 = 3;
  while ( 1 )  // 当 1 循环
  {
    switch ( v4 )  // 分支：按 v4 分派
    {
      case 0:  // case 0
        v5 = 9;
        break;
      case 1:  // case 1
        v5 = 41;
        break;
      case 2:  // case 2
        v5 = 73;
        break;
      case 3:  // case 3
        v5 = 105;
        break;
      case 4:  // case 4
        v5 = 137;
        break;
      default:
        v5 = 0;
        break;
    }
    if ( result >= v5 )  // 若 result >= v5
      break;
    if ( --v4 < 0 )  // 若 --v4 < 0
      return result;
  }
  *(this + 14) = v4;  // this+56 = v4
  return result;
}



// ------------------------------------------------------------
// 0x547450 sub_547450 —— 物品栏格子重建（28 行）
// ------------------------------------------------------------
// 大白话：物品栏格子重建：返回鼠标悬停格下标（28 行，格 28x28，见 dword_7248A0/7248C0 表）。
int sub_547450()  // 物品栏格子重建
{
  int result; // eax
  int v1; // ecx
  LONG v2; // edx
  LONG v3; // esi

  result = 8;
  v1 = 0;
  while ( 1 )  // 当 1 循环
  {
    v2 = dword_7248A0[v1];
    v3 = dword_7248C8[v1];
    if ( pt.x >= v2 && pt.x < v2 + 28 && pt.y >= v3 && pt.y < v3 + 28 )  // 若 pt.x >= v2 && pt.x < v2 + 28 && pt.y >= v3 && pt.y < v3 + 28
      break;
    ++v1;  // 自增v1
    ++result;  // 自增result
    if ( v1 >= 10 )  // 若 v1 >= 10
      return 18;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5474B0 CNRDItemInventoryWindow__vmt14 —— CNRDItemInventoryWindow__vmt14 关闭槽（87 行：5470B0/547300/541A30/541AF0/547450 + 44BC30/44A980）
// ------------------------------------------------------------
// 大白话：物品拖出分发：页签 14（摆摊模式）时把背包物品放进摆摊空槽（541A30/541AF0 找位）；
// 其余按悬停格取物品（角色虚表+792 / 44A980 数组）经 44BC30(2,2)/(2,3) 发起拖动【推断】。
char /*thiscall*/ CNRDItemInventoryWindow__vmt14(int this)  // 函数: CNRDItemInventoryWindow__vmt14 关闭槽（87 行：5470B0/547300/541A30/541AF0/547450 + 44BC30/44A980）
{
  int pObj3; // edi
  int v4; // edi
  int nSlotIndex; // eax  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  uint32_t *v6; // eax
  int v7; // ebx
  int fld_382; // eax  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  int v9; // edx
  int pOwnerWnd; // eax  | +0x0004 → 宿主窗口（0x5474B0: fld_4=*(this+4)）【推断】（CNRDItemInventoryWindow；va=005474B0）
  int v11; // eax
  int v12; // ebx
  void *pObj2; // edi
  int pHostCtrl; // eax  | +0x0008 → 宿主控件（0x5474B0: *(*(this+8)+2504)==14 判摆摊模式页签）（CNRDItemInventoryWindow；va=005474B0）
  int v15; // eax
  int v16; // ebx
  void *pObj; // edi
  int fld_82; // eax  | +0x0008 → 宿主控件（0x5474B0: *(*(this+8)+2504)==14 判摆摊模式页签）（CNRDItemInventoryWindow；va=005474B0）
  int v19; // eax
  int v20; // [esp-Ch] [ebp-18h]
  int v21; // [esp-Ch] [ebp-18h]
  int fld_383; // [esp+8h] [ebp-4h]  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）

  pObj3 = dword_8F7C04;  // 全局 dword_8F7C04 = 本机角色对象
  if ( dword_8F7C04 == 0 )  // 全局 dword_8F7C04 = 本机角色对象
    return 0;
  if ( *(uint32_t *)(*(uint32_t *)(this + 8) + 2504) == 14 )  // 判定 “+8 宿主控件”
  {
    v4 = sub_5470B0(1);  // 结果 = 物品栏格子参数
    if ( v4 != -1 )  // 若 v4 != -1
    {
      nSlotIndex = v4 + sub_547300(*(uint32_t *)(this + 56));  // 结果 = 物品栏数据
      if ( nSlotIndex < *((uint32_t *)dword_8F852C + 2) && *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * nSlotIndex) != 0 )  // 全局 dword_8F852C = 角色/物品栏管理器
      {
        v6 = (uint32_t *)sub_541A30();  // 结果 = 摊位条目名取串
        v7 = sub_541AF0(v6);  // 结果 = 摊位辅助
        sub_541A30();  // 摊位条目名取串
        fld_382 = sub_547300(*(uint32_t *)(this + 56));  // 结果 = 物品栏数据
        (*(void (/*stdcall*/ **)(int, int, uint32_t))(v9 + 64))(v4 + fld_382, v7, 0);  // 调用虚函数槽 +64
        sub_44ABE0(*(uint32_t **)(this + 8), 0);  // 选中索引 setter
        return 1;
      }
    }
    return 0;
  }
  pOwnerWnd = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主窗口）
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0 || dword_79BE3C != *(uint32_t *)(pOwnerWnd + 12) )  // 若 *(uint8_t *)(fld_4 + 17) == 0 || dword_79BE3C != *(uint32_t *)..
    return 0;
  v11 = sub_547450();  // 结果 = 物品栏格子重建
  v12 = v11;
  if ( v11 != 18 )  // 若 v11 != 18
  {
    pObj2 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 792))(pObj3, v11);  // 虚槽+792 18 观察者槽数组访问（+6468+4*a2）
    if ( pObj2 != nullptr )  // 若 pObj2 非空
    {
      pHostCtrl = *(uint32_t *)(*(uint32_t *)(this + 8) + 2504);  // this+8 pHostCtrl
      if ( pHostCtrl != 5 && pHostCtrl != 6 && pHostCtrl != 7 && pHostCtrl != 18 )  // 若 fld_8 != 5 && fld_8 != 6 && fld_8 != 7 && fld_8 != 18
      {
        v20 = *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pObj2 + 16))(pObj2) + 68);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
        v15 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pObj2 + 16))(pObj2);  // 调用虚函数槽 +16
        sub_44BC30(*(uint32_t **)(this + 8), (void *)2, 2, *(uint32_t *)(v15 + 4), v12, v20, pObj2);  // 拾取模式状态 + ICON_PICK/ITEM_PICK 音效
      }
      return 1;
    }
  }
  v16 = sub_5470B0(1);  // 结果 = 物品栏格子参数
  if ( v16 == -1 )  // 若 v16 == -1
    return 0;
  fld_383 = sub_547300(*(uint32_t *)(this + 56));  // 结果 = 物品栏数据
  pObj = (void *)sub_44A980(dword_8F852C, v16 + fld_383);  // 结果 = 带界索引 getter
  if ( pObj == nullptr )  // 若 pObj 为空
    return 0;
  fld_82 = *(uint32_t *)(*(uint32_t *)(this + 8) + 2504);  // this+8 pHostCtrl
  if ( fld_82 != 5 && fld_82 != 6 && fld_82 != 7 && fld_82 != 18 )  // 若 fld_82 != 5 && fld_82 != 6 && fld_82 != 7 && fld_82 != 18
  {
    v21 = *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pObj + 16))(pObj) + 68);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
    v19 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pObj + 16))(pObj);  // 调用虚函数槽 +16
    sub_44BC30(*(uint32_t **)(this + 8), (void *)2, 3, *(uint32_t *)(v19 + 4), v16 + fld_383, v21, pObj);  // 拾取模式状态 + ICON_PICK/ITEM_PICK 音效
  }
  return 1;
}



// ------------------------------------------------------------
// 0x547670 CNRDItemInventoryWindow__vmt18 —— CNRDItemInventoryWindow__vmt18 按钮动作（CLICK_BUTTON2 + 44BBA0 显示）
// ------------------------------------------------------------
// 大白话：格子点击选中：按页签(+626)+来源(+627)取格内物品（792/44A980 系列），
// 547350 求格号；未选中则 44BBA0(1) 展开并播 CLICK_BUTTON2，已选中则记入 +14。
char /*thiscall*/ CNRDItemInventoryWindow__vmt18(uint32_t *this)  // 函数: CNRDItemInventoryWindow__vmt18 按钮动作（CLICK_BUTTON2 + 44BBA0 显示）
{
  int pOwnerWnd; // eax  | +0x0004 → 宿主窗口（0x5474B0: fld_4=*(this+4)）【推断】（CNRDItemInventoryWindow；va=005474B0）
  uint32_t *pHostCtrl; // eax
  int v4; // eax
  int v5; // eax
  char result; // al

  if ( dword_8F7C04 == 0 )  // 全局 dword_8F7C04 = 本机角色对象
    return 0;
  pOwnerWnd = *(this + 1);  // 读 fld_e1 = this+4（宿主窗口）
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0 )  // 若 *(uint8_t *)(fld_e1 + 17) == 0
    return 0;
  if ( dword_79BE3C != *(uint32_t *)(pOwnerWnd + 12) )  // 若 dword_79BE3C != *(uint32_t *)(fld_e1 + 12)
    return 0;
  pHostCtrl = (uint32_t *)*(this + 2);
  if ( pHostCtrl[626] != 2 )  // 若 fld_e2[626] != 2
    return 0;
  switch ( pHostCtrl[627] )
  {
    case 2:  // case 2
      v4 = (*(int (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(pHostCtrl[629]);  // 全局 dword_8F7C04 = 本机角色对象
      goto LABEL_10;  // 跳转 LABEL_10
    case 3:  // case 3
    case 4:  // case 4
      v4 = sub_44A980(dword_8F852C, pHostCtrl[629]);  // 结果 = 带界索引 getter
      goto LABEL_10;  // 跳转 LABEL_10
    case 5:  // case 5
      v4 = sub_44A980(*(uint32_t **)(dword_8F8538 + 16), pHostCtrl[629]);  // 结果 = 带界索引 getter
      goto LABEL_10;  // 跳转 LABEL_10
    case 8:  // case 8
      v4 = sub_44A980(dword_8F8530, pHostCtrl[629]);  // 结果 = 带界索引 getter
LABEL_10:
      if ( v4 == 0 )  // 若 v4 == 0
        goto LABEL_15;  // 跳转 LABEL_15
      v5 = sub_547350(v4);  // 结果 = 物品栏条目
      if ( v5 == -1 )  // 若 v5 == -1
      {
        sub_44BBA0((uint32_t *)*(this + 2), 1, 0);  // 窗口显示切换（WINDOW_SHOW 音效）
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
      }
      else if ( v5 != *(this + 14) )  // 否则若 v5 != *(this + 14)
      {
        *(this + 14) = v5;  // 写 this+56 = v5（槽下标）
        return 1;
      }
LABEL_15:
      result = 1;
      break;
    default:
      goto LABEL_15;  // 跳转 LABEL_15
  }
  return result;
}



// ------------------------------------------------------------
// 0x547770 CNRDItemInventoryWindow__vmt1C —— CNRDItemInventoryWindow__vmt1C 内容刷新（318 行：44F2E0/44F400/44F580/44F670 格子系列 + 486820/486530 + 540DE0）
// ------------------------------------------------------------
// 大白话：物品栏内容刷新：44F2E0/44F400/44F580/44F670 格子系列 + 486820/486530
// 重排全部格子并 540DE0 重建列表（318 行）。
char /*thiscall*/ sub_547770(int this)  // 【CNRDItemInventoryWindow__vmt1C】
{
  int pOwnerWnd; // eax  | +0x0004 → 宿主窗口（0x5474B0: fld_4=*(this+4)）【推断】（CNRDItemInventoryWindow；va=005474B0）
  uint32_t *pHostCtrl; // ebx
  int v5; // edi
  int v6; // eax
  int pObj5; // eax
  int pObj7; // edi
  int v9; // ebx
  int *v10; // eax
  int fld_383; // eax  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  int v12; // esi
  int *v13; // eax
  int pObj10; // eax
  int pObj12; // edi
  int v16; // eax
  unsigned int v17; // eax
  int pObj9; // edi
  int v19; // eax
  int v20; // edi
  int v21; // edi
  int fld_3810; // esi  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  int v23; // ebx
  int fld_386; // eax  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  int pObj11; // eax
  int pObj; // ebx
  int v27; // ebx
  int fld_389; // eax  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  int pObj8; // eax
  int v30; // ebx
  int fld_388; // eax  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  unsigned int v32; // eax
  int pObj3; // eax
  int pObj2; // edi
  int pObj4; // eax
  int *v36; // eax
  int fld_384; // eax  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  int v38; // ebx
  int v39; // ecx
  int v40; // eax
  int v41; // eax
  int v42; // ebx
  int v43; // eax
  int nSlotIndex; // eax  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  int v45; // ecx
  int v46; // eax
  int v47; // eax
  uint32_t *dword_8F852C2; // [esp-10h] [ebp-28h]
  int fld_387; // [esp-Ch] [ebp-24h]  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  uint32_t *fld_82; // [esp+4h] [ebp-14h]
  int fld_382; // [esp+4h] [ebp-14h]  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  int fld_3832; // [esp+4h] [ebp-14h]
  int pObj6; // [esp+8h] [ebp-10h]
  int v54; // [esp+Ch] [ebp-Ch]
  int v55; // [esp+Ch] [ebp-Ch]
  int v56; // [esp+10h] [ebp-8h]
  signed int fld_385; // [esp+10h] [ebp-8h]  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  int v58; // [esp+10h] [ebp-8h]
  int v59; // [esp+10h] [ebp-8h]
  char v60; // [esp+17h] [ebp-1h]

  if ( dword_8F7C04 == 0 )  // 全局 dword_8F7C04 = 本机角色对象
    return 0;
  pOwnerWnd = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主窗口）
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0 || dword_79BE34 != *(uint32_t *)(pOwnerWnd + 12) )  // 若 *(uint8_t *)(fld_4 + 17) == 0 || dword_79BE34 != *(uint32_t *)..
    return 0;
  pHostCtrl = *(uint32_t **)(this + 8);  // this+8 pHostCtrl
  v5 = pHostCtrl[626];  // fld_8=this+8 pHostCtrl
  fld_82 = pHostCtrl;  // fld_8=this+8 pHostCtrl
  if ( v5 == 5 || v5 == 6 || v5 == 7 || v5 == 18 )  // 若 v5 == 5 || v5 == 6 || v5 == 7 || v5 == 18
  {
    v41 = sub_547450(this);  // 结果 = 物品栏格子重建
    v42 = v41;
    if ( v41 == 18 )  // 若 v41 == 18
    {
      if ( sub_5470B0(1) == -1 )  // 物品栏格子参数
        return 0;
      nSlotIndex = sub_547300(*(uint32_t *)(this + 56));  // 结果 = 物品栏数据
      v46 = v45 + nSlotIndex;
      if ( v46 >= *((uint32_t *)dword_8F852C + 2) )  // 全局 dword_8F852C = 角色/物品栏管理器
        return 0;
      v43 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v46);  // 全局 dword_8F852C = 角色/物品栏管理器
    }
    else
    {
      v43 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, v41);  // 全局 dword_8F7C04 = 本机角色对象
    }
    if ( v43 == 0 )  // 若 v43 == 0
      return 0;
    switch ( v5 )  // 分支：按 v5 分派
    {
      case 5:  // case 5
        sub_44F2E0(v43, 1);  // 出售入口分发
        return 1;
      case 6:  // case 6
        sub_44F400(v43, 1);  // 修理入口
        return 1;
      case 7:  // case 7
        if ( v42 == 18 )  // 若 v42 == 18
        {
          sub_44F580(v43, 1);  // 道具二次校验分发（拒绝文案 408/409/410/411）
          return 1;
        }
        v47 = sub_422E70(413);  // 调 sub_422E70
        break;
      default:
        if ( v42 == 18 )  // 若 v42 == 18
        {
          sub_44F670(v43, 1);  // 道具校验分发 2（拒绝文案 1652/1653/1664）
          return 1;
        }
        v47 = sub_422E70(1651);  // 调 sub_422E70
        break;
    }
    sub_44E8D0(*(char **)(this + 8), (void *)0x1B, v47, 0);  // 对象池借出（按池号取可用对象）
    return 1;
  }
  if ( v5 != 2 )  // 若 v5 != 2
    return 0;
  v60 = sub_5472D0(this);  // 结果 = 10 行小辅助 3
  v6 = pHostCtrl[627];  // fld_8=this+8 pHostCtrl
  switch ( v6 )  // 分支：按 v6 分派
  {
    case 2:  // case 2
      pObj5 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, pHostCtrl[629]);  // 全局 dword_8F7C04 = 本机角色对象
      pObj7 = pObj5;
      if ( pObj5 == 0 )  // 若 pObj5 == 0
        return 0;
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 16))(pObj5) + 4) != pHostCtrl[628] )  // fld_8=this+8 pHostCtrl
        return 0;
      v9 = sub_5470B0(0);  // 结果 = 物品栏格子参数
      if ( v9 == -1 )  // 若 v9 == -1
        return 0;
      fld_382 = sub_547300(*(uint32_t *)(this + 56));  // 结果 = 物品栏数据
      v10 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj7 + 172))(pObj7);  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
      if ( sub_486820((int *)dword_8F852C, v9 + fld_382, *v10, 1) == 0 )  // 施放拒绝提示（ALERT_1 音效 + sub_485510）
      {
        fld_383 = sub_547300(*(uint32_t *)(this + 56));  // 结果 = 物品栏数据
        v12 = fld_383 + v9;
        fld_3832 = fld_383;
        if ( sub_44A980(fld_383 + v9) != 0 )  // 带界索引 getter
        {
          v54 = 0;
          while ( sub_44A980(v12) != 0 )  // 当 sub_44A980(v12) != 0 循环
          {
            if ( ++v54 >= 32 )  // 若 ++v54 >= 32
              return 0;
          }
          v13 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj7 + 172))(pObj7);  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
          sub_486820((int *)dword_8F852C, v9 + fld_3832, *v13, 1);  // 施放拒绝提示（ALERT_1 音效 + sub_485510）
          return 1;
        }
        return 0;
      }
      return 1;
    case 3:  // case 3
    case 4:  // case 4
      pObj2 = sub_44A980(pHostCtrl[629]);  // 结果 = 带界索引 getter
      if ( pObj2 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 4) == pHostCtrl[628] )  // fld_8=this+8 pHostCtrl
      {
        if ( v60 != 0 )  // 若 v60 != 0
        {
          pObj4 = __RTDynamicCast(pObj2, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
          if ( pObj4 != 0 && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 172))(pObj4) >= 8 )  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
          {
            v36 = (int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 172))(pObj2);  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
            sub_486820((int *)dword_8F852C, pHostCtrl[629], *v36, 1);  // 施放拒绝提示（ALERT_1 音效 + sub_485510）
            return 1;
          }
        }
        else if ( sub_5470B0(0) != -1 )  // 物品栏格子参数
        {
          fld_384 = sub_547300(*(uint32_t *)(this + 56));  // 结果 = 物品栏数据
          v38 = pHostCtrl[629];  // fld_8=this+8 pHostCtrl
          v40 = v39 + fld_384;
          if ( v40 != v38 )  // 若 v40 != v38
          {
            sub_486530(dword_8F852C, v40, v38, 1);  // 请求 op 19：两槽交换
            return 1;
          }
        }
      }
      return 0;
    case 8:  // case 8
      pObj10 = sub_44A980(pHostCtrl[629]);  // 结果 = 带界索引 getter
      pObj12 = pObj10;
      if ( pObj10 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj10 + 16))(pObj10) + 4) == pHostCtrl[628] && v60 != 1 )  // fld_8=this+8 pHostCtrl
      {
        v56 = sub_5470B0(0);  // 结果 = 物品栏格子参数
        if ( v56 != -1 )  // 若 v56 != -1
        {
          fld_385 = sub_547300(*(uint32_t *)(this + 56)) + v56;  // 结果 = 物品栏数据
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj12 + 20))(pObj12, 1) != 0  // 虚槽+20 CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认购买（541A30/541B
            && (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj12 + 44))(pObj12) > 1 )  // CNRDItemInventoryWindow__vmt1C 内容刷新（318 行：44F2E0/44F400/44F580/44F670 格子系列 + 486820/486530 + 540DE0）
          {
            sub_540DE0(1, 2, pHostCtrl[629], 0, fld_385, 0, 0);  // 摊位列表构建
            return 1;
          }
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj12 + 36))(pObj12);  // 调用虚函数槽 +36
          if ( (uint8_t)sub_547170(v16, 1) != 1 )  // 物品格子查询（484FA0 + 422E70/44E8D0）
          {
            dword_8F852C2 = dword_8F852C;  // 全局 dword_8F852C = 角色/物品栏管理器
            v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj12 + 44))(pObj12);  // 调用虚函数槽 +44
            sub_4866D0(dword_8F8530, pHostCtrl[629], v17, dword_8F852C2, fld_385);  // 请求 op 19 带来源对象（等级 + 来源容器）
            return 1;
          }
        }
      }
      return 0;
    case 9:  // case 9
      return 0;
    default:
      break;
  }
  if ( v6 != 5 )  // 若 v6 != 5
  {
    if ( v6 == 10 )  // 若 v6 == 10
    {
      pObj3 = sub_541A30();  // 结果 = 摊位条目名取串
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj3 + 72))(pObj3, pHostCtrl[629]);  // 调用虚函数槽 +72
      return 0;
    }
    return 0;
  }
  pObj9 = sub_44A980(pHostCtrl[629]);  // 结果 = 带界索引 getter
  if ( pObj9 == 0 )  // 若 pObj9 == 0
    return 0;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 16))(pObj9) + 4) != pHostCtrl[628] )  // fld_8=this+8 pHostCtrl
    return 0;
  v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 16))(pObj9);  // 调用虚函数槽 +16
  if ( sub_4F2D40(*(uint32_t *)(v19 + 4)) == 2 && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 172))(pObj9) <= 7 )  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
    return 0;
  if ( v60 == 0 || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj9 + 20))(pObj9, 2) == 0 )  // 虚槽+20 CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认购买（541A30/541B
  {
    v23 = sub_5470B0(0);  // 结果 = 物品栏格子参数
    v55 = v23;
    if ( v23 != -1 )  // 若 v23 != -1
    {
      fld_386 = sub_547300(*(uint32_t *)(this + 56));  // 结果 = 物品栏数据
      pObj11 = sub_44A980(v23 + fld_386);  // 结果 = 带界索引 getter
      if ( pObj11 != 0 )  // 若 pObj11 != 0
      {
        pObj = pObj11;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj11 + 20))(pObj11, 1) == 0  // 虚槽+20 CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认购买（541A30/541B
          || *(uint32_t *)((v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj)) + 4) != *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 16))(pObj9) + 4) )
        {
          v23 = -1;
          v55 = -1;
          goto LABEL_54;  // 跳转 LABEL_54
        }
        v23 = v55;
      }
LABEL_65:
      if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 44))(pObj9) <= 1 )  // 虚槽+44 IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 + 69A5F0/69A8
      {
        fld_387 = v23 + sub_547300(*(uint32_t *)(this + 56));  // 结果 = 物品栏数据
        v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 44))(pObj9);  // 调用虚函数槽 +44
        sub_484AF0(dword_8F8538, fld_82[629], v32, 0, fld_387);  // 技能施放请求（包 op 19 变体：槽/参数/来源字段序不同）
      }
      else
      {
        fld_388 = sub_547300(*(uint32_t *)(this + 56));  // 结果 = 物品栏数据
        sub_540DE0(1, 4, fld_82[629], 0, v23 + fld_388, 0, 0);  // 摊位列表构建
      }
      return 1;
    }
LABEL_54:
    v59 = 0;
    while ( 1 )  // 当 1 循环
    {
      fld_389 = sub_547300(*(uint32_t *)(this + 56));  // 结果 = 物品栏数据
      pObj8 = sub_44A980(v23 + fld_389);  // 结果 = 带界索引 getter
      pObj6 = pObj8;
      if ( pObj8 == 0 )  // 若 pObj8 == 0
        break;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj8 + 20))(pObj8, 1) != 0 )  // 虚槽+20 CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认购买（541A30/541B
      {
        v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 16))(pObj9);  // 调用虚函数槽 +16
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj6 + 16))(pObj6) + 4) == *(uint32_t *)(v30 + 4) )  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
          break;
        v23 = v55;
      }
      if ( ++v59 >= 32 )  // 若 ++v59 >= 32
        goto LABEL_62;  // 跳转 LABEL_62
    }
    v23 = v59;
LABEL_62:
    if ( v23 == -1 )  // 若 v23 == -1
      return 0;
    goto LABEL_65;  // 跳转 LABEL_65
  }
  v20 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 172))(pObj9);  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
  v58 = v20;
  if ( v20 < 8 )  // 若 v20 < 8
    return 0;
  if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, v20) != 0 )  // 全局 dword_8F7C04 = 本机角色对象
  {
    v21 = 0;
    fld_3810 = sub_547300(*(uint32_t *)(this + 56));  // 结果 = 物品栏数据
    while ( sub_44A980(fld_3810 + v21) != 0 )  // 当 sub_44A980(fld_3810 + v21) != 0 循环
    {
      if ( ++v21 >= 32 )  // 若 ++v21 >= 32
      {
        sub_484AF0(dword_8F8538, pHostCtrl[629], 1u, 3u, v58);  // 技能施放请求（包 op 19 变体：槽/参数/来源字段序不同）
        return 1;
      }
    }
    sub_486820((int *)dword_8F852C, v21 + fld_3810, v58, 1);  // 施放拒绝提示（ALERT_1 音效 + sub_485510）
    v20 = v58;
  }
  sub_484AF0(dword_8F8538, pHostCtrl[629], 1u, 3u, v20);  // 技能施放请求（包 op 19 变体：槽/参数/来源字段序不同）
  return 1;
}


// ------------------------------------------------------------
// 0x547E80 CNRDItemInventoryWindow__vmt28 —— CNRDItemInventoryWindow__vmt28 槽（4872A0）
// ------------------------------------------------------------
// 大白话：物品栏槽：4872A0 转发。
char /*thiscall*/ CNRDItemInventoryWindow__vmt28(int *this)  // 函数: CNRDItemInventoryWindow__vmt28 槽（4872A0）
{
  int pOwnerWnd; // eax  | +0x0004 → 宿主窗口（0x5474B0: fld_4=*(this+4)）【推断】（CNRDItemInventoryWindow；va=005474B0）
  int nSlotIndex; // eax  | +0x0038 → 槽下标（CNRDItemInventoryWindow；va=005474B0）
  int v4; // ecx

  pOwnerWnd = *(this + 1);  // 读 fld_e1 = this+4（宿主窗口）
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0  // fld_e1=this+4 pOwnerWnd
    || dword_79BE38 != *(uint32_t *)(pOwnerWnd + 12)  // CNRDItemInventoryWindow__vmt28 槽（4872A0）
    || *(uint32_t *)(*(this + 2) + 2504) != 0
    || sub_5470B0(1) == -1 )  // 物品栏格子参数
  {
    return 0;
  }
  nSlotIndex = sub_547300(*(this + 14));  // 结果 = 物品栏数据
  sub_4872A0(v4 + nSlotIndex);  // 槽对象使用分发（按虚表 +20 类型分流）
  return 1;
}



// ------------------------------------------------------------
// 0x547EE0 CNRDItemInventoryWindow__vmt8 —— CNRDItemInventoryWindow__vmt8 Update（134 行：CLICK_BUTTON2/WINDOW_CLOSE + 486C40/540DE0 格子点击）
// ------------------------------------------------------------
// 大白话：物品栏逐帧 Update：按钮播 CLICK_BUTTON2/WINDOW_CLOSE 音；486C40 物品操作；
// 放入摆摊/丢弃分支调 540DE0 数量弹窗（模式 7）；悬停格子经 44E8D0 消息 0x1A 弹
// 物品提示，无物品时解除 26 号对象。
char /*thiscall*/ sub_547EE0(char *this)  // 【CNRDItemInventoryWindow__vmt8】
{
  int pThis_22; // eax
  int pThis_5; // eax
  int dword_79BE342; // esi
  int v5; // edx
  char *pThis_18; // ecx
  int pThis_A; // eax
  int pThis_B; // eax
  int pThis_C; // eax
  int v10; // eax
  int pThis_2; // eax
  int pThis_1; // ecx
  int v13; // ebx
  int64_t pThis_E; // rax
  int v15; // ecx
  int v16; // esi
  int v17; // ebx
  int v18; // eax
  int v19; // ebx

  if ( dword_8F7C04 != 0 )  // 全局 dword_8F7C04 = 本机角色对象
  {
    pThis_5 = *((uint32_t *)this + 5);  // pThis_5=this+20 频道页号
    dword_79BE342 = dword_79BE34;
    if ( *(uint8_t *)(pThis_5 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_5 + 12) )  // 若 *(uint8_t *)(pThis_5 + 17) != 0 && dword_79BE34 == *(uint32_t ..
    {
      (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 44))(this);  // 调用虚函数槽 +44
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
      LOBYTE(pThis_22) = (uint8_t)sub_432EA0("WINDOW_CLOSE", -1, 0, 0);  // 字符串 “WINDOW_CLOSE”
    }
    else
    {
      v5 = 0;
      pThis_18 = this + 24;  // this+24 页数上限
      while ( *(uint8_t *)(*(uint32_t *)pThis_18 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*(uint32_t *)pThis_18 + 12) )  // 当 *(uint8_t *)(*(uint32_t *)pThis_18 + 17) == 0 || dword_79BE34 .. 循环
      {
        ++v5;  // 自增v5
        pThis_18 += 4;  // pThis_18=this+24 页数上限
        if ( v5 >= 4 )  // 若 v5 >= 4
          goto LABEL_12;  // 跳转 LABEL_12
      }
      *((uint32_t *)this + 14) = v5;  // 写 this+56 = v5（槽下标）
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
      dword_79BE342 = dword_79BE34;
LABEL_12:
      pThis_A = *((uint32_t *)this + 10);  // pThis_A=this+40 物品状态附属标志
      if ( *(uint8_t *)(pThis_A + 17) != 0 && dword_79BE342 == *(uint32_t *)(pThis_A + 12) )  // 若 *(uint8_t *)(pThis_A + 17) != 0 && dword_79BE342 == *(uint32_t..
      {
        sub_44BBA0(1, 0);  // 窗口显示切换（WINDOW_SHOW 音效）
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
        dword_79BE342 = dword_79BE34;
      }
      pThis_B = *((uint32_t *)this + 11);  // pThis_B=this+44 剩余时间 ms
      if ( *(uint8_t *)(pThis_B + 17) != 0 && dword_79BE342 == *(uint32_t *)(pThis_B + 12) )  // 若 *(uint8_t *)(pThis_B + 17) != 0 && dword_79BE342 == *(uint32_t..
      {
        sub_486C40(dword_8F852C, v5);  // 请求 op 20（整栏技能重置）
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
        dword_79BE342 = dword_79BE34;
      }
      pThis_C = *((uint32_t *)this + 12);  // this+12 nTabIndex
      if ( *(uint8_t *)(pThis_C + 17) != 0 && dword_79BE342 == *(uint32_t *)(pThis_C + 12) )  // 若 *(uint8_t *)(pThis_C + 17) != 0 && dword_79BE342 == *(uint32_t..
      {
        v10 = *(uint32_t *)(dword_8F7A24 + 12);  // 全局 dword_8F7A24 = 登录/选区管理器
        if ( v10 == 1 || v10 == 4 || v10 == 6 )  // 若 v10 == 1 || v10 == 4 || v10 == 6
        {
          sub_540DE0(0, 0, 0, 7, 0, 0, 0);  // 摊位列表构建
        }
        else if ( v10 == 3 )  // 否则若 v10 == 3
        {
          sub_540DE0(4, 0, 0, 7, 0, 0, 0);  // 摊位列表构建
        }
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
        dword_79BE342 = dword_79BE34;
      }
      pThis_2 = *(uint32_t *)(*((uint32_t *)this + 2) + 2504);
      if ( pThis_2 == 1 )  // 若 pThis_2 == 1
        goto LABEL_40;  // 跳转 LABEL_40
      if ( pThis_2 == 2 )  // 若 pThis_2 == 2
        goto LABEL_40;  // 跳转 LABEL_40
      pThis_1 = *((uint32_t *)this + 1);  // 读 pThis_1 = this+4（宿主窗口）
      if ( *(uint8_t *)(pThis_1 + 17) == 0 )  // 若 *(uint8_t *)(pThis_1 + 17) == 0
        goto LABEL_40;  // 跳转 LABEL_40
      v13 = *(uint32_t *)(pThis_1 + 12);  // v13 = pThis_1+12
      if ( dword_79BE3C != v13 && dword_79BE342 != v13 && dword_79BE38 != v13 )  // 若 dword_79BE3C != v13 && dword_79BE342 != v13 && dword_79BE38 !=..
        goto LABEL_40;  // 跳转 LABEL_40
      if ( sub_5470B0(1) != -1 )  // 物品栏格子参数
      {
        pThis_E = sub_547300(*((uint32_t *)this + 14));  // 结果 = 物品栏数据
        LODWORD(pThis_E) = HIDWORD(pThis_E) + pThis_E;
        v15 = (int)pThis_E >= *((uint32_t *)dword_8F852C + 2) ? 0 : *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * pThis_E);  // 全局 dword_8F852C = 角色/物品栏管理器
        pThis_22 = ((SHIDWORD(pThis_E) >> 31) & 7) + HIDWORD(pThis_E);  // 调 SHIDWORD（取 64 位值高 32 位(带符号)）
        v16 = 32 * (SHIDWORD(pThis_E) % 8) + 339;  // 调 SHIDWORD（取 64 位值高 32 位(带符号)）
        v17 = 32 * (SHIDWORD(pThis_E) / 8) + 210;  // 调 SHIDWORD（取 64 位值高 32 位(带符号)）
        if ( v15 != 0 )  // 若 v15 != 0
          goto LABEL_50;  // 跳转 LABEL_50
      }
      v18 = sub_547450(this);  // 结果 = 物品栏格子重建
      v19 = v18;
      if ( v18 != 18
        && (pThis_22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, v18),  // 全局 dword_8F7C04 = 本机角色对象
            v16 = dword_724880[v19],
            v17 = dword_7248A8[v19],
            v15 = pThis_22,
            pThis_22 != 0) )
      {
LABEL_50:
        if ( dword_9B88D0 != v15 || dword_795378 != 1 )  // 若 dword_9B88D0 != v15 || dword_795378 != 1
        {
          pThis_22 = sub_44E8D0(*((char **)this + 2), (void *)0x1A, v15, 1);  // 结果 = 对象池借出（按池号取可用对象）
          if ( pThis_22 != 0 )  // 若 pThis_22 != 0
            LOBYTE(pThis_22) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pThis_22 + 48))(pThis_22, v16, v17, 28, 28);  // 虚槽+48 CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0）
        }
      }
      else
      {
LABEL_40:
        LOBYTE(pThis_22) = dword_9B88D0;
        if ( dword_9B88D0 != 0 && dword_795378 == 1 )  // 若 dword_9B88D0 != 0 && dword_795378 == 1
          LOBYTE(pThis_22) = sub_44E850(*((uint32_t **)this + 2), 26);  // 按池号批量回收活动对象
      }
    }
  }
  else
  {
    LOBYTE(pThis_22) = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 44))(this);  // this+44 剩余时间 ms
  }
  return pThis_22;
}


// ------------------------------------------------------------
// 0x5481A0 sub_5481A0 —— 物品栏页绘制（153 行：43C250/43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0 + 699E20/699E40）
// ------------------------------------------------------------
// 大白话：物品栏页绘制：43C250/43C410 布件 + 426BD0/69C780/69C7B0 图像 + 699E20/699E40。
char /*thiscall*/ sub_5481A0(uint32_t *this)  // 函数: 物品栏页绘制（153 行：43C250/43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0 + 699E20/699E40）
{
  int fld_e4; // eax
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  int v5; // ebx
  uint32_t *pThis_6; // edi
  uint8_t *pMem2; // eax
  uint8_t *v8; // eax
  uint8_t *pMem3; // eax
  uint32_t *pMem32; // edi
  int fld_e42; // ebx
  uint8_t *pMem4; // eax
  uint32_t *pMem42; // edi
  int fld_e43; // ebx
  uint8_t *pMem5; // edi
  int v16; // ebx
  uint8_t *pMem6; // eax
  uint8_t *pMem62; // edi
  int fld_e44; // ebx
  char result; // al
  void *Block; // [esp+10h] [ebp-10h]

  *(this + 4) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 16);  // this+16 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  if ( operator new(0x6Cu) != nullptr )  // 堆分配 108 字节对象
    fld_e4 = sub_43C250(*(this + 4), 0);  // 结果 = nengine::CNFrame 构造
  else
    fld_e4 = 0;
  *(this + 1) = fld_e4;  // this+4 = fld_e4
  *(uint32_t *)(fld_e4 + 28) = *(uint32_t *)(fld_e4 + 28);  // fld_e4+28 = *(uint32_t *)(fld_e4 + 28)
  *(uint32_t *)(fld_e4 + 32) = 383;  // fld_e4+32 = 383
  *(uint32_t *)(*(this + 1) + 68) = this;
  pMem = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v4 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 11, 12, 13, 11, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v4 = nullptr;  // v4 = nullptr 空指针
  *(this + 5) = v4;  // this+20 = v4
  sub_69A5F0(v4, 51, 383);  // 调 sub_69A5F0
  sub_69A840(*(this + 5));  // 调 sub_69A840
  v5 = 19;
  pThis_6 = this + 6;
  do
  {
    pMem2 = operator new(0x68u);  // 堆分配 104 字节对象
    if ( pMem2 != nullptr )  // 若 pMem2 非空
      v8 = sub_426BD0(pMem2);  // 结果 = nengine::IControl 构造
    else
      v8 = nullptr;  // v8 = nullptr 空指针
    *pThis_6 = v8;  // *pThis_6 写入 v8
    *((uint32_t *)v8 + 7) = 64;
    *((uint32_t *)v8 + 8) = 20;
    sub_69A5F0((uint32_t *)*pThis_6, v5, 153);  // 调 sub_69A5F0
    sub_69A840(*pThis_6);  // 调 sub_69A840
    v5 += 64;
    ++pThis_6;  // 自增pThis_6
  }
  while ( v5 < 275 );  // 当 v5 < 275 循环
  pMem3 = operator new(0x84u);  // 堆分配 132 字节对象
  pMem32 = pMem3;
  if ( pMem3 != nullptr )  // 若 pMem3 非空
  {
    fld_e42 = *(this + 4);  // fld_e42 = this+4
    sub_426BD0(pMem3);  // nengine::IControl 构造
    *pMem32 = &nengine::CNButton::`vftable';
    sub_69C780(v10);  // 调 sub_69C780
    sub_69C7B0(v11, 7, 8, 8, 7, 0, 0);  // 调 sub_69C7B0
  }
  else
  {
    v10 = nullptr;  // v10 = nullptr 空指针
  }
  *(this + 10) = v10;  // this+40 = v10
  sub_69A5F0(v10, 10, 0);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // 调 sub_69A840
  v12 = operator new(0x84u);  // 堆分配 132 字节对象
  v13 = v12;
  if ( v12 != nullptr )  // 若 v12 非空
  {
    v14 = *(this + 4);  // v14 = this+4
    sub_426BD0(v12);  // nengine::IControl 构造
    *v13 = &nengine::CNButton::`vftable';
    sub_69C780(pMem42);  // 调 sub_69C780
    sub_69C7B0(fld_e43, 1, 2, 3, 1, 0, 0);  // 调 sub_69C7B0
  }
  else
  {
    pMem42 = nullptr;  // pMem42 = nullptr 空指针
  }
  *(this + 11) = pMem42;  // this+44 = pMem42
  sub_69A5F0(pMem42, 229, 309);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  pMem5 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem5 != nullptr )  // 若 pMem5 非空
  {
    v16 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 24);
    sub_426BD0(pMem5);  // nengine::IControl 构造
    *(uint32_t *)pMem5 = &nengine::CNButton::`vftable';
    sub_69C780(v15);  // 调 sub_69C780
    sub_69C7B0(v16, 1, 2, 3, 7, 0, 0);  // 调 sub_69C7B0
  }
  else
  {
    v15 = nullptr;  // v15 = nullptr 空指针
  }
  *(this + 12) = v15;  // this+48 = v15
  sub_69A5F0(v15, 19, 344);  // 调 sub_69A5F0
  sub_69A840(*(this + 12));  // 调 sub_69A840
  sub_69A5F0((uint32_t *)*(this + 1), 320, 33);  // 调 sub_69A5F0
  v17 = operator new(0x2Cu);  // 堆分配 44 字节对象
  v18 = v17;
  if ( v17 != nullptr )  // 若 v17 非空
  {
    v19 = *(this + 4);  // v19 = this+4
    Block = (void *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
    v17[4] = 0;
    *(uint32_t *)v17 = &nengine::CNNumberSet::`vftable';
    sub_699E20(pMem6);  // 调 sub_699E20
    sub_699E40(Block, fld_e44, 25, 4);  // 调 sub_699E40
  }
  else
  {
    pMem62 = nullptr;  // pMem62 = nullptr 空指针
  }
  *(this + 13) = pMem62;  // this+52 = pMem62
  pMem62[24] = 1;
  result = byte_9B8054;
  if ( byte_9B8054 == 0 )  // 若 byte_9B8054 == 0
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
// 大白话：物品栏文本（4015C0/401740 字符串装配）。
int /*thiscall*/ sub_548540(uint32_t *this, unsigned int uArg2)  // 函数: 物品栏文本（4015C0/401740）
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // fld_e2 = this+2
  if ( 0x7FFFFFF - fld_e2 < uArg2 )  // 若 0x7FFFFFF - fld_e2 < uArg2
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
    v8 = 0;
    sub_401740(v5);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;  // fld_e2=this+8 物品 id
  *(this + 2) = result;  // this+8 = result
  return result;
}



// ------------------------------------------------------------
// 0x5485D0 sub_5485D0 —— 物品栏辅助（5014C0）
// ------------------------------------------------------------
// 大白话：物品栏辅助：5014C0 数据访问。
uint32_t */*thiscall*/ sub_5485D0(uint32_t *this)  // 物品栏辅助（5014C0）
{
  uint32_t **fld_e1; // eax
  uint32_t *v3; // esi
  uint32_t *result; // eax
  bool fld_e12; // zf
  uint32_t *v6; // ebx

  fld_e1 = (uint32_t **)*(this + 1);
  v3 = *fld_e1;
  *fld_e1 = fld_e1;  // *fld_e1 写入 fld_e1
  result = (uint32_t *)*(this + 1);
  result[1] = result;
  fld_e12 = v3 == (uint32_t *)*(this + 1);
  *(this + 2) = 0;  // this+8 = 0
  if ( !fld_e12 )  // 若 !fld_e12
  {
    do
    {
      v6 = (uint32_t *)*v3;
      sub_5014C0(v3);  // 调 sub_5014C0
      j__free(v3);  // 调 j__free
      result = (uint32_t *)*(this + 1);
      v3 = v6;
    }
    while ( v6 != result );  // 当 v6 != result 循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x548610 sub_548610 —— 物品栏文本 2（4014D0）
// ------------------------------------------------------------
// 大白话：物品栏文本 2（4014D0）。
uint32_t */*stdcall*/ sub_548610(int nArg1, int nArg2, uint32_t *uArg3)  // 物品栏文本 2（4014D0）
{
  uint32_t *pMem; // eax
  uint32_t *pMem2; // esi
  void *v6[9]; // [esp+0h] [ebp-24h] BYREF

  v6[5] = v6;
  pMem = operator new(0x28u);  // 堆分配 40 字节对象
  pMem2 = pMem;
  v6[4] = pMem;
  v6[8] = (void *)1;  // v6[8] 写入 (void *)1
  v6[3] = pMem;
  if ( pMem != nullptr )  // 若 pMem 非空
  {
    *pMem = nArg1;  // *pMem 写入 nArg1
    pMem[1] = nArg2;
    pMem[2] = *uArg3;  // pMem[2] 写入 *uArg3
    pMem[9] = 15;
    pMem[8] = 0;
    *((uint8_t *)pMem + 16) = 0;
    sub_4014D0((std::_String_base *)(pMem + 3), uArg3 + 1, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
  }
  return pMem2;
}



// ------------------------------------------------------------
// 0x5486B0 sub_5486B0 —— 物品栏标题组装（4015C0/4014D0/548610/548540，113 行）
// ------------------------------------------------------------
// 大白话：物品栏标题组装：4015C0/4014D0/548610/548540 拼标题与页码文本。
uint32_t */*cdecl*/ sub_5486B0(int nArg1)  // 物品栏标题组装
{
  uint32_t *v1; // eax
  unsigned int nLen; // edx
  signed int nLen2; // ecx
  int v4; // edi
  signed int i; // esi
  int v7; // esi
  uint32_t *v8; // edi
  void *pObj; // esi
  int v10; // [esp-14h] [ebp-C4h]
  int v11; // [esp-10h] [ebp-C0h]
  int nArg12; // [esp+4h] [ebp-ACh] BYREF
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
  int dword_796E502; // [esp+A0h] [ebp-10h]
  int v24; // [esp+ACh] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v1 = *(uint32_t **)dword_9B805C;
  if ( *(uint32_t *)dword_9B805C == dword_9B805C )  // 若 *(uint32_t *)dword_9B805C == dword_9B805C
  {
LABEL_4:
    sprintf(Buffer, "%d", nArg1);  // 字符串 “%d”
    nLen = (strlen(Buffer) - 1) / 3;  // 调 strlen（求串长）
    Src[nLen + strlen(Buffer)] = 0;
    nLen2 = strlen(Buffer) + nLen - 1;  // 调 strlen（求串长）
    v4 = 0;
    for ( i = strlen(Buffer) - 1; nLen2 >= 0; ++v4 )  // 循环：i = strlen(Buffer) - 1; nLen2 >= 0; ++v4
    {
      if ( i < 0 )  // 若 i < 0
        break;
      if ( v4 % 4 == 3 )  // 若 v4 % 4 == 3
        Src[nLen2] = 44;
      else
        Src[nLen2] = Buffer[i--];  // Src[nLen2] 写入 Buffer[i--]
      --nLen2;  // 自减nLen2
    }
    v20 = 15;
    v19 = 0;
    LOBYTE(v18) = 0;
    sub_4015C0(Src, strlen(Src));  // 【std::string构造赋值】
    nArg12 = nArg1;
    v24 = 0;
    v16 = 15;
    v15 = 0;
    LOBYTE(Block) = 0;
    sub_4014D0((std::_String_base *)v13, v17, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
    v7 = *(uint32_t *)dword_9B805C;  // v7 = dword_9B805C
    v11 = *(uint32_t *)(*(uint32_t *)dword_9B805C + 4);
    v10 = *(uint32_t *)dword_9B805C;  // v10 = dword_9B805C
    LOBYTE(v24) = 1;
    v8 = sub_548610(v10, v11, &nArg12);  // 结果 = 物品栏文本 2（4014D0）
    sub_548540(&dword_9B8058, 1u);  // 物品栏文本（4015C0/401740）
    *(uint32_t *)(v7 + 4) = v8;  // v7+4 = v8
    *(uint32_t *)v8[1] = v8;
    if ( v16 >= 0x10 )  // 若 v16 >= 0x10
      j__free(Block);  // 调 j__free
    v16 = 15;
    v15 = 0;
    LOBYTE(Block) = 0;
    v24 = -1;
    if ( v20 >= 0x10 )  // 若 v20 >= 0x10
      j__free(v18);  // 调 j__free
    v20 = 15;
    v19 = 0;
    LOBYTE(v18) = 0;
    if ( (unsigned int)dword_9B8060 > 0xA )  // 若 (unsigned int)dword_9B8060 > 0xA
    {
      pObj = *(void **)(dword_9B805C + 4);
      if ( pObj != (void *)dword_9B805C )  // 若 pObj != (void *)dword_9B805C
      {
        **((uint32_t **)pObj + 1) = *(uint32_t *)pObj;
        *(uint32_t *)(*(uint32_t *)pObj + 4) = *((uint32_t *)pObj + 1);
        if ( *((uint32_t *)pObj + 9) >= 0x10u )  // 若 *((uint32_t *)pObj + 9) >= 0x10u
          j__free(*((void **)pObj + 4));  // 调 j__free
        *((uint32_t *)pObj + 9) = 15;
        *((uint32_t *)pObj + 8) = 0;
        *((uint8_t *)pObj + 16) = 0;
        j__free(pObj);  // 调 j__free
        --dword_9B8060;  // 自减dword_9B8060
      }
    }
    return (uint32_t *)sub_5486B0(nArg1);  // 物品栏标题组装
  }
  else
  {
    while ( v1[2] != nArg1 )  // 当 v1[2] != nArg1 循环
    {
      v1 = (uint32_t *)*v1;
      if ( v1 == (uint32_t *)dword_9B805C )  // 若 v1 == (uint32_t *)dword_9B805C
        goto LABEL_4;  // 跳转 LABEL_4
    }
    if ( v1[9] < 0x10u )  // 若 v1[9] < 0x10u
      return v1 + 4;
    else
      return (uint32_t *)v1[4];
  }
}



// ------------------------------------------------------------
// 0x548930 CNRDItemInventoryWindow__vmt0 —— CNRDItemInventoryWindow__vmt0 构造（202 行：4CE8A0 + 547450/4F2E40/5470B0/5486B0 + 69A110/484FA0/488670）
// ------------------------------------------------------------
// 大白话：物品栏窗构造：4CE8A0 基类 + 547450/4F2E40/5470B0/5486B0 装配 + 69A110/484FA0/488670。
uint32_t */*thiscall*/ sub_548930(uint32_t *this, int pArg2)  // 【CNRDItemInventoryWindow__vmt0】
{
  uint32_t *result; // eax
  uint32_t *pThis; // edx
  int v4; // eax
  int v5; // ecx
  int *v6; // esi
  unsigned int v7; // ecx
  int v8; // edi
  int v9; // edi
  int v10; // ebx
  int pObj3; // eax
  int v12; // edi
  int j; // esi
  int pObj2; // eax
  int pArg22; // ebx
  uint32_t *pThis2; // edi
  int pHostCtrl; // eax  | +0x0008 → 宿主控件（0x5474B0: *(*(this+8)+2504)==14 判摆摊模式页签）（CNRDItemInventoryWindow；va=005474B0）
  int v18; // eax
  int v19; // eax
  uint32_t *dword_8F852C2; // edx
  int k; // esi
  int v22; // eax
  int v23; // eax
  int pObj; // ecx
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
  int pObj4; // eax
  int i; // [esp+0h] [ebp-10h]
  int v40; // [esp+4h] [ebp-Ch]
  int v41; // [esp+8h] [ebp-8h]

  result = (uint32_t *)dword_8F7C04;  // 全局 dword_8F7C04 = 本机角色对象
  pThis = this;
  if ( dword_8F7C04 == 0 )  // 全局 dword_8F7C04 = 本机角色对象
    return result;
  result = (uint32_t *)pArg2;
  if ( pArg2 != *(this + 1) )  // 判定 “+4 宿主窗口”
    return result;
  v4 = -12 - (uint32_t)this;
  v5 = -14 - (uint32_t)this;
  v41 = 0;
  v6 = pThis + 6;
  v40 = -12 - (uint32_t)pThis;
  for ( i = -14 - (uint32_t)pThis; ; v5 = i )  // 循环：i = -14 - (uint32_t)pThis; ; v5 = i
  {
    v7 = (unsigned int)v6 + v5;
    if ( pThis[14] != v41 )  // 若 pThis[14] != v41
      v7 = (unsigned int)v6 + v4;
    v8 = *v6;
    if ( *(uint8_t *)(*v6 + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(v8 + 12)  // CNRDItemInventoryWindow__vmt0 构造（202 行：4CE8A0 + 547450/4F2E40/5470B0/5486B0 + 69A110/484FA0/488670）
       || dword_79BE34 == *(uint32_t *)(v8 + 12)
       || dword_79BE38 == *(uint32_t *)(v8 + 12)) )
    {
      ++v7;  // 自增v7
    }
    v9 = *(uint32_t *)(*v6 + 24);
    v10 = *(uint32_t *)(*v6 + 20);
    pObj3 = sub_418DD0((uint32_t *)pThis[4], v7);  // 调 sub_418DD0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v10, v9, dword_79C0B0);  // 调用虚函数槽 +152
    ++v6;  // 自增v6
    if ( ++v41 >= 4 )  // 若 ++v41 >= 4
      break;
    v4 = v40;
    pThis = this;
  }
  v12 = 8;
  for ( j = 0; j < 10; ++j )  // 循环：j = 0; j < 10; ++j
  {
    pObj2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, v12);  // 全局 dword_8F7C04 = 本机角色对象
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)pObj2 + 8))(  // 虚槽+8 CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTTON2/DISSOLVE
        pObj2,
        dword_7248A0[j],
        dword_7248C8[j],
        0,
        1);
    ++v12;  // 自增v12
  }
  if ( pt.x < 332 || pt.x >= 598 || pt.y < 75 || pt.y >= 178 )  // 若 pt.x < 332 || pt.x >= 598 || pt.y < 75 || pt.y >= 178
  {
    pArg22 = pArg2;
  }
  else
  {
    pArg22 = pArg2;
    if ( *(uint8_t *)(pArg2 + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(pArg2 + 12)
       || dword_79BE34 == *(uint32_t *)(pArg2 + 12)
       || dword_79BE38 == *(uint32_t *)(pArg2 + 12)) )
    {
      pThis2 = this;
      pHostCtrl = *(this + 2);  // 读 fld_e2 = this+8（宿主控件）
      if ( *(uint32_t *)(pHostCtrl + 2504) != 2  // fld_e2=this+8 pHostCtrl
        || (v18 = sub_4CE8A0((uint32_t *)dword_8F84D0, *(uint32_t *)(pHostCtrl + 2512))) == 0  // fld_e2=this+8 pHostCtrl
        || (v19 = *(uint32_t *)(v18 + 92)) < 8 )
      {
        v19 = sub_547450(this);  // 结果 = 物品栏格子重建
      }
      if ( v19 != 18 )  // 若 v19 != 18
        sub_4F2E40(dword_724880[v19], dword_7248A8[v19]);  // 调 sub_4F2E40
      goto LABEL_35;  // 跳转 LABEL_35
    }
  }
  pThis2 = this;
LABEL_35:
  dword_8F852C2 = dword_8F852C;  // 全局 dword_8F852C = 角色/物品栏管理器
  for ( k = 0; k < 32; ++k )  // 循环：k = 0; k < 32; ++k
  {
    switch ( pThis2[14] )
    {
      case 0:  // case 0
        v22 = 9;
        break;
      case 1:  // case 1
        v22 = 41;
        break;
      case 2:  // case 2
        v22 = 73;
        break;
      case 3:  // case 3
        v22 = 105;
        break;
      case 4:  // case 4
        v22 = 137;
        break;
      default:
        v22 = 0;
        break;
    }
    v23 = k + v22;
    if ( v23 < dword_8F852C2[2] )  // 若 v23 < dword_8F852C2[2]
    {
      pObj = *(uint32_t *)(dword_8F852C2[3] + 4 * v23);
      if ( pObj != 0 )  // 若 pObj != 0
      {
        (*(void (/*thiscall*/ **)(int, int, unsigned int, uint32_t, int))(*(uint32_t *)pObj + 8))(  // 虚槽+8 CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTTON2/DISSOLVE
          pObj,
          32 * (k & 7) + 339,
          32 * ((unsigned int)k >> 3) + 210,
          0,
          1);
        dword_8F852C2 = dword_8F852C;  // 全局 dword_8F852C = 角色/物品栏管理器
      }
    }
  }
  if ( *(uint8_t *)(pArg22 + 17) != 0 )  // 若 *(uint8_t *)(pArg22 + 17) != 0
  {
    if ( dword_79BE3C == *(uint32_t *)(pArg22 + 12)  // 若 dword_79BE3C == *(uint32_t *)(pArg22 + 12
      || (v25 = *(uint32_t *)(pArg22 + 12), dword_79BE34 == v25)
      || dword_79BE38 == v25 )
    {
      v26 = sub_5470B0(1);  // 结果 = 物品栏格子参数
      if ( v26 != -1 )  // 若 v26 != -1
        sub_4F2E40(32 * (v26 % 8) + 339, 32 * (v26 / 8) + 210);  // 调 sub_4F2E40
    }
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);  // 调用虚函数槽 +72
  v27 = *(uint32_t *)dword_79C0B0;  // v27 = dword_79C0B0
  v28 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));  // 全局 dword_8F852C = 角色/物品栏管理器
  v29 = sub_5486B0(v28);  // 结果 = 物品栏标题组装
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(v27 + 80))(dword_79C0B0, 333, 382, -4265479, v29);  // 调用虚函数槽 +80
  v30 = *(uint32_t *)dword_79C0B0;  // v30 = dword_79C0B0
  v31 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8));  // 全局 dword_8F852C = 角色/物品栏管理器
  v32 = sub_5486B0(v31);  // 结果 = 物品栏标题组装
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(v30 + 80))(dword_79C0B0, 462, 382, -4265479, v32);  // 调用虚函数槽 +80
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
  v33 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(  // 全局 dword_8F852C = 角色/物品栏管理器
          *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4),  // 全局 dword_8F852C = 角色/物品栏管理器
          -1);
  sub_69A110(366, 347, v33, (int)&byte_7947AC);  // 调 sub_69A110
  v34 = *((uint32_t *)dword_8F852C + 1);  // 全局 dword_8F852C = 角色/物品栏管理器
  v35 = sub_484FA0();  // 结果 = 全局时间系数计算（+732 与 +746 相乘）
  v36 = (uint64_t)sub_4049C0(0.0, 90.0, v34, v35);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v37 = (uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
  *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0+48 = 0
  v37[13] = 0;
  v37[14] = v36 + 445;  // v37[14] 写入 v36 + 445
  v37[15] = 480;
  pObj4 = sub_418DD0((uint32_t *)pThis2[4], 5u);  // 调 sub_418DD0
  if ( pObj4 != 0 )  // 若 pObj4 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 445, 349, dword_79C0B0);  // 调用虚函数槽 +152
  return sub_488670((uint32_t *)dword_79C0B0);  // 视口重置 640x480
}


// ============================================================
// 【分区 11】时装栏 CNRDAvatarInventoryWindow（0x548D40-0x549AC0）
// 结构与物品栏同构：vmt1C=刷新（182 行）、vmt8=Update（CLICK_BUTTON2/
// WINDOW_CLOSE）、vmt14=关闭清理（44BC30）。
// ============================================================
// ------------------------------------------------------------
// 0x548D40 sub_548D40 —— 52 行小辅助
// ------------------------------------------------------------
// 大白话：52 行小辅助（时装栏前置数据处理）。
int /*thiscall*/ sub_548D40(uint32_t *this)  // 函数: 52 行小辅助
{
  void (/*thiscall*/ ***fld_e1)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e5)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e6)(uint32_t, int); // ecx
  uint32_t *pThis_7; // edi
  int i; // ebx
  void (/*thiscall*/ ***fld_e9)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  int result; // eax

  fld_e1 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( fld_e1 != nullptr )  // 若 fld_e1 非空
    (**fld_e1)(fld_e1, 1);
  fld_e4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 4);  // this+4 宿主对象
  *(this + 1) = 0;  // this+4 = 0
  if ( fld_e4 != nullptr )  // 若 fld_e4 非空
    (**fld_e4)(fld_e4, 1);
  fld_e5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 4) = 0;  // this+16 = 0
  if ( fld_e5 != nullptr )  // 若 fld_e5 非空
    (**fld_e5)(fld_e5, 1);
  fld_e6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  *(this + 5) = 0;  // this+20 = 0
  if ( fld_e6 != nullptr )  // 若 fld_e6 非空
    (**fld_e6)(fld_e6, 1);
  *(this + 6) = 0;  // this+24 = 0
  pThis_7 = this + 7;  // this+7 路径尾终止位
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
  {
    if ( *pThis_7 != 0 )  // 若 *pThis_7 != 0
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_7)(*pThis_7, 1);  // pThis_7=this+7 路径尾终止位
    *pThis_7++ = 0;  // *pThis_7++ 写入 0
  }
  fld_e9 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( fld_e9 != nullptr )  // 若 fld_e9 非空
    (**fld_e9)(fld_e9, 1);
  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  result = 0;
  *(this + 9) = 0;  // this+36 = 0
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    result = (**fld_e10)(fld_e10, 1);
  *(this + 10) = 0;  // this+40 = 0
  return result;
}



// ------------------------------------------------------------
// 0x548DE0 CNRDAvatarInventoryWindow__vmtC —— CNRDAvatarInventoryWindow__vmtC 打开槽（429830 + 42B340）
// ------------------------------------------------------------
// 大白话：时装栏打开槽：429830 动画 + 42B340。
char /*thiscall*/ CNRDAvatarInventoryWindow__vmtC(int this)  // 函数: CNRDAvatarInventoryWindow__vmtC 打开槽（429830 + 42B340）
{
  bool v1; // zf
  int v4; // eax

  v1 = dword_8F7C04 == 0;  // 全局 dword_8F7C04 = 本机角色对象
  *(uint32_t *)(this + 44) = dword_8F7C04;  // 全局 dword_8F7C04 = 本机角色对象
  if ( v1 )  // 若 v1
    return 0;
  v4 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // 结果 = 表按键查找（uint16）
  sub_42B340(v4);  // 虚拟角色惰性创建（0x294 字节）
  (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 40) + 32))(*(uint32_t *)(this + 40), 12);  // 调用虚函数槽 +32
  return 1;
}



// ------------------------------------------------------------
// 0x548E20 sub_548E20 —— 时装栏数据（44 行）
// ------------------------------------------------------------
// 大白话：时装栏数据：44 行取时装槽位数据。
int /*thiscall*/ sub_548E20(uint32_t *this, char pszArg2)  // 函数: 时装栏数据（44 行）
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
  while ( 1 )  // 当 1 循环
  {
    v4 = v3 / 7;
    v5 = 32 * (v3 % 7);
    if ( pszArg2 != 0 )  // 若 pszArg2 != 0
    {
      v6 = v5 + 349;
      v7 = 32 * v4 + 243;
    }
    else
    {
      v6 = v5 + 347;
      v7 = 32 * v4 + 241;
    }
    if ( x >= v6 )  // 若 x >= v6
    {
      v8 = 4 * (pszArg2 == 0) + 28;
      x = pt.x;
      if ( pt.x < v8 + v6 && pt.y >= v7 && pt.y < v7 + v8 )  // 若 pt.x < v8 + v6 && pt.y >= v7 && pt.y < v7 + v8
        break;
    }
    if ( ++v3 >= 21 )  // 若 ++v3 >= 21
      return -1;  // 返回 -1（0xFFFFFFFF）
  }
  return v3 + 7 * *(this + 12);  // this+12 物品类型号
}



// ------------------------------------------------------------
// 0x548EC0 CNRDAvatarInventoryWindow__vmt10 —— CNRDAvatarInventoryWindow__vmt10 状态切换（44AB50 + 44E850 + 540960）
// ------------------------------------------------------------
// 大白话：时装栏状态切换：44AB50 + 44E850 + 540960。
int /*thiscall*/ CNRDAvatarInventoryWindow__vmt10(uint32_t *this)  // 函数: CNRDAvatarInventoryWindow__vmt10 状态切换（44AB50 + 44E850 + 540960）
{
  uint32_t *fld_e2; // ecx
  int v3; // eax
  int result; // eax

  fld_e2 = (uint32_t *)*(this + 2);
  v3 = fld_e2[26];
  if ( (v3 == 9 || v3 == 2) && fld_e2[27] != 0 )  // 若 (v3 == 9 || v3 == 2) && fld_e2[27] != 0
    sub_44AB50(fld_e2, 0, 12);  // 页签切换
  if ( dword_9B88D0 != 0 && dword_795378 == 2 )  // 若 dword_9B88D0 != 0 && dword_795378 == 2
    sub_44E850((uint32_t *)*(this + 2), 26);  // 按池号批量回收活动对象
  result = sub_540960(*(uint32_t **)(*(this + 2) + 116));  // 结果 = 数量输入框刷新
  *(this + 11) = 0;  // this+44 = 0
  return result;
}



// ------------------------------------------------------------
// 0x548F20 sub_548F20 —— 10 行小辅助
// ------------------------------------------------------------
// 大白话：10 行小辅助（时装栏）。
bool sub_548F20()  // 10 行小辅助
{
  return pt.x >= 332 && pt.x < 599 && pt.y >= 74 && pt.y < 232;
}



// ------------------------------------------------------------
// 0x548F50 CNRDAvatarInventoryWindow__vmt18 —— CNRDAvatarInventoryWindow__vmt18 按钮动作（CLICK_BUTTON2 + 44BBA0）
// ------------------------------------------------------------
// 大白话：时装栏按钮动作：CLICK_BUTTON2 + 44BBA0 显示。
char /*thiscall*/ CNRDAvatarInventoryWindow__vmt18(uint32_t *this)  // 函数: CNRDAvatarInventoryWindow__vmt18 按钮动作（CLICK_BUTTON2 + 44BBA0）
{
  int fld_e1; // eax  | +0x0004 → 宿主窗口（0x5497A0: pArg2 == *(this+4) 分派）【推断】（CNRDAvatarInventoryWindow；va=005497A0）
  uint32_t *fld_e2; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int pObj; // esi
  int v8; // eax

  if ( dword_8F7C04 == 0 )  // 全局 dword_8F7C04 = 本机角色对象
    return 0;
  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( *(uint8_t *)(fld_e1 + 17) == 0 )  // 若 *(uint8_t *)(fld_e1 + 17) == 0
    return 0;
  if ( dword_79BE3C != *(uint32_t *)(fld_e1 + 12) )  // 若 dword_79BE3C != *(uint32_t *)(fld_e1 + 12)
    return 0;
  fld_e2 = (uint32_t *)*(this + 2);
  if ( fld_e2[626] != 2 )  // 若 fld_e2[626] != 2
    return 0;
  if ( fld_e2[627] == 5 )  // 若 fld_e2[627] == 5
  {
    v4 = *(uint32_t *)(dword_8F8538 + 16);  // 全局 dword_8F8538 = 随身影身/占位管理器
    v5 = fld_e2[629];
    if ( v5 < *(uint32_t *)(v4 + 8) )  // 若 v5 < *(uint32_t *)(v4 + 8)
    {
      v6 = *(uint32_t *)(v4 + 12);  // v6 = v4+12
      pObj = *(uint32_t *)(v6 + 4 * v5);
      if ( pObj != 0 )  // 若 pObj != 0
      {
        v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj + 16))(*(uint32_t *)(v6 + 4 * v5));  // 调用虚函数槽 +16
        if ( sub_4F2D40(*(uint32_t *)(v8 + 4)) != 2 || *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj) > 7 )  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
        {
          sub_44BBA0((uint32_t *)*(this + 2), 0, 0);  // 窗口显示切换（WINDOW_SHOW 音效）
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
        }
      }
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x549000 sub_549000 —— 时装栏数据 2（24 行）
// ------------------------------------------------------------
// 大白话：时装栏数据 2：24 行。
int sub_549000()  // 时装栏数据 2
{
  int result; // eax
  LONG v1; // ecx
  LONG v2; // edx

  result = 0;
  while ( 1 )  // 当 1 循环
  {
    v1 = dword_724904[result];
    v2 = dword_724924[result];
    if ( pt.x >= v1 && pt.x < v1 + 28 && pt.y >= v2 && pt.y < v2 + 28 )  // 若 pt.x >= v1 && pt.x < v1 + 28 && pt.y >= v2 && pt.y < v2 + 28
      break;
    if ( ++result > 7 )  // 若 ++result > 7
      return 18;
  }
  return result;
}



// ------------------------------------------------------------
// 0x549050 CNRDAvatarInventoryWindow__vmt14 —— CNRDAvatarInventoryWindow__vmt14 关闭槽（549000 + 44BC30 + 548E20）
// ------------------------------------------------------------
// 大白话：时装栏关闭槽：549000 + 44BC30 + 548E20。
char /*thiscall*/ CNRDAvatarInventoryWindow__vmt14(int this)  // 函数: CNRDAvatarInventoryWindow__vmt14 关闭槽（549000 + 44BC30 + 548E20）
{
  int pOwnerWnd; // eax  | +0x0004 → 宿主窗口（0x5497A0: pArg2 == *(this+4) 分派）【推断】（CNRDAvatarInventoryWindow；va=005497A0）
  int v3; // eax
  int v4; // ebx
  int fld_2C; // eax  | +0x002C → ★ 角色对象（CNRDAvatarInventoryWindow；va=005497A0）
  void *pObj2; // esi
  int v7; // eax
  int v9; // ebx
  int v10; // ecx
  int pObj; // esi
  int v12; // eax
  int v13; // [esp-8h] [ebp-14h]
  int v14; // [esp-8h] [ebp-14h]
  void *v15; // [esp-4h] [ebp-10h]

  pOwnerWnd = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0 || dword_79BE3C != *(uint32_t *)(pOwnerWnd + 12) )  // 若 *(uint8_t *)(fld_4 + 17) == 0 || dword_79BE3C != *(uint32_t *)..
    return 0;
  v3 = sub_549000();  // 结果 = 时装栏数据 2
  v4 = v3;
  if ( v3 != 18 )  // 若 v3 != 18
  {
    fld_2C = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 44) + 792))(*(uint32_t *)(this + 44), v3);  // 调用虚函数槽 +792
    pObj2 = (void *)fld_2C;
    if ( fld_2C != 0 )  // 若 fld_2C != 0
    {
      v13 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_2C + 16))(fld_2C) + 68);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
      v7 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pObj2 + 16))(pObj2);  // 调用虚函数槽 +16
      sub_44BC30(*(uint32_t **)(this + 8), (void *)2, 6, *(uint32_t *)(v7 + 4), v4, v13, pObj2);  // 拾取模式状态 + ICON_PICK/ITEM_PICK 音效
      return 1;
    }
  }
  v9 = sub_548E20((uint32_t *)this, 1);  // 结果 = 时装栏数据
  if ( v9 == -1 )  // 若 v9 == -1
    return 0;
  if ( v9 >= *((uint32_t *)dword_8F8534 + 2) )  // 若 v9 >= *((uint32_t *)dword_8F8534 + 2)
    return 0;
  v10 = *((uint32_t *)dword_8F8534 + 3);  // dword_8F8534（技能槽装载对象）
  pObj = *(uint32_t *)(v10 + 4 * v9);
  if ( pObj == 0 )  // 若 pObj == 0
    return 0;
  v15 = *(void **)(v10 + 4 * v9);
  v14 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 68);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);  // 调用虚函数槽 +16
  sub_44BC30(*(uint32_t **)(this + 8), (void *)2, 7, *(uint32_t *)(v12 + 4), v9, v14, v15);  // 拾取模式状态 + ICON_PICK/ITEM_PICK 音效
  return 1;
}



// ------------------------------------------------------------
// 0x549110 CNRDAvatarInventoryWindow__vmt1C —— CNRDAvatarInventoryWindow__vmt1C 内容刷新（182 行：486820/44A980/548F20/484AF0/540DE0/486530）
// ------------------------------------------------------------
// 大白话：时装栏内容刷新：486820/44A980/548F20/484AF0/540DE0/486530 重排（182 行）。
char /*thiscall*/ sub_549110(int this)  // 【CNRDAvatarInventoryWindow__vmt1C】
{
  int pOwnerWnd; // eax  | +0x0004 → 宿主窗口（0x5497A0: pArg2 == *(this+4) 分派）【推断】（CNRDAvatarInventoryWindow；va=005497A0）
  uint32_t *pHostCtrl; // edi
  int v5; // eax
  int fld_2C; // eax  | +0x002C → ★ 角色对象（CNRDAvatarInventoryWindow；va=005497A0）
  int pObj3; // esi
  int v8; // edi
  uint32_t *v9; // eax
  int v10; // edi
  uint32_t *v11; // eax
  int v12; // eax
  int v13; // eax
  int pObj7; // eax
  int pObj8; // esi
  uint32_t *v16; // eax
  int v17; // eax
  int v18; // edi
  int pObj9; // eax
  int pObj11; // esi
  int pObj4; // eax
  int pObj5; // esi
  uint32_t *v23; // eax
  int v24; // eax
  int v25; // ebx
  int pObj; // eax
  int v27; // edi
  int pObj10; // eax
  int pObj6; // edi
  int v30; // eax
  uint32_t *fld_82; // [esp+8h] [ebp-Ch]
  int v32; // [esp+Ch] [ebp-8h]
  int pObj2; // [esp+10h] [ebp-4h]
  int v34; // [esp+10h] [ebp-4h]

  pOwnerWnd = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0 || dword_79BE34 != *(uint32_t *)(pOwnerWnd + 12) )  // 若 *(uint8_t *)(fld_4 + 17) == 0 || dword_79BE34 != *(uint32_t *)..
    return 0;
  pHostCtrl = *(uint32_t **)(this + 8);  // this+8 物品 id
  fld_82 = pHostCtrl;  // fld_8=this+8 物品 id
  if ( pHostCtrl[626] != 2 )  // 若 fld_8[626] != 2
    return 0;
  v5 = pHostCtrl[627];  // fld_8=this+8 物品 id
  if ( v5 == 6 )  // 若 v5 == 6
  {
    fld_2C = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 44) + 792))(*(uint32_t *)(this + 44), pHostCtrl[629]);  // 调用虚函数槽 +792
    pObj3 = fld_2C;
    if ( fld_2C != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_2C + 16))(fld_2C) + 4) == pHostCtrl[628] )  // fld_8=this+8 物品 id
    {
      v8 = sub_548E20(0);  // 结果 = 时装栏数据
      if ( v8 != -1 )  // 若 v8 != -1
      {
        v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 172))(pObj3);  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
        if ( (uint8_t)sub_486820(v8, *v9, 1) != 0 )  // 施放拒绝提示（ALERT_1 音效 + sub_485510）
          return 1;
        if ( sub_44A980(v8) != 0 )  // 带界索引 getter
        {
          v10 = 0;
          while ( sub_44A980(v10) != 0 )  // 当 sub_44A980(v10) != 0 循环
          {
            if ( ++v10 >= 21 )  // 若 ++v10 >= 21
              return 0;
          }
          v11 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 172))(pObj3);  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
          sub_486820(v10, *v11, 1);  // 施放拒绝提示（ALERT_1 音效 + sub_485510）
          return 1;
        }
      }
    }
    return 0;
  }
  if ( v5 != 7 )  // 若 v5 != 7
  {
    if ( v5 != 5 )  // 若 v5 != 5
      return 0;
    pObj9 = sub_44A980(pHostCtrl[629]);  // 结果 = 带界索引 getter
    pObj11 = pObj9;
    if ( pObj9 == 0
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 16))(pObj9) + 4) != pHostCtrl[628]  // fld_8=this+8 物品 id
      || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj11 + 20))(pObj11, 2) == 0  // 虚槽+20 CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认购买（541A30/541B
      || *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj11 + 172))(pObj11) > 7 )  // CNRDAvatarInventoryWindow__vmt1C 内容刷新（182 行：486820/44A980/548F20/484AF0/540DE0/486530）
    {
      return 0;
    }
    if ( (uint8_t)sub_548F20(this) != 0 )  // 10 行小辅助
    {
      pObj4 = __RTDynamicCast(pObj11, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
      pObj5 = pObj4;
      if ( pObj4 == 0 || *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 172))(pObj4) > 7 )  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
        return 0;
      v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 172))(pObj5);  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
      sub_484AF0(pHostCtrl[629], 1, 3, *v23);  // 技能施放请求（包 op 19 变体：槽/参数/来源字段序不同）
      return 1;
    }
    v24 = sub_548E20(0);  // 结果 = 时装栏数据
    v25 = v24;
    if ( v24 != -1 )  // 若 v24 != -1
    {
      pObj = sub_44A980(v24);  // 结果 = 带界索引 getter
      pObj2 = pObj;
      if ( pObj == 0 )  // 若 pObj == 0
      {
LABEL_52:
        if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj11 + 44))(pObj11) <= 1 )  // 虚槽+44 IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 + 69A5F0/69A8
        {
          v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj11 + 44))(pObj11);  // 调用虚函数槽 +44
          sub_484AF0(pHostCtrl[629], v30, 1, v25);  // 技能施放请求（包 op 19 变体：槽/参数/来源字段序不同）
        }
        else
        {
          sub_540DE0(1, 4, pHostCtrl[629], 1, v25, 0, 0);  // 摊位列表构建
        }
        return 1;
      }
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 20))(pObj, 1) != 0 )  // 虚槽+20 CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认购买（541A30/541B
      {
        v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2);  // 调用虚函数槽 +16
        if ( *(uint32_t *)(v27 + 4) == *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj11 + 16))(pObj11) + 4) )  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
        {
LABEL_51:
          pHostCtrl = fld_82;  // fld_8=this+8 物品 id
          goto LABEL_52;  // 跳转 LABEL_52
        }
      }
      v25 = -1;
    }
    v34 = 0;
    while ( 1 )  // 当 1 循环
    {
      pObj10 = sub_44A980(v25);  // 结果 = 带界索引 getter
      pObj6 = pObj10;
      if ( pObj10 == 0 )  // 若 pObj10 == 0
        break;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj10 + 20))(pObj10, 1) != 0 )  // 虚槽+20 CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认购买（541A30/541B
      {
        v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj11 + 16))(pObj11);  // 调用虚函数槽 +16
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj6 + 16))(pObj6) + 4) == *(uint32_t *)(v32 + 4) )  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
          break;
      }
      if ( ++v34 >= 105 )  // 若 ++v34 >= 105
        goto LABEL_50;  // 跳转 LABEL_50
    }
    v25 = v34;
LABEL_50:
    if ( v25 == -1 )  // 若 v25 == -1
      return 0;
    goto LABEL_51;  // 跳转 LABEL_51
  }
  v12 = pHostCtrl[629];  // fld_8=this+8 物品 id
  if ( v12 >= *((uint32_t *)dword_8F8534 + 2) )  // 若 v12 >= *((uint32_t *)dword_8F8534 + 2)
    v13 = 0;
  else
    v13 = *(uint32_t *)(*((uint32_t *)dword_8F8534 + 3) + 4 * v12);  // dword_8F8534（技能槽装载对象）
  pObj7 = __RTDynamicCast(v13, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
  pObj8 = pObj7;
  if ( pObj7 == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj7 + 16))(pObj7) + 4) != pHostCtrl[628] )  // fld_8=this+8 物品 id
    return 0;
  if ( (uint8_t)sub_548F20(this) != 0 )  // 10 行小辅助
  {
    if ( *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 172))(pObj8) > 7 )  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
      return 0;
    v16 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 172))(pObj8);  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
    sub_486820(pHostCtrl[629], *v16, 1);  // 施放拒绝提示（ALERT_1 音效 + sub_485510）
    return 1;
  }
  else
  {
    v17 = sub_548E20(0);  // 结果 = 时装栏数据
    if ( v17 == -1 )  // 若 v17 == -1
      return 0;
    v18 = pHostCtrl[629];  // fld_8=this+8 物品 id
    if ( v17 == v18 )  // 若 v17 == v18
      return 0;
    sub_486530(v17, v18, 1);  // 请求 op 19：两槽交换
    return 1;
  }
}


// ------------------------------------------------------------
// 0x5494C0 CNRDAvatarInventoryWindow__vmt28 —— CNRDAvatarInventoryWindow__vmt28 槽（548E20/4872A0/549000/486820）
// ------------------------------------------------------------
// 大白话：时装栏槽：548E20/4872A0/549000/486820。
char /*thiscall*/ CNRDAvatarInventoryWindow__vmt28(int this)  // 函数: CNRDAvatarInventoryWindow__vmt28 槽（548E20/4872A0/549000/486820）
{
  int fld_4; // eax  | +0x0004 → 宿主窗口（0x5497A0: pArg2 == *(this+4) 分派）【推断】（CNRDAvatarInventoryWindow；va=005497A0）
  int v3; // eax
  int v5; // eax
  int fld_2C; // eax  | +0x002C → ★ 角色对象（CNRDAvatarInventoryWindow；va=005497A0）
  int v7; // esi
  uint32_t *v8; // eax

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( *(uint8_t *)(fld_4 + 17) == 0  // fld_4=this+4 宿主对象
    || dword_79BE38 != *(uint32_t *)(fld_4 + 12)  // CNRDAvatarInventoryWindow__vmt28 槽（548E20/4872A0/549000/486820）
    || *(uint32_t *)(*(uint32_t *)(this + 8) + 2504) != 0 )
  {
    return 0;
  }
  v3 = sub_548E20((uint32_t *)this, 1);  // 结果 = 时装栏数据
  if ( v3 != -1 )  // 若 v3 != -1
  {
    sub_4872A0(v3);  // 槽对象使用分发（按虚表 +20 类型分流）
    return 1;
  }
  v5 = sub_549000();  // 结果 = 时装栏数据 2
  if ( v5 == 18 )  // 若 v5 == 18
    return 0;
  fld_2C = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 44) + 792))(*(uint32_t *)(this + 44), v5);  // 调用虚函数槽 +792
  if ( fld_2C == 0 )  // 若 fld_2C == 0
    return 0;
  v7 = 0;
  while ( v7 < *((uint32_t *)dword_8F8534 + 2) && *(uint32_t *)(*((uint32_t *)dword_8F8534 + 3) + 4 * v7) != 0 )  // 当 v7 < *((uint32_t *)dword_8F8534 + 2) && *(uint32_t *)(*((uint3.. 循环
  {
    if ( ++v7 >= 21 )  // 若 ++v7 >= 21
      return 1;
  }
  v8 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_2C + 172))(fld_2C);  // 虚槽+172 朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
  sub_486820(v7, *v8, 1);  // 施放拒绝提示（ALERT_1 音效 + sub_485510）
  return 1;
}



// ------------------------------------------------------------
// 0x549580 CNRDAvatarInventoryWindow__vmt8 —— CNRDAvatarInventoryWindow__vmt8 Update（93 行：CLICK_BUTTON2/WINDOW_CLOSE + 69C690/560610）
// ------------------------------------------------------------
// 大白话：时装栏逐帧 Update：按钮 CLICK_BUTTON2/WINDOW_CLOSE 音；悬停格经消息 0x1A
// (模式 2) 弹时装提示、无则解除 26 号；+48 = 69C690(+40)；末尾调 560610(1)——
// 联动打开赛丽亚商店/时装店页【推断，560610 见 cashshop.cpp SERA_SHOP】。
int /*thiscall*/ CNRDAvatarInventoryWindow__vmt8(int this)  // 函数: CNRDAvatarInventoryWindow__vmt8 Update（93 行：CLICK_BUTTON2/WINDOW_CLOSE + 69C690/560610）
{
  int fld_10; // eax  | +0x0010 → 选中格子下标（0x549580: fld_10 = *(this+16)）【推断】（CNRDAvatarInventoryWindow；va=00549580）
  int fld_14; // eax  | +0x0014 → 悬停格子下标（0x549580: fld_14 = *(this+20)；44E8D0 消息 0x1A 用）【推断】（CNRDAvatarInventoryWindow；va=00549580）
  int fld_8; // eax  | +0x0008 → ★ 宿主控件（0x5497A0: *(*(this+8)+2504) == 2 判定当前页；0x5494C0 同址）（CNRDAvatarInventoryWindow；va=005497A0）
  int fld_4; // ecx  | +0x0004 → 宿主窗口（0x5497A0: pArg2 == *(this+4) 分派）【推断】（CNRDAvatarInventoryWindow；va=005497A0）
  int v6; // edi
  int v7; // eax
  int v8; // ecx
  int v9; // ebx
  int v10; // edi
  int v11; // eax
  int v12; // edi
  int fld_2C; // eax  | +0x002C → ★ 角色对象（CNRDAvatarInventoryWindow；va=005497A0）
  int fld_82; // eax  | +0x0008 → ★ 宿主控件（0x5497A0: *(*(this+8)+2504) == 2 判定当前页；0x5494C0 同址）（CNRDAvatarInventoryWindow；va=005497A0）
  int fld_1C; // eax  | +0x001C → ★ 格子总数（0x549580: fld_1C = *(this+28)）（CNRDAvatarInventoryWindow；va=00549580）
  int fld_20; // eax  | +0x0020 → ★ 格子像素尺寸（0x549580: fld_20 = *(this+32)；0x5497A0 32px/格）（CNRDAvatarInventoryWindow；va=00549580）
  int result; // eax

  fld_10 = *(uint32_t *)(this + 16);  // fld_10 = this+16
  if ( *(uint8_t *)(fld_10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_10 + 12) )  // 若 *(uint8_t *)(fld_10 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 44))(this);  // 调用虚函数槽 +44
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    sub_432EA0("WINDOW_CLOSE", -1, 0, 0);  // 字符串 “WINDOW_CLOSE”
  }
  fld_14 = *(uint32_t *)(this + 20);  // fld_14 = this+20
  if ( *(uint8_t *)(fld_14 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_14 + 12) )  // 若 *(uint8_t *)(fld_14 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    sub_44BBA0(*(uint32_t **)(this + 8), 0, 0);  // 窗口显示切换（WINDOW_SHOW 音效）
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  fld_8 = *(uint32_t *)(*(uint32_t *)(this + 8) + 2504);  // this+8 物品 id
  if ( fld_8 == 1 )  // 若 fld_8 == 1
    goto LABEL_21;  // 跳转 LABEL_21
  if ( fld_8 == 2 )  // 若 fld_8 == 2
    goto LABEL_21;  // 跳转 LABEL_21
  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( *(uint8_t *)(fld_4 + 17) == 0 )  // 若 *(uint8_t *)(fld_4 + 17) == 0
    goto LABEL_21;  // 跳转 LABEL_21
  v6 = *(uint32_t *)(fld_4 + 12);  // v6 = fld_4+12
  if ( dword_79BE3C != v6 && dword_79BE34 != v6 && dword_79BE38 != v6 )  // 若 dword_79BE3C != v6 && dword_79BE34 != v6 && dword_79BE38 != v6
    goto LABEL_21;  // 跳转 LABEL_21
  v7 = sub_548E20((uint32_t *)this, 1);  // 结果 = 时装栏数据
  if ( v7 != -1 )  // 若 v7 != -1
  {
    v8 = v7 >= *((uint32_t *)dword_8F8534 + 2) ? 0 : *(uint32_t *)(*((uint32_t *)dword_8F8534 + 3) + 4 * v7);  // dword_8F8534（技能槽装载对象）
    v9 = 32 * (v7 % 7) + 349;
    v10 = 32 * (v7 / 7) + 243;
    if ( v8 != 0 )  // 若 v8 != 0
      goto LABEL_38;  // 跳转 LABEL_38
  }
  v11 = sub_549000();  // 结果 = 时装栏数据 2
  v12 = v11;
  if ( v11 != 18
    && (fld_2C = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 44) + 792))(*(uint32_t *)(this + 44), v11),  // this+44 剩余时间 ms 等2字段
        v9 = dword_724904[v12],
        v10 = dword_724924[v12],
        v8 = fld_2C,
        fld_2C != 0) )
  {
LABEL_38:
    if ( dword_9B88D0 != v8 || dword_795378 != 2 )  // 若 dword_9B88D0 != v8 || dword_795378 != 2
    {
      fld_82 = sub_44E8D0(*(char **)(this + 8), (void *)0x1A, v8, 2);  // 结果 = 对象池借出（按池号取可用对象）
      if ( fld_82 != 0 )  // 若 fld_82 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)fld_82 + 48))(fld_82, v9, v10, 28, 28);  // 调用虚函数槽 +48
    }
  }
  else
  {
LABEL_21:
    if ( dword_9B88D0 != 0 && dword_795378 == 2 )  // 若 dword_9B88D0 != 0 && dword_795378 == 2
      sub_44E850(*(uint32_t **)(this + 8), 26);  // 按池号批量回收活动对象
  }
  fld_1C = *(uint32_t *)(this + 28);  // fld_1C = this+28
  if ( *(uint8_t *)(fld_1C + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_1C + 12) )  // 若 *(uint8_t *)(fld_1C + 17) != 0 && dword_79BE34 == *(uint32_t *..
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  fld_20 = *(uint32_t *)(this + 32);  // fld_20 = this+32
  if ( *(uint8_t *)(fld_20 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_20 + 12) )  // 若 *(uint8_t *)(fld_20 + 17) != 0 && dword_79BE34 == *(uint32_t *..
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  *(uint32_t *)(this + 48) = sub_69C690(*(uint32_t *)(this + 40));  // 取设备对象 +112 字段（类型或句柄）
  result = *(uint32_t *)(this + 24);  // result = this+24
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 若 *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *..
    return sub_560610(1);  // SERA_SHOP 赛丽亚商店事件（698F90/55FDB0/5604F0/432EA0/
  return result;  // result=this+24 页数上限
}



// ------------------------------------------------------------
// 0x5497A0 CNRDAvatarInventoryWindow__vmt0 —— CNRDAvatarInventoryWindow__vmt0 构造（141 行：4CE8A0/549000/4F2E40/548E20/4938F0/491D00/422E70）
// ------------------------------------------------------------
// 大白话：时装栏窗构造：4CE8A0/549000/4F2E40/548E20/4938F0/491D00/422E70 装配。
int /*thiscall*/ sub_5497A0(int this, int pArg2)  // 【CNRDAvatarInventoryWindow__vmt0】
{
  int result; // eax
  int pArg22; // ebx
  int i; // esi
  int fld_2C; // eax  | +0x002C → ★ 角色对象（CNRDAvatarInventoryWindow；va=005497A0）
  int fld_8; // eax  | +0x0008 → ★ 宿主控件（0x5497A0: *(*(this+8)+2504) == 2 判定当前页；0x5494C0 同址）（CNRDAvatarInventoryWindow；va=005497A0）
  int v8; // eax
  int v9; // eax
  int fld_30; // esi  | +0x0030 → ★ 网格列数（0x5497A0: 7 * *(this+48) 换算格子下标；32 像素/格）（CNRDAvatarInventoryWindow；va=005497A0）
  int v11; // edx
  uint32_t *dword_8F85342; // eax
  int pObj; // ecx
  int v14; // eax
  int dword_77F6DC2; // edx
  int v16; // esi
  const char *v17; // eax
  const char *v18; // eax
  const char *v19; // eax
  int v20; // [esp-8h] [ebp-7Ch]
  int v21; // [esp-8h] [ebp-7Ch]
  int dword_8F7C0C2; // [esp-8h] [ebp-7Ch]
  int v23; // [esp+8h] [ebp-6Ch]
  char Buffer[100]; // [esp+Ch] [ebp-68h] BYREF
  int dword_796E502; // [esp+70h] [ebp-4h]
  int dword_77F6DC22; // [esp+7Ch] [ebp+8h]

  result = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  pArg22 = pArg2;
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  if ( pArg2 == *(uint32_t *)(this + 4) )  // 若 pArg2 == *(uint32_t *)(this + 4)
  {
    for ( i = 0; i < 8; ++i )  // 循环：i = 0; i < 8; ++i
    {
      fld_2C = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 44) + 792))(*(uint32_t *)(this + 44), i);  // 调用虚函数槽 +792
      if ( fld_2C != 0 )  // 若 fld_2C != 0
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)fld_2C + 8))(  // 虚槽+8 CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTTON2/DISSOLVE
          fld_2C,
          dword_724904[i],
          dword_724924[i],
          0,
          1);
    }
    if ( pt.x >= 332
      && pt.x < 599
      && pt.y >= 74
      && pt.y < 232
      && *(uint8_t *)(pArg2 + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(pArg2 + 12)  // CNRDAvatarInventoryWindow__vmt0 构造（141 行：4CE8A0/549000/4F2E40/548E20/4938F0/491D00/422E70）
       || dword_79BE34 == *(uint32_t *)(pArg2 + 12)
       || dword_79BE38 == *(uint32_t *)(pArg2 + 12))
      && (*(uint32_t *)((fld_8 = *(uint32_t *)(this + 8)) + 2504) == 2  // this+8 物品 id
       && (v8 = sub_4CE8A0(*(uint32_t *)(fld_8 + 2512))) != 0
       && (v9 = *(uint32_t *)(v8 + 92)) <= 7
       || (v9 = sub_549000(this)) != 18) )  // 时装栏数据 2
    {
      sub_4F2E40(dword_724904[v9], dword_724924[v9]);  // 调 sub_4F2E40
    }
    fld_30 = 7 * *(uint32_t *)(this + 48);  // this+48 UDP 上报使能位
    v11 = fld_30 + 21;
    v23 = fld_30 + 21;
    if ( !__OFSUB__(fld_30, fld_30 + 21) )  // 若 !__OFSUB__(fld_30, fld_30 + 21)
    {
      dword_8F85342 = dword_8F8534;  // dword_8F8534（技能槽装载对象）
      do
      {
        if ( fld_30 < dword_8F85342[2] )  // 若 fld_30 < dword_8F85342[2]
        {
          pObj = *(uint32_t *)(dword_8F85342[3] + 4 * fld_30);
          if ( pObj != 0 )  // 若 pObj != 0
          {
            (*(void (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)pObj + 8))(  // 虚槽+8 CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTTON2/DISSOLVE
              pObj,
              32 * (fld_30 % 7) + 349,
              32 * (fld_30 / 7 - *(uint32_t *)(this + 48)) + 243,  // this+48 UDP 上报使能位
              0,
              1);
            dword_8F85342 = dword_8F8534;  // dword_8F8534（技能槽装载对象）
            pArg22 = pArg2;
            v11 = v23;
          }
        }
        ++fld_30;  // 自增fld_30
      }
      while ( fld_30 < v11 );  // 当 fld_30 < v11 循环
    }
    if ( *(uint8_t *)(pArg22 + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(pArg22 + 12)
       || dword_79BE34 == *(uint32_t *)(pArg22 + 12)
       || dword_79BE38 == *(uint32_t *)(pArg22 + 12)) )
    {
      v14 = sub_548E20(1);  // 结果 = 时装栏数据
      if ( v14 != -1 )  // 若 v14 != -1
        sub_4F2E40(32 * (v14 % 7) + 349, 32 * (v14 / 7 - *(uint32_t *)(this + 48)) + 243);  // 调 sub_4F2E40
    }
    dword_77F6DC2 = dword_77F6DC;  // dword_77F6DC（全局变焦值）
    dword_77F6DC = 1065353216;  // dword_77F6DC（全局变焦值）
    dword_77F6DC22 = dword_77F6DC2;
    v16 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C08 + 344))(dword_8F7C08);  // 虚槽+344 CNRDNpc__vmt158 交互槽（45E490/45E4D0/525CE0）
    sub_4938F0(v16);  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    sub_491D00(dword_79C0B0, 465, 213, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    dword_77F6DC = dword_77F6DC22;  // dword_77F6DC（全局变焦值）
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_7947AC);  // 调用虚函数槽 +72
    v20 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));  // 全局 dword_8F852C = 角色/物品栏管理器
    v17 = (const char *)sub_422E70(180);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v17, v20);  // 调 sprintf 格式化
    (*(void (/*cdecl*/ **)(int, int, int, int, char *, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      459,
      355,
      -4265479,
      Buffer,
      2);
    v21 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8));  // 全局 dword_8F852C = 角色/物品栏管理器
    v18 = (const char *)sub_422E70(181);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v18, v21);  // 调 sprintf 格式化
    (*(void (/*cdecl*/ **)(int, int, int, int, char *, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      459,
      372,
      -4265479,
      Buffer,
      2);
    dword_8F7C0C2 = dword_8F7C0C;  // 全局 dword_8F7C0C = 现金(Cash)
    v19 = (const char *)sub_422E70(182);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v19, dword_8F7C0C2);  // 调 sprintf 格式化
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      459,
      389,
      -4265479,
      Buffer);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
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
// 大白话：时装栏页绘制：43C250/43C410/69A5F0/69A840 + 69C980/43C4D0/43C630。
uint32_t */*thiscall*/ sub_549AC0(int *this)  // 时装栏页绘制
{
  uint8_t *pMem; // eax
  uint8_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax
  uint32_t *pMem3; // eax
  uint32_t *v7; // eax
  uint32_t *pMem4; // eax
  uint32_t *v9; // eax
  uint32_t *pMem5; // eax
  uint32_t *v11; // eax
  uint32_t *pMem6; // eax
  uint32_t *v13; // eax
  uint8_t *pMem7; // edi
  uint8_t *pMem8; // eax
  uint8_t *fld_e7; // eax

  pMem = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C250(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 20), 0);  // 结果 = nengine::CNFrame 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 1) = (int)v3;  // this+4 = (int)v3
  *((uint32_t *)v3 + 7) = *((uint32_t *)v3 + 7);
  *((uint32_t *)v3 + 8) = 383;
  *(uint32_t *)(*(this + 1) + 68) = this;
  pMem2 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 11, 12, 13, 11, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 4) = (int)v5;  // this+16 = (int)v5
  sub_69A5F0(v5, 51, 383);  // 调 sub_69A5F0
  sub_69A840(*(this + 4));  // 调 sub_69A840
  pMem3 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    v7 = sub_43C410(pMem3, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 20), 1, 2, 2, 1, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v7 = nullptr;  // v7 = nullptr 空指针
  *(this + 5) = (int)v7;  // this+20 = (int)v7
  sub_69A5F0(v7, 149, 0);  // 调 sub_69A5F0
  sub_69A840(*(this + 5));  // 调 sub_69A840
  pMem4 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    v9 = sub_43C410(pMem4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 20), 4, 5, 6, -1, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v9 = nullptr;  // v9 = nullptr 空指针
  *(this + 6) = (int)v9;  // this+24 = (int)v9
  sub_69A5F0(v9, 24, 315);  // 调 sub_69A5F0
  sub_69A840(*(this + 6));  // 调 sub_69A840
  sub_69C980(*(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 20), 4, 4, 4, 4, 0, 0);  // 调 sub_69C980
  *(uint8_t *)(*(this + 6) + 17) = 0;
  pMem5 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem5 != nullptr )  // 若 pMem5 非空
    v11 = sub_43C410(pMem5, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 4, 4, 5, 4, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v11 = nullptr;  // v11 = nullptr 空指针
  *(this + 7) = (int)v11;  // this+28 = (int)v11
  *((uint8_t *)v11 + 16) = 1;
  pMem6 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem6 != nullptr )  // 若 pMem6 非空
    v13 = sub_43C410(pMem6, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 6, 6, 7, 6, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v13 = nullptr;  // v13 = nullptr 空指针
  *(this + 8) = (int)v13;  // this+32 = (int)v13
  *((uint8_t *)v13 + 16) = 1;
  pMem7 = operator new(0x88u);  // 堆分配 136 字节对象
  if ( pMem7 != nullptr )  // 若 pMem7 非空
  {
    sub_43C4D0(pMem7, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 20), 7, 13);  // nengine::CNSlider 构造
    *(uint32_t *)pMem7 = &vftbl_nengine__CNVSlider;
  }
  else
  {
    pMem7 = nullptr;  // pMem7 = nullptr 空指针
  }
  *(this + 9) = (int)pMem7;  // this+36 = (int)pMem7
  pMem8 = operator new(0x74u);  // 堆分配 116 字节对象
  if ( pMem8 != nullptr )  // 若 pMem8 非空
    fld_e7 = sub_43C630(pMem8, *(this + 7), *(this + 8), *(this + 9));  // 结果 = nengine::CNVScroll 构造
  else
    fld_e7 = nullptr;  // fld_e7 = nullptr 空指针
  *(this + 10) = (int)fld_e7;  // this+40 = (int)fld_e7
  sub_69A5F0(fld_e7, 254, 207);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // 调 sub_69A840
  return sub_69A5F0((uint32_t *)*(this + 1), 320, 33);  // 调 sub_69A5F0
}



// ------------------------------------------------------------
// 0x549DC0 sub_549DC0 —— 23 行小辅助
// ------------------------------------------------------------
// 大白话：23 行小辅助（交易窗）。
int /*thiscall*/ sub_549DC0(int this)  // 函数: 23 行小辅助
{
  *(uint32_t *)(this + 16) = 0;  // this+16 = 0
  *(uint32_t *)(this + 20) = 0;  // this+20 = 0
  *(uint32_t *)(this + 24) = 0;  // this+24 = 0
  *(uint32_t *)(this + 132) = 0;  // this+132 = 0
  *(uint32_t *)(this + 136) = 0;  // this+136 = 0
  *(uint32_t *)(this + 140) = 0;  // this+140 = 0
  *(uint16_t *)(this + 148) = 48;  // this+148 = 48
  *(uint32_t *)(this + 212) = 0;  // this+212 = 0
  *(uint32_t *)(this + 220) = 0;  // this+220 = 0
  *(uint32_t *)(this + 144) = 0;  // this+144 = 0
  *(uint16_t *)(this + 180) = 48;  // this+180 = 48
  *(uint32_t *)(this + 216) = 0;  // this+216 = 0
  *(uint32_t *)(this + 224) = 0;  // this+224 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x549E10 CNRDItemTradeWindow__vmt1C —— CNRDItemTradeWindow__vmt1C 刷新槽（83 行：4848E0/422E70/44E8D0/432F00/540DE0）
// ------------------------------------------------------------
// 大白话：交易窗刷新槽：4848E0/422E70/44E8D0/432F00/540DE0 重排双方物品格（83 行）。
char /*thiscall*/ CNRDItemTradeWindow__vmt1C(int this)  // 函数: CNRDItemTradeWindow__vmt1C 刷新槽（83 行：4848E0/422E70/44E8D0/432F00/540DE0）
{
  int pOwnerWnd; // eax  | +0x0004 → 宿主窗口指针（CNRDItemTradeWindow；va=0054A820）
  uint32_t *pHostCtrl; // esi
  int v4; // eax
  int pObj; // edi
  char *v6; // eax
  int v7; // ebx
  int v8; // edi
  uint32_t *v9; // eax
  int pObj2; // edi
  unsigned int v11; // eax
  int v12; // ecx
  char *v13; // eax

  pOwnerWnd = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主窗口指针）
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0 )  // 若 *(uint8_t *)(fld_4 + 17) == 0
    return 0;
  if ( dword_79BE34 != *(uint32_t *)(pOwnerWnd + 12) )  // 若 dword_79BE34 != *(uint32_t *)(fld_4 + 12)
    return 0;
  pHostCtrl = *(uint32_t **)(this + 8);  // this+8 pHostCtrl
  if ( pHostCtrl[626] != 2 )  // 若 fld_8[626] != 2
    return 0;
  v4 = pHostCtrl[627];  // fld_8=this+8 pHostCtrl
  if ( v4 == 3 || v4 == 4 )  // 若 v4 == 3 || v4 == 4
  {
    v7 = 0;
  }
  else
  {
    if ( v4 != 7 )  // 若 v4 != 7
    {
      if ( v4 == 2 || v4 == 6 )  // 若 v4 == 2 || v4 == 6
      {
        pObj = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, pHostCtrl[629]);  // 全局 dword_8F7C04 = 本机角色对象
        if ( pObj != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 4) == pHostCtrl[628] )  // fld_8=this+8 pHostCtrl
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 80))(pObj) != 0 )  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
          {
            sub_4848E0(3, pHostCtrl[629], 1);  // 技能施放请求（包 op 19：来源/槽/参数，前置等级与占用校验）
          }
          else
          {
            v6 = sub_422E70(423);  // 调 sub_422E70
            sub_44E8D0(*(char **)(this + 8), (void *)0x1B, (int)v6, 0);  // 对象池借出（按池号取可用对象）
          }
          return 1;
        }
      }
      return 0;
    }
    v7 = 1;
  }
  v8 = pHostCtrl[629];  // fld_8=this+8 pHostCtrl
  v9 = sub_432F00(v7);  // 结果 = 按类型取全局列表对象
  if ( v8 >= v9[2] )  // 若 v8 >= v9[2]
    return 0;
  pObj2 = *(uint32_t *)(v9[3] + 4 * v8);
  if ( pObj2 == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 4) != pHostCtrl[628] )  // fld_8=this+8 pHostCtrl
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 80))(pObj2) != 0 )  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  {
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2);  // 调用虚函数槽 +44
    v12 = pHostCtrl[629];  // fld_8=this+8 pHostCtrl
    if ( v11 <= 1 )  // 若 v11 <= 1
      sub_4848E0(v7, v12, 1);  // 技能施放请求（包 op 19：来源/槽/参数，前置等级与占用校验）
    else
      sub_540DE0(*(int **)(*(uint32_t *)(this + 8) + 116), 1, v7, v12, 4, 0, 0, 0);  // 摊位列表构建
    return 1;
  }
  else
  {
    v13 = sub_422E70(422);  // 调 sub_422E70
    sub_44E8D0(*(char **)(this + 8), (void *)0x1B, (int)v13, 0);  // 对象池借出（按池号取可用对象）
    return 1;
  }
}



// ------------------------------------------------------------
// 0x549FD0 sub_549FD0 —— 交易窗公共更新（40 行）
// ------------------------------------------------------------
// 大白话：交易窗公共更新（40 行）：同步对方就绪/锁定状态。
int /*thiscall*/ sub_549FD0(uint32_t *this)  // 函数: 交易窗公共更新（40 行）
{
  int fld_e1; // eax
  int v2; // edi
  int i; // ecx
  int v5; // [esp+Ch] [ebp-Ch]
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  v2 = 0;
  v7 = 0;
  v6 = *(uint32_t *)(fld_e1 + 20);  // v6 = fld_e1+20
  v5 = *(uint32_t *)(fld_e1 + 24);  // v5 = fld_e1+24
  while ( 2 )  // 当 2 循环
  {
    for ( i = 0; i < 24; ++i )  // 循环：i = 0; i < 24; ++i
    {
      if ( pt.x >= 32 * (i % 8) + v6 + 19
        && pt.x < 32 * (i % 8) + v6 + 47
        && pt.y >= 32 * (i / 8) - v2 + v5 + 231
        && pt.y < 32 * (i / 8) - v2 + v5 + 259 )  // 交易窗公共更新（40 行）
      {
        return i + 24 * v7;
      }
    }
    v2 += 174;
    ++v7;  // 自增v7
    if ( v2 < 348 )  // 若 v2 < 348
      continue;
    break;
  }
  return -1;  // 返回 -1（0xFFFFFFFF）
}



// ------------------------------------------------------------
// 0x54A080 CNRDItemTradeWindow__vmt10 —— CNRDItemTradeWindow__vmt10 状态切换（44E850 + 484600 + 540960）
// ------------------------------------------------------------
// 大白话：交易窗状态切换：44E850 + 484600 + 540960。
char /*thiscall*/ CNRDItemTradeWindow__vmt10(uint32_t **this)  // 函数: CNRDItemTradeWindow__vmt10 状态切换（44E850 + 484600 + 540960）
{
  if ( dword_9B88D0 != 0 && dword_795378 == 3 )  // 若 dword_9B88D0 != 0 && dword_795378 == 3
    sub_44E850(*(this + 2), 26);  // 按池号批量回收活动对象
  if ( *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
    sub_484600();  // 技能槽状态置 2 请求（包 op 26 写单字节 2）
  sub_540960((uint32_t *)(*(this + 2))[29]);  // 数量输入框刷新
  sub_44E850(dword_8F8528, 66);  // 按池号批量回收活动对象
  return sub_44E850(dword_8F8528, 27);  // 按池号批量回收活动对象
}



// ------------------------------------------------------------
// 0x54A0E0 sub_54A0E0 —— 交易窗数据（44 行）
// ------------------------------------------------------------
// 大白话：交易窗数据：44 行取双方交易格数据。
int /*thiscall*/ sub_54A0E0(uint32_t *this, int pArg2, int nArg3)  // 函数: 交易窗数据（44 行）
{
  int pArg22; // edi
  int v5; // ecx
  unsigned int nLen; // esi
  signed int nLen2; // esi
  signed int nLen3; // eax
  int v9; // edx
  int i; // [esp+Ch] [ebp-28h]
  char Buffer[32]; // [esp+10h] [ebp-24h] BYREF
  int dword_796E502; // [esp+30h] [ebp-4h]

  pArg22 = pArg2;
  v5 = *(this + pArg2 + 53);
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  if ( nArg3 != v5 )  // 若 nArg3 != v5
  {
    sprintf(Buffer, "%d", nArg3);  // 字符串 “%d”
    nLen = (strlen(Buffer) - 1) / 3;  // 调 strlen（求串长）
    *((uint8_t *)this + 32 * pArg2 + nLen + strlen(Buffer) + 148) = 0;  // 调 strlen（求串长）
    nLen2 = strlen(Buffer) + nLen - 1;  // 调 strlen（求串长）
    nLen3 = strlen(Buffer) - 1;  // 调 strlen（求串长）
    for ( i = 0; nLen2 >= 0; ++i )  // 循环：i = 0; nLen2 >= 0; ++i
    {
      if ( nLen3 < 0 )  // 若 nLen3 < 0
        break;
      v9 = 32 * pArg2 + nLen2;
      if ( i % 4 == 3 )  // 若 i % 4 == 3
        *((uint8_t *)this + v9 + 148) = 44;
      else
        *((uint8_t *)this + v9 + 148) = Buffer[nLen3--];
      --nLen2;  // 自减nLen2
    }
    *(this + pArg2 + 53) = nArg3;
    pArg22 = pArg2;
  }
  return (int)(this + 8 * pArg22 + 37);
}



// ------------------------------------------------------------
// 0x54A200 sub_54A200 —— 交易窗数量联动（14 行，被 5409C0 调用）
// ------------------------------------------------------------
// 大白话：交易窗数量联动：14 行，被数量窗 5409C0 回调（把确认数量写入交易格）。
int /*thiscall*/ sub_54A200(uint32_t *this, char pszArg2)  // 函数: 交易窗数量联动（14 行，被 5409C0 调用）
{
  int result; // eax

  result = *(this + 5);  // result = this+5
  *(uint8_t *)(result + 17) = pszArg2;  // result+17 = pszArg2
  return result;  // result=this+20 频道页号
}



// ------------------------------------------------------------
// 0x54A210 CNRDItemTradeWindow__vmt8 —— CNRDItemTradeWindow__vmt8 Update（103 行：CLICK_BUTTON2/WINDOW_CLOSE + 4844E0/50EB10/549FD0 交易状态）
// ------------------------------------------------------------
// 大白话：交易窗逐帧 Update：按钮 CLICK_BUTTON2/WINDOW_CLOSE 音；4844E0(1) 请求就绪、
// 50EB10 同步交易状态、549FD0 公共更新；悬停格 44E8D0 消息 0x1A(模式 3) 弹提示、
// 无则解除 26 号对象；含 540DE0(…,4,…) 数量弹窗分支。
char /*thiscall*/ CNRDItemTradeWindow__vmt8(uint32_t *this)  // 函数: CNRDItemTradeWindow__vmt8 Update（103 行：CLICK_BUTTON2/WINDOW_CLOSE + 4844E0/50EB10/549FD0 交易状态）
{
  int dword_8F85382; // ecx
  int pObj; // eax
  int fld_e4; // eax
  bool v5; // al
  int pLockCtrl; // eax  | +0x0014 → 就绪/锁定控件（0x54A7A0: *(uint8_t*)(*(this+20)+17)=1 置激活显示）（CNRDItemTradeWindow；va=0054A7A0）
  bool v7; // al
  int fld_e6; // eax
  uint32_t *pThis_37; // edi
  int i; // ebx
  char *pHostCtrl; // edi
  int v12; // eax
  int pOwnerWnd; // ecx  | +0x0004 → 宿主窗口指针（CNRDItemTradeWindow；va=0054A820）
  int v14; // ebx
  int v15; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // eax
  int v19; // ebx
  int pOwnerWnd_; // edi  | +0x0004 → 宿主窗口指针（CNRDItemTradeWindow；va=0054A820）
  int v21; // esi
  int v23; // [esp+4h] [ebp-8h]
  char *fld_e22; // [esp+8h] [ebp-4h]

  dword_8F85382 = dword_8F8538;  // 全局 dword_8F8538 = 随身影身/占位管理器
  if ( *(uint16_t *)(dword_8F8538 + 4) == 0xFFFF )  // 全局 dword_8F8538 = 随身影身/占位管理器
  {
    LOBYTE(pObj) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 44))(this);  // 虚调用 vt+44
    return pObj;
  }
  fld_e4 = *(this + 4);  // fld_e4 = this+4
  if ( *(uint8_t *)(fld_e4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e4 + 12) )  // 若 *(uint8_t *)(fld_e4 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 44))(this);  // 虚调用 vt+44
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    sub_432EA0("WINDOW_CLOSE", -1, 0, 0);  // 字符串 “WINDOW_CLOSE”
    dword_8F85382 = dword_8F8538;  // 全局 dword_8F8538 = 随身影身/占位管理器
  }
  v5 = *(uint32_t *)(dword_8F85382 + 8) != 1 && (*(uint8_t *)(dword_8F85382 + 64) == 0 || sub_699000(dword_8F85382 + 52) > 2000);  // 【clock_now(clk)】
  *(uint8_t *)(*(this + 5) + 16) = v5;
  pLockCtrl = *(this + 5);  // 读 fld_e5 = this+20（就绪/锁定控件）
  if ( *(uint8_t *)(pLockCtrl + 17) != 0 && dword_79BE34 == *(uint32_t *)(pLockCtrl + 12) )  // 若 *(uint8_t *)(fld_e5 + 17) != 0 && dword_79BE34 == *(uint32_t *..
    sub_540DE0(*(int **)(*(this + 2) + 116), 1, 0, 0, 4, 0, 0, 0);  // 摊位列表构建
  v7 = *(uint32_t *)(dword_8F8538 + 8) != 1  // 全局 dword_8F8538 = 随身影身/占位管理器
    && (*(uint8_t *)(dword_8F8538 + 36) == 0 || sub_699000(dword_8F8538 + 24) > 1000);  // 【clock_now(clk)】
  *(uint8_t *)(*(this + 6) + 17) = v7;
  fld_e6 = *(this + 6);  // fld_e6 = this+6
  if ( *(uint8_t *)(fld_e6 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e6 + 12) )  // 若 *(uint8_t *)(fld_e6 + 17) != 0 && dword_79BE34 == *(uint32_t *..
    sub_4844E0(1);  // 技能自动施放开关切换（包 op 26，剩余冷却走提示串 419）
  pThis_37 = this + 55;
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
    sub_50EB10(*pThis_37++);  // 气泡计时到期判定
  pHostCtrl = (char *)*(this + 2);
  v12 = *((uint32_t *)pHostCtrl + 626);
  fld_e22 = pHostCtrl;
  if ( v12 == 1 )  // 若 v12 == 1
    goto LABEL_36;  // 跳转 LABEL_36
  if ( v12 == 2 )  // 若 v12 == 2
    goto LABEL_36;  // 跳转 LABEL_36
  pOwnerWnd = *(this + 1);  // 读 fld_e1 = this+4（宿主窗口指针）
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0 )  // 若 *(uint8_t *)(fld_e1 + 17) == 0
    goto LABEL_36;  // 跳转 LABEL_36
  v14 = *(uint32_t *)(pOwnerWnd + 12);  // v14 = fld_e1+12
  if ( dword_79BE3C != v14 && dword_79BE34 != v14 && dword_79BE38 != v14 )  // 若 dword_79BE3C != v14 && dword_79BE34 != v14 && dword_79BE38 != ..
    goto LABEL_36;  // 跳转 LABEL_36
  v15 = sub_549FD0(this);  // 结果 = 交易窗公共更新
  if ( v15 == -1 )  // 若 v15 == -1
    goto LABEL_36;  // 跳转 LABEL_36
  v16 = v15 % 24;
  v17 = v15 / 24;
  v18 = *(uint32_t *)(dword_8F8538 + 4 * (v15 / 24) + 16);  // 全局 dword_8F8538 = 随身影身/占位管理器
  if ( v16 + 3 >= *(uint32_t *)(v18 + 8) )  // 若 v16 + 3 >= *(uint32_t *)(v18 + 8)
    v19 = 0;
  else
    v19 = *(uint32_t *)(*(uint32_t *)(v18 + 12) + 4 * (v16 + 3));
  pOwnerWnd_ = *(this + 1);  // 读 fld_e12 = this+4（宿主窗口指针）
  v23 = 32 * (v16 % 8) + *(uint32_t *)(pOwnerWnd_ + 20) + 19;  // fld_e12=this+4 宿主对象
  pObj = *(uint32_t *)(pOwnerWnd_ + 24);  // pObj = fld_e12+24
  v21 = pObj + 32 * (v16 / 8) - 174 * v17 + 231;
  if ( v19 == 0 )  // 若 v19 == 0
  {
    pHostCtrl = fld_e22;
LABEL_36:
    LOBYTE(pObj) = dword_9B88D0;
    if ( dword_9B88D0 != 0 && dword_795378 == 3 )  // 若 dword_9B88D0 != 0 && dword_795378 == 3
      LOBYTE(pObj) = sub_44E850(pHostCtrl, 26);  // 按池号批量回收活动对象
    return pObj;
  }
  if ( dword_9B88D0 != v19 || dword_795378 != 3 )  // 若 dword_9B88D0 != v19 || dword_795378 != 3
  {
    pObj = sub_44E8D0(fld_e22, (void *)0x1A, v19, 3);  // 结果 = 对象池借出（按池号取可用对象）
    if ( pObj != 0 )  // 若 pObj != 0
      LOBYTE(pObj) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pObj + 48))(pObj, v23, v21, 28, 28);  // 虚槽+48 CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0）
  }
  return pObj;
}



// ------------------------------------------------------------
// 0x54A480 CNRDItemTradeWindow__vmt0 —— CNRDItemTradeWindow__vmt0 构造（154 行：42B340/4924C0/4938F0/491D00 + 54A0E0/50EB40）
// ------------------------------------------------------------
// 大白话：交易窗构造：42B340/4924C0/4938F0/491D00 部件 + 54A0E0/50EB40 数据（154 行）。
int /*userpurge*/ sub_54A480@<eax>(int pArg1@<ecx>, int nArg2@<esi>, int pArg3)  // 函数: CNRDItemTradeWindow__vmt0 构造（154 行：42B340/4924C0/4938F0/491D00 + 54A0E0/50EB40）
{
  int pArg12; // ebx
  int result; // eax
  int pArg32; // edi
  int v6; // eax
  int v7; // esi
  int pObj4; // eax
  int v9; // esi
  int pObj5; // eax
  int pObj7; // edi
  unsigned int v12; // edi
  int v13; // eax
  unsigned int v14; // ecx
  int v15; // eax
  int v16; // ecx
  int pObj; // ecx
  int v18; // edi
  int v19; // eax
  int v20; // eax
  unsigned int v21; // edi
  int v22; // ecx
  int pObj6; // ecx
  int v24; // ecx
  int v25; // edi
  int pObj2; // eax
  int pObj3; // eax
  int v30; // [esp+10h] [ebp-10h]
  int v31; // [esp+10h] [ebp-10h]
  int v32; // [esp+10h] [ebp-10h]
  int v33; // [esp+10h] [ebp-10h]
  int v34; // [esp+10h] [ebp-10h]
  int v35; // [esp+14h] [ebp-Ch]
  int v36; // [esp+18h] [ebp-8h]

  pArg12 = pArg1;
  result = *(uint32_t *)(pArg1 + 4);  // result = pArg1+4
  pArg32 = pArg3;
  if ( pArg3 == result )  // 若 pArg3 == result
  {
    v6 = *(uint32_t *)(pArg1 + 20);  // v6 = pArg1+20
    if ( *(uint8_t *)(v6 + 16) == 0 )  // 若 *(uint8_t *)(v6 + 16) == 0
    {
      v7 = *(uint32_t *)(v6 + 24);  // v7 = v6+24
      v30 = *(uint32_t *)(v6 + 20);  // v30 = v6+20
      pObj4 = sub_418DD0(1);  // 调 sub_418DD0
      if ( pObj4 != 0 )  // 若 pObj4 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v30, v7, dword_79C0B0);  // 调用虚函数槽 +152
    }
    v9 = 1;
    while ( 1 )  // 当 1 循环
    {
      v35 = *(uint32_t *)(pArg32 + 20) + 15;
      if ( v9 != 0 )  // 若 v9 != 0
        v36 = *(uint32_t *)(pArg32 + 24) + 24;
      else
        v36 = *(uint32_t *)(pArg32 + 24) + 198;
      pObj5 = sub_42B340(*(uint32_t *)(pArg12 + 4 * v9 + 140));  // 结果 = 虚拟角色惰性创建（0x294 字节）
      pObj7 = pObj5;
      if ( pObj5 != 0 )  // 若 pObj5 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)pObj5 + 384))(  // 虚槽+384 槽数组 getter（+348 起，越界返回 0）
          pObj5,
          v35 + 3,
          v36 + 4,
          24,
          24,
          1065353216);
      v31 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj7 + 360))(pObj7, nArg2);  // 调用虚函数槽 +360
      if ( v31 != 0 )  // 若 v31 != 0
      {
        v12 = *(uint32_t *)(*(uint32_t *)sub_4924C0(0) + 36);  // 结果 = 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
        sub_4938F0(v31);  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
        sub_491D00(dword_79C0B0, v35 - (v12 >> 1) + 69, v36 + 1, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg12 + 28);  // 调用虚函数槽 +72
      v13 = *(uint32_t *)(pArg12 + 4 * v9 + 140);
      v14 = *(uint32_t *)(v13 + 40);  // v14 = v13+40
      v15 = v13 + 16;
      v16 = v14 < 0x10 ? v15 + 4 : *(uint32_t *)(v15 + 4);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        v35 + 24,
        v36 + 17,
        -1,
        v16);
      pObj = **(uint32_t **)(*(uint32_t *)(dword_8F8538 + 4 * v9 + 16) + 12);  // 结果 = 虚调用 vt+16
      v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj);  // 调用虚函数槽 +44
      nArg2 = pArg12 + 80;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0);  // 调用虚函数槽 +68
      v32 = *(uint32_t *)dword_79C0B0;  // v32 = dword_79C0B0
      v19 = sub_54A0E0(v9, v18);  // 结果 = 交易窗数据
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(v32 + 80))(dword_79C0B0, v35 + 126, v36 + 11, -4265479, v19);  // 调用虚函数槽 +80
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
      v20 = 12;
      v21 = 0;
      v33 = 12;
      do
      {
        v22 = *(uint32_t *)(dword_8F8538 + 4 * v9 + 16);  // 全局 dword_8F8538 = 随身影身/占位管理器
        if ( (signed int)(v21 + 3) < *(uint32_t *)(v22 + 8) )  // 若 (signed int)(v21 + 3) < *(uint32_t *)(v22 + 8)
        {
          pObj6 = *(uint32_t *)(v20 + *(uint32_t *)(v22 + 12));
          if ( pObj6 != 0 )  // 若 pObj6 != 0
          {
            (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, uint32_t, uint32_t))(*(uint32_t *)pObj6 + 8))(  // 虚槽+8 CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTTON2/DISSOLVE
              pObj6,
              32 * (v21 & 7) + *(uint32_t *)(*(uint32_t *)(pArg12 + 4) + 20) + 19,
              *(uint32_t *)(*(uint32_t *)(pArg12 + 4) + 24) + 32 * (v21 >> 3) - 174 * v9 + 231,  // 虚调用 vt+231
              0,
              0);
            v20 = v33;
            pArg12 = pArg1;
          }
        }
        v20 += 4;
        ++v21;  // 自增v21
        v33 = v20;
      }
      while ( v20 < 108 );  // 当 v20 < 108 循环
      if ( *(uint32_t *)(dword_8F8538 + 4 * v9 + 8) == 1 )  // 全局 dword_8F8538 = 随身影身/占位管理器
      {
        v24 = *(uint32_t *)(pArg3 + 20);  // v24 = pArg3+20
        if ( v9 != 0 )  // 若 v9 != 0
        {
          v34 = v24 + 152;
          v25 = *(uint32_t *)(pArg3 + 24) + 155;
        }
        else
        {
          v34 = v24 + 96;
          v25 = *(uint32_t *)(pArg3 + 24) + 165;
        }
        pObj2 = sub_418DD0((v9 != 0) + 4);  // 调 sub_418DD0
        if ( pObj2 != 0 )  // 若 pObj2 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v34, v25, dword_79C0B0);  // 调用虚函数槽 +152
        sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
        pObj3 = sub_418DD0(1 - v9);  // 调 sub_418DD0
        if ( pObj3 != 0 )  // 若 pObj3 != 0
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pObj3 + 152))(pObj3, 0, 0, dword_79C0B0);  // 调用虚函数槽 +152
        sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
      }
      result = sub_50EB40(v35 + 14, v36 + 4, 255);  // 结果 = 表情气泡绘制
      if ( --v9 < 0 )  // 若 --v9 < 0
        break;
      pArg32 = pArg3;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x54A7A0 CNRDItemTradeWindow__vmtC —— CNRDItemTradeWindow__vmtC 打开槽（44BBA0 + 429830）
// ------------------------------------------------------------
// 大白话：交易窗打开槽：44BBA0 显示 + 429830 动画。
char /*thiscall*/ CNRDItemTradeWindow__vmtC(int this)  // 函数: CNRDItemTradeWindow__vmtC 打开槽（44BBA0 + 429830）
{
  int v2; // eax
  int pTradeSelf; // ecx  | +0x008C → 交易己方对象（CNRDItemTradeWindow；va=0054A7A0）

  sub_44BBA0(*(uint32_t **)(this + 8), 0, 0);  // 窗口显示切换（WINDOW_SHOW 音效）
  *(uint32_t *)(this + 140) = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // 表按键查找（uint16）
  v2 = sub_429830((uint32_t *)dword_8F8500, *(uint16_t *)(dword_8F8538 + 4));  // 结果 = 表按键查找（uint16）
  pTradeSelf = *(uint32_t *)(this + 140);  // 读 fld_8C = this+140（交易己方对象）
  *(uint32_t *)(this + 144) = v2;  // 写 this+144 = v2（交易对方对象）
  if ( pTradeSelf == 0 || v2 == 0 )  // 若 fld_8C == 0 || v2 == 0
    return 0;
  *(uint8_t *)(*(uint32_t *)(this + 220) + 40) = 0;  // this+220 pSelfReadyTag
  *(uint8_t *)(*(uint32_t *)(this + 224) + 40) = 0;  // this+224 pPeerReadyTag
  *(uint8_t *)(*(uint32_t *)(this + 20) + 17) = 1;  // this+20 pLockCtrl
  return 1;
}



// ------------------------------------------------------------
// 0x54A820 CNRDItemTradeWindow__vmt14 —— CNRDItemTradeWindow__vmt14 关闭槽（549FD0 + 44BC30）
// ------------------------------------------------------------
// 大白话：交易窗关闭槽：549FD0 + 44BC30 清理。
char /*thiscall*/ CNRDItemTradeWindow__vmt14(int this)  // 函数: CNRDItemTradeWindow__vmt14 关闭槽（549FD0 + 44BC30）
{
  int dword_8F85382; // esi
  int pOwnerWnd; // eax  | +0x0004 → 宿主窗口指针（CNRDItemTradeWindow；va=0054A820）
  int v5; // eax
  int v6; // ecx
  int v7; // edi
  int v8; // edx
  int pObj; // esi
  int v10; // eax
  int v11; // [esp-Ch] [ebp-14h]
  void *v12; // [esp-8h] [ebp-10h]

  dword_8F85382 = dword_8F8538;  // 全局 dword_8F8538 = 随身影身/占位管理器
  if ( *(uint32_t *)(dword_8F8538 + 8) == 1 )  // 全局 dword_8F8538 = 随身影身/占位管理器
    return 0;
  pOwnerWnd = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主窗口指针）
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0 )  // 若 *(uint8_t *)(fld_4 + 17) == 0
    return 0;
  if ( dword_79BE3C != *(uint32_t *)(pOwnerWnd + 12) )  // 若 dword_79BE3C != *(uint32_t *)(fld_4 + 12)
    return 0;
  v5 = sub_549FD0((uint32_t *)this);  // 结果 = 交易窗公共更新
  if ( v5 == -1 )  // 若 v5 == -1
    return 0;
  if ( v5 >= 24 )  // 若 v5 >= 24
    return 0;
  v6 = *(uint32_t *)(dword_8F85382 + 16);  // v6 = dword_8F85382+16
  v7 = v5 + 3;
  if ( v5 + 3 >= *(uint32_t *)(v6 + 8) )  // 若 v5 + 3 >= *(uint32_t *)(v6 + 8)
    return 0;
  v8 = *(uint32_t *)(v6 + 12);  // v8 = v6+12
  pObj = *(uint32_t *)(v8 + 4 * v7);
  if ( pObj == 0 )  // 若 pObj == 0
    return 0;
  v12 = *(void **)(v8 + 4 * v7);
  v11 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 68);  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);  // 调用虚函数槽 +16
  sub_44BC30(*(uint32_t **)(this + 8), (void *)2, 5, *(uint32_t *)(v10 + 4), v7, v11, v12);  // 拾取模式状态 + ICON_PICK/ITEM_PICK 音效
  return 1;
}



// ------------------------------------------------------------
// 0x54A8B0 sub_54A8B0 —— 交易辅助（4999D0）
// ------------------------------------------------------------
// 大白话：交易辅助：4999D0 数据访问。
void /*thiscall*/ sub_54A8B0(uint32_t *this)  // 函数: 交易辅助（4999D0）
{
  void (/*thiscall*/ ***fld_e1)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e5)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e6)(uint32_t, int); // ecx
  uint32_t *pThis_37; // esi
  int i; // ebx
  void *v8; // edi

  fld_e1 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( fld_e1 != nullptr )  // 若 fld_e1 非空
    (**fld_e1)(fld_e1, 1);
  fld_e4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 4);  // this+4 宿主对象
  *(this + 1) = 0;  // this+4 = 0
  if ( fld_e4 != nullptr )  // 若 fld_e4 非空
    (**fld_e4)(fld_e4, 1);
  fld_e5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 4) = 0;  // this+16 = 0
  if ( fld_e5 != nullptr )  // 若 fld_e5 非空
    (**fld_e5)(fld_e5, 1);
  fld_e6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  *(this + 5) = 0;  // this+20 = 0
  if ( fld_e6 != nullptr )  // 若 fld_e6 非空
    (**fld_e6)(fld_e6, 1);
  *(this + 6) = 0;  // this+24 = 0
  pThis_37 = this + 55;
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
  {
    v8 = (void *)*pThis_37;
    if ( *pThis_37 != 0 )  // 若 *pThis_37 != 0
    {
      sub_4999D0(*pThis_37);  // 子对象析构序（基类释放 + 虚表回落）
      j__free(v8);  // 调 j__free
    }
    *pThis_37++ = 0;  // *pThis_37++ 写入 0
  }
}



// ------------------------------------------------------------
// 0x54A930 sub_54A930 —— 交易就绪绘制：资源 Interface/ItemTradeWindowReady.img（43C250/43C410/69A5F0/69A840 + 499960）
// ------------------------------------------------------------
// 大白话：交易就绪页绘制：加载 Interface/ItemTradeWindowReady.img，43C250/43C410/69A5F0/69A840
// 布件 + 499960，双方确认后切换到该页。
int /*thiscall*/ sub_54A930(int this)  // 函数: 交易就绪绘制：资源 Interface/ItemTradeWindowReady.img（43C250/43C410/69A5F0/69A840 + 499960）
{
  uint8_t *pMem; // eax
  uint8_t *fld_84; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax
  uint32_t *pMem3; // eax
  uint32_t *fld_842; // eax
  uint32_t *pMem4; // eax
  uint32_t *fld_843; // eax
  int v10; // edi
  int *pThis_DC; // esi
  int result; // eax

  *(uint32_t *)(this + 132) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 24);  // this+132 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  *(uint32_t *)(this + 136) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // this+136 演出已播标志
                              dword_8F84B8,
                              "Interface/ItemTradeWindowReady.img");  // 字符串 “Interface/ItemTradeWindowReady.img”
  pMem = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_84 = sub_43C250(pMem, *(uint32_t *)(this + 132), 0);  // 结果 = nengine::CNFrame 构造
  else
    fld_84 = nullptr;  // fld_84 = nullptr 空指针
  *(uint32_t *)(this + 4) = fld_84;  // this+4 = fld_84
  *((uint32_t *)fld_84 + 7) = *((uint32_t *)fld_84 + 7);
  *((uint32_t *)fld_84 + 8) = 353;
  *(uint32_t *)(*(uint32_t *)(this + 4) + 68) = this;  // this+4 宿主对象
  pMem2 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 11, 12, 13, 11, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(uint32_t *)(this + 16) = v5;  // this+16 = v5
  sub_69A5F0(v5, 221, 353);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 16));  // 调 sub_69A840
  pMem3 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    fld_842 = sub_43C410(pMem3, *(uint32_t *)(this + 132), 1, 2, 3, 1, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_842 = nullptr;  // fld_842 = nullptr 空指针
  *(uint32_t *)(this + 20) = fld_842;  // this+20 = fld_842
  sub_69A5F0(fld_842, 132, 203);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 20));  // 调 sub_69A840
  pMem4 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    fld_843 = sub_43C410(pMem4, *(uint32_t *)(this + 132), 6, 7, 8, 9, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_843 = nullptr;  // fld_843 = nullptr 空指针
  *(uint32_t *)(this + 24) = fld_843;  // this+24 = fld_843
  sub_69A5F0(fld_843, 117, 332);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 24));  // 调 sub_69A840
  sub_69A5F0(*(uint32_t **)(this + 4), 29, 63);  // 调 sub_69A5F0
  *(uint32_t *)(this + 44) = 6;  // this+44 = 6
  *(uint8_t *)(this + 28) = 0;  // this+28 = 0
  *(uint8_t *)(this + 29) = 0;  // this+29 = 0
  *(uint8_t *)(this + 30) = 0;  // this+30 = 0
  *(uint8_t *)(this + 31) = 0;  // this+31 = 0
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint32_t *)(this + 52) = 0;  // this+52 = 0
  *(uint32_t *)(this + 60) = 0;  // this+60 = 0
  *(uint32_t *)(this + 64) = 0;  // this+64 = 0
  *(uint32_t *)(this + 68) = 0;  // this+68 = 0
  *(uint32_t *)(this + 72) = 0;  // this+72 = 0
  *(uint32_t *)(this + 76) = 0;  // this+76 = 0
  *(uint32_t *)(this + 56) = 1600;  // this+56 = 1600
  *(uint32_t *)(this + 48) = 12;  // this+48 = 12
  *(uint32_t *)(this + 76) = dword_99FCCC;  // this+76 = dword_99FCCC
  *(uint32_t *)(this + 40) = 1;  // this+40 = 1
  *(uint32_t *)(this + 56) = 90;  // this+56 = 90
  *(uint32_t *)(this + 96) = 6;  // this+96 = 6
  *(uint8_t *)(this + 80) = 0;  // this+80 = 0
  *(uint8_t *)(this + 81) = 0;  // this+81 = 0
  *(uint8_t *)(this + 82) = 0;  // this+82 = 0
  *(uint8_t *)(this + 83) = 0;  // this+83 = 0
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 100) = 12;  // this+100 = 12
  *(uint32_t *)(this + 104) = 0;  // this+104 = 0
  *(uint32_t *)(this + 108) = 1600;  // this+108 = 1600
  *(uint32_t *)(this + 112) = 0;  // this+112 = 0
  *(uint32_t *)(this + 116) = 0;  // this+116 = 0
  *(uint32_t *)(this + 120) = 0;  // this+120 = 0
  *(uint32_t *)(this + 124) = 0;  // this+124 = 0
  *(uint32_t *)(this + 128) = 0;  // this+128 = 0
  v10 = 2;
  *(uint32_t *)(this + 128) = dword_99FCCC;  // this+128 = dword_99FCCC
  *(uint32_t *)(this + 92) = 2;  // this+92 = 2
  *(uint32_t *)(this + 108) = 120;  // this+108 = 120
  pThis_DC = (int *)(this + 220);  // this+220 己方就绪标签控件
  do
  {
    if ( operator new(0x44u) != nullptr )  // 堆分配 68 字节对象
      result = sub_499960(nullptr, 120, 0);  // 结果 = 子对象构造（off_6C2B88 装配 + 基类初始化）
    else
      result = 0;
    *pThis_DC++ = result;  // *pThis_DC++ 写入 result
    --v10;  // 自减v10
  }
  while ( v10 != 0 );  // 当 v10 != 0 循环
  return result;
}



// ------------------------------------------------------------
// 0x54ABC0 sub_54ABC0 —— 19 行小辅助
// ------------------------------------------------------------
// 大白话：19 行小辅助（交易窗）。
int /*thiscall*/ sub_54ABC0(uint32_t *this)  // 函数: 19 行小辅助
{
  *(this + 4) = 0;  // this+16 = 0
  *(this + 5) = 0;  // this+20 = 0
  *(this + 6) = 0;  // this+24 = 0
  *(this + 7) = 0;  // this+28 = 0
  *(this + 8) = 0;  // this+32 = 0
  *(this + 9) = 0;  // this+36 = 0
  *(this + 10) = 0;  // this+40 = 0
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x54ABE0 sub_54ABE0 —— 交易条目（47 行）
// ------------------------------------------------------------
// 大白话：交易条目：47 行取交易格条目。
int /*thiscall*/ sub_54ABE0(uint32_t *this)  // 函数: 交易条目（47 行）
{
  void (/*thiscall*/ ***fld_e1)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e5)(uint32_t, int); // ecx
  uint32_t *pThis_6; // edi
  int i; // ebx
  void (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx
  int result; // eax

  fld_e1 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( fld_e1 != nullptr )  // 若 fld_e1 非空
    (**fld_e1)(fld_e1, 1);
  fld_e4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 4);  // this+4 宿主对象
  *(this + 1) = 0;  // this+4 = 0
  if ( fld_e4 != nullptr )  // 若 fld_e4 非空
    (**fld_e4)(fld_e4, 1);
  fld_e5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 4) = 0;  // this+16 = 0
  if ( fld_e5 != nullptr )  // 若 fld_e5 非空
    (**fld_e5)(fld_e5, 1);
  *(this + 5) = 0;  // this+20 = 0
  pThis_6 = this + 6;
  for ( i = 5; i != 0; --i )  // 循环：i = 5; i != 0; --i
  {
    if ( *pThis_6 != 0 )  // 若 *pThis_6 != 0
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_6)(*pThis_6, 1);
    *pThis_6++ = 0;  // *pThis_6++ 写入 0
  }
  fld_e11 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    (**fld_e11)(fld_e11, 1);
  fld_e12 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);  // this+12 物品类型号
  result = 0;
  *(this + 11) = 0;  // this+44 = 0
  if ( fld_e12 != nullptr )  // 若 fld_e12 非空
    result = (**fld_e12)(fld_e12, 1);
  *(this + 12) = 0;  // this+48 = 0
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
// 大白话：技能栏状态切换：44ABE0 + 550C40 + 44AB50 + 44E850。
char /*thiscall*/ CNRDSkillInventoryWindow__vmt10(uint32_t *this)  // 函数: CNRDSkillInventoryWindow__vmt10 状态切换（44ABE0 + 550C40 + 44AB50 + 44E850）
{
  uint32_t *fld_e2; // ecx
  int v3; // eax
  int fld_e22; // eax
  char result; // al

  fld_e2 = (uint32_t *)*(this + 2);
  v3 = fld_e2[626];
  if ( v3 == 10 || v3 == 11 )  // 若 v3 == 10 || v3 == 11
    sub_44ABE0(fld_e2, 0);  // 选中索引 setter
  fld_e22 = *(this + 2);  // fld_e22 = this+2
  if ( *(uint32_t *)(fld_e22 + 104) == 3 )  // 若 *(uint32_t *)(fld_e22 + 104) == 3
  {
    sub_550C40(*(uint32_t *)(fld_e22 + 68));  // 技能购买数据收尾
    sub_44AB50((uint32_t *)*(this + 2), 0, 12);  // 页签切换
  }
  result = dword_9B88CC;
  if ( dword_9B88CC != 0 && dword_795374 == 1 )  // 若 dword_9B88CC != 0 && dword_795374 == 1
    return sub_44E850((uint32_t *)*(this + 2), 18);  // 按池号批量回收活动对象
  return result;
}



// ------------------------------------------------------------
// 0x54ACD0 sub_54ACD0 —— 技能栏数据（40 行）
// ------------------------------------------------------------
// 大白话：技能栏数据：40 行取技能槽数据。
int /*thiscall*/ sub_54ACD0(uint32_t *this, char pszArg2)  // 函数: 技能栏数据（40 行）
{
  int v2; // edi
  int fld_e1; // esi
  LONG v4; // edx
  LONG v5; // ebx
  int v6; // eax
  int i; // [esp+Ch] [ebp-4h]

  v2 = 0;
  for ( i = 42 * *(uint32_t *)(*(this + 5) + 104) + 6; ; ++i )  // 循环：i = 42 * *(uint32_t *)(*(this + 5) + 104) + 6; ; ++i
  {
    fld_e1 = *(this + 1);  // fld_e1 = this+1
    if ( pszArg2 != 0 )  // 若 pszArg2 != 0
    {
      v4 = *(uint32_t *)(fld_e1 + 20) + 37 * (v2 % 6) + 39;  // fld_e1=this+4 宿主对象
      v5 = 37 * (v2 / 6) + *(uint32_t *)(fld_e1 + 24) + 57;  // fld_e1=this+4 宿主对象
    }
    else
    {
      v4 = *(uint32_t *)(fld_e1 + 20) + 37 * (v2 % 6) + 35;  // fld_e1=this+4 宿主对象
      v5 = 37 * (v2 / 6) + *(uint32_t *)(fld_e1 + 24) + 53;  // fld_e1=this+4 宿主对象
    }
    if ( pt.x >= v4 )  // 若 pt.x >= v4
    {
      v6 = pszArg2 != 0 ? 28 : 37;
      if ( pt.x < v6 + v4 && pt.y >= v5 && pt.y < v5 + v6 )  // 若 pt.x < v6 + v4 && pt.y >= v5 && pt.y < v5 + v6
        break;
    }
    if ( ++v2 >= 42 )  // 若 ++v2 >= 42
      return -1;  // 返回 -1（0xFFFFFFFF）
  }
  return i;
}



// ------------------------------------------------------------
// 0x54AD80 CNRDSkillInventoryWindow__vmt14 —— CNRDSkillInventoryWindow__vmt14 关闭槽（54ACD0 + 41A5E0 + 44BC30）
// ------------------------------------------------------------
// 大白话：技能栏关闭槽：54ACD0 + 41A5E0 + 44BC30。
char /*thiscall*/ CNRDSkillInventoryWindow__vmt14(uint32_t *this)  // 函数: CNRDSkillInventoryWindow__vmt14 关闭槽（54ACD0 + 41A5E0 + 44BC30）
{
  int fld_e1; // eax
  int v4; // edi
  int *v5; // esi
  int fld_e2; // eax
  int v7; // eax

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( *(uint8_t *)(fld_e1 + 17) == 0 || dword_79BE3C != *(uint32_t *)(fld_e1 + 12) )  // 若 *(uint8_t *)(fld_e1 + 17) == 0 || dword_79BE3C != *(uint32_t *..
    return 0;
  v4 = sub_54ACD0(this, 1);  // 结果 = 技能栏数据
  if ( v4 == -1 )  // 若 v4 == -1
    return 0;
  if ( v4 >= *(uint32_t *)dword_8F853C )  // 若 v4 >= *(uint32_t *)dword_8F853C
    return 0;
  v5 = *(int **)(*((uint32_t *)dword_8F853C + 1) + 4 * v4);
  if ( v5 == nullptr )  // 若 v5 为空
    return 0;
  fld_e2 = *(uint32_t *)(*(this + 2) + 2504);
  if ( fld_e2 == 10 || fld_e2 == 11 )  // 若 fld_e2 == 10 || fld_e2 == 11
    return 0;
  v7 = sub_41A5E0((unsigned int)(v5 + 1));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  sub_44BC30((uint32_t *)*(this + 2), (void *)1, 0, v7, v4, v5[95], v5);  // 拾取模式状态 + ICON_PICK/ITEM_PICK 音效
  return 1;
}



// ------------------------------------------------------------
// 0x54AE10 CNRDSkillInventoryWindow__vmt1C —— CNRDSkillInventoryWindow__vmt1C 刷新槽（109 行：ICON_DROP 图标拖入事件 432EA0 + 460570/483E70/47E7A0）
// ------------------------------------------------------------
// 大白话：技能栏刷新槽：ICON_DROP 图标拖入事件(432EA0) + 460570/483E70/47E7A0 重排（109 行）。
char /*thiscall*/ CNRDSkillInventoryWindow__vmt1C(uint32_t *this)  // 函数: CNRDSkillInventoryWindow__vmt1C 刷新槽（109 行：ICON_DROP 图标拖入事件 432EA0 + 460570/483E70/47E7A0）
{
  int fld_e1; // eax
  uint32_t *fld_e2; // ebx
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
  int fld_e52; // [esp+4h] [ebp-4h]
  int fld_e5; // [esp+4h] [ebp-4h]

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( *(uint8_t *)(fld_e1 + 17) == 0 || dword_79BE34 != *(uint32_t *)(fld_e1 + 12) )  // 若 *(uint8_t *)(fld_e1 + 17) == 0 || dword_79BE34 != *(uint32_t *..
    return 0;
  fld_e2 = (uint32_t *)*(this + 2);
  v5 = fld_e2[626];
  if ( v5 != 10 && v5 != 11 )  // 若 v5 != 10 && v5 != 11
  {
    if ( v5 == 1 )  // 若 v5 == 1
    {
      v6 = fld_e2[627];
      if ( v6 != 0 )  // 若 v6 != 0
      {
        if ( v6 == 1 )  // 若 v6 == 1
        {
          v11 = sub_460570(dword_8F853C, fld_e2[629]);  // 结果 = 索引取值（越界返 0）
          v12 = v11;
          if ( v11 != 0 && sub_41A5E0(v11 + 4) == fld_e2[628] )  // crypt4byte 解密校验（·0x41A590 逆运算）
          {
            fld_e5 = *(uint32_t *)(*(this + 5) + 104);
            v13 = v12 + 128;
            if ( fld_e5 == sub_41A5E0(v13) )  // crypt4byte 解密校验（·0x41A590 逆运算）
            {
              v14 = sub_54ACD0(this, 0);  // 结果 = 技能栏数据
              if ( v14 != -1 )  // 若 v14 != -1
                goto LABEL_23;  // 跳转 LABEL_23
            }
            v14 = 42 * sub_41A5E0(v13) + 6;  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
            for ( i = 0; i < 42; ++i )  // 循环：i = 0; i < 42; ++i
            {
              if ( sub_460570(dword_8F853C, v14) == 0 )  // 索引取值（越界返 0）
                break;
              ++v14;  // 自增v14
            }
            if ( v14 != -1 )  // 若 v14 != -1
            {
LABEL_23:
              sub_483E70(fld_e2[629], v14, 1);  // 技能槽交换请求（包 op 30，先做占用校验后本地预交换）
              goto LABEL_24;  // 跳转 LABEL_24
            }
          }
        }
      }
      else
      {
        v7 = sub_460570(dword_8F853C, fld_e2[629]);  // 结果 = 索引取值（越界返 0）
        v8 = v7;
        if ( v7 != 0 && sub_41A5E0(v7 + 4) == fld_e2[628] )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          fld_e52 = *(uint32_t *)(*(this + 5) + 104);
          if ( fld_e52 == sub_41A5E0(v8 + 128) )  // crypt4byte 解密校验（·0x41A590 逆运算）
          {
            v9 = sub_54ACD0(this, 1);  // 结果 = 技能栏数据
            if ( v9 != -1 )  // 若 v9 != -1
            {
              v10 = fld_e2[629];
              if ( v10 != v9 )  // 若 v10 != v9
              {
                sub_483E70(v10, v9, 1);  // 技能槽交换请求（包 op 30，先做占用校验后本地预交换）
LABEL_24:
                sub_432EA0("ICON_DROP", -1, 0, 0);  // 字符串 “ICON_DROP”
                return 1;
              }
            }
          }
        }
      }
    }
    return 0;
  }
  v16 = sub_54ACD0(this, 1);  // 结果 = 技能栏数据
  if ( v16 == -1 )  // 若 v16 == -1
    return 0;
  if ( v16 >= *(uint32_t *)dword_8F853C )  // 若 v16 >= *(uint32_t *)dword_8F853C
    return 0;
  v17 = *(int **)(*((uint32_t *)dword_8F853C + 1) + 4 * v16);
  if ( v17 == nullptr )  // 若 v17 为空
    return 0;
  if ( v5 == 10 )  // 若 v5 == 10
    sub_47E7A0(v17, 1u, 1);  // 调 sub_47E7A0
  else
    sub_47E7A0(v17, 0, 1);  // 调 sub_47E7A0
  return 1;
}



// ------------------------------------------------------------
// 0x54AFF0 CNRDSkillInventoryWindow__vmt18 —— CNRDSkillInventoryWindow__vmt18 页签动作（41A5E0 + 44AB90=TAB_SELECT 音）
// ------------------------------------------------------------
// 大白话：技能栏页签动作：41A5E0 + 44AB90(TAB_SELECT 切页音)。
char /*thiscall*/ CNRDSkillInventoryWindow__vmt18(uint32_t *this)  // 函数: CNRDSkillInventoryWindow__vmt18 页签动作（41A5E0 + 44AB90=TAB_SELECT 音）
{
  int fld_e1; // eax
  uint32_t *fld_e2; // eax
  int v4; // eax
  int v5; // eax
  unsigned int v6; // esi
  void *v7; // eax

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( *(uint8_t *)(fld_e1 + 17) == 0 )  // 若 *(uint8_t *)(fld_e1 + 17) == 0
    return 0;
  if ( dword_79BE3C != *(uint32_t *)(fld_e1 + 12) )  // 若 dword_79BE3C != *(uint32_t *)(fld_e1 + 12)
    return 0;
  fld_e2 = (uint32_t *)*(this + 2);
  if ( fld_e2[626] != 1 || fld_e2[627] != 1 )  // 若 fld_e2[626] != 1 || fld_e2[627] != 1
    return 0;
  v4 = fld_e2[629];
  if ( v4 < *(uint32_t *)dword_8F853C )  // 若 v4 < *(uint32_t *)dword_8F853C
  {
    v5 = *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * v4);
    if ( v5 != 0 )  // 若 v5 != 0
    {
      v6 = v5 + 128;
      if ( sub_41A5E0(v5 + 128) != *(uint32_t *)(*(this + 5) + 104) )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        v7 = (void *)sub_41A5E0(v6);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        sub_44AB90((uint32_t *)*(this + 2), v7);  // 标签页选中联动（TAB_SELECT 音效）
      }
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x54B070 CNRDSkillInventoryWindow__vmt8 —— CNRDSkillInventoryWindow__vmt8 Update（73 行：CLICK_BUTTON2/WINDOW_CLOSE + 54ACD0/44AB90/44ABE0）
// ------------------------------------------------------------
// 大白话：技能栏逐帧 Update：CLICK_BUTTON2/WINDOW_CLOSE 音 + 54ACD0/44AB90/44ABE0 状态。
int /*thiscall*/ CNRDSkillInventoryWindow__vmt8(int *this)  // 函数: CNRDSkillInventoryWindow__vmt8 Update（73 行：CLICK_BUTTON2/WINDOW_CLOSE + 54ACD0/44AB90/44ABE0）
{
  int fld_e2; // ebx
  int v3; // eax
  int fld_e1; // ecx
  int v5; // edi
  int v6; // edi
  int v7; // eax
  int pObj; // ecx
  int fld_e4; // eax
  int v10; // eax
  uint32_t *pThis_6; // edx
  int fld_e11; // eax
  int result; // eax

  fld_e2 = *(this + 2);  // fld_e2 = this+2
  v3 = *(uint32_t *)(fld_e2 + 2504);  // v3 = fld_e2+2504
  if ( v3 != 1
    && v3 != 2
    && *(uint8_t *)((fld_e1 = *(this + 1)) + 17) != 0
    && ((v5 = *(uint32_t *)(fld_e1 + 12), dword_79BE3C == v5) || dword_79BE34 == v5 || dword_79BE38 == v5)  // CNRDSkillInventoryWindow__vmt8 Update（73 行：CLICK_BUTTON2/WINDOW_CLOSE + 54ACD0/44AB90/44ABE0）
    && (v6 = sub_54ACD0(this, 1)) != -1  // 技能栏数据
    && v6 < *(uint32_t *)dword_8F853C
    && (v7 = *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * v6)) != 0 )
  {
    if ( dword_9B88CC != v7 || dword_795374 != 1 )  // 若 dword_9B88CC != v7 || dword_795374 != 1
    {
      pObj = sub_44E8D0((char *)fld_e2, (void *)0x12, v7, 1);  // 结果 = 对象池借出（按池号取可用对象）
      if ( pObj != 0 )  // 若 pObj != 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pObj + 48))(  // 虚槽+48 CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0）
          pObj,
          37 * ((v6 - 42 * *(uint32_t *)(*(this + 5) + 104) - 6) % 6) + *(uint32_t *)(*(this + 1) + 20) + 39,
          37 * ((v6 - 42 * *(uint32_t *)(*(this + 5) + 104) - 6) / 6) + *(uint32_t *)(*(this + 1) + 24) + 57,
          28,
          28);
    }
  }
  else if ( dword_9B88CC != 0 && dword_795374 == 1 )  // 否则若 dword_9B88CC != 0 && dword_795374 == 1
  {
    sub_44E850((uint32_t *)fld_e2, 18);  // 按池号批量回收活动对象
  }
  fld_e4 = *(this + 4);  // fld_e4 = this+4
  if ( *(uint8_t *)(fld_e4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e4 + 12) )  // 若 *(uint8_t *)(fld_e4 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 44))(this);  // 虚调用 vt+44
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    sub_432EA0("WINDOW_CLOSE", -1, 0, 0);  // 字符串 “WINDOW_CLOSE”
  }
  v10 = 0;
  pThis_6 = this + 6;
  while ( *(uint8_t *)(*pThis_6 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*pThis_6 + 12) )  // 当 *(uint8_t *)(*pThis_6 + 17) == 0 || dword_79BE34 != *(uint32_t.. 循环
  {
    ++v10;  // 自增v10
    ++pThis_6;  // 自增pThis_6
    if ( v10 >= 5 )  // 若 v10 >= 5
      goto LABEL_26;  // 跳转 LABEL_26
  }
  sub_44AB90((uint32_t *)*(this + 2), (void *)v10);  // 标签页选中联动（TAB_SELECT 音效）
LABEL_26:
  fld_e11 = *(this + 11);  // fld_e11 = this+11
  if ( *(uint8_t *)(fld_e11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e11 + 12) )  // 若 *(uint8_t *)(fld_e11 + 17) != 0 && dword_79BE34 == *(uint32_t ..
    sub_44ABE0((uint32_t *)*(this + 2), 10);  // 选中索引 setter
  result = *(this + 12);  // result = this+12
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 若 *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *..
    return sub_44ABE0((uint32_t *)*(this + 2), 11);  // 选中索引 setter
  return result;  // result=this+48 UDP 上报使能位
}



// ------------------------------------------------------------
// 0x54B210 CNRDSkillInventoryWindow__vmt0 —— CNRDSkillInventoryWindow__vmt0 构造（47DF50 + 54ACD0 + 4F2E40）
// ------------------------------------------------------------
// 大白话：技能栏构造：47DF50 + 54ACD0 + 4F2E40。
void /*thiscall*/ CNRDSkillInventoryWindow__vmt0(uint32_t *this, int nArg2)  // 函数: CNRDSkillInventoryWindow__vmt0 构造（47DF50 + 54ACD0 + 4F2E40）
{
  int nArg22; // ebx
  uint32_t *pThis; // esi
  int *v4; // edx
  int v5; // edi
  int fld_e5; // eax
  uint32_t *v7; // ecx
  int v8; // ecx
  int v9; // eax
  int fld_e52; // [esp+Ch] [ebp-4h]

  nArg22 = nArg2;
  pThis = this;
  if ( nArg2 == *(this + 1) )  // 若 nArg2 == *(this + 1)
  {
    v4 = (int *)dword_8F853C;
    v5 = 0;
    fld_e5 = 42 * *(uint32_t *)(*(this + 5) + 104) + 6;
    fld_e52 = fld_e5;
    do
    {
      if ( fld_e5 < *v4 )  // 若 fld_e5 < *v4
      {
        v7 = *(uint32_t **)(v4[1] + 4 * fld_e5);
        if ( v7 != nullptr )  // 若 v7 非空
        {
          sub_47DF50(  // 调 参数；pszArg7 时按 this+630 剩余时间画倒计时
            v7,
            *(uint32_t *)(pThis[1] + 20) + 37 * (v5 % 6u) + 39,
            *(uint32_t *)(pThis[1] + 24) + 37 * (v5 / 6u) + 57,
            -1,
            0,
            0,
            1,
            1);
          v4 = (int *)dword_8F853C;
          pThis = this;
          nArg22 = nArg2;
          fld_e5 = fld_e52;
        }
      }
      ++v5;  // 自增v5
      fld_e52 = ++fld_e5;
    }
    while ( v5 < 42 );  // 当 v5 < 42 循环
    if ( *(uint8_t *)(nArg22 + 17) != 0 )  // 若 *(uint8_t *)(nArg22 + 17) != 0
    {
      if ( dword_79BE3C == *(uint32_t *)(nArg22 + 12) || (v8 = *(uint32_t *)(nArg22 + 12), dword_79BE34 == v8) || dword_79BE38 == v8 )  // 若 dword_79BE3C == *(uint32_t *)(nArg22 + 12) || (v8 = *(uint32_t..
      {
        v9 = sub_54ACD0(pThis, 1);  // 结果 = 技能栏数据
        if ( v9 != -1 )  // 若 v9 != -1
          sub_4F2E40(
            *(uint32_t *)(pThis[1] + 20) + 37 * ((-6 - 42 * *(uint32_t *)(pThis[5] + 104) + v9) % 6) + 39,
            *(uint32_t *)(pThis[1] + 24) + 37 * ((-6 - 42 * *(uint32_t *)(pThis[5] + 104) + v9) / 6) + 57);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x54B320 CNRDSkillInventoryWindow__vmt28 —— CNRDSkillInventoryWindow__vmt28 槽（54ACD0 + 41A5E0 + 47E7A0）
// ------------------------------------------------------------
// 大白话：技能栏槽：54ACD0 + 41A5E0 + 47E7A0。
char /*thiscall*/ CNRDSkillInventoryWindow__vmt28(uint32_t *this)  // 函数: CNRDSkillInventoryWindow__vmt28 槽（54ACD0 + 41A5E0 + 47E7A0）
{
  int fld_e1; // eax
  int v2; // eax
  int *v3; // esi
  int v4; // eax

  fld_e1 = *(this + 1);  // fld_e1 = this+1
  if ( *(uint8_t *)(fld_e1 + 17) == 0 )  // 若 *(uint8_t *)(fld_e1 + 17) == 0
    return 0;
  if ( dword_79BE38 != *(uint32_t *)(fld_e1 + 12) )  // 若 dword_79BE38 != *(uint32_t *)(fld_e1 + 12)
    return 0;
  if ( *(uint32_t *)(*(this + 2) + 2504) != 0 )  // 若 *(uint32_t *)(*(this + 2) + 2504) != 0
    return 0;
  v2 = sub_54ACD0(this, 1);  // 结果 = 技能栏数据
  if ( v2 == -1 )  // 若 v2 == -1
    return 0;
  if ( v2 < *(uint32_t *)dword_8F853C )  // 若 v2 < *(uint32_t *)dword_8F853C
  {
    v3 = *(int **)(*((uint32_t *)dword_8F853C + 1) + 4 * v2);
    if ( v3 != nullptr )  // 若 v3 非空
    {
      v4 = sub_41A5E0((unsigned int)v3 + 558);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_47E7A0(v3, v4 == 0, 1);  // 调 sub_47E7A0
    }
  }
  return 1;
}



// ------------------------------------------------------------
// 0x54B390 CNRDSkillInventoryWindow__vmtC —— CNRDSkillInventoryWindow__vmtC 打开槽（69C980 + 69A5F0 定位）
// ------------------------------------------------------------
// 大白话：技能栏打开槽：69C980 + 69A5F0 定位。
char /*thiscall*/ CNRDSkillInventoryWindow__vmtC(char *this)  // 函数: CNRDSkillInventoryWindow__vmtC 打开槽（69C980 + 69A5F0 定位）
{
  char *pThis; // ebx
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

  pThis = this;
  if ( dword_8F7C04 == 0 )  // 全局 dword_8F7C04 = 本机角色对象
    return 0;
  v3 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);  // 全局 dword_8F7C04 = 本机角色对象
  v4 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
  if ( v3 != 0 )  // 若 v3 != 0
  {
    switch ( v3 )  // 分支：按 v3 分派
    {
      case 1:  // case 1
        v7 = 33;
        v8 = pThis + 24;
        do
        {
          sub_69C980(v4, v7, v7, v7 - 1, -1, 0, 0);  // 调 sub_69C980
          v7 += 2;
          v8 += 4;
        }
        while ( v7 < 41 );  // 当 v7 < 41 循环
        break;
      case 2:  // case 2
        v9 = 98;
        v10 = pThis + 24;
        do
        {
          sub_69C980(v4, v9, v9, v9 - 1, -1, 0, 0);  // 调 sub_69C980
          v9 += 2;
          v10 += 4;
        }
        while ( v9 < 108 );  // 当 v9 < 108 循环
        goto LABEL_19;  // 跳转 LABEL_19
      case 3:  // case 3
        v11 = 119;
        v12 = pThis + 24;
        do
        {
          sub_69C980(v4, v11, v11, v11 - 1, -1, 0, 0);  // 调 sub_69C980
          v11 += 2;
          v12 += 4;
        }
        while ( v11 < 127 );  // 当 v11 < 127 循环
        break;
      default:
        goto LABEL_20;  // 跳转 LABEL_20
    }
  }
  else
  {
    v5 = 25;
    v6 = pThis + 24;
    do
    {
      sub_69C980(v4, v5, v5, v5 - 1, -1, 0, 0);  // 调 sub_69C980
      v5 += 2;
      v6 += 4;
    }
    while ( v5 < 33 );  // 当 v5 < 33 循环
  }
  sub_69C980(v4, 95, 95, 94, -1, 0, 0);  // 调 sub_69C980
LABEL_19:
  pThis = this;
LABEL_20:
  v13 = (uint32_t **)(pThis + 24);
  v14 = 337;
  for ( i = 5; i != 0; --i )  // 循环：i = 5; i != 0; --i
  {
    sub_69A5F0(*v13, v14, 80);  // 调 sub_69A5F0
    v14 += (*v13++)[7];
  }
  return 1;
}



// ------------------------------------------------------------
// 0x54B4E0 sub_54B4E0 —— 技能栏页绘制（98 行：43C250/43C410/69A5F0/69A840 + 46F7A0/46F880 + 69CE50/426BD0/69C780）
// ------------------------------------------------------------
// 大白话：技能栏页绘制：43C250/43C410/69A5F0/69A840 + 46F7A0/46F880 + 69CE50/426BD0/69C780。
uint32_t */*thiscall*/ sub_54B4E0(uint32_t *this)  // 技能栏页绘制
{
  uint8_t *pMem; // eax
  uint8_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax
  uint8_t *pMem3; // eax
  uint8_t *v7; // eax
  uint32_t *pThis_6; // edi
  uint8_t *pMem4; // eax
  uint8_t *v10; // eax
  uint8_t *pMem5; // edi
  int v12; // ebx
  uint32_t *pMem52; // ecx
  uint8_t *pMem6; // edi
  int v15; // ebx
  void *Block; // [esp+10h] [ebp-14h]
  int i; // [esp+14h] [ebp-10h]

  pMem = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C250(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 48), 0);  // 结果 = nengine::CNFrame 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 1) = v3;  // this+4 = v3
  *((uint32_t *)v3 + 7) = *((uint32_t *)v3 + 7);
  *((uint32_t *)v3 + 8) = 353;
  *(uint32_t *)(*(this + 1) + 68) = this;
  pMem2 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 11, 12, 13, 11, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(this + 4) = v5;  // this+16 = v5
  sub_69A5F0(v5, 51, 353);  // 调 sub_69A5F0
  sub_69A840(*(this + 4));  // 调 sub_69A840
  Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
  pMem3 = operator new(0x70u);  // 堆分配 112 字节对象
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    v7 = sub_46F7A0(pMem3, 0);  // 结果 = nengine::CNRadioButton 构造
  else
    v7 = nullptr;  // v7 = nullptr 空指针
  *(this + 5) = v7;  // this+20 = v7
  pThis_6 = this + 6;
  for ( i = 5; i != 0; --i )  // 循环：i = 5; i != 0; --i
  {
    pMem4 = operator new(0x88u);  // 堆分配 136 字节对象
    if ( pMem4 != nullptr )  // 若 pMem4 非空
      v10 = sub_46F880(pMem4, (int)Block, 95, 95, 94, -1, 0, 0);  // 结果 = nengine::CNCheckBox 构造
    else
      v10 = nullptr;  // v10 = nullptr 空指针
    *pThis_6 = v10;  // *pThis_6 写入 v10
    sub_69A840(v10);  // 调 sub_69A840
    ++pThis_6;  // 自增pThis_6
  }
  sub_69CE50(0);  // 调 sub_69CE50
  sub_69A840(*(this + 5));  // 调 sub_69A840
  pMem5 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem5 != nullptr )  // 若 pMem5 非空
  {
    v12 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 48);
    sub_426BD0(pMem5);  // nengine::IControl 构造
    *(uint32_t *)pMem5 = &vftbl_nengine__CNButton;
    sub_69C780(pMem5);  // 调 sub_69C780
    nengine__CNButton__vmt20(v12, 1, 2, 3, 1, 0, 0);
    pMem52 = pMem5;
  }
  else
  {
    pMem52 = nullptr;  // pMem52 = nullptr 空指针
  }
  *(this + 11) = pMem52;  // this+44 = pMem52
  sub_69A5F0(pMem52, 80, 332);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  pMem6 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem6 != nullptr )  // 若 pMem6 非空
  {
    v15 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 48);
    sub_426BD0(pMem6);  // nengine::IControl 构造
    *(uint32_t *)pMem6 = &vftbl_nengine__CNButton;
    sub_69C780(pMem6);  // 调 sub_69C780
    nengine__CNButton__vmt20(v15, 4, 5, 6, 4, 0, 0);
  }
  else
  {
    pMem6 = nullptr;  // pMem6 = nullptr 空指针
  }
  *(this + 12) = pMem6;  // this+48 = pMem6
  sub_69A5F0(pMem6, 163, 332);  // 调 sub_69A5F0
  sub_69A840(*(this + 12));  // 调 sub_69A840
  return sub_69A5F0((uint32_t *)*(this + 1), 320, 63);  // 调 sub_69A5F0
}



// ============================================================
// 【分区 14】状态窗口 CNRDStatusWindow（0x54B780-0x54C8B0）
// vmt0=构造（570 行：4938F0/491D00 部件 + 4E66B0/4DA0F0 属性面板装配）；
// vmt8=Update（CLICK_BUTTON2/WINDOW_CLOSE）。
// ============================================================
// ------------------------------------------------------------
// 0x54B780 sub_54B780 —— 技能栏辅助（22 行）
// ------------------------------------------------------------
// 大白话：技能栏辅助：22 行。
int /*thiscall*/ sub_54B780(uint32_t *this)  // 函数: 技能栏辅助（22 行）
{
  int (/*thiscall*/ ***fld_e1)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e4)(uint32_t, int); // ecx

  fld_e1 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( fld_e1 != nullptr )  // 若 fld_e1 非空
    result = (**fld_e1)(fld_e1, 1);
  fld_e4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 4);  // this+4 宿主对象
  *(this + 1) = 0;  // this+4 = 0
  if ( fld_e4 != nullptr )  // 若 fld_e4 非空
    result = (**fld_e4)(fld_e4, 1);
  *(this + 4) = 0;  // this+16 = 0
  return result;
}



// ------------------------------------------------------------
// 0x54B7B0 CNRDStatusWindow__vmt8 —— CNRDStatusWindow__vmt8 Update（CLICK_BUTTON2/WINDOW_CLOSE 音效）
// ------------------------------------------------------------
// 大白话：状态窗逐帧 Update：处理 CLICK_BUTTON2/WINDOW_CLOSE 音效。
uint8_t */*thiscall*/ CNRDStatusWindow__vmt8(uint32_t *this)  // CNRDStatusWindow__vmt8 Update（CLICK_BUTTON2/WINDOW_CLOSE 音效）
{
  uint8_t *result; // eax

  if ( *(this + 5) == 0 )  // 若 *(this + 5) == 0
    *(this + 5) = dword_8F7C04;  // 全局 dword_8F7C04 = 本机角色对象
  result = (uint8_t *)*(this + 4);  // this+4 宿主对象
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 44))(this);  // 虚调用 vt+44
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    return sub_432EA0("WINDOW_CLOSE", -1, 0, 0);  // 字符串 “WINDOW_CLOSE”
  }
  return result;
}



// ------------------------------------------------------------
// 0x54B800 CNRDStatusWindow__vmtC —— CNRDStatusWindow__vmtC 打开槽（418DD0）
// ------------------------------------------------------------
// 大白话：状态窗打开槽：418DD0 取控件。
BOOL /*thiscall*/ CNRDStatusWindow__vmtC(uint32_t *this)  // 函数: CNRDStatusWindow__vmtC 打开槽（418DD0）
{
  int pObj; // ecx
  bool v3; // zf
  uint32_t *v4; // eax

  pObj = dword_8F7C04;  // 全局 dword_8F7C04 = 本机角色对象
  v3 = dword_8F7C04 == 0;  // 全局 dword_8F7C04 = 本机角色对象
  *(this + 5) = dword_8F7C04;  // 全局 dword_8F7C04 = 本机角色对象
  if ( !v3 )  // 若 !v3
  {
    v4 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1032))(pObj);  // 调虚函数 vt+1032
    *(this + 6) = sub_418DD0(*v4);  // this+24 = sub_418DD0(*v4)
  }
  return *(this + 5) != 0;
}



// ------------------------------------------------------------
// 0x54B850 sub_54B850 —— 状态窗数据（418DD0，27 行）
// ------------------------------------------------------------
// 大白话：状态窗数据：418DD0，27 行。
int /*cdecl*/ sub_54B850(uint32_t *uArg1, int nArg2, int nArg3)  // 函数: 状态窗数据（418DD0，27 行）
{
  if ( nArg2 >= nArg3 )  // 若 nArg2 >= nArg3
  {
    if ( nArg2 <= nArg3 )  // 若 nArg2 <= nArg3
    {
      *uArg1 = -1;  // *uArg1 写入 -1
      return 0;
    }
    else
    {
      *uArg1 = -13487361;  // *uArg1 写入 -13487361
      return sub_418DD0(2);  // 调 sub_418DD0
    }
  }
  else
  {
    *uArg1 = -14745706;  // *uArg1 写入 -14745706
    return sub_418DD0(1);  // 调 sub_418DD0
  }
}



// ------------------------------------------------------------
// 0x54B8B0 sub_54B8B0 —— 状态窗页绘制（53 行：43C250/43C410/69A5F0/69A840）
// ------------------------------------------------------------
// 大白话：状态窗页绘制：43C250/43C410/69A5F0/69A840。
int /*thiscall*/ sub_54B8B0(int this)  // 函数: 状态窗页绘制（53 行：43C250/43C410/69A5F0/69A840）
{
  uint8_t *pMem; // eax
  uint8_t *v3; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax
  int result; // eax

  pMem = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C250(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 52), 0);  // 结果 = nengine::CNFrame 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(uint32_t *)(this + 4) = v3;  // this+4 = v3
  *((uint32_t *)v3 + 7) = *((uint32_t *)v3 + 7);
  *((uint32_t *)v3 + 8) = 353;
  *(uint32_t *)(*(uint32_t *)(this + 4) + 68) = this;  // this+4 宿主对象
  pMem2 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 11, 12, 13, 11, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(uint32_t *)(this + 16) = v5;  // this+16 = v5
  sub_69A5F0(v5, 221, 353);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 16));  // 调 sub_69A840
  sub_69A5F0(*(uint32_t **)(this + 4), 29, 63);  // 调 sub_69A5F0
  *(uint8_t *)(this + 28) = 0;  // this+28 = 0
  *(uint8_t *)(this + 29) = 0;  // this+29 = 0
  *(uint8_t *)(this + 30) = 0;  // this+30 = 0
  *(uint8_t *)(this + 31) = 0;  // this+31 = 0
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint32_t *)(this + 52) = 0;  // this+52 = 0
  *(uint32_t *)(this + 60) = 0;  // this+60 = 0
  *(uint32_t *)(this + 64) = 0;  // this+64 = 0
  *(uint32_t *)(this + 68) = 0;  // this+68 = 0
  *(uint32_t *)(this + 72) = 0;  // this+72 = 0
  *(uint32_t *)(this + 76) = 0;  // this+76 = 0
  *(uint32_t *)(this + 44) = 6;  // this+44 = 6
  *(uint32_t *)(this + 48) = 12;  // this+48 = 12
  *(uint32_t *)(this + 56) = 1600;  // this+56 = 1600
  result = dword_99FCCC;
  *(uint32_t *)(this + 60) = 0;  // this+60 = 0
  *(uint32_t *)(this + 76) = result;  // this+76 = result
  *(uint32_t *)(this + 56) = 120;  // this+56 = 120
  *(uint32_t *)(this + 40) = 2;  // this+40 = 2
  return result;
}



// ------------------------------------------------------------
// 0x54B9F0 CNRDStatusWindow__vmt0 —— CNRDStatusWindow__vmt0 构造（570 行：4938F0/491D00/4924C0 部件 + 433F60/4176A0 + 4E66B0/4DA0F0 属性面板装配）
// ------------------------------------------------------------
// 大白话：状态窗构造（570 行）：4938F0/491D00/4924C0 部件 + 433F60/4176A0 文本 +
// 4E66B0/4DA0F0 属性面板装配——本文件最大构造函数。
int /*userpurge*/ sub_54B9F0@<eax>(float *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, uint32_t *pArg4)  // 函数: CNRDStatusWindow__vmt0 构造（570 行：4938F0/491D00/4924C0 部件 + 433F60/4176A0 + 4E66B0/4DA0F0 属性面板装配）
{
  uint32_t *v5; // ecx
  int result; // eax
  int pObj; // ecx
  int v8; // edx
  int v9; // ebx
  int v10; // eax
  int pObj6; // ecx
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
  int pObj3; // eax
  int v28; // ebx
  int v29; // eax
  int v30; // eax
  int pObj12; // eax
  int v32; // eax
  int v33; // edx
  double v34; // st7
  float v35; // eax
  int v36; // ecx
  int pObj13; // eax
  int v38; // ebx
  int v39; // eax
  int v40; // eax
  int pObj5; // eax
  int v42; // eax
  int v43; // edx
  double v44; // st7
  int pObj7; // eax
  int v46; // eax
  int v47; // edx
  double v48; // st7
  int v49; // eax
  double v50; // st7
  int v51; // eax
  int pObj11; // ecx
  int v53; // ebx
  int pObj4; // eax
  int v55; // eax
  int v56; // eax
  double v57; // st7
  int v58; // eax
  int pObj9; // ecx
  int v60; // ebx
  int pObj14; // eax
  int v62; // eax
  int v63; // ebx
  int v64; // eax
  double v65; // st7
  int pObj16; // eax
  int v67; // eax
  int v68; // ebx
  int v69; // eax
  double v70; // st7
  int pObj8; // eax
  int v72; // esi
  int v73; // eax
  int v74; // eax
  int pObj10; // eax
  int v76; // eax
  int v77; // esi
  int v78; // eax
  int pObj17; // eax
  int v80; // esi
  int v81; // eax
  int v82; // eax
  int pObj2; // eax
  int v84; // eax
  int v85; // esi
  int v86; // eax
  int pObj15; // eax
  int v88; // ebx
  int v89; // eax
  int v90; // [esp-18h] [ebp-84h]
  uint32_t *pArg45; // [esp-14h] [ebp-80h]
  int v92; // [esp-10h] [ebp-7Ch]
  uint32_t *pArg42; // [esp-Ch] [ebp-78h]
  uint32_t *pArg43; // [esp-Ch] [ebp-78h]
  uint32_t *pArg44; // [esp-Ch] [ebp-78h]
  int v96; // [esp-Ch] [ebp-78h]
  int v97; // [esp-Ch] [ebp-78h]
  int v98; // [esp-Ch] [ebp-78h]
  int v99; // [esp-Ch] [ebp-78h]
  int v100; // [esp-Ch] [ebp-78h]
  int dword_8F7C182; // [esp-8h] [ebp-74h]
  int dword_8F7C1C2; // [esp-4h] [ebp-70h]
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
  int dword_796E502; // [esp+68h] [ebp-4h]

  v5 = *((uint32_t **)pArg1 + 1);
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = (int)pArg4;
  if ( pArg4 == v5 && *((uint32_t *)pArg1 + 5) != 0 )  // 若 pArg4 == v5 && *((uint32_t *)pArg1 + 5) != 0
  {
    pObj = *((uint32_t *)pArg1 + 6);
    v8 = pArg4[5];
    v9 = pArg4[6];
    v110 = v8;
    v112 = v9;
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v8 + 19, v9 + 22, dword_79C0B0);  // 调用虚函数槽 +152
    v10 = (*(int (/*thiscall*/ **)(uint32_t, int, int, int))(**((uint32_t **)pArg1 + 5) + 672))(*((uint32_t *)pArg1 + 5), 1, nArg3, nArg2);  // 调用虚函数槽 +672
    pObj6 = *((uint32_t *)pArg1 + 5);
    v108 = v10;
    v12 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 672))(pObj6, 3);  // 虚槽+672 子对象基址 getter（1364 字节步长，this+1364*a2+676）
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);  // 调用虚函数槽 +72
    v13 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)pArg1 + 5) + 832))(*((uint32_t *)pArg1 + 5));  // 调用虚函数槽 +832
    v111 = *(float *)&v13;
    pArg4 = (uint32_t *)(v110 + 130);
    if ( v13 != 0 )  // 若 v13 != 0
    {
      sub_4938F0(v13);  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      sub_491D00(dword_79C0B0, (int)pArg4 - 2, v9 + 24, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      pArg4 = (uint32_t *)((char *)pArg4 + *(uint32_t *)(*(uint32_t *)sub_4924C0(0) + 36) - 1);  // 结果 = 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
    }
    v14 = *((uint32_t *)pArg1 + 5);
    v15 = *(uint32_t *)(v14 + 312);  // v15 = v14+312
    v16 = v14 + 288;
    if ( v15 < 0x10 )  // 若 v15 < 0x10
      v17 = v16 + 4;
    else
      v17 = *(uint32_t *)(v16 + 4);  // v17 = v16+4
    (*(void (/*cdecl*/ **)(int, uint32_t *, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      pArg4,
      v9 + 27,
      -1,
      v17);
    v18 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)pArg1 + 5) + 1032))(*((uint32_t *)pArg1 + 5));  // 调用虚函数槽 +1032
    v19 = *(uint32_t *)(v18 + 36);  // v19 = v18+36
    v20 = v18 + 12;
    if ( v19 < 0x10 )  // 若 v19 < 0x10
      v21 = v20 + 4;
    else
      v21 = *(uint32_t *)(v20 + 4);  // v21 = v20+4
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 + 130,
      v9 + 48,
      -1,
      v21);
    (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 + 143,
      v9 + 69,
      -1,
      "Lv.%2d",  // 字符串 “Lv.%2d”
      *v12);
    v22 = *(uint32_t *)dword_79C0B0;  // v22 = dword_79C0B0
    dword_8F7C1C2 = dword_8F7C1C;
    dword_8F7C182 = dword_8F7C18;
    v23 = sub_422E70(499);  // 调 sub_422E70
    (*(void (/*cdecl*/ **)(int, int, int, int, char *, int, int))(v22 + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 + 130,
      v112 + 90,
      -1,
      v23,
      dword_8F7C182,
      dword_8F7C1C2);
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, (uint32_t *)pArg1 + 7);  // 调用虚函数槽 +68
    v24 = *(uint32_t *)dword_79C0B0;  // v24 = dword_79C0B0
    pArg4 = *((uint32_t **)pArg1 + 5);
    v25 = (*(int (**)(void))(*pArg4 + 1032))();  // 结果 = 虚调用 vt+1032
    v26 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg4 + 1032))(pArg4, *(uint32_t *)(v25 + 44));  // 结果 = 虚调用 vt+1032
    (*(void (/*cdecl*/ **)(int, int, int, int, const char *, uint32_t))(v24 + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 + 148,
      v112 + 69,
      -1,
      "%d / %d",  // 字符串 “%d / %d”
      *(uint32_t *)(v26 + 40));
    pArg4 = nullptr;  // pArg4 = nullptr 空指针
    v111 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 1)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v107 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 18));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v109 = COERCE_FLOAT(sub_41A5E0(v108 + 4));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v113 = COERCE_FLOAT(sub_41A5E0(v108 + 18));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    pObj3 = sub_54B850(  // 结果 = 状态窗数据
            &pArg4,
            (uint64_t)((double)SLODWORD(v109) * v113),
            (uint64_t)((double)SLODWORD(v111) * v107));
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v110 + 82, v112 + 129, dword_79C0B0);  // 调用虚函数槽 +152
    v28 = *(uint32_t *)dword_79C0B0;  // v28 = dword_79C0B0
    v113 = pArg1[5];
    v29 = (*(int (**)(void))(*(uint32_t *)LODWORD(v113) + 740))();  // 调用虚函数槽 +740
    v30 = (*(int (/*thiscall*/ **)(float, int))(*(uint32_t *)LODWORD(v113) + 736))(COERCE_FLOAT(LODWORD(v113)), v29);  // 调用虚函数槽 +736
    (*(void (/*cdecl*/ **)(int, int, int, uint32_t *, const char *, int))(v28 + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 + 17,
      v112 + 128,
      pArg4,
      "%d/%d",  // 字符串 “%d/%d”
      v30);
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 15)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 74));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v107 = COERCE_FLOAT(sub_41A5E0(v108 + 60));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v111 = COERCE_FLOAT(sub_41A5E0(v108 + 74));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    pObj12 = sub_54B850(  // 结果 = 状态窗数据
            &pArg4,
            (uint64_t)((double)SLODWORD(v107) * v111),
            (uint64_t)((double)SLODWORD(v113) * v109));
    if ( pObj12 != 0 )  // 若 pObj12 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj12 + 152))(pObj12, v110 + 82, v112 + 156, dword_79C0B0);  // 调用虚函数槽 +152
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 15)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v32 = sub_41A5E0((unsigned int)v12 + 74);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v33 = *((uint32_t *)pArg1 + 5);
    v109 = *(float *)&v32;
    v34 = sub_433F60(v33, 3);  // 调 sub_433F60
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 + 17,
      v112 + 155,
      pArg4,
      "%d",  // 字符串 “%d”
      (unsigned int)(uint64_t)(v34 * (double)(int)(uint64_t)((double)SLODWORD(v113) * v109)));
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 29)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 130));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v107 = COERCE_FLOAT(sub_41A5E0(v108 + 116));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v111 = COERCE_FLOAT(sub_41A5E0(v108 + 130));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v107 = COERCE_FLOAT(
             sub_54B850(  // 状态窗数据
               &pArg4,
               (uint64_t)((double)SLODWORD(v107) * v111),
               (uint64_t)((double)SLODWORD(v113) * v109)));
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 29)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v35 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 130));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v36 = *((uint32_t *)pArg1 + 5);
    v109 = v35;
    v113 = sub_433F60(v36, 5) * (double)(int)(uint64_t)((double)SLODWORD(v113) * v35);  // 调 sub_433F60
    if ( v107 != 0.0 )  // 若 v107 != 0.0
      (*(void (/*thiscall*/ **)(float, int, int, int))(*(uint32_t *)LODWORD(v107) + 152))(
        COERCE_FLOAT(LODWORD(v107)),
        v110 + 82,
        v112 + 183,
        dword_79C0B0);  // dword_79C0B0（文本/图像绘制对象）
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 + 17,
      v112 + 182,
      pArg4,
      "%d",  // 字符串 “%d”
      (unsigned int)(uint64_t)v113);
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 8)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 46));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v107 = COERCE_FLOAT(sub_41A5E0(v108 + 32));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v111 = COERCE_FLOAT(sub_41A5E0(v108 + 46));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    pObj13 = sub_54B850(  // 结果 = 状态窗数据
            &pArg4,
            (uint64_t)((double)SLODWORD(v107) * v111),
            (uint64_t)((double)SLODWORD(v113) * v109));
    if ( pObj13 != 0 )  // 若 pObj13 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj13 + 152))(pObj13, v110 + 211, v112 + 129, dword_79C0B0);  // 调用虚函数槽 +152
    v38 = *(uint32_t *)dword_79C0B0;  // v38 = dword_79C0B0
    v113 = pArg1[5];
    v39 = (*(int (**)(void))(*(uint32_t *)LODWORD(v113) + 756))();  // 调用虚函数槽 +756
    v40 = (*(int (/*thiscall*/ **)(float, int))(*(uint32_t *)LODWORD(v113) + 752))(COERCE_FLOAT(LODWORD(v113)), v39);  // 调用虚函数槽 +752
    (*(void (/*cdecl*/ **)(int, int, int, uint32_t *, const char *, int))(v38 + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 + 148,
      v112 + 128,
      pArg4,
      "%d/%d",  // 字符串 “%d/%d”
      v40);
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 22)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 102));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v107 = COERCE_FLOAT(sub_41A5E0(v108 + 88));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v111 = COERCE_FLOAT(sub_41A5E0(v108 + 102));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    pObj5 = sub_54B850(  // 结果 = 状态窗数据
            &pArg4,
            (uint64_t)((double)SLODWORD(v107) * v111),
            (uint64_t)((double)SLODWORD(v113) * v109));
    if ( pObj5 != 0 )  // 若 pObj5 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v110 + 211, v112 + 156, dword_79C0B0);  // 调用虚函数槽 +152
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 22)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v42 = sub_41A5E0((unsigned int)v12 + 102);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v43 = *((uint32_t *)pArg1 + 5);
    v109 = *(float *)&v42;
    v44 = sub_433F60(v43, 4);  // 调 sub_433F60
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 + 148,
      v112 + 155,
      pArg4,
      "%d",  // 字符串 “%d”
      (unsigned int)(uint64_t)(v44 * (double)(int)(uint64_t)((double)SLODWORD(v113) * v109)));
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 36)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 158));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v107 = COERCE_FLOAT(sub_41A5E0(v108 + 144));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v111 = COERCE_FLOAT(sub_41A5E0(v108 + 158));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    pObj7 = sub_54B850(  // 结果 = 状态窗数据
            &pArg4,
            (uint64_t)((double)SLODWORD(v107) * v111),
            (uint64_t)((double)SLODWORD(v113) * v109));
    if ( pObj7 != 0 )  // 若 pObj7 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v110 + 211, v112 + 183, dword_79C0B0);  // 调用虚函数槽 +152
    v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 36)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v46 = sub_41A5E0((unsigned int)v12 + 158);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v47 = *((uint32_t *)pArg1 + 5);
    v109 = *(float *)&v46;
    v48 = sub_433F60(v47, 6);  // 调 sub_433F60
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 + 148,
      v112 + 182,
      pArg4,
      "%d",  // 字符串 “%d”
      (unsigned int)(uint64_t)(v48 * (double)(int)(uint64_t)((double)SLODWORD(v113) * v109)));
    LODWORD(v113) = v108 + 1124;
    if ( sub_41A5E0(v108 + 1124) != 0 || sub_41A5E0((unsigned int)(v12 + 281)) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 281)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v49 = sub_41A5E0(LODWORD(v113));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_54B850(&pArg4, v49, LODWORD(v109));  // 状态窗数据
      v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 281)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v50 = sub_433F60(*((uint32_t *)pArg1 + 5), 7) * (double)SLODWORD(v113);  // 调 sub_433F60
      sprintf(Buffer, off_724968, (unsigned int)(uint64_t)v50);  // 调 sprintf 格式化
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t *, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        v110 + 17,
        v112 + 216,
        pArg4,
        Buffer);
    }
    else
    {
      Buffer[0] = 0;
    }
    v51 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, int))(**((uint32_t **)pArg1 + 5) + 708))(*((uint32_t *)pArg1 + 5), 0, 1);  // 调用虚函数槽 +708
    pObj11 = *((uint32_t *)pArg1 + 5);
    v111 = *(float *)&v51;
    v53 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj11 + 708))(pObj11, 0, 3);  // 调用虚函数槽 +708
    pObj4 = sub_54B850(&pArg4, LODWORD(v111), v53);  // 结果 = 状态窗数据
    if ( pObj4 != 0 )  // 若 pObj4 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v110 + 82, v112 + 217, dword_79C0B0);  // 调用虚函数槽 +152
    pArg42 = pArg4;
    v113 = *(float *)dword_79C0B0;  // v113 = dword_79C0B0
    v55 = sub_4176A0(Buffer);  // 结果 = 文本像素宽估算（5 × 字符数）
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(LODWORD(v113) + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 - v55 + 17,
      v112 + 216,
      pArg42,
      "%d",  // 字符串 “%d”
      v53);
    LODWORD(v113) = v108 + 1166;
    if ( sub_41A5E0(v108 + 1166) != 0 || sub_41A5E0((unsigned int)v12 + 1166) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v109 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 1166));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v56 = sub_41A5E0(LODWORD(v113));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_54B850(&pArg4, v56, LODWORD(v109));  // 状态窗数据
      v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 1166));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v57 = sub_433F60(*((uint32_t *)pArg1 + 5), 9) * (double)SLODWORD(v113);  // 调 sub_433F60
      sprintf(Buffer, off_724968, (unsigned int)(uint64_t)v57);  // 调 sprintf 格式化
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t *, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        v110 + 17,
        v112 + 242,
        pArg4,
        Buffer);
    }
    else
    {
      Buffer[0] = 0;
    }
    v58 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**((uint32_t **)pArg1 + 5) + 708))(*((uint32_t *)pArg1 + 5), 1, 1);  // 调用虚函数槽 +708
    pObj9 = *((uint32_t *)pArg1 + 5);
    v111 = *(float *)&v58;
    v60 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj9 + 708))(pObj9, 1, 3);  // 调用虚函数槽 +708
    pObj14 = sub_54B850(&pArg4, LODWORD(v111), v60);  // 结果 = 状态窗数据
    if ( pObj14 != 0 )  // 若 pObj14 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj14 + 152))(pObj14, v110 + 82, v112 + 243, dword_79C0B0);  // 调用虚函数槽 +152
    pArg43 = pArg4;
    v113 = *(float *)dword_79C0B0;  // v113 = dword_79C0B0
    v62 = sub_4176A0(Buffer);  // 结果 = 文本像素宽估算（5 × 字符数）
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(LODWORD(v113) + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 - v62 + 17,
      v112 + 242,
      pArg43,
      "%d",  // 字符串 “%d”
      v60);
    v105 = 0;
    v106 = 0;
    v111 = COERCE_FLOAT(sub_4E66B0(0));  // 结果 = 场景/角色系数查询（PVP 50 / 战场表 / 角色技能表）
    if ( sub_41A5E0(v108 + 1138) != 0 || sub_41A5E0((unsigned int)v12 + 1138) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 1138));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v64 = sub_41A5E0(v108 + 1138);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_54B850(&pArg4, v64, LODWORD(v113));  // 状态窗数据
      v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)v12 + 1138));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v65 = sub_433F60(*((uint32_t *)pArg1 + 5), 8) * (double)SLODWORD(v113);  // 调 sub_433F60
      sprintf(Buffer, off_724968, (unsigned int)(uint64_t)v65);  // 调 sprintf 格式化
      v63 = v112;
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t *, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        v110 + 148,
        v112 + 216,
        pArg4,
        Buffer);
    }
    else
    {
      v63 = v112;
      Buffer[0] = 0;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int *, float, uint32_t, int))(**((uint32_t **)pArg1 + 5) + 712))(
      *((uint32_t *)pArg1 + 5),
      &v105,
      COERCE_FLOAT(LODWORD(v111)),
      0,
      1);
    (*(void (/*thiscall*/ **)(uint32_t, int *, float, uint32_t, int))(**((uint32_t **)pArg1 + 5) + 712))(
      *((uint32_t *)pArg1 + 5),
      &v106,
      COERCE_FLOAT(LODWORD(v111)),
      0,
      3);
    pObj16 = sub_54B850(&pArg4, v105, v106);  // 结果 = 状态窗数据
    if ( pObj16 != 0 )  // 若 pObj16 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj16 + 152))(pObj16, v110 + 211, v63 + 217, dword_79C0B0);  // 调用虚函数槽 +152
    v104 = v106;
    pArg44 = pArg4;
    v92 = v63 + 216;
    v113 = *(float *)dword_79C0B0;  // v113 = dword_79C0B0
    v67 = sub_4176A0(Buffer);  // 结果 = 文本像素宽估算（5 × 字符数）
    v68 = v110;
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(LODWORD(v113) + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v110 - v67 + 148,
      v92,
      pArg44,
      "%d",  // 字符串 “%d”
      v104);
    if ( sub_41A5E0(v108 + 1180) != 0 || sub_41A5E0((unsigned int)(v12 + 295)) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 295)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v69 = sub_41A5E0(v108 + 1180);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_54B850(&pArg4, v69, LODWORD(v113));  // 状态窗数据
      v113 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v12 + 295)));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v70 = sub_433F60(*((uint32_t *)pArg1 + 5), 10);  // 调 sub_433F60
      sprintf(Buffer, off_724968, (unsigned int)(uint64_t)(v70 * (double)SLODWORD(v113)));  // 调 sprintf 格式化
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t *, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        v68 + 148,
        v112 + 242,
        pArg4,
        Buffer);
    }
    else
    {
      Buffer[0] = 0;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int *, float))(**((uint32_t **)pArg1 + 5) + 712))(
      *((uint32_t *)pArg1 + 5),
      &v105,
      COERCE_FLOAT(LODWORD(v111)));
    (*(void (/*thiscall*/ **)(uint32_t, int *, float, int, int))(**((uint32_t **)pArg1 + 5) + 712))(
      *((uint32_t *)pArg1 + 5),
      &v106,
      COERCE_FLOAT(LODWORD(v111)),
      1,
      3);
    pObj8 = sub_54B850(&pArg4, v105, v106);  // 结果 = 状态窗数据
    if ( pObj8 != 0 )  // 若 pObj8 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, v68 + 211, v112 + 243, dword_79C0B0);  // 调用虚函数槽 +152
    v72 = *(uint32_t *)dword_79C0B0;  // v72 = dword_79C0B0
    v96 = v106;
    pArg45 = pArg4;
    v90 = v112 + 242;
    v73 = sub_4176A0(Buffer);  // 结果 = 文本像素宽估算（5 × 字符数）
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(v72 + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v68 - v73 + 148,
      v90,
      pArg45,
      "%d",  // 字符串 “%d”
      v96);
    v97 = sub_4DA0F0(0);  // 调 sub_4DA0F0
    v74 = sub_4DA0F0(0);  // 调 sub_4DA0F0
    pObj10 = sub_54B850(&pArg4, v74, v97);  // 结果 = 状态窗数据
    if ( pObj10 != 0 )  // 若 pObj10 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj10 + 152))(pObj10, v68 + 79, v112 + 299, dword_79C0B0);  // 调用虚函数槽 +152
    v113 = *(float *)dword_79C0B0;  // v113 = dword_79C0B0
    v76 = sub_4DA0F0(0);  // 调 sub_4DA0F0
    v77 = v112;
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(LODWORD(v113) + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v68 + 17,
      v112 + 298,
      pArg4,
      "%d",  // 字符串 “%d”
      v76);
    v98 = sub_4DA0F0(3);  // 调 sub_4DA0F0
    v78 = sub_4DA0F0(3);  // 调 sub_4DA0F0
    pObj17 = sub_54B850(&pArg4, v78, v98);  // 结果 = 状态窗数据
    if ( pObj17 != 0 )  // 若 pObj17 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj17 + 152))(pObj17, v68 + 79, v77 + 326, dword_79C0B0);  // 调用虚函数槽 +152
    LODWORD(v111) = v77 + 325;
    v80 = *(uint32_t *)dword_79C0B0;  // v80 = dword_79C0B0
    v81 = sub_4DA0F0(3);  // 调 sub_4DA0F0
    (*(void (**)(int, int, float, uint32_t *, const char *, ...))(v80 + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v68 + 17,
      COERCE_FLOAT(LODWORD(v111)),
      pArg4,
      "%d",  // 字符串 “%d”
      v81);
    v99 = sub_4DA0F0(1);  // 调 sub_4DA0F0
    v82 = sub_4DA0F0(1);  // 调 sub_4DA0F0
    pObj2 = sub_54B850(&pArg4, v82, v99);  // 结果 = 状态窗数据
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v68 + 210, v112 + 299, dword_79C0B0);  // 调用虚函数槽 +152
    v113 = *(float *)dword_79C0B0;  // v113 = dword_79C0B0
    v84 = sub_4DA0F0(1);  // 调 sub_4DA0F0
    v85 = v68 + 148;
    (*(void (**)(int, int, int, uint32_t *, const char *, ...))(LODWORD(v113) + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v68 + 148,
      v112 + 298,
      pArg4,
      "%d",  // 字符串 “%d”
      v84);
    v100 = sub_4DA0F0(2);  // 调 sub_4DA0F0
    v86 = sub_4DA0F0(2);  // 调 sub_4DA0F0
    pObj15 = sub_54B850(&pArg4, v86, v100);  // 结果 = 状态窗数据
    if ( pObj15 != 0 )  // 若 pObj15 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj15 + 152))(pObj15, v68 + 210, v112 + 326, dword_79C0B0);  // 调用虚函数槽 +152
    v88 = *(uint32_t *)dword_79C0B0;  // v88 = dword_79C0B0
    v89 = sub_4DA0F0(2);  // 调 sub_4DA0F0
    (*(void (**)(int, int, float, uint32_t *, const char *, ...))(v88 + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      v85,
      COERCE_FLOAT(LODWORD(v111)),
      pArg4,
      "%d",  // 字符串 “%d”
      v89);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
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
// 大白话：24 行小辅助（状态窗）。
int /*thiscall*/ sub_54C8B0(uint32_t *this)  // 函数: 24 行小辅助
{
  *(this + 4) = 0;  // this+16 = 0
  *(this + 8) = 0;  // this+32 = 0
  *(this + 31) = 0;  // this+124 = 0
  *(this + 32) = 0;  // this+128 = 0
  *(this + 33) = 0;  // this+132 = 0
  *(this + 34) = 0;  // this+136 = 0
  *(this + 35) = 0;  // this+140 = 0
  *(this + 6) = 0;  // this+24 = 0
  *(this + 5) = 0;  // this+20 = 0
  *(this + 7) = 0;  // this+28 = 0
  *(this + 16) = 0;  // this+64 = 0
  *(this + 17) = 0;  // this+68 = 0
  *(this + 18) = 0;  // this+72 = 0
  *(this + 30) = -1;  // this+120 = -1
  return 0;
}



// ------------------------------------------------------------
// 0x54C8F0 sub_54C8F0 —— 状态窗辅助（47 行）
// ------------------------------------------------------------
// 大白话：状态窗辅助：47 行。
int /*thiscall*/ sub_54C8F0(uint32_t *this)  // 函数: 状态窗辅助（47 行）
{
  int (/*thiscall*/ ***fld_e1)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e31)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e32)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e33)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e34)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e37)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e36)(uint32_t, int); // ecx

  fld_e1 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  if ( fld_e1 != nullptr )  // 若 fld_e1 非空
    result = (**fld_e1)(fld_e1, 1);
  fld_e31 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 31);
  *(this + 1) = 0;  // this+4 = 0
  if ( fld_e31 != nullptr )  // 若 fld_e31 非空
    result = (**fld_e31)(fld_e31, 1);
  fld_e32 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 32);  // this+32 格子像素尺寸
  *(this + 31) = 0;  // this+124 = 0
  if ( fld_e32 != nullptr )  // 若 fld_e32 非空
    result = (**fld_e32)(fld_e32, 1);
  fld_e33 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 33);  // this+33 职业数据脏位
  *(this + 32) = 0;  // this+128 = 0
  if ( fld_e33 != nullptr )  // 若 fld_e33 非空
    result = (**fld_e33)(fld_e33, 1);
  fld_e34 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 34);
  *(this + 33) = 0;  // this+132 = 0
  if ( fld_e34 != nullptr )  // 若 fld_e34 非空
    result = (**fld_e34)(fld_e34, 1);
  fld_e37 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 37);  // this+37 淡入收尾标志 A
  *(this + 34) = 0;  // this+136 = 0
  if ( fld_e37 != nullptr )  // 若 fld_e37 非空
    result = (**fld_e37)(fld_e37, 1);
  fld_e36 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 36);  // this+36 物品状态字
  *(this + 37) = 0;  // this+148 = 0
  if ( fld_e36 != nullptr )  // 若 fld_e36 非空
    result = (**fld_e36)(fld_e36, 1);
  *(this + 36) = 0;  // this+144 = 0
  return result;
}



// ------------------------------------------------------------
// 0x54C990 sub_54C990 —— 状态窗联动（56CFE0 频道选择复用）
// ------------------------------------------------------------
// 大白话：状态窗联动：复用 56CFE0 频道选择逻辑。
int /*thiscall*/ sub_54C990(uint32_t *this, int nArg2)  // 函数: 状态窗联动（56CFE0 频道选择复用）
{
  int result; // eax

  if ( nArg2 != 0 )  // 若 nArg2 != 0
  {
    result = nArg2 - 1;
    if ( nArg2 == 1 )  // 若 nArg2 == 1
    {
      *(uint8_t *)(*(this + 37) + 16) = 1;  // this+37 淡入收尾标志 A
      *(uint8_t *)(*(this + 36) + 16) = 0;  // this+36 物品状态字
      result = sub_56CFE0(13);  // 结果 = 频道选择主入口
      *(this + 4) = 1;  // this+16 = 1
      *(this + 6) = result;  // this+24 = result
    }
  }
  else
  {
    *(uint8_t *)(*(this + 37) + 16) = 0;  // this+37 淡入收尾标志 A
    *(uint8_t *)(*(this + 36) + 16) = 1;  // this+36 物品状态字
    result = sub_56CFE0(17);  // 结果 = 频道选择主入口
    *(this + 6) = result;  // this+24 = result
    *(this + 4) = 0;  // this+16 = 0
  }
  return result;
}



// ------------------------------------------------------------
// 0x54CA00 sub_54CA00 —— 工具窗面板绘制（491530/491630 批次 + 418DD0，100 行）
// ------------------------------------------------------------
// 大白话：工具窗面板绘制：491530/491630 批次 + 418DD0（100 行）。
int /*thiscall*/ sub_54CA00(uint32_t *this, int pArg2, int pArg3)  // 函数: 工具窗面板绘制（491530/491630 批次 + 418DD0，100 行）
{
  int pThis_9; // eax
  unsigned int fld_e7; // ecx
  int pObj7; // eax
  int pArg32; // edi
  int pArg22; // ebx
  int pObj2; // eax
  int pObj6; // eax
  int pObj4; // eax
  int pObj; // eax
  int pObj3; // eax
  int pObj5; // eax
  int pThis_9222; // ecx
  unsigned int pThis_92; // [esp+Ch] [ebp-Ch]
  int v18; // [esp+10h] [ebp-8h]
  unsigned int v19; // [esp+14h] [ebp-4h]
  uint8_t pThis_922; // [esp+24h] [ebp+Ch]

  pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  fld_e7 = *(this + 7);  // fld_e7 = this+7
  pThis_92 = pThis_9;
  v18 = fld_e7 & 1;  // fld_e7=this+28 逐帧驱动对象
  v19 = fld_e7 % 3;  // fld_e7=this+28 逐帧驱动对象
  if ( *(this + 5) != 0 )  // 若 *(this + 5) != 0
  {
    pObj6 = sub_418DD0(fld_e7 % 3 + 20);  // 调 sub_418DD0
    pArg32 = pArg3;
    pArg22 = pArg2;
    if ( pObj6 != 0 )  // 若 pObj6 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, pArg2 + 232, pArg3 + 127, dword_79C0B0);  // 调用虚函数槽 +152
    pObj2 = sub_418DD0(v19 + 17);  // 调 sub_418DD0
  }
  else
  {
    pObj7 = sub_418DD0(20);  // 调 sub_418DD0
    pArg32 = pArg3;
    pArg22 = pArg2;
    if ( pObj7 != 0 )  // 若 pObj7 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, pArg2 + 232, pArg3 + 127, dword_79C0B0);  // 调用虚函数槽 +152
    pObj2 = sub_418DD0(17);  // 调 sub_418DD0
  }
  if ( pObj2 != 0 )  // 若 pObj2 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, pArg22 + 34, pArg32 + 127, dword_79C0B0);  // 调用虚函数槽 +152
  pObj4 = sub_418DD0(v19 + 34);  // 调 sub_418DD0
  if ( pObj4 != 0 )  // 若 pObj4 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, pArg22 + 87, pArg32 + 150, dword_79C0B0);  // 调用虚函数槽 +152
  pObj = sub_418DD0(30);  // 调 sub_418DD0
  if ( pObj != 0 )  // 若 pObj != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, pArg22 + 61, pArg32 + 127, dword_79C0B0);  // 调用虚函数槽 +152
  sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
  if ( *(this + 5) != 0 )  // 若 *(this + 5) != 0
  {
    pObj3 = sub_418DD0(v19 + 31);  // 调 sub_418DD0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, pArg22 + 83, pArg32 + 127, dword_79C0B0);  // 调用虚函数槽 +152
  }
  if ( pThis_92 > 0x7D0 )  // 若 pThis_92 > 0x7D0
  {
    if ( pThis_92 <= 0x8CF )  // 若 pThis_92 <= 0x8CF
    {
      pObj5 = sub_418DD0(v18 + 15);  // 调 sub_418DD0
      if ( pObj5 != 0 )  // 若 pObj5 != 0
      {
        pThis_9222 = (uint8_t)(-49 - pThis_92);
        goto LABEL_25;  // 跳转 LABEL_25
      }
    }
  }
  else
  {
    pThis_922 = pThis_92;
    if ( pThis_92 >= 0xFF )  // 若 pThis_92 >= 0xFF
      pThis_922 = -1;
    pObj5 = sub_418DD0(v18 + 15);  // 调 sub_418DD0
    if ( pObj5 != 0 )  // 若 pObj5 != 0
    {
      pThis_9222 = pThis_922;
LABEL_25:
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj5,
        pArg22 + 72,
        pArg32 + 127,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        (pThis_9222 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    }
  }
  return sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
}



// ------------------------------------------------------------
// 0x54CC00 sub_54CC00 —— 工具窗面板绘制 2（164 行）
// ------------------------------------------------------------
// 大白话：工具窗面板绘制 2：164 行。
int /*thiscall*/ sub_54CC00(uint32_t *this, int pArg2, int pArg3)  // 函数: 工具窗面板绘制 2（164 行）
{
  int fld_e5; // eax
  int fld_e7; // esi
  int pObj5; // eax
  int pObj2; // eax
  int pObj3; // eax
  int fld_e18; // ecx
  int pObj4; // eax
  int pObj8; // eax
  unsigned int pThis_9; // edi
  int result; // eax
  int v14; // esi
  uint64_t v15; // rax
  int pObj7; // eax
  int pObj; // eax
  int pObj6; // eax
  int pObj9; // eax
  uint32_t v20[5]; // [esp+Ch] [ebp-20h]
  unsigned int fld_e72; // [esp+20h] [ebp-Ch]
  uint32_t *pThis; // [esp+24h] [ebp-8h]
  uint8_t v23; // [esp+29h] [ebp-3h]
  uint8_t v24; // [esp+2Ah] [ebp-2h]
  uint8_t v25; // [esp+2Bh] [ebp-1h]

  fld_e5 = *(this + 5);  // fld_e5 = this+5
  pThis = this;
  if ( fld_e5 != 0 )  // 若 fld_e5 != 0
    fld_e7 = *(this + 7) & 1;  // this+7 路径尾终止位
  else
    fld_e7 = 0;
  fld_e72 = *(this + 7) % 7u;  // this+7 路径尾终止位
  pObj5 = sub_418DD0(fld_e7 != 0 ? 4 : 1);  // 调 sub_418DD0
  if ( pObj5 != 0 )  // 若 pObj5 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, pArg2 + 34, pArg3 + 127, dword_79C0B0);  // 调用虚函数槽 +152
  pObj2 = sub_418DD0(fld_e7 != 0 ? 6 : 3);  // 调 sub_418DD0
  if ( pObj2 != 0 )  // 若 pObj2 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, pArg2 + 190, pArg3 + 127, dword_79C0B0);  // 调用虚函数槽 +152
  pObj3 = sub_418DD0(5);  // 调 sub_418DD0
  if ( pObj3 != 0 )  // 若 pObj3 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, pArg2 + 100, pArg3 + 127, dword_79C0B0);  // 调用虚函数槽 +152
  fld_e18 = *(this + 18);  // fld_e18 = this+18
  if ( fld_e18 != 0 )  // 若 fld_e18 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e18 + 152))(fld_e18, pArg2 + 131, pArg3 + 154, dword_79C0B0);  // 调用虚函数槽 +152
  sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
  pObj4 = sub_418DD0(fld_e72 + 8);  // 调 sub_418DD0
  if ( pObj4 != 0 )  // 若 pObj4 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, pArg2 + 113, pArg3 + 137, dword_79C0B0);  // 调用虚函数槽 +152
  sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
  pObj8 = sub_418DD0(2);  // 调 sub_418DD0
  if ( pObj8 != 0 )  // 若 pObj8 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, pArg2 + 100, pArg3 + 127, dword_79C0B0);  // 调用虚函数槽 +152
  pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  if ( result <= 5900 )  // 若 result <= 5900
  {
    v20[0] = 1000;
    v20[1] = 500;
    v20[2] = 250;
    v20[3] = 125;
    v20[4] = 0;
    if ( pThis_9 >= 0xFA0 )  // 若 pThis_9 >= 0xFA0
    {
      if ( pThis_9 >= 0x1004 )  // 若 pThis_9 >= 0x1004
      {
        if ( pThis_9 >= 0x1130 )  // 若 pThis_9 >= 0x1130
        {
          fld_e72 = pThis_9 - 4400;
          v23 = (uint64_t)((1.0 - sin((double)(pThis_9 - 4400) * 0.001047197551196598)) * 255.0);  // 调 sin（正弦）
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
        fld_e72 = pThis_9 - 3900;
        v23 = (uint64_t)((1.0 - sin((double)(pThis_9 - 3900) * 0.01570796326794897)) * 255.0);  // 调 sin（正弦）
        v25 = 127;
        v24 = 127;
      }
    }
    else
    {
      fld_e72 = pThis_9;
      v23 = 0;
      v14 = (uint8_t)(pThis_9 / 0x3E8);
      v15 = (uint64_t)((sin((double)pThis_9 * 6.283185307179586 / (double)(unsigned int)v20[v14]) + 1.0) * 127.0);  // 调 sin（正弦）
      if ( (uint8_t)(pThis_9 / 0x3E8) != 0 && pThis[30] != 0 )  // 若 (uint8_t)(pThis_9 / 0x3E8) != 0 && pThis[30] != 0
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
    sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    pObj7 = sub_418DD0(7);  // 调 sub_418DD0
    if ( pObj7 != 0 )  // 若 pObj7 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj7 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj7,
        pArg2 + 100,
        pArg3 + 127,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        (v23 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    pObj = sub_418DD0(55);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj,
        pArg2 + 187,
        pArg3 + 154,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        (v25 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    pObj6 = sub_418DD0(54);  // 调 sub_418DD0
    if ( pObj6 != 0 )  // 若 pObj6 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj6 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj6,
        pArg2 + 167,
        pArg3 + 154,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        (v24 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    pObj9 = sub_418DD0(56);  // 调 sub_418DD0
    if ( pObj9 != 0 )  // 若 pObj9 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj9 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj9,
        pArg2 + 167,
        pArg3 + 154,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        (v23 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    return sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
  }
  return result;
}


// ------------------------------------------------------------
// 0x54D020 CNRDItemToolWindow__vmt0 —— CNRDItemToolWindow__vmt0 构造（54CA00 + 54CC00）
// ------------------------------------------------------------
// 大白话：物品工具窗（CNRDItemToolWindow）构造：54CA00 + 54CC00 装配。
int /*thiscall*/ CNRDItemToolWindow__vmt0(uint32_t *this, int pArg2)  // 函数: CNRDItemToolWindow__vmt0 构造（54CA00 + 54CC00）
{
  int result; // eax
  int v4; // ecx
  int v5; // ebx
  int fld_e6; // eax
  int pObj; // eax
  int nState20; // esi  | +0x0014 → 状态机（0x54D600：==1 待机；置 2 = 处理中收尾）（证据: va=0054D600）（CNRDItemToolWindow；va=0054D600）
  int nCountdown16; // eax  | +0x0010 → 倒计时计数（vmt8 0x54D600：--fld_10 == 0 才进结算分支）（证据: va=0054D600）（CNRDItemToolWindow；va=0054D600）
  int v10; // [esp+Ch] [ebp+8h]

  result = pArg2;
  if ( pArg2 == *(this + 1) )  // 若 pArg2 == *(this + 1)
  {
    v4 = *(uint32_t *)(pArg2 + 24);  // v4 = pArg2+24
    v5 = *(uint32_t *)(pArg2 + 20);  // v5 = pArg2+20
    fld_e6 = *(this + 6);  // fld_e6 = this+6
    v10 = v4;
    if ( fld_e6 != 0 )  // 若 fld_e6 != 0
    {
      pObj = *(uint32_t *)(fld_e6 + 60);  // pObj = fld_e6+60
      if ( pObj != 0 )  // 若 pObj != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v5 + 28, v4 + 26, dword_79C0B0);  // 调用虚函数槽 +152
    }
    nState20 = *(this + 5);  // 读 fld_e5 = this+20（状态机）
    *(this + 7) = timeGetTime() / (nState20 != 0 ? 100 : 300);  // this+28 = timeGetTime() / (nState20 != 0 ? 100 : 300)
    nCountdown16 = *(this + 4);  // 读 fld_e4 = this+16（倒计时计数）
    if ( nCountdown16 != 0 )  // 若 fld_e4 != 0
    {
      result = nCountdown16 - 1;  // fld_e4=this+16 nCountdown16
      if ( result == 0 )  // 若 result == 0
        return sub_54CA00(this, v5, v10);  // 工具窗面板绘制
    }
    else
    {
      return sub_54CC00(this, v5, v10);  // 工具窗面板绘制 2
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x54D0C0 sub_54D0C0 —— 工具窗动画切换（69C340/69C360/69C500）——强化结果窗 0x63AC20 复用
// ------------------------------------------------------------
// 大白话：工具窗动画切换：69C340/69C360/69C500——强化结果窗 0x63AC20 复用。
int /*thiscall*/ sub_54D0C0(int **this, int nArg2)  // 函数: 工具窗动画切换（69C340/69C360/69C500）——强化结果窗 0x63AC20 复用
{
  unsigned int fld_e31; // eax
  int *fld_e35; // ecx
  int v5; // edi
  int fld_e312; // eax

  sub_69C340(-1);  // 调 sub_69C340
  sub_69C360(nArg2, 0);  // 调 sub_69C360
  fld_e31 = sub_69C500(*(this + 31));  // 调 sub_69C500
  fld_e35 = *(this + 35);  // fld_e35 = this+35
  if ( fld_e31 <= 5 )  // 若 fld_e31 <= 5
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*fld_e35 + 32))(fld_e35, 0);  // 虚调用 vt+32
  v5 = *fld_e35;
  fld_e312 = sub_69C500(*(this + 31));  // 调 sub_69C500
  return (*(int (/*thiscall*/ **)(uint32_t, int))(v5 + 32))(*(this + 35), fld_e312 - 5);  // 调用虚函数槽 +32
}



// ------------------------------------------------------------
// 0x54D120 sub_54D120 —— 工具窗条目（422E70/44E8D0 + 484ED0）
// ------------------------------------------------------------
// 大白话：工具窗条目：422E70/44E8D0 + 484ED0。
char /*thiscall*/ sub_54D120(uint32_t *this)  // 函数: 工具窗条目（422E70/44E8D0 + 484ED0）
{
  char *v2; // eax

  if ( (unsigned int)(*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C  // 全局 dword_8F852C = 角色/物品栏管理器
                                                                                               + 3)) < *(this + 29) )  // 工具窗条目（422E70/44E8D0 + 484ED0）
  {
    v2 = sub_422E70(1660);  // 调 sub_422E70
LABEL_9:
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);  // 对象池借出（按池号取可用对象）
    return 0;
  }
  if ( sub_484ED0(*(this + 17)) == -1  // 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
    || (unsigned int)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 17) + 44))(*(this + 17)) >= *(this + 28) )
  {
    if ( (int)sub_484ED0(*(this + 16)) < 0 )  // 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
    {
      v2 = sub_422E70(1658);  // 调 sub_422E70
      goto LABEL_9;  // 跳转 LABEL_9
    }
    if ( (int)sub_484ED0(*(this + 17)) >= 0 )  // 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
      return 1;
  }
  v2 = sub_422E70(1661);  // 调 sub_422E70
  goto LABEL_9;  // 跳转 LABEL_9
}



// ------------------------------------------------------------
// 0x54D1C0 CNRDItemToolWindow__vmt1C —— CNRDItemToolWindow__vmt1C 刷新槽（44F580/44F670 格子）
// ------------------------------------------------------------
// 大白话：工具窗刷新槽：44F580/44F670 格子。
char /*thiscall*/ CNRDItemToolWindow__vmt1C(int *this)  // 函数: CNRDItemToolWindow__vmt1C 刷新槽（44F580/44F670 格子）
{
  int pOwnerWnd; // eax
  uint32_t *pHostCtrl; // ebx
  int v5; // eax
  int v6; // eax
  int pObj; // esi
  int nCountdown16; // eax  | +0x0010 → 倒计时计数（vmt8 0x54D600：--fld_10 == 0 才进结算分支）（证据: va=0054D600）（CNRDItemToolWindow；va=0054D600）

  pOwnerWnd = *(this + 1);  // fld_e1 = this+1
  if ( *(uint8_t *)(pOwnerWnd + 17) == 0 || dword_79BE34 != *(uint32_t *)(pOwnerWnd + 12) )  // 若 *(uint8_t *)(fld_e1 + 17) == 0 || dword_79BE34 != *(uint32_t *..
    return 0;
  pHostCtrl = (uint32_t *)*(this + 2);
  if ( pHostCtrl[626] != 2 )  // 若 fld_e2[626] != 2
    return 0;
  v5 = pHostCtrl[627];
  if ( v5 != 3 && v5 != 4 )  // 若 v5 != 3 && v5 != 4
    return 0;
  v6 = pHostCtrl[629];
  if ( v6 >= *((uint32_t *)dword_8F852C + 2) )  // 全局 dword_8F852C = 角色/物品栏管理器
    return 0;
  pObj = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v6);  // 全局 dword_8F852C = 角色/物品栏管理器
  if ( pObj == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj) + 4) != pHostCtrl[628] )  // 虚槽+16 CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE0/44E850 + d
    return 0;
  nCountdown16 = *(this + 4);  // 读 fld_e4 = this+16（倒计时计数）
  if ( nCountdown16 != 0 )  // 若 fld_e4 != 0
  {
    if ( nCountdown16 == 1 )  // 若 fld_e4 == 1
    {
      sub_44F580(*(this + 2), pObj, 1);  // 道具二次校验分发（拒绝文案 408/409/410/411）
      return 1;
    }
  }
  else
  {
    sub_44F670(*(this + 2), pObj, 1);  // 道具校验分发 2（拒绝文案 1652/1653/1664）
  }
  return 1;
}



// ------------------------------------------------------------
// 0x54D260 CNRDItemToolWindow__vmt10 —— CNRDItemToolWindow__vmt10 状态切换（44ABE0 + 44E850）
// ------------------------------------------------------------
// 大白话：工具窗状态切换：44ABE0 + 44E850。
char /*thiscall*/ CNRDItemToolWindow__vmt10(uint32_t *this)  // 函数: CNRDItemToolWindow__vmt10 状态切换（44ABE0 + 44E850）
{
  uint32_t *fld_e2; // ecx
  int v3; // eax
  char result; // al

  fld_e2 = (uint32_t *)*(this + 2);
  v3 = fld_e2[626];
  if ( v3 == 18 || v3 == 7 )  // 若 v3 == 18 || v3 == 7
    sub_44ABE0(fld_e2, 0);  // 选中索引 setter
  sub_44E850((uint32_t *)*(this + 2), 23);  // 按池号批量回收活动对象
  result = sub_44E850((uint32_t *)*(this + 2), 59);  // 结果 = 按池号批量回收活动对象
  *(this + 16) = 0;  // 写 this+64 = 0（物品 id A）
  *(this + 17) = 0;  // 写 this+68 = 0（物品 id B）
  *(this + 18) = 0;  // 写 this+72 = 0（物品槽复位值）
  return result;
}



// ------------------------------------------------------------
// 0x54D2B0 sub_54D2B0 —— 21 行小辅助
// ------------------------------------------------------------
// 大白话：21 行小辅助（工具窗）。
int /*thiscall*/ sub_54D2B0(uint32_t *this, int nArg2)  // 函数: 21 行小辅助
{
  int result; // eax

  if ( *(this + 5) == 2 )  // 若 *(this + 5) == 2
  {
    *(this + 5) = 0;  // this+20 = 0
    *(this + 16) = 0;  // this+64 = 0
    *(this + 17) = 0;  // this+68 = 0
    *(this + 18) = 0;  // this+72 = 0
    *(this + 30) = -1;  // this+120 = -1
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x54D600 CNRDItemToolWindow__vmt8 —— CNRDItemToolWindow__vmt8 Update（98 行：CLICK_BUTTON2 + 69C690/69C400 + 486E00/486E80/54D120）
// ------------------------------------------------------------
// 大白话：工具窗逐帧 Update：CLICK_BUTTON2 音 + 69C690/69C400 焦点 + 486E00/486E80/54D120 操作。
char /*thiscall*/ CNRDItemToolWindow__vmt8(int this)  // 函数: CNRDItemToolWindow__vmt8 Update（98 行：CLICK_BUTTON2 + 69C690/69C400 + 486E00/486E80/54D120）
{
  int nItemIdA64; // eax  | +0x0040 → 物品 id A（CNRDItemToolWindow；va=0054D600）
  char *v2; // eax
  int fld_402; // edi  | +0x0040 → 物品 id A（CNRDItemToolWindow；va=0054D600）
  int nItemIdB68; // eax  | +0x0044 → 物品 id B（CNRDItemToolWindow；va=0054D600）
  char *v5; // eax
  int pFocusObj140; // eax  | +0x008C → 焦点对象（CNRDItemToolWindow；va=0054D600）
  int pThis_80; // edi
  int i; // ebx
  int pBtnB148; // eax  | +0x0094 → 按钮件 B（0x54D600：点击 → 44ABE0(宿主控件, 7)）（证据: va=0054D600）（CNRDItemToolWindow；va=0054D600）
  int pBtnA144; // eax  | +0x0090 → 按钮件 A（0x54D600：点击 → 44ABE0(宿主控件, 18)）（证据: va=0054D600）（CNRDItemToolWindow；va=0054D600）
  int fld_10; // eax  | +0x0010 → 倒计时计数（vmt8 0x54D600：--fld_10 == 0 才进结算分支）（证据: va=0054D600）（CNRDItemToolWindow；va=0054D600）

  pFocusObj140 = sub_69C690(*(uint32_t *)(this + 140));  // 结果 = 取设备对象 +112 字段（类型或句柄）
  sub_69C400(pFocusObj140);  // 调 sub_69C400
  pThis_80 = this + 128;  // this+128 第 2 组·+1208 增量子倍率
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
  {
    if ( *(uint8_t *)(*(uint32_t *)pThis_80 + 17) != 0 && dword_79BE34 == *(uint32_t *)(*(uint32_t *)pThis_80 + 12) )  // 若 *(uint8_t *)(*(uint32_t *)pThis_80 + 17) != 0 && dword_79BE34 ..
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    pThis_80 += 4;  // pThis_80=this+128 第 2 组·+1208 增量子倍率
  }
  pBtnB148 = *(uint32_t *)(this + 148);  // 读 fld_94 = this+148（按钮件 B）
  if ( *(uint8_t *)(pBtnB148 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnB148 + 12) )  // 若 *(uint8_t *)(fld_94 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    sub_44ABE0(*(uint32_t **)(this + 8), 7);  // 选中索引 setter
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  pBtnA144 = *(uint32_t *)(this + 144);  // 读 fld_90 = this+144（按钮件 A）
  if ( *(uint8_t *)(pBtnA144 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnA144 + 12) )  // 若 *(uint8_t *)(fld_90 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    sub_44ABE0(*(uint32_t **)(this + 8), 18);  // 选中索引 setter
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  fld_10 = *(uint32_t *)(this + 16);  // 读 fld_10 = this+16（倒计时计数）
  if ( fld_10 != 0 )  // 若 fld_10 != 0
  {
    if ( --fld_10 == 0 && *(uint32_t *)(this + 20) == 1 )  // 判定 “+20 状态机”
    {
      fld_10 = sub_699000(this + 36);  // 【clock_now(clk)】
      if ( fld_10 > 2000 )  // 若 fld_10 > 2000
      {
        nItemIdA64 = sub_484ED0(*(uint32_t *)(this + 64));  // 结果 = 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
        if ( nItemIdA64 >= 0 )  // 若 fld_40 >= 0
        {
          LOBYTE(fld_10) = sub_486E00(nItemIdA64);  // 请求 op 28（2 字节参数）
          if ( (uint8_t)fld_10 != 0 )  // 若 (uint8_t)fld_10 != 0
          {
            *(uint32_t *)(this + 20) = 2;  // 写 this+20 = 2（状态机）
            return fld_10;  // +0x0010 → 倒计时计数（vmt8 0x54D600：--fld_10 == 0 才进结算分支）（证据: va=0054D600）（CNRDItemToolWindow；va=0054D600）
          }
          v2 = sub_422E70(1659);  // 调 sub_422E70
        }
        else
        {
          v2 = sub_422E70(1658);  // 调 sub_422E70
        }
        LOBYTE(fld_10) = sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);  // 对象池借出（按池号取可用对象）
        *(uint32_t *)(this + 20) = 0;  // 写 this+20 = 0（状态机）
        *(uint32_t *)(this + 64) = 0;  // 写 this+64 = 0（物品 id A）
      }
    }
  }
  else if ( *(uint32_t *)(this + 20) == 1 )  // 判定 “+20 状态机”
  {
    fld_10 = sub_699000(this + 36);  // 【clock_now(clk)】
    if ( fld_10 > 5900 )  // 若 fld_10 > 5900
    {
      LOBYTE(fld_10) = sub_54D120((uint32_t *)this);  // 工具窗条目（422E70/44E8D0 + 484ED0）
      if ( (uint8_t)fld_10 == 1 )  // 若 (uint8_t)fld_10 == 1
      {
        fld_402 = sub_484ED0(*(uint32_t *)(this + 64));  // 结果 = 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
        nItemIdB68 = sub_484ED0(*(uint32_t *)(this + 68));  // 结果 = 由对象指针反查槽下标（线性扫描，空指针或未命中 -1）
        LOBYTE(fld_10) = sub_486E80(fld_402, nItemIdB68);  // 请求 op 83（槽号 + 对象 id + 参数）
        if ( (uint8_t)fld_10 != 0 )  // 若 (uint8_t)fld_10 != 0
        {
          *(uint32_t *)(this + 20) = 2;  // 写 this+20 = 2（状态机）
          return fld_10;  // +0x0010 → 倒计时计数（vmt8 0x54D600：--fld_10 == 0 才进结算分支）（证据: va=0054D600）（CNRDItemToolWindow；va=0054D600）
        }
        v5 = sub_422E70(1659);  // 调 sub_422E70
        LOBYTE(fld_10) = sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v5, 0);  // 对象池借出（按池号取可用对象）
      }
      *(uint32_t *)(this + 64) = 0;  // 写 this+64 = 0（物品 id A）
      *(uint32_t *)(this + 68) = 0;  // 写 this+68 = 0（物品 id B）
      *(uint32_t *)(this + 72) = 0;  // 写 this+72 = 0（物品槽复位值）
      *(uint32_t *)(this + 20) = 0;  // 写 this+20 = 0（状态机）
      *(uint32_t *)(this + 120) = -1;  // 写 this+120 = -1（哨兵槽）
    }
  }
  return fld_10;  // +0x0010 → 倒计时计数（vmt8 0x54D600：--fld_10 == 0 才进结算分支）（证据: va=0054D600）（CNRDItemToolWindow；va=0054D600）
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
// 大白话：工具窗页绘制：43C250/43C330 + 69C440/69C420/69C3E0/69C4C0 + 56CFE0。
char /*thiscall*/ sub_54D6E0(int this)  // 函数: 工具窗页绘制（106 行：43C250/43C330 + 69C440/69C420/69C3E0/69C4C0 + 56CFE0）
{
  uint8_t *pMem; // eax
  uint8_t *fld_20; // eax
  uint8_t *pMem2; // eax
  uint8_t *v5; // eax
  uint32_t *pMem3; // eax
  uint32_t *v7; // eax
  uint32_t *pMem4; // eax
  uint32_t *v9; // eax
  uint8_t *pMem5; // edi
  uint8_t *pMem52; // eax
  uint8_t *pMem6; // eax
  uint8_t *fld_80; // eax
  uint32_t *pMem7; // eax
  uint32_t *fld_202; // eax
  uint32_t *pMem8; // eax
  uint32_t *fld_203; // eax

  *(uint32_t *)(this + 32) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 36);  // this+32 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_20 = sub_43C250(pMem, *(uint32_t *)(this + 32), 0);  // 结果 = nengine::CNFrame 构造
  else
    fld_20 = nullptr;  // fld_20 = nullptr 空指针
  *(uint32_t *)(this + 4) = fld_20;  // this+4 = fld_20
  *((uint32_t *)fld_20 + 7) = *((uint32_t *)fld_20 + 7);
  *((uint32_t *)fld_20 + 8) = 250;
  *(uint32_t *)(*(uint32_t *)(this + 4) + 68) = this;  // this+4 宿主对象
  pMem2 = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    v5 = sub_43C330(pMem2, 130, 2048);  // 结果 = nengine::CNTextBox 构造
  else
    v5 = nullptr;  // v5 = nullptr 空指针
  *(uint32_t *)(this + 124) = v5;  // this+124 = v5
  sub_69C440(-4265479);  // 调 sub_69C440
  sub_69C420(2);  // 调 sub_69C420
  sub_69C3E0(5);  // 调 sub_69C3E0
  sub_69C4C0(dword_99FCCC);  // 调 sub_69C4C0
  sub_69A5F0(*(uint32_t **)(this + 124), 110, 31);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 124));  // 调 sub_69A840
  pMem3 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    v7 = sub_43C410(pMem3, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 4, 4, 5, 4, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v7 = nullptr;  // v7 = nullptr 空指针
  *(uint32_t *)(this + 128) = v7;  // this+128 = v7
  pMem4 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    v9 = sub_43C410(pMem4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 6, 6, 7, 6, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v9 = nullptr;  // v9 = nullptr 空指针
  *(uint32_t *)(this + 132) = v9;  // this+132 = v9
  pMem5 = operator new(0x88u);  // 堆分配 136 字节对象
  if ( pMem5 != nullptr )  // 若 pMem5 非空
  {
    sub_43C4D0(pMem5, *(uint32_t *)(this + 32), 29, 27);  // nengine::CNSlider 构造
    *(uint32_t *)pMem5 = &vftbl_nengine__CNVSlider;
    pMem52 = pMem5;
  }
  else
  {
    pMem52 = nullptr;  // pMem52 = nullptr 空指针
  }
  *(uint32_t *)(this + 136) = pMem52;  // this+136 = pMem52
  pMem6 = operator new(0x74u);  // 堆分配 116 字节对象
  if ( pMem6 != nullptr )  // 若 pMem6 非空
    fld_80 = sub_43C630(pMem6, *(uint32_t *)(this + 128), *(uint32_t *)(this + 132), *(uint32_t *)(this + 136));  // 结果 = nengine::CNVScroll 构造
  else
    fld_80 = nullptr;  // fld_80 = nullptr 空指针
  *(uint32_t *)(this + 140) = fld_80;  // this+140 = fld_80
  sub_69A5F0(fld_80, 249, 27);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 140));  // 调 sub_69A840
  pMem7 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem7 != nullptr )  // 若 pMem7 非空
    fld_202 = sub_43C410(pMem7, *(uint32_t *)(this + 32), 40, 41, 42, 40, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_202 = nullptr;  // fld_202 = nullptr 空指针
  *(uint32_t *)(this + 148) = fld_202;  // this+148 = fld_202
  sub_69A5F0(fld_202, 116, 215);  // 调 sub_69A5F0
  *(uint8_t *)(*(uint32_t *)(this + 148) + 16) = 0;  // this+148 第 4 组·+802 增量子倍率
  sub_69A840(*(uint32_t *)(this + 148));  // 调 sub_69A840
  pMem8 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem8 != nullptr )  // 若 pMem8 非空
    fld_203 = sub_43C410(pMem8, *(uint32_t *)(this + 32), 37, 38, 39, 37, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_203 = nullptr;  // fld_203 = nullptr 空指针
  *(uint32_t *)(this + 144) = fld_203;  // this+144 = fld_203
  sub_69A5F0(fld_203, 116, 215);  // 调 sub_69A5F0
  *(uint8_t *)(*(uint32_t *)(this + 144) + 16) = 0;  // this+144 第 4 组·+1040 增量子倍率
  sub_69A840(*(uint32_t *)(this + 144));  // 调 sub_69A840
  sub_69A5F0(*(uint32_t **)(this + 4), 29, 193);  // 调 sub_69A5F0
  *(uint8_t *)(*(uint32_t *)(this + 148) + 16) = 0;  // this+148 第 4 组·+802 增量子倍率
  *(uint8_t *)(*(uint32_t *)(this + 144) + 16) = 1;  // this+144 第 4 组·+1040 增量子倍率
  *(uint32_t *)(this + 24) = sub_56CFE0(17);  // 频道选择主入口
  *(uint32_t *)(this + 16) = 0;  // this+16 = 0
  *(uint8_t *)(this + 49) = 0;  // this+49 = 0
  *(uint8_t *)(this + 50) = 0;  // this+50 = 0
  return sub_698F90(this + 36, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x54DA10 sub_54DA10 —— PVP 结算辅助（22 行）
// ------------------------------------------------------------
// 大白话：PVP 结算辅助：22 行。
int /*thiscall*/ sub_54DA10(uint32_t *this)  // 函数: PVP 结算辅助（22 行）
{
  int (/*thiscall*/ ***fld_e17)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e32)(uint32_t, int); // ecx

  fld_e17 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 17);  // this+17 激活/可命中标志
  if ( fld_e17 != nullptr )  // 若 fld_e17 非空
    result = (**fld_e17)(fld_e17, 1);
  fld_e32 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 32);  // this+32 格子像素尺寸
  *(this + 17) = 0;  // this+68 = 0
  if ( fld_e32 != nullptr )  // 若 fld_e32 非空
    result = (**fld_e32)(fld_e32, 1);
  *(this + 32) = 0;  // this+128 = 0
  return result;
}



// ------------------------------------------------------------
// 0x54DA50 sub_54DA50 —— PVP 结算背景绘制（206 行：48F620 + 418DD0/4049F0/43B560）
// ------------------------------------------------------------
// 大白话：PVP 结算背景绘制：48F620 数据 + 418DD0/4049F0/43B560（206 行）。
char /*thiscall*/ sub_54DA50(int this, int nArg2, char pszArg3)  // 函数: PVP 结算背景绘制（206 行：48F620 + 418DD0/4049F0/43B560）
{
  void *pThis_C; // edi
  uint8_t nArg22; // bl
  int fld_48; // eax
  unsigned int fld_84; // ebx
  int v8; // edi
  int fld_482; // eax
  int fld_483; // eax
  uint8_t nArg23; // bl
  int v12; // edi
  int fld_484; // eax
  int nArg24; // ebx
  int fld_485; // eax
  int v16; // edi
  int fld_486; // eax
  int fld_487; // eax
  void *pThis_C2; // [esp+Ch] [ebp-4h]

  if ( pszArg3 == 1 )  // 若 pszArg3 == 1
  {
    pThis_C = (void *)sub_699000(this + 12);  // 【clock_now(clk)】
    pThis_C2 = pThis_C;
  }
  else
  {
    pThis_C2 = &unk_989680;
    pThis_C = &unk_989680;
  }
  if ( sub_48F620((uint32_t *)dword_99FEC0) )  // 对局中标志查询
  {
    nArg22 = nArg2;
    if ( nArg2 >= 90 )  // 若 nArg2 >= 90
      nArg22 = 90;
    fld_48 = sub_418DD0(*(uint32_t **)(this + 72), 0x56u);  // 调 sub_418DD0
    if ( fld_48 != 0 )  // 若 fld_48 != 0
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_48 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        fld_48,
        0,
        0,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        (nArg22 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    fld_84 = 2 * (*(uint32_t *)(this + 132) != 0) + 80;  // this+132 第 3 组·+60 增量项
    v8 = (uint64_t)sub_4049F0(-239.0, 127.0, (int)pThis_C, 300, 1);  // 结果 = 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正
    fld_482 = sub_418DD0(*(uint32_t **)(this + 72), fld_84);  // 调 sub_418DD0
    if ( fld_482 != 0 )  // 若 fld_482 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_482 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        fld_482,
        v8,
        179,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg2 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    if ( v8 == 127 && pszArg3 != 0 && (fld_483 = sub_418DD0(*(uint32_t **)(this + 72), fld_84 + 1)) != 0 )  // 若 v8 == 127 && pszArg3 != 0 && (fld_483 = sub_418DD0(*(uint32_t ..
    {
      nArg23 = nArg2;
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_483 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        fld_483,
        127,
        179,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg2 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    }
    else
    {
      nArg23 = nArg2;
    }
    v12 = (uint64_t)sub_4049F0(640.0, 170.0, (int)pThis_C2, 300, 1);  // 结果 = 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正
    fld_484 = sub_418DD0(*(uint32_t **)(this + 72), 0x4Eu);  // 调 sub_418DD0
    if ( fld_484 != 0 )  // 若 fld_484 != 0
      LOBYTE(fld_484) = (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_484 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
                      fld_484,
                      v12,
                      215,
                      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
                      1065353216,
                      1065353216,
                      0,
                      (nArg23 << 24) | 0xFFFFFF,
                      1333788672,
                      1333788672);
    if ( v12 == 170 )  // 若 v12 == 170
    {
      LOBYTE(fld_484) = pszArg3;
      if ( pszArg3 != 0 )  // 若 pszArg3 != 0
      {
        fld_484 = sub_418DD0(*(uint32_t **)(this + 72), 0x4Fu);  // 调 sub_418DD0
        if ( fld_484 != 0 )  // 若 fld_484 != 0
          LOBYTE(fld_484) = (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_484 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
                          fld_484,
                          170,
                          215,
                          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
                          1065353216,
                          1065353216,
                          0,
                          (nArg23 << 24) | 0xFFFFFF,
                          1333788672,
                          1333788672);
      }
    }
  }
  else
  {
    fld_484 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);  // 全局 dword_8F7C04 = 本机角色对象
    if ( fld_484 != 2 )  // 若 fld_484 != 2
    {
      nArg24 = nArg2;
      if ( nArg2 >= 90 )  // 若 nArg2 >= 90
        LOBYTE(nArg2) = 90;
      fld_485 = sub_418DD0(*(uint32_t **)(this + 72), 0x56u);  // 调 sub_418DD0
      if ( fld_485 != 0 )  // 若 fld_485 != 0
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_485 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
          fld_485,
          0,
          0,
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          1065353216,
          1065353216,
          0,
          ((uint8_t)nArg2 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      if ( *(uint32_t *)(this + 132) == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) )  // 全局 dword_8F7C04 = 本机角色对象
      {
        v16 = (uint64_t)sub_4049F0(640.0, 167.0, (int)pThis_C, 300, 1);  // 结果 = 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正
        fld_484 = sub_418DD0(*(uint32_t **)(this + 72), 0x4Eu);  // 调 sub_418DD0
        if ( fld_484 != 0 )  // 若 fld_484 != 0
          LOBYTE(fld_484) = (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_484 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
                          fld_484,
                          v16,
                          197,
                          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
                          1065353216,
                          1065353216,
                          0,
                          ((uint8_t)nArg24 << 24) | 0xFFFFFF,
                          1333788672,
                          1333788672);
        if ( v16 == 167 )  // 若 v16 == 167
        {
          LOBYTE(fld_484) = pszArg3;
          if ( pszArg3 != 0 )  // 若 pszArg3 != 0
          {
            fld_486 = sub_418DD0(*(uint32_t **)(this + 72), 0x4Fu);  // 调 sub_418DD0
            LOBYTE(fld_484) = sub_43B560(  // 绘制转发（vt+128）
                            167,
                            197,
                            fld_486,
                            1065353216,
                            1065353216,
                            0,
                            ((uint8_t)nArg24 << 24) | 0xFFFFFF,
                            1333788672,
                            1333788672);
          }
        }
      }
      else
      {
        fld_484 = sub_418DD0(*(uint32_t **)(this + 72), 0x54u);  // 调 sub_418DD0
        if ( fld_484 != 0 )  // 若 fld_484 != 0
          LOBYTE(fld_484) = (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_484 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
                          fld_484,
                          219,
                          193,
                          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
                          1065353216,
                          1065353216,
                          0,
                          ((uint8_t)nArg24 << 24) | 0xFFFFFF,
                          1333788672,
                          1333788672);
        if ( nArg24 == 255 )  // 若 nArg24 == 255
        {
          LOBYTE(fld_484) = pszArg3;
          if ( pszArg3 != 0 )  // 若 pszArg3 != 0
          {
            fld_487 = sub_418DD0(*(uint32_t **)(this + 72), 0x55u);  // 调 sub_418DD0
            LOBYTE(fld_484) = sub_43B560(219, 193, fld_487, 1065353216, 1065353216, 0, -1, 1333788672, 1333788672);  // 绘制转发（vt+128）
          }
        }
      }
    }
  }
  return fld_484;
}


// ------------------------------------------------------------
// 0x54DE80 sub_54DE80 —— 结算辅助（418DD0）
// ------------------------------------------------------------
// 大白话：结算辅助：418DD0。
int /*thiscall*/ sub_54DE80(int *this, int nArg2, uint8_t uArg3)  // 函数: 结算辅助（418DD0）
{
  int fld_e35; // eax
  int pObj; // eax
  int result; // eax

  fld_e35 = *(this + 35);  // fld_e35 = this+35
  if ( fld_e35 >= 30 )  // 若 fld_e35 >= 30
  {
    pObj = sub_418DD0(fld_e35 + 16);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj,
        0,
        0,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        (uArg3 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
  }
  result = sub_418DD0(*(this + 35));  // 调 sub_418DD0
  if ( result != 0 )  // 若 result != 0
    return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
             result,
             0,
             0,
             dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
             1065353216,
             1065353216,
             0,
             (uArg3 << 24) | 0xFFFFFF,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x54DF30 sub_54DF30 —— 13 行小辅助
// ------------------------------------------------------------
// 大白话：13 行小辅助（结算）。
int /*thiscall*/ sub_54DF30(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 13 行小辅助
{
  *(this + 43) = nArg2;  // this+172 = nArg2
  *(this + 44) = nArg3;  // this+176 = nArg3
  *(this + 45) = nArg4;  // this+180 = nArg4
  return nArg4;
}



// ------------------------------------------------------------
// 0x54DF60 sub_54DF60 —— 结算文字（699000 + 4049C0，107 行）
// ------------------------------------------------------------
// 大白话：结算文字：699000 时钟 + 4049C0 精灵（107 行，逐字浮现【推断】）。
int /*thiscall*/ sub_54DF60(int this)  // 函数: 结算文字（699000 + 4049C0，107 行）
{
  int v2; // edi
  int fld_AC; // ebx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  double v7; // st7
  double v8; // st6
  int fld_8; // eax
  int v10; // eax
  int64_t v11; // rax
  int fld_88; // eax
  double v13; // st7
  int pThis_C2; // ecx
  int v15; // eax
  int pThis_C; // ecx
  int v17; // eax
  int v19; // [esp-8h] [ebp-28h]
  int pThis_C3; // [esp-8h] [ebp-28h]
  int v21; // [esp-8h] [ebp-28h]
  float v22; // [esp+10h] [ebp-10h]
  float v23; // [esp+14h] [ebp-Ch]
  float v24; // [esp+18h] [ebp-8h]
  float v25; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04) + 52);  // 全局 dword_8F7C04 = 本机角色对象
  fld_AC = *(uint32_t *)(this + 172);  // fld_AC = this+172
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);  // 全局 dword_8F7C04 = 本机角色对象
  v5 = *(uint32_t *)dword_8F7C04;  // 全局 dword_8F7C04 = 本机角色对象
  v23 = *(float *)(v4 + 56);  // v23 = v4+56
  v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(v5 + 1032))(dword_8F7C04) + 60);  // 全局 dword_8F7C04 = 本机角色对象
  v7 = (double)(LODWORD(v23) - v6);
  v8 = (double)(v2 - v6);
  LODWORD(v25) = fld_AC - *(uint32_t *)(this + 176);  // this+176 附属对象向量 cap
  fld_8 = *(uint32_t *)(this + 8) - 10;  // this+8 物品 id
  v22 = (float)SLODWORD(v25);
  v25 = 1.0 / v7;
  v23 = 1.0 / v7 * v8;
  v24 = v25 * v22;
  if ( fld_8 == 0 )  // 若 fld_8 == 0
    return (uint64_t)(*(&v23 + (*(uint32_t *)(this + 136) != 0)) * 129.0);  // this+136 演出已播标志
  v10 = fld_8 - 1;
  if ( v10 == 0 )  // 若 v10 == 0
  {
    fld_88 = *(uint32_t *)(this + 136);  // fld_88 = this+136
    v13 = 0.0;
    if ( fld_88 == -1 )  // 若 fld_88 == -1
    {
      pThis_C = this + 12;  // this+12 物品类型号
      if ( *(uint8_t *)(this + 184) != 0 )  // 若 *(uint8_t *)(this + 184) != 0
      {
        v21 = sub_699000(pThis_C);  // 【clock_now(clk)】
        v13 = sub_4049C0(1.0, v24, v21, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      }
      else
      {
        v17 = sub_699000(pThis_C);  // 【clock_now(clk)】
        v13 = sub_4049C0(v23, 0.0, v17, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        if ( v13 <= 0.0 )  // 若 v13 <= 0.0
        {
          *(uint8_t *)(this + 184) = 1;  // this+184 = 1
          return (uint64_t)(v13 * 129.0);
        }
      }
    }
    else if ( fld_88 != 0 )  // 否则若 fld_88 != 0
    {
      if ( fld_88 == 1 )  // 若 fld_88 == 1
      {
        pThis_C2 = this + 12;  // this+12 物品类型号
        if ( *(uint8_t *)(this + 184) != 0 )  // 若 *(uint8_t *)(this + 184) != 0
        {
          v19 = sub_699000(pThis_C2);  // 【clock_now(clk)】
          v13 = sub_4049C0(0.0, v23, v19, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        }
        else
        {
          v15 = sub_699000(pThis_C2);  // 【clock_now(clk)】
          v13 = sub_4049C0(v24, 1.0, v15, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          if ( v13 >= 1.0 )  // 若 v13 >= 1.0
          {
            *(uint8_t *)(this + 184) = 1;  // this+184 = 1
            return (uint64_t)(v13 * 129.0);
          }
        }
      }
    }
    else
    {
      pThis_C3 = sub_699000(this + 12);  // 【clock_now(clk)】
      v13 = sub_4049C0(v23, v23, pThis_C3, 600);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    }
    return (uint64_t)(v13 * 129.0);
  }
  if ( v10 == 1 )  // 若 v10 == 1
    return (uint64_t)(v23 * 129.0);
  else
    LODWORD(v11) = 0;
  return v11;
}



// ------------------------------------------------------------
// 0x54E160 sub_54E160 —— 17 行小辅助
// ------------------------------------------------------------
// 大白话：17 行小辅助（结算）。
int /*thiscall*/ sub_54E160(uint32_t *this, int nArg2)  // 函数: 17 行小辅助
{
  int v3; // esi

  v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8));  // 全局 dword_8F852C = 角色/物品栏管理器
  (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 40))(  // 全局 dword_8F852C = 角色/物品栏管理器
    *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8),  // 全局 dword_8F852C = 角色/物品栏管理器
    nArg2);
  *(this + 37) = nArg2 - v3;  // this+148 = nArg2 - v3
  return off_77F3FC(aPvp_4, v3, nArg2);  // off_77F3FC（引擎日志输出函数）
}



// ------------------------------------------------------------
// 0x54E1B0 sub_54E1B0 —— 结算辅助 2（26 行）
// ------------------------------------------------------------
// 大白话：结算辅助 2：26 行。
uint32_t */*cdecl*/ sub_54E1B0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 结算辅助 2
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax
  uint32_t *v5; // edi
  int v6; // esi

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; v5[3] = v6 )  // 循环：result = uArg3; uArg12 != uArg2; v5[3] = v6
  {
    v5 = result;
    *result = *uArg12;  // *result 写入 *uArg12
    result[1] = uArg12[1];  // result[1] 写入 uArg12[1]
    result[2] = uArg12[2];  // result[2] 写入 uArg12[2]
    v6 = uArg12[3];
    uArg12 += 4;
    result += 4;
  }
  return result;
}



// ------------------------------------------------------------
// 0x54E1F0 sub_54E1F0 —— 结算 UI 构建（219 行：48F5A0/48F690 + 42A410/42A430 + 54DF60/488670/54DE80）
// ------------------------------------------------------------
// 大白话：结算 UI 构建：48F5A0/48F690 取数据 + 42A410/42A430 + 54DF60/488670/54DE80（219 行）。
int /*thiscall*/ sub_54E1F0(int *this, int nArg2)  // 函数: 结算 UI 构建（219 行：48F5A0/48F690 + 42A410/42A430 + 54DF60/488670/54DE80）
{
  int pObj10; // eax
  int pObj2; // eax
  int pObj7; // eax
  int pObj6; // eax
  char *v7; // eax
  int v8; // esi
  int pObj3; // eax
  int pObj5; // eax
  char *v11; // eax
  int v12; // eax
  int v13; // ebx
  int pObj9; // ebx
  int v15; // eax
  uint32_t *v16; // ecx
  int pObj; // eax
  int pObj8; // eax
  int result; // eax
  int pObj11; // eax
  int fld_e37; // [esp-4h] [ebp-88h]
  int fld_e36; // [esp-4h] [ebp-88h]
  uint8_t nArg22; // [esp+Ch] [ebp-78h]
  int pObj4; // [esp+Ch] [ebp-78h]
  char Buffer[112]; // [esp+10h] [ebp-74h] BYREF
  int dword_796E502; // [esp+80h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  nArg22 = nArg2;
  if ( nArg2 >= 150 )  // 若 nArg2 >= 150
    nArg22 = -106;
  pObj10 = sub_418DD0(35);  // 调 sub_418DD0
  if ( pObj10 != 0 )  // 若 pObj10 != 0
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj10 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj10,
      0,
      0,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      (nArg22 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  pObj2 = sub_418DD0(36);  // 调 sub_418DD0
  if ( pObj2 != 0 )  // 若 pObj2 != 0
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj2,
      0,
      0,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      ((uint8_t)nArg2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  pObj7 = sub_418DD0(39);  // 调 sub_418DD0
  if ( pObj7 != 0 )  // 若 pObj7 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj7 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj7,
      236,
      223,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      ((uint8_t)nArg2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  pObj6 = sub_418DD0(38);  // 调 sub_418DD0
  if ( pObj6 != 0 )  // 若 pObj6 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj6 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj6,
      235,
      222,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      ((uint8_t)nArg2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 19);  // 调用虚函数槽 +72
  fld_e37 = *(this + 37);  // fld_e37 = this+37
  v7 = sub_422E70(458);  // 调 sub_422E70
  sprintf(Buffer, v7, fld_e37);  // 调 sprintf 格式化
  v8 = ((uint8_t)nArg2 << 24) | 0xFFFFFF;
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 281, 232, v8, Buffer);  // 调用虚函数槽 +80
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
  pObj3 = sub_418DD0(37);  // 调 sub_418DD0
  if ( pObj3 != 0 )  // 若 pObj3 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj3,
      235,
      268,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      v8,
      1333788672,
      1333788672);
  pObj5 = sub_418DD0(38);  // 调 sub_418DD0
  if ( pObj5 != 0 )  // 若 pObj5 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj5,
      235,
      268,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      v8,
      1333788672,
      1333788672);
  (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 19);  // 调用虚函数槽 +72
  fld_e36 = *(this + 36);  // fld_e36 = this+36
  v11 = sub_422E70(459);  // 调 sub_422E70
  sprintf(Buffer, v11, fld_e36);  // 调 sprintf 格式化
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 282, 280, v8, Buffer);  // 调用虚函数槽 +80
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
  v12 = sub_48F5A0();  // 结果 = 自身座位下标查找（房间号比对）
  v13 = sub_48F690(v12);  // 结果 = 槽 id 解析·第二组（偏移 +10）
  if ( v13 != 0 && dword_8F7C04 != 0 )  // 全局 dword_8F7C04 = 本机角色对象
  {
    pObj4 = sub_42A410(v13);  // 结果 = 图标句柄取用（+116 槽）
    pObj9 = sub_42A430(v13);  // 结果 = 同构 ·0x42A410
    if ( pObj4 != 0 )  // 若 pObj4 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj4,
        228,
        305,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        v8,
        1333788672,
        1333788672);
    if ( pObj9 != 0 )  // 若 pObj9 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj9 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj9,
        228,
        305,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        v8,
        1333788672,
        1333788672);
    v15 = sub_54DF60(this);  // 结果 = 结算文字
    v16 = (uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
    *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0+48 = 0
    v16[13] = 0;
    v16[14] = v15 + 280;  // v16[14] 写入 v15 + 280
    v16[15] = 480;
    pObj = sub_418DD0(91);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj,
        281,
        307,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        v8,
        1333788672,
        1333788672);
    sub_488670(dword_79C0B0);  // 视口重置 640x480
  }
  if ( *(this + 33) == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) )  // 全局 dword_8F7C04 = 本机角色对象
    pObj8 = sub_418DD0(45);  // 调 sub_418DD0
  else
    pObj8 = sub_418DD0(44);  // 调 sub_418DD0
  if ( pObj8 != 0 )  // 若 pObj8 != 0
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj8 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj8,
      0,
      0,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      v8,
      1333788672,
      1333788672);
  result = *(this + 34);  // result = this+34
  if ( result == -1 )  // 若 result == -1
  {
    pObj11 = sub_418DD0(42);  // 调 sub_418DD0
  }
  else
  {
    if ( result != 1 )  // 若 result != 1
      return result;  // result=this+136 演出已播标志
    pObj11 = sub_418DD0(43);  // 调 sub_418DD0
  }
  if ( pObj11 != 0 )  // 若 pObj11 != 0
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj11 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj11,
      0,
      0,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      v8,
      1333788672,
      1333788672);
  return sub_54DE80(*(this + 35), nArg2);  // 结算辅助（418DD0）
}


// ------------------------------------------------------------
// 0x54E660 sub_54E660 —— 结算转发（54E1B0）
// ------------------------------------------------------------
// 大白话：结算转发：调 54E1B0。
uint32_t */*cdecl*/ sub_54E660(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 结算转发（54E1B0）
{
  return sub_54E1B0(uArg1, uArg2, uArg3);  // 结算辅助 2
}



// ------------------------------------------------------------
// 0x54E680 sub_54E680 —— 结算转发 2（602460）
// ------------------------------------------------------------
// 大白话：结算转发 2：调 602460。
uint32_t */*stdcall*/ sub_54E680(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 结算转发 2（602460）
{
  return sub_602460(uArg1, uArg2, uArg3);  // 16 字节批量拷贝
}



// ------------------------------------------------------------
// 0x54E6A0 sub_54E6A0 —— 结算徽章绘制（418DD0 + 491530/491630，50 行）
// ------------------------------------------------------------
// 大白话：结算徽章绘制：418DD0 + 491530/491630 批次（50 行）。
int /*thiscall*/ sub_54E6A0(void *this, int nArg2)  // 函数: 结算徽章绘制（418DD0 + 491530/491630，50 行）
{
  uint8_t nArg22; // bl
  int pObj; // eax
  uint8_t nArg23; // bl
  int pObj2; // eax
  float pThis_28; // [esp+14h] [ebp+8h]

  nArg22 = nArg2;
  if ( nArg2 >= 220 )  // 若 nArg2 >= 220
    nArg22 = -36;
  pObj = sub_418DD0(33);  // 调 sub_418DD0
  if ( pObj != 0 )  // 若 pObj != 0
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj,
      0,
      0,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      (nArg22 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  pThis_28 = (double)sub_699000((int)this + 40) * 0.000033333334;  // 【clock_now(clk)】
  sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
  nArg23 = nArg2;
  if ( nArg2 >= 120 )  // 若 nArg2 >= 120
    nArg23 = 120;
  pObj2 = sub_418DD0(1);  // 调 sub_418DD0
  if ( pObj2 != 0 )  // 若 pObj2 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, float, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj2,
      111,
      31,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      COERCE_FLOAT(LODWORD(pThis_28)),
      (nArg23 << 24) | 0xFFFFFF,
      1129447424,
      1129447424);
  return sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
}



// ------------------------------------------------------------
// 0x54E7B0 sub_54E7B0 —— PVP 结算主绘制（451 行：491530/491630 + 429830/48F620 + 42B340/42A410/42A430 + 69A110）
// ------------------------------------------------------------
// 大白话：PVP 结算主绘制：491530/491630 批次 + 429830/48F620 + 42B340/42A410/42A430 + 69A110（451 行）。
int /*thiscall*/ sub_54E7B0(uint32_t *this, int nArg2)  // 函数: PVP 结算主绘制（451 行：491530/491630 + 429830/48F620 + 42B340/42A410/42A430 + 69A110）
{
  int fld_e39; // eax
  int fld_e40; // edi
  int v4; // esi
  int pObj12; // eax
  int nArg22; // ebx
  int pObj6; // eax
  int v8; // eax
  int v9; // esi
  int pObj11; // eax
  int nArg2222; // ecx
  int result; // eax
  int pObj8; // eax
  int pObj16; // eax
  int fld_e392; // eax
  int fld_e3922; // edi
  int pObj; // esi
  int pObj15; // eax
  int pObj18; // eax
  int pObj20; // eax
  int pObj9; // eax
  int v22; // ecx
  int pObj13; // eax
  int v24; // eax
  int pObj17; // eax
  int pObj2; // eax
  int fld_e393; // eax
  int pObj19; // esi
  int pObj14; // eax
  int pObj10; // eax
  int pObj7; // eax
  int pObj3; // eax
  int pObj4; // eax
  int v34; // ecx
  int pObj5; // eax
  int v36; // edx
  int v37; // esi
  int v38; // edi
  bool v39; // cc
  int fld_e402; // [esp+10h] [ebp-2Ch]
  int i; // [esp+14h] [ebp-28h]
  uint8_t nArg224; // [esp+14h] [ebp-28h]
  uint8_t nArg225; // [esp+14h] [ebp-28h]
  int fld_e3932; // [esp+14h] [ebp-28h]
  int v45; // [esp+18h] [ebp-24h]
  int v46; // [esp+1Ch] [ebp-20h]
  int v47; // [esp+20h] [ebp-1Ch]
  int v48; // [esp+24h] [ebp-18h]
  int v49; // [esp+28h] [ebp-14h]
  int v50; // [esp+2Ch] [ebp-10h]
  int v51; // [esp+30h] [ebp-Ch]
  int v52; // [esp+34h] [ebp-8h]
  uint8_t nArg222; // [esp+44h] [ebp+8h]
  uint8_t nArg223; // [esp+44h] [ebp+8h]
  int v56; // [esp+44h] [ebp+8h]

  fld_e39 = *(this + 39);  // fld_e39 = this+39
  if ( fld_e39 != 0 )  // 若 fld_e39 != 0
    fld_e40 = (*(this + 40) - fld_e39) >> 4;  // this+40 物品状态附属标志
  else
    fld_e40 = 0;
  v4 = dword_7249C4[fld_e40];
  fld_e402 = fld_e40;
  pObj12 = sub_418DD0(12);  // 调 sub_418DD0
  nArg22 = nArg2;
  if ( pObj12 != 0 )  // 若 pObj12 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj12 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj12,
      269,
      v4 - 45,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      ((uint8_t)nArg2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  if ( nArg2 >= 150 )  // 若 nArg2 >= 150
    LOBYTE(nArg2) = -106;
  pObj6 = sub_418DD0(73);  // 调 sub_418DD0
  if ( pObj6 != 0 )  // 若 pObj6 != 0
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj6 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj6,
      127,
      v4,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      ((uint8_t)nArg2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  v8 = 0;
  v9 = v4 + 70;
  for ( i = 0; i < fld_e40 - 1; ++i )  // 循环：i = 0; i < fld_e40 - 1; ++i
  {
    if ( v8 == fld_e40 - 2 )  // 若 v8 == fld_e40 - 2
    {
      nArg222 = nArg22;
      if ( nArg22 >= 150 )  // 若 nArg22 >= 150
        nArg222 = -106;
      pObj11 = sub_418DD0(75);  // 调 sub_418DD0
      if ( pObj11 == 0 )  // 若 pObj11 == 0
        goto LABEL_21;  // 跳转 LABEL_21
      nArg2222 = nArg222;
    }
    else
    {
      nArg223 = nArg22;
      if ( nArg22 >= 150 )  // 若 nArg22 >= 150
        nArg223 = -106;
      pObj11 = sub_418DD0(74);  // 调 sub_418DD0
      if ( pObj11 == 0 )  // 若 pObj11 == 0
        goto LABEL_21;  // 跳转 LABEL_21
      nArg2222 = nArg223;
    }
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj11 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj11,
      127,
      v9,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1065353216,
      1065353216,
      0,
      (nArg2222 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
LABEL_21:
    v8 = i + 1;
    v9 += 43;
  }
  result = dword_7249C4[fld_e40];
  v52 = result;
  v45 = 0;
  if ( fld_e40 > 0 )  // 若 fld_e40 > 0
  {
    v46 = result + 13;
    v47 = result + 14;
    v56 = result + 26;
    v48 = result + 7;
    v50 = result + 10;
    v49 = result + 3;
    v51 = result + 21;
    while ( v45 == 0 )  // 当 v45 == 0 循环
    {
      sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      nArg224 = nArg22;
      if ( nArg22 >= 70 )  // 若 nArg22 >= 70
        nArg224 = 70;
      pObj8 = sub_418DD0(77);  // 调 sub_418DD0
      if ( pObj8 != 0 )  // 若 pObj8 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj8 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
          pObj8,
          141,
          v47,
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          1065353216,
          1065353216,
          0,
          (nArg224 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
      pObj16 = sub_418DD0(51);  // 调 sub_418DD0
      if ( pObj16 != 0 )  // 若 pObj16 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj16 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
          pObj16,
          447,
          v56,
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          1065353216,
          1065353216,
          0,
          ((uint8_t)nArg22 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      fld_e392 = sub_429830(*(uint16_t *)*(this + 39));  // 结果 = 表按键查找（uint16）
      fld_e3922 = fld_e392;
      if ( fld_e392 != 0 )  // 若 fld_e392 != 0
        pObj = *(uint32_t *)(fld_e392 + 196);  // pObj = fld_e392+196
      else
        pObj = 0;
      if ( fld_e392 != 0 && pObj != 0 )  // 若 fld_e392 != 0 && pObj != 0
      {
        if ( (uint8_t)sub_48F620(dword_99FEC0) != 0 )  // 对局中标志查询
        {
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj) != 0 )  // 虚槽+376 坐标同步包（type 37）
            pObj15 = sub_418DD0(88);  // 调 sub_418DD0
          else
            pObj15 = sub_418DD0(87);  // 调 sub_418DD0
        }
        else
        {
          pObj15 = sub_418DD0(59);  // 调 sub_418DD0
        }
        if ( pObj15 != 0 )  // 若 pObj15 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj15 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
            pObj15,
            206,
            v51,
            dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
            1065353216,
            1065353216,
            0,
            ((uint8_t)nArg22 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        pObj18 = sub_42B340(fld_e3922);  // 结果 = 虚拟角色惰性创建（0x294 字节）
        if ( pObj18 != 0 )  // 若 pObj18 != 0
        {
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)pObj18 + 384))(  // 虚槽+384 槽数组 getter（+348 起，越界返回 0）
            pObj18,
            216,
            v52 + 32,
            24,
            24,
            1065353216);
          pObj20 = sub_42A410(fld_e3922);  // 结果 = 图标句柄取用（+116 槽）
          if ( pObj20 != 0 )  // 若 pObj20 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj20 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
              pObj20,
              254,
              v56,
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              1065353216,
              1065353216,
              0,
              ((uint8_t)nArg22 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          pObj9 = sub_42A430(fld_e3922);  // 结果 = 同构 ·0x42A410
          if ( pObj9 != 0 )  // 若 pObj9 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj9 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
              pObj9,
              254,
              v56,
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              1065353216,
              1065353216,
              0,
              ((uint8_t)nArg22 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 19);  // 调用虚函数槽 +72
          if ( *(uint32_t *)(fld_e3922 + 40) < 0x10u )  // 若 *(uint32_t *)(fld_e3922 + 40) < 0x10u
            v22 = fld_e3922 + 20;
          else
            v22 = *(uint32_t *)(fld_e3922 + 20);  // v22 = fld_e3922+20
          (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
            dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
            256,
            v52 + 45,
            ((uint8_t)nArg22 << 24) | 0xFFFFFF,
            v22);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
        }
      }
      sub_69A110(405, v52 + 31, *(uint32_t *)(*(this + 39) + 4), nArg22);  // 调 sub_69A110
      pObj13 = sub_418DD0(71);  // 调 sub_418DD0
      if ( pObj13 != 0 )  // 若 pObj13 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj13 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
          pObj13,
          405,
          v52 + 30,
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          1065353216,
          1065353216,
          0,
          ((uint8_t)nArg22 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v24 = 70;
      v52 += 70;
LABEL_91:
      v50 += v24;  // v50 累加 v24
      v49 += v24;  // v49 累加 v24
      v51 += v24;  // v51 累加 v24
      v36 = v24 + v47;
      v37 = v24 + v56;
      v38 = v24 + v48;
      v46 += v24;  // v46 累加 v24
      result = v45 + 1;
      v39 = v45 + 1 < fld_e402;
      v48 = v38;
      v56 = v37;
      v47 = v36;
      ++v45;  // 自增v45
      if ( !v39 )  // 若 !v39
        return result;
    }
    sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    nArg225 = nArg22;
    if ( nArg22 >= 200 )  // 若 nArg22 >= 200
      nArg225 = -56;
    pObj17 = sub_418DD0(76);  // 调 sub_418DD0
    if ( pObj17 != 0 )  // 若 pObj17 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj17 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj17,
        127,
        v52,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        (nArg225 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
    pObj2 = sub_418DD0(v45 + 51);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj2,
        447,
        v52 + 12,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg22 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    fld_e393 = sub_429830(*(uint16_t *)(16 * v45 + *(this + 39)));  // 结果 = 表按键查找（uint16）
    fld_e3932 = fld_e393;
    if ( fld_e393 != 0 )  // 若 fld_e393 != 0
      pObj19 = *(uint32_t *)(fld_e393 + 196);  // pObj19 = fld_e393+196
    else
      pObj19 = 0;
    if ( fld_e393 == 0 || pObj19 == 0 )  // 若 fld_e393 == 0 || pObj19 == 0
    {
LABEL_88:
      sub_69A110(405, v47, *(uint32_t *)(16 * v45 + *(this + 39) + 4), nArg22);  // 调 sub_69A110
      pObj5 = sub_418DD0(71);  // 调 sub_418DD0
      if ( pObj5 != 0 )  // 若 pObj5 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
          pObj5,
          405,
          v46,
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          1065353216,
          1065353216,
          0,
          ((uint8_t)nArg22 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v24 = 43;
      v52 += 43;
      goto LABEL_91;  // 跳转 LABEL_91
    }
    if ( (uint8_t)sub_48F620(dword_99FEC0) != 0 )  // 对局中标志查询
    {
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj19 + 376))(pObj19) == *(this + 33) )  // this+33 职业数据脏位
      {
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj19 + 376))(pObj19) != 0 )  // 虚槽+376 坐标同步包（type 37）
          pObj14 = sub_418DD0(93);  // 调 sub_418DD0
        else
          pObj14 = sub_418DD0(92);  // 调 sub_418DD0
        if ( pObj14 != 0 )  // 若 pObj14 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj14 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
            pObj14,
            206,
            v49,
            dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
            1065353216,
            1065353216,
            0,
            ((uint8_t)nArg22 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
LABEL_79:
        pObj7 = sub_42B340(fld_e3932);  // 结果 = 虚拟角色惰性创建（0x294 字节）
        if ( pObj7 != 0 )  // 若 pObj7 != 0
        {
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)pObj7 + 384))(  // 虚槽+384 槽数组 getter（+348 起，越界返回 0）
            pObj7,
            216,
            v46,
            24,
            24,
            1065353216);
          pObj3 = sub_42A410(fld_e3932);  // 结果 = 图标句柄取用（+116 槽）
          if ( pObj3 != 0 )  // 若 pObj3 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
              pObj3,
              254,
              v48,
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              1065353216,
              1065353216,
              0,
              ((uint8_t)nArg22 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          pObj4 = sub_42A430(fld_e3932);  // 结果 = 同构 ·0x42A410
          if ( pObj4 != 0 )  // 若 pObj4 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
              pObj4,
              254,
              v48,
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              1065353216,
              1065353216,
              0,
              ((uint8_t)nArg22 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 19);  // 调用虚函数槽 +72
          if ( *(uint32_t *)(fld_e3932 + 40) < 0x10u )  // 若 *(uint32_t *)(fld_e3932 + 40) < 0x10u
            v34 = fld_e3932 + 20;
          else
            v34 = *(uint32_t *)(fld_e3932 + 20);  // v34 = fld_e3932+20
          (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
            dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
            256,
            v56,
            ((uint8_t)nArg22 << 24) | 0xFFFFFF,
            v34);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
        }
        goto LABEL_88;  // 跳转 LABEL_88
      }
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj19 + 376))(pObj19) != 0 )  // 虚槽+376 坐标同步包（type 37）
        pObj10 = sub_418DD0(90);  // 调 sub_418DD0
      else
        pObj10 = sub_418DD0(89);  // 调 sub_418DD0
    }
    else
    {
      pObj10 = sub_418DD0(60);  // 调 sub_418DD0
    }
    if ( pObj10 != 0 )  // 若 pObj10 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj10 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj10,
        213,
        v50,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg22 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    goto LABEL_79;  // 跳转 LABEL_79
  }
  return result;
}


// ------------------------------------------------------------
// 0x54F050 sub_54F050 —— 结算数字绘制（158 行：4049F0/4049C0 + 491530/418DD0/491630）
// ------------------------------------------------------------
// 大白话：结算数字绘制：4049F0/4049C0 数字精灵 + 491530/418DD0/491630（158 行）。
int /*userpurge*/ sub_54F050@<eax>(uint32_t *pArg1@<ecx>, double fArg2@<st0>, uint8_t uArg3)  // 函数: 结算数字绘制（158 行：4049F0/4049C0 + 491530/418DD0/491630）
{
  uint32_t *pArg12; // ebx
  int v4; // ecx
  int v5; // edi
  unsigned int v6; // esi
  int result; // eax
  int v8; // edx
  int v9; // ecx
  float fArg222; // edi
  int v11; // edi
  int v12; // ebx
  int pObj; // eax
  int pObj3; // eax
  int v15; // eax
  int v16; // edi
  int v17; // ebx
  int pObj2; // eax
  int pObj4; // eax
  int v20; // edx
  bool v21; // cc
  int v22; // [esp+Ch] [ebp-20h]
  uint32_t *pArg122; // [esp+10h] [ebp-1Ch]
  int v24; // [esp+14h] [ebp-18h]
  int v25; // [esp+18h] [ebp-14h]
  int v26; // [esp+1Ch] [ebp-10h]
  int v27; // [esp+20h] [ebp-Ch]
  int v28; // [esp+24h] [ebp-8h]
  float fArg22; // [esp+28h] [ebp-4h]

  pArg12 = pArg1;
  v4 = pArg1[39];
  pArg122 = pArg12;
  if ( v4 != 0 )  // 若 v4 != 0
    v24 = (pArg12[40] - v4) >> 4;
  else
    v24 = 0;
  v5 = dword_7249C4[v24];
  v6 = sub_699000((int)(pArg12 + 3));  // 【clock_now(clk)】
  sub_4049F0(3.0, 0.94999999, v6, 200, 1);  // 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正
  result = 0;
  v22 = 0;
  if ( v24 > 0 )  // 若 v24 > 0
  {
    v8 = v5 - 57;
    v25 = v5 + 5;
    v9 = v5 + 22;
    v28 = v5 - 44;
    fArg22 = fArg2;
    fArg222 = fArg22;
    v26 = v8;
    v27 = v9;
    do
    {
      if ( result != 0 )  // 若 result != 0
      {
        if ( pArg12[33] == *(uint32_t *)(16 * result + pArg12[39] + 12) )  // 若 pArg12[33] == *(uint32_t *)(16 * result + pArg12[39] + 12)
        {
          if ( v6 >= 0xC8 )  // 若 v6 >= 0xC8
          {
            v6 -= 200;
            v16 = (uint64_t)sub_4049C0(87.0, 93.0, v6, 200);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            v17 = (uint64_t)sub_4049C0(255.0, 0.0, v6, 200);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
            pObj2 = sub_418DD0(v16);  // 调 sub_418DD0
            if ( pObj2 != 0 )  // 若 pObj2 != 0
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
                pObj2,
                98,
                v26,
                dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
                1065353216,
                1065353216,
                0,
                ((uint8_t)v17 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
            sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
            fArg222 = 1.0;
            pArg12 = pArg122;
          }
          pObj4 = sub_418DD0(95);  // 调 sub_418DD0
          if ( pObj4 != 0 )  // 若 pObj4 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int, float, float, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 156))(  // 虚槽+156 与目标 x/y 距离绝对值
              pObj4,
              156,
              v25,
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              COERCE_FLOAT(LODWORD(fArg222)),
              COERCE_FLOAT(LODWORD(fArg222)),
              0,
              (uArg3 << 24) | 0xFFFFFF,
              1101529088,
              1100480512);
        }
        v15 = 43;
      }
      else
      {
        if ( pArg12[33] == *(uint32_t *)(pArg12[39] + 12) )  // 若 pArg12[33] == *(uint32_t *)(pArg12[39] + 12)
        {
          if ( v6 >= 0xC8 )  // 若 v6 >= 0xC8
          {
            v6 -= 200;
            v11 = (uint64_t)sub_4049C0(87.0, 93.0, v6, 200);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            v12 = (uint64_t)sub_4049C0(255.0, 0.0, v6, 200);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
            pObj = sub_418DD0(v11);  // 调 sub_418DD0
            if ( pObj != 0 )  // 若 pObj != 0
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
                pObj,
                98,
                v28,
                dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
                1065353216,
                1065353216,
                0,
                ((uint8_t)v12 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
            sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
            fArg222 = 1.0;
            pArg12 = pArg122;
          }
          pObj3 = sub_418DD0(95);  // 调 sub_418DD0
          if ( pObj3 != 0 )  // 若 pObj3 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int, float, float, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 156))(  // 虚槽+156 与目标 x/y 距离绝对值
              pObj3,
              156,
              v27,
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              COERCE_FLOAT(LODWORD(fArg222)),
              COERCE_FLOAT(LODWORD(fArg222)),
              0,
              (uArg3 << 24) | 0xFFFFFF,
              1101529088,
              1100480512);
        }
        v15 = 70;
      }
      v27 += v15;  // v27 累加 v15
      v28 += v15;  // v28 累加 v15
      v20 = v15 + v26;
      v25 += v15;  // v25 累加 v15
      result = v22 + 1;
      v21 = v22 + 1 < v24;
      v26 = v20;
      ++v22;  // 自增v22
    }
    while ( v21 );  // 当 v21 循环
  }
  return result;
}


// ------------------------------------------------------------
// 0x54F370 sub_54F370 —— 结算文本（418DD0，83 行）
// ------------------------------------------------------------
// 大白话：结算文本：418DD0（83 行）。
int /*thiscall*/ sub_54F370(uint32_t *this, uint8_t uArg2)  // 函数: 结算文本（418DD0，83 行）
{
  int fld_e39; // eax
  int result; // eax
  int v5; // ecx
  int v6; // edi
  int pObj2; // eax
  int v8; // eax
  int pObj; // eax
  int v10; // [esp+4h] [ebp-Ch]
  int fld_e40; // [esp+8h] [ebp-8h]
  int v12; // [esp+Ch] [ebp-4h]

  fld_e39 = *(this + 39);  // fld_e39 = this+39
  if ( fld_e39 != 0 )  // 若 fld_e39 != 0
    fld_e40 = (*(this + 40) - fld_e39) >> 4;  // this+40 物品状态附属标志
  else
    fld_e40 = 0;
  result = dword_7249C4[fld_e40];
  v5 = 0;
  v10 = 0;
  if ( fld_e40 > 0 )  // 若 fld_e40 > 0
  {
    v12 = result + 5;
    v6 = result + 22;
    do
    {
      if ( v5 != 0 )  // 若 v5 != 0
      {
        if ( *(this + 33) == *(uint32_t *)(16 * v5 + *(this + 39) + 12) )  // 若 *(this + 33) == *(uint32_t *)(16 * v5 + *(this + 39) + 12)
        {
          pObj = sub_418DD0(95);  // 调 sub_418DD0
          if ( pObj != 0 )  // 若 pObj != 0
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
              pObj,
              156,
              v12,
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              1065353216,
              1065353216,
              0,
              (uArg2 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
        }
        v6 += 43;
        v8 = v12 + 43;
      }
      else
      {
        if ( *(this + 33) == *(uint32_t *)(*(this + 39) + 12) )  // 若 *(this + 33) == *(uint32_t *)(*(this + 39) + 12)
        {
          pObj2 = sub_418DD0(95);  // 调 sub_418DD0
          if ( pObj2 != 0 )  // 若 pObj2 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
              pObj2,
              156,
              v6,
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              1065353216,
              1065353216,
              0,
              (uArg2 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
        }
        v6 += 70;
        v8 = v12 + 70;
      }
      v12 = v8;
      result = fld_e40;
      v5 = ++v10;
    }
    while ( v10 < fld_e40 );  // 当 v10 < fld_e40 循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x54F4C0 sub_54F4C0 —— 结算事件复位（698F90）
// ------------------------------------------------------------
// 大白话：结算事件复位：698F90。
void /*thiscall*/ sub_54F4C0(int this)  // 函数: 结算事件复位（698F90）
{
  int pThis_28; // ecx

  pThis_28 = this + 40;  // this+40 物品状态附属标志
  *(uint32_t *)(this + 132) = -1;  // this+132 = -1
  *(uint32_t *)(this + 136) = 0;  // this+136 = 0
  *(uint32_t *)(this + 140) = 0;  // this+140 = 0
  *(uint32_t *)(this + 144) = 0;  // this+144 = 0
  *(uint8_t *)(pThis_28 + 13) = 0;  // pThis_28+13 = 0
  *(uint8_t *)(pThis_28 + 14) = 0;  // pThis_28+14 = 0
  sub_698F90(pThis_28, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( *(uint32_t *)(this + 156) != 0 )  // 若 *(uint32_t *)(this + 156) != 0
    j__free(*(void **)(this + 156));  // 调 j__free
  *(uint32_t *)(this + 156) = 0;  // this+156 = 0
  *(uint32_t *)(this + 160) = 0;  // this+160 = 0
  *(uint32_t *)(this + 164) = 0;  // this+164 = 0
  *(uint8_t *)(this + 184) = 0;  // this+184 = 0
  *(uint32_t *)(this + 168) = -1;  // this+168 = -1
}



// ------------------------------------------------------------
// 0x54F530 sub_54F530 —— 转发 54F4C0
// ------------------------------------------------------------
// 大白话：转发 54F4C0。
void /*thiscall*/ sub_54F530(int this)  // 函数: 转发 54F4C0
{
  *(uint32_t *)(this + 128) = 0;  // this+128 = 0
  sub_54F4C0(this);  // 结算事件复位（698F90）
}



// ------------------------------------------------------------
// 0x54F540 sub_54F540 —— 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432EE0/65DC70/432EA0）
// ------------------------------------------------------------
// 大白话：结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432EE0/65DC70/432EA0）。
uint8_t */*thiscall*/ sub_54F540(uint32_t *this, int nArg2)  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
{
  int pThis_3; // ecx
  uint8_t *result; // eax
  int i; // esi
  int fld_e2; // esi

  pThis_3 = (int)(this + 3);
  *(this + 2) = nArg2;  // this+8 = nArg2
  *(uint8_t *)(pThis_3 + 13) = 0;  // pThis_3+13 = 0
  *(uint8_t *)(pThis_3 + 14) = 0;  // pThis_3+14 = 0
  sub_698F90(pThis_3, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( *(this + 2) != 0 )  // 若 *(this + 2) != 0
  {
    if ( nArg2 == 1 )  // 若 nArg2 == 1
    {
      *(uint8_t *)(*(this + 17) + 16) = 0;  // this+17 激活/可命中标志
      for ( i = 0; i < 4; ++i )  // 循环：i = 0; i < 4; ++i
        result = (uint8_t *)sub_432EE0(i);  // 结果 = 音效 TAG 查询包装
    }
    else
    {
      if ( *(uint8_t *)(*(this + 17) + 16) == 0 )  // 若 *(uint8_t *)(*(this + 17) + 16) == 0
      {
        sub_65DC70(lpCriticalSection);  // FSOUND 全停：50 个 48B 通道槽逐个 sub_65D8B0 停止，再摘 +256
        sub_432EA0("M_RESULT", -1, 0, 0);  // 字符串 “M_RESULT”
      }
      result = (uint8_t *)*(this + 17);  // this+17 激活/可命中标志
      result[16] = 1;
      fld_e2 = *(this + 2);  // fld_e2 = this+2
      if ( fld_e2 == 2 )  // 若 fld_e2 == 2
      {
        return sub_432EA0("RESULT_COME", -1, 0, 0);  // 字符串 “RESULT_COME”
      }
      else if ( fld_e2 == 6 )  // 否则若 fld_e2 == 6
      {
        return sub_432EA0("MAP_APPEAR", -1, 0, 0);  // 字符串 “MAP_APPEAR”
      }
    }
  }
  else
  {
    sub_54F4C0((int)this);  // 结算事件复位（698F90）
    result = (uint8_t *)*(this + 17);  // this+17 激活/可命中标志
    result[16] = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x54F610 sub_54F610 —— PVP 结算窗口入队实现（44CAB0/602460 + 4BF320/453C20/504650/4BF340，121 行）
// ------------------------------------------------------------
// 大白话：PVP 结算窗口入队实现：44CAB0/602460 + 4BF320/453C20/504650/4BF340（121 行）。
unsigned int /*thiscall*/ sub_54F610(int this, int pArg2, unsigned int uArg3, uint32_t *Block)  // 函数: PVP 结算窗口入队实现（44CAB0/602460 + 4BF320/453C20/504650/4BF340，121 行）
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
  v26[0] = *Block;  // v26[0] 写入 *Block
  v6 = Block[2];
  v26[1] = v5;
  v26[3] = Block[3];  // v26[3] 写入 Block[3]
  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  v26[4] = &v25;
  v26[2] = v6;
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    result = (*(uint32_t *)(this + 12) - fld_4) >> 4;  // this+12 物品类型号
  else
    result = 0;
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 != 0
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8 物品 id
    else
      fld_8 = 0;
    if ( 0xFFFFFFF - fld_8 < uArg3 )  // 若 0xFFFFFFF - fld_8 < uArg3
      sub_44CAB0(this);  // vector 超长抛 std::length_error
    if ( fld_4 != 0 )  // 若 fld_4 != 0
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8 物品 id
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )  // 若 result >= uArg3 + fld_82
    {
      fld_83 = *(char **)(this + 8);  // this+8 物品 id
      Blockb = fld_83;  // fld_83=this+8 物品 id
      if ( (int)&fld_83[-pArg2] >> 4 >= uArg3 )  // 若 (int)&fld_83[-pArg2] >> 4 >= uArg3
      {
        v21 = &fld_83[-16 * uArg3];
        *(uint32_t *)(this + 8) = sub_602460(v21, fld_83, fld_83);  // 16 字节批量拷贝
        sub_4BF320(pArg2, v21, Blockb);  // 转发壳
        return sub_453C20(pArg2, pArg2 + 16 * uArg3, v26);  // 16 字节元素区间填充
      }
      else
      {
        sub_602460(pArg2, fld_83, pArg2 + 16 * uArg3);  // 16 字节批量拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 4);  // this+8 物品 id
        fld_85 = *(uint32_t *)(this + 8);  // fld_85 = this+8
        v27 = 2;
        sub_504650(fld_85, fld_84, v26);  // 调 sub_504650
        fld_86 = 16 * uArg3 + *(uint32_t *)(this + 8);  // this+8 物品 id
        *(uint32_t *)(this + 8) = fld_86;  // this+8 = fld_86
        return sub_453C20(pArg2, fld_86 - 16 * uArg3, v26);  // 16 字节元素区间填充
      }
    }
    else
    {
      if ( 0xFFFFFFF - (result >> 1) >= result )  // 若 0xFFFFFFF - (result >> 1) >= result
        v12 = (result >> 1) + result;
      else
        v12 = 0;
      if ( fld_4 != 0 )  // 若 fld_4 != 0
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8 物品 id
      else
        fld_87 = 0;
      if ( v12 < uArg3 + fld_87 )  // 若 v12 < uArg3 + fld_87
      {
        if ( fld_4 != 0 )  // 若 fld_4 != 0
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8 物品 id
        else
          fld_88 = 0;
        v12 = uArg3 + fld_88;
      }
      v28 = 16 * v12;
      Blocka = (char *)operator new(16 * v12);
      fld_42 = *(uint32_t *)(this + 4);  // fld_42 = this+4
      v27 = 0;
      v15 = sub_602460(fld_42, pArg2, Blocka);  // 结果 = 16 字节批量拷贝
      sub_4BF340(v15, uArg3, v26);  // 16 字节元素填充
      sub_602460(pArg2, *(uint32_t *)(this + 8), 16 * uArg3 + v15);  // 16 字节批量拷贝
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = this+4
      if ( fld_43 != 0 )  // 若 fld_43 != 0
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 4;  // this+8 物品 id
      else
        fld_89 = 0;
      v18 = fld_89 + uArg3;
      if ( fld_43 != 0 )  // 若 fld_43 != 0
        j__free(*(void **)(this + 4));  // 调 j__free
      *(uint32_t *)(this + 12) = &Blocka[v28];  // this+12 = &Blocka[v28]
      *(uint32_t *)(this + 8) = &Blocka[16 * v18];  // this+8 = &Blocka[16 * v18]
      *(uint32_t *)(this + 4) = Blocka;  // this+4 = Blocka
      return (unsigned int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x54F870 sub_54F870 —— 结算触发（426BD0/423B30 + 54F540）
// ------------------------------------------------------------
// 大白话：结算触发：426BD0/423B30 + 54F540。
uint8_t */*thiscall*/ sub_54F870(int this, void *Block)  // 结算触发（426BD0/423B30 + 54F540）
{
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  uint8_t *pMem2; // eax
  uint8_t *fld_48; // eax

  *(uint32_t *)(this + 4) = Block;  // this+4 = Block
  *(uint32_t *)(this + 72) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 132);  // this+72 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x68u);  // 堆分配 104 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v4 = sub_426BD0(pMem);  // 结果 = nengine::IControl 构造
  else
    v4 = nullptr;  // v4 = nullptr 空指针
  *(uint32_t *)(this + 68) = v4;  // this+68 = v4
  *((uint32_t *)v4 + 7) = 640;
  *((uint32_t *)v4 + 8) = 480;
  *(uint32_t *)(*(uint32_t *)(this + 68) + 68) = this;  // this+68 角色数（begin/end 差 >>2；>=8 …
  *(uint8_t *)(this + 76) = 0;  // this+76 = 0
  *(uint8_t *)(this + 77) = 0;  // this+77 = 0
  *(uint8_t *)(this + 78) = 0;  // this+78 = 0
  *(uint8_t *)(this + 79) = 0;  // this+79 = 0
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  *(uint32_t *)(this + 92) = 6;  // this+92 = 6
  *(uint32_t *)(this + 96) = 12;  // this+96 = 12
  *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  *(uint32_t *)(this + 104) = 1600;  // this+104 = 1600
  *(uint32_t *)(this + 108) = 0;  // this+108 = 0
  *(uint32_t *)(this + 112) = 0;  // this+112 = 0
  *(uint32_t *)(this + 116) = 0;  // this+116 = 0
  *(uint32_t *)(this + 120) = 0;  // this+120 = 0
  *(uint32_t *)(this + 124) = 0;  // this+124 = 0
  *(uint32_t *)(this + 124) = dword_99FCCC;  // this+124 = dword_99FCCC
  *(uint32_t *)(this + 104) = 180;  // this+104 = 180
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  *(uint32_t *)(this + 80) = -16777216;  // this+80 = -16777216
  pMem2 = operator new(0x2Cu);  // 堆分配 44 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_48 = sub_423B30(pMem2, dword_79C0B0, *(uint32_t *)(this + 72), 60, 7);  // 结果 = CNNumberSet 构造
  else
    fld_48 = nullptr;  // fld_48 = nullptr 空指针
  *(uint32_t *)(this + 128) = fld_48;  // this+128 = fld_48
  *((uint32_t *)fld_48 + 10) = -3;
  *(uint32_t *)(*(uint32_t *)(this + 128) + 36) = 2;  // this+128 第 2 组·+1208 增量子倍率
  *(uint8_t *)(*(uint32_t *)(this + 128) + 24) = 0;  // this+128 第 2 组·+1208 增量子倍率
  return sub_54F540((uint32_t *)this, 0);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
}



// ------------------------------------------------------------
// 0x54F9B0 sub_54F9B0 —— 结算触发 2（699000 + 54F540）
// ------------------------------------------------------------
// 大白话：结算触发 2：699000 时钟 + 54F540。
int /*thiscall*/ sub_54F9B0(int *this)  // 函数: 结算触发 2（699000 + 54F540）
{
  int result; // eax

  result = *(this + 2);  // result = this+2
  if ( result != 0 && --result == 0 )  // 若 result != 0 && --result == 0
  {
    result = sub_699000((int)(this + 3));  // 【clock_now(clk)】
    if ( result >= 2000 )  // 若 result >= 2000
      return (int)sub_54F540(this, *(this + 2) + 1);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
  }
  return result;  // result=this+8 物品 id
}



// ------------------------------------------------------------
// 0x54F9E0 CNRDPVPResult__vmt0 —— CNRDPVPResult__vmt0 构造（160 行：54DA50 背景 + 54F540 事件 + 54E6A0/54E7B0/54F050/54F370/54E1F0 结算件；标签 VICTORY_UP_LOOP/DEFEAT_DOWN_LOOP/RANK_UP/RESULT_CHARACTER）
// ------------------------------------------------------------
// 大白话：PVP 结算窗（CNRDPVPResult）构造：54DA50 背景 + 54F540 事件 +
// 54E6A0/54E7B0/54F050/54F370/54E1F0 结算件；动画标签
// VICTORY_UP_LOOP/DEFEAT_DOWN_LOOP/RANK_UP/RESULT_CHARACTER。
int /*userpurge*/ sub_54F9E0@<eax>(uint32_t *pArg1@<ecx>, double fArg2@<st0>, int nArg3)  // 函数: CNRDPVPResult__vmt0 构造（160 行：54DA50 背景 + 54F540 事件 + 54E6A0/54E7B0/54F050/54F370/54E1F0 结算件；标签 VICTORY_UP_LOOP/DEFEAT_DOWN_LOOP/RANK_UP/RESULT_CHARACTER）
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

  result = nArg3;  // result=this+8 物品 id
  if ( nArg3 == pArg1[17] )  // 若 nArg3 == pArg1[17]
  {
    if ( pArg1[2] == 2 )  // 若 pArg1[2] == 2
    {
      v5 = sub_699000((int)(pArg1 + 3));  // 【clock_now(clk)】
      fArg2 = sub_4049C0(0.0, 255.0, v5, 180);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      sub_54DA50((uint64_t)fArg2, 1);  // PVP 结算背景绘制
      if ( pArg1[2] == 2 && sub_699000((int)(pArg1 + 3)) >= 350 )  // 【clock_now(clk)】
        return sub_54F540(pArg1[2] + 1);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
    }
    if ( pArg1[2] == 3 )  // 若 pArg1[2] == 3
    {
      sub_54DA50(255, 0);  // PVP 结算背景绘制
      if ( pArg1[2] == 3 && sub_699000((int)(pArg1 + 3)) >= 1500 )  // 【clock_now(clk)】
        return sub_54F540(pArg1[2] + 1);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
    }
    if ( pArg1[2] == 4 )  // 若 pArg1[2] == 4
    {
      v6 = sub_699000((int)(pArg1 + 3));  // 【clock_now(clk)】
      fArg2 = sub_4049C0(255.0, 0.0, v6, 200);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      sub_54DA50((uint64_t)fArg2, 0);  // PVP 结算背景绘制
      if ( pArg1[2] == 4 && sub_699000((int)(pArg1 + 3)) >= 300 )  // 【clock_now(clk)】
        return sub_54F540(pArg1[2] + 1);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
    }
    v7 = pArg1[2];
    if ( v7 >= 5 )  // 若 v7 >= 5
    {
      LODWORD(v8) = 255;
      if ( v7 == 5 )  // 若 v7 == 5
      {
        v9 = sub_699000((int)(pArg1 + 3));  // 【clock_now(clk)】
        fArg2 = sub_4049C0(0.0, 255.0, v9, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        v8 = (uint64_t)fArg2;
      }
      else if ( v7 == 12 )  // 否则若 v7 == 12
      {
        v10 = sub_699000((int)(pArg1 + 3));  // 【clock_now(clk)】
        LODWORD(v8) = sub_423A80(255, 0, v10, 250);  // 同上 int 版（FTOL 截断）
      }
      sub_54E6A0(pArg1, v8);  // 结算徽章绘制
      if ( pArg1[2] == 5 && sub_699000((int)(pArg1 + 3)) >= 500 )  // 【clock_now(clk)】
      {
        v11 = pArg1[39];
        if ( v11 != 0 && (pArg1[40] - v11) >> 4 != 0 )  // 若 v11 != 0 && (pArg1[40] - v11) >> 4 != 0
          return sub_54F540(pArg1[2] + 1);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
        return sub_54F540(0);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
      }
    }
    if ( pArg1[2] == 6 )  // 若 pArg1[2] == 6
    {
      v12 = sub_699000((int)(pArg1 + 3));  // 【clock_now(clk)】
      fArg2 = sub_4049C0(0.0, 255.0, v12, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      sub_54E7B0(pArg1, (uint64_t)fArg2);  // PVP 结算主绘制
      if ( pArg1[2] == 6 && sub_699000((int)(pArg1 + 3)) >= 800 )  // 【clock_now(clk)】
        return sub_54F540(pArg1[2] + 1);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
    }
    if ( pArg1[2] == 7 )  // 若 pArg1[2] == 7
    {
      sub_54E7B0(pArg1, 255);  // PVP 结算主绘制
      sub_54F050(pArg1, fArg2, 0xFFu);  // 结算数字绘制
      if ( pArg1[2] == 7 && sub_699000((int)(pArg1 + 3)) >= 400 )  // 【clock_now(clk)】
      {
        sub_432EA0("RESULT_CHARACTER", -1, 0, 0);  // 字符串 “RESULT_CHARACTER”
        return sub_54F540(pArg1[2] + 1);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
      }
    }
    if ( pArg1[2] == 8 )  // 若 pArg1[2] == 8
    {
      sub_54E7B0(pArg1, 255);  // PVP 结算主绘制
      sub_54F370(255);  // 结算文本
      v13 = 4000;
      if ( dword_8F7C04 != 0 && *(uint8_t *)(dword_8F7C04 + 8052) != 0 )  // 全局 dword_8F7C04 = 本机角色对象
        v13 = 10000;
      if ( pArg1[2] == 8 && sub_699000((int)(pArg1 + 3)) >= v13 )  // 【clock_now(clk)】
      {
        if ( dword_8F7C04 == 0 || *(uint8_t *)(dword_8F7C04 + 8052) == 0 )  // 全局 dword_8F7C04 = 本机角色对象
          return sub_54F540(pArg1[2] + 1);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
        return sub_54F540(0);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
      }
    }
    if ( pArg1[2] == 9 )  // 若 pArg1[2] == 9
    {
      v14 = sub_699000((int)(pArg1 + 3));  // 【clock_now(clk)】
      v15 = (uint64_t)sub_4049C0(255.0, 0.0, v14, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      sub_54E7B0(pArg1, v15);  // PVP 结算主绘制
      sub_54F370(v15);  // 结算文本
      if ( pArg1[2] == 9 && sub_699000((int)(pArg1 + 3)) >= 500 )  // 【clock_now(clk)】
        return sub_54F540(pArg1[2] + 1);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
    }
    if ( pArg1[2] == 10
      && (v16 = sub_699000((int)(pArg1 + 3)),  // 【clock_now(clk)】
          v17 = sub_4049C0(0.0, 255.0, v16, 500),  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          sub_54E1F0((uint64_t)v17),  // 结算 UI 构建
          pArg1[2] == 10)
      && sub_699000((int)(pArg1 + 3)) >= 500 )  // 【clock_now(clk)】
    {
      sub_54F540(pArg1[2] + 1);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
      result = pArg1[36];
      if ( result <= 0 )  // 若 result <= 0
      {
        if ( result < 0 )  // 若 result < 0
          return (int)sub_432EA0("DEFEAT_DOWN_LOOP", -1, 0, 0);  // 字符串 “DEFEAT_DOWN_LOOP”
      }
      else
      {
        if ( pArg1[34] != 0 )  // 若 pArg1[34] != 0
          sub_432EA0("RANK_UP", -1, 0, 0);  // 字符串 “RANK_UP”
        return (int)sub_432EA0("VICTORY_UP_LOOP", -1, 0, 0);  // 字符串 “VICTORY_UP_LOOP”
      }
    }
    else
    {
      if ( pArg1[2] == 11 )  // 若 pArg1[2] == 11
      {
        sub_54E1F0(255);  // 结算 UI 构建
        if ( pArg1[2] == 11 && sub_699000((int)(pArg1 + 3)) >= 4000 )  // 【clock_now(clk)】
          return sub_54F540(pArg1[2] + 1);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
      }
      result = pArg1[2];
      if ( result >= 12 )  // 若 result >= 12
      {
        v18 = sub_699000((int)(pArg1 + 3));  // 【clock_now(clk)】
        v19 = sub_4049C0(255.0, 0.0, v18, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        result = sub_54E1F0((uint64_t)v19);  // 结果 = 结算 UI 构建
        if ( pArg1[2] == 12 )  // 若 pArg1[2] == 12
        {
          result = sub_699000((int)(pArg1 + 3));  // 【clock_now(clk)】
          if ( result >= 500 )  // 若 result >= 500
            return sub_54F540(0);  // 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432E
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x54FE50 sub_54FE50 —— 结算收尾（54E1B0 + 44CF50 + 54E680/54E660/602460）
// ------------------------------------------------------------
// 大白话：结算收尾：54E1B0 + 44CF50 + 54E680/54E660/602460 清理退场。
int /*thiscall*/ sub_54FE50(int this, int pArg2)  // 函数: 结算收尾（54E1B0 + 44CF50 + 54E680/54E660/602460）
{
  uint32_t *v3; // ebx
  unsigned int v4; // eax
  uint32_t *fld_4; // ecx
  unsigned int fld_8; // edx
  int v8; // eax
  int fld_42; // edi
  unsigned int fld_C; // edx
  int fld_82; // eax
  uint32_t *v12; // ebx
  int v13; // ecx
  unsigned int v14; // eax

  if ( this == pArg2 )  // 若 this == pArg2
    return this;  // 返回自身指针
  v3 = *(uint32_t **)(pArg2 + 4);
  if ( v3 == nullptr || (v4 = (*(uint32_t *)(pArg2 + 8) - (int)v3) >> 4) == 0 )  // 若 v3 == nullptr || (v4 = (*(uint32_t *)(pArg2 + 8) - (int)v3) >>..
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // 若 *(uint32_t *)(this + 4) != 0
      j__free(*(void **)(this + 4));  // 调 j__free
    *(uint32_t *)(this + 4) = 0;  // this+4 = 0
    *(uint32_t *)(this + 8) = 0;  // this+8 = 0
    *(uint32_t *)(this + 12) = 0;  // this+12 = 0
    return this;  // 返回自身指针
  }
  fld_4 = *(uint32_t **)(this + 4);  // this+4 宿主对象
  if ( fld_4 != nullptr )  // 若 fld_4 非空
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 4;  // this+8 物品 id
  else
    fld_8 = 0;
  if ( v4 <= fld_8 )  // 若 v4 <= fld_8
  {
    sub_54E1B0(v3, *(uint32_t **)(pArg2 + 8), fld_4);  // 结算辅助 2
    v8 = *(uint32_t *)(pArg2 + 4);  // v8 = pArg2+4
    if ( v8 != 0 )  // 若 v8 != 0
      fld_42 = *(uint32_t *)(this + 4) + 16 * ((*(uint32_t *)(pArg2 + 8) - v8) >> 4);  // this+4 宿主对象
    else
      fld_42 = *(uint32_t *)(this + 4);  // fld_42 = this+4
    *(uint32_t *)(this + 8) = fld_42;  // this+8 = fld_42
    return this;  // 返回自身指针
  }
  if ( fld_4 != nullptr )  // 若 fld_4 非空
    fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) >> 4;  // this+12 物品类型号
  else
    fld_C = 0;
  if ( v4 > fld_C )  // 若 v4 > fld_C
  {
    if ( fld_4 != nullptr )  // 若 fld_4 非空
      j__free(*(void **)(this + 4));  // 调 j__free
    v13 = *(uint32_t *)(pArg2 + 4);  // v13 = pArg2+4
    if ( v13 != 0 )  // 若 v13 != 0
      v14 = (*(uint32_t *)(pArg2 + 8) - v13) >> 4;
    else
      v14 = 0;
    if ( sub_44CF50((uint32_t *)this, v14) != 0 )  // 16 字节元素容器预留（首次分配）
      *(uint32_t *)(this + 8) = sub_54E680(*(uint32_t **)(pArg2 + 4), *(uint32_t **)(pArg2 + 8), *(uint32_t **)(this + 4));  // 结算转发 2（602460）
    return this;  // 返回自身指针
  }
  if ( fld_4 != nullptr )  // 若 fld_4 非空
    fld_82 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 4;  // this+8 物品 id
  else
    fld_82 = 0;
  v12 = (uint32_t *)(*(uint32_t *)(pArg2 + 4) + 16 * fld_82);
  sub_54E660(*(uint32_t **)(pArg2 + 4), v12, *(uint32_t **)(this + 4));  // 结算转发（54E1B0）
  *(uint32_t *)(this + 8) = sub_602460(v12, *(uint32_t **)(pArg2 + 8), *(uint32_t **)(this + 8));  // 16 字节批量拷贝
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x54FFB0 sub_54FFB0 —— PVP 结算窗口入队（54F610 + 4BF340，23 行——被 cashshop.cpp 0x550020 调用）
// ------------------------------------------------------------
// 大白话：PVP 结算窗口入队入口：54F610 + 4BF340（23 行）——被 cashshop.cpp 0x550020 调用。
unsigned int /*thiscall*/ sub_54FFB0(int this, uint32_t *Block)  // 函数: PVP 结算窗口入队（54F610 + 4BF340，23 行——被 cashshop.cpp 0x550020 调用）
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  int fld_82; // edi
  unsigned int result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8 物品 id
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) >> 4 )  // 若 fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) >> 4
    return sub_54F610(this, *(char **)(this + 8), 1u, Block);  // PVP 结算窗口入队实现
  fld_82 = *(uint32_t *)(this + 8);  // fld_82 = this+8
  result = sub_4BF340(fld_82, 1, Block);  // 结果 = 16 字节元素填充
  *(uint32_t *)(this + 8) = fld_82 + 16;  // this+8 = fld_82 + 16
  return result;
}


