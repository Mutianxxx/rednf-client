// ============================================================
// 【40JP逆向源代码工程】game/worldmap_reward.cpp
// 模块: 世界地图/副本选择/房间列表/奖励（CNPVPModule/CNSelectDungeonModule/
//       CNRoomListModule/CNRDParty/CNRDReward/CNRDNpc）
// 来源: work/dump_combat.txt  区块: 0x450000-0x460000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
// 函数数: 217
// ------------------------------------------------------------
// ★ 本文件已按以下 UI 事件锚点升级注释（sub_432EA0 事件名 = 字符串自证）：
//   地图交互：MAP_DISAPPEAR(0x453B10) / MAP_MOUSEOVER·MAP_SELECT
//     （CNSelectDungeonModule__vmt4=0x454740）/ MAP_COUNTDOWN(0x454F00 巨型)
//   按钮音效：CLICK_BUTTON1(0x451AD0) / CLICK_BUTTON2（0x453DD0 座位确认、
//     0x4577F0 奖励开箱等多处）
//   奖励系统：REWARD_OPEN1(0x4577F0/0x458120) / REWARD_OPEN2(0x458930) /
//     REWARD_BOX_SET·REWARD_ICON_OFF(0x459ED0) / REWARD_BOX_GLITTER(CNRDReward__vmt0)
//   世界地图创建："CRITICAL ERROR : WORLD MAP LOAD FAIL %d" 自证
//     0x456210（地图创建）/ CNRoomListModule__vmt8=0x45B4A0（房间列表侧）
//   PVP 房间地图："HendonMyre/Hendon_Pub_PVP.map" 自证（0x452C50）
// ★ 战斗分发器（sub_4471E0，见 bigfunc_4471E0_sub_4471E0.cpp）配套落点：
//   case 2/3 → 0x453DD0 座位同步；case 2 循环体 → 0x455EB0 队伍分组登记；
//   case 0x21 → 0x45ED80 对象移除；case 0x22 → 0x45EF30 全场怪物同步；
//   case 0x15/0x16 → 0x45FE80 对象注册；id→对象解析 → 0x45EBE0（全 case 共用）
// ★ 帧循环锚点（docs/13 §2）：0x451D50 = 主管理器 tick（dword_8F8528）；0x45E1A0 =
//   UDP 接收泵（dword_8F8524，SOCKET recvfrom 直证，按模块类型分发）
// 交叉引用：发包 API 0x423200/0x423380 已 L1 精修于 src/nengine/net_socket.cpp
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】世界地图数据容器（0x450130-0x452580）
// 地图/房间词条表与容器操作（含 0x451D50 主管理器 tick，docs/13 §2）。
// ============================================================
// ------------------------------------------------------------
// 0x450130 sub_450130 —— CNRDPVPInterface 析构：句柄族回收
// vftbl_CNRDPVPInterface 自证：句柄索引 +86/+73/+60/+47 逐项 DeleteObject 后统一清指针，
// 末段 44F730(+9) 与 free(+3) 收尾。
// ------------------------------------------------------------
void /*thiscall*/ sub_450130(HGDIOBJ *this)  // sub_450130 —— CNRDPVPInterface 析构：句柄族回收
{
  *this = &vftbl_CNRDPVPInterface;  // 装虚表/取地址：← vftbl_CNRDPVPInterface
  sub_52A7B0();  // 调 粒子析构：各子指针（发射器/贴图/动画槽）逐个 vt+0(1) 释放（107L）
  if ( *(this + 86) != nullptr )  // this+344〔nReservedDelay〕
  {
    DeleteObject(*(this + 86));  // this+344〔nReservedDelay〕
    *(this + 86) = nullptr;  // 写字段 this+86 ← nullptr
  }
  *((uint8_t *)this + 300) = 0;  // 写字段 this+300（pAnim300）
  *((uint8_t *)this + 301) = 0;  // 写字段 this[301]（宽1字节）
  *((uint8_t *)this + 302) = 0;  // 写字段 this[302]（宽1字节）
  *((uint8_t *)this + 303) = 0;  // 写字段 this[303]（宽1字节）
  *(this + 78) = nullptr;  // 写字段 this+78（bGuildFlagC） ← nullptr
  *(this + 79) = nullptr;  // 写字段 this+79 ← nullptr
  *(this + 80) = nullptr;  // 写字段 this+80（nAuraStage） ← nullptr
  *(this + 81) = nullptr;  // 写字段 this+81 ← nullptr
  *(this + 82) = nullptr;  // 写字段 this+82 ← nullptr
  *(this + 83) = nullptr;  // 写字段 this+83 ← nullptr
  *(this + 84) = nullptr;  // 写字段 this+84（pFxObjA） ← nullptr
  *(this + 85) = nullptr;  // 写字段 this+85 ← nullptr
  *(this + 86) = nullptr;  // 写字段 this+86 ← nullptr
  *(this + 87) = nullptr;  // 写字段 this+87 ← nullptr
  if ( *(this + 73) != nullptr )  // this+292〔nOpenMode292(推断)〕
  {
    DeleteObject(*(this + 73));  // this+292〔nOpenMode292(推断)〕
    *(this + 73) = nullptr;  // 写字段 this+73（szDigitalName） ← nullptr
  }
  *((uint8_t *)this + 248) = 0;  // 写字段 this+248（bParamSlotA）
  *((uint8_t *)this + 249) = 0;  // 写字段 this[249]（宽1字节）
  *((uint8_t *)this + 250) = 0;  // 写字段 this[250]（宽1字节）
  *((uint8_t *)this + 251) = 0;  // 写字段 this[251]（宽1字节）
  *(this + 65) = nullptr;  // 写字段 this+65 ← nullptr
  *(this + 66) = nullptr;  // 写字段 this+66 ← nullptr
  *(this + 67) = nullptr;  // 写字段 this+67（nPeriodMs） ← nullptr
  *(this + 68) = nullptr;  // 写字段 this+68（nCharCount） ← nullptr
  *(this + 69) = nullptr;  // 写字段 this+69 ← nullptr
  *(this + 70) = nullptr;  // 写字段 this+70 ← nullptr
  *(this + 71) = nullptr;  // 写字段 this+71（bMoveType） ← nullptr
  *(this + 72) = nullptr;  // 写字段 this+72（nSnapshot72） ← nullptr
  *(this + 73) = nullptr;  // 写字段 this+73（szDigitalName） ← nullptr
  *(this + 74) = nullptr;  // 写字段 this+74（field_004A） ← nullptr
  if ( *(this + 60) != nullptr )  // this+240〔nSyncArgB〕
  {
    DeleteObject(*(this + 60));  // this+240〔nSyncArgB〕
    *(this + 60) = nullptr;  // 写字段 this+60（nFadeValue60） ← nullptr
  }
  *((uint8_t *)this + 196) = 0;  // 写字段 this[196]（宽1字节）
  *((uint8_t *)this + 197) = 0;  // 写字段 this+197（field_00C5）
  *((uint8_t *)this + 198) = 0;  // 写字段 this+198（field_00C6）
  *((uint8_t *)this + 199) = 0;  // 写字段 this[199]（宽1字节）
  *(this + 52) = nullptr;  // 写字段 this+52（bAuraState） ← nullptr
  *(this + 53) = nullptr;  // 写字段 this+53 ← nullptr
  *(this + 54) = nullptr;  // 写字段 this+54 ← nullptr
  *(this + 55) = nullptr;  // 写字段 this+55 ← nullptr
  *(this + 56) = nullptr;  // 写字段 this+56（pCmdVecCap56） ← nullptr
  *(this + 57) = nullptr;  // 写字段 this+57 ← nullptr
  *(this + 58) = nullptr;  // 写字段 this+58 ← nullptr
  *(this + 59) = nullptr;  // 写字段 this+59 ← nullptr
  *(this + 60) = nullptr;  // 写字段 this+60（nFadeValue60） ← nullptr
  *(this + 61) = nullptr;  // 写字段 this+61（bReadyFlagA） ← nullptr
  if ( *(this + 47) != nullptr )  // this+188〔nStatusIdx(推断)〕
  {
    DeleteObject(*(this + 47));  // this+188〔nStatusIdx(推断)〕
    *(this + 47) = nullptr;  // 写字段 this+47 ← nullptr
  }
  *((uint8_t *)this + 144) = 0;  // 写字段 this+144（pFrameList144）
  *((uint8_t *)this + 145) = 0;  // 写字段 this[145]（宽1字节）
  *((uint8_t *)this + 146) = 0;  // 写字段 this[146]（宽1字节）
  *((uint8_t *)this + 147) = 0;  // 写字段 this[147]（宽1字节）
  *(this + 39) = nullptr;  // 写字段 this+39 ← nullptr
  *(this + 40) = nullptr;  // 写字段 this+40（bStateSub40） ← nullptr
  *(this + 41) = nullptr;  // 写字段 this+41 ← nullptr
  *(this + 42) = nullptr;  // 写字段 this+42 ← nullptr
  *(this + 43) = nullptr;  // 写字段 this+43 ← nullptr
  *(this + 44) = nullptr;  // 写字段 this+44（nExpireMs） ← nullptr
  *(this + 45) = nullptr;  // 写字段 this+45 ← nullptr
  *(this + 46) = nullptr;  // 写字段 this+46 ← nullptr
  *(this + 47) = nullptr;  // 写字段 this+47 ← nullptr
  *(this + 48) = nullptr;  // 写字段 this+48（pCmdVecBegin48） ← nullptr
  sub_44F730(this + 9);  // sub_44F730 —— 28 字节记录数组析构释放
  if ( *(this + 3) != nullptr )  // this+12〔nSkillRec12(推断)〕
    j__free(*(this + 3));  // 释放堆块
  *(this + 3) = nullptr;  // 写字段 this+3 ← nullptr
  *(this + 4) = nullptr;  // 写字段 this+4（pHostObj） ← nullptr
  *(this + 5) = nullptr;  // 写字段 this+5 ← nullptr
}



// ------------------------------------------------------------
// 0x450340 sub_450340 —— CNRDReward 构造：定时器组初始化
// vftbl_CNRDReward 自证；内嵌 3 个 nengine::CNTimer 子对象 + eh vector ctor 4×0x10 定时器表，
// 两组 6/12/1600 定时参数默认值；456F50 参数复位 + 45A8A0 挂装。
// ------------------------------------------------------------
char */*thiscall*/ sub_450340(char *this, void *Block)  // sub_450340 —— CNRDReward 构造：定时器组初始化
{
  *(uint32_t *)this = &vftbl_CNRDReward;  // 构造装配 vftable：CNRDReward
  *(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  *((uint32_t *)this + 2) = &vftbl_nengine__CNTimer;  // 写字段 this[2]（宽4字节）
  *((uint32_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
  *(this + 20) = 1;  // 写字段 this+20（nPage） ← 1
  *(this + 22) = 0;  // 写字段 this+22 ← 0
  *(this + 21) = 0;  // 写字段 this+21（bArmorState） ← 0
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 7) = 0;  // 写字段 this+7（uPathTerm）
  *((uint32_t *)this + 6) = 0;  // 写字段 this[6]（宽4字节）
  *(this + 56) = 0;  // 写字段 this+56（pCmdVecCap56） ← 0
  *(this + 57) = 0;  // 写字段 this+57 ← 0
  *(this + 58) = 0;  // 写字段 this+58 ← 0
  *(this + 59) = 0;  // 写字段 this+59 ← 0
  *((uint32_t *)this + 17) = 0;  // 写字段 this+17（bEnable）
  *((uint32_t *)this + 18) = 6;  // 写字段 this+18（bDragChild）
  *((uint32_t *)this + 19) = 12;  // 写字段 this[19]（宽4字节）
  *((uint32_t *)this + 20) = 0;  // 写字段 this+20（nPage）
  *((uint32_t *)this + 21) = 1600;  // 写字段 this+21（bArmorState）
  *((uint32_t *)this + 22) = 0;  // 写字段 this[22]（宽4字节）
  *((uint32_t *)this + 23) = 0;  // 写字段 this[23]（宽4字节）
  *((uint32_t *)this + 24) = 0;  // 写字段 this+24（nPageMax）
  *((uint32_t *)this + 25) = 0;  // 写字段 this[25]（宽4字节）
  *((uint32_t *)this + 26) = 0;  // 写字段 this[26]（宽4字节）
  *(this + 108) = 0;  // 写字段 this+108（nAdd108） ← 0
  *(this + 109) = 0;  // 写字段 this+109 ← 0
  *(this + 110) = 0;  // 写字段 this+110 ← 0
  *(this + 111) = 0;  // 写字段 this+111 ← 0
  *((uint32_t *)this + 30) = 0;  // 写字段 this[30]（宽4字节）
  *((uint32_t *)this + 31) = 6;  // 写字段 this[31]（宽4字节）
  *((uint32_t *)this + 32) = 12;  // 写字段 this+32（nHeight）
  *((uint32_t *)this + 33) = 0;  // 写字段 this+33（bJobVecDirty）
  *((uint32_t *)this + 34) = 1600;  // 写字段 this[34]（宽4字节）
  *((uint32_t *)this + 35) = 0;  // 写字段 this[35]（宽4字节）
  *((uint32_t *)this + 36) = 0;  // 写字段 this+36（nStateWord36）
  *((uint32_t *)this + 37) = 0;  // 写字段 this+37（bFadeFlag37）
  *((uint32_t *)this + 38) = 0;  // 写字段 this+38（bFadeFlag38）
  *((uint32_t *)this + 39) = 0;  // 写字段 this[39]（宽4字节）
  *(this + 168) = 0;  // 写字段 this+168（pAppendVec） ← 0
  *((uint32_t *)this + 41) = &vftbl_nengine__CNTimer;  // 写字段 this[41]（宽4字节）
  *((uint32_t *)this + 43) = 0;  // 写字段 this[43]（宽4字节）
  *(this + 176) = 1;  // 写字段 this+176（pAppendVecCap） ← 1
  *(this + 178) = 0;  // 写字段 this+178 ← 0
  *(this + 177) = 0;  // 写字段 this+177 ← 0
  *((uint32_t *)this + 47) = 0;  // 写字段 this[47]（宽4字节）
  *((uint32_t *)this + 46) = 0;  // 写字段 this[46]（宽4字节）
  *((uint32_t *)this + 45) = 0;  // 写字段 this[45]（宽4字节）
  *((uint32_t *)this + 59) = 0;  // 写字段 this[59]（宽4字节）
  *((uint32_t *)this + 60) = 0;  // 写字段 this+60（nFadeValue60）
  *((uint32_t *)this + 61) = 0;  // 写字段 this+61（bReadyFlagA）
  *((uint32_t *)this + 63) = 0;  // 写字段 this[63]（宽4字节）
  *((uint32_t *)this + 64) = 0;  // 写字段 this+64（apServerTabBtn）
  *((uint32_t *)this + 65) = 0;  // 写字段 this[65]（宽4字节）
  `eh vector constructor iterator'(this + 440, 0x10u, 4, sub_4019A0, sub_44CF40);  // 指针 vector 三字段清零（起/止/容量 = 0）
  *(this + 616) = 0;  // 写字段 this+616（nReactionState） ← 0
  *((uint32_t *)this + 153) = &vftbl_nengine__CNTimer;  // 写字段 this+153（bCastFlagA）
  *((uint32_t *)this + 155) = 0;  // 写字段 this[155]（宽4字节）
  *(this + 624) = 1;  // 写字段 this+624 ← 1
  *(this + 626) = 0;  // 写字段 this+626 ← 0
  *(this + 625) = 0;  // 写字段 this+625 ← 0
  *((uint32_t *)this + 159) = 0;  // 写字段 this[159]（宽4字节）
  *((uint32_t *)this + 158) = 0;  // 写字段 this[158]（宽4字节）
  *((uint32_t *)this + 157) = 0;  // 写字段 this[157]（宽4字节）
  sub_456F50(this);  // sub_456F50 —— 奖励参数初始化
  sub_45A8A0(Block);  // sub_45A8A0 —— CNRDReward 构造（控件/按钮/贴图全套）
  return this;
}



// ------------------------------------------------------------
// 0x4504F0 sub_4504F0 —— CNRDReward 析构：与构造对称
// vftbl_CNRDReward 自证；456F80 释放 + 4×0x10 定时器表析构（对称 ·0x450340），
// 两处 55A050 信息窗文本组块清空。
// ------------------------------------------------------------
int /*thiscall*/ sub_4504F0(char *this)  // sub_4504F0 —— CNRDReward 析构：与构造对称
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNRDReward;  // 构造装配 vftable：CNRDReward
  sub_456F80();  // sub_456F80 —— 奖励 UI 对象释放
  *((uint32_t *)this + 153) = &vftbl_nengine__IObject;  // 写字段 this+153（bCastFlagA）
  *(this + 616) = 0;  // 写字段 this+616（nReactionState） ← 0
  `eh vector destructor iterator'(this + 440, 0x10u, 4, sub_44CF40);
  sub_55A050(this + 248);  // sub_55A050 —— 结果 = 信息窗文本 2（5014C0）
  sub_55A050(this + 232);  // sub_55A050 —— 结果 = 信息窗文本 2（5014C0）
  *((uint32_t *)this + 41) = &vftbl_nengine__IObject;  // 写字段 this[41]（宽4字节）
  *(this + 168) = 0;  // 写字段 this+168（pAppendVec） ← 0
  if ( *((uint32_t *)this + 38) != 0 )  // this+152〔nAdd152(推断)〕
  {
    DeleteObject(*((HGDIOBJ *)this + 38));  // this+152〔nAdd152(推断)〕
    *((uint32_t *)this + 38) = 0;  // 写字段 this+38（bFadeFlag38）
  }
  *(this + 108) = 0;  // 写字段 this+108（nAdd108） ← 0
  *(this + 109) = 0;  // 写字段 this+109 ← 0
  *(this + 110) = 0;  // 写字段 this+110 ← 0
  *(this + 111) = 0;  // 写字段 this+111 ← 0
  *((uint32_t *)this + 30) = 0;  // 写字段 this[30]（宽4字节）
  *((uint32_t *)this + 31) = 0;  // 写字段 this[31]（宽4字节）
  *((uint32_t *)this + 32) = 0;  // 写字段 this+32（nHeight）
  *((uint32_t *)this + 33) = 0;  // 写字段 this+33（bJobVecDirty）
  *((uint32_t *)this + 34) = 0;  // 写字段 this[34]（宽4字节）
  *((uint32_t *)this + 35) = 0;  // 写字段 this[35]（宽4字节）
  *((uint32_t *)this + 36) = 0;  // 写字段 this+36（nStateWord36）
  *((uint32_t *)this + 37) = 0;  // 写字段 this+37（bFadeFlag37）
  *((uint32_t *)this + 38) = 0;  // 写字段 this+38（bFadeFlag38）
  *((uint32_t *)this + 39) = 0;  // 写字段 this[39]（宽4字节）
  result = *((uint32_t *)this + 25);  // 读字段 result = this[25]
  if ( result != 0 )  // result=this+100 插值终点 Y
  {
    result = DeleteObject(*((HGDIOBJ *)this + 25));  // result = 调 DeleteObject
    *((uint32_t *)this + 25) = 0;  // 写字段 this[25]（宽4字节）
  }
  *(this + 56) = 0;  // 写字段 this+56（pCmdVecCap56） ← 0
  *(this + 57) = 0;  // 写字段 this+57 ← 0
  *(this + 58) = 0;  // 写字段 this+58 ← 0
  *(this + 59) = 0;  // 写字段 this+59 ← 0
  *((uint32_t *)this + 17) = 0;  // 写字段 this+17（bEnable）
  *((uint32_t *)this + 18) = 0;  // 写字段 this+18（bDragChild）
  *((uint32_t *)this + 19) = 0;  // 写字段 this[19]（宽4字节）
  *((uint32_t *)this + 20) = 0;  // 写字段 this+20（nPage）
  *((uint32_t *)this + 21) = 0;  // 写字段 this+21（bArmorState）
  *((uint32_t *)this + 22) = 0;  // 写字段 this[22]（宽4字节）
  *((uint32_t *)this + 23) = 0;  // 写字段 this[23]（宽4字节）
  *((uint32_t *)this + 24) = 0;  // 写字段 this+24（nPageMax）
  *((uint32_t *)this + 25) = 0;  // 写字段 this[25]（宽4字节）
  *((uint32_t *)this + 26) = 0;  // 写字段 this[26]（宽4字节）
  *(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  *((uint32_t *)this + 2) = &vftbl_nengine__IObject;  // 写字段 this[2]（宽4字节）
  return result;  // result=this+100 插值终点 Y
}



// ------------------------------------------------------------
// 0x450620 sub_450620 —— CNRDCashShop 构造：商城词条表装配
// CNRDCashShop::vftable 自证：80×0x54 商品词条表 + 4×0x20/4×0x10/128×0x10 列表区间，
// 末段 55C1A0/560D10 商城初始化（0x2794 字节大对象）。
// ------------------------------------------------------------
char */*thiscall*/ sub_450620(char *this, int nArg2)  // sub_450620 —— CNRDCashShop 构造：商城词条表装配
{
  *(uint32_t *)this = &CNRDCashShop::`vftable';  // 构造装配 vftable：CNRDCashShop
  *(this + 20) = 0;  // 写字段 this+20（nPage） ← 0
  *((uint32_t *)this + 4) = &off_6C2B88;  // 写字段 this+4（pHostObj）
  *((uint32_t *)this + 6) = 0;  // 写字段 this[6]（宽4字节）
  *(this + 28) = 1;  // 写字段 this+28（pPanelVec） ← 1
  *(this + 30) = 0;  // 写字段 this+30 ← 0
  *(this + 29) = 0;  // 写字段 this+29 ← 0
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 9) = 0;  // 写字段 this[9]（宽4字节）
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  *(this + 64) = 0;  // 写字段 this+64（apServerTabBtn） ← 0
  *(this + 65) = 0;  // 写字段 this+65 ← 0
  *(this + 66) = 0;  // 写字段 this+66 ← 0
  *(this + 67) = 0;  // 写字段 this+67（nPeriodMs） ← 0
  *((uint32_t *)this + 19) = 0;  // 写字段 this[19]（宽4字节）
  *((uint32_t *)this + 20) = 6;  // 写字段 this+20（nPage）
  *((uint32_t *)this + 21) = 12;  // 写字段 this+21（bArmorState）
  *((uint32_t *)this + 22) = 0;  // 写字段 this[22]（宽4字节）
  *((uint32_t *)this + 23) = 1600;  // 写字段 this[23]（宽4字节）
  *((uint32_t *)this + 24) = 0;  // 写字段 this+24（nPageMax）
  *((uint32_t *)this + 25) = 0;  // 写字段 this[25]（宽4字节）
  *((uint32_t *)this + 26) = 0;  // 写字段 this[26]（宽4字节）
  *((uint32_t *)this + 27) = 0;  // 写字段 this[27]（宽4字节）
  *((uint32_t *)this + 28) = 0;  // 写字段 this+28（pPanelVec）
  *(this + 116) = 0;  // 写字段 this+116（pSessionCtx） ← 0
  *(this + 117) = 0;  // 写字段 this+117 ← 0
  *(this + 118) = 0;  // 写字段 this+118 ← 0
  *(this + 119) = 0;  // 写字段 this+119 ← 0
  *((uint32_t *)this + 32) = 0;  // 写字段 this+32（nHeight）
  *((uint32_t *)this + 33) = 6;  // 写字段 this+33（bJobVecDirty）
  *((uint32_t *)this + 34) = 12;  // 写字段 this[34]（宽4字节）
  *((uint32_t *)this + 35) = 0;  // 写字段 this[35]（宽4字节）
  *((uint32_t *)this + 36) = 1600;  // 写字段 this+36（nStateWord36）
  *((uint32_t *)this + 37) = 0;  // 写字段 this+37（bFadeFlag37）
  *((uint32_t *)this + 38) = 0;  // 写字段 this+38（bFadeFlag38）
  *((uint32_t *)this + 39) = 0;  // 写字段 this[39]（宽4字节）
  *((uint32_t *)this + 40) = 0;  // 写字段 this+40（bStateSub40）
  *((uint32_t *)this + 41) = 0;  // 写字段 this[41]（宽4字节）
  *(this + 168) = 0;  // 写字段 this+168（pAppendVec） ← 0
  *(this + 169) = 0;  // 写字段 this+169 ← 0
  *(this + 170) = 0;  // 写字段 this+170 ← 0
  *(this + 171) = 0;  // 写字段 this+171 ← 0
  *((uint32_t *)this + 45) = 0;  // 写字段 this[45]（宽4字节）
  *((uint32_t *)this + 46) = 6;  // 写字段 this[46]（宽4字节）
  *((uint32_t *)this + 47) = 12;  // 写字段 this[47]（宽4字节）
  *((uint32_t *)this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48）
  *((uint32_t *)this + 49) = 1600;  // 写字段 this+49（bUdpReported）
  *((uint32_t *)this + 50) = 0;  // 写字段 this+50（bCharSelSent）
  *((uint32_t *)this + 51) = 0;  // 写字段 this[51]（宽4字节）
  *((uint32_t *)this + 52) = 0;  // 写字段 this+52（bAuraState）
  *((uint32_t *)this + 53) = 0;  // 写字段 this[53]（宽4字节）
  *((uint32_t *)this + 54) = 0;  // 写字段 this[54]（宽4字节）
  *(this + 220) = 0;  // 写字段 this+220（nSnapDst220） ← 0
  *(this + 221) = 0;  // 写字段 this+221 ← 0
  *(this + 222) = 0;  // 写字段 this+222 ← 0
  *(this + 223) = 0;  // 写字段 this+223 ← 0
  *((uint32_t *)this + 58) = 0;  // 写字段 this[58]（宽4字节）
  *((uint32_t *)this + 59) = 6;  // 写字段 this[59]（宽4字节）
  *((uint32_t *)this + 60) = 12;  // 写字段 this+60（nFadeValue60）
  *((uint32_t *)this + 61) = 0;  // 写字段 this+61（bReadyFlagA）
  *((uint32_t *)this + 62) = 1600;  // 写字段 this+62（bReadyFlagB）
  *((uint32_t *)this + 63) = 0;  // 写字段 this[63]（宽4字节）
  *((uint32_t *)this + 64) = 0;  // 写字段 this+64（apServerTabBtn）
  *((uint32_t *)this + 65) = 0;  // 写字段 this[65]（宽4字节）
  *((uint32_t *)this + 66) = 0;  // 写字段 this[66]（宽4字节）
  *((uint32_t *)this + 67) = 0;  // 写字段 this+67（nPeriodMs）
  *(this + 272) = 0;  // 写字段 this+272 ← 0
  *(this + 273) = 0;  // 写字段 this+273 ← 0
  *(this + 274) = 0;  // 写字段 this+274 ← 0
  *(this + 275) = 0;  // 写字段 this+275 ← 0
  *((uint32_t *)this + 71) = 0;  // 写字段 this+71（bMoveType）
  *((uint32_t *)this + 72) = 6;  // 写字段 this+72（nSnapshot72）
  *((uint32_t *)this + 73) = 12;  // 写字段 this+73（szDigitalName）
  *((uint32_t *)this + 74) = 0;  // 写字段 this+74（field_004A）
  *((uint32_t *)this + 75) = 1600;  // 写字段 this[75]（宽4字节）
  *((uint32_t *)this + 76) = 0;  // 写字段 this+76（szEmblemPath）
  *((uint32_t *)this + 77) = 0;  // 写字段 this+77（bGuildFlagB）
  *((uint32_t *)this + 78) = 0;  // 写字段 this+78（bGuildFlagC）
  *((uint32_t *)this + 79) = 0;  // 写字段 this[79]（宽4字节）
  *((uint32_t *)this + 80) = 0;  // 写字段 this+80（nAuraStage）
  `eh vector constructor iterator'(this + 348, 0x20u, 4, sub_44CA10, sub_44C050);  // 槽位记录复位（内嵌 std::string 置空 + 首字段清零）
  `eh vector constructor iterator'(this + 508, 0x10u, 4, sub_4019A0, sub_44FF50);  // 指针 vector 三字段清零（起/止/容量 = 0）
  `eh vector constructor iterator'(this + 604, 0x54u, 80, sub_44CF30, sub_44C2A0);  // 对象 + 字符串成对释放弃构体
  *(this + 7504) = 0;  // 写字段 this+7504 ← 0
  *((uint32_t *)this + 1875) = &off_6C2B88;  // 写字段 this[1875]（宽4字节）
  *((uint32_t *)this + 1877) = 0;  // 写字段 this[1877]（宽4字节）
  *(this + 7512) = 1;  // 写字段 this+7512 ← 1
  *(this + 7514) = 0;  // 写字段 this+7514 ← 0
  *(this + 7513) = 0;  // 写字段 this+7513 ← 0
  *((uint32_t *)this + 1881) = 0;  // 写字段 this[1881]（宽4字节）
  *((uint32_t *)this + 1880) = 0;  // 写字段 this[1880]（宽4字节）
  *((uint32_t *)this + 1879) = 0;  // 写字段 this[1879]（宽4字节）
  *(this + 7532) = 0;  // 写字段 this+7532（bCfgBlock12） ← 0
  *((uint32_t *)this + 1882) = &off_6C2B88;  // 写字段 this[1882]（宽4字节）
  *((uint32_t *)this + 1884) = 0;  // 写字段 this[1884]（宽4字节）
  *(this + 7540) = 1;  // 写字段 this+7540 ← 1
  *(this + 7542) = 0;  // 写字段 this+7542 ← 0
  *(this + 7541) = 0;  // 写字段 this+7541 ← 0
  *((uint32_t *)this + 1888) = 0;  // 写字段 this[1888]（宽4字节）
  *((uint32_t *)this + 1887) = 0;  // 写字段 this[1887]（宽4字节）
  *((uint32_t *)this + 1886) = 0;  // 写字段 this[1886]（宽4字节）
  *(this + 7560) = 0;  // 写字段 this+7560 ← 0
  *((uint32_t *)this + 1889) = &off_6C2B88;  // 写字段 this[1889]（宽4字节）
  *((uint32_t *)this + 1891) = 0;  // 写字段 this[1891]（宽4字节）
  *(this + 7568) = 1;  // 写字段 this+7568（uEnable7568） ← 1
  *(this + 7570) = 0;  // 写字段 this+7570 ← 0
  *(this + 7569) = 0;  // 写字段 this+7569 ← 0
  *((uint32_t *)this + 1895) = 0;  // 写字段 this[1895]（宽4字节）
  *((uint32_t *)this + 1894) = 0;  // 写字段 this[1894]（宽4字节）
  *((uint32_t *)this + 1893) = 0;  // 写字段 this[1893]（宽4字节）
  `eh vector constructor iterator'(this + 7848, 0x10u, 128, sub_4019A0, sub_5E5260);  // 指针 vector 三字段清零（起/止/容量 = 0）
  *((uint32_t *)this + 2499) = 0;  // 写字段 this[2499]（宽4字节）
  *((uint32_t *)this + 2500) = 0;  // 写字段 this[2500]（宽4字节）
  *((uint32_t *)this + 2501) = 0;  // 写字段 this[2501]（宽4字节）
  *((uint32_t *)this + 2503) = 0;  // 写字段 this[2503]（宽4字节）
  *((uint32_t *)this + 2504) = 0;  // 写字段 this[2504]（宽4字节）
  *((uint32_t *)this + 2505) = 0;  // 写字段 this[2505]（宽4字节）
  sub_44CEA0(this + 10024);  // sub_44CEA0 —— 槽位记录全量初始化（含内嵌 std::string 置空）
  *((uint32_t *)this + 1) = nArg2;  // 写字段 this[1]（宽4字节）
  sub_55C1A0(this);  // sub_55C1A0 —— 商城辅助 4（66 行）
  sub_560D10(this);  // sub_560D10 —— 新版商城主窗口逻辑（778 行·本文件最大）：装载 Etc/NewCashShop.etc 配置 + 426BD0/423B30/43C410/43C4D0/43C630 绘制 + 69A5F0/69A840 + 69C780/…
  return this;
}


// ------------------------------------------------------------
// 0x450970 sub_450970 —— CNRDCashShop 析构：对称释放
// CNRDCashShop::vftable 自证；55EDC0 列表刷新收尾 + 128/80/4 三层 eh vector 析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_450970(void **this)  // sub_450970 —— CNRDCashShop 析构：对称释放
{
  int result; // eax

  *this = &CNRDCashShop::`vftable';  // 构造装配 vftable：CNRDCashShop
  sub_55EDC0();  // sub_55EDC0 —— 礼赠列表刷新（55EA90，126 行）
  sub_44C2A0(this + 2506);  // sub_44C2A0 —— 对象 + 字符串成对释放弃构体
  if ( *(this + 2503) != nullptr )
    j__free(*(this + 2503));  // 释放堆块
  *(this + 2503) = nullptr;  // 写字段 this+2503 ← nullptr
  *(this + 2504) = nullptr;  // 写字段 this+2504 ← nullptr
  *(this + 2505) = nullptr;  // 写字段 this+2505 ← nullptr
  if ( *(this + 2499) != nullptr )
    j__free(*(this + 2499));  // 释放堆块
  *(this + 2499) = nullptr;  // 写字段 this+2499 ← nullptr
  *(this + 2500) = nullptr;  // 写字段 this+2500 ← nullptr
  *(this + 2501) = nullptr;  // 写字段 this+2501 ← nullptr
  `eh vector destructor iterator'(this + 1962, 0x10u, 128, sub_5E5260);  // 调 动画子对象清理临时缓冲
  *(this + 1889) = &nengine::IObject::`vftable';  // 写字段 this+1889 ← &nengine::IObject::`vftable
  *((uint8_t *)this + 7560) = 0;  // 写字段 this[7560]（宽1字节）
  *(this + 1882) = &nengine::IObject::`vftable';  // 写字段 this+1882 ← &nengine::IObject::`vftable
  *((uint8_t *)this + 7532) = 0;  // 写字段 this+7532（bCfgBlock12）
  *(this + 1875) = &nengine::IObject::`vftable';  // 写字段 this+1875 ← &nengine::IObject::`vftable
  *((uint8_t *)this + 7504) = 0;  // 写字段 this[7504]（宽1字节）
  `eh vector destructor iterator'(this + 151, 0x54u, 80, sub_44C2A0);  // 对象 + 字符串成对释放弃构体
  `eh vector destructor iterator'(this + 127, 0x10u, 4, sub_44FF50);
  `eh vector destructor iterator'(this + 87, 0x20u, 4, sub_44C050);  // 元素成对释放弃构体
  if ( *(this + 79) != nullptr )
  {
    DeleteObject(*(this + 79));  // 调 删除 GDI 对象
    *(this + 79) = nullptr;  // 写字段 this+79 ← nullptr
  }
  *((uint8_t *)this + 272) = 0;  // 写字段 this[272]（宽1字节）
  *((uint8_t *)this + 273) = 0;  // 写字段 this[273]（宽1字节）
  *((uint8_t *)this + 274) = 0;  // 写字段 this[274]（宽1字节）
  *((uint8_t *)this + 275) = 0;  // 写字段 this[275]（宽1字节）
  *(this + 71) = nullptr;  // 写字段 this+71（bMoveType） ← nullptr
  *(this + 72) = nullptr;  // 写字段 this+72（nSnapshot72） ← nullptr
  *(this + 73) = nullptr;  // 写字段 this+73（szDigitalName） ← nullptr
  *(this + 74) = nullptr;  // 写字段 this+74（field_004A） ← nullptr
  *(this + 75) = nullptr;  // 写字段 this+75 ← nullptr
  *(this + 76) = nullptr;  // 写字段 this+76（szEmblemPath） ← nullptr
  *(this + 77) = nullptr;  // 写字段 this+77（bGuildFlagB） ← nullptr
  *(this + 78) = nullptr;  // 写字段 this+78（bGuildFlagC） ← nullptr
  *(this + 79) = nullptr;  // 写字段 this+79 ← nullptr
  *(this + 80) = nullptr;  // 写字段 this+80（nAuraStage） ← nullptr
  if ( *(this + 66) != nullptr )  // this+264〔nAnimHandle(推断)〕
  {
    DeleteObject(*(this + 66));  // this+264〔nAnimHandle(推断)〕
    *(this + 66) = nullptr;  // 写字段 this+66 ← nullptr
  }
  *((uint8_t *)this + 220) = 0;  // 写字段 this+220（nSnapDst220）
  *((uint8_t *)this + 221) = 0;  // 写字段 this[221]（宽1字节）
  *((uint8_t *)this + 222) = 0;  // 写字段 this[222]（宽1字节）
  *((uint8_t *)this + 223) = 0;  // 写字段 this[223]（宽1字节）
  *(this + 58) = nullptr;  // 写字段 this+58 ← nullptr
  *(this + 59) = nullptr;  // 写字段 this+59 ← nullptr
  *(this + 60) = nullptr;  // 写字段 this+60（nFadeValue60） ← nullptr
  *(this + 61) = nullptr;  // 写字段 this+61（bReadyFlagA） ← nullptr
  *(this + 62) = nullptr;  // 写字段 this+62（bReadyFlagB） ← nullptr
  *(this + 63) = nullptr;  // 写字段 this+63 ← nullptr
  *(this + 64) = nullptr;  // 写字段 this+64（apServerTabBtn） ← nullptr
  *(this + 65) = nullptr;  // 写字段 this+65 ← nullptr
  *(this + 66) = nullptr;  // 写字段 this+66 ← nullptr
  *(this + 67) = nullptr;  // 写字段 this+67（nPeriodMs） ← nullptr
  if ( *(this + 53) != nullptr )  // this+212〔nField212(推断)〕
  {
    DeleteObject(*(this + 53));  // this+212〔nField212(推断)〕
    *(this + 53) = nullptr;  // 写字段 this+53 ← nullptr
  }
  *((uint8_t *)this + 168) = 0;  // 写字段 this+168（pAppendVec）
  *((uint8_t *)this + 169) = 0;  // 写字段 this[169]（宽1字节）
  *((uint8_t *)this + 170) = 0;  // 写字段 this[170]（宽1字节）
  *((uint8_t *)this + 171) = 0;  // 写字段 this[171]（宽1字节）
  *(this + 45) = nullptr;  // 写字段 this+45 ← nullptr
  *(this + 46) = nullptr;  // 写字段 this+46 ← nullptr
  *(this + 47) = nullptr;  // 写字段 this+47 ← nullptr
  *(this + 48) = nullptr;  // 写字段 this+48（pCmdVecBegin48） ← nullptr
  *(this + 49) = nullptr;  // 写字段 this+49（bUdpReported） ← nullptr
  *(this + 50) = nullptr;  // 写字段 this+50（bCharSelSent） ← nullptr
  *(this + 51) = nullptr;  // 写字段 this+51 ← nullptr
  *(this + 52) = nullptr;  // 写字段 this+52（bAuraState） ← nullptr
  *(this + 53) = nullptr;  // 写字段 this+53 ← nullptr
  *(this + 54) = nullptr;  // 写字段 this+54 ← nullptr
  if ( *(this + 40) != nullptr )  // this+160〔fAdd160(推断)〕
  {
    DeleteObject(*(this + 40));  // this+160〔fAdd160(推断)〕
    *(this + 40) = nullptr;  // 写字段 this+40（bStateSub40） ← nullptr
  }
  *((uint8_t *)this + 116) = 0;  // 写字段 this+116（pSessionCtx）
  *((uint8_t *)this + 117) = 0;  // 写字段 this[117]（宽1字节）
  *((uint8_t *)this + 118) = 0;  // 写字段 this[118]（宽1字节）
  *((uint8_t *)this + 119) = 0;  // 写字段 this[119]（宽1字节）
  *(this + 32) = nullptr;  // 写字段 this+32（nHeight） ← nullptr
  *(this + 33) = nullptr;  // 写字段 this+33（bJobVecDirty） ← nullptr
  *(this + 34) = nullptr;  // 写字段 this+34 ← nullptr
  *(this + 35) = nullptr;  // 写字段 this+35 ← nullptr
  *(this + 36) = nullptr;  // 写字段 this+36（nStateWord36） ← nullptr
  *(this + 37) = nullptr;  // 写字段 this+37（bFadeFlag37） ← nullptr
  *(this + 38) = nullptr;  // 写字段 this+38（bFadeFlag38） ← nullptr
  *(this + 39) = nullptr;  // 写字段 this+39 ← nullptr
  *(this + 40) = nullptr;  // 写字段 this+40（bStateSub40） ← nullptr
  *(this + 41) = nullptr;  // 写字段 this+41 ← nullptr
  result = (int)*(this + 27);  // this+108〔nAdd108(推断)〕
  if ( result != 0 )  // result=this+108 nAdd108
  {
    result = DeleteObject(*(this + 27));  // result = 调 DeleteObject
    *(this + 27) = nullptr;  // 写字段 this+27 ← nullptr
  }
  *((uint8_t *)this + 64) = 0;  // 写字段 this+64（apServerTabBtn）
  *((uint8_t *)this + 65) = 0;  // 写字段 this[65]（宽1字节）
  *((uint8_t *)this + 66) = 0;  // 写字段 this[66]（宽1字节）
  *((uint8_t *)this + 67) = 0;  // 写字段 this+67（nPeriodMs）
  *(this + 19) = nullptr;  // 写字段 this+19 ← nullptr
  *(this + 20) = nullptr;  // 写字段 this+20（nPage） ← nullptr
  *(this + 21) = nullptr;  // 写字段 this+21（bArmorState） ← nullptr
  *(this + 22) = nullptr;  // 写字段 this+22 ← nullptr
  *(this + 23) = nullptr;  // 写字段 this+23 ← nullptr
  *(this + 24) = nullptr;  // 写字段 this+24（nPageMax） ← nullptr
  *(this + 25) = nullptr;  // 写字段 this+25 ← nullptr
  *(this + 26) = nullptr;  // 写字段 this+26 ← nullptr
  *(this + 27) = nullptr;  // 写字段 this+27 ← nullptr
  *(this + 28) = nullptr;  // 写字段 this+28（pPanelVec） ← nullptr
  *((uint8_t *)this + 20) = 0;  // 写字段 this+20（nPage）
  *(this + 4) = &nengine::IObject::`vftable';  // 写字段 this+4（pHostObj） ← &nengine::IObject::`vftable
  return result;  // result=this+108 nAdd108
}


// ------------------------------------------------------------
// 0x450C80 sub_450C80 —— 主管理器子对象构造：UI 族批量装配
// RTTI 自证批量装配 UI 族：CNRDTutorial/CNRDItemInventory/CNRDAvatarInventory/CNRDSkillInventory 等窗口，
// CNRDPrivateStoreWindow 三形态 + CNRDSelectWarRoomArea/CNRDWarRoomBattleTalkBox/CNRDStackNumberSet/CNRDCursor，
// 末段经 dword_8F84B8 vt+60 载 Common/Etc/MonoLayer.img 建底图。
// ------------------------------------------------------------
int /*thiscall*/ sub_450C80(char *Block)  // sub_450C80 —— 主管理器子对象构造：UI 族批量装配
{
  uint32_t *v2; // edi
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  char *pMem2; // eax
  char *v6; // eax
  uint32_t *v7; // edi
  uint8_t *pMem3; // eax
  uint8_t *v9; // eax
  int v10; // eax
  uint32_t *pMem4; // eax
  uint32_t *v12; // eax
  int v13; // eax
  int v14; // eax
  uint8_t *pMem5; // eax
  uint8_t *v16; // eax
  uint8_t *pMem6; // eax
  uint8_t *pMem62; // edi
  int v19; // eax
  uint8_t *pMem7; // eax
  uint8_t *v21; // eax
  uint32_t *pMem8; // eax
  uint32_t *pMem82; // edi
  uint32_t *pMem9; // eax
  uint32_t *pMem92; // edi
  int v26; // eax
  int v27; // eax
  uint32_t *pMem10; // eax
  uint32_t *pMem102; // edi
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // eax
  uint32_t *pMem11; // eax
  uint32_t *pMem112; // edi
  uint32_t *pMem12; // eax
  uint32_t *pMem122; // edi
  uint32_t *pMem13; // eax
  uint32_t *pMem132; // edi
  uint8_t *pMem14; // eax
  uint8_t *v43; // eax
  uint8_t *pMem15; // eax
  uint8_t *v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // eax
  char *pMem16; // eax
  char *v50; // eax
  int v51; // eax
  char *pMem17; // eax
  char *v53; // eax
  uint32_t *pMem18; // eax
  uint32_t *pMem182; // edi
  uint32_t *pMem19; // eax
  uint32_t *pMem192; // edi
  uint8_t *pMem20; // eax
  uint8_t *v59; // eax
  uint32_t *pMem21; // eax
  uint32_t *pMem212; // edi
  uint8_t *pMem22; // eax
  uint8_t *v63; // eax
  uint32_t *v64; // edi
  uint8_t *pMem23; // eax
  uint8_t *pMem232; // edi
  uint8_t *pMem24; // eax
  uint32_t *pMem242; // edi
  int i; // [esp+10h] [ebp-10h]
  int j; // [esp+10h] [ebp-10h]

  v2 = Block + 8;  // 计算 v2 = Block + 8
  for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    pMem = operator new(0x68u);  // 堆分配
    if ( pMem != nullptr )
      v4 = sub_426BD0(pMem);  // sub_426BD0 —— nengine::IControl 构造
    else
      v4 = nullptr;
    *v2++ = v4;
  }
  pMem2 = (char *)operator new(0x5B4u);  // 堆分配
  if ( pMem2 != nullptr )
    v6 = sub_44D530(pMem2, Block);  // sub_44D530 —— CNRDBaseInterface 虚表起步的大型界面对象构造（自证 vftable）
  else
    v6 = nullptr;
  *((uint32_t *)Block + 4) = v6;  // 写字段 Block+4（pHostObj）
  sub_69A840(*((uint32_t *)v6 + 2));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  v7 = Block + 20;  // 计算 v7 = Block + 20
  for ( j = 2; j != 0; --j )  // 遍历计次循环（j != 0）
  {
    pMem3 = operator new(0x68u);  // 堆分配
    if ( pMem3 != nullptr )
      v9 = sub_426BD0(pMem3);  // sub_426BD0 —— nengine::IControl 构造
    else
      v9 = nullptr;
    *v7++ = v9;
  }
  sub_69A840(*((uint32_t *)Block + 5));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  if ( operator new(0x720u) != nullptr )  // 堆分配
    v10 = sub_44BDA0(Block);  // sub_44BDA0 —— CNRDChatting 构造
  else
    v10 = 0;
  *((uint32_t *)Block + 7) = v10;  // 写字段 Block+7（uPathTerm）
  pMem4 = operator new(0x184u);  // 堆分配
  if ( pMem4 != nullptr )
    v12 = sub_44FF60(pMem4, Block);  // sub_44FF60 —— CNRDPVPInterface 构造
  else
    v12 = nullptr;
  *((uint32_t *)Block + 8) = v12;  // 写字段 Block+8（nSkillRec8）
  sub_69A840(v12[6]);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  if ( operator new(0x108u) != nullptr )  // 堆分配
    v13 = sub_44DA60(Block);  // sub_44DA60 —— CNRDWarRoomInterface 构造
  else
    v13 = 0;
  *((uint32_t *)Block + 9) = v13;  // 写字段 Block[9]（宽4字节）
  sub_69A840(*(uint32_t *)(v13 + 24));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  if ( operator new(0xF0u) != nullptr )  // 堆分配
    v14 = sub_44ACE0(Block);  // sub_44ACE0 —— CNRDCommunityMenu 构造
  else
    v14 = 0;
  *((uint32_t *)Block + 10) = v14;  // 写字段 Block[10]（宽4字节）
  sub_69A840(*(uint32_t *)(v14 + 8));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem5 = operator new(0x68u);  // 堆分配
  if ( pMem5 != nullptr )
    v16 = sub_426BD0(pMem5);  // sub_426BD0 —— nengine::IControl 构造
  else
    v16 = nullptr;
  *((uint32_t *)Block + 30) = v16;  // 写字段 Block[30]（宽4字节）
  sub_69A840(v16);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem6 = operator new(0x44u);  // 堆分配
  pMem62 = pMem6;
  if ( pMem6 != nullptr )
  {
    *(uint32_t *)pMem6 = &CNRDTutorial::`vftable';  // 构造装配 vftable：CNRDTutorial
    v17[24] = 0;
    *((uint32_t *)v17 + 5) = &off_6C2B88;  // 写字段 v17[5]（宽4字节）
    *((uint32_t *)v17 + 7) = 0;  // 写字段 v17+7（uPathTerm）
    v17[32] = 1;
    v17[34] = 0;
    v17[33] = 0;
    *((uint32_t *)v17 + 11) = 0;  // 写字段 v17[11]（宽4字节）
    *((uint32_t *)v17 + 10) = 0;  // 写字段 v17[10]（宽4字节）
    *((uint32_t *)v17 + 9) = 0;  // 写字段 v17[9]（宽4字节）
    sub_546030(v17);  // sub_546030 —— 22 行小辅助
    sub_546F30(Block);  // sub_546F30 —— 引导清理（426BD0 + 698F90）
  }
  else
  {
    v18 = nullptr;
  }
  *((uint32_t *)Block + 11) = v18;  // 写字段 Block[11]（宽4字节）
  sub_69A840(*((uint32_t *)v18 + 2));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  if ( operator new(0xE0u) != nullptr )  // 堆分配
    v19 = sub_44E000(Block);  // sub_44E000 —— CNRDPopupMenu 构造
  else
    v19 = 0;
  *((uint32_t *)Block + 12) = v19;  // 写字段 Block+12（nSkillRec12）
  sub_69A840(*(uint32_t *)(v19 + 48));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  v20 = operator new(0x68u);  // 堆分配
  if ( v20 != nullptr )
    v21 = sub_426BD0(v20);  // sub_426BD0 —— nengine::IControl 构造
  else
    v21 = nullptr;
  *((uint32_t *)Block + 13) = v21;  // 写字段 Block[13]（宽4字节）
  sub_69A840(v21);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  v22 = operator new(0x3Cu);  // 堆分配
  v23 = v22;
  if ( v22 != nullptr )
  {
    *v22 = &off_6C64BC;  // 装虚表/取地址：← off_6C64BC
    sub_540330(v22);  // sub_540330 —— 13 行小辅助
    sub_540340(Block, 1);  // sub_540340 —— 12 行小辅助
    *v23 = &CNRDItemInventoryWindow::`vftable';  // 构造装配 vftable：CNRDItemInventoryWindow
    sub_546FD0(pMem82);  // sub_546FD0 —— 21 行小辅助
    sub_5481A0(pMem82);  // sub_5481A0 —— 物品栏页绘制（153 行：43C250/43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0 + 699E20/699E40）
  }
  else
  {
    pMem82 = nullptr;
  }
  *((uint32_t *)Block + 14) = pMem82;  // 写字段 Block[14]（宽4字节）
  pMem9 = operator new(0x34u);  // 堆分配
  pMem92 = pMem9;
  if ( pMem9 != nullptr )
  {
    *pMem9 = &off_6C64BC;  // 装虚表/取地址：← off_6C64BC
    sub_540330(pMem9);  // sub_540330 —— 13 行小辅助
    sub_540340(Block, 1);  // sub_540340 —— 12 行小辅助
    *pMem92 = &CNRDAvatarInventoryWindow::`vftable';  // 构造装配 vftable：CNRDAvatarInventoryWindow
    sub_54ABC0(v25);  // sub_54ABC0 —— 19 行小辅助
    sub_549AC0(v25);  // sub_549AC0 —— 时装栏页绘制（94 行：43C250/43C410/69A5F0/69A840 + 69C980/43C4D0/43C630）
  }
  else
  {
    v25 = nullptr;
  }
  *((uint32_t *)Block + 15) = v25;  // 写字段 Block[15]（宽4字节）
  if ( operator new(0xE4u) != nullptr )  // 堆分配
    v26 = sub_44B2E0(Block);  // sub_44B2E0 —— CNRDItemTradeWindow 构造（双参数块）
  else
    v26 = 0;
  *((uint32_t *)Block + 16) = v26;  // 写字段 Block+16（nChannelTypeSel）
  if ( operator new(0x148u) != nullptr )  // 堆分配
    v27 = sub_44DC90(Block);  // sub_44DC90 —— CNRDSkillBuyWindow 构造
  else
    v27 = 0;
  *((uint32_t *)Block + 17) = v27;  // 写字段 Block+17（bEnable）
  v28 = operator new(0x34u);  // 堆分配
  v29 = v28;
  if ( v28 != nullptr )
  {
    *v28 = &off_6C64BC;  // 装虚表/取地址：← off_6C64BC
    sub_540330(v28);  // sub_540330 —— 13 行小辅助
    sub_540340(Block, 1);  // sub_540340 —— 12 行小辅助
    *v29 = &CNRDSkillInventoryWindow::`vftable';  // 构造装配 vftable：CNRDSkillInventoryWindow
    sub_54ABC0(pMem102);  // sub_54ABC0 —— 19 行小辅助
    sub_54B4E0(pMem102);  // sub_54B4E0 —— 技能栏页绘制（98 行：43C250/43C410/69A5F0/69A840 + 46F7A0/46F880 + 69CE50/426BD0/69C780）
  }
  else
  {
    pMem102 = nullptr;
  }
  *((uint32_t *)Block + 18) = pMem102;  // 写字段 Block+18（bDragChild）
  if ( operator new(0x50u) != nullptr )  // 堆分配
    v30 = sub_44B550(Block);  // sub_44B550 —— CNRDStatusWindow 构造
  else
    v30 = 0;
  *((uint32_t *)Block + 19) = v30;  // 写字段 Block[19]（宽4字节）
  if ( operator new(0xC0u) != nullptr )  // 堆分配
    v31 = sub_44F7B0(Block);  // sub_44F7B0 —— CNRDItemShopWindow 构造
  else
    v31 = 0;
  *((uint32_t *)Block + 20) = v31;  // 写字段 Block+20（nPage）
  if ( operator new(0xD4u) != nullptr )  // 堆分配
    v32 = sub_44E440(Block);  // sub_44E440 —— CNRDQuestListWindow 构造
  else
    v32 = 0;
  *((uint32_t *)Block + 21) = v32;  // 写字段 Block+21（bArmorState）
  if ( operator new(0xD8u) != nullptr )  // 堆分配
    v33 = sub_44DDF0(Block);  // sub_44DDF0 —— CNRDQuestInfoWindow 构造
  else
    v33 = 0;
  *((uint32_t *)Block + 22) = v33;  // 写字段 Block[22]（宽4字节）
  if ( operator new(0x98u) != nullptr )  // 堆分配
    v34 = sub_44B750(Block);  // sub_44B750 —— CNRDItemToolWindow 构造
  else
    v34 = 0;
  *((uint32_t *)Block + 24) = v34;  // 写字段 Block+24（nPageMax）
  if ( operator new(0x114u) != nullptr )  // 堆分配
    v35 = sub_44F9B0(Block);  // sub_44F9B0 —— CNRDItemProductWindow 构造
  else
    v35 = 0;
  *((uint32_t *)Block + 25) = v35;  // 写字段 Block[25]（宽4字节）
  *((uint32_t *)Block + 23) = 0;  // 写字段 Block[23]（宽4字节）
  sub_541AD0((int)(Block + 92));  // Block+92〔pFxObjC(推断)〕
  pMem11 = operator new(0x40u);  // 堆分配
  pMem112 = pMem11;
  if ( pMem11 != nullptr )
  {
    *pMem11 = &off_6C64BC;  // 装虚表/取地址：← off_6C64BC
    sub_540330(pMem11);  // sub_540330 —— 13 行小辅助
    sub_540340(Block, 0);  // sub_540340 —— 12 行小辅助
    *pMem112 = &CNRDPrivateStoreWindow::`vftable';  // 构造装配 vftable：CNRDPrivateStoreWindow
    sub_541900(v37);  // 【CNRDPrivateStoreWindow__vmt64】
    sub_544250(v37);  // 【CNRDPrivateStoreWindow__vmt68】
    *v37 = &CNRDPrivateStoreWindow_Display::`vftable';  // 构造装配 vftable：CNRDPrivateStoreWindow_Display
    sub_542360(pMem112);  // 【CNRDPrivateStoreWindow_Display__vmt64】
    sub_543190(pMem112);  // 【CNRDPrivateStoreWindow_Display__vmt68】
  }
  pMem12 = operator new(0x30u);  // 堆分配
  pMem122 = pMem12;
  if ( pMem12 != nullptr )
  {
    *pMem12 = &off_6C64BC;  // 装虚表/取地址：← off_6C64BC
    sub_540330(pMem12);  // sub_540330 —— 13 行小辅助
    sub_540340(Block, 0);  // sub_540340 —— 12 行小辅助
    *pMem122 = &CNRDPrivateStoreWindow::`vftable';  // 构造装配 vftable：CNRDPrivateStoreWindow
    sub_541900(v39);  // 【CNRDPrivateStoreWindow__vmt64】
    sub_544250(v39);  // 【CNRDPrivateStoreWindow__vmt68】
    *v39 = &CNRDPrivateStoreWindow_Sell::`vftable';  // 构造装配 vftable：CNRDPrivateStoreWindow_Sell
    sub_542470(pMem122);  // 调 : 清字段 this+44、this+40
    sub_5434F0(pMem122);  // 【CNRDPrivateStoreWindow_Sell__vmt68】
  }
  pMem13 = operator new(0x2Cu);  // 堆分配
  pMem132 = pMem13;
  if ( pMem13 != nullptr )
  {
    *pMem13 = &off_6C64BC;  // 装虚表/取地址：← off_6C64BC
    sub_540330(pMem13);  // sub_540330 —— 13 行小辅助
    sub_540340(Block, 0);  // sub_540340 —— 12 行小辅助
    *pMem132 = &CNRDPrivateStoreWindow::`vftable';  // 构造装配 vftable：CNRDPrivateStoreWindow
    sub_541900(v41);  // 【CNRDPrivateStoreWindow__vmt64】
    sub_544250(v41);  // 【CNRDPrivateStoreWindow__vmt68】
    *v41 = &CNRDPrivateStoreWindow_Buy::`vftable';  // 构造装配 vftable：CNRDPrivateStoreWindow_Buy
    sub_542480(pMem132);  // 调 : 清字段 this+40
    sub_5446F0(pMem132);  // 【CNRDPrivateStoreWindow_Buy__vmt68】
  }
  pMem14 = operator new(0x68u);  // 堆分配
  if ( pMem14 != nullptr )
    v43 = sub_426BD0(pMem14);  // sub_426BD0 —— nengine::IControl 构造
  else
    v43 = nullptr;
  *((uint32_t *)Block + 28) = v43;  // 写字段 Block+28（pPanelVec）
  *((uint32_t *)v43 + 17) = Block;  // 写字段 v43+17（bEnable）
  sub_69A840(*((uint32_t *)Block + 28));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem15 = operator new(0x68u);  // 堆分配
  if ( pMem15 != nullptr )
    v45 = sub_426BD0(pMem15);  // sub_426BD0 —— nengine::IControl 构造
  else
    v45 = nullptr;
  *((uint32_t *)Block + 31) = v45;  // 写字段 Block[31]（宽4字节）
  sub_69A840(v45);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  sub_69A840(*((uint32_t *)Block + 6));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  sub_69A840(*(uint32_t *)(*((uint32_t *)Block + 7) + 120));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  if ( operator new(0x6Cu) != nullptr )  // 堆分配
    v46 = sub_44AE70(Block);  // sub_44AE70 —— CNRDCountDown 构造
  else
    v46 = 0;
  *((uint32_t *)Block + 605) = v46;  // 写字段 Block[605]（宽4字节）
  sub_69A840(*(uint32_t *)(v46 + 8));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  if ( operator new(0x9Cu) != nullptr )  // 堆分配
    v47 = sub_44AFB0(Block, dword_99FD58);  // sub_44AFB0 —— CNRDWarRoomResult 构造
  else
    v47 = 0;
  *((uint32_t *)Block + 607) = v47;  // 写字段 Block[607]（宽4字节）
  sub_69A840(*(uint32_t *)(v47 + 48));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  if ( operator new(0x150u) != nullptr )  // 堆分配
    v48 = sub_44B0C0(Block, dword_99FD58);  // sub_44B0C0 —— CNRDResult 构造
  else
    v48 = 0;
  *((uint32_t *)Block + 608) = v48;  // 写字段 Block+608（nAttackGate）
  sub_69A840(*(uint32_t *)(v48 + 76));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem16 = (char *)operator new(0x298u);  // 堆分配
  if ( pMem16 != nullptr )
    v50 = sub_450340(pMem16, dword_99FD58);  // sub_450340 —— CNRDReward 构造：定时器组初始化
  else
    v50 = nullptr;
  *((uint32_t *)Block + 609) = v50;  // 写字段 Block[609]（宽4字节）
  sub_69A840(*((uint32_t *)v50 + 11));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  if ( operator new(0xBCu) != nullptr )  // 堆分配
    v51 = sub_44DBB0(Block);  // sub_44DBB0 —— CNRDPVPResult 构造
  else
    v51 = 0;
  *((uint32_t *)Block + 610) = v51;  // 写字段 Block[610]（宽4字节）
  sub_69A840(*(uint32_t *)(v51 + 68));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem17 = (char *)operator new(0x2794u);  // 堆分配
  if ( pMem17 != nullptr )
    v53 = sub_450620(pMem17, (int)Block);  // sub_450620 —— CNRDCashShop 构造：商城词条表装配
  else
    v53 = nullptr;
  *((uint32_t *)Block + 611) = v53;  // 写字段 Block[611]（宽4字节）
  sub_69A840(*((uint32_t *)v53 + 13));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem18 = operator new(0x24u);  // 堆分配
  pMem182 = pMem18;
  if ( pMem18 != nullptr )
  {
    *pMem18 = &CNRDSelectWarRoomArea::`vftable';  // 构造装配 vftable：CNRDSelectWarRoomArea
    sub_540370(v54);  // sub_540370 —— 窗口状态复位（+1/+5/+7 清零、+8=-1）
    sub_540670(v55);  // sub_540670 —— 世界地图绘制：资源 worldmap/arad.img（426BD0 图像 + 69C780/69A5F0/69A840 定位）
  }
  else
  {
    v55 = nullptr;
  }
  *((uint32_t *)Block + 633) = v55;  // 写字段 Block[633]（宽4字节）
  sub_69A840(v55[1]);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  v56 = operator new(0x5Cu);  // 堆分配
  v57 = v56;
  if ( v56 != nullptr )
  {
    sub_44E260(v56);  // sub_44E260 —— CNRDCharacterTalkBox 构造
    *v57 = &CNRDWarRoomBattleTalkBox::`vftable';  // 构造装配 vftable：CNRDWarRoomBattleTalkBox
    sub_49A9C0(pMem192);
    nullsub_3();  // 空桩函数（无操作）
  }
  else
  {
    pMem192 = nullptr;
  }
  *((uint32_t *)Block + 634) = pMem192;  // 写字段 Block[634]（宽4字节）
  sub_69A840(pMem192[1]);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem20 = operator new(0x68u);  // 堆分配
  if ( pMem20 != nullptr )
    v59 = sub_426BD0(pMem20);  // sub_426BD0 —— nengine::IControl 构造
  else
    v59 = nullptr;
  *((uint32_t *)Block + 32) = v59;  // 写字段 Block+32（nHeight）
  sub_69A840(v59);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem21 = operator new(0x4Cu);  // 堆分配
  pMem212 = pMem21;
  if ( pMem21 != nullptr )
  {
    *pMem21 = &CNRDStackNumberSet::`vftable';  // 构造装配 vftable：CNRDStackNumberSet
    sub_540890(v60);  // sub_540890 —— 数量输入辅助（28 行）
    sub_540AE0(Block);  // sub_540AE0 —— 摊位展示绘制（126 行：43C250/43C060/43C410 列表控件 + 426BD0/69C780 图像 + 4BF300）
  }
  else
  {
    v61 = nullptr;
  }
  *((uint32_t *)Block + 29) = v61;  // 写字段 Block[29]（宽4字节）
  sub_69A840(v61[2]);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  v62 = operator new(0x68u);  // 堆分配
  if ( v62 != nullptr )
    v63 = sub_426BD0(v62);  // sub_426BD0 —— nengine::IControl 构造
  else
    v63 = nullptr;
  *((uint32_t *)Block + 612) = v63;  // 写字段 Block[612]（宽4字节）
  *((uint32_t *)v63 + 17) = Block;  // 写字段 v63+17（bEnable）
  sub_69A840(*((uint32_t *)Block + 612));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  v64 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
                    dword_8F84B8,  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
                    "Common/Etc/MonoLayer.img");  // 资源 Common/Etc/MonoLayer.img
  *((uint32_t *)Block + 613) = sub_418DD0(v64, 2u);  // sub_418DD0 —— 资源句柄 (101)
  *(Block + 2468) = 0;  // 写字段 Block+2468 ← 0
  *((uint32_t *)Block + 622) = sub_418DD0(v64, 0);  // sub_418DD0 —— 资源句柄 (101)
  *((uint32_t *)Block + 624) = sub_418DD0(v64, 1u);  // sub_418DD0 —— 资源句柄 (101)
  v65 = operator new(0x40u);  // 堆分配
  v66 = v65;
  if ( v65 != nullptr )
  {
    *(uint32_t *)v65 = &CNRDCursor::`vftable';  // 构造装配 vftable：CNRDCursor
    pMem23[16] = 0;
    *((uint32_t *)pMem23 + 3) = &off_6C2B88;  // 写字段 pMem23[3]（宽4字节）
    *((uint32_t *)pMem23 + 5) = 0;  // 写字段 pMem23[5]（宽4字节）
    pMem23[24] = 1;
    pMem23[26] = 0;
    pMem23[25] = 0;
    *((uint32_t *)pMem23 + 9) = 0;  // 写字段 pMem23[9]（宽4字节）
    *((uint32_t *)pMem23 + 8) = 0;  // 写字段 pMem23+8（nSkillRec8）
    *((uint32_t *)pMem23 + 7) = 0;  // 写字段 pMem23+7（uPathTerm）
    sub_544FC0(pMem23);  // sub_544FC0 —— 18 行小辅助
    sub_545400(Block);  // sub_545400 —— 光标数据清理（426BD0 + 698F90）
  }
  else
  {
    pMem232 = nullptr;
  }
  *((uint32_t *)Block + 625) = pMem232;  // 写字段 Block[625]（宽4字节）
  pMem24 = operator new(0x94u);  // 堆分配
  pMem242 = pMem24;
  if ( pMem24 != nullptr )
  {
    sub_426BD0(pMem24);  // sub_426BD0 —— nengine::IControl 构造
    *pMem242 = &nengine::CNFrame::`vftable';  // vftable 复位
    sub_69C6B0(v68);  // 调 初始化 → ·vmt20(nArg2
    *v68 = &CNRDMakePriceWindow::`vftable';  // 构造装配 vftable：CNRDMakePriceWindow
    sub_5449A0(pMem242);  // sub_5449A0 —— 18 行小辅助
    sub_544E40(Block);  // sub_544E40 —— 定价窗口绘制（43C060/69A5F0/69A840/43C410 + 544A10，55 行）
  }
  else
  {
    pMem242 = nullptr;
  }
  return sub_69A840(pMem242[28]);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
}


// ------------------------------------------------------------
// 0x451750 sub_451750 —— 主管理器析构：同族对象逐项释放
// 对称释放 ·0x450C80 所建各族对象（含 450130/4504F0/450970 三析构），清理 71×2 组帧游标链，
// 末尾清 dword_9B8050 全局对象。
// ------------------------------------------------------------
void /*thiscall*/ sub_451750(int this)  // sub_451750 —— 主管理器析构：同族对象逐项释放
{
  uint32_t *pThis_8; // esi
  int i; // ebx
  void *fld_10; // esi
  uint32_t *pThis_14; // esi
  int j; // ebx
  void *fld_1C; // esi
  HGDIOBJ *fld_20; // esi
  HGDIOBJ *fld_24; // esi
  void *fld_28; // esi
  uint32_t *fld_2C; // esi
  HGDIOBJ *fld_30; // esi
  void (/*thiscall*/ ***pThis_34)(uint32_t, int); // ecx
  uint32_t *pThis_38; // esi
  int k; // ebx
  void (/*thiscall*/ ***pThis_70)(uint32_t, int); // ecx
  uint32_t *fld_74; // esi
  uint32_t *pThis_78; // esi
  int m; // ebx
  uint32_t *pThis_8C; // ebx
  uint32_t *ii; // esi
  uint32_t *jj; // esi
  void *fld_974; // esi
  void *fld_97C; // esi
  void *fld_980; // esi
  char *fld_984; // esi
  void **fld_988; // esi
  void **fld_98C; // esi
  uint32_t *fld_9E4; // esi
  uint32_t *fld_9E8; // esi
  void (/*thiscall*/ ***pThis_990)(uint32_t, int); // ecx
  uint32_t *fld_9C4; // esi
  int n; // [esp+Ch] [ebp-4h]

  pThis_8 = (uint32_t *)(this + 8);  // this+8〔nSkillRec8(推断)〕等 2 字段
  for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    if ( *pThis_8 != 0 )  // pThis_8=this+8 nSkillRec8
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_8)(*pThis_8, 1);  // pThis_8=this+8 nSkillRec8
    *pThis_8++ = 0;  // pThis_8=this+8 nSkillRec8
  }
  fld_10 = *(void **)(this + 16);  // this+64〔apServerTabBtn(推断)〕
  if ( fld_10 != nullptr )  // fld_10=this+64 apServerTabBtn
  {
    sub_44C4C0(*(char **)(this + 16));  // sub_44C4C0 —— CNRDBaseInterface 析构
    j__free(fld_10);  // 释放堆块
  }
  *(uint32_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
  pThis_14 = (uint32_t *)(this + 20);  // this+20〔nPage(推断)〕等 2 字段
  for ( j = 2; j != 0; --j )  // 遍历计次循环（j != 0）
  {
    if ( *pThis_14 != 0 )  // pThis_14=this+20 nPage
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_14)(*pThis_14, 1);  // pThis_14=this+20 nPage
    *pThis_14++ = 0;  // pThis_14=this+20 nPage
  }
  fld_1C = *(void **)(this + 28);  // this+112〔pHostComp112〕
  if ( fld_1C != nullptr )  // fld_1C=this+112 pHostComp112
  {
    sub_44BF40(*(uint32_t *)(this + 28));  // sub_44BF40 —— CNRDChatting 析构
    j__free(fld_1C);  // 释放堆块
  }
  fld_20 = *(HGDIOBJ **)(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
  *(uint32_t *)(this + 28) = 0;  // 写字段 this+28（pPanelVec） ← 0
  if ( fld_20 != nullptr )  // fld_20=this+128 szStatusKeyBuf
  {
    sub_450130(fld_20);  // sub_450130 —— CNRDPVPInterface 析构：句柄族回收
    j__free(fld_20);  // 释放堆块
  }
  fld_24 = *(HGDIOBJ **)(this + 36);  // this+144〔pFrameList144(推断)〕
  *(uint32_t *)(this + 32) = 0;  // 写字段 this+32（nHeight） ← 0
  if ( fld_24 != nullptr )  // fld_24=this+144 pFrameList144
  {
    sub_44C130(fld_24);  // sub_44C130 —— CNRDWarRoomInterface 析构
    j__free(fld_24);  // 释放堆块
  }
  fld_28 = *(void **)(this + 40);  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 36) = 0;  // 写字段 this+36（nStateWord36） ← 0
  if ( fld_28 != nullptr )  // fld_28=this+160 fAdd160
  {
    sub_44AD80(fld_28);  // sub_44AD80 —— CNRDCommunityMenu 析构
    j__free(fld_28);  // 释放堆块
  }
  fld_2C = *(uint32_t **)(this + 44);  // this+176〔pAppendVecCap(推断)〕
  *(uint32_t *)(this + 40) = 0;  // 写字段 this+40（bStateSub40） ← 0
  if ( fld_2C != nullptr )  // fld_2C=this+176 pAppendVecCap
  {
    sub_44AE20(fld_2C);  // sub_44AE20 —— CNRDTutorial 构造
    j__free(fld_2C);  // 释放堆块
  }
  fld_30 = *(HGDIOBJ **)(this + 48);  // this+192〔nDlgId(推断)〕
  *(uint32_t *)(this + 44) = 0;  // 写字段 this+44（nExpireMs） ← 0
  if ( fld_30 != nullptr )  // fld_30=this+192 nDlgId
  {
    sub_44C310(fld_30);  // sub_44C310 —— CNRDPopupMenu 析构
    j__free(fld_30);  // 释放堆块
  }
  pThis_34 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 52);  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48） ← 0
  if ( pThis_34 != nullptr )  // pThis_34=this+208 nField208
    (**pThis_34)(pThis_34, 1);  // 调 pThis_34 的虚函数（vt+0）
  *(uint32_t *)(this + 52) = 0;  // 写字段 this+52（bAuraState） ← 0
  pThis_38 = (uint32_t *)(this + 56);  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  for ( k = 12; k != 0; --k )  // 遍历计次循环（k != 0）
  {
    if ( *pThis_38 != 0 )  // pThis_38=this+56 pCmdVecCap56
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*pThis_38 + 4))(*pThis_38, 1);  // 虚调用 vt+4（pThis_38）对象赋值/迁移
    *pThis_38++ = 0;  // pThis_38=this+56 pCmdVecCap56
  }
  pThis_70 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 112);  // this+112〔pHostComp112〕
  if ( pThis_70 != nullptr )  // pThis_70=this+112 pHostComp112
    (**pThis_70)(pThis_70, 1);  // 调 pThis_70 的虚函数（vt+0）
  fld_74 = *(uint32_t **)(this + 116);  // this+116 观察者 vector 尾针
  *(uint32_t *)(this + 112) = 0;  // 写字段 this+112（pHostComp） ← 0
  if ( fld_74 != nullptr )  // fld_74=this+116 观察者 vector 尾针
  {
    *fld_74 = &CNRDStackNumberSet::`vftable';  // 构造装配 vftable：CNRDStackNumberSet
    sub_5408E0(v17);  // sub_5408E0 —— 数量输入辅助 2（50 行）
    j__free(v17);  // 释放堆块
  }
  *(uint32_t *)(this + 116) = 0;  // 写字段 this+116（pSessionCtx） ← 0
  v18 = (uint32_t *)(this + 120);  // this+120〔pAnimObj〕
  for ( m = 3; m != 0; --m )  // 遍历计次循环（m != 0）
  {
    if ( *v18 != 0 )  // v18=this+120 pAnimObj
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v18)(*v18, 1);  // v18=this+120 pAnimObj
    *v18++ = 0;  // v18=this+120 pAnimObj
  }
  v20 = (uint32_t *)(this + 140);  // this+140〔nAdd140(推断)〕
  for ( n = 71; n != 0; --n )  // 遍历计次循环（n != 0）
  {
    for ( ii = (uint32_t *)*(v20 - 1); ii != (uint32_t *)*v20; ++ii )  // v20=this+140 nAdd140
    {
      if ( *ii != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*ii + 4))(*ii, 1);  // 虚调用 vt+4（ii）对象赋值/迁移
      *ii = 0;
    }
    for ( jj = (uint32_t *)v20[283]; jj != (uint32_t *)v20[284]; ++jj )  // v20=this+140 nAdd140
    {
      if ( *jj != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*jj + 4))(*jj, 1);  // 虚调用 vt+4（jj）对象赋值/迁移
      *jj = 0;
    }
    v20 += 4;  // v20=this+140 nAdd140
  }
  v23 = *(void **)(this + 2420);
  if ( v23 != nullptr )
  {
    sub_44AF20(*(uint32_t *)(this + 2420));  // sub_44AF20 —— CNRDCountDown 析构
    j__free(v23);  // 释放堆块
  }
  v24 = *(void **)(this + 2428);
  *(uint32_t *)(this + 2420) = 0;  // 写字段 this+2420 ← 0
  if ( v24 != nullptr )
  {
    sub_44B060(v24);  // sub_44B060 —— CNRDWarRoomResult 析构
    j__free(v24);  // 释放堆块
  }
  v25 = *(void **)(this + 2432);
  *(uint32_t *)(this + 2428) = 0;  // 写字段 this+2428 ← 0
  if ( v25 != nullptr )
  {
    sub_44B160(v25);  // sub_44B160 —— CNRDResult 析构
    j__free(v25);  // 释放堆块
  }
  v26 = *(char **)(this + 2436);
  *(uint32_t *)(this + 2432) = 0;  // 写字段 this+2432 ← 0
  if ( v26 != nullptr )
  {
    sub_4504F0(v26);  // sub_4504F0 —— CNRDReward 析构：与构造对称
    j__free(v26);  // 释放堆块
  }
  v27 = *(void ***)(this + 2440);
  *(uint32_t *)(this + 2436) = 0;  // 写字段 this+2436 ← 0
  if ( v27 != nullptr )
  {
    sub_44CDE0(v27);  // sub_44CDE0 —— CNRDPVPResult 析构主体
    j__free(v27);  // 释放堆块
  }
  v28 = *(void ***)(this + 2444);
  *(uint32_t *)(this + 2440) = 0;  // 写字段 this+2440 ← 0
  if ( v28 != nullptr )
  {
    sub_450970(v28);  // sub_450970 —— CNRDCashShop 析构：对称释放
    j__free(v28);  // 释放堆块
  }
  v29 = *(uint32_t **)(this + 2532);
  *(uint32_t *)(this + 2444) = 0;  // 写字段 this+2444 ← 0
  if ( v29 != nullptr )
  {
    *v29 = &CNRDSelectWarRoomArea::`vftable';  // 构造装配 vftable：CNRDSelectWarRoomArea
    sub_540390(fld_9E4);  // sub_540390 —— 子窗口释放链：依次 vf+0 销毁 *(this+1)/(+5)/(+6) 三个子窗口
    j__free(fld_9E4);  // 释放堆块
  }
  fld_9E8 = *(uint32_t **)(this + 2536);
  *(uint32_t *)(this + 2532) = 0;  // 写字段 this+2532 ← 0
  if ( fld_9E8 != nullptr )
  {
    sub_44C8C0(fld_9E8);  // sub_44C8C0 —— 战房对话框析构
    j__free(fld_9E8);  // 释放堆块
  }
  pThis_990 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 2448);  // this+2448 当前窗口 id
  *(uint32_t *)(this + 2536) = 0;  // 写字段 this+2536 ← 0
  if ( pThis_990 != nullptr )
    (**pThis_990)(pThis_990, 1);  // 调 pThis_990 的虚函数（vt+0）
  fld_9C4 = *(uint32_t **)(this + 2500);
  *(uint32_t *)(this + 2448) = 0;  // 写字段 this+2448 ← 0
  if ( fld_9C4 != nullptr )
  {
    sub_44AC30(fld_9C4);  // sub_44AC30 —— CNRDCursor 构造
    j__free(fld_9C4);  // 释放堆块
  }
  *(uint32_t *)(this + 2500) = 0;  // 写字段 this+2500 ← 0
  if ( dword_9B8050 != 0 )  // dword_9B8050 —— 输入框取值
    (**(void (/*thiscall*/ ***)(int, int))dword_9B8050)(dword_9B8050, 1);  // dword_9B8050 —— 输入框取值
}


// ------------------------------------------------------------
// 0x451AD0 sub_451AD0
// ------------------------------------------------------------
// 世界地图交互：CLICK_BUTTON1（按钮音效自证）【推断：翻页/确认】
int /*thiscall*/ sub_451AD0(int *this)  // 实现：世界地图交互：CLICK_BUTTON1（按钮音效自证）(推断：翻页/确认)
{
  int fld_e26; // eax
  int pObj2; // esi
  int pObj; // ebx
  int fld_e27; // eax
  int result; // eax
  int pObj3; // esi
  int v8; // ebx
  int v9; // eax
  int v10; // edx
  int v11; // esi
  int v12; // eax
  char *v13; // eax
  char *v14; // eax
  int fld_e6322; // eax
  int fld_e632; // [esp-4h] [ebp-28h]
  int v17; // [esp+10h] [ebp-14h] BYREF
  int v18; // [esp+14h] [ebp-10h] BYREF
  int v19; // [esp+20h] [ebp-4h]

  fld_e26 = *(this + 26);  // 读字段 fld_e26 = this+26
  pObj2 = 0;
  pObj = 0;
  if ( fld_e26 != 12 )  // fld_e26=this+104 插值终点 Z
    pObj2 = *(this + fld_e26 + 14);  // fld_e26=this+104 插值终点 Z
  fld_e27 = *(this + 27);  // 读字段 fld_e27 = this+27
  if ( fld_e27 != 12 )  // fld_e27=this+108 第 1 组·宿主属性 +886 增量
    pObj = *(this + fld_e27 + 14);  // fld_e27=this+108 第 1 组·宿主属性 +886 增量
  result = sub_461B80(*(this + 4));  // sub_461B80 —— 队伍槽命中标志与本机上报
  if ( (uint8_t)result == 0
    && (pObj2 == 0 || (uint8_t)(result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 40))(pObj2)) == 0)  // 虚调用 vt+40（pObj2）条件查询(273等)
    && (pObj == 0 || (uint8_t)(result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 40))(pObj)) == 0) )  // 虚调用 vt+40（pObj）条件查询(273等)
  {
    if ( (unsigned int)*(this + 626) > 2 )
    {
      *(this + 626) = 0;  // 写字段 this+626 ← 0
      sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    }
    result = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 36);  // 虚调用 vt+120（dword_8F8520）转发(对象+缓冲)
    if ( *(uint8_t *)(result + 17) != 0 && dword_79BE38 == *(uint32_t *)(result + 12) && *(uint32_t *)(dword_8F7A24 + 12) == 1 )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    {
      pObj3 = dword_8F7C08;  // dword_8F7C08 —— 副玩家/观战
      if ( dword_8F7C08 != 0 )  // dword_8F7C08 —— 副玩家/观战
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C08 + 80))(dword_8F7C08);  // 虚调用 vt+80（dword_8F7C08）读 4 字节
        if ( result != 0 )
        {
          v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 80))(pObj3);  // 虚调用 vt+80（pObj3）读 4 字节
          v18 = sub_45E510(pt.x, 1);  // sub_45E510 —— 结果 = 与 ·sub_45E490 反向（层坐标 → 屏幕 y）
          v9 = sub_45E550(pt.y, 0, 1);  // sub_45E550 —— 结果 = 与 ·sub_45E4D0 配对的回换算（nArg2 + nArg3 - 120）
          v10 = *(uint32_t *)pObj3;
          v17 = v9;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(v10 + 136))(pObj3, v18, v9, 0) != 0  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
            || (uint8_t)(result = (*(int (/*thiscall*/ **)(int, int *, int *, int, int, int, uint32_t, int))(*(uint32_t *)pObj3 + 140))(  // 虚调用 vt+140（pObj3）日志(变参 printf)
                                  pObj3,
                                  &v18,
                                  &v17,
                                  v18,
                                  v17,
                                  100,
                                  0,
                                  1)) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 372))(pObj3, v18, v17);  // 虚调用 vt+372（pObj3）数值写入
            v11 = 0;
            byte_8F8118 = 1;
            sub_432EA0("CLICK_MOVE", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
            if ( *(this + 632) == 0 )
            {
              v12 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
              v19 = 0;
              if ( v12 != 0 )
                v11 = sub_431860(v12, "Common/Etc/Animation/MoveDestinationMark.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
              v19 = -1;
              v13 = (char *)sub_44B6C0(284);  // sub_44B6C0 —— 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
              v19 = 1;
              if ( v13 != nullptr )
                v14 = sub_44E1F0(v13, v11, 0);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
              else
                v14 = nullptr;
              v19 = -1;
              *(this + 632) = (int)v14;  // 写字段 this+632 ← (int)v14
            }
            if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 632) + 80))(*(this + 632)) != 0 )  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
            {
              fld_e632 = *(this + 632);  // 读字段 fld_e632 = this+632
              (*(void (**)(void))(*(uint32_t *)fld_e632 + 80))();  // 虚调用 vt+80（fld_e632）读 4 字节
              sub_45F1E0(fld_e632);  // sub_45F1E0 —— 对象注销/退场（递归，含 ELVEN_GATE 检查）
            }
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*(this + 632) + 112))(  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
              *(this + 632),
              v18,
              v17,
              0);
            sub_45FE80(v8, (int)this, 2, 0, *(this + 632), 0, 0);  // sub_45FE80 —— 对象注册
            fld_e6322 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 632) + 200))(*(this + 632));  // 调虚槽 +200：取动画对象
            return sub_4926A0(fld_e6322);  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x451D50 sub_451D50
// ------------------------------------------------------------
// 主管理器 tick（docs/13 §2：主帧循环 sub_433690 调 sub_451D50(0x8F8528)）——
// 全 UI/窗口管理器心跳；快门特性横幅去重亦经此路径（docs/13 §2）
void /*thiscall*/ sub_451D50(int this)  // sub_451D50 —— 主管理器 tick
{
  int v1; // ebx
  int fld_4; // eax
  bool fld_42; // sf
  int fld_43; // eax
  int fld_6C; // eax
  int pThis_4; // edi
  int v8; // eax
  int fld_68; // eax
  int pThis_42; // edi
  int v11; // eax
  uint32_t *pThis_68; // edi
  int i; // ebx
  uint32_t *pThis_8C; // ebx
  uint32_t *k; // edi
  void *fld_968; // eax
  uint32_t *m; // edi
  int fld_682; // eax
  int pThis_43; // ecx
  int pThis_44; // edi
  int fld_6C2; // eax
  int fld_683; // eax
  int pThis_45; // edi
  int pThis_46; // ebx
  int fld_6C3; // eax
  int fld_9C8; // eax
  char byte_89D2752; // bl
  int fld_684; // eax
  int pThis_47; // ecx
  int pThis_48; // edi
  int fld_6C4; // eax
  int fld_685; // eax
  int pThis_49; // ecx
  int pThis_410; // edi
  int fld_6C5; // eax
  int v36; // eax
  int pObj2; // eax
  int pObj22; // edi
  int v39; // edi
  int v40; // ebx
  char v41; // al
  int v42; // eax
  int pObj; // eax
  int pObj3; // edi
  int v45; // eax
  int v46; // ecx
  int fld_30; // ecx
  uint32_t *pThis_682; // ebx
  int pThis_411; // edi
  int v50; // eax
  int fld_74; // ecx
  int ii; // edi
  int pThis_88; // ecx
  int fld_1C; // ecx
  int v55; // eax
  uint32_t *Block; // [esp+10h] [ebp-24h]
  uint32_t *v57; // [esp+14h] [ebp-20h]
  int v58; // [esp+1Ch] [ebp-18h]
  int j; // [esp+20h] [ebp-14h]
  int *v60; // [esp+20h] [ebp-14h]
  int n; // [esp+20h] [ebp-14h]
  char byte_89D2742; // [esp+27h] [ebp-Dh]
  char v63; // [esp+27h] [ebp-Dh]
  char v64; // [esp+27h] [ebp-Dh]

  v1 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  if ( *(uint8_t *)(*(uint32_t *)(this + 28) + 256) == 0  // this+28〔pPanelVec(推断)〕等 2 字段
    && (v1 == 3 || v1 == 6)  // 主管理器析构：同族对象逐项释放
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, 10) == 0  // 虚调用 vt+20（dword_79C0B4）条件位掩码测试(273受击/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 31) != 0 )  // 虚调用 vt+16（dword_79C0B4 虚表槽）
  {
    fld_4 = *(uint32_t *)(this + 4) + 1;  // this+4〔宿主对象〕等 2 字段
    fld_42 = *(uint32_t *)(this + 4) - 1 < 0;  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 4) = fld_4;  // 写字段 this+4（pHostObj） ← fld_4
    if ( !(fld_42 ^ __OFSUB__(fld_4, 2) | (fld_4 == 2)) )  // fld_42=this+4 宿主对象
      *(uint32_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  }
  if ( v1 != 3 && v1 != 6 )
    *(uint32_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
  if ( fld_43 == 1 || fld_43 == 2 )  // fld_43=this+4 pHostObj
  {
    if ( *(uint32_t *)(this + 56) != 0 || *(uint32_t *)(this + 60) != 0 )  // this+56〔pCmdVecCap56(推断)〕等 4 字段
    {
      fld_6C = *(uint32_t *)(this + 108);  // 读字段 fld_6C = this+108（nAdd108）
      if ( fld_6C != 12 )  // fld_6C=this+108 nAdd108
      {
        pThis_4 = *(uint32_t *)(this + 4 * fld_6C + 56);  // fld_6C=this+108 nAdd108
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_4 + 48))(pThis_4);  // 虚调用 vt+48（pThis_4）归属坐标x
        sub_69A580(v8);  // 调 注销其资源后
        *(uint32_t *)(this + 108) = 12;  // 写字段 this+108（nAdd108） ← 12
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pThis_4 + 16))(pThis_4);  // 虚调用 vt+16（pThis_4 虚表槽）
      }
    }
    if ( *(uint32_t *)(this + 76) != 0 )  // this+76〔pBtnActionE〕
    {
      fld_68 = *(uint32_t *)(this + 104);  // 读字段 fld_68 = this+104（nTimerEnd）
      if ( fld_68 != 12 )  // fld_68=this+104 nTimerEnd
      {
        pThis_42 = *(uint32_t *)(this + 4 * fld_68 + 56);  // fld_68=this+104 nTimerEnd
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_42 + 48))(pThis_42);  // 虚调用 vt+48（pThis_42）归属坐标x
        sub_69A580(v11);  // 调 注销其资源后
        *(uint32_t *)(this + 104) = 12;  // 写字段 this+104（nTimerEnd） ← 12
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pThis_42 + 16))(pThis_42);  // 虚调用 vt+16（pThis_42 虚表槽）
      }
    }
    sub_44E850((uint32_t *)this, 18);  // sub_44E850 —— 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
    sub_44E850((uint32_t *)this, 26);  // sub_44E850 —— 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
  }
  sub_463FB0(*(uint32_t *)(this + 16));  // sub_463FB0 —— 快捷栏逐帧刷新（悬停/点击/商店/任务）
  sub_441750(*(uint32_t *)(this + 28));  // this+28〔pPanelVec(推断)〕等 2 字段
  sub_52BBB0(*(uint32_t *)(this + 32));  // this+32〔nHeight(推断)〕等 2 字段
  sub_49CBD0(*(uint32_t *)(this + 36));  // sub_49CBD0 —— CLICK_BUTTON2 事件分发（音效 sub_432EA0、sub_48FCA0/48FC30）
  if ( *(uint32_t *)(this + 4) != 0 || v1 != 6 )  // this+4 宿主对象
  {
    sub_49CD70(0);  // sub_49CD70 —— CLICK_BUTTON2 可见切换（+24 主件 + 22×槽号 联动移位）
  }
  else if ( *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 32) <= 1u )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  {
    sub_49CD70(1);  // sub_49CD70 —— CLICK_BUTTON2 可见切换（+24 主件 + 22×槽号 联动移位）
  }
  sub_545800(*(uint32_t *)(this + 40));  // sub_545800 —— 输入确认（CLICK_BUTTON1 音 + 545510/545590/545610）
  nullsub_3(*(uint32_t *)(this + 44));  // this+44〔nExpireMs(推断)〕等 2 字段
  sub_526070(*(uint32_t *)(this + 48));  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  pThis_68 = (uint32_t *)(this + 104);  // this+104〔nTimerEnd(推断)〕
  for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    if ( *pThis_68 != 12 )  // pThis_68=this+104 nTimerEnd
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4 * *pThis_68 + 56) + 8))(*(uint32_t *)(this + 4 * *pThis_68 + 56));  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BUTT…
    ++pThis_68;  // 计数自增 pThis_68
  }
  sub_541620(*(uint32_t *)(this + 116));  // sub_541620 —— 摊位点击处理：CLICK_BUTTON2 + 69A650 显示 + 69B740/69BD90 输入 + 541190/5409C0 联动
  pThis_8C = (uint32_t *)(this + 140);  // this+140〔nAdd140(推断)〕
  for ( j = 71; j != 0; --j )  // 遍历计次循环（j != 0）
  {
    for ( k = (uint32_t *)*(pThis_8C - 1); k != (uint32_t *)*pThis_8C; ++k )  // pThis_8C=this+140 nAdd140
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*k + 8))(*k);  // 虚调用 vt+8（k 虚表槽）
    pThis_8C += 4;  // pThis_8C=this+140 nAdd140
  }
  sub_44D490(this + 2404);  // sub_44D490 —— 4 字节元素容器整体拷贝赋值
  fld_968 = *(void **)(this + 2408);
  if ( fld_968 != nullptr )
    j__free(fld_968);  // 释放堆块
  *(uint32_t *)(this + 2408) = 0;  // 写字段 this+2408 ← 0
  *(uint32_t *)(this + 2412) = 0;  // 写字段 this+2412 ← 0
  *(uint32_t *)(this + 2416) = 0;  // 写字段 this+2416 ← 0
  for ( m = Block; m != v57; ++m )  // 遍历计次循环（m != v57）
    sub_44E780(*m);  // sub_44E780 —— 对象池归位（活动对象回收）
  sub_49E0E0(*(uint32_t *)(this + 2428));  // sub_49E0E0 —— 结算阶段计时推进（阶段计数归零且满 4000ms → ·sub_49E050(+1)）
  sub_4773B0(*(uint32_t *)(this + 2432));  // 调 (this, 步骤+1) 进入下一步骤
  sub_457010(*(uint32_t *)(this + 2436));  // sub_457010 —— 场景类型联动标志
  sub_54F9B0(*(uint32_t *)(this + 2440));  // sub_54F9B0 —— 结算触发 2（699000 + 54F540）
  sub_561E10(*(uint32_t *)(this + 2444));  // sub_561E10 —— 商城窗口刷新汇总（55D0F0/55E050/5607D0/55C6E0/55C860/699000）
  sub_540420(*(uint32_t *)(this + 2532));  // sub_540420 —— 按钮点击处理：CLICK_BUTTON2 音 + 44E8D0/44E850 对象登记/切换（53 行）
  sub_544FE0(*(uint32_t *)(this + 2500));  // sub_544FE0 —— 光标辅助（699000 时钟）
  byte_89D2742 = byte_89D274;  // byte_89D2742 —— [esp+27h] [ebp-Dh]
  if ( byte_89D274 != 0 )  // byte_89D274 —— 非拖拽态：SendMessageA WM_NCLBUTTONDOWN 拖标题栏
  {
    fld_682 = *(uint32_t *)(this + 104);  // 读字段 fld_682 = this+104（nTimerEnd）
    pThis_43 = 0;
    pThis_44 = 0;
    if ( fld_682 != 12 )  // fld_682=this+104 nTimerEnd
      pThis_43 = *(uint32_t *)(this + 4 * fld_682 + 56);  // fld_682=this+104 nTimerEnd
    fld_6C2 = *(uint32_t *)(this + 108);  // 读字段 fld_6C2 = this+108（nAdd108）
    if ( fld_6C2 != 12 )  // fld_6C2=this+108 nAdd108
      pThis_44 = *(uint32_t *)(this + 4 * fld_6C2 + 56);  // fld_6C2=this+108 nAdd108
    if ( (pThis_43 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pThis_43 + 24))(pThis_43) == 0) && pThis_44 != 0 )  // 虚调用 vt+24（pThis_43）（析构，参 1）与 8（Release）释放后 GlobalFree 并 SetWindowLongA 摘除 —— 与 ·0x6528C0 挂载配对。
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pThis_44 + 24))(pThis_44);  // 虚调用 vt+24（pThis_44）（析构，参 1）与 8（Release）释放后 GlobalFree 并 SetWindowLongA 摘除 —— 与 ·0x6528C0 挂载配对。
  }
  if ( *(uint8_t *)(this + 2524) != byte_89D2742 )  // byte_89D2742 —— [esp+27h] [ebp-Dh]
  {
    if ( byte_89D2742 != 0 )  // byte_89D2742 —— [esp+27h] [ebp-Dh]
    {
      fld_683 = *(uint32_t *)(this + 104);  // 读字段 fld_683 = this+104（nTimerEnd）
      pThis_45 = 0;
      pThis_46 = 0;
      if ( fld_683 != 12 )  // fld_683=this+104 nTimerEnd
        pThis_45 = *(uint32_t *)(this + 4 * fld_683 + 56);  // fld_683=this+104 nTimerEnd
      fld_6C3 = *(uint32_t *)(this + 108);  // 读字段 fld_6C3 = this+108（nAdd108）
      if ( fld_6C3 != 12 )  // fld_6C3=this+108 nAdd108
        pThis_46 = *(uint32_t *)(this + 4 * fld_6C3 + 56);  // fld_6C3=this+108 nAdd108
      if ( (uint8_t)sub_460830(*(uint32_t *)(this + 16)) == 0  // sub_460830 —— 悬停对象拾取/交互触发
        && (pThis_45 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pThis_45 + 20))(pThis_45) == 0)  // 虚调用 vt+20（pThis_45）条件位掩码测试(273受击/17有血/65机械)
        && pThis_46 != 0 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pThis_46 + 20))(pThis_46);  // 虚调用 vt+20（pThis_46）条件位掩码测试(273受击/17有血/65机械)
      }
    }
    else
    {
      sub_44FC40(this);  // sub_44FC40 —— NPC 交互主分发（点击/输入状态机）
      fld_9C8 = *(uint32_t *)(this + 2504);  // 读字段 fld_9C8 = this+2504
      if ( fld_9C8 == 1 || fld_9C8 == 2 )
      {
        *(uint32_t *)(this + 2504) = 0;  // 写字段 this+2504 ← 0
        *(uint32_t *)(this + 2508) = 12;  // 写字段 this+2508 ← 12
        *(uint32_t *)(this + 2512) = 0;  // 写字段 this+2512 ← 0
        *(uint32_t *)(this + 2516) = 0;  // 写字段 this+2516 ← 0
        *(uint32_t *)(this + 2520) = 0;  // 写字段 this+2520 ← 0
      }
    }
    *(uint8_t *)(this + 2524) = byte_89D2742;  // byte_89D2742 —— [esp+27h] [ebp-Dh]
  }
  byte_89D2752 = byte_89D275;  // byte_89D2752 —— [esp+7h] [ebp-1h]
  if ( byte_89D275 != 0 )
  {
    fld_684 = *(uint32_t *)(this + 104);  // 读字段 fld_684 = this+104（nTimerEnd）
    pThis_47 = 0;
    pThis_48 = 0;
    if ( fld_684 != 12 )  // fld_684=this+104 nTimerEnd
      pThis_47 = *(uint32_t *)(this + 4 * fld_684 + 56);  // fld_684=this+104 nTimerEnd
    fld_6C4 = *(uint32_t *)(this + 108);  // 读字段 fld_6C4 = this+108（nAdd108）
    if ( fld_6C4 != 12 )  // fld_6C4=this+108 nAdd108
      pThis_48 = *(uint32_t *)(this + 4 * fld_6C4 + 56);  // fld_6C4=this+108 nAdd108
    if ( (pThis_47 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pThis_47 + 36))(pThis_47) == 0) && pThis_48 != 0 )  // 虚调用 vt+36（pThis_47 虚表槽）
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pThis_48 + 36))(pThis_48);  // 虚调用 vt+36（pThis_48 虚表槽）
  }
  if ( *(uint8_t *)(this + 2525) != byte_89D2752 )  // byte_89D2752 —— [esp+7h] [ebp-1h]
  {
    if ( byte_89D2752 != 0 )  // byte_89D2752 —— [esp+7h] [ebp-1h]
    {
      fld_685 = *(uint32_t *)(this + 104);  // 读字段 fld_685 = this+104（nTimerEnd）
      pThis_49 = 0;
      pThis_410 = 0;
      if ( fld_685 != 12 )  // fld_685=this+104 nTimerEnd
        pThis_49 = *(uint32_t *)(this + 4 * fld_685 + 56);  // fld_685=this+104 nTimerEnd
      fld_6C5 = *(uint32_t *)(this + 108);  // 读字段 fld_6C5 = this+108（nAdd108）
      if ( fld_6C5 != 12 )  // fld_6C5=this+108 nAdd108
        pThis_410 = *(uint32_t *)(this + 4 * fld_6C5 + 56);  // fld_6C5=this+108 nAdd108
      if ( (pThis_49 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pThis_49 + 32))(pThis_49) == 0) && pThis_410 != 0 )  // 虚调用 vt+32（pThis_49 虚表槽）
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pThis_410 + 32))(pThis_410);  // 虚调用 vt+32（pThis_410 虚表槽）
    }
    else
    {
      sub_451AD0(this);  // 调 世界地图交互：CLICK_BUTTON1（按钮音效自证）(推断：翻页/确认)
    }
    *(uint8_t *)(this + 2525) = byte_89D2752;  // byte_89D2752 —— [esp+7h] [ebp-1h]
  }
  v36 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  if ( v36 == 1 )
  {
    if ( (uint8_t)sub_4BFBC0(&unk_8F85B4, 0) != 0 )  // sub_4BFBC0 —— 列表登记与状态判定
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 虚调用 vt+120（dword_8F8520）转发(对象+缓冲)
      pObj2 = sub_45E9B0(dword_8F7C08);  // sub_45E9B0 —— 点选最近对象（50x50 判定框）
      pObj22 = pObj2;
      if ( pObj2 != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 34) != 0 )  // 虚调用 vt+40（pObj2）条件查询(273等)
          sub_567F40(0);  // sub_567F40 —— NPC 商店/任务联动（546840 引导 + 472E30/44E8D0/522E20/47CC80/5E5260/461730/463ED0/463F10/5540D0/44BBA0/552BD0/526BF0，126 行）
        else
          sub_526BF0(pObj22, 0);  // 调 与 ·sub_567F40 联动
      }
    }
    goto LABEL_118;
  }
  if ( v36 != 3 )
  {
    if ( v36 != 6 )
      goto LABEL_118;
    if ( (uint8_t)sub_42B560(*(uint32_t *)(dword_8F7A24 + 40)) == 0 )  // sub_42B560 —— 类别子集判定（2/3）
      goto LABEL_118;
    if ( (uint8_t)sub_4BFBC0(&unk_8F85B4, 0) == 0 )  // sub_4BFBC0 —— 列表登记与状态判定
      goto LABEL_118;
    pObj3 = dword_8F7C04;  // 本地玩家对象
    if ( dword_8F7C04 == 0  // dword_8F7C04（本地玩家对象）
      || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1196))(dword_8F7C04) == 0 )  // 虚调用 vt+1196（dword_8F7C04 虚表槽）
    {
      goto LABEL_118;
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4)) != 0 )  // 角色/物品栏管理器
    {
LABEL_106:
      v45 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 52))(pObj3);  // 虚调用 vt+52（pObj3）归属坐标y
      sub_486D40(v45);  // sub_486D40 —— 请求 op 44（地图技能判定【推断】）
      goto LABEL_118;
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) < (unsigned int)dword_795210 )  // 角色/物品栏管理器
      goto LABEL_118;
    v46 = *((uint32_t *)dword_8F8528 + 611);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
LABEL_117:
    sub_55D210(v46);  // sub_55D210 —— 商城确认参数（49BE70/422E70/43BEE0 + 423200/423290/423380，40 行）
    goto LABEL_118;
  }
  if ( *(uint32_t *)(*(uint32_t *)(this + 2432) + 4) == 0
    && *(uint32_t *)(*(uint32_t *)(this + 2436) + 4) == 0
    && *(uint32_t *)(*(uint32_t *)(this + 2440) + 8) == 0 )
  {
    v39 = 0;
    v40 = 16;
    v60 = &dword_77FD48;  // 取全局对象/数组首址（v60 ← dword_77FD48）
    do
    {
      v41 = sub_4BF250(v60);  // sub_4BF250 —— 结果 = 槽查询（+64 表）
      v63 = v41;
      if ( *(uint8_t *)(this + v39 + 2424) == 0 && v41 != 0 && v39 != sub_456420(dword_8F850C) )  // sub_456420 —— 存 座位查找
      {
        v42 = *(uint32_t *)(v40 + dword_8F850C);  // dword_8F850C —— 队伍槽重置 4 槽 +188 解锁清空 → 自身
        v58 = v42;
        if ( v42 != 0 )
        {
          pObj = *(uint32_t *)(v42 + 196);  // 读字段 pObj = v42+196
          if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1196))(pObj) != 0 )  // 虚调用 vt+1196（pObj 虚表槽）
            sub_486D40(*(uint16_t *)(v58 + 4));  // sub_486D40 —— 请求 op 44（地图技能判定【推断】）
        }
      }
      *(uint8_t *)(this + v39 + 2424) = v63;
      v40 += 4;
      ++v39;  // 计数自增 v39
      v60 += 2;
    }
    while ( v40 < 32 );  // 循环直到 v40 < 32
    if ( (uint8_t)sub_4BFBC0(&unk_8F85B4, 0) != 0 )  // sub_4BFBC0 —— 列表登记与状态判定
    {
      pObj3 = dword_8F7C04;  // 本地玩家对象
      if ( dword_8F7C04 != 0  // dword_8F7C04（本地玩家对象）
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1196))(dword_8F7C04) != 0 )  // 虚调用 vt+1196（dword_8F7C04 虚表槽）
      {
        if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4)) != 0 )  // 角色/物品栏管理器
          goto LABEL_106;
        if ( (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) < (unsigned int)dword_795210 )  // 角色/物品栏管理器
          goto LABEL_118;
        v46 = *((uint32_t *)dword_8F8528 + 611);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
        goto LABEL_117;
      }
    }
  }
LABEL_118:
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 26) != 0  // 虚调用 vt+16（dword_79C0B4 虚表槽）
    && *(uint32_t *)(this + 2504) != 17 )
  {
    fld_30 = *(uint32_t *)(this + 48);  // 读字段 fld_30 = this+48（pCmdVecBegin48）
    v64 = 0;
    if ( *(uint32_t *)(fld_30 + 8) != 0 )  // fld_30=this+48 pCmdVecBegin48
    {
      sub_525740(fld_30);  // sub_525740 —— 辅助
      v64 = 1;
    }
    pThis_682 = (uint32_t *)(this + 104);  // this+104〔nTimerEnd(推断)〕
    for ( n = 2; n != 0; --n )  // 遍历计次循环（n != 0）
    {
      if ( *pThis_682 != 12 )  // pThis_682=this+104 nTimerEnd
      {
        pThis_411 = *(uint32_t *)(this + 4 * *pThis_682 + 56);  // pThis_682=this+104 nTimerEnd
        v50 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_411 + 48))(pThis_411);  // 虚调用 vt+48（pThis_411）归属坐标x
        sub_69A580(v50);  // 调 注销其资源后
        *pThis_682 = 12;  // pThis_682=this+104 nTimerEnd
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pThis_411 + 16))(pThis_411);  // 虚调用 vt+16（pThis_411 虚表槽）
        v64 = 1;
      }
      ++pThis_682;  // 计数自增 pThis_682
    }
    fld_74 = *(uint32_t *)(this + 116);  // 读字段 fld_74 = this+116（pSessionCtx）
    if ( *(uint8_t *)(*(uint32_t *)(fld_74 + 8) + 16) != 0 )  // fld_74=this+116 pSessionCtx
    {
      sub_540960(fld_74);  // sub_540960 —— 数量输入框刷新（24 行）
      v64 = 1;
    }
    for ( ii = 0; ii < 71; ++ii )  // 遍历计次循环（ii < 71）
    {
      pThis_88 = *(uint32_t *)(16 * ii + this + 136);  // this+136 演出已播标志
      if ( pThis_88 != 0
        && (*(uint32_t *)(16 * ii + this + 140) - pThis_88) >> 2 != 0  // this+140 第 3 组·+900 增量
        && (ii != 15 || *(uint32_t *)(dword_8F7A24 + 12) != 3)  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        && ((uint8_t)sub_41C590(dword_8F7A24) == 0 || ii != 2) )  // sub_41C590 —— 状态查询（this+348 == 4）
      {
        sub_44E850((uint32_t *)this, ii);  // sub_44E850 —— 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
        v64 = 1;
      }
    }
    fld_1C = *(uint32_t *)(this + 28);  // 读字段 fld_1C = this+28（pPanelVec）
    if ( *(uint8_t *)(fld_1C + 256) != 0 && *(uint8_t *)(*(uint32_t *)(fld_1C + 136) + 117) == 0 )  // fld_1C=this+28 pPanelVec
    {
      sub_43DA50(fld_1C, szPassword, 0);  // sub_43DA50 —— 输入框提交与回显
      sub_43B920(0);  // sub_43B920 —— 输入面板开关
      v64 = 1;
    }
    if ( *(uint32_t *)(*(uint32_t *)(this + 2444) + 12) != 0 )
    {
      sub_560610(0);  // sub_560610 —— SERA_SHOP 赛丽亚商店事件（698F90/55FDB0/5604F0/432EA0/44E8D0/65FA00/461170/461190/55EFB0/645CA0/44E850/44ABE0）
      v64 = 1;
    }
    if ( *(uint32_t *)(*(uint32_t *)(this + 2532) + 28) != 0 )
    {
      sub_5403D0(0);  // sub_5403D0 —— 对象状态切换（44E850）——区域选择联动
    }
    else if ( v64 == 0
           && *(uint32_t *)(dword_8F7A24 + 12) != 5  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
           && *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 28) + 136) + 117) == 0  // this+28〔pPanelVec(推断)〕等 2 字段
           && byte_9D3BE4 == 0 )
    {
      sub_44E8D0((char *)dword_8F8528, (void *)0x2B, 0, 0);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）
    }
  }
  if ( dword_8F7C04 != 0 && *(uint8_t *)(dword_8F7C04 + 8052) != 0 )  // dword_8F7C04（本地玩家对象）
  {
    v55 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    if ( v55 == 4 || v55 == 6 )
      sub_4B0A80();  // sub_4B0A80 —— 输入驱动的外观目标切换与镜头联动
  }
  if ( Block != nullptr )
    j__free(Block);  // 释放堆块
}


// ============================================================
// 【分区 2】地图选择工具（0x452580-0x452FA0）
// 加载门 8 态推进 0x452700（分发器 case 0x25 落点）；
// PVP 房间地图装载 0x452C50（"HendonMyre/Hendon_Pub_PVP.map" 自证）。
// ============================================================
// ------------------------------------------------------------
// 0x452580 sub_452580 —— 槽位类别查询（表值 4/3 判定）
// 表项 (+4+4n) 值等于 4 或 3 返回真【推断：参战/观战态位表】。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_452580(uint32_t *this, int pArg2)  // sub_452580 —— 槽位类别查询（表值 4/3 判定）
{
  int v2; // eax

  v2 = *(this + pArg2 + 1);
  return v2 == 4 || v2 == 3;
}



// ------------------------------------------------------------
// 0x4525B0 sub_4525B0 —— 自身槽 id 取出
// 下标 +27（-1 视为无效返回 0xFFFF）→ 取 +10 项表值（调用方用于与 word_77F804 比对定位自身槽）【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_4525B0(uint32_t *this)  // sub_4525B0 —— 自身槽 id 取出
{
  int fld_e27; // eax

  fld_e27 = *(this + 27);  // 读字段 fld_e27 = this+27
  if ( fld_e27 == -1 )  // fld_e27=this+108 第 1 组·宿主属性 +886 增量
    return 0xFFFF;
  else
    return *(this + fld_e27 + 10);  // fld_e27=this+108 第 1 组·宿主属性 +886 增量
}



// ------------------------------------------------------------
// 0x4525D0 sub_4525D0 —— 槽表状态复位
// +4 关闭态时清 +12..+136 共 21 字段（+124 置 -1）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4525D0(int this)  // sub_4525D0 —— 槽表状态复位
{
  int result; // eax

  result = 0;
  if ( *(uint8_t *)(this + 4) == 0 )  // this+4〔宿主对象〕等 2 字段
  {
    *(uint32_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
    *(uint32_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
    *(uint32_t *)(this + 20) = 0;  // 写字段 this+20（nPage） ← 0
    *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
    *(uint32_t *)(this + 28) = 0;  // 写字段 this+28（pPanelVec） ← 0
    *(uint32_t *)(this + 32) = 0;  // 写字段 this+32（nHeight） ← 0
    *(uint32_t *)(this + 36) = 0;  // 写字段 this+36（nStateWord36） ← 0
    *(uint32_t *)(this + 80) = 0;  // 写字段 this+80（nAuraStage） ← 0
    *(uint32_t *)(this + 84) = 0;  // 写字段 this+84（pFxObjA） ← 0
    *(uint32_t *)(this + 88) = 0;  // 写字段 this+88（pFxObjB） ← 0
    *(uint32_t *)(this + 92) = 0;  // 写字段 this+92（pFxObjC） ← 0
    *(uint32_t *)(this + 96) = 0;  // 写字段 this+96（nStatusMode） ← 0
    *(uint32_t *)(this + 100) = 0;  // 写字段 this+100（bEnchantDone） ← 0
    *(uint32_t *)(this + 104) = 0;  // 写字段 this+104（nTimerEnd） ← 0
    *(uint32_t *)(this + 108) = 0;  // 写字段 this+108（nAdd108） ← 0
    *(uint8_t *)(this + 112) = 0;  // 写字段 this+112（pHostComp） ← 0
    *(uint32_t *)(this + 116) = 0;  // 写字段 this+116（pSessionCtx） ← 0
    *(uint8_t *)(this + 120) = 0;  // 写字段 this+120（pAnimObj） ← 0
    *(uint32_t *)(this + 124) = -1;  // 写字段 this+124（pAuraAnim） ← -1
    *(uint32_t *)(this + 128) = 0;  // 写字段 this+128（szStatusKeyBuf） ← 0
    *(uint32_t *)(this + 132) = 0;  // 写字段 this+132（nAdd132） ← 0
    *(uint8_t *)(this + 136) = 0;  // 写字段 this+136（nCtx136） ← 0
  }
  return result;
}



// ------------------------------------------------------------
// 0x452630 sub_452630 —— 成员移除广播
// @@REMOVE PEER 自证：目标槽与 429830(word_77F804) 查得的自身不一致才走 vmt+104 分支，
// 再销毁 +196 对象（45F1E0）。
// ------------------------------------------------------------
int /*stdcall*/ sub_452630(int nArg1, int pArg2)  // sub_452630 —— 成员移除广播
{
  int result; // eax

  result = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
  if ( pArg2 != result )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 104))(dword_8F8520, nArg1);  // 虚调用 vt+104（dword_8F8520）并日志
    result = off_77F3FC("@@REMOVE PEER");  // off_77F3FC —— 日志打印（printf 风格）
  }
  if ( pArg2 != 0 )
  {
    result = *(uint32_t *)(pArg2 + 196);  // 读字段 result = pArg2+196
    if ( result != 0 )
      return sub_45F1E0(*(uint32_t *)(pArg2 + 196));  // sub_45F1E0 —— 对象注销/退场（递归，含 ELVEN_GATE 检查）
  }
  return result;
}



// ------------------------------------------------------------
// 0x452690 sub_452690 —— 座位状态上报
// 48F5A0 自身座位下标与 dword_99FEC0+108 一致时，op 59 上报 +20 起 8×u32（423200/423290/423380 三段）。
// ------------------------------------------------------------
int /*thiscall*/ sub_452690(int *this)  // sub_452690 —— 座位状态上报
{
  int result; // eax
  int *pThis_14; // esi
  int i; // edi
  int v5; // [esp+4h] [ebp-4h] BYREF

  result = dword_99FEC0;  // dword_99FEC0 —— 对局中标志查询
  if ( dword_99FEC0 != 0 )  // dword_99FEC0 —— 对局中标志查询
  {
    result = sub_48F5A0();  // sub_48F5A0 —— 结果 = 自身座位下标查找（房间号比对）
    if ( *(uint32_t *)(dword_99FEC0 + 108) == result )  // dword_99FEC0 —— 对局中标志查询
    {
      sub_423200(dword_8F7B08, 59);  // 【发送网络包API】
      pThis_14 = this + 20;  // this+20 频道页号
      for ( i = 8; i != 0; --i )  // 遍历计次循环（i != 0）
      {
        v5 = *pThis_14;  // pThis_14=this+20 频道页号
        sub_423290(dword_8F7B08, (int)&v5, 4);  // sub_423290 —— 写 4B 长度
        ++pThis_14;  // 计数自增 pThis_14
      }
      return sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x452700 sub_452700
// ------------------------------------------------------------
// 分发器 case 0x25 落点 —— 加载门推进：a2(0..7) 置 +128 位表；
// 8 门（sub_48F690 查询存在性）全开或 a2==8 → sub_698FE0 触发事件
char /*thiscall*/ sub_452700(uint8_t *this, int pArg2)  // 实现：8 门（sub_48F690 查询存在性）全开或 a2==8 → sub_698FE0 触发事件
{
  char v3; // bl
  int i; // esi
  int v5; // eax

  if ( pArg2 == 8 )
    goto LABEL_8;
  v3 = 1;
  *(this + pArg2 + 128) = 1;
  for ( i = 0; i < 8; ++i )  // 遍历计次循环（i < 8）
  {
    v5 = sub_48F690(i);  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
    if ( v5 != 0 )
    {
      LOBYTE(v5) = *(this + i + 128);
      if ( (uint8_t)v5 == 0 )
        v3 = 0;
    }
  }
  if ( v3 != 0 )
LABEL_8:
    LOBYTE(v5) = sub_698FE0((int)(this + 40));  // 【clock_unfreeze(clk)】
  return v5;
}



// ------------------------------------------------------------
// 0x452760 sub_452760 —— 主管理器状态推送
// 对 dword_8F8520：vmt+8(37,2) → vmt+32 入参 nArg1 → vmt+60(1,-1) 提交。
// ------------------------------------------------------------
int /*stdcall*/ sub_452760(int nArg1)  // sub_452760 —— 主管理器状态推送
{
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 37, 2);  // 虚调用 vt+8（dword_8F8520 虚表槽）
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nArg1);  // 虚调用 vt+32（dword_8F8520 虚表槽）
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 虚调用 vt+60（dword_8F8520）对象销毁/释放
}



// ------------------------------------------------------------
// 0x4527A0 sub_4527A0 —— 计数累加
// 槽 pArg2 的 +20 字段 += nArg3，返回槽号。
// ------------------------------------------------------------
int /*thiscall*/ sub_4527A0(uint32_t *this, int pArg2, int nArg3)  // sub_4527A0 —— 计数累加
{
  *(this + pArg2 + 20) += nArg3;
  return pArg2;
}



// ------------------------------------------------------------
// 0x4527C0 sub_4527C0 —— 帧表数值采样
// dword_98B720 帧表按 44 字节步长取第 nArg2 通道浮点；uArg1 越界钳到末帧，-1 返回 1.0。
// ------------------------------------------------------------
double /*cdecl*/ sub_4527C0(unsigned int uArg1, int nArg2)  // sub_4527C0 —— 帧表数值采样
{
  int uArg12; // ecx
  unsigned int v4; // eax
  unsigned int uArg13; // edx

  uArg12 = uArg1;
  if ( uArg1 == -1 )
    return 1.0;  // 返回 1.0
  if ( dword_98B720 == 0 )
    goto LABEL_9;
  v4 = (dword_98B724 - dword_98B720) / 44;
  uArg13 = uArg1;
  if ( uArg1 >= v4 )
    uArg13 = (dword_98B724 - dword_98B720) / 44;
  if ( uArg13 > 1 )
  {
    if ( uArg1 >= v4 )
      return *(float *)(44 * v4 + dword_98B720 - 44 + 4 * nArg2);
  }
  else
  {
LABEL_9:
    uArg12 = 1;
  }
  return *(float *)(44 * uArg12 + dword_98B720 - 44 + 4 * nArg2);
}



// ------------------------------------------------------------
// 0x452830 sub_452830 —— 44 字节元素表分配
// 三指针区间 +1/+2/+3（44 字节元素）；uArg2 > 0x5D1745D 抛 length_error（434730）。
// ------------------------------------------------------------
char /*thiscall*/ sub_452830(uint32_t *this, unsigned int uArg2)  // sub_452830 —— 44 字节元素表分配
{
  char *pMem; // eax

  *(this + 1) = 0;  // 写字段 this+1 ← 0
  *(this + 2) = 0;  // 写字段 this+2 ← 0
  *(this + 3) = 0;  // 写字段 this+3 ← 0
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x5D1745D )
    sub_434730(this);  // sub_434730 —— vector 超长抛 length_error
  pMem = (char *)operator new(44 * uArg2);  // 堆分配
  *(this + 3) = &pMem[44 * uArg2];  // 写字段 this+3 ← &pMem[44 * uArg2]
  *(this + 1) = pMem;  // 写字段 this+1 ← pMem
  *(this + 2) = pMem;  // 写字段 this+2 ← pMem
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x452880 sub_452880 —— 对象缩放登记
// map(+17, 键 fArg4) 去重；IRDMonster/CNRDPassiveObject（RTTI 自证）按 fArg2 放大，
// 乘法经防篡改 clong 包装 42B3F0。
// ------------------------------------------------------------
void /*userpurge*/ sub_452880(uint32_t *pArg1@<ecx>, float fArg2@<esi>, double fArg3@<st0>, float fArg4, int nArg5)  // sub_452880 —— 对象缩放登记
{
  int v5; // edi
  uint32_t *v6; // esi
  uint32_t *v7; // eax
  int nArg52; // ebx
  int pObj; // esi
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int *v13; // eax
  int *v14; // esi
  int *v15; // ebx
  double v16; // st7
  int *v17; // esi
  float fArg32; // [esp+0h] [ebp-14h]

  v5 = LODWORD(fArg4);  // v5 = 调 LODWORD
  if ( fArg4 != 0.0 )
  {
    v6 = pArg1 + 17;  // 计算 v6 = pArg1 + 17
    v7 = (uint32_t *)sub_42D430(pArg1 + 17, &fArg4);  // sub_42D430 —— map 取或建
    nArg52 = nArg5;
    if ( *v7 != nArg5 )
    {
      *(uint32_t *)sub_42D430(v6, &fArg4) = nArg52;  // sub_42D430 —— map 取或建
      pObj = __RTDynamicCast(v5, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // pObj = 调 __RTDynamicCast
      if ( pObj != 0 )
      {
        fArg4 = flt_7904FC;
        sub_433E90(pArg1, v5, 2);
        fArg3 = fArg3 * fArg4;  // 计算 fArg3 = fArg3 * fArg4
        fArg32 = fArg3;
        v10 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pObj + 672))(pObj, 0, LODWORD(fArg32));  // 虚调用 vt+672（pObj）队伍编号取址
        sub_42B3F0((void *)(v10 + 4), fArg2);  // sub_42B3F0 —— 防篡改浮点乘法（clong）
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 676))(pObj, 0);  // 虚调用 vt+676（pObj）队伍编号刷新
        v11 = *(uint32_t *)pObj;
        v12 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj + 740))(pObj, 0, 1);  // 虚调用 vt+740（pObj 虚表槽）
        (*(void (/*thiscall*/ **)(int, int))(v11 + 732))(pObj, v12);  // 调虚槽 +732：CNMapObject__vmt2DC
      }
      v13 = (int *)__RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                     v5,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &CNRDPassiveObject `RTTI Type Descriptor',
                     0);
      v14 = v13;
      if ( v13 != nullptr && v13[171] > 0 )
      {
        v15 = (int *)((*(int (/*thiscall*/ **)(int *))(*v13 + 672))(v13) + 4);  // 虚调用 vt+672（v13）队伍编号取址
        sub_433E90(pArg1, v5, 2);
        v16 = fArg3 * (double)*v15 * flt_7904FC;
        *v15 = (uint64_t)v16;
        v17 = (int *)(*(int (/*thiscall*/ **)(int *))(*v14 + 672))(v14);  // 虚调用 vt+672（v14）队伍编号取址
        sub_433E90(pArg1, v5, 2);
        *v17 = (uint64_t)(v16 * (double)*v17 * flt_7904FC);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x4529B0 sub_4529B0 —— 对象入场装配
// 45FE80 注册 + vmt112 落点(48C2A0) + 演出参数 4B0780 + vmt148 显隐 + 452880 缩放大 +
// 外观切换 4B05D0 + 424A40 锚定；+196 缺失打 CRITICAL ERROR。
// ------------------------------------------------------------
void /*userpurge*/ sub_4529B0(uint32_t *pArg1@<ecx>, double fArg2@<st0>, int ArgList, int nArg4, char pszArg5)  // sub_4529B0 —— 对象入场装配
{
  int nArg42; // edi
  int v7; // eax
  int pObj; // esi
  int v9; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // [esp+8h] [ebp-4h] BYREF

  nArg42 = nArg4;
  if ( nArg4 != 0 )
  {
    v7 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
    if ( nArg42 != v7 )
    {
      LOBYTE(v7) = pszArg5 == 0;
      (*(void (/*thiscall*/ **)(int, int, int, int, uint32_t))(*(uint32_t *)dword_8F8520 + 100))(  // 虚调用 vt+100（dword_8F8520 虚表槽）
        dword_8F8520,  // dword_8F8520 —— 虚表 +120 调用
        ArgList,
        nArg42,
        v7,
        0);
    }
    pObj = *(uint32_t *)(nArg42 + 196);  // 读字段 pObj = nArg42+196
    if ( pObj != 0 )
    {
      sub_45FE80(pArg1[8], nArg42, 273, *(uint16_t *)(nArg42 + 4), pObj, 0, 0);  // sub_45FE80 —— 对象注册
      v9 = *(uint16_t *)(nArg42 + 4);  // 读字段 v9 = nArg42+4（pHostObj）
      v13 = 0;
      nArg4 = 0;
      sub_48C2A0(&v13, &nArg4, 0, pObj, ArgList * v9);  // sub_48C2A0 —— 区域内找落点（失败打 FIND POS FAIL）
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 112))(pObj, v13, nArg4, 0);  // 虚调用 vt+112（pObj）坐标三元组写入
      sub_4B0780(v13, nArg4, 0);  // sub_4B0780 —— 设置三演出参数 +8056..+8064
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 148))(pObj, 1);  // 虚调用 vt+148（pObj）位置/朝向写入
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1020))(pObj);  // 虚调用 vt+1020（pObj 虚表槽）
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 1200))(pObj, 0);  // 虚调用 vt+1200（pObj）(nArg1) —— 全体广播族。
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1212))(pObj, ArgList);  // 虚调用 vt+1212（pObj 虚表槽）
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);  // 虚调用 vt+388（pObj）攻击计算
      sub_452880(pArg1, *(float *)&pObj, fArg2, *(float *)&pObj, v10);  // sub_452880 —— 对象缩放登记
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1056))(pObj, 1);  // 虚调用 vt+1056（pObj 虚表槽）
      if ( dword_8F7C04 != 0 && *(uint8_t *)(dword_8F7C04 + 8052) != 0 )  // dword_8F7C04（本地玩家对象）
      {
        v11 = *(uint32_t *)(pArg1[4] + 52);
        if ( v11 == 0 || v11 == dword_8F7C04 )  // dword_8F7C04（本地玩家对象）
        {
          v12 = sub_4B05D0(0);  // sub_4B05D0 —— 外观状态切换（+52；sub_48F690/578E80 场景联动）
          sub_424A40((uint32_t *)pArg1[4], v12);  // sub_424A40 —— 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
        }
      }
    }
    else
    {
      off_77F3FC(aCriticalError_4, ArgList);  // off_77F3FC —— 日志打印（printf 风格）
    }
  }
}



// ------------------------------------------------------------
// 0x452B10 sub_452B10 —— 战场对象主体构造
// sub_42DF70 主体构造外壳（两处空实现）。
// ------------------------------------------------------------
void */*thiscall*/ sub_452B10(void *this)  // sub_452B10 —— 战场对象主体构造
{
  sub_42DF70((int)this);  // sub_42DF70 —— 主体构造
  nullsub_3();  // 空桩函数（无操作）
  nullsub_3();  // 空桩函数（无操作）
  return this;
}



// ------------------------------------------------------------
// 0x452B60 sub_452B60
// ------------------------------------------------------------
// 【推断】地图词条/路径辅助
uint32_t */*thiscall*/ sub_452B60(uint32_t *this, char ArgList, int nArg3)  // 实现：(推断)地图词条/路径辅助
{
  sub_42D6A0((int)this);  // sub_42D6A0 —— 战场观看主件构造
  *(this + 91) = 0;  // 写字段 this+91 ← 0
  *(this + 92) = 0;  // 写字段 this+92（pFxObjC） ← 0
  *(this + 93) = 0;  // 写字段 this+93（bEnableFlag） ← 0
  *(this + 95) = 0;  // 写字段 this+95 ← 0
  *(this + 96) = 0;  // 写字段 this+96（nStatusMode） ← 0
  *(this + 97) = 0;  // 写字段 this+97（bFlag97） ← 0
  *(this + 100) = 0;  // 写字段 this+100（bEnchantDone） ← 0
  *(this + 101) = 0;  // 写字段 this+101（bFired101） ← 0
  *(this + 102) = 0;  // 写字段 this+102（bFlashClearB） ← 0
  *(this + 103) = 0;  // 写字段 this+103 ← 0
  *(this + 104) = 0;  // 写字段 this+104（nTimerEnd） ← 0
  *(this + 105) = 0;  // 写字段 this+105（bGuildFlagD） ← 0
  *(this + 106) = 0;  // 写字段 this+106（bClockUnfreeze106） ← 0
  *(this + 107) = 0;  // 写字段 this+107 ← 0
  *(this + 108) = 0;  // 写字段 this+108（nAdd108） ← 0
  *(this + 109) = 0;  // 写字段 this+109 ← 0
  *(this + 110) = 0;  // 写字段 this+110 ← 0
  *(this + 111) = 0;  // 写字段 this+111 ← 0
  *(this + 112) = 0;  // 写字段 this+112（pHostComp） ← 0
  *(this + 113) = 0;  // 写字段 this+113 ← 0
  *(this + 114) = 0;  // 写字段 this+114 ← 0
  *(this + 115) = 0;  // 写字段 this+115 ← 0
  *(this + 123) = 0;  // 写字段 this+123 ← 0
  *(this + 124) = 0;  // 写字段 this+124（pAuraAnim） ← 0
  *(this + 125) = 0;  // 写字段 this+125（field_007D） ← 0
  *(this + 127) = 0;  // 写字段 this+127 ← 0
  *(this + 128) = 0;  // 写字段 this+128（szStatusKeyBuf） ← 0
  *(this + 129) = 0;  // 写字段 this+129 ← 0
  sub_48D9D0(this);  // sub_48D9D0 —— 战场块字段复位与缓冲释放
  sub_48EED0(ArgList, nArg3);  // sub_48EED0 —— 图像/动画装载包装（+53/+57/+50 槽位；sub_48E2E0 %s%s 拼路径；IMAGE/ANI 一体化）
  return this;
}



// ------------------------------------------------------------
// 0x452C50 sub_452C50
// ------------------------------------------------------------
// PVP 房间地图装载（"HendonMyre/Hendon_Pub_PVP.map" 自证）：
// sub_452B60 取词条 → dword_8F84B8 vt+60 载入 .map → 场景层创建
char /*thiscall*/ sub_452C50(int this)  // sub_452C50 —— 后续初始化
{
  char result; // al
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  char *pMem2; // eax
  char *v6; // eax
  void *pMem3; // eax
  void *v8; // eax
  int fld_10; // ecx
  uint32_t *pMem4; // eax
  uint32_t *v11; // eax
  uint32_t *pMem5; // eax
  uint32_t *v13; // eax
  uint32_t *fld_102; // ecx

  result = *(uint8_t *)(this + 4);  // 读字段 result = this+4（pHostObj）
  if ( result == 0 )  // result=this+4 pHostObj
  {
    *(uint8_t *)(this + 4) = 1;  // 写字段 this+4（pHostObj） ← 1
    pMem = operator new(0x68u);  // 堆分配
    if ( pMem != nullptr )
      v4 = sub_426BD0(pMem);  // sub_426BD0 —— nengine::IControl 构造
    else
      v4 = nullptr;
    *(uint32_t *)(this + 12) = v4;  // 写字段 this+12（nSkillRec12） ← v4
    *((uint32_t *)v4 + 17) = this + 8;  // 写字段 v4+17（bEnable）
    pMem2 = (char *)operator new(0x558u);  // 堆分配
    if ( pMem2 != nullptr )
      v6 = sub_42B7E0(pMem2);  // 调 ：= 评价/横幅对象大构造器（36 字节槽组 ×N，尾调 0x423C10 复位评价值）
    else
      v6 = nullptr;
    *(uint32_t *)(this + 16) = v6;  // 写字段 this+16（nChannelTypeSel） ← v6
    sub_69A840(*((uint32_t *)v6 + 9));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    pMem3 = operator new(0x1F0u);  // 堆分配
    if ( pMem3 != nullptr )
      v8 = sub_452B10(pMem3);  // sub_452B10 —— 战场对象主体构造
    else
      v8 = nullptr;
    fld_10 = *(uint32_t *)(this + 16);  // 读字段 fld_10 = this+16（nChannelTypeSel）
    *(uint32_t *)(this + 20) = v8;  // 写字段 this+20（nPage） ← v8
    *(uint32_t *)(fld_10 + 108) = v8;  // 写字段 fld_10+108（nAdd108） ← v8
    pMem4 = operator new(0x208u);  // 堆分配
    if ( pMem4 != nullptr )
      v11 = sub_452B60(pMem4, (char)"HendonMyre/Hendon_Pub_PVP.map", 0);  // 调 取词条 → dword_8F84B8 vt+60 载入 .map → 场景层创建
    else
      v11 = nullptr;
    *(uint32_t *)(this + 24) = v11;  // 写字段 this+24（nPageMax） ← v11
    *(uint32_t *)(this + 28) = 0;  // 写字段 this+28（pPanelVec） ← 0
    pMem5 = operator new(0xA0u);  // 堆分配
    if ( pMem5 != nullptr )
      v13 = sub_42D590(pMem5, 0);  // sub_42D590 —— 战斗条目构造（0xA0）
    else
      v13 = nullptr;
    fld_102 = *(uint32_t **)(this + 16);  // this+64〔apServerTabBtn(推断)〕
    *(uint32_t *)(this + 32) = v13;  // 写字段 this+32（nHeight） ← v13
    sub_424100(fld_102, (int)v13);  // sub_424100 —— 关联对象 setter
    sub_69A840(*((uint32_t *)dword_8F8528 + 2));  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    sub_69A840(*((uint32_t *)dword_8F8528 + 3));  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 16) + 40));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    return sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));  // dword_8F8528 —— 对象池借出（按池号取可用对象）
  }
  return result;  // result=this+4 pHostObj
}



// ------------------------------------------------------------
// 0x452DF0 sub_452DF0 —— 离场复原
// 8 槽解绑（48F690 遍历 → 45FE80/452880/425500/42EDE0/45FC60 清理 +18 表复位），
// 末段按 +4 表值 4/3 把角色移出屏（vmt112 -10000）。
// ------------------------------------------------------------
int /*usercall*/ sub_452DF0@<eax>(uint32_t *pArg1@<ecx>, double fArg2@<st0>)  // 实现：离场复原
{
  void *v3; // esi
  int v4; // ecx
  uint32_t *v5; // eax
  int v6; // esi
  int v7; // eax
  int v8; // ebx
  int pObj; // esi
  int v10; // eax
  uint16_t v11; // bx
  int v12; // eax
  int i; // esi
  int result; // eax
  int v15; // ecx
  int v16; // [esp+Ch] [ebp-Ch]
  int v17; // [esp+10h] [ebp-8h] BYREF
  int v18; // [esp+14h] [ebp-4h] BYREF

  sub_425500(pArg1[4], pArg1[6]);  // sub_425500 —— 锚定对象换绑
  v3 = (void *)pArg1[7];
  if ( v3 != nullptr )
  {
    sub_42EDE0(pArg1[7]);  // sub_42EDE0 —— 战场块析构
    j__free(v3);  // 释放堆块
  }
  v4 = pArg1[8];
  pArg1[7] = 0;
  sub_45FC60(v4);  // sub_45FC60 —— ★ 对象表按类型过滤批量卸载（六类型码黑名单 + 两轮清理）
  sub_4602C0(*(uint32_t *)(pArg1[6] + 476));  // sub_4602C0 —— 图标容器批量实例化
  sub_41CAA0(*(void **)(pArg1[18] + 4));  // sub_41CAA0 —— 递归释放右子树
  *(uint32_t *)(pArg1[18] + 4) = pArg1[18];
  v5 = (uint32_t *)pArg1[18];
  pArg1[19] = 0;
  *v5 = v5;
  *(uint32_t *)(pArg1[18] + 8) = pArg1[18];
  v6 = 0;
  v16 = 0;
  do
  {
    v7 = sub_48F690(v6);  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
    v8 = v7;
    if ( v7 != 0 )
    {
      pObj = *(uint32_t *)(v7 + 196);  // 读字段 pObj = v7+196
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);  // 虚调用 vt+388（pObj）攻击计算
      sub_452880(pArg1, *(float *)&pObj, fArg2, *(float *)&pObj, v10);  // sub_452880 —— 对象缩放登记
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1020))(pObj);  // 虚调用 vt+1020（pObj 虚表槽）
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 1200))(pObj, 0);  // 虚调用 vt+1200（pObj）(nArg1) —— 全体广播族。
      sub_45FE80(pArg1[8], (int)pArg1, 273, *(uint16_t *)(v8 + 4), pObj, 0, 0);  // sub_45FE80 —— 对象注册
      v11 = *(uint16_t *)(v8 + 4);  // 读字段 v11 = v8+4（pHostObj）
      v17 = 0;
      v18 = 0;
      v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1216))(pObj);  // 虚调用 vt+1216（pObj 虚表槽）
      sub_48C2A0(&v17, &v18, 0, pObj, v11 * v12);  // sub_48C2A0 —— 区域内找落点（失败打 FIND POS FAIL）
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 112))(pObj, v17, v18, 0);  // 虚调用 vt+112（pObj）坐标三元组写入
      (*(void (/*thiscall*/ **)(int, int *, int *, int, int, int, uint32_t, int))(*(uint32_t *)pObj + 140))(  // 虚调用 vt+140（pObj）日志(变参 printf)
        pObj,
        &v17,
        &v18,
        v17,
        v18,
        200,
        0,
        1);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 112))(pObj, v17, v18, 0);  // 虚调用 vt+112（pObj）坐标三元组写入
      v6 = v16;
    }
    v16 = ++v6;
  }
  while ( v6 < 8 );  // 循环直到 v6 < 8
  for ( i = 0; i < 8; ++i )  // 遍历计次循环（i < 8）
  {
    result = sub_48F690(i);  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
    if ( result != 0 )  // result=this+4 pHostObj
    {
      v15 = *(uint32_t *)(dword_99FEC0 + 4 * i + 8);  // dword_99FEC0 —— 对局中标志查询
      if ( v15 == 4 || v15 == 3 )
        result = (*(int (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(result + 196) + 112))(  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
                   *(uint32_t *)(result + 196),  // result=this+4 pHostObj
                   -10000,
                   -10000,
                   0);
    }
  }
  return result;  // result=this+4 pHostObj
}



// ============================================================
// 【分区 3】CNPVPModule 与座位管理（0x452FA0-0x454610）
// CNPVPModule__vmt4（RTTI 自证）；0x453DD0 = 座位/选中槽同步
// （战斗分发器 case 2/3 落点，CLICK_BUTTON2 自证）。
// ============================================================
// ------------------------------------------------------------
// 0x452FA0 sub_452FA0 —— 场景容器析构
// 对 ·0x452C50 所建：42BD40(CNRDStage)/42E940/42EDE0×2/42C770 逐项释放。
// ------------------------------------------------------------
void /*thiscall*/ sub_452FA0(int this)  // sub_452FA0 —— 场景容器析构
{
  void (/*thiscall*/ ***pThis_C)(uint32_t, int); // ecx
  void *fld_10; // edi
  void *fld_14; // edi
  void *fld_18; // edi
  void *fld_1C; // edi
  void *fld_20; // edi

  if ( *(uint8_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
  {
    pThis_C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
    *(uint8_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
    if ( pThis_C != nullptr )  // pThis_C=this+48 pCmdVecBegin48
      (**pThis_C)(pThis_C, 1);  // 调 pThis_C 的虚函数（vt+0）
    fld_10 = *(void **)(this + 16);  // this+64〔apServerTabBtn(推断)〕
    *(uint32_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
    if ( fld_10 != nullptr )  // fld_10=this+64 apServerTabBtn
    {
      sub_42BD40((int)fld_10);  // sub_42BD40 —— CNRDStage 析构（对应 ·0x42B7E0 构造）
      j__free(fld_10);  // 释放堆块
    }
    fld_14 = *(void **)(this + 20);  // this+80〔nAuraStage(推断)〕
    *(uint32_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
    if ( fld_14 != nullptr )  // fld_14=this+80 nAuraStage
    {
      sub_42E940(fld_14);  // sub_42E940 —— 析构（0x1F0）
      j__free(fld_14);  // 释放堆块
    }
    fld_18 = *(void **)(this + 24);  // this+96〔nStatusMode(推断)〕
    *(uint32_t *)(this + 20) = 0;  // 写字段 this+20（nPage） ← 0
    if ( fld_18 != nullptr )  // fld_18=this+96 nStatusMode
    {
      sub_42EDE0((int)fld_18);  // sub_42EDE0 —— 战场块析构
      j__free(fld_18);  // 释放堆块
    }
    fld_1C = *(void **)(this + 28);  // this+112〔pHostComp112〕
    *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
    if ( fld_1C != nullptr )  // fld_1C=this+112 pHostComp112
    {
      sub_42EDE0((int)fld_1C);  // sub_42EDE0 —— 战场块析构
      j__free(fld_1C);  // 释放堆块
    }
    fld_20 = *(void **)(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
    *(uint32_t *)(this + 28) = 0;  // 写字段 this+28（pPanelVec） ← 0
    if ( fld_20 != nullptr )  // fld_20=this+128 szStatusKeyBuf
    {
      sub_42C770((int)fld_20);  // sub_42C770 —— 战斗条目析构
      j__free(fld_20);  // 释放堆块
    }
    *(uint32_t *)(this + 32) = 0;  // 写字段 this+32（nHeight） ← 0
  }
}



// ------------------------------------------------------------
// 0x453050 sub_453050 —— 阶段切换主控
// nArg3 case 0..4：clock_set_countdown + 帧游标复位(4926A0/44E850) + 槽快照(445830)，
// case 3 全员 vmt1200/vmt320 收拢；case 0 走 452DF0 复原【推断：PVP 房间阶段机】。
// ------------------------------------------------------------
void /*userpurge*/ sub_453050(int pArg1@<ecx>, double fArg2@<st0>, int nArg3, int nArg4)  // sub_453050 —— 阶段切换主控 nArg3 case 0..4：clock_set_countdown + 帧游标复位
{
  int v5; // ecx
  int v6; // ebx
  int v7; // esi
  int v8; // eax
  int pObj; // esi

  v5 = pArg1 + 40;  // 计算 v5 = pArg1 + 40
  *(uint32_t *)(pArg1 + 36) = nArg3;  // 写字段 pArg1+36（nStateWord36） ← nArg3
  v6 = 0;
  *(uint8_t *)(v5 + 13) = 0;  // 写字段 v5+13 ← 0
  *(uint8_t *)(v5 + 14) = 0;  // 写字段 v5+14 ← 0
  sub_698F90(v5, 0, nArg4);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( dword_8F7C04 == 0 || *(uint8_t *)(dword_8F7C04 + 8052) == 0 )  // dword_8F7C04（本地玩家对象）
    sub_424A40(*(uint32_t **)(pArg1 + 16), dword_8F7C04);  // sub_424A40 —— 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
  sub_4684F0(*((uint32_t *)dword_8F8528 + 4), nullptr);  // sub_4684F0 —— 目标 HUD 更新（血条宽度 = 等级比）
  if ( nArg3 != 0 )
  {
    switch ( nArg3 )  // 按 nArg3 分派
    {
      case 1:  // case 1 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
        sub_52C7F0(0);  // 调 控件定位（567,142)/(542,155)/(458,114) → +30/+28 状态清零
        v7 = *((uint32_t *)dword_8F8528 + 4);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
        sub_4926A0(*(uint32_t *)(v7 + 1016));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
        *(uint32_t *)(v7 + 1020) = 0;  // 写字段 v7+1020（pAnimHandleArr） ← 0
        sub_44E850(dword_8F8528, 40);  // sub_44E850 —— 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
        sub_44E850(dword_8F8528, 43);  // sub_44E850 —— 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
        break;
      case 2:  // case 2 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
        *(uint32_t *)(pArg1 + 116) = 180000;  // 写字段 pArg1+116（pSessionCtx） ← 180000
        sub_445830((uint8_t *)dword_8F8520, 1);  // sub_445830 —— 槽快照区复位 写 +1048944 旗标；置位时清 8 组 28 字节记录
        break;
      case 3:  // case 3 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
        do
        {
          v8 = sub_48F690(v6);  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
          if ( v8 != 0 )
          {
            pObj = *(uint32_t *)(v8 + 196);  // 读字段 pObj = v8+196
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1200))(pObj, 1);  // 虚调用 vt+1200（pObj）(nArg1) —— 全体广播族。
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 320))(pObj);  // 虚调用 vt+320（pObj 虚表槽）
          }
          ++v6;  // 计数自增 v6
        }
        while ( v6 < 8 );  // 循环直到 v6 < 8
        *(uint8_t *)(pArg1 + 112) = 0;  // 写字段 pArg1+112（pHostComp） ← 0
        CNCommandChecker__vmt40(0, 1);
        *((uint32_t *)dword_8F8528 + 621) = 0;  // dword_8F8528 —— 对象池借出（按池号取可用对象）
        break;
      case 4:  // case 4 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
        *(uint32_t *)(pArg1 + 116) = 0;  // 写字段 pArg1+116（pSessionCtx） ← 0
        sub_445830((uint8_t *)dword_8F8520, 0);  // sub_445830 —— 槽快照区复位 写 +1048944 旗标；置位时清 8 组 28 字节记录
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 112))(dword_8F8520);  // 虚调用 vt+112（dword_8F8520）坐标三元组写入
        break;
      default:
        break;
    }
  }
  else
  {
    CNCommandChecker__vmt40(0, 1);
    sub_52C7F0(1);  // 调 控件定位（567,142)/(542,155)/(458,114) → +30/+28 状态清零
    sub_452DF0((uint32_t *)pArg1, fArg2);  // sub_452DF0 —— 离场复原
    sub_4772A0(0);  // sub_4772A0 —— 结算事件：M_RESULT 打开结算界面
    sub_45A420(0);  // sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
    sub_54F540(0);  // sub_54F540 —— 结算动画事件：MAP_APPEAR/M_RESULT/RESULT_COME 标签（432EE0/65DC70/432EA0）
    *((uint32_t *)dword_8F8528 + 621) = 0;  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    *(uint32_t *)(pArg1 + 124) = -1;  // 写字段 pArg1+124（pAuraAnim） ← -1
    *(uint32_t *)(pArg1 + 128) = 0;  // 写字段 pArg1+128（szStatusKeyBuf） ← 0
    *(uint32_t *)(pArg1 + 132) = 0;  // 写字段 pArg1+132（nAdd132） ← 0
    *(uint8_t *)(pArg1 + 120) = 0;  // 写字段 pArg1+120（pAnimObj） ← 0
  }
}



// ------------------------------------------------------------
// 0x453230 sub_453230 —— 阶段复位包装
// +4 有效 → 453050(case 0) 并清 +136。
// ------------------------------------------------------------
void /*usercall*/ sub_453230(int pArg1@<ecx>, double fArg2@<st0>)  // sub_453230 —— (this+32 对象)
{
  if ( *(uint8_t *)(pArg1 + 4) != 0 )  // pArg1+4〔宿主对象〕
  {
    sub_453050(pArg1, fArg2, 0, 0);  // sub_453050 —— 阶段切换主控 nArg3 case 0..4：clock_set_countdown + 帧游标复位
    *(uint8_t *)(pArg1 + 136) = 0;  // 写字段 pArg1+136（nCtx136） ← 0
  }
}



// ------------------------------------------------------------
// 0x453250 CNPVPModule__vmt4
// ------------------------------------------------------------
// CNPVPModule::vmt4 —— PVP 模块帧处理（RTTI 自证）
char /*thiscall*/ sub_453250(int *this)  // 【CNPVPModule__vmt4】
{
  int *pThis; // esi
  int v2; // ebx
  int v3; // eax
  int i; // edi
  int v5; // eax
  int *v6; // esi
  int v7; // ebx
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // ecx
  char v15; // al
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  uint16_t v19; // di
  int v20; // eax
  int v21; // eax
  int v22; // edi
  int v23; // eax
  unsigned int v24; // ecx
  bool v25; // zf
  uint16_t v26; // ax
  int v27; // edi
  int v28; // edi
  char v29; // al
  int v30; // eax
  int v31; // ecx
  int v32; // eax
  int v33; // edi
  uint8_t *pObj; // esi
  int v35; // ebx
  int j; // edi
  int v37; // eax
  int v38; // eax
  int v39; // edi
  int v40; // ebx
  int v41; // esi
  int v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // eax
  uint8_t *v46; // eax
  int k; // ecx
  int v49; // [esp-8h] [ebp-3Ch]
  int v50; // [esp-4h] [ebp-38h]
  uint16_t Block; // [esp+Ch] [ebp-28h]
  int v52; // [esp+10h] [ebp-24h] BYREF
  int v53; // [esp+14h] [ebp-20h] BYREF
  int v54; // [esp+18h] [ebp-1Ch]
  uint32_t *v55; // [esp+1Ch] [ebp-18h]
  int *pThis2; // [esp+20h] [ebp-14h]
  bool v57; // [esp+27h] [ebp-Dh]
  int v58; // [esp+30h] [ebp-4h]

  pThis = this;
  pThis2 = this;
  sub_4AEB30(&dword_9A02B0);  // sub_4AEB30 —— 帧开始（原文参数 &unk_9A02B0）
  v2 = 0;
  if ( byte_77F280 != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 88) != 0 )  // 虚调用 vt+16（dword_79C0B4 虚表槽）
  {
    *(uint32_t *)(dword_99FEC0 + 112) = 0;  // dword_99FEC0 —— 对局中标志查询
    sub_453050(1, 0);  // sub_453050 —— 阶段切换主控 nArg3 case 0..4：clock_set_countdown + 帧游标复位
  }
  sub_433690();  // 【= 主帧 tick（timeGetTime 驱动；'SHUTTER_ON' 截屏音效…】
  sub_4294E0(pThis[4]);  // sub_4294E0 —— HUD 每帧总 tick（尾段）
  v3 = pThis[9];
  switch ( v3 )  // 按 v3 分派
  {
    case 0:  // case 0 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
      if ( dword_99FEC0 != 0 )  // dword_99FEC0 —— 对局中标志查询
      {
        for ( i = 0; i < 8; ++i )  // 遍历计次循环（i < 8）
        {
          v5 = sub_48F690((uint32_t *)dword_99FEC0, i);  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
          if ( v5 != 0 )
          {
            v6 = *(int **)(v5 + 196);
            if ( v6 != nullptr )
            {
              v7 = (*(int (/*thiscall*/ **)(uint32_t))(*v6 + 740))(*(uint32_t *)(v5 + 196));  // 虚调用 vt+740（v6 虚表槽）
              if ( (*(int (/*thiscall*/ **)(int *))(*v6 + 736))(v6) != v7 )  // 虚调用 vt+736（v6 虚表槽）
              {
                v8 = *v6;
                v9 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*v6 + 740))(v6, 0, 1);  // 虚调用 vt+740（v6 虚表槽）
                (*(void (/*thiscall*/ **)(int *, int))(v8 + 732))(v6, v9);  // 调虚槽 +732：CNMapObject__vmt2DC
              }
              v10 = (*(int (/*thiscall*/ **)(int *))(*v6 + 756))(v6);  // 虚调用 vt+756（v6 虚表槽）
              if ( (*(int (/*thiscall*/ **)(int *))(*v6 + 752))(v6) != v10 )  // 虚调用 vt+752（v6 虚表槽）
              {
                v11 = *v6;
                v12 = (*(int (/*thiscall*/ **)(int *, int))(*v6 + 756))(v6, 1);  // 虚调用 vt+756（v6 虚表槽）
                (*(void (/*thiscall*/ **)(int *, int))(v11 + 748))(v6, v12);  // 调虚槽 +748：[RTTI: IRDActiveObject__vmt2EC · 槽位 IRDActiveObj…
              }
            }
          }
        }
        pThis = pThis2;
      }
      break;
    case 2:  // case 2 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
      sub_4BF300(dword_8F8558, 0, 0);  // sub_4BF300 —— 槽写侧（+64 + 索引）
      if ( sub_699000((int)(pThis + 10)) >= 4640 )  // 【clock_now(clk)】
      {
        v13 = sub_699000((int)(pThis + 10));  // 【clock_now(clk)】
        sub_453050(3, v13 - 4640);  // sub_453050 —— 阶段切换主控 nArg3 case 0..4：clock_set_countdown + 帧游标复位
        *((uint32_t *)dword_8F8528 + 621) = 0;  // dword_8F8528 —— 对象池借出（按池号取可用对象）
      }
      break;
    case 3:  // case 3 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
      if ( 180000 - sub_699000((int)(pThis + 10)) <= 0 )  // 【clock_now(clk)】
        v14 = 0;
      else
        v14 = 180000 - sub_699000((int)(pThis + 10));  // 【clock_now(clk)】
      v15 = *((uint8_t *)pThis + 112);  // 读字段 v15 = pThis+112（pHostComp）
      pThis[29] = v14;
      if ( v15 == 0 && sub_699000((int)(pThis + 10)) >= 180000 )  // 【clock_now(clk)】
      {
        sub_452690(pThis);  // sub_452690 —— 座位状态上报
        *((uint8_t *)pThis + 112) = 1;  // 写字段 pThis+112（pHostComp）
      }
      break;
    case 4:  // case 4 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
      if ( *(uint32_t *)(*((uint32_t *)dword_8F8528 + 610) + 8) == 0 )  // dword_8F8528 —— 对象池借出（按池号取可用对象）
      {
        pThis[9] = 5;
        *((uint8_t *)pThis + 53) = 0;  // 写字段 pThis[53]（宽1字节）
        *((uint8_t *)pThis + 54) = 0;  // 写字段 pThis[54]（宽1字节）
        sub_698F90((int)(pThis + 10), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        if ( dword_8F7C04 == 0 || *(uint8_t *)(dword_8F7C04 + 8052) == 0 )  // dword_8F7C04（本地玩家对象）
          sub_424A40((uint32_t *)pThis[4], dword_8F7C04);  // sub_424A40 —— 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
        sub_4684F0(*((uint32_t *)dword_8F8528 + 4), nullptr);  // sub_4684F0 —— 目标 HUD 更新（血条宽度 = 等级比）
      }
      break;
    case 1:  // case 1 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
      sub_4BF300(dword_8F8558, 0, 0);  // sub_4BF300 —— 槽写侧（+64 + 索引）
      v16 = sub_699000((int)(pThis + 10));  // 【clock_now(clk)】
      v17 = (int)(pThis + 10);
      if ( v16 < 1000 )
        goto LABEL_33;
      if ( sub_699000(v17) >= 2000 )  // 【clock_now(clk)】
      {
        if ( sub_699000((int)(pThis + 10)) >= 2000 )  // 【clock_now(clk)】
        {
          pThis[9] = 2;
          *((uint8_t *)pThis + 53) = 0;  // 写字段 pThis[53]（宽1字节）
          *((uint8_t *)pThis + 54) = 0;  // 写字段 pThis[54]（宽1字节）
          sub_698F90((int)(pThis + 10), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
          if ( dword_8F7C04 == 0 || *(uint8_t *)(dword_8F7C04 + 8052) == 0 )  // dword_8F7C04（本地玩家对象）
            sub_424A40((uint32_t *)pThis[4], dword_8F7C04);  // sub_424A40 —— 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
          sub_4684F0(*((uint32_t *)dword_8F8528 + 4), nullptr);  // sub_4684F0 —— 目标 HUD 更新（血条宽度 = 等级比）
          pThis[29] = 180000;
          sub_445830(1);  // sub_445830 —— 槽快照区复位 写 +1048944 旗标；置位时清 8 组 28 字节记录
        }
      }
      else
      {
        if ( dword_99FEC0 != 0  // dword_99FEC0 —— 对局中标志查询
          && sub_4525B0() == (uint16_t)word_77F804  // sub_4525B0 —— 自身槽 id 取出
          && *((uint8_t *)pThis + 54) == 1
          && pThis[31] != -1
          && (int)(GetTickCount() - pThis[31]) >= 10000 )  // 调 取系统运行毫秒数
        {
          v19 = *(uint16_t *)(sub_429830((uint16_t)word_77F804) + 4);  // sub_429830 —— 结果 = 表按键查找（uint16）
          v20 = sub_429830((uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
          if ( *(uint32_t *)(v20 + 40) < 0x10u )
            v21 = v20 + 20;  // 计算 v21 = v20 + 20
          else
            v21 = *(uint32_t *)(v20 + 20);  // 读字段 v21 = v20+20（nPage）
          off_77F3FC(aPvp, v21, v19);  // off_77F3FC —— 日志打印（printf 风格）
          do
          {
            v22 = sub_48F690((uint32_t *)dword_99FEC0, v2);  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
            if ( v22 != 0 && *((uint8_t *)pThis + v2 + 128) == 0 )
            {
              sub_48F500(v2, 254);  // sub_48F500 —— 座位状态上报发包（op 55）
              v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1216))(dword_8F7C04);  // 虚调用 vt+1216（dword_8F7C04 虚表槽）
              v24 = *(uint32_t *)(v22 + 40);  // 读字段 v24 = v22+40（bStateSub40）
              v25 = v23 == v2;
              v26 = *(uint16_t *)(v22 + 4);  // 读字段 v26 = v22+4（pHostObj）
              if ( v25 )
              {
                if ( v24 < 0x10 )
                {
                  v50 = v26;
                  v49 = v2;
                  v27 = v22 + 20;  // 计算 v27 = v22 + 20
                }
                else
                {
                  v27 = *(uint32_t *)(v22 + 20);  // 读字段 v27 = v22+20（nPage）
                  v50 = v26;
                  v49 = v2;
                }
                off_77F3FC(aPvp_5, v27, v49, v50);  // off_77F3FC —— 日志打印（printf 风格）
              }
              else
              {
                if ( v24 < 0x10 )
                  v28 = v22 + 20;  // 计算 v28 = v22 + 20
                else
                  v28 = *(uint32_t *)(v22 + 20);  // 读字段 v28 = v22+20（nPage）
                off_77F3FC(aPvp_0, v28, v2, v26);  // off_77F3FC —— 日志打印（printf 风格）
              }
            }
            ++v2;  // 计数自增 v2
          }
          while ( v2 < 8 );  // 循环直到 v2 < 8
          sub_452760(8);  // sub_452760 —— 主管理器状态推送
          pThis[31] = -1;
        }
        if ( pThis[7] == 0 )
        {
          pThis[31] = GetTickCount();  // pThis[31] = 调 GetTickCount
          sub_699030((int)(pThis + 10));  // 【clock_freeze(clk)】
          v58 = 0;
          if ( operator new(0x208u) != nullptr )  // 堆分配
          {
            v29 = sub_52C040(*((uint32_t *)dword_8F8528 + 8));  // dword_8F8528 —— 对象池借出（按池号取可用对象）
            v30 = sub_452B60(v29, 0);  // 调 取词条 → dword_8F84B8 vt+60 载入 .map → 场景层创建
          }
          else
          {
            v30 = 0;
          }
          v31 = pThis[8];
          v58 = -1;
          pThis[7] = v30;
          sub_45FC60(v31);  // sub_45FC60 —— ★ 对象表按类型过滤批量卸载（六类型码黑名单 + 两轮清理）
          sub_4602C0(*(uint32_t *)(pThis[7] + 476));  // sub_4602C0 —— 图标容器批量实例化
          sub_425460(pThis[4]);  // sub_425460 —— 模式切换清理
          v57 = sub_48F620((uint32_t *)dword_99FEC0);  // sub_48F620 —— 对局中标志查询
          v54 = 0;
          v55 = pThis + 20;  // 计算 v55 = pThis + 20
          do
          {
            v32 = sub_48F690((uint32_t *)dword_99FEC0, v54);  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
            v33 = v32;
            if ( v32 != 0 )
            {
              pObj = *(uint8_t **)(v32 + 196);
              (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 1020))(pObj);  // 虚调用 vt+1020（pObj 虚表槽）
              (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)pObj + 1200))(pObj, 0);  // 虚调用 vt+1200（pObj）(nArg1) —— 全体广播族。
              sub_45FE80(pThis2[8], v33, 273, *(uint16_t *)(v33 + 4), (int)pObj, 0, 0);  // sub_45FE80 —— 对象注册
              v35 = *(uint16_t *)(v33 + 4);  // 读字段 v35 = v33+4（pHostObj）
              v52 = 10;
              v53 = 250;
              for ( j = 0; j < 8; ++j )  // 遍历计次循环（j < 8）
              {
                if ( sub_48F690((uint32_t *)dword_99FEC0, j) != 0 )  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
                {
                  Block = *(uint16_t *)(sub_48F690((uint32_t *)dword_99FEC0, j) + 4);  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
                  v37 = sub_48F690((uint32_t *)dword_99FEC0, j);  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
                  v35 += Block
                       + (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v37 + 196) + 376))(*(uint32_t *)(v37 + 196));  // 调虚槽 +376：坐标同步包（type 37）
                }
              }
              if ( pObj[8052] != 0 )
              {
                (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)pObj + 112))(pObj, -10000, -10000, 0);  // 虚调用 vt+112（pObj）坐标三元组写入
                *v55 = 100000000;
              }
              else
              {
                if ( v57 )
                  v38 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 376))(pObj) + 1;  // 虚调用 vt+376（pObj 虚表槽）
                else
                  v38 = 0;
                sub_48C3A0((uint32_t *)pThis2[7], v38, &v52, &v53, (int)pObj, v35);  // sub_48C3A0 —— 重试找落点（上限 1000 次）
                (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)pObj + 112))(pObj, v52, v53, 0);  // 虚调用 vt+112（pObj）坐标三元组写入
                *v55 = 0;
              }
              v39 = *(uint32_t *)(pThis2[4] + 44);
              v40 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 120))(pObj);  // 虚调用 vt+120（pObj）转发(对象+缓冲)
              if ( v40 < sub_425050(v39) / 2 )  // sub_425050 —— 结果 = 总宽换算
                (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pObj + 148))(pObj, 1);  // 虚调用 vt+148（pObj）位置/朝向写入
              else
                (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)pObj + 148))(pObj, 0);  // 虚调用 vt+148（pObj）位置/朝向写入
            }
            v41 = v54;
            sub_48F580(v54, 0);  // sub_48F580 —— 座位/就绪表置位并刷新房间列表 写座位/就绪字节表 dword_99FEB8 加 槽号 = 值，随后
            v54 = v41 + 1;  // 计算 v54 = v41 + 1
            ++v55;  // 计数自增 v55
          }
          while ( v41 + 1 < 8 );  // 循环直到 v41 + 1 < 8
          pThis = pThis2;
          sub_425500(pThis2[7]);  // sub_425500 —— 锚定对象换绑
          sub_48E870(*(uint32_t *)(pThis[4] + 44), pThis[8]);  // sub_48E870 —— 地牢格快照与寻路网格重建
          v42 = sub_48F5A0();  // sub_48F5A0 —— 结果 = 自身座位下标查找（房间号比对）
          sub_452760(v42);  // sub_452760 —— 主管理器状态推送
        }
        v43 = sub_699000((int)(pThis + 10));  // 【clock_now(clk)】
        *((uint32_t *)dword_8F8528 + 621) = sub_423A80(255, 0, v43 - 1000, 1000);  // sub_423A80 —— 同上 int 版（FTOL 截断）
      }
      break;
    case 5:  // case 5 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
      sub_4BF300(dword_8F8558, 0, 0);  // sub_4BF300 —— 槽写侧（+64 + 索引）
      v44 = sub_699000((int)(pThis + 10));  // 【clock_now(clk)】
      v17 = (int)(pThis + 10);
      if ( v44 < 1000 )
      {
LABEL_33:
        v18 = sub_699000(v17);  // 【clock_now(clk)】
        *((uint32_t *)dword_8F8528 + 621) = sub_423A80(0, 255, v18, 1000);  // sub_423A80 —— 同上 int 版（FTOL 截断）
        break;
      }
      if ( sub_699000(v17) < 2000 )  // 【clock_now(clk)】
      {
        v45 = sub_699000((int)(pThis + 10));  // 【clock_now(clk)】
        *((uint32_t *)dword_8F8528 + 621) = sub_423A80(255, 0, v45 - 1000, 1000);  // sub_423A80 —— 同上 int 版（FTOL 截断）
        if ( dword_99FEC0 != 0 && *((uint8_t *)pThis + 120) == 0 )  // dword_99FEC0 —— 对局中标志查询
        {
          sub_423200(dword_8F7B08, 60);  // 【发送网络包API】
          sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
          *((uint8_t *)pThis + 120) = 1;  // 写字段 pThis+120（pAnimObj）
        }
      }
      break;
    default:
      break;
  }
  LOBYTE(v46) = *((uint8_t *)pThis + 136);
  if ( (uint8_t)v46 == 0 )
  {
    *((uint8_t *)pThis + 136) = 1;  // 写字段 pThis+136（nCtx136）
    v46 = (uint8_t *)(dword_8F8520 + 1048692);  // dword_8F8520 —— 虚表 +120 调用
    for ( k = 8; k != 0; --k )  // 遍历计次循环（k != 0）
    {
      if ( *v46 == 0 )
      {
        *v46 = 1;
        v46[1] = 0;
        v46[2] = 0;
      }
      v46 += 28;
    }
  }
  return (char)v46;
}


// ------------------------------------------------------------
// 0x4539D0 sub_4539D0 —— 界面对象析构
// +12..+28 五对象 vt[1] 释放 + +32 起 2 项清零。
// ------------------------------------------------------------
char /*thiscall*/ sub_4539D0(int this)  // sub_4539D0 —— 界面对象析构
{
  char result; // al
  int (/*thiscall*/ ***pThis_C)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_10)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_14)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_18)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_1C)(uint32_t, int); // ecx
  uint32_t *pThis_20; // esi
  int i; // edi

  result = *(uint8_t *)(this + 4);  // 读字段 result = this+4（pHostObj）
  if ( result != 0 )  // result=this+4 pHostObj
  {
    pThis_C = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
    *(uint8_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
    if ( pThis_C != nullptr )  // pThis_C=this+48 pCmdVecBegin48
      result = (**pThis_C)(pThis_C, 1);  // 调 pThis_C 的虚函数（vt+0）
    pThis_10 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 16);  // this+64〔apServerTabBtn(推断)〕
    *(uint32_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
    if ( pThis_10 != nullptr )  // pThis_10=this+64 apServerTabBtn
      result = (**pThis_10)(pThis_10, 1);  // 调 pThis_10 的虚函数（vt+0）
    pThis_14 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 20);  // this+80〔nAuraStage(推断)〕
    *(uint32_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
    if ( pThis_14 != nullptr )  // pThis_14=this+80 nAuraStage
      result = (**pThis_14)(pThis_14, 1);  // 调 pThis_14 的虚函数（vt+0）
    pThis_18 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 24);  // this+96〔nStatusMode(推断)〕
    *(uint32_t *)(this + 20) = 0;  // 写字段 this+20（nPage） ← 0
    if ( pThis_18 != nullptr )  // pThis_18=this+96 nStatusMode
      result = (**pThis_18)(pThis_18, 1);  // 调 pThis_18 的虚函数（vt+0）
    pThis_1C = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 28);  // this+112〔pHostComp112〕
    *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
    if ( pThis_1C != nullptr )  // pThis_1C=this+112 pHostComp112
      result = (**pThis_1C)(pThis_1C, 1);  // 调 pThis_1C 的虚函数（vt+0）
    *(uint32_t *)(this + 28) = 0;  // 写字段 this+28（pPanelVec） ← 0
    pThis_20 = (uint32_t *)(this + 32);  // this+32〔nHeight(推断)〕等 2 字段
    for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
    {
      if ( *pThis_20 != 0 )  // pThis_20=this+32 nHeight
        result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_20)(*pThis_20, 1);  // result=this+4 pHostObj
      *pThis_20++ = 0;  // pThis_20=this+32 nHeight
    }
  }
  return result;  // result=this+4 pHostObj
}



// ------------------------------------------------------------
// 0x453A60 sub_453A60 —— 交互状态复位
// +4 有效时把选中/悬停/箱号等 13 字段清零（+212 置 -1）。
// ------------------------------------------------------------
int /*thiscall*/ sub_453A60(int this)  // sub_453A60 —— (this+24 对象)
{
  int result; // eax

  result = 0;
  if ( *(uint8_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
  {
    *(uint8_t *)(this + 53) = 0;  // 写字段 this+53 ← 0
    *(uint8_t *)(this + 54) = 0;  // 写字段 this+54 ← 0
    *(uint8_t *)(this + 180) = 0;  // 写字段 this+180（nRadius） ← 0
    *(uint32_t *)(this + 288) = -1;  // 写字段 this+288（pMaster288） ← -1
    *(uint32_t *)(this + 292) = -1;  // 写字段 this+292（nOpenMode292） ← -1
    *(uint32_t *)(this + 220) = -1;  // 写字段 this+220（nSnapDst220） ← -1
    *(uint32_t *)(this + 224) = 0;  // 写字段 this+224（nSnapDst224） ← 0
    *(uint32_t *)(this + 228) = 0;  // 写字段 this+228（nSnapDst228） ← 0
    *(uint32_t *)(this + 232) = 0;  // 写字段 this+232（bSyncSwitch） ← 0
    *(uint8_t *)(this + 236) = 0;  // 写字段 this+236（nSyncArgA） ← 0
    *(uint32_t *)(this + 296) = -1;  // 写字段 this+296（bInitFlag296） ← -1
    *(uint8_t *)(this + 148) = 0;  // 写字段 this+148（fAdd148） ← 0
    *(uint32_t *)(this + 212) = -1;  // 写字段 this+212（nField212） ← -1
  }
  return result;
}



// ------------------------------------------------------------
// 0x453AC0 sub_453AC0 —— 锚定对象换装
// 旧 +17 的 +36 句柄解绑（69A580）→ 新对象挂接（69A840）+ 425960 级联广播。
// ------------------------------------------------------------
char /*thiscall*/ sub_453AC0(uint32_t *this, int pArg2)  // sub_453AC0 —— 锚定对象换装
{
  int fld_e17; // eax

  fld_e17 = *(this + 17);  // 读字段 fld_e17 = this+17（bEnable）
  if ( fld_e17 != pArg2 )  // fld_e17=this+17 bEnable
  {
    if ( fld_e17 != 0 )  // fld_e17=this+17 bEnable
      LOBYTE(fld_e17) = sub_69A580(*(uint32_t *)(fld_e17 + 36));  // 调 注销其资源后
    *(this + 17) = pArg2;  // 写字段 this+17（bEnable） ← pArg2
    if ( pArg2 != 0 )
    {
      sub_69A840(*(uint32_t *)(pArg2 + 36));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
      LOBYTE(fld_e17) = sub_425960(1, *(uint32_t *)(*(this + 17) + 44), *(int ***)(*(this + 17) + 104));  // sub_425960 —— 播放/暂停级联广播
    }
  }
  return fld_e17;  // fld_e17=this+17 bEnable
}



// ------------------------------------------------------------
// 0x453B10 sub_453B10 —— 地图消失处理
// MAP_DISAPPEAR 自证：置 +148/+165/+166 消失标记，经 dword_8F7A24+28 链换锚定对象并 vmt+124 通知主管理器，
// 末尾 424A40 解绑角色。
// ------------------------------------------------------------
int /*thiscall*/ sub_453B10(int this)  // sub_453B10 —— 地图消失处理 MAP_DISAPPEAR 自证：置 +148/+165/+166 消失标记，经 dword_8F7A24+28 链换锚定对象并 vmt+124 通知主管理器， 末尾 424A40 解绑角色。
{
  *(uint8_t *)(this + 148) = 1;  // 写字段 this+148（fAdd148） ← 1
  *(uint8_t *)(this + 165) = 0;  // 写字段 this+165 ← 0
  *(uint8_t *)(this + 166) = 0;  // 写字段 this+166 ← 0
  sub_432EA0("MAP_DISAPPEAR", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
  sub_453AC0((uint32_t *)this, *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16));  // sub_453AC0 —— 锚定对象换装
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 124))(  // 虚调用 vt+124（dword_8F8520）目标坐标y下界
    dword_8F8520,  // dword_8F8520 —— 虚表 +120 调用
    *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16));  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  return sub_424A40(*(uint32_t **)(this + 68), 0);  // sub_424A40 —— 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
}



// ------------------------------------------------------------
// 0x453B80 sub_453B80 —— 按钮点击登记
// CLICK_BUTTON2 自证：记录 nArg2..nArg4 到 +220/+224/+228（+232 置 1），
// +300 存 nArg2、+304 存 dword_99FB8C 时刻、+180 置忙。
// ------------------------------------------------------------
int /*thiscall*/ sub_453B80(int this, int nArg2, int nArg3, int nArg4)  // sub_453B80 —— 按钮点击登记 CLICK_BUTTON2 自证：记录 nArg2..nArg4 到 +220/+224/+228
{
  int result; // eax

  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
  *(uint32_t *)(this + 224) = nArg3;  // 写字段 this+224（nSnapDst224） ← nArg3
  *(uint32_t *)(this + 220) = nArg2;  // 写字段 this+220（nSnapDst220） ← nArg2
  *(uint32_t *)(this + 228) = nArg4;  // 写字段 this+228（nSnapDst228） ← nArg4
  *(uint32_t *)(this + 232) = 1;  // 写字段 this+232（bSyncSwitch） ← 1
  *(uint32_t *)(this + 300) = nArg2;  // 写字段 this+300（pAnim300） ← nArg2
  result = dword_99FB8C;  // dword_99FB8C —— 触发条件评估器：遍历条件对象
  *(uint32_t *)(this + 304) = dword_99FB8C;  // dword_99FB8C —— 触发条件评估器：遍历条件对象
  *(uint8_t *)(this + 180) = 1;  // 写字段 this+180（nRadius） ← 1
  return result;
}



// ------------------------------------------------------------
// 0x453BE0 sub_453BE0 —— 启动门判定
// clock_now(clk+40) > 20300 判定【推断：界面出现后的延时门槛】。
// ------------------------------------------------------------
bool /*thiscall*/ sub_453BE0(void *this)  // sub_453BE0 —— 启动门判定
{
  return sub_699000((int)this + 40) > 20300;  // 【clock_now(clk)】
}



// ------------------------------------------------------------
// 0x453C00 sub_453C00 —— 16 字节元素计数
// (+2 - +1) >> 4 计数（空表 0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_453C00(uint32_t *this)  // sub_453C00 —— 16 字节元素计数
{
  int fld_e1; // edx

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    return (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
  else
    return 0;
}



// ------------------------------------------------------------
// 0x453C20 sub_453C20 —— 16 字节元素区间填充
// [uArg1, uArg2) 每 16 字节元素拷 pArg3 四字段。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_453C20(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)  // sub_453C20 —— 16 字节元素区间填充
{
  uint32_t *result; // eax
  uint32_t *v4; // edi

  for ( result = uArg1; result != uArg2; v4[3] = pArg3[3] )
  {
    v4 = result;
    *result = *pArg3;
    result[1] = pArg3[1];  // result[1] = 取 pArg3[1]
    result[2] = pArg3[2];  // result[2] = 取 pArg3[2]
    result += 4;
  }
  return result;
}



// ------------------------------------------------------------
// 0x453C60 sub_453C60 —— 淡变状态机推进
// 以 476B60(+220) 角色渲染对象（+64）为载体；case 0..3 推进 countdown 与 4049C0 lerp，写全局调色 dword_8F8528+621，
// 完成一周期返回 1【推断：开箱全屏淡入】。
// ------------------------------------------------------------
char /*thiscall*/ sub_453C60(int this)  // sub_453C60 —— 淡变状态机推进
{
  int fld_DC; // ecx
  int fld_D4; // eax
  int pThis_B8; // eax
  uint64_t v6; // rax
  int fld_D0; // ebx
  int pThis_B82; // eax
  uint64_t v9; // rax

  fld_DC = *(uint32_t *)(sub_476B60(*(uint32_t *)(this + 220)) + 64);  // sub_476B60 —— 存 选区角色数据查找
  if ( fld_DC == 0 )
    return 0;
  (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)fld_DC + 152))(fld_DC, 0, 0, dword_79C0B0);  // 虚调用 vt+152（fld_DC）取值(参数)
  fld_D4 = *(uint32_t *)(this + 212);  // 读字段 fld_D4 = this+212（nField212）
  switch ( fld_D4 )  // 按 fld_D4 分派
  {
    case 0:  // case 0 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
      sub_698F90(this + 184, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      pThis_B8 = sub_699000(this + 184);  // 【clock_now(clk)】
      v6 = (uint64_t)sub_4049C0(255.0, 0.0, pThis_B8, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      *((uint32_t *)dword_8F8528 + 621) = v6;  // dword_8F8528 —— 对象池借出（按池号取可用对象）
      if ( sub_699000(this + 184) >= 300 )  // 【clock_now(clk)】
      {
        *(uint32_t *)(this + 212) = 1;  // 写字段 this+212（nField212） ← 1
        *(uint8_t *)(this + 197) = 0;  // 写字段 this+197（field_00C5） ← 0
        *(uint8_t *)(this + 198) = 0;  // 写字段 this+198（field_00C6） ← 0
        sub_698F90(this + 184, 1500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
      return 0;
    case 1:  // case 1 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
      fld_D0 = *(uint32_t *)(this + 208);  // 读字段 fld_D0 = this+208（nField208）
      if ( sub_699000(this + 184) < fld_D0 )  // 【clock_now(clk)】
        return 0;
      *(uint32_t *)(this + 212) = 2;  // 写字段 this+212（nField212） ← 2
      *(uint8_t *)(this + 197) = 0;  // 写字段 this+197（field_00C5） ← 0
      *(uint8_t *)(this + 198) = 0;  // 写字段 this+198（field_00C6） ← 0
      return 0;
    case 2:  // case 2 分派（CNPVPModule 与座位管理（0x452FA0-0x454610））
      sub_698F90(this + 184, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      pThis_B82 = sub_699000(this + 184);  // 【clock_now(clk)】
      v9 = (uint64_t)sub_4049C0(0.0, 255.0, pThis_B82, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      *((uint32_t *)dword_8F8528 + 621) = v9;  // dword_8F8528 —— 对象池借出（按池号取可用对象）
      if ( sub_699000(this + 184) < 300 )  // 【clock_now(clk)】
        return 0;
      *(uint32_t *)(this + 212) = 3;  // 写字段 this+212（nField212） ← 3
      return 1;  // 返回 1(成功)
    default:
      return 0;
  }
}



// ------------------------------------------------------------
// 0x453DA0 sub_453DA0 —— 参战 id 变更检测
// 472E30 查键值与 +13 现值比对，返回是否变更。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_453DA0(uint32_t *this, char pszArg2)  // sub_453DA0 —— 参战 id 变更检测
{
  uint8_t v3[4]; // [esp+4h] [ebp-4h] BYREF

  return *(uint32_t *)sub_472E30(v3, &pszArg2) != *(this + 13);  // 返回 读 this+13
}



// ------------------------------------------------------------
// 0x453DD0 sub_453DD0
// ------------------------------------------------------------
// 座位/选中槽同步 —— 战斗分发器 case 2/3 落点：
// +276 座位表（16 字节/项）/ +288 当前选中；a2==当前且 +4 槽位吻合则短路返回；
// 换座经 sub_476B60 取角色数据 → 23 字节/项的名字表刷新（sub_69A5F0）→
// +16/+20 按钮可见性 → a3!=4 时回写 +4 槽位并播 CLICK_BUTTON2
char /*thiscall*/ sub_453DD0(int this, unsigned int uArg2, int nArg3)  // sub_453DD0 —— 选中槽同步
{
  int fld_78; // eax
  int fld_120; // ecx
  char v6; // dl
  int fld_114; // edx
  int fld_782; // ebx
  int v9; // edi
  bool v10; // al
  int fld_1202; // eax
  int dword_8F850C2; // edi
  int v13; // edi
  int fld_1203; // eax
  int fld_1142; // edi
  int fld_1204; // ecx
  int nArg32; // eax
  int *pThis_6C; // edi
  char v19; // cl
  int v20; // ecx
  uint32_t **pThis_20; // [esp+8h] [ebp-8h]
  int v23; // [esp+8h] [ebp-8h]
  int v24; // [esp+8h] [ebp-8h]
  char v25; // [esp+Fh] [ebp-1h]

  fld_78 = uArg2;
  fld_120 = *(uint32_t *)(this + 288);  // 读字段 fld_120 = this+288（pMaster288）
  if ( fld_120 == uArg2 && (uArg2 == -1 || *(uint32_t *)(*(uint32_t *)(this + 276) + 16 * uArg2 + 4) == nArg3) )  // this+276 地图条目指针
    return fld_78;
  v6 = 0;
  v25 = 0;
  if ( fld_120 != uArg2 )  // fld_120=this+288 pMaster288
  {
    if ( uArg2 != -1 )
    {
      fld_114 = *(uint32_t *)(this + 276);  // 读字段 fld_114 = this+276（pMapEntry）
      if ( fld_114 == 0 )  // fld_114=this+276 pMapEntry
        return fld_78;
      if ( (*(uint32_t *)(this + 280) - fld_114) >> 4 <= uArg2 )  // this+280 地图条目数组 end
        return fld_78;
      fld_78 = sub_476B60(*(uint32_t *)(fld_114 + 16 * uArg2));  // sub_476B60 —— 存 选区角色数据查找
      fld_782 = fld_78;
      if ( fld_78 == 0 )
        return fld_78;
      v9 = 0;
      pThis_20 = (uint32_t **)(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
      do
      {
        sub_69A5F0(*pThis_20, v9 + *(uint32_t *)(fld_782 + 80) + 61, *(uint32_t *)(fld_782 + 84) + 65);  // 调 设位、sub_69A840 登记
        v9 += 23;
        ++pThis_20;  // 计数自增 pThis_20
      }
      while ( v9 < 46 );  // 循环直到 v9 < 46
      fld_78 = uArg2;
    }
    *(uint32_t *)(this + 288) = fld_78;  // 写字段 this+288（pMaster288） ← fld_78
    v10 = fld_78 != -1;
    *(uint8_t *)(*(uint32_t *)(this + 32) + 16) = v10;  // this+32〔nHeight(推断)〕等 2 字段
    *(uint8_t *)(*(uint32_t *)(this + 36) + 16) = v10;  // this+36〔nStateWord36(推断)〕等 2 字段
    v6 = 1;
    v25 = 1;
  }
  fld_1202 = *(uint32_t *)(this + 288);  // 读字段 fld_1202 = this+288（pMaster288）
  if ( fld_1202 != -1 && nArg3 != 4 )  // fld_1202=this+288 pMaster288
  {
    *(uint32_t *)(16 * fld_1202 + *(uint32_t *)(this + 276) + 4) = nArg3;  // this+276〔pMapEntry〕
LABEL_17:
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    goto LABEL_18;
  }
  if ( v6 != 0 )
    goto LABEL_17;
LABEL_18:
  dword_8F850C2 = dword_8F850C;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
  if ( sub_456480(dword_8F850C) == -1 )  // sub_456480 —— 存 座位号
    v13 = 0;
  else
    v13 = *(uint32_t *)(dword_8F850C2 + 4 * sub_456480(dword_8F850C2) + 16);  // sub_456480 —— 存 座位号
  if ( v13 == sub_429830((uint16_t)word_77F804) )  // sub_429830 —— 结果 = 表按键查找（uint16）
  {
    *(uint8_t *)(*(uint32_t *)(this + 32) + 17) = *(uint32_t *)(16 * *(uint32_t *)(this + 288) + *(uint32_t *)(this + 276) + 4) != 0;  // this+32〔nHeight(推断)〕等 5 字段
    *(uint8_t *)(*(uint32_t *)(this + 36) + 17) = *(uint32_t *)(*(uint32_t *)(this + 276) + 16 * *(uint32_t *)(this + 288) + 4) != *(uint32_t *)(16 * *(uint32_t *)(this + 288) + *(uint32_t *)(this + 276) + 8);  // this+36〔nStateWord36(推断)〕等 5 字段
  }
  fld_1203 = *(uint32_t *)(this + 288);  // 读字段 fld_1203 = this+288（pMaster288）
  HIWORD(uArg2) = 0;
  if ( fld_1203 != -1 )  // fld_1203=this+288 pMaster288
  {
    fld_1142 = 16 * fld_1203 + *(uint32_t *)(this + 276);  // this+276〔pMapEntry〕
    if ( *(uint32_t *)(fld_1142 + 4) != 0 )  // fld_1142=this+276 pMapEntry
    {
      BYTE2(uArg2) = 1;
      if ( sub_456390(0) <= *(uint32_t *)(fld_1142 + 4) )  // sub_456390 —— 存 座位号查询
      {
        fld_1204 = *(uint32_t *)(16 * *(uint32_t *)(this + 288) + *(uint32_t *)(this + 276) + 4) + 1;  // this+288〔pMaster288(推断)〕等 3 字段
        HIBYTE(uArg2) = 1;
        *(uint32_t *)(this + 144) = fld_1204;  // 写字段 this+144（pFrameList144） ← fld_1204
      }
    }
  }
  nArg32 = 0;
  nArg3 = 0;
  pThis_6C = (int *)(this + 108);  // this+108〔nAdd108(推断)〕
  do
  {
    v19 = *((uint8_t *)&uArg2 + nArg32 + 2);
    if ( *(uint8_t *)(this + nArg32 + 140) != v19 )
    {
      *(uint8_t *)(this + nArg32 + 140) = v19;
      v23 = *pThis_6C;  // pThis_6C=this+108 nAdd108
      if ( v23 < sub_699000((int)(pThis_6C - 6)) )  // 【clock_now(clk)】
      {
        v20 = 0;
      }
      else
      {
        v24 = *pThis_6C;  // pThis_6C=this+108 nAdd108
        v20 = v24 - sub_699000((int)(pThis_6C - 6));  // 【clock_now(clk)】
      }
      *((uint8_t *)pThis_6C - 11) = 0;  // pThis_6C=this+108 nAdd108
      *((uint8_t *)pThis_6C - 10) = 0;  // pThis_6C=this+108 nAdd108
      sub_698F90((int)(pThis_6C - 6), 300, v20);  // 【clock_set_countdown(clk, duration=a2, star…】
      nArg32 = nArg3;
    }
    ++nArg32;  // 计数自增 nArg32
    pThis_6C += 7;  // pThis_6C=this+108 nAdd108
    nArg3 = nArg32;
  }
  while ( nArg32 < 2 );  // 循环直到 nArg32 < 2
  LOBYTE(fld_78) = v25;
  if ( v25 != 0 )
  {
    LOBYTE(fld_78) = *(uint8_t *)(this + 126);  // this+126〔field_007E〕
    if ( (uint8_t)fld_78 != 0 )
    {
      *(uint32_t *)(this + 132) = 300;  // 写字段 this+132（nAdd132） ← 300
    }
    else
    {
      fld_78 = dword_79D100[*(uint32_t *)(this + 120)];  // this+120〔pAnimObj〕
      *(uint32_t *)(this + 128) = 300 - fld_78;  // 写字段 this+128（szStatusKeyBuf） ← 300 - fld_78
    }
  }
  return fld_78;  // fld_78=this+120 pAnimObj
}


// ------------------------------------------------------------
// 0x454070 sub_454070 —— 悬停命中检测
// 门禁：456480 自身座位 == 429830(word_77F804)、+180 未忙、43BCB0 焦点窗口；
// 对 +276 座位表逐项矩形命中（选中 168×63 / 未选 118×53），返回槽下标或 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_454070(int this)  // sub_454070 —— 悬停命中检测
{
  int dword_8F850C2; // esi
  int v3; // esi
  int fld_114; // ecx
  int v6; // esi
  int fld_1142; // eax
  int fld_120; // ecx
  BOOL v9; // edx
  LONG v10; // edi
  LONG v11; // eax
  LONG y; // [esp+8h] [ebp-10h]
  LONG x; // [esp+Ch] [ebp-Ch]
  int fld_118; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  dword_8F850C2 = dword_8F850C;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
  if ( sub_456480(dword_8F850C) == -1 )  // sub_456480 —— 存 座位号
    v3 = 0;
  else
    v3 = *(uint32_t *)(dword_8F850C2 + 4 * sub_456480(dword_8F850C2) + 16);  // sub_456480 —— 存 座位号
  if ( v3 != sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )  // sub_429830 —— 结果 = 表按键查找（uint16）
    return -1;
  if ( *(uint8_t *)(this + 180) != 0 )  // this+180〔nRadius(推断)〕
    return -1;
  if ( !sub_43BCB0(*(uint32_t *)(this + 20)) )  // sub_43BCB0 —— 焦点窗口判定（三选）
    return -1;
  x = pt.x;
  fld_114 = *(uint32_t *)(this + 276);  // 读字段 fld_114 = this+276（pMapEntry）
  v6 = 0;
  y = pt.y;
  if ( fld_114 != 0 )  // fld_114=this+276 pMapEntry
    fld_118 = (*(uint32_t *)(this + 280) - fld_114) >> 4;  // this+280〔pMapEntryVecEnd〕
  else
    fld_118 = 0;  // fld_118=this+280 pMapEntryVecEnd
  if ( fld_118 <= 0 )  // fld_118=this+280 pMapEntryVecEnd
    return -1;
  for ( i = 0; ; i += 16 )
  {
    fld_1142 = sub_476B60(*(uint32_t *)(i + *(uint32_t *)(this + 276)));  // sub_476B60 —— 存 选区角色数据查找
    fld_120 = *(uint32_t *)(this + 288);  // 读字段 fld_120 = this+288（pMaster288）
    v9 = v6 == fld_120;  // fld_120=this+288 pMaster288
    v10 = *(uint32_t *)(fld_1142 + 8 * v9 + 72);
    v11 = *(uint32_t *)(fld_1142 + 8 * v9 + 76);
    if ( x >= v10 && x < v10 + (v6 != fld_120 ? 118 : 168) && y >= v11 && y < v11 + (v6 != fld_120 ? 53 : 63) )  // 判定 x >= v10 且 x < v10 且 v6 != fld_120
      break;
    if ( ++v6 >= fld_118 )  // fld_118=this+280 pMapEntryVecEnd
      return -1;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x4541B0 sub_4541B0 —— 座位矩形查询
// 同 ·0x454070 门禁；命中槽经 476B60 输出 x/y/w/h 四出参（尺寸随选中态）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4541B0(int this, int nArg2, uint32_t *uArg3, uint32_t *uArg4, uint32_t *uArg5, uint32_t *uArg6)  // sub_4541B0 —— 座位矩形查询
{
  int dword_8F850C2; // edi
  int v8; // edi
  int fld_114; // eax

  dword_8F850C2 = dword_8F850C;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
  if ( sub_456480(dword_8F850C) == -1 )  // sub_456480 —— 存 座位号
    v8 = 0;
  else
    v8 = *(uint32_t *)(dword_8F850C2 + 4 * sub_456480(dword_8F850C2) + 16);  // sub_456480 —— 存 座位号
  if ( v8 == sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )  // sub_429830 —— 结果 = 表按键查找（uint16）
  {
    if ( *(uint8_t *)(this + 180) != 0 )  // this+180〔nRadius(推断)〕
      return -1;
    if ( sub_43BCB0(*(uint32_t *)(this + 20)) )  // sub_43BCB0 —— 焦点窗口判定（三选）
    {
      fld_114 = sub_476B60(*(uint32_t *)(*(uint32_t *)(this + 276) + 16 * nArg2));  // sub_476B60 —— 存 选区角色数据查找
      *uArg3 = *(uint32_t *)(fld_114 + 8 * (nArg2 == *(uint32_t *)(this + 288)) + 72);  // this+288〔pMaster288(推断)〕
      *uArg4 = *(uint32_t *)(fld_114 + 8 * (nArg2 == *(uint32_t *)(this + 288)) + 76);  // this+288〔pMaster288(推断)〕
      *uArg5 = nArg2 != *(uint32_t *)(this + 288) ? 118 : 168;  // this+288〔pMaster288(推断)〕
      *uArg6 = nArg2 != *(uint32_t *)(this + 288) ? 53 : 63;  // this+288〔pMaster288(推断)〕
    }
  }
  return -1;
}



// ------------------------------------------------------------
// 0x4542A0 sub_4542A0 —— 按钮可见态刷新
// 按自身座位与 +288 选中槽状态，刷新 +6..+9 四按钮 +16/+17 可见位。
// ------------------------------------------------------------
char /*thiscall*/ sub_4542A0(uint32_t *this)  // sub_4542A0 —— 按钮可见态刷新
{
  int dword_8F850C2; // edi
  int v3; // edi
  int v4; // eax
  bool v5; // cl
  int fld_e72; // eax
  bool v7; // al
  int fld_e722; // eax

  dword_8F850C2 = dword_8F850C;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
  if ( sub_456480(dword_8F850C) == -1 )  // sub_456480 —— 存 座位号
    v3 = 0;
  else
    v3 = *(uint32_t *)(dword_8F850C2 + 4 * sub_456480(dword_8F850C2) + 16);  // sub_456480 —— 存 座位号
  v4 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
  v5 = v3 == v4;
  *(uint8_t *)(*(this + 6) + 16) = v3 == v4;  // this+24〔nPageMax(推断)〕
  *(uint8_t *)(*(this + 7) + 16) = v3 == v4;  // this+28〔pPanelVec(推断)〕
  *(uint8_t *)(*(this + 7) + 16) = 0;  // this+28〔pPanelVec(推断)〕
  v7 = false;
  if ( v3 == v4 )
  {
    fld_e72 = *(this + 72);  // 读字段 fld_e72 = this+72（nSnapshot72）
    if ( fld_e72 != -1 && *(uint32_t *)(16 * fld_e72 + *(this + 69) + 4) != 0 )  // fld_e72=this+72 nSnapshot72
      v7 = true;
  }
  *(uint8_t *)(*(this + 8) + 17) = v7;  // this+32〔nHeight(推断)〕
  if ( !v5
    || (fld_e722 = *(this + 72)) == -1  // this+288〔pMaster288(推断)〕
    || *(uint32_t *)(16 * fld_e722 + *(this + 69) + 4) == *(uint32_t *)(*(this + 69) + 16 * fld_e722 + 8) )  // this+276〔pMapEntry〕
  {
    *(uint8_t *)(*(this + 9) + 17) = 0;  // this+36〔nStateWord36(推断)〕
    return 0;
  }
  else
  {
    *(uint8_t *)(*(this + 9) + 17) = 1;  // this+36〔nStateWord36(推断)〕
    return 1;  // 返回 1(成功)
  }
}



// ------------------------------------------------------------
// 0x454360 sub_454360 —— 副本选择界面构造
// Interface/SelectDungeonEvent.img 自证（dword_8F84B8 vt+60）；+4 闸门装配 7 个控件 + 底图句柄
// （640×480 层 + 202×41 与 155×38 图元），末段复位 +148..+212 状态。
// ------------------------------------------------------------
char /*thiscall*/ sub_454360(int this)  // sub_454360 —— 副本选择界面构造
{
  char result; // al
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  uint8_t *pMem2; // eax
  uint8_t *v6; // eax
  uint8_t *pMem3; // eax
  uint8_t *v8; // eax
  uint8_t *pMem4; // eax
  uint8_t *v10; // eax
  uint8_t *pMem5; // eax
  uint8_t *v12; // eax
  uint32_t *pThis_20; // edi
  uint8_t *pMem6; // eax
  uint8_t *v15; // eax
  int Block; // [esp+8h] [ebp-10h]

  result = *(uint8_t *)(this + 4);  // 读字段 result = this+4（pHostObj）
  if ( result == 0 )  // result=this+4 pHostObj
  {
    *(uint8_t *)(this + 4) = 1;  // 写字段 this+4（pHostObj） ← 1
    *(uint32_t *)(this + 72) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 76);  // dword_99FCC8 —— nengine::CNSlider 构造
    *(uint32_t *)(this + 76) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 80);  // dword_99FCC8 —— nengine::CNSlider 构造
    *(uint32_t *)(this + 80) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
                               dword_8F84B8,  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
                               "Interface/SelectDungeonEvent.img");  // 资源 Interface/SelectDungeonEvent.img
    pMem = operator new(0x68u);  // 堆分配
    if ( pMem != nullptr )
      v4 = sub_426BD0(pMem);  // sub_426BD0 —— nengine::IControl 构造
    else
      v4 = nullptr;
    *(uint32_t *)(this + 12) = v4;  // 写字段 this+12（nSkillRec12） ← v4
    pMem2 = operator new(0x68u);  // 堆分配
    if ( pMem2 != nullptr )
      v6 = sub_426BD0(pMem2);  // sub_426BD0 —— nengine::IControl 构造
    else
      v6 = nullptr;
    *(uint32_t *)(this + 16) = v6;  // 写字段 this+16（nChannelTypeSel） ← v6
    sub_69A840(v6);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    sub_69A840(*((uint32_t *)dword_8F8528 + 2));  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    pMem3 = operator new(0x68u);  // 堆分配
    if ( pMem3 != nullptr )
      v8 = sub_426BD0(pMem3);  // sub_426BD0 —— nengine::IControl 构造
    else
      v8 = nullptr;
    *(uint32_t *)(this + 20) = v8;  // 写字段 this+20（nPage） ← v8
    *((uint32_t *)v8 + 7) = 640;  // 写字段 v8+7（uPathTerm）
    *((uint32_t *)v8 + 8) = 480;  // 写字段 v8+8（nSkillRec8）
    *(uint32_t *)(*(uint32_t *)(this + 20) + 68) = this + 8;  // this+20〔nPage(推断)〕等 2 字段
    pMem4 = operator new(0x68u);  // 堆分配
    if ( pMem4 != nullptr )
      v10 = sub_426BD0(pMem4);  // sub_426BD0 —— nengine::IControl 构造
    else
      v10 = nullptr;
    *(uint32_t *)(this + 24) = v10;  // 写字段 this+24（nPageMax） ← v10
    *((uint32_t *)v10 + 7) = 202;  // 写字段 v10+7（uPathTerm）
    *((uint32_t *)v10 + 8) = 41;  // 写字段 v10+8（nSkillRec8）
    sub_69A5F0(*(uint32_t **)(this + 24), 417, 371);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 24));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    pMem5 = operator new(0x68u);  // 堆分配
    if ( pMem5 != nullptr )
      v12 = sub_426BD0(pMem5);  // sub_426BD0 —— nengine::IControl 构造
    else
      v12 = nullptr;
    *(uint32_t *)(this + 28) = v12;  // 写字段 this+28（pPanelVec） ← v12
    *((uint32_t *)v12 + 7) = 155;  // 写字段 v12+7（uPathTerm）
    *((uint32_t *)v12 + 8) = 38;  // 写字段 v12+8（nSkillRec8）
    sub_69A5F0(*(uint32_t **)(this + 28), 418, 411);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 28));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    pThis_20 = (uint32_t *)(this + 32);  // this+32〔nHeight(推断)〕等 2 字段
    for ( Block = 2; Block != 0; --Block )  // 遍历计次循环（Block != 0）
    {
      pMem6 = operator new(0x68u);  // 堆分配
      if ( pMem6 != nullptr )
        v15 = sub_426BD0(pMem6);  // sub_426BD0 —— nengine::IControl 构造
      else
        v15 = nullptr;
      *pThis_20 = v15;  // pThis_20=this+32 nHeight
      *((uint32_t *)v15 + 7) = 22;  // 写字段 v15+7（uPathTerm）
      *((uint32_t *)v15 + 8) = 14;  // 写字段 v15+8（nSkillRec8）
      *(uint8_t *)(*pThis_20 + 16) = 0;  // pThis_20=this+32 nHeight
      sub_69A840(*pThis_20++);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    }
    sub_69A840(*(uint32_t *)(this + 20));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    sub_69A840(*((uint32_t *)dword_8F8528 + 3));  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    result = *(uint8_t *)(this + 4);  // 读字段 result = this+4（pHostObj）
    if ( result != 0 )  // result=this+4 pHostObj
    {
      *(uint8_t *)(this + 53) = 0;  // 写字段 this+53 ← 0
      *(uint8_t *)(this + 54) = 0;  // 写字段 this+54 ← 0
      *(uint8_t *)(this + 180) = 0;  // 写字段 this+180（nRadius） ← 0
      *(uint32_t *)(this + 288) = -1;  // 写字段 this+288（pMaster288） ← -1
      *(uint32_t *)(this + 292) = -1;  // 写字段 this+292（nOpenMode292） ← -1
      *(uint32_t *)(this + 220) = -1;  // 写字段 this+220（nSnapDst220） ← -1
      *(uint32_t *)(this + 224) = 0;  // 写字段 this+224（nSnapDst224） ← 0
      *(uint32_t *)(this + 228) = 0;  // 写字段 this+228（nSnapDst228） ← 0
      *(uint32_t *)(this + 232) = 0;  // 写字段 this+232（bSyncSwitch） ← 0
      *(uint8_t *)(this + 236) = 0;  // 写字段 this+236（nSyncArgA） ← 0
      *(uint32_t *)(this + 296) = -1;  // 写字段 this+296（bInitFlag296） ← -1
      *(uint8_t *)(this + 148) = 0;  // 写字段 this+148（fAdd148） ← 0
      *(uint32_t *)(this + 212) = -1;  // 写字段 this+212（nField212） ← -1
      return 0;
    }
  }
  return result;  // result=this+4 pHostObj
}



// ============================================================
// 【分区 4】副本选择界面（0x454610-0x455E20）
// CNSelectDungeonModule__vmt4 = 副本选择帧（MAP_MOUSEOVER/MAP_SELECT）；
// 副本倒计时巨函数 0x454F00（MAP_COUNTDOWN 自证，~780 行）。
// ============================================================
// ------------------------------------------------------------
// 0x454610 sub_454610 —— 座位选定提交
// 目标槽 +69[].+12 有效（或 uArg2==-1）时先 453DD0 同步，再主管理器 vmt+8(3,1) + 两次 vmt+32 + 提交。
// ------------------------------------------------------------
int /*thiscall*/ sub_454610(uint32_t *this, unsigned int uArg2, int nArg3)  // sub_454610 —— 座位选定提交
{
  int result; // eax

  if ( uArg2 == -1 || *(uint32_t *)((result = *(this + 69) + 16 * uArg2) + 12) != -1 )
  {
    sub_453DD0((int)this, uArg2, nArg3);  // sub_453DD0 —— 选中槽同步
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 3, 1);  // 虚调用 vt+8（dword_8F8520 虚表槽）
    (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, uArg2);  // 虚调用 vt+32（dword_8F8520 虚表槽）
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nArg3);  // 虚调用 vt+32（dword_8F8520 虚表槽）
    return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 虚调用 vt+60（dword_8F8520）对象销毁/释放
  }
  return result;
}



// ------------------------------------------------------------
// 0x454680 sub_454680 —— 房间选择确认
// 按房间 id 定位槽 → 454610 提交；发包 op 16 = 房间 id(u16) + 类型(u8)【推断：进入房间请求】，
// 置 +180 忙、熄四按钮，收尾触发事件 55。
// ------------------------------------------------------------
char /*thiscall*/ sub_454680(int this, int nArg2, int nArg3)  // sub_454680 —— 房间选择确认
{
  int nArg22; // ebx
  int fld_114; // edx
  unsigned int v6; // ecx
  int v7; // edi
  int fld_18; // eax

  nArg22 = nArg2;
  fld_114 = *(uint32_t *)(this + 276);  // 读字段 fld_114 = this+276（pMapEntry）
  v6 = 0;
  v7 = 0;
  while ( fld_114 != 0 && v6 < (*(uint32_t *)(this + 280) - fld_114) >> 4 )  // 循环直到 fld_114 != 0
  {
    if ( *(uint32_t *)(v7 + *(uint32_t *)(this + 276)) == nArg2 )  // this+276〔pMapEntry〕
    {
      sub_454610((uint32_t *)this, v6, nArg3);  // sub_454610 —— 座位选定提交
      break;
    }
    ++v6;  // 计数自增 v6
    v7 += 16;
  }
  sub_423200(dword_8F7B08, 16);  // 【发送网络包API】
  nArg2 = nArg22;
  sub_423290(dword_8F7B08, (int)&nArg2, 2);  // sub_423290 —— 写 4B 长度
  HIBYTE(nArg3) = nArg3;
  sub_423290(dword_8F7B08, (int)&nArg3 + 3, 1);  // sub_423290 —— 写 4B 长度
  sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
  fld_18 = *(uint32_t *)(this + 24);  // 读字段 fld_18 = this+24（nPageMax）
  *(uint8_t *)(this + 180) = 1;  // 写字段 this+180（nRadius） ← 1
  *(uint8_t *)(fld_18 + 17) = 0;  // 写字段 fld_18+17（bEnable） ← 0
  *(uint8_t *)(*(uint32_t *)(this + 28) + 17) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint8_t *)(*(uint32_t *)(this + 32) + 17) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  *(uint8_t *)(*(uint32_t *)(this + 36) + 17) = 0;  // this+36〔nStateWord36(推断)〕等 2 字段
  return sub_44E850(dword_8F8528, 55);  // sub_44E850 —— 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
}



// ------------------------------------------------------------
// 0x454740 CNSelectDungeonModule__vmt4
// ------------------------------------------------------------
// CNSelectDungeonModule::vmt4 —— 副本选择界面帧（RTTI 自证）：
// 主帧循环 → 选中项命中测试 sub_454070（1100ms 启动门 +180）→
// MAP_MOUSEOVER（悬停变更）/ MAP_SELECT（确认）；悬停信息条 dword_8F8528 vt 55
char /*thiscall*/ sub_454740(int this)  // 【CNSelectDungeonModule__vmt4】
{
  int pFrameTickObj; // ecx  | +0x0044 → 每帧驱动对象（0x454740: sub_4294E0(fld_44=+68) 逐帧驱动）【推断】（CNSelectDungeonModule；va=00454740）
  int dword_8F850C2; // edi
  int v4; // edi
  int v5; // eax
  int v6; // edi
  int *fld_114; // eax
  int pObj; // ebx
  int pBtnMapEntry; // eax  | +0x0014 → ★ 地图条目按钮（CNSelectDungeonModule；va=00454740）
  int pBtnConfirm; // eax  | +0x0018 → 确认/进入按钮（CNSelectDungeonModule；va=00454740）
  int pMapEntry; // edx  | +0x0114 → ★ 地图条目指针（CNSelectDungeonModule；va=00454740）
  unsigned int nSelMap; // edi  | +0x0120 → ★ 选中地图索引（CNSelectDungeonModule；va=00454740）
  int pBtnDiffDown; // eax  | +0x0020 → ★ 难度降档按钮（CNSelectDungeonModule；va=00454740）
  int pBtnDiffUp; // eax  | +0x0024 → ★ 难度升档按钮（CNSelectDungeonModule；va=00454740）
  int nPhase; // eax  | +0x00E8 → ★ 阶段状态机（0x454740: 1→2→3→4 推进；==2 且倒计时到点进入入场演出）（CNSelectDungeonModule；va=00454740）
  int *fld_DC; // eax
  int nPhase_; // eax  | +0x00E8 → ★ 阶段状态机（0x454740: 1→2→3→4 推进；==2 且倒计时到点进入入场演出）（CNSelectDungeonModule；va=00454740）
  int pThis_98; // eax
  uint64_t v19; // rax
  int v20; // eax
  int pThis_F0; // eax
  int v23; // [esp+4h] [ebp-10h] BYREF
  int v24; // [esp+8h] [ebp-Ch] BYREF
  int v25; // [esp+Ch] [ebp-8h] BYREF
  int v26; // [esp+10h] [ebp-4h] BYREF

  sub_433690();  // 【= 主帧 tick（timeGetTime 驱动；'SHUTTER_ON' 截屏音效…】
  pFrameTickObj = *(uint32_t *)(this + 68);  // 读字段 fld_44 = this+68（nCharCount）
  if ( pFrameTickObj != 0 )  // fld_44=this+68 nCharCount
    sub_4294E0(pFrameTickObj);  // sub_4294E0 —— HUD 每帧总 tick（尾段）
  dword_8F850C2 = dword_8F850C;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
  if ( sub_456480(dword_8F850C) == -1 )  // sub_456480 —— 存 座位号
    v4 = 0;
  else
    v4 = *(uint32_t *)(dword_8F850C2 + 4 * sub_456480(dword_8F850C2) + 16);  // sub_456480 —— 存 座位号
  if ( v4 == sub_429830((uint16_t)word_77F804) && *(uint8_t *)(this + 180) == 0 && sub_699000(this + 40) >= 1100 )  // sub_429830 —— 结果 = 表按键查找（uint16）；sub_699000 —— 【clock_now(clk)】
  {
    v5 = sub_454070(this);  // sub_454070 —— 悬停命中检测
    v6 = v5;
    if ( v5 != *(uint32_t *)(this + 292) )  // this+292〔nHoverMap〕
    {
      if ( v5 != -1 && v5 != *(uint32_t *)(this + 288) )  // this+288 nSelMap
        sub_432EA0("MOUSE_OVER", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
      *(uint32_t *)(this + 292) = v6;  // 写字段 this+292（nOpenMode292） ← v6
      if ( v6 == -1 || *(uint8_t *)(this + 180) != 0 )  // this+180 bStartGate
      {
        sub_44E850(dword_8F8528, 55);  // sub_44E850 —— 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
      }
      else
      {
        fld_114 = (int *)(*(uint32_t *)(this + 276) + 16 * v6);  // this+276〔pMapEntry〕
        if ( *fld_114 != dword_795314 )  // fld_114=this+276 pMapEntry
        {
          pObj = sub_44E8D0((char *)dword_8F8528, (void *)0x37, 0, *fld_114);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）
          if ( pObj != 0 )
          {
            v23 = 0;
            v24 = 0;
            v25 = 0;
            v26 = 0;
            sub_4541B0(v6, &v23, &v24, &v25, &v26);  // sub_4541B0 —— 座位矩形查询
            (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pObj + 48))(pObj, v23, v24, v25, v26);  // 虚调用 vt+48（pObj）归属坐标x
          }
        }
      }
    }
    pBtnMapEntry = *(uint32_t *)(this + 20);  // 读字段 fld_14 = this+20（nPage）
    if ( *(uint8_t *)(pBtnMapEntry + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnMapEntry + 12) && v6 != -1 )  // fld_14=this+20 nPage
    {
      if ( v6 == *(uint32_t *)(this + 288) )  // this+288〔nSelMap〕
        goto LABEL_27;
      sub_454610(v6, 4);  // sub_454610 —— 座位选定提交
      sub_432EA0("MAP_MOUSEOVER", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    }
    pBtnConfirm = *(uint32_t *)(this + 24);  // 读字段 fld_18 = this+24（nPageMax）
    if ( (*(uint8_t *)(pBtnConfirm + 17) == 0 || dword_79BE34 != *(uint32_t *)(pBtnConfirm + 12)) && (uint8_t)sub_453BE0(this) == 0 )  // sub_453BE0 —— 启动门判定
    {
LABEL_33:
      pBtnDiffDown = *(uint32_t *)(this + 32);  // 读字段 fld_20 = this+32（nHeight）
      if ( *(uint8_t *)(pBtnDiffDown + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnDiffDown + 12) )  // 当前动画对象指针(帧同步比对基准)
        sub_454610(*(uint32_t *)(this + 288), *(uint32_t *)(*(uint32_t *)(this + 276) + 16 * *(uint32_t *)(this + 288) + 4) - 1);  // sub_454610 —— 座位选定提交
      pBtnDiffUp = *(uint32_t *)(this + 36);  // 读字段 fld_24 = this+36（nStateWord36）
      if ( *(uint8_t *)(pBtnDiffUp + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnDiffUp + 12) )  // 当前动画对象指针(帧同步比对基准)
        sub_454610(*(uint32_t *)(this + 288), *(uint32_t *)(*(uint32_t *)(this + 276) + 16 * *(uint32_t *)(this + 288) + 4) + 1);  // sub_454610 —— 座位选定提交
      goto LABEL_39;
    }
LABEL_27:
    pMapEntry = *(uint32_t *)(this + 276);  // 读字段 fld_1142 = this+276（pMapEntry）
    if ( pMapEntry != 0 && (*(uint32_t *)(this + 280) - pMapEntry) >> 4 != 0 )  // this+280 pMapEntryVecEnd
    {
      nSelMap = *(uint32_t *)(this + 288);  // 读字段 fld_120 = this+288（pMaster288）
      if ( nSelMap == -1 || nSelMap >= sub_453C00(this + 272) )  // sub_453C00 —— 16 字节元素计数
        nSelMap = 0;  // fld_120=this+288 pMaster288
      sub_454680(*(uint32_t *)(*(uint32_t *)(this + 276) + 16 * nSelMap), *(uint32_t *)(*(uint32_t *)(this + 276) + 16 * nSelMap + 4));  // sub_454680 —— 房间选择确认
      sub_432EA0("MAP_SELECT", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    }
    goto LABEL_33;
  }
LABEL_39:
  nPhase = *(uint32_t *)(this + 232);  // 读字段 fld_E8 = this+232（bSyncSwitch）
  if ( nPhase == 1 )  // fld_E8=this+232 bSyncSwitch
  {
    *(uint32_t *)(this + 232) = 2;  // 写字段 this+232（bSyncSwitch） ← 2
  }
  else if ( nPhase == 2 && *(uint32_t *)(this + 212) == -1 )  // this+212 nCountdownState
  {
    fld_DC = (int *)sub_476B60(*(uint32_t *)(this + 220));  // sub_476B60 —— 存 选区角色数据查找
    sub_475810(fld_DC, this, *(uint32_t *)(this + 224), *(uint32_t *)(this + 228));  // this+224〔nRewardMapNo〕
    sub_4284C0(*(uint32_t *)(this + 224), *(uint32_t *)(this + 228));  // sub_4284C0 —— 场景格切换装配
    *(uint8_t *)(this + 236) = 1;  // 写字段 this+236（nSyncArgA） ← 1
    *(uint8_t *)(this + 253) = 0;  // 写字段 this+253（field_00FD） ← 0
    *(uint8_t *)(this + 254) = 0;  // 写字段 this+254（field_00FE） ← 0
    sub_698F90(this + 240, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(uint32_t *)(this + 212) = 0;  // 写字段 this+212（nField212） ← 0
  }
  if ( *(uint8_t *)(this + 148) != 0 )  // this+148〔bEnterTrigger〕
  {
    nPhase_ = *(uint32_t *)(this + 232);  // 读字段 fld_E82 = this+232（bSyncSwitch）
    if ( nPhase_ == 2 )  // fld_E82=this+232 bSyncSwitch
    {
      sub_698F90(this + 152, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      pThis_98 = sub_699000(this + 152);  // 【clock_now(clk)】
      v19 = (uint64_t)sub_4049C0(0.0, 255.0, pThis_98, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      *((uint32_t *)dword_8F8528 + 621) = v19;  // dword_8F8528 —— 对象池借出（按池号取可用对象）
      if ( sub_699000(this + 152) >= 300 )  // 【clock_now(clk)】
      {
        *(uint32_t *)(this + 232) = 3;  // 写字段 this+232（bSyncSwitch） ← 3
        v20 = *(uint32_t *)(dword_8F7A24 + 20);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        if ( *(uint32_t *)(v20 + 216) == 0 )
          *(uint32_t *)(v20 + 216) = -1;  // 写字段 v20+216（bField216） ← -1
      }
    }
    else if ( (nPhase_ == 3 || nPhase_ == 4) && nPhase_ == 4 )  // 判定 fld_E82 == 3 或 fld_E82 == 4 且 fld_E82 == 4
    {
      sub_41D300(3);  // sub_41D300 —— 模块切换 setter → 0x41CC80(onChangeModule) 转发
      *(uint8_t *)(this + 148) = 0;  // 写字段 this+148（fAdd148） ← 0
      *(uint8_t *)(this + 197) = 0;  // 写字段 this+197（field_00C5） ← 0
      *(uint8_t *)(this + 198) = 0;  // 写字段 this+198（field_00C6） ← 0
      *(uint32_t *)(this + 212) = -1;  // 写字段 this+212（nField212） ← -1
      *(uint8_t *)(this + 216) = 1;  // 写字段 this+216（bField216） ← 1
    }
  }
  LOBYTE(pThis_F0) = *(uint8_t *)(this + 236);  // this+236〔bSendGate〕
  if ( (uint8_t)pThis_F0 != 0 )
  {
    pThis_F0 = sub_699000(this + 240);  // 【clock_now(clk)】
    if ( pThis_F0 >= 1000 )
    {
      sub_423200(dword_8F7B08, 40);  // 【发送网络包API】
      LOBYTE(pThis_F0) = sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
      *(uint8_t *)(this + 236) = 0;  // 写字段 this+236（nSyncArgA） ← 0
    }
  }
  return pThis_F0;
}


// ------------------------------------------------------------
// 0x454B50 sub_454B50 —— vector 越界抛异常
// invalid vector<T> subscript 自证：构造 out_of_range 后 _CxxThrowException。
// ------------------------------------------------------------
void /*noreturn*/ sub_454B50()  // sub_454B50 —— vector 越界抛异常
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
  sub_401740(v1);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject = &std::out_of_range::`vftable';  // vftable 复位
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);  // 抛出 C++ 异常（越界/长度非法）
}



// ------------------------------------------------------------
// 0x454BC0 sub_454BC0 —— 副本界面状态复位
// +4 关闭态：+12..+304 全字段清零并释放 +276 座位表。
// ------------------------------------------------------------
void /*thiscall*/ sub_454BC0(int this)  // sub_454BC0 —— 副本界面状态复位
{
  if ( *(uint8_t *)(this + 4) == 0 )  // this+4〔宿主对象〕等 2 字段
  {
    *(uint32_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
    *(uint32_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
    *(uint32_t *)(this + 20) = 0;  // 写字段 this+20（nPage） ← 0
    *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
    *(uint32_t *)(this + 28) = 0;  // 写字段 this+28（pPanelVec） ← 0
    *(uint32_t *)(this + 32) = 0;  // 写字段 this+32（nHeight） ← 0
    *(uint32_t *)(this + 36) = 0;  // 写字段 this+36（nStateWord36） ← 0
    *(uint32_t *)(this + 68) = 0;  // 写字段 this+68（nCharCount） ← 0
    *(uint8_t *)(this + 148) = 0;  // 写字段 this+148（fAdd148） ← 0
    *(uint8_t *)(this + 180) = 0;  // 写字段 this+180（nRadius） ← 0
    *(uint8_t *)(this + 197) = 0;  // 写字段 this+197（field_00C5） ← 0
    *(uint8_t *)(this + 198) = 0;  // 写字段 this+198（field_00C6） ← 0
    *(uint32_t *)(this + 212) = -1;  // 写字段 this+212（nField212） ← -1
    *(uint8_t *)(this + 216) = 1;  // 写字段 this+216（bField216） ← 1
    *(uint32_t *)(this + 72) = 0;  // 写字段 this+72（nSnapshot72） ← 0
    *(uint32_t *)(this + 76) = 0;  // 写字段 this+76（szEmblemPath） ← 0
    *(uint32_t *)(this + 80) = 0;  // 写字段 this+80（nAuraStage） ← 0
    *(uint16_t *)(this + 140) = 0;  // 写字段 this+140（nAdd140） ← 0
    *(uint32_t *)(this + 144) = 0;  // 写字段 this+144（pFrameList144） ← 0
    *(uint32_t *)(this + 220) = -1;  // 写字段 this+220（nSnapDst220） ← -1
    *(uint32_t *)(this + 224) = 0;  // 写字段 this+224（nSnapDst224） ← 0
    *(uint32_t *)(this + 228) = 0;  // 写字段 this+228（nSnapDst228） ← 0
    *(uint32_t *)(this + 232) = 0;  // 写字段 this+232（bSyncSwitch） ← 0
    *(uint8_t *)(this + 236) = 0;  // 写字段 this+236（nSyncArgA） ← 0
    *(uint32_t *)(this + 268) = 0;  // 写字段 this+268 ← 0
    if ( *(uint32_t *)(this + 276) != 0 )  // this+276〔pMapEntry〕
      j__free(*(void **)(this + 276));  // 释放堆块
    *(uint32_t *)(this + 276) = 0;  // 写字段 this+276（pMapEntry） ← 0
    *(uint32_t *)(this + 280) = 0;  // 写字段 this+280（pMapEntryVecEnd） ← 0
    *(uint32_t *)(this + 284) = 0;  // 写字段 this+284（bBindGate284） ← 0
    *(uint32_t *)(this + 288) = -1;  // 写字段 this+288（pMaster288） ← -1
    *(uint32_t *)(this + 292) = -1;  // 写字段 this+292（nOpenMode292） ← -1
    *(uint32_t *)(this + 300) = -1;  // 写字段 this+300（pAnim300） ← -1
    *(uint32_t *)(this + 296) = 0;  // 写字段 this+296（bInitFlag296） ← 0
    *(uint32_t *)(this + 304) = 0;  // 写字段 this+304（pLayer304） ← 0
  }
}



// ------------------------------------------------------------
// 0x454CA0 sub_454CA0 —— 座位表区间插入
// 16 字节元素三路插入（602460 挪移 / 4BF320 壳 / 504650 扩容 + 453C20 填充），
// 超 0xFFFFFFF 抛 vector<T> too long。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_454CA0(int this, int pArg2, unsigned int uArg3, uint32_t *Block)  // sub_454CA0 —— 座位表区间插入
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
  v26[3] = Block[3];  // v26[3] = 取 Block[3]
  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  v26[4] = &v25;
  v26[2] = v6;
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    result = (*(uint32_t *)(this + 12) - fld_4) >> 4;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    result = 0;  // result=this+12 nSkillRec12
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_8 = 0;  // fld_8=this+8 nSkillRec8
    if ( 0xFFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 nSkillRec8
      sub_41D5A0(this);  // 【模块切换辅助（map 容器/观察者清理/资源卸载链）】
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_82 = 0;  // fld_82=this+8 nSkillRec8
    if ( result >= uArg3 + fld_82 )  // result=this+12 nSkillRec12
    {
      fld_83 = *(void **)(this + 8);  // this+32〔nHeight(推断)〕
      Blockb = fld_83;  // fld_83=this+32 nHeight
      if ( ((int)fld_83 - pArg2) >> 4 >= uArg3 )  // fld_83=this+32 nHeight
      {
        v21 = (int)fld_83 - 16 * uArg3;  // fld_83=this+32 nHeight
        *(uint32_t *)(this + 8) = sub_602460(v21, fld_83, fld_83);  // sub_602460 —— 16 字节批量拷贝
        sub_4BF320(pArg2, v21, (int)Blockb);  // sub_4BF320 —— 转发壳
        return sub_453C20(pArg2, pArg2 + 16 * uArg3, v26);  // sub_453C20 —— 16 字节元素区间填充
      }
      else
      {
        sub_602460(pArg2, fld_83, pArg2 + 16 * uArg3);  // sub_602460 —— 16 字节批量拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 4);  // this+8〔nSkillRec8(推断)〕等 2 字段
        fld_85 = *(uint32_t *)(this + 8);  // 读字段 fld_85 = this+8（nSkillRec8）
        v27 = 2;
        sub_504650(fld_85, fld_84, v26);  // fld_85=this+8 nSkillRec8
        fld_86 = 16 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;  // 写字段 this+8（nSkillRec8） ← fld_86
        return sub_453C20(pArg2, fld_86 - 16 * uArg3, v26);  // sub_453C20 —— 16 字节元素区间填充
      }
    }
    else
    {
      if ( 0xFFFFFFF - (result >> 1) >= result )  // result=this+12 nSkillRec12
        v12 = (result >> 1) + result;  // result=this+12 nSkillRec12
      else
        v12 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_87 = 0;  // fld_87=this+8 nSkillRec8
      if ( v12 < uArg3 + fld_87 )  // fld_87=this+8 nSkillRec8
      {
        if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else
          fld_88 = 0;  // fld_88=this+8 nSkillRec8
        v12 = uArg3 + fld_88;  // 计算 v12 = uArg3 + fld_88
      }
      v28 = 16 * v12;  // 计算 v28 = 16 * v12
      Blocka = (char *)operator new(16 * v12);  // 堆分配
      fld_42 = *(uint32_t *)(this + 4);  // 读字段 fld_42 = this+4（pHostObj）
      v27 = 0;
      v15 = (uint32_t *)sub_602460(fld_42, pArg2, Blocka);  // sub_602460 —— 16 字节批量拷贝
      sub_4BF340(v15, (uint32_t *)uArg3, v26);  // sub_4BF340 —— 16 字节元素填充
      sub_602460(pArg2, *(uint32_t *)(this + 8), &v15[4 * uArg3]);  // sub_602460 —— 16 字节批量拷贝
      fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_89 = 0;  // fld_89=this+8 nSkillRec8
      v18 = fld_89 + uArg3;  // 计算 v18 = fld_89 + uArg3
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        j__free(*(void **)(this + 4));  // 释放堆块
      *(uint32_t *)(this + 12) = &Blocka[v28];  // 写字段 this+12（nSkillRec12） ← &Blocka[v28]
      *(uint32_t *)(this + 8) = &Blocka[16 * v18];  // 写字段 this+8（nSkillRec8） ← &Blocka[16 * v18]
      *(uint32_t *)(this + 4) = Blocka;  // 写字段 this+4（pHostObj） ← Blocka
      return (unsigned int)Blocka;
    }
  }
  return result;  // result=this+12 nSkillRec12
}


// ------------------------------------------------------------
// 0x454F00 sub_454F00
// ------------------------------------------------------------
// ★ 巨型（~780 行）副本倒计时处理 —— MAP_COUNTDOWN 自证（4558 行附近）：
// 全员就绪轮询 → 倒计时推进 → 入场转移【推断】
char /*thiscall*/ sub_454F00(int this)  // 实现：全员就绪轮询 → 倒计时推进 → 入场转移(推断)
{
  unsigned int pObj14; // eax
  int pThis_28; // edi
  double v4; // st7
  int v5; // ebx
  int fld_10C; // ecx
  int fld_18; // ecx
  int v8; // edi
  int pObj21; // eax
  int pObj15; // eax
  int fld_1C; // ecx
  int v12; // edi
  int pObj2; // eax
  int pObj8; // eax
  int fld_6C; // edi
  int pThis_54; // ecx
  int v17; // edi
  int pObj26; // eax
  int fld_114; // eax
  int fld_118; // esi
  int fld_1142; // esi
  int pObj16; // eax
  int pObj6; // eax
  int pObj3; // eax
  int pObj27; // eax
  int pObj; // eax
  int pObj4; // eax
  int pObj20; // eax
  bool v29; // cc
  int fld_120; // eax
  int fld_1143; // edi
  int v32; // esi
  int pObj19; // eax
  int pThis_70; // ecx
  int pObj13; // eax
  int fld_90; // eax
  uint32_t *v37; // eax
  int pObj17; // eax
  uint32_t *v39; // eax
  int pObj25; // eax
  uint32_t *v41; // eax
  int pObj10; // eax
  uint32_t *v43; // eax
  int pObj9; // eax
  int fld_1202; // eax
  int pObj7; // eax
  int pObj22; // eax
  int pObj12; // eax
  int pObj11; // eax
  int pObj23; // eax
  int v51; // ecx
  int v52; // esi
  int v53; // edi
  int pObj5; // eax
  int v55; // eax
  int v56; // edx
  int pObj18; // eax
  signed int Time; // eax
  int v59; // ecx
  int pThis_282; // ecx
  int v61; // edi
  int v62; // esi
  int pObj28; // eax
  int v64; // ebx
  int pObj24; // eax
  int v66; // ecx
  uint32_t *fld_1144; // edi
  unsigned int i; // esi
  int v69; // edx
  float v71; // [esp+2ACh] [ebp-38h]
  int v72; // [esp+2B0h] [ebp-34h]
  int v73; // [esp+2B0h] [ebp-34h]
  int v74; // [esp+2B0h] [ebp-34h]
  int v75; // [esp+2B0h] [ebp-34h]
  float v76; // [esp+2B0h] [ebp-34h]
  int v77; // [esp+2C8h] [ebp-1Ch]
  int fld_88; // [esp+2C8h] [ebp-1Ch]
  int v79; // [esp+2C8h] [ebp-1Ch]
  int v80; // [esp+2CCh] [ebp-18h]
  int v81; // [esp+2D0h] [ebp-14h]
  int v82; // [esp+2D0h] [ebp-14h]
  int v83; // [esp+2D4h] [ebp-10h]
  int v84; // [esp+2D4h] [ebp-10h]
  int v85; // [esp+2D4h] [ebp-10h]
  int fld_1182; // [esp+2D4h] [ebp-10h]
  int v87; // [esp+2D8h] [ebp-Ch]
  int v88; // [esp+2D8h] [ebp-Ch]
  int v89; // [esp+2D8h] [ebp-Ch]
  int v90; // [esp+2DCh] [ebp-8h]
  int v91; // [esp+2DCh] [ebp-8h]
  int *pThis_20; // [esp+2DCh] [ebp-8h]

  LOBYTE(pObj14) = *(uint8_t *)(this + 216);  // this+216〔bField216(推断)〕
  if ( (uint8_t)pObj14 == 0 )
    return pObj14;
  sub_698F90(this + 40, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  pThis_28 = sub_699000(this + 40);  // 【clock_now(clk)】
  v81 = (uint64_t)sub_4049C0(0.0, 255.0, pThis_28, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v4 = sub_4049C0(0.0, 255.0, pThis_28 - 1100, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v5 = (uint64_t)v4;
  if ( pThis_28 >= 1100 )
    v83 = 255 - v5;  // 计算 v83 = 255 - v5
  else
    v83 = v81;
  fld_10C = *(uint32_t *)(this + 268);  // 读字段 fld_10C = this+268
  if ( fld_10C != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_10C + 128))(  // 虚调用 vt+128（fld_10C）目标坐标y上界
      fld_10C,
      0,
      0,
      dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      1065353216,
      1065353216,
      0,
      ((uint8_t)v81 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  LOBYTE(pObj14) = v83;
  if ( v83 != 0 )
  {
    pObj14 = sub_418DD0(16);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj14 != 0 )
      LOBYTE(pObj14) = (*(int (/*thiscall*/ **)(unsigned int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj14 + 128))(  // 虚调用 vt+128（pObj14）目标坐标y上界
                     pObj14,
                     0,
                     0,
                     dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                     1065353216,
                     1065353216,
                     0,
                     ((uint8_t)v83 << 24) | 0xFFFFFF,
                     1333788672,
                     1333788672);
  }
  if ( v5 == 0 )
    return pObj14;
  fld_18 = *(uint32_t *)(this + 24);  // 读字段 fld_18 = this+24（nPageMax）
  if ( *(uint8_t *)(fld_18 + 16) != 0 )  // fld_18=this+24 nPageMax
  {
    v8 = *(uint32_t *)(fld_18 + 20);  // 读字段 v8 = fld_18+20（nPage）
    v84 = *(uint32_t *)(fld_18 + 24);  // 读字段 v84 = fld_18+24（nPageMax）
    if ( (uint8_t)sub_43BCB0() != 0 )  // sub_43BCB0 —— 焦点窗口判定（三选）
    {
      sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      pObj21 = sub_418DD0(19);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj21 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj21 + 128))(  // 虚调用 vt+128（pObj21）目标坐标y上界
          pObj21,
          v8,
          v84,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
      pObj15 = sub_418DD0(18);  // sub_418DD0 —— 资源句柄 (101)
    }
    else
    {
      pObj15 = sub_418DD0(17);  // sub_418DD0 —— 资源句柄 (101)
    }
    if ( pObj15 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj15 + 128))(  // 虚调用 vt+128（pObj15）目标坐标y上界
        pObj15,
        v8,
        v84,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        ((uint8_t)v5 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
  }
  fld_1C = *(uint32_t *)(this + 28);  // 读字段 fld_1C = this+28（pPanelVec）
  if ( *(uint8_t *)(fld_1C + 16) != 0 )  // fld_1C=this+28 pPanelVec
  {
    v12 = *(uint32_t *)(fld_1C + 20);  // 读字段 v12 = fld_1C+20（nPage）
    v85 = *(uint32_t *)(fld_1C + 24);  // 读字段 v85 = fld_1C+24（nPageMax）
    if ( (uint8_t)sub_43BCB0() != 0 )  // sub_43BCB0 —— 焦点窗口判定（三选）
    {
      sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      pObj2 = sub_418DD0(22);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj2 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚调用 vt+128（pObj2）目标坐标y上界
          pObj2,
          v12,
          v85,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
      pObj8 = sub_418DD0(21);  // sub_418DD0 —— 资源句柄 (101)
    }
    else
    {
      pObj8 = sub_418DD0(20);  // sub_418DD0 —— 资源句柄 (101)
    }
    if ( pObj8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj8 + 128))(  // 虚调用 vt+128（pObj8）目标坐标y上界
        pObj8,
        v12,
        v85,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        ((uint8_t)v5 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
  }
  fld_6C = *(uint32_t *)(this + 108);  // 读字段 fld_6C = this+108（nAdd108）
  pThis_54 = this + 84;  // this+84 插值起点 X
  if ( *(uint8_t *)(this + 140) != 0 )  // this+140〔nAdd140(推断)〕
  {
    v72 = sub_699000(pThis_54);  // 【clock_now(clk)】
    sub_4049F0(640.0, 376.0, v72, fld_6C, 1);  // sub_4049F0 —— 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
  }
  else
  {
    v73 = sub_699000(pThis_54);  // 【clock_now(clk)】
    sub_4049F0(376.0, 640.0, v73, fld_6C, 0);  // sub_4049F0 —— 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
  }
  v17 = (uint64_t)v4;
  if ( v17 != 640 )
  {
    pObj26 = sub_418DD0(8);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj26 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj26 + 128))(  // 虚调用 vt+128（pObj26）目标坐标y上界
        pObj26,
        v17,
        30,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        ((uint8_t)v5 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
  }
  v77 = sub_454070(this);  // sub_454070 —— 悬停命中检测
  fld_114 = *(uint32_t *)(this + 276);  // 读字段 fld_114 = this+276（pMapEntry）
  if ( fld_114 != 0 )  // fld_114=this+276 pMapEntry
    fld_118 = (*(uint32_t *)(this + 280) - fld_114) >> 4;  // this+280〔pMapEntryVecEnd〕
  else
    fld_118 = 0;  // fld_118=this+280 pMapEntryVecEnd
  fld_1182 = fld_118;  // fld_118=this+280 pMapEntryVecEnd
  v87 = 0;
  if ( fld_118 > 0 )  // fld_118=this+280 pMapEntryVecEnd
  {
    v90 = 0;
    do
    {
      if ( v87 != *(uint32_t *)(this + 288) )  // this+288〔pMaster288(推断)〕
      {
        fld_1142 = sub_476B60(*(uint32_t *)(*(uint32_t *)(this + 276) + v90));  // sub_476B60 —— 存 选区角色数据查找
        if ( *(uint32_t *)(*(uint32_t *)(this + 276) + v90 + 12) == -1 )  // this+276〔pMapEntry〕
        {
          pObj16 = sub_418DD0(4);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj16 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj16 + 128))(  // 虚调用 vt+128（pObj16）目标坐标y上界
              pObj16,
              0,
              0,
              dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
              1065353216,
              1065353216,
              0,
              ((uint8_t)(2 * v5 / 3) << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          if ( *(uint8_t *)(fld_1142 + 464) == 1 )
          {
            pObj6 = sub_418DD0(11);  // sub_418DD0 —— 资源句柄 (101)
            if ( pObj6 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj6 + 128))(  // 虚调用 vt+128（pObj6）目标坐标y上界
                pObj6,
                *(uint32_t *)(fld_1142 + 72) - 7,
                *(uint32_t *)(fld_1142 + 76) - 16,
                dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                1065353216,
                1065353216,
                0,
                ((uint8_t)(2 * v5 / 3) << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
          }
          else
          {
            pObj3 = sub_418DD0(7);  // sub_418DD0 —— 资源句柄 (101)
            if ( pObj3 != 0 )
              (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚调用 vt+128（pObj3）目标坐标y上界
                pObj3,
                *(uint32_t *)(fld_1142 + 72),
                *(uint32_t *)(fld_1142 + 76) - 9,
                dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                1065353216,
                1065353216,
                0,
                ((uint8_t)(2 * v5 / 3) << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
          }
        }
        else
        {
          if ( v77 == v87 )
          {
            sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
            pObj27 = sub_418DD0(3);  // sub_418DD0 —— 资源句柄 (101)
            if ( pObj27 != 0 )
              (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj27 + 128))(  // 虚调用 vt+128（pObj27）目标坐标y上界
                pObj27,
                0,
                0,
                dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                1065353216,
                1065353216,
                0,
                ((uint8_t)v5 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
            sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
          }
          pObj = sub_418DD0(2);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
              pObj,
              0,
              0,
              dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
              1065353216,
              1065353216,
              0,
              ((uint8_t)v5 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          if ( *(uint8_t *)(fld_1142 + 464) == 1 )
          {
            pObj4 = sub_418DD0(11);  // sub_418DD0 —— 资源句柄 (101)
            if ( pObj4 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(  // 虚调用 vt+128（pObj4）目标坐标y上界
                pObj4,
                *(uint32_t *)(fld_1142 + 72) - 7,
                *(uint32_t *)(fld_1142 + 76) - 16,
                dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                1065353216,
                1065353216,
                0,
                ((uint8_t)v5 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
          }
          else
          {
            pObj20 = sub_418DD0(6);  // sub_418DD0 —— 资源句柄 (101)
            if ( pObj20 != 0 )
              (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj20 + 128))(  // 虚调用 vt+128（pObj20）目标坐标y上界
                pObj20,
                *(uint32_t *)(fld_1142 + 72),
                *(uint32_t *)(fld_1142 + 76) - 9,
                dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                1065353216,
                1065353216,
                0,
                ((uint8_t)v5 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
          }
        }
      }
      v29 = ++v87 < fld_1182;
      v90 += 16;
    }
    while ( v29 );
  }
  fld_120 = *(uint32_t *)(this + 288);  // 读字段 fld_120 = this+288（pMaster288）
  if ( fld_120 != -1 )  // fld_120=this+288 pMaster288
  {
    fld_1143 = sub_476B60(*(uint32_t *)(*(uint32_t *)(this + 276) + 16 * fld_120));  // sub_476B60 —— 存 选区角色数据查找
    v32 = *(uint32_t *)(fld_1143 + 84);  // 读字段 v32 = fld_1143+84（pFxObjA）
    v88 = *(uint32_t *)(fld_1143 + 80);  // 读字段 v88 = fld_1143+80（nAuraStage）
    sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    pObj19 = sub_418DD0(1);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj19 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj19 + 128))(  // 虚调用 vt+128（pObj19）目标坐标y上界
        pObj19,
        0,
        0,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        ((uint8_t)v5 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
    fld_88 = *(uint32_t *)(this + 136);  // 读字段 fld_88 = this+136（nCtx136）
    pThis_70 = this + 112;  // this+112〔pHostComp112〕
    if ( *(uint8_t *)(this + 141) != 0 )  // this+141〔bFadeFlagA〕
    {
      v74 = sub_699000(pThis_70);  // 【clock_now(clk)】
      sub_4049F0(-12.0, -39.0, v74, fld_88, 1);  // sub_4049F0 —— 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
    }
    else
    {
      v75 = sub_699000(pThis_70);  // 【clock_now(clk)】
      sub_4049F0(-39.0, -12.0, v75, fld_88, 0);  // sub_4049F0 —— 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
    }
    v91 = (uint64_t)v4;
    if ( v91 == -12 )
    {
      pObj11 = sub_418DD0(0);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj11 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj11 + 128))(  // 虚调用 vt+128（pObj11）目标坐标y上界
          pObj11,
          0,
          0,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
    }
    else
    {
      pObj13 = sub_418DD0(5);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj13 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj13 + 128))(  // 虚调用 vt+128（pObj13）目标坐标y上界
          pObj13,
          v88,
          v32 + v91,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      fld_90 = sub_418DD0(*(uint32_t *)(this + 144));  // sub_418DD0 —— 资源句柄 (101)
      if ( fld_90 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_90 + 128))(  // 虚调用 vt+128（fld_90）目标坐标y上界
          fld_90,
          v88,
          v32 + v91,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v37 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      v37[13] = 0;
      v37[14] = 640;
      v37[15] = v91 + v32 + 12;
      pObj17 = sub_418DD0(0);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj17 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj17 + 128))(  // 虚调用 vt+128（pObj17）目标坐标y上界
          pObj17,
          0,
          0,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v39 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      v39[13] = v32;
      v39[14] = 640;
      v39[15] = 480;
      pObj25 = sub_418DD0(0);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj25 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj25 + 128))(  // 虚调用 vt+128（pObj25）目标坐标y上界
          pObj25,
          0,
          0,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v41 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      *(uint32_t *)(dword_79C0B0 + 52) = v91 + v32 + 12;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      v41[12] = 0;
      v41[14] = v88;
      v41[15] = v32;
      pObj10 = sub_418DD0(0);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj10 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj10 + 128))(  // 虚调用 vt+128（pObj10）目标坐标y上界
          pObj10,
          0,
          0,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v43 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      *(uint32_t *)(dword_79C0B0 + 48) = v88 + 168;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      v43[13] = v91 + v32 + 12;
      v43[14] = 640;
      v43[15] = v32;
      pObj9 = sub_418DD0(0);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj9 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj9 + 128))(  // 虚调用 vt+128（pObj9）目标坐标y上界
          pObj9,
          0,
          0,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_488670(dword_79C0B0);  // sub_488670 —— 视口重置 640x480
    }
    fld_1202 = 16 * *(uint32_t *)(this + 288) + *(uint32_t *)(this + 276);
    if ( *(uint32_t *)(fld_1202 + 4) != 0 )
    {
      pObj7 = sub_418DD0(*(uint32_t *)(fld_1202 + 4) + 4);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj7 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj7 + 128))(  // 虚调用 vt+128（pObj7）目标坐标y上界
          pObj7,
          v88,
          v32,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
    }
    if ( *(uint8_t *)(fld_1143 + 464) == 1 )
    {
      pObj22 = sub_418DD0(9);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj22 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj22 + 128))(  // 虚调用 vt+128（pObj22）目标坐标y上界
          pObj22,
          v88 - 9,
          v91 + v32 - 12,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      pObj12 = sub_418DD0(10);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj12 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj12 + 128))(  // 虚调用 vt+128（pObj12）目标坐标y上界
          pObj12,
          v88 - 5,
          v32 + 59,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
    }
    else
    {
      pObj23 = sub_418DD0(0);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj23 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj23 + 128))(  // 虚调用 vt+128（pObj23）目标坐标y上界
          pObj23,
          v88,
          v32 + v91,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
    }
    v82 = 0;
    v89 = 11;
    pThis_20 = (int *)(this + 32);  // this+32〔nHeight(推断)〕等 2 字段
    do
    {
      v51 = *pThis_20;  // pThis_20=this+32 nHeight
      if ( *(uint8_t *)(*pThis_20 + 16) != 0 )  // pThis_20=this+32 nHeight
      {
        v52 = *(uint32_t *)(v51 + 20);  // 读字段 v52 = v51+20（nPage）
        v53 = *(uint32_t *)(v51 + 24);  // 读字段 v53 = v51+24（nPageMax）
        if ( (uint8_t)sub_69A4D0(v51) != 0 )
        {
          pObj5 = sub_418DD0(v89 + 1);  // sub_418DD0 —— 资源句柄 (101)
        }
        else
        {
          v55 = *pThis_20;  // pThis_20=this+32 nHeight
          if ( *(uint8_t *)(*pThis_20 + 17) != 0  // pThis_20=this+32 nHeight
            && (dword_79BE3C == *(uint32_t *)(v55 + 12)  // 动画对象指针(帧同步比对基准 C)
             || dword_79BE34 == *(uint32_t *)(v55 + 12)  // 当前动画对象指针(帧同步比对基准)
             || dword_79BE38 == *(uint32_t *)(v55 + 12)) )  // 动画对象指针(帧同步比对基准 B)
          {
            v56 = v89;
          }
          else
          {
            if ( *(uint8_t *)(v55 + 17) != 0 )
            {
              pObj18 = sub_418DD0(v89 - 1);  // sub_418DD0 —— 资源句柄 (101)
              if ( pObj18 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj18 + 128))(  // 虚调用 vt+128（pObj18）目标坐标y上界
                  pObj18,
                  v52,
                  v53,
                  dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                  1065353216,
                  1065353216,
                  0,
                  ((uint8_t)v5 << 24) | 0xFFFFFF,
                  1333788672,
                  1333788672);
              Time = timeGetTime();  // Time = 调 timeGetTime
              v76 = (float)v5;
              v79 = (uint64_t)sub_4049C0(0.0, v76, abs32(300 - Time % 600), 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
              pObj5 = sub_418DD0(v89);  // sub_418DD0 —— 资源句柄 (101)
              if ( pObj5 == 0 )
                goto LABEL_110;
              v59 = (uint8_t)v79;
              goto LABEL_109;
            }
            v56 = v82 + 23;  // 计算 v56 = v82 + 23
          }
          pObj5 = sub_418DD0(v56);  // sub_418DD0 —— 资源句柄 (101)
        }
        if ( pObj5 != 0 )
        {
          v59 = (uint8_t)v5;
LABEL_109:
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(  // 虚调用 vt+128（pObj5）目标坐标y上界
            pObj5,
            v52,
            v53,
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            1065353216,
            1065353216,
            0,
            (v59 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        }
      }
LABEL_110:
      v29 = v89 + 3 < 17;
      ++v82;  // 计数自增 v82
      ++pThis_20;  // 计数自增 pThis_20
      v89 += 3;
    }
    while ( v29 );
  }
  if ( *(uint8_t *)(this + 180) == 0 )  // this+180〔nRadius(推断)〕
  {
    if ( 20300 - sub_699000(this + 40) <= 0 )  // 【clock_now(clk)】
    {
      pThis_282 = 0;
      goto LABEL_114;
    }
    pThis_282 = 20300 - sub_699000(this + 40);  // 【clock_now(clk)】
    if ( pThis_282 < 10000 )
    {
LABEL_114:
      v61 = pThis_282 % 1000;
      v62 = pThis_282 / 1000;  // 计算 v62 = pThis_282 / 1000
      if ( *(uint32_t *)(this + 296) != pThis_282 / 1000 )  // this+296〔bInitFlag296(推断)〕
      {
        *(uint32_t *)(this + 296) = v62;  // 写字段 this+296（bInitFlag296） ← v62
        sub_432EA0("MAP_COUNTDOWN", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
      }
      pObj28 = sub_418DD0(v62);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj28 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj28 + 128))(  // 虚调用 vt+128（pObj28）目标坐标y上界
          pObj28,
          0,
          0,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v71 = (float)v5;
      v64 = (uint64_t)sub_4049C0(v71, 0.0, 999 - v61, 250);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      if ( v64 != 0 )
      {
        sub_491530(5, -1);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
        pObj24 = sub_418DD0(v62);  // sub_418DD0 —— 资源句柄 (101)
        if ( pObj24 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj24 + 128))(  // 虚调用 vt+128（pObj24）目标坐标y上界
            pObj24,
            0,
            0,
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            1065353216,
            1065353216,
            0,
            ((uint8_t)v64 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        sub_491630(5);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
      }
    }
  }
  pObj14 = sub_568A70((uint8_t)byte_99FCD0, (uint8_t)byte_99FCD1);  // sub_568A70 —— 频道条目组装（568940/568800）
  if ( pObj14 != 0 )
  {
    v66 = *(uint32_t *)(pObj14 + 88);  // 读字段 v66 = pObj14+88（pFxObjB）
    if ( v66 != 0 )
    {
      LOBYTE(pObj14) = fld_1182;
      v80 = 0;
      if ( fld_1182 > 0 )
      {
        fld_1144 = *(uint32_t **)(this + 276);  // this+276〔pMapEntry〕
        do
        {
          for ( i = 0; ; ++i )
          {
            v69 = *(uint32_t *)(v66 + 4);  // 读字段 v69 = v66+4（pHostObj）
            if ( v69 == 0 || i >= (*(uint32_t *)(v66 + 8) - v69) >> 2 )
              break;
            pObj14 = (*(uint32_t *)(v66 + 8) - v69) >> 2;
            if ( pObj14 <= i )
              sub_454B50();  // sub_454B50 —— vector 越界抛异常
            if ( *fld_1144 == *(uint32_t *)(v69 + 4 * i) )  // fld_1144=this+276 pMapEntry
              goto LABEL_134;
          }
          LOBYTE(pObj14) = v80 + 1;
          fld_1144 += 4;  // fld_1144=this+276 pMapEntry
          ++v80;  // 计数自增 v80
        }
        while ( v80 < fld_1182 );  // 循环直到 v80 < fld_1182
      }
    }
  }
LABEL_134:
  if ( *(uint32_t *)(this + 232) == 3 )  // this+232〔bSyncFlag〕
  {
    LOBYTE(pObj14) = sub_453C60(this);  // sub_453C60 —— 淡变状态机推进
    if ( (uint8_t)pObj14 == 1 )
    {
      LOBYTE(pObj14) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B0 + 28))(dword_79C0B0, 0);  // 虚调用 vt+28（dword_79C0B0 虚表槽）
      *(uint8_t *)(this + 216) = 0;  // 写字段 this+216（bField216） ← 0
      *(uint32_t *)(this + 232) = 4;  // 写字段 this+232（bSyncSwitch） ← 4
    }
  }
  return pObj14;
}


// ============================================================
// 【分区 5】地图创建与队伍分组登记（0x455E20-0x456690）
// 队伍分组登记 0x455EB0（分发器 case 2 循环体落点）；
// 世界地图创建 0x456210（"CRITICAL ERROR : WORLD MAP LOAD FAIL %d" 自证）；
// 座位查询族 0x456390/0x456420/0x456480（docs/13 §3 进图 2 座位分配）。
// ============================================================
// ------------------------------------------------------------
// 0x455E20 sub_455E20 —— 倒计时转发
// 模块类型 +3 与 nArg2 吻合 → 转发巨型 ·0x454F00【推断：类型过滤】。
// ------------------------------------------------------------
char /*thiscall*/ sub_455E20(uint32_t *this, int nArg2)  // sub_455E20 —— 倒计时转发
{
  char result; // al

  result = nArg2;
  if ( nArg2 == *(this + 3) )  // this+12〔nSkillRec12(推断)〕
    return sub_454F00((int)(this - 2));  // 返回 全员就绪轮询 → 倒计时推进 → 入场转移(推断)
  return result;
}



// ------------------------------------------------------------
// 0x455E40 sub_455E40 —— 表尾追加
// 16 字节元素 ×1 追加（+4/+8/+12 区间）：满则 454CA0 扩容，否则 4BF340 填充 + 尾针 +16（调用方用于 +272 表）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_455E40(int this, uint32_t *Block)  // sub_455E40 —— 表尾追加
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  int fld_82; // edi
  unsigned int result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) >> 4 )  // this+12 物品类型号
    return sub_454CA0(this, *(char **)(this + 8), 1u, Block);  // sub_454CA0 —— 座位表区间插入
  fld_82 = *(uint32_t *)(this + 8);  // 读字段 fld_82 = this+8（nSkillRec8）
  result = sub_4BF340(fld_82, 1, Block);  // sub_4BF340 —— 16 字节元素填充
  *(uint32_t *)(this + 8) = fld_82 + 16;  // 写字段 this+8（nSkillRec8） ← fld_82 + 16
  return result;
}



// ------------------------------------------------------------
// 0x455EB0 sub_455EB0
// ------------------------------------------------------------
// 队伍分组登记 —— 分发器 case 2 循环体落点：
// sub_476B60(角色) +92 队伍规模 → 与本地座位(sub_456480→+16)规模比较定分组级
// （0/1/2，-1=不可比）→ 本地座位补 sub_472F90 → Block{id,0,数据,等级} →
// sub_455E40 入 +272 表
unsigned int /*thiscall*/ sub_455EB0(void *this, int nArg2)  // 实现：sub_455E40 入 +272 表
{
  int v2; // esi
  int v3; // edi
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // esi
  int dword_8F850C2; // edi
  int v10; // edi
  uint32_t Block[4]; // [esp+Ch] [ebp-14h] BYREF
  void *pThis; // [esp+1Ch] [ebp-4h]

  pThis = this;
  v2 = *(uint32_t *)(sub_476B60(nArg2) + 92);  // sub_476B60 —— 存 选区角色数据查找
  if ( v2 <= 1
    || ((v3 = dword_8F850C, sub_456480(dword_8F850C) != -1)  // sub_456480 —— 存 座位号
      ? (v4 = *(uint32_t *)(v3 + 4 * sub_456480(v3) + 16))  // sub_456480 —— 存 座位号
      : (v4 = 0),
        sub_41A5E0(v4 + 53) >= v2) )  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
    v7 = sub_41A5E0(v6 + 53) - v2;  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    if ( v7 > 2 || v2 <= 2 )
      v5 = v7 <= 4;
    else
      v5 = 2;
  }
  else
  {
    v5 = -1;
  }
  v8 = 0;
  dword_8F850C2 = dword_8F850C;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
  if ( sub_456480(dword_8F850C) == -1 )  // sub_456480 —— 存 座位号
    v10 = 0;
  else
    v10 = *(uint32_t *)(dword_8F850C2 + 4 * sub_456480(dword_8F850C2) + 16);  // sub_456480 —— 存 座位号
  if ( v10 == sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )  // sub_429830 —— 结果 = 表按键查找（uint16）
    v8 = sub_472F90(nArg2);  // 调 命中返回节点 dword#4（+16），未命中返回 0
  Block[0] = nArg2;
  Block[1] = 0;
  Block[2] = v8;
  Block[3] = v5;
  return sub_455E40((int)pThis + 272, Block);  // sub_455E40 —— 表尾追加
}



// ------------------------------------------------------------
// 0x455FC0 sub_455FC0 —— 候选名单筛选提交
// pArg4 的 +68/+72 pair 表过滤（47C080/41C290 与 dword_8F8540+52 比对），命中 +300/+304 者优先，
// 结果经主管理器 vmt+8(2,2) + vmt+32 队列（含 430C80 追加）提交。
// ------------------------------------------------------------
void /*userpurge*/ sub_455FC0(int nArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int pArg4)  // sub_455FC0 —— 候选名单筛选提交
{
  int dword_8F850C2; // esi
  int v5; // esi
  int *v6; // esi
  int *v7; // ebx
  int *v8; // edi
  bool v9; // zf
  unsigned int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int *i; // edi
  char v18[4]; // [esp+4h] [ebp-28h] BYREF
  int *v19; // [esp+8h] [ebp-24h]
  int *v20; // [esp+Ch] [ebp-20h]
  int v21; // [esp+10h] [ebp-1Ch]
  int nArg12; // [esp+14h] [ebp-18h]
  int v23; // [esp+18h] [ebp-14h] BYREF
  uint32_t v24[4]; // [esp+1Ch] [ebp-10h] BYREF
  int v25; // [esp+34h] [ebp+8h]

  nArg12 = nArg1;
  dword_8F850C2 = dword_8F850C;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
  if ( sub_456480(dword_8F850C) == -1 )  // sub_456480 —— 存 座位号
    v5 = 0;
  else
    v5 = *(uint32_t *)(dword_8F850C2 + 4 * sub_456480(dword_8F850C2) + 16);  // sub_456480 —— 存 座位号
  if ( v5 == sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )  // sub_429830 —— 结果 = 表按键查找（uint16）
  {
    v6 = nullptr;
    if ( pArg4 != 0 )
    {
      v7 = nullptr;
      v19 = nullptr;
      v20 = nullptr;
      v21 = 0;
      v8 = *(int **)(pArg4 + 68);  // pArg4+68〔nCharCount(推断)〕
      v9 = v8 == *(int **)(pArg4 + 72);  // pArg4+72〔nSnapshot72(推断)〕
      v24[3] = 0;
      if ( !v9 )
      {
        do
        {
          v24[0] = v8[1];  // v24[0] = 取 v8[1]
          if ( v24[0] == -1
            || (uint8_t)sub_47C080(v24[0]) != 0  // 调 在 20 字节条目表中线性查找首 DWORD==nArg2 的条目：命中返回 1（纯存在性查询，无发包）
            || *(uint32_t *)sub_472E30(&v23, v24) != *(uint32_t *)(dword_8F8540 + 52)  // dword_8F8540 —— 逐条处理型别 fld[68]==0 的条件条目：为已注册
            || (uint8_t)sub_41C290(dword_8F7A24) != 0 )  // sub_41C290 —— this+248 子对象完整性校验
          {
            if ( v6 != nullptr && v7 - v6 < (unsigned int)((v21 - (int)v6) >> 2) )
            {
              *v7++ = *v8;
              v20 = v7;
            }
            else
            {
              sub_430C80((int)v18, (int)v7, 1u, v8);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
              v7 = v20;
              v6 = v19;
            }
          }
          v8 += 2;
        }
        while ( v8 != *(int **)(pArg4 + 72) );  // pArg4+72〔nSnapshot72(推断)〕
      }
      v10 = 0;
      v25 = -1;
      v24[0] = 0;
      while ( v6 != nullptr && v10 < v7 - v6 )  // 循环直到 v6 != nullptr 且 v10 < v7
      {
        v11 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
        v23 = sub_41A5E0(v11 + 53);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        v12 = sub_476B60(v6[v10]);  // sub_476B60 —— 存 选区角色数据查找
        if ( v23 >= *(uint32_t *)(v12 + 92) )
        {
          if ( v6[v10] == *(uint32_t *)(nArg12 + 300) )  // nArg12+300〔pAnim300(推断)〕
          {
            v25 = v10;
            v13 = *(uint32_t *)(nArg12 + 304);  // 读字段 v13 = nArg12+304（pLayer304）
            if ( sub_472F90(*(uint32_t *)(nArg12 + 300)) >= v13 )  // nArg12+300〔pAnim300(推断)〕
              v24[0] = v13;
            break;
          }
          if ( v25 == -1 )
            v25 = v10;
        }
        ++v10;  // 计数自增 v10
      }
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 2, 2, nArg3, nArg2);  // 虚调用 vt+8（dword_8F8520 虚表槽）
      if ( v6 != nullptr )
        v14 = v7 - v6;  // 计算 v14 = v7 - v6
      else
        v14 = 0;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v14);  // 虚调用 vt+32（dword_8F8520 虚表槽）
      for ( i = v6; i != v7; ++i )  // 遍历计次循环（i != v7）
        (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 36))(*(uint16_t *)i);  // 虚调用 vt+36（dword_8F8520 虚表槽）
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v25);  // 虚调用 vt+32（dword_8F8520 虚表槽）
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v24[0]);  // 虚调用 vt+32（dword_8F8520 虚表槽）
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 虚调用 vt+60（dword_8F8520）对象销毁/释放
      if ( v6 != nullptr )
        j__free(v6);  // 释放堆块
    }
  }
}



// ------------------------------------------------------------
// 0x456210 sub_456210
// ------------------------------------------------------------
// 世界地图创建 —— "CRITICAL ERROR : WORLD MAP LOAD FAIL %d" 自证：
// sub_4CE8A0 取地图数据 → 图像名 → dword_8F84B8 vt+60 载入 → sub_418DD0 建层
// → sub_455FC0/sub_4542A0 构建节点 → +6/+7 按钮激活 → 2×300ms 定时器（+140 位表）
char /*thiscall*/ sub_456210(uint32_t *this, int ArgList)  // 函数 sub_456210：（地图创建）/ CNRoomListModule__vmt8=0x45B4A0（房间列表侧）
{
  uint32_t *v3; // eax
  uint32_t *v4; // edi
  char result; // al
  int v6; // ebx
  int v7; // edi
  int pThis_15; // ebx
  int v9; // [esp-4h] [ebp-10h]

  v3 = (uint32_t *)sub_4CE8A0(ArgList);  // sub_4CE8A0 —— 调用 sub_4CE8A0
  v4 = v3;
  if ( v3 == nullptr )
    return off_77F3FC("CRITICAL ERROR : WORLD MAP LOAD FAIL %d", ArgList);  // off_77F3FC —— 日志打印（printf 风格）
  v6 = (int)(v3 + 8);
  if ( sub_40BF00((std::_String_base *)(v3 + 8), 0, v3[13], szPassword, 0) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    if ( v4[14] < 0x10u )
      v6 = (int)(v4 + 9);
    else
      v6 = v4[9];
    v9 = v4[15];
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v6);  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
    *(this + 67) = sub_418DD0(v9);  // sub_418DD0 —— 资源句柄 (101)
  }
  else
  {
    *(this + 67) = 0;  // 写字段 this+67（nPeriodMs） ← 0
  }
  sub_455FC0((int)this, v6, (int)v4, (int)v4);  // sub_455FC0 —— 候选名单筛选提交
  sub_4542A0(this);  // sub_4542A0 —— 按钮可见态刷新
  *(uint8_t *)(*(this + 6) + 17) = 1;  // this+24〔nPageMax(推断)〕
  *(uint8_t *)(*(this + 7) + 17) = 1;  // this+28〔pPanelVec(推断)〕
  v7 = 0;
  pThis_15 = (int)(this + 21);  // this+21〔bArmorState〕
  do
  {
    *((uint8_t *)this + v7 + 140) = 0;
    result = sub_698F90(pThis_15, 300, 300);  // 【clock_set_countdown(clk, duration=a2, star…】
    ++v7;  // 计数自增 v7
    pThis_15 += 28;  // pThis_15=this+21 bArmorState
  }
  while ( v7 < 2 );  // 循环直到 v7 < 2
  return result;
}



// ------------------------------------------------------------
// 0x4562E0 sub_4562E0 —— 槽表清空
// +4..+8 五字段归零。
// ------------------------------------------------------------
int /*thiscall*/ sub_4562E0(uint32_t *this)  // sub_4562E0 —— 槽表清空
{
  *(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  *(this + 5) = 0;  // 写字段 this+5 ← 0
  *(this + 6) = 0;  // 写字段 this+6 ← 0
  *(this + 7) = 0;  // 写字段 this+7（uPathTerm） ← 0
  *(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x456300 sub_456300 —— 槽位绑定
// 旧对象 +188 清 0、新对象置 1，写入 +4+4n。
// ------------------------------------------------------------
int /*thiscall*/ sub_456300(uint32_t *this, int pArg2, int pArg3)  // sub_456300 —— 槽位绑定
{
  int result; // eax

  result = *(this + pArg2 + 4);
  if ( result != pArg3 )
  {
    if ( result != 0 )
      *(uint8_t *)(result + 188) = 0;  // 写字段 result+188（nStatusIdx） ← 0
    if ( pArg3 != 0 )
      *(uint8_t *)(pArg3 + 188) = 1;  // 写字段 pArg3+188（nStatusIdx） ← 1
    *(this + pArg2 + 4) = pArg3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x456340 sub_456340 —— 槽位绑定（按 id 版）
// 429830 查表（0xFFFF → 0）；其余同 ·0x456300。
// ------------------------------------------------------------
int /*thiscall*/ sub_456340(uint32_t *this, int pArg2, int nArg3)  // sub_456340 —— 槽位绑定（按 id 版）
{
  int result; // eax
  int v5; // ecx

  if ( (uint16_t)nArg3 == 0xFFFF )
    result = 0;
  else
    result = sub_429830((uint32_t *)dword_8F8500, nArg3);  // sub_429830 —— 结果 = 表按键查找（uint16）
  v5 = *(this + pArg2 + 4);
  if ( v5 != result )
  {
    if ( v5 != 0 )
      *(uint8_t *)(v5 + 188) = 0;  // 写字段 v5+188（nStatusIdx） ← 0
    if ( result != 0 )
      *(uint8_t *)(result + 188) = 1;  // 写字段 result+188（nStatusIdx） ← 1
    *(this + pArg2 + 4) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x456390 sub_456390
// ------------------------------------------------------------
// 座位号查询（本地玩家 → 座位 index；触发条件评估器 case 5 所用）
int /*thiscall*/ sub_456390(char *this, char pszArg2)  // sub_456390 —— 存 座位号查询
{
  int v2; // ebx
  char *pThis_10; // esi
  int i; // edi
  int pObj; // ecx
  int v6; // eax
  int pObj2; // ecx

  v2 = 0;
  pThis_10 = this + 16;  // this+16 频道型选中索引
  for ( i = 4; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    if ( *(uint32_t *)pThis_10 != 0  // pThis_10=this+16 频道型选中索引
      && (pszArg2 == 0
       || (pObj = *(uint32_t *)(*(uint32_t *)pThis_10 + 196)) != 0  // 虚调用 vt+196（pThis_10）物件非空判定
       && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1196))(pObj) == 0) )  // 虚调用 vt+1196（pObj 虚表槽）
    {
      ++v2;  // 计数自增 v2
    }
    pThis_10 += 4;  // pThis_10=this+16 频道型选中索引
  }
  if ( v2 != 0 )
    return v2;
  if ( pszArg2 != 0
    && ((v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804)) == 0  // sub_429830 —— 结果 = 表按键查找（uint16）
     || (pObj2 = *(uint32_t *)(v6 + 196)) == 0
     || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 1196))(pObj2) != 0) )  // 虚调用 vt+1196（pObj2 虚表槽）
  {
    return v2;
  }
  else
  {
    return 1;  // 返回 1(成功)
  }
}



// ------------------------------------------------------------
// 0x456420 sub_456420
// ------------------------------------------------------------
// 座位查找（docs/13 §3：进 2 = MAP_APPEAR + 座位 sub_456420）：
// 本地角色在 +4 起的 4 槽中定位 → 0..3，未找到 -1
int /*thiscall*/ sub_456420(uint32_t *this)  // sub_456420 —— 存 座位查找
{
  int v2; // edx
  int result; // eax
  uint32_t *i; // ecx

  v2 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
  if ( v2 == 0 )
    return -1;
  result = 0;
  for ( i = this + 4; *i != v2; ++i )  // this+4 宿主对象
  {
    if ( ++result >= 4 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x456460 sub_456460 —— 本地座位号设置
// 写 +8；dword_8F7A24+12 == 2 时联动 4542A0 按钮刷新。
// ------------------------------------------------------------
char /*thiscall*/ sub_456460(uint32_t *this, int nArg2)  // sub_456460 —— 本地座位号设置 写 +8；dword_8F7A24+12 == 2 时联动 4542A0 按钮刷新。
{
  char result; // al

  *(this + 8) = nArg2;  // 写字段 this+8（nSkillRec8） ← nArg2
  result = dword_8F7A24;  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 2 )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    return sub_4542A0(*(uint32_t **)(dword_8F7A24 + 24));  // sub_4542A0 —— 按钮可见态刷新
  return result;
}



// ------------------------------------------------------------
// 0x456480 sub_456480
// ------------------------------------------------------------
// 座位号（PVP/WARROOM 场景恒 -1；其余取 +8）
int /*thiscall*/ sub_456480(uint32_t *this)  // sub_456480 —— 存 座位号
{
  int v1; // eax

  v1 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  if ( v1 == 4 || v1 == 6 )
    return -1;
  else
    return *(this + 8);  // 返回字段 this+32（nHeight）
}



// ------------------------------------------------------------
// 0x4564A0 sub_4564A0 —— 组队邀请发送
// 门检 432..439 文案（目标存在/非自身/未忙/队伍饱和 56A720）；发包 op 10 = id(u16) + 0(u8) +
// 角色句柄(vmt+44 u32)【推断：组队邀请】。
// ------------------------------------------------------------
char /*cdecl*/ sub_4564A0(int nArg1)  // sub_4564A0 —— 组队邀请发送
{
  int v1; // esi
  uint32_t *v2; // esi
  char *v3; // eax
  int v5; // esi
  int v6; // eax
  int v7; // edi
  uint32_t *v8; // esi
  char *v9; // eax
  uint32_t *v10; // edi
  int pObj; // ecx
  int dword_8F7B082; // edi
  uint32_t *v13; // esi
  char *v14; // eax
  int v15; // [esp-14h] [ebp-24h]
  int v16; // [esp-10h] [ebp-20h]
  int nArg12; // [esp+8h] [ebp-8h] BYREF
  uint8_t v18[4]; // [esp+Ch] [ebp-4h] BYREF

  v1 = sub_429830((uint32_t *)dword_8F8500, nArg1);  // sub_429830 —— 结果 = 表按键查找（uint16）
  if ( v1 == 0 )
  {
    v16 = 432;
LABEL_7:
    v2 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    v3 = sub_422E70(v16);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    goto LABEL_8;
  }
  if ( v1 == sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )  // sub_429830 —— 结果 = 表按键查找（uint16）
  {
    v2 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    v3 = sub_422E70(433);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
LABEL_8:
    sub_43BEE0(v2, (int)v3, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
    return 0;
  }
  if ( *(uint32_t *)(v1 + 68) != 0 )
  {
    v16 = 434;
    goto LABEL_7;
  }
  v5 = *(uint32_t *)(v1 + 184);  // 读字段 v5 = v1+184（bSingleTarget）
  v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
  v7 = *(uint32_t *)(v6 + 184);  // 读字段 v7 = v6+184（bSingleTarget）
  if ( v5 != 0 )
  {
    if ( v7 != 0 )
    {
      v15 = 435;
LABEL_12:
      v8 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
      v9 = sub_422E70(v15);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
      sub_43BEE0(v8, (int)v9, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
      return 0;
    }
    if ( *(uint32_t *)(v5 + 60) - sub_56A720(v5) <= 0 )  // sub_56A720 —— 组队列表联动（55 行）
    {
      v15 = 436;
      goto LABEL_12;
    }
  }
  else if ( v7 != 0 && *(uint32_t *)(v7 + 60) - sub_56A720(*(uint32_t *)(v6 + 184)) <= 0 )  // sub_56A720 —— 组队列表联动（55 行）
  {
    v15 = 437;
    goto LABEL_12;
  }
  v10 = sub_432F00(0);  // sub_432F00 —— 按类型取全局列表对象
  sub_423200(dword_8F7B08, 10);  // 【发送网络包API】
  nArg12 = nArg1;
  sub_423290(dword_8F7B08, (int)&nArg12, 2);  // sub_423290 —— 写 4B 长度
  v18[0] = 0;
  sub_423290(dword_8F7B08, (int)v18, 1);  // sub_423290 —— 写 4B 长度
  pObj = *(uint32_t *)(v10[3] + 4);
  dword_8F7B082 = dword_8F7B08;  // dword_8F7B08 —— 【发送网络包API】
  nArg12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj);  // 虚调用 vt+44（pObj 虚表槽）
  sub_423290(dword_8F7B082, (int)&nArg12, 4);  // sub_423290 —— 写 4B 长度
  sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
  if ( v5 != 0 )
  {
    v13 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    v14 = sub_422E70(438);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
  }
  else
  {
    v13 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    v14 = sub_422E70(439);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
  }
  sub_43BEE0(v13, (int)v14, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
  return 1;  // 返回 1(成功)
}



// ============================================================
// 【分区 6】队伍管理（0x456690-0x457790）
// CNRDParty__vmt0（RTTI 自证）与队员槽位维护。
// ============================================================
// ------------------------------------------------------------
// 0x456690 sub_456690 —— 组队申请发送
// 同族 ·0x4564A0 的 op 11 版（440..446 文案，句柄填 0）【推断：入队申请】。
// ------------------------------------------------------------
char /*cdecl*/ sub_456690(int nArg1)  // sub_456690 —— 组队申请发送
{
  int v1; // eax
  uint32_t *v2; // esi
  char *v3; // eax
  int v5; // esi
  int v6; // eax
  int v7; // edi
  uint32_t *v8; // esi
  char *v9; // eax
  uint32_t *v10; // esi
  char *v11; // eax
  int nArg12; // [esp+4h] [ebp-8h] BYREF
  uint8_t v13[4]; // [esp+8h] [ebp-4h] BYREF

  v1 = sub_429830((uint32_t *)dword_8F8500, nArg1);  // sub_429830 —— 结果 = 表按键查找（uint16）
  if ( v1 == 0 )
  {
    v2 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    v3 = sub_422E70(440);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
LABEL_5:
    sub_43BEE0(v2, (int)v3, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
    return 0;
  }
  if ( *(uint32_t *)(v1 + 68) != 0 )
  {
    v2 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    v3 = sub_422E70(441);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    goto LABEL_5;
  }
  v5 = *(uint32_t *)(v1 + 184);  // 读字段 v5 = v1+184（bSingleTarget）
  v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
  v7 = *(uint32_t *)(v6 + 184);  // 读字段 v7 = v6+184（bSingleTarget）
  if ( v5 != 0 )
  {
    if ( v7 != 0 )
    {
      v8 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
      v9 = sub_422E70(442);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
LABEL_9:
      sub_43BEE0(v8, (int)v9, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
      return 0;
    }
    if ( *(uint32_t *)(v5 + 60) - sub_56A720(v5) <= 0 )  // sub_56A720 —— 组队列表联动（55 行）
    {
      v8 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
      v9 = sub_422E70(443);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
      goto LABEL_9;
    }
  }
  else if ( v7 != 0 && *(uint32_t *)(v7 + 60) - sub_56A720(*(uint32_t *)(v6 + 184)) <= 0 )  // sub_56A720 —— 组队列表联动（55 行）
  {
    v8 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    v9 = sub_422E70(444);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    goto LABEL_9;
  }
  sub_423200(dword_8F7B08, 11);  // 【发送网络包API】
  nArg12 = nArg1;
  sub_423290(dword_8F7B08, (int)&nArg12, 2);  // sub_423290 —— 写 4B 长度
  v13[0] = 0;
  sub_423290(dword_8F7B08, (int)v13, 1);  // sub_423290 —— 写 4B 长度
  nArg12 = 0;
  sub_423290(dword_8F7B08, (int)&nArg12, 4);  // sub_423290 —— 写 4B 长度
  sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
  if ( v5 != 0 )
  {
    v10 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    v11 = sub_422E70(445);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
  }
  else
  {
    v10 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    v11 = sub_422E70(446);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
  }
  sub_43BEE0(v10, (int)v11, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x456850 sub_456850 —— 队伍槽重置
// 4 槽 +188 解锁清空 → 自身（429830 查 word_77F804）填入 +4 → +8 清 0；场景 2 联动 4542A0。
// ------------------------------------------------------------
char /*thiscall*/ sub_456850(int *this)  // sub_456850 —— 队伍槽重置 4 槽 +188 解锁清空 → 自身
{
  int *pThis_4; // esi
  uint32_t *pThis_42; // eax
  int i; // edx
  int v5; // eax
  int v6; // ecx
  char result; // al

  pThis_4 = this + 4;  // this+4 宿主对象
  pThis_42 = this + 4;  // this+4 宿主对象
  for ( i = 4; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    if ( *pThis_42 != 0 )  // pThis_42=this+4 宿主对象
    {
      *(uint8_t *)(*pThis_42 + 188) = 0;  // pThis_42=this+4 宿主对象
      *pThis_42 = 0;  // pThis_42=this+4 宿主对象
    }
    ++pThis_42;  // 计数自增 pThis_42
  }
  v5 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
  v6 = *pThis_4;  // pThis_4=this+4 宿主对象
  if ( *pThis_4 != v5 )  // pThis_4=this+4 宿主对象
  {
    if ( v6 != 0 )
      *(uint8_t *)(v6 + 188) = 0;  // 写字段 v6+188（nStatusIdx） ← 0
    if ( v5 != 0 )
      *(uint8_t *)(v5 + 188) = 1;  // 写字段 v5+188（nStatusIdx） ← 1
    *pThis_4 = v5;  // pThis_4=this+4 宿主对象
  }
  *(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  result = dword_8F7A24;  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 2 )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    return sub_4542A0(*(uint32_t **)(dword_8F7A24 + 24));  // sub_4542A0 —— 按钮可见态刷新
  return result;
}



// ------------------------------------------------------------
// 0x4568C0 sub_4568C0 —— 队伍表销毁
// 链表逐项 vt[1] 释放（41C5E0 推进）+ 红黑树节点递归释放（433BC0）+ 哨兵复位。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4568C0(uint32_t *this)  // sub_4568C0 —— 队伍表销毁
{
  uint32_t *fld_e2; // ecx
  uint32_t *v3; // eax
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void *i; // ebx
  uint32_t *pThis_1; // edi
  uint32_t *fld_e22; // esi
  uint32_t *result; // eax
  uint32_t *v9; // [esp+Ch] [ebp-4h] BYREF

  fld_e2 = (uint32_t *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
  v3 = (uint32_t *)*fld_e2;  // fld_e2=this+8 nSkillRec8
  v9 = (uint32_t *)*fld_e2;  // fld_e2=this+8 nSkillRec8
  if ( v9 != fld_e2 )  // fld_e2=this+8 nSkillRec8
  {
    do
    {
      v4 = (void (/*thiscall*/ ***)(uint32_t, int))v3[4];
      if ( v4 != nullptr )
        (**v4)(v4, 1);  // 调 v4 的虚函数（vt+0）
      sub_41C5E0(&v9);  // sub_41C5E0 —— 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
      v3 = v9;
    }
    while ( v9 != (uint32_t *)*(this + 2) );  // this+8〔nSkillRec8(推断)〕
  }
  pThis_1 = this + 1;
  fld_e22 = *(uint32_t **)(*(this + 2) + 4);  // this+8〔nSkillRec8(推断)〕
  for ( i = fld_e22; *((uint8_t *)fld_e22 + 21) == 0; i = fld_e22 )  // fld_e22=this+8 nSkillRec8
  {
    sub_433BC0((void **)fld_e22[2]);  // sub_433BC0 —— 红黑树递归销毁（+21 版）
    fld_e22 = (uint32_t *)*fld_e22;  // fld_e22=this+8 nSkillRec8
    j__free(i);  // 释放堆块
  }
  *(uint32_t *)(pThis_1[1] + 4) = pThis_1[1];
  result = (uint32_t *)pThis_1[1];
  pThis_1[2] = 0;
  *result = result;
  *(uint32_t *)(pThis_1[1] + 8) = pThis_1[1];
  return result;
}



// ------------------------------------------------------------
// 0x456950 sub_456950 —— 队伍表销毁（全清版）
// 同构 ·0x4568C0，另清 +3..+8 五指针。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_456950(void ***this)  // sub_456950 —— (dword_8F850C)
{
  void **fld_e2; // ecx
  uint32_t *Block2; // eax
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  uint32_t *fld_e22; // esi
  char v6; // al
  char v7; // al
  uint32_t *result; // eax
  void *Block; // [esp+Ch] [ebp-4h] BYREF

  fld_e2 = *(this + 2);  // 读字段 fld_e2 = this+2
  Block2 = *fld_e2;  // fld_e2=this+8 物品 id
  Block = *fld_e2;  // fld_e2=this+8 物品 id
  if ( Block != fld_e2 )  // fld_e2=this+8 物品 id
  {
    do
    {
      v4 = (void (/*thiscall*/ ***)(uint32_t, int))Block2[4];
      if ( v4 != nullptr )
        (**v4)(v4, 1);  // 调 v4 的虚函数（vt+0）
      sub_41C5E0(&Block);  // sub_41C5E0 —— 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
      Block2 = Block;
    }
    while ( Block != *(this + 2) );  // this+8〔nSkillRec8(推断)〕
  }
  fld_e22 = (*(this + 2))[1];  // this+8〔nSkillRec8(推断)〕
  v6 = *((uint8_t *)fld_e22 + 21);  // 读字段 v6 = fld_e22+21（bArmorState）
  Block = fld_e22;  // fld_e22=this+8 nSkillRec8
  if ( v6 == 0 )
  {
    do
    {
      sub_433BC0((void **)fld_e22[2]);  // sub_433BC0 —— 红黑树递归销毁（+21 版）
      fld_e22 = (uint32_t *)*fld_e22;  // fld_e22=this+8 nSkillRec8
      j__free(Block);  // 释放堆块
      v7 = *((uint8_t *)fld_e22 + 21);  // 读字段 v7 = fld_e22+21（bArmorState）
      Block = fld_e22;  // fld_e22=this+8 nSkillRec8
    }
    while ( v7 == 0 );  // 循环直到 v7 == 0
  }
  (*(this + 2))[1] = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  result = *(this + 2);  // 读字段 result = this+2
  *(this + 3) = nullptr;  // 写字段 this+3 ← nullptr
  *result = result;  // result=this+8 物品 id
  (*(this + 2))[2] = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  *(this + 4) = nullptr;  // 写字段 this+4（pHostObj） ← nullptr
  *(this + 5) = nullptr;  // 写字段 this+5 ← nullptr
  *(this + 6) = nullptr;  // 写字段 this+6 ← nullptr
  *(this + 7) = nullptr;  // 写字段 this+7（uPathTerm） ← nullptr
  *(this + 8) = nullptr;  // 写字段 this+8（nSkillRec8） ← nullptr
  return result;  // result=this+8 物品 id
}



// ------------------------------------------------------------
// 0x4569F0 sub_4569F0 —— 队员槽查询
// 472E30 查键命中取节点 +16 值，未命中 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_4569F0(uint32_t *this, char pszArg2)  // sub_4569F0 —— 存 队员槽查询 472E30 查键命中取节点 +16 值，未命中 0。
{
  int v4; // [esp+4h] [ebp-4h] BYREF

  sub_472E30(&v4, &pszArg2);  // 调 +13 现值比对，返回是否变更。
  if ( v4 == *(this + 2) )  // this+8〔nSkillRec8(推断)〕
    return 0;
  else
    return *(uint32_t *)(v4 + 16);  // 返回字段 v4+16（nChannelTypeSel）
}



// ------------------------------------------------------------
// 0x456A30 sub_456A30
// ------------------------------------------------------------
// attributes: thunk
uint32_t */*thiscall*/ sub_456A30(void ***this)  // +16 值，未命中 0
{
  return sub_456950(this);  // sub_456950 —— (dword_8F850C)
}



// ------------------------------------------------------------
// 0x456A40 sub_456A40 —— 红黑树插入
// 5648C0 建节点 + 染色修复（433130 左旋、4296E0 摘除重连）；超 0x1FFFFFFE 抛 map/set<T> too long。
// ------------------------------------------------------------
int */*thiscall*/ sub_456A40(int **this, int *pDwArg2, char pszArg3, int *pDwArg4, int nArg5)  // sub_456A40 —— 红黑树插入
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

  if ( (unsigned int)*(this + 2) >= 0x1FFFFFFE )  // this+8〔nSkillRec8(推断)〕
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v20 = 0;
    sub_401740(v17);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject = &std::length_error::`vftable';  // vftable 复位
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  fld_e1 = sub_5648C0(*(this + 1), pDwArg4, *(this + 1), nArg5, 0);  // sub_5648C0 —— 商店文本（23 行）
  fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
  fld_e15 = fld_e1;
  *(this + 2) = (int *)((char *)*(this + 2) + 1);  // 写字段 this+2 ← (int *)((char *)*(this + 2) + 1)
  if ( pDwArg4 == fld_e12 )  // fld_e12=this+4 宿主对象
  {
    fld_e12[1] = fld_e1;  // fld_e12=this+4 宿主对象
    **(this + 1) = fld_e1;  // 写字段 this+1 ← fld_e1
    (*(this + 1))[2] = fld_e1;  // this+4〔宿主对象〕
  }
  else if ( pszArg3 != 0 )
  {
    *pDwArg4 = fld_e1;
    fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
    if ( pDwArg4 == (int *)*fld_e13 )  // fld_e13=this+4 宿主对象
      *fld_e13 = fld_e1;  // fld_e13=this+4 宿主对象
  }
  else
  {
    pDwArg4[2] = fld_e1;
    fld_e14 = (int)*(this + 1);  // this+4〔宿主对象〕
    if ( pDwArg4 == *(int **)(fld_e14 + 8) )  // fld_e14=this+4 宿主对象
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // 写字段 fld_e14+8（nSkillRec8） ← fld_e1
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
            sub_433130(this, *v10);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(this, *(uint32_t **)(*(uint32_t *)(fld_e16 + 4) + 4));  // sub_4296E0 —— STL 内联红黑树节点摘除重连
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(this, (uint32_t *)*v10);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(this, *(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // sub_433130 —— 红黑树左旋（节点 0x18 版）
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;  // 写字段 v14+20（nPage） ← 1
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
  *(uint8_t *)((*(this + 1))[1] + 20) = 1;  // this+4〔宿主对象〕
  *pDwArg2 = fld_e1;
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x456BF0 sub_456BF0 —— 队伍条目初始化
// 内嵌 string 置空（4015C0）+ 4 槽 0xFFFF 哨兵 + 容量 4（+14）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_456BF0(uint32_t *this)  // sub_456BF0 —— 队伍条目初始化
{
  uint32_t *pThis_2; // ecx

  pThis_2 = this + 2;
  pThis_2[6] = 15;
  pThis_2[5] = 0;
  *((uint8_t *)pThis_2 + 4) = 0;  // 写字段 pThis_2+4（pHostObj）
  *this = 0;
  *(this + 1) = 0;  // 写字段 this+1 ← 0
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 9) = 0xFFFF;  // 写字段 this+9 ← 0xFFFF
  *(this + 10) = 0xFFFF;  // 写字段 this+10 ← 0xFFFF
  *(this + 11) = 0xFFFF;  // 写字段 this+11 ← 0xFFFF
  *(this + 12) = 0xFFFF;  // 写字段 this+12（nSkillRec12） ← 0xFFFF
  *(this + 13) = 0;  // 写字段 this+13 ← 0
  *(this + 14) = 4;  // 写字段 this+14 ← 4
  return this;
}



// ------------------------------------------------------------
// 0x456C70 sub_456C70 —— CNRDParty 构造
// vftbl_CNRDParty 自证：条目初始化（456BF0）后 unknown_libname_7(nArg2) 尾续。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_456C70(uint32_t *this, int nArg2)  // sub_456C70 —— CNRDParty 构造
{
  *this = &vftbl_CNRDParty;  // 装虚表/取地址：← vftbl_CNRDParty
  sub_456BF0(this + 1);  // sub_456BF0 —— 队伍条目初始化
  nullsub_3();  // 空桩函数（无操作）
  unknown_libname_7(nArg2);  // IDA 未命名库函数调用（CRT/数学库）
  return this;
}



// ------------------------------------------------------------
// 0x456CD0 CNRDParty__vmt0
// ------------------------------------------------------------
// CNRDParty::vmt0 —— 队伍对象构造（RTTI 自证）
void */*thiscall*/ CNRDParty__vmt0(void *Block, char pszArg2)  // 实现：CNRDParty::vmt0 —— 队伍对象构造（RTTI 自证）
{
  sub_456D00();  // sub_456D00 —— CNRDParty 析构主体
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x456D00 sub_456D00 —— CNRDParty 析构主体
// vftbl_CNRDParty 置回 + string 堆释放（容量 ≥ 16）+ 容量/长度复位。
// ------------------------------------------------------------
void /*thiscall*/ sub_456D00(void **this)  // sub_456D00 —— CNRDParty 析构主体
{
  *this = &vftbl_CNRDParty;  // 装虚表/取地址：← vftbl_CNRDParty
  nullsub_3();  // 空桩函数（无操作）
  if ( (unsigned int)*(this + 9) >= 0x10 )  // this+36〔nStateWord36(推断)〕
    j__free(*(this + 4));  // 释放堆块
  *(this + 9) = (void *)15;  // 写字段 this+9 ← (void *)15
  *(this + 8) = nullptr;  // 写字段 this+8（nSkillRec8） ← nullptr
  *((uint8_t *)this + 16) = 0;  // 写字段 this+16（nChannelTypeSel）
}



// ------------------------------------------------------------
// 0x456D70 sub_456D70 —— 队员移除
// 472E30 定位 → 4 槽 +184 反查清空（429830）→ 对象 vt[1] 销毁 → 4341B0 树摘除。
// ------------------------------------------------------------
int */*thiscall*/ sub_456D70(uint32_t *this, int nArg2)  // sub_456D70 —— 队员移除 472E30 定位 → 4 槽 +184 反查清空
{
  int *result; // eax
  void (/*thiscall*/ ***v4)(uint32_t, int); // ebx
  int *v5; // esi
  int i; // edi
  int v7; // eax
  uint32_t *pThis_1; // [esp+4h] [ebp-8h]
  int *v9; // [esp+8h] [ebp-4h] BYREF

  pThis_1 = this + 1;
  sub_472E30(&v9, &nArg2);  // 调 +13 现值比对，返回是否变更。
  result = v9;
  if ( v9 != (int *)*(this + 2) )  // this+8〔nSkillRec8(推断)〕
  {
    v4 = (void (/*thiscall*/ ***)(uint32_t, int))v9[4];
    v5 = (int *)(v4 + 10);
    for ( i = 4; i != 0; --i )  // 遍历计次循环（i != 0）
    {
      if ( *v5 != 0xFFFF )
      {
        v7 = sub_429830((uint32_t *)dword_8F8500, *v5);  // sub_429830 —— 结果 = 表按键查找（uint16）
        if ( v7 != 0 )
          *(uint32_t *)(v7 + 184) = 0;  // 写字段 v7+184（bSingleTarget） ← 0
      }
      ++v5;  // 计数自增 v5
    }
    if ( v4 != nullptr )
      (**v4)(v4, 1);  // 调 v4 的虚函数（vt+0）
    return sub_4341B0(pThis_1, &nArg2, (int)v9);  // sub_4341B0 —— std::map 节点摘除 + 红黑再平衡（0x18 节点版）
  }
  return result;
}



// ------------------------------------------------------------
// 0x456DF0 sub_456DF0 —— map 插入定位
// 红黑树下界查找（键 +12）+ 456A40 建节点；输出 (迭代器, 是否新建)。
// ------------------------------------------------------------
int /*thiscall*/ sub_456DF0(int **this, int pArg2, int *pDwArg3)  // sub_456DF0 —— map 插入定位
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
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v6 = fld_e1[1];  // fld_e1=this+4 宿主对象
  v7 = true;
  v13 = 1;
  if ( *(uint8_t *)(v6 + 21) == 0 )
  {
    v8 = *pDwArg3;
    do
    {
      v7 = v8 < *(uint32_t *)(v6 + 12);
      fld_e1 = (int *)v6;  // fld_e1=this+4 宿主对象
      v13 = v7;
      if ( v8 >= *(uint32_t *)(v6 + 12) )
        v6 = *(uint32_t *)(v6 + 8);  // 读字段 v6 = v6+8（nSkillRec8）
      else
        v6 = *(uint32_t *)v6;
    }
    while ( *(uint8_t *)(v6 + 21) == 0 );  // 写字段 v6+21（bArmorState） ← = 0 )
  }
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  pDwArg3 = fld_e1;  // fld_e1=this+4 宿主对象
  if ( v7 )
  {
    if ( fld_e1 == (int *)**(this + 1) )  // this+4〔宿主对象〕
    {
      v10 = *sub_456A40(this, (int *)&pDwArg3, 1, fld_e1, (int)pDwArg32);  // sub_456A40 —— 红黑树插入
      *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
      *(uint32_t *)pArg2 = v10;  // *pArg2 = v10
      return pArg2;
    }
    sub_4A3B30(&pDwArg3);  // 调 取后继再插
    fld_e12 = pDwArg3;
  }
  if ( fld_e12[3] >= *pDwArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // 写字段 pArg2+4（pHostObj） ← 0
    *(uint32_t *)pArg2 = fld_e12;  // *pArg2 = fld_e12
    return pArg2;
  }
  else
  {
    v12 = *sub_456A40(this, (int *)&pDwArg3, v13, fld_e1, (int)pDwArg32);  // sub_456A40 —— 红黑树插入
    *(uint32_t *)pArg2 = v12;  // *pArg2 = v12
    *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x456EB0 sub_456EB0 —— 队伍条目取或建
// 472E30 命中即回；否则 new 0x40 走 456C70 → 456DF0 插入。
// ------------------------------------------------------------
int */*thiscall*/ sub_456EB0(int **this, void *Block)  // sub_456EB0 —— 存 队伍条目取或建 472E30 命中即回；否则 new 0x40 走 456C70 → 456DF0 插入。
{
  int v2; // ebx
  int **pThis_1; // edi
  int *result; // eax
  uint32_t *pMem; // eax
  int *v7; // esi
  char v8[8]; // [esp+Ch] [ebp-1Ch] BYREF
  int v9; // [esp+14h] [ebp-14h] BYREF
  int *v10; // [esp+18h] [ebp-10h] BYREF
  int v11; // [esp+24h] [ebp-4h]

  v2 = (int)Block;
  pThis_1 = this + 1;
  sub_472E30(&v10, &Block);  // 调 +13 现值比对，返回是否变更。
  if ( v10 == *(this + 2) || (result = (int *)v10[4]) == nullptr )  // this+8〔nSkillRec8(推断)〕
  {
    pMem = operator new(0x40u);  // 堆分配
    Block = pMem;
    v7 = nullptr;
    v11 = 0;
    if ( pMem != nullptr )
      v7 = sub_456C70(pMem, v2);  // sub_456C70 —— CNRDParty 构造
    v11 = -1;
    v9 = v2;
    v10 = v7;
    sub_456DF0(pThis_1, (int)v8, &v9);  // sub_456DF0 —— map 插入定位
    return v7;
  }
  return result;
}



// ------------------------------------------------------------
// 0x456F50 sub_456F50 —— 奖励参数初始化
// +1/+9..+13/+40/+164 清零，模式位 +160 置 3。
// ------------------------------------------------------------
int /*thiscall*/ sub_456F50(uint32_t *this)  // sub_456F50 —— 奖励参数初始化
{
  *(this + 40) = 0;  // 写字段 this+40（bStateSub40） ← 0
  *(this + 11) = 0;  // 写字段 this+11 ← 0
  *(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  *(this + 13) = 0;  // 写字段 this+13 ← 0
  *(this + 164) = 0;  // 写字段 this+164（fAdd164） ← 0
  *(this + 1) = 0;  // 写字段 this+1 ← 0
  *(this + 9) = 0;  // 写字段 this+9 ← 0
  *(this + 10) = 0;  // 写字段 this+10 ← 0
  *(this + 160) = 3;  // 写字段 this+160（fAdd160） ← 3
  return 0;
}



// ------------------------------------------------------------
// 0x456F80 sub_456F80 —— 奖励 UI 对象释放
// +11 单对象 + +9 起 2 项 + +131 起 4 项 + +147 起 3 项逐项 vt[1]。
// ------------------------------------------------------------
int /*thiscall*/ sub_456F80(uint32_t *this)  // sub_456F80 —— 奖励 UI 对象释放
{
  int (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  int result; // eax
  uint32_t *pThis_9; // esi
  int i; // edi
  uint32_t *pThis_83; // esi
  int j; // edi
  uint32_t *pThis_93; // esi
  int k; // edi

  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);  // this+44〔nExpireMs(推断)〕
  if ( fld_e11 != nullptr )  // fld_e11=this+44 nExpireMs
    result = (**fld_e11)(fld_e11, 1);  // 调 fld_e11 的虚函数（vt+0）
  *(this + 11) = 0;  // 写字段 this+11 ← 0
  pThis_9 = this + 9;
  for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    if ( *pThis_9 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_9)(*pThis_9, 1);
    *pThis_9++ = 0;
  }
  pThis_83 = this + 131;
  for ( j = 4; j != 0; --j )  // 遍历计次循环（j != 0）
  {
    if ( *pThis_83 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_83)(*pThis_83, 1);
    *pThis_83++ = 0;
  }
  pThis_93 = this + 147;
  for ( k = 3; k != 0; --k )  // 遍历计次循环（k != 0）
  {
    if ( *pThis_93 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_93)(*pThis_93, 1);
    *pThis_93++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x457010 sub_457010 —— 场景类型联动标志
// 场景类型 +1 == 9 时，按 dword_8F8528+27 == 12 置 +11 对象 +16 标志【推断：结算态标志】。
// ------------------------------------------------------------
void */*thiscall*/ sub_457010(uint32_t *this)  // sub_457010 —— 场景类型联动标志
{
  void *result; // eax

  if ( *(this + 1) == 9 )  // this+4〔宿主对象〕
  {
    result = dword_8F8528;  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    *(uint8_t *)(*(this + 11) + 16) = *((uint32_t *)dword_8F8528 + 27) == 12;  // dword_8F8528 —— 对象池借出（按池号取可用对象）
  }
  return result;
}



// ------------------------------------------------------------
// 0x457040 sub_457040 —— 控件 53 全屏绘制
// 418DD0(53) 取件后 vt128 全屏绘制，uArg1 入 alpha 高位。
// ------------------------------------------------------------
int /*stdcall*/ sub_457040(uint8_t uArg1)  // sub_457040 —— 控件 53 全屏绘制
{
  int result; // eax

  result = sub_418DD0(53);  // sub_418DD0 —— 资源句柄 (101)
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(  // 虚调用 vt+128（result）目标坐标y上界
             result,
             0,
             0,
             dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
             1065353216,
             1065353216,
             0,
             (uArg1 << 24) | 0xFFFFFF,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x457090 sub_457090 —— 奖励箱列表逐项淡入
// +66 项循环：+67+i 时刻起 500ms lerp（4049C0）写 alpha，控件号 3i（0/3/6..）。
// ------------------------------------------------------------
int /*thiscall*/ sub_457090(int *this)  // sub_457090 —— 奖励箱列表逐项淡入
{
  int result; // eax
  int *pThis_43; // edi
  int pThis_2; // eax
  int v5; // ebx
  int pObj; // eax
  bool fld_e66; // cc
  int v8; // [esp+4h] [ebp-8h]
  int v9; // [esp+8h] [ebp-4h]

  result = 0;
  v8 = 0;
  if ( *(this + 66) > 0 )  // this+264〔nAnimHandle(推断)〕
  {
    v9 = 0;
    pThis_43 = this + 67;  // this+67〔nPeriodMs〕
    do
    {
      if ( *pThis_43 > 0 )  // pThis_43=this+67 nPeriodMs
      {
        pThis_2 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
        v5 = (uint64_t)sub_4049C0(0.0, 255.0, pThis_2 - *pThis_43, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        pObj = sub_418DD0(v9);  // sub_418DD0 —— 资源句柄 (101)
        if ( pObj != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
            pObj,
            0,
            0,
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            1065353216,
            1065353216,
            0,
            ((uint8_t)v5 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
      }
      result = v8 + 1;
      ++pThis_43;  // 计数自增 pThis_43
      fld_e66 = ++v8 < *(this + 66);  // this+264〔nAnimHandle(推断)〕
      v9 += 3;
    }
    while ( fld_e66 );  // fld_e66=this+264 nAnimHandle
  }
  return result;
}



// ------------------------------------------------------------
// 0x457160 sub_457160 —— 开箱动画 I（53/54/55 组）
// 1800ms 时间轴：控件 53/54/55 交叉淡变（4049C0 ×3），491530/491630 调色模式配对。
// ------------------------------------------------------------
int /*thiscall*/ sub_457160(void *this)  // sub_457160 —— 开箱动画 I（53/54/55 组）
{
  int pThis_8; // edi
  int v2; // eax
  int v3; // esi
  int pObj2; // eax
  int v5; // eax
  int v6; // esi
  int pObj4; // eax
  double v8; // st7
  int result; // eax
  int v10; // eax
  int v11; // esi
  int pObj; // eax
  int pObj3; // eax
  int v14; // [esp-8h] [ebp-14h]
  int v15; // [esp-8h] [ebp-14h]

  pThis_8 = (int)this + 8;  // this+8 物品 id
  if ( sub_699000((int)this + 8) >= 1800 )  // 【clock_now(clk)】
  {
    result = sub_699000(pThis_8);  // 【clock_now(clk)】
    if ( result >= 1800 )
      return result;
    sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    v10 = sub_699000(pThis_8);  // 【clock_now(clk)】
    v11 = ((uint8_t)(uint64_t)sub_4049C0(255.0, 0.0, v10, 1800) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    pObj = sub_418DD0(54);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
        pObj,
        0,
        0,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        v11,
        1333788672,
        1333788672);
    v15 = sub_699000(pThis_8);  // 【clock_now(clk)】
    v8 = sub_4049C0(200.0, 0.0, v15, 1800);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  }
  else
  {
    v2 = sub_699000(pThis_8);  // 【clock_now(clk)】
    v3 = ((uint8_t)(uint64_t)sub_4049C0(255.0, 0.0, v2, 1800) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    pObj2 = sub_418DD0(53);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj2 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚调用 vt+128（pObj2）目标坐标y上界
        pObj2,
        0,
        0,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        v3,
        1333788672,
        1333788672);
    sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    v5 = sub_699000(pThis_8);  // 【clock_now(clk)】
    v6 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 255.0, v5, 1800) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    pObj4 = sub_418DD0(54);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj4 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(  // 虚调用 vt+128（pObj4）目标坐标y上界
        pObj4,
        0,
        0,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        v6,
        1333788672,
        1333788672);
    v14 = sub_699000(pThis_8);  // 【clock_now(clk)】
    v8 = sub_4049C0(0.0, 200.0, v14, 1800);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  }
  pObj3 = sub_418DD0(55);  // sub_418DD0 —— 资源句柄 (101)
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚调用 vt+128（pObj3）目标坐标y上界
      pObj3,
      0,
      0,
      dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      1065353216,
      1065353216,
      0,
      ((uint8_t)(uint64_t)v8 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  return sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
}



// ------------------------------------------------------------
// 0x457370 sub_457370 —— 开箱动画 II（多箱版）
// 同族 ·0x457160 的多箱版：每箱三元组控件（v21=2+3i 起）同轴播放。
// ------------------------------------------------------------
int /*thiscall*/ sub_457370(int *this)  // sub_457370 —— 开箱动画 II（多箱版）
{
  int result; // eax
  int pThis_2; // eax
  int pThis_22; // ecx
  int v5; // eax
  int v6; // edi
  int pObj; // eax
  int pThis_23; // eax
  int v9; // edi
  int pObj2; // eax
  double v11; // st7
  int pThis_25; // eax
  int v13; // edi
  int pObj3; // eax
  int pObj4; // eax
  bool fld_e66; // cc
  int pThis_24; // [esp-10h] [ebp-20h]
  int pThis_26; // [esp-10h] [ebp-20h]
  int v19; // [esp+4h] [ebp-Ch]
  int *pThis_43; // [esp+8h] [ebp-8h]
  int v21; // [esp+Ch] [ebp-4h]

  result = *(this + 66);  // 读字段 result = this+66
  v19 = 0;
  if ( result > 0 )  // result=this+264 动画句柄
  {
    v21 = 2;
    pThis_43 = this + 67;  // this+67〔nPeriodMs〕
    do
    {
      if ( *pThis_43 > 0 )  // pThis_43=this+67 nPeriodMs
      {
        pThis_2 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
        pThis_22 = (int)(this + 2);  // this+8〔nSkillRec8(推断)〕
        if ( pThis_2 < 1800 )
        {
          v5 = sub_699000(pThis_22);  // 【clock_now(clk)】
          v6 = ((uint8_t)(uint64_t)sub_4049C0(255.0, 0.0, v5, 1800) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          pObj = sub_418DD0(v21 - 2);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
              pObj,
              0,
              0,
              dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
              1065353216,
              1065353216,
              0,
              v6,
              1333788672,
              1333788672);
          sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
          pThis_23 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
          v9 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 255.0, pThis_23, 1800) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          pObj2 = sub_418DD0(v21 - 1);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj2 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚调用 vt+128（pObj2）目标坐标y上界
              pObj2,
              0,
              0,
              dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
              1065353216,
              1065353216,
              0,
              v9,
              1333788672,
              1333788672);
          pThis_24 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
          v11 = sub_4049C0(0.0, 200.0, pThis_24, 1800);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
LABEL_14:
          pObj4 = sub_418DD0(v21);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj4 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(  // 虚调用 vt+128（pObj4）目标坐标y上界
              pObj4,
              0,
              0,
              dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
              1065353216,
              1065353216,
              0,
              ((uint8_t)(uint64_t)v11 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
          goto LABEL_17;
        }
        if ( sub_699000(pThis_22) < 1800 )  // 【clock_now(clk)】
        {
          sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
          pThis_25 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
          v13 = ((uint8_t)(uint64_t)sub_4049C0(255.0, 0.0, pThis_25, 1800) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          pObj3 = sub_418DD0(v21 - 1);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj3 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚调用 vt+128（pObj3）目标坐标y上界
              pObj3,
              0,
              0,
              dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
              1065353216,
              1065353216,
              0,
              v13,
              1333788672,
              1333788672);
          pThis_26 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
          v11 = sub_4049C0(200.0, 0.0, pThis_26, 1800);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          goto LABEL_14;
        }
      }
LABEL_17:
      result = v19 + 1;  // result=this+264 动画句柄
      fld_e66 = ++v19 < *(this + 66);  // this+264〔nAnimHandle(推断)〕
      ++pThis_43;  // 计数自增 pThis_43
      v21 += 3;
    }
    while ( fld_e66 );  // fld_e66=this+264 nAnimHandle
  }
  return result;  // result=this+264 动画句柄
}


// ------------------------------------------------------------
// 0x4575F0 sub_4575F0 —— 开箱动画 III（56/57 组）
// 控件 56/57 + fArg2 透明度参数；两分支时间窗 1800/2300ms。
// ------------------------------------------------------------
int /*usercall*/ sub_4575F0@<eax>(int pArg1@<ecx>, double fArg2@<st0>)  // 实现：开箱动画 III（56/57 组）
{
  int v2; // edi
  int v3; // eax
  int pObj; // eax
  int result; // eax
  int v6; // eax
  int pObj3; // eax
  int pObj2; // eax
  int v9; // [esp-8h] [ebp-14h]
  int v10; // [esp-8h] [ebp-14h]

  v2 = pArg1 + 8;  // 计算 v2 = pArg1 + 8
  if ( sub_699000(pArg1 + 8) >= 1800 )  // 【clock_now(clk)】
  {
    result = sub_699000(v2);  // 【clock_now(clk)】
    if ( result >= 1800 )  // result=this+264 动画句柄
      return result;  // result=this+264 动画句柄
    sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    v6 = sub_699000(v2);  // 【clock_now(clk)】
    sub_4049C0(200.0, 0.0, v6, 1800);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    pObj3 = sub_418DD0(56);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj3 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚调用 vt+128（pObj3）目标坐标y上界
        pObj3,
        0,
        0,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        ((uint8_t)(uint64_t)fArg2 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v10 = sub_699000(v2);  // 【clock_now(clk)】
    sub_4049C0(150.0, 0.0, v10, 1800);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  }
  else
  {
    sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    v3 = sub_699000(v2);  // 【clock_now(clk)】
    sub_4049C0(0.0, 200.0, v3, 2300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    pObj = sub_418DD0(56);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
        pObj,
        0,
        0,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        ((uint8_t)(uint64_t)fArg2 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v9 = sub_699000(v2);  // 【clock_now(clk)】
    sub_4049C0(0.0, 150.0, v9, 2300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  }
  pObj2 = sub_418DD0(57);  // sub_418DD0 —— 资源句柄 (101)
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚调用 vt+128（pObj2）目标坐标y上界
      pObj2,
      0,
      0,
      dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      1065353216,
      1065353216,
      0,
      ((uint8_t)(uint64_t)fArg2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  return sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
}



// ============================================================
// 【分区 7】奖励系统 I（0x457790-0x458930）
// 奖励箱开启：REWARD_OPEN1（0x4577F0/0x458120，CLICK_BUTTON2 自证）。
// ============================================================
// ------------------------------------------------------------
// 0x457790 sub_457790 —— 全箱判定
// 统计 +127 起 +109 项中非 -1 计数是否等于 +109（全箱已分配）。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_457790(int *this)  // sub_457790 —— 全箱判定
{
  int fld_e109; // edx
  int v2; // esi
  uint32_t *pThis_7F; // eax
  int fld_e1092; // ecx

  fld_e109 = *(this + 109);  // 读字段 fld_e109 = this+109
  v2 = 0;
  if ( fld_e109 > 0 )  // fld_e109=this+436 【推断】攻击数据表取值
  {
    pThis_7F = this + 127;
    fld_e1092 = *(this + 109);  // 读字段 fld_e1092 = this+109
    do
    {
      if ( *pThis_7F != -1 )
        ++v2;  // 计数自增 v2
      ++pThis_7F;  // 计数自增 pThis_7F
      --fld_e1092;  // 计数自减 fld_e1092
    }
    while ( fld_e1092 != 0 );  // 循环直到 fld_e1092 != 0
  }
  return v2 == fld_e109;  // fld_e109=this+436 【推断】攻击数据表取值
}



// ------------------------------------------------------------
// 0x4577C0 sub_4577C0 —— 开箱完成上报
// 发包 op 73（无载荷）并置 +580 完成标志。
// ------------------------------------------------------------
int /*thiscall*/ sub_4577C0(uint8_t *this)  // sub_4577C0 —— 开箱完成上报
{
  int result; // eax

  sub_423200(dword_8F7B08, 73);  // 【发送网络包API】
  result = sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
  *(this + 580) = 1;  // 写字段 this+580（uOffset580） ← 1
  return result;
}



// ------------------------------------------------------------
// 0x4577F0 sub_4577F0
// ------------------------------------------------------------
// 奖励箱开启 —— REWARD_OPEN1 + CLICK_BUTTON2 自证：
// +127 槽空且 a3 有效 → 记箱号/时刻；与本地主角 vt+1216 比对 → +135 命中标记
// （CLICK_BUTTON2）否则 +146=-1 → 按钮熄灭 → REWARD_OPEN1
void /*thiscall*/ sub_4577F0(uint32_t *this, char pszArg2, char pszArg3)  // 【奖励开箱等多处）】
{
  if ( *(this + pszArg2 + 127) == -1 && pszArg3 != -1 )
  {
    *(this + pszArg2 + 127) = pszArg3;
    *(this + pszArg2 + 136) = sub_699000((int)(this + 41));  // sub_699000 —— 【clock_now(clk)】
    if ( pszArg3 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1216))(dword_8F7C04) )  // 虚调用 vt+1216（dword_8F7C04 虚表槽）
    {
      *(this + 135) = pszArg2;  // 写字段 this+135 ← pszArg2
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    }
    else
    {
      *(this + 146) = -1;  // 写字段 this+146 ← -1
    }
    *(uint8_t *)(*(this + pszArg2 + 131) + 16) = 0;
    sub_432EA0("REWARD_OPEN1", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
  }
}



// ------------------------------------------------------------
// 0x457890 sub_457890 —— 开箱卡片动画
// 控件 34 整屏淡入 + 逐箱（步长 158）控件 45/40 位移，1200ms lerp。
// ------------------------------------------------------------
int /*thiscall*/ sub_457890(uint32_t *this)  // sub_457890 —— 开箱卡片动画
{
  int pThis_2; // edi
  int pThis_22; // eax
  int v4; // esi
  int pObj; // eax
  int result; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // esi
  int pObj2; // eax
  int v12; // eax
  int v13; // esi
  int pObj3; // eax
  bool fld_e1092; // cc
  float fld_e109; // [esp+24h] [ebp-28h]
  int v17; // [esp+3Ch] [ebp-10h]
  int v18; // [esp+40h] [ebp-Ch]
  int v19; // [esp+44h] [ebp-8h]
  int v20; // [esp+48h] [ebp-4h]

  pThis_2 = (int)(this + 2);  // this+8〔nSkillRec8(推断)〕
  pThis_22 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
  v4 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 200.0, pThis_22, 1200) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  pObj = sub_418DD0(34);  // sub_418DD0 —— 资源句柄 (101)
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
      pObj,
      0,
      0,
      dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      1065353216,
      1065353216,
      0,
      v4,
      1333788672,
      1333788672);
  result = 0;
  v17 = 0;
  if ( (int)*(this + 109) > 0 )  // this+436〔nAtkTableVal(推断)〕
  {
    v20 = 0;
    do
    {
      v7 = sub_699000(pThis_2);  // 【clock_now(clk)】
      fld_e109 = (float)(v20 + dword_6C6E00[*(this + 109)]);  // this+436〔nAtkTableVal(推断)〕
      v18 = (uint64_t)sub_4049C0(243.0, fld_e109, v7, 1200);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v8 = sub_699000(pThis_2);  // 【clock_now(clk)】
      v19 = (uint64_t)sub_4049C0(163.0, 163.0, v8, 1200);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v9 = sub_699000(pThis_2);  // 【clock_now(clk)】
      v10 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 255.0, v9, 1200) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      pObj2 = sub_418DD0(45);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj2 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚调用 vt+128（pObj2）目标坐标y上界
          pObj2,
          v18,
          v19,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          v10,
          1333788672,
          1333788672);
      sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      v12 = sub_699000(pThis_2);  // 【clock_now(clk)】
      v13 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 220.0, v12, 1200) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      pObj3 = sub_418DD0(40);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj3 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚调用 vt+128（pObj3）目标坐标y上界
          pObj3,
          v18,
          v19,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          v13,
          1333788672,
          1333788672);
      sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
      result = v17 + 1;
      fld_e1092 = ++v17 < *(this + 109);  // this+436〔nAtkTableVal(推断)〕
      v20 += 158;
    }
    while ( fld_e1092 );  // fld_e1092=this+436 nAtkTableVal
  }
  return result;
}



// ------------------------------------------------------------
// 0x457AA0 sub_457AA0 —— 开箱结果高亮
// 按 nArg2 箱：悬停/选中（79BE3C/79BE34 + 对象 +17）→ 控件 86 高亮；未开（+127==-1）→ 36..39 循环闪烁，
// +500ms 内控件 40 淡出。
// ------------------------------------------------------------
int /*thiscall*/ sub_457AA0(int *this, int nArg2)  // sub_457AA0 —— 开箱结果高亮
{
  int result; // eax
  int *pThis_83; // edx
  int v5; // ecx
  int v6; // ebx
  int v7; // esi
  int pThis_2; // eax
  int pObj; // eax
  int pObj3; // eax
  int pThis_22; // eax
  int v12; // esi
  int pObj2; // eax
  bool v14; // cc
  uint32_t *pThis_832; // [esp+4h] [ebp-Ch]
  int v16; // [esp+8h] [ebp-8h]
  int v17; // [esp+Ch] [ebp-4h]

  result = *(this + 109);  // 读字段 result = this+109
  v16 = 0;
  if ( result > 0 )  // result=this+436 【推断】攻击数据表取值
  {
    pThis_83 = this + 131;
    v17 = 0;
    pThis_832 = this + 131;
    do
    {
      v5 = *pThis_83;
      if ( nArg2 == *pThis_83 )
      {
        v6 = v17 + dword_6C6E00[result];  // result=this+436 【推断】攻击数据表取值
        if ( *(uint8_t *)(v5 + 17) != 0
          && ((v7 = *(uint32_t *)(v5 + 12), dword_79BE3C == v7) || *(uint8_t *)(v5 + 17) != 0 && dword_79BE34 == v7) )  // 动画对象指针(帧同步比对基准 C)
        {
          sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
          pObj3 = sub_418DD0(86);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj3 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v6, 163, dword_79C0B0);  // 虚调用 vt+152（pObj3）取值(参数)
          sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
        }
        else if ( *(pThis_83 - 4) == -1 )
        {
          pThis_2 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
          pObj = sub_418DD0(pThis_2 % 800 / 200 + 36);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v6, 163, dword_79C0B0);  // 虚调用 vt+152（pObj）取值(参数)
        }
        if ( sub_699000((int)(this + 2)) < 500 )  // 【clock_now(clk)】
        {
          sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
          pThis_22 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
          v12 = ((uint8_t)(uint64_t)sub_4049C0(220.0, 0.0, pThis_22, 500) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          pObj2 = sub_418DD0(40);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj2 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚调用 vt+128（pObj2）目标坐标y上界
              pObj2,
              v6,
              163,
              dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
              1065353216,
              1065353216,
              0,
              v12,
              1333788672,
              1333788672);
          sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
        }
      }
      result = *(this + 109);  // 读字段 result = this+109
      pThis_83 = pThis_832 + 1;
      v14 = ++v16 < result;  // result=this+436 【推断】攻击数据表取值
      ++pThis_832;  // 计数自增 pThis_832
      v17 += 158;
    }
    while ( v14 );
  }
  return result;  // result=this+436 【推断】攻击数据表取值
}



// ------------------------------------------------------------
// 0x457C60 sub_457C60 —— 开箱时序表初始化
// 写入 3 组成对时刻（步长 400ms 起点 1000/1400/1800，对端各 +2000）。
// ------------------------------------------------------------
int /*thiscall*/ sub_457C60(int *this)  // sub_457C60 —— 开箱时序表初始化
{
  int pThis_29; // ebx
  int v2; // esi
  int *pThis_4F; // edi
  int result; // eax

  pThis_29 = (int)(this + 41);  // this+164〔fAdd164(推断)〕
  v2 = 1000;
  pThis_4F = this + 79;
  do
  {
    *(pThis_4F - 1) = v2 + sub_699000(pThis_29);  // sub_699000 —— 【clock_now(clk)】
    result = sub_699000(pThis_29) + v2 + 2000;  // 【clock_now(clk)】
    *pThis_4F = result;
    v2 += 400;
    pThis_4F += 3;
  }
  while ( v2 < 2200 );  // 循环直到 v2 < 2200
  return result;
}



// ------------------------------------------------------------
// 0x457CB0 sub_457CB0 —— 开箱缩放动画
// 3 槽（+316 起步长 12）：4049F0 曲线采样 + 控件 58 vt156 缩放 0.5→1.3。
// ------------------------------------------------------------
int /*usercall*/ sub_457CB0@<eax>(int pArg1@<ecx>, double fArg2@<st0>)  // 实现：开箱缩放动画
{
  uint32_t *v2; // eax
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // esi
  int v7; // ebx
  int pObj; // eax
  bool v9; // zf
  int result; // eax
  float fArg23; // [esp+0h] [ebp-30h]
  float fArg22; // [esp+1Ch] [ebp-14h]
  int v13; // [esp+20h] [ebp-10h]
  int v14; // [esp+24h] [ebp-Ch]
  int pArg12; // [esp+28h] [ebp-8h]
  uint32_t *v16; // [esp+2Ch] [ebp-4h]

  v2 = (uint32_t *)(pArg1 + 316);
  pArg12 = pArg1;
  v16 = (uint32_t *)(pArg1 + 316);
  v14 = 3;
  while ( 1 )
  {
    v3 = *(v2 - 1);
    v4 = *v2 - v3;
    v5 = sub_699000(pArg1 + 164);  // 【clock_now(clk)】
    v6 = v5 - v3;  // 计算 v6 = v5 - v3
    v13 = v5 - v3;  // 计算 v13 = v5 - v3
    if ( v5 - v3 > 0 && v6 < v4 )
    {
      if ( v6 >= 800 )
        sub_4049F0(255.0, 0.0, v5 - v3, v4, 1);  // sub_4049F0 —— 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
      else
        sub_4049F0(0.0, 255.0, v5 - v3, 800, 1);  // sub_4049F0 —— 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
      v7 = (uint64_t)fArg2;
      sub_4049F0(0.5, 1.3, v6, v4, 1);  // sub_4049F0 —— 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
      fArg22 = fArg2;
      sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      pObj = sub_418DD0(58);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj != 0 )
      {
        fArg2 = (double)v13 * 0.02;
        fArg23 = fArg2;
        (*(void (/*thiscall*/ **)(int, int, int, int, float, float, uint32_t, int, int, int))(*(uint32_t *)pObj + 156))(  // 虚调用 vt+156（pObj 虚表槽）
          pObj,
          175,
          20,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          COERCE_FLOAT(LODWORD(fArg22)),
          COERCE_FLOAT(LODWORD(fArg22)),
          LODWORD(fArg23),
          ((uint8_t)v7 << 24) | 0xFFFFFF,
          1128923136,
          1128923136);
      }
      sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
    }
    result = v14 - 1;
    v9 = v14 == 1;
    v16 += 3;
    --v14;  // 计数自减 v14
    if ( v9 )
      break;
    v2 = v16;
    pArg1 = pArg12;
  }
  return result;
}



// ------------------------------------------------------------
// 0x457DD0 sub_457DD0 —— 未开箱余量提示
// 满箱计数不足时点亮控件 83/82，并按 (4 - 经过秒) 调 69A110(305,355) 闪烁计数。
// ------------------------------------------------------------
void /*thiscall*/ sub_457DD0(int *this)  // sub_457DD0 —— 未开箱余量提示
{
  int fld_e109; // ecx
  int v3; // edi
  uint32_t *pThis_7F; // eax
  int i; // edx
  int pObj; // eax
  int pObj2; // eax
  int fld_e54; // ecx
  int v9; // edi

  fld_e109 = *(this + 109);  // 读字段 fld_e109 = this+109
  v3 = 0;
  if ( fld_e109 > 0 )  // fld_e109=this+436 【推断】攻击数据表取值
  {
    pThis_7F = this + 127;
    for ( i = fld_e109; i != 0; --i )  // 遍历计次循环（i != 0）
    {
      if ( *pThis_7F != -1 )
        ++v3;  // 计数自增 v3
      ++pThis_7F;  // 计数自增 pThis_7F
    }
  }
  if ( v3 != fld_e109 )  // fld_e109=this+436 【推断】攻击数据表取值
  {
    pObj = sub_418DD0(83);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 152))(pObj, 0, 0, dword_79C0B0);  // 虚调用 vt+152（pObj）取值(参数)
    pObj2 = sub_418DD0(82);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj2 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pObj2 + 152))(pObj2, 0, 0, dword_79C0B0);  // 虚调用 vt+152（pObj2）取值(参数)
    fld_e54 = sub_699000((int)(this + 41)) - *(this + 54);  // 【clock_now(clk)】
    if ( fld_e54 >= 1000 )
    {
      v9 = (4 - fld_e54 / 1000) & ((4 - fld_e54 / 1000 < 0) - 1);
      sub_69A110(305, 355, v9, -1);
      sub_69A110(305, 355, v9, -1);
    }
  }
}



// ------------------------------------------------------------
// 0x457EC0 sub_457EC0 —— 开箱选项提交
// 门禁：nArg3==2 需换值或 612 计时 ≥500ms；+660 或 ArgList≥2 放行；发包 op 75 分路编码，
// 写 +604/+608，复位 +625/+626 与 612 计时，按 byte_6C6E70 出提示。
// ------------------------------------------------------------
void /*thiscall*/ sub_457EC0(int this, unsigned int ArgList, int nArg3)  // sub_457EC0 —— 开箱选项提交
{
  int nArg32; // ebx

  nArg32 = nArg3;
  if ( (nArg3 != 2 || *(uint32_t *)(this + 604) != ArgList && sub_699000(this + 612) >= 500)  // 【clock_now(clk)】
    && (*(uint8_t *)(this + 660) != 0 || ArgList >= 2) )  // 开箱选项提交
  {
    *(uint32_t *)(this + 604) = ArgList;  // 写字段 this+604 ← ArgList
    *(uint32_t *)(this + 608) = nArg32;  // 写字段 this+608（nAttackGate） ← nArg32
    sub_423200(dword_8F7B08, 75);  // 【发送网络包API】
    HIBYTE(nArg3) = nArg32;
    sub_423290(dword_8F7B08, (int)&nArg3 + 3, 1);  // sub_423290 —— 写 4B 长度
    if ( ArgList != 0 )
    {
      if ( ArgList == 1 )
      {
        HIBYTE(nArg3) = 1;
        sub_423290(dword_8F7B08, (int)&nArg3 + 3, 1);  // sub_423290 —— 写 4B 长度
      }
      else if ( ArgList == 2 )
      {
        HIBYTE(nArg3) = 2;
        sub_423290(dword_8F7B08, (int)&nArg3 + 3, 1);  // sub_423290 —— 写 4B 长度
      }
    }
    else
    {
      HIBYTE(nArg3) = 0;
      sub_423290(dword_8F7B08, (int)&nArg3 + 3, 1);  // sub_423290 —— 写 4B 长度
    }
    sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
    *(uint8_t *)(this + 625) = 0;  // 写字段 this+625 ← 0
    *(uint8_t *)(this + 626) = 0;  // 写字段 this+626 ← 0
    sub_698F90(this + 612, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    off_77F3FC((char *)&byte_6C6E70, ArgList, nArg32);  // off_77F3FC —— 日志打印（printf 风格）
  }
}



// ------------------------------------------------------------
// 0x457FB0 sub_457FB0 —— 开箱模式切换显示
// 记 +151/+152 并按 byte_6C6E98 提示；非自身时逐行配色 69C980（基表 unk_6C6E2C，命中 ArgList 行用 4×pArg3 偏移表）；
// pArg3==1 记 +160/+161/+162 并打 479..481 文案。
// ------------------------------------------------------------
int /*thiscall*/ sub_457FB0(uint32_t *this, int ArgList, int pArg3)  // sub_457FB0 —— 开箱模式切换显示
{
  int v3; // esi
  uint32_t *v5; // ebx
  int v6; // ebx
  int result; // eax
  int *v8; // esi
  uint32_t *pThis_93; // ebx
  int v10; // eax
  int v11; // esi
  uint32_t *v12; // esi
  char *v13; // eax
  int *v14; // [esp+Ch] [ebp-8h]
  int v15; // [esp+10h] [ebp-4h]

  v3 = ArgList;
  *(this + 151) = ArgList;  // 写字段 this+151 ← ArgList
  *(this + 152) = pArg3;  // 写字段 this+152（nAdd152） ← pArg3
  off_77F3FC((char *)&byte_6C6E98, ArgList, pArg3);  // off_77F3FC —— 日志打印（printf 风格）
  v5 = (uint32_t *)dword_8F850C;  // dword_8F850C —— 队伍槽重置 4 槽 +188 解锁清空 → 自身
  if ( sub_456480((uint32_t *)dword_8F850C) == -1 )  // sub_456480 —— 存 座位号
    v6 = 0;
  else
    v6 = v5[sub_456480(v5) + 4];  // sub_456480 —— 存 座位号
  result = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
  if ( v6 != result )
  {
    v15 = 0;
    v8 = (int *)&unk_6C6E2C;
    pThis_93 = this + 147;
    v14 = (int *)(4 * pArg3 + 7106092);
    do
    {
      v10 = *v8;
      if ( v15 == ArgList )
        v10 = *v14;
      result = sub_69C980(*(this + 13), v10, v10, v10, v10, 0, 0);  // 调 换 191/190/190 号图
      v8 += 4;
      ++pThis_93;  // 计数自增 pThis_93
      ++v15;  // 计数自增 v15
      v14 += 4;
    }
    while ( (int)v8 < (int)"REWARD_OPEN1" );  // 音效/动画 TAG REWARD_OPEN1
    v3 = ArgList;
  }
  if ( pArg3 == 1 )
  {
    *(this + 160) = v3;  // 写字段 this+160（fAdd160） ← v3
    *(this + 161) = **(uint32_t **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    result = dword_99FB8C;  // dword_99FB8C —— 触发条件评估器：遍历条件对象
    *(this + 162) = dword_99FB8C;  // dword_99FB8C —— 触发条件评估器：遍历条件对象
    if ( v3 != 0 )
    {
      v11 = v3 - 1;  // 计算 v11 = v3 - 1
      if ( v11 != 0 )
      {
        if ( v11 != 1 )
          return result;
        v12 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
        v13 = sub_422E70(481);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
      }
      else
      {
        v12 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
        v13 = sub_422E70(480);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
      }
    }
    else
    {
      v12 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
      v13 = sub_422E70(479);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    }
    return sub_43BEE0(v12, (int)v13, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
  }
  return result;
}



// ------------------------------------------------------------
// 0x458120 sub_458120
// ------------------------------------------------------------
// 奖励箱开启循环（REWARD_OPEN1 自证）【推断：多箱批量推进】
int /*thiscall*/ sub_458120(uint32_t *this)  // sub_458120 —— 调用 sub_458120
{
  *(this + 160) = 3;  // 写字段 this+160（fAdd160） ← 3
  *(this + 161) = -1;  // 写字段 this+161 ← -1
  *(this + 162) = -1;  // 写字段 this+162（bSubFlags648） ← -1
  return -1;
}



// ------------------------------------------------------------
// 0x458140 sub_458140 —— 52 字节元素计数
// (+2 - +1) / 52（空返回 0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_458140(int *this)  // sub_458140 —— 52 字节元素计数
{
  int result; // eax

  result = *(this + 1);  // 读字段 result = this+1
  if ( result != 0 )  // result=this+4 宿主对象
    return (*(this + 2) - result) / 52;  // this+8〔nSkillRec8(推断)〕
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x458160 sub_458160 —— 槽元素数大于一判定
// 按第 pArg2 槽（+111+4n）以 52 字节步长计数 >1 判定（魔数除 52）。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_458160(uint32_t *this, int pArg2)  // sub_458160 —— 槽元素数大于一判定
{
  int pThis_4; // edx
  unsigned int pThis_42; // edx

  pThis_4 = *(this + 4 * pArg2 + 111);
  if ( pThis_4 == 0 )
    return false;
  pThis_42 = (int)((uint64_t)(1321528399LL * (*(this + 4 * pArg2 + 112) - pThis_4)) >> 32) >> 4;
  return pThis_42 + (pThis_42 >> 31) > 1;
}



// ------------------------------------------------------------
// 0x4581C0 sub_4581C0 —— 奖励箱悬停点击派发
// uArg2 == +11（自身）→ 控件 0 + 选中行高亮（控件 13+，行 y=40/70/100）；
// 否则扫 3 箱：悬停(79BE3C)→457EC0(v,2)，点击(79BE34)→457EC0(v,1)+CLICK_BUTTON2。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4581C0(int *this, uint8_t *uArg2)  // sub_4581C0 —— 奖励箱悬停点击派发
{
  uint8_t *result; // eax
  bool fld_e11; // zf
  int pObj; // eax
  int fld_e152; // eax
  int fld_e1512; // esi
  int dword_8F850C2; // ebx
  int v9; // ebx
  int pObj3; // eax
  int pObj2; // eax
  int dword_8F850C3; // esi
  uint8_t *v13; // esi
  int v14; // esi
  uint32_t *pThis_93; // ebx
  int pObj4; // eax
  uint32_t v17[3]; // [esp+Ch] [ebp-Ch]
  int fld_e151; // [esp+20h] [ebp+8h]

  result = uArg2;
  fld_e11 = uArg2 == (uint8_t *)*(this + 11);  // this+44〔nExpireMs(推断)〕
  v17[0] = 40;
  v17[1] = 70;
  v17[2] = 100;
  if ( fld_e11 )  // fld_e11=this+44 nExpireMs
  {
    pObj = sub_418DD0(0);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, 352, 22, dword_79C0B0);  // 虚调用 vt+152（pObj）取值(参数)
    fld_e152 = *(this + 152);  // 读字段 fld_e152 = this+152（nAdd152）
    fld_e1512 = -1;
    fld_e151 = -1;
    if ( fld_e152 == 1 )  // fld_e152=this+152 nAdd152
    {
      fld_e151 = *(this + 151);  // 读字段 fld_e151 = this+151
    }
    else if ( fld_e152 == 2 )  // fld_e152=this+152 nAdd152
    {
      fld_e1512 = *(this + 151);  // 读字段 fld_e1512 = this+151
    }
    sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    if ( fld_e1512 != -1 )
    {
      dword_8F850C2 = dword_8F850C;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
      v9 = sub_456480(dword_8F850C) == -1 ? 0 : *(uint32_t *)(dword_8F850C2 + 4 * sub_456480(dword_8F850C2) + 16);  // sub_456480 —— 存 座位号；sub_456480 —— 存 座位号
      if ( v9 != sub_429830((uint16_t)word_77F804) )  // sub_429830 —— 结果 = 表按键查找（uint16）
      {
        pObj3 = sub_418DD0(fld_e1512 + 13);  // sub_418DD0 —— 资源句柄 (101)
        if ( pObj3 != 0 )
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)pObj3 + 152))(pObj3, 355, v17[fld_e1512], dword_79C0B0);  // 虚调用 vt+152（pObj3）取值(参数)
      }
    }
    if ( fld_e151 != -1 )
    {
      pObj2 = sub_418DD0(fld_e151 + 13);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj2 != 0 )
        (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)pObj2 + 152))(pObj2, 355, v17[fld_e151], dword_79C0B0);  // 虚调用 vt+152（pObj2）取值(参数)
    }
    return (uint8_t *)sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
  }
  else if ( *(this + 152) != 1 )  // this+608〔nAttackGate〕
  {
    dword_8F850C3 = dword_8F850C;  // dword_8F850C —— 队伍槽重置 4 槽 +188 解锁清空 → 自身
    v13 = sub_456480(dword_8F850C) == -1 ? nullptr : *(uint8_t **)(dword_8F850C3 + 4 * sub_456480(dword_8F850C3) + 16);  // sub_456480 —— 存 座位号；sub_456480 —— 存 座位号
    result = (uint8_t *)sub_429830((uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
    if ( v13 == result )
    {
      v14 = 0;
      pThis_93 = this + 147;
      do
      {
        result = (uint8_t *)*pThis_93;
        if ( uArg2 == (uint8_t *)*pThis_93 )
        {
          if ( result[17] != 0 && dword_79BE3C == *((uint32_t *)result + 3) )  // 动画对象指针(帧同步比对基准 C)
          {
            sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
            pObj4 = sub_418DD0(v14 + 13);  // sub_418DD0 —— 资源句柄 (101)
            if ( pObj4 != 0 )
              (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)pObj4 + 152))(pObj4, 355, v17[v14], dword_79C0B0);  // 虚调用 vt+152（pObj4）取值(参数)
            sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
            sub_457EC0(v14, 2);  // sub_457EC0 —— 开箱选项提交
          }
          result = (uint8_t *)*pThis_93;
          if ( *(uint8_t *)(*pThis_93 + 17) != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 当前动画对象指针(帧同步比对基准)
          {
            sub_457EC0(v14, 1);  // sub_457EC0 —— 开箱选项提交
            result = sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
          }
        }
        ++v14;  // 计数自增 v14
        ++pThis_93;  // 计数自增 pThis_93
      }
      while ( v14 < 3 );  // 循环直到 v14 < 3
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x458400 sub_458400 —— 奖励模式执行
// case 0/1：置 dword_8F7A24+20 链对象 +216 后（自身）发包 op 15，case 0 续 454680(+161,+162)；
// case 2/3 → 45B060(1)；收尾统一 +160=3、+161/+162=-1。
// ------------------------------------------------------------
char /*thiscall*/ sub_458400(int *this)  // sub_458400 —— 奖励模式执行
{
  int fld_e160; // eax
  uint32_t *v3; // edi
  int v4; // edi
  uint32_t *v5; // edi
  int v6; // edi

  fld_e160 = *(this + 160);  // 读字段 fld_e160 = this+160（fAdd160）
  switch ( fld_e160 )  // 按 fld_e160 分派
  {
    case 0:  // case 0 分派（奖励系统 I（0x457790-0x458930））
      *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 216) = 0;  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
      v3 = (uint32_t *)dword_8F850C;  // dword_8F850C —— 队伍槽重置 4 槽 +188 解锁清空 → 自身
      if ( sub_456480((uint32_t *)dword_8F850C) == -1 )  // sub_456480 —— 存 座位号
        v4 = 0;
      else
        v4 = v3[sub_456480(v3) + 4];  // sub_456480 —— 存 座位号
      fld_e160 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
      if ( v4 == fld_e160 )  // fld_e160=this+160 fAdd160
      {
        sub_423200(dword_8F7B08, 15);  // 【发送网络包API】
        sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
        LOBYTE(fld_e160) = sub_454680(*(uint32_t *)(dword_8F7A24 + 24), *(this + 161), *(this + 162));  // sub_454680 —— 房间选择确认
      }
      break;
    case 1:  // case 1 分派（奖励系统 I（0x457790-0x458930））
      *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 216) = 1;  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
      v5 = (uint32_t *)dword_8F850C;  // dword_8F850C —— 队伍槽重置 4 槽 +188 解锁清空 → 自身
      if ( sub_456480((uint32_t *)dword_8F850C) == -1 )  // sub_456480 —— 存 座位号
        v6 = 0;
      else
        v6 = v5[sub_456480(v5) + 4];  // sub_456480 —— 存 座位号
      fld_e160 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
      if ( v6 == fld_e160 )  // fld_e160=this+160 fAdd160
      {
        sub_423200(dword_8F7B08, 15);  // 【发送网络包API】
        LOBYTE(fld_e160) = sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
      }
      break;
    case 2:  // case 2 分派（奖励系统 I（0x457790-0x458930））
    case 3:  // case 3 分派（奖励系统 I（0x457790-0x458930））
      LOBYTE(fld_e160) = sub_45B060(1);  // sub_45B060 —— 淡入档位设定（·+120 = nArg2）
      break;
    default:
      break;
  }
  *(this + 160) = 3;  // 写字段 this+160（fAdd160） ← 3
  *(this + 161) = -1;  // 写字段 this+161 ← -1
  *(this + 162) = -1;  // 写字段 this+162（bSubFlags648） ← -1
  return fld_e160;  // fld_e160=this+160 fAdd160
}



// ------------------------------------------------------------
// 0x458550 sub_458550 —— 开箱数量文本绘制
// 取 +59 表（40 字节元素）末项：vt128 绘底 105,133，再 vt72/80/76 于 133,140 描文本。
// ------------------------------------------------------------
int /*thiscall*/ sub_458550(int *this, uint8_t uArg2)  // sub_458550 —— 开箱数量文本绘制
{
  int result; // eax
  int fld_e59; // eax
  int v5; // esi
  int fld_e592; // eax
  int fld_e593; // edi
  unsigned int v8; // eax
  int v9; // edi
  int v10; // edi

  result = *(this + 59);  // 读字段 result = this+59
  if ( result != 0 )  // result=this+236 动画同步参数 A
  {
    result = (*(this + 60) - result) / 40;  // this+240〔nSyncArgB〕
    if ( result != 0 )  // result=this+240 nSyncArgB
    {
      fld_e59 = *(this + 59);  // 读字段 fld_e59 = this+59
      if ( fld_e59 != 0 )  // fld_e59=this+236 动画同步参数 A
        fld_e59 = (*(this + 60) - fld_e59) / 40;  // this+240〔nSyncArgB〕
      v5 = 8 * (5 * fld_e59 - 5);
      fld_e592 = *(uint32_t *)(v5 + *(this + 59) + 8);  // this+236〔nSyncArgA〕
      if ( fld_e592 != 0 )  // fld_e592=this+236 nSyncArgA
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_e592 + 128))(  // 虚调用 vt+128（fld_e592）目标坐标y上界
          fld_e592,  // fld_e592=this+236 nSyncArgA
          105,
          133,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,
          1065353216,
          0,
          (uArg2 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 14);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
      fld_e593 = *(this + 59);  // 读字段 fld_e593 = this+59
      v8 = *(uint32_t *)(fld_e593 + v5 + 36);  // fld_e593=this+236 动画同步参数 A
      v9 = v5 + fld_e593;  // 计算 v9 = v5 + fld_e593
      if ( v8 < 0x10 )
        v10 = v9 + 16;  // 计算 v10 = v9 + 16
      else
        v10 = *(uint32_t *)(v9 + 16);  // 读字段 v10 = v9+16（nChannelTypeSel）
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        133,
        140,
        (uArg2 << 24) | 0xFFFFFF,
        v10);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
    }
  }
  return result;  // result=this+240 nSyncArgB
}



// ------------------------------------------------------------
// 0x458670 sub_458670 —— 开箱数量文本绘制（多行版）
// 同族 ·0x458550 多行版：i=177..301 步长 31 逐行绘制。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_458670(unsigned int *this, uint8_t uArg2)  // sub_458670 —— 开箱数量文本绘制（多行版）
{
  unsigned int result; // eax
  int v4; // ebx
  int i; // esi
  int fld_e63; // ecx
  int fld_e632; // eax
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // eax
  unsigned int v11; // [esp+8h] [ebp-4h]

  result = *(this + 63);  // 读字段 result = this+63
  v4 = 0;
  if ( result != 0 )  // result=this+252 参数灌入槽 2
  {
    result = (int)(*(this + 64) - result) / 40;  // this+256〔bQuad3〕
    if ( result != 0 )  // result=this+256 bQuad3
    {
      v11 = 0;
      for ( i = 177; ; i += 31 )
      {
        result = *(this + 63);  // 读字段 result = this+63
        if ( result == 0 )  // result=this+252 参数灌入槽 2
          break;
        result = (int)(*(this + 64) - result) / 40;  // this+256〔bQuad3〕
        if ( v11 >= result || i >= 301 )  // result=this+256 bQuad3
          break;
        fld_e63 = *(uint32_t *)(*(this + 63) + v4 + 8);  // this+252〔nQuad2〕
        if ( fld_e63 != 0 )  // fld_e63=this+252 nQuad2
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_e63 + 128))(  // 虚调用 vt+128（fld_e63）目标坐标y上界
            fld_e63,  // fld_e63=this+252 nQuad2
            105,
            i,
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            1065353216,
            1065353216,
            0,
            (uArg2 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        (*(void (/*thiscall*/ **)(int, unsigned int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 14);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
        fld_e632 = *(this + 63);  // 读字段 fld_e632 = this+63
        v8 = *(uint32_t *)(fld_e632 + v4 + 36);  // fld_e632=this+252 参数灌入槽 2
        v9 = v4 + fld_e632;  // 计算 v9 = v4 + fld_e632
        if ( v8 < 0x10 )
          v10 = v9 + 16;  // 计算 v10 = v9 + 16
        else
          v10 = *(uint32_t *)(v9 + 16);  // 读字段 v10 = v9+16（nChannelTypeSel）
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          133,
          i + 7,
          (uArg2 << 24) | 0xFFFFFF,
          v10);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
        ++v11;  // 计数自增 v11
        v4 += 40;
      }
    }
  }
  return result;  // result=this+256 bQuad3
}



// ------------------------------------------------------------
// 0x4587C0 sub_4587C0 —— 箱体高亮旋转绘制
// 控件 33（alpha = nArg2，>220 退化 -36）+ 控件 1（角度 clock_now×0.0000333、alpha 120）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4587C0(void *this, int nArg2)  // sub_4587C0 —— 箱体高亮旋转绘制
{
  uint8_t nArg22; // bl
  int pObj; // eax
  uint8_t nArg23; // bl
  int pObj2; // eax
  float pThis_A4; // [esp+14h] [ebp+8h]

  nArg22 = -36;
  if ( nArg2 <= 220 )
    nArg22 = nArg2;
  pObj = sub_418DD0(33);  // sub_418DD0 —— 资源句柄 (101)
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
      pObj,
      0,
      0,
      dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      1065353216,
      1065353216,
      0,
      (nArg22 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  pThis_A4 = (double)sub_699000((int)this + 164) * 0.000033333334;  // 【clock_now(clk)】
  sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
  nArg23 = 120;
  if ( nArg2 <= 120 )
    nArg23 = nArg2;
  pObj2 = sub_418DD0(1);  // sub_418DD0 —— 资源句柄 (101)
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, float, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚调用 vt+128（pObj2）目标坐标y上界
      pObj2,
      111,
      31,
      dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      1065353216,
      1065353216,
      COERCE_FLOAT(LODWORD(pThis_A4)),
      (nArg23 << 24) | 0xFFFFFF,
      1129447424,
      1129447424);
  return sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
}



// ------------------------------------------------------------
// 0x4588C0 sub_4588C0 —— 箱体绘制转发
// 控件 35（alpha nArg2，≥220 → -36）+ 458550 数量文本。
// ------------------------------------------------------------
int /*thiscall*/ sub_4588C0(int *this, int nArg2)  // sub_4588C0 —— 箱体绘制转发
{
  uint8_t nArg22; // bl
  int pObj; // eax

  nArg22 = nArg2;
  if ( nArg2 >= 220 )
    nArg22 = -36;
  pObj = sub_418DD0(35);  // sub_418DD0 —— 资源句柄 (101)
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
      pObj,
      0,
      0,
      dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      1065353216,
      1065353216,
      0,
      (nArg22 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  return sub_458550(this, nArg2);  // sub_458550 —— 开箱数量文本绘制
}



// ============================================================
// 【分区 8】奖励系统 II（0x458930-0x459ED0）
// REWARD_OPEN2（0x458930 自证）——二级奖励开启。
// ============================================================
// ------------------------------------------------------------
// 0x458930 sub_458930
// ------------------------------------------------------------
// 奖励箱二级开启 —— REWARD_OPEN2 自证（7308 行附近）
int /*userpurge*/ sub_458930@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<esi>, unsigned int pArg3, int nArg4, int nArg5)  // 实现：奖励箱二级开启 —— REWARD_OPEN2 自证（7308 行附近）
{
  int result; // eax
  uint32_t *pArg12; // ebx
  int v7; // edi
  uint32_t *v8; // esi
  int pObj; // ecx
  uint8_t *v10; // eax
  int v11; // ecx
  uint32_t *v12; // eax
  uint32_t *v13; // ecx
  const char *v14; // eax
  int v15; // esi
  int pObj3; // eax
  int v17; // ecx
  int pObj2; // eax
  int v19; // ebx
  int v20; // eax
  int v21; // esi
  int v22; // eax
  int v23; // [esp-8h] [ebp-A4h]
  int v26; // [esp+Ch] [ebp-90h]
  int v27; // [esp+Ch] [ebp-90h]
  int v28; // [esp+10h] [ebp-8Ch]
  uint32_t *v29; // [esp+10h] [ebp-8Ch]
  uint8_t v30; // [esp+14h] [ebp-88h]
  const char *psz; // [esp+14h] [ebp-88h]
  char Buffer[128]; // [esp+18h] [ebp-84h] BYREF
  int dword_796E502; // [esp+98h] [ebp-4h]
  uint8_t v34; // [esp+A4h] [ebp+8h]
  unsigned int nLen; // [esp+A8h] [ebp+Ch]
  int v36; // [esp+ACh] [ebp+10h]
  int v37; // [esp+ACh] [ebp+10h]

  result = dword_796E50;  // dword_796E50 —— 栈检 cookie
  pArg12 = pArg1;
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  if ( pArg1[1] == 8 )
  {
    result = pArg1[150];
    v30 = result;
  }
  else
  {
    v30 = -1;
  }
  v36 = nArg5 - 500;  // 计算 v36 = nArg5 - 500
  v7 = dword_6C6E00[pArg1[109]] + 158 * nArg4;
  if ( pArg3 < 4 )
  {
    result = pArg1[4 * pArg3 + 111];
    v8 = &pArg1[4 * pArg3];
    if ( result != 0 )
    {
      result = (v8[112] - result) / 52;
      if ( result != 0 )
      {
        if ( (uint8_t)sub_458160(pArg3) != 0 )  // sub_458160 —— 槽元素数大于一判定
        {
          pObj = *(uint32_t *)(v8[111] + 56);
          if ( pObj != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
              pObj,
              v7 + 64,
              180,
              dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
              1065353216,
              1065353216,
              0,
              (v30 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          v10 = (uint8_t *)v8[111];
          v11 = v10[90];
          BYTE1(v11) = v30;
          v28 = v10[88] | ((v10[89] | (v11 << 8)) << 8);
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg12 + 27);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
          v12 = (uint32_t *)v8[111];
          if ( v12[21] < 0x10u )
            v13 = v12 + 16;  // 计算 v13 = v12 + 16
          else
            v13 = (uint32_t *)v12[16];
          (*(void (/*cdecl*/ **)(int, unsigned int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            v7 - ((unsigned int)(5 * v12[20]) >> 1) + 78,
            217,
            v28,
            v13);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
        }
        v23 = *(uint32_t *)(v8[111] + 40);
        v14 = (const char *)sub_422E70(476);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
        sprintf(Buffer, v14, v23);  // 调 格式化到缓冲
        v29 = pArg12 + 27;  // 计算 v29 = pArg12 + 27
        (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg12 + 27, nArg2);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
        v15 = (v30 << 24) | 0xFFFFFF;
        (*(void (/*cdecl*/ **)(int, unsigned int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          v7 - ((5 * strlen(Buffer)) >> 1) + 78,  // 调 返回字符串长度（逐字节扫描）
          239,
          v15,
          Buffer);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
        v26 = (uint64_t)sub_4049C0(0.0, 255.0, v36, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        if ( pArg12[1] == 8 )
          LOBYTE(v26) = v30;
        if ( nArg4 == pArg12[135] )
          pObj3 = sub_418DD0(60);  // sub_418DD0 —— 资源句柄 (101)
        else
          pObj3 = sub_418DD0(61);  // sub_418DD0 —— 资源句柄 (101)
        if ( pObj3 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚调用 vt+128（pObj3）目标坐标y上界
            pObj3,
            v7 + 5,
            113,
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            1065353216,
            1065353216,
            0,
            ((uint8_t)v26 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        v17 = *(uint32_t *)(dword_8F850C + 4 * pArg3 + 16);  // dword_8F850C —— 队伍槽重置 4 槽 +188 解锁清空 → 自身
        v27 = v17;
        if ( v17 != 0 )
        {
          pObj2 = sub_42B340(v17);  // sub_42B340 —— 结果 = 虚拟角色惰性创建（0x294 字节）
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, int))(*(uint32_t *)pObj2 + 388))(  // 虚调用 vt+388（pObj2）攻击计算
            pObj2,
            v7 + 12,
            118,
            24,
            24,
            1065353216,
            v15);
          if ( *(uint32_t *)(v27 + 40) < 0x10u )
            psz = (const char *)(v27 + 20);
          else
            psz = *(const char **)(v27 + 20);
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v29);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
          (*(void (/*cdecl*/ **)(int, unsigned int, int, int, const char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            v7 - ((5 * strlen(psz)) >> 1) + 93,  // 调 返回字符串长度（逐字节扫描）
            126,
            v15,
            psz);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v29);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
          nLen = strlen((const char *)sub_422E70(477));  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
          v19 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          v20 = sub_422E70(478);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
          (*(void (/*cdecl*/ **)(int, unsigned int, int, int, int))(v19 + 80))(  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            v7 - ((5 * nLen) >> 1) + 93,
            126,
            v15,
            v20);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
          pArg12 = pArg1;
        }
        result = sub_458160(pArg3);  // sub_458160 —— 槽元素数大于一判定
        if ( (uint8_t)result != 0 )
        {
          v21 = v36;
          if ( v36 < 800 )
          {
            if ( *((uint8_t *)pArg12 + pArg3 + 504) == 0 )
            {
              sub_432EA0("REWARD_OPEN2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
              *((uint8_t *)pArg12 + pArg3 + 504) = 1;
            }
            v37 = sub_423A80(87, 93, v36, 500);  // sub_423A80 —— 同上 int 版（FTOL 截断）
            v34 = -1;
            if ( v21 > 500 )
              v34 = sub_423A80(255, 0, v21, 800);  // sub_423A80 —— 同上 int 版（FTOL 截断）
            sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
            v22 = sub_418DD0(v37);  // sub_418DD0 —— 资源句柄 (101)
            sub_43B560(v7 - 4, 112, v22, 1065353216, 1065353216, 0, (v34 << 24) | 0xFFFFFF, 1333788672, 1333788672);  // sub_43B560 —— 绘制转发（vt+128）
            return sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
          }
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x458E00 sub_458E00 —— 开箱阶段刷帧
// +109 箱循环：<250ms 控件 85 缩放；250-500ms 控件 41/42；≥500ms 控件 41 + 43/44 + 458930 二级开启；
// 另对悬停空箱（+146==-1）发包 op 74 单飞索取【推断：开箱内容拉取】。
// ------------------------------------------------------------
int /*thiscall*/ sub_458E00(uint32_t *this)  // sub_458E00 —— 开箱阶段刷帧
{
  int v2; // ebx
  uint32_t *pThis_7F; // edi
  int v4; // eax
  int fld_e150; // ebx
  int result; // eax
  int v7; // edi
  int pThis_29; // ebx
  int pObj; // eax
  int pObj2; // eax
  int pObj5; // eax
  int pObj3; // eax
  int pThis_4; // edx
  int pObj4; // eax
  bool fld_e109; // cc
  int v16; // [esp+Ch] [ebp-14h]
  float v17; // [esp+10h] [ebp-10h]
  float v18; // [esp+10h] [ebp-10h]
  unsigned int v19; // [esp+10h] [ebp-10h]
  unsigned int *pThis_7F2; // [esp+14h] [ebp-Ch]
  uint8_t fld_e1502; // [esp+18h] [ebp-8h]
  uint8_t v22[4]; // [esp+1Ch] [ebp-4h] BYREF

  v2 = 0;
  if ( (int)*(this + 109) > 0 )  // this+436〔nAtkTableVal(推断)〕
  {
    pThis_7F = this + 127;
    do
    {
      if ( *(this + 135) == -1 )
      {
        v4 = pThis_7F[4];
        if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) && *pThis_7F == -1 )
        {
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1216))(dword_8F7C04);  // 虚调用 vt+1216（dword_8F7C04 虚表槽）
          if ( *(this + 146) == -1 )
          {
            sub_423200(dword_8F7B08, 74);  // 【发送网络包API】
            v22[0] = v2;
            sub_423290(v22, 1);  // sub_423290 —— 写 4B 长度
            sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
            *(this + 146) = v2;  // 写字段 this+146 ← v2
          }
        }
      }
      ++v2;  // 计数自增 v2
      ++pThis_7F;  // 计数自增 pThis_7F
    }
    while ( v2 < *(this + 109) );  // this+436〔nAtkTableVal(推断)〕
  }
  if ( *(this + 1) == 8 )  // this+4〔宿主对象〕
  {
    fld_e150 = *(this + 150);  // 读字段 fld_e150 = this+150
    fld_e1502 = fld_e150;
    if ( fld_e150 < 200 )
      goto LABEL_13;
  }
  else
  {
    fld_e1502 = -1;
  }
  LOBYTE(fld_e150) = -56;
LABEL_13:
  result = sub_418DD0(34);  // sub_418DD0 —— 资源句柄 (101)
  v7 = 0;
  if ( result != 0 )
    result = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(  // 虚调用 vt+128（result）目标坐标y上界
               result,
               0,
               0,
               dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
               1065353216,
               1065353216,
               0,
               ((uint8_t)fld_e150 << 24) | 0xFFFFFF,
               1333788672,
               1333788672);
  v16 = 0;
  if ( (int)*(this + 109) > 0 )  // this+436〔nAtkTableVal(推断)〕
  {
    pThis_7F2 = this + 127;
    do
    {
      if ( *pThis_7F2 != -1 )
      {
        pThis_29 = sub_699000((int)(this + 41)) - pThis_7F2[9];  // 【clock_now(clk)】
        if ( pThis_29 >= 250 )
        {
          if ( pThis_29 >= 500 )
          {
            v19 = *pThis_7F2;
            pObj3 = sub_418DD0(41);  // sub_418DD0 —— 资源句柄 (101)
            if ( pObj3 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚调用 vt+128（pObj3）目标坐标y上界
                pObj3,
                v7 + dword_6C6E00[*(this + 109)],
                163,
                dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                1065353216,
                1065353216,
                0,
                (fld_e1502 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
            pThis_4 = *(this + 4 * v19 + 111);
            if ( pThis_4 != 0 && (unsigned int)((*(this + 4 * v19 + 112) - pThis_4) / 52) > 1 )
              pObj4 = sub_418DD0(43);  // sub_418DD0 —— 资源句柄 (101)
            else
              pObj4 = sub_418DD0(44);  // sub_418DD0 —— 资源句柄 (101)
            if ( pObj4 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(  // 虚调用 vt+128（pObj4）目标坐标y上界
                pObj4,
                v7 + dword_6C6E00[*(this + 109)],
                163,
                dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                1065353216,
                1065353216,
                0,
                (fld_e1502 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
            sub_458930(this, (int)this, v19, v16, pThis_29);  // 调 奖励箱二级开启 —— REWARD_OPEN2 自证（7308 行附近）
          }
          else
          {
            v18 = sub_4049C0(0.0, 1.0, pThis_29 - 250, 250);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            pObj2 = sub_418DD0(41);  // sub_418DD0 —— 资源句柄 (101)
            if ( pObj2 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, float, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 156))(  // 虚调用 vt+156（pObj2 虚表槽）
                pObj2,
                v7 + dword_6C6E00[*(this + 109)],
                163,
                dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                COERCE_FLOAT(LODWORD(v18)),
                1065353216,
                0,
                -1,
                1117257728,
                1333788672);
            pObj5 = sub_418DD0(42);  // sub_418DD0 —— 资源句柄 (101)
            if ( pObj5 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, float, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 156))(  // 虚调用 vt+156（pObj5 虚表槽）
                pObj5,
                v7 + dword_6C6E00[*(this + 109)],
                163,
                dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                COERCE_FLOAT(LODWORD(v18)),
                1065353216,
                0,
                -1,
                1117257728,
                1333788672);
          }
        }
        else
        {
          v17 = sub_4049C0(1.0, 0.0, pThis_29, 250);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          pObj = sub_418DD0(85);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, float, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 156))(  // 虚调用 vt+156（pObj 虚表槽）
              pObj,
              v7 + dword_6C6E00[*(this + 109)],
              163,
              dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
              COERCE_FLOAT(LODWORD(v17)),
              1065353216,
              0,
              -1,
              1117257728,
              1333788672);
        }
      }
      result = v16 + 1;
      v7 += 158;
      fld_e109 = ++v16 < *(this + 109);  // this+436〔nAtkTableVal(推断)〕
      ++pThis_7F2;  // 计数自增 pThis_7F2
    }
    while ( fld_e109 );  // fld_e109=this+436 nAtkTableVal
  }
  return result;
}


// ------------------------------------------------------------
// 0x459190 sub_459190 —— 结算遮罩网格绘制
// 从 dword_8F7A24+28 链定位 id 48026 对象【推断：奖励对话框】；45E490/45E4D0 折算坐标后
// 以 50px 瓦片铺 640×480，中心 500×500 挖空，叠控件 418DD0(pszArg2==0)。
// ------------------------------------------------------------
int /*thiscall*/ sub_459190(int *this, char pszArg2)  // sub_459190 —— 结算遮罩网格绘制
{
  int result; // eax
  int v4; // esi
  unsigned int i; // edi
  int v6; // ecx
  int v7; // ecx
  int pObj; // ecx
  int v9; // ecx
  int fld_e163; // edi
  int v11; // eax
  int v12; // ebx
  int fld_e1633; // edi
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int fld_e1634; // edi
  int v18; // eax
  int v19; // ebx
  int v20; // edi
  int v21; // esi
  int v22; // ebx
  int pObj2; // eax
  int v24; // [esp-14h] [ebp-28h]
  int v25; // [esp-14h] [ebp-28h]
  int v26; // [esp-10h] [ebp-24h]
  int v27; // [esp-10h] [ebp-24h]
  int fld_e1632; // [esp-Ch] [ebp-20h]
  int v29; // [esp+4h] [ebp-10h]
  int v31; // [esp+Ch] [ebp-8h]
  int v32; // [esp+10h] [ebp-4h]
  int v33; // [esp+10h] [ebp-4h]
  unsigned int v34; // [esp+1Ch] [ebp+8h]

  result = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  if ( result != 0 )
  {
    v4 = *(uint32_t *)(result + 104);  // 读字段 v4 = result+104（nTimerEnd）
    if ( v4 != 0 )
    {
      result = *(this + 163);  // 读字段 result = this+163
      if ( result == 0 )
      {
        for ( i = 0; ; ++i )
        {
          v6 = *(uint32_t *)(v4 + 120);  // 读字段 v6 = v4+120（pAnimObj）
          result = v6 != 0 ? (*(uint32_t *)(v4 + 124) - v6) >> 2 : 0;
          if ( (int)i >= result )
            break;
          v7 = *(uint32_t *)(v4 + 120);  // 读字段 v7 = v4+120（pAnimObj）
          if ( v7 != 0 && i < (*(uint32_t *)(v4 + 124) - v7) >> 2 )
            pObj = *(uint32_t *)(v7 + 4 * i);
          else
            pObj = 0;
          if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 48026 )  // 虚调用 vt+340（pObj 虚表槽）
          {
            v9 = *(uint32_t *)(v4 + 120);  // 读字段 v9 = v4+120（pAnimObj）
            if ( v9 != 0 && i < (*(uint32_t *)(v4 + 124) - v9) >> 2 )
              result = *(uint32_t *)(v9 + 4 * i);
            else
              result = 0;
            *(this + 163) = result;  // 写字段 this+163 ← result
            break;
          }
        }
      }
      fld_e163 = *(this + 163);  // 读字段 fld_e163 = this+163
      if ( fld_e163 != 0 )
      {
        fld_e1632 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)fld_e163 + 36))(*(this + 163)) + 8);  // 虚调用 vt+36（fld_e163 虚表槽）
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e163 + 120))(fld_e163);  // 虚调用 vt+120（fld_e163）转发(对象+缓冲)
        if ( pszArg2 != 0 )
        {
          v12 = sub_45E490(v11, fld_e1632);  // sub_45E490 —— 结果 = 屏幕 y → 演出层坐标（减基线）
          fld_e1633 = *(this + 163);  // 读字段 fld_e1633 = this+163
          v26 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1633 + 36))(fld_e1633) + 8);  // 虚调用 vt+36（fld_e1633 虚表槽）
          v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1633 + 128))(fld_e1633);  // 虚调用 vt+128（fld_e1633）目标坐标y上界
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1633 + 124))(fld_e1633);  // 虚调用 vt+124（fld_e1633）目标坐标y下界
          v15 = sub_45E4D0(v14, v24, v26, 0.0);  // sub_45E4D0 —— 结果 = 带比例的回换算（nArg2 - nArg3*f + 120）
        }
        else
        {
          v16 = sub_45E490(v11, fld_e1632);  // sub_45E490 —— 结果 = 屏幕 y → 演出层坐标（减基线）
          fld_e1634 = *(this + 163);  // 读字段 fld_e1634 = this+163
          v32 = v16;
          v27 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1634 + 36))(fld_e1634) + 8);  // 虚调用 vt+36（fld_e1634 虚表槽）
          v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1634 + 128))(fld_e1634);  // 虚调用 vt+128（fld_e1634）目标坐标y上界
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1634 + 124))(fld_e1634);  // 虚调用 vt+124（fld_e1634）目标坐标y下界
          v12 = v32;
          v15 = sub_45E4D0(v18, v25, v27, 1.0);  // sub_45E4D0 —— 结果 = 带比例的回换算（nArg2 - nArg3*f + 120）
        }
        v19 = v12 - 245;  // 计算 v19 = v12 - 245
        v20 = v15 - 345;  // 计算 v20 = v15 - 345
        v33 = v19;
        v31 = v20;
        result = sub_418DD0(pszArg2 == 0);  // sub_418DD0 —— 资源句柄 (101)
        if ( result != 0 )
          result = (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(  // 虚调用 vt+128（result）目标坐标y上界
                     result,
                     v19,
                     v20,
                     dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                     1065353216,
                     1065353216,
                     0,
                     1694498815,
                     1333788672,
                     1333788672);
        v34 = v19;
        if ( v19 > 0 )
        {
          result = 1374389535 * (v19 - 1);
          v34 = v19 - 50 * ((v19 - 1) / 0x32u + 1);
        }
        if ( v20 > 0 )
        {
          result = 1374389535 * (v20 - 1);
          v20 -= 50 * ((v20 - 1) / 0x32u + 1);
        }
        if ( v20 < 480 )
        {
          v21 = v34;
          result = v20;
          v29 = v20;
          do
          {
            if ( v21 < 640 )
            {
              v22 = v21;
              do
              {
                if ( v21 < v33 || v21 >= v33 + 500 || v20 < v31 || v20 >= v31 + 500 )  // 判定 v21 < v33 或 v21 >= v33 + 500 或 v20 < v31
                {
                  pObj2 = sub_418DD0(2);  // sub_418DD0 —— 资源句柄 (101)
                  if ( pObj2 != 0 )
                    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚调用 vt+128（pObj2）目标坐标y上界
                      pObj2,
                      v21,
                      v20,
                      dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
                      1065353216,
                      1065353216,
                      0,
                      1694498815,
                      1333788672,
                      1333788672);
                }
                v22 += 50;
                v21 = v22;
              }
              while ( v22 < 640 );  // 循环直到 v22 < 640
              result = v29;
              v21 = v34;
            }
            result += 50;
            v29 = result;
            v20 = result;
          }
          while ( result < 480 );  // 循环直到 result < 480
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x459440 sub_459440 —— 队伍条目拷贝构造
// 拷贝两前置字段 + 内嵌 string（4014D0）+ +9..+12 四字段。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_459440(uint32_t *this, uint32_t *pArg2)  // sub_459440 —— 队伍条目拷贝构造
{
  uint32_t *pThis_2; // ecx

  *this = *pArg2;
  *(this + 1) = pArg2[1];  // 写字段 this+1 ← pArg2[1]
  pThis_2 = this + 2;
  pThis_2[6] = 15;
  pThis_2[5] = 0;
  *((uint8_t *)pThis_2 + 4) = 0;  // 写字段 pThis_2+4（pHostObj）
  sub_4014D0((std::_String_base *)pThis_2, pArg2 + 2, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *(this + 9) = pArg2[9];  // 写字段 this+9 ← pArg2[9]
  *(this + 10) = pArg2[10];  // 写字段 this+10 ← pArg2[10]
  *(this + 11) = pArg2[11];  // 写字段 this+11 ← pArg2[11]
  *(this + 12) = pArg2[12];  // 写字段 this+12（nSkillRec12） ← pArg2[12]
  return this;
}



// ------------------------------------------------------------
// 0x4594A0 sub_4594A0 —— 52 字节元素区间倒序拷贝（插入右移腾位）
// 逐项复制 13 个 uint32（+8 std::string 随项拷贝），src/dst 同步回退，供向量插入时右移腾位【推断】。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4594A0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // sub_4594A0 —— 52 字节元素区间倒序拷贝（插入右移腾位）
{
  uint32_t *uArg22; // esi
  uint32_t *uArg32; // edi
  int v5; // eax

  uArg22 = uArg2;
  if ( uArg1 == uArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    v5 = *(uArg22 - 13);
    uArg22 -= 13;
    uArg32 -= 13;
    *uArg32 = v5;
    uArg32[1] = uArg22[1];  // uArg32[1] = 取 uArg22[1]
    sub_4014D0((std::_String_base *)(uArg32 + 2), uArg22 + 2, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    uArg32[9] = uArg22[9];  // uArg32[9] = 取 uArg22[9]
    uArg32[10] = uArg22[10];  // uArg32[10] = 取 uArg22[10]
    uArg32[11] = uArg22[11];  // uArg32[11] = 取 uArg22[11]
    uArg32[12] = uArg22[12];  // uArg32[12] = 取 uArg22[12]
  }
  while ( uArg22 != uArg1 );  // 循环直到 uArg22 != uArg1
  return uArg32;
}



// ------------------------------------------------------------
// 0x459500 sub_459500 —— 52 字节元素区间填充
// 以单条 pArg3 顺序覆盖 [uArg1, uArg2) 各 13 个 uint32（std::fill 同类），返回原 uArg2。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_459500(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)  // sub_459500 —— 52 字节元素区间填充
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 13 )
  {
    *i = *pArg3;
    i[1] = pArg3[1];  // i[1] = 取 pArg3[1]
    sub_4014D0((std::_String_base *)(i + 2), pArg3 + 2, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    i[9] = pArg3[9];  // i[9] = 取 pArg3[9]
    i[10] = pArg3[10];  // i[10] = 取 pArg3[10]
    result = uArg2;
    i[11] = pArg3[11];  // i[11] = 取 pArg3[11]
    i[12] = pArg3[12];  // i[12] = 取 pArg3[12]
  }
  return result;
}



// ------------------------------------------------------------
// 0x459560 sub_459560 —— 转发 ·sub_4594A0（52 字节右移拷贝）
// 52 字节条目向量插入右移路径的转发入口。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_459560(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // sub_459560 —— 转发 ·sub_4594A0（52 字节右移拷贝）
{
  return sub_4594A0(uArg1, uArg2, uArg3);  // sub_4594A0 —— 52 字节元素区间倒序拷贝（插入右移腾位）
}



// ------------------------------------------------------------
// 0x459580 sub_459580 —— 40 字节元素区间顺序拷贝
// 逐项复制 10 个 uint32（+12 std::string 随项拷贝），用于房间/名单条目向量的搬运。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_459580(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // sub_459580 —— 40 字节元素区间顺序拷贝
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
    uArg32[1] = uArg12[1];  // uArg32[1] = 取 uArg12[1]
    uArg32[2] = uArg12[2];  // uArg32[2] = 取 uArg12[2]
    sub_4014D0((std::_String_base *)(uArg32 + 3), uArg12 + 3, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    uArg12 += 10;
    uArg32 += 10;
  }
  while ( uArg12 != uArg2 );  // 循环直到 uArg12 != uArg2
  return uArg32;
}



// ------------------------------------------------------------
// 0x4595D0 sub_4595D0 —— 52 字节元素构造拷贝循环
// 把 [pArg1, uArg2) 逐项构造到 nArg3（+8 串、+32 容量 15），异常标记 v7 复用；返回 dst 末址。
// ------------------------------------------------------------
int /*cdecl*/ sub_4595D0(uint32_t *pArg1, uint32_t *uArg2, int nArg3)  // sub_4595D0 —— 52 字节元素构造拷贝循环
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( pArg1 != uArg2 )  // 循环直到 pArg1 != uArg2
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
    {
      *(uint32_t *)nArg32 = *pArg1;
      *(uint32_t *)(nArg32 + 4) = pArg1[1];  // 写字段 nArg32+4（pHostObj） ← pArg1[1]
      *(uint32_t *)(nArg32 + 32) = 15;  // 写字段 nArg32+32（nHeight） ← 15
      *(uint32_t *)(nArg32 + 28) = 0;  // 写字段 nArg32+28（pPanelVec） ← 0
      *(uint8_t *)(nArg32 + 12) = 0;  // 写字段 nArg32+12（nSkillRec12） ← 0
      sub_4014D0((std::_String_base *)(nArg32 + 8), pArg1 + 2, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      *(uint32_t *)(nArg32 + 36) = pArg1[9];  // 写字段 nArg32+36（nStateWord36） ← pArg1[9]
      *(uint32_t *)(nArg32 + 40) = pArg1[10];  // 写字段 nArg32+40（bStateSub40） ← pArg1[10]
      *(uint32_t *)(nArg32 + 44) = pArg1[11];  // 写字段 nArg32+44（nExpireMs） ← pArg1[11]
      *(uint32_t *)(nArg32 + 48) = pArg1[12];  // 写字段 nArg32+48（pCmdVecBegin48） ← pArg1[12]
    }
    nArg32 += 52;
    LOBYTE(v7) = 0;
    pArg1 += 13;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x459690 sub_459690 —— 单条 40 字节元素拷贝构造
// dst = 10 个 uint32（+12 std::string 重构造、+36 容量 15、+16 置 0），返回 dst。
// ------------------------------------------------------------
int /*cdecl*/ sub_459690(int pArg1, uint32_t *pArg2)  // sub_459690 —— 单条 40 字节元素拷贝构造
{
  int result; // eax

  result = pArg1;
  if ( pArg1 != 0 )
  {
    *(uint32_t *)pArg1 = *pArg2;
    *(uint32_t *)(pArg1 + 4) = pArg2[1];  // 写字段 pArg1+4（pHostObj） ← pArg2[1]
    *(uint32_t *)(pArg1 + 8) = pArg2[2];  // 写字段 pArg1+8（nSkillRec8） ← pArg2[2]
    *(uint32_t *)(pArg1 + 36) = 15;  // 写字段 pArg1+36（nStateWord36） ← 15
    *(uint32_t *)(pArg1 + 32) = 0;  // 写字段 pArg1+32（nHeight） ← 0
    *(uint8_t *)(pArg1 + 16) = 0;  // 写字段 pArg1+16（nChannelTypeSel） ← 0
    return sub_4014D0((std::_String_base *)(pArg1 + 12), pArg2 + 3, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  }
  return result;
}



// ------------------------------------------------------------
// 0x459700 sub_459700 —— 52 字节元素默认初始化
// +8 串置空（容量 15）、+36 = 0xFF000000、+0/+4 与 +40..+48 归零。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_459700(uint32_t *this)  // sub_459700 —— 52 字节元素默认初始化
{
  uint32_t *pThis_2; // ecx

  pThis_2 = this + 2;
  pThis_2[6] = 15;
  pThis_2[5] = 0;
  *((uint8_t *)pThis_2 + 4) = 0;  // 写字段 pThis_2+4（pHostObj）
  *this = 0;
  *(this + 1) = 0;  // 写字段 this+1 ← 0
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 10) = 0;  // 写字段 this+10 ← 0
  *(this + 11) = 0;  // 写字段 this+11 ← 0
  *(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  *(this + 9) = -16777216;  // 写字段 this+9 ← -16777216
  return this;
}



// ------------------------------------------------------------
// 0x459770 sub_459770 —— 转发 ·sub_459580（40 字节区间拷贝）
// 40 字节条目向量搬运的转发入口（·sub_45A1C0 原地路径调用）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_459770(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // sub_459770 —— 转发 ·sub_459580（40 字节区间拷贝）
{
  return sub_459580(uArg1, uArg2, uArg3);  // sub_459580 —— 40 字节元素区间顺序拷贝
}



// ------------------------------------------------------------
// 0x459790 sub_459790 —— 52 字节元素区间填充（重复同一源项）
// 以 pArg3 逐项构造 nArg2 份（dst 步进 52），返回末次拷贝的字段值。
// ------------------------------------------------------------
int /*cdecl*/ sub_459790(int nArg1, int nArg2, uint32_t *pArg3)  // sub_459790 —— 52 字节元素区间填充（重复同一源项）
{
  int nArg12; // esi
  int result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  nArg12 = nArg1;
  v5[5] = v5;
  v5[4] = nArg1;
  v6 = 0;
  while ( nArg2 != 0 )  // 循环直到 nArg2 != 0
  {
    v5[3] = nArg12;
    LOBYTE(v6) = 1;
    if ( nArg12 != 0 )
    {
      *(uint32_t *)nArg12 = *pArg3;
      *(uint32_t *)(nArg12 + 4) = pArg3[1];  // 写字段 nArg12+4（pHostObj） ← pArg3[1]
      *(uint32_t *)(nArg12 + 32) = 15;  // 写字段 nArg12+32（nHeight） ← 15
      *(uint32_t *)(nArg12 + 28) = 0;  // 写字段 nArg12+28（pPanelVec） ← 0
      *(uint8_t *)(nArg12 + 12) = 0;  // 写字段 nArg12+12（nSkillRec12） ← 0
      sub_4014D0((std::_String_base *)(nArg12 + 8), pArg3 + 2, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      *(uint32_t *)(nArg12 + 36) = pArg3[9];  // 写字段 nArg12+36（nStateWord36） ← pArg3[9]
      *(uint32_t *)(nArg12 + 40) = pArg3[10];  // 写字段 nArg12+40（bStateSub40） ← pArg3[10]
      *(uint32_t *)(nArg12 + 44) = pArg3[11];  // 写字段 nArg12+44（nExpireMs） ← pArg3[11]
      result = pArg3[12];
      *(uint32_t *)(nArg12 + 48) = result;  // 写字段 nArg12+48（pCmdVecBegin48） ← result
    }
    nArg12 += 52;
    LOBYTE(v6) = 0;
    --nArg2;  // 计数自减 nArg2
  }
  return result;
}



// ------------------------------------------------------------
// 0x459860 sub_459860 —— 40 字节元素区间拷贝循环
// 逐项经 ·sub_459690 构造（dst 步进 40），返回 dst 末址。
// ------------------------------------------------------------
int /*cdecl*/ sub_459860(uint32_t *uArg1, uint32_t *uArg2, int nArg3)  // sub_459860 —— 40 字节元素区间拷贝循环
{
  int nArg32; // edi
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v6[7] = 0;
  while ( uArg1 != uArg2 )  // 循环直到 uArg1 != uArg2
  {
    sub_459690(nArg32, uArg1);  // sub_459690 —— 单条 40 字节元素拷贝构造
    nArg32 += 40;
    uArg1 += 10;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x459910 sub_459910 —— 转发 ·sub_459790 并返回末项地址
// 填充 nArg2 项后回传 dst + 52*n，向量尾批量插入循环的包装。
// ------------------------------------------------------------
int /*stdcall*/ sub_459910(int nArg1, int nArg2, uint32_t *uArg3)  // sub_459910 —— 转发 ·sub_459790 并返回末项地址
{
  sub_459790(nArg1, nArg2, uArg3);  // sub_459790 —— 52 字节元素区间填充（重复同一源项）
  return nArg1 + 52 * nArg2;
}



// ------------------------------------------------------------
// 0x459940 sub_459940 —— 52 字节向量 insert_n（n 项插入 + 1.5 倍扩容）
// 先 ·sub_459440 复制样本值；容量不足按 1.5 倍增长重分配搬移（上限 82595524 项，超限 ·sub_44CAB0 抛长异常）；
// 三路分支分别为原地右移、补构造与整段搬迁，是奖励/名单条目向量的插入实现。
// ------------------------------------------------------------
int /*thiscall*/ sub_459940(int *this, int pArg2, unsigned int uArg3, int nArg4)  // sub_459940 —— 52 字节向量 insert_n（n 项插入 + 1.5 倍扩容）
{
  int pVecEnd_14; // ebx
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
  int fld_e12; // [esp-18h] [ebp-78h]
  int fld_e28; // [esp-10h] [ebp-70h]
  int fld_e25; // [esp-Ch] [ebp-6Ch]
  unsigned int fld_e24; // [esp-8h] [ebp-68h]
  int v24; // [esp+0h] [ebp-60h] BYREF
  void *Block; // [esp+Ch] [ebp-54h]
  int *pThis; // [esp+10h] [ebp-50h]
  char *pMem2; // [esp+14h] [ebp-4Ch]
  uint8_t v28[52]; // [esp+18h] [ebp-48h] BYREF
  int dword_796E502; // [esp+4Ch] [ebp-14h]
  int *v30; // [esp+50h] [ebp-10h]
  int v31; // [esp+5Ch] [ebp-4h]
  int v32; // [esp+68h] [ebp+8h]
  int v33; // [esp+6Ch] [ebp+Ch]
  int fld_e232; // [esp+70h] [ebp+10h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  v30 = &v24;
  pThis = this;
  sub_459440(nArg4);  // sub_459440 —— 队伍条目拷贝构造
  pVecEnd_14 = *(this + 1);  // 读字段 fld_e1 = this+1
  fld_e3 = 0;
  v31 = 0;
  if ( pVecEnd_14 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - pVecEnd_14) / 52;  // this+12〔nSkillRec12(推断)〕
  if ( uArg3 != 0 )
  {
    if ( pVecEnd_14 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - pVecEnd_14) / 52;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
    if ( 82595524 - fld_e2 < uArg3 )  // fld_e2=this+8 nSkillRec8
      sub_44CAB0(this);  // sub_44CAB0 —— vector 超长抛 std::length_error
    if ( pVecEnd_14 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - pVecEnd_14) / 52;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    if ( fld_e3 >= uArg3 + fld_e22 )  // fld_e3=this+12 nSkillRec12
    {
      fld_e23 = *(this + 2);  // 读字段 fld_e23 = this+2
      fld_e232 = fld_e23;  // fld_e23=this+8 物品 id
      if ( (fld_e23 - pArg2) / 52 >= uArg3 )  // fld_e23=this+8 物品 id
      {
        v32 = fld_e23 - 52 * uArg3;  // fld_e23=this+8 物品 id
        *(this + 2) = sub_4595D0(v32, fld_e23, fld_e23);  // sub_4595D0 —— 52 字节元素构造拷贝循环
        sub_459560(pArg2, v32, fld_e232);  // sub_459560 —— 转发 ·sub_4594A0（52 字节右移拷贝）
        sub_459500(pArg2, pArg2 + 52 * uArg3, v28);  // sub_459500 —— 52 字节元素区间填充
      }
      else
      {
        sub_4595D0(pArg2, fld_e23, pArg2 + 52 * uArg3);  // sub_4595D0 —— 52 字节元素构造拷贝循环
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 52;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        LOBYTE(v31) = 3;
        sub_459910(fld_e25, fld_e24, v28);  // sub_459910 —— 转发 ·sub_459790 并返回末项地址
        fld_e26 = 52 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        v31 = 0;
        sub_459500(pArg2, fld_e26 - 52 * uArg3, v28);  // sub_459500 —— 52 字节元素区间填充
      }
    }
    else
    {
      if ( 82595524 - (fld_e3 >> 1) >= fld_e3 )  // fld_e3=this+12 nSkillRec12
        v10 = (fld_e3 >> 1) + fld_e3;  // fld_e3=this+12 nSkillRec12
      else
        v10 = 0;
      if ( pVecEnd_14 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - pVecEnd_14) / 52;  // this+8〔nSkillRec8(推断)〕
      else
        fld_e27 = 0;  // fld_e27=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_e27 )  // fld_e27=this+8 nSkillRec8
        v10 = uArg3 + sub_458140(this);  // sub_458140 —— 52 字节元素计数
      v33 = 52 * v10;  // 计算 v33 = 52 * v10
      pMem = (char *)operator new(52 * v10);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v31) = 1;
      pMem2 = (char *)sub_4595D0(fld_e12, pArg2, pMem);  // sub_4595D0 —— 52 字节元素构造拷贝循环
      sub_459790(pMem2, uArg3, v28);  // sub_459790 —— 52 字节元素区间填充（重复同一源项）
      fld_e28 = *(this + 2);  // 读字段 fld_e28 = this+2
      pMem2 += 52 * uArg3;
      sub_4595D0(pArg2, fld_e28, pMem2);  // sub_4595D0 —— 52 字节元素构造拷贝循环
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      v31 = 0;
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 52;  // this+8〔nSkillRec8(推断)〕
      v14 = fld_e13 + uArg3;  // 计算 v14 = fld_e13 + uArg3
      fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
      if ( fld_e14 != 0 )  // fld_e14=this+4 宿主对象
      {
        sub_44C990(fld_e14, *(this + 2));  // sub_44C990 —— 52 字节记录数组析构遍历
        j__free((void *)*(this + 1));  // 释放堆块
      }
      *(this + 3) = (int)&pMem[v33];  // 写字段 this+3 ← (int)&pMem[v33]
      *(this + 2) = (int)&pMem[52 * v14];  // 写字段 this+2 ← (int)&pMem[52 * v14]
      *(this + 1) = (int)pMem;  // 写字段 this+1 ← (int)pMem
    }
  }
  v31 = -1;
  return sub_477AF0(v28);  // 调 后 j__free 基址并三指针清零
}


// ------------------------------------------------------------
// 0x459C40 sub_459C40 —— 40 字节元素尾删（pop_back）
// 末项先拷至 pArg3 再销毁区间，end -= 40，返回 pArg3（奖励图标退场队列用）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_459C40(char **this, uint32_t *uArg2, uint32_t *pArg3)  // sub_459C40 —— 40 字节元素尾删（pop_back）
{
  char *fld_e2; // edi
  char *v5; // esi

  sub_459580(pArg3 + 10, *(this + 2), pArg3);  // sub_459580 —— 40 字节元素区间顺序拷贝
  fld_e2 = *(this + 2);  // 读字段 fld_e2 = this+2
  v5 = fld_e2 - 40;  // 计算 v5 = fld_e2 - 40
  do
  {
    sub_5014C0(v5);  // sub_5014C0 —— 调 sub_5014C0
    v5 += 40;
  }
  while ( v5 != fld_e2 );  // 循环直到 v5 != fld_e2
  *(this + 2) -= 40;  // this+8〔nSkillRec8(推断)〕
  *uArg2 = pArg3;
  return uArg2;
}



// ------------------------------------------------------------
// 0x459CA0 sub_459CA0 —— 52 字节向量指定位置插入一项
// 转发 ·sub_459940（n = 1）后按页内下标换算返回新项地址。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_459CA0(int *this, uint32_t *uArg2, char *pszArg3, uint32_t *uArg4)  // sub_459CA0 —— 52 字节向量指定位置插入一项
{
  int pVecEnd_7; // esi
  int v6; // esi

  pVecEnd_7 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( pVecEnd_7 != 0 && (*(this + 2) - pVecEnd_7) / 52 != 0 )  // pVecEnd_7=this+4 宿主对象
    v6 = (int)&pszArg3[-pVecEnd_7] / 52;  // pVecEnd_7=this+4 宿主对象
  else
    v6 = 0;
  sub_459940(this, pszArg3, 1u, uArg4);  // sub_459940 —— 52 字节向量 insert_n（n 项插入 + 1.5 倍扩容）
  *uArg2 = *(this + 1) + 52 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x459D10 sub_459D10 —— 转发 ·sub_459860（40 字节区间拷贝）
// 40 字节条目区间批拷贝的转发入口（重分配路径调用）。
// ------------------------------------------------------------
int /*stdcall*/ sub_459D10(uint32_t *uArg1, uint32_t *uArg2, int nArg3)  // sub_459D10 —— 转发 ·sub_459860（40 字节区间拷贝）
{
  return sub_459860(uArg1, uArg2, nArg3);  // sub_459860 —— 40 字节元素区间拷贝循环
}



// ------------------------------------------------------------
// 0x459D30 sub_459D30 —— CNRDReward 状态重置（整窗复原）
// 清 +192 起字段、信息窗文本(+232/+248 ·sub_55A050)、4 组 52 字节子向量(+444)与按钮可见位，
// 时钟(+164)归零、主控件(+44)收回 640x480，置 +584/+604 = -1、+600 = 255、+660 = 0。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_459D30(int this)  // sub_459D30 —— CNRDReward 状态重置（整窗复原）
{
  uint32_t *pThis_C0; // ecx
  int v3; // eax
  void **pThis_1BC; // edi
  char *v5; // ebx
  uint32_t *pThis_220; // eax
  int j; // ecx
  int *pThis_24C; // eax
  int k; // ecx
  int v10; // edi
  uint32_t *fld_2C; // ecx
  uint32_t *result; // eax
  int fld_2C2; // esi
  char *i; // [esp+8h] [ebp-Ch]
  uint32_t *pThis_1FC; // [esp+Ch] [ebp-8h]
  int v16; // [esp+10h] [ebp-4h]

  pThis_C0 = (uint32_t *)(this + 192);  // this+192〔nDlgId(推断)〕
  *pThis_C0 = 0;  // pThis_C0=this+192 nDlgId
  pThis_C0[1] = 0;  // pThis_C0=this+192 nDlgId
  pThis_C0[2] = 0;  // pThis_C0=this+192 nDlgId
  pThis_C0[3] = 0;  // pThis_C0=this+192 nDlgId
  pThis_C0[4] = 0;  // pThis_C0=this+192 nDlgId
  pThis_C0[5] = 0;  // pThis_C0=this+192 nDlgId
  pThis_C0[6] = 0;  // pThis_C0=this+192 nDlgId
  pThis_C0[7] = 0;  // pThis_C0=this+192 nDlgId
  pThis_C0[8] = 0;  // pThis_C0=this+192 nDlgId
  pThis_C0[9] = 0;  // pThis_C0=this+192 nDlgId
  sub_55A050(this + 248);  // sub_55A050 —— 结果 = 信息窗文本 2（5014C0）
  sub_55A050(this + 232);  // sub_55A050 —— 结果 = 信息窗文本 2（5014C0）
  v3 = 0;
  *(uint32_t *)(this + 264) = 0;  // 写字段 this+264（nAnimHandle） ← 0
  *(uint8_t *)(this + 432) = 0;  // 写字段 this+432 ← 0
  memset((void *)(this + 268), 0, 0x2Cu);  // 调 内存按字节填充
  memset((void *)(this + 312), 0, 0x78u);  // 调 内存按字节填充
  *(uint32_t *)(this + 436) = 0;  // 写字段 this+436（nAtkTableVal） ← 0
  v16 = 0;
  pThis_1FC = (uint32_t *)(this + 508);  // this+508〔uPetFlag(推断)〕
  pThis_1BC = (void **)(this + 444);
  do
  {
    v5 = (char *)*pThis_1BC;
    if ( *pThis_1BC != nullptr )
    {
      for ( i = (char *)pThis_1BC[1]; v5 != i; v5 += 52 )
        sub_477AF0(v5);  // 调 后 j__free 基址并三指针清零
      j__free(*pThis_1BC);  // 释放堆块
      v3 = v16;
    }
    *pThis_1BC = nullptr;
    pThis_1BC[1] = nullptr;
    pThis_1BC[2] = nullptr;
    *pThis_1FC = -1;  // pThis_1FC=this+508 uPetFlag
    *(uint8_t *)(this + v3++ + 504) = 0;
    pThis_1BC += 4;
    v16 = v3;
    ++pThis_1FC;  // 计数自增 pThis_1FC
  }
  while ( v3 < 4 );  // 循环直到 v3 < 4
  *(uint32_t *)(this + 540) = -1;  // 写字段 this+540 ← -1
  *(uint32_t *)(this + 560) = 0;  // 写字段 this+560 ← 0
  pThis_220 = (uint32_t *)(this + 544);  // this+544〔nFaction〕
  for ( j = 4; j != 0; --j )  // 遍历计次循环（j != 0）
  {
    *(uint8_t *)(*(pThis_220 - 5) + 16) = 0;  // pThis_220=this+544 nFaction
    *pThis_220 = 0;  // pThis_220=this+544 nFaction
    pThis_220[5] = 1;  // pThis_220=this+544 nFaction
    ++pThis_220;  // 计数自增 pThis_220
  }
  pThis_24C = (int *)(this + 588);
  for ( k = 3; k != 0; --k )  // 遍历计次循环（k != 0）
  {
    v10 = *pThis_24C++;
    *(uint8_t *)(v10 + 16) = 0;  // 写字段 v10+16（nChannelTypeSel） ← 0
  }
  *(uint8_t *)(this + 177) = 0;  // 写字段 this+177 ← 0
  *(uint8_t *)(this + 178) = 0;  // 写字段 this+178 ← 0
  sub_698F90(this + 164, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  fld_2C = *(uint32_t **)(this + 44);  // this+176〔pAppendVecCap(推断)〕
  *(uint32_t *)(this + 584) = -1;  // 写字段 this+584 ← -1
  *(uint32_t *)(this + 604) = -1;  // 写字段 this+604 ← -1
  *(uint8_t *)(this + 580) = 0;  // 写字段 this+580（uOffset580） ← 0
  *(uint32_t *)(this + 600) = 255;  // 写字段 this+600 ← 255
  *(uint32_t *)(this + 608) = 0;  // 写字段 this+608（nAttackGate） ← 0
  *(uint32_t *)(this + 652) = 0;  // 写字段 this+652 ← 0
  *(uint8_t *)(this + 660) = 0;  // 写字段 this+660 ← 0
  result = sub_69A5F0(fld_2C, 0, 0);  // 调 设位、sub_69A840 登记
  fld_2C2 = *(uint32_t *)(this + 44);  // 读字段 fld_2C2 = this+44（nExpireMs）
  *(uint32_t *)(fld_2C2 + 28) = 640;  // 写字段 fld_2C2+28（pPanelVec） ← 640
  *(uint32_t *)(fld_2C2 + 32) = 480;  // 写字段 fld_2C2+32（nHeight） ← 480
  return result;
}



// ============================================================
// 【分区 9】奖励系统 III（0x459ED0-0x45AC20）
// 奖励箱点亮动画 0x459ED0（REWARD_BOX_SET / REWARD_ICON_OFF 自证，
// 4 箱 × sub_4049F0 500ms 插值）。
// ============================================================
// ------------------------------------------------------------
// 0x459ED0 sub_459ED0
// ------------------------------------------------------------
// 奖励箱点亮动画 —— REWARD_BOX_SET / REWARD_ICON_OFF 自证：
// +252 表（40 字节/项）前 4 箱按 +8 时钟差插值（sub_4049F0 0→30 / 500ms）；
// +264<11 且 +432 未置位时记时刻并 REWARD_BOX_SET
unsigned int /*usercall*/ sub_459ED0@<eax>(int pArg1@<ecx>, double fArg2@<st0>)  // 实现：+264<11 且 +432 未置位时记时刻并 REWARD_BOX_SET
{
  unsigned int result; // eax
  int v4; // ebx
  int v5; // eax
  int v6; // esi
  int v7; // ebx
  int pObj2; // ecx
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // eax
  int pObj; // eax
  unsigned int v14; // [esp+4h] [ebp-10h] BYREF
  int v15; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]
  int v17; // [esp+10h] [ebp-4h]

  result = *(uint32_t *)(pArg1 + 252);  // 读字段 result = pArg1+252（nParamSlotB）
  if ( result != 0 )
  {
    result = (int)(*(uint32_t *)(pArg1 + 256) - result) / 40;  // pArg1+256〔bParamSlotC(推断)〕
    v14 = result;
    if ( result != 0 )
    {
      v4 = 0;
      v17 = sub_699000(pArg1 + 8) - *(uint32_t *)(pArg1 + 560);  // 【clock_now(clk)】
      for ( i = 0; ; v4 = i )
      {
        result = *(uint32_t *)(pArg1 + 252);  // 读字段 result = pArg1+252（nParamSlotB）
        if ( result == 0 )
          break;
        result = (int)(*(uint32_t *)(pArg1 + 256) - result) / 40;  // pArg1+256〔bParamSlotC(推断)〕
        if ( v4 >= result || v4 >= 4 )
          break;
        v5 = v17;
        v6 = 31 * v4 + 177;
        v15 = 255;
        v14 = 0;
        if ( v17 >= 0 )
        {
          if ( *(int *)(pArg1 + 264) < 11 && *(uint8_t *)(pArg1 + 432) == 0 )  // pArg1+264〔nAnimHandle(推断)〕
          {
            *(uint32_t *)(pArg1 + 4 * (*(uint32_t *)(pArg1 + 264))++ + 268) = sub_699000(pArg1 + 8);  // sub_699000 —— 【clock_now(clk)】
            sub_432EA0("REWARD_BOX_SET", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
            v5 = v17;
            *(uint8_t *)(pArg1 + 432) = 1;  // 写字段 pArg1+432 ← 1
          }
          if ( v4 != 0 )
          {
            sub_4049F0(0.0, 30.0, v5, 500, 1);  // sub_4049F0 —— 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
            v6 -= (uint64_t)fArg2;
          }
          else
          {
            v14 = (uint64_t)sub_4049C0(0.0, 150.0, v5, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            fArg2 = sub_4049C0(255.0, 30.0, v17, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            v15 = (uint64_t)fArg2;
          }
        }
        v7 = 40 * v4;  // 计算 v7 = 40 * v4
        pObj2 = *(uint32_t *)(*(uint32_t *)(pArg1 + 252) + v7 + 8);  // pArg1+252〔nQuad2〕
        if ( pObj2 != 0 )
          (*(void (/*thiscall*/ **)(int, unsigned int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚调用 vt+128（pObj2）目标坐标y上界
            pObj2,
            v14 + 105,
            v6,
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            1065353216,
            1065353216,
            0,
            ((uint8_t)v15 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 56);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
        v9 = *(uint32_t *)(pArg1 + 252);  // 读字段 v9 = pArg1+252（nParamSlotB）
        v10 = *(uint32_t *)(v9 + v7 + 36);
        v11 = v7 + v9;  // 计算 v11 = v7 + v9
        if ( v10 < 0x10 )
          v12 = v11 + 16;  // 计算 v12 = v11 + 16
        else
          v12 = *(uint32_t *)(v11 + 16);  // 读字段 v12 = v11+16（nChannelTypeSel）
        (*(void (/*cdecl*/ **)(int, unsigned int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          v14 + 133,
          v6 + 7,
          ((uint8_t)v15 << 24) | 0xFFFFFF,
          v12);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
        if ( v17 < 0 && i == 0 )
        {
          fArg2 = sub_4049C0(50.0, 53.0, v17 + 125, 125);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
          pObj = sub_418DD0((uint64_t)fArg2);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
              pObj,
              0,
              0,
              dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
              1065353216,
              1065353216,
              0,
              -587202561,
              1333788672,
              1333788672);
          sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
        }
        ++i;  // 计数自增 i
      }
      if ( v17 >= 500 )
      {
        sub_459C40(&v14, *(uint32_t *)(pArg1 + 252));  // sub_459C40 —— 40 字节元素尾删（pop_back）
        *(uint32_t *)(pArg1 + 560) = sub_699000(pArg1 + 8) + 125;  // sub_699000 —— 【clock_now(clk)】
        *(uint8_t *)(pArg1 + 432) = 0;  // 写字段 pArg1+432 ← 0
        return (unsigned int)sub_432EA0("REWARD_ICON_OFF", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x45A1C0 sub_45A1C0 —— 40 字节向量赋值（this = pArg2）
// 容量足则原地拷贝（·sub_459770/459860），超容量经 ·sub_434AE0 预留重分配；
// 旧区间经 ·sub_55A010 析构，空源则转 ·sub_55A050 清空。
// ------------------------------------------------------------
int /*thiscall*/ sub_45A1C0(int this, int pArg2)  // sub_45A1C0 —— 40 字节向量赋值（this = pArg2）
{
  int v4; // eax
  unsigned int v5; // ecx
  uint32_t *pVecEnd_12; // edi
  unsigned int fld_8; // eax
  uint32_t *v9; // eax
  int v10; // eax
  int fld_42; // ecx
  unsigned int fld_C; // eax
  unsigned int v13; // eax
  uint32_t *v14; // [esp+10h] [ebp+8h]

  if ( this == pArg2 )
    return this;
  v4 = *(uint32_t *)(pArg2 + 4);  // 读字段 v4 = pArg2+4（pHostObj）
  if ( v4 == 0 || (v5 = (*(uint32_t *)(pArg2 + 8) - v4) / 40) == 0 )
  {
    sub_55A050(this);  // sub_55A050 —— 结果 = 信息窗文本 2（5014C0）
    return this;
  }
  pVecEnd_12 = *(uint32_t **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  if ( pVecEnd_12 != nullptr )  // fld_4=this+16 nChannelTypeSel
    fld_8 = (*(uint32_t *)(this + 8) - (int)pVecEnd_12) / 40;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( v5 > fld_8 )  // fld_8=this+8 nSkillRec8
  {
    if ( pVecEnd_12 != nullptr )  // fld_4=this+16 nChannelTypeSel
      fld_C = (*(uint32_t *)(this + 12) - (int)pVecEnd_12) / 40;  // this+12〔nSkillRec12(推断)〕等 2 字段
    else
      fld_C = 0;  // fld_C=this+12 nSkillRec12
    if ( v5 <= fld_C )  // fld_C=this+12 nSkillRec12
    {
      v14 = (uint32_t *)(*(uint32_t *)(pArg2 + 4) + 40 * sub_5721D0(this));  // sub_5721D0 —— 物品信息窗小辅助（15 行）
      sub_459770(*(uint32_t **)(pArg2 + 4), v14, pVecEnd_12);  // sub_459770 —— 转发 ·sub_459580（40 字节区间拷贝）
      *(uint32_t *)(this + 8) = sub_459860(v14, *(uint32_t **)(pArg2 + 8), *(uint32_t *)(this + 8));  // sub_459860 —— 40 字节元素区间拷贝循环
      return this;
    }
    if ( pVecEnd_12 != nullptr )  // fld_4=this+16 nChannelTypeSel
    {
      sub_55A010(pVecEnd_12, *(uint32_t *)(this + 8));  // sub_55A010 —— 信息窗文本（5014C0）
      j__free(*(void **)(this + 4));  // 释放堆块
    }
    v13 = sub_5721D0(pArg2);  // sub_5721D0 —— 物品信息窗小辅助（15 行）
    if ( sub_434AE0((uint32_t *)this, v13) != 0 )  // sub_434AE0 —— 40 字节元素向量预留
      *(uint32_t *)(this + 8) = sub_459D10(*(uint32_t **)(pArg2 + 4), *(uint32_t **)(pArg2 + 8), *(uint32_t *)(this + 4));  // sub_459D10 —— 转发 ·sub_459860（40 字节区间拷贝）
    return this;
  }
  v9 = sub_459580(*(uint32_t **)(pArg2 + 4), *(uint32_t **)(pArg2 + 8), pVecEnd_12);  // sub_459580 —— 40 字节元素区间顺序拷贝
  sub_55A010(v9, *(uint32_t *)(this + 8));  // sub_55A010 —— 信息窗文本（5014C0）
  v10 = *(uint32_t *)(pArg2 + 4);  // 读字段 v10 = pArg2+4（pHostObj）
  if ( v10 != 0 )
    fld_42 = *(uint32_t *)(this + 4) + 40 * ((*(uint32_t *)(pArg2 + 8) - v10) / 40);  // this+4〔宿主对象〕等 2 字段
  else
    fld_42 = *(uint32_t *)(this + 4);  // 读字段 fld_42 = this+4（pHostObj）
  *(uint32_t *)(this + 8) = fld_42;  // 写字段 this+8（nSkillRec8） ← fld_42
  return this;
}



// ------------------------------------------------------------
// 0x45A340 sub_45A340 —— 52 字节向量尾插
// 未满在 end 处构造（·sub_459790）并 end += 52；满则转 ·sub_459CA0 插入路径。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45A340(int this, uint32_t *uArg2)  // sub_45A340 —— 52 字节向量尾插
{
  int pVecEnd_7; // edi
  unsigned int fld_8; // ecx
  int fld_82; // edi
  uint32_t *result; // eax

  pVecEnd_7 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( pVecEnd_7 != 0 )  // fld_4=this+4 pHostObj
    fld_8 = (*(uint32_t *)(this + 8) - pVecEnd_7) / 52;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( pVecEnd_7 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - pVecEnd_7) / 52 )  // this+12 物品类型号
    return sub_459CA0((int *)this, &uArg2, *(char **)(this + 8), uArg2);  // sub_459CA0 —— 52 字节向量指定位置插入一项
  fld_82 = *(uint32_t *)(this + 8);  // 读字段 fld_82 = this+8（nSkillRec8）
  result = (uint32_t *)sub_459790(fld_82, 1, uArg2);  // sub_459790 —— 52 字节元素区间填充（重复同一源项）
  *(uint32_t *)(this + 8) = fld_82 + 52;  // 写字段 this+8（nSkillRec8） ← fld_82 + 52
  return result;
}



// ------------------------------------------------------------
// 0x45A3D0 sub_45A3D0 —— 状态 2 装载：两张 40 字节条目表复制入 +232/+248
// 源为 ·+160 处对象 +1008/+1024 两表（奖励划分/持有条目）【推断】；
// 并置 +640 = 3、+644/+648 = -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_45A3D0(uint32_t *this)  // sub_45A3D0 —— 状态 2 装载：两张 40 字节条目表复制入 +232/+248
{
  sub_45A1C0((int)(this + 62), *(this + 40) + 1024);  // sub_45A1C0 —— 40 字节向量赋值（this = pArg2）
  sub_45A1C0((int)(this + 58), *(this + 40) + 1008);  // sub_45A1C0 —— 40 字节向量赋值（this = pArg2）
  *(this + 160) = 3;  // 写字段 this+160（fAdd160） ← 3
  *(this + 161) = -1;  // 写字段 this+161 ← -1
  *(this + 162) = -1;  // 写字段 this+162（bSubFlags648） ← -1
  return -1;
}



// ------------------------------------------------------------
// 0x45A420 sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
// 登记进入时刻(+192+4n)并复位时钟后按状态分发：0 全清(·sub_459D30)、1 隐主控件、2 装载划分(·sub_45A3D0)并显示、
// 7 隐四按钮(+524..+536)、9 亮三按钮(+588..+596) 并按 380x76 与 ·unk_6C6E14 坐标表排布、
// 8 遍历 ·dword_8F850C 四玩家槽定位本机对象，镜头横向位夹取 [200, 内部宽-200] 后下发 ·sub_4E4A50 子命令 48026。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45A420(int this, int nArg2)  // sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
{
  uint32_t *result; // eax
  int dword_8F850C2; // ecx
  int v5; // esi
  int v6; // ebx
  int dword_8F850C22; // edi
  int v8; // eax
  int pObj; // esi
  int v10; // edi
  int v11; // esi
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  int v17; // edi
  int v18; // edi
  uint32_t **pThis_24C; // edi
  int fld_24C; // eax
  uint32_t *v21; // ebx
  int v22; // eax
  int fld_2C; // esi
  int *v24; // esi
  int v25; // [esp+14h] [ebp+8h]

  *(uint32_t *)(this + 4) = nArg2;  // 写字段 this+4（pHostObj） ← nArg2
  *(uint32_t *)(this + 4 * *(uint32_t *)(this + 4) + 192) = sub_699000(this + 164);  // sub_699000 —— 【clock_now(clk)】
  *(uint8_t *)(this + 21) = 0;  // 写字段 this+21（bArmorState） ← 0
  *(uint8_t *)(this + 22) = 0;  // 写字段 this+22 ← 0
  sub_698F90(this + 8, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  result = *(uint32_t **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  switch ( (unsigned int)result )  // 按 (unsigned int)result 分派
  {
    case 0u:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = (uint32_t *)sub_459D30(this);  // sub_459D30 —— CNRDReward 状态重置（整窗复原）
      *(uint8_t *)(*(uint32_t *)(this + 44) + 16) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
      return result;  // result=this+16 nChannelTypeSel
    case 1u:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = *(uint32_t **)(this + 44);  // this+176〔pAppendVecCap(推断)〕
      *((uint8_t *)result + 16) = 0;  // 写字段 result+16（nChannelTypeSel）
      return result;  // result=this+176 pAppendVecCap
    case 2u:  // case 2 = ENUM_CMDPACKET_LOGIN
      result = (uint32_t *)sub_45A3D0(this);  // sub_45A3D0 —— 状态 2 装载：两张 40 字节条目表复制入 +232/+248
      goto LABEL_5;
    case 7u:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      *(uint8_t *)(*(uint32_t *)(this + 524) + 16) = 0;  // this+524〔fAbilityScale(推断)〕
      result = *(uint32_t **)(this + 528);
      *((uint8_t *)result + 16) = 0;  // 写字段 result+16（nChannelTypeSel）
      *(uint8_t *)(*(uint32_t *)(this + 532) + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(this + 536) + 16) = 0;  // this+536〔nCountdownEnd〕
      return result;
    case 8u:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      dword_8F850C2 = dword_8F850C;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
      v25 = 0;
      v5 = 16;
      break;
    case 9u:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      pThis_24C = (uint32_t **)(this + 588);
      *(uint8_t *)(*(uint32_t *)(this + 588) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(this + 592) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(this + 596) + 16) = 1;
      fld_24C = *(uint32_t *)(this + 588);  // 读字段 fld_24C = this+588
      if ( *(uint8_t *)(this + 660) != 0 )
      {
        *(uint8_t *)(fld_24C + 17) = 1;  // 写字段 fld_24C+17（bEnable） ← 1
        *(uint8_t *)(*(uint32_t *)(this + 592) + 17) = 1;
      }
      else
      {
        *(uint8_t *)(fld_24C + 17) = 0;  // 写字段 fld_24C+17（bEnable） ← 0
        *(uint8_t *)(*(uint32_t *)(this + 592) + 17) = 0;
        v21 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
        v22 = sub_422E70(475);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
        sub_43BEE0(v21, v22, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
      }
      *(uint8_t *)(this + 625) = 0;  // 写字段 this+625 ← 0
      *(uint8_t *)(this + 626) = 0;  // 写字段 this+626 ← 0
      sub_698F90(this + 612, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      sub_69A5F0(*(uint32_t **)(this + 44), 380, 76);  // 调 设位、sub_69A840 登记
      fld_2C = *(uint32_t *)(this + 44);  // 读字段 fld_2C = this+44（nExpireMs）
      *(uint32_t *)(fld_2C + 28) = 230;  // 写字段 fld_2C+28（pPanelVec） ← 230
      *(uint32_t *)(fld_2C + 32) = 95;  // 写字段 fld_2C+32（nHeight） ← 95
      v24 = (int *)&unk_6C6E14;
      do
      {
        result = sub_69A5F0(*pThis_24C, *v24, v24[1]);  // 调 设位、sub_69A840 登记
        v24 += 2;
        ++pThis_24C;  // 计数自增 pThis_24C
      }
      while ( (int)v24 < (int)&unk_6C6E2C );
      return result;
    default:
LABEL_5:
      *(uint8_t *)(*(uint32_t *)(this + 44) + 16) = 1;  // this+44〔nExpireMs(推断)〕等 2 字段
      return result;
  }
  while ( 1 )
  {
    v6 = *(uint32_t *)(v5 + dword_8F850C2);  // dword_8F850C2 —— [esp+20h] [ebp+10h]
    if ( v6 != 0 )
      break;
LABEL_16:
    v5 += 4;
    ++v25;  // 计数自增 v25
    if ( v5 >= 32 )
      goto LABEL_19;
  }
  dword_8F850C22 = dword_8F850C2;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
  if ( sub_456480(dword_8F850C2) == -1 )  // sub_456480 —— 存 座位号
    v8 = 0;
  else
    v8 = *(uint32_t *)(dword_8F850C22 + 4 * sub_456480(dword_8F850C22) + 16);  // sub_456480 —— 存 座位号
  if ( v6 != v8
    || (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(uint32_t *)(v5 + dword_8F850C) + 196) + 80))(*(uint32_t *)(*(uint32_t *)(v5 + dword_8F850C) + 196)) == 0 )  // dword_8F850C —— 队伍槽重置 4 槽 +188 解锁清空 → 自身
  {
    dword_8F850C2 = dword_8F850C;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
    goto LABEL_16;
  }
  dword_8F850C2 = dword_8F850C;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
  pObj = *(uint32_t *)(*(uint32_t *)(dword_8F850C + 4 * v25 + 16) + 196);  // dword_8F850C —— 队伍槽重置 4 槽 +188 解锁清空 → 自身
  if ( pObj != 0 )
  {
LABEL_26:
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 80))(pObj);  // 虚调用 vt+80（pObj）读 4 字节
    if ( result != nullptr )
    {
      v12 = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 80))(pObj) + 132) + 44);  // 虚调用 vt+80（pObj）读 4 字节
      v13 = *(uint32_t *)(v12 + 364);  // 读字段 v13 = v12+364（pAnimNameStr）
      v14 = v12 + 360;  // 计算 v14 = v12 + 360
      if ( v13 != 0 )
        v15 = (*(uint32_t *)(v14 + 8) - v13) >> 5;
      else
        v15 = 0;
      v16 = 224 * v15;  // 计算 v16 = 224 * v15
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 虚调用 vt+120（pObj）转发(对象+缓冲)
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 152))(pObj) == 1 )  // 虚调用 vt+152（pObj）取值(参数)
        v18 = v17 + 80;  // 计算 v18 = v17 + 80
      else
        v18 = v17 - 80;  // 计算 v18 = v17 - 80
      if ( v18 > 200 )
      {
        if ( v18 >= v16 - 200 )
          v18 = v16 - 200;  // 计算 v18 = v16 - 200
      }
      else
      {
        v18 = 200;
      }
      result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj);  // 虚调用 vt+308（pObj）是否本地玩家
      if ( (uint8_t)result != 0 )
        return (uint32_t *)sub_4E4A50(pObj, 48026, 0, v18, 245, 0, 1, 0, 0, 0);  // sub_4E4A50 —— 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
    }
    return result;
  }
LABEL_19:
  v10 = 0;
  v11 = 16;
  while ( 2 )
  {
    result = *(uint32_t **)(v11 + dword_8F850C2);  // dword_8F850C2 —— [esp+20h] [ebp+10h]
    if ( result == nullptr )
    {
LABEL_23:
      v11 += 4;
      ++v10;  // 计数自增 v10
      if ( v11 >= 32 )
        return result;
      continue;
    }
    break;
  }
  result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)result[49] + 80))(result[49]);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  if ( result == nullptr )
  {
    dword_8F850C2 = dword_8F850C;  // dword_8F850C2 —— [esp+20h] [ebp+10h]
    goto LABEL_23;
  }
  result = (uint32_t *)dword_8F850C;  // dword_8F850C —— 队伍槽重置 4 槽 +188 解锁清空 → 自身
  pObj = *(uint32_t *)(*(uint32_t *)(dword_8F850C + 4 * v10 + 16) + 196);  // dword_8F850C —— 队伍槽重置 4 槽 +188 解锁清空 → 自身
  if ( pObj != 0 )
    goto LABEL_26;
  return result;
}


// ------------------------------------------------------------
// 0x45A750 sub_45A750 —— 向第 nArg4 组追加一条 52 字节玩家条目
// 默认构造(·sub_459700)后取值：·sub_4F33A0(+4)、·sub_4015C0 名串(+8)、·sub_4F2DF0(+36)、
// +40 = nArg3、·sub_4F2DA0(+44)，尾插 ·+440+16*nArg4 组。
// ------------------------------------------------------------
int /*thiscall*/ sub_45A750(void *this, int nArg2, int nArg3, int nArg4)  // sub_45A750 —— 向第 nArg4 组追加一条 52 字节玩家条目 默认
{
  void *v5; // eax
  int v6; // eax
  uint32_t v8[14]; // [esp+Ch] [ebp-44h] BYREF
  int v9; // [esp+4Ch] [ebp-4h]

  v8[13] = dword_796E50;  // dword_796E50 —— 栈检 cookie
  sub_459700(v8);  // sub_459700 —— 52 字节元素默认初始化
  v9 = 0;
  v8[1] = sub_4F33A0(nArg2);  // v8[1] = 调 sub_4F33A0 返回值
  v5 = (void *)sub_4F2CE0(nArg2);  // sub_4F2CE0 —— 存 按物品 id 取名称串：查模板表
  sub_4015C0(v5, strlen((const char *)v5));  // 【std::string构造赋值】
  v8[10] = nArg3;
  v6 = sub_4F2D60(nArg2);
  v8[9] = sub_4F2DF0(v6);  // v8[9] = 调 sub_4F2DF0 返回值
  v8[11] = sub_4F2DA0(nArg2);  // v8[11] = 调 sub_4F2DA0 返回值
  sub_45A340((int)this + 16 * nArg4 + 440, v8);  // sub_45A340 —— 52 字节向量尾插
  v9 = -1;
  return sub_477AF0(v8);  // 调 后 j__free 基址并三指针清零
}



// ------------------------------------------------------------
// 0x45A820 sub_45A820 —— REWARD_DIVIDE_SET —— 划分按钮逐格排布
// 字符串自证：切状态 6 后按 ·+436 划分计数把按钮(+524+i*4) 依 ·dword_6C6E00[count] + 158*i 排开（y = 163）并点亮。
// ------------------------------------------------------------
void */*thiscall*/ sub_45A820(uint32_t *this)  // sub_45A820 —— REWARD_DIVIDE_SET —— 划分按钮逐格排布
{
  int fld_e109; // eax
  int v3; // ebx
  int v4; // edi
  uint32_t **pThis_83; // esi

  sub_45A420((int)this, 6);  // sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
  fld_e109 = *(this + 109);  // 读字段 fld_e109 = this+109
  v3 = 0;
  if ( fld_e109 > 0 )  // fld_e109=this+436 【推断】攻击数据表取值
  {
    v4 = 0;
    pThis_83 = (uint32_t **)(this + 131);  // this+524〔fAbilityScale(推断)〕
    do
    {
      sub_69A5F0(*pThis_83, v4 + dword_6C6E00[fld_e109], 163);  // 调 设位、sub_69A840 登记
      *((uint8_t *)*pThis_83 + 16) = 1;  // pThis_83=this+524 fAbilityScale
      fld_e109 = *(this + 109);  // 读字段 fld_e109 = this+109
      ++v3;  // 计数自增 v3
      ++pThis_83;  // 计数自增 pThis_83
      v4 += 158;
    }
    while ( v3 < fld_e109 );  // 循环直到 v3 < fld_e109
  }
  return sub_432EA0("REWARD_DIVIDE_SET", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
}



// ------------------------------------------------------------
// 0x45A8A0 sub_45A8A0 —— CNRDReward 构造（控件/按钮/贴图全套）
// 取 ·dword_99FCC8+20 的 +128/+184 与 ·dword_99FCCC 配色，载 Common/ActiveStatus/Blind1.img 入 ·+656；
// 建主控件 0x68(+44，640x480)、2 个 CNNumberSet(+36/+40)、4 按钮(+524..+536) 与 3 划分按钮(+588..+596，
// 坐标表 ·unk_6C6E34)，末以状态 0 收尾（构造末尾 sub_45A420(0) 实参被反编译吞掉）。
// ------------------------------------------------------------
int /*thiscall*/ sub_45A8A0(int this, void *Block)  // sub_45A8A0 —— CNRDReward 构造（控件/按钮/贴图全套）
{
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  int fld_2C; // eax
  uint32_t *pMem2; // edi
  int pObj; // eax
  bool v8; // cc
  uint32_t *pMem3; // edi
  uint32_t *pMem32; // eax
  bool v11; // zf
  uint32_t *pMem4; // edi
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  void *fld_34; // eax
  uint32_t *pMem43; // eax
  int pObj2; // edi
  int v20; // [esp+Ch] [ebp-2Ch]
  void *pMem42; // [esp+10h] [ebp-28h]
  void *pMem22; // [esp+14h] [ebp-24h]
  int v23; // [esp+18h] [ebp-20h]
  int v24; // [esp+1Ch] [ebp-1Ch]
  int fld_302; // [esp+20h] [ebp-18h]
  int fld_30; // [esp+24h] [ebp-14h]
  int pThis_24; // [esp+28h] [ebp-10h]
  int v28; // [esp+34h] [ebp-4h]
  char *Blocka; // [esp+40h] [ebp+8h]
  char *Blockb; // [esp+40h] [ebp+8h]
  int *Blockc; // [esp+40h] [ebp+8h]

  *(uint32_t *)(this + 160) = Block;  // 写字段 this+160（fAdd160） ← Block
  *(uint32_t *)(this + 48) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 128);  // dword_99FCC8 —— nengine::CNSlider 构造
  *(uint32_t *)(this + 52) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 184);  // dword_99FCC8 —— nengine::CNSlider 构造
  *(uint32_t *)(this + 656) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
                              dword_8F84B8,  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
                              "Common/ActiveStatus/Blind1.img");  // 资源 Common/ActiveStatus/Blind1.img
  pMem = operator new(0x68u);  // 堆分配
  v28 = 0;
  if ( pMem != nullptr )
    v4 = sub_426BD0(pMem);  // sub_426BD0 —— nengine::IControl 构造
  else
    v4 = nullptr;
  *(uint32_t *)(this + 44) = v4;  // 写字段 this+44（nExpireMs） ← v4
  *((uint32_t *)v4 + 7) = 640;  // 写字段 v4+7（uPathTerm）
  *((uint32_t *)v4 + 8) = 480;  // 写字段 v4+8（nSkillRec8）
  fld_2C = *(uint32_t *)(this + 44);  // 读字段 fld_2C = this+44（nExpireMs）
  v28 = -1;
  *(uint32_t *)(fld_2C + 68) = this;  // 写字段 fld_2C+68（nCharCount） ← this
  v20 = 61;
  pMem42 = (void *)71;  // pMem42 = 转换(71)
  Blocka = nullptr;
  pThis_24 = this + 36;  // this+36 物品状态字
  do
  {
    pMem2 = operator new(0x2Cu);  // 堆分配
    pMem22 = pMem2;
    v28 = 1;
    if ( pMem2 != nullptr )
    {
      fld_30 = *(uint32_t *)(this + 48);  // 读字段 fld_30 = this+48（pCmdVecBegin48）
      fld_302 = dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      *((uint8_t *)pMem2 + 4) = 0;  // 写字段 pMem2+4（pHostObj）
      LOBYTE(v28) = 2;
      *pMem2 = &nengine::CNNumberSet::`vftable';  // vftable 复位
      sub_699E20(v6);  // 调 本体初始化 + sub_699E40(a2..a5)
      sub_699E40(v25, v26, *(&v20 + (uint32_t)Blocka), 1);
    }
    else
    {
      v6 = nullptr;
    }
    v7 = v27;
    *(uint32_t *)v27 = v6;  // *v27 = v6
    v6[10] = -5;
    *(uint32_t *)(*(uint32_t *)v7 + 36) = 0;
    *(uint8_t *)(*(uint32_t *)v7 + 24) = 0;
    v8 = (int)(Blocka + 1) < 2;
    v28 = -1;
    ++Blocka;  // 计数自增 Blocka
    v27 = v7 + 4;  // 计算 v27 = v7 + 4
  }
  while ( v8 );
  *(uint8_t *)(this + 56) = 0;  // 写字段 this+56（pCmdVecCap56） ← 0
  *(uint8_t *)(this + 57) = 0;  // 写字段 this+57 ← 0
  *(uint8_t *)(this + 58) = 0;  // 写字段 this+58 ← 0
  *(uint8_t *)(this + 59) = 0;  // 写字段 this+59 ← 0
  *(uint32_t *)(this + 68) = 0;  // 写字段 this+68（nCharCount） ← 0
  *(uint32_t *)(this + 80) = 0;  // 写字段 this+80（nAuraStage） ← 0
  *(uint32_t *)(this + 88) = 0;  // 写字段 this+88（pFxObjB） ← 0
  *(uint32_t *)(this + 92) = 0;  // 写字段 this+92（pFxObjC） ← 0
  *(uint32_t *)(this + 96) = 0;  // 写字段 this+96（nStatusMode） ← 0
  *(uint32_t *)(this + 100) = 0;  // 写字段 this+100（bEnchantDone） ← 0
  *(uint32_t *)(this + 104) = 0;  // 写字段 this+104（nTimerEnd） ← 0
  *(uint32_t *)(this + 76) = 12;  // 写字段 this+76（szEmblemPath） ← 12
  *(uint32_t *)(this + 84) = 1600;  // 写字段 this+84（pFxObjA） ← 1600
  *(uint32_t *)(this + 72) = 6;  // 写字段 this+72（nSnapshot72） ← 6
  *(uint32_t *)(this + 104) = dword_99FCCC;  // 写字段 this+104（nTimerEnd） ← dword_99FCCC
  *(uint32_t *)(this + 84) = 180;  // 写字段 this+84（pFxObjA） ← 180
  *(uint32_t *)(this + 68) = 0;  // 写字段 this+68（nCharCount） ← 0
  *(uint32_t *)(this + 60) = -16777216;  // 写字段 this+60（nFadeValue60） ← -16777216
  *(uint32_t *)(this + 136) = 1600;  // 写字段 this+136（nCtx136） ← 1600
  *(uint8_t *)(this + 108) = 0;  // 写字段 this+108（nAdd108） ← 0
  *(uint8_t *)(this + 109) = 0;  // 写字段 this+109 ← 0
  *(uint8_t *)(this + 110) = 0;  // 写字段 this+110 ← 0
  *(uint8_t *)(this + 111) = 0;  // 写字段 this+111 ← 0
  *(uint32_t *)(this + 120) = 0;  // 写字段 this+120（pAnimObj） ← 0
  *(uint32_t *)(this + 124) = 6;  // 写字段 this+124（pAuraAnim） ← 6
  *(uint32_t *)(this + 128) = 12;  // 写字段 this+128（szStatusKeyBuf） ← 12
  *(uint32_t *)(this + 132) = 0;  // 写字段 this+132（nAdd132） ← 0
  *(uint32_t *)(this + 140) = 0;  // 写字段 this+140（nAdd140） ← 0
  *(uint32_t *)(this + 144) = 0;  // 写字段 this+144（pFrameList144） ← 0
  *(uint32_t *)(this + 148) = 0;  // 写字段 this+148（fAdd148） ← 0
  *(uint32_t *)(this + 152) = 0;  // 写字段 this+152（nAdd152） ← 0
  *(uint32_t *)(this + 156) = 0;  // 写字段 this+156（nAdd156） ← 0
  *(uint32_t *)(this + 156) = dword_99FCCC;  // 写字段 this+156（nAdd156） ← dword_99FCCC
  *(uint32_t *)(this + 136) = 120;  // 写字段 this+136（nCtx136） ← 120
  *(uint32_t *)(this + 120) = 0;  // 写字段 this+120（pAnimObj） ← 0
  *(uint32_t *)(this + 112) = -16777216;  // 写字段 this+112（pHostComp） ← -16777216
  *(uint8_t *)(this + 110) = 1;  // 写字段 this+110 ← 1
  sub_698F90(this + 164, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  Blockb = (char *)(this + 524);  // this+524〔fAbilityScale(推断)〕
  v27 = 4;
  do
  {
    v9 = operator new(0x84u);  // 堆分配
    v22 = v9;
    v28 = 3;
    if ( v9 != nullptr )
    {
      v25 = *(uint32_t *)(this + 48);  // 读字段 v25 = this+48（pCmdVecBegin48）
      sub_426BD0(v9);  // sub_426BD0 —— nengine::IControl 构造
      LOBYTE(v28) = 4;
      *v9 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(pMem3);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(fld_302, 85, 85, 85, -1, 0, 0);
      pMem32 = pMem3;
    }
    else
    {
      pMem32 = nullptr;
    }
    *(uint32_t *)Blockb = pMem32;  // *Blockb = pMem32
    v28 = -1;
    sub_69A840(pMem32);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    *(uint32_t *)(*(uint32_t *)Blockb + 68) = this;  // Blockb=this+524 fAbilityScale
    v11 = pThis_24 == 1;  // pThis_24=this+36 物品状态字
    Blockb += 4;  // Blockb 前进 4
    --pThis_24;  // 计数自减 pThis_24
  }
  while ( !v11 );
  Blockc = (int *)&unk_6C6E34;
  pThis_24 = this + 588;
  do
  {
    pMem4 = operator new(0x84u);  // 堆分配
    pMem42 = pMem4;
    v28 = 5;
    if ( pMem4 != nullptr )
    {
      v13 = *Blockc;
      fld_302 = Blockc[1];
      v14 = *(Blockc - 1);
      fld_30 = v13;  // fld_30=this+48 pCmdVecBegin48
      v15 = *(Blockc - 2);
      fld_34 = *(void **)(this + 52);  // this+208〔nField208(推断)〕
      v24 = v14;
      v23 = v15;
      pMem22 = fld_34;  // fld_34=this+208 nField208
      sub_426BD0(pMem4);  // sub_426BD0 —— nengine::IControl 构造
      LOBYTE(v28) = 6;
      *pMem4 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(pMem4);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(pMem22, v23, v24, fld_30, fld_302, 0, 0);  // fld_30=this+48 pCmdVecBegin48
      pMem43 = pMem4;
    }
    else
    {
      pMem43 = nullptr;
    }
    pObj2 = pThis_24;
    *(uint32_t *)pThis_24 = pMem43;  // *pThis_24 = pMem43
    v28 = -1;
    sub_69A840(pMem43);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    *(uint32_t *)(*(uint32_t *)pObj2 + 68) = this;
    v8 = (int)(Blockc + 4) < 7106148;  // Blockc+4〔宿主对象〕
    pThis_24 = pObj2 + 4;
    Blockc += 4;  // Blockc 前进 4
  }
  while ( v8 );
  return sub_45A420(0);  // sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
}


// ============================================================
// 【分区 10】CNRDReward 奖励主类（0x45AC20-0x45B4A0）
// CNRDReward__vmt0（RTTI 自证；REWARD_BOX_GLITTER 自证）。
// ============================================================
// ------------------------------------------------------------
// 0x45AC20 CNRDReward__vmt0
// ------------------------------------------------------------
// CNRDReward::vmt0 —— 奖励主类帧处理（RTTI 自证；REWARD_BOX_GLITTER 自证）
int /*userpurge*/ sub_45AC20@<eax>(int pArg1@<ecx>, double fArg2@<st0>, uint8_t *uArg3)  // 实现：CNRDReward::vmt0 —— 奖励主类帧处理（RTTI 自证；REWARD_BOX_GLITTER 自证）
{
  int result; // eax
  int v5; // eax
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // ebx
  int v10; // ebx
  int pObj; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edi
  int v16; // eax

  result = *(uint32_t *)(pArg1 + 4);  // 读字段 result = pArg1+4（pHostObj）
  if ( result == 9 )
    return (int)sub_4581C0((int *)pArg1, uArg3);  // sub_4581C0 —— 奖励箱悬停点击派发
  if ( uArg3 != *(uint8_t **)(pArg1 + 44) )  // pArg1+44〔nExpireMs(推断)〕
  {
LABEL_51:
    if ( *(uint32_t *)(pArg1 + 4) == 6 )  // pArg1+4〔宿主对象〕
      return sub_457AA0((int *)pArg1, (int)uArg3);  // sub_457AA0 —— 开箱结果高亮
    return result;
  }
  if ( result >= 2 )
  {
    v5 = result == 8 ? *(uint32_t *)(pArg1 + 600) : 255;
    sub_4587C0((void *)pArg1, v5);  // sub_4587C0 —— 箱体高亮旋转绘制
    if ( *(uint32_t *)(pArg1 + 4) == 2 )  // pArg1+4〔宿主对象〕
    {
      v6 = sub_699000(pArg1 + 8);  // 【clock_now(clk)】
      v7 = sub_423A80(0, 255, v6, 800);  // sub_423A80 —— 同上 int 版（FTOL 截断）
      v8 = sub_418DD0(84);  // sub_418DD0 —— 资源句柄 (101)
      sub_43B560(0, 0, v8, 1065353216, 1065353216, 0, ((uint8_t)v7 << 24) | 0xFFFFFF, 1333788672, 1333788672);  // sub_43B560 —— 绘制转发（vt+128）
      sub_4588C0(v7);  // sub_4588C0 —— 箱体绘制转发
      sub_458670(v7);  // sub_458670 —— 开箱数量文本绘制（多行版）
      sub_457040(v7);  // sub_457040 —— 控件 53 全屏绘制
      if ( *(uint32_t *)(pArg1 + 4) == 2 && sub_699000(pArg1 + 8) >= 800 )  // 【clock_now(clk)】
      {
        sub_45A420(*(uint32_t *)(pArg1 + 4) + 1);  // sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
        result = sub_699000(pArg1 + 8) + 125;  // 【clock_now(clk)】
        *(uint32_t *)(pArg1 + 560) = result;  // 写字段 pArg1+560 ← result
        return result;
      }
    }
  }
  v9 = *(uint32_t *)(pArg1 + 4);  // 读字段 v9 = pArg1+4（pHostObj）
  if ( v9 >= 3 )
  {
    if ( v9 == 8 )
      v10 = *(uint32_t *)(pArg1 + 600);  // 读字段 v10 = pArg1+600
    else
      LOBYTE(v10) = -1;
    pObj = sub_418DD0(84);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
        pObj,
        0,
        0,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,
        1065353216,
        0,
        ((uint8_t)v10 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    if ( *(uint32_t *)(pArg1 + 4) == 3 )  // pArg1+4〔宿主对象〕
    {
      sub_4588C0(255);  // sub_4588C0 —— 箱体绘制转发
      sub_459ED0(pArg1, fArg2);  // 调 +264<11 且 +432 未置位时记时刻并 REWARD_BOX_SET
      sub_457090(pArg1);  // sub_457090 —— 奖励箱列表逐项淡入
      sub_457040(255);  // sub_457040 —— 控件 53 全屏绘制
    }
    v9 = *(uint32_t *)(pArg1 + 4);  // 读字段 v9 = pArg1+4（pHostObj）
    if ( v9 == 3 && sub_5721D0(pArg1 + 248) == 0 )  // sub_5721D0 —— 物品信息窗小辅助（15 行）
    {
      sub_45A420(4);  // sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
      memset((void *)(pArg1 + 268), 1u, 0x2Cu);  // 调 内存按字节填充
      sub_457C60(pArg1);  // sub_457C60 —— 开箱时序表初始化
      return (int)sub_432EA0("REWARD_BOX_GLITTER", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    }
  }
  if ( v9 >= 4 )
  {
    if ( v9 == 4 )
    {
      v12 = sub_699000(pArg1 + 8);  // 【clock_now(clk)】
      v13 = sub_423A80(255, 0, v12, 1800);  // sub_423A80 —— 同上 int 版（FTOL 截断）
      sub_4588C0(v13);  // sub_4588C0 —— 箱体绘制转发
      sub_4575F0(pArg1, fArg2);  // sub_4575F0 —— 开箱动画 III（56/57 组）
      sub_457370((int *)pArg1);  // sub_457370 —— 开箱动画 II（多箱版）
      sub_457160((void *)pArg1);  // sub_457160 —— 开箱动画 I（53/54/55 组）
    }
    if ( *(uint32_t *)(pArg1 + 4) == 5 )  // pArg1+4〔宿主对象〕
      sub_457890((uint32_t *)pArg1);  // sub_457890 —— 开箱卡片动画
    sub_457CB0(pArg1, fArg2);  // sub_457CB0 —— 开箱缩放动画
    if ( *(uint32_t *)(pArg1 + 4) == 4 && sub_699000(pArg1 + 8) >= 1800 )  // 【clock_now(clk)】
    {
      sub_432EA0("REWARD_DIVIDE", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
      return sub_45A420(*(uint32_t *)(pArg1 + 4) + 1);  // sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
    }
  }
  if ( *(uint32_t *)(pArg1 + 4) == 5 && sub_699000(pArg1 + 8) >= 1200 && *(uint8_t *)(pArg1 + 580) == 0 )  // 【clock_now(clk)】
    return sub_4577C0(pArg1);  // sub_4577C0 —— 开箱完成上报
  v14 = *(uint32_t *)(pArg1 + 4);  // 读字段 v14 = pArg1+4（pHostObj）
  if ( v14 >= 6 )
  {
    sub_458E00((uint32_t *)pArg1);  // sub_458E00 —— 开箱阶段刷帧
    if ( *(uint32_t *)(pArg1 + 4) == 6 )  // pArg1+4〔宿主对象〕
      sub_457DD0(pArg1);  // sub_457DD0 —— 未开箱余量提示
    v14 = *(uint32_t *)(pArg1 + 4);  // 读字段 v14 = pArg1+4（pHostObj）
    if ( v14 == 6 )
    {
      v15 = sub_699000(pArg1 + 164) - *(uint32_t *)(pArg1 + 216);  // 【clock_now(clk)】
      result = sub_457790(pArg1);  // sub_457790 —— 全箱判定
      if ( (uint8_t)result == 1 || v15 >= 4000 )
        return sub_45A420(*(uint32_t *)(pArg1 + 4) + 1);  // sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
      return result;
    }
  }
  if ( v14 == 7 && sub_699000(pArg1 + 8) >= 5000 )  // 【clock_now(clk)】
    return sub_45A420(*(uint32_t *)(pArg1 + 4) + 1);  // sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
  result = *(uint32_t *)(pArg1 + 4);  // 读字段 result = pArg1+4（pHostObj）
  if ( result >= 8 )
  {
    result = sub_699000(pArg1 + 8);  // 【clock_now(clk)】
    if ( result <= 1000 )
    {
      v16 = sub_699000(pArg1 + 8);  // 【clock_now(clk)】
      result = sub_423A80(255, 0, v16, 1000);  // sub_423A80 —— 同上 int 版（FTOL 截断）
      *(uint32_t *)(pArg1 + 600) = result;  // 写字段 pArg1+600 ← result
    }
    if ( *(uint32_t *)(pArg1 + 4) == 8 )  // pArg1+4〔宿主对象〕
    {
      result = sub_699000(pArg1 + 8);  // 【clock_now(clk)】
      if ( result >= 1500 )
        return sub_45A420(*(uint32_t *)(pArg1 + 4) + 1);  // sub_45A420 —— CNRDReward 状态机入口（·+4 = 状态 n）
    }
  }
  goto LABEL_51;
}


// ------------------------------------------------------------
// 0x45AFD0 sub_45AFD0 —— 对象存在谓词（·sub_472F90(句柄) >= 1）
// 句柄解引用非空即判存在【推断：存活/存在判断】。
// ------------------------------------------------------------
bool /*cdecl*/ sub_45AFD0(char pszArg1)  // sub_45AFD0 —— 对象存在谓词（·sub_472F90(句柄) >= 1）
{
  return sub_472F90(pszArg1) >= 1;  // 返回 命中返回节点 dword#4（+16），未命中返回 0
}



// ------------------------------------------------------------
// 0x45AFF0 sub_45AFF0 —— 未激活(·+4 = 0)时的字段清空
// +12/+44/+48 与 +112..+208 区段清 0，装载态 +172 复置 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_45AFF0(int this)  // sub_45AFF0 —— 未激活(·+4 = 0)时的字段清空
{
  int result; // eax

  result = 0;
  if ( *(uint8_t *)(this + 4) == 0 )  // this+4〔宿主对象〕等 2 字段
  {
    *(uint32_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
    *(uint32_t *)(this + 44) = 0;  // 写字段 this+44（nExpireMs） ← 0
    *(uint32_t *)(this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48） ← 0
    *(uint32_t *)(this + 112) = 0;  // 写字段 this+112（pHostComp） ← 0
    *(uint8_t *)(this + 116) = 0;  // 写字段 this+116（pSessionCtx） ← 0
    *(uint32_t *)(this + 100) = 0;  // 写字段 this+100（bEnchantDone） ← 0
    *(uint32_t *)(this + 104) = 0;  // 写字段 this+104（nTimerEnd） ← 0
    *(uint32_t *)(this + 108) = 0;  // 写字段 this+108（nAdd108） ← 0
    *(uint8_t *)(this + 117) = 0;  // 写字段 this+117 ← 0
    *(uint32_t *)(this + 120) = 0;  // 写字段 this+120（pAnimObj） ← 0
    *(uint32_t *)(this + 152) = 0;  // 写字段 this+152（nAdd152） ← 0
    *(uint32_t *)(this + 156) = 0;  // 写字段 this+156（nAdd156） ← 0
    *(uint32_t *)(this + 160) = 0;  // 写字段 this+160（fAdd160） ← 0
    *(uint32_t *)(this + 164) = 0;  // 写字段 this+164（fAdd164） ← 0
    *(uint32_t *)(this + 168) = 0;  // 写字段 this+168（pAppendVec） ← 0
    *(uint32_t *)(this + 172) = -1;  // 写字段 this+172（pAppendVecEnd） ← -1
    *(uint8_t *)(this + 189) = 0;  // 写字段 this+189（bFlag189） ← 0
    *(uint8_t *)(this + 190) = 0;  // 写字段 this+190（bFlag190） ← 0
    *(uint32_t *)(this + 204) = 0;  // 写字段 this+204（pSubAnim204） ← 0
    *(uint32_t *)(this + 208) = 0;  // 写字段 this+208（nField208） ← 0
  }
  return result;
}



// ------------------------------------------------------------
// 0x45B060 sub_45B060 —— 淡入档位设定（·+120 = nArg2）
// 时钟(+124)归零、+137/+138 清 0；nArg2 = 1 时主控 alpha(dword_8F8528+2484) 置 255，
// 配合 ·sub_45CB30 做 300ms 255→0 的渐隐。
// ------------------------------------------------------------
void */*thiscall*/ sub_45B060(uint32_t *this, int nArg2)  // sub_45B060 —— 淡入档位设定（·+120 = nArg2）
{
  int pThis_1F; // ecx
  void *result; // eax

  *(this + 30) = nArg2;  // 写字段 this+30 ← nArg2
  pThis_1F = (int)(this + 31);  // this+124〔pAuraAnim(推断)〕
  *(uint8_t *)(pThis_1F + 13) = 0;  // 写字段 pThis_1F+13 ← 0
  *(uint8_t *)(pThis_1F + 14) = 0;  // 写字段 pThis_1F+14 ← 0
  sub_698F90(pThis_1F, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  result = (void *)(nArg2 - 1);
  if ( nArg2 == 1 )
  {
    result = dword_8F8528;  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    *((uint32_t *)dword_8F8528 + 621) = 255;  // dword_8F8528 —— 对象池借出（按池号取可用对象）
  }
  return result;
}



// ------------------------------------------------------------
// 0x45B0A0 sub_45B0A0 —— 引导（教程）对象登记转发
// 已登记与否经 ·sub_5460A0/546120 判定；未完成取 ·sub_44E8D0(0x1F) 引导对象按有无第二参调 vt+56/vt+60，完成后清 ·+164。
// ------------------------------------------------------------
void /*thiscall*/ sub_45B0A0(uint32_t *this)  // sub_45B0A0 —— 引导（教程）对象登记转发
{
  uint32_t *fld_e41; // edx
  int pObj; // ecx

  fld_e41 = (uint32_t *)*(this + 41);  // this+164〔fAdd164(推断)〕
  if ( fld_e41 != nullptr )  // fld_e41=this+164 fAdd164
  {
    if ( *(this + 42) != 0 )  // this+168〔pAppendVec(推断)〕
    {
      if ( (uint8_t)sub_5460A0(*fld_e41, *(this + 42)) != 0 )  // sub_5460A0 —— 引导辅助（44E8D0）
      {
LABEL_9:
        *(this + 41) = 0;  // 写字段 this+41 ← 0
        return;
      }
    }
    else if ( (uint8_t)sub_546120(*((uint32_t *)dword_8F8528 + 11)) != 0 )  // sub_546120 —— 引导辅助 3（429830 + 41A5E0 + 44E8D0）
    {
      *(this + 41) = 0;  // 写字段 this+41 ← 0
      return;
    }
    pObj = sub_44E8D0((char *)dword_8F8528, (void *)0x1F, 0, 0);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）
    if ( *(this + 42) == 0 )  // this+168〔pAppendVec(推断)〕
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 60))(pObj, *(this + 41));  // 虚调用 vt+60（pObj）对象销毁/释放
      *(this + 41) = 0;  // 写字段 this+41 ← 0
      return;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pObj + 56))(pObj, *(this + 41), *(this + 42));  // 虚调用 vt+56（pObj 虚表槽）
    goto LABEL_9;
  }
}



// ------------------------------------------------------------
// 0x45B140 sub_45B140 —— 刷新 ·+108 悬停记录
// 主控件(·+44) 的 +44 标志置位且 ·dword_8F7C08 存在时，按坐标取覆盖矩形记录 ·sub_48C860。
// ------------------------------------------------------------
int /*thiscall*/ sub_45B140(int *this)  // sub_45B140 —— 刷新 ·+108 悬停记录
{
  int result; // eax

  result = *(this + 11);  // 读字段 result = this+11
  if ( *(uint32_t *)(result + 44) != 0 )  // result=this+44 剩余时间 ms
  {
    result = dword_8F7C08;  // dword_8F7C08 —— 副玩家/观战
    if ( dword_8F7C08 != 0 )  // dword_8F7C08 —— 副玩家/观战
    {
      result = sub_48C860(dword_8F7C08);  // sub_48C860 —— 按坐标查覆盖矩形记录（this+54 表）
      *(this + 27) = result;  // 写字段 this+27 ← result
    }
  }
  return result;  // result=this+44 剩余时间 ms
}



// ------------------------------------------------------------
// 0x45B170 sub_45B170 —— 房间对象可用判定
// ·sub_4CE8A0 查对象：缺失报 aCriticalError_5；+92 键为 -1 或 ·sub_472F90(键) >= 1 即可用。
// ------------------------------------------------------------
bool /*stdcall*/ sub_45B170(int ArgList)  // sub_45B170 —— 房间对象可用判定
{
  int v1; // eax
  int v3; // eax

  v1 = sub_4CE8A0(ArgList);  // sub_4CE8A0 —— 调用 sub_4CE8A0
  if ( v1 != 0 )
  {
    v3 = *(uint32_t *)(v1 + 92);  // 读字段 v3 = v1+92（pFxObjC）
    return v3 == -1 || sub_472F90(v3) >= 1;  // 返回 命中返回节点 dword#4（+16），未命中返回 0
  }
  else
  {
    off_77F3FC(aCriticalError_5, ArgList);  // off_77F3FC —— 日志打印（printf 风格）
    return false;
  }
}



// ------------------------------------------------------------
// 0x45B1C0 sub_45B1C0 —— 取 ·+152 登记对象（失联则清零）
// 归属校验 ·sub_45E680 失败即置 0 返回。
// ------------------------------------------------------------
int /*thiscall*/ sub_45B1C0(uint32_t *this)  // sub_45B1C0 —— 取 ·+152 登记对象（失联则清零）
{
  if ( (uint8_t)sub_45E680(*(this + 38)) == 0 )  // sub_45E680 —— 对象表归属判定
    *(this + 38) = 0;  // 写字段 this+38（bFadeFlag38） ← 0
  return *(this + 38);  // 返回字段 this+152（nAdd152）
}



// ------------------------------------------------------------
// 0x45B1F0 sub_45B1F0 —— STL 红黑树迭代器自增
// MSVC _Tree 中序后继：有右子取右子树最左，否则回溯父链（哨兵字节 ·+33）。
// ------------------------------------------------------------
int /*thiscall*/ sub_45B1F0(void *this)  // sub_45B1F0 —— STL 红黑树迭代器自增
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 33) != 0 )  // this+33〔bJobVecDirty〕
  {
    result = v1[2];
    *(uint32_t *)this = result;  // *this = result
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 33) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 33) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;  // *this = result
          result = *(uint32_t *)(result + 4);  // 读字段 result = result+4（pHostObj）
        }
        while ( *(uint8_t *)(result + 33) == 0 );  // 写字段 result+33（bJobVecDirty） ← = 0 )
        if ( *(uint8_t *)(result + 33) == 0 )
          *(uint32_t *)this = result;  // *this = result
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 33) == 0; result = *(uint32_t *)(result + 8) )  // 读字段 result = v3+8（nSkillRec8）
        v3 = result;
      *(uint32_t *)this = v3;  // *this = v3
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x45B250 sub_45B250 —— 激活态重置 + 锚定当前角色
// 两条时钟(+16/+124)归零、+112 = -1000、+120 淡入档与 +216 清 0/-1；
// ·sub_424A40 把主控件(·+44) 锚定到 ·dword_8F7C08（锚定角色 setter）。
// ------------------------------------------------------------
char /*thiscall*/ sub_45B250(int this)  // sub_45B250 —— 激活态重置 + 锚定当前角色
{
  char result; // al

  result = *(uint8_t *)(this + 4);  // 读字段 result = this+4（pHostObj）
  if ( result != 0 )  // result=this+4 pHostObj
  {
    *(uint8_t *)(this + 29) = 0;  // 写字段 this+29 ← 0
    *(uint8_t *)(this + 30) = 0;  // 写字段 this+30 ← 0
    sub_698F90(this + 16, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(uint32_t *)(this + 112) = -1000;  // 写字段 this+112（pHostComp） ← -1000
    *(uint8_t *)(this + 116) = 0;  // 写字段 this+116（pSessionCtx） ← 0
    *(uint32_t *)(this + 156) = 0;  // 写字段 this+156（nAdd156） ← 0
    *(uint32_t *)(this + 120) = 0;  // 写字段 this+120（pAnimObj） ← 0
    *(uint8_t *)(this + 137) = 0;  // 写字段 this+137（field_0089） ← 0
    *(uint8_t *)(this + 138) = 0;  // 写字段 this+138（field_008A） ← 0
    sub_698F90(this + 124, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    result = sub_424A40(*(uint32_t **)(this + 44), dword_8F7C08);  // sub_424A40 —— 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
    *(uint32_t *)(this + 216) = -1;  // 写字段 this+216（bField216） ← -1
  }
  return result;  // result=this+4 pHostObj
}



// ------------------------------------------------------------
// 0x45B2B0 sub_45B2B0 —— 世界地图出现/黑场过渡状态机（·+172 = 0/1/2）
// 驱动图层播放 ·sub_4938F0 与 320x240 属性 ·sub_491D00；0/2 态做 300ms 255↔0 透明度插值(·sub_4049C0)，
// 1 态等待 ·+200 时长；终态 ·sub_472B30(1) 后落 ·+117 = 1、状态回 -1。
// ------------------------------------------------------------
char /*thiscall*/ sub_45B2B0(int this)  // sub_45B2B0 —— 世界地图出现/黑场过渡状态机（·+172 = 0/1/2）
{
  int fld_2C; // edi
  int fld_AC; // eax
  int pThis_B0; // eax
  uint64_t v5; // rax
  int fld_C8; // ebx
  int pThis_B02; // eax
  uint64_t v9; // rax
  int v10; // [esp+Ch] [ebp-10h] BYREF
  int v11; // [esp+10h] [ebp-Ch]
  int v12; // [esp+14h] [ebp-8h]
  int v13; // [esp+18h] [ebp-4h]

  fld_2C = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 44) + 108) + 64);  // this+44〔nExpireMs(推断)〕等 2 字段
  if ( fld_2C != 0 )  // fld_2C=this+44 nExpireMs
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)fld_2C + 152))(fld_2C, 0, 0, dword_79C0B0);  // 虚调用 vt+152（fld_2C）取值(参数)
  sub_4938F0(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 44) + 108) + 60));  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  sub_491D00(dword_79C0B0, 320, 240, 0.0);  // sub_491D00 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
  fld_AC = *(uint32_t *)(this + 172);  // 读字段 fld_AC = this+172（pAppendVecEnd）
  switch ( fld_AC )  // 按 fld_AC 分派
  {
    case 0:  // case 0 分派（CNRDReward 奖励主类（0x45AC20-0x45B4A0））
      sub_698F90(this + 176, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      pThis_B0 = sub_699000(this + 176);  // 【clock_now(clk)】
      v5 = (uint64_t)sub_4049C0(255.0, 0.0, pThis_B0, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v10 = 0;
      v11 = 0;
      v12 = 640;
      v13 = 480;
      if ( fld_2C != 0 )  // fld_2C=this+44 nExpireMs
        (*(void (/*thiscall*/ **)(int, int *, int *, int, uint32_t, int))(*(uint32_t *)fld_2C + 136))(  // 虚调用 vt+136（fld_2C）目标挂接
          fld_2C,  // fld_2C=this+44 nExpireMs
          &v10,
          &v10,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          0,
          (uint8_t)v5 << 24);
      if ( sub_699000(this + 176) >= 300 )  // 【clock_now(clk)】
      {
        *(uint32_t *)(this + 172) = 1;  // 写字段 this+172（pAppendVecEnd） ← 1
        *(uint8_t *)(this + 189) = 0;  // 写字段 this+189（bFlag189） ← 0
        *(uint8_t *)(this + 190) = 0;  // 写字段 this+190（bFlag190） ← 0
        sub_698F90(this + 176, 1500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
      return 0;
    case 1:  // case 1 分派（CNRDReward 奖励主类（0x45AC20-0x45B4A0））
      fld_C8 = *(uint32_t *)(this + 200);  // 读字段 fld_C8 = this+200（field_00C8）
      if ( sub_699000(this + 176) < fld_C8 )  // 【clock_now(clk)】
        return 0;
      *(uint32_t *)(this + 172) = 2;  // 写字段 this+172（pAppendVecEnd） ← 2
      *(uint8_t *)(this + 189) = 0;  // 写字段 this+189（bFlag189） ← 0
      *(uint8_t *)(this + 190) = 0;  // 写字段 this+190（bFlag190） ← 0
      return 0;
    case 2:  // case 2 分派（CNRDReward 奖励主类（0x45AC20-0x45B4A0））
      sub_698F90(this + 176, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      pThis_B02 = sub_699000(this + 176);  // 【clock_now(clk)】
      v9 = (uint64_t)sub_4049C0(0.0, 255.0, pThis_B02, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v10 = 0;
      v11 = 0;
      v12 = 640;
      v13 = 480;
      if ( fld_2C != 0 )  // fld_2C=this+44 nExpireMs
        (*(void (/*thiscall*/ **)(int, int *, int *, int, uint32_t, int))(*(uint32_t *)fld_2C + 136))(  // 虚调用 vt+136（fld_2C）目标挂接
          fld_2C,  // fld_2C=this+44 nExpireMs
          &v10,
          &v10,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          0,
          (uint8_t)v9 << 24);
      if ( sub_699000(this + 176) < 300 )  // 【clock_now(clk)】
        return 0;
      sub_472B30(1, 0);  // 调 过场渐隐控制：byte_99FB90 使能 + dword_99FB94 起始时刻
      *(uint8_t *)(this + 117) = 1;  // 写字段 this+117 ← 1
      *(uint32_t *)(this + 172) = -1;  // 写字段 this+172（pAppendVecEnd） ← -1
      return 1;  // 返回 1(成功)
    default:
      return 0;
  }
}



// ============================================================
// 【分区 11】房间列表模块（0x45B4A0-0x45D190）
// CNRoomListModule__vmt8/vmt4（RTTI 自证；vmt8 侧同样打
// "CRITICAL ERROR : WORLD MAP LOAD FAIL %d"）。
// ============================================================
// ------------------------------------------------------------
// 0x45B4A0 CNRoomListModule__vmt8
// ------------------------------------------------------------
// CNRoomListModule::vmt8 —— 房间列表通知（RTTI 自证；世界地图装载失败同串）
int /*thiscall*/ CNRoomListModule__vmt8(uint32_t *this)  // 实现：CNRoomListModule::vmt8 —— 房间列表通知（RTTI 自证；世界地图装载失败同串）
{
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B0 + 28))(dword_79C0B0, 0);  // 虚调用 vt+28（dword_79C0B0 虚表槽）
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 84))(dword_79C0B0);  // 虚调用 vt+84（dword_79C0B0）退出可视/停止
  if ( *(this + 43) == -1 )  // this+172〔pAppendVecEnd(推断)〕
    sub_69AB00(*(this + 3));  // this+12〔nSkillRec12(推断)〕
  else
    sub_45B2B0((int)this);  // sub_45B2B0 —— 世界地图出现/黑场过渡状态机（·+172 = 0/1/2）
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 88))(dword_79C0B0);  // 虚调用 vt+88（dword_79C0B0 虚表槽）
  return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_79C0A4 + 4))(dword_79C0A4, 0, 0);  // 虚调用 vt+4（dword_79C0A4）对象赋值/迁移
}



// ------------------------------------------------------------
// 0x45B500 sub_45B500 —— 世界地图装载校验（WORLD MAP LOAD FAIL 自证）
// 取 ·+104 房间条目的地图 id → ·sub_4CE8A0，比对本频道门槛 ·sub_41A5E0(频道+53) 与地图条目 ·sub_476B60 的 +92
// （等级门槛【推断】）：达标返回 1；否则以 ·sub_422E70(535) 组文案（含最大可选值）上屏 ·sub_43BEE0，返回 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_45B500(uint32_t *this)  // sub_45B500 —— 世界地图装载校验（WORLD MAP LOAD FAIL 自证）
{
  int fld_e26; // eax
  int v3; // edi
  uint32_t *v4; // esi
  int v5; // eax
  int v6; // eax
  uint32_t *v7; // edi
  int i; // ebx
  int v9; // eax
  uint32_t *v10; // eax
  int v11; // eax
  uint32_t *v12; // esi
  char *v13; // eax
  int v14; // [esp+0h] [ebp-88h]
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int dword_796E502; // [esp+84h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  fld_e26 = *(this + 26);  // 读字段 fld_e26 = this+26
  if ( fld_e26 == 0 || *(uint32_t *)(fld_e26 + 32) != 4 )  // fld_e26=this+104 插值终点 Z
    return 0;
  v3 = **(uint32_t **)(fld_e26 + 40);  // fld_e26=this+104 插值终点 Z
  v4 = (uint32_t *)sub_4CE8A0(v3);  // sub_4CE8A0 —— 调用 sub_4CE8A0
  if ( v4 == nullptr )
  {
    off_77F3FC("CRITICAL ERROR : WORLD MAP LOAD FAIL %d", v3);  // off_77F3FC —— 日志打印（printf 风格）
    return 0;
  }
  v5 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
  v6 = sub_41A5E0(v5 + 53);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v7 = (uint32_t *)v4[17];
  v14 = v6;
  for ( i = -1; v7 != (uint32_t *)v4[18]; v7 += 2 )
  {
    if ( v7[1] == -1 )
    {
      v9 = sub_476B60(*v7);  // sub_476B60 —— 存 选区角色数据查找
      if ( v9 != 0 )
      {
        v11 = *(uint32_t *)(v9 + 92);  // 读字段 v11 = v9+92（pFxObjC）
        if ( v14 >= v11 )
          return 1;  // 返回 1(成功)
        if ( i == -1 || i > v11 )
          i = v11;
      }
      else
      {
        if ( v4[7] < 0x10u )
          v10 = v4 + 2;  // 计算 v10 = v4 + 2
        else
          v10 = (uint32_t *)v4[2];
        off_77F3FC(aCriticalError_6, v10, *v7);  // off_77F3FC —— 日志打印（printf 风格）
      }
    }
  }
  if ( v4[7] < 0x10u )
    v12 = v4 + 2;  // 计算 v12 = v4 + 2
  else
    v12 = (uint32_t *)v4[2];
  v13 = sub_422E70(535);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
  sprintf(Buffer, v13, v12, i);  // 调 格式化到缓冲
  sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
  return 0;
}



// ------------------------------------------------------------
// 0x45B660 sub_45B660 —— STL 红黑树 lower_bound（哨兵 ·+69）
// 返回首个键(·+12) >= *uArg3 的节点或头节点，供 0x18 节点树使用。
// ------------------------------------------------------------
int **/*thiscall*/ sub_45B660(int **this, int **pDwArg2, uint32_t *uArg3)  // sub_45B660 —— STL 红黑树 lower_bound（哨兵 ·+69）
{
  int *fld_e1; // edx
  int *v4; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v4 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  while ( *((uint8_t *)v4 + 69) == 0 )  // 当 *((uint8_t *)v4 + 69) == 0 循环
  {
    if ( v4[3] >= *uArg3 )
    {
      fld_e1 = v4;  // fld_e1=this+4 宿主对象
      v4 = (int *)*v4;
    }
    else
    {
      v4 = (int *)v4[2];
    }
  }
  if ( fld_e1 == *(this + 1) || *uArg3 < fld_e1[3] )  // fld_e1=this+4 宿主对象
  {
    *pDwArg2 = *(this + 1);  // this+4〔宿主对象〕
    return pDwArg2;
  }
  else
  {
    *pDwArg2 = fld_e1;  // fld_e1=this+4 宿主对象
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x45B6D0 sub_45B6D0 —— 与 ·sub_45B660 同构（差异：哨兵字节 ·+33）
// 节点尺寸 0x24 之树的 lower_bound 查询（树头 +8 系列）。
// ------------------------------------------------------------
int **/*thiscall*/ sub_45B6D0(int **this, int **pDwArg2, uint32_t *uArg3)  // sub_45B6D0 —— 与 ·sub_45B660 同构（差异：哨兵字节 ·+33）
{
  int *fld_e1; // edx
  int *v4; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v4 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  while ( *((uint8_t *)v4 + 33) == 0 )  // 当 *((uint8_t *)v4 + 33) == 0 循环
  {
    if ( v4[3] >= *uArg3 )
    {
      fld_e1 = v4;  // fld_e1=this+4 宿主对象
      v4 = (int *)*v4;
    }
    else
    {
      v4 = (int *)v4[2];
    }
  }
  if ( fld_e1 == *(this + 1) || *uArg3 < fld_e1[3] )  // fld_e1=this+4 宿主对象
  {
    *pDwArg2 = *(this + 1);  // this+4〔宿主对象〕
    return pDwArg2;
  }
  else
  {
    *pDwArg2 = fld_e1;  // fld_e1=this+4 宿主对象
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x45B740 sub_45B740 —— STL 红黑树插入再平衡（节点 0x18）
// ·sub_5648C0 建/挂节点，插入后沿父链着色修复（·sub_433130 左旋、·sub_4296E0 重连）；
// 节点数超 0x1FFFFFFE 抛 map/set<T> too long。
// ------------------------------------------------------------
int */*thiscall*/ sub_45B740(int **this, int *pDwArg2, char pszArg3, int *pDwArg4, int nArg5)  // sub_45B740 —— STL 红黑树插入再平衡（节点 0x18）
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

  if ( (unsigned int)*(this + 2) >= 0x1FFFFFFE )  // this+8〔nSkillRec8(推断)〕
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v20 = 0;
    sub_401740(v17);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject = &std::length_error::`vftable';  // vftable 复位
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  fld_e1 = sub_5648C0(*(this + 1), pDwArg4, *(this + 1), nArg5, 0);  // sub_5648C0 —— 商店文本（23 行）
  fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
  fld_e15 = fld_e1;
  *(this + 2) = (int *)((char *)*(this + 2) + 1);  // 写字段 this+2 ← (int *)((char *)*(this + 2) + 1)
  if ( pDwArg4 == fld_e12 )  // fld_e12=this+4 宿主对象
  {
    fld_e12[1] = fld_e1;  // fld_e12=this+4 宿主对象
    **(this + 1) = fld_e1;  // 写字段 this+1 ← fld_e1
    (*(this + 1))[2] = fld_e1;  // this+4〔宿主对象〕
  }
  else if ( pszArg3 != 0 )
  {
    *pDwArg4 = fld_e1;
    fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
    if ( pDwArg4 == (int *)*fld_e13 )  // fld_e13=this+4 宿主对象
      *fld_e13 = fld_e1;  // fld_e13=this+4 宿主对象
  }
  else
  {
    pDwArg4[2] = fld_e1;
    fld_e14 = (int)*(this + 1);  // this+4〔宿主对象〕
    if ( pDwArg4 == *(int **)(fld_e14 + 8) )  // fld_e14=this+4 宿主对象
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // 写字段 fld_e14+8（nSkillRec8） ← fld_e1
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
            sub_433130(this, *v10);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(this, *(uint32_t **)(*(uint32_t *)(fld_e16 + 4) + 4));  // sub_4296E0 —— STL 内联红黑树节点摘除重连
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(this, (uint32_t *)*v10);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(this, *(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // sub_433130 —— 红黑树左旋（节点 0x18 版）
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;  // 写字段 v14+20（nPage） ← 1
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
  *(uint8_t *)((*(this + 1))[1] + 20) = 1;  // this+4〔宿主对象〕
  *pDwArg2 = fld_e1;
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x45B8F0 sub_45B8F0 —— 抛 std::length_error（vector<T> too long）
// 向量规模守卫：超过 0x3FFFFFFF 项时经此抛出。
// ------------------------------------------------------------
void /*noreturn*/ sub_45B8F0()  // sub_45B8F0 —— 抛 std::length_error（vector<T> too long）
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
  sub_401740(v1);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject = &std::length_error::`vftable';  // vftable 复位
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
}



// ------------------------------------------------------------
// 0x45B960 sub_45B960 —— 红黑树定位插入并回传 {迭代器, 是否新插}
// 先 lower_bound（v7 标向），未命中经 ·sub_45B740 插于下界，结果对写 pArg2 返回。
// ------------------------------------------------------------
int /*thiscall*/ sub_45B960(int **this, int pArg2, int *pDwArg3)  // sub_45B960 —— 红黑树定位插入并回传 {迭代器, 是否新插}
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
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v6 = fld_e1[1];  // fld_e1=this+4 宿主对象
  v7 = true;
  v13 = 1;
  if ( *(uint8_t *)(v6 + 21) == 0 )
  {
    v8 = *pDwArg3;
    do
    {
      v7 = v8 < *(uint32_t *)(v6 + 12);
      fld_e1 = (int *)v6;  // fld_e1=this+4 宿主对象
      v13 = v7;
      if ( v8 >= *(uint32_t *)(v6 + 12) )
        v6 = *(uint32_t *)(v6 + 8);  // 读字段 v6 = v6+8（nSkillRec8）
      else
        v6 = *(uint32_t *)v6;
    }
    while ( *(uint8_t *)(v6 + 21) == 0 );  // 写字段 v6+21（bArmorState） ← = 0 )
  }
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  pDwArg3 = fld_e1;  // fld_e1=this+4 宿主对象
  if ( v7 )
  {
    if ( fld_e1 == (int *)**(this + 1) )  // this+4〔宿主对象〕
    {
      v10 = *sub_45B740(this, (int *)&pDwArg3, 1, fld_e1, (int)pDwArg32);  // sub_45B740 —— STL 红黑树插入再平衡（节点 0x18）
      *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
      *(uint32_t *)pArg2 = v10;  // *pArg2 = v10
      return pArg2;
    }
    sub_4A3B30(&pDwArg3);  // 调 取后继再插
    fld_e12 = pDwArg3;
  }
  if ( fld_e12[3] >= *pDwArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // 写字段 pArg2+4（pHostObj） ← 0
    *(uint32_t *)pArg2 = fld_e12;  // *pArg2 = fld_e12
    return pArg2;
  }
  else
  {
    v12 = *sub_45B740(this, (int *)&pDwArg3, v13, fld_e1, (int)pDwArg32);  // sub_45B740 —— STL 红黑树插入再平衡（节点 0x18）
    *(uint32_t *)pArg2 = v12;  // *pArg2 = v12
    *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x45BA20 sub_45BA20 —— vector<uint32> 预留分配
// 清零三指针后按 n 分配 4n 字节（begin = end、cap 在尾）；n = 0 返回 0，超 0x3FFFFFFF 抛 ·sub_45B8F0。
// ------------------------------------------------------------
char /*thiscall*/ sub_45BA20(uint32_t *this, unsigned int uArg2)  // sub_45BA20 —— vector<uint32> 预留分配
{
  char *pMem; // eax

  *(this + 1) = 0;  // 写字段 this+1 ← 0
  *(this + 2) = 0;  // 写字段 this+2 ← 0
  *(this + 3) = 0;  // 写字段 this+3 ← 0
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x3FFFFFFF )
    sub_45B8F0(this);  // sub_45B8F0 —— 抛 std::length_error（vector<T> too long）
  pMem = (char *)operator new(4 * uArg2);  // 堆分配
  *(this + 3) = &pMem[4 * uArg2];  // 写字段 this+3 ← &pMem[4 * uArg2]
  *(this + 1) = pMem;  // 写字段 this+1 ← pMem
  *(this + 2) = pMem;  // 写字段 this+2 ← pMem
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x45BA80 sub_45BA80 —— vector<uint32> insert_n
// 位置 Src 起插 uArg3 个同值：容量足就地右移（·sub_55E7F0/5DAF70）并填充（·sub_49A9D0），
// 否则按 1.5 倍扩容重建（·sub_523700 补填）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_45BA80(int this, int Src, unsigned int uArg3, int *pDwArg4)  // sub_45BA80 —— vector<uint32> insert_n
{
  int pVecEnd_17; // edx
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

  pVecEnd_17 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  pDwArg4 = (int *)*pDwArg4;
  if ( pVecEnd_17 != 0 )  // fld_4=this+4 pHostObj
    result = (*(uint32_t *)(this + 12) - pVecEnd_17) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    result = 0;  // result=this+12 nSkillRec12
  if ( uArg3 != 0 )
  {
    if ( pVecEnd_17 != 0 )  // fld_4=this+4 pHostObj
      fld_8 = (*(uint32_t *)(this + 8) - pVecEnd_17) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_8 = 0;  // fld_8=this+8 nSkillRec8
    if ( 0x3FFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 nSkillRec8
      sub_45B8F0(this);  // sub_45B8F0 —— 抛 std::length_error（vector<T> too long）
    if ( pVecEnd_17 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - pVecEnd_17) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_82 = 0;  // fld_82=this+8 nSkillRec8
    if ( result >= uArg3 + fld_82 )  // result=this+12 nSkillRec12
    {
      fld_83 = *(uint8_t **)(this + 8);  // this+32〔nHeight(推断)〕
      v21 = (int)&fld_83[-Src] >> 2;  // fld_83=this+32 nHeight
      v22 = 4 * uArg3;  // 计算 v22 = 4 * uArg3
      v29 = (int)fld_83;  // fld_83=this+32 nHeight
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];  // fld_83=this+32 nHeight
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // sub_55E7F0 —— 商城状态（10 行）
        sub_5DAF70((void *)Src, v24, v29);  // sub_5DAF70 —— 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推得，尾段整体后移一格
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);  // sub_49A9D0 —— 区间填充（逐 uint32 写同值）
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));  // sub_55E7F0 —— 商城状态（10 行）
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);  // sub_523700 —— 填充补足尾段
        fld_84 = &Srca[*(uint32_t *)(this + 8)];  // this+8〔nSkillRec8(推断)〕等 2 字段
        *(uint32_t *)(this + 8) = fld_84;  // 写字段 this+8（nSkillRec8） ← fld_84
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);  // sub_49A9D0 —— 区间填充（逐 uint32 写同值）
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )  // result=this+12 nSkillRec12
        v10 = (result >> 1) + result;  // result=this+12 nSkillRec12
      else
        v10 = 0;
      if ( pVecEnd_17 != 0 )  // fld_4=this+4 pHostObj
        fld_85 = (*(uint32_t *)(this + 8) - pVecEnd_17) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_85 = 0;  // fld_85=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_85 )  // fld_85=this+8 nSkillRec8
      {
        if ( pVecEnd_17 != 0 )  // fld_4=this+4 pHostObj
          fld_86 = (*(uint32_t *)(this + 8) - pVecEnd_17) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else
          fld_86 = 0;  // fld_86=this+8 nSkillRec8
        v10 = uArg3 + fld_86;  // 计算 v10 = uArg3 + fld_86
      }
      v28 = 4 * v10;  // 计算 v28 = 4 * v10
      pMem = (char *)operator new(4 * v10);  // 堆分配
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);  // this+16〔nChannelTypeSel(推断)〕
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);  // sub_523700 —— 填充补足尾段
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));  // this+8〔nSkillRec8(推断)〕等 2 字段
      fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_87 = 0;  // fld_87=this+8 nSkillRec8
      v18 = fld_87 + uArg3;  // 计算 v18 = fld_87 + uArg3
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        j__free(*(void **)(this + 4));  // 释放堆块
      *(uint32_t *)(this + 12) = &pMem[v28];  // 写字段 this+12（nSkillRec12） ← &pMem[v28]
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // 写字段 this+8（nSkillRec8） ← &pMem[4 * v18]
      *(uint32_t *)(this + 4) = pMem;  // 写字段 this+4（pHostObj） ← pMem
      return (unsigned int)pMem;
    }
  }
  return result;  // result=this+12 nSkillRec12
}



// ------------------------------------------------------------
// 0x45BC60 sub_45BC60 —— 红黑树带提示插入（_Insert_hint 三态）
// 两端点/相邻键比较后转 ·sub_45B740（定位插）或 ·sub_45B960（下界查插）。
// ------------------------------------------------------------
int */*thiscall*/ sub_45BC60(int this, int *pDwArg2, int *pDwArg3, int *pDwArg4)  // sub_45BC60 —— 红黑树带提示插入（_Insert_hint 三态）
{
  int *fld_4; // eax
  int *pDwArg42; // esi
  int *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )  // this+8〔nSkillRec8(推断)〕等 2 字段
  {
    sub_45B740((int **)this, pDwArg2, 1, *(int **)(this + 4), (int)pDwArg4);  // sub_45B740 —— STL 红黑树插入再平衡（节点 0x18）
    return pDwArg2;
  }
  fld_4 = *(int **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  pDwArg42 = pDwArg4;
  if ( pDwArg3 == (int *)*fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    if ( *pDwArg4 < pDwArg3[3] )
    {
      sub_45B740((int **)this, pDwArg2, 1, pDwArg3, (int)pDwArg4);  // sub_45B740 —— STL 红黑树插入再平衡（节点 0x18）
      return pDwArg2;
    }
    goto LABEL_22;
  }
  if ( pDwArg3 == fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    v8 = (int *)fld_4[2];  // fld_4=this+16 nChannelTypeSel
    if ( v8[3] < *pDwArg4 )
    {
      sub_45B740((int **)this, pDwArg2, 0, v8, (int)pDwArg4);  // sub_45B740 —— STL 红黑树插入再平衡（节点 0x18）
      return pDwArg2;
    }
    goto LABEL_22;
  }
  if ( *pDwArg4 >= pDwArg3[3] || (pDwArg4 = pDwArg3, sub_4A3B30(&pDwArg4), pDwArg4[3] >= *pDwArg42) )  // 调 取后继再插
  {
    if ( pDwArg3[3] >= *pDwArg42 || (pDwArg4 = pDwArg3, sub_41C5E0(&pDwArg4), pDwArg4 != *(int **)(this + 4)) && *pDwArg42 >= pDwArg4[3] )  // sub_41C5E0 —— 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
    {
LABEL_22:
      v9 = *(uint32_t *)sub_45B960((int **)this, (int)v10, pDwArg42);  // sub_45B960 —— 红黑树定位插入并回传 {迭代器, 是否新插}
      *pDwArg2 = v9;
      return pDwArg2;
    }
    if ( *(uint8_t *)(pDwArg3[2] + 21) != 0 )
      sub_45B740((int **)this, pDwArg2, 0, pDwArg3, (int)pDwArg42);  // sub_45B740 —— STL 红黑树插入再平衡（节点 0x18）
    else
      sub_45B740((int **)this, pDwArg2, 1, pDwArg4, (int)pDwArg42);  // sub_45B740 —— STL 红黑树插入再平衡（节点 0x18）
    return pDwArg2;
  }
  else
  {
    if ( *(uint8_t *)(pDwArg4[2] + 21) != 0 )
      sub_45B740((int **)this, pDwArg2, 0, pDwArg4, (int)pDwArg42);  // sub_45B740 —— STL 红黑树插入再平衡（节点 0x18）
    else
      sub_45B740((int **)this, pDwArg2, 1, pDwArg3, (int)pDwArg42);  // sub_45B740 —— STL 红黑树插入再平衡（节点 0x18）
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x45BDC0 sub_45BDC0 —— vector<uint32> 拷贝赋值（构造语义）
// 按源(pArg2+4/+8) 计数 ·sub_45BA20 预留，再 ·sub_497E70 区间拷贝至 this。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45BDC0(uint32_t *this, int pArg2)  // sub_45BDC0 —— vector<uint32> 拷贝赋值（构造语义）
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

  v3 = *(uint32_t *)(pArg2 + 4);  // 读字段 v3 = pArg2+4（pHostObj）
  v11 = &v9;
  pThis = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2;  // pArg2+8〔nSkillRec8(推断)〕
  else
    v4 = 0;
  if ( sub_45BA20(this, v4) != 0 )  // sub_45BA20 —— vector<uint32> 预留分配
  {
    fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
    v7 = *(uint32_t *)(pArg2 + 8);  // 读字段 v7 = pArg2+8（nSkillRec8）
    v6 = *(uint32_t *)(pArg2 + 4);  // 读字段 v6 = pArg2+4（pHostObj）
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, fld_e1);  // sub_497E70 —— uint32 区间逐元素拷贝
  }
  return this;
}



// ------------------------------------------------------------
// 0x45BE60 sub_45BE60 —— 0x18 树 operator[]
// 下界命中（键相等）返回节点值 ·+16，否则以 {键, 0} 默认值经 ·sub_45BC60 插入。
// ------------------------------------------------------------
int /*thiscall*/ sub_45BE60(int **this, int *pDwArg2)  // sub_45BE60 —— 0x18 树 operator[]
{
  int *fld_e1; // edx
  int v3; // eax
  int v5[2]; // [esp+Ch] [ebp-8h] BYREF

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v3 = fld_e1[1];  // fld_e1=this+4 宿主对象
  while ( *(uint8_t *)(v3 + 21) == 0 )  // 当 *(uint8_t *)(v3 + 21) == 0 循环
  {
    if ( *(uint32_t *)(v3 + 12) >= *pDwArg2 )
    {
      fld_e1 = (int *)v3;  // fld_e1=this+4 宿主对象
      v3 = *(uint32_t *)v3;
    }
    else
    {
      v3 = *(uint32_t *)(v3 + 8);  // 读字段 v3 = v3+8（nSkillRec8）
    }
  }
  if ( fld_e1 != *(this + 1) && *pDwArg2 >= fld_e1[3] )  // fld_e1=this+4 宿主对象
    return (int)(fld_e1 + 4);  // fld_e1=this+4 宿主对象
  v5[0] = *pDwArg2;
  v5[1] = 0;
  return *sub_45BC60((int)this, (int *)&pDwArg2, fld_e1, v5) + 16;  // sub_45BC60 —— 红黑树带提示插入（_Insert_hint 三态）
}



// ------------------------------------------------------------
// 0x45BEE0 sub_45BEE0 —— 分配 0x24 节点（含四字节向量值）
// 字段 +0/+4/+8/+12 = 三参 + *pArg4；+16 起为 vector<uint32>（·sub_45BDC0 拷贝 pArg4+1）；+32 = pszArg5、+33 = 0。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_45BEE0(int nArg1, int nArg2, int nArg3, uint32_t *pArg4, char pszArg5)  // sub_45BEE0 —— 分配 0x24 节点（含四字节向量值）
{
  uint32_t *pMem; // eax
  uint32_t *pMem2; // esi
  void *v8[9]; // [esp+0h] [ebp-24h] BYREF

  v8[5] = v8;
  pMem = operator new(0x24u);  // 堆分配
  pMem2 = pMem;
  v8[4] = pMem;
  v8[8] = (void *)1;  // v8[8] = 转换(1)
  v8[3] = pMem;
  if ( pMem != nullptr )
  {
    *pMem = nArg1;
    pMem[1] = nArg2;
    pMem[2] = nArg3;
    pMem[3] = *pArg4;
    sub_45BDC0(pMem + 4, (int)(pArg4 + 1));  // sub_45BDC0 —— vector<uint32> 拷贝赋值（构造语义）
    *((uint8_t *)pMem2 + 32) = pszArg5;  // 写字段 pMem2+32（nHeight）
    *((uint8_t *)pMem2 + 33) = 0;  // 写字段 pMem2+33（bJobVecDirty）
  }
  return pMem2;
}



// ------------------------------------------------------------
// 0x45BF80 sub_45BF80 —— STL 红黑树插入再平衡（节点 0x24）
// ·sub_45BEE0 建节点，哨兵字节 ·+32，旋转用 0x24 版 ·sub_4331B0/433230；超 0xCCCCCCB 抛 map/set<T> too long。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45BF80(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, uint32_t *uArg5)  // sub_45BF80 —— STL 红黑树插入再平衡（节点 0x24）
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

  if ( (unsigned int)*(this + 2) >= 0xCCCCCCB )  // this+8〔nSkillRec8(推断)〕
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v20 = 0;
    sub_401740(v17);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject = &std::length_error::`vftable';  // vftable 复位
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  fld_e1 = sub_45BEE0(*(this + 1), (int)pArg4, *(this + 1), uArg5, 0);  // sub_45BEE0 —— 分配 0x24 节点（含四字节向量值）
  fld_e12 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( pArg4 == fld_e12 )  // fld_e12=this+4 宿主对象
  {
    fld_e12[1] = fld_e1;  // fld_e12=this+4 宿主对象
    *(uint32_t *)*(this + 1) = fld_e1;  // 写字段 this+1 ← fld_e1
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4〔宿主对象〕
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
    if ( pArg4 == (uint32_t *)*fld_e13 )  // fld_e13=this+4 宿主对象
      *fld_e13 = fld_e1;  // fld_e13=this+4 宿主对象
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )  // fld_e14=this+4 宿主对象
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // 写字段 fld_e14+8（nSkillRec8） ← fld_e1
  }
  v10 = fld_e1 + 1;  // 计算 v10 = fld_e1 + 1
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
            sub_4331B0(this, *v10);  // sub_4331B0 —— 红黑树左旋（节点 0x24 版）
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 32) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 32) = 0;
          sub_433230(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));  // sub_433230 —— 红黑树右旋（节点 0x24 版）
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 32) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_433230(this, (uint32_t *)*v10);  // sub_433230 —— 红黑树右旋（节点 0x24 版）
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 32) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 32) = 0;
        sub_4331B0(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));  // sub_4331B0 —— 红黑树左旋（节点 0x24 版）
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 32) = 1;
      *(uint8_t *)(v14 + 32) = 1;  // 写字段 v14+32（nHeight） ← 1
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
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 32) = 1;  // this+4〔宿主对象〕
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x45C130 sub_45C130 —— 0x24 树定位插入（回传 {迭代器, 是否新插}）
// lower_bound 后用 ·sub_45B1F0 迭代器自增，未命中经 ·sub_45BF80 插入。
// ------------------------------------------------------------
int /*thiscall*/ sub_45C130(int *this, int pArg2, uint32_t *uArg3)  // sub_45C130 —— 0x24 树定位插入（回传 {迭代器, 是否新插}）
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
  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  v6 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 33) == 0 )
  {
    v8 = *uArg3;
    do
    {
      v7 = v8 < v6[3];
      fld_e1 = v6;  // fld_e1=this+4 宿主对象
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 33) == 0 );
  }
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  uArg3 = fld_e1;  // fld_e1=this+4 宿主对象
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )  // this+4〔宿主对象〕
    {
      v10 = *sub_45BF80(this, &uArg3, 1, fld_e1, uArg32);  // sub_45BF80 —— STL 红黑树插入再平衡（节点 0x24）
      *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
      *(uint32_t *)pArg2 = v10;  // *pArg2 = v10
      return pArg2;
    }
    sub_45B1F0(&uArg3);  // sub_45B1F0 —— STL 红黑树迭代器自增
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // 写字段 pArg2+4（pHostObj） ← 0
    *(uint32_t *)pArg2 = fld_e12;  // *pArg2 = fld_e12
    return pArg2;
  }
  else
  {
    v12 = *sub_45BF80(this, &uArg3, v13, fld_e1, uArg32);  // sub_45BF80 —— STL 红黑树插入再平衡（节点 0x24）
    *(uint32_t *)pArg2 = v12;  // *pArg2 = v12
    *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x45C1F0 sub_45C1F0 —— 与 ·sub_45BC60 同构（差异：0x24 节点 / ·sub_45B1F0 / ·sub_45BF80）
// 节点尺寸 0x24 之树的带提示插入实现（·sub_45C350 调用）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45C1F0(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)  // sub_45C1F0 —— 与 ·sub_45BC60 同构（差异：0x24 节点 / ·sub_45B1F0 / ·sub_45BF80）
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )  // this+8〔nSkillRec8(推断)〕等 2 字段
  {
    sub_45BF80((int *)this, uArg2, 1, *(uint32_t **)(this + 4), pArg4);  // sub_45BF80 —— STL 红黑树插入再平衡（节点 0x24）
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_45BF80((int *)this, uArg2, 1, pArg3, pArg4);  // sub_45BF80 —— STL 红黑树插入再平衡（节点 0x24）
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    v8 = (uint32_t *)fld_4[2];  // fld_4=this+16 nChannelTypeSel
    if ( v8[3] < *pArg4 )
    {
      sub_45BF80((int *)this, uArg2, 0, v8, pArg4);  // sub_45BF80 —— STL 红黑树插入再平衡（节点 0x24）
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_45B1F0(&pArg4), pArg4[3] >= *pArg42) )  // sub_45B1F0 —— STL 红黑树迭代器自增
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_41C640(&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )  // sub_41C640 —— 红黑树迭代器自增（_Inc 实例二，nil 标志 +33）
    {
LABEL_22:
      v9 = *(uint32_t *)sub_45C130((int *)this, (int)v10, pArg42);  // sub_45C130 —— 0x24 树定位插入（回传 {迭代器, 是否新插}）
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 33) != 0 )
      sub_45BF80((int *)this, uArg2, 0, pArg3, pArg42);  // sub_45BF80 —— STL 红黑树插入再平衡（节点 0x24）
    else
      sub_45BF80((int *)this, uArg2, 1, pArg4, pArg42);  // sub_45BF80 —— STL 红黑树插入再平衡（节点 0x24）
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 33) != 0 )
      sub_45BF80((int *)this, uArg2, 0, pArg4, pArg42);  // sub_45BF80 —— STL 红黑树插入再平衡（节点 0x24）
    else
      sub_45BF80((int *)this, uArg2, 1, pArg3, pArg42);  // sub_45BF80 —— STL 红黑树插入再平衡（节点 0x24）
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x45C350 sub_45C350 —— 0x24 树 operator[]
// 下界命中（哨兵 ·+33）返回节点值 ·+16；未命中构 {键, 0, 空向量} 经 ·sub_45C1F0 插入。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45C350(uint32_t *this, int *pDwArg2)  // sub_45C350 —— 0x24 树 operator[]
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

  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  v4 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  while ( *((uint8_t *)v4 + 33) == 0 )  // 当 *((uint8_t *)v4 + 33) == 0 循环
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
    sub_45BDC0(&v8, (int)v10);  // sub_45BDC0 —— vector<uint32> 拷贝赋值（构造语义）
    LOBYTE(v14) = 1;
    fld_e12 = (uint32_t *)*sub_45C1F0((int)this, &pDwArg2, fld_e12, &v7);  // sub_45C1F0 —— 与 ·sub_45BC60 同构（差异：0x24 节点 / ·sub_45B1F0 / ·sub_45BF80）
    if ( Block != nullptr )
      j__free(Block);  // 释放堆块
  }
  return fld_e12 + 4;  // 返回内嵌子对象/缓冲指针（fld_e12+4）
}



// ------------------------------------------------------------
// 0x45C400 sub_45C400 —— NPC 归属重建（房间 → 对象）
// 遍历 ·+56 树各房间的 NPC 向量（·__RTDynamicCast 到 CNRDNpc）：·vt+336 id 与本端 ·+92 不符者经 ·sub_45C350 取/建
// 房间记录后 ·sub_45BA80 追加；命中本端者以 ·sub_45FE80 重新注册并从原房间移除（配对树 ·+80 侧）。
// ------------------------------------------------------------
char /*thiscall*/ sub_45C400(uint32_t *this)  // sub_45C400 —— NPC 归属重建（房间 → 对象）
{
  int *fld_e14; // eax
  int *fld_e1422; // edi
  bool v3; // zf
  int v4; // esi
  int v5; // ecx
  unsigned int v6; // edx
  int v7; // ecx
  uint32_t *v8; // eax
  uint8_t *pObj; // eax
  uint8_t *pObj3; // edi
  int v11; // eax
  uint32_t *pThis2; // ebx
  int v13; // eax
  int v14; // edx
  unsigned int v15; // ebx
  uint32_t *pObj32; // ecx
  int v17; // ebx
  int *v18; // edi
  int v19; // eax
  uint32_t *pThis3; // esi
  int pObj2; // esi
  int v22; // eax
  int *fld_e143; // ecx
  int v25; // [esp-18h] [ebp-48h]
  int v26; // [esp-14h] [ebp-44h]
  char v27[4]; // [esp+4h] [ebp-2Ch] BYREF
  char v28[4]; // [esp+8h] [ebp-28h] BYREF
  int v29; // [esp+Ch] [ebp-24h]
  int v30; // [esp+10h] [ebp-20h] BYREF
  int v31; // [esp+14h] [ebp-1Ch] BYREF
  int v32; // [esp+18h] [ebp-18h] BYREF
  int v33; // [esp+1Ch] [ebp-14h] BYREF
  int v34; // [esp+20h] [ebp-10h]
  void *Src; // [esp+24h] [ebp-Ch]
  uint32_t *pThis; // [esp+28h] [ebp-8h]
  int *fld_e142; // [esp+2Ch] [ebp-4h]

  fld_e14 = (int *)*(this + 14);  // this+56〔pCmdVecCap56(推断)〕
  fld_e1422 = (int *)*fld_e14;  // fld_e14=this+56 pCmdVecCap56
  v3 = *fld_e14 == (uint32_t)fld_e14;  // fld_e14=this+56 pCmdVecCap56
  pThis = this;
  fld_e142 = fld_e1422;
  if ( !v3 )
  {
    do
    {
      v4 = fld_e1422[4];
      v5 = *(uint32_t *)(v4 + 8);  // 读字段 v5 = v4+8（nSkillRec8）
      v6 = 0;
      v33 = fld_e1422[3];
      v29 = v4;
      if ( v5 != 0 )
        Src = (void *)((*(uint32_t *)(v4 + 12) - v5) >> 2);
      else
        Src = nullptr;
      v34 = 0;
      if ( (int)Src > 0 )
      {
        do
        {
          v7 = *(uint32_t *)(v4 + 8);  // 读字段 v7 = v4+8（nSkillRec8）
          if ( v7 != 0 && v6 < (*(uint32_t *)(v4 + 12) - v7) >> 2 )
            v8 = *(uint32_t **)(v7 + 4 * v6);
          else
            v8 = nullptr;
          pObj = __RTDynamicCast(v8, 0, &CNRDObject `RTTI Type Descriptor', &CNRDNpc `RTTI Type Descriptor', 0);  // pObj = 调 __RTDynamicCast
          pObj3 = pObj;
          v31 = (int)pObj;
          if ( pObj != nullptr )
          {
            v11 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 336))(pObj);  // 虚调用 vt+336（pObj 虚表槽）
            pThis2 = pThis;
            v32 = v11;
            if ( *(uint32_t *)sub_472E30(v28, &v32) != pThis2[23] )  // 调 +13 现值比对，返回是否变更。
            {
              sub_45F1E0(pObj3);  // sub_45F1E0 —— 对象注销/退场（递归，含 ELVEN_GATE 检查）
              v13 = sub_45C350(&v33);  // sub_45C350 —— 0x24 树 operator[]
              v14 = *(uint32_t *)(v13 + 4);  // 读字段 v14 = v13+4（pHostObj）
              if ( v14 != 0 )
                v15 = (*(uint32_t *)(v13 + 8) - v14) >> 2;
              else
                v15 = 0;
              if ( v14 != 0 && v15 < (*(uint32_t *)(v13 + 12) - v14) >> 2 )
              {
                pObj32 = *(uint32_t **)(v13 + 8);
                *pObj32 = pObj3;
                *(uint32_t *)(v13 + 8) = pObj32 + 1;  // 写字段 v13+8（nSkillRec8） ← pObj32 + 1
              }
              else
              {
                sub_45BA80(*(void **)(v13 + 8), 1, (int)&v31);  // sub_45BA80 —— vector<uint32> insert_n
              }
            }
          }
          v6 = ++v34;
        }
        while ( v34 < (int)Src );
        fld_e1422 = fld_e142;
      }
      sub_45B6D0(&v30, &v33);  // sub_45B6D0 —— 与 ·sub_45B660 同构（差异：哨兵字节 ·+33）
      v17 = v30;
      if ( v30 != pThis[20] )
      {
        v18 = *(int **)(v30 + 20);
        if ( v18 != *(int **)(v30 + 24) )
        {
          Src = v18 + 1;
          do
          {
            v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)*v18 + 336))(*v18);  // 虚调用 vt+336（v18 虚表槽）
            pThis3 = pThis;
            v31 = v19;
            if ( *(uint32_t *)sub_472E30(v27, &v31) == pThis3[23] )  // 调 +13 现值比对，返回是否变更。
            {
              pObj2 = *v18;
              v26 = *v18;
              v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)*v18 + 52))(*v18);  // 虚调用 vt+52（v18）归属坐标y
              v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);  // 虚调用 vt+48（pObj2）归属坐标x
              sub_45FE80(v29, (int)v18, v22, v25, v26, 0, 0);  // sub_45FE80 —— 对象注册
              memcpy_0(v18, Src, 4 * ((*(uint32_t *)(v17 + 24) - (int)Src) >> 2));
              *(uint32_t *)(v17 + 24) -= 4;  // 字段 v17+24（nPageMax） -= 4
            }
            else
            {
              ++v18;  // 计数自增 v18
              Src = (char *)Src + 4;
            }
          }
          while ( v18 != *(int **)(v17 + 24) );
        }
        fld_e1422 = fld_e142;
      }
      LOBYTE(fld_e14) = *((uint8_t *)fld_e1422 + 21);  // fld_e14=this+56 pCmdVecCap56
      if ( (uint8_t)fld_e14 == 0 )  // fld_e14=this+56 pCmdVecCap56
      {
        fld_e143 = (int *)fld_e1422[2];
        if ( *((uint8_t *)fld_e143 + 21) != 0 )
        {
          fld_e14 = (int *)fld_e1422[1];  // fld_e14=this+56 pCmdVecCap56
          if ( *((uint8_t *)fld_e14 + 21) == 0 )  // fld_e14=this+56 pCmdVecCap56
          {
            while ( fld_e1422 == (int *)fld_e14[2] )  // 当 fld_e1422 == (int *)fld_e14[2] 循环
            {
              fld_e142 = fld_e14;  // fld_e14=this+56 pCmdVecCap56
              fld_e14 = (int *)fld_e14[1];  // fld_e14=this+56 pCmdVecCap56
              if ( *((uint8_t *)fld_e14 + 21) != 0 )  // fld_e14=this+56 pCmdVecCap56
                break;
              fld_e1422 = fld_e142;
            }
          }
          fld_e142 = fld_e14;  // fld_e14=this+56 pCmdVecCap56
        }
        else
        {
          fld_e14 = (int *)*fld_e143;  // fld_e14=this+56 pCmdVecCap56
          if ( *(uint8_t *)(*fld_e143 + 21) == 0 )
          {
            do
            {
              fld_e143 = fld_e14;  // fld_e14=this+56 pCmdVecCap56
              fld_e14 = (int *)*fld_e14;  // fld_e14=this+56 pCmdVecCap56
            }
            while ( *((uint8_t *)fld_e14 + 21) == 0 );  // fld_e14=this+56 pCmdVecCap56
          }
          fld_e142 = fld_e143;
        }
        fld_e1422 = fld_e142;
      }
    }
    while ( fld_e1422 != (int *)pThis[14] );
  }
  return (char)fld_e14;  // fld_e14=this+56 pCmdVecCap56
}


// ------------------------------------------------------------
// 0x45C640 sub_45C640 —— 延迟构造（·+4 首次置 1）
// 建控件 0x68(+12)、战场对象 0x558(+44) 与 0x1F0(+48，挂入 ·+44 的 +108)；
// 逐子控件 ·sub_69A840 上屏后调 ·sub_45B250 复位。
// ------------------------------------------------------------
char /*thiscall*/ sub_45C640(int this)  // sub_45C640 —— 延迟构造（·+4 首次置 1）
{
  char result; // al
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  char *pMem2; // eax
  char *v6; // eax
  void *pMem3; // eax
  void *v8; // eax
  int fld_2C; // ecx

  result = *(uint8_t *)(this + 4);  // 读字段 result = this+4（pHostObj）
  if ( result == 0 )  // result=this+4 pHostObj
  {
    *(uint8_t *)(this + 4) = 1;  // 写字段 this+4（pHostObj） ← 1
    pMem = operator new(0x68u);  // 堆分配
    if ( pMem != nullptr )
      v4 = sub_426BD0(pMem);  // sub_426BD0 —— nengine::IControl 构造
    else
      v4 = nullptr;
    *(uint32_t *)(this + 12) = v4;  // 写字段 this+12（nSkillRec12） ← v4
    pMem2 = (char *)operator new(0x558u);  // 堆分配
    if ( pMem2 != nullptr )
      v6 = sub_42B7E0(pMem2);  // 调 ：= 评价/横幅对象大构造器（36 字节槽组 ×N，尾调 0x423C10 复位评价值）
    else
      v6 = nullptr;
    *(uint32_t *)(this + 44) = v6;  // 写字段 this+44（nExpireMs） ← v6
    pMem3 = operator new(0x1F0u);  // 堆分配
    if ( pMem3 != nullptr )
      v8 = sub_452B10(pMem3);  // sub_452B10 —— 战场对象主体构造
    else
      v8 = nullptr;
    fld_2C = *(uint32_t *)(this + 44);  // 读字段 fld_2C = this+44（nExpireMs）
    *(uint32_t *)(this + 48) = v8;  // 写字段 this+48（pCmdVecBegin48） ← v8
    *(uint32_t *)(fld_2C + 108) = v8;  // 写字段 fld_2C+108（nAdd108） ← v8
    sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 44) + 36));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    sub_69A840(*((uint32_t *)dword_8F8528 + 2));  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    sub_69A840(*((uint32_t *)dword_8F8528 + 3));  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 44) + 40));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    return sub_45B250(this);  // sub_45B250 —— 激活态重置 + 锚定当前角色
  }
  return result;  // result=this+4 pHostObj
}



// ------------------------------------------------------------
// 0x45C770 sub_45C770 —— 按 (地图, 索引) 取/建 0x208 关卡对象
// 键 = ArgList 高 16 位 + Block 低 16 位，查树 ·+64（·sub_472E30/登记 ·sub_45BE60）；
// 未命中查房间对象(·sub_4CE8A0)+96 的条目（缺则 aCriticalError_7），以 ·sub_452B60 依条目标识建 0x208。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45C770(int **this, unsigned int ArgList, unsigned int Block)  // sub_45C770 —— 按 (地图, 索引) 取/建 0x208 关卡对象
{
  unsigned int v3; // edi
  int **pThis_10; // ebx
  int v6; // esi
  int *v8; // eax
  int *v9; // esi
  uint32_t *pMem; // eax
  uint32_t *v11; // esi
  int *v12; // [esp+Ch] [ebp-10h] BYREF
  int v13; // [esp+18h] [ebp-4h]

  v3 = ArgList;
  pThis_10 = this + 16;  // this+16 频道型选中索引
  ArgList = Block | (ArgList << 16);
  sub_472E30(&v12, &ArgList);  // 调 +13 现值比对，返回是否变更。
  if ( v12 != *(this + 17) )  // this+68〔nCharCount(推断)〕
    return (uint32_t *)v12[4];
  v6 = sub_4CE8A0(v3);  // sub_4CE8A0 —— 调用 sub_4CE8A0
  if ( v6 != 0 )
  {
    sub_45B660((int **)(v6 + 96), &v12, &Block);  // sub_45B660 —— STL 红黑树 lower_bound（哨兵 ·+69）
    v8 = *(int **)(v6 + 100);
    v9 = v12;
    if ( v12 == v8 )
    {
      off_77F3FC(aCriticalError_7, v3, Block);  // off_77F3FC —— 日志打印（printf 风格）
      return nullptr;
    }
    else
    {
      pMem = operator new(0x208u);  // 堆分配
      Block = (unsigned int)pMem;
      v13 = 0;
      if ( pMem != nullptr )
      {
        if ( (unsigned int)v9[11] < 0x10 )
          v11 = sub_452B60(pMem, (uint8_t)v9 + 24, 0);  // 调 取词条 → dword_8F84B8 vt+60 载入 .map → 场景层创建
        else
          v11 = sub_452B60(pMem, v9[6], 0);  // 调 取词条 → dword_8F84B8 vt+60 载入 .map → 场景层创建
      }
      else
      {
        v11 = nullptr;
      }
      v13 = -1;
      *(uint32_t *)sub_45BE60(pThis_10, (int *)&ArgList) = v11;  // sub_45BE60 —— 0x18 树 operator[]
      return v11;
    }
  }
  else
  {
    off_77F3FC(aCriticalError_5, v3);  // off_77F3FC —— 日志打印（printf 风格）
    return nullptr;
  }
}



// ------------------------------------------------------------
// 0x45C8C0 sub_45C8C0 —— 按 (地图, 索引) 取/建 0xA0 战斗条目
// 树 ·+52 未命中：·sub_42D590 建条目、·sub_45C770 取关卡并 ·sub_4602C0 初始化其 +476，再登记；
// 管理器激活(·+96)时顺带触发 ·sub_45C400 归属重建。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45C8C0(int this, unsigned int ArgList, unsigned int uArg3)  // sub_45C8C0 —— 按 (地图, 索引) 取/建 0xA0 战斗条目
{
  int **pThis_34; // ebx
  uint32_t *pMem; // eax
  uint32_t *v6; // edi
  uint32_t *v7; // eax
  void *Block; // [esp+8h] [ebp-14h] BYREF
  unsigned int v10; // [esp+Ch] [ebp-10h] BYREF
  int v11; // [esp+18h] [ebp-4h]

  pThis_34 = (int **)(this + 52);  // this+208〔nField208(推断)〕
  v10 = uArg3 | (ArgList << 16);
  sub_472E30(&Block, &v10);  // 调 +13 现值比对，返回是否变更。
  if ( Block != *(void **)(this + 56) )  // this+224〔nSnapDst224(推断)〕
    return *((uint32_t **)Block + 4);
  pMem = operator new(0xA0u);  // 堆分配
  Block = pMem;
  v6 = nullptr;
  v11 = 0;
  if ( pMem != nullptr )
    v6 = sub_42D590(pMem, 1);  // sub_42D590 —— 战斗条目构造（0xA0）
  v11 = -1;
  v7 = sub_45C770((int **)this, ArgList, uArg3);  // sub_45C770 —— 按 (地图, 索引) 取/建 0x208 关卡对象
  sub_4602C0(v7[119]);  // sub_4602C0 —— 图标容器批量实例化
  *(uint32_t *)sub_45BE60(pThis_34, (int *)&v10) = v6;  // sub_45BE60 —— 0x18 树 operator[]
  if ( *(uint32_t *)(this + 96) != 0 )  // this+96〔nStatusMode(推断)〕等 2 字段
    sub_45C400((int **)this);  // sub_45C400 —— NPC 归属重建（房间 → 对象）
  return v6;
}



// ------------------------------------------------------------
// 0x45C9A0 sub_45C9A0 —— CNRoomListModule 关停/析构
// ·+4 置 0 后：·+12 控件自毁、·+44/·+48 战场对象与块经 ·sub_42BD40/42E940 释放；
// 遍历 ·+56 树 ·sub_42C770 释放战斗条目、·+68 树 ·sub_42EDE0 释放战场块、·+80 树逐元素 vt[0](1) 自毁。
// ------------------------------------------------------------
char /*thiscall*/ sub_45C9A0(int this)  // sub_45C9A0 —— CNRoomListModule 关停/析构
{
  uint32_t *pThis; // edi
  int *k; // eax
  void (/*thiscall*/ ***pThis_C)(uint32_t, int); // ecx
  void *v4; // esi
  void *v5; // esi
  int *v6; // eax
  int v7; // esi
  void *v8; // edi
  uint32_t *v9; // eax
  uint32_t *v10; // esi
  void *v11; // edi
  bool v12; // zf
  int **v13; // eax
  int *j; // eax
  int i; // eax
  int *v16; // esi
  int *v17; // edi
  int **v18; // eax
  int *v20; // [esp+8h] [ebp-8h] BYREF
  uint32_t *pThis2; // [esp+Ch] [ebp-4h]

  pThis = (uint32_t *)this;
  LOBYTE(k) = *(uint8_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  pThis2 = (uint32_t *)this;
  if ( (uint8_t)k != 0 )
  {
    pThis_C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
    *((uint8_t *)pThis + 4) = 0;  // 写字段 pThis+4（pHostObj）
    if ( pThis_C != nullptr )  // pThis_C=this+48 pCmdVecBegin48
      (**pThis_C)(pThis_C, 1);  // 调 pThis_C 的虚函数（vt+0）
    v4 = (void *)pThis[11];
    pThis[3] = 0;
    if ( v4 != nullptr )
    {
      sub_42BD40(v4);  // sub_42BD40 —— CNRDStage 析构（对应 ·0x42B7E0 构造）
      j__free(v4);  // 释放堆块
    }
    v5 = (void *)pThis[12];
    pThis[11] = 0;
    if ( v5 != nullptr )
    {
      sub_42E940(v5);  // sub_42E940 —— 析构（0x1F0）
      j__free(v5);  // 释放堆块
    }
    v6 = (int *)pThis[14];
    pThis[12] = 0;
    v7 = *v6;
    v20 = (int *)*v6;
    if ( v20 != v6 )
    {
      do
      {
        v8 = *(void **)(v7 + 16);
        if ( v8 != nullptr )
        {
          sub_42C770(*(uint32_t *)(v7 + 16));  // sub_42C770 —— 战斗条目析构
          j__free(v8);  // 释放堆块
        }
        *(uint32_t *)(v7 + 16) = 0;  // 写字段 v7+16（nChannelTypeSel） ← 0
        sub_41C5E0((int *)&v20);  // sub_41C5E0 —— 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
        v7 = (int)v20;
      }
      while ( v20 != (int *)pThis2[14] );
      pThis = pThis2;
    }
    v9 = (uint32_t *)pThis[17];
    v10 = (uint32_t *)*v9;
    if ( (uint32_t *)*v9 != v9 )
    {
      do
      {
        v11 = (void *)v10[4];
        if ( v11 != nullptr )
        {
          sub_42EDE0(v10[4]);  // sub_42EDE0 —— 战场块析构
          j__free(v11);  // 释放堆块
        }
        v12 = *((uint8_t *)v10 + 21) == 0;
        v10[4] = 0;
        if ( v12 )
        {
          v13 = (int **)v10[2];
          if ( *((uint8_t *)v13 + 21) != 0 )
          {
            for ( i = v10[1]; *(uint8_t *)(i + 21) == 0; i = *(uint32_t *)(i + 4) )
            {
              if ( v10 != *(uint32_t **)(i + 8) )
                break;
              v10 = (uint32_t *)i;
            }
            v10 = (uint32_t *)i;
          }
          else
          {
            v10 = (uint32_t *)v10[2];
            for ( j = *v13; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              v10 = j;
          }
        }
      }
      while ( v10 != (uint32_t *)pThis2[17] );
      pThis = pThis2;
    }
    k = (int *)pThis[20];
    v16 = (int *)*k;
    if ( (int *)*k != k )
    {
      do
      {
        v17 = (int *)v16[5];
        if ( v17 != (int *)v16[6] )
        {
          do
          {
            if ( *v17 != 0 )
              (**(void (/*thiscall*/ ***)(int, int))*v17)(*v17, 1);
            *v17 = 0;
            k = (int *)v16[6];
            ++v17;  // 计数自增 v17
          }
          while ( v17 != k );  // 循环直到 v17 != k
        }
        if ( *((uint8_t *)v16 + 33) == 0 )
        {
          v18 = (int **)v16[2];
          if ( *((uint8_t *)v18 + 33) != 0 )
          {
            for ( k = (int *)v16[1]; *((uint8_t *)k + 33) == 0; k = (int *)k[1] )
            {
              if ( v16 != (int *)k[2] )
                break;
              v16 = k;
            }
            v16 = k;
          }
          else
          {
            v16 = (int *)v16[2];
            for ( k = *v18; *((uint8_t *)k + 33) == 0; k = (int *)*k )
              v16 = k;
          }
        }
      }
      while ( v16 != (int *)pThis2[20] );
    }
  }
  return (char)k;
}


// ------------------------------------------------------------
// 0x45CB30 CNRoomListModule__vmt4
// ------------------------------------------------------------
// CNRoomListModule::vmt4 —— 房间列表帧处理（RTTI 自证）
char /*thiscall*/ sub_45CB30(int this)  // 【CNRoomListModule__vmt4】
{
  int v2; // esi
  int pSelRoomWnd; // eax  | +0x0098 → ★ 选中房间窗口（CNRoomListModule；va=0045CB30）
  int pThis_10; // eax
  uint8_t v5; // al
  int pObj; // esi
  int pRoomListCtrl; // eax  | +0x0068 → ★ 房间列表控件（CNRoomListModule；va=0045CB30）
  int v8; // eax
  int v9; // ebx
  bool nCurRoomId; // zf  | +0x006C → ★ 当前房间 id（CNRoomListModule；va=0045CB30）
  int v11; // esi
  int v12; // esi
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  uint32_t *v16; // ebx
  char *v17; // eax
  int pObj2; // esi
  int v19; // ebx
  int v20; // eax
  int v21; // ebx
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  int v25; // ebx
  int v26; // ebx
  int v27; // eax
  int v28; // eax
  unsigned int v29; // esi
  void *v30; // edx
  unsigned int v31; // ebx
  uint32_t *pRoomListCtrl_; // eax
  int *pRoomListCtrl_2; // edx
  int v34; // edx
  int v35; // eax
  int v36; // eax
  char *v37; // eax
  unsigned int nRand; // esi
  unsigned int v39; // ebx
  uint32_t *v40; // ebx
  int v41; // eax
  uint64_t v42; // rax
  int pThis_7C; // eax
  int v45; // [esp-4h] [ebp-A8h]
  int v46; // [esp+Ch] [ebp-98h] BYREF
  int v47; // [esp+10h] [ebp-94h] BYREF
  int v48; // [esp+14h] [ebp-90h]
  void *Block; // [esp+18h] [ebp-8Ch] BYREF
  char v50[4]; // [esp+1Ch] [ebp-88h] BYREF
  char Buffer[128]; // [esp+20h] [ebp-84h] BYREF
  int dword_796E502; // [esp+A0h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  sub_433690();  // 【= 主帧 tick（timeGetTime 驱动；'SHUTTER_ON' 截屏音效…】
  v2 = 0;
  if ( *(uint8_t *)(*((uint32_t *)dword_8F8528 + 625) + 44) != 0 )  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    v2 = sub_45E870(pt.x, pt.y, 1);  // sub_45E870 —— 结果 = 光标点选对象（倒序遍历 ·+40 表）
  pSelRoomWnd = *(uint32_t *)(this + 152);  // 读字段 fld_98 = this+152（nAdd152）
  if ( pSelRoomWnd != v2 )  // fld_98=this+152 nAdd152
  {
    if ( pSelRoomWnd != 0 && (uint8_t)sub_45E680(*(uint32_t *)(this + 152)) != 0 )  // sub_45E680 —— 对象表归属判定
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(**(uint32_t **)(this + 152) + 284))(  // this+152〔pSelRoomWnd〕
        *(uint32_t *)(this + 152),  // this+152〔pSelRoomWnd〕
        0,
        0,
        1,
        2);
    *(uint32_t *)(this + 152) = v2;  // 写字段 this+152（nAdd152） ← v2
  }
  if ( *(uint32_t *)(this + 152) != 0 )  // this+152〔pSelRoomWnd〕
  {
    pThis_10 = sub_699000(this + 16);  // 【clock_now(clk)】
    v5 = sub_42B420(100, 255, pThis_10, 500);  // sub_42B420 —— 结果 = 往返插值（三角波）
    (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, int))(**(uint32_t **)(this + 152) + 284))(  // this+152〔pSelRoomWnd〕
      *(uint32_t *)(this + 152),  // this+152〔pSelRoomWnd〕
      1,
      (v5 << 24) | 0xFF9B,
      0,
      1);
  }
  pObj = dword_8F7C08;  // dword_8F7C08 —— 副玩家/观战
  if ( dword_8F7C08 != 0 )  // dword_8F7C08 —— 副玩家/观战
  {
    if ( *(uint8_t *)(this + 116) == 0 )  // this+116〔bFirstTick〕
    {
      pRoomListCtrl = *(uint32_t *)(this + 104);  // 读字段 fld_68 = this+104（nTimerEnd）
      if ( pRoomListCtrl != 0 && *(uint32_t *)(pRoomListCtrl + 32) != 1 && sub_699000(this + 16) > *(uint32_t *)(this + 112) + 1000 )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 虚调用 vt+376（pObj 虚表槽）
        *(uint32_t *)(this + 112) = sub_699000(this + 16);  // sub_699000 —— 【clock_now(clk)】
      }
    }
    if ( (uint8_t)sub_45E680(pObj) != 0 )  // sub_45E680 —— 对象表归属判定
    {
      v8 = sub_48C860(pObj);  // sub_48C860 —— 按坐标查覆盖矩形记录（this+54 表）
      v9 = v8;
      nCurRoomId = *(uint32_t *)(this + 108) == v8;  // 写字段 this+108（nAdd108） ← = v8
      v48 = v8;
      if ( nCurRoomId || v8 == 0 )
        goto LABEL_36;
      if ( *(uint32_t *)(v8 + 16) == -1 )
      {
        v11 = sub_429830((uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
        if ( sub_423B10(dword_8F850C) != v11 || (uint8_t)sub_45B500(this) == 0 )  // sub_423B10 —— 本机槽元素取用；sub_45B500 —— 世界地图装载校验（WORLD MAP LOAD FAIL 自证）
          goto LABEL_36;
        v12 = 0;
        v13 = 16;
        while ( 1 )
        {
          if ( sub_445080(v12) != 0 )  // sub_445080 —— 槽位表值查询
          {
            v16 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
            v17 = sub_422E70(532);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
            goto LABEL_31;
          }
          v14 = *(uint32_t *)(v13 + dword_8F850C);  // dword_8F850C —— 队伍槽重置 4 槽 +188 解锁清空 → 自身
          if ( v14 != 0 )
          {
            v15 = *(uint32_t *)(v14 + 192);  // 读字段 v15 = v14+192（nDlgId）
            if ( v15 == 0 || (uint8_t)sub_45E680(v15) == 0 )  // sub_45E680 —— 对象表归属判定
              break;
          }
          v13 += 4;
          ++v12;  // 计数自增 v12
          if ( v13 >= 32 )
            goto LABEL_32;
        }
        v16 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
        v17 = sub_422E70(533);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
LABEL_31:
        sub_43BEE0(v16, (int)v17, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
LABEL_32:
        if ( v12 != 4 )
        {
LABEL_35:
          v9 = v48;
LABEL_36:
          *(uint32_t *)(this + 108) = v9;  // 写字段 this+108（nAdd108） ← v9
          goto LABEL_37;
        }
        sub_423200(dword_8F7B08, 15);  // 【发送网络包API】
      }
      else
      {
        if ( (uint8_t)sub_45B170(*(uint32_t *)(v8 + 16)) == 0 )  // sub_45B170 —— 房间对象可用判定
        {
          if ( (uint8_t)sub_5460F0(*(uint32_t *)(v9 + 16)) == 0 )  // sub_5460F0 —— 引导辅助 2（44E8D0）
          {
            v35 = sub_4CE8A0(*(uint32_t *)(v9 + 16));  // sub_4CE8A0 —— 调用 sub_4CE8A0
            if ( v35 != 0 )
            {
              if ( *(uint32_t *)(v35 + 28) < 0x10u )
                v36 = v35 + 8;  // 计算 v36 = v35 + 8
              else
                v36 = *(uint32_t *)(v35 + 8);  // 读字段 v36 = v35+8（nSkillRec8）
              v45 = v36;
              v37 = sub_422E70(534);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
              sprintf(Buffer, v37, v45);  // 调 格式化到缓冲
              sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
            }
          }
          goto LABEL_36;
        }
        v30 = *(void **)(v48 + 20);
        v31 = *(uint32_t *)(v9 + 16);  // 读字段 v31 = v9+16（nChannelTypeSel）
        v47 = 0;
        v46 = 0;
        Block = v30;
        if ( (uint8_t)sub_41C590(dword_8F7A24) != 0 )  // sub_41C590 —— 状态查询（this+348 == 4）
        {
          pRoomListCtrl_ = *(uint32_t **)(this + 104);  // this+104〔pRoomListCtrl〕
          if ( pRoomListCtrl_ != nullptr && *pRoomListCtrl_ == 5 )  // 判定 fld_682 != nullptr 且 fld_682 == 5
          {
            LOBYTE(v31) = 2;
            Block = (void *)4;  // Block = 转换(4)
            v47 = 115;
            v46 = 175;
          }
          else
          {
            LOBYTE(v31) = 2;
            Block = (void *)5;  // Block = 转换(5)
            v47 = 350;
            v46 = 280;
          }
        }
        else
        {
          sub_45C770((uint32_t *)this, v31, (unsigned int)Block);  // sub_45C770 —— 按 (地图, 索引) 取/建 0x208 关卡对象
          pRoomListCtrl_2 = *(int **)(this + 104);  // this+104〔pRoomListCtrl〕
          if ( pRoomListCtrl_2 != nullptr )  // fld_683=this+104 pRoomListCtrl
            v34 = *pRoomListCtrl_2;  // fld_683=this+104 pRoomListCtrl
          else
            v34 = -1;
          sub_48C920((int)&v47, (int)&v46, pObj, *(uint32_t *)(this + 100), v34);  // sub_48C920 —— 按键对查矩形记录并回填中心（未中打 aCriticalError_10）
        }
        sub_423200(dword_8F7B08, 38);  // 【发送网络包API】
        v50[0] = v31;
        sub_423290(v50, 1);  // sub_423290 —— 写 4B 长度
        v50[0] = (char)Block;
        sub_423290(v50, 1);  // sub_423290 —— 写 4B 长度
        Block = (void *)v47;
        sub_423290(&Block, 2);  // sub_423290 —— 写 4B 长度
        Block = (void *)v46;
        sub_423290(&Block, 2);  // sub_423290 —— 写 4B 长度
        v50[0] = 5;
        sub_423290(v50, 1);  // sub_423290 —— 写 4B 长度
      }
      sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
      *(uint8_t *)(this + 116) = 1;  // 写字段 this+116（pSessionCtx） ← 1
      goto LABEL_35;
    }
  }
LABEL_37:
  pObj2 = dword_8F7C04;  // 本地玩家对象
  if ( dword_8F7C04 != 0 )  // dword_8F7C04（本地玩家对象）
  {
    v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1064))(dword_8F7C04);  // 虚调用 vt+1064（dword_8F7C04 虚表槽）
    v20 = *(uint32_t *)pObj2;
    v48 = v19;
    v21 = v19 * (*(int (/*thiscall*/ **)(int))(v20 + 740))(pObj2) / 100;  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 736))(pObj2) != v21 )  // 虚调用 vt+736（pObj2 虚表槽）
    {
      v22 = *(uint32_t *)pObj2;
      v23 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj2 + 740))(pObj2, 0, 1);  // 虚调用 vt+740（pObj2 虚表槽）
      (*(void (/*thiscall*/ **)(int, int))(v22 + 732))(pObj2, v48 * v23 / 100);  // 调虚槽 +732：CNMapObject__vmt2DC
    }
    v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 756))(pObj2);  // 虚调用 vt+756（pObj2 虚表槽）
    v25 = v48 * v24 / 100;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 752))(pObj2) != v25 )  // 虚调用 vt+752（pObj2 虚表槽）
    {
      v26 = *(uint32_t *)pObj2;
      v27 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 756))(pObj2, 1);  // 虚调用 vt+756（pObj2 虚表槽）
      (*(void (/*thiscall*/ **)(int, int))(v26 + 748))(pObj2, v48 * v27 / 100);  // 调虚槽 +748：[RTTI: IRDActiveObject__vmt2EC · 槽位 IRDActiveObj…
    }
  }
  sub_4294E0(*(uint32_t *)(this + 44));  // sub_4294E0 —— HUD 每帧总 tick（尾段）
  if ( sub_699000(this + 16) >= *(uint32_t *)(this + 156) + 14000 )  // 【clock_now(clk)】
  {
    v28 = sub_429830((uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
    if ( v28 != 0 && sub_41A5E0(v28 + 53) <= 3 )  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( dword_98B730 != nullptr )
        v29 = (dword_98B734 - (int)dword_98B730) >> 2;
      else
        v29 = 0;
      nRand = rand() % v29;  // nRand = 调 rand
      if ( nRand == *(uint32_t *)(this + 160) )  // this+160〔nRandCache〕
      {
        if ( dword_98B730 != nullptr )
          v39 = (dword_98B734 - (int)dword_98B730) >> 2;
        else
          v39 = 0;
        nRand = (nRand + 1) % v39;
      }
      v40 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
      v41 = sub_41ACF0((char *)dword_98B730 + 4 * nRand);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      sub_43BEE0(v40, v41, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
      *(uint32_t *)(this + 160) = nRand;  // 写字段 this+160（fAdd160） ← nRand
      *(uint32_t *)(this + 156) = sub_699000(this + 16);  // sub_699000 —— 【clock_now(clk)】
    }
  }
  LODWORD(v42) = *(uint32_t *)(this + 120);  // this+120〔nSelRoomBgId〕
  if ( (uint32_t)v42 == 1 )
  {
    pThis_7C = sub_699000(this + 124);  // 【clock_now(clk)】
    v42 = (uint64_t)sub_4049C0(255.0, 0.0, pThis_7C, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *((uint32_t *)dword_8F8528 + 621) = v42;  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    if ( (uint32_t)v42 == 0 )
    {
      *(uint32_t *)(this + 120) = 0;  // 写字段 this+120（pAnimObj） ← 0
      *(uint8_t *)(this + 137) = 0;  // 写字段 this+137（field_0089） ← 0
      *(uint8_t *)(this + 138) = 0;  // 写字段 this+138（field_008A） ← 0
      LOBYTE(v42) = sub_698F90(this + 124, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
  }
  return v42;
}


// ============================================================
// 【分区 12】对象管理器（0x45D190-0x45FB20）
// UDP 接收泵 0x45E1A0（docs/13 §2 主帧循环调用）；id 对→对象查找 0x45EBE0
// （分发器全 case 共用）；0x45ED80/0x45EF30 = 分发器 case 0x21/0x22 落点。
// ============================================================
// ------------------------------------------------------------
// 0x45D190 sub_45D190 —— 进入/切换房间（DOOR_SHUT 自证）
// 旧地图经 ·sub_45F4D0(18) 清场后登记 ·+100 房间 id 与 ·+104 关卡记录；·sub_45C770/45C8C0 建关卡与战斗条目，
// ·sub_425500 换绑、·sub_424100 关联旧地图对象；再按房间名串 ·sub_431920 重建 +60 地图层，密码命中经
// ·dword_8F84B8 取 +64 资源；末置地图出现态 ·+172 = 0，双方同 kind 1 时响 ·DOOR_SHUT。
// ------------------------------------------------------------
int /*thiscall*/ sub_45D190(int this, uint32_t *ArgList, void *Block)  // sub_45D190 —— 进入/切换房间（DOOR_SHUT 自证）
{
  int fld_2C; // edx
  int fld_64; // eax
  uint32_t *v7; // ebx
  int result; // eax
  void *Block2; // ebx
  int v10; // eax
  int v11; // eax
  int fld_2C2; // edi
  int fld_682; // edi
  int fld_2C3; // edi
  uint32_t *v15; // ebx
  int v16; // ecx
  int v17; // eax
  uint32_t *v18; // eax
  int fld_30; // edi
  int fld_683; // eax
  void *Block3; // [esp-4h] [ebp-28h]
  int v22; // [esp-4h] [ebp-28h]
  int fld_642; // [esp+Ch] [ebp-18h]
  int v24; // [esp+10h] [ebp-14h] BYREF
  int fld_68; // [esp+14h] [ebp-10h]
  int v26; // [esp+20h] [ebp-4h]
  uint32_t *ArgLista; // [esp+2Ch] [ebp+8h]

  fld_2C = *(uint32_t *)(this + 44);  // 读字段 fld_2C = this+44（nExpireMs）
  fld_64 = *(uint32_t *)(this + 100);  // 读字段 fld_64 = this+100（bEnchantDone）
  fld_68 = *(uint32_t *)(this + 104);  // 读字段 fld_68 = this+104（nTimerEnd）
  fld_642 = fld_64;  // fld_64=this+100 bEnchantDone
  if ( *(uint32_t *)(fld_2C + 104) != 0 )  // fld_2C=this+44 nExpireMs
    sub_45F4D0(18);  // sub_45F4D0 —— 按类型批量注销
  *(uint32_t *)(this + 100) = ArgList;  // 写字段 this+100（bEnchantDone） ← ArgList
  v7 = (uint32_t *)sub_4CE8A0(ArgList);  // sub_4CE8A0 —— 调用 sub_4CE8A0
  ArgLista = v7;
  if ( v7 == nullptr )
    return off_77F3FC(aCriticalError_5, ArgList);  // off_77F3FC —— 日志打印（printf 风格）
  sub_45B660(&v24, &Block);  // sub_45B660 —— STL 红黑树 lower_bound（哨兵 ·+69）
  if ( v24 == v7[25] )
    return off_77F3FC(aCriticalError_7, ArgList, Block);  // off_77F3FC —— 日志打印（printf 风格）
  Block2 = Block;
  Block3 = Block;
  *(uint32_t *)(this + 104) = v24 + 16;  // 写字段 this+104（nTimerEnd） ← v24 + 16
  v10 = sub_45C770((char)ArgList, Block3);  // sub_45C770 —— 按 (地图, 索引) 取/建 0x208 关卡对象
  sub_425500(v10);  // sub_425500 —— 锚定对象换绑
  v11 = sub_45C8C0((char)ArgList, Block2);  // sub_45C8C0 —— 按 (地图, 索引) 取/建 0xA0 战斗条目
  sub_424100(*(uint32_t **)(this + 44), v11);  // sub_424100 —— 关联对象 setter
  fld_2C2 = *(uint32_t *)(*(uint32_t *)(this + 44) + 104);  // this+44〔nExpireMs(推断)〕等 2 字段
  sub_45F4D0(18);  // sub_45F4D0 —— 按类型批量注销
  result = sub_45ECE0(fld_2C2);  // sub_45ECE0 —— 对象表逐项刷新钩子
  fld_682 = fld_68;  // fld_68=this+104 nTimerEnd
  if ( fld_68 != 0 )  // fld_68=this+104 nTimerEnd
  {
    if ( (uint8_t)sub_41C590(dword_8F7A24) == 0  // sub_41C590 —— 状态查询（this+348 == 4）
      && (*(uint8_t *)(this + 117) == 0 && *(uint32_t *)(fld_682 + 32) == 1 && *(uint32_t *)(*(uint32_t *)(this + 104) + 32) != 1  // this+104〔nTimerEnd(推断)〕
       || fld_642 != *(uint32_t *)(this + 100)) )  // this+100〔bEnchantDone(推断)〕
    {
      fld_2C3 = *(uint32_t *)(*(uint32_t *)(this + 44) + 108);  // this+44〔nExpireMs(推断)〕等 2 字段
      v15 = *(uint32_t **)(fld_2C3 + 60);  // fld_2C3=this+44 nExpireMs
      if ( v15 != nullptr )
      {
        sub_42AF90(*(void ***)(fld_2C3 + 60));  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
        sub_657740((int *)dword_9A0128, v15, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
      }
      *(uint32_t *)(fld_2C3 + 60) = 0;  // 写字段 fld_2C3+60（nFadeValue60） ← 0
      Block = (void *)sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
      v26 = 0;
      if ( Block != nullptr )
      {
        if ( ArgLista[14] < 0x10u )
          LOBYTE(v16) = (uint8_t)ArgLista + 36;
        else
          v16 = ArgLista[9];
        if ( ArgLista[33] < 0x10u )
          v17 = sub_431920((uint8_t)ArgLista + 112, v16, 1);  // sub_431920 —— 动画件构造（文件名版）
        else
          v17 = sub_431920(ArgLista[28], v16, 1);  // sub_431920 —— 动画件构造（文件名版）
      }
      else
      {
        v17 = 0;
      }
      *(uint32_t *)(fld_2C3 + 60) = v17;  // 写字段 fld_2C3+60（nFadeValue60） ← v17
      v26 = -1;
      if ( (uint8_t)sub_423340(ArgLista + 15, szPassword) != 0 )  // sub_423340 —— 串首比较判定（不等）
      {
        if ( ArgLista[21] < 0x10u )
          v18 = ArgLista + 16;  // 计算 v18 = ArgLista + 16
        else
          v18 = (uint32_t *)ArgLista[16];
        fld_30 = *(uint32_t *)(this + 48);  // 读字段 fld_30 = this+48（pCmdVecBegin48）
        v22 = ArgLista[22];
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v18);  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
        *(uint32_t *)(fld_30 + 64) = sub_418DD0(v22);  // sub_418DD0 —— 资源句柄 (101)
      }
      fld_683 = fld_68;  // fld_68=this+104 nTimerEnd
      *(uint32_t *)(this + 172) = 0;  // 写字段 this+172（pAppendVecEnd） ← 0
      *(uint8_t *)(this + 189) = 0;  // 写字段 this+189（bFlag189） ← 0
      *(uint8_t *)(this + 190) = 0;  // 写字段 this+190（bFlag190） ← 0
      *(uint32_t *)(this + 212) = *(uint32_t *)(fld_683 + 32);  // 写字段 this+212（nField212） ← *(uint32_t *)(fld_683 + 32)
      fld_682 = fld_683;
    }
    result = 1;
    if ( *(uint32_t *)(fld_682 + 32) == 1 && *(uint32_t *)(*(uint32_t *)(this + 104) + 32) == 1 )  // this+104〔nTimerEnd(推断)〕
      result = (int)sub_432EA0("DOOR_SHUT", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
  }
  *(uint32_t *)(this + 108) = 0;  // 写字段 this+108（nAdd108） ← 0
  return result;
}


// ------------------------------------------------------------
// 0x45D410 sub_45D410 —— 网络对象字段批量复位
// +8 = 0x01010101、+76 = 1、+77 起 0x100 字节清零、+444 = -1，返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_45D410(int this)  // sub_45D410 —— 网络对象字段批量复位
{
  uint32_t *pThis_14; // ecx

  *(uint32_t *)(this + 396) = 0;  // 写字段 this+396（uReflectCtx） ← 0
  *(uint32_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  pThis_14 = (uint32_t *)(this + 20);  // this+20〔nPage(推断)〕等 2 字段
  *pThis_14 = 0;  // pThis_14=this+20 nPage
  pThis_14[1] = 0;  // pThis_14=this+20 nPage
  pThis_14[2] = 0;  // pThis_14=this+20 nPage
  pThis_14[3] = 0;  // pThis_14=this+20 nPage
  *(uint32_t *)(this + 36) = 0;  // 写字段 this+36（nStateWord36） ← 0
  *(uint32_t *)(this + 40) = 0;  // 写字段 this+40（bStateSub40） ← 0
  *(uint32_t *)(this + 44) = 0;  // 写字段 this+44（nExpireMs） ← 0
  *(uint32_t *)(this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48） ← 0
  *(uint32_t *)(this + 68) = 0;  // 写字段 this+68（nCharCount） ← 0
  *(uint32_t *)(this + 72) = 0;  // 写字段 this+72（nSnapshot72） ← 0
  *(uint8_t *)(this + 76) = 1;  // 写字段 this+76（szEmblemPath） ← 1
  memset((void *)(this + 77), 0, 0x100u);  // this+77〔bGuildFlagB〕
  *(uint32_t *)(this + 336) = 0;  // 写字段 this+336 ← 0
  *(uint32_t *)(this + 340) = 0;  // 写字段 this+340（pSlotTbl340） ← 0
  *(uint32_t *)(this + 344) = 0;  // 写字段 this+344（nReservedDelay） ← 0
  *(uint32_t *)(this + 348) = 0;  // 写字段 this+348（pParamTbl348） ← 0
  *(uint32_t *)(this + 352) = 0;  // 写字段 this+352（uHitCtx352） ← 0
  *(uint32_t *)(this + 356) = 0;  // 写字段 this+356 ← 0
  *(uint32_t *)(this + 360) = 0;  // 写字段 this+360 ← 0
  *(uint32_t *)(this + 364) = 0;  // 写字段 this+364（pAnimNameStr） ← 0
  *(uint32_t *)(this + 8) = 16843009;  // 写字段 this+8（nSkillRec8） ← 16843009
  *(uint32_t *)(this + 404) = 0;  // 写字段 this+404 ← 0
  *(uint8_t *)(this + 421) = 0;  // 写字段 this+421 ← 0
  *(uint8_t *)(this + 422) = 0;  // 写字段 this+422 ← 0
  *(uint8_t *)(this + 420) = 0;  // 写字段 this+420 ← 0
  *(uint32_t *)(this + 436) = 0;  // 写字段 this+436（nAtkTableVal） ← 0
  *(uint32_t *)(this + 440) = 0;  // 写字段 this+440 ← 0
  *(uint8_t *)(this + 400) = 0;  // 写字段 this+400 ← 0
  *(uint32_t *)(this + 444) = -1;  // 写字段 this+444 ← -1
  return 0;
}



// ------------------------------------------------------------
// 0x45D4C0 sub_45D4C0 —— 网络栈初始化（本机 IP / UDP 套接字 / MTU 探测）
// gethostname 取本机 IP(·+12)、socket UDP 非阻塞(·+16) 并 bind 5063；rand()%4 从 ·ArgList 服务器表选一台
// 装填 ·+20(0x907)/·+36(0x908) 目标；ICMP 二分探测 MTU（目标 211.189.29.106）分档 768/1024/1280/1472 存 ·+444。
// ------------------------------------------------------------
int /*thiscall*/ sub_45D4C0(int this)  // sub_45D4C0 —— 网络栈初始化（本机 IP / UDP 套接字 / MTU 探测）
{
  int Error; // eax
  struct hostent *v4; // eax
  SOCKET v5; // eax
  u_long v6; // eax
  SOCKET fld_10; // ecx
  int nRand; // esi
  struct ip_option_information *v9; // eax
  unsigned int pBuf2; // esi
  HGLOBAL v11; // eax
  IPAddr v12; // edx
  void *v13; // edi
  HANDLE v14; // [esp-24h] [ebp-ECh]
  void *v15; // [esp-1Ch] [ebp-E4h]
  SOCKET fld_102; // [esp-18h] [ebp-E0h]
  SOCKET fld_103; // [esp-18h] [ebp-E0h]
  struct ip_option_information *v18; // [esp-14h] [ebp-DCh]
  DWORD v19; // [esp+8h] [ebp-C0h]
  char optval[4]; // [esp+Ch] [ebp-BCh] BYREF
  IPAddr DestinationAddress; // [esp+10h] [ebp-B8h]
  u_long argp; // [esp+14h] [ebp-B4h] BYREF
  int v23; // [esp+18h] [ebp-B0h]
  HANDLE IcmpHandle; // [esp+1Ch] [ebp-ACh]
  unsigned int pBuf22; // [esp+20h] [ebp-A8h]
  LPVOID RequestData; // [esp+24h] [ebp-A4h]
  char v27[4]; // [esp+28h] [ebp-A0h] BYREF
  PIP_OPTION_INFORMATION RequestOptions; // [esp+2Ch] [ebp-9Ch]
  char name[100]; // [esp+30h] [ebp-98h] BYREF
  char cp[32]; // [esp+94h] [ebp-34h] BYREF
  struct sockaddr pBuf; // [esp+B4h] [ebp-14h] BYREF
  int dword_796E502; // [esp+C4h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  if ( byte_98B73C == 0 )
  {
    sub_56ADA0();  // sub_56ADA0 —— 频道表重建（56AA00/56AC80/56A8A0）
    byte_98B73C = 1;
  }
  memset(name, 0, sizeof(name));  // 调 内存按字节填充
  if ( gethostname(name, 100) == -1 )
  {
    Error = WSAGetLastError();  // Error = 调 WSAGetLastError
    return off_77F3FC("SOCKET ERROR : %d", Error);  // off_77F3FC —— 日志打印（printf 风格）
  }
  else
  {
    v4 = gethostbyname(name);  // v4 = 调 gethostbyname
    if ( v4 != nullptr )
      sprintf(  // 调 格式化到缓冲
        cp,
        "%d.%d.%d.%d",
        **(uint8_t **)v4->h_addr_list,
        *((uint8_t *)*v4->h_addr_list + 1),
        *((uint8_t *)*v4->h_addr_list + 2),
        *((uint8_t *)*v4->h_addr_list + 3));
    else
      sprintf(cp, "127.0.0.1");  // 拼字符串（模板 127.0.0.1）
    off_77F3FC("Local IP : [%s]", cp);  // off_77F3FC —— 日志打印（printf 风格）
    *(uint32_t *)(this + 12) = inet_addr(cp);  // 写字段 this+12（nSkillRec12） ← inet_addr(cp)
    v5 = socket(2, 2, 0);  // v5 = 调 socket
    *(uint32_t *)(this + 16) = v5;  // 写字段 this+16（nChannelTypeSel） ← v5
    argp = 1;
    if ( ioctlsocket(v5, -2147195266, &argp) == -1 )
    {
      return off_77F3FC("Socket Error!");  // off_77F3FC —— 日志打印（printf 风格）
    }
    else
    {
      memset(pBuf.sa_data, 0, sizeof(pBuf.sa_data));  // 调 内存按字节填充
      pBuf.sa_family = 2;
      *(uint16_t *)pBuf.sa_data = htons(0x13C7u);  // 调 主机序转网络序(16位)
      v6 = htonl(0);  // v6 = 调 htonl
      fld_10 = *(uint32_t *)(this + 16);  // 读字段 fld_10 = this+16（nChannelTypeSel）
      *(uint32_t *)&pBuf.sa_data[2] = v6;
      bind(fld_10, &pBuf, 16);  // 调 绑定地址
      nRand = rand() % 4;  // nRand = 调 rand
      *(uint8_t *)(nRand + this + 8) = 0;  // this+8 物品 id
      off_77F3FC("UDP SERVER CONNECT : [%s]", (&ArgList)[nRand]);  // off_77F3FC —— 日志打印（printf 风格）
      *(uint16_t *)(this + 2 * nRand + 436) = 2;
      *(uint16_t *)(this + 20) = 2;  // 写字段 this+20（nPage） ← 2
      *(uint32_t *)(this + 24) = inet_addr((&ArgList)[nRand]);  // 写字段 this+24（nPageMax） ← inet_addr((&ArgList)[nRand])
      *(uint16_t *)(this + 22) = htons(0x907u);  // 写字段 this+22 ← htons(0x907u)
      *(uint16_t *)(this + 36) = 2;  // 写字段 this+36（nStateWord36） ← 2
      *(uint32_t *)(this + 40) = inet_addr((&ArgList)[nRand]);  // 写字段 this+40（bStateSub40） ← inet_addr((&ArgList)[nRand])
      *(uint16_t *)(this + 38) = htons(0x908u);  // 写字段 this+38（bFadeFlag38） ← htons(0x908u)
      fld_102 = *(uint32_t *)(this + 16);  // 读字段 fld_102 = this+16（nChannelTypeSel）
      *(uint32_t *)optval = 10;  // *optval = 10
      setsockopt(fld_102, 0xFFFF, 4102, optval, 4);  // 调 设置套接字选项
      fld_103 = *(uint32_t *)(this + 16);  // 读字段 fld_103 = this+16（nChannelTypeSel）
      *(uint32_t *)v27 = 0x100000;  // *v27 = 0x100000
      setsockopt(fld_103, 0xFFFF, 4098, v27, 4);  // 调 设置套接字选项
      setsockopt(*(uint32_t *)(this + 16), 0xFFFF, 4097, v27, 4);  // this+16〔nChannelTypeSel(推断)〕等 2 字段
      IcmpHandle = IcmpCreateFile();  // IcmpHandle = 调 IcmpCreateFile
      DestinationAddress = inet_addr("211.189.29.106");  // DestinationAddress = 调 inet_addr
      v9 = (struct ip_option_information *)GlobalAlloc(0x40u, 8u);  // 调 全局内存分配
      pBuf2 = 1472;
      RequestOptions = v9;
      v9->Flags = 2;
      v9->Ttl = -1;
      pBuf22 = 0;
      v23 = 1472;
      while ( 1 )
      {
        while ( 1 )
        {
          RequestData = GlobalAlloc(0x40u, pBuf2);  // RequestData = 调 GlobalAlloc
          memset(RequestData, 0xAAu, pBuf2);  // 调 内存按字节填充
          v11 = GlobalAlloc(0x40u, pBuf2 + 28);  // v11 = 调 GlobalAlloc
          v12 = DestinationAddress;
          v13 = v11;
          v18 = RequestOptions;
          v15 = RequestData;
          *((uint32_t *)v11 + 4) = RequestData;  // 写字段 v11+4（pHostObj）
          v14 = IcmpHandle;
          *((uint16_t *)v11 + 6) = pBuf2;  // 写字段 v11[6]（宽2字节）
          v19 = IcmpSendEcho(v14, v12, v15, pBuf2, v18, v11, pBuf2 + 28, 0x3E8u);  // v19 = 调 IcmpSendEcho
          GlobalFree(v13);  // 调 全局内存释放
          GlobalFree(RequestData);  // 调 全局内存释放
          if ( v19 == 0 )
            break;
          if ( pBuf2 == v23 )
            goto LABEL_16;
          pBuf22 = pBuf2;
          pBuf2 = (pBuf2 + v23 + 1) >> 1;
        }
        if ( pBuf2 == pBuf22 )
          break;
        v23 = pBuf2 - 1;  // 计算 v23 = pBuf2 - 1
        pBuf2 = (pBuf22 + pBuf2 - 1) >> 1;
      }
LABEL_16:
      GlobalFree(RequestOptions);  // 调 全局内存释放
      IcmpCloseHandle(IcmpHandle);
      if ( pBuf2 < 0x5C0 )
      {
        if ( pBuf2 < 0x500 )
        {
          if ( pBuf2 < 0x400 )
            *(uint32_t *)(this + 444) = 768;  // 写字段 this+444 ← 768
          else
            *(uint32_t *)(this + 444) = 1024;  // 写字段 this+444 ← 1024
        }
        else
        {
          *(uint32_t *)(this + 444) = 1280;  // 写字段 this+444 ← 1280
        }
      }
      else
      {
        *(uint32_t *)(this + 444) = 1472;  // 写字段 this+444 ← 1472
      }
      return off_77F3FC("[MTU] Client MTU Size is [%d]", *(uint32_t *)(this + 444));  // off_77F3FC —— 日志打印（printf 风格）
    }
  }
}


// ------------------------------------------------------------
// 0x45D890 sub_45D890 —— UDP 识别完成回执（UDP IDENTIFIED 自证）
// 置 ·+68 = 4(PVP)、·+18 = net_type 并回填频道表 ·+160/+164/+168（地址/端口）；
// 组 2 号包依次写 net_type(1B)、·+12(4B)、远端地址/端口(4B+2B)、MTU(·+444，4B) 后提交。
// ------------------------------------------------------------
char /*thiscall*/ sub_45D890(void *this, uint32_t *pArg2, int ArgList)  // sub_45D890 —— UDP 识别完成回执（UDP IDENTIFIED 自证）
{
  char v3; // bl
  int pThis_12; // edx
  char result; // al
  int v7; // eax
  int pThis_59; // edx
  u_short pThis_B0; // ax
  char v10; // [esp-4h] [ebp-10h]

  v3 = ArgList;
  v10 = ArgList;
  *((uint32_t *)this + 18) = ArgList;  // 写字段 this+18（bDragChild）
  sub_40BE20("1@@@@@@@@@@@@@@net_type:%d#####################\n", v10);  // sub_40BE20 —— 调 sub_40BE20
  pThis_12 = *((uint32_t *)this + 18);  // 读字段 pThis_12 = this+18（bDragChild）
  *((uint32_t *)this + 17) = 4;  // 写字段 this+17（bEnable）
  *(uint32_t *)this = *pArg2;
  *((uint32_t *)this + 1) = pArg2[1];  // 写字段 this[1]（宽4字节）
  off_77F3FC("UDP IDENTIFIED! [%d]", pThis_12);  // off_77F3FC —— 日志打印（printf 风格）
  sub_40BE20("---------%d %d\n", *(uint8_t *)(dword_8F7B08 + 8));  // sub_40BE20 —— 调 sub_40BE20
  result = *(uint8_t *)(dword_8F7B08 + 8);  // dword_8F7B08 —— 【发送网络包API】
  if ( result != 0 )
  {
    result = *(uint8_t *)(*(uint32_t *)(dword_8F7A24 + 16) + 48);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    if ( result != 0 )
    {
      if ( sub_429830((uint16_t)word_77F804) != 0 )  // sub_429830 —— 结果 = 表按键查找（uint16）
      {
        v7 = sub_429830((uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
        *(uint32_t *)(v7 + 160) = *((uint32_t *)this + 3);  // 写字段 v7+160（fAdd160） ← *((uint32_t *)this + 3)
        pThis_59 = *((uint32_t *)this + 89);  // 读字段 pThis_59 = this+89（nLifetime）
        ArgList = v7;
        *(uint32_t *)(v7 + 164) = pThis_59;  // 写字段 v7+164（fAdd164） ← pThis_59
        pThis_B0 = ntohs(*((uint16_t *)this + 176));  // this+352〔uHitCtx352〕
        *(uint16_t *)(ArgList + 168) = pThis_B0;  // 写字段 ArgList+168（pAppendVec） ← pThis_B0
      }
      sub_423200(dword_8F7B08, 2);  // 【发送网络包API】
      HIBYTE(ArgList) = v3;
      sub_423290((char *)&ArgList + 3, 1);  // sub_423290 —— 写 4B 长度
      sub_40BE20("2@@@@@@@@@@@@@@net_type:%d#####################\n", v3);  // sub_40BE20 —— 调 sub_40BE20
      ArgList = *((uint32_t *)this + 3);  // 读字段 ArgList = this[3]
      sub_423290(&ArgList, 4);  // sub_423290 —— 写 4B 长度
      ArgList = pArg2[1];  // ArgList=this+12 物品类型号
      sub_423290(&ArgList, 4);  // sub_423290 —— 写 4B 长度
      ArgList = *(uint16_t *)pArg2;  // ArgList=this+12 物品类型号
      sub_423290(&ArgList, 2);  // sub_423290 —— 写 4B 长度
      ArgList = *((uint32_t *)this + 111);  // 读字段 ArgList = this[111]
      sub_423290(&ArgList, 4);  // sub_423290 —— 写 4B 长度
      sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
      return off_77F3FC("UDP IDENTIFY INFO SEND!");  // off_77F3FC —— 日志打印（printf 风格）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x45DA30 sub_45DA30 —— net_type 非 0 时重发识别回执
// 以自身为地址/端口参数转 ·sub_45D890，返回 1（net_type 为 0 返回 0）。
// ------------------------------------------------------------
char /*thiscall*/ sub_45DA30(int *this)  // sub_45DA30 —— net_type 非 0 时重发识别回执
{
  if ( *(this + 18) == 0 )  // this+72〔nSnapshot72(推断)〕
    return 0;
  sub_45D890(this, this, *(this + 18));  // sub_45D890 —— UDP 识别完成回执（UDP IDENTIFIED 自证）
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x45DA50 sub_45DA50 —— 切换备用服务器（4 候选轮询）
// 扫描 ·+8..+11 标志与端口计数 ·+436+2i（用后计数归 2、标志清 0），
// 选中者重置 ·+20(0x907)/·+36(0x908) 目标地址并记录日志。
// ------------------------------------------------------------
char /*thiscall*/ sub_45DA50(int this)  // sub_45DA50 —— 切换备用服务器（4 候选轮询）
{
  int v2; // edi
  uint16_t *pThis_1B4; // eax

  v2 = 0;
  pThis_1B4 = (uint16_t *)(this + 436);  // this+436〔nAtkTableVal(推断)〕等 2 字段
  while ( *(uint8_t *)(this + v2 + 8) != 1 )  // 当 *(uint8_t *)(this + v2 + 8) != 1 循环
  {
LABEL_5:
    ++v2;  // 计数自增 v2
    ++pThis_1B4;  // 计数自增 pThis_1B4
    if ( v2 >= 4 )
      goto LABEL_8;
  }
  if ( *pThis_1B4 == 0 )  // pThis_1B4=this+436 nAtkTableVal
  {
    *(uint8_t *)(this + v2 + 8) = 0;
    goto LABEL_5;
  }
  *(uint16_t *)(this + 2 * v2 + 436) = 2;
  *(uint8_t *)(v2 + this + 8) = 0;  // this+8 物品 id
LABEL_8:
  sub_40BE20(asc_6C71AC, (char)(&ArgList)[v2]);  // sub_40BE20 —— 调 sub_40BE20
  *(uint16_t *)(this + 20) = 2;  // 写字段 this+20（nPage） ← 2
  *(uint32_t *)(this + 24) = inet_addr((&ArgList)[v2]);  // 写字段 this+24（nPageMax） ← inet_addr((&ArgList)[v2])
  *(uint16_t *)(this + 22) = htons(0x907u);  // 写字段 this+22 ← htons(0x907u)
  *(uint16_t *)(this + 36) = 2;  // 写字段 this+36（nStateWord36） ← 2
  *(uint32_t *)(this + 40) = inet_addr((&ArgList)[v2]);  // 写字段 this+40（bStateSub40） ← inet_addr((&ArgList)[v2])
  *(uint16_t *)(this + 38) = htons(0x908u);  // 写字段 this+38（bFadeFlag38） ← htons(0x908u)
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x45DB00 sub_45DB00 —— 取当前服务器 IP 串
// 索引 ·+404 → ·off_790540 表（与 ·sub_45DF90 的 _RELAY 覆盖逻辑配套）。
// ------------------------------------------------------------
char */*thiscall*/ sub_45DB00(uint32_t *this)  // sub_45DB00 —— 取当前服务器 IP 串
{
  return off_790540[*(this + 101)];  // 返回 取 off_790540[*(this + 101)]
}



// ------------------------------------------------------------
// 0x45DB20 sub_45DB20 —— NAT 类型探测（SNAT 系列日志自证）
// ·+72 == 3 时按 4 服务器端口计数 0x907/0x908 交替 sendto 探针，收包解析公网映射地址/端口写记录 +168；
// 随后以 2 号包上报 net_type / 记录 +160/+164 / htons(+168) / MTU(·+444)。
// ------------------------------------------------------------
int /*thiscall*/ sub_45DB20(int this, int nArg2)  // sub_45DB20 —— NAT 类型探测（SNAT 系列日志自证）
{
  int result; // eax
  int v4; // esi
  uint16_t *i; // eax
  const char *v6; // ecx
  uint16_t pThis_2; // ax
  u_short v8; // ax
  SOCKET fld_10; // ecx
  int v10; // eax
  int pThis_4D; // eax
  int nArg22; // esi
  u_long fld_4E; // eax
  u_short fld_52; // cx
  struct in_addr v15; // edi
  char *v16; // eax
  u_short v17; // ax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  SOCKET fld_102; // [esp-20h] [ebp-50h]
  int v22; // [esp-Ch] [ebp-3Ch]
  int v23; // [esp-Ch] [ebp-3Ch]
  int v24; // [esp-Ch] [ebp-3Ch]
  int fromlen; // [esp+4h] [ebp-2Ch] BYREF
  char buf[3]; // [esp+Bh] [ebp-25h] BYREF
  u_short netshort[7]; // [esp+Eh] [ebp-22h]
  struct sockaddr to; // [esp+1Ch] [ebp-14h] BYREF
  int dword_796E502; // [esp+2Ch] [ebp-4h]

  result = dword_796E50;  // dword_796E50 —— 栈检 cookie
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  if ( *(uint32_t *)(this + 72) == 3 )  // this+72〔nSnapshot72(推断)〕等 2 字段
  {
    v4 = 0;
    for ( i = (uint16_t *)(this + 436); *i >= 2u; ++i )  // this+436〔nAtkTableVal(推断)〕等 2 字段
    {
      if ( ++v4 >= 4 )
        return off_77F3FC(aSNat);  // off_77F3FC —— 日志打印（printf 风格）
    }
    v6 = (&ArgList)[v4];
    *(uint16_t *)to.sa_data = 0;
    *(uint32_t *)&to.sa_data[6] = 0;
    *(uint32_t *)&to.sa_data[10] = 0;
    to.sa_family = 2;
    *(uint32_t *)&to.sa_data[2] = inet_addr(v6);
    pThis_2 = *(uint16_t *)(this + 2 * v4 + 436);
    if ( pThis_2 < 2u )
    {
      if ( pThis_2 != 0 )
        v8 = htons(0x908u);  // v8 = 调 htons
      else
        v8 = htons(0x907u);  // v8 = 调 htons
      ++*(uint16_t *)(this + 2 * v4 + 436);
      *(uint16_t *)to.sa_data = v8;
    }
    fld_10 = *(uint32_t *)(this + 16);  // 读字段 fld_10 = this+16（nChannelTypeSel）
    buf[0] = 1;
    v10 = sendto(fld_10, buf, 1, 0, &to, 16);  // v10 = 调 sendto
    off_77F3FC(aSNat_0, v10);  // off_77F3FC —— 日志打印（printf 风格）
    memset((void *)(this + 77), 0, 0x100u);  // this+77〔bGuildFlagB〕
    *(uint32_t *)(this + 336) = 0;  // 写字段 this+336 ← 0
    *(uint32_t *)(this + 340) = 0;  // 写字段 this+340（pSlotTbl340） ← 0
    *(uint32_t *)(this + 344) = 0;  // 写字段 this+344（nReservedDelay） ← 0
    *(uint32_t *)(this + 348) = 0;  // 写字段 this+348（pParamTbl348） ← 0
    fld_102 = *(uint32_t *)(this + 16);  // 读字段 fld_102 = this+16（nChannelTypeSel）
    fromlen = 16;
    pThis_4D = recvfrom(fld_102, (char *)(this + 77), 256, 0, (struct sockaddr *)(this + 336), &fromlen);  // this+77〔bGuildFlagB〕
    nArg22 = nArg2;
    if ( pThis_4D == -1 || *(uint8_t *)(this + 77) != 2 )  // this+77 公会标志字节 B
    {
      off_77F3FC(aSNat_3);  // off_77F3FC —— 日志打印（printf 风格）
    }
    else
    {
      fld_4E = htonl(*(uint32_t *)(this + 78));  // this+78〔bGuildFlagC〕
      fld_52 = *(uint16_t *)(this + 82);  // 读字段 fld_52 = this+82
      v15 = (struct in_addr)fld_4E;  // fld_4E=this+78 bGuildFlagC
      *(uint32_t *)&netshort[1] = fld_4E;  // fld_4E=this+78 bGuildFlagC
      netshort[0] = htons(fld_52);  // netshort[0] = 调 htons
      v22 = ntohs(netshort[0]);  // v22 = 调 ntohs
      v16 = inet_ntoa(v15);  // v16 = 调 inet_ntoa
      off_77F3FC(aSNat_1, v16, v22);  // off_77F3FC —— 日志打印（printf 风格）
      v17 = ntohs(netshort[0]);  // v17 = 调 ntohs
      v23 = v17;
      *(uint16_t *)(nArg22 + 168) = v17;  // 写字段 nArg22+168（pAppendVec） ← v17
      v18 = sub_42A380(1);  // sub_42A380 —— 四字节号格式化（四段十进制）
      off_77F3FC(aSNat_2, v18, v23);  // off_77F3FC —— 日志打印（printf 风格）
      sub_423200(dword_8F7B08, 2);  // 【发送网络包API】
      HIBYTE(nArg2) = *(uint8_t *)(this + 72);  // this+72〔nSnapshot72(推断)〕等 2 字段
      sub_423290((char *)&nArg2 + 3, 1);  // sub_423290 —— 写 4B 长度
      nArg2 = *(uint32_t *)(nArg22 + 160);  // 读字段 nArg2 = nArg22+160（fAdd160）
      sub_423290(&nArg2, 4);  // sub_423290 —— 写 4B 长度
      nArg2 = *(uint32_t *)(nArg22 + 164);  // 读字段 nArg2 = nArg22+164（fAdd164）
      sub_423290(&nArg2, 4);  // sub_423290 —— 写 4B 长度
      LOWORD(v19) = htons(*(uint16_t *)(nArg22 + 168));  // nArg22+168〔pAppendVec(推断)〕
      nArg2 = v19;
      sub_423290(&nArg2, 2);  // sub_423290 —— 写 4B 长度
      nArg2 = *(uint32_t *)(this + 444);  // 读字段 nArg2 = this+444
      sub_423290(&nArg2, 4);  // sub_423290 —— 写 4B 长度
      sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
    }
    v24 = *(uint16_t *)(nArg22 + 168);  // 读字段 v24 = nArg22+168（pAppendVec）
    v20 = sub_42A380(1);  // sub_42A380 —— 四字节号格式化（四段十进制）
    return off_77F3FC(aSNat_4, v20, v24);  // off_77F3FC —— 日志打印（printf 风格）
  }
  return result;
}


// ------------------------------------------------------------
// 0x45DDA0 sub_45DDA0 —— 连接自检状态机（目标态 nArg2）
// ·+68 == 4 时每 10s 向 ·+36 发 10 字节保活（·+76 起）；否则切 ·+68 = nArg2 并按档发探包：
// 1 REALIP（附 MTU 4 字节）、2 NAT、3 端口限制（首字节 5）；同态累计 10 次失败 ·sub_45DA50 换服，
// 再失败弹 Run Error 并 PostQuitMessage 退出。
// ------------------------------------------------------------
void /*thiscall*/ sub_45DDA0(int this, int nArg2)  // sub_45DDA0 —— 连接自检状态机（目标态 nArg2）
{
  int fld_188; // edi
  int fld_44; // ecx
  int fld_1882; // ebx
  SOCKET fld_10; // edx
  int fld_18C; // ecx
  HWND v8; // esi
  char *v9; // eax
  SOCKET fld_105; // edx
  int fld_102; // eax
  SOCKET fld_103; // ecx
  int fld_1BC; // edx
  int pThis_4C; // [esp-8h] [ebp-18h]
  int fld_104; // [esp-8h] [ebp-18h]
  int pThis_14; // [esp-8h] [ebp-18h]
  char buf; // [esp+8h] [ebp-8h] BYREF
  int fld_1BC2; // [esp+9h] [ebp-7h]

  if ( *(uint8_t *)(this + 400) == 0 || (fld_188 = *(uint32_t *)(this + 392), sub_699000(this + 368) >= fld_188) )  // 【clock_now(clk)】
  {
    fld_44 = *(uint32_t *)(this + 68);  // 读字段 fld_44 = this+68（nCharCount）
    if ( fld_44 == 4 )  // fld_44=this+68 nCharCount
    {
      fld_1882 = *(uint32_t *)(this + 392);  // 读字段 fld_1882 = this+392
      if ( sub_699000(this + 368) >= fld_1882 )  // 【clock_now(clk)】
      {
        fld_10 = *(uint32_t *)(this + 16);  // 读字段 fld_10 = this+16（nChannelTypeSel）
        *(uint8_t *)(this + 76) = 0;  // 写字段 this+76（szEmblemPath） ← 0
        sendto(fld_10, (const char *)(this + 76), 10, 0, (const struct sockaddr *)(this + 36), 16);  // this+76〔pBtnActionE〕
        *(uint8_t *)(this + 381) = 0;  // 写字段 this+381 ← 0
        *(uint8_t *)(this + 382) = 0;  // 写字段 this+382 ← 0
        sub_698F90(this + 368, 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
      return;
    }
    if ( nArg2 == fld_44 )  // fld_44=this+68 nCharCount
    {
      fld_18C = *(uint32_t *)(this + 396);  // 读字段 fld_18C = this+396（uReflectCtx）
      if ( fld_18C >= 10 )  // fld_18C=this+396 uReflectCtx
      {
        if ( sub_45DA50(this) == 1 )  // sub_45DA50 —— 切换备用服务器（4 候选轮询）
        {
          off_77F3FC(aCnrdudpidentif);  // off_77F3FC —— 日志打印（printf 风格）
          *(uint32_t *)(this + 396) = 0;  // 写字段 this+396（uReflectCtx） ← 0
        }
        else
        {
          ShowCursor(true);
          v8 = *(HWND *)(dword_79C0A0 + 16);  // dword_79C0A0 —— v11 存调用结果
          v9 = sub_422E70(501);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
          MessageBoxA(v8, v9, "Run Error", 0);
          PostQuitMessage(0);  // 调 投递退出消息
        }
        return;
      }
      *(uint32_t *)(this + 396) = fld_18C + 1;  // 写字段 this+396（uReflectCtx） ← fld_18C + 1
    }
    else
    {
      *(uint32_t *)(this + 68) = nArg2;  // 写字段 this+68（nCharCount） ← nArg2
    }
    switch ( nArg2 )  // 按 nArg2 分派
    {
      case 1:  // case 1 分派（对象管理器（0x45D190-0x45FB20））
        fld_102 = sendto(*(uint32_t *)(this + 16), (const char *)(this + 76), 1, 0, (const struct sockaddr *)(this + 20), 16);  // fld_102 = 调 sendto
        off_77F3FC("SEND REALIP CHECK %d\n", fld_102);  // off_77F3FC —— 日志打印（printf 风格）
        fld_103 = *(uint32_t *)(this + 16);  // 读字段 fld_103 = this+16（nChannelTypeSel）
        fld_1BC = *(uint32_t *)(this + 444);  // 读字段 fld_1BC = this+444
        buf = 6;
        fld_1BC2 = fld_1BC;
        pThis_14 = sendto(fld_103, &buf, 5, 0, (const struct sockaddr *)(this + 20), 16);  // pThis_14 = 调 sendto
        off_77F3FC("SEND TO MTU LOG %d\n", pThis_14);  // off_77F3FC —— 日志打印（printf 风格）
        break;
      case 2:  // case 2 分派（对象管理器（0x45D190-0x45FB20））
        fld_104 = sendto(*(uint32_t *)(this + 16), (const char *)(this + 76), 1, 0, (const struct sockaddr *)(this + 36), 16);  // fld_104 = 调 sendto
        off_77F3FC("SEND NAT CHECK %d\n", fld_104);  // off_77F3FC —— 日志打印（printf 风格）
        break;
      case 3:  // case 3 分派（对象管理器（0x45D190-0x45FB20））
        fld_105 = *(uint32_t *)(this + 16);  // 读字段 fld_105 = this+16（nChannelTypeSel）
        *(uint8_t *)(this + 76) = 5;  // 写字段 this+76（szEmblemPath） ← 5
        pThis_4C = sendto(fld_105, (const char *)(this + 76), 1, 0, (const struct sockaddr *)(this + 20), 16);  // this+76〔pBtnActionE〕
        off_77F3FC("SEND PORT RESTRICT CHECK %d\n", pThis_4C);  // off_77F3FC —— 日志打印（printf 风格）
        break;
      default:
LABEL_20:
        *(uint8_t *)(this + 381) = 0;  // 写字段 this+381 ← 0
        *(uint8_t *)(this + 382) = 0;  // 写字段 this+382 ← 0
        sub_698F90(this + 368, 500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        return;
    }
    *(uint8_t *)(this + 400) = 1;  // 写字段 this+400 ← 1
    goto LABEL_20;
  }
}



// ------------------------------------------------------------
// 0x45DF90 sub_45DF90 —— 中继(relay) 连接（_RELAY 自证）
// ·+420 置位期间只重试 ·sub_4458C0；否则读 ·+404 默认服务器，_RELAY 存在则以文件首行 IP/末行端口覆盖，
// 经 ·sub_446000 写入网络对象并置 10s 计时；成功即 ·sub_45D890 上报识别（result==true 日志）。
// ------------------------------------------------------------
char /*usercall*/ sub_45DF90@<al>(int pArg1@<ecx>, char pszArg2@<bl>)  // 实现：中继(relay) 连接（_RELAY 自证）
{
  int v3; // edi
  int v5; // eax
  int v6; // edi
  const char *v7; // ebx
  FILE *pFile; // edi
  char v9; // al
  char v10; // bl
  FILE *Stream; // [esp+8h] [ebp-130h]
  char String[256]; // [esp+Ch] [ebp-12Ch] BYREF
  void *Block[5]; // [esp+110h] [ebp-28h] BYREF
  unsigned int v15; // [esp+124h] [ebp-14h]
  int dword_796E502; // [esp+128h] [ebp-10h]
  int v17; // [esp+134h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  if ( *(uint8_t *)(pArg1 + 420) != 0 && (v3 = *(uint32_t *)(pArg1 + 432), sub_699000(pArg1 + 408) < v3) )  // 【clock_now(clk)】
  {
    if ( sub_4458C0((uint32_t *)dword_8F8520) != 0 )  // sub_4458C0 —— 网络对象连接初始化
    {
      sub_45D890((void *)pArg1, (uint32_t *)(pArg1 + 352), *(uint32_t *)(pArg1 + 72));  // sub_45D890 —— UDP 识别完成回执（UDP IDENTIFIED 自证）
      *(uint8_t *)(pArg1 + 420) = 0;  // 写字段 pArg1+420 ← 0
      return 1;  // 返回 1(成功)
    }
    else
    {
      return 0;
    }
  }
  else
  {
    v5 = *(uint32_t *)(pArg1 + 404);  // 读字段 v5 = pArg1+404
    v6 = dword_6C7018[v5];
    v7 = off_790540[v5];
    v15 = 15;
    Block[4] = nullptr;
    LOBYTE(Block[0]) = 0;
    v17 = 0;
    if ( _access("_RELAY", 0) == 0 )  // 调 以 GetFileAttributesA 判定存在与读写权限
    {
      pFile = fopen("_RELAY", "rt");  // pFile = 调 fopen
      Stream = pFile;
      fgets(String, 256, pFile);  // 调 读一行
      String[strlen(String)] = 0;  // 调 返回字符串长度（逐字节扫描）
      sub_4015C0(String, strlen(String));  // 【std::string构造赋值】
      v7 = (const char *)Block[0];
      if ( v15 < 0x10 )
        v7 = (const char *)Block;
      fgets(String, 256, pFile);  // 调 读一行
      j__atol(String);
      fgets(String, 256, pFile);  // 调 读一行
      v6 = j__atol(String);  // v6 = 调 j__atol
      fclose(Stream);  // 调 关闭文件
    }
    v9 = sub_446000((uint32_t *)dword_8F8520, v7, v6);  // sub_446000 —— 网络对象字符串/数值写入 + 绑定
    *(uint8_t *)(pArg1 + 421) = 0;  // 写字段 pArg1+421 ← 0
    *(uint8_t *)(pArg1 + 422) = 0;  // 写字段 pArg1+422 ← 0
    v10 = v9;
    *(uint8_t *)(pArg1 + 420) = 1;  // 写字段 pArg1+420 ← 1
    sub_698F90(pArg1 + 408, 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    if ( v10 != 0 )
    {
      sub_40BE20("\nresult==true\n", pszArg2);  // sub_40BE20 —— 调 sub_40BE20
      sub_45D890((void *)pArg1, (uint32_t *)(pArg1 + 352), *(uint32_t *)(pArg1 + 72));  // sub_45D890 —— UDP 识别完成回执（UDP IDENTIFIED 自证）
      *(uint8_t *)(pArg1 + 420) = 0;  // 写字段 pArg1+420 ← 0
    }
    if ( v15 >= 0x10 )
      j__free(Block[0]);  // 释放堆块
    return v10;
  }
}



// ------------------------------------------------------------
// 0x45E1A0 sub_45E1A0
// ------------------------------------------------------------
// UDP 接收泵（docs/13 §2：主帧循环 sub_433690 调 sub_45E1A0(0x8F8524)）：
// dword_8F7B08+8 已连接且模块 +16 槽使能 → 按 +68 模块类型分发：
// 4(PVP) → sub_45DDA0 + sub_445940 就绪查询 + sub_45DF90；recvfrom/in_addr 直证
char /*usercall*/ sub_45E1A0@<al>(int pArg1@<ecx>, char pszArg2@<dil>)  // 实现：4(PVP) → sub_45DDA0 + sub_445940 就绪查询 + sub_45DF90；recvfrom/in_add…
{
  int v2; // eax
  uint8_t *v4; // ebx
  u_short v5; // ax
  struct in_addr v6; // ebx
  char *v7; // eax
  char *v8; // eax
  u_short v9; // ax
  struct in_addr v10; // ebx
  u_short v11; // cx
  int v12; // edx
  char *v13; // eax
  char *v14; // eax
  SOCKET v16; // [esp-20h] [ebp-4Ch]
  int v17; // [esp-Ch] [ebp-38h]
  int v18; // [esp-Ch] [ebp-38h]
  int v19; // [esp-Ch] [ebp-38h]
  int v20; // [esp-Ch] [ebp-38h]
  int fromlen; // [esp+4h] [ebp-28h] BYREF
  uint16_t netshort[8]; // [esp+Ah] [ebp-22h]
  u_short v23[7]; // [esp+1Ah] [ebp-12h]
  int dword_796E502; // [esp+28h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  LOBYTE(v2) = dword_8F7B08;  // dword_8F7B08 —— 【发送网络包API】
  if ( *(uint8_t *)(dword_8F7B08 + 8) != 0 )  // dword_8F7B08 —— 【发送网络包API】
  {
    LOBYTE(v2) = *(uint8_t *)(*(uint32_t *)(dword_8F7A24 + 16) + 48);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    if ( (uint8_t)v2 != 0 )
    {
      v2 = *(uint32_t *)(pArg1 + 68);  // 读字段 v2 = pArg1+68（nCharCount）
      if ( v2 == 4 )
      {
        if ( *(uint32_t *)(pArg1 + 72) != 1 )  // pArg1+72〔nSnapshot72(推断)〕
          sub_45DDA0(pArg1, 4);  // sub_45DDA0 —— 连接自检状态机（目标态 nArg2）
        LOBYTE(v2) = sub_445940(dword_8F8520);  // dword_8F8520 —— 虚表 +120 调用
        if ( (uint8_t)v2 == 0 )
          LOBYTE(v2) = sub_45DF90(pArg1);  // sub_45DF90 —— 中继(relay) 连接（_RELAY 自证）
      }
      else if ( v2 != 0 )
      {
        v4 = (uint8_t *)(pArg1 + 77);  // pArg1+77〔bGuildFlagB(推断)〕
        memset((void *)(pArg1 + 77), 0, 0x100u);  // pArg1+77〔bGuildFlagB(推断)〕
        *(uint32_t *)(pArg1 + 336) = 0;  // 写字段 pArg1+336 ← 0
        *(uint32_t *)(pArg1 + 340) = 0;  // 写字段 pArg1+340（pSlotTbl340） ← 0
        *(uint32_t *)(pArg1 + 344) = 0;  // 写字段 pArg1+344（nReservedDelay） ← 0
        *(uint32_t *)(pArg1 + 348) = 0;  // 写字段 pArg1+348（pParamTbl348） ← 0
        v16 = *(uint32_t *)(pArg1 + 16);  // 读字段 v16 = pArg1+16（nChannelTypeSel）
        fromlen = 16;
        if ( recvfrom(v16, (char *)(pArg1 + 77), 256, 0, (struct sockaddr *)(pArg1 + 336), &fromlen) == -1 || *v4 != 2 )  // 调 recvfrom（UDP 接收）
        {
          if ( *(uint32_t *)(pArg1 + 68) == 3 )  // pArg1+68〔nCharCount(推断)〕
          {
            LOBYTE(v2) = sub_45D890((void *)pArg1, (uint32_t *)(pArg1 + 352), 4);  // sub_45D890 —— UDP 识别完成回执（UDP IDENTIFIED 自证）
          }
          else
          {
            v20 = *(uint32_t *)(pArg1 + 68);  // 读字段 v20 = pArg1+68（nCharCount）
            *(uint32_t *)(pArg1 + 72) = 0;  // 写字段 pArg1+72（nSnapshot72） ← 0
            sub_45DDA0(pArg1, v20);  // sub_45DDA0 —— 连接自检状态机（目标态 nArg2）
            LOBYTE(v2) = sub_40BE20(aStunServer, pszArg2);  // sub_40BE20 —— 调 sub_40BE20
          }
        }
        else
        {
          v2 = *(uint32_t *)(pArg1 + 68);  // 读字段 v2 = pArg1+68（nCharCount）
          *(uint8_t *)(pArg1 + 400) = 0;  // 写字段 pArg1+400 ← 0
          switch ( v2 )  // 按 v2 分派
          {
            case 1:  // case 1 分派（对象管理器（0x45D190-0x45FB20））
              *(uint32_t *)(pArg1 + 356) = htonl(*(uint32_t *)(pArg1 + 78));  // 写字段 pArg1+356 ← htonl(*(uint32_t *)(pArg1 + 78))
              v5 = htons(*(uint16_t *)(pArg1 + 82));  // v5 = 调 htons
              v6 = *(struct in_addr *)(pArg1 + 356);
              *(uint16_t *)(pArg1 + 352) = v5;  // 写字段 pArg1+352（uHitCtx352） ← v5
              v7 = inet_ntoa(*(struct in_addr *)(pArg1 + 12));  // v7 = 调 inet_ntoa
              off_77F3FC("CHECK IP : [%s]", v7);  // off_77F3FC —— 日志打印（printf 风格）
              v17 = ntohs(*(uint16_t *)(pArg1 + 352));  // v17 = 调 ntohs
              v8 = inet_ntoa(v6);  // v8 = 调 inet_ntoa
              off_77F3FC("->[%s:%d]\n", v8, v17);  // off_77F3FC —— 日志打印（printf 风格）
              if ( *(uint32_t *)(pArg1 + 12) == *(uint32_t *)(pArg1 + 356) )  // pArg1+12〔nSkillRec12(推断)〕
                LOBYTE(v2) = sub_45D890((void *)pArg1, (uint32_t *)(pArg1 + 352), 1);  // sub_45D890 —— UDP 识别完成回执（UDP IDENTIFIED 自证）
              else
                LOBYTE(v2) = sub_45DDA0(pArg1, 2);  // sub_45DDA0 —— 连接自检状态机（目标态 nArg2）
              break;
            case 2:  // case 2 分派（对象管理器（0x45D190-0x45FB20））
              *(uint32_t *)(pArg1 + 364) = htonl(*(uint32_t *)(pArg1 + 78));  // 写字段 pArg1+364（pAnimNameStr） ← htonl(*(uint32_t *)(pArg1 + 78))
              v9 = htons(*(uint16_t *)(pArg1 + 82));  // v9 = 调 htons
              v10 = *(struct in_addr *)(pArg1 + 356);
              v11 = *(uint16_t *)(pArg1 + 352);  // 读字段 v11 = pArg1+352（uHitCtx352）
              v12 = *(uint32_t *)(pArg1 + 364);  // 读字段 v12 = pArg1+364（pAnimNameStr）
              *(uint16_t *)(pArg1 + 360) = v9;  // 写字段 pArg1+360 ← v9
              netshort[0] = v11;
              v23[0] = v9;
              *(struct in_addr *)&netshort[1] = v10;
              *(uint32_t *)&v23[1] = v12;
              v18 = ntohs(v11);  // v18 = 调 ntohs
              v13 = inet_ntoa(v10);  // v13 = 调 inet_ntoa
              off_77F3FC("CHECK IP : [%s:%d]", v13, v18);  // off_77F3FC —— 日志打印（printf 风格）
              v19 = ntohs(v23[0]);  // v19 = 调 ntohs
              v14 = inet_ntoa(*(struct in_addr *)&v23[1]);  // v14 = 调 inet_ntoa
              off_77F3FC("->[%s:%d]\n", v14, v19);  // off_77F3FC —— 日志打印（printf 风格）
              if ( *(uint32_t *)(pArg1 + 356) == *(uint32_t *)(pArg1 + 364) && *(uint16_t *)(pArg1 + 352) == *(uint16_t *)(pArg1 + 360) )  // pArg1+364〔pAnimNameStr(推断)〕
                LOBYTE(v2) = sub_45DDA0(pArg1, 3);  // sub_45DDA0 —— 连接自检状态机（目标态 nArg2）
              else
                LOBYTE(v2) = sub_45D890((void *)pArg1, (uint32_t *)(pArg1 + 360), 3);  // sub_45D890 —— UDP 识别完成回执（UDP IDENTIFIED 自证）
              break;
            case 3:  // case 3 分派（对象管理器（0x45D190-0x45FB20））
              LOBYTE(v2) = sub_45D890((void *)pArg1, (uint32_t *)(pArg1 + 352), 2);  // sub_45D890 —— UDP 识别完成回执（UDP IDENTIFIED 自证）
              break;
            default:
              break;
          }
        }
      }
    }
  }
  return v2;
}


// ------------------------------------------------------------
// 0x45E490 sub_45E490 —— 屏幕 y → 演出层坐标（减基线）
// 舞台(·+132)为空则原样返回；否则舞台 ·+192 + nArg2 - ·sub_48C1C0(nArg3)。
// ------------------------------------------------------------
int /*thiscall*/ sub_45E490(uint32_t *this, int nArg2, int nArg3)  // sub_45E490 —— 结果 = 屏幕 y → 演出层坐标（减基线）
{
  int fld_e33; // eax
  int v4; // esi

  fld_e33 = *(this + 33);  // 读字段 fld_e33 = this+33（bJobVecDirty）
  if ( fld_e33 == 0 )  // fld_e33=this+33 bJobVecDirty
    return nArg2;
  v4 = *(uint32_t *)(fld_e33 + 192);  // 读字段 v4 = fld_e33+192（nDlgId）
  return v4 + nArg2 - sub_48C1C0(nArg3);  // sub_48C1C0 —— 结果 = 演出层纵向基线换算（按类型取字段乘百分位）
}



// ------------------------------------------------------------
// 0x45E4D0 sub_45E4D0 —— 带比例的回换算（nArg2 - nArg3*f + 120）
// 再叠舞台 ·+196 与 (舞台 ·+44 表 +468) 的差值【推断：行距/基准缩放，与 ·sub_45E490 配对】。
// ------------------------------------------------------------
int /*thiscall*/ sub_45E4D0(uint32_t *this, int nArg2, int nArg3, int nArg4, float fArg5)  // sub_45E4D0 —— 结果 = 带比例的回换算（nArg2 - nArg3*f + 120）
{
  int fld_e33; // ecx
  int result; // eax

  fld_e33 = *(this + 33);  // 读字段 fld_e33 = this+33（bJobVecDirty）
  result = nArg2 - (uint64_t)((double)nArg3 * fArg5) + 120;
  if ( fld_e33 != 0 )  // fld_e33=this+33 bJobVecDirty
    result += *(uint32_t *)(fld_e33 + 196) - *(uint32_t *)(*(uint32_t *)(fld_e33 + 44) + 468);  // fld_e33=this+33 bJobVecDirty
  return result;
}



// ------------------------------------------------------------
// 0x45E510 sub_45E510 —— 与 ·sub_45E490 反向（层坐标 → 屏幕 y）
// 即 nArg2 - 舞台 ·+192 + 基线 ·sub_48C1C0(nArg3)。
// ------------------------------------------------------------
int /*thiscall*/ sub_45E510(uint32_t *this, int nArg2, int nArg3)  // sub_45E510 —— 结果 = 与 ·sub_45E490 反向（层坐标 → 屏幕 y）
{
  int fld_e33; // eax
  int v4; // esi

  fld_e33 = *(this + 33);  // 读字段 fld_e33 = this+33（bJobVecDirty）
  if ( fld_e33 == 0 )  // fld_e33=this+33 bJobVecDirty
    return nArg2;
  v4 = *(uint32_t *)(fld_e33 + 192);  // 读字段 v4 = fld_e33+192（nDlgId）
  return nArg2 - v4 + sub_48C1C0(nArg3);  // sub_48C1C0 —— 结果 = 演出层纵向基线换算（按类型取字段乘百分位）
}



// ------------------------------------------------------------
// 0x45E550 sub_45E550 —— 与 ·sub_45E4D0 配对的回换算（nArg2 + nArg3 - 120）
// 再叠 (舞台 ·+44 表 +468) - 舞台 ·+196 的差值。
// ------------------------------------------------------------
int /*thiscall*/ sub_45E550(uint32_t *this, int nArg2, int nArg3, int nArg4)  // sub_45E550 —— 结果 = 与 ·sub_45E4D0 配对的回换算（nArg2 + nArg3 - 120）
{
  int result; // eax
  int fld_e33; // edx

  result = nArg2 + nArg3 - 120;
  fld_e33 = *(this + 33);  // 读字段 fld_e33 = this+33（bJobVecDirty）
  if ( fld_e33 != 0 )  // fld_e33=this+33 bJobVecDirty
    result += *(uint32_t *)(*(uint32_t *)(fld_e33 + 44) + 468) - *(uint32_t *)(fld_e33 + 196);  // fld_e33=this+33 bJobVecDirty
  return result;
}



// ------------------------------------------------------------
// 0x45E580 sub_45E580 —— 容器计数（跨度 / 20）
// 20 字节元素向量的元素个数 getter。
// ------------------------------------------------------------
int /*thiscall*/ sub_45E580(int *this)  // sub_45E580 —— vector::size（+64 掉落概率表）
{
  int result; // eax

  result = *(this + 1);  // 读字段 result = this+1
  if ( result != 0 )  // result=this+4 宿主对象
    return (*(this + 2) - result) / 20;  // this+8〔nSkillRec8(推断)〕
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x45E5A0 sub_45E5A0 —— uint32 区间线性查找
// 返回 [uArg2, uArg3) 中首个等于 *uArg4 的迭代器（写回 *uArg1）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_45E5A0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3, uint32_t *uArg4)  // sub_45E5A0 —— uint32 区间线性查找
{
  uint32_t *uArg22; // ecx

  uArg22 = uArg2;
  if ( uArg2 == uArg3 )
  {
    *uArg1 = uArg2;
    return uArg1;
  }
  else
  {
    do
    {
      if ( *uArg22 == *uArg4 )
        break;
      ++uArg22;  // 计数自增 uArg22
    }
    while ( uArg22 != uArg3 );  // 循环直到 uArg22 != uArg3
    *uArg1 = uArg22;
    return uArg1;
  }
}



// ------------------------------------------------------------
// 0x45E5D0 sub_45E5D0 —— 指针向量插入排序（按 ·vt+124）
// 对 ·+40 表逐项后移插入，比较值为对象虚函数 vt+124。
// ------------------------------------------------------------
int /*thiscall*/ sub_45E5D0(uint32_t *this)  // sub_45E5D0 —— 指针向量插入排序（按 ·vt+124）
{
  int fld_e10; // ecx
  int result; // eax
  int v4; // edx
  int fld_e102; // ecx
  int v6; // ebx
  int fld_e103; // edi
  int fld_e104; // eax
  int v9; // ecx
  int v10; // eax
  bool v11; // zf
  int v12; // [esp+4h] [ebp-14h]
  int v13; // [esp+8h] [ebp-10h]
  int v14; // [esp+Ch] [ebp-Ch]
  int fld_e1022; // [esp+10h] [ebp-8h]
  int v16; // [esp+14h] [ebp-4h]

  fld_e10 = *(this + 10);  // 读字段 fld_e10 = this+10
  if ( fld_e10 != 0 )  // fld_e10=this+40 物品状态附属标志
    result = (*(this + 11) - fld_e10) >> 2;  // this+44〔nExpireMs(推断)〕
  else
    result = 0;  // result=this+44 nExpireMs
  if ( result > 1 )  // result=this+44 nExpireMs
  {
    v4 = 0;
    v14 = 0;
    v16 = 4;
    v13 = result - 1;  // 计算 v13 = result - 1
    do
    {
      fld_e102 = *(uint32_t *)(v16 + *(this + 10));  // this+40〔bStateSub40(推断)〕
      fld_e1022 = fld_e102;  // fld_e102=this+40 bStateSub40
      v6 = v4;
      if ( v4 >= 0 )
      {
        while ( 1 )
        {
          fld_e103 = *(uint32_t *)(*(this + 10) + 4 * v6);  // this+40〔bStateSub40(推断)〕
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e102 + 124))(fld_e102);  // 虚调用 vt+124（fld_e102）目标坐标y下界
          if ( v12 >= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e103 + 124))(fld_e103) )  // 虚调用 vt+124（fld_e103）目标坐标y下界
            break;
          fld_e104 = *(this + 10);  // 读字段 fld_e104 = this+10
          v9 = *(uint32_t *)(fld_e104 + 4 * v6);  // fld_e104=this+40 物品状态附属标志
          v10 = fld_e104 + 4 * v6--;  // fld_e104=this+40 物品状态附属标志
          *(uint32_t *)(v10 + 4) = v9;  // 写字段 v10+4（pHostObj） ← v9
          if ( v6 < 0 )
            break;
          fld_e102 = fld_e1022;  // fld_e102=this+40 bStateSub40
        }
        fld_e102 = fld_e1022;  // fld_e102=this+40 bStateSub40
        v4 = v14;
      }
      ++v4;  // 计数自增 v4
      result = v13 - 1;
      v11 = v13 == 1;
      *(uint32_t *)(*(this + 10) + 4 * v6 + 4) = fld_e102;  // this+40〔bStateSub40(推断)〕
      v16 += 4;
      v14 = v4;
      --v13;  // 计数自减 v13
    }
    while ( !v11 );
  }
  return result;  // result=this+44 nExpireMs
}



// ------------------------------------------------------------
// 0x45E680 sub_45E680 —— 对象表归属判定
// nArg2 是否在 ·+8 向量内（1/0），供 ·sub_45B1C0 等做失联剔除。
// ------------------------------------------------------------
char /*thiscall*/ sub_45E680(uint32_t *this, int nArg2)  // sub_45E680 —— 对象表归属判定
{
  int pVecCap_5; // edx
  int fld_e3; // eax
  int v4; // edx
  uint32_t *i; // ecx

  pVecCap_5 = *(this + 2);  // 读字段 fld_e2 = this+2
  if ( pVecCap_5 != 0 )  // fld_e2=this+8 物品 id
    fld_e3 = (*(this + 3) - pVecCap_5) >> 2;  // this+12〔nSkillRec12(推断)〕
  else
    fld_e3 = 0;  // fld_e3=this+12 nSkillRec12
  v4 = 0;
  if ( fld_e3 <= 0 )  // fld_e3=this+12 nSkillRec12
    return 0;
  for ( i = (uint32_t *)*(this + 2); *i != nArg2; ++i )  // this+8〔nSkillRec8(推断)〕
  {
    if ( ++v4 >= fld_e3 )  // fld_e3=this+12 nSkillRec12
      return 0;
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x45E6C0 sub_45E6C0 —— 对象表 id 对匹配判定
// 命中条件：·vt+48 == nArg2 且 ·vt+52 == nArg3（返回 1/0）。
// ------------------------------------------------------------
char /*thiscall*/ sub_45E6C0(uint32_t *this, int nArg2, int nArg3)  // sub_45E6C0 —— 对象表 id 对匹配判定
{
  int pVecCap_5; // ecx
  int v5; // ebx
  int fld_e22; // ecx
  int fld_e3; // [esp+Ch] [ebp-4h]

  pVecCap_5 = *(this + 2);  // 读字段 fld_e2 = this+2
  v5 = 0;
  if ( pVecCap_5 != 0 )  // fld_e2=this+8 物品 id
    fld_e3 = (*(this + 3) - pVecCap_5) >> 2;  // this+12〔nSkillRec12(推断)〕
  else
    fld_e3 = 0;  // fld_e3=this+12 nSkillRec12
  if ( fld_e3 <= 0 )  // fld_e3=this+12 nSkillRec12
    return 0;
  while ( 1 )
  {
    fld_e22 = *(uint32_t *)(*(this + 2) + 4 * v5);  // this+8〔nSkillRec8(推断)〕
    if ( fld_e22 != 0  // fld_e22=this+8 nSkillRec8
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e22 + 48))(fld_e22) == nArg2  // 虚调用 vt+48（fld_e22）归属坐标x
      && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(4 * v5 + *(this + 2)) + 52))(*(uint32_t *)(4 * v5 + *(this + 2))) == nArg3 )  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15 行…
    {
      break;
    }
    if ( ++v5 >= fld_e3 )  // fld_e3=this+12 nSkillRec12
      return 0;
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x45E740 sub_45E740 —— 分组逐对象刷新
// 第 nArg2 组(·+24+16n) 逐项 ·vt+16；组 1 额外 ·sub_45E5D0 排序并逐项 ·vt+24；末统一 ·vt+20。
// ------------------------------------------------------------
int /*thiscall*/ sub_45E740(uint32_t *this, int nArg2)  // sub_45E740 —— 分组逐对象刷新
{
  uint32_t *pThis_4; // ebx
  int result; // eax
  int v4; // esi
  int v5; // edi
  int i; // edi
  int j; // edi
  int pObj; // ecx
  uint32_t *pThis; // [esp+Ch] [ebp-4h]

  pThis_4 = this + 4 * nArg2;
  result = pThis_4[6];
  pThis = this;
  if ( result != 0 )
    v4 = (pThis_4[7] - result) >> 2;
  else
    v4 = 0;
  v5 = 0;
  if ( v4 > 0 )
  {
    do
    {
      result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pThis_4[6] + 4 * v5) + 16))(*(uint32_t *)(pThis_4[6] + 4 * v5));  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE…
      ++v5;  // 计数自增 v5
    }
    while ( v5 < v4 );  // 循环直到 v5 < v4
    this = pThis;
  }
  if ( nArg2 == 1 )
  {
    result = sub_45E5D0(this);  // sub_45E5D0 —— 指针向量插入排序（按 ·vt+124）
    for ( i = 0; i < v4; ++i )  // 遍历计次循环（i < v4）
      result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pThis[10] + 4 * i) + 24))(*(uint32_t *)(pThis[10] + 4 * i));  // 调虚槽 +24：CNRDSkillInventoryWindow__vmt18 页签动作（41A5E0 + 44…
  }
  for ( j = 0; j < v4; ++j )  // 遍历计次循环（j < v4）
  {
    pObj = *(uint32_t *)(pThis_4[6] + 4 * j);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 20))(pObj);  // 虚调用 vt+20（pObj）条件位掩码测试(273受击/17有血/65机械)
  }
  return result;
}



// ------------------------------------------------------------
// 0x45E7D0 sub_45E7D0 —— 索敌目标筛选（·+120 表）
// nArg2 需在对象表(·+8) 且 ·vt+428/432 非 0，再从 ·+120 取 ·vt+484(nArg2, x) 成立的敌对目标【推断：合法性预筛】。
// ------------------------------------------------------------
int /*thiscall*/ sub_45E7D0(uint32_t *this, int nArg2)  // sub_45E7D0 —— 索敌目标筛选（·+120 表）
{
  int pVecCap_5; // ecx
  int fld_e3; // eax
  int v5; // ecx
  uint32_t *i; // edx
  uint32_t *fld_e30; // esi

  pVecCap_5 = *(this + 2);  // 读字段 fld_e2 = this+2
  if ( pVecCap_5 != 0 )  // fld_e2=this+8 物品 id
    fld_e3 = (*(this + 3) - pVecCap_5) >> 2;  // this+12〔nSkillRec12(推断)〕
  else
    fld_e3 = 0;  // fld_e3=this+12 nSkillRec12
  v5 = 0;
  if ( fld_e3 <= 0 )  // fld_e3=this+12 nSkillRec12
    return 0;
  for ( i = (uint32_t *)*(this + 2); *i != nArg2; ++i )  // this+8〔nSkillRec8(推断)〕
  {
    if ( ++v5 >= fld_e3 )  // fld_e3=this+12 nSkillRec12
      return 0;
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 428))(nArg2) == 0  // 虚调用 vt+428（nArg2 虚表槽）
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 432))(nArg2) == 0 )  // 虚调用 vt+432（nArg2 虚表槽）
  {
    return 0;
  }
  fld_e30 = (uint32_t *)*(this + 30);  // this+120〔pAnimObj〕
  if ( fld_e30 == (uint32_t *)*(this + 31) )  // this+124〔pAuraAnim(推断)〕
    return 0;
  while ( *fld_e30 == nArg2 || (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)nArg2 + 484))(nArg2, *fld_e30) == 0 )  // 虚调用 vt+484（nArg2 虚表槽）
  {
    if ( ++fld_e30 == (uint32_t *)*(this + 31) )  // this+124〔pAuraAnim(推断)〕
      return 0;
  }
  return *fld_e30;  // fld_e30=this+120 pAnimObj
}



// ------------------------------------------------------------
// 0x45E870 sub_45E870 —— 光标点选对象（倒序遍历 ·+40 表）
// 主态 ·dword_8F8528+2504 == 16 或舞台锁屏直接空；按 ·vt+40 类型 18/34/66 分支走 ·vt+380/344/336 命中测试，
// 类型 66 还需 +285 = 0 且 (+284 非 0 或 ·sub_42FB30 组件匹配)；pszArg5 非 0 时排除当前选中对象。
// ------------------------------------------------------------
uint8_t */*userpurge*/ sub_45E870@<eax>(int pArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4, char pszArg5)  // 实现：光标点选对象（倒序遍历 ·+40 表）
{
  int pArg12; // edx
  int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  uint8_t *pObj; // esi
  char v14; // al
  int v17; // [esp+4h] [ebp-4h]

  pArg12 = pArg1;
  if ( *((uint32_t *)dword_8F8528 + 626) == 16 )  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    return nullptr;
  v7 = *(uint32_t *)(pArg1 + 132);  // 读字段 v7 = pArg1+132（nAdd132）
  if ( v7 != 0 )
  {
    v8 = *(uint32_t *)(v7 + 36);  // 读字段 v8 = v7+36（nStateWord36）
    if ( *(uint8_t *)(v8 + 17) == 0 )
      return nullptr;
    v9 = *(uint32_t *)(v8 + 12);  // 读字段 v9 = v8+12（nSkillRec12）
    if ( dword_79BE3C != v9 && (*(uint8_t *)(v8 + 17) == 0 || dword_79BE34 != v9) )  // 判定 dword_79BE3C != v9 且 dword_79BE34 != v9
      return nullptr;
  }
  v10 = *(uint32_t *)(pArg1 + 40);  // 读字段 v10 = pArg1+40（bStateSub40）
  if ( v10 != 0 )
    v11 = (*(uint32_t *)(pArg12 + 44) - v10) >> 2;  // pArg12+44〔nExpireMs(推断)〕
  else
    v11 = 0;
  v12 = v11 - 1;  // 计算 v12 = v11 - 1
  v17 = v12;
  if ( v12 < 0 )
    return nullptr;
  while ( 1 )
  {
    pObj = *(uint8_t **)(*(uint32_t *)(pArg12 + 40) + 4 * v12);  // pArg12+40〔bStateSub40(推断)〕
    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pObj + 40))(pObj, 18) != 0 )  // 虚调用 vt+40（pObj）条件查询(273等)
    {
      if ( pszArg5 == 0 || (uint8_t *)dword_8F7C08 != pObj )  // dword_8F7C08 —— 副玩家/观战
      {
        v14 = (*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pObj + 380))(pObj, nArg3, nArg4);  // 虚调用 vt+380（pObj）判定体获取
        goto LABEL_26;
      }
      goto LABEL_27;
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pObj + 40))(pObj, 34, nArg2) != 0 )  // 虚调用 vt+40（pObj）条件查询(273等)
    {
      nArg2 = nArg4;
      v14 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pObj + 344))(pObj, nArg3);  // 虚调用 vt+344（pObj）动画件访问(基偏移)
      goto LABEL_26;
    }
    nArg2 = 66;
    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 40))(pObj) != 0  // 虚调用 vt+40（pObj）条件查询(273等)
      && pObj[285] == 0
      && (pObj[284] != 0 || sub_42FB30((uint32_t *)dword_8F7C08, (int)pObj)) )  // sub_42FB30 —— 组件匹配判定
    {
      break;
    }
LABEL_27:
    if ( --v17 < 0 )
      return nullptr;
    v12 = v17;
    pArg12 = pArg1;
  }
  v14 = (*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pObj + 336))(pObj, nArg3, nArg4);  // 虚调用 vt+336（pObj 虚表槽）
LABEL_26:
  if ( v14 == 0 )
    goto LABEL_27;
  return pObj;
}



// ------------------------------------------------------------
// 0x45E9B0 sub_45E9B0 —— 点选最近对象（50x50 判定框）
// 以 ·vt+120/124 与 50/25 构建 v17 框，倒序扫 ·+40 表：类型 18/34、非当前选中(·dword_8F7C08)、
// 落框内(·sub_48C0A0)者取 ·vt+8 距离最小。
// ------------------------------------------------------------
int /*thiscall*/ sub_45E9B0(uint32_t *this, int *pDwArg2)  // sub_45E9B0 —— 点选最近对象（50x50 判定框）
{
  int pObj2; // ebx
  uint32_t *pThis; // esi
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int pObj; // esi
  int v14; // eax
  int v15; // eax
  int v16; // [esp-8h] [ebp-2Ch]
  int v17; // [esp+Ch] [ebp-18h] BYREF
  int v18; // [esp+10h] [ebp-14h]
  int v19; // [esp+14h] [ebp-10h]
  int v20; // [esp+18h] [ebp-Ch]
  uint32_t *pThis2; // [esp+1Ch] [ebp-8h]
  int v22; // [esp+20h] [ebp-4h]
  int v23; // [esp+2Ch] [ebp+8h]

  pObj2 = 0;
  pThis = this;
  pThis2 = this;
  if ( pDwArg2 == nullptr )
    return 0;
  v19 = 50;
  v20 = 50;
  v6 = *pDwArg2;
  v17 = 0;
  v18 = 0;
  if ( (*(int (/*thiscall*/ **)(int *))(v6 + 152))(pDwArg2) == 1 )  // 调虚槽 +152：效果通道 3
    v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 120))(pDwArg2);  // 虚调用 vt+120（pDwArg2）转发(对象+缓冲)
  else
    v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 120))(pDwArg2) - v19;  // 虚调用 vt+120（pDwArg2）转发(对象+缓冲)
  v8 = *pDwArg2;
  v17 = v7;
  v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 124))(pDwArg2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
  v10 = pThis[10];
  v18 = v9 - 25;  // 计算 v18 = v9 - 25
  v22 = 0;
  if ( v10 != 0 )
    v11 = (pThis[11] - v10) >> 2;
  else
    v11 = 0;
  v12 = v11 - 1;  // 计算 v12 = v11 - 1
  v23 = v12;
  if ( v12 >= 0 )
  {
    while ( 1 )
    {
      pObj = *(uint32_t *)(pThis[10] + 4 * v12);
      if ( ((*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 18) != 0  // 虚调用 vt+40（pObj）条件查询(273等)
         || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 34) != 0)  // 虚调用 vt+40（pObj）条件查询(273等)
        && dword_8F7C08 != pObj )  // dword_8F7C08 —— 副玩家/观战
      {
        v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 虚调用 vt+124（pObj）目标坐标y下界
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 虚调用 vt+120（pObj）转发(对象+缓冲)
        if ( (uint8_t)sub_48C0A0(v14, v16, &v17) != 0 )  // sub_48C0A0 —— 点是否落在 {x, y, 宽, 高} 矩形内
        {
          v15 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*pDwArg2 + 8))(pDwArg2, pObj, 0);  // 虚调用 vt+8（pDwArg2 虚表槽）
          if ( pObj2 == 0 || v15 < v22 )
          {
            pObj2 = pObj;
            v22 = v15;
          }
        }
      }
      if ( --v23 < 0 )
        break;
      pThis = pThis2;
      v12 = v23;
    }
  }
  return pObj2;
}



// ------------------------------------------------------------
// 0x45EAC0 sub_45EAC0 —— 拖拽落点目标搜索（·+56 表，48x36 框）
// 要求 ·vt+40(289) 且 +977 未占用；与 ·vt+440..452 边界互交测试后取 ·vt+8 最近者。
// ------------------------------------------------------------
int /*thiscall*/ sub_45EAC0(uint32_t *this, int nArg2)  // sub_45EAC0 —— 拖拽落点目标搜索（·+56 表，48x36 框）
{
  uint32_t *pThis; // ebx
  int fld_e14; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // esi
  int pObj3; // ecx
  int pObj2; // eax
  int pObj; // esi
  int v10; // ebx
  int v11; // ebx
  int v12; // ebx
  int v13; // ebx
  int v14; // eax
  uint32_t *pThis2; // [esp+4h] [ebp-10h]
  int v17; // [esp+8h] [ebp-Ch]
  int v18; // [esp+Ch] [ebp-8h]
  int pObj4; // [esp+10h] [ebp-4h]

  pThis = this;
  fld_e14 = *(this + 14);  // 读字段 fld_e14 = this+14
  pThis2 = pThis;
  pObj4 = 0;
  v18 = 0;
  if ( fld_e14 != 0 )  // fld_e14=this+56 键盘输入使能
    v4 = (pThis[15] - fld_e14) >> 2;  // fld_e14=this+56 键盘输入使能
  else
    v4 = 0;
  v5 = v4 - 1;  // 计算 v5 = v4 - 1
  v17 = v5;
  if ( v5 < 0 )
    return 0;
  while ( 1 )
  {
    v6 = 4 * v5;  // 计算 v6 = 4 * v5
    pObj3 = *(uint32_t *)(4 * v5 + pThis[14]);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 289) != 0 )  // 虚调用 vt+40（pObj3）条件查询(273等)
    {
      pObj2 = v6 + pThis[14];
      pObj = *(uint32_t *)pObj2;
      if ( *(uint8_t *)(*(uint32_t *)pObj2 + 977) == 0 )
      {
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) - 24;  // 虚调用 vt+120（pObj）转发(对象+缓冲)
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 444))(nArg2) >= v10 )  // 虚调用 vt+444（nArg2 虚表槽）
        {
          v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) + 24;  // 虚调用 vt+120（pObj）转发(对象+缓冲)
          if ( v11 >= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 440))(nArg2) )  // 虚调用 vt+440（nArg2 虚表槽）
          {
            v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj) - 18;  // 虚调用 vt+124（pObj）目标坐标y下界
            if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 452))(nArg2) >= v12 )  // 虚调用 vt+452（nArg2 虚表槽）
            {
              v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj) + 18;  // 虚调用 vt+124（pObj）目标坐标y下界
              if ( v13 >= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 448))(nArg2) )  // 虚调用 vt+448（nArg2 虚表槽）
              {
                v14 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)nArg2 + 8))(nArg2, pObj, 1);  // 虚调用 vt+8（nArg2 虚表槽）
                if ( pObj4 == 0 || v14 < v18 )
                {
                  pObj4 = pObj;
                  v18 = v14;
                }
              }
            }
          }
        }
      }
    }
    v5 = --v17;
    if ( v17 < 0 )
      break;
    pThis = pThis2;
  }
  return pObj4;
}



// ------------------------------------------------------------
// 0x45EBE0 sub_45EBE0
// ------------------------------------------------------------
// id 对 → 对象查找（战斗分发器全 case 共用解析器）：
// 遍历 +2 对象表，vt+48/vt+52 返回值与 (a2,a3) 双字匹配 → 返回对象，未中 0
int /*thiscall*/ sub_45EBE0(uint32_t *this, int nArg2, int nArg3)  // sub_45EBE0 —— 存 id 对 → 对象查找
{
  int pVecCap_5; // ecx
  int v5; // ebx
  int fld_e22; // ecx
  int fld_e3; // [esp+Ch] [ebp-4h]

  pVecCap_5 = *(this + 2);  // 读字段 fld_e2 = this+2
  v5 = 0;
  if ( pVecCap_5 != 0 )  // fld_e2=this+8 物品 id
    fld_e3 = (*(this + 3) - pVecCap_5) >> 2;  // this+12〔nSkillRec12(推断)〕
  else
    fld_e3 = 0;  // fld_e3=this+12 nSkillRec12
  if ( fld_e3 <= 0 )  // fld_e3=this+12 nSkillRec12
    return 0;
  while ( 1 )
  {
    fld_e22 = *(uint32_t *)(4 * v5 + *(this + 2));  // this+8〔nSkillRec8(推断)〕
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e22 + 48))(fld_e22) == nArg2  // 虚调用 vt+48（fld_e22）归属坐标x
      && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(4 * v5 + *(this + 2)) + 52))(*(uint32_t *)(4 * v5 + *(this + 2))) == nArg3 )  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15 行…
    {
      break;
    }
    if ( ++v5 >= fld_e3 )  // fld_e3=this+12 nSkillRec12
      return 0;
  }
  return *(uint32_t *)(*(this + 2) + 4 * v5);  // 返回 读 this+2
}



// ------------------------------------------------------------
// 0x45EC70 sub_45EC70 —— 两两通知（·+120 表 O(n^2)）
// 对每对 (i, j) 调 ·vt+476(table[i], table[j])【推断：碰撞/可见性两两分发】。
// ------------------------------------------------------------
int /*thiscall*/ sub_45EC70(uint32_t *this)  // sub_45EC70 —— 两两通知（·+120 表 O(n^2)）
{
  int pAnimObj; // eax
  int fld_e31; // edi
  int result; // eax
  int v4; // esi
  int v5; // ebx
  int i; // [esp+8h] [ebp-4h]

  pAnimObj = *(this + 30);  // 读字段 fld_e30 = this+30
  if ( pAnimObj != 0 )  // fld_e30=this+30 pAnimObj
    fld_e31 = (*(this + 31) - pAnimObj) >> 2;  // this+124〔pAuraAnim(推断)〕
  else
    fld_e31 = 0;  // fld_e31=this+124 pAuraAnim
  result = 0;
  for ( i = 0; i < fld_e31; ++i )  // 遍历计次循环（i < fld_e31）
  {
    v4 = 0;
    v5 = 4 * result;  // 计算 v5 = 4 * result
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*(this + 30) + 4 * v4) + 476))(  // this+120〔pAnimObj〕
        *(uint32_t *)(*(this + 30) + 4 * v4),  // this+120〔pAnimObj〕
        *(uint32_t *)(v5 + *(this + 30)));  // this+120〔pAnimObj〕
      ++v4;  // 计数自增 v4
    }
    while ( v4 < fld_e31 );  // 循环直到 v4 < fld_e31
    result = i + 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x45ECE0 sub_45ECE0 —— 对象表逐项刷新钩子
// 对 ·+8 表每项调 ·vt+12（每帧时钟推进/动画刷新）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45ECE0(uint32_t *this)  // sub_45ECE0 —— 对象表逐项刷新钩子
{
  uint32_t *fld_e2; // esi
  uint32_t *result; // eax

  fld_e2 = (uint32_t *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( fld_e2 != (uint32_t *)*(this + 3) )  // this+12〔nSkillRec12(推断)〕
  {
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e2 + 12))(*fld_e2);  // 虚调用 vt+12（fld_e2 虚表槽）
      result = (uint32_t *)*(this + 3);  // this+12〔nSkillRec12(推断)〕
      ++fld_e2;  // 计数自增 fld_e2
    }
    while ( fld_e2 != result );  // 循环直到 fld_e2 != result
  }
  return result;  // result=this+12 nSkillRec12
}



// ------------------------------------------------------------
// 0x45ED10 sub_45ED10 —— 全局暂停/恢复
// pszArg2 真 = 暂停：·+8 表逐项 ·vt+228(2/0, -1, 0)，并冻结(·sub_699030)/解冻(·sub_698FE0)
// ·unk_9B0C70、·unk_99FC80 两只时钟。
// ------------------------------------------------------------
char /*thiscall*/ sub_45ED10(int **this, char pszArg2)  // sub_45ED10 —— 全局暂停/恢复
{
  int *i; // esi
  int pObj; // ecx

  for ( i = *(this + 2); i != *(this + 3); ++i )  // this+8〔nSkillRec8(推断)〕等 2 字段
  {
    pObj = *i;
    if ( pszArg2 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 228))(pObj, 2, -1, 0);  // 虚调用 vt+228（pObj）主状态写入(state,param,flag)
    else
      (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t))(*(uint32_t *)pObj + 228))(pObj, 0, -1, 0);  // 虚调用 vt+228（pObj）主状态写入(state,param,flag)
  }
  if ( pszArg2 != 0 )
  {
    sub_699030((int)&unk_9B0C70);  // 【clock_freeze(clk)】
    return sub_699030((int)&unk_99FC80);  // 【clock_freeze(clk)】
  }
  else
  {
    sub_698FE0((int)&unk_9B0C70);  // 【clock_unfreeze(clk)】
    return sub_698FE0((int)&unk_99FC80);  // 【clock_unfreeze(clk)】
  }
}



// ------------------------------------------------------------
// 0x45ED80 sub_45ED80
// ------------------------------------------------------------
// 对象移除 —— 分发器 case 0x21 落点【推断：退场清理】
uint32_t */*thiscall*/ sub_45ED80(uint32_t *this, int nArg2)  // 实现：对象移除 —— 分发器 case 0x21 落点(推断：退场清理)
{
  uint32_t *fld_e30; // esi
  uint32_t *result; // eax

  fld_e30 = (uint32_t *)*(this + 30);  // this+120〔pAnimObj〕
  if ( fld_e30 != (uint32_t *)*(this + 31) )  // this+124〔pAuraAnim(推断)〕
  {
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*fld_e30 + 536))(*fld_e30, nArg2);  // 虚调用 vt+536（fld_e30 虚表槽）
      result = (uint32_t *)*(this + 31);  // this+124〔pAuraAnim(推断)〕
      ++fld_e30;  // 计数自增 fld_e30
    }
    while ( fld_e30 != result );  // 循环直到 fld_e30 != result
  }
  return result;  // result=this+124 pAuraAnim
}



// ------------------------------------------------------------
// 0x45EDB0 sub_45EDB0 —— 位置同步节流（每 1000ms）
// 以 ·dword_8F8520 组 34/2 头，遍历 ·+120 表取 ·vt+40(529) 可动对象，·vt+1124 坐标与缓存(+7632/+7636) 不同
// 即发 id 对与坐标；末尾写 0xFFFF 收尾并 ·vt+60(1, -1) 提交。
// ------------------------------------------------------------
DWORD /*thiscall*/ sub_45EDB0(uint32_t *this)  // sub_45EDB0 —— 位置同步节流（每 1000ms）
{
  DWORD result; // eax
  int v3; // edx
  int pAnimObj; // eax
  int v5; // esi
  int fld_e302; // ecx
  uint32_t *fld_e303; // esi
  int v8; // ebx
  int v9; // ebx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // [esp+8h] [ebp-18h]
  int v14; // [esp+Ch] [ebp-14h]
  int v15; // [esp+10h] [ebp-10h] BYREF
  int v16; // [esp+14h] [ebp-Ch] BYREF
  DWORD v17; // [esp+18h] [ebp-8h]
  int fld_e31; // [esp+1Ch] [ebp-4h]

  result = GetTickCount();  // result = 调 GetTickCount
  if ( *(this + 39) + 1000 <= result )
  {
    *(this + 39) = GetTickCount();  // 写字段 this+39 ← GetTickCount()
    v3 = *(uint32_t *)dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
    v17 = 0;
    (*(void (/*thiscall*/ **)(int, int, int))(v3 + 8))(dword_8F8520, 34, 2);  // dword_8F8520 —— 虚表 +120 调用
    pAnimObj = *(this + 30);  // 读字段 fld_e30 = this+30
    fld_e31 = pAnimObj != 0 ? (*(this + 31) - pAnimObj) >> 2 : 0;  // this+124〔pAuraAnim(推断)〕
    result = 0;
    v14 = 0;
    if ( fld_e31 > 0 )  // fld_e31=this+124 pAuraAnim
    {
      do
      {
        v5 = 4 * result;  // 计算 v5 = 4 * result
        fld_e302 = *(uint32_t *)(4 * result + *(this + 30));  // this+120〔pAnimObj〕
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e302 + 40))(fld_e302, 529) != 0  // 虚调用 vt+40（fld_e302）条件查询(273等)
          && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v5 + *(this + 30)) + 308))(*(uint32_t *)(v5 + *(this + 30))) != 0 )  // this+120〔pAnimObj〕
        {
          fld_e303 = *(uint32_t **)(v5 + *(this + 30));  // this+120〔pAnimObj〕
          if ( (*(int (/*thiscall*/ **)(uint32_t *))(*fld_e303 + 840))(fld_e303) == 0 )  // 虚调用 vt+840（fld_e303 虚表槽）
          {
            v8 = fld_e303[1908];  // fld_e303=this+120 pAnimObj
            v13 = fld_e303[1909];  // fld_e303=this+120 pAnimObj
            (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(*fld_e303 + 1124))(fld_e303, &v16, &v15);  // 虚调用 vt+1124（fld_e303 虚表槽）
            if ( v8 != v16 || v13 != v15 )
            {
              v9 = *(uint32_t *)dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
              v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*fld_e303 + 48))(fld_e303);  // 虚调用 vt+48（fld_e303）归属坐标x
              (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);  // dword_8F8520 —— 虚表 +120 调用
              v11 = *(uint32_t *)dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
              v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*fld_e303 + 52))(fld_e303);  // 虚调用 vt+52（fld_e303）归属坐标y
              (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);  // dword_8F8520 —— 虚表 +120 调用
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v16);  // 虚调用 vt+32（dword_8F8520 虚表槽）
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v15);  // 虚调用 vt+32（dword_8F8520 虚表槽）
              ++v17;  // 计数自增 v17
            }
          }
        }
        result = ++v14;
      }
      while ( v14 < fld_e31 );  // 循环直到 v14 < fld_e31
      result = v17;
      if ( v17 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0xFFFF);  // 虚调用 vt+36（dword_8F8520 虚表槽）
        return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 虚调用 vt+60（dword_8F8520）对象销毁/释放
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x45EF30 sub_45EF30
// ------------------------------------------------------------
// 全场怪物参数批量同步 —— 分发器 case 0x22 落点：
// dword_8F8520 vt+76 逐对象读 id 对 → IRDMonster → vt+1128(4 参数)；
// 值相等则以 -2 抹平（1 万次上限，aCriticalErrorC_1 自证溢出）
int /*thiscall*/ sub_45EF30(uint32_t *this)  // 实现：值相等则以 -2 抹平（1 万次上限，aCriticalErrorC_1 自证溢出）
{
  int v1; // esi
  int result; // eax
  int v3; // eax
  uint32_t *v4; // eax
  char v5; // bl
  int v6; // ecx
  int v7; // esi
  char v8; // dl
  int v9; // [esp+Ch] [ebp-14h]
  uint16_t v11; // [esp+14h] [ebp-Ch] BYREF
  uint16_t v12[3]; // [esp+18h] [ebp-8h] BYREF
  char v13; // [esp+1Eh] [ebp-2h] BYREF
  char v14; // [esp+1Fh] [ebp-1h] BYREF

  v1 = 10000;
  v14 = -2;
  v13 = -2;
  while ( 1 )
  {
    result = (*(int (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, v12);  // 虚调用 vt+76（dword_8F8520 虚表槽）
    if ( v12[0] == 0xFFFF )
      break;
    v1 += 0xFFFF;
    v9 = v1;
    (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v11);  // 虚调用 vt+76（dword_8F8520 虚表槽）
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &v14);  // 虚调用 vt+72（dword_8F8520 虚表槽）
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &v13);  // 虚调用 vt+72（dword_8F8520 虚表槽）
    v3 = sub_45EBE0(this, v12[0], v11);  // sub_45EBE0 —— 存 id 对 → 对象查找
    v4 = (uint32_t *)__RTDynamicCast(v3, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    if ( v4 != nullptr )
    {
      v5 = v14;
      v6 = v4[1908];
      v7 = v4[1909];
      if ( v6 == v14 )
      {
        v6 = -2;
        v5 = -2;
        v14 = -2;
      }
      v8 = v13;
      if ( v7 == v13 )
      {
        v8 = -2;
        v7 = -2;
        v13 = -2;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*v4 + 1128))(v4, v5, v8, v6, v7);  // 虚调用 vt+1128（v4 虚表槽）
      v1 = v9;
    }
    if ( (uint16_t)v1 == 0 )
      return off_77F3FC(aCriticalErrorC_1);  // off_77F3FC —— 日志打印（printf 风格）
  }
  return result;
}



// ------------------------------------------------------------
// 0x45F040 sub_45F040 —— 轻量复位
// +132/+0 归零、+152/+153 清标志，并释放 ·+8 缓冲（三段指针清空）。
// ------------------------------------------------------------
void /*thiscall*/ sub_45F040(void *this)  // sub_45F040 —— 轻量复位
{
  *((uint32_t *)this + 33) = 0;  // 写字段 this+33（bJobVecDirty）
  *(uint32_t *)this = 0;  // *this = 0
  *((uint8_t *)this + 152) = 0;  // 写字段 this+152（nAdd152）
  if ( *((uint32_t *)this + 2) != 0 )  // this+8〔nSkillRec8(推断)〕
    j__free(*((void **)this + 2));  // 释放堆块
  *((uint32_t *)this + 2) = 0;  // 写字段 this[2]（宽4字节）
  *((uint32_t *)this + 3) = 0;  // 写字段 this[3]（宽4字节）
  *((uint32_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
  *((uint8_t *)this + 153) = 0;  // 写字段 this+153（bCastFlagA）
}



// ------------------------------------------------------------
// 0x45F080 sub_45F080 —— 对象管理器清空（析构前段）
// ·+8 表逐项 ·vt+76(0) 解挂，非 273/18/65/66/129/130 型 vt[0](1) 自毁；
// 再释放 ·+8 表、·+24 起六个 16 字节分组向量与 ·+120 表。
// ------------------------------------------------------------
void /*thiscall*/ sub_45F080(int this)  // sub_45F080 —— 对象管理器清空（析构前段）
{
  int pVecCap_5; // eax
  int v3; // ebx
  int v4; // esi
  int fld_82; // ecx
  void (/*thiscall*/ ***fld_83)(uint32_t, int); // eax
  int pThis_18; // esi
  int i; // ebx
  int fld_C; // [esp+Ch] [ebp-4h]

  pVecCap_5 = *(uint32_t *)(this + 8);  // 读字段 fld_8 = this+8（nSkillRec8）
  v3 = 0;
  if ( pVecCap_5 != 0 )  // fld_8=this+8 nSkillRec8
    fld_C = (*(uint32_t *)(this + 12) - pVecCap_5) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    fld_C = 0;  // fld_C=this+12 nSkillRec12
  if ( fld_C > 0 )  // fld_C=this+12 nSkillRec12
  {
    do
    {
      v4 = 4 * v3;  // 计算 v4 = 4 * v3
      fld_82 = *(uint32_t *)(4 * v3 + *(uint32_t *)(this + 8));  // this+8〔nSkillRec8(推断)〕等 2 字段
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_82 + 76))(fld_82, 0);  // 虚调用 vt+76（fld_82 虚表槽）
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(uint32_t *)(this + 8)) + 40))(  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
             *(uint32_t *)(v4 + *(uint32_t *)(this + 8)),  // this+8 物品 id
             273) == 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(uint32_t *)(this + 8)) + 40))(  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
             *(uint32_t *)(v4 + *(uint32_t *)(this + 8)),  // this+8 物品 id
             18) == 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(uint32_t *)(this + 8)) + 40))(  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
             *(uint32_t *)(v4 + *(uint32_t *)(this + 8)),  // this+8 物品 id
             65) == 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(uint32_t *)(this + 8)) + 40))(  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
             *(uint32_t *)(v4 + *(uint32_t *)(this + 8)),  // this+8 物品 id
             66) == 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(uint32_t *)(this + 8)) + 40))(  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
             *(uint32_t *)(v4 + *(uint32_t *)(this + 8)),  // this+8 物品 id
             129) == 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(uint32_t *)(this + 8)) + 40))(  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
             *(uint32_t *)(v4 + *(uint32_t *)(this + 8)),  // this+8 物品 id
             130) == 0 )
      {
        fld_83 = *(void (/*thiscall*/ ****)(uint32_t, int))(v4 + *(uint32_t *)(this + 8));  // this+8〔nSkillRec8(推断)〕等 2 字段
        if ( fld_83 != nullptr )  // fld_83=this+8 nSkillRec8
          (**fld_83)(fld_83, 1);  // 调 fld_83 的虚函数（vt+0）
      }
      ++v3;  // 计数自增 v3
    }
    while ( v3 < fld_C );  // 循环直到 v3 < fld_C
  }
  if ( *(uint32_t *)(this + 8) != 0 )  // this+8〔nSkillRec8(推断)〕等 2 字段
    j__free(*(void **)(this + 8));  // 释放堆块
  *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  *(uint32_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  *(uint32_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
  pThis_18 = this + 24;  // this+24 页数上限
  for ( i = 6; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    if ( *(uint32_t *)pThis_18 != 0 )  // pThis_18=this+24 页数上限
      j__free(*(void **)pThis_18);  // 释放堆块
    *(uint32_t *)pThis_18 = 0;  // *pThis_18 = 0
    *(uint32_t *)(pThis_18 + 4) = 0;  // 写字段 pThis_18+4（pHostObj） ← 0
    *(uint32_t *)(pThis_18 + 8) = 0;  // 写字段 pThis_18+8（nSkillRec8） ← 0
    pThis_18 += 16;  // pThis_18=this+24 页数上限
  }
  if ( *(uint32_t *)(this + 120) != 0 )  // this+120〔pAnimObj〕
    j__free(*(void **)(this + 120));  // 释放堆块
  *(uint32_t *)(this + 120) = 0;  // 写字段 this+120（pAnimObj） ← 0
  *(uint32_t *)(this + 124) = 0;  // 写字段 this+124（pAuraAnim） ← 0
  *(uint32_t *)(this + 128) = 0;  // 写字段 this+128（szStatusKeyBuf） ← 0
}



// ------------------------------------------------------------
// 0x45F1E0 sub_45F1E0 —— 对象注销/退场（递归，含 ELVEN_GATE 检查）
// ·vt+40(18) 先递归载体；类型 33 命中经 ·sub_48C990 存在性查找 + ·sub_48DA40 清地图阻挡；随后向 ·+8 表其余对象
// 广播 ·vt+300，并从 ·+8、所属分组(·+24+16n) 与 ·+120 表摘除、·vt+76(0) 解挂；
// ·+152 == 1 时扫 ·+120 查有无留守（·vt+376 同队或类型 33 且 +676 = 1），无人则复位并响 ·ELVEN_GATE（自证）。
// ------------------------------------------------------------
void /*userpurge*/ sub_45F1E0(int pArg1@<ecx>, int nArg2@<ebx>, uint32_t *pArg3)  // sub_45F1E0 —— 对象注销/退场（递归，含 ELVEN_GATE 检查）
{
  uint32_t *v5; // ebx
  int v6; // eax
  int *v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // ecx
  uint32_t *v12; // edx
  int v13; // eax
  uint32_t *v14; // ecx
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  uint32_t *v20; // edx
  int v21; // eax
  int v22; // ecx
  int v23; // eax
  uint32_t *v24; // edx
  int v25; // ebx
  int v26; // eax
  int v27; // ecx
  uint32_t *v28; // esi
  int v29; // [esp-8h] [ebp-14h]
  int v30; // [esp-4h] [ebp-10h]
  int v31; // [esp+8h] [ebp-4h]
  int i; // [esp+14h] [ebp+8h]
  int v33; // [esp+14h] [ebp+8h]

  if ( pArg3 != nullptr )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 40))(pArg3, 18) != 0 )  // 虚调用 vt+40（pArg3）条件查询(273等)
      sub_45F1E0(pArg3[162]);  // sub_45F1E0 —— 对象注销/退场（递归，含 ELVEN_GATE 检查）
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int))(*pArg3 + 40))(pArg3, 33, nArg2) != 0 )  // 虚调用 vt+40（pArg3）条件查询(273等)
    {
      v5 = *(uint32_t **)(*(uint32_t *)(pArg1 + 132) + 44);  // pArg1+132〔nAgeTicks〕
      v30 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 52))(pArg3);  // 虚调用 vt+52（pArg3）归属坐标y
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 48))(pArg3);  // 虚调用 vt+48（pArg3）归属坐标x
      if ( sub_48C990(v5, v6, v30) != 0 )  // sub_48C990 —— 键对存在性查找（this+123 表）
      {
        v7 = *(int **)(*(uint32_t *)(pArg1 + 132) + 44);  // pArg1+132〔nAgeTicks〕
        v29 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 52))(pArg3);  // 虚调用 vt+52（pArg3）归属坐标y
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 48))(pArg3);  // 虚调用 vt+48（pArg3）归属坐标x
        sub_48DA40(v7, v8, v29, 1);  // sub_48DA40 —— 地图阻挡掩码刷新（快照 → 活缓冲，再叠记录矩形）
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*pArg3 + 300))(pArg3, pArg3);  // 虚调用 vt+300（pArg3 虚表槽）
    v9 = *(uint32_t *)(pArg1 + 8);  // 读字段 v9 = pArg1+8（nSkillRec8）
    if ( v9 != 0 )
      v10 = (*(uint32_t *)(pArg1 + 12) - v9) >> 2;  // pArg1+12〔nSkillRec12(推断)〕
    else
      v10 = 0;
    v11 = 0;
    for ( i = 0; v11 < v10; i = v11 )
    {
      v12 = *(uint32_t **)(*(uint32_t *)(pArg1 + 8) + 4 * v11);  // pArg1+8〔nSkillRec8(推断)〕
      if ( v12 != pArg3 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v12 + 300))(v12, pArg3);  // 虚调用 vt+300（v12 虚表槽）
        v11 = i;
      }
      ++v11;  // 计数自增 v11
    }
    v13 = 0;
    if ( v10 > 0 )
    {
      v14 = *(uint32_t **)(pArg1 + 8);  // pArg1+8〔nSkillRec8(推断)〕
      while ( (uint32_t *)*v14 != pArg3 )  // 循环直到 v14 != pArg3
      {
        ++v13;  // 计数自增 v13
        ++v14;  // 计数自增 v14
        if ( v13 >= v10 )
          goto LABEL_20;
      }
      memcpy_0(
        (void *)(*(uint32_t *)(pArg1 + 8) + 4 * v13),
        (const void *)(*(uint32_t *)(pArg1 + 8) + 4 * v13 + 4),
        4 * ((*(uint32_t *)(pArg1 + 12) - (*(uint32_t *)(pArg1 + 8) + 4 * v13 + 4)) >> 2));  // pArg1+12〔nSkillRec12(推断)〕
      *(uint32_t *)(pArg1 + 12) -= 4;  // 字段 pArg1+12（nSkillRec12） -= 4
    }
LABEL_20:
    v15 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 36))(pArg3) + 8);  // 虚调用 vt+36（pArg3 虚表槽）
    if ( v15 != 6 )
    {
      v16 = 16 * v15 + pArg1;
      v17 = *(uint32_t *)(v16 + 24);  // 读字段 v17 = v16+24（nPageMax）
      v18 = v17 != 0 ? (*(uint32_t *)(v16 + 28) - v17) >> 2 : 0;
      v19 = 0;
      if ( v18 > 0 )
      {
        v20 = *(uint32_t **)(v16 + 24);
        while ( (uint32_t *)*v20 != pArg3 )  // 循环直到 v20 != pArg3
        {
          ++v19;  // 计数自增 v19
          ++v20;  // 计数自增 v20
          if ( v19 >= v18 )
            goto LABEL_30;
        }
        memcpy_0(
          (void *)(*(uint32_t *)(v16 + 24) + 4 * v19),
          (const void *)(*(uint32_t *)(v16 + 24) + 4 * v19 + 4),
          4 * ((*(uint32_t *)(v16 + 28) - (*(uint32_t *)(v16 + 24) + 4 * v19 + 4)) >> 2));
        *(uint32_t *)(v16 + 28) -= 4;  // 字段 v16+28（pPanelVec） -= 4
      }
    }
LABEL_30:
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 40))(pArg3, 1) != 0  // 虚调用 vt+40（pArg3）条件查询(273等)
      && (*(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 36))(pArg3) + 8) == 1  // 虚调用 vt+36（pArg3 虚表槽）
       || *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 36))(pArg3) + 8) == 2) )  // 虚调用 vt+36（pArg3 虚表槽）
    {
      v21 = *(uint32_t *)(pArg1 + 120);  // 读字段 v21 = pArg1+120（pAnimObj）
      v22 = v21 != 0 ? (*(uint32_t *)(pArg1 + 124) - v21) >> 2 : 0;  // pArg1+124〔pAuraAnim(推断)〕
      v23 = 0;
      if ( v22 > 0 )
      {
        v24 = *(uint32_t **)(pArg1 + 120);  // pArg1+120〔pAnimObj〕
        while ( (uint32_t *)*v24 != pArg3 )  // 循环直到 v24 != pArg3
        {
          ++v23;  // 计数自增 v23
          ++v24;  // 计数自增 v24
          if ( v23 >= v22 )
            goto LABEL_42;
        }
        memcpy_0(
          (void *)(*(uint32_t *)(pArg1 + 120) + 4 * v23),
          (const void *)(*(uint32_t *)(pArg1 + 120) + 4 * v23 + 4),
          4 * ((*(uint32_t *)(pArg1 + 124) - (*(uint32_t *)(pArg1 + 120) + 4 * v23 + 4)) >> 2));  // pArg1+124〔pAuraAnim(推断)〕
        *(uint32_t *)(pArg1 + 124) -= 4;  // 字段 pArg1+124（pAuraAnim） -= 4
      }
    }
LABEL_42:
    v25 = 0;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg3 + 76))(pArg3, 0);  // 虚调用 vt+76（pArg3 虚表槽）
    if ( *(uint8_t *)(pArg1 + 152) == 1  // pArg1+152〔nAdd152(推断)〕
      && dword_8F7C04 != 0  // 本地玩家对象
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 40))(pArg3, 1) != 0 )  // 虚调用 vt+40（pArg3）条件查询(273等)
    {
      v26 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);  // 虚调用 vt+376（dword_8F7C04 虚表槽）
      v27 = *(uint32_t *)(pArg1 + 120);  // 读字段 v27 = pArg1+120（pAnimObj）
      v31 = v26;
      if ( v27 != 0 )
        v33 = (*(uint32_t *)(pArg1 + 124) - v27) >> 2;  // pArg1+124〔pAuraAnim(推断)〕
      else
        v33 = 0;
      if ( v33 > 0 )
      {
        do
        {
          v28 = *(uint32_t **)(*(uint32_t *)(pArg1 + 120) + 4 * v25);  // pArg1+120〔pAnimObj〕
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v28 + 40))(v28, 17) != 0 )  // 虚调用 vt+40（v28）条件查询(273等)
          {
            if ( (*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 376))(v28) != v31 )  // 虚调用 vt+376（v28 虚表槽）
              break;
          }
          else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v28 + 40))(v28, 33) != 0 && v28[169] == 1 )  // 虚调用 vt+40（v28）条件查询(273等)
          {
            break;
          }
          ++v25;  // 计数自增 v25
        }
        while ( v25 < v33 );  // 循环直到 v25 < v33
      }
      if ( v25 == v33 )
      {
        off_77F3FC((char *)&byte_6C7448);  // off_77F3FC —— 日志打印（printf 风格）
        *(uint8_t *)(pArg1 + 152) = 0;  // 写字段 pArg1+152（nAdd152） ← 0
        sub_432EA0("ELVEN_GATE", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
          sub_47BE30(**(uint32_t **)(*(uint32_t *)(pArg1 + 132) + 44));  // pArg1+132〔nAgeTicks〕
      }
    }
  }
}


// ------------------------------------------------------------
// 0x45F4D0 sub_45F4D0 —— 按类型批量注销
// ·+8 表中 ·vt+40 == nArg2 者逐个走 ·sub_45F1E0 并前移下标。
// ------------------------------------------------------------
void /*thiscall*/ sub_45F4D0(uint32_t *this, int nArg2)  // sub_45F4D0 —— 按类型批量注销
{
  int pVecCap_5; // ecx
  int v4; // ebx
  int fld_e22; // ecx
  int fld_e3; // [esp+8h] [ebp-4h]

  pVecCap_5 = *(this + 2);  // 读字段 fld_e2 = this+2
  v4 = 0;
  if ( pVecCap_5 != 0 )  // fld_e2=this+8 物品 id
    fld_e3 = (*(this + 3) - pVecCap_5) >> 2;  // this+12〔nSkillRec12(推断)〕
  else
    fld_e3 = 0;  // fld_e3=this+12 nSkillRec12
  if ( fld_e3 > 0 )  // fld_e3=this+12 nSkillRec12
  {
    do
    {
      fld_e22 = *(uint32_t *)(4 * v4 + *(this + 2));  // this+8〔nSkillRec8(推断)〕
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e22 + 40))(fld_e22, nArg2) != 0 )  // 虚调用 vt+40（fld_e22）条件查询(273等)
      {
        sub_45F1E0((int)this, v4, *(uint32_t **)(*(this + 2) + 4 * v4));  // sub_45F1E0 —— 对象注销/退场（递归，含 ELVEN_GATE 检查）
        --v4;  // 计数自减 v4
        --fld_e3;  // 计数自减 fld_e3
      }
      ++v4;  // 计数自增 v4
    }
    while ( v4 < fld_e3 );  // 循环直到 v4 < fld_e3
  }
}



// ------------------------------------------------------------
// 0x45F550 sub_45F550 —— 清理失活对象
// ·vt+88 == 0 者按类型 273/18/65/129/130 仅注销(·sub_45F1E0)，其余注销后 vt[0](1) 自毁。
// ------------------------------------------------------------
int /*thiscall*/ sub_45F550(int *this)  // sub_45F550 —— 清理失活对象
{
  int result; // eax
  int v3; // ebx
  int v4; // edi
  int fld_e2; // ecx
  uint32_t *fld_e22; // edi
  int fld_e3; // [esp+8h] [ebp-4h]

  result = *(this + 2);  // 读字段 result = this+2
  v3 = 0;
  if ( result != 0 )  // result=this+8 物品 id
    fld_e3 = (*(this + 3) - result) >> 2;  // this+12〔nSkillRec12(推断)〕
  else
    fld_e3 = 0;  // fld_e3=this+12 nSkillRec12
  if ( fld_e3 > 0 )  // fld_e3=this+12 nSkillRec12
  {
    do
    {
      v4 = 4 * v3;  // 计算 v4 = 4 * v3
      fld_e2 = *(uint32_t *)(4 * v3 + *(this + 2));  // this+8〔nSkillRec8(推断)〕
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2 + 88))(fld_e2) == 0 )  // 虚调用 vt+88（pVecCap_4 虚表槽）
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(this + 2)) + 40))(  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
               *(uint32_t *)(v4 + *(this + 2)),  // this+8 = 技能槽记录首字
               273) != 0
          || (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(this + 2)) + 40))(  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
               *(uint32_t *)(v4 + *(this + 2)),  // this+8 = 技能槽记录首字
               18) != 0
          || (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(this + 2)) + 40))(  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
               *(uint32_t *)(v4 + *(this + 2)),  // this+8 = 技能槽记录首字
               65) != 0
          || (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(this + 2)) + 40))(  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
               *(uint32_t *)(v4 + *(this + 2)),  // this+8 = 技能槽记录首字
               129) != 0
          || (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(this + 2)) + 40))(  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
               *(uint32_t *)(v4 + *(this + 2)),  // this+8 = 技能槽记录首字
               130) != 0 )
        {
          sub_45F1E0((int)this, v3, *(uint32_t **)(*(this + 2) + 4 * v3));  // sub_45F1E0 —— 对象注销/退场（递归，含 ELVEN_GATE 检查）
        }
        else
        {
          fld_e22 = *(uint32_t **)(v4 + *(this + 2));  // this+8〔nSkillRec8(推断)〕
          sub_45F1E0((int)this, v3, fld_e22);  // sub_45F1E0 —— 对象注销/退场（递归，含 ELVEN_GATE 检查）
          if ( fld_e22 != nullptr )  // fld_e22=this+8 nSkillRec8
            (*(void (/*thiscall*/ **)(uint32_t *, int))*fld_e22)(fld_e22, 1);  // fld_e22=this+8 nSkillRec8
        }
        --v3;  // 计数自减 v3
        --fld_e3;  // 计数自减 fld_e3
      }
      result = fld_e3;  // result=this+8 物品 id
      ++v3;  // 计数自增 v3
    }
    while ( v3 < fld_e3 );  // 循环直到 v3 < fld_e3
  }
  return result;  // result=this+8 物品 id
}



// ------------------------------------------------------------
// 0x45F660 sub_45F660 —— 向量按值删除（·+140..）
// 命中 nArg2 后 memmove 前移，end -= 4。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45F660(uint32_t *this, int nArg2)  // sub_45F660 —— 向量按值删除（·+140..）
{
  uint32_t *fld_e36; // ecx
  uint32_t *result; // eax

  fld_e36 = (uint32_t *)*(this + 36);  // this+144〔pFrameList144(推断)〕
  result = (uint32_t *)*(this + 35);  // this+140〔nAdd140(推断)〕
  if ( result != fld_e36 )  // result=this+140 nAdd140
  {
    do
    {
      if ( *result == nArg2 )  // result=this+140 nAdd140
        break;
      ++result;  // 计数自增 result
    }
    while ( result != fld_e36 );  // 循环直到 result != fld_e36
    if ( result != fld_e36 )  // result=this+140 nAdd140
    {
      memcpy_0(result, result + 1, 4 * ((*(this + 36) - (int)(result + 1)) >> 2));  // this+144〔pFrameList144(推断)〕
      result = (uint32_t *)(*(this + 36) - 4);  // this+144〔pFrameList144(推断)〕
      *(this + 36) = result;  // 写字段 this+36（nStateWord36） ← result
    }
  }
  return result;  // result=this+144 pFrameList144
}



// ------------------------------------------------------------
// 0x45F6C0 sub_45F6C0 —— 对象管理器帧更新
// 逐对象 ·vt+28 → ·sub_45F550 清场 → ·sub_45EC70 两两通知 → ·sub_45EDB0 位置同步。
// ------------------------------------------------------------
DWORD /*thiscall*/ sub_45F6C0(int *this)  // sub_45F6C0 —— 对象管理器帧更新
{
  unsigned int i; // edi
  int pVecCap_7; // ecx

  for ( i = 0; ; ++i )
  {
    pVecCap_7 = *(this + 2);  // 读字段 fld_e2 = this+2
    if ( pVecCap_7 == 0 || i >= (*(this + 3) - pVecCap_7) >> 2 )  // fld_e2=this+8 物品 id
      break;
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pVecCap_7 + 4 * i) + 28))(*(uint32_t *)(pVecCap_7 + 4 * i));  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/Ani…
  }
  sub_45F550(this);  // sub_45F550 —— 清理失活对象
  sub_45EC70(this);  // sub_45EC70 —— 两两通知（·+120 表 O(n^2)）
  return sub_45EDB0(this);  // sub_45EDB0 —— 位置同步节流（每 1000ms）
}



// ------------------------------------------------------------
// 0x45F700 sub_45F700 —— vector<uint32> reserve
// n 超现有容量则按 n 重分配搬移（·sub_497E70）并释放旧缓冲；上限 0x3FFFFFFF 抛 vector<T> too long。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_45F700(int this, unsigned int uArg2)  // sub_45F700 —— vector<uint32> reserve
{
  int pVecEnd_5; // ecx
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
    sub_427E20(this);  // sub_427E20 —— STL 内联 vector<T> too long
  pVecEnd_5 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  fld_82 = 0;
  if ( pVecEnd_5 != 0 )  // fld_4=this+4 pHostObj
    result = (*(uint32_t *)(this + 12) - pVecEnd_5) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    result = 0;  // result=this+12 nSkillRec12
  if ( result < uArg2 )  // result=this+12 nSkillRec12
  {
    v14 = 4 * uArg2;  // 计算 v14 = 4 * uArg2
    pMem = (char *)operator new(v14);  // 堆分配
    fld_8 = *(uint32_t *)(this + 8);  // 读字段 fld_8 = this+8（nSkillRec8）
    fld_42 = *(uint32_t *)(this + 4);  // 读字段 fld_42 = this+4（pHostObj）
    Block = pMem;
    v13 = 0;
    sub_497E70(fld_42, fld_8, pMem);  // sub_497E70 —— uint32 区间逐元素拷贝
    fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
    if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
    {
      fld_82 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      j__free(*(void **)(this + 4));  // 释放堆块
    }
    *(uint32_t *)(this + 12) = &pMem[v14];  // 写字段 this+12（nSkillRec12） ← &pMem[v14]
    *(uint32_t *)(this + 8) = &pMem[4 * fld_82];  // 写字段 this+8（nSkillRec8） ← &pMem[4 * fld_82]
    *(uint32_t *)(this + 4) = pMem;  // 写字段 this+4（pHostObj） ← pMem
    return (unsigned int)&pMem[v14];
  }
  return result;  // result=this+12 nSkillRec12
}



// ------------------------------------------------------------
// 0x45F7D0 sub_45F7D0 —— 对象指针表扩容分配（内联 vector 分配路径）
// uArg2 超 0x3FFFFFFF 走 CRT 桩 ·sub_42CB90（vector too long）；this 为 44 字节段对象，
// +4 起四字段为数据段三指针族。由 ·sub_45F8A0/·sub_45FA80 家族调用
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_45F7D0(int this, unsigned int uArg2)  // sub_45F7D0 —— 对象指针表扩容分配（内联 vector 分配路径）
{
  int pVecEnd_5; // ecx
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
    sub_42CB90(this);  // sub_42CB90 —— CRT 桩（vector 长度异常）
  pVecEnd_5 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  fld_82 = 0;
  if ( pVecEnd_5 != 0 )  // fld_4=this+4 pHostObj
    result = (*(uint32_t *)(this + 12) - pVecEnd_5) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    result = 0;  // result=this+12 nSkillRec12
  if ( result < uArg2 )  // result=this+12 nSkillRec12
  {
    v14 = 4 * uArg2;  // 计算 v14 = 4 * uArg2
    pMem = (char *)operator new(v14);  // 堆分配
    fld_8 = *(uint32_t *)(this + 8);  // 读字段 fld_8 = this+8（nSkillRec8）
    fld_42 = *(uint32_t *)(this + 4);  // 读字段 fld_42 = this+4（pHostObj）
    Block = pMem;
    v13 = 0;
    sub_497E70(fld_42, fld_8, pMem);  // sub_497E70 —— uint32 区间逐元素拷贝
    fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
    if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
    {
      fld_82 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      j__free(*(void **)(this + 4));  // 释放堆块
    }
    *(uint32_t *)(this + 12) = &pMem[v14];  // 写字段 this+12（nSkillRec12） ← &pMem[v14]
    *(uint32_t *)(this + 8) = &pMem[4 * fld_82];  // 写字段 this+8（nSkillRec8） ← &pMem[4 * fld_82]
    *(uint32_t *)(this + 4) = pMem;  // 写字段 this+4（pHostObj） ← pMem
    return (unsigned int)&pMem[v14];
  }
  return result;  // result=this+12 nSkillRec12
}



// ------------------------------------------------------------
// 0x45F8A0 sub_45F8A0 —— 对象指针表插入（内联 vector insert_n：搬移/填值/扩容三路）
// 与 ·sub_5DAF70（内联 vector 插入搬移）/·sub_49A9D0（区间填充同值）同族；
// ·sub_55E7F0 为商城状态查询；超 0x3FFFFFFF 走 ·sub_42CB90 抛 vector too long
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_45F8A0(int this, int Src, unsigned int uArg3, int *pDwArg4)  // sub_45F8A0 —— 对象指针表插入（内联 vector insert_n：搬移/填值/扩容三路）
{
  int pVecEnd_17; // edx
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

  pVecEnd_17 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  pDwArg4 = (int *)*pDwArg4;
  if ( pVecEnd_17 != 0 )  // fld_4=this+4 pHostObj
    result = (*(uint32_t *)(this + 12) - pVecEnd_17) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    result = 0;  // result=this+12 nSkillRec12
  if ( uArg3 != 0 )
  {
    if ( pVecEnd_17 != 0 )  // fld_4=this+4 pHostObj
      fld_8 = (*(uint32_t *)(this + 8) - pVecEnd_17) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_8 = 0;  // fld_8=this+8 nSkillRec8
    if ( 0x3FFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 nSkillRec8
      sub_42CB90(this);  // sub_42CB90 —— CRT 桩（vector 长度异常）
    if ( pVecEnd_17 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - pVecEnd_17) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_82 = 0;  // fld_82=this+8 nSkillRec8
    if ( result >= uArg3 + fld_82 )  // result=this+12 nSkillRec12
    {
      fld_83 = *(uint8_t **)(this + 8);  // this+32〔nHeight(推断)〕
      v21 = (int)&fld_83[-Src] >> 2;  // fld_83=this+32 nHeight
      v22 = 4 * uArg3;  // 计算 v22 = 4 * uArg3
      v29 = (int)fld_83;  // fld_83=this+32 nHeight
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];  // fld_83=this+32 nHeight
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // sub_55E7F0 —— 商城状态（10 行）
        sub_5DAF70((void *)Src, v24, v29);  // sub_5DAF70 —— 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推得，尾段整体后移一格
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);  // sub_49A9D0 —— 区间填充（逐 uint32 写同值）
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));  // sub_55E7F0 —— 商城状态（10 行）
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);  // sub_523700 —— 填充补足尾段
        fld_84 = &Srca[*(uint32_t *)(this + 8)];  // this+8〔nSkillRec8(推断)〕等 2 字段
        *(uint32_t *)(this + 8) = fld_84;  // 写字段 this+8（nSkillRec8） ← fld_84
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);  // sub_49A9D0 —— 区间填充（逐 uint32 写同值）
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )  // result=this+12 nSkillRec12
        v10 = (result >> 1) + result;  // result=this+12 nSkillRec12
      else
        v10 = 0;
      if ( pVecEnd_17 != 0 )  // fld_4=this+4 pHostObj
        fld_85 = (*(uint32_t *)(this + 8) - pVecEnd_17) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_85 = 0;  // fld_85=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_85 )  // fld_85=this+8 nSkillRec8
      {
        if ( pVecEnd_17 != 0 )  // fld_4=this+4 pHostObj
          fld_86 = (*(uint32_t *)(this + 8) - pVecEnd_17) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else
          fld_86 = 0;  // fld_86=this+8 nSkillRec8
        v10 = uArg3 + fld_86;  // 计算 v10 = uArg3 + fld_86
      }
      v28 = 4 * v10;  // 计算 v28 = 4 * v10
      pMem = (char *)operator new(4 * v10);  // 堆分配
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);  // this+16〔nChannelTypeSel(推断)〕
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);  // sub_523700 —— 填充补足尾段
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));  // this+8〔nSkillRec8(推断)〕等 2 字段
      fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_87 = 0;  // fld_87=this+8 nSkillRec8
      v18 = fld_87 + uArg3;  // 计算 v18 = fld_87 + uArg3
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        j__free(*(void **)(this + 4));  // 释放堆块
      *(uint32_t *)(this + 12) = &pMem[v28];  // 写字段 this+12（nSkillRec12） ← &pMem[v28]
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // 写字段 this+8（nSkillRec8） ← &pMem[4 * v18]
      *(uint32_t *)(this + 4) = pMem;  // 写字段 this+4（pHostObj） ← pMem
      return (unsigned int)pMem;
    }
  }
  return result;  // result=this+12 nSkillRec12
}



// ------------------------------------------------------------
// 0x45FA80 sub_45FA80 —— 对象表重置与批量装载（GetTickCount 时间戳 + 逐表 reserve/填）
// 记 GetTickCount 到 +39 槽、nArg2 写首字段；对 this+1/+5 两子表各走 ·sub_45F700 reserve
// 与 ·sub_45F7D0 分配，末尾经 ·sub_45FA80 家族填数据
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_45FA80(uint32_t *this, int nArg2)  // sub_45FA80 —— 对象表重置与批量装载（GetTickCount 时间戳 + 逐表 reserve/填）
{
  int pThis_1; // ecx
  int v4; // esi
  int pThis_52; // edi
  unsigned int result; // eax
  int v7; // esi
  int pThis_5; // edi

  *(this + 39) = GetTickCount();  // 写字段 this+39 ← GetTickCount()
  *this = nArg2;
  pThis_1 = (int)(this + 1);  // this+4〔宿主对象〕
  if ( nArg2 != 0 )
  {
    sub_45F7D0(pThis_1, 0x64u);  // sub_45F7D0 —— 对象指针表扩容分配（内联 vector 分配路径）
    v7 = 0;
    pThis_5 = (int)(this + 5);  // this+20〔nPage(推断)〕
    do
    {
      result = sub_45F7D0(pThis_5, v7++ != 1 ? 5 : 100);  // sub_45F7D0 —— 对象指针表扩容分配（内联 vector 分配路径）
      pThis_5 += 16;  // pThis_5=this+20 nPage
    }
    while ( v7 < 6 );  // 循环直到 v7 < 6
  }
  else
  {
    sub_45F7D0(pThis_1, 0xC8u);  // sub_45F7D0 —— 对象指针表扩容分配（内联 vector 分配路径）
    v4 = 0;
    pThis_52 = (int)(this + 5);  // this+20〔nPage(推断)〕
    do
    {
      sub_45F7D0(pThis_52, v4++ != 1 ? 30 : 100);  // sub_45F7D0 —— 对象指针表扩容分配（内联 vector 分配路径）
      pThis_52 += 16;  // pThis_52=this+20 nPage
    }
    while ( v4 < 6 );  // 循环直到 v4 < 6
    return sub_45F700((int)(this + 29), 0x64u);  // sub_45F700 —— vector<uint32> reserve
  }
  return result;
}



// ============================================================
// 【分区 13】NPC 与对象注册（0x45FB20-0x460000）
// CNRDNpc__vmt0/vmt154（RTTI 自证）；0x45FE80 = 对象注册
// （分发器 case 0x15/0x16 与 ui_icon_perf 0x4600B0 的注册链入口）。
// ============================================================
// ------------------------------------------------------------
// 0x45FB20 sub_45FB20 —— 对象表插入包装（转 ·sub_45F8A0 后回传尾址）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45FB20(uint32_t *this, uint32_t *uArg2, void *Src, int *pDwArg4)  // sub_45FB20 —— 对象表插入包装（转 ·sub_45F8A0 后回传尾址）
{
  int pVecEnd_7; // ecx
  int v6; // esi

  pVecEnd_7 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( pVecEnd_7 != 0 && (*(this + 2) - pVecEnd_7) >> 2 != 0 )  // fld_e1=this+4 宿主对象
    v6 = ((int)Src - pVecEnd_7) >> 2;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_45F8A0((int)this, (int)Src, 1u, pDwArg4);  // sub_45F8A0 —— 对象指针表插入（内联 vector insert_n：搬移/填值/扩容三路）
  *uArg2 = *(this + 1) + 4 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x45FB80 CNRDNpc__vmt154 —— NPC 交互入口槽（转频道选择主入口）
// 取 this+71 槽对象转 ·sub_56CFE0（频道选择主入口，191 行；0x56 区）
// ------------------------------------------------------------
int /*thiscall*/ CNRDNpc__vmt154(uint32_t *this)  // 实现：NPC 交互入口槽（转频道选择主入口）
{
  return sub_56CFE0(*(this + 71));  // 频道选择主入口（191 行：56AEE0/56C1F0/56C320/442D00/56BFA0/56BDF0/4FE770/4014D0/423340/4…
}



// ------------------------------------------------------------
// 0x45FB90 CNRDNpc__vmt0
// ------------------------------------------------------------
// CNRDNpc::vmt0 —— NPC 对象构造（RTTI 自证）
void */*thiscall*/ CNRDNpc__vmt0(void *Block, char pszArg2)  // 实现：CNRDNpc::vmt0 —— NPC 对象构造（RTTI 自证）
{
  sub_45FBC0();  // sub_45FBC0 —— 析构转发槽（转 CNRDObject 析构主体）
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x45FBC0 sub_45FBC0 —— 析构转发槽（转 CNRDObject 析构主体）
// ------------------------------------------------------------
int /*thiscall*/ sub_45FBC0(void **this)  // sub_45FBC0 —— 析构转发槽（转 CNRDObject 析构主体）
{
  *this = &vftbl_CNRDNpc;  // 装虚表/取地址：← vftbl_CNRDNpc
  nullsub_3();  // 空桩函数（无操作）
  return sub_42A450(this);  // sub_42A450 —— CNRDObject 析构主体
}



// ------------------------------------------------------------
// 0x45FC10 sub_45FC10 —— 单对象插入包装（转 ·sub_45F8A0 后回传槽址）
// 与 ·sub_45FB20 同族（差异：pDwArg2 直接作插入源）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_45FC10(int *this, int *pDwArg2)  // sub_45FC10 —— 单对象插入包装（转 ·sub_45F8A0 后回传槽址）
{
  int pVecEnd_8; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  pVecEnd_8 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( pVecEnd_8 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - pVecEnd_8) >> 2;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( pVecEnd_8 == 0 || fld_e2 >= (*(this + 3) - pVecEnd_8) >> 2 )  // fld_e1=this+4 宿主对象
    return sub_45F8A0((int)this, *(this + 2), 1u, pDwArg2);  // sub_45F8A0 —— 对象指针表插入（内联 vector insert_n：搬移/填值/扩容三路）
  fld_e22 = (int *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
  *fld_e22 = *pDwArg2;  // fld_e22=this+8 nSkillRec8
  result = (unsigned int)(fld_e22 + 1);  // fld_e22=this+8 nSkillRec8
  *(this + 2) = result;  // 写字段 this+2 ← result
  return result;
}



// ------------------------------------------------------------
// 0x45FC60 sub_45FC60 —— ★ 对象表按类型过滤批量卸载（六类型码黑名单 + 两轮清理）
// 第一轮：遍历 this+8..+12 指针表，对每个对象调 vt+40(类型码) —— 命中
// 273/18/65/66/129/130 六种（对象类型 id，非玩家/怪物主类）者经 vt+76(0) 卸载，
// 并即时从表内摘除（memcpy 前移 + 表尾 -4）；未命中者才进入第二轮待清理链。
// 第二轮：对剩余对象走 ·sub_45F8A0 插入搬移（重建表/交接）。
// 【推断】六个类型码的官方名称（273=物品/18=NPC/65·66·129·130 待验证）
// ------------------------------------------------------------
void /*thiscall*/ sub_45FC60(int this)  // sub_45FC60 —— ★ 对象表按类型过滤批量卸载（六类型码黑名单 + 两轮清理）
{
  int *fld_8; // esi
  bool fld_C; // zf
  char *v4; // edi
  uint32_t *i; // edi
  uint32_t *Block2; // esi
  int pThis_18; // esi
  int j; // edi
  void *Block3; // ecx
  uint8_t v10[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *v12; // [esp+14h] [ebp-18h]
  int v13; // [esp+18h] [ebp-14h]
  void *Src; // [esp+1Ch] [ebp-10h]
  int v15; // [esp+28h] [ebp-4h]

  Block = nullptr;
  v12 = nullptr;
  v13 = 0;
  fld_8 = *(int **)(this + 8);  // this+32〔nHeight(推断)〕
  fld_C = fld_8 == *(int **)(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
  v15 = 0;
  if ( !fld_C )  // fld_C=this+48 pCmdVecBegin48
  {
    Src = fld_8 + 1;  // fld_8=this+32 nHeight
    do
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*fld_8 + 40))(*fld_8, 273) != 0  // 虚调用 vt+40（pVecCap_32）条件查询(273等)
        || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*fld_8 + 40))(*fld_8, 18) != 0  // 虚调用 vt+40（pVecCap_32）条件查询(273等)
        || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*fld_8 + 40))(*fld_8, 65) != 0  // 虚调用 vt+40（pVecCap_32）条件查询(273等)
        || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*fld_8 + 40))(*fld_8, 66) != 0  // 虚调用 vt+40（pVecCap_32）条件查询(273等)
        || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*fld_8 + 40))(*fld_8, 129) != 0  // 虚调用 vt+40（pVecCap_32）条件查询(273等)
        || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*fld_8 + 40))(*fld_8, 130) != 0 )  // 虚调用 vt+40（pVecCap_32）条件查询(273等)
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)*fld_8 + 76))(*fld_8, 0);  // 虚调用 vt+76（pVecCap_32 虚表槽）
        v4 = (char *)v12;
        if ( Block != nullptr && ((uint8_t *)v12 - (uint8_t *)Block) >> 2 < (unsigned int)((v13 - (int)Block) >> 2) )
        {
          *(uint32_t *)v12 = *fld_8;  // fld_8=this+32 nHeight
          v12 = v4 + 4;  // 计算 v12 = v4 + 4
        }
        else
        {
          sub_45F8A0((int)v10, (int)v12, 1u, fld_8);  // sub_45F8A0 —— 对象指针表插入（内联 vector insert_n：搬移/填值/扩容三路）
        }
        memcpy_0(fld_8, Src, 4 * ((*(uint32_t *)(this + 12) - (int)Src) >> 2));  // this+12〔nSkillRec12(推断)〕等 2 字段
        *(uint32_t *)(this + 12) -= 4;  // 字段 this+12（nSkillRec12） -= 4
      }
      else
      {
        ++fld_8;  // 计数自增 fld_8
        Src = (char *)Src + 4;
      }
    }
    while ( fld_8 != *(int **)(this + 12) );  // this+48〔pCmdVecBegin48(推断)〕
  }
  for ( i = *(uint32_t **)(this + 8); i != *(uint32_t **)(this + 12); ++i )  // this+32〔nHeight(推断)〕等 2 字段
  {
    Block2 = Block;
    if ( Block != v12 )
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*Block2 + 300))(*Block2, *i);  // 虚调用 vt+300（Block2 虚表槽）
        ++Block2;  // 计数自增 Block2
      }
      while ( Block2 != v12 );  // 循环直到 Block2 != v12
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*i + 76))(*i, 0);  // 虚调用 vt+76（i 虚表槽）
    if ( *i != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*i)(*i, 1);
  }
  if ( *(uint32_t *)(this + 8) != 0 )  // this+8〔nSkillRec8(推断)〕等 2 字段
    j__free(*(void **)(this + 8));  // 释放堆块
  *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  *(uint32_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  *(uint32_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
  pThis_18 = this + 24;  // this+24 页数上限
  for ( j = 6; j != 0; --j )  // 遍历计次循环（j != 0）
  {
    if ( *(uint32_t *)pThis_18 != 0 )  // pThis_18=this+24 页数上限
      j__free(*(void **)pThis_18);  // 释放堆块
    *(uint32_t *)pThis_18 = 0;  // *pThis_18 = 0
    *(uint32_t *)(pThis_18 + 4) = 0;  // 写字段 pThis_18+4（pHostObj） ← 0
    *(uint32_t *)(pThis_18 + 8) = 0;  // 写字段 pThis_18+8（nSkillRec8） ← 0
    pThis_18 += 16;  // pThis_18=this+24 页数上限
  }
  if ( *(uint32_t *)(this + 120) != 0 )  // this+120〔pAnimObj〕
    j__free(*(void **)(this + 120));  // 释放堆块
  *(uint32_t *)(this + 120) = 0;  // 写字段 this+120（pAnimObj） ← 0
  *(uint32_t *)(this + 124) = 0;  // 写字段 this+124（pAuraAnim） ← 0
  *(uint32_t *)(this + 128) = 0;  // 写字段 this+128（szStatusKeyBuf） ← 0
  if ( *(uint32_t *)(this + 140) != 0 )  // this+140〔nAdd140(推断)〕
    j__free(*(void **)(this + 140));  // 释放堆块
  Block3 = Block;
  fld_C = Block == nullptr;  // fld_C=this+48 pCmdVecBegin48
  *(uint32_t *)(this + 140) = 0;  // 写字段 this+140（nAdd140） ← 0
  *(uint32_t *)(this + 144) = 0;  // 写字段 this+144（pFrameList144） ← 0
  *(uint32_t *)(this + 148) = 0;  // 写字段 this+148（fAdd148） ← 0
  *(uint8_t *)(this + 152) = 0;  // 写字段 this+152（nAdd152） ← 0
  *(uint8_t *)(this + 153) = 0;  // 写字段 this+153（bCastFlagA） ← 0
  if ( !fld_C )  // fld_C=this+48 pCmdVecBegin48
    j__free(Block3);  // 释放堆块
}



// ------------------------------------------------------------
// 0x45FE80 sub_45FE80
// ------------------------------------------------------------
// 对象注册（场景对象表插入）—— 分发器 case 0x15/0x16 与
// ui_icon_perf 0x4600B0 的注册链入口；参数 (容器, 源表, a2, a3, 对象, 0, 0)
void /*userpurge*/ sub_45FE80(int pArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7)  // sub_45FE80 —— 对象注册
{
  int pObj2; // esi
  int v9; // ecx
  int v10; // edi
  void *v11; // ebx
  int v12; // eax
  int v13; // ebx
  int i; // edi
  int pObj; // ecx
  int pArg122; // ebx
  int v17; // edi
  int v18; // [esp+8h] [ebp-Ch]
  void *Src; // [esp+Ch] [ebp-8h] BYREF
  int pArg12; // [esp+10h] [ebp-4h]

  pObj2 = nArg5;
  pArg12 = pArg1;
  if ( nArg5 != 0 && (uint8_t)sub_45E680(nArg5) == 0 )  // sub_45E680 —— 对象表归属判定
  {
    *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 36))(pObj2) = nArg3;  // 虚调用 vt+36（pObj2 虚表槽）
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 36))(pObj2) + 4) = nArg4;  // 虚调用 vt+36（pObj2 虚表槽）
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 80))(pObj2) != 0 )  // 虚调用 vt+80（pObj2）读 4 字节
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 80))(pObj2);  // 虚调用 vt+80（pObj2）读 4 字节
      sub_45F1E0(pObj2);  // sub_45F1E0 —— 对象注销/退场（递归，含 ELVEN_GATE 检查）
    }
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj2 + 76))(pObj2, pArg1, nArg2);  // 虚调用 vt+76（pObj2 虚表槽）
    v18 = pArg1 + 4;  // 计算 v18 = pArg1 + 4
    sub_45FC10(&nArg5);  // sub_45FC10 —— 单对象插入包装（转 ·sub_45F8A0 后回传槽址）
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 36))(pObj2) + 8) != 6 )  // 虚调用 vt+36（pObj2 虚表槽）
    {
      v9 = 16 * *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 36))(pObj2) + 8);  // 虚调用 vt+36（pObj2 虚表槽）
      v10 = v9 + pArg1 + 20;
      if ( nArg6 != 0 )
      {
        v11 = *(void **)(v9 + pArg1 + 28);
        sub_45E5A0(&Src, *(uint32_t *)(v10 + 4), v11, &nArg6);  // sub_45E5A0 —— uint32 区间线性查找
        if ( Src == v11 )
        {
          sub_45FC10(&nArg5);  // sub_45FC10 —— 单对象插入包装（转 ·sub_45F8A0 后回传槽址）
        }
        else if ( (uint8_t)nArg7 != 0 )
        {
          sub_45FB20((int)&nArg7, Src, (int)&nArg5);  // sub_45FB20 —— 对象表插入包装（转 ·sub_45F8A0 后回传尾址）
        }
        else
        {
          sub_45FB20((int)&nArg7, (char *)Src + 4, (int)&nArg5);  // sub_45FB20 —— 对象表插入包装（转 ·sub_45F8A0 后回传尾址）
        }
      }
      else
      {
        sub_45FC10(&nArg5);  // sub_45FC10 —— 单对象插入包装（转 ·sub_45F8A0 后回传槽址）
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 1) != 0  // 虚调用 vt+40（pObj2）条件查询(273等)
      && (*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 36))(pObj2) + 8) == 1  // 虚调用 vt+36（pObj2 虚表槽）
       || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 36))(pObj2) + 8) == 2) )  // 虚调用 vt+36（pObj2 虚表槽）
    {
      nArg7 = pObj2;
      sub_428430(&nArg7);  // sub_428430 —— STL 内联 vector push_back（4B 元素）
    }
    if ( dword_8F7C04 != 0 && nArg3 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04) )  // 虚调用 vt+1220（dword_8F7C04 虚表槽）
      sub_45F660(nArg4);  // sub_45F660 —— 向量按值删除（·+140..）
    v12 = *(uint32_t *)(v18 + 4);  // 读字段 v12 = v18+4（pHostObj）
    if ( v12 != 0 )
      v13 = (*(uint32_t *)(v18 + 8) - v12) >> 2;
    else
      v13 = 0;
    for ( i = 0; i < v13; ++i )  // 遍历计次循环（i < v13）
    {
      pObj = *(uint32_t *)(*(uint32_t *)(pArg12 + 8) + 4 * i);  // pArg12+8〔nSkillRec8(推断)〕
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 296))(pObj, pObj2);  // 虚调用 vt+296（pObj 虚表槽）
    }
    pArg122 = pArg12;
    if ( *(uint8_t *)(pArg12 + 152) == 0  // pArg12+152〔nAdd152(推断)〕
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0  // 虚调用 vt+40（pObj2）条件查询(273等)
      && dword_8F7C04 != 0 )  // 本地玩家对象
    {
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);  // 虚调用 vt+376（dword_8F7C04 虚表槽）
      if ( v17 != (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2) )  // 虚调用 vt+376（pObj2 虚表槽）
        *(uint8_t *)(pArg122 + 152) = 1;  // 写字段 pArg122+152（nAdd152） ← 1
    }
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 12))(pObj2);  // 虚调用 vt+12（pObj2 虚表槽）
  }
}


