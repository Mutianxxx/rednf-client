// ============================================================
// 【40JP逆向源代码工程】game/login_channel.cpp
// 模块: 登录/频道连接 CNEntranceChannel + 选区→选角→进副本→结算链路
// 来源: work/dump_combat.txt  区块: 0x470000-0x480000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
// 函数数: 291
// ------------------------------------------------------------
// ★ 登录协议阶段图（自 connectServer 至 M_CHARACTER_SELECT 的完整链）：
//   阶段① 频道列表获取（HTTP）
//     CNEntranceChannel 的 HTTP 线程 0x46EB70"StartAddress"（见 ui_icon_perf.cpp，
//     "MERONG(0.9/;p)" 解密）→ 结果存 dword_98BA5C → 0x471CC0
//     checkHTTPChannelDataWork 轮询（超时 5000ms/失败自证）→ 成功调 0x471850。
//   0x471850 retrieveServerInfo（IDA 误名 money_put::_Putmfld，日志串自证真名）：
//     解析 "user_age#server_count|…"（分隔符 ;|#,,）→ 填 6 服务器型 × 5 频道型 ×
//     N 频道条目（104 字节/条：名字/负载 cur/max/满员旗标>95%/地址/端口），
//     打印 "** server_count = %d  user_age = %d"。
//   阶段② 选区界面（CNEntranceChannel__vmt4 = 0x471280 帧 tick）
//     进图一次性 M_CHARACTER_SELECT → 服务器页签×6(BUTTON_04)/频道型×5(BUTTON_03)
//     /翻页(CLICK_BUTTON1) → 频道单击(BUTTON_02)或双击(timeGetTime 差 < +1744 阈值)
//     → 调 connectServer。
//   阶段③ 连接频道（connectServer = 0x470640，日志串自证）
//     校验 server_type<6 / channel_type<5 / index 有效 → 连接历史存 +74/+76/+78
//     （channel_type 4 除外）→ 组登录串 "%d?%s?%d?%s?%s" → sub_488690 切分 →
//     sub_41E4F0 发出（发包 API 0x423200/423380 见 src/nengine/net_socket.cpp）；
//     测试账号白名单 dnftest299/300、testman412/425 → dword_8F7A24+244=2（"TN"）。
//   阶段④ 预约/重连：0x46EAA0 reserveConnection 预约 → 0x46E360
//     startTimerForReservedConnectChannel（500ms tick）→ 0x470A80
//     processReservedConnection 自动重连。
//   阶段⑤ 选角：CNEntranceModule__vmt4（0x46C300，见 ui_icon_perf.cpp）+
//     键盘导航 0x46BD70（SELECT_CHARACTER/CLICK_BUTTON4）。
// ★ 其余链路：副本创建（DUNGEON create FAIL 自证）→ 进副本一次性演出（0x475810
//   巨型，docs/13 遗留#3）→ 结算（RESULT_* 事件 + CNRDResult__vmt0）→
//   社交管理器（Friend/Member/Guild/Buddy）→ 触发条件评估器（0x47BBE0）。
// 交叉引用：频道表条目操作 0x46ECC0/0x46EF10/0x46E6B0 等在 ui_icon_perf.cpp 尾部；
//   发包 API 0x423200/0x423380 已 L1 精修于 src/nengine/net_socket.cpp（docs/13 §5）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】CNEntranceChannel 频道连接核心（0x470330-0x471280）
// 频道表容器（104 字节/条目的定长搬运 vector，容量上限 41297762 条）→
// connectServer（协议阶段③）→ processReservedConnection（阶段④ 重连）。
// ============================================================
// ------------------------------------------------------------
// 0x470330 sub_470330
// ------------------------------------------------------------
// 频道表 vector 定点插入：104 字节/条目（qmemcpy 0x68）；尾部插入 / 中部
// 腾挪（sub_46ECC0/46E6B0）/ 扩容重建（operator new + free）三路；
// 41297762 与 1321528399 = 扩容运算魔数（×4 溢出等价）
int /*thiscall*/ sub_470330(int *this, int a2, unsigned int a3, const void *a4)
{
  int result; // eax
  int v6; // edi
  unsigned int v7; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // edi
  void *v13; // eax
  int v14; // ecx
  int v15; // eax
  unsigned int v16; // esi
  char *v17; // esi
  int v18; // ecx
  int v20; // esi
  int v21; // [esp-Ch] [ebp-9Ch]
  unsigned int v22; // [esp-8h] [ebp-98h]
  int v23; // [esp+0h] [ebp-90h] BYREF
  int v24; // [esp+Ch] [ebp-84h]
  void *Block; // [esp+10h] [ebp-80h]
  uint32_t v26[28]; // [esp+14h] [ebp-7Ch] BYREF
  int v27; // [esp+8Ch] [ebp-4h]
  int v28; // [esp+98h] [ebp+8h]
  int v29; // [esp+A0h] [ebp+10h]

  result = dword_796E50;
  qmemcpy(v26, a4, 0x68u);
  v6 = *(this + 1);
  v26[26] = dword_796E50;
  v26[27] = &v23;
  if ( v6 != 0 )
  {
    result = 1321528399 * (*(this + 3) - v6);
    v7 = (*(this + 3) - v6) / 104;
  }
  else
  {
    v7 = 0;
  }
  if ( a3 != 0 )
  {
    if ( v6 != 0 )
      v8 = (*(this + 2) - v6) / 104;
    else
      v8 = 0;
    if ( 41297762 - v8 < a3 )
      sub_41D5A0(this);
    if ( v6 != 0 )
      v9 = (*(this + 2) - v6) / 104;
    else
      v9 = 0;
    if ( v7 >= a3 + v9 )
    {
      v18 = *(this + 2);
      v29 = v18;
      if ( (v18 - a2) / 104 >= a3 )
      {
        v28 = v18 - 104 * a3;
        *(this + 2) = sub_46ED50(v28, v18, v18);
        sub_46ECC0(a2, v28, v29);
        return sub_46E6B0(a2, a2 + 104 * a3, v26);
      }
      else
      {
        sub_46ED50(a2, v18, a2 + 104 * a3);
        v22 = a3 - (*(this + 2) - a2) / 104;
        v21 = *(this + 2);
        v27 = 2;
        sub_46F6B0(v21, v22, v26);
        v20 = 104 * a3 + *(this + 2);
        *(this + 2) = v20;
        return sub_46E6B0(a2, v20 - 104 * a3, v26);
      }
    }
    else
    {
      if ( 41297762 - (v7 >> 1) >= v7 )
        v10 = (v7 >> 1) + v7;
      else
        v10 = 0;
      if ( v6 != 0 )
        v11 = (*(this + 2) - v6) / 104;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_46E3D0(this);
      v12 = 104 * v10;
      v13 = operator new(104 * v10);
      v14 = *(this + 1);
      Block = v13;
      v27 = 0;
      v24 = sub_46ED50(v14, a2, v13);
      sub_46EF10(v24, a3, v26);
      sub_46ED50(a2, *(this + 2), 104 * a3 + v24);
      v15 = *(this + 1);
      if ( v15 != 0 )
        v15 = (*(this + 2) - v15) / 104;
      v16 = v15 + a3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      result = (int)Block;
      v17 = (char *)Block + 104 * v16;
      *(this + 3) = (int)Block + v12;
      *(this + 2) = (int)v17;
      *(this + 1) = result;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4705D0 sub_4705D0
// ------------------------------------------------------------
// 频道表追加一条并返回新条目指针（配合 0x470330 定点插入）
uint32_t */*thiscall*/ sub_4705D0(uint32_t *this, uint32_t *a2, char *a3, const void *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 104 != 0 )
    v6 = (int)&a3[-v5] / 104;
  else
    v6 = 0;
  sub_470330((int)this, a3, 1u, a4);
  *a2 = *(this + 1) + 104 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x470640 sub_470640
// ------------------------------------------------------------
// CNEntranceChannel::connectServer —— 协议阶段③ 连接频道（日志串自证）：
// 1) 校验 server_type<6 / channel_type<5 / 频道索引在表内（无效即日志返回 -1）
// 2) channel_type!=4 时保存连接历史 +74/+76/+78（"connection history saved"）
// 3) 条目 +88 满员旗标为 1 → 拒绝
// 4) byte_99FCD1 ← 条目首字节；sub_46E230 取年龄档 → sprintf("%d?%s?%d?%s?%s")
//    登录串 → sub_488690 按 '?' 切分 → sub_41E4F0 发出登录请求
// 5) sub_48B7C0(13/14/15/16) 置请求参数；135 号串提示（+79==-1 时）
// 6) 返回值解析 atol → dword_8F7A24+244（==2 → sub_419CF0("TN")）
// 7) 测试账号白名单 dnftest299/300、testman412/425（tolower 比对）→ 同置 "TN"
//    （docs/13 §6：开发期测试账号残留）
void /*thiscall*/ sub_470640(uint32_t *this, int ArgList, int a3, unsigned int a4)
{
  uint32_t *v6; // eax
  int v7; // edx
  uint32_t *v8; // eax
  int v9; // esi
  void **v10; // esi
  int v11; // eax
  char *v12; // eax
  const char *v13; // eax
  int v14; // eax
  signed int v15; // esi
  signed int i; // edi
  void **v17; // edi
  const char *v18; // [esp-18h] [ebp-33Ch]
  int v19; // [esp-14h] [ebp-338h]
  const char *v20; // [esp-10h] [ebp-334h]
  const char *v21; // [esp-Ch] [ebp-330h]
  char v22[4]; // [esp+4h] [ebp-320h] BYREF
  void *Block; // [esp+8h] [ebp-31Ch]
  void **v24; // [esp+Ch] [ebp-318h]
  int v25; // [esp+10h] [ebp-314h]
  char Buffer[512]; // [esp+14h] [ebp-310h] BYREF
  char v27[256]; // [esp+214h] [ebp-110h] BYREF
  int v28; // [esp+314h] [ebp-10h]
  int v29; // [esp+320h] [ebp-4h]
  uint32_t *v30; // [esp+330h] [ebp+Ch]

  v28 = dword_796E50;
  if ( *(uint8_t *)(*(this + 42) + 17) == 1 )
  {
    Block = nullptr;
    v24 = nullptr;
    v25 = 0;
    v29 = 0;
    if ( ArgList >= 6 )
    {
      off_77F3FC("CNEntranceChannel::connectServer - invalied server type. server_type = %d", ArgList);
      v29 = -1;
      return;
    }
    if ( a3 >= 5 )
    {
      off_77F3FC("CNEntranceChannel::connectServer - invalied channel type. channel_type = %d", a3);
      v29 = -1;
      return;
    }
    v6 = this + 35 * ArgList;
    v7 = v6[4 * a3 + 170];
    v8 = &v6[4 * a3];
    v30 = v8;
    if ( v7 == 0 || a4 >= (v8[171] - v7) / 104 )
    {
      off_77F3FC("CNEntranceChannel::connectServer - invalied channel index. index = %d", a4);
      v29 = -1;
      return;
    }
    if ( a3 != 4 )
    {
      *(this + 74) = ArgList;
      *(this + 76) = a3;
      *(this + 78) = a4;
      off_77F3FC(
        "CNEntranceChannel::connectServer - connection history saved. server_type = %d, channel_type = %d, channel_index = %d",
        ArgList,
        a3,
        a4);
    }
    v9 = v30[170] + 104 * a4;
    if ( *(uint8_t *)(v9 + 88) == 1 )
    {
      v10 = (void **)Block;
      v29 = -1;
      if ( Block == nullptr )
        return;
      if ( Block == v24 )
        goto LABEL_31;
      do
        sub_41B010(v10++);
      while ( v10 != v24 );
      goto LABEL_30;
    }
    byte_99FCD1 = *(uint8_t *)v9;
    v11 = sub_46E230(this, v9 + 64, *(uint32_t *)(v9 + 84), dword_8F7A24 + 113, dword_8F7A24 + 177);
    sprintf(Buffer, "%d?%s?%d?%s?%s", v11, v18, v19, v20, v21);
    sub_488690(v22, Buffer, "?", 0);
    sub_48B7C0(13, *(this + 3));
    sub_48B7C0(14, *(this + 4));
    sub_48B7C0(15, 0);
    sub_48B7C0(16, 0);
    sub_41E4F0(v22);
    if ( *(this + 79) == -1 )
    {
      v12 = sub_422E70(135);
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v12, 0);
    }
    v13 = (const char *)sub_41ACF0(Block);
    v14 = j__atol(v13);
    *(uint32_t *)(dword_8F7A24 + 244) = v14;
    *(uint32_t *)(dword_8F7A24 + 244) = 0;
    if ( v14 == 2 )
      sub_419CF0("TN");
    v15 = dword_8F7A24 + 113 + strlen((const char *)(dword_8F7A24 + 113)) + 1 - (dword_8F7A24 + 114);
    memset(v27, 0, sizeof(v27));
    for ( i = 0; i < v15; ++i )
      v27[i] = tolower(*(uint8_t *)(dword_8F7A24 + i + 113));
    if ( strcmp(v27, "dnftest299") == 0
      || strcmp(v27, "dnftest300") == 0
      || strcmp(v27, "testman412") == 0
      || strcmp(v27, "testman425") == 0 )
    {
      *(uint32_t *)(dword_8F7A24 + 244) = 2;
      sub_419CF0("TN");
    }
    *(uint8_t *)(*(this + 42) + 17) = 0;
    v10 = (void **)Block;
    v29 = -1;
    if ( Block != nullptr )
    {
      v17 = v24;
      if ( Block == v24 )
      {
LABEL_31:
        j__free(v10);
        return;
      }
      do
        sub_41B010(v10++);
      while ( v10 != v17 );
LABEL_30:
      v10 = (void **)Block;
      goto LABEL_31;
    }
  }
}


// ------------------------------------------------------------
// 0x470A80 sub_470A80
// ------------------------------------------------------------
// CNEntranceChannel::processReservedConnection（日志串自证）—— 协议阶段④：
// 预约三元组(+300/+308/+316)有效 → 打印目标频道名/端口 → 强制选中界面按钮态 →
// connectServer 重连 → 清预约。由 vmt4 的 500ms 定时器（0x46E360 启动）触发
void /*thiscall*/ sub_470A80(int this)
{
  int v2; // eax
  int v3; // edi

  v2 = *(uint32_t *)(this + 316);
  if ( v2 != -1 )
  {
    v3 = *(uint32_t *)(16 * *(uint32_t *)(this + 308) + this + 140 * *(uint32_t *)(this + 300) + 680);
    off_77F3FC(
      "CNEntranceChannel::processReservedConnection = %s %d",
      (const char *)(v3 + 104 * v2 + 64),
      *(uint32_t *)(104 * v2 + v3 + 84));
    *(uint8_t *)(*(uint32_t *)(this + 168) + 17) = 1;
    sub_470640((int *)this, *(uint32_t *)(this + 300), *(uint32_t *)(this + 308), *(uint32_t *)(this + 316));
    *(uint32_t *)(this + 300) = 6;
    *(uint32_t *)(this + 308) = 5;
    *(uint32_t *)(this + 316) = -1;
    *(uint8_t *)(this + 332) = 0;
  }
}



// ------------------------------------------------------------
// 0x470B20 sub_470B20
// ------------------------------------------------------------
// 频道条目入表（0x4705D0 包装：容量够则原地 +104）
char */*thiscall*/ sub_470B20(int this, const void *a2)
{
  int v3; // edi
  unsigned int v4; // ecx
  char *v5; // edi
  char *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 104;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 104 )
    return (char *)sub_4705D0((uint32_t *)this, &a2, *(char **)(this + 8), a2);
  v5 = *(char **)(this + 8);
  result = sub_46EF10(v5, (char *)1, a2);
  *(uint32_t *)(this + 8) = v5 + 104;
  return result;
}



// ------------------------------------------------------------
// 0x470BB0 sub_470BB0
// ------------------------------------------------------------
int ***/*thiscall*/ sub_470BB0(uint32_t *this, int ***a2, int **a3)
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
  if ( *((uint8_t *)a3 + 85) != 0 )
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
  sub_46E5F0(&a3);
  if ( *((uint8_t *)*v3 + 85) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 85) == 0 )
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
      if ( *((uint8_t *)v4 + 85) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_46E470(v4);
        v7 = v25;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 85) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_46E450(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)v3[2] + 85) != 0 )
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
    if ( *((uint8_t *)v4 + 85) == 0 )
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
  v14 = *((uint8_t *)v5 + 84);
  *((uint8_t *)v5 + 84) = *((uint8_t *)v3 + 84);
  *((uint8_t *)v3 + 84) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 84) == 1 )
  {
    v15 = v25;
    if ( v4 != *(int **)(v25[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 84) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 84) == 0 )
          {
            *((uint8_t *)v16 + 84) = 1;
            *((uint8_t *)v6 + 84) = 0;
            sub_46E3F0(v6);
            v16 = (uint32_t *)v6[2];
            v15 = v25;
          }
          if ( *((uint8_t *)v16 + 85) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 84) != 1 || *(uint8_t *)(v16[2] + 84) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 84) == 1 )
            {
              *(uint8_t *)(*v16 + 84) = 1;
              *((uint8_t *)v16 + 84) = 0;
              sub_46E490(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 84) = *((uint8_t *)v6 + 84);
            *((uint8_t *)v6 + 84) = 1;
            *(uint8_t *)(v16[2] + 84) = 1;
            sub_46E3F0(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 84) == 0 )
          {
            *((uint8_t *)v16 + 84) = 1;
            *((uint8_t *)v6 + 84) = 0;
            sub_46E490(v6);
            v16 = (uint32_t *)*v6;
            v15 = v25;
          }
          if ( *((uint8_t *)v16 + 85) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 84) != 1 || *(uint8_t *)(*v16 + 84) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 84) == 1 )
            {
              *(uint8_t *)(v16[2] + 84) = 1;
              *((uint8_t *)v16 + 84) = 0;
              sub_46E3F0(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 84) = *((uint8_t *)v6 + 84);
            *((uint8_t *)v6 + 84) = 1;
            *(uint8_t *)(*v16 + 84) = 1;
            sub_46E490(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 84) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(v15[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 84) = 1;
  }
  sub_46F6E0((char *)Block + 12);
  j__free(Block);
  v17 = v25[2];
  if ( v17 != 0 )
    v25[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x470E80 sub_470E80
// ------------------------------------------------------------
char /*stdcall*/ sub_470E80(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 85);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_470E80(i[2]);
    i = (void **)*i;
    sub_470310(v1);
    j__free(v1);
    result = *((uint8_t *)i + 85);
  }
  return result;
}



// ------------------------------------------------------------
// 0x470ED0 sub_470ED0
// ------------------------------------------------------------
int ***/*thiscall*/ sub_470ED0(uint32_t *this, int ***a2, int **a3)
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
  if ( *((uint8_t *)a3 + 153) != 0 )
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
  sub_46E7B0(&a3);
  if ( *((uint8_t *)*v3 + 153) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 153) == 0 )
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
      if ( *((uint8_t *)v4 + 153) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_46E710(v4);
        v7 = v25;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 153) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_46E6E0(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)v3[2] + 153) != 0 )
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
    if ( *((uint8_t *)v4 + 153) == 0 )
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
  v14 = *((uint8_t *)v5 + 152);
  *((uint8_t *)v5 + 152) = *((uint8_t *)v3 + 152);
  *((uint8_t *)v3 + 152) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 152) == 1 )
  {
    v15 = v25;
    if ( v4 != *(int **)(v25[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 152) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 152) == 0 )
          {
            *((uint8_t *)v16 + 152) = 1;
            *((uint8_t *)v6 + 152) = 0;
            sub_46ECF0(v6);
            v16 = (uint32_t *)v6[2];
            v15 = v25;
          }
          if ( *((uint8_t *)v16 + 153) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 152) != 1 || *(uint8_t *)(v16[2] + 152) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 152) == 1 )
            {
              *(uint8_t *)(*v16 + 152) = 1;
              *((uint8_t *)v16 + 152) = 0;
              sub_46E740(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 152) = *((uint8_t *)v6 + 152);
            *((uint8_t *)v6 + 152) = 1;
            *(uint8_t *)(v16[2] + 152) = 1;
            sub_46ECF0(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 152) == 0 )
          {
            *((uint8_t *)v16 + 152) = 1;
            *((uint8_t *)v6 + 152) = 0;
            sub_46E740(v6);
            v16 = (uint32_t *)*v6;
            v15 = v25;
          }
          if ( *((uint8_t *)v16 + 153) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 152) != 1 || *(uint8_t *)(*v16 + 152) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 152) == 1 )
            {
              *(uint8_t *)(v16[2] + 152) = 1;
              *((uint8_t *)v16 + 152) = 0;
              sub_46ECF0(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 152) = *((uint8_t *)v6 + 152);
            *((uint8_t *)v6 + 152) = 1;
            *(uint8_t *)(*v16 + 152) = 1;
            sub_46E740(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 152) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(v15[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 152) = 1;
  }
  sub_46F490((char *)Block + 16);
  j__free(Block);
  v17 = v25[2];
  if ( v17 != 0 )
    v25[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x471230 sub_471230
// ------------------------------------------------------------
char /*stdcall*/ sub_471230(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 153);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_471230(i[2]);
    i = (void **)*i;
    sub_470320(v1);
    j__free(v1);
    result = *((uint8_t *)i + 153);
  }
  return result;
}



// ============================================================
// 【分区 2】选区界面帧处理（0x471280-0x471850）
// CNEntranceChannel__vmt4 = 选区界面帧 tick（协议阶段②）。
// ============================================================
// ------------------------------------------------------------
// 0x471280 CNEntranceChannel__vmt4
// ------------------------------------------------------------
// CNEntranceChannel::vmt4 —— 选区界面帧 tick（协议阶段②）：
// 主帧循环 sub_433690 → 预约定时器到点则 processReservedConnection →
// 一次性 M_CHARACTER_SELECT（+1460）→ 各按钮命中(dword_79BE34 焦点窗口)：
// 服务器页签×6（BUTTON_04，+64 起）/频道型×5（BUTTON_03，+92 起）/
// 频道翻页（CLICK_BUTTON1，+172/-1 页与 +176/+1 页，页容量 10）/频道单击
// （BUTTON_02 → channel_type 2/3 直连或按高亮列）→ 双击检测（+1728/+1732 记槽位、
// +1736/+1740 timeGetTime，差 < +1744 阈值即 connect）→ connectServer(server, type, idx)
void /*thiscall*/ sub_471280(int this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int *v6; // ebx
  int v7; // eax
  int v8; // edi
  int *v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // ecx
  int v17; // edi
  int v18; // eax
  DWORD Time; // eax
  int v20; // eax
  bool v21; // cl
  int v22; // edx
  int v23; // edi
  int *i; // ebx
  int v25; // eax
  int v26; // eax
  DWORD v27; // eax
  int v28; // eax
  bool v29; // cl
  int v30; // edx
  int v31; // [esp+8h] [ebp-8h]
  int v32; // [esp+Ch] [ebp-4h]
  int v33; // [esp+Ch] [ebp-4h]

  sub_433690();
  *((uint32_t *)dword_8F8528 + 621) = *(uint32_t *)(this + 1456);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, 10) != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 84) != 0 )
  {
    sub_41C860(dword_8F7A24);
  }
  if ( *(uint8_t *)(this + 332) != 0 )
  {
    v2 = *(uint32_t *)(this + 344);
    if ( sub_699000(this + 320) >= v2 )
      sub_470A80(this);
  }
  else
  {
    if ( *(uint8_t *)(this + 1460) == 0 )
    {
      sub_432EA0("M_CHARACTER_SELECT", -1, 0, 0);
      *(uint8_t *)(this + 1460) = 1;
    }
    v3 = *(uint32_t *)(this + 164);
    if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
    {
      sub_432EA0("CLICK_BUTTON1", -1, 0, 0);
      sub_46F3E0(this);
    }
    v4 = *(uint32_t *)(this + 180);
    if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) )
    {
      sub_432EA0("CLICK_BUTTON3", -1, 0, 0);
      sub_41C860(dword_8F7A24);
    }
    if ( *(uint32_t *)(this + 1464) == 1 )
    {
      v5 = 0;
      v6 = (int *)(this + 64);
      do
      {
        v7 = *v6;
        if ( *v6 != 0
          && *(uint8_t *)(v7 + 17) != 0
          && dword_79BE34 == *(uint32_t *)(v7 + 12)
          && *(uint32_t *)(this + 12) != v5 )
        {
          sub_432EA0("BUTTON_04", -1, 0, 0);
          *(uint32_t *)(this + 12) = v5;
          sub_46E810(this);
        }
        ++v5;
        ++v6;
      }
      while ( v5 < 6 );
      if ( *(uint32_t *)(this + 12) != 6 )
      {
        v8 = 0;
        v9 = (int *)(this + 92);
        do
        {
          v10 = *v9;
          if ( *v9 != 0
            && *(uint8_t *)(v10 + 17) != 0
            && dword_79BE34 == *(uint32_t *)(v10 + 12)
            && *(uint32_t *)(this + 16) != v8 )
          {
            sub_432EA0("BUTTON_03", -1, 0, 0);
            *(uint32_t *)(this + 16) = v8;
            sub_46E810(this);
          }
          ++v8;
          ++v9;
        }
        while ( v8 < 5 );
        if ( *(uint32_t *)(this + 16) != 5 )
        {
          v11 = *(uint32_t *)(this + 172);
          if ( *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v11 + 12) )
          {
            sub_432EA0("CLICK_BUTTON1", -1, 0, 0);
            if ( *(int *)(this + 20) > 0 )
            {
              sub_69CEB0(*(uint32_t *)(this + 112));
              *(uint8_t *)(*(uint32_t *)(this + 116) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 120) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 124) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 132) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 136) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 140) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 144) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 148) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 152) + 16) = 0;
              --*(uint32_t *)(this + 20);
            }
          }
          v12 = *(uint32_t *)(this + 176);
          if ( *(uint8_t *)(v12 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v12 + 12) )
          {
            sub_432EA0("CLICK_BUTTON1", -1, 0, 0);
            if ( *(uint32_t *)(this + 20) < *(uint32_t *)(this + 24) - 1 )
            {
              sub_69CEB0(*(uint32_t *)(this + 112));
              *(uint8_t *)(*(uint32_t *)(this + 116) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 120) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 124) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 132) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 136) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 140) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 144) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 148) + 16) = 0;
              *(uint8_t *)(*(uint32_t *)(this + 152) + 16) = 0;
              ++*(uint32_t *)(this + 20);
            }
          }
          v13 = *(uint32_t *)(this + 168);
          v14 = 10 * *(uint32_t *)(this + 20);
          v31 = v14;
          if ( *(uint8_t *)(v13 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v13 + 12) )
          {
            sub_432EA0("BUTTON_02", -1, 0, 0);
            if ( *(uint8_t *)(*(uint32_t *)(this + 156) + 132) == 1 )
            {
              sub_470640((uint32_t *)this, *(uint32_t *)(this + 12), 2, 0);
            }
            else if ( *(uint8_t *)(*(uint32_t *)(this + 160) + 132) == 1 )
            {
              sub_470640((uint32_t *)this, *(uint32_t *)(this + 12), 3, 0);
            }
            else
            {
              v15 = 0;
              v16 = this + 116;
              while ( *(uint8_t *)(*(uint32_t *)v16 + 16) != 1 || *(uint8_t *)(*(uint32_t *)v16 + 132) != 1 )
              {
                ++v15;
                v16 += 4;
                if ( v15 >= 10 )
                  goto LABEL_52;
              }
              sub_470640((uint32_t *)this, *(uint32_t *)(this + 12), *(uint32_t *)(this + 16), v15 + v14);
            }
          }
LABEL_52:
          v17 = 100;
          v32 = this + 156;
          do
          {
            if ( *(uint8_t *)(*(uint32_t *)v32 + 17) != 0 && dword_79BE34 == *(uint32_t *)(*(uint32_t *)v32 + 12) )
            {
              sub_432EA0("BUTTON_04", -1, 0, 0);
              v18 = *(uint32_t *)(this + 1728);
              if ( v18 == -1 || v18 != v17 )
              {
                *(uint32_t *)(this + 1728) = v17;
                *(uint32_t *)(this + 1736) = timeGetTime();
                Time = -1;
                *(uint32_t *)(this + 1732) = -1;
              }
              else
              {
                *(uint32_t *)(this + 1732) = v17;
                Time = timeGetTime();
              }
              *(uint32_t *)(this + 1740) = Time;
            }
            if ( *(uint8_t *)(*(uint32_t *)v32 + 132) == 1 )
            {
              v20 = *(uint32_t *)(this + 1728);
              v21 = false;
              if ( v20 != -1 )
              {
                v22 = *(uint32_t *)(this + 1732);
                if ( v22 != -1 )
                {
                  if ( v20 == v17 && v22 == v17 )
                    v21 = (unsigned int)(*(uint32_t *)(this + 1740) - *(uint32_t *)(this + 1736)) < *(uint32_t *)(this + 1744);
                  *(uint32_t *)(this + 1728) = -1;
                  *(uint32_t *)(this + 1732) = -1;
                  *(uint32_t *)(this + 1736) = -1;
                  *(uint32_t *)(this + 1740) = -1;
                  if ( v21 )
                    sub_470640((uint32_t *)this, *(uint32_t *)(this + 12), (v17 != 100) + 2, 0);
                }
              }
            }
            ++v17;
            v32 += 4;
          }
          while ( v17 - 100 < 2 );
          v23 = v31;
          v33 = 0;
          for ( i = (int *)(this + 116); ; ++i )
          {
            v25 = *i;
            if ( *(uint8_t *)(*i + 16) != 0 )
            {
              if ( *(uint8_t *)(v25 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v25 + 12) )
              {
                sub_432EA0("BUTTON_04", -1, 0, 0);
                v26 = *(uint32_t *)(this + 1728);
                if ( v26 == -1 || v26 != v23 )
                {
                  *(uint32_t *)(this + 1728) = v23;
                  *(uint32_t *)(this + 1736) = timeGetTime();
                  v27 = -1;
                  *(uint32_t *)(this + 1732) = -1;
                }
                else
                {
                  *(uint32_t *)(this + 1732) = v23;
                  v27 = timeGetTime();
                }
                *(uint32_t *)(this + 1740) = v27;
              }
              if ( *(uint8_t *)(*i + 132) == 1 )
              {
                v28 = *(uint32_t *)(this + 1728);
                v29 = false;
                if ( v28 != -1 )
                {
                  v30 = *(uint32_t *)(this + 1732);
                  if ( v30 != -1 )
                  {
                    if ( v28 == v23 && v30 == v23 )
                      v29 = (unsigned int)(*(uint32_t *)(this + 1740) - *(uint32_t *)(this + 1736)) < *(uint32_t *)(this + 1744);
                    *(uint32_t *)(this + 1728) = -1;
                    *(uint32_t *)(this + 1732) = -1;
                    *(uint32_t *)(this + 1736) = -1;
                    *(uint32_t *)(this + 1740) = -1;
                    if ( v29 )
                      break;
                  }
                }
              }
            }
            ++v23;
            if ( ++v33 >= 10 )
              return;
          }
          sub_470640((uint32_t *)this, *(uint32_t *)(this + 12), *(uint32_t *)(this + 16), v33 + v31);
        }
      }
    }
  }
}


// ============================================================
// 【分区 3】频道列表获取（0x471850-0x471DB0）
// retrieveServerInfo（协议阶段① 数据落表）+ checkHTTPChannelDataWork（线程轮询）。
// ============================================================
// ------------------------------------------------------------
// 0x471850 ?_Putmfld@?$money_put@DV?$ostreambuf_iterator@DU?$char_traits@D@std@@@std@@@std@@ABE?AV?$ostreambuf_iterator@DU?$char_traits@D@std@@@2@V32@_NAAVios_base@2@D1V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z
// ------------------------------------------------------------
// CNEntranceChannel::retrieveServerInfo —— 协议阶段① 频道列表落表。
// ★ IDA 误名 money_put::_Putmfld（相邻 CRT 符号）；真名由日志串自证
//   "CNEntranceChannel::retrieveServerInfo - refresh channel information start"。
// 流程：清空 6×5 频道表 → 分词器(sub_577850/577310，分隔符 ";" "|" "#" ",") →
//   首字段 user_age（+72）/ server_count → 按服务器名匹配 off_790590[0..5] →
//   每频道 5 字段：名字(→sub_46E260 抽数字 id)/类型槽 sub_568A70/负载 cur/max
//   （max×100/cur>95 → 满员旗标 +22）/地址串/端口 → sub_470B20 入表并打日志
//   "'%s' '%s' '%d' %s:%d %d/%d"；异常名 "abnormal server name"；
//   收尾 sub_4F8FE0("Etc/pvpChannelList.etc") 加载 PVP 频道表
int /*thiscall*/ std::money_put<char,std::ostreambuf_iterator<char>>::_Putmfld(uint32_t *this, const char *ArgList)
{
  uint32_t *v3; // edi
  void **v4; // esi
  int j; // ebx
  uint32_t *v6; // ebx
  const char *v7; // eax
  const char *v8; // eax
  int v9; // esi
  const char *v10; // esi
  const char *v11; // edi
  const char *v12; // eax
  int v13; // eax
  const char *v14; // eax
  const char *v15; // eax
  const char *v16; // eax
  int v17; // esi
  int v18; // eax
  bool v19; // cc
  int v21; // [esp+Ch] [ebp-1BCh]
  int v23; // [esp+10h] [ebp-1B8h]
  int i; // [esp+14h] [ebp-1B4h]
  const char *v25; // [esp+14h] [ebp-1B4h]
  char v26[4]; // [esp+14h] [ebp-1B4h]
  uint8_t v27[312]; // [esp+18h] [ebp-1B0h] BYREF
  uint32_t v28[27]; // [esp+150h] [ebp-78h] BYREF
  int v29; // [esp+1C4h] [ebp-4h]

  v28[26] = dword_796E50;
  sub_577780(v27);
  v29 = 0;
  off_77F3FC("CNEntranceChannel::retrieveServerInfo - refresh channel information start");
  off_77F3FC("%s", ArgList);
  v3 = this + 168;
  for ( i = 6; i != 0; --i )
  {
    *((uint8_t *)v3 - 56) = 0;
    *(v3 - 1) = 0;
    *v3 = 0;
    v4 = (void **)(v3 + 2);
    for ( j = 5; j != 0; --j )
    {
      if ( *v4 != nullptr )
        j__free(*v4);
      *v4 = nullptr;
      v4[1] = nullptr;
      v4[2] = nullptr;
      v4 += 4;
    }
    v3 += 35;
  }
  if ( ArgList != nullptr )
  {
    sub_577850((void *)";");
    sub_577310("|");
    sub_577850("#");
    sub_577850(",");
    sub_5772E0(ArgList);
    v6 = this;
    if ( (int)*(this + 72) >= 0 )
    {
      sub_577330(v27);
    }
    else
    {
      v7 = (const char *)sub_577330(v27);
      *(this + 72) = j__atol(v7);
    }
    v8 = (const char *)sub_577330(v27);
    v9 = j__atol(v8);
    off_77F3FC("\t** server_count = %d  user_age = %d", v9, *(this + 72));
    if ( v9 != 0 )
    {
      v23 = 0;
      while ( 1 )
      {
        v10 = (const char *)sub_577330(v27);
        v25 = v10;
        if ( v10 != nullptr )
        {
          v11 = nullptr;
          while ( 1 )
          {
            off_77F3FC("server_type_name %d : %s", v11, off_790590[(uint32_t)v11]);
            if ( strcmp(off_790590[(uint32_t)v11], v10) == 0 )
              break;
            if ( (int)++v11 >= 6 )
              goto LABEL_22;
            v10 = v25;
          }
          ArgList = v11;
          strcpy((char *)&v6[35 * (uint32_t)v11 + 154], off_790590[(uint32_t)v11]);
LABEL_22:
          if ( v11 == (const char *)6 )
          {
            off_77F3FC("CNEntranceChannel::retrieveServerInfo - the given string has abnormal server name %s", v25);
            goto LABEL_34;
          }
          v12 = (const char *)sub_577330(v27);
          v13 = j__atol(v12);
          if ( v13 > 0 )
          {
            *(uint32_t *)v26 = v13;
            do
            {
              memset(v28, 0, 0x68u);
              strcpy((char *)&v28[1], (const char *)sub_577330(v27));
              v28[0] = sub_46E260(&v28[1]);
              LOBYTE(v21) = (uint8_t)ArgList + 1;
              v28[23] = sub_568A70(v21, v28[0]);
              if ( v28[23] == 0 )
                off_77F3FC(
                  "CNEntranceChannel::retrieveServerInfo - channel %s is unknown.type : %d",
                  (const char *)&v28[1],
                  ArgList);
              v14 = (const char *)sub_577330(v27);
              v28[14] = j__atol(v14);
              v15 = (const char *)sub_577330(v27);
              v28[15] = j__atol(v15);
              LOBYTE(v28[22]) = (double)v28[15] * 100.0 / (double)v28[14] > 95.0;
              strcpy((char *)&v28[16], (const char *)sub_577330(v27));
              v16 = (const char *)sub_577330(v27);
              v28[21] = j__atol(v16);
              if ( v28[23] != 0 )
              {
                v17 = 35 * (uint32_t)ArgList;
                sub_470B20(v28);
                v18 = v28[15];
                v19 = v6[35 * (uint32_t)ArgList + 168] < v28[15];
                ++v6[35 * (uint32_t)ArgList + 167];
                if ( v19 )
                  v6[v17 + 168] = v18;
                off_77F3FC(
                  "\t** '%s' '%s' '%d' %s:%d %d/%d",
                  (const char *)&v6[v17 + 154],
                  (const char *)&v28[1],
                  *(uint32_t *)(v28[23] + 28),
                  (const char *)&v28[16],
                  v28[21],
                  v18,
                  v28[14]);
              }
              --*(uint32_t *)v26;
            }
            while ( *(uint32_t *)v26 != 0 );
          }
        }
        if ( ++v23 >= 6 )
        {
          off_77F3FC("CNEntranceChannel::retrieveServerInfo - refresh channel information complete");
          sub_4F8FE0((char)"Etc/pvpChannelList.etc", (int)(v6 + 154), 6);
          goto LABEL_34;
        }
      }
    }
    off_77F3FC("CNEntranceChannel::retrieveServerInfo - all servers are down.");
  }
  else
  {
    off_77F3FC("CNEntranceChannel::retrieveServerInfo - the given string is NULL.");
  }
LABEL_34:
  v29 = -1;
  return sub_5777F0(v27);
}


// ------------------------------------------------------------
// 0x471CC0 sub_471CC0
// ------------------------------------------------------------
// CNEntranceChannel::checkHTTPChannelDataWork（日志串自证）—— 阶段① 线程轮询：
// byte_98BB64 线程在跑 → GetExitCodeThread：259=STILL_ACTIVE（超 5000ms 强收）、
// 1=成功 → retrieveServerInfo(dword_98BA5C 数据) 并 sub_46E810 刷新界面、
// -2=失败（"the http thread failed"）→ 重启线程 sub_46EE10
char /*thiscall*/ sub_471CC0(int this)
{
  int v1; // eax
  int *v3; // edi
  int v4; // edi

  LOBYTE(v1) = byte_98BB64;
  if ( byte_98BB64 != 0 )
  {
    v3 = (int *)(this + 1464);
    *(uint32_t *)(this + 1464) = -1;
    LOBYTE(v1) = GetExitCodeThread(hObject, (LPDWORD)(this + 1464));
    v4 = *v3;
    switch ( v4 )
    {
      case 259:
        v1 = sub_699000(this + 376);
        if ( v1 < 5000 )
          return v1;
        off_77F3FC("CNEntranceChannel::checkHTTPChannelDataWork - waiting for thread termination for five seconds.");
        *(uint8_t *)(this + 389) = 0;
        *(uint8_t *)(this + 390) = 0;
        sub_698F90(this + 376, 0, 0);
        CloseHandle(hObject);
        break;
      case 1:
        std::money_put<char,std::ostreambuf_iterator<char>>::_Putmfld((uint32_t *)this, (const char *)dword_98BA5C);
        byte_98BB64 = 0;
        CloseHandle(hObject);
        hObject = nullptr;
        LOBYTE(v1) = sub_46E810((uint32_t *)this);
        return v1;
      case -2:
        off_77F3FC("CNEntranceChannel::checkHTTPChannelDataWork - the http thread failed.");
        CloseHandle(hObject);
        break;
      default:
        return v1;
    }
    hObject = nullptr;
    LOBYTE(v1) = (uint8_t)sub_46EE10((int)&hObject, (const char *)(this + 1468));
  }
  return v1;
}



// ============================================================
// 【分区 4】登录过场/数据装载（0x471DB0-0x475510）
// MonoLayer 渐隐过场（0x472AF0-0x472B80）、物品数据装载（"ITEM CREATE FAIL!"
// 自证 0x4730A0/0x4730F0）、红黑树/容器辅助（0x473440/0x473920 族）【推断】。
// ============================================================
// ------------------------------------------------------------
// 0x471DB0 sub_471DB0
// ------------------------------------------------------------
// 【推断】登录数据装载巨函数（~310 行，与物品/条目装载同族）
int /*thiscall*/ sub_471DB0(uint32_t *this, int a2)
{
  int v3; // ecx
  int result; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // edx
  uint8_t *v10; // ebx
  uint8_t v11; // al
  unsigned int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  int v17; // ecx
  int v18; // eax
  int v19; // edi
  int v20; // eax
  long double v21; // st7
  uint8_t v22; // al
  unsigned int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // edi
  int v27; // ebx
  int v28; // eax
  bool v29; // cc
  uint32_t *v30; // edi
  int v31; // eax
  int v32; // edi
  int v33; // ebx
  int v34; // eax
  bool v35; // zf
  uint32_t *v36; // edi
  int v37; // eax
  int v38; // edi
  int v39; // ebx
  int v40; // eax
  int v41; // [esp+14h] [ebp-58h]
  int v42; // [esp+18h] [ebp-54h]
  int v43; // [esp+1Ch] [ebp-50h]
  int v44; // [esp+20h] [ebp-4Ch]
  int v45; // [esp+20h] [ebp-4Ch]
  uint32_t *v46; // [esp+24h] [ebp-48h]
  int v47; // [esp+24h] [ebp-48h]
  int v48; // [esp+24h] [ebp-48h]
  char Buffer[64]; // [esp+28h] [ebp-44h] BYREF
  int v50; // [esp+68h] [ebp-4h]
  float v51; // [esp+74h] [ebp+8h]
  uint32_t *i; // [esp+74h] [ebp+8h]
  uint32_t *v53; // [esp+74h] [ebp+8h]
  uint32_t *v54; // [esp+74h] [ebp+8h]
  uint32_t *v55; // [esp+74h] [ebp+8h]

  v3 = *(this + 11);
  v50 = dword_796E50;
  result = a2;
  if ( a2 == v3 )
  {
    sub_471CC0(this - 2);
    v5 = sub_418DD0(0);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v5 + 152))(v5, 0, 0, dword_79C0B0);
    v6 = sub_418DD0(10);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, 241, 6, dword_79C0B0);
    v51 = (double)sub_699000((int)(this + 85)) * 0.000033333334;
    sub_491530(1, 0);
    v7 = sub_418DD0(1);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, float, int, int, int))(*(uint32_t *)v7 + 128))(
        v7,
        149,
        10,
        dword_79C0B0,
        1065353216,
        1065353216,
        COERCE_FLOAT(LODWORD(v51)),
        -1,
        1126891520,
        1126891520);
    sub_491630(1);
    v8 = sub_418DD0(12);
    if ( v8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(v8, 267, 416, dword_79C0B0);
    if ( (int)*(this + 1) < 6 && *(this + 364) == 1 )
    {
      v9 = -424 - (uint32_t)this;
      v10 = (uint8_t *)(this + 106);
      for ( i = &unk_6C7BCC; ; i += 6 )
      {
        v11 = *v10;
        if ( &v10[v9] == (uint8_t *)*(this + 1) )
        {
          if ( v11 != 0xFF )
          {
            v12 = v11 + 10;
            if ( v12 >= 0xFF )
              LOBYTE(v12) = -1;
            goto LABEL_19;
          }
        }
        else if ( v11 != 0 )
        {
          LOBYTE(v12) = (v11 - 10) & ((v11 <= 0xAu) - 1);
LABEL_19:
          *v10 = v12;
        }
        if ( *v10 != 0 )
        {
          v13 = (*v10 << 24) | 0xFFFFFF;
          v14 = sub_418DD0(*i);
          if ( v14 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
              v14,
              0,
              0,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              v13,
              1333788672,
              1333788672);
          v9 = -424 - (uint32_t)this;
        }
        ++v10;
        if ( (int)&v10[v9] >= 6 )
        {
          v15 = sub_418DD0(0);
          if ( v15 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v15 + 152))(v15, 0, 0, dword_79C0B0);
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 57);
          sprintf(Buffer, "%d / %d", *(this + 3) + 1, *(this + 4));
          (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            368,
            382,
            -1,
            "%s",
            Buffer);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
          v53 = this + 14;
          v16 = 0;
          v17 = (int)(this + 108);
          v42 = 0;
          v46 = &unk_6C7BBC;
          v43 = (int)(this + 108);
          do
          {
            v18 = *v53;
            if ( *v53 != 0 && *(uint8_t *)(v18 + 17) != 0 && *(uint8_t *)(v18 + 16) != 0 )
            {
              v19 = sub_699000(v17);
              v20 = *v53;
              if ( *(uint8_t *)(*v53 + 17) != 0 && dword_79BE3C == *(uint32_t *)(v20 + 12) || *(uint8_t *)(v20 + 132) == 1 )
              {
                if ( v19 == 0 )
                  sub_698F90(v43, 0, 0);
                v23 = *((uint8_t *)this + v16 + 600) + 10;
                if ( v23 >= 0xD7 )
                  LOBYTE(v23) = -41;
                *((uint8_t *)this + v16 + 600) = v23;
                v21 = sin((double)(unsigned int)v19 * 0.006283185307179587) * 35.0 + (double)(uint8_t)v23;
              }
              else
              {
                if ( v19 != 0 )
                {
                  *(uint8_t *)(v43 + 13) = 0;
                  *(uint8_t *)(v43 + 14) = 0;
                  *((uint8_t *)this + v16 + 600) = -76;
                  v44 = *((uint8_t *)this + v16 + 600);
                }
                else
                {
                  v22 = (*((uint8_t *)this + v16 + 600) - 10) & ((*((uint8_t *)this + v16 + 600) <= 0xAu) - 1);
                  v44 = v22;
                  *((uint8_t *)this + v16 + 600) = v22;
                }
                v21 = (double)v44;
              }
              sub_491530(2, 0);
              if ( v21 > 0.0 )
              {
                v45 = *(uint32_t *)(*v53 + 24);
                v41 = *(uint32_t *)(*v53 + 20);
                v24 = sub_418DD0(41);
                if ( v24 != 0 )
                {
                  (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v24 + 128))(
                    v24,
                    v41 - 12,
                    v45 - 40,
                    dword_79C0B0,
                    1065353216,
                    1065353216,
                    0,
                    ((uint8_t)(uint64_t)v21 << 24) | 0xFFFFFF,
                    1333788672,
                    1333788672);
                  v16 = v42;
                }
              }
              v25 = *v53;
              if ( *(uint8_t *)(*v53 + 132) == 1 )
              {
                v26 = *(uint32_t *)(v25 + 24);
                v27 = *(uint32_t *)(v25 + 20);
                v28 = sub_418DD0(*v46);
                if ( v28 != 0 )
                  (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v28 + 128))(
                    v28,
                    v27,
                    v26,
                    dword_79C0B0,
                    1065353216,
                    1065353216,
                    0,
                    -1,
                    1333788672,
                    1333788672);
                v16 = v42;
              }
              sub_491630(2);
            }
            ++v53;
            result = (int)(v46 + 6);
            ++v16;
            v17 = v43 + 28;
            v29 = (int)(v46 + 6) < (int)"er";
            v42 = v16;
            v43 += 28;
            v46 += 6;
          }
          while ( v29 );
          return result;
        }
      }
    }
    result = sub_418DD0(0);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)result + 152))(result, 0, 0, dword_79C0B0);
  }
  else if ( a2 == *(this + 12) )
  {
    v30 = this + 27;
    v54 = this + 27;
    v47 = 10;
    do
    {
      if ( *(uint8_t *)(*v30 + 17) != 0 && dword_79BE3C == *(uint32_t *)(*v30 + 12) )
      {
        sub_491530(2, 0);
        v31 = *v30;
        v32 = *(uint32_t *)(*v30 + 24);
        v33 = *(uint32_t *)(v31 + 20);
        v34 = sub_418DD0(58);
        if ( v34 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v34 + 152))(v34, v33, v32, dword_79C0B0);
        sub_491630(2);
        v30 = v54;
      }
      ++v30;
      v35 = v47 == 1;
      v54 = v30;
      --v47;
    }
    while ( !v35 );
    v36 = this + 37;
    v55 = this + 37;
    v48 = 2;
    do
    {
      if ( *(uint8_t *)(*v36 + 17) != 0 && dword_79BE3C == *(uint32_t *)(*v36 + 12) )
      {
        sub_491530(2, 0);
        v37 = *v36;
        v38 = *(uint32_t *)(*v36 + 24);
        v39 = *(uint32_t *)(v37 + 20);
        v40 = sub_418DD0(58);
        if ( v40 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v40 + 128))(
            v40,
            v39,
            v38,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
        sub_491630(2);
        v36 = v55;
      }
      ++v36;
      v35 = v48 == 1;
      v55 = v36;
      --v48;
    }
    while ( !v35 );
    return sub_46F500(this - 2);
  }
  return result;
}


// ------------------------------------------------------------
// 0x4723A0 sub_4723A0
// ------------------------------------------------------------
int */*thiscall*/ sub_4723A0(int **this, int *a2, int a3, int a4)
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
    sub_470E80(*(void ***)(v7 + 4));
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
        if ( *(uint8_t *)(v5 + 85) == 0 )
        {
          v11 = *(uint32_t *)(v5 + 8);
          if ( *(uint8_t *)(v11 + 85) != 0 )
          {
            for ( i = *(uint32_t *)(v5 + 4); *(uint8_t *)(i + 85) == 0; i = *(uint32_t *)(i + 4) )
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
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 85) == 0; j = *(uint32_t *)j )
              v5 = j;
          }
        }
        sub_470BB0(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x472460 sub_472460
// ------------------------------------------------------------
int ***/*thiscall*/ sub_472460(int ****this, int ***a2, int **a3, int **a4)
{
  int **v4; // ebx
  int v6; // eax
  int **v7; // ecx
  uint32_t *v8; // eax
  int **v10; // edi

  v4 = a4;
  v6 = (int)*(this + 1);
  v7 = a3;
  if ( a3 == *(int ***)v6 && a4 == (int **)v6 )
  {
    sub_471230(*(void ***)(v6 + 4));
    (*(this + 1))[1] = (int **)*(this + 1);
    v8 = *(this + 1);
    *(this + 2) = nullptr;
    *v8 = v8;
    (*(this + 1))[2] = (int **)*(this + 1);
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
        sub_46E7B0((int *)&a3);
        sub_470ED0(this, &a4, v10);
        v7 = a3;
      }
      while ( a3 != v4 );
    }
    *a2 = v7;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x4724E0 sub_4724E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4724E0(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_4723A0((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x472520 sub_472520
// ------------------------------------------------------------
int /*thiscall*/ sub_472520(int this)
{
  int **v3; // [esp+4h] [ebp-4h] BYREF

  sub_472460((int ****)this, &v3, **(int ****)(this + 4), *(int ***)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x472560 sub_472560
// ------------------------------------------------------------
int /*thiscall*/ sub_472560(int ****this)
{
  int ****v1; // esi
  int **v3; // [esp+4h] [ebp-4h] BYREF

  v1 = this + 1;
  sub_472460(this + 1, &v3, **(this + 2), (int **)*(this + 2));
  j__free(v1[1]);
  v1[1] = nullptr;
  v1[2] = nullptr;
  return 0;
}



// ------------------------------------------------------------
// 0x4725A0 sub_4725A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4725A0(int ****this)
{
  int ****v1; // esi
  int **v3; // [esp+4h] [ebp-4h] BYREF

  v1 = this + 4;
  sub_472460(this + 4, &v3, **(this + 5), (int **)*(this + 5));
  j__free(v1[1]);
  v1[1] = nullptr;
  v1[2] = nullptr;
  return 0;
}



// ------------------------------------------------------------
// 0x4725E0 sub_4725E0
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4725E0(uint32_t *this, int ***a2, int **a3)
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
  void **v17; // esi
  int v18; // eax
  void *v20; // [esp-8h] [ebp-70h]
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v22[20]; // [esp+34h] [ebp-34h] BYREF
  int v23; // [esp+48h] [ebp-20h]
  int v24; // [esp+4Ch] [ebp-1Ch]
  int v25; // [esp+50h] [ebp-18h] BYREF
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *v27; // [esp+58h] [ebp-10h]
  int v28; // [esp+64h] [ebp-4h]

  v27 = this;
  if ( *((uint8_t *)a3 + 29) != 0 )
  {
    v24 = 15;
    v23 = 0;
    v22[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);
    v28 = 0;
    sub_401740(pExceptionObject, (int)v22);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_46E650(&a3);
  if ( *((uint8_t *)*v3 + 29) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 29) == 0 )
      v4[1] = (int)v6;
    v7 = v27;
    v8 = v27[1];
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
      if ( *((uint8_t *)v4 + 29) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_46E570(v4);
        v7 = v27;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v25 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 29) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v25 + 8) = sub_46E550(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)v3[2] + 29) != 0 )
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
    if ( *((uint8_t *)v4 + 29) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)v3[2];
    v3[2][1] = (int)v5;
  }
  v12 = v27[1];
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
  v14 = *((uint8_t *)v5 + 28);
  *((uint8_t *)v5 + 28) = *((uint8_t *)v3 + 28);
  *((uint8_t *)v3 + 28) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 28) == 1 )
  {
    v15 = v27;
    if ( v4 != *(int **)(v27[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 28) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 28) == 0 )
          {
            *((uint8_t *)v16 + 28) = 1;
            *((uint8_t *)v6 + 28) = 0;
            sub_46E4F0(v6);
            v16 = (uint32_t *)v6[2];
            v15 = v27;
          }
          if ( *((uint8_t *)v16 + 29) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 28) != 1 || *(uint8_t *)(v16[2] + 28) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 28) == 1 )
            {
              *(uint8_t *)(*v16 + 28) = 1;
              *((uint8_t *)v16 + 28) = 0;
              sub_46E590(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 28) = *((uint8_t *)v6 + 28);
            *((uint8_t *)v6 + 28) = 1;
            *(uint8_t *)(v16[2] + 28) = 1;
            sub_46E4F0(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 28) == 0 )
          {
            *((uint8_t *)v16 + 28) = 1;
            *((uint8_t *)v6 + 28) = 0;
            sub_46E590(v6);
            v16 = (uint32_t *)*v6;
            v15 = v27;
          }
          if ( *((uint8_t *)v16 + 29) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 28) != 1 || *(uint8_t *)(*v16 + 28) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 28) == 1 )
            {
              *(uint8_t *)(v16[2] + 28) = 1;
              *((uint8_t *)v16 + 28) = 0;
              sub_46E4F0(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 28) = *((uint8_t *)v6 + 28);
            *((uint8_t *)v6 + 28) = 1;
            *(uint8_t *)(*v16 + 28) = 1;
            sub_46E590(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 28) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(v15[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 28) = 1;
  }
  v17 = (void **)((char *)Block + 16);
  sub_472460(&v25, **((uint32_t **)Block + 5), *((uint32_t *)Block + 5));
  j__free(v17[1]);
  v20 = Block;
  v17[1] = nullptr;
  v17[2] = nullptr;
  j__free(v20);
  v18 = v27[2];
  if ( v18 != 0 )
    v27[2] = v18 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x4728C0 sub_4728C0
// ------------------------------------------------------------
char /*stdcall*/ sub_4728C0(int ****Block)
{
  int ****v1; // edi
  char result; // al
  int ****i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 29);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_4728C0(i[2]);
    i = (int ****)*i;
    sub_4725A0(v1);
    j__free(v1);
    result = *((uint8_t *)i + 29);
  }
  return result;
}



// ------------------------------------------------------------
// 0x472910 sub_472910
// ------------------------------------------------------------
int */*thiscall*/ sub_472910(int **this, int *a2, int a3, int a4)
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
    sub_4728C0(*(int *****)(v7 + 4));
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
        if ( *(uint8_t *)(v5 + 29) == 0 )
        {
          v11 = *(uint32_t *)(v5 + 8);
          if ( *(uint8_t *)(v11 + 29) != 0 )
          {
            for ( i = *(uint32_t *)(v5 + 4); *(uint8_t *)(i + 29) == 0; i = *(uint32_t *)(i + 4) )
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
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 29) == 0; j = *(uint32_t *)j )
              v5 = j;
          }
        }
        sub_4725E0(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x4729D0 sub_4729D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4729D0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax

  v2 = sub_46EE90();
  *(this + 1) = v2;
  *((uint8_t *)v2 + 85) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  v3 = sub_46EED0();
  *(this + 4) = v3;
  *((uint8_t *)v3 + 29) = 1;
  *(uint32_t *)(*(this + 4) + 4) = *(this + 4);
  *(uint32_t *)*(this + 4) = *(this + 4);
  *(uint32_t *)(*(this + 4) + 8) = *(this + 4);
  *(this + 5) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x472A60 sub_472A60
// ------------------------------------------------------------
void /*thiscall*/ sub_472A60(int this)
{
  int *v2; // eax
  int v3; // edi
  int v4; // [esp-8h] [ebp-28h]
  int v5; // [esp-8h] [ebp-28h]
  int *v6; // [esp-4h] [ebp-24h]
  int v7[2]; // [esp+Ch] [ebp-14h] BYREF
  int v8; // [esp+1Ch] [ebp-4h]

  v7[1] = this;
  v2 = *(int **)(this + 16);
  v3 = this + 12;
  v4 = *v2;
  v8 = 0;
  sub_472910((int **)(this + 12), v7, v4, (int)v2);
  j__free(*(void **)(v3 + 4));
  *(uint32_t *)(v3 + 4) = 0;
  *(uint32_t *)(v3 + 8) = 0;
  v6 = *(int **)(this + 4);
  v5 = *v6;
  v8 = -1;
  sub_4723A0((int **)this, v7, v5, (int)v6);
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x472AF0 sub_472AF0
// ------------------------------------------------------------
// 登录过场层装载：dword_8F84B8 vt+60 载入 "Common/Etc/MonoLayer.img" → sub_418DD0 建层
int sub_472AF0()
{
  int result; // eax

  (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Common/Etc/MonoLayer.img");
  result = sub_418DD0(0);
  dword_99FB74 = result;
  *(uint32_t *)dword_99FB70 = 0;
  dword_99FB8C = 0;
  return result;
}



// ------------------------------------------------------------
// 0x472B30 sub_472B30
// ------------------------------------------------------------
// 过场渐隐控制：byte_99FB90 使能 + dword_99FB94 起始时刻
int /*thiscall*/ sub_472B30(int *this, char a2, int a3)
{
  int v3; // ecx
  int result; // eax

  if ( a2 != 0 )
  {
    v3 = *(this + 15);
    if ( v3 != 0 )
      sub_4926A0(v3);
    byte_99FB90 = a2;
    byte_99FBED = 0;
    byte_99FBEE = 0;
    dword_99FB94 = a3;
    return a3;
  }
  else
  {
    byte_99FB90 = 0;
    dword_99FB94 = a3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x472B80 sub_472B80
// ------------------------------------------------------------
// 过场渐隐绘制：3000ms 内 sub_4049C0 透明度插值，超时自关
char /*thiscall*/ sub_472B80(int *this)
{
  int v2; // edi
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // esi
  int v7; // [esp-10h] [ebp-10h]
  int v8; // [esp-10h] [ebp-10h]

  if ( byte_99FB90 == 0 )
    return 1;
  v2 = *(this + 15);
  if ( v2 == 0 )
    return 1;
  sub_698F90((int)&unk_99FBE0, 0, 0);
  if ( sub_699000((int)&unk_99FBE0) >= dword_99FB94 + 3000 )
  {
    byte_99FB90 = 0;
    return 1;
  }
  LOBYTE(v3) = -1;
  if ( sub_699000((int)&unk_99FBE0) >= dword_99FB94 )
  {
    v4 = sub_699000((int)&unk_99FBE0);
    v3 = (uint64_t)sub_4049C0(255.0, 0.0, v4 - dword_99FB94, 3000);
  }
  if ( dword_99FB74 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)dword_99FB74 + 128))(
      dword_99FB74,
      0,
      0,
      dword_79C0B0,
      1098907648,
      1094713344,
      0,
      ((uint8_t)v3 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  if ( sub_699000((int)&unk_99FBE0) >= dword_99FB94 + 300 )
  {
    if ( sub_699000((int)&unk_99FBE0) >= dword_99FB94 + 600 )
    {
      if ( sub_699000((int)&unk_99FBE0) < dword_99FB94 + 2700 )
      {
        v6 = 255;
LABEL_18:
        sub_4938F0(v2);
        sub_491F80(-1, -1, -1, v6, 1);
        sub_491D00(dword_79C0B0, 320, 240, 0.0);
        return 0;
      }
      v8 = -2700 - dword_99FB94 + sub_699000((int)&unk_99FBE0);
      v5 = sub_423A80(255, 0, v8, 300);
    }
    else
    {
      v7 = -300 - dword_99FB94 + sub_699000((int)&unk_99FBE0);
      v5 = sub_423A80(0, 255, v7, 300);
    }
    v6 = v5;
    if ( v5 != 0 )
      goto LABEL_18;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x472D40 sub_472D40
// ------------------------------------------------------------
int /*thiscall*/ sub_472D40(uint32_t *this, int a2)
{
  return *(this + a2 + 119);
}



// ------------------------------------------------------------
// 0x472D60 sub_472D60
// ------------------------------------------------------------
char */*cdecl*/ sub_472D60(char *a1, char *a2, char *a3)
{
  char *v3; // edx
  char *result; // eax
  const void *v5; // esi
  void *v6; // edi

  v3 = a1;
  result = a3;
  while ( v3 != a2 )
  {
    v5 = v3;
    v6 = result;
    v3 += 28;
    result += 28;
    qmemcpy(v6, v5, 0x1Cu);
  }
  return result;
}



// ------------------------------------------------------------
// 0x472D90 sub_472D90
// ------------------------------------------------------------
int /*cdecl*/ sub_472D90(int a1, int a2, int a3)
{
  return sub_4FBD40(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x472DB0 sub_472DB0
// ------------------------------------------------------------
char */*cdecl*/ sub_472DB0(char *a1, char *a2, char *a3)
{
  char *v3; // edx
  char *result; // eax

  v3 = a1;
  for ( result = a3; v3 != a2; result += 28 )
  {
    if ( result != nullptr )
      qmemcpy(result, v3, 0x1Cu);
    v3 += 28;
  }
  return result;
}



// ------------------------------------------------------------
// 0x472DF0 sub_472DF0
// ------------------------------------------------------------
char /*stdcall*/ sub_472DF0(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_472DF0(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x472E30 sub_472E30
// ------------------------------------------------------------
int **/*thiscall*/ sub_472E30(int **this, int **a2, uint32_t *a3)
{
  int *v3; // edx
  int *v4; // eax

  v3 = *(this + 1);
  v4 = (int *)v3[1];
  while ( *((uint8_t *)v4 + 21) == 0 )
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
// 0x472EA0 sub_472EA0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_472EA0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_44BD30(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x472EC0 sub_472EC0
// ------------------------------------------------------------
char */*stdcall*/ sub_472EC0(char *a1, char *a2, char *a3)
{
  return sub_472DB0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x472EE0 sub_472EE0
// ------------------------------------------------------------
int /*stdcall*/ sub_472EE0(int a1, int a2, int a3)
{
  return sub_4FBDE0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x472F00 sub_472F00
// ------------------------------------------------------------
void /*thiscall*/ sub_472F00(int this)
{
  if ( *(uint32_t *)(this + 24) != 0 )
    j__free(*(void **)(this + 24));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  if ( *(uint32_t *)(this + 8) != 0 )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
}



// ------------------------------------------------------------
// 0x472F40 sub_472F40
// ------------------------------------------------------------
void /*thiscall*/ sub_472F40(int this)
{
  if ( *(uint32_t *)(this + 52) >= 0x10u )
    j__free(*(void **)(this + 32));
  *(uint32_t *)(this + 52) = 15;
  *(uint32_t *)(this + 48) = 0;
  *(uint8_t *)(this + 32) = 0;
  if ( *(uint32_t *)(this + 24) >= 0x10u )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 15;
  *(uint8_t *)(this + 4) = 0;
}



// ------------------------------------------------------------
// 0x472F90 sub_472F90
// ------------------------------------------------------------
int /*cdecl*/ sub_472F90(int a1)
{
  int *v1; // ecx
  int *v3; // [esp+0h] [ebp-4h] BYREF

  v3 = v1;
  sub_472E30(&dword_99FBA4, &v3, &a1);
  if ( v3 == (int *)dword_99FBA8 )
    return 0;
  else
    return v3[4];
}



// ------------------------------------------------------------
// 0x472FC0 sub_472FC0
// ------------------------------------------------------------
void */*thiscall*/ sub_472FC0(void *Block, char a2)
{
  sub_472F00((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x472FF0 sub_472FF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_472FF0(uint32_t *this)
{
  uint32_t *v2; // eax
  unsigned int v3; // edx
  uint32_t *v4; // ebx
  unsigned int v5; // ecx
  uint32_t *v6; // edx
  uint32_t *v7; // ebx
  char v9[4]; // [esp+Ch] [ebp-14h] BYREF
  void *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = this + 1;
  *(this + 6) = 15;
  *(this + 5) = 0;
  v10 = this;
  *((uint8_t *)this + 4) = 0;
  *(this + 13) = 15;
  *(this + 12) = 0;
  v11 = 0;
  *((uint8_t *)this + 32) = 0;
  v3 = *(this + 6);
  LOBYTE(v11) = 1;
  if ( v3 < 0x10 )
    v4 = this + 1;
  else
    v4 = (uint32_t *)*v2;
  if ( v3 >= 0x10 )
    v2 = (uint32_t *)*v2;
  sub_406D00(v9, v2, (char *)v4 + *(this + 5));
  v5 = *(this + 13);
  v6 = this + 8;
  if ( v5 < 0x10 )
    v7 = this + 8;
  else
    v7 = (uint32_t *)*v6;
  if ( v5 >= 0x10 )
    v6 = (uint32_t *)*v6;
  sub_406D00(v9, v6, (char *)v7 + *(this + 12));
  return this;
}



// ------------------------------------------------------------
// 0x4730A0 sub_4730A0
// ------------------------------------------------------------
// 物品数据装载（"ITEM CREATE FAIL! ItemIndex %d" 自证）【推断】
char **/*thiscall*/ sub_4730A0(char **this, char **a2, char *a3)
{
  char *v3; // ebx
  char *v4; // eax
  char *v5; // edx
  const void *v6; // esi
  void *v7; // edi

  v3 = *(this + 2);
  v4 = a3 + 28;
  if ( a3 + 28 != v3 )
  {
    v5 = a3;
    do
    {
      v6 = v4;
      v7 = v5;
      v4 += 28;
      v5 += 28;
      qmemcpy(v7, v6, 0x1Cu);
    }
    while ( v4 != v3 );
  }
  *(this + 2) -= 28;
  *a2 = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x4730F0 sub_4730F0
// ------------------------------------------------------------
// 物品数据装载 II（同上自证串）【推断】
int **/*stdcall*/ sub_4730F0(int a1, uint32_t *a2, int a3, int *a4, unsigned int Seed)
{
  int **result; // eax
  int *v6; // ecx
  bool v7; // zf
  int *v8; // edi
  uint32_t *v9; // esi
  uint32_t *v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // ecx
  uint32_t *v15; // eax
  unsigned int v16; // esi
  int v17; // eax
  int v18; // eax
  int v19; // esi
  uint32_t *v20; // eax
  uint32_t *v21; // edx
  int v22; // eax
  int v23; // esi
  int v24; // ebx
  int v25; // edi
  unsigned int v26; // ebx
  int v27; // eax
  uint32_t *v28; // esi
  void *v29; // eax
  int v30; // eax
  int v31; // edi
  int v32; // esi
  int v33; // eax
  int v34; // [esp+0h] [ebp-1Ch] BYREF
  int v35; // [esp+4h] [ebp-18h]
  int v36; // [esp+8h] [ebp-14h]
  unsigned int v37; // [esp+Ch] [ebp-10h]
  char ArgList[4]; // [esp+10h] [ebp-Ch]
  int *i; // [esp+14h] [ebp-8h]
  uint32_t *v40; // [esp+18h] [ebp-4h]
  char Seed_3; // [esp+37h] [ebp+1Bh]

  srand(Seed);
  result = *(int ***)(a3 + 96);
  v6 = *result;
  v7 = *result == (int *)result;
  v35 = 0;
  for ( i = v6; !v7; ++v35 )
  {
    v8 = i;
    Seed_3 = 0;
    v9 = (uint32_t *)sub_53A220((void *)i[2], nullptr);
    v10 = __RTDynamicCast(v9, 0, &CNRDPassiveObject `RTTI Type Descriptor', &CNMapObject `RTTI Type Descriptor', 0);
    v40 = v10;
    if ( v10 != nullptr )
    {
      sub_45FE80(a1, (int)v8, 33, *a4, (int)v10, 0, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(*v10 + 112))(v10, v8[3], v8[4], v8[5]);
      ++*a4;
      v11 = 0;
      v37 = 0;
      while ( 1 )
      {
        v36 = v11;
        v12 = v8[7];
        if ( v12 == 0 || v37 >= (v8[8] - v12) / 24 )
          break;
        v13 = v8[7];
        v14 = *(uint32_t *)(v13 + v36);
        v15 = (uint32_t *)(v36 + v13);
        switch ( v14 )
        {
          case 0:
            v16 = 0;
            for ( *(uint32_t *)ArgList = 0; ; *(uint32_t *)ArgList += 28 )
            {
              v17 = a2[2];
              if ( v17 == 0 || v16 >= (a2[3] - v17) / 28 )
                break;
              v18 = a2[2] + *(uint32_t *)ArgList;
              if ( *(uint8_t *)(v18 + 20) == 1 && *(uint32_t *)(v18 + 24) == v35 )
              {
                v19 = 28 * v16;
                (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t))(*v40 + 728))(
                  v40,
                  *(uint32_t *)(v19 + a2[2] + 8),
                  *(uint32_t *)(v19 + a2[2] + 12),
                  *(uint32_t *)(v19 + a2[2] + 4));
                v20 = (uint32_t *)(v19 + a2[2]);
                if ( v40[78] < 0x10u )
                  v21 = v40 + 73;
                else
                  v21 = (uint32_t *)v40[73];
                *(uint32_t *)ArgList = v21;
                v22 = (*(int (/*cdecl*/ **)(uint32_t, uint32_t, uint32_t))(*v40 + 52))(v20[2], v20[3], v20[1]);
                off_77F3FC((char *)&byte_6C8660, *(uint32_t *)ArgList, v22);
                sub_4730A0(&v34, v19 + a2[2]);
                goto LABEL_30;
              }
              ++v16;
            }
            break;
          case 1:
            v23 = v15[1];
            v24 = v15[2];
            v25 = v15[3];
            v34 = v15[4];
            if ( Seed_3 == 0 && rand() % v34 < v25 )
            {
              Seed_3 = 1;
              (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*v40 + 724))(v40, v23, v24);
            }
            break;
          case 2:
            v26 = 0;
            v34 = v15[1];
            for ( *(uint32_t *)ArgList = 0; ; *(uint32_t *)ArgList += 20 )
            {
              v27 = a2[6];
              if ( v27 == 0 || v26 >= (a2[7] - v27) / 20 )
                break;
              v28 = (uint32_t *)(a2[6] + *(uint32_t *)ArgList);
              if ( *v28 == v34 )
              {
                v29 = (void *)v28[2];
                if ( v29 != (void *)0xFFFF )
                {
                  v30 = sub_522300(v29, v28[3], 0, 0, v28[4], 1);
                  v31 = v30;
                  if ( v30 != 0 )
                  {
                    v32 = v28[1];
                    v33 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v30 + 16))(v30);
                    off_77F3FC(asc_6C8608, i[2], v34, v32, *(uint32_t *)(v33 + 4));
                    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*v40 + 720))(v40, v32, v31);
                    *(uint32_t *)(a2[6] + 20 * v26) = -345;
                    goto LABEL_30;
                  }
                  off_77F3FC("ITEM CREATE FAIL! ItemIndex %d", v28[2]);
                }
              }
              ++v26;
            }
            break;
          case 3:
            v10[169] = v15[1];
            break;
          default:
            break;
        }
LABEL_30:
        v8 = i;
        v10 = v40;
        ++v37;
        v11 = v36 + 24;
      }
    }
    else if ( v9 != nullptr )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))*v9)(v9, 1);
    }
    result = (int **)*v8;
    v7 = *v8 == *(uint32_t *)(a3 + 96);
    i = (int *)*v8;
  }
  return result;
}


// ------------------------------------------------------------
// 0x473440 sub_473440
// ------------------------------------------------------------
// 红黑树/有序容器节点插入辅助（CRT 容器模板实体）
int */*thiscall*/ sub_473440(int **this, int *a2, char a3, int *a4, int a5)
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
// 0x4735F0 sub_4735F0
// ------------------------------------------------------------
void /*noreturn*/ sub_4735F0()
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
// 0x473660 sub_473660
// ------------------------------------------------------------
int ***/*thiscall*/ sub_473660(uint32_t *this, int ***a2, int **a3)
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
// 0x473920 sub_473920
// ------------------------------------------------------------
// 红黑树/有序容器查找-插入辅助（CRT 容器模板实体）
int /*thiscall*/ sub_473920(int **this, int a2, int *a3)
{
  int *v3; // ebx
  int *v5; // esi
  int v6; // eax
  bool v7; // cl
  int v8; // edx
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
      v10 = *sub_473440(this, (int *)&a3, 1, v5, (int)v3);
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
    v12 = *sub_473440(this, (int *)&a3, v13, v5, (int)v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x4739E0 sub_4739E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4739E0(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x9249249 )
    sub_4735F0(this);
  v4 = (char *)operator new(28 * a2);
  *(this + 3) = &v4[28 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x473A30 sub_473A30
// ------------------------------------------------------------
char /*thiscall*/ sub_473A30(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0xCCCCCCC )
    sub_4735F0(this);
  v4 = (char *)operator new(20 * a2);
  *(this + 3) = &v4[20 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x473A80 sub_473A80
// ------------------------------------------------------------
void /*thiscall*/ sub_473A80(int this, int a2, unsigned int a3, int a4)
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
      sub_42CB90(this);
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
// 0x473CD0 sub_473CD0
// ------------------------------------------------------------
int */*thiscall*/ sub_473CD0(int **this, int *a2, int a3, int a4)
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
    sub_472DF0(*(void ***)(v7 + 4));
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
        sub_473660(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x473D90 sub_473D90
// ------------------------------------------------------------
int */*thiscall*/ sub_473D90(int **this, int *a2, int a3, int a4)
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
    sub_41CA20(*(void **)(v7 + 4));
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
        sub_473660(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x473E50 sub_473E50
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_473E50(int this, int Src, unsigned int a3, int *a4)
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
      sub_4735F0(this);
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
// 0x474030 sub_474030
// ------------------------------------------------------------
char **/*thiscall*/ sub_474030(char **this, int a2)
{
  unsigned int v2; // eax
  char *v5; // [esp-14h] [ebp-34h]
  char *v6; // [esp-10h] [ebp-30h]
  char *v7; // [esp-Ch] [ebp-2Ch]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *v9; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(a2 + 4);
  v10 = &v8;
  v9 = this;
  if ( v2 != 0 )
    v2 = (int)(*(uint32_t *)(a2 + 8) - v2) / 28;
  if ( sub_4739E0(this, v2) != 0 )
  {
    v7 = *(this + 1);
    v6 = *(char **)(a2 + 8);
    v5 = *(char **)(a2 + 4);
    v11 = 0;
    *(this + 2) = sub_472DB0(v5, v6, v7);
  }
  return this;
}



// ------------------------------------------------------------
// 0x4740D0 sub_4740D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4740D0(uint32_t *this, int a2)
{
  unsigned int v2; // eax
  int v5; // [esp-14h] [ebp-34h]
  int v6; // [esp-10h] [ebp-30h]
  int v7; // [esp-Ch] [ebp-2Ch]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *v9; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(a2 + 4);
  v10 = &v8;
  v9 = this;
  if ( v2 != 0 )
    v2 = (int)(*(uint32_t *)(a2 + 8) - v2) / 20;
  if ( sub_473A30(this, v2) != 0 )
  {
    v7 = *(this + 1);
    v6 = *(uint32_t *)(a2 + 8);
    v5 = *(uint32_t *)(a2 + 4);
    v11 = 0;
    *(this + 2) = sub_4FBDE0(v5, v6, v7);
  }
  return this;
}



// ------------------------------------------------------------
// 0x474170 sub_474170
// ------------------------------------------------------------
int /*thiscall*/ sub_474170(int this, int a2)
{
  int v2; // edi
  int v4; // eax
  unsigned int v5; // ecx
  char *v7; // ebx
  unsigned int v8; // eax
  int v9; // eax
  unsigned int v10; // eax
  char *v11; // edi
  unsigned int v12; // eax

  v2 = a2;
  if ( this == a2 )
    return this;
  v4 = *(uint32_t *)(a2 + 4);
  if ( v4 == 0 || (v5 = (*(uint32_t *)(a2 + 8) - v4) / 28) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  v7 = *(char **)(this + 4);
  if ( v7 != nullptr )
  {
    v2 = a2;
    v8 = (*(uint32_t *)(this + 8) - (int)v7) / 28;
  }
  else
  {
    v8 = 0;
  }
  if ( v5 > v8 )
  {
    if ( v7 != nullptr )
    {
      v2 = a2;
      v10 = (*(uint32_t *)(this + 12) - (int)v7) / 28;
    }
    else
    {
      v10 = 0;
    }
    if ( v5 <= v10 )
    {
      v11 = (char *)(*(uint32_t *)(a2 + 4) + 28 * sub_52AEF0(this));
      sub_472D60(*(char **)(a2 + 4), v11, v7);
      *(uint32_t *)(this + 8) = sub_472DB0(v11, *(char **)(a2 + 8), *(char **)(this + 8));
      return this;
    }
    if ( v7 != nullptr )
      j__free(*(void **)(this + 4));
    v12 = sub_52AEF0(v2);
    if ( sub_4739E0((uint32_t *)this, v12) != 0 )
      *(uint32_t *)(this + 8) = sub_472EC0(*(char **)(v2 + 4), *(char **)(v2 + 8), *(char **)(this + 4));
    return this;
  }
  sub_472D60(*(char **)(v2 + 4), *(char **)(v2 + 8), *(char **)(this + 4));
  v9 = *(uint32_t *)(v2 + 4);
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 28 * ((*(uint32_t *)(v2 + 8) - v9) / 28);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x474300 sub_474300
// ------------------------------------------------------------
int /*thiscall*/ sub_474300(int this, int *a2)
{
  int v4; // eax
  unsigned int v5; // ecx
  int v7; // edi
  unsigned int v8; // eax
  int v9; // eax
  unsigned int v10; // eax
  unsigned int v11; // eax
  int v12; // [esp+10h] [ebp+8h]

  if ( (int *)this == a2 )
    return this;
  v4 = a2[1];
  if ( v4 == 0 || (v5 = (a2[2] - v4) / 20) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  v7 = *(uint32_t *)(this + 4);
  if ( v7 != 0 )
    v8 = (*(uint32_t *)(this + 8) - v7) / 20;
  else
    v8 = 0;
  if ( v5 > v8 )
  {
    if ( v7 != 0 )
      v10 = (*(uint32_t *)(this + 12) - v7) / 20;
    else
      v10 = 0;
    if ( v5 <= v10 )
    {
      v12 = a2[1] + 20 * sub_45E580((int *)this);
      sub_472D90(a2[1], v12, v7);
      *(uint32_t *)(this + 8) = sub_4FBDE0(v12, a2[2], *(uint32_t *)(this + 8));
      return this;
    }
    if ( v7 != 0 )
      j__free(*(void **)(this + 4));
    v11 = sub_45E580(a2);
    if ( sub_473A30((uint32_t *)this, v11) != 0 )
      *(uint32_t *)(this + 8) = sub_472EE0(a2[1], a2[2], *(uint32_t *)(this + 4));
    return this;
  }
  sub_4FBD40(a2[1], a2[2], v7);
  v9 = a2[1];
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 20 * ((a2[2] - v9) / 20);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x474480 sub_474480
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_474480(unsigned int *this, unsigned int a2, int a3)
{
  int v4; // edx
  unsigned int result; // eax
  int v6; // eax
  void *v7; // edx

  v4 = *(this + 1);
  if ( v4 != 0 )
    result = (int)(*(this + 2) - v4) >> 2;
  else
    result = 0;
  if ( result >= a2 )
  {
    if ( v4 != 0 )
    {
      result = *(this + 2);
      if ( a2 < (int)(result - v4) >> 2 )
      {
        v7 = (void *)(v4 + 4 * a2);
        if ( v7 != (void *)result )
        {
          result = (unsigned int)memcpy_0(v7, (const void *)result, 0);
          *(this + 2) = result;
        }
      }
    }
  }
  else
  {
    if ( v4 != 0 )
      v6 = (int)(*(this + 2) - v4) >> 2;
    else
      v6 = 0;
    return sub_473E50((int)this, *(this + 2), a2 - v6, &a3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x474510 sub_474510
// ------------------------------------------------------------
char **/*thiscall*/ sub_474510(char **this, char **a2)
{
  *this = *a2;
  sub_474030(this + 1, (int)(a2 + 1));
  sub_4740D0(this + 5, (int)(a2 + 5));
  return this;
}



// ------------------------------------------------------------
// 0x474570 sub_474570
// ------------------------------------------------------------
int /*cdecl*/ sub_474570(int a1, int a2, int a3)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 16 )
    result = sub_4ED3F0(i, a3);
  return result;
}



// ------------------------------------------------------------
// 0x4745A0 sub_4745A0
// ------------------------------------------------------------
int /*cdecl*/ sub_4745A0(int a1, int a2, int a3)
{
  int v3; // esi
  int v4; // edi

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v3 -= 16;
    v4 -= 16;
    sub_4ED3F0(v4, v3);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x4745E0 sub_4745E0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4745E0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
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
    sub_474170((int)(v4 + 1), (int)(v3 + 1));
    sub_474300((int)(v4 + 5), v3 + 5);
    v3 += 9;
    v4 += 9;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x474630 sub_474630
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_474630(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  uint32_t *v4; // edi
  int v5; // eax

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v5 = *(uint32_t *)(v3 - 36);
    v3 -= 36;
    v4 -= 9;
    *v4 = v5;
    sub_474170((int)(v4 + 1), v3 + 4);
    sub_474300((int)(v4 + 5), (int *)(v3 + 20));
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x474680 sub_474680
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_474680(char *a1, char *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
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
      sub_435020(v3, a1);
    v3 += 4;
    LOBYTE(v7) = 0;
    a1 += 16;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x474710 sub_474710
// ------------------------------------------------------------
void */*thiscall*/ sub_474710(void *this)
{
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 8) = 0;
  *(uint32_t *)this = 0;
  if ( *((uint32_t *)this + 2) != 0 )
    j__free(*((void **)this + 2));
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  if ( *((uint32_t *)this + 6) != 0 )
    j__free(*((void **)this + 6));
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 8) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x474790 sub_474790
// ------------------------------------------------------------
char */*thiscall*/ sub_474790(char *this, char *a2)
{
  int v4; // eax
  int v5; // ebx
  int v6; // ebx
  int v8; // [esp+Ch] [ebp-4h]
  int v9; // [esp+18h] [ebp+8h]
  int i; // [esp+18h] [ebp+8h]

  *(uint32_t *)this = *(uint32_t *)a2;
  v4 = a2 - this;
  v5 = (int)(this + 4);
  v8 = a2 - this;
  v9 = 4;
  while ( 1 )
  {
    sub_4ED3F0(v5, v5 + v4);
    v5 += 16;
    if ( --v9 == 0 )
      break;
    v4 = v8;
  }
  sub_4ED3F0((int)(this + 68), (int)(a2 + 68));
  *((uint32_t *)this + 21) = *((uint32_t *)a2 + 21);
  *((uint32_t *)this + 22) = *((uint32_t *)a2 + 22);
  *((uint32_t *)this + 23) = *((uint32_t *)a2 + 23);
  *((uint32_t *)this + 24) = *((uint32_t *)a2 + 24);
  *((uint32_t *)this + 25) = *((uint32_t *)a2 + 25);
  *((uint32_t *)this + 26) = *((uint32_t *)a2 + 26);
  *((uint32_t *)this + 27) = *((uint32_t *)a2 + 27);
  v6 = (int)(this + 112);
  for ( i = 4; i != 0; --i )
  {
    sub_4ED3F0(v6, v6 + v8);
    v6 += 16;
  }
  *((uint32_t *)this + 44) = *((uint32_t *)a2 + 44);
  *((uint32_t *)this + 45) = *((uint32_t *)a2 + 45);
  *((uint32_t *)this + 46) = *((uint32_t *)a2 + 46);
  *((uint32_t *)this + 47) = *((uint32_t *)a2 + 47);
  *((uint32_t *)this + 48) = *((uint32_t *)a2 + 48);
  *((uint32_t *)this + 49) = *((uint32_t *)a2 + 49);
  *((uint32_t *)this + 50) = *((uint32_t *)a2 + 50);
  *((uint32_t *)this + 51) = *((uint32_t *)a2 + 51);
  *((uint32_t *)this + 52) = *((uint32_t *)a2 + 52);
  *((uint32_t *)this + 53) = *((uint32_t *)a2 + 53);
  *((uint32_t *)this + 54) = *((uint32_t *)a2 + 54);
  *((uint32_t *)this + 55) = *((uint32_t *)a2 + 55);
  *((uint32_t *)this + 56) = *((uint32_t *)a2 + 56);
  *((uint32_t *)this + 57) = *((uint32_t *)a2 + 57);
  *((uint32_t *)this + 58) = *((uint32_t *)a2 + 58);
  *((uint32_t *)this + 59) = *((uint32_t *)a2 + 59);
  *((uint32_t *)this + 60) = *((uint32_t *)a2 + 60);
  *((uint32_t *)this + 61) = *((uint32_t *)a2 + 61);
  *((uint32_t *)this + 62) = *((uint32_t *)a2 + 62);
  *((uint32_t *)this + 63) = *((uint32_t *)a2 + 63);
  *((uint32_t *)this + 64) = *((uint32_t *)a2 + 64);
  *((uint32_t *)this + 65) = *((uint32_t *)a2 + 65);
  *((uint32_t *)this + 66) = *((uint32_t *)a2 + 66);
  return this;
}



// ------------------------------------------------------------
// 0x474950 sub_474950
// ------------------------------------------------------------
void /*thiscall*/ sub_474950(int this, int a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 3;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 12) - v3) >> 3 )
  {
    v5 = *(uint32_t *)(this + 8);
    sub_63A7C0(v5, 1, a2);
    *(uint32_t *)(this + 8) = v5 + 8;
  }
  else
  {
    sub_473A80(this, *(char **)(this + 8), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x4749C0 sub_4749C0
// ------------------------------------------------------------
int /*cdecl*/ sub_4749C0(int a1, int a2, int a3)
{
  return sub_4745A0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4749E0 sub_4749E0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4749E0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = a2;
  for ( i = a1; i != a2; i += 9 )
  {
    *i = *a3;
    sub_474170((int)(i + 1), (int)(a3 + 1));
    sub_474300((int)(i + 5), a3 + 5);
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x474A20 sub_474A20
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_474A20(int a1, int a2, uint32_t *a3)
{
  return sub_474630(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x474A40 sub_474A40
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_474A40(uint32_t *a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v6[4] = v6;
  v6[3] = a1;
  v7 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
      result = sub_435020(v3, a3);
    --a2;
    v3 += 4;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x474AD0 sub_474AD0
// ------------------------------------------------------------
int /*cdecl*/ sub_474AD0(uint32_t *a1, uint32_t *a2, int a3)
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
      *(uint32_t *)v3 = *a1;
      sub_474030((char **)(v3 + 4), (int)(a1 + 1));
      LOBYTE(v7) = 2;
      sub_4740D0((uint32_t *)(v3 + 20), (int)(a1 + 5));
    }
    v3 += 36;
    LOBYTE(v7) = 0;
    a1 += 9;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x474C30 sub_474C30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_474C30(uint32_t *this)
{
  uint32_t *v2; // eax

  v2 = sub_433AC0();
  *(this + 1) = v2;
  *((uint8_t *)v2 + 21) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x474C60 sub_474C60
// ------------------------------------------------------------
int /*thiscall*/ sub_474C60(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 36 )
      sub_472F00(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x474CA0 sub_474CA0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_474CA0(void *this, char *a2, char *a3, uint32_t *a4)
{
  return sub_474680(a2, a3, a4);
}



// ------------------------------------------------------------
// 0x474CC0 sub_474CC0
// ------------------------------------------------------------
void /*cdecl*/ sub_474CC0(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  uint32_t v4[6]; // [esp+0h] [ebp-24h] BYREF
  int v5; // [esp+20h] [ebp-4h]

  v3 = a1;
  v4[5] = v4;
  v4[4] = a1;
  v5 = 0;
  while ( a2 != 0 )
  {
    v4[3] = v3;
    LOBYTE(v5) = 1;
    if ( v3 != 0 )
    {
      *(uint32_t *)v3 = *a3;
      sub_474030((char **)(v3 + 4), (int)(a3 + 1));
      LOBYTE(v5) = 2;
      sub_4740D0((uint32_t *)(v3 + 20), (int)(a3 + 5));
    }
    v3 += 36;
    LOBYTE(v5) = 0;
    --a2;
  }
}



// ------------------------------------------------------------
// 0x474DB0 sub_474DB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_474DB0(void *this, uint32_t *a2, int a3, uint32_t *a4)
{
  sub_474A40(a2, a3, a4);
  return &a2[4 * a3];
}



// ------------------------------------------------------------
// 0x474DE0 sub_474DE0
// ------------------------------------------------------------
void /*thiscall*/ sub_474DE0(int this, char *a2, unsigned int a3, void *a4)
{
  int v5; // edx
  int v6; // ecx
  unsigned int v7; // eax
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // eax
  void *v13; // ebx
  int v14; // ecx
  int v15; // eax
  unsigned int v16; // edi
  char *v17; // eax
  int v18; // edi
  char *v19; // edi
  int v20; // eax
  void *v21; // [esp-18h] [ebp-4Ch]
  void *v22; // [esp-18h] [ebp-4Ch]
  void *v23; // [esp-Ch] [ebp-40h]
  int v24; // [esp-8h] [ebp-3Ch]
  int v25; // [esp+0h] [ebp-34h] BYREF
  char v26[4]; // [esp+Ch] [ebp-28h] BYREF
  void *v27; // [esp+10h] [ebp-24h]
  void *Block; // [esp+1Ch] [ebp-18h]
  int v29; // [esp+20h] [ebp-14h]
  int *v30; // [esp+24h] [ebp-10h]
  int v31; // [esp+30h] [ebp-4h]
  char *v32; // [esp+40h] [ebp+Ch]
  char *v33; // [esp+44h] [ebp+10h]

  v30 = &v25;
  v29 = this;
  sub_435020(a4);
  v5 = *(uint32_t *)(this + 4);
  v6 = 0;
  v31 = 0;
  if ( v5 != 0 )
    v7 = (*(uint32_t *)(this + 12) - v5) >> 4;
  else
    v7 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v6 = (*(uint32_t *)(this + 8) - v5) >> 4;
    if ( 0xFFFFFFF - v6 < a3 )
      sub_42CB90(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 4;
    else
      v9 = 0;
    if ( v7 >= a3 + v9 )
    {
      v17 = *(char **)(this + 8);
      Block = v17;
      if ( (v17 - a2) >> 4 >= a3 )
      {
        v19 = &v17[-16 * a3];
        v20 = sub_474680(v19, (int)v17, v17, this);
        v22 = Block;
        *(uint32_t *)(this + 8) = v20;
        sub_4749C0(a2, v19, v22);
        sub_474570(a2, &a2[16 * a3], v26);
      }
      else
      {
        sub_474680(a2, (int)v17, &a2[16 * a3], this);
        v24 = a3 - ((*(uint32_t *)(this + 8) - (int)a2) >> 4);
        v23 = *(void **)(this + 8);
        LOBYTE(v31) = 3;
        sub_474DB0(this, v23, v24, v26);
        v18 = 16 * a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v18;
        v31 = 0;
        sub_474570(a2, v18 - 16 * a3, v26);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (v7 >> 1) >= v7 )
        v10 = (v7 >> 1) + v7;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(uint32_t *)(this + 8) - v5) >> 4;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( v5 != 0 )
          v12 = (*(uint32_t *)(this + 8) - v5) >> 4;
        else
          v12 = 0;
        v10 = a3 + v12;
      }
      v33 = (char *)(16 * v10);
      v13 = operator new(16 * v10);
      v21 = *(void **)(this + 4);
      Block = v13;
      LOBYTE(v31) = 1;
      v32 = (char *)sub_474680(v21, (int)a2, v13, this);
      sub_474A40(v32, a3, v26, this);
      sub_474680(a2, *(uint32_t *)(this + 8), &v32[16 * a3], this);
      v14 = *(uint32_t *)(this + 4);
      if ( v14 != 0 )
        v15 = (*(uint32_t *)(this + 8) - v14) >> 4;
      else
        v15 = 0;
      v16 = v15 + a3;
      if ( v14 != 0 )
      {
        sub_42CC00(v14, *(uint32_t *)(this + 8));
        j__free(*(void **)(this + 4));
      }
      *(uint32_t *)(this + 12) = &v33[(uint32_t)v13];
      *(uint32_t *)(this + 8) = (char *)v13 + 16 * v16;
      *(uint32_t *)(this + 4) = v13;
    }
  }
  if ( v27 != nullptr )
    j__free(v27);
}


// ------------------------------------------------------------
// 0x475080 sub_475080
// ------------------------------------------------------------
void /*stdcall*/ sub_475080(int a1, int a2)
{
  int i; // esi

  for ( i = a1; i != a2; i += 36 )
    sub_472F00(i);
}



// ------------------------------------------------------------
// 0x4750B0 sub_4750B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4750B0(int this)
{
  if ( *(uint32_t *)(this + 44) != 0 )
    j__free(*(void **)(this + 44));
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  if ( *(uint32_t *)(this + 28) != 0 )
    j__free(*(void **)(this + 28));
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 0;
  return sub_474C60((int *)(this + 8));
}



// ------------------------------------------------------------
// 0x475100 sub_475100
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_475100(uint32_t **this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
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
    v6 = sub_4745E0(a4, *(this + 2), a3);
    v7 = (int)*(this + 2);
    v8 = v6;
    for ( i = (int)v6; i != v7; i += 36 )
      sub_472F00(i);
    v5 = a3;
    v11[2] = v8;
  }
  *a2 = v5;
  return a2;
}



// ------------------------------------------------------------
// 0x475160 sub_475160
// ------------------------------------------------------------
int /*stdcall*/ sub_475160(int a1, int a2, uint32_t *a3)
{
  sub_474CC0(a1, a2, a3);
  return a1 + 36 * a2;
}



// ------------------------------------------------------------
// 0x475190 sub_475190
// ------------------------------------------------------------
void /*thiscall*/ sub_475190(int this, uint32_t *a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  uint32_t *v5; // edi

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 4;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 12) - v3) >> 4 )
  {
    v5 = *(uint32_t **)(this + 8);
    sub_474A40(v5, 1, a2);
    *(uint32_t *)(this + 8) = v5 + 4;
  }
  else
  {
    sub_474DE0(this, *(char **)(this + 8), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x475200 sub_475200
// ------------------------------------------------------------
void /*thiscall*/ sub_475200(int *this, int a2, unsigned int a3, int a4)
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
  int v15; // eax
  int v16; // ecx
  int v18; // edi
  int v19; // [esp-18h] [ebp-60h]
  int v20; // [esp-Ch] [ebp-54h]
  unsigned int v21; // [esp-8h] [ebp-50h]
  int v22; // [esp+0h] [ebp-48h] BYREF
  uint8_t v23[8]; // [esp+Ch] [ebp-3Ch] BYREF
  void *v24; // [esp+14h] [ebp-34h]
  void *v25; // [esp+24h] [ebp-24h]
  int v26; // [esp+28h] [ebp-20h]
  int v27; // [esp+2Ch] [ebp-1Ch]
  void *Block; // [esp+30h] [ebp-18h]
  int *v29; // [esp+34h] [ebp-14h]
  int *v30; // [esp+38h] [ebp-10h]
  int v31; // [esp+44h] [ebp-4h]
  int v32; // [esp+50h] [ebp+8h]
  int v33; // [esp+54h] [ebp+Ch]
  int v34; // [esp+58h] [ebp+10h]
  int v35; // [esp+58h] [ebp+10h]

  v30 = &v22;
  v29 = this;
  sub_474510(a4);
  v5 = *(this + 1);
  v6 = 0;
  v31 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 36;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - v5) / 36;
    else
      v8 = 0;
    if ( 119304647 - v8 < a3 )
      sub_4735F0(this);
    if ( v5 != 0 )
      v9 = (*(this + 2) - v5) / 36;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = *(this + 2);
      v35 = v16;
      if ( (v16 - a2) / 36 >= a3 )
      {
        v32 = v16 - 36 * a3;
        *(this + 2) = sub_474AD0(v32, v16, v16);
        sub_474A20(a2, v32, v35);
        sub_4749E0(a2, a2 + 36 * a3, v23);
      }
      else
      {
        sub_474AD0(a2, v16, a2 + 36 * a3);
        v21 = a3 - (*(this + 2) - a2) / 36;
        v20 = *(this + 2);
        LOBYTE(v31) = 3;
        sub_475160(v20, v21, v23);
        v18 = 36 * a3 + *(this + 2);
        *(this + 2) = v18;
        v31 = 0;
        sub_4749E0(a2, v18 - 36 * a3, v23);
      }
    }
    else
    {
      if ( 119304647 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(this + 2) - v5) / 36;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_504390(this);
      v34 = 36 * v10;
      v12 = (char *)operator new(36 * v10);
      v19 = *(this + 1);
      Block = v12;
      LOBYTE(v31) = 1;
      v33 = sub_474AD0(v19, a2, v12);
      sub_474CC0(v33, a3, v23);
      sub_474AD0(a2, *(this + 2), v33 + 36 * a3);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 36;
      v14 = v13 + a3;
      v15 = *(this + 1);
      if ( v15 != 0 )
      {
        sub_475080(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v34];
      *(this + 2) = (int)&v12[36 * v14];
      *(this + 1) = (int)v12;
    }
  }
  if ( v25 != nullptr )
    j__free(v25);
  v25 = nullptr;
  v26 = 0;
  v27 = 0;
  if ( v24 != nullptr )
    j__free(v24);
}


// ============================================================
// 【分区 5】进副本一次性演出（0x475510-0x476300）
// 巨型 0x475810（docs/13 遗留#3：进副本震屏 85/100 + 物件生成，半还原范围）。
// ============================================================
// ------------------------------------------------------------
// 0x475510 sub_475510
// ------------------------------------------------------------
void /*thiscall*/ sub_475510(
        int this,
        unsigned int a2,
        char *a3,
        int a4,
        void *a5,
        int a6,
        int a7,
        int a8,
        void *Block,
        int a10,
        int a11)
{
  int v11; // esi
  unsigned int v12; // eax
  int v13; // eax

  v11 = *(uint32_t *)(this + 4);
  if ( v11 != 0 )
    v12 = (*(uint32_t *)(this + 8) - v11) / 36;
  else
    v12 = 0;
  if ( v12 >= a2 )
  {
    if ( v11 != 0 && a2 < (*(uint32_t *)(this + 8) - v11) / 36 )
      sub_475100((uint32_t **)this, &a2, (uint32_t *)(v11 + 36 * a2), *(uint32_t **)(this + 8));
  }
  else
  {
    if ( v11 != 0 )
      v13 = (*(uint32_t *)(this + 8) - v11) / 36;
    else
      v13 = 0;
    sub_475200((int *)this, *(char **)(this + 8), a2 - v13, &a3);
  }
  if ( Block != nullptr )
    j__free(Block);
  if ( a5 != nullptr )
    j__free(a5);
}



// ------------------------------------------------------------
// 0x4755F0 sub_4755F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4755F0(uint32_t *this, int Block)
{
  signed int v2; // edi
  int v3; // eax
  int v4; // esi
  signed int v5; // eax
  uint32_t *result; // eax
  int v7; // esi
  uint32_t *v8; // eax
  uint32_t v9[11]; // [esp-24h] [ebp-38h] BYREF
  int v10; // [esp+10h] [ebp-4h]

  dword_99FB78 = Block;
  v2 = *(uint32_t *)(8 * Block + *(this + 42)) * *(uint32_t *)(8 * Block + *(this + 42) + 4);
  v3 = dword_99FBB4;
  if ( dword_99FBB4 != 0 )
    v3 = (dword_99FBB8 - dword_99FBB4) / 36;
  if ( v3 < v2 )
  {
    sub_474710(v9);
    sub_475510(
      (int)&unk_99FBB0,
      v2,
      (char *)v9[0],
      v9[1],
      (void *)v9[2],
      v9[3],
      v9[4],
      v9[5],
      (void *)v9[6],
      v9[7],
      v9[8]);
  }
  if ( dword_99FBC4 != 0 )
    v4 = (dword_99FBC8 - dword_99FBC4) >> 2;
  else
    v4 = 0;
  if ( v4 < v2 )
  {
    sub_474480(&dword_99FBC0, v2, 0);
    v5 = v4;
    do
      *(uint32_t *)(dword_99FBC4 + 4 * v5++) = 0;
    while ( v5 < v2 );
  }
  result = (uint32_t *)dword_99FBD4;
  if ( dword_99FBD4 != 0 )
    v7 = (dword_99FBD8 - dword_99FBD4) >> 2;
  else
    v7 = 0;
  if ( v7 < v2 )
  {
    sub_474480(&dword_99FBD0, v2, 0);
    do
    {
      v8 = operator new(0xA0u);
      v10 = 0;
      if ( v8 != nullptr )
        result = sub_42D590(v8, 0);
      else
        result = nullptr;
      *(uint32_t *)(dword_99FBD4 + 4 * v7++) = result;
      v10 = -1;
    }
    while ( v7 < v2 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x475730 sub_475730
// ------------------------------------------------------------
int /*stdcall*/ sub_475730(int a1, int a2)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 56 )
    result = sub_4750B0(i);
  return result;
}



// ------------------------------------------------------------
// 0x475760 sub_475760
// ------------------------------------------------------------
int sub_475760()
{
  int result; // eax
  uint32_t *v1; // edi
  int v2; // esi
  int *i; // esi
  void *v4; // edi
  int *j; // esi

  result = dword_99FBB8;
  v1 = (uint32_t *)dword_99FBB4;
  if ( dword_99FBB4 != dword_99FBB8 )
  {
    v2 = dword_99FBB4 + 8;
    do
    {
      *v1 = 0;
      if ( *(uint32_t *)v2 != 0 )
        j__free(*(void **)v2);
      *(uint32_t *)v2 = 0;
      *(uint32_t *)(v2 + 4) = 0;
      *(uint32_t *)(v2 + 8) = 0;
      if ( *(uint32_t *)(v2 + 16) != 0 )
        j__free(*(void **)(v2 + 16));
      *(uint32_t *)(v2 + 16) = 0;
      *(uint32_t *)(v2 + 20) = 0;
      *(uint32_t *)(v2 + 24) = 0;
      result = dword_99FBB8;
      v1 += 9;
      v2 += 36;
    }
    while ( v1 != (uint32_t *)dword_99FBB8 );
  }
  for ( i = (int *)dword_99FBC4; i != (int *)dword_99FBC8; ++i )
  {
    v4 = (void *)*i;
    if ( *i != 0 )
    {
      sub_42EDE0(*i);
      j__free(v4);
    }
    *i = 0;
    result = dword_99FBC8;
  }
  for ( j = (int *)dword_99FBD4; j != (int *)dword_99FBD8; ++j )
  {
    sub_45FC60(*j);
    result = dword_99FBD8;
  }
  return result;
}



// ------------------------------------------------------------
// 0x475810 sub_475810
// ------------------------------------------------------------
// ★ 巨型（~310 行，userpurge）—— 进副本一次性演出，docs/13 遗留#3 课题：
// 震屏 85/100 触发 + 副本物件批量生成（"ITEM CREATE FAIL!" 族日志可见）；
// 半还原范围（前半主干），完整逻辑待 P5 专项
void /*userpurge*/ sub_475810(int *a1@<ecx>, int a2@<esi>, int a3, int a4)
{
  int *v4; // ebx
  int v5; // eax
  int v6; // ecx
  int v7; // edi
  int v8; // ecx
  uint32_t *v9; // esi
  int v10; // eax
  int v11; // eax
  int *v12; // esi
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // ecx
  int i; // edi
  int v18; // ecx
  void *v19; // eax
  int v20; // ebx
  int *v21; // edx
  int v22; // eax
  int v23; // ecx
  int j; // edi
  uint32_t *v25; // ebx
  uint8_t *v26; // esi
  uint32_t *v27; // eax
  int v28; // eax
  int v29; // ebx
  int v30; // eax
  int v31; // eax
  uint32_t **v32; // eax
  uint32_t *v33; // edi
  bool v34; // zf
  void *v35; // eax
  int v36; // ebx
  int v37; // eax
  int v38; // esi
  int v39; // eax
  int v40; // eax
  int v41; // esi
  int v42; // ecx
  uint32_t *v43; // esi
  void *v44; // eax
  int v45; // edi
  int v46; // edx
  int v47; // eax
  int v48; // esi
  int v49; // [esp-10h] [ebp-5Ch]
  int v50; // [esp-8h] [ebp-54h]
  unsigned int Seed; // [esp+18h] [ebp-34h]
  unsigned int Seeda; // [esp+18h] [ebp-34h]
  int *v54; // [esp+1Ch] [ebp-30h]
  int v55; // [esp+20h] [ebp-2Ch] BYREF
  int v56; // [esp+24h] [ebp-28h]
  int v57; // [esp+28h] [ebp-24h]
  int v58; // [esp+2Ch] [ebp-20h]
  int v59; // [esp+30h] [ebp-1Ch]
  int v60; // [esp+34h] [ebp-18h]
  int *v61; // [esp+38h] [ebp-14h]
  int v62; // [esp+3Ch] [ebp-10h] BYREF
  int v63; // [esp+48h] [ebp-4h]
  uint32_t *v64; // [esp+54h] [ebp+8h]
  int v65; // [esp+54h] [ebp+8h]
  int v66; // [esp+58h] [ebp+Ch]
  uint32_t *v67; // [esp+58h] [ebp+Ch]

  v4 = a1;
  v5 = a3 + a4 * *(uint32_t *)(a1[42] + 8 * dword_99FB78);
  v6 = *(uint32_t *)(dword_99FBC4 + 4 * v5);
  v7 = 4 * v5;
  v61 = v4;
  Seed = 4 * v5;
  if ( v6 == 0 )
  {
    v8 = *v4;
    if ( *v4 < 15 || (dword_79D0C4 = 85, v8 > 16) )
      dword_79D0C4 = 100;
    v9 = (uint32_t *)(dword_99FBB4 + 36 * v5);
    v10 = *(uint32_t *)(dword_99FBD4 + 4 * v5);
    v60 = (int)v9;
    v59 = v10;
    v63 = 0;
    if ( operator new(0x208u) != nullptr )
    {
      v7 = Seed;
      v58 = sub_42ECF0(
              *v9,
              *(uint32_t *)(*(uint32_t *)(v4[46] + 16 * dword_99FB78 + 4)
                        + 4 * (a3 + a4 * *(uint32_t *)(v4[42] + 8 * dword_99FB78))));
    }
    else
    {
      v58 = 0;
    }
    *(uint32_t *)(dword_99FBC4 + v7) = v58;
    v63 = -1;
    v11 = sub_456390(0);
    v50 = *v9;
    v56 = v11;
    v12 = (int *)sub_4CE8A0(v50);
    v13 = *(uint32_t *)(dword_8F850C + 16);
    v54 = v12;
    v62 = 0;
    if ( v13 != 0 )
      v62 = *(uint16_t *)(v13 + 4);
    v14 = *(uint32_t *)(dword_8F850C + 20);
    if ( v14 != 0 )
      v62 += *(uint16_t *)(v14 + 4);
    v15 = *(uint32_t *)(dword_8F850C + 24);
    if ( v15 != 0 )
      v62 += *(uint16_t *)(v15 + 4);
    v16 = *(uint32_t *)(dword_8F850C + 28);
    if ( v16 != 0 )
      v62 += *(uint16_t *)(v16 + 4);
    Seeda = v56
          + v62
          + *(uint32_t *)(*(uint32_t *)(v4[46] + 16 * dword_99FB78 + 4)
                      + 4 * (a3 + a4 * *(uint32_t *)(v4[42] + 8 * dword_99FB78)))
          + v4[123]
          + *(uint32_t *)v60;
    off_77F3FC((char *)&byte_6C8724, Seeda, v4[123]);
    sub_4602C0(v12);
    v62 = v12[14];
    for ( i = 0; i < 4; ++i )
    {
      v57 = 2;
      v4[i + 119] = 0;
      if ( (uint8_t)sub_48C220(i) != 0 )
      {
        v18 = a4;
        v57 = 0;
        if ( dword_99FB7C == a3 && dword_99FB80 == a4 )
          goto LABEL_27;
        v55 = a3;
        switch ( i )
        {
          case 0:
            v55 = a3 - 1;
            break;
          case 1:
            v55 = a3 + 1;
            break;
          case 2:
            v18 = a4 - 1;
            break;
          case 3:
            v18 = a4 + 1;
            break;
          default:
            break;
        }
        if ( dword_99FB7C == v55 && dword_99FB80 == v18 )
LABEL_27:
          v57 = 1;
      }
      v19 = (void *)v4[2 * i + 29 + i + v57];
      if ( v19 != (void *)-1 )
      {
        v20 = sub_53A220(v19, nullptr);
        sub_45FE80(33, v62, v20, 0, 0);
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v20 + 112))(v20, v12[2 * i + 54], v12[2 * i + 55], 0);
        if ( __RTDynamicCast(v20, 0, &CNRDPassiveObject `RTTI Type Descriptor', &CNPathGate `RTTI Type Descriptor', 0) != 0 )
          sub_577A30(v58, i);
        v21 = v61;
        v22 = v62 + 1;
        v61[i + 119] = v20;
        v62 = v22;
        v4 = v21;
      }
    }
    v23 = v60;
    *(uint32_t *)dword_9A05CC = 0;
    dword_9A05D0 = 0;
    dword_9A05D4 = 0;
    for ( j = *(uint32_t *)(v60 + 8); j != *(uint32_t *)(v60 + 12); j += 28 )
    {
      if ( *(uint8_t *)(j + 20) != 1 )
      {
        off_77F3FC((char *)&byte_6C86EC, *(uint32_t *)j, *(uint32_t *)(j + 8), *(uint32_t *)(j + 12));
        v25 = (uint32_t *)(v12[16] + 56 * *(uint32_t *)j);
        v64 = v25;
        v26 = (uint8_t *)sub_4ABE10(*(void **)(j + 8), *(void **)(j + 12), 0);
        if ( v56 > 1 )
        {
          v27 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v26 + 1040))(v26);
          *v27 += 50 * v56 - 50;
          v28 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v26 + 1040))(v26);
          *(uint32_t *)(v28 + 72) += 7 * v56 - 7;
        }
        if ( (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)v26 + 436))(v26, a2) <= 0 )
          v66 = v25[5];
        else
          v66 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v26 + 436))(v26);
        a2 = 100;
        (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v26 + 372))(v26);
        (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, int))(*(uint32_t *)v26 + 112))(v26, v25[3], v25[4], v66);
        v26[7801] = 1;
        sub_45FE80(529, *(uint32_t *)(j + 4), v26, 0, 0);
        v29 = *(uint32_t *)v26;
        v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 144))(dword_8F8520);
        (*(void (/*thiscall*/ **)(uint8_t *, int))(v29 + 1044))(v26, v30);
        v31 = *(uint32_t *)(j + 16);
        if ( v31 == 1 || v31 == 2 )
        {
          (*(void (/*thiscall*/ **)(uint8_t *, unsigned int, uint32_t *, uint32_t))(*(uint32_t *)v26 + 1160))(
            v26,
            Seeda + *(uint32_t *)(j + 8),
            v64 + 10,
            *(uint32_t *)(j + 16));
          ++dword_9A05D0;
        }
        else if ( v31 == 3 )
        {
          (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v26 + 1120))(v26);
          ++*(uint32_t *)dword_9A05CC;
        }
        sub_495C00(1);
        v12 = v54;
      }
      v23 = v60;
    }
    v32 = (uint32_t **)v12[21];
    v33 = *v32;
    v34 = *v32 == v32;
    v63 = 1;
    v65 = 0;
    v67 = v33;
    if ( !v34 )
    {
      while ( 1 )
      {
        v35 = (void *)v33[8];
        if ( v35 != (void *)-1 )
        {
          v36 = sub_53A220(v35, nullptr);
          v34 = (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v36 + 40))(v36, 1057, a2) == 0;
          v37 = *(uint32_t *)v36;
          if ( v34 )
          {
            a2 = 1;
            (*(void (/*thiscall*/ **)(int))v37)(v36);
          }
          else
          {
            a2 = v33[10];
            (*(void (/*thiscall*/ **)(int, uint32_t))(v37 + 724))(v36, v33[9]);
            v38 = v62;
            sub_45FE80(33, v62, v36, 0, 0);
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v36 + 112))(v36, v33[5], v33[6], v33[7]);
            v62 = v38 + 1;
            v55 = v36;
            sub_45F8A0(nullptr, 1, (int)&v55);
            v39 = 0;
            v55 = 0;
            while ( 1 )
            {
              v56 = v39;
              v40 = *(uint32_t *)(v60 + 24);
              if ( v40 == 0 || v55 >= (unsigned int)((*(uint32_t *)(v60 + 28) - v40) / 20) )
                break;
              v41 = *(uint32_t *)(v60 + 24);
              v42 = *(uint32_t *)(v41 + v56);
              v43 = (uint32_t *)(v56 + v41);
              if ( v42 == v65 )
              {
                v44 = (void *)v43[2];
                if ( v44 != (void *)0xFFFF )
                {
                  v45 = sub_522300(v44, v43[3], 0, 0, v43[4], 1);
                  if ( v45 != 0 )
                  {
                    v46 = *(uint32_t *)v36;
                    v57 = v43[1];
                    (*(void (/*thiscall*/ **)(int, int, int))(v46 + 720))(v36, v57, v45);
                    v47 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v45 + 16))(v45);
                    off_77F3FC(aItem_1, v67[8], v65, v57, *(uint32_t *)(v47 + 4));
                    *v43 = -345;
                  }
                  else
                  {
                    off_77F3FC("ITEM CREATE FAIL! ItemIndex %d", v43[2]);
                  }
                  v33 = v67;
                }
              }
              ++v55;
              v39 = v56 + 20;
            }
          }
          v12 = v54;
        }
        v67 = (uint32_t *)*v33;
        ++v65;
        if ( *v33 == v12[21] )
          break;
        v33 = (uint32_t *)*v33;
      }
      v23 = v60;
    }
    v49 = (int)v12;
    v48 = v59;
    sub_4730F0(v59, v23, v49, (int)&v62, Seeda);
    sub_425960(1, v58, v48);
    nullsub_3(dword_8F84BC);
  }
}


// ------------------------------------------------------------
// 0x475EB0 sub_475EB0
// ------------------------------------------------------------
int /*thiscall*/ sub_475EB0(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 56 )
      sub_4750B0(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x475EF0 sub_475EF0
// ------------------------------------------------------------
int sub_475EF0()
{
  int v0; // ebx
  int v1; // eax
  void *v2; // esi
  void ***v3; // edi
  void ***v4; // esi
  int result; // eax
  int *i; // esi
  void *v7; // edi
  int *j; // esi
  void *v9; // edi
  int v10; // [esp+Ch] [ebp-4h] BYREF

  v0 = dword_99FB9C;
  v1 = *(uint32_t *)dword_99FB9C;
  v10 = *(uint32_t *)dword_99FB9C;
  if ( v10 != dword_99FB9C )
  {
    do
    {
      v2 = *(void **)(v1 + 16);
      if ( v2 != nullptr )
      {
        sub_42E940(*(void **)(v1 + 16));
        j__free(v2);
        v0 = dword_99FB9C;
      }
      sub_41C5E0(&v10);
      v1 = v10;
    }
    while ( v10 != v0 );
  }
  v3 = *(void ****)(v0 + 4);
  v4 = v3;
  if ( *((uint8_t *)v3 + 21) == 0 )
  {
    do
    {
      sub_472DF0(v4[2]);
      v4 = (void ***)*v4;
      j__free(v3);
      v3 = v4;
    }
    while ( *((uint8_t *)v4 + 21) == 0 );
    v0 = dword_99FB9C;
  }
  *(uint32_t *)(v0 + 4) = v0;
  dword_99FBA0 = 0;
  *(uint32_t *)dword_99FB9C = dword_99FB9C;
  result = dword_99FB9C;
  *(uint32_t *)(dword_99FB9C + 8) = dword_99FB9C;
  for ( i = (int *)dword_99FBC4; i != (int *)dword_99FBC8; ++i )
  {
    v7 = (void *)*i;
    if ( *i != 0 )
    {
      sub_42EDE0(*i);
      j__free(v7);
    }
    result = dword_99FBC8;
  }
  for ( j = (int *)dword_99FBD4; j != (int *)dword_99FBD8; ++j )
  {
    v9 = (void *)*j;
    if ( *j != 0 )
    {
      sub_42C770(*j);
      j__free(v9);
    }
    result = dword_99FBD8;
  }
  return result;
}



// ------------------------------------------------------------
// 0x476000 sub_476000
// ------------------------------------------------------------
int /*thiscall*/ sub_476000(char *this)
{
  int v2; // edi
  void **v3; // edi
  int result; // eax
  void *Block; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]
  int j; // [esp+10h] [ebp-4h]

  *(uint32_t *)this = 0;
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0((void *)szPassword, 0);
  *((uint32_t *)this + 29) = 0;
  sub_4015C0((void *)szPassword, 0);
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 39) = 0;
  *((uint32_t *)this + 40) = 0;
  sub_4015C0((void *)szPassword, 0);
  *((uint32_t *)this + 48) = 0;
  *((uint32_t *)this + 49) = 0xFFFF;
  *((uint32_t *)this + 50) = 0;
  *(this + 204) = 0;
  *((uint32_t *)this + 52) = -1;
  *((uint32_t *)this + 53) = 1;
  *((uint32_t *)this + 54) = 1065353216;
  *((uint32_t *)this + 55) = 0;
  *((uint32_t *)this + 56) = 0;
  *((uint32_t *)this + 57) = 0;
  *((uint32_t *)this + 58) = 0;
  if ( *((uint32_t *)this + 60) != 0 )
    j__free(*((void **)this + 60));
  *((uint32_t *)this + 60) = 0;
  *((uint32_t *)this + 61) = 0;
  *((uint32_t *)this + 62) = 0;
  *((uint32_t *)this + 63) = -1;
  *((uint32_t *)this + 64) = -1;
  *((uint32_t *)this + 65) = -1;
  *((uint32_t *)this + 66) = -1;
  *((uint32_t *)this + 67) = -1;
  *((uint32_t *)this + 68) = -1;
  *((uint32_t *)this + 69) = -1;
  *((uint32_t *)this + 70) = -1;
  *((uint32_t *)this + 71) = -1;
  *((uint32_t *)this + 72) = -1;
  *((uint32_t *)this + 73) = -1;
  *((uint32_t *)this + 74) = -1;
  v2 = *((uint32_t *)this + 76);
  if ( v2 != 0 )
  {
    for ( i = *((uint32_t *)this + 77); v2 != i; v2 += 56 )
      sub_4750B0(v2);
    j__free(*((void **)this + 76));
  }
  *((uint32_t *)this + 76) = 0;
  *((uint32_t *)this + 77) = 0;
  *((uint32_t *)this + 78) = 0;
  sub_4015C0((void *)szPassword, 0);
  v3 = (void **)(this + 404);
  for ( j = 3; j != 0; --j )
  {
    Block = *v3;
    if ( *v3 != nullptr )
    {
      sub_472F40();
      j__free(Block);
    }
    *v3++ = nullptr;
  }
  result = sub_42C250(this + 416);
  *(this + 684) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4761F0 sub_4761F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4761F0(int this)
{
  int v2; // edi

  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 56) = 15;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 36) = 0;
  *(uint32_t *)(this + 84) = 15;
  *(uint32_t *)(this + 80) = 0;
  *(uint8_t *)(this + 64) = 0;
  *(uint32_t *)(this + 112) = 15;
  *(uint32_t *)(this + 108) = 0;
  *(uint8_t *)(this + 92) = 0;
  *(uint32_t *)(this + 144) = 15;
  *(uint32_t *)(this + 140) = 0;
  *(uint8_t *)(this + 124) = 0;
  *(uint32_t *)(this + 188) = 15;
  *(uint32_t *)(this + 184) = 0;
  *(uint8_t *)(this + 168) = 0;
  *(uint32_t *)(this + 196) = 0xFFFF;
  *(uint32_t *)(this + 200) = 0;
  *(uint8_t *)(this + 204) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  *(uint32_t *)(this + 248) = 0;
  *(uint32_t *)(this + 304) = 0;
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 340) = 15;
  *(uint32_t *)(this + 336) = 0;
  *(uint8_t *)(this + 320) = 0;
  v2 = this + 344;
  sub_472FF0((uint32_t *)(this + 344));
  sub_42D620(this + 416);
  *(uint32_t *)(this + 400) = 0;
  *(uint32_t *)(this + 404) = 0;
  *(uint32_t *)(this + 408) = 0;
  *(uint32_t *)(this + 412) = 0;
  *(uint32_t *)(this + 400) = v2;
  sub_476000((char *)this);
  return this;
}



// ============================================================
// 【分区 6】副本创建（0x476300-0x477060）
// "DUNGEON create FAIL! FILENAME[%s]" / "INDEX %d" 自证（0x476600/0x476AF0）；
// 选区角色数据查找 0x476B60（座位表 sub_453DD0 所用）。
// ============================================================
// ------------------------------------------------------------
// 0x476300 sub_476300
// ------------------------------------------------------------
void /*thiscall*/ sub_476300(int this)
{
  uint32_t *v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // edi
  char *v6; // ecx
  int v7; // [esp+Ch] [ebp-1Ch]
  char *v8; // [esp+10h] [ebp-18h]
  int i; // [esp+14h] [ebp-14h]
  int v10; // [esp+14h] [ebp-14h]
  uint32_t *v11; // [esp+18h] [ebp-10h]
  char *v12; // [esp+18h] [ebp-10h]

  v2 = (uint32_t *)(this + 404);
  v11 = (uint32_t *)(this + 404);
  for ( i = 3; i != 0; --i )
  {
    v3 = *v2;
    if ( *v2 != 0 )
    {
      if ( *(uint32_t *)(v3 + 52) >= 0x10u )
        j__free(*(void **)(v3 + 32));
      *(uint32_t *)(v3 + 52) = 15;
      *(uint32_t *)(v3 + 48) = 0;
      *(uint8_t *)(v3 + 32) = 0;
      if ( *(uint32_t *)(v3 + 24) >= 0x10u )
        j__free(*(void **)(v3 + 4));
      *(uint32_t *)(v3 + 24) = 15;
      *(uint32_t *)(v3 + 20) = 0;
      *(uint8_t *)(v3 + 4) = 0;
      j__free((void *)v3);
      v2 = v11;
    }
    *v2++ = 0;
    v11 = v2;
  }
  sub_42C370(this + 416);
  if ( *(uint32_t *)(this + 396) >= 0x10u )
    j__free(*(void **)(this + 376));
  *(uint32_t *)(this + 396) = 15;
  *(uint32_t *)(this + 392) = 0;
  *(uint8_t *)(this + 376) = 0;
  if ( *(uint32_t *)(this + 368) >= 0x10u )
    j__free(*(void **)(this + 348));
  *(uint32_t *)(this + 368) = 15;
  *(uint32_t *)(this + 364) = 0;
  *(uint8_t *)(this + 348) = 0;
  if ( *(uint32_t *)(this + 340) >= 0x10u )
    j__free(*(void **)(this + 320));
  *(uint32_t *)(this + 340) = 15;
  *(uint32_t *)(this + 336) = 0;
  *(uint8_t *)(this + 320) = 0;
  v4 = *(uint32_t *)(this + 304);
  if ( v4 != 0 )
  {
    v7 = *(uint32_t *)(this + 308);
    v10 = *(uint32_t *)(this + 304);
    if ( v4 != v7 )
    {
      v5 = v4 + 44;
      do
      {
        if ( *(uint32_t *)v5 != 0 )
          j__free(*(void **)v5);
        *(uint32_t *)v5 = 0;
        *(uint32_t *)(v5 + 4) = 0;
        *(uint32_t *)(v5 + 8) = 0;
        if ( *(uint32_t *)(v5 - 16) != 0 )
          j__free(*(void **)(v5 - 16));
        *(uint32_t *)(v5 - 16) = 0;
        *(uint32_t *)(v5 - 12) = 0;
        *(uint32_t *)(v5 - 8) = 0;
        v6 = *(char **)(v5 - 32);
        if ( v6 != nullptr )
        {
          v8 = *(char **)(v5 - 28);
          v12 = *(char **)(v5 - 32);
          if ( v6 != v8 )
          {
            while ( 1 )
            {
              sub_472FC0(v6, 0);
              v12 += 36;
              if ( v12 == v8 )
                break;
              v6 = v12;
            }
          }
          j__free(*(void **)(v5 - 32));
        }
        *(uint32_t *)(v5 - 32) = 0;
        *(uint32_t *)(v5 - 28) = 0;
        *(uint32_t *)(v5 - 24) = 0;
        v5 += 56;
        v10 += 56;
      }
      while ( v10 != v7 );
    }
    j__free(*(void **)(this + 304));
  }
  *(uint32_t *)(this + 304) = 0;
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 312) = 0;
  if ( *(uint32_t *)(this + 240) != 0 )
    j__free(*(void **)(this + 240));
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  *(uint32_t *)(this + 248) = 0;
  if ( *(uint32_t *)(this + 188) >= 0x10u )
    j__free(*(void **)(this + 168));
  *(uint32_t *)(this + 188) = 15;
  *(uint32_t *)(this + 184) = 0;
  *(uint8_t *)(this + 168) = 0;
  if ( *(uint32_t *)(this + 144) >= 0x10u )
    j__free(*(void **)(this + 124));
  *(uint32_t *)(this + 144) = 15;
  *(uint32_t *)(this + 140) = 0;
  *(uint8_t *)(this + 124) = 0;
  if ( *(uint32_t *)(this + 112) >= 0x10u )
    j__free(*(void **)(this + 92));
  *(uint32_t *)(this + 112) = 15;
  *(uint32_t *)(this + 108) = 0;
  *(uint8_t *)(this + 92) = 0;
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
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
}


// ------------------------------------------------------------
// 0x476600 sub_476600
// ------------------------------------------------------------
// 副本创建（按文件名）—— "DUNGEON create FAIL! FILENAME[%s]" 自证：
// dword_9B0BB8 表查词条 → sub_476600 主干：障碍/事件列表展开（9 字节/项）、
// 464 偏移状态、dword_99FB70 清零、+123=-1
int /*thiscall*/ sub_476600(size_t *this, const char *ArgList)
{
  size_t *v2; // ebx
  unsigned int v4; // eax
  unsigned int v5; // ecx
  unsigned int v6; // eax
  unsigned int v7; // ecx
  unsigned int v8; // edx
  int *v9; // edx
  uint32_t *v10; // ecx
  size_t v11; // eax
  unsigned int *v12; // eax
  uint32_t *v13; // eax
  uint32_t *v14; // eax
  uint32_t *v15; // eax
  int i; // esi
  unsigned int *v17; // eax
  uint32_t *v18; // eax
  int v19; // eax
  int v20; // edx
  int v21; // edi
  size_t v22; // eax
  size_t *v23; // esi
  unsigned int v24; // edx
  size_t v25; // ebx
  uint32_t *v26; // edx
  uint8_t *v27; // ebx
  uint32_t *v28; // esi
  bool v29; // zf
  size_t v30; // edx
  size_t *v31; // esi
  unsigned int v32; // ecx
  char *v33; // edi
  unsigned int v34; // [esp-Ch] [ebp-2F4h]
  unsigned int v35; // [esp-4h] [ebp-2ECh]
  uint32_t v36[2]; // [esp+8h] [ebp-2E0h] BYREF
  size_t *v37; // [esp+10h] [ebp-2D8h]
  char v38[4]; // [esp+14h] [ebp-2D4h] BYREF
  uint8_t *v39; // [esp+18h] [ebp-2D0h]
  uint32_t *v40; // [esp+1Ch] [ebp-2CCh]
  int v41; // [esp+20h] [ebp-2C8h]
  int v42; // [esp+24h] [ebp-2C4h]
  int v43; // [esp+28h] [ebp-2C0h] BYREF
  size_t v44[7]; // [esp+2Ch] [ebp-2BCh] BYREF
  size_t v45[7]; // [esp+48h] [ebp-2A0h] BYREF
  char v46[4]; // [esp+64h] [ebp-284h] BYREF
  int v47; // [esp+68h] [ebp-280h] BYREF
  uint8_t v48[4]; // [esp+70h] [ebp-278h] BYREF
  uint8_t v49[4]; // [esp+74h] [ebp-274h] BYREF
  unsigned int v50; // [esp+78h] [ebp-270h]
  unsigned int v51; // [esp+7Ch] [ebp-26Ch]
  char v52[4]; // [esp+80h] [ebp-268h] BYREF
  unsigned int v53[7]; // [esp+84h] [ebp-264h] BYREF
  char v54[4]; // [esp+A0h] [ebp-248h] BYREF
  uint32_t *v55; // [esp+A4h] [ebp-244h] BYREF
  uint8_t v56[4]; // [esp+ACh] [ebp-23Ch] BYREF
  uint8_t v57[4]; // [esp+B0h] [ebp-238h] BYREF
  unsigned int v58[6]; // [esp+B4h] [ebp-234h] BYREF
  char v59[4]; // [esp+CCh] [ebp-21Ch] BYREF
  unsigned int v60[34]; // [esp+D0h] [ebp-218h] BYREF
  int v61; // [esp+158h] [ebp-190h]
  int v62; // [esp+15Ch] [ebp-18Ch]
  uint32_t v63[24]; // [esp+168h] [ebp-180h] BYREF
  uint8_t v64[272]; // [esp+1C8h] [ebp-120h] BYREF
  int v65; // [esp+2D8h] [ebp-10h]
  int v66; // [esp+2E4h] [ebp-4h]
  int ArgLista; // [esp+2F0h] [ebp+8h]
  unsigned int ArgListb; // [esp+2F0h] [ebp+8h]

  v2 = this;
  v65 = dword_796E50;
  v37 = this;
  sub_4761F0(&v43);
  v66 = 0;
  if ( (uint8_t)sub_4F1A20((int)&v43, (char)ArgList) != 0 )
  {
    *v2 = v43;
    sub_4014D0(v2 + 1, v44, 0, 0xFFFFFFFF);
    sub_4014D0(v2 + 8, v45, 0, 0xFFFFFFFF);
    v4 = v60[7];
    v2[23] = v60[6];
    v5 = v60[8];
    v2[24] = v4;
    v6 = v60[9];
    v2[25] = v5;
    v7 = v60[10];
    v2[26] = v6;
    v8 = v60[11];
    v34 = v50;
    v2[27] = v7;
    v2[28] = v8;
    if ( sub_40BF00((std::_String_base *)v46, 0, v34, szPassword, 0) != 0 )
    {
      v42 = sub_42FCB0(228);
      LOBYTE(v66) = 1;
      if ( v42 != 0 )
      {
        LOBYTE(v9) = v47;
        if ( v51 < 0x10 )
          v9 = &v47;
        LOBYTE(v10) = v63[0];
        if ( v63[5] < 0x10u )
          v10 = v63;
        v11 = sub_431920((char)v10, (char)v9, 1);
      }
      else
      {
        v11 = 0;
      }
      LOBYTE(v66) = 0;
      v2[15] = v11;
      sub_699070(0);
    }
    if ( sub_40BF00((std::_String_base *)v52, 0, v53[4], szPassword, 0) != 0 )
    {
      v12 = (unsigned int *)v53[0];
      if ( v53[5] < 0x10 )
        v12 = v53;
      v35 = v53[6];
      v13 = (uint32_t *)(*(int (/*thiscall*/ **)(int, unsigned int *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v12);
      v2[16] = sub_418DD0(v13, v35);
    }
    if ( sub_40BF00((std::_String_base *)v54, 0, v58[0], szPassword, 0) != 0 )
    {
      v14 = v55;
      if ( v58[1] < 0x10 )
        v14 = &v55;
      v2[17] = (*(int (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v14);
    }
    v15 = v2 + 19;
    for ( i = 2; i != 0; --i )
    {
      *(v15 - 1) = *(uint32_t *)((char *)v15 + v48 - (uint8_t *)v2);
      *v15 = *(uint32_t *)((char *)v15 + v49 - (uint8_t *)v2);
      v15 += 2;
    }
    if ( sub_40BF00((std::_String_base *)v59, 0, v60[4], szPassword, 0) != 0 )
    {
      v17 = (unsigned int *)v60[0];
      if ( v60[5] < 0x10 )
        v17 = v60;
      v2[22] = (*(int (/*thiscall*/ **)(int, unsigned int *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v17);
    }
    v18 = v2 + 30;
    for ( ArgLista = 4; ArgLista != 0; --ArgLista )
    {
      *(v18 - 1) = *(uint32_t *)((char *)v18 + v56 - (uint8_t *)v2);
      *v18 = *(uint32_t *)((char *)v18 + v57 - (uint8_t *)v2);
      v18[1] = *(uint32_t *)((char *)v18 + (char *)v58 - (char *)v2);
      v18 += 3;
    }
    v19 = 0;
    for ( ArgListb = 0; ; ++ArgListb )
    {
      v42 = v19;
      if ( v61 == 0 || ArgListb >= (v62 - v61) / 56 )
        break;
      v20 = *(uint32_t *)(v42 + v61 + 4);
      v21 = v42 + v61;
      v22 = v2[42];
      v23 = v2 + 41;
      v36[0] = *(uint32_t *)(v42 + v61);
      v36[1] = v20;
      if ( v22 != 0 )
        v24 = (int)(v2[43] - v22) >> 3;
      else
        v24 = 0;
      if ( v22 != 0 && v24 < (int)(v2[44] - v22) >> 3 )
      {
        v25 = v2[43];
        sub_63A7C0(v25, 1, v36);
        v23[2] = v25 + 8;
      }
      else
      {
        sub_473A80(v2[43], 1, v36);
      }
      v26 = nullptr;
      v27 = nullptr;
      v39 = nullptr;
      v40 = nullptr;
      v41 = 0;
      v28 = *(uint32_t **)(v21 + 12);
      v29 = v28 == *(uint32_t **)(v21 + 16);
      LOBYTE(v66) = 2;
      if ( !v29 )
      {
        do
        {
          if ( v27 != nullptr && ((char *)v26 - v27) >> 2 < (unsigned int)((v41 - (int)v39) >> 2) )
          {
            *v26++ = *v28;
            v40 = v26;
          }
          else
          {
            sub_430C80(v26, 1, (int)v28);
            v26 = v40;
          }
          v27 = v39;
          v28 += 9;
        }
        while ( v28 != *(uint32_t **)(v21 + 16) );
      }
      v30 = v37[46];
      v31 = v37 + 45;
      if ( v30 != 0 )
        v32 = (int)(v37[47] - v30) >> 4;
      else
        v32 = 0;
      if ( v30 != 0 && v32 < (int)(v37[48] - v30) >> 4 )
      {
        v33 = (char *)v37[47];
        sub_474A40(v33, 1, v38, (int)(v37 + 45));
        v31[2] = (size_t)(v33 + 16);
      }
      else
      {
        sub_474DE0((int)(v37 + 45), (void *)v37[47], 1, v38);
      }
      LOBYTE(v66) = 0;
      if ( v27 != nullptr )
        j__free(v27);
      v2 = v37;
      v39 = nullptr;
      v40 = nullptr;
      v41 = 0;
      v19 = v42 + 56;
    }
    sub_474790(v64);
    *((uint8_t *)v2 + 464) = v64[268];
    *(uint32_t *)dword_99FB70 = 0;
    v2[123] = -1;
    v66 = -1;
    return sub_476300(&v43);
  }
  else
  {
    off_77F3FC("DUNGEON create FAIL! FILENAME[%s]", ArgList);
    v66 = -1;
    return sub_476300(&v43);
  }
}


// ------------------------------------------------------------
// 0x476AF0 sub_476AF0
// ------------------------------------------------------------
// 副本创建（按索引）—— "DUNGEON create FAIL! INDEX %d" 自证；词条取后转 0x476600
void /*thiscall*/ sub_476AF0(char *this, int ArgList)
{
  int v2; // edi
  const char *v4; // eax
  int *v5; // [esp+8h] [ebp-4h] BYREF

  v2 = ArgList;
  sub_442D00(&dword_9B0BB8, &v5, &ArgList);
  if ( v5 == (int *)dword_9B0BBC
    || ((unsigned int)v5[10] < 0x10 ? (v4 = (const char *)(v5 + 5)) : (v4 = (const char *)v5[5]), v4 == nullptr) )
  {
    off_77F3FC("DUNGEON create FAIL! INDEX %d", v2);
  }
  else
  {
    sub_476600(this, v4);
  }
}



// ------------------------------------------------------------
// 0x476B60 sub_476B60
// ------------------------------------------------------------
// 选区角色数据查找（座位表 sub_453DD0 所用；+80/+84 名字串）
void */*cdecl*/ sub_476B60(int a1)
{
  void *v2; // eax
  int v3; // edi
  void *v4; // esi
  uint8_t v5[8]; // [esp+0h] [ebp-1Ch] BYREF
  int v6; // [esp+8h] [ebp-14h] BYREF
  void *Block; // [esp+Ch] [ebp-10h] BYREF
  int v8; // [esp+18h] [ebp-4h]

  sub_472E30(&dword_99FB98, (int **)&Block, &a1);
  if ( Block != (void *)dword_99FB9C )
    return *((void **)Block + 4);
  v2 = operator new(0x1F0u);
  Block = v2;
  v3 = a1;
  v4 = nullptr;
  v8 = 0;
  if ( v2 != nullptr )
    v4 = sub_42E8F0(v2, a1);
  v8 = -1;
  v6 = v3;
  Block = v4;
  sub_473920(&dword_99FB98, (int)v5, &v6);
  return v4;
}



// ------------------------------------------------------------
// 0x476C10 sub_476C10
// ------------------------------------------------------------
int /*thiscall*/ sub_476C10(uint32_t *this)
{
  *(this + 48) = 0;
  *(this + 49) = 0;
  *(this + 19) = 0;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 1) = 0;
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
  return 0;
}



// ------------------------------------------------------------
// 0x476C50 sub_476C50
// ------------------------------------------------------------
int /*thiscall*/ sub_476C50(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  uint32_t *v5; // esi
  int i; // edi

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 19);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 20);
  *(this + 19) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 20) = 0;
  v5 = this + 9;
  for ( i = 10; i != 0; --i )
  {
    if ( *v5 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v5)(*v5, 1);
    *v5++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x476CA0 sub_476CA0
// ------------------------------------------------------------
int /*stdcall*/ sub_476CA0(int a1)
{
  uint8_t v1; // bl
  int v2; // eax
  int result; // eax

  v1 = a1;
  if ( a1 >= 220 )
    v1 = -36;
  v2 = sub_418DD0(0);
  if ( v2 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v2 + 128))(
      v2,
      94,
      63,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (v1 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  result = sub_418DD0(12);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
             result,
             264,
             13,
             dword_79C0B0,
             1065353216,
             1065353216,
             0,
             ((uint8_t)a1 << 24) | 0xFFFFFF,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x476D50 sub_476D50
// ------------------------------------------------------------
int /*thiscall*/ sub_476D50(uint32_t *this, int a2, int a3, float a4, int a5)
{
  double v5; // st7
  double v6; // st7
  int v7; // esi
  int v8; // eax
  int64_t v9; // rax
  float v11; // [esp+0h] [ebp-1Ch]
  float v12; // [esp+18h] [ebp-4h]
  float v13; // [esp+2Ch] [ebp+10h]

  v5 = (double)a2;
  v12 = v5;
  v6 = v5 * a4;
  v13 = a4 * 1000.0;
  if ( v6 >= v13 )
    v6 = v13;
  v7 = (uint64_t)v6;
  v8 = sub_699000((int)(this + 23)) - *(this + a3 + 30);
  if ( v7 < 400 )
    v7 = 400;
  if ( v7 <= v8 )
  {
    LODWORD(v9) = a2;
  }
  else
  {
    v11 = (float)a5;
    return (uint64_t)sub_4049C0(v11, v12, v8, v7);
  }
  return v9;
}



// ------------------------------------------------------------
// 0x476DD0 sub_476DD0
// ------------------------------------------------------------
int /*thiscall*/ sub_476DD0(uint32_t *this)
{
  int result; // eax

  switch ( sub_495C80(*(this + 49)) )
  {
    case '#':
      result = 10;
      break;
    case '(':
      result = 9;
      break;
    case '-':
      result = 8;
      break;
    case '7':
      result = 7;
      break;
    case 'F':
      result = 6;
      break;
    case 'U':
      result = 5;
      break;
    case '_':
      result = 4;
      break;
    case 'i':
      result = 3;
      break;
    default:
      result = 11;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x476EC0 sub_476EC0
// ------------------------------------------------------------
bool /*thiscall*/ sub_476EC0(uint32_t *this)
{
  return sub_495C80(*(this + 49)) >= 55;
}



// ------------------------------------------------------------
// 0x476EE0 sub_476EE0
// ------------------------------------------------------------
int /*thiscall*/ sub_476EE0(uint32_t *this)
{
  int v1; // ebx
  uint32_t *v2; // esi
  int v3; // edi
  int result; // eax
  int v5; // [esp+Ch] [ebp-8h]
  int v6; // [esp+10h] [ebp-4h]

  v1 = 0;
  v6 = (int)(this + 23);
  v5 = 0;
  v2 = this + 62;
  do
  {
    v3 = (uint64_t)((double)v5 + 270.0);
    *(v2 - 1) = v3 + sub_699000(v6);
    result = sub_699000(v6);
    v1 += 50;
    *v2 = result + v3 + 300;
    v2 += 3;
    v5 = v1;
  }
  while ( v1 < 100 );
  return result;
}



// ------------------------------------------------------------
// 0x476F50 sub_476F50
// ------------------------------------------------------------
int /*usercall*/ sub_476F50@<eax>(int a1@<ecx>, double a2@<st0>)
{
  uint32_t *v2; // eax
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // esi
  int v7; // eax
  bool v8; // zf
  int result; // eax
  float v10; // [esp+Ch] [ebp-10h]
  int v11; // [esp+10h] [ebp-Ch]
  int v12; // [esp+14h] [ebp-8h]
  uint32_t *v13; // [esp+18h] [ebp-4h]

  v2 = (uint32_t *)(a1 + 248);
  v12 = a1;
  v13 = (uint32_t *)(a1 + 248);
  v11 = 2;
  while ( 1 )
  {
    v3 = *(v2 - 1);
    v4 = *v2 - v3;
    v5 = sub_699000(a1 + 92);
    v6 = v5 - v3;
    if ( v5 - v3 > 0 && v6 < v4 )
    {
      if ( v6 >= 120 )
        sub_4049F0(255.0, 0.0, v5 - v3, v4, 1);
      else
        sub_4049F0(0.0, 255.0, v5 - v3, 120, 1);
      sub_4049F0(0.80000001, 1.3, v6, v4, 1);
      sub_491530(2, 0);
      v7 = sub_418DD0(2);
      if ( v7 != 0 )
      {
        v10 = a2;
        (*(void (/*thiscall*/ **)(int, int, int, int, uint32_t, uint32_t, uint32_t, int, int, int))(*(uint32_t *)v7 + 156))(
          v7,
          71,
          245,
          dword_79C0B0,
          LODWORD(v10),
          LODWORD(v10),
          0,
          ((uint8_t)(uint64_t)a2 << 24) | 0xFFFFFF,
          1122107392,
          1122107392);
      }
      sub_491630(2);
    }
    result = v11 - 1;
    v8 = v11 == 1;
    v13 += 3;
    --v11;
    if ( v8 )
      break;
    v2 = v13;
    a1 = v12;
  }
  return result;
}



// ============================================================
// 【分区 7】结算界面（0x477060-0x478C70）
// 事件自证：RESULT_FLASH / M_RESULT / RESULT_CHARACTER / RESULT_SCORE_UP_LOOP；
// 结算主类 CNRDResult__vmt0 = 0x477B60。
// ============================================================
// ------------------------------------------------------------
// 0x477060 sub_477060
// ------------------------------------------------------------
// 结算事件：RESULT_FLASH（6195 行附近）【推断：闪光演出】
int /*thiscall*/ sub_477060(uint32_t *this)
{
  int64_t v2; // rax
  int v3; // edi
  int v4; // eax

  LODWORD(v2) = *(this + 76);
  if ( (unsigned int)v2 >= 2 )
  {
    LODWORD(v2) = sub_699000((int)(this + 2)) - *(this + 76);
    if ( (int)v2 >= 0 )
    {
      v2 = 1717986919LL * ((int)v2 % 640);
      v3 = (SHIDWORD(v2) >> 5) + (HIDWORD(v2) >> 31);
      if ( v3 < 8 )
      {
        if ( v3 == 7 )
        {
          *(this + 76) = 1;
        }
        else
        {
          sub_491530(2, 0);
          v4 = sub_418DD0(v3 + 79);
          sub_40FC80(2, 375, v4);
          sub_491630(2);
          LODWORD(v2) = *(this + 50)
                      + *(this + 51)
                      + *(this + 52)
                      + *(this + 53)
                      + *(this + 54)
                      + *(this + 55)
                      + *(this + 56)
                      + *(this + 57);
          if ( v3 == 0 && *(this + 59) == 0 )
          {
            *(this + 59) = v2 + *(this + 58);
            LODWORD(v2) = sub_432EA0("RESULT_FLASH", -1, 0, 0);
          }
        }
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x477170 sub_477170
// ------------------------------------------------------------
char /*thiscall*/ sub_477170(int this)
{
  uint32_t *v2; // edi
  char result; // al

  memset((void *)(this + 120), 0, 0x44u);
  v2 = (uint32_t *)(this + 200);
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 228) = 0;
  sub_432FA0();
  *(uint32_t *)(this + 232) = 0;
  *v2 = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 228) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 324) = 0;
  *(uint16_t *)(this + 240) = 0;
  *(uint8_t *)(this + 242) = 0;
  memset((void *)(this + 244), 0, 0x3Cu);
  *(uint32_t *)(this + 304) = 0;
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 312) = 255;
  *(uint32_t *)(this + 188) = 0xFFFF;
  *(uint8_t *)(this + 105) = 0;
  *(uint8_t *)(this + 106) = 0;
  result = sub_698F90(this + 92, 0, 0);
  *(uint32_t *)(this + 316) = 0;
  *(uint8_t *)(this + 320) = 0;
  *(uint8_t *)(this + 328) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x477240 sub_477240
// ------------------------------------------------------------
char /*thiscall*/ sub_477240(int *this)
{
  int v1; // eax
  int *i; // ecx

  v1 = 0;
  for ( i = this + 50; *i <= 0; ++i )
  {
    if ( ++v1 >= 8 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x477260 sub_477260
// ------------------------------------------------------------
// 加载进度查询（触发条件 case 3 所用：sub_477260×100/sub_43B5C0）
double /*thiscall*/ sub_477260(void *this)
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this + 878));
}



// ------------------------------------------------------------
// 0x477280 sub_477280
// ------------------------------------------------------------
double /*thiscall*/ sub_477280(void *this)
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this + 906));
}



// ------------------------------------------------------------
// 0x4772A0 sub_4772A0
// ------------------------------------------------------------
// 结算事件：M_RESULT 打开结算界面（6339 行附近）
char /*thiscall*/ sub_4772A0(int this, int a2)
{
  int v3; // eax
  int i; // esi

  *(uint32_t *)(this + 4) = a2;
  *(uint32_t *)(this + 4 * *(uint32_t *)(this + 4) + 120) = sub_699000(this + 92);
  *(uint8_t *)(this + 21) = 0;
  *(uint8_t *)(this + 22) = 0;
  sub_698F90(this + 8, 0, 0);
  v3 = *(uint32_t *)(this + 4);
  if ( v3 >= 8 )
  {
    if ( v3 <= 15 )
    {
      if ( *(int *)(this + 4 * v3 + 168) <= 0 )
        LOBYTE(v3) = sub_4772A0(v3 + 1);
    }
    else if ( v3 == 16 )
    {
      LOBYTE(v3) = sub_432EE0(33311);
    }
  }
  if ( *(uint32_t *)(this + 4) != 0 )
  {
    if ( a2 == 1 )
    {
      *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = 0;
      for ( i = 0; i < 4; ++i )
        LOBYTE(v3) = sub_432EE0(i);
    }
    else if ( a2 == 16 )
    {
      sub_432EE0(33311);
      LOBYTE(v3) = sub_477240((int *)this);
      if ( (uint8_t)v3 != 0 )
        *(uint32_t *)(this + 304) = 500;
    }
    else
    {
      if ( *(uint8_t *)(*(uint32_t *)(this + 76) + 16) == 0 )
      {
        sub_65DC70(lpCriticalSection);
        LOBYTE(v3) = (uint8_t)sub_432EA0("M_RESULT", -1, 0, 0);
      }
      *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = 1;
    }
  }
  else
  {
    sub_477170(this);
    *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = 0;
    LOBYTE(v3) = sub_432EE0(33311);
  }
  return v3;
}



// ------------------------------------------------------------
// 0x4773B0 sub_4773B0
// ------------------------------------------------------------
char /*thiscall*/ sub_4773B0(int *this)
{
  int v2; // eax

  v2 = *(this + 1);
  if ( v2 != 0 && --v2 == 0 )
  {
    v2 = sub_699000((int)(this + 2));
    if ( v2 >= 3000 )
      LOBYTE(v2) = sub_4772A0((int)this, *(this + 1) + 1);
  }
  return v2;
}



// ------------------------------------------------------------
// 0x4773E0 sub_4773E0
// ------------------------------------------------------------
uint32_t */*userpurge*/ sub_4773E0@<eax>(int *a1@<ecx>, double a2@<st0>, int a3)
{
  int v3; // edi
  uint8_t v5; // bl
  int v6; // eax
  int v7; // ebx
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  uint8_t v11; // bl
  int v12; // eax
  int v13; // eax
  int v14; // edi
  uint32_t *result; // eax
  int v16; // ecx
  int *i; // edx
  int v18; // eax
  int v19; // ebx
  int v20; // edi
  uint8_t v21; // al
  int v22; // eax
  int v23; // ecx
  int v24; // edx
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // edi
  int v31; // ebx
  int v32; // eax
  int v33; // eax
  uint64_t v34; // rax
  int v35; // ebx
  int v36; // eax
  int v37; // eax
  bool v38; // cc
  int v39; // [esp-8h] [ebp-4Ch]
  int v40; // [esp-4h] [ebp-48h]
  int v41; // [esp-4h] [ebp-48h]
  int v42; // [esp+Ch] [ebp-38h]
  int *v43; // [esp+10h] [ebp-34h]
  int *v44; // [esp+14h] [ebp-30h]
  int v45; // [esp+18h] [ebp-2Ch]
  int v46; // [esp+1Ch] [ebp-28h]
  int v47; // [esp+20h] [ebp-24h]
  int v48; // [esp+24h] [ebp-20h]
  int v49; // [esp+24h] [ebp-20h]
  int v50; // [esp+24h] [ebp-20h]
  int v51; // [esp+24h] [ebp-20h]
  int Value; // [esp+28h] [ebp-1Ch]
  int Valuea; // [esp+28h] [ebp-1Ch]
  int Valueb; // [esp+28h] [ebp-1Ch]
  int v55; // [esp+2Ch] [ebp-18h]
  uint8_t v56; // [esp+2Ch] [ebp-18h]
  uint8_t v57; // [esp+2Ch] [ebp-18h]
  int v58; // [esp+30h] [ebp-14h]
  uint8_t v59; // [esp+30h] [ebp-14h]
  uint8_t v60; // [esp+30h] [ebp-14h]
  int v61; // [esp+30h] [ebp-14h]
  uint8_t v62; // [esp+37h] [ebp-Dh]
  bool v63; // [esp+37h] [ebp-Dh]
  char v64; // [esp+38h] [ebp-Ch]
  int v65; // [esp+39h] [ebp-Bh]
  int16_t v66; // [esp+3Dh] [ebp-7h]
  char v67; // [esp+3Fh] [ebp-5h]
  int v68; // [esp+40h] [ebp-4h]

  v3 = a3;
  v68 = dword_796E50;
  v5 = a3;
  if ( a3 >= 200 )
    v5 = -56;
  v6 = sub_418DD0(137);
  if ( v6 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
      v6,
      297,
      269,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (v5 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  v7 = a1[1];
  v65 = 0;
  v66 = 0;
  v8 = v7 - 8;
  v64 = 0;
  v67 = 0;
  v47 = v8;
  if ( v8 < 0 )
    goto LABEL_24;
  if ( v8 == 0 )
  {
    v9 = sub_699000((int)(a1 + 2));
    a2 = sub_4049C0(0.0, 255.0, v9, 300);
    a3 = (uint64_t)a2;
    v3 = a3;
  }
  sub_491530(2, 0);
  v10 = 120;
  if ( a1[59] != 0 )
    v10 = 255;
  v11 = v3;
  if ( v3 >= v10 )
    v11 = v10;
  v12 = sub_418DD0(139);
  if ( v12 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v12 + 128))(
      v12,
      299,
      403,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (v11 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  sub_491630(2);
  v13 = sub_418DD0(173);
  if ( v13 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
      v13,
      320,
      408,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)a3 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  v14 = a1[59];
  if ( v14 == 0 )
    v14 = a1[58];
  if ( v47 == 0 )
    v14 = sub_476D50(a1[58], a1[1], 1.0, 0);
  sub_69A110(504, 406, v14, a1[78]);
  if ( v47 != 0 || v14 != a1[58] )
  {
    v8 = v47;
LABEL_24:
    v16 = 1;
    for ( i = a1 + 51; ; ++i )
    {
      v18 = v8;
      if ( v8 >= 7 )
        v18 = 7;
      if ( v16 > v18 )
        break;
      if ( *i > 0 )
        *(&v64 + v16) = 1;
      ++v16;
    }
    v19 = 1;
    v46 = 1;
    v42 = 3;
    v43 = (int *)&unk_6C87E4;
    v44 = a1 + 51;
    while ( 1 )
    {
      v55 = *(uint32_t *)(sub_418DD0(138) + 20) >> 1;
      v62 = *(&v64 + v19);
      Value = dword_6C87D0[v42 + v62];
      v45 = *v43;
      v48 = *(uint32_t *)(sub_418DD0(Value) + 20) >> 1;
      v20 = *(uint32_t *)(sub_418DD0(140) + 20) >> 1;
      sub_491530(2, 0);
      if ( a1[83] != 0 || v19 != v47 )
        goto LABEL_47;
      v21 = v62;
      if ( v62 != 0 )
        break;
LABEL_48:
      v59 = a3;
      v26 = v21 != 0 ? 255 : 120;
      if ( a3 >= v26 )
        v59 = v26;
      v27 = sub_418DD0(138);
      if ( v27 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v27 + 128))(
          v27,
          dword_6C8790[2 * v19],
          dword_6C8794[2 * v19],
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          (v59 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_491630(2);
      v60 = a3;
      if ( a3 >= 255 )
        v60 = -1;
      v28 = sub_418DD0(Value);
      if ( v28 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v28 + 128))(
          v28,
          v55 + dword_6C8790[2 * v19] - v48,
          dword_6C8794[2 * v19] + 3,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          (v60 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      if ( a1[83] == 1 && v19 == v47 )
      {
        v29 = sub_699000((int)(a1 + 2));
        v63 = v29 <= 350;
        if ( v29 <= 350 )
          sub_491530(5, -1);
        Valuea = *v44;
        v30 = v55 + dword_6C8790[2 * v19] - sub_699FC0(*v44) / 2;
        v31 = dword_6C8794[2 * v19] - 10;
        v32 = sub_699000((int)(a1 + 2));
        sub_4049F0(0.0, 40.0, v32, 1000, 0);
        v49 = (uint64_t)a2;
        v33 = sub_699000((int)(a1 + 2));
        a2 = sub_4049C0(637.0, 0.0, v33, 1300);
        v34 = (uint64_t)a2;
        v61 = (uint64_t)a2;
        if ( v61 > 255 )
          LODWORD(v34) = 255;
        v35 = v31 - v49;
        sub_69A110(v30, v35, Valuea, v34);
        v56 = -1;
        if ( v61 <= 255 )
          v56 = v61;
        v50 = *(uint32_t *)(sub_418DD0(172) + 20);
        v36 = sub_418DD0(172);
        if ( v36 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v36 + 128))(
            v36,
            v30 - v50,
            v35,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            (v56 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        if ( v45 != -1 )
        {
          v57 = -1;
          if ( v61 <= 255 )
            v57 = v61;
          v51 = *(uint32_t *)(sub_418DD0(172) + 20);
          Valueb = *(uint32_t *)(sub_418DD0(v45) + 20);
          v37 = sub_418DD0(v45);
          if ( v37 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v37 + 128))(
              v37,
              v30 - v51 - Valueb,
              v35,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              (v57 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
        }
        if ( v63 )
          sub_491630(5);
        if ( sub_699000((int)(a1 + 2)) >= 1000 )
        {
          v41 = a1[1] + 1;
          a1[83] = 0;
          sub_4772A0(v41);
        }
        v19 = v46;
      }
      ++v44;
      result = v43 + 3;
      ++v19;
      v38 = (int)(v43 + 3) < (int)"RESULT_FLASH";
      v46 = v19;
      v42 += 3;
      v43 += 3;
      if ( !v38 )
        return result;
    }
    LOBYTE(v58) = 0;
    v22 = sub_699000((int)(a1 + 2));
    v23 = (int)(a1 + 2);
    if ( v22 > 150 )
    {
      if ( sub_699000(v23) > 250 )
      {
LABEL_43:
        v25 = sub_418DD0(140);
        if ( v25 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v25 + 128))(
            v25,
            v55 + dword_6C8790[2 * v19] - v20,
            dword_6C8794[2 * v19] - 16,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)v58 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        if ( sub_699000((int)(a1 + 2)) >= 250 )
          a1[83] = 1;
LABEL_47:
        v21 = v62;
        goto LABEL_48;
      }
      v24 = sub_699000((int)(a1 + 2)) % 500;
      v40 = 250;
      if ( v24 < 250 )
      {
        a2 = sub_4049C0(255.0, 0.0, v24, 250);
LABEL_42:
        v58 = (uint64_t)a2;
        goto LABEL_43;
      }
      v39 = v24 - 250;
    }
    else
    {
      v40 = 150;
      v39 = sub_699000(v23);
    }
    a2 = sub_4049C0(0.0, 255.0, v39, v40);
    goto LABEL_42;
  }
  result = (uint32_t *)sub_4772A0(a1[1] + 1);
  a1[83] = 0;
  return result;
}


// ------------------------------------------------------------
// 0x477AF0 sub_477AF0
// ------------------------------------------------------------
void /*thiscall*/ sub_477AF0(int this)
{
  int v2; // ecx

  v2 = *(uint32_t *)(this + 48);
  if ( v2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 4))(v2, 1);
  *(uint32_t *)(this + 48) = 0;
  if ( *(uint32_t *)(this + 32) >= 0x10u )
    j__free(*(void **)(this + 12));
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 15;
  *(uint8_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x477B60 CNRDResult__vmt0
// ------------------------------------------------------------
// CNRDResult::vmt0 —— 结算主类帧处理（RTTI 自证）：
// RESULT_CHARACTER + RESULT_SCORE_UP_LOOP(33311) 事件序列（6899 行附近）
char /*userpurge*/ sub_477B60@<al>(int a1@<ecx>, double a2@<st0>, int a3)
{
  int v3; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // edi
  int v8; // eax
  uint8_t v9; // bl
  int v10; // eax
  uint8_t v11; // bl
  int v12; // eax
  double v13; // st7
  int v14; // edi
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // eax
  uint64_t v19; // rax
  int v20; // edi
  uint64_t v21; // rax
  uint32_t *v22; // eax
  int v23; // edi
  int v24; // eax
  int v25; // edi
  int v26; // eax
  int v27; // edi
  int v28; // eax
  int v29; // edi
  int v30; // eax
  int v31; // eax
  uint64_t v32; // rax
  int v33; // edi
  uint64_t v34; // rax
  uint32_t *v35; // eax
  int v36; // edi
  int v37; // eax
  int v38; // edi
  int v39; // eax
  int v40; // edi
  int v41; // eax
  int v42; // edi
  int v43; // eax
  int v44; // eax
  uint64_t v45; // rax
  int v46; // edi
  int v47; // ebx
  int v48; // eax
  int v49; // ecx
  int v50; // eax
  int v51; // eax
  int v52; // eax
  int v53; // eax
  int v54; // eax
  int v55; // eax
  int v56; // eax
  LONG x; // edi
  LONG y; // ebx
  int v59; // esi
  int v60; // eax
  int v61; // eax
  int v62; // eax
  int v63; // eax
  int v64; // eax
  int v66; // [esp-14h] [ebp-28h]
  int v67; // [esp-14h] [ebp-28h]
  int v68; // [esp-14h] [ebp-28h]
  int v69; // [esp-14h] [ebp-28h]
  int v70; // [esp-14h] [ebp-28h]
  int v71; // [esp-14h] [ebp-28h]
  int v72; // [esp-14h] [ebp-28h]
  int v73; // [esp-Ch] [ebp-20h]
  int v74; // [esp-Ch] [ebp-20h]
  int v75; // [esp-Ch] [ebp-20h]
  int v76; // [esp+Ch] [ebp-8h]
  uint8_t v77; // [esp+10h] [ebp-4h]
  float v78; // [esp+1Ch] [ebp+8h]
  int v79; // [esp+1Ch] [ebp+8h]
  int v80; // [esp+1Ch] [ebp+8h]
  int v81; // [esp+1Ch] [ebp+8h]
  float v82; // [esp+1Ch] [ebp+8h]

  LOBYTE(v3) = a3;
  v5 = *(uint32_t *)(a1 + 76);
  if ( a3 == v5 )
  {
    v6 = *(uint32_t *)(a1 + 4);
    if ( v6 >= 2 )
    {
      v7 = 255;
      if ( v6 != 2
        || (v8 = sub_699000(a1 + 8), v7 = (uint64_t)sub_4049C0(0.0, 255.0, v8, 800), v9 = v7, v7 >= 220) )
      {
        v9 = -36;
      }
      v10 = sub_418DD0(33);
      if ( v10 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 128))(
          v10,
          0,
          0,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          (v9 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      a2 = (double)sub_699000(a1 + 92) * 0.000033333334;
      sub_491530(2, 0);
      v11 = v7;
      if ( v7 >= 120 )
        v11 = 120;
      v12 = sub_418DD0(1);
      if ( v12 != 0 )
      {
        v78 = a2;
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v12 + 128))(
          v12,
          111,
          31,
          dword_79C0B0,
          1065353216,
          1065353216,
          LODWORD(v78),
          (v11 << 24) | 0xFFFFFF,
          1129447424,
          1129447424);
      }
      sub_491630(2);
      if ( *(uint32_t *)(a1 + 4) == 16 )
        v7 = *(uint32_t *)(a1 + 312);
      sub_476CA0(v7);
      if ( *(uint32_t *)(a1 + 4) == 2 && sub_699000(a1 + 8) >= 800 )
        goto LABEL_16;
    }
    if ( *(int *)(a1 + 4) >= 3 )
    {
      v13 = COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(a1 + 196) + 976));
      sub_69A110(351, 86, (uint64_t)v13, *(uint32_t *)(a1 + 312));
      v14 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
      v15 = sub_418DD0(24);
      if ( v15 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v15 + 128))(
          v15,
          351,
          84,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v14,
          1333788672,
          1333788672);
      a2 = COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(a1 + 196) + 990));
      sub_69A110(381, 86, (uint64_t)a2, *(uint32_t *)(a1 + 312));
      if ( sub_699000(a1 + 8) >= 800 && *(uint32_t *)(a1 + 4) == 3 )
      {
        sub_432EA0("RESULT_CHARACTER", -1, 0, 0);
        sub_432EA0("RESULT_SCORE_UP_LOOP", 33311, 0, 0);
        LOBYTE(v3) = sub_4772A0(*(uint32_t *)(a1 + 4) + 1);
        return v3;
      }
    }
    if ( *(int *)(a1 + 4) >= 4 )
    {
      v16 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
      v17 = sub_418DD0(14);
      if ( v17 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v17 + 128))(
          v17,
          172,
          141,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v16,
          1333788672,
          1333788672);
      if ( *(int *)(a1 + 4) >= 7 && *(uint8_t *)(a1 + 240) != 0 && sub_699000(a1 + 92) % 2000 < 1000 )
      {
        v73 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
        v18 = sub_418DD0(17);
        sub_43B560(173, 139, v18, 1065353216, 1065353216, 0, v73, 1333788672, 1333788672);
      }
      v19 = (uint64_t)COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(a1 + 196) + 878));
      v20 = sub_476D50(v19, 4, 1.0, 0);
      v21 = (uint64_t)COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(a1 + 196) + 892));
      v79 = (uint64_t)sub_4049C0(0.0, 161.0, v20, v21);
      sub_69A110(312, 142, v20, *(uint32_t *)(a1 + 312));
      v22 = (uint32_t *)dword_79C0B0;
      *(uint32_t *)(dword_79C0B0 + 48) = 0;
      v22[13] = 0;
      v22[14] = v79 + 364;
      v22[15] = 480;
      v23 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
      v24 = sub_418DD0(23);
      if ( v24 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v24 + 128))(
          v24,
          366,
          141,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v23,
          1333788672,
          1333788672);
      sub_488670(dword_79C0B0);
      v25 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
      v26 = sub_418DD0(78);
      if ( v26 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v26 + 128))(
          v26,
          364,
          139,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v25,
          1333788672,
          1333788672);
      a2 = (double)v79 * 0.0062111802 * 100.0;
      sub_69A110(451, 143, (uint64_t)a2, *(uint32_t *)(a1 + 312));
      v27 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
      v28 = sub_418DD0(26);
      if ( v28 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v28 + 128))(
          v28,
          451,
          143,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v27,
          1333788672,
          1333788672);
      if ( sub_699000(a1 + 8) >= 800 && *(uint32_t *)(a1 + 4) == 4 )
        goto LABEL_16;
    }
    if ( *(int *)(a1 + 4) < 5 )
      goto LABEL_53;
    v29 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
    v30 = sub_418DD0(15);
    if ( v30 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v30 + 128))(
        v30,
        172,
        175,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v29,
        1333788672,
        1333788672);
    if ( *(int *)(a1 + 4) >= 7 && *(uint8_t *)(a1 + 241) != 0 && sub_699000(a1 + 92) % 2000 < 1000 )
    {
      v74 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
      v31 = sub_418DD0(17);
      sub_43B560(173, 172, v31, 1065353216, 1065353216, 0, v74, 1333788672, 1333788672);
    }
    v32 = (uint64_t)COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(a1 + 196) + 906));
    v33 = sub_476D50(v32, 5, 1.0, 0);
    v34 = (uint64_t)COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(a1 + 196) + 920));
    v80 = (uint64_t)sub_4049C0(0.0, 161.0, v33, v34);
    sub_69A110(312, 177, v33, *(uint32_t *)(a1 + 312));
    v35 = (uint32_t *)dword_79C0B0;
    *(uint32_t *)(dword_79C0B0 + 48) = 0;
    v35[13] = 0;
    v35[14] = v80 + 364;
    v35[15] = 480;
    v36 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
    v37 = sub_418DD0(23);
    if ( v37 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v37 + 128))(
        v37,
        366,
        174,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v36,
        1333788672,
        1333788672);
    sub_488670(dword_79C0B0);
    v38 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
    v39 = sub_418DD0(78);
    if ( v39 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v39 + 128))(
        v39,
        364,
        172,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v38,
        1333788672,
        1333788672);
    a2 = (double)v80 * 0.0062111802 * 100.0;
    sub_69A110(451, 176, (uint64_t)a2, *(uint32_t *)(a1 + 312));
    v40 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
    v41 = sub_418DD0(26);
    if ( v41 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v41 + 128))(
        v41,
        451,
        176,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v40,
        1333788672,
        1333788672);
    if ( sub_699000(a1 + 8) >= 800 && *(uint32_t *)(a1 + 4) == 5 )
    {
LABEL_16:
      sub_432EA0("RESULT_CHARACTER", -1, 0, 0);
      LOBYTE(v3) = sub_4772A0(*(uint32_t *)(a1 + 4) + 1);
    }
    else
    {
LABEL_53:
      if ( *(int *)(a1 + 4) < 6 )
        goto LABEL_68;
      v42 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
      v43 = sub_418DD0(16);
      if ( v43 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v43 + 128))(
          v43,
          172,
          207,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v42,
          1333788672,
          1333788672);
      if ( *(int *)(a1 + 4) >= 7 && *(uint8_t *)(a1 + 242) != 0 && sub_699000(a1 + 92) % 2000 < 1000 )
      {
        v75 = (*(uint8_t *)(a1 + 312) << 24) | 0xFFFFFF;
        v44 = sub_418DD0(17);
        sub_43B560(173, 205, v44, 1065353216, 1065353216, 0, v75, 1333788672, 1333788672);
      }
      v45 = (uint64_t)COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(a1 + 196) + 948));
      v81 = sub_476D50(v45, 6, 1.0, 0);
      sub_69A110(312, 209, v81, *(uint32_t *)(a1 + 312));
      if ( *(uint32_t *)(a1 + 4) == 6 && COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(a1 + 196) + 948)) == (double)v81 )
        sub_432EE0(33311);
      a2 = (double)sub_699000(a1 + 8);
      if ( a2 >= 1200.0 && *(uint32_t *)(a1 + 4) == 6 )
      {
        sub_4772A0(7);
        if ( (uint8_t)sub_476EC0(a1) != 0 )
        {
          sub_476EE0(a1);
          LOBYTE(v3) = (uint8_t)sub_432EA0("RESULT_RANK1", -1, 0, 0);
        }
        else
        {
          LOBYTE(v3) = (uint8_t)sub_432EA0("RESULT_RANK2", -1, 0, 0);
        }
      }
      else
      {
LABEL_68:
        v46 = *(uint32_t *)(a1 + 4);
        if ( v46 < 7 )
          goto LABEL_100;
        v82 = 1.0;
        v47 = 255;
        if ( *(int *)(a1 + 204) > 0 && v46 == 9
          || *(int *)(a1 + 208) > 0 && v46 == 10
          || *(int *)(a1 + 212) > 0 && v46 == 11 )
        {
          v46 = *(uint32_t *)(a1 + 4);
          a2 = (double)(unsigned int)(sub_699000(a1 + 92) - *(uint32_t *)(a1 + 4 * v46 + 120)) * 0.0040000002;
          *(float *)(a1 + 308) = a2;
        }
        if ( v46 == 7 )
        {
          v48 = sub_495C80(*(uint32_t *)(a1 + 196));
          v49 = a1 + 8;
          if ( v48 < 55 )
          {
            if ( sub_699000(v49) < 800 )
            {
              v51 = sub_699000(a1 + 8);
              v47 = sub_423A80(0, 255, v51, 800);
            }
          }
          else if ( sub_699000(v49) < 300 )
          {
            v50 = sub_699000(a1 + 8);
            sub_4049F0(3.0, 1.0, v50, 300, 1);
            v82 = a2;
          }
        }
        if ( *(uint32_t *)(a1 + 4) == 16 )
          v47 = *(uint32_t *)(a1 + 312);
        sub_476F50(a1, a2);
        sub_491530(2, 0);
        v77 = v47;
        if ( v47 >= 200 )
          v77 = -56;
        v76 = *(uint32_t *)(a1 + 308);
        v52 = sub_418DD0(2);
        if ( v52 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, int, int, int, int))(*(uint32_t *)v52 + 128))(
            v52,
            71,
            245,
            dword_79C0B0,
            1065353216,
            1065353216,
            v76,
            (v77 << 24) | 0xFFFFFF,
            1122107392,
            1122107392);
        sub_491630(2);
        v53 = sub_476DD0(a1);
        v54 = sub_418DD0(v53);
        if ( v54 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, float, float, uint32_t, int, int, int))(*(uint32_t *)v54 + 156))(
            v54,
            116,
            289,
            dword_79C0B0,
            COERCE_FLOAT(LODWORD(v82)),
            COERCE_FLOAT(LODWORD(v82)),
            0,
            ((uint8_t)v47 << 24) | 0xFFFFFF,
            1116471296,
            1116602368);
        v55 = sub_418DD0(13);
        if ( v55 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v55 + 128))(
            v55,
            232,
            324,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)v47 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        if ( v47 == 255 )
        {
          a2 = 1.0;
          if ( v82 == 1.0 && *(uint32_t *)(a1 + 188) == 0xFFFF )
            *(uint32_t *)(a1 + 188) = sub_699000(a1 + 8) + 1000;
        }
        if ( *(uint32_t *)(a1 + 4) != 7
          || *(uint32_t *)(a1 + 188) == 0xFFFF
          || (unsigned int)sub_699000(a1 + 8) < *(uint32_t *)(a1 + 188) )
        {
LABEL_100:
          v3 = *(uint32_t *)(a1 + 4);
          if ( v3 >= 8 )
            LOBYTE(v3) = (uint8_t)sub_4773E0((int *)a1, a2, *(uint32_t *)(a1 + 312));
          if ( *(int *)(a1 + 4) >= 16 )
          {
            if ( sub_699000(a1 + 8) <= 2000 )
            {
              if ( (uint8_t)sub_477240(a1) != 0 )
                sub_477060((uint32_t *)a1);
            }
            else
            {
              v56 = sub_699000(a1 + 8);
              *(uint32_t *)(a1 + 312) = sub_423A80(255, 0, v56, 2800);
            }
            v3 = sub_699000(a1 + 8);
            if ( v3 >= 3000 && *(uint32_t *)(a1 + 4) == 16 )
            {
              LOBYTE(v3) = *(uint8_t *)(a1 + 328);
              if ( (uint8_t)v3 == 0 )
              {
                sub_423200(dword_8F7B08, 72);
                LOBYTE(v3) = sub_423380(dword_8F7B08);
                *(uint8_t *)(a1 + 328) = 1;
              }
            }
          }
        }
        else
        {
          LOBYTE(v3) = sub_4772A0(*(uint32_t *)(a1 + 4) + 1);
          *(uint32_t *)(a1 + 332) = 0;
        }
      }
    }
  }
  else if ( a3 == *(uint32_t *)(a1 + 80) )
  {
    LOBYTE(v3) = sub_43BCB0(v5);
    if ( (uint8_t)v3 != 0 )
    {
      x = pt.x;
      y = pt.y;
      if ( pt.x >= 105 && pt.x <= 528 )
      {
        if ( pt.y < 77 || pt.y > 121 )
        {
          if ( pt.y < 134 || pt.y > 165 )
          {
            if ( pt.y < 167 || pt.y > 198 )
            {
              if ( pt.y >= 200 && pt.y <= 231 )
              {
                v69 = sub_422E70(468);
                LOBYTE(v3) = sub_4649B0(320, 200, -1, -16777216, 2, v69, 0, 0, 1600, 0);
              }
            }
            else
            {
              v68 = sub_422E70(467);
              LOBYTE(v3) = sub_4649B0(320, 167, -1, -16777216, 2, v68, 0, 0, 1600, 0);
            }
          }
          else
          {
            v67 = sub_422E70(466);
            LOBYTE(v3) = sub_4649B0(320, 134, -1, -16777216, 2, v67, 0, 0, 1600, 0);
          }
        }
        else
        {
          v66 = sub_422E70(465);
          LOBYTE(v3) = sub_4649B0(320, 77, -1, -16777216, 2, v66, 0, 0, 1600, 0);
        }
      }
      v59 = *(uint32_t *)(a1 + 4);
      if ( v59 < 7 || x < 73 || x > 294 || y < 236 || y > 458 )
      {
        if ( v59 >= 8 )
        {
          if ( x < 329 || x > 531 || y < 403 || y > 432 )
          {
            if ( x < 312 || x > 412 || y < 292 || y > 322 )
            {
              if ( x < 424 || x > 524 || y < 292 || y > 322 )
              {
                if ( x < 312 || x > 412 || y < 328 || y > 358 )
                {
                  if ( x < 424 || x > 524 || y < 328 || y > 358 )
                  {
                    if ( x < 312 || x > 412 || y < 364 || y > 394 )
                    {
                      if ( x >= 424 && x <= 524 && y >= 364 && y <= 394 )
                      {
                        v72 = sub_422E70(1608);
                        LOBYTE(v3) = sub_4649B0(424, 364, -1, -16777216, 2, v72, 0, 0, 1600, 0);
                      }
                    }
                    else
                    {
                      v64 = sub_422E70(1246);
                      LOBYTE(v3) = sub_4649B0(312, 364, -1, -16777216, 2, v64, 0, 0, 1600, 0);
                    }
                  }
                  else
                  {
                    v71 = sub_422E70(1206);
                    LOBYTE(v3) = sub_4649B0(424, 328, -1, -16777216, 2, v71, 0, 0, 1600, 0);
                  }
                }
                else
                {
                  v63 = sub_422E70(473);
                  LOBYTE(v3) = sub_4649B0(312, 328, -1, -16777216, 2, v63, 0, 0, 1600, 0);
                }
              }
              else
              {
                v70 = sub_422E70(472);
                LOBYTE(v3) = sub_4649B0(424, 292, -1, -16777216, 2, v70, 0, 0, 1600, 0);
              }
            }
            else
            {
              v62 = sub_422E70(471);
              LOBYTE(v3) = sub_4649B0(312, 292, -1, -16777216, 2, v62, 0, 0, 1600, 0);
            }
          }
          else
          {
            v61 = sub_422E70(470);
            LOBYTE(v3) = sub_4649B0(329, 403, -1, -16777216, 2, v61, 0, 0, 1600, 0);
          }
        }
      }
      else
      {
        v60 = sub_422E70(469);
        LOBYTE(v3) = sub_4649B0(183, 278, -1, -16777216, 2, v60, 0, 0, 1600, 0);
      }
    }
  }
  return v3;
}


// ============================================================
// 【分区 8】社交管理器 I（0x478C70-0x47B000）
// CNRDFriendManager__vmt4/vmt8、CNRDMemberManager__vmt4/vmt8（RTTI 自证）。
// ============================================================
// ------------------------------------------------------------
// 0x478C70 sub_478C70
// ------------------------------------------------------------
char /*thiscall*/ sub_478C70(int *this, void *Block, int a3)
{
  uint8_t *v4; // eax
  int v5; // ebx
  uint8_t *v6; // eax
  uint8_t *v7; // eax
  uint8_t *v8; // eax
  uint32_t *v9; // esi
  int v10; // ecx
  int v11; // edx
  int v13; // [esp-4h] [ebp-9Ch]
  uint32_t v14[10]; // [esp+Ch] [ebp-8Ch]
  uint32_t v15[10]; // [esp+34h] [ebp-64h]
  void *v16[11]; // [esp+5Ch] [ebp-3Ch]
  int v17; // [esp+88h] [ebp-10h]
  int v18; // [esp+94h] [ebp-4h]
  char *Blocka; // [esp+A0h] [ebp+8h]
  int v20; // [esp+A4h] [ebp+Ch]

  *(this + 48) = (int)Block;
  *(this + 49) = a3;
  *(this + 21) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 64);
  *(this + 22) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 88);
  v4 = operator new(0x68u);
  v5 = 0;
  v18 = 0;
  if ( v4 != nullptr )
    v6 = sub_426BD0(v4);
  else
    v6 = nullptr;
  *(this + 19) = (int)v6;
  *((uint32_t *)v6 + 7) = 640;
  *((uint32_t *)v6 + 8) = 480;
  *(uint32_t *)(*(this + 19) + 68) = this;
  v7 = operator new(0x68u);
  v18 = 1;
  if ( v7 != nullptr )
    v8 = sub_426BD0(v7);
  else
    v8 = nullptr;
  *(this + 20) = (int)v8;
  *((uint32_t *)v8 + 17) = this;
  v13 = *(this + 20);
  v18 = -1;
  sub_69A840(v13);
  v16[0] = (void *)26;
  v16[5] = (void *)26;
  v15[0] = -5;
  v15[1] = -5;
  v15[2] = -5;
  v15[4] = -5;
  v15[5] = -5;
  v15[6] = -2;
  v15[7] = -2;
  v15[8] = -4;
  v15[9] = -4;
  v16[1] = (void *)36;
  v16[2] = (void *)57;
  v16[3] = (void *)67;
  v16[4] = (void *)46;
  v16[6] = (void *)91;
  v16[7] = (void *)102;
  v16[8] = (void *)150;
  v16[9] = (void *)161;
  v15[3] = -3;
  v14[0] = 2;
  v14[1] = 2;
  v14[2] = 2;
  v14[3] = 2;
  v14[4] = 2;
  v14[5] = 0;
  v14[6] = 2;
  v14[7] = 2;
  v14[8] = 2;
  v14[9] = 0;
  Blocka = (char *)(this + 9);
  do
  {
    v9 = operator new(0x2Cu);
    v16[10] = v9;
    v18 = 2;
    if ( v9 != nullptr )
    {
      v20 = *(this + 21);
      v17 = dword_79C0B0;
      *((uint8_t *)v9 + 4) = 0;
      LOBYTE(v18) = 3;
      *v9 = &vftbl_nengine__CNNumberSet;
      sub_699E20(v9);
      sub_699E40(v17, v20, v16[v5], 7);
    }
    else
    {
      v9 = nullptr;
    }
    v10 = v15[v5];
    *(uint32_t *)Blocka = v9;
    v9[10] = v10;
    *(uint32_t *)(*(uint32_t *)Blocka + 36) = v14[v5];
    v11 = *(uint32_t *)Blocka;
    ++v5;
    v18 = -1;
    *(uint8_t *)(v11 + 24) = 0;
    Blocka += 4;
  }
  while ( v5 < 10 );
  sub_698F90((int)(this + 23), 0, 0);
  return sub_4772A0((int)this, 0);
}



// ------------------------------------------------------------
// 0x478EA0 sub_478EA0
// ------------------------------------------------------------
char /*thiscall*/ sub_478EA0(int this, int a2)
{
  int v3; // eax

  if ( a2 == 1 )
  {
    *(uint32_t *)(this + 60) = 0;
    *(uint32_t *)(this + 56) = 0;
  }
  if ( (*(uint32_t *)(this + 60) != 1 || (v3 = sub_699000(this + 92)) >= 10000)
    && (*(uint32_t *)(this + 56) != 1 || (v3 = sub_699000(this + 64)) >= 3000) )
  {
    sub_423200(dword_8F7B08, 70);
    sub_423380(dword_8F7B08);
    *(uint32_t *)(this + 56) = 1;
    *(uint8_t *)(this + 77) = 0;
    *(uint8_t *)(this + 78) = 0;
    LOBYTE(v3) = sub_698F90(this + 64, 0, 0);
  }
  return v3;
}



// ------------------------------------------------------------
// 0x478F20 sub_478F20
// ------------------------------------------------------------
char /*thiscall*/ sub_478F20(int this)
{
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 1;
  *(uint8_t *)(this + 77) = 0;
  *(uint8_t *)(this + 78) = 0;
  return sub_698F90(this + 92, 0, 0);
}



// ------------------------------------------------------------
// 0x478F40 sub_478F40
// ------------------------------------------------------------
char /*thiscall*/ sub_478F40(int this, int a2)
{
  int v3; // eax

  if ( a2 == 1 )
  {
    *(uint32_t *)(this + 52) = 0;
    *(uint32_t *)(this + 48) = 0;
  }
  if ( (*(uint32_t *)(this + 52) != 1 || (v3 = sub_699000(this + 84)) >= 10000)
    && (*(uint32_t *)(this + 48) != 1 || (v3 = sub_699000(this + 56)) >= 3000) )
  {
    sub_423200(dword_8F7B08, 82);
    sub_423380(dword_8F7B08);
    *(uint32_t *)(this + 48) = 1;
    *(uint8_t *)(this + 69) = 0;
    *(uint8_t *)(this + 70) = 0;
    LOBYTE(v3) = sub_698F90(this + 56, 0, 0);
  }
  return v3;
}



// ------------------------------------------------------------
// 0x478FC0 sub_478FC0
// ------------------------------------------------------------
char /*thiscall*/ sub_478FC0(int this)
{
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 1;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  return sub_698F90(this + 84, 0, 0);
}



// ------------------------------------------------------------
// 0x478FE0 sub_478FE0
// ------------------------------------------------------------
int /*thiscall*/ sub_478FE0(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 180;
  return result;
}



// ------------------------------------------------------------
// 0x479010 sub_479010
// ------------------------------------------------------------
int /*cdecl*/ sub_479010(int a1)
{
  int result; // eax
  int i; // ecx

  result = a1;
  for ( i = *(uint32_t *)(a1 + 8); *(uint8_t *)(i + 49) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x479030 sub_479030
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_479030(uint32_t *a1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = a1;
  v2 = (int *)*a1;
  if ( *(uint8_t *)(*a1 + 49) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 49) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x479050 sub_479050
// ------------------------------------------------------------
int /*thiscall*/ sub_479050(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 49) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 49) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 49) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 49) == 0 );
        if ( *(uint8_t *)(result + 49) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 49) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4790B0 sub_4790B0
// ------------------------------------------------------------
int */*thiscall*/ sub_4790B0(int *this)
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 49) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 49) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 49) == 0; result = (int *)result[1] )
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
      if ( *(uint8_t *)(*v2 + 49) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 49) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x479110 sub_479110
// ------------------------------------------------------------
int /*thiscall*/ sub_479110(int *this)
{
  int result; // eax

  result = *(this + 2);
  if ( result != 0 )
    return (*(this + 3) - result) / 180;
  return result;
}



// ------------------------------------------------------------
// 0x479140 sub_479140
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_479140(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  int v3; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(a2 + 8);
  *(uint32_t *)(a2 + 8) = *result;
  if ( *(uint8_t *)(*result + 49) == 0 )
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
// 0x4791A0 sub_4791A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4791A0(uint32_t *this, uint32_t *a2)
{
  int result; // eax
  int v3; // esi
  int v4; // ecx
  uint32_t *v5; // ecx

  result = *a2;
  *a2 = *(uint32_t *)(*a2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 49) == 0 )
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
// 0x479200 sub_479200
// ------------------------------------------------------------
uint32_t *sub_479200()
{
  uint32_t *result; // eax

  result = operator new(0x34u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 48) = 1;
  *((uint8_t *)result + 49) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x479240 sub_479240
// ------------------------------------------------------------
int /*thiscall*/ sub_479240(uint32_t *this, unsigned int a2)
{
  int v2; // eax

  v2 = *(this + 2);
  if ( v2 != 0 && a2 < (*(this + 3) - v2) / 180 )
    return *(this + 2) + 180 * a2;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x479290 sub_479290
// ------------------------------------------------------------
int /*thiscall*/ sub_479290(uint32_t *this, const char *a2)
{
  unsigned int v3; // ecx
  int v4; // eax
  int v5; // eax
  unsigned int v6; // edx
  int v7; // eax
  const char *v8; // eax
  int i; // [esp+Ch] [ebp-4h]

  v3 = 0;
  for ( i = 0; ; i += 180 )
  {
    v4 = *(this + 2);
    if ( v4 == 0 || v3 >= (*(this + 3) - v4) / 180 )
      break;
    v5 = *(this + 2);
    v6 = *(uint32_t *)(v5 + i + 24);
    v7 = i + v5;
    if ( v6 < 0x10 )
      v8 = (const char *)(v7 + 4);
    else
      v8 = *(const char **)(v7 + 4);
    if ( strcmp(v8, a2) == 0 )
      return v3;
    ++v3;
  }
  return -1;
}



// ------------------------------------------------------------
// 0x479340 CNRDFriendManager__vmt4
// ------------------------------------------------------------
// CNRDFriendManager::vmt4 好友管理帧处理（RTTI 自证）
int /*thiscall*/ CNRDFriendManager__vmt4(uint32_t *this, const char *a2)
{
  int v2; // eax
  char *v3; // eax

  v2 = *(this + 2);
  if ( v2 != 0 && (unsigned int)((*(this + 3) - v2) / 180) >= 0x20 )
  {
    v3 = sub_422E70(396);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);
  }
  if ( sub_479290(this, a2) > 0 )
  {
    v3 = sub_422E70(397);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);
  }
  sub_423200(dword_8F7B08, 63);
  sub_41C100(a2);
  return sub_423380(dword_8F7B08);
}



// ------------------------------------------------------------
// 0x4793D0 CNRDFriendManager__vmt8
// ------------------------------------------------------------
// CNRDFriendManager::vmt8（RTTI 自证）
int /*thiscall*/ CNRDFriendManager__vmt8(uint32_t *this, const char *a2)
{
  char *v2; // eax

  if ( sub_479290(this, a2) == -1 )
  {
    v2 = sub_422E70(398);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);
  }
  else
  {
    sub_423200(dword_8F7B08, 64);
    sub_41C100(a2);
    return sub_423380(dword_8F7B08);
  }
}



// ------------------------------------------------------------
// 0x479430 CNRDMemberManager__vmt4
// ------------------------------------------------------------
// CNRDMemberManager::vmt4 会员管理帧处理（RTTI 自证）
int /*thiscall*/ CNRDMemberManager__vmt4(uint32_t *this, const char *a2)
{
  char *v2; // eax

  if ( sub_479290(this, a2) < 0 )
  {
    sub_423200(dword_8F7B08, 79);
    sub_41C100(a2);
    return sub_423380(dword_8F7B08);
  }
  else
  {
    v2 = sub_422E70(1522);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);
  }
}



// ------------------------------------------------------------
// 0x479490 CNRDMemberManager__vmt8
// ------------------------------------------------------------
// CNRDMemberManager::vmt8（RTTI 自证）
int /*thiscall*/ CNRDMemberManager__vmt8(uint32_t *this, const char *a2)
{
  char *v2; // eax

  if ( sub_479290(this, a2) == -1 )
  {
    v2 = sub_422E70(1523);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);
  }
  else
  {
    sub_423200(dword_8F7B08, 81);
    sub_41C100(a2);
    return sub_423380(dword_8F7B08);
  }
}



// ------------------------------------------------------------
// 0x4794F0 sub_4794F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4794F0(uint32_t *this, const char *a2, uint8_t a3)
{
  int result; // eax

  result = sub_479290(this, a2);
  if ( result >= 0 )
  {
    result = *(this + 2) + 180 * result;
    if ( result != 0 )
      *(uint32_t *)(result + 40) = a3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x479520 sub_479520
// ------------------------------------------------------------
int /*thiscall*/ sub_479520(uint32_t *this, const char *a2)
{
  int result; // eax

  result = sub_479290(this, a2);
  if ( result >= 0 )
  {
    result = *(this + 2) + 180 * result;
    if ( result != 0 )
      *(uint32_t *)(result + 40) = -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x479550 sub_479550
// ------------------------------------------------------------
int */*thiscall*/ sub_479550(int **this, int a2)
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
  if ( *((uint8_t *)v3 + 49) == 0 )
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
      if ( *((uint8_t *)v3 + 49) != 0 )
        return v16;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x479610 sub_479610
// ------------------------------------------------------------
int **/*thiscall*/ sub_479610(int **this, int **a2, unsigned int *a3)
{
  int *v5; // eax
  unsigned int v6; // ecx
  const char *v7; // eax
  int *v9; // [esp+18h] [ebp+Ch]

  v5 = sub_479550(this, (int)a3);
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
// 0x479680 sub_479680
// ------------------------------------------------------------
void /*noreturn*/ sub_479680()
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
// 0x4796F0 sub_4796F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4796F0(int this, uint32_t *a2)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((std::_String_base *)this, a2, 0, -1);
  *(uint32_t *)(this + 28) = a2[7];
  *(uint32_t *)(this + 32) = a2[8];
  *(uint32_t *)(this + 36) = a2[9];
  *(uint32_t *)(this + 40) = a2[10];
  *(uint32_t *)(this + 44) = a2[11];
  *(uint32_t *)(this + 48) = a2[12];
  qmemcpy((void *)(this + 52), a2 + 13, 0x80u);
  return this;
}



// ------------------------------------------------------------
// 0x479750 sub_479750
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_479750(char *a1, char *a2, uint32_t *a3)
{
  char *v3; // edi
  uint32_t *v4; // esi
  uint8_t *v5; // eax
  int i; // edx

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    sub_4014D0((std::_String_base *)v4, v3, 0, -1);
    v4[7] = *((uint32_t *)v3 + 7);
    v4[8] = *((uint32_t *)v3 + 8);
    v4[9] = *((uint32_t *)v3 + 9);
    v4[10] = *((uint32_t *)v3 + 10);
    v4[11] = *((uint32_t *)v3 + 11);
    v4[12] = *((uint32_t *)v3 + 12);
    v5 = v4 + 13;
    for ( i = 128; i != 0; --i )
    {
      *v5 = v5[v3 - (char *)v4];
      ++v5;
    }
    v3 += 180;
    v4 += 45;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x4797D0 sub_4797D0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4797D0(char *a1, char *a2, uint32_t *a3)
{
  char *v3; // edi
  uint32_t *v4; // esi
  uint8_t *v5; // eax
  int i; // edx

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v3 -= 180;
    v4 -= 45;
    sub_4014D0((std::_String_base *)v4, v3, 0, -1);
    v4[7] = *((uint32_t *)v3 + 7);
    v4[8] = *((uint32_t *)v3 + 8);
    v4[9] = *((uint32_t *)v3 + 9);
    v4[10] = *((uint32_t *)v3 + 10);
    v4[11] = *((uint32_t *)v3 + 11);
    v4[12] = *((uint32_t *)v3 + 12);
    v5 = v4 + 13;
    for ( i = 128; i != 0; --i )
    {
      *v5 = v5[v3 - (char *)v4];
      ++v5;
    }
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x479850 sub_479850
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_479850(unsigned int *this)
{
  int v1; // eax
  unsigned int result; // eax
  int v4; // esi
  unsigned int v5; // eax
  char *v6; // esi
  const char *v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // [esp+Ch] [ebp-8h]
  unsigned int i; // [esp+10h] [ebp-4h]

  v1 = 0;
  for ( i = 0; ; ++i )
  {
    v10 = v1;
    result = *(this + 2);
    if ( result == 0 )
      break;
    result = (int)(*(this + 3) - result) / 180;
    if ( i >= result )
      break;
    v4 = *(this + 2);
    v5 = *(uint32_t *)(v4 + v10 + 24);
    v6 = (char *)(v10 + v4);
    if ( v5 < 0x10 )
      v7 = v6 + 4;
    else
      v7 = *((const char **)v6 + 1);
    v8 = sub_429870((int **)dword_8F8500, v7);
    *((uint32_t *)v6 + 12) = v8;
    if ( v8 != 0 )
    {
      v9 = v8 + 16;
      sub_4014D0((std::_String_base *)v6, v8 + 16, 0, -1);
      *((uint32_t *)v6 + 7) = sub_41A5E0(v9 + 37);
      *((uint32_t *)v6 + 8) = *(uint32_t *)(v9 + 28);
      *((uint32_t *)v6 + 9) = *(uint32_t *)(v9 + 32);
    }
    v1 = v10 + 180;
  }
  return result;
}



// ------------------------------------------------------------
// 0x479900 sub_479900
// ------------------------------------------------------------
int ***/*thiscall*/ sub_479900(uint32_t *this, int ***a2, int **a3)
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
  void **v15; // eax
  uint32_t *v16; // ecx
  uint32_t *v17; // eax
  uint32_t *v18; // eax
  int v19; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  size_t v22; // [esp+34h] [ebp-34h] BYREF
  char v23; // [esp+38h] [ebp-30h]
  int v24; // [esp+48h] [ebp-20h]
  int v25; // [esp+4Ch] [ebp-1Ch]
  int v26; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *v28; // [esp+58h] [ebp-10h]
  int v29; // [esp+64h] [ebp-4h]

  v28 = this;
  if ( *((uint8_t *)a3 + 49) != 0 )
  {
    v25 = 15;
    v24 = 0;
    v23 = 0;
    sub_4015C0(&v22, "invalid map/set<T> iterator", 0x1Bu);
    v29 = 0;
    sub_401740(pExceptionObject, &v22);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_4790B0(&a3);
  if ( *((uint8_t *)*v3 + 49) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 49) == 0 )
      v4[1] = (int)v6;
    v7 = v28;
    v8 = v28[1];
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
      if ( *((uint8_t *)v4 + 49) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_479030(v4);
        v7 = v28;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v26 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 49) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v26 + 8) = sub_479010(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)v3[2] + 49) != 0 )
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
    if ( *((uint8_t *)v4 + 49) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)v3[2];
    v3[2][1] = (int)v5;
  }
  v12 = v28[1];
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
  v14 = *((uint8_t *)v5 + 48);
  *((uint8_t *)v5 + 48) = *((uint8_t *)v3 + 48);
  *((uint8_t *)v3 + 48) = v14;
LABEL_35:
  v15 = (void **)Block;
  if ( *((uint8_t *)Block + 48) == 1 )
  {
    v16 = v28;
    if ( v4 != *(int **)(v28[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 48) != 1 )
          break;
        v17 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v17 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v17 + 48) == 0 )
          {
            *((uint8_t *)v17 + 48) = 1;
            *((uint8_t *)v6 + 48) = 0;
            sub_479140(v6);
            v17 = (uint32_t *)v6[2];
            v16 = v28;
          }
          if ( *((uint8_t *)v17 + 49) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v17 + 48) != 1 || *(uint8_t *)(v17[2] + 48) != 1 )
          {
            if ( *(uint8_t *)(v17[2] + 48) == 1 )
            {
              *(uint8_t *)(*v17 + 48) = 1;
              *((uint8_t *)v17 + 48) = 0;
              sub_4791A0(v17);
              v17 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v17 + 48) = *((uint8_t *)v6 + 48);
            *((uint8_t *)v6 + 48) = 1;
            *(uint8_t *)(v17[2] + 48) = 1;
            sub_479140(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v17 + 48) == 0 )
          {
            *((uint8_t *)v17 + 48) = 1;
            *((uint8_t *)v6 + 48) = 0;
            sub_4791A0(v6);
            v17 = (uint32_t *)*v6;
            v16 = v28;
          }
          if ( *((uint8_t *)v17 + 49) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v17[2] + 48) != 1 || *(uint8_t *)(*v17 + 48) != 1 )
          {
            if ( *(uint8_t *)(*v17 + 48) == 1 )
            {
              *(uint8_t *)(v17[2] + 48) = 1;
              *((uint8_t *)v17 + 48) = 0;
              sub_479140(v17);
              v17 = (uint32_t *)*v6;
            }
            *((uint8_t *)v17 + 48) = *((uint8_t *)v6 + 48);
            *((uint8_t *)v6 + 48) = 1;
            *(uint8_t *)(*v17 + 48) = 1;
            sub_4791A0(v6);
            break;
          }
        }
        *((uint8_t *)v17 + 48) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(v16[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    v15 = (void **)Block;
    *((uint8_t *)v4 + 48) = 1;
  }
  if ( (unsigned int)v15[9] >= 0x10 )
    j__free(v15[4]);
  v18 = Block;
  *((uint32_t *)Block + 9) = 15;
  v18[8] = 0;
  *((uint8_t *)v18 + 16) = 0;
  j__free(v18);
  v19 = v28[2];
  if ( v19 != 0 )
    v28[2] = v19 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x479BE0 sub_479BE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_479BE0(uint32_t *this, int a2, int a3, int a4, int a5, char a6)
{
  char *v7; // edi

  *(this + 1) = a3;
  v7 = (char *)(this + 3);
  *this = a2;
  *(this + 2) = a4;
  *(this + 9) = 15;
  *(this + 8) = 0;
  *((uint8_t *)this + 16) = 0;
  sub_4014D0((std::_String_base *)(this + 3), a5, 0, -1);
  *((uint32_t *)v7 + 7) = *(uint32_t *)(a5 + 28);
  *((uint32_t *)v7 + 8) = *(uint32_t *)(a5 + 32);
  *((uint8_t *)this + 48) = a6;
  *((uint8_t *)this + 49) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x479C40 sub_479C40
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_479C40(uint32_t *a1, uint32_t *a2, char *a3)
{
  uint32_t *result; // eax
  uint32_t *v4; // esi
  int v5; // ebx
  uint8_t *v6; // eax
  int i; // ecx

  result = a2;
  v4 = a1;
  if ( a1 != a2 )
  {
    v5 = a3 - (char *)a1;
    do
    {
      sub_4014D0((std::_String_base *)v4, a3, 0, -1);
      v4[7] = *((uint32_t *)a3 + 7);
      v4[8] = *((uint32_t *)a3 + 8);
      v4[9] = *((uint32_t *)a3 + 9);
      v4[10] = *((uint32_t *)a3 + 10);
      v4[11] = *((uint32_t *)a3 + 11);
      v4[12] = *((uint32_t *)a3 + 12);
      v6 = v4 + 13;
      for ( i = 128; i != 0; --i )
      {
        *v6 = v6[v5];
        ++v6;
      }
      result = a2;
      v4 += 45;
      v5 -= 180;
    }
    while ( v4 != a2 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x479CC0 sub_479CC0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_479CC0(char *a1, char *a2, uint32_t *a3)
{
  return sub_4797D0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x479CE0 sub_479CE0
// ------------------------------------------------------------
int /*cdecl*/ sub_479CE0(uint32_t *a1, uint32_t *a2, int a3)
{
  int v3; // ebx
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
    if ( v3 != 0 )
    {
      *(uint32_t *)(v3 + 24) = 15;
      *(uint32_t *)(v3 + 20) = 0;
      *(uint8_t *)(v3 + 4) = 0;
      sub_4014D0((std::_String_base *)v3, a1, 0, -1);
      *(uint32_t *)(v3 + 28) = a1[7];
      *(uint32_t *)(v3 + 32) = a1[8];
      *(uint32_t *)(v3 + 36) = a1[9];
      *(uint32_t *)(v3 + 40) = a1[10];
      *(uint32_t *)(v3 + 44) = a1[11];
      *(uint32_t *)(v3 + 48) = a1[12];
      qmemcpy((void *)(v3 + 52), a1 + 13, 0x80u);
      v4 = a1;
    }
    v3 += 180;
    LOBYTE(v7) = 0;
    a1 = v4 + 45;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x479DF0 sub_479DF0
// ------------------------------------------------------------
int /*thiscall*/ sub_479DF0(int this, void *Src, int a3, int a4, int a5, int a6, int a7)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4015C0((void *)szPassword, 0);
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 4;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 40) = -1;
  *(uint8_t *)(this + 52) = 0;
  sub_4015C0(Src, strlen((const char *)Src));
  *(uint32_t *)(this + 28) = a3;
  *(uint32_t *)(this + 32) = a4;
  *(uint32_t *)(this + 48) = a7;
  *(uint32_t *)(this + 44) = a6;
  *(uint8_t *)(this + 52) = 0;
  *(uint32_t *)(this + 36) = a5;
  *(uint32_t *)(this + 40) = -1;
  return this;
}



// ------------------------------------------------------------
// 0x479EA0 sub_479EA0
// ------------------------------------------------------------
char /*stdcall*/ sub_479EA0(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 49);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_479EA0(i[2]);
    i = (void **)*i;
    sub_5014C0(v1);
    j__free(v1);
    result = *((uint8_t *)i + 49);
  }
  return result;
}



// ------------------------------------------------------------
// 0x479EF0 sub_479EF0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_479EF0(int a1, int a2, int a3, int a4, char a5)
{
  uint32_t *v5; // esi
  void *v7[9]; // [esp+0h] [ebp-24h] BYREF

  v7[5] = v7;
  v5 = operator new(0x34u);
  v7[4] = v5;
  v7[8] = (void *)1;
  v7[3] = v5;
  if ( v5 != nullptr )
    sub_479BE0(v5, a1, a2, a3, a4, a5);
  return v5;
}



// ------------------------------------------------------------
// 0x479F80 sub_479F80
// ------------------------------------------------------------
int /*cdecl*/ sub_479F80(int a1, int a2, uint32_t *a3)
{
  int v3; // ebx
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
      *(uint32_t *)(v3 + 24) = 15;
      *(uint32_t *)(v3 + 20) = 0;
      *(uint8_t *)(v3 + 4) = 0;
      sub_4014D0((std::_String_base *)v3, a3, 0, -1);
      *(uint32_t *)(v3 + 28) = a3[7];
      *(uint32_t *)(v3 + 32) = a3[8];
      *(uint32_t *)(v3 + 36) = a3[9];
      *(uint32_t *)(v3 + 40) = a3[10];
      *(uint32_t *)(v3 + 44) = a3[11];
      *(uint32_t *)(v3 + 48) = a3[12];
      qmemcpy((void *)(v3 + 52), a3 + 13, 0x80u);
    }
    v3 += 180;
    LOBYTE(v6) = 0;
    --a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47A090 sub_47A090
// ------------------------------------------------------------
void /*stdcall*/ sub_47A090(char *a1, char *a2)
{
  char *i; // esi

  for ( i = a1; i != a2; i += 180 )
    sub_501490(i);
}



// ------------------------------------------------------------
// 0x47A0C0 sub_47A0C0
// ------------------------------------------------------------
int /*thiscall*/ sub_47A0C0(int this)
{
  char *v2; // esi
  int result; // eax
  char *i; // edi

  v2 = *(char **)(this + 4);
  result = 0;
  if ( v2 != nullptr )
  {
    for ( i = *(char **)(this + 8); v2 != i; v2 += 180 )
      sub_501490(v2);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x47A110 sub_47A110
// ------------------------------------------------------------
int */*thiscall*/ sub_47A110(int **this, int *a2, int a3, int a4)
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
    sub_479EA0(*(void ***)(v7 + 4));
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
        if ( *(uint8_t *)(v5 + 49) == 0 )
        {
          v11 = *(uint32_t *)(v5 + 8);
          if ( *(uint8_t *)(v11 + 49) != 0 )
          {
            for ( i = *(uint32_t *)(v5 + 4); *(uint8_t *)(i + 49) == 0; i = *(uint32_t *)(i + 4) )
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
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 49) == 0; j = *(uint32_t *)j )
              v5 = j;
          }
        }
        sub_479900(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x47A1D0 sub_47A1D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47A1D0(int *this, uint32_t *a2, char a3, uint32_t *a4, int a5)
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

  if ( (unsigned int)*(this + 2) >= 0x71C71C6 )
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
  v6 = sub_479EF0(*(this + 1), (int)a4, *(this + 1), a5, 0);
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
  if ( *(uint8_t *)(v6[1] + 48) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 48) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_479140(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 48) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 48) = 0;
          sub_4791A0(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 48) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_4791A0(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 48) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 48) = 0;
        sub_479140(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 48) = 1;
      *(uint8_t *)(v14 + 48) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 48) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 48) != 0 )
      {
        v6 = v21;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 48) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x47A380 sub_47A380
// ------------------------------------------------------------
int sub_47A380()
{
  int result; // eax

  sub_479EA0(*(void ***)(dword_99FC00 + 4));
  *(uint32_t *)(dword_99FC00 + 4) = dword_99FC00;
  dword_99FC04 = 0;
  *(uint32_t *)dword_99FC00 = dword_99FC00;
  result = dword_99FC00;
  *(uint32_t *)(dword_99FC00 + 8) = dword_99FC00;
  return result;
}



// ------------------------------------------------------------
// 0x47A3C0 sub_47A3C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47A3C0(char **this, uint32_t *a2, int a3)
{
  char *v4; // edi
  char *v5; // esi

  sub_479750((char *)(a3 + 180), *(this + 2), (uint32_t *)a3);
  v4 = *(this + 2);
  v5 = v4 - 180;
  do
  {
    sub_501490(v5);
    v5 += 180;
  }
  while ( v5 != v4 );
  *(this + 2) -= 180;
  *a2 = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x47A420 sub_47A420
// ------------------------------------------------------------
int /*stdcall*/ sub_47A420(int a1, int a2, uint32_t *a3)
{
  sub_479F80(a1, a2, a3);
  return a1 + 180 * a2;
}



// ------------------------------------------------------------
// 0x47A450 sub_47A450
// ------------------------------------------------------------
int /*thiscall*/ sub_47A450(int *this, int a2, uint32_t *a3)
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
  if ( *(uint8_t *)(v3 + 49) == 0 )
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
      if ( *(uint8_t *)(v3 + 49) != 0 )
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
      *(uint32_t *)a2 = *sub_47A1D0(this, &a3, 1, v4, (int)v6);
      *(uint8_t *)(a2 + 4) = 1;
      return a2;
    }
    sub_479050(&a3);
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
    *(uint32_t *)a2 = *sub_47A1D0(v20, &a3, v21, v4, (int)v6);
    *(uint8_t *)(a2 + 4) = 1;
  }
  return a2;
}



// ------------------------------------------------------------
// 0x47A5B0 sub_47A5B0
// ------------------------------------------------------------
void /*thiscall*/ sub_47A5B0(int *this, char *a2, unsigned int a3, int a4)
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
  uint32_t *v16; // ecx
  int v18; // edx
  uint32_t *v19; // [esp-18h] [ebp-F8h]
  uint32_t *v20; // [esp-10h] [ebp-F0h]
  int v21; // [esp-Ch] [ebp-ECh]
  unsigned int v22; // [esp-8h] [ebp-E8h]
  uint32_t v23[4]; // [esp+0h] [ebp-E0h] BYREF
  void *Block; // [esp+10h] [ebp-D0h]
  char *v25; // [esp+14h] [ebp-CCh]
  void *v26[47]; // [esp+18h] [ebp-C8h] BYREF
  int v27; // [esp+DCh] [ebp-4h]
  uint32_t *v28; // [esp+E8h] [ebp+8h]
  int v29; // [esp+ECh] [ebp+Ch]

  v26[45] = (void *)dword_796E50;
  v26[46] = v23;
  v23[3] = this;
  sub_4796F0(a4);
  v5 = *(this + 1);
  v6 = 0;
  v27 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 180;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - *(this + 1)) / 180;
    else
      v8 = 0;
    if ( 23860929 - v8 < a3 )
      sub_479680(this);
    if ( *(this + 1) != 0 )
      v9 = (*(this + 2) - *(this + 1)) / 180;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = (uint32_t *)*(this + 2);
      Block = v16;
      if ( ((char *)v16 - a2) / 180 >= a3 )
      {
        v28 = &v16[-45 * a3];
        *(this + 2) = sub_479CE0(v28, v16, (int)v16);
        sub_479CC0(a2, v28, Block);
        sub_479C40(a2, &a2[180 * a3], v26);
      }
      else
      {
        sub_479CE0(a2, v16, (int)&a2[180 * a3]);
        v22 = a3 - (*(this + 2) - (int)a2) / 180;
        v21 = *(this + 2);
        LOBYTE(v27) = 3;
        sub_47A420(v21, v22, v26);
        v18 = 180 * a3 + *(this + 2);
        *(this + 2) = v18;
        v27 = 0;
        sub_479C40(a2, v18 - 180 * a3, v26);
      }
    }
    else
    {
      if ( 23860929 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        v11 = (*(this + 2) - *(this + 1)) / 180;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_478FE0(this);
      v29 = 180 * v10;
      v12 = (char *)operator new(180 * v10);
      v19 = (uint32_t *)*(this + 1);
      Block = v12;
      v25 = v12;
      LOBYTE(v27) = 1;
      v25 = (char *)sub_479CE0(v19, a2, (int)v12);
      sub_479F80((int)v25, a3, v26);
      v20 = (uint32_t *)*(this + 2);
      v25 += 180 * a3;
      sub_479CE0(a2, v20, (int)v25);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 180;
      v14 = v13 + a3;
      v15 = (void *)*(this + 1);
      if ( v15 != nullptr )
      {
        sub_47A090(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v29];
      *(this + 2) = (int)&v12[180 * v14];
      *(this + 1) = (int)v12;
    }
  }
  if ( v26[6] >= (void *)0x10 )
    j__free(v26[1]);
}


// ------------------------------------------------------------
// 0x47A930 sub_47A930
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_47A930(unsigned int *this, unsigned int a2)
{
  unsigned int result; // eax
  char **v4; // ecx

  result = *(this + 2);
  v4 = (char **)(this + 1);
  if ( result != 0 )
  {
    result = (int)&v4[2][-result] / 180;
    if ( a2 < result )
      return (unsigned int)sub_47A3C0(v4, &a2, *(this + 2) + 180 * a2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x47A980 sub_47A980
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_47A980(unsigned int *this, const char *a2)
{
  unsigned int v3; // eax

  v3 = sub_479290(this, a2);
  return sub_47A930(this, v3);
}



// ------------------------------------------------------------
// 0x47A9B0 sub_47A9B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47A9B0(uint32_t *this)
{
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *this = &vftbl_CNRDFriendManager;
  return this;
}



// ------------------------------------------------------------
// 0x47A9D0 sub_47A9D0
// ------------------------------------------------------------
int /*thiscall*/ sub_47A9D0(uint32_t *this)
{
  *this = &vftbl_CNRDBuddyManager;
  return sub_47A0C0((int)(this + 1));
}



// ------------------------------------------------------------
// 0x47A9E0 sub_47A9E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47A9E0(uint32_t *this)
{
  char *v2; // ecx

  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  v2 = (char *)(this + 5);
  *this = &vftbl_CNRDGuildManager;
  *((uint32_t *)v2 + 6) = 15;
  *((uint32_t *)v2 + 5) = 0;
  v2[4] = 0;
  *((uint8_t *)this + 68) = 0;
  *(this + 16) = &vftbl_nengine__CNTimer;
  *(this + 18) = 0;
  *((uint8_t *)this + 76) = 1;
  *((uint8_t *)this + 78) = 0;
  *((uint8_t *)this + 77) = 0;
  *(this + 22) = 0;
  *(this + 21) = 0;
  *(this + 20) = 0;
  *((uint8_t *)this + 96) = 0;
  *(this + 23) = &vftbl_nengine__CNTimer;
  *(this + 25) = 0;
  *((uint8_t *)this + 104) = 1;
  *((uint8_t *)this + 106) = 0;
  *((uint8_t *)this + 105) = 0;
  *(this + 29) = 0;
  *(this + 28) = 0;
  *(this + 27) = 0;
  sub_4015C0((void *)szPassword, 0);
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *((uint8_t *)this + 77) = 0;
  *((uint8_t *)this + 78) = 0;
  *((uint8_t *)this + 105) = 0;
  *((uint8_t *)this + 106) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x47AAA0 sub_47AAA0
// ------------------------------------------------------------
int /*thiscall*/ sub_47AAA0(void *this)
{
  *(uint32_t *)this = &vftbl_CNRDGuildManager;
  *((uint32_t *)this + 23) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 96) = 0;
  *((uint32_t *)this + 16) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 68) = 0;
  if ( *((uint32_t *)this + 11) >= 0x10u )
    j__free(*((void **)this + 6));
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 15;
  *((uint8_t *)this + 24) = 0;
  *(uint32_t *)this = &vftbl_CNRDBuddyManager;
  return sub_47A0C0((int)this + 4);
}



// ------------------------------------------------------------
// 0x47AAF0 CNRDGuildManager__vmtC
// ------------------------------------------------------------
// CNRDGuildManager::vmtC（RTTI 自证）
int /*thiscall*/ CNRDGuildManager__vmtC(int this)
{
  sub_4015C0((void *)szPassword, 0);
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint8_t *)(this + 77) = 0;
  *(uint8_t *)(this + 78) = 0;
  *(uint8_t *)(this + 105) = 0;
  *(uint8_t *)(this + 106) = 0;
  return sub_47A0C0(this + 4);
}



// ------------------------------------------------------------
// 0x47AB30 sub_47AB30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47AB30(uint32_t *this)
{
  uint32_t *v2; // edi
  int v3; // edx
  int v4; // edx

  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *this = &vftbl_CNRDMemberManager;
  *(this + 11) = 15;
  *(this + 10) = 0;
  *((uint8_t *)this + 24) = 0;
  *((uint8_t *)this + 60) = 0;
  *(this + 14) = &vftbl_nengine__CNTimer;
  *(this + 16) = 0;
  *((uint8_t *)this + 68) = 1;
  *((uint8_t *)this + 70) = 0;
  *((uint8_t *)this + 69) = 0;
  *(this + 20) = 0;
  *(this + 19) = 0;
  *(this + 18) = 0;
  *((uint8_t *)this + 88) = 0;
  *(this + 21) = &vftbl_nengine__CNTimer;
  *(this + 23) = 0;
  *((uint8_t *)this + 96) = 1;
  *((uint8_t *)this + 98) = 0;
  *((uint8_t *)this + 97) = 0;
  *(this + 27) = 0;
  *(this + 26) = 0;
  *(this + 25) = 0;
  v2 = this + 28;
  sub_41A630((unsigned int)(this + 28));
  *v2 = &vftbl_clong;
  sub_41A630((unsigned int)this + 126);
  *(uint32_t *)((char *)this + 126) = &vftbl_clong;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *((uint8_t *)this + 69) = 0;
  *((uint8_t *)this + 70) = 0;
  *((uint8_t *)this + 97) = 0;
  *((uint8_t *)this + 98) = 0;
  sub_41A590((unsigned int)v2, v3, 0);
  sub_41A590((unsigned int)this + 126, v4, 0);
  return this;
}



// ------------------------------------------------------------
// 0x47AC10 sub_47AC10
// ------------------------------------------------------------
int /*thiscall*/ sub_47AC10(char *this)
{
  *(uint32_t *)this = &vftbl_CNRDMemberManager;
  sub_41A580(this + 126);
  sub_41A580(this + 112);
  *((uint32_t *)this + 21) = &vftbl_nengine__IObject;
  *(this + 88) = 0;
  *((uint32_t *)this + 14) = &vftbl_nengine__IObject;
  *(this + 60) = 0;
  if ( *((uint32_t *)this + 11) >= 0x10u )
    j__free(*((void **)this + 6));
  *((uint32_t *)this + 11) = 15;
  *((uint32_t *)this + 10) = 0;
  *(this + 24) = 0;
  *(uint32_t *)this = &vftbl_CNRDBuddyManager;
  return sub_47A0C0((int)(this + 4));
}



// ------------------------------------------------------------
// 0x47ACB0 CNRDMemberManager__vmtC
// ------------------------------------------------------------
// CNRDMemberManager::vmtC（RTTI 自证）
int /*fastcall*/ CNRDMemberManager__vmtC(int a1, int a2)
{
  int v3; // edx

  *(uint32_t *)(a1 + 48) = 0;
  *(uint32_t *)(a1 + 52) = 0;
  *(uint8_t *)(a1 + 69) = 0;
  *(uint8_t *)(a1 + 70) = 0;
  *(uint8_t *)(a1 + 97) = 0;
  *(uint8_t *)(a1 + 98) = 0;
  sub_41A590(a1 + 112, a2, 0);
  sub_41A590(a1 + 126, v3, 0);
  return sub_47A0C0(a1 + 4);
}



// ------------------------------------------------------------
// 0x47ACF0 sub_47ACF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47ACF0(int this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_47A1D0((int *)this, a2, 1, *(uint32_t **)(this + 4), (int)a4);
    return a2;
  }
  v6 = *(uint32_t **)(this + 4);
  v7 = a4;
  if ( a3 == (uint32_t *)*v6 )
  {
    if ( (uint8_t)sub_40C160(a4, a3 + 3) != 0 )
    {
      sub_47A1D0((int *)this, a2, 1, a3, (int)v7);
      return a2;
    }
    goto LABEL_23;
  }
  if ( a3 == v6 )
  {
    if ( (uint8_t)sub_40C160(v6[2] + 12, a4) != 0 )
    {
      sub_47A1D0((int *)this, a2, 0, *(uint32_t **)(*(uint32_t *)(this + 4) + 8), (int)v7);
      return a2;
    }
    goto LABEL_23;
  }
  if ( (uint8_t)sub_40C160(a4, a3 + 3) != 0 )
  {
    a4 = a3;
    sub_479050(&a4);
    if ( (uint8_t)sub_40C160(a4 + 3, v7) != 0 )
    {
      if ( *(uint8_t *)(a4[2] + 49) != 0 )
        sub_47A1D0((int *)this, a2, 0, a4, (int)v7);
      else
        sub_47A1D0((int *)this, a2, 1, a3, (int)v7);
      return a2;
    }
  }
  if ( (uint8_t)sub_40C160(a3 + 3, v7) == 0 )
    goto LABEL_23;
  a4 = a3;
  sub_4790B0((int *)&a4);
  v8 = a4;
  if ( a4 != *(uint32_t **)(this + 4) )
  {
    if ( (uint8_t)sub_40C160(v7, a4 + 3) != 0 )
    {
      v8 = a4;
      goto LABEL_19;
    }
LABEL_23:
    v9 = *(uint32_t *)sub_47A450((int *)this, (int)v10, v7);
    *a2 = v9;
    return a2;
  }
LABEL_19:
  if ( *(uint8_t *)(a3[2] + 49) != 0 )
    sub_47A1D0((int *)this, a2, 0, a3, (int)v7);
  else
    sub_47A1D0((int *)this, a2, 1, v8, (int)v7);
  return a2;
}



// ------------------------------------------------------------
// 0x47AE90 sub_47AE90
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47AE90(int *this, uint32_t *a2, char *a3, uint32_t *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 180 != 0 )
    v6 = (int)&a3[-v5] / 180;
  else
    v6 = 0;
  sub_47A5B0(this, a3, 1u, a4);
  *a2 = *(this + 1) + 180 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x47AF40 CNRDBuddyManager__vmt0
// ------------------------------------------------------------
// CNRDBuddyManager::vmt0（RTTI 自证）
uint32_t */*thiscall*/ CNRDBuddyManager__vmt0(uint32_t *Block, char a2)
{
  sub_47A9D0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x47AF70 CNRDGuildManager__vmt0
// ------------------------------------------------------------
// CNRDGuildManager::vmt0（RTTI 自证）
void */*thiscall*/ CNRDGuildManager__vmt0(void *Block, char a2)
{
  sub_47AAA0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x47AFA0 CNRDMemberManager__vmt0
// ------------------------------------------------------------
// CNRDMemberManager::vmt0（RTTI 自证）
char */*thiscall*/ CNRDMemberManager__vmt0(char *Block, char a2)
{
  sub_47AC10(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x47AFD0 sub_47AFD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47AFD0(uint32_t *this)
{
  uint32_t *v2; // eax

  v2 = sub_479200();
  *(this + 1) = v2;
  *((uint8_t *)v2 + 49) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  return this;
}



// ============================================================
// 【分区 9】社交管理器 II（0x47B000-0x47B9E0）
// CNRDGuildManager/CNRDMemberManager/CNRDBuddyManager 各 vmt 槽（RTTI 自证）。
// ============================================================
// ------------------------------------------------------------
// 0x47B000 sub_47B000
// ------------------------------------------------------------
int */*thiscall*/ sub_47B000(int this, int a2)
{
  unsigned int *v2; // edi
  int *v4; // esi
  const char *v5; // eax
  int v7; // [esp+Ch] [ebp-30h] BYREF
  void *Block; // [esp+10h] [ebp-2Ch]
  int v9; // [esp+20h] [ebp-1Ch]
  unsigned int v10; // [esp+24h] [ebp-18h]
  int v11; // [esp+28h] [ebp-14h]
  int v12; // [esp+2Ch] [ebp-10h]
  int v13; // [esp+38h] [ebp-4h]

  v2 = (unsigned int *)a2;
  v4 = sub_479550((int **)this, a2);
  if ( v4 == *(int **)(this + 4)
    || ((unsigned int)v4[9] < 0x10 ? (v5 = (const char *)(v4 + 4)) : (v5 = (const char *)v4[4]),
        sub_40BF00((std::_String_base *)v2, 0, v2[5], v5, v4[8]) < 0) )
  {
    v10 = 15;
    v9 = 0;
    LOBYTE(Block) = 0;
    sub_4014D0((std::_String_base *)&v7, a2, 0, -1);
    v11 = 0;
    v12 = 0;
    v13 = 0;
    v4 = (int *)*sub_47ACF0(this, &a2, v4, &v7);
    if ( v10 >= 0x10 )
      j__free(Block);
  }
  return v4 + 10;
}



// ------------------------------------------------------------
// 0x47B0C0 sub_47B0C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47B0C0(int this, uint32_t *a2)
{
  int v3; // ebx
  unsigned int v4; // esi
  int v5; // esi
  uint32_t *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 180;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 180 )
    return sub_47AE90((int *)this, &a2, *(char **)(this + 8), a2);
  v5 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_479F80(v5, 1, a2);
  *(uint32_t *)(this + 8) = v5 + 180;
  return result;
}



// ------------------------------------------------------------
// 0x47B150 sub_47B150
// ------------------------------------------------------------
int /*thiscall*/ sub_47B150(uint32_t *this, char *Src, int a3, int a4, int a5, int a6)
{
  int v7; // eax
  uint32_t *v8; // eax
  uint8_t v10[4]; // [esp+Ch] [ebp-C0h] BYREF
  void *Block; // [esp+10h] [ebp-BCh]
  unsigned int v12; // [esp+24h] [ebp-A8h]
  int v13; // [esp+C8h] [ebp-4h]

  if ( Src == nullptr || a4 >= 4 )
    return 0;
  v7 = sub_429870((int **)dword_8F8500, Src);
  v8 = (uint32_t *)sub_479DF0((int)v10, Src, a3, a4, a5, a6, v7);
  v13 = 0;
  sub_47B0C0((int)(this + 1), v8);
  if ( v12 >= 0x10 )
    j__free(Block);
  return *(this + 3) - 180;
}



// ------------------------------------------------------------
// 0x47B200 sub_47B200
// ------------------------------------------------------------
int /*cdecl*/ sub_47B200(void *Src, int a2)
{
  int *v2; // eax
  int *v4; // eax
  int *v5; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v6[4]; // [esp+10h] [ebp-4Ch] BYREF
  void *v7; // [esp+14h] [ebp-48h]
  int v8; // [esp+24h] [ebp-38h]
  unsigned int v9; // [esp+28h] [ebp-34h]
  DWORD Time; // [esp+2Ch] [ebp-30h]
  unsigned int v11; // [esp+30h] [ebp-2Ch] BYREF
  void *Block; // [esp+34h] [ebp-28h]
  int v13; // [esp+44h] [ebp-18h]
  unsigned int v14; // [esp+48h] [ebp-14h]
  int v15; // [esp+4Ch] [ebp-10h]
  int v16; // [esp+58h] [ebp-4h]

  v15 = dword_796E50;
  v14 = 15;
  v13 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(Src, strlen((const char *)Src));
  v16 = 0;
  Time = timeGetTime();
  v2 = *sub_479610(&dword_99FBFC, &v5, &v11);
  if ( v2 == (int *)dword_99FC00 || v2[10] != a2 || v2[11] + 2000 <= Time )
  {
    v9 = 15;
    v8 = 0;
    LOBYTE(v7) = 0;
    sub_4015C0(Src, strlen((const char *)Src));
    LOBYTE(v16) = 1;
    *sub_47B000((int)&dword_99FBFC, (int)v6) = a2;
    LOBYTE(v16) = 0;
    if ( v9 >= 0x10 )
      j__free(v7);
    v9 = 15;
    v8 = 0;
    LOBYTE(v7) = 0;
    sub_4015C0(Src, strlen((const char *)Src));
    LOBYTE(v16) = 2;
    v4 = sub_47B000((int)&dword_99FBFC, (int)v6);
    v4[1] = Time;
    if ( v9 >= 0x10 )
      j__free(v7);
    if ( v14 >= 0x10 )
      j__free(Block);
    return 1;
  }
  else
  {
    if ( v14 >= 0x10 )
      j__free(Block);
    return 0;
  }
}



// ------------------------------------------------------------
// 0x47B380 sub_47B380
// ------------------------------------------------------------
int /*cdecl*/ sub_47B380(void *Src, uint8_t a2)
{
  int result; // eax
  char *v3; // eax
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int v5; // [esp+84h] [ebp-4h]

  v5 = dword_796E50;
  result = sub_47B200(Src, 1);
  if ( result == 1 )
  {
    v3 = sub_422E70(671);
    sprintf(Buffer, v3, Src, a2);
    return sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x47B400 sub_47B400
// ------------------------------------------------------------
int /*cdecl*/ sub_47B400(void *Src)
{
  int result; // eax
  char *v2; // eax
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int v4; // [esp+84h] [ebp-4h]

  v4 = dword_796E50;
  result = sub_47B200(Src, 0);
  if ( result == 1 )
  {
    v2 = sub_422E70(670);
    sprintf(Buffer, v2, Src);
    return sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x47B470 sub_47B470
// ------------------------------------------------------------
int /*cdecl*/ sub_47B470(int a1)
{
  int v1; // eax
  int v2; // eax
  int v3; // ecx
  int v4; // eax

  v1 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  v2 = sub_41A5E0(v1 + 53);
  v3 = *(uint32_t *)(a1 + 156);
  v4 = v2 - v3;
  if ( v4 > 2 || v3 <= 2 )
    return v4 > 4 ? -16599746 : -16525825;
  else
    return -16776961;
}



// ------------------------------------------------------------
// 0x47B4D0 sub_47B4D0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_47B4D0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t *v4; // edi
  int v5; // eax
  int v6; // edx

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    *v4 = *v3;
    v5 = sub_41A5E0((unsigned int)(v3 + 1));
    sub_41A590((unsigned int)(v4 + 1), v6, v5);
    v3 += 5;
    v4 += 5;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x47B510 sub_47B510
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_47B510(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  uint32_t *v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // edx

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v5 = *(uint32_t *)(v3 - 20);
    v3 -= 20;
    v4 -= 5;
    *v4 = v5;
    v6 = sub_41A5E0(v3 + 4);
    sub_41A590((unsigned int)(v4 + 1), v7, v6);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x47B560 sub_47B560
// ------------------------------------------------------------
int /*thiscall*/ sub_47B560(uint32_t *this, int a2)
{
  int v2; // eax
  char *v3; // eax

  v2 = *(this + 2);
  if ( v2 != 0 && (unsigned int)((*(this + 3) - v2) / 20) >= 3 )
  {
    v3 = sub_422E70(464);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);
  }
  else
  {
    sub_423200(dword_8F7B08, 33);
    sub_423290(dword_8F7B08, (int)&a2, 2);
    return sub_423380(dword_8F7B08);
  }
}



// ------------------------------------------------------------
// 0x47B5E0 sub_47B5E0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_47B5E0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi
  int v5; // eax
  int v6; // edx

  result = a2;
  for ( i = a1; i != a2; i += 5 )
  {
    *i = *a3;
    v5 = sub_41A5E0((unsigned int)(a3 + 1));
    sub_41A590((unsigned int)(i + 1), v6, v5);
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47B620 sub_47B620
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_47B620(int a1, int a2, uint32_t *a3)
{
  return sub_47B510(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x47B640 sub_47B640
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_47B640(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v4; // esi
  int v5; // eax
  int v6; // edx
  uint32_t v8[6]; // [esp+0h] [ebp-24h] BYREF
  int v9; // [esp+20h] [ebp-4h]

  v4 = a3;
  v8[5] = v8;
  v8[4] = a3;
  v9 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v9) = 1;
    if ( v4 != nullptr )
    {
      *v4 = *a1;
      v8[3] = v4 + 1;
      sub_41A630((unsigned int)(v4 + 1));
      LOBYTE(v9) = 2;
      v4[1] = &vftbl_clong;
      v5 = sub_41A5E0((unsigned int)(a1 + 1));
      sub_41A590((unsigned int)(v4 + 1), v6, v5);
    }
    v4 += 5;
    LOBYTE(v9) = 0;
    a1 += 5;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x47B6F0 sub_47B6F0
// ------------------------------------------------------------
char /*thiscall*/ sub_47B6F0(uint32_t *this, int a2)
{
  uint32_t **v2; // eax
  uint32_t **v3; // ecx

  v2 = (uint32_t **)*(this + 6);
  v3 = (uint32_t **)*(this + 7);
  if ( v2 == v3 )
    return 0;
  while ( **v2 != a2 )
  {
    if ( ++v2 == v3 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x47B720 sub_47B720
// ------------------------------------------------------------
char /*thiscall*/ sub_47B720(uint32_t *this, unsigned int a2, int a3)
{
  int v4; // ecx
  unsigned int v5; // edi
  int v7; // eax
  int v8; // eax
  int *v9; // eax
  int v10; // ebx
  uint32_t *v11; // ecx
  uint32_t *v12; // eax
  uint32_t *v13; // ecx
  uint32_t *v14; // [esp+8h] [ebp-4h]
  int i; // [esp+14h] [ebp+8h]
  int v16; // [esp+18h] [ebp+Ch]

  v4 = *(this + 6);
  v5 = 0;
  if ( v4 == 0 )
    return 0;
  if ( (*(this + 7) - v4) >> 2 <= a2 )
    return 0;
  v14 = *(uint32_t **)(*(this + 6) + 4 * a2);
  if ( v14[31] != a3 )
    return 0;
  v7 = *(this + 2);
  if ( v7 != 0 )
    v16 = (*(this + 3) - v7) / 20;
  else
    v16 = 0;
  if ( v16 <= 0 )
    return 1;
  for ( i = 0; ; i += 20 )
  {
    v8 = *(this + 2);
    if ( v8 != 0 && v5 < (*(this + 3) - v8) / 20 )
      v9 = *(int **)(i + *(this + 2));
    else
      v9 = nullptr;
    v10 = *v9;
    v11 = v14;
    if ( *v9 == *v14 )
    {
      if ( sub_463F10(this, v5) != -1 )
        return 0;
      v11 = v14;
    }
    v12 = (uint32_t *)v11[46];
    v13 = (uint32_t *)v11[47];
    if ( v12 != v13 )
      break;
LABEL_20:
    if ( (int)++v5 >= v16 )
      return 1;
  }
  while ( *v12 != v10 )
  {
    if ( ++v12 == v13 )
      goto LABEL_20;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x47B820 sub_47B820
// ------------------------------------------------------------
int /*thiscall*/ sub_47B820(uint32_t *this, int a2)
{
  int64_t v2; // rax
  int v3; // edi
  unsigned int v4; // esi
  int v5; // ebx
  int v7; // [esp+8h] [ebp-4h]

  LODWORD(v2) = *(this + 2);
  if ( (uint32_t)v2 != 0 )
  {
    v2 = 1717986919LL * (*(this + 3) - (int)v2);
    v3 = (SHIDWORD(v2) >> 3) + (HIDWORD(v2) >> 31);
  }
  else
  {
    v3 = 0;
  }
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = *(this + 2);
    v7 = 0;
    do
    {
      if ( v5 != 0 && v4 < (*(this + 3) - v5) / 20 )
        LODWORD(v2) = *(uint32_t *)(v7 + *(this + 2));
      else
        LODWORD(v2) = 0;
      if ( *(uint32_t *)v2 == a2 )
        break;
      ++v4;
      v7 += 20;
    }
    while ( (int)v4 < v3 );
  }
  if ( v4 != v3 )
  {
    sub_423200(dword_8F7B08, 34);
    sub_423290(dword_8F7B08, (int)&a2, 2);
    LODWORD(v2) = sub_423380(dword_8F7B08);
  }
  return v2;
}



// ------------------------------------------------------------
// 0x47B8D0 sub_47B8D0
// ------------------------------------------------------------
char /*thiscall*/ sub_47B8D0(uint32_t *this, int a2, int a3)
{
  int64_t v3; // rax
  int v4; // edi
  unsigned int v5; // esi
  int v6; // ebx
  int v7; // eax
  int v9; // [esp+Ch] [ebp-4h]

  LODWORD(v3) = *(this + 2);
  if ( (uint32_t)v3 != 0 )
  {
    v3 = 1717986919LL * (*(this + 3) - (int)v3);
    v4 = (SHIDWORD(v3) >> 3) + (HIDWORD(v3) >> 31);
  }
  else
  {
    v4 = 0;
  }
  v5 = 0;
  if ( v4 <= 0 )
    goto LABEL_17;
  v6 = *(this + 2);
  v9 = 0;
  while ( 1 )
  {
    LODWORD(v3) = v6 != 0 && v5 < (*(this + 3) - v6) / 20 ? *(uint32_t *)(v9 + *(this + 2)) : 0;
    if ( *(uint32_t *)v3 == a2 )
      break;
    ++v5;
    v9 += 20;
    if ( (int)v5 >= v4 )
      goto LABEL_17;
  }
  if ( (v7 = *(this + 2)) != 0
    && v5 < (*(this + 3) - v7) / 20
    && (LODWORD(v3) = *(this + 2) + 20 * v5, *(uint32_t *)v3 != 0)
    || (LOBYTE(v3) = a3, (uint8_t)a3 != 0) )
  {
LABEL_17:
    if ( v5 != v4 )
    {
      sub_423200(dword_8F7B08, 35);
      sub_423290(dword_8F7B08, (int)&a2, 2);
      HIBYTE(a3) = (uint8_t)a3 != 0;
      sub_423290(dword_8F7B08, (int)&a3 + 3, 1);
      LOBYTE(v3) = sub_423380(dword_8F7B08);
    }
  }
  return v3;
}



// ============================================================
// 【分区 10】触发条件评估器（0x47B9E0-0x47C2F0）
// 评估器 0x47BBE0：八类条件 case 0-7（0=计时器 / 2=比例% / 3=加载进度 sub_477260×100/
// sub_43B5C0 / 4=旗标 / 5=座位比对 / 6=恒真 / 7=进度值）——不满足即 sub_47B8D0 关断。
// ============================================================
// ------------------------------------------------------------
// 0x47B9E0 sub_47B9E0
// ------------------------------------------------------------
int /*thiscall*/ sub_47B9E0(uint32_t *this, int a2)
{
  int64_t v2; // rax
  int v3; // edi
  unsigned int v4; // esi
  int v5; // ebx
  int v7; // [esp+Ch] [ebp-4h]

  LODWORD(v2) = *(this + 2);
  if ( (uint32_t)v2 != 0 )
  {
    v2 = 1717986919LL * (*(this + 3) - (int)v2);
    v3 = (SHIDWORD(v2) >> 3) + (HIDWORD(v2) >> 31);
  }
  else
  {
    v3 = 0;
  }
  v4 = 0;
  if ( v3 <= 0 )
    goto LABEL_14;
  v5 = *(this + 2);
  v7 = 0;
  while ( 1 )
  {
    LODWORD(v2) = v5 != 0 && v4 < (*(this + 3) - v5) / 20 ? *(uint32_t *)(v7 + *(this + 2)) : 0;
    if ( *(uint32_t *)v2 == a2 )
      break;
    ++v4;
    v7 += 20;
    if ( (int)v4 >= v3 )
      goto LABEL_14;
  }
  LODWORD(v2) = sub_463F10(this, v4);
  if ( (uint32_t)v2 == 0 )
  {
LABEL_14:
    if ( v4 != v3 )
    {
      sub_423200(dword_8F7B08, 36);
      sub_423290(dword_8F7B08, (int)&a2, 2);
      LODWORD(v2) = sub_423380(dword_8F7B08);
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x47BAA0 sub_47BAA0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_47BAA0(unsigned int *this)
{
  unsigned int v1; // edi
  unsigned int result; // eax
  int v4; // eax
  int v5; // ebx
  int v6; // ebx
  int v7; // [esp+Ch] [ebp-8h]
  int *v8; // [esp+10h] [ebp-4h]

  v1 = 0;
  v7 = 0;
  while ( 1 )
  {
    result = *(this + 2);
    if ( result == 0 )
      return result;
    result = (int)(*(this + 3) - result) / 20;
    if ( v1 >= result )
      return result;
    v4 = *(this + 2);
    if ( v4 != 0 && v1 < (int)(*(this + 3) - v4) / 20 )
    {
      v5 = *(uint32_t *)(*(this + 2) + v7);
      v8 = (int *)v5;
    }
    else
    {
      v8 = nullptr;
      v5 = 0;
    }
    if ( *(uint32_t *)(v5 + 272) == 5
      && sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0
      && sub_463F10(this, v1) != -1 )
    {
      if ( *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 116) < **(uint32_t **)(v5 + 284) )
      {
        if ( sub_463F10(this, v1) == 0 )
          sub_47B8D0(this, *(uint32_t *)v5, 1);
        goto LABEL_18;
      }
      if ( sub_463F10(this, v1) <= 0 )
        goto LABEL_18;
      v6 = 0;
      if ( sub_463F10(this, v1) <= 0 )
        goto LABEL_18;
      do
      {
        sub_47B8D0(this, *v8, 0);
        ++v6;
      }
      while ( v6 < sub_463F10(this, v1) );
      ++v1;
      v7 += 20;
    }
    else
    {
LABEL_18:
      ++v1;
      v7 += 20;
    }
  }
}



// ------------------------------------------------------------
// 0x47BBE0 sub_47BBE0
// ------------------------------------------------------------
// 触发条件评估器：遍历条件对象（+68 表，20 字节/项），按 v9[69] 型别：
// 0=计时器（dword_8F8520 vt+120 时钟 +164）/ 1=|Y| 阈值（dword_99FD58+948）/
// 2=百分比（+906/+920 ×100）/ 3=加载进度（sub_477260×100/sub_43B5C0）/
// 4=旗标（+120 非零）/ 5=座位号比对 sub_456390 / 6=恒真 / 7=进度值 sub_495C80；
// 不满足 → sub_47B8D0(对象, 0) 关断
int /*thiscall*/ sub_47BBE0(int *this, int a2, int a3)
{
  int result; // eax
  unsigned int v5; // esi
  int v6; // edx
  int v7; // eax
  int v8; // ecx
  uint32_t *v9; // edi
  uint32_t *v10; // esi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int *v14; // esi
  uint64_t v15; // rax
  int v16; // ecx
  bool v17; // cc
  int v18; // eax
  float v19; // [esp+8h] [ebp-14h]
  float v20; // [esp+Ch] [ebp-10h]
  int v21; // [esp+10h] [ebp-Ch]
  int i; // [esp+14h] [ebp-8h]
  unsigned int v23; // [esp+18h] [ebp-4h]

  result = *(this + 2);
  v5 = 0;
  if ( result != 0 )
  {
    result = (*(this + 3) - result) / 20;
    v21 = result;
  }
  else
  {
    v21 = 0;
  }
  v23 = 0;
  if ( v21 > 0 )
  {
    for ( i = 0; ; i += 20 )
    {
      if ( (int)sub_463F10(v5) <= 0 )
        goto LABEL_38;
      v7 = *(this + 2);
      if ( v7 != 0
        && (v8 = *(this + 3) - v7, v6 = (int)((uint64_t)(1717986919LL * v8) >> 32) >> 3, v5 < v8 / 20) )
      {
        v9 = *(uint32_t **)(*(this + 2) + i);
      }
      else
      {
        v9 = nullptr;
      }
      if ( v9[68] != 1 )
        goto LABEL_38;
      v10 = (uint32_t *)v9[71];
      if ( a2 != *v10 )
        goto LABEL_37;
      v11 = v10[1];
      if ( v11 != -1 && a3 != v11 )
        goto LABEL_37;
      v12 = v9[69];
      switch ( v12 )
      {
        case 0:
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
          v14 = (int *)(v9[71] + 8);
          if ( sub_699000(v13 + 164) / 1000 <= *v14 )
            goto LABEL_36;
          goto LABEL_37;
        case 1:
          if ( (double)*(int *)(v9[71] + 8) >= fabs(COERCE_FLOAT(sub_41A5E0((unsigned int)dword_99FD58 + 948))) )
            goto LABEL_36;
          goto LABEL_37;
        case 2:
          v20 = COERCE_FLOAT(sub_41A5E0((unsigned int)dword_99FD58 + 906));
          v15 = (uint64_t)(v20 / COERCE_FLOAT(sub_41A5E0((unsigned int)dword_99FD58 + 920)) * 100.0);
          v16 = *(uint32_t *)(v9[71] + 8);
          goto LABEL_34;
        default:
          break;
      }
      if ( v12 == 3 )
        break;
      switch ( v12 )
      {
        case 4:
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
          if ( sub_41A5E0(v18 + 120) == 0 )
            goto LABEL_36;
          break;
        case 5:
          if ( sub_456390(0) == v10[2] )
            goto LABEL_36;
          break;
        case 6:
          goto LABEL_36;
        case 7:
          LODWORD(v15) = sub_495C80(dword_99FD58);
          v16 = v10[2];
LABEL_34:
          v17 = (int)v15 < v16;
LABEL_35:
          if ( !v17 )
LABEL_36:
            sub_47B8D0(*v9, 0);
          break;
        default:
          break;
      }
LABEL_37:
      v5 = v23;
LABEL_38:
      result = v21;
      v23 = ++v5;
      if ( (int)v5 >= v21 )
        return result;
    }
    v19 = sub_477260(dword_99FD58, v6) * 100.0;
    v17 = (int)(uint64_t)(v19 / sub_43B5C0(dword_99FD58)) < *(uint32_t *)(v9[71] + 8);
    goto LABEL_35;
  }
  return result;
}


// ------------------------------------------------------------
// 0x47BE30 sub_47BE30
// ------------------------------------------------------------
char /*thiscall*/ sub_47BE30(uint32_t *this, int a2)
{
  int64_t v3; // rax
  int v4; // ebx
  unsigned int v5; // edi
  int v6; // eax
  int v8; // [esp+Ch] [ebp-4h]

  LODWORD(v3) = *(this + 2);
  if ( (uint32_t)v3 != 0 )
  {
    v3 = 1717986919LL * (*(this + 3) - (int)v3);
    v4 = (SHIDWORD(v3) >> 3) + (HIDWORD(v3) >> 31);
  }
  else
  {
    v4 = 0;
  }
  v5 = 0;
  if ( v4 > 0 )
  {
    v8 = 0;
    do
    {
      LODWORD(v3) = sub_463F10(this, v5);
      if ( (int)v3 > 0 )
      {
        v6 = *(this + 2);
        if ( v6 != 0 && v5 < (*(this + 3) - v6) / 20 )
          LODWORD(v3) = *(uint32_t *)(v8 + *(this + 2));
        else
          LODWORD(v3) = 0;
        if ( *(uint32_t *)(v3 + 272) == 3 && a2 == **(uint32_t **)(v3 + 284) )
          LOBYTE(v3) = sub_47B8D0(this, *(uint32_t *)v3, 0);
      }
      ++v5;
      v8 += 20;
    }
    while ( (int)v5 < v4 );
  }
  return v3;
}



// ------------------------------------------------------------
// 0x47BEE0 sub_47BEE0
// ------------------------------------------------------------
char /*thiscall*/ sub_47BEE0(uint32_t *this, int a2, int a3, int a4)
{
  int64_t v5; // rax
  int v6; // ebx
  unsigned int v7; // edi
  int v8; // eax
  uint32_t *v9; // ecx
  int v11; // [esp+Ch] [ebp-4h]

  LODWORD(v5) = *(this + 2);
  if ( (uint32_t)v5 != 0 )
  {
    v5 = 1717986919LL * (*(this + 3) - (int)v5);
    v6 = (SHIDWORD(v5) >> 3) + (HIDWORD(v5) >> 31);
  }
  else
  {
    v6 = 0;
  }
  v7 = 0;
  if ( v6 > 0 )
  {
    v11 = 0;
    do
    {
      LODWORD(v5) = sub_463F10(this, v7);
      if ( (int)v5 > 0 )
      {
        v8 = *(this + 2);
        if ( v8 != 0 && v7 < (*(this + 3) - v8) / 20 )
          LODWORD(v5) = *(uint32_t *)(v11 + *(this + 2));
        else
          LODWORD(v5) = 0;
        if ( *(uint32_t *)(v5 + 272) == 2 )
        {
          v9 = *(uint32_t **)(v5 + 284);
          if ( (*v9 == -1 || a2 == *v9) && (v9[1] == -1 || a3 == v9[1]) && a4 == v9[2] )
            LOBYTE(v5) = sub_47B8D0(this, *(uint32_t *)v5, 0);
        }
      }
      ++v7;
      v11 += 20;
    }
    while ( (int)v7 < v6 );
  }
  return v5;
}



// ------------------------------------------------------------
// 0x47BFB0 sub_47BFB0
// ------------------------------------------------------------
char /*thiscall*/ sub_47BFB0(uint32_t *this, int a2)
{
  int v3; // eax
  unsigned int v4; // ebx
  int v5; // eax
  int v6; // esi
  int v8; // [esp+8h] [ebp-Ch]
  int v9; // [esp+Ch] [ebp-8h]
  char v10; // [esp+13h] [ebp-1h]

  v3 = *(this + 2);
  v4 = 0;
  v10 = 0;
  if ( v3 != 0 )
    v8 = (*(this + 3) - v3) / 20;
  else
    v8 = 0;
  if ( v8 > 0 )
  {
    v9 = 0;
    do
    {
      if ( sub_463F10(this, v4) > 0 )
      {
        v5 = *(this + 2);
        if ( v5 != 0 && v4 < (*(this + 3) - v5) / 20 )
          v6 = *(uint32_t *)(*(this + 2) + v9);
        else
          v6 = 0;
        if ( *(uint32_t *)(v6 + 272) == 4 && a2 == **(uint32_t **)(v6 + 284) )
        {
          sub_47B8D0(this, *(uint32_t *)v6, 0);
          if ( *(uint32_t *)(v6 + 128) == a2 )
            v10 = 1;
        }
      }
      ++v4;
      v9 += 20;
    }
    while ( (int)v4 < v8 );
  }
  return v10;
}



// ------------------------------------------------------------
// 0x47C080 sub_47C080
// ------------------------------------------------------------
char /*thiscall*/ sub_47C080(uint32_t *this, int a2)
{
  int v2; // edi
  unsigned int v3; // esi
  int v4; // ebx

  v2 = *(this + 2);
  v3 = 0;
  v4 = 0;
  while ( v2 != 0 && v3 < (*(this + 3) - v2) / 20 )
  {
    if ( **(uint32_t **)(v4 + *(this + 2)) == a2 )
      return 1;
    ++v3;
    v4 += 20;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x47C0E0 sub_47C0E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47C0E0(uint32_t *this, uint32_t *a2, uint32_t *a3)
{
  int *v3; // edx
  int *v4; // eax
  int *v5; // ecx
  int *v6; // eax

  v3 = (int *)*(this + 1);
  v4 = (int *)v3[1];
  while ( *((uint8_t *)v4 + 21) == 0 )
  {
    if ( *a3 >= v4[3] )
    {
      v4 = (int *)v4[2];
    }
    else
    {
      v3 = v4;
      v4 = (int *)*v4;
    }
  }
  v5 = (int *)*(this + 1);
  v6 = (int *)v5[1];
  while ( *((uint8_t *)v6 + 21) == 0 )
  {
    if ( v6[3] >= *a3 )
    {
      v5 = v6;
      v6 = (int *)*v6;
    }
    else
    {
      v6 = (int *)v6[2];
    }
  }
  *a2 = v5;
  a2[1] = v3;
  return a2;
}



// ------------------------------------------------------------
// 0x47C150 sub_47C150
// ------------------------------------------------------------
int /*cdecl*/ sub_47C150(uint32_t *a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  int result; // eax
  int v5; // eax
  int v6; // edx
  uint32_t v7[7]; // [esp+0h] [ebp-28h] BYREF
  int v8; // [esp+24h] [ebp-4h]

  v3 = a1;
  v7[6] = v7;
  v7[5] = a1;
  v8 = 0;
  while ( 1 )
  {
    result = a2;
    if ( a2 == 0 )
      break;
    v7[4] = v3;
    LOBYTE(v8) = 1;
    if ( v3 != nullptr )
    {
      *v3 = *a3;
      v7[3] = v3 + 1;
      sub_41A630((unsigned int)(v3 + 1));
      LOBYTE(v8) = 2;
      v3[1] = &vftbl_clong;
      v5 = sub_41A5E0((unsigned int)(a3 + 1));
      sub_41A590((unsigned int)(v3 + 1), v6, v5);
    }
    v3 += 5;
    LOBYTE(v8) = 0;
    --a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47C210 sub_47C210
// ------------------------------------------------------------
int /*cdecl*/ sub_47C210(int a1)
{
  int v1; // eax
  int v2; // eax

  if ( *(uint8_t *)(a1 + 120) != 0 )
  {
    v1 = 30;
  }
  else
  {
    v2 = *(uint32_t *)(a1 + 116);
    if ( v2 == 2 )
      v1 = 27;
    else
      v1 = v2 != 0 ? 28 : 41;
  }
  return sub_418DD0(v1);
}



// ------------------------------------------------------------
// 0x47C260 sub_47C260
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_47C260(uint32_t *a1, int a2, uint32_t *a3)
{
  sub_47C150(a1, a2, a3);
  return &a1[5 * a2];
}



// ------------------------------------------------------------
// 0x47C290 sub_47C290
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47C290(uint32_t **this, uint32_t *a2, uint32_t *a3)
{
  int v4; // edi
  int v5; // esi

  sub_47B4D0(a3 + 5, *(this + 2), a3);
  v4 = (int)*(this + 2);
  v5 = v4 - 20;
  do
  {
    sub_433350(v5);
    v5 += 20;
  }
  while ( v5 != v4 );
  *(this + 2) -= 5;
  *a2 = a3;
  return a2;
}



// ============================================================
// 【分区 11】物品/封印数据处理（0x47C2F0-0x47E720）
// 44 字节/条目的批量数据处理；SEAL_ON/SEAL_OFF 事件（0x47E000 附近）【推断】。
// ============================================================
// ------------------------------------------------------------
// 0x47C2F0 sub_47C2F0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_47C2F0(int this, uint32_t *Src, uint32_t *a3, uint32_t *a4, int a5)
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
  uint32_t *v17; // eax
  int v18; // ecx
  int v19; // eax
  unsigned int v20; // edi
  int v21; // ebx
  uint32_t *v23; // ebx
  const void *v24; // [esp-Ch] [ebp-34h]
  uint32_t *v25; // [esp-Ch] [ebp-34h]
  int v26; // [esp+0h] [ebp-28h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v28; // [esp+10h] [ebp-18h]
  unsigned int v29; // [esp+14h] [ebp-14h]
  int *v30; // [esp+18h] [ebp-10h]
  int v31; // [esp+24h] [ebp-4h]
  int Srca; // [esp+30h] [ebp+8h]
  void *Srcb; // [esp+30h] [ebp+8h]

  v6 = *(uint32_t *)(this + 4);
  v7 = a4 - a3;
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
      sub_434730(this);
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
        return (unsigned int)sub_6511B0(a3, a4, Src);
      }
      else
      {
        Srca = 4 * v7;
        sub_55E7F0(Src, v21, &Src[v7]);
        v23 = &a3[(*(uint32_t *)(this + 8) - (int)Src) >> 2];
        v25 = *(uint32_t **)(this + 8);
        v31 = 2;
        sub_497E70(v23, a4, v25);
        *(uint32_t *)(this + 8) += Srca;
        return (unsigned int)sub_6511B0(a3, v23, Src);
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
      v15 = 4 * (((int)Src - *(uint32_t *)(this + 4)) >> 2);
      v24 = *(const void **)(this + 4);
      Block = v14;
      v31 = 0;
      v16 = (char *)memcpy_0(v14, v24, v15);
      v17 = sub_497E70(a3, a4, &v16[v15]);
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
// 0x47C540 sub_47C540
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47C540(int this, int a2)
{
  uint32_t *v2; // eax
  uint32_t *v3; // edx
  uint32_t *v4; // esi

  v2 = *(uint32_t **)(this + 8);
  v3 = *(uint32_t **)(this + 12);
  if ( v2 == v3 )
    return nullptr;
  while ( 1 )
  {
    v4 = (uint32_t *)*v2;
    if ( *(uint32_t *)*v2 == a2 )
      break;
    v2 += 5;
    if ( v2 == v3 )
      return nullptr;
  }
  sub_47C290((uint32_t **)(this + 4), &a2, v2);
  return v4;
}



// ------------------------------------------------------------
// 0x47C580 sub_47C580
// ------------------------------------------------------------
int /*thiscall*/ sub_47C580(uint32_t *this, uint32_t *a2)
{
  uint32_t *v2; // eax
  uint32_t *v3; // edi
  int v4; // esi
  uint32_t *v6; // [esp+Ch] [ebp-8h] BYREF
  uint32_t *v7; // [esp+10h] [ebp-4h]

  sub_47C0E0(this, &v6, a2);
  v2 = v6;
  v3 = v7;
  v4 = 0;
  a2 = v6;
  if ( v6 != v7 )
  {
    do
    {
      ++v4;
      sub_41C5E0(&a2);
    }
    while ( a2 != v3 );
    v2 = v6;
  }
  sub_41D980(&a2, v2, v3);
  return v4;
}



// ------------------------------------------------------------
// 0x47C5E0 sub_47C5E0
// ------------------------------------------------------------
int /*thiscall*/ sub_47C5E0(int *this, char *a2, unsigned int a3, int *a4)
{
  int v5; // ecx
  int v6; // ebx
  unsigned int v7; // ecx
  int v9; // eax
  int v10; // eax
  unsigned int v11; // ecx
  int v12; // eax
  char *v13; // ebx
  int v14; // eax
  unsigned int v15; // edi
  int v16; // eax
  char *v17; // ecx
  int v19; // edi
  uint32_t *v21; // [esp-18h] [ebp-50h]
  int v22; // [esp-Ch] [ebp-44h]
  unsigned int v23; // [esp-8h] [ebp-40h]
  int v24; // [esp+0h] [ebp-38h] BYREF
  int v25; // [esp+Ch] [ebp-2Ch] BYREF
  void *v26[7]; // [esp+10h] [ebp-28h] BYREF
  int v27; // [esp+34h] [ebp-4h]
  char *v28; // [esp+40h] [ebp+8h]
  uint32_t *v29; // [esp+44h] [ebp+Ch]
  int v30; // [esp+48h] [ebp+10h]
  char *v31; // [esp+48h] [ebp+10h]

  v5 = *a4;
  v26[6] = &v24;
  v25 = v5;
  v26[5] = this;
  sub_46B080(v26, (unsigned int)(a4 + 1));
  v6 = *(this + 1);
  v7 = 0;
  v27 = 0;
  if ( v6 != 0 )
    v7 = (*(this + 3) - v6) / 20;
  if ( a3 != 0 )
  {
    if ( v6 != 0 )
      v9 = (*(this + 2) - v6) / 20;
    else
      v9 = 0;
    if ( 214748364 - v9 < a3 )
      sub_434730(this);
    if ( v6 != 0 )
      v10 = (*(this + 2) - v6) / 20;
    else
      v10 = 0;
    if ( v7 >= a3 + v10 )
    {
      v17 = (char *)*(this + 2);
      v31 = v17;
      if ( (v17 - a2) / 20 >= a3 )
      {
        v28 = &v17[-20 * a3];
        *(this + 2) = (int)sub_47B640(v28, v17, v17);
        sub_47B620(a2, v28, v31);
        sub_47B5E0(a2, &a2[20 * a3], &v25);
      }
      else
      {
        sub_47B640(a2, v17, &a2[20 * a3]);
        v23 = a3 - (*(this + 2) - (int)a2) / 20;
        v22 = *(this + 2);
        LOBYTE(v27) = 3;
        sub_47C260(v22, v23, &v25);
        v19 = 20 * a3 + *(this + 2);
        *(this + 2) = v19;
        v27 = 0;
        sub_47B5E0(a2, v19 - 20 * a3, &v25);
      }
    }
    else
    {
      if ( 214748364 - (v7 >> 1) >= v7 )
        v11 = (v7 >> 1) + v7;
      else
        v11 = 0;
      if ( v6 != 0 )
        v12 = (*(this + 2) - v6) / 20;
      else
        v12 = 0;
      if ( v11 < a3 + v12 )
        v11 = a3 + sub_45E580(this);
      v30 = 20 * v11;
      v13 = (char *)operator new(20 * v11);
      v21 = (uint32_t *)*(this + 1);
      v26[4] = v13;
      LOBYTE(v27) = 1;
      v29 = sub_47B640(v21, a2, v13);
      sub_47C150(v29, a3, &v25);
      sub_47B640(a2, (uint32_t *)*(this + 2), &v29[5 * a3]);
      v14 = *(this + 1);
      v27 = 0;
      if ( v14 != 0 )
        v14 = (*(this + 2) - v14) / 20;
      v15 = v14 + a3;
      v16 = *(this + 1);
      if ( v16 != 0 )
      {
        sub_434180(v16, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v13[v30];
      *(this + 2) = (int)&v13[20 * v15];
      *(this + 1) = (int)v13;
    }
  }
  v27 = -1;
  return sub_41A580(v26);
}


// ------------------------------------------------------------
// 0x47C8F0 sub_47C8F0
// ------------------------------------------------------------
int /*fastcall*/ sub_47C8F0(int a1, int a2, int a3, int a4)
{
  int v4; // esi
  int v5; // ecx
  int v6; // ebx
  int v8; // edi
  uint32_t *v9; // edi
  char *v10; // eax
  int v11; // edi

  v4 = *(uint32_t *)(a1 + 8);
  v5 = *(uint32_t *)(a1 + 12);
  if ( v4 == v5 )
    return 0;
  v6 = a3;
  while ( **(uint32_t **)v4 != a3 )
  {
    v4 += 20;
    if ( v4 == v5 )
      return 0;
  }
  v8 = a4;
  sub_41A590(v4 + 4, a2, a4);
  if ( v8 == 0 )
  {
    if ( (uint8_t)sub_546080(v6) == 0 )
    {
      v9 = *((uint32_t **)dword_8F8528 + 7);
      v10 = sub_422E70(463);
      sub_43BEE0(v9, (int)v10, -6567706, 0, -1);
    }
    *(uint8_t *)(*(uint32_t *)v4 + 320) = 1;
    if ( *(uint32_t *)(*(uint32_t *)v4 + 204) != -1 )
    {
      v11 = *(uint32_t *)(dword_8F7A24 + 20);
      a3 = *(uint32_t *)(*(uint32_t *)v4 + 204);
      sub_47C580((uint32_t *)(v11 + 88), &a3);
      sub_45C400((int **)v11);
    }
  }
  return *(uint32_t *)v4;
}



// ------------------------------------------------------------
// 0x47C9A0 sub_47C9A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47C9A0(uint32_t *this, int a2)
{
  int v3; // ecx
  unsigned int v4; // eax
  int v6; // [esp-14h] [ebp-34h]
  int v7; // [esp-10h] [ebp-30h]
  int v8; // [esp-Ch] [ebp-2Ch]
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
  if ( sub_4349E0(this, v4) != 0 )
  {
    v8 = *(this + 1);
    v7 = *(uint32_t *)(a2 + 8);
    v6 = *(uint32_t *)(a2 + 4);
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, v8);
  }
  return this;
}



// ------------------------------------------------------------
// 0x47CA40 sub_47CA40
// ------------------------------------------------------------
int /*thiscall*/ sub_47CA40(int this, int a2)
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
  unsigned int v14; // eax

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
    if ( sub_4349E0((uint32_t *)this, v14) != 0 )
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
// 0x47CB90 sub_47CB90
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47CB90(int *this, uint32_t *a2, char *a3, int *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 20 != 0 )
    v6 = (int)&a3[-v5] / 20;
  else
    v6 = 0;
  sub_47C5E0(this, a3, 1u, a4);
  *a2 = *(this + 1) + 20 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x47CC00 sub_47CC00
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47CC00(int this)
{
  uint32_t *v2; // eax
  uint32_t *result; // eax

  sub_4349A0((int *)(this + 4));
  if ( *(uint32_t *)(this + 24) != 0 )
    j__free(*(void **)(this + 24));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  sub_435BA0(*(void ***)(*(uint32_t *)(this + 40) + 4));
  *(uint32_t *)(*(uint32_t *)(this + 40) + 4) = *(uint32_t *)(this + 40);
  v2 = *(uint32_t **)(this + 40);
  *(uint32_t *)(this + 44) = 0;
  *v2 = v2;
  *(uint32_t *)(*(uint32_t *)(this + 40) + 8) = *(uint32_t *)(this + 40);
  sub_41CA60(*(void **)(*(uint32_t *)(this + 52) + 4));
  *(uint32_t *)(*(uint32_t *)(this + 52) + 4) = *(uint32_t *)(this + 52);
  result = *(uint32_t **)(this + 52);
  *(uint32_t *)(this + 56) = 0;
  *result = result;
  *(uint32_t *)(*(uint32_t *)(this + 52) + 8) = *(uint32_t *)(this + 52);
  return result;
}



// ------------------------------------------------------------
// 0x47CC80 sub_47CC80
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47CC80(int **this, uint32_t *a2, int a3)
{
  int *v5; // [esp-4h] [ebp-2Ch]
  char v6; // [esp+8h] [ebp-20h] BYREF
  int v7; // [esp+Ch] [ebp-1Ch]
  int v8; // [esp+10h] [ebp-18h]
  int v9; // [esp+14h] [ebp-14h]
  int *v10[4]; // [esp+18h] [ebp-10h] BYREF

  v10[0] = nullptr;
  sub_45B6D0(this + 9, v10, &a3);
  if ( v10[0] == *(this + 10) )
  {
    v7 = 0;
    v8 = 0;
    v9 = 0;
    v10[3] = nullptr;
    v5 = (int *)&v6;
  }
  else
  {
    v5 = v10[0] + 4;
  }
  sub_47C9A0(a2, (int)v5);
  return a2;
}



// ------------------------------------------------------------
// 0x47CD00 sub_47CD00
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_47CD00(uint32_t *this)
{
  uint32_t *v1; // esi
  unsigned int v2; // edi
  unsigned int result; // eax
  int v4; // eax
  uint32_t *v5; // ebx
  unsigned int v6; // eax
  int v7; // ecx
  signed int v8; // edi
  signed int v9; // esi
  int v10; // eax
  int v11; // ecx
  uint32_t *v12; // eax
  int v13; // ebx
  int v14; // ecx
  int v15; // esi
  uint32_t *v16; // edi
  int v17; // ecx
  int v18; // ebx
  int v19; // eax
  int v20; // esi
  uint32_t *v21; // edi
  unsigned int v22; // ebx
  int j; // esi
  int v24; // [esp-8h] [ebp-58h]
  char v25[4]; // [esp+Ch] [ebp-44h] BYREF
  void *Block; // [esp+10h] [ebp-40h]
  int v27; // [esp+14h] [ebp-3Ch]
  uint32_t v28[2]; // [esp+18h] [ebp-38h] BYREF
  uint32_t *v29; // [esp+20h] [ebp-30h] BYREF
  char v30[4]; // [esp+24h] [ebp-2Ch] BYREF
  int v31; // [esp+28h] [ebp-28h] BYREF
  uint32_t *v32; // [esp+2Ch] [ebp-24h] BYREF
  int v33; // [esp+30h] [ebp-20h] BYREF
  int i; // [esp+34h] [ebp-1Ch]
  unsigned int v35; // [esp+38h] [ebp-18h]
  uint32_t *v36; // [esp+3Ch] [ebp-14h]
  uint32_t *v37; // [esp+40h] [ebp-10h]
  int v38; // [esp+4Ch] [ebp-4h]

  v1 = this;
  v2 = 0;
  v36 = this;
  for ( i = 0; ; i += 20 )
  {
    result = v1[2];
    v35 = v2;
    if ( result == 0 )
      break;
    result = (int)(v1[3] - result) / 20;
    if ( v2 >= result )
      break;
    v4 = v1[2];
    if ( v4 != 0 && v2 < (v1[3] - v4) / 20 )
    {
      v5 = *(uint32_t **)(i + v1[2]);
      v37 = v5;
    }
    else
    {
      v37 = nullptr;
      v5 = nullptr;
    }
    if ( v5[68] == 0 && dword_8F7C04 != 0 && sub_463F10(v2) != -1 )
    {
      Block = (void *)sub_433AC0(v25);
      *((uint8_t *)Block + 21) = 1;
      *((uint32_t *)Block + 1) = Block;
      *(uint32_t *)Block = Block;
      *((uint32_t *)Block + 2) = Block;
      v6 = 0;
      v27 = 0;
      v7 = v5[71];
      v38 = 0;
      if ( v7 != 0 )
        v6 = (v5[72] - v7) >> 2;
      v8 = v6 >> 1;
      v9 = 0;
      if ( v6 >> 1 != 0 )
      {
        do
        {
          v10 = v5[71];
          v11 = *(uint32_t *)(v10 + 8 * v9);
          v28[1] = *(uint32_t *)(v10 + 8 * v9 + 4);
          v28[0] = v11;
          sub_4682D0(v30, v28);
          ++v9;
        }
        while ( v9 < v8 );
      }
      v12 = dword_8F852C;
      v13 = 0;
      v31 = *((uint32_t *)dword_8F852C + 2);
      if ( v31 > 0 )
      {
        while ( 1 )
        {
          if ( v13 < v12[2] )
          {
            v14 = v12[3];
            v15 = *(uint32_t *)(v14 + 4 * v13);
            if ( v15 != 0 )
            {
              v33 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v15 + 16))(*(uint32_t *)(v14 + 4 * v13)) + 4);
              sub_472E30(&v32, &v33);
              v16 = v32;
              if ( v32 != Block )
              {
                if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 44))(v15) < v16[4] )
                  v16[4] -= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 44))(v15);
                else
                  sub_41D610(&v33, v16);
              }
            }
          }
          if ( ++v13 >= v31 )
            break;
          v12 = dword_8F852C;
        }
      }
      v17 = dword_8F7C04;
      v31 = dword_8F7C04;
      v18 = 0;
      while ( 1 )
      {
        v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v17 + 792))(v17, v18);
        v20 = v19;
        if ( v19 != 0 )
        {
          v33 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 16))(v19) + 4);
          sub_472E30(&v29, &v33);
          v21 = v29;
          if ( v29 != Block )
          {
            if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 44))(v20) < v21[4] )
              v21[4] -= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 44))(v20);
            else
              sub_41D610(&v33, v21);
          }
        }
        if ( ++v18 >= 18 )
          break;
        v17 = v31;
      }
      if ( v27 != 0 )
      {
        if ( sub_463F10(v35) == 0 )
          sub_47B8D0(*v37, 1);
      }
      else
      {
        v22 = v35;
        if ( (int)sub_463F10(v35) > 0 )
        {
          for ( j = 0; j < sub_463F10(v22); ++j )
            sub_47B8D0(*v37, 0);
        }
      }
      v24 = *(uint32_t *)Block;
      v38 = -1;
      sub_41D980(&v31, v24, Block);
      j__free(Block);
      v2 = v35;
      v1 = v36;
      Block = nullptr;
      v27 = 0;
    }
    ++v2;
  }
  return result;
}


// ------------------------------------------------------------
// 0x47CFD0 sub_47CFD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47CFD0(int this, int *a2)
{
  int v3; // edi
  unsigned int v4; // ecx
  uint32_t *v5; // edi
  uint32_t *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 20;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 20 )
    return sub_47CB90((int *)this, &a2, *(char **)(this + 8), a2);
  v5 = *(uint32_t **)(this + 8);
  result = (uint32_t *)sub_47C150(v5, 1, a2);
  *(uint32_t *)(this + 8) = v5 + 5;
  return result;
}



// ------------------------------------------------------------
// 0x47D060 sub_47D060
// ------------------------------------------------------------
int /*thiscall*/ sub_47D060(unsigned int *this, uint32_t *a2, int a3)
{
  int v4; // eax
  int v5; // edi
  int v7; // ebx
  uint32_t *v8; // eax
  uint32_t *v9; // esi
  int v10; // esi
  int v11; // edx
  int v12; // eax
  int v13; // edx
  unsigned int *v14; // edi
  int **v15; // esi
  uint32_t *v16; // edi
  int v17; // [esp+8h] [ebp-34h] BYREF
  uint32_t v18[4]; // [esp+Ch] [ebp-30h] BYREF
  uint32_t v19[3]; // [esp+1Eh] [ebp-1Eh] BYREF
  unsigned int *v20; // [esp+2Ch] [ebp-10h]
  int v21; // [esp+38h] [ebp-4h]

  v4 = *(this + 2);
  v5 = (int)(this + 1);
  v20 = this;
  if ( v4 != 0 && (unsigned int)((int)(*(this + 3) - v4) / 20) >= 3 )
    return 0;
  v7 = sub_4CE8A0(a2);
  if ( v7 == 0 )
    return 0;
  v8 = (uint32_t *)*(this + 2);
  v9 = (uint32_t *)*(this + 3);
  if ( v8 != v9 )
  {
    while ( *v8 != v7 )
    {
      v8 += 5;
      if ( v8 == v9 )
        goto LABEL_9;
    }
    return 0;
  }
LABEL_9:
  sub_41A630((unsigned int)v19);
  v10 = a3;
  v21 = 0;
  v19[0] = &vftbl_clong;
  sub_41A590((unsigned int)v19, v11, a3);
  v21 = 1;
  v17 = v7;
  a2 = v18;
  sub_41A630((unsigned int)v18);
  LOBYTE(v21) = 2;
  v18[0] = &vftbl_clong;
  v12 = sub_41A5E0((unsigned int)v19);
  sub_41A590((unsigned int)v18, v13, v12);
  LOBYTE(v21) = 3;
  sub_47CFD0(v5, &v17);
  LOBYTE(v21) = 1;
  sub_41A580(v18);
  v21 = -1;
  sub_41A580(v19);
  if ( v10 == 0 )
    *(uint8_t *)(v7 + 320) = 1;
  v14 = v20;
  sub_47CD00(v20);
  sub_47BAA0(v14);
  if ( *(uint32_t *)(v7 + 204) != -1 && v10 != 0 )
  {
    v15 = *(int ***)(dword_8F7A24 + 20);
    a2 = *(uint32_t **)(v7 + 204);
    v16 = a2;
    *(uint32_t *)sub_468BA0(v15 + 22, (int *)&a2) = v16;
    sub_45C400(v15);
  }
  return v7;
}



// ------------------------------------------------------------
// 0x47D1E0 sub_47D1E0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_47D1E0(int *this, unsigned int a2)
{
  unsigned int result; // eax

  result = sub_4CE8A0(a2);
  a2 = result;
  if ( result != 0 )
    return sub_44E2F0(this + 5, (int *)&a2);
  return result;
}



// ------------------------------------------------------------
// 0x47D210 sub_47D210
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47D210(uint32_t *this, uint32_t *a2, int a3)
{
  signed int v3; // esi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  uint8_t *v8; // ecx
  unsigned int v9; // esi
  int *v10; // eax
  int *v11; // esi
  int i; // edi
  uint8_t v14[36]; // [esp+Ch] [ebp-5Ch] BYREF
  char v15; // [esp+30h] [ebp-38h] BYREF
  uint8_t v16[4]; // [esp+3Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+40h] [ebp-28h]
  void *Src; // [esp+44h] [ebp-24h]
  int v19; // [esp+48h] [ebp-20h]
  int v20; // [esp+4Ch] [ebp-1Ch]
  int v21; // [esp+50h] [ebp-18h] BYREF
  int v22; // [esp+54h] [ebp-14h]
  signed int v23; // [esp+58h] [ebp-10h]
  int v24; // [esp+64h] [ebp-4h]

  v3 = 0;
  v20 = 0;
  `eh vector constructor iterator'(v14, 0x10u, 3, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  v5 = *(this + 6);
  v24 = 1;
  if ( v5 != 0 )
    v22 = (*(this + 7) - v5) >> 2;
  else
    v22 = 0;
  v23 = 0;
  if ( v22 > 0 )
  {
    do
    {
      if ( sub_47B720(this, v3, a3) != 0 )
      {
        v6 = *(uint32_t *)(*(this + 6) + 4 * v3);
        v7 = *(uint32_t *)&v14[16 * *(uint32_t *)(v6 + 116) + 4];
        v8 = &v14[16 * *(uint32_t *)(v6 + 116)];
        v21 = v6;
        if ( v7 != 0 )
          v9 = (*((uint32_t *)v8 + 2) - v7) >> 2;
        else
          v9 = 0;
        if ( v7 != 0 && v9 < (*((uint32_t *)v8 + 3) - v7) >> 2 )
        {
          v10 = *((int **)v8 + 2);
          *v10 = v6;
          *((uint32_t *)v8 + 2) = v10 + 1;
        }
        else
        {
          sub_44CFA0((int)v8, *((uint32_t *)v8 + 2), 1u, &v21);
        }
        v3 = v23;
      }
      v23 = ++v3;
    }
    while ( v3 < v22 );
  }
  Block = nullptr;
  Src = nullptr;
  v19 = 0;
  LOBYTE(v24) = 2;
  v11 = (int *)&v15;
  for ( i = 3; i != 0; --i )
  {
    sub_47C2F0((int)v16, (char *)Src, *v11, v11[1], a3);
    v11 -= 4;
  }
  sub_47C9A0(a2, (int)v16);
  v20 = 1;
  if ( Block != nullptr )
    j__free(Block);
  LOBYTE(v24) = 0;
  `eh vector destructor iterator'(v14, 0x10u, 3, (void (/*thiscall*/ *)(void *))sub_5E5260);
  return a2;
}



// ------------------------------------------------------------
// 0x47D370 sub_47D370
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_47D370(int a1, int a2, int a3, uint32_t *a4, char a5)
{
  uint32_t *v5; // eax
  uint32_t *v6; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  v5 = operator new(0x24u);
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
    sub_47C9A0(v5 + 4, (int)(a4 + 1));
    *((uint8_t *)v6 + 32) = a5;
    *((uint8_t *)v6 + 33) = 0;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x47D410 sub_47D410
// ------------------------------------------------------------
void */*thiscall*/ sub_47D410(void **this, int *a2, int a3)
{
  char v3; // al
  uint32_t *v4; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);
  v3 = *((uint8_t *)a2 + 33);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    v4 = sub_47D370((int)*(this + 1), a3, (int)*(this + 1), a2 + 3, *((uint8_t *)a2 + 32));
    if ( *((uint8_t *)Block + 33) != 0 )
      Block = v4;
    v6 = *a2;
    v10 = 0;
    *v4 = sub_47D410(v6, v4);
    v4[2] = sub_47D410(a2[2], v4);
  }
  return Block;
}



// ------------------------------------------------------------
// 0x47D4C0 sub_47D4C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47D4C0(int *this, uint32_t *a2, char a3, uint32_t *a4, uint32_t *a5)
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

  if ( (unsigned int)*(this + 2) >= 0xCCCCCCB )
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
  v6 = sub_47D370(*(this + 1), (int)a4, *(this + 1), a5, 0);
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
  if ( *(uint8_t *)(v6[1] + 32) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 32) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_4331B0(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 32) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 32) = 0;
          sub_433230(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 32) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_433230(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 32) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 32) = 0;
        sub_4331B0(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 32) = 1;
      *(uint8_t *)(v14 + 32) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 32) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 32) != 0 )
      {
        v6 = v21;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 32) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x47D670 sub_47D670
// ------------------------------------------------------------
int */*thiscall*/ sub_47D670(int this, int a2)
{
  int v3; // edi
  int **v4; // edx
  int *result; // eax
  int *v6; // ecx
  int v7; // esi
  int **v8; // ecx

  v3 = *(uint32_t *)(this + 4);
  *(uint32_t *)(v3 + 4) = sub_47D410((void **)this, *(int **)(*(uint32_t *)(a2 + 4) + 4), v3);
  *(uint32_t *)(this + 8) = *(uint32_t *)(a2 + 8);
  v4 = *(int ***)(this + 4);
  result = v4[1];
  if ( *((uint8_t *)result + 33) != 0 )
  {
    *v4 = (int *)v4;
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);
  }
  else
  {
    v6 = (int *)*result;
    if ( *(uint8_t *)(*result + 33) == 0 )
    {
      do
      {
        result = v6;
        v6 = (int *)*v6;
      }
      while ( *((uint8_t *)v6 + 33) == 0 );
    }
    *v4 = result;
    v7 = *(uint32_t *)(this + 4);
    v8 = *(int ***)(v7 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 33) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(v7 + 8) = v8;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47D700 sub_47D700
// ------------------------------------------------------------
int /*thiscall*/ sub_47D700(int *this, int a2, uint32_t *a3)
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
  if ( *((uint8_t *)v6 + 33) == 0 )
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
    while ( *((uint8_t *)v6 + 33) == 0 );
  }
  v9 = v5;
  a3 = v5;
  if ( v7 )
  {
    if ( v5 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_47D4C0(this, &a3, 1, v5, v3);
      *(uint8_t *)(a2 + 4) = 1;
      *(uint32_t *)a2 = v10;
      return a2;
    }
    sub_45B1F0(&a3);
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
    v12 = *sub_47D4C0(this, &a3, v13, v5, v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x47D7C0 sub_47D7C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47D7C0(int this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v6; // eax
  uint32_t *v7; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_47D4C0((int *)this, a2, 1, *(uint32_t **)(this + 4), a4);
    return a2;
  }
  v6 = *(uint32_t **)(this + 4);
  v7 = a4;
  if ( a3 == (uint32_t *)*v6 )
  {
    if ( *a4 < a3[3] )
    {
      sub_47D4C0((int *)this, a2, 1, a3, a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( a3 == v6 )
  {
    v8 = (uint32_t *)v6[2];
    if ( v8[3] < *a4 )
    {
      sub_47D4C0((int *)this, a2, 0, v8, a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( *a4 >= a3[3] || (a4 = a3, sub_45B1F0(&a4), a4[3] >= *v7) )
  {
    if ( a3[3] >= *v7 || (a4 = a3, sub_41C640(&a4), a4 != *(uint32_t **)(this + 4)) && *v7 >= a4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_47D700((int *)this, (int)v10, v7);
      *a2 = v9;
      return a2;
    }
    if ( *(uint8_t *)(a3[2] + 33) != 0 )
      sub_47D4C0((int *)this, a2, 0, a3, v7);
    else
      sub_47D4C0((int *)this, a2, 1, a4, v7);
    return a2;
  }
  else
  {
    if ( *(uint8_t *)(a4[2] + 33) != 0 )
      sub_47D4C0((int *)this, a2, 0, a4, v7);
    else
      sub_47D4C0((int *)this, a2, 1, a3, v7);
    return a2;
  }
}



// ------------------------------------------------------------
// 0x47D920 sub_47D920
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_47D920(uint32_t *this, int *a2)
{
  uint32_t *v3; // ecx
  int *v4; // eax
  uint32_t *v5; // esi
  int v7; // [esp+Ch] [ebp-30h] BYREF
  int v8; // [esp+10h] [ebp-2Ch] BYREF
  void *Block; // [esp+14h] [ebp-28h]
  uint8_t v10[4]; // [esp+20h] [ebp-1Ch] BYREF
  int v11; // [esp+24h] [ebp-18h]
  int v12; // [esp+28h] [ebp-14h]
  int v13; // [esp+2Ch] [ebp-10h]
  int v14; // [esp+38h] [ebp-4h]

  v3 = (uint32_t *)*(this + 1);
  v4 = (int *)v3[1];
  v5 = v3;
  while ( *((uint8_t *)v4 + 33) == 0 )
  {
    if ( v4[3] >= *a2 )
    {
      v5 = v4;
      v4 = (int *)*v4;
    }
    else
    {
      v4 = (int *)v4[2];
    }
  }
  if ( v5 == (uint32_t *)*(this + 1) || *a2 < v5[3] )
  {
    v11 = 0;
    v12 = 0;
    v13 = 0;
    v7 = *a2;
    v14 = 0;
    sub_47C9A0(&v8, (int)v10);
    LOBYTE(v14) = 1;
    v5 = (uint32_t *)*sub_47D7C0((int)this, &a2, v5, &v7);
    if ( Block != nullptr )
      j__free(Block);
  }
  return v5 + 4;
}



// ------------------------------------------------------------
// 0x47D9D0 sub_47D9D0
// ------------------------------------------------------------
void /*thiscall*/ sub_47D9D0(uint32_t *this)
{
  uint32_t *v1; // ebx
  int v2; // esi
  int v3; // edi
  void **v4; // eax
  int *j; // esi
  int v6; // eax
  int v7; // ebx
  int *k; // eax
  int v9; // ecx
  bool v10; // dl
  int *m; // edx
  uint32_t *v12; // ecx
  uint32_t *v13; // eax
  int v14; // eax
  bool v15; // cl
  int **v16; // eax
  int *ii; // eax
  int *n; // eax
  int *v19; // [esp-8h] [ebp-48h]
  int v20; // [esp-4h] [ebp-44h]
  char v21[4]; // [esp+Ch] [ebp-34h] BYREF
  void *Block; // [esp+10h] [ebp-30h]
  int v23; // [esp+14h] [ebp-2Ch]
  int v24; // [esp+18h] [ebp-28h]
  char v25[4]; // [esp+1Ch] [ebp-24h] BYREF
  void *v26; // [esp+20h] [ebp-20h]
  int v27; // [esp+24h] [ebp-1Ch]
  int v28; // [esp+28h] [ebp-18h] BYREF
  uint32_t *v29; // [esp+2Ch] [ebp-14h]
  int v30; // [esp+30h] [ebp-10h] BYREF
  int i; // [esp+3Ch] [ebp-4h]

  v1 = this;
  v29 = this;
  v26 = (void *)sub_433B40(v25);
  *((uint8_t *)v26 + 33) = 1;
  *((uint32_t *)v26 + 1) = v26;
  *(uint32_t *)v26 = v26;
  *((uint32_t *)v26 + 2) = v26;
  v27 = 0;
  v2 = v1[6];
  for ( i = 0; v2 != v1[7]; v2 += 4 )
  {
    v3 = *(uint32_t *)(*(uint32_t *)v2 + 124);
    v30 = v3;
    v4 = (void **)sub_45B6D0(&v28, &v30);
    if ( *v4 == v26 )
    {
      v20 = sub_47D210(v21, v3);
      LOBYTE(i) = 1;
      sub_47D920(&v30);
      sub_47CA40(v20);
      LOBYTE(i) = 0;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v23 = 0;
      v24 = 0;
    }
  }
  for ( j = *(int **)v26; j != v26; v1 = v29 )
  {
    v30 = j[3];
    sub_45B6D0(&v28, &v30);
    v6 = v1[10];
    v7 = v28;
    if ( v28 == v6 )
    {
      for ( k = (int *)j[5]; k != (int *)j[6]; ++k )
      {
        v9 = *k;
        v10 = *(uint32_t *)(*k + 116) == 2 || *(uint8_t *)(v9 + 120) != 0;
        *(uint8_t *)(v9 + 320) = v10;
      }
    }
    else
    {
      for ( m = (int *)j[5]; m != (int *)j[6]; ++m )
      {
        v12 = *(uint32_t **)(v7 + 24);
        v13 = *(uint32_t **)(v7 + 20);
        if ( v13 != v12 )
        {
          do
          {
            if ( *v13 == *m )
              break;
            ++v13;
          }
          while ( v13 != v12 );
          if ( v13 != v12 )
            continue;
        }
        v14 = *m;
        v15 = *(uint32_t *)(*m + 116) == 2 || *(uint8_t *)(v14 + 120) != 0;
        *(uint8_t *)(v14 + 320) = v15;
      }
    }
    if ( *((uint8_t *)j + 33) == 0 )
    {
      v16 = (int **)j[2];
      if ( *((uint8_t *)v16 + 33) != 0 )
      {
        for ( n = (int *)j[1]; *((uint8_t *)n + 33) == 0; n = (int *)n[1] )
        {
          if ( j != (int *)n[2] )
            break;
          j = n;
        }
        j = n;
      }
      else
      {
        j = (int *)j[2];
        for ( ii = *v16; *((uint8_t *)ii + 33) == 0; ii = (int *)*ii )
          j = ii;
      }
    }
  }
  if ( v1 + 9 != (uint32_t *)v25 )
  {
    sub_437990(&v28, *(uint32_t *)v1[10], v1[10]);
    sub_47D670(v25);
  }
  v19 = *(int **)v26;
  i = -1;
  sub_437990(&v28, v19, v26);
  j__free(v26);
}


// ------------------------------------------------------------
// 0x47DC00 sub_47DC00
// ------------------------------------------------------------
int /*thiscall*/ sub_47DC00(uint32_t *this)
{
  uint32_t *v1; // esi
  int i; // ebx

  *(this + 135) = 0;
  v1 = this + 124;
  for ( i = 2; i != 0; --i )
  {
    sub_41A590(0);
    v1 = (uint32_t *)((char *)v1 + 14);
  }
  sub_41A590(1065353216);
  sub_41A590(1);
  sub_41A590(0);
  sub_41A590(0);
  sub_41A590(0);
  return sub_41A590(0);
}



// ------------------------------------------------------------
// 0x47DC90 sub_47DC90
// ------------------------------------------------------------
int /*cdecl*/ sub_47DC90(int a1)
{
  int v1; // eax

  v1 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  return sub_47E720(*(uint32_t *)(v1 + 44), a1);
}



// ------------------------------------------------------------
// 0x47DCD0 sub_47DCD0
// ------------------------------------------------------------
int /*thiscall*/ sub_47DCD0(int *this, int a2, int a3)
{
  int result; // eax
  int v5; // edi
  int v6; // eax

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 80))(a2);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 80))(a2);
    if ( *(uint32_t *)(result + 132) != 0 )
    {
      v5 = a3;
      if ( a3 == -1 )
        v5 = *(this + 115);
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 80))(a2);
      return sub_424120(*(uint32_t **)(v6 + 132), *(this + 114), v5);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x47DD30 sub_47DD30
// ------------------------------------------------------------
int /*stdcall*/ sub_47DD30(int a1)
{
  int result; // eax
  int v2; // eax

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 80))(a1);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 80))(a1);
    if ( *(uint32_t *)(result + 132) != 0 )
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 80))(a1);
      return sub_424120(*(uint32_t **)(v2 + 132), 0, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x47DD70 sub_47DD70
// ------------------------------------------------------------
int /*thiscall*/ sub_47DD70(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 14;
  return result;
}



// ------------------------------------------------------------
// 0x47DDA0 sub_47DDA0
// ------------------------------------------------------------
void /*cdecl*/ sub_47DDA0(unsigned int a1, int a2, unsigned int a3)
{
  unsigned int i; // esi
  int v4; // eax
  int v5; // edx

  for ( i = a1; i != a2; i += 14 )
  {
    v4 = sub_41A5E0(a3);
    sub_41A590(i, v5, v4);
  }
}



// ------------------------------------------------------------
// 0x47DDD0 sub_47DDD0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_47DDD0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax
  uint32_t *v5; // edi
  int v6; // esi

  v3 = a1;
  for ( result = a3; v3 != a2; v5[2] = v6 )
  {
    v5 = result;
    *result = *v3;
    result[1] = v3[1];
    v6 = v3[2];
    v3 += 3;
    result += 3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47DE10 sub_47DE10
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_47DE10(unsigned int a1, int a2, unsigned int a3)
{
  unsigned int v3; // esi
  unsigned int v4; // edi
  int v5; // eax
  int v6; // edx

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v5 = sub_41A5E0(v3);
    sub_41A590(v4, v6, v5);
    v3 += 14;
    v4 += 14;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x47DE50 sub_47DE50
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_47DE50(int a1, unsigned int a2, unsigned int a3)
{
  unsigned int v3; // esi
  unsigned int v4; // edi
  int v5; // eax
  int v6; // edx

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v3 -= 14;
    v4 -= 14;
    v5 = sub_41A5E0(v3);
    sub_41A590(v4, v6, v5);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x47DE90 sub_47DE90
// ------------------------------------------------------------
int /*thiscall*/ sub_47DE90(void *this, int a2)
{
  int v3; // edi

  v3 = sub_41A5E0((unsigned int)this + 64);
  return v3 + (a2 - 1) * sub_41A5E0((unsigned int)this + 78);
}



// ------------------------------------------------------------
// 0x47DEC0 sub_47DEC0
// ------------------------------------------------------------
int /*thiscall*/ sub_47DEC0(void *this, int a2, int a3)
{
  return sub_41A590((unsigned int)this + 14 * a2 + 496, 14 * a2, a3);
}



// ------------------------------------------------------------
// 0x47DEE0 sub_47DEE0
// ------------------------------------------------------------
int /*thiscall*/ sub_47DEE0(void *this, int a2)
{
  if ( *(float *)&a2 <= 0.0 )
    return sub_41A590((unsigned int)this + 524, 0, 0);
  else
    return sub_41A590((unsigned int)this + 524, a2, a2);
}



// ------------------------------------------------------------
// 0x47DF30 sub_47DF30
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_47DF30(void *this)
{
  return sub_41A5E0((unsigned int)this + 544) != 0;
}



// ------------------------------------------------------------
// 0x47DF50 sub_47DF50
// ------------------------------------------------------------
void /*thiscall*/ sub_47DF50(uint32_t *this, int a2, int a3, int Value, int a5, char a6, char a7, char a8)
{
  int v9; // eax
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // edi
  int v14; // edi
  int v15; // ecx
  int v16; // edi
  int v17; // esi
  int v18; // eax

  if ( a8 != 0 && sub_699000((int)(this + 147)) < 1500 )
  {
    v9 = sub_41A5E0((unsigned int)(this + 124));
    v10 = (int)(this + 147);
    if ( v9 == 1 )
    {
      if ( ((sub_699000(v10) / 0xFAu) & 1) != 0 )
        return;
    }
    else if ( ((sub_699000(v10) / 0xFAu) & 1) == 0 )
    {
      return;
    }
  }
  if ( sub_41A5E0((unsigned int)(this + 143)) != 0 && a6 == 0 )
  {
    if ( *((uint32_t *)dword_8F8528 + 626) == 1 && *((uint32_t *)dword_8F8528 + 628) == sub_41A5E0((unsigned int)(this + 1)) )
      return;
    sub_41A590((unsigned int)(this + 143), v11, 0);
  }
  v12 = *(this + (a5 == 1) + 95);
  if ( v12 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(v12, a2, a3, dword_79C0B0);
  v13 = 0;
  if ( a5 != 1 )
  {
    if ( Value == -1 )
    {
      v14 = sub_41A5E0((unsigned int)(this + 124));
      if ( v14 < sub_41A5E0((unsigned int)this + 510) )
      {
        v13 = 3;
LABEL_20:
        Value = sub_41A5E0((unsigned int)this + 510);
        goto LABEL_21;
      }
    }
    v13 = (*(this + 31) != 0) + 1;
  }
  if ( Value == -1 )
    goto LABEL_20;
LABEL_21:
  v15 = dword_99FC08[v13];
  if ( v15 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v15 + 152))(v15, a2 + 10, a3, dword_79C0B0);
  sub_69A110(a2 + 28, a3, Value, -1);
  if ( sub_41A5E0((unsigned int)this + 558) != 0 && dword_99FC28 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_99FC28 + 152))(dword_99FC28, a2, a3, dword_79C0B0);
  if ( a5 == 2 && dword_9B0C5C != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)dword_9B0C5C + 128))(
      dword_9B0C5C,
      a2,
      a3,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      1308622847,
      1333788672,
      1333788672);
  if ( a7 != 0 )
  {
    v16 = sub_41A5E0((unsigned int)this + 630);
    v17 = sub_41A5E0((unsigned int)(this + 154));
    v18 = sub_699000((int)&unk_99FC80);
    sub_4F2E80(a2, a3, v17, v16 - v18);
  }
}



// ------------------------------------------------------------
// 0x47E170 sub_47E170
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_47E170(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_47DDD0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x47E190 sub_47E190
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_47E190(unsigned int a1, int a2, unsigned int a3)
{
  return sub_47DE10(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x47E1B0 sub_47E1B0
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_47E1B0(int a1, unsigned int a2, unsigned int a3)
{
  return sub_47DE50(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x47E1D0 sub_47E1D0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_47E1D0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax

  v3 = a1;
  for ( result = a3; v3 != a2; result += 2 )
  {
    *result = *v3;
    result[1] = v3[1];
    v3 += 2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47E200 sub_47E200
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_47E200(unsigned int a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  int v5; // eax
  int v6; // edx
  uint32_t v8[5]; // [esp+0h] [ebp-20h] BYREF
  int v9; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v8[4] = v8;
  v8[3] = a3;
  v9 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v9) = 1;
    if ( v3 != nullptr )
    {
      sub_41A630((unsigned int)v3);
      LOBYTE(v9) = 2;
      *v3 = &vftbl_clong;
      v5 = sub_41A5E0(a1);
      sub_41A590((unsigned int)v3, v6, v5);
    }
    v3 = (uint32_t *)((char *)v3 + 14);
    LOBYTE(v9) = 0;
    a1 += 14;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x47E2B0 sub_47E2B0
// ------------------------------------------------------------
int /*fastcall*/ sub_47E2B0(int a1, int a2)
{
  int *v2; // edi
  int v3; // ebx
  int result; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // [esp+Ch] [ebp-4h]

  v2 = &dword_99FC34;
  do
  {
    v3 = 0;
    if ( *v2 != 0 )
    {
      result = (v2[1] - *v2) >> 2;
      v7 = result;
    }
    else
    {
      v7 = 0;
    }
    if ( v7 > 0 )
    {
      do
      {
        v5 = *(uint32_t *)(*v2 + 4 * v3);
        if ( v5 != 0 )
        {
          *(uint32_t *)(v5 + 540) = 0;
          sub_41A590(*(uint32_t *)(*v2 + 4 * v3) + 496, a2, 0);
          sub_41A590(*(uint32_t *)(*v2 + 4 * v3) + 510, v6, 0);
        }
        result = v7;
        ++v3;
      }
      while ( v3 < v7 );
    }
    v2 += 4;
  }
  while ( (int)v2 < (int)dword_99FC74 );
  return result;
}



// ------------------------------------------------------------
// 0x47E340 sub_47E340
// ------------------------------------------------------------
int /*thiscall*/ sub_47E340(uint32_t *this)
{
  int v3; // eax
  int v4; // esi
  int v5; // ebx
  int i; // edi

  if ( sub_41A5E0((unsigned int)this + 558) != 0 )
    return -1;
  v3 = *(this + 98);
  if ( v3 != 0 )
    v4 = (*(this + 99) - v3) / 44;
  else
    v4 = 0;
  v5 = 0;
  if ( v4 <= 0 )
    return -1;
  for ( i = 0; (uint8_t)CNCommandChecker__vmt48(i + *(this + 98), 1) == 0; i += 44 )
  {
    if ( ++v5 >= v4 )
      return -1;
  }
  if ( v4 == 1 )
    return 4;
  else
    return v5 == 0;
}



// ------------------------------------------------------------
// 0x47E3E0 sub_47E3E0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_47E3E0(unsigned int *this)
{
  unsigned int v1; // edi
  int i; // ebx
  unsigned int result; // eax

  v1 = 0;
  for ( i = 0; ; i += 44 )
  {
    result = *(this + 98);
    if ( result == 0 )
      break;
    result = (int)(*(this + 99) - result) / 44;
    if ( v1 >= result )
      break;
    CNCommandChecker__vmt50(i + *(this + 98));
    ++v1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47E440 sub_47E440
// ------------------------------------------------------------
char /*thiscall*/ sub_47E440(unsigned int *this, uint8_t a2)
{
  unsigned int v3; // edi
  bool v4; // zf
  unsigned int v5; // eax
  unsigned int v6; // edi
  int v7; // ebx

  v3 = (unsigned int)(this + 136);
  v4 = sub_41A5E0((unsigned int)(this + 136)) == 0;
  LOBYTE(v5) = a2;
  if ( !v4 != a2 )
  {
    sub_41A590(v3, a2, a2);
    v6 = 0;
    v7 = 0;
    while ( 1 )
    {
      v5 = *(this + 98);
      if ( v5 == 0 )
        break;
      v5 = (int)(*(this + 99) - v5) / 44;
      if ( v6 >= v5 )
        break;
      if ( sub_41A5E0((unsigned int)(this + 136)) == 0 || sub_41A5E0((unsigned int)this + 558) != 0 )
      {
        ++v6;
        *(uint8_t *)(v7 + *(this + 98) + 40) = 0;
        v7 += 44;
      }
      else
      {
        ++v6;
        *(uint8_t *)(v7 + *(this + 98) + 40) = 1;
        v7 += 44;
      }
    }
  }
  return v5;
}



// ------------------------------------------------------------
// 0x47E4F0 sub_47E4F0
// ------------------------------------------------------------
void sub_47E4F0()
{
  int v0; // ebx
  int v1; // eax
  char *v2; // edi
  uint32_t *v3; // esi
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // esi
  int v8; // eax
  int v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // ecx
  char *v12; // ebx
  int v13; // esi
  int v14; // edi
  int v15; // esi
  int v16; // esi
  int v17; // eax
  bool v18; // zf
  int v19; // [esp+Ch] [ebp-2Ch]
  int v20; // [esp+10h] [ebp-28h]
  char *v21; // [esp+14h] [ebp-24h]
  int v22; // [esp+18h] [ebp-20h]
  int i; // [esp+1Ch] [ebp-1Ch]
  int j; // [esp+20h] [ebp-18h]
  int v25; // [esp+24h] [ebp-14h]
  uint32_t *v26; // [esp+28h] [ebp-10h]
  int v27; // [esp+2Ch] [ebp-Ch]
  uint32_t *v28; // [esp+30h] [ebp-8h]
  int v29; // [esp+34h] [ebp-4h]

  v0 = dword_8F7C04;
  v27 = dword_8F7C04;
  if ( dword_8F7C04 != 0 )
  {
    v1 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);
    v2 = (char *)&unk_99FC30 + 16 * v1;
    v3 = *((uint32_t **)v2 + 1);
    v22 = v1;
    v21 = v2;
    if ( v3 != *((uint32_t **)v2 + 2) )
    {
      do
      {
        if ( *v3 != 0 )
        {
          v4 = sub_41A5E0(*v3 + 496);
          sub_41A590(v4);
          sub_41A590(1065353216);
        }
        ++v3;
      }
      while ( v3 != *((uint32_t **)v2 + 2) );
      v0 = v27;
    }
    v5 = 0;
    for ( i = 0; i < 18; ++i )
    {
      v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v0 + 792))(v0, v5);
      v29 = v6;
      if ( v6 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 200))(v6) != 0 )
        v29 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v0 + 1084))(v0, v5);
      v7 = v29;
      if ( v29 != 0 )
      {
        v8 = 0;
        for ( j = 0; j < 2; ++j )
        {
          if ( v8 != 0 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 224))(v7) == 0 )
              break;
            v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 228))(v7);
          }
          else
          {
            v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 176))(v7);
          }
          v10 = (uint32_t *)(v9 + 892);
          v26 = v10;
          v25 = 2;
          do
          {
            v11 = (uint32_t *)*(v10 - 1);
            v28 = v11;
            if ( v11 != (uint32_t *)*v10 )
            {
              v12 = (char *)v11 + 18;
              do
              {
                if ( *v11 == 4 || *v11 == v22 )
                {
                  v13 = *(uint32_t *)(*((uint32_t *)v21 + 1) + 4 * sub_41A5E0(v12 - 14));
                  if ( v13 != 0 )
                  {
                    if ( sub_41A5E0(v13 + 496) != 0 )
                    {
                      v14 = v13 + 510;
                      v20 = sub_41A5E0(v13 + 510);
                      v15 = v13 + 32;
                      v19 = sub_41A5E0(v12);
                      if ( v19 + v20 >= sub_41A5E0(v15) )
                      {
                        v17 = sub_41A5E0(v15);
                      }
                      else
                      {
                        v16 = sub_41A5E0(v14);
                        v17 = v16 + sub_41A5E0(v12);
                      }
                      sub_41A590(v17);
                    }
                  }
                  else
                  {
                    off_77F3FC(
                      "CRITICAL ERROR : CNRDSkill::flushSkillParameter - skill %d is NULL",
                      *(uint32_t *)(v12 - 14));
                  }
                }
                v10 = v26;
                v11 = v28 + 8;
                v12 += 32;
                v28 += 8;
              }
              while ( v28 != (uint32_t *)*v26 );
              v0 = v27;
              v7 = v29;
            }
            v10 += 4;
            v18 = v25 == 1;
            v26 = v10;
            --v25;
          }
          while ( !v18 );
          v8 = j + 1;
        }
      }
      v5 = i + 1;
    }
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v0 + 1164))(v0);
  }
}


// ============================================================
// 【分区 12】技能数据（0x47E720-0x480000）
// CNRDSkill__vmt4（RTTI 自证）与技能条目读写。
// ============================================================
// ------------------------------------------------------------
// 0x47E720 sub_47E720
// ------------------------------------------------------------
// 技能条目查找/换算（配合 0x47EFD0 的 14 字节/项表）【推断】
int /*cdecl*/ sub_47E720(int a1, unsigned int a2)
{
  int v2; // eax
  int v3; // eax
  int v4; // edx

  v2 = a1;
  if ( a1 == 4 )
  {
    while ( sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0 )
    {
      v2 = *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 44);
      if ( v2 != 4 )
        goto LABEL_6;
    }
    v2 = 0;
  }
LABEL_6:
  v3 = 4 * v2;
  v4 = dword_99FC34[v3];
  if ( v4 != 0 && a2 < (dword_99FC38[v3] - v4) >> 2 )
    return *(uint32_t *)(dword_99FC34[v3] + 4 * a2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x47E7A0 sub_47E7A0
// ------------------------------------------------------------
char /*thiscall*/ sub_47E7A0(int *this, uint8_t a2, char a3)
{
  int v4; // eax
  bool v5; // zf
  unsigned int v6; // edi
  int v7; // ebx
  int v8; // eax

  v4 = *(this + 98);
  if ( v4 != 0 )
  {
    v4 = (*(this + 99) - v4) / 44;
    if ( v4 != 0 )
    {
      v5 = sub_41A5E0((unsigned int)this + 558) == 0;
      LOBYTE(v4) = a2;
      if ( !v5 != a2 )
      {
        sub_41A590((unsigned int)this + 558, a2, a2);
        v6 = 0;
        v7 = 0;
        while ( 1 )
        {
          v8 = *(this + 98);
          if ( v8 == 0 || v6 >= (*(this + 99) - v8) / 44 )
            break;
          if ( sub_41A5E0((unsigned int)(this + 136)) == 0 || sub_41A5E0((unsigned int)this + 558) != 0 )
          {
            ++v6;
            *(uint8_t *)(v7 + *(this + 98) + 40) = 0;
            v7 += 44;
          }
          else
          {
            ++v6;
            *(uint8_t *)(v7 + *(this + 98) + 40) = 1;
            v7 += 44;
          }
        }
        LOBYTE(v4) = a3;
        if ( a3 != 0 )
        {
          if ( a2 != 0 )
            sub_432EA0("SEAL_ON", -1, 0, 0);
          else
            sub_432EA0("SEAL_OFF", -1, 0, 0);
          sub_44E850(dword_8F8528, 18);
          LOBYTE(v4) = sub_48BAD0(dword_8F8544);
        }
      }
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x47E8C0 sub_47E8C0
// ------------------------------------------------------------
uint32_t *sub_47E8C0()
{
  int v0; // ebx
  uint32_t *result; // eax
  int v2; // edi
  int i; // esi

  v0 = 4 * *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 44);
  result = (uint32_t *)dword_99FC34[v0];
  if ( result != nullptr )
    v2 = (dword_99FC38[v0] - (int)result) >> 2;
  else
    v2 = 0;
  for ( i = 0; i < v2; ++i )
  {
    result = (uint32_t *)(dword_99FC34[v0] + 4 * i);
    if ( *result != 0 )
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*result + 8))(*result);
  }
  return result;
}



// ------------------------------------------------------------
// 0x47E920 sub_47E920
// ------------------------------------------------------------
void /*cdecl*/ sub_47E920(uint32_t *a1, int a2, unsigned int a3)
{
  uint32_t *v3; // esi
  int v5; // eax
  int v6; // edx
  uint32_t v7[5]; // [esp+0h] [ebp-20h] BYREF
  int v8; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v7[4] = v7;
  v7[3] = a1;
  v8 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v8) = 1;
    if ( v3 != nullptr )
    {
      sub_41A630((unsigned int)v3);
      LOBYTE(v8) = 2;
      *v3 = &vftbl_clong;
      v5 = sub_41A5E0(a3);
      sub_41A590((unsigned int)v3, v6, v5);
    }
    --a2;
    v3 = (uint32_t *)((char *)v3 + 14);
    LOBYTE(v8) = 0;
  }
}



// ------------------------------------------------------------
// 0x47E9D0 sub_47E9D0
// ------------------------------------------------------------
int /*thiscall*/ sub_47E9D0(uint32_t *this, unsigned int a2)
{
  char v2; // bl
  int v3; // eax
  unsigned int v4; // eax
  int v5; // esi
  uint8_t v7[14]; // [esp+Ah] [ebp-1Eh] BYREF
  int v8; // [esp+18h] [ebp-10h]
  int v9; // [esp+24h] [ebp-4h]

  v2 = 0;
  v8 = 0;
  v3 = *(this + 103);
  if ( v3 != 0 && a2 < (*(this + 104) - v3) / 14 )
  {
    v4 = *(this + 103) + 14 * a2;
  }
  else
  {
    v4 = sub_461750(0);
    v9 = 0;
    v2 = 1;
    v8 = 1;
  }
  v5 = sub_41A5E0(v4);
  v9 = -1;
  if ( (v2 & 1) != 0 )
    sub_41A580(v7);
  return v5;
}



// ------------------------------------------------------------
// 0x47EA80 sub_47EA80
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_47EA80(uint32_t *this, int a2)
{
  int v2; // eax
  int v5; // [esp+10h] [ebp+8h]

  v2 = a2;
  if ( a2 == -1 )
    v2 = sub_41A5E0((unsigned int)this + 510);
  v5 = sub_41A5E0(*(this + 75) + 14 * (v2 - 1));
  return (uint64_t)((double)v5 * COERCE_FLOAT(sub_41A5E0((unsigned int)(this + 131))));
}



// ------------------------------------------------------------
// 0x47EAD0 sub_47EAD0
// ------------------------------------------------------------
int /*thiscall*/ sub_47EAD0(uint32_t *this, int a2)
{
  int v2; // eax

  v2 = a2;
  if ( a2 == -1 )
    v2 = sub_41A5E0((unsigned int)this + 510);
  return sub_41A5E0(*(this + 87) + 14 * (v2 - 1));
}



// ------------------------------------------------------------
// 0x47EB10 sub_47EB10
// ------------------------------------------------------------
int /*thiscall*/ sub_47EB10(uint32_t *this)
{
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax

  if ( dword_8F7C04 == 0 )
    return 0;
  v3 = sub_41A5E0((unsigned int)(this + 124));
  v4 = sub_41A5E0(*(this + 13) + 14 * v3);
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);
  v6 = sub_41A5E0((unsigned int)this + 14 * *(uint32_t *)(v5 + 4) + 142);
  if ( v6 != 0 )
    v4 = v4 * (100 - v6) / 100;
  return (v4 - *(this + 135)) & ((v4 - *(this + 135) < 0) - 1);
}



// ------------------------------------------------------------
// 0x47EB90 sub_47EB90
// ------------------------------------------------------------
char /*thiscall*/ sub_47EB90(uint32_t *this)
{
  int v2; // eax
  int v3; // esi
  unsigned int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // ebx
  int v9; // [esp+Ch] [ebp-8h]
  int v10; // [esp+10h] [ebp-4h]

  v2 = *(this + 24);
  v3 = 0;
  if ( v2 != 0 )
    v10 = (*(this + 25) - v2) / 14;
  else
    v10 = 0;
  v9 = 0;
  if ( v10 <= 0 )
    return 1;
  while ( 1 )
  {
    v4 = sub_41A5E0(v3 + *(this + 24));
    v5 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    v6 = sub_47E720(*(uint32_t *)(v5 + 44), v4);
    v7 = sub_41A5E0(v6 + 496);
    if ( v7 < sub_41A5E0(v3 + *(this + 28)) )
      break;
    v3 += 14;
    if ( ++v9 >= v10 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x47EC40 sub_47EC40
// ------------------------------------------------------------
void sub_47EC40()
{
  int *v0; // esi
  int v1; // ebx
  int i; // edi
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int *v4; // esi

  v0 = dword_99FC34;
  do
  {
    if ( *v0 != 0 )
      v1 = (v0[1] - *v0) >> 2;
    else
      v1 = 0;
    for ( i = 0; i < v1; ++i )
    {
      v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(*v0 + 4 * i);
      if ( v3 != nullptr )
        (**v3)(v3, 1);
    }
    if ( *v0 != 0 )
      j__free((void *)*v0);
    *v0 = 0;
    v0[1] = 0;
    v0[2] = 0;
    v0 += 4;
  }
  while ( (int)v0 < (int)dword_99FC74 );
  v4 = &dword_99FC18;
  do
  {
    if ( *v4 != 0 )
      (**(void (/*thiscall*/ ***)(int, int))*v4)(*v4, 1);
    *v4++ = 0;
  }
  while ( (int)v4 < (int)&dword_99FC28 );
}



// ------------------------------------------------------------
// 0x47ECE0 sub_47ECE0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_47ECE0(unsigned int *this)
{
  unsigned int v1; // edi
  int i; // ebx
  unsigned int result; // eax
  int v5; // [esp+Ch] [ebp-4h] BYREF

  v1 = 0;
  for ( i = 0; ; i += 44 )
  {
    result = *(this + 98);
    if ( result == 0 )
      break;
    result = (int)(*(this + 99) - result) / 44;
    if ( v1 >= result )
      break;
    v5 = i + *(this + 98);
    sub_437240(dword_8F85A8, (int)&v5);
    ++v1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47ED40 sub_47ED40
// ------------------------------------------------------------
char /*thiscall*/ sub_47ED40(uint32_t *this)
{
  uint32_t *v1; // edi
  int v3; // esi
  int v4; // eax
  int *v5; // esi
  int v6; // ebx
  int v7; // edi
  unsigned int v8; // edi
  int v9; // eax
  int v10; // eax
  float v11; // [esp+4h] [ebp-Ch]
  int v12; // [esp+8h] [ebp-8h]

  v1 = this;
  if ( sub_41A5E0((unsigned int)(this + 136)) == 0 )
    return 0;
  v3 = dword_8F7C04;
  if ( dword_8F7C04 == 0 )
    return 0;
  v4 = sub_41A5E0((unsigned int)v1 + 510);
  v12 = sub_41A5E0(v1[75] + 14 * (v4 - 1));
  v11 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v1 + 131)));
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 752))(v3) < (int)(uint64_t)((double)v12 * v11) )
    return 0;
  v5 = (int *)v1[83];
  if ( v5 == (int *)v1[84] )
    return 1;
  while ( 1 )
  {
    v6 = *v5;
    v7 = sub_41A5E0((unsigned int)(v1 + 8));
    v8 = v5[1] + (sub_41A5E0((unsigned int)this + 510) - 1) * (v5[2] - v5[1]) / (v7 - 1);
    if ( v8 != 0 )
    {
      v9 = sub_484E80(v6);
      if ( v9 == -1 )
        break;
      v10 = v9 >= *((uint32_t *)dword_8F852C + 2) ? 0 : *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v9);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 44))(v10) < v8 )
        break;
    }
    v5 += 3;
    if ( v5 == (int *)*(this + 84) )
      return 1;
    v1 = this;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x47EE70 sub_47EE70
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_47EE70(uint32_t *this, unsigned int a2, unsigned int a3, int a4)
{
  float v6; // [esp+0h] [ebp-14h]
  float v7; // [esp+4h] [ebp-10h]
  int v8; // [esp+Ch] [ebp-8h]
  float v9; // [esp+Ch] [ebp-8h]

  v8 = sub_41A5E0((unsigned int)(this + 8)) - 1;
  v7 = (float)sub_47E9D0(this, a3);
  v6 = (float)sub_47E9D0(this, a2);
  v9 = sub_4049C0(v6, v7, a4 - 1, v8);
  return sub_432F40(v9);
}



// ------------------------------------------------------------
// 0x47EED0 sub_47EED0
// ------------------------------------------------------------
void /*thiscall*/ sub_47EED0(uint32_t *this, unsigned int a2, unsigned int a3, int a4)
{
  float v5; // [esp+0h] [ebp-14h]
  float v6; // [esp+4h] [ebp-10h]
  int v7; // [esp+Ch] [ebp-8h]

  v7 = sub_41A5E0((unsigned int)(this + 8)) - 1;
  v6 = (float)sub_47E9D0(this, a3);
  v5 = (float)sub_47E9D0(this, a2);
  sub_4049C0(v5, v6, a4 - 1, v7);
}



// ------------------------------------------------------------
// 0x47EF20 sub_47EF20
// ------------------------------------------------------------
int /*thiscall*/ sub_47EF20(uint32_t *this, unsigned int a2, int a3, int a4, int a5, int a6)
{
  int v6; // edx
  int64_t v7; // rax
  int v8; // esi
  unsigned int v9; // eax
  float v11; // [esp+8h] [ebp+8h]

  v6 = *(this + 107);
  if ( v6 != 0 && a2 < (*(this + 108) - v6) >> 4 )
  {
    v8 = *(this + 107) + 16 * a2;
    v9 = *(uint32_t *)(v8 + 4);
    if ( v9 != 0 )
      v9 = (int)(*(uint32_t *)(v8 + 8) - v9) / 14;
    if ( a3 - 1 < v9 )
    {
      LODWORD(v7) = sub_41A5E0(*(uint32_t *)(v8 + 4) + 14 * a3 - 14);
      if ( a6 != 11 && a4 != a5 )
      {
        v11 = sub_432FD0(a4, a6) * (double)(int)v7;
        return (uint64_t)(v11 / sub_432FD0(a5, a6));
      }
    }
    else
    {
      LODWORD(v7) = 0;
    }
  }
  else
  {
    LODWORD(v7) = 0;
  }
  return v7;
}



// ------------------------------------------------------------
// 0x47EFD0 sub_47EFD0
// ------------------------------------------------------------
// 技能表槽位设置（越界打 aCriticalError_8；+87 处 14 字节/项表）【推断】
int /*thiscall*/ sub_47EFD0(char *this, float a2, int a3, int a4, int a5, int a6)
{
  int v7; // edi
  int v8; // eax
  int v10; // edi
  int v11; // edi
  int v12; // eax
  double v14; // st7
  int v15; // edi
  int v16; // eax
  int v17; // eax
  float v18; // [esp+0h] [ebp-14h]
  float v19; // [esp+10h] [ebp-4h]
  int v20; // [esp+1Ch] [ebp+8h]
  float v21; // [esp+1Ch] [ebp+8h]
  float v22; // [esp+1Ch] [ebp+8h]
  int v23; // [esp+20h] [ebp+Ch]

  v7 = sub_47EF20(LODWORD(a2), a3, a4, a5, a6);
  v8 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v8 != 4 && v8 != 6 )
    return v7;
  if ( sub_41A5E0(this + 32) <= 1 || sub_41A5E0(this + 78) == 0 || a4 == -1 )
    return v7;
  v10 = sub_41A5E0(this + 64);
  v11 = (a4 - v10) / sub_41A5E0(this + 78) + 1;
  if ( v11 >= sub_41A5E0(this + 282) )
    v11 = sub_41A5E0(this + 282);
  v12 = sub_41A5E0(this + 282);
  v23 = v11 - a3;
  v19 = (float)(int)sub_47EF20(LODWORD(a2), v12, -1, -1, 11);
  if ( sub_41A5E0(this + 282) == 1 )
  {
    v20 = sub_47EF20(LODWORD(a2), 2, -1, -1, 11);
    v14 = (double)(v20 - sub_47EF20(LODWORD(a2), 1, -1, -1, 11));
  }
  else
  {
    v15 = sub_41A5E0(this + 282);
    v14 = (v19 - (double)(int)sub_47EF20(LODWORD(a2), 1, -1, -1, 11)) / (double)(v15 - 1);
  }
  v18 = v19 - (double)v23 * v14;
  v21 = (float)sub_432F40(v18);
  if ( a6 != 11 )
  {
    v16 = sub_41A5E0(this + 282);
    v17 = sub_47DE90(v16);
    if ( a4 < v17 )
    {
      v22 = sub_432FD0(v17, a6) * v21;
      v21 = v22 / sub_432FD0(a5, a6);
    }
  }
  return sub_432F40(v21);
}



// ------------------------------------------------------------
// 0x47F190 CNRDSkill__vmt4
// ------------------------------------------------------------
// CNRDSkill::vmt4 技能帧处理（RTTI 自证）
unsigned int /*thiscall*/ CNRDSkill__vmt4(unsigned int *this, int ArgList)
{
  unsigned int v3; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // ebx
  int v8; // edx
  int v9; // eax
  int v10; // edx
  unsigned int result; // eax
  unsigned int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // edi
  int v16; // eax
  int v17; // edx
  int v18; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]
  unsigned int ArgLista; // [esp+1Ch] [ebp+8h]

  v3 = (unsigned int)(this + 8);
  v4 = ArgList;
  if ( ArgList > sub_41A5E0((unsigned int)(this + 8)) )
  {
    v5 = sub_41A5E0(v3);
    off_77F3FC(aCriticalError_8, ArgList, v5);
    v4 = sub_41A5E0(v3);
  }
  if ( v4 == -1 )
    v6 = sub_41A5E0((unsigned int)this + 510) - 1;
  else
    v6 = v4 - 1;
  v7 = sub_41A5E0(*(this + 87) + 14 * v6);
  sub_41A590((unsigned int)(this + 154), v8, v7);
  v9 = sub_699000((int)&unk_99FC80);
  sub_41A590((unsigned int)this + 630, v10, v7 + v9);
  result = *(this + 91);
  if ( result != 0 )
  {
    result = (int)(*(this + 92) - result) / 14;
    if ( result != 0 )
    {
      v18 = *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 44);
      ArgLista = 0;
      for ( i = 0; ; i += 14 )
      {
        result = *(this + 91);
        if ( result == 0 )
          break;
        result = (int)(*(this + 92) - result) / 14;
        if ( ArgLista >= result )
          break;
        v12 = sub_41A5E0(i + *(this + 91));
        v13 = sub_47E720(v18, v12);
        v15 = v13;
        if ( v13 != 0 )
        {
          sub_41A590(v13 + 616, v14, v7);
          v16 = sub_699000((int)&unk_99FC80);
          sub_41A590(v15 + 630, v17, v7 + v16);
        }
        ++ArgLista;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x47F310 sub_47F310
// ------------------------------------------------------------
char /*thiscall*/ sub_47F310(int **this, char *a2, int a3)
{
  int *v5; // eax
  int *v6; // esi
  const char *v7; // edi
  int v8; // ecx
  char *v9; // eax
  const char *v10; // ebx
  int v11; // esi
  unsigned int *v12; // eax
  int v13; // edx
  unsigned int v14; // eax
  double v15; // st7
  int v16; // esi
  int v17; // eax
  unsigned int v18; // eax
  unsigned int v19; // esi
  unsigned int v20; // edi
  const char *v21; // eax
  int v22; // eax
  const char *v23; // eax
  const char *v24; // edx
  unsigned int v25; // eax
  const char *v26; // eax
  const char *v27; // eax
  const char *v28; // eax
  const char *v29; // eax
  unsigned int v30; // esi
  float v31; // [esp+0h] [ebp-40h]
  float v32; // [esp+4h] [ebp-3Ch]
  int v33; // [esp+Ch] [ebp-34h]
  size_t v34; // [esp+Ch] [ebp-34h]
  size_t v35; // [esp+Ch] [ebp-34h]
  size_t v36; // [esp+Ch] [ebp-34h]
  int *v38; // [esp+20h] [ebp-20h]
  char *Destinationa; // [esp+24h] [ebp-1Ch]
  float v41; // [esp+28h] [ebp-18h]
  char Buffer[16]; // [esp+2Ch] [ebp-14h] BYREF
  int v43; // [esp+3Ch] [ebp-4h]
  unsigned int v44; // [esp+48h] [ebp+8h]

  v43 = dword_796E50;
  if ( a3 > sub_41A5E0((unsigned int)(this + 8)) )
    return 0;
  v5 = *(this + 112);
  v6 = *(this + 111);
  if ( v6 == v5 )
    return 0;
  while ( *v6 > a3 || v6[1] < a3 )
  {
    v6 += 11;
    if ( v6 == v5 )
      return 0;
  }
  v38 = v6;
  v7 = (const char *)sub_41ACF0(v6 + 2);
  v44 = 0;
  while ( 1 )
  {
    v8 = v6[4];
    if ( v8 == 0 )
      break;
    if ( v44 >= (v6[5] - v8) >> 3 )
      break;
    v9 = strstr(v7, "<");
    v10 = v9;
    if ( v9 == nullptr )
      break;
    v11 = v9 - v7;
    strncpy(a2, v7, v9 - v7);
    v12 = (unsigned int *)(v38[4] + 8 * v44);
    Destinationa = &a2[v11];
    if ( *v12 == -1 )
    {
      v13 = (int)*(this + 107);
      v14 = v12[1];
      if ( v13 != 0 && v14 < ((int)*(this + 108) - v13) >> 4 )
      {
        v16 = (int)&(*(this + 107))[4 * v14];
        v17 = *(uint32_t *)(v16 + 4);
        if ( v17 != 0 )
          v18 = (*(uint32_t *)(v16 + 8) - v17) / 14;
        else
          v18 = 0;
        if ( a3 - 1 < v18 )
          v15 = (double)sub_41A5E0(*(uint32_t *)(v16 + 4) + 14 * a3 - 14);
        else
          v15 = (double)0;
      }
      else
      {
        v15 = (double)0;
      }
    }
    else
    {
      v19 = v12[1];
      v20 = *v12;
      v33 = sub_41A5E0((unsigned int)(this + 8)) - 1;
      v32 = (float)sub_47E9D0(this, v19);
      v31 = (float)sub_47E9D0(this, v20);
      v15 = sub_4049C0(v31, v32, a3 - 1, v33);
    }
    v41 = v15 * *(float *)(v38[8] + 4 * v44);
    v34 = strlen((const char *)sub_422E70(483));
    v21 = (const char *)sub_422E70(482);
    if ( strncmp(v10, v21, v34) == 0 )
    {
      v22 = sub_432F40(v41);
      sprintf(Buffer, "%d", v22);
      v23 = (const char *)sub_422E70(484);
      v24 = v23 + 1;
      v25 = (unsigned int)&v23[strlen(v23) + 1];
      goto LABEL_29;
    }
    v35 = strlen((const char *)sub_422E70(486));
    v26 = (const char *)sub_422E70(485);
    if ( strncmp(v10, v26, v35) == 0 )
    {
      sprintf(Buffer, "%.1f", v41);
      v27 = (const char *)sub_422E70(487);
      v24 = v27 + 1;
      v25 = (unsigned int)&v27[strlen(v27) + 1];
      goto LABEL_29;
    }
    v36 = strlen((const char *)sub_422E70(489));
    v28 = (const char *)sub_422E70(488);
    if ( strncmp(v10, v28, v36) == 0 )
    {
      sprintf(Buffer, "%.2f", v41);
      v29 = (const char *)sub_422E70(490);
      v24 = v29 + 1;
      v25 = (unsigned int)&v29[strlen(v29) + 1];
LABEL_29:
      v30 = v25 - (uint32_t)v24;
      strcpy(Destinationa, Buffer);
      v7 = &v10[v30];
      v6 = v38;
      a2 = &Destinationa[strlen(Buffer)];
      ++v44;
    }
    else
    {
      strncpy(Destinationa, v10, 1u);
      a2 = Destinationa + 1;
      v6 = v38;
      v7 = v10 + 1;
    }
  }
  strcpy(a2, v7);
  return 1;
}


// ------------------------------------------------------------
// 0x47F6B0 sub_47F6B0
// ------------------------------------------------------------
int /*stdcall*/ sub_47F6B0(char *a1, char *a2)
{
  char *i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 14 )
    result = (**(int (/*thiscall*/ ***)(char *, uint32_t))i)(i, 0);
  return result;
}



// ------------------------------------------------------------
// 0x47F6E0 sub_47F6E0
// ------------------------------------------------------------
int /*thiscall*/ sub_47F6E0(int this)
{
  char *v2; // esi
  char *i; // edi

  v2 = *(char **)(this + 4);
  if ( v2 != nullptr )
  {
    for ( i = *(char **)(this + 8); v2 != i; v2 += 14 )
      (**(void (/*thiscall*/ ***)(char *, uint32_t))v2)(v2, 0);
    j__free(*(void **)(this + 4));
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x47F720 sub_47F720
// ------------------------------------------------------------
unsigned int */*thiscall*/ sub_47F720(int *this, unsigned int *a2, unsigned int a3, unsigned int a4)
{
  unsigned int v5; // eax
  char *v6; // edi
  unsigned int v7; // ebx
  char *i; // esi

  if ( a3 == a4 )
  {
    *a2 = a3;
    return a2;
  }
  else
  {
    v5 = sub_47DE10(a4, *(this + 2), a3);
    v6 = (char *)*(this + 2);
    v7 = v5;
    for ( i = (char *)v5; i != v6; i += 14 )
      (**(void (/*thiscall*/ ***)(char *, uint32_t))i)(i, 0);
    *(this + 2) = v7;
    *a2 = a3;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x47F790 sub_47F790
// ------------------------------------------------------------
int /*stdcall*/ sub_47F790(int a1, int a2, int a3)
{
  return sub_59EE30(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x47F7B0 sub_47F7B0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_47F7B0(unsigned int a1, int a2, uint32_t *a3)
{
  return sub_47E200(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x47F7D0 sub_47F7D0
// ------------------------------------------------------------
bool /*thiscall*/ sub_47F7D0(uint32_t *this)
{
  int v3; // esi
  int v4; // ebx
  int v5; // esi
  int v6; // esi
  int v7; // [esp+4h] [ebp-4h]
  int v8; // [esp+4h] [ebp-4h]

  if ( dword_8F7C04 == 0 )
    return false;
  v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04) + 4);
  v7 = sub_41A5E0((unsigned int)(this + 124));
  if ( v7 >= sub_41A5E0((unsigned int)this + 14 * v3 + 212) )
    return false;
  v4 = sub_41A5E0((unsigned int)(this + 124));
  v8 = sub_41A5E0((unsigned int)(this + 16));
  v5 = sub_41A5E0((unsigned int)this + 78);
  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) < v8 + v4 * v5
    || sub_47EB90(this) == 0 )
  {
    return false;
  }
  v6 = Value;
  return sub_47EB10(this) <= v6;
}



// ------------------------------------------------------------
// 0x47F890 sub_47F890
// ------------------------------------------------------------
bool /*thiscall*/ sub_47F890(uint32_t *this)
{
  bool result; // al
  uint8_t v3[4]; // [esp+4h] [ebp-4h] BYREF

  result = sub_47F7D0(this);
  if ( result )
  {
    sub_423200(dword_8F7B08, 31);
    v3[0] = sub_41A5E0((unsigned int)(this + 1));
    sub_423290(dword_8F7B08, (int)v3, 1);
    sub_423380(dword_8F7B08);
    return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47F8E0 sub_47F8E0
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_47F8E0(int this)
{
  return sub_47F6E0(this);
}



// ------------------------------------------------------------
// 0x47F8F0 sub_47F8F0
// ------------------------------------------------------------
char */*stdcall*/ sub_47F8F0(uint32_t *a1, int a2, unsigned int a3)
{
  sub_47E920(a1, a2, a3);
  return (char *)a1 + 14 * a2;
}



// ------------------------------------------------------------
// 0x47F920 sub_47F920
// ------------------------------------------------------------
void /*noreturn*/ sub_47F920()
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
// 0x47F990 sub_47F990
// ------------------------------------------------------------
void /*noreturn*/ sub_47F990()
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
// 0x47FA00 sub_47FA00
// ------------------------------------------------------------
void /*thiscall*/ sub_47FA00(int this)
{
  if ( *(uint32_t *)(this + 32) != 0 )
    j__free(*(void **)(this + 32));
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  if ( *(uint32_t *)(this + 16) != 0 )
    j__free(*(void **)(this + 16));
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  sub_41B010((void **)(this + 8));
}



// ------------------------------------------------------------
// 0x47FA50 sub_47FA50
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_47FA50(int this, unsigned int a2)
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
    sub_44CAB0(this);
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
// 0x47FB20 sub_47FB20
// ------------------------------------------------------------
char /*thiscall*/ sub_47FB20(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x3FFFFFFF )
    sub_47F990(this);
  v4 = (char *)operator new(4 * a2);
  *(this + 3) = &v4[4 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x47FB80 sub_47FB80
// ------------------------------------------------------------
char /*thiscall*/ sub_47FB80(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x15555555 )
    sub_47F990(this);
  v4 = (char *)operator new(12 * a2);
  *(this + 3) = &v4[12 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x47FBD0 sub_47FBD0
// ------------------------------------------------------------
char /*thiscall*/ sub_47FBD0(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x5D1745D )
    sub_47F990(this);
  v4 = (char *)operator new(44 * a2);
  *(this + 3) = &v4[44 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x47FC20 sub_47FC20
// ------------------------------------------------------------
char /*thiscall*/ sub_47FC20(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x12492492 )
    sub_47F990(this);
  v4 = (char *)operator new(14 * a2);
  *(this + 3) = &v4[14 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x47FC70 sub_47FC70
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_47FC70(unsigned int *this, unsigned int a2, int a3)
{
  int v4; // edx
  unsigned int result; // eax
  int v6; // eax
  void *v7; // edx

  v4 = *(this + 1);
  if ( v4 != 0 )
    result = (int)(*(this + 2) - v4) >> 2;
  else
    result = 0;
  if ( result >= a2 )
  {
    if ( v4 != 0 )
    {
      result = *(this + 2);
      if ( a2 < (int)(result - v4) >> 2 )
      {
        v7 = (void *)(v4 + 4 * a2);
        if ( v7 != (void *)result )
        {
          result = (unsigned int)memcpy_0(v7, (const void *)result, 0);
          *(this + 2) = result;
        }
      }
    }
  }
  else
  {
    if ( v4 != 0 )
      v6 = (int)(*(this + 2) - v4) >> 2;
    else
      v6 = 0;
    return sub_565EE0((void *)*(this + 2), a2 - v6, (int)&a3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x47FD00 sub_47FD00
// ------------------------------------------------------------
void /*thiscall*/ sub_47FD00(int *this, int a2, unsigned int a3, int a4)
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
  int v15; // eax
  char *v16; // ecx
  int v18; // edx
  int v19; // [esp-18h] [ebp-4Ch]
  int v20; // [esp-Ch] [ebp-40h]
  unsigned int v21; // [esp-8h] [ebp-3Ch]
  int v22; // [esp+0h] [ebp-34h] BYREF
  uint32_t v23[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+1Ch] [ebp-18h]
  int *v25; // [esp+20h] [ebp-14h]
  int *v26; // [esp+24h] [ebp-10h]
  int v27; // [esp+30h] [ebp-4h]
  char *v28; // [esp+3Ch] [ebp+8h]
  int v29; // [esp+40h] [ebp+Ch]
  int v30; // [esp+44h] [ebp+10h]

  v26 = &v22;
  v25 = this;
  sub_46B080(a4);
  v5 = *(this + 1);
  v6 = 0;
  v27 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 14;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - *(this + 1)) / 14;
    else
      v8 = 0;
    if ( 306783378 - v8 < a3 )
      sub_47F990(this);
    if ( *(this + 1) != 0 )
      v9 = (*(this + 2) - *(this + 1)) / 14;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = (char *)*(this + 2);
      Block = v16;
      if ( (int)&v16[-a2] / 14 >= a3 )
      {
        v28 = &v16[-14 * a3];
        *(this + 2) = sub_47E200(v28, v16, v16);
        sub_47E1B0(a2, v28, Block);
        sub_47DDA0(a2, a2 + 14 * a3, v23);
      }
      else
      {
        sub_47E200(a2, v16, a2 + 14 * a3);
        v21 = a3 - (*(this + 2) - a2) / 14;
        v20 = *(this + 2);
        LOBYTE(v27) = 3;
        sub_47F8F0(v20, v21, v23);
        v18 = 14 * a3 + *(this + 2);
        *(this + 2) = v18;
        v27 = 0;
        sub_47DDA0(a2, v18 - 14 * a3, v23);
      }
    }
    else
    {
      if ( 306783378 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        v11 = (*(this + 2) - *(this + 1)) / 14;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_47DD70(this);
      v30 = 14 * v10;
      v12 = (char *)operator new(14 * v10);
      v19 = *(this + 1);
      Block = v12;
      LOBYTE(v27) = 1;
      v29 = sub_47E200(v19, a2, v12);
      sub_47E920(v29, a3, v23);
      sub_47E200(a2, *(this + 2), 14 * a3 + v29);
      v13 = *(this + 1);
      v27 = 0;
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 14;
      v14 = v13 + a3;
      v15 = *(this + 1);
      if ( v15 != 0 )
      {
        sub_47F6B0(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v30];
      *(this + 2) = (int)&v12[14 * v14];
      *(this + 1) = (int)v12;
    }
  }
  v27 = -1;
  sub_41A580(v23);
}

