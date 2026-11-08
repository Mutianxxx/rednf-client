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
// 0x450130 sub_450130
// ------------------------------------------------------------
void /*thiscall*/ sub_450130(HGDIOBJ *this)
{
  *this = &vftbl_CNRDPVPInterface;
  sub_52A7B0();
  if ( *(this + 86) != nullptr )
  {
    DeleteObject(*(this + 86));
    *(this + 86) = nullptr;
  }
  *((uint8_t *)this + 300) = 0;
  *((uint8_t *)this + 301) = 0;
  *((uint8_t *)this + 302) = 0;
  *((uint8_t *)this + 303) = 0;
  *(this + 78) = nullptr;
  *(this + 79) = nullptr;
  *(this + 80) = nullptr;
  *(this + 81) = nullptr;
  *(this + 82) = nullptr;
  *(this + 83) = nullptr;
  *(this + 84) = nullptr;
  *(this + 85) = nullptr;
  *(this + 86) = nullptr;
  *(this + 87) = nullptr;
  if ( *(this + 73) != nullptr )
  {
    DeleteObject(*(this + 73));
    *(this + 73) = nullptr;
  }
  *((uint8_t *)this + 248) = 0;
  *((uint8_t *)this + 249) = 0;
  *((uint8_t *)this + 250) = 0;
  *((uint8_t *)this + 251) = 0;
  *(this + 65) = nullptr;
  *(this + 66) = nullptr;
  *(this + 67) = nullptr;
  *(this + 68) = nullptr;
  *(this + 69) = nullptr;
  *(this + 70) = nullptr;
  *(this + 71) = nullptr;
  *(this + 72) = nullptr;
  *(this + 73) = nullptr;
  *(this + 74) = nullptr;
  if ( *(this + 60) != nullptr )
  {
    DeleteObject(*(this + 60));
    *(this + 60) = nullptr;
  }
  *((uint8_t *)this + 196) = 0;
  *((uint8_t *)this + 197) = 0;
  *((uint8_t *)this + 198) = 0;
  *((uint8_t *)this + 199) = 0;
  *(this + 52) = nullptr;
  *(this + 53) = nullptr;
  *(this + 54) = nullptr;
  *(this + 55) = nullptr;
  *(this + 56) = nullptr;
  *(this + 57) = nullptr;
  *(this + 58) = nullptr;
  *(this + 59) = nullptr;
  *(this + 60) = nullptr;
  *(this + 61) = nullptr;
  if ( *(this + 47) != nullptr )
  {
    DeleteObject(*(this + 47));
    *(this + 47) = nullptr;
  }
  *((uint8_t *)this + 144) = 0;
  *((uint8_t *)this + 145) = 0;
  *((uint8_t *)this + 146) = 0;
  *((uint8_t *)this + 147) = 0;
  *(this + 39) = nullptr;
  *(this + 40) = nullptr;
  *(this + 41) = nullptr;
  *(this + 42) = nullptr;
  *(this + 43) = nullptr;
  *(this + 44) = nullptr;
  *(this + 45) = nullptr;
  *(this + 46) = nullptr;
  *(this + 47) = nullptr;
  *(this + 48) = nullptr;
  sub_44F730(this + 9);
  if ( *(this + 3) != nullptr )
    j__free(*(this + 3));
  *(this + 3) = nullptr;
  *(this + 4) = nullptr;
  *(this + 5) = nullptr;
}



// ------------------------------------------------------------
// 0x450340 sub_450340
// ------------------------------------------------------------
char */*thiscall*/ sub_450340(char *this, void *Block)
{
  *(uint32_t *)this = &vftbl_CNRDReward;
  *(this + 12) = 0;
  *((uint32_t *)this + 2) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 4) = 0;
  *(this + 20) = 1;
  *(this + 22) = 0;
  *(this + 21) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 6) = 0;
  *(this + 56) = 0;
  *(this + 57) = 0;
  *(this + 58) = 0;
  *(this + 59) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 6;
  *((uint32_t *)this + 19) = 12;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 21) = 1600;
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 24) = 0;
  *((uint32_t *)this + 25) = 0;
  *((uint32_t *)this + 26) = 0;
  *(this + 108) = 0;
  *(this + 109) = 0;
  *(this + 110) = 0;
  *(this + 111) = 0;
  *((uint32_t *)this + 30) = 0;
  *((uint32_t *)this + 31) = 6;
  *((uint32_t *)this + 32) = 12;
  *((uint32_t *)this + 33) = 0;
  *((uint32_t *)this + 34) = 1600;
  *((uint32_t *)this + 35) = 0;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 39) = 0;
  *(this + 168) = 0;
  *((uint32_t *)this + 41) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 43) = 0;
  *(this + 176) = 1;
  *(this + 178) = 0;
  *(this + 177) = 0;
  *((uint32_t *)this + 47) = 0;
  *((uint32_t *)this + 46) = 0;
  *((uint32_t *)this + 45) = 0;
  *((uint32_t *)this + 59) = 0;
  *((uint32_t *)this + 60) = 0;
  *((uint32_t *)this + 61) = 0;
  *((uint32_t *)this + 63) = 0;
  *((uint32_t *)this + 64) = 0;
  *((uint32_t *)this + 65) = 0;
  `eh vector constructor iterator'(this + 440, 0x10u, 4, sub_4019A0, sub_44CF40);
  *(this + 616) = 0;
  *((uint32_t *)this + 153) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 155) = 0;
  *(this + 624) = 1;
  *(this + 626) = 0;
  *(this + 625) = 0;
  *((uint32_t *)this + 159) = 0;
  *((uint32_t *)this + 158) = 0;
  *((uint32_t *)this + 157) = 0;
  sub_456F50(this);
  sub_45A8A0(Block);
  return this;
}



// ------------------------------------------------------------
// 0x4504F0 sub_4504F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4504F0(char *this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNRDReward;
  sub_456F80();
  *((uint32_t *)this + 153) = &vftbl_nengine__IObject;
  *(this + 616) = 0;
  `eh vector destructor iterator'(this + 440, 0x10u, 4, sub_44CF40);
  sub_55A050(this + 248);
  sub_55A050(this + 232);
  *((uint32_t *)this + 41) = &vftbl_nengine__IObject;
  *(this + 168) = 0;
  if ( *((uint32_t *)this + 38) != 0 )
  {
    DeleteObject(*((HGDIOBJ *)this + 38));
    *((uint32_t *)this + 38) = 0;
  }
  *(this + 108) = 0;
  *(this + 109) = 0;
  *(this + 110) = 0;
  *(this + 111) = 0;
  *((uint32_t *)this + 30) = 0;
  *((uint32_t *)this + 31) = 0;
  *((uint32_t *)this + 32) = 0;
  *((uint32_t *)this + 33) = 0;
  *((uint32_t *)this + 34) = 0;
  *((uint32_t *)this + 35) = 0;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 39) = 0;
  result = *((uint32_t *)this + 25);
  if ( result != 0 )
  {
    result = DeleteObject(*((HGDIOBJ *)this + 25));
    *((uint32_t *)this + 25) = 0;
  }
  *(this + 56) = 0;
  *(this + 57) = 0;
  *(this + 58) = 0;
  *(this + 59) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 24) = 0;
  *((uint32_t *)this + 25) = 0;
  *((uint32_t *)this + 26) = 0;
  *(this + 12) = 0;
  *((uint32_t *)this + 2) = &vftbl_nengine__IObject;
  return result;
}



// ------------------------------------------------------------
// 0x450620 sub_450620
// ------------------------------------------------------------
char */*thiscall*/ sub_450620(char *this, int a2)
{
  *(uint32_t *)this = &CNRDCashShop::`vftable';
  *(this + 20) = 0;
  *((uint32_t *)this + 4) = &off_6C2B88;
  *((uint32_t *)this + 6) = 0;
  *(this + 28) = 1;
  *(this + 30) = 0;
  *(this + 29) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 8) = 0;
  *(this + 64) = 0;
  *(this + 65) = 0;
  *(this + 66) = 0;
  *(this + 67) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 6;
  *((uint32_t *)this + 21) = 12;
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 23) = 1600;
  *((uint32_t *)this + 24) = 0;
  *((uint32_t *)this + 25) = 0;
  *((uint32_t *)this + 26) = 0;
  *((uint32_t *)this + 27) = 0;
  *((uint32_t *)this + 28) = 0;
  *(this + 116) = 0;
  *(this + 117) = 0;
  *(this + 118) = 0;
  *(this + 119) = 0;
  *((uint32_t *)this + 32) = 0;
  *((uint32_t *)this + 33) = 6;
  *((uint32_t *)this + 34) = 12;
  *((uint32_t *)this + 35) = 0;
  *((uint32_t *)this + 36) = 1600;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 39) = 0;
  *((uint32_t *)this + 40) = 0;
  *((uint32_t *)this + 41) = 0;
  *(this + 168) = 0;
  *(this + 169) = 0;
  *(this + 170) = 0;
  *(this + 171) = 0;
  *((uint32_t *)this + 45) = 0;
  *((uint32_t *)this + 46) = 6;
  *((uint32_t *)this + 47) = 12;
  *((uint32_t *)this + 48) = 0;
  *((uint32_t *)this + 49) = 1600;
  *((uint32_t *)this + 50) = 0;
  *((uint32_t *)this + 51) = 0;
  *((uint32_t *)this + 52) = 0;
  *((uint32_t *)this + 53) = 0;
  *((uint32_t *)this + 54) = 0;
  *(this + 220) = 0;
  *(this + 221) = 0;
  *(this + 222) = 0;
  *(this + 223) = 0;
  *((uint32_t *)this + 58) = 0;
  *((uint32_t *)this + 59) = 6;
  *((uint32_t *)this + 60) = 12;
  *((uint32_t *)this + 61) = 0;
  *((uint32_t *)this + 62) = 1600;
  *((uint32_t *)this + 63) = 0;
  *((uint32_t *)this + 64) = 0;
  *((uint32_t *)this + 65) = 0;
  *((uint32_t *)this + 66) = 0;
  *((uint32_t *)this + 67) = 0;
  *(this + 272) = 0;
  *(this + 273) = 0;
  *(this + 274) = 0;
  *(this + 275) = 0;
  *((uint32_t *)this + 71) = 0;
  *((uint32_t *)this + 72) = 6;
  *((uint32_t *)this + 73) = 12;
  *((uint32_t *)this + 74) = 0;
  *((uint32_t *)this + 75) = 1600;
  *((uint32_t *)this + 76) = 0;
  *((uint32_t *)this + 77) = 0;
  *((uint32_t *)this + 78) = 0;
  *((uint32_t *)this + 79) = 0;
  *((uint32_t *)this + 80) = 0;
  `eh vector constructor iterator'(this + 348, 0x20u, 4, sub_44CA10, sub_44C050);
  `eh vector constructor iterator'(this + 508, 0x10u, 4, sub_4019A0, sub_44FF50);
  `eh vector constructor iterator'(this + 604, 0x54u, 80, sub_44CF30, sub_44C2A0);
  *(this + 7504) = 0;
  *((uint32_t *)this + 1875) = &off_6C2B88;
  *((uint32_t *)this + 1877) = 0;
  *(this + 7512) = 1;
  *(this + 7514) = 0;
  *(this + 7513) = 0;
  *((uint32_t *)this + 1881) = 0;
  *((uint32_t *)this + 1880) = 0;
  *((uint32_t *)this + 1879) = 0;
  *(this + 7532) = 0;
  *((uint32_t *)this + 1882) = &off_6C2B88;
  *((uint32_t *)this + 1884) = 0;
  *(this + 7540) = 1;
  *(this + 7542) = 0;
  *(this + 7541) = 0;
  *((uint32_t *)this + 1888) = 0;
  *((uint32_t *)this + 1887) = 0;
  *((uint32_t *)this + 1886) = 0;
  *(this + 7560) = 0;
  *((uint32_t *)this + 1889) = &off_6C2B88;
  *((uint32_t *)this + 1891) = 0;
  *(this + 7568) = 1;
  *(this + 7570) = 0;
  *(this + 7569) = 0;
  *((uint32_t *)this + 1895) = 0;
  *((uint32_t *)this + 1894) = 0;
  *((uint32_t *)this + 1893) = 0;
  `eh vector constructor iterator'(this + 7848, 0x10u, 128, sub_4019A0, sub_5E5260);
  *((uint32_t *)this + 2499) = 0;
  *((uint32_t *)this + 2500) = 0;
  *((uint32_t *)this + 2501) = 0;
  *((uint32_t *)this + 2503) = 0;
  *((uint32_t *)this + 2504) = 0;
  *((uint32_t *)this + 2505) = 0;
  sub_44CEA0(this + 10024);
  *((uint32_t *)this + 1) = a2;
  sub_55C1A0(this);
  sub_560D10(this);
  return this;
}


// ------------------------------------------------------------
// 0x450970 sub_450970
// ------------------------------------------------------------
int /*thiscall*/ sub_450970(void **this)
{
  int result; // eax

  *this = &CNRDCashShop::`vftable';
  sub_55EDC0();
  sub_44C2A0(this + 2506);
  if ( *(this + 2503) != nullptr )
    j__free(*(this + 2503));
  *(this + 2503) = nullptr;
  *(this + 2504) = nullptr;
  *(this + 2505) = nullptr;
  if ( *(this + 2499) != nullptr )
    j__free(*(this + 2499));
  *(this + 2499) = nullptr;
  *(this + 2500) = nullptr;
  *(this + 2501) = nullptr;
  `eh vector destructor iterator'(this + 1962, 0x10u, 128, sub_5E5260);
  *(this + 1889) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 7560) = 0;
  *(this + 1882) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 7532) = 0;
  *(this + 1875) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 7504) = 0;
  `eh vector destructor iterator'(this + 151, 0x54u, 80, sub_44C2A0);
  `eh vector destructor iterator'(this + 127, 0x10u, 4, sub_44FF50);
  `eh vector destructor iterator'(this + 87, 0x20u, 4, sub_44C050);
  if ( *(this + 79) != nullptr )
  {
    DeleteObject(*(this + 79));
    *(this + 79) = nullptr;
  }
  *((uint8_t *)this + 272) = 0;
  *((uint8_t *)this + 273) = 0;
  *((uint8_t *)this + 274) = 0;
  *((uint8_t *)this + 275) = 0;
  *(this + 71) = nullptr;
  *(this + 72) = nullptr;
  *(this + 73) = nullptr;
  *(this + 74) = nullptr;
  *(this + 75) = nullptr;
  *(this + 76) = nullptr;
  *(this + 77) = nullptr;
  *(this + 78) = nullptr;
  *(this + 79) = nullptr;
  *(this + 80) = nullptr;
  if ( *(this + 66) != nullptr )
  {
    DeleteObject(*(this + 66));
    *(this + 66) = nullptr;
  }
  *((uint8_t *)this + 220) = 0;
  *((uint8_t *)this + 221) = 0;
  *((uint8_t *)this + 222) = 0;
  *((uint8_t *)this + 223) = 0;
  *(this + 58) = nullptr;
  *(this + 59) = nullptr;
  *(this + 60) = nullptr;
  *(this + 61) = nullptr;
  *(this + 62) = nullptr;
  *(this + 63) = nullptr;
  *(this + 64) = nullptr;
  *(this + 65) = nullptr;
  *(this + 66) = nullptr;
  *(this + 67) = nullptr;
  if ( *(this + 53) != nullptr )
  {
    DeleteObject(*(this + 53));
    *(this + 53) = nullptr;
  }
  *((uint8_t *)this + 168) = 0;
  *((uint8_t *)this + 169) = 0;
  *((uint8_t *)this + 170) = 0;
  *((uint8_t *)this + 171) = 0;
  *(this + 45) = nullptr;
  *(this + 46) = nullptr;
  *(this + 47) = nullptr;
  *(this + 48) = nullptr;
  *(this + 49) = nullptr;
  *(this + 50) = nullptr;
  *(this + 51) = nullptr;
  *(this + 52) = nullptr;
  *(this + 53) = nullptr;
  *(this + 54) = nullptr;
  if ( *(this + 40) != nullptr )
  {
    DeleteObject(*(this + 40));
    *(this + 40) = nullptr;
  }
  *((uint8_t *)this + 116) = 0;
  *((uint8_t *)this + 117) = 0;
  *((uint8_t *)this + 118) = 0;
  *((uint8_t *)this + 119) = 0;
  *(this + 32) = nullptr;
  *(this + 33) = nullptr;
  *(this + 34) = nullptr;
  *(this + 35) = nullptr;
  *(this + 36) = nullptr;
  *(this + 37) = nullptr;
  *(this + 38) = nullptr;
  *(this + 39) = nullptr;
  *(this + 40) = nullptr;
  *(this + 41) = nullptr;
  result = (int)*(this + 27);
  if ( result != 0 )
  {
    result = DeleteObject(*(this + 27));
    *(this + 27) = nullptr;
  }
  *((uint8_t *)this + 64) = 0;
  *((uint8_t *)this + 65) = 0;
  *((uint8_t *)this + 66) = 0;
  *((uint8_t *)this + 67) = 0;
  *(this + 19) = nullptr;
  *(this + 20) = nullptr;
  *(this + 21) = nullptr;
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *(this + 24) = nullptr;
  *(this + 25) = nullptr;
  *(this + 26) = nullptr;
  *(this + 27) = nullptr;
  *(this + 28) = nullptr;
  *((uint8_t *)this + 20) = 0;
  *(this + 4) = &nengine::IObject::`vftable';
  return result;
}


// ------------------------------------------------------------
// 0x450C80 sub_450C80
// ------------------------------------------------------------
int /*thiscall*/ sub_450C80(char *Block)
{
  uint32_t *v2; // edi
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  char *v5; // eax
  char *v6; // eax
  uint32_t *v7; // edi
  uint8_t *v8; // eax
  uint8_t *v9; // eax
  int v10; // eax
  uint32_t *v11; // eax
  uint32_t *v12; // eax
  int v13; // eax
  int v14; // eax
  uint8_t *v15; // eax
  uint8_t *v16; // eax
  uint8_t *v17; // eax
  uint8_t *v18; // edi
  int v19; // eax
  uint8_t *v20; // eax
  uint8_t *v21; // eax
  uint32_t *v22; // eax
  uint32_t *v23; // edi
  uint32_t *v24; // eax
  uint32_t *v25; // edi
  int v26; // eax
  int v27; // eax
  uint32_t *v28; // eax
  uint32_t *v29; // edi
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // eax
  uint32_t *v36; // eax
  uint32_t *v37; // edi
  uint32_t *v38; // eax
  uint32_t *v39; // edi
  uint32_t *v40; // eax
  uint32_t *v41; // edi
  uint8_t *v42; // eax
  uint8_t *v43; // eax
  uint8_t *v44; // eax
  uint8_t *v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // eax
  char *v49; // eax
  char *v50; // eax
  int v51; // eax
  char *v52; // eax
  char *v53; // eax
  uint32_t *v54; // eax
  uint32_t *v55; // edi
  uint32_t *v56; // eax
  uint32_t *v57; // edi
  uint8_t *v58; // eax
  uint8_t *v59; // eax
  uint32_t *v60; // eax
  uint32_t *v61; // edi
  uint8_t *v62; // eax
  uint8_t *v63; // eax
  uint32_t *v64; // edi
  uint8_t *v65; // eax
  uint8_t *v66; // edi
  uint8_t *v67; // eax
  uint32_t *v68; // edi
  int i; // [esp+10h] [ebp-10h]
  int j; // [esp+10h] [ebp-10h]

  v2 = Block + 8;
  for ( i = 2; i != 0; --i )
  {
    v3 = operator new(0x68u);
    if ( v3 != nullptr )
      v4 = sub_426BD0(v3);
    else
      v4 = nullptr;
    *v2++ = v4;
  }
  v5 = (char *)operator new(0x5B4u);
  if ( v5 != nullptr )
    v6 = sub_44D530(v5, Block);
  else
    v6 = nullptr;
  *((uint32_t *)Block + 4) = v6;
  sub_69A840(*((uint32_t *)v6 + 2));
  v7 = Block + 20;
  for ( j = 2; j != 0; --j )
  {
    v8 = operator new(0x68u);
    if ( v8 != nullptr )
      v9 = sub_426BD0(v8);
    else
      v9 = nullptr;
    *v7++ = v9;
  }
  sub_69A840(*((uint32_t *)Block + 5));
  if ( operator new(0x720u) != nullptr )
    v10 = sub_44BDA0(Block);
  else
    v10 = 0;
  *((uint32_t *)Block + 7) = v10;
  v11 = operator new(0x184u);
  if ( v11 != nullptr )
    v12 = sub_44FF60(v11, Block);
  else
    v12 = nullptr;
  *((uint32_t *)Block + 8) = v12;
  sub_69A840(v12[6]);
  if ( operator new(0x108u) != nullptr )
    v13 = sub_44DA60(Block);
  else
    v13 = 0;
  *((uint32_t *)Block + 9) = v13;
  sub_69A840(*(uint32_t *)(v13 + 24));
  if ( operator new(0xF0u) != nullptr )
    v14 = sub_44ACE0(Block);
  else
    v14 = 0;
  *((uint32_t *)Block + 10) = v14;
  sub_69A840(*(uint32_t *)(v14 + 8));
  v15 = operator new(0x68u);
  if ( v15 != nullptr )
    v16 = sub_426BD0(v15);
  else
    v16 = nullptr;
  *((uint32_t *)Block + 30) = v16;
  sub_69A840(v16);
  v17 = operator new(0x44u);
  v18 = v17;
  if ( v17 != nullptr )
  {
    *(uint32_t *)v17 = &CNRDTutorial::`vftable';
    v17[24] = 0;
    *((uint32_t *)v17 + 5) = &off_6C2B88;
    *((uint32_t *)v17 + 7) = 0;
    v17[32] = 1;
    v17[34] = 0;
    v17[33] = 0;
    *((uint32_t *)v17 + 11) = 0;
    *((uint32_t *)v17 + 10) = 0;
    *((uint32_t *)v17 + 9) = 0;
    sub_546030(v17);
    sub_546F30(Block);
  }
  else
  {
    v18 = nullptr;
  }
  *((uint32_t *)Block + 11) = v18;
  sub_69A840(*((uint32_t *)v18 + 2));
  if ( operator new(0xE0u) != nullptr )
    v19 = sub_44E000(Block);
  else
    v19 = 0;
  *((uint32_t *)Block + 12) = v19;
  sub_69A840(*(uint32_t *)(v19 + 48));
  v20 = operator new(0x68u);
  if ( v20 != nullptr )
    v21 = sub_426BD0(v20);
  else
    v21 = nullptr;
  *((uint32_t *)Block + 13) = v21;
  sub_69A840(v21);
  v22 = operator new(0x3Cu);
  v23 = v22;
  if ( v22 != nullptr )
  {
    *v22 = &off_6C64BC;
    sub_540330(v22);
    sub_540340(Block, 1);
    *v23 = &CNRDItemInventoryWindow::`vftable';
    sub_546FD0(v23);
    sub_5481A0(v23);
  }
  else
  {
    v23 = nullptr;
  }
  *((uint32_t *)Block + 14) = v23;
  v24 = operator new(0x34u);
  v25 = v24;
  if ( v24 != nullptr )
  {
    *v24 = &off_6C64BC;
    sub_540330(v24);
    sub_540340(Block, 1);
    *v25 = &CNRDAvatarInventoryWindow::`vftable';
    sub_54ABC0(v25);
    sub_549AC0(v25);
  }
  else
  {
    v25 = nullptr;
  }
  *((uint32_t *)Block + 15) = v25;
  if ( operator new(0xE4u) != nullptr )
    v26 = sub_44B2E0(Block);
  else
    v26 = 0;
  *((uint32_t *)Block + 16) = v26;
  if ( operator new(0x148u) != nullptr )
    v27 = sub_44DC90(Block);
  else
    v27 = 0;
  *((uint32_t *)Block + 17) = v27;
  v28 = operator new(0x34u);
  v29 = v28;
  if ( v28 != nullptr )
  {
    *v28 = &off_6C64BC;
    sub_540330(v28);
    sub_540340(Block, 1);
    *v29 = &CNRDSkillInventoryWindow::`vftable';
    sub_54ABC0(v29);
    sub_54B4E0(v29);
  }
  else
  {
    v29 = nullptr;
  }
  *((uint32_t *)Block + 18) = v29;
  if ( operator new(0x50u) != nullptr )
    v30 = sub_44B550(Block);
  else
    v30 = 0;
  *((uint32_t *)Block + 19) = v30;
  if ( operator new(0xC0u) != nullptr )
    v31 = sub_44F7B0(Block);
  else
    v31 = 0;
  *((uint32_t *)Block + 20) = v31;
  if ( operator new(0xD4u) != nullptr )
    v32 = sub_44E440(Block);
  else
    v32 = 0;
  *((uint32_t *)Block + 21) = v32;
  if ( operator new(0xD8u) != nullptr )
    v33 = sub_44DDF0(Block);
  else
    v33 = 0;
  *((uint32_t *)Block + 22) = v33;
  if ( operator new(0x98u) != nullptr )
    v34 = sub_44B750(Block);
  else
    v34 = 0;
  *((uint32_t *)Block + 24) = v34;
  if ( operator new(0x114u) != nullptr )
    v35 = sub_44F9B0(Block);
  else
    v35 = 0;
  *((uint32_t *)Block + 25) = v35;
  *((uint32_t *)Block + 23) = 0;
  sub_541AD0((int)(Block + 92));
  v36 = operator new(0x40u);
  v37 = v36;
  if ( v36 != nullptr )
  {
    *v36 = &off_6C64BC;
    sub_540330(v36);
    sub_540340(Block, 0);
    *v37 = &CNRDPrivateStoreWindow::`vftable';
    sub_541900(v37);
    sub_544250(v37);
    *v37 = &CNRDPrivateStoreWindow_Display::`vftable';
    sub_542360(v37);
    sub_543190(v37);
  }
  v38 = operator new(0x30u);
  v39 = v38;
  if ( v38 != nullptr )
  {
    *v38 = &off_6C64BC;
    sub_540330(v38);
    sub_540340(Block, 0);
    *v39 = &CNRDPrivateStoreWindow::`vftable';
    sub_541900(v39);
    sub_544250(v39);
    *v39 = &CNRDPrivateStoreWindow_Sell::`vftable';
    sub_542470(v39);
    sub_5434F0(v39);
  }
  v40 = operator new(0x2Cu);
  v41 = v40;
  if ( v40 != nullptr )
  {
    *v40 = &off_6C64BC;
    sub_540330(v40);
    sub_540340(Block, 0);
    *v41 = &CNRDPrivateStoreWindow::`vftable';
    sub_541900(v41);
    sub_544250(v41);
    *v41 = &CNRDPrivateStoreWindow_Buy::`vftable';
    sub_542480(v41);
    sub_5446F0(v41);
  }
  v42 = operator new(0x68u);
  if ( v42 != nullptr )
    v43 = sub_426BD0(v42);
  else
    v43 = nullptr;
  *((uint32_t *)Block + 28) = v43;
  *((uint32_t *)v43 + 17) = Block;
  sub_69A840(*((uint32_t *)Block + 28));
  v44 = operator new(0x68u);
  if ( v44 != nullptr )
    v45 = sub_426BD0(v44);
  else
    v45 = nullptr;
  *((uint32_t *)Block + 31) = v45;
  sub_69A840(v45);
  sub_69A840(*((uint32_t *)Block + 6));
  sub_69A840(*(uint32_t *)(*((uint32_t *)Block + 7) + 120));
  if ( operator new(0x6Cu) != nullptr )
    v46 = sub_44AE70(Block);
  else
    v46 = 0;
  *((uint32_t *)Block + 605) = v46;
  sub_69A840(*(uint32_t *)(v46 + 8));
  if ( operator new(0x9Cu) != nullptr )
    v47 = sub_44AFB0(Block, dword_99FD58);
  else
    v47 = 0;
  *((uint32_t *)Block + 607) = v47;
  sub_69A840(*(uint32_t *)(v47 + 48));
  if ( operator new(0x150u) != nullptr )
    v48 = sub_44B0C0(Block, dword_99FD58);
  else
    v48 = 0;
  *((uint32_t *)Block + 608) = v48;
  sub_69A840(*(uint32_t *)(v48 + 76));
  v49 = (char *)operator new(0x298u);
  if ( v49 != nullptr )
    v50 = sub_450340(v49, dword_99FD58);
  else
    v50 = nullptr;
  *((uint32_t *)Block + 609) = v50;
  sub_69A840(*((uint32_t *)v50 + 11));
  if ( operator new(0xBCu) != nullptr )
    v51 = sub_44DBB0(Block);
  else
    v51 = 0;
  *((uint32_t *)Block + 610) = v51;
  sub_69A840(*(uint32_t *)(v51 + 68));
  v52 = (char *)operator new(0x2794u);
  if ( v52 != nullptr )
    v53 = sub_450620(v52, (int)Block);
  else
    v53 = nullptr;
  *((uint32_t *)Block + 611) = v53;
  sub_69A840(*((uint32_t *)v53 + 13));
  v54 = operator new(0x24u);
  v55 = v54;
  if ( v54 != nullptr )
  {
    *v54 = &CNRDSelectWarRoomArea::`vftable';
    sub_540370(v54);
    sub_540670(v55);
  }
  else
  {
    v55 = nullptr;
  }
  *((uint32_t *)Block + 633) = v55;
  sub_69A840(v55[1]);
  v56 = operator new(0x5Cu);
  v57 = v56;
  if ( v56 != nullptr )
  {
    sub_44E260(v56);
    *v57 = &CNRDWarRoomBattleTalkBox::`vftable';
    sub_49A9C0(v57);
    nullsub_3();
  }
  else
  {
    v57 = nullptr;
  }
  *((uint32_t *)Block + 634) = v57;
  sub_69A840(v57[1]);
  v58 = operator new(0x68u);
  if ( v58 != nullptr )
    v59 = sub_426BD0(v58);
  else
    v59 = nullptr;
  *((uint32_t *)Block + 32) = v59;
  sub_69A840(v59);
  v60 = operator new(0x4Cu);
  v61 = v60;
  if ( v60 != nullptr )
  {
    *v60 = &CNRDStackNumberSet::`vftable';
    sub_540890(v60);
    sub_540AE0(Block);
  }
  else
  {
    v61 = nullptr;
  }
  *((uint32_t *)Block + 29) = v61;
  sub_69A840(v61[2]);
  v62 = operator new(0x68u);
  if ( v62 != nullptr )
    v63 = sub_426BD0(v62);
  else
    v63 = nullptr;
  *((uint32_t *)Block + 612) = v63;
  *((uint32_t *)v63 + 17) = Block;
  sub_69A840(*((uint32_t *)Block + 612));
  v64 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                    dword_8F84B8,
                    "Common/Etc/MonoLayer.img");
  *((uint32_t *)Block + 613) = sub_418DD0(v64, 2u);
  *(Block + 2468) = 0;
  *((uint32_t *)Block + 622) = sub_418DD0(v64, 0);
  *((uint32_t *)Block + 624) = sub_418DD0(v64, 1u);
  v65 = operator new(0x40u);
  v66 = v65;
  if ( v65 != nullptr )
  {
    *(uint32_t *)v65 = &CNRDCursor::`vftable';
    v65[16] = 0;
    *((uint32_t *)v65 + 3) = &off_6C2B88;
    *((uint32_t *)v65 + 5) = 0;
    v65[24] = 1;
    v65[26] = 0;
    v65[25] = 0;
    *((uint32_t *)v65 + 9) = 0;
    *((uint32_t *)v65 + 8) = 0;
    *((uint32_t *)v65 + 7) = 0;
    sub_544FC0(v65);
    sub_545400(Block);
  }
  else
  {
    v66 = nullptr;
  }
  *((uint32_t *)Block + 625) = v66;
  v67 = operator new(0x94u);
  v68 = v67;
  if ( v67 != nullptr )
  {
    sub_426BD0(v67);
    *v68 = &nengine::CNFrame::`vftable';
    sub_69C6B0(v68);
    *v68 = &CNRDMakePriceWindow::`vftable';
    sub_5449A0(v68);
    sub_544E40(Block);
  }
  else
  {
    v68 = nullptr;
  }
  return sub_69A840(v68[28]);
}


// ------------------------------------------------------------
// 0x451750 sub_451750
// ------------------------------------------------------------
void /*thiscall*/ sub_451750(int this)
{
  uint32_t *v2; // esi
  int i; // ebx
  void *v4; // esi
  uint32_t *v5; // esi
  int j; // ebx
  void *v7; // esi
  HGDIOBJ *v8; // esi
  HGDIOBJ *v9; // esi
  void *v10; // esi
  uint32_t *v11; // esi
  HGDIOBJ *v12; // esi
  void (/*thiscall*/ ***v13)(uint32_t, int); // ecx
  uint32_t *v14; // esi
  int k; // ebx
  void (/*thiscall*/ ***v16)(uint32_t, int); // ecx
  uint32_t *v17; // esi
  uint32_t *v18; // esi
  int m; // ebx
  uint32_t *v20; // ebx
  uint32_t *ii; // esi
  uint32_t *jj; // esi
  void *v23; // esi
  void *v24; // esi
  void *v25; // esi
  char *v26; // esi
  void **v27; // esi
  void **v28; // esi
  uint32_t *v29; // esi
  uint32_t *v30; // esi
  void (/*thiscall*/ ***v31)(uint32_t, int); // ecx
  uint32_t *v32; // esi
  int n; // [esp+Ch] [ebp-4h]

  v2 = (uint32_t *)(this + 8);
  for ( i = 2; i != 0; --i )
  {
    if ( *v2 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v2)(*v2, 1);
    *v2++ = 0;
  }
  v4 = *(void **)(this + 16);
  if ( v4 != nullptr )
  {
    sub_44C4C0(*(char **)(this + 16));
    j__free(v4);
  }
  *(uint32_t *)(this + 16) = 0;
  v5 = (uint32_t *)(this + 20);
  for ( j = 2; j != 0; --j )
  {
    if ( *v5 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v5)(*v5, 1);
    *v5++ = 0;
  }
  v7 = *(void **)(this + 28);
  if ( v7 != nullptr )
  {
    sub_44BF40(*(uint32_t *)(this + 28));
    j__free(v7);
  }
  v8 = *(HGDIOBJ **)(this + 32);
  *(uint32_t *)(this + 28) = 0;
  if ( v8 != nullptr )
  {
    sub_450130(v8);
    j__free(v8);
  }
  v9 = *(HGDIOBJ **)(this + 36);
  *(uint32_t *)(this + 32) = 0;
  if ( v9 != nullptr )
  {
    sub_44C130(v9);
    j__free(v9);
  }
  v10 = *(void **)(this + 40);
  *(uint32_t *)(this + 36) = 0;
  if ( v10 != nullptr )
  {
    sub_44AD80(v10);
    j__free(v10);
  }
  v11 = *(uint32_t **)(this + 44);
  *(uint32_t *)(this + 40) = 0;
  if ( v11 != nullptr )
  {
    sub_44AE20(v11);
    j__free(v11);
  }
  v12 = *(HGDIOBJ **)(this + 48);
  *(uint32_t *)(this + 44) = 0;
  if ( v12 != nullptr )
  {
    sub_44C310(v12);
    j__free(v12);
  }
  v13 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 52);
  *(uint32_t *)(this + 48) = 0;
  if ( v13 != nullptr )
    (**v13)(v13, 1);
  *(uint32_t *)(this + 52) = 0;
  v14 = (uint32_t *)(this + 56);
  for ( k = 12; k != 0; --k )
  {
    if ( *v14 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*v14 + 4))(*v14, 1);
    *v14++ = 0;
  }
  v16 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 112);
  if ( v16 != nullptr )
    (**v16)(v16, 1);
  v17 = *(uint32_t **)(this + 116);
  *(uint32_t *)(this + 112) = 0;
  if ( v17 != nullptr )
  {
    *v17 = &CNRDStackNumberSet::`vftable';
    sub_5408E0(v17);
    j__free(v17);
  }
  *(uint32_t *)(this + 116) = 0;
  v18 = (uint32_t *)(this + 120);
  for ( m = 3; m != 0; --m )
  {
    if ( *v18 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v18)(*v18, 1);
    *v18++ = 0;
  }
  v20 = (uint32_t *)(this + 140);
  for ( n = 71; n != 0; --n )
  {
    for ( ii = (uint32_t *)*(v20 - 1); ii != (uint32_t *)*v20; ++ii )
    {
      if ( *ii != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*ii + 4))(*ii, 1);
      *ii = 0;
    }
    for ( jj = (uint32_t *)v20[283]; jj != (uint32_t *)v20[284]; ++jj )
    {
      if ( *jj != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*jj + 4))(*jj, 1);
      *jj = 0;
    }
    v20 += 4;
  }
  v23 = *(void **)(this + 2420);
  if ( v23 != nullptr )
  {
    sub_44AF20(*(uint32_t *)(this + 2420));
    j__free(v23);
  }
  v24 = *(void **)(this + 2428);
  *(uint32_t *)(this + 2420) = 0;
  if ( v24 != nullptr )
  {
    sub_44B060(v24);
    j__free(v24);
  }
  v25 = *(void **)(this + 2432);
  *(uint32_t *)(this + 2428) = 0;
  if ( v25 != nullptr )
  {
    sub_44B160(v25);
    j__free(v25);
  }
  v26 = *(char **)(this + 2436);
  *(uint32_t *)(this + 2432) = 0;
  if ( v26 != nullptr )
  {
    sub_4504F0(v26);
    j__free(v26);
  }
  v27 = *(void ***)(this + 2440);
  *(uint32_t *)(this + 2436) = 0;
  if ( v27 != nullptr )
  {
    sub_44CDE0(v27);
    j__free(v27);
  }
  v28 = *(void ***)(this + 2444);
  *(uint32_t *)(this + 2440) = 0;
  if ( v28 != nullptr )
  {
    sub_450970(v28);
    j__free(v28);
  }
  v29 = *(uint32_t **)(this + 2532);
  *(uint32_t *)(this + 2444) = 0;
  if ( v29 != nullptr )
  {
    *v29 = &CNRDSelectWarRoomArea::`vftable';
    sub_540390(v29);
    j__free(v29);
  }
  v30 = *(uint32_t **)(this + 2536);
  *(uint32_t *)(this + 2532) = 0;
  if ( v30 != nullptr )
  {
    sub_44C8C0(v30);
    j__free(v30);
  }
  v31 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 2448);
  *(uint32_t *)(this + 2536) = 0;
  if ( v31 != nullptr )
    (**v31)(v31, 1);
  v32 = *(uint32_t **)(this + 2500);
  *(uint32_t *)(this + 2448) = 0;
  if ( v32 != nullptr )
  {
    sub_44AC30(v32);
    j__free(v32);
  }
  *(uint32_t *)(this + 2500) = 0;
  if ( dword_9B8050 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_9B8050)(dword_9B8050, 1);
}


// ------------------------------------------------------------
// 0x451AD0 sub_451AD0
// ------------------------------------------------------------
// 世界地图交互：CLICK_BUTTON1（按钮音效自证）【推断：翻页/确认】
int /*thiscall*/ sub_451AD0(int *this)
{
  int v2; // eax
  int v3; // esi
  int v4; // ebx
  int v5; // eax
  int result; // eax
  int v7; // esi
  int v8; // ebx
  int v9; // eax
  int v10; // edx
  int v11; // esi
  int v12; // eax
  char *v13; // eax
  char *v14; // eax
  int v15; // eax
  int v16; // [esp-4h] [ebp-28h]
  int v17; // [esp+10h] [ebp-14h] BYREF
  int v18; // [esp+14h] [ebp-10h] BYREF
  int v19; // [esp+20h] [ebp-4h]

  v2 = *(this + 26);
  v3 = 0;
  v4 = 0;
  if ( v2 != 12 )
    v3 = *(this + v2 + 14);
  v5 = *(this + 27);
  if ( v5 != 12 )
    v4 = *(this + v5 + 14);
  result = sub_461B80(*(this + 4));
  if ( (uint8_t)result == 0
    && (v3 == 0 || (uint8_t)(result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 40))(v3)) == 0)
    && (v4 == 0 || (uint8_t)(result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 40))(v4)) == 0) )
  {
    if ( (unsigned int)*(this + 626) > 2 )
    {
      *(this + 626) = 0;
      sub_432EA0("CLICK_BUTTON1", -1, 0, 0);
    }
    result = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 36);
    if ( *(uint8_t *)(result + 17) != 0 && dword_79BE38 == *(uint32_t *)(result + 12) && *(uint32_t *)(dword_8F7A24 + 12) == 1 )
    {
      v7 = dword_8F7C08;
      if ( dword_8F7C08 != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C08 + 80))(dword_8F7C08);
        if ( result != 0 )
        {
          v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 80))(v7);
          v18 = sub_45E510(pt.x, 1);
          v9 = sub_45E550(pt.y, 0, 1);
          v10 = *(uint32_t *)v7;
          v17 = v9;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(v10 + 136))(v7, v18, v9, 0) != 0
            || (uint8_t)(result = (*(int (/*thiscall*/ **)(int, int *, int *, int, int, int, uint32_t, int))(*(uint32_t *)v7 + 140))(
                                  v7,
                                  &v18,
                                  &v17,
                                  v18,
                                  v17,
                                  100,
                                  0,
                                  1)) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v7 + 372))(v7, v18, v17);
            v11 = 0;
            byte_8F8118 = 1;
            sub_432EA0("CLICK_MOVE", -1, 0, 0);
            if ( *(this + 632) == 0 )
            {
              v12 = sub_42FCB0(228);
              v19 = 0;
              if ( v12 != 0 )
                v11 = sub_431860(v12, "Common/Etc/Animation/MoveDestinationMark.ani", 1);
              v19 = -1;
              v13 = (char *)sub_44B6C0(284);
              v19 = 1;
              if ( v13 != nullptr )
                v14 = sub_44E1F0(v13, v11, 0);
              else
                v14 = nullptr;
              v19 = -1;
              *(this + 632) = (int)v14;
            }
            if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 632) + 80))(*(this + 632)) != 0 )
            {
              v16 = *(this + 632);
              (*(void (**)(void))(*(uint32_t *)v16 + 80))();
              sub_45F1E0(v16);
            }
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*(this + 632) + 112))(
              *(this + 632),
              v18,
              v17,
              0);
            sub_45FE80(v8, (int)this, 2, 0, *(this + 632), 0, 0);
            v15 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 632) + 200))(*(this + 632));
            return sub_4926A0(v15);
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
void /*thiscall*/ sub_451D50(int this)
{
  int v1; // ebx
  int v3; // eax
  bool v4; // sf
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // eax
  uint32_t *v12; // edi
  int i; // ebx
  uint32_t *v14; // ebx
  uint32_t *k; // edi
  void *v16; // eax
  uint32_t *m; // edi
  int v18; // eax
  int v19; // ecx
  int v20; // edi
  int v21; // eax
  int v22; // eax
  int v23; // edi
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  char v27; // bl
  int v28; // eax
  int v29; // ecx
  int v30; // edi
  int v31; // eax
  int v32; // eax
  int v33; // ecx
  int v34; // edi
  int v35; // eax
  int v36; // eax
  int v37; // eax
  int v38; // edi
  int v39; // edi
  int v40; // ebx
  char v41; // al
  int v42; // eax
  int v43; // eax
  int v44; // edi
  int v45; // eax
  int v46; // ecx
  int v47; // ecx
  uint32_t *v48; // ebx
  int v49; // edi
  int v50; // eax
  int v51; // ecx
  int ii; // edi
  int v53; // ecx
  int v54; // ecx
  int v55; // eax
  uint32_t *Block; // [esp+10h] [ebp-24h]
  uint32_t *v57; // [esp+14h] [ebp-20h]
  int v58; // [esp+1Ch] [ebp-18h]
  int j; // [esp+20h] [ebp-14h]
  int *v60; // [esp+20h] [ebp-14h]
  int n; // [esp+20h] [ebp-14h]
  char v62; // [esp+27h] [ebp-Dh]
  char v63; // [esp+27h] [ebp-Dh]
  char v64; // [esp+27h] [ebp-Dh]

  v1 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( *(uint8_t *)(*(uint32_t *)(this + 28) + 256) == 0
    && (v1 == 3 || v1 == 6)
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, 10) == 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 31) != 0 )
  {
    v3 = *(uint32_t *)(this + 4) + 1;
    v4 = *(uint32_t *)(this + 4) - 1 < 0;
    *(uint32_t *)(this + 4) = v3;
    if ( !(v4 ^ __OFSUB__(v3, 2) | (v3 == 2)) )
      *(uint32_t *)(this + 4) = 0;
  }
  if ( v1 != 3 && v1 != 6 )
    *(uint32_t *)(this + 4) = 0;
  v5 = *(uint32_t *)(this + 4);
  if ( v5 == 1 || v5 == 2 )
  {
    if ( *(uint32_t *)(this + 56) != 0 || *(uint32_t *)(this + 60) != 0 )
    {
      v6 = *(uint32_t *)(this + 108);
      if ( v6 != 12 )
      {
        v7 = *(uint32_t *)(this + 4 * v6 + 56);
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 48))(v7);
        sub_69A580(v8);
        *(uint32_t *)(this + 108) = 12;
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 16))(v7);
      }
    }
    if ( *(uint32_t *)(this + 76) != 0 )
    {
      v9 = *(uint32_t *)(this + 104);
      if ( v9 != 12 )
      {
        v10 = *(uint32_t *)(this + 4 * v9 + 56);
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 48))(v10);
        sub_69A580(v11);
        *(uint32_t *)(this + 104) = 12;
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 16))(v10);
      }
    }
    sub_44E850((uint32_t *)this, 18);
    sub_44E850((uint32_t *)this, 26);
  }
  sub_463FB0(*(uint32_t *)(this + 16));
  sub_441750(*(uint32_t *)(this + 28));
  sub_52BBB0(*(uint32_t *)(this + 32));
  sub_49CBD0(*(uint32_t *)(this + 36));
  if ( *(uint32_t *)(this + 4) != 0 || v1 != 6 )
  {
    sub_49CD70(0);
  }
  else if ( *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 32) <= 1u )
  {
    sub_49CD70(1);
  }
  sub_545800(*(uint32_t *)(this + 40));
  nullsub_3(*(uint32_t *)(this + 44));
  sub_526070(*(uint32_t *)(this + 48));
  v12 = (uint32_t *)(this + 104);
  for ( i = 2; i != 0; --i )
  {
    if ( *v12 != 12 )
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4 * *v12 + 56) + 8))(*(uint32_t *)(this + 4 * *v12 + 56));
    ++v12;
  }
  sub_541620(*(uint32_t *)(this + 116));
  v14 = (uint32_t *)(this + 140);
  for ( j = 71; j != 0; --j )
  {
    for ( k = (uint32_t *)*(v14 - 1); k != (uint32_t *)*v14; ++k )
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*k + 8))(*k);
    v14 += 4;
  }
  sub_44D490(this + 2404);
  v16 = *(void **)(this + 2408);
  if ( v16 != nullptr )
    j__free(v16);
  *(uint32_t *)(this + 2408) = 0;
  *(uint32_t *)(this + 2412) = 0;
  *(uint32_t *)(this + 2416) = 0;
  for ( m = Block; m != v57; ++m )
    sub_44E780(*m);
  sub_49E0E0(*(uint32_t *)(this + 2428));
  sub_4773B0(*(uint32_t *)(this + 2432));
  sub_457010(*(uint32_t *)(this + 2436));
  sub_54F9B0(*(uint32_t *)(this + 2440));
  sub_561E10(*(uint32_t *)(this + 2444));
  sub_540420(*(uint32_t *)(this + 2532));
  sub_544FE0(*(uint32_t *)(this + 2500));
  v62 = byte_89D274;
  if ( byte_89D274 != 0 )
  {
    v18 = *(uint32_t *)(this + 104);
    v19 = 0;
    v20 = 0;
    if ( v18 != 12 )
      v19 = *(uint32_t *)(this + 4 * v18 + 56);
    v21 = *(uint32_t *)(this + 108);
    if ( v21 != 12 )
      v20 = *(uint32_t *)(this + 4 * v21 + 56);
    if ( (v19 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 24))(v19) == 0) && v20 != 0 )
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 24))(v20);
  }
  if ( *(uint8_t *)(this + 2524) != v62 )
  {
    if ( v62 != 0 )
    {
      v22 = *(uint32_t *)(this + 104);
      v23 = 0;
      v24 = 0;
      if ( v22 != 12 )
        v23 = *(uint32_t *)(this + 4 * v22 + 56);
      v25 = *(uint32_t *)(this + 108);
      if ( v25 != 12 )
        v24 = *(uint32_t *)(this + 4 * v25 + 56);
      if ( (uint8_t)sub_460830(*(uint32_t *)(this + 16)) == 0
        && (v23 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v23 + 20))(v23) == 0)
        && v24 != 0 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v24 + 20))(v24);
      }
    }
    else
    {
      sub_44FC40(this);
      v26 = *(uint32_t *)(this + 2504);
      if ( v26 == 1 || v26 == 2 )
      {
        *(uint32_t *)(this + 2504) = 0;
        *(uint32_t *)(this + 2508) = 12;
        *(uint32_t *)(this + 2512) = 0;
        *(uint32_t *)(this + 2516) = 0;
        *(uint32_t *)(this + 2520) = 0;
      }
    }
    *(uint8_t *)(this + 2524) = v62;
  }
  v27 = byte_89D275;
  if ( byte_89D275 != 0 )
  {
    v28 = *(uint32_t *)(this + 104);
    v29 = 0;
    v30 = 0;
    if ( v28 != 12 )
      v29 = *(uint32_t *)(this + 4 * v28 + 56);
    v31 = *(uint32_t *)(this + 108);
    if ( v31 != 12 )
      v30 = *(uint32_t *)(this + 4 * v31 + 56);
    if ( (v29 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v29 + 36))(v29) == 0) && v30 != 0 )
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v30 + 36))(v30);
  }
  if ( *(uint8_t *)(this + 2525) != v27 )
  {
    if ( v27 != 0 )
    {
      v32 = *(uint32_t *)(this + 104);
      v33 = 0;
      v34 = 0;
      if ( v32 != 12 )
        v33 = *(uint32_t *)(this + 4 * v32 + 56);
      v35 = *(uint32_t *)(this + 108);
      if ( v35 != 12 )
        v34 = *(uint32_t *)(this + 4 * v35 + 56);
      if ( (v33 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v33 + 32))(v33) == 0) && v34 != 0 )
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v34 + 32))(v34);
    }
    else
    {
      sub_451AD0(this);
    }
    *(uint8_t *)(this + 2525) = v27;
  }
  v36 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v36 == 1 )
  {
    if ( (uint8_t)sub_4BFBC0(&unk_8F85B4, 0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
      v37 = sub_45E9B0(dword_8F7C08);
      v38 = v37;
      if ( v37 != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v37 + 40))(v37, 34) != 0 )
          sub_567F40(0);
        else
          sub_526BF0(v38, 0);
      }
    }
    goto LABEL_118;
  }
  if ( v36 != 3 )
  {
    if ( v36 != 6 )
      goto LABEL_118;
    if ( (uint8_t)sub_42B560(*(uint32_t *)(dword_8F7A24 + 40)) == 0 )
      goto LABEL_118;
    if ( (uint8_t)sub_4BFBC0(&unk_8F85B4, 0) == 0 )
      goto LABEL_118;
    v44 = dword_8F7C04;
    if ( dword_8F7C04 == 0
      || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1196))(dword_8F7C04) == 0 )
    {
      goto LABEL_118;
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4)) != 0 )
    {
LABEL_106:
      v45 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v44 + 52))(v44);
      sub_486D40(v45);
      goto LABEL_118;
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) < (unsigned int)dword_795210 )
      goto LABEL_118;
    v46 = *((uint32_t *)dword_8F8528 + 611);
LABEL_117:
    sub_55D210(v46);
    goto LABEL_118;
  }
  if ( *(uint32_t *)(*(uint32_t *)(this + 2432) + 4) == 0
    && *(uint32_t *)(*(uint32_t *)(this + 2436) + 4) == 0
    && *(uint32_t *)(*(uint32_t *)(this + 2440) + 8) == 0 )
  {
    v39 = 0;
    v40 = 16;
    v60 = &dword_77FD48;
    do
    {
      v41 = sub_4BF250(v60);
      v63 = v41;
      if ( *(uint8_t *)(this + v39 + 2424) == 0 && v41 != 0 && v39 != sub_456420(dword_8F850C) )
      {
        v42 = *(uint32_t *)(v40 + dword_8F850C);
        v58 = v42;
        if ( v42 != 0 )
        {
          v43 = *(uint32_t *)(v42 + 196);
          if ( v43 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v43 + 1196))(v43) != 0 )
            sub_486D40(*(uint16_t *)(v58 + 4));
        }
      }
      *(uint8_t *)(this + v39 + 2424) = v63;
      v40 += 4;
      ++v39;
      v60 += 2;
    }
    while ( v40 < 32 );
    if ( (uint8_t)sub_4BFBC0(&unk_8F85B4, 0) != 0 )
    {
      v44 = dword_8F7C04;
      if ( dword_8F7C04 != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1196))(dword_8F7C04) != 0 )
      {
        if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4)) != 0 )
          goto LABEL_106;
        if ( (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) < (unsigned int)dword_795210 )
          goto LABEL_118;
        v46 = *((uint32_t *)dword_8F8528 + 611);
        goto LABEL_117;
      }
    }
  }
LABEL_118:
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 26) != 0
    && *(uint32_t *)(this + 2504) != 17 )
  {
    v47 = *(uint32_t *)(this + 48);
    v64 = 0;
    if ( *(uint32_t *)(v47 + 8) != 0 )
    {
      sub_525740(v47);
      v64 = 1;
    }
    v48 = (uint32_t *)(this + 104);
    for ( n = 2; n != 0; --n )
    {
      if ( *v48 != 12 )
      {
        v49 = *(uint32_t *)(this + 4 * *v48 + 56);
        v50 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v49 + 48))(v49);
        sub_69A580(v50);
        *v48 = 12;
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v49 + 16))(v49);
        v64 = 1;
      }
      ++v48;
    }
    v51 = *(uint32_t *)(this + 116);
    if ( *(uint8_t *)(*(uint32_t *)(v51 + 8) + 16) != 0 )
    {
      sub_540960(v51);
      v64 = 1;
    }
    for ( ii = 0; ii < 71; ++ii )
    {
      v53 = *(uint32_t *)(16 * ii + this + 136);
      if ( v53 != 0
        && (*(uint32_t *)(16 * ii + this + 140) - v53) >> 2 != 0
        && (ii != 15 || *(uint32_t *)(dword_8F7A24 + 12) != 3)
        && ((uint8_t)sub_41C590(dword_8F7A24) == 0 || ii != 2) )
      {
        sub_44E850((uint32_t *)this, ii);
        v64 = 1;
      }
    }
    v54 = *(uint32_t *)(this + 28);
    if ( *(uint8_t *)(v54 + 256) != 0 && *(uint8_t *)(*(uint32_t *)(v54 + 136) + 117) == 0 )
    {
      sub_43DA50(v54, szPassword, 0);
      sub_43B920(0);
      v64 = 1;
    }
    if ( *(uint32_t *)(*(uint32_t *)(this + 2444) + 12) != 0 )
    {
      sub_560610(0);
      v64 = 1;
    }
    if ( *(uint32_t *)(*(uint32_t *)(this + 2532) + 28) != 0 )
    {
      sub_5403D0(0);
    }
    else if ( v64 == 0
           && *(uint32_t *)(dword_8F7A24 + 12) != 5
           && *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 28) + 136) + 117) == 0
           && byte_9D3BE4 == 0 )
    {
      sub_44E8D0((char *)dword_8F8528, (void *)0x2B, 0, 0);
    }
  }
  if ( dword_8F7C04 != 0 && *(uint8_t *)(dword_8F7C04 + 8052) != 0 )
  {
    v55 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v55 == 4 || v55 == 6 )
      sub_4B0A80();
  }
  if ( Block != nullptr )
    j__free(Block);
}


// ============================================================
// 【分区 2】地图选择工具（0x452580-0x452FA0）
// 加载门 8 态推进 0x452700（分发器 case 0x25 落点）；
// PVP 房间地图装载 0x452C50（"HendonMyre/Hendon_Pub_PVP.map" 自证）。
// ============================================================
// ------------------------------------------------------------
// 0x452580 sub_452580
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_452580(uint32_t *this, int a2)
{
  int v2; // eax

  v2 = *(this + a2 + 1);
  return v2 == 4 || v2 == 3;
}



// ------------------------------------------------------------
// 0x4525B0 sub_4525B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4525B0(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 27);
  if ( v1 == -1 )
    return 0xFFFF;
  else
    return *(this + v1 + 10);
}



// ------------------------------------------------------------
// 0x4525D0 sub_4525D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4525D0(int this)
{
  int result; // eax

  result = 0;
  if ( *(uint8_t *)(this + 4) == 0 )
  {
    *(uint32_t *)(this + 12) = 0;
    *(uint32_t *)(this + 16) = 0;
    *(uint32_t *)(this + 20) = 0;
    *(uint32_t *)(this + 24) = 0;
    *(uint32_t *)(this + 28) = 0;
    *(uint32_t *)(this + 32) = 0;
    *(uint32_t *)(this + 36) = 0;
    *(uint32_t *)(this + 80) = 0;
    *(uint32_t *)(this + 84) = 0;
    *(uint32_t *)(this + 88) = 0;
    *(uint32_t *)(this + 92) = 0;
    *(uint32_t *)(this + 96) = 0;
    *(uint32_t *)(this + 100) = 0;
    *(uint32_t *)(this + 104) = 0;
    *(uint32_t *)(this + 108) = 0;
    *(uint8_t *)(this + 112) = 0;
    *(uint32_t *)(this + 116) = 0;
    *(uint8_t *)(this + 120) = 0;
    *(uint32_t *)(this + 124) = -1;
    *(uint32_t *)(this + 128) = 0;
    *(uint32_t *)(this + 132) = 0;
    *(uint8_t *)(this + 136) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x452630 sub_452630
// ------------------------------------------------------------
int /*stdcall*/ sub_452630(int a1, int a2)
{
  int result; // eax

  result = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  if ( a2 != result )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 104))(dword_8F8520, a1);
    result = off_77F3FC("@@REMOVE PEER");
  }
  if ( a2 != 0 )
  {
    result = *(uint32_t *)(a2 + 196);
    if ( result != 0 )
      return sub_45F1E0(*(uint32_t *)(a2 + 196));
  }
  return result;
}



// ------------------------------------------------------------
// 0x452690 sub_452690
// ------------------------------------------------------------
int /*thiscall*/ sub_452690(int *this)
{
  int result; // eax
  int *v3; // esi
  int i; // edi
  int v5; // [esp+4h] [ebp-4h] BYREF

  result = dword_99FEC0;
  if ( dword_99FEC0 != 0 )
  {
    result = sub_48F5A0();
    if ( *(uint32_t *)(dword_99FEC0 + 108) == result )
    {
      sub_423200(dword_8F7B08, 59);
      v3 = this + 20;
      for ( i = 8; i != 0; --i )
      {
        v5 = *v3;
        sub_423290(dword_8F7B08, (int)&v5, 4);
        ++v3;
      }
      return sub_423380(dword_8F7B08);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x452700 sub_452700
// ------------------------------------------------------------
// 分发器 case 0x25 落点 —— 加载门推进：a2(0..7) 置 +128 位表；
// 8 门（sub_48F690 查询存在性）全开或 a2==8 → sub_698FE0 触发事件
char /*thiscall*/ sub_452700(uint8_t *this, int a2)
{
  char v3; // bl
  int i; // esi
  int v5; // eax

  if ( a2 == 8 )
    goto LABEL_8;
  v3 = 1;
  *(this + a2 + 128) = 1;
  for ( i = 0; i < 8; ++i )
  {
    v5 = sub_48F690(i);
    if ( v5 != 0 )
    {
      LOBYTE(v5) = *(this + i + 128);
      if ( (uint8_t)v5 == 0 )
        v3 = 0;
    }
  }
  if ( v3 != 0 )
LABEL_8:
    LOBYTE(v5) = sub_698FE0((int)(this + 40));
  return v5;
}



// ------------------------------------------------------------
// 0x452760 sub_452760
// ------------------------------------------------------------
int /*stdcall*/ sub_452760(int a1)
{
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 37, 2);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, a1);
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
}



// ------------------------------------------------------------
// 0x4527A0 sub_4527A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4527A0(uint32_t *this, int a2, int a3)
{
  *(this + a2 + 20) += a3;
  return a2;
}



// ------------------------------------------------------------
// 0x4527C0 sub_4527C0
// ------------------------------------------------------------
double /*cdecl*/ sub_4527C0(unsigned int a1, int a2)
{
  int v2; // ecx
  unsigned int v4; // eax
  unsigned int v5; // edx

  v2 = a1;
  if ( a1 == -1 )
    return 1.0;
  if ( dword_98B720 == 0 )
    goto LABEL_9;
  v4 = (dword_98B724 - dword_98B720) / 44;
  v5 = a1;
  if ( a1 >= v4 )
    v5 = (dword_98B724 - dword_98B720) / 44;
  if ( v5 > 1 )
  {
    if ( a1 >= v4 )
      return *(float *)(44 * v4 + dword_98B720 - 44 + 4 * a2);
  }
  else
  {
LABEL_9:
    v2 = 1;
  }
  return *(float *)(44 * v2 + dword_98B720 - 44 + 4 * a2);
}



// ------------------------------------------------------------
// 0x452830 sub_452830
// ------------------------------------------------------------
char /*thiscall*/ sub_452830(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x5D1745D )
    sub_434730(this);
  v4 = (char *)operator new(44 * a2);
  *(this + 3) = &v4[44 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x452880 sub_452880
// ------------------------------------------------------------
void /*userpurge*/ sub_452880(uint32_t *a1@<ecx>, float a2@<esi>, double a3@<st0>, float a4, int a5)
{
  int v5; // edi
  uint32_t *v6; // esi
  uint32_t *v7; // eax
  int v8; // ebx
  int v9; // esi
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int *v13; // eax
  int *v14; // esi
  int *v15; // ebx
  double v16; // st7
  int *v17; // esi
  float v18; // [esp+0h] [ebp-14h]

  v5 = LODWORD(a4);
  if ( a4 != 0.0 )
  {
    v6 = a1 + 17;
    v7 = (uint32_t *)sub_42D430(a1 + 17, &a4);
    v8 = a5;
    if ( *v7 != a5 )
    {
      *(uint32_t *)sub_42D430(v6, &a4) = v8;
      v9 = __RTDynamicCast(v5, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      if ( v9 != 0 )
      {
        a4 = flt_7904FC;
        sub_433E90(a1, v5, 2);
        a3 = a3 * a4;
        v18 = a3;
        v10 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)v9 + 672))(v9, 0, LODWORD(v18));
        sub_42B3F0((void *)(v10 + 4), a2);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v9 + 676))(v9, 0);
        v11 = *(uint32_t *)v9;
        v12 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v9 + 740))(v9, 0, 1);
        (*(void (/*thiscall*/ **)(int, int))(v11 + 732))(v9, v12);
      }
      v13 = (int *)__RTDynamicCast(
                     v5,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &CNRDPassiveObject `RTTI Type Descriptor',
                     0);
      v14 = v13;
      if ( v13 != nullptr && v13[171] > 0 )
      {
        v15 = (int *)((*(int (/*thiscall*/ **)(int *))(*v13 + 672))(v13) + 4);
        sub_433E90(a1, v5, 2);
        v16 = a3 * (double)*v15 * flt_7904FC;
        *v15 = (uint64_t)v16;
        v17 = (int *)(*(int (/*thiscall*/ **)(int *))(*v14 + 672))(v14);
        sub_433E90(a1, v5, 2);
        *v17 = (uint64_t)(v16 * (double)*v17 * flt_7904FC);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x4529B0 sub_4529B0
// ------------------------------------------------------------
void /*userpurge*/ sub_4529B0(uint32_t *a1@<ecx>, double a2@<st0>, int ArgList, int a4, char a5)
{
  int v5; // edi
  int v7; // eax
  int v8; // esi
  int v9; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // [esp+8h] [ebp-4h] BYREF

  v5 = a4;
  if ( a4 != 0 )
  {
    v7 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    if ( v5 != v7 )
    {
      LOBYTE(v7) = a5 == 0;
      (*(void (/*thiscall*/ **)(int, int, int, int, uint32_t))(*(uint32_t *)dword_8F8520 + 100))(
        dword_8F8520,
        ArgList,
        v5,
        v7,
        0);
    }
    v8 = *(uint32_t *)(v5 + 196);
    if ( v8 != 0 )
    {
      sub_45FE80(a1[8], v5, 273, *(uint16_t *)(v5 + 4), v8, 0, 0);
      v9 = *(uint16_t *)(v5 + 4);
      v13 = 0;
      a4 = 0;
      sub_48C2A0(&v13, &a4, 0, v8, ArgList * v9);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v8 + 112))(v8, v13, a4, 0);
      sub_4B0780(v13, a4, 0);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 148))(v8, 1);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 1020))(v8);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v8 + 1200))(v8, 0);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 1212))(v8, ArgList);
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 388))(v8);
      sub_452880(a1, *(float *)&v8, a2, *(float *)&v8, v10);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 1056))(v8, 1);
      if ( dword_8F7C04 != 0 && *(uint8_t *)(dword_8F7C04 + 8052) != 0 )
      {
        v11 = *(uint32_t *)(a1[4] + 52);
        if ( v11 == 0 || v11 == dword_8F7C04 )
        {
          v12 = sub_4B05D0(0);
          sub_424A40((uint32_t *)a1[4], v12);
        }
      }
    }
    else
    {
      off_77F3FC(aCriticalError_4, ArgList);
    }
  }
}



// ------------------------------------------------------------
// 0x452B10 sub_452B10
// ------------------------------------------------------------
void */*thiscall*/ sub_452B10(void *this)
{
  sub_42DF70((int)this);
  nullsub_3();
  nullsub_3();
  return this;
}



// ------------------------------------------------------------
// 0x452B60 sub_452B60
// ------------------------------------------------------------
// 【推断】地图词条/路径辅助
uint32_t */*thiscall*/ sub_452B60(uint32_t *this, char ArgList, int a3)
{
  sub_42D6A0((int)this);
  *(this + 91) = 0;
  *(this + 92) = 0;
  *(this + 93) = 0;
  *(this + 95) = 0;
  *(this + 96) = 0;
  *(this + 97) = 0;
  *(this + 100) = 0;
  *(this + 101) = 0;
  *(this + 102) = 0;
  *(this + 103) = 0;
  *(this + 104) = 0;
  *(this + 105) = 0;
  *(this + 106) = 0;
  *(this + 107) = 0;
  *(this + 108) = 0;
  *(this + 109) = 0;
  *(this + 110) = 0;
  *(this + 111) = 0;
  *(this + 112) = 0;
  *(this + 113) = 0;
  *(this + 114) = 0;
  *(this + 115) = 0;
  *(this + 123) = 0;
  *(this + 124) = 0;
  *(this + 125) = 0;
  *(this + 127) = 0;
  *(this + 128) = 0;
  *(this + 129) = 0;
  sub_48D9D0(this);
  sub_48EED0(ArgList, a3);
  return this;
}



// ------------------------------------------------------------
// 0x452C50 sub_452C50
// ------------------------------------------------------------
// PVP 房间地图装载（"HendonMyre/Hendon_Pub_PVP.map" 自证）：
// sub_452B60 取词条 → dword_8F84B8 vt+60 载入 .map → 场景层创建
char /*thiscall*/ sub_452C50(int this)
{
  char result; // al
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  char *v5; // eax
  char *v6; // eax
  void *v7; // eax
  void *v8; // eax
  int v9; // ecx
  uint32_t *v10; // eax
  uint32_t *v11; // eax
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  uint32_t *v14; // ecx

  result = *(uint8_t *)(this + 4);
  if ( result == 0 )
  {
    *(uint8_t *)(this + 4) = 1;
    v3 = operator new(0x68u);
    if ( v3 != nullptr )
      v4 = sub_426BD0(v3);
    else
      v4 = nullptr;
    *(uint32_t *)(this + 12) = v4;
    *((uint32_t *)v4 + 17) = this + 8;
    v5 = (char *)operator new(0x558u);
    if ( v5 != nullptr )
      v6 = sub_42B7E0(v5);
    else
      v6 = nullptr;
    *(uint32_t *)(this + 16) = v6;
    sub_69A840(*((uint32_t *)v6 + 9));
    v7 = operator new(0x1F0u);
    if ( v7 != nullptr )
      v8 = sub_452B10(v7);
    else
      v8 = nullptr;
    v9 = *(uint32_t *)(this + 16);
    *(uint32_t *)(this + 20) = v8;
    *(uint32_t *)(v9 + 108) = v8;
    v10 = operator new(0x208u);
    if ( v10 != nullptr )
      v11 = sub_452B60(v10, (char)"HendonMyre/Hendon_Pub_PVP.map", 0);
    else
      v11 = nullptr;
    *(uint32_t *)(this + 24) = v11;
    *(uint32_t *)(this + 28) = 0;
    v12 = operator new(0xA0u);
    if ( v12 != nullptr )
      v13 = sub_42D590(v12, 0);
    else
      v13 = nullptr;
    v14 = *(uint32_t **)(this + 16);
    *(uint32_t *)(this + 32) = v13;
    sub_424100(v14, (int)v13);
    sub_69A840(*((uint32_t *)dword_8F8528 + 2));
    sub_69A840(*((uint32_t *)dword_8F8528 + 3));
    sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 16) + 40));
    return sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));
  }
  return result;
}



// ------------------------------------------------------------
// 0x452DF0 sub_452DF0
// ------------------------------------------------------------
int /*usercall*/ sub_452DF0@<eax>(uint32_t *a1@<ecx>, double a2@<st0>)
{
  void *v3; // esi
  int v4; // ecx
  uint32_t *v5; // eax
  int v6; // esi
  int v7; // eax
  int v8; // ebx
  int v9; // esi
  int v10; // eax
  uint16_t v11; // bx
  int v12; // eax
  int i; // esi
  int result; // eax
  int v15; // ecx
  int v16; // [esp+Ch] [ebp-Ch]
  int v17; // [esp+10h] [ebp-8h] BYREF
  int v18; // [esp+14h] [ebp-4h] BYREF

  sub_425500(a1[4], a1[6]);
  v3 = (void *)a1[7];
  if ( v3 != nullptr )
  {
    sub_42EDE0(a1[7]);
    j__free(v3);
  }
  v4 = a1[8];
  a1[7] = 0;
  sub_45FC60(v4);
  sub_4602C0(*(uint32_t *)(a1[6] + 476));
  sub_41CAA0(*(void **)(a1[18] + 4));
  *(uint32_t *)(a1[18] + 4) = a1[18];
  v5 = (uint32_t *)a1[18];
  a1[19] = 0;
  *v5 = v5;
  *(uint32_t *)(a1[18] + 8) = a1[18];
  v6 = 0;
  v16 = 0;
  do
  {
    v7 = sub_48F690(v6);
    v8 = v7;
    if ( v7 != 0 )
    {
      v9 = *(uint32_t *)(v7 + 196);
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 388))(v9);
      sub_452880(a1, *(float *)&v9, a2, *(float *)&v9, v10);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 1020))(v9);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v9 + 1200))(v9, 0);
      sub_45FE80(a1[8], (int)a1, 273, *(uint16_t *)(v8 + 4), v9, 0, 0);
      v11 = *(uint16_t *)(v8 + 4);
      v17 = 0;
      v18 = 0;
      v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 1216))(v9);
      sub_48C2A0(&v17, &v18, 0, v9, v11 * v12);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v9 + 112))(v9, v17, v18, 0);
      (*(void (/*thiscall*/ **)(int, int *, int *, int, int, int, uint32_t, int))(*(uint32_t *)v9 + 140))(
        v9,
        &v17,
        &v18,
        v17,
        v18,
        200,
        0,
        1);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v9 + 112))(v9, v17, v18, 0);
      v6 = v16;
    }
    v16 = ++v6;
  }
  while ( v6 < 8 );
  for ( i = 0; i < 8; ++i )
  {
    result = sub_48F690(i);
    if ( result != 0 )
    {
      v15 = *(uint32_t *)(dword_99FEC0 + 4 * i + 8);
      if ( v15 == 4 || v15 == 3 )
        result = (*(int (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(result + 196) + 112))(
                   *(uint32_t *)(result + 196),
                   -10000,
                   -10000,
                   0);
    }
  }
  return result;
}



// ============================================================
// 【分区 3】CNPVPModule 与座位管理（0x452FA0-0x454610）
// CNPVPModule__vmt4（RTTI 自证）；0x453DD0 = 座位/选中槽同步
// （战斗分发器 case 2/3 落点，CLICK_BUTTON2 自证）。
// ============================================================
// ------------------------------------------------------------
// 0x452FA0 sub_452FA0
// ------------------------------------------------------------
void /*thiscall*/ sub_452FA0(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void *v3; // edi
  void *v4; // edi
  void *v5; // edi
  void *v6; // edi
  void *v7; // edi

  if ( *(uint8_t *)(this + 4) != 0 )
  {
    v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
    *(uint8_t *)(this + 4) = 0;
    if ( v2 != nullptr )
      (**v2)(v2, 1);
    v3 = *(void **)(this + 16);
    *(uint32_t *)(this + 12) = 0;
    if ( v3 != nullptr )
    {
      sub_42BD40((int)v3);
      j__free(v3);
    }
    v4 = *(void **)(this + 20);
    *(uint32_t *)(this + 16) = 0;
    if ( v4 != nullptr )
    {
      sub_42E940(v4);
      j__free(v4);
    }
    v5 = *(void **)(this + 24);
    *(uint32_t *)(this + 20) = 0;
    if ( v5 != nullptr )
    {
      sub_42EDE0((int)v5);
      j__free(v5);
    }
    v6 = *(void **)(this + 28);
    *(uint32_t *)(this + 24) = 0;
    if ( v6 != nullptr )
    {
      sub_42EDE0((int)v6);
      j__free(v6);
    }
    v7 = *(void **)(this + 32);
    *(uint32_t *)(this + 28) = 0;
    if ( v7 != nullptr )
    {
      sub_42C770((int)v7);
      j__free(v7);
    }
    *(uint32_t *)(this + 32) = 0;
  }
}



// ------------------------------------------------------------
// 0x453050 sub_453050
// ------------------------------------------------------------
void /*userpurge*/ sub_453050(int a1@<ecx>, double a2@<st0>, int a3, int a4)
{
  int v5; // ecx
  int v6; // ebx
  int v7; // esi
  int v8; // eax
  int v9; // esi

  v5 = a1 + 40;
  *(uint32_t *)(a1 + 36) = a3;
  v6 = 0;
  *(uint8_t *)(v5 + 13) = 0;
  *(uint8_t *)(v5 + 14) = 0;
  sub_698F90(v5, 0, a4);
  if ( dword_8F7C04 == 0 || *(uint8_t *)(dword_8F7C04 + 8052) == 0 )
    sub_424A40(*(uint32_t **)(a1 + 16), dword_8F7C04);
  sub_4684F0(*((uint32_t *)dword_8F8528 + 4), nullptr);
  if ( a3 != 0 )
  {
    switch ( a3 )
    {
      case 1:
        sub_52C7F0(0);
        v7 = *((uint32_t *)dword_8F8528 + 4);
        sub_4926A0(*(uint32_t *)(v7 + 1016));
        *(uint32_t *)(v7 + 1020) = 0;
        sub_44E850(dword_8F8528, 40);
        sub_44E850(dword_8F8528, 43);
        break;
      case 2:
        *(uint32_t *)(a1 + 116) = 180000;
        sub_445830((uint8_t *)dword_8F8520, 1);
        break;
      case 3:
        do
        {
          v8 = sub_48F690(v6);
          if ( v8 != 0 )
          {
            v9 = *(uint32_t *)(v8 + 196);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 1200))(v9, 1);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 320))(v9);
          }
          ++v6;
        }
        while ( v6 < 8 );
        *(uint8_t *)(a1 + 112) = 0;
        CNCommandChecker__vmt40(0, 1);
        *((uint32_t *)dword_8F8528 + 621) = 0;
        break;
      case 4:
        *(uint32_t *)(a1 + 116) = 0;
        sub_445830((uint8_t *)dword_8F8520, 0);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 112))(dword_8F8520);
        break;
      default:
        break;
    }
  }
  else
  {
    CNCommandChecker__vmt40(0, 1);
    sub_52C7F0(1);
    sub_452DF0((uint32_t *)a1, a2);
    sub_4772A0(0);
    sub_45A420(0);
    sub_54F540(0);
    *((uint32_t *)dword_8F8528 + 621) = 0;
    *(uint32_t *)(a1 + 124) = -1;
    *(uint32_t *)(a1 + 128) = 0;
    *(uint32_t *)(a1 + 132) = 0;
    *(uint8_t *)(a1 + 120) = 0;
  }
}



// ------------------------------------------------------------
// 0x453230 sub_453230
// ------------------------------------------------------------
void /*usercall*/ sub_453230(int a1@<ecx>, double a2@<st0>)
{
  if ( *(uint8_t *)(a1 + 4) != 0 )
  {
    sub_453050(a1, a2, 0, 0);
    *(uint8_t *)(a1 + 136) = 0;
  }
}



// ------------------------------------------------------------
// 0x453250 CNPVPModule__vmt4
// ------------------------------------------------------------
// CNPVPModule::vmt4 —— PVP 模块帧处理（RTTI 自证）
char /*thiscall*/ sub_453250(int *this)
{
  int *v1; // esi
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
  uint8_t *v34; // esi
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
  int *v56; // [esp+20h] [ebp-14h]
  bool v57; // [esp+27h] [ebp-Dh]
  int v58; // [esp+30h] [ebp-4h]

  v1 = this;
  v56 = this;
  sub_4AEB30(&dword_9A02B0);
  v2 = 0;
  if ( byte_77F280 != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 88) != 0 )
  {
    *(uint32_t *)(dword_99FEC0 + 112) = 0;
    sub_453050(1, 0);
  }
  sub_433690();
  sub_4294E0(v1[4]);
  v3 = v1[9];
  switch ( v3 )
  {
    case 0:
      if ( dword_99FEC0 != 0 )
      {
        for ( i = 0; i < 8; ++i )
        {
          v5 = sub_48F690((uint32_t *)dword_99FEC0, i);
          if ( v5 != 0 )
          {
            v6 = *(int **)(v5 + 196);
            if ( v6 != nullptr )
            {
              v7 = (*(int (/*thiscall*/ **)(uint32_t))(*v6 + 740))(*(uint32_t *)(v5 + 196));
              if ( (*(int (/*thiscall*/ **)(int *))(*v6 + 736))(v6) != v7 )
              {
                v8 = *v6;
                v9 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*v6 + 740))(v6, 0, 1);
                (*(void (/*thiscall*/ **)(int *, int))(v8 + 732))(v6, v9);
              }
              v10 = (*(int (/*thiscall*/ **)(int *))(*v6 + 756))(v6);
              if ( (*(int (/*thiscall*/ **)(int *))(*v6 + 752))(v6) != v10 )
              {
                v11 = *v6;
                v12 = (*(int (/*thiscall*/ **)(int *, int))(*v6 + 756))(v6, 1);
                (*(void (/*thiscall*/ **)(int *, int))(v11 + 748))(v6, v12);
              }
            }
          }
        }
        v1 = v56;
      }
      break;
    case 2:
      sub_4BF300(dword_8F8558, 0, 0);
      if ( sub_699000((int)(v1 + 10)) >= 4640 )
      {
        v13 = sub_699000((int)(v1 + 10));
        sub_453050(3, v13 - 4640);
        *((uint32_t *)dword_8F8528 + 621) = 0;
      }
      break;
    case 3:
      if ( 180000 - sub_699000((int)(v1 + 10)) <= 0 )
        v14 = 0;
      else
        v14 = 180000 - sub_699000((int)(v1 + 10));
      v15 = *((uint8_t *)v1 + 112);
      v1[29] = v14;
      if ( v15 == 0 && sub_699000((int)(v1 + 10)) >= 180000 )
      {
        sub_452690(v1);
        *((uint8_t *)v1 + 112) = 1;
      }
      break;
    case 4:
      if ( *(uint32_t *)(*((uint32_t *)dword_8F8528 + 610) + 8) == 0 )
      {
        v1[9] = 5;
        *((uint8_t *)v1 + 53) = 0;
        *((uint8_t *)v1 + 54) = 0;
        sub_698F90((int)(v1 + 10), 0, 0);
        if ( dword_8F7C04 == 0 || *(uint8_t *)(dword_8F7C04 + 8052) == 0 )
          sub_424A40((uint32_t *)v1[4], dword_8F7C04);
        sub_4684F0(*((uint32_t *)dword_8F8528 + 4), nullptr);
      }
      break;
    case 1:
      sub_4BF300(dword_8F8558, 0, 0);
      v16 = sub_699000((int)(v1 + 10));
      v17 = (int)(v1 + 10);
      if ( v16 < 1000 )
        goto LABEL_33;
      if ( sub_699000(v17) >= 2000 )
      {
        if ( sub_699000((int)(v1 + 10)) >= 2000 )
        {
          v1[9] = 2;
          *((uint8_t *)v1 + 53) = 0;
          *((uint8_t *)v1 + 54) = 0;
          sub_698F90((int)(v1 + 10), 0, 0);
          if ( dword_8F7C04 == 0 || *(uint8_t *)(dword_8F7C04 + 8052) == 0 )
            sub_424A40((uint32_t *)v1[4], dword_8F7C04);
          sub_4684F0(*((uint32_t *)dword_8F8528 + 4), nullptr);
          v1[29] = 180000;
          sub_445830(1);
        }
      }
      else
      {
        if ( dword_99FEC0 != 0
          && sub_4525B0() == (uint16_t)word_77F804
          && *((uint8_t *)v1 + 54) == 1
          && v1[31] != -1
          && (int)(GetTickCount() - v1[31]) >= 10000 )
        {
          v19 = *(uint16_t *)(sub_429830((uint16_t)word_77F804) + 4);
          v20 = sub_429830((uint16_t)word_77F804);
          if ( *(uint32_t *)(v20 + 40) < 0x10u )
            v21 = v20 + 20;
          else
            v21 = *(uint32_t *)(v20 + 20);
          off_77F3FC(aPvp, v21, v19);
          do
          {
            v22 = sub_48F690((uint32_t *)dword_99FEC0, v2);
            if ( v22 != 0 && *((uint8_t *)v1 + v2 + 128) == 0 )
            {
              sub_48F500(v2, 254);
              v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1216))(dword_8F7C04);
              v24 = *(uint32_t *)(v22 + 40);
              v25 = v23 == v2;
              v26 = *(uint16_t *)(v22 + 4);
              if ( v25 )
              {
                if ( v24 < 0x10 )
                {
                  v50 = v26;
                  v49 = v2;
                  v27 = v22 + 20;
                }
                else
                {
                  v27 = *(uint32_t *)(v22 + 20);
                  v50 = v26;
                  v49 = v2;
                }
                off_77F3FC(aPvp_5, v27, v49, v50);
              }
              else
              {
                if ( v24 < 0x10 )
                  v28 = v22 + 20;
                else
                  v28 = *(uint32_t *)(v22 + 20);
                off_77F3FC(aPvp_0, v28, v2, v26);
              }
            }
            ++v2;
          }
          while ( v2 < 8 );
          sub_452760(8);
          v1[31] = -1;
        }
        if ( v1[7] == 0 )
        {
          v1[31] = GetTickCount();
          sub_699030((int)(v1 + 10));
          v58 = 0;
          if ( operator new(0x208u) != nullptr )
          {
            v29 = sub_52C040(*((uint32_t *)dword_8F8528 + 8));
            v30 = sub_452B60(v29, 0);
          }
          else
          {
            v30 = 0;
          }
          v31 = v1[8];
          v58 = -1;
          v1[7] = v30;
          sub_45FC60(v31);
          sub_4602C0(*(uint32_t *)(v1[7] + 476));
          sub_425460(v1[4]);
          v57 = sub_48F620((uint32_t *)dword_99FEC0);
          v54 = 0;
          v55 = v1 + 20;
          do
          {
            v32 = sub_48F690((uint32_t *)dword_99FEC0, v54);
            v33 = v32;
            if ( v32 != 0 )
            {
              v34 = *(uint8_t **)(v32 + 196);
              (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v34 + 1020))(v34);
              (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)v34 + 1200))(v34, 0);
              sub_45FE80(v56[8], v33, 273, *(uint16_t *)(v33 + 4), (int)v34, 0, 0);
              v35 = *(uint16_t *)(v33 + 4);
              v52 = 10;
              v53 = 250;
              for ( j = 0; j < 8; ++j )
              {
                if ( sub_48F690((uint32_t *)dword_99FEC0, j) != 0 )
                {
                  Block = *(uint16_t *)(sub_48F690((uint32_t *)dword_99FEC0, j) + 4);
                  v37 = sub_48F690((uint32_t *)dword_99FEC0, j);
                  v35 += Block
                       + (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v37 + 196) + 376))(*(uint32_t *)(v37 + 196));
                }
              }
              if ( v34[8052] != 0 )
              {
                (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)v34 + 112))(v34, -10000, -10000, 0);
                *v55 = 100000000;
              }
              else
              {
                if ( v57 )
                  v38 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v34 + 376))(v34) + 1;
                else
                  v38 = 0;
                sub_48C3A0((uint32_t *)v56[7], v38, &v52, &v53, (int)v34, v35);
                (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)v34 + 112))(v34, v52, v53, 0);
                *v55 = 0;
              }
              v39 = *(uint32_t *)(v56[4] + 44);
              v40 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v34 + 120))(v34);
              if ( v40 < sub_425050(v39) / 2 )
                (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)v34 + 148))(v34, 1);
              else
                (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)v34 + 148))(v34, 0);
            }
            v41 = v54;
            sub_48F580(v54, 0);
            v54 = v41 + 1;
            ++v55;
          }
          while ( v41 + 1 < 8 );
          v1 = v56;
          sub_425500(v56[7]);
          sub_48E870(*(uint32_t *)(v1[4] + 44), v1[8]);
          v42 = sub_48F5A0();
          sub_452760(v42);
        }
        v43 = sub_699000((int)(v1 + 10));
        *((uint32_t *)dword_8F8528 + 621) = sub_423A80(255, 0, v43 - 1000, 1000);
      }
      break;
    case 5:
      sub_4BF300(dword_8F8558, 0, 0);
      v44 = sub_699000((int)(v1 + 10));
      v17 = (int)(v1 + 10);
      if ( v44 < 1000 )
      {
LABEL_33:
        v18 = sub_699000(v17);
        *((uint32_t *)dword_8F8528 + 621) = sub_423A80(0, 255, v18, 1000);
        break;
      }
      if ( sub_699000(v17) < 2000 )
      {
        v45 = sub_699000((int)(v1 + 10));
        *((uint32_t *)dword_8F8528 + 621) = sub_423A80(255, 0, v45 - 1000, 1000);
        if ( dword_99FEC0 != 0 && *((uint8_t *)v1 + 120) == 0 )
        {
          sub_423200(dword_8F7B08, 60);
          sub_423380(dword_8F7B08);
          *((uint8_t *)v1 + 120) = 1;
        }
      }
      break;
    default:
      break;
  }
  LOBYTE(v46) = *((uint8_t *)v1 + 136);
  if ( (uint8_t)v46 == 0 )
  {
    *((uint8_t *)v1 + 136) = 1;
    v46 = (uint8_t *)(dword_8F8520 + 1048692);
    for ( k = 8; k != 0; --k )
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
// 0x4539D0 sub_4539D0
// ------------------------------------------------------------
char /*thiscall*/ sub_4539D0(int this)
{
  char result; // al
  int (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  uint32_t *v8; // esi
  int i; // edi

  result = *(uint8_t *)(this + 4);
  if ( result != 0 )
  {
    v3 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 12);
    *(uint8_t *)(this + 4) = 0;
    if ( v3 != nullptr )
      result = (**v3)(v3, 1);
    v4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 16);
    *(uint32_t *)(this + 12) = 0;
    if ( v4 != nullptr )
      result = (**v4)(v4, 1);
    v5 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 20);
    *(uint32_t *)(this + 16) = 0;
    if ( v5 != nullptr )
      result = (**v5)(v5, 1);
    v6 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 24);
    *(uint32_t *)(this + 20) = 0;
    if ( v6 != nullptr )
      result = (**v6)(v6, 1);
    v7 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 28);
    *(uint32_t *)(this + 24) = 0;
    if ( v7 != nullptr )
      result = (**v7)(v7, 1);
    *(uint32_t *)(this + 28) = 0;
    v8 = (uint32_t *)(this + 32);
    for ( i = 2; i != 0; --i )
    {
      if ( *v8 != 0 )
        result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v8)(*v8, 1);
      *v8++ = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x453A60 sub_453A60
// ------------------------------------------------------------
int /*thiscall*/ sub_453A60(int this)
{
  int result; // eax

  result = 0;
  if ( *(uint8_t *)(this + 4) != 0 )
  {
    *(uint8_t *)(this + 53) = 0;
    *(uint8_t *)(this + 54) = 0;
    *(uint8_t *)(this + 180) = 0;
    *(uint32_t *)(this + 288) = -1;
    *(uint32_t *)(this + 292) = -1;
    *(uint32_t *)(this + 220) = -1;
    *(uint32_t *)(this + 224) = 0;
    *(uint32_t *)(this + 228) = 0;
    *(uint32_t *)(this + 232) = 0;
    *(uint8_t *)(this + 236) = 0;
    *(uint32_t *)(this + 296) = -1;
    *(uint8_t *)(this + 148) = 0;
    *(uint32_t *)(this + 212) = -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x453AC0 sub_453AC0
// ------------------------------------------------------------
char /*thiscall*/ sub_453AC0(uint32_t *this, int a2)
{
  int v3; // eax

  v3 = *(this + 17);
  if ( v3 != a2 )
  {
    if ( v3 != 0 )
      LOBYTE(v3) = sub_69A580(*(uint32_t *)(v3 + 36));
    *(this + 17) = a2;
    if ( a2 != 0 )
    {
      sub_69A840(*(uint32_t *)(a2 + 36));
      LOBYTE(v3) = sub_425960(1, *(uint32_t *)(*(this + 17) + 44), *(int ***)(*(this + 17) + 104));
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x453B10 sub_453B10
// ------------------------------------------------------------
int /*thiscall*/ sub_453B10(int this)
{
  *(uint8_t *)(this + 148) = 1;
  *(uint8_t *)(this + 165) = 0;
  *(uint8_t *)(this + 166) = 0;
  sub_432EA0("MAP_DISAPPEAR", -1, 0, 0);
  sub_453AC0((uint32_t *)this, *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16));
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 124))(
    dword_8F8520,
    *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16));
  return sub_424A40(*(uint32_t **)(this + 68), 0);
}



// ------------------------------------------------------------
// 0x453B80 sub_453B80
// ------------------------------------------------------------
int /*thiscall*/ sub_453B80(int this, int a2, int a3, int a4)
{
  int result; // eax

  sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  *(uint32_t *)(this + 224) = a3;
  *(uint32_t *)(this + 220) = a2;
  *(uint32_t *)(this + 228) = a4;
  *(uint32_t *)(this + 232) = 1;
  *(uint32_t *)(this + 300) = a2;
  result = dword_99FB8C;
  *(uint32_t *)(this + 304) = dword_99FB8C;
  *(uint8_t *)(this + 180) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x453BE0 sub_453BE0
// ------------------------------------------------------------
bool /*thiscall*/ sub_453BE0(void *this)
{
  return sub_699000((int)this + 40) > 20300;
}



// ------------------------------------------------------------
// 0x453C00 sub_453C00
// ------------------------------------------------------------
int /*thiscall*/ sub_453C00(uint32_t *this)
{
  int v1; // edx

  v1 = *(this + 1);
  if ( v1 != 0 )
    return (*(this + 2) - v1) >> 4;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x453C20 sub_453C20
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_453C20(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *v4; // edi

  for ( result = a1; result != a2; v4[3] = a3[3] )
  {
    v4 = result;
    *result = *a3;
    result[1] = a3[1];
    result[2] = a3[2];
    result += 4;
  }
  return result;
}



// ------------------------------------------------------------
// 0x453C60 sub_453C60
// ------------------------------------------------------------
char /*thiscall*/ sub_453C60(int this)
{
  int v2; // ecx
  int v4; // eax
  int v5; // eax
  uint64_t v6; // rax
  int v7; // ebx
  int v8; // eax
  uint64_t v9; // rax

  v2 = *(uint32_t *)(sub_476B60(*(uint32_t *)(this + 220)) + 64);
  if ( v2 == 0 )
    return 0;
  (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v2 + 152))(v2, 0, 0, dword_79C0B0);
  v4 = *(uint32_t *)(this + 212);
  switch ( v4 )
  {
    case 0:
      sub_698F90(this + 184, 0, 0);
      v5 = sub_699000(this + 184);
      v6 = (uint64_t)sub_4049C0(255.0, 0.0, v5, 300);
      *((uint32_t *)dword_8F8528 + 621) = v6;
      if ( sub_699000(this + 184) >= 300 )
      {
        *(uint32_t *)(this + 212) = 1;
        *(uint8_t *)(this + 197) = 0;
        *(uint8_t *)(this + 198) = 0;
        sub_698F90(this + 184, 1500, 0);
      }
      return 0;
    case 1:
      v7 = *(uint32_t *)(this + 208);
      if ( sub_699000(this + 184) < v7 )
        return 0;
      *(uint32_t *)(this + 212) = 2;
      *(uint8_t *)(this + 197) = 0;
      *(uint8_t *)(this + 198) = 0;
      return 0;
    case 2:
      sub_698F90(this + 184, 0, 0);
      v8 = sub_699000(this + 184);
      v9 = (uint64_t)sub_4049C0(0.0, 255.0, v8, 300);
      *((uint32_t *)dword_8F8528 + 621) = v9;
      if ( sub_699000(this + 184) < 300 )
        return 0;
      *(uint32_t *)(this + 212) = 3;
      return 1;
    default:
      return 0;
  }
}



// ------------------------------------------------------------
// 0x453DA0 sub_453DA0
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_453DA0(uint32_t *this, char a2)
{
  uint8_t v3[4]; // [esp+4h] [ebp-4h] BYREF

  return *(uint32_t *)sub_472E30(v3, &a2) != *(this + 13);
}



// ------------------------------------------------------------
// 0x453DD0 sub_453DD0
// ------------------------------------------------------------
// 座位/选中槽同步 —— 战斗分发器 case 2/3 落点：
// +276 座位表（16 字节/项）/ +288 当前选中；a2==当前且 +4 槽位吻合则短路返回；
// 换座经 sub_476B60 取角色数据 → 23 字节/项的名字表刷新（sub_69A5F0）→
// +16/+20 按钮可见性 → a3!=4 时回写 +4 槽位并播 CLICK_BUTTON2
char /*thiscall*/ sub_453DD0(int this, unsigned int a2, int a3)
{
  int v3; // eax
  int v5; // ecx
  char v6; // dl
  int v7; // edx
  int v8; // ebx
  int v9; // edi
  bool v10; // al
  int v11; // eax
  int v12; // edi
  int v13; // edi
  int v14; // eax
  int v15; // edi
  int v16; // ecx
  int v17; // eax
  int *v18; // edi
  char v19; // cl
  int v20; // ecx
  uint32_t **v22; // [esp+8h] [ebp-8h]
  int v23; // [esp+8h] [ebp-8h]
  int v24; // [esp+8h] [ebp-8h]
  char v25; // [esp+Fh] [ebp-1h]

  v3 = a2;
  v5 = *(uint32_t *)(this + 288);
  if ( v5 == a2 && (a2 == -1 || *(uint32_t *)(*(uint32_t *)(this + 276) + 16 * a2 + 4) == a3) )
    return v3;
  v6 = 0;
  v25 = 0;
  if ( v5 != a2 )
  {
    if ( a2 != -1 )
    {
      v7 = *(uint32_t *)(this + 276);
      if ( v7 == 0 )
        return v3;
      if ( (*(uint32_t *)(this + 280) - v7) >> 4 <= a2 )
        return v3;
      v3 = sub_476B60(*(uint32_t *)(v7 + 16 * a2));
      v8 = v3;
      if ( v3 == 0 )
        return v3;
      v9 = 0;
      v22 = (uint32_t **)(this + 32);
      do
      {
        sub_69A5F0(*v22, v9 + *(uint32_t *)(v8 + 80) + 61, *(uint32_t *)(v8 + 84) + 65);
        v9 += 23;
        ++v22;
      }
      while ( v9 < 46 );
      v3 = a2;
    }
    *(uint32_t *)(this + 288) = v3;
    v10 = v3 != -1;
    *(uint8_t *)(*(uint32_t *)(this + 32) + 16) = v10;
    *(uint8_t *)(*(uint32_t *)(this + 36) + 16) = v10;
    v6 = 1;
    v25 = 1;
  }
  v11 = *(uint32_t *)(this + 288);
  if ( v11 != -1 && a3 != 4 )
  {
    *(uint32_t *)(16 * v11 + *(uint32_t *)(this + 276) + 4) = a3;
LABEL_17:
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    goto LABEL_18;
  }
  if ( v6 != 0 )
    goto LABEL_17;
LABEL_18:
  v12 = dword_8F850C;
  if ( sub_456480(dword_8F850C) == -1 )
    v13 = 0;
  else
    v13 = *(uint32_t *)(v12 + 4 * sub_456480(v12) + 16);
  if ( v13 == sub_429830((uint16_t)word_77F804) )
  {
    *(uint8_t *)(*(uint32_t *)(this + 32) + 17) = *(uint32_t *)(16 * *(uint32_t *)(this + 288) + *(uint32_t *)(this + 276) + 4) != 0;
    *(uint8_t *)(*(uint32_t *)(this + 36) + 17) = *(uint32_t *)(*(uint32_t *)(this + 276) + 16 * *(uint32_t *)(this + 288) + 4) != *(uint32_t *)(16 * *(uint32_t *)(this + 288) + *(uint32_t *)(this + 276) + 8);
  }
  v14 = *(uint32_t *)(this + 288);
  HIWORD(a2) = 0;
  if ( v14 != -1 )
  {
    v15 = 16 * v14 + *(uint32_t *)(this + 276);
    if ( *(uint32_t *)(v15 + 4) != 0 )
    {
      BYTE2(a2) = 1;
      if ( sub_456390(0) <= *(uint32_t *)(v15 + 4) )
      {
        v16 = *(uint32_t *)(16 * *(uint32_t *)(this + 288) + *(uint32_t *)(this + 276) + 4) + 1;
        HIBYTE(a2) = 1;
        *(uint32_t *)(this + 144) = v16;
      }
    }
  }
  v17 = 0;
  a3 = 0;
  v18 = (int *)(this + 108);
  do
  {
    v19 = *((uint8_t *)&a2 + v17 + 2);
    if ( *(uint8_t *)(this + v17 + 140) != v19 )
    {
      *(uint8_t *)(this + v17 + 140) = v19;
      v23 = *v18;
      if ( v23 < sub_699000((int)(v18 - 6)) )
      {
        v20 = 0;
      }
      else
      {
        v24 = *v18;
        v20 = v24 - sub_699000((int)(v18 - 6));
      }
      *((uint8_t *)v18 - 11) = 0;
      *((uint8_t *)v18 - 10) = 0;
      sub_698F90((int)(v18 - 6), 300, v20);
      v17 = a3;
    }
    ++v17;
    v18 += 7;
    a3 = v17;
  }
  while ( v17 < 2 );
  LOBYTE(v3) = v25;
  if ( v25 != 0 )
  {
    LOBYTE(v3) = *(uint8_t *)(this + 126);
    if ( (uint8_t)v3 != 0 )
    {
      *(uint32_t *)(this + 132) = 300;
    }
    else
    {
      v3 = dword_79D100[*(uint32_t *)(this + 120)];
      *(uint32_t *)(this + 128) = 300 - v3;
    }
  }
  return v3;
}


// ------------------------------------------------------------
// 0x454070 sub_454070
// ------------------------------------------------------------
int /*thiscall*/ sub_454070(int this)
{
  int v2; // esi
  int v3; // esi
  int v5; // ecx
  int v6; // esi
  int v7; // eax
  int v8; // ecx
  BOOL v9; // edx
  LONG v10; // edi
  LONG v11; // eax
  LONG y; // [esp+8h] [ebp-10h]
  LONG x; // [esp+Ch] [ebp-Ch]
  int v14; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  v2 = dword_8F850C;
  if ( sub_456480(dword_8F850C) == -1 )
    v3 = 0;
  else
    v3 = *(uint32_t *)(v2 + 4 * sub_456480(v2) + 16);
  if ( v3 != sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )
    return -1;
  if ( *(uint8_t *)(this + 180) != 0 )
    return -1;
  if ( !sub_43BCB0(*(uint32_t *)(this + 20)) )
    return -1;
  x = pt.x;
  v5 = *(uint32_t *)(this + 276);
  v6 = 0;
  y = pt.y;
  if ( v5 != 0 )
    v14 = (*(uint32_t *)(this + 280) - v5) >> 4;
  else
    v14 = 0;
  if ( v14 <= 0 )
    return -1;
  for ( i = 0; ; i += 16 )
  {
    v7 = sub_476B60(*(uint32_t *)(i + *(uint32_t *)(this + 276)));
    v8 = *(uint32_t *)(this + 288);
    v9 = v6 == v8;
    v10 = *(uint32_t *)(v7 + 8 * v9 + 72);
    v11 = *(uint32_t *)(v7 + 8 * v9 + 76);
    if ( x >= v10 && x < v10 + (v6 != v8 ? 118 : 168) && y >= v11 && y < v11 + (v6 != v8 ? 53 : 63) )
      break;
    if ( ++v6 >= v14 )
      return -1;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x4541B0 sub_4541B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4541B0(int this, int a2, uint32_t *a3, uint32_t *a4, uint32_t *a5, uint32_t *a6)
{
  int v7; // edi
  int v8; // edi
  int v10; // eax

  v7 = dword_8F850C;
  if ( sub_456480(dword_8F850C) == -1 )
    v8 = 0;
  else
    v8 = *(uint32_t *)(v7 + 4 * sub_456480(v7) + 16);
  if ( v8 == sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )
  {
    if ( *(uint8_t *)(this + 180) != 0 )
      return -1;
    if ( sub_43BCB0(*(uint32_t *)(this + 20)) )
    {
      v10 = sub_476B60(*(uint32_t *)(*(uint32_t *)(this + 276) + 16 * a2));
      *a3 = *(uint32_t *)(v10 + 8 * (a2 == *(uint32_t *)(this + 288)) + 72);
      *a4 = *(uint32_t *)(v10 + 8 * (a2 == *(uint32_t *)(this + 288)) + 76);
      *a5 = a2 != *(uint32_t *)(this + 288) ? 118 : 168;
      *a6 = a2 != *(uint32_t *)(this + 288) ? 53 : 63;
    }
  }
  return -1;
}



// ------------------------------------------------------------
// 0x4542A0 sub_4542A0
// ------------------------------------------------------------
char /*thiscall*/ sub_4542A0(uint32_t *this)
{
  int v2; // edi
  int v3; // edi
  int v4; // eax
  bool v5; // cl
  int v6; // eax
  bool v7; // al
  int v8; // eax

  v2 = dword_8F850C;
  if ( sub_456480(dword_8F850C) == -1 )
    v3 = 0;
  else
    v3 = *(uint32_t *)(v2 + 4 * sub_456480(v2) + 16);
  v4 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  v5 = v3 == v4;
  *(uint8_t *)(*(this + 6) + 16) = v3 == v4;
  *(uint8_t *)(*(this + 7) + 16) = v3 == v4;
  *(uint8_t *)(*(this + 7) + 16) = 0;
  v7 = false;
  if ( v3 == v4 )
  {
    v6 = *(this + 72);
    if ( v6 != -1 && *(uint32_t *)(16 * v6 + *(this + 69) + 4) != 0 )
      v7 = true;
  }
  *(uint8_t *)(*(this + 8) + 17) = v7;
  if ( !v5
    || (v8 = *(this + 72)) == -1
    || *(uint32_t *)(16 * v8 + *(this + 69) + 4) == *(uint32_t *)(*(this + 69) + 16 * v8 + 8) )
  {
    *(uint8_t *)(*(this + 9) + 17) = 0;
    return 0;
  }
  else
  {
    *(uint8_t *)(*(this + 9) + 17) = 1;
    return 1;
  }
}



// ------------------------------------------------------------
// 0x454360 sub_454360
// ------------------------------------------------------------
char /*thiscall*/ sub_454360(int this)
{
  char result; // al
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  uint8_t *v5; // eax
  uint8_t *v6; // eax
  uint8_t *v7; // eax
  uint8_t *v8; // eax
  uint8_t *v9; // eax
  uint8_t *v10; // eax
  uint8_t *v11; // eax
  uint8_t *v12; // eax
  uint32_t *v13; // edi
  uint8_t *v14; // eax
  uint8_t *v15; // eax
  int Block; // [esp+8h] [ebp-10h]

  result = *(uint8_t *)(this + 4);
  if ( result == 0 )
  {
    *(uint8_t *)(this + 4) = 1;
    *(uint32_t *)(this + 72) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 76);
    *(uint32_t *)(this + 76) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 80);
    *(uint32_t *)(this + 80) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                               dword_8F84B8,
                               "Interface/SelectDungeonEvent.img");
    v3 = operator new(0x68u);
    if ( v3 != nullptr )
      v4 = sub_426BD0(v3);
    else
      v4 = nullptr;
    *(uint32_t *)(this + 12) = v4;
    v5 = operator new(0x68u);
    if ( v5 != nullptr )
      v6 = sub_426BD0(v5);
    else
      v6 = nullptr;
    *(uint32_t *)(this + 16) = v6;
    sub_69A840(v6);
    sub_69A840(*((uint32_t *)dword_8F8528 + 2));
    v7 = operator new(0x68u);
    if ( v7 != nullptr )
      v8 = sub_426BD0(v7);
    else
      v8 = nullptr;
    *(uint32_t *)(this + 20) = v8;
    *((uint32_t *)v8 + 7) = 640;
    *((uint32_t *)v8 + 8) = 480;
    *(uint32_t *)(*(uint32_t *)(this + 20) + 68) = this + 8;
    v9 = operator new(0x68u);
    if ( v9 != nullptr )
      v10 = sub_426BD0(v9);
    else
      v10 = nullptr;
    *(uint32_t *)(this + 24) = v10;
    *((uint32_t *)v10 + 7) = 202;
    *((uint32_t *)v10 + 8) = 41;
    sub_69A5F0(*(uint32_t **)(this + 24), 417, 371);
    sub_69A840(*(uint32_t *)(this + 24));
    v11 = operator new(0x68u);
    if ( v11 != nullptr )
      v12 = sub_426BD0(v11);
    else
      v12 = nullptr;
    *(uint32_t *)(this + 28) = v12;
    *((uint32_t *)v12 + 7) = 155;
    *((uint32_t *)v12 + 8) = 38;
    sub_69A5F0(*(uint32_t **)(this + 28), 418, 411);
    sub_69A840(*(uint32_t *)(this + 28));
    v13 = (uint32_t *)(this + 32);
    for ( Block = 2; Block != 0; --Block )
    {
      v14 = operator new(0x68u);
      if ( v14 != nullptr )
        v15 = sub_426BD0(v14);
      else
        v15 = nullptr;
      *v13 = v15;
      *((uint32_t *)v15 + 7) = 22;
      *((uint32_t *)v15 + 8) = 14;
      *(uint8_t *)(*v13 + 16) = 0;
      sub_69A840(*v13++);
    }
    sub_69A840(*(uint32_t *)(this + 20));
    sub_69A840(*((uint32_t *)dword_8F8528 + 3));
    sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));
    result = *(uint8_t *)(this + 4);
    if ( result != 0 )
    {
      *(uint8_t *)(this + 53) = 0;
      *(uint8_t *)(this + 54) = 0;
      *(uint8_t *)(this + 180) = 0;
      *(uint32_t *)(this + 288) = -1;
      *(uint32_t *)(this + 292) = -1;
      *(uint32_t *)(this + 220) = -1;
      *(uint32_t *)(this + 224) = 0;
      *(uint32_t *)(this + 228) = 0;
      *(uint32_t *)(this + 232) = 0;
      *(uint8_t *)(this + 236) = 0;
      *(uint32_t *)(this + 296) = -1;
      *(uint8_t *)(this + 148) = 0;
      *(uint32_t *)(this + 212) = -1;
      return 0;
    }
  }
  return result;
}



// ============================================================
// 【分区 4】副本选择界面（0x454610-0x455E20）
// CNSelectDungeonModule__vmt4 = 副本选择帧（MAP_MOUSEOVER/MAP_SELECT）；
// 副本倒计时巨函数 0x454F00（MAP_COUNTDOWN 自证，~780 行）。
// ============================================================
// ------------------------------------------------------------
// 0x454610 sub_454610
// ------------------------------------------------------------
int /*thiscall*/ sub_454610(uint32_t *this, unsigned int a2, int a3)
{
  int result; // eax

  if ( a2 == -1 || *(uint32_t *)((result = *(this + 69) + 16 * a2) + 12) != -1 )
  {
    sub_453DD0((int)this, a2, a3);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 3, 1);
    (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, a2);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, a3);
    return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x454680 sub_454680
// ------------------------------------------------------------
char /*thiscall*/ sub_454680(int this, int a2, int a3)
{
  int v3; // ebx
  int v5; // edx
  unsigned int v6; // ecx
  int v7; // edi
  int v8; // eax

  v3 = a2;
  v5 = *(uint32_t *)(this + 276);
  v6 = 0;
  v7 = 0;
  while ( v5 != 0 && v6 < (*(uint32_t *)(this + 280) - v5) >> 4 )
  {
    if ( *(uint32_t *)(v7 + *(uint32_t *)(this + 276)) == a2 )
    {
      sub_454610((uint32_t *)this, v6, a3);
      break;
    }
    ++v6;
    v7 += 16;
  }
  sub_423200(dword_8F7B08, 16);
  a2 = v3;
  sub_423290(dword_8F7B08, (int)&a2, 2);
  HIBYTE(a3) = a3;
  sub_423290(dword_8F7B08, (int)&a3 + 3, 1);
  sub_423380(dword_8F7B08);
  v8 = *(uint32_t *)(this + 24);
  *(uint8_t *)(this + 180) = 1;
  *(uint8_t *)(v8 + 17) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 28) + 17) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 32) + 17) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 36) + 17) = 0;
  return sub_44E850(dword_8F8528, 55);
}



// ------------------------------------------------------------
// 0x454740 CNSelectDungeonModule__vmt4
// ------------------------------------------------------------
// CNSelectDungeonModule::vmt4 —— 副本选择界面帧（RTTI 自证）：
// 主帧循环 → 选中项命中测试 sub_454070（1100ms 启动门 +180）→
// MAP_MOUSEOVER（悬停变更）/ MAP_SELECT（确认）；悬停信息条 dword_8F8528 vt 55
char /*thiscall*/ sub_454740(int this)
{
  int v2; // ecx
  int v3; // edi
  int v4; // edi
  int v5; // eax
  int v6; // edi
  int *v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // edx
  unsigned int v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int *v16; // eax
  int v17; // eax
  int v18; // eax
  uint64_t v19; // rax
  int v20; // eax
  int v21; // eax
  int v23; // [esp+4h] [ebp-10h] BYREF
  int v24; // [esp+8h] [ebp-Ch] BYREF
  int v25; // [esp+Ch] [ebp-8h] BYREF
  int v26; // [esp+10h] [ebp-4h] BYREF

  sub_433690();
  v2 = *(uint32_t *)(this + 68);
  if ( v2 != 0 )
    sub_4294E0(v2);
  v3 = dword_8F850C;
  if ( sub_456480(dword_8F850C) == -1 )
    v4 = 0;
  else
    v4 = *(uint32_t *)(v3 + 4 * sub_456480(v3) + 16);
  if ( v4 == sub_429830((uint16_t)word_77F804) && *(uint8_t *)(this + 180) == 0 && sub_699000(this + 40) >= 1100 )
  {
    v5 = sub_454070(this);
    v6 = v5;
    if ( v5 != *(uint32_t *)(this + 292) )
    {
      if ( v5 != -1 && v5 != *(uint32_t *)(this + 288) )
        sub_432EA0("MOUSE_OVER", -1, 0, 0);
      *(uint32_t *)(this + 292) = v6;
      if ( v6 == -1 || *(uint8_t *)(this + 180) != 0 )
      {
        sub_44E850(dword_8F8528, 55);
      }
      else
      {
        v7 = (int *)(*(uint32_t *)(this + 276) + 16 * v6);
        if ( *v7 != dword_795314 )
        {
          v8 = sub_44E8D0((char *)dword_8F8528, (void *)0x37, 0, *v7);
          if ( v8 != 0 )
          {
            v23 = 0;
            v24 = 0;
            v25 = 0;
            v26 = 0;
            sub_4541B0(v6, &v23, &v24, &v25, &v26);
            (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v8 + 48))(v8, v23, v24, v25, v26);
          }
        }
      }
    }
    v9 = *(uint32_t *)(this + 20);
    if ( *(uint8_t *)(v9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v9 + 12) && v6 != -1 )
    {
      if ( v6 == *(uint32_t *)(this + 288) )
        goto LABEL_27;
      sub_454610(v6, 4);
      sub_432EA0("MAP_MOUSEOVER", -1, 0, 0);
    }
    v10 = *(uint32_t *)(this + 24);
    if ( (*(uint8_t *)(v10 + 17) == 0 || dword_79BE34 != *(uint32_t *)(v10 + 12)) && (uint8_t)sub_453BE0(this) == 0 )
    {
LABEL_33:
      v13 = *(uint32_t *)(this + 32);
      if ( *(uint8_t *)(v13 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v13 + 12) )
        sub_454610(*(uint32_t *)(this + 288), *(uint32_t *)(*(uint32_t *)(this + 276) + 16 * *(uint32_t *)(this + 288) + 4) - 1);
      v14 = *(uint32_t *)(this + 36);
      if ( *(uint8_t *)(v14 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v14 + 12) )
        sub_454610(*(uint32_t *)(this + 288), *(uint32_t *)(*(uint32_t *)(this + 276) + 16 * *(uint32_t *)(this + 288) + 4) + 1);
      goto LABEL_39;
    }
LABEL_27:
    v11 = *(uint32_t *)(this + 276);
    if ( v11 != 0 && (*(uint32_t *)(this + 280) - v11) >> 4 != 0 )
    {
      v12 = *(uint32_t *)(this + 288);
      if ( v12 == -1 || v12 >= sub_453C00(this + 272) )
        v12 = 0;
      sub_454680(*(uint32_t *)(*(uint32_t *)(this + 276) + 16 * v12), *(uint32_t *)(*(uint32_t *)(this + 276) + 16 * v12 + 4));
      sub_432EA0("MAP_SELECT", -1, 0, 0);
    }
    goto LABEL_33;
  }
LABEL_39:
  v15 = *(uint32_t *)(this + 232);
  if ( v15 == 1 )
  {
    *(uint32_t *)(this + 232) = 2;
  }
  else if ( v15 == 2 && *(uint32_t *)(this + 212) == -1 )
  {
    v16 = (int *)sub_476B60(*(uint32_t *)(this + 220));
    sub_475810(v16, this, *(uint32_t *)(this + 224), *(uint32_t *)(this + 228));
    sub_4284C0(*(uint32_t *)(this + 224), *(uint32_t *)(this + 228));
    *(uint8_t *)(this + 236) = 1;
    *(uint8_t *)(this + 253) = 0;
    *(uint8_t *)(this + 254) = 0;
    sub_698F90(this + 240, 0, 0);
    *(uint32_t *)(this + 212) = 0;
  }
  if ( *(uint8_t *)(this + 148) != 0 )
  {
    v17 = *(uint32_t *)(this + 232);
    if ( v17 == 2 )
    {
      sub_698F90(this + 152, 0, 0);
      v18 = sub_699000(this + 152);
      v19 = (uint64_t)sub_4049C0(0.0, 255.0, v18, 300);
      *((uint32_t *)dword_8F8528 + 621) = v19;
      if ( sub_699000(this + 152) >= 300 )
      {
        *(uint32_t *)(this + 232) = 3;
        v20 = *(uint32_t *)(dword_8F7A24 + 20);
        if ( *(uint32_t *)(v20 + 216) == 0 )
          *(uint32_t *)(v20 + 216) = -1;
      }
    }
    else if ( (v17 == 3 || v17 == 4) && v17 == 4 )
    {
      sub_41D300(3);
      *(uint8_t *)(this + 148) = 0;
      *(uint8_t *)(this + 197) = 0;
      *(uint8_t *)(this + 198) = 0;
      *(uint32_t *)(this + 212) = -1;
      *(uint8_t *)(this + 216) = 1;
    }
  }
  LOBYTE(v21) = *(uint8_t *)(this + 236);
  if ( (uint8_t)v21 != 0 )
  {
    v21 = sub_699000(this + 240);
    if ( v21 >= 1000 )
    {
      sub_423200(dword_8F7B08, 40);
      LOBYTE(v21) = sub_423380(dword_8F7B08);
      *(uint8_t *)(this + 236) = 0;
    }
  }
  return v21;
}


// ------------------------------------------------------------
// 0x454B50 sub_454B50
// ------------------------------------------------------------
void /*noreturn*/ sub_454B50()
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
// 0x454BC0 sub_454BC0
// ------------------------------------------------------------
void /*thiscall*/ sub_454BC0(int this)
{
  if ( *(uint8_t *)(this + 4) == 0 )
  {
    *(uint32_t *)(this + 12) = 0;
    *(uint32_t *)(this + 16) = 0;
    *(uint32_t *)(this + 20) = 0;
    *(uint32_t *)(this + 24) = 0;
    *(uint32_t *)(this + 28) = 0;
    *(uint32_t *)(this + 32) = 0;
    *(uint32_t *)(this + 36) = 0;
    *(uint32_t *)(this + 68) = 0;
    *(uint8_t *)(this + 148) = 0;
    *(uint8_t *)(this + 180) = 0;
    *(uint8_t *)(this + 197) = 0;
    *(uint8_t *)(this + 198) = 0;
    *(uint32_t *)(this + 212) = -1;
    *(uint8_t *)(this + 216) = 1;
    *(uint32_t *)(this + 72) = 0;
    *(uint32_t *)(this + 76) = 0;
    *(uint32_t *)(this + 80) = 0;
    *(uint16_t *)(this + 140) = 0;
    *(uint32_t *)(this + 144) = 0;
    *(uint32_t *)(this + 220) = -1;
    *(uint32_t *)(this + 224) = 0;
    *(uint32_t *)(this + 228) = 0;
    *(uint32_t *)(this + 232) = 0;
    *(uint8_t *)(this + 236) = 0;
    *(uint32_t *)(this + 268) = 0;
    if ( *(uint32_t *)(this + 276) != 0 )
      j__free(*(void **)(this + 276));
    *(uint32_t *)(this + 276) = 0;
    *(uint32_t *)(this + 280) = 0;
    *(uint32_t *)(this + 284) = 0;
    *(uint32_t *)(this + 288) = -1;
    *(uint32_t *)(this + 292) = -1;
    *(uint32_t *)(this + 300) = -1;
    *(uint32_t *)(this + 296) = 0;
    *(uint32_t *)(this + 304) = 0;
  }
}



// ------------------------------------------------------------
// 0x454CA0 sub_454CA0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_454CA0(int this, int a2, unsigned int a3, uint32_t *Block)
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
  uint32_t *v15; // ebx
  int v16; // ecx
  int v17; // eax
  unsigned int v18; // edi
  void *v19; // eax
  int v20; // edi
  int v21; // edi
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
      sub_41D5A0(this);
    if ( v7 != 0 )
      v11 = (*(uint32_t *)(this + 8) - v7) >> 4;
    else
      v11 = 0;
    if ( result >= a3 + v11 )
    {
      v19 = *(void **)(this + 8);
      Blockb = v19;
      if ( ((int)v19 - a2) >> 4 >= a3 )
      {
        v21 = (int)v19 - 16 * a3;
        *(uint32_t *)(this + 8) = sub_602460(v21, v19, v19);
        sub_4BF320(a2, v21, (int)Blockb);
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
      v15 = (uint32_t *)sub_602460(v22, a2, Blocka);
      sub_4BF340(v15, (uint32_t *)a3, v26);
      sub_602460(a2, *(uint32_t *)(this + 8), &v15[4 * a3]);
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
// 0x454F00 sub_454F00
// ------------------------------------------------------------
// ★ 巨型（~780 行）副本倒计时处理 —— MAP_COUNTDOWN 自证（4558 行附近）：
// 全员就绪轮询 → 倒计时推进 → 入场转移【推断】
char /*thiscall*/ sub_454F00(int this)
{
  unsigned int v2; // eax
  int v3; // edi
  double v4; // st7
  int v5; // ebx
  int v6; // ecx
  int v7; // ecx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // edi
  int v16; // ecx
  int v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // esi
  int v21; // esi
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  bool v29; // cc
  int v30; // eax
  int v31; // edi
  int v32; // esi
  int v33; // eax
  int v34; // ecx
  int v35; // eax
  int v36; // eax
  uint32_t *v37; // eax
  int v38; // eax
  uint32_t *v39; // eax
  int v40; // eax
  uint32_t *v41; // eax
  int v42; // eax
  uint32_t *v43; // eax
  int v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // ecx
  int v52; // esi
  int v53; // edi
  int v54; // eax
  int v55; // eax
  int v56; // edx
  int v57; // eax
  signed int Time; // eax
  int v59; // ecx
  int v60; // ecx
  int v61; // edi
  int v62; // esi
  int v63; // eax
  int v64; // ebx
  int v65; // eax
  int v66; // ecx
  uint32_t *v67; // edi
  unsigned int i; // esi
  int v69; // edx
  float v71; // [esp+2ACh] [ebp-38h]
  int v72; // [esp+2B0h] [ebp-34h]
  int v73; // [esp+2B0h] [ebp-34h]
  int v74; // [esp+2B0h] [ebp-34h]
  int v75; // [esp+2B0h] [ebp-34h]
  float v76; // [esp+2B0h] [ebp-34h]
  int v77; // [esp+2C8h] [ebp-1Ch]
  int v78; // [esp+2C8h] [ebp-1Ch]
  int v79; // [esp+2C8h] [ebp-1Ch]
  int v80; // [esp+2CCh] [ebp-18h]
  int v81; // [esp+2D0h] [ebp-14h]
  int v82; // [esp+2D0h] [ebp-14h]
  int v83; // [esp+2D4h] [ebp-10h]
  int v84; // [esp+2D4h] [ebp-10h]
  int v85; // [esp+2D4h] [ebp-10h]
  int v86; // [esp+2D4h] [ebp-10h]
  int v87; // [esp+2D8h] [ebp-Ch]
  int v88; // [esp+2D8h] [ebp-Ch]
  int v89; // [esp+2D8h] [ebp-Ch]
  int v90; // [esp+2DCh] [ebp-8h]
  int v91; // [esp+2DCh] [ebp-8h]
  int *v92; // [esp+2DCh] [ebp-8h]

  LOBYTE(v2) = *(uint8_t *)(this + 216);
  if ( (uint8_t)v2 == 0 )
    return v2;
  sub_698F90(this + 40, 0, 0);
  v3 = sub_699000(this + 40);
  v81 = (uint64_t)sub_4049C0(0.0, 255.0, v3, 300);
  v4 = sub_4049C0(0.0, 255.0, v3 - 1100, 300);
  v5 = (uint64_t)v4;
  if ( v3 >= 1100 )
    v83 = 255 - v5;
  else
    v83 = v81;
  v6 = *(uint32_t *)(this + 268);
  if ( v6 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
      v6,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)v81 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  LOBYTE(v2) = v83;
  if ( v83 != 0 )
  {
    v2 = sub_418DD0(16);
    if ( v2 != 0 )
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(unsigned int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v2 + 128))(
                     v2,
                     0,
                     0,
                     dword_79C0B0,
                     1065353216,
                     1065353216,
                     0,
                     ((uint8_t)v83 << 24) | 0xFFFFFF,
                     1333788672,
                     1333788672);
  }
  if ( v5 == 0 )
    return v2;
  v7 = *(uint32_t *)(this + 24);
  if ( *(uint8_t *)(v7 + 16) != 0 )
  {
    v8 = *(uint32_t *)(v7 + 20);
    v84 = *(uint32_t *)(v7 + 24);
    if ( (uint8_t)sub_43BCB0() != 0 )
    {
      sub_491530(2, 0);
      v9 = sub_418DD0(19);
      if ( v9 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 128))(
          v9,
          v8,
          v84,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_491630(2);
      v10 = sub_418DD0(18);
    }
    else
    {
      v10 = sub_418DD0(17);
    }
    if ( v10 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 128))(
        v10,
        v8,
        v84,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)v5 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
  }
  v11 = *(uint32_t *)(this + 28);
  if ( *(uint8_t *)(v11 + 16) != 0 )
  {
    v12 = *(uint32_t *)(v11 + 20);
    v85 = *(uint32_t *)(v11 + 24);
    if ( (uint8_t)sub_43BCB0() != 0 )
    {
      sub_491530(2, 0);
      v13 = sub_418DD0(22);
      if ( v13 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
          v13,
          v12,
          v85,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_491630(2);
      v14 = sub_418DD0(21);
    }
    else
    {
      v14 = sub_418DD0(20);
    }
    if ( v14 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
        v14,
        v12,
        v85,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)v5 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
  }
  v15 = *(uint32_t *)(this + 108);
  v16 = this + 84;
  if ( *(uint8_t *)(this + 140) != 0 )
  {
    v72 = sub_699000(v16);
    sub_4049F0(640.0, 376.0, v72, v15, 1);
  }
  else
  {
    v73 = sub_699000(v16);
    sub_4049F0(376.0, 640.0, v73, v15, 0);
  }
  v17 = (uint64_t)v4;
  if ( v17 != 640 )
  {
    v18 = sub_418DD0(8);
    if ( v18 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v18 + 128))(
        v18,
        v17,
        30,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)v5 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
  }
  v77 = sub_454070(this);
  v19 = *(uint32_t *)(this + 276);
  if ( v19 != 0 )
    v20 = (*(uint32_t *)(this + 280) - v19) >> 4;
  else
    v20 = 0;
  v86 = v20;
  v87 = 0;
  if ( v20 > 0 )
  {
    v90 = 0;
    do
    {
      if ( v87 != *(uint32_t *)(this + 288) )
      {
        v21 = sub_476B60(*(uint32_t *)(*(uint32_t *)(this + 276) + v90));
        if ( *(uint32_t *)(*(uint32_t *)(this + 276) + v90 + 12) == -1 )
        {
          v22 = sub_418DD0(4);
          if ( v22 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v22 + 128))(
              v22,
              0,
              0,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              ((uint8_t)(2 * v5 / 3) << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          if ( *(uint8_t *)(v21 + 464) == 1 )
          {
            v23 = sub_418DD0(11);
            if ( v23 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v23 + 128))(
                v23,
                *(uint32_t *)(v21 + 72) - 7,
                *(uint32_t *)(v21 + 76) - 16,
                dword_79C0B0,
                1065353216,
                1065353216,
                0,
                ((uint8_t)(2 * v5 / 3) << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
          }
          else
          {
            v24 = sub_418DD0(7);
            if ( v24 != 0 )
              (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v24 + 128))(
                v24,
                *(uint32_t *)(v21 + 72),
                *(uint32_t *)(v21 + 76) - 9,
                dword_79C0B0,
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
            sub_491530(2, 0);
            v25 = sub_418DD0(3);
            if ( v25 != 0 )
              (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v25 + 128))(
                v25,
                0,
                0,
                dword_79C0B0,
                1065353216,
                1065353216,
                0,
                ((uint8_t)v5 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
            sub_491630(2);
          }
          v26 = sub_418DD0(2);
          if ( v26 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v26 + 128))(
              v26,
              0,
              0,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              ((uint8_t)v5 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          if ( *(uint8_t *)(v21 + 464) == 1 )
          {
            v27 = sub_418DD0(11);
            if ( v27 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v27 + 128))(
                v27,
                *(uint32_t *)(v21 + 72) - 7,
                *(uint32_t *)(v21 + 76) - 16,
                dword_79C0B0,
                1065353216,
                1065353216,
                0,
                ((uint8_t)v5 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
          }
          else
          {
            v28 = sub_418DD0(6);
            if ( v28 != 0 )
              (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v28 + 128))(
                v28,
                *(uint32_t *)(v21 + 72),
                *(uint32_t *)(v21 + 76) - 9,
                dword_79C0B0,
                1065353216,
                1065353216,
                0,
                ((uint8_t)v5 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
          }
        }
      }
      v29 = ++v87 < v86;
      v90 += 16;
    }
    while ( v29 );
  }
  v30 = *(uint32_t *)(this + 288);
  if ( v30 != -1 )
  {
    v31 = sub_476B60(*(uint32_t *)(*(uint32_t *)(this + 276) + 16 * v30));
    v32 = *(uint32_t *)(v31 + 84);
    v88 = *(uint32_t *)(v31 + 80);
    sub_491530(2, 0);
    v33 = sub_418DD0(1);
    if ( v33 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v33 + 128))(
        v33,
        0,
        0,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)v5 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491630(2);
    v78 = *(uint32_t *)(this + 136);
    v34 = this + 112;
    if ( *(uint8_t *)(this + 141) != 0 )
    {
      v74 = sub_699000(v34);
      sub_4049F0(-12.0, -39.0, v74, v78, 1);
    }
    else
    {
      v75 = sub_699000(v34);
      sub_4049F0(-39.0, -12.0, v75, v78, 0);
    }
    v91 = (uint64_t)v4;
    if ( v91 == -12 )
    {
      v49 = sub_418DD0(0);
      if ( v49 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v49 + 128))(
          v49,
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
    else
    {
      v35 = sub_418DD0(5);
      if ( v35 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v35 + 128))(
          v35,
          v88,
          v32 + v91,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v36 = sub_418DD0(*(uint32_t *)(this + 144));
      if ( v36 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v36 + 128))(
          v36,
          v88,
          v32 + v91,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v37 = (uint32_t *)dword_79C0B0;
      *(uint32_t *)(dword_79C0B0 + 48) = 0;
      v37[13] = 0;
      v37[14] = 640;
      v37[15] = v91 + v32 + 12;
      v38 = sub_418DD0(0);
      if ( v38 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v38 + 128))(
          v38,
          0,
          0,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v39 = (uint32_t *)dword_79C0B0;
      *(uint32_t *)(dword_79C0B0 + 48) = 0;
      v39[13] = v32;
      v39[14] = 640;
      v39[15] = 480;
      v40 = sub_418DD0(0);
      if ( v40 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v40 + 128))(
          v40,
          0,
          0,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v41 = (uint32_t *)dword_79C0B0;
      *(uint32_t *)(dword_79C0B0 + 52) = v91 + v32 + 12;
      v41[12] = 0;
      v41[14] = v88;
      v41[15] = v32;
      v42 = sub_418DD0(0);
      if ( v42 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v42 + 128))(
          v42,
          0,
          0,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v43 = (uint32_t *)dword_79C0B0;
      *(uint32_t *)(dword_79C0B0 + 48) = v88 + 168;
      v43[13] = v91 + v32 + 12;
      v43[14] = 640;
      v43[15] = v32;
      v44 = sub_418DD0(0);
      if ( v44 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v44 + 128))(
          v44,
          0,
          0,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_488670(dword_79C0B0);
    }
    v45 = 16 * *(uint32_t *)(this + 288) + *(uint32_t *)(this + 276);
    if ( *(uint32_t *)(v45 + 4) != 0 )
    {
      v46 = sub_418DD0(*(uint32_t *)(v45 + 4) + 4);
      if ( v46 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v46 + 128))(
          v46,
          v88,
          v32,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
    }
    if ( *(uint8_t *)(v31 + 464) == 1 )
    {
      v47 = sub_418DD0(9);
      if ( v47 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v47 + 128))(
          v47,
          v88 - 9,
          v91 + v32 - 12,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v48 = sub_418DD0(10);
      if ( v48 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v48 + 128))(
          v48,
          v88 - 5,
          v32 + 59,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
    }
    else
    {
      v50 = sub_418DD0(0);
      if ( v50 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v50 + 128))(
          v50,
          v88,
          v32 + v91,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
    }
    v82 = 0;
    v89 = 11;
    v92 = (int *)(this + 32);
    do
    {
      v51 = *v92;
      if ( *(uint8_t *)(*v92 + 16) != 0 )
      {
        v52 = *(uint32_t *)(v51 + 20);
        v53 = *(uint32_t *)(v51 + 24);
        if ( (uint8_t)sub_69A4D0(v51) != 0 )
        {
          v54 = sub_418DD0(v89 + 1);
        }
        else
        {
          v55 = *v92;
          if ( *(uint8_t *)(*v92 + 17) != 0
            && (dword_79BE3C == *(uint32_t *)(v55 + 12)
             || dword_79BE34 == *(uint32_t *)(v55 + 12)
             || dword_79BE38 == *(uint32_t *)(v55 + 12)) )
          {
            v56 = v89;
          }
          else
          {
            if ( *(uint8_t *)(v55 + 17) != 0 )
            {
              v57 = sub_418DD0(v89 - 1);
              if ( v57 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v57 + 128))(
                  v57,
                  v52,
                  v53,
                  dword_79C0B0,
                  1065353216,
                  1065353216,
                  0,
                  ((uint8_t)v5 << 24) | 0xFFFFFF,
                  1333788672,
                  1333788672);
              Time = timeGetTime();
              v76 = (float)v5;
              v79 = (uint64_t)sub_4049C0(0.0, v76, abs32(300 - Time % 600), 300);
              v54 = sub_418DD0(v89);
              if ( v54 == 0 )
                goto LABEL_110;
              v59 = (uint8_t)v79;
              goto LABEL_109;
            }
            v56 = v82 + 23;
          }
          v54 = sub_418DD0(v56);
        }
        if ( v54 != 0 )
        {
          v59 = (uint8_t)v5;
LABEL_109:
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v54 + 128))(
            v54,
            v52,
            v53,
            dword_79C0B0,
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
      ++v82;
      ++v92;
      v89 += 3;
    }
    while ( v29 );
  }
  if ( *(uint8_t *)(this + 180) == 0 )
  {
    if ( 20300 - sub_699000(this + 40) <= 0 )
    {
      v60 = 0;
      goto LABEL_114;
    }
    v60 = 20300 - sub_699000(this + 40);
    if ( v60 < 10000 )
    {
LABEL_114:
      v61 = v60 % 1000;
      v62 = v60 / 1000;
      if ( *(uint32_t *)(this + 296) != v60 / 1000 )
      {
        *(uint32_t *)(this + 296) = v62;
        sub_432EA0("MAP_COUNTDOWN", -1, 0, 0);
      }
      v63 = sub_418DD0(v62);
      if ( v63 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v63 + 128))(
          v63,
          0,
          0,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          ((uint8_t)v5 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      v71 = (float)v5;
      v64 = (uint64_t)sub_4049C0(v71, 0.0, 999 - v61, 250);
      if ( v64 != 0 )
      {
        sub_491530(5, -1);
        v65 = sub_418DD0(v62);
        if ( v65 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v65 + 128))(
            v65,
            0,
            0,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)v64 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        sub_491630(5);
      }
    }
  }
  v2 = sub_568A70((uint8_t)byte_99FCD0, (uint8_t)byte_99FCD1);
  if ( v2 != 0 )
  {
    v66 = *(uint32_t *)(v2 + 88);
    if ( v66 != 0 )
    {
      LOBYTE(v2) = v86;
      v80 = 0;
      if ( v86 > 0 )
      {
        v67 = *(uint32_t **)(this + 276);
        do
        {
          for ( i = 0; ; ++i )
          {
            v69 = *(uint32_t *)(v66 + 4);
            if ( v69 == 0 || i >= (*(uint32_t *)(v66 + 8) - v69) >> 2 )
              break;
            v2 = (*(uint32_t *)(v66 + 8) - v69) >> 2;
            if ( v2 <= i )
              sub_454B50();
            if ( *v67 == *(uint32_t *)(v69 + 4 * i) )
              goto LABEL_134;
          }
          LOBYTE(v2) = v80 + 1;
          v67 += 4;
          ++v80;
        }
        while ( v80 < v86 );
      }
    }
  }
LABEL_134:
  if ( *(uint32_t *)(this + 232) == 3 )
  {
    LOBYTE(v2) = sub_453C60(this);
    if ( (uint8_t)v2 == 1 )
    {
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B0 + 28))(dword_79C0B0, 0);
      *(uint8_t *)(this + 216) = 0;
      *(uint32_t *)(this + 232) = 4;
    }
  }
  return v2;
}


// ============================================================
// 【分区 5】地图创建与队伍分组登记（0x455E20-0x456690）
// 队伍分组登记 0x455EB0（分发器 case 2 循环体落点）；
// 世界地图创建 0x456210（"CRITICAL ERROR : WORLD MAP LOAD FAIL %d" 自证）；
// 座位查询族 0x456390/0x456420/0x456480（docs/13 §3 进图 2 座位分配）。
// ============================================================
// ------------------------------------------------------------
// 0x455E20 sub_455E20
// ------------------------------------------------------------
char /*thiscall*/ sub_455E20(uint32_t *this, int a2)
{
  char result; // al

  result = a2;
  if ( a2 == *(this + 3) )
    return sub_454F00((int)(this - 2));
  return result;
}



// ------------------------------------------------------------
// 0x455E40 sub_455E40
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_455E40(int this, uint32_t *Block)
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
    return sub_454CA0(this, *(char **)(this + 8), 1u, Block);
  v5 = *(uint32_t *)(this + 8);
  result = sub_4BF340(v5, 1, Block);
  *(uint32_t *)(this + 8) = v5 + 16;
  return result;
}



// ------------------------------------------------------------
// 0x455EB0 sub_455EB0
// ------------------------------------------------------------
// 队伍分组登记 —— 分发器 case 2 循环体落点：
// sub_476B60(角色) +92 队伍规模 → 与本地座位(sub_456480→+16)规模比较定分组级
// （0/1/2，-1=不可比）→ 本地座位补 sub_472F90 → Block{id,0,数据,等级} →
// sub_455E40 入 +272 表
unsigned int /*thiscall*/ sub_455EB0(void *this, int a2)
{
  int v2; // esi
  int v3; // edi
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // edi
  int v10; // edi
  uint32_t Block[4]; // [esp+Ch] [ebp-14h] BYREF
  void *v13; // [esp+1Ch] [ebp-4h]

  v13 = this;
  v2 = *(uint32_t *)(sub_476B60(a2) + 92);
  if ( v2 <= 1
    || ((v3 = dword_8F850C, sub_456480(dword_8F850C) != -1)
      ? (v4 = *(uint32_t *)(v3 + 4 * sub_456480(v3) + 16))
      : (v4 = 0),
        sub_41A5E0(v4 + 53) >= v2) )
  {
    v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    v7 = sub_41A5E0(v6 + 53) - v2;
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
  v9 = dword_8F850C;
  if ( sub_456480(dword_8F850C) == -1 )
    v10 = 0;
  else
    v10 = *(uint32_t *)(v9 + 4 * sub_456480(v9) + 16);
  if ( v10 == sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )
    v8 = sub_472F90(a2);
  Block[0] = a2;
  Block[1] = 0;
  Block[2] = v8;
  Block[3] = v5;
  return sub_455E40((int)v13 + 272, Block);
}



// ------------------------------------------------------------
// 0x455FC0 sub_455FC0
// ------------------------------------------------------------
void /*userpurge*/ sub_455FC0(int a1@<ecx>, int a2@<ebx>, int a3@<edi>, int a4)
{
  int v4; // esi
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
  int v22; // [esp+14h] [ebp-18h]
  int v23; // [esp+18h] [ebp-14h] BYREF
  uint32_t v24[4]; // [esp+1Ch] [ebp-10h] BYREF
  int v25; // [esp+34h] [ebp+8h]

  v22 = a1;
  v4 = dword_8F850C;
  if ( sub_456480(dword_8F850C) == -1 )
    v5 = 0;
  else
    v5 = *(uint32_t *)(v4 + 4 * sub_456480(v4) + 16);
  if ( v5 == sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )
  {
    v6 = nullptr;
    if ( a4 != 0 )
    {
      v7 = nullptr;
      v19 = nullptr;
      v20 = nullptr;
      v21 = 0;
      v8 = *(int **)(a4 + 68);
      v9 = v8 == *(int **)(a4 + 72);
      v24[3] = 0;
      if ( !v9 )
      {
        do
        {
          v24[0] = v8[1];
          if ( v24[0] == -1
            || (uint8_t)sub_47C080(v24[0]) != 0
            || *(uint32_t *)sub_472E30(&v23, v24) != *(uint32_t *)(dword_8F8540 + 52)
            || (uint8_t)sub_41C290(dword_8F7A24) != 0 )
          {
            if ( v6 != nullptr && v7 - v6 < (unsigned int)((v21 - (int)v6) >> 2) )
            {
              *v7++ = *v8;
              v20 = v7;
            }
            else
            {
              sub_430C80((int)v18, (int)v7, 1u, v8);
              v7 = v20;
              v6 = v19;
            }
          }
          v8 += 2;
        }
        while ( v8 != *(int **)(a4 + 72) );
      }
      v10 = 0;
      v25 = -1;
      v24[0] = 0;
      while ( v6 != nullptr && v10 < v7 - v6 )
      {
        v11 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
        v23 = sub_41A5E0(v11 + 53);
        v12 = sub_476B60(v6[v10]);
        if ( v23 >= *(uint32_t *)(v12 + 92) )
        {
          if ( v6[v10] == *(uint32_t *)(v22 + 300) )
          {
            v25 = v10;
            v13 = *(uint32_t *)(v22 + 304);
            if ( sub_472F90(*(uint32_t *)(v22 + 300)) >= v13 )
              v24[0] = v13;
            break;
          }
          if ( v25 == -1 )
            v25 = v10;
        }
        ++v10;
      }
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 2, 2, a3, a2);
      if ( v6 != nullptr )
        v14 = v7 - v6;
      else
        v14 = 0;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v14);
      for ( i = v6; i != v7; ++i )
        (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 36))(*(uint16_t *)i);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v25);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v24[0]);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
      if ( v6 != nullptr )
        j__free(v6);
    }
  }
}



// ------------------------------------------------------------
// 0x456210 sub_456210
// ------------------------------------------------------------
// 世界地图创建 —— "CRITICAL ERROR : WORLD MAP LOAD FAIL %d" 自证：
// sub_4CE8A0 取地图数据 → 图像名 → dword_8F84B8 vt+60 载入 → sub_418DD0 建层
// → sub_455FC0/sub_4542A0 构建节点 → +6/+7 按钮激活 → 2×300ms 定时器（+140 位表）
char /*thiscall*/ sub_456210(uint32_t *this, int ArgList)
{
  uint32_t *v3; // eax
  uint32_t *v4; // edi
  char result; // al
  int v6; // ebx
  int v7; // edi
  int v8; // ebx
  int v9; // [esp-4h] [ebp-10h]

  v3 = (uint32_t *)sub_4CE8A0(ArgList);
  v4 = v3;
  if ( v3 == nullptr )
    return off_77F3FC("CRITICAL ERROR : WORLD MAP LOAD FAIL %d", ArgList);
  v6 = (int)(v3 + 8);
  if ( sub_40BF00((std::_String_base *)(v3 + 8), 0, v3[13], szPassword, 0) != 0 )
  {
    if ( v4[14] < 0x10u )
      v6 = (int)(v4 + 9);
    else
      v6 = v4[9];
    v9 = v4[15];
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v6);
    *(this + 67) = sub_418DD0(v9);
  }
  else
  {
    *(this + 67) = 0;
  }
  sub_455FC0((int)this, v6, (int)v4, (int)v4);
  sub_4542A0(this);
  *(uint8_t *)(*(this + 6) + 17) = 1;
  *(uint8_t *)(*(this + 7) + 17) = 1;
  v7 = 0;
  v8 = (int)(this + 21);
  do
  {
    *((uint8_t *)this + v7 + 140) = 0;
    result = sub_698F90(v8, 300, 300);
    ++v7;
    v8 += 28;
  }
  while ( v7 < 2 );
  return result;
}



// ------------------------------------------------------------
// 0x4562E0 sub_4562E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4562E0(uint32_t *this)
{
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x456300 sub_456300
// ------------------------------------------------------------
int /*thiscall*/ sub_456300(uint32_t *this, int a2, int a3)
{
  int result; // eax

  result = *(this + a2 + 4);
  if ( result != a3 )
  {
    if ( result != 0 )
      *(uint8_t *)(result + 188) = 0;
    if ( a3 != 0 )
      *(uint8_t *)(a3 + 188) = 1;
    *(this + a2 + 4) = a3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x456340 sub_456340
// ------------------------------------------------------------
int /*thiscall*/ sub_456340(uint32_t *this, int a2, int a3)
{
  int result; // eax
  int v5; // ecx

  if ( (uint16_t)a3 == 0xFFFF )
    result = 0;
  else
    result = sub_429830((uint32_t *)dword_8F8500, a3);
  v5 = *(this + a2 + 4);
  if ( v5 != result )
  {
    if ( v5 != 0 )
      *(uint8_t *)(v5 + 188) = 0;
    if ( result != 0 )
      *(uint8_t *)(result + 188) = 1;
    *(this + a2 + 4) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x456390 sub_456390
// ------------------------------------------------------------
// 座位号查询（本地玩家 → 座位 index；触发条件评估器 case 5 所用）
int /*thiscall*/ sub_456390(char *this, char a2)
{
  int v2; // ebx
  char *v3; // esi
  int i; // edi
  int v5; // ecx
  int v6; // eax
  int v7; // ecx

  v2 = 0;
  v3 = this + 16;
  for ( i = 4; i != 0; --i )
  {
    if ( *(uint32_t *)v3 != 0
      && (a2 == 0
       || (v5 = *(uint32_t *)(*(uint32_t *)v3 + 196)) != 0
       && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 1196))(v5) == 0) )
    {
      ++v2;
    }
    v3 += 4;
  }
  if ( v2 != 0 )
    return v2;
  if ( a2 != 0
    && ((v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804)) == 0
     || (v7 = *(uint32_t *)(v6 + 196)) == 0
     || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 1196))(v7) != 0) )
  {
    return v2;
  }
  else
  {
    return 1;
  }
}



// ------------------------------------------------------------
// 0x456420 sub_456420
// ------------------------------------------------------------
// 座位查找（docs/13 §3：进 2 = MAP_APPEAR + 座位 sub_456420）：
// 本地角色在 +4 起的 4 槽中定位 → 0..3，未找到 -1
int /*thiscall*/ sub_456420(uint32_t *this)
{
  int v2; // edx
  int result; // eax
  uint32_t *i; // ecx

  v2 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  if ( v2 == 0 )
    return -1;
  result = 0;
  for ( i = this + 4; *i != v2; ++i )
  {
    if ( ++result >= 4 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x456460 sub_456460
// ------------------------------------------------------------
char /*thiscall*/ sub_456460(uint32_t *this, int a2)
{
  char result; // al

  *(this + 8) = a2;
  result = dword_8F7A24;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 2 )
    return sub_4542A0(*(uint32_t **)(dword_8F7A24 + 24));
  return result;
}



// ------------------------------------------------------------
// 0x456480 sub_456480
// ------------------------------------------------------------
// 座位号（PVP/WARROOM 场景恒 -1；其余取 +8）
int /*thiscall*/ sub_456480(uint32_t *this)
{
  int v1; // eax

  v1 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v1 == 4 || v1 == 6 )
    return -1;
  else
    return *(this + 8);
}



// ------------------------------------------------------------
// 0x4564A0 sub_4564A0
// ------------------------------------------------------------
char /*cdecl*/ sub_4564A0(int a1)
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
  int v11; // ecx
  int v12; // edi
  uint32_t *v13; // esi
  char *v14; // eax
  int v15; // [esp-14h] [ebp-24h]
  int v16; // [esp-10h] [ebp-20h]
  int v17; // [esp+8h] [ebp-8h] BYREF
  uint8_t v18[4]; // [esp+Ch] [ebp-4h] BYREF

  v1 = sub_429830((uint32_t *)dword_8F8500, a1);
  if ( v1 == 0 )
  {
    v16 = 432;
LABEL_7:
    v2 = *((uint32_t **)dword_8F8528 + 7);
    v3 = sub_422E70(v16);
    goto LABEL_8;
  }
  if ( v1 == sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )
  {
    v2 = *((uint32_t **)dword_8F8528 + 7);
    v3 = sub_422E70(433);
LABEL_8:
    sub_43BEE0(v2, (int)v3, -6567706, 0, -1);
    return 0;
  }
  if ( *(uint32_t *)(v1 + 68) != 0 )
  {
    v16 = 434;
    goto LABEL_7;
  }
  v5 = *(uint32_t *)(v1 + 184);
  v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  v7 = *(uint32_t *)(v6 + 184);
  if ( v5 != 0 )
  {
    if ( v7 != 0 )
    {
      v15 = 435;
LABEL_12:
      v8 = *((uint32_t **)dword_8F8528 + 7);
      v9 = sub_422E70(v15);
      sub_43BEE0(v8, (int)v9, -6567706, 0, -1);
      return 0;
    }
    if ( *(uint32_t *)(v5 + 60) - sub_56A720(v5) <= 0 )
    {
      v15 = 436;
      goto LABEL_12;
    }
  }
  else if ( v7 != 0 && *(uint32_t *)(v7 + 60) - sub_56A720(*(uint32_t *)(v6 + 184)) <= 0 )
  {
    v15 = 437;
    goto LABEL_12;
  }
  v10 = sub_432F00(0);
  sub_423200(dword_8F7B08, 10);
  v17 = a1;
  sub_423290(dword_8F7B08, (int)&v17, 2);
  v18[0] = 0;
  sub_423290(dword_8F7B08, (int)v18, 1);
  v11 = *(uint32_t *)(v10[3] + 4);
  v12 = dword_8F7B08;
  v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 44))(v11);
  sub_423290(v12, (int)&v17, 4);
  sub_423380(dword_8F7B08);
  if ( v5 != 0 )
  {
    v13 = *((uint32_t **)dword_8F8528 + 7);
    v14 = sub_422E70(438);
  }
  else
  {
    v13 = *((uint32_t **)dword_8F8528 + 7);
    v14 = sub_422E70(439);
  }
  sub_43BEE0(v13, (int)v14, -6567706, 0, -1);
  return 1;
}



// ============================================================
// 【分区 6】队伍管理（0x456690-0x457790）
// CNRDParty__vmt0（RTTI 自证）与队员槽位维护。
// ============================================================
// ------------------------------------------------------------
// 0x456690 sub_456690
// ------------------------------------------------------------
char /*cdecl*/ sub_456690(int a1)
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
  int v12; // [esp+4h] [ebp-8h] BYREF
  uint8_t v13[4]; // [esp+8h] [ebp-4h] BYREF

  v1 = sub_429830((uint32_t *)dword_8F8500, a1);
  if ( v1 == 0 )
  {
    v2 = *((uint32_t **)dword_8F8528 + 7);
    v3 = sub_422E70(440);
LABEL_5:
    sub_43BEE0(v2, (int)v3, -6567706, 0, -1);
    return 0;
  }
  if ( *(uint32_t *)(v1 + 68) != 0 )
  {
    v2 = *((uint32_t **)dword_8F8528 + 7);
    v3 = sub_422E70(441);
    goto LABEL_5;
  }
  v5 = *(uint32_t *)(v1 + 184);
  v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  v7 = *(uint32_t *)(v6 + 184);
  if ( v5 != 0 )
  {
    if ( v7 != 0 )
    {
      v8 = *((uint32_t **)dword_8F8528 + 7);
      v9 = sub_422E70(442);
LABEL_9:
      sub_43BEE0(v8, (int)v9, -6567706, 0, -1);
      return 0;
    }
    if ( *(uint32_t *)(v5 + 60) - sub_56A720(v5) <= 0 )
    {
      v8 = *((uint32_t **)dword_8F8528 + 7);
      v9 = sub_422E70(443);
      goto LABEL_9;
    }
  }
  else if ( v7 != 0 && *(uint32_t *)(v7 + 60) - sub_56A720(*(uint32_t *)(v6 + 184)) <= 0 )
  {
    v8 = *((uint32_t **)dword_8F8528 + 7);
    v9 = sub_422E70(444);
    goto LABEL_9;
  }
  sub_423200(dword_8F7B08, 11);
  v12 = a1;
  sub_423290(dword_8F7B08, (int)&v12, 2);
  v13[0] = 0;
  sub_423290(dword_8F7B08, (int)v13, 1);
  v12 = 0;
  sub_423290(dword_8F7B08, (int)&v12, 4);
  sub_423380(dword_8F7B08);
  if ( v5 != 0 )
  {
    v10 = *((uint32_t **)dword_8F8528 + 7);
    v11 = sub_422E70(445);
  }
  else
  {
    v10 = *((uint32_t **)dword_8F8528 + 7);
    v11 = sub_422E70(446);
  }
  sub_43BEE0(v10, (int)v11, -6567706, 0, -1);
  return 1;
}



// ------------------------------------------------------------
// 0x456850 sub_456850
// ------------------------------------------------------------
char /*thiscall*/ sub_456850(int *this)
{
  int *v2; // esi
  uint32_t *v3; // eax
  int i; // edx
  int v5; // eax
  int v6; // ecx
  char result; // al

  v2 = this + 4;
  v3 = this + 4;
  for ( i = 4; i != 0; --i )
  {
    if ( *v3 != 0 )
    {
      *(uint8_t *)(*v3 + 188) = 0;
      *v3 = 0;
    }
    ++v3;
  }
  v5 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  v6 = *v2;
  if ( *v2 != v5 )
  {
    if ( v6 != 0 )
      *(uint8_t *)(v6 + 188) = 0;
    if ( v5 != 0 )
      *(uint8_t *)(v5 + 188) = 1;
    *v2 = v5;
  }
  *(this + 8) = 0;
  result = dword_8F7A24;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 2 )
    return sub_4542A0(*(uint32_t **)(dword_8F7A24 + 24));
  return result;
}



// ------------------------------------------------------------
// 0x4568C0 sub_4568C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4568C0(uint32_t *this)
{
  uint32_t *v2; // ecx
  uint32_t *v3; // eax
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void *i; // ebx
  uint32_t *v6; // edi
  uint32_t *v7; // esi
  uint32_t *result; // eax
  uint32_t *v9; // [esp+Ch] [ebp-4h] BYREF

  v2 = (uint32_t *)*(this + 2);
  v3 = (uint32_t *)*v2;
  v9 = (uint32_t *)*v2;
  if ( v9 != v2 )
  {
    do
    {
      v4 = (void (/*thiscall*/ ***)(uint32_t, int))v3[4];
      if ( v4 != nullptr )
        (**v4)(v4, 1);
      sub_41C5E0(&v9);
      v3 = v9;
    }
    while ( v9 != (uint32_t *)*(this + 2) );
  }
  v6 = this + 1;
  v7 = *(uint32_t **)(*(this + 2) + 4);
  for ( i = v7; *((uint8_t *)v7 + 21) == 0; i = v7 )
  {
    sub_433BC0((void **)v7[2]);
    v7 = (uint32_t *)*v7;
    j__free(i);
  }
  *(uint32_t *)(v6[1] + 4) = v6[1];
  result = (uint32_t *)v6[1];
  v6[2] = 0;
  *result = result;
  *(uint32_t *)(v6[1] + 8) = v6[1];
  return result;
}



// ------------------------------------------------------------
// 0x456950 sub_456950
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_456950(void ***this)
{
  void **v2; // ecx
  uint32_t *v3; // eax
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  uint32_t *v5; // esi
  char v6; // al
  char v7; // al
  uint32_t *result; // eax
  void *Block; // [esp+Ch] [ebp-4h] BYREF

  v2 = *(this + 2);
  v3 = *v2;
  Block = *v2;
  if ( Block != v2 )
  {
    do
    {
      v4 = (void (/*thiscall*/ ***)(uint32_t, int))v3[4];
      if ( v4 != nullptr )
        (**v4)(v4, 1);
      sub_41C5E0(&Block);
      v3 = Block;
    }
    while ( Block != *(this + 2) );
  }
  v5 = (*(this + 2))[1];
  v6 = *((uint8_t *)v5 + 21);
  Block = v5;
  if ( v6 == 0 )
  {
    do
    {
      sub_433BC0((void **)v5[2]);
      v5 = (uint32_t *)*v5;
      j__free(Block);
      v7 = *((uint8_t *)v5 + 21);
      Block = v5;
    }
    while ( v7 == 0 );
  }
  (*(this + 2))[1] = *(this + 2);
  result = *(this + 2);
  *(this + 3) = nullptr;
  *result = result;
  (*(this + 2))[2] = *(this + 2);
  *(this + 4) = nullptr;
  *(this + 5) = nullptr;
  *(this + 6) = nullptr;
  *(this + 7) = nullptr;
  *(this + 8) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x4569F0 sub_4569F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4569F0(uint32_t *this, char a2)
{
  int v4; // [esp+4h] [ebp-4h] BYREF

  sub_472E30(&v4, &a2);
  if ( v4 == *(this + 2) )
    return 0;
  else
    return *(uint32_t *)(v4 + 16);
}



// ------------------------------------------------------------
// 0x456A30 sub_456A30
// ------------------------------------------------------------
// attributes: thunk
uint32_t */*thiscall*/ sub_456A30(void ***this)
{
  return sub_456950(this);
}



// ------------------------------------------------------------
// 0x456A40 sub_456A40
// ------------------------------------------------------------
int */*thiscall*/ sub_456A40(int **this, int *a2, char a3, int *a4, int a5)
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
// 0x456BF0 sub_456BF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_456BF0(uint32_t *this)
{
  uint32_t *v2; // ecx

  v2 = this + 2;
  v2[6] = 15;
  v2[5] = 0;
  *((uint8_t *)v2 + 4) = 0;
  *this = 0;
  *(this + 1) = 0;
  sub_4015C0((void *)szPassword, 0);
  *(this + 9) = 0xFFFF;
  *(this + 10) = 0xFFFF;
  *(this + 11) = 0xFFFF;
  *(this + 12) = 0xFFFF;
  *(this + 13) = 0;
  *(this + 14) = 4;
  return this;
}



// ------------------------------------------------------------
// 0x456C70 sub_456C70
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_456C70(uint32_t *this, int a2)
{
  *this = &vftbl_CNRDParty;
  sub_456BF0(this + 1);
  nullsub_3();
  unknown_libname_7(a2);
  return this;
}



// ------------------------------------------------------------
// 0x456CD0 CNRDParty__vmt0
// ------------------------------------------------------------
// CNRDParty::vmt0 —— 队伍对象构造（RTTI 自证）
void */*thiscall*/ CNRDParty__vmt0(void *Block, char a2)
{
  sub_456D00();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x456D00 sub_456D00
// ------------------------------------------------------------
void /*thiscall*/ sub_456D00(void **this)
{
  *this = &vftbl_CNRDParty;
  nullsub_3();
  if ( (unsigned int)*(this + 9) >= 0x10 )
    j__free(*(this + 4));
  *(this + 9) = (void *)15;
  *(this + 8) = nullptr;
  *((uint8_t *)this + 16) = 0;
}



// ------------------------------------------------------------
// 0x456D70 sub_456D70
// ------------------------------------------------------------
int */*thiscall*/ sub_456D70(uint32_t *this, int a2)
{
  int *result; // eax
  void (/*thiscall*/ ***v4)(uint32_t, int); // ebx
  int *v5; // esi
  int i; // edi
  int v7; // eax
  uint32_t *v8; // [esp+4h] [ebp-8h]
  int *v9; // [esp+8h] [ebp-4h] BYREF

  v8 = this + 1;
  sub_472E30(&v9, &a2);
  result = v9;
  if ( v9 != (int *)*(this + 2) )
  {
    v4 = (void (/*thiscall*/ ***)(uint32_t, int))v9[4];
    v5 = (int *)(v4 + 10);
    for ( i = 4; i != 0; --i )
    {
      if ( *v5 != 0xFFFF )
      {
        v7 = sub_429830((uint32_t *)dword_8F8500, *v5);
        if ( v7 != 0 )
          *(uint32_t *)(v7 + 184) = 0;
      }
      ++v5;
    }
    if ( v4 != nullptr )
      (**v4)(v4, 1);
    return sub_4341B0(v8, &a2, (int)v9);
  }
  return result;
}



// ------------------------------------------------------------
// 0x456DF0 sub_456DF0
// ------------------------------------------------------------
int /*thiscall*/ sub_456DF0(int **this, int a2, int *a3)
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
      v10 = *sub_456A40(this, (int *)&a3, 1, v5, (int)v3);
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
    v12 = *sub_456A40(this, (int *)&a3, v13, v5, (int)v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x456EB0 sub_456EB0
// ------------------------------------------------------------
int */*thiscall*/ sub_456EB0(int **this, void *Block)
{
  int v2; // ebx
  int **v4; // edi
  int *result; // eax
  uint32_t *v6; // eax
  int *v7; // esi
  char v8[8]; // [esp+Ch] [ebp-1Ch] BYREF
  int v9; // [esp+14h] [ebp-14h] BYREF
  int *v10; // [esp+18h] [ebp-10h] BYREF
  int v11; // [esp+24h] [ebp-4h]

  v2 = (int)Block;
  v4 = this + 1;
  sub_472E30(&v10, &Block);
  if ( v10 == *(this + 2) || (result = (int *)v10[4]) == nullptr )
  {
    v6 = operator new(0x40u);
    Block = v6;
    v7 = nullptr;
    v11 = 0;
    if ( v6 != nullptr )
      v7 = sub_456C70(v6, v2);
    v11 = -1;
    v9 = v2;
    v10 = v7;
    sub_456DF0(v4, (int)v8, &v9);
    return v7;
  }
  return result;
}



// ------------------------------------------------------------
// 0x456F50 sub_456F50
// ------------------------------------------------------------
int /*thiscall*/ sub_456F50(uint32_t *this)
{
  *(this + 40) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 164) = 0;
  *(this + 1) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 160) = 3;
  return 0;
}



// ------------------------------------------------------------
// 0x456F80 sub_456F80
// ------------------------------------------------------------
int /*thiscall*/ sub_456F80(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  uint32_t *v4; // esi
  int i; // edi
  uint32_t *v6; // esi
  int j; // edi
  uint32_t *v8; // esi
  int k; // edi

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 11) = 0;
  v4 = this + 9;
  for ( i = 2; i != 0; --i )
  {
    if ( *v4 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v4)(*v4, 1);
    *v4++ = 0;
  }
  v6 = this + 131;
  for ( j = 4; j != 0; --j )
  {
    if ( *v6 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v6)(*v6, 1);
    *v6++ = 0;
  }
  v8 = this + 147;
  for ( k = 3; k != 0; --k )
  {
    if ( *v8 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v8)(*v8, 1);
    *v8++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x457010 sub_457010
// ------------------------------------------------------------
void */*thiscall*/ sub_457010(uint32_t *this)
{
  void *result; // eax

  if ( *(this + 1) == 9 )
  {
    result = dword_8F8528;
    *(uint8_t *)(*(this + 11) + 16) = *((uint32_t *)dword_8F8528 + 27) == 12;
  }
  return result;
}



// ------------------------------------------------------------
// 0x457040 sub_457040
// ------------------------------------------------------------
int /*stdcall*/ sub_457040(uint8_t a1)
{
  int result; // eax

  result = sub_418DD0(53);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
             result,
             0,
             0,
             dword_79C0B0,
             1065353216,
             1065353216,
             0,
             (a1 << 24) | 0xFFFFFF,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x457090 sub_457090
// ------------------------------------------------------------
int /*thiscall*/ sub_457090(int *this)
{
  int result; // eax
  int *v3; // edi
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  bool v7; // cc
  int v8; // [esp+4h] [ebp-8h]
  int v9; // [esp+8h] [ebp-4h]

  result = 0;
  v8 = 0;
  if ( *(this + 66) > 0 )
  {
    v9 = 0;
    v3 = this + 67;
    do
    {
      if ( *v3 > 0 )
      {
        v4 = sub_699000((int)(this + 2));
        v5 = (uint64_t)sub_4049C0(0.0, 255.0, v4 - *v3, 500);
        v6 = sub_418DD0(v9);
        if ( v6 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
            v6,
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
      result = v8 + 1;
      ++v3;
      v7 = ++v8 < *(this + 66);
      v9 += 3;
    }
    while ( v7 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x457160 sub_457160
// ------------------------------------------------------------
int /*thiscall*/ sub_457160(void *this)
{
  int v1; // edi
  int v2; // eax
  int v3; // esi
  int v4; // eax
  int v5; // eax
  int v6; // esi
  int v7; // eax
  double v8; // st7
  int result; // eax
  int v10; // eax
  int v11; // esi
  int v12; // eax
  int v13; // eax
  int v14; // [esp-8h] [ebp-14h]
  int v15; // [esp-8h] [ebp-14h]

  v1 = (int)this + 8;
  if ( sub_699000((int)this + 8) >= 1800 )
  {
    result = sub_699000(v1);
    if ( result >= 1800 )
      return result;
    sub_491530(2, 0);
    v10 = sub_699000(v1);
    v11 = ((uint8_t)(uint64_t)sub_4049C0(255.0, 0.0, v10, 1800) << 24) | 0xFFFFFF;
    v12 = sub_418DD0(54);
    if ( v12 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v12 + 128))(
        v12,
        0,
        0,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v11,
        1333788672,
        1333788672);
    v15 = sub_699000(v1);
    v8 = sub_4049C0(200.0, 0.0, v15, 1800);
  }
  else
  {
    v2 = sub_699000(v1);
    v3 = ((uint8_t)(uint64_t)sub_4049C0(255.0, 0.0, v2, 1800) << 24) | 0xFFFFFF;
    v4 = sub_418DD0(53);
    if ( v4 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v4 + 128))(
        v4,
        0,
        0,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v3,
        1333788672,
        1333788672);
    sub_491530(2, 0);
    v5 = sub_699000(v1);
    v6 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 255.0, v5, 1800) << 24) | 0xFFFFFF;
    v7 = sub_418DD0(54);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v7 + 128))(
        v7,
        0,
        0,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v6,
        1333788672,
        1333788672);
    v14 = sub_699000(v1);
    v8 = sub_4049C0(0.0, 200.0, v14, 1800);
  }
  v13 = sub_418DD0(55);
  if ( v13 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
      v13,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)(uint64_t)v8 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  return sub_491630(2);
}



// ------------------------------------------------------------
// 0x457370 sub_457370
// ------------------------------------------------------------
int /*thiscall*/ sub_457370(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // eax
  double v11; // st7
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax
  bool v16; // cc
  int v17; // [esp-10h] [ebp-20h]
  int v18; // [esp-10h] [ebp-20h]
  int v19; // [esp+4h] [ebp-Ch]
  int *v20; // [esp+8h] [ebp-8h]
  int v21; // [esp+Ch] [ebp-4h]

  result = *(this + 66);
  v19 = 0;
  if ( result > 0 )
  {
    v21 = 2;
    v20 = this + 67;
    do
    {
      if ( *v20 > 0 )
      {
        v3 = sub_699000((int)(this + 2));
        v4 = (int)(this + 2);
        if ( v3 < 1800 )
        {
          v5 = sub_699000(v4);
          v6 = ((uint8_t)(uint64_t)sub_4049C0(255.0, 0.0, v5, 1800) << 24) | 0xFFFFFF;
          v7 = sub_418DD0(v21 - 2);
          if ( v7 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v7 + 128))(
              v7,
              0,
              0,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              v6,
              1333788672,
              1333788672);
          sub_491530(2, 0);
          v8 = sub_699000((int)(this + 2));
          v9 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 255.0, v8, 1800) << 24) | 0xFFFFFF;
          v10 = sub_418DD0(v21 - 1);
          if ( v10 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 128))(
              v10,
              0,
              0,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              v9,
              1333788672,
              1333788672);
          v17 = sub_699000((int)(this + 2));
          v11 = sub_4049C0(0.0, 200.0, v17, 1800);
LABEL_14:
          v15 = sub_418DD0(v21);
          if ( v15 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v15 + 128))(
              v15,
              0,
              0,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              ((uint8_t)(uint64_t)v11 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          sub_491630(2);
          goto LABEL_17;
        }
        if ( sub_699000(v4) < 1800 )
        {
          sub_491530(2, 0);
          v12 = sub_699000((int)(this + 2));
          v13 = ((uint8_t)(uint64_t)sub_4049C0(255.0, 0.0, v12, 1800) << 24) | 0xFFFFFF;
          v14 = sub_418DD0(v21 - 1);
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
          v18 = sub_699000((int)(this + 2));
          v11 = sub_4049C0(200.0, 0.0, v18, 1800);
          goto LABEL_14;
        }
      }
LABEL_17:
      result = v19 + 1;
      v16 = ++v19 < *(this + 66);
      ++v20;
      v21 += 3;
    }
    while ( v16 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x4575F0 sub_4575F0
// ------------------------------------------------------------
int /*usercall*/ sub_4575F0@<eax>(int a1@<ecx>, double a2@<st0>)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int result; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // [esp-8h] [ebp-14h]
  int v10; // [esp-8h] [ebp-14h]

  v2 = a1 + 8;
  if ( sub_699000(a1 + 8) >= 1800 )
  {
    result = sub_699000(v2);
    if ( result >= 1800 )
      return result;
    sub_491530(2, 0);
    v6 = sub_699000(v2);
    sub_4049C0(200.0, 0.0, v6, 1800);
    v7 = sub_418DD0(56);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v7 + 128))(
        v7,
        0,
        0,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)(uint64_t)a2 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v10 = sub_699000(v2);
    sub_4049C0(150.0, 0.0, v10, 1800);
  }
  else
  {
    sub_491530(2, 0);
    v3 = sub_699000(v2);
    sub_4049C0(0.0, 200.0, v3, 2300);
    v4 = sub_418DD0(56);
    if ( v4 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v4 + 128))(
        v4,
        0,
        0,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)(uint64_t)a2 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v9 = sub_699000(v2);
    sub_4049C0(0.0, 150.0, v9, 2300);
  }
  v8 = sub_418DD0(57);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v8 + 128))(
      v8,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)(uint64_t)a2 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  return sub_491630(2);
}



// ============================================================
// 【分区 7】奖励系统 I（0x457790-0x458930）
// 奖励箱开启：REWARD_OPEN1（0x4577F0/0x458120，CLICK_BUTTON2 自证）。
// ============================================================
// ------------------------------------------------------------
// 0x457790 sub_457790
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_457790(int *this)
{
  int v1; // edx
  int v2; // esi
  uint32_t *v3; // eax
  int v4; // ecx

  v1 = *(this + 109);
  v2 = 0;
  if ( v1 > 0 )
  {
    v3 = this + 127;
    v4 = *(this + 109);
    do
    {
      if ( *v3 != -1 )
        ++v2;
      ++v3;
      --v4;
    }
    while ( v4 != 0 );
  }
  return v2 == v1;
}



// ------------------------------------------------------------
// 0x4577C0 sub_4577C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4577C0(uint8_t *this)
{
  int result; // eax

  sub_423200(dword_8F7B08, 73);
  result = sub_423380(dword_8F7B08);
  *(this + 580) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x4577F0 sub_4577F0
// ------------------------------------------------------------
// 奖励箱开启 —— REWARD_OPEN1 + CLICK_BUTTON2 自证：
// +127 槽空且 a3 有效 → 记箱号/时刻；与本地主角 vt+1216 比对 → +135 命中标记
// （CLICK_BUTTON2）否则 +146=-1 → 按钮熄灭 → REWARD_OPEN1
void /*thiscall*/ sub_4577F0(uint32_t *this, char a2, char a3)
{
  if ( *(this + a2 + 127) == -1 && a3 != -1 )
  {
    *(this + a2 + 127) = a3;
    *(this + a2 + 136) = sub_699000((int)(this + 41));
    if ( a3 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1216))(dword_8F7C04) )
    {
      *(this + 135) = a2;
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
    else
    {
      *(this + 146) = -1;
    }
    *(uint8_t *)(*(this + a2 + 131) + 16) = 0;
    sub_432EA0("REWARD_OPEN1", -1, 0, 0);
  }
}



// ------------------------------------------------------------
// 0x457890 sub_457890
// ------------------------------------------------------------
int /*thiscall*/ sub_457890(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int result; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // esi
  int v11; // eax
  int v12; // eax
  int v13; // esi
  int v14; // eax
  bool v15; // cc
  float v16; // [esp+24h] [ebp-28h]
  int v17; // [esp+3Ch] [ebp-10h]
  int v18; // [esp+40h] [ebp-Ch]
  int v19; // [esp+44h] [ebp-8h]
  int v20; // [esp+48h] [ebp-4h]

  v2 = (int)(this + 2);
  v3 = sub_699000((int)(this + 2));
  v4 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 200.0, v3, 1200) << 24) | 0xFFFFFF;
  v5 = sub_418DD0(34);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v5 + 128))(
      v5,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      v4,
      1333788672,
      1333788672);
  result = 0;
  v17 = 0;
  if ( (int)*(this + 109) > 0 )
  {
    v20 = 0;
    do
    {
      v7 = sub_699000(v2);
      v16 = (float)(v20 + dword_6C6E00[*(this + 109)]);
      v18 = (uint64_t)sub_4049C0(243.0, v16, v7, 1200);
      v8 = sub_699000(v2);
      v19 = (uint64_t)sub_4049C0(163.0, 163.0, v8, 1200);
      v9 = sub_699000(v2);
      v10 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 255.0, v9, 1200) << 24) | 0xFFFFFF;
      v11 = sub_418DD0(45);
      if ( v11 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v11 + 128))(
          v11,
          v18,
          v19,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v10,
          1333788672,
          1333788672);
      sub_491530(2, 0);
      v12 = sub_699000(v2);
      v13 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 220.0, v12, 1200) << 24) | 0xFFFFFF;
      v14 = sub_418DD0(40);
      if ( v14 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
          v14,
          v18,
          v19,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v13,
          1333788672,
          1333788672);
      sub_491630(2);
      result = v17 + 1;
      v15 = ++v17 < *(this + 109);
      v20 += 158;
    }
    while ( v15 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x457AA0 sub_457AA0
// ------------------------------------------------------------
int /*thiscall*/ sub_457AA0(int *this, int a2)
{
  int result; // eax
  int *v4; // edx
  int v5; // ecx
  int v6; // ebx
  int v7; // esi
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // esi
  int v13; // eax
  bool v14; // cc
  uint32_t *v15; // [esp+4h] [ebp-Ch]
  int v16; // [esp+8h] [ebp-8h]
  int v17; // [esp+Ch] [ebp-4h]

  result = *(this + 109);
  v16 = 0;
  if ( result > 0 )
  {
    v4 = this + 131;
    v17 = 0;
    v15 = this + 131;
    do
    {
      v5 = *v4;
      if ( a2 == *v4 )
      {
        v6 = v17 + dword_6C6E00[result];
        if ( *(uint8_t *)(v5 + 17) != 0
          && ((v7 = *(uint32_t *)(v5 + 12), dword_79BE3C == v7) || *(uint8_t *)(v5 + 17) != 0 && dword_79BE34 == v7) )
        {
          sub_491530(2, 0);
          v10 = sub_418DD0(86);
          if ( v10 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 152))(v10, v6, 163, dword_79C0B0);
          sub_491630(2);
        }
        else if ( *(v4 - 4) == -1 )
        {
          v8 = sub_699000((int)(this + 2));
          v9 = sub_418DD0(v8 % 800 / 200 + 36);
          if ( v9 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, v6, 163, dword_79C0B0);
        }
        if ( sub_699000((int)(this + 2)) < 500 )
        {
          sub_491530(2, 0);
          v11 = sub_699000((int)(this + 2));
          v12 = ((uint8_t)(uint64_t)sub_4049C0(220.0, 0.0, v11, 500) << 24) | 0xFFFFFF;
          v13 = sub_418DD0(40);
          if ( v13 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
              v13,
              v6,
              163,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              v12,
              1333788672,
              1333788672);
          sub_491630(2);
        }
      }
      result = *(this + 109);
      v4 = v15 + 1;
      v14 = ++v16 < result;
      ++v15;
      v17 += 158;
    }
    while ( v14 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x457C60 sub_457C60
// ------------------------------------------------------------
int /*thiscall*/ sub_457C60(int *this)
{
  int v1; // ebx
  int v2; // esi
  int *v3; // edi
  int result; // eax

  v1 = (int)(this + 41);
  v2 = 1000;
  v3 = this + 79;
  do
  {
    *(v3 - 1) = v2 + sub_699000(v1);
    result = sub_699000(v1) + v2 + 2000;
    *v3 = result;
    v2 += 400;
    v3 += 3;
  }
  while ( v2 < 2200 );
  return result;
}



// ------------------------------------------------------------
// 0x457CB0 sub_457CB0
// ------------------------------------------------------------
int /*usercall*/ sub_457CB0@<eax>(int a1@<ecx>, double a2@<st0>)
{
  uint32_t *v2; // eax
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // esi
  int v7; // ebx
  int v8; // eax
  bool v9; // zf
  int result; // eax
  float v11; // [esp+0h] [ebp-30h]
  float v12; // [esp+1Ch] [ebp-14h]
  int v13; // [esp+20h] [ebp-10h]
  int v14; // [esp+24h] [ebp-Ch]
  int v15; // [esp+28h] [ebp-8h]
  uint32_t *v16; // [esp+2Ch] [ebp-4h]

  v2 = (uint32_t *)(a1 + 316);
  v15 = a1;
  v16 = (uint32_t *)(a1 + 316);
  v14 = 3;
  while ( 1 )
  {
    v3 = *(v2 - 1);
    v4 = *v2 - v3;
    v5 = sub_699000(a1 + 164);
    v6 = v5 - v3;
    v13 = v5 - v3;
    if ( v5 - v3 > 0 && v6 < v4 )
    {
      if ( v6 >= 800 )
        sub_4049F0(255.0, 0.0, v5 - v3, v4, 1);
      else
        sub_4049F0(0.0, 255.0, v5 - v3, 800, 1);
      v7 = (uint64_t)a2;
      sub_4049F0(0.5, 1.3, v6, v4, 1);
      v12 = a2;
      sub_491530(2, 0);
      v8 = sub_418DD0(58);
      if ( v8 != 0 )
      {
        a2 = (double)v13 * 0.02;
        v11 = a2;
        (*(void (/*thiscall*/ **)(int, int, int, int, float, float, uint32_t, int, int, int))(*(uint32_t *)v8 + 156))(
          v8,
          175,
          20,
          dword_79C0B0,
          COERCE_FLOAT(LODWORD(v12)),
          COERCE_FLOAT(LODWORD(v12)),
          LODWORD(v11),
          ((uint8_t)v7 << 24) | 0xFFFFFF,
          1128923136,
          1128923136);
      }
      sub_491630(2);
    }
    result = v14 - 1;
    v9 = v14 == 1;
    v16 += 3;
    --v14;
    if ( v9 )
      break;
    v2 = v16;
    a1 = v15;
  }
  return result;
}



// ------------------------------------------------------------
// 0x457DD0 sub_457DD0
// ------------------------------------------------------------
void /*thiscall*/ sub_457DD0(int *this)
{
  int v2; // ecx
  int v3; // edi
  uint32_t *v4; // eax
  int i; // edx
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // edi

  v2 = *(this + 109);
  v3 = 0;
  if ( v2 > 0 )
  {
    v4 = this + 127;
    for ( i = v2; i != 0; --i )
    {
      if ( *v4 != -1 )
        ++v3;
      ++v4;
    }
  }
  if ( v3 != v2 )
  {
    v6 = sub_418DD0(83);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v6 + 152))(v6, 0, 0, dword_79C0B0);
    v7 = sub_418DD0(82);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v7 + 152))(v7, 0, 0, dword_79C0B0);
    v8 = sub_699000((int)(this + 41)) - *(this + 54);
    if ( v8 >= 1000 )
    {
      v9 = (4 - v8 / 1000) & ((4 - v8 / 1000 < 0) - 1);
      sub_69A110(305, 355, v9, -1);
      sub_69A110(305, 355, v9, -1);
    }
  }
}



// ------------------------------------------------------------
// 0x457EC0 sub_457EC0
// ------------------------------------------------------------
void /*thiscall*/ sub_457EC0(int this, unsigned int ArgList, int a3)
{
  int v3; // ebx

  v3 = a3;
  if ( (a3 != 2 || *(uint32_t *)(this + 604) != ArgList && sub_699000(this + 612) >= 500)
    && (*(uint8_t *)(this + 660) != 0 || ArgList >= 2) )
  {
    *(uint32_t *)(this + 604) = ArgList;
    *(uint32_t *)(this + 608) = v3;
    sub_423200(dword_8F7B08, 75);
    HIBYTE(a3) = v3;
    sub_423290(dword_8F7B08, (int)&a3 + 3, 1);
    if ( ArgList != 0 )
    {
      if ( ArgList == 1 )
      {
        HIBYTE(a3) = 1;
        sub_423290(dword_8F7B08, (int)&a3 + 3, 1);
      }
      else if ( ArgList == 2 )
      {
        HIBYTE(a3) = 2;
        sub_423290(dword_8F7B08, (int)&a3 + 3, 1);
      }
    }
    else
    {
      HIBYTE(a3) = 0;
      sub_423290(dword_8F7B08, (int)&a3 + 3, 1);
    }
    sub_423380(dword_8F7B08);
    *(uint8_t *)(this + 625) = 0;
    *(uint8_t *)(this + 626) = 0;
    sub_698F90(this + 612, 0, 0);
    off_77F3FC((char *)&byte_6C6E70, ArgList, v3);
  }
}



// ------------------------------------------------------------
// 0x457FB0 sub_457FB0
// ------------------------------------------------------------
int /*thiscall*/ sub_457FB0(uint32_t *this, int ArgList, int a3)
{
  int v3; // esi
  uint32_t *v5; // ebx
  int v6; // ebx
  int result; // eax
  int *v8; // esi
  uint32_t *v9; // ebx
  int v10; // eax
  int v11; // esi
  uint32_t *v12; // esi
  char *v13; // eax
  int *v14; // [esp+Ch] [ebp-8h]
  int v15; // [esp+10h] [ebp-4h]

  v3 = ArgList;
  *(this + 151) = ArgList;
  *(this + 152) = a3;
  off_77F3FC((char *)&byte_6C6E98, ArgList, a3);
  v5 = (uint32_t *)dword_8F850C;
  if ( sub_456480((uint32_t *)dword_8F850C) == -1 )
    v6 = 0;
  else
    v6 = v5[sub_456480(v5) + 4];
  result = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  if ( v6 != result )
  {
    v15 = 0;
    v8 = (int *)&unk_6C6E2C;
    v9 = this + 147;
    v14 = (int *)(4 * a3 + 7106092);
    do
    {
      v10 = *v8;
      if ( v15 == ArgList )
        v10 = *v14;
      result = sub_69C980(*(this + 13), v10, v10, v10, v10, 0, 0);
      v8 += 4;
      ++v9;
      ++v15;
      v14 += 4;
    }
    while ( (int)v8 < (int)"REWARD_OPEN1" );
    v3 = ArgList;
  }
  if ( a3 == 1 )
  {
    *(this + 160) = v3;
    *(this + 161) = **(uint32_t **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);
    result = dword_99FB8C;
    *(this + 162) = dword_99FB8C;
    if ( v3 != 0 )
    {
      v11 = v3 - 1;
      if ( v11 != 0 )
      {
        if ( v11 != 1 )
          return result;
        v12 = *((uint32_t **)dword_8F8528 + 7);
        v13 = sub_422E70(481);
      }
      else
      {
        v12 = *((uint32_t **)dword_8F8528 + 7);
        v13 = sub_422E70(480);
      }
    }
    else
    {
      v12 = *((uint32_t **)dword_8F8528 + 7);
      v13 = sub_422E70(479);
    }
    return sub_43BEE0(v12, (int)v13, -6567706, 0, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x458120 sub_458120
// ------------------------------------------------------------
// 奖励箱开启循环（REWARD_OPEN1 自证）【推断：多箱批量推进】
int /*thiscall*/ sub_458120(uint32_t *this)
{
  *(this + 160) = 3;
  *(this + 161) = -1;
  *(this + 162) = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x458140 sub_458140
// ------------------------------------------------------------
int /*thiscall*/ sub_458140(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 52;
  return result;
}



// ------------------------------------------------------------
// 0x458160 sub_458160
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_458160(uint32_t *this, int a2)
{
  int v2; // edx
  unsigned int v4; // edx

  v2 = *(this + 4 * a2 + 111);
  if ( v2 == 0 )
    return false;
  v4 = (int)((uint64_t)(1321528399LL * (*(this + 4 * a2 + 112) - v2)) >> 32) >> 4;
  return v4 + (v4 >> 31) > 1;
}



// ------------------------------------------------------------
// 0x4581C0 sub_4581C0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4581C0(int *this, uint8_t *a2)
{
  uint8_t *result; // eax
  bool v4; // zf
  int v5; // eax
  int v6; // eax
  int v7; // esi
  int v8; // ebx
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // esi
  uint8_t *v13; // esi
  int v14; // esi
  uint32_t *v15; // ebx
  int v16; // eax
  uint32_t v17[3]; // [esp+Ch] [ebp-Ch]
  int v18; // [esp+20h] [ebp+8h]

  result = a2;
  v4 = a2 == (uint8_t *)*(this + 11);
  v17[0] = 40;
  v17[1] = 70;
  v17[2] = 100;
  if ( v4 )
  {
    v5 = sub_418DD0(0);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 152))(v5, 352, 22, dword_79C0B0);
    v6 = *(this + 152);
    v7 = -1;
    v18 = -1;
    if ( v6 == 1 )
    {
      v18 = *(this + 151);
    }
    else if ( v6 == 2 )
    {
      v7 = *(this + 151);
    }
    sub_491530(2, 0);
    if ( v7 != -1 )
    {
      v8 = dword_8F850C;
      v9 = sub_456480(dword_8F850C) == -1 ? 0 : *(uint32_t *)(v8 + 4 * sub_456480(v8) + 16);
      if ( v9 != sub_429830((uint16_t)word_77F804) )
      {
        v10 = sub_418DD0(v7 + 13);
        if ( v10 != 0 )
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)v10 + 152))(v10, 355, v17[v7], dword_79C0B0);
      }
    }
    if ( v18 != -1 )
    {
      v11 = sub_418DD0(v18 + 13);
      if ( v11 != 0 )
        (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)v11 + 152))(v11, 355, v17[v18], dword_79C0B0);
    }
    return (uint8_t *)sub_491630(2);
  }
  else if ( *(this + 152) != 1 )
  {
    v12 = dword_8F850C;
    v13 = sub_456480(dword_8F850C) == -1 ? nullptr : *(uint8_t **)(v12 + 4 * sub_456480(v12) + 16);
    result = (uint8_t *)sub_429830((uint16_t)word_77F804);
    if ( v13 == result )
    {
      v14 = 0;
      v15 = this + 147;
      do
      {
        result = (uint8_t *)*v15;
        if ( a2 == (uint8_t *)*v15 )
        {
          if ( result[17] != 0 && dword_79BE3C == *((uint32_t *)result + 3) )
          {
            sub_491530(2, 0);
            v16 = sub_418DD0(v14 + 13);
            if ( v16 != 0 )
              (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)v16 + 152))(v16, 355, v17[v14], dword_79C0B0);
            sub_491630(2);
            sub_457EC0(v14, 2);
          }
          result = (uint8_t *)*v15;
          if ( *(uint8_t *)(*v15 + 17) != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
          {
            sub_457EC0(v14, 1);
            result = sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
          }
        }
        ++v14;
        ++v15;
      }
      while ( v14 < 3 );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x458400 sub_458400
// ------------------------------------------------------------
char /*thiscall*/ sub_458400(int *this)
{
  int v2; // eax
  uint32_t *v3; // edi
  int v4; // edi
  uint32_t *v5; // edi
  int v6; // edi

  v2 = *(this + 160);
  switch ( v2 )
  {
    case 0:
      *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 216) = 0;
      v3 = (uint32_t *)dword_8F850C;
      if ( sub_456480((uint32_t *)dword_8F850C) == -1 )
        v4 = 0;
      else
        v4 = v3[sub_456480(v3) + 4];
      v2 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
      if ( v4 == v2 )
      {
        sub_423200(dword_8F7B08, 15);
        sub_423380(dword_8F7B08);
        LOBYTE(v2) = sub_454680(*(uint32_t *)(dword_8F7A24 + 24), *(this + 161), *(this + 162));
      }
      break;
    case 1:
      *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 216) = 1;
      v5 = (uint32_t *)dword_8F850C;
      if ( sub_456480((uint32_t *)dword_8F850C) == -1 )
        v6 = 0;
      else
        v6 = v5[sub_456480(v5) + 4];
      v2 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
      if ( v6 == v2 )
      {
        sub_423200(dword_8F7B08, 15);
        LOBYTE(v2) = sub_423380(dword_8F7B08);
      }
      break;
    case 2:
    case 3:
      LOBYTE(v2) = sub_45B060(1);
      break;
    default:
      break;
  }
  *(this + 160) = 3;
  *(this + 161) = -1;
  *(this + 162) = -1;
  return v2;
}



// ------------------------------------------------------------
// 0x458550 sub_458550
// ------------------------------------------------------------
int /*thiscall*/ sub_458550(int *this, uint8_t a2)
{
  int result; // eax
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // edi
  unsigned int v8; // eax
  int v9; // edi
  int v10; // edi

  result = *(this + 59);
  if ( result != 0 )
  {
    result = (*(this + 60) - result) / 40;
    if ( result != 0 )
    {
      v4 = *(this + 59);
      if ( v4 != 0 )
        v4 = (*(this + 60) - v4) / 40;
      v5 = 8 * (5 * v4 - 5);
      v6 = *(uint32_t *)(v5 + *(this + 59) + 8);
      if ( v6 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
          v6,
          105,
          133,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          (a2 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 14);
      v7 = *(this + 59);
      v8 = *(uint32_t *)(v7 + v5 + 36);
      v9 = v5 + v7;
      if ( v8 < 0x10 )
        v10 = v9 + 16;
      else
        v10 = *(uint32_t *)(v9 + 16);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        133,
        140,
        (a2 << 24) | 0xFFFFFF,
        v10);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x458670 sub_458670
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_458670(unsigned int *this, uint8_t a2)
{
  unsigned int result; // eax
  int v4; // ebx
  int i; // esi
  int v6; // ecx
  int v7; // eax
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // eax
  unsigned int v11; // [esp+8h] [ebp-4h]

  result = *(this + 63);
  v4 = 0;
  if ( result != 0 )
  {
    result = (int)(*(this + 64) - result) / 40;
    if ( result != 0 )
    {
      v11 = 0;
      for ( i = 177; ; i += 31 )
      {
        result = *(this + 63);
        if ( result == 0 )
          break;
        result = (int)(*(this + 64) - result) / 40;
        if ( v11 >= result || i >= 301 )
          break;
        v6 = *(uint32_t *)(*(this + 63) + v4 + 8);
        if ( v6 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
            v6,
            105,
            i,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            (a2 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        (*(void (/*thiscall*/ **)(int, unsigned int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 14);
        v7 = *(this + 63);
        v8 = *(uint32_t *)(v7 + v4 + 36);
        v9 = v4 + v7;
        if ( v8 < 0x10 )
          v10 = v9 + 16;
        else
          v10 = *(uint32_t *)(v9 + 16);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          133,
          i + 7,
          (a2 << 24) | 0xFFFFFF,
          v10);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        ++v11;
        v4 += 40;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4587C0 sub_4587C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4587C0(void *this, int a2)
{
  uint8_t v4; // bl
  int v5; // eax
  uint8_t v6; // bl
  int v7; // eax
  float v9; // [esp+14h] [ebp+8h]

  v4 = -36;
  if ( a2 <= 220 )
    v4 = a2;
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
  v9 = (double)sub_699000((int)this + 164) * 0.000033333334;
  sub_491530(2, 0);
  v6 = 120;
  if ( a2 <= 120 )
    v6 = a2;
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
// 0x4588C0 sub_4588C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4588C0(int *this, int a2)
{
  uint8_t v3; // bl
  int v4; // eax

  v3 = a2;
  if ( a2 >= 220 )
    v3 = -36;
  v4 = sub_418DD0(35);
  if ( v4 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v4 + 128))(
      v4,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (v3 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  return sub_458550(this, a2);
}



// ============================================================
// 【分区 8】奖励系统 II（0x458930-0x459ED0）
// REWARD_OPEN2（0x458930 自证）——二级奖励开启。
// ============================================================
// ------------------------------------------------------------
// 0x458930 sub_458930
// ------------------------------------------------------------
// 奖励箱二级开启 —— REWARD_OPEN2 自证（7308 行附近）
int /*userpurge*/ sub_458930@<eax>(uint32_t *a1@<ecx>, int a2@<esi>, unsigned int a3, int a4, int a5)
{
  int result; // eax
  uint32_t *v6; // ebx
  int v7; // edi
  uint32_t *v8; // esi
  int v9; // ecx
  uint8_t *v10; // eax
  int v11; // ecx
  uint32_t *v12; // eax
  uint32_t *v13; // ecx
  const char *v14; // eax
  int v15; // esi
  int v16; // eax
  int v17; // ecx
  int v18; // eax
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
  const char *v31; // [esp+14h] [ebp-88h]
  char Buffer[128]; // [esp+18h] [ebp-84h] BYREF
  int v33; // [esp+98h] [ebp-4h]
  uint8_t v34; // [esp+A4h] [ebp+8h]
  unsigned int v35; // [esp+A8h] [ebp+Ch]
  int v36; // [esp+ACh] [ebp+10h]
  int v37; // [esp+ACh] [ebp+10h]

  result = dword_796E50;
  v6 = a1;
  v33 = dword_796E50;
  if ( a1[1] == 8 )
  {
    result = a1[150];
    v30 = result;
  }
  else
  {
    v30 = -1;
  }
  v36 = a5 - 500;
  v7 = dword_6C6E00[a1[109]] + 158 * a4;
  if ( a3 < 4 )
  {
    result = a1[4 * a3 + 111];
    v8 = &a1[4 * a3];
    if ( result != 0 )
    {
      result = (v8[112] - result) / 52;
      if ( result != 0 )
      {
        if ( (uint8_t)sub_458160(a3) != 0 )
        {
          v9 = *(uint32_t *)(v8[111] + 56);
          if ( v9 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 128))(
              v9,
              v7 + 64,
              180,
              dword_79C0B0,
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
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v6 + 27);
          v12 = (uint32_t *)v8[111];
          if ( v12[21] < 0x10u )
            v13 = v12 + 16;
          else
            v13 = (uint32_t *)v12[16];
          (*(void (/*cdecl*/ **)(int, unsigned int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v7 - ((unsigned int)(5 * v12[20]) >> 1) + 78,
            217,
            v28,
            v13);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        }
        v23 = *(uint32_t *)(v8[111] + 40);
        v14 = (const char *)sub_422E70(476);
        sprintf(Buffer, v14, v23);
        v29 = v6 + 27;
        (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v6 + 27, a2);
        v15 = (v30 << 24) | 0xFFFFFF;
        (*(void (/*cdecl*/ **)(int, unsigned int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v7 - ((5 * strlen(Buffer)) >> 1) + 78,
          239,
          v15,
          Buffer);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        v26 = (uint64_t)sub_4049C0(0.0, 255.0, v36, 500);
        if ( v6[1] == 8 )
          LOBYTE(v26) = v30;
        if ( a4 == v6[135] )
          v16 = sub_418DD0(60);
        else
          v16 = sub_418DD0(61);
        if ( v16 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v16 + 128))(
            v16,
            v7 + 5,
            113,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)v26 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        v17 = *(uint32_t *)(dword_8F850C + 4 * a3 + 16);
        v27 = v17;
        if ( v17 != 0 )
        {
          v18 = sub_42B340(v17);
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, int))(*(uint32_t *)v18 + 388))(
            v18,
            v7 + 12,
            118,
            24,
            24,
            1065353216,
            v15);
          if ( *(uint32_t *)(v27 + 40) < 0x10u )
            v31 = (const char *)(v27 + 20);
          else
            v31 = *(const char **)(v27 + 20);
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v29);
          (*(void (/*cdecl*/ **)(int, unsigned int, int, int, const char *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v7 - ((5 * strlen(v31)) >> 1) + 93,
            126,
            v15,
            v31);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v29);
          v35 = strlen((const char *)sub_422E70(477));
          v19 = *(uint32_t *)dword_79C0B0;
          v20 = sub_422E70(478);
          (*(void (/*cdecl*/ **)(int, unsigned int, int, int, int))(v19 + 80))(
            dword_79C0B0,
            v7 - ((5 * v35) >> 1) + 93,
            126,
            v15,
            v20);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
          v6 = a1;
        }
        result = sub_458160(a3);
        if ( (uint8_t)result != 0 )
        {
          v21 = v36;
          if ( v36 < 800 )
          {
            if ( *((uint8_t *)v6 + a3 + 504) == 0 )
            {
              sub_432EA0("REWARD_OPEN2", -1, 0, 0);
              *((uint8_t *)v6 + a3 + 504) = 1;
            }
            v37 = sub_423A80(87, 93, v36, 500);
            v34 = -1;
            if ( v21 > 500 )
              v34 = sub_423A80(255, 0, v21, 800);
            sub_491530(2, 0);
            v22 = sub_418DD0(v37);
            sub_43B560(v7 - 4, 112, v22, 1065353216, 1065353216, 0, (v34 << 24) | 0xFFFFFF, 1333788672, 1333788672);
            return sub_491630(2);
          }
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x458E00 sub_458E00
// ------------------------------------------------------------
int /*thiscall*/ sub_458E00(uint32_t *this)
{
  int v2; // ebx
  uint32_t *v3; // edi
  int v4; // eax
  int v5; // ebx
  int result; // eax
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // eax
  bool v15; // cc
  int v16; // [esp+Ch] [ebp-14h]
  float v17; // [esp+10h] [ebp-10h]
  float v18; // [esp+10h] [ebp-10h]
  unsigned int v19; // [esp+10h] [ebp-10h]
  unsigned int *v20; // [esp+14h] [ebp-Ch]
  uint8_t v21; // [esp+18h] [ebp-8h]
  uint8_t v22[4]; // [esp+1Ch] [ebp-4h] BYREF

  v2 = 0;
  if ( (int)*(this + 109) > 0 )
  {
    v3 = this + 127;
    do
    {
      if ( *(this + 135) == -1 )
      {
        v4 = v3[4];
        if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) && *v3 == -1 )
        {
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1216))(dword_8F7C04);
          if ( *(this + 146) == -1 )
          {
            sub_423200(dword_8F7B08, 74);
            v22[0] = v2;
            sub_423290(v22, 1);
            sub_423380(dword_8F7B08);
            *(this + 146) = v2;
          }
        }
      }
      ++v2;
      ++v3;
    }
    while ( v2 < *(this + 109) );
  }
  if ( *(this + 1) == 8 )
  {
    v5 = *(this + 150);
    v21 = v5;
    if ( v5 < 200 )
      goto LABEL_13;
  }
  else
  {
    v21 = -1;
  }
  LOBYTE(v5) = -56;
LABEL_13:
  result = sub_418DD0(34);
  v7 = 0;
  if ( result != 0 )
    result = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
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
  v16 = 0;
  if ( (int)*(this + 109) > 0 )
  {
    v20 = this + 127;
    do
    {
      if ( *v20 != -1 )
      {
        v8 = sub_699000((int)(this + 41)) - v20[9];
        if ( v8 >= 250 )
        {
          if ( v8 >= 500 )
          {
            v19 = *v20;
            v12 = sub_418DD0(41);
            if ( v12 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v12 + 128))(
                v12,
                v7 + dword_6C6E00[*(this + 109)],
                163,
                dword_79C0B0,
                1065353216,
                1065353216,
                0,
                (v21 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
            v13 = *(this + 4 * v19 + 111);
            if ( v13 != 0 && (unsigned int)((*(this + 4 * v19 + 112) - v13) / 52) > 1 )
              v14 = sub_418DD0(43);
            else
              v14 = sub_418DD0(44);
            if ( v14 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
                v14,
                v7 + dword_6C6E00[*(this + 109)],
                163,
                dword_79C0B0,
                1065353216,
                1065353216,
                0,
                (v21 << 24) | 0xFFFFFF,
                1333788672,
                1333788672);
            sub_458930(this, (int)this, v19, v16, v8);
          }
          else
          {
            v18 = sub_4049C0(0.0, 1.0, v8 - 250, 250);
            v10 = sub_418DD0(41);
            if ( v10 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, float, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 156))(
                v10,
                v7 + dword_6C6E00[*(this + 109)],
                163,
                dword_79C0B0,
                COERCE_FLOAT(LODWORD(v18)),
                1065353216,
                0,
                -1,
                1117257728,
                1333788672);
            v11 = sub_418DD0(42);
            if ( v11 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, float, int, uint32_t, int, int, int))(*(uint32_t *)v11 + 156))(
                v11,
                v7 + dword_6C6E00[*(this + 109)],
                163,
                dword_79C0B0,
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
          v17 = sub_4049C0(1.0, 0.0, v8, 250);
          v9 = sub_418DD0(85);
          if ( v9 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, float, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 156))(
              v9,
              v7 + dword_6C6E00[*(this + 109)],
              163,
              dword_79C0B0,
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
      v15 = ++v16 < *(this + 109);
      ++v20;
    }
    while ( v15 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x459190 sub_459190
// ------------------------------------------------------------
int /*thiscall*/ sub_459190(int *this, char a2)
{
  int result; // eax
  int v4; // esi
  unsigned int i; // edi
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // edi
  int v11; // eax
  int v12; // ebx
  int v13; // edi
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // ebx
  int v20; // edi
  int v21; // esi
  int v22; // ebx
  int v23; // eax
  int v24; // [esp-14h] [ebp-28h]
  int v25; // [esp-14h] [ebp-28h]
  int v26; // [esp-10h] [ebp-24h]
  int v27; // [esp-10h] [ebp-24h]
  int v28; // [esp-Ch] [ebp-20h]
  int v29; // [esp+4h] [ebp-10h]
  int v31; // [esp+Ch] [ebp-8h]
  int v32; // [esp+10h] [ebp-4h]
  int v33; // [esp+10h] [ebp-4h]
  unsigned int v34; // [esp+1Ch] [ebp+8h]

  result = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16);
  if ( result != 0 )
  {
    v4 = *(uint32_t *)(result + 104);
    if ( v4 != 0 )
    {
      result = *(this + 163);
      if ( result == 0 )
      {
        for ( i = 0; ; ++i )
        {
          v6 = *(uint32_t *)(v4 + 120);
          result = v6 != 0 ? (*(uint32_t *)(v4 + 124) - v6) >> 2 : 0;
          if ( (int)i >= result )
            break;
          v7 = *(uint32_t *)(v4 + 120);
          if ( v7 != 0 && i < (*(uint32_t *)(v4 + 124) - v7) >> 2 )
            v8 = *(uint32_t *)(v7 + 4 * i);
          else
            v8 = 0;
          if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 340))(v8) == 48026 )
          {
            v9 = *(uint32_t *)(v4 + 120);
            if ( v9 != 0 && i < (*(uint32_t *)(v4 + 124) - v9) >> 2 )
              result = *(uint32_t *)(v9 + 4 * i);
            else
              result = 0;
            *(this + 163) = result;
            break;
          }
        }
      }
      v10 = *(this + 163);
      if ( v10 != 0 )
      {
        v28 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v10 + 36))(*(this + 163)) + 8);
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 120))(v10);
        if ( a2 != 0 )
        {
          v12 = sub_45E490(v11, v28);
          v13 = *(this + 163);
          v26 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 36))(v13) + 8);
          v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 128))(v13);
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 124))(v13);
          v15 = sub_45E4D0(v14, v24, v26, 0.0);
        }
        else
        {
          v16 = sub_45E490(v11, v28);
          v17 = *(this + 163);
          v32 = v16;
          v27 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 36))(v17) + 8);
          v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 128))(v17);
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 124))(v17);
          v12 = v32;
          v15 = sub_45E4D0(v18, v25, v27, 1.0);
        }
        v19 = v12 - 245;
        v20 = v15 - 345;
        v33 = v19;
        v31 = v20;
        result = sub_418DD0(a2 == 0);
        if ( result != 0 )
          result = (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
                     result,
                     v19,
                     v20,
                     dword_79C0B0,
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
                if ( v21 < v33 || v21 >= v33 + 500 || v20 < v31 || v20 >= v31 + 500 )
                {
                  v23 = sub_418DD0(2);
                  if ( v23 != 0 )
                    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v23 + 128))(
                      v23,
                      v21,
                      v20,
                      dword_79C0B0,
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
              while ( v22 < 640 );
              result = v29;
              v21 = v34;
            }
            result += 50;
            v29 = result;
            v20 = result;
          }
          while ( result < 480 );
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x459440 sub_459440
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_459440(uint32_t *this, uint32_t *a2)
{
  uint32_t *v3; // ecx

  *this = *a2;
  *(this + 1) = a2[1];
  v3 = this + 2;
  v3[6] = 15;
  v3[5] = 0;
  *((uint8_t *)v3 + 4) = 0;
  sub_4014D0((std::_String_base *)v3, a2 + 2, 0, -1);
  *(this + 9) = a2[9];
  *(this + 10) = a2[10];
  *(this + 11) = a2[11];
  *(this + 12) = a2[12];
  return this;
}



// ------------------------------------------------------------
// 0x4594A0 sub_4594A0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4594A0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t *v4; // edi
  int v5; // eax

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v5 = *(v3 - 13);
    v3 -= 13;
    v4 -= 13;
    *v4 = v5;
    v4[1] = v3[1];
    sub_4014D0((std::_String_base *)(v4 + 2), v3 + 2, 0, -1);
    v4[9] = v3[9];
    v4[10] = v3[10];
    v4[11] = v3[11];
    v4[12] = v3[12];
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x459500 sub_459500
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_459500(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = a2;
  for ( i = a1; i != a2; i += 13 )
  {
    *i = *a3;
    i[1] = a3[1];
    sub_4014D0((std::_String_base *)(i + 2), a3 + 2, 0, -1);
    i[9] = a3[9];
    i[10] = a3[10];
    result = a2;
    i[11] = a3[11];
    i[12] = a3[12];
  }
  return result;
}



// ------------------------------------------------------------
// 0x459560 sub_459560
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_459560(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_4594A0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x459580 sub_459580
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_459580(uint32_t *a1, uint32_t *a2, uint32_t *a3)
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
    v4[2] = v3[2];
    sub_4014D0((std::_String_base *)(v4 + 3), v3 + 3, 0, -1);
    v3 += 10;
    v4 += 10;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x4595D0 sub_4595D0
// ------------------------------------------------------------
int /*cdecl*/ sub_4595D0(uint32_t *a1, uint32_t *a2, int a3)
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
      *(uint32_t *)(v3 + 4) = a1[1];
      *(uint32_t *)(v3 + 32) = 15;
      *(uint32_t *)(v3 + 28) = 0;
      *(uint8_t *)(v3 + 12) = 0;
      sub_4014D0((std::_String_base *)(v3 + 8), a1 + 2, 0, -1);
      *(uint32_t *)(v3 + 36) = a1[9];
      *(uint32_t *)(v3 + 40) = a1[10];
      *(uint32_t *)(v3 + 44) = a1[11];
      *(uint32_t *)(v3 + 48) = a1[12];
    }
    v3 += 52;
    LOBYTE(v7) = 0;
    a1 += 13;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x459690 sub_459690
// ------------------------------------------------------------
int /*cdecl*/ sub_459690(int a1, uint32_t *a2)
{
  int result; // eax

  result = a1;
  if ( a1 != 0 )
  {
    *(uint32_t *)a1 = *a2;
    *(uint32_t *)(a1 + 4) = a2[1];
    *(uint32_t *)(a1 + 8) = a2[2];
    *(uint32_t *)(a1 + 36) = 15;
    *(uint32_t *)(a1 + 32) = 0;
    *(uint8_t *)(a1 + 16) = 0;
    return sub_4014D0((std::_String_base *)(a1 + 12), a2 + 3, 0, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x459700 sub_459700
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_459700(uint32_t *this)
{
  uint32_t *v2; // ecx

  v2 = this + 2;
  v2[6] = 15;
  v2[5] = 0;
  *((uint8_t *)v2 + 4) = 0;
  *this = 0;
  *(this + 1) = 0;
  sub_4015C0((void *)szPassword, 0);
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 9) = -16777216;
  return this;
}



// ------------------------------------------------------------
// 0x459770 sub_459770
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_459770(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_459580(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x459790 sub_459790
// ------------------------------------------------------------
int /*cdecl*/ sub_459790(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  int result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  v3 = a1;
  v5[5] = v5;
  v5[4] = a1;
  v6 = 0;
  while ( a2 != 0 )
  {
    v5[3] = v3;
    LOBYTE(v6) = 1;
    if ( v3 != 0 )
    {
      *(uint32_t *)v3 = *a3;
      *(uint32_t *)(v3 + 4) = a3[1];
      *(uint32_t *)(v3 + 32) = 15;
      *(uint32_t *)(v3 + 28) = 0;
      *(uint8_t *)(v3 + 12) = 0;
      sub_4014D0((std::_String_base *)(v3 + 8), a3 + 2, 0, -1);
      *(uint32_t *)(v3 + 36) = a3[9];
      *(uint32_t *)(v3 + 40) = a3[10];
      *(uint32_t *)(v3 + 44) = a3[11];
      result = a3[12];
      *(uint32_t *)(v3 + 48) = result;
    }
    v3 += 52;
    LOBYTE(v6) = 0;
    --a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x459860 sub_459860
// ------------------------------------------------------------
int /*cdecl*/ sub_459860(uint32_t *a1, uint32_t *a2, int a3)
{
  int v4; // edi
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  v4 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v6[7] = 0;
  while ( a1 != a2 )
  {
    sub_459690(v4, a1);
    v4 += 40;
    a1 += 10;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x459910 sub_459910
// ------------------------------------------------------------
int /*stdcall*/ sub_459910(int a1, int a2, uint32_t *a3)
{
  sub_459790(a1, a2, a3);
  return a1 + 52 * a2;
}



// ------------------------------------------------------------
// 0x459940 sub_459940
// ------------------------------------------------------------
int /*thiscall*/ sub_459940(int *this, int a2, unsigned int a3, int a4)
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
  int v20; // [esp-18h] [ebp-78h]
  int v21; // [esp-10h] [ebp-70h]
  int v22; // [esp-Ch] [ebp-6Ch]
  unsigned int v23; // [esp-8h] [ebp-68h]
  int v24; // [esp+0h] [ebp-60h] BYREF
  void *Block; // [esp+Ch] [ebp-54h]
  int *v26; // [esp+10h] [ebp-50h]
  char *v27; // [esp+14h] [ebp-4Ch]
  uint8_t v28[52]; // [esp+18h] [ebp-48h] BYREF
  int v29; // [esp+4Ch] [ebp-14h]
  int *v30; // [esp+50h] [ebp-10h]
  int v31; // [esp+5Ch] [ebp-4h]
  int v32; // [esp+68h] [ebp+8h]
  int v33; // [esp+6Ch] [ebp+Ch]
  int v34; // [esp+70h] [ebp+10h]

  v29 = dword_796E50;
  v30 = &v24;
  v26 = this;
  sub_459440(a4);
  v5 = *(this + 1);
  v6 = 0;
  v31 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 52;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - v5) / 52;
    else
      v8 = 0;
    if ( 82595524 - v8 < a3 )
      sub_44CAB0(this);
    if ( v5 != 0 )
      v9 = (*(this + 2) - v5) / 52;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = *(this + 2);
      v34 = v16;
      if ( (v16 - a2) / 52 >= a3 )
      {
        v32 = v16 - 52 * a3;
        *(this + 2) = sub_4595D0(v32, v16, v16);
        sub_459560(a2, v32, v34);
        sub_459500(a2, a2 + 52 * a3, v28);
      }
      else
      {
        sub_4595D0(a2, v16, a2 + 52 * a3);
        v23 = a3 - (*(this + 2) - a2) / 52;
        v22 = *(this + 2);
        LOBYTE(v31) = 3;
        sub_459910(v22, v23, v28);
        v18 = 52 * a3 + *(this + 2);
        *(this + 2) = v18;
        v31 = 0;
        sub_459500(a2, v18 - 52 * a3, v28);
      }
    }
    else
    {
      if ( 82595524 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(this + 2) - v5) / 52;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_458140(this);
      v33 = 52 * v10;
      v12 = (char *)operator new(52 * v10);
      v20 = *(this + 1);
      Block = v12;
      v27 = v12;
      LOBYTE(v31) = 1;
      v27 = (char *)sub_4595D0(v20, a2, v12);
      sub_459790(v27, a3, v28);
      v21 = *(this + 2);
      v27 += 52 * a3;
      sub_4595D0(a2, v21, v27);
      v13 = *(this + 1);
      v31 = 0;
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 52;
      v14 = v13 + a3;
      v15 = *(this + 1);
      if ( v15 != 0 )
      {
        sub_44C990(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v33];
      *(this + 2) = (int)&v12[52 * v14];
      *(this + 1) = (int)v12;
    }
  }
  v31 = -1;
  return sub_477AF0(v28);
}


// ------------------------------------------------------------
// 0x459C40 sub_459C40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_459C40(char **this, uint32_t *a2, uint32_t *a3)
{
  char *v4; // edi
  char *v5; // esi

  sub_459580(a3 + 10, *(this + 2), a3);
  v4 = *(this + 2);
  v5 = v4 - 40;
  do
  {
    sub_5014C0(v5);
    v5 += 40;
  }
  while ( v5 != v4 );
  *(this + 2) -= 40;
  *a2 = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x459CA0 sub_459CA0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_459CA0(int *this, uint32_t *a2, char *a3, uint32_t *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 52 != 0 )
    v6 = (int)&a3[-v5] / 52;
  else
    v6 = 0;
  sub_459940(this, a3, 1u, a4);
  *a2 = *(this + 1) + 52 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x459D10 sub_459D10
// ------------------------------------------------------------
int /*stdcall*/ sub_459D10(uint32_t *a1, uint32_t *a2, int a3)
{
  return sub_459860(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x459D30 sub_459D30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_459D30(int this)
{
  uint32_t *v2; // ecx
  int v3; // eax
  void **v4; // edi
  char *v5; // ebx
  uint32_t *v6; // eax
  int j; // ecx
  int *v8; // eax
  int k; // ecx
  int v10; // edi
  uint32_t *v11; // ecx
  uint32_t *result; // eax
  int v13; // esi
  char *i; // [esp+8h] [ebp-Ch]
  uint32_t *v15; // [esp+Ch] [ebp-8h]
  int v16; // [esp+10h] [ebp-4h]

  v2 = (uint32_t *)(this + 192);
  *v2 = 0;
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = 0;
  v2[4] = 0;
  v2[5] = 0;
  v2[6] = 0;
  v2[7] = 0;
  v2[8] = 0;
  v2[9] = 0;
  sub_55A050(this + 248);
  sub_55A050(this + 232);
  v3 = 0;
  *(uint32_t *)(this + 264) = 0;
  *(uint8_t *)(this + 432) = 0;
  memset((void *)(this + 268), 0, 0x2Cu);
  memset((void *)(this + 312), 0, 0x78u);
  *(uint32_t *)(this + 436) = 0;
  v16 = 0;
  v15 = (uint32_t *)(this + 508);
  v4 = (void **)(this + 444);
  do
  {
    v5 = (char *)*v4;
    if ( *v4 != nullptr )
    {
      for ( i = (char *)v4[1]; v5 != i; v5 += 52 )
        sub_477AF0(v5);
      j__free(*v4);
      v3 = v16;
    }
    *v4 = nullptr;
    v4[1] = nullptr;
    v4[2] = nullptr;
    *v15 = -1;
    *(uint8_t *)(this + v3++ + 504) = 0;
    v4 += 4;
    v16 = v3;
    ++v15;
  }
  while ( v3 < 4 );
  *(uint32_t *)(this + 540) = -1;
  *(uint32_t *)(this + 560) = 0;
  v6 = (uint32_t *)(this + 544);
  for ( j = 4; j != 0; --j )
  {
    *(uint8_t *)(*(v6 - 5) + 16) = 0;
    *v6 = 0;
    v6[5] = 1;
    ++v6;
  }
  v8 = (int *)(this + 588);
  for ( k = 3; k != 0; --k )
  {
    v10 = *v8++;
    *(uint8_t *)(v10 + 16) = 0;
  }
  *(uint8_t *)(this + 177) = 0;
  *(uint8_t *)(this + 178) = 0;
  sub_698F90(this + 164, 0, 0);
  v11 = *(uint32_t **)(this + 44);
  *(uint32_t *)(this + 584) = -1;
  *(uint32_t *)(this + 604) = -1;
  *(uint8_t *)(this + 580) = 0;
  *(uint32_t *)(this + 600) = 255;
  *(uint32_t *)(this + 608) = 0;
  *(uint32_t *)(this + 652) = 0;
  *(uint8_t *)(this + 660) = 0;
  result = sub_69A5F0(v11, 0, 0);
  v13 = *(uint32_t *)(this + 44);
  *(uint32_t *)(v13 + 28) = 640;
  *(uint32_t *)(v13 + 32) = 480;
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
unsigned int /*usercall*/ sub_459ED0@<eax>(int a1@<ecx>, double a2@<st0>)
{
  unsigned int result; // eax
  int v4; // ebx
  int v5; // eax
  int v6; // esi
  int v7; // ebx
  int v8; // ecx
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  unsigned int v14; // [esp+4h] [ebp-10h] BYREF
  int v15; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]
  int v17; // [esp+10h] [ebp-4h]

  result = *(uint32_t *)(a1 + 252);
  if ( result != 0 )
  {
    result = (int)(*(uint32_t *)(a1 + 256) - result) / 40;
    v14 = result;
    if ( result != 0 )
    {
      v4 = 0;
      v17 = sub_699000(a1 + 8) - *(uint32_t *)(a1 + 560);
      for ( i = 0; ; v4 = i )
      {
        result = *(uint32_t *)(a1 + 252);
        if ( result == 0 )
          break;
        result = (int)(*(uint32_t *)(a1 + 256) - result) / 40;
        if ( v4 >= result || v4 >= 4 )
          break;
        v5 = v17;
        v6 = 31 * v4 + 177;
        v15 = 255;
        v14 = 0;
        if ( v17 >= 0 )
        {
          if ( *(int *)(a1 + 264) < 11 && *(uint8_t *)(a1 + 432) == 0 )
          {
            *(uint32_t *)(a1 + 4 * (*(uint32_t *)(a1 + 264))++ + 268) = sub_699000(a1 + 8);
            sub_432EA0("REWARD_BOX_SET", -1, 0, 0);
            v5 = v17;
            *(uint8_t *)(a1 + 432) = 1;
          }
          if ( v4 != 0 )
          {
            sub_4049F0(0.0, 30.0, v5, 500, 1);
            v6 -= (uint64_t)a2;
          }
          else
          {
            v14 = (uint64_t)sub_4049C0(0.0, 150.0, v5, 500);
            a2 = sub_4049C0(255.0, 30.0, v17, 500);
            v15 = (uint64_t)a2;
          }
        }
        v7 = 40 * v4;
        v8 = *(uint32_t *)(*(uint32_t *)(a1 + 252) + v7 + 8);
        if ( v8 != 0 )
          (*(void (/*thiscall*/ **)(int, unsigned int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v8 + 128))(
            v8,
            v14 + 105,
            v6,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            ((uint8_t)v15 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 56);
        v9 = *(uint32_t *)(a1 + 252);
        v10 = *(uint32_t *)(v9 + v7 + 36);
        v11 = v7 + v9;
        if ( v10 < 0x10 )
          v12 = v11 + 16;
        else
          v12 = *(uint32_t *)(v11 + 16);
        (*(void (/*cdecl*/ **)(int, unsigned int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v14 + 133,
          v6 + 7,
          ((uint8_t)v15 << 24) | 0xFFFFFF,
          v12);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        if ( v17 < 0 && i == 0 )
        {
          a2 = sub_4049C0(50.0, 53.0, v17 + 125, 125);
          sub_491530(2, 0);
          v13 = sub_418DD0((uint64_t)a2);
          if ( v13 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
              v13,
              0,
              0,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              -587202561,
              1333788672,
              1333788672);
          sub_491630(2);
        }
        ++i;
      }
      if ( v17 >= 500 )
      {
        sub_459C40(&v14, *(uint32_t *)(a1 + 252));
        *(uint32_t *)(a1 + 560) = sub_699000(a1 + 8) + 125;
        *(uint8_t *)(a1 + 432) = 0;
        return (unsigned int)sub_432EA0("REWARD_ICON_OFF", -1, 0, 0);
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x45A1C0 sub_45A1C0
// ------------------------------------------------------------
int /*thiscall*/ sub_45A1C0(int this, int a2)
{
  int v4; // eax
  unsigned int v5; // ecx
  uint32_t *v7; // edi
  unsigned int v8; // eax
  uint32_t *v9; // eax
  int v10; // eax
  int v11; // ecx
  unsigned int v12; // eax
  unsigned int v13; // eax
  uint32_t *v14; // [esp+10h] [ebp+8h]

  if ( this == a2 )
    return this;
  v4 = *(uint32_t *)(a2 + 4);
  if ( v4 == 0 || (v5 = (*(uint32_t *)(a2 + 8) - v4) / 40) == 0 )
  {
    sub_55A050(this);
    return this;
  }
  v7 = *(uint32_t **)(this + 4);
  if ( v7 != nullptr )
    v8 = (*(uint32_t *)(this + 8) - (int)v7) / 40;
  else
    v8 = 0;
  if ( v5 > v8 )
  {
    if ( v7 != nullptr )
      v12 = (*(uint32_t *)(this + 12) - (int)v7) / 40;
    else
      v12 = 0;
    if ( v5 <= v12 )
    {
      v14 = (uint32_t *)(*(uint32_t *)(a2 + 4) + 40 * sub_5721D0(this));
      sub_459770(*(uint32_t **)(a2 + 4), v14, v7);
      *(uint32_t *)(this + 8) = sub_459860(v14, *(uint32_t **)(a2 + 8), *(uint32_t *)(this + 8));
      return this;
    }
    if ( v7 != nullptr )
    {
      sub_55A010(v7, *(uint32_t *)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v13 = sub_5721D0(a2);
    if ( sub_434AE0((uint32_t *)this, v13) != 0 )
      *(uint32_t *)(this + 8) = sub_459D10(*(uint32_t **)(a2 + 4), *(uint32_t **)(a2 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  v9 = sub_459580(*(uint32_t **)(a2 + 4), *(uint32_t **)(a2 + 8), v7);
  sub_55A010(v9, *(uint32_t *)(this + 8));
  v10 = *(uint32_t *)(a2 + 4);
  if ( v10 != 0 )
    v11 = *(uint32_t *)(this + 4) + 40 * ((*(uint32_t *)(a2 + 8) - v10) / 40);
  else
    v11 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 8) = v11;
  return this;
}



// ------------------------------------------------------------
// 0x45A340 sub_45A340
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45A340(int this, uint32_t *a2)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi
  uint32_t *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 52;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 52 )
    return sub_459CA0((int *)this, &a2, *(char **)(this + 8), a2);
  v5 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_459790(v5, 1, a2);
  *(uint32_t *)(this + 8) = v5 + 52;
  return result;
}



// ------------------------------------------------------------
// 0x45A3D0 sub_45A3D0
// ------------------------------------------------------------
int /*thiscall*/ sub_45A3D0(uint32_t *this)
{
  sub_45A1C0((int)(this + 62), *(this + 40) + 1024);
  sub_45A1C0((int)(this + 58), *(this + 40) + 1008);
  *(this + 160) = 3;
  *(this + 161) = -1;
  *(this + 162) = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x45A420 sub_45A420
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45A420(int this, int a2)
{
  uint32_t *result; // eax
  int v4; // ecx
  int v5; // esi
  int v6; // ebx
  int v7; // edi
  int v8; // eax
  int v9; // esi
  int v10; // edi
  int v11; // esi
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  int v17; // edi
  int v18; // edi
  uint32_t **v19; // edi
  int v20; // eax
  uint32_t *v21; // ebx
  int v22; // eax
  int v23; // esi
  int *v24; // esi
  int v25; // [esp+14h] [ebp+8h]

  *(uint32_t *)(this + 4) = a2;
  *(uint32_t *)(this + 4 * *(uint32_t *)(this + 4) + 192) = sub_699000(this + 164);
  *(uint8_t *)(this + 21) = 0;
  *(uint8_t *)(this + 22) = 0;
  sub_698F90(this + 8, 0, 0);
  result = *(uint32_t **)(this + 4);
  switch ( (unsigned int)result )
  {
    case 0u:
      result = (uint32_t *)sub_459D30(this);
      *(uint8_t *)(*(uint32_t *)(this + 44) + 16) = 0;
      return result;
    case 1u:
      result = *(uint32_t **)(this + 44);
      *((uint8_t *)result + 16) = 0;
      return result;
    case 2u:
      result = (uint32_t *)sub_45A3D0(this);
      goto LABEL_5;
    case 7u:
      *(uint8_t *)(*(uint32_t *)(this + 524) + 16) = 0;
      result = *(uint32_t **)(this + 528);
      *((uint8_t *)result + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(this + 532) + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(this + 536) + 16) = 0;
      return result;
    case 8u:
      v4 = dword_8F850C;
      v25 = 0;
      v5 = 16;
      break;
    case 9u:
      v19 = (uint32_t **)(this + 588);
      *(uint8_t *)(*(uint32_t *)(this + 588) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(this + 592) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(this + 596) + 16) = 1;
      v20 = *(uint32_t *)(this + 588);
      if ( *(uint8_t *)(this + 660) != 0 )
      {
        *(uint8_t *)(v20 + 17) = 1;
        *(uint8_t *)(*(uint32_t *)(this + 592) + 17) = 1;
      }
      else
      {
        *(uint8_t *)(v20 + 17) = 0;
        *(uint8_t *)(*(uint32_t *)(this + 592) + 17) = 0;
        v21 = *((uint32_t **)dword_8F8528 + 7);
        v22 = sub_422E70(475);
        sub_43BEE0(v21, v22, -6567706, 0, -1);
      }
      *(uint8_t *)(this + 625) = 0;
      *(uint8_t *)(this + 626) = 0;
      sub_698F90(this + 612, 0, 0);
      sub_69A5F0(*(uint32_t **)(this + 44), 380, 76);
      v23 = *(uint32_t *)(this + 44);
      *(uint32_t *)(v23 + 28) = 230;
      *(uint32_t *)(v23 + 32) = 95;
      v24 = (int *)&unk_6C6E14;
      do
      {
        result = sub_69A5F0(*v19, *v24, v24[1]);
        v24 += 2;
        ++v19;
      }
      while ( (int)v24 < (int)&unk_6C6E2C );
      return result;
    default:
LABEL_5:
      *(uint8_t *)(*(uint32_t *)(this + 44) + 16) = 1;
      return result;
  }
  while ( 1 )
  {
    v6 = *(uint32_t *)(v5 + v4);
    if ( v6 != 0 )
      break;
LABEL_16:
    v5 += 4;
    ++v25;
    if ( v5 >= 32 )
      goto LABEL_19;
  }
  v7 = v4;
  if ( sub_456480(v4) == -1 )
    v8 = 0;
  else
    v8 = *(uint32_t *)(v7 + 4 * sub_456480(v7) + 16);
  if ( v6 != v8
    || (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*(uint32_t *)(v5 + dword_8F850C) + 196) + 80))(*(uint32_t *)(*(uint32_t *)(v5 + dword_8F850C) + 196)) == 0 )
  {
    v4 = dword_8F850C;
    goto LABEL_16;
  }
  v4 = dword_8F850C;
  v9 = *(uint32_t *)(*(uint32_t *)(dword_8F850C + 4 * v25 + 16) + 196);
  if ( v9 != 0 )
  {
LABEL_26:
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 80))(v9);
    if ( result != nullptr )
    {
      v12 = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 80))(v9) + 132) + 44);
      v13 = *(uint32_t *)(v12 + 364);
      v14 = v12 + 360;
      if ( v13 != 0 )
        v15 = (*(uint32_t *)(v14 + 8) - v13) >> 5;
      else
        v15 = 0;
      v16 = 224 * v15;
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 120))(v9);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 152))(v9) == 1 )
        v18 = v17 + 80;
      else
        v18 = v17 - 80;
      if ( v18 > 200 )
      {
        if ( v18 >= v16 - 200 )
          v18 = v16 - 200;
      }
      else
      {
        v18 = 200;
      }
      result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 308))(v9);
      if ( (uint8_t)result != 0 )
        return (uint32_t *)sub_4E4A50(v9, 48026, 0, v18, 245, 0, 1, 0, 0, 0);
    }
    return result;
  }
LABEL_19:
  v10 = 0;
  v11 = 16;
  while ( 2 )
  {
    result = *(uint32_t **)(v11 + v4);
    if ( result == nullptr )
    {
LABEL_23:
      v11 += 4;
      ++v10;
      if ( v11 >= 32 )
        return result;
      continue;
    }
    break;
  }
  result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)result[49] + 80))(result[49]);
  if ( result == nullptr )
  {
    v4 = dword_8F850C;
    goto LABEL_23;
  }
  result = (uint32_t *)dword_8F850C;
  v9 = *(uint32_t *)(*(uint32_t *)(dword_8F850C + 4 * v10 + 16) + 196);
  if ( v9 != 0 )
    goto LABEL_26;
  return result;
}


// ------------------------------------------------------------
// 0x45A750 sub_45A750
// ------------------------------------------------------------
int /*thiscall*/ sub_45A750(void *this, int a2, int a3, int a4)
{
  void *v5; // eax
  int v6; // eax
  uint32_t v8[14]; // [esp+Ch] [ebp-44h] BYREF
  int v9; // [esp+4Ch] [ebp-4h]

  v8[13] = dword_796E50;
  sub_459700(v8);
  v9 = 0;
  v8[1] = sub_4F33A0(a2);
  v5 = (void *)sub_4F2CE0(a2);
  sub_4015C0(v5, strlen((const char *)v5));
  v8[10] = a3;
  v6 = sub_4F2D60(a2);
  v8[9] = sub_4F2DF0(v6);
  v8[11] = sub_4F2DA0(a2);
  sub_45A340((int)this + 16 * a4 + 440, v8);
  v9 = -1;
  return sub_477AF0(v8);
}



// ------------------------------------------------------------
// 0x45A820 sub_45A820
// ------------------------------------------------------------
void */*thiscall*/ sub_45A820(uint32_t *this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // edi
  uint32_t **v5; // esi

  sub_45A420((int)this, 6);
  v2 = *(this + 109);
  v3 = 0;
  if ( v2 > 0 )
  {
    v4 = 0;
    v5 = (uint32_t **)(this + 131);
    do
    {
      sub_69A5F0(*v5, v4 + dword_6C6E00[v2], 163);
      *((uint8_t *)*v5 + 16) = 1;
      v2 = *(this + 109);
      ++v3;
      ++v5;
      v4 += 158;
    }
    while ( v3 < v2 );
  }
  return sub_432EA0("REWARD_DIVIDE_SET", -1, 0, 0);
}



// ------------------------------------------------------------
// 0x45A8A0 sub_45A8A0
// ------------------------------------------------------------
int /*thiscall*/ sub_45A8A0(int this, void *Block)
{
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  int v5; // eax
  uint32_t *v6; // edi
  int v7; // eax
  bool v8; // cc
  uint32_t *v9; // edi
  uint32_t *v10; // eax
  bool v11; // zf
  uint32_t *v12; // edi
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  void *v16; // eax
  uint32_t *v17; // eax
  int v18; // edi
  int v20; // [esp+Ch] [ebp-2Ch]
  void *v21; // [esp+10h] [ebp-28h]
  void *v22; // [esp+14h] [ebp-24h]
  int v23; // [esp+18h] [ebp-20h]
  int v24; // [esp+1Ch] [ebp-1Ch]
  int v25; // [esp+20h] [ebp-18h]
  int v26; // [esp+24h] [ebp-14h]
  int v27; // [esp+28h] [ebp-10h]
  int v28; // [esp+34h] [ebp-4h]
  char *Blocka; // [esp+40h] [ebp+8h]
  char *Blockb; // [esp+40h] [ebp+8h]
  int *Blockc; // [esp+40h] [ebp+8h]

  *(uint32_t *)(this + 160) = Block;
  *(uint32_t *)(this + 48) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 128);
  *(uint32_t *)(this + 52) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 184);
  *(uint32_t *)(this + 656) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                              dword_8F84B8,
                              "Common/ActiveStatus/Blind1.img");
  v3 = operator new(0x68u);
  v28 = 0;
  if ( v3 != nullptr )
    v4 = sub_426BD0(v3);
  else
    v4 = nullptr;
  *(uint32_t *)(this + 44) = v4;
  *((uint32_t *)v4 + 7) = 640;
  *((uint32_t *)v4 + 8) = 480;
  v5 = *(uint32_t *)(this + 44);
  v28 = -1;
  *(uint32_t *)(v5 + 68) = this;
  v20 = 61;
  v21 = (void *)71;
  Blocka = nullptr;
  v27 = this + 36;
  do
  {
    v6 = operator new(0x2Cu);
    v22 = v6;
    v28 = 1;
    if ( v6 != nullptr )
    {
      v26 = *(uint32_t *)(this + 48);
      v25 = dword_79C0B0;
      *((uint8_t *)v6 + 4) = 0;
      LOBYTE(v28) = 2;
      *v6 = &nengine::CNNumberSet::`vftable';
      sub_699E20(v6);
      sub_699E40(v25, v26, *(&v20 + (uint32_t)Blocka), 1);
    }
    else
    {
      v6 = nullptr;
    }
    v7 = v27;
    *(uint32_t *)v27 = v6;
    v6[10] = -5;
    *(uint32_t *)(*(uint32_t *)v7 + 36) = 0;
    *(uint8_t *)(*(uint32_t *)v7 + 24) = 0;
    v8 = (int)(Blocka + 1) < 2;
    v28 = -1;
    ++Blocka;
    v27 = v7 + 4;
  }
  while ( v8 );
  *(uint8_t *)(this + 56) = 0;
  *(uint8_t *)(this + 57) = 0;
  *(uint8_t *)(this + 58) = 0;
  *(uint8_t *)(this + 59) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 76) = 12;
  *(uint32_t *)(this + 84) = 1600;
  *(uint32_t *)(this + 72) = 6;
  *(uint32_t *)(this + 104) = dword_99FCCC;
  *(uint32_t *)(this + 84) = 180;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 60) = -16777216;
  *(uint32_t *)(this + 136) = 1600;
  *(uint8_t *)(this + 108) = 0;
  *(uint8_t *)(this + 109) = 0;
  *(uint8_t *)(this + 110) = 0;
  *(uint8_t *)(this + 111) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 6;
  *(uint32_t *)(this + 128) = 12;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 156) = dword_99FCCC;
  *(uint32_t *)(this + 136) = 120;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 112) = -16777216;
  *(uint8_t *)(this + 110) = 1;
  sub_698F90(this + 164, 0, 0);
  Blockb = (char *)(this + 524);
  v27 = 4;
  do
  {
    v9 = operator new(0x84u);
    v22 = v9;
    v28 = 3;
    if ( v9 != nullptr )
    {
      v25 = *(uint32_t *)(this + 48);
      sub_426BD0(v9);
      LOBYTE(v28) = 4;
      *v9 = &nengine::CNButton::`vftable';
      sub_69C780(v9);
      sub_69C7B0(v25, 85, 85, 85, -1, 0, 0);
      v10 = v9;
    }
    else
    {
      v10 = nullptr;
    }
    *(uint32_t *)Blockb = v10;
    v28 = -1;
    sub_69A840(v10);
    *(uint32_t *)(*(uint32_t *)Blockb + 68) = this;
    v11 = v27 == 1;
    Blockb += 4;
    --v27;
  }
  while ( !v11 );
  Blockc = (int *)&unk_6C6E34;
  v27 = this + 588;
  do
  {
    v12 = operator new(0x84u);
    v21 = v12;
    v28 = 5;
    if ( v12 != nullptr )
    {
      v13 = *Blockc;
      v25 = Blockc[1];
      v14 = *(Blockc - 1);
      v26 = v13;
      v15 = *(Blockc - 2);
      v16 = *(void **)(this + 52);
      v24 = v14;
      v23 = v15;
      v22 = v16;
      sub_426BD0(v12);
      LOBYTE(v28) = 6;
      *v12 = &nengine::CNButton::`vftable';
      sub_69C780(v12);
      sub_69C7B0(v22, v23, v24, v26, v25, 0, 0);
      v17 = v12;
    }
    else
    {
      v17 = nullptr;
    }
    v18 = v27;
    *(uint32_t *)v27 = v17;
    v28 = -1;
    sub_69A840(v17);
    *(uint32_t *)(*(uint32_t *)v18 + 68) = this;
    v8 = (int)(Blockc + 4) < 7106148;
    v27 = v18 + 4;
    Blockc += 4;
  }
  while ( v8 );
  return sub_45A420(0);
}


// ============================================================
// 【分区 10】CNRDReward 奖励主类（0x45AC20-0x45B4A0）
// CNRDReward__vmt0（RTTI 自证；REWARD_BOX_GLITTER 自证）。
// ============================================================
// ------------------------------------------------------------
// 0x45AC20 CNRDReward__vmt0
// ------------------------------------------------------------
// CNRDReward::vmt0 —— 奖励主类帧处理（RTTI 自证；REWARD_BOX_GLITTER 自证）
int /*userpurge*/ sub_45AC20@<eax>(int a1@<ecx>, double a2@<st0>, uint8_t *a3)
{
  int result; // eax
  int v5; // eax
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // ebx
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edi
  int v16; // eax

  result = *(uint32_t *)(a1 + 4);
  if ( result == 9 )
    return (int)sub_4581C0((int *)a1, a3);
  if ( a3 != *(uint8_t **)(a1 + 44) )
  {
LABEL_51:
    if ( *(uint32_t *)(a1 + 4) == 6 )
      return sub_457AA0((int *)a1, (int)a3);
    return result;
  }
  if ( result >= 2 )
  {
    v5 = result == 8 ? *(uint32_t *)(a1 + 600) : 255;
    sub_4587C0((void *)a1, v5);
    if ( *(uint32_t *)(a1 + 4) == 2 )
    {
      v6 = sub_699000(a1 + 8);
      v7 = sub_423A80(0, 255, v6, 800);
      v8 = sub_418DD0(84);
      sub_43B560(0, 0, v8, 1065353216, 1065353216, 0, ((uint8_t)v7 << 24) | 0xFFFFFF, 1333788672, 1333788672);
      sub_4588C0(v7);
      sub_458670(v7);
      sub_457040(v7);
      if ( *(uint32_t *)(a1 + 4) == 2 && sub_699000(a1 + 8) >= 800 )
      {
        sub_45A420(*(uint32_t *)(a1 + 4) + 1);
        result = sub_699000(a1 + 8) + 125;
        *(uint32_t *)(a1 + 560) = result;
        return result;
      }
    }
  }
  v9 = *(uint32_t *)(a1 + 4);
  if ( v9 >= 3 )
  {
    if ( v9 == 8 )
      v10 = *(uint32_t *)(a1 + 600);
    else
      LOBYTE(v10) = -1;
    v11 = sub_418DD0(84);
    if ( v11 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v11 + 128))(
        v11,
        0,
        0,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)v10 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    if ( *(uint32_t *)(a1 + 4) == 3 )
    {
      sub_4588C0(255);
      sub_459ED0(a1, a2);
      sub_457090(a1);
      sub_457040(255);
    }
    v9 = *(uint32_t *)(a1 + 4);
    if ( v9 == 3 && sub_5721D0(a1 + 248) == 0 )
    {
      sub_45A420(4);
      memset((void *)(a1 + 268), 1u, 0x2Cu);
      sub_457C60(a1);
      return (int)sub_432EA0("REWARD_BOX_GLITTER", -1, 0, 0);
    }
  }
  if ( v9 >= 4 )
  {
    if ( v9 == 4 )
    {
      v12 = sub_699000(a1 + 8);
      v13 = sub_423A80(255, 0, v12, 1800);
      sub_4588C0(v13);
      sub_4575F0(a1, a2);
      sub_457370((int *)a1);
      sub_457160((void *)a1);
    }
    if ( *(uint32_t *)(a1 + 4) == 5 )
      sub_457890((uint32_t *)a1);
    sub_457CB0(a1, a2);
    if ( *(uint32_t *)(a1 + 4) == 4 && sub_699000(a1 + 8) >= 1800 )
    {
      sub_432EA0("REWARD_DIVIDE", -1, 0, 0);
      return sub_45A420(*(uint32_t *)(a1 + 4) + 1);
    }
  }
  if ( *(uint32_t *)(a1 + 4) == 5 && sub_699000(a1 + 8) >= 1200 && *(uint8_t *)(a1 + 580) == 0 )
    return sub_4577C0(a1);
  v14 = *(uint32_t *)(a1 + 4);
  if ( v14 >= 6 )
  {
    sub_458E00((uint32_t *)a1);
    if ( *(uint32_t *)(a1 + 4) == 6 )
      sub_457DD0(a1);
    v14 = *(uint32_t *)(a1 + 4);
    if ( v14 == 6 )
    {
      v15 = sub_699000(a1 + 164) - *(uint32_t *)(a1 + 216);
      result = sub_457790(a1);
      if ( (uint8_t)result == 1 || v15 >= 4000 )
        return sub_45A420(*(uint32_t *)(a1 + 4) + 1);
      return result;
    }
  }
  if ( v14 == 7 && sub_699000(a1 + 8) >= 5000 )
    return sub_45A420(*(uint32_t *)(a1 + 4) + 1);
  result = *(uint32_t *)(a1 + 4);
  if ( result >= 8 )
  {
    result = sub_699000(a1 + 8);
    if ( result <= 1000 )
    {
      v16 = sub_699000(a1 + 8);
      result = sub_423A80(255, 0, v16, 1000);
      *(uint32_t *)(a1 + 600) = result;
    }
    if ( *(uint32_t *)(a1 + 4) == 8 )
    {
      result = sub_699000(a1 + 8);
      if ( result >= 1500 )
        return sub_45A420(*(uint32_t *)(a1 + 4) + 1);
    }
  }
  goto LABEL_51;
}


// ------------------------------------------------------------
// 0x45AFD0 sub_45AFD0
// ------------------------------------------------------------
bool /*cdecl*/ sub_45AFD0(char a1)
{
  return sub_472F90(a1) >= 1;
}



// ------------------------------------------------------------
// 0x45AFF0 sub_45AFF0
// ------------------------------------------------------------
int /*thiscall*/ sub_45AFF0(int this)
{
  int result; // eax

  result = 0;
  if ( *(uint8_t *)(this + 4) == 0 )
  {
    *(uint32_t *)(this + 12) = 0;
    *(uint32_t *)(this + 44) = 0;
    *(uint32_t *)(this + 48) = 0;
    *(uint32_t *)(this + 112) = 0;
    *(uint8_t *)(this + 116) = 0;
    *(uint32_t *)(this + 100) = 0;
    *(uint32_t *)(this + 104) = 0;
    *(uint32_t *)(this + 108) = 0;
    *(uint8_t *)(this + 117) = 0;
    *(uint32_t *)(this + 120) = 0;
    *(uint32_t *)(this + 152) = 0;
    *(uint32_t *)(this + 156) = 0;
    *(uint32_t *)(this + 160) = 0;
    *(uint32_t *)(this + 164) = 0;
    *(uint32_t *)(this + 168) = 0;
    *(uint32_t *)(this + 172) = -1;
    *(uint8_t *)(this + 189) = 0;
    *(uint8_t *)(this + 190) = 0;
    *(uint32_t *)(this + 204) = 0;
    *(uint32_t *)(this + 208) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x45B060 sub_45B060
// ------------------------------------------------------------
void */*thiscall*/ sub_45B060(uint32_t *this, int a2)
{
  int v2; // ecx
  void *result; // eax

  *(this + 30) = a2;
  v2 = (int)(this + 31);
  *(uint8_t *)(v2 + 13) = 0;
  *(uint8_t *)(v2 + 14) = 0;
  sub_698F90(v2, 0, 0);
  result = (void *)(a2 - 1);
  if ( a2 == 1 )
  {
    result = dword_8F8528;
    *((uint32_t *)dword_8F8528 + 621) = 255;
  }
  return result;
}



// ------------------------------------------------------------
// 0x45B0A0 sub_45B0A0
// ------------------------------------------------------------
void /*thiscall*/ sub_45B0A0(uint32_t *this)
{
  uint32_t *v2; // edx
  int v3; // ecx

  v2 = (uint32_t *)*(this + 41);
  if ( v2 != nullptr )
  {
    if ( *(this + 42) != 0 )
    {
      if ( (uint8_t)sub_5460A0(*v2, *(this + 42)) != 0 )
      {
LABEL_9:
        *(this + 41) = 0;
        return;
      }
    }
    else if ( (uint8_t)sub_546120(*((uint32_t *)dword_8F8528 + 11)) != 0 )
    {
      *(this + 41) = 0;
      return;
    }
    v3 = sub_44E8D0((char *)dword_8F8528, (void *)0x1F, 0, 0);
    if ( *(this + 42) == 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v3 + 60))(v3, *(this + 41));
      *(this + 41) = 0;
      return;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)v3 + 56))(v3, *(this + 41), *(this + 42));
    goto LABEL_9;
  }
}



// ------------------------------------------------------------
// 0x45B140 sub_45B140
// ------------------------------------------------------------
int /*thiscall*/ sub_45B140(int *this)
{
  int result; // eax

  result = *(this + 11);
  if ( *(uint32_t *)(result + 44) != 0 )
  {
    result = dword_8F7C08;
    if ( dword_8F7C08 != 0 )
    {
      result = sub_48C860(dword_8F7C08);
      *(this + 27) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x45B170 sub_45B170
// ------------------------------------------------------------
bool /*stdcall*/ sub_45B170(int ArgList)
{
  int v1; // eax
  int v3; // eax

  v1 = sub_4CE8A0(ArgList);
  if ( v1 != 0 )
  {
    v3 = *(uint32_t *)(v1 + 92);
    return v3 == -1 || sub_472F90(v3) >= 1;
  }
  else
  {
    off_77F3FC(aCriticalError_5, ArgList);
    return false;
  }
}



// ------------------------------------------------------------
// 0x45B1C0 sub_45B1C0
// ------------------------------------------------------------
int /*thiscall*/ sub_45B1C0(uint32_t *this)
{
  if ( (uint8_t)sub_45E680(*(this + 38)) == 0 )
    *(this + 38) = 0;
  return *(this + 38);
}



// ------------------------------------------------------------
// 0x45B1F0 sub_45B1F0
// ------------------------------------------------------------
int /*thiscall*/ sub_45B1F0(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 33) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
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
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 33) == 0 );
        if ( *(uint8_t *)(result + 33) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 33) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x45B250 sub_45B250
// ------------------------------------------------------------
char /*thiscall*/ sub_45B250(int this)
{
  char result; // al

  result = *(uint8_t *)(this + 4);
  if ( result != 0 )
  {
    *(uint8_t *)(this + 29) = 0;
    *(uint8_t *)(this + 30) = 0;
    sub_698F90(this + 16, 0, 0);
    *(uint32_t *)(this + 112) = -1000;
    *(uint8_t *)(this + 116) = 0;
    *(uint32_t *)(this + 156) = 0;
    *(uint32_t *)(this + 120) = 0;
    *(uint8_t *)(this + 137) = 0;
    *(uint8_t *)(this + 138) = 0;
    sub_698F90(this + 124, 0, 0);
    result = sub_424A40(*(uint32_t **)(this + 44), dword_8F7C08);
    *(uint32_t *)(this + 216) = -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x45B2B0 sub_45B2B0
// ------------------------------------------------------------
char /*thiscall*/ sub_45B2B0(int this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  uint64_t v5; // rax
  int v7; // ebx
  int v8; // eax
  uint64_t v9; // rax
  int v10; // [esp+Ch] [ebp-10h] BYREF
  int v11; // [esp+10h] [ebp-Ch]
  int v12; // [esp+14h] [ebp-8h]
  int v13; // [esp+18h] [ebp-4h]

  v2 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 44) + 108) + 64);
  if ( v2 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v2 + 152))(v2, 0, 0, dword_79C0B0);
  sub_4938F0(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 44) + 108) + 60));
  sub_491D00(dword_79C0B0, 320, 240, 0.0);
  v3 = *(uint32_t *)(this + 172);
  switch ( v3 )
  {
    case 0:
      sub_698F90(this + 176, 0, 0);
      v4 = sub_699000(this + 176);
      v5 = (uint64_t)sub_4049C0(255.0, 0.0, v4, 300);
      v10 = 0;
      v11 = 0;
      v12 = 640;
      v13 = 480;
      if ( v2 != 0 )
        (*(void (/*thiscall*/ **)(int, int *, int *, int, uint32_t, int))(*(uint32_t *)v2 + 136))(
          v2,
          &v10,
          &v10,
          dword_79C0B0,
          0,
          (uint8_t)v5 << 24);
      if ( sub_699000(this + 176) >= 300 )
      {
        *(uint32_t *)(this + 172) = 1;
        *(uint8_t *)(this + 189) = 0;
        *(uint8_t *)(this + 190) = 0;
        sub_698F90(this + 176, 1500, 0);
      }
      return 0;
    case 1:
      v7 = *(uint32_t *)(this + 200);
      if ( sub_699000(this + 176) < v7 )
        return 0;
      *(uint32_t *)(this + 172) = 2;
      *(uint8_t *)(this + 189) = 0;
      *(uint8_t *)(this + 190) = 0;
      return 0;
    case 2:
      sub_698F90(this + 176, 0, 0);
      v8 = sub_699000(this + 176);
      v9 = (uint64_t)sub_4049C0(0.0, 255.0, v8, 300);
      v10 = 0;
      v11 = 0;
      v12 = 640;
      v13 = 480;
      if ( v2 != 0 )
        (*(void (/*thiscall*/ **)(int, int *, int *, int, uint32_t, int))(*(uint32_t *)v2 + 136))(
          v2,
          &v10,
          &v10,
          dword_79C0B0,
          0,
          (uint8_t)v9 << 24);
      if ( sub_699000(this + 176) < 300 )
        return 0;
      sub_472B30(1, 0);
      *(uint8_t *)(this + 117) = 1;
      *(uint32_t *)(this + 172) = -1;
      return 1;
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
int /*thiscall*/ CNRoomListModule__vmt8(uint32_t *this)
{
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B0 + 28))(dword_79C0B0, 0);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 84))(dword_79C0B0);
  if ( *(this + 43) == -1 )
    sub_69AB00(*(this + 3));
  else
    sub_45B2B0((int)this);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 88))(dword_79C0B0);
  return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_79C0A4 + 4))(dword_79C0A4, 0, 0);
}



// ------------------------------------------------------------
// 0x45B500 sub_45B500
// ------------------------------------------------------------
char /*thiscall*/ sub_45B500(uint32_t *this)
{
  int v1; // eax
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
  int v16; // [esp+84h] [ebp-4h]

  v16 = dword_796E50;
  v1 = *(this + 26);
  if ( v1 == 0 || *(uint32_t *)(v1 + 32) != 4 )
    return 0;
  v3 = **(uint32_t **)(v1 + 40);
  v4 = (uint32_t *)sub_4CE8A0(v3);
  if ( v4 == nullptr )
  {
    off_77F3FC("CRITICAL ERROR : WORLD MAP LOAD FAIL %d", v3);
    return 0;
  }
  v5 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  v6 = sub_41A5E0(v5 + 53);
  v7 = (uint32_t *)v4[17];
  v14 = v6;
  for ( i = -1; v7 != (uint32_t *)v4[18]; v7 += 2 )
  {
    if ( v7[1] == -1 )
    {
      v9 = sub_476B60(*v7);
      if ( v9 != 0 )
      {
        v11 = *(uint32_t *)(v9 + 92);
        if ( v14 >= v11 )
          return 1;
        if ( i == -1 || i > v11 )
          i = v11;
      }
      else
      {
        if ( v4[7] < 0x10u )
          v10 = v4 + 2;
        else
          v10 = (uint32_t *)v4[2];
        off_77F3FC(aCriticalError_6, v10, *v7);
      }
    }
  }
  if ( v4[7] < 0x10u )
    v12 = v4 + 2;
  else
    v12 = (uint32_t *)v4[2];
  v13 = sub_422E70(535);
  sprintf(Buffer, v13, v12, i);
  sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
  return 0;
}



// ------------------------------------------------------------
// 0x45B660 sub_45B660
// ------------------------------------------------------------
int **/*thiscall*/ sub_45B660(int **this, int **a2, uint32_t *a3)
{
  int *v3; // edx
  int *v4; // eax

  v3 = *(this + 1);
  v4 = (int *)v3[1];
  while ( *((uint8_t *)v4 + 69) == 0 )
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
// 0x45B6D0 sub_45B6D0
// ------------------------------------------------------------
int **/*thiscall*/ sub_45B6D0(int **this, int **a2, uint32_t *a3)
{
  int *v3; // edx
  int *v4; // eax

  v3 = *(this + 1);
  v4 = (int *)v3[1];
  while ( *((uint8_t *)v4 + 33) == 0 )
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
// 0x45B740 sub_45B740
// ------------------------------------------------------------
int */*thiscall*/ sub_45B740(int **this, int *a2, char a3, int *a4, int a5)
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
// 0x45B8F0 sub_45B8F0
// ------------------------------------------------------------
void /*noreturn*/ sub_45B8F0()
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
// 0x45B960 sub_45B960
// ------------------------------------------------------------
int /*thiscall*/ sub_45B960(int **this, int a2, int *a3)
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
      v10 = *sub_45B740(this, (int *)&a3, 1, v5, (int)v3);
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
    v12 = *sub_45B740(this, (int *)&a3, v13, v5, (int)v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x45BA20 sub_45BA20
// ------------------------------------------------------------
char /*thiscall*/ sub_45BA20(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x3FFFFFFF )
    sub_45B8F0(this);
  v4 = (char *)operator new(4 * a2);
  *(this + 3) = &v4[4 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x45BA80 sub_45BA80
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_45BA80(int this, int Src, unsigned int a3, int *a4)
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
      sub_45B8F0(this);
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
// 0x45BC60 sub_45BC60
// ------------------------------------------------------------
int */*thiscall*/ sub_45BC60(int this, int *a2, int *a3, int *a4)
{
  int *v6; // eax
  int *v7; // esi
  int *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_45B740((int **)this, a2, 1, *(int **)(this + 4), (int)a4);
    return a2;
  }
  v6 = *(int **)(this + 4);
  v7 = a4;
  if ( a3 == (int *)*v6 )
  {
    if ( *a4 < a3[3] )
    {
      sub_45B740((int **)this, a2, 1, a3, (int)a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( a3 == v6 )
  {
    v8 = (int *)v6[2];
    if ( v8[3] < *a4 )
    {
      sub_45B740((int **)this, a2, 0, v8, (int)a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( *a4 >= a3[3] || (a4 = a3, sub_4A3B30(&a4), a4[3] >= *v7) )
  {
    if ( a3[3] >= *v7 || (a4 = a3, sub_41C5E0(&a4), a4 != *(int **)(this + 4)) && *v7 >= a4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_45B960((int **)this, (int)v10, v7);
      *a2 = v9;
      return a2;
    }
    if ( *(uint8_t *)(a3[2] + 21) != 0 )
      sub_45B740((int **)this, a2, 0, a3, (int)v7);
    else
      sub_45B740((int **)this, a2, 1, a4, (int)v7);
    return a2;
  }
  else
  {
    if ( *(uint8_t *)(a4[2] + 21) != 0 )
      sub_45B740((int **)this, a2, 0, a4, (int)v7);
    else
      sub_45B740((int **)this, a2, 1, a3, (int)v7);
    return a2;
  }
}



// ------------------------------------------------------------
// 0x45BDC0 sub_45BDC0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45BDC0(uint32_t *this, int a2)
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
  if ( sub_45BA20(this, v4) != 0 )
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
// 0x45BE60 sub_45BE60
// ------------------------------------------------------------
int /*thiscall*/ sub_45BE60(int **this, int *a2)
{
  int *v2; // edx
  int v3; // eax
  int v5[2]; // [esp+Ch] [ebp-8h] BYREF

  v2 = *(this + 1);
  v3 = v2[1];
  while ( *(uint8_t *)(v3 + 21) == 0 )
  {
    if ( *(uint32_t *)(v3 + 12) >= *a2 )
    {
      v2 = (int *)v3;
      v3 = *(uint32_t *)v3;
    }
    else
    {
      v3 = *(uint32_t *)(v3 + 8);
    }
  }
  if ( v2 != *(this + 1) && *a2 >= v2[3] )
    return (int)(v2 + 4);
  v5[0] = *a2;
  v5[1] = 0;
  return *sub_45BC60((int)this, (int *)&a2, v2, v5) + 16;
}



// ------------------------------------------------------------
// 0x45BEE0 sub_45BEE0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_45BEE0(int a1, int a2, int a3, uint32_t *a4, char a5)
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
    sub_45BDC0(v5 + 4, (int)(a4 + 1));
    *((uint8_t *)v6 + 32) = a5;
    *((uint8_t *)v6 + 33) = 0;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x45BF80 sub_45BF80
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45BF80(int *this, uint32_t *a2, char a3, uint32_t *a4, uint32_t *a5)
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
  v6 = sub_45BEE0(*(this + 1), (int)a4, *(this + 1), a5, 0);
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
// 0x45C130 sub_45C130
// ------------------------------------------------------------
int /*thiscall*/ sub_45C130(int *this, int a2, uint32_t *a3)
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
      v10 = *sub_45BF80(this, &a3, 1, v5, v3);
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
    v12 = *sub_45BF80(this, &a3, v13, v5, v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x45C1F0 sub_45C1F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45C1F0(int this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v6; // eax
  uint32_t *v7; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_45BF80((int *)this, a2, 1, *(uint32_t **)(this + 4), a4);
    return a2;
  }
  v6 = *(uint32_t **)(this + 4);
  v7 = a4;
  if ( a3 == (uint32_t *)*v6 )
  {
    if ( *a4 < a3[3] )
    {
      sub_45BF80((int *)this, a2, 1, a3, a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( a3 == v6 )
  {
    v8 = (uint32_t *)v6[2];
    if ( v8[3] < *a4 )
    {
      sub_45BF80((int *)this, a2, 0, v8, a4);
      return a2;
    }
    goto LABEL_22;
  }
  if ( *a4 >= a3[3] || (a4 = a3, sub_45B1F0(&a4), a4[3] >= *v7) )
  {
    if ( a3[3] >= *v7 || (a4 = a3, sub_41C640(&a4), a4 != *(uint32_t **)(this + 4)) && *v7 >= a4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_45C130((int *)this, (int)v10, v7);
      *a2 = v9;
      return a2;
    }
    if ( *(uint8_t *)(a3[2] + 33) != 0 )
      sub_45BF80((int *)this, a2, 0, a3, v7);
    else
      sub_45BF80((int *)this, a2, 1, a4, v7);
    return a2;
  }
  else
  {
    if ( *(uint8_t *)(a4[2] + 33) != 0 )
      sub_45BF80((int *)this, a2, 0, a4, v7);
    else
      sub_45BF80((int *)this, a2, 1, a3, v7);
    return a2;
  }
}



// ------------------------------------------------------------
// 0x45C350 sub_45C350
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45C350(uint32_t *this, int *a2)
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
    sub_45BDC0(&v8, (int)v10);
    LOBYTE(v14) = 1;
    v5 = (uint32_t *)*sub_45C1F0((int)this, &a2, v5, &v7);
    if ( Block != nullptr )
      j__free(Block);
  }
  return v5 + 4;
}



// ------------------------------------------------------------
// 0x45C400 sub_45C400
// ------------------------------------------------------------
char /*thiscall*/ sub_45C400(uint32_t *this)
{
  int *v1; // eax
  int *v2; // edi
  bool v3; // zf
  int v4; // esi
  int v5; // ecx
  unsigned int v6; // edx
  int v7; // ecx
  uint32_t *v8; // eax
  uint8_t *v9; // eax
  uint8_t *v10; // edi
  int v11; // eax
  uint32_t *v12; // ebx
  int v13; // eax
  int v14; // edx
  unsigned int v15; // ebx
  uint32_t *v16; // ecx
  int v17; // ebx
  int *v18; // edi
  int v19; // eax
  uint32_t *v20; // esi
  int v21; // esi
  int v22; // eax
  int *v23; // ecx
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
  uint32_t *v36; // [esp+28h] [ebp-8h]
  int *v37; // [esp+2Ch] [ebp-4h]

  v1 = (int *)*(this + 14);
  v2 = (int *)*v1;
  v3 = *v1 == (uint32_t)v1;
  v36 = this;
  v37 = v2;
  if ( !v3 )
  {
    do
    {
      v4 = v2[4];
      v5 = *(uint32_t *)(v4 + 8);
      v6 = 0;
      v33 = v2[3];
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
          v7 = *(uint32_t *)(v4 + 8);
          if ( v7 != 0 && v6 < (*(uint32_t *)(v4 + 12) - v7) >> 2 )
            v8 = *(uint32_t **)(v7 + 4 * v6);
          else
            v8 = nullptr;
          v9 = __RTDynamicCast(v8, 0, &CNRDObject `RTTI Type Descriptor', &CNRDNpc `RTTI Type Descriptor', 0);
          v10 = v9;
          v31 = (int)v9;
          if ( v9 != nullptr )
          {
            v11 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v9 + 336))(v9);
            v12 = v36;
            v32 = v11;
            if ( *(uint32_t *)sub_472E30(v28, &v32) != v12[23] )
            {
              sub_45F1E0(v10);
              v13 = sub_45C350(&v33);
              v14 = *(uint32_t *)(v13 + 4);
              if ( v14 != 0 )
                v15 = (*(uint32_t *)(v13 + 8) - v14) >> 2;
              else
                v15 = 0;
              if ( v14 != 0 && v15 < (*(uint32_t *)(v13 + 12) - v14) >> 2 )
              {
                v16 = *(uint32_t **)(v13 + 8);
                *v16 = v10;
                *(uint32_t *)(v13 + 8) = v16 + 1;
              }
              else
              {
                sub_45BA80(*(void **)(v13 + 8), 1, (int)&v31);
              }
            }
          }
          v6 = ++v34;
        }
        while ( v34 < (int)Src );
        v2 = v37;
      }
      sub_45B6D0(&v30, &v33);
      v17 = v30;
      if ( v30 != v36[20] )
      {
        v18 = *(int **)(v30 + 20);
        if ( v18 != *(int **)(v30 + 24) )
        {
          Src = v18 + 1;
          do
          {
            v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)*v18 + 336))(*v18);
            v20 = v36;
            v31 = v19;
            if ( *(uint32_t *)sub_472E30(v27, &v31) == v20[23] )
            {
              v21 = *v18;
              v26 = *v18;
              v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)*v18 + 52))(*v18);
              v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v21 + 48))(v21);
              sub_45FE80(v29, (int)v18, v22, v25, v26, 0, 0);
              memcpy_0(v18, Src, 4 * ((*(uint32_t *)(v17 + 24) - (int)Src) >> 2));
              *(uint32_t *)(v17 + 24) -= 4;
            }
            else
            {
              ++v18;
              Src = (char *)Src + 4;
            }
          }
          while ( v18 != *(int **)(v17 + 24) );
        }
        v2 = v37;
      }
      LOBYTE(v1) = *((uint8_t *)v2 + 21);
      if ( (uint8_t)v1 == 0 )
      {
        v23 = (int *)v2[2];
        if ( *((uint8_t *)v23 + 21) != 0 )
        {
          v1 = (int *)v2[1];
          if ( *((uint8_t *)v1 + 21) == 0 )
          {
            while ( v2 == (int *)v1[2] )
            {
              v37 = v1;
              v1 = (int *)v1[1];
              if ( *((uint8_t *)v1 + 21) != 0 )
                break;
              v2 = v37;
            }
          }
          v37 = v1;
        }
        else
        {
          v1 = (int *)*v23;
          if ( *(uint8_t *)(*v23 + 21) == 0 )
          {
            do
            {
              v23 = v1;
              v1 = (int *)*v1;
            }
            while ( *((uint8_t *)v1 + 21) == 0 );
          }
          v37 = v23;
        }
        v2 = v37;
      }
    }
    while ( v2 != (int *)v36[14] );
  }
  return (char)v1;
}


// ------------------------------------------------------------
// 0x45C640 sub_45C640
// ------------------------------------------------------------
char /*thiscall*/ sub_45C640(int this)
{
  char result; // al
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  char *v5; // eax
  char *v6; // eax
  void *v7; // eax
  void *v8; // eax
  int v9; // ecx

  result = *(uint8_t *)(this + 4);
  if ( result == 0 )
  {
    *(uint8_t *)(this + 4) = 1;
    v3 = operator new(0x68u);
    if ( v3 != nullptr )
      v4 = sub_426BD0(v3);
    else
      v4 = nullptr;
    *(uint32_t *)(this + 12) = v4;
    v5 = (char *)operator new(0x558u);
    if ( v5 != nullptr )
      v6 = sub_42B7E0(v5);
    else
      v6 = nullptr;
    *(uint32_t *)(this + 44) = v6;
    v7 = operator new(0x1F0u);
    if ( v7 != nullptr )
      v8 = sub_452B10(v7);
    else
      v8 = nullptr;
    v9 = *(uint32_t *)(this + 44);
    *(uint32_t *)(this + 48) = v8;
    *(uint32_t *)(v9 + 108) = v8;
    sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 44) + 36));
    sub_69A840(*((uint32_t *)dword_8F8528 + 2));
    sub_69A840(*((uint32_t *)dword_8F8528 + 3));
    sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 44) + 40));
    sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));
    return sub_45B250(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x45C770 sub_45C770
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45C770(int **this, unsigned int ArgList, unsigned int Block)
{
  unsigned int v3; // edi
  int **v5; // ebx
  int v6; // esi
  int *v8; // eax
  int *v9; // esi
  uint32_t *v10; // eax
  uint32_t *v11; // esi
  int *v12; // [esp+Ch] [ebp-10h] BYREF
  int v13; // [esp+18h] [ebp-4h]

  v3 = ArgList;
  v5 = this + 16;
  ArgList = Block | (ArgList << 16);
  sub_472E30(&v12, &ArgList);
  if ( v12 != *(this + 17) )
    return (uint32_t *)v12[4];
  v6 = sub_4CE8A0(v3);
  if ( v6 != 0 )
  {
    sub_45B660((int **)(v6 + 96), &v12, &Block);
    v8 = *(int **)(v6 + 100);
    v9 = v12;
    if ( v12 == v8 )
    {
      off_77F3FC(aCriticalError_7, v3, Block);
      return nullptr;
    }
    else
    {
      v10 = operator new(0x208u);
      Block = (unsigned int)v10;
      v13 = 0;
      if ( v10 != nullptr )
      {
        if ( (unsigned int)v9[11] < 0x10 )
          v11 = sub_452B60(v10, (uint8_t)v9 + 24, 0);
        else
          v11 = sub_452B60(v10, v9[6], 0);
      }
      else
      {
        v11 = nullptr;
      }
      v13 = -1;
      *(uint32_t *)sub_45BE60(v5, (int *)&ArgList) = v11;
      return v11;
    }
  }
  else
  {
    off_77F3FC(aCriticalError_5, v3);
    return nullptr;
  }
}



// ------------------------------------------------------------
// 0x45C8C0 sub_45C8C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45C8C0(int this, unsigned int ArgList, unsigned int a3)
{
  int **v4; // ebx
  uint32_t *v5; // eax
  uint32_t *v6; // edi
  uint32_t *v7; // eax
  void *Block; // [esp+8h] [ebp-14h] BYREF
  unsigned int v10; // [esp+Ch] [ebp-10h] BYREF
  int v11; // [esp+18h] [ebp-4h]

  v4 = (int **)(this + 52);
  v10 = a3 | (ArgList << 16);
  sub_472E30(&Block, &v10);
  if ( Block != *(void **)(this + 56) )
    return *((uint32_t **)Block + 4);
  v5 = operator new(0xA0u);
  Block = v5;
  v6 = nullptr;
  v11 = 0;
  if ( v5 != nullptr )
    v6 = sub_42D590(v5, 1);
  v11 = -1;
  v7 = sub_45C770((int **)this, ArgList, a3);
  sub_4602C0(v7[119]);
  *(uint32_t *)sub_45BE60(v4, (int *)&v10) = v6;
  if ( *(uint32_t *)(this + 96) != 0 )
    sub_45C400((int **)this);
  return v6;
}



// ------------------------------------------------------------
// 0x45C9A0 sub_45C9A0
// ------------------------------------------------------------
char /*thiscall*/ sub_45C9A0(int this)
{
  uint32_t *v1; // edi
  int *k; // eax
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
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
  uint32_t *v21; // [esp+Ch] [ebp-4h]

  v1 = (uint32_t *)this;
  LOBYTE(k) = *(uint8_t *)(this + 4);
  v21 = (uint32_t *)this;
  if ( (uint8_t)k != 0 )
  {
    v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
    *((uint8_t *)v1 + 4) = 0;
    if ( v3 != nullptr )
      (**v3)(v3, 1);
    v4 = (void *)v1[11];
    v1[3] = 0;
    if ( v4 != nullptr )
    {
      sub_42BD40(v4);
      j__free(v4);
    }
    v5 = (void *)v1[12];
    v1[11] = 0;
    if ( v5 != nullptr )
    {
      sub_42E940(v5);
      j__free(v5);
    }
    v6 = (int *)v1[14];
    v1[12] = 0;
    v7 = *v6;
    v20 = (int *)*v6;
    if ( v20 != v6 )
    {
      do
      {
        v8 = *(void **)(v7 + 16);
        if ( v8 != nullptr )
        {
          sub_42C770(*(uint32_t *)(v7 + 16));
          j__free(v8);
        }
        *(uint32_t *)(v7 + 16) = 0;
        sub_41C5E0((int *)&v20);
        v7 = (int)v20;
      }
      while ( v20 != (int *)v21[14] );
      v1 = v21;
    }
    v9 = (uint32_t *)v1[17];
    v10 = (uint32_t *)*v9;
    if ( (uint32_t *)*v9 != v9 )
    {
      do
      {
        v11 = (void *)v10[4];
        if ( v11 != nullptr )
        {
          sub_42EDE0(v10[4]);
          j__free(v11);
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
      while ( v10 != (uint32_t *)v21[17] );
      v1 = v21;
    }
    k = (int *)v1[20];
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
            ++v17;
          }
          while ( v17 != k );
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
      while ( v16 != (int *)v21[20] );
    }
  }
  return (char)k;
}


// ------------------------------------------------------------
// 0x45CB30 CNRoomListModule__vmt4
// ------------------------------------------------------------
// CNRoomListModule::vmt4 —— 房间列表帧处理（RTTI 自证）
char /*thiscall*/ sub_45CB30(int this)
{
  int v2; // esi
  int v3; // eax
  int v4; // eax
  uint8_t v5; // al
  int v6; // esi
  int v7; // eax
  int v8; // eax
  int v9; // ebx
  bool v10; // zf
  int v11; // esi
  int v12; // esi
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  uint32_t *v16; // ebx
  char *v17; // eax
  int v18; // esi
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
  uint32_t *v32; // eax
  int *v33; // edx
  int v34; // edx
  int v35; // eax
  int v36; // eax
  char *v37; // eax
  unsigned int v38; // esi
  unsigned int v39; // ebx
  uint32_t *v40; // ebx
  int v41; // eax
  uint64_t v42; // rax
  int v43; // eax
  int v45; // [esp-4h] [ebp-A8h]
  int v46; // [esp+Ch] [ebp-98h] BYREF
  int v47; // [esp+10h] [ebp-94h] BYREF
  int v48; // [esp+14h] [ebp-90h]
  void *Block; // [esp+18h] [ebp-8Ch] BYREF
  char v50[4]; // [esp+1Ch] [ebp-88h] BYREF
  char Buffer[128]; // [esp+20h] [ebp-84h] BYREF
  int v52; // [esp+A0h] [ebp-4h]

  v52 = dword_796E50;
  sub_433690();
  v2 = 0;
  if ( *(uint8_t *)(*((uint32_t *)dword_8F8528 + 625) + 44) != 0 )
    v2 = sub_45E870(pt.x, pt.y, 1);
  v3 = *(uint32_t *)(this + 152);
  if ( v3 != v2 )
  {
    if ( v3 != 0 && (uint8_t)sub_45E680(*(uint32_t *)(this + 152)) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(**(uint32_t **)(this + 152) + 284))(
        *(uint32_t *)(this + 152),
        0,
        0,
        1,
        2);
    *(uint32_t *)(this + 152) = v2;
  }
  if ( *(uint32_t *)(this + 152) != 0 )
  {
    v4 = sub_699000(this + 16);
    v5 = sub_42B420(100, 255, v4, 500);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, int))(**(uint32_t **)(this + 152) + 284))(
      *(uint32_t *)(this + 152),
      1,
      (v5 << 24) | 0xFF9B,
      0,
      1);
  }
  v6 = dword_8F7C08;
  if ( dword_8F7C08 != 0 )
  {
    if ( *(uint8_t *)(this + 116) == 0 )
    {
      v7 = *(uint32_t *)(this + 104);
      if ( v7 != 0 && *(uint32_t *)(v7 + 32) != 1 && sub_699000(this + 16) > *(uint32_t *)(this + 112) + 1000 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 376))(v6);
        *(uint32_t *)(this + 112) = sub_699000(this + 16);
      }
    }
    if ( (uint8_t)sub_45E680(v6) != 0 )
    {
      v8 = sub_48C860(v6);
      v9 = v8;
      v10 = *(uint32_t *)(this + 108) == v8;
      v48 = v8;
      if ( v10 || v8 == 0 )
        goto LABEL_36;
      if ( *(uint32_t *)(v8 + 16) == -1 )
      {
        v11 = sub_429830((uint16_t)word_77F804);
        if ( sub_423B10(dword_8F850C) != v11 || (uint8_t)sub_45B500(this) == 0 )
          goto LABEL_36;
        v12 = 0;
        v13 = 16;
        while ( 1 )
        {
          if ( sub_445080(v12) != 0 )
          {
            v16 = *((uint32_t **)dword_8F8528 + 7);
            v17 = sub_422E70(532);
            goto LABEL_31;
          }
          v14 = *(uint32_t *)(v13 + dword_8F850C);
          if ( v14 != 0 )
          {
            v15 = *(uint32_t *)(v14 + 192);
            if ( v15 == 0 || (uint8_t)sub_45E680(v15) == 0 )
              break;
          }
          v13 += 4;
          ++v12;
          if ( v13 >= 32 )
            goto LABEL_32;
        }
        v16 = *((uint32_t **)dword_8F8528 + 7);
        v17 = sub_422E70(533);
LABEL_31:
        sub_43BEE0(v16, (int)v17, -6567706, 0, -1);
LABEL_32:
        if ( v12 != 4 )
        {
LABEL_35:
          v9 = v48;
LABEL_36:
          *(uint32_t *)(this + 108) = v9;
          goto LABEL_37;
        }
        sub_423200(dword_8F7B08, 15);
      }
      else
      {
        if ( (uint8_t)sub_45B170(*(uint32_t *)(v8 + 16)) == 0 )
        {
          if ( (uint8_t)sub_5460F0(*(uint32_t *)(v9 + 16)) == 0 )
          {
            v35 = sub_4CE8A0(*(uint32_t *)(v9 + 16));
            if ( v35 != 0 )
            {
              if ( *(uint32_t *)(v35 + 28) < 0x10u )
                v36 = v35 + 8;
              else
                v36 = *(uint32_t *)(v35 + 8);
              v45 = v36;
              v37 = sub_422E70(534);
              sprintf(Buffer, v37, v45);
              sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
            }
          }
          goto LABEL_36;
        }
        v30 = *(void **)(v48 + 20);
        v31 = *(uint32_t *)(v9 + 16);
        v47 = 0;
        v46 = 0;
        Block = v30;
        if ( (uint8_t)sub_41C590(dword_8F7A24) != 0 )
        {
          v32 = *(uint32_t **)(this + 104);
          if ( v32 != nullptr && *v32 == 5 )
          {
            LOBYTE(v31) = 2;
            Block = (void *)4;
            v47 = 115;
            v46 = 175;
          }
          else
          {
            LOBYTE(v31) = 2;
            Block = (void *)5;
            v47 = 350;
            v46 = 280;
          }
        }
        else
        {
          sub_45C770((uint32_t *)this, v31, (unsigned int)Block);
          v33 = *(int **)(this + 104);
          if ( v33 != nullptr )
            v34 = *v33;
          else
            v34 = -1;
          sub_48C920((int)&v47, (int)&v46, v6, *(uint32_t *)(this + 100), v34);
        }
        sub_423200(dword_8F7B08, 38);
        v50[0] = v31;
        sub_423290(v50, 1);
        v50[0] = (char)Block;
        sub_423290(v50, 1);
        Block = (void *)v47;
        sub_423290(&Block, 2);
        Block = (void *)v46;
        sub_423290(&Block, 2);
        v50[0] = 5;
        sub_423290(v50, 1);
      }
      sub_423380(dword_8F7B08);
      *(uint8_t *)(this + 116) = 1;
      goto LABEL_35;
    }
  }
LABEL_37:
  v18 = dword_8F7C04;
  if ( dword_8F7C04 != 0 )
  {
    v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1064))(dword_8F7C04);
    v20 = *(uint32_t *)v18;
    v48 = v19;
    v21 = v19 * (*(int (/*thiscall*/ **)(int))(v20 + 740))(v18) / 100;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 736))(v18) != v21 )
    {
      v22 = *(uint32_t *)v18;
      v23 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v18 + 740))(v18, 0, 1);
      (*(void (/*thiscall*/ **)(int, int))(v22 + 732))(v18, v48 * v23 / 100);
    }
    v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 756))(v18);
    v25 = v48 * v24 / 100;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 752))(v18) != v25 )
    {
      v26 = *(uint32_t *)v18;
      v27 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v18 + 756))(v18, 1);
      (*(void (/*thiscall*/ **)(int, int))(v26 + 748))(v18, v48 * v27 / 100);
    }
  }
  sub_4294E0(*(uint32_t *)(this + 44));
  if ( sub_699000(this + 16) >= *(uint32_t *)(this + 156) + 14000 )
  {
    v28 = sub_429830((uint16_t)word_77F804);
    if ( v28 != 0 && sub_41A5E0(v28 + 53) <= 3 )
    {
      if ( dword_98B730 != nullptr )
        v29 = (dword_98B734 - (int)dword_98B730) >> 2;
      else
        v29 = 0;
      v38 = rand() % v29;
      if ( v38 == *(uint32_t *)(this + 160) )
      {
        if ( dword_98B730 != nullptr )
          v39 = (dword_98B734 - (int)dword_98B730) >> 2;
        else
          v39 = 0;
        v38 = (v38 + 1) % v39;
      }
      v40 = *((uint32_t **)dword_8F8528 + 7);
      v41 = sub_41ACF0((char *)dword_98B730 + 4 * v38);
      sub_43BEE0(v40, v41, -6567706, 0, -1);
      *(uint32_t *)(this + 160) = v38;
      *(uint32_t *)(this + 156) = sub_699000(this + 16);
    }
  }
  LODWORD(v42) = *(uint32_t *)(this + 120);
  if ( (uint32_t)v42 == 1 )
  {
    v43 = sub_699000(this + 124);
    v42 = (uint64_t)sub_4049C0(255.0, 0.0, v43, 300);
    *((uint32_t *)dword_8F8528 + 621) = v42;
    if ( (uint32_t)v42 == 0 )
    {
      *(uint32_t *)(this + 120) = 0;
      *(uint8_t *)(this + 137) = 0;
      *(uint8_t *)(this + 138) = 0;
      LOBYTE(v42) = sub_698F90(this + 124, 0, 0);
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
// 0x45D190 sub_45D190
// ------------------------------------------------------------
int /*thiscall*/ sub_45D190(int this, uint32_t *ArgList, void *Block)
{
  int v4; // edx
  int v5; // eax
  uint32_t *v7; // ebx
  int result; // eax
  void *v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // edi
  int v13; // edi
  int v14; // edi
  uint32_t *v15; // ebx
  int v16; // ecx
  int v17; // eax
  uint32_t *v18; // eax
  int v19; // edi
  int v20; // eax
  void *v21; // [esp-4h] [ebp-28h]
  int v22; // [esp-4h] [ebp-28h]
  int v23; // [esp+Ch] [ebp-18h]
  int v24; // [esp+10h] [ebp-14h] BYREF
  int v25; // [esp+14h] [ebp-10h]
  int v26; // [esp+20h] [ebp-4h]
  uint32_t *ArgLista; // [esp+2Ch] [ebp+8h]

  v4 = *(uint32_t *)(this + 44);
  v5 = *(uint32_t *)(this + 100);
  v25 = *(uint32_t *)(this + 104);
  v23 = v5;
  if ( *(uint32_t *)(v4 + 104) != 0 )
    sub_45F4D0(18);
  *(uint32_t *)(this + 100) = ArgList;
  v7 = (uint32_t *)sub_4CE8A0(ArgList);
  ArgLista = v7;
  if ( v7 == nullptr )
    return off_77F3FC(aCriticalError_5, ArgList);
  sub_45B660(&v24, &Block);
  if ( v24 == v7[25] )
    return off_77F3FC(aCriticalError_7, ArgList, Block);
  v9 = Block;
  v21 = Block;
  *(uint32_t *)(this + 104) = v24 + 16;
  v10 = sub_45C770((char)ArgList, v21);
  sub_425500(v10);
  v11 = sub_45C8C0((char)ArgList, v9);
  sub_424100(*(uint32_t **)(this + 44), v11);
  v12 = *(uint32_t *)(*(uint32_t *)(this + 44) + 104);
  sub_45F4D0(18);
  result = sub_45ECE0(v12);
  v13 = v25;
  if ( v25 != 0 )
  {
    if ( (uint8_t)sub_41C590(dword_8F7A24) == 0
      && (*(uint8_t *)(this + 117) == 0 && *(uint32_t *)(v13 + 32) == 1 && *(uint32_t *)(*(uint32_t *)(this + 104) + 32) != 1
       || v23 != *(uint32_t *)(this + 100)) )
    {
      v14 = *(uint32_t *)(*(uint32_t *)(this + 44) + 108);
      v15 = *(uint32_t **)(v14 + 60);
      if ( v15 != nullptr )
      {
        sub_42AF90(*(void ***)(v14 + 60));
        sub_657740((int *)dword_9A0128, v15, 228);
      }
      *(uint32_t *)(v14 + 60) = 0;
      Block = (void *)sub_42FCB0(228);
      v26 = 0;
      if ( Block != nullptr )
      {
        if ( ArgLista[14] < 0x10u )
          LOBYTE(v16) = (uint8_t)ArgLista + 36;
        else
          v16 = ArgLista[9];
        if ( ArgLista[33] < 0x10u )
          v17 = sub_431920((uint8_t)ArgLista + 112, v16, 1);
        else
          v17 = sub_431920(ArgLista[28], v16, 1);
      }
      else
      {
        v17 = 0;
      }
      *(uint32_t *)(v14 + 60) = v17;
      v26 = -1;
      if ( (uint8_t)sub_423340(ArgLista + 15, szPassword) != 0 )
      {
        if ( ArgLista[21] < 0x10u )
          v18 = ArgLista + 16;
        else
          v18 = (uint32_t *)ArgLista[16];
        v19 = *(uint32_t *)(this + 48);
        v22 = ArgLista[22];
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v18);
        *(uint32_t *)(v19 + 64) = sub_418DD0(v22);
      }
      v20 = v25;
      *(uint32_t *)(this + 172) = 0;
      *(uint8_t *)(this + 189) = 0;
      *(uint8_t *)(this + 190) = 0;
      *(uint32_t *)(this + 212) = *(uint32_t *)(v20 + 32);
      v13 = v20;
    }
    result = 1;
    if ( *(uint32_t *)(v13 + 32) == 1 && *(uint32_t *)(*(uint32_t *)(this + 104) + 32) == 1 )
      result = (int)sub_432EA0("DOOR_SHUT", -1, 0, 0);
  }
  *(uint32_t *)(this + 108) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x45D410 sub_45D410
// ------------------------------------------------------------
int /*thiscall*/ sub_45D410(int this)
{
  uint32_t *v3; // ecx

  *(uint32_t *)(this + 396) = 0;
  *(uint32_t *)(this + 12) = 0;
  v3 = (uint32_t *)(this + 20);
  *v3 = 0;
  v3[1] = 0;
  v3[2] = 0;
  v3[3] = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint8_t *)(this + 76) = 1;
  memset((void *)(this + 77), 0, 0x100u);
  *(uint32_t *)(this + 336) = 0;
  *(uint32_t *)(this + 340) = 0;
  *(uint32_t *)(this + 344) = 0;
  *(uint32_t *)(this + 348) = 0;
  *(uint32_t *)(this + 352) = 0;
  *(uint32_t *)(this + 356) = 0;
  *(uint32_t *)(this + 360) = 0;
  *(uint32_t *)(this + 364) = 0;
  *(uint32_t *)(this + 8) = 16843009;
  *(uint32_t *)(this + 404) = 0;
  *(uint8_t *)(this + 421) = 0;
  *(uint8_t *)(this + 422) = 0;
  *(uint8_t *)(this + 420) = 0;
  *(uint32_t *)(this + 436) = 0;
  *(uint32_t *)(this + 440) = 0;
  *(uint8_t *)(this + 400) = 0;
  *(uint32_t *)(this + 444) = -1;
  return 0;
}



// ------------------------------------------------------------
// 0x45D4C0 sub_45D4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_45D4C0(int this)
{
  int Error; // eax
  struct hostent *v4; // eax
  SOCKET v5; // eax
  u_long v6; // eax
  SOCKET v7; // ecx
  int v8; // esi
  struct ip_option_information *v9; // eax
  unsigned int v10; // esi
  HGLOBAL v11; // eax
  IPAddr v12; // edx
  void *v13; // edi
  HANDLE v14; // [esp-24h] [ebp-ECh]
  void *v15; // [esp-1Ch] [ebp-E4h]
  SOCKET v16; // [esp-18h] [ebp-E0h]
  SOCKET v17; // [esp-18h] [ebp-E0h]
  struct ip_option_information *v18; // [esp-14h] [ebp-DCh]
  DWORD v19; // [esp+8h] [ebp-C0h]
  char optval[4]; // [esp+Ch] [ebp-BCh] BYREF
  IPAddr DestinationAddress; // [esp+10h] [ebp-B8h]
  u_long argp; // [esp+14h] [ebp-B4h] BYREF
  int v23; // [esp+18h] [ebp-B0h]
  HANDLE IcmpHandle; // [esp+1Ch] [ebp-ACh]
  unsigned int v25; // [esp+20h] [ebp-A8h]
  LPVOID RequestData; // [esp+24h] [ebp-A4h]
  char v27[4]; // [esp+28h] [ebp-A0h] BYREF
  PIP_OPTION_INFORMATION RequestOptions; // [esp+2Ch] [ebp-9Ch]
  char name[100]; // [esp+30h] [ebp-98h] BYREF
  char cp[32]; // [esp+94h] [ebp-34h] BYREF
  struct sockaddr v31; // [esp+B4h] [ebp-14h] BYREF
  int v32; // [esp+C4h] [ebp-4h]

  v32 = dword_796E50;
  if ( byte_98B73C == 0 )
  {
    sub_56ADA0();
    byte_98B73C = 1;
  }
  memset(name, 0, sizeof(name));
  if ( gethostname(name, 100) == -1 )
  {
    Error = WSAGetLastError();
    return off_77F3FC("SOCKET ERROR : %d", Error);
  }
  else
  {
    v4 = gethostbyname(name);
    if ( v4 != nullptr )
      sprintf(
        cp,
        "%d.%d.%d.%d",
        **(uint8_t **)v4->h_addr_list,
        *((uint8_t *)*v4->h_addr_list + 1),
        *((uint8_t *)*v4->h_addr_list + 2),
        *((uint8_t *)*v4->h_addr_list + 3));
    else
      sprintf(cp, "127.0.0.1");
    off_77F3FC("Local IP : [%s]", cp);
    *(uint32_t *)(this + 12) = inet_addr(cp);
    v5 = socket(2, 2, 0);
    *(uint32_t *)(this + 16) = v5;
    argp = 1;
    if ( ioctlsocket(v5, -2147195266, &argp) == -1 )
    {
      return off_77F3FC("Socket Error!");
    }
    else
    {
      memset(v31.sa_data, 0, sizeof(v31.sa_data));
      v31.sa_family = 2;
      *(uint16_t *)v31.sa_data = htons(0x13C7u);
      v6 = htonl(0);
      v7 = *(uint32_t *)(this + 16);
      *(uint32_t *)&v31.sa_data[2] = v6;
      bind(v7, &v31, 16);
      v8 = rand() % 4;
      *(uint8_t *)(v8 + this + 8) = 0;
      off_77F3FC("UDP SERVER CONNECT : [%s]", (&ArgList)[v8]);
      *(uint16_t *)(this + 2 * v8 + 436) = 2;
      *(uint16_t *)(this + 20) = 2;
      *(uint32_t *)(this + 24) = inet_addr((&ArgList)[v8]);
      *(uint16_t *)(this + 22) = htons(0x907u);
      *(uint16_t *)(this + 36) = 2;
      *(uint32_t *)(this + 40) = inet_addr((&ArgList)[v8]);
      *(uint16_t *)(this + 38) = htons(0x908u);
      v16 = *(uint32_t *)(this + 16);
      *(uint32_t *)optval = 10;
      setsockopt(v16, 0xFFFF, 4102, optval, 4);
      v17 = *(uint32_t *)(this + 16);
      *(uint32_t *)v27 = 0x100000;
      setsockopt(v17, 0xFFFF, 4098, v27, 4);
      setsockopt(*(uint32_t *)(this + 16), 0xFFFF, 4097, v27, 4);
      IcmpHandle = IcmpCreateFile();
      DestinationAddress = inet_addr("211.189.29.106");
      v9 = (struct ip_option_information *)GlobalAlloc(0x40u, 8u);
      v10 = 1472;
      RequestOptions = v9;
      v9->Flags = 2;
      v9->Ttl = -1;
      v25 = 0;
      v23 = 1472;
      while ( 1 )
      {
        while ( 1 )
        {
          RequestData = GlobalAlloc(0x40u, v10);
          memset(RequestData, 0xAAu, v10);
          v11 = GlobalAlloc(0x40u, v10 + 28);
          v12 = DestinationAddress;
          v13 = v11;
          v18 = RequestOptions;
          v15 = RequestData;
          *((uint32_t *)v11 + 4) = RequestData;
          v14 = IcmpHandle;
          *((uint16_t *)v11 + 6) = v10;
          v19 = IcmpSendEcho(v14, v12, v15, v10, v18, v11, v10 + 28, 0x3E8u);
          GlobalFree(v13);
          GlobalFree(RequestData);
          if ( v19 == 0 )
            break;
          if ( v10 == v23 )
            goto LABEL_16;
          v25 = v10;
          v10 = (v10 + v23 + 1) >> 1;
        }
        if ( v10 == v25 )
          break;
        v23 = v10 - 1;
        v10 = (v25 + v10 - 1) >> 1;
      }
LABEL_16:
      GlobalFree(RequestOptions);
      IcmpCloseHandle(IcmpHandle);
      if ( v10 < 0x5C0 )
      {
        if ( v10 < 0x500 )
        {
          if ( v10 < 0x400 )
            *(uint32_t *)(this + 444) = 768;
          else
            *(uint32_t *)(this + 444) = 1024;
        }
        else
        {
          *(uint32_t *)(this + 444) = 1280;
        }
      }
      else
      {
        *(uint32_t *)(this + 444) = 1472;
      }
      return off_77F3FC("[MTU] Client MTU Size is [%d]", *(uint32_t *)(this + 444));
    }
  }
}


// ------------------------------------------------------------
// 0x45D890 sub_45D890
// ------------------------------------------------------------
char /*thiscall*/ sub_45D890(void *this, uint32_t *a2, int ArgList)
{
  char v3; // bl
  int v5; // edx
  char result; // al
  int v7; // eax
  int v8; // edx
  u_short v9; // ax
  char v10; // [esp-4h] [ebp-10h]

  v3 = ArgList;
  v10 = ArgList;
  *((uint32_t *)this + 18) = ArgList;
  sub_40BE20("1@@@@@@@@@@@@@@net_type:%d#####################\n", v10);
  v5 = *((uint32_t *)this + 18);
  *((uint32_t *)this + 17) = 4;
  *(uint32_t *)this = *a2;
  *((uint32_t *)this + 1) = a2[1];
  off_77F3FC("UDP IDENTIFIED! [%d]", v5);
  sub_40BE20("---------%d %d\n", *(uint8_t *)(dword_8F7B08 + 8));
  result = *(uint8_t *)(dword_8F7B08 + 8);
  if ( result != 0 )
  {
    result = *(uint8_t *)(*(uint32_t *)(dword_8F7A24 + 16) + 48);
    if ( result != 0 )
    {
      if ( sub_429830((uint16_t)word_77F804) != 0 )
      {
        v7 = sub_429830((uint16_t)word_77F804);
        *(uint32_t *)(v7 + 160) = *((uint32_t *)this + 3);
        v8 = *((uint32_t *)this + 89);
        ArgList = v7;
        *(uint32_t *)(v7 + 164) = v8;
        v9 = ntohs(*((uint16_t *)this + 176));
        *(uint16_t *)(ArgList + 168) = v9;
      }
      sub_423200(dword_8F7B08, 2);
      HIBYTE(ArgList) = v3;
      sub_423290((char *)&ArgList + 3, 1);
      sub_40BE20("2@@@@@@@@@@@@@@net_type:%d#####################\n", v3);
      ArgList = *((uint32_t *)this + 3);
      sub_423290(&ArgList, 4);
      ArgList = a2[1];
      sub_423290(&ArgList, 4);
      ArgList = *(uint16_t *)a2;
      sub_423290(&ArgList, 2);
      ArgList = *((uint32_t *)this + 111);
      sub_423290(&ArgList, 4);
      sub_423380(dword_8F7B08);
      return off_77F3FC("UDP IDENTIFY INFO SEND!");
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x45DA30 sub_45DA30
// ------------------------------------------------------------
char /*thiscall*/ sub_45DA30(int *this)
{
  if ( *(this + 18) == 0 )
    return 0;
  sub_45D890(this, this, *(this + 18));
  return 1;
}



// ------------------------------------------------------------
// 0x45DA50 sub_45DA50
// ------------------------------------------------------------
char /*thiscall*/ sub_45DA50(int this)
{
  int v2; // edi
  uint16_t *v3; // eax

  v2 = 0;
  v3 = (uint16_t *)(this + 436);
  while ( *(uint8_t *)(this + v2 + 8) != 1 )
  {
LABEL_5:
    ++v2;
    ++v3;
    if ( v2 >= 4 )
      goto LABEL_8;
  }
  if ( *v3 == 0 )
  {
    *(uint8_t *)(this + v2 + 8) = 0;
    goto LABEL_5;
  }
  *(uint16_t *)(this + 2 * v2 + 436) = 2;
  *(uint8_t *)(v2 + this + 8) = 0;
LABEL_8:
  sub_40BE20(asc_6C71AC, (char)(&ArgList)[v2]);
  *(uint16_t *)(this + 20) = 2;
  *(uint32_t *)(this + 24) = inet_addr((&ArgList)[v2]);
  *(uint16_t *)(this + 22) = htons(0x907u);
  *(uint16_t *)(this + 36) = 2;
  *(uint32_t *)(this + 40) = inet_addr((&ArgList)[v2]);
  *(uint16_t *)(this + 38) = htons(0x908u);
  return 1;
}



// ------------------------------------------------------------
// 0x45DB00 sub_45DB00
// ------------------------------------------------------------
char */*thiscall*/ sub_45DB00(uint32_t *this)
{
  return off_790540[*(this + 101)];
}



// ------------------------------------------------------------
// 0x45DB20 sub_45DB20
// ------------------------------------------------------------
int /*thiscall*/ sub_45DB20(int this, int a2)
{
  int result; // eax
  int v4; // esi
  uint16_t *i; // eax
  const char *v6; // ecx
  uint16_t v7; // ax
  u_short v8; // ax
  SOCKET v9; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // esi
  u_long v13; // eax
  u_short v14; // cx
  struct in_addr v15; // edi
  char *v16; // eax
  u_short v17; // ax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  SOCKET v21; // [esp-20h] [ebp-50h]
  int v22; // [esp-Ch] [ebp-3Ch]
  int v23; // [esp-Ch] [ebp-3Ch]
  int v24; // [esp-Ch] [ebp-3Ch]
  int fromlen; // [esp+4h] [ebp-2Ch] BYREF
  char buf[3]; // [esp+Bh] [ebp-25h] BYREF
  u_short netshort[7]; // [esp+Eh] [ebp-22h]
  struct sockaddr to; // [esp+1Ch] [ebp-14h] BYREF
  int v29; // [esp+2Ch] [ebp-4h]

  result = dword_796E50;
  v29 = dword_796E50;
  if ( *(uint32_t *)(this + 72) == 3 )
  {
    v4 = 0;
    for ( i = (uint16_t *)(this + 436); *i >= 2u; ++i )
    {
      if ( ++v4 >= 4 )
        return off_77F3FC(aSNat);
    }
    v6 = (&ArgList)[v4];
    *(uint16_t *)to.sa_data = 0;
    *(uint32_t *)&to.sa_data[6] = 0;
    *(uint32_t *)&to.sa_data[10] = 0;
    to.sa_family = 2;
    *(uint32_t *)&to.sa_data[2] = inet_addr(v6);
    v7 = *(uint16_t *)(this + 2 * v4 + 436);
    if ( v7 < 2u )
    {
      if ( v7 != 0 )
        v8 = htons(0x908u);
      else
        v8 = htons(0x907u);
      ++*(uint16_t *)(this + 2 * v4 + 436);
      *(uint16_t *)to.sa_data = v8;
    }
    v9 = *(uint32_t *)(this + 16);
    buf[0] = 1;
    v10 = sendto(v9, buf, 1, 0, &to, 16);
    off_77F3FC(aSNat_0, v10);
    memset((void *)(this + 77), 0, 0x100u);
    *(uint32_t *)(this + 336) = 0;
    *(uint32_t *)(this + 340) = 0;
    *(uint32_t *)(this + 344) = 0;
    *(uint32_t *)(this + 348) = 0;
    v21 = *(uint32_t *)(this + 16);
    fromlen = 16;
    v11 = recvfrom(v21, (char *)(this + 77), 256, 0, (struct sockaddr *)(this + 336), &fromlen);
    v12 = a2;
    if ( v11 == -1 || *(uint8_t *)(this + 77) != 2 )
    {
      off_77F3FC(aSNat_3);
    }
    else
    {
      v13 = htonl(*(uint32_t *)(this + 78));
      v14 = *(uint16_t *)(this + 82);
      v15 = (struct in_addr)v13;
      *(uint32_t *)&netshort[1] = v13;
      netshort[0] = htons(v14);
      v22 = ntohs(netshort[0]);
      v16 = inet_ntoa(v15);
      off_77F3FC(aSNat_1, v16, v22);
      v17 = ntohs(netshort[0]);
      v23 = v17;
      *(uint16_t *)(v12 + 168) = v17;
      v18 = sub_42A380(1);
      off_77F3FC(aSNat_2, v18, v23);
      sub_423200(dword_8F7B08, 2);
      HIBYTE(a2) = *(uint8_t *)(this + 72);
      sub_423290((char *)&a2 + 3, 1);
      a2 = *(uint32_t *)(v12 + 160);
      sub_423290(&a2, 4);
      a2 = *(uint32_t *)(v12 + 164);
      sub_423290(&a2, 4);
      LOWORD(v19) = htons(*(uint16_t *)(v12 + 168));
      a2 = v19;
      sub_423290(&a2, 2);
      a2 = *(uint32_t *)(this + 444);
      sub_423290(&a2, 4);
      sub_423380(dword_8F7B08);
    }
    v24 = *(uint16_t *)(v12 + 168);
    v20 = sub_42A380(1);
    return off_77F3FC(aSNat_4, v20, v24);
  }
  return result;
}


// ------------------------------------------------------------
// 0x45DDA0 sub_45DDA0
// ------------------------------------------------------------
void /*thiscall*/ sub_45DDA0(int this, int a2)
{
  int v3; // edi
  int v4; // ecx
  int v5; // ebx
  SOCKET v6; // edx
  int v7; // ecx
  HWND v8; // esi
  char *v9; // eax
  SOCKET v10; // edx
  int v11; // eax
  SOCKET v12; // ecx
  int v13; // edx
  int v14; // [esp-8h] [ebp-18h]
  int v15; // [esp-8h] [ebp-18h]
  int v16; // [esp-8h] [ebp-18h]
  char buf; // [esp+8h] [ebp-8h] BYREF
  int v18; // [esp+9h] [ebp-7h]

  if ( *(uint8_t *)(this + 400) == 0 || (v3 = *(uint32_t *)(this + 392), sub_699000(this + 368) >= v3) )
  {
    v4 = *(uint32_t *)(this + 68);
    if ( v4 == 4 )
    {
      v5 = *(uint32_t *)(this + 392);
      if ( sub_699000(this + 368) >= v5 )
      {
        v6 = *(uint32_t *)(this + 16);
        *(uint8_t *)(this + 76) = 0;
        sendto(v6, (const char *)(this + 76), 10, 0, (const struct sockaddr *)(this + 36), 16);
        *(uint8_t *)(this + 381) = 0;
        *(uint8_t *)(this + 382) = 0;
        sub_698F90(this + 368, 10000, 0);
      }
      return;
    }
    if ( a2 == v4 )
    {
      v7 = *(uint32_t *)(this + 396);
      if ( v7 >= 10 )
      {
        if ( sub_45DA50(this) == 1 )
        {
          off_77F3FC(aCnrdudpidentif);
          *(uint32_t *)(this + 396) = 0;
        }
        else
        {
          ShowCursor(true);
          v8 = *(HWND *)(dword_79C0A0 + 16);
          v9 = sub_422E70(501);
          MessageBoxA(v8, v9, "Run Error", 0);
          PostQuitMessage(0);
        }
        return;
      }
      *(uint32_t *)(this + 396) = v7 + 1;
    }
    else
    {
      *(uint32_t *)(this + 68) = a2;
    }
    switch ( a2 )
    {
      case 1:
        v11 = sendto(*(uint32_t *)(this + 16), (const char *)(this + 76), 1, 0, (const struct sockaddr *)(this + 20), 16);
        off_77F3FC("SEND REALIP CHECK %d\n", v11);
        v12 = *(uint32_t *)(this + 16);
        v13 = *(uint32_t *)(this + 444);
        buf = 6;
        v18 = v13;
        v16 = sendto(v12, &buf, 5, 0, (const struct sockaddr *)(this + 20), 16);
        off_77F3FC("SEND TO MTU LOG %d\n", v16);
        break;
      case 2:
        v15 = sendto(*(uint32_t *)(this + 16), (const char *)(this + 76), 1, 0, (const struct sockaddr *)(this + 36), 16);
        off_77F3FC("SEND NAT CHECK %d\n", v15);
        break;
      case 3:
        v10 = *(uint32_t *)(this + 16);
        *(uint8_t *)(this + 76) = 5;
        v14 = sendto(v10, (const char *)(this + 76), 1, 0, (const struct sockaddr *)(this + 20), 16);
        off_77F3FC("SEND PORT RESTRICT CHECK %d\n", v14);
        break;
      default:
LABEL_20:
        *(uint8_t *)(this + 381) = 0;
        *(uint8_t *)(this + 382) = 0;
        sub_698F90(this + 368, 500, 0);
        return;
    }
    *(uint8_t *)(this + 400) = 1;
    goto LABEL_20;
  }
}



// ------------------------------------------------------------
// 0x45DF90 sub_45DF90
// ------------------------------------------------------------
char /*usercall*/ sub_45DF90@<al>(int a1@<ecx>, char a2@<bl>)
{
  int v3; // edi
  int v5; // eax
  int v6; // edi
  const char *v7; // ebx
  FILE *v8; // edi
  char v9; // al
  char v10; // bl
  FILE *Stream; // [esp+8h] [ebp-130h]
  char String[256]; // [esp+Ch] [ebp-12Ch] BYREF
  void *Block[5]; // [esp+110h] [ebp-28h] BYREF
  unsigned int v15; // [esp+124h] [ebp-14h]
  int v16; // [esp+128h] [ebp-10h]
  int v17; // [esp+134h] [ebp-4h]

  v16 = dword_796E50;
  if ( *(uint8_t *)(a1 + 420) != 0 && (v3 = *(uint32_t *)(a1 + 432), sub_699000(a1 + 408) < v3) )
  {
    if ( sub_4458C0((uint32_t *)dword_8F8520) != 0 )
    {
      sub_45D890((void *)a1, (uint32_t *)(a1 + 352), *(uint32_t *)(a1 + 72));
      *(uint8_t *)(a1 + 420) = 0;
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    v5 = *(uint32_t *)(a1 + 404);
    v6 = dword_6C7018[v5];
    v7 = off_790540[v5];
    v15 = 15;
    Block[4] = nullptr;
    LOBYTE(Block[0]) = 0;
    v17 = 0;
    if ( _access("_RELAY", 0) == 0 )
    {
      v8 = fopen("_RELAY", "rt");
      Stream = v8;
      fgets(String, 256, v8);
      String[strlen(String)] = 0;
      sub_4015C0(String, strlen(String));
      v7 = (const char *)Block[0];
      if ( v15 < 0x10 )
        v7 = (const char *)Block;
      fgets(String, 256, v8);
      j__atol(String);
      fgets(String, 256, v8);
      v6 = j__atol(String);
      fclose(Stream);
    }
    v9 = sub_446000((uint32_t *)dword_8F8520, v7, v6);
    *(uint8_t *)(a1 + 421) = 0;
    *(uint8_t *)(a1 + 422) = 0;
    v10 = v9;
    *(uint8_t *)(a1 + 420) = 1;
    sub_698F90(a1 + 408, 10000, 0);
    if ( v10 != 0 )
    {
      sub_40BE20("\nresult==true\n", a2);
      sub_45D890((void *)a1, (uint32_t *)(a1 + 352), *(uint32_t *)(a1 + 72));
      *(uint8_t *)(a1 + 420) = 0;
    }
    if ( v15 >= 0x10 )
      j__free(Block[0]);
    return v10;
  }
}



// ------------------------------------------------------------
// 0x45E1A0 sub_45E1A0
// ------------------------------------------------------------
// UDP 接收泵（docs/13 §2：主帧循环 sub_433690 调 sub_45E1A0(0x8F8524)）：
// dword_8F7B08+8 已连接且模块 +16 槽使能 → 按 +68 模块类型分发：
// 4(PVP) → sub_45DDA0 + sub_445940 就绪查询 + sub_45DF90；recvfrom/in_addr 直证
char /*usercall*/ sub_45E1A0@<al>(int a1@<ecx>, char a2@<dil>)
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
  int v24; // [esp+28h] [ebp-4h]

  v24 = dword_796E50;
  LOBYTE(v2) = dword_8F7B08;
  if ( *(uint8_t *)(dword_8F7B08 + 8) != 0 )
  {
    LOBYTE(v2) = *(uint8_t *)(*(uint32_t *)(dword_8F7A24 + 16) + 48);
    if ( (uint8_t)v2 != 0 )
    {
      v2 = *(uint32_t *)(a1 + 68);
      if ( v2 == 4 )
      {
        if ( *(uint32_t *)(a1 + 72) != 1 )
          sub_45DDA0(a1, 4);
        LOBYTE(v2) = sub_445940(dword_8F8520);
        if ( (uint8_t)v2 == 0 )
          LOBYTE(v2) = sub_45DF90(a1);
      }
      else if ( v2 != 0 )
      {
        v4 = (uint8_t *)(a1 + 77);
        memset((void *)(a1 + 77), 0, 0x100u);
        *(uint32_t *)(a1 + 336) = 0;
        *(uint32_t *)(a1 + 340) = 0;
        *(uint32_t *)(a1 + 344) = 0;
        *(uint32_t *)(a1 + 348) = 0;
        v16 = *(uint32_t *)(a1 + 16);
        fromlen = 16;
        if ( recvfrom(v16, (char *)(a1 + 77), 256, 0, (struct sockaddr *)(a1 + 336), &fromlen) == -1 || *v4 != 2 )
        {
          if ( *(uint32_t *)(a1 + 68) == 3 )
          {
            LOBYTE(v2) = sub_45D890((void *)a1, (uint32_t *)(a1 + 352), 4);
          }
          else
          {
            v20 = *(uint32_t *)(a1 + 68);
            *(uint32_t *)(a1 + 72) = 0;
            sub_45DDA0(a1, v20);
            LOBYTE(v2) = sub_40BE20(aStunServer, a2);
          }
        }
        else
        {
          v2 = *(uint32_t *)(a1 + 68);
          *(uint8_t *)(a1 + 400) = 0;
          switch ( v2 )
          {
            case 1:
              *(uint32_t *)(a1 + 356) = htonl(*(uint32_t *)(a1 + 78));
              v5 = htons(*(uint16_t *)(a1 + 82));
              v6 = *(struct in_addr *)(a1 + 356);
              *(uint16_t *)(a1 + 352) = v5;
              v7 = inet_ntoa(*(struct in_addr *)(a1 + 12));
              off_77F3FC("CHECK IP : [%s]", v7);
              v17 = ntohs(*(uint16_t *)(a1 + 352));
              v8 = inet_ntoa(v6);
              off_77F3FC("->[%s:%d]\n", v8, v17);
              if ( *(uint32_t *)(a1 + 12) == *(uint32_t *)(a1 + 356) )
                LOBYTE(v2) = sub_45D890((void *)a1, (uint32_t *)(a1 + 352), 1);
              else
                LOBYTE(v2) = sub_45DDA0(a1, 2);
              break;
            case 2:
              *(uint32_t *)(a1 + 364) = htonl(*(uint32_t *)(a1 + 78));
              v9 = htons(*(uint16_t *)(a1 + 82));
              v10 = *(struct in_addr *)(a1 + 356);
              v11 = *(uint16_t *)(a1 + 352);
              v12 = *(uint32_t *)(a1 + 364);
              *(uint16_t *)(a1 + 360) = v9;
              netshort[0] = v11;
              v23[0] = v9;
              *(struct in_addr *)&netshort[1] = v10;
              *(uint32_t *)&v23[1] = v12;
              v18 = ntohs(v11);
              v13 = inet_ntoa(v10);
              off_77F3FC("CHECK IP : [%s:%d]", v13, v18);
              v19 = ntohs(v23[0]);
              v14 = inet_ntoa(*(struct in_addr *)&v23[1]);
              off_77F3FC("->[%s:%d]\n", v14, v19);
              if ( *(uint32_t *)(a1 + 356) == *(uint32_t *)(a1 + 364) && *(uint16_t *)(a1 + 352) == *(uint16_t *)(a1 + 360) )
                LOBYTE(v2) = sub_45DDA0(a1, 3);
              else
                LOBYTE(v2) = sub_45D890((void *)a1, (uint32_t *)(a1 + 360), 3);
              break;
            case 3:
              LOBYTE(v2) = sub_45D890((void *)a1, (uint32_t *)(a1 + 352), 2);
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
// 0x45E490 sub_45E490
// ------------------------------------------------------------
int /*thiscall*/ sub_45E490(uint32_t *this, int a2, int a3)
{
  int v3; // eax
  int v4; // esi

  v3 = *(this + 33);
  if ( v3 == 0 )
    return a2;
  v4 = *(uint32_t *)(v3 + 192);
  return v4 + a2 - sub_48C1C0(a3);
}



// ------------------------------------------------------------
// 0x45E4D0 sub_45E4D0
// ------------------------------------------------------------
int /*thiscall*/ sub_45E4D0(uint32_t *this, int a2, int a3, int a4, float a5)
{
  int v5; // ecx
  int result; // eax

  v5 = *(this + 33);
  result = a2 - (uint64_t)((double)a3 * a5) + 120;
  if ( v5 != 0 )
    result += *(uint32_t *)(v5 + 196) - *(uint32_t *)(*(uint32_t *)(v5 + 44) + 468);
  return result;
}



// ------------------------------------------------------------
// 0x45E510 sub_45E510
// ------------------------------------------------------------
int /*thiscall*/ sub_45E510(uint32_t *this, int a2, int a3)
{
  int v3; // eax
  int v4; // esi

  v3 = *(this + 33);
  if ( v3 == 0 )
    return a2;
  v4 = *(uint32_t *)(v3 + 192);
  return a2 - v4 + sub_48C1C0(a3);
}



// ------------------------------------------------------------
// 0x45E550 sub_45E550
// ------------------------------------------------------------
int /*thiscall*/ sub_45E550(uint32_t *this, int a2, int a3, int a4)
{
  int result; // eax
  int v5; // edx

  result = a2 + a3 - 120;
  v5 = *(this + 33);
  if ( v5 != 0 )
    result += *(uint32_t *)(*(uint32_t *)(v5 + 44) + 468) - *(uint32_t *)(v5 + 196);
  return result;
}



// ------------------------------------------------------------
// 0x45E580 sub_45E580
// ------------------------------------------------------------
int /*thiscall*/ sub_45E580(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 20;
  return result;
}



// ------------------------------------------------------------
// 0x45E5A0 sub_45E5A0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_45E5A0(uint32_t *a1, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v4; // ecx

  v4 = a2;
  if ( a2 == a3 )
  {
    *a1 = a2;
    return a1;
  }
  else
  {
    do
    {
      if ( *v4 == *a4 )
        break;
      ++v4;
    }
    while ( v4 != a3 );
    *a1 = v4;
    return a1;
  }
}



// ------------------------------------------------------------
// 0x45E5D0 sub_45E5D0
// ------------------------------------------------------------
int /*thiscall*/ sub_45E5D0(uint32_t *this)
{
  int v2; // ecx
  int result; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // ebx
  int v7; // edi
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  bool v11; // zf
  int v12; // [esp+4h] [ebp-14h]
  int v13; // [esp+8h] [ebp-10h]
  int v14; // [esp+Ch] [ebp-Ch]
  int v15; // [esp+10h] [ebp-8h]
  int v16; // [esp+14h] [ebp-4h]

  v2 = *(this + 10);
  if ( v2 != 0 )
    result = (*(this + 11) - v2) >> 2;
  else
    result = 0;
  if ( result > 1 )
  {
    v4 = 0;
    v14 = 0;
    v16 = 4;
    v13 = result - 1;
    do
    {
      v5 = *(uint32_t *)(v16 + *(this + 10));
      v15 = v5;
      v6 = v4;
      if ( v4 >= 0 )
      {
        while ( 1 )
        {
          v7 = *(uint32_t *)(*(this + 10) + 4 * v6);
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 124))(v5);
          if ( v12 >= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 124))(v7) )
            break;
          v8 = *(this + 10);
          v9 = *(uint32_t *)(v8 + 4 * v6);
          v10 = v8 + 4 * v6--;
          *(uint32_t *)(v10 + 4) = v9;
          if ( v6 < 0 )
            break;
          v5 = v15;
        }
        v5 = v15;
        v4 = v14;
      }
      ++v4;
      result = v13 - 1;
      v11 = v13 == 1;
      *(uint32_t *)(*(this + 10) + 4 * v6 + 4) = v5;
      v16 += 4;
      v14 = v4;
      --v13;
    }
    while ( !v11 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x45E680 sub_45E680
// ------------------------------------------------------------
char /*thiscall*/ sub_45E680(uint32_t *this, int a2)
{
  int v2; // edx
  int v3; // eax
  int v4; // edx
  uint32_t *i; // ecx

  v2 = *(this + 2);
  if ( v2 != 0 )
    v3 = (*(this + 3) - v2) >> 2;
  else
    v3 = 0;
  v4 = 0;
  if ( v3 <= 0 )
    return 0;
  for ( i = (uint32_t *)*(this + 2); *i != a2; ++i )
  {
    if ( ++v4 >= v3 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x45E6C0 sub_45E6C0
// ------------------------------------------------------------
char /*thiscall*/ sub_45E6C0(uint32_t *this, int a2, int a3)
{
  int v4; // ecx
  int v5; // ebx
  int v6; // ecx
  int v8; // [esp+Ch] [ebp-4h]

  v4 = *(this + 2);
  v5 = 0;
  if ( v4 != 0 )
    v8 = (*(this + 3) - v4) >> 2;
  else
    v8 = 0;
  if ( v8 <= 0 )
    return 0;
  while ( 1 )
  {
    v6 = *(uint32_t *)(*(this + 2) + 4 * v5);
    if ( v6 != 0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 48))(v6) == a2
      && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(4 * v5 + *(this + 2)) + 52))(*(uint32_t *)(4 * v5 + *(this + 2))) == a3 )
    {
      break;
    }
    if ( ++v5 >= v8 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x45E740 sub_45E740
// ------------------------------------------------------------
int /*thiscall*/ sub_45E740(uint32_t *this, int a2)
{
  uint32_t *v2; // ebx
  int result; // eax
  int v4; // esi
  int v5; // edi
  int i; // edi
  int j; // edi
  int v8; // ecx
  uint32_t *v9; // [esp+Ch] [ebp-4h]

  v2 = this + 4 * a2;
  result = v2[6];
  v9 = this;
  if ( result != 0 )
    v4 = (v2[7] - result) >> 2;
  else
    v4 = 0;
  v5 = 0;
  if ( v4 > 0 )
  {
    do
    {
      result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v2[6] + 4 * v5) + 16))(*(uint32_t *)(v2[6] + 4 * v5));
      ++v5;
    }
    while ( v5 < v4 );
    this = v9;
  }
  if ( a2 == 1 )
  {
    result = sub_45E5D0(this);
    for ( i = 0; i < v4; ++i )
      result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v9[10] + 4 * i) + 24))(*(uint32_t *)(v9[10] + 4 * i));
  }
  for ( j = 0; j < v4; ++j )
  {
    v8 = *(uint32_t *)(v2[6] + 4 * j);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 20))(v8);
  }
  return result;
}



// ------------------------------------------------------------
// 0x45E7D0 sub_45E7D0
// ------------------------------------------------------------
int /*thiscall*/ sub_45E7D0(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  uint32_t *i; // edx
  uint32_t *v8; // esi

  v3 = *(this + 2);
  if ( v3 != 0 )
    v4 = (*(this + 3) - v3) >> 2;
  else
    v4 = 0;
  v5 = 0;
  if ( v4 <= 0 )
    return 0;
  for ( i = (uint32_t *)*(this + 2); *i != a2; ++i )
  {
    if ( ++v5 >= v4 )
      return 0;
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 428))(a2) == 0
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 432))(a2) == 0 )
  {
    return 0;
  }
  v8 = (uint32_t *)*(this + 30);
  if ( v8 == (uint32_t *)*(this + 31) )
    return 0;
  while ( *v8 == a2 || (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a2 + 484))(a2, *v8) == 0 )
  {
    if ( ++v8 == (uint32_t *)*(this + 31) )
      return 0;
  }
  return *v8;
}



// ------------------------------------------------------------
// 0x45E870 sub_45E870
// ------------------------------------------------------------
uint8_t */*userpurge*/ sub_45E870@<eax>(int a1@<ecx>, int a2@<edi>, int a3, int a4, char a5)
{
  int v5; // edx
  int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  uint8_t *v13; // esi
  char v14; // al
  int v17; // [esp+4h] [ebp-4h]

  v5 = a1;
  if ( *((uint32_t *)dword_8F8528 + 626) == 16 )
    return nullptr;
  v7 = *(uint32_t *)(a1 + 132);
  if ( v7 != 0 )
  {
    v8 = *(uint32_t *)(v7 + 36);
    if ( *(uint8_t *)(v8 + 17) == 0 )
      return nullptr;
    v9 = *(uint32_t *)(v8 + 12);
    if ( dword_79BE3C != v9 && (*(uint8_t *)(v8 + 17) == 0 || dword_79BE34 != v9) )
      return nullptr;
  }
  v10 = *(uint32_t *)(a1 + 40);
  if ( v10 != 0 )
    v11 = (*(uint32_t *)(v5 + 44) - v10) >> 2;
  else
    v11 = 0;
  v12 = v11 - 1;
  v17 = v12;
  if ( v12 < 0 )
    return nullptr;
  while ( 1 )
  {
    v13 = *(uint8_t **)(*(uint32_t *)(v5 + 40) + 4 * v12);
    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)v13 + 40))(v13, 18) != 0 )
    {
      if ( a5 == 0 || (uint8_t *)dword_8F7C08 != v13 )
      {
        v14 = (*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)v13 + 380))(v13, a3, a4);
        goto LABEL_26;
      }
      goto LABEL_27;
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)v13 + 40))(v13, 34, a2) != 0 )
    {
      a2 = a4;
      v14 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)v13 + 344))(v13, a3);
      goto LABEL_26;
    }
    a2 = 66;
    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v13 + 40))(v13) != 0
      && v13[285] == 0
      && (v13[284] != 0 || sub_42FB30((uint32_t *)dword_8F7C08, (int)v13)) )
    {
      break;
    }
LABEL_27:
    if ( --v17 < 0 )
      return nullptr;
    v12 = v17;
    v5 = a1;
  }
  v14 = (*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)v13 + 336))(v13, a3, a4);
LABEL_26:
  if ( v14 == 0 )
    goto LABEL_27;
  return v13;
}



// ------------------------------------------------------------
// 0x45E9B0 sub_45E9B0
// ------------------------------------------------------------
int /*thiscall*/ sub_45E9B0(uint32_t *this, int *a2)
{
  int v3; // ebx
  uint32_t *v4; // esi
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // esi
  int v14; // eax
  int v15; // eax
  int v16; // [esp-8h] [ebp-2Ch]
  int v17; // [esp+Ch] [ebp-18h] BYREF
  int v18; // [esp+10h] [ebp-14h]
  int v19; // [esp+14h] [ebp-10h]
  int v20; // [esp+18h] [ebp-Ch]
  uint32_t *v21; // [esp+1Ch] [ebp-8h]
  int v22; // [esp+20h] [ebp-4h]
  int v23; // [esp+2Ch] [ebp+8h]

  v3 = 0;
  v4 = this;
  v21 = this;
  if ( a2 == nullptr )
    return 0;
  v19 = 50;
  v20 = 50;
  v6 = *a2;
  v17 = 0;
  v18 = 0;
  if ( (*(int (/*thiscall*/ **)(int *))(v6 + 152))(a2) == 1 )
    v7 = (*(int (/*thiscall*/ **)(int *))(*a2 + 120))(a2);
  else
    v7 = (*(int (/*thiscall*/ **)(int *))(*a2 + 120))(a2) - v19;
  v8 = *a2;
  v17 = v7;
  v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 124))(a2);
  v10 = v4[10];
  v18 = v9 - 25;
  v22 = 0;
  if ( v10 != 0 )
    v11 = (v4[11] - v10) >> 2;
  else
    v11 = 0;
  v12 = v11 - 1;
  v23 = v12;
  if ( v12 >= 0 )
  {
    while ( 1 )
    {
      v13 = *(uint32_t *)(v4[10] + 4 * v12);
      if ( ((*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 40))(v13, 18) != 0
         || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 40))(v13, 34) != 0)
        && dword_8F7C08 != v13 )
      {
        v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 124))(v13);
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 120))(v13);
        if ( (uint8_t)sub_48C0A0(v14, v16, &v17) != 0 )
        {
          v15 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*a2 + 8))(a2, v13, 0);
          if ( v3 == 0 || v15 < v22 )
          {
            v3 = v13;
            v22 = v15;
          }
        }
      }
      if ( --v23 < 0 )
        break;
      v4 = v21;
      v12 = v23;
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x45EAC0 sub_45EAC0
// ------------------------------------------------------------
int /*thiscall*/ sub_45EAC0(uint32_t *this, int a2)
{
  uint32_t *v2; // ebx
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // esi
  int v7; // ecx
  int v8; // eax
  int v9; // esi
  int v10; // ebx
  int v11; // ebx
  int v12; // ebx
  int v13; // ebx
  int v14; // eax
  uint32_t *v16; // [esp+4h] [ebp-10h]
  int v17; // [esp+8h] [ebp-Ch]
  int v18; // [esp+Ch] [ebp-8h]
  int v19; // [esp+10h] [ebp-4h]

  v2 = this;
  v3 = *(this + 14);
  v16 = v2;
  v19 = 0;
  v18 = 0;
  if ( v3 != 0 )
    v4 = (v2[15] - v3) >> 2;
  else
    v4 = 0;
  v5 = v4 - 1;
  v17 = v5;
  if ( v5 < 0 )
    return 0;
  while ( 1 )
  {
    v6 = 4 * v5;
    v7 = *(uint32_t *)(4 * v5 + v2[14]);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 289) != 0 )
    {
      v8 = v6 + v2[14];
      v9 = *(uint32_t *)v8;
      if ( *(uint8_t *)(*(uint32_t *)v8 + 977) == 0 )
      {
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 120))(v9) - 24;
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 444))(a2) >= v10 )
        {
          v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 120))(v9) + 24;
          if ( v11 >= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 440))(a2) )
          {
            v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 124))(v9) - 18;
            if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 452))(a2) >= v12 )
            {
              v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 124))(v9) + 18;
              if ( v13 >= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 448))(a2) )
              {
                v14 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a2 + 8))(a2, v9, 1);
                if ( v19 == 0 || v14 < v18 )
                {
                  v19 = v9;
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
    v2 = v16;
  }
  return v19;
}



// ------------------------------------------------------------
// 0x45EBE0 sub_45EBE0
// ------------------------------------------------------------
// id 对 → 对象查找（战斗分发器全 case 共用解析器）：
// 遍历 +2 对象表，vt+48/vt+52 返回值与 (a2,a3) 双字匹配 → 返回对象，未中 0
int /*thiscall*/ sub_45EBE0(uint32_t *this, int a2, int a3)
{
  int v4; // ecx
  int v5; // ebx
  int v6; // ecx
  int v8; // [esp+Ch] [ebp-4h]

  v4 = *(this + 2);
  v5 = 0;
  if ( v4 != 0 )
    v8 = (*(this + 3) - v4) >> 2;
  else
    v8 = 0;
  if ( v8 <= 0 )
    return 0;
  while ( 1 )
  {
    v6 = *(uint32_t *)(4 * v5 + *(this + 2));
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 48))(v6) == a2
      && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(4 * v5 + *(this + 2)) + 52))(*(uint32_t *)(4 * v5 + *(this + 2))) == a3 )
    {
      break;
    }
    if ( ++v5 >= v8 )
      return 0;
  }
  return *(uint32_t *)(*(this + 2) + 4 * v5);
}



// ------------------------------------------------------------
// 0x45EC70 sub_45EC70
// ------------------------------------------------------------
int /*thiscall*/ sub_45EC70(uint32_t *this)
{
  int v1; // eax
  int v2; // edi
  int result; // eax
  int v4; // esi
  int v5; // ebx
  int i; // [esp+8h] [ebp-4h]

  v1 = *(this + 30);
  if ( v1 != 0 )
    v2 = (*(this + 31) - v1) >> 2;
  else
    v2 = 0;
  result = 0;
  for ( i = 0; i < v2; ++i )
  {
    v4 = 0;
    v5 = 4 * result;
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*(this + 30) + 4 * v4) + 476))(
        *(uint32_t *)(*(this + 30) + 4 * v4),
        *(uint32_t *)(v5 + *(this + 30)));
      ++v4;
    }
    while ( v4 < v2 );
    result = i + 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x45ECE0 sub_45ECE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45ECE0(uint32_t *this)
{
  uint32_t *v2; // esi
  uint32_t *result; // eax

  v2 = (uint32_t *)*(this + 2);
  if ( v2 != (uint32_t *)*(this + 3) )
  {
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v2 + 12))(*v2);
      result = (uint32_t *)*(this + 3);
      ++v2;
    }
    while ( v2 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x45ED10 sub_45ED10
// ------------------------------------------------------------
char /*thiscall*/ sub_45ED10(int **this, char a2)
{
  int *i; // esi
  int v4; // ecx

  for ( i = *(this + 2); i != *(this + 3); ++i )
  {
    v4 = *i;
    if ( a2 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v4 + 228))(v4, 2, -1, 0);
    else
      (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t))(*(uint32_t *)v4 + 228))(v4, 0, -1, 0);
  }
  if ( a2 != 0 )
  {
    sub_699030((int)&unk_9B0C70);
    return sub_699030((int)&unk_99FC80);
  }
  else
  {
    sub_698FE0((int)&unk_9B0C70);
    return sub_698FE0((int)&unk_99FC80);
  }
}



// ------------------------------------------------------------
// 0x45ED80 sub_45ED80
// ------------------------------------------------------------
// 对象移除 —— 分发器 case 0x21 落点【推断：退场清理】
uint32_t */*thiscall*/ sub_45ED80(uint32_t *this, int a2)
{
  uint32_t *v3; // esi
  uint32_t *result; // eax

  v3 = (uint32_t *)*(this + 30);
  if ( v3 != (uint32_t *)*(this + 31) )
  {
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*v3 + 536))(*v3, a2);
      result = (uint32_t *)*(this + 31);
      ++v3;
    }
    while ( v3 != result );
  }
  return result;
}



// ------------------------------------------------------------
// 0x45EDB0 sub_45EDB0
// ------------------------------------------------------------
DWORD /*thiscall*/ sub_45EDB0(uint32_t *this)
{
  DWORD result; // eax
  int v3; // edx
  int v4; // eax
  int v5; // esi
  int v6; // ecx
  uint32_t *v7; // esi
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
  int v18; // [esp+1Ch] [ebp-4h]

  result = GetTickCount();
  if ( *(this + 39) + 1000 <= result )
  {
    *(this + 39) = GetTickCount();
    v3 = *(uint32_t *)dword_8F8520;
    v17 = 0;
    (*(void (/*thiscall*/ **)(int, int, int))(v3 + 8))(dword_8F8520, 34, 2);
    v4 = *(this + 30);
    v18 = v4 != 0 ? (*(this + 31) - v4) >> 2 : 0;
    result = 0;
    v14 = 0;
    if ( v18 > 0 )
    {
      do
      {
        v5 = 4 * result;
        v6 = *(uint32_t *)(4 * result + *(this + 30));
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 40))(v6, 529) != 0
          && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v5 + *(this + 30)) + 308))(*(uint32_t *)(v5 + *(this + 30))) != 0 )
        {
          v7 = *(uint32_t **)(v5 + *(this + 30));
          if ( (*(int (/*thiscall*/ **)(uint32_t *))(*v7 + 840))(v7) == 0 )
          {
            v8 = v7[1908];
            v13 = v7[1909];
            (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(*v7 + 1124))(v7, &v16, &v15);
            if ( v8 != v16 || v13 != v15 )
            {
              v9 = *(uint32_t *)dword_8F8520;
              v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*v7 + 48))(v7);
              (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
              v11 = *(uint32_t *)dword_8F8520;
              v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*v7 + 52))(v7);
              (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v16);
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v15);
              ++v17;
            }
          }
        }
        result = ++v14;
      }
      while ( v14 < v18 );
      result = v17;
      if ( v17 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0xFFFF);
        return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
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
int /*thiscall*/ sub_45EF30(uint32_t *this)
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
    result = (*(int (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, v12);
    if ( v12[0] == 0xFFFF )
      break;
    v1 += 0xFFFF;
    v9 = v1;
    (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v11);
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &v14);
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &v13);
    v3 = sub_45EBE0(this, v12[0], v11);
    v4 = (uint32_t *)__RTDynamicCast(v3, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
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
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*v4 + 1128))(v4, v5, v8, v6, v7);
      v1 = v9;
    }
    if ( (uint16_t)v1 == 0 )
      return off_77F3FC(aCriticalErrorC_1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x45F040 sub_45F040
// ------------------------------------------------------------
void /*thiscall*/ sub_45F040(void *this)
{
  *((uint32_t *)this + 33) = 0;
  *(uint32_t *)this = 0;
  *((uint8_t *)this + 152) = 0;
  if ( *((uint32_t *)this + 2) != 0 )
    j__free(*((void **)this + 2));
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint8_t *)this + 153) = 0;
}



// ------------------------------------------------------------
// 0x45F080 sub_45F080
// ------------------------------------------------------------
void /*thiscall*/ sub_45F080(int this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // esi
  int v5; // ecx
  void (/*thiscall*/ ***v6)(uint32_t, int); // eax
  int v7; // esi
  int i; // ebx
  int v9; // [esp+Ch] [ebp-4h]

  v2 = *(uint32_t *)(this + 8);
  v3 = 0;
  if ( v2 != 0 )
    v9 = (*(uint32_t *)(this + 12) - v2) >> 2;
  else
    v9 = 0;
  if ( v9 > 0 )
  {
    do
    {
      v4 = 4 * v3;
      v5 = *(uint32_t *)(4 * v3 + *(uint32_t *)(this + 8));
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v5 + 76))(v5, 0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(uint32_t *)(this + 8)) + 40))(
             *(uint32_t *)(v4 + *(uint32_t *)(this + 8)),
             273) == 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(uint32_t *)(this + 8)) + 40))(
             *(uint32_t *)(v4 + *(uint32_t *)(this + 8)),
             18) == 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(uint32_t *)(this + 8)) + 40))(
             *(uint32_t *)(v4 + *(uint32_t *)(this + 8)),
             65) == 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(uint32_t *)(this + 8)) + 40))(
             *(uint32_t *)(v4 + *(uint32_t *)(this + 8)),
             66) == 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(uint32_t *)(this + 8)) + 40))(
             *(uint32_t *)(v4 + *(uint32_t *)(this + 8)),
             129) == 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(uint32_t *)(this + 8)) + 40))(
             *(uint32_t *)(v4 + *(uint32_t *)(this + 8)),
             130) == 0 )
      {
        v6 = *(void (/*thiscall*/ ****)(uint32_t, int))(v4 + *(uint32_t *)(this + 8));
        if ( v6 != nullptr )
          (**v6)(v6, 1);
      }
      ++v3;
    }
    while ( v3 < v9 );
  }
  if ( *(uint32_t *)(this + 8) != 0 )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  v7 = this + 24;
  for ( i = 6; i != 0; --i )
  {
    if ( *(uint32_t *)v7 != 0 )
      j__free(*(void **)v7);
    *(uint32_t *)v7 = 0;
    *(uint32_t *)(v7 + 4) = 0;
    *(uint32_t *)(v7 + 8) = 0;
    v7 += 16;
  }
  if ( *(uint32_t *)(this + 120) != 0 )
    j__free(*(void **)(this + 120));
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
}



// ------------------------------------------------------------
// 0x45F1E0 sub_45F1E0
// ------------------------------------------------------------
void /*userpurge*/ sub_45F1E0(int a1@<ecx>, int a2@<ebx>, uint32_t *a3)
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

  if ( a3 != nullptr )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a3 + 40))(a3, 18) != 0 )
      sub_45F1E0(a3[162]);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int))(*a3 + 40))(a3, 33, a2) != 0 )
    {
      v5 = *(uint32_t **)(*(uint32_t *)(a1 + 132) + 44);
      v30 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 52))(a3);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 48))(a3);
      if ( sub_48C990(v5, v6, v30) != 0 )
      {
        v7 = *(int **)(*(uint32_t *)(a1 + 132) + 44);
        v29 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 52))(a3);
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 48))(a3);
        sub_48DA40(v7, v8, v29, 1);
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*a3 + 300))(a3, a3);
    v9 = *(uint32_t *)(a1 + 8);
    if ( v9 != 0 )
      v10 = (*(uint32_t *)(a1 + 12) - v9) >> 2;
    else
      v10 = 0;
    v11 = 0;
    for ( i = 0; v11 < v10; i = v11 )
    {
      v12 = *(uint32_t **)(*(uint32_t *)(a1 + 8) + 4 * v11);
      if ( v12 != a3 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v12 + 300))(v12, a3);
        v11 = i;
      }
      ++v11;
    }
    v13 = 0;
    if ( v10 > 0 )
    {
      v14 = *(uint32_t **)(a1 + 8);
      while ( (uint32_t *)*v14 != a3 )
      {
        ++v13;
        ++v14;
        if ( v13 >= v10 )
          goto LABEL_20;
      }
      memcpy_0(
        (void *)(*(uint32_t *)(a1 + 8) + 4 * v13),
        (const void *)(*(uint32_t *)(a1 + 8) + 4 * v13 + 4),
        4 * ((*(uint32_t *)(a1 + 12) - (*(uint32_t *)(a1 + 8) + 4 * v13 + 4)) >> 2));
      *(uint32_t *)(a1 + 12) -= 4;
    }
LABEL_20:
    v15 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 36))(a3) + 8);
    if ( v15 != 6 )
    {
      v16 = 16 * v15 + a1;
      v17 = *(uint32_t *)(v16 + 24);
      v18 = v17 != 0 ? (*(uint32_t *)(v16 + 28) - v17) >> 2 : 0;
      v19 = 0;
      if ( v18 > 0 )
      {
        v20 = *(uint32_t **)(v16 + 24);
        while ( (uint32_t *)*v20 != a3 )
        {
          ++v19;
          ++v20;
          if ( v19 >= v18 )
            goto LABEL_30;
        }
        memcpy_0(
          (void *)(*(uint32_t *)(v16 + 24) + 4 * v19),
          (const void *)(*(uint32_t *)(v16 + 24) + 4 * v19 + 4),
          4 * ((*(uint32_t *)(v16 + 28) - (*(uint32_t *)(v16 + 24) + 4 * v19 + 4)) >> 2));
        *(uint32_t *)(v16 + 28) -= 4;
      }
    }
LABEL_30:
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a3 + 40))(a3, 1) != 0
      && (*(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 36))(a3) + 8) == 1
       || *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 36))(a3) + 8) == 2) )
    {
      v21 = *(uint32_t *)(a1 + 120);
      v22 = v21 != 0 ? (*(uint32_t *)(a1 + 124) - v21) >> 2 : 0;
      v23 = 0;
      if ( v22 > 0 )
      {
        v24 = *(uint32_t **)(a1 + 120);
        while ( (uint32_t *)*v24 != a3 )
        {
          ++v23;
          ++v24;
          if ( v23 >= v22 )
            goto LABEL_42;
        }
        memcpy_0(
          (void *)(*(uint32_t *)(a1 + 120) + 4 * v23),
          (const void *)(*(uint32_t *)(a1 + 120) + 4 * v23 + 4),
          4 * ((*(uint32_t *)(a1 + 124) - (*(uint32_t *)(a1 + 120) + 4 * v23 + 4)) >> 2));
        *(uint32_t *)(a1 + 124) -= 4;
      }
    }
LABEL_42:
    v25 = 0;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a3 + 76))(a3, 0);
    if ( *(uint8_t *)(a1 + 152) == 1
      && dword_8F7C04 != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a3 + 40))(a3, 1) != 0 )
    {
      v26 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);
      v27 = *(uint32_t *)(a1 + 120);
      v31 = v26;
      if ( v27 != 0 )
        v33 = (*(uint32_t *)(a1 + 124) - v27) >> 2;
      else
        v33 = 0;
      if ( v33 > 0 )
      {
        do
        {
          v28 = *(uint32_t **)(*(uint32_t *)(a1 + 120) + 4 * v25);
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v28 + 40))(v28, 17) != 0 )
          {
            if ( (*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 376))(v28) != v31 )
              break;
          }
          else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v28 + 40))(v28, 33) != 0 && v28[169] == 1 )
          {
            break;
          }
          ++v25;
        }
        while ( v25 < v33 );
      }
      if ( v25 == v33 )
      {
        off_77F3FC((char *)&byte_6C7448);
        *(uint8_t *)(a1 + 152) = 0;
        sub_432EA0("ELVEN_GATE", -1, 0, 0);
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )
          sub_47BE30(**(uint32_t **)(*(uint32_t *)(a1 + 132) + 44));
      }
    }
  }
}


// ------------------------------------------------------------
// 0x45F4D0 sub_45F4D0
// ------------------------------------------------------------
void /*thiscall*/ sub_45F4D0(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // ebx
  int v5; // ecx
  int v6; // [esp+8h] [ebp-4h]

  v3 = *(this + 2);
  v4 = 0;
  if ( v3 != 0 )
    v6 = (*(this + 3) - v3) >> 2;
  else
    v6 = 0;
  if ( v6 > 0 )
  {
    do
    {
      v5 = *(uint32_t *)(4 * v4 + *(this + 2));
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 40))(v5, a2) != 0 )
      {
        sub_45F1E0((int)this, v4, *(uint32_t **)(*(this + 2) + 4 * v4));
        --v4;
        --v6;
      }
      ++v4;
    }
    while ( v4 < v6 );
  }
}



// ------------------------------------------------------------
// 0x45F550 sub_45F550
// ------------------------------------------------------------
int /*thiscall*/ sub_45F550(int *this)
{
  int result; // eax
  int v3; // ebx
  int v4; // edi
  int v5; // ecx
  uint32_t *v6; // edi
  int v7; // [esp+8h] [ebp-4h]

  result = *(this + 2);
  v3 = 0;
  if ( result != 0 )
    v7 = (*(this + 3) - result) >> 2;
  else
    v7 = 0;
  if ( v7 > 0 )
  {
    do
    {
      v4 = 4 * v3;
      v5 = *(uint32_t *)(4 * v3 + *(this + 2));
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 88))(v5) == 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(this + 2)) + 40))(
               *(uint32_t *)(v4 + *(this + 2)),
               273) != 0
          || (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(this + 2)) + 40))(
               *(uint32_t *)(v4 + *(this + 2)),
               18) != 0
          || (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(this + 2)) + 40))(
               *(uint32_t *)(v4 + *(this + 2)),
               65) != 0
          || (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(this + 2)) + 40))(
               *(uint32_t *)(v4 + *(this + 2)),
               129) != 0
          || (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v4 + *(this + 2)) + 40))(
               *(uint32_t *)(v4 + *(this + 2)),
               130) != 0 )
        {
          sub_45F1E0((int)this, v3, *(uint32_t **)(*(this + 2) + 4 * v3));
        }
        else
        {
          v6 = *(uint32_t **)(v4 + *(this + 2));
          sub_45F1E0((int)this, v3, v6);
          if ( v6 != nullptr )
            (*(void (/*thiscall*/ **)(uint32_t *, int))*v6)(v6, 1);
        }
        --v3;
        --v7;
      }
      result = v7;
      ++v3;
    }
    while ( v3 < v7 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x45F660 sub_45F660
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45F660(uint32_t *this, int a2)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax

  v3 = (uint32_t *)*(this + 36);
  result = (uint32_t *)*(this + 35);
  if ( result != v3 )
  {
    do
    {
      if ( *result == a2 )
        break;
      ++result;
    }
    while ( result != v3 );
    if ( result != v3 )
    {
      memcpy_0(result, result + 1, 4 * ((*(this + 36) - (int)(result + 1)) >> 2));
      result = (uint32_t *)(*(this + 36) - 4);
      *(this + 36) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x45F6C0 sub_45F6C0
// ------------------------------------------------------------
DWORD /*thiscall*/ sub_45F6C0(int *this)
{
  unsigned int i; // edi
  int v3; // ecx

  for ( i = 0; ; ++i )
  {
    v3 = *(this + 2);
    if ( v3 == 0 || i >= (*(this + 3) - v3) >> 2 )
      break;
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v3 + 4 * i) + 28))(*(uint32_t *)(v3 + 4 * i));
  }
  sub_45F550(this);
  sub_45EC70(this);
  return sub_45EDB0(this);
}



// ------------------------------------------------------------
// 0x45F700 sub_45F700
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_45F700(int this, unsigned int a2)
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
    sub_427E20(this);
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
// 0x45F7D0 sub_45F7D0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_45F7D0(int this, unsigned int a2)
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
    sub_42CB90(this);
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
// 0x45F8A0 sub_45F8A0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_45F8A0(int this, int Src, unsigned int a3, int *a4)
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
      sub_42CB90(this);
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
// 0x45FA80 sub_45FA80
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_45FA80(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // esi
  int v5; // edi
  unsigned int result; // eax
  int v7; // esi
  int v8; // edi

  *(this + 39) = GetTickCount();
  *this = a2;
  v3 = (int)(this + 1);
  if ( a2 != 0 )
  {
    sub_45F7D0(v3, 0x64u);
    v7 = 0;
    v8 = (int)(this + 5);
    do
    {
      result = sub_45F7D0(v8, v7++ != 1 ? 5 : 100);
      v8 += 16;
    }
    while ( v7 < 6 );
  }
  else
  {
    sub_45F7D0(v3, 0xC8u);
    v4 = 0;
    v5 = (int)(this + 5);
    do
    {
      sub_45F7D0(v5, v4++ != 1 ? 30 : 100);
      v5 += 16;
    }
    while ( v4 < 6 );
    return sub_45F700((int)(this + 29), 0x64u);
  }
  return result;
}



// ============================================================
// 【分区 13】NPC 与对象注册（0x45FB20-0x460000）
// CNRDNpc__vmt0/vmt154（RTTI 自证）；0x45FE80 = 对象注册
// （分发器 case 0x15/0x16 与 ui_icon_perf 0x4600B0 的注册链入口）。
// ============================================================
// ------------------------------------------------------------
// 0x45FB20 sub_45FB20
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_45FB20(uint32_t *this, uint32_t *a2, void *Src, int *a4)
{
  int v5; // ecx
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) >> 2 != 0 )
    v6 = ((int)Src - v5) >> 2;
  else
    v6 = 0;
  sub_45F8A0((int)this, (int)Src, 1u, a4);
  *a2 = *(this + 1) + 4 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x45FB80 CNRDNpc__vmt154
// ------------------------------------------------------------
int /*thiscall*/ CNRDNpc__vmt154(uint32_t *this)
{
  return sub_56CFE0(*(this + 71));
}



// ------------------------------------------------------------
// 0x45FB90 CNRDNpc__vmt0
// ------------------------------------------------------------
// CNRDNpc::vmt0 —— NPC 对象构造（RTTI 自证）
void */*thiscall*/ CNRDNpc__vmt0(void *Block, char a2)
{
  sub_45FBC0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x45FBC0 sub_45FBC0
// ------------------------------------------------------------
int /*thiscall*/ sub_45FBC0(void **this)
{
  *this = &vftbl_CNRDNpc;
  nullsub_3();
  return sub_42A450(this);
}



// ------------------------------------------------------------
// 0x45FC10 sub_45FC10
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_45FC10(int *this, int *a2)
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
    return sub_45F8A0((int)this, *(this + 2), 1u, a2);
  v4 = (int *)*(this + 2);
  *v4 = *a2;
  result = (unsigned int)(v4 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x45FC60 sub_45FC60
// ------------------------------------------------------------
void /*thiscall*/ sub_45FC60(int this)
{
  int *v2; // esi
  bool v3; // zf
  char *v4; // edi
  uint32_t *i; // edi
  uint32_t *v6; // esi
  int v7; // esi
  int j; // edi
  void *v9; // ecx
  uint8_t v10[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *v12; // [esp+14h] [ebp-18h]
  int v13; // [esp+18h] [ebp-14h]
  void *Src; // [esp+1Ch] [ebp-10h]
  int v15; // [esp+28h] [ebp-4h]

  Block = nullptr;
  v12 = nullptr;
  v13 = 0;
  v2 = *(int **)(this + 8);
  v3 = v2 == *(int **)(this + 12);
  v15 = 0;
  if ( !v3 )
  {
    Src = v2 + 1;
    do
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*v2 + 40))(*v2, 273) != 0
        || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*v2 + 40))(*v2, 18) != 0
        || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*v2 + 40))(*v2, 65) != 0
        || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*v2 + 40))(*v2, 66) != 0
        || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*v2 + 40))(*v2, 129) != 0
        || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)*v2 + 40))(*v2, 130) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)*v2 + 76))(*v2, 0);
        v4 = (char *)v12;
        if ( Block != nullptr && ((uint8_t *)v12 - (uint8_t *)Block) >> 2 < (unsigned int)((v13 - (int)Block) >> 2) )
        {
          *(uint32_t *)v12 = *v2;
          v12 = v4 + 4;
        }
        else
        {
          sub_45F8A0((int)v10, (int)v12, 1u, v2);
        }
        memcpy_0(v2, Src, 4 * ((*(uint32_t *)(this + 12) - (int)Src) >> 2));
        *(uint32_t *)(this + 12) -= 4;
      }
      else
      {
        ++v2;
        Src = (char *)Src + 4;
      }
    }
    while ( v2 != *(int **)(this + 12) );
  }
  for ( i = *(uint32_t **)(this + 8); i != *(uint32_t **)(this + 12); ++i )
  {
    v6 = Block;
    if ( Block != v12 )
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*v6 + 300))(*v6, *i);
        ++v6;
      }
      while ( v6 != v12 );
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*i + 76))(*i, 0);
    if ( *i != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*i)(*i, 1);
  }
  if ( *(uint32_t *)(this + 8) != 0 )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  v7 = this + 24;
  for ( j = 6; j != 0; --j )
  {
    if ( *(uint32_t *)v7 != 0 )
      j__free(*(void **)v7);
    *(uint32_t *)v7 = 0;
    *(uint32_t *)(v7 + 4) = 0;
    *(uint32_t *)(v7 + 8) = 0;
    v7 += 16;
  }
  if ( *(uint32_t *)(this + 120) != 0 )
    j__free(*(void **)(this + 120));
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  if ( *(uint32_t *)(this + 140) != 0 )
    j__free(*(void **)(this + 140));
  v9 = Block;
  v3 = Block == nullptr;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint8_t *)(this + 152) = 0;
  *(uint8_t *)(this + 153) = 0;
  if ( !v3 )
    j__free(v9);
}



// ------------------------------------------------------------
// 0x45FE80 sub_45FE80
// ------------------------------------------------------------
// 对象注册（场景对象表插入）—— 分发器 case 0x15/0x16 与
// ui_icon_perf 0x4600B0 的注册链入口；参数 (容器, 源表, a2, a3, 对象, 0, 0)
void /*userpurge*/ sub_45FE80(int a1@<ecx>, int a2@<edi>, int a3, int a4, int a5, int a6, int a7)
{
  int v7; // esi
  int v9; // ecx
  int v10; // edi
  void *v11; // ebx
  int v12; // eax
  int v13; // ebx
  int i; // edi
  int v15; // ecx
  int v16; // ebx
  int v17; // edi
  int v18; // [esp+8h] [ebp-Ch]
  void *Src; // [esp+Ch] [ebp-8h] BYREF
  int v20; // [esp+10h] [ebp-4h]

  v7 = a5;
  v20 = a1;
  if ( a5 != 0 && (uint8_t)sub_45E680(a5) == 0 )
  {
    *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 36))(v7) = a3;
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 36))(v7) + 4) = a4;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 80))(v7) != 0 )
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 80))(v7);
      sub_45F1E0(v7);
    }
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v7 + 76))(v7, a1, a2);
    v18 = a1 + 4;
    sub_45FC10(&a5);
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 36))(v7) + 8) != 6 )
    {
      v9 = 16 * *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 36))(v7) + 8);
      v10 = v9 + a1 + 20;
      if ( a6 != 0 )
      {
        v11 = *(void **)(v9 + a1 + 28);
        sub_45E5A0(&Src, *(uint32_t *)(v10 + 4), v11, &a6);
        if ( Src == v11 )
        {
          sub_45FC10(&a5);
        }
        else if ( (uint8_t)a7 != 0 )
        {
          sub_45FB20((int)&a7, Src, (int)&a5);
        }
        else
        {
          sub_45FB20((int)&a7, (char *)Src + 4, (int)&a5);
        }
      }
      else
      {
        sub_45FC10(&a5);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 1) != 0
      && (*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 36))(v7) + 8) == 1
       || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 36))(v7) + 8) == 2) )
    {
      a7 = v7;
      sub_428430(&a7);
    }
    if ( dword_8F7C04 != 0 && a3 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04) )
      sub_45F660(a4);
    v12 = *(uint32_t *)(v18 + 4);
    if ( v12 != 0 )
      v13 = (*(uint32_t *)(v18 + 8) - v12) >> 2;
    else
      v13 = 0;
    for ( i = 0; i < v13; ++i )
    {
      v15 = *(uint32_t *)(*(uint32_t *)(v20 + 8) + 4 * i);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 296))(v15, v7);
    }
    v16 = v20;
    if ( *(uint8_t *)(v20 + 152) == 0
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 17) != 0
      && dword_8F7C04 != 0 )
    {
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);
      if ( v17 != (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 376))(v7) )
        *(uint8_t *)(v16 + 152) = 1;
    }
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 12))(v7);
  }
}


