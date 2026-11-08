// ============================================================
// 【40JP逆向源代码工程】game/pvp_ui.cpp
// 模块: PVP 房间界面/UI 命令 + 粒子系统(CNRDParticle) + 观察者-装备族（0x52 区）
// 来源: work/dump_miscb.txt  区块: 0x520000-0x530000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 162
// ------------------------------------------------------------
// ★ 四大板块（区块实际内容比"文件名"丰富）：
//   ① PO 工厂分发器 0x522300（0x51 区全部物品/装备 PO 的 new 调度，接 po_effects.cpp）
//   ② 邮件系统 mail::MailFrame/MailBox/CreateMailFrame/InboxFrame/CNRDMailWindow
//      + 弹出菜单 CNRDPopupMenu + PVP 房间 UI（音效 TAG：COMMAND_SELECT / UI_COMMAND_CLOSE /
//      COMMAND_SHOW / CLICK_BUTTON2，P32 TAG 分发链 sub_432EA0）
//   ③ CNRDParticle 粒子系统 = 《21_速查》P36/P40 的实现本体（0x529D20-0x52B090）：
//      vmt48 轴偏移求值器 = P40 三种移动类型公式；vmt8 物理更新消费 P9 全局时间域
//      dword_7930D0 + 重力二次项；vmt14 X 镜像；vmt38 冻结槽（P36⑥）
//   ④ 观察者-装备族 0x52D550-0x52E1C0：docs/15 已 L1 精修（src/cnrd/ActiveObjectEquipment.cpp），
//      本文件保留 L2 转写体并逐函数标注交叉引用
// 证据关键字：dword_99FEC0 = PVP 房间管理器全局；0x52C040 取当前 PVP 房间名
//   （IDA 符号 CNRDPVPInterface::getCurrentPVPMapFileName 自证，非 PVP 模式回 aErrorPvpModeCn）
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============
// 【分区 1】PO 工厂分发器 + 邮件帧辅助（0x522300-0x522580）
// 其中工厂分发器（0x522300）是物品→PassiveObject 的统一 new 入口：护符大函数(0x510F30)→巨函数(0x51BA00)→
// 装备判定(0x442DA0)→CNRDEquipment(0x5140A0, 0x544B) 或按物品类型 new 消耗品 PO
// （po_effects.cpp 分区 1 的各 Stackable 类）。后三函数为邮件帧的光标/点击辅助。
// ============

// 0x522300 sub_522300
// ------------------------------------------------------------
// ★ PO 工厂分发器（0x51 区物品/装备 PO 统一 new 入口）：sub_510F30(护符 PO) →
// sub_51BA00(0x51 区巨函数) → sub_442DA0 装备判定 → new(0x544)+sub_5140A0 建 CNRDEquipment；
// 否则按物品类型 switch：case 3/4=new(0xA4)+0x5106C0 CNThrowStackable / case 2=0x5107A0
// CNRecipeStackable / case 5=0x510880 CNLotteryStackable / 默认=0x50F740 CNRDStackable
// → vt+20(1) 激活 + vt+40(a2) 参数注入 + 类型!=3 标志写入

int /*cdecl*/ sub_522300(void *a1, int a2, int a3, int a4, int a5, char a6)
{
  int v6; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  char v12; // bl
  uint32_t v14[15]; // [esp+Ch] [ebp-50h] BYREF
  void *Block; // [esp+48h] [ebp-14h]
  int v16; // [esp+4Ch] [ebp-10h]
  int v17; // [esp+58h] [ebp-4h]

  v16 = 0;
  v6 = sub_510F30(a1, a2);
  if ( v6 == 0 )
  {
    v6 = sub_51BA00((int)a1, a5, a4, a2, a3);
    if ( v6 == 0 )
    {
      if ( sub_442DA0((char)a1) != 0 )
      {
        Block = operator new(0x544u);
        v7 = 0;
        v17 = 0;
        if ( Block != nullptr )
        {
          v8 = sub_4E9B10(v14, a2, a3, a4, a5);
          LOBYTE(v17) = 1;
          v16 = 1;
          v7 = sub_5140A0((char)a1, (int)v8);
        }
        v6 = v7;
        v17 = -1;
        if ( (v16 & 1) != 0 )
          sub_445150(v14);
LABEL_24:
        if ( v6 == 0 )
          return v6;
        goto LABEL_25;
      }
      if ( sub_442DA0((char)a1) == 0 )
        return v6;
      v9 = sub_4CE8A0((uint32_t *)dword_8F84D4, (int)a1);
      if ( v9 == 0 )
        return v6;
      v10 = *(uint32_t *)(v9 + 100);
      switch ( v10 )
      {
        case 3:
        case 4:
          Block = operator new(0xA4u);
          v17 = 3;
          if ( Block != nullptr )
          {
            v11 = sub_5106C0(a1);
            goto LABEL_23;
          }
          break;
        case 2:
          Block = operator new(0xA8u);
          v17 = 4;
          if ( Block != nullptr )
          {
            v11 = sub_5107A0(a1);
LABEL_23:
            v17 = -1;
            v6 = v11;
            goto LABEL_24;
          }
          break;
        case 5:
          Block = operator new(0xA4u);
          v17 = 5;
          if ( Block != nullptr )
          {
            v11 = sub_510880(a1);
            goto LABEL_23;
          }
          break;
        default:
          Block = operator new(0xA4u);
          v17 = 6;
          if ( Block != nullptr )
          {
            v11 = sub_50F740((char)a1);
            goto LABEL_23;
          }
          break;
      }
      v11 = 0;
      goto LABEL_23;
    }
  }
LABEL_25:
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 20))(v6, 1) != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 40))(v6, a2);
  v12 = (*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 16))(v6) + 28) != 3) - 1;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 16))(v6) + 32) = a6 & v12;
  return v6;
}


// ------------------------------------------------------------
// 0x522500 sub_522500
// ------------------------------------------------------------
// MailFrame 辅助：+48 非空返回 +47（选中项句柄）

int /*thiscall*/ sub_522500(uint32_t *this)
{
  if ( *(this + 48) != 0 )
    return *(this + 47);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x522520 sub_522520
// ------------------------------------------------------------
// MailFrame 光标项换算：+27 项对象 → vt+44()/vt+16() → sub_4F33A0/sub_4F2C10 屏幕坐标（+29/+30 偏移）

int /*thiscall*/ sub_522520(int *this)
{
  int result; // eax
  int v3; // ebx
  int v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // [esp-Ch] [ebp-14h]
  int v8; // [esp+4h] [ebp-4h]

  result = *(this + 27);
  if ( result != 0 )
  {
    v3 = *(this + 5);
    v4 = *(uint32_t *)(result + 40);
    v8 = *(this + 6);
    if ( v4 != 0 )
    {
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 44))(v4);
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 16))(v4);
      v6 = sub_4F33A0(*(uint32_t *)(v5 + 4));
      return sub_4F2C10(v3 + *(this + 29), v8 + *(this + 30), v6, v7);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x522580 sub_522580
// ------------------------------------------------------------
// MailFrame 命中判定：pt ∈ (+5+29, +6+30) 起 30×30 格（邮件图标格）

bool /*thiscall*/ sub_522580(uint32_t *this)
{
  int v1; // edx
  bool result; // al
  int v3; // eax

  v1 = *(this + 29) + *(this + 5);
  result = pt.x >= v1 - 2 && pt.x < v1 + 30 && (v3 = *(this + 6) + *(this + 30), pt.y >= v3 - 2) && pt.y < v3 + 30;
  return result;
}



// ------------------------------------------------------------
// ============
// 【分区 2】邮件系统（0x523860-0x525760）
// mail::MailFrame（信箱框架）/ mail::MailBox（附件容器）/ mail::CreateMailFrame（写信框）/
// mail::InboxFrame（收件箱）/ mail::CNRDMailWindow（窗口宿主）。按 28 字节/项的
// std::string vector 与 44 字节/项的附件结构驱动；确认/关闭走 COMMAND_SELECT/UI_COMMAND_CLOSE。
// ============

// 0x523860 mail__MailFrame__vmt1C
// ------------------------------------------------------------
// mail::MailFrame__vmt1C 帧处理：基类 nengine::CNFrame__vmt1C → +108 邮件对象非空
// && 全局 dword_9B7E94 使能 → 0x522520 光标换算/0x523420/0x522F20 刷新 →
// 命中 30×30 格且 +108[10] 变化 → sub_44E8D0(0x1A, id, 11) 28×28 邮件图标重绘

char /*thiscall*/ mail__MailFrame__vmt1C(int this)
{
  int v1; // edi
  uint32_t *v3; // eax

  nengine__CNFrame__vmt1C();
  v3 = *(uint32_t **)(this + 108);
  if ( v3 != nullptr )
  {
    LOBYTE(v3) = dword_9B7E94;
    if ( dword_9B7E94 != 0 )
    {
      LOBYTE(v3) = *(uint8_t *)(this + 16);
      if ( (uint8_t)v3 != 0 )
      {
        sub_522520((int *)this);
        sub_523420(this);
        sub_522F20(this);
        v3 = *(uint32_t **)(this + 108);
        if ( v3 != nullptr )
        {
          v1 = v3[10];
          LOBYTE(v3) = sub_522580((uint32_t *)this);
          if ( (uint8_t)v3 != 0 && v1 != 0 )
          {
            if ( dword_9B88D0 != v1 || dword_795378 != 11 )
            {
              v3 = (uint32_t *)sub_44E8D0((char *)dword_8F8528, (void *)0x1A, v1, 11);
              if ( v3 != nullptr )
                LOBYTE(v3) = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*v3 + 48))(
                               v3,
                               *(uint32_t *)(this + 20) + *(uint32_t *)(this + 116),
                               *(uint32_t *)(this + 24) + *(uint32_t *)(this + 120),
                               28,
                               28);
            }
          }
          else
          {
            LOBYTE(v3) = dword_9B88D0;
            if ( dword_9B88D0 != 0 && dword_795378 == 11 )
              LOBYTE(v3) = sub_44E850(dword_8F8528, 26);
          }
        }
      }
    }
  }
  return (char)v3;
}



// ------------------------------------------------------------
// 0x5238A0 sub_5238A0
// ------------------------------------------------------------
// MailFrame 辅助（24L：列表项状态刷新）

int /*thiscall*/ sub_5238A0(uint32_t *this)
{
  int v1; // edi
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int result; // eax

  v1 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 212);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 32))(this, v1, 9);
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, v1, 11, 12, 13, -1, 0, 0);
  else
    v4 = nullptr;
  *(this + 28) = v4;
  sub_69A5F0(v4, 185, 6);
  sub_69A840(*(this + 28));
  *((uint8_t *)this + 16) = 1;
  result = dword_9B7E94;
  if ( dword_9B7E94 == 0 )
  {
    result = sub_418DD0(8);
    dword_9B7E94 = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x523960 sub_523960
// ------------------------------------------------------------
// MailFrame 辅助（30L：列表内容重建）

void /*thiscall*/ sub_523960(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  void *v6; // edi

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 28);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 29);
  *(this + 28) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 30);
  *(this + 29) = 0;
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 31);
  *(this + 30) = 0;
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  v6 = (void *)*(this + 32);
  *(this + 31) = 0;
  if ( v6 != nullptr )
  {
    sub_433E30(v6);
    j__free(v6);
  }
  *(this + 32) = 0;
}



// ------------------------------------------------------------
// 0x5239D0 sub_5239D0
// ------------------------------------------------------------
// MailFrame 辅助（12L）

int /*thiscall*/ sub_5239D0(int this)
{
  sub_426BD0((uint8_t *)this);
  *(uint32_t *)this = &vftbl_nengine__CNFrame;
  sub_69C6B0(this);
  *(uint32_t *)this = &vftbl_mail__MailFrame;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 4;
  *(uint32_t *)(this + 120) = 4;
  sub_5238A0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x523A50 mail__MailFrame__vmt0
// ------------------------------------------------------------
// mail::MailFrame__vmt0 删除析构壳

void */*thiscall*/ mail__MailFrame__vmt0(void *Block, char a2)
{
  sub_523A80();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x523A80 sub_523A80
// ------------------------------------------------------------
// MailFrame 辅助（9L）

int /*thiscall*/ sub_523A80(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_mail__MailFrame;
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 112);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(uint32_t *)(this + 112) = 0;
  return sub_43C2E0((void **)this);
}



// ------------------------------------------------------------
// 0x523AE0 sub_523AE0
// ------------------------------------------------------------
// MailFrame 项插入（15L：a4=Src 数据 + a5/a6 参数）

uint32_t */*thiscall*/ sub_523AE0(uint32_t *this, int a2, int a3, void *Src, int a5, int a6)
{
  uint32_t *v7; // ecx

  v7 = this + 3;
  *this = &vftbl_mail__Mail;
  v7[6] = 15;
  v7[5] = 0;
  *((uint8_t *)v7 + 4) = 0;
  *(this + 1) = a2;
  *(this + 2) = a3;
  sub_4015C0(Src, strlen((const char *)Src));
  *(this + 11) = a5;
  *(this + 10) = a6;
  *(this + 12) = timeGetTime();
  return this;
}



// ------------------------------------------------------------
// 0x523B70 mail__MailBox__vmt0
// ------------------------------------------------------------
// mail::MailBox__vmt0 删除析构壳（19L，附件容器）

uint32_t */*thiscall*/ mail__MailBox__vmt0(uint32_t *Block, char a2)
{
  int v3; // esi

  *Block = &vftbl_mail__MailBox;
  sub_523800(Block);
  v3 = *(Block + 3);
  if ( v3 != 0 )
  {
    if ( *(uint32_t *)(v3 + 4) != 0 )
      j__free(*(void **)(v3 + 4));
    *(uint32_t *)(v3 + 4) = 0;
    *(uint32_t *)(v3 + 8) = 0;
    *(uint32_t *)(v3 + 12) = 0;
    j__free((void *)v3);
  }
  *(Block + 3) = 0;
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x523BD0 sub_523BD0
// ------------------------------------------------------------
// noreturn 辅助（15L，异常/断言路径）

void /*noreturn*/ sub_523BD0()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0("invalid vector<T> subscript", 0x1Bu);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::out_of_range::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// ------------------------------------------------------------
// 0x523C40 sub_523C40
// ------------------------------------------------------------
// noreturn 辅助（15L）

void /*noreturn*/ sub_523C40()
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
// 0x523CB0 sub_523CB0
// ------------------------------------------------------------
// MailBox 主逻辑（107L：邮件列表装载/翻页）

int /*thiscall*/ sub_523CB0(uint32_t *this)
{
  int v2; // ecx
  int v3; // edi
  void *v4; // ebx
  const char *v5; // eax
  void **v6; // ecx
  int v7; // esi
  void **v8; // ecx
  int v9; // ebx
  char *v10; // eax
  int v11; // ebx
  char *v12; // eax
  int v14; // [esp+Ch] [ebp-38h]
  uint32_t *v15; // [esp+10h] [ebp-34h]
  int v16; // [esp+14h] [ebp-30h]
  uint8_t v17[4]; // [esp+18h] [ebp-2Ch] BYREF
  void *Block[4]; // [esp+1Ch] [ebp-28h] BYREF
  int v19; // [esp+2Ch] [ebp-18h]
  unsigned int v20; // [esp+30h] [ebp-14h]
  int v21; // [esp+34h] [ebp-10h]
  int v22; // [esp+40h] [ebp-4h]

  v2 = *(this + 42);
  v21 = dword_796E50;
  v3 = *(this + 6);
  v15 = this;
  v16 = *(this + 5);
  v14 = sub_5486B0(v2);
  v4 = (void *)sub_5486B0(*(this + 40));
  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
  if ( *(this + 41) != 0 )
  {
    v20 = 15;
    v19 = 0;
    LOBYTE(Block[0]) = 0;
    sub_4015C0(v4, strlen((const char *)v4));
    v22 = 0;
    sub_4022F0((std::_String_base *)v17, &unk_7039C4, 3);
    v5 = (const char *)sub_5486B0(*(this + 41));
    sub_4022F0((std::_String_base *)v17, v5, strlen(v5));
    v6 = (void **)Block[0];
    if ( v20 < 0x10 )
      v6 = Block;
    v7 = v16 + 75;
    (*(void (/*cdecl*/ **)(int, int, int, int, void **))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v16 + 75,
      v3 + 108,
      -9795152,
      v6);
    v8 = (void **)Block[0];
    if ( v20 < 0x10 )
      v8 = Block;
    (*(void (/*cdecl*/ **)(int, int, int, int, void **))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v7,
      v3 + 107,
      -16179413,
      v8);
    v22 = -1;
    if ( v20 >= 0x10 )
      j__free(Block[0]);
    v20 = 15;
    v19 = 0;
    LOBYTE(Block[0]) = 0;
  }
  else
  {
    v7 = v16 + 75;
    (*(void (/*cdecl*/ **)(int, int, int, int, void *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v16 + 75,
      v3 + 108,
      -9795152,
      v4);
    (*(void (/*cdecl*/ **)(int, int, int, int, void *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v16 + 75,
      v3 + 107,
      -16179413,
      v4);
  }
  if ( (int)v15[42] < 0 )
  {
    v9 = *(uint32_t *)dword_79C0B0;
    v10 = sub_422E70(2066);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v9 + 80))(dword_79C0B0, v7, v3 + 134, -13487361, v10);
    v11 = *(uint32_t *)dword_79C0B0;
    v12 = sub_422E70(2066);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v11 + 80))(dword_79C0B0, v7, v3 + 133, -16179413, v12);
  }
  else
  {
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v7,
      v3 + 134,
      -9795152,
      v14);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v7,
      v3 + 133,
      -16179413,
      v14);
  }
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
}



// ------------------------------------------------------------
// 0x523F10 sub_523F10
// ------------------------------------------------------------
// MailFrame 点击响应（24L）

char /*thiscall*/ sub_523F10(uint32_t *this)
{
  int v2; // esi
  char result; // al
  int v4; // edi
  int v5; // ebx
  char *v6; // eax

  sub_523CB0(this);
  sub_522920(this);
  sub_5229C0(this);
  v2 = *(this + 29);
  result = *(uint8_t *)(v2 + 17);
  v4 = *(uint32_t *)(v2 + 20);
  v5 = *(uint32_t *)(v2 + 24);
  if ( result != 0 )
  {
    result = dword_79BE3C;
    if ( dword_79BE3C == *(uint32_t *)(v2 + 12) )
    {
      v6 = sub_422E70(2069);
      return sub_4649B0(v4, v5, -1, -16777216, 1, (int)v6, 0, 0, 1600, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x523F80 sub_523F80
// ------------------------------------------------------------
// vector 插入编译器实例化体（104L，元素尺寸 a3，MSVC 泛型形态）

unsigned int /*thiscall*/ sub_523F80(int this, int Src, unsigned int a3, int *a4)
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
      sub_523C40(this);
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
// 0x524160 sub_524160
// ------------------------------------------------------------
// 容器扩容/访问辅助（15L）

unsigned int /*thiscall*/ sub_524160(uint32_t *this, int a2)
{
  int v2; // ecx
  unsigned int result; // eax
  int v4; // esi

  v2 = *(this + 3);
  for ( result = 0; ; ++result )
  {
    v4 = *(uint32_t *)(v2 + 4);
    if ( v4 == 0 || result >= (*(uint32_t *)(v2 + 8) - v4) >> 2 )
      break;
    if ( *(uint32_t *)(*(uint32_t *)(v4 + 4 * result) + 4) == a2 )
      return result;
  }
  return -1;
}



// ------------------------------------------------------------
// 0x5241B0 sub_5241B0
// ------------------------------------------------------------
// 邮件数据装载（81L：网络包/文件 → 列表项）

int /*thiscall*/ sub_5241B0(uint32_t *this, int a2)
{
  int v2; // edi
  int v3; // eax
  int v4; // edx
  int v5; // esi
  int v6; // edx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int i; // ebx
  int v12; // edi
  int v13; // eax
  int v14; // esi
  int v15; // edi
  int result; // eax

  v2 = *(uint32_t *)(*(this + 30) + 12);
  v3 = *(uint32_t *)(v2 + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(v2 + 8) - v3) >> 2;
  else
    v4 = 0;
  v5 = v4 / 5;
  v6 = *(uint32_t *)(v2 + 4);
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(v2 + 8) - v6) >> 2;
  else
    v7 = 0;
  if ( v7 % 5 != 0 )
    ++v5;
  v8 = a2 + *(this + 31);
  *(this + 31) = v8;
  if ( v8 > 1 )
  {
    *(uint8_t *)(*(this + 29) + 17) = 1;
  }
  else
  {
    v9 = *(this + 29);
    *(this + 31) = 1;
    *(uint8_t *)(v9 + 17) = 0;
  }
  if ( *(this + 31) < v5 )
  {
    *(uint8_t *)(*(this + 28) + 17) = 1;
  }
  else
  {
    v10 = *(this + 28);
    *(this + 31) = v5;
    *(uint8_t *)(v10 + 17) = 0;
  }
  for ( i = 0; i < 5; ++i )
  {
    v12 = *(this + 31) + i + 4 * *(this + 31) - 5;
    v13 = *(uint32_t *)(*(this + 30) + 12);
    v14 = *(uint32_t *)(v13 + 4);
    if ( v14 != 0 && v12 < (unsigned int)((*(uint32_t *)(v13 + 8) - v14) >> 2) && v12 >= 0 )
    {
      if ( (*(uint32_t *)(v13 + 8) - v14) >> 2 <= (unsigned int)v12 )
        sub_523BD0(*(uint32_t *)(*(this + 30) + 12));
      v15 = *(uint32_t *)(v14 + 4 * v12);
    }
    else
    {
      v15 = 0;
    }
    result = *(uint32_t *)(*(this + 32) + 4 * i);
    *(uint32_t *)(result + 108) = v15;
    if ( v15 != 0 )
    {
      result = *(uint32_t *)(result + 112);
      *(uint8_t *)(result + 16) = 1;
    }
    else
    {
      *(uint8_t *)(*(uint32_t *)(result + 112) + 16) = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5242C0 mail__CreateMailFrame__vmt1C
// ------------------------------------------------------------
// mail::CreateMailFrame__vmt1C 帧处理（4L 薄转发）

char /*thiscall*/ mail__CreateMailFrame__vmt1C(uint32_t *this)
{
  nengine__CNFrame__vmt1C();
  return sub_523F10(this);
}



// ------------------------------------------------------------
// 0x5242D0 sub_5242D0
// ------------------------------------------------------------
// CreateMailFrame 辅助（19L）

uint32_t */*thiscall*/ sub_5242D0(uint32_t *this)
{
  uint32_t *v2; // eax

  *this = &vftbl_mail__MailBox;
  v2 = operator new(0x10u);
  if ( v2 != nullptr )
  {
    v2[1] = 0;
    v2[2] = 0;
    v2[3] = 0;
  }
  else
  {
    v2 = nullptr;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = v2;
  return this;
}



// ------------------------------------------------------------
// 0x524330 sub_524330
// ------------------------------------------------------------
// 全局构造（20L：邮件窗口单例 new）

uint32_t *sub_524330()
{
  uint32_t *result; // eax
  uint32_t *v1; // eax

  result = (uint32_t *)dword_9B7E90;
  if ( dword_9B7E90 == 0 )
  {
    v1 = operator new(0x10u);
    if ( v1 != nullptr )
    {
      result = sub_5242D0(v1);
      dword_9B7E90 = (int)result;
    }
    else
    {
      dword_9B7E90 = 0;
      return nullptr;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5243A0 sub_5243A0
// ------------------------------------------------------------
// CreateMailFrame 主逻辑（51L：写信界面初始化）

int /*thiscall*/ sub_5243A0(uint32_t *this)
{
  int v1; // eax
  int v2; // ebx
  uint32_t *v4; // eax
  int v5; // edi
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // ecx
  int i; // ebx
  void *v11; // eax
  int v12; // eax
  int result; // eax

  v1 = *(uint32_t *)(dword_99FCC8 + 20);
  v2 = *(uint32_t *)(v1 + 160);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 32))(this, *(uint32_t *)(v1 + 60), 37);
  *(this + 27) = sub_418DD0(10);
  *(this + 30) = sub_524330();
  v4 = operator new(0x84u);
  v5 = 0;
  if ( v4 != nullptr )
    v6 = sub_43C410(v4, v2, 46, 47, 48, 46, 0, 0);
  else
    v6 = nullptr;
  *(this + 29) = v6;
  v7 = operator new(0x84u);
  if ( v7 != nullptr )
    v8 = sub_43C410(v7, v2, 49, 50, 51, 49, 0, 0);
  else
    v8 = nullptr;
  v9 = (uint32_t *)*(this + 29);
  *(this + 28) = v8;
  sub_69A5F0(v9, 80, 203);
  sub_69A5F0((uint32_t *)*(this + 28), 133, 203);
  sub_69A840(*(this + 29));
  sub_69A840(*(this + 28));
  *(this + 32) = operator new(0x14u);
  for ( i = 0; i < 195; i += 39 )
  {
    v11 = operator new(0x7Cu);
    if ( v11 != nullptr )
      v12 = sub_5239D0((int)v11);
    else
      v12 = 0;
    *(uint32_t *)(v5 + *(this + 32)) = v12;
    sub_69A5F0(*(uint32_t **)(v5 + *(this + 32)), 0, i);
    result = sub_69A840(*(uint32_t *)(v5 + *(this + 32)));
    v5 += 4;
  }
  return result;
}



// ------------------------------------------------------------
// 0x524530 mail__InboxFrame__vmt18
// ------------------------------------------------------------
// mail::InboxFrame__vmt18 帧处理（21L：收件箱刷新）

char /*thiscall*/ mail__InboxFrame__vmt18(Concurrency::details::ExternalContextBase *this)
{
  int v2; // eax
  int v3; // eax
  char result; // al

  Concurrency::details::ExternalContextBase::SpinYield(this);
  v2 = *((uint32_t *)this + 29);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    sub_5241B0(this, -1);
  }
  else
  {
    v3 = *((uint32_t *)this + 28);
    if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
      sub_5241B0(this, 1);
  }
  result = byte_9B7E98;
  if ( byte_9B7E98 != 0 )
    return sub_5241B0(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x524580 sub_524580
// ------------------------------------------------------------
// InboxFrame 列表装载（64L）

uint32_t */*thiscall*/ sub_524580(uint32_t *this)
{
  int v1; // eax
  void *v3; // eax
  uint32_t *v4; // eax
  int v5; // eax
  void *v6; // eax
  uint32_t *v7; // eax
  int v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  uint32_t *result; // eax
  int v15; // [esp+Ch] [ebp-10h]

  v1 = *(uint32_t *)(dword_99FCC8 + 20);
  v15 = *(uint32_t *)(v1 + 60);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 32))(this, *(uint32_t *)(v1 + 212), 7);
  v3 = operator new(0xE4u);
  if ( v3 != nullptr )
    v4 = (uint32_t *)sub_43C060((int)v3, 12, -1);
  else
    v4 = nullptr;
  *(this + 28) = v4;
  sub_69A5F0(v4, 75, 4);
  v5 = *(this + 28);
  *(uint32_t *)(v5 + 28) = 120;
  *(uint32_t *)(v5 + 32) = 18;
  v6 = operator new(0xE4u);
  if ( v6 != nullptr )
    v7 = (uint32_t *)sub_43C060((int)v6, 10, -1);
  else
    v7 = nullptr;
  *(this + 29) = v7;
  sub_69A5F0(v7, 75, 84);
  v8 = *(this + 29);
  *(uint32_t *)(v8 + 28) = 120;
  *(uint32_t *)(v8 + 32) = 18;
  v9 = operator new(0x84u);
  if ( v9 != nullptr )
    v10 = sub_43C410(v9, v15, 216, 217, 218, 216, 0, 0);
  else
    v10 = nullptr;
  *(this + 30) = v10;
  sub_69A5F0(v10, 43, 168);
  v11 = operator new(0x84u);
  if ( v11 != nullptr )
    v12 = sub_43C410(v11, v15, 12, 13, 14, 12, 0, 0);
  else
    v12 = nullptr;
  *(this + 31) = v12;
  sub_69A5F0(v12, 106, 168);
  sub_69A840(*(this + 28));
  sub_69A840(*(this + 29));
  sub_69A840(*(this + 30));
  sub_69A840(*(this + 31));
  v13 = operator new(0x20u);
  if ( v13 != nullptr )
    result = sub_4354D0(v13, (void *)6, 1);
  else
    result = nullptr;
  *(this + 32) = result;
  return result;
}



// ------------------------------------------------------------
// 0x524760 sub_524760
// ------------------------------------------------------------
// cdecl 回调（8L）

int /*cdecl*/ sub_524760(int a1)
{
  uint32_t *v1; // eax
  unsigned int v2; // eax

  v1 = sub_524330();
  v2 = sub_524160(v1, a1);
  sub_523760(v2);
  return sub_44AC10(dword_8F8528);
}



// ------------------------------------------------------------
// 0x524790 sub_524790
// ------------------------------------------------------------
// cdecl 列表构建（21L）

uint32_t */*cdecl*/ sub_524790(int a1)
{
  char *v1; // eax
  uint32_t *result; // eax
  char Buffer[256]; // [esp+4h] [ebp-104h] BYREF
  int v4; // [esp+104h] [ebp-4h]

  v4 = dword_796E50;
  sub_44AC10(dword_8F8528);
  sub_44E850(dword_8F8528, 28);
  sub_44E8D0((char *)dword_8F8528, (void *)0xD, 0, 0);
  if ( a1 > 0 )
  {
    memset(Buffer, 0, sizeof(Buffer));
    v1 = sub_422E70(2067);
    sprintf(Buffer, v1, a1);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);
  }
  sub_524330()[2] = a1;
  result = sub_524330();
  result[1] = 0;
  return result;
}



// ------------------------------------------------------------
// 0x524850 sub_524850
// ------------------------------------------------------------
// 比较/查找回调（18L）

unsigned int /*thiscall*/ sub_524850(int *this, int *a2)
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
    return sub_523F80((int)this, *(this + 2), 1u, a2);
  v4 = (int *)*(this + 2);
  *v4 = *a2;
  result = (unsigned int)(v4 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x5248A0 sub_5248A0
// ------------------------------------------------------------
// InboxFrame 辅助（14L）

int /*thiscall*/ sub_5248A0(int this)
{
  sub_426BD0((uint8_t *)this);
  *(uint32_t *)this = &vftbl_nengine__CNFrame;
  sub_69C6B0(this);
  *(uint32_t *)this = &vftbl_mail__InboxFrame;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 1;
  *(uint32_t *)(this + 128) = 0;
  sub_5243A0((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x524920 mail__InboxFrame__vmt0
// ------------------------------------------------------------
// mail::InboxFrame__vmt0 删除析构壳

void */*thiscall*/ mail__InboxFrame__vmt0(void *Block, char a2)
{
  sub_524950();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x524950 sub_524950
// ------------------------------------------------------------
// InboxFrame 析构基座（5L）

int /*thiscall*/ sub_524950(void **this)
{
  *this = &vftbl_mail__InboxFrame;
  sub_522660();
  return sub_43C2E0(this);
}



// ------------------------------------------------------------
// 0x5249A0 sub_5249A0
// ------------------------------------------------------------
// InboxFrame 删除确认（22L）

int /*thiscall*/ sub_5249A0(int this)
{
  sub_426BD0((uint8_t *)this);
  *(uint32_t *)this = &vftbl_nengine__CNFrame;
  sub_69C6B0(this);
  *(uint32_t *)(this + 108) = &vftbl_IRDStackCountReceiver;
  *(uint32_t *)this = &vftbl_mail__CreateMailFrame;
  *(uint32_t *)(this + 108) = &mail::CreateMailFrame::`vftable';
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 148) = 75;
  *(uint32_t *)(this + 152) = 41;
  *(uint32_t *)(this + 160) = 1000;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  sub_524580((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x524A60 mail__CreateMailFrame__vmt0
// ------------------------------------------------------------
// mail::CreateMailFrame__vmt0 删除析构壳

void */*thiscall*/ mail__CreateMailFrame__vmt0(void *Block, char a2)
{
  sub_524A90();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x524A90 sub_524A90
// ------------------------------------------------------------
// CreateMailFrame 析构基座（6L）

int /*thiscall*/ sub_524A90(void **this)
{
  *this = &vftbl_mail__CreateMailFrame;
  *(this + 27) = &mail::CreateMailFrame::`vftable';
  sub_523960(this);
  return sub_43C2E0(this);
}



// ------------------------------------------------------------
// 0x524AF0 sub_524AF0
// ------------------------------------------------------------
// 收件人/标题字段写入（25L：Src 数据拷入）

void /*thiscall*/ sub_524AF0(int **this, int a2, int a3, void *Src, void *Block, int a6)
{
  int v6; // esi
  int v8; // edi
  uint32_t *v9; // eax
  uint32_t *v10; // eax
  int *v11; // ecx

  v6 = (int)Block;
  if ( (int)Block >= 0 )
  {
    v8 = a6;
    if ( Block != nullptr || a6 != 0 )
    {
      v9 = operator new(0x34u);
      Block = v9;
      if ( v9 != nullptr )
        v10 = sub_523AE0(v9, a2, a3, Src, v6, v8);
      else
        v10 = nullptr;
      v11 = *(this + 3);
      Block = v10;
      sub_524850(v11, (int *)&Block);
      byte_9B7E98 = 1;
    }
  }
}



// ------------------------------------------------------------
// 0x524B80 sub_524B80
// ------------------------------------------------------------
// 发送邮件主逻辑（39L：7 参数打包）

char /*thiscall*/ sub_524B80(int this, int Block, int a3, int a4, void *Src, void *a6, uint32_t *a7)
{
  int v8; // eax
  int v9; // edx
  int v11; // esi
  char *v12; // ecx
  uint32_t *v13; // eax
  uint32_t *v14; // eax
  int v15; // ecx

  if ( Block < 0 )
    return 0;
  v8 = *(uint32_t *)(this + 12);
  v9 = *(uint32_t *)(v8 + 4);
  if ( v9 == 0 || Block >= (unsigned int)((*(uint32_t *)(v8 + 8) - v9) >> 2) )
  {
    sub_524AF0((int **)this, a3, a4, Src, a6, (int)a7);
    return 1;
  }
  v11 = *(uint32_t *)(v8 + 4);
  v12 = nullptr;
  if ( v11 == *(uint32_t *)(v8 + 8) )
    return 0;
  while ( v12 != (char *)Block || v11 == *(uint32_t *)(v8 + 8) )
  {
    v11 += 4;
    ++v12;
    if ( v11 == *(uint32_t *)(v8 + 8) )
      return 0;
  }
  v13 = operator new(0x34u);
  if ( v13 != nullptr )
    v14 = sub_523AE0(v13, a3, a4, Src, (int)a6, (int)a7);
  else
    v14 = nullptr;
  v15 = *(uint32_t *)(this + 12);
  a7 = v14;
  sub_523F80(v15, v11, 1u, (int *)&a7);
  byte_9B7E98 = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x524C90 sub_524C90
// ------------------------------------------------------------
// 附件处理（46L）

int /*thiscall*/ sub_524C90(int *this)
{
  int result; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // esi
  int v5; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // eax

  result = *(this + 32);
  if ( *(int *)(result + 8) > 0 )
  {
    result = *(uint32_t *)(result + 12);
    if ( *(uint32_t *)result != 0 )
    {
      v3 = sub_432F00(*(this + 35));
      v4 = v3;
      v5 = v3[5];
      if ( v5 != 0 && (v3[6] - v5) >> 2 != 0 )
        v3[6] -= 4;
      v6 = v3[5];
      if ( v6 == 0 || (result = (v3[6] - v6) >> 2) <= 0 )
      {
        v7 = *(this + 32);
        v8 = *(uint32_t *)(v7 + 20);
        v9 = v7 + 16;
        if ( v8 == 0 || (result = (*(uint32_t *)(v9 + 8) - v8) >> 2) <= 0 )
        {
          sub_484880(15);
          sub_484880(15);
          v10 = *(this + 32);
          if ( *(int *)(v10 + 8) <= 0 )
            v11 = 0;
          else
            v11 = **(uint32_t **)(v10 + 12);
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 44))(v11);
          return sub_485330(0, v12, v4, *(this + 33));
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x524D70 sub_524D70
// ------------------------------------------------------------
// 附件槽读取（14L）

int /*thiscall*/ sub_524D70(int *this)
{
  int v2; // eax

  sub_524C90(this);
  v2 = *((uint32_t *)dword_8F8528 + 7);
  if ( *(uint8_t *)(v2 + 256) == 0 )
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v2 + 124) + 12);
    dword_79BE54 = dword_79BE4C;
  }
  CNCommandChecker__vmt40(0, 1);
  *(uint8_t *)(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 7) + 136) + 17) = 1;
  sub_69BCC0(*(this + 28));
  return sub_69BCC0(*(this + 29));
}



// ------------------------------------------------------------
// 0x524DD0 sub_524DD0
// ------------------------------------------------------------
// 附件栏渲染（52L）

int /*thiscall*/ sub_524DD0(int *this)
{
  int v2; // eax
  uint32_t *v3; // eax
  int v4; // edx
  int v5; // ecx
  int result; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // edi
  int v11; // eax

  v2 = *(this + 32);
  if ( *(int *)(v2 + 8) <= 0 || **(uint32_t **)(v2 + 12) == 0 )
  {
LABEL_15:
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 40))(
      **((uint32_t **)dword_8F852C + 3),
      *(this + 42));
    v11 = *((uint32_t *)dword_8F8528 + 7);
    if ( *(uint8_t *)(v11 + 256) == 0 )
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v11 + 124) + 12);
      dword_79BE54 = dword_79BE4C;
    }
    CNCommandChecker__vmt40(0, 1);
    *(uint8_t *)(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 7) + 136) + 17) = 1;
    sub_69BCC0(*(this + 28));
    return sub_69BCC0(*(this + 29));
  }
  v3 = sub_432F00(*(this + 35));
  v4 = v3[5];
  if ( v4 != 0 && (v3[6] - v4) >> 2 != 0 && (v3[6] - v3[5]) >> 2 != 0 )
    v3[6] -= 4;
  v5 = v3[5];
  if ( v5 == 0 || (result = (v3[6] - v5) >> 2) <= 0 )
  {
    v7 = *(this + 32);
    v8 = *(uint32_t *)(v7 + 20);
    if ( v8 == 0 || (result = (*(uint32_t *)(v7 + 24) - v8) >> 2) <= 0 )
    {
      if ( *(int *)(v7 + 8) <= 0 )
        v9 = 0;
      else
        v9 = **(uint32_t **)(v7 + 12);
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 44))(v9);
      sub_484880(0);
      sub_4850B0(0, v10);
      goto LABEL_15;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x524F10 sub_524F10
// ------------------------------------------------------------
// 附件栏交互（66L）

int /*thiscall*/ sub_524F10(uint32_t *this)
{
  int v1; // edi
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  void *v7; // eax
  int v8; // eax
  void *v9; // eax
  int v10; // eax
  int v11; // edi
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  int i; // edi
  int result; // eax

  v1 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 212);
  *(this + 9) = sub_418DD0(0);
  *(this + 10) = operator new(8u);
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, v1, 2, 3, 3, 1, 0, 0);
  else
    v4 = nullptr;
  *(uint32_t *)*(this + 10) = v4;
  v5 = operator new(0x84u);
  if ( v5 != nullptr )
    v6 = sub_43C410(v5, v1, 5, 6, 6, 4, 0, 0);
  else
    v6 = nullptr;
  *(uint32_t *)(*(this + 10) + 4) = v6;
  sub_69A5F0(*(uint32_t **)*(this + 10), 21, 51);
  sub_69A5F0(*(uint32_t **)(*(this + 10) + 4), 86, 51);
  *(this + 11) = operator new(8u);
  v7 = operator new(0x84u);
  if ( v7 != nullptr )
    v8 = sub_5248A0((int)v7);
  else
    v8 = 0;
  *(uint32_t *)*(this + 11) = v8;
  v9 = operator new(0xACu);
  if ( v9 != nullptr )
    v10 = sub_5249A0((int)v9);
  else
    v10 = 0;
  *(uint32_t *)(*(this + 11) + 4) = v10;
  sub_69A5F0(*(uint32_t **)*(this + 11), 29, 82);
  sub_69A5F0(*(uint32_t **)(*(this + 11) + 4), 40, 99);
  v11 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v12 = operator new(0x84u);
  if ( v12 != nullptr )
    v13 = sub_43C410(v12, v11, 23, 24, 25, -1, 0, 0);
  else
    v13 = nullptr;
  *(this + 12) = v13;
  sub_69A5F0(v13, 245, 22);
  sub_69A840(*(this + 12));
  for ( i = 0; i < 8; i += 4 )
  {
    sub_69A840(*(uint32_t *)(i + *(this + 10)));
    sub_69A840(*(uint32_t *)(*(this + 11) + i));
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 1);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 22, 24);
  dword_9B7E9C = (int)this;
  return result;
}



// ------------------------------------------------------------
// 0x525120 mail__CNRDMailWindow__vmt10
// ------------------------------------------------------------
// mail::CNRDMailWindow__vmt10（3L 薄转发：窗口宿主槽）

int /*thiscall*/ mail__CNRDMailWindow__vmt10(uint32_t *this)
{
  return sub_524D70(*(int **)(*(this + 11) + 4));
}



// ------------------------------------------------------------
// 0x525130 sub_525130
// ------------------------------------------------------------
// 全局辅助（13L）

int sub_525130()
{
  int result; // eax
  char *v1; // eax

  sub_44AC10(dword_8F8528);
  result = dword_9B7E9C;
  if ( dword_9B7E9C != 0 )
  {
    sub_524DD0(*(int **)(*(uint32_t *)(dword_9B7E9C + 44) + 4));
    v1 = sub_422E70(2063);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v1, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x525170 sub_525170
// ------------------------------------------------------------
// CNRDMailWindow 消息处理（38L）

int /*thiscall*/ sub_525170(int *this, int a2, int a3, int a4)
{
  int result; // eax
  uint32_t *v6; // esi
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax

  result = (int)sub_432F00(a2);
  v6 = (uint32_t *)result;
  if ( result != 0 )
  {
    result = *(uint32_t *)(result + 8);
    if ( a3 < result && *(uint32_t *)(v6[3] + 4 * a3) != 0 )
    {
      v7 = *(this + 32);
      if ( *(int *)(v7 + 8) > 0 && **(uint32_t **)(v7 + 12) != 0 )
        sub_524C90(this);
      v8 = v6[5];
      if ( v8 == 0 || (result = (v6[6] - v8) >> 2) <= 0 )
      {
        v9 = *(this + 32);
        v10 = *(uint32_t *)(v9 + 20);
        v11 = v9 + 16;
        if ( v10 == 0 || (result = (*(uint32_t *)(v11 + 8) - v10) >> 2) <= 0 )
        {
          sub_484880(15);
          sub_484880(15);
          sub_485330(a3, a4, *(this + 32), 0);
          *(this + 33) = a3;
          *(this + 35) = a2;
          return sub_484880(16);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x525240 sub_525240
// ------------------------------------------------------------
// 窗口槽转发（3L）

int /*thiscall*/ sub_525240(int *this, int a2)
{
  return sub_525170(this - 27, *(this + 9), *(this + 7), a2);
}



// ------------------------------------------------------------
// 0x525260 sub_525260
// ------------------------------------------------------------
// 窗口状态重建（53L）

uint32_t */*thiscall*/ sub_525260(int *this)
{
  uint32_t *result; // eax
  uint32_t *v3; // edi
  int v4; // ecx
  int *v5; // esi
  int v6; // eax
  void (/*stdcall*/ **v7)(int); // edx
  int v8; // eax
  int v9; // [esp+4h] [ebp-4h]

  result = dword_8F8528;
  if ( *((uint32_t *)dword_8F8528 + 626) == 2 )
  {
    v3 = (char *)dword_8F8528 + 2508;
    result = sub_432F00(0);
    if ( *v3 == 3 )
    {
      v4 = v3[2];
      if ( v4 < result[2] )
      {
        result = (uint32_t *)result[3];
        v5 = (int *)result[v4];
        if ( v5 != nullptr )
        {
          result = *(uint32_t **)((*(int (/*thiscall*/ **)(uint32_t))(*v5 + 16))(result[v4]) + 4);
          if ( result == (uint32_t *)v3[1] )
          {
            result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 80))(v5);
            if ( (uint8_t)result != 0 )
            {
              v9 = *v5;
              v6 = (*(int (/*thiscall*/ **)(int *))(*v5 + 16))(v5);
              if ( (*(uint8_t (/*thiscall*/ **)(int *, uint32_t))(v9 + 60))(v5, *(uint32_t *)(v6 + 4)) != 0
                && (unsigned int)(*(int (/*thiscall*/ **)(int *))(*v5 + 44))(v5) > 1 )
              {
                v7 = (void (/*stdcall*/ **)(int))*(this + 27);
                *(this + 36) = 0;
                *(this + 34) = v3[2];
                (*v7)((int)(this + 27));
                return (uint32_t *)sub_540DE0(1, 0, v3[2], 6, 0, 0, 0);
              }
              else
              {
                v8 = (*(int (/*thiscall*/ **)(int *))(*v5 + 44))(v5);
                return (uint32_t *)sub_525170(this, 0, v3[2], v8);
              }
            }
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x525360 sub_525360
// ------------------------------------------------------------
// 窗口项访问（11L）

uint32_t */*thiscall*/ sub_525360(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  sub_5542C0();
  sub_5548B0(a2, 13);
  *this = &vftbl_mail__CNRDMailWindow;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 12) = 0;
  sub_524F10(this);
  return this;
}



// ------------------------------------------------------------
// 0x5253D0 mail__CNRDMailWindow__vmt4
// ------------------------------------------------------------
// mail::CNRDMailWindow__vmt4 删除析构壳

void */*thiscall*/ mail__CNRDMailWindow__vmt4(void *Block, char a2)
{
  sub_525400();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x525400 sub_525400
// ------------------------------------------------------------
// CNRDMailWindow 析构基座（6L）

int /*thiscall*/ sub_525400(uint32_t *this)
{
  *this = &vftbl_mail__CNRDMailWindow;
  sub_522AA0();
  *this = &vftbl_IRDPopupWindow;
  return sub_5542F0(this);
}



// ------------------------------------------------------------
// 0x525460 mail__CreateMailFrame__vmt18
// ------------------------------------------------------------
// mail::CreateMailFrame__vmt18 帧处理（87L：写信框逐帧刷新）

int /*thiscall*/ mail__CreateMailFrame__vmt18(int this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // edx
  int v12; // edi
  int v13; // eax
  int v14; // [esp-4h] [ebp-14h]
  int v15; // [esp+Ch] [ebp-4h]

  Concurrency::details::ExternalContextBase::SpinYield((Concurrency::details::ExternalContextBase *)this);
  v2 = *(uint32_t *)(this + 148) + *(uint32_t *)(this + 20);
  if ( pt.x < v2 - 2
    || pt.x >= v2 + 30
    || (v3 = *(uint32_t *)(this + 24) + *(uint32_t *)(this + 152), pt.y < v3 - 2)
    || pt.y >= v3 + 30 )
  {
    v4 = dword_79BE34;
    if ( *(uint8_t *)(this + 17) != 0 && dword_79BE34 == *(uint32_t *)(this + 12) )
    {
      v5 = *(uint32_t *)(this + 112);
      if ( *(uint8_t *)(v5 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v5 + 12) )
      {
        sub_5226F0(this, v5);
        v4 = dword_79BE34;
      }
      v6 = *(uint32_t *)(this + 116);
      if ( *(uint8_t *)(v6 + 17) != 0 && v4 == *(uint32_t *)(v6 + 12) )
      {
        sub_5226F0(this, v6);
        return sub_5227D0(this);
      }
    }
    else
    {
      v8 = *(uint32_t *)(this + 124);
      if ( *(uint8_t *)(v8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v8 + 12) )
      {
        sub_524D70((int *)this);
        return sub_5227D0(this);
      }
      v9 = *(uint32_t *)(this + 120);
      if ( *(uint8_t *)(v9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v9 + 12) )
      {
        if ( (uint8_t)sub_5235E0(this) != 0 )
        {
          v10 = sub_69B740(*(uint32_t *)(this + 112));
          v15 = sub_5232E0(this);
          if ( sub_5227B0(this) != 0 )
          {
            v12 = sub_5227B0(this);
            v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 44))(v12);
            v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 16))(v12);
            sub_522D60(v10, v15, *(uint32_t *)(this + 140), *(uint32_t *)(this + 132), *(uint32_t *)(v13 + 4), v14);
          }
          else
          {
            sub_522D60(v10, v11, 0, 0, 0, 0);
          }
        }
      }
      else if ( *(uint32_t *)(*(uint32_t *)(this + 112) + 12) == dword_79BE4C
             || *(uint32_t *)(*(uint32_t *)(this + 116) + 12) == dword_79BE4C )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 16) != 0 )
        {
          sub_522760(this);
          return sub_5227D0(this);
        }
        sub_522730(this);
      }
    }
  }
  else if ( byte_89D274 != 0 )
  {
    sub_524C90((int *)this);
  }
  else
  {
    sub_525260((int *)this);
  }
  return sub_5227D0(this);
}



// ------------------------------------------------------------
// 0x525660 sub_525660
// ------------------------------------------------------------
// 写信框输入处理（34L）

int /*thiscall*/ sub_525660(int this)
{
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
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
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint8_t *)(this + 220) = 0;
  *(uint8_t *)(this + 221) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x5256E0 sub_5256E0
// ------------------------------------------------------------
// 收件人校验（23L）

int /*thiscall*/ sub_5256E0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  uint32_t *v4; // esi
  int i; // ebx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 12) = 0;
  v4 = this + 13;
  for ( i = 23; i != 0; --i )
  {
    if ( *v4 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v4)(*v4, 1);
    *v4++ = 0;
  }
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 4);
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x525740 sub_525740
// ------------------------------------------------------------
// 辅助（9L）

int /*thiscall*/ sub_525740(uint32_t *this)
{
  int result; // eax

  result = 0;
  *(this + 2) = 0;
  *(uint8_t *)(*(this + 12) + 16) = 0;
  if ( byte_8F8118 != 0 )
    byte_8F8118 = 0;
  return result;
}



// ------------------------------------------------------------
// 0x525760 sub_525760
// ------------------------------------------------------------
// ★ 邮件窗口主 tick（154L userpurge）【音效 TAG 实证】：按钮命中 →
// sub_432EA0("COMMAND_SELECT")（P32 TAG 分发）确认音

void */*userpurge*/ sub_525760@<eax>(int a1@<ecx>, int a2@<edi>, int a3)
{
  void *result; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // ebx
  uint32_t *v10; // ecx
  int v11; // edx
  int v12; // eax
  int v13; // edi
  uint32_t *v14; // edi
  char *v15; // eax
  int v16; // eax
  int v17; // edi
  int v18; // edi
  int v19; // eax
  int v20; // eax
  unsigned int v21; // ecx
  int v22; // eax
  int v23; // eax
  int v24; // eax
  unsigned int v25; // ecx
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // eax
  unsigned int v30; // ecx
  int v31; // eax
  int v32; // eax
  int v33; // eax
  unsigned int v34; // ecx
  int v35; // eax
  int v36; // eax

  result = (void *)a3;
  switch ( a3 )
  {
    case 0:
    case 1:
      v5 = sub_429830((uint16_t)word_77F804);
      sub_45DB20((int)dword_8F8524, v5);
      v6 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8) + 52))(*(uint32_t *)(a1 + 8));
      sub_4564A0(v6);
      goto LABEL_32;
    case 2:
      sub_423200(dword_8F7B08, 13);
      sub_423380(dword_8F7B08);
      goto LABEL_32;
    case 3:
      v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8) + 52))(*(uint32_t *)(a1 + 8));
      v8 = sub_429830(v7);
      v9 = 0;
      v10 = (uint32_t *)(dword_8F850C + 16);
      break;
    case 4:
      v12 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8) + 52))(*(uint32_t *)(a1 + 8));
      sub_484640(v12);
      goto LABEL_32;
    case 5:
      v13 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8) + 52))(*(uint32_t *)(a1 + 8));
      sub_423200(dword_8F7B08, 10);
      a3 = v13;
      sub_423290(&a3, 2);
      HIBYTE(a3) = 2;
      sub_423290((char *)&a3 + 3, 1);
      a3 = 0;
      sub_423290(&a3, 4);
      sub_423380(dword_8F7B08);
      v14 = *(uint32_t **)(*(uint32_t *)(a1 + 4) + 28);
      v15 = sub_422E70(447);
      sub_43BEE0(v14, (int)v15, -6567706, 0, -1);
      goto LABEL_32;
    case 6:
      v16 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8) + 52))(*(uint32_t *)(a1 + 8));
      v17 = sub_429830(v16);
      sub_43B920(1);
      if ( *(uint32_t *)(v17 + 40) < 0x10u )
        v18 = v17 + 20;
      else
        v18 = *(uint32_t *)(v17 + 20);
      sub_43DA50(*((uint32_t *)dword_8F8528 + 7), v18, 0);
      goto LABEL_32;
    case 7:
      v19 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 8) + 52))(*(uint32_t *)(a1 + 8), a2);
      v20 = sub_429830(v19);
      v21 = *(uint32_t *)(v20 + 40);
      v22 = v20 + 16;
      if ( v21 < 0x10 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8510 + 4))(dword_8F8510, v22 + 4);
      else
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8510 + 4))(dword_8F8510, *(uint32_t *)(v22 + 4));
      goto LABEL_32;
    case 8:
      v23 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8) + 52))(*(uint32_t *)(a1 + 8));
      v24 = sub_429830(v23);
      v25 = *(uint32_t *)(v24 + 40);
      v26 = v24 + 16;
      if ( v25 < 0x10 )
        v27 = v26 + 4;
      else
        v27 = *(uint32_t *)(v26 + 4);
      sub_44E8D0((char *)dword_8F8528, (void *)0x2D, v27, 0);
      goto LABEL_32;
    case 9:
      sub_423200(dword_8F7B08, 78);
      a3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8) + 52))(*(uint32_t *)(a1 + 8));
      sub_423290(&a3, 2);
      sub_423380(dword_8F7B08);
      goto LABEL_32;
    case 10:
      v28 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 8) + 52))(*(uint32_t *)(a1 + 8), a2);
      v29 = sub_429830(v28);
      v30 = *(uint32_t *)(v29 + 40);
      v31 = v29 + 16;
      if ( v30 < 0x10 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8518 + 4))(dword_8F8518, v31 + 4);
      else
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8518 + 4))(dword_8F8518, *(uint32_t *)(v31 + 4));
      goto LABEL_32;
    case 11:
      v32 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8) + 52))(*(uint32_t *)(a1 + 8));
      v33 = sub_429830(v32);
      v34 = *(uint32_t *)(v33 + 40);
      v35 = v33 + 16;
      if ( v34 < 0x10 )
        v36 = v35 + 4;
      else
        v36 = *(uint32_t *)(v35 + 4);
      sub_44E8D0((char *)dword_8F8528, (void *)0x38, v36, 0);
LABEL_32:
      sub_525740(a1);
      return sub_432EA0("COMMAND_SELECT", -1, 0, 0);
    default:
      return result;
  }
  while ( v8 != *v10 )
  {
    ++v9;
    ++v10;
    if ( v9 >= 4 )
      goto LABEL_9;
  }
  sub_423200(dword_8F7B08, 14);
  HIBYTE(a3) = v9;
  sub_423290((char *)&a3 + 3, 1);
  sub_423380(dword_8F7B08);
LABEL_9:
  v11 = *(uint32_t *)(a1 + 48);
  *(uint32_t *)(a1 + 8) = 0;
  *(uint8_t *)(v11 + 16) = 0;
  if ( byte_8F8118 != 0 )
    byte_8F8118 = 0;
  return sub_432EA0("COMMAND_SELECT", -1, 0, 0);
}


// ------------------------------------------------------------
// ============
// 【分区 3】弹出菜单 + PVP 房间 UI + 文件加载器（0x525AD0-0x528C60）
// CNRDPopupMenu（右键菜单）→ 0x526070 窗口关闭链（UI_COMMAND_CLOSE）→ 0x526440/0x526BF0
// 主 UI 命令处理（COMMAND_SHOW）→ 房间列表/槽位/按钮族（CLICK_BUTTON2）→
// 文件加载器在 0x528DB0/0x529100 两项（_fsopen/fopen + 魔数校验 + 解码）。
// ============

// 0x525AD0 CNRDPopupMenu__vmt0
// ------------------------------------------------------------
// ★ CNRDPopupMenu 构造（126L：右键弹出菜单，菜单项数组构建）

void /*thiscall*/ sub_525AD0(int this, int a2)
{
  int v2; // edx
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  uint8_t *v7; // edi
  uint8_t *v8; // eax
  uint8_t *v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // edi
  int v13; // eax
  int v14; // eax
  unsigned int v15; // ecx
  int v16; // eax
  unsigned int i; // edi
  int v18; // ecx
  int v19; // ecx
  int v20; // eax
  uint32_t *v21; // eax
  int v22; // ecx
  int v23; // [esp+Ch] [ebp-4h]
  int v24; // [esp+18h] [ebp+8h]

  v2 = a2;
  if ( a2 == *(uint32_t *)(this + 48) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    v23 = v4;
    v24 = v5;
    v6 = sub_418DD0(103);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v4, v5, dword_79C0B0);
    v7 = __RTDynamicCast(
           *(uint32_t **)(this + 8),
           0,
           &CNRDObject `RTTI Type Descriptor',
           &CNRDVirtualCharacter `RTTI Type Descriptor',
           0);
    v8 = __RTDynamicCast(
           *(uint32_t **)(this + 8),
           0,
           &CNRDObject `RTTI Type Descriptor',
           &CNRDNpc `RTTI Type Descriptor',
           0);
    v9 = v8;
    if ( v7 != nullptr )
    {
      (*(void (/*thiscall*/ **)(uint8_t *, int, int, int, int, int))(*(uint32_t *)v7 + 384))(
        v7,
        v23 + 2,
        v24 + 2,
        18,
        18,
        1065353216);
      v10 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v7 + 52))(v7);
      v11 = sub_429830(v10);
      if ( v11 == 0 )
        return;
      if ( *(uint32_t *)(v11 + 40) < 0x10u )
        v12 = v11 + 20;
      else
        v12 = *(uint32_t *)(v11 + 20);
    }
    else if ( v8 != nullptr )
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v8 + 340))(v8) + 68) != 0 )
      {
        v13 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v9 + 340))(v9);
        sub_40FC80(v23 + 2, v24 + 2, *(uint32_t *)(v13 + 68));
      }
      v14 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v9 + 340))(v9);
      v15 = *(uint32_t *)(v14 + 28);
      v16 = v14 + 4;
      if ( v15 < 0x10 )
        v12 = v16 + 4;
      else
        v12 = *(uint32_t *)(v16 + 4);
    }
    else if ( *(uint32_t *)(this + 44) < 0x10u )
    {
      v12 = this + 24;
    }
    else
    {
      v12 = *(uint32_t *)(this + 24);
    }
    if ( v12 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 164);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v23 + 20,
        v24 + 6,
        -1,
        v12);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    }
  }
  else
  {
    for ( i = 0; ; ++i )
    {
      v18 = *(uint32_t *)(this + 148);
      if ( v18 == 0 || i >= (*(uint32_t *)(this + 152) - v18) >> 2 )
        break;
      if ( i == *(uint32_t *)(this + 160) )
      {
        v19 = *(uint32_t *)(v18 + 4 * i);
        v20 = *(uint32_t *)(this + 4 * v19 + 52);
        if ( v2 == v20
          && (*(uint8_t *)(v20 + 17) == 0
           || dword_79BE3C != *(uint32_t *)(v20 + 12)
           && dword_79BE34 != *(uint32_t *)(v20 + 12)
           && dword_79BE38 != *(uint32_t *)(v20 + 12)) )
        {
          v21 = *(uint32_t **)(this + 4 * v19 + 52);
          v22 = v21[28];
          if ( v22 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v22 + 152))(v22, v21[5], v21[6], dword_79C0B0);
        }
      }
      v2 = a2;
    }
  }
}


// ------------------------------------------------------------
// 0x525CE0 sub_525CE0
// ------------------------------------------------------------
// 菜单项使能查询（4L → BOOL）

BOOL /*thiscall*/ sub_525CE0(int **this, int a2)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  return *sub_472E30(this + 48, &v3, &a2) != *(this + 49);
}



// ------------------------------------------------------------
// 0x525D10 sub_525D10
// ------------------------------------------------------------
// 菜单项勾选（8L）

int /*thiscall*/ sub_525D10(int **this, int a2)
{
  int *v4; // [esp+4h] [ebp-4h] BYREF

  sub_472E30(this + 48, &v4, &a2);
  if ( v4 == *(this + 49) )
    return 0;
  else
    return v4[4];
}



// ------------------------------------------------------------
// 0x525D50 sub_525D50
// ------------------------------------------------------------
// 菜单取项（18L）

int */*thiscall*/ sub_525D50(int this)
{
  int *result; // eax
  int i; // ecx
  int v4; // edx

  if ( *(uint32_t *)(this + 148) != 0 )
    j__free(*(void **)(this + 148));
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = -1;
  result = (int *)(this + 52);
  for ( i = 23; i != 0; --i )
  {
    v4 = *result++;
    *(uint8_t *)(v4 + 16) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x525DA0 sub_525DA0
// ------------------------------------------------------------
// ★ 菜单确认处理（62L）【音效 TAG 实证】：命中项 → sub_432EA0("COMMAND_SELECT")

void */*thiscall*/ sub_525DA0(int this, int a2)
{
  int **v3; // ecx
  void *result; // eax
  char v5; // al
  char v6; // al
  int v7; // eax

  v3 = (int **)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8) + 340))(*(uint32_t *)(this + 8));
  result = (void *)(a2 - 12);
  switch ( a2 )
  {
    case 12:
      sub_44E8D0(*(char **)(this + 4), (void *)0x25, (int)v3, 0);
      goto LABEL_16;
    case 13:
      v5 = sub_525D10(v3, 0);
      sub_566110(v5);
      sub_44BBA0(*(uint32_t **)(this + 4), 6, 0);
      goto LABEL_16;
    case 14:
      sub_551500(v3);
      sub_44BBA0(*(uint32_t **)(this + 4), 3, 0);
      goto LABEL_16;
    case 15:
      v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8) + 336))(*(uint32_t *)(this + 8));
      sub_5540D0((void *)1, v7);
      sub_44BBA0(*(uint32_t **)(this + 4), 7, 0);
      sub_525740((uint32_t *)this);
      return sub_432EA0("COMMAND_SELECT", -1, 0, 0);
    case 16:
      sub_44E8D0(*(char **)(this + 4), (void *)0x2E, 0, 0);
      goto LABEL_16;
    case 17:
      if ( *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 2444) + 12) == 0 )
        sub_560610(1);
      return (void *)sub_525740((uint32_t *)this);
    case 18:
      sub_44E8D0(*(char **)(this + 4), (void *)0x34, 0, 0);
      goto LABEL_16;
    case 19:
      sub_44E8D0(*(char **)(this + 4), (void *)0x34, 0, 2);
      goto LABEL_16;
    case 20:
      sub_54C990(0);
      goto LABEL_15;
    case 21:
      sub_54C990(1);
LABEL_15:
      sub_44BBA0(dword_8F8528, 10, 0);
      goto LABEL_16;
    case 22:
      v6 = sub_525D10(v3, 6);
      sub_567470(v6);
      sub_44BBA0(*(uint32_t **)(this + 4), 11, 0);
LABEL_16:
      sub_525740((uint32_t *)this);
      result = sub_432EA0("COMMAND_SELECT", -1, 0, 0);
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x525F50 sub_525F50
// ------------------------------------------------------------
// 菜单布局/命中（63L usercall ecx/edi）

char /*usercall*/ sub_525F50@<al>(int a1@<ecx>, int a2@<edi>)
{
  int v2; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // ecx

  LOBYTE(v2) = dword_79C0A0;
  if ( *(uint32_t *)(dword_79C0A0 + 32) != 0 )
  {
    if ( sub_415660(38, byte_9B7EBE) != 0 )
    {
      v2 = *(uint32_t *)(a1 + 160);
      if ( v2 > 0 )
        *(uint32_t *)(a1 + 160) = --v2;
    }
    else if ( sub_415660(40, &unk_9B7EBD) != 0 )
    {
      v4 = *(uint32_t *)(a1 + 148);
      if ( v4 != 0 )
        v5 = (*(uint32_t *)(a1 + 152) - v4) >> 2;
      else
        v5 = 0;
      v6 = *(uint32_t *)(a1 + 160);
      v2 = v5 - 1;
      if ( v6 < v2 )
        *(uint32_t *)(a1 + 160) = v6 + 1;
    }
    else
    {
      LOBYTE(v2) = sub_44BCC0(dword_8F8528);
      if ( (uint8_t)v2 != 0 )
      {
        byte_9B7EBC = 0;
      }
      else
      {
        LOBYTE(v2) = sub_415660(32, &byte_9B7EBC);
        if ( (uint8_t)v2 != 0 )
        {
          v2 = sub_41C5A0(a1 + 144);
          if ( *(uint32_t *)(a1 + 160) < (unsigned int)v2 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 8) + 40))(*(uint32_t *)(a1 + 8), 18) != 0 )
            {
              LOBYTE(v2) = (uint8_t)sub_525760(
                                              a1,
                                              a2,
                                              *(uint32_t *)(*(uint32_t *)(a1 + 148) + 4 * *(uint32_t *)(a1 + 160)));
            }
            else
            {
              LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 8) + 40))(*(uint32_t *)(a1 + 8), 34);
              if ( (uint8_t)v2 != 0 )
                LOBYTE(v2) = (uint8_t)sub_525DA0(
                                                a1,
                                                *(uint32_t *)(*(uint32_t *)(a1 + 148) + 4 * *(uint32_t *)(a1 + 160)));
            }
          }
        }
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x526070 sub_526070
// ------------------------------------------------------------
// ★ 窗口关闭链（182L usercall）【音效 TAG 实证】：关闭确认 →
// sub_432EA0("UI_COMMAND_CLOSE")（P32 TAG）

uint32_t */*usercall*/ sub_526070@<eax>(int a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  uint32_t *result; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  uint32_t *v8; // esi
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // edi
  int v19; // ecx
  int v20; // edi
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // edi
  int v25; // ebx
  int v26; // edi
  int v27; // ebx
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // [esp-Ch] [ebp-14h]
  char v32; // [esp+7h] [ebp-1h]

  result = *(uint32_t **)(a1 + 8);
  if ( result == nullptr )
    return result;
  v32 = byte_89D275;
  if ( byte_89D274 != 0 && *(uint8_t *)(a1 + 220) == 0 || byte_89D275 != 0 && *(uint8_t *)(a1 + 221) == 0 )
  {
    v5 = 0;
    v6 = a1 + 52;
    do
    {
      if ( *(uint8_t *)(*(uint32_t *)v6 + 17) != 0 && dword_79BE3C == *(uint32_t *)(*(uint32_t *)v6 + 12) )
        break;
      ++v5;
      v6 += 4;
    }
    while ( v5 < 23 );
    if ( v5 == 23 )
    {
      v7 = *(uint32_t *)(a1 + 48);
      *(uint32_t *)(a1 + 8) = 0;
      *(uint8_t *)(v7 + 16) = 0;
      if ( byte_8F8118 != 0 )
        byte_8F8118 = 0;
      sub_432EA0("UI_COMMAND_CLOSE", -1, 0, 0);
      result = (uint32_t *)__RTDynamicCast(
                           *(uint32_t *)(a1 + 8),
                           0,
                           &CNRDObject `RTTI Type Descriptor',
                           &CNRDNpc `RTTI Type Descriptor',
                           0);
      v8 = result;
      if ( result != nullptr )
      {
        v9 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*result + 340))(result, a3, a2);
        v10 = *(uint32_t *)(v9 + 180);
        v11 = v9 + 156;
        if ( v10 < 0x10 )
          v12 = v11 + 4;
        else
          v12 = *(uint32_t *)(v11 + 4);
        return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int))(*v8 + 212))(v8, v12, -1);
      }
      return result;
    }
    *(uint8_t *)(a1 + 220) = byte_89D274;
    *(uint8_t *)(a1 + 221) = v32;
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 8) + 40))(*(uint32_t *)(a1 + 8), 18) != 0 )
  {
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 && (uint8_t)sub_45E680(*(uint32_t *)(a1 + 8)) == 0 )
    {
      v13 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 8) + 52))(*(uint32_t *)(a1 + 8));
      v14 = sub_429830(v13);
      v15 = v14;
      if ( v14 == 0
        || *(uint8_t *)(v14 + 188) == 0
        && (*(uint32_t *)(v14 + 40) < 0x10u ? (v16 = v14 + 20) : (v16 = *(uint32_t *)(v14 + 20)),
            sub_479290(v16) == -1
         && (*(uint32_t *)(v15 + 40) < 0x10u ? (v17 = v15 + 20) : (v17 = *(uint32_t *)(v15 + 20)),
             sub_479290(v17) == -1
          && (*(uint32_t *)(v15 + 40) < 0x10u ? (v18 = v15 + 20) : (v18 = *(uint32_t *)(v15 + 20)), sub_479290(v18) == -1))) )
      {
        v19 = *(uint32_t *)(a1 + 48);
        *(uint32_t *)(a1 + 8) = 0;
        *(uint8_t *)(v19 + 16) = 0;
        if ( byte_8F8118 != 0 )
        {
          byte_8F8118 = 0;
          return sub_432EA0("UI_COMMAND_CLOSE", -1, 0, 0);
        }
        return sub_432EA0("UI_COMMAND_CLOSE", -1, 0, 0);
      }
    }
  }
  else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 8) + 40))(*(uint32_t *)(a1 + 8), 34) != 0 )
  {
    v20 = *(uint32_t *)(a1 + 8);
    v31 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 36))(v20) + 8);
    v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 120))(v20);
    v22 = sub_45E490(v21, v31);
    if ( v22 < -50 || v22 >= 690 )
    {
      v23 = *(uint32_t *)(a1 + 48);
      *(uint32_t *)(a1 + 8) = 0;
      *(uint8_t *)(v23 + 16) = 0;
      if ( byte_8F8118 != 0 )
        byte_8F8118 = 0;
      return sub_432EA0("UI_COMMAND_CLOSE", -1, 0, 0);
    }
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 8) + 40))(*(uint32_t *)(a1 + 8), 18) != 0 )
  {
    sub_525F50(a1);
    v24 = 0;
    v25 = a1 + 52;
    do
    {
      result = *(uint32_t **)v25;
      if ( *(uint8_t *)(*(uint32_t *)v25 + 17) != 0 && dword_79BE34 == result[3] )
        result = (uint32_t *)sub_525760(v24);
      ++v24;
      v25 += 4;
    }
    while ( v24 < 12 );
  }
  else
  {
    result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 8) + 40))(*(uint32_t *)(a1 + 8), 34);
    if ( (uint8_t)result != 0 )
    {
      sub_525F50(a1);
      v26 = 12;
      v27 = a1 + 100;
      do
      {
        result = *(uint32_t **)v27;
        if ( *(uint8_t *)(*(uint32_t *)v27 + 17) != 0 && dword_79BE34 == result[3] )
          result = (uint32_t *)sub_525DA0(v26);
        ++v26;
        v27 += 4;
      }
      while ( v26 < 23 );
    }
    else if ( *(uint32_t *)(a1 + 8) == *(uint32_t *)(a1 + 16) )
    {
      v28 = *(uint32_t *)(a1 + 84);
      if ( *(uint8_t *)(v28 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v28 + 12) )
      {
        if ( *(uint32_t *)(a1 + 44) < 0x10u )
          v29 = a1 + 24;
        else
          v29 = *(uint32_t *)(a1 + 24);
        sub_44E8D0((char *)dword_8F8528, (void *)0x2D, v29, 0);
        sub_525740(a1);
        sub_432EA0("COMMAND_SELECT", -1, 0, 0);
      }
      result = *(uint32_t **)(a1 + 96);
      if ( *((uint8_t *)result + 17) != 0 && dword_79BE34 == result[3] )
      {
        if ( *(uint32_t *)(a1 + 44) < 0x10u )
          v30 = a1 + 24;
        else
          v30 = *(uint32_t *)(a1 + 24);
        sub_44E8D0((char *)dword_8F8528, (void *)0x38, v30, 0);
        sub_525740(a1);
        return sub_432EA0("COMMAND_SELECT", -1, 0, 0);
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x526440 sub_526440
// ------------------------------------------------------------
// UI 命令主处理 A（238L：拖拽/放置逻辑）

void */*thiscall*/ sub_526440(int this, void *Block)
{
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
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
  uint32_t *v17; // eax
  uint32_t *v18; // eax
  uint32_t *v19; // eax
  uint32_t *v20; // eax
  uint32_t *v21; // eax
  uint32_t *v22; // eax
  uint32_t *v23; // eax
  uint32_t *v24; // eax
  uint32_t *v25; // eax
  uint32_t *v26; // eax
  uint32_t *v27; // eax
  uint32_t *v28; // eax
  uint32_t *v29; // eax
  uint32_t *v30; // eax
  uint32_t *v31; // eax
  uint32_t *v32; // eax
  uint32_t *v33; // eax
  uint32_t *v34; // eax
  uint32_t *v35; // eax
  uint32_t *v36; // eax
  uint32_t *v37; // eax
  uint32_t *v38; // eax
  uint32_t *v39; // eax
  uint32_t *v40; // eax
  uint32_t *v41; // eax
  uint32_t *v42; // eax
  uint32_t *v43; // eax
  uint32_t *v44; // eax
  uint32_t *v45; // eax
  uint32_t *v46; // eax
  uint32_t *v47; // eax
  uint32_t *v48; // eax
  uint32_t *v49; // eax
  uint32_t *v50; // eax
  int *v51; // edi
  void *result; // eax
  int Blocka; // [esp+20h] [ebp+8h]

  *(uint32_t *)(this + 4) = Block;
  *(uint32_t *)(this + 216) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  v3 = operator new(0x68u);
  if ( v3 != nullptr )
    v4 = sub_426BD0(v3);
  else
    v4 = nullptr;
  *(uint32_t *)(this + 48) = v4;
  *((uint32_t *)v4 + 7) = 100;
  *((uint32_t *)v4 + 8) = 21;
  *(uint32_t *)(*(uint32_t *)(this + 48) + 68) = this;
  *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 0;
  v5 = operator new(0x84u);
  if ( v5 != nullptr )
    v6 = sub_43C410(v5, *(uint32_t *)(this + 216), 30, 31, 32, 30, 0, 0);
  else
    v6 = nullptr;
  *(uint32_t *)(this + 52) = v6;
  v7 = operator new(0x84u);
  if ( v7 != nullptr )
    v8 = sub_43C410(v7, *(uint32_t *)(this + 216), 33, 34, 35, 33, 0, 0);
  else
    v8 = nullptr;
  *(uint32_t *)(this + 56) = v8;
  v9 = operator new(0x84u);
  if ( v9 != nullptr )
    v10 = sub_43C410(v9, *(uint32_t *)(this + 216), 38, 39, 40, 38, 0, 0);
  else
    v10 = nullptr;
  *(uint32_t *)(this + 60) = v10;
  v11 = operator new(0x84u);
  if ( v11 != nullptr )
    v12 = sub_43C410(v11, *(uint32_t *)(this + 216), 106, 107, 106, 106, 0, 0);
  else
    v12 = nullptr;
  *(uint32_t *)(this + 64) = v12;
  v13 = operator new(0x84u);
  if ( v13 != nullptr )
    v14 = sub_43C410(v13, *(uint32_t *)(this + 216), 27, 28, 29, 27, 0, 0);
  else
    v14 = nullptr;
  *(uint32_t *)(this + 68) = v14;
  v15 = operator new(0x84u);
  if ( v15 != nullptr )
    v16 = sub_43C410(v15, *(uint32_t *)(this + 216), 125, 126, 127, 125, 0, 0);
  else
    v16 = nullptr;
  *(uint32_t *)(this + 72) = v16;
  v17 = operator new(0x84u);
  if ( v17 != nullptr )
    v18 = sub_43C410(v17, *(uint32_t *)(this + 216), 131, 132, 133, 131, 0, 0);
  else
    v18 = nullptr;
  *(uint32_t *)(this + 76) = v18;
  v19 = operator new(0x84u);
  if ( v19 != nullptr )
    v20 = sub_43C410(v19, *(uint32_t *)(this + 216), 162, 163, 164, 162, 0, 0);
  else
    v20 = nullptr;
  *(uint32_t *)(this + 80) = v20;
  v21 = operator new(0x84u);
  if ( v21 != nullptr )
    v22 = sub_43C410(v21, *(uint32_t *)(this + 216), 165, 166, 167, 165, 0, 0);
  else
    v22 = nullptr;
  *(uint32_t *)(this + 84) = v22;
  v23 = operator new(0x84u);
  if ( v23 != nullptr )
    v24 = sub_43C410(v23, *(uint32_t *)(this + 216), 200, 201, 202, 200, 0, 0);
  else
    v24 = nullptr;
  *(uint32_t *)(this + 88) = v24;
  v25 = operator new(0x84u);
  if ( v25 != nullptr )
    v26 = sub_43C410(v25, *(uint32_t *)(this + 216), 184, 185, 186, 184, 0, 0);
  else
    v26 = nullptr;
  *(uint32_t *)(this + 92) = v26;
  v27 = operator new(0x84u);
  if ( v27 != nullptr )
    v28 = sub_43C410(v27, *(uint32_t *)(this + 216), 187, 188, 189, 187, 0, 0);
  else
    v28 = nullptr;
  *(uint32_t *)(this + 96) = v28;
  v29 = operator new(0x84u);
  if ( v29 != nullptr )
    v30 = sub_43C410(v29, *(uint32_t *)(this + 216), 47, 48, 49, 47, 0, 0);
  else
    v30 = nullptr;
  *(uint32_t *)(this + 100) = v30;
  v31 = operator new(0x84u);
  if ( v31 != nullptr )
    v32 = sub_43C410(v31, *(uint32_t *)(this + 216), 44, 45, 46, 44, 0, 0);
  else
    v32 = nullptr;
  *(uint32_t *)(this + 104) = v32;
  v33 = operator new(0x84u);
  if ( v33 != nullptr )
    v34 = sub_43C410(v33, *(uint32_t *)(this + 216), 128, 129, 130, 128, 0, 0);
  else
    v34 = nullptr;
  *(uint32_t *)(this + 108) = v34;
  v35 = operator new(0x84u);
  if ( v35 != nullptr )
    v36 = sub_43C410(v35, *(uint32_t *)(this + 216), 41, 42, 43, 41, 0, 0);
  else
    v36 = nullptr;
  *(uint32_t *)(this + 112) = v36;
  v37 = operator new(0x84u);
  if ( v37 != nullptr )
    v38 = sub_43C410(v37, *(uint32_t *)(this + 216), 168, 169, 170, 168, 0, 0);
  else
    v38 = nullptr;
  *(uint32_t *)(this + 116) = v38;
  v39 = operator new(0x84u);
  if ( v39 != nullptr )
    v40 = sub_43C410(v39, *(uint32_t *)(this + 216), 181, 182, 183, 181, 0, 0);
  else
    v40 = nullptr;
  *(uint32_t *)(this + 120) = v40;
  v41 = operator new(0x84u);
  if ( v41 != nullptr )
    v42 = sub_43C410(v41, *(uint32_t *)(this + 216), 193, 194, 195, 193, 0, 0);
  else
    v42 = nullptr;
  *(uint32_t *)(this + 124) = v42;
  v43 = operator new(0x84u);
  if ( v43 != nullptr )
    v44 = sub_43C410(v43, *(uint32_t *)(this + 216), 196, 197, 198, 196, 0, 0);
  else
    v44 = nullptr;
  *(uint32_t *)(this + 128) = v44;
  v45 = operator new(0x84u);
  if ( v45 != nullptr )
    v46 = sub_43C410(v45, *(uint32_t *)(this + 216), 190, 191, 192, 190, 0, 0);
  else
    v46 = nullptr;
  *(uint32_t *)(this + 132) = v46;
  v47 = operator new(0x84u);
  if ( v47 != nullptr )
    v48 = sub_43C410(v47, *(uint32_t *)(this + 216), 204, 205, 206, 204, 0, 0);
  else
    v48 = nullptr;
  *(uint32_t *)(this + 136) = v48;
  v49 = operator new(0x84u);
  if ( v49 != nullptr )
    v50 = sub_43C410(v49, *(uint32_t *)(this + 216), 207, 208, 209, 207, 0, 0);
  else
    v50 = nullptr;
  *(uint32_t *)(this + 140) = v50;
  v51 = (int *)(this + 52);
  for ( Blocka = 23; Blocka != 0; --Blocka )
  {
    sub_69A840(*(uint32_t **)(this + 48), *v51);
    *(uint32_t *)(*v51++ + 68) = this;
  }
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
  *(uint32_t *)(this + 212) = dword_99FCCC;
  *(uint32_t *)(this + 176) = 1;
  *(uint32_t *)(this + 192) = 80;
  *(uint32_t *)(this + 196) = 1;
  result = operator new(0x11Cu);
  if ( result != nullptr )
  {
    result = (void *)sub_42AAB0(result);
    *(uint32_t *)(this + 16) = result;
  }
  else
  {
    *(uint32_t *)(this + 16) = 0;
  }
  return result;
}


// ------------------------------------------------------------
// 0x526BF0 sub_526BF0
// ------------------------------------------------------------
// ★ UI 命令主处理 B（746L 本文件最大函数）【音效 TAG 实证】：
// 命令分发含 sub_432EA0("COMMAND_SHOW")（显示面板）

char /*thiscall*/ sub_526BF0(int this, int *a2, char a3)
{
  char v4; // al
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // ebx
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int v14; // edx
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // edx
  int v19; // ebx
  int v20; // eax
  int v21; // ecx
  int v22; // edi
  int v23; // eax
  int v24; // ecx
  int v25; // edx
  int v26; // ebx
  int v27; // eax
  int v28; // eax
  int v29; // ecx
  int v30; // edx
  int v31; // ebx
  int v32; // eax
  int v33; // eax
  int v34; // edx
  int v35; // ebx
  int v36; // eax
  int v37; // ecx
  int v38; // eax
  int v39; // edx
  int v40; // ebx
  int v41; // eax
  int v42; // ecx
  int v43; // eax
  int v44; // edx
  int v45; // ebx
  int v46; // eax
  int v47; // ecx
  uint32_t *v48; // ebx
  uint32_t *v49; // eax
  uint32_t *v50; // ebx
  int v51; // eax
  int v52; // eax
  int v53; // edx
  int v54; // ebx
  int v55; // eax
  int v56; // ecx
  int v57; // eax
  int v58; // edx
  int v59; // ebx
  int v60; // eax
  int v61; // ecx
  int v62; // eax
  int v63; // ecx
  int v64; // edx
  int v65; // ebx
  int v66; // eax
  uint32_t *v67; // edi
  int v68; // eax
  int v69; // edx
  int v70; // ebx
  int v71; // eax
  int v72; // ecx
  int v73; // eax
  int v74; // edx
  int v75; // ebx
  int v76; // eax
  int v77; // ecx
  int v78; // ebx
  int v79; // eax
  int v80; // ecx
  int v81; // edx
  int v82; // ebx
  int v83; // eax
  int v84; // eax
  int v85; // ecx
  int v86; // eax
  bool v87; // bl
  int v88; // edi
  int v89; // eax
  int v90; // eax
  int v91; // edx
  int v92; // ebx
  int v93; // eax
  int v94; // ecx
  uint32_t *v95; // ebx
  int v96; // eax
  int v97; // ecx
  int v98; // edx
  int v99; // ebx
  int v100; // eax
  int v101; // eax
  int v102; // ecx
  int v103; // edx
  int v104; // eax
  int v105; // ecx
  int v106; // eax
  int v107; // ecx
  int v108; // edx
  int v109; // ebx
  int v110; // edi
  int v111; // eax
  int v112; // eax
  void *v113; // eax
  int v114; // eax
  int v115; // eax
  int v116; // edx
  int v117; // ebx
  int v118; // eax
  int v119; // ecx
  int v120; // eax
  int v121; // edx
  int v122; // ebx
  int v123; // eax
  int v124; // ecx
  int v125; // eax
  int v126; // edx
  int v127; // ebx
  int v128; // eax
  int v129; // ecx
  int v130; // eax
  int v131; // edx
  int v132; // ebx
  int v133; // eax
  int v134; // ecx
  uint32_t *v135; // edi
  int v136; // ecx
  int *v137; // edi
  int *v138; // ebx
  int v139; // eax
  int v140; // edx
  int v141; // eax
  int v142; // eax
  int v143; // eax
  int v144; // edx
  int v145; // ebx
  int v146; // eax
  int v147; // ecx
  int v148; // eax
  int v149; // eax
  int v150; // ecx
  int v151; // edx
  int v152; // ebx
  int v153; // eax
  int v154; // ecx
  int v155; // edi
  LONG x; // edi
  LONG y; // eax
  int v158; // eax
  int v159; // eax
  int v160; // edx
  int v161; // ecx
  int v162; // eax
  int v163; // ecx
  int v165; // [esp-Ch] [ebp-34h]
  int v166; // [esp-8h] [ebp-30h]
  int v167; // [esp-4h] [ebp-2Ch]
  char v168[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v170; // [esp+1Ch] [ebp-Ch] BYREF
  int v171; // [esp+20h] [ebp-8h] BYREF
  uint32_t *v172; // [esp+24h] [ebp-4h]

  sub_525D50();
  v4 = (*(int (/*thiscall*/ **)(int *, int))(*a2 + 40))(a2, 18);
  v5 = *a2;
  if ( v4 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int *))(v5 + 52))(a2);
    v7 = sub_429830(v6);
    v8 = v7;
    v172 = (uint32_t *)v7;
    if ( v7 == 0 )
      return v7;
    v9 = sub_429830((uint16_t)word_77F804);
    v10 = dword_8F7A24;
    v11 = *(uint32_t *)(dword_8F7A24 + 12);
    v170 = v9;
    if ( v11 == 1 )
    {
      if ( *(uint32_t *)(v8 + 184) != 0 )
      {
        if ( *(uint32_t *)(v9 + 184) != 0 )
        {
          if ( *(uint8_t *)(v8 + 188) != 0 )
          {
            if ( (uint8_t)sub_41C590(dword_8F7A24) == 0 )
            {
              v17 = *(uint32_t *)(this + 48);
              v18 = *(uint32_t *)(this + 148);
              v19 = *(uint32_t *)(v17 + 20);
              v20 = *(uint32_t *)(v17 + 24);
              if ( v18 != 0 )
                v21 = (*(uint32_t *)(this + 152) - v18) >> 2;
              else
                v21 = 0;
              sub_69A5F0(*(uint32_t **)(this + 60), v19, v20 + 21 * (v21 + 1));
              *(uint8_t *)(*(uint32_t *)(this + 60) + 16) = 1;
              v171 = 2;
              sub_431230(this + 144, &v171);
            }
            v22 = sub_429830((uint16_t)word_77F804);
            if ( sub_423B10(dword_8F850C) == v22 && (uint8_t)sub_41C590(dword_8F7A24) == 0 )
            {
              v23 = *(uint32_t *)(this + 48);
              v24 = *(uint32_t *)(this + 148);
              v25 = *(uint32_t *)(v23 + 20);
              v26 = *(uint32_t *)(v23 + 24);
              if ( v24 != 0 )
                v27 = (*(uint32_t *)(this + 152) - v24) >> 2;
              else
                v27 = 0;
              sub_69A5F0(*(uint32_t **)(this + 64), v25, v26 + 21 * (v27 + 1));
              *(uint8_t *)(*(uint32_t *)(this + 64) + 16) = 1;
              v171 = 3;
              sub_431230(this + 144, &v171);
            }
          }
        }
        else if ( (uint8_t)sub_41C590(dword_8F7A24) == 0 )
        {
          v28 = *(uint32_t *)(this + 48);
          v29 = *(uint32_t *)(this + 148);
          v30 = *(uint32_t *)(v28 + 20);
          v31 = *(uint32_t *)(v28 + 24);
          if ( v29 != 0 )
            v32 = (*(uint32_t *)(this + 152) - v29) >> 2;
          else
            v32 = 0;
          sub_69A5F0(*(uint32_t **)(this + 52), v30, v31 + 21 * (v32 + 1));
          *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 1;
          v171 = 0;
          sub_431230(this + 144, &v171);
        }
      }
      else if ( (uint8_t)sub_43B540(dword_8F850C) != 0 && (uint8_t)sub_41C590(v10) == 0 )
      {
        v12 = *(uint32_t *)(this + 48);
        v13 = *(uint32_t *)(this + 148);
        v14 = *(uint32_t *)(v12 + 20);
        v15 = *(uint32_t *)(v12 + 24);
        if ( v13 != 0 )
          v16 = (*(uint32_t *)(this + 152) - v13) >> 2;
        else
          v16 = 0;
        sub_69A5F0(*(uint32_t **)(this + 56), v14, v15 + 21 * (v16 + 1));
        *(uint8_t *)(*(uint32_t *)(this + 56) + 16) = 1;
        v171 = 1;
        sub_431230(this + 144, &v171);
      }
      if ( *(uint16_t *)(dword_8F8538 + 4) == 0xFFFF )
      {
        sub_41C590(dword_8F7A24);
        v33 = *(uint32_t *)(this + 48);
        v34 = *(uint32_t *)(this + 148);
        v35 = *(uint32_t *)(v33 + 20);
        v36 = *(uint32_t *)(v33 + 24);
        if ( v34 != 0 )
          v37 = (*(uint32_t *)(this + 152) - v34) >> 2;
        else
          v37 = 0;
        sub_69A5F0(*(uint32_t **)(this + 68), v35, v36 + 21 * (v37 + 1));
        *(uint8_t *)(*(uint32_t *)(this + 68) + 16) = 1;
        v171 = 4;
        sub_431230(this + 144, &v171);
      }
    }
    else if ( v11 == 4 && *(uint32_t *)(v8 + 68) == 0 )
    {
      sub_41C590(dword_8F7A24);
      v38 = *(uint32_t *)(this + 48);
      v39 = *(uint32_t *)(this + 148);
      v40 = *(uint32_t *)(v38 + 20);
      v41 = *(uint32_t *)(v38 + 24);
      if ( v39 != 0 )
        v42 = (*(uint32_t *)(this + 152) - v39) >> 2;
      else
        v42 = 0;
      sub_69A5F0(*(uint32_t **)(this + 72), v40, v41 + 21 * (v42 + 1));
      *(uint8_t *)(*(uint32_t *)(this + 72) + 16) = 1;
      v171 = 5;
      sub_431230(this + 144, &v171);
    }
    sub_41C590(dword_8F7A24);
    v43 = *(uint32_t *)(this + 48);
    v44 = *(uint32_t *)(this + 148);
    v45 = *(uint32_t *)(v43 + 20);
    v46 = *(uint32_t *)(v43 + 24);
    if ( v44 != 0 )
      v47 = (*(uint32_t *)(this + 152) - v44) >> 2;
    else
      v47 = 0;
    sub_69A5F0(*(uint32_t **)(this + 76), v45, v46 + 21 * (v47 + 1));
    *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = 1;
    v171 = 6;
    sub_431230(this + 144, &v171);
    v48 = v172;
    if ( v172[10] < 0x10u )
      v49 = v172 + 5;
    else
      v49 = (uint32_t *)v172[5];
    v171 = sub_479290(v49);
    if ( v48[10] < 0x10u )
      v50 = v48 + 5;
    else
      v50 = (uint32_t *)v48[5];
    v51 = sub_479290(v50);
    if ( v171 == -1 )
    {
      if ( v51 == -1 )
      {
        sub_41C590(dword_8F7A24);
        v52 = *(uint32_t *)(this + 48);
        v53 = *(uint32_t *)(this + 148);
        v54 = *(uint32_t *)(v52 + 20);
        v55 = *(uint32_t *)(v52 + 24);
        if ( v53 != 0 )
          v56 = (*(uint32_t *)(this + 152) - v53) >> 2;
        else
          v56 = 0;
        sub_69A5F0(*(uint32_t **)(this + 80), v54, v55 + 21 * (v56 + 1));
        *(uint8_t *)(*(uint32_t *)(this + 80) + 16) = 1;
        v171 = 7;
        sub_431230(this + 144, &v171);
      }
    }
    else
    {
      sub_41C590(dword_8F7A24);
      v57 = *(uint32_t *)(this + 48);
      v58 = *(uint32_t *)(this + 148);
      v59 = *(uint32_t *)(v57 + 20);
      v60 = *(uint32_t *)(v57 + 24);
      if ( v58 != 0 )
        v61 = (*(uint32_t *)(this + 152) - v58) >> 2;
      else
        v61 = 0;
      sub_69A5F0(*(uint32_t **)(this + 84), v59, v60 + 21 * (v61 + 1));
      *(uint8_t *)(*(uint32_t *)(this + 84) + 16) = 1;
      v171 = 8;
      sub_431230(this + 144, &v171);
    }
    v7 = *(uint32_t *)(v170 + 120);
    if ( v7 != 0 )
    {
      v7 = v172[30];
      if ( v7 == 0 )
      {
        sub_41C590(dword_8F7A24);
        v62 = *(uint32_t *)(this + 48);
        v63 = *(uint32_t *)(this + 148);
        v64 = *(uint32_t *)(v62 + 20);
        v65 = *(uint32_t *)(v62 + 24);
        if ( v63 != 0 )
          v66 = (*(uint32_t *)(this + 152) - v63) >> 2;
        else
          v66 = 0;
        sub_69A5F0(*(uint32_t **)(this + 88), v64, v65 + 21 * (v66 + 1));
        *(uint8_t *)(*(uint32_t *)(this + 88) + 16) = 1;
        v170 = 9;
        LOBYTE(v7) = sub_431230(this + 144, &v170);
      }
    }
    goto LABEL_178;
  }
  LOBYTE(v7) = (*(int (/*thiscall*/ **)(int *, int))(v5 + 40))(a2, 34);
  if ( (uint8_t)v7 == 0 )
  {
    if ( a2 == *(int **)(this + 16) )
    {
      if ( *(uint32_t *)(this + 44) < 0x10u )
        v142 = this + 24;
      else
        v142 = *(uint32_t *)(this + 24);
      if ( sub_479290(v142) != -1 )
      {
        sub_41C590(dword_8F7A24);
        v143 = *(uint32_t *)(this + 48);
        v144 = *(uint32_t *)(this + 148);
        v145 = *(uint32_t *)(v143 + 20);
        v146 = *(uint32_t *)(v143 + 24);
        if ( v144 != 0 )
          v147 = (*(uint32_t *)(this + 152) - v144) >> 2;
        else
          v147 = 0;
        sub_69A5F0(*(uint32_t **)(this + 84), v145, v146 + 21 * (v147 + 1));
        *(uint8_t *)(*(uint32_t *)(this + 84) + 16) = 1;
        v170 = 8;
        sub_431230(this + 144, &v170);
      }
      if ( *(uint32_t *)(this + 44) < 0x10u )
        v148 = this + 24;
      else
        v148 = *(uint32_t *)(this + 24);
      v7 = sub_479290(v148);
      if ( v7 != -1 )
      {
        sub_41C590(dword_8F7A24);
        v149 = *(uint32_t *)(this + 48);
        v150 = *(uint32_t *)(this + 148);
        v151 = *(uint32_t *)(v149 + 20);
        v152 = *(uint32_t *)(v149 + 24);
        if ( v150 != 0 )
          v153 = (*(uint32_t *)(this + 152) - v150) >> 2;
        else
          v153 = 0;
        sub_69A5F0(*(uint32_t **)(this + 96), v151, v152 + 21 * (v153 + 1));
        *(uint8_t *)(*(uint32_t *)(this + 96) + 16) = 1;
        v170 = 11;
        LOBYTE(v7) = sub_431230(this + 144, &v170);
      }
    }
    goto LABEL_178;
  }
  v67 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*a2 + 340))(a2);
  v172 = v67;
  if ( (uint8_t)sub_606CA0(v67 + 74) != 0 && (uint8_t)sub_41C590(dword_8F7A24) == 0 )
  {
    v68 = *(uint32_t *)(this + 48);
    v69 = *(uint32_t *)(this + 148);
    v70 = *(uint32_t *)(v68 + 20);
    v71 = *(uint32_t *)(v68 + 24);
    if ( v69 != 0 )
      v72 = (*(uint32_t *)(this + 152) - v69) >> 2;
    else
      v72 = 0;
    sub_69A5F0(*(uint32_t **)(this + 100), v70, v71 + 21 * (v72 + 1));
    *(uint8_t *)(*(uint32_t *)(this + 100) + 16) = 1;
    v170 = 12;
    sub_431230(this + 144, &v170);
    v67 = v172;
  }
  v170 = 0;
  if ( *(uint32_t *)sub_472E30(&v171, &v170) != v67[49] && (uint8_t)sub_41C590(dword_8F7A24) == 0 )
  {
    v73 = *(uint32_t *)(this + 48);
    v74 = *(uint32_t *)(this + 148);
    v75 = *(uint32_t *)(v73 + 20);
    v76 = *(uint32_t *)(v73 + 24);
    if ( v74 != 0 )
      v77 = (*(uint32_t *)(this + 152) - v74) >> 2;
    else
      v77 = 0;
    sub_69A5F0(*(uint32_t **)(this + 104), v75, v76 + 21 * (v77 + 1));
    *(uint8_t *)(*(uint32_t *)(this + 104) + 16) = 1;
    v170 = 13;
    sub_431230(this + 144, &v170);
    v67 = v172;
  }
  v78 = sub_429830((uint16_t)word_77F804);
  if ( v78 != 0
    && (*v67 != 27 || (uint8_t)sub_453DA0(99) != 0)
    && (uint8_t)sub_484F10(&v67[4 * *(uint32_t *)(v78 + 44) + 58]) == 0
    && (uint8_t)sub_41C590(dword_8F7A24) == 0 )
  {
    v79 = *(uint32_t *)(this + 48);
    v80 = *(uint32_t *)(this + 148);
    v81 = *(uint32_t *)(v79 + 20);
    v82 = *(uint32_t *)(v79 + 24);
    if ( v80 != 0 )
      v83 = (*(uint32_t *)(this + 152) - v80) >> 2;
    else
      v83 = 0;
    sub_69A5F0(*(uint32_t **)(this + 108), v81, v82 + 21 * (v83 + 1));
    *(uint8_t *)(*(uint32_t *)(this + 108) + 16) = 1;
    v170 = 14;
    sub_431230(this + 144, &v170);
    v67 = v172;
  }
  if ( (uint8_t)sub_47BFB0(*v67) == 0 )
  {
    v84 = sub_47CC80(v168, *v172);
    v85 = *(uint32_t *)(v84 + 4);
    if ( v85 != 0 )
      v86 = (*(uint32_t *)(v84 + 8) - v85) >> 2;
    else
      v86 = 0;
    v87 = v86 != 0;
    if ( Block != nullptr )
      j__free(Block);
    if ( !v87 )
    {
      v88 = 0;
      v170 = sub_461730(dword_8F8540);
      if ( v170 <= 0 )
        goto LABEL_104;
      while ( 1 )
      {
        if ( sub_463F10(v88) == 0 )
        {
          v89 = sub_463ED0(v88);
          if ( *(uint32_t *)(v89 + 128) == *v172 )
            break;
        }
        if ( ++v88 >= v170 )
          goto LABEL_104;
      }
    }
  }
  if ( (uint8_t)sub_41C590(dword_8F7A24) == 0 )
  {
    v90 = *(uint32_t *)(this + 48);
    v91 = *(uint32_t *)(this + 148);
    v92 = *(uint32_t *)(v90 + 20);
    v93 = *(uint32_t *)(v90 + 24);
    if ( v91 != 0 )
      v94 = (*(uint32_t *)(this + 152) - v91) >> 2;
    else
      v94 = 0;
    sub_69A5F0(*(uint32_t **)(this + 112), v92, v93 + 21 * (v94 + 1));
    *(uint8_t *)(*(uint32_t *)(this + 112) + 16) = 1;
    v170 = 15;
    sub_431230(this + 144, &v170);
  }
LABEL_104:
  v95 = v172;
  v170 = 1;
  if ( *(uint32_t *)sub_472E30(&v171, &v170) != v95[49] && (uint8_t)sub_41C590(dword_8F7A24) == 0 )
  {
    v96 = *(uint32_t *)(this + 48);
    v97 = *(uint32_t *)(this + 148);
    v98 = *(uint32_t *)(v96 + 20);
    v99 = *(uint32_t *)(v96 + 24);
    if ( v97 != 0 )
      v100 = (*(uint32_t *)(this + 152) - v97) >> 2;
    else
      v100 = 0;
    sub_69A5F0(*(uint32_t **)(this + 116), v98, v99 + 21 * (v100 + 1));
    *(uint8_t *)(*(uint32_t *)(this + 116) + 16) = 1;
    v170 = 16;
    sub_431230(this + 144, &v170);
    v95 = v172;
  }
  v170 = 2;
  if ( *(uint32_t *)sub_472E30(&v171, &v170) != v95[49] && (uint8_t)sub_41C590(dword_8F7A24) == 0 )
  {
    v101 = *(uint32_t *)(this + 48);
    v102 = *(uint32_t *)(v101 + 20);
    v103 = *(uint32_t *)(this + 148);
    v104 = *(uint32_t *)(v101 + 24);
    v170 = v102;
    if ( v103 != 0 )
      v105 = (*(uint32_t *)(this + 152) - v103) >> 2;
    else
      v105 = 0;
    sub_69A5F0(*(uint32_t **)(this + 120), v170, v104 + 21 * (v105 + 1));
    *(uint8_t *)(*(uint32_t *)(this + 120) + 16) = 1;
    v170 = 17;
    sub_431230(this + 144, &v170);
  }
  v170 = 3;
  if ( *(uint32_t *)sub_472E30(&v171, &v170) != v95[49] )
  {
    if ( sub_429900(dword_8F8500) != 0 )
    {
      if ( *(uint32_t *)(dword_8F8514 + 48) == 1 )
      {
        v113 = (void *)sub_429900(dword_8F8500);
        v114 = sub_4BF0F0(v113);
        if ( v114 != 0 && (uint8_t)sub_4BE1D0(v114) == 0 && (uint8_t)sub_41C590(dword_8F7A24) == 0 )
        {
          v115 = *(uint32_t *)(this + 48);
          v116 = *(uint32_t *)(this + 148);
          v117 = *(uint32_t *)(v115 + 20);
          v118 = *(uint32_t *)(v115 + 24);
          v110 = this + 144;
          if ( v116 != 0 )
            v119 = (*(uint32_t *)(this + 152) - v116) >> 2;
          else
            v119 = 0;
          sub_69A5F0(*(uint32_t **)(this + 128), v117, v118 + 21 * (v119 + 1));
          v112 = *(uint32_t *)(this + 128);
          v170 = 19;
          goto LABEL_132;
        }
      }
    }
    else if ( *(uint32_t *)(dword_8F8514 + 52) == 0 && (uint8_t)sub_41C590(dword_8F7A24) == 0 )
    {
      v106 = *(uint32_t *)(this + 48);
      v107 = *(uint32_t *)(this + 148);
      v108 = *(uint32_t *)(v106 + 20);
      v109 = *(uint32_t *)(v106 + 24);
      v110 = this + 144;
      if ( v107 != 0 )
        v111 = (*(uint32_t *)(this + 152) - v107) >> 2;
      else
        v111 = 0;
      sub_69A5F0(*(uint32_t **)(this + 124), v108, v109 + 21 * (v111 + 1));
      v112 = *(uint32_t *)(this + 124);
      v170 = 18;
LABEL_132:
      *(uint8_t *)(v112 + 16) = 1;
      sub_431230(v110, &v170);
      v95 = v172;
    }
  }
  v170 = 4;
  if ( *(uint32_t *)sub_472E30(&v171, &v170) != v95[49] )
  {
    sub_41C590(dword_8F7A24);
    v120 = *(uint32_t *)(this + 48);
    v121 = *(uint32_t *)(this + 148);
    v122 = *(uint32_t *)(v120 + 20);
    v123 = *(uint32_t *)(v120 + 24);
    if ( v121 != 0 )
      v124 = (*(uint32_t *)(this + 152) - v121) >> 2;
    else
      v124 = 0;
    sub_69A5F0(*(uint32_t **)(this + 132), v122, v123 + 21 * (v124 + 1));
    *(uint8_t *)(*(uint32_t *)(this + 132) + 16) = 1;
    v170 = 20;
    sub_431230(this + 144, &v170);
    v95 = v172;
  }
  v170 = 5;
  if ( *(uint32_t *)sub_472E30(&v171, &v170) != v95[49] )
  {
    sub_41C590(dword_8F7A24);
    v125 = *(uint32_t *)(this + 48);
    v126 = *(uint32_t *)(this + 148);
    v127 = *(uint32_t *)(v125 + 20);
    v128 = *(uint32_t *)(v125 + 24);
    if ( v126 != 0 )
      v129 = (*(uint32_t *)(this + 152) - v126) >> 2;
    else
      v129 = 0;
    sub_69A5F0(*(uint32_t **)(this + 136), v127, v128 + 21 * (v129 + 1));
    *(uint8_t *)(*(uint32_t *)(this + 136) + 16) = 1;
    v170 = 21;
    sub_431230(this + 144, &v170);
    v95 = v172;
  }
  v170 = 6;
  if ( *(uint32_t *)sub_472E30(&v171, &v170) != v95[49] && (uint8_t)sub_41C590(dword_8F7A24) == 0 )
  {
    v130 = *(uint32_t *)(this + 48);
    v131 = *(uint32_t *)(this + 148);
    v132 = *(uint32_t *)(v130 + 20);
    v133 = *(uint32_t *)(v130 + 24);
    if ( v131 != 0 )
      v134 = (*(uint32_t *)(this + 152) - v131) >> 2;
    else
      v134 = 0;
    sub_69A5F0(*(uint32_t **)(this + 140), v132, v133 + 21 * (v134 + 1));
    *(uint8_t *)(*(uint32_t *)(this + 140) + 16) = 1;
    v170 = 22;
    sub_431230(this + 144, &v170);
    v95 = v172;
  }
  v7 = sub_40BF00((std::_String_base *)(v95 + 32), 0, v95[37], szPassword, 0);
  if ( v7 != 0 )
  {
    if ( v95[38] < 0x10u )
      v135 = v95 + 33;
    else
      v135 = (uint32_t *)v95[33];
    LOBYTE(v7) = (*(int (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*a2 + 212))(a2, v135, -1, 0, 0);
  }
  v136 = *(uint32_t *)(this + 148);
  v137 = a2;
  if ( v136 != 0 )
  {
    v7 = (*(uint32_t *)(this + 152) - v136) >> 2;
    if ( v7 != 0 )
    {
      LOBYTE(v7) = *((uint8_t *)v95 + 184);
      if ( (uint8_t)v7 != 0 )
      {
        v138 = (int *)dword_8F7C08;
        if ( dword_8F7C08 != 0 )
        {
          v139 = (*(int (/*thiscall*/ **)(int *))(*a2 + 120))(a2);
          v140 = *v138;
          v170 = v139;
          v141 = (*(int (/*thiscall*/ **)(int *))(v140 + 120))(v138);
          if ( v141 >= v170 )
            LOBYTE(v7) = (*(int (/*thiscall*/ **)(int *, int))(*a2 + 148))(a2, 1);
          else
            LOBYTE(v7) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*a2 + 148))(a2, 0);
        }
        goto LABEL_179;
      }
    }
  }
LABEL_178:
  v137 = a2;
LABEL_179:
  v154 = *(uint32_t *)(this + 148);
  if ( v154 != 0 )
  {
    v7 = (*(uint32_t *)(this + 152) - v154) >> 2;
    if ( v7 != 0 )
    {
      *(uint32_t *)(this + 12) = dword_8F7C08 == 0
                            || (v155 = (*(int (/*thiscall*/ **)(int *))(*v137 + 120))(v137),
                                (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C08 + 120))(dword_8F7C08) >= v155);
      if ( a3 != 0 )
      {
        x = pt.x;
        y = pt.y;
      }
      else
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
        v167 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*a2 + 36))(a2) + 8);
        v158 = (*(int (/*thiscall*/ **)(int *))(*a2 + 120))(a2);
        x = sub_45E490(v158, v167) - 46;
        v166 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*a2 + 36))(a2) + 8);
        v165 = (*(int (/*thiscall*/ **)(int *))(*a2 + 128))(a2);
        v159 = (*(int (/*thiscall*/ **)(int *))(*a2 + 124))(a2);
        y = sub_45E4D0(v159, v165, v166, 1.0) - 80;
      }
      if ( x + 92 > 640 )
        x = 548;
      v160 = *(uint32_t *)(this + 148);
      if ( v160 != 0 )
        v161 = (*(uint32_t *)(this + 152) - v160) >> 2;
      else
        v161 = 0;
      if ( (unsigned int)(y + 21 * v161) > 0x1E0 )
      {
        v162 = *(uint32_t *)(this + 148);
        if ( v162 != 0 )
          v163 = (*(uint32_t *)(this + 152) - v162) >> 2;
        else
          v163 = 0;
        y = 480 - 21 * v163;
      }
      *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 1;
      sub_69A5F0(*(uint32_t **)(this + 48), x, y);
      *(uint8_t *)(this + 220) = byte_89D274;
      *(uint8_t *)(this + 221) = byte_89D275;
      LOBYTE(v7) = (uint8_t)sub_432EA0("COMMAND_SHOW", -1, 0, 0);
      *(uint32_t *)(this + 8) = a2;
      *(uint32_t *)(this + 160) = -1;
    }
  }
  return v7;
}


// ------------------------------------------------------------
// 0x527A60 sub_527A60
// ------------------------------------------------------------
// 字符串槽写入（4L → void* Src）

char /*thiscall*/ sub_527A60(int **this, void *Src)
{
  sub_4015C0(Src, strlen((const char *)Src));
  return sub_526BF0((int)this, *(this + 4), 1);
}



// ------------------------------------------------------------
// 0x527AA0 sub_527AA0
// ------------------------------------------------------------
// 比较回调（3L → BOOL）

BOOL /*cdecl*/ sub_527AA0(uint32_t *a1, uint32_t *a2)
{
  return *a1 < *a2;
}



// ------------------------------------------------------------
// 0x527AC0 sub_527AC0
// ------------------------------------------------------------
// 数据块解码（33L usercall：位流/解包，被 0x528DB0 文件加载器调用）

BOOL /*usercall*/ sub_527AC0@<eax>(unsigned int a1@<eax>, int a2@<ecx>, int a3, int a4, unsigned int *a5)
{
  unsigned int *v8; // ecx
  unsigned int *v9; // edi
  unsigned int v10; // esi
  char v11; // dl
  unsigned int v12; // eax
  int v13; // esi
  unsigned int v14; // eax
  unsigned int v15; // eax

  if ( (a1 & 3) != 0 )
    return false;
  if ( dword_9B927C == 0 )
    sub_57A1C0();
  v8 = a5;
  v9 = &a5[a1 >> 2];
  v10 = ~a2;
  if ( a5 != v9 )
  {
    do
    {
      v11 = (a4 ^ *v8) >> 6;
      *v8 = ((a4 ^ *v8) >> 6) | ((a4 ^ *v8) << 26);
      v12 = v10 >> 8;
      ++v8;
      v13 = dword_9B8E80[(uint8_t)(v10 ^ v11)];
      v14 = dword_9B8E80[(uint8_t)(v13 ^ v12 ^ *((uint8_t *)v8 - 3))] ^ ((v13 ^ v12) >> 8);
      v15 = dword_9B8E80[(uint8_t)(v14 ^ *((uint8_t *)v8 - 2))] ^ (v14 >> 8);
      v10 = dword_9B8E80[(uint8_t)(v15 ^ *((uint8_t *)v8 - 1))] ^ (v15 >> 8);
    }
    while ( v8 != v9 );
  }
  return a3 + v10 + 1 == 0;
}



// ------------------------------------------------------------
// 0x527B90 sub_527B90
// ------------------------------------------------------------
// 辅助（7L）

int /*thiscall*/ sub_527B90(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 44;
  return result;
}



// ------------------------------------------------------------
// 0x527BB0 sub_527BB0
// ------------------------------------------------------------
// 列表构造回调版 A（33L cdecl：a5=元素构造函数指针）

uint32_t */*cdecl*/ sub_527BB0(uint32_t *a1, int a2, int a3, int a4, uint8_t (/*cdecl*/ *a5)(int, int))
{
  int v5; // ecx
  int v6; // ebx
  int v7; // esi

  v5 = a2;
  v6 = (a3 - a2) / 44;
  if ( v6 <= 0 )
  {
    *a1 = a2;
    return a1;
  }
  else
  {
    while ( 1 )
    {
      v7 = v5 + 44 * (v6 / 2);
      if ( a5(v7, a4) != 0 )
      {
        a2 = v7 + 44;
        v6 += -1 - v6 / 2;
      }
      else
      {
        v6 /= 2;
      }
      if ( v6 <= 0 )
        break;
      v5 = a2;
    }
    *a1 = a2;
    return a1;
  }
}



// ------------------------------------------------------------
// 0x527C30 sub_527C30
// ------------------------------------------------------------
// 列表构造回调版 B（33L cdecl，同上变体）

uint32_t */*cdecl*/ sub_527C30(uint32_t *a1, int a2, int a3, int a4, uint8_t (/*cdecl*/ *a5)(int, int))
{
  int v5; // ecx
  int v6; // ebx
  int v7; // esi

  v5 = a2;
  v6 = (a3 - a2) / 44;
  if ( v6 <= 0 )
  {
    *a1 = a2;
    return a1;
  }
  else
  {
    while ( 1 )
    {
      v7 = v5 + 44 * (v6 / 2);
      if ( a5(a4, v7) != 0 )
      {
        v6 /= 2;
      }
      else
      {
        a2 = v7 + 44;
        v6 += -1 - v6 / 2;
      }
      if ( v6 <= 0 )
        break;
      v5 = a2;
    }
    *a1 = a2;
    return a1;
  }
}



// ------------------------------------------------------------
// 0x527CB0 sub_527CB0
// ------------------------------------------------------------
// 游标推进（13L）

int /*thiscall*/ sub_527CB0(unsigned int *this)
{
  unsigned int v2; // ecx
  unsigned int v3; // eax
  unsigned int v4; // ecx
  unsigned int v5; // esi

  v2 = *(this + 3) + *(this + 4) - 1;
  v3 = v2 >> 2;
  v4 = v2 - 4 * (v2 >> 2);
  v5 = *(this + 2);
  if ( v5 <= v3 )
    v3 -= v5;
  return *(uint32_t *)(*(this + 1) + 4 * v3) + 4 * v4;
}



// ------------------------------------------------------------
// 0x527CE0 sub_527CE0
// ------------------------------------------------------------
// 区间映射构造（40L cdecl：a5=元素构造函数）

int */*cdecl*/ sub_527CE0(int *a1, int a2, int a3, int a4, uint8_t (/*cdecl*/ *a5)(int, int))
{
  int v5; // ecx
  int v6; // edi
  int v7; // esi
  int v9; // ebx
  int v10; // ecx

  v5 = a2;
  v6 = (a3 - a2) / 44;
  if ( v6 <= 0 )
  {
LABEL_7:
    a1[1] = v5;
    *a1 = v5;
    return a1;
  }
  while ( 1 )
  {
    v7 = v5 + 44 * (v6 / 2);
    if ( a5(v7, a4) == 0 )
      break;
    a2 = v7 + 44;
    v6 += -1 - v6 / 2;
LABEL_6:
    v5 = a2;
    if ( v6 <= 0 )
      goto LABEL_7;
  }
  if ( a5(a4, v7) != 0 )
  {
    v6 /= 2;
    goto LABEL_6;
  }
  v9 = a2;
  sub_527BB0(&a2, a2, v7, a4, a5);
  sub_527C30(&a3, v7 + 44, v9 + 44 * v6, a4, a5);
  v10 = a2;
  a1[1] = a3;
  *a1 = v10;
  return a1;
}



// ------------------------------------------------------------
// 0x527DB0 sub_527DB0
// ------------------------------------------------------------
// noreturn 辅助（15L）

void /*noreturn*/ sub_527DB0()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0("invalid vector<T> subscript", 0x1Bu);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::out_of_range::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// ------------------------------------------------------------
// 0x527E20 sub_527E20
// ------------------------------------------------------------
// noreturn 辅助（15L）

void /*noreturn*/ sub_527E20()
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
// 0x527E90 sub_527E90
// ------------------------------------------------------------
// noreturn 辅助（15L）

void /*noreturn*/ sub_527E90()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0("deque<T> too long", 0x11u);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x527F00 sub_527F00
// ------------------------------------------------------------
// 容器元素迁移（34L cdecl）

int /*cdecl*/ sub_527F00(uint32_t *a1, uint32_t *a2, int a3)
{
  int v3; // edi
  uint32_t *v4; // ebx
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
    if ( v3 != 0 )
    {
      *(uint32_t *)v3 = *a1;
      *(uint32_t *)(v3 + 28) = 15;
      *(uint32_t *)(v3 + 24) = 0;
      *(uint8_t *)(v3 + 8) = 0;
      sub_4014D0((std::_String_base *)(v3 + 4), a1 + 1, 0, -1);
      *(uint32_t *)(v3 + 32) = a1[8];
      *(uint32_t *)(v3 + 36) = a1[9];
      v4 = a1;
      *(uint32_t *)(v3 + 40) = a1[10];
    }
    v3 += 44;
    LOBYTE(v7) = 0;
    a1 = v4 + 11;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x527FF0 sub_527FF0
// ------------------------------------------------------------
// 槽位数组定位（65L：a2 索引 → 槽基址）

unsigned int /*thiscall*/ sub_527FF0(int this, unsigned int a2)
{
  unsigned int v2; // edx
  unsigned int v4; // eax
  unsigned int v5; // ecx
  unsigned int v6; // edi
  int v7; // esi
  char *v8; // eax
  const void *v9; // ecx
  char *v10; // eax
  char *v11; // edx
  unsigned int v12; // ecx
  char *v13; // edi
  size_t v14; // esi
  char *v15; // eax
  unsigned int result; // eax
  size_t v17; // [esp+8h] [ebp-Ch]
  char *v18; // [esp+10h] [ebp-4h]

  v2 = a2;
  v4 = *(uint32_t *)(this + 8);
  if ( 0xFFFFFFF - v4 < a2 )
    sub_527E90(this);
  v5 = v4 >> 1;
  if ( v4 >> 1 < 8 )
    v5 = 8;
  if ( a2 < v5 && v4 <= 0xFFFFFFF - v5 )
  {
    a2 = v5;
    v2 = v5;
  }
  v6 = *(uint32_t *)(this + 12) >> 2;
  v7 = 4 * v6;
  v18 = (char *)operator new(4 * (v2 + v4));
  v17 = 4 * ((int)(4 * *(uint32_t *)(this + 8) - 4 * v6) >> 2);
  v8 = (char *)memcpy_0(&v18[4 * v6], (const void *)(4 * v6 + *(uint32_t *)(this + 4)), v17);
  v9 = *(const void **)(this + 4);
  v10 = &v8[v17];
  if ( v6 > a2 )
  {
    memcpy_0(v10, v9, 4 * ((int)(4 * a2) >> 2));
    v14 = 4 * ((int)(v7 - 4 * a2) >> 2);
    v15 = (char *)memcpy_0(v18, (const void *)(4 * a2 + *(uint32_t *)(this + 4)), v14);
    v12 = a2;
    v13 = &v15[v14];
    if ( a2 == 0 )
      goto LABEL_15;
    goto LABEL_14;
  }
  v11 = (char *)memcpy_0(v10, v9, 4 * (v7 >> 2)) + 4 * (v7 >> 2);
  if ( a2 != v6 )
    memset(v11, 0, 4 * (a2 - v6));
  if ( v6 != 0 )
  {
    v12 = v6;
    v13 = v18;
LABEL_14:
    memset(v13, 0, 4 * v12);
  }
LABEL_15:
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  result = a2 + *(uint32_t *)(this + 8);
  *(uint32_t *)(this + 4) = v18;
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x528140 sub_528140
// ------------------------------------------------------------
// 三容器操作（25L cdecl）

uint32_t */*cdecl*/ sub_528140(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ebx
  uint32_t *v4; // esi
  uint32_t *v5; // edi

  v3 = a1;
  if ( a1 != a2 )
  {
    v4 = a3 + 9;
    v5 = a1 + 9;
    do
    {
      *a3 = *v3;
      sub_4014D0((std::_String_base *)(v4 - 8), v5 - 8, 0, -1);
      *(v4 - 1) = *(v5 - 1);
      *v4 = *v5;
      v4[1] = v5[1];
      v3 += 11;
      v4 += 11;
      v5 += 11;
      a3 += 11;
    }
    while ( v3 != a2 );
  }
  return a3;
}



// ------------------------------------------------------------
// 0x5281B0 sub_5281B0
// ------------------------------------------------------------
// 容器迁移（27L cdecl）

int /*cdecl*/ sub_5281B0(int a1, int a2, int a3)
{
  int v3; // ebx
  uint32_t *v4; // edi
  uint32_t *v5; // esi
  int v6; // ecx

  v3 = a2;
  if ( a1 != a2 )
  {
    v4 = (uint32_t *)(a3 + 36);
    v5 = (uint32_t *)(a2 + 36);
    do
    {
      v6 = *(uint32_t *)(v3 - 44);
      v3 -= 44;
      v5 -= 11;
      v4 -= 11;
      *(uint32_t *)(a3 - 44) = v6;
      a3 -= 44;
      sub_4014D0((std::_String_base *)(v4 - 8), v5 - 8, 0, -1);
      *(v4 - 1) = *(v5 - 1);
      *v4 = *v5;
      v4[1] = v5[1];
    }
    while ( v3 != a1 );
  }
  return a3;
}



// ------------------------------------------------------------
// 0x528220 sub_528220
// ------------------------------------------------------------
// 容器插入（33L cdecl，44B/元素）

int /*cdecl*/ sub_528220(int a1, int a2, uint32_t *a3)
{
  int v3; // edi
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
    if ( v3 != 0 )
    {
      *(uint32_t *)v3 = *a3;
      *(uint32_t *)(v3 + 28) = 15;
      *(uint32_t *)(v3 + 24) = 0;
      *(uint8_t *)(v3 + 8) = 0;
      sub_4014D0((std::_String_base *)(v3 + 4), a3 + 1, 0, -1);
      *(uint32_t *)(v3 + 32) = a3[8];
      *(uint32_t *)(v3 + 36) = a3[9];
      *(uint32_t *)(v3 + 40) = a3[10];
    }
    v3 += 44;
    LOBYTE(v6) = 0;
    --a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x528310 sub_528310
// ------------------------------------------------------------
// 元素访问（24L thiscall）

int /*thiscall*/ sub_528310(int this, uint32_t *a2)
{
  int v3; // eax
  unsigned int v4; // eax
  unsigned int v5; // edi
  unsigned int v6; // ebx
  uint32_t *v7; // edi
  int result; // eax

  v3 = *(uint32_t *)(this + 16);
  if ( (((uint8_t)v3 + *(uint8_t *)(this + 12)) & 3) == 0 && *(uint32_t *)(this + 8) <= (unsigned int)(v3 + 4) >> 2 )
    sub_527FF0(this, 1u);
  v4 = *(uint32_t *)(this + 8);
  v5 = *(uint32_t *)(this + 16) + *(uint32_t *)(this + 12);
  v6 = v5 >> 2;
  if ( v4 <= v5 >> 2 )
    v6 -= v4;
  if ( *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) == 0 )
    *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) = operator new(0x10u);
  v7 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) + 4 * (v5 & 3));
  if ( v7 != nullptr )
    *v7 = *a2;
  result = *(uint32_t *)(this + 16) + 1;
  *(uint32_t *)(this + 16) = result;
  return result;
}



// ------------------------------------------------------------
// 0x528390 sub_528390
// ------------------------------------------------------------
// 三容器操作变体（24L cdecl）

uint32_t */*cdecl*/ sub_528390(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *v4; // ebx
  uint32_t *v5; // esi

  result = a2;
  v4 = a1;
  if ( a1 != a2 )
  {
    v5 = a1 + 9;
    do
    {
      *v4 = *a3;
      sub_4014D0((std::_String_base *)(v5 - 8), a3 + 1, 0, -1);
      *(v5 - 1) = a3[8];
      *v5 = a3[9];
      result = a2;
      v5[1] = a3[10];
      v4 += 11;
      v5 += 11;
    }
    while ( v4 != a2 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x5283F0 sub_5283F0
// ------------------------------------------------------------
// 薄转发 → sub_5281B0（3L）

int /*cdecl*/ sub_5283F0(int a1, int a2, int a3)
{
  return sub_5281B0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x528410 sub_528410
// ------------------------------------------------------------
// 区间析构（7L stdcall：44B/元素步进 sub_442C50）

int /*stdcall*/ sub_528410(int a1, int a2)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 44 )
    result = sub_442C50(i);
  return result;
}



// ------------------------------------------------------------
// 0x528440 sub_528440
// ------------------------------------------------------------
// 插入包装（4L stdcall → sub_528220）

int /*stdcall*/ sub_528440(int a1, int a2, uint32_t *a3)
{
  sub_528220(a1, a2, a3);
  return a1 + 44 * a2;
}



// ------------------------------------------------------------
// 0x528470 sub_528470
// ------------------------------------------------------------
// ★ 字符串比较/查找器（122L cdecl：三字符串参数，区间扫描）

int /*cdecl*/ sub_528470(char *a1, char *a2, char *a3)
{
  char *v3; // eax
  char *v4; // edi
  char *v5; // ebx
  char v6; // al
  bool v7; // zf
  unsigned int v8; // eax
  int v9; // ecx
  char *v10; // ecx
  int v11; // eax
  int v12; // ecx
  unsigned int v13; // ecx
  unsigned int v14; // eax
  unsigned int v15; // ecx
  char *v16; // edi
  const char *v17; // esi
  char v19[4]; // [esp+4h] [ebp-20h] BYREF
  int v20; // [esp+8h] [ebp-1Ch]
  unsigned int v21; // [esp+Ch] [ebp-18h]
  int v22; // [esp+10h] [ebp-14h]
  int v23; // [esp+14h] [ebp-10h]
  int v24; // [esp+20h] [ebp-4h]

  v3 = a1;
  if ( a1 == nullptr )
    return 0;
  v4 = a2;
  if ( a2 == nullptr )
    return 0;
  a1 = a2;
  v5 = v3;
  v20 = 0;
  v21 = 0;
  v22 = 0;
  v23 = 0;
  v24 = 0;
  sub_528310(&a1);
  while ( 1 )
  {
    v6 = *v5;
    if ( *v5 != 0 )
      break;
LABEL_12:
    ++v5;
LABEL_13:
    if ( v6 == 0 )
      goto LABEL_31;
    v8 = (unsigned int)(v22 + v23 - 1) >> 2;
    v9 = v22 + v23 - 1 - 4 * v8;
    if ( v21 <= v8 )
      v8 -= v21;
    v10 = *(char **)(*(uint32_t *)(v20 + 4 * v8) + 4 * v9);
    v11 = v4 - v10;
    if ( v4 - v10 == 1 )
    {
      v4 = v10;
      a1 = v10;
    }
    else if ( v11 == 2 && *v10 == 46 )
    {
      v4 = v10;
      a1 = v10;
    }
    else if ( v11 == 3 && *(uint16_t *)v10 == 11822 )
    {
      if ( v23 == 0 )
      {
        sub_406E40((int)v19);
        return 0;
      }
      v12 = v23 - 1;
      v23 = v12;
      if ( v12 == 0 )
        v22 = 0;
      v13 = v22 + v12 - 1;
      v14 = v13 >> 2;
      v15 = v13 - 4 * (v13 >> 2);
      if ( v21 <= v14 )
        v14 -= v21;
      v4 = *(char **)(*(uint32_t *)(v20 + 4 * v14) + 4 * v15);
      a1 = v4;
    }
    else
    {
      sub_528310(&a1);
    }
  }
  while ( 1 )
  {
    ++v5;
    if ( v6 == 0 )
      break;
    if ( v6 == 47 || v6 == 92 )
    {
      *v4++ = 47;
      a1 = v4;
      goto LABEL_13;
    }
    if ( v6 >= 65 && v6 <= 90 )
      v6 += 32;
    *v4 = v6;
    v6 = *v5;
    ++v4;
    v7 = *v5 == 0;
    a1 = v4;
    if ( v7 )
      goto LABEL_12;
  }
LABEL_31:
  *v4 = 0;
  v16 = a3;
  if ( a3 != nullptr )
  {
    v17 = *(const char **)sub_527CB0(v19);
    strcpy(v16, v17);
    if ( v17 == a2 )
      *v17 = 0;
    else
      *((uint8_t *)v17 - 1) = 0;
  }
  sub_406E40((int)v19);
  return 1;
}


// ------------------------------------------------------------
// 0x528650 sub_528650
// ------------------------------------------------------------
// ★ 列表装载（119L：Buffer 读入 + 逐项解析）

int /*thiscall*/ sub_528650(uint32_t *this, int a2, void *Buffer, unsigned int a4)
{
  char *v5; // ecx
  int v6; // ebx
  char v7; // al
  int v8; // edx
  uint32_t *v9; // esi
  const char *v10; // eax
  uint32_t *v11; // edi
  int v12; // ecx
  uint32_t *v14; // esi
  int v15; // edi
  int v16; // [esp-14h] [ebp-194h]
  int v17; // [esp-10h] [ebp-190h]
  int v18; // [esp+Ch] [ebp-174h] BYREF
  char v19[4]; // [esp+10h] [ebp-170h] BYREF
  void *Block; // [esp+14h] [ebp-16Ch]
  int v21; // [esp+24h] [ebp-15Ch]
  unsigned int v22; // [esp+28h] [ebp-158h]
  int v23; // [esp+2Ch] [ebp-154h]
  int v24; // [esp+30h] [ebp-150h]
  int v25; // [esp+34h] [ebp-14Ch]
  uint32_t *v26; // [esp+38h] [ebp-148h] BYREF
  uint32_t *v27; // [esp+3Ch] [ebp-144h]
  uint32_t *v28; // [esp+40h] [ebp-140h]
  char v29[260]; // [esp+44h] [ebp-13Ch] BYREF
  char v30[4]; // [esp+148h] [ebp-38h] BYREF
  void *v31; // [esp+14Ch] [ebp-34h]
  int v32; // [esp+15Ch] [ebp-24h]
  unsigned int v33; // [esp+160h] [ebp-20h]
  int v34; // [esp+164h] [ebp-1Ch]
  int v35; // [esp+168h] [ebp-18h]
  int v36; // [esp+16Ch] [ebp-14h]
  int v37; // [esp+170h] [ebp-10h]
  int v38; // [esp+17Ch] [ebp-4h]
  int v39; // [esp+188h] [ebp+8h]

  v37 = dword_796E50;
  v28 = this;
  v33 = 15;
  v32 = 0;
  LOBYTE(v31) = 0;
  v38 = 0;
  sub_528470(a2, v29, 0);
  v5 = v29;
  v6 = 5381;
  if ( v29[0] != 0 )
  {
    do
    {
      v7 = *v5;
      v8 = *v5++;
      v6 = v8 + 33 * v6;
    }
    while ( v7 != 0 );
  }
  v18 = v6;
  v22 = 15;
  v21 = 0;
  LOBYTE(Block) = 0;
  sub_4014D0((std::_String_base *)v19, v30, 0, -1);
  v23 = v34;
  v24 = v35;
  v25 = v36;
  v17 = *(this + 4);
  v16 = *(this + 3);
  LOBYTE(v38) = 1;
  sub_527CE0(&v26, v16, v17, &v18, sub_527AA0);
  v9 = v26;
  LOBYTE(v38) = 0;
  if ( v22 >= 0x10 )
    j__free(Block);
  if ( *v9 != v6 )
  {
    if ( v33 < 0x10 )
      return 0;
LABEL_15:
    j__free(v31);
    return 0;
  }
  v10 = (const char *)(v9 + 2);
  v11 = v9;
  v27 = (uint32_t *)v28[4];
  v39 = (int)(v9 + 2);
  while ( 1 )
  {
    if ( v11 == v27 )
    {
LABEL_14:
      if ( v33 < 0x10 )
        return 0;
      goto LABEL_15;
    }
    if ( *((uint32_t *)v10 + 5) >= 0x10u )
      v10 = *(const char **)v10;
    if ( strcmp(v10, v29) == 0 )
      break;
    v12 = v11[11];
    v11 += 11;
    v10 = (const char *)(v39 + 44);
    v39 += 44;
    if ( v12 != v6 )
      goto LABEL_14;
  }
  if ( a4 < v11[9] + 1 || (v14 = v28, fseek((FILE *)v28[6], v11[8] + *v28 + v28[1], 0) != 0) )
  {
    if ( v33 < 0x10 )
      return 0;
    goto LABEL_15;
  }
  if ( sub_66BD5A(Buffer, (v11[9] + 3) & 0xFFFFFFFC, 1u, (FILE *)v14[6]) == 0
    || sub_527AC0(v11[10], v11[10], Buffer) == 0 )
  {
    sub_501490(v30);
    return 0;
  }
  *((uint8_t *)Buffer + v11[9]) = 0;
  v15 = v11[9];
  sub_501490(v30);
  return v15;
}


// ------------------------------------------------------------
// 0x5288D0 sub_5288D0
// ------------------------------------------------------------
// 三元组读取（22L）

uint32_t */*thiscall*/ sub_5288D0(uint32_t **this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v5; // ecx
  uint32_t *v6; // eax
  int v7; // ebx
  uint32_t *v8; // edi
  int i; // esi
  uint32_t **v11; // [esp+4h] [ebp-4h]

  v5 = a3;
  v11 = this;
  if ( a3 != a4 )
  {
    v6 = sub_528140(a4, *(this + 2), a3);
    v7 = (int)*(this + 2);
    v8 = v6;
    for ( i = (int)v6; i != v7; i += 44 )
      sub_442C50(i);
    v5 = a3;
    v11[2] = v8;
  }
  *a2 = v5;
  return a2;
}



// ------------------------------------------------------------
// 0x528930 sub_528930
// ------------------------------------------------------------
// 数据项写入（133L：a2 索引 + a3 尺寸 + a4 载荷）

void /*thiscall*/ sub_528930(int *this, int a2, unsigned int a3, int *a4)
{
  int v5; // eax
  int v6; // ecx
  int v7; // ebx
  unsigned int v8; // ecx
  int v10; // eax
  int v11; // eax
  unsigned int v12; // ecx
  int v13; // eax
  char *v14; // ebx
  int v15; // eax
  unsigned int v16; // edi
  int v17; // eax
  int v18; // ecx
  int v20; // edi
  int v21; // [esp-18h] [ebp-70h]
  int v22; // [esp-10h] [ebp-68h]
  int v23; // [esp-Ch] [ebp-64h]
  unsigned int v24; // [esp-8h] [ebp-60h]
  int v25; // [esp+0h] [ebp-58h] BYREF
  void *Block; // [esp+Ch] [ebp-4Ch]
  int *v27; // [esp+10h] [ebp-48h]
  char *v28; // [esp+14h] [ebp-44h]
  int v29; // [esp+18h] [ebp-40h] BYREF
  char v30[4]; // [esp+1Ch] [ebp-3Ch] BYREF
  void *v31; // [esp+20h] [ebp-38h]
  int v32; // [esp+30h] [ebp-28h]
  unsigned int v33; // [esp+34h] [ebp-24h]
  int v34; // [esp+38h] [ebp-20h]
  int v35; // [esp+3Ch] [ebp-1Ch]
  int v36; // [esp+40h] [ebp-18h]
  int v37; // [esp+44h] [ebp-14h]
  int *v38; // [esp+48h] [ebp-10h]
  int v39; // [esp+54h] [ebp-4h]
  int v40; // [esp+60h] [ebp+8h]
  int v41; // [esp+64h] [ebp+Ch]
  int v42; // [esp+68h] [ebp+10h]

  v38 = &v25;
  v37 = dword_796E50;
  v29 = *a4;
  v27 = this;
  v33 = 15;
  v32 = 0;
  LOBYTE(v31) = 0;
  sub_4014D0((std::_String_base *)v30, a4 + 1, 0, -1);
  v5 = a4[9];
  v6 = a4[10];
  v34 = a4[8];
  v35 = v5;
  v36 = v6;
  v7 = *(this + 1);
  v39 = 0;
  if ( v7 != 0 )
    v8 = (*(this + 3) - v7) / 44;
  else
    v8 = 0;
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v10 = (*(this + 2) - v7) / 44;
    else
      v10 = 0;
    if ( 97612893 - v10 < a3 )
      sub_527E20(this);
    if ( v7 != 0 )
      v11 = (*(this + 2) - v7) / 44;
    else
      v11 = 0;
    if ( v8 >= a3 + v11 )
    {
      v18 = *(this + 2);
      v42 = v18;
      if ( (v18 - a2) / 44 >= a3 )
      {
        v40 = v18 - 44 * a3;
        *(this + 2) = sub_527F00(v40, v18, v18);
        sub_5283F0(a2, v40, v42);
        sub_528390(a2, a2 + 44 * a3, &v29);
      }
      else
      {
        sub_527F00(a2, v18, a2 + 44 * a3);
        v24 = a3 - (*(this + 2) - a2) / 44;
        v23 = *(this + 2);
        LOBYTE(v39) = 3;
        sub_528440(v23, v24, &v29);
        v20 = 44 * a3 + *(this + 2);
        *(this + 2) = v20;
        v39 = 0;
        sub_528390(a2, v20 - 44 * a3, &v29);
      }
    }
    else
    {
      if ( 97612893 - (v8 >> 1) >= v8 )
        v12 = (v8 >> 1) + v8;
      else
        v12 = 0;
      if ( v7 != 0 )
        v13 = (*(this + 2) - v7) / 44;
      else
        v13 = 0;
      if ( v12 < a3 + v13 )
        v12 = a3 + sub_527B90(this);
      v41 = 44 * v12;
      v14 = (char *)operator new(44 * v12);
      v21 = *(this + 1);
      Block = v14;
      v28 = v14;
      LOBYTE(v39) = 1;
      v28 = (char *)sub_527F00(v21, a2, v14);
      sub_528220(v28, a3, &v29);
      v22 = *(this + 2);
      v28 += 44 * a3;
      sub_527F00(a2, v22, v28);
      v15 = *(this + 1);
      if ( v15 != 0 )
        v15 = (*(this + 2) - v15) / 44;
      v16 = v15 + a3;
      v17 = *(this + 1);
      if ( v17 != 0 )
      {
        sub_528410(v17, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v14[v41];
      *(this + 2) = (int)&v14[44 * v16];
      *(this + 1) = (int)v14;
    }
  }
  if ( v33 >= 0x10 )
    j__free(v31);
}


// ------------------------------------------------------------
// 0x528C60 sub_528C60
// ------------------------------------------------------------
// 可变参/大栈参辅助（38L）

void /*thiscall*/ sub_528C60(
        int this,
        unsigned int a2,
        int a3,
        int a4,
        void *Block,
        int a6,
        int a7,
        int a8,
        int a9,
        unsigned int a10,
        int a11,
        int a12,
        int a13)
{
  int v13; // edi
  unsigned int v14; // eax
  int v15; // eax

  v13 = *(uint32_t *)(this + 4);
  if ( v13 != 0 )
    v14 = (*(uint32_t *)(this + 8) - v13) / 44;
  else
    v14 = 0;
  if ( v14 >= a2 )
  {
    if ( v13 != 0 && a2 < (*(uint32_t *)(this + 8) - v13) / 44 )
      sub_5288D0((uint32_t **)this, &a2, (uint32_t *)(v13 + 44 * a2), *(uint32_t **)(this + 8));
  }
  else
  {
    if ( v13 != 0 )
      v15 = (*(uint32_t *)(this + 8) - v13) / 44;
    else
      v15 = 0;
    sub_528930((int *)this, *(char **)(this + 8), a2 - v15, &a3);
  }
  if ( a10 >= 0x10 )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x528D30 sub_528D30
// ------------------------------------------------------------
// 加载器辅助（9L）

uint32_t */*thiscall*/ sub_528D30(uint32_t *this)
{
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *this = 0;
  *(this + 1) = 0;
  *(this + 6) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x528D50 sub_528D50
// ------------------------------------------------------------
// ★ 解码表初始化（14L：a2 参数 → sub_527AC0 用的表）

void /*thiscall*/ sub_528D50(void *this, unsigned int a2)
{
  int v2[2]; // [esp+0h] [ebp-30h] BYREF
  void *v3; // [esp+8h] [ebp-28h]
  int v4; // [esp+Ch] [ebp-24h]
  int v5; // [esp+10h] [ebp-20h]
  int v6; // [esp+14h] [ebp-1Ch]
  int v7; // [esp+20h] [ebp-10h]
  int v8; // [esp+24h] [ebp-Ch]
  int v9; // [esp+28h] [ebp-8h]
  int *v10; // [esp+2Ch] [ebp-4h]

  LOBYTE(v3) = 0;
  v10 = v2;
  sub_528C60((int)this, a2, 0, v2[1], v3, v4, v5, v6, 0, 0xFu, v7, v8, v9);
}



// ------------------------------------------------------------
// 0x528DB0 sub_528DB0
// ------------------------------------------------------------
// ★ 文件加载器【fopen 族实证】：_fsopen(FileName,"rb",16) → 魔数比对 off_7930CC
// （前 strlen 字节）→ 读 4B 计数 + 4B 尺寸 → operator new 整块读入 → sub_527AC0 解码
// → 逐项建表；失败路径 off_77F3FC(aErrorS_1) 报错（-2）

int /*thiscall*/ sub_528DB0(FILE **this, char *FileName)
{
  int result; // eax
  size_t v4; // edi
  unsigned int v5; // edx
  uint32_t *v6; // edi
  size_t *v7; // eax
  size_t *v8; // ebx
  int v9; // esi
  size_t v10; // eax
  int v11; // ecx
  size_t *v12; // esi
  size_t *v13; // ebx
  size_t v14; // edx
  uint32_t *v15; // ebx
  size_t v16; // eax
  unsigned int v17; // eax
  bool v18; // cf
  FILE *v19; // [esp-2Ch] [ebp-154h]
  size_t v20; // [esp-18h] [ebp-140h]
  FILE *v21; // [esp-10h] [ebp-138h]
  int v22; // [esp+4h] [ebp-124h] BYREF
  size_t *v23; // [esp+8h] [ebp-120h]
  size_t *v24; // [esp+Ch] [ebp-11Ch]
  uint32_t *v25; // [esp+10h] [ebp-118h]
  size_t v26; // [esp+14h] [ebp-114h]
  int v27; // [esp+18h] [ebp-110h]
  unsigned int v28; // [esp+1Ch] [ebp-10Ch] BYREF
  char Buffer[260]; // [esp+20h] [ebp-108h] BYREF
  int v30; // [esp+124h] [ebp-4h]
  unsigned int FileNamea; // [esp+130h] [ebp+8h]

  v30 = dword_796E50;
  result = (int)_fsopen(FileName, "rb", 16);
  *(this + 6) = (FILE *)result;
  if ( result != 0 )
  {
    v4 = strlen(off_7930CC);
    *this = (FILE *)((char *)*this + v4);
    sub_66BD5A(Buffer, v4, 1u, (FILE *)result);
    Buffer[v4] = 0;
    if ( strcmp(Buffer, off_7930CC) != 0 )
      return 0;
    sub_66BD5A(this + 1, 4u, 1u, *(this + 6));
    *this = (FILE *)((char *)*this + 4);
    sub_66BD5A(&v22, 4u, 1u, *(this + 6));
    v19 = *(this + 6);
    *this = (FILE *)((char *)*this + 4);
    sub_66BD5A(&v28, 4u, 1u, v19);
    v5 = v28;
    v6 = this + 2;
    *this = (FILE *)((char *)*this + 4);
    v25 = this + 2;
    sub_528D50(v5);
    v7 = (size_t *)operator new((size_t)*(this + 1));
    v21 = *(this + 6);
    v8 = v7;
    v20 = (size_t)*(this + 1);
    v24 = v7;
    if ( sub_66BD5A(v7, v20, 1u, v21) == 0 )
      return 0;
    if ( sub_527AC0(v22, v22, v8) != 0 )
    {
      FileNamea = 0;
      if ( v28 != 0 )
      {
        v27 = 0;
        while ( 1 )
        {
          v9 = v6[1];
          if ( v9 == 0
            || (v6[2] - v9) / 44 <= FileNamea
            || (v10 = *v8, v11 = v6[1], v12 = (size_t *)(v27 + v9 + 4), v13 = v8 + 1, v23 = v12, v26 = v10, v11 == 0)
            || (v6[2] - v11) / 44 <= FileNamea )
          {
            sub_527DB0(v6);
          }
          *(uint32_t *)(v27 + v11) = v26;
          v12[7] = *v13;
          v14 = v13[1];
          v15 = v13 + 1;
          v12[8] = v14;
          v16 = v15[1];
          ++v15;
          v12[9] = v16;
          v17 = v15[1];
          v15 += 2;
          qmemcpy(Buffer, v15, v17);
          v8 = (uint32_t *)((char *)v15 + v17);
          Buffer[v17] = 0;
          sub_4015C0(v23, Buffer, strlen(Buffer));
          v18 = ++FileNamea < v28;
          v27 += 44;
          if ( !v18 )
            break;
          v6 = v25;
        }
        v8 = v24;
      }
      j__free(v8);
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x529090 sub_529090
// ------------------------------------------------------------
// 加载后续（39L cdecl：a3 出参）

int /*cdecl*/ sub_529090(int a1, int a2, int *a3)
{
  int v4; // eax
  int v5; // ebx
  int v6; // esi
  int v7; // edi
  int result; // eax
  int v9; // edx
  int v10; // edx
  int v11; // [esp+18h] [ebp+Ch]
  int v12; // [esp+1Ch] [ebp+10h]

  v4 = a3[2];
  v6 = 0;
  v7 = *a3;
  v12 = a3[1];
  v5 = v12;
  v11 = a2 - 1;
  if ( v4 < v12 )
  {
    result = a1;
    while ( v6 < v11 )
    {
      *(uint8_t *)(v6 + a1) = *(uint8_t *)(v7 + a3[2]);
      v9 = a3[2];
      if ( *(uint8_t *)(v9 + v7) == 10 || v9 == v5 - 1 )
      {
        ++a3[2];
        *(uint8_t *)(v6 + a1 + 1) = 0;
        return result;
      }
      v5 = v12;
      v10 = v9 + 1;
      ++v6;
      a3[2] = v10;
      if ( v10 >= v12 )
        return 0;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x529100 sub_529100
// ------------------------------------------------------------
// ★ 文本文件装载（78L：fopen 逐行读 + 名字表构建）

char */*thiscall*/ sub_529100(uint32_t *this, const char *a2)
{
  const char *v3; // ecx
  int v4; // esi
  char v5; // al
  int v6; // edx
  bool v7; // zf
  const char *v8; // edi
  int v10; // [esp-14h] [ebp-78h]
  int v11; // [esp-10h] [ebp-74h]
  int v12; // [esp+Ch] [ebp-58h] BYREF
  char v13[4]; // [esp+10h] [ebp-54h] BYREF
  void *Block; // [esp+14h] [ebp-50h]
  int v15; // [esp+24h] [ebp-40h]
  unsigned int v16; // [esp+28h] [ebp-3Ch]
  char v17[4]; // [esp+2Ch] [ebp-38h] BYREF
  void *v18; // [esp+30h] [ebp-34h]
  int v19; // [esp+40h] [ebp-24h]
  unsigned int v20; // [esp+44h] [ebp-20h]
  int v21; // [esp+4Ch] [ebp-18h]
  int v22[2]; // [esp+50h] [ebp-14h] BYREF
  int v23; // [esp+60h] [ebp-4h]

  v3 = a2;
  v4 = 5381;
  if ( *a2 != 0 )
  {
    do
    {
      v5 = *v3;
      v6 = *v3++;
      v4 = v6 + 33 * v4;
    }
    while ( v5 != 0 );
  }
  v20 = 15;
  v19 = 0;
  LOBYTE(v18) = 0;
  sub_4015C0((void *)szPassword, 0);
  v23 = 0;
  v12 = v4;
  v16 = 15;
  v15 = 0;
  LOBYTE(Block) = 0;
  sub_4014D0((std::_String_base *)v13, v17, 0, -1);
  v11 = *(this + 9);
  v10 = *(this + 8);
  LOBYTE(v23) = 1;
  sub_4217E0(v22, v10, v11, (int)&v12, (uint8_t (/*cdecl*/ *)(int, int))sub_4212E0);
  v21 = v22[1];
  if ( v16 >= 0x10 )
    j__free(Block);
  v16 = 15;
  v15 = 0;
  LOBYTE(Block) = 0;
  v23 = -1;
  if ( v20 >= 0x10 )
    j__free(v18);
  v7 = *(uint32_t *)v22[0] == v4;
  v20 = 15;
  v19 = 0;
  LOBYTE(v18) = 0;
  if ( v7 )
  {
    if ( *(uint32_t *)(v22[0] + 28) < 0x10u )
      return (char *)(v22[0] + 8);
    else
      return *(char **)(v22[0] + 8);
  }
  else
  {
    if ( *(this + 6) < 0x10u )
      v8 = (const char *)(this + 1);
    else
      v8 = (const char *)*(this + 1);
    sprintf(byte_9B7EC0, "%s == NULL, %s : ", a2, v8);
    off_77F3FC("Error : cant find tag : %s", byte_9B7EC0);
    return byte_9B7EC0;
  }
}



// ------------------------------------------------------------
// 0x529280 sub_529280
// ------------------------------------------------------------
// ★ PVP 地图项解析（183L fastcall：a3=名字，格式化后入库；错误路径 aErrorS_1）

int /*fastcall*/ sub_529280(unsigned int a1, int a2, const char *a3, int a4, int a5, int a6)
{
  int v6; // eax
  char v8; // cl
  int v9; // edi
  int i; // edx
  char v11; // cl
  const char *v12; // esi
  bool v13; // zf
  unsigned int v14; // eax
  size_t j; // esi
  int v16; // esi
  unsigned int v17; // kr00_4
  unsigned int v18; // edx
  int v19; // ecx
  const char *v20; // esi
  int v21; // eax
  char *v22; // edx
  int v23; // eax
  char v24; // cl
  int v25; // esi
  int v26; // eax
  unsigned int v27; // edx
  int v28; // ebx
  int v29; // [esp+4h] [ebp-7Ch] BYREF
  uint8_t v30[4]; // [esp+8h] [ebp-78h] BYREF
  void *Block; // [esp+Ch] [ebp-74h]
  int v32; // [esp+1Ch] [ebp-64h]
  unsigned int v33; // [esp+20h] [ebp-60h]
  unsigned int v34; // [esp+24h] [ebp-5Ch]
  char Src[44]; // [esp+28h] [ebp-58h] BYREF
  int v36; // [esp+54h] [ebp-2Ch] BYREF
  void *v37; // [esp+58h] [ebp-28h]
  int v38; // [esp+68h] [ebp-18h]
  unsigned int v39; // [esp+6Ch] [ebp-14h]
  int v40; // [esp+70h] [ebp-10h]
  int v41; // [esp+7Ch] [ebp-4h]
  int v42; // [esp+88h] [ebp+8h]

  v40 = dword_796E50;
  v34 = a1;
  v6 = strlen(a3);
  if ( v6 == 0 )
    return 0;
  for ( ; v6 >= 1; a3[v6] = 0 )
  {
    v8 = a3[v6 - 1];
    if ( v8 != 13 && v8 != 10 )
      break;
    --v6;
  }
  v9 = 0;
  if ( v6 == 0 )
    return 0;
  for ( i = 0; i < v6; ++i )
  {
    v11 = a3[i];
    if ( v11 != 32 && v11 != 9 )
      break;
  }
  v12 = &a3[i];
  if ( a3[i] == 47 && v12[1] == 47 )
    return 0;
  v13 = i == v6;
  if ( i < v6 )
  {
    do
    {
      if ( *v12 == 62 )
        break;
      if ( i >= 40 )
        goto LABEL_21;
      ++i;
      v12[Src - a3] = *v12;
      ++v12;
    }
    while ( i < v6 );
    v9 = 0;
    v13 = i == v6;
  }
  if ( !v13 )
  {
    Src[i] = 0;
    v39 = 15;
    v38 = 0;
    LOBYTE(v37) = 0;
    v41 = 0;
    sub_4015C0((void *)&a3[i + 1], strlen(&a3[i + 1]));
    for ( j = sub_4027F0("\\n", 0, 2); j != -1; j = sub_4027F0("\\n", j, 2) )
      sub_4218A0((unsigned int *)&v36, j, 2u, "\n", 1u);
    v34 = 0;
    while ( 1 )
    {
      v42 = v9;
      v16 = *(uint32_t *)(a5 + 4);
      if ( v16 == 0 || v34 >= (*(uint32_t *)(a5 + 8) - v16) / 28 )
        break;
      v17 = strlen(Src);
      v18 = *(uint32_t *)(v9 + v16 + 20);
      if ( v18 == 0 )
        goto LABEL_38;
      v19 = *(uint32_t *)(v9 + v16 + 20);
      if ( v18 >= v17 )
        v19 = v17;
      v20 = *(uint32_t *)(v9 + v16 + 24) < 0x10u ? (const char *)(v9 + v16 + 4) : *(const char **)(v9 + v16 + 4);
      v21 = memcmp(v20, Src, v19);
      v9 = v42;
      if ( v21 == 0 )
      {
LABEL_38:
        if ( v18 >= v17 && v18 == v17 )
        {
          v32 = 0;
          LOBYTE(Block) = v18 != v17;
          v33 = 15;
          sub_4015C0(Src, strlen(Src));
          LOBYTE(v41) = 1;
          sub_416C40(v30);
          LOBYTE(v41) = 0;
          if ( v33 >= 0x10 )
            j__free(Block);
          v33 = 15;
          v32 = 0;
          LOBYTE(Block) = 0;
        }
      }
      ++v34;
      v9 += 28;
    }
    v22 = Src;
    v23 = 5381;
    if ( Src[0] != 0 )
    {
      do
      {
        v24 = *v22;
        v25 = *v22++;
        v23 = v25 + 33 * v23;
      }
      while ( v24 != 0 );
    }
    v29 = v23;
    v33 = 15;
    v32 = 0;
    LOBYTE(Block) = 0;
    sub_4014D0((std::_String_base *)v30, &v36, 0, -1);
    v26 = *(uint32_t *)(a4 + 4);
    LOBYTE(v41) = 2;
    if ( v26 != 0 )
      v27 = (*(uint32_t *)(a4 + 8) - v26) >> 5;
    else
      v27 = 0;
    if ( v26 != 0 && v27 < (*(uint32_t *)(a4 + 12) - v26) >> 5 )
    {
      v28 = *(uint32_t *)(a4 + 8);
      sub_421F90(v28, 1, &v29);
      *(uint32_t *)(a4 + 8) = v28 + 32;
    }
    else
    {
      sub_4223B0(a4, *(char **)(a4 + 8), 1u, &v29);
    }
    LOBYTE(v41) = 0;
    if ( v33 >= 0x10 )
      j__free(Block);
    v33 = 15;
    v32 = 0;
    LOBYTE(Block) = 0;
    sub_4015C0(Src, strlen(Src));
    LOBYTE(v41) = 3;
    sub_416C40(v30);
    if ( v33 >= 0x10 )
      j__free(Block);
    if ( v39 >= 0x10 )
      j__free(v37);
    return 0;
  }
LABEL_21:
  if ( *(uint32_t *)(v34 + 24) < 0x10u )
    v14 = v34 + 4;
  else
    v14 = *(uint32_t *)(v34 + 4);
  off_77F3FC(aErrorS_1, v14, Src, 40);
  return -2;
}


// ------------------------------------------------------------
// 0x529630 sub_529630
// ------------------------------------------------------------
// PVP 地图列表校验（76L：列表非空门 + sub_422AE0 排序(32B/元素, sub_4212E0 比较)）

bool /*thiscall*/ sub_529630(uint32_t *this, int a2, int a3)
{
  int v3; // eax
  char v6; // dl
  int v7; // ebx
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // edx
  unsigned int v13; // esi
  uint32_t *j; // ecx
  int v15; // [esp+0h] [ebp-10h]
  int i; // [esp+4h] [ebp-Ch]
  char ArgList[4]; // [esp+8h] [ebp-8h]
  int v18; // [esp+Ch] [ebp-4h]
  unsigned int v19; // [esp+18h] [ebp+8h]

  v3 = *(this + 12);
  if ( v3 != 0 && (*(this + 13) - v3) / 28 != 0 )
    return false;
LABEL_4:
  sub_422AE0(
    *(int **)(a2 + 4),
    *(int **)(a2 + 8),
    (*(uint32_t *)(a2 + 8) - *(uint32_t *)(a2 + 4)) >> 5,
    (uint8_t (/*cdecl*/ *)(int, int))sub_4212E0);
  v6 = 0;
  v19 = 1;
  v7 = 32;
  for ( i = 28; ; i += 28 )
  {
    v8 = *(uint32_t *)(a2 + 4);
    if ( v8 == 0 || v19 >= (*(uint32_t *)(a2 + 8) - v8) >> 5 )
      break;
    if ( *(uint32_t *)(v7 + v8) == *(uint32_t *)(v7 + v8 - 32) )
    {
      v9 = *(uint32_t *)(a3 + 4) + i;
      if ( *(uint32_t *)(v9 + 24) < 0x10u )
        v10 = v9 + 4;
      else
        v10 = *(uint32_t *)(v9 + 4);
      *(uint32_t *)ArgList = v10;
      if ( *(uint32_t *)(v9 - 4) < 0x10u )
        v11 = v9 - 24;
      else
        v11 = *(uint32_t *)(v9 - 24);
      v18 = v11;
      off_77F3FC(aErrorS_2, v10, v11);
      v15 = 9999;
      while ( 2 )
      {
        *(uint32_t *)(v7 + *(uint32_t *)(a2 + 4)) = *(uint32_t *)(*(uint32_t *)(a2 + 4) + v7) + 1;
        v12 = *(uint32_t *)(a2 + 4);
        v13 = v19 + 1;
        for ( j = (uint32_t *)(v12 + 32 * (v19 + 1)); ; j += 8 )
        {
          if ( v12 == 0 || v13 >= (*(uint32_t *)(a2 + 8) - v12) >> 5 )
          {
            off_77F3FC(aErrorS_4, *(uint32_t *)ArgList, v18);
            goto LABEL_4;
          }
          if ( *(uint32_t *)(v7 + v12) == *j )
            break;
          ++v13;
        }
        if ( --v15 != 0 )
          continue;
        break;
      }
      off_77F3FC(aErrorS_3, *(uint32_t *)ArgList, v18);
      v6 = 1;
    }
    ++v19;
    v7 += 32;
  }
  return v6 != 1;
}



// ------------------------------------------------------------
// 0x5297C0 sub_5297C0
// ------------------------------------------------------------
// 房间项插入（49L）

int /*thiscall*/ sub_5297C0(uint32_t *this, void *Src)
{
  const char *v3; // eax
  int v5; // edi
  int v6[3]; // [esp+8h] [ebp-282Ch] BYREF
  int v7[4]; // [esp+14h] [ebp-2820h] BYREF
  char v8[10240]; // [esp+24h] [ebp-2810h] BYREF
  int v9; // [esp+2824h] [ebp-10h]
  int v10; // [esp+2830h] [ebp-4h]

  v9 = dword_796E50;
  sub_4015C0(Src, strlen((const char *)Src));
  if ( *(this + 6) < 0x10u )
    v3 = (const char *)(this + 1);
  else
    v3 = (const char *)*(this + 1);
  if ( sub_442A10(szPassword, v3) == 0 )
    return -1;
  v6[0] = dword_97B204;
  v6[1] = dword_97B208;
  v6[2] = 0;
  memset(&v7[1], 0, 12);
  v10 = 0;
  if ( sub_529090((int)v8, 10240, v6) != 0 )
  {
    while ( 1 )
    {
      v5 = sub_529280((unsigned int)this, (int)v8, v8, this + 7, (int)v7, (int)(this + 11));
      if ( v5 != 0 )
        break;
      if ( sub_529090((int)v8, 10240, v6) == 0 )
        goto LABEL_9;
    }
    sub_4438D0(v7);
    return v5;
  }
  else
  {
LABEL_9:
    if ( sub_529630(this, (int)(this + 7), (int)v7) )
    {
      sub_4438D0(v7);
      return 0;
    }
    else
    {
      sub_4438D0(v7);
      return -3;
    }
  }
}



// ------------------------------------------------------------
// 0x529920 sub_529920
// ------------------------------------------------------------
// 房间项插入变体（53L）

int /*thiscall*/ sub_529920(uint32_t *this, void *Src)
{
  const char *v3; // eax
  FILE *v4; // edi
  int v6; // edi
  int v7[4]; // [esp+8h] [ebp-2824h] BYREF
  FILE *Stream; // [esp+18h] [ebp-2814h]
  char Buffer[10240]; // [esp+1Ch] [ebp-2810h] BYREF
  int v10; // [esp+281Ch] [ebp-10h]
  int v11; // [esp+2828h] [ebp-4h]

  v10 = dword_796E50;
  sub_4015C0(Src, strlen((const char *)Src));
  if ( *(this + 6) < 0x10u )
    v3 = (const char *)(this + 1);
  else
    v3 = (const char *)*(this + 1);
  v4 = fopen(v3, "r");
  Stream = v4;
  if ( v4 == nullptr )
    return -1;
  memset(&v7[1], 0, 12);
  v11 = 0;
  if ( fgets(Buffer, 10240, v4) != nullptr )
  {
    while ( 1 )
    {
      v6 = sub_529280((unsigned int)this, (int)Buffer, Buffer, this + 7, (int)v7, (int)(this + 11));
      if ( v6 != 0 )
        break;
      if ( fgets(Buffer, 10240, Stream) == nullptr )
      {
        v4 = Stream;
        goto LABEL_10;
      }
    }
    sub_4438D0(v7);
    return v6;
  }
  else
  {
LABEL_10:
    if ( sub_529630(this, (int)(this + 7), (int)v7) )
    {
      fclose(v4);
      sub_4438D0(v7);
      return 0;
    }
    else
    {
      sub_4438D0(v7);
      return -3;
    }
  }
}



// ------------------------------------------------------------
// 0x529A80 sub_529A80
// ------------------------------------------------------------
// 房间数据装载（156L：a2/a3 双容器）

int /*thiscall*/ sub_529A80(uint32_t *this, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v5; // esi
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  bool v9; // zf
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  char v13; // cl
  char v14; // cl
  char v15; // cl
  char v16; // cl
  int v18; // [esp+Ch] [ebp-4h]
  int v19; // [esp+Ch] [ebp-4h]
  uint32_t *v20; // [esp+18h] [ebp+8h]
  uint32_t *v21; // [esp+18h] [ebp+8h]
  int v22; // [esp+1Ch] [ebp+Ch]

  *a3 = 0;
  *a2 = *this;
  *a3 += 4;
  a2[1] = *(this + 1);
  *a3 += 4;
  a2[2] = *(this + 2);
  *a3 += 4;
  v5 = a2 + 3;
  v18 = 3;
  v22 = ((*((uint8_t *)this + 89) & 3) << 22)
      | ((*((uint8_t *)this + 67) & 3) << 24)
      | ((*(uint8_t *)(this + 3) & 3) << 26)
      | ((*((uint8_t *)this + 13) & 3) << 28)
      | (*((char *)this + 14) << 30);
  v6 = 21;
  v20 = (uint32_t *)((char *)this + 19);
  do
  {
    v7 = *(v20 - 1);
    if ( v7 != 0 )
    {
      *v5++ = v7;
      *a3 += 4;
    }
    else
    {
      v22 |= 1 << v6;
    }
    v8 = v6 - 1;
    if ( *v20 != 0 )
    {
      *v5++ = *v20;
      *a3 += 4;
    }
    else
    {
      v22 |= 1 << v8;
    }
    v6 = v8 - 1;
    v9 = v18 == 1;
    v20 += 2;
    --v18;
  }
  while ( !v9 );
  v21 = (uint32_t *)((char *)this + 43);
  v19 = 3;
  do
  {
    v10 = *(v21 - 1);
    if ( v10 != 0 )
    {
      *v5++ = v10;
      *a3 += 4;
    }
    else
    {
      v22 |= 1 << v6;
    }
    v11 = v6 - 1;
    if ( *v21 != 0 )
    {
      *v5++ = *v21;
      *a3 += 4;
    }
    else
    {
      v22 |= 1 << v11;
    }
    v6 = v11 - 1;
    v9 = v19 == 1;
    v21 += 2;
    --v19;
  }
  while ( !v9 );
  v12 = *(uint32_t *)((char *)this + 63);
  if ( v12 != 0 )
  {
    *v5++ = v12;
    *a3 += 4;
  }
  else
  {
    v22 |= 1 << v6;
  }
  v13 = v6 - 1;
  if ( *(this + 17) != 0 )
  {
    *(uint16_t *)v5 = *((uint16_t *)this + 34);
    v5 = (uint32_t *)((char *)v5 + 2);
    *a3 += 2;
  }
  else
  {
    v22 |= 1 << v13;
  }
  v14 = v13 - 1;
  if ( *(this + 18) != 0 )
  {
    *(uint16_t *)v5 = *((uint16_t *)this + 36);
    v5 = (uint32_t *)((char *)v5 + 2);
    *a3 += 2;
  }
  else
  {
    v22 |= 1 << v14;
  }
  v15 = v14 - 1;
  if ( *(this + 19) != 0 )
  {
    *(uint16_t *)v5 = *((uint16_t *)this + 38);
    v5 = (uint32_t *)((char *)v5 + 2);
    *a3 += 2;
  }
  else
  {
    v22 |= 1 << v15;
  }
  v16 = v15 - 1;
  if ( *(this + 20) != 0 )
  {
    *(uint16_t *)v5 = *((uint16_t *)this + 40);
    v5 = (uint32_t *)((char *)v5 + 2);
    *a3 += 2;
  }
  else
  {
    v22 |= 1 << v16;
  }
  if ( *((uint8_t *)this + 84) != 0 )
    v22 |= 1 << (v16 - 1);
  *v5 = *(uint32_t *)((char *)this + 85);
  *a3 += 4;
  *((uint8_t *)v5 + 4) = *((uint8_t *)this + 90);
  ++*a3;
  *((uint8_t *)v5 + 5) = *((uint8_t *)this + 94);
  ++*a3;
  return v22;
}


// ------------------------------------------------------------
// ============
// 【分区 4】CNRDParticle 粒子系统（《21_速查》P36/P40 实现本体）（0x529CE0-0x52B090）
// 创建器 0x529D20（"PARTICLE CREATE FAIL"）→ vmt4 出生初始化 → vmt48 轴偏移求值
// （P40：加速直线/加速+匀速/往返折返 × sin/cos 周期斜坡）→ vmt8 物理更新
// （P9 时间域 dword_7930D0 + 重力 t²/−2000000 + landing type）→ vmt14 镜像 → vmt38 冻结槽
// → 0x52A2A0 位流参数解码（.ptl 逐位解包）→ 0x52A730 复位/0x52A7B0 析构。
// ============

// 0x529CE0 sub_529CE0
// ------------------------------------------------------------
// 粒子工厂辅助（9L）

int /*thiscall*/ sub_529CE0(int this)
{
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint8_t *)(this + 152) = 0;
  *(uint32_t *)(this + 148) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x529D10 sub_529D10
// ------------------------------------------------------------
// 粒子槽清零（3L）

int /*thiscall*/ sub_529D10(void *this)
{
  return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 4))(this, 0);
}



// ------------------------------------------------------------
// 0x529D20 sub_529D20
// ------------------------------------------------------------
// ★ 粒子创建【P36 错误串实证】：dword_8F84E4->vt+12("%s%s", 前缀, 文件名) 工厂 →
// 失败 off_77F3FC("PARTICLE CREATE FAIL! FILENAME[%s%s]") → vt+12(句柄) + vt+4(0) 复位

int /*thiscall*/ sub_529D20(void *this, const char *ArgList, const char *a3)
{
  int v4; // eax

  v4 = (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E4 + 12))(dword_8F84E4, "%s%s", ArgList, a3);
  if ( v4 == 0 )
    return off_77F3FC("PARTICLE CREATE FAIL! FILENAME[%s%s]", ArgList, a3);
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 12))(this, v4);
  return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 4))(this, 0);
}



// ------------------------------------------------------------
// 0x529D80 CNRDParticle__vmt4
// ------------------------------------------------------------
// ★ CNRDParticle__vmt4 出生初始化（P36）：+152 活动位、+89 寿命上限门（超则隐藏）、
// sub_698F90(+104 时钟, +89, 寿命)（P30 时钟族）→ +33=出生时刻、位置 +1/+2/+3 → +34/+35/+36、
// +37 = (float)+94 缩放 → vt+8() 首帧推进

int /*thiscall*/ CNRDParticle__vmt4(char *this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // eax

  v3 = *(uint32_t *)this;
  *(this + 152) = 1;
  (*(void (/*stdcall*/ **)(uint32_t))(v3 + 56))(0);
  v4 = *(uint32_t *)(this + 89);
  v5 = a2;
  if ( v4 != 0 && v4 <= a2 )
  {
    v5 = *(uint32_t *)(this + 89);
    *(this + 152) = 0;
  }
  *(this + 117) = 0;
  *(this + 118) = 0;
  sub_698F90((int)(this + 104), *(uint32_t *)(this + 89), v5);
  *((uint32_t *)this + 33) = v5;
  v6 = *((uint32_t *)this + 1);
  v7 = *((uint32_t *)this + 3);
  *((uint32_t *)this + 35) = *((uint32_t *)this + 2);
  *((uint32_t *)this + 34) = v6;
  *((uint32_t *)this + 36) = v7;
  v8 = *(uint32_t *)this;
  *((float *)this + 37) = (float)*(int *)(this + 94);
  return (*(int (/*thiscall*/ **)(char *))(v8 + 8))(this);
}



// ------------------------------------------------------------
// 0x529E00 CNRDParticle__vmt48
// ------------------------------------------------------------
// ★ CNRDParticle__vmt48 轴偏移求值器（a2=轴）= 《21_速查》P40 公式本体：
// 参数块 +16·a2 起；移动类型 v4(+16·a2)：==1 直线（变速段 +67：0=纯线性 t·v0·0.001 /
// 1=梯形积分 (v0+vt)·0.5·t·0.001，超段后匀速 / 2=往返折返（周期奇偶翻转起止））；
// 否则波形：周期从 +43 渐变到 +47（2π 相位积分），v4==2 → sin(x)·amp，否则 cos(x)·amp
// （v4==0 时恒幅、amp 从 +19 渐变到 +23）

double /*thiscall*/ sub_529E00(int this, int a2)
{
  double result; // st7
  char v4; // bl
  int v5; // edx
  char v6; // al
  double v7; // st7
  int v8; // eax
  double v9; // st7
  int v10; // edi
  int v11; // eax
  bool v12; // zf
  signed int v13; // eax
  double v14; // st6
  double v15; // st5
  double v16; // st4
  long double v17; // st7
  char v18; // al
  double v19; // st7
  double v20; // st6
  int v21; // eax
  double v22; // st7
  int v23; // edi
  int v24; // eax
  bool v25; // zf
  signed int v26; // eax
  double v27; // st6
  double v28; // st5
  double v29; // st5
  double v30; // st4
  double v31; // st5
  float v32; // [esp+Ch] [ebp-4h]
  int v33; // [esp+18h] [ebp+8h]
  float v34; // [esp+18h] [ebp+8h]
  float v35; // [esp+18h] [ebp+8h]
  float v36; // [esp+18h] [ebp+8h]
  float v37; // [esp+18h] [ebp+8h]

  result = 0.0;
  v4 = *(uint8_t *)(a2 + this + 16);
  if ( v4 == 0 )
    return result;
  v5 = *(uint32_t *)(this + 67);
  if ( v4 != 1 )
  {
    v17 = 0.0;
    v34 = 1.0;
    if ( v5 != 0 )
    {
      v18 = *(uint8_t *)(this + 71);
      if ( v18 == 0 )
        goto LABEL_22;
      if ( v18 != 1 )
      {
        if ( v18 == 2 )
        {
          v23 = *(uint32_t *)(this + 67);
          v24 = *(uint32_t *)(this + 132) / v23;
          if ( v24 > 0 )
            v17 = (double)v5
                * 6.28318530717958
                / (((double)*(int *)(this + 8 * a2 + 47) + (double)*(int *)(this + 8 * a2 + 43))
                 * 0.5)
                * (double)(*(uint32_t *)(this + 132) / v23);
          v26 = v24 & 0x80000001;
          v25 = v26 == 0;
          if ( v26 < 0 )
            v25 = (((uint8_t)v26 - 1) | 0xFFFFFFFE) == -1;
          v27 = (double)(*(uint32_t *)(this + 132) % v23);
          if ( v25 )
          {
            v28 = (double)*(int *)(this + 8 * a2 + 43);
            v36 = (float)*(int *)(this + 67);
            v17 = v17
                + v27
                * 6.28318530717958
                / ((((double)*(int *)(this + 8 * a2 + 47) - v28) * v27 / v36 + v28 + v28)
                 * 0.5);
            v29 = (double)*(int *)(this + 8 * a2 + 19);
            v30 = ((double)*(int *)(this + 8 * a2 + 23) - v29) * v27 / v36;
          }
          else
          {
            v31 = (double)*(int *)(this + 8 * a2 + 47);
            v37 = (float)*(int *)(this + 67);
            v17 = v17
                + v27
                * 6.28318530717958
                / ((((double)*(int *)(this + 8 * a2 + 43) - v31) * v27 / v37 + v31 + v31)
                 * 0.5);
            v29 = (double)*(int *)(this + 8 * a2 + 23);
            v30 = ((double)*(int *)(this + 8 * a2 + 19) - v29) * v27 / v37;
          }
          v34 = v30 + v29;
        }
        goto LABEL_35;
      }
      v21 = *(uint32_t *)(this + 132);
      if ( v21 >= v5 )
      {
        v22 = (double)*(int *)(this + 8 * a2 + 47);
        v17 = (double)(v21 - *(uint32_t *)(this + 67)) * 6.28318530717958 / v22
            + (double)*(int *)(this + 67) * 6.28318530717958 / (((double)*(int *)(this + 8 * a2 + 43) + v22) * 0.5);
        v34 = (float)*(int *)(this + 8 * a2 + 23);
      }
      else
      {
LABEL_22:
        v35 = (float)*(int *)(this + 132);
        v19 = (double)*(int *)(this + 8 * a2 + 43);
        v32 = (float)*(int *)(this + 67);
        v17 = v35 * 6.28318530717958 / ((((double)*(int *)(this + 8 * a2 + 47) - v19) * v35 / v32 + v19 + v19) * 0.5);
        v20 = (double)*(int *)(this + 8 * a2 + 19);
        v34 = ((double)*(int *)(this + 8 * a2 + 23) - v20) * v35 / v32 + v20;
      }
    }
    else
    {
      v17 = (double)*(int *)(this + 132) * 6.28318530717958 / (double)*(int *)(this + 8 * a2 + 43);
      v34 = (float)*(int *)(this + 8 * a2 + 19);
    }
LABEL_35:
    if ( v4 == 2 )
      return sin(v17) * v34;
    else
      return cos(v17) * v34;
  }
  if ( v5 == 0 )
    return (double)(*(uint32_t *)(this + 132) * *(uint32_t *)(this + 8 * a2 + 19)) * 0.001;
  v6 = *(uint8_t *)(this + 71);
  switch ( v6 )
  {
    case 0:
      goto LABEL_6;
    case 1:
      v8 = *(uint32_t *)(this + 132);
      if ( v8 < v5 )
      {
LABEL_6:
        v7 = (double)*(int *)(this + 8 * a2 + 19);
        return (v7 + ((double)*(int *)(this + 8 * a2 + 23) - v7) * (double)*(int *)(this + 132) / (double)v5 + v7)
             * 0.5
             * (double)*(int *)(this + 132)
             * 0.001;
      }
      v9 = (double)*(int *)(this + 8 * a2 + 23);
      return ((double)*(int *)(this + 8 * a2 + 19) + v9) * 0.5 * (double)*(int *)(this + 67) * 0.001
           + (double)(v8 - *(uint32_t *)(this + 67)) * v9 * 0.001;
    case 2:
      v10 = *(uint32_t *)(this + 67);
      v11 = *(uint32_t *)(this + 132) / v10;
      v33 = *(uint32_t *)(this + 132) % v10;
      if ( v11 > 0 )
        result = ((double)*(int *)(this + 8 * a2 + 23) + (double)*(int *)(this + 8 * a2 + 19))
               * 0.5
               * (double)v5
               * 0.001
               * (double)(*(uint32_t *)(this + 132) / v10);
      v13 = v11 & 0x80000001;
      v12 = v13 == 0;
      if ( v13 < 0 )
        v12 = (((uint8_t)v13 - 1) | 0xFFFFFFFE) == -1;
      if ( v12 )
      {
        v14 = (double)*(int *)(this + 8 * a2 + 19);
        v15 = (double)v33;
        v16 = (double)*(int *)(this + 8 * a2 + 23);
      }
      else
      {
        v14 = (double)*(int *)(this + 8 * a2 + 23);
        v15 = (double)v33;
        v16 = (double)*(int *)(this + 8 * a2 + 19);
      }
      return result + ((v16 - v14) * v15 / (double)v5 + v14 + v14) * 0.5 * v15 * 0.001;
    default:
      break;
  }
  return result;
}


// ------------------------------------------------------------
// 0x52A1A0 sub_52A1A0
// ------------------------------------------------------------
// 向量旋转 helper：a3 度（%360≠0）→ atan2 + a3×0.0174532925199433(π/180) → sin/cos 重建 (x,y)

int /*cdecl*/ sub_52A1A0(float *a1, float *a2, int a3)
{
  int result; // eax
  long double v4; // st7
  long double v5; // st6
  long double v6; // st7
  float v7; // [esp+0h] [ebp-4h]

  result = a3 / 360;
  if ( a3 % 360 != 0 )
  {
    v4 = *a1;
    v5 = *a2;
    v7 = sqrt(v5 * v5 + v4 * v4);
    v6 = atan2(v5, v4) + (double)a3 * 0.0174532925199433;
    *a1 = cos(v6) * v7;
    *a2 = sin(v6) * v7;
    return (int)a1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x52A1F0 CNRDParticle__vmt14
// ------------------------------------------------------------
// ★ CNRDParticle__vmt14 X 轴镜像拷贝（P36⑥）：qmemcpy 本体 96B →
// x −= 2×|x−中心(+34)| 翻转 → 镜像标志取反 → 98B 输出到 a2

void */*thiscall*/ CNRDParticle__vmt14(uint32_t *this, void *a2)
{
  uint16_t *v2; // esi
  int v3; // ecx
  unsigned int v4; // eax
  uint32_t v6[26]; // [esp+8h] [ebp-68h] BYREF

  v6[25] = dword_796E50;
  qmemcpy(v6, this + 1, 0x60u);
  v2 = this + 25;
  v3 = *(this + 34);
  LOWORD(v6[24]) = *v2;
  v4 = abs32(v6[0] - v3);
  if ( v6[0] >= v3 )
    v6[0] -= 2 * v4;
  else
    v6[0] += 2 * v4;
  LOBYTE(v6[21]) = LOBYTE(v6[21]) == 0;
  qmemcpy(a2, v6, 98);
  return a2;
}



// ------------------------------------------------------------
// 0x52A270 CNRDParticle__vmt38
// ------------------------------------------------------------
// ★ CNRDParticle__vmt38 冻结设置（P36⑥ 冻结槽）：+153 变化时 sub_699030(+104) 冻结 /
// sub_698FE0(+104) 恢复（P30 时钟冻结族）—— 卡肉时粒子与本体同步定格

char /*thiscall*/ CNRDParticle__vmt38(uint8_t *this, char a2)
{
  char result; // al
  uint8_t *v3; // ecx

  result = a2;
  if ( *(this + 153) != a2 )
  {
    *(this + 153) = a2;
    v3 = this + 104;
    if ( a2 != 0 )
      return sub_699030((int)v3);
    else
      return sub_698FE0((int)v3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x52A2A0 sub_52A2A0
// ------------------------------------------------------------
// ★ 粒子参数位流解码器（.ptl 逐位解包，125L）：
// +16/+17/+18 三轴移动类型（各 2bit）、+71 changing type、+93 landing type、
// +19..31 三轴 初速/末速（bit 无效→0，有效→dword_8F8520->vt+88 随机数）、
// +43..55 三轴 初/末周期、+67 变速段、+72/+76/+80/+84 区域参数(16bit)、
// +88 逻辑标志、+89 寿命(32bit)、+94/+98 缩放起止（各 8bit）

int /*thiscall*/ sub_52A2A0(int this, unsigned int a2)
{
  int v3; // esi
  int i; // edi
  unsigned int v5; // eax
  char v6; // si
  uint32_t *v7; // edi
  uint32_t *v8; // edi
  char v9; // si
  char v10; // si
  char v11; // si
  char v12; // si
  int result; // eax
  int j; // [esp+Ch] [ebp-8h]
  int m; // [esp+Ch] [ebp-8h]
  int k; // [esp+10h] [ebp-4h] BYREF

  v3 = this + 4;
  for ( i = 3; i != 0; --i )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, v3, 4);
    v3 += 4;
  }
  v5 = a2;
  *(uint8_t *)(this + 18) = a2 >> 30;
  *(uint8_t *)(this + 17) = (v5 >> 28) & 3;
  *(uint8_t *)(this + 16) = (v5 >> 26) & 3;
  *(uint8_t *)(this + 71) = HIBYTE(v5) & 3;
  *(uint8_t *)(this + 93) = (v5 >> 22) & 3;
  v6 = 21;
  v7 = (uint32_t *)(this + 19);
  for ( j = 3; j != 0; --j )
  {
    for ( k = 2; k != 0; --k )
    {
      if ( ((v5 >> v6) & 1) != 0 )
      {
        *v7 = 0;
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, v7, 4);
        v5 = a2;
      }
      --v6;
      ++v7;
    }
  }
  v8 = (uint32_t *)(this + 43);
  for ( k = 3; k != 0; --k )
  {
    for ( m = 2; m != 0; --m )
    {
      if ( ((v5 >> v6) & 1) != 0 )
      {
        *v8 = 0;
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, v8, 4);
        v5 = a2;
      }
      --v6;
      ++v8;
    }
  }
  if ( ((v5 >> v6) & 1) != 0 )
  {
    *(uint32_t *)(this + 67) = 0;
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, this + 67, 4);
    v5 = a2;
  }
  v9 = v6 - 1;
  if ( ((v5 >> v9) & 1) != 0 )
  {
    *(uint32_t *)(this + 72) = 0;
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (char *)&k + 2, 2);
    *(uint32_t *)(this + 72) = SHIWORD(k);
    v5 = a2;
  }
  v10 = v9 - 1;
  if ( ((v5 >> v10) & 1) != 0 )
  {
    *(uint32_t *)(this + 76) = 0;
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (char *)&k + 2, 2);
    *(uint32_t *)(this + 76) = SHIWORD(k);
    v5 = a2;
  }
  v11 = v10 - 1;
  if ( ((v5 >> v11) & 1) != 0 )
  {
    *(uint32_t *)(this + 80) = 0;
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (char *)&k + 2, 2);
    *(uint32_t *)(this + 80) = SHIWORD(k);
    v5 = a2;
  }
  v12 = v11 - 1;
  if ( ((v5 >> v12) & 1) != 0 )
  {
    *(uint32_t *)(this + 84) = 0;
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (char *)&k + 2, 2);
    *(uint32_t *)(this + 84) = SHIWORD(k);
    v5 = a2;
  }
  *(uint8_t *)(this + 88) = (v5 >> (v12 - 1)) & 1;
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, this + 89, 4);
  (*(void (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (char *)&a2 + 3, 1);
  *(uint32_t *)(this + 94) = HIBYTE(a2);
  result = (*(int (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, (char *)&a2 + 3, 1);
  *(uint32_t *)(this + 98) = HIBYTE(a2);
  return result;
}


// ------------------------------------------------------------
// 0x52A4D0 CNRDParticle__vmt8
// ------------------------------------------------------------
// ★ CNRDParticle__vmt8 物理更新（P36⑤ 全公式）：+153 冻结位门 →
// +33 = sub_699000(+104 时钟)；寿命(+89) 到 → +152 活动位清零；
// 三轴速度 = vt+72(轴)（即 vmt48 求值器）；三轴角度 +19/+20/+21（%360≠0 → atan2+旋转）；
// ★ 位移 +34..36 = 基准 +1..3 − dword_7930D0[轴](P9 全局时间域 tick) × 速度 × 0.0099999998；
// ★ 重力 +36 += t² × +18 / −2000000（自由落体二次项），落低下潜类型 1/2 → 0、3 → 隐藏；
// 缩放 +37 = sub_4049C0(+94, +98, t, +89)（P30 lerp）

void /*thiscall*/ CNRDParticle__vmt8(uint32_t *this)
{
  int v2; // ebx
  int i; // edi
  long double v4; // st7
  long double v5; // st6
  long double v6; // st7
  long double v7; // st6
  long double v8; // st7
  long double v9; // st6
  int j; // edi
  int v11; // edi
  int v12; // ecx
  int v13; // eax
  char v14; // al
  float v15; // [esp+4h] [ebp-28h]
  float v16; // [esp+8h] [ebp-24h]
  float v17; // [esp+1Ch] [ebp-10h]
  float v18; // [esp+20h] [ebp-Ch]
  float v19; // [esp+24h] [ebp-8h]
  int v20; // [esp+28h] [ebp-4h]

  if ( *((uint8_t *)this + 153) == 0 )
  {
    *(this + 33) = sub_699000((int)(this + 26));
    if ( *(uint32_t *)((char *)this + 89) != 0 )
    {
      v2 = *(this + 32);
      if ( sub_699000((int)(this + 26)) >= v2 && *((uint8_t *)this + 152) != 0 )
        *((uint8_t *)this + 152) = 0;
    }
    for ( i = 0; i < 3; ++i )
      *(&v17 + i) = ((double (/*thiscall*/ *)(uint32_t *, int))*(uint32_t *)(*this + 72))(this, i);
    if ( *((uint8_t *)this + 93) != 2 || *(this + 36) != 0 )
    {
      v20 = *(this + 21);
      if ( v20 % 360 != 0 )
      {
        v4 = sqrt(v18 * v18 + v19 * v19);
        v5 = atan2(v18, v19) + (double)v20 * 0.0174532925199433;
        v19 = cos(v5) * v4;
        v18 = sin(v5) * v4;
      }
      v20 = *(this + 20);
      if ( v20 % 360 != 0 )
      {
        v6 = sqrt(v19 * v19 + v17 * v17);
        v7 = atan2(v19, v17) + (double)v20 * 0.0174532925199433;
        v17 = cos(v7) * v6;
        v19 = sin(v7) * v6;
      }
      v20 = *(this + 19);
      if ( v20 % 360 != 0 )
      {
        v8 = sqrt(v18 * v18 + v17 * v17);
        v9 = atan2(v18, v17) + (double)v20 * 0.0174532925199433;
        v17 = cos(v9) * v8;
        v18 = sin(v9) * v8;
      }
      for ( j = 0; j < 3; ++j )
      {
        if ( j != 0 || *((uint8_t *)this + 88) == 0 )
          *(this + j + 34) = *(this + j + 1) - (uint64_t)((double)dword_7930D0[j] * *(&v17 + j) * -0.0099999998);
        else
          *(this + 34) = *(this + 1) - (uint64_t)((double)dword_7930D0[0] * v17 * 0.0099999998);
      }
      v11 = *(this + 33);
      v12 = *(this + 36);
      v13 = v11 * v11 * *(this + 18) / -2000000;
      *(this + 36) = v13 + v12;
      if ( v13 + v12 < 0 )
      {
        v14 = *((uint8_t *)this + 93);
        if ( v14 == 1 || v14 == 2 )
        {
          *(this + 36) = 0;
        }
        else if ( v14 == 3 )
        {
          *((uint8_t *)this + 152) = 0;
        }
      }
      if ( *(uint32_t *)((char *)this + 89) != 0 )
      {
        v16 = (float)*(int *)((char *)this + 98);
        v15 = (float)*(int *)((char *)this + 94);
        *((float *)this + 37) = sub_4049C0(v15, v16, v11, *(uint32_t *)((char *)this + 89));
      }
    }
  }
}



// ------------------------------------------------------------
// 0x52A700 sub_52A700
// ------------------------------------------------------------
// 轴移动类型检查：+1·a2 ∈ [1,3] → BOOL

BOOL /*thiscall*/ sub_52A700(uint32_t *this, int a2)
{
  int v2; // eax

  v2 = *(this + a2 + 1);
  return v2 >= 1 && v2 <= 3;
}



// ------------------------------------------------------------
// 0x52A730 sub_52A730
// ------------------------------------------------------------
// 粒子复位：+1..+35 清零，+89..+96 = −1 哨兵（无限寿命标记）

int /*thiscall*/ sub_52A730(uint32_t *this)
{
  uint32_t *v2; // ecx

  *(this + 1) = 0;
  *(this + 6) = 0;
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
  *(this + 30) = 0;
  *(this + 31) = 0;
  *(this + 32) = 0;
  *(this + 33) = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
  *(this + 88) = 0;
  v2 = this + 89;
  *v2 = -1;
  v2[1] = -1;
  v2[2] = -1;
  v2[3] = -1;
  v2[4] = -1;
  v2[5] = -1;
  v2[6] = -1;
  v2[7] = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x52A7B0 sub_52A7B0
// ------------------------------------------------------------
// 粒子析构：各子指针（发射器/贴图/动画槽）逐个 vt+0(1) 释放（107L）

int /*thiscall*/ sub_52A7B0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  uint32_t *v9; // edi
  int i; // ebx
  void (/*thiscall*/ ***v11)(uint32_t, int); // ecx
  uint32_t *v12; // edi
  int j; // ebx
  void (/*thiscall*/ ***v14)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v15)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v16)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v17)(uint32_t, int); // ecx
  uint32_t *v18; // edi
  int k; // ebx
  void (/*thiscall*/ ***v20)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v21)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v22)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  *(this + 6) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  v4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;
  if ( v4 != nullptr )
    (**v4)(v4, 1);
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  *(this + 14) = 0;
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  v6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 16);
  *(this + 15) = 0;
  if ( v6 != nullptr )
    (**v6)(v6, 1);
  v7 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 17);
  *(this + 16) = 0;
  if ( v7 != nullptr )
    (**v7)(v7, 1);
  v8 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 18);
  *(this + 17) = 0;
  if ( v8 != nullptr )
    (**v8)(v8, 1);
  *(this + 18) = 0;
  v9 = this + 19;
  for ( i = 3; i != 0; --i )
  {
    if ( *v9 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v9)(*v9, 1);
    *v9++ = 0;
  }
  v11 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 22);
  if ( v11 != nullptr )
    (**v11)(v11, 1);
  *(this + 22) = 0;
  v12 = this + 23;
  for ( j = 2; j != 0; --j )
  {
    if ( *v12 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v12)(*v12, 1);
    *v12++ = 0;
  }
  v14 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 25);
  if ( v14 != nullptr )
    (**v14)(v14, 1);
  v15 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 26);
  *(this + 25) = 0;
  if ( v15 != nullptr )
    (**v15)(v15, 1);
  v16 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 27);
  *(this + 26) = 0;
  if ( v16 != nullptr )
    (**v16)(v16, 1);
  v17 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 28);
  *(this + 27) = 0;
  if ( v17 != nullptr )
    (**v17)(v17, 1);
  *(this + 28) = 0;
  v18 = this + 29;
  for ( k = 4; k != 0; --k )
  {
    if ( *v18 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v18)(*v18, 1);
    *v18++ = 0;
  }
  v20 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 33);
  if ( v20 != nullptr )
    (**v20)(v20, 1);
  v21 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 34);
  *(this + 33) = 0;
  if ( v21 != nullptr )
    (**v21)(v21, 1);
  v22 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 35);
  result = 0;
  *(this + 34) = 0;
  if ( v22 != nullptr )
    result = (**v22)(v22, 1);
  *(this + 35) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x52A950 sub_52A950
// ------------------------------------------------------------
// ★ PVP 房间槽位 UI 状态刷新：sub_48F5A0() 自身槽 → dword_99FEC0+槽×4+8 状态 ∈[1,3]
// → 按钮组 +15/+16/+17/+18/+22 显隐位；房间号 dword_99FEC0+108 → word_77F804 比较置可点

int /*thiscall*/ sub_52A950(int *this)
{
  int result; // eax
  int v3; // eax
  bool v4; // cl
  int v5; // eax
  int v6; // eax

  result = sub_48F5A0();
  if ( result != -1 )
  {
    v3 = *(uint32_t *)(dword_99FEC0 + 4 * result + 8);
    v4 = false;
    if ( v3 >= 1 )
      v4 = v3 <= 3;
    *(uint8_t *)(*(this + 15) + 16) = v4;
    *(uint8_t *)(*(this + 16) + 16) = !v4;
    *(uint8_t *)(*(this + 18) + 16) = 1;
    *(uint8_t *)(*(this + 17) + 16) = 0;
    *(uint8_t *)(*(this + 22) + 16) = 0;
    v5 = *(uint32_t *)(dword_99FEC0 + 108);
    if ( v5 == -1 )
      v6 = 0xFFFF;
    else
      v6 = *(uint32_t *)(dword_99FEC0 + 4 * v5 + 40);
    if ( v6 == (uint16_t)word_77F804 )
    {
      *(uint8_t *)(*(this + 15) + 17) = 1;
      result = *(this + 16);
      *(uint8_t *)(result + 17) = 1;
    }
    else
    {
      *(uint8_t *)(*(this + 15) + 17) = 0;
      result = *(this + 16);
      *(uint8_t *)(result + 17) = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x52A9F0 sub_52A9F0
// ------------------------------------------------------------
// ★ 模式切换处理【音效 TAG 实证】：+28 = a2 模式 + sub_432EA0("CLICK_BUTTON2") →
// 按钮组 +104..+136 显隐位重排（+30 选中槽 >>2 → +32 页号）

char /*thiscall*/ sub_52A9F0(int this, char a2)
{
  char v3; // dl
  int v4; // eax

  *(uint8_t *)(this + 28) = a2;
  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  v3 = *(uint8_t *)(this + 28);
  v4 = *(uint32_t *)(this + 132);
  *(uint32_t *)(this + 32) = *(uint16_t *)(this + 30) >> 2;
  *(uint8_t *)(v4 + 16) = v3 == 0;
  *(uint8_t *)(*(uint32_t *)(this + 104) + 16) = *(uint8_t *)(this + 28);
  *(uint8_t *)(*(uint32_t *)(this + 108) + 16) = *(uint8_t *)(this + 28);
  *(uint8_t *)(*(uint32_t *)(this + 116) + 16) = *(uint8_t *)(this + 28);
  *(uint8_t *)(*(uint32_t *)(this + 120) + 16) = *(uint8_t *)(this + 28);
  *(uint8_t *)(*(uint32_t *)(this + 124) + 16) = *(uint8_t *)(this + 28);
  *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = *(uint8_t *)(this + 28);
  *(uint8_t *)(*(uint32_t *)(this + 112) + 16) = *(uint8_t *)(this + 28);
  *(uint8_t *)(*(uint32_t *)(this + 136) + 16) = *(uint8_t *)(this + 28) == 0;
  LOBYTE(v4) = *(uint8_t *)(this + 28);
  if ( (uint8_t)v4 != 0 )
  {
    *(uint8_t *)(*(uint32_t *)(this + 72) + 16) = 0;
  }
  else
  {
    v4 = *(uint32_t *)(this + 72);
    *(uint8_t *)(v4 + 16) = 1;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x52AAA0 sub_52AAA0
// ------------------------------------------------------------
// ★ PVP 开战条件检查（143L）：扫 dword_99FEC0 全槽状态（排除 255/254/4/3 空位），
// 统计 1/2 两队人数与就绪人数（dword_99FEB8 准备表），两队均衡且全员就绪 → true

bool sub_52AAA0()
{
  int v0; // ebx
  uint8_t *v1; // esi
  char v3; // al
  uint8_t *v4; // edx
  int v5; // edi
  int *v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int *v12; // esi
  int v13; // ebx
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // [esp+8h] [ebp-20h]
  int v20; // [esp+Ch] [ebp-1Ch]
  int v21; // [esp+10h] [ebp-18h]
  int v22; // [esp+14h] [ebp-14h]
  int v23; // [esp+18h] [ebp-10h]
  int v24; // [esp+1Ch] [ebp-Ch]
  int v25; // [esp+20h] [ebp-8h]
  int v26; // [esp+24h] [ebp-4h]

  v0 = dword_99FEC0 + 4;
  v1 = nullptr;
  v25 = dword_99FEC0 + 4;
  if ( dword_99FEC0 == -4 )
    return false;
  v3 = sub_48F620(dword_99FEC0);
  v4 = nullptr;
  v5 = 0;
  if ( v3 != 0 )
  {
    v24 = -10092215;
    v19 = 0;
    v20 = 0;
    v21 = 0;
    v22 = 0;
    v23 = -10092214;
    while ( 1 )
    {
      v25 = 1;
      v6 = (int *)(v0 + 8);
      do
      {
        v7 = *(v6 - 1);
        if ( v7 != 255 && v7 != 254 && v7 != 4 && v7 != 3 && (uint8_t *)(v7 - 1) == v4 )
        {
          ++*(&v19 + 2 * (uint32_t)v4);
          if ( *((uint8_t *)dword_99FEB8 + (uint32_t)v1) == 1 || *(uint8_t **)(v0 + 104) == v1 )
            ++*(&v20 + 2 * (uint32_t)v4);
          ++v5;
        }
        v8 = *v6;
        if ( *v6 != 255 && v8 != 254 && v8 != 4 && v8 != 3 && (uint8_t *)(v8 - 1) == v4 )
        {
          ++*(&v19 + 2 * (uint32_t)v4);
          if ( v1[10092217] == 1 || *(uint32_t *)(v0 + 104) == v25 )
            ++*(&v20 + 2 * (uint32_t)v4);
          ++v5;
        }
        v9 = v6[1];
        if ( v9 != 255 && v9 != 254 && v9 != 4 && v9 != 3 && (uint8_t *)(v9 - 1) == v4 )
        {
          ++*(&v19 + 2 * (uint32_t)v4);
          if ( v1[10092218] == 1 || *(uint8_t **)(v0 + 104) == &v1[v24 + 10092217] )
            ++*(&v20 + 2 * (uint32_t)v4);
          ++v5;
        }
        v10 = v6[2];
        if ( v10 != 255 && v10 != 254 && v10 != 4 && v10 != 3 && (uint8_t *)(v10 - 1) == v4 )
        {
          ++*(&v19 + 2 * (uint32_t)v4);
          if ( v1[10092219] == 1 || *(uint8_t **)(v0 + 104) == &v1[v23 + 10092217] )
            ++*(&v20 + 2 * (uint32_t)v4);
          ++v5;
        }
        v1 += 4;
        v6 += 4;
        v25 += 4;
      }
      while ( v25 < 9 );
      if ( (int)++v4 >= 2 )
        break;
      v1 = nullptr;
    }
    if ( v19 == 0 || v21 == 0 || v19 != v21 )
      return false;
    return v5 == v20 + v22;
  }
  else
  {
    v26 = 0;
    v12 = (int *)(v0 + 8);
    v13 = -10092215;
    v14 = 1;
    v24 = -10092215;
    v23 = -10092214;
    while ( 1 )
    {
      v15 = *(v12 - 1);
      if ( v15 != 255 && v15 != 254 && v15 != 4 && v15 != 3 )
      {
        ++v5;
        if ( *((uint8_t *)dword_99FEB8 + (uint32_t)v4) == 1 || *(uint8_t **)(v25 + 104) == v4 )
          ++v26;
      }
      v16 = *v12;
      if ( *v12 != 255 && v16 != 254 && v16 != 4 && v16 != 3 )
      {
        ++v5;
        if ( v4[10092217] == 1 || *(uint32_t *)(v25 + 104) == v14 )
          ++v26;
      }
      v17 = v12[1];
      if ( v17 != 255 && v17 != 254 && v17 != 4 && v17 != 3 )
      {
        ++v5;
        if ( v4[10092218] == 1 || *(uint8_t **)(v25 + 104) == &v4[v13 + 10092217] )
          ++v26;
      }
      v18 = v12[2];
      if ( v18 != 255 && v18 != 254 && v18 != 4 && v18 != 3 )
      {
        ++v5;
        if ( v4[10092219] == 1 || *(uint8_t **)(v25 + 104) == &v4[v23 + 10092217] )
          ++v26;
      }
      v14 += 4;
      v4 += 4;
      v12 += 4;
      if ( v14 >= 9 )
        break;
      v13 = v24;
    }
    if ( v5 < 2 )
      return false;
    return v5 == v26;
  }
}


// ------------------------------------------------------------
// 0x52ADA0 sub_52ADA0
// ------------------------------------------------------------
// 房间槽位快照重建（80L：+89..96 = −1 起逐槽填 dword_99FEC0 状态）

int /*thiscall*/ sub_52ADA0(int *this)
{
  int v2; // ecx
  int v3; // esi
  int v4; // ebx
  uint32_t *v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  bool v9; // zf
  int result; // eax
  uint32_t *v11; // [esp+10h] [ebp-Ch]
  int v12; // [esp+14h] [ebp-8h]
  int *v13; // [esp+18h] [ebp-4h]

  v2 = dword_99FEC0;
  *(this + 89) = -1;
  *(this + 90) = -1;
  *(this + 91) = -1;
  *(this + 92) = -1;
  *(this + 93) = -1;
  *(this + 94) = -1;
  *(this + 95) = -1;
  *(this + 96) = -1;
  v3 = 0;
  v4 = 1;
  v5 = (uint32_t *)(v2 + 8);
  v12 = 1;
  v13 = this + 89;
  v11 = v5;
  do
  {
    if ( *v5 != 254 && *v5 != 255 )
    {
      if ( v3 == sub_48F5A0() )
      {
        *v13 = 0;
      }
      else
      {
        v6 = sub_48F690(v3);
        if ( v6 != 0 )
        {
          v7 = *(uint32_t *)(v6 + 196);
          if ( v7 != 0 )
          {
            v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 376))(v7);
            v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) == v8;
            v4 = v12;
            if ( v9 )
            {
              *v13 = v12;
              v4 = ++v12;
            }
          }
        }
      }
    }
    ++v3;
    v5 = ++v11;
    ++v13;
  }
  while ( v3 < 8 );
  result = -1;
  if ( *(this + 89) == -1 )
    *(this + 89) = v4++;
  if ( *(this + 90) == -1 )
    *(this + 90) = v4++;
  if ( *(this + 91) == -1 )
    *(this + 91) = v4++;
  if ( *(this + 92) == -1 )
    *(this + 92) = v4++;
  if ( *(this + 93) == -1 )
    *(this + 93) = v4++;
  if ( *(this + 94) == -1 )
    *(this + 94) = v4++;
  if ( *(this + 95) == -1 )
    *(this + 95) = v4++;
  if ( *(this + 96) == -1 )
    *(this + 96) = v4;
  return result;
}



// ------------------------------------------------------------
// 0x52AEF0 sub_52AEF0
// ------------------------------------------------------------
// 辅助（7L）

int /*thiscall*/ sub_52AEF0(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 28;
  return result;
}



// ------------------------------------------------------------
// 0x52AF20 sub_52AF20
// ------------------------------------------------------------
// 房间列表刷新（57L）

char /*thiscall*/ sub_52AF20(uint32_t *this)
{
  int v1; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // ecx

  LOBYTE(v1) = dword_99FEC0;
  if ( dword_99FEC0 != 0 )
  {
    LOBYTE(v1) = dword_8F8520;
    if ( *(uint8_t *)(dword_8F8520 + 1048645) != 0 )
    {
      *(uint8_t *)(*(this + 25) + 16) = 1;
      v3 = *(uint32_t *)(dword_99FEC0 + 108);
      if ( v3 == -1 )
        v4 = 0xFFFF;
      else
        v4 = *(uint32_t *)(dword_99FEC0 + 4 * v3 + 40);
      if ( v4 == (uint16_t)word_77F804 )
      {
        LOBYTE(v1) = sub_52AAA0();
        if ( (uint8_t)v1 != 0 )
        {
          *(uint8_t *)(*(this + 25) + 17) = 1;
          LOBYTE(v1) = sub_69C980(*(this + 88), 35, 36, 37, 28, 0, 0);
        }
        else
        {
          *(uint8_t *)(*(this + 25) + 17) = 0;
        }
      }
      else
      {
        v5 = sub_48F5A0();
        v6 = *(uint32_t *)(dword_99FEC0 + 4 * v5 + 8);
        if ( v6 == 4 || v6 == 3 )
        {
          v1 = *(this + 25);
          *(uint8_t *)(v1 + 17) = 0;
        }
        else
        {
          *(uint8_t *)(*(this + 25) + 17) = 1;
          if ( v5 == -1 || *((uint8_t *)dword_99FEB8 + v5) == 0 )
            LOBYTE(v1) = sub_69C980(*(this + 88), 32, 33, 34, 28, 0, 0);
          else
            LOBYTE(v1) = sub_69C980(*(this + 88), 29, 30, 31, 28, 0, 0);
        }
      }
    }
    else
    {
      *(uint8_t *)(*(this + 25) + 16) = 0;
    }
  }
  return v1;
}



// ------------------------------------------------------------
// 0x52B020 sub_52B020
// ------------------------------------------------------------
// 选中槽读取（25L → 槽号或 −1）

int /*thiscall*/ sub_52B020(uint32_t *this)
{
  LONG v1; // ebx
  int result; // eax
  uint32_t *v3; // edx

  v1 = dword_793118;
  result = 0;
  v3 = this + 89;
  do
  {
    if ( pt.x >= v1 )
    {
      if ( pt.x < v1 + 230
        && pt.y >= dword_79311C + dword_793120 * *v3
        && pt.y < dword_79311C + dword_793120 * (*v3 + 1) )
      {
        return result;
      }
      v1 = dword_793118;
    }
    ++result;
    ++v3;
  }
  while ( result < 8 );
  return -1;
}



// ------------------------------------------------------------
// 0x52B090 sub_52B090
// ------------------------------------------------------------
// ★ 房间进入确认（19L：+30 选中槽 → 模式/房间号校验）

char /*thiscall*/ sub_52B090(uint16_t *this)
{
  int v2; // eax
  int v3; // eax
  int v5; // [esp+4h] [ebp-4h] BYREF

  v2 = *(uint32_t *)(dword_99FEC0 + 108);
  if ( v2 == -1 )
    v3 = 0xFFFF;
  else
    v3 = *(uint32_t *)(dword_99FEC0 + 4 * v2 + 40);
  if ( v3 == (uint16_t)word_77F804 )
  {
    sub_423200(dword_8F7B08, 62);
    v5 = *(this + 15);
    sub_423290(dword_8F7B08, (int)&v5, 2);
    sub_423380(dword_8F7B08);
    LOBYTE(v3) = sub_52A9F0((int)this, 0);
  }
  return v3;
}



// ------------------------------------------------------------
// ============
// 【分区 5】CNRDPVPInterface PVP 接口（0x52B100-0x52CA40）
// vmt0 构造(402L) → 房间槽位/按钮 tick（CLICK_BUTTON2）→ 0x52C040 取当前 PVP 房间名
// （getCurrentPVPMapFileName 自证）→ std::string vector 辅助(28B/项) → 0x52CA40 大函数(556L)。
// ============

// 0x52B100 CNRDPVPInterface__vmt0
// ------------------------------------------------------------
// ★ CNRDPVPInterface__vmt0 构造（402L userpurge ecx/edi）：PVP 界面宿主初始化
// （子控件逐个 new + 布局 + 房间列表容器），dword_99FEC0 管理器挂接

void /*userpurge*/ sub_52B100(int a1@<ecx>, int a2@<edi>, int a3)
{
  uint32_t *v3; // ebx
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // ecx
  int v18; // ecx
  int v19; // eax
  bool v20; // cc
  int v21; // eax
  int v22; // edi
  int v23; // ebx
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // edi
  int v28; // ebx
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // edi
  int v33; // ebx
  int v34; // eax
  int v35; // edx
  int v36; // edi
  int v37; // ebx
  int v38; // eax
  int v39; // eax
  int v40; // edi
  uint32_t *v41; // eax
  int v42; // eax
  int v43; // edi
  int v44; // ebx
  int v45; // eax
  int v46; // eax
  unsigned int v47; // ebx
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // ebx
  int v52; // eax
  int v53; // edi
  int v54; // edx
  int v55; // edi
  int v56; // eax
  int v57; // eax
  int v58; // eax
  int v59; // eax
  char v60; // al
  int v61; // esi
  int v62; // edi
  int v63; // esi
  int v64; // eax
  int v65; // eax
  int v66; // [esp-18h] [ebp-38h]
  int v67; // [esp-18h] [ebp-38h]
  int v68; // [esp-8h] [ebp-28h]
  int v69; // [esp-8h] [ebp-28h]
  int v70; // [esp-8h] [ebp-28h]
  int v71; // [esp-8h] [ebp-28h]
  int v72; // [esp-8h] [ebp-28h]
  int v73; // [esp-8h] [ebp-28h]
  int v75; // [esp+8h] [ebp-18h]
  unsigned int v76; // [esp+8h] [ebp-18h]
  int v77; // [esp+8h] [ebp-18h]
  uint32_t *v78; // [esp+Ch] [ebp-14h]
  int v79; // [esp+10h] [ebp-10h]
  uint32_t *v80; // [esp+14h] [ebp-Ch]
  int v81; // [esp+18h] [ebp-8h]
  int v82; // [esp+1Ch] [ebp-4h]
  int v83; // [esp+28h] [ebp+8h]
  int v84; // [esp+28h] [ebp+8h]
  int v85; // [esp+28h] [ebp+8h]
  int v86; // [esp+28h] [ebp+8h]
  int v87; // [esp+28h] [ebp+8h]
  int v88; // [esp+28h] [ebp+8h]

  v3 = (uint32_t *)dword_99FEC0;
  if ( dword_99FEC0 != 0 )
  {
    if ( a3 == *(uint32_t *)(a1 + 24) )
    {
      v75 = dword_99FEC0 + 4;
      v81 = dword_99FEC0;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 248);
      v5 = v3[19];
      if ( v5 != 0 )
      {
        v83 = dword_99FEC4[v5];
      }
      else if ( v3[26] < 0x10u )
      {
        v83 = (int)(v3 + 21);
      }
      else
      {
        v83 = v3[21];
      }
      v6 = *(uint32_t *)dword_79C0B0;
      v7 = sub_48F4C0(v3);
      v8 = sub_48FBB0(v3, v7);
      (*(void (**)(int, int, int, int, const char *, ...))(v6 + 80))(
        dword_79C0B0,
        424,
        28,
        -4134672,
        "%s (%d/%d)",
        v83,
        v8);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v9 = sub_418DD0(*(uint32_t *)(v75 + 108) + 94);
      if ( v9 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, 388, 57, dword_79C0B0);
      if ( *(uint8_t *)(a1 + 28) != 0 )
      {
        v25 = sub_418DD0(72);
        if ( v25 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v25 + 152))(v25, 382, 127, dword_79C0B0);
        v26 = *(uint32_t *)(a1 + 132);
        v27 = *(uint32_t *)(v26 + 24);
        v28 = *(uint32_t *)(v26 + 20);
        v29 = sub_418DD0(70);
        if ( v29 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v29 + 152))(v29, v28, v27, dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 144);
        v30 = *(uint32_t *)(a1 + 40);
        if ( v30 != 0 )
          v30 = (*(uint32_t *)(a1 + 44) - v30) / 28;
        (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          494,
          308,
          -9830451,
          "%d/%d",
          *(uint32_t *)(a1 + 32) + 1,
          ((unsigned int)(v30 + 1) >> 2) + 1);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      }
      else
      {
        v10 = dword_793118;
        v82 = 0;
        v79 = 100;
        v80 = (uint32_t *)(v75 + 4);
        v78 = (uint32_t *)(a1 + 356);
        do
        {
          v11 = dword_79311C + dword_793120 * *v78;
          if ( *v80 == 254 )
          {
            v12 = sub_418DD0(19);
            if ( v12 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(v12, v10, v11, dword_79C0B0);
          }
          else if ( *v80 != 255 )
          {
            v13 = sub_48F690(v82);
            v84 = v13;
            if ( v13 != 0 )
            {
              v14 = sub_42B340(v13);
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, int))(*(uint32_t *)v14 + 384))(
                v14,
                v10,
                v11,
                16,
                16,
                1065353216,
                a2);
              sub_491530(2, 0);
              v15 = sub_42A430(v84);
              if ( v15 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v15 + 152))(
                  v15,
                  v10 + 19,
                  v11 - 1,
                  dword_79C0B0);
              sub_491630(2);
              v16 = sub_42A410(v84);
              if ( v16 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v16 + 152))(
                  v16,
                  v10 + 19,
                  v11 - 1,
                  dword_79C0B0);
              a2 = a1 + 196;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);
              if ( *(uint32_t *)(v84 + 40) < 0x10u )
                v17 = v84 + 20;
              else
                v17 = *(uint32_t *)(v84 + 20);
              (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
                dword_79C0B0,
                v10 + 55,
                v11 + 4,
                -9795152,
                v17);
              if ( *(uint32_t *)(v84 + 40) < 0x10u )
                v18 = v84 + 20;
              else
                v18 = *(uint32_t *)(v84 + 20);
              (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
                dword_79C0B0,
                v10 + 55,
                v11 + 3,
                -16179413,
                v18);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
              if ( (uint8_t)sub_452580(v82) != 0 )
              {
                v85 = v11 + 2;
                v68 = sub_418DD0(dword_7930F8);
                sub_40FC80(v10 + 158, v11 + 2, v68);
              }
              else
              {
                v85 = v11 + 2;
                if ( (uint8_t)sub_52A700(v82) != 0 )
                  v69 = sub_418DD0(dword_7930D4[3 * *v80]);
                else
                  v69 = sub_418DD0(v79);
                sub_40FC80(v10 + 158, v85, v69);
              }
              if ( sub_445080(v82) != 0 )
              {
                v70 = sub_418DD0(44);
                sub_40FC80(v10 + 201, v11 + 3, v70);
              }
              else if ( *(uint32_t *)(v81 + 108) == v82 )
              {
                v71 = sub_418DD0(38);
                sub_40FC80(v10 + 201, v11 - 2, v71);
              }
              else if ( *((uint8_t *)&dword_99FEB8 + v82) != 0 )
              {
                sub_491530(2, 0);
                v19 = sub_418DD0(17);
                sub_40FC80(v10 + 198, v11 - 1, v19);
                sub_491630(2);
                v72 = sub_418DD0(16);
                sub_40FC80(v10 + 201, v85, v72);
              }
              else
              {
                v73 = sub_418DD0(18);
                sub_40FC80(v10 + 201, v11, v73);
              }
            }
          }
          ++v82;
          v20 = v79 + 2 < 116;
          v79 += 2;
          ++v78;
          ++v80;
        }
        while ( v20 );
        v21 = *(uint32_t *)(a1 + 100);
        if ( *(uint8_t *)(v21 + 16) == 0 )
        {
          v22 = *(uint32_t *)(v21 + 24);
          v23 = *(uint32_t *)(v21 + 20);
          v24 = sub_418DD0(43);
          if ( v24 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v24 + 152))(v24, v23, v22, dword_79C0B0);
        }
      }
      v31 = *(uint32_t *)(a1 + 60);
      if ( *(uint8_t *)(v31 + 16) == 0 )
      {
        v32 = *(uint32_t *)(v31 + 24);
        v33 = *(uint32_t *)(v31 + 20);
        v34 = sub_418DD0(21);
        if ( v34 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v34 + 152))(v34, v33, v32, dword_79C0B0);
      }
      v35 = *(uint32_t *)(a1 + 64);
      if ( *(uint8_t *)(v35 + 16) == 0 )
      {
        v36 = *(uint32_t *)(v35 + 24);
        v37 = *(uint32_t *)(v35 + 20);
        v38 = sub_418DD0(25);
        if ( v38 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v38 + 152))(v38, v37, v36, dword_79C0B0);
      }
      v39 = sub_418DD0(71);
      if ( v39 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v39 + 152))(v39, 452, 108, dword_79C0B0);
    }
    else if ( *(uint8_t *)(a1 + 28) != 0 )
    {
      v40 = 0;
      v41 = (uint32_t *)(a1 + 116);
      while ( *v41 != a3 )
      {
        ++v40;
        ++v41;
        if ( v40 >= 4 )
          goto LABEL_63;
      }
      v46 = *(uint32_t *)(a1 + 40);
      v47 = v40 + 4 * *(uint32_t *)(a1 + 32);
      v76 = v47;
      if ( v46 != 0 && v47 < (*(uint32_t *)(a1 + 44) - v46) / 28 )
      {
        v48 = *(uint32_t *)(a1 + 4 * v40 + 116);
        if ( v47 == *(uint16_t *)(a1 + 30) )
        {
          v86 = *(uint32_t *)(v48 + 24);
          v77 = *(uint32_t *)(v48 + 20);
          v49 = sub_418DD0(74);
          if ( v49 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v49 + 152))(v49, v77, v86, dword_79C0B0);
        }
        else if ( *(uint8_t *)(v48 + 17) != 0 && dword_79BE3C == *(uint32_t *)(v48 + 12) )
        {
          v50 = *(uint32_t *)(a1 + 4 * v40 + 116);
          v51 = *(uint32_t *)(v50 + 24);
          v87 = *(uint32_t *)(v50 + 20);
          v52 = sub_418DD0(74);
          sub_43B560(v87, v51, v52, 1065353216, 1065353216, 0, -1258291201, 1333788672, 1333788672);
          v47 = v76;
        }
        v53 = *(uint32_t *)(a1 + 4 * v40 + 116);
        v54 = *(uint32_t *)(v53 + 24);
        v55 = *(uint32_t *)(v53 + 20);
        v88 = v54;
        v56 = sub_418DD0(v47 + 88);
        if ( v56 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v56 + 152))(v56, v55 + 3, v88 + 3, dword_79C0B0);
      }
    }
    else
    {
LABEL_63:
      v42 = *(uint32_t *)(a1 + 56);
      if ( a3 == v42 )
      {
        if ( *(uint8_t *)(v42 + 17) != 0 && dword_79BE3C == *(uint32_t *)(v42 + 12) )
        {
          v43 = *(uint32_t *)(v42 + 24);
          v44 = *(uint32_t *)(v42 + 20);
          v45 = sub_418DD0(87);
          if ( v45 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v45 + 152))(v45, v44 - 16, v43 - 33, dword_79C0B0);
        }
      }
      else if ( a3 == *(uint32_t *)(a1 + 140) )
      {
        if ( (uint8_t)sub_43BCB0(*(uint32_t *)(a1 + 136)) != 0 )
        {
          v57 = sub_422E70(449);
          sub_4649B0(510, 321, -1, -16777216, 2, v57, 0, 0, 1600, 0);
        }
        else if ( (uint8_t)sub_43BCB0(*(uint32_t *)(a1 + 60)) != 0 )
        {
          v58 = sub_422E70(450);
          sub_4649B0(483, 364, -1, -16777216, 2, v58, 0, 0, 1600, 0);
        }
        else if ( (uint8_t)sub_43BCB0(*(uint32_t *)(a1 + 64)) != 0 )
        {
          v59 = sub_422E70(451);
          sub_4649B0(537, 364, -1, -16777216, 2, v59, 0, 0, 1600, 0);
        }
        else if ( (uint8_t)sub_43BCB0(*(uint32_t *)(a1 + 72)) != 0 )
        {
          v60 = sub_48F620(v3);
          v61 = *(uint32_t *)(a1 + 72);
          v62 = *(uint32_t *)(v61 + 24);
          v63 = *(uint32_t *)(v61 + 20);
          if ( v60 != 0 )
            v64 = sub_422E70(452);
          else
            v64 = sub_422E70(453);
          sub_4649B0(v63 - 10, v62, -1, -16777216, 2, v64, 0, 0, 1600, 0);
        }
        else if ( (uint8_t)sub_43BCB0(*(uint32_t *)(a1 + 132)) != 0 )
        {
          v65 = sub_422E70(454);
          sub_4649B0(503, 112, -1, -16777216, 2, v65, 0, 0, 1600, 0);
        }
        else if ( (uint8_t)sub_43BCB0(*(uint32_t *)(a1 + 84)) != 0 )
        {
          v66 = sub_422E70(455);
          sub_4649B0(505, 202, -1, -16777216, 2, v66, 0, 0, 1600, 0);
        }
        else if ( (uint8_t)sub_43BCB0(*(uint32_t *)(a1 + 96)) != 0 )
        {
          v67 = sub_422E70(456);
          sub_4649B0(505, 188, -1, -16777216, 2, v67, 0, 0, 1600, 0);
        }
      }
    }
  }
}


// ------------------------------------------------------------
// 0x52BA80 sub_52BA80
// ------------------------------------------------------------
// ★ 房间槽位滚动/点击 tick（61L）【音效 TAG 实证】：+104/+108 按钮命中 →
// CLICK_BUTTON2 + +32 页号 ±1（28B/项步进）→ 四按钮显隐 → 选中槽 +30 更新 → 0x52B090

char /*thiscall*/ sub_52BA80(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  unsigned int v6; // ecx
  int v7; // edi
  int v8; // ebx
  unsigned int v9; // edi
  int v10; // eax
  int v11; // eax
  int v13; // [esp+4h] [ebp-4h]

  v2 = *(uint32_t *)(this + 104);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    v3 = *(uint32_t *)(this + 32);
    if ( v3 > 0 )
    {
      *(uint32_t *)(this + 32) = v3 - 1;
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
  }
  v4 = *(uint32_t *)(this + 108);
  if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) )
  {
    v5 = *(uint32_t *)(this + 40);
    if ( v5 != 0 )
      v5 = (*(uint32_t *)(this + 44) - v5) / 28;
    v6 = *(uint32_t *)(this + 32);
    if ( v6 < (unsigned int)(v5 + 1) >> 2 )
    {
      *(uint32_t *)(this + 32) = v6 + 1;
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
  }
  v7 = 0;
  v13 = 0;
  v8 = this + 116;
  while ( 1 )
  {
    v9 = v7 + 4 * *(uint32_t *)(this + 32);
    v10 = *(uint32_t *)(this + 40);
    if ( v10 != 0 && v9 < (*(uint32_t *)(this + 44) - v10) / 28 )
      break;
    *(uint8_t *)(*(uint32_t *)v8 + 16) = 0;
LABEL_17:
    v7 = v13 + 1;
    v8 += 4;
    if ( ++v13 >= 4 )
      goto LABEL_20;
  }
  *(uint8_t *)(*(uint32_t *)v8 + 16) = 1;
  if ( *(uint8_t *)(*(uint32_t *)v8 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*(uint32_t *)v8 + 12) )
    goto LABEL_17;
  *(uint16_t *)(this + 30) = v9;
LABEL_20:
  v11 = *(uint32_t *)(this + 112);
  if ( *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v11 + 12) )
    LOBYTE(v11) = sub_52B090((uint16_t *)this);
  return v11;
}



// ------------------------------------------------------------
// 0x52BBB0 sub_52BBB0
// ------------------------------------------------------------
// ★ 房间交互主 tick（241L）【音效 TAG 实证】：+24 按钮使能 && dword_99FEC0 →
// word_77F804 房间号比对 → 0x52B020 选槽（排除自身 sub_48F5A0）→ 状态 254/255 翻转
// (sub_48F500) / 否则 sub_44E8D0(0x28) 弹确认 → CLICK_BUTTON2

char /*thiscall*/ sub_52BBB0(int this)
{
  int v2; // edx
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edx
  uint32_t *v17; // esi
  char *v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  bool v23; // zf
  int v24; // eax
  char v25; // al
  int v26; // edx
  int v27; // esi
  int v28; // ecx
  int v29; // eax
  int v30; // esi
  int v31; // ecx
  int v32; // esi
  int v33; // eax
  int v34; // eax
  int v35; // eax
  bool v37[4]; // [esp+4h] [ebp-4h] BYREF

  v2 = *(uint32_t *)(this + 24);
  LOBYTE(v3) = *(uint8_t *)(v2 + 16);
  if ( (uint8_t)v3 == 0 )
    return v3;
  if ( dword_99FEC0 == 0 )
    return v3;
  v4 = *(uint32_t *)(this + 4);
  v5 = *(uint32_t *)(v4 + 808);
  v6 = v4 + 804;
  if ( v5 != 0 )
  {
    v3 = (*(uint32_t *)(v6 + 8) - v5) >> 2;
    if ( v3 != 0 )
      return v3;
  }
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    v7 = *(uint32_t *)(dword_99FEC0 + 108);
    v8 = v7 == -1 ? 0xFFFF : *(uint32_t *)(dword_99FEC0 + 4 * v7 + 40);
    if ( v8 == (uint16_t)word_77F804 && *(uint8_t *)(this + 28) == 0 )
    {
      v9 = sub_52B020(this);
      if ( v9 != -1 && v9 != sub_48F5A0() )
      {
        v10 = *(uint32_t *)(dword_99FEC0 + 4 * v9 + 8);
        if ( v10 == 254 )
        {
          sub_48F500(v9, 255);
        }
        else if ( v10 == 255 )
        {
          if ( sub_48F4C0(dword_99FEC0) > 2 )
            sub_48F500(v9, 254);
        }
        else
        {
          sub_44E8D0(*(char **)(this + 4), (void *)0x28, 0, *(uint32_t *)(dword_99FEC0 + 4 * v9 + 40));
        }
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
    }
  }
  v11 = *(uint32_t *)(this + 132);
  if ( *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v11 + 12) )
  {
    v12 = *(uint32_t *)(dword_99FEC0 + 108);
    v13 = v12 == -1 ? 0xFFFF : *(uint32_t *)(dword_99FEC0 + 4 * v12 + 40);
    if ( v13 == (uint16_t)word_77F804 )
    {
      sub_52A9F0(*(uint8_t *)(this + 28) == 0);
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
  }
  if ( *(uint8_t *)(this + 28) == 0 )
  {
    v14 = *(uint32_t *)(this + 60);
    if ( *(uint8_t *)(v14 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v14 + 12) )
    {
      sub_423200(dword_8F7B08, 57);
      v37[0] = false;
      sub_423290(v37, 1);
    }
    else
    {
      if ( (uint8_t)sub_43B500(*(uint32_t *)(this + 64)) == 0 )
        goto LABEL_36;
      sub_423200(dword_8F7B08, 57);
      v37[0] = true;
      sub_423290(v37, 1);
    }
    sub_423380(dword_8F7B08);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    goto LABEL_36;
  }
  sub_52BA80(this);
LABEL_36:
  v15 = *(uint32_t *)(this + 136);
  if ( *(uint8_t *)(v15 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v15 + 12) )
  {
    v16 = *(uint32_t *)(this + 12);
    if ( v16 != 0 && (*(uint32_t *)(this + 16) - v16) >> 2 != 0 )
    {
      sub_44E8D0((char *)dword_8F8528, (void *)0x2A, this + 8, 0);
    }
    else
    {
      v17 = *(uint32_t **)(*(uint32_t *)(this + 4) + 28);
      v18 = sub_422E70(448);
      sub_43BEE0(v17, (int)v18, -6567706, 0, -1);
    }
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v19 = *(uint32_t *)(this + 56);
  if ( *(uint8_t *)(v19 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v19 + 12) )
  {
    v20 = sub_48F5A0();
    if ( v20 != -1 )
      sub_48F500(v20, 254);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v21 = *(uint32_t *)(this + 72);
  if ( *(uint8_t *)(v21 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v21 + 12) )
  {
    if ( (uint8_t)sub_48F620(dword_99FEC0) != 0 )
    {
      *(uint8_t *)(*(uint32_t *)(this + 68) + 16) = *(uint8_t *)(*(uint32_t *)(this + 68) + 16) == 0;
    }
    else
    {
      v22 = *(uint32_t *)(this + 88);
      v23 = *(uint8_t *)(v22 + 16) != 0;
      *(uint8_t *)(v22 + 16) = *(uint8_t *)(v22 + 16) == 0;
      if ( !v23 )
      {
        v24 = sub_48F5A0();
        sub_69C980(
          *(uint32_t *)(this + 92),
          *(uint32_t *)(this + 352),
          2 * v24 + 101,
          2 * v24 + 100,
          2 * v24 + 100,
          -1,
          0,
          0);
      }
    }
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v25 = sub_48F620(dword_99FEC0);
  v26 = dword_79BE34;
  v27 = 0;
  if ( v25 != 0 )
  {
    v28 = this + 76;
    while ( *(uint8_t *)(*(uint32_t *)v28 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*(uint32_t *)v28 + 12) )
    {
      ++v27;
      v28 += 4;
      if ( v27 >= 3 )
        goto LABEL_72;
    }
    *(uint8_t *)(*(uint32_t *)(this + 68) + 16) = 0;
    v29 = sub_48F5A0();
    if ( v29 == -1 )
      goto LABEL_71;
    v30 = v27 + 1;
    goto LABEL_70;
  }
  v31 = this + 92;
  while ( *(uint8_t *)(*(uint32_t *)v31 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*(uint32_t *)v31 + 12) )
  {
    ++v27;
    v31 += 4;
    if ( v27 >= 2 )
      goto LABEL_72;
  }
  *(uint8_t *)(*(uint32_t *)(this + 88) + 16) = 0;
  v29 = sub_48F5A0();
  if ( v29 != -1 )
  {
    v30 = v27 != 0 ? 4 : 0;
LABEL_70:
    sub_48F500(v29, v30);
  }
LABEL_71:
  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  v26 = dword_79BE34;
LABEL_72:
  v3 = *(uint32_t *)(this + 100);
  if ( *(uint8_t *)(v3 + 17) != 0 && v26 == *(uint32_t *)(v3 + 12) )
  {
    v3 = sub_48F5A0();
    v32 = v3;
    if ( v3 != -1 )
    {
      v33 = *(uint32_t *)(dword_99FEC0 + 108);
      if ( v33 == -1 )
        v34 = 0xFFFF;
      else
        v34 = *(uint32_t *)(dword_99FEC0 + 4 * v33 + 40);
      if ( v34 == (uint16_t)word_77F804 )
      {
        if ( (uint8_t)sub_52AAA0(this) == 0 )
        {
LABEL_81:
          LOBYTE(v3) = (uint8_t)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
          return v3;
        }
      }
      else
      {
        v35 = *(uint32_t *)(dword_99FEC0 + 4 * v32 + 8);
        if ( v35 == 4 || v35 == 3 )
          goto LABEL_81;
      }
      sub_44E850(dword_8F8528, 40);
      sub_423200(dword_8F7B08, 56);
      v37[0] = *((uint8_t *)&dword_99FEB8 + v32) == 0;
      sub_423290(v37, 1);
      sub_423380(dword_8F7B08);
      goto LABEL_81;
    }
  }
  return v3;
}


// ------------------------------------------------------------
// 0x52C040 sub_52C040
// ------------------------------------------------------------
// ★ 取当前 PVP 房间名（IDA 符号 CNRDPVPInterface::getCurrentPVPMapFileName 自证）：
// dword_99FEC0+116 = 房间名索引 → 房间名 vector(28B/项 std::string) 第 i 项（SSO：+24<0x10 内联），
// 非 PVP 模式 → off_77F3FC(aErrorPvpModeCn) 报错并返回 szPassword

const CHAR */*thiscall*/ sub_52C040(uint32_t *this)
{
  int v2; // edx
  int v3; // eax
  unsigned int v4; // ecx
  int v5; // eax

  if ( dword_99FEC0 != 0 )
  {
    v2 = *(this + 10);
    v3 = 28 * *(uint32_t *)(dword_99FEC0 + 116);
    v4 = *(uint32_t *)(v3 + v2 + 24);
    v5 = v2 + v3;
    if ( v4 < 0x10 )
      return (const CHAR *)(v5 + 4);
    else
      return *(const CHAR **)(v5 + 4);
  }
  else
  {
    off_77F3FC(aErrorPvpModeCn);
    return szPassword;
  }
}



// ------------------------------------------------------------
// 0x52C080 sub_52C080
// ------------------------------------------------------------
// std::string vector 区间赋值（28B/元素步进 sub_4014D0 assign）

int /*cdecl*/ sub_52C080(std::_String_base *a1, std::_String_base *a2, int a3)
{
  std::_String_base *i; // esi
  int result; // eax

  for ( i = a1; i != a2; i = (std::_String_base *)((char *)i + 28) )
    result = sub_4014D0(i, a3, 0, -1);
  return result;
}



// ------------------------------------------------------------
// 0x52C0B0 sub_52C0B0
// ------------------------------------------------------------
// std::string vector 区间构造（+24=15 SSO 容量初始化）

int /*cdecl*/ sub_52C0B0(int a1, int a2, int a3)
{
  int v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != 0 )
    {
      *(uint32_t *)(v3 + 24) = 15;
      *(uint32_t *)(v3 + 20) = 0;
      *(uint8_t *)(v3 + 4) = 0;
      sub_4014D0((std::_String_base *)v3, a1, 0, -1);
    }
    v3 += 28;
    LOBYTE(v7) = 0;
    a1 += 28;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x52C170 sub_52C170
// ------------------------------------------------------------
// std::string vector 填充 n 个 a3

int /*cdecl*/ sub_52C170(int a1, int a2, int a3)
{
  int v3; // esi
  int result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v6[4] = v6;
  v6[3] = a1;
  v7 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != 0 )
    {
      *(uint32_t *)(v3 + 24) = 15;
      *(uint32_t *)(v3 + 20) = 0;
      *(uint8_t *)(v3 + 4) = 0;
      result = sub_4014D0((std::_String_base *)v3, a3, 0, -1);
    }
    --a2;
    v3 += 28;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x52C220 sub_52C220
// ------------------------------------------------------------
// 填充包装：sub_52C170 → 返回尾指针

int /*stdcall*/ sub_52C220(int a1, int a2, int a3)
{
  sub_52C170(a1, a2, a3);
  return a1 + 28 * a2;
}



// ------------------------------------------------------------
// 0x52C250 sub_52C250
// ------------------------------------------------------------
// ★ std::vector<std::string>::insert 编译器实例化体（119L：153391689 元素容量上限、
// 1.5× 扩容、sub_52C0B0/52C220/52C080 为 MSVC 辅助）

void /*thiscall*/ sub_52C250(int *this, int a2, unsigned int a3, int a4)
{
  int v5; // ebx
  unsigned int v6; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  char *v12; // ebx
  int v13; // eax
  unsigned int v14; // edi
  void *v15; // eax
  char *v16; // ecx
  int v18; // edx
  int v19; // [esp-18h] [ebp-60h]
  int v20; // [esp-10h] [ebp-58h]
  int v21; // [esp-Ch] [ebp-54h]
  unsigned int v22; // [esp-8h] [ebp-50h]
  uint32_t v23[4]; // [esp+0h] [ebp-48h] BYREF
  void *Block; // [esp+10h] [ebp-38h]
  char *v25; // [esp+14h] [ebp-34h]
  char v26[4]; // [esp+18h] [ebp-30h] BYREF
  void *v27; // [esp+1Ch] [ebp-2Ch]
  int v28; // [esp+2Ch] [ebp-1Ch]
  unsigned int v29; // [esp+30h] [ebp-18h]
  int v30; // [esp+34h] [ebp-14h]
  uint32_t *v31; // [esp+38h] [ebp-10h]
  int v32; // [esp+44h] [ebp-4h]
  char *v33; // [esp+50h] [ebp+8h]
  int v34; // [esp+54h] [ebp+Ch]

  v31 = v23;
  v30 = dword_796E50;
  v23[3] = this;
  v29 = 15;
  v28 = 0;
  LOBYTE(v27) = 0;
  sub_4014D0((std::_String_base *)v26, a4, 0, -1);
  v5 = *(this + 1);
  v32 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 28;
  else
    v6 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - *(this + 1)) / 28;
    else
      v8 = 0;
    if ( 153391689 - v8 < a3 )
      sub_44CAB0(this);
    if ( *(this + 1) != 0 )
      v9 = (*(this + 2) - *(this + 1)) / 28;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = (char *)*(this + 2);
      Block = v16;
      if ( (int)&v16[-a2] / 28 >= a3 )
      {
        v33 = &v16[-28 * a3];
        *(this + 2) = sub_52C0B0(v33, v16, v16);
        sub_416680(a2, v33, Block);
        sub_52C080(a2, a2 + 28 * a3, v26);
      }
      else
      {
        sub_52C0B0(a2, v16, a2 + 28 * a3);
        v22 = a3 - (*(this + 2) - a2) / 28;
        v21 = *(this + 2);
        LOBYTE(v32) = 3;
        sub_52C220(v21, v22, v26);
        v18 = 28 * a3 + *(this + 2);
        *(this + 2) = v18;
        v32 = 0;
        sub_52C080(a2, v18 - 28 * a3, v26);
      }
    }
    else
    {
      if ( 153391689 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        v11 = (*(this + 2) - *(this + 1)) / 28;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_52AEF0(this);
      v34 = 28 * v10;
      v12 = (char *)operator new(28 * v10);
      v19 = *(this + 1);
      Block = v12;
      v25 = v12;
      LOBYTE(v32) = 1;
      v25 = (char *)sub_52C0B0(v19, a2, v12);
      sub_52C170(v25, a3, v26);
      v20 = *(this + 2);
      v25 += 28 * a3;
      sub_52C0B0(a2, v20, v25);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 28;
      v14 = v13 + a3;
      v15 = (void *)*(this + 1);
      if ( v15 != nullptr )
      {
        sub_44E3B0(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v34];
      *(this + 2) = (int)&v12[28 * v14];
      *(this + 1) = (int)v12;
    }
  }
  if ( v29 >= 0x10 )
    j__free(v27);
}


// ------------------------------------------------------------
// 0x52C590 sub_52C590
// ------------------------------------------------------------
// 房间 UI 重置（141L：按钮组/列表/滚动条复位）

void /*thiscall*/ sub_52C590(uint32_t *this)
{
  void *v1; // eax
  uint32_t *v2; // esi
  uint32_t *v3; // ecx
  int **v4; // eax
  int *v5; // edi
  int **v6; // edx
  bool v7; // zf
  int v8; // eax
  int v9; // eax
  uint32_t *v10; // esi
  signed int i; // eax
  int v12; // ebx
  int **v13; // eax
  int *k; // eax
  int *j; // eax
  uint32_t *v16; // ebx
  int v17; // ecx
  unsigned int v18; // edx
  uint32_t *v19; // eax
  uint32_t *v20; // eax
  uint32_t *v21; // esi
  int v22; // [esp-14h] [ebp-44h]
  uint32_t *v23; // [esp+4h] [ebp-2Ch]
  uint32_t v24[2]; // [esp+Ch] [ebp-24h] BYREF
  uint32_t *v25; // [esp+14h] [ebp-1Ch]
  int v26; // [esp+18h] [ebp-18h]
  int v27; // [esp+1Ch] [ebp-14h]
  int v28; // [esp+20h] [ebp-10h]
  int v29; // [esp+2Ch] [ebp-4h]

  if ( *(uint8_t *)(*(this + 6) + 16) != 0 )
  {
    v1 = (void *)*(this + 3);
    v2 = this + 2;
    v25 = this + 2;
    if ( v1 != nullptr )
      j__free(v1);
    v2[1] = 0;
    v2[2] = 0;
    v2[3] = 0;
    v28 = sub_429830((uint16_t)word_77F804);
    v27 = sub_41A5E0(v28 + 53);
    v3 = sub_4A2CF0();
    v23 = v3;
    v4 = *(int ***)(dword_8F8500 + 8);
    v5 = *v4;
    v6 = (int **)(dword_8F8500 + 8);
    v7 = *v4 == (int *)v4;
    v29 = 0;
    v26 = dword_8F8500 + 8;
    if ( !v7 )
    {
      do
      {
        v8 = v5[4];
        if ( *(uint32_t *)(v8 + 68) == 0 && v8 != v28 )
        {
          v9 = sub_41A5E0(v8 + 53);
          v10 = (uint32_t *)*v23;
          for ( i = abs32(v27 - v9); v10 != v23; v10 = (uint32_t *)*v10 )
          {
            if ( v10[2] >= i )
              break;
          }
          v24[0] = i;
          v22 = v10[1];
          v24[1] = *(uint16_t *)(v5[4] + 4);
          v12 = sub_52DAA0(v10, v22, v24);
          sub_468240(1);
          v6 = (int **)v26;
          v10[1] = v12;
          v2 = v25;
          **(uint32_t **)(v12 + 4) = v12;
          v3 = v23;
        }
        if ( *((uint8_t *)v5 + 21) == 0 )
        {
          v13 = (int **)v5[2];
          if ( *((uint8_t *)v13 + 21) != 0 )
          {
            for ( j = (int *)v5[1]; *((uint8_t *)j + 21) == 0; j = (int *)j[1] )
            {
              if ( v5 != (int *)j[2] )
                break;
              v5 = j;
            }
            v5 = j;
          }
          else
          {
            v5 = (int *)v5[2];
            for ( k = *v13; *((uint8_t *)k + 21) == 0; k = (int *)*k )
              v5 = k;
          }
        }
      }
      while ( v5 != *v6 );
    }
    v16 = (uint32_t *)*v3;
    if ( (uint32_t *)*v3 != v3 )
    {
      do
      {
        v17 = v2[1];
        if ( v17 != 0 )
          v18 = (v2[2] - v17) >> 2;
        else
          v18 = 0;
        if ( v17 != 0 && v18 < (v2[3] - v17) >> 2 )
        {
          v19 = (uint32_t *)v2[2];
          *v19 = v16[3];
          v2[2] = v19 + 1;
        }
        else
        {
          sub_430C80((void *)v2[2], 1, (int)(v16 + 3));
        }
        v16 = (uint32_t *)*v16;
      }
      while ( v16 != v23 );
      v3 = v23;
    }
    v20 = (uint32_t *)*v3;
    v7 = *v3 == (uint32_t)v3;
    *v3 = v3;
    v3[1] = v3;
    if ( !v7 )
    {
      do
      {
        v21 = (uint32_t *)*v20;
        j__free(v20);
        v3 = v23;
        v20 = v21;
      }
      while ( v21 != v23 );
    }
    j__free(v3);
  }
}


// ------------------------------------------------------------
// 0x52C780 sub_52C780
// ------------------------------------------------------------
// vector<string> 定点插入（12L：算偏移 → sub_52C250 → 出参迭代器）

uint32_t */*thiscall*/ sub_52C780(int *this, uint32_t *a2, std::_String_base *a3, int a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 28 != 0 )
    v6 = ((int)a3 - v5) / 28;
  else
    v6 = 0;
  sub_52C250(this, a3, 1u, a4);
  *a2 = *(this + 1) + 28 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x52C7F0 sub_52C7F0
// ------------------------------------------------------------
// ★ PVP 界面打开（29L）：+24 使能翻转 → 0x52A9F0(0)/0x52C590/0x52AF20/0x52A950 四连复位 →
// sub_69A5F0 控件定位（567,142)/(542,155)/(458,114) → +30/+28 状态清零

char /*thiscall*/ sub_52C7F0(int this, char a2)
{
  int v3; // eax

  v3 = *(uint32_t *)(this + 24);
  if ( *(uint8_t *)(v3 + 16) != a2 )
  {
    *(uint8_t *)(v3 + 16) = a2;
    if ( a2 != 0 )
    {
      sub_52A9F0(this, 0);
      sub_52C590((uint32_t *)this);
      sub_52AF20((uint32_t *)this);
      sub_52A950((int *)this);
      sub_48F5A0();
      sub_69A5F0(*(uint32_t **)(this + 72), 567, 142);
      sub_69A5F0(*(uint32_t **)(this + 68), 542, 155);
      *(uint8_t *)(*(uint32_t *)(this + 68) + 16) = 0;
      sub_69A5F0(*(uint32_t **)(this + 88), 542, 155);
      *(uint8_t *)(*(uint32_t *)(this + 88) + 16) = 0;
      sub_69A5F0(*(uint32_t **)(this + 132), 458, 114);
      *(uint8_t *)(*(uint32_t *)(this + 132) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(this + 136) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 1;
      *(uint16_t *)(this + 30) = 0;
      *(uint8_t *)(this + 28) = 0;
      LOBYTE(v3) = 1;
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x52C8B0 sub_52C8B0
// ------------------------------------------------------------
// 界面项访问（17L）

uint32_t */*thiscall*/ sub_52C8B0(int this, int a2)
{
  int v3; // ebx
  unsigned int v4; // esi
  int v5; // esi
  uint32_t *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 28;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 28 )
    return sub_52C780((int *)this, &a2, *(std::_String_base **)(this + 8), a2);
  v5 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_52C170(v5, 1, a2);
  *(uint32_t *)(this + 8) = v5 + 28;
  return result;
}



// ------------------------------------------------------------
// 0x52C940 sub_52C940
// ------------------------------------------------------------
// 界面数据读取（48L）

int */*thiscall*/ sub_52C940(uint16_t *this)
{
  int v1; // eax
  int v2; // edi
  int v3; // esi
  int *result; // eax
  int *v5; // ecx
  int *v6; // [esp+Ch] [ebp-34h] BYREF
  int v7; // [esp+10h] [ebp-30h] BYREF
  uint8_t v8[4]; // [esp+14h] [ebp-2Ch] BYREF
  void *Block; // [esp+18h] [ebp-28h]
  int v10; // [esp+28h] [ebp-18h]
  unsigned int v11; // [esp+2Ch] [ebp-14h]
  int v12; // [esp+30h] [ebp-10h]
  int v13; // [esp+3Ch] [ebp-4h]

  v1 = dword_796E50;
  v2 = (int)(this + 18);
  *(this + 15) = 0;
  v12 = v1;
  sub_44F730((int)(this + 18));
  v3 = 50000;
  while ( 1 )
  {
    v7 = v3;
    sub_442D00(&dword_9B7408, &v6, &v7);
    result = v6;
    if ( v6 == (int *)dword_9B740C )
      v5 = nullptr;
    else
      v5 = (unsigned int)v6[10] < 0x10 ? v6 + 5 : (int *)v6[5];
    v7 = v3 + 1;
    if ( v5 == nullptr )
      break;
    v11 = 15;
    v10 = 0;
    LOBYTE(Block) = 0;
    v13 = 0;
    sub_4015C0(v5, strlen((const char *)v5));
    sub_52C8B0(v2, (int)v8);
    v13 = -1;
    if ( v11 >= 0x10 )
      j__free(Block);
    v3 = v7;
    v11 = 15;
    v10 = 0;
    LOBYTE(Block) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x52CA40 sub_52CA40
// ------------------------------------------------------------
// ★ PVP 界面主处理（556L 本文件第二大函数）：消息/命令分发大函数

int /*thiscall*/ sub_52CA40(int this, void *Block)
{
  int v3; // eax
  void *v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  uint32_t *v9; // edi
  int v10; // edx
  int v11; // eax
  uint32_t *v12; // ecx
  uint32_t *v13; // edi
  bool v14; // cc
  uint32_t *v15; // eax
  uint32_t *v16; // edi
  uint32_t *v17; // eax
  uint32_t *v18; // edi
  uint32_t *v19; // edi
  int v20; // edx
  int v21; // eax
  uint32_t *v22; // ecx
  uint32_t *v23; // edi
  uint32_t *v24; // eax
  uint32_t *v25; // edi
  uint32_t *v26; // edi
  uint32_t *v27; // eax
  uint32_t *v28; // edi
  uint32_t *v29; // edi
  uint32_t *v30; // ecx
  uint32_t *v31; // edi
  uint32_t *v32; // ecx
  uint32_t *v33; // eax
  uint32_t *v34; // edi
  uint32_t *v35; // eax
  uint32_t *v36; // edi
  uint32_t *v37; // eax
  uint32_t *v38; // edi
  uint32_t *v39; // ecx
  uint32_t *v40; // eax
  uint32_t *v41; // edi
  uint32_t *v42; // ecx
  uint32_t *v43; // eax
  uint32_t *v44; // edi
  uint32_t *v45; // ecx
  uint32_t *v46; // eax
  uint32_t *v47; // edi
  uint32_t *v48; // ecx
  void *v49; // eax
  int v50; // eax
  int result; // eax
  int v52; // esi
  int v53; // [esp-Ch] [ebp-5Ch]
  int v54; // [esp-8h] [ebp-58h]
  int v55; // [esp-8h] [ebp-58h]
  int v56; // [esp-8h] [ebp-58h]
  int v57; // [esp-8h] [ebp-58h]
  int v58; // [esp+8h] [ebp-48h]
  uint32_t v59[7]; // [esp+Ch] [ebp-44h]
  void *v60; // [esp+28h] [ebp-28h]
  int v61; // [esp+2Ch] [ebp-24h]
  int v62; // [esp+30h] [ebp-20h]
  int v63; // [esp+34h] [ebp-1Ch]
  int v64; // [esp+38h] [ebp-18h]
  uint32_t *v65; // [esp+3Ch] [ebp-14h]
  int v66; // [esp+40h] [ebp-10h]
  int v67; // [esp+4Ch] [ebp-4h]
  int *Blocka; // [esp+58h] [ebp+8h]
  void *Blocke; // [esp+58h] [ebp+8h]
  void *Blockf; // [esp+58h] [ebp+8h]
  int *Blockb; // [esp+58h] [ebp+8h]
  void *Blockg; // [esp+58h] [ebp+8h]
  uint32_t *Blockc; // [esp+58h] [ebp+8h]
  void *Blockh; // [esp+58h] [ebp+8h]
  void *Blocki; // [esp+58h] [ebp+8h]
  void *Blockd; // [esp+58h] [ebp+8h]
  void *Blockj; // [esp+58h] [ebp+8h]
  void *Blockk; // [esp+58h] [ebp+8h]
  void *Blockl; // [esp+58h] [ebp+8h]
  void *Blockm; // [esp+58h] [ebp+8h]

  *(uint32_t *)(this + 4) = Block;
  *(uint32_t *)(this + 352) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 100);
  v67 = 0;
  if ( operator new(0x6Cu) != nullptr )
    v3 = sub_43C250(*(uint32_t *)(this + 352), 0);
  else
    v3 = 0;
  *(uint32_t *)(this + 24) = v3;
  *(uint32_t *)(v3 + 68) = this;
  v4 = operator new(0x68u);
  v67 = 1;
  if ( v4 != nullptr )
    v5 = sub_426BD0(v4);
  else
    v5 = 0;
  *(uint32_t *)(this + 52) = v5;
  sub_69A840(v5);
  v67 = 2;
  if ( operator new(0x84u) != nullptr )
    v6 = sub_43C410(*(uint32_t *)(this + 352), 20, 22, 23, 20, 0, 0);
  else
    v6 = 0;
  v67 = -1;
  *(uint32_t *)(this + 60) = v6;
  sub_69A5F0(89, 364);
  sub_69A840(*(uint32_t *)(this + 60));
  v67 = 3;
  if ( operator new(0x84u) != nullptr )
    v7 = sub_43C410(*(uint32_t *)(this + 352), 24, 26, 27, 24, 0, 0);
  else
    v7 = 0;
  v67 = -1;
  *(uint32_t *)(this + 64) = v7;
  sub_69A5F0(143, 364);
  sub_69A840(*(uint32_t *)(this + 64));
  v67 = 4;
  if ( operator new(0x6Cu) != nullptr )
    v8 = sub_43C250(*(uint32_t *)(this + 352), 75);
  else
    v8 = 0;
  v67 = -1;
  *(uint32_t *)(this + 68) = v8;
  sub_69A840(v8);
  v66 = 2;
  Blocka = (int *)&unk_7930DC;
  v65 = (uint32_t *)(this + 76);
  do
  {
    v9 = operator new(0x84u);
    v60 = v9;
    v67 = 5;
    if ( v9 != nullptr )
    {
      v10 = Blocka[2];
      v11 = Blocka[1];
      v64 = *Blocka;
      v61 = *(uint32_t *)(this + 352);
      v63 = v10;
      v62 = v11;
      sub_426BD0(v9);
      LOBYTE(v67) = 6;
      *v9 = &nengine::CNButton::`vftable';
      sub_69C780(v9);
      sub_69C7B0(v61, v64, v62, v63, v64, 0, 0);
      v12 = v9;
    }
    else
    {
      v12 = nullptr;
    }
    v13 = v65;
    v54 = v66;
    v67 = -1;
    *v65 = v12;
    sub_69A5F0(2, v54);
    sub_69A840(*v13);
    v14 = (int)(Blocka + 3) < (int)&unk_793100;
    v65 = v13 + 1;
    Blocka += 3;
    v66 += 13;
  }
  while ( v14 );
  v15 = operator new(0x84u);
  v16 = v15;
  v60 = v15;
  v67 = 7;
  if ( v15 != nullptr )
  {
    Blocke = *(void **)(this + 352);
    sub_426BD0(v15);
    LOBYTE(v67) = 8;
    *v16 = &nengine::CNButton::`vftable';
    sub_69C780(v16);
    sub_69C7B0(Blocke, 4, 5, 6, 4, 0, 0);
  }
  else
  {
    v16 = nullptr;
  }
  *(uint32_t *)(this + 72) = v16;
  sub_69A840(v16);
  v17 = operator new(0x6Cu);
  v18 = v17;
  v60 = v17;
  v67 = 9;
  if ( v17 != nullptr )
  {
    Blockf = *(void **)(this + 352);
    sub_426BD0(v17);
    LOBYTE(v67) = 10;
    *v18 = &nengine::CNFrame::`vftable';
    sub_69C6B0(v18);
    sub_69C6C0(Blockf, 7);
  }
  else
  {
    v18 = nullptr;
  }
  v67 = -1;
  *(uint32_t *)(this + 88) = v18;
  sub_69A840(v18);
  v66 = 2;
  Blockb = (int *)&unk_793100;
  v65 = (uint32_t *)(this + 92);
  do
  {
    v19 = operator new(0x84u);
    v60 = v19;
    v67 = 11;
    if ( v19 != nullptr )
    {
      v20 = Blockb[2];
      v21 = Blockb[1];
      v61 = *Blockb;
      v64 = *(uint32_t *)(this + 352);
      v62 = v20;
      v63 = v21;
      sub_426BD0(v19);
      LOBYTE(v67) = 12;
      *v19 = &nengine::CNButton::`vftable';
      sub_69C780(v19);
      sub_69C7B0(v64, v61, v63, v62, v61, 0, 0);
      v22 = v19;
    }
    else
    {
      v22 = nullptr;
    }
    v23 = v65;
    v55 = v66;
    v67 = -1;
    *v65 = v22;
    sub_69A5F0(2, v55);
    sub_69A840(*v23);
    v14 = (int)(Blockb + 3) < (int)&dword_793118;
    v65 = v23 + 1;
    Blockb += 3;
    v66 += 13;
  }
  while ( v14 );
  v24 = operator new(0x84u);
  v25 = v24;
  v60 = v24;
  v67 = 13;
  if ( v24 != nullptr )
  {
    Blockg = *(void **)(this + 352);
    sub_426BD0(v24);
    LOBYTE(v67) = 14;
    *v25 = &nengine::CNButton::`vftable';
    sub_69C780(v25);
    sub_69C7B0(Blockg, 1, 2, 3, 1, 0, 0);
  }
  else
  {
    v25 = nullptr;
  }
  *(uint32_t *)(this + 56) = v25;
  v25[17] = this;
  v67 = -1;
  sub_69A5F0(15, 389);
  sub_69A840(*(uint32_t *)(this + 56));
  *(uint8_t *)(this + 28) = 0;
  *(uint16_t *)(this + 30) = 0;
  *(uint32_t *)(this + 32) = 0;
  v26 = *(uint32_t **)(this + 40);
  if ( v26 != nullptr )
  {
    v27 = *(uint32_t **)(this + 44);
    Blockc = v27;
    if ( v26 != v27 )
    {
      v28 = v26 + 6;
      do
      {
        if ( *v28 >= 0x10u )
        {
          j__free((void *)*(v28 - 5));
          v27 = Blockc;
        }
        *v28 = 15;
        *(v28 - 1) = 0;
        *((uint8_t *)v28 - 20) = 0;
        v28 += 7;
      }
      while ( v28 - 6 != v27 );
    }
    j__free(*(void **)(this + 40));
  }
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  v29 = operator new(0x84u);
  v60 = v29;
  v67 = 15;
  if ( v29 != nullptr )
  {
    Blockh = *(void **)(this + 352);
    sub_426BD0(v29);
    LOBYTE(v67) = 16;
    *v29 = &nengine::CNButton::`vftable';
    sub_69C780(v29);
    sub_69C7B0(Blockh, 62, 63, 64, 62, 0, 0);
    v30 = v29;
  }
  else
  {
    v30 = nullptr;
  }
  v67 = -1;
  *(uint32_t *)(this + 104) = v30;
  sub_69A5F0(104, 307);
  *(uint8_t *)(*(uint32_t *)(this + 104) + 16) = 0;
  sub_69A840(*(uint32_t *)(this + 104));
  v31 = operator new(0x84u);
  v60 = v31;
  v67 = 17;
  if ( v31 != nullptr )
  {
    Blocki = *(void **)(this + 352);
    sub_426BD0(v31);
    LOBYTE(v67) = 18;
    *v31 = &nengine::CNButton::`vftable';
    sub_69C780(v31);
    sub_69C7B0(Blocki, 65, 66, 67, 65, 0, 0);
    v32 = v31;
  }
  else
  {
    v32 = nullptr;
  }
  v67 = -1;
  *(uint32_t *)(this + 108) = v32;
  sub_69A5F0(150, 307);
  *(uint8_t *)(*(uint32_t *)(this + 108) + 16) = 0;
  sub_69A840(*(uint32_t *)(this + 108));
  v58 = 20;
  v59[3] = 20;
  v59[4] = 226;
  v59[6] = 226;
  v59[0] = 148;
  v59[1] = 136;
  v59[2] = 148;
  v59[5] = 136;
  Blockd = nullptr;
  v65 = (uint32_t *)(this + 116);
  do
  {
    v33 = operator new(0x84u);
    v34 = v33;
    v60 = v33;
    v67 = 19;
    if ( v33 != nullptr )
    {
      v61 = *(uint32_t *)(this + 352);
      sub_426BD0(v33);
      LOBYTE(v67) = 20;
      *v34 = &nengine::CNButton::`vftable';
      sub_69C780(v34);
      sub_69C7B0(v61, 73, 73, 74, 73, 0, 0);
      v35 = v34;
    }
    else
    {
      v35 = nullptr;
    }
    v36 = v65;
    *v65 = v35;
    v35[17] = this;
    *(uint8_t *)(*v36 + 16) = 0;
    v56 = v59[2 * (uint32_t)Blockd];
    v53 = v59[2 * (uint32_t)Blockd - 1];
    v67 = -1;
    sub_69A5F0(v53, v56);
    sub_69A840(*v36);
    v14 = (int)Blockd + 1 < 4;
    Blockd = (char *)Blockd + 1;
    v65 = v36 + 1;
  }
  while ( v14 );
  v37 = operator new(0x84u);
  v38 = v37;
  v60 = v37;
  v67 = 21;
  if ( v37 != nullptr )
  {
    Blockj = *(void **)(this + 352);
    sub_426BD0(v37);
    LOBYTE(v67) = 22;
    *v38 = &nengine::CNButton::`vftable';
    sub_69C780(v38);
    sub_69C7B0(Blockj, 49, 50, 51, 49, 0, 0);
    v39 = v38;
  }
  else
  {
    v39 = nullptr;
  }
  v67 = -1;
  *(uint32_t *)(this + 112) = v39;
  sub_69A5F0(192, 313);
  *(uint8_t *)(*(uint32_t *)(this + 112) + 16) = 0;
  sub_69A840(*(uint32_t *)(this + 112));
  v40 = operator new(0x84u);
  v41 = v40;
  v60 = v40;
  v67 = 23;
  if ( v40 != nullptr )
  {
    Blockk = *(void **)(this + 352);
    sub_426BD0(v40);
    LOBYTE(v67) = 24;
    *v41 = &nengine::CNButton::`vftable';
    sub_69C780(v41);
    sub_69C7B0(Blockk, 68, 69, 70, 68, 0, 0);
    v42 = v41;
  }
  else
  {
    v42 = nullptr;
  }
  v67 = -1;
  *(uint32_t *)(this + 132) = v42;
  sub_69A5F0(458, 114);
  sub_69A840(*(uint32_t *)(this + 132));
  sub_52C940(this);
  v43 = operator new(0x84u);
  v44 = v43;
  v60 = v43;
  v67 = 25;
  if ( v43 != nullptr )
  {
    Blockl = *(void **)(this + 352);
    sub_426BD0(v43);
    LOBYTE(v67) = 26;
    *v44 = &nengine::CNButton::`vftable';
    sub_69C780(v44);
    sub_69C7B0(Blockl, 46, 47, 48, 46, 0, 0);
    v45 = v44;
  }
  else
  {
    v45 = nullptr;
  }
  v67 = -1;
  *(uint32_t *)(this + 136) = v45;
  sub_69A5F0(113, 321);
  sub_69A840(*(uint32_t *)(this + 136));
  v46 = operator new(0x84u);
  v47 = v46;
  v60 = v46;
  v67 = 27;
  if ( v46 != nullptr )
  {
    Blockm = *(void **)(this + 352);
    sub_426BD0(v46);
    LOBYTE(v67) = 28;
    *v47 = &nengine::CNButton::`vftable';
    sub_69C780(v47);
    sub_69C7B0(Blockm, 29, 30, 31, 28, 0, 0);
    v48 = v47;
  }
  else
  {
    v48 = nullptr;
  }
  v67 = -1;
  *(uint32_t *)(this + 100) = v48;
  sub_69A5F0(77, 387);
  sub_69A840(*(uint32_t *)(this + 100));
  v49 = operator new(0x68u);
  v67 = 29;
  if ( v49 != nullptr )
    v50 = sub_426BD0(v49);
  else
    v50 = 0;
  *(uint32_t *)(this + 140) = v50;
  *(uint32_t *)(v50 + 68) = this;
  v57 = *(uint32_t *)(this + 140);
  v67 = -1;
  sub_69A840(v57);
  *(uint8_t *)(this + 144) = 0;
  *(uint8_t *)(this + 145) = 0;
  *(uint8_t *)(this + 146) = 0;
  *(uint8_t *)(this + 147) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 172) = 1600;
  *(uint32_t *)(this + 160) = 6;
  *(uint32_t *)(this + 164) = 12;
  *(uint32_t *)(this + 192) = dword_99FCCC;
  *(uint32_t *)(this + 148) = -16777216;
  *(uint8_t *)(this + 196) = 0;
  *(uint8_t *)(this + 197) = 0;
  *(uint8_t *)(this + 198) = 0;
  *(uint8_t *)(this + 199) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 6;
  *(uint32_t *)(this + 216) = 12;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 1600;
  *(uint32_t *)(this + 228) = 0;
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  *(uint32_t *)(this + 244) = dword_99FCCC;
  *(uint32_t *)(this + 224) = 72;
  *(uint32_t *)(this + 208) = 1;
  *(uint8_t *)(this + 248) = 0;
  *(uint8_t *)(this + 249) = 0;
  *(uint8_t *)(this + 250) = 0;
  *(uint8_t *)(this + 251) = 0;
  *(uint32_t *)(this + 260) = 0;
  *(uint32_t *)(this + 264) = 6;
  *(uint32_t *)(this + 268) = 12;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 1600;
  *(uint32_t *)(this + 280) = 0;
  *(uint32_t *)(this + 284) = 0;
  *(uint32_t *)(this + 288) = 0;
  *(uint32_t *)(this + 292) = 0;
  *(uint32_t *)(this + 296) = 0;
  *(uint32_t *)(this + 296) = dword_99FCCC;
  *(uint32_t *)(this + 276) = 156;
  *(uint32_t *)(this + 252) = -16777216;
  *(uint8_t *)(this + 250) = 1;
  *(uint32_t *)(this + 260) = 1;
  *(uint8_t *)(this + 300) = 0;
  *(uint8_t *)(this + 301) = 0;
  *(uint8_t *)(this + 302) = 0;
  *(uint8_t *)(this + 303) = 0;
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 6;
  *(uint32_t *)(this + 320) = 12;
  *(uint32_t *)(this + 324) = 0;
  *(uint32_t *)(this + 328) = 1600;
  *(uint32_t *)(this + 332) = 0;
  *(uint32_t *)(this + 336) = 0;
  *(uint32_t *)(this + 340) = 0;
  *(uint32_t *)(this + 344) = 0;
  *(uint32_t *)(this + 348) = 0;
  *(uint32_t *)(this + 348) = dword_99FCCC;
  *(uint32_t *)(this + 328) = 120;
  *(uint32_t *)(this + 312) = 1;
  *(uint32_t *)(this + 304) = -16777216;
  result = sub_69A5F0(369, 0);
  v52 = *(uint32_t *)(this + 24);
  if ( *(uint8_t *)(v52 + 16) != 0 )
    *(uint8_t *)(v52 + 16) = 0;
  return result;
}


// ------------------------------------------------------------
// ============
// 【分区 6】观察者-装备族（0x52D550-0x52E1C0）—— docs/15 已 L1 精修
// ★ 本区 14 函数在 src/cnrd/ActiveObjectEquipment.cpp 有逐行 L1 精修版（docs/15），
//   本文件保留 L2 转写体。核心定案：18 观察者槽(+6468) = 装备/称号组件挂载点；
//   vmt310 挂载 / vmt314 卸下 / vmt31C 属性求和 / vmt324 装备可用性(CNRDEquipment RTTI 直证) /
//   vmt328 = UDP type=10 物品使用 / vmt360 = UDP type=25 时钟同步 / vmt368 光环显示链。
//   0x52D970/0x52DAA0/0x52E130 为本区私有辅助（不在 docs/15 清单内）。
// ============

// 0x52D550 IRDActiveObject__vmt31C
// ------------------------------------------------------------
// vmt31C 全观察者属性求和：18 槽(+6468) 逐个 vt+792(i)，非空取 vt+16() 属性块 +56 项累加

int /*fastcall*/ IRDActiveObject__vmt31C(uint32_t *a1)
{
  int v1; // ebx
  int v2; // esi
  uint32_t *v3; // edi
  uint32_t *v5; // [esp+Ch] [ebp-4h]

  v1 = 0;
  v5 = a1;
  v2 = 0;
  v3 = a1 + 1617;
  while ( 1 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 792))(a1, v2) != 0 )
      v1 += *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v3 + 16))(*v3) + 56);
    ++v2;
    ++v3;
    if ( v2 >= 18 )
      break;
    a1 = v5;
  }
  return v1;
}



// ------------------------------------------------------------
// 0x52D5A0 IRDActiveObject__vmt324
// ------------------------------------------------------------
// vmt324 装备可用性检查：大状态 2 拒 / RTDynamicCast→CNRDEquipment / 职业字节 / 需求等级(防篡读)

bool /*thiscall*/ IRDActiveObject__vmt324(uint32_t *this, int a2)
{
  int v2; // edi
  int v5; // eax
  int v6; // esi
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  uint32_t *v12; // esi
  int v14; // [esp+10h] [ebp+8h]

  v2 = (int)this;
  if ( *(this + 50) == 2 )
    return false;
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 16))(a2);
  v5 = __RTDynamicCast(v2, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
  v6 = v5;
  if ( v5 != 0 )
  {
    if ( *(uint8_t *)(*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 1032))(v5) + v14 + 60) == 0 )
      return false;
    if ( dword_8F7C04 == v6 )
    {
      v7 = __RTDynamicCast(a2, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
      v8 = v7;
      if ( v7 != 0 )
      {
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 172))(v7);
        if ( sub_41A5E0(v9 + 32) != -1 )
        {
          v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 172))(v8);
          v11 = sub_41A5E0(v10 + 32);
          if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 1160))(v6, v11) == 0 || sub_44ACC0(1) == 0 )
            return false;
        }
      }
      v2 = (int)this;
    }
  }
  v12 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 672))(v2, 3);
  return *v12 >= CNRDParticleCreater__vmt30(a2)
      || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 20))(a2, 1) != 0
      && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 132))(a2) == 2;
}



// ------------------------------------------------------------
// 0x52D6D0 IRDActiveObject__vmt32C
// ------------------------------------------------------------
// vmt32C 装备动作转发：物品类型+索引 → vt+808 应用

int /*thiscall*/ IRDActiveObject__vmt32C(int *this, int a2, int a3)
{
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  uint32_t *v10; // [esp+14h] [ebp+8h]

  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 172))(a2);
  v6 = *this;
  v10 = (uint32_t *)v5;
  v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 188))(a2, a3);
  v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 16))(a2, v7);
  return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(v6 + 808))(this, *v10, *(uint32_t *)(v8 + 4));
}



// ------------------------------------------------------------
// 0x52D720 IRDActiveObject__vmt328
// ------------------------------------------------------------
// ★ vmt328 UDP type=10 物品使用：3 防篡读字段 + 三元组 + 60B 包体（sub_4E9A50 构造）

int /*thiscall*/ IRDActiveObject__vmt328(void *this, int a2, int a3, uint32_t *a4, int a5)
{
  int result; // eax
  uint32_t *v7; // esi
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  uint8_t v15[60]; // [esp+4h] [ebp-48h] BYREF
  int v16; // [esp+48h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    sub_4E9A50(v15);
    v7 = a4;
    v16 = 0;
    if ( a4 == nullptr )
      v7 = v15;
    (*(void (/*thiscall*/ **)(int, int, bool))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 10, a5 == -1);
    v8 = *(uint32_t *)dword_8F8520;
    v9 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);
    (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);
    v10 = *(uint32_t *)dword_8F8520;
    v11 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
    (*(void (/*thiscall*/ **)(int, int))(v10 + 36))(dword_8F8520, v11);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, a2);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a3);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, *v7);
    v12 = sub_41A5E0((unsigned int)(v7 + 1));
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v12);
    v13 = sub_41A5E0((unsigned int)v7 + 18);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v13);
    v14 = sub_41A5E0((unsigned int)(v7 + 8));
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v14);
    if ( a5 == -1 )
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    else
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, a5);
    v16 = -1;
    return sub_445150(v15);
  }
  return result;
}



// ------------------------------------------------------------
// 0x52D860 IRDActiveObject__vmt360
// ------------------------------------------------------------
// ★ vmt360 UDP type=25 时钟同步：clockAux 时刻载荷

int /*thiscall*/ IRDActiveObject__vmt360(void *this, int a2)
{
  int result; // eax
  int v4; // edi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 25, 2);
    v4 = *(uint32_t *)dword_8F8520;
    v5 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);
    (*(void (/*thiscall*/ **)(int, int))(v4 + 36))(dword_8F8520, v5);
    v6 = *(uint32_t *)dword_8F8520;
    v7 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
    (*(void (/*thiscall*/ **)(int, int))(v6 + 36))(dword_8F8520, v7);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a2);
    v8 = *(uint32_t *)dword_8F8520;
    v9 = sub_699000((int)this + 36);
    (*(void (/*thiscall*/ **)(int, int))(v8 + 40))(dword_8F8520, v9);
    return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x52D8F0 IRDActiveObject__vmt33C
// ------------------------------------------------------------
// vmt33C 称号名字：+6504 观察者 → 字符串链（空则 szPassword）

const CHAR */*thiscall*/ IRDActiveObject__vmt33C(uint32_t *this)
{
  int v1; // eax
  int v2; // eax

  v1 = *(this + 1626);
  if ( v1 == 0 )
    return szPassword;
  v2 = (*(int (**)(void))(*(uint32_t *)v1 + 16))();
  return (const CHAR *)sub_41ACF0(v2 + 8);
}



// ------------------------------------------------------------
// 0x52D920 IRDActiveObject__vmt340
// ------------------------------------------------------------
// vmt340 称号状态转发：+6504 观察者 → vt+252(0)

int /*thiscall*/ IRDActiveObject__vmt340(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 1626);
  if ( v1 != 0 )
    return (*(int (/*stdcall*/ **)(uint32_t))(*(uint32_t *)v1 + 252))(0);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x52D940 IRDActiveObject__vmt320
// ------------------------------------------------------------
// vmt320 18 观察者 vt+216 全广播

int /*thiscall*/ IRDActiveObject__vmt320(int *this)
{
  int *v1; // esi
  int i; // edi
  int result; // eax

  v1 = this + 1617;
  for ( i = 18; i != 0; --i )
  {
    result = *v1;
    if ( *v1 != 0 )
      result = (*(int (**)(void))(*(uint32_t *)result + 216))();
    ++v1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x52D970 sub_52D970
// ------------------------------------------------------------
// 光环事件构造辅助（60L usercall edi：不在 docs/15 清单，L2 注释待深挖）

int /*usercall*/ sub_52D970@<eax>(int a1@<edi>, int a2, char a3)
{
  int v3; // esi
  int result; // eax
  int v5; // edi
  int v6; // esi
  int v7; // eax
  int v8; // eax
  int i; // esi
  int v10; // eax
  int v11; // eax

  v3 = dword_8F8520;
  if ( *(uint32_t *)(sub_656710() + 4 * a2) == -1 || (result = *(uint32_t *)(v3 + 4 * a2 + 1048648)) == 0 )
  {
    result = *(uint32_t *)(dword_8F7A24 + 12);
    if ( result == 4 )
    {
      if ( a2 >= 8 || dword_99FEC0 == 0 )
        return result;
      result = sub_48F690(a2);
    }
    else if ( result == 6 )
    {
      if ( a2 >= 8 || dword_99FF08 == 0 )
        return result;
      result = sub_578E80(a2);
    }
    else
    {
      if ( a2 >= 4 )
        return result;
      result = *(uint32_t *)(dword_8F850C + 4 * a2 + 16);
    }
    if ( result != 0 )
    {
      v5 = *(uint32_t *)(result + 196);
      if ( v5 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 11, 0, a1);
        v6 = *(uint32_t *)dword_8F8520;
        v7 = sub_656710();
        v8 = sub_656840(v7);
        (*(void (/*thiscall*/ **)(int, int))(v6 + 32))(dword_8F8520, v8);
        for ( i = 0; i < 18; ++i )
        {
          v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 792))(v5, i);
          if ( v10 != 0 )
            v11 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 16))(v10) + 4);
          else
            v11 = 0xFFFF;
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v11);
        }
        if ( a3 == 1 )
          return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1);
        else
          return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x52DAA0 sub_52DAA0
// ------------------------------------------------------------
// 事件节点分配：new(0x10){a1,a2,a3[0],a3[1]}（光环显示链节点，0x52E1C0 使用）

uint32_t */*stdcall*/ sub_52DAA0(int a1, int a2, uint32_t *a3)
{
  uint32_t *result; // eax

  result = operator new(0x10u);
  if ( result != nullptr )
  {
    *result = a1;
    result[1] = a2;
    result[2] = *a3;
    result[3] = a3[1];
  }
  return result;
}



// ------------------------------------------------------------
// 0x52DAD0 IRDActiveObject__vmt310
// ------------------------------------------------------------
// ★ vmt310 装备观察者挂载：槽位写入 +6468+4×槽 = 观察者 + 回指 + 内嵌记录 124B 步长链

int /*userpurge*/ IRDActiveObject__vmt310@<eax>(int a1@<ecx>, int a2@<ebx>, int a3)
{
  uint32_t *v5; // ebx
  int v6; // eax
  int v7; // ebx
  uint32_t *i; // esi
  int v10; // [esp+10h] [ebp+8h]

  if ( a3 == 0 || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 172))(a3) == 18 )
    return a3;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 16))(a3, a2);
  v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 172))(a3);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 264))(a3) == 0 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 256))(a3);
  v6 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 788))(a1, *v5);
  *(uint32_t *)(a1 + 4 * *v5 + 6468) = a3;
  v10 = v6;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 208))(a3, a1);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 148))(a3);
  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 16))(a3) + 32) = 0;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 800))(a1);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 676))(a1, 0);
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 248))(a3);
  for ( i = *(uint32_t **)(v7 + 4); i != *(uint32_t **)(v7 + 8); i += 31 )
    (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t *))(*(uint32_t *)a1 + 692))(a1, *i, a1 + 6160, i + 1);
  return v10;
}



// ------------------------------------------------------------
// 0x52DBC0 IRDActiveObject__vmt314
// ------------------------------------------------------------
// ★ vmt314 装备观察者卸下：对称操作

int /*thiscall*/ IRDActiveObject__vmt314(uint32_t *this, int a2)
{
  int v4; // ebx
  int v5; // eax
  int v6; // edi
  int i; // [esp+Ch] [ebp+8h]

  if ( a2 == 18 )
    return 0;
  v4 = *(this + a2 + 1617);
  if ( v4 == 0 )
    return 0;
  *(this + a2 + 1617) = 0;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 152))(v4);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v4 + 208))(v4, 0);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 800))(this);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 248))(v4);
  v6 = *(uint32_t *)(v5 + 4);
  for ( i = v5; v6 != *(uint32_t *)(i + 8); v6 += 124 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int))(*this + 696))(this, this + 1540, v6 + 4);
  return v4;
}



// ------------------------------------------------------------
// 0x52DC70 IRDActiveObject__vmt2B4
// ------------------------------------------------------------
// ★ vmt2B4 观察者组件逐槽挂载：9 单指针 + 数组段 40/44 + 数组段 56/60（124B 记录）

uint32_t */*stdcall*/ sub_52DC70(int a1, uint32_t *a2, char *a3)
{
  uint32_t *v3; // esi
  int v4; // edi
  int i; // ebx
  int v6; // eax
  unsigned int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // edi
  int v11; // edi
  int j; // esi
  uint32_t *v13; // eax
  int v14; // eax
  unsigned int v15; // ecx
  int v16; // edx
  uint32_t *result; // eax
  int v18; // edi
  int v19; // edi
  int k; // esi

  if ( *a2 != 0 && *(uint32_t *)a3 != 0 )
    sub_494240(a1, *(uint32_t *)a3);
  if ( a2[1] != 0 && *((uint32_t *)a3 + 1) != 0 )
    sub_494240(a1, *((uint32_t *)a3 + 1));
  if ( a2[2] != 0 && *((uint32_t *)a3 + 2) != 0 )
    sub_494240(a1, *((uint32_t *)a3 + 2));
  v3 = a2 + 3;
  v4 = a3 - (char *)a2;
  for ( i = 2; i != 0; --i )
  {
    if ( *v3 != 0 && *(uint32_t *)((char *)v3 + v4) != 0 )
      sub_494240(a1, *(uint32_t *)((char *)v3 + v4));
    ++v3;
  }
  if ( a2[5] != 0 && *((uint32_t *)a3 + 5) != 0 )
    sub_494240(a1, *((uint32_t *)a3 + 5));
  if ( a2[6] != 0 && *((uint32_t *)a3 + 6) != 0 )
    sub_494240(a1, *((uint32_t *)a3 + 6));
  if ( a2[7] != 0 && *((uint32_t *)a3 + 7) != 0 )
    sub_494240(a1, *((uint32_t *)a3 + 7));
  if ( a2[8] != 0 && *((uint32_t *)a3 + 8) != 0 )
    sub_494240(a1, *((uint32_t *)a3 + 8));
  v6 = a2[10];
  if ( v6 != 0 )
    v7 = (a2[11] - v6) >> 2;
  else
    v7 = 0;
  v8 = *((uint32_t *)a3 + 10);
  if ( v8 != 0 && v7 < (*((uint32_t *)a3 + 11) - v8) >> 2 )
  {
    v9 = a2[10];
    if ( v9 == 0 )
    {
      v10 = 0;
      goto LABEL_39;
    }
    v11 = a2[11];
  }
  else
  {
    v9 = *((uint32_t *)a3 + 10);
    if ( v9 == 0 )
    {
      v10 = 0;
      goto LABEL_39;
    }
    v11 = *((uint32_t *)a3 + 11);
  }
  v10 = (v11 - v9) >> 2;
LABEL_39:
  for ( j = 0; j < v10; ++j )
  {
    if ( *(uint32_t *)(a2[10] + 4 * j) != 0 )
    {
      v13 = (uint32_t *)(*((uint32_t *)a3 + 10) + 4 * j);
      if ( *v13 != 0 )
        sub_494240(a1, *v13);
    }
  }
  v14 = a2[14];
  if ( v14 != 0 )
    v15 = (a2[15] - v14) >> 2;
  else
    v15 = 0;
  v16 = *((uint32_t *)a3 + 14);
  if ( v16 != 0 && v15 < (*((uint32_t *)a3 + 15) - v16) >> 2 )
  {
    result = (uint32_t *)a2[14];
    if ( result == nullptr )
    {
      v18 = 0;
      goto LABEL_56;
    }
    v19 = a2[15];
  }
  else
  {
    result = *((uint32_t **)a3 + 14);
    if ( result == nullptr )
    {
      v18 = 0;
      goto LABEL_56;
    }
    v19 = *((uint32_t *)a3 + 15);
  }
  v18 = (v19 - (int)result) >> 2;
LABEL_56:
  for ( k = 0; k < v18; ++k )
  {
    result = *(uint32_t **)(a2[14] + 4 * k);
    if ( result != nullptr )
    {
      result = (uint32_t *)(*((uint32_t *)a3 + 14) + 4 * k);
      if ( *result != 0 )
        result = (uint32_t *)sub_494240(a1, *result);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x52DE60 IRDActiveObject__vmt2B8
// ------------------------------------------------------------
// ★ vmt2B8 观察者组件卸载：逐项 sub_492980 释放

void **/*stdcall*/ sub_52DE60(int a1, int a2)
{
  void ***v3; // ecx
  void ***v4; // ecx
  void ****v5; // esi
  int v6; // edi
  void ***v7; // ecx
  void ***v8; // ecx
  void ***v9; // ecx
  void ***v10; // ecx
  int v11; // eax
  unsigned int v12; // ecx
  int v13; // edx
  int v14; // eax
  int v15; // edi
  int v16; // edi
  int j; // esi
  void ****v18; // ecx
  void *v19; // edx
  int v20; // eax
  unsigned int v21; // ecx
  int v22; // edx
  void **result; // eax
  int v24; // edi
  int v25; // edi
  int k; // esi
  void ****v27; // ecx
  int v28; // eax
  void *v29; // edx
  int i; // [esp+14h] [ebp+8h]

  if ( *(uint32_t *)a1 != 0 && *(uint32_t *)a2 != 0 )
    sub_492980(*(void ****)a1, *(void **)a2);
  v3 = *(void ****)(a1 + 4);
  if ( v3 != nullptr && *(uint32_t *)(a2 + 4) != 0 )
    sub_492980(v3, *(void **)(a2 + 4));
  v4 = *(void ****)(a1 + 8);
  if ( v4 != nullptr && *(uint32_t *)(a2 + 8) != 0 )
    sub_492980(v4, *(void **)(a2 + 8));
  v5 = (void ****)(a1 + 12);
  v6 = a2 - a1;
  for ( i = 2; i != 0; --i )
  {
    if ( *v5 != nullptr && *(void ****)((char *)v5 + v6) != nullptr )
      sub_492980(*v5, *(void ****)((char *)v5 + v6));
    ++v5;
  }
  v7 = *(void ****)(a1 + 20);
  if ( v7 != nullptr && *(uint32_t *)(a2 + 20) != 0 )
    sub_492980(v7, *(void **)(a2 + 20));
  v8 = *(void ****)(a1 + 24);
  if ( v8 != nullptr && *(uint32_t *)(a2 + 24) != 0 )
    sub_492980(v8, *(void **)(a2 + 24));
  v9 = *(void ****)(a1 + 28);
  if ( v9 != nullptr && *(uint32_t *)(a2 + 28) != 0 )
    sub_492980(v9, *(void **)(a2 + 28));
  v10 = *(void ****)(a1 + 32);
  if ( v10 != nullptr && *(uint32_t *)(a2 + 32) != 0 )
    sub_492980(v10, *(void **)(a2 + 32));
  v11 = *(uint32_t *)(a1 + 40);
  if ( v11 != 0 )
    v12 = (*(uint32_t *)(a1 + 44) - v11) >> 2;
  else
    v12 = 0;
  v13 = *(uint32_t *)(a2 + 40);
  if ( v13 != 0 && v12 < (*(uint32_t *)(a2 + 44) - v13) >> 2 )
  {
    v14 = *(uint32_t *)(a1 + 40);
    if ( v14 == 0 )
    {
      v15 = 0;
      goto LABEL_39;
    }
    v16 = *(uint32_t *)(a1 + 44);
  }
  else
  {
    v14 = *(uint32_t *)(a2 + 40);
    if ( v14 == 0 )
    {
      v15 = 0;
      goto LABEL_39;
    }
    v16 = *(uint32_t *)(a2 + 44);
  }
  v15 = (v16 - v14) >> 2;
LABEL_39:
  for ( j = 0; j < v15; ++j )
  {
    v18 = (void ****)(*(uint32_t *)(a1 + 40) + 4 * j);
    if ( *v18 != nullptr )
    {
      v19 = *(void **)(*(uint32_t *)(a2 + 40) + 4 * j);
      if ( v19 != nullptr )
        sub_492980(*v18, v19);
    }
  }
  v20 = *(uint32_t *)(a1 + 56);
  if ( v20 != 0 )
    v21 = (*(uint32_t *)(a1 + 60) - v20) >> 2;
  else
    v21 = 0;
  v22 = *(uint32_t *)(a2 + 56);
  if ( v22 != 0 && v21 < (*(uint32_t *)(a2 + 60) - v22) >> 2 )
  {
    result = *(void ***)(a1 + 56);
    if ( result == nullptr )
    {
      v24 = 0;
      goto LABEL_56;
    }
    v25 = *(uint32_t *)(a1 + 60);
  }
  else
  {
    result = *(void ***)(a2 + 56);
    if ( result == nullptr )
    {
      v24 = 0;
      goto LABEL_56;
    }
    v25 = *(uint32_t *)(a2 + 60);
  }
  v24 = (v25 - (int)result) >> 2;
LABEL_56:
  for ( k = 0; k < v24; ++k )
  {
    result = *(void ***)(a1 + 56);
    v27 = (void ****)&result[k];
    if ( *v27 != nullptr )
    {
      v28 = *(uint32_t *)(a2 + 56);
      v29 = *(void **)(v28 + 4 * k);
      result = (void **)(v28 + 4 * k);
      if ( v29 != nullptr )
        result = sub_492980(*v27, v29);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x52E020 IRDActiveObject__vmt368
// ------------------------------------------------------------
// ★ vmt368 光环显示链逐帧推进：+6544 链表、1s 窗淡出（lerp）、超时摘链

void **/*userpurge*/ IRDActiveObject__vmt368@<eax>(int a1@<ecx>, double a2@<st0>, int a3, int a4, float a5)
{
  int v5; // edi
  void **result; // eax
  uint32_t *v7; // esi
  int v8; // ecx
  int v9; // ebx
  uint32_t *v10; // ebx
  int v11; // edi

  v5 = a1;
  result = *(void ***)(a1 + 6548);
  if ( result != nullptr )
  {
    result = *(void ***)(a1 + 6544);
    v7 = *result;
    if ( *result != result )
    {
      do
      {
        result = (void **)sub_699000(v5 + 64);
        v8 = v7[3];
        v9 = (int)result - v8;
        if ( (int)result - v8 <= 1000 )
        {
          sub_4049F0(0.0, 50.0, (int)result - v8, 1000, 1);
          v11 = (uint64_t)a2 - 166;
          a2 = sub_4049C0(255.0, 0.0, v9, 1000);
          result = (void **)sub_499690(
                              dword_79C0B0,
                              a3,
                              a4,
                              0,
                              v11,
                              a5,
                              v7[2],
                              0.5,
                              1056964608,
                              0.0,
                              ((uint8_t)(uint64_t)a2 << 24) | 0xFFFFFF,
                              0.0,
                              0.0);
          v7 = (uint32_t *)*v7;
          v5 = a1;
        }
        else
        {
          v10 = (uint32_t *)*v7;
          if ( v7 != *(uint32_t **)(v5 + 6544) )
          {
            *(uint32_t *)v7[1] = v10;
            *(uint32_t *)(*v7 + 4) = v7[1];
            j__free(v7);
            result = (void **)(*(uint32_t *)(v5 + 6548) - 1);
            *(uint32_t *)(v5 + 6548) = result;
          }
          v7 = v10;
        }
      }
      while ( v7 != *(uint32_t **)(v5 + 6544) );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x52E130 sub_52E130
// ------------------------------------------------------------
// list 容量检查器：0x1FFFFFFF 上限，超限 _CxxThrowException(std::length_error("list<T> too long"))

int /*thiscall*/ sub_52E130(uint32_t *this, unsigned int a2)
{
  int v2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  v2 = *(this + 2);
  if ( 0x1FFFFFFF - v2 < a2 )
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
// 0x52E1C0 IRDActiveObject__vmt364
// ------------------------------------------------------------
// ★ vmt364 光环/标记显示入链：sub_4F32A0(a2) 事件转换 + 时钟 sub_699000(+16) +
// +6544(+1636→+4) 链头 → sub_52DAA0 建节点 → sub_52E130 容量检查 → 头插

uint32_t */*thiscall*/ IRDActiveObject__vmt364(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // edi
  int v5; // ebx
  uint32_t *result; // eax
  int v7; // [esp-8h] [ebp-1Ch]
  uint32_t v8[2]; // [esp+Ch] [ebp-8h] BYREF

  v8[0] = sub_4F32A0(a2);
  v3 = sub_699000((int)(this + 16));
  v4 = *(this + 1636);
  v7 = *(uint32_t *)(v4 + 4);
  v8[1] = v3;
  v5 = sub_52DAA0(v4, v7, v8);
  sub_52E130(1);
  *(uint32_t *)(v4 + 4) = v5;
  result = *(uint32_t **)(v5 + 4);
  *result = v5;
  return result;
}



// ------------------------------------------------------------
// ============
// 【分区 7】池归还辅助 + CNBlueBallBox（0x52E220-0x52E510）
// 池化归还薄壳在 0x52E220（sub_657740 转发）；0x52E240-0x52E4D0 图像包/树节点杂项；
// CNBlueBallBox（蓝球箱破坏物，vmt2E4 转发 CNRDObject__vmtCC(100,...)）。
// ============

// 0x52E220 sub_52E220
// ------------------------------------------------------------
// 池化归还薄壳：→ sub_657740(a1, a2)（粒子/特效池归还，P33）

int /*cdecl*/ sub_52E220(int a1, int a2)
{
  return sub_657740(a1, a2);
}



// ------------------------------------------------------------
// 0x52E240 sub_52E240
// ------------------------------------------------------------
// 图像包字段写入（11L float* this）

void /*thiscall*/ sub_52E240(float *this, int a2)
{
  int v3; // edi
  float v4; // [esp+Ch] [ebp-20h]
  float v5; // [esp+10h] [ebp-1Ch]
  int v6; // [esp+24h] [ebp-8h]

  v3 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  v6 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  v5 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
  v4 = (float)v6;
  *(this + 181) = sub_4049C0(v4, v5, a2 - 1, v3 - 1);
}



// ------------------------------------------------------------
// 0x52E2B0 j_nullsub_3
// ------------------------------------------------------------
// j_nullsub_3 空桩（3L）

// attributes: thunk
void j_nullsub_3()
{
  nullsub_3();
}



// ------------------------------------------------------------
// 0x52E2C0 sub_52E2C0
// ------------------------------------------------------------
// 薄转发（3L cdecl）

int /*cdecl*/ sub_52E2C0(int a1, int a2)
{
  return sub_657740(a1, a2);
}



// ------------------------------------------------------------
// 0x52E2E0 sub_52E2E0
// ------------------------------------------------------------
// 薄转发（3L cdecl）

int /*cdecl*/ sub_52E2E0(int a1, int a2)
{
  return sub_657740(a1, a2);
}



// ------------------------------------------------------------
// 0x52E300 sub_52E300
// ------------------------------------------------------------
// 容器辅助（16L cdecl）

uint32_t */*cdecl*/ sub_52E300(uint32_t *a1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = a1;
  v2 = (int *)*a1;
  if ( *(uint8_t *)(*a1 + 21) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 21) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x52E320 sub_52E320
// ------------------------------------------------------------
// 容器辅助（13L cdecl）

int /*cdecl*/ sub_52E320(int a1)
{
  if ( dword_9B9354 == 0 )
  {
    if ( (dword_9B7FE4 & 1) == 0 )
    {
      dword_9B7FE4 |= 1u;
      sub_657800(a1, 256);
      atexit(sub_6BFDB0);
    }
    dword_9B9354 = (int)&unk_9B7FC4;
  }
  return sub_6578B0(a1);
}



// ------------------------------------------------------------
// 0x52E3B0 sub_52E3B0
// ------------------------------------------------------------
// 容器辅助（13L cdecl）

int /*cdecl*/ sub_52E3B0(int a1)
{
  if ( dword_9B9380 == 0 )
  {
    if ( (dword_9B8008 & 1) == 0 )
    {
      dword_9B8008 |= 1u;
      sub_657800(a1, 256);
      atexit(sub_6BFDC0);
    }
    dword_9B9380 = (int)&unk_9B7FE8;
  }
  return sub_6578B0(a1);
}



// ------------------------------------------------------------
// 0x52E440 sub_52E440
// ------------------------------------------------------------
// 惰性初始化表（13L：dword_9B93A4/dword_9B802C 标志 + atexit(sub_6BFDD0)）

int /*cdecl*/ sub_52E440(int a1)
{
  if ( dword_9B93A4 == 0 )
  {
    if ( (dword_9B802C & 1) == 0 )
    {
      dword_9B802C |= 1u;
      sub_657800(a1, 256);
      atexit(sub_6BFDD0);
    }
    dword_9B93A4 = (int)&unk_9B800C;
  }
  return sub_6578B0(a1);
}



// ------------------------------------------------------------
// 0x52E4D0 sub_52E4D0
// ------------------------------------------------------------
// 树节点递归释放（15L stdcall：+21 哨兵沿 +0/+8 链 free）

char /*stdcall*/ sub_52E4D0(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_52E4D0(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x52E510 CNBlueBallBox__vmt2E4
// ------------------------------------------------------------
// CNBlueBallBox__vmt2E4 初始化：vt+51(100, +36 首值, 0,0,0,0)（CNRDObject__vmtCC 同款显示设定）

int /*thiscall*/ CNBlueBallBox__vmt2E4(uint32_t **this)
{
  return ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
           this,
           100,
           **(this + 36),
           0,
           0,
           0,
           0);
}


