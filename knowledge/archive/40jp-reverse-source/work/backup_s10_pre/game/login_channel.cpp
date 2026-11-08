// ============================================================
// 【40JP逆向源代码工程】game/login_channel.cpp
// 模块: 登录/频道连接 CNEntranceChannel + 选区→选角→进副本→结算链路
// 来源: work/dump_combat.txt  区块: 0x470000-0x480000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
// 函数数: 291
// 二轮精修: 2026-10-07 补齐 0x47B5E0-0x47FD00 共 98 个函数的大白话头注释；
//   包 34/35/36 族 0x47B820/B8D0/B9E0 与评估器 0x47BBE0 变量业务名化
//   （条件条目 20 字节/项、÷20 魔数 1717986919、节点 0x24、条目上限 2^32/条目大小）
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
int /*thiscall*/ sub_470330(int *this, int pArg2, unsigned int uArg3, const void *pArg4)
{
  int result; // eax
  int pEntriesBegin; // edi  【this+1：频道表首条目指针（vector begin）】
  unsigned int nCapEntries; // ecx  【(capEnd-begin)/104：容量（条目数）】
  int nCountNow; // eax  【当前条目数（插入前快照）】
  int nCountRecheck; // eax  【当前条目数（溢出检查后复查）】
  unsigned int nNewCapEntries; // ecx  【扩容目标容量（条目数）】
  int nCountRecheck2; // eax  【当前条目数（扩容判定用）】
  int nGrowBytes; // edi  【新缓冲区总字节数 = 104*新容量】
  void *pMem; // eax  【operator new 出的新缓冲区】
  int pBeginRecheck; // ecx  【begin 复查（搬旧数据前）】
  int pBeginRecheck2; // eax  【begin 复查（统计待搬条目数）】
  unsigned int nAfterInsertCount; // esi  【扩容后条目总数 = 旧条目数+uArg3】
  char *pNewEnd; // esi  【新缓冲区末条目之后的位置】
  int pOldEnd; // ecx  【旧 end（尾部腾挪起点）】
  int pNewEnd2; // esi  【腾挪后的新 end】
  int pEndSpill; // [esp-Ch] [ebp-9Ch]  【旧 end 溢出寄存器暂存】
  unsigned int nTailEntries; // [esp-8h] [ebp-98h]  【end 之后还需补足的条目数】
  int v23; // [esp+0h] [ebp-90h] BYREF
  int v24; // [esp+Ch] [ebp-84h]  【扩容路径：旧数据搬到新块后的落点】
  void *Block; // [esp+10h] [ebp-80h]  【新缓冲区（异常清理用）】
  uint32_t v26[28]; // [esp+14h] [ebp-7Ch] BYREF  【104 字节新条目暂存区（0x68 qmemcpy 目标）】
  int v27; // [esp+8Ch] [ebp-4h]
  int v28; // [esp+98h] [ebp+8h]
  int pOldEndSpill; // [esp+A0h] [ebp+10h]  【旧 end 的栈暂存（供 sub_46ECC0 用）】

  result = dword_796E50;
  qmemcpy(v26, pArg4, 0x68u);  // 0x68=104：整条频道条目逐字节拷入暂存区
  pEntriesBegin = *(this + 1);
  v26[26] = dword_796E50;
  v26[27] = &v23;
  if ( pEntriesBegin != 0 )
  {
    result = 1321528399 * (*(this + 3) - pEntriesBegin);  // 1321528399：×2^32/104 取整的等价魔数（编译器优化除法）
    nCapEntries = (*(this + 3) - pEntriesBegin) / 104;  // 容量 = (capEnd-begin)/104 字节条目
  }
  else
  {
    nCapEntries = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( pEntriesBegin != 0 )
      nCountNow = (*(this + 2) - pEntriesBegin) / 104;
    else
      nCountNow = 0;
    if ( 41297762 - nCountNow < uArg3 )  // 41297762：最大条目数（×104 溢出前上限），超出则先清表
      sub_41D5A0(this);  // 【模块切换辅助（map 容器/观察者清理/资源卸载链）】
    if ( pEntriesBegin != 0 )
      nCountRecheck = (*(this + 2) - pEntriesBegin) / 104;
    else
      nCountRecheck = 0;
    if ( nCapEntries >= uArg3 + nCountRecheck )
    {
      // 容量够：原地腾出 uArg3 条的空洞
      pOldEnd = *(this + 2);
      pOldEndSpill = pOldEnd;
      if ( (pOldEnd - pArg2) / 104 >= uArg3 )  // 插入点之后已有 >=uArg3 条：整体后移再覆盖
      {
        v28 = pOldEnd - 104 * uArg3;  // 104*N：按条目大小做指针算术
        *(this + 2) = sub_46ED50(v28, pOldEnd, pOldEnd);
        sub_46ECC0(pArg2, v28, pOldEndSpill);
        return sub_46E6B0(pArg2, pArg2 + 104 * uArg3, v26);  // 空洞处写入新条目
      }
      else
      {
        // 插入点贴近旧 end：先挪尾，再补足，最后写新条目
        sub_46ED50(pArg2, pOldEnd, pArg2 + 104 * uArg3);
        nTailEntries = uArg3 - (*(this + 2) - pArg2) / 104;
        pEndSpill = *(this + 2);
        v27 = 2;
        sub_46F6B0(pEndSpill, nTailEntries, v26);
        pNewEnd2 = 104 * uArg3 + *(this + 2);
        *(this + 2) = pNewEnd2;
        return sub_46E6B0(pArg2, pNewEnd2 - 104 * uArg3, v26);
      }
    }
    else
    {
      // 容量不够：扩容重建（新块 = 1.5 倍或最大值，再整体搬运）
      if ( 41297762 - (nCapEntries >> 1) >= nCapEntries )
        nNewCapEntries = (nCapEntries >> 1) + nCapEntries;  // 新容量 = 旧容量×1.5
      else
        nNewCapEntries = 0;
      if ( pEntriesBegin != 0 )
        nCountRecheck2 = (*(this + 2) - pEntriesBegin) / 104;
      else
        nCountRecheck2 = 0;
      if ( nNewCapEntries < uArg3 + nCountRecheck2 )
        nNewCapEntries = uArg3 + sub_46E3D0(this);
      nGrowBytes = 104 * nNewCapEntries;  // 总字节数 = 104×条目数
      pMem = operator new(104 * nNewCapEntries);
      pBeginRecheck = *(this + 1);
      Block = pMem;
      v27 = 0;
      v24 = sub_46ED50(pBeginRecheck, pArg2, pMem);  // 搬插入点之前的旧条目
      sub_46EF10(v24, uArg3, v26);  // 空洞处填 uArg3 条新条目
      sub_46ED50(pArg2, *(this + 2), 104 * uArg3 + v24);  // 搬插入点之后的旧条目
      pBeginRecheck2 = *(this + 1);
      if ( pBeginRecheck2 != 0 )
        pBeginRecheck2 = (*(this + 2) - pBeginRecheck2) / 104;
      nAfterInsertCount = pBeginRecheck2 + uArg3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));  // 释放旧缓冲区
      result = (int)Block;
      pNewEnd = (char *)Block + 104 * nAfterInsertCount;
      *(this + 3) = (int)Block + nGrowBytes;  // this+3：容量端 capEnd
      *(this + 2) = (int)pNewEnd;  // this+2：end
      *(this + 1) = result;  // this+1：begin
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4705D0 sub_4705D0
// ------------------------------------------------------------
// 频道表追加一条并返回新条目指针（配合 0x470330 定点插入）
uint32_t */*thiscall*/ sub_4705D0(uint32_t *this, uint32_t *uArg2, char *pszArg3, const void *pArg4)
{
  int pEntriesBegin; // esi  【this+1：频道表首条目指针】
  int nInsertPos; // esi  【pszArg3 落点在表内的条目序号（104 字节/条）】

  pEntriesBegin = *(this + 1);
  if ( pEntriesBegin != 0 && (*(this + 2) - pEntriesBegin) / 104 != 0 )
    nInsertPos = (int)&pszArg3[-pEntriesBegin] / 104;  // 指针差/104 = 条目序号
  else
    nInsertPos = 0;
  sub_470330((int)this, pszArg3, 1u, pArg4);  // 在 pszArg3 处定点插入 1 条
  *uArg2 = *(this + 1) + 104 * nInsertPos;  // 返回新条目地址（扩容后按序号重算）
  return uArg2;
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
void /*thiscall*/ sub_470640(uint32_t *this, int ArgList, int nArg3, unsigned int uArg4)
{
  uint32_t *pSrvPage; // eax  【this+35*server_type：该服务器的频道列表组基址（35 dword=140 字节/页）】
  int pChannelBegin; // edx  【选中频道型的条目数组首指针（+680 起）】
  uint32_t *pBeginSlot; // eax  【&pSrvPage[4*channel_type]：begin 字段槽位】
  int pEntry; // esi  【选中的频道条目地址 = begin + 104*索引】
  void **ppCleanup; // esi  【切分 token 数组清理游标】
  int nAgeTier; // eax  【sub_46E230 返回：年龄档位（登录串首段 %d）】
  char *pszTip135; // eax  【135 号提示串（+79==-1 时弹）】
  const char *pszResp; // eax  【响应/首 token 的 C 串（atol 输入）】
  int nAuthResult; // eax  【atol 解析结果 → dword_8F7A24+244】
  signed int nLen; // esi
  signed int i; // edi
  void **ppCleanupEnd; // edi
  const char *pszFmtName; // [esp-18h] [ebp-33Ch]  【sprintf %s 段1：频道名【推断】】
  int nFmtPort; // [esp-14h] [ebp-338h]  【sprintf %d 段2：端口【推断】】
  const char *pszFmtAccount; // [esp-10h] [ebp-334h]  【sprintf %s 段3：账号【推断】】
  const char *pszFmtTicket; // [esp-Ch] [ebp-330h]  【sprintf %s 段4：凭据【推断】】
  char fmtPack[4]; // [esp+4h] [ebp-320h] BYREF  【sub_488690 切分容器首字段（与后续 Block/v24/v25 同体）】
  void *Block; // [esp+8h] [ebp-31Ch]  【token 数组 begin】
  void **v24; // [esp+Ch] [ebp-318h]  【token 数组 end】
  int v25; // [esp+10h] [ebp-314h]
  char Buffer[512]; // [esp+14h] [ebp-310h] BYREF  【组好的登录串 "%d?%s?%d?%s?%s"】
  char psz[256]; // [esp+214h] [ebp-110h] BYREF  【账号小写化副本（白名单比对）】
  int dword_796E502; // [esp+314h] [ebp-10h]
  int nRet; // [esp+320h] [ebp-4h]  【本函数返回值槽】
  uint32_t *pBeginSlotSaved; // [esp+330h] [ebp+Ch]

  dword_796E502 = dword_796E50;
  if ( *(uint8_t *)(*(this + 42) + 17) == 1 )  // +42→对象+17：连接流程进行中旗标
  {
    Block = nullptr;
    v24 = nullptr;
    v25 = 0;
    nRet = 0;
    if ( ArgList >= 6 )
    {
      off_77F3FC("CNEntranceChannel::connectServer - invalied server type. server_type = %d", ArgList);
      nRet = -1;
      return;
    }
    if ( nArg3 >= 5 )
    {
      off_77F3FC("CNEntranceChannel::connectServer - invalied channel type. channel_type = %d", nArg3);
      nRet = -1;
      return;
    }
    pSrvPage = this + 35 * ArgList;  // 每服务器页 35 dword：4 dword/频道型 + 170 dword 条目区
    pChannelBegin = pSrvPage[4 * nArg3 + 170];  // +680(0x2A8)：该频道型条目数组 begin
    pBeginSlot = &pSrvPage[4 * nArg3];
    pBeginSlotSaved = pBeginSlot;
    if ( pChannelBegin == 0 || uArg4 >= (pBeginSlot[171] - pChannelBegin) / 104 )  // +684：end；/104=条目数
    {
      off_77F3FC("CNEntranceChannel::connectServer - invalied channel index. index = %d", uArg4);
      nRet = -1;
      return;
    }
    if ( nArg3 != 4 )
    {
      *(this + 74) = ArgList;  // +296：连接历史·服务器型
      *(this + 76) = nArg3;  // +304：连接历史·频道型
      *(this + 78) = uArg4;  // +312：连接历史·频道索引
      off_77F3FC(
        "CNEntranceChannel::connectServer - connection history saved. server_type = %d, channel_type = %d, channel_index = %d",
        ArgList,
        nArg3,
        uArg4);
    }
    pEntry = pBeginSlotSaved[170] + 104 * uArg4;  // 选中条目 = begin + 104*索引
    if ( *(uint8_t *)(pEntry + 88) == 1 )  // +88：满员旗标（retrieveServerInfo 按 >95% 负载置位）
    {
      ppCleanup = (void **)Block;
      nRet = -1;
      if ( Block == nullptr )
        return;
      if ( Block == v24 )
        goto LABEL_31;
      do
        sub_41B010(ppCleanup++);
      while ( ppCleanup != v24 );
      goto LABEL_30;
    }
    byte_99FCD1 = *(uint8_t *)pEntry;  // 条目首字节 → 全局（当前选中频道种类?）
    nAgeTier = sub_46E230(this, pEntry + 64, *(uint32_t *)(pEntry + 84), dword_8F7A24 + 113, dword_8F7A24 + 177);  // +64：地址串；+84：端口；+113：账号；+177：凭据
    sprintf(Buffer, "%d?%s?%d?%s?%s", nAgeTier, pszFmtName, nFmtPort, pszFmtAccount, pszFmtTicket);
    sub_488690(fmtPack, Buffer, "?", 0);  // 登录串按 '?' 切分成 token 数组
    sub_48B7C0(13, *(this + 3));  // 请求参数 13 ← this+3（容量端?【推断】）
    sub_48B7C0(14, *(this + 4));
    sub_48B7C0(15, 0);
    sub_48B7C0(16, 0);
    sub_41E4F0(fmtPack);  // 【服务器连接 UI 状态（Connect to Server.../Connectio…】发出登录请求
    if ( *(this + 79) == -1 )
    {
      pszTip135 = sub_422E70(135);  // 135 号提示串（+79==-1 时弹出，具体文案未证）
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)pszTip135, 0);
    }
    pszResp = (const char *)sub_41ACF0(Block);
    nAuthResult = j__atol(pszResp);
    *(uint32_t *)(dword_8F7A24 + 244) = nAuthResult;  // +244：登录鉴权结果（==2 → 测试服标 "TN"）
    *(uint32_t *)(dword_8F7A24 + 244) = 0;
    if ( nAuthResult == 2 )
      sub_419CF0("TN");
    nLen = dword_8F7A24 + 113 + strlen((const char *)(dword_8F7A24 + 113)) + 1 - (dword_8F7A24 + 114);  // 账号串长度（含结尾 0）
    memset(psz, 0, sizeof(psz));
    for ( i = 0; i < nLen; ++i )
      psz[i] = tolower(*(uint8_t *)(dword_8F7A24 + i + 113));  // 账号名小写化后做测试白名单比对
    if ( strcmp(psz, "dnftest299") == 0
      || strcmp(psz, "dnftest300") == 0
      || strcmp(psz, "testman412") == 0
      || strcmp(psz, "testman425") == 0 )
    {
      *(uint32_t *)(dword_8F7A24 + 244) = 2;  // 测试账号 → 强制 "TN"（docs/13 §6 开发期残留）
      sub_419CF0("TN");
    }
    *(uint8_t *)(*(this + 42) + 17) = 0;  // 连接中旗标复位
    ppCleanup = (void **)Block;
    nRet = -1;
    if ( Block != nullptr )
    {
      ppCleanupEnd = v24;
      if ( Block == v24 )
      {
LABEL_31:
        j__free(ppCleanup);
        return;
      }
      do
        sub_41B010(ppCleanup++);
      while ( ppCleanup != ppCleanupEnd );
LABEL_30:
      ppCleanup = (void **)Block;
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
  int nReserveIdx; // eax  【+316：预约频道索引（-1=无预约）】
  int pChannelBegin; // edi  【按预约三元组定位的条目数组 begin】

  nReserveIdx = *(uint32_t *)(this + 316);
  if ( nReserveIdx != -1 )
  {
    // begin = *(this + 680 + 140*server_type + 16*channel_type)：与 connectServer 的
    // 页基址 35 dword + 每频道型 16 字节布局一致
    pChannelBegin = *(uint32_t *)(16 * *(uint32_t *)(this + 308) + this + 140 * *(uint32_t *)(this + 300) + 680);
    off_77F3FC(
      "CNEntranceChannel::processReservedConnection = %s %d",
      (const char *)(pChannelBegin + 104 * nReserveIdx + 64),  // +64：地址串
      *(uint32_t *)(104 * nReserveIdx + pChannelBegin + 84));  // +84：端口
    *(uint8_t *)(*(uint32_t *)(this + 168) + 17) = 1;  // 连接流程旗标置位（connectServer 入口条件）
    sub_470640((int *)this, *(uint32_t *)(this + 300), *(uint32_t *)(this + 308), *(uint32_t *)(this + 316));  // 按预约三元组重连
    *(uint32_t *)(this + 300) = 6;  // 清预约：server_type 还原为哨兵 6（越界值）
    *(uint32_t *)(this + 308) = 5;  // 清预约：channel_type 哨兵 5
    *(uint32_t *)(this + 316) = -1;  // 清预约：索引 -1
    *(uint8_t *)(this + 332) = 0;  // 重连进行中旗标复位
  }
}



// ------------------------------------------------------------
// 0x470B20 sub_470B20
// ------------------------------------------------------------
// 频道条目入表（0x4705D0 包装：容量够则原地 +104）
char */*thiscall*/ sub_470B20(int this, const void *pArg2)
{
  int pEntriesBegin; // edi  【this+4：频道表首条目指针（字节布局下 +4/+8/+12 = begin/end/capEnd）】
  unsigned int nCount; // ecx  【当前条目数 = (end-begin)/104】
  char *pEnd; // edi  【this+8：end】
  char *result; // eax

  pEntriesBegin = *(uint32_t *)(this + 4);
  if ( pEntriesBegin != 0 )
    nCount = (*(uint32_t *)(this + 8) - pEntriesBegin) / 104;
  else
    nCount = 0;
  if ( pEntriesBegin == 0 || nCount >= (*(uint32_t *)(this + 12) - pEntriesBegin) / 104 )
    return (char *)sub_4705D0((uint32_t *)this, &pArg2, *(char **)(this + 8), pArg2);  // 容量不够：走扩容插入
  pEnd = *(char **)(this + 8);
  result = sub_46EF10(pEnd, (char *)1, pArg2);  // 容量够：直接在 end 处构造 1 条
  *(uint32_t *)(this + 8) = pEnd + 104;  // end 后移 104 字节
  return result;
}



// ------------------------------------------------------------
// 0x470BB0 sub_470BB0
// ------------------------------------------------------------
// RB-tree erase(iterator)（小节点 map，+84 双色/+85 nil 旗标）：CLRS
// RB-DELETE（x=顶替孩子/y=后继/w=兄弟），值销毁 +12；end 迭代器抛
// out_of_range；返回后继迭代器
int ***/*thiscall*/ sub_470BB0(uint32_t *this, int ***uArg2, int **pDwArg3)
{
  int **pDwArg32; // ebx  【z：本次擦除的节点】
  int *pNodeX; // edi  【x：顶替被摘节点位子的孩子（或 nil）】
  int *pNodeY; // ecx  【y：两孩路径中被摘的后继节点（pDwArg3 复用）】
  int *pNodeXParent; // esi  【x 的父亲（重平衡回溯起点）】
  uint32_t *pThis2; // ecx
  int pHeaderTmp; // eax
  int *pMinSucc; // eax  【leftmost 修正用：x 子树最小节点】
  int pHeader2; // ecx
  bool bAtRoot; // zf  【x 已回溯到 header 左孩 = 结束循环】
  int pHeader3; // eax
  int **pParentSlot; // eax  【待改写的父槽位（左/右孩指针）】
  char nColorTmp; // al  【红黑双色字节交换暂存（+84）】
  uint32_t *pThis3; // ecx
  uint32_t *pSibling; // eax  【重平衡时的兄弟节点 w】
  int nSizeTmp; // eax
  void **pExceptionObject; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t exStrBuf[20]; // [esp+34h] [ebp-34h] BYREF  【异常消息串 "invalid map/set<T> iterator" 缓冲】
  int exStrSize; // [esp+48h] [ebp-20h]
  int exStrCap; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]  【z 原节点指针（销毁用）】
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v26; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 85) != 0 )  // +85：nil 旗标 —— 传入了 end() 迭代器
  {
    exStrCap = 15;
    exStrSize = 0;
    exStrBuf[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v26 = 0;
    sub_401740(exStrBuf);
    pExceptionObject = &std::out_of_range::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_46E5F0(&pDwArg3);  // 取后继迭代器（返回值），随后 pDwArg3 = 后继节点 y
  if ( *((uint8_t *)*pDwArg32 + 85) != 0 )  // z 左孩为 nil：x = 右孩
  {
    pNodeX = pDwArg32[2];
LABEL_8:
    pNodeXParent = pDwArg32[1];  // x 的父亲 = z 的父亲
    if ( *((uint8_t *)pNodeX + 85) == 0 )
      pNodeX[1] = (int)pNodeXParent;  // x.parent = x_parent
    pThis2 = pThis;
    pHeaderTmp = pThis[1];
    if ( *(int ***)(pHeaderTmp + 4) == pDwArg32 )  // header.left（最左）== z → 修正 leftmost
    {
      *(uint32_t *)(pHeaderTmp + 4) = pNodeX;
    }
    else if ( (int **)*pNodeXParent == pDwArg32 )  // z 是左孩 → 父.left = x
    {
      *pNodeXParent = (int)pNodeX;
    }
    else
    {
      pNodeXParent[2] = (int)pNodeX;  // 否则 父.right = x
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)pNodeX + 85) != 0 )
      {
        pMinSucc = pNodeXParent;
      }
      else
      {
        pMinSucc = (int *)sub_46E470(pNodeX);  // 新 leftmost = x 子树最小
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = pMinSucc;
    }
    pHeader2 = pThis2[1];
    bAtRoot = *(uint32_t *)(pHeader2 + 8) == (uint32_t)pDwArg32;
    v23 = pHeader2;
    if ( bAtRoot )  // header.right（最右）== z → 修正 rightmost
    {
      if ( *((uint8_t *)pNodeX + 85) != 0 )
        *(uint32_t *)(pHeader2 + 8) = pNodeXParent;
      else
        *(uint32_t *)(v23 + 8) = sub_46E450(pNodeX);  // 新 rightmost = x 子树最大
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 85) != 0 )  // z 右孩为 nil：x = 左孩
  {
    pNodeX = *pDwArg32;
    goto LABEL_8;
  }
  // 两孩路径：摘后继 y（pDwArg3 已被 sub_46E5F0 换成后继），x = y.right
  pNodeY = (int *)pDwArg3;
  pNodeX = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;  // z.left.parent = y
  *pNodeY = (int)*pDwArg32;  // y.left = z.left
  if ( pNodeY == pDwArg32[2] )  // y 原本就是 z 的右孩 → x_parent = y
  {
    pNodeXParent = pNodeY;
  }
  else
  {
    pNodeXParent = (int *)pNodeY[1];
    if ( *((uint8_t *)pNodeX + 85) == 0 )
      pNodeX[1] = (int)pNodeXParent;  // x.parent = y.parent
    *pNodeXParent = (int)pNodeX;  // y.parent.left = x
    pNodeY[2] = (int)pDwArg32[2];  // y.right = z.right
    pDwArg32[2][1] = (int)pNodeY;  // z.right.parent = y
  }
  pHeader3 = pThis[1];
  if ( *(int ***)(pHeader3 + 4) == pDwArg32 )  // 用 y 顶替 z 在父/header 中的槽位
  {
    *(uint32_t *)(pHeader3 + 4) = pNodeY;
  }
  else
  {
    pParentSlot = (int **)pDwArg32[1];
    if ( *pParentSlot == (int *)pDwArg32 )
      *pParentSlot = pNodeY;
    else
      pParentSlot[2] = pNodeY;
  }
  pNodeY[1] = (int)pDwArg32[1];  // y.parent = z.parent
  nColorTmp = *((uint8_t *)pNodeY + 84);  // 交换 z/y 的颜色字节（+84）
  *((uint8_t *)pNodeY + 84) = *((uint8_t *)pDwArg32 + 84);
  *((uint8_t *)pDwArg32 + 84) = nColorTmp;
LABEL_35:
  if ( *((uint8_t *)Block + 84) == 1 )  // 摘除的是红节点 → 无需重平衡
  {
    pThis3 = pThis;
    if ( pNodeX != *(int **)(pThis[1] + 4) )  // x 不是 header.left 才进入修复循环
    {
      do
      {
        if ( *((uint8_t *)pNodeX + 84) != 1 )
          break;
        pSibling = (uint32_t *)*pNodeXParent;
        if ( pNodeX == (int *)*pNodeXParent )  // x 是左孩 → 兄弟 = 父.right
        {
          pSibling = (uint32_t *)pNodeXParent[2];
          if ( *((uint8_t *)pSibling + 84) == 0 )  // 情形1：兄弟为红 → 换色后旋转
          {
            *((uint8_t *)pSibling + 84) = 1;
            *((uint8_t *)pNodeXParent + 84) = 0;
            sub_46E3F0(pNodeXParent);  // 左旋
            pSibling = (uint32_t *)pNodeXParent[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)pSibling + 85) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*pSibling + 84) != 1 || *(uint8_t *)(pSibling[2] + 84) != 1 )  // 兄弟有红孩
          {
            if ( *(uint8_t *)(pSibling[2] + 84) == 1 )  // 情形2b：右孩为黑 → 先右旋
            {
              *(uint8_t *)(*pSibling + 84) = 1;
              *((uint8_t *)pSibling + 84) = 0;
              sub_46E490(pSibling);  // 右旋
              pSibling = (uint32_t *)pNodeXParent[2];
            }
            *((uint8_t *)pSibling + 84) = *((uint8_t *)pNodeXParent + 84);  // 情形2c：换色+左旋收尾
            *((uint8_t *)pNodeXParent + 84) = 1;
            *(uint8_t *)(pSibling[2] + 84) = 1;
            sub_46E3F0(pNodeXParent);
            break;
          }
        }
        else  // 镜像：x 是右孩
        {
          if ( *((uint8_t *)pSibling + 84) == 0 )  // 情形1（镜像）
          {
            *((uint8_t *)pSibling + 84) = 1;
            *((uint8_t *)pNodeXParent + 84) = 0;
            sub_46E490(pNodeXParent);  // 右旋
            pSibling = (uint32_t *)*pNodeXParent;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)pSibling + 85) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(pSibling[2] + 84) != 1 || *(uint8_t *)(*pSibling + 84) != 1 )  // 兄弟有红孩（镜像）
          {
            if ( *(uint8_t *)(*pSibling + 84) == 1 )  // 情形2b（镜像）：左孩为黑 → 先左旋
            {
              *(uint8_t *)(pSibling[2] + 84) = 1;
              *((uint8_t *)pSibling + 84) = 0;
              sub_46E3F0(pSibling);
              pSibling = (uint32_t *)*pNodeXParent;
            }
            *((uint8_t *)pSibling + 84) = *((uint8_t *)pNodeXParent + 84);  // 情形2c（镜像）
            *((uint8_t *)pNodeXParent + 84) = 1;
            *(uint8_t *)(*pSibling + 84) = 1;
            sub_46E490(pNodeXParent);
            break;
          }
        }
        *((uint8_t *)pSibling + 84) = 0;  // 情形2a：兄弟改红，向上继续
LABEL_53:
        pNodeX = pNodeXParent;  // 上升一层
        bAtRoot = pNodeXParent == *(int **)(pThis3[1] + 4);
        pNodeXParent = (int *)pNodeXParent[1];
      }
      while ( !bAtRoot );
    }
    *((uint8_t *)pNodeX + 84) = 1;  // x 染黑
  }
  sub_46F6E0((char *)Block + 12);  // 销毁节点内值（值位于 +12）
  j__free(Block);  // 释放节点
  nSizeTmp = pThis[2];
  if ( nSizeTmp != 0 )
    pThis[2] = nSizeTmp - 1;  // 容器计数 -1
  *uArg2 = pDwArg3;  // 返回擦除点的后继迭代器
  return uArg2;
}


// ------------------------------------------------------------
// 0x470E80 sub_470E80
// ------------------------------------------------------------
// RB-tree 整树销毁（+85 nil 旗标）：递归右子树 → 中序 sub_470310+free
// 释放节点（与 sub_471230 同构）
char /*stdcall*/ sub_470E80(void **Block)
{
  void **pCurNode; // edi  【当前释放的节点】
  char result; // al
  void **pNextNode; // esi  【中序下一节点】

  pCurNode = Block;
  result = *((uint8_t *)Block + 85);  // +85：nil 旗标 = 到头节点为止
  for ( pNextNode = Block; result == 0; pCurNode = pNextNode )
  {
    sub_470E80(pNextNode[2]);  // 先递归释放右子树
    pNextNode = (void **)*pNextNode;  // 走左孩
    sub_470310(pCurNode);  // 销毁节点值
    j__free(pCurNode);  // 释放节点
    result = *((uint8_t *)pNextNode + 85);
  }
  return result;
}



// ------------------------------------------------------------
// 0x470ED0 sub_470ED0
// ------------------------------------------------------------
// RB-tree erase(iterator)（大节点 map，+152 双色/+153 nil 旗标）：与
// sub_470BB0 同构（RB-DELETE），值销毁 +16；返回后继迭代器
int ***/*thiscall*/ sub_470ED0(uint32_t *this, int ***uArg2, int **pDwArg3)
{
  int **pDwArg32; // ebx  【z：本次擦除的节点（另一棵大值 map 的 erase，与 sub_470BB0 同构）】
  int *pNodeX; // edi  【x：顶替被摘节点位子的孩子（或 nil）】
  int *pNodeY; // ecx  【y：两孩路径中被摘的后继节点】
  int *pNodeXParent; // esi  【x 的父亲（重平衡回溯起点）】
  uint32_t *pThis2; // ecx
  int pHeaderTmp; // eax
  int *pMinSucc; // eax  【leftmost 修正用：x 子树最小节点】
  int pHeader2; // ecx
  bool bAtRoot; // zf  【x 已回溯到 header 左孩 = 结束循环】
  int pHeader3; // eax
  int **pParentSlot; // eax  【待改写的父槽位（左/右孩指针）】
  char nColorTmp; // al  【红黑双色字节交换暂存（+152）】
  uint32_t *pThis3; // ecx
  uint32_t *pSibling; // eax  【重平衡时的兄弟节点 w】
  int nSizeTmp; // eax
  void **pExceptionObject; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t exStrBuf[20]; // [esp+34h] [ebp-34h] BYREF  【异常消息串缓冲】
  int exStrSize; // [esp+48h] [ebp-20h]
  int exStrCap; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]  【z 原节点指针（销毁用）】
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v26; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 153) != 0 )  // +153：nil 旗标 —— 传入了 end() 迭代器
  {
    exStrCap = 15;
    exStrSize = 0;
    exStrBuf[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v26 = 0;
    sub_401740(exStrBuf);
    pExceptionObject = &std::out_of_range::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_46E7B0(&pDwArg3);  // 取后继迭代器，随后 pDwArg3 = 后继节点 y
  if ( *((uint8_t *)*pDwArg32 + 153) != 0 )  // z 左孩为 nil：x = 右孩
  {
    pNodeX = pDwArg32[2];
LABEL_8:
    pNodeXParent = pDwArg32[1];  // x 的父亲 = z 的父亲
    if ( *((uint8_t *)pNodeX + 153) == 0 )
      pNodeX[1] = (int)pNodeXParent;
    pThis2 = pThis;
    pHeaderTmp = pThis[1];
    if ( *(int ***)(pHeaderTmp + 4) == pDwArg32 )  // 修正 leftmost
    {
      *(uint32_t *)(pHeaderTmp + 4) = pNodeX;
    }
    else if ( (int **)*pNodeXParent == pDwArg32 )
    {
      *pNodeXParent = (int)pNodeX;
    }
    else
    {
      pNodeXParent[2] = (int)pNodeX;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)pNodeX + 153) != 0 )
      {
        pMinSucc = pNodeXParent;
      }
      else
      {
        pMinSucc = (int *)sub_46E710(pNodeX);  // 新 leftmost = x 子树最小
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = pMinSucc;
    }
    pHeader2 = pThis2[1];
    bAtRoot = *(uint32_t *)(pHeader2 + 8) == (uint32_t)pDwArg32;
    v23 = pHeader2;
    if ( bAtRoot )  // 修正 rightmost
    {
      if ( *((uint8_t *)pNodeX + 153) != 0 )
        *(uint32_t *)(pHeader2 + 8) = pNodeXParent;
      else
        *(uint32_t *)(v23 + 8) = sub_46E6E0(pNodeX);  // 新 rightmost = x 子树最大
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 153) != 0 )  // z 右孩为 nil：x = 左孩
  {
    pNodeX = *pDwArg32;
    goto LABEL_8;
  }
  // 两孩路径：摘后继 y，x = y.right
  pNodeY = (int *)pDwArg3;
  pNodeX = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;  // z.left.parent = y
  *pNodeY = (int)*pDwArg32;  // y.left = z.left
  if ( pNodeY == pDwArg32[2] )  // y 原本就是 z 的右孩 → x_parent = y
  {
    pNodeXParent = pNodeY;
  }
  else
  {
    pNodeXParent = (int *)pNodeY[1];
    if ( *((uint8_t *)pNodeX + 153) == 0 )
      pNodeX[1] = (int)pNodeXParent;
    *pNodeXParent = (int)pNodeX;
    pNodeY[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)pNodeY;
  }
  pHeader3 = pThis[1];
  if ( *(int ***)(pHeader3 + 4) == pDwArg32 )  // 用 y 顶替 z 的槽位
  {
    *(uint32_t *)(pHeader3 + 4) = pNodeY;
  }
  else
  {
    pParentSlot = (int **)pDwArg32[1];
    if ( *pParentSlot == (int *)pDwArg32 )
      *pParentSlot = pNodeY;
    else
      pParentSlot[2] = pNodeY;
  }
  pNodeY[1] = (int)pDwArg32[1];
  nColorTmp = *((uint8_t *)pNodeY + 152);  // 交换颜色字节（+152）
  *((uint8_t *)pNodeY + 152) = *((uint8_t *)pDwArg32 + 152);
  *((uint8_t *)pDwArg32 + 152) = nColorTmp;
LABEL_35:
  if ( *((uint8_t *)Block + 152) == 1 )  // 摘除红节点 → 无需重平衡
  {
    pThis3 = pThis;
    if ( pNodeX != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)pNodeX + 152) != 1 )
          break;
        pSibling = (uint32_t *)*pNodeXParent;
        if ( pNodeX == (int *)*pNodeXParent )  // x 是左孩
        {
          pSibling = (uint32_t *)pNodeXParent[2];
          if ( *((uint8_t *)pSibling + 152) == 0 )  // 情形1：兄弟为红 → 换色+左旋
          {
            *((uint8_t *)pSibling + 152) = 1;
            *((uint8_t *)pNodeXParent + 152) = 0;
            sub_46ECF0(pNodeXParent);
            pSibling = (uint32_t *)pNodeXParent[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)pSibling + 153) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*pSibling + 152) != 1 || *(uint8_t *)(pSibling[2] + 152) != 1 )  // 兄弟有红孩
          {
            if ( *(uint8_t *)(pSibling[2] + 152) == 1 )  // 情形2b：右孩为黑 → 先右旋
            {
              *(uint8_t *)(*pSibling + 152) = 1;
              *((uint8_t *)pSibling + 152) = 0;
              sub_46E740(pSibling);
              pSibling = (uint32_t *)pNodeXParent[2];
            }
            *((uint8_t *)pSibling + 152) = *((uint8_t *)pNodeXParent + 152);  // 情形2c：换色+左旋收尾
            *((uint8_t *)pNodeXParent + 152) = 1;
            *(uint8_t *)(pSibling[2] + 152) = 1;
            sub_46ECF0(pNodeXParent);
            break;
          }
        }
        else  // 镜像：x 是右孩
        {
          if ( *((uint8_t *)pSibling + 152) == 0 )  // 情形1（镜像）
          {
            *((uint8_t *)pSibling + 152) = 1;
            *((uint8_t *)pNodeXParent + 152) = 0;
            sub_46E740(pNodeXParent);
            pSibling = (uint32_t *)*pNodeXParent;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)pSibling + 153) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(pSibling[2] + 152) != 1 || *(uint8_t *)(*pSibling + 152) != 1 )  // 兄弟有红孩（镜像）
          {
            if ( *(uint8_t *)(*pSibling + 152) == 1 )  // 情形2b（镜像）：左孩为黑 → 先左旋
            {
              *(uint8_t *)(pSibling[2] + 152) = 1;
              *((uint8_t *)pSibling + 152) = 0;
              sub_46ECF0(pSibling);
              pSibling = (uint32_t *)*pNodeXParent;
            }
            *((uint8_t *)pSibling + 152) = *((uint8_t *)pNodeXParent + 152);  // 情形2c（镜像）
            *((uint8_t *)pNodeXParent + 152) = 1;
            *(uint8_t *)(*pSibling + 152) = 1;
            sub_46E740(pNodeXParent);
            break;
          }
        }
        *((uint8_t *)pSibling + 152) = 0;  // 情形2a：兄弟改红，向上继续
LABEL_53:
        pNodeX = pNodeXParent;
        bAtRoot = pNodeXParent == *(int **)(pThis3[1] + 4);
        pNodeXParent = (int *)pNodeXParent[1];
      }
      while ( !bAtRoot );
    }
    *((uint8_t *)pNodeX + 152) = 1;  // x 染黑
  }
  sub_46F490((char *)Block + 16);  // 销毁节点内值（值位于 +16）
  j__free(Block);
  nSizeTmp = pThis[2];
  if ( nSizeTmp != 0 )
    pThis[2] = nSizeTmp - 1;  // 容器计数 -1
  *uArg2 = pDwArg3;  // 返回后继迭代器
  return uArg2;
}


// ------------------------------------------------------------
// 0x471230 sub_471230
// ------------------------------------------------------------
// RB-tree 整树销毁（+153 nil 旗标）：递归右子树 → 中序 sub_470320+free
// 释放节点
char /*stdcall*/ sub_471230(void **Block)
{
  void **pCurNode; // edi  【当前释放的节点】
  char result; // al
  void **pNextNode; // esi  【中序下一节点】

  pCurNode = Block;
  result = *((uint8_t *)Block + 153);  // +153：nil 旗标 = 到头节点为止
  for ( pNextNode = Block; result == 0; pCurNode = pNextNode )
  {
    sub_471230(pNextNode[2]);  // 先递归释放右子树
    pNextNode = (void **)*pNextNode;  // 走左孩
    sub_470320(pCurNode);  // 销毁节点值
    j__free(pCurNode);  // 释放节点
    result = *((uint8_t *)pNextNode + 153);
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
void /*thiscall*/ sub_471280(int this)  // 【CNEntranceChannel__vmt4】
{
  int fld_158; // edi
  int fld_A4; // eax
  int fld_B4; // eax
  int v5; // edi
  int *pThis_40; // ebx
  int v7; // eax
  int v8; // edi
  int *pThis_5C; // ebx
  int v10; // eax
  int fld_AC; // eax
  int fld_B0; // eax
  int fld_A8; // eax
  int fld_14; // edi
  int v15; // eax
  int pThis_74; // ecx
  int v17; // edi
  int fld_6C0; // eax
  DWORD Time; // eax
  int fld_6C02; // eax
  bool fld_6CC; // cl
  int fld_6C4; // edx
  int fld_1422; // edi
  int *i; // ebx
  int v25; // eax
  int fld_6C03; // eax
  DWORD dwNow; // eax
  int fld_6C04; // eax
  bool fld_6CC2; // cl
  int fld_6C42; // edx
  int fld_142; // [esp+8h] [ebp-8h]
  int pThis_9C; // [esp+Ch] [ebp-4h]
  int v33; // [esp+Ch] [ebp-4h]

  sub_433690();  // 【= 主帧 tick（timeGetTime 驱动；'SHUTTER_ON' 截屏音效…】
  *((uint32_t *)dword_8F8528 + 621) = *(uint32_t *)(this + 1456);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, 10) != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 84) != 0 )
  {
    sub_41C860(dword_8F7A24);
  }
  if ( *(uint8_t *)(this + 332) != 0 )
  {
    fld_158 = *(uint32_t *)(this + 344);
    if ( sub_699000(this + 320) >= fld_158 )  // 【clock_now(clk)】
      sub_470A80(this);
  }
  else
  {
    if ( *(uint8_t *)(this + 1460) == 0 )
    {
      sub_432EA0("M_CHARACTER_SELECT", -1, 0, 0);
      *(uint8_t *)(this + 1460) = 1;
    }
    fld_A4 = *(uint32_t *)(this + 164);
    if ( *(uint8_t *)(fld_A4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_A4 + 12) )
    {
      sub_432EA0("CLICK_BUTTON1", -1, 0, 0);
      sub_46F3E0(this);
    }
    fld_B4 = *(uint32_t *)(this + 180);
    if ( *(uint8_t *)(fld_B4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_B4 + 12) )
    {
      sub_432EA0("CLICK_BUTTON3", -1, 0, 0);
      sub_41C860(dword_8F7A24);
    }
    if ( *(uint32_t *)(this + 1464) == 1 )
    {
      v5 = 0;
      pThis_40 = (int *)(this + 64);
      do
      {
        v7 = *pThis_40;
        if ( *pThis_40 != 0
          && *(uint8_t *)(v7 + 17) != 0
          && dword_79BE34 == *(uint32_t *)(v7 + 12)
          && *(uint32_t *)(this + 12) != v5 )
        {
          sub_432EA0("BUTTON_04", -1, 0, 0);
          *(uint32_t *)(this + 12) = v5;
          sub_46E810(this);
        }
        ++v5;
        ++pThis_40;
      }
      while ( v5 < 6 );
      if ( *(uint32_t *)(this + 12) != 6 )
      {
        v8 = 0;
        pThis_5C = (int *)(this + 92);
        do
        {
          v10 = *pThis_5C;
          if ( *pThis_5C != 0
            && *(uint8_t *)(v10 + 17) != 0
            && dword_79BE34 == *(uint32_t *)(v10 + 12)
            && *(uint32_t *)(this + 16) != v8 )
          {
            sub_432EA0("BUTTON_03", -1, 0, 0);
            *(uint32_t *)(this + 16) = v8;
            sub_46E810(this);
          }
          ++v8;
          ++pThis_5C;
        }
        while ( v8 < 5 );
        if ( *(uint32_t *)(this + 16) != 5 )
        {
          fld_AC = *(uint32_t *)(this + 172);
          if ( *(uint8_t *)(fld_AC + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_AC + 12) )
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
          fld_B0 = *(uint32_t *)(this + 176);
          if ( *(uint8_t *)(fld_B0 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_B0 + 12) )
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
          fld_A8 = *(uint32_t *)(this + 168);
          fld_14 = 10 * *(uint32_t *)(this + 20);
          fld_142 = fld_14;
          if ( *(uint8_t *)(fld_A8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_A8 + 12) )
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
              pThis_74 = this + 116;
              while ( *(uint8_t *)(*(uint32_t *)pThis_74 + 16) != 1 || *(uint8_t *)(*(uint32_t *)pThis_74 + 132) != 1 )
              {
                ++v15;
                pThis_74 += 4;
                if ( v15 >= 10 )
                  goto LABEL_52;
              }
              sub_470640((uint32_t *)this, *(uint32_t *)(this + 12), *(uint32_t *)(this + 16), v15 + fld_14);
            }
          }
LABEL_52:
          v17 = 100;
          pThis_9C = this + 156;
          do
          {
            if ( *(uint8_t *)(*(uint32_t *)pThis_9C + 17) != 0 && dword_79BE34 == *(uint32_t *)(*(uint32_t *)pThis_9C + 12) )
            {
              sub_432EA0("BUTTON_04", -1, 0, 0);
              fld_6C0 = *(uint32_t *)(this + 1728);
              if ( fld_6C0 == -1 || fld_6C0 != v17 )
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
            if ( *(uint8_t *)(*(uint32_t *)pThis_9C + 132) == 1 )
            {
              fld_6C02 = *(uint32_t *)(this + 1728);
              fld_6CC = false;
              if ( fld_6C02 != -1 )
              {
                fld_6C4 = *(uint32_t *)(this + 1732);
                if ( fld_6C4 != -1 )
                {
                  if ( fld_6C02 == v17 && fld_6C4 == v17 )
                    fld_6CC = (unsigned int)(*(uint32_t *)(this + 1740) - *(uint32_t *)(this + 1736)) < *(uint32_t *)(this + 1744);
                  *(uint32_t *)(this + 1728) = -1;
                  *(uint32_t *)(this + 1732) = -1;
                  *(uint32_t *)(this + 1736) = -1;
                  *(uint32_t *)(this + 1740) = -1;
                  if ( fld_6CC )
                    sub_470640((uint32_t *)this, *(uint32_t *)(this + 12), (v17 != 100) + 2, 0);
                }
              }
            }
            ++v17;
            pThis_9C += 4;
          }
          while ( v17 - 100 < 2 );
          fld_1422 = fld_142;
          v33 = 0;
          for ( i = (int *)(this + 116); ; ++i )
          {
            v25 = *i;
            if ( *(uint8_t *)(*i + 16) != 0 )
            {
              if ( *(uint8_t *)(v25 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v25 + 12) )
              {
                sub_432EA0("BUTTON_04", -1, 0, 0);
                fld_6C03 = *(uint32_t *)(this + 1728);
                if ( fld_6C03 == -1 || fld_6C03 != fld_1422 )
                {
                  *(uint32_t *)(this + 1728) = fld_1422;
                  *(uint32_t *)(this + 1736) = timeGetTime();
                  dwNow = -1;
                  *(uint32_t *)(this + 1732) = -1;
                }
                else
                {
                  *(uint32_t *)(this + 1732) = fld_1422;
                  dwNow = timeGetTime();
                }
                *(uint32_t *)(this + 1740) = dwNow;
              }
              if ( *(uint8_t *)(*i + 132) == 1 )
              {
                fld_6C04 = *(uint32_t *)(this + 1728);
                fld_6CC2 = false;
                if ( fld_6C04 != -1 )
                {
                  fld_6C42 = *(uint32_t *)(this + 1732);
                  if ( fld_6C42 != -1 )
                  {
                    if ( fld_6C04 == fld_1422 && fld_6C42 == fld_1422 )
                      fld_6CC2 = (unsigned int)(*(uint32_t *)(this + 1740) - *(uint32_t *)(this + 1736)) < *(uint32_t *)(this + 1744);
                    *(uint32_t *)(this + 1728) = -1;
                    *(uint32_t *)(this + 1732) = -1;
                    *(uint32_t *)(this + 1736) = -1;
                    *(uint32_t *)(this + 1740) = -1;
                    if ( fld_6CC2 )
                      break;
                  }
                }
              }
            }
            ++fld_1422;
            if ( ++v33 >= 10 )
              return;
          }
          sub_470640((uint32_t *)this, *(uint32_t *)(this + 12), *(uint32_t *)(this + 16), v33 + fld_142);
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
  uint32_t *pThis_A8; // edi
  void **v4; // esi
  int j; // ebx
  uint32_t *pThis; // ebx
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
  uint32_t pBuf[27]; // [esp+150h] [ebp-78h] BYREF
  int v29; // [esp+1C4h] [ebp-4h]

  pBuf[26] = dword_796E50;
  sub_577780(v27);
  v29 = 0;
  off_77F3FC("CNEntranceChannel::retrieveServerInfo - refresh channel information start");
  off_77F3FC("%s", ArgList);
  pThis_A8 = this + 168;
  for ( i = 6; i != 0; --i )
  {
    *((uint8_t *)pThis_A8 - 56) = 0;
    *(pThis_A8 - 1) = 0;
    *pThis_A8 = 0;
    v4 = (void **)(pThis_A8 + 2);
    for ( j = 5; j != 0; --j )
    {
      if ( *v4 != nullptr )
        j__free(*v4);
      *v4 = nullptr;
      v4[1] = nullptr;
      v4[2] = nullptr;
      v4 += 4;
    }
    pThis_A8 += 35;
  }
  if ( ArgList != nullptr )
  {
    sub_577850((void *)";");
    sub_577310("|");
    sub_577850("#");
    sub_577850(",");
    sub_5772E0(ArgList);
    pThis = this;
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
          strcpy((char *)&pThis[35 * (uint32_t)v11 + 154], off_790590[(uint32_t)v11]);
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
              memset(pBuf, 0, 0x68u);
              strcpy((char *)&pBuf[1], (const char *)sub_577330(v27));
              pBuf[0] = sub_46E260(&pBuf[1]);
              LOBYTE(v21) = (uint8_t)ArgList + 1;
              pBuf[23] = sub_568A70(v21, pBuf[0]);
              if ( pBuf[23] == 0 )
                off_77F3FC(
                  "CNEntranceChannel::retrieveServerInfo - channel %s is unknown.type : %d",
                  (const char *)&pBuf[1],
                  ArgList);
              v14 = (const char *)sub_577330(v27);
              pBuf[14] = j__atol(v14);
              v15 = (const char *)sub_577330(v27);
              pBuf[15] = j__atol(v15);
              LOBYTE(pBuf[22]) = (double)pBuf[15] * 100.0 / (double)pBuf[14] > 95.0;
              strcpy((char *)&pBuf[16], (const char *)sub_577330(v27));
              v16 = (const char *)sub_577330(v27);
              pBuf[21] = j__atol(v16);
              if ( pBuf[23] != 0 )
              {
                v17 = 35 * (uint32_t)ArgList;
                sub_470B20(pBuf);
                v18 = pBuf[15];
                v19 = pThis[35 * (uint32_t)ArgList + 168] < pBuf[15];
                ++pThis[35 * (uint32_t)ArgList + 167];
                if ( v19 )
                  pThis[v17 + 168] = v18;
                off_77F3FC(
                  "\t** '%s' '%s' '%d' %s:%d %d/%d",
                  (const char *)&pThis[v17 + 154],
                  (const char *)&pBuf[1],
                  *(uint32_t *)(pBuf[23] + 28),
                  (const char *)&pBuf[16],
                  pBuf[21],
                  v18,
                  pBuf[14]);
              }
              --*(uint32_t *)v26;
            }
            while ( *(uint32_t *)v26 != 0 );
          }
        }
        if ( ++v23 >= 6 )
        {
          off_77F3FC("CNEntranceChannel::retrieveServerInfo - refresh channel information complete");
          sub_4F8FE0((char)"Etc/pvpChannelList.etc", (int)(pThis + 154), 6);
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
  int nRet; // eax  【返回值槽（兼存线程退出码判定中间值）】
  int *pExitCodeSlot; // edi  【+1464：线程退出码存放槽】
  int nExitCode; // edi

  LOBYTE(nRet) = byte_98BB64;
  if ( byte_98BB64 != 0 )  // HTTP 频道列表线程仍在
  {
    pExitCodeSlot = (int *)(this + 1464);
    *(uint32_t *)(this + 1464) = -1;
    LOBYTE(nRet) = GetExitCodeThread(hObject, (LPDWORD)(this + 1464));
    nExitCode = *pExitCodeSlot;
    switch ( nExitCode )
    {
      case 259:  // STILL_ACTIVE：还在拉取
        nRet = sub_699000(this + 376);  // 【clock_now(clk)】+376：等待计时器
        if ( nRet < 5000 )  // 未到 5 秒继续等
          return nRet;
        off_77F3FC("CNEntranceChannel::checkHTTPChannelDataWork - waiting for thread termination for five seconds.");
        *(uint8_t *)(this + 389) = 0;  // 超时自证失败：清等待旗标
        *(uint8_t *)(this + 390) = 0;
        sub_698F90(this + 376, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】计时器清零
        CloseHandle(hObject);
        break;
      case 1:  // 成功：数据已落在 dword_98BA5C
        std::money_put<char,std::ostreambuf_iterator<char>>::_Putmfld((uint32_t *)this, (const char *)dword_98BA5C);  // retrieveServerInfo 落表
        byte_98BB64 = 0;
        CloseHandle(hObject);
        hObject = nullptr;
        LOBYTE(nRet) = sub_46E810((uint32_t *)this);  // 刷新选区界面频道列表
        return nRet;
      case -2:  // 失败
        off_77F3FC("CNEntranceChannel::checkHTTPChannelDataWork - the http thread failed.");
        CloseHandle(hObject);
        break;
      default:
        return nRet;
    }
    hObject = nullptr;
    LOBYTE(nRet) = (uint8_t)sub_46EE10((int)&hObject, (const char *)(this + 1468));  // 重启 HTTP 线程（+1468 请求串）
  }
  return nRet;
}



// ============================================================
// 【分区 4】登录过场/数据装载（0x471DB0-0x475510）
// MonoLayer 渐隐过场（0x472AF0-0x472B80）、物品数据装载（"ITEM CREATE FAIL!"
// 自证 0x4730A0/0x4730F0）、红黑树/容器辅助（0x473440/0x473920 族）【推断】。
// ============================================================
// ------------------------------------------------------------
// 0x471DB0 sub_471DB0
// ------------------------------------------------------------
// 【推断】登录过场绘制（~310 行）：nArg2==事件id 时画装载屏（背景/图标/进度条/
// "%d / %d" 槽位计数/槽位呼吸灯高亮），nArg2==悬停事件时重画 10 槽+2 翻页按钮高亮
int /*thiscall*/ sub_471DB0(uint32_t *this, int nArg2)
{
  int nDrawEvtId; // ecx  【this+11：本界面接受的绘制事件 id】
  int result; // eax
  int pSpriteBg; // eax  【sub_418DD0(0)：背景绘制对象【推断】】
  int pSpriteLogo; // eax  【sub_418DD0(10)：标饰绘制对象【推断】】
  int pSpriteBar; // eax  【sub_418DD0(1)：进度条绘制对象（带进度浮点）【推断】】
  int pSpriteFrame; // eax  【sub_418DD0(12)：边框绘制对象【推断】】
  int nSlotOfs; // edx  【this+106 槽位数组到 *(this+1) 的偏移差（-424-this）】
  uint8_t *pSlotAlpha; // ebx  【this+106：6 槽透明度字节】
  uint8_t nAlpha; // al
  unsigned int nAlphaNew; // eax
  int nAlphaColor; // edi  【(alpha<<24)|0xFFFFFF：ARGB 绘制色】
  int pSpriteSlotIcon; // eax  【按槽位图标 id 取绘制对象】
  int pSpriteBg2; // eax  【sub_418DD0(0)：背景（重画）【推断】】
  int nSlotIdx; // ebx  【槽位循环索引 0..9】
  int pSlotClock; // ecx  【当前槽计时器地址（每槽 28 字节步进）】
  int pBtnObj; // eax
  int nClockNow; // eax  【槽位计时器当前值】
  int pBtnObj2; // eax  【槽位按钮对象（条件判断用）】
  long double fAlpha; // st7  【绘制透明度（呼吸灯合成值）】
  uint8_t nAlphaDown; // al  【淡出后的透明度】
  unsigned int nAlphaUp; // eax  【淡入中的透明度（封顶 215）】
  int pSpriteSlotGlow; // eax  【sub_418DD0(41)：槽位高亮光晕绘制对象】
  int pBtnObj3; // eax  【槽位按钮对象（按下框用）】
  int pBtnY2; // edi  【按钮 +24：y】
  int pBtnX2; // ebx  【按钮 +20：x】
  int pSpriteSlotFrame; // eax  【按槽位框 id 取绘制对象】
  bool bLast; // zf  【循环到最后一个】
  uint32_t *pHoverBtn; // edi  【this+27：10 个悬停按钮】
  int pBtnObj4; // eax
  int pBtnY3; // edi  【按钮 +24：y】
  int pBtnX3; // ebx  【按钮 +20：x】
  int pSpriteHoverBtn; // eax  【sub_418DD0(58)：悬停高亮绘制对象】
  bool bLoop; // cc  【槽位框循环继续】
  uint32_t *pPageBtn; // edi  【this+37：2 个翻页按钮】
  int pBtnObj5; // eax
  int pBtnY4; // edi
  int pBtnX4; // ebx
  int pSpritePageBtn; // eax  【sub_418DD0(58)：翻页按钮高亮】
  int pBtnX; // [esp+14h] [ebp-58h]  【按钮 +20：x】
  int nSlotIdxSpill; // [esp+18h] [ebp-54h]  【nSlotIdx 的栈暂存】
  int pSlotClock2; // [esp+1Ch] [ebp-50h]  【this+108 槽位计时器（每槽 28 字节）】
  int pBtnY; // [esp+20h] [ebp-4Ch]  【按钮 +24：y】
  int nAlphaSpill; // [esp+20h] [ebp-4Ch]  【透明度暂存（与 pBtnY 复用栈槽）】
  uint32_t *pSlotFrameIds; // [esp+24h] [ebp-48h]  【&unk_6C7BBC：槽位框资源 id 表（步进 6）】
  int nHoverLeft; // [esp+24h] [ebp-48h]  【悬停按钮循环倒计 10..0（栈槽复用）】
  int nPageLeft; // [esp+24h] [ebp-48h]  【翻页按钮循环倒计 2..0（栈槽复用）】
  char Buffer[64]; // [esp+28h] [ebp-44h] BYREF  【"%d / %d" 槽位计数文本】
  int dword_796E502; // [esp+68h] [ebp-4h]
  float fProgress; // [esp+74h] [ebp+8h]  【clock×1/30000：装载进度 0..1【推断】】
  uint32_t *pSlotIconIds; // [esp+74h] [ebp+8h]  【&unk_6C7BCC：槽位图标资源 id 表（步进 6，栈槽复用）】
  uint32_t *pSlotBtn; // [esp+74h] [ebp+8h]  【this+14：槽位按钮数组（栈槽复用）】
  uint32_t *pHoverBtn2; // [esp+74h] [ebp+8h]  【pHoverBtn 栈暂存（栈槽复用）】
  uint32_t *pPageBtn2; // [esp+74h] [ebp+8h]  【pPageBtn 栈暂存（栈槽复用）】

  nDrawEvtId = *(this + 11);
  dword_796E502 = dword_796E50;
  result = nArg2;
  if ( nArg2 == nDrawEvtId )
  {
    sub_471CC0(this - 2);  // this-8：回指 CNEntranceChannel，顺带轮询频道列表线程
    pSpriteBg = sub_418DD0(0);
    if ( pSpriteBg != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pSpriteBg + 152))(pSpriteBg, 0, 0, dword_79C0B0);
    pSpriteLogo = sub_418DD0(10);
    if ( pSpriteLogo != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pSpriteLogo + 152))(pSpriteLogo, 241, 6, dword_79C0B0);
    fProgress = (double)sub_699000((int)(this + 85)) * 0.000033333334;  // 【clock_now(clk)】计时期→进度比
    sub_491530(1, 0);
    pSpriteBar = sub_418DD0(1);
    if ( pSpriteBar != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, float, int, int, int))(*(uint32_t *)pSpriteBar + 128))(
        pSpriteBar,
        149,
        10,
        dword_79C0B0,
        1065353216,
        1065353216,
        COERCE_FLOAT(LODWORD(fProgress)),  // 进度条填充比例
        -1,
        1126891520,
        1126891520);
    sub_491630(1);
    pSpriteFrame = sub_418DD0(12);
    if ( pSpriteFrame != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pSpriteFrame + 152))(pSpriteFrame, 267, 416, dword_79C0B0);
    if ( (int)*(this + 1) < 6 && *(this + 364) == 1 )  // +4：目标槽数 <6 且 +364 已激活
    {
      nSlotOfs = -424 - (uint32_t)this;
      pSlotAlpha = (uint8_t *)(this + 106);
      for ( pSlotIconIds = &unk_6C7BCC; ; pSlotIconIds += 6 )
      {
        nAlpha = *pSlotAlpha;
        if ( &pSlotAlpha[nSlotOfs] == (uint8_t *)*(this + 1) )  // 当前目标槽：透明度爬升到 0xFF
        {
          if ( nAlpha != 0xFF )
          {
            nAlphaNew = nAlpha + 10;
            if ( nAlphaNew >= 0xFF )
              LOBYTE(nAlphaNew) = -1;
            goto LABEL_19;
          }
        }
        else if ( nAlpha != 0 )  // 其他槽：透明度回落到 0
        {
          LOBYTE(nAlphaNew) = (nAlpha - 10) & ((nAlpha <= 0xAu) - 1);
LABEL_19:
          *pSlotAlpha = nAlphaNew;
        }
        if ( *pSlotAlpha != 0 )
        {
          nAlphaColor = (*pSlotAlpha << 24) | 0xFFFFFF;
          pSpriteSlotIcon = sub_418DD0(*pSlotIconIds);
          if ( pSpriteSlotIcon != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pSpriteSlotIcon + 128))(
              pSpriteSlotIcon,
              0,
              0,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              nAlphaColor,
              1333788672,
              1333788672);
          nSlotOfs = -424 - (uint32_t)this;
        }
        ++pSlotAlpha;
        if ( (int)&pSlotAlpha[nSlotOfs] >= 6 )  // 6 槽处理完 → 画文字与高亮
        {
          pSpriteBg2 = sub_418DD0(0);
          if ( pSpriteBg2 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pSpriteBg2 + 152))(pSpriteBg2, 0, 0, dword_79C0B0);
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 57);  // dword_79C0B0：文本绘制对象（+72 设文本）
          sprintf(Buffer, "%d / %d", *(this + 3) + 1, *(this + 4));  // 当前槽/总槽
          (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            368,
            382,
            -1,
            "%s",
            Buffer);  // +80：指定坐标绘文本
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // +76：提交绘制
          pSlotBtn = this + 14;
          nSlotIdx = 0;
          pSlotClock = (int)(this + 108);
          nSlotIdxSpill = 0;
          pSlotFrameIds = &unk_6C7BBC;
          pSlotClock2 = (int)(this + 108);
          do
          {
            pBtnObj = *pSlotBtn;
            if ( *pSlotBtn != 0 && *(uint8_t *)(pBtnObj + 17) != 0 && *(uint8_t *)(pBtnObj + 16) != 0 )
            {
              nClockNow = sub_699000(pSlotClock);  // 【clock_now(clk)】槽位计时器
              pBtnObj2 = *pSlotBtn;
              if ( *(uint8_t *)(*pSlotBtn + 17) != 0 && dword_79BE3C == *(uint32_t *)(pBtnObj2 + 12) || *(uint8_t *)(pBtnObj2 + 132) == 1 )
              {
                if ( nClockNow == 0 )
                  sub_698F90(pSlotClock2, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】计时起点
                nAlphaUp = *((uint8_t *)this + nSlotIdx + 600) + 10;
                if ( nAlphaUp >= 0xD7 )
                  LOBYTE(nAlphaUp) = -41;  // 高亮透明度封顶 215
                *((uint8_t *)this + nSlotIdx + 600) = nAlphaUp;
                fAlpha = sin((double)(unsigned int)nClockNow * 0.006283185307179587) * 35.0 + (double)(uint8_t)nAlphaUp;  // 2π/1000：1 秒呼吸灯正弦
              }
              else
              {
                if ( nClockNow != 0 )
                {
                  *(uint8_t *)(pSlotClock2 + 13) = 0;
                  *(uint8_t *)(pSlotClock2 + 14) = 0;
                  *((uint8_t *)this + nSlotIdx + 600) = -76;  // 未选中：透明度 -76
                  nAlphaSpill = *((uint8_t *)this + nSlotIdx + 600);
                }
                else
                {
                  nAlphaDown = (*((uint8_t *)this + nSlotIdx + 600) - 10) & ((*((uint8_t *)this + nSlotIdx + 600) <= 0xAu) - 1);  // 逐步淡出到 0
                  nAlphaSpill = nAlphaDown;
                  *((uint8_t *)this + nSlotIdx + 600) = nAlphaDown;
                }
                fAlpha = (double)nAlphaSpill;
              }
              sub_491530(2, 0);
              if ( fAlpha > 0.0 )
              {
                pBtnY = *(uint32_t *)(*pSlotBtn + 24);
                pBtnX = *(uint32_t *)(*pSlotBtn + 20);
                pSpriteSlotGlow = sub_418DD0(41);
                if ( pSpriteSlotGlow != 0 )
                {
                  (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pSpriteSlotGlow + 128))(
                    pSpriteSlotGlow,
                    pBtnX - 12,
                    pBtnY - 40,
                    dword_79C0B0,
                    1065353216,
                    1065353216,
                    0,
                    ((uint8_t)(uint64_t)fAlpha << 24) | 0xFFFFFF,
                    1333788672,
                    1333788672);
                  nSlotIdx = nSlotIdxSpill;
                }
              }
              pBtnObj3 = *pSlotBtn;
              if ( *(uint8_t *)(*pSlotBtn + 132) == 1 )  // 槽位被按下 → 叠画按下框
              {
                pBtnY2 = *(uint32_t *)(pBtnObj3 + 24);
                pBtnX2 = *(uint32_t *)(pBtnObj3 + 20);
                pSpriteSlotFrame = sub_418DD0(*pSlotFrameIds);
                if ( pSpriteSlotFrame != 0 )
                  (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pSpriteSlotFrame + 128))(
                    pSpriteSlotFrame,
                    pBtnX2,
                    pBtnY2,
                    dword_79C0B0,
                    1065353216,
                    1065353216,
                    0,
                    -1,
                    1333788672,
                    1333788672);
                nSlotIdx = nSlotIdxSpill;
              }
              sub_491630(2);
            }
            ++pSlotBtn;
            result = (int)(pSlotFrameIds + 6);
            ++nSlotIdx;
            pSlotClock = pSlotClock2 + 28;
            bLoop = (int)(pSlotFrameIds + 6) < (int)"er";  // 循环上界哨兵（IDA 把结束地址显示成 "er"）
            nSlotIdxSpill = nSlotIdx;
            pSlotClock2 += 28;  // 计时器步进 28 字节
            pSlotFrameIds += 6;
          }
          while ( bLoop );
          return result;
        }
      }
    }
    result = sub_418DD0(0);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)result + 152))(result, 0, 0, dword_79C0B0);
  }
  else if ( nArg2 == *(this + 12) )  // 悬停重绘事件
  {
    pHoverBtn = this + 27;
    pHoverBtn2 = this + 27;
    nHoverLeft = 10;
    do  // 10 个悬停按钮
    {
      if ( *(uint8_t *)(*pHoverBtn + 17) != 0 && dword_79BE3C == *(uint32_t *)(*pHoverBtn + 12) )
      {
        sub_491530(2, 0);
        pBtnObj4 = *pHoverBtn;
        pBtnY3 = *(uint32_t *)(*pHoverBtn + 24);
        pBtnX3 = *(uint32_t *)(pBtnObj4 + 20);
        pSpriteHoverBtn = sub_418DD0(58);
        if ( pSpriteHoverBtn != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pSpriteHoverBtn + 152))(pSpriteHoverBtn, pBtnX3, pBtnY3, dword_79C0B0);
        sub_491630(2);
        pHoverBtn = pHoverBtn2;
      }
      ++pHoverBtn;
      bLast = nHoverLeft == 1;
      pHoverBtn2 = pHoverBtn;
      --nHoverLeft;
    }
    while ( !bLast );
    pPageBtn = this + 37;
    pPageBtn2 = this + 37;
    nPageLeft = 2;
    do  // 2 个翻页按钮
    {
      if ( *(uint8_t *)(*pPageBtn + 17) != 0 && dword_79BE3C == *(uint32_t *)(*pPageBtn + 12) )
      {
        sub_491530(2, 0);
        pBtnObj5 = *pPageBtn;
        pBtnY4 = *(uint32_t *)(*pPageBtn + 24);
        pBtnX4 = *(uint32_t *)(pBtnObj5 + 20);
        pSpritePageBtn = sub_418DD0(58);
        if ( pSpritePageBtn != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pSpritePageBtn + 128))(
            pSpritePageBtn,
            pBtnX4,
            pBtnY4,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
        sub_491630(2);
        pPageBtn = pPageBtn2;
      }
      ++pPageBtn;
      bLast = nPageLeft == 1;
      pPageBtn2 = pPageBtn;
      --nPageLeft;
    }
    while ( !bLast );
    return sub_46F500(this - 2);
  }
  return result;
}


// ------------------------------------------------------------
// 0x4723A0 sub_4723A0
// ------------------------------------------------------------
// std::map::erase(first,last) 区间擦除（小节点树，节点 +85 nil 旗标）：
// 全表（first==begin 且 last==end）→ sub_470E80 整树销毁重置；否则逐节点
// sub_470BB0 擦除直到 last，返回 last 迭代器
int */*thiscall*/ sub_4723A0(int **this, int *pDwArg2, int nArg3, int nArg4)
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
  if ( nArg3 == *(uint32_t *)fld_e1 && nArg4 == fld_e1 )
  {
    sub_470E80(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( nArg3 != nArg4 )
    {
      do
      {
        nArg322 = nArg32;
        if ( *(uint8_t *)(nArg32 + 85) == 0 )
        {
          v11 = *(uint32_t *)(nArg32 + 8);
          if ( *(uint8_t *)(v11 + 85) != 0 )
          {
            for ( i = *(uint32_t *)(nArg32 + 4); *(uint8_t *)(i + 85) == 0; i = *(uint32_t *)(i + 4) )
            {
              if ( nArg32 != *(uint32_t *)(i + 8) )
                break;
              nArg32 = i;
            }
            nArg32 = i;
          }
          else
          {
            nArg32 = *(uint32_t *)(nArg32 + 8);
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 85) == 0; j = *(uint32_t *)j )
              nArg32 = j;
          }
        }
        sub_470BB0(this, &nArg3, nArg322);
      }
      while ( nArg32 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x472460 sub_472460
// ------------------------------------------------------------
// std::map::erase(first,last) 区间擦除（大节点树，与 sub_4723A0 同构）：
// 全表 → sub_471230 整树销毁重置；否则循环 sub_470ED0 逐节点擦除
int ***/*thiscall*/ sub_472460(int ****this, int ***uArg2, int **pDwArg3, int **pDwArg4)
{
  int **pDwArg42; // ebx
  int fld_e1; // eax
  int **pDwArg32; // ecx
  uint32_t *fld_e12; // eax
  int **pDwArg322; // edi

  pDwArg42 = pDwArg4;
  fld_e1 = (int)*(this + 1);
  pDwArg32 = pDwArg3;
  if ( pDwArg3 == *(int ***)fld_e1 && pDwArg4 == (int **)fld_e1 )
  {
    sub_471230(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int **)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int **)*(this + 1);
    *uArg2 = **(this + 1);
    return uArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        pDwArg322 = pDwArg32;
        sub_46E7B0((int *)&pDwArg3);
        sub_470ED0(this, &pDwArg4, pDwArg322);
        pDwArg32 = pDwArg3;
      }
      while ( pDwArg3 != pDwArg42 );
    }
    *uArg2 = pDwArg32;
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4724E0 sub_4724E0
// ------------------------------------------------------------
// 清空并释放成员小节点 map（+4 头节点）：区间擦除全部 → free 头节点 → 置空
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
// 清空并释放成员大节点 map（+4 头节点）：与 sub_4724E0 同构
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
// 成员析构辅助：清空 this+1 处的大节点 map 并释放头节点
int /*thiscall*/ sub_472560(int ****this)
{
  int ****pThis_1; // esi
  int **v3; // [esp+4h] [ebp-4h] BYREF

  pThis_1 = this + 1;
  sub_472460(this + 1, &v3, **(this + 2), (int **)*(this + 2));
  j__free(pThis_1[1]);
  pThis_1[1] = nullptr;
  pThis_1[2] = nullptr;
  return 0;
}



// ------------------------------------------------------------
// 0x4725A0 sub_4725A0
// ------------------------------------------------------------
// 成员析构辅助：清空 this+4 处的大节点 map 并释放头节点
int /*thiscall*/ sub_4725A0(int ****this)
{
  int ****pThis_4; // esi
  int **v3; // [esp+4h] [ebp-4h] BYREF

  pThis_4 = this + 4;
  sub_472460(this + 4, &v3, **(this + 5), (int **)*(this + 5));
  j__free(pThis_4[1]);
  pThis_4[1] = nullptr;
  pThis_4[2] = nullptr;
  return 0;
}



// ------------------------------------------------------------
// 0x4725E0 sub_4725E0
// ------------------------------------------------------------
// RB-tree erase(iterator)（又一克隆，节点 +29 nil 旗标/+28 双色字节）：
// 与 sub_470BB0 同构（CLRS RB-DELETE：x/y/x_parent/w），值销毁 +12，
// 迭代器无效抛 out_of_range("invalid map/set<T> iterator")
int ***/*thiscall*/ sub_4725E0(uint32_t *this, int ***uArg2, int **pDwArg3)
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
  void **v17; // esi
  int v18; // eax
  void *Block2; // [esp-8h] [ebp-70h]
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v22[20]; // [esp+34h] [ebp-34h] BYREF
  int v23; // [esp+48h] [ebp-20h]
  int v24; // [esp+4Ch] [ebp-1Ch]
  int v25; // [esp+50h] [ebp-18h] BYREF
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v28; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 29) != 0 )
  {
    v24 = 15;
    v23 = 0;
    v22[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v28 = 0;
    sub_401740(pExceptionObject, (int)v22);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_46E650(&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 29) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 29) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 29) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_46E570(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
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
  if ( *((uint8_t *)pDwArg32[2] + 29) != 0 )
  {
    v4 = *pDwArg32;
    goto LABEL_8;
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 29) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)v5;
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 28);
  *((uint8_t *)v5 + 28) = *((uint8_t *)pDwArg32 + 28);
  *((uint8_t *)pDwArg32 + 28) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 28) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
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
            pThis3 = pThis;
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
            pThis3 = pThis;
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
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 28) = 1;
  }
  v17 = (void **)((char *)Block + 16);
  sub_472460(&v25, **((uint32_t **)Block + 5), *((uint32_t *)Block + 5));
  j__free(v17[1]);
  Block2 = Block;
  v17[1] = nullptr;
  v17[2] = nullptr;
  j__free(Block2);
  v18 = pThis[2];
  if ( v18 != 0 )
    pThis[2] = v18 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x4728C0 sub_4728C0
// ------------------------------------------------------------
// RB-tree 整树销毁（节点 +29 nil 旗标克隆）：递归右子树 → 中序释放节点，
// 节点值经 sub_4725A0 清理（与 sub_470E80 同构）
char /*stdcall*/ sub_4728C0(int ****Block)
{
  int ****Block2; // edi
  char result; // al
  int ****i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 29);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4728C0(i[2]);
    i = (int ****)*i;
    sub_4725A0(Block2);
    j__free(Block2);
    result = *((uint8_t *)i + 29);
  }
  return result;
}



// ------------------------------------------------------------
// 0x472910 sub_472910
// ------------------------------------------------------------
// std::map::erase(first,last) 区间擦除（+29 nil 旗标树，经 sub_4725E0 逐点擦除；
// 与 sub_4723A0 同构）
int */*thiscall*/ sub_472910(int **this, int *pDwArg2, int nArg3, int nArg4)
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
  if ( nArg3 == *(uint32_t *)fld_e1 && nArg4 == fld_e1 )
  {
    sub_4728C0(*(int *****)(fld_e1 + 4));
    (*(this + 1))[1] = (int)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( nArg3 != nArg4 )
    {
      do
      {
        nArg322 = nArg32;
        if ( *(uint8_t *)(nArg32 + 29) == 0 )
        {
          v11 = *(uint32_t *)(nArg32 + 8);
          if ( *(uint8_t *)(v11 + 29) != 0 )
          {
            for ( i = *(uint32_t *)(nArg32 + 4); *(uint8_t *)(i + 29) == 0; i = *(uint32_t *)(i + 4) )
            {
              if ( nArg32 != *(uint32_t *)(i + 8) )
                break;
              nArg32 = i;
            }
            nArg32 = i;
          }
          else
          {
            nArg32 = *(uint32_t *)(nArg32 + 8);
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 29) == 0; j = *(uint32_t *)j )
              nArg32 = j;
          }
        }
        sub_4725E0(this, &nArg3, nArg322);
      }
      while ( nArg32 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4729D0 sub_4729D0
// ------------------------------------------------------------
// 构造：初始化两棵 map 头节点（sub_46EE90 小节点树 +85 旗标 / sub_46EED0
// 大节点树 +29 旗标），各自自环并清计数（+2/+5）
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
// 清空两棵成员 map（+12 小节点树经 sub_472910、+0 大节点树经 sub_4723A0）
// 并 free 各自头节点置空
void /*thiscall*/ sub_472A60(int this)
{
  int *fld_10; // eax
  int pThis_C; // edi
  int v4; // [esp-8h] [ebp-28h]
  int v5; // [esp-8h] [ebp-28h]
  int *fld_4; // [esp-4h] [ebp-24h]
  int v7[2]; // [esp+Ch] [ebp-14h] BYREF
  int v8; // [esp+1Ch] [ebp-4h]

  v7[1] = this;
  fld_10 = *(int **)(this + 16);
  pThis_C = this + 12;
  v4 = *fld_10;
  v8 = 0;
  sub_472910((int **)(this + 12), v7, v4, (int)fld_10);
  j__free(*(void **)(pThis_C + 4));
  *(uint32_t *)(pThis_C + 4) = 0;
  *(uint32_t *)(pThis_C + 8) = 0;
  fld_4 = *(int **)(this + 4);
  v5 = *fld_4;
  v8 = -1;
  sub_4723A0((int **)this, v7, v5, (int)fld_4);
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
int /*thiscall*/ sub_472B30(int *this, char pszArg2, int nArg3)
{
  int fld_e15; // ecx
  int result; // eax

  if ( pszArg2 != 0 )
  {
    fld_e15 = *(this + 15);
    if ( fld_e15 != 0 )
      sub_4926A0(fld_e15);
    byte_99FB90 = pszArg2;
    byte_99FBED = 0;
    byte_99FBEE = 0;
    dword_99FB94 = nArg3;
    return nArg3;
  }
  else
  {
    byte_99FB90 = 0;
    dword_99FB94 = nArg3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x472B80 sub_472B80
// ------------------------------------------------------------
// 过场渐隐绘制：3000ms 内 sub_4049C0 透明度插值，超时自关
char /*thiscall*/ sub_472B80(int *this)
{
  int fld_e15; // edi
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // esi
  int v7; // [esp-10h] [ebp-10h]
  int v8; // [esp-10h] [ebp-10h]

  if ( byte_99FB90 == 0 )
    return 1;
  fld_e15 = *(this + 15);
  if ( fld_e15 == 0 )
    return 1;
  sub_698F90((int)&unk_99FBE0, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( sub_699000((int)&unk_99FBE0) >= dword_99FB94 + 3000 )  // 【clock_now(clk)】
  {
    byte_99FB90 = 0;
    return 1;
  }
  LOBYTE(v3) = -1;
  if ( sub_699000((int)&unk_99FBE0) >= dword_99FB94 )  // 【clock_now(clk)】
  {
    v4 = sub_699000((int)&unk_99FBE0);  // 【clock_now(clk)】
    v3 = (uint64_t)sub_4049C0(255.0, 0.0, v4 - dword_99FB94, 3000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
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
  if ( sub_699000((int)&unk_99FBE0) >= dword_99FB94 + 300 )  // 【clock_now(clk)】
  {
    if ( sub_699000((int)&unk_99FBE0) >= dword_99FB94 + 600 )  // 【clock_now(clk)】
    {
      if ( sub_699000((int)&unk_99FBE0) < dword_99FB94 + 2700 )  // 【clock_now(clk)】
      {
        v6 = 255;
LABEL_18:
        sub_4938F0(fld_e15);
        sub_491F80(-1, -1, -1, v6, 1);
        sub_491D00(dword_79C0B0, 320, 240, 0.0);
        return 0;
      }
      v8 = -2700 - dword_99FB94 + sub_699000((int)&unk_99FBE0);  // 【clock_now(clk)】
      v5 = sub_423A80(255, 0, v8, 300);
    }
    else
    {
      v7 = -300 - dword_99FB94 + sub_699000((int)&unk_99FBE0);  // 【clock_now(clk)】
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
// 取成员数组元素：返回 *(this + 119 + pArg2)（dword 下标访问器）
int /*thiscall*/ sub_472D40(uint32_t *this, int pArg2)
{
  return *(this + pArg2 + 119);
}



// ------------------------------------------------------------
// 0x472D60 sub_472D60
// ------------------------------------------------------------
// 28 字节/条目的批量拷贝（memcpy 变体）：[pszArg1,pszArg2) → pszArg3，
// 0x1C=28 为单条大小
char */*cdecl*/ sub_472D60(char *pszArg1, char *pszArg2, char *pszArg3)
{
  char *pszArg12; // edx
  char *result; // eax
  const void *pszArg122; // esi
  void *v6; // edi

  pszArg12 = pszArg1;
  result = pszArg3;
  while ( pszArg12 != pszArg2 )
  {
    pszArg122 = pszArg12;
    v6 = result;
    pszArg12 += 28;
    result += 28;
    qmemcpy(v6, pszArg122, 0x1Cu);
  }
  return result;
}



// ------------------------------------------------------------
// 0x472D90 sub_472D90
// ------------------------------------------------------------
// 三参转发：直呼 sub_4FBD40（stub）
int /*cdecl*/ sub_472D90(int nArg1, int nArg2, int nArg3)
{
  return sub_4FBD40(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x472DB0 sub_472DB0
// ------------------------------------------------------------
// 28 字节/条目的批量搬运（可空目标，memmove 变体）：[pszArg1,pszArg2) →
// pszArg3，返回新游标
char */*cdecl*/ sub_472DB0(char *pszArg1, char *pszArg2, char *pszArg3)
{
  char *pszArg12; // edx
  char *result; // eax

  pszArg12 = pszArg1;
  for ( result = pszArg3; pszArg12 != pszArg2; result += 28 )
  {
    if ( result != nullptr )
      qmemcpy(result, pszArg12, 0x1Cu);
    pszArg12 += 28;
  }
  return result;
}



// ------------------------------------------------------------
// 0x472DF0 sub_472DF0
// ------------------------------------------------------------
// RB-tree 整树销毁（+21 nil 旗标克隆）：递归右子树 → 中序 sub_470310+free
char /*stdcall*/ sub_472DF0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_472DF0(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x472E30 sub_472E30
// ------------------------------------------------------------
// std::map::lower_bound（int 键 = 节点 dword#3，+21 nil 旗标）：首个
// 键 >= uArg3 的节点；不存在则返回 end
int **/*thiscall*/ sub_472E30(int **this, int **pDwArg2, uint32_t *uArg3)
{
  int *fld_e1; // edx
  int *v4; // eax

  fld_e1 = *(this + 1);
  v4 = (int *)fld_e1[1];
  while ( *((uint8_t *)v4 + 21) == 0 )
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
// 0x472EA0 sub_472EA0
// ------------------------------------------------------------
// 三参转发：直呼 sub_44BD30（stub）
uint32_t */*stdcall*/ sub_472EA0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  return sub_44BD30(uArg1, uArg2, uArg3);
}



// ------------------------------------------------------------
// 0x472EC0 sub_472EC0
// ------------------------------------------------------------
// 转发 sub_472DB0（28 字节/条目批量搬运）
char */*stdcall*/ sub_472EC0(char *pszArg1, char *pszArg2, char *pszArg3)
{
  return sub_472DB0(pszArg1, pszArg2, pszArg3);
}



// ------------------------------------------------------------
// 0x472EE0 sub_472EE0
// ------------------------------------------------------------
// 三参转发：直呼 sub_4FBDE0（stub）
int /*stdcall*/ sub_472EE0(int nArg1, int nArg2, int nArg3)
{
  return sub_4FBDE0(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x472F00 sub_472F00
// ------------------------------------------------------------
// 释放两块 vector 缓冲（+24 与 +8 处 begin/end/capEnd 置空并 free）
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
// 清空两个 std::string 成员（+4/+20 与 +32/+48，SSO：容量 >=0x10 才 free，
// 复位 size=0/cap=15/首字节 0）
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
// 全局 map dword_99FBA4 查找（sub_472E30 lower_bound，int 键 nArg1）：
// 命中返回节点 dword#4（+16），未命中返回 0
int /*cdecl*/ sub_472F90(int nArg1)
{
  int *v1; // ecx
  int *v3; // [esp+0h] [ebp-4h] BYREF

  v3 = v1;
  sub_472E30(&dword_99FBA4, &v3, &nArg1);
  if ( v3 == (int *)dword_99FBA8 )
    return 0;
  else
    return v3[4];
}



// ------------------------------------------------------------
// 0x472FC0 sub_472FC0
// ------------------------------------------------------------
// 析构：先 sub_472F00 清缓冲，pszArg2&1 时再 free 自身（delete 语义）
void */*thiscall*/ sub_472FC0(void *Block, char pszArg2)
{
  sub_472F00((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x472FF0 sub_472FF0
// ------------------------------------------------------------
// 构造：两个 std::string 成员置空（+4 与 +32 的 SSO 内联缓冲，cap=15），
// 并对两串各做一次 sub_406D00 赋值
uint32_t */*thiscall*/ sub_472FF0(uint32_t *this)
{
  uint32_t *pThis_1; // eax
  unsigned int fld_e6; // edx
  uint32_t *pThis_12; // ebx
  unsigned int fld_e13; // ecx
  uint32_t *pThis_8; // edx
  uint32_t *pThis_82; // ebx
  char v9[4]; // [esp+Ch] [ebp-14h] BYREF
  void *pThis; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  pThis_1 = this + 1;
  *(this + 6) = 15;
  *(this + 5) = 0;
  pThis = this;
  *((uint8_t *)this + 4) = 0;
  *(this + 13) = 15;
  *(this + 12) = 0;
  v11 = 0;
  *((uint8_t *)this + 32) = 0;
  fld_e6 = *(this + 6);
  LOBYTE(v11) = 1;
  if ( fld_e6 < 0x10 )
    pThis_12 = this + 1;
  else
    pThis_12 = (uint32_t *)*pThis_1;
  if ( fld_e6 >= 0x10 )
    pThis_1 = (uint32_t *)*pThis_1;
  sub_406D00(v9, pThis_1, (char *)pThis_12 + *(this + 5));
  fld_e13 = *(this + 13);
  pThis_8 = this + 8;
  if ( fld_e13 < 0x10 )
    pThis_82 = this + 8;
  else
    pThis_82 = (uint32_t *)*pThis_8;
  if ( fld_e13 >= 0x10 )
    pThis_8 = (uint32_t *)*pThis_8;
  sub_406D00(v9, pThis_8, (char *)pThis_82 + *(this + 12));
  return this;
}



// ------------------------------------------------------------
// 0x4730A0 sub_4730A0
// ------------------------------------------------------------
// 物品数据装载（"ITEM CREATE FAIL! ItemIndex %d" 自证）【推断】
char **/*thiscall*/ sub_4730A0(char **this, char **pszArg2, char *pszArg3)
{
  char *fld_e2; // ebx
  char *v4; // eax
  char *pszArg32; // edx
  const void *v6; // esi
  void *pszArg322; // edi

  fld_e2 = *(this + 2);
  v4 = pszArg3 + 28;
  if ( pszArg3 + 28 != fld_e2 )
  {
    pszArg32 = pszArg3;
    do
    {
      v6 = v4;
      pszArg322 = pszArg32;
      v4 += 28;
      pszArg32 += 28;
      qmemcpy(pszArg322, v6, 0x1Cu);
    }
    while ( v4 != fld_e2 );
  }
  *(this + 2) -= 28;
  *pszArg2 = pszArg3;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4730F0 sub_4730F0
// ------------------------------------------------------------
// 物品数据装载 II（同上自证串）【推断】
int **/*stdcall*/ sub_4730F0(int nArg1, uint32_t *pArg2, int pArg3, int *pDwArg4, unsigned int Seed)
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
  int pObj; // eax
  int pObj2; // edi
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
  result = *(int ***)(pArg3 + 96);
  v6 = *result;
  v7 = *result == (int *)result;
  v35 = 0;
  for ( i = v6; !v7; ++v35 )
  {
    v8 = i;
    Seed_3 = 0;
    v9 = (uint32_t *)sub_53A220((void *)i[2], nullptr);  // 【巨函数（size=17574）→ src/combat/bigfunc_53A220…】
    v10 = __RTDynamicCast(v9, 0, &CNRDPassiveObject `RTTI Type Descriptor', &CNMapObject `RTTI Type Descriptor', 0);
    v40 = v10;
    if ( v10 != nullptr )
    {
      sub_45FE80(nArg1, (int)v8, 33, *pDwArg4, (int)v10, 0, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(*v10 + 112))(v10, v8[3], v8[4], v8[5]);
      ++*pDwArg4;
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
              v17 = pArg2[2];
              if ( v17 == 0 || v16 >= (pArg2[3] - v17) / 28 )
                break;
              v18 = pArg2[2] + *(uint32_t *)ArgList;
              if ( *(uint8_t *)(v18 + 20) == 1 && *(uint32_t *)(v18 + 24) == v35 )
              {
                v19 = 28 * v16;
                (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t))(*v40 + 728))(
                  v40,
                  *(uint32_t *)(v19 + pArg2[2] + 8),
                  *(uint32_t *)(v19 + pArg2[2] + 12),
                  *(uint32_t *)(v19 + pArg2[2] + 4));
                v20 = (uint32_t *)(v19 + pArg2[2]);
                if ( v40[78] < 0x10u )
                  v21 = v40 + 73;
                else
                  v21 = (uint32_t *)v40[73];
                *(uint32_t *)ArgList = v21;
                v22 = (*(int (/*cdecl*/ **)(uint32_t, uint32_t, uint32_t))(*v40 + 52))(v20[2], v20[3], v20[1]);
                off_77F3FC((char *)&byte_6C8660, *(uint32_t *)ArgList, v22);
                sub_4730A0(&v34, v19 + pArg2[2]);
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
              v27 = pArg2[6];
              if ( v27 == 0 || v26 >= (pArg2[7] - v27) / 20 )
                break;
              v28 = (uint32_t *)(pArg2[6] + *(uint32_t *)ArgList);
              if ( *v28 == v34 )
              {
                v29 = (void *)v28[2];
                if ( v29 != (void *)0xFFFF )
                {
                  pObj = sub_522300(v29, v28[3], 0, 0, v28[4], 1);
                  pObj2 = pObj;
                  if ( pObj != 0 )
                  {
                    v32 = v28[1];
                    v33 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);
                    off_77F3FC(asc_6C8608, i[2], v34, v32, *(uint32_t *)(v33 + 4));
                    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*v40 + 720))(v40, v32, pObj2);
                    *(uint32_t *)(pArg2[6] + 20 * v26) = -345;
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
    v7 = *v8 == *(uint32_t *)(pArg3 + 96);
    i = (int *)*v8;
  }
  return result;
}


// ------------------------------------------------------------
// 0x473440 sub_473440
// ------------------------------------------------------------
// 红黑树/有序容器节点插入辅助（CRT 容器模板实体）
int */*thiscall*/ sub_473440(int **this, int *pDwArg2, char pszArg3, int *pDwArg4, int nArg5)
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
// 0x4735F0 sub_4735F0
// ------------------------------------------------------------
// 抛 std::length_error("vector<T> too long")（vector 扩容上限辅助）
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
  sub_4015C0((void *)"vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x473660 sub_473660
// ------------------------------------------------------------
// RB-tree erase(iterator)（又一克隆：节点 +21 nil 旗标/+20 双色字节，
// 与 sub_470BB0 同构；值销毁与后继计算换用 sub_41C5E0/52E300/542490 族）
int ***/*thiscall*/ sub_473660(uint32_t *this, int ***uArg2, int **pDwArg3)
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
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  size_t v20; // [esp+34h] [ebp-34h] BYREF
  char v21; // [esp+38h] [ebp-30h]
  int v22; // [esp+48h] [ebp-20h]
  int v23; // [esp+4Ch] [ebp-1Ch]
  int v24; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v27; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 21) != 0 )
  {
    v23 = 15;
    v22 = 0;
    v21 = 0;
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v27 = 0;
    sub_401740(pExceptionObject, &v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C5E0((int *)&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 21) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_52E300(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
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
  if ( *((uint8_t *)pDwArg32[2] + 21) != 0 )
  {
    v4 = *pDwArg32;
    goto LABEL_8;
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)v5;
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 20);
  *((uint8_t *)v5 + 20) = *((uint8_t *)pDwArg32 + 20);
  *((uint8_t *)pDwArg32 + 20) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 20) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
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
            pThis3 = pThis;
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
            pThis3 = pThis;
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
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 20) = 1;
  }
  j__free(Block);
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x473920 sub_473920
// ------------------------------------------------------------
// 红黑树/有序容器查找-插入辅助（CRT 容器模板实体）
int /*thiscall*/ sub_473920(int **this, int pArg2, int *pDwArg3)
{
  int *pDwArg32; // ebx
  int *fld_e1; // esi
  int v6; // eax
  bool v7; // cl
  int v8; // edx
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
      v10 = *sub_473440(this, (int *)&pDwArg3, 1, fld_e1, (int)pDwArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4A3B30(&pDwArg3);
    fld_e12 = pDwArg3;
  }
  if ( fld_e12[3] >= *pDwArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else
  {
    v12 = *sub_473440(this, (int *)&pDwArg3, v13, fld_e1, (int)pDwArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4739E0 sub_4739E0
// ------------------------------------------------------------
// vector 预留容量（28 字节/条目）：new 一块 n×28 缓冲，begin=end=首、
// capEnd=末；超上限（0x9249249×28 溢出界）抛 length_error
char /*thiscall*/ sub_4739E0(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x9249249 )
    sub_4735F0(this);
  pMem = (char *)operator new(28 * uArg2);
  *(this + 3) = &pMem[28 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x473A30 sub_473A30
// ------------------------------------------------------------
// vector 预留容量（20 字节/条目）：与 sub_4739E0 同构，上限 0xCCCCCCC 条
char /*thiscall*/ sub_473A30(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0xCCCCCCC )
    sub_4735F0(this);
  pMem = (char *)operator new(20 * uArg2);
  *(this + 3) = &pMem[20 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x473A80 sub_473A80
// ------------------------------------------------------------
// vector 定点插入（8 字节/条目）：容量够则原地腾洞（/8 计数），不够则
// 1.5 倍扩容重建；0x1FFFFFFF=最大条目数（×8 不溢出 32 位的上限）
void /*thiscall*/ sub_473A80(int this, int nArg2, unsigned int uArg3, int pArg4)
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
      sub_42CB90(this);
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
// 0x473CD0 sub_473CD0
// ------------------------------------------------------------
// std::map::erase(first,last) 区间擦除（+21 nil 旗标树，经 sub_473660 逐点
// 擦除；与 sub_4723A0/472910 同构）
int */*thiscall*/ sub_473CD0(int **this, int *pDwArg2, int nArg3, int nArg4)
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
  if ( nArg3 == *(uint32_t *)fld_e1 && nArg4 == fld_e1 )
  {
    sub_472DF0(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( nArg3 != nArg4 )
    {
      do
      {
        nArg322 = nArg32;
        if ( *(uint8_t *)(nArg32 + 21) == 0 )
        {
          v11 = *(uint32_t *)(nArg32 + 8);
          if ( *(uint8_t *)(v11 + 21) != 0 )
          {
            for ( i = *(uint32_t *)(nArg32 + 4); *(uint8_t *)(i + 21) == 0; i = *(uint32_t *)(i + 4) )
            {
              if ( nArg32 != *(uint32_t *)(i + 8) )
                break;
              nArg32 = i;
            }
            nArg32 = i;
          }
          else
          {
            nArg32 = *(uint32_t *)(nArg32 + 8);
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 21) == 0; j = *(uint32_t *)j )
              nArg32 = j;
          }
        }
        sub_473660(this, &nArg3, nArg322);
      }
      while ( nArg32 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x473D90 sub_473D90
// ------------------------------------------------------------
// std::map::erase(first,last) 区间擦除（+21 旗标树克隆；全表改走
// sub_41CA20 整树销毁，其余经 sub_473660 逐点擦除）
int */*thiscall*/ sub_473D90(int **this, int *pDwArg2, int nArg3, int nArg4)
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
  if ( nArg3 == *(uint32_t *)fld_e1 && nArg4 == fld_e1 )
  {
    sub_41CA20(*(void **)(fld_e1 + 4));
    (*(this + 1))[1] = (int)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( nArg3 != nArg4 )
    {
      do
      {
        nArg322 = nArg32;
        if ( *(uint8_t *)(nArg32 + 21) == 0 )
        {
          v11 = *(uint32_t *)(nArg32 + 8);
          if ( *(uint8_t *)(v11 + 21) != 0 )
          {
            for ( i = *(uint32_t *)(nArg32 + 4); *(uint8_t *)(i + 21) == 0; i = *(uint32_t *)(i + 4) )
            {
              if ( nArg32 != *(uint32_t *)(i + 8) )
                break;
              nArg32 = i;
            }
            nArg32 = i;
          }
          else
          {
            nArg32 = *(uint32_t *)(nArg32 + 8);
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 21) == 0; j = *(uint32_t *)j )
              nArg32 = j;
          }
        }
        sub_473660(this, &nArg3, nArg322);
      }
      while ( nArg32 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x473E50 sub_473E50
// ------------------------------------------------------------
// vector<int> 定点插入（4 字节/条目，>>2 计数）：原地腾洞或 1.5 倍扩容
// 重建；0x3FFFFFFF=最大条目数（×4 不溢出）
unsigned int /*thiscall*/ sub_473E50(int this, int Src, unsigned int uArg3, int *pDwArg4)
{
  int fld_4; // edx
  unsigned int result; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v10; // eax
  int fld_85; // ecx
  int fld_86; // eax
  char *fld_42; // eax
  void *v15; // eax
  int fld_43; // eax
  int fld_87; // ecx
  unsigned int v18; // edi
  uint8_t *fld_83; // eax
  unsigned int v21; // edx
  int v22; // ecx
  char *fld_84; // edi
  int v24; // edi
  char *pMem; // [esp+8h] [ebp-4h]
  int Srcb; // [esp+14h] [ebp+8h]
  char *Srca; // [esp+14h] [ebp+8h]
  int v28; // [esp+18h] [ebp+Ch]
  int v29; // [esp+18h] [ebp+Ch]

  fld_4 = *(uint32_t *)(this + 4);
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_4735F0(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(uint8_t **)(this + 8);
      v21 = (int)&fld_83[-Src] >> 2;
      v22 = 4 * uArg3;
      v29 = (int)fld_83;
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);
        sub_5DAF70((void *)Src, v24, v29);
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);
        fld_84 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = fld_84;
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )
      {
        if ( fld_4 != 0 )
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
        else
          fld_86 = 0;
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;
      else
        fld_87 = 0;
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &pMem[v28];
      *(uint32_t *)(this + 8) = &pMem[4 * v18];
      *(uint32_t *)(this + 4) = pMem;
      return (unsigned int)pMem;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x474030 sub_474030
// ------------------------------------------------------------
// vector 拷贝构造（28 字节/条目）：按源元素数 sub_4739E0 预留后整块搬运
char **/*thiscall*/ sub_474030(char **this, int pArg2)
{
  unsigned int v2; // eax
  char *v5; // [esp-14h] [ebp-34h]
  char *v6; // [esp-10h] [ebp-30h]
  char *fld_e1; // [esp-Ch] [ebp-2Ch]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(pArg2 + 4);
  v10 = &v8;
  pThis = this;
  if ( v2 != 0 )
    v2 = (int)(*(uint32_t *)(pArg2 + 8) - v2) / 28;
  if ( sub_4739E0(this, v2) != 0 )
  {
    fld_e1 = *(this + 1);
    v6 = *(char **)(pArg2 + 8);
    v5 = *(char **)(pArg2 + 4);
    v11 = 0;
    *(this + 2) = sub_472DB0(v5, v6, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x4740D0 sub_4740D0
// ------------------------------------------------------------
// vector 拷贝构造（20 字节/条目）：与 sub_474030 同构，搬运走 sub_4FBDE0
uint32_t */*thiscall*/ sub_4740D0(uint32_t *this, int pArg2)
{
  unsigned int v2; // eax
  int v5; // [esp-14h] [ebp-34h]
  int v6; // [esp-10h] [ebp-30h]
  int fld_e1; // [esp-Ch] [ebp-2Ch]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(pArg2 + 4);
  v10 = &v8;
  pThis = this;
  if ( v2 != 0 )
    v2 = (int)(*(uint32_t *)(pArg2 + 8) - v2) / 20;
  if ( sub_473A30(this, v2) != 0 )
  {
    fld_e1 = *(this + 1);
    v6 = *(uint32_t *)(pArg2 + 8);
    v5 = *(uint32_t *)(pArg2 + 4);
    v11 = 0;
    *(this + 2) = sub_4FBDE0(v5, v6, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x474170 sub_474170
// ------------------------------------------------------------
// vector 拷贝赋值（28 字节/条目）：自赋值直返；按容量够/不够分别
// 原地覆写或重配（sub_4739E0）
int /*thiscall*/ sub_474170(int this, int pArg2)
{
  int pArg22; // edi
  int v4; // eax
  unsigned int v5; // ecx
  char *fld_4; // ebx
  unsigned int fld_8; // eax
  int v9; // eax
  unsigned int fld_C; // eax
  char *v11; // edi
  unsigned int v12; // eax

  pArg22 = pArg2;
  if ( this == pArg2 )
    return this;
  v4 = *(uint32_t *)(pArg2 + 4);
  if ( v4 == 0 || (v5 = (*(uint32_t *)(pArg2 + 8) - v4) / 28) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  fld_4 = *(char **)(this + 4);
  if ( fld_4 != nullptr )
  {
    pArg22 = pArg2;
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 28;
  }
  else
  {
    fld_8 = 0;
  }
  if ( v5 > fld_8 )
  {
    if ( fld_4 != nullptr )
    {
      pArg22 = pArg2;
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 28;
    }
    else
    {
      fld_C = 0;
    }
    if ( v5 <= fld_C )
    {
      v11 = (char *)(*(uint32_t *)(pArg2 + 4) + 28 * sub_52AEF0(this));
      sub_472D60(*(char **)(pArg2 + 4), v11, fld_4);
      *(uint32_t *)(this + 8) = sub_472DB0(v11, *(char **)(pArg2 + 8), *(char **)(this + 8));
      return this;
    }
    if ( fld_4 != nullptr )
      j__free(*(void **)(this + 4));
    v12 = sub_52AEF0(pArg22);
    if ( sub_4739E0((uint32_t *)this, v12) != 0 )
      *(uint32_t *)(this + 8) = sub_472EC0(*(char **)(pArg22 + 4), *(char **)(pArg22 + 8), *(char **)(this + 4));
    return this;
  }
  sub_472D60(*(char **)(pArg22 + 4), *(char **)(pArg22 + 8), *(char **)(this + 4));
  v9 = *(uint32_t *)(pArg22 + 4);
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 28 * ((*(uint32_t *)(pArg22 + 8) - v9) / 28);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x474300 sub_474300
// ------------------------------------------------------------
// vector 拷贝赋值（20 字节/条目）：与 sub_474170 同构（自赋值直返、
// 容量够/不够两路，sub_473A30 重配）
int /*thiscall*/ sub_474300(int this, int *pDwArg2)
{
  int v4; // eax
  unsigned int v5; // ecx
  int fld_4; // edi
  unsigned int fld_8; // eax
  int v9; // eax
  unsigned int fld_C; // eax
  unsigned int v11; // eax
  int v12; // [esp+10h] [ebp+8h]

  if ( (int *)this == pDwArg2 )
    return this;
  v4 = pDwArg2[1];
  if ( v4 == 0 || (v5 = (pDwArg2[2] - v4) / 20) == 0 )
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
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 20;
  else
    fld_8 = 0;
  if ( v5 > fld_8 )
  {
    if ( fld_4 != 0 )
      fld_C = (*(uint32_t *)(this + 12) - fld_4) / 20;
    else
      fld_C = 0;
    if ( v5 <= fld_C )
    {
      v12 = pDwArg2[1] + 20 * sub_45E580((int *)this);
      sub_472D90(pDwArg2[1], v12, fld_4);
      *(uint32_t *)(this + 8) = sub_4FBDE0(v12, pDwArg2[2], *(uint32_t *)(this + 8));
      return this;
    }
    if ( fld_4 != 0 )
      j__free(*(void **)(this + 4));
    v11 = sub_45E580(pDwArg2);
    if ( sub_473A30((uint32_t *)this, v11) != 0 )
      *(uint32_t *)(this + 8) = sub_472EE0(pDwArg2[1], pDwArg2[2], *(uint32_t *)(this + 4));
    return this;
  }
  sub_4FBD40(pDwArg2[1], pDwArg2[2], fld_4);
  v9 = pDwArg2[1];
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 20 * ((pDwArg2[2] - v9) / 20);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x474480 sub_474480
// ------------------------------------------------------------
// vector resize（int 元素，>>2 计数）：缩小则收 end，放大则经
// sub_473E50 在尾部补 nArg3
unsigned int /*thiscall*/ sub_474480(unsigned int *this, unsigned int uArg2, int nArg3)
{
  int fld_e1; // edx
  unsigned int result; // eax
  int fld_e2; // eax
  void *v7; // edx

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    result = (int)(*(this + 2) - fld_e1) >> 2;
  else
    result = 0;
  if ( result >= uArg2 )
  {
    if ( fld_e1 != 0 )
    {
      result = *(this + 2);
      if ( uArg2 < (int)(result - fld_e1) >> 2 )
      {
        v7 = (void *)(fld_e1 + 4 * uArg2);
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
    if ( fld_e1 != 0 )
      fld_e2 = (int)(*(this + 2) - fld_e1) >> 2;
    else
      fld_e2 = 0;
    return sub_473E50((int)this, *(this + 2), uArg2 - fld_e2, &nArg3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x474510 sub_474510
// ------------------------------------------------------------
// 聚合对象浅拷贝：首 dword + 两个 vector（28B/20B 条目，sub_474030/
// sub_4740D0 拷贝构造）
char **/*thiscall*/ sub_474510(char **this, char **pszArg2)
{
  *this = *pszArg2;
  sub_474030(this + 1, (int)(pszArg2 + 1));
  sub_4740D0(this + 5, (int)(pszArg2 + 5));
  return this;
}



// ------------------------------------------------------------
// 0x474570 sub_474570
// ------------------------------------------------------------
// 16 字节/条目容器逐条正向析构辅助（元素经 sub_4ED3F0 清理）
int /*cdecl*/ sub_474570(int nArg1, int nArg2, int nArg3)
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 16 )
    result = sub_4ED3F0(i, nArg3);
  return result;
}



// ------------------------------------------------------------
// 0x4745A0 sub_4745A0
// ------------------------------------------------------------
// 16 字节/条目容器逐条反向搬运+析构辅助（uninitialized_copy 类）
int /*cdecl*/ sub_4745A0(int nArg1, int nArg2, int nArg3)
{
  int nArg22; // esi
  int nArg32; // edi

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    nArg22 -= 16;
    nArg32 -= 16;
    sub_4ED3F0(nArg32, nArg22);
  }
  while ( nArg22 != nArg1 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x4745E0 sub_4745E0
// ------------------------------------------------------------
// 36 字节聚合条目正向拷贝（9 dword/条）：首 dword 赋值 + 两个 vector
// 成员（sub_474170/sub_474300）
uint32_t */*cdecl*/ sub_4745E0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // esi
  uint32_t *uArg32; // edi

  uArg12 = uArg1;
  if ( uArg1 == uArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    *uArg32 = *uArg12;
    sub_474170((int)(uArg32 + 1), (int)(uArg12 + 1));
    sub_474300((int)(uArg32 + 5), uArg12 + 5);
    uArg12 += 9;
    uArg32 += 9;
  }
  while ( uArg12 != uArg2 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x474630 sub_474630
// ------------------------------------------------------------
// 36 字节聚合条目反向拷贝（9 dword/条）：与 sub_4745E0 同构（倒序）
uint32_t */*cdecl*/ sub_474630(int nArg1, int nArg2, uint32_t *uArg3)
{
  int nArg22; // esi
  uint32_t *uArg32; // edi
  int v5; // eax

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    v5 = *(uint32_t *)(nArg22 - 36);
    nArg22 -= 36;
    uArg32 -= 9;
    *uArg32 = v5;
    sub_474170((int)(uArg32 + 1), nArg22 + 4);
    sub_474300((int)(uArg32 + 5), (int *)(nArg22 + 20));
  }
  while ( nArg22 != nArg1 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x474680 sub_474680
// ------------------------------------------------------------
// 16 字节条目拷贝构造辅助：逐条 sub_435020 拷入目标（空源跳过）
uint32_t */*cdecl*/ sub_474680(char *pszArg1, char *pszArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg32 = uArg3;
  v6[4] = v6;
  v6[3] = uArg3;
  v7 = 0;
  while ( pszArg1 != pszArg2 )
  {
    LOBYTE(v7) = 1;
    if ( uArg32 != nullptr )
      sub_435020(uArg32, pszArg1);
    uArg32 += 4;
    LOBYTE(v7) = 0;
    pszArg1 += 16;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x474710 sub_474710
// ------------------------------------------------------------
// 构造+释放：清字段后释放两个 vector 缓冲（+8 与 +24 处三指针置空）
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
// 大型聚合对象拷贝赋值：首 dword + 8×16B 条目组（sub_4ED3F0）+ 尾部
// 多组 dword 平铺拷贝（+84..+264）
char */*thiscall*/ sub_474790(char *this, char *pszArg2)
{
  int v4; // eax
  int pThis_4; // ebx
  int pThis_70; // ebx
  int v8; // [esp+Ch] [ebp-4h]
  int v9; // [esp+18h] [ebp+8h]
  int i; // [esp+18h] [ebp+8h]

  *(uint32_t *)this = *(uint32_t *)pszArg2;
  v4 = pszArg2 - this;
  pThis_4 = (int)(this + 4);
  v8 = pszArg2 - this;
  v9 = 4;
  while ( 1 )
  {
    sub_4ED3F0(pThis_4, pThis_4 + v4);
    pThis_4 += 16;
    if ( --v9 == 0 )
      break;
    v4 = v8;
  }
  sub_4ED3F0((int)(this + 68), (int)(pszArg2 + 68));
  *((uint32_t *)this + 21) = *((uint32_t *)pszArg2 + 21);
  *((uint32_t *)this + 22) = *((uint32_t *)pszArg2 + 22);
  *((uint32_t *)this + 23) = *((uint32_t *)pszArg2 + 23);
  *((uint32_t *)this + 24) = *((uint32_t *)pszArg2 + 24);
  *((uint32_t *)this + 25) = *((uint32_t *)pszArg2 + 25);
  *((uint32_t *)this + 26) = *((uint32_t *)pszArg2 + 26);
  *((uint32_t *)this + 27) = *((uint32_t *)pszArg2 + 27);
  pThis_70 = (int)(this + 112);
  for ( i = 4; i != 0; --i )
  {
    sub_4ED3F0(pThis_70, pThis_70 + v8);
    pThis_70 += 16;
  }
  *((uint32_t *)this + 44) = *((uint32_t *)pszArg2 + 44);
  *((uint32_t *)this + 45) = *((uint32_t *)pszArg2 + 45);
  *((uint32_t *)this + 46) = *((uint32_t *)pszArg2 + 46);
  *((uint32_t *)this + 47) = *((uint32_t *)pszArg2 + 47);
  *((uint32_t *)this + 48) = *((uint32_t *)pszArg2 + 48);
  *((uint32_t *)this + 49) = *((uint32_t *)pszArg2 + 49);
  *((uint32_t *)this + 50) = *((uint32_t *)pszArg2 + 50);
  *((uint32_t *)this + 51) = *((uint32_t *)pszArg2 + 51);
  *((uint32_t *)this + 52) = *((uint32_t *)pszArg2 + 52);
  *((uint32_t *)this + 53) = *((uint32_t *)pszArg2 + 53);
  *((uint32_t *)this + 54) = *((uint32_t *)pszArg2 + 54);
  *((uint32_t *)this + 55) = *((uint32_t *)pszArg2 + 55);
  *((uint32_t *)this + 56) = *((uint32_t *)pszArg2 + 56);
  *((uint32_t *)this + 57) = *((uint32_t *)pszArg2 + 57);
  *((uint32_t *)this + 58) = *((uint32_t *)pszArg2 + 58);
  *((uint32_t *)this + 59) = *((uint32_t *)pszArg2 + 59);
  *((uint32_t *)this + 60) = *((uint32_t *)pszArg2 + 60);
  *((uint32_t *)this + 61) = *((uint32_t *)pszArg2 + 61);
  *((uint32_t *)this + 62) = *((uint32_t *)pszArg2 + 62);
  *((uint32_t *)this + 63) = *((uint32_t *)pszArg2 + 63);
  *((uint32_t *)this + 64) = *((uint32_t *)pszArg2 + 64);
  *((uint32_t *)this + 65) = *((uint32_t *)pszArg2 + 65);
  *((uint32_t *)this + 66) = *((uint32_t *)pszArg2 + 66);
  return this;
}



// ------------------------------------------------------------
// 0x474950 sub_474950
// ------------------------------------------------------------
// vector 尾插 1 条（8 字节/条目）：容量够则原地构造，不够走
// sub_473A80 扩容插入
void /*thiscall*/ sub_474950(int this, int nArg2)
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
    sub_473A80(this, *(char **)(this + 8), 1u, nArg2);
  }
}



// ------------------------------------------------------------
// 0x4749C0 sub_4749C0
// ------------------------------------------------------------
// 转发 sub_4745A0（16 字节条目反向搬运辅助）
int /*cdecl*/ sub_4749C0(int nArg1, int nArg2, int nArg3)
{
  return sub_4745A0(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x4749E0 sub_4749E0
// ------------------------------------------------------------
// 36 字节聚合条目按样例填充（fill 辅助）：单值 + 两 vector 成员拷贝
uint32_t */*cdecl*/ sub_4749E0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 9 )
  {
    *i = *pArg3;
    sub_474170((int)(i + 1), (int)(pArg3 + 1));
    sub_474300((int)(i + 5), pArg3 + 5);
    result = uArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x474A20 sub_474A20
// ------------------------------------------------------------
// 转发 sub_474630（36 字节聚合条目反向拷贝）
uint32_t */*cdecl*/ sub_474A20(int nArg1, int nArg2, uint32_t *uArg3)
{
  return sub_474630(nArg1, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x474A40 sub_474A40
// ------------------------------------------------------------
// 16 字节条目按值填充 n 次（construct_n 辅助，元素经 sub_435020 拷入）
uint32_t */*cdecl*/ sub_474A40(uint32_t *uArg1, int nArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // esi
  uint32_t *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg12 = uArg1;
  v6[4] = v6;
  v6[3] = uArg1;
  v7 = 0;
  while ( nArg2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( uArg12 != nullptr )
      result = sub_435020(uArg12, uArg3);
    --nArg2;
    uArg12 += 4;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x474AD0 sub_474AD0
// ------------------------------------------------------------
// 36 字节聚合条目区间拷贝（uninitialized_copy：dword + 两 vector 成员）
int /*cdecl*/ sub_474AD0(uint32_t *pArg1, uint32_t *uArg2, int nArg3)
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( pArg1 != uArg2 )
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
    {
      *(uint32_t *)nArg32 = *pArg1;
      sub_474030((char **)(nArg32 + 4), (int)(pArg1 + 1));
      LOBYTE(v7) = 2;
      sub_4740D0((uint32_t *)(nArg32 + 20), (int)(pArg1 + 5));
    }
    nArg32 += 36;
    LOBYTE(v7) = 0;
    pArg1 += 9;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x474C30 sub_474C30
// ------------------------------------------------------------
// 构造：初始化一棵 map 头节点（sub_433AC0 分配，+21 nil 旗标，自环清计数）
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
// 36 字节条目 vector 析构：逐条 sub_472F00 清缓冲后整块 free 并置空
int /*thiscall*/ sub_474C60(int *this)
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);
  result = 0;
  if ( fld_e1 != 0 )
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 36 )
      sub_472F00(fld_e1);
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
// 转发 sub_474680（16 字节条目拷贝构造辅助）
uint32_t */*thiscall*/ sub_474CA0(void *this, char *pszArg2, char *pszArg3, uint32_t *uArg4)
{
  return sub_474680(pszArg2, pszArg3, uArg4);
}



// ------------------------------------------------------------
// 0x474CC0 sub_474CC0
// ------------------------------------------------------------
// 36 字节聚合条目按值填充 n 次（与 sub_474A40 同族，正向）
void /*cdecl*/ sub_474CC0(int nArg1, int nArg2, uint32_t *pArg3)
{
  int nArg12; // esi
  uint32_t v4[6]; // [esp+0h] [ebp-24h] BYREF
  int v5; // [esp+20h] [ebp-4h]

  nArg12 = nArg1;
  v4[5] = v4;
  v4[4] = nArg1;
  v5 = 0;
  while ( nArg2 != 0 )
  {
    v4[3] = nArg12;
    LOBYTE(v5) = 1;
    if ( nArg12 != 0 )
    {
      *(uint32_t *)nArg12 = *pArg3;
      sub_474030((char **)(nArg12 + 4), (int)(pArg3 + 1));
      LOBYTE(v5) = 2;
      sub_4740D0((uint32_t *)(nArg12 + 20), (int)(pArg3 + 5));
    }
    nArg12 += 36;
    LOBYTE(v5) = 0;
    --nArg2;
  }
}



// ------------------------------------------------------------
// 0x474DB0 sub_474DB0
// ------------------------------------------------------------
// 16 字节条目填充 n 条并返回尾指针（转发 sub_474A40）
uint32_t */*thiscall*/ sub_474DB0(void *this, uint32_t *pArg2, int nArg3, uint32_t *uArg4)
{
  sub_474A40(pArg2, nArg3, uArg4);
  return &pArg2[4 * nArg3];
}



// ------------------------------------------------------------
// 0x474DE0 sub_474DE0
// ------------------------------------------------------------
// vector 定点插入（16 字节/条目，>>4 计数）：原地腾洞或 1.5 倍扩容重建；
// 0xFFFFFFF=最大条目数（×16 溢出界）；旧缓冲经 sub_42CC00+free 释放
void /*thiscall*/ sub_474DE0(int this, char *pszArg2, unsigned int uArg3, void *pArg4)
{
  int fld_4; // edx
  int fld_8; // ecx
  unsigned int fld_C; // eax
  int fld_82; // ecx
  unsigned int v10; // eax
  int fld_87; // ecx
  int fld_88; // eax
  void *pMem; // ebx
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v16; // edi
  char *fld_83; // eax
  int fld_86; // edi
  char *v19; // edi
  int v20; // eax
  void *fld_42; // [esp-18h] [ebp-4Ch]
  void *Block2; // [esp-18h] [ebp-4Ch]
  void *fld_85; // [esp-Ch] [ebp-40h]
  int fld_84; // [esp-8h] [ebp-3Ch]
  int v25; // [esp+0h] [ebp-34h] BYREF
  char v26[4]; // [esp+Ch] [ebp-28h] BYREF
  void *v27; // [esp+10h] [ebp-24h]
  void *Block; // [esp+1Ch] [ebp-18h]
  int pThis; // [esp+20h] [ebp-14h]
  int *v30; // [esp+24h] [ebp-10h]
  int v31; // [esp+30h] [ebp-4h]
  char *v32; // [esp+40h] [ebp+Ch]
  char *v33; // [esp+44h] [ebp+10h]

  v30 = &v25;
  pThis = this;
  sub_435020(pArg4);
  fld_4 = *(uint32_t *)(this + 4);
  fld_8 = 0;
  v31 = 0;
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 4;
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
    if ( 0xFFFFFFF - fld_8 < uArg3 )
      sub_42CB90(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(char **)(this + 8);
      Block = fld_83;
      if ( (fld_83 - pszArg2) >> 4 >= uArg3 )
      {
        v19 = &fld_83[-16 * uArg3];
        v20 = sub_474680(v19, (int)fld_83, fld_83, this);
        Block2 = Block;
        *(uint32_t *)(this + 8) = v20;
        sub_4749C0(pszArg2, v19, Block2);
        sub_474570(pszArg2, &pszArg2[16 * uArg3], v26);
      }
      else
      {
        sub_474680(pszArg2, (int)fld_83, &pszArg2[16 * uArg3], this);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - (int)pszArg2) >> 4);
        fld_85 = *(void **)(this + 8);
        LOBYTE(v31) = 3;
        sub_474DB0(this, fld_85, fld_84, v26);
        fld_86 = 16 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        v31 = 0;
        sub_474570(pszArg2, fld_86 - 16 * uArg3, v26);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (fld_C >> 1) >= fld_C )
        v10 = (fld_C >> 1) + fld_C;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
      else
        fld_87 = 0;
      if ( v10 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
        else
          fld_88 = 0;
        v10 = uArg3 + fld_88;
      }
      v33 = (char *)(16 * v10);
      pMem = operator new(16 * v10);
      fld_42 = *(void **)(this + 4);
      Block = pMem;
      LOBYTE(v31) = 1;
      v32 = (char *)sub_474680(fld_42, (int)pszArg2, pMem, this);
      sub_474A40(v32, uArg3, v26, this);
      sub_474680(pszArg2, *(uint32_t *)(this + 8), &v32[16 * uArg3], this);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 4;
      else
        fld_89 = 0;
      v16 = fld_89 + uArg3;
      if ( fld_43 != 0 )
      {
        sub_42CC00(fld_43, *(uint32_t *)(this + 8));
        j__free(*(void **)(this + 4));
      }
      *(uint32_t *)(this + 12) = &v33[(uint32_t)pMem];
      *(uint32_t *)(this + 8) = (char *)pMem + 16 * v16;
      *(uint32_t *)(this + 4) = pMem;
    }
  }
  if ( v27 != nullptr )
    j__free(v27);
}


// ------------------------------------------------------------
// 0x475080 sub_475080
// ------------------------------------------------------------
// 36 字节条目区间析构辅助（逐条 sub_472F00 清缓冲）
void /*stdcall*/ sub_475080(int nArg1, int nArg2)
{
  int i; // esi

  for ( i = nArg1; i != nArg2; i += 36 )
    sub_472F00(i);
}



// ------------------------------------------------------------
// 0x4750B0 sub_4750B0
// ------------------------------------------------------------
// 成员析构：释放 +44/+28 两个 vector 缓冲，再 sub_474C60 清 36B 条目表
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
// 36 字节条目 erase 返回辅助：先把 [uArg3,uArg4) 前移覆盖，再析构尾部残余
uint32_t */*thiscall*/ sub_475100(uint32_t **this, uint32_t *uArg2, uint32_t *uArg3, uint32_t *uArg4)
{
  uint32_t *uArg32; // ecx
  uint32_t *fld_e2; // eax
  int fld_e22; // ebx
  uint32_t *fld_e23; // edi
  int i; // esi
  uint32_t **pThis; // [esp+4h] [ebp-4h]

  uArg32 = uArg3;
  pThis = this;
  if ( uArg3 != uArg4 )
  {
    fld_e2 = sub_4745E0(uArg4, *(this + 2), uArg3);
    fld_e22 = (int)*(this + 2);
    fld_e23 = fld_e2;
    for ( i = (int)fld_e2; i != fld_e22; i += 36 )
      sub_472F00(i);
    uArg32 = uArg3;
    pThis[2] = fld_e23;
  }
  *uArg2 = uArg32;
  return uArg2;
}



// ------------------------------------------------------------
// 0x475160 sub_475160
// ------------------------------------------------------------
// 36 字节条目填充 n 条并返回尾指针（转发 sub_474CC0）
int /*stdcall*/ sub_475160(int nArg1, int nArg2, uint32_t *uArg3)
{
  sub_474CC0(nArg1, nArg2, uArg3);
  return nArg1 + 36 * nArg2;
}



// ------------------------------------------------------------
// 0x475190 sub_475190
// ------------------------------------------------------------
// vector 尾插 1 条（16 字节/条目）：容量够原地构造，不够走 sub_474DE0
void /*thiscall*/ sub_475190(int this, uint32_t *uArg2)
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
  else
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 4 )
  {
    fld_82 = *(uint32_t **)(this + 8);
    sub_474A40(fld_82, 1, uArg2);
    *(uint32_t *)(this + 8) = fld_82 + 4;
  }
  else
  {
    sub_474DE0(this, *(char **)(this + 8), 1u, uArg2);
  }
}



// ------------------------------------------------------------
// 0x475200 sub_475200
// ------------------------------------------------------------
// vector 定点插入（36 字节聚合条目，/36 计数）：原地腾洞或 1.5 倍扩容
// 重建；119304647=最大条目数（×36 溢出界）；插入条目为 nArg4 的拷贝
void /*thiscall*/ sub_475200(int *this, int pArg2, unsigned int uArg3, int nArg4)
{
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v14; // edi
  int fld_e14; // eax
  int fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-60h]
  int fld_e25; // [esp-Ch] [ebp-54h]
  unsigned int fld_e24; // [esp-8h] [ebp-50h]
  int v22; // [esp+0h] [ebp-48h] BYREF
  uint8_t v23[8]; // [esp+Ch] [ebp-3Ch] BYREF
  void *v24; // [esp+14h] [ebp-34h]
  void *v25; // [esp+24h] [ebp-24h]
  int v26; // [esp+28h] [ebp-20h]
  int v27; // [esp+2Ch] [ebp-1Ch]
  void *Block; // [esp+30h] [ebp-18h]
  int *pThis; // [esp+34h] [ebp-14h]
  int *v30; // [esp+38h] [ebp-10h]
  int v31; // [esp+44h] [ebp-4h]
  int v32; // [esp+50h] [ebp+8h]
  int v33; // [esp+54h] [ebp+Ch]
  int v34; // [esp+58h] [ebp+10h]
  int fld_e232; // [esp+58h] [ebp+10h]

  v30 = &v22;
  pThis = this;
  sub_474510(nArg4);
  fld_e1 = *(this + 1);
  fld_e3 = 0;
  v31 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 36;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 36;
    else
      fld_e2 = 0;
    if ( 119304647 - fld_e2 < uArg3 )
      sub_4735F0(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 36;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = *(this + 2);
      fld_e232 = fld_e23;
      if ( (fld_e23 - pArg2) / 36 >= uArg3 )
      {
        v32 = fld_e23 - 36 * uArg3;
        *(this + 2) = sub_474AD0(v32, fld_e23, fld_e23);
        sub_474A20(pArg2, v32, fld_e232);
        sub_4749E0(pArg2, pArg2 + 36 * uArg3, v23);
      }
      else
      {
        sub_474AD0(pArg2, fld_e23, pArg2 + 36 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 36;
        fld_e25 = *(this + 2);
        LOBYTE(v31) = 3;
        sub_475160(fld_e25, fld_e24, v23);
        fld_e26 = 36 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v31 = 0;
        sub_4749E0(pArg2, fld_e26 - 36 * uArg3, v23);
      }
    }
    else
    {
      if ( 119304647 - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 36;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_504390(this);
      v34 = 36 * v10;
      pMem = (char *)operator new(36 * v10);
      fld_e12 = *(this + 1);
      Block = pMem;
      LOBYTE(v31) = 1;
      v33 = sub_474AD0(fld_e12, pArg2, pMem);
      sub_474CC0(v33, uArg3, v23);
      sub_474AD0(pArg2, *(this + 2), v33 + 36 * uArg3);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 36;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);
      if ( fld_e14 != 0 )
      {
        sub_475080(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v34];
      *(this + 2) = (int)&pMem[36 * v14];
      *(this + 1) = (int)pMem;
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
// 36 字节条目 vector resize：缩小收 end（sub_475100），放大补样例条目
// （sub_475200）；随后释放两个临时对象 Block/a5
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
// 按关卡尺寸（+168 处 w*h）扩容三张全局表（dword_99FBB0 36B 条目、
// dword_99FBC0 int 表、dword_99FBD0 对象指针表 0xA0/个）
uint32_t */*thiscall*/ sub_4755F0(uint32_t *this, int Block)
{
  signed int fld_e42; // edi
  int dword_99FBB42; // eax
  int v4; // esi
  signed int v5; // eax
  uint32_t *result; // eax
  int v7; // esi
  uint32_t *pMem; // eax
  uint32_t v9[11]; // [esp-24h] [ebp-38h] BYREF
  int v10; // [esp+10h] [ebp-4h]

  dword_99FB78 = Block;
  fld_e42 = *(uint32_t *)(8 * Block + *(this + 42)) * *(uint32_t *)(8 * Block + *(this + 42) + 4);
  dword_99FBB42 = dword_99FBB4;
  if ( dword_99FBB4 != 0 )
    dword_99FBB42 = (dword_99FBB8 - dword_99FBB4) / 36;
  if ( dword_99FBB42 < fld_e42 )
  {
    sub_474710(v9);
    sub_475510(
      (int)&unk_99FBB0,
      fld_e42,
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
  if ( v4 < fld_e42 )
  {
    sub_474480(&dword_99FBC0, fld_e42, 0);
    v5 = v4;
    do
      *(uint32_t *)(dword_99FBC4 + 4 * v5++) = 0;
    while ( v5 < fld_e42 );
  }
  result = (uint32_t *)dword_99FBD4;
  if ( dword_99FBD4 != 0 )
    v7 = (dword_99FBD8 - dword_99FBD4) >> 2;
  else
    v7 = 0;
  if ( v7 < fld_e42 )
  {
    sub_474480(&dword_99FBD0, fld_e42, 0);
    do
    {
      pMem = operator new(0xA0u);
      v10 = 0;
      if ( pMem != nullptr )
        result = sub_42D590(pMem, 0);
      else
        result = nullptr;
      *(uint32_t *)(dword_99FBD4 + 4 * v7++) = result;
      v10 = -1;
    }
    while ( v7 < fld_e42 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x475730 sub_475730
// ------------------------------------------------------------
// 56 字节条目区间析构辅助（逐条 sub_4750B0）
int /*stdcall*/ sub_475730(int nArg1, int nArg2)
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 56 )
    result = sub_4750B0(i);
  return result;
}



// ------------------------------------------------------------
// 0x475760 sub_475760
// ------------------------------------------------------------
// 清理全局三表（0x4755F0 建的 dword_99FBB0/99FBC0/99FBD0）：逐条释放
// 缓冲/对象后清空
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
void /*userpurge*/ sub_475810(int *pDwArg1@<ecx>, int nArg2@<esi>, int pArg3, int nArg4)
{
  int *pDwArg12; // ebx
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
  int nArg42; // ecx
  void *v19; // eax
  int pObj4; // ebx
  int *pDwArg1222; // edx
  int v22; // eax
  int v23; // ecx
  int j; // edi
  uint32_t *v25; // ebx
  uint8_t *pObj; // esi
  uint32_t *v27; // eax
  int v28; // eax
  int v29; // ebx
  int v30; // eax
  int v31; // eax
  uint32_t **v32; // eax
  uint32_t *v33; // edi
  bool v34; // zf
  void *v35; // eax
  int pObj2; // ebx
  int v37; // eax
  int v38; // esi
  int v39; // eax
  int v40; // eax
  int v41; // esi
  int v42; // ecx
  uint32_t *v43; // esi
  void *v44; // eax
  int pObj3; // edi
  int v46; // edx
  int v47; // eax
  int v48; // esi
  int v49; // [esp-10h] [ebp-5Ch]
  int v50; // [esp-8h] [ebp-54h]
  unsigned int Seed; // [esp+18h] [ebp-34h]
  unsigned int Seeda; // [esp+18h] [ebp-34h]
  int *v54; // [esp+1Ch] [ebp-30h]
  int pArg32; // [esp+20h] [ebp-2Ch] BYREF
  int v56; // [esp+24h] [ebp-28h]
  int v57; // [esp+28h] [ebp-24h]
  int v58; // [esp+2Ch] [ebp-20h]
  int v59; // [esp+30h] [ebp-1Ch]
  int v60; // [esp+34h] [ebp-18h]
  int *pDwArg122; // [esp+38h] [ebp-14h]
  int v62; // [esp+3Ch] [ebp-10h] BYREF
  int v63; // [esp+48h] [ebp-4h]
  uint32_t *v64; // [esp+54h] [ebp+8h]
  int v65; // [esp+54h] [ebp+8h]
  int v66; // [esp+58h] [ebp+Ch]
  uint32_t *v67; // [esp+58h] [ebp+Ch]

  pDwArg12 = pDwArg1;
  v5 = pArg3 + nArg4 * *(uint32_t *)(pDwArg1[42] + 8 * dword_99FB78);
  v6 = *(uint32_t *)(dword_99FBC4 + 4 * v5);
  v7 = 4 * v5;
  pDwArg122 = pDwArg12;
  Seed = 4 * v5;
  if ( v6 == 0 )
  {
    v8 = *pDwArg12;
    if ( *pDwArg12 < 15 || (dword_79D0C4 = 85, v8 > 16) )
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
              *(uint32_t *)(*(uint32_t *)(pDwArg12[46] + 16 * dword_99FB78 + 4)
                        + 4 * (pArg3 + nArg4 * *(uint32_t *)(pDwArg12[42] + 8 * dword_99FB78))));
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
          + *(uint32_t *)(*(uint32_t *)(pDwArg12[46] + 16 * dword_99FB78 + 4)
                      + 4 * (pArg3 + nArg4 * *(uint32_t *)(pDwArg12[42] + 8 * dword_99FB78)))
          + pDwArg12[123]
          + *(uint32_t *)v60;
    off_77F3FC((char *)&byte_6C8724, Seeda, pDwArg12[123]);
    sub_4602C0(v12);
    v62 = v12[14];
    for ( i = 0; i < 4; ++i )
    {
      v57 = 2;
      pDwArg12[i + 119] = 0;
      if ( (uint8_t)sub_48C220(i) != 0 )
      {
        nArg42 = nArg4;
        v57 = 0;
        if ( dword_99FB7C == pArg3 && dword_99FB80 == nArg4 )
          goto LABEL_27;
        pArg32 = pArg3;
        switch ( i )
        {
          case 0:
            pArg32 = pArg3 - 1;
            break;
          case 1:
            pArg32 = pArg3 + 1;
            break;
          case 2:
            nArg42 = nArg4 - 1;
            break;
          case 3:
            nArg42 = nArg4 + 1;
            break;
          default:
            break;
        }
        if ( dword_99FB7C == pArg32 && dword_99FB80 == nArg42 )
LABEL_27:
          v57 = 1;
      }
      v19 = (void *)pDwArg12[2 * i + 29 + i + v57];
      if ( v19 != (void *)-1 )
      {
        pObj4 = sub_53A220(v19, nullptr);  // 【巨函数（size=17574）→ src/combat/bigfunc_53A220…】
        sub_45FE80(33, v62, pObj4, 0, 0);
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj4 + 112))(pObj4, v12[2 * i + 54], v12[2 * i + 55], 0);
        if ( __RTDynamicCast(pObj4, 0, &CNRDPassiveObject `RTTI Type Descriptor', &CNPathGate `RTTI Type Descriptor', 0) != 0 )
          sub_577A30(v58, i);
        pDwArg1222 = pDwArg122;
        v22 = v62 + 1;
        pDwArg122[i + 119] = pObj4;
        v62 = v22;
        pDwArg12 = pDwArg1222;
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
        pObj = (uint8_t *)sub_4ABE10(*(void **)(j + 8), *(void **)(j + 12), 0);
        if ( v56 > 1 )
        {
          v27 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 1040))(pObj);
          *v27 += 50 * v56 - 50;
          v28 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 1040))(pObj);
          *(uint32_t *)(v28 + 72) += 7 * v56 - 7;
        }
        if ( (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pObj + 436))(pObj, nArg2) <= 0 )
          v66 = v25[5];
        else
          v66 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 436))(pObj);
        nArg2 = 100;
        (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 372))(pObj);
        (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 112))(pObj, v25[3], v25[4], v66);
        pObj[7801] = 1;
        sub_45FE80(529, *(uint32_t *)(j + 4), pObj, 0, 0);
        v29 = *(uint32_t *)pObj;
        v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 144))(dword_8F8520);
        (*(void (/*thiscall*/ **)(uint8_t *, int))(v29 + 1044))(pObj, v30);
        v31 = *(uint32_t *)(j + 16);
        if ( v31 == 1 || v31 == 2 )
        {
          (*(void (/*thiscall*/ **)(uint8_t *, unsigned int, uint32_t *, uint32_t))(*(uint32_t *)pObj + 1160))(
            pObj,
            Seeda + *(uint32_t *)(j + 8),
            v64 + 10,
            *(uint32_t *)(j + 16));
          ++dword_9A05D0;
        }
        else if ( v31 == 3 )
        {
          (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 1120))(pObj);
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
          pObj2 = sub_53A220(v35, nullptr);  // 【巨函数（size=17574）→ src/combat/bigfunc_53A220…】
          v34 = (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 1057, nArg2) == 0;
          v37 = *(uint32_t *)pObj2;
          if ( v34 )
          {
            nArg2 = 1;
            (*(void (/*thiscall*/ **)(int))v37)(pObj2);
          }
          else
          {
            nArg2 = v33[10];
            (*(void (/*thiscall*/ **)(int, uint32_t))(v37 + 724))(pObj2, v33[9]);
            v38 = v62;
            sub_45FE80(33, v62, pObj2, 0, 0);
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj2 + 112))(pObj2, v33[5], v33[6], v33[7]);
            v62 = v38 + 1;
            pArg32 = pObj2;
            sub_45F8A0(nullptr, 1, (int)&pArg32);
            v39 = 0;
            pArg32 = 0;
            while ( 1 )
            {
              v56 = v39;
              v40 = *(uint32_t *)(v60 + 24);
              if ( v40 == 0 || pArg32 >= (unsigned int)((*(uint32_t *)(v60 + 28) - v40) / 20) )
                break;
              v41 = *(uint32_t *)(v60 + 24);
              v42 = *(uint32_t *)(v41 + v56);
              v43 = (uint32_t *)(v56 + v41);
              if ( v42 == v65 )
              {
                v44 = (void *)v43[2];
                if ( v44 != (void *)0xFFFF )
                {
                  pObj3 = sub_522300(v44, v43[3], 0, 0, v43[4], 1);
                  if ( pObj3 != 0 )
                  {
                    v46 = *(uint32_t *)pObj2;
                    v57 = v43[1];
                    (*(void (/*thiscall*/ **)(int, int, int))(v46 + 720))(pObj2, v57, pObj3);
                    v47 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 16))(pObj3);
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
              ++pArg32;
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
// 56 字节条目 vector 析构：逐条 sub_4750B0 清理后整块 free 并置空
int /*thiscall*/ sub_475EB0(int *this)
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);
  result = 0;
  if ( fld_e1 != 0 )
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 56 )
      sub_4750B0(fld_e1);
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
// 全局场景对象表清理：dword_99FB9C map 逐节点释放（值对象+内层树）、
// 两张全局表（dword_99FBC0/99FBD0）逐项释放
int sub_475EF0()
{
  int dword_99FB9C2; // ebx
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

  dword_99FB9C2 = dword_99FB9C;
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
        dword_99FB9C2 = dword_99FB9C;
      }
      sub_41C5E0(&v10);
      v1 = v10;
    }
    while ( v10 != dword_99FB9C2 );
  }
  v3 = *(void ****)(dword_99FB9C2 + 4);
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
    dword_99FB9C2 = dword_99FB9C;
  }
  *(uint32_t *)(dword_99FB9C2 + 4) = dword_99FB9C2;
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
// 副本描述对象清理/复位：清 5 个 std::string 成员、56B 条目表
// （+304）、3 个字符串槽（+404）、再 sub_42C250 复位 +416 子对象
int /*thiscall*/ sub_476000(char *this)
{
  int pThis_4C; // edi
  void **pThis_194; // edi
  int result; // eax
  void *Block; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]
  int j; // [esp+10h] [ebp-4h]

  *(uint32_t *)this = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 29) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 39) = 0;
  *((uint32_t *)this + 40) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
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
  pThis_4C = *((uint32_t *)this + 76);
  if ( pThis_4C != 0 )
  {
    for ( i = *((uint32_t *)this + 77); pThis_4C != i; pThis_4C += 56 )
      sub_4750B0(pThis_4C);
    j__free(*((void **)this + 76));
  }
  *((uint32_t *)this + 76) = 0;
  *((uint32_t *)this + 77) = 0;
  *((uint32_t *)this + 78) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_194 = (void **)(this + 404);
  for ( j = 3; j != 0; --j )
  {
    Block = *pThis_194;
    if ( *pThis_194 != nullptr )
    {
      sub_472F40();
      j__free(Block);
    }
    *pThis_194++ = nullptr;
  }
  result = sub_42C250(this + 416);
  *(this + 684) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4761F0 sub_4761F0
// ------------------------------------------------------------
// 副本描述对象构造：7 个 std::string 成员置空（SSO cap=15）、字段
// 默认值（+196=0xFFFF 等）、+344 子对象 sub_472FF0 初始化
int /*thiscall*/ sub_4761F0(int this)
{
  int pThis_158; // edi

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
  pThis_158 = this + 344;
  sub_472FF0((uint32_t *)(this + 344));
  sub_42D620(this + 416);
  *(uint32_t *)(this + 400) = 0;
  *(uint32_t *)(this + 404) = 0;
  *(uint32_t *)(this + 408) = 0;
  *(uint32_t *)(this + 412) = 0;
  *(uint32_t *)(this + 400) = pThis_158;
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
// 副本描述对象全清：3 个字符串槽（+404）、+416 子对象、3 个 std::string
// （+348/+368、+320/+340、+376/+396）、56B 条目表（+304）与各 string 成员
void /*thiscall*/ sub_476300(int this)
{
  uint32_t *pThis_194; // eax
  int v3; // edi
  int fld_130; // eax
  int v5; // edi
  char *v6; // ecx
  int fld_134; // [esp+Ch] [ebp-1Ch]
  char *v8; // [esp+10h] [ebp-18h]
  int i; // [esp+14h] [ebp-14h]
  int fld_1302; // [esp+14h] [ebp-14h]
  uint32_t *pThis_1942; // [esp+18h] [ebp-10h]
  char *v12; // [esp+18h] [ebp-10h]

  pThis_194 = (uint32_t *)(this + 404);
  pThis_1942 = (uint32_t *)(this + 404);
  for ( i = 3; i != 0; --i )
  {
    v3 = *pThis_194;
    if ( *pThis_194 != 0 )
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
      pThis_194 = pThis_1942;
    }
    *pThis_194++ = 0;
    pThis_1942 = pThis_194;
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
  fld_130 = *(uint32_t *)(this + 304);
  if ( fld_130 != 0 )
  {
    fld_134 = *(uint32_t *)(this + 308);
    fld_1302 = *(uint32_t *)(this + 304);
    if ( fld_130 != fld_134 )
    {
      v5 = fld_130 + 44;
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
        fld_1302 += 56;
      }
      while ( fld_1302 != fld_134 );
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
  size_t *pThis; // ebx
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
  size_t *pThis2; // [esp+10h] [ebp-2D8h]
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
  int dword_796E502; // [esp+2D8h] [ebp-10h]
  int v66; // [esp+2E4h] [ebp-4h]
  int ArgLista; // [esp+2F0h] [ebp+8h]
  unsigned int ArgListb; // [esp+2F0h] [ebp+8h]

  pThis = this;
  dword_796E502 = dword_796E50;
  pThis2 = this;
  sub_4761F0(&v43);
  v66 = 0;
  if ( (uint8_t)sub_4F1A20((int)&v43, (char)ArgList) != 0 )
  {
    *pThis = v43;
    sub_4014D0(pThis + 1, v44, 0, 0xFFFFFFFF);
    sub_4014D0(pThis + 8, v45, 0, 0xFFFFFFFF);
    v4 = v60[7];
    pThis[23] = v60[6];
    v5 = v60[8];
    pThis[24] = v4;
    v6 = v60[9];
    pThis[25] = v5;
    v7 = v60[10];
    pThis[26] = v6;
    v8 = v60[11];
    v34 = v50;
    pThis[27] = v7;
    pThis[28] = v8;
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
      pThis[15] = v11;
      sub_699070(0);  // 【clock_bind_domain(clk, newDomainId)】
    }
    if ( sub_40BF00((std::_String_base *)v52, 0, v53[4], szPassword, 0) != 0 )
    {
      v12 = (unsigned int *)v53[0];
      if ( v53[5] < 0x10 )
        v12 = v53;
      v35 = v53[6];
      v13 = (uint32_t *)(*(int (/*thiscall*/ **)(int, unsigned int *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v12);
      pThis[16] = sub_418DD0(v13, v35);
    }
    if ( sub_40BF00((std::_String_base *)v54, 0, v58[0], szPassword, 0) != 0 )
    {
      v14 = v55;
      if ( v58[1] < 0x10 )
        v14 = &v55;
      pThis[17] = (*(int (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v14);
    }
    v15 = pThis + 19;
    for ( i = 2; i != 0; --i )
    {
      *(v15 - 1) = *(uint32_t *)((char *)v15 + v48 - (uint8_t *)pThis);
      *v15 = *(uint32_t *)((char *)v15 + v49 - (uint8_t *)pThis);
      v15 += 2;
    }
    if ( sub_40BF00((std::_String_base *)v59, 0, v60[4], szPassword, 0) != 0 )
    {
      v17 = (unsigned int *)v60[0];
      if ( v60[5] < 0x10 )
        v17 = v60;
      pThis[22] = (*(int (/*thiscall*/ **)(int, unsigned int *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v17);
    }
    v18 = pThis + 30;
    for ( ArgLista = 4; ArgLista != 0; --ArgLista )
    {
      *(v18 - 1) = *(uint32_t *)((char *)v18 + v56 - (uint8_t *)pThis);
      *v18 = *(uint32_t *)((char *)v18 + v57 - (uint8_t *)pThis);
      v18[1] = *(uint32_t *)((char *)v18 + (char *)v58 - (char *)pThis);
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
      v22 = pThis[42];
      v23 = pThis + 41;
      v36[0] = *(uint32_t *)(v42 + v61);
      v36[1] = v20;
      if ( v22 != 0 )
        v24 = (int)(pThis[43] - v22) >> 3;
      else
        v24 = 0;
      if ( v22 != 0 && v24 < (int)(pThis[44] - v22) >> 3 )
      {
        v25 = pThis[43];
        sub_63A7C0(v25, 1, v36);
        v23[2] = v25 + 8;
      }
      else
      {
        sub_473A80(pThis[43], 1, v36);
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
      v30 = pThis2[46];
      v31 = pThis2 + 45;
      if ( v30 != 0 )
        v32 = (int)(pThis2[47] - v30) >> 4;
      else
        v32 = 0;
      if ( v30 != 0 && v32 < (int)(pThis2[48] - v30) >> 4 )
      {
        v33 = (char *)pThis2[47];
        sub_474A40(v33, 1, v38, (int)(pThis2 + 45));
        v31[2] = (size_t)(v33 + 16);
      }
      else
      {
        sub_474DE0((int)(pThis2 + 45), (void *)pThis2[47], 1, v38);
      }
      LOBYTE(v66) = 0;
      if ( v27 != nullptr )
        j__free(v27);
      pThis = pThis2;
      v39 = nullptr;
      v40 = nullptr;
      v41 = 0;
      v19 = v42 + 56;
    }
    sub_474790(v64);
    *((uint8_t *)pThis + 464) = v64[268];
    *(uint32_t *)dword_99FB70 = 0;
    pThis[123] = -1;
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
void */*cdecl*/ sub_476B60(int nArg1)
{
  void *pMem; // eax
  int nArg12; // edi
  void *v4; // esi
  uint8_t v5[8]; // [esp+0h] [ebp-1Ch] BYREF
  int nArg122; // [esp+8h] [ebp-14h] BYREF
  void *Block; // [esp+Ch] [ebp-10h] BYREF
  int v8; // [esp+18h] [ebp-4h]

  sub_472E30(&dword_99FB98, (int **)&Block, &nArg1);
  if ( Block != (void *)dword_99FB9C )
    return *((void **)Block + 4);
  pMem = operator new(0x1F0u);
  Block = pMem;
  nArg12 = nArg1;
  v4 = nullptr;
  v8 = 0;
  if ( pMem != nullptr )
    v4 = sub_42E8F0(pMem, nArg1);
  v8 = -1;
  nArg122 = nArg12;
  Block = v4;
  sub_473920(&dword_99FB98, (int)v5, &nArg122);
  return v4;
}



// ------------------------------------------------------------
// 0x476C10 sub_476C10
// ------------------------------------------------------------
// 演出控制器字段复位：+48/+49、+19..+22、+1、+9..+18 全部清零
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
// 释放演出对象：+19/+20 两个对象与 +9 起 10 个对象逐个以参数 1 调虚函数
// （delete 语义）后置空
int /*thiscall*/ sub_476C50(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e19)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e20)(uint32_t, int); // ecx
  uint32_t *pThis_9; // esi
  int i; // edi

  fld_e19 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 19);
  if ( fld_e19 != nullptr )
    result = (**fld_e19)(fld_e19, 1);
  fld_e20 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 20);
  *(this + 19) = 0;
  if ( fld_e20 != nullptr )
    result = (**fld_e20)(fld_e20, 1);
  *(this + 20) = 0;
  pThis_9 = this + 9;
  for ( i = 10; i != 0; --i )
  {
    if ( *pThis_9 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_9)(*pThis_9, 1);
    *pThis_9++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x476CA0 sub_476CA0
// ------------------------------------------------------------
// 画血条外框/底（sprite 94@94,63 与 sprite 12@264,13）：nArg1=透明度
// （>=220 时外框按 -36 绘制）
int /*stdcall*/ sub_476CA0(int nArg1)
{
  uint8_t nArg12; // bl
  int pObj; // eax
  int result; // eax

  nArg12 = nArg1;
  if ( nArg1 >= 220 )
    nArg12 = -36;
  pObj = sub_418DD0(0);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(
      pObj,
      94,
      63,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (nArg12 << 24) | 0xFFFFFF,
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
             ((uint8_t)nArg1 << 24) | 0xFFFFFF,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x476D50 sub_476D50
// ------------------------------------------------------------
// 计时插值取值：目标时长 nArg2×fArg4（ms，下限 400，上限 ×1000），按
// +23 计时器与 +30+档位 起点差在 [nArg5,nArg2] 间 lerp（sub_4049C0）
int /*thiscall*/ sub_476D50(uint32_t *this, int nArg2, int pArg3, float fArg4, int nArg5)
{
  double v5; // st7
  double v6; // st7
  int v7; // esi
  int pThis_17; // eax
  int64_t v9; // rax
  float v11; // [esp+0h] [ebp-1Ch]
  float v12; // [esp+18h] [ebp-4h]
  float v13; // [esp+2Ch] [ebp+10h]

  v5 = (double)nArg2;
  v12 = v5;
  v6 = v5 * fArg4;
  v13 = fArg4 * 1000.0;
  if ( v6 >= v13 )
    v6 = v13;
  v7 = (uint64_t)v6;
  pThis_17 = sub_699000((int)(this + 23)) - *(this + pArg3 + 30);  // 【clock_now(clk)】
  if ( v7 < 400 )
    v7 = 400;
  if ( v7 <= pThis_17 )
  {
    LODWORD(v9) = nArg2;
  }
  else
  {
    v11 = (float)nArg5;
    return (uint64_t)sub_4049C0(v11, v12, pThis_17, v7);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  }
  return v9;
}



// ------------------------------------------------------------
// 0x476DD0 sub_476DD0
// ------------------------------------------------------------
// 按 +49 处字符分档返回 10..3（'#'→10 … 'i'→3），其余 11（特效档位表）
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
// 判定：+49 字符 >= 55（'7'）＝启用某演出项
bool /*thiscall*/ sub_476EC0(uint32_t *this)
{
  return sub_495C80(*(this + 49)) >= 55;
}



// ------------------------------------------------------------
// 0x476EE0 sub_476EE0
// ------------------------------------------------------------
// 预排 2 帧时刻表（+61 起 2 槽×3 dword）：第 v 槽起点 = 计时器+270+50×槽，
// 终点 = 起点+300（血条增长演出节拍）
int /*thiscall*/ sub_476EE0(uint32_t *this)
{
  int v1; // ebx
  uint32_t *pThis_3E; // esi
  int v3; // edi
  int result; // eax
  int v5; // [esp+Ch] [ebp-8h]
  int pThis_17; // [esp+10h] [ebp-4h]

  v1 = 0;
  pThis_17 = (int)(this + 23);
  v5 = 0;
  pThis_3E = this + 62;
  do
  {
    v3 = (uint64_t)((double)v5 + 270.0);
    *(pThis_3E - 1) = v3 + sub_699000(pThis_17);
    result = sub_699000(pThis_17);  // 【clock_now(clk)】
    v1 += 50;
    *pThis_3E = result + v3 + 300;
    pThis_3E += 3;
    v5 = v1;
  }
  while ( v1 < 100 );
  return result;
}



// ------------------------------------------------------------
// 0x476F50 sub_476F50
// ------------------------------------------------------------
// 2 槽演出绘制：+244/+248 起各 3 dword 为起止时刻，槽活动期间用
// sub_4049F0 做透明度/缩放插值并画 sprite 2（71,245）
int /*usercall*/ sub_476F50@<eax>(int pArg1@<ecx>, double fArg2@<st0>)
{
  uint32_t *v2; // eax
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // esi
  int pObj; // eax
  bool v8; // zf
  int result; // eax
  float fArg22; // [esp+Ch] [ebp-10h]
  int v11; // [esp+10h] [ebp-Ch]
  int pArg12; // [esp+14h] [ebp-8h]
  uint32_t *v13; // [esp+18h] [ebp-4h]

  v2 = (uint32_t *)(pArg1 + 248);
  pArg12 = pArg1;
  v13 = (uint32_t *)(pArg1 + 248);
  v11 = 2;
  while ( 1 )
  {
    v3 = *(v2 - 1);
    v4 = *v2 - v3;
    v5 = sub_699000(pArg1 + 92);  // 【clock_now(clk)】
    v6 = v5 - v3;
    if ( v5 - v3 > 0 && v6 < v4 )
    {
      if ( v6 >= 120 )
        sub_4049F0(255.0, 0.0, v5 - v3, v4, 1);
      else
        sub_4049F0(0.0, 255.0, v5 - v3, 120, 1);
      sub_4049F0(0.80000001, 1.3, v6, v4, 1);
      sub_491530(2, 0);
      pObj = sub_418DD0(2);
      if ( pObj != 0 )
      {
        fArg22 = fArg2;
        (*(void (/*thiscall*/ **)(int, int, int, int, uint32_t, uint32_t, uint32_t, int, int, int))(*(uint32_t *)pObj + 156))(
          pObj,
          71,
          245,
          dword_79C0B0,
          LODWORD(fArg22),
          LODWORD(fArg22),
          0,
          ((uint8_t)(uint64_t)fArg2 << 24) | 0xFFFFFF,
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
    pArg1 = pArg12;
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
    LODWORD(v2) = sub_699000((int)(this + 2)) - *(this + 76);  // 【clock_now(clk)】
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
// 结算状态复位：+120 起 0x44 字节、+244 起 0x3C 字节清零，各计数/旗标
// 复位（+312=255、+188=0xFFFF），+92 计时器清零
char /*thiscall*/ sub_477170(int this)
{
  uint32_t *pThis_C8; // edi
  char result; // al

  memset((void *)(this + 120), 0, 0x44u);
  pThis_C8 = (uint32_t *)(this + 200);
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
  *pThis_C8 = 0;
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
  result = sub_698F90(this + 92, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(uint32_t *)(this + 316) = 0;
  *(uint8_t *)(this + 320) = 0;
  *(uint8_t *)(this + 328) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x477240 sub_477240
// ------------------------------------------------------------
// 判定：+50 起 8 个 dword 是否有任一 >0（有加分项=1）
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
// 读 this+906 处 float 返回（进度/计数值访问器，与 sub_477260 同族）
double /*thiscall*/ sub_477280(void *this)
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this + 906));
}



// ------------------------------------------------------------
// 0x4772A0 sub_4772A0
// ------------------------------------------------------------
// 结算事件：M_RESULT 打开结算界面（6339 行附近）
char /*thiscall*/ sub_4772A0(int this, int nArg2)
{
  int fld_4; // eax
  int i; // esi

  *(uint32_t *)(this + 4) = nArg2;
  *(uint32_t *)(this + 4 * *(uint32_t *)(this + 4) + 120) = sub_699000(this + 92);
  *(uint8_t *)(this + 21) = 0;
  *(uint8_t *)(this + 22) = 0;
  sub_698F90(this + 8, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 >= 8 )
  {
    if ( fld_4 <= 15 )
    {
      if ( *(int *)(this + 4 * fld_4 + 168) <= 0 )
        LOBYTE(fld_4) = sub_4772A0(fld_4 + 1);
    }
    else if ( fld_4 == 16 )
    {
      LOBYTE(fld_4) = sub_432EE0(33311);
    }
  }
  if ( *(uint32_t *)(this + 4) != 0 )
  {
    if ( nArg2 == 1 )
    {
      *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = 0;
      for ( i = 0; i < 4; ++i )
        LOBYTE(fld_4) = sub_432EE0(i);
    }
    else if ( nArg2 == 16 )
    {
      sub_432EE0(33311);
      LOBYTE(fld_4) = sub_477240((int *)this);
      if ( (uint8_t)fld_4 != 0 )
        *(uint32_t *)(this + 304) = 500;
    }
    else
    {
      if ( *(uint8_t *)(*(uint32_t *)(this + 76) + 16) == 0 )
      {
        sub_65DC70(lpCriticalSection);
        LOBYTE(fld_4) = (uint8_t)sub_432EA0("M_RESULT", -1, 0, 0);
      }
      *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = 1;
    }
  }
  else
  {
    sub_477170(this);
    *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = 0;
    LOBYTE(fld_4) = sub_432EE0(33311);
  }
  return fld_4;
}



// ------------------------------------------------------------
// 0x4773B0 sub_4773B0
// ------------------------------------------------------------
// 结算步骤推进器：+4 当前步骤==1 且 +8 计时器 >=3000ms 时调
// sub_4772A0(this, 步骤+1) 进入下一步骤
char /*thiscall*/ sub_4773B0(int *this)
{
  int fld_e1; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && --fld_e1 == 0 )
  {
    fld_e1 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
    if ( fld_e1 >= 3000 )
      LOBYTE(fld_e1) = sub_4772A0((int)this, *(this + 1) + 1);
  }
  return fld_e1;
}



// ------------------------------------------------------------
// 0x4773E0 sub_4773E0
// ------------------------------------------------------------
// ★ 结算步骤逐条绘制（userpurge）：按 +4 步骤画名次/得分/掉落行
// （sub_418DD0 各 sprite，dword_6C8790 坐标表），计时到点推进
// sub_4772A0(步骤+1)（1 秒/步，+83 为步骤完成旗标）
uint32_t */*userpurge*/ sub_4773E0@<eax>(int *pDwArg1@<ecx>, double fArg2@<st0>, int nArg3)
{
  int nArg32; // edi
  uint8_t nArg33; // bl
  int pObj4; // eax
  int v7; // ebx
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  uint8_t nArg322; // bl
  int pObj5; // eax
  int pObj; // eax
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
  int pObj7; // eax
  int v26; // eax
  int pObj2; // eax
  int pObj8; // eax
  int v29; // eax
  int v30; // edi
  int v31; // ebx
  int v32; // eax
  int v33; // eax
  uint64_t v34; // rax
  int v35; // ebx
  int pObj6; // eax
  int pObj3; // eax
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
  uint8_t nArg34; // [esp+30h] [ebp-14h]
  uint8_t nArg35; // [esp+30h] [ebp-14h]
  int v61; // [esp+30h] [ebp-14h]
  uint8_t v62; // [esp+37h] [ebp-Dh]
  bool v63; // [esp+37h] [ebp-Dh]
  char v64; // [esp+38h] [ebp-Ch]
  int v65; // [esp+39h] [ebp-Bh]
  int16_t v66; // [esp+3Dh] [ebp-7h]
  char v67; // [esp+3Fh] [ebp-5h]
  int dword_796E502; // [esp+40h] [ebp-4h]

  nArg32 = nArg3;
  dword_796E502 = dword_796E50;
  nArg33 = nArg3;
  if ( nArg3 >= 200 )
    nArg33 = -56;
  pObj4 = sub_418DD0(137);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(
      pObj4,
      297,
      269,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (nArg33 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  v7 = pDwArg1[1];
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
    v9 = sub_699000((int)(pDwArg1 + 2));  // 【clock_now(clk)】
    fArg2 = sub_4049C0(0.0, 255.0, v9, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    nArg3 = (uint64_t)fArg2;
    nArg32 = nArg3;
  }
  sub_491530(2, 0);
  v10 = 120;
  if ( pDwArg1[59] != 0 )
    v10 = 255;
  nArg322 = nArg32;
  if ( nArg32 >= v10 )
    nArg322 = v10;
  pObj5 = sub_418DD0(139);
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(
      pObj5,
      299,
      403,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (nArg322 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  sub_491630(2);
  pObj = sub_418DD0(173);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(
      pObj,
      320,
      408,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)nArg3 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  v14 = pDwArg1[59];
  if ( v14 == 0 )
    v14 = pDwArg1[58];
  if ( v47 == 0 )
    v14 = sub_476D50(pDwArg1[58], pDwArg1[1], 1.0, 0);
  sub_69A110(504, 406, v14, pDwArg1[78]);
  if ( v47 != 0 || v14 != pDwArg1[58] )
  {
    v8 = v47;
LABEL_24:
    v16 = 1;
    for ( i = pDwArg1 + 51; ; ++i )
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
    v44 = pDwArg1 + 51;
    while ( 1 )
    {
      v55 = *(uint32_t *)(sub_418DD0(138) + 20) >> 1;
      v62 = *(&v64 + v19);
      Value = dword_6C87D0[v42 + v62];
      v45 = *v43;
      v48 = *(uint32_t *)(sub_418DD0(Value) + 20) >> 1;
      v20 = *(uint32_t *)(sub_418DD0(140) + 20) >> 1;
      sub_491530(2, 0);
      if ( pDwArg1[83] != 0 || v19 != v47 )
        goto LABEL_47;
      v21 = v62;
      if ( v62 != 0 )
        break;
LABEL_48:
      nArg34 = nArg3;
      v26 = v21 != 0 ? 255 : 120;
      if ( nArg3 >= v26 )
        nArg34 = v26;
      pObj2 = sub_418DD0(138);
      if ( pObj2 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(
          pObj2,
          dword_6C8790[2 * v19],
          dword_6C8794[2 * v19],
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          (nArg34 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_491630(2);
      nArg35 = nArg3;
      if ( nArg3 >= 255 )
        nArg35 = -1;
      pObj8 = sub_418DD0(Value);
      if ( pObj8 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj8 + 128))(
          pObj8,
          v55 + dword_6C8790[2 * v19] - v48,
          dword_6C8794[2 * v19] + 3,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          (nArg35 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      if ( pDwArg1[83] == 1 && v19 == v47 )
      {
        v29 = sub_699000((int)(pDwArg1 + 2));  // 【clock_now(clk)】
        v63 = v29 <= 350;
        if ( v29 <= 350 )
          sub_491530(5, -1);
        Valuea = *v44;
        v30 = v55 + dword_6C8790[2 * v19] - sub_699FC0(*v44) / 2;
        v31 = dword_6C8794[2 * v19] - 10;
        v32 = sub_699000((int)(pDwArg1 + 2));  // 【clock_now(clk)】
        sub_4049F0(0.0, 40.0, v32, 1000, 0);
        v49 = (uint64_t)fArg2;
        v33 = sub_699000((int)(pDwArg1 + 2));  // 【clock_now(clk)】
        fArg2 = sub_4049C0(637.0, 0.0, v33, 1300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        v34 = (uint64_t)fArg2;
        v61 = (uint64_t)fArg2;
        if ( v61 > 255 )
          LODWORD(v34) = 255;
        v35 = v31 - v49;
        sub_69A110(v30, v35, Valuea, v34);
        v56 = -1;
        if ( v61 <= 255 )
          v56 = v61;
        v50 = *(uint32_t *)(sub_418DD0(172) + 20);
        pObj6 = sub_418DD0(172);
        if ( pObj6 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj6 + 128))(
            pObj6,
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
          pObj3 = sub_418DD0(v45);
          if ( pObj3 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(
              pObj3,
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
        if ( sub_699000((int)(pDwArg1 + 2)) >= 1000 )  // 【clock_now(clk)】
        {
          v41 = pDwArg1[1] + 1;
          pDwArg1[83] = 0;
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
    v22 = sub_699000((int)(pDwArg1 + 2));  // 【clock_now(clk)】
    v23 = (int)(pDwArg1 + 2);
    if ( v22 > 150 )
    {
      if ( sub_699000(v23) > 250 )  // 【clock_now(clk)】
      {
LABEL_43:
        pObj7 = sub_418DD0(140);
        if ( pObj7 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj7 + 128))(
            pObj7,
            v55 + dword_6C8790[2 * v19] - v20,
            dword_6C8794[2 * v19] - 16,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)v58 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        if ( sub_699000((int)(pDwArg1 + 2)) >= 250 )  // 【clock_now(clk)】
          pDwArg1[83] = 1;
LABEL_47:
        v21 = v62;
        goto LABEL_48;
      }
      v24 = sub_699000((int)(pDwArg1 + 2)) % 500;  // 【clock_now(clk)】
      v40 = 250;
      if ( v24 < 250 )
      {
        fArg2 = sub_4049C0(255.0, 0.0, v24, 250);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
LABEL_42:
        v58 = (uint64_t)fArg2;
        goto LABEL_43;
      }
      v39 = v24 - 250;
    }
    else
    {
      v40 = 150;
      v39 = sub_699000(v23);  // 【clock_now(clk)】
    }
    fArg2 = sub_4049C0(0.0, 255.0, v39, v40);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    goto LABEL_42;
  }
  result = (uint32_t *)sub_4772A0(pDwArg1[1] + 1);
  pDwArg1[83] = 0;
  return result;
}


// ------------------------------------------------------------
// 0x477AF0 sub_477AF0
// ------------------------------------------------------------
// 析构辅助：删除 +48 对象并清空 +12 处 std::string 成员（SSO 复位）
void /*thiscall*/ sub_477AF0(int this)
{
  int fld_30; // ecx

  fld_30 = *(uint32_t *)(this + 48);
  if ( fld_30 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_30 + 4))(fld_30, 1);
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
char /*userpurge*/ sub_477B60@<al>(int pArg1@<ecx>, double fArg2@<st0>, int nArg3)
{
  int v3; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // edi
  int v8; // eax
  uint8_t v9; // bl
  int pObj8; // eax
  uint8_t v11; // bl
  int pObj9; // eax
  double v13; // st7
  int v14; // edi
  int pObj5; // eax
  int v16; // edi
  int pObj10; // eax
  int v18; // eax
  uint64_t v19; // rax
  int v20; // edi
  uint64_t v21; // rax
  uint32_t *v22; // eax
  int v23; // edi
  int pObj2; // eax
  int v25; // edi
  int pObj; // eax
  int v27; // edi
  int pObj14; // eax
  int v29; // edi
  int pObj7; // eax
  int v31; // eax
  uint64_t v32; // rax
  int v33; // edi
  uint64_t v34; // rax
  uint32_t *v35; // eax
  int v36; // edi
  int pObj13; // eax
  int v38; // edi
  int pObj4; // eax
  int v40; // edi
  int pObj6; // eax
  int v42; // edi
  int pObj11; // eax
  int v44; // eax
  uint64_t v45; // rax
  int v46; // edi
  int v47; // ebx
  int v48; // eax
  int v49; // ecx
  int v50; // eax
  int v51; // eax
  int pObj12; // eax
  int v53; // eax
  int pObj3; // eax
  int pObj15; // eax
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
  float fArg22; // [esp+1Ch] [ebp+8h]
  int v79; // [esp+1Ch] [ebp+8h]
  int v80; // [esp+1Ch] [ebp+8h]
  int v81; // [esp+1Ch] [ebp+8h]
  float fArg23; // [esp+1Ch] [ebp+8h]

  LOBYTE(v3) = nArg3;
  v5 = *(uint32_t *)(pArg1 + 76);
  if ( nArg3 == v5 )
  {
    v6 = *(uint32_t *)(pArg1 + 4);
    if ( v6 >= 2 )
    {
      v7 = 255;
      if ( v6 != 2
        || (v8 = sub_699000(pArg1 + 8), v7 = (uint64_t)sub_4049C0(0.0, 255.0, v8, 800), v9 = v7, v7 >= 220) )  // 【clock_now(clk)】
      {
        v9 = -36;
      }
      pObj8 = sub_418DD0(33);
      if ( pObj8 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj8 + 128))(
          pObj8,
          0,
          0,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          (v9 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      fArg2 = (double)sub_699000(pArg1 + 92) * 0.000033333334;  // 【clock_now(clk)】
      sub_491530(2, 0);
      v11 = v7;
      if ( v7 >= 120 )
        v11 = 120;
      pObj9 = sub_418DD0(1);
      if ( pObj9 != 0 )
      {
        fArg22 = fArg2;
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj9 + 128))(
          pObj9,
          111,
          31,
          dword_79C0B0,
          1065353216,
          1065353216,
          LODWORD(fArg22),
          (v11 << 24) | 0xFFFFFF,
          1129447424,
          1129447424);
      }
      sub_491630(2);
      if ( *(uint32_t *)(pArg1 + 4) == 16 )
        v7 = *(uint32_t *)(pArg1 + 312);
      sub_476CA0(v7);
      if ( *(uint32_t *)(pArg1 + 4) == 2 && sub_699000(pArg1 + 8) >= 800 )  // 【clock_now(clk)】
        goto LABEL_16;
    }
    if ( *(int *)(pArg1 + 4) >= 3 )
    {
      v13 = COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(pArg1 + 196) + 976));
      sub_69A110(351, 86, (uint64_t)v13, *(uint32_t *)(pArg1 + 312));
      v14 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
      pObj5 = sub_418DD0(24);
      if ( pObj5 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(
          pObj5,
          351,
          84,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v14,
          1333788672,
          1333788672);
      fArg2 = COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(pArg1 + 196) + 990));
      sub_69A110(381, 86, (uint64_t)fArg2, *(uint32_t *)(pArg1 + 312));
      if ( sub_699000(pArg1 + 8) >= 800 && *(uint32_t *)(pArg1 + 4) == 3 )  // 【clock_now(clk)】
      {
        sub_432EA0("RESULT_CHARACTER", -1, 0, 0);
        sub_432EA0("RESULT_SCORE_UP_LOOP", 33311, 0, 0);
        LOBYTE(v3) = sub_4772A0(*(uint32_t *)(pArg1 + 4) + 1);
        return v3;
      }
    }
    if ( *(int *)(pArg1 + 4) >= 4 )
    {
      v16 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
      pObj10 = sub_418DD0(14);
      if ( pObj10 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj10 + 128))(
          pObj10,
          172,
          141,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v16,
          1333788672,
          1333788672);
      if ( *(int *)(pArg1 + 4) >= 7 && *(uint8_t *)(pArg1 + 240) != 0 && sub_699000(pArg1 + 92) % 2000 < 1000 )  // 【clock_now(clk)】
      {
        v73 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
        v18 = sub_418DD0(17);
        sub_43B560(173, 139, v18, 1065353216, 1065353216, 0, v73, 1333788672, 1333788672);
      }
      v19 = (uint64_t)COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(pArg1 + 196) + 878));
      v20 = sub_476D50(v19, 4, 1.0, 0);
      v21 = (uint64_t)COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(pArg1 + 196) + 892));
      v79 = (uint64_t)sub_4049C0(0.0, 161.0, v20, v21);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      sub_69A110(312, 142, v20, *(uint32_t *)(pArg1 + 312));
      v22 = (uint32_t *)dword_79C0B0;
      *(uint32_t *)(dword_79C0B0 + 48) = 0;
      v22[13] = 0;
      v22[14] = v79 + 364;
      v22[15] = 480;
      v23 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
      pObj2 = sub_418DD0(23);
      if ( pObj2 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(
          pObj2,
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
      v25 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
      pObj = sub_418DD0(78);
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(
          pObj,
          364,
          139,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v25,
          1333788672,
          1333788672);
      fArg2 = (double)v79 * 0.0062111802 * 100.0;
      sub_69A110(451, 143, (uint64_t)fArg2, *(uint32_t *)(pArg1 + 312));
      v27 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
      pObj14 = sub_418DD0(26);
      if ( pObj14 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj14 + 128))(
          pObj14,
          451,
          143,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v27,
          1333788672,
          1333788672);
      if ( sub_699000(pArg1 + 8) >= 800 && *(uint32_t *)(pArg1 + 4) == 4 )  // 【clock_now(clk)】
        goto LABEL_16;
    }
    if ( *(int *)(pArg1 + 4) < 5 )
      goto LABEL_53;
    v29 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
    pObj7 = sub_418DD0(15);
    if ( pObj7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj7 + 128))(
        pObj7,
        172,
        175,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v29,
        1333788672,
        1333788672);
    if ( *(int *)(pArg1 + 4) >= 7 && *(uint8_t *)(pArg1 + 241) != 0 && sub_699000(pArg1 + 92) % 2000 < 1000 )  // 【clock_now(clk)】
    {
      v74 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
      v31 = sub_418DD0(17);
      sub_43B560(173, 172, v31, 1065353216, 1065353216, 0, v74, 1333788672, 1333788672);
    }
    v32 = (uint64_t)COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(pArg1 + 196) + 906));
    v33 = sub_476D50(v32, 5, 1.0, 0);
    v34 = (uint64_t)COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(pArg1 + 196) + 920));
    v80 = (uint64_t)sub_4049C0(0.0, 161.0, v33, v34);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    sub_69A110(312, 177, v33, *(uint32_t *)(pArg1 + 312));
    v35 = (uint32_t *)dword_79C0B0;
    *(uint32_t *)(dword_79C0B0 + 48) = 0;
    v35[13] = 0;
    v35[14] = v80 + 364;
    v35[15] = 480;
    v36 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
    pObj13 = sub_418DD0(23);
    if ( pObj13 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj13 + 128))(
        pObj13,
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
    v38 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
    pObj4 = sub_418DD0(78);
    if ( pObj4 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(
        pObj4,
        364,
        172,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v38,
        1333788672,
        1333788672);
    fArg2 = (double)v80 * 0.0062111802 * 100.0;
    sub_69A110(451, 176, (uint64_t)fArg2, *(uint32_t *)(pArg1 + 312));
    v40 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
    pObj6 = sub_418DD0(26);
    if ( pObj6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj6 + 128))(
        pObj6,
        451,
        176,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v40,
        1333788672,
        1333788672);
    if ( sub_699000(pArg1 + 8) >= 800 && *(uint32_t *)(pArg1 + 4) == 5 )  // 【clock_now(clk)】
    {
LABEL_16:
      sub_432EA0("RESULT_CHARACTER", -1, 0, 0);
      LOBYTE(v3) = sub_4772A0(*(uint32_t *)(pArg1 + 4) + 1);
    }
    else
    {
LABEL_53:
      if ( *(int *)(pArg1 + 4) < 6 )
        goto LABEL_68;
      v42 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
      pObj11 = sub_418DD0(16);
      if ( pObj11 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj11 + 128))(
          pObj11,
          172,
          207,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v42,
          1333788672,
          1333788672);
      if ( *(int *)(pArg1 + 4) >= 7 && *(uint8_t *)(pArg1 + 242) != 0 && sub_699000(pArg1 + 92) % 2000 < 1000 )  // 【clock_now(clk)】
      {
        v75 = (*(uint8_t *)(pArg1 + 312) << 24) | 0xFFFFFF;
        v44 = sub_418DD0(17);
        sub_43B560(173, 205, v44, 1065353216, 1065353216, 0, v75, 1333788672, 1333788672);
      }
      v45 = (uint64_t)COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(pArg1 + 196) + 948));
      v81 = sub_476D50(v45, 6, 1.0, 0);
      sub_69A110(312, 209, v81, *(uint32_t *)(pArg1 + 312));
      if ( *(uint32_t *)(pArg1 + 4) == 6 && COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(pArg1 + 196) + 948)) == (double)v81 )
        sub_432EE0(33311);
      fArg2 = (double)sub_699000(pArg1 + 8);  // 【clock_now(clk)】
      if ( fArg2 >= 1200.0 && *(uint32_t *)(pArg1 + 4) == 6 )
      {
        sub_4772A0(7);
        if ( (uint8_t)sub_476EC0(pArg1) != 0 )
        {
          sub_476EE0(pArg1);
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
        v46 = *(uint32_t *)(pArg1 + 4);
        if ( v46 < 7 )
          goto LABEL_100;
        fArg23 = 1.0;
        v47 = 255;
        if ( *(int *)(pArg1 + 204) > 0 && v46 == 9
          || *(int *)(pArg1 + 208) > 0 && v46 == 10
          || *(int *)(pArg1 + 212) > 0 && v46 == 11 )
        {
          v46 = *(uint32_t *)(pArg1 + 4);
          fArg2 = (double)(unsigned int)(sub_699000(pArg1 + 92) - *(uint32_t *)(pArg1 + 4 * v46 + 120)) * 0.0040000002;  // 【clock_now(clk)】
          *(float *)(pArg1 + 308) = fArg2;
        }
        if ( v46 == 7 )
        {
          v48 = sub_495C80(*(uint32_t *)(pArg1 + 196));
          v49 = pArg1 + 8;
          if ( v48 < 55 )
          {
            if ( sub_699000(v49) < 800 )  // 【clock_now(clk)】
            {
              v51 = sub_699000(pArg1 + 8);  // 【clock_now(clk)】
              v47 = sub_423A80(0, 255, v51, 800);
            }
          }
          else if ( sub_699000(v49) < 300 )  // 【clock_now(clk)】
          {
            v50 = sub_699000(pArg1 + 8);  // 【clock_now(clk)】
            sub_4049F0(3.0, 1.0, v50, 300, 1);
            fArg23 = fArg2;
          }
        }
        if ( *(uint32_t *)(pArg1 + 4) == 16 )
          v47 = *(uint32_t *)(pArg1 + 312);
        sub_476F50(pArg1, fArg2);
        sub_491530(2, 0);
        v77 = v47;
        if ( v47 >= 200 )
          v77 = -56;
        v76 = *(uint32_t *)(pArg1 + 308);
        pObj12 = sub_418DD0(2);
        if ( pObj12 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, int, int, int, int))(*(uint32_t *)pObj12 + 128))(
            pObj12,
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
        v53 = sub_476DD0(pArg1);
        pObj3 = sub_418DD0(v53);
        if ( pObj3 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, float, float, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 156))(
            pObj3,
            116,
            289,
            dword_79C0B0,
            COERCE_FLOAT(LODWORD(fArg23)),
            COERCE_FLOAT(LODWORD(fArg23)),
            0,
            ((uint8_t)v47 << 24) | 0xFFFFFF,
            1116471296,
            1116602368);
        pObj15 = sub_418DD0(13);
        if ( pObj15 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj15 + 128))(
            pObj15,
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
          fArg2 = 1.0;
          if ( fArg23 == 1.0 && *(uint32_t *)(pArg1 + 188) == 0xFFFF )
            *(uint32_t *)(pArg1 + 188) = sub_699000(pArg1 + 8) + 1000;
        }
        if ( *(uint32_t *)(pArg1 + 4) != 7
          || *(uint32_t *)(pArg1 + 188) == 0xFFFF
          || (unsigned int)sub_699000(pArg1 + 8) < *(uint32_t *)(pArg1 + 188) )  // 【clock_now(clk)】
        {
LABEL_100:
          v3 = *(uint32_t *)(pArg1 + 4);
          if ( v3 >= 8 )
            LOBYTE(v3) = (uint8_t)sub_4773E0((int *)pArg1, fArg2, *(uint32_t *)(pArg1 + 312));
          if ( *(int *)(pArg1 + 4) >= 16 )
          {
            if ( sub_699000(pArg1 + 8) <= 2000 )  // 【clock_now(clk)】
            {
              if ( (uint8_t)sub_477240(pArg1) != 0 )
                sub_477060((uint32_t *)pArg1);
            }
            else
            {
              v56 = sub_699000(pArg1 + 8);  // 【clock_now(clk)】
              *(uint32_t *)(pArg1 + 312) = sub_423A80(255, 0, v56, 2800);
            }
            v3 = sub_699000(pArg1 + 8);  // 【clock_now(clk)】
            if ( v3 >= 3000 && *(uint32_t *)(pArg1 + 4) == 16 )
            {
              LOBYTE(v3) = *(uint8_t *)(pArg1 + 328);
              if ( (uint8_t)v3 == 0 )
              {
                sub_423200(dword_8F7B08, 72);  // 【发送网络包API】
                LOBYTE(v3) = sub_423380(dword_8F7B08);
                *(uint8_t *)(pArg1 + 328) = 1;
              }
            }
          }
        }
        else
        {
          LOBYTE(v3) = sub_4772A0(*(uint32_t *)(pArg1 + 4) + 1);
          *(uint32_t *)(pArg1 + 332) = 0;
        }
      }
    }
  }
  else if ( nArg3 == *(uint32_t *)(pArg1 + 80) )
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
      v59 = *(uint32_t *)(pArg1 + 4);
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
// 社区界面（Friend 面板?）初始化：存 +48/+49 参数，建两个 0x68 绘制对象
// （sub_426BD0，+19/+20），填偏移/字距表（v14/v15/v16）
char /*thiscall*/ sub_478C70(int *this, void *Block, int nArg3)
{
  uint8_t *pMem; // eax
  int v5; // ebx
  uint8_t *v6; // eax
  uint8_t *pMem2; // eax
  uint8_t *v8; // eax
  uint32_t *pMem3; // esi
  int v10; // ecx
  int v11; // edx
  int fld_e20; // [esp-4h] [ebp-9Ch]
  uint32_t v14[10]; // [esp+Ch] [ebp-8Ch]
  uint32_t v15[10]; // [esp+34h] [ebp-64h]
  void *v16[11]; // [esp+5Ch] [ebp-3Ch]
  int dword_79C0B02; // [esp+88h] [ebp-10h]
  int v18; // [esp+94h] [ebp-4h]
  char *Blocka; // [esp+A0h] [ebp+8h]
  int fld_e21; // [esp+A4h] [ebp+Ch]

  *(this + 48) = (int)Block;
  *(this + 49) = nArg3;
  *(this + 21) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 64);
  *(this + 22) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 88);
  pMem = operator new(0x68u);
  v5 = 0;
  v18 = 0;
  if ( pMem != nullptr )
    v6 = sub_426BD0(pMem);
  else
    v6 = nullptr;
  *(this + 19) = (int)v6;
  *((uint32_t *)v6 + 7) = 640;
  *((uint32_t *)v6 + 8) = 480;
  *(uint32_t *)(*(this + 19) + 68) = this;
  pMem2 = operator new(0x68u);
  v18 = 1;
  if ( pMem2 != nullptr )
    v8 = sub_426BD0(pMem2);
  else
    v8 = nullptr;
  *(this + 20) = (int)v8;
  *((uint32_t *)v8 + 17) = this;
  fld_e20 = *(this + 20);
  v18 = -1;
  sub_69A840(fld_e20);
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
    pMem3 = operator new(0x2Cu);
    v16[10] = pMem3;
    v18 = 2;
    if ( pMem3 != nullptr )
    {
      fld_e21 = *(this + 21);
      dword_79C0B02 = dword_79C0B0;
      *((uint8_t *)pMem3 + 4) = 0;
      LOBYTE(v18) = 3;
      *pMem3 = &vftbl_nengine__CNNumberSet;
      sub_699E20(pMem3);
      sub_699E40(dword_79C0B02, fld_e21, v16[v5], 7);
    }
    else
    {
      pMem3 = nullptr;
    }
    v10 = v15[v5];
    *(uint32_t *)Blocka = pMem3;
    pMem3[10] = v10;
    *(uint32_t *)(*(uint32_t *)Blocka + 36) = v14[v5];
    v11 = *(uint32_t *)Blocka;
    ++v5;
    v18 = -1;
    *(uint8_t *)(v11 + 24) = 0;
    Blocka += 4;
  }
  while ( v5 < 10 );
  sub_698F90((int)(this + 23), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  return sub_4772A0((int)this, 0);
}



// ------------------------------------------------------------
// 0x478EA0 sub_478EA0
// ------------------------------------------------------------
// 列表滚动状态机（一）：nArg2==1 复位 +56/+60；+60==1 且 +92 计时
// >=10 秒时进入下一状态（长驻超时）
char /*thiscall*/ sub_478EA0(int this, int nArg2)
{
  int fld_38; // eax

  if ( nArg2 == 1 )
  {
    *(uint32_t *)(this + 60) = 0;
    *(uint32_t *)(this + 56) = 0;
  }
  if ( (*(uint32_t *)(this + 60) != 1 || (fld_38 = sub_699000(this + 92)) >= 10000)  // 【clock_now(clk)】
    && (*(uint32_t *)(this + 56) != 1 || (fld_38 = sub_699000(this + 64)) >= 3000) )  // 【clock_now(clk)】
  {
    sub_423200(dword_8F7B08, 70);  // 【发送网络包API】
    sub_423380(dword_8F7B08);
    *(uint32_t *)(this + 56) = 1;
    *(uint8_t *)(this + 77) = 0;
    *(uint8_t *)(this + 78) = 0;
    LOBYTE(fld_38) = sub_698F90(this + 64, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return fld_38;
}



// ------------------------------------------------------------
// 0x478F20 sub_478F20
// ------------------------------------------------------------
// 滚动状态复位（一）：+56=0/+60=1，清 +77/+78 旗标，+92 计时器清零
char /*thiscall*/ sub_478F20(int this)
{
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 1;
  *(uint8_t *)(this + 77) = 0;
  *(uint8_t *)(this + 78) = 0;
  return sub_698F90(this + 92, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x478F40 sub_478F40
// ------------------------------------------------------------
// 列表滚动状态机（二）：与 sub_478EA0 同构（+48/+52 与 +84 计时器）
char /*thiscall*/ sub_478F40(int this, int nArg2)
{
  int fld_30; // eax

  if ( nArg2 == 1 )
  {
    *(uint32_t *)(this + 52) = 0;
    *(uint32_t *)(this + 48) = 0;
  }
  if ( (*(uint32_t *)(this + 52) != 1 || (fld_30 = sub_699000(this + 84)) >= 10000)  // 【clock_now(clk)】
    && (*(uint32_t *)(this + 48) != 1 || (fld_30 = sub_699000(this + 56)) >= 3000) )  // 【clock_now(clk)】
  {
    sub_423200(dword_8F7B08, 82);  // 【发送网络包API】
    sub_423380(dword_8F7B08);
    *(uint32_t *)(this + 48) = 1;
    *(uint8_t *)(this + 69) = 0;
    *(uint8_t *)(this + 70) = 0;
    LOBYTE(fld_30) = sub_698F90(this + 56, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return fld_30;
}



// ------------------------------------------------------------
// 0x478FC0 sub_478FC0
// ------------------------------------------------------------
// 滚动状态复位（二）：+48=0/+52=1，清 +69/+70，+84 计时器清零
char /*thiscall*/ sub_478FC0(int this)
{
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 1;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  return sub_698F90(this + 84, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x478FE0 sub_478FE0
// ------------------------------------------------------------
// 180 字节条目 vector 元素数访问器：(end-begin)/180
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
// 树辅助（+49 nil 旗标）：取右子树最大节点（tree_max）
int /*cdecl*/ sub_479010(int pArg1)
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 49) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x479030 sub_479030
// ------------------------------------------------------------
// 树辅助（+49 nil 旗标）：取中序前驱/后继节点（tree_next 族）
uint32_t */*cdecl*/ sub_479030(uint32_t *pArg1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 49) == 0 )
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
// 树辅助（+49 nil 旗标）：迭代器步进（++it，走右子树或回溯父链）
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
// 树辅助（+49 nil 旗标）：迭代器后退（--it，走左子树最右或回溯父链）
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
// 另一 180 字节条目 vector 元素数访问器：(end-begin)/180
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
// RB-tree erase(iterator)（+48/+49 旗标克隆，RB-DELETE，经 sub_479610
// 取后继；与 sub_470BB0 同构）
uint32_t */*thiscall*/ sub_479140(uint32_t *this, int pArg2)
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);
  *(uint32_t *)(pArg2 + 8) = *result;
  if ( *(uint8_t *)(*result + 49) == 0 )
    *(uint32_t *)(*result + 4) = pArg2;
  result[1] = *(uint32_t *)(pArg2 + 4);
  fld_e1 = *(this + 1);
  if ( pArg2 == *(uint32_t *)(fld_e1 + 4) )
  {
    *(uint32_t *)(fld_e1 + 4) = result;
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;
  }
  else
  {
    v4 = *(uint32_t **)(pArg2 + 4);
    if ( pArg2 == *v4 )
      *v4 = result;
    else
      v4[2] = result;
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4791A0 sub_4791A0
// ------------------------------------------------------------
// RB-tree 右旋辅助（+48/+49 旗标树，erase 修复/插入共用）
int /*thiscall*/ sub_4791A0(uint32_t *this, uint32_t *pArg2)
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 49) == 0 )
    *(uint32_t *)(v3 + 4) = pArg2;
  *(uint32_t *)(result + 4) = pArg2[1];
  fld_e1 = *(this + 1);
  if ( pArg2 == *(uint32_t **)(fld_e1 + 4) )
  {
    *(uint32_t *)(fld_e1 + 4) = result;
    *(uint32_t *)(result + 8) = pArg2;
    pArg2[1] = result;
  }
  else
  {
    v5 = (uint32_t *)pArg2[1];
    if ( pArg2 == (uint32_t *)v5[2] )
      v5[2] = result;
    else
      *v5 = result;
    *(uint32_t *)(result + 8) = pArg2;
    pArg2[1] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x479200 sub_479200
// ------------------------------------------------------------
// 分配 0x34 字节树头节点并初始化自环（operator new + 清零）
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
// 180 字节条目按下标取址（越界返回 0）
int /*thiscall*/ sub_479240(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax

  fld_e2 = *(this + 2);
  if ( fld_e2 != 0 && uArg2 < (*(this + 3) - fld_e2) / 180 )
    return *(this + 2) + 180 * uArg2;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x479290 sub_479290
// ------------------------------------------------------------
// 按名字串查找条目下标（180 字节条目遍历比对；未找到返回 -1 附近值）
int /*thiscall*/ sub_479290(uint32_t *this, const char *pArg2)
{
  unsigned int v3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v6; // edx
  int v7; // eax
  const char *psz; // eax
  int i; // [esp+Ch] [ebp-4h]

  v3 = 0;
  for ( i = 0; ; i += 180 )
  {
    fld_e2 = *(this + 2);
    if ( fld_e2 == 0 || v3 >= (*(this + 3) - fld_e2) / 180 )
      break;
    fld_e22 = *(this + 2);
    v6 = *(uint32_t *)(fld_e22 + i + 24);
    v7 = i + fld_e22;
    if ( v6 < 0x10 )
      psz = (const char *)(v7 + 4);
    else
      psz = *(const char **)(v7 + 4);
    if ( strcmp(psz, pArg2) == 0 )
      return v3;
    ++v3;
  }
  return -1;
}



// ------------------------------------------------------------
// 0x479340 CNRDFriendManager__vmt4
// ------------------------------------------------------------
// CNRDFriendManager::vmt4 好友管理帧处理（RTTI 自证）
int /*thiscall*/ CNRDFriendManager__vmt4(uint32_t *this, const char *pArg2)
{
  int fld_e2; // eax
  char *v3; // eax

  fld_e2 = *(this + 2);
  if ( fld_e2 != 0 && (unsigned int)((*(this + 3) - fld_e2) / 180) >= 0x20 )
  {
    v3 = sub_422E70(396);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);
  }
  if ( sub_479290(this, pArg2) > 0 )
  {
    v3 = sub_422E70(397);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);
  }
  sub_423200(dword_8F7B08, 63);  // 【发送网络包API】
  sub_41C100(pArg2);
  return sub_423380(dword_8F7B08);
}



// ------------------------------------------------------------
// 0x4793D0 CNRDFriendManager__vmt8
// ------------------------------------------------------------
// CNRDFriendManager::vmt8（RTTI 自证）
int /*thiscall*/ CNRDFriendManager__vmt8(uint32_t *this, const char *pArg2)
{
  char *v2; // eax

  if ( sub_479290(this, pArg2) == -1 )
  {
    v2 = sub_422E70(398);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);
  }
  else
  {
    sub_423200(dword_8F7B08, 64);  // 【发送网络包API】
    sub_41C100(pArg2);
    return sub_423380(dword_8F7B08);
  }
}



// ------------------------------------------------------------
// 0x479430 CNRDMemberManager__vmt4
// ------------------------------------------------------------
// CNRDMemberManager::vmt4 会员管理帧处理（RTTI 自证）
int /*thiscall*/ CNRDMemberManager__vmt4(uint32_t *this, const char *pArg2)
{
  char *v2; // eax

  if ( sub_479290(this, pArg2) < 0 )
  {
    sub_423200(dword_8F7B08, 79);  // 【发送网络包API】
    sub_41C100(pArg2);
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
int /*thiscall*/ CNRDMemberManager__vmt8(uint32_t *this, const char *pArg2)
{
  char *v2; // eax

  if ( sub_479290(this, pArg2) == -1 )
  {
    v2 = sub_422E70(1523);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v2, 0);
  }
  else
  {
    sub_423200(dword_8F7B08, 81);  // 【发送网络包API】
    sub_41C100(pArg2);
    return sub_423380(dword_8F7B08);
  }
}



// ------------------------------------------------------------
// 0x4794F0 sub_4794F0
// ------------------------------------------------------------
// 按名找到条目后置其 +40 旗标为 uArg3（在线/成员状态标记）
int /*thiscall*/ sub_4794F0(uint32_t *this, const char *pArg2, uint8_t uArg3)
{
  int result; // eax

  result = sub_479290(this, pArg2);
  if ( result >= 0 )
  {
    result = *(this + 2) + 180 * result;
    if ( result != 0 )
      *(uint32_t *)(result + 40) = uArg3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x479520 sub_479520
// ------------------------------------------------------------
// 按名找到条目后清其 +40 旗标（置 -1）
int /*thiscall*/ sub_479520(uint32_t *this, const char *pArg2)
{
  int result; // eax

  result = sub_479290(this, pArg2);
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
// map 查找（int 键）：返回命中节点或 end
int */*thiscall*/ sub_479550(int **this, int pArg2)
{
  int *fld_e1; // ecx
  int *v3; // eax
  unsigned int v4; // edx
  unsigned int v5; // esi
  const char **v6; // ecx
  const char *v7; // edi
  unsigned int v8; // ebx
  int v9; // ecx
  const char *v10; // esi
  int nCmp; // edx
  bool v12; // sf
  unsigned int v14; // [esp+0h] [ebp-Ch]
  const char **i; // [esp+4h] [ebp-8h]
  int *fld_e12; // [esp+8h] [ebp-4h]
  unsigned int v17; // [esp+14h] [ebp+8h]

  fld_e1 = *(this + 1);
  v3 = (int *)fld_e1[1];
  fld_e12 = fld_e1;
  if ( *((uint8_t *)v3 + 49) == 0 )
  {
    v4 = *(uint32_t *)(pArg2 + 24);
    v5 = *(uint32_t *)(pArg2 + 20);
    v6 = (const char **)(pArg2 + 4);
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
      nCmp = memcmp(v10, v7, v9);
      v12 = nCmp < 0;
      v5 = v17;
      if ( nCmp == 0 )
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
      fld_e12 = v3;
      v3 = (int *)*v3;
LABEL_19:
      if ( *((uint8_t *)v3 + 49) != 0 )
        return fld_e12;
    }
  }
  return fld_e1;
}



// ------------------------------------------------------------
// 0x479610 sub_479610
// ------------------------------------------------------------
// 树辅助（+49 旗标）：取后继节点（erase 返回值用，tree_next）
int **/*thiscall*/ sub_479610(int **this, int **pDwArg2, unsigned int *pDwArg3)
{
  int *v5; // eax
  unsigned int v6; // ecx
  const char *v7; // eax
  int *v9; // [esp+18h] [ebp+Ch]

  v5 = sub_479550(this, (int)pDwArg3);
  v9 = v5;
  if ( v5 == *(this + 1)
    || ((v6 = v5[8], (unsigned int)v5[9] < 0x10) ? (v7 = (const char *)(v5 + 4)) : (v7 = (const char *)v5[4]),
        sub_40BF00((std::_String_base *)pDwArg3, 0, pDwArg3[5], v7, v6) < 0) )
  {
    *pDwArg2 = *(this + 1);
    return pDwArg2;
  }
  else
  {
    *pDwArg2 = v9;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x479680 sub_479680
// ------------------------------------------------------------
// 抛 std::length_error（容器长度溢出辅助）
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
  sub_4015C0((void *)"vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4796F0 sub_4796F0
// ------------------------------------------------------------
// 成员 string 拷贝/赋值（SSO：+24 容量、+20 长度、+4 缓冲）
int /*thiscall*/ sub_4796F0(int this, uint32_t *pArg2)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((std::_String_base *)this, pArg2, 0, -1);
  *(uint32_t *)(this + 28) = pArg2[7];
  *(uint32_t *)(this + 32) = pArg2[8];
  *(uint32_t *)(this + 36) = pArg2[9];
  *(uint32_t *)(this + 40) = pArg2[10];
  *(uint32_t *)(this + 44) = pArg2[11];
  *(uint32_t *)(this + 48) = pArg2[12];
  qmemcpy((void *)(this + 52), pArg2 + 13, 0x80u);
  return this;
}



// ------------------------------------------------------------
// 0x479750 sub_479750
// ------------------------------------------------------------
// 36 字节聚合条目反向拷贝（9 dword/条，与 sub_474630 同族）
uint32_t */*cdecl*/ sub_479750(char *pszArg1, char *pszArg2, uint32_t *uArg3)
{
  char *pszArg12; // edi
  uint32_t *uArg32; // esi
  uint8_t *v5; // eax
  int i; // edx

  pszArg12 = pszArg1;
  if ( pszArg1 == pszArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    sub_4014D0((std::_String_base *)uArg32, pszArg12, 0, -1);
    uArg32[7] = *((uint32_t *)pszArg12 + 7);
    uArg32[8] = *((uint32_t *)pszArg12 + 8);
    uArg32[9] = *((uint32_t *)pszArg12 + 9);
    uArg32[10] = *((uint32_t *)pszArg12 + 10);
    uArg32[11] = *((uint32_t *)pszArg12 + 11);
    uArg32[12] = *((uint32_t *)pszArg12 + 12);
    v5 = uArg32 + 13;
    for ( i = 128; i != 0; --i )
    {
      *v5 = v5[pszArg12 - (char *)uArg32];
      ++v5;
    }
    pszArg12 += 180;
    uArg32 += 45;
  }
  while ( pszArg12 != pszArg2 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x4797D0 sub_4797D0
// ------------------------------------------------------------
// 36 字节聚合条目正向拷贝（与 sub_4745E0 同族）
uint32_t */*cdecl*/ sub_4797D0(char *pszArg1, char *pszArg2, uint32_t *uArg3)
{
  char *pszArg22; // edi
  uint32_t *uArg32; // esi
  uint8_t *v5; // eax
  int i; // edx

  pszArg22 = pszArg2;
  if ( pszArg1 == pszArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    pszArg22 -= 180;
    uArg32 -= 45;
    sub_4014D0((std::_String_base *)uArg32, pszArg22, 0, -1);
    uArg32[7] = *((uint32_t *)pszArg22 + 7);
    uArg32[8] = *((uint32_t *)pszArg22 + 8);
    uArg32[9] = *((uint32_t *)pszArg22 + 9);
    uArg32[10] = *((uint32_t *)pszArg22 + 10);
    uArg32[11] = *((uint32_t *)pszArg22 + 11);
    uArg32[12] = *((uint32_t *)pszArg22 + 12);
    v5 = uArg32 + 13;
    for ( i = 128; i != 0; --i )
    {
      *v5 = v5[pszArg22 - (char *)uArg32];
      ++v5;
    }
  }
  while ( pszArg22 != pszArg1 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x479850 sub_479850
// ------------------------------------------------------------
// 遍历 180 字节条目表做名次/位置统计（按 +40 旗标等计数，返回计数值）
unsigned int /*thiscall*/ sub_479850(unsigned int *this)
{
  int v1; // eax
  unsigned int result; // eax
  int fld_e2; // esi
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
    fld_e2 = *(this + 2);
    v5 = *(uint32_t *)(fld_e2 + v10 + 24);
    v6 = (char *)(v10 + fld_e2);
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
// RB-tree erase(iterator)（+48/+49 旗标克隆，RB-DELETE，经 sub_479140
// 族辅助；与 sub_470BB0 同构）
int ***/*thiscall*/ sub_479900(uint32_t *this, int ***uArg2, int **pDwArg3)
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
  void **v15; // eax
  uint32_t *pThis3; // ecx
  uint32_t *v17; // eax
  uint32_t *Block2; // eax
  int v19; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  size_t v22; // [esp+34h] [ebp-34h] BYREF
  char v23; // [esp+38h] [ebp-30h]
  int v24; // [esp+48h] [ebp-20h]
  int v25; // [esp+4Ch] [ebp-1Ch]
  int v26; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v29; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 49) != 0 )
  {
    v25 = 15;
    v24 = 0;
    v23 = 0;
    sub_4015C0(&v22, "invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v29 = 0;
    sub_401740(pExceptionObject, &v22);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_4790B0(&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 49) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 49) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 49) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_479030(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
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
  if ( *((uint8_t *)pDwArg32[2] + 49) != 0 )
  {
    v4 = *pDwArg32;
    goto LABEL_8;
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 49) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)v5;
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 48);
  *((uint8_t *)v5 + 48) = *((uint8_t *)pDwArg32 + 48);
  *((uint8_t *)pDwArg32 + 48) = v14;
LABEL_35:
  v15 = (void **)Block;
  if ( *((uint8_t *)Block + 48) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
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
            pThis3 = pThis;
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
            pThis3 = pThis;
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
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    v15 = (void **)Block;
    *((uint8_t *)v4 + 48) = 1;
  }
  if ( (unsigned int)v15[9] >= 0x10 )
    j__free(v15[4]);
  Block2 = Block;
  *((uint32_t *)Block + 9) = 15;
  Block2[8] = 0;
  *((uint8_t *)Block2 + 16) = 0;
  j__free(Block2);
  v19 = pThis[2];
  if ( v19 != 0 )
    pThis[2] = v19 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x479BE0 sub_479BE0
// ------------------------------------------------------------
// 节点 0x34 字节初始化：存 nArg2/nArg3/nArg4 三 dword + string 成员
// （+36 SSO cap=15）【推断：社交节点构造】
uint32_t */*thiscall*/ sub_479BE0(uint32_t *this, int nArg2, int nArg3, int nArg4, int pArg5, char pszArg6)
{
  char *pThis_3; // edi

  *(this + 1) = nArg3;
  pThis_3 = (char *)(this + 3);
  *this = nArg2;
  *(this + 2) = nArg4;
  *(this + 9) = 15;
  *(this + 8) = 0;
  *((uint8_t *)this + 16) = 0;
  sub_4014D0((std::_String_base *)(this + 3), pArg5, 0, -1);
  *((uint32_t *)pThis_3 + 7) = *(uint32_t *)(pArg5 + 28);
  *((uint32_t *)pThis_3 + 8) = *(uint32_t *)(pArg5 + 32);
  *((uint8_t *)this + 48) = pszArg6;
  *((uint8_t *)this + 49) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x479C40 sub_479C40
// ------------------------------------------------------------
// 节点 0x34 字节区间拷贝（正向，逐节点 sub_479BE0 构造）
uint32_t */*cdecl*/ sub_479C40(uint32_t *uArg1, uint32_t *uArg2, char *pszArg3)
{
  uint32_t *result; // eax
  uint32_t *uArg12; // esi
  int v5; // ebx
  uint8_t *v6; // eax
  int i; // ecx

  result = uArg2;
  uArg12 = uArg1;
  if ( uArg1 != uArg2 )
  {
    v5 = pszArg3 - (char *)uArg1;
    do
    {
      sub_4014D0((std::_String_base *)uArg12, pszArg3, 0, -1);
      uArg12[7] = *((uint32_t *)pszArg3 + 7);
      uArg12[8] = *((uint32_t *)pszArg3 + 8);
      uArg12[9] = *((uint32_t *)pszArg3 + 9);
      uArg12[10] = *((uint32_t *)pszArg3 + 10);
      uArg12[11] = *((uint32_t *)pszArg3 + 11);
      uArg12[12] = *((uint32_t *)pszArg3 + 12);
      v6 = uArg12 + 13;
      for ( i = 128; i != 0; --i )
      {
        *v6 = v6[v5];
        ++v6;
      }
      result = uArg2;
      uArg12 += 45;
      v5 -= 180;
    }
    while ( uArg12 != uArg2 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x479CC0 sub_479CC0
// ------------------------------------------------------------
// 转发 sub_4797D0（36 字节聚合条目正向拷贝）
uint32_t */*cdecl*/ sub_479CC0(char *pszArg1, char *pszArg2, uint32_t *uArg3)
{
  return sub_4797D0(pszArg1, pszArg2, uArg3);
}



// ------------------------------------------------------------
// 0x479CE0 sub_479CE0
// ------------------------------------------------------------
// 36 字节聚合条目按值填充 n 次（与 sub_474CC0 同族）
int /*cdecl*/ sub_479CE0(uint32_t *pArg1, uint32_t *uArg2, int nArg3)
{
  int nArg32; // ebx
  uint32_t *pArg12; // esi
  uint32_t v6[6]; // [esp+0h] [ebp-24h] BYREF
  int v7; // [esp+20h] [ebp-4h]

  nArg32 = nArg3;
  v6[5] = v6;
  v6[4] = nArg3;
  v7 = 0;
  while ( 1 )
  {
    pArg12 = pArg1;
    if ( pArg1 == uArg2 )
      break;
    v6[3] = nArg32;
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
    {
      *(uint32_t *)(nArg32 + 24) = 15;
      *(uint32_t *)(nArg32 + 20) = 0;
      *(uint8_t *)(nArg32 + 4) = 0;
      sub_4014D0((std::_String_base *)nArg32, pArg1, 0, -1);
      *(uint32_t *)(nArg32 + 28) = pArg1[7];
      *(uint32_t *)(nArg32 + 32) = pArg1[8];
      *(uint32_t *)(nArg32 + 36) = pArg1[9];
      *(uint32_t *)(nArg32 + 40) = pArg1[10];
      *(uint32_t *)(nArg32 + 44) = pArg1[11];
      *(uint32_t *)(nArg32 + 48) = pArg1[12];
      qmemcpy((void *)(nArg32 + 52), pArg1 + 13, 0x80u);
      pArg12 = pArg1;
    }
    nArg32 += 180;
    LOBYTE(v7) = 0;
    pArg1 = pArg12 + 45;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x479DF0 sub_479DF0
// ------------------------------------------------------------
// 节点构造：string 成员（+4/+20）置空、+32=4、+40=-1 等默认值，
// 随后按 7 参填字段【推断：社交条目构造】
int /*thiscall*/ sub_479DF0(int this, void *Src, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 4;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 40) = -1;
  *(uint8_t *)(this + 52) = 0;
  sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  *(uint32_t *)(this + 28) = nArg3;
  *(uint32_t *)(this + 32) = nArg4;
  *(uint32_t *)(this + 48) = nArg7;
  *(uint32_t *)(this + 44) = nArg6;
  *(uint8_t *)(this + 52) = 0;
  *(uint32_t *)(this + 36) = nArg5;
  *(uint32_t *)(this + 40) = -1;
  return this;
}



// ------------------------------------------------------------
// 0x479EA0 sub_479EA0
// ------------------------------------------------------------
// RB-tree 整树销毁（+49 nil 旗标）：递归右子树 → 中序释放节点
char /*stdcall*/ sub_479EA0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 49);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_479EA0(i[2]);
    i = (void **)*i;
    sub_5014C0(Block2);
    j__free(Block2);
    result = *((uint8_t *)i + 49);
  }
  return result;
}



// ------------------------------------------------------------
// 0x479EF0 sub_479EF0
// ------------------------------------------------------------
// 分配 0x34 节点并按 5 参构造（含 string 拷贝），返回新节点
uint32_t */*stdcall*/ sub_479EF0(int nArg1, int nArg2, int nArg3, int nArg4, char pszArg5)
{
  uint32_t *pMem; // esi
  void *v7[9]; // [esp+0h] [ebp-24h] BYREF

  v7[5] = v7;
  pMem = operator new(0x34u);
  v7[4] = pMem;
  v7[8] = (void *)1;
  v7[3] = pMem;
  if ( pMem != nullptr )
    sub_479BE0(pMem, nArg1, nArg2, nArg3, nArg4, pszArg5);
  return pMem;
}



// ------------------------------------------------------------
// 0x479F80 sub_479F80
// ------------------------------------------------------------
// 36 字节聚合条目按值填充 n 次（与 sub_479CE0 同族变体）
int /*cdecl*/ sub_479F80(int nArg1, int nArg2, uint32_t *pArg3)
{
  int nArg12; // ebx
  int result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  nArg12 = nArg1;
  v5[5] = v5;
  v5[4] = nArg1;
  v6 = 0;
  while ( 1 )
  {
    result = nArg2;
    if ( nArg2 == 0 )
      break;
    v5[3] = nArg12;
    LOBYTE(v6) = 1;
    if ( nArg12 != 0 )
    {
      *(uint32_t *)(nArg12 + 24) = 15;
      *(uint32_t *)(nArg12 + 20) = 0;
      *(uint8_t *)(nArg12 + 4) = 0;
      sub_4014D0((std::_String_base *)nArg12, pArg3, 0, -1);
      *(uint32_t *)(nArg12 + 28) = pArg3[7];
      *(uint32_t *)(nArg12 + 32) = pArg3[8];
      *(uint32_t *)(nArg12 + 36) = pArg3[9];
      *(uint32_t *)(nArg12 + 40) = pArg3[10];
      *(uint32_t *)(nArg12 + 44) = pArg3[11];
      *(uint32_t *)(nArg12 + 48) = pArg3[12];
      qmemcpy((void *)(nArg12 + 52), pArg3 + 13, 0x80u);
    }
    nArg12 += 180;
    LOBYTE(v6) = 0;
    --nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47A090 sub_47A090
// ------------------------------------------------------------
// 180 字节条目区间析构辅助（逐条 sub_501490）
void /*stdcall*/ sub_47A090(char *pszArg1, char *pszArg2)
{
  char *i; // esi

  for ( i = pszArg1; i != pszArg2; i += 180 )
    sub_501490(i);
}



// ------------------------------------------------------------
// 0x47A0C0 sub_47A0C0
// ------------------------------------------------------------
// 180 字节条目 vector 析构：逐条 sub_501490 后整块 free 并置空
int /*thiscall*/ sub_47A0C0(int this)
{
  char *fld_4; // esi
  int result; // eax
  char *i; // edi

  fld_4 = *(char **)(this + 4);
  result = 0;
  if ( fld_4 != nullptr )
  {
    for ( i = *(char **)(this + 8); fld_4 != i; fld_4 += 180 )
      sub_501490(fld_4);
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
// std::map::erase(first,last) 区间擦除（+49 旗标树，经 sub_479140 逐点
// 擦除；与 sub_4723A0 同构）
int */*thiscall*/ sub_47A110(int **this, int *pDwArg2, int nArg3, int nArg4)
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
  if ( nArg3 == *(uint32_t *)fld_e1 && nArg4 == fld_e1 )
  {
    sub_479EA0(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( nArg3 != nArg4 )
    {
      do
      {
        nArg322 = nArg32;
        if ( *(uint8_t *)(nArg32 + 49) == 0 )
        {
          v11 = *(uint32_t *)(nArg32 + 8);
          if ( *(uint8_t *)(v11 + 49) != 0 )
          {
            for ( i = *(uint32_t *)(nArg32 + 4); *(uint8_t *)(i + 49) == 0; i = *(uint32_t *)(i + 4) )
            {
              if ( nArg32 != *(uint32_t *)(i + 8) )
                break;
              nArg32 = i;
            }
            nArg32 = i;
          }
          else
          {
            nArg32 = *(uint32_t *)(nArg32 + 8);
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 49) == 0; j = *(uint32_t *)j )
              nArg32 = j;
          }
        }
        sub_479900(this, &nArg3, nArg322);
      }
      while ( nArg32 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x47A1D0 sub_47A1D0
// ------------------------------------------------------------
// RB-tree insert-with-hint 节点插入（+49 旗标树；与 sub_473440 同构，
// 旋转/换色经 sub_479140/4791A0，值经 sub_479EF0 构造）
uint32_t */*thiscall*/ sub_47A1D0(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)
{
  uint32_t *fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
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
  uint32_t *fld_e15; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0x71C71C6 )
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
  fld_e1 = sub_479EF0(*(this + 1), (int)pArg4, *(this + 1), nArg5, 0);
  fld_e12 = (uint32_t *)*(this + 1);
  fld_e15 = fld_e1;
  ++*(this + 2);
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);
    if ( pArg4 == (uint32_t *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
  }
  v10 = fld_e1 + 1;
  v11 = (int)fld_e1;
  if ( *(uint8_t *)(fld_e1[1] + 48) == 0 )
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
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 48) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x47A380 sub_47A380
// ------------------------------------------------------------
// 清空全局 map dword_99FC00（整树销毁 + 头节点自环 + 计数清零）
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
// 180 字节条目 erase 收尾：把 pArg3 之后条目前移覆盖（sub_479750），
// 再逐条析构尾部残余（sub_501490）
uint32_t */*thiscall*/ sub_47A3C0(char **this, uint32_t *uArg2, int pArg3)
{
  char *fld_e2; // edi
  char *v5; // esi

  sub_479750((char *)(pArg3 + 180), *(this + 2), (uint32_t *)pArg3);
  fld_e2 = *(this + 2);
  v5 = fld_e2 - 180;
  do
  {
    sub_501490(v5);
    v5 += 180;
  }
  while ( v5 != fld_e2 );
  *(this + 2) -= 180;
  *uArg2 = pArg3;
  return uArg2;
}



// ------------------------------------------------------------
// 0x47A420 sub_47A420
// ------------------------------------------------------------
// 180 字节条目按值填充 n 条并返回尾指针（转发 sub_479F80）
int /*stdcall*/ sub_47A420(int nArg1, int nArg2, uint32_t *uArg3)
{
  sub_479F80(nArg1, nArg2, uArg3);
  return nArg1 + 180 * nArg2;
}



// ------------------------------------------------------------
// 0x47A450 sub_47A450
// ------------------------------------------------------------
// 按名字在 180 字节条目表中查找（strcmp 比对），返回条目地址；未找到
// 返回/插入提示
int /*thiscall*/ sub_47A450(int *this, int pArg2, uint32_t *pArg3)
{
  int fld_e1; // ebx
  uint32_t *fld_e12; // esi
  char v5; // al
  uint32_t *pArg32; // edi
  unsigned int i; // esi
  unsigned int v8; // ecx
  const char *v9; // eax
  unsigned int v10; // edx
  const char *v11; // esi
  int nCmp; // eax
  bool v13; // sf
  unsigned int v14; // esi
  int v15; // eax
  uint32_t *fld_e122; // ebx
  const char *v18; // eax
  uint32_t *v19; // [esp+Ch] [ebp-14h]
  int *pThis; // [esp+18h] [ebp-8h]
  char v21; // [esp+1Ch] [ebp-4h]

  fld_e1 = *(uint32_t *)(*(this + 1) + 4);
  fld_e12 = (uint32_t *)*(this + 1);
  v5 = 1;
  pArg32 = pArg3;
  pThis = this;
  v21 = 1;
  if ( *(uint8_t *)(fld_e1 + 49) == 0 )
  {
    for ( i = pArg3[5]; ; i = pArg3[5] )
    {
      v8 = *(uint32_t *)(fld_e1 + 32);
      v19 = (uint32_t *)fld_e1;
      if ( *(uint32_t *)(fld_e1 + 36) < 0x10u )
        v9 = (const char *)(fld_e1 + 16);
      else
        v9 = *(const char **)(fld_e1 + 16);
      v10 = pArg3[5];
      if ( i < v10 )
        v10 = i;
      if ( v10 == 0 )
        goto LABEL_16;
      if ( v10 < v8 )
        v8 = v10;
      v11 = pArg32[6] < 0x10u ? (const char *)(pArg32 + 1) : (const char *)pArg32[1];
      nCmp = memcmp(v11, v9, v8);
      v13 = nCmp < 0;
      pArg32 = pArg3;
      if ( nCmp == 0 )
      {
LABEL_16:
        v14 = *(uint32_t *)(fld_e1 + 32);
        if ( v10 >= v14 )
          v15 = v10 != v14;
        else
          v15 = -1;
        v13 = v15 < 0;
      }
      v5 = v13;
      v21 = v13;
      fld_e1 = v13 ? *(uint32_t *)fld_e1 : *(uint32_t *)(fld_e1 + 8);
      if ( *(uint8_t *)(fld_e1 + 49) != 0 )
        break;
    }
    fld_e12 = v19;
    this = pThis;
  }
  fld_e122 = fld_e12;
  pArg3 = fld_e12;
  if ( v5 != 0 )
  {
    if ( fld_e12 == *(uint32_t **)*(this + 1) )
    {
      *(uint32_t *)pArg2 = *sub_47A1D0(this, &pArg3, 1, fld_e12, (int)pArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      return pArg2;
    }
    sub_479050(&pArg3);
    fld_e122 = pArg3;
  }
  if ( pArg32[6] < 0x10u )
    v18 = (const char *)(pArg32 + 1);
  else
    v18 = (const char *)pArg32[1];
  if ( sub_40BF00((std::_String_base *)(fld_e122 + 3), 0, fld_e122[8], v18, pArg32[5]) >= 0 )
  {
    *(uint32_t *)pArg2 = fld_e122;
    *(uint8_t *)(pArg2 + 4) = 0;
  }
  else
  {
    *(uint32_t *)pArg2 = *sub_47A1D0(pThis, &pArg3, v21, fld_e12, (int)pArg32);
    *(uint8_t *)(pArg2 + 4) = 1;
  }
  return pArg2;
}



// ------------------------------------------------------------
// 0x47A5B0 sub_47A5B0
// ------------------------------------------------------------
// vector 定点插入（180 字节条目，/180 计数）：原地腾洞或 1.5 倍扩容
// 重建（与 sub_475200 同构）
void /*thiscall*/ sub_47A5B0(int *this, char *pszArg2, unsigned int uArg3, int nArg4)
{
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v14; // edi
  void *fld_e14; // eax
  uint32_t *fld_e23; // ecx
  int fld_e26; // edx
  uint32_t *fld_e12; // [esp-18h] [ebp-F8h]
  uint32_t *fld_e28; // [esp-10h] [ebp-F0h]
  int fld_e25; // [esp-Ch] [ebp-ECh]
  unsigned int fld_e24; // [esp-8h] [ebp-E8h]
  uint32_t v23[4]; // [esp+0h] [ebp-E0h] BYREF
  void *Block; // [esp+10h] [ebp-D0h]
  char *pMem2; // [esp+14h] [ebp-CCh]
  void *v26[47]; // [esp+18h] [ebp-C8h] BYREF
  int v27; // [esp+DCh] [ebp-4h]
  uint32_t *v28; // [esp+E8h] [ebp+8h]
  int v29; // [esp+ECh] [ebp+Ch]

  v26[45] = (void *)dword_796E50;
  v26[46] = v23;
  v23[3] = this;
  sub_4796F0(nArg4);
  fld_e1 = *(this + 1);
  fld_e3 = 0;
  v27 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 180;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - *(this + 1)) / 180;
    else
      fld_e2 = 0;
    if ( 23860929 - fld_e2 < uArg3 )
      sub_479680(this);
    if ( *(this + 1) != 0 )
      fld_e22 = (*(this + 2) - *(this + 1)) / 180;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (uint32_t *)*(this + 2);
      Block = fld_e23;
      if ( ((char *)fld_e23 - pszArg2) / 180 >= uArg3 )
      {
        v28 = &fld_e23[-45 * uArg3];
        *(this + 2) = sub_479CE0(v28, fld_e23, (int)fld_e23);
        sub_479CC0(pszArg2, v28, Block);
        sub_479C40(pszArg2, &pszArg2[180 * uArg3], v26);
      }
      else
      {
        sub_479CE0(pszArg2, fld_e23, (int)&pszArg2[180 * uArg3]);
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 180;
        fld_e25 = *(this + 2);
        LOBYTE(v27) = 3;
        sub_47A420(fld_e25, fld_e24, v26);
        fld_e26 = 180 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v27 = 0;
        sub_479C40(pszArg2, fld_e26 - 180 * uArg3, v26);
      }
    }
    else
    {
      if ( 23860929 - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        fld_e27 = (*(this + 2) - *(this + 1)) / 180;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_478FE0(this);
      v29 = 180 * v10;
      pMem = (char *)operator new(180 * v10);
      fld_e12 = (uint32_t *)*(this + 1);
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v27) = 1;
      pMem2 = (char *)sub_479CE0(fld_e12, pszArg2, (int)pMem);
      sub_479F80((int)pMem2, uArg3, v26);
      fld_e28 = (uint32_t *)*(this + 2);
      pMem2 += 180 * uArg3;
      sub_479CE0(pszArg2, fld_e28, (int)pMem2);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 180;
      v14 = fld_e13 + uArg3;
      fld_e14 = (void *)*(this + 1);
      if ( fld_e14 != nullptr )
      {
        sub_47A090(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v29];
      *(this + 2) = (int)&pMem[180 * v14];
      *(this + 1) = (int)pMem;
    }
  }
  if ( v26[6] >= (void *)0x10 )
    j__free(v26[1]);
}


// ------------------------------------------------------------
// 0x47A930 sub_47A930
// ------------------------------------------------------------
// 按下标删除 180 字节条目（越界直返；经 sub_47A3C0 前移+析构）
unsigned int /*thiscall*/ sub_47A930(unsigned int *this, unsigned int uArg2)
{
  unsigned int result; // eax
  char **pThis_1; // ecx

  result = *(this + 2);
  pThis_1 = (char **)(this + 1);
  if ( result != 0 )
  {
    result = (int)&pThis_1[2][-result] / 180;
    if ( uArg2 < result )
      return (unsigned int)sub_47A3C0(pThis_1, &uArg2, *(this + 2) + 180 * uArg2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x47A980 sub_47A980
// ------------------------------------------------------------
// 按名字删除条目：sub_479290 求下标 → sub_47A930 删除
unsigned int /*thiscall*/ sub_47A980(unsigned int *this, const char *pArg2)
{
  unsigned int v3; // eax

  v3 = sub_479290(this, pArg2);
  return sub_47A930(this, v3);
}



// ------------------------------------------------------------
// 0x47A9B0 sub_47A9B0
// ------------------------------------------------------------
// CNRDFriendManager 构造：vftbl 置位 + 180 字节条目表清空
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
// CNRDBuddyManager 构造：vftbl 置位 + 清条目表（sub_47A0C0）
int /*thiscall*/ sub_47A9D0(uint32_t *this)
{
  *this = &vftbl_CNRDBuddyManager;
  return sub_47A0C0((int)(this + 1));
}



// ------------------------------------------------------------
// 0x47A9E0 sub_47A9E0
// ------------------------------------------------------------
// CNRDGuildManager 构造：vftbl 置位 + 条目表清空 + string 成员
// （+20 SSO cap=15）复位
uint32_t */*thiscall*/ sub_47A9E0(uint32_t *this)
{
  char *pThis_5; // ecx

  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  pThis_5 = (char *)(this + 5);
  *this = &vftbl_CNRDGuildManager;
  *((uint32_t *)pThis_5 + 6) = 15;
  *((uint32_t *)pThis_5 + 5) = 0;
  pThis_5[4] = 0;
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
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
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
// CNRDGuildManager::vmt0 析构前段：IObject vftbl 链 + string 成员/
// 条目表清空
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
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
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
// CNRDMemberManager 构造：vftbl 置位 + 条目表/string 成员复位
uint32_t */*thiscall*/ sub_47AB30(uint32_t *this)
{
  uint32_t *pThis_1C; // edi
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
  pThis_1C = this + 28;
  sub_41A630((unsigned int)(this + 28));
  *pThis_1C = &vftbl_clong;
  sub_41A630((unsigned int)this + 126);
  *(uint32_t *)((char *)this + 126) = &vftbl_clong;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *((uint8_t *)this + 69) = 0;
  *((uint8_t *)this + 70) = 0;
  *((uint8_t *)this + 97) = 0;
  *((uint8_t *)this + 98) = 0;
  sub_41A590((unsigned int)pThis_1C, v3, 0);
  sub_41A590((unsigned int)this + 126, v4, 0);
  return this;
}



// ------------------------------------------------------------
// 0x47AC10 sub_47AC10
// ------------------------------------------------------------
// CNRDMemberManager::vmt0 析构前段：多个子对象（sub_41A580）与
// string 成员清理
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
int /*fastcall*/ CNRDMemberManager__vmtC(int pArg1, int nArg2)
{
  int v3; // edx

  *(uint32_t *)(pArg1 + 48) = 0;
  *(uint32_t *)(pArg1 + 52) = 0;
  *(uint8_t *)(pArg1 + 69) = 0;
  *(uint8_t *)(pArg1 + 70) = 0;
  *(uint8_t *)(pArg1 + 97) = 0;
  *(uint8_t *)(pArg1 + 98) = 0;
  sub_41A590(pArg1 + 112, nArg2, 0);
  sub_41A590(pArg1 + 126, v3, 0);
  return sub_47A0C0(pArg1 + 4);
}



// ------------------------------------------------------------
// 0x47ACF0 sub_47ACF0
// ------------------------------------------------------------
// 成员插入（key 重复检查后经 sub_47A1D0 入树；+8 为空时首插）
uint32_t */*thiscall*/ sub_47ACF0(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // edi
  uint32_t *pArg43; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_47A1D0((int *)this, uArg2, 1, *(uint32_t **)(this + 4), (int)pArg4);
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )
  {
    if ( (uint8_t)sub_40C160(pArg4, pArg3 + 3) != 0 )
    {
      sub_47A1D0((int *)this, uArg2, 1, pArg3, (int)pArg42);
      return uArg2;
    }
    goto LABEL_23;
  }
  if ( pArg3 == fld_4 )
  {
    if ( (uint8_t)sub_40C160(fld_4[2] + 12, pArg4) != 0 )
    {
      sub_47A1D0((int *)this, uArg2, 0, *(uint32_t **)(*(uint32_t *)(this + 4) + 8), (int)pArg42);
      return uArg2;
    }
    goto LABEL_23;
  }
  if ( (uint8_t)sub_40C160(pArg4, pArg3 + 3) != 0 )
  {
    pArg4 = pArg3;
    sub_479050(&pArg4);
    if ( (uint8_t)sub_40C160(pArg4 + 3, pArg42) != 0 )
    {
      if ( *(uint8_t *)(pArg4[2] + 49) != 0 )
        sub_47A1D0((int *)this, uArg2, 0, pArg4, (int)pArg42);
      else
        sub_47A1D0((int *)this, uArg2, 1, pArg3, (int)pArg42);
      return uArg2;
    }
  }
  if ( (uint8_t)sub_40C160(pArg3 + 3, pArg42) == 0 )
    goto LABEL_23;
  pArg4 = pArg3;
  sub_4790B0((int *)&pArg4);
  pArg43 = pArg4;
  if ( pArg4 != *(uint32_t **)(this + 4) )
  {
    if ( (uint8_t)sub_40C160(pArg42, pArg4 + 3) != 0 )
    {
      pArg43 = pArg4;
      goto LABEL_19;
    }
LABEL_23:
    v9 = *(uint32_t *)sub_47A450((int *)this, (int)v10, pArg42);
    *uArg2 = v9;
    return uArg2;
  }
LABEL_19:
  if ( *(uint8_t *)(pArg3[2] + 49) != 0 )
    sub_47A1D0((int *)this, uArg2, 0, pArg3, (int)pArg42);
  else
    sub_47A1D0((int *)this, uArg2, 1, pArg43, (int)pArg42);
  return uArg2;
}



// ------------------------------------------------------------
// 0x47AE90 sub_47AE90
// ------------------------------------------------------------
// 180 字节条目定点插入并返回新条目地址（sub_47A5B0 包装，与
// sub_4705D0 同构）
uint32_t */*thiscall*/ sub_47AE90(int *this, uint32_t *uArg2, char *pszArg3, uint32_t *uArg4)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 180 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 180;
  else
    v6 = 0;
  sub_47A5B0(this, pszArg3, 1u, uArg4);
  *uArg2 = *(this + 1) + 180 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x47AF40 CNRDBuddyManager__vmt0
// ------------------------------------------------------------
// CNRDBuddyManager::vmt0（RTTI 自证）
uint32_t */*thiscall*/ CNRDBuddyManager__vmt0(uint32_t *Block, char pszArg2)
{
  sub_47A9D0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x47AF70 CNRDGuildManager__vmt0
// ------------------------------------------------------------
// CNRDGuildManager::vmt0（RTTI 自证）
void */*thiscall*/ CNRDGuildManager__vmt0(void *Block, char pszArg2)
{
  sub_47AAA0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x47AFA0 CNRDMemberManager__vmt0
// ------------------------------------------------------------
// CNRDMemberManager::vmt0（RTTI 自证）
char */*thiscall*/ CNRDMemberManager__vmt0(char *Block, char pszArg2)
{
  sub_47AC10(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x47AFD0 sub_47AFD0
// ------------------------------------------------------------
// 构造：初始化 +49 旗标树头节点（sub_479200 自环）并清计数
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
// 按条件从 180 字节条目表取条目（组 nArg2 成员列表，拼串/日志辅助）
int */*thiscall*/ sub_47B000(int this, int nArg2)
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

  v2 = (unsigned int *)nArg2;
  v4 = sub_479550((int **)this, nArg2);
  if ( v4 == *(int **)(this + 4)
    || ((unsigned int)v4[9] < 0x10 ? (v5 = (const char *)(v4 + 4)) : (v5 = (const char *)v4[4]),
        sub_40BF00((std::_String_base *)v2, 0, v2[5], v5, v4[8]) < 0) )
  {
    v10 = 15;
    v9 = 0;
    LOBYTE(Block) = 0;
    sub_4014D0((std::_String_base *)&v7, nArg2, 0, -1);
    v11 = 0;
    v12 = 0;
    v13 = 0;
    v4 = (int *)*sub_47ACF0(this, &nArg2, v4, &v7);
    if ( v10 >= 0x10 )
      j__free(Block);
  }
  return v4 + 10;
}



// ------------------------------------------------------------
// 0x47B0C0 sub_47B0C0
// ------------------------------------------------------------
// 尾插一条 180 字节条目（容量够原地构造，不够走 sub_47A5B0 扩容）
uint32_t */*thiscall*/ sub_47B0C0(int this, uint32_t *uArg2)
{
  int fld_4; // ebx
  unsigned int fld_8; // esi
  int fld_82; // esi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 180;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 180 )
    return sub_47AE90((int *)this, &uArg2, *(char **)(this + 8), uArg2);
  fld_82 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_479F80(fld_82, 1, uArg2);
  *(uint32_t *)(this + 8) = fld_82 + 180;
  return result;
}



// ------------------------------------------------------------
// 0x47B150 sub_47B150
// ------------------------------------------------------------
// 添加好友/成员申请（名字 Src）：查对象 dword_8F8500 校验（nArg4<4）
// 后入表【推断：社交添加链】
int /*thiscall*/ sub_47B150(uint32_t *this, char *Src, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int v7; // eax
  uint32_t *v8; // eax
  uint8_t v10[4]; // [esp+Ch] [ebp-C0h] BYREF
  void *Block; // [esp+10h] [ebp-BCh]
  unsigned int v12; // [esp+24h] [ebp-A8h]
  int v13; // [esp+C8h] [ebp-4h]

  if ( Src == nullptr || nArg4 >= 4 )
    return 0;
  v7 = sub_429870((int **)dword_8F8500, Src);
  v8 = (uint32_t *)sub_479DF0((int)v10, Src, nArg3, nArg4, nArg5, nArg6, v7);
  v13 = 0;
  sub_47B0C0((int)(this + 1), v8);
  if ( v12 >= 0x10 )
    j__free(Block);
  return *(this + 3) - 180;
}



// ------------------------------------------------------------
// 0x47B200 sub_47B200
// ------------------------------------------------------------
// 好友上下线广播处理（uArg2=1 上线）：查对象、构造/刷新条目、
// timeGetTime 记时【推断：社交上线链】
int /*cdecl*/ sub_47B200(void *Src, int nArg2)
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
  int dword_796E502; // [esp+4Ch] [ebp-10h]
  int v16; // [esp+58h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v14 = 15;
  v13 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  v16 = 0;
  Time = timeGetTime();
  v2 = *sub_479610(&dword_99FBFC, &v5, &v11);
  if ( v2 == (int *)dword_99FC00 || v2[10] != nArg2 || v2[11] + 2000 <= Time )
  {
    v9 = 15;
    v8 = 0;
    LOBYTE(v7) = 0;
    sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
    LOBYTE(v16) = 1;
    *sub_47B000((int)&dword_99FBFC, (int)v6) = nArg2;
    LOBYTE(v16) = 0;
    if ( v9 >= 0x10 )
      j__free(v7);
    v9 = 15;
    v8 = 0;
    LOBYTE(v7) = 0;
    sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
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
// 好友上线提示：sub_47B200(Src,1) 成功后弹 671 号提示串
int /*cdecl*/ sub_47B380(void *Src, uint8_t uArg2)
{
  int result; // eax
  char *v3; // eax
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int dword_796E502; // [esp+84h] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_47B200(Src, 1);
  if ( result == 1 )
  {
    v3 = sub_422E70(671);
    sprintf(Buffer, v3, Src, uArg2);
    return sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x47B400 sub_47B400
// ------------------------------------------------------------
// 好友下线提示：sub_47B200(Src,0) 成功后弹 670 号提示串
int /*cdecl*/ sub_47B400(void *Src)
{
  int result; // eax
  char *v2; // eax
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int dword_796E502; // [esp+84h] [ebp-4h]

  dword_796E502 = dword_796E50;
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
// 等级差校验：对象 +53 处等级与 pArg1+156 比较（±2 之内才通过）
int /*cdecl*/ sub_47B470(int pArg1)
{
  int v1; // eax
  int v2; // eax
  int v3; // ecx
  int v4; // eax

  v1 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  v2 = sub_41A5E0(v1 + 53);
  v3 = *(uint32_t *)(pArg1 + 156);
  v4 = v2 - v3;
  if ( v4 > 2 || v3 <= 2 )
    return v4 > 4 ? -16599746 : -16525825;
  else
    return -16776961;
}



// ------------------------------------------------------------
// 0x47B4D0 sub_47B4D0
// ------------------------------------------------------------
// 聚合条目区间拷贝（5 dword/条=20 字节，逐字段含 float 读改写）
uint32_t */*cdecl*/ sub_47B4D0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // esi
  uint32_t *uArg32; // edi
  int v5; // eax
  int v6; // edx

  uArg12 = uArg1;
  if ( uArg1 == uArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    *uArg32 = *uArg12;
    v5 = sub_41A5E0((unsigned int)(uArg12 + 1));
    sub_41A590((unsigned int)(uArg32 + 1), v6, v5);
    uArg12 += 5;
    uArg32 += 5;
  }
  while ( uArg12 != uArg2 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x47B510 sub_47B510
// ------------------------------------------------------------
// 20 字节条目区间拷贝变体（与 sub_47B4D0 同族）
uint32_t */*cdecl*/ sub_47B510(int nArg1, int nArg2, uint32_t *uArg3)
{
  int nArg22; // esi
  uint32_t *uArg32; // edi
  int v5; // eax
  int v6; // eax
  int v7; // edx

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    v5 = *(uint32_t *)(nArg22 - 20);
    nArg22 -= 20;
    uArg32 -= 5;
    *uArg32 = v5;
    v6 = sub_41A5E0(nArg22 + 4);
    sub_41A590((unsigned int)(uArg32 + 1), v7, v6);
  }
  while ( nArg22 != nArg1 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x47B560 sub_47B560
// ------------------------------------------------------------
// 上限校验：20 字节条目表 <3 条时弹 464 号提示（成员不足）
int /*thiscall*/ sub_47B560(uint32_t *this, int nArg2)
{
  int fld_e2; // eax
  char *v3; // eax

  fld_e2 = *(this + 2);
  if ( fld_e2 != 0 && (unsigned int)((*(this + 3) - fld_e2) / 20) >= 3 )
  {
    v3 = sub_422E70(464);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);
  }
  else
  {
    sub_423200(dword_8F7B08, 33);  // 【发送网络包API】
    sub_423290(dword_8F7B08, (int)&nArg2, 2);
    return sub_423380(dword_8F7B08);
  }
}



// ------------------------------------------------------------
// 0x47B5E0 sub_47B5E0
// ------------------------------------------------------------
// 20 字节条目区间填充（std::fill 族）：[uArg1,uArg2) 内每条（5 DWORD=20 字节）
// 从 pArg3 模板条目拷贝首 DWORD 并深拷贝其字符串成员（sub_41A5E0/41A590）
uint32_t */*cdecl*/ sub_47B5E0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi
  int v5; // eax
  int v6; // edx

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 5 )
  {
    *i = *pArg3;
    v5 = sub_41A5E0((unsigned int)(pArg3 + 1));
    sub_41A590((unsigned int)(i + 1), v6, v5);
    result = uArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47B620 sub_47B620
// ------------------------------------------------------------
// 转发到 sub_47B510（20 字节条目区间拷贝变体），无自身逻辑
uint32_t */*cdecl*/ sub_47B620(int nArg1, int nArg2, uint32_t *uArg3)
{
  return sub_47B510(nArg1, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x47B640 sub_47B640
// ------------------------------------------------------------
// 20 字节条目未初始化区间复制（uninitialized_copy 族）：把 [pArg1,uArg2) 逐条
// 复制构造到 uArg3 起的裸内存（首 DWORD 拷贝 + clong 子对象构造 + 字符串深拷贝）
uint32_t */*cdecl*/ sub_47B640(uint32_t *pArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // esi
  int v5; // eax
  int v6; // edx
  uint32_t v8[6]; // [esp+0h] [ebp-24h] BYREF
  int v9; // [esp+20h] [ebp-4h]

  uArg32 = uArg3;
  v8[5] = v8;
  v8[4] = uArg3;
  v9 = 0;
  while ( pArg1 != uArg2 )
  {
    LOBYTE(v9) = 1;
    if ( uArg32 != nullptr )
    {
      *uArg32 = *pArg1;
      v8[3] = uArg32 + 1;
      sub_41A630((unsigned int)(uArg32 + 1));
      LOBYTE(v9) = 2;
      uArg32[1] = &vftbl_clong;
      v5 = sub_41A5E0((unsigned int)(pArg1 + 1));
      sub_41A590((unsigned int)(uArg32 + 1), v6, v5);
    }
    uArg32 += 5;
    LOBYTE(v9) = 0;
    pArg1 += 5;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x47B6F0 sub_47B6F0
// ------------------------------------------------------------
// 在 this+6/7 指针表（begin/end）中线性查找首 DWORD==nArg2 的条目：
// 命中返回 1，遍历完返回 0（按 ID 判断条目是否存在的辅助）
char /*thiscall*/ sub_47B6F0(uint32_t *this, int nArg2)
{
  uint32_t **fld_e6; // eax
  uint32_t **fld_e7; // ecx

  fld_e6 = (uint32_t **)*(this + 6);
  fld_e7 = (uint32_t **)*(this + 7);
  if ( fld_e6 == fld_e7 )
    return 0;
  while ( **fld_e6 != nArg2 )
  {
    if ( ++fld_e6 == fld_e7 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x47B720 sub_47B720
// ------------------------------------------------------------
// 条目资格校验：按 uArg2 索引 this+6 指针表取条目（须 +124==nArg3），再遍历
// 20 字节条目表逐条检查：ID 撞车且 sub_463F10 已有实例→返回 0；条目内部
// 指针表 fld[46]/fld[47] 中已含该 ID→返回 0；全部通过返回 1
char /*thiscall*/ sub_47B720(uint32_t *this, unsigned int uArg2, int nArg3)
{
  int fld_e6; // ecx
  unsigned int v5; // edi
  int fld_e2; // eax
  int fld_e22; // eax
  int *fld_e23; // eax
  int v10; // ebx
  uint32_t *fld_e622; // ecx
  uint32_t *v12; // eax
  uint32_t *v13; // ecx
  uint32_t *fld_e62; // [esp+8h] [ebp-4h]
  int i; // [esp+14h] [ebp+8h]
  int fld_e3; // [esp+18h] [ebp+Ch]

  fld_e6 = *(this + 6);
  v5 = 0;
  if ( fld_e6 == 0 )
    return 0;
  if ( (*(this + 7) - fld_e6) >> 2 <= uArg2 )
    return 0;
  fld_e62 = *(uint32_t **)(*(this + 6) + 4 * uArg2);
  if ( fld_e62[31] != nArg3 )
    return 0;
  fld_e2 = *(this + 2);
  if ( fld_e2 != 0 )
    fld_e3 = (*(this + 3) - fld_e2) / 20;
  else
    fld_e3 = 0;
  if ( fld_e3 <= 0 )
    return 1;
  for ( i = 0; ; i += 20 )
  {
    fld_e22 = *(this + 2);
    if ( fld_e22 != 0 && v5 < (*(this + 3) - fld_e22) / 20 )
      fld_e23 = *(int **)(i + *(this + 2));
    else
      fld_e23 = nullptr;
    v10 = *fld_e23;
    fld_e622 = fld_e62;
    if ( *fld_e23 == *fld_e62 )
    {
      if ( sub_463F10(this, v5) != -1 )
        return 0;
      fld_e622 = fld_e62;
    }
    v12 = (uint32_t *)fld_e622[46];
    v13 = (uint32_t *)fld_e622[47];
    if ( v12 != v13 )
      break;
LABEL_20:
    if ( (int)++v5 >= fld_e3 )
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
// 20 字节条目表线性查找首 DWORD==nArg2 的条目（1717986919 魔数=÷20）；
// 命中即发网络包 34（携带 2 字节 ID）——与 0x47B8D0（包 35）/0x47B9E0（包 36）同族
int /*thiscall*/ sub_47B820(uint32_t *this, int nArg2)
{
  int64_t fld_e3; // rax
  int nEntryTotal; // edi  【条目总数（÷20 魔数结果）】
  unsigned int nEntryIdx; // esi  【循环下标】
  int fld_e2; // ebx
  int nByteOfs; // [esp+8h] [ebp-4h]  【条目字节偏移（+=20）】

  LODWORD(fld_e3) = *(this + 2);
  if ( (uint32_t)fld_e3 != 0 )
  {
    fld_e3 = 1717986919LL * (*(this + 3) - (int)fld_e3);
    nEntryTotal = (SHIDWORD(fld_e3) >> 3) + (HIDWORD(fld_e3) >> 31);
  }
  else
  {
    nEntryTotal = 0;
  }
  nEntryIdx = 0;
  if ( nEntryTotal > 0 )
  {
    fld_e2 = *(this + 2);
    nByteOfs = 0;
    do
    {
      if ( fld_e2 != 0 && nEntryIdx < (*(this + 3) - fld_e2) / 20 )
        LODWORD(fld_e3) = *(uint32_t *)(nByteOfs + *(this + 2));
      else
        LODWORD(fld_e3) = 0;
      if ( *(uint32_t *)fld_e3 == nArg2 )
        break;
      ++nEntryIdx;
      nByteOfs += 20;
    }
    while ( (int)nEntryIdx < nEntryTotal );
  }
  if ( nEntryIdx != nEntryTotal )
  {
    sub_423200(dword_8F7B08, 34);  // 【发送网络包API】
    sub_423290(dword_8F7B08, (int)&nArg2, 2);
    LODWORD(fld_e3) = sub_423380(dword_8F7B08);
  }
  return fld_e3;
}



// ------------------------------------------------------------
// 0x47B8D0 sub_47B8D0
// ------------------------------------------------------------
// 同 0x47B820 的条目查找；命中且条目首 DWORD 非零（或旗标 nArg3 非零）时
// 发网络包 35（2 字节 ID + 1 字节开/关旗标）——评估器条件不满足时的"关断"出口
char /*thiscall*/ sub_47B8D0(uint32_t *this, int nArg2, int nArg3)
{
  int64_t fld_e3; // rax
  int nEntryTotal; // edi  【条目总数（÷20 魔数结果）】
  unsigned int nEntryIdx; // esi  【循环下标】
  int fld_e2; // ebx
  int fld_e22; // eax
  int nByteOfs; // [esp+Ch] [ebp-4h]  【条目字节偏移（+=20）】

  LODWORD(fld_e3) = *(this + 2);
  if ( (uint32_t)fld_e3 != 0 )
  {
    fld_e3 = 1717986919LL * (*(this + 3) - (int)fld_e3);
    nEntryTotal = (SHIDWORD(fld_e3) >> 3) + (HIDWORD(fld_e3) >> 31);
  }
  else
  {
    nEntryTotal = 0;
  }
  nEntryIdx = 0;
  if ( nEntryTotal <= 0 )
    goto LABEL_17;
  fld_e2 = *(this + 2);
  nByteOfs = 0;
  while ( 1 )
  {
    LODWORD(fld_e3) = fld_e2 != 0 && nEntryIdx < (*(this + 3) - fld_e2) / 20 ? *(uint32_t *)(nByteOfs + *(this + 2)) : 0;
    if ( *(uint32_t *)fld_e3 == nArg2 )
      break;
    ++nEntryIdx;
    nByteOfs += 20;
    if ( (int)nEntryIdx >= nEntryTotal )
      goto LABEL_17;
  }
  if ( (fld_e22 = *(this + 2)) != 0
    && nEntryIdx < (*(this + 3) - fld_e22) / 20
    && (LODWORD(fld_e3) = *(this + 2) + 20 * nEntryIdx, *(uint32_t *)fld_e3 != 0)
    || (LOBYTE(fld_e3) = nArg3, (uint8_t)nArg3 != 0) )
  {
LABEL_17:
    if ( nEntryIdx != nEntryTotal )
    {
      sub_423200(dword_8F7B08, 35);  // 【发送网络包API】
      sub_423290(dword_8F7B08, (int)&nArg2, 2);
      HIBYTE(nArg3) = (uint8_t)nArg3 != 0;
      sub_423290(dword_8F7B08, (int)&nArg3 + 3, 1);
      LOBYTE(fld_e3) = sub_423380(dword_8F7B08);
    }
  }
  return fld_e3;
}



// ============================================================
// 【分区 10】触发条件评估器（0x47B9E0-0x47C2F0）
// 评估器 0x47BBE0：八类条件 case 0-7（0=计时器 / 2=比例% / 3=加载进度 sub_477260×100/
// sub_43B5C0 / 4=旗标 / 5=座位比对 / 6=恒真 / 7=进度值）——不满足即 sub_47B8D0 关断。
// ============================================================
// ------------------------------------------------------------
// 0x47B9E0 sub_47B9E0
// ------------------------------------------------------------
// 查找首 DWORD==nArg2 的 20 字节条目；命中且 sub_463F10 实例数为 0 时
// 发网络包 36（2 字节 ID）——0x47B820/0x47B8D0 同族的第三个发包变体
int /*thiscall*/ sub_47B9E0(uint32_t *this, int nArg2)
{
  int64_t fld_e3; // rax
  int nEntryTotal; // edi  【条目总数（÷20 魔数结果）】
  unsigned int nEntryIdx; // esi  【循环下标】
  int fld_e2; // ebx
  int nByteOfs; // [esp+Ch] [ebp-4h]  【条目字节偏移（+=20）】

  LODWORD(fld_e3) = *(this + 2);
  if ( (uint32_t)fld_e3 != 0 )
  {
    fld_e3 = 1717986919LL * (*(this + 3) - (int)fld_e3);
    nEntryTotal = (SHIDWORD(fld_e3) >> 3) + (HIDWORD(fld_e3) >> 31);
  }
  else
  {
    nEntryTotal = 0;
  }
  nEntryIdx = 0;
  if ( nEntryTotal <= 0 )
    goto LABEL_14;
  fld_e2 = *(this + 2);
  nByteOfs = 0;
  while ( 1 )
  {
    LODWORD(fld_e3) = fld_e2 != 0 && nEntryIdx < (*(this + 3) - fld_e2) / 20 ? *(uint32_t *)(nByteOfs + *(this + 2)) : 0;
    if ( *(uint32_t *)fld_e3 == nArg2 )
      break;
    ++nEntryIdx;
    nByteOfs += 20;
    if ( (int)nEntryIdx >= nEntryTotal )
      goto LABEL_14;
  }
  LODWORD(fld_e3) = sub_463F10(this, nEntryIdx);
  if ( (uint32_t)fld_e3 == 0 )
  {
LABEL_14:
    if ( nEntryIdx != nEntryTotal )
    {
      sub_423200(dword_8F7B08, 36);  // 【发送网络包API】
      sub_423290(dword_8F7B08, (int)&nArg2, 2);
      LODWORD(fld_e3) = sub_423380(dword_8F7B08);
    }
  }
  return fld_e3;
}



// ------------------------------------------------------------
// 0x47BAA0 sub_47BAA0
// ------------------------------------------------------------
// 开/关对账（0x47CD00/0x47D060 的联动收尾）：遍历 20 字节条目表，型别
// (+272)==5 的条目经 sub_429830 场景对象 + sub_463F10 实例数判定：需求值
// (**(+284)) 大于当前值(场景+116) 且无实例→sub_47B8D0(ID,1) 开启一次；
// 否则按实例数逐个 sub_47B8D0(ID,0) 关断
unsigned int /*thiscall*/ sub_47BAA0(unsigned int *this)
{
  unsigned int v1; // edi
  unsigned int result; // eax
  int fld_e2; // eax
  int fld_e22; // ebx
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
    fld_e2 = *(this + 2);
    if ( fld_e2 != 0 && v1 < (int)(*(this + 3) - fld_e2) / 20 )
    {
      fld_e22 = *(uint32_t *)(*(this + 2) + v7);
      v8 = (int *)fld_e22;
    }
    else
    {
      v8 = nullptr;
      fld_e22 = 0;
    }
    if ( *(uint32_t *)(fld_e22 + 272) == 5
      && sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0
      && sub_463F10(this, v1) != -1 )
    {
      if ( *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 116) < **(uint32_t **)(fld_e22 + 284) )
      {
        if ( sub_463F10(this, v1) == 0 )
          sub_47B8D0(this, *(uint32_t *)fld_e22, 1);
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
// 触发条件评估器：遍历条件对象（+68 表，20 字节/项），按条目[69] 型别：
// 0=计时器（dword_8F8520 vt+120 时钟 +164）/ 1=|Y| 阈值（dword_99FD58+948）/
// 2=百分比（+906/+920 ×100）/ 3=加载进度（sub_477260×100/sub_43B5C0）/
// 4=旗标（+120 非零）/ 5=座位号比对 sub_456390 / 6=恒真 / 7=进度值 sub_495C80；
// 不满足 → sub_47B8D0(对象, 0) 关断
int /*thiscall*/ sub_47BBE0(int *this, int nArg2, int nArg3)
{
  int result; // eax
  unsigned int nEntryIdx; // esi  【条件条目循环下标】
  int nCountRecheck; // edx  【(end-begin)/20 条目数（÷20 魔数 1717986919 的结果）】
  int fld_e2; // eax
  int fld_e3; // ecx
  uint32_t *pEntry; // edi  【当前条目指针（原 fld_e22：*(this+2)+偏移 处的表项）】
  uint32_t *pCondParam; // esi  【条目[71]：条件参数块（[0]=目标ID [1]=子ID(-1=通配) [2]=阈值）】
  int nSubId; // eax  【参数[1]：子 ID（-1=通配）】
  int nCondType; // eax  【条目[69]：条件型别 0-7】
  int nClockHost; // eax  【vt+120 取得的时钟宿主对象】
  int *pThreshold; // esi  【&参数[2]（条目[71]+8）】
  uint64_t nCurValue; // rax  【当前值（百分比/进度）】
  int nThreshold; // ecx  【阈值（参数[2]）】
  bool bReached; // cc  【当前值≥阈值（达到即关断）】
  int nFlagHost; // eax  【vt+120 取得的旗标宿主对象】
  float fLoadPct; // [esp+8h] [ebp-14h]  【加载进度×100（case 3）】
  float fCurVal; // [esp+Ch] [ebp-10h]  【+906 当前值（case 2 分子）】
  int nEntryTotal; // [esp+10h] [ebp-Ch]  【条目总数快照】
  int nByteOfs; // [esp+14h] [ebp-8h]  【条目字节偏移（每次 +=20）】
  unsigned int nEntryIdxSaved; // [esp+18h] [ebp-4h]  【下标保存（跨调用恢复）】

  result = *(this + 2);
  nEntryIdx = 0;
  if ( result != 0 )
  {
    result = (*(this + 3) - result) / 20;
    nEntryTotal = result;
  }
  else
  {
    nEntryTotal = 0;
  }
  nEntryIdxSaved = 0;
  if ( nEntryTotal > 0 )
  {
    for ( nByteOfs = 0; ; nByteOfs += 20 )
    {
      if ( (int)sub_463F10(nEntryIdx) <= 0 )
        goto LABEL_38;
      fld_e2 = *(this + 2);
      if ( fld_e2 != 0
        && (fld_e3 = *(this + 3) - fld_e2, nCountRecheck = (int)((uint64_t)(1717986919LL * fld_e3) >> 32) >> 3, nEntryIdx < fld_e3 / 20) )
      {
        pEntry = *(uint32_t **)(*(this + 2) + nByteOfs);
      }
      else
      {
        pEntry = nullptr;
      }
      if ( pEntry[68] != 1 )
        goto LABEL_38;
      pCondParam = (uint32_t *)pEntry[71];
      if ( nArg2 != *pCondParam )
        goto LABEL_37;
      nSubId = pCondParam[1];
      if ( nSubId != -1 && nArg3 != nSubId )
        goto LABEL_37;
      nCondType = pEntry[69];
      switch ( nCondType )
      {
        case 0:
          nClockHost = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
          pThreshold = (int *)(pEntry[71] + 8);
          if ( sub_699000(nClockHost + 164) / 1000 <= *pThreshold )  // 【clock_now(clk)】
            goto LABEL_36;
          goto LABEL_37;
        case 1:
          if ( (double)*(int *)(pEntry[71] + 8) >= fabs(COERCE_FLOAT(sub_41A5E0((unsigned int)dword_99FD58 + 948))) )
            goto LABEL_36;
          goto LABEL_37;
        case 2:
          fCurVal = COERCE_FLOAT(sub_41A5E0((unsigned int)dword_99FD58 + 906));
          nCurValue = (uint64_t)(fCurVal / COERCE_FLOAT(sub_41A5E0((unsigned int)dword_99FD58 + 920)) * 100.0);
          nThreshold = *(uint32_t *)(pEntry[71] + 8);
          goto LABEL_34;
        default:
          break;
      }
      if ( nCondType == 3 )
        break;
      switch ( nCondType )
      {
        case 4:
          nFlagHost = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
          if ( sub_41A5E0(nFlagHost + 120) == 0 )
            goto LABEL_36;
          break;
        case 5:
          if ( sub_456390(0) == pCondParam[2] )
            goto LABEL_36;
          break;
        case 6:
          goto LABEL_36;
        case 7:
          LODWORD(nCurValue) = sub_495C80(dword_99FD58);
          nThreshold = pCondParam[2];
LABEL_34:
          bReached = (int)nCurValue < nThreshold;
LABEL_35:
          if ( !bReached )
LABEL_36:
            sub_47B8D0(*pEntry, 0);
          break;
        default:
          break;
      }
LABEL_37:
      nEntryIdx = nEntryIdxSaved;
LABEL_38:
      result = nEntryTotal;
      nEntryIdxSaved = ++nEntryIdx;
      if ( (int)nEntryIdx >= nEntryTotal )
        return result;
    }
    fLoadPct = sub_477260(dword_99FD58, nCountRecheck) * 100.0;
    bReached = (int)(uint64_t)(fLoadPct / sub_43B5C0(dword_99FD58)) < *(uint32_t *)(pEntry[71] + 8);
    goto LABEL_35;
  }
  return result;
}


// ------------------------------------------------------------
// 0x47BE30 sub_47BE30
// ------------------------------------------------------------
// 批量关断：遍历 20 字节条件条目表，型别(+272)==3 且参数头(**(+284))==nArg2
// 的条目逐个 sub_47B8D0(ID,0) 关断（评估器条件组的按型别清除）
char /*thiscall*/ sub_47BE30(uint32_t *this, int nArg2)
{
  int64_t fld_e3; // rax
  int v4; // ebx
  unsigned int v5; // edi
  int fld_e2; // eax
  int v8; // [esp+Ch] [ebp-4h]

  LODWORD(fld_e3) = *(this + 2);
  if ( (uint32_t)fld_e3 != 0 )
  {
    fld_e3 = 1717986919LL * (*(this + 3) - (int)fld_e3);
    v4 = (SHIDWORD(fld_e3) >> 3) + (HIDWORD(fld_e3) >> 31);
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
      LODWORD(fld_e3) = sub_463F10(this, v5);
      if ( (int)fld_e3 > 0 )
      {
        fld_e2 = *(this + 2);
        if ( fld_e2 != 0 && v5 < (*(this + 3) - fld_e2) / 20 )
          LODWORD(fld_e3) = *(uint32_t *)(v8 + *(this + 2));
        else
          LODWORD(fld_e3) = 0;
        if ( *(uint32_t *)(fld_e3 + 272) == 3 && nArg2 == **(uint32_t **)(fld_e3 + 284) )
          LOBYTE(fld_e3) = sub_47B8D0(this, *(uint32_t *)fld_e3, 0);
      }
      ++v5;
      v8 += 20;
    }
    while ( (int)v5 < v4 );
  }
  return fld_e3;
}



// ------------------------------------------------------------
// 0x47BEE0 sub_47BEE0
// ------------------------------------------------------------
// 批量关断：型别(+272)==2 且参数三元组(+284) 与 (nArg2,nArg3,nArg4) 全等
// （-1=通配）的条目逐个 sub_47B8D0(ID,0) 关断
char /*thiscall*/ sub_47BEE0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int64_t fld_e3; // rax
  int v6; // ebx
  unsigned int v7; // edi
  int fld_e2; // eax
  uint32_t *v9; // ecx
  int v11; // [esp+Ch] [ebp-4h]

  LODWORD(fld_e3) = *(this + 2);
  if ( (uint32_t)fld_e3 != 0 )
  {
    fld_e3 = 1717986919LL * (*(this + 3) - (int)fld_e3);
    v6 = (SHIDWORD(fld_e3) >> 3) + (HIDWORD(fld_e3) >> 31);
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
      LODWORD(fld_e3) = sub_463F10(this, v7);
      if ( (int)fld_e3 > 0 )
      {
        fld_e2 = *(this + 2);
        if ( fld_e2 != 0 && v7 < (*(this + 3) - fld_e2) / 20 )
          LODWORD(fld_e3) = *(uint32_t *)(v11 + *(this + 2));
        else
          LODWORD(fld_e3) = 0;
        if ( *(uint32_t *)(fld_e3 + 272) == 2 )
        {
          v9 = *(uint32_t **)(fld_e3 + 284);
          if ( (*v9 == -1 || nArg2 == *v9) && (v9[1] == -1 || nArg3 == v9[1]) && nArg4 == v9[2] )
            LOBYTE(fld_e3) = sub_47B8D0(this, *(uint32_t *)fld_e3, 0);
        }
      }
      ++v7;
      v11 += 20;
    }
    while ( (int)v7 < v6 );
  }
  return fld_e3;
}



// ------------------------------------------------------------
// 0x47BFB0 sub_47BFB0
// ------------------------------------------------------------
// 批量关断：型别(+272)==4 且参数头(**(+284))==nArg2 的条目逐个 sub_47B8D0(ID,0)；
// 任一被关断条目的 +128==nArg2 时返回 1（命中旗标）
char /*thiscall*/ sub_47BFB0(uint32_t *this, int nArg2)
{
  int fld_e2; // eax
  unsigned int v4; // ebx
  int fld_e22; // eax
  int fld_e23; // esi
  int fld_e3; // [esp+8h] [ebp-Ch]
  int v9; // [esp+Ch] [ebp-8h]
  char v10; // [esp+13h] [ebp-1h]

  fld_e2 = *(this + 2);
  v4 = 0;
  v10 = 0;
  if ( fld_e2 != 0 )
    fld_e3 = (*(this + 3) - fld_e2) / 20;
  else
    fld_e3 = 0;
  if ( fld_e3 > 0 )
  {
    v9 = 0;
    do
    {
      if ( sub_463F10(this, v4) > 0 )
      {
        fld_e22 = *(this + 2);
        if ( fld_e22 != 0 && v4 < (*(this + 3) - fld_e22) / 20 )
          fld_e23 = *(uint32_t *)(*(this + 2) + v9);
        else
          fld_e23 = 0;
        if ( *(uint32_t *)(fld_e23 + 272) == 4 && nArg2 == **(uint32_t **)(fld_e23 + 284) )
        {
          sub_47B8D0(this, *(uint32_t *)fld_e23, 0);
          if ( *(uint32_t *)(fld_e23 + 128) == nArg2 )
            v10 = 1;
        }
      }
      ++v4;
      v9 += 20;
    }
    while ( (int)v4 < fld_e3 );
  }
  return v10;
}



// ------------------------------------------------------------
// 0x47C080 sub_47C080
// ------------------------------------------------------------
// 在 20 字节条目表中线性查找首 DWORD==nArg2 的条目：命中返回 1（纯存在性查询，无发包）
char /*thiscall*/ sub_47C080(uint32_t *this, int nArg2)
{
  int fld_e2; // edi
  unsigned int v3; // esi
  int v4; // ebx

  fld_e2 = *(this + 2);
  v3 = 0;
  v4 = 0;
  while ( fld_e2 != 0 && v3 < (*(this + 3) - fld_e2) / 20 )
  {
    if ( **(uint32_t **)(v4 + *(this + 2)) == nArg2 )
      return 1;
    ++v3;
    v4 += 20;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x47C0E0 sub_47C0E0
// ------------------------------------------------------------
// std::map equal_range：在 this+1 红黑树（节点 +21=nil 旗标、+12=键值、
// +8/+0=右/左子）中对键 *uArg3 求下界/上界，pair 写入 pArg2 后返回
uint32_t */*thiscall*/ sub_47C0E0(uint32_t *this, uint32_t *pArg2, uint32_t *uArg3)
{
  int *fld_e1; // edx
  int *v4; // eax
  int *fld_e12; // ecx
  int *v6; // eax

  fld_e1 = (int *)*(this + 1);
  v4 = (int *)fld_e1[1];
  while ( *((uint8_t *)v4 + 21) == 0 )
  {
    if ( *uArg3 >= v4[3] )
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
    if ( v6[3] >= *uArg3 )
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
// 0x47C150 sub_47C150
// ------------------------------------------------------------
// 20 字节条目未初始化填充 n 条（uninitialized_fill_n 族）：从 pArg3 模板逐条
// 构造到 uArg1 起的裸内存（clong 子对象构造 + 字符串深拷贝，同 0x47B640）
int /*cdecl*/ sub_47C150(uint32_t *uArg1, int nArg2, uint32_t *pArg3)
{
  uint32_t *uArg12; // esi
  int result; // eax
  int v5; // eax
  int v6; // edx
  uint32_t v7[7]; // [esp+0h] [ebp-28h] BYREF
  int v8; // [esp+24h] [ebp-4h]

  uArg12 = uArg1;
  v7[6] = v7;
  v7[5] = uArg1;
  v8 = 0;
  while ( 1 )
  {
    result = nArg2;
    if ( nArg2 == 0 )
      break;
    v7[4] = uArg12;
    LOBYTE(v8) = 1;
    if ( uArg12 != nullptr )
    {
      *uArg12 = *pArg3;
      v7[3] = uArg12 + 1;
      sub_41A630((unsigned int)(uArg12 + 1));
      LOBYTE(v8) = 2;
      uArg12[1] = &vftbl_clong;
      v5 = sub_41A5E0((unsigned int)(pArg3 + 1));
      sub_41A590((unsigned int)(uArg12 + 1), v6, v5);
    }
    uArg12 += 5;
    LOBYTE(v8) = 0;
    --nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47C210 sub_47C210
// ------------------------------------------------------------
// 条件对象状态→资源号映射：+120 旗标非零→30；否则 +116==2→27、非零→28、
// 零→41，交给 sub_418DD0 取对应资源【推断：提示文案/音效编号】
int /*cdecl*/ sub_47C210(int pArg1)
{
  int v1; // eax
  int v2; // eax

  if ( *(uint8_t *)(pArg1 + 120) != 0 )
  {
    v1 = 30;
  }
  else
  {
    v2 = *(uint32_t *)(pArg1 + 116);
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
// 填充 nArg2 条（转发 0x47C150）并返回末条目之后的指针（vector 插入辅助三件套之一）
uint32_t */*stdcall*/ sub_47C260(uint32_t *pArg1, int nArg2, uint32_t *uArg3)
{
  sub_47C150(pArg1, nArg2, uArg3);
  return &pArg1[5 * nArg2];
}



// ------------------------------------------------------------
// 0x47C290 sub_47C290
// ------------------------------------------------------------
// 弹出末条目（vector::pop_back 变体）：先经 sub_47B4D0 复制末条目内容到
// pArg3 区，再 sub_433350 析构之，end(this+2) 回退 20 字节（5 DWORD）
uint32_t */*thiscall*/ sub_47C290(uint32_t **this, uint32_t *uArg2, uint32_t *pArg3)
{
  int fld_e2; // edi
  int v5; // esi

  sub_47B4D0(pArg3 + 5, *(this + 2), pArg3);
  fld_e2 = (int)*(this + 2);
  v5 = fld_e2 - 20;
  do
  {
    sub_433350(v5);
    v5 += 20;
  }
  while ( v5 != fld_e2 );
  *(this + 2) -= 5;
  *uArg2 = pArg3;
  return uArg2;
}



// ============================================================
// 【分区 11】物品/封印数据处理（0x47C2F0-0x47E720）
// 44 字节/条目的批量数据处理；SEAL_ON/SEAL_OFF 事件（0x47E000 附近）【推断】。
// ============================================================
// ------------------------------------------------------------
// 0x47C2F0 sub_47C2F0
// ------------------------------------------------------------
// DWORD vector 定点插入（vector::insert）：this+4/8/12 = begin/end/capEnd
// （4 字节/元素），把 [uArg3,uArg4) 插到 Src 之前；容量不够时 operator new
// 扩容重建（0x3FFFFFFF = 32 位内 4 字节/元素的最大个数）
unsigned int /*thiscall*/ sub_47C2F0(int this, uint32_t *Src, uint32_t *uArg3, uint32_t *uArg4, int nArg5)
{
  int fld_4; // edx
  unsigned int v7; // ecx
  unsigned int result; // eax
  int fld_8; // edi
  int fld_82; // edi
  unsigned int v11; // eax
  int fld_86; // edi
  int fld_87; // eax
  char *pMem; // ebx
  size_t fld_42; // edi
  char *v16; // eax
  uint32_t *v17; // eax
  int fld_44; // ecx
  int fld_88; // eax
  unsigned int v20; // edi
  int fld_83; // ebx
  uint32_t *fld_84; // ebx
  const void *fld_43; // [esp-Ch] [ebp-34h]
  uint32_t *fld_85; // [esp-Ch] [ebp-34h]
  int v26; // [esp+0h] [ebp-28h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v28; // [esp+10h] [ebp-18h]
  unsigned int v29; // [esp+14h] [ebp-14h]
  int *v30; // [esp+18h] [ebp-10h]
  int v31; // [esp+24h] [ebp-4h]
  int Srca; // [esp+30h] [ebp+8h]
  void *Srcb; // [esp+30h] [ebp+8h]

  fld_4 = *(uint32_t *)(this + 4);
  v7 = uArg4 - uArg3;
  v30 = &v26;
  v29 = v7;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;
  else
    result = 0;
  if ( v7 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < v7 )
      sub_434730(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( result >= v7 + fld_82 )
    {
      fld_83 = *(uint32_t *)(this + 8);
      if ( (fld_83 - (int)Src) >> 2 >= v7 )
      {
        Srcb = (void *)(fld_83 - 4 * v7);
        *(uint32_t *)(this + 8) = sub_55E7F0(Srcb, fld_83, *(void **)(this + 8));
        sub_5DAF70(Src, (int)Srcb, fld_83);
        return (unsigned int)sub_6511B0(uArg3, uArg4, Src);
      }
      else
      {
        Srca = 4 * v7;
        sub_55E7F0(Src, fld_83, &Src[v7]);
        fld_84 = &uArg3[(*(uint32_t *)(this + 8) - (int)Src) >> 2];
        fld_85 = *(uint32_t **)(this + 8);
        v31 = 2;
        sub_497E70(fld_84, uArg4, fld_85);
        *(uint32_t *)(this + 8) += Srca;
        return (unsigned int)sub_6511B0(uArg3, fld_84, Src);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v11 = (result >> 1) + result;
      else
        v11 = 0;
      if ( fld_4 != 0 )
        fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
      else
        fld_86 = 0;
      if ( v11 < v7 + fld_86 )
      {
        if ( fld_4 != 0 )
          fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
        else
          fld_87 = 0;
        v11 = v7 + fld_87;
      }
      v28 = 4 * v11;
      pMem = (char *)operator new(4 * v11);
      fld_42 = 4 * (((int)Src - *(uint32_t *)(this + 4)) >> 2);
      fld_43 = *(const void **)(this + 4);
      Block = pMem;
      v31 = 0;
      v16 = (char *)memcpy_0(pMem, fld_43, fld_42);
      v17 = sub_497E70(uArg3, uArg4, &v16[fld_42]);
      memcpy_0(v17, Src, 4 * ((*(uint32_t *)(this + 8) - (int)Src) >> 2));
      fld_44 = *(uint32_t *)(this + 4);
      if ( fld_44 != 0 )
        fld_88 = (*(uint32_t *)(this + 8) - fld_44) >> 2;
      else
        fld_88 = 0;
      v20 = fld_88 + v29;
      if ( fld_44 != 0 )
        j__free(*(void **)(this + 4));
      result = (unsigned int)&pMem[v28];
      *(uint32_t *)(this + 12) = &pMem[v28];
      *(uint32_t *)(this + 8) = &pMem[4 * v20];
      *(uint32_t *)(this + 4) = pMem;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x47C540 sub_47C540
// ------------------------------------------------------------
// 在 20 字节条目表（this+8/12）中按首 DWORD==nArg2 查找，找到则经 0x47C290
// 弹出该条目并返回其内容指针（找不到返回 nullptr）
uint32_t */*thiscall*/ sub_47C540(int this, int nArg2)
{
  uint32_t *fld_8; // eax
  uint32_t *fld_C; // edx
  uint32_t *v4; // esi

  fld_8 = *(uint32_t **)(this + 8);
  fld_C = *(uint32_t **)(this + 12);
  if ( fld_8 == fld_C )
    return nullptr;
  while ( 1 )
  {
    v4 = (uint32_t *)*fld_8;
    if ( *(uint32_t *)*fld_8 == nArg2 )
      break;
    fld_8 += 5;
    if ( fld_8 == fld_C )
      return nullptr;
  }
  sub_47C290((uint32_t **)(this + 4), &nArg2, fld_8);
  return v4;
}



// ------------------------------------------------------------
// 0x47C580 sub_47C580
// ------------------------------------------------------------
// std::map 按键删除：equal_range（0x47C0E0）取上下界，逐节点（sub_41C5E0
// 后继）推进统计条数后区间删除（sub_41D980）；返回删除的条数
int /*thiscall*/ sub_47C580(uint32_t *this, uint32_t *uArg2)
{
  uint32_t *v2; // eax
  uint32_t *v3; // edi
  int v4; // esi
  uint32_t *v6; // [esp+Ch] [ebp-8h] BYREF
  uint32_t *v7; // [esp+10h] [ebp-4h]

  sub_47C0E0(this, &v6, uArg2);
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
  sub_41D980(&uArg2, v2, v3);
  return v4;
}



// ------------------------------------------------------------
// 0x47C5E0 sub_47C5E0
// ------------------------------------------------------------
// 20 字节条目 vector 定点插入 uArg3 条（新条目值由 pDwArg4 构造：首 DWORD +
// 字符串 sub_46B080）；原地路径用 0x47B640/0x47B620/0x47B5E0 腾挪填充，
// 容量不足时 1.5 倍扩容重建（214748364 = 32 位内 20 字节/条的最大条数）
int /*thiscall*/ sub_47C5E0(int *this, char *pszArg2, unsigned int uArg3, int *pDwArg4)
{
  int v5; // ecx
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v11; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v15; // edi
  int fld_e14; // eax
  char *fld_e23; // ecx
  int fld_e26; // edi
  uint32_t *fld_e12; // [esp-18h] [ebp-50h]
  int fld_e25; // [esp-Ch] [ebp-44h]
  unsigned int fld_e24; // [esp-8h] [ebp-40h]
  int v24; // [esp+0h] [ebp-38h] BYREF
  int v25; // [esp+Ch] [ebp-2Ch] BYREF
  void *v26[7]; // [esp+10h] [ebp-28h] BYREF
  int v27; // [esp+34h] [ebp-4h]
  char *v28; // [esp+40h] [ebp+8h]
  uint32_t *v29; // [esp+44h] [ebp+Ch]
  int v30; // [esp+48h] [ebp+10h]
  char *fld_e232; // [esp+48h] [ebp+10h]

  v5 = *pDwArg4;
  v26[6] = &v24;
  v25 = v5;
  v26[5] = this;
  sub_46B080(v26, (unsigned int)(pDwArg4 + 1));
  fld_e1 = *(this + 1);
  fld_e3 = 0;
  v27 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 20;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 20;
    else
      fld_e2 = 0;
    if ( 214748364 - fld_e2 < uArg3 )
      sub_434730(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 20;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (char *)*(this + 2);
      fld_e232 = fld_e23;
      if ( (fld_e23 - pszArg2) / 20 >= uArg3 )
      {
        v28 = &fld_e23[-20 * uArg3];
        *(this + 2) = (int)sub_47B640(v28, fld_e23, fld_e23);
        sub_47B620(pszArg2, v28, fld_e232);
        sub_47B5E0(pszArg2, &pszArg2[20 * uArg3], &v25);
      }
      else
      {
        sub_47B640(pszArg2, fld_e23, &pszArg2[20 * uArg3]);
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 20;
        fld_e25 = *(this + 2);
        LOBYTE(v27) = 3;
        sub_47C260(fld_e25, fld_e24, &v25);
        fld_e26 = 20 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v27 = 0;
        sub_47B5E0(pszArg2, fld_e26 - 20 * uArg3, &v25);
      }
    }
    else
    {
      if ( 214748364 - (fld_e3 >> 1) >= fld_e3 )
        v11 = (fld_e3 >> 1) + fld_e3;
      else
        v11 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 20;
      else
        fld_e27 = 0;
      if ( v11 < uArg3 + fld_e27 )
        v11 = uArg3 + sub_45E580(this);
      v30 = 20 * v11;
      pMem = (char *)operator new(20 * v11);
      fld_e12 = (uint32_t *)*(this + 1);
      v26[4] = pMem;
      LOBYTE(v27) = 1;
      v29 = sub_47B640(fld_e12, pszArg2, pMem);
      sub_47C150(v29, uArg3, &v25);
      sub_47B640(pszArg2, (uint32_t *)*(this + 2), &v29[5 * uArg3]);
      fld_e13 = *(this + 1);
      v27 = 0;
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 20;
      v15 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);
      if ( fld_e14 != 0 )
      {
        sub_434180(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v30];
      *(this + 2) = (int)&pMem[20 * v15];
      *(this + 1) = (int)pMem;
    }
  }
  v27 = -1;
  return sub_41A580(v26);
}


// ------------------------------------------------------------
// 0x47C8F0 sub_47C8F0
// ------------------------------------------------------------
// 在 20 字节条目表（pArg1+8/12）中按首 DWORD==nArg3 查找并改写其字符串成员
// （+4，sub_41A590）；nArg4==0 时弹 463 号提示（条件 sub_546080）、置条目
// 对象 +320 旗标，对象 +204 有挂接 ID 时从管理器 map 删除并刷新 sub_45C400
int /*fastcall*/ sub_47C8F0(int pArg1, int nArg2, int nArg3, int nArg4)
{
  int pObj; // esi
  int v5; // ecx
  int nArg32; // ebx
  int nArg42; // edi
  uint32_t *v9; // edi
  char *v10; // eax
  int v11; // edi

  pObj = *(uint32_t *)(pArg1 + 8);
  v5 = *(uint32_t *)(pArg1 + 12);
  if ( pObj == v5 )
    return 0;
  nArg32 = nArg3;
  while ( **(uint32_t **)pObj != nArg3 )
  {
    pObj += 20;
    if ( pObj == v5 )
      return 0;
  }
  nArg42 = nArg4;
  sub_41A590(pObj + 4, nArg2, nArg4);
  if ( nArg42 == 0 )
  {
    if ( (uint8_t)sub_546080(nArg32) == 0 )
    {
      v9 = *((uint32_t **)dword_8F8528 + 7);
      v10 = sub_422E70(463);
      sub_43BEE0(v9, (int)v10, -6567706, 0, -1);
    }
    *(uint8_t *)(*(uint32_t *)pObj + 320) = 1;
    if ( *(uint32_t *)(*(uint32_t *)pObj + 204) != -1 )
    {
      v11 = *(uint32_t *)(dword_8F7A24 + 20);
      nArg3 = *(uint32_t *)(*(uint32_t *)pObj + 204);
      sub_47C580((uint32_t *)(v11 + 88), &nArg3);
      sub_45C400((int **)v11);
    }
  }
  return *(uint32_t *)pObj;
}



// ------------------------------------------------------------
// 0x47C9A0 sub_47C9A0
// ------------------------------------------------------------
// DWORD vector 赋值（operator= 简版）：按源元素数预留容量（sub_4349E0）
// 后整段 memcpy 拷入（this+1 = begin）
uint32_t */*thiscall*/ sub_47C9A0(uint32_t *this, int pArg2)
{
  int v3; // ecx
  unsigned int v4; // eax
  int v6; // [esp-14h] [ebp-34h]
  int v7; // [esp-10h] [ebp-30h]
  int fld_e1; // [esp-Ch] [ebp-2Ch]
  int v9; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+1Ch] [ebp-4h]

  v3 = *(uint32_t *)(pArg2 + 4);
  v11 = &v9;
  pThis = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2;
  else
    v4 = 0;
  if ( sub_4349E0(this, v4) != 0 )
  {
    fld_e1 = *(this + 1);
    v7 = *(uint32_t *)(pArg2 + 8);
    v6 = *(uint32_t *)(pArg2 + 4);
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x47CA40 sub_47CA40
// ------------------------------------------------------------
// DWORD vector 赋值（operator= 完整版）：空源→清空自身并 free；元素数足够→
// 原地 memcpy；不足但容量够→尾部搬迁（sub_433A30/sub_55E7F0）；
// 容量也不够→free 旧块后扩容重建（sub_4349E0）
int /*thiscall*/ sub_47CA40(int this, int pArg2)
{
  int v3; // ecx
  unsigned int v4; // edx
  void *fld_4; // ecx
  unsigned int fld_8; // ebx
  int v8; // eax
  int fld_42; // ecx
  unsigned int fld_C; // eax
  int fld_82; // eax
  void *v12; // ebx
  int v13; // ecx
  unsigned int v14; // eax

  if ( this == pArg2 )
    return this;
  v3 = *(uint32_t *)(pArg2 + 4);
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  fld_4 = *(void **)(this + 4);
  if ( fld_4 != nullptr )
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 2;
  else
    fld_8 = 0;
  if ( v4 <= fld_8 )
  {
    memcpy_0(fld_4, *(const void **)(pArg2 + 4), 4 * ((*(uint32_t *)(pArg2 + 8) - *(uint32_t *)(pArg2 + 4)) >> 2));
    v8 = *(uint32_t *)(pArg2 + 4);
    if ( v8 != 0 )
      fld_42 = *(uint32_t *)(this + 4) + 4 * ((*(uint32_t *)(pArg2 + 8) - v8) >> 2);
    else
      fld_42 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = fld_42;
    return this;
  }
  if ( fld_4 != nullptr )
    fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) >> 2;
  else
    fld_C = 0;
  if ( v4 > fld_C )
  {
    if ( fld_4 != nullptr )
      j__free(*(void **)(this + 4));
    v13 = *(uint32_t *)(pArg2 + 4);
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(pArg2 + 8) - v13) >> 2;
    else
      v14 = 0;
    if ( sub_4349E0((uint32_t *)this, v14) != 0 )
      *(uint32_t *)(this + 8) = sub_55E7F0(*(void **)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(void **)(this + 4));
    return this;
  }
  if ( fld_4 != nullptr )
    fld_82 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 2;
  else
    fld_82 = 0;
  v12 = (void *)(*(uint32_t *)(pArg2 + 4) + 4 * fld_82);
  sub_433A30(*(void **)(pArg2 + 4), (int)v12, *(void **)(this + 4));
  *(uint32_t *)(this + 8) = sub_55E7F0(v12, *(uint32_t *)(pArg2 + 8), *(void **)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x47CB90 sub_47CB90
// ------------------------------------------------------------
// 20 字节条目表在 pszArg3 落点插入一条（值由 pDwArg4 构造），经 0x47C5E0
// 插入后返回新条目地址（0x4705D0 频道表版的 20 字节同类）
uint32_t */*thiscall*/ sub_47CB90(int *this, uint32_t *uArg2, char *pszArg3, int *pDwArg4)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 20 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 20;
  else
    v6 = 0;
  sub_47C5E0(this, pszArg3, 1u, pDwArg4);
  *uArg2 = *(this + 1) + 20 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x47CC00 sub_47CC00
// ------------------------------------------------------------
// 对象清空辅助：清 +4 起的 DWORD vector（sub_4349A0）并 free +24；再把
// +40 与 +52 两个容器头清空并回链自环（空树/空链表形态）
uint32_t */*thiscall*/ sub_47CC00(int this)
{
  uint32_t *fld_28; // eax
  uint32_t *result; // eax

  sub_4349A0((int *)(this + 4));
  if ( *(uint32_t *)(this + 24) != 0 )
    j__free(*(void **)(this + 24));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  sub_435BA0(*(void ***)(*(uint32_t *)(this + 40) + 4));
  *(uint32_t *)(*(uint32_t *)(this + 40) + 4) = *(uint32_t *)(this + 40);
  fld_28 = *(uint32_t **)(this + 40);
  *(uint32_t *)(this + 44) = 0;
  *fld_28 = fld_28;
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
// 从映射容器（this+9 → sub_45B6D0 按键 nArg3 查找）取值：命中则经 0x47C9A0
// 把 DWORD vector 拷出到 uArg2，未命中则拷出空 vector
uint32_t */*thiscall*/ sub_47CC80(int **this, uint32_t *uArg2, int nArg3)
{
  int *v5; // [esp-4h] [ebp-2Ch]
  char v6; // [esp+8h] [ebp-20h] BYREF
  int v7; // [esp+Ch] [ebp-1Ch]
  int v8; // [esp+10h] [ebp-18h]
  int v9; // [esp+14h] [ebp-14h]
  int *v10[4]; // [esp+18h] [ebp-10h] BYREF

  v10[0] = nullptr;
  sub_45B6D0(this + 9, v10, &nArg3);
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
  sub_47C9A0(uArg2, (int)v5);
  return uArg2;
}



// ------------------------------------------------------------
// 0x47CD00 sub_47CD00
// ------------------------------------------------------------
// 逐条处理型别 fld[68]==0 的条件条目：为已注册（sub_463F10 != -1）者建空红黑
// 树（sub_433AC0），收集 fld[71]/[72] 的 8 字节对（半数，sub_4682D0）；再对
// dword_8F852C 列表与 dword_8F7C04 的 18 个槽（vt+792）扣减计数（节点[4] 减
// vt+44 值，不够则 sub_41D610 摘除）；余量>0 → sub_47B8D0(ID,1) 开启，否则
// 按实例数逐个 sub_47B8D0(ID,0) 关断，最后从 map 摘除【推断：条件达成结算】
unsigned int /*thiscall*/ sub_47CD00(uint32_t *this)
{
  uint32_t *pThis; // esi
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
  uint32_t *dword_8F852C2; // eax
  int v13; // ebx
  int v14; // ecx
  int pObj2; // esi
  uint32_t *v16; // edi
  int pObj; // ecx
  int v18; // ebx
  int pObj3; // eax
  int pObj4; // esi
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
  int dword_8F7C042; // [esp+28h] [ebp-28h] BYREF
  uint32_t *v32; // [esp+2Ch] [ebp-24h] BYREF
  int v33; // [esp+30h] [ebp-20h] BYREF
  int i; // [esp+34h] [ebp-1Ch]
  unsigned int v35; // [esp+38h] [ebp-18h]
  uint32_t *pThis2; // [esp+3Ch] [ebp-14h]
  uint32_t *v37; // [esp+40h] [ebp-10h]
  int v38; // [esp+4Ch] [ebp-4h]

  pThis = this;
  v2 = 0;
  pThis2 = this;
  for ( i = 0; ; i += 20 )
  {
    result = pThis[2];
    v35 = v2;
    if ( result == 0 )
      break;
    result = (int)(pThis[3] - result) / 20;
    if ( v2 >= result )
      break;
    v4 = pThis[2];
    if ( v4 != 0 && v2 < (pThis[3] - v4) / 20 )
    {
      v5 = *(uint32_t **)(i + pThis[2]);
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
      dword_8F852C2 = dword_8F852C;
      v13 = 0;
      dword_8F7C042 = *((uint32_t *)dword_8F852C + 2);
      if ( dword_8F7C042 > 0 )
      {
        while ( 1 )
        {
          if ( v13 < dword_8F852C2[2] )
          {
            v14 = dword_8F852C2[3];
            pObj2 = *(uint32_t *)(v14 + 4 * v13);
            if ( pObj2 != 0 )
            {
              v33 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj2 + 16))(*(uint32_t *)(v14 + 4 * v13)) + 4);
              sub_472E30(&v32, &v33);
              v16 = v32;
              if ( v32 != Block )
              {
                if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2) < v16[4] )
                  v16[4] -= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2);
                else
                  sub_41D610(&v33, v16);
              }
            }
          }
          if ( ++v13 >= dword_8F7C042 )
            break;
          dword_8F852C2 = dword_8F852C;
        }
      }
      pObj = dword_8F7C04;
      dword_8F7C042 = dword_8F7C04;
      v18 = 0;
      while ( 1 )
      {
        pObj3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 792))(pObj, v18);
        pObj4 = pObj3;
        if ( pObj3 != 0 )
        {
          v33 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 16))(pObj3) + 4);
          sub_472E30(&v29, &v33);
          v21 = v29;
          if ( v29 != Block )
          {
            if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 44))(pObj4) < v21[4] )
              v21[4] -= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 44))(pObj4);
            else
              sub_41D610(&v33, v21);
          }
        }
        if ( ++v18 >= 18 )
          break;
        pObj = dword_8F7C042;
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
      sub_41D980(&dword_8F7C042, v24, Block);
      j__free(Block);
      v2 = v35;
      pThis = pThis2;
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
// 20 字节条目表 push_back：容量够→在 end 处构造 1 条（sub_47C150）并推进
// end(+20 字节)；满了→经 0x47CB90/0x47C5E0 扩容插入
uint32_t */*thiscall*/ sub_47CFD0(int this, int *pDwArg2)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 20;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 20 )
    return sub_47CB90((int *)this, &pDwArg2, *(char **)(this + 8), pDwArg2);
  fld_82 = *(uint32_t **)(this + 8);
  result = (uint32_t *)sub_47C150(fld_82, 1, pDwArg2);
  *(uint32_t *)(this + 8) = fld_82 + 5;
  return result;
}



// ------------------------------------------------------------
// 0x47D060 sub_47D060
// ------------------------------------------------------------
// 登记条件条目：表满 3 条 / sub_4CE8A0 解析失败 / 已存在 → 返回 0；否则构造
// {ID, clong 串} 压表（0x47CFD0），nArg3==0 时置对象 +320 旗标，随后
// 经 0x47CD00 重算 + 0x47BAA0 对账开关；nArg3!=0 且对象 +204 有效时写入管理器
// map（dword_8F7A24+20 → +22）并 sub_45C400 刷新；返回对象指针
int /*thiscall*/ sub_47D060(unsigned int *this, uint32_t *uArg2, int nArg3)
{
  int fld_e2; // eax
  int pThis_1; // edi
  int v7; // ebx
  uint32_t *fld_e22; // eax
  uint32_t *fld_e3; // esi
  int nArg32; // esi
  int v11; // edx
  int v12; // eax
  int v13; // edx
  unsigned int *pThis2; // edi
  int **v15; // esi
  uint32_t *uArg22; // edi
  int v17; // [esp+8h] [ebp-34h] BYREF
  uint32_t v18[4]; // [esp+Ch] [ebp-30h] BYREF
  uint32_t v19[3]; // [esp+1Eh] [ebp-1Eh] BYREF
  unsigned int *pThis; // [esp+2Ch] [ebp-10h]
  int v21; // [esp+38h] [ebp-4h]

  fld_e2 = *(this + 2);
  pThis_1 = (int)(this + 1);
  pThis = this;
  if ( fld_e2 != 0 && (unsigned int)((int)(*(this + 3) - fld_e2) / 20) >= 3 )
    return 0;
  v7 = sub_4CE8A0(uArg2);
  if ( v7 == 0 )
    return 0;
  fld_e22 = (uint32_t *)*(this + 2);
  fld_e3 = (uint32_t *)*(this + 3);
  if ( fld_e22 != fld_e3 )
  {
    while ( *fld_e22 != v7 )
    {
      fld_e22 += 5;
      if ( fld_e22 == fld_e3 )
        goto LABEL_9;
    }
    return 0;
  }
LABEL_9:
  sub_41A630((unsigned int)v19);
  nArg32 = nArg3;
  v21 = 0;
  v19[0] = &vftbl_clong;
  sub_41A590((unsigned int)v19, v11, nArg3);
  v21 = 1;
  v17 = v7;
  uArg2 = v18;
  sub_41A630((unsigned int)v18);
  LOBYTE(v21) = 2;
  v18[0] = &vftbl_clong;
  v12 = sub_41A5E0((unsigned int)v19);
  sub_41A590((unsigned int)v18, v13, v12);
  LOBYTE(v21) = 3;
  sub_47CFD0(pThis_1, &v17);
  LOBYTE(v21) = 1;
  sub_41A580(v18);
  v21 = -1;
  sub_41A580(v19);
  if ( nArg32 == 0 )
    *(uint8_t *)(v7 + 320) = 1;
  pThis2 = pThis;
  sub_47CD00(pThis);
  sub_47BAA0(pThis2);
  if ( *(uint32_t *)(v7 + 204) != -1 && nArg32 != 0 )
  {
    v15 = *(int ***)(dword_8F7A24 + 20);
    uArg2 = *(uint32_t **)(v7 + 204);
    uArg22 = uArg2;
    *(uint32_t *)sub_468BA0(v15 + 22, (int *)&uArg2) = uArg22;
    sub_45C400(v15);
  }
  return v7;
}



// ------------------------------------------------------------
// 0x47D1E0 sub_47D1E0
// ------------------------------------------------------------
// 按 ID uArg2 注销：sub_4CE8A0 解析出对象后经 sub_44E2F0 从表 this+5 移除
// （0x47D060 的反向操作）；对象不存在返回 0
unsigned int /*thiscall*/ sub_47D1E0(int *this, unsigned int uArg2)
{
  unsigned int result; // eax

  result = sub_4CE8A0(uArg2);
  uArg2 = result;
  if ( result != 0 )
    return sub_44E2F0(this + 5, (int *)&uArg2);
  return result;
}



// ------------------------------------------------------------
// 0x47D210 sub_47D210
// ------------------------------------------------------------
// 把通过 0x47B720 资格校验的指针表条目按 +116 型别分拣进 3 个 16 字节桶
// （eh vector 构造），三桶范围依序经 0x47C2F0 汇入一个 DWORD vector 后由
// sub_47C9A0 拷出到 uArg2【推断：按型别分组的条目汇总表】
uint32_t */*thiscall*/ sub_47D210(uint32_t *this, uint32_t *uArg2, int nArg3)
{
  signed int v3; // esi
  int fld_e6; // eax
  int fld_e62; // edi
  int v7; // eax
  uint8_t *v8; // ecx
  unsigned int v9; // esi
  int *fld_e623; // eax
  int *v11; // esi
  int i; // edi
  uint8_t v14[36]; // [esp+Ch] [ebp-5Ch] BYREF
  char v15; // [esp+30h] [ebp-38h] BYREF
  uint8_t v16[4]; // [esp+3Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+40h] [ebp-28h]
  void *Src; // [esp+44h] [ebp-24h]
  int v19; // [esp+48h] [ebp-20h]
  int v20; // [esp+4Ch] [ebp-1Ch]
  int fld_e622; // [esp+50h] [ebp-18h] BYREF
  int fld_e7; // [esp+54h] [ebp-14h]
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
  return uArg2;
}



// ------------------------------------------------------------
// 0x47D370 sub_47D370
// ------------------------------------------------------------
// 红黑树节点构造（operator new 0x24=36 字节）：填 3 个 DWORD + 经 0x47C9A0
// 拷入一个 DWORD vector 载荷；+32=红黑旗标(pszArg5)、+33=nil 旗标=0；
// 返回新节点
uint32_t */*stdcall*/ sub_47D370(int nArg1, int nArg2, int nArg3, uint32_t *pArg4, char pszArg5)
{
  uint32_t *pMem; // eax
  uint32_t *pMem2; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  pMem = operator new(0x24u);
  pMem2 = pMem;
  v8[4] = pMem;
  v8[8] = (void *)1;
  v8[3] = pMem;
  if ( pMem != nullptr )
  {
    *pMem = nArg1;
    pMem[1] = nArg2;
    pMem[2] = nArg3;
    pMem[3] = *pArg4;
    sub_47C9A0(pMem + 4, (int)(pArg4 + 1));
    *((uint8_t *)pMem2 + 32) = pszArg5;
    *((uint8_t *)pMem2 + 33) = 0;
  }
  return pMem2;
}



// ------------------------------------------------------------
// 0x47D410 sub_47D410
// ------------------------------------------------------------
// 红黑树节点深拷贝（_Copy_nodes）：经 0x47D370 复制 pDwArg2 节点（含 vector
// 载荷），递归克隆左/右子（+0/+8），父指针=nArg3；源节点为 nil(+33) 时直接返回
void */*thiscall*/ sub_47D410(void **this, int *pDwArg2, int nArg3)
{
  char v3; // al
  uint32_t *fld_e1; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);
  v3 = *((uint8_t *)pDwArg2 + 33);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    fld_e1 = sub_47D370((int)*(this + 1), nArg3, (int)*(this + 1), pDwArg2 + 3, *((uint8_t *)pDwArg2 + 32));
    if ( *((uint8_t *)Block + 33) != 0 )
      Block = fld_e1;
    v6 = *pDwArg2;
    v10 = 0;
    *fld_e1 = sub_47D410(v6, fld_e1);
    fld_e1[2] = sub_47D410(pDwArg2[2], fld_e1);
  }
  return Block;
}



// ------------------------------------------------------------
// 0x47D4C0 sub_47D4C0
// ------------------------------------------------------------
// std::map 红黑树插入（带父节点提示）：节点数超 0xCCCCCCB 抛 length_error
// （"map/set<T> too long"）；经 0x47D370 建节点并按 pszArg3 挂到 pArg4 左/右，
// 随后红黑着色修正（旋转 sub_4331B0/sub_433230），根置黑；新节点写入 uArg2
uint32_t */*thiscall*/ sub_47D4C0(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, uint32_t *uArg5)
{
  uint32_t *fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
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
  uint32_t *fld_e15; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0xCCCCCCB )
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
  fld_e1 = sub_47D370(*(this + 1), (int)pArg4, *(this + 1), uArg5, 0);
  fld_e12 = (uint32_t *)*(this + 1);
  fld_e15 = fld_e1;
  ++*(this + 2);
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);
    if ( pArg4 == (uint32_t *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
  }
  v10 = fld_e1 + 1;
  v11 = (int)fld_e1;
  if ( *(uint8_t *)(fld_e1[1] + 32) == 0 )
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
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 32) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x47D670 sub_47D670
// ------------------------------------------------------------
// std::map 树整体克隆（operator= 核心）：从 pArg2 的树递归克隆节点挂到
// this+4 头节点下，拷贝元素数(+8)，再重算头节点的最左/最右指针（begin/end）
int */*thiscall*/ sub_47D670(int this, int pArg2)
{
  int fld_4; // edi
  int **fld_42; // edx
  int *result; // eax
  int *v6; // ecx
  int fld_43; // esi
  int **v8; // ecx

  fld_4 = *(uint32_t *)(this + 4);
  *(uint32_t *)(fld_4 + 4) = sub_47D410((void **)this, *(int **)(*(uint32_t *)(pArg2 + 4) + 4), fld_4);
  *(uint32_t *)(this + 8) = *(uint32_t *)(pArg2 + 8);
  fld_42 = *(int ***)(this + 4);
  result = fld_42[1];
  if ( *((uint8_t *)result + 33) != 0 )
  {
    *fld_42 = (int *)fld_42;
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
    *fld_42 = result;
    fld_43 = *(uint32_t *)(this + 4);
    v8 = *(int ***)(fld_43 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 33) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(fld_43 + 8) = v8;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47D700 sub_47D700
// ------------------------------------------------------------
// std::map 键值插入（insert(value) 语义）：沿树按 uArg3 键值下行定位
// （节点 +12=键），已存在→{节点,false}；否则经 0x47D4C0 插入→{新节点,true}；
// 结果 pair 写入 pArg2
int /*thiscall*/ sub_47D700(int *this, int pArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // ebx
  uint32_t *fld_e1; // esi
  int *v6; // eax
  bool v7; // cl
  int v8; // edx
  uint32_t *fld_e12; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  uArg32 = uArg3;
  fld_e1 = (uint32_t *)*(this + 1);
  v6 = (int *)fld_e1[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 33) == 0 )
  {
    v8 = *uArg3;
    do
    {
      v7 = v8 < v6[3];
      fld_e1 = v6;
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 33) == 0 );
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_47D4C0(this, &uArg3, 1, fld_e1, uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_45B1F0(&uArg3);
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else
  {
    v12 = *sub_47D4C0(this, &uArg3, v13, fld_e1, uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x47D7C0 sub_47D7C0
// ------------------------------------------------------------
// std::map 带提示插入（insert(hint, value)）：pArg3=提示节点，先校验新键
// pArg4 是否恰好落在提示前/后（前驱 sub_45B1F0 / 后继 sub_41C640）；提示
// 失效则回落 0x47D700 常规插入；新节点写入 uArg2
uint32_t */*thiscall*/ sub_47D7C0(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_47D4C0((int *)this, uArg2, 1, *(uint32_t **)(this + 4), pArg4);
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_47D4C0((int *)this, uArg2, 1, pArg3, pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_4 )
  {
    v8 = (uint32_t *)fld_4[2];
    if ( v8[3] < *pArg4 )
    {
      sub_47D4C0((int *)this, uArg2, 0, v8, pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_45B1F0(&pArg4), pArg4[3] >= *pArg42) )
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_41C640(&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_47D700((int *)this, (int)v10, pArg42);
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 33) != 0 )
      sub_47D4C0((int *)this, uArg2, 0, pArg3, pArg42);
    else
      sub_47D4C0((int *)this, uArg2, 1, pArg4, pArg42);
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 33) != 0 )
      sub_47D4C0((int *)this, uArg2, 0, pArg4, pArg42);
    else
      sub_47D4C0((int *)this, uArg2, 1, pArg3, pArg42);
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x47D920 sub_47D920
// ------------------------------------------------------------
// std::map operator[]：按键 *pDwArg2 下行定位；不存在则构造默认值（空 vector
// + 键）经 0x47D7C0 插入；返回节点载荷（节点+16 起的 DWORD vector 头）
uint32_t */*thiscall*/ sub_47D920(uint32_t *this, int *pDwArg2)
{
  uint32_t *fld_e1; // ecx
  int *v4; // eax
  uint32_t *fld_e12; // esi
  int v7; // [esp+Ch] [ebp-30h] BYREF
  int v8; // [esp+10h] [ebp-2Ch] BYREF
  void *Block; // [esp+14h] [ebp-28h]
  uint8_t v10[4]; // [esp+20h] [ebp-1Ch] BYREF
  int v11; // [esp+24h] [ebp-18h]
  int v12; // [esp+28h] [ebp-14h]
  int v13; // [esp+2Ch] [ebp-10h]
  int v14; // [esp+38h] [ebp-4h]

  fld_e1 = (uint32_t *)*(this + 1);
  v4 = (int *)fld_e1[1];
  fld_e12 = fld_e1;
  while ( *((uint8_t *)v4 + 33) == 0 )
  {
    if ( v4[3] >= *pDwArg2 )
    {
      fld_e12 = v4;
      v4 = (int *)*v4;
    }
    else
    {
      v4 = (int *)v4[2];
    }
  }
  if ( fld_e12 == (uint32_t *)*(this + 1) || *pDwArg2 < fld_e12[3] )
  {
    v11 = 0;
    v12 = 0;
    v13 = 0;
    v7 = *pDwArg2;
    v14 = 0;
    sub_47C9A0(&v8, (int)v10);
    LOBYTE(v14) = 1;
    fld_e12 = (uint32_t *)*sub_47D7C0((int)this, &pDwArg2, fld_e12, &v7);
    if ( Block != nullptr )
      j__free(Block);
  }
  return fld_e12 + 4;
}



// ------------------------------------------------------------
// 0x47D9D0 sub_47D9D0
// ------------------------------------------------------------
// 条件旗标重算（+320 开/关）：遍历 this[6]/[7] 指针表，按条目 +124 键经
// 经 0x47D210 分桶汇总建临时 map（0x47D920 写入）；再中序遍历之，对每组成员
// 置 +320 =（型别+116==2 或旗标 +120 非零），已登记于 this[10] map 的键则
// 跳过其 vector(+20/+24) 已含的成员；最后把临时 map 克隆回 this+9 成员 map
void /*thiscall*/ sub_47D9D0(uint32_t *this)
{
  uint32_t *pThis; // ebx
  int pObj; // esi
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
  uint32_t *pThis2; // [esp+2Ch] [ebp-14h]
  int v30; // [esp+30h] [ebp-10h] BYREF
  int i; // [esp+3Ch] [ebp-4h]

  pThis = this;
  pThis2 = this;
  v26 = (void *)sub_433B40(v25);
  *((uint8_t *)v26 + 33) = 1;
  *((uint32_t *)v26 + 1) = v26;
  *(uint32_t *)v26 = v26;
  *((uint32_t *)v26 + 2) = v26;
  v27 = 0;
  pObj = pThis[6];
  for ( i = 0; pObj != pThis[7]; pObj += 4 )
  {
    v3 = *(uint32_t *)(*(uint32_t *)pObj + 124);
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
  for ( j = *(int **)v26; j != v26; pThis = pThis2 )
  {
    v30 = j[3];
    sub_45B6D0(&v28, &v30);
    v6 = pThis[10];
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
  if ( pThis + 9 != (uint32_t *)v25 )
  {
    sub_437990(&v28, *(uint32_t *)pThis[10], pThis[10]);
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
// 对象字段重置（恢复构造态）：清 +135 字段；重置两个间隔 14 字节的 clong 串
// （this+124 元素起）；再依次写入 float 1.0f（1065353216=IEEE 位型）与 5 个零值字段
int /*thiscall*/ sub_47DC00(uint32_t *this)
{
  uint32_t *pThis_7C; // esi
  int i; // ebx

  *(this + 135) = 0;
  pThis_7C = this + 124;
  for ( i = 2; i != 0; --i )
  {
    sub_41A590(0);
    pThis_7C = (uint32_t *)((char *)pThis_7C + 14);
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
// 薄分发：取当前场景对象（dword_8F8500 按地图 word_77F804 查）的 +44，
// 转调 0x47E720(句柄, nArg1)
int /*cdecl*/ sub_47DC90(int nArg1)
{
  int v1; // eax

  v1 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  return sub_47E720(*(uint32_t *)(v1 + 44), nArg1);
}



// ------------------------------------------------------------
// 0x47DCD0 sub_47DCD0
// ------------------------------------------------------------
// 经 nArg2 对象 vt+80 取其 +132 资源，调 sub_424120(资源, this+114, 档位)；
// nArg3==-1 时用 this+115 作档位（资源播放/设置辅助）
int /*thiscall*/ sub_47DCD0(int *this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_e115; // edi
  int v6; // eax

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 80))(nArg2);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 80))(nArg2);
    if ( *(uint32_t *)(result + 132) != 0 )
    {
      fld_e115 = nArg3;
      if ( nArg3 == -1 )
        fld_e115 = *(this + 115);
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 80))(nArg2);
      return sub_424120(*(uint32_t **)(v6 + 132), *(this + 114), fld_e115);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x47DD30 sub_47DD30
// ------------------------------------------------------------
// 复位变体（0x47DD30）：对 nArg1 对象 vt+80 资源的 +132 调 sub_424120(资源, 0, 0)
int /*stdcall*/ sub_47DD30(int nArg1)
{
  int result; // eax
  int v2; // eax

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 80))(nArg1);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 80))(nArg1);
    if ( *(uint32_t *)(result + 132) != 0 )
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 80))(nArg1);
      return sub_424120(*(uint32_t **)(v2 + 132), 0, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x47DD70 sub_47DD70
// ------------------------------------------------------------
// 14 字节条目 vector 计数 getter（this+1/2 = begin/end，条目 0x0E=14 字节）
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
// 14 字节条目区间填充：[uArg1,nArg2) 每条从 uArg3 模板深拷贝
// （sub_41A5E0/41A590 字符串族）
void /*cdecl*/ sub_47DDA0(unsigned int uArg1, int nArg2, unsigned int uArg3)
{
  unsigned int i; // esi
  int v4; // eax
  int v5; // edx

  for ( i = uArg1; i != nArg2; i += 14 )
  {
    v4 = sub_41A5E0(uArg3);
    sub_41A590(i, v5, v4);
  }
}



// ------------------------------------------------------------
// 0x47DDD0 sub_47DDD0
// ------------------------------------------------------------
// 12 字节（3 DWORD）条目区间平搬拷贝：[uArg1,uArg2) → uArg3 起，逐条 3 DWORD
uint32_t */*cdecl*/ sub_47DDD0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax
  uint32_t *v5; // edi
  int v6; // esi

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; v5[2] = v6 )
  {
    v5 = result;
    *result = *uArg12;
    result[1] = uArg12[1];
    v6 = uArg12[2];
    uArg12 += 3;
    result += 3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47DE10 sub_47DE10
// ------------------------------------------------------------
// 14 字节条目区间正向拷贝：[uArg1,nArg2) 逐条深拷贝（字符串族）到 uArg3
unsigned int /*cdecl*/ sub_47DE10(unsigned int uArg1, int nArg2, unsigned int uArg3)
{
  unsigned int uArg12; // esi
  unsigned int uArg32; // edi
  int v5; // eax
  int v6; // edx

  uArg12 = uArg1;
  if ( uArg1 == nArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    v5 = sub_41A5E0(uArg12);
    sub_41A590(uArg32, v6, v5);
    uArg12 += 14;
    uArg32 += 14;
  }
  while ( uArg12 != nArg2 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x47DE50 sub_47DE50
// ------------------------------------------------------------
// 14 字节条目区间反向拷贝（自 nArg2 向 nArg1 回退）到 uArg3
// （源/目标区间重叠时的 backward 变体）
unsigned int /*cdecl*/ sub_47DE50(int nArg1, unsigned int uArg2, unsigned int uArg3)
{
  unsigned int uArg22; // esi
  unsigned int uArg32; // edi
  int v5; // eax
  int v6; // edx

  uArg22 = uArg2;
  if ( nArg1 == uArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    uArg22 -= 14;
    uArg32 -= 14;
    v5 = sub_41A5E0(uArg22);
    sub_41A590(uArg32, v6, v5);
  }
  while ( uArg22 != nArg1 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x47DE90 sub_47DE90
// ------------------------------------------------------------
// 取第 nArg2 条的地址：基址 this+64 + (nArg2-1) × 条目大小（this+78 处的值）
int /*thiscall*/ sub_47DE90(void *this, int nArg2)
{
  int pThis_40; // edi

  pThis_40 = sub_41A5E0((unsigned int)this + 64);
  return pThis_40 + (nArg2 - 1) * sub_41A5E0((unsigned int)this + 78);
}



// ------------------------------------------------------------
// 0x47DEC0 sub_47DEC0
// ------------------------------------------------------------
// 写第 nArg2 条的 clong 串（sub_41A590 赋值）：地址 = this + 14×nArg2 + 496
int /*thiscall*/ sub_47DEC0(void *this, int nArg2, int nArg3)
{
  return sub_41A590((unsigned int)this + 14 * nArg2 + 496, 14 * nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x47DEE0 sub_47DEE0
// ------------------------------------------------------------
// 写 this+524 的 float（经 clong setter）：nArg2<=0 写 0，否则写 nArg2
int /*thiscall*/ sub_47DEE0(void *this, int nArg2)
{
  if ( *(float *)&nArg2 <= 0.0 )
    return sub_41A590((unsigned int)this + 524, 0, 0);
  else
    return sub_41A590((unsigned int)this + 524, nArg2, nArg2);
}



// ------------------------------------------------------------
// 0x47DF30 sub_47DF30
// ------------------------------------------------------------
// 开关状态 getter：this+544 值非零返回 TRUE
BOOL /*thiscall*/ sub_47DF30(void *this)
{
  return sub_41A5E0((unsigned int)this + 544) != 0;
}



// ------------------------------------------------------------
// 0x47DF50 sub_47DF50
// ------------------------------------------------------------
// 状态条/资源框绘制（一串 vt+152 绘制调用）：闪烁门控（this+147 时钟<1500ms
// 且 pszArg8 时按 250ms 周期 0xFA 奇偶跳绘）；依次绘制 this[95]/[96]（nArg5
// 选择）、dword_99FC08[档]（超限时档=3，否则 1/2）、数值 sub_69A110、+558
// 附框 dword_99FC28；nArg5==2 额外经 dword_9B0C5C vt+128 传一组 float 位型
// 参数；pszArg7 时按 this+630 剩余时间画倒计时
void /*thiscall*/ sub_47DF50(uint32_t *this, int pArg2, int nArg3, int Value, int nArg5, char pszArg6, char pszArg7, char pszArg8)
{
  int pThis_7C; // eax
  int pThis_93; // ecx
  int v11; // edx
  int pObj; // ecx
  int fld_e31; // edi
  int pThis_7C2; // edi
  int pObj2; // ecx
  int pThis_276; // edi
  int pThis_9A; // esi
  int v18; // eax

  if ( pszArg8 != 0 && sub_699000((int)(this + 147)) < 1500 )  // 【clock_now(clk)】
  {
    pThis_7C = sub_41A5E0((unsigned int)(this + 124));
    pThis_93 = (int)(this + 147);
    if ( pThis_7C == 1 )
    {
      if ( ((sub_699000(pThis_93) / 0xFAu) & 1) != 0 )  // 【clock_now(clk)】
        return;
    }
    else if ( ((sub_699000(pThis_93) / 0xFAu) & 1) == 0 )  // 【clock_now(clk)】
    {
      return;
    }
  }
  if ( sub_41A5E0((unsigned int)(this + 143)) != 0 && pszArg6 == 0 )
  {
    if ( *((uint32_t *)dword_8F8528 + 626) == 1 && *((uint32_t *)dword_8F8528 + 628) == sub_41A5E0((unsigned int)(this + 1)) )
      return;
    sub_41A590((unsigned int)(this + 143), v11, 0);
  }
  pObj = *(this + (nArg5 == 1) + 95);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, pArg2, nArg3, dword_79C0B0);
  fld_e31 = 0;
  if ( nArg5 != 1 )
  {
    if ( Value == -1 )
    {
      pThis_7C2 = sub_41A5E0((unsigned int)(this + 124));
      if ( pThis_7C2 < sub_41A5E0((unsigned int)this + 510) )
      {
        fld_e31 = 3;
LABEL_20:
        Value = sub_41A5E0((unsigned int)this + 510);
        goto LABEL_21;
      }
    }
    fld_e31 = (*(this + 31) != 0) + 1;
  }
  if ( Value == -1 )
    goto LABEL_20;
LABEL_21:
  pObj2 = dword_99FC08[fld_e31];
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, pArg2 + 10, nArg3, dword_79C0B0);
  sub_69A110(pArg2 + 28, nArg3, Value, -1);
  if ( sub_41A5E0((unsigned int)this + 558) != 0 && dword_99FC28 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_99FC28 + 152))(dword_99FC28, pArg2, nArg3, dword_79C0B0);
  if ( nArg5 == 2 && dword_9B0C5C != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)dword_9B0C5C + 128))(
      dword_9B0C5C,
      pArg2,
      nArg3,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      1308622847,
      1333788672,
      1333788672);
  if ( pszArg7 != 0 )
  {
    pThis_276 = sub_41A5E0((unsigned int)this + 630);
    pThis_9A = sub_41A5E0((unsigned int)(this + 154));
    v18 = sub_699000((int)&unk_99FC80);  // 【clock_now(clk)】
    sub_4F2E80(pArg2, nArg3, pThis_9A, pThis_276 - v18);
  }
}



// ------------------------------------------------------------
// 0x47E170 sub_47E170
// ------------------------------------------------------------
// 转发 0x47DDD0（12 字节/3 DWORD 条目区间平搬拷贝）
uint32_t */*cdecl*/ sub_47E170(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  return sub_47DDD0(uArg1, uArg2, uArg3);
}



// ------------------------------------------------------------
// 0x47E190 sub_47E190
// ------------------------------------------------------------
// 转发 0x47DE10（14 字节条目区间正向拷贝）
unsigned int /*cdecl*/ sub_47E190(unsigned int uArg1, int nArg2, unsigned int uArg3)
{
  return sub_47DE10(uArg1, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x47E1B0 sub_47E1B0
// ------------------------------------------------------------
// 转发 0x47DE50（14 字节条目区间反向拷贝）
unsigned int /*cdecl*/ sub_47E1B0(int nArg1, unsigned int uArg2, unsigned int uArg3)
{
  return sub_47DE50(nArg1, uArg2, uArg3);
}



// ------------------------------------------------------------
// 0x47E1D0 sub_47E1D0
// ------------------------------------------------------------
// 8 字节（2 DWORD）条目区间平搬拷贝：[uArg1,uArg2) → uArg3 起，逐条 2 DWORD
uint32_t */*cdecl*/ sub_47E1D0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; result += 2 )
  {
    *result = *uArg12;
    result[1] = uArg12[1];
    uArg12 += 2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47E200 sub_47E200
// ------------------------------------------------------------
// 14 字节条目未初始化复制构造（uninitialized_copy）：[uArg1,nArg2) 逐条
// clong 构造（vftbl_clong + 字符串深拷贝）到 uArg3 起
uint32_t */*cdecl*/ sub_47E200(unsigned int uArg1, int nArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // esi
  int v5; // eax
  int v6; // edx
  uint32_t v8[5]; // [esp+0h] [ebp-20h] BYREF
  int v9; // [esp+1Ch] [ebp-4h]

  uArg32 = uArg3;
  v8[4] = v8;
  v8[3] = uArg3;
  v9 = 0;
  while ( uArg1 != nArg2 )
  {
    LOBYTE(v9) = 1;
    if ( uArg32 != nullptr )
    {
      sub_41A630((unsigned int)uArg32);
      LOBYTE(v9) = 2;
      *uArg32 = &vftbl_clong;
      v5 = sub_41A5E0(uArg1);
      sub_41A590((unsigned int)uArg32, v6, v5);
    }
    uArg32 = (uint32_t *)((char *)uArg32 + 14);
    LOBYTE(v9) = 0;
    uArg1 += 14;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x47E2B0 sub_47E2B0
// ------------------------------------------------------------
// 全局重置：遍历 dword_99FC34→dword_99FC74 的 4 个对象指针 vector（头步进
// 16 字节），对每个对象清 +540、按 nArg2 重写 +496/+510 两个 clong 串
int /*fastcall*/ sub_47E2B0(int nArg1, int nArg2)
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
          sub_41A590(*(uint32_t *)(*v2 + 4 * v3) + 496, nArg2, 0);
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
// 在 44 字节条目表（this+98/99）中找第一个 vt+48 检查通过（传 1）的条目：
// 无→-1；仅 1 条→4；多条→"是否第 0 条"（1/0）
int /*thiscall*/ sub_47E340(uint32_t *this)
{
  int fld_e98; // eax
  int fld_e99; // esi
  int v5; // ebx
  int i; // edi

  if ( sub_41A5E0((unsigned int)this + 558) != 0 )
    return -1;
  fld_e98 = *(this + 98);
  if ( fld_e98 != 0 )
    fld_e99 = (*(this + 99) - fld_e98) / 44;
  else
    fld_e99 = 0;
  v5 = 0;
  if ( fld_e99 <= 0 )
    return -1;
  for ( i = 0; (uint8_t)CNCommandChecker__vmt48(i + *(this + 98), 1) == 0; i += 44 )
  {
    if ( ++v5 >= fld_e99 )
      return -1;
  }
  if ( fld_e99 == 1 )
    return 4;
  else
    return v5 == 0;
}



// ------------------------------------------------------------
// 0x47E3E0 sub_47E3E0
// ------------------------------------------------------------
// 遍历 44 字节条目表（this+98/99）逐条调 CNCommandChecker__vmt50
// （条目清理/析构）
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
// 显示开关（写 this+136）：与 uArg2 不同才写（clong setter），随后遍历
// 44 字节条目表（this+98/99）逐条置 +40 =（this+136==0 或 this+558!=0 ? 0 : 1）
// ——条目可见性旗标联动【推断】
char /*thiscall*/ sub_47E440(unsigned int *this, uint8_t uArg2)
{
  unsigned int pThis_88; // edi
  bool pThis_882; // zf
  unsigned int fld_e98; // eax
  unsigned int v6; // edi
  int v7; // ebx

  pThis_88 = (unsigned int)(this + 136);
  pThis_882 = sub_41A5E0((unsigned int)(this + 136)) == 0;
  LOBYTE(fld_e98) = uArg2;
  if ( !pThis_882 != uArg2 )
  {
    sub_41A590(pThis_88, uArg2, uArg2);
    v6 = 0;
    v7 = 0;
    while ( 1 )
    {
      fld_e98 = *(this + 98);
      if ( fld_e98 == 0 )
        break;
      fld_e98 = (int)(*(this + 99) - fld_e98) / 44;
      if ( v6 >= fld_e98 )
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
  return fld_e98;
}



// ------------------------------------------------------------
// 0x47E4F0 sub_47E4F0
// ------------------------------------------------------------
// 技能参数刷新（错误串自证 CNRDSkill::flushSkillParameter）：按 dword_8F7C04
// vt+1032 选 unk_99FC30+16×槽 的对象 vector，重置各对象 +496 串并写 1.0f；
// 再对 18 个槽（vt+792，缺则 vt+1084）两轮遍历 vt+176/vt+228 链上的
// {技能ID, 数量} 对（32 字节步进），型别==4 或==当前槽时按上限(+32)封顶写入
// 技能对象 +510；最后调 vt+1164 收尾
void sub_47E4F0()
{
  int pObj3; // ebx
  int v1; // eax
  char *v2; // edi
  uint32_t *v3; // esi
  int v4; // eax
  int v5; // esi
  int pObj2; // eax
  int pObj; // esi
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
  int dword_8F7C042; // [esp+2Ch] [ebp-Ch]
  uint32_t *v28; // [esp+30h] [ebp-8h]
  int pObj22; // [esp+34h] [ebp-4h]

  pObj3 = dword_8F7C04;
  dword_8F7C042 = dword_8F7C04;
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
      pObj3 = dword_8F7C042;
    }
    v5 = 0;
    for ( i = 0; i < 18; ++i )
    {
      pObj2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 792))(pObj3, v5);
      pObj22 = pObj2;
      if ( pObj2 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 200))(pObj2) != 0 )
        pObj22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 1084))(pObj3, v5);
      pObj = pObj22;
      if ( pObj22 != 0 )
      {
        v8 = 0;
        for ( j = 0; j < 2; ++j )
        {
          if ( v8 != 0 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 224))(pObj) == 0 )
              break;
            v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 228))(pObj);
          }
          else
          {
            v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);
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
              pObj3 = dword_8F7C042;
              pObj = pObj22;
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
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 1164))(pObj3);
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
int /*cdecl*/ sub_47E720(int nArg1, unsigned int uArg2)
{
  int nArg12; // eax
  int v3; // eax
  int v4; // edx

  nArg12 = nArg1;
  if ( nArg1 == 4 )
  {
    while ( sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0 )
    {
      nArg12 = *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 44);
      if ( nArg12 != 4 )
        goto LABEL_6;
    }
    nArg12 = 0;
  }
LABEL_6:
  v3 = 4 * nArg12;
  v4 = dword_99FC34[v3];
  if ( v4 != 0 && uArg2 < (dword_99FC38[v3] - v4) >> 2 )
    return *(uint32_t *)(dword_99FC34[v3] + 4 * uArg2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x47E7A0 sub_47E7A0
// ------------------------------------------------------------
// 封印开关（SEAL_ON/SEAL_OFF 事件串自证）：this+558 与 uArg2 不同才生效
// （clong setter），遍历 44 字节条目表逐条置 +40 旗标（同 0x47E440 规则）；
// pszArg3 时播 SEAL_ON/SEAL_OFF（sub_432EA0）+ sub_44E850(18) + sub_48BAD0 刷新
char /*thiscall*/ sub_47E7A0(int *this, uint8_t uArg2, char pszArg3)
{
  int fld_e98; // eax
  bool pThis_22E; // zf
  unsigned int v6; // edi
  int v7; // ebx
  int fld_e982; // eax

  fld_e98 = *(this + 98);
  if ( fld_e98 != 0 )
  {
    fld_e98 = (*(this + 99) - fld_e98) / 44;
    if ( fld_e98 != 0 )
    {
      pThis_22E = sub_41A5E0((unsigned int)this + 558) == 0;
      LOBYTE(fld_e98) = uArg2;
      if ( !pThis_22E != uArg2 )
      {
        sub_41A590((unsigned int)this + 558, uArg2, uArg2);
        v6 = 0;
        v7 = 0;
        while ( 1 )
        {
          fld_e982 = *(this + 98);
          if ( fld_e982 == 0 || v6 >= (*(this + 99) - fld_e982) / 44 )
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
        LOBYTE(fld_e98) = pszArg3;
        if ( pszArg3 != 0 )
        {
          if ( uArg2 != 0 )
            sub_432EA0("SEAL_ON", -1, 0, 0);
          else
            sub_432EA0("SEAL_OFF", -1, 0, 0);
          sub_44E850(dword_8F8528, 18);
          LOBYTE(fld_e98) = sub_48BAD0(dword_8F8544);
        }
      }
    }
  }
  return fld_e98;
}



// ------------------------------------------------------------
// 0x47E8C0 sub_47E8C0
// ------------------------------------------------------------
// 对当前场景（dword_8F8500 按 word_77F804 查）的 +44 槽位，遍历
// dword_99FC34 槽 vector 逐对象调 vt+8（对象重置/清理）
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
// 14 字节条目未初始化填充 n 条（uninitialized_fill_n）：从 uArg3 模板
// 逐条 clong 构造到 uArg1
void /*cdecl*/ sub_47E920(uint32_t *uArg1, int nArg2, unsigned int uArg3)
{
  uint32_t *uArg12; // esi
  int v5; // eax
  int v6; // edx
  uint32_t v7[5]; // [esp+0h] [ebp-20h] BYREF
  int v8; // [esp+1Ch] [ebp-4h]

  uArg12 = uArg1;
  v7[4] = v7;
  v7[3] = uArg1;
  v8 = 0;
  while ( nArg2 != 0 )
  {
    LOBYTE(v8) = 1;
    if ( uArg12 != nullptr )
    {
      sub_41A630((unsigned int)uArg12);
      LOBYTE(v8) = 2;
      *uArg12 = &vftbl_clong;
      v5 = sub_41A5E0(uArg3);
      sub_41A590((unsigned int)uArg12, v6, v5);
    }
    --nArg2;
    uArg12 = (uint32_t *)((char *)uArg12 + 14);
    LOBYTE(v8) = 0;
  }
}



// ------------------------------------------------------------
// 0x47E9D0 sub_47E9D0
// ------------------------------------------------------------
// 取 this+103/104 的 14 字节条目表中第 uArg2 条的 clong 值；
// 越界则退回 sub_461750(0) 默认对象取值
int /*thiscall*/ sub_47E9D0(uint32_t *this, unsigned int uArg2)
{
  char v2; // bl
  int fld_e103; // eax
  unsigned int fld_e1032; // eax
  int v5; // esi
  uint8_t v7[14]; // [esp+Ah] [ebp-1Eh] BYREF
  int v8; // [esp+18h] [ebp-10h]
  int v9; // [esp+24h] [ebp-4h]

  v2 = 0;
  v8 = 0;
  fld_e103 = *(this + 103);
  if ( fld_e103 != 0 && uArg2 < (*(this + 104) - fld_e103) / 14 )
  {
    fld_e1032 = *(this + 103) + 14 * uArg2;
  }
  else
  {
    fld_e1032 = sub_461750(0);
    v9 = 0;
    v2 = 1;
    v8 = 1;
  }
  v5 = sub_41A5E0(fld_e1032);
  v9 = -1;
  if ( (v2 & 1) != 0 )
    sub_41A580(v7);
  return v5;
}



// ------------------------------------------------------------
// 0x47EA80 sub_47EA80
// ------------------------------------------------------------
// 查表换算（浮点积）：索引 nArg2（-1=用 this+510 当前值），取 this[75] 的
// 14 字节条目表第 (索引-1) 条值 × (this+131 的值)，按 double 返回
uint64_t /*thiscall*/ sub_47EA80(uint32_t *this, int nArg2)
{
  int pThis_1FE; // eax
  int fld_e75; // [esp+10h] [ebp+8h]

  pThis_1FE = nArg2;
  if ( nArg2 == -1 )
    pThis_1FE = sub_41A5E0((unsigned int)this + 510);
  fld_e75 = sub_41A5E0(*(this + 75) + 14 * (pThis_1FE - 1));
  return (uint64_t)((double)fld_e75 * COERCE_FLOAT(sub_41A5E0((unsigned int)(this + 131))));
}



// ------------------------------------------------------------
// 0x47EAD0 sub_47EAD0
// ------------------------------------------------------------
// 上行 0x47EA80 的整型版：取 this[87] 的 14 字节条目表第 (索引-1) 条值
// （nArg2==-1 用 this+510 当前值）
int /*thiscall*/ sub_47EAD0(uint32_t *this, int nArg2)
{
  int pThis_1FE; // eax

  pThis_1FE = nArg2;
  if ( nArg2 == -1 )
    pThis_1FE = sub_41A5E0((unsigned int)this + 510);
  return sub_41A5E0(*(this + 87) + 14 * (pThis_1FE - 1));
}



// ------------------------------------------------------------
// 0x47EB10 sub_47EB10
// ------------------------------------------------------------
// 余量计算【推断】：取 this[13] 的 14 字节表第 (this+124 型别) 条值；若
// dword_8F7C04 vt+1032 槽位中 this+142+14×[槽+4] 的减免百分比非零则按
// (100-x)/100 折减；再减 this+135 已消耗量，负值钳为 0
int /*thiscall*/ sub_47EB10(uint32_t *this)
{
  int pThis_7C; // eax
  int fld_e13; // edi
  int v5; // eax
  int pThis_E; // eax

  if ( dword_8F7C04 == 0 )
    return 0;
  pThis_7C = sub_41A5E0((unsigned int)(this + 124));
  fld_e13 = sub_41A5E0(*(this + 13) + 14 * pThis_7C);
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);
  pThis_E = sub_41A5E0((unsigned int)this + 14 * *(uint32_t *)(v5 + 4) + 142);
  if ( pThis_E != 0 )
    fld_e13 = fld_e13 * (100 - pThis_E) / 100;
  return (fld_e13 - *(this + 135)) & ((fld_e13 - *(this + 135) < 0) - 1);
}



// ------------------------------------------------------------
// 0x47EB90 sub_47EB90
// ------------------------------------------------------------
// 材料齐备检查：遍历 this+24/25 的 14 字节条目表，逐条经 sub_429830/
// 经 0x47E720 取技能对象（+496 当前量）与需求（this+28 表对应项）比较，
// 任一不足返回 0，全部满足返回 1
char /*thiscall*/ sub_47EB90(uint32_t *this)
{
  int fld_e24; // eax
  int v3; // esi
  unsigned int fld_e242; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // ebx
  int v9; // [esp+Ch] [ebp-8h]
  int fld_e25; // [esp+10h] [ebp-4h]

  fld_e24 = *(this + 24);
  v3 = 0;
  if ( fld_e24 != 0 )
    fld_e25 = (*(this + 25) - fld_e24) / 14;
  else
    fld_e25 = 0;
  v9 = 0;
  if ( fld_e25 <= 0 )
    return 1;
  while ( 1 )
  {
    fld_e242 = sub_41A5E0(v3 + *(this + 24));
    v5 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    v6 = sub_47E720(*(uint32_t *)(v5 + 44), fld_e242);
    v7 = sub_41A5E0(v6 + 496);
    if ( v7 < sub_41A5E0(v3 + *(this + 28)) )
      break;
    v3 += 14;
    if ( ++v9 >= fld_e25 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x47EC40 sub_47EC40
// ------------------------------------------------------------
// 全局对象表释放：dword_99FC34→dword_99FC74 的 4 个 vector 逐对象调
// vt[0](1)（回收）后 free 并清空表头；再清 dword_99FC18→dword_99FC28
// 的单对象槽
void sub_47EC40()
{
  int *dword_99FC342; // esi
  int v1; // ebx
  int i; // edi
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int *v4; // esi

  dword_99FC342 = dword_99FC34;
  do
  {
    if ( *dword_99FC342 != 0 )
      v1 = (dword_99FC342[1] - *dword_99FC342) >> 2;
    else
      v1 = 0;
    for ( i = 0; i < v1; ++i )
    {
      v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(*dword_99FC342 + 4 * i);
      if ( v3 != nullptr )
        (**v3)(v3, 1);
    }
    if ( *dword_99FC342 != 0 )
      j__free((void *)*dword_99FC342);
    *dword_99FC342 = 0;
    dword_99FC342[1] = 0;
    dword_99FC342[2] = 0;
    dword_99FC342 += 4;
  }
  while ( (int)dword_99FC342 < (int)dword_99FC74 );
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
// 遍历 44 字节条目表（this+98/99）逐条把条目地址经 sub_437240 登记
// 到 dword_8F85A8（收集/重挂列表）
unsigned int /*thiscall*/ sub_47ECE0(unsigned int *this)
{
  unsigned int v1; // edi
  int i; // ebx
  unsigned int result; // eax
  int fld_e98; // [esp+Ch] [ebp-4h] BYREF

  v1 = 0;
  for ( i = 0; ; i += 44 )
  {
    result = *(this + 98);
    if ( result == 0 )
      break;
    result = (int)(*(this + 99) - result) / 44;
    if ( v1 >= result )
      break;
    fld_e98 = i + *(this + 98);
    sub_437240(dword_8F85A8, (int)&fld_e98);
    ++v1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x47ED40 sub_47ED40
// ------------------------------------------------------------
// 进度型条件深检查【推断】：this+136 开且 dword_8F7C04 在，vt+752 值 ≥
// this[75] 表第 (this+510-1) 条 × (this+131) 浮点积；再遍历 this[83]/[84]
// 的 3 DWORD 条目（{对象, 起点, 步长}）按当前进度插值出需求量，经
// sub_484E80/dword_8F852C 查对象 vt+44 比较，不足即返回 0；全部通过返回 1
char /*thiscall*/ sub_47ED40(uint32_t *this)
{
  uint32_t *pThis; // edi
  int pObj2; // esi
  int v4; // eax
  int *v5; // esi
  int v6; // ebx
  int v7; // edi
  unsigned int pThis_1FE; // edi
  int v9; // eax
  int pObj; // eax
  float v11; // [esp+4h] [ebp-Ch]
  int v12; // [esp+8h] [ebp-8h]

  pThis = this;
  if ( sub_41A5E0((unsigned int)(this + 136)) == 0 )
    return 0;
  pObj2 = dword_8F7C04;
  if ( dword_8F7C04 == 0 )
    return 0;
  v4 = sub_41A5E0((unsigned int)pThis + 510);
  v12 = sub_41A5E0(pThis[75] + 14 * (v4 - 1));
  v11 = COERCE_FLOAT(sub_41A5E0((unsigned int)(pThis + 131)));
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 752))(pObj2) < (int)(uint64_t)((double)v12 * v11) )
    return 0;
  v5 = (int *)pThis[83];
  if ( v5 == (int *)pThis[84] )
    return 1;
  while ( 1 )
  {
    v6 = *v5;
    v7 = sub_41A5E0((unsigned int)(pThis + 8));
    pThis_1FE = v5[1] + (sub_41A5E0((unsigned int)this + 510) - 1) * (v5[2] - v5[1]) / (v7 - 1);
    if ( pThis_1FE != 0 )
    {
      v9 = sub_484E80(v6);
      if ( v9 == -1 )
        break;
      pObj = v9 >= *((uint32_t *)dword_8F852C + 2) ? 0 : *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v9);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj) < pThis_1FE )
        break;
    }
    v5 += 3;
    if ( v5 == (int *)*(this + 84) )
      return 1;
    pThis = this;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x47EE70 sub_47EE70
// ------------------------------------------------------------
// 两点插值取值（double）：级数上限=(this+8)-1；0x47E9D0 取 uArg2/uArg3 两级
// 的值，经 sub_4049C0 插值（档 nArg4-1）后 sub_432F40 转 double 返回
uint64_t /*thiscall*/ sub_47EE70(uint32_t *this, unsigned int uArg2, unsigned int uArg3, int nArg4)
{
  float v6; // [esp+0h] [ebp-14h]
  float v7; // [esp+4h] [ebp-10h]
  int pThis_8; // [esp+Ch] [ebp-8h]
  float v9; // [esp+Ch] [ebp-8h]

  pThis_8 = sub_41A5E0((unsigned int)(this + 8)) - 1;
  v7 = (float)sub_47E9D0(this, uArg3);
  v6 = (float)sub_47E9D0(this, uArg2);
  v9 = sub_4049C0(v6, v7, nArg4 - 1, pThis_8);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  return sub_432F40(v9);
}



// ------------------------------------------------------------
// 0x47EED0 sub_47EED0
// ------------------------------------------------------------
// 上行 0x47EE70 的 void 版：同款插值但丢弃结果（仅触发插值副作用）
void /*thiscall*/ sub_47EED0(uint32_t *this, unsigned int uArg2, unsigned int uArg3, int nArg4)
{
  float v5; // [esp+0h] [ebp-14h]
  float v6; // [esp+4h] [ebp-10h]
  int pThis_8; // [esp+Ch] [ebp-8h]

  pThis_8 = sub_41A5E0((unsigned int)(this + 8)) - 1;
  v6 = (float)sub_47E9D0(this, uArg3);
  v5 = (float)sub_47E9D0(this, uArg2);
  sub_4049C0(v5, v6, nArg4 - 1, pThis_8);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
}



// ------------------------------------------------------------
// 0x47EF20 sub_47EF20
// ------------------------------------------------------------
// 技能数值查表：this+107/108 的 16 字节条目（+4=14 字节子表 begin、+8=end）
// 中第 uArg2 项的第 nArg3 级值；nArg6!=11 且 nArg4!=nArg5 时经 sub_432FD0
// 做单位换算（nArg4→nArg5），否则原值；越界/空表返回 0
int /*thiscall*/ sub_47EF20(uint32_t *this, unsigned int uArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int fld_e107; // edx
  int64_t v7; // rax
  int fld_e1072; // esi
  unsigned int v9; // eax
  float v11; // [esp+8h] [ebp+8h]

  fld_e107 = *(this + 107);
  if ( fld_e107 != 0 && uArg2 < (*(this + 108) - fld_e107) >> 4 )
  {
    fld_e1072 = *(this + 107) + 16 * uArg2;
    v9 = *(uint32_t *)(fld_e1072 + 4);
    if ( v9 != 0 )
      v9 = (int)(*(uint32_t *)(fld_e1072 + 8) - v9) / 14;
    if ( nArg3 - 1 < v9 )
    {
      LODWORD(v7) = sub_41A5E0(*(uint32_t *)(fld_e1072 + 4) + 14 * nArg3 - 14);
      if ( nArg6 != 11 && nArg4 != nArg5 )
      {
        v11 = sub_432FD0(nArg4, nArg6) * (double)(int)v7;
        return (uint64_t)(v11 / sub_432FD0(nArg5, nArg6));
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
int /*thiscall*/ sub_47EFD0(char *this, float fArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int v7; // edi
  int v8; // eax
  int pThis_40; // edi
  int pThis_4E; // edi
  int pThis_11A; // eax
  double v14; // st7
  int pThis_11A2; // edi
  int pThis_11A3; // eax
  int v17; // eax
  float v18; // [esp+0h] [ebp-14h]
  float v19; // [esp+10h] [ebp-4h]
  int v20; // [esp+1Ch] [ebp+8h]
  float v21; // [esp+1Ch] [ebp+8h]
  float v22; // [esp+1Ch] [ebp+8h]
  int v23; // [esp+20h] [ebp+Ch]

  v7 = sub_47EF20(LODWORD(fArg2), nArg3, nArg4, nArg5, nArg6);
  v8 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v8 != 4 && v8 != 6 )
    return v7;
  if ( sub_41A5E0(this + 32) <= 1 || sub_41A5E0(this + 78) == 0 || nArg4 == -1 )
    return v7;
  pThis_40 = sub_41A5E0(this + 64);
  pThis_4E = (nArg4 - pThis_40) / sub_41A5E0(this + 78) + 1;
  if ( pThis_4E >= sub_41A5E0(this + 282) )
    pThis_4E = sub_41A5E0(this + 282);
  pThis_11A = sub_41A5E0(this + 282);
  v23 = pThis_4E - nArg3;
  v19 = (float)(int)sub_47EF20(LODWORD(fArg2), pThis_11A, -1, -1, 11);
  if ( sub_41A5E0(this + 282) == 1 )
  {
    v20 = sub_47EF20(LODWORD(fArg2), 2, -1, -1, 11);
    v14 = (double)(v20 - sub_47EF20(LODWORD(fArg2), 1, -1, -1, 11));
  }
  else
  {
    pThis_11A2 = sub_41A5E0(this + 282);
    v14 = (v19 - (double)(int)sub_47EF20(LODWORD(fArg2), 1, -1, -1, 11)) / (double)(pThis_11A2 - 1);
  }
  v18 = v19 - (double)v23 * v14;
  v21 = (float)sub_432F40(v18);
  if ( nArg6 != 11 )
  {
    pThis_11A3 = sub_41A5E0(this + 282);
    v17 = sub_47DE90(pThis_11A3);
    if ( nArg4 < v17 )
    {
      v22 = sub_432FD0(v17, nArg6) * v21;
      v21 = v22 / sub_432FD0(nArg5, nArg6);
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
  unsigned int pThis_8; // ebx
  int v4; // edi
  int v5; // eax
  int pThis_1FE; // eax
  int fld_e87; // ebx
  int v8; // edx
  int v9; // eax
  int v10; // edx
  unsigned int result; // eax
  unsigned int fld_e91; // eax
  int v13; // eax
  int v14; // edx
  int v15; // edi
  int v16; // eax
  int v17; // edx
  int v18; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]
  unsigned int ArgLista; // [esp+1Ch] [ebp+8h]

  pThis_8 = (unsigned int)(this + 8);
  v4 = ArgList;
  if ( ArgList > sub_41A5E0((unsigned int)(this + 8)) )
  {
    v5 = sub_41A5E0(pThis_8);
    off_77F3FC(aCriticalError_8, ArgList, v5);
    v4 = sub_41A5E0(pThis_8);
  }
  if ( v4 == -1 )
    pThis_1FE = sub_41A5E0((unsigned int)this + 510) - 1;
  else
    pThis_1FE = v4 - 1;
  fld_e87 = sub_41A5E0(*(this + 87) + 14 * pThis_1FE);
  sub_41A590((unsigned int)(this + 154), v8, fld_e87);
  v9 = sub_699000((int)&unk_99FC80);  // 【clock_now(clk)】
  sub_41A590((unsigned int)this + 630, v10, fld_e87 + v9);
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
        fld_e91 = sub_41A5E0(i + *(this + 91));
        v13 = sub_47E720(v18, fld_e91);
        v15 = v13;
        if ( v13 != 0 )
        {
          sub_41A590(v13 + 616, v14, fld_e87);
          v16 = sub_699000((int)&unk_99FC80);  // 【clock_now(clk)】
          sub_41A590(v15 + 630, v17, fld_e87 + v16);
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
// 技能描述串模板渲染：在 this+111/112 的 11 DWORD（44 字节）条目中按级别
// 区间 [fld[0],fld[1]] 找到 nArg3 所在条目，取描述模板（fld[2] 起）；循环
// 扫 '<' 占位符并按占位表（fld[4]/[5] 8 字节对）替换数值：型别 -1 → 0x47EF20
// 查表，否则 0x47E9D0 两点插值（sub_4049C0），再乘 fld[8] 系数；按资源
// 482/485/488 三种格式（%d/%.1f/%.2f，后缀资源 484/487/490）拼回 pszArg2
char /*thiscall*/ sub_47F310(int **this, char *pszArg2, int nArg3)
{
  int *fld_e112; // eax
  int *fld_e111; // esi
  const char *psz2; // edi
  int v8; // ecx
  char *pFound; // eax
  const char *psz5; // ebx
  int v11; // esi
  unsigned int *v12; // eax
  int fld_e107; // edx
  unsigned int v14; // eax
  double v15; // st7
  int fld_e1072; // esi
  int v17; // eax
  unsigned int v18; // eax
  unsigned int v19; // esi
  unsigned int v20; // edi
  const char *psz3; // eax
  int v22; // eax
  const char *psz6; // eax
  const char *v24; // edx
  unsigned int nLen2; // eax
  const char *psz; // eax
  const char *psz4; // eax
  const char *psz8; // eax
  const char *psz7; // eax
  unsigned int v30; // esi
  float v31; // [esp+0h] [ebp-40h]
  float v32; // [esp+4h] [ebp-3Ch]
  int pThis_8; // [esp+Ch] [ebp-34h]
  size_t nLen; // [esp+Ch] [ebp-34h]
  size_t nLen3; // [esp+Ch] [ebp-34h]
  size_t nLen4; // [esp+Ch] [ebp-34h]
  int *fld_e1112; // [esp+20h] [ebp-20h]
  char *Destinationa; // [esp+24h] [ebp-1Ch]
  float v41; // [esp+28h] [ebp-18h]
  char Buffer[16]; // [esp+2Ch] [ebp-14h] BYREF
  int dword_796E502; // [esp+3Ch] [ebp-4h]
  unsigned int v44; // [esp+48h] [ebp+8h]

  dword_796E502 = dword_796E50;
  if ( nArg3 > sub_41A5E0((unsigned int)(this + 8)) )
    return 0;
  fld_e112 = *(this + 112);
  fld_e111 = *(this + 111);
  if ( fld_e111 == fld_e112 )
    return 0;
  while ( *fld_e111 > nArg3 || fld_e111[1] < nArg3 )
  {
    fld_e111 += 11;
    if ( fld_e111 == fld_e112 )
      return 0;
  }
  fld_e1112 = fld_e111;
  psz2 = (const char *)sub_41ACF0(fld_e111 + 2);
  v44 = 0;
  while ( 1 )
  {
    v8 = fld_e111[4];
    if ( v8 == 0 )
      break;
    if ( v44 >= (fld_e111[5] - v8) >> 3 )
      break;
    pFound = strstr(psz2, "<");
    psz5 = pFound;
    if ( pFound == nullptr )
      break;
    v11 = pFound - psz2;
    strncpy(pszArg2, psz2, pFound - psz2);
    v12 = (unsigned int *)(fld_e1112[4] + 8 * v44);
    Destinationa = &pszArg2[v11];
    if ( *v12 == -1 )
    {
      fld_e107 = (int)*(this + 107);
      v14 = v12[1];
      if ( fld_e107 != 0 && v14 < ((int)*(this + 108) - fld_e107) >> 4 )
      {
        fld_e1072 = (int)&(*(this + 107))[4 * v14];
        v17 = *(uint32_t *)(fld_e1072 + 4);
        if ( v17 != 0 )
          v18 = (*(uint32_t *)(fld_e1072 + 8) - v17) / 14;
        else
          v18 = 0;
        if ( nArg3 - 1 < v18 )
          v15 = (double)sub_41A5E0(*(uint32_t *)(fld_e1072 + 4) + 14 * nArg3 - 14);
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
      pThis_8 = sub_41A5E0((unsigned int)(this + 8)) - 1;
      v32 = (float)sub_47E9D0(this, v19);
      v31 = (float)sub_47E9D0(this, v20);
      v15 = sub_4049C0(v31, v32, nArg3 - 1, pThis_8);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    }
    v41 = v15 * *(float *)(fld_e1112[8] + 4 * v44);
    nLen = strlen((const char *)sub_422E70(483));
    psz3 = (const char *)sub_422E70(482);
    if ( strncmp(psz5, psz3, nLen) == 0 )
    {
      v22 = sub_432F40(v41);
      sprintf(Buffer, "%d", v22);
      psz6 = (const char *)sub_422E70(484);
      v24 = psz6 + 1;
      nLen2 = (unsigned int)&psz6[strlen(psz6) + 1];
      goto LABEL_29;
    }
    nLen3 = strlen((const char *)sub_422E70(486));
    psz = (const char *)sub_422E70(485);
    if ( strncmp(psz5, psz, nLen3) == 0 )
    {
      sprintf(Buffer, "%.1f", v41);
      psz4 = (const char *)sub_422E70(487);
      v24 = psz4 + 1;
      nLen2 = (unsigned int)&psz4[strlen(psz4) + 1];
      goto LABEL_29;
    }
    nLen4 = strlen((const char *)sub_422E70(489));
    psz8 = (const char *)sub_422E70(488);
    if ( strncmp(psz5, psz8, nLen4) == 0 )
    {
      sprintf(Buffer, "%.2f", v41);
      psz7 = (const char *)sub_422E70(490);
      v24 = psz7 + 1;
      nLen2 = (unsigned int)&psz7[strlen(psz7) + 1];
LABEL_29:
      v30 = nLen2 - (uint32_t)v24;
      strcpy(Destinationa, Buffer);
      psz2 = &psz5[v30];
      fld_e111 = fld_e1112;
      pszArg2 = &Destinationa[strlen(Buffer)];
      ++v44;
    }
    else
    {
      strncpy(Destinationa, psz5, 1u);
      pszArg2 = Destinationa + 1;
      fld_e111 = fld_e1112;
      psz2 = psz5 + 1;
    }
  }
  strcpy(pszArg2, psz2);
  return 1;
}


// ------------------------------------------------------------
// 0x47F6B0 sub_47F6B0
// ------------------------------------------------------------
// 14 字节条目区间逐条调 vt[0](0)（析构/清理）：[pszArg1, pszArg2) 步进 14 字节
int /*stdcall*/ sub_47F6B0(char *pszArg1, char *pszArg2)
{
  char *i; // esi
  int result; // eax

  for ( i = pszArg1; i != pszArg2; i += 14 )
    result = (**(int (/*thiscall*/ ***)(char *, uint32_t))i)(i, 0);
  return result;
}



// ------------------------------------------------------------
// 0x47F6E0 sub_47F6E0
// ------------------------------------------------------------
// 14 字节条目 vector 销毁：逐条调 vt[0](0) 后 free 缓冲区，
// begin/end/cap（+4/8/12）清零
int /*thiscall*/ sub_47F6E0(int this)
{
  char *fld_4; // esi
  char *i; // edi

  fld_4 = *(char **)(this + 4);
  if ( fld_4 != nullptr )
  {
    for ( i = *(char **)(this + 8); fld_4 != i; fld_4 += 14 )
      (**(void (/*thiscall*/ ***)(char *, uint32_t))fld_4)(fld_4, 0);
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
// 14 字节条目 vector erase 区间收缩：[uArg3,uArg4) 后段前移覆盖
// （0x47DE10 拷贝），尾段逐条析构（vt[0](0)），end(+8) 回收；
// 区间相等时直接返回
unsigned int */*thiscall*/ sub_47F720(int *this, unsigned int *pDwArg2, unsigned int uArg3, unsigned int uArg4)
{
  unsigned int fld_e2; // eax
  char *fld_e22; // edi
  unsigned int fld_e23; // ebx
  char *i; // esi

  if ( uArg3 == uArg4 )
  {
    *pDwArg2 = uArg3;
    return pDwArg2;
  }
  else
  {
    fld_e2 = sub_47DE10(uArg4, *(this + 2), uArg3);
    fld_e22 = (char *)*(this + 2);
    fld_e23 = fld_e2;
    for ( i = (char *)fld_e2; i != fld_e22; i += 14 )
      (**(void (/*thiscall*/ ***)(char *, uint32_t))i)(i, 0);
    *(this + 2) = fld_e23;
    *pDwArg2 = uArg3;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x47F790 sub_47F790
// ------------------------------------------------------------
// 转发 sub_59EE30（3 参透传）
int /*stdcall*/ sub_47F790(int nArg1, int nArg2, int nArg3)
{
  return sub_59EE30(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x47F7B0 sub_47F7B0
// ------------------------------------------------------------
// 转发 0x47E200（14 字节条目未初始化复制构造）
uint32_t */*stdcall*/ sub_47F7B0(unsigned int uArg1, int nArg2, uint32_t *uArg3)
{
  return sub_47E200(uArg1, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x47F7D0 sub_47F7D0
// ------------------------------------------------------------
// 技能可用性检查【推断】：dword_8F7C04 在；vt+1032 槽位中 (this+124 型别) <
// this+212+14×[槽+4] 的等级门槛；vt+672(3) ≥ this+16 + 型别×(this+78)；
// 经 0x47EB90 材料齐备；0x47EB10 余量 ≤ Value（全局）——全过返回 true
bool /*thiscall*/ sub_47F7D0(uint32_t *this)
{
  int v3; // esi
  int pThis_7C2; // ebx
  int pThis_4E; // esi
  int v6; // esi
  int pThis_7C; // [esp+4h] [ebp-4h]
  int pThis_10; // [esp+4h] [ebp-4h]

  if ( dword_8F7C04 == 0 )
    return false;
  v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04) + 4);
  pThis_7C = sub_41A5E0((unsigned int)(this + 124));
  if ( pThis_7C >= sub_41A5E0((unsigned int)this + 14 * v3 + 212) )
    return false;
  pThis_7C2 = sub_41A5E0((unsigned int)(this + 124));
  pThis_10 = sub_41A5E0((unsigned int)(this + 16));
  pThis_4E = sub_41A5E0((unsigned int)this + 78);
  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) < pThis_10 + pThis_7C2 * pThis_4E
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
// 技能使用请求：0x47F7D0 检查通过则发网络包 31
// （1 字节载荷 = this+1 的 clong 值）
bool /*thiscall*/ sub_47F890(uint32_t *this)
{
  bool result; // al
  uint8_t v3[4]; // [esp+4h] [ebp-4h] BYREF

  result = sub_47F7D0(this);
  if ( result )
  {
    sub_423200(dword_8F7B08, 31);  // 【发送网络包API】
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
// 0x47F8E0 sub_47F8E0
// ------------------------------------------------------------
// 转发 0x47F6E0（14 字节条目 vector 销毁）
// attributes: thunk
int /*thiscall*/ sub_47F8E0(int this)
{
  return sub_47F6E0(this);
}



// ------------------------------------------------------------
// 0x47F8F0 sub_47F8F0
// ------------------------------------------------------------
// 填充 n 条 14 字节条目（转发 0x47E920）并返回末尾指针
char */*stdcall*/ sub_47F8F0(uint32_t *uArg1, int nArg2, unsigned int uArg3)
{
  sub_47E920(uArg1, nArg2, uArg3);
  return (char *)uArg1 + 14 * nArg2;
}



// ------------------------------------------------------------
// 0x47F920 sub_47F920
// ------------------------------------------------------------
// 抛 std::out_of_range（"invalid vector<T> subscript"）——vector 越界的标准抛出点
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
  sub_4015C0("invalid vector<T> subscript", 0x1Bu);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::out_of_range::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// ------------------------------------------------------------
// 0x47F990 sub_47F990
// ------------------------------------------------------------
// 抛 std::length_error（"vector<T> too long"）——vector 超长的标准抛出点
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
  sub_4015C0((void *)"vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x47FA00 sub_47FA00
// ------------------------------------------------------------
// 对象清空：free +32 与 +16 两个缓冲区并各清 begin/end/cap 三字段；
// sub_41B010 清 this+8 处容器
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
// DWORD vector reserve：容量（this+4/8/12）不足 uArg2 时 operator new(4×uArg2)
// 重建并搬旧数据（0x3FFFFFFF=4 字节/元素的 32 位上限）；返回新 capEnd
unsigned int /*thiscall*/ sub_47FA50(int this, unsigned int uArg2)
{
  int fld_4; // ecx
  int fld_82; // ebx
  unsigned int result; // eax
  char *pMem; // edi
  int fld_43; // eax
  int fld_42; // [esp-18h] [ebp-38h]
  int fld_8; // [esp-14h] [ebp-34h]
  int v10; // [esp+0h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-14h]
  int *v12; // [esp+10h] [ebp-10h]
  int v13; // [esp+1Ch] [ebp-4h]
  size_t v14; // [esp+28h] [ebp+8h]

  v12 = &v10;
  if ( uArg2 > 0x3FFFFFFF )
    sub_44CAB0(this);
  fld_4 = *(uint32_t *)(this + 4);
  fld_82 = 0;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;
  else
    result = 0;
  if ( result < uArg2 )
  {
    v14 = 4 * uArg2;
    pMem = (char *)operator new(v14);
    fld_8 = *(uint32_t *)(this + 8);
    fld_42 = *(uint32_t *)(this + 4);
    Block = pMem;
    v13 = 0;
    sub_497E70(fld_42, fld_8, pMem);
    fld_43 = *(uint32_t *)(this + 4);
    if ( fld_43 != 0 )
    {
      fld_82 = (*(uint32_t *)(this + 8) - fld_43) >> 2;
      j__free(*(void **)(this + 4));
    }
    *(uint32_t *)(this + 12) = &pMem[v14];
    *(uint32_t *)(this + 8) = &pMem[4 * fld_82];
    *(uint32_t *)(this + 4) = pMem;
    return (unsigned int)&pMem[v14];
  }
  return result;
}



// ------------------------------------------------------------
// 0x47FB20 sub_47FB20
// ------------------------------------------------------------
// DWORD vector 定容构造：清 +1/2/3 后 operator new(4×uArg2)，begin=end=块首，
// capEnd=块首+4×uArg2；超 0x3FFFFFFF（2^32/4 条）抛 0x47F990
char /*thiscall*/ sub_47FB20(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x3FFFFFFF )
    sub_47F990(this);
  pMem = (char *)operator new(4 * uArg2);
  *(this + 3) = &pMem[4 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x47FB80 sub_47FB80
// ------------------------------------------------------------
// 12 字节条目 vector 定容构造：清 +1/2/3 后 operator new(12×uArg2)；
// 条目上限 0x15555555（=2^32/12），超限抛 0x47F990
char /*thiscall*/ sub_47FB80(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x15555555 )
    sub_47F990(this);
  pMem = (char *)operator new(12 * uArg2);
  *(this + 3) = &pMem[12 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x47FBD0 sub_47FBD0
// ------------------------------------------------------------
// 44 字节条目 vector 定容构造：清 +1/2/3 后 operator new(44×uArg2)；
// 条目上限 0x5D1745D（=2^32/44），超限抛 0x47F990
char /*thiscall*/ sub_47FBD0(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x5D1745D )
    sub_47F990(this);
  pMem = (char *)operator new(44 * uArg2);
  *(this + 3) = &pMem[44 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x47FC20 sub_47FC20
// ------------------------------------------------------------
// 14 字节条目 vector 定容构造：清 +1/2/3 后 operator new(14×uArg2)；
// 条目上限 0x12492492（=2^32/14），超限抛 0x47F990
char /*thiscall*/ sub_47FC20(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x12492492 )
    sub_47F990(this);
  pMem = (char *)operator new(14 * uArg2);
  *(this + 3) = &pMem[14 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x47FC70 sub_47FC70
// ------------------------------------------------------------
// DWORD vector resize：元素数 <uArg2 时尾部补 nArg3 值（sub_565EE0 fill），
// >uArg2 时截断 end（memcpy 0 字节的平移写法）
unsigned int /*thiscall*/ sub_47FC70(unsigned int *this, unsigned int uArg2, int nArg3)
{
  int fld_e1; // edx
  unsigned int result; // eax
  int fld_e2; // eax
  void *v7; // edx

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    result = (int)(*(this + 2) - fld_e1) >> 2;
  else
    result = 0;
  if ( result >= uArg2 )
  {
    if ( fld_e1 != 0 )
    {
      result = *(this + 2);
      if ( uArg2 < (int)(result - fld_e1) >> 2 )
      {
        v7 = (void *)(fld_e1 + 4 * uArg2);
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
    if ( fld_e1 != 0 )
      fld_e2 = (int)(*(this + 2) - fld_e1) >> 2;
    else
      fld_e2 = 0;
    return sub_565EE0((void *)*(this + 2), uArg2 - fld_e2, (int)&nArg3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x47FD00 sub_47FD00
// ------------------------------------------------------------
// 14 字节条目 vector 定点插入 uArg3 条（新条目值由 nArg4 构造：sub_46B080
// 字符串化到 v23 暂存）；原地路径用 0x47E200/0x47E1B0/0x47DDA0 腾挪填充；
// 容量不足时 1.5 倍扩容重建（306783378=0x12492492=2^32/14 的最大条数）
void /*thiscall*/ sub_47FD00(int *this, int pArg2, unsigned int uArg3, int nArg4)
{
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v14; // edi
  int fld_e14; // eax
  char *fld_e23; // ecx
  int fld_e26; // edx
  int fld_e12; // [esp-18h] [ebp-4Ch]
  int fld_e25; // [esp-Ch] [ebp-40h]
  unsigned int fld_e24; // [esp-8h] [ebp-3Ch]
  int v22; // [esp+0h] [ebp-34h] BYREF
  uint32_t v23[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+1Ch] [ebp-18h]
  int *pThis; // [esp+20h] [ebp-14h]
  int *v26; // [esp+24h] [ebp-10h]
  int v27; // [esp+30h] [ebp-4h]
  char *v28; // [esp+3Ch] [ebp+8h]
  int v29; // [esp+40h] [ebp+Ch]
  int v30; // [esp+44h] [ebp+10h]

  v26 = &v22;
  pThis = this;
  sub_46B080(nArg4);
  fld_e1 = *(this + 1);
  fld_e3 = 0;
  v27 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 14;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - *(this + 1)) / 14;
    else
      fld_e2 = 0;
    if ( 306783378 - fld_e2 < uArg3 )
      sub_47F990(this);
    if ( *(this + 1) != 0 )
      fld_e22 = (*(this + 2) - *(this + 1)) / 14;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (char *)*(this + 2);
      Block = fld_e23;
      if ( (int)&fld_e23[-pArg2] / 14 >= uArg3 )
      {
        v28 = &fld_e23[-14 * uArg3];
        *(this + 2) = sub_47E200(v28, fld_e23, fld_e23);
        sub_47E1B0(pArg2, v28, Block);
        sub_47DDA0(pArg2, pArg2 + 14 * uArg3, v23);
      }
      else
      {
        sub_47E200(pArg2, fld_e23, pArg2 + 14 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 14;
        fld_e25 = *(this + 2);
        LOBYTE(v27) = 3;
        sub_47F8F0(fld_e25, fld_e24, v23);
        fld_e26 = 14 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v27 = 0;
        sub_47DDA0(pArg2, fld_e26 - 14 * uArg3, v23);
      }
    }
    else
    {
      if ( 306783378 - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        fld_e27 = (*(this + 2) - *(this + 1)) / 14;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_47DD70(this);
      v30 = 14 * v10;
      pMem = (char *)operator new(14 * v10);
      fld_e12 = *(this + 1);
      Block = pMem;
      LOBYTE(v27) = 1;
      v29 = sub_47E200(fld_e12, pArg2, pMem);
      sub_47E920(v29, uArg3, v23);
      sub_47E200(pArg2, *(this + 2), 14 * uArg3 + v29);
      fld_e13 = *(this + 1);
      v27 = 0;
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 14;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);
      if ( fld_e14 != 0 )
      {
        sub_47F6B0(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v30];
      *(this + 2) = (int)&pMem[14 * v14];
      *(this + 1) = (int)pMem;
    }
  }
  v27 = -1;
  sub_41A580(v23);
}

