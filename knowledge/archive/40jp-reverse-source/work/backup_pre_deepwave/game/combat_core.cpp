// ============================================================
// 【40JP逆向源代码工程】game/combat_core.cpp
// 模块: ActiveObject战斗核心/怪物生成
// 来源: work/dump_misca.txt  区块: 0x4D0000-0x4E0000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
//        语义与 IDA Hex-Rays 逐字对应; 逐行精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 224
// ------------------------------------------------------------
// ★ 本文件已按《20_打击感与HitStop系统研究》定案锚点升级注释（研究 20 §x 为引）：
//   0x4D71B0 命中主处理器 vt+512（§2 全文定案）
//   0x4D6D90 攻方完整反应 vt+500（§8 双向卡肉入口）
//   0x4D4D40 HP setter vt+728（§1.1；DLL 锚点 [13]）
//   0x4D7960 飘字咽喉（§1.1 case 0x14；第 14/39 轮 5 层精灵）
//   0x4D46C0/0x4D7000 构造初始化与析构（§13 17 状态槽 + 18 观察者槽）
//   0x4D6A80 多命中盒碰撞 vt+480（§1.2）、0x4D9840 主状态包装器（§4.2）
//   0x4D5170 霸体 setter vt+720（§1.2）、0x4D5140 状态激活查询 vt+776
//   0x4D9F20 格挡时刻戳 vt+548（§1.2）、0x4D6690 硬直强度 vt+704（第 27 轮）
// ------------------------------------------------------------
// 交叉引用：已被 L1 逐行精修的重复函数（以 cnrd/ 版为准，此处保留 L2 转写体）：
//   0x4D49A0/0x4D49E0/0x4D4A20/0x4D4A80 → src/cnrd/IRDActiveObject.cpp:134/54/28/42
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】数据对象构造/析构族（对象工厂 case 0..14 的布局还原）
// 依据：研究 18/19 定案 —— 全 PE 无 [weight] 标签，怪物"重量"出自
// MonsterBaseParameter.tbl；case 1 = 0x5A0 角色/怪物数据对象
// （[hit recovery] +396/+400、[jump power] +404、[stuckbonus on damage] +428..440 四档）。
// 本区函数 = 各 case 的构造器（+396/+404/+428 族初始化可直读）与配套析构器。
// ============================================================

// ------------------------------------------------------------
// 0x4D01E0 sub_4D01E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D01E0(int this)
{
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  `eh vector constructor iterator'(
    (void *)(this + 64),
    0x10u,
    4,
    (void (/*thiscall*/ *)(void *))sub_4019A0,
    (void (/*thiscall*/ *)(void *))sub_5E5260);
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 532) = 15;
  *(uint32_t *)(this + 528) = 0;
  *(uint8_t *)(this + 512) = 0;
  *(uint32_t *)(this + 564) = 15;
  *(uint32_t *)(this + 560) = 0;
  *(uint8_t *)(this + 544) = 0;
  *(uint32_t *)(this + 592) = 15;
  *(uint32_t *)(this + 588) = 0;
  *(uint8_t *)(this + 572) = 0;
  *(uint32_t *)(this + 620) = 15;
  *(uint32_t *)(this + 616) = 0;
  *(uint8_t *)(this + 600) = 0;
  `eh vector constructor iterator'((void *)(this + 624), 0x1Cu, 2, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);
  *(uint32_t *)(this + 704) = 15;
  *(uint32_t *)(this + 700) = 0;
  *(uint8_t *)(this + 684) = 0;
  *(uint32_t *)(this + 732) = 15;
  *(uint32_t *)(this + 728) = 0;
  *(uint8_t *)(this + 712) = 0;
  *(uint32_t *)(this + 760) = 15;
  *(uint32_t *)(this + 756) = 0;
  *(uint8_t *)(this + 740) = 0;
  *(uint32_t *)(this + 788) = 15;
  *(uint32_t *)(this + 784) = 0;
  *(uint8_t *)(this + 768) = 0;
  *(uint32_t *)(this + 796) = 0;
  *(uint32_t *)(this + 800) = 0;
  *(uint32_t *)(this + 804) = 0;
  *(uint32_t *)(this + 812) = 0;
  *(uint32_t *)(this + 816) = 0;
  *(uint32_t *)(this + 820) = 0;
  *(uint32_t *)(this + 848) = 15;
  *(uint32_t *)(this + 844) = 0;
  *(uint8_t *)(this + 828) = 0;
  *(uint32_t *)(this + 856) = 0;
  *(uint32_t *)(this + 860) = 0;
  *(uint32_t *)(this + 864) = 0;
  *(uint32_t *)(this + 872) = 0;
  *(uint32_t *)(this + 876) = 0;
  *(uint32_t *)(this + 880) = 0;
  *(uint32_t *)(this + 888) = 0;
  *(uint32_t *)(this + 892) = 0;
  *(uint32_t *)(this + 896) = 0;
  *(uint32_t *)(this + 904) = 0;
  *(uint32_t *)(this + 908) = 0;
  *(uint32_t *)(this + 912) = 0;
  *(uint32_t *)(this + 952) = 15;
  *(uint32_t *)(this + 948) = 0;
  *(uint8_t *)(this + 932) = 0;
  `eh vector constructor iterator'((void *)(this + 956), 0x10u, 29, (void (/*thiscall*/ *)(void *))sub_4019A0, sub_401940);
  *(uint32_t *)(this + 1424) = 0;
  *(uint32_t *)(this + 1428) = 0;
  *(uint32_t *)(this + 1432) = 0;
  sub_4CEB80((char *)this);
  return this;
}



// ------------------------------------------------------------
// 0x4D03E0 sub_4D03E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D03E0(int this)
{
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 96) = 15;
  *(uint32_t *)(this + 92) = 0;
  *(uint8_t *)(this + 76) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 140) = 15;
  *(uint32_t *)(this + 136) = 0;
  *(uint8_t *)(this + 120) = 0;
  *(uint32_t *)(this + 168) = 15;
  *(uint32_t *)(this + 164) = 0;
  *(uint8_t *)(this + 148) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 244) = 15;
  *(uint32_t *)(this + 240) = 0;
  *(uint8_t *)(this + 224) = 0;
  sub_4CF050((void *)this);
  return this;
}



// ------------------------------------------------------------
// 0x4D04C0 sub_4D04C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D04C0(int this)
{
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 104) = 15;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 84) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 196) = 15;
  *(uint32_t *)(this + 192) = 0;
  *(uint8_t *)(this + 176) = 0;
  sub_4CF120((char *)this);
  return this;
}



// ------------------------------------------------------------
// 0x4D0570 sub_4D0570
// ------------------------------------------------------------
int /*thiscall*/ sub_4D0570(int this)
{
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 124) = 15;
  *(uint32_t *)(this + 120) = 0;
  *(uint8_t *)(this + 104) = 0;
  *(uint32_t *)(this + 152) = 15;
  *(uint32_t *)(this + 148) = 0;
  *(uint8_t *)(this + 132) = 0;
  *(uint32_t *)(this + 180) = 15;
  *(uint32_t *)(this + 176) = 0;
  *(uint8_t *)(this + 160) = 0;
  *(uint32_t *)(this + 208) = 15;
  *(uint32_t *)(this + 204) = 0;
  *(uint8_t *)(this + 188) = 0;
  *(uint32_t *)(this + 236) = 15;
  *(uint32_t *)(this + 232) = 0;
  *(uint8_t *)(this + 216) = 0;
  *(uint32_t *)(this + 264) = 15;
  *(uint32_t *)(this + 260) = 0;
  *(uint8_t *)(this + 244) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;
  *(uint32_t *)(this + 280) = 0;
  *(uint32_t *)(this + 288) = 0;
  *(uint32_t *)(this + 292) = 0;
  *(uint32_t *)(this + 296) = 0;
  *(uint32_t *)(this + 304) = 0;
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 324) = 0;
  *(uint32_t *)(this + 328) = 0;
  *(uint32_t *)(this + 356) = 15;
  *(uint32_t *)(this + 352) = 0;
  *(uint8_t *)(this + 336) = 0;
  sub_4CF290((char *)this);
  return this;
}



// ------------------------------------------------------------
// 0x4D0680 sub_4D0680
// ------------------------------------------------------------
int /*thiscall*/ sub_4D0680(int this)
{
  void **pThis_4; // ecx

  pThis_4 = (void **)(this + 4);
  *pThis_4 = nullptr;
  sub_41BFE0(pThis_4, szPassword);
  *(uint32_t *)(this + 8) = 0;
  sub_41BFE0((void **)(this + 8), szPassword);
  *(uint32_t *)(this + 12) = 0;
  sub_41BFE0((void **)(this + 12), szPassword);
  *(uint32_t *)(this + 16) = 0;
  sub_41BFE0((void **)(this + 16), szPassword);
  *(uint32_t *)(this + 80) = 0;
  sub_41BFE0((void **)(this + 80), szPassword);
  *(uint32_t *)(this + 88) = 0;
  sub_41BFE0((void **)(this + 88), szPassword);
  *(uint32_t *)(this + 104) = 0;
  sub_41BFE0((void **)(this + 104), szPassword);
  *(uint32_t *)(this + 108) = 0;
  sub_41BFE0((void **)(this + 108), szPassword);
  *(uint32_t *)(this + 112) = 0;
  sub_41BFE0((void **)(this + 112), szPassword);
  *(uint32_t *)(this + 116) = 0;
  sub_41BFE0((void **)(this + 116), szPassword);
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  sub_4CF480((void *)this);
  return this;
}



// ------------------------------------------------------------
// 0x4D07A0 sub_4D07A0
// ------------------------------------------------------------
char */*thiscall*/ sub_4D07A0(char *this)
{
  char *pThis_10; // ecx

  pThis_10 = this + 16;
  *((uint32_t *)pThis_10 + 6) = 15;
  *((uint32_t *)pThis_10 + 5) = 0;
  pThis_10[4] = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 1) = 0;
  *((uint32_t *)this + 2) = 0;
  *(this + 12) = 0;
  sub_4015C0((size_t *)pThis_10, szPassword, 0);  // 【std::string构造赋值】
  if ( *((uint32_t *)this + 12) != 0 )
    j__free(*((void **)this + 12));
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4D0830 sub_4D0830
// ------------------------------------------------------------
char */*thiscall*/ sub_4D0830(char *this)
{
  char *pThis_4; // ecx

  pThis_4 = this + 4;
  *((uint32_t *)pThis_4 + 6) = 15;
  *((uint32_t *)pThis_4 + 5) = 0;
  pThis_4[4] = 0;
  *((uint32_t *)this + 14) = 15;
  *((uint32_t *)this + 13) = 0;
  *(this + 36) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  *(uint32_t *)this = 0;
  sub_4015C0((size_t *)pThis_4, szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 8, szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 15) = 0;
  if ( *((uint32_t *)this + 17) != 0 )
    j__free(*((void **)this + 17));
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4D1680 sub_4D1680
// ------------------------------------------------------------
int /*thiscall*/ sub_4D1680(int this)
{
  int pThis_4; // edi
  uint32_t *pThis_158; // eax
  int i; // ecx

  pThis_4 = this + 4;
  *(uint32_t *)(this + 8) = sub_425940(this + 4);
  *(uint32_t *)(pThis_4 + 8) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 40) = sub_4CE710();
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 52) = sub_4CE730();
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 84) = sub_4CE750();
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 96) = sub_4CE770();
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 248) = 0;
  *(uint32_t *)(this + 252) = 0;
  *(uint32_t *)(this + 256) = 0;
  *(uint32_t *)(this + 260) = 0;
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;
  *(uint32_t *)(this + 304) = 15;
  *(uint32_t *)(this + 300) = 0;
  *(uint8_t *)(this + 284) = 0;
  *(uint32_t *)(this + 332) = 15;
  *(uint32_t *)(this + 328) = 0;
  *(uint8_t *)(this + 312) = 0;
  pThis_158 = (uint32_t *)(this + 344);
  for ( i = 3; i != 0; --i )
  {
    *pThis_158 = 0;
    pThis_158[1] = 0;
    pThis_158[2] = 0;
    pThis_158[3] = 0;
    pThis_158 += 4;
  }
  sub_4CE9F0((uint32_t *)(this + 396));
  *(uint32_t *)(this + 444) = 0;
  *(uint32_t *)(this + 448) = 0;
  *(uint32_t *)(this + 452) = 0;
  *(uint32_t *)(this + 460) = 0;
  *(uint32_t *)(this + 464) = 0;
  *(uint32_t *)(this + 468) = 0;
  *(uint32_t *)(this + 424) = 0;
  *(uint32_t *)(this + 428) = 0;
  *(uint32_t *)(this + 432) = 0;
  *(uint32_t *)(this + 436) = 0;
  *(uint32_t *)(this + 424) = this + 396;
  sub_4D13A0(this);
  return this;
}



// ------------------------------------------------------------
// 0x4D1860 sub_4D1860
// ------------------------------------------------------------
void /*thiscall*/ sub_4D1860(int this)
{
  uint32_t *pThis_1AC; // eax
  int v3; // edi
  void **fld_10C; // edi
  uint32_t *fld_AC; // edi
  uint32_t *fld_B0; // eax
  uint32_t *v7; // edi
  void **fld_90; // edi
  void **fld_80; // edi
  void **fld_60; // eax
  void **v11; // edi
  bool fld_602; // zf
  uint32_t **fld_54; // eax
  uint32_t *v14; // edi
  uint32_t *fld_542; // eax
  void *v16; // eax
  int fld_40; // eax
  int fld_44; // edx
  int v19; // edi
  uint32_t **fld_34; // ecx
  uint32_t *v21; // eax
  uint32_t *v22; // edi
  void **fld_28; // eax
  void **v24; // edi
  void **fld_282; // eax
  uint32_t **fld_8; // ecx
  uint32_t *v27; // eax
  uint32_t *v28; // edi
  int i; // [esp+10h] [ebp-14h]
  void **j; // [esp+10h] [ebp-14h]
  uint32_t *fld_B02; // [esp+10h] [ebp-14h]
  void **k; // [esp+10h] [ebp-14h]
  void **m; // [esp+10h] [ebp-14h]
  void **v34; // [esp+10h] [ebp-14h]
  uint32_t *v35; // [esp+10h] [ebp-14h]
  int fld_402; // [esp+10h] [ebp-14h]
  void **v37; // [esp+10h] [ebp-14h]
  uint32_t *pThis_1AC2; // [esp+14h] [ebp-10h]
  int fld_442; // [esp+14h] [ebp-10h]

  pThis_1AC = (uint32_t *)(this + 428);
  pThis_1AC2 = (uint32_t *)(this + 428);
  for ( i = 3; i != 0; --i )
  {
    v3 = *pThis_1AC;
    if ( *pThis_1AC != 0 )
    {
      if ( *(uint32_t *)(v3 + 24) >= 0x10u )
        j__free(*(void **)(v3 + 4));
      *(uint32_t *)(v3 + 24) = 15;
      *(uint32_t *)(v3 + 20) = 0;
      *(uint8_t *)(v3 + 4) = 0;
      j__free((void *)v3);
      pThis_1AC = pThis_1AC2;
    }
    *pThis_1AC++ = 0;
    pThis_1AC2 = pThis_1AC;
  }
  if ( *(uint32_t *)(this + 460) != 0 )
    j__free(*(void **)(this + 460));
  *(uint32_t *)(this + 460) = 0;
  *(uint32_t *)(this + 464) = 0;
  *(uint32_t *)(this + 468) = 0;
  if ( *(uint32_t *)(this + 444) != 0 )
    j__free(*(void **)(this + 444));
  *(uint32_t *)(this + 444) = 0;
  *(uint32_t *)(this + 448) = 0;
  *(uint32_t *)(this + 452) = 0;
  if ( *(uint32_t *)(this + 420) >= 0x10u )
    j__free(*(void **)(this + 400));
  *(uint32_t *)(this + 420) = 15;
  *(uint32_t *)(this + 416) = 0;
  *(uint8_t *)(this + 400) = 0;
  if ( *(uint32_t *)(this + 332) >= 0x10u )
    j__free(*(void **)(this + 312));
  *(uint32_t *)(this + 332) = 15;
  *(uint32_t *)(this + 328) = 0;
  *(uint8_t *)(this + 312) = 0;
  if ( *(uint32_t *)(this + 304) >= 0x10u )
    j__free(*(void **)(this + 284));
  *(uint32_t *)(this + 304) = 15;
  *(uint32_t *)(this + 300) = 0;
  *(uint8_t *)(this + 284) = 0;
  fld_10C = *(void ***)(this + 268);
  if ( fld_10C != nullptr )
  {
    for ( j = *(void ***)(this + 272); fld_10C != j; ++fld_10C )
      sub_41B010(fld_10C);
    j__free(*(void **)(this + 268));
  }
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;
  if ( *(uint32_t *)(this + 204) != 0 )
    j__free(*(void **)(this + 204));
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  if ( *(uint32_t *)(this + 188) != 0 )
    j__free(*(void **)(this + 188));
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  fld_AC = *(uint32_t **)(this + 172);
  if ( fld_AC != nullptr )
  {
    fld_B0 = *(uint32_t **)(this + 176);
    fld_B02 = fld_B0;
    if ( fld_AC != fld_B0 )
    {
      v7 = fld_AC + 6;
      do
      {
        if ( *v7 >= 0x10u )
        {
          j__free((void *)*(v7 - 5));
          fld_B0 = fld_B02;
        }
        *v7 = 15;
        *(v7 - 1) = 0;
        *((uint8_t *)v7 - 20) = 0;
        v7 += 9;
      }
      while ( v7 - 6 != fld_B0 );
    }
    j__free(*(void **)(this + 172));
  }
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  fld_90 = *(void ***)(this + 144);
  if ( fld_90 != nullptr )
  {
    for ( k = *(void ***)(this + 148); fld_90 != k; ++fld_90 )
      sub_41B010(fld_90);
    j__free(*(void **)(this + 144));
  }
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  fld_80 = *(void ***)(this + 128);
  if ( fld_80 != nullptr )
  {
    for ( m = *(void ***)(this + 132); fld_80 != m; ++fld_80 )
      sub_41B010(fld_80);
    j__free(*(void **)(this + 128));
  }
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  if ( *(uint32_t *)(this + 108) != 0 )
    j__free(*(void **)(this + 108));
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  fld_60 = *(void ***)(this + 96);
  v11 = (void **)*fld_60;
  *fld_60 = fld_60;
  *(uint32_t *)(*(uint32_t *)(this + 96) + 4) = *(uint32_t *)(this + 96);
  fld_602 = v11 == *(void ***)(this + 96);
  *(uint32_t *)(this + 100) = 0;
  if ( !fld_602 )
  {
    do
    {
      v34 = (void **)*v11;
      if ( v11[7] != nullptr )
        j__free(v11[7]);
      v11[7] = nullptr;
      v11[8] = nullptr;
      v11[9] = nullptr;
      j__free(v11);
      v11 = v34;
    }
    while ( v34 != *(void ***)(this + 96) );
  }
  j__free(*(void **)(this + 96));
  *(uint32_t *)(this + 96) = 0;
  fld_54 = *(uint32_t ***)(this + 84);
  v14 = *fld_54;
  *fld_54 = fld_54;
  *(uint32_t *)(*(uint32_t *)(this + 84) + 4) = *(uint32_t *)(this + 84);
  fld_542 = *(uint32_t **)(this + 84);
  *(uint32_t *)(this + 88) = 0;
  if ( v14 != fld_542 )
  {
    do
    {
      v16 = (void *)v14[12];
      v35 = (uint32_t *)*v14;
      if ( v16 != nullptr )
        j__free(v16);
      v14[12] = 0;
      v14[13] = 0;
      v14[14] = 0;
      j__free(v14);
      v14 = v35;
    }
    while ( v35 != *(uint32_t **)(this + 84) );
  }
  j__free(*(void **)(this + 84));
  *(uint32_t *)(this + 84) = 0;
  fld_40 = *(uint32_t *)(this + 64);
  if ( fld_40 != 0 )
  {
    fld_44 = *(uint32_t *)(this + 68);
    fld_442 = fld_44;
    fld_402 = *(uint32_t *)(this + 64);
    if ( fld_40 != fld_44 )
    {
      v19 = fld_40 + 44;
      do
      {
        if ( *(uint32_t *)v19 != 0 )
        {
          j__free(*(void **)v19);
          fld_40 = fld_402;
          fld_44 = fld_442;
        }
        fld_40 += 56;
        *(uint32_t *)v19 = 0;
        *(uint32_t *)(v19 + 4) = 0;
        *(uint32_t *)(v19 + 8) = 0;
        v19 += 56;
        fld_402 = fld_40;
      }
      while ( fld_40 != fld_44 );
    }
    j__free(*(void **)(this + 64));
  }
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  fld_34 = *(uint32_t ***)(this + 52);
  v21 = *fld_34;
  *fld_34 = fld_34;
  *(uint32_t *)(*(uint32_t *)(this + 52) + 4) = *(uint32_t *)(this + 52);
  fld_602 = v21 == *(uint32_t **)(this + 52);
  *(uint32_t *)(this + 56) = 0;
  if ( !fld_602 )
  {
    do
    {
      v22 = (uint32_t *)*v21;
      j__free(v21);
      v21 = v22;
    }
    while ( v22 != *(uint32_t **)(this + 52) );
  }
  j__free(*(void **)(this + 52));
  *(uint32_t *)(this + 52) = 0;
  fld_28 = *(void ***)(this + 40);
  v24 = (void **)*fld_28;
  *fld_28 = fld_28;
  *(uint32_t *)(*(uint32_t *)(this + 40) + 4) = *(uint32_t *)(this + 40);
  fld_282 = *(void ***)(this + 40);
  *(uint32_t *)(this + 44) = 0;
  if ( v24 != fld_282 )
  {
    do
    {
      v37 = (void **)*v24;
      if ( (unsigned int)v24[8] >= 0x10 )
        j__free(v24[3]);
      v24[8] = (void *)15;
      v24[7] = nullptr;
      *((uint8_t *)v24 + 12) = 0;
      j__free(v24);
      v24 = v37;
    }
    while ( v37 != *(void ***)(this + 40) );
  }
  j__free(*(void **)(this + 40));
  *(uint32_t *)(this + 40) = 0;
  if ( *(uint32_t *)(this + 24) != 0 )
    j__free(*(void **)(this + 24));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  fld_8 = *(uint32_t ***)(this + 8);
  v27 = *fld_8;
  *fld_8 = fld_8;
  *(uint32_t *)(*(uint32_t *)(this + 8) + 4) = *(uint32_t *)(this + 8);
  fld_602 = v27 == *(uint32_t **)(this + 8);
  *(uint32_t *)(this + 12) = 0;
  if ( !fld_602 )
  {
    do
    {
      v28 = (uint32_t *)*v27;
      j__free(v27);
      v27 = v28;
    }
    while ( v28 != *(uint32_t **)(this + 8) );
  }
  j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 8) = 0;
}


// ------------------------------------------------------------
// 0x4D1D70 sub_4D1D70
// ------------------------------------------------------------
int /*thiscall*/ sub_4D1D70(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_4D0A20((int)&v3, **(void ***)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4D1DB0 sub_4D1DB0
// ------------------------------------------------------------
void /*thiscall*/ sub_4D1DB0(int this)
{
  bool fld_84; // cf
  int v3[5]; // [esp+Ch] [ebp-14h] BYREF

  v3[1] = this;
  fld_84 = *(uint32_t *)(this + 132) < 0x10u;
  v3[4] = 2;
  if ( !fld_84 )
    j__free(*(void **)(this + 112));
  *(uint32_t *)(this + 132) = 15;
  *(uint32_t *)(this + 128) = 0;
  *(uint8_t *)(this + 112) = 0;
  sub_4D0A20((int)v3, **(void ***)(this + 100), *(uint32_t *)(this + 100));
  j__free(*(void **)(this + 100));
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
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
// 0x4D1EA0 sub_4D1EA0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D1EA0(char *this)
{
  char *pThis_4; // edi
  char *pThis_278; // eax
  char *pThis_A0; // edi
  char *pThis_38C; // edi
  char *pThis_4C0; // edi
  void **pThis_169; // edi
  void **pThis_16D; // edi
  void **pThis_17F; // edi
  void **pThis_183; // edi
  int pThis_187; // eax
  int result; // eax
  int j; // [esp+Ch] [ebp-8h]
  int k; // [esp+Ch] [ebp-8h]
  int m; // [esp+Ch] [ebp-8h]
  void **n; // [esp+Ch] [ebp-8h]
  void **ii; // [esp+Ch] [ebp-8h]
  void **jj; // [esp+Ch] [ebp-8h]
  void **kk; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]
  char *pThis_2782; // [esp+10h] [ebp-4h]

  *(uint32_t *)this = 4;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  pThis_4 = this + 4;
  for ( i = 5; i != 0; --i )
  {
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    pThis_4 += 28;
  }
  pThis_278 = this + 632;
  pThis_2782 = this + 632;
  pThis_A0 = this + 160;
  for ( j = 6; j != 0; --j )
  {
    *((uint32_t *)pThis_A0 - 2) = 0;
    *((uint32_t *)pThis_A0 - 1) = 0;
    *(uint16_t *)pThis_A0 = 0;
    *((uint16_t *)pThis_A0 + 1) = 0;
    *((uint16_t *)pThis_A0 + 2) = 0;
    *((uint16_t *)pThis_A0 + 3) = 0;
    *((uint32_t *)pThis_A0 + 2) = 0;
    *((uint32_t *)pThis_A0 + 3) = 0;
    *((uint32_t *)pThis_A0 + 4) = 0;
    *((uint32_t *)pThis_A0 + 5) = 0;
    *((uint32_t *)pThis_A0 + 6) = 0;
    *((uint32_t *)pThis_A0 + 7) = 0;
    *((uint32_t *)pThis_A0 + 8) = 0;
    *((uint32_t *)pThis_A0 + 9) = 0;
    *((uint32_t *)pThis_A0 + 10) = 0;
    *((uint32_t *)pThis_A0 + 11) = 0;
    *((uint32_t *)pThis_A0 + 12) = 0;
    *((uint16_t *)pThis_A0 + 26) = 0;
    *((uint16_t *)pThis_A0 + 27) = 0;
    *((uint16_t *)pThis_A0 + 28) = 0;
    *((uint16_t *)pThis_A0 + 29) = 0;
    *((uint16_t *)pThis_A0 + 30) = 0;
    *((uint16_t *)pThis_A0 + 31) = 0;
    *((uint16_t *)pThis_A0 + 32) = 0;
    *(uint32_t *)(pThis_A0 + 66) = 0;
    pThis_A0[70] = 0;
    if ( *(uint32_t *)pThis_278 != 0 )
    {
      j__free(*(void **)pThis_278);
      pThis_278 = pThis_2782;
    }
    *(uint32_t *)pThis_278 = 0;
    *((uint32_t *)pThis_278 + 1) = 0;
    *((uint32_t *)pThis_278 + 2) = 0;
    if ( *((uint32_t *)pThis_278 + 24) != 0 )
    {
      j__free(*((void **)pThis_278 + 24));
      pThis_278 = pThis_2782;
    }
    *((uint32_t *)pThis_278 + 24) = 0;
    *((uint32_t *)pThis_278 + 25) = 0;
    *((uint32_t *)pThis_278 + 26) = 0;
    pThis_278 += 16;
    pThis_A0 += 79;
    pThis_2782 = pThis_278;
  }
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_38C = this + 908;
  for ( k = 2; k != 0; --k )
  {
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    pThis_38C += 28;
  }
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_4C0 = this + 1216;
  for ( m = 4; m != 0; --m )
  {
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    pThis_4C0 += 28;
  }
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_169 = *((void ***)this + 361);
  if ( pThis_169 != nullptr )
  {
    for ( n = *((void ***)this + 362); pThis_169 != n; ++pThis_169 )
      sub_41B010(pThis_169);
    j__free(*((void **)this + 361));
  }
  *((uint32_t *)this + 361) = 0;
  *((uint32_t *)this + 362) = 0;
  *((uint32_t *)this + 363) = 0;
  pThis_16D = *((void ***)this + 365);
  if ( pThis_16D != nullptr )
  {
    for ( ii = *((void ***)this + 366); pThis_16D != ii; ++pThis_16D )
      sub_41B010(pThis_16D);
    j__free(*((void **)this + 365));
  }
  *((uint32_t *)this + 365) = 0;
  *((uint32_t *)this + 366) = 0;
  *((uint32_t *)this + 367) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_17F = *((void ***)this + 383);
  if ( pThis_17F != nullptr )
  {
    for ( jj = *((void ***)this + 384); pThis_17F != jj; ++pThis_17F )
      sub_41B010(pThis_17F);
    j__free(*((void **)this + 383));
  }
  *((uint32_t *)this + 383) = 0;
  *((uint32_t *)this + 384) = 0;
  *((uint32_t *)this + 385) = 0;
  pThis_183 = *((void ***)this + 387);
  if ( pThis_183 != nullptr )
  {
    for ( kk = *((void ***)this + 388); pThis_183 != kk; ++pThis_183 )
      sub_41B010(pThis_183);
    j__free(*((void **)this + 387));
  }
  *((uint32_t *)this + 387) = 0;
  *((uint32_t *)this + 388) = 0;
  *((uint32_t *)this + 389) = 0;
  pThis_187 = *((uint32_t *)this + 391);
  if ( pThis_187 != 0 )
  {
    sub_4B4950(pThis_187, *((uint32_t *)this + 392));
    j__free(*((void **)this + 391));
  }
  *((uint32_t *)this + 391) = 0;
  *((uint32_t *)this + 392) = 0;
  *((uint32_t *)this + 393) = 0;
  if ( *((uint32_t *)this + 395) != 0 )
    j__free(*((void **)this + 395));
  *((uint32_t *)this + 395) = 0;
  *((uint32_t *)this + 396) = 0;
  *((uint32_t *)this + 397) = 0;
  if ( *((uint32_t *)this + 399) != 0 )
    j__free(*((void **)this + 399));
  *((uint32_t *)this + 399) = 0;
  *((uint32_t *)this + 400) = 0;
  *((uint32_t *)this + 401) = 0;
  if ( *((uint32_t *)this + 403) != 0 )
    j__free(*((void **)this + 403));
  *((uint32_t *)this + 403) = 0;
  *((uint32_t *)this + 404) = 0;
  *((uint32_t *)this + 405) = 0;
  if ( *((uint32_t *)this + 407) != 0 )
    j__free(*((void **)this + 407));
  *((uint32_t *)this + 407) = 0;
  *((uint32_t *)this + 408) = 0;
  *((uint32_t *)this + 409) = 0;
  result = sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 205) = 100;
  return result;
}


// ------------------------------------------------------------
// 0x4D2320 sub_4D2320
// ------------------------------------------------------------
int /*thiscall*/ sub_4D2320(int this)
{
  int pThis_98; // eax
  int i; // ecx

  `eh vector constructor iterator'((void *)(this + 4), 0x1Cu, 5, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);
  v2 = this + 152;
  for ( i = 6; i != 0; --i )
  {
    *(uint32_t *)v2 = 0;
    *(uint32_t *)(v2 + 4) = 0;
    *(uint16_t *)(v2 + 8) = 0;
    *(uint16_t *)(v2 + 10) = 0;
    *(uint16_t *)(v2 + 12) = 0;
    *(uint16_t *)(v2 + 14) = 0;
    *(uint32_t *)(v2 + 16) = 0;
    *(uint32_t *)(v2 + 20) = 0;
    *(uint32_t *)(v2 + 24) = 0;
    *(uint32_t *)(v2 + 28) = 0;
    *(uint32_t *)(v2 + 32) = 0;
    *(uint32_t *)(v2 + 36) = 0;
    *(uint32_t *)(v2 + 40) = 0;
    *(uint32_t *)(v2 + 44) = 0;
    *(uint32_t *)(v2 + 48) = 0;
    *(uint32_t *)(v2 + 52) = 0;
    *(uint32_t *)(v2 + 56) = 0;
    *(uint16_t *)(v2 + 60) = 0;
    *(uint16_t *)(v2 + 62) = 0;
    *(uint16_t *)(v2 + 64) = 0;
    *(uint16_t *)(v2 + 66) = 0;
    *(uint16_t *)(v2 + 68) = 0;
    *(uint16_t *)(v2 + 70) = 0;
    *(uint16_t *)(v2 + 72) = 0;
    *(uint32_t *)(v2 + 74) = 0;
    *(uint8_t *)(v2 + 78) = 0;
    v2 += 79;
  }
  `eh vector constructor iterator'(
    (void *)(this + 628),
    0x10u,
    6,
    (void (/*thiscall*/ *)(void *))sub_4019A0,
    (void (/*thiscall*/ *)(void *))sub_5E5260);
  `eh vector constructor iterator'(
    (void *)(this + 724),
    0x10u,
    6,
    (void (/*thiscall*/ *)(void *))sub_4019A0,
    (void (/*thiscall*/ *)(void *))sub_5E5260);
  *(uint32_t *)(this + 848) = 15;
  *(uint32_t *)(this + 844) = 0;
  *(uint8_t *)(this + 828) = 0;
  *(uint32_t *)(this + 876) = 15;
  *(uint32_t *)(this + 872) = 0;
  *(uint8_t *)(this + 856) = 0;
  *(uint32_t *)(this + 904) = 15;
  *(uint32_t *)(this + 900) = 0;
  *(uint8_t *)(this + 884) = 0;
  `eh vector constructor iterator'((void *)(this + 908), 0x1Cu, 2, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);
  *(uint32_t *)(this + 988) = 15;
  *(uint32_t *)(this + 984) = 0;
  *(uint8_t *)(this + 968) = 0;
  *(uint32_t *)(this + 1016) = 15;
  *(uint32_t *)(this + 1012) = 0;
  *(uint8_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1044) = 15;
  *(uint32_t *)(this + 1040) = 0;
  *(uint8_t *)(this + 1024) = 0;
  *(uint32_t *)(this + 1072) = 15;
  *(uint32_t *)(this + 1068) = 0;
  *(uint8_t *)(this + 1052) = 0;
  *(uint32_t *)(this + 1100) = 15;
  *(uint32_t *)(this + 1096) = 0;
  *(uint8_t *)(this + 1080) = 0;
  `eh vector constructor iterator'((void *)(this + 1104), 0x1Cu, 4, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);
  `eh vector constructor iterator'((void *)(this + 1216), 0x1Cu, 4, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);
  *(uint32_t *)(this + 1352) = 15;
  *(uint32_t *)(this + 1348) = 0;
  *(uint8_t *)(this + 1332) = 0;
  *(uint32_t *)(this + 1380) = 15;
  *(uint32_t *)(this + 1376) = 0;
  *(uint8_t *)(this + 1360) = 0;
  *(uint32_t *)(this + 1408) = 15;
  *(uint32_t *)(this + 1404) = 0;
  *(uint8_t *)(this + 1388) = 0;
  *(uint32_t *)(this + 1436) = 15;
  *(uint32_t *)(this + 1432) = 0;
  *(uint8_t *)(this + 1416) = 0;
  *(uint32_t *)(this + 1444) = 0;
  *(uint32_t *)(this + 1448) = 0;
  *(uint32_t *)(this + 1452) = 0;
  *(uint32_t *)(this + 1460) = 0;
  *(uint32_t *)(this + 1464) = 0;
  *(uint32_t *)(this + 1468) = 0;
  *(uint32_t *)(this + 1496) = 15;
  *(uint32_t *)(this + 1492) = 0;
  *(uint8_t *)(this + 1476) = 0;
  *(uint32_t *)(this + 1524) = 15;
  *(uint32_t *)(this + 1520) = 0;
  *(uint8_t *)(this + 1504) = 0;
  *(uint32_t *)(this + 1532) = 0;
  *(uint32_t *)(this + 1536) = 0;
  *(uint32_t *)(this + 1540) = 0;
  *(uint32_t *)(this + 1548) = 0;
  *(uint32_t *)(this + 1552) = 0;
  *(uint32_t *)(this + 1556) = 0;
  *(uint32_t *)(this + 1564) = 0;
  *(uint32_t *)(this + 1568) = 0;
  *(uint32_t *)(this + 1572) = 0;
  *(uint32_t *)(this + 1580) = 0;
  *(uint32_t *)(this + 1584) = 0;
  *(uint32_t *)(this + 1588) = 0;
  *(uint32_t *)(this + 1596) = 0;
  *(uint32_t *)(this + 1600) = 0;
  *(uint32_t *)(this + 1604) = 0;
  *(uint32_t *)(this + 1612) = 0;
  *(uint32_t *)(this + 1616) = 0;
  *(uint32_t *)(this + 1620) = 0;
  *(uint32_t *)(this + 1628) = 0;
  *(uint32_t *)(this + 1632) = 0;
  *(uint32_t *)(this + 1636) = 0;
  *(uint32_t *)(this + 1664) = 15;
  *(uint32_t *)(this + 1660) = 0;
  *(uint8_t *)(this + 1644) = 0;
  sub_4D1EA0((char *)this);
  return this;
}


// ------------------------------------------------------------
// 0x4D2640 sub_4D2640
// ------------------------------------------------------------
int /*thiscall*/ sub_4D2640(int this)
{
  int pThis_60; // edi
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
  pThis_60 = this + 96;
  v3 = sub_4CE790();
  *(uint32_t *)(pThis_60 + 4) = v3;
  *((uint8_t *)v3 + 69) = 1;
  *(uint32_t *)(*(uint32_t *)(pThis_60 + 4) + 4) = *(uint32_t *)(pThis_60 + 4);
  **(uint32_t **)(pThis_60 + 4) = *(uint32_t *)(pThis_60 + 4);
  *(uint32_t *)(*(uint32_t *)(pThis_60 + 4) + 8) = *(uint32_t *)(pThis_60 + 4);
  *(uint32_t *)(pThis_60 + 8) = 0;
  *(uint32_t *)(this + 132) = 15;
  *(uint32_t *)(this + 128) = 0;
  *(uint8_t *)(this + 112) = 0;
  sub_4D1020(this);
  return this;
}



// ------------------------------------------------------------
// 0x4D26E0 sub_4D26E0
// ------------------------------------------------------------
void /*thiscall*/ sub_4D26E0(int this)
{
  int fld_61C; // eax

  if ( *(uint32_t *)(this + 1664) >= 0x10u )
    j__free(*(void **)(this + 1644));
  *(uint32_t *)(this + 1664) = 15;
  *(uint32_t *)(this + 1660) = 0;
  *(uint8_t *)(this + 1644) = 0;
  if ( *(uint32_t *)(this + 1628) != 0 )
    j__free(*(void **)(this + 1628));
  *(uint32_t *)(this + 1628) = 0;
  *(uint32_t *)(this + 1632) = 0;
  *(uint32_t *)(this + 1636) = 0;
  if ( *(uint32_t *)(this + 1612) != 0 )
    j__free(*(void **)(this + 1612));
  *(uint32_t *)(this + 1612) = 0;
  *(uint32_t *)(this + 1616) = 0;
  *(uint32_t *)(this + 1620) = 0;
  if ( *(uint32_t *)(this + 1596) != 0 )
    j__free(*(void **)(this + 1596));
  *(uint32_t *)(this + 1596) = 0;
  *(uint32_t *)(this + 1600) = 0;
  *(uint32_t *)(this + 1604) = 0;
  if ( *(uint32_t *)(this + 1580) != 0 )
    j__free(*(void **)(this + 1580));
  *(uint32_t *)(this + 1580) = 0;
  *(uint32_t *)(this + 1584) = 0;
  *(uint32_t *)(this + 1588) = 0;
  fld_61C = *(uint32_t *)(this + 1564);
  if ( fld_61C != 0 )
  {
    sub_4B4950(fld_61C, *(uint32_t *)(this + 1568));
    j__free(*(void **)(this + 1564));
  }
  *(uint32_t *)(this + 1564) = 0;
  *(uint32_t *)(this + 1568) = 0;
  *(uint32_t *)(this + 1572) = 0;
  sub_4017E0(this + 1544);
  sub_4017E0(this + 1528);
  if ( *(uint32_t *)(this + 1524) >= 0x10u )
    j__free(*(void **)(this + 1504));
  *(uint32_t *)(this + 1524) = 15;
  *(uint32_t *)(this + 1520) = 0;
  *(uint8_t *)(this + 1504) = 0;
  if ( *(uint32_t *)(this + 1496) >= 0x10u )
    j__free(*(void **)(this + 1476));
  *(uint32_t *)(this + 1496) = 15;
  *(uint32_t *)(this + 1492) = 0;
  *(uint8_t *)(this + 1476) = 0;
  sub_4017E0(this + 1456);
  sub_4017E0(this + 1440);
  if ( *(uint32_t *)(this + 1436) >= 0x10u )
    j__free(*(void **)(this + 1416));
  *(uint32_t *)(this + 1436) = 15;
  *(uint32_t *)(this + 1432) = 0;
  *(uint8_t *)(this + 1416) = 0;
  if ( *(uint32_t *)(this + 1408) >= 0x10u )
    j__free(*(void **)(this + 1388));
  *(uint32_t *)(this + 1408) = 15;
  *(uint32_t *)(this + 1404) = 0;
  *(uint8_t *)(this + 1388) = 0;
  if ( *(uint32_t *)(this + 1380) >= 0x10u )
    j__free(*(void **)(this + 1360));
  *(uint32_t *)(this + 1380) = 15;
  *(uint32_t *)(this + 1376) = 0;
  *(uint8_t *)(this + 1360) = 0;
  if ( *(uint32_t *)(this + 1352) >= 0x10u )
    j__free(*(void **)(this + 1332));
  *(uint32_t *)(this + 1352) = 15;
  *(uint32_t *)(this + 1348) = 0;
  *(uint8_t *)(this + 1332) = 0;
  `eh vector destructor iterator'((void *)(this + 1216), 0x1Cu, 4, sub_501490);
  `eh vector destructor iterator'((void *)(this + 1104), 0x1Cu, 4, sub_501490);
  if ( *(uint32_t *)(this + 1100) >= 0x10u )
    j__free(*(void **)(this + 1080));
  *(uint32_t *)(this + 1100) = 15;
  *(uint32_t *)(this + 1096) = 0;
  *(uint8_t *)(this + 1080) = 0;
  if ( *(uint32_t *)(this + 1072) >= 0x10u )
    j__free(*(void **)(this + 1052));
  *(uint32_t *)(this + 1072) = 15;
  *(uint32_t *)(this + 1068) = 0;
  *(uint8_t *)(this + 1052) = 0;
  if ( *(uint32_t *)(this + 1044) >= 0x10u )
    j__free(*(void **)(this + 1024));
  *(uint32_t *)(this + 1044) = 15;
  *(uint32_t *)(this + 1040) = 0;
  *(uint8_t *)(this + 1024) = 0;
  if ( *(uint32_t *)(this + 1016) >= 0x10u )
    j__free(*(void **)(this + 996));
  *(uint32_t *)(this + 1016) = 15;
  *(uint32_t *)(this + 1012) = 0;
  *(uint8_t *)(this + 996) = 0;
  if ( *(uint32_t *)(this + 988) >= 0x10u )
    j__free(*(void **)(this + 968));
  *(uint32_t *)(this + 988) = 15;
  *(uint32_t *)(this + 984) = 0;
  *(uint8_t *)(this + 968) = 0;
  `eh vector destructor iterator'((void *)(this + 908), 0x1Cu, 2, sub_501490);
  if ( *(uint32_t *)(this + 904) >= 0x10u )
    j__free(*(void **)(this + 884));
  *(uint32_t *)(this + 904) = 15;
  *(uint32_t *)(this + 900) = 0;
  *(uint8_t *)(this + 884) = 0;
  if ( *(uint32_t *)(this + 876) >= 0x10u )
    j__free(*(void **)(this + 856));
  *(uint32_t *)(this + 876) = 15;
  *(uint32_t *)(this + 872) = 0;
  *(uint8_t *)(this + 856) = 0;
  if ( *(uint32_t *)(this + 848) >= 0x10u )
    j__free(*(void **)(this + 828));
  *(uint32_t *)(this + 848) = 15;
  *(uint32_t *)(this + 844) = 0;
  *(uint8_t *)(this + 828) = 0;
  `eh vector destructor iterator'((void *)(this + 724), 0x10u, 6, (void (/*thiscall*/ *)(void *))sub_5E5260);
  `eh vector destructor iterator'((void *)(this + 628), 0x10u, 6, (void (/*thiscall*/ *)(void *))sub_5E5260);
  `eh vector destructor iterator'((void *)(this + 4), 0x1Cu, 5, sub_501490);
}


// ------------------------------------------------------------
// 0x4D2B30 sub_4D2B30
// ------------------------------------------------------------
// 对象工厂析构分派：按 this+288(运行期 case id) 分发到对应类的析构器 + free。
// 与 0x4D2D60（构造侧）成对；case 表 = 14 类对象（0x4D26E0/0x4CF5C0/...）。
// 依据：研究 18/19 —— 对象工厂 case 1 = 0x5A0 角色/怪物数据对象。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D2B30(uint32_t *this, void *Block)
{
  switch ( *(this + 72) )
  {
    case 0:
      if ( Block != nullptr )
      {
        sub_4D26E0(Block);
        j__free(Block);
      }
      break;
    case 1:
      if ( Block != nullptr )
      {
        sub_4CF5C0(Block);
        j__free(Block);
      }
      break;
    case 2:
      if ( Block != nullptr )
      {
        sub_4CF8F0(Block);
        j__free(Block);
      }
      break;
    case 3:
      if ( Block != nullptr )
      {
        sub_4CFA50(Block);
        j__free(Block);
      }
      break;
    case 4:
      if ( Block != nullptr )
      {
        sub_439810(Block);
        j__free(Block);
      }
      break;
    case 5:
      if ( Block != nullptr )
      {
        sub_4CFB40(Block);
        j__free(Block);
      }
      break;
    case 6:
      if ( Block != nullptr )
      {
        sub_4D10A0(Block);
        j__free(Block);
      }
      break;
    case 7:
      if ( Block != nullptr )
      {
        sub_4D1860(Block);
        j__free(Block);
      }
      break;
    case 8:
      if ( Block != nullptr )
      {
        sub_4A2EB0(Block);
        j__free(Block);
      }
      break;
    case 9:
      if ( Block != nullptr )
      {
        sub_4D1100(Block);
        j__free(Block);
      }
      break;
    case 0xA:
      if ( Block != nullptr )
      {
        sub_4CE850(Block);
        j__free(Block);
      }
      break;
    case 0xB:
      if ( Block != nullptr )
      {
        sub_4D1140((int)Block);
        j__free(Block);
      }
      break;
    case 0xC:
      if ( Block != nullptr )
      {
        sub_4D1DB0(Block);
        j__free(Block);
      }
      break;
    case 0xD:
      if ( Block != nullptr )
      {
        sub_4CFC20(Block);
        j__free(Block);
      }
      break;
    case 0xE:
      if ( Block != nullptr )
      {
        sub_4CFC80(Block);
        j__free(Block);
      }
      break;
    default:
      return;
  }
}


// 0x4D2D60 sub_4D2D60
// ------------------------------------------------------------
// ★ 对象工厂构造分派（研究 18/19 定案的 sub_4D2D60）
//   this+288 = case id；每个 case = 固定尺寸 new + 构造器 + 专用解析器：
//     case 0 0x684 → sub_4D2320 + sub_50C290（最大：状态/观察者全槽）
//     case 1 0x5A0 → sub_4D01E0 + sub_509C90（★ 角色/怪物数据对象：
//                   [attack speed] +380/384、[hit recovery] +396/400、
//                   [jump power] +404、[stuckbonus on damage] +428..440 四档）
//     case 2 0xF8 / case 3 0xC8 / case 4 0x85C / case 5 0xA4 / case 6 0x34 /
//     case 7 0x1D8 / ... 其余怪物/装备数据类
//   解析器 = 属性块通用解析器 sub_509C90（[hit recovery] 双解析器之一，研究 §3/§12）。
//   与 0x4D2B30（析构分派）成对。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D2D60(uint32_t *this, const char *ArgList, int nArg3)
{
  void *pMem; // eax
  int v4; // esi
  void *pMem2; // eax
  void *pMem3; // eax
  void *pMem4; // eax
  void *pMem5; // eax
  void *pMem6; // eax
  void *pMem7; // eax
  void *pMem8; // eax
  void *pMem9; // eax
  void *pMem10; // eax
  void *pMem11; // eax
  void *pMem12; // eax
  void *pMem13; // eax
  void *pMem14; // eax
  void *pMem15; // eax

  switch ( *(this + 72) )
  {
    case 0:
      pMem = operator new(0x684u);
      if ( pMem != nullptr )
        v4 = sub_4D2320(pMem);
      else
        v4 = 0;
      if ( (uint8_t)sub_50C290(v4, ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      sub_4D26E0(v4);
      goto LABEL_101;
    case 1:
      pMem2 = operator new(0x5A0u);
      if ( pMem2 != nullptr )
        v4 = sub_4D01E0(pMem2);
      else
        v4 = 0;
      if ( sub_509C90(v4, (int)ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      sub_4CF5C0(v4);
      goto LABEL_101;
    case 2:
      pMem3 = operator new(0xF8u);
      if ( pMem3 != nullptr )
        v4 = sub_4D03E0(pMem3);
      else
        v4 = 0;
      if ( (uint8_t)sub_50AF40(v4, ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      sub_4CF8F0(v4);
      goto LABEL_101;
    case 3:
      pMem4 = operator new(0xC8u);
      if ( pMem4 != nullptr )
        v4 = sub_4D04C0(pMem4);
      else
        v4 = 0;
      if ( (uint8_t)sub_50B400(v4, ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      sub_4CFA50(v4);
      goto LABEL_101;
    case 4:
      pMem5 = operator new(0x85Cu);
      if ( pMem5 != nullptr )
        v4 = sub_439680(pMem5);
      else
        v4 = 0;
      if ( (uint8_t)sub_4F7C60(v4, (char)ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      sub_439810(v4);
      goto LABEL_101;
    case 5:
      pMem6 = operator new(0xA4u);
      if ( pMem6 != nullptr )
        v4 = sub_4D0680(pMem6);
      else
        v4 = 0;
      if ( (uint8_t)sub_4F5B90(v4, (char)ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      sub_4CFB40(v4);
      goto LABEL_101;
    case 6:
      pMem7 = operator new(0x34u);
      if ( pMem7 != nullptr )
        v4 = sub_4D0B30(pMem7);
      else
        v4 = 0;
      if ( (uint8_t)sub_507690(v4, (char)ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      sub_4D10A0(v4);
      goto LABEL_101;
    case 7:
      pMem8 = operator new(0x1D8u);
      if ( pMem8 != nullptr )
        v4 = sub_4D1680(pMem8);
      else
        v4 = 0;
      if ( (uint8_t)sub_5078C0(v4, (char)ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      sub_4D1860(v4);
      goto LABEL_101;
    case 8:
      pMem9 = operator new(0x98u);
      if ( pMem9 != nullptr )
        v4 = sub_4A3520(pMem9);
      else
        v4 = 0;
      if ( sub_503BA0(v4, ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      if ( *(uint32_t *)(v4 + 116) >= 0x10u )
        j__free(*(void **)(v4 + 96));
      *(uint32_t *)(v4 + 116) = 15;
      *(uint32_t *)(v4 + 112) = 0;
      *(uint8_t *)(v4 + 96) = 0;
      goto LABEL_101;
    case 9:
      pMem10 = operator new(0xE0u);
      if ( pMem10 != nullptr )
        v4 = sub_4D0C30(pMem10);
      else
        v4 = 0;
      if ( (uint8_t)sub_500B30(v4, ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      if ( *(uint32_t *)(v4 + 220) >= 0x10u )
        j__free(*(void **)(v4 + 200));
      *(uint32_t *)(v4 + 220) = 15;
      *(uint32_t *)(v4 + 216) = 0;
      *(uint8_t *)(v4 + 200) = 0;
      sub_428480(v4 + 180);
      goto LABEL_101;
    case 0xA:
      pMem11 = operator new(0x3Cu);
      if ( pMem11 != nullptr )
        v4 = sub_4D07A0(pMem11);
      else
        v4 = 0;
      if ( (uint8_t)sub_500330(v4, (char)ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      if ( *(uint32_t *)(v4 + 48) != 0 )
        j__free(*(void **)(v4 + 48));
      *(uint32_t *)(v4 + 48) = 0;
      *(uint32_t *)(v4 + 52) = 0;
      *(uint32_t *)(v4 + 56) = 0;
      if ( *(uint32_t *)(v4 + 40) >= 0x10u )
        j__free(*(void **)(v4 + 20));
      *(uint32_t *)(v4 + 40) = 15;
      *(uint32_t *)(v4 + 36) = 0;
      *(uint8_t *)(v4 + 20) = 0;
      goto LABEL_101;
    case 0xB:
      pMem12 = operator new(0x144u);
      if ( pMem12 != nullptr )
        v4 = sub_4D0F00((int)pMem12);
      else
        v4 = 0;
      if ( (uint8_t)sub_4FF870(v4, (char)ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      sub_4D1140(v4);
      goto LABEL_101;
    case 0xC:
      pMem13 = operator new(0x88u);
      if ( pMem13 != nullptr )
        v4 = sub_4D2640(pMem13);
      else
        v4 = 0;
      if ( (uint8_t)sub_4FD040(v4, (char)ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      sub_4D1DB0(v4);
      goto LABEL_101;
    case 0xD:
      pMem14 = operator new(0x50u);
      if ( pMem14 != nullptr )
        v4 = sub_4D0830(pMem14);
      else
        v4 = 0;
      if ( (uint8_t)sub_4FD4C0(v4, (char)ArgList) != 0 )
        return v4;
      if ( v4 == 0 )
        return 0;
      sub_4CFC20(v4);
      goto LABEL_101;
    case 0xE:
      pMem15 = operator new(0x168u);
      if ( pMem15 != nullptr )
        v4 = sub_4D0570(pMem15);
      else
        v4 = 0;
      if ( (uint8_t)sub_50B840(v4, ArgList) != 0 )
        return v4;
      if ( v4 != 0 )
      {
        sub_4CFC80(v4);
LABEL_101:
        j__free((void *)v4);
      }
      return 0;
    default:
      return 0;
  }
}


// 0x4D33A0 sub_4D33A0
// ------------------------------------------------------------
// 线性同余伪随机数发生器（LCG）。三条 1103515245×x+12345 递推，取每拍高 10 bit
// 拼接为 30 bit 结果。研究 20 §5.1 的"hash%10000 < 率×100"消费点之一（伤害流水线
// 方差/暴击掷）；亦被 sub_4DB130（srand(坐标和+序列)）调用的随机池。
// ------------------------------------------------------------
int /*cdecl*/ sub_4D33A0(unsigned int *pDwArg1)
{
  unsigned int v1; // edx
  unsigned int v2; // ecx
  unsigned int v3; // eax

  v1 = 1103515245 * *pDwArg1 + 12345;
  v2 = 1103515245 * v1 + 12345;
  v3 = 1103515245 * v2 + 12345;
  *pDwArg1 = v3;
  return ((((HIWORD(v1) & 0x7FF) << 10) ^ HIWORD(v2) & 0x3FF) << 10) ^ HIWORD(v3) & 0x3FF;
}



// ------------------------------------------------------------
// 0x4D3400 sub_4D3400
// ------------------------------------------------------------
signed int /*cdecl*/ sub_4D3400(uint8_t *uArg1, const char *pArg2)
{
  signed int v2; // edx
  int v3; // ebx
  char v4; // al
  signed int result; // eax
  char v6; // cl

  v2 = 0;
  v3 = 0;
  if ( (int)strlen(pArg2) <= 0 )
  {
    *uArg1 = 0;
    return (signed int)uArg1;
  }
  else
  {
    do
    {
      v4 = pArg2[v2];
      if ( v4 < 9 || v4 > 10 && v4 != 32 )
        uArg1[v3++] = v4;
      ++v2;
      result = strlen(pArg2);
    }
    while ( v2 < result );
    uArg1[v3] = v6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D3470 sub_4D3470
// ------------------------------------------------------------
char */*cdecl*/ sub_4D3470(void *pArg1, void *pArg2, unsigned int uArg3)
{
  char *result; // eax
  char v4; // cl

  if ( strlen((const char *)pArg2) > uArg3 )
  {
    qmemcpy(pArg1, pArg2, uArg3);
    *((uint8_t *)pArg1 + uArg3) = 0;
    return (char *)pArg1;
  }
  else
  {
    result = (char *)pArg2;
    do
    {
      v4 = *result;
      result[(uint8_t *)pArg1 - (uint8_t *)pArg2] = *result;
      ++result;
    }
    while ( v4 != 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D34D0 sub_4D34D0
// ------------------------------------------------------------
const char */*cdecl*/ sub_4D34D0(const char *pArg1, const char *pArg2)
{
  const char *psz; // esi
  void *pMem; // edi
  char *v5; // ebx
  char v6; // al
  unsigned int v7; // eax
  unsigned int v8; // [esp+Ch] [ebp-4h]

  psz = pArg2;
  if ( strlen(pArg1) < strlen(pArg2) )
    return nullptr;
  v8 = 0;
  if ( strlen(pArg1) - strlen(pArg2) == -1 )
    return nullptr;
  while ( 1 )
  {
    pMem = malloc(strlen(psz) + 1);
    v5 = (char *)&pArg1[v8];
    sub_4D3470(pMem, (void *)&pArg1[v8], strlen(psz));
    if ( strcmp((const char *)pMem, pArg2) == 0 )
      break;
    free(pMem);
    v6 = *v5;
    if ( *v5 < 0
      && (v6 == -127
       || v6 == -126
       || v6 == -125
       || v6 == -124
       || v6 == -121
       || v6 == -120
       || v6 == -119
       || v6 == -118
       || v6 == -117
       || v6 == -116
       || v6 == -115
       || v6 == -114
       || v6 == -113
       || v6 == -112
       || v6 == -111
       || v6 == -110
       || v6 == -109
       || v6 == -108
       || v6 == -107
       || v6 == -106
       || v6 == -105
       || v6 == -104
       || v6 == -103
       || v6 == -102
       || v6 == -101
       || v6 == -100
       || v6 == -99
       || v6 == -98
       || v6 == -97
       || v6 == -32
       || v6 == -31
       || v6 == -30
       || v6 == -29
       || v6 == -28
       || v6 == -27
       || v6 == -26
       || v6 == -25
       || v6 == -24
       || v6 == -23
       || v6 == -22
       || v6 == -19
       || v6 == -18
       || v6 == -6
       || v6 == -5
       || v6 == -4) )
    {
      v7 = v8 + 2;
    }
    else
    {
      v7 = v8 + 1;
    }
    v8 = v7;
    if ( v7 >= strlen(pArg1) - strlen(pArg2) + 1 )
      return nullptr;
    psz = pArg2;
  }
  free(pMem);
  return &pArg1[v8];
}



// ------------------------------------------------------------
// 0x4D3710 sub_4D3710
// ------------------------------------------------------------
int /*thiscall*/ sub_4D3710(uint32_t *this)
{
  *(this + 8) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4D3720 sub_4D3720
// ------------------------------------------------------------
int /*thiscall*/ sub_4D3720(uint32_t *this, char *FileName)
{
  FILE *pFile; // eax
  FILE *pFile2; // ebx
  int v5; // esi
  int v7; // esi
  char *pFound; // eax
  char Buffer[1024]; // [esp+Ch] [ebp-404h] BYREF
  int dword_796E502; // [esp+40Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  pFile = fopen(FileName, "r");
  pFile2 = pFile;
  v5 = 0;
  if ( pFile == nullptr )
    return 0;
  *(this + 8) = 0;
  if ( fgets(Buffer, 1023, pFile) != nullptr )
  {
    do
    {
      sub_4D3400(Buffer, Buffer);
      if ( Buffer[0] != 35 && strlen(Buffer) != 0 )
        ++*(this + 8);
    }
    while ( fgets(Buffer, 1023, pFile2) != nullptr );
  }
  *(this + 6) = operator new(4 * *(this + 8));
  *(this + 7) = operator new(4 * *(this + 8));
  if ( (int)*(this + 8) > 0 )
  {
    do
    {
      *(uint32_t *)(*(this + 6) + 4 * v5) = operator new(0x20u);
      *(uint32_t *)(*(this + 7) + 4 * v5++) = operator new(0x20u);
    }
    while ( v5 < *(this + 8) );
  }
  fseek(pFile2, 0, 0);
  if ( fgets(Buffer, 1023, pFile2) != nullptr )
  {
    v7 = 0;
    do
    {
      sub_4D3400(Buffer, Buffer);
      if ( Buffer[0] != 35 && strlen(Buffer) != 0 )
      {
        if ( strstr(Buffer, ":") != nullptr )
        {
          pFound = strstr(Buffer, ":");
          sub_4D3470(*(void **)(*(this + 6) + v7), Buffer, pFound - Buffer);
          strcpy(*(char **)(v7 + *(this + 7)), strstr(Buffer, ":") + 1);
        }
        else
        {
          strcpy(*(char **)(v7 + *(this + 6)), Buffer);
          **(uint8_t **)(v7 + *(this + 7)) = 0;
        }
        v7 += 4;
      }
    }
    while ( fgets(Buffer, 1023, pFile2) != nullptr );
  }
  fclose(pFile2);
  return 1;
}



// ------------------------------------------------------------
// 0x4D3950 sub_4D3950
// ------------------------------------------------------------
int /*thiscall*/ sub_4D3950(int this)
{
  int fld_20; // eax
  int v4; // edi
  int fld_1C; // edx
  void *fld_1C2; // eax

  if ( *(uint8_t *)(this + 4) == 0 )
    return 0;
  fld_20 = *(uint32_t *)(this + 32);
  v4 = 0;
  *(uint8_t *)(this + 4) = 0;
  if ( fld_20 > 0 )
  {
    do
    {
      if ( *(uint32_t *)(*(uint32_t *)(this + 24) + 4 * v4) != 0 )
        j__free(*(void **)(*(uint32_t *)(this + 24) + 4 * v4));
      *(uint32_t *)(*(uint32_t *)(this + 24) + 4 * v4) = 0;
      fld_1C = *(uint32_t *)(this + 28);
      if ( *(uint32_t *)(fld_1C + 4 * v4) != 0 )
        j__free(*(void **)(fld_1C + 4 * v4));
      *(uint32_t *)(*(uint32_t *)(this + 28) + 4 * v4++) = 0;
    }
    while ( v4 < *(uint32_t *)(this + 32) );
  }
  if ( *(uint32_t *)(this + 24) != 0 )
    j_j__free(*(void **)(this + 24));
  fld_1C2 = *(void **)(this + 28);
  *(uint32_t *)(this + 24) = 0;
  if ( fld_1C2 != nullptr )
    j_j__free(fld_1C2);
  *(uint32_t *)(this + 28) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x4D39F0 sub_4D39F0
// ------------------------------------------------------------
const char */*thiscall*/ sub_4D39F0(int this, uint32_t *uArg2, const char *pArg3)
{
  uint8_t *pMem; // esi
  int v6; // ebx
  const char *fld_18; // eax
  int v8; // ecx
  int v9; // edx
  int i; // esi
  char v11; // al
  const char *fld_182; // edi
  const char *v13; // esi
  char v14; // al
  int v15; // [esp+8h] [ebp-18h]
  void *Block; // [esp+10h] [ebp-10h]
  int v18; // [esp+14h] [ebp-Ch]
  int v19; // [esp+18h] [ebp-8h]
  unsigned int v20; // [esp+1Ch] [ebp-4h]

  if ( *(uint8_t *)(this + 4) == 0 )
    return nullptr;
  pMem = malloc(strlen(pArg3) + 1);
  Block = pMem;
  sub_4D3400(pMem, pArg3);
  v6 = 0;
  if ( *(int *)(this + 32) <= 0 )
  {
LABEL_6:
    free(pMem);
    return nullptr;
  }
  else
  {
    while ( sub_4D34D0(pMem, *(const char **)(*(uint32_t *)(this + 24) + 4 * v6)) == nullptr )
    {
      if ( ++v6 >= *(uint32_t *)(this + 32) )
        goto LABEL_6;
    }
    fld_18 = sub_4D34D0(pMem, *(const char **)(*(uint32_t *)(this + 24) + 4 * v6));
    v8 = 0;
    v9 = fld_18 - pMem;
    v15 = fld_18 - pMem;
    v18 = 0;
    v19 = 0;
    for ( i = 0; ; ++i )
    {
      while ( 1 )
      {
        v11 = pArg3[i];
        if ( v11 != 32 && v11 != 9 && v11 != 10 )
          break;
        ++v18;
        ++i;
      }
      if ( v8 >= v9 )
        break;
      ++v8;
    }
    fld_182 = *(const char **)(*(uint32_t *)(this + 24) + 4 * v6);
    v20 = 0;
    if ( strlen(fld_182) != 0 )
    {
      v13 = &pArg3[i];
      do
      {
        v14 = *v13;
        if ( *v13 == 32 || v14 == 9 || v14 == 10 )
          ++v19;
        else
          ++v20;
        ++v13;
      }
      while ( v20 < strlen(fld_182) );
    }
    free(Block);
    if ( uArg2 != nullptr )
      *uArg2 = v19 + strlen(*(const char **)(*(uint32_t *)(this + 24) + 4 * v6));
    return &pArg3[v18 + v15];
  }
}



// ------------------------------------------------------------
// 0x4D3B50 sub_4D3B50
// ------------------------------------------------------------
void /*thiscall*/ sub_4D3B50(int this, uint8_t *uArg2, const char *pArg3, unsigned int uArg4)
{
  uint8_t *pMem; // edi
  int v6; // edx
  const char **fld_18; // ebx
  int fld_20; // [esp+8h] [ebp-4h]
  const char **fld_182; // [esp+18h] [ebp+Ch]

  if ( *(uint8_t *)(this + 4) != 0 )
  {
    pMem = malloc(strlen(pArg3) + 1);
    sub_4D3400(pMem, pArg3);
    v6 = 0;
    fld_20 = *(uint32_t *)(this + 32);
    if ( fld_20 <= 0 )
    {
LABEL_6:
      *uArg2 = 0;
      free(pMem);
    }
    else
    {
      fld_18 = *(const char ***)(this + 24);
      fld_182 = fld_18;
      while ( strcmp(pMem, *fld_18) != 0 )
      {
        ++v6;
        fld_18 = ++fld_182;
        if ( v6 >= fld_20 )
          goto LABEL_6;
      }
      sub_4D3470(uArg2, *(void **)(*(uint32_t *)(this + 28) + 4 * v6), uArg4);
      free(pMem);
    }
  }
}



// ------------------------------------------------------------
// 0x4D3C30 sub_4D3C30
// ------------------------------------------------------------
char */*thiscall*/ sub_4D3C30(uint8_t *this, uint32_t *uArg2, char *Str)
{
  char *result; // eax
  char v4; // dl
  int i; // ecx
  int v6; // edx

  if ( *(this + 4) == 0 )
    return nullptr;
  if ( strstr(Str, "&#") != nullptr )
  {
    result = strstr(Str, "&#");
    v4 = result[2];
    for ( i = (int)(result + 2); v4 != 0; v4 = *(uint8_t *)++i )
    {
      if ( v4 == 38 )
      {
        if ( *(uint8_t *)(i + 1) == 35 )
          result = (char *)i;
      }
      else if ( v4 == 59 )
      {
        if ( uArg2 != nullptr )
          *uArg2 = i - (uint32_t)result + 1;
        return result;
      }
    }
  }
  if ( strstr(Str, "<br>") != nullptr )
  {
    if ( uArg2 != nullptr )
      *uArg2 = 4;
    return strstr(Str, "<br>");
  }
  else
  {
    v6 = 0;
    if ( (int)strlen(Str) <= 0 )
    {
LABEL_19:
      if ( strstr(Str, "&nbsp;") != nullptr )
      {
        if ( uArg2 != nullptr )
          *uArg2 = 6;
        return strstr(Str, "&nbsp;");
      }
      else if ( strstr(Str, "&nbsp") != nullptr )
      {
        if ( uArg2 != nullptr )
          *uArg2 = 5;
        return strstr(Str, "&nbsp");
      }
      else if ( strstr(Str, "&quot;") != nullptr )
      {
        if ( uArg2 != nullptr )
          *uArg2 = 6;
        return strstr(Str, "&quot;");
      }
      else if ( strstr(Str, "&amp;") != nullptr )
      {
        if ( uArg2 != nullptr )
          *uArg2 = 5;
        return strstr(Str, "&amp;");
      }
      else if ( strstr(Str, "&lt;") != nullptr )
      {
        if ( uArg2 != nullptr )
          *uArg2 = 4;
        return strstr(Str, "&lt;");
      }
      else if ( strstr(Str, "&gt;") != nullptr )
      {
        if ( uArg2 != nullptr )
          *uArg2 = 4;
        return strstr(Str, "&gt;");
      }
      else
      {
        return nullptr;
      }
    }
    else
    {
      while ( Str[v6] != 13 )
      {
        if ( ++v6 >= (int)strlen(Str) )
          goto LABEL_19;
      }
      if ( uArg2 != nullptr )
        *uArg2 = 1;
      return &Str[v6];
    }
  }
}



// ------------------------------------------------------------
// 0x4D3E60 sub_4D3E60
// ------------------------------------------------------------
uint8_t /*thiscall*/ sub_4D3E60(uint8_t *this, uint8_t *uArg2, char *Str, unsigned int uArg4)
{
  uint8_t result; // al
  char *pFound; // eax
  WCHAR WideCharStr[256]; // [esp+0h] [ebp-404h] BYREF
  char String[256]; // [esp+200h] [ebp-204h] BYREF
  CHAR MultiByteStr[256]; // [esp+300h] [ebp-104h] BYREF
  int dword_796E502; // [esp+400h] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = *(this + 4);
  if ( result != 0 )
  {
    if ( *Str == 38 && Str[1] == 35 )
    {
      pFound = strstr(Str, ";");
      sub_4D3470(String, Str + 2, (unsigned int)&pFound[-2 - (uint32_t)Str]);
      WideCharStr[0] = j__atol(String);
      WideCharToMultiByte(0, 0x200u, WideCharStr, 1, MultiByteStr, 256, nullptr, nullptr);
      MultiByteStr[2] = 0;
      return (uint8_t)sub_4D3470(uArg2, MultiByteStr, uArg4);
    }
    else if ( strcmp(Str, "<br>") == 0 )
    {
      return (uint8_t)sub_4D3470(uArg2, (void *)"\n", uArg4);
    }
    else if ( *Str == 13 )
    {
      return (uint8_t)sub_4D3470(uArg2, (void *)szPassword, uArg4);
    }
    else
    {
      if ( strcmp(Str, "&nbsp;") == 0 )
        return (uint8_t)sub_4D3470(uArg2, (void *)" ", uArg4);
      result = 0;
      if ( strcmp(Str, "&nbsp") == 0 )
      {
        return (uint8_t)sub_4D3470(uArg2, (void *)" ", uArg4);
      }
      else if ( strcmp(Str, "&quot;") == 0 )
      {
        return (uint8_t)sub_4D3470(uArg2, &unk_6F8688, uArg4);
      }
      else if ( strcmp(Str, "&amp;") == 0 )
      {
        return (uint8_t)sub_4D3470(uArg2, &word_6F8684, uArg4);
      }
      else if ( strcmp(Str, "&lt;") == 0 )
      {
        return (uint8_t)sub_4D3470(uArg2, (void *)"<", uArg4);
      }
      else if ( strcmp(Str, "&gt;") == 0 )
      {
        return (uint8_t)sub_4D3470(uArg2, (void *)">", uArg4);
      }
      else
      {
        *uArg2 = 0;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D4040 sub_4D4040
// ------------------------------------------------------------
int /*thiscall*/ sub_4D4040(uint32_t *this, int pArg2)
{
  int v3; // ecx
  unsigned int v4; // eax
  unsigned int v5; // eax
  void *pMem; // eax
  int i; // edi
  int v8; // edi
  int v9; // ebx
  size_t fld_e8; // [esp-8h] [ebp-10h]

  v3 = *(uint32_t *)(pArg2 + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2;
  else
    v4 = 0;
  v5 = v4 >> 1;
  *(this + 8) = v5;
  pMem = operator new(4 * v5);
  fld_e8 = 4 * *(this + 8);
  *(this + 6) = pMem;
  *(this + 7) = operator new(fld_e8);
  for ( i = 0; i < *(this + 8); ++i )
  {
    *(uint32_t *)(*(this + 6) + 4 * i) = operator new(0x20u);
    *(uint32_t *)(*(this + 7) + 4 * i) = operator new(0x20u);
  }
  v8 = 0;
  if ( (int)*(this + 8) > 0 )
  {
    v9 = 0;
    do
    {
      strcpy(*(char **)(*(this + 6) + 4 * v8), sub_41ACF0((unsigned int **)(v9 + *(uint32_t *)(pArg2 + 4))));
      strcpy(*(char **)(*(this + 7) + 4 * v8++), sub_41ACF0((unsigned int **)(v9 + *(uint32_t *)(pArg2 + 4) + 4)));
      v9 += 8;
    }
    while ( v8 < *(this + 8) );
  }
  return 1;
}



// ------------------------------------------------------------
// 0x4D4120 sub_4D4120
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4D4120(int this, int pArg2)
{
  unsigned int result; // eax
  int v4; // ebx
  int v5; // edi
  int fld_38; // eax
  int v7; // ebx
  int fld_34; // edi
  unsigned int v9; // edi
  int fld_382; // eax
  int v11; // edi
  int fld_74; // ecx
  uint32_t *fld_742; // eax
  uint32_t *v14; // edx
  int v15; // [esp+8h] [ebp-8h]
  int v16; // [esp+Ch] [ebp-4h]
  int v17; // [esp+18h] [ebp+8h]

  result = sub_554930(pArg2);  // 【IRDPopupWindow__vmt0】
  if ( pArg2 == *(uint32_t *)(this + 8) )
  {
    v4 = *(uint32_t *)(pArg2 + 20);
    v5 = *(uint32_t *)(pArg2 + 24);
    v16 = v4;
    fld_38 = sub_418DD0(*(uint32_t **)(this + 56), 0xD7u);
    if ( fld_38 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_38 + 152))(fld_38, v4 + 9, v5 + 7, dword_79C0B0);
    v7 = 0;
    v15 = 0;
    v17 = v5 + 48;
    do
    {
      fld_34 = sub_69C690(*(uint32_t *)(this + 52));
      result = *(uint32_t *)(this + 116);
      v9 = v7 + fld_34;
      if ( result != 0 )
      {
        result = (int)(*(uint32_t *)(this + 120) - result) / 52;
        if ( result > v9 )
        {
          fld_382 = sub_418DD0(*(uint32_t **)(this + 56), 0x5Au);
          if ( fld_382 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_382 + 128))(
              fld_382,
              v16 + 11,
              v17 - 10,
              dword_79C0B0,
              1065353216,
              1065353216,
              0,
              872415231,
              1333788672,
              1333788672);
          v11 = 52 * v9;
          fld_74 = *(uint32_t *)(*(uint32_t *)(this + 116) + v11 + 4);
          if ( fld_74 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_74 + 152))(fld_74, v16 + 12, v17 - 9, dword_79C0B0);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 60);
          fld_742 = (uint32_t *)(*(uint32_t *)(this + 116) + v11);
          if ( fld_742[8] < 0x10u )
            v14 = fld_742 + 3;
          else
            v14 = (uint32_t *)fld_742[3];
          (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v16 + 6,
            v17,
            fld_742[9],
            v14);
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
          v7 = v15;
        }
      }
      v15 = ++v7;
      v17 += 39;
    }
    while ( v7 < 3 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D42A0 sub_4D42A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D42A0(uint32_t *this)
{
  int v2; // edx
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  int v5; // ebx
  uint8_t *pMem2; // edi
  uint8_t *pMem3; // eax
  uint32_t *pMem32; // edi
  int fld_e14; // ebx
  uint32_t *fld_e10; // eax
  int result; // eax
  void *Block; // [esp+Ch] [ebp-14h]
  uint32_t *pThis_A; // [esp+10h] [ebp-10h]

  v2 = *this;
  *(this + 14) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 24))(18, 7);
  pMem = operator new(0x84u);
  if ( pMem != nullptr )
    v4 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);
  else
    v4 = nullptr;
  *(this + 9) = v4;
  sub_69A5F0(v4, 87, 73);
  sub_69A840(*(this + 9));
  v5 = 4;
  pThis_A = this + 10;
  do
  {
    pMem2 = operator new(0x84u);
    if ( pMem2 != nullptr )
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(pMem2);
      *(uint32_t *)pMem2 = &nengine::CNButton::`vftable';
      sub_69C780(v6);
      sub_69C7B0(Block, v5, v5, v5 + 1, v5, 0, 0);
    }
    else
    {
      v6 = nullptr;
    }
    *v13 = v6;
    v5 += 2;
    ++v13;
  }
  while ( v5 < 8 );
  v7 = operator new(0x88u);
  v8 = v7;
  if ( v7 != nullptr )
  {
    v9 = *(this + 14);
    sub_426BD0(v7);
    *v8 = &nengine::CNSlider::`vftable';
    sub_69CA20(pMem32);
    sub_69CA50(fld_e14, 87, 88);
    *pMem32 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    pMem32 = nullptr;
  }
  *(this + 12) = pMem32;
  if ( operator new(0x74u) != nullptr )
    fld_e10 = (uint32_t *)sub_43C630(*(this + 10), *(this + 11), *(this + 12));
  else
    fld_e10 = nullptr;
  *(this + 13) = fld_e10;
  sub_69A5F0(fld_e10, 218, 49);
  sub_69A840(*(this + 13));
  result = *(this + 13);
  *(uint8_t *)(result + 16) = 0;
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
  *(this + 27) = dword_99FCCC;
  *(this + 22) = 228;
  *(this + 18) = 1;
  *(this + 16) = -16777216;
  return result;
}



// ------------------------------------------------------------
// 0x4D44E0 sub_4D44E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4D44E0(uint32_t **this, int nArg2, int nArg3)
{
  sub_69A5F0(*(this + 2), (640 - (*(this + 2))[7]) / 2, (480 - (*(this + 2))[8]) / 2);
  sub_44CA70(this + 28);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 13) + 32))(*(this + 13), 0);
  return 1;
}



// ------------------------------------------------------------
// 0x4D4530 sub_4D4530
// ------------------------------------------------------------
int /*thiscall*/ sub_4D4530(int this, int *pDwArg2)
{
  int v3; // eax
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  const char *v9; // eax
  char *psz; // eax
  int fld_74; // eax
  int v13; // [esp-4h] [ebp-D0h]
  char Buffer[128]; // [esp+8h] [ebp-C4h] BYREF
  uint8_t v15[4]; // [esp+88h] [ebp-44h] BYREF
  int v16; // [esp+8Ch] [ebp-40h]
  size_t v17[8]; // [esp+90h] [ebp-3Ch] BYREF
  int v18; // [esp+B0h] [ebp-1Ch]
  int dword_796E502; // [esp+BCh] [ebp-10h]
  int v20; // [esp+C8h] [ebp-4h]

  dword_796E502 = dword_796E50;
  sub_459700(v15);
  v3 = *pDwArg2;
  v20 = 0;
  v4 = (*(int (/*thiscall*/ **)(int *))(v3 + 16))(pDwArg2);
  v5 = *pDwArg2;
  v16 = *(uint32_t *)(v4 + 68);
  v17[7] = (*(int (/*thiscall*/ **)(int *))(v5 + 24))(pDwArg2);
  v6 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 44))(pDwArg2);
  v7 = *pDwArg2;
  v18 = v6;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v7 + 16))(pDwArg2) + 4) != 0 )
  {
    psz = (char *)(*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 108))(pDwArg2);
    if ( v18 <= 1 )
    {
      sub_4015C0(v17, psz, strlen(psz));  // 【std::string构造赋值】
    }
    else
    {
      sprintf(Buffer, "%s", psz);
      sub_4015C0(v17, Buffer, strlen(Buffer));  // 【std::string构造赋值】
    }
  }
  else
  {
    v8 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 88), 0xAu);
    v13 = v18;
    v16 = v8;
    v9 = (const char *)sub_422E70(1116);
    sprintf(Buffer, v9, v13);
    sub_4015C0(v17, Buffer, strlen(Buffer));  // 【std::string构造赋值】
  }
  sub_45A340(v15);
  fld_74 = *(uint32_t *)(this + 116);
  if ( fld_74 != 0 )
    fld_74 = (*(uint32_t *)(this + 120) - fld_74) / 52;
  (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 52) + 32))(
    *(uint32_t *)(this + 52),
    fld_74 - 3 <= 0 ? 0 : fld_74 - 3);
  v20 = -1;
  return sub_477AF0(v15);
}



// ============================================================
// 【分区 3】IRDActiveObject 战斗核心 —— 生命周期 / 状态槽 / 伤害落地
// ★ 本区是《20 打击感与 HitStop 系统研究》的宿主层（受击者视角的全部状态字段）：
//   构造 0x4D46C0（§13：清 17 状态槽 this+6228..6292、18 观察者槽 +6468..6540、
//   两组伤害窗描述符默认 4、计时字段默认 1000/1000 —— 与反编译体逐条吻合）
//   析构 0x4D7000（§13：17 状态 vt+0 销毁、18 观察者 vt+4 引用计数释放）
// ============================================================

// ------------------------------------------------------------
// 0x4D46C0 sub_4D46C0 —— ★ ActiveObject 构造初始化（研究 20 §13 定案）
// this+96=17（状态槽计数）；this+1557..1573（word 下标） = +6228..6292 十七个异常状态槽清零；
// this+1617..1634（word 下标）= +6468..6536 十八个观察者槽清零；
// +6552 霸体字节、+6556 大状态、+6664/+6668 计时、+6752 标志；
// this[1663]=this[1664]=1000 —— 研究 §13 的"计时字段默认 1000/1000"直证；
// 循环 v2<2 段 = 两组伤害窗描述符（每组 5 个字段，末位 4 = 默认槽数，研究 §13）。
// 调用者：对象工厂 sub_4D2D60 的 case 0 之外的 ActiveObject 派发路径。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D46C0(uint32_t *this)
{
  int v2; // ecx
  uint32_t *pThis_676; // eax
  int result; // eax

  *(this + 24) = 17;
  *(this + 1557) = 0;
  *(this + 1558) = 0;
  *(this + 1559) = 0;
  *(this + 1560) = 0;
  *(this + 1561) = 0;
  *(this + 1562) = 0;
  *(this + 1563) = 0;
  *(this + 1564) = 0;
  *(this + 1565) = 0;
  *(this + 1566) = 0;
  *(this + 1567) = 0;
  *(this + 1568) = 0;
  *(this + 1569) = 0;
  *(this + 1570) = 0;
  *(this + 1571) = 0;
  *(this + 1572) = 0;
  *(this + 1573) = 0;
  *(this + 1574) = 0;
  *(this + 1617) = 0;
  *(this + 1618) = 0;
  *(this + 1619) = 0;
  *(this + 1620) = 0;
  *(this + 1621) = 0;
  *(this + 1622) = 0;
  *(this + 1623) = 0;
  *(this + 1624) = 0;
  *(this + 1625) = 0;
  *(this + 1626) = 0;
  *(this + 1627) = 0;
  *(this + 1628) = 0;
  *(this + 1629) = 0;
  *(this + 1630) = 0;
  *(this + 1631) = 0;
  *(this + 1632) = 0;
  *(this + 1633) = 0;
  *(this + 1634) = 0;
  *((uint8_t *)this + 6552) = 0;
  *(this + 1639) = 0;
  sub_699070(1);  // 【clock_bind_domain(clk, newDomainId)】
  *(this + 1647) = 0;
  *(this + 1649) = 0;
  *(this + 1648) = 0;
  *(this + 1650) = -1;
  *(this + 1651) = -1;
  v2 = 0;
  pThis_676 = this + 1654;
  do
  {
    *(pThis_676 - 2) = 0;
    *pThis_676 = 0;
    pThis_676[2] = 0;
    *((uint8_t *)this + v2 + 6634) = 0;
    pThis_676[5] = 4;
    ++v2;
    ++pThis_676;
  }
  while ( v2 < 2 );
  *(this + 1661) = 0;
  *(this + 1662) = 0;
  *(this + 1663) = 1000;
  *(this + 1664) = 1000;
  *(this + 1665) = 0;
  *(this + 1666) = 0;
  *((uint8_t *)this + 6668) = 0;
  *(this + 1668) = 0;
  *(this + 1669) = 0;
  *((uint8_t *)this + 6680) = 0;
  *((uint8_t *)this + 6681) = 0;
  *((uint8_t *)this + 6682) = 0;
  *(this + 1671) = 0;
  *(this + 1672) = -1;
  *(this + 1673) = -1;
  *(this + 1674) = -1;
  *(this + 1675) = 4;
  *(this + 1676) = 4;
  *(this + 1677) = 0;
  *((uint8_t *)this + 6740) = 1;
  *(this + 1686) = -1;
  *(this + 1687) = 0;
  *((uint8_t *)this + 6752) = 1;
  *(this + 1689) = 0;
  *(this + 1690) = 0;
  *(this + 1698) = 0;
  *(this + 1699) = 0;
  *(this + 1700) = 0;
  *(this + 1701) = 0;
  *(this + 1702) = 0;
  *(this + 1703) = 0;
  *(this + 1705) = 0;
  *(this + 1706) = 0;
  *(this + 1707) = -1;
  *(this + 1704) = 0;
  *(this + 1708) = 0;
  *(this + 1716) = 0;
  *(this + 1717) = 0;
  *(this + 1718) = 0;
  *(this + 1719) = 0;
  *(this + 1720) = 0;
  *(this + 1721) = 0;
  *(this + 1722) = 0;
  *(this + 1723) = 0;
  *(this + 1724) = 0;
  *(this + 1725) = 0;
  *((uint8_t *)this + 6988) = 0;
  *(this + 1748) = 20;
  *((uint8_t *)this + 6996) = 0;
  sub_41A590(0);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 932))(this);
  *((uint8_t *)this + 7092) = 0;
  *((uint8_t *)this + 7093) = 0;
  *(this + 1774) = -1;
  *(this + 1775) = -1;
  *((uint8_t *)this + 7105) = 0;
  *(this + 1777) = -1;
  *(this + 1778) = -1;
  *((uint8_t *)this + 7104) = 1;
  *((uint8_t *)this + 7129) = 0;
  *((uint8_t *)this + 7130) = 0;
  *((uint8_t *)this + 7144) = 1;
  return result;
}


// 0x4D49A0 sub_4D49A0 —— 场景判定 → +7088 = 0 / 7
// 已精修版见 src/cnrd/IRDActiveObject.cpp:134（0x4D49A0 vmt3A4）。
// 取全局对象 vmt120 的容器 +108 表首元素；15/16 号场景（PVP/战场？【待验证】）→ 7。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D49A0(uint32_t *this)
{
  int result; // eax

  result = **(uint32_t **)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108);
  if ( result < 15 || result > 16 )
    *(this + 1772) = 0;
  else
    *(this + 1772) = 7;
  return result;
}



// ------------------------------------------------------------
// 0x4D49E0 sub_4D49E0 —— 终结算 vt+544：播报层 HK_ATTACKED（研究 §1.2/§2⑩）
// 已精修版见 src/cnrd/IRDActiveObject.cpp:54（0x4D49E0 vmt220）。
// 条件 273（受击态）成立 → sub_426820(attackinfo, 3, 伤害值) —— 研究 §12 定案的
// HUD 评价横幅系统（HK_ATTACKED 累积受伤值 this+556），DLL 播报层锚点 [bc3] 源头。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D49E0(void *this, int nArg2, int nArg3)
{
  int v4; // edi
  int result; // eax

  v4 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);
  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 44))(this);
  if ( result == 273 )
    return sub_426820(*(uint32_t *)(v4 + 132), 3, nArg3);  // 【总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTA…】
  return result;
}



// ------------------------------------------------------------
// 0x4D4A20 sub_4D4A20 —— 攻方观察者通知 vt+504（六回调第 5 号，研究 §1.1）
// 已精修版见 src/cnrd/IRDActiveObject.cpp:28（0x4D4A20 vmt1F8）。
// 18 观察者逐个 vt+136(观察者, 攻, 受, 盒, flag=0, this+388) —— 轻量版
// （flag=0，对应 sub_4D6D90 = vt+500 的 flag=1 完整版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D4A20(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  uint32_t *pThis_651; // esi
  int i; // [esp+Ch] [ebp-4h]

  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )
  {
    if ( *pThis_651 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t, uint32_t *))(*(uint32_t *)*pThis_651 + 136))(
        *pThis_651,
        nArg2,
        nArg3,
        nArg4,
        0,
        this + 97);
    ++pThis_651;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4D4A80 sub_4D4A80 —— 受击后观察者 vt+516（六回调第 6 号，研究 §1.1/§1.2）
// 已精修版见 src/cnrd/IRDActiveObject.cpp:42（0x4D4A80 vmt204）。
// 18 观察者 vt+140(flag=0) + 尾调 sub_4E48D0（记录最后受击时刻 this+568
// + 仇人 id this+572 —— 击杀归属数据，研究 §1.1 定案）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D4A80(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  uint32_t *pThis_651; // esi
  int i; // [esp+10h] [ebp-4h]

  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )
  {
    if ( *pThis_651 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t))(*(uint32_t *)*pThis_651 + 140))(*pThis_651, nArg2, nArg3, nArg4, 0);
    ++pThis_651;
  }
  return sub_4E48D0(nArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x4D4AE0 sub_4D4AE0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D4AE0(uint32_t *this, int nArg2)
{
  int pObj; // ebx
  int v4; // edi
  uint32_t *v5; // edi
  int v6; // eax
  int result; // eax
  int v8; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  pObj = nArg2;
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 1) != 0 && *(uint32_t *)(v4 + 20) == 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 764))(this, 1, 0, 0, 0);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 8) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 4
    && *(this + 1708) == 2
    && *(uint32_t *)(v4 + 60) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 764))(this, 8, 0, 0, 0);
  }
  v5 = (uint32_t *)(v4 + 24);
  for ( i = 3; i != 0; --i )
  {
    if ( *v5 != 17 )
    {
      v8 = *this;
      v6 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 576))(pObj, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int))(v8 + 760))(this, *v5, v5[3], v5[6], v6);
      pObj = nArg2;
    }
    ++v5;
    result = i - 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D4BC0 sub_4D4BC0
// ------------------------------------------------------------
int /*userpurge*/ sub_4D4BC0@<eax>(int nArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4, int nArg5, int nArg6, char pszArg7)
{
  int result; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax

  if ( pszArg7 != 0 || (uint8_t)(result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 308))(nArg1)) != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)nArg1 + 768))(nArg1, nArg4, nArg5, nArg6, nArg3, nArg2);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 14, 1);
    v9 = *(uint32_t *)dword_8F8520;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 48))(nArg1);
    (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
    v11 = *(uint32_t *)dword_8F8520;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 52))(nArg1);
    (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nArg4);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg5);
    if ( nArg6 != 0 )
      v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg6 + 48))(nArg6);
    else
      v13 = 0xFFFF;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v13);
    if ( nArg6 != 0 )
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg6 + 52))(nArg6);
    else
      v14 = 0xFFFF;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v14);
    if ( nArg6 != 0 )
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg6 + 52))(nArg6);
    else
      v15 = 0xFFFF;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v15);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);
    return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D4CE0 sub_4D4CE0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D4CE0(char *this, int nArg2)
{
  char *pThis_1944; // esi
  int i; // ebx

  sub_4E7440(nArg2);
  pThis_1944 = this + 6468;
  for ( i = 18; i != 0; --i )
  {
    if ( *(uint32_t *)pThis_1944 != 0 )
      (*(void (/*stdcall*/ **)(char *))(**(uint32_t **)pThis_1944 + 128))(this + 388);
    pThis_1944 += 4;
  }
  return sub_53F7A0(this + 388);
}



// ------------------------------------------------------------
// 0x4D4D40 sub_4D4D40 —— ★★ HP setter / DMGAPPLY vt+728（研究 20 §1.1 定案；DLL 锚点 [13]）
// 调用点：命中主处理器 sub_4D71B0 ⑦ 伤害落地（研究 §2）—— 非延滞伤走 vt+728(this, 新HP, 0, 攻击者)。
//
// 参数（转写体 a1=this@ecx, a4=新HP 差值, a5=强制标志, a6=攻击者）：
//   ① vt+308（是否本地玩家的对象）门 —— 非玩家对象直接返回（研究 §1.2 vt+308 语义）
//   ② vt+724 门 —— 无敌/不可受击路径直接返回（无敌帧研究 P35：受击盒使能标志）
//   ③ vt+736(GetHP) 取当前值；a4<0 时（扣血）额外做"大伤害"分支：
//        v20 = 当前HP − a4（= 本次伤害值）；vt+740(最大HP) × 0.30000001（30%）阈值比较
//        —— 单次伤害 ≥ 30% 最大 HP → 置 this+7092 标志（濒死/大伤害标记）
//        并在 a6（攻击者）非空时做"击杀归属"三通道解析
//        （攻方 vt+576 车主 → 车主条件 273 → 取宿主 id → sub_495A70(1,3,id) 播音；
//          条件 529 分支走 __RTDynamicCast 到 IRDCharacter 再取 id）
//        —— 该三通道 = 研究 §1.2 "+544 收尾/命中语音"的受伤侧对偶
//   ④ 血条上限夹取：v15 夹在 [0, vt+740 最大HP] 之间
//   ⑤ a5（显式/强制）或 v15==0（归零 = 死亡）→ 走告示包序列（type 12）+ a1[1650]=−1
//      否则在离上次写入时刻 vt+736 变化且 a1[1650]==−1 时戳 a1[1650]=当前时钟
//   ⑥ 尾调 vt+732(this, v15) —— 写回 HP（研究 §13 的"HP 侧终点"）
//
// 与研究文档的差异核对：研究 §2⑥ 记"暴击成立则 伤害×1.25"系早期推断，
// 第 14 轮已更正为 ×1.5（在 sub_4E6770 尾段掷定）；本函数不做暴击倍率，
// 它只做"落地/夹取/告示/大伤害标记"，倍率在上游伤害流水线内完成。
// ------------------------------------------------------------
int /*userpurge*/ sub_4D4D40@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4, char pszArg5, int nArg6)
{
  int result; // eax
  int v8; // eax
  int nArg42; // edi
  int pObj2; // eax
  int *v11; // edi
  int v12; // eax
  int pObj; // ecx
  int pObj3; // eax
  int v15; // edi
  int v16; // ebx
  int v17; // eax
  int v18; // ebx
  int v19; // eax
  float v20; // [esp+4h] [ebp-8h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result == 0 )
    return result;
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 724))(pArg1);
  if ( (uint8_t)result != 0 )
    return result;
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 736))(pArg1, nArg3, nArg2);
  nArg42 = nArg4;
  if ( nArg4 < 0 )
  {
    v20 = (float)(v8 - nArg4);
    if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1) * 0.30000001 <= v20 )
    {
      *((uint8_t *)pArg1 + 7092) = 1;
      if ( nArg6 != 0 )
      {
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 4
          && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 40))(pArg1, 273) == 0
          && (*(uint32_t *)(dword_8F7A24 + 12) != 6
           || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 40))(pArg1, 273) == 0) )
        {
          goto LABEL_19;
        }
        pObj2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg6 + 576))(nArg6);
        v11 = (int *)pObj2;
        if ( pObj2 == 0 )
          goto LABEL_19;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) != 0 )
        {
          v12 = (*(int (/*thiscall*/ **)(int *))(*v11 + 52))(v11);
        }
        else
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v11 + 40))(v11, 529) == 0 )
            goto LABEL_19;
          pObj = v11[2088];
          if ( pObj == 0 )
            goto LABEL_19;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273) == 0 )
            goto LABEL_19;
          pObj3 = __RTDynamicCast(
                  v11[2088],
                  0,
                  &IRDActiveObject `RTTI Type Descriptor',
                  &IRDCharacter `RTTI Type Descriptor',
                  0);
          if ( pObj3 == 0 )
            goto LABEL_19;
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 52))(pObj3);
        }
        sub_495A70(1, 3, v12);
LABEL_19:
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg6 + 576))(nArg6) == dword_8F7C04 || nArg6 == dword_8F7C04 )
          sub_426820(*(uint32_t *)(pArg1[29] + 132), 0, 0);  // 【总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTA…】
        nArg42 = nArg4;
      }
    }
  }
  v15 = nArg42 < 0 ? 0 : nArg42;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1) < v15 )
    v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1);
  if ( pszArg5 != 0 || v15 == 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 12, 1);
    v16 = *(uint32_t *)dword_8F8520;
    v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 48))(pArg1);
    (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);
    v18 = *(uint32_t *)dword_8F8520;
    v19 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);
    (*(void (/*thiscall*/ **)(int, int))(v18 + 36))(dword_8F8520, v19);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v15);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    pArg1[1650] = -1;
  }
  else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 736))(pArg1) != v15 && pArg1[1650] == -1 )
  {
    pArg1[1650] = sub_699000(pArg1 + 2);  // 【clock_now(clk)】
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 732))(pArg1, v15);
}



// ------------------------------------------------------------
// 0x4D4F90 sub_4D4F90 —— MP setter vt+748（HP setter 0x4D4D40 的同构对偶）
// 流程镜像：vt+308 门 → vt+724 门 → vt+756(GetMP) 取当前 → 夹取 [0, vt+756] →
// a4(强制) 走告示包 type 13 + a1[1651]=−1；否则变化时戳 a1[1651] → 尾调 vt+748 写回。
// 与 0x4D4D40 共用 a1[1650]/a1[1651] 两个"上次写入时刻戳"字段。
// ------------------------------------------------------------
int /*userpurge*/ sub_4D4F90@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3, char pszArg4)
{
  int result; // eax
  int v6; // edi
  int v7; // ebx
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // edx

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 724))(pArg1);
    if ( (uint8_t)result == 0 )
    {
      v6 = nArg3 < 0 ? 0 : nArg3;
      if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 756))(pArg1, nArg2) < v6 )
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 756))(pArg1);
      if ( pszArg4 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 13, 1);
        v7 = *(uint32_t *)dword_8F8520;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 48))(pArg1);
        (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
        v9 = *(uint32_t *)dword_8F8520;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);
        (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v6);
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0, -1);
        v11 = *pArg1;
        pArg1[1651] = -1;
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(v11 + 748))(pArg1, v6);
      }
      else
      {
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 752))(pArg1) != v6 && pArg1[1651] == -1 )
          pArg1[1651] = sub_699000(pArg1 + 2);  // 【clock_now(clk)】
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 748))(pArg1, v6);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D50A0 sub_4D50A0
// ------------------------------------------------------------
void /*thiscall*/ sub_4D50A0(int *this, int pArg2)
{
  int fld_e30; // ecx
  float fld_e1664; // [esp+0h] [ebp-Ch]

  *(this + 30) = pArg2;
  if ( pArg2 != 0 )
  {
    sub_699070(*(this + 23));  // 【clock_bind_domain(clk, newDomainId)】
    if ( *(uint8_t *)(pArg2 + 168) != 0 )
      sub_4938F0(pArg2);
  }
  fld_e30 = *(this + 30);
  if ( fld_e30 != 0 )
  {
    fld_e1664 = (double)*(this + 1664) * 0.1;
    sub_493D00(fld_e30, fld_e1664);
  }
}



// ------------------------------------------------------------
// 0x4D50F0 sub_4D50F0
// ------------------------------------------------------------
void /*thiscall*/ sub_4D50F0(int *this, int nArg2, int nArg3, int nArg4, int nArg5, char pszArg6, char pszArg7)
{
  float fld_e1664; // [esp+0h] [ebp-Ch]

  sub_49A7B0(nArg2, nArg3, nArg4, nArg5, pszArg6, pszArg7);
  if ( nArg3 != 0 )
  {
    fld_e1664 = (double)*(this + 1664) * 0.1;
    sub_493D00(nArg3, fld_e1664);
  }
}



// ------------------------------------------------------------
// 0x4D5140 sub_4D5140 —— ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
// `*(this + a2 + 1557)` = 17 槽状态槽 this+6228..6292（word 下标 1557..1573），
// 槽非空再问状态对象->vt+24()（"当前是否激活"）—— 研究 §10 状态枚举 0..16
// （slow0/freeze1/poison2/stun3/curse4/blind5/lightning6/stone7/sleep8/burn9/
// deadlystrike10/bleeding11/haste12/bless13/element14/confuse15/hold16）。
// 全库消费点密集：表现壳判 freeze(1)、命中主处理器判 1/7、无敌族判 16 等。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4D5140(uint32_t *this, int pArg2)
{
  int pObj; // edx

  pObj = *(this + pArg2 + 1557);
  return pObj != 0 && (*(uint8_t (**)(void))(*(uint32_t *)pObj + 24))() != 0;
}



// ------------------------------------------------------------
// 0x4D5170 sub_4D5170 —— ★ 霸体 setter vt+720（研究 20 §1.2 + §14#10 定案）
// 写 this+6552 霸体字节；**开启（a2!=0）时通知全部 17 个"已激活"的状态对象
// ->vt+68()**（逐槽 vt+776 查询 → 状态对象 vt+68 回调）—— 与反编译体循环
// `for v4<17，vt+776 非 0 才调 *v5+68` 逐条吻合。
// 研究 §14#10：调用者 = ~94 张子类虚表（霸体开启由子类/技能逻辑驱动）；
// `.ani` 帧 DAMAGE TYPE(+52) → +6552 的直连仍未证实【待验证】。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D5170(uint8_t *this, char pszArg2)
{
  char result; // al
  int v4; // esi
  uint32_t *pThis_1854; // edi

  result = pszArg2;
  if ( pszArg2 != *(this + 6552) )
  {
    *(this + 6552) = pszArg2;
    if ( pszArg2 != 0 )
    {
      v4 = 0;
      pThis_1854 = this + 6228;
      do
      {
        result = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 776))(this, v4);
        if ( result != 0 )
          result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_1854 + 68))(*pThis_1854);
        ++v4;
        ++pThis_1854;
      }
      while ( v4 < 17 );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D51C0 sub_4D51C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D51C0(uint32_t *this)
{
  int v2; // esi
  uint32_t *pThis_615; // edi
  int result; // eax

  v2 = 0;
  pThis_615 = this + 1557;
  do
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, v2);
    if ( (uint8_t)result != 0 )
      result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)*pThis_615 + 4))(*pThis_615, 0, 0);
    ++v2;
    ++pThis_615;
  }
  while ( v2 < 17 );
  return result;
}



// ------------------------------------------------------------
// 0x4D5200 sub_4D5200
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5200(uint8_t *this, int *pDwArg2)
{
  int result; // eax
  uint8_t *pThis; // esi
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // edx
  int v9; // eax
  int v10; // [esp-8h] [ebp-10h]

  result = *pDwArg2;
  pThis = this;
  switch ( *pDwArg2 )
  {
    case 0:
      v4 = *(uint32_t *)this;
      LOBYTE(this) = pDwArg2[3] == 0;
      return (*(int (/*thiscall*/ **)(uint8_t *, uint8_t *))(v4 + 604))(pThis, this);
    case 1:
      if ( pDwArg2[3] != 0 )
      {
        v5 = *(uint32_t *)this;
        *(this + 7093) = 1;
        return (*(int (/*stdcall*/ **)(int, int))(v5 + 252))(3, 100);
      }
      else
      {
        v6 = *(uint32_t *)this;
        *(this + 7093) = 0;
        return (*(int (/*stdcall*/ **)(int, int))(v6 + 252))(3, -1);
      }
    case 2:
      v7 = *(uint32_t *)this;
      if ( pDwArg2[3] == 1 )
      {
        if ( (*(uint8_t (**)(void))(v7 + 616))() == 0
          || (result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pThis + 620))(pThis)) != 1 )
        {
          v10 = 1;
          goto LABEL_20;
        }
      }
      else
      {
        result = (*(int (**)(void))(v7 + 616))();
        if ( (uint8_t)result == 1 )
        {
          result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pThis + 620))(pThis);
          if ( result == 1 )
          {
            v10 = 1;
            goto LABEL_20;
          }
        }
      }
      return result;
    case 3:
      v8 = *(uint32_t *)this;
      if ( pDwArg2[3] == 1 )
      {
        if ( (*(uint8_t (**)(void))(v8 + 616))() != 0 )
        {
          result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pThis + 620))(pThis);
          if ( result == 2 )
            return result;
        }
      }
      else
      {
        result = (*(int (**)(void))(v8 + 616))();
        if ( (uint8_t)result != 1 )
          return result;
        result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pThis + 620))(pThis);
        if ( result != 2 )
          return result;
      }
      v10 = 2;
LABEL_20:
      v9 = pDwArg2[3];
      LOBYTE(v9) = v9 == 1;
      return (*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pThis + 612))(pThis, v9, v10);
    default:
      return result;
  }
}



// ------------------------------------------------------------
// 0x4D5330 sub_4D5330 —— 伤害日志写出（DNF.trc；研究 §2⑦ 定案勿与 HP setter 混淆）
// 打包站 type 20/子命令 2：依次写 受方 id/子id、攻方 id/子id、伤害盒 6 个 float
// （a3[0] 以 4 字节写、a3[1..5] 各 2 字节）、abs(伤害值 a4)、abs(类型 a5)、
// 受方 vt+736（HP 快照）、标志位（a6 != 0）、abs(a7)、a8，然后提交。
// 调用者 = 命中主处理器 0x4D71B0 的伤害落地分支（§2⑦ sub_4D5330 写 DNF.trc）。
// ------------------------------------------------------------
int /*cdecl*/ sub_4D5330(int nArg1, int nArg2, float *pArg3, int nArg4, int nArg5, char pszArg6, int nArg7, int nArg8)
{
  int v8; // edi
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v13; // edi
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // edx
  int v21; // [esp+8h] [ebp-4h] BYREF

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 20, 2);
  v8 = *(uint32_t *)dword_8F8520;
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 48))(nArg1);
  (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);
  v10 = *(uint32_t *)dword_8F8520;
  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 52))(nArg1);
  (*(void (/*thiscall*/ **)(int, int))(v10 + 36))(dword_8F8520, v11);
  v13 = *(uint32_t *)dword_8F8520;
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 48))(nArg2);
  (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);
  v15 = *(uint32_t *)dword_8F8520;
  v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 52))(nArg2);
  (*(void (/*thiscall*/ **)(int, int))(v15 + 36))(dword_8F8520, v16);
  (*(void (/*thiscall*/ **)(int, float *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, pArg3, 4);
  v21 = (uint64_t)pArg3[1];
  (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &v21, 2);
  v21 = (uint64_t)pArg3[2];
  (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &v21, 2);
  v21 = (uint64_t)pArg3[3];
  (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &v21, 2);
  v21 = (uint64_t)pArg3[4];
  (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &v21, 2);
  v21 = (uint64_t)pArg3[5];
  (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &v21, 2);
  (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, abs32(nArg4));
  (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, abs32(nArg5));
  v17 = *(uint32_t *)dword_8F8520;
  v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 736))(nArg2);
  (*(void (/*thiscall*/ **)(int, int))(v17 + 40))(dword_8F8520, v18);
  LOBYTE(v19) = pszArg6 != 0;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v19);
  (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, abs32(nArg7));
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nArg8);
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
}



// ------------------------------------------------------------
// 0x4D54E0 sub_4D54E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4D54E0(int *this)
{
  int v2; // edi
  int fld_e1777; // eax
  int fld_e30; // ecx
  int v5; // ebx
  uint64_t v6; // rax
  int fld_e302; // ecx
  int v8; // edi

  sub_53F960(*(this + 1574));
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) != 0 )
  {
    v2 = 0;
    fld_e1777 = sub_699000((int)(this + 9)) - *(this + 1777);  // 【clock_now(clk)】
    if ( fld_e1777 <= 1000 )
      v2 = (uint64_t)sub_4049C0(255.0, 0.0, fld_e1777, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    fld_e30 = *(this + 30);
    if ( fld_e30 != 0 )
    {
      sub_4938F0(fld_e30);
      if ( ((*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 40))(this, 273) != 0 && (int *)dword_8F7C04 == this
         || (v5 = (*(int (/*thiscall*/ **)(int *))(*this + 376))(this)) == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04))
        && v2 <= 128 )
      {
        v2 = 128;
      }
      sub_491F80(*(this + 30), -1, -1, -1, v2, 1);
    }
    LODWORD(v6) = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( (int)v6 >= *(this + 1778) )
      LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 944))(this, 0, -1);
  }
  else
  {
    LODWORD(v6) = *(this + 1778);
    if ( (uint32_t)v6 != -1 )
    {
      LODWORD(v6) = sub_699000((int)(this + 9)) - *(this + 1777);  // 【clock_now(clk)】
      if ( (int)v6 > 1000 )
      {
        *(this + 1778) = -1;
      }
      else
      {
        v6 = (uint64_t)sub_4049C0(0.0, 255.0, v6, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        fld_e302 = *(this + 30);
        v8 = v6;
        if ( fld_e302 != 0 )
        {
          sub_4938F0(fld_e302);
          if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 40))(this, 273) != 0
            && (int *)dword_8F7C04 == this
            && v8 <= 128 )
          {
            v8 = 128;
          }
          LOBYTE(v6) = sub_491F80(*(this + 30), -1, -1, -1, v8, 1);
        }
      }
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x4D5650 sub_4D5650 —— ★ HP 吸收/回复量折算（研究 §12 [HP drain]/[MP drain] 消费侧）
// vt+716 取"基础值+加成"两路浮点（&v10/&v11），按 a4 选全局系数
// （0 → flt_9A05FC；1 → flt_9A0614 —— 运行时从数据文件加载，PE 内全 0，研究 §11）；
// 场景 4/6（PVP/战场）系数 ×2（研究 §11 "PVP/战场速率走查表修正"同族）；
// 最终 `a3 × (v10+v11) × 系数 / (1 − (v10+v11))`，比率上限 0.99000001。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4D5650(int *this, uint32_t *uArg2, int nArg3, int nArg4, int nArg5)
{
  int v5; // eax
  double v6; // st7
  int v7; // eax
  double v8; // st6
  uint64_t result; // rax
  float v10; // [esp+4h] [ebp-8h] BYREF
  float v11; // [esp+8h] [ebp-4h] BYREF

  v5 = *this;
  v10 = 0.0;
  v11 = 0.0;
  (*(void (/*thiscall*/ **)(int *, float *, float *, int, int))(v5 + 716))(this, &v10, &v11, nArg3, nArg4);
  v6 = 0.0;
  if ( nArg4 != 0 )
  {
    if ( nArg4 == 1 )
      v6 = flt_9A0614;
  }
  else
  {
    v6 = flt_9A05FC;
  }
  v7 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v7 == 4 || v7 == 6 )
    v6 = v6 + v6;
  v8 = v11 + v10;
  if ( v8 >= 0.99000001 )
    v8 = 0.99000001;
  result = (uint64_t)((double)nArg3 * v8 * v6 / (1.0 - v8));
  *uArg2 = result;
  return result;
}



// ------------------------------------------------------------
// 0x4D5700 sub_4D5700 —— 状态对象引用移交（self == a2 时对 17 个激活状态 ->vt+80）
// 与 0x4D51C0（17 槽 ->vt+4 清理）成族 —— 研究 §10 状态对象生命周期。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5700(uint32_t *this, uint32_t *uArg2)
{
  int result; // eax
  int v4; // esi
  uint32_t *pThis_615; // edi

  result = (int)uArg2;
  if ( uArg2 == this )
  {
    v4 = 0;
    pThis_615 = this + 1557;
    do
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, v4);
      if ( (uint8_t)result != 0 )
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t *))(*(uint32_t *)*pThis_615 + 80))(*pThis_615, uArg2);
      ++v4;
      ++pThis_615;
    }
    while ( v4 < 17 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D5750 sub_4D5750
// ------------------------------------------------------------
void /*usercall*/ sub_4D5750(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // edi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // eax

  if ( pArg1[1639] == 9 )
  {
    if ( pArg1[1687] != 0 )
      v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg3) + 1;
    else
      v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg3) - 1;
    v5 = sub_432E50(pArg1[1687]);
    v6 = *pArg1;
    pArg1[1687] = v5;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(v6 + 124))(pArg1, 0, nArg2);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int))(v6 + 136))(pArg1, v4, v7) == 0 )
    {
      if ( pArg1[1687] != 0 )
        v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) + 1;
      else
        v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - 1;
      pArg1[1687] = sub_432E50(pArg1[1687]);
    }
    v8 = *pArg1;
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 124))(pArg1, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int))(v8 + 136))(pArg1, v4, v9) != 0 )
    {
      v10 = *pArg1;
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v11);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v10 + 112))(pArg1, v4, v12);
    }
  }
}



// ------------------------------------------------------------
// 0x4D5820 sub_4D5820
// ------------------------------------------------------------
void /*thiscall*/ sub_4D5820(int *this)
{
  int fld_e30; // edi
  int v3; // eax
  uint32_t *pThis_607; // ecx
  uint32_t *i; // edx

  if ( *(this + 1639) == 9 )
  {
    fld_e30 = *(this + 30);
    v3 = 0;
    pThis_607 = this + 1543;
    for ( i = this + 1544; fld_e30 != *pThis_607 || *i == 0; --i )
    {
      ++v3;
      ++pThis_607;
      if ( v3 >= 2 )
        return;
    }
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1544 - v3));
    sub_4926A0(*(this + 30));
    sub_4939E0(*(this + 30), 1);
  }
}



// ------------------------------------------------------------
// 0x4D5890 sub_4D5890
// ------------------------------------------------------------
char /*thiscall*/ sub_4D5890(void *this, int nArg2, int nArg3, int nArg4)
{
  if ( (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 776))(this, 16) != 0 )
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) == 5;
  else
    return sub_4E4950(nArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x4D58E0 sub_4D58E0
// ------------------------------------------------------------
BOOL /*stdcall*/ sub_4D58E0(int nArg1)
{
  return nArg1 >= 0;
}



// ------------------------------------------------------------
// 0x4D5900 sub_4D5900
// ------------------------------------------------------------
char /*thiscall*/ sub_4D5900(uint32_t *this, int nArg2, int nArg3, char pszArg4)
{
  char result; // al

  sub_41A590(nArg2);
  if ( nArg2 == 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 720))(this, 1);
  result = pszArg4;
  if ( pszArg4 != 0 )
    *(this + 1650) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x4D5940 sub_4D5940
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5940(uint32_t *this, int nArg2)
{
  int result; // eax

  switch ( *(this + 1772) )
  {
    case 2:
      if ( nArg2 != 0 )
      {
        if ( nArg2 == 1 )
        {
          result = 31;
        }
        else
        {
          if ( nArg2 != 2 )
            goto LABEL_28;
          result = 32;
        }
      }
      else
      {
        result = 30;
      }
      break;
    case 3:
      if ( nArg2 != 0 )
      {
        if ( nArg2 == 1 )
        {
          result = 34;
        }
        else
        {
          if ( nArg2 != 2 )
            goto LABEL_28;
          result = 35;
        }
      }
      else
      {
        result = 33;
      }
      break;
    case 7:
      if ( nArg2 != 0 )
      {
        if ( nArg2 == 1 )
        {
          result = 37;
        }
        else
        {
          if ( nArg2 != 2 )
            goto LABEL_28;
          result = 38;
        }
      }
      else
      {
        result = 36;
      }
      break;
    case 8:
      if ( nArg2 != 0 )
      {
        if ( nArg2 == 1 )
        {
          result = 41;
        }
        else
        {
          if ( nArg2 != 2 )
            goto LABEL_28;
          result = 42;
        }
      }
      else
      {
        result = 40;
      }
      break;
    default:
      if ( nArg2 != 0 )
      {
        if ( nArg2 == 1 )
          result = 11;
        else
LABEL_28:
          result = 12;
      }
      else
      {
        result = 10;
      }
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D5A60 sub_4D5A60 —— ★ 伤害类型/命中类型计算 vt+648（研究 §1.2 定案 6 版本之一）
// this+7093 == 1（格挡中）→ *a2 = 0、返回 3（落空/格挡类）；否则 *a2 = 100、返回 0。
// 研究 §1.2：+648 每类不同（0x4D5A60 等 6 版本），返回 0/1/2，2 = 落空；
// 本版本返回 3 是"格挡且伤害置零"特例 —— 表现壳/命中主处理器以 `!= 2` 作放行判据。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5A60(uint8_t *this, uint32_t *uArg2, int nArg3)
{
  if ( *(this + 7093) == 1 )
  {
    *uArg2 = 0;
    return 3;
  }
  else
  {
    *uArg2 = 100;
    return 0;
  }
}



// ------------------------------------------------------------
// 0x4D5A90 sub_4D5A90
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5A90(int this, int nArg2, char pszArg3)
{
  *(uint32_t *)(this + 7096) = sub_699000(this + 36);
  *(uint32_t *)(this + 7100) = nArg2;
  *(uint8_t *)(this + 7104) = pszArg3;
  return nArg2;
}



// ------------------------------------------------------------
// 0x4D5AC0 sub_4D5AC0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5AC0(int *this)
{
  int result; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1000))(this) == 0 )
    return 0;
  result = *(this + 1775);
  if ( *((uint8_t *)this + 7104) != 0 )
    return 1000 * result / *(this + 1664);
  return result;
}



// ------------------------------------------------------------
// 0x4D5B00 sub_4D5B00
// ------------------------------------------------------------
int64_t /*thiscall*/ sub_4D5B00(void *this)
{
  int pThis_3EC; // edi
  int pThis_3F0; // eax
  double v4; // st7

  pThis_3EC = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1004))(this);
  pThis_3F0 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1008))(this);
  v4 = sub_4049C0(0.0, 50.0, pThis_3F0, pThis_3EC);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  return _ftol2(v4);
}



// ------------------------------------------------------------
// 0x4D5B30 sub_4D5B30
// ------------------------------------------------------------
bool /*thiscall*/ sub_4D5B30(uint32_t *this)
{
  int fld_e161; // edi
  int fld_e30; // edi
  bool v4; // bl
  bool v6; // [esp+Dh] [ebp-3h]
  char v7; // [esp+Eh] [ebp-2h]
  char v8; // [esp+Fh] [ebp-1h]

  if ( *((uint8_t *)this + 642) != 0 )
  {
    fld_e161 = *(this + 161);
  }
  else
  {
    fld_e30 = *(this + 30);
    if ( fld_e30 == 0 )
    {
LABEL_9:
      v8 = 1;
      goto LABEL_10;
    }
    if ( *(uint32_t *)(fld_e30 + 148) == -1 )
      sub_4938F0(*(this + 30));
    fld_e161 = *(uint32_t *)(fld_e30 + 112);
  }
  if ( fld_e161 == 0 )
    goto LABEL_9;
  v8 = 0;
  if ( fld_e161 == 1 )
    goto LABEL_9;
LABEL_10:
  v4 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 688))(this) + 12) != 0;
  v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 688))(this) + 20) != 0;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 1) != 0
    || (v7 = 1, (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 7) != 0) )
  {
    v7 = 0;
  }
  return *((uint8_t *)this + 612) != 0
      && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 9
      && v8 != 0
      && v4
      && v6
      && v7 != 0;
}



// ------------------------------------------------------------
// 0x4D5C10 sub_4D5C10
// ------------------------------------------------------------
bool /*thiscall*/ sub_4D5C10(uint8_t *this)
{
  return *(this + 6740) != 0
      && *(this + 6552) == 0
      && (*(uint8_t (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 776))(this, 1) == 0
      && (*(uint8_t (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 776))(this, 7) == 0;
}



// ------------------------------------------------------------
// 0x4D5C50 sub_4D5C50
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5C50(uint32_t *this)
{
  uint32_t *pThis_651; // esi
  int i; // edi

  sub_499790();
  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )
  {
    if ( *pThis_651 != 0 )
      (*(void (**)(void))(*(uint32_t *)*pThis_651 + 160))();
    ++pThis_651;
  }
  return sub_53F8F0(*(this + 1574));
}



// ------------------------------------------------------------
// 0x4D5C90 sub_4D5C90
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5C90(int *this, int nArg2)
{
  int result; // eax
  int v4; // edi
  uint64_t v5; // rax

  result = nullsub_1(nArg2);
  if ( nArg2 == 6 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);
    if ( result > 0 )
    {
      v4 = *this;
      v5 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 736))(this, 0, 1) * 1.2);
      return (*(int (/*fastcall*/ **)(int *, uint32_t, uint32_t))(v4 + 732))(this, HIDWORD(v5), v5);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D5CF0 sub_4D5CF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5CF0(void *this, int nArg2)
{
  int result; // eax
  double pThis_2E0; // st7

  result = nullsub_1(nArg2);
  if ( nArg2 == 6 )
  {
    result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 736))(this);
    if ( result > 0 )
    {
      if ( (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 736))(this) * 0.83333331 <= 1.0 )
        pThis_2E0 = 1.0;
      else
        pThis_2E0 = (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 736))(this) * 0.83333331;
      return (*(int (/*fastcall*/ **)(void *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 732))(
               this,
               (uint64_t)pThis_2E0 >> 32,
               (uint64_t)pThis_2E0,
               0,
               1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D5D70 sub_4D5D70
// ------------------------------------------------------------
int /*stdcall*/ sub_4D5D70(int nArg1, uint32_t *pArg2)
{
  int result; // eax
  unsigned int v3; // esi
  int v4; // edx
  int v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // edi
  int v9; // eax
  int v10; // edx
  int v11; // [esp+10h] [ebp+Ch]

  result = nArg1;
  if ( nArg1 == 6 )
  {
    v3 = (unsigned int)pArg2 + 18;
    *(float *)&v11 = COERCE_FLOAT(sub_41A5E0((unsigned int)pArg2 + 18)) * 1.2;
    return sub_41A590(v3, v4, v11);
  }
  else if ( nArg1 == 18 )
  {
    v5 = dword_9A05C8 * *pArg2;
    v6 = sub_41A5E0((unsigned int)(pArg2 + 260));
    sub_41A590((unsigned int)(pArg2 + 260), v7, v5 + v6);
    v8 = dword_9A05C8 * *pArg2;
    v9 = sub_41A5E0((unsigned int)(pArg2 + 274));
    return sub_41A590((unsigned int)(pArg2 + 274), v10, v8 + v9);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D5E00 sub_4D5E00
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4D5E00(void *this)
{
  int pThis_74; // [esp+8h] [ebp-4h]

  pThis_74 = sub_41A5E0((unsigned int)this + 116);
  return (uint64_t)((double)pThis_74 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 130)));
}



// ------------------------------------------------------------
// 0x4D5E40 sub_4D5E40
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4D5E40(char *this, int nArg2)
{
  char *pThis_E; // esi
  int v4; // [esp+10h] [ebp+8h]

  pThis_E = this + 14 * nArg2;
  v4 = sub_41A5E0((unsigned int)(pThis_E + 284));
  return (uint64_t)((double)v4 * COERCE_FLOAT(sub_41A5E0((unsigned int)(pThis_E + 508))));
}



// ------------------------------------------------------------
// 0x4D5E80 sub_4D5E80 —— CNRDActiveStatus 构造（17 槽状态对象的实现类）
// 设 CNRDActiveStatus::vftable + 内嵌两个 nengine::IObject 子块（+60/+156）
// 各带 off_6C2B88 子表，随后 sub_496CE0（基类）+ sub_497840（本类初始化，
// 携带 Block=状态 id、a3=宿主）—— 研究 §10 "状态对象自身持有独立时钟（状态+60）"
// 与此处 +60 子块吻合；状态对象由 0x4D6030 懒创建。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5E80(int this, void *Block, int nArg3)
{
  *(uint32_t *)this = &CNRDActiveStatus::`vftable';
  *(uint8_t *)(this + 64) = 0;
  *(uint32_t *)(this + 60) = &off_6C2B88;
  *(uint32_t *)(this + 68) = 0;
  *(uint8_t *)(this + 72) = 1;
  *(uint8_t *)(this + 74) = 0;
  *(uint8_t *)(this + 73) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint8_t *)(this + 160) = 0;
  *(uint32_t *)(this + 156) = &off_6C2B88;
  *(uint32_t *)(this + 164) = 0;
  *(uint8_t *)(this + 168) = 1;
  *(uint8_t *)(this + 170) = 0;
  *(uint8_t *)(this + 169) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 172) = 0;
  sub_496CE0(this);
  sub_497840((int *)this, Block, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x4D5FA0 sub_4D5FA0
// ------------------------------------------------------------
void */*thiscall*/ sub_4D5FA0(void *Block, char pszArg2)
{
  sub_4D5FD0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4D5FD0 sub_4D5FD0
// ------------------------------------------------------------
char /*thiscall*/ sub_4D5FD0(int this)
{
  *(uint32_t *)this = &CNRDActiveStatus::`vftable';
  sub_497500((char *)this);
  *(uint32_t *)(this + 156) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 160) = 0;
  *(uint32_t *)(this + 60) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 64) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4D6030 sub_4D6030 —— ★ 状态施加入口（17 状态槽懒创建 + 转发）
// = 研究 §13"观察者/状态懒创建族"的状态侧对偶；流程：
//   vt+724（无敌门）不通过才继续；Block(=状态 id) 属于 {1,7} → 检查动画对象 +12；
//   ==8 → 检查 +20 且大状态 != 9（研究 §10 的 stun(3)/sleep(8) 互斥门近似）；
//   `*(this + Block + 1557)` = 17 槽之一（+6228 数组，研究 §1.2 定案布局）；
//   槽空 && a3 != 0 → new 0xD0 字节 → sub_4D5E80(状态对象, 状态id, this)；
//   尾调 状态对象->vt+4(状态对象, a3, a4) —— 施加/解除。
// 注：这里的第三参 a3 是"是否新建/强度"，与 sub_5FB830（0x64 区状态施加器，
// 研究 §10）不是同一函数 —— 后者按状态枚举分派到 vt+848/时钟冻结，本函数只到 vtable。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D6030(uint32_t *this, void *Block, int nArg3, int nArg4)
{
  int result; // eax
  void *pMem; // eax
  int v7; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 724))(this);
  if ( (uint8_t)result == 0 )
  {
    if ( Block == (void *)1 || Block == (void *)7 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);
      if ( *(uint32_t *)(result + 12) == 0 )
        return result;
    }
    else if ( Block == (void *)8 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);
      if ( *(uint32_t *)(result + 20) == 0 )
        return result;
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
      if ( result == 9 )
        return result;
    }
    result = *(this + (uint32_t)Block + 1557);
    if ( result == 0 )
    {
      if ( nArg3 == 0 )
        return result;
      pMem = operator new(0xD0u);
      if ( pMem != nullptr )
        v7 = sub_4D5E80((int)pMem, Block, (int)this);
      else
        v7 = 0;
      *(this + (uint32_t)Block + 1557) = v7;
    }
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)*(this + (uint32_t)Block + 1557) + 4))(
             *(this + (uint32_t)Block + 1557),
             nArg3,
             nArg4);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D6130 sub_4D6130 —— HP/MP 自然回复逐帧累加（小数累积器模式）
// v16 = 本帧历时（时钟 this+16 差值）；两路独立：
//   ① HP：属性 (vt+672 块 +760) × (+774) × dt × 0.01 × 0.001 × PVE/PVP 系数(0x4D33A0 场景门)
//      累加到 this+1649；|值| ≥ 1.0 → vt+684(取HP) + vt+728(=HP setter, 0x4D4D40) 落地
//      并把余数留在 this+1649（避免低帧率丢回复量）
//   ② MP：+788/+802 同构 → this+1648 → vt+744(MP setter)
// 与研究 §4.4/§16 的时间域架构一致：回复速率消费 dt，而 dt 在时钟冻结时 = 0
// （sub_699000 恒返定格值）—— 所以卡肉期间不回复。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D6130(float *this)
{
  int pThis_10; // edi
  int pThis_2A0; // edi
  long double fld_e1649; // st7
  unsigned int pThis_2AC; // eax
  int v6; // eax
  int pThis_2A02; // edi
  long double fld_e1648; // st7
  int pThis_2AC2; // eax
  int v10; // eax
  float v11; // [esp+8h] [ebp-Ch]
  int v12; // [esp+8h] [ebp-Ch]
  int v13; // [esp+8h] [ebp-Ch]
  int v14; // [esp+8h] [ebp-Ch]
  int v15; // [esp+Ch] [ebp-8h]
  int pThis_102; // [esp+10h] [ebp-4h]
  float v17; // [esp+10h] [ebp-4h]

  pThis_10 = (int)(this + 16);
  pThis_102 = sub_699000((int)(this + 16)) - *((uint32_t *)this + 1647);  // 【clock_now(clk)】
  *((uint32_t *)this + 1647) = sub_699000(pThis_10);
  pThis_2A0 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);
  v15 = sub_41A5E0(pThis_2A0 + 760);
  v17 = (float)pThis_102;
  v11 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 774));
  fld_e1649 = sub_433F60((int)this, 2) * ((double)(int)(uint64_t)((double)v15 * v11) * v17 * 0.0099999998 * 0.001)
     + *(this + 1649);
  *(this + 1649) = fld_e1649;
  if ( fabs(fld_e1649) >= 1.0 )
  {
    v12 = (uint64_t)fld_e1649;
    pThis_2AC = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 684))(this);
    v6 = sub_41A5E0(pThis_2AC);
    (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t))(*(uint32_t *)this + 728))(this, v12 + v6, 0, 0);
    *(this + 1649) = *(this + 1649) - (double)v12;
  }
  pThis_2A02 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);
  v13 = sub_41A5E0(pThis_2A02 + 788);
  fld_e1648 = (double)(int)(uint64_t)((double)v13 * COERCE_FLOAT(sub_41A5E0(pThis_2A02 + 802))) * v17 * 0.050000001 * 0.001
     + *(this + 1648);
  *(this + 1648) = fld_e1648;
  if ( fabs(fld_e1648) >= 1.0 )
  {
    v14 = (uint64_t)fld_e1648;
    pThis_2AC2 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 684))(this);
    v10 = sub_41A5E0(pThis_2AC2 + 14);
    (*(void (/*thiscall*/ **)(float *, int, uint32_t))(*(uint32_t *)this + 744))(this, v14 + v10, 0);
    *(this + 1648) = *(this + 1648) - (double)v14;
  }
}



// ------------------------------------------------------------
// 0x4D62D0 sub_4D62D0 —— ★ 物理/魔法攻击力基值（研究 §5.1/§12 的"攻击力"项）
// a2 = 0（物理）/ 1（魔法）二路，各自取属性块两对值 (基础×加成)：
//   物理 v4+1012/+1026、魔法 v4+1068/+1082；再乘玩家攻击速度对偶项（+60/+74 与 +116/+130）
//   ÷ flt_9A05F4（物理）/ flt_9A060C（魔法）—— 运行时加载的平衡系数（研究 §11）；
// 尾乘 (v4+1306 或 +1334) × 0.01 + 1.0（技能/装备百分比加成）→ sub_433F60（PVP 平衡路由）
// —— 与 0x4D6450/0x4D33A0 同族构成"伤害流水线的属性供给侧"（研究 P14 九步的第 1 步）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4D62D0(void *this, int nArg2, int nArg3)
{
  int pThis_2A0; // esi
  double v5; // st7
  float v7; // [esp+8h] [ebp-8h]
  int v8; // [esp+8h] [ebp-8h]
  int v9; // [esp+Ch] [ebp-4h]
  float v10; // [esp+Ch] [ebp-4h]
  float v11; // [esp+18h] [ebp+8h]
  float v12; // [esp+18h] [ebp+8h]
  float v13; // [esp+1Ch] [ebp+Ch]
  int v14; // [esp+1Ch] [ebp+Ch]
  float v15; // [esp+1Ch] [ebp+Ch]
  int v16; // [esp+1Ch] [ebp+Ch]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, nArg3);
  v13 = 0.0;
  if ( nArg2 == 0 )
  {
    v9 = sub_41A5E0(pThis_2A0 + 1012);
    v7 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 1026));
    v14 = sub_41A5E0(pThis_2A0 + 60);
    v11 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 74));
    v15 = (double)(int)(uint64_t)((double)v9 * v7)
        * (sub_433F60(this, 3) * (double)(int)(uint64_t)((double)v14 * v11) / flt_9A05F4 + 1.0);
    v5 = (double)sub_41A5E0(pThis_2A0 + 1306);
LABEL_5:
    v13 = (v5 * 0.0099999998 + 1.0) * v15;
    return (uint64_t)(sub_433F60(this, 0) * v13);
  }
  if ( nArg2 == 1 )
  {
    v8 = sub_41A5E0(pThis_2A0 + 1068);
    v10 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 1082));
    v16 = sub_41A5E0(pThis_2A0 + 116);
    v12 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 130));
    v15 = (double)(int)(uint64_t)((double)v8 * v10)
        * (sub_433F60(this, 5) * (double)(int)(uint64_t)((double)v16 * v12) / flt_9A060C + 1.0);
    v5 = (double)sub_41A5E0(pThis_2A0 + 1334);
    goto LABEL_5;
  }
  return (uint64_t)(sub_433F60(this, 0) * v13);
}



// ------------------------------------------------------------
// 0x4D6450 sub_4D6450 —— ★ 减伤率与抗性取值（研究 §5.1 的"防御×(1−减伤)"项）
// 输出两路：*a2 = 有效伤害比（v11/v14 归一）、*a3 = 抗性项 v16。
// 物理(0)/魔法(1) 取属性块 (+1040/+1054，+1096/+1110) × (1 + +1320/+1348 × 0.01)；
// 抗性来自 +1152/+1194 × 0.01；场景 4/6（PVP/战场）抗性 ×2；分母下限 1.0 防除零。
// 与研究 §16"PVP/战场走查表"一致：本函数是 PVE/PVP 分离的另一处体现。
// ------------------------------------------------------------
float */*thiscall*/ sub_4D6450(void *this, float *pArg2, float *pArg3, int nArg4, int nArg5, int nArg6)
{
  int pThis_2A0; // edi
  double v8; // st7
  double v9; // st6
  int v10; // ecx
  double v11; // st7
  int v12; // eax
  double v13; // st6
  double v14; // st6
  float v16; // [esp+8h] [ebp-8h]
  int v17; // [esp+8h] [ebp-8h]
  int v18; // [esp+8h] [ebp-8h]
  float v19; // [esp+Ch] [ebp-4h]
  float v20; // [esp+Ch] [ebp-4h]
  float v21; // [esp+Ch] [ebp-4h]
  float v22; // [esp+28h] [ebp+18h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, nArg6);
  v19 = 0.0;
  v16 = 0.0;
  v22 = 0.0;
  if ( nArg5 == 0 )
  {
    v17 = sub_41A5E0(pThis_2A0 + 1040);
    v20 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 1054));
    v8 = (double)sub_41A5E0(pThis_2A0 + 1320) * 0.0099999998 + 1.0;
    v9 = (double)(int)(uint64_t)((double)v17 * v20);
    v22 = flt_9A05FC;
    v10 = pThis_2A0 + 1152;
LABEL_5:
    v19 = v8 * v9;
    v16 = COERCE_FLOAT(sub_41A5E0(v10)) * 0.0099999998;
    goto LABEL_6;
  }
  if ( nArg5 == 1 )
  {
    v18 = sub_41A5E0(pThis_2A0 + 1096);
    v21 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 1110));
    v8 = (double)sub_41A5E0(pThis_2A0 + 1348) * 0.0099999998 + 1.0;
    v9 = (double)(int)(uint64_t)((double)v18 * v21);
    v22 = flt_9A0614;
    v10 = pThis_2A0 + 1194;
    goto LABEL_5;
  }
LABEL_6:
  v11 = sub_433F60(this, 1) * v19;
  v12 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v12 == 4 || v12 == 6 )
    v13 = v22 + v22;
  else
    v13 = v22;
  v14 = v13 * (double)nArg4 + v11;
  if ( v14 <= 1.0 )
    v14 = 1.0;
  *pArg2 = v11 / v14;
  *pArg3 = v16;
  return pArg3;
}



// ------------------------------------------------------------
// 0x4D65C0 sub_4D65C0 —— 攻速/施放速度取值（带技能对象修正分支）
// this+1625 != 0（存在技能对象）时多减一项 vt+176 技能容器 (+686 × 0.001)；
// 属性对 = (+844, +858) —— 研究 §12 的 [attack speed] a1+380/384 属另一种聚合路径
// 【待验证：+844/+858 是速度还是其它乘率，需 0x5A0 数据对象布局对读】。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4D65C0(uint32_t **this, int nArg2)
{
  int v3; // eax
  int v4; // eax
  int fld_e1625; // eax
  int v7; // esi
  int v8; // [esp+8h] [ebp-8h]
  float v9; // [esp+Ch] [ebp-4h]
  int v10; // [esp+18h] [ebp+8h]

  if ( nArg2 != 0 && *(this + 1625) != nullptr )
  {
    v3 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[168])(this, nArg2);
    v8 = sub_41A5E0(v3 + 844);
    v4 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[168])(this, nArg2);
    v9 = COERCE_FLOAT(sub_41A5E0(v4 + 858));
    fld_e1625 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1625) + 176))(*(this + 1625));
    return (uint64_t)((v9 - (double)sub_41A5E0(fld_e1625 + 686) * 0.001) * (double)v8);
  }
  else
  {
    v7 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[168])(this, nArg2);
    v10 = sub_41A5E0(v7 + 844);
    return (uint64_t)((double)v10 * COERCE_FLOAT(sub_41A5E0(v7 + 858)));
  }
}



// ------------------------------------------------------------
// 0x4D6690 sub_4D6690 —— ★ 硬直强度 vt+704（研究 第 27 轮定案：sub_4D6690）
// [stuck resistance] 扣除点：容器 (+466 × +690 × 0.1)。
// 529（濒死/石化类）且攻击定义 +12 != 0 时拒绝扣除（非魔法类跳过）；
// 攻击者 vt+368 浮空位 → 加 +280，否则加 +284 —— 研究 §14 的"浮空分支 +280/+284"。
// 消费者 = 硬直掷（三角级数连击加成 n(n+1)/2−1、PVP 缩放 ×(sub_4E4610/10000)）。
// 调用点：命中主处理器 / 表现壳的硬直时长计算链。
// ------------------------------------------------------------
double /*thiscall*/ sub_4D6690(void *this, int nArg2)
{
  int pThis_2A0; // edi
  int v5; // [esp+Ch] [ebp-4h]
  float v6; // [esp+Ch] [ebp-4h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
  v5 = sub_41A5E0(pThis_2A0 + 466);
  v6 = (double)(int)(uint64_t)((double)v5 * COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 690))) * 0.1;
  if ( (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 40))(this, 529) == 0
    || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0 )
  {
    return v6;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 368))(nArg2) != 0 )
    return (double)*(int *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1032))(this) + 280) + v6;
  return (double)*(int *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1032))(this) + 284) + v6;
}



// ------------------------------------------------------------
// 0x4D6750 sub_4D6750 —— 状态施加"概率/抗性"掷（rand%10000 < 率×100）
// 结构 = 研究 §5.1 的判定掷同构：v9 由 sub_41A5E0（防篡读）取；受方条件 17（有血）
// 时从属性对 (+284/+508，14 字节步距) 扣抵抗；a4 非空时用 sub_4D33A0（LCG）替代 rand。
// 调用点：状态附加（命中携带异常状态，研究 §3 attackinfo+24..48）与霸体/受击门。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4D6750(void *this, int nArg2, float fArg3, unsigned int *pDwArg4)
{
  int v5; // esi
  int pThis_2A0; // esi
  int nRand; // eax
  int v9; // [esp+14h] [ebp+8h]

  v5 = sub_496F80(nArg2);
  if ( v5 != 16 )
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3) + 14 * v5;
    v9 = sub_41A5E0(pThis_2A0 + 284);
    fArg3 = (100.0 - (double)(int)(uint64_t)((double)v9 * COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 508)))) * fArg3 * 0.0099999998;
  }
  if ( pDwArg4 != nullptr )
  {
    nRand = sub_4D33A0(pDwArg4);
  }
  else
  {
    sub_432FA0();
    nRand = rand();
  }
  return fArg3 * 100.0 > (double)(nRand % 10000);
}



// ------------------------------------------------------------
// 0x4D6810 sub_4D6810 —— ★ CNChangeHp 构造（研究 §2⑦ 的"延滞伤"分支）
// 命中主处理器 0x4D71B0 判 attackinfo+124 == 2（burn/延滞伤）时 new 本对象
// （伤害值, 1000ms, …）—— 研究 §2⑦ 已定案"new CNChangeHp(伤害, 1000ms, …)"；
// 本体 = sub_4B1030 基类 + CNChangeHp::vftable + sub_5FD600/5FD630 参数装载。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4D6810(uint8_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  sub_4B1030(this);
  *(uint32_t *)this = &CNChangeHp::`vftable';
  sub_5FD600(this);
  sub_5FD630(this, nArg2, nArg3, nArg4, nArg5);
  return this;
}



// ------------------------------------------------------------
// 0x4D6880 sub_4D6880
// ------------------------------------------------------------
void */*thiscall*/ sub_4D6880(void *Block, char pszArg2)
{
  sub_4D68B0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4D68B0 sub_4D68B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D68B0(uint32_t *this)
{
  int result; // eax

  *this = &CNChangeHp::`vftable';
  sub_5FDC90();
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4D6910 sub_4D6910 —— ★ 状态施加通用壳（a2=状态id, a3=强度, a4/a5=参数, a6=强制位）
// 门：a6 != 0 或 vt+308（本地玩家对象）；a2 != 17（17 = 无状态哨兵，研究 §10 枚举
// "17=none"）；a4 != 0（参数非零）→ sub_4D6750(状态id, 强度, 0) 概率掷通过后
// 调 vt+764(this, 状态id, a4, a5, a6) —— 与 0x4D4AE0（三连调 vt+764 施加异常状态）
// 同一转发目标。调用点：0x4DCC60（技能/被动施加，带 1943==3 时强度×0.1 的 PVP 修正）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D6910(void *this, int nArg2, float fArg3, int nArg4, int nArg5, int nArg6)
{
  char result; // al

  result = nArg6;
  if ( ((uint8_t)nArg6 != 0 || (result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this)) != 0)
    && nArg2 != 17
    && nArg4 != 0 )
  {
    result = sub_4D6750(nArg2, fArg3, 0);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(void *, int, int, int, int))(*(uint32_t *)this + 764))(this, nArg2, nArg4, nArg5, nArg6);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D6970 sub_4D6970 —— ★ 角色出生/复活初始化（尾调 0x4E73B0 复活重置）
// 首调 sub_4E73B0（研究 第 31 轮 P35：出生/复活重置 —— 全状态归零 + 双盒使能）
// → +6664 冻结/无敌位（+324 非零时 0，否则 0xFFFFFA24 = −1500【待验证：−1500ms 哨兵】）
// → +6588 记时钟、+6596/+6592 清零、vt+848(0) 清冻结标志、vt+212 播音效(5000ms)、
//   +6672/+6680/+6682/+6684/+6688/+6692 复位、vt+472(0,0,1,1)、
//   +6172/6176/6180 任一为 0 → 清 +6740、vt+932、+7105/+7112/+7108 复位 → sub_49FD20。
// 与研究 §1.2 字段表（+6744 冻结标志 vt+848 write；+6692 格挡时刻戳）呼应。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D6970(int this)
{
  int pThis_40; // eax
  int v3; // edx
  int pThis_1A3C; // eax
  int v5; // eax
  int fld_70; // ecx

  sub_4E73B0((int *)this);
  *(uint32_t *)(this + 6664) = *(uint32_t *)(this + 324) != 0 ? 0 : 0xFFFFFA24;
  sub_6569D0(this + 6540);
  pThis_40 = sub_699000(this + 64);  // 【clock_now(clk)】
  v3 = *(uint32_t *)this;
  *(uint32_t *)(this + 6588) = pThis_40;
  *(uint32_t *)(this + 6596) = 0;
  *(uint32_t *)(this + 6592) = 0;
  (*(void (/*thiscall*/ **)(int, uint32_t))(v3 + 848))(this, 0);
  if ( *(uint32_t *)(this + 6736) < 0x10u )
    pThis_1A3C = this + 6716;
  else
    pThis_1A3C = *(uint32_t *)(this + 6716);
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int))(*(uint32_t *)this + 212))(this, pThis_1A3C, 0, 0, 5000);
  v5 = *(uint32_t *)this;
  *(uint32_t *)(this + 6672) = 0;
  *(uint8_t *)(this + 6680) = 0;
  *(uint8_t *)(this + 6682) = 0;
  *(uint32_t *)(this + 6684) = 0;
  *(uint32_t *)(this + 6688) = -1;
  *(uint32_t *)(this + 6692) = -1;
  (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(v5 + 472))(this, 0, 0, 1, 1);
  if ( *(uint32_t *)(this + 6172) == 0 || *(uint32_t *)(this + 6176) == 0 || *(uint32_t *)(this + 6180) == 0 )
    *(uint8_t *)(this + 6740) = 0;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 932))(this);
  fld_70 = *(uint32_t *)(this + 112);
  *(uint8_t *)(this + 7105) = 0;
  *(uint32_t *)(this + 7112) = 0;
  *(uint32_t *)(this + 7108) = -1;
  return sub_49FD20(fld_70);
}



// ------------------------------------------------------------
// 0x4D6A80 sub_4D6A80 —— ★ 多命中盒碰撞测试 vt+480（研究 §1.2/§11 定案）
// 主盒：sub_4E62B0(this, this+120 动画对象, 目标, 目标 vt+200, a3) —— 研究 P29 的
//   "攻击盒=动画+116/受击盒=动画+132，24B/盒"族（会话 3 定案的 0x4E62B0 调用方）。
// 附加盒：动画对象 +204 双向链表（研究 §1.2 "主盒 + this+120+204 附加盒链表逐盒
//   sub_4E62B0"）—— 逐节点取 v9[3] 作盒对象再测。
// 任一命中即返回 1。调用者 = 本地扫掠 sub_4E82B0（vt+476，研究 §1.2/§11 第 11 轮）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D6A80(uint32_t *this, int nArg2, int nArg3)
{
  int v5; // eax
  int fld_e30; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // edi
  int v10; // eax
  int fld_e302; // [esp+10h] [ebp+8h]

  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 200))(nArg2);
  if ( (uint8_t)sub_4E62B0(this, *(this + 30), nArg2, v5, nArg3) != 0 )  // 【攻击盒 vs 受击盒碰撞（研究 P29 盒模型，会话 3 交叉引用）】
    return 1;
  fld_e30 = *(this + 30);
  fld_e302 = fld_e30;
  if ( fld_e30 == 0 )
    return 0;
  v8 = *(uint32_t **)(fld_e30 + 204);
  v9 = (uint32_t *)*v8;
  if ( (uint32_t *)*v8 == v8 )
    return 0;
  while ( 1 )
  {
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 200))(nArg2);
    if ( (uint8_t)sub_4E62B0(this, v9[3], nArg2, v10, nArg3) != 0 )  // 【攻击盒 vs 受击盒碰撞（研究 P29 盒模型，会话 3 交叉引用）】
      break;
    v9 = (uint32_t *)*v9;
    if ( v9 == *(uint32_t **)(fld_e302 + 204) )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x4D6B10 sub_4D6B10 —— 观察者/状态的对象绑定与解绑（a2 = 0/1/2）
//   a2 == 0：18 观察者 ->vt+132(this+510) 广播 + 遍历 this+332 数组 ->vt+836 逐个绑定
//             + 尾调 vt+676(this, 1)
//   a2 == 1：17 状态槽（vt+24 检查）->vt+48(this+851) + 尾调 vt+676(this, 2)
//   a2 == 2：从 +851 与 +1192 解除；若剩余硬直 vt+736 > vt+740 则强制归位
//            （vt+732 写值）—— 与受击硬直"延长"语义同源（研究 §4.2 退出 stuck 链）。
// 与 0x4D5700/0x4D51C0 同族（状态/观察者生命周期），0x4D6E40（对象移除）为对偶。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D6B10(uint32_t *this, int nArg2)
{
  int result; // eax
  uint32_t *pThis_651; // edi
  unsigned int k; // edi
  int fld_e83; // ecx
  uint32_t *pThis_615; // edi
  int v8; // edi
  int v9; // edi
  int v10; // eax
  int v11; // edi
  int v12; // edi
  int v13; // eax
  int j; // [esp+14h] [ebp+8h]
  int i; // [esp+14h] [ebp+8h]

  result = nArg2;
  if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 )
    {
      sub_4A2480(this + 510);  // 【怪物属性块大拷贝（vmt29C）】
      pThis_615 = this + 1557;
      for ( i = 17; i != 0; --i )
      {
        if ( *pThis_615 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)*pThis_615 + 24))() != 0 )
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t *))(*(uint32_t *)*pThis_615 + 48))(*pThis_615, this + 851);
        ++pThis_615;
      }
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 676))(this, 2);
    }
    else if ( nArg2 == 2 )
    {
      sub_4A2480(this + 851);  // 【怪物属性块大拷贝（vmt29C）】
      sub_53F820(this + 1192);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this);
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) > v8 )
      {
        v9 = *this;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 736))(this, 0, 1);
        (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 732))(this, v10);
      }
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 756))(this);
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 752))(this);
      if ( result > v11 )
      {
        v12 = *this;
        v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 752))(this, 1);
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(v12 + 748))(this, v13);
      }
    }
  }
  else
  {
    sub_4A2480(this + 169);  // 【怪物属性块大拷贝（vmt29C）】
    pThis_651 = this + 1617;
    for ( j = 18; j != 0; --j )
    {
      if ( *pThis_651 != 0 )
        (*(void (/*stdcall*/ **)(uint32_t *))(*(uint32_t *)*pThis_651 + 132))(this + 510);
      ++pThis_651;
    }
    for ( k = 0; ; ++k )
    {
      fld_e83 = *(this + 83);
      if ( fld_e83 == 0 || k >= (*(this + 84) - fld_e83) >> 2 )
        break;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t *))(*this + 836))(this, *(uint32_t *)(fld_e83 + 4 * k), this + 510);
    }
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 676))(this, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D6CA0 sub_4D6CA0 —— ★ 50% 预表现门（研究 §2① / §8 定案）
// 命中前置"花式点缀"：this+7076 容器（v2=this+1769 的 vector）非空 且 长度>0 且
// vt+308（本地玩家对象）成立 且 **rand()%10 >= 5**（50% 门）时，容器内每个对象
// ->vt+60() 触发一次 + sub_49FFC0(1, 0)。
// 双调用点：命中主处理器 0x4D71B0 ①（受方侧）与攻方完整反应 0x4D6D90（攻方侧）。
// 研究 §2① 记"受 vt+308 门控——受击'花式'点缀的随机性来源"。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D6CA0(uint32_t *this)
{
  int fld_e1769; // ecx
  unsigned int i; // edi
  int fld_e17692; // ecx

  fld_e1769 = *(this + 1769);
  if ( fld_e1769 != 0
    && (*(this + 1770) - fld_e1769) >> 2 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && rand() % 10 >= 5 )
  {
    for ( i = 0; ; ++i )
    {
      fld_e17692 = *(this + 1769);
      if ( fld_e17692 == 0 || i >= (*(this + 1770) - fld_e17692) >> 2 )
        break;
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(fld_e17692 + 4 * i) + 60))(*(uint32_t *)(fld_e17692 + 4 * i));
      sub_49FFC0(1, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x4D6D20 sub_4D6D20
// ------------------------------------------------------------
void /*thiscall*/ sub_4D6D20(uint32_t *this, int nArg2)
{
  unsigned int i; // edi
  int fld_e1769; // ecx

  for ( i = 0; ; ++i )
  {
    fld_e1769 = *(this + 1769);
    if ( fld_e1769 == 0 || i >= (*(this + 1770) - fld_e1769) >> 2 )
      break;
    if ( nArg2 == *(uint32_t *)(fld_e1769 + 4 * i) )
    {
      memcpy_0(
        (void *)(*(this + 1769) + 4 * i),
        (const void *)(*(this + 1769) + 4 * i + 4),
        4 * ((int)(*(this + 1770) - (*(this + 1769) + 4 * i + 4)) >> 2));
      *(this + 1770) -= 4;
    }
  }
}



// ------------------------------------------------------------
// 0x4D6D90 sub_4D6D90 —— ★★ 攻方完整反应 vt+500（六回调第 3 号，研究 20 §8 定案）
// this = 攻击者，a2 = 受击者，a3 = 命中盒，a4 = 格挡/暴击位。
// 流程与反编译体逐条对上研究 §1.1/§8 定案表：
//   ① 18 观察者 ->vt+136(观察者, 受, 盒, a4, **flag=1**, this+388)
//      —— 与 sub_4D4A20（flag=0 轻量版）成对的完整版
//   ② 17 自身状态槽：vt+776 查询激活 → 状态对象 ->vt+72(受, 盒, a4)（攻方状态回调）
//   ③ sub_4D6CA0(this) —— 50% 预表现门（攻方侧）
//   ④ a4 != 0 时 vt+548(this, a3) —— 格挡时刻戳（研究 §1.2：记录 this+64 时钟
//      当前时刻 → this+6692）
//   ⑤ 尾调 sub_4E4710(this, 受, 盒, a4) —— ★ 攻方表现载荷（双向卡肉入口，§8）
// 调用者 = 命中包 case 0x13 的分发器（研究 §1.1 六回调交替调用）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D6D90(int *this, uint32_t *uArg2, int nArg3, int nArg4)  // 【攻方完整反应 vt+500（§8 双向卡肉入口）】
{
  uint32_t *pThis_651; // edi
  int i; // ebx
  int v7; // ebx
  uint32_t *pThis_615; // edi

  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )
  {
    if ( *pThis_651 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, int, int, int, int *))(*(uint32_t *)*pThis_651 + 136))(
        *pThis_651,
        uArg2,
        nArg3,
        nArg4,
        1,
        this + 97);
    ++pThis_651;
  }
  v7 = 0;
  pThis_615 = this + 1557;
  do
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 776))(this, v7) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, int, int))(*(uint32_t *)*pThis_615 + 72))(*pThis_615, uArg2, nArg3, nArg4);
    ++v7;
    ++pThis_615;
  }
  while ( v7 < 17 );
  sub_4D6CA0(this);
  if ( (uint8_t)nArg4 != 0 )
    (*(void (/*thiscall*/ **)(int *, int))(*this + 548))(this, nArg3);
  return sub_4E4710(this, uArg2, nArg3, nArg4);  // 【攻方表现载荷（ 双向卡肉，研究 §8 全文定案）】
}



// ------------------------------------------------------------
// 0x4D6E40 sub_4D6E40
// ------------------------------------------------------------
int /*thiscall*/ sub_4D6E40(uint32_t *this, int nArg2)
{
  int pObj; // ebx
  uint32_t *pThis_615; // edi
  uint8_t *v5; // eax
  int v6; // ecx
  int i; // [esp+8h] [ebp-4h]

  pObj = nArg2;
  sub_4E7480(nArg2);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 33) != 0 )
    sub_4D6D20(this, nArg2);
  pThis_615 = this + 1557;
  for ( i = 17; i != 0; --i )
  {
    if ( *pThis_615 != 0
      && (*(uint8_t (**)(void))(*(uint32_t *)*pThis_615 + 24))() != 0
      && (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_615 + 20))(*pThis_615) == nArg2 )
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*pThis_615 + 16))(*pThis_615, 0);
    }
    ++pThis_615;
  }
  if ( (uint32_t *)nArg2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 1);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 2);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 4);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 5);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 6);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 7);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 8);
    if ( *(uint32_t **)(*((uint32_t *)dword_8F8528 + 4) + 736) == this )
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) == 0 )
      {
        v5 = *((uint8_t **)dword_8F8528 + 4);
        if ( v5[856] != 1 )
        {
          v5[856] = 1;
          v5[873] = 0;
          v5[874] = 0;
          sub_698F90((int)(v5 + 860), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        }
      }
      v6 = *((uint32_t *)dword_8F8528 + 4);
      if ( *(uint8_t *)(v6 + 856) != 0 )
        *(uint32_t *)(v6 + 736) = 0;
      else
        sub_4684F0(v6, nullptr);
    }
    pObj = nArg2;
  }
  return sub_53F8A0(pObj);
}



// ------------------------------------------------------------
// 0x4D6FA0 sub_4D6FA0
// ------------------------------------------------------------
void /*thiscall*/ sub_4D6FA0(int this)
{
  sub_53FD50();
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x4D7000 sub_4D7000 —— ★ ActiveObject 析构（研究 20 §13 定案）
// 17 状态槽逐个 ->vt+0(对象, 1) 销毁（this+1557 起）+ 槽指针清零；
// this+1574 的辅助对象 → sub_4D6FA0（转发 sub_53FD50）+ free；
// 18 观察者槽逐个 ->vt+4(观察者, 1) 引用计数释放（this+1617 起）+ 清零。
// 研究 §13："观察者是引用计数组件" —— 此处 vt+4 释放即其据。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D7000(uint32_t *this)
{
  uint32_t *pThis_615; // esi
  int i; // ebx
  void *fld_e1574; // esi
  uint32_t *pThis_651; // esi
  int j; // edi

  pThis_615 = this + 1557;
  for ( i = 17; i != 0; --i )
  {
    if ( *pThis_615 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_615)(*pThis_615, 1);
    *pThis_615++ = 0;
  }
  fld_e1574 = (void *)*(this + 1574);
  if ( fld_e1574 != nullptr )
  {
    sub_4D6FA0(*(this + 1574));
    j__free(fld_e1574);
  }
  *(this + 1574) = 0;
  pThis_651 = this + 1617;
  for ( j = 18; j != 0; --j )
  {
    if ( *pThis_651 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*pThis_651 + 4))(*pThis_651, 1);
    *pThis_651++ = 0;
  }
}



// ------------------------------------------------------------
// 0x4D7080 sub_4D7080
// ------------------------------------------------------------
void /*noreturn*/ sub_4D7080()
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4D70F0 sub_4D70F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4D70F0(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  nullsub_3(this);
  sub_540270(this);
  return this;
}



// ------------------------------------------------------------
// 0x4D7140 sub_4D7140
// ------------------------------------------------------------
int /*thiscall*/ sub_4D7140(int this)
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  int result; // eax

  pMem = operator new(0x10u);
  if ( pMem != nullptr )
    v3 = sub_4D70F0(pMem);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 6296) = v3;
  result = *(uint32_t *)(this + 112);
  *(uint32_t *)(result + 200) = 500;
  *(uint8_t *)(this + 6740) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x4D71B0 sub_4D71B0 —— ★★★ 命中主处理器 / hit_main_handler vt+512
// （研究 20 §2 全文定案；~94 张子类虚表在此槽覆写为 0x58Bxxx 家族，§1.2/§14#4）
//
// 签名：__thiscall(this=受击者, a2=攻击者, a3=命中盒, a4=格挡/无伤害标志)
// 反编译体逐段对应研究 §2 编号流程（头部注释已按 ①..⑩ 对齐）：
//   ① sub_4D6CA0(this)          50% 预表现门（rand%10>=5；受 vt+308 门控）
//   ② 18 观察者 ->vt+140(…, flag=1)   受方命中通知（完整版）
//   ③ sub_4E5DC0(this, 攻, 盒, a4)    ★ 表现壳 —— hit stop 施加点（研究 §3）
//   ④ HIBYTE(a2) = sub_4E5B50(this, 攻)  ★ 暴击/有效命中判定（研究 §5.1）
//   ⑤ a4 != 0 → vt+552(this, 盒) 后收尾（格挡/无伤害路径，§1.2 +552）
//   ⑥ 伤害计算：vt+648(类型) → vt+628(伤害流水线 sub_4E6770，研究 P14 九步)
//      暴击分支：HIBYTE(a2) = sub_4E5B50(this, 攻) 的返回值；其成立
//      **且** 受击者车主（受->vt+576）非空 **且** 车主条件 273（受击态）成立时，
//      转写体 `v14 += v48 * 0.25` —— 即伤害**追加 25%**。
//      ⚠ 与研究 §5.1 第 14 轮更正的关系（**差异标注**）：
//      研究写"早期 ×1.25 系推断错误，实测 ×1.5 在 sub_4E6770 尾段"——
//      实测本文件 0x4E6770 尾段确有 `v59 = a7 * 1.5; *a2 = 1;`（暴击 ×1.5，
//      掷法 `sub_4D33A0 %10000 < 暴击率×100`），**且** 0x4D71B0 此处另有
//      一个**条件追加 +25%**（门 = 暴击位 && 受击者车主存在 && 车主受击态）。
//      两者并存不矛盾：×1.5 是通用暴击倍率，本处 +25% 是"打在被受击的宿主所辖
//      对象上"的额外加成【待验证：该门的游戏语义（协助/守护目标？），L2 无法定论】。
//   ⑦ 伤害落地：attackinfo+124 == 2 → new CNChangeHp(sub_4D6810, 延滞 1000ms)
//      否则 vt+728(this, 新HP, 0, 攻) = HP setter 0x4D4D40（DLL 锚点 [13]）
//   ⑧ 受击反应三档（state 3 硬直动作 / 4 击退 / 5 击倒）→ vt+560 = sub_4E7A80
//      优先级门 this+636（研究 §1.2/§15：只升不降仲裁）
//   ⑨ 17 异常状态观察者 ->vt+76（激活的才通知）
//   ⑩ 收尾 vt+544 → 0x4D49E0 → sub_426820(a2=3) 播报层 HK_ATTACKED
//
// 关键字段：+30(word)=动画对象、+161(word)=当前帧、+642/644=碰撞盒快照、
//           +200 主状态、+204 硬直时长、+520 攻方卡肉时长（§8）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D71B0(unsigned int *this, float fArg2, int nArg3, int nArg4)  // 【命中主处理器 vt+512（§2 全文定案）】
{
  int pObj; // edi
  uint32_t *pThis_651; // ebx
  char nArg42; // bl
  int fld_e30; // ebx
  unsigned int fld_e161; // ebx
  int v10; // edx
  unsigned int v11; // edx
  int v12; // eax
  unsigned int v13; // edx
  int v14; // ebx
  int pObj2; // eax
  int *v16; // eax
  int v17; // edx
  int pThis_5FD; // eax
  int v19; // ebx
  bool v20; // cc
  int v21; // ebx
  int v22; // eax
  bool v23; // sf
  bool v24; // of
  char *pThis_69C; // eax
  int fld_e1689; // eax
  int v27; // eax
  int v28; // edx
  int v29; // ebx
  int v30; // eax
  uint32_t *pThis_615; // ebx
  int v32; // eax
  int v33; // ebx
  float v35; // [esp+38h] [ebp-60h]
  char v36[4]; // [esp+54h] [ebp-44h] BYREF
  void *Block; // [esp+58h] [ebp-40h]
  int v38; // [esp+5Ch] [ebp-3Ch]
  int v39; // [esp+60h] [ebp-38h]
  void *pMem; // [esp+64h] [ebp-34h]
  int v41; // [esp+68h] [ebp-30h] BYREF
  int v42; // [esp+6Ch] [ebp-2Ch] BYREF
  int v43; // [esp+70h] [ebp-28h] BYREF
  int v44; // [esp+74h] [ebp-24h] BYREF
  int i; // [esp+78h] [ebp-20h] BYREF
  int fld_e16892; // [esp+7Ch] [ebp-1Ch] BYREF
  int fld_e1612; // [esp+80h] [ebp-18h]
  int v48; // [esp+84h] [ebp-14h]
  int v49; // [esp+88h] [ebp-10h]
  int v50; // [esp+94h] [ebp-4h]

  sub_4D6CA0(this);
  pObj = LODWORD(fArg2);
  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )
  {
    if ( *pThis_651 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int))(*(uint32_t *)*pThis_651 + 140))(*pThis_651, pObj, nArg3, nArg4, 1);
    ++pThis_651;
  }
  nArg42 = nArg4;
  sub_4E5DC0(pObj, nArg3, nArg4);  // 【表现壳（hit stop 施加点，研究 §3 全文定案）】
  v48 = 0;
  HIBYTE(fArg2) = sub_4E5B50((int)this, pObj);
  if ( nArg42 != 0 )
  {
    (*(void (/*thiscall*/ **)(unsigned int *, int))(*this + 552))(this, nArg3);
    goto LABEL_101;
  }
  v49 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj);
  if ( (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 308))(this) == 0 || (fld_e30 = *(this + 30)) == 0 )
  {
    v48 = -1;
    goto LABEL_101;
  }
  if ( *((uint8_t *)this + 642) != 0 )
  {
    fld_e161 = *(this + 161);
  }
  else
  {
    if ( *(uint32_t *)(fld_e30 + 148) == -1 )
      sub_4938F0(*(this + 30));
    fld_e161 = *(uint32_t *)(fld_e30 + 112);
  }
  v10 = *(uint32_t *)(v49 + 60);
  fld_e1612 = fld_e161;
  fld_e16892 = v10;
  if ( fld_e161 <= 1 )
  {
    (*(void (/*thiscall*/ **)(unsigned int *, int))(*this + 964))(this, pObj);
    v11 = *this;
    LOBYTE(v42) = 0;
    v44 = 100;
    v43 = 0;
    v12 = (*(int (/*thiscall*/ **)(unsigned int *, int *, int))(v11 + 648))(this, &v44, pObj);
    v13 = *this;
    v41 = v12;
    v14 = (*(int (/*thiscall*/ **)(unsigned int *, int *, int *, int, int, int, uint32_t))(v13 + 628))(
            this,
            &v42,
            &v43,
            v44,
            pObj,
            nArg3,
            0);
    v48 = v14;
    if ( HIBYTE(fArg2) != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 576))(pObj) != 0 )
    {
      pObj2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 576))(pObj);
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) != 0 )
      {
        v14 += (uint64_t)((double)v48 * 0.25);
        v48 = v14;
        if ( fld_e16892 == 1 )
          fld_e16892 = 2;
        sub_424AB0(500, 50);
      }
    }
    if ( v14 >= (*(int (/*thiscall*/ **)(unsigned int *))(*this + 736))(this) )
      i = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 736))(this);
    else
      i = v14;
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj) + 124) == 2 )
    {
      pMem = operator new(0x80u);
      v50 = 0;
      if ( pMem != nullptr )
      {
        v41 = -i;
        v35 = (float)-i;
        v16 = (int *)sub_4D6810(LODWORD(v35), 1000, 0, 1);
      }
      else
      {
        v16 = nullptr;
      }
      v17 = *v16;
      v50 = -1;
      (*(void (/*thiscall*/ **)(int *, unsigned int *, int, uint32_t, uint32_t, uint32_t, int))(v17 + 56))(
        v16,
        this,
        pObj,
        0,
        0,
        0,
        -1);
    }
    else
    {
      pThis_5FD = sub_41A5E0(this + 1533);
      (*(void (/*thiscall*/ **)(unsigned int *, int, uint32_t, int))(*this + 728))(this, pThis_5FD - v14, 0, pObj);
      *(this + 1650) = -1;
      if ( v14 != 0 || *(uint8_t *)(v49 + 16) != 0 || *(float *)v49 > 0.0 )
        sub_4D5330(pObj, this, nArg3, v14, i, v42, v43, v41);
      if ( fld_e1612 != 2 && (v41 == 1 || v41 == 2) )
        fld_e1612 = 1;
    }
  }
  i = 0;
  v41 = 0;
  if ( fld_e16892 == 0 )
    goto LABEL_101;
  if ( (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 724))(this) != 0 )
  {
    if ( *(this + 1639) == 5 || *(this + 154) == 5 )
      goto LABEL_101;
    if ( (*(uint8_t (/*thiscall*/ **)(unsigned int *, int))(*this + 40))(this, 273) != 0 )
    {
      v19 = 4;
    }
    else
    {
      if ( (*(uint8_t (/*thiscall*/ **)(unsigned int *, int))(*this + 40))(this, 529) == 0 )
        goto LABEL_101;
      if ( *(uint32_t *)(dword_8F7A24 + 244) == 2 )
      {
        v19 = 4;
      }
      else if ( ((*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 936))(this) != 0 || *(this + 1639) == 9)
             && (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 1020))(this) == 0
             || *(this + 1545) == 0 )
      {
        v20 = *(uint32_t *)(v49 + 64) < 150;
        v19 = 5;
        v42 = 5;
        if ( v20 )
        {
          i = *(uint32_t *)(v49 + 68) < 400 ? 2 : 5;
        }
        else
        {
          v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
          v22 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 120))(this);
          v24 = __OFSUB__(v21, v22);
          v23 = v21 - v22 < 0;
          v19 = v42;
          i = (v23 ^ v24) + 3;
        }
      }
      else
      {
        v19 = 4;
      }
    }
    goto LABEL_67;
  }
  if ( fld_e1612 != 0
    || (*(uint8_t (/*thiscall*/ **)(unsigned int *, int))(*this + 776))(this, 1) != 0
    || (*(uint8_t (/*thiscall*/ **)(unsigned int *, int))(*this + 776))(this, 7) != 0 )
  {
    goto LABEL_101;
  }
  if ( fld_e16892 == 1 )
  {
    if ( ((*(int (/*thiscall*/ **)(unsigned int *))(*this + 436))(this) > 0
       || (*(int (/*thiscall*/ **)(unsigned int *))(*this + 128))(this) <= 0)
      && *(this + 1639) != 4 )
    {
      v19 = 3;
      goto LABEL_67;
    }
  }
  else if ( fld_e16892 != 2 )
  {
    goto LABEL_101;
  }
  v19 = 4;
  if ( *(this + 1545) != 0 )
  {
    if ( *(this + 1639) == 4 && (int)*(this + 1708) >= 1 )
      v41 = 1;
  }
  else
  {
    v19 = 3;
  }
LABEL_67:
  if ( *((uint8_t *)this + 612) != 0 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj) + 124) == 2 )
      rand();
    if ( *(this + 1697) < 0x10 )
      pThis_69C = (char *)(this + 1692);
    else
      pThis_69C = (char *)*(this + 1692);
    (*(void (/*thiscall*/ **)(unsigned int *, char *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_69C, -1, 0, 0);
  }
  switch ( v19 )
  {
    case 3:
      if ( *(this + 1544) != 0 )
      {
        if ( *(this + 1543) != 0 )
        {
          if ( *(this + 1639) == 3 )
            fld_e1689 = 1 - *(this + 1689);
          else
            fld_e1689 = rand() % 2;
          fld_e16892 = fld_e1689;
        }
        else
        {
          fld_e16892 = 1;
        }
      }
      else
      {
        fld_e16892 = 0;
      }
      fArg2 = *(float *)(v49 + 136);
      if ( fArg2 == -1.0 )
        fArg2 = 1.0;
      if ( *(uint32_t *)(v49 + 12) == 1 )
        fArg2 = fArg2 * 0.69999999;
      Block = nullptr;
      v38 = 0;
      v39 = 0;
      v27 = *(uint32_t *)pObj;
      v50 = 1;
      v41 = (*(int (/*thiscall*/ **)(int, unsigned int *))(v27 + 660))(pObj, this);
      sub_431230(&v41);
      if ( *(uint8_t *)(v49 + 81) != 0 )
        fArg2 = NAN;
      else
        LODWORD(fArg2) = (uint64_t)(fArg2 * 100.0);
      sub_431230(&fArg2);
      sub_431230(&fld_e16892);
      fArg2 = *(float *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj) + 124);
      sub_431230(&fArg2);
      (*(void (/*thiscall*/ **)(unsigned int *, int, char *, int, uint32_t))(*this + 560))(this, 3, v36, 2, 0);
      v50 = -1;
      if ( Block != nullptr )
LABEL_91:
        j__free(Block);
      break;
    case 4:
      Block = nullptr;
      v38 = 0;
      v39 = 0;
      v28 = *(uint32_t *)pObj;
      v50 = 2;
      v42 = (*(int (/*thiscall*/ **)(int, unsigned int *))(v28 + 660))(pObj, this);
      sub_431230(&v42);
      sub_431230(&v41);
      v41 = 1;
      sub_431230(&v41);
      v29 = v49;
      sub_431230(v49 + 64);
      v30 = 0;
      if ( HIBYTE(fArg2) != 0 )
        v30 = *(uint32_t *)(v29 + 60) != 1 ? 50 : 250;
      LODWORD(fArg2) = v30 + *(uint32_t *)(v29 + 68);
      sub_431230(&fArg2);
      (*(void (/*thiscall*/ **)(unsigned int *, int, char *, int, uint32_t))(*this + 560))(this, 4, v36, 2, 0);
      v50 = -1;
      if ( Block != nullptr )
        goto LABEL_91;
      break;
    case 5:
      Block = nullptr;
      v38 = 0;
      v39 = 0;
      v50 = 3;
      sub_431230(&i);
      (*(void (/*thiscall*/ **)(unsigned int *, int, char *, int, uint32_t))(*this + 560))(this, 5, v36, 2, 0);
      v50 = -1;
      sub_5E5260(v36);
      break;
    default:
      break;
  }
LABEL_101:
  fArg2 = 0.0;
  pThis_615 = this + 1557;
  do
  {
    if ( (*(uint8_t (/*thiscall*/ **)(unsigned int *, float))(*this + 776))(this, COERCE_FLOAT(LODWORD(fArg2))) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*pThis_615 + 76))(*pThis_615, pObj, nArg3, nArg4);
    ++pThis_615;
    ++LODWORD(fArg2);
  }
  while ( SLODWORD(fArg2) < 17 );
  v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj);
  if ( *(uint8_t *)(v32 + 16) == 0 && *(float *)v32 <= 0.0 )
    return v48;
  v33 = v48;
  (*(void (/*thiscall*/ **)(unsigned int *, int, int))(*this + 544))(this, pObj, v48);
  return v33;
}


// ============================================================
// 【分区 4】飘字 / 表现层物件族（0x4D7960 起）
//   0x4D7960 飘字咽喉（研究 §1.1 case 0x14 + 第 34/39 轮 P39 全套）
//   0x4D7C60 吟唱条/进度渲染（EndofCasting.ani 分支）
//   0x4D7F30 伪装态切换（Camouflage/Decamouflage.ani + CAMOUFLAGE_* 音效标签）
//   0x4D8170 附魔解除（Disenchanted.ani，按体型+40 算缩放）
//   0x4D82D0/0x4D83E0/0x4D84F0/0x4D8600 头顶气泡（Command/Exclamation/
//     CommandReceive/Question.ani —— 指令/惊讶/接收/疑问四种）
// ============================================================

// ------------------------------------------------------------
// 0x4D7960 sub_4D7960 —— ★★★ 飘字咽喉（研究 20 §1.1 case 0x14；第 34/39 轮 P39 全套）
// 调用链：战斗分发器 case 0x14「伤害表现包」→ 本函数（值/类型/是否玩家受击，
//         坐标 = 盒中心 +50 z）。
// 反编译体与研究 P39 定案的对应：
//   • sprintf("%d", abs32(a7)) 把伤害值转串，**逐位**取字形（v10 = 位数）
//   • 字体基址 v29：默认 44（伤害类型分表：44/64/74/54 —— 研究 P39
//     "伤害类型分表 44/64/74/54"，与 a8==2→64、a8==3→74、a8==4||a9→54 逐条吻合）
//   • a10 == 1（暴击位）→ v29 = 143 **暴击专用字体基址 143**（研究 P39 定案）
//   • a8 == 4 → 字形缩放 1067030938 = **1.4f**（研究 P39 "类型4 放大 1.4f"）
//   • v13 = (5 - 5*位数 + 总宽)/-2 = 整串居中偏移
//   • v15 循环 = **5 槽幽灵叠层**：case 1/2/3/4 分别设 (v17+48) = 200/100/100/0 延迟、
//     (v17+16) = 宽度/-2 的水平偏移、(v17+36) = 1 半透明标志、
//     (v17+32) = -2130706433 = 0x80FFFFFF 的半透明色 —— 研究 P39
//     "5 槽幽灵叠层（y−15/−30 梯次半透明残影）"
//   • 逐层 sub_4924C0(层号) 建字形对象 → sub_45FE80 入演播层 2（池化，P39）
// ------------------------------------------------------------
int /*usercall*/ sub_4D7960@<eax>(
        int a1@<ebx>,
        int a2@<edi>,
        int a3@<esi>,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        char a9,
        char a10)
{
  int v10; // kr04_4
  int v11; // edi
  int i; // esi
  int v13; // ebx
  int result; // eax
  int v15; // esi
  int v16; // edi
  int v17; // ecx
  int v18; // eax
  int v19; // edx
  int v20; // esi
  int v21; // edx
  bool v22; // cc
  int v26; // [esp+4h] [ebp-64h]
  int v27; // [esp+10h] [ebp-58h]
  int v28; // [esp+10h] [ebp-58h]
  int v29; // [esp+14h] [ebp-54h]
  char Buffer[64]; // [esp+18h] [ebp-50h] BYREF
  int v31; // [esp+58h] [ebp-10h]
  int v32; // [esp+64h] [ebp-4h]
  int v33; // [esp+88h] [ebp+20h]

  v31 = dword_796E50;
  sprintf(Buffer, "%d", abs32(a7));
  v10 = strlen(Buffer);
  v29 = 44;
  if ( a8 == 2 )
  {
    v29 = 64;
  }
  else if ( a8 == 3 )
  {
    v29 = 74;
  }
  else if ( a8 == 4 || a9 != 0 )
  {
    v29 = 54;
  }
  if ( a10 == 1 )
    v29 = 143;
  v11 = 0;
  for ( i = 0; i < v10; ++i )
    v11 += *(uint32_t *)(sub_418DD0(Buffer[i] + v29 - 48) + 20);
  v13 = (5 - 5 * v10 + v11) / -2;
  v26 = *(uint32_t *)((*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 120))(
                      dword_8F8520,
                      a2,
                      a3,
                      a1)
                  + 104);
  result = v10;
  v15 = 0;
  v33 = 0;
  if ( v10 <= 0 )
    return result;
  while ( 2 )
  {
    v16 = sub_418DD0(Buffer[v33] + v29 - 48);
    v27 = sub_42FCB0(228);
    v32 = 0;
    if ( v27 != 0 )
      v28 = sub_4B59A0(5);
    else
      v28 = 0;
    v32 = -1;
    do
    {
      v17 = sub_4924C0(v15);
      *(uint32_t *)v17 = v16;
      *(uint32_t *)(v17 + 12) = v13;
      if ( a8 == 4 )
      {
        *(uint32_t *)(v17 + 20) = 1067030938;
        *(uint32_t *)(v17 + 24) = 1067030938;
      }
      if ( v15 != 0 )
      {
        switch ( v15 )
        {
          case 1:
            *(uint32_t *)(v17 + 48) = 200;
            *(uint32_t *)(v17 + 16) = *(uint32_t *)(v16 + 24) / -2;
            goto LABEL_36;
          case 2:
            *(uint32_t *)(v17 + 48) = 100;
            *(uint32_t *)(v17 + 16) = *(uint32_t *)(v16 + 24) / -2;
            *(uint8_t *)(v17 + 36) = 1;
            goto LABEL_36;
          case 3:
            *(uint32_t *)(v17 + 48) = 100;
            v18 = *(uint32_t *)(v16 + 24) - (*(int *)(v16 + 24) >> 31);
            v19 = -15;
            *(uint8_t *)(v17 + 36) = 1;
            *(uint32_t *)(v17 + 32) = -2130706433;
            break;
          case 4:
            *(uint32_t *)(v17 + 48) = 0;
            v18 = *(uint32_t *)(v16 + 24) - (*(int *)(v16 + 24) >> 31);
            v19 = -30;
            *(uint32_t *)(v17 + 32) = 0xFFFFFF;
            break;
          default:
            goto LABEL_36;
        }
        *(uint32_t *)(v17 + 16) = v19 - (v18 >> 1);
      }
      else
      {
        *(uint32_t *)(v17 + 48) = 100;
        *(uint32_t *)(v17 + 16) = *(uint32_t *)(v16 + 24) / -2;
        if ( a8 != 4 )
        {
          *(uint32_t *)(v17 + 20) = 0x40000000;
          *(uint32_t *)(v17 + 24) = 0x40000000;
        }
        *(uint8_t *)(v17 + 36) = 1;
        if ( a8 == 1 || a8 == 4 )
        {
          *(uint32_t *)(v17 + 40) = 5;
          *(uint32_t *)(v17 + 44) = -1;
        }
      }
LABEL_36:
      ++v15;
    }
    while ( v15 < 5 );
    v20 = sub_44B6C0(284);
    v32 = 1;
    if ( v20 != 0 )
    {
      sub_44E0D0(v28, 1);
      *(uint32_t *)v20 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v20 = 0;
    }
    v21 = *(uint32_t *)v20;
    v32 = -1;
    (*(void (/*thiscall*/ **)(int, int))(v21 + 72))(v20, 2);
    sub_45FE80(v26, v16, 2, 0, v20, 0, 0);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v20 + 112))(v20, a4, a5, a6);
    result = v33 + 1;
    v22 = v33 + 1 < v10;
    v13 = v13 + *(uint32_t *)(v16 + 20) - 5;
    ++v33;
    if ( v22 )
    {
      v15 = 0;
      continue;
    }
    return result;
  }
}


// ------------------------------------------------------------
// 0x4D7C60 sub_4D7C60 —— 吟唱进度/收尾表现（研究 §7 图"技能演出"族）
// vt+1000（吟唱中）为真时：vt+1012 进度 < 50 → 进度条三段绘制（sub_45E490 算 x −25；
//   sub_45E4D0 算 y；sub_424980 画填充；dword_99FCC8 资源族索引 0/1/2/3 = 四段贴图）
// 否则（完成）→ 播放 "Common/Etc/Animation/EndofCasting.ani" 池化对象 + sub_4A06D0(v10, 2)。
// 与技能区 0x5E-0x64 的吟唱逻辑配套（研究 §4.3 技能自带定格族）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D7C60(int *this)  // 【吟唱条/进度渲染（EndofCasting.ani 分支）】
{
  int v2; // ebx
  char *v3; // eax
  int pObj; // edi
  int v5; // ebx
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // edi
  int v13; // eax
  int v14; // ebx
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // [esp-14h] [ebp-28h]
  int v21; // [esp-10h] [ebp-24h]
  int v22; // [esp-Ch] [ebp-20h]
  int v23; // [esp+4h] [ebp-10h]
  int pObj2; // [esp+4h] [ebp-10h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1000))(this) != 0 )
  {
    v23 = (*(int (/*thiscall*/ **)(int *))(*this + 1012))(this);
    if ( v23 < 50 )
    {
      (*(void (/*thiscall*/ **)(int *))(*this + 80))(this);
      v22 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 36))(this) + 8);
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      v12 = sub_45E490(v11, v22) - 25;
      (*(void (/*thiscall*/ **)(int *))(*this + 80))(this);
      v21 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 36))(this) + 8);
      v20 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v13 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
      v14 = sub_45E4D0(v13, v20, v21, 1.0);
      v15 = -10 - (*(int (/*thiscall*/ **)(int *))(*this + 192))(this) + v14;
      v16 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 148), 0);
      sub_424760(dword_79C0B0, v12 - 1, v15 - 1, v16, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      v17 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 148), 2u);
      sub_424760(dword_79C0B0, v12 - 4, v15 - 3, v17, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      sub_424980(dword_79C0B0, v12, 0, v12 + v23, 480);
      v18 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 148), 1u);
      sub_424760(dword_79C0B0, v12, v15, v18, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      sub_488670((uint32_t *)dword_79C0B0);
      v19 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 148), 3u);
      sub_424760(dword_79C0B0, v12 + v23, v15, v19, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
    }
    else
    {
      v2 = 0;
      if ( sub_42FCB0(228) != 0 )
        v2 = sub_431860((char)"Common/Etc/Animation/EndofCasting.ani", 1);
      v3 = (char *)sub_44B6C0(284);
      pObj = (int)v3;
      if ( v3 != nullptr )
      {
        sub_44E0D0(v3, v2, 1);
        *(uint32_t *)pObj = &CNRDPooledObject::`vftable';
      }
      else
      {
        pObj = 0;
      }
      pObj2 = pObj;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 72))(pObj);
      sub_45FE80(*(this + 29), pObj, 2, 0, pObj, (int)this, 0);
      v5 = *(uint32_t *)pObj;
      v6 = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v6 + v7 + 10);
      v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8 + 1);
      (*(void (/*thiscall*/ **)(int, int))(v5 + 112))(pObj2, v9);
      v10 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj2 + 60))(pObj2, this);
      sub_4A06D0(v10, 2);
      (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);
    }
  }
}



// ------------------------------------------------------------
// 0x4D7F30 sub_4D7F30 —— 伪装/隐身影身切换（a2 = 1 进入 / 0 退出）
// 进入：Camouflage.ani 池化 + this+7096 起三段计时（vt+1777 = 起始时刻，
//       vt+1778 = 结束时刻 = 当前 + a3）→ 广播音效标签 "CAMOUFLAGE_DISAPPEAR"
// 退出：Decamouflage.ani 池化 + vt+1777 复位、vt+1778 = 0
//       → 广播 "CAMOUFLAGE_APPEAR"
// 消费点 = 0x4D54E0（按 vt+940 门逐帧做 alpha 255→0 线性淡出，
//   并用 sub_491F80 把动画对象整体染色/透明化，研究 §5/§33 的帧绘制桥）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D7F30(int *this, char pszArg2, int nArg3)  // 【伪装态切换（Camouflage/Decamouflage.ani + CAMOUF…】
{
  int fld_e29; // eax
  int v5; // ebx
  char *v6; // eax
  int pObj; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v14; // ebx
  char *v15; // eax
  int pObj2; // edi
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  char pThis_1BC1; // [esp+Fh] [ebp-Dh]

  pThis_1BC1 = *((uint8_t *)this + 7105);
  *((uint8_t *)this + 7105) = pszArg2;
  fld_e29 = *(this + 29);
  if ( pszArg2 != 0 )
  {
    v5 = 0;
    if ( fld_e29 != 0 )
    {
      if ( sub_42FCB0(228) != 0 )
        v5 = sub_431860((char)"Common/CommonEffect/Animation/Camouflage.ani", 1);
      v6 = (char *)sub_44B6C0(284);
      pObj = (int)v6;
      if ( v6 != nullptr )
      {
        sub_44E0D0(v6, v5, 1);
        *(uint32_t *)pObj = &CNRDPooledObject::`vftable';
      }
      else
      {
        v7 = 0;
      }
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 72))(v7);
      sub_45FE80(*(this + 29), v7, 2, 0, v7, (int)this, 0);
      v8 = *(uint32_t *)v7;
      v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v9);
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v10);
      (*(void (/*thiscall*/ **)(int, int))(v8 + 112))(v7, v11);
      v12 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)v7 + 60))(v7, this);
      sub_4A06D0(v12, 2);
    }
    if ( v22 != 1 )
      *(this + 1777) = sub_699000((int)(this + 9));
    *(this + 1778) = a3 + sub_699000((int)(this + 9));
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "CAMOUFLAGE_DISAPPEAR",
             -1,
             0,
             0);
  }
  else
  {
    if ( v4 != 0 )
    {
      if ( sub_42FCB0(228) != 0 )
        v14 = sub_431860((char)"Common/CommonEffect/Animation/Decamouflage.ani", 1);
      else
        v14 = 0;
      v15 = (char *)sub_44B6C0(284);
      v16 = (int)v15;
      if ( v15 != nullptr )
      {
        sub_44E0D0(v15, v14, 1);
        *(uint32_t *)v16 = &CNRDPooledObject::`vftable';
      }
      else
      {
        pObj2 = 0;
      }
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 72))(pObj2);
      sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, (int)this, 0);
      v17 = *(uint32_t *)pObj2;
      v18 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v18);
      v20 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v19);
      (*(void (/*thiscall*/ **)(int, int))(v17 + 112))(pObj2, v20);
      v21 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj2 + 60))(pObj2, this);
      sub_4A06D0(v21, 2);
    }
    *(this + 1777) = sub_699000((int)(this + 9));
    *(this + 1778) = 0;
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "CAMOUFLAGE_APPEAR",
             -1,
             0,
             0);
  }
}



// ------------------------------------------------------------
// 0x4D8170 sub_4D8170 —— 附魔解除表现（"Disenchanted.ani"）
// 缩放推导：v14 = 2×max(盒边界0, 边界1) × 0.014705882（= 1/68，恰为 2/136 的倒数）
//           v15 = (this+160 + 40) × 0.0078125（= 1/128）
// 随后 sub_4920E0(资源, v14, v15) —— **批量改写特效帧 IMAGE RATE**（研究 §5.2 定案：
// 该函数作用于特效帧数组 +20/+24，88 字节帧距）—— 与暴击火花 1.5 倍、燃烧状态
// 等比缩放共用同一原语（研究 §10 burn 分支、§5.2 暴击 1.5×）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D8170(int *this)  // 【附魔解除（Disenchanted.ani，按体型+40 算缩放）】
{
  int *fld_e1540; // ecx
  int *v3; // edi
  int v4; // ebx
  int v5; // eax
  uint32_t *v6; // ebx
  char *v7; // eax
  int pObj; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // [esp-Ch] [ebp-28h]
  float v14; // [esp+8h] [ebp-14h]
  float fld_e40; // [esp+Ch] [ebp-10h]

  if ( *(this + 29) != 0 )
  {
    fld_e1540 = (int *)*(this + 1540);
    v14 = 1.0;
    fld_e40 = 1.0;
    if ( fld_e1540 != nullptr )
    {
      v3 = (int *)sub_4924C0(fld_e1540, 0);
      v4 = sub_4918E0(v3, 0);
      v5 = sub_4918E0(v3, 1);
      if ( v4 > v5 )
        v5 = v4;
      v14 = (double)(2 * v5) * 0.014705882;
      fld_e40 = (double)(*(this + 40) + 40) * 0.0078125;
    }
    v6 = nullptr;
    if ( sub_42FCB0(228) != 0 )
      v6 = (uint32_t *)sub_431860((char)"Common/CommonEffect/Animation/Disenchanted.ani", 1);
    sub_4920E0(v6, v14, fld_e40);
    v7 = (char *)sub_44B6C0(284);
    pObj = (int)v7;
    if ( v7 != nullptr )
    {
      sub_44E0D0(v7, (int)v6, 1);
      *(uint32_t *)pObj = &CNRDPooledObject::`vftable';
    }
    else
    {
      pObj = 0;
    }
    sub_45FE80(*(this + 29), pObj, 2, 0, pObj, 0, 0);
    v9 = *(uint32_t *)pObj;
    v13 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v10 + 1);
    (*(void (/*thiscall*/ **)(int, int))(v9 + 112))(pObj, v11);
    v12 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);
    sub_4A06D0(v12, v13);
  }
}



// ============================================================
// 【分区 5】头顶表情气泡四件套（Command / Exclamation / CommandReceive / Question）
//   四者结构完全同构（仅 .ani 资源名与定位微调不同），全部 = 池化对象 + 演播层 2 入队
//   + sub_4A06D0(对象, 2)。定位用 vt+340（动画帧 +40 偏移）与 vt+192/128/124/120 取坐标。
//   0x4D82D0 = Command.ani（指令）；0x4D83E0 = Exclamation.ani（!）
//   0x4D84F0 = CommandReceive.ani（接收）；0x4D8600 = Question.ani（?）
// ============================================================

// ------------------------------------------------------------
// 0x4D82D0 sub_4D82D0 —— 头顶气泡 "Command.ani"（a2/a3 = 定位偏移）
// ------------------------------------------------------------
void /*thiscall*/ sub_4D82D0(int *this, int nArg2, int nArg3)
{
  int v4; // ebx
  char *v5; // eax
  int pObj2; // edi
  int v7; // ebx
  int v8; // edi
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int pObj; // [esp+Ch] [ebp-10h]

  v4 = 0;
  if ( sub_42FCB0(228) != 0 )
    v4 = sub_431860((char)"Common/CommonEffect/Animation/Command.ani", 1);
  v5 = (char *)sub_44B6C0(284);
  pObj2 = (int)v5;
  if ( v5 != nullptr )
  {
    sub_44E0D0(v5, v4, 1);
    *(uint32_t *)pObj2 = &CNRDPooledObject::`vftable';
  }
  else
  {
    pObj2 = 0;
  }
  pObj = pObj2;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 72))(pObj2);
  sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, (int)this, 0);
  v7 = *(uint32_t *)pObj2;
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v10 = nArg3 - *(uint32_t *)((*(int (/*thiscall*/ **)(int *, int))(*this + 340))(this, v9 + v8) + 40);
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11 + v10);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 112))(pObj, nArg2 + v12);
  v13 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);
  sub_4A06D0(v13, 2);
}



// ------------------------------------------------------------
// 0x4D83E0 sub_4D83E0 —— 头顶气泡 "Exclamation.ani"（惊叹；同 0x4D82D0 结构）
// ------------------------------------------------------------
void /*thiscall*/ sub_4D83E0(int *this, int nArg2, int nArg3)
{
  int v4; // ebx
  char *v5; // eax
  int pObj2; // edi
  int v7; // ebx
  int v8; // edi
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int pObj; // [esp+Ch] [ebp-10h]

  v4 = 0;
  if ( sub_42FCB0(228) != 0 )
    v4 = sub_431860((char)"Common/CommonEffect/Animation/Exclamation.ani", 1);
  v5 = (char *)sub_44B6C0(284);
  pObj2 = (int)v5;
  if ( v5 != nullptr )
  {
    sub_44E0D0(v5, v4, 1);
    *(uint32_t *)pObj2 = &CNRDPooledObject::`vftable';
  }
  else
  {
    pObj2 = 0;
  }
  pObj = pObj2;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 72))(pObj2);
  sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, (int)this, 0);
  v7 = *(uint32_t *)pObj2;
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v10 = nArg3 - *(uint32_t *)((*(int (/*thiscall*/ **)(int *, int))(*this + 340))(this, v9 + v8) + 40);
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11 + v10);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 112))(pObj, nArg2 + v12);
  v13 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);
  sub_4A06D0(v13, 2);
}



// ------------------------------------------------------------
// 0x4D84F0 sub_4D84F0 —— 头顶气泡 "CommandReceive.ani"（同 0x4D82D0 结构）
// ------------------------------------------------------------
void /*thiscall*/ sub_4D84F0(int *this, int nArg2, int nArg3)
{
  int v4; // ebx
  char *v5; // eax
  int pObj2; // edi
  int v7; // ebx
  int v8; // edi
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int pObj; // [esp+Ch] [ebp-10h]

  v4 = 0;
  if ( sub_42FCB0(228) != 0 )
    v4 = sub_431860((char)"Common/CommonEffect/Animation/CommandReceive.ani", 1);
  v5 = (char *)sub_44B6C0(284);
  pObj2 = (int)v5;
  if ( v5 != nullptr )
  {
    sub_44E0D0(v5, v4, 1);
    *(uint32_t *)pObj2 = &CNRDPooledObject::`vftable';
  }
  else
  {
    pObj2 = 0;
  }
  pObj = pObj2;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 72))(pObj2);
  sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, (int)this, 0);
  v7 = *(uint32_t *)pObj2;
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v10 = nArg3 - *(uint32_t *)((*(int (/*thiscall*/ **)(int *, int))(*this + 340))(this, v9 + v8) + 40);
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11 + v10);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 112))(pObj, nArg2 + v12);
  v13 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);
  sub_4A06D0(v13, 2);
}



// ------------------------------------------------------------
// 0x4D8600 sub_4D8600 —— 头顶气泡 "Question.ani"（疑问；结构同上但少一层坐标补偿）
// 被 0x4D8A80 调用：位置 1000ms 未变且大状态 == 0 时进入"发呆"表现并切大状态 21。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D8600(int *this, int nArg2, int nArg3)
{
  int v4; // ebx
  char *v5; // eax
  int pObj2; // edi
  int v7; // ebx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int pObj; // [esp+Ch] [ebp-10h]

  v4 = 0;
  if ( sub_42FCB0(228) != 0 )
    v4 = sub_431860((char)"Common/CommonEffect/Animation/Question.ani", 1);
  v5 = (char *)sub_44B6C0(284);
  pObj2 = (int)v5;
  if ( v5 != nullptr )
  {
    sub_44E0D0(v5, v4, 1);
    *(uint32_t *)pObj2 = &CNRDPooledObject::`vftable';
  }
  else
  {
    pObj2 = 0;
  }
  pObj = pObj2;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 72))(pObj2);
  sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, (int)this, 0);
  v7 = *(uint32_t *)pObj2;
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v9 + v8);
  v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nArg3 + v10);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 112))(pObj, nArg2 + v11);
  v12 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);
  sub_4A06D0(v12, 2);
}



// ------------------------------------------------------------
// 0x4D8700 sub_4D8700
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8700(void *this, int nArg2)
{
  int v3; // esi
  int v4; // edx

  v3 = sub_41A5E0((unsigned int)this) - nArg2;
  sub_41A590((unsigned int)this, v4, v3);
  return v3;
}



// ------------------------------------------------------------
// 0x4D8730 sub_4D8730
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8730(uint32_t *this)
{
  int result; // eax

  result = sub_699000((int)(this + 16));  // 【clock_now(clk)】
  *(this + 1673) = result;
  return result;
}



// ============================================================
// 【分区 6】怪物/角色 AI 与状态机族（0x4D8DF0 起）
// 研究第 31 轮 P35 定案：无敌开关 = this+641 受击盒使能（setter sub_4A2D70 →
// 附属物广播 vt+604）；全库 30+ 调用点三类（战斗核心/58xxx 怪物 AI/反应族）。
// 研究第 15 轮：三层状态 = this+200 主状态 / this+616 反应态+636 优先级 /
// this+6556 大状态（本区 vt+1104 = 大状态 setter 大量出现）。
// ============================================================

// ------------------------------------------------------------
// 0x4D8750 sub_4D8750 —— 朝向决策（依据参照对象 vt+1813 的 x 比较得方向码 0/4）
// 与 0x4D8DF0（y 轴/朝向更新）配对；结果经 vt+148 与 vt+144 写入朝向族。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8750(int *this)
{
  int fld_e1813; // edi
  int v3; // ebx
  int v4; // eax
  bool v5; // sf
  bool v6; // of
  int result; // eax
  int v8; // ecx
  int v9; // edi

  (*(void (/*thiscall*/ **)(int *))(*this + 184))(this);
  fld_e1813 = *(this + 1813);
  v3 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813);
  v6 = __OFSUB__(v3, v4);
  v5 = v3 - v4 < 0;
  result = *(this + 1639);
  v8 = v5 ^ v6;
  v9 = v8;
  if ( result == 0 && v8 != 4 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, v8);
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 144))(this, v9);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D87B0 sub_4D87B0
// ------------------------------------------------------------
void /*thiscall*/ sub_4D87B0(int *this, int nArg2, int nArg3)
{
  int fld_e28; // ebx
  int fld_e282; // edi
  int v6; // eax
  int fld_e283; // eax
  int fld_e284; // ecx
  int v9; // eax
  int fld_e285; // ecx
  int *pThis_81B; // ebx
  int fld_e286; // eax
  int fld_e287; // ecx
  int v14; // eax
  int fld_e288; // ecx
  int i; // edi
  char v17; // [esp+4h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && *(this + 50) == 0
    && (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 776))(this, 16) == 0 )
  {
    v17 = 1;
    if ( nArg2 == 4 || nArg3 == 4 )
      v17 = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t, int, char))(*this + 892))(this, 0, nArg2, v17);
    (*(void (/*thiscall*/ **)(int *, int, int, char))(*this + 892))(this, 1, nArg3, v17);
    fld_e28 = sub_4A0650(*(this + 28), 0) / 16;
    fld_e282 = sub_4A0650(*(this + 28), 1) / 12;
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 436))(this);
    if ( sub_58AD30(fld_e28, fld_e282, v6 > 0) == 1 )
    {
      fld_e283 = sub_4A0650(*(this + 28), 0);
      fld_e284 = *(this + 28);
      *(this + 2075) = fld_e283;
      v9 = sub_4A0650(fld_e284, 1);
      fld_e285 = *(this + 28);
      *(this + 2076) = v9;
      *(this + 2077) = sub_4A0650(fld_e285, 2);
    }
    else
    {
      pThis_81B = this + 2075;
      if ( *(this + 2075) == -1 && *(this + 2076) == -1 && *(this + 2077) == -1 )
      {
        fld_e286 = sub_4A0650(*(this + 28), 0);
        fld_e287 = *(this + 28);
        *pThis_81B = fld_e286;
        v14 = sub_4A0650(fld_e287, 1);
        fld_e288 = *(this + 28);
        *(this + 2076) = v14;
        *(this + 2077) = sub_4A0650(fld_e288, 2);
      }
      for ( i = 0; i < 3; ++i )
        sub_498B00((float *)*(this + 28), i, *pThis_81B++);
    }
  }
}



// ------------------------------------------------------------
// 0x4D8920 sub_4D8920
// ------------------------------------------------------------
int /*stdcall*/ sub_4D8920(int nArg1, int nArg2, int nArg3, int nArg4)
{
  sub_53FC10(nArg1, nArg2, nArg3, nArg4);
  return 0;
}



// ------------------------------------------------------------
// 0x4D8950 sub_4D8950 —— ★ 技能活动帧 tick 主入口（本区最核心的逐帧驱动）
// 门：vt+308（本地玩家对象）且 vt+724（可行动/非无敌）通过才走。
// 六段（依次）：
//   ① 目标失效三判 → vt+1236（取消/打断）：参照对象 vt+1813 空且时钟超 +1816+1000ms；
//      或参照对象 vt+45E680 判定失败；或参照对象 vt+1244 门失败；或 +1881 超时
//   ② 时钟 − +1922 > 333ms（≈3 帧节流）→ 当前反应态 vt+1639 不在 {3,4,8,9,5}
//      才 vt+1092（注释：333 = 1000/3 的典型帧节流常量，原值保留）
//   ③ 超过 +1818（动作结束时刻）→ vt+1240（收招）
//   ④ vt+1228（相位更新）
//   ⑤ 尾调 vt+1224（帧推进）
// 与研究 §11 帧时间引擎（P30）对应：+1818 = 帧尾累积时刻，vt+1240 = 出帧。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8950(uint32_t *this)
{
  int result; // eax
  int fld_e1639; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 724))(this);
    if ( (uint8_t)result == 0 )
    {
      if ( *(this + 1813) == 0 && sub_699000((int)(this + 1910)) >= *(this + 1816) + 1000  // 【clock_now(clk)】
        || *(this + 1813) != 0 && (uint8_t)sub_45E680(*(this + 1813)) == 0
        || *(this + 1813) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1244))(this, *(this + 1813)) == 0
        || *(this + 1881) != 0 && sub_699000((int)(this + 1910)) >= *(this + 1881) + *(this + 1816) )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1236))(this);
      }
      if ( sub_699000((int)(this + 1910)) - *(this + 1922) > 333 )  // 【clock_now(clk)】
      {
        fld_e1639 = *(this + 1639);
        if ( fld_e1639 != 3 && fld_e1639 != 4 && fld_e1639 != 8 && fld_e1639 != 9 && fld_e1639 != 5 )
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1092))(this);
        *(this + 1922) = sub_699000((int)(this + 1910));
      }
      if ( sub_699000((int)(this + 1910)) > *(this + 1818) )  // 【clock_now(clk)】
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1240))(this);
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1228))(this);
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1224))(this);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D8A80 sub_4D8A80
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8A80(int *this)
{
  int result; // eax
  int v3; // edi

  result = (*(int (/*thiscall*/ **)(int *, int))(*this + 776))(this, 16);
  if ( (uint8_t)result == 0 )
  {
    if ( *(this + 1928) != (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) )
    {
      *(this + 1928) = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      *(this + 1927) = sub_699000((int)(this + 1910));
    }
    if ( *(this + 1929) != (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) )
    {
      *(this + 1929) = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
      *(this + 1927) = sub_699000((int)(this + 1910));
    }
    if ( *(this + 1930) != (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) )
    {
      *(this + 1930) = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      *(this + 1927) = sub_699000((int)(this + 1910));
    }
    v3 = (*(int (/*thiscall*/ **)(int *))(*this + 688))(this);
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) == *(uint32_t *)(v3 + 4) )
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
      if ( result == 0 )
      {
        result = sub_699000((int)(this + 1910)) - *(this + 1927);  // 【clock_now(clk)】
        if ( result > 1000 )
        {
          sub_4D8600(this, 0, 0);
          (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 21);
          result = sub_699000((int)(this + 1910));  // 【clock_now(clk)】
          *(this + 1927) = result;
        }
      }
    }
    else
    {
      result = sub_699000((int)(this + 1910));  // 【clock_now(clk)】
      *(this + 1927) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D8BB0 sub_4D8BB0
// ------------------------------------------------------------
char /*thiscall*/ sub_4D8BB0(uint32_t *this, int nArg2)
{
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, nArg2) == 0 || *(this + 1813) == nArg2 )
    return 0;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1152))(this, nArg2);
  return 1;
}



// ------------------------------------------------------------
// 0x4D8BF0 sub_4D8BF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8BF0(void *this)
{
  int result; // eax
  int v3; // edi
  int pThis_30; // eax
  int v5; // edi
  int pThis_34; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 7, 1);
    v3 = *(uint32_t *)dword_8F8520;
    pThis_30 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);
    (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, pThis_30);
    v5 = *(uint32_t *)dword_8F8520;
    pThis_34 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
    (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, pThis_34);
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1084))(this);
    return (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0, -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D8C60 sub_4D8C60
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8C60(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int pThis_776; // eax
  int fld_e1787; // edx
  int fld_e1818; // ecx
  int fld_e1919; // eax
  int fld_e1918; // ecx
  int fld_e1920; // eax
  int fld_e1921; // edx
  uint32_t v12[6]; // [esp+8h] [ebp-18h] BYREF

  v2 = *(uint32_t *)dword_8F8520;
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
  (*(void (/*thiscall*/ **)(int, int))(v2 + 36))(dword_8F8520, v3);
  pThis_776 = sub_699000((int)(this + 1910));  // 【clock_now(clk)】
  fld_e1787 = *(this + 1787);
  fld_e1818 = *(this + 1818) - pThis_776;
  fld_e1919 = *(this + 1919);
  v12[0] = fld_e1818;
  fld_e1918 = *(this + 1918);
  v12[2] = fld_e1919;
  fld_e1920 = *(this + 1920);
  v12[1] = fld_e1787;
  fld_e1921 = *(this + 1921);
  v12[3] = fld_e1918;
  v12[5] = fld_e1920;
  v12[4] = fld_e1921;
  return (*(int (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v12, 24);
}



// ------------------------------------------------------------
// 0x4D8CE0 sub_4D8CE0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8CE0(uint32_t *this)
{
  int result; // eax
  int fld_e1815; // ecx
  int pThis_776; // eax
  uint32_t v5[6]; // [esp+4h] [ebp-1Ch] BYREF
  uint16_t v6; // [esp+1Ch] [ebp-4h] BYREF

  result = (*(int (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v6);
  fld_e1815 = *(this + 1815);
  if ( fld_e1815 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1815 + 52))(fld_e1815);
    if ( result == v6 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, v5, 24);
      pThis_776 = sub_699000((int)(this + 1910));  // 【clock_now(clk)】
      result = v5[0] + pThis_776;
      *(this + 1818) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D8D40 sub_4D8D40
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8D40(int *this)
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // edi
  int fld_e1813; // eax
  int fld_e18132; // ecx
  int v10; // esi
  int v11; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = *(this + 1813);
    if ( result != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 32, 1);
      v3 = *(uint32_t *)dword_8F8520;
      v4 = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);
      (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, v4);
      v5 = *(uint32_t *)dword_8F8520;
      v6 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
      (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, v6);
      v7 = *(uint32_t *)dword_8F8520;
      fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 48))(*(this + 1813));
      (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, fld_e1813);
      fld_e18132 = *(this + 1813);
      v10 = *(uint32_t *)dword_8F8520;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 52))(fld_e18132);
      (*(void (/*thiscall*/ **)(int, int))(v10 + 36))(dword_8F8520, v11);
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D8DF0 sub_4D8DF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8DF0(uint32_t *this, int nArg2, char pszArg3, int nArg4)
{
  int result; // eax
  int pObj; // eax
  int v7; // esi
  int *i; // ecx
  int v9; // ebx
  int v10; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 724))(this);
    if ( (uint8_t)result == 0 )
    {
      result = sub_4D4D40(this, nArg4, (int)this, nArg2, pszArg3, nArg4);  // 【HP setter vt+728（§1.1；DLL 锚点 [13]）】
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 724))(this);
        if ( (uint8_t)result != 0 && nArg4 != 0 )
        {
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 576))(nArg4);
          if ( result != 0 )
          {
            pObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 576))(nArg4);
            result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273);
            if ( (uint8_t)result != 0 )
            {
              v7 = 0;
              for ( i = (int *)(dword_8F850C + 16); ; ++i )
              {
                result = *i;
                if ( *i != 0 && *(uint32_t *)(result + 196) == nArg4 )
                  break;
                if ( ++v7 >= 4 )
                  return result;
              }
              (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 24, 0);
              v9 = *(uint32_t *)dword_8F8520;
              v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 936))(this);
              LOBYTE(v10) = (uint8_t)v10 != 0;
              (*(void (/*thiscall*/ **)(int, int))(v9 + 32))(dword_8F8520, v10);
              return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, v7);
            }
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D8F00 sub_4D8F00
// ------------------------------------------------------------
char /*thiscall*/ sub_4D8F00(uint32_t *this, int nArg2)
{
  int pThis_2; // eax
  int fld_e1815; // ecx
  int nArg22; // eax
  int v6; // eax
  int v7; // edi
  int v8; // esi
  uint32_t *v9; // eax
  int v10; // eax

  pThis_2 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
  fld_e1815 = *(this + 1815);
  *(this + 1917) = pThis_2 + 2000;
  nArg22 = nArg2;
  if ( nArg2 != fld_e1815 )
  {
    if ( nArg2 == dword_8F7C04 && nArg2 != 0 )
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 60))(this);
      qmemcpy((void *)(v6 + 53), (const void *)(v6 + 4), 0x31u);
      v8 = v6 + 53;
      v7 = v6 + 102;
      v9 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 60))(this);
      sub_49FFC0(v9, v7, v8, 1, 0);
      nArg22 = nArg2;
    }
    *(this + 1815) = nArg22;
    LOBYTE(nArg22) = *((uint8_t *)this + 7776);
    if ( (uint8_t)nArg22 == 0 )
    {
      v10 = *this;
      *((uint8_t *)this + 7776) = 1;
      LOBYTE(nArg22) = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 1116))(this);
    }
  }
  return nArg22;
}



// ------------------------------------------------------------
// 0x4D8F90 sub_4D8F90
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8F90(void *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  if ( (uint8_t)nArg2 == 0 )
    return sub_58E550(0, nArg3, nArg4, nArg5);  // 【IRDActiveObject__vmt144】
  sub_58E550(nArg2, nArg3, nArg4, nArg5);  // 【IRDActiveObject__vmt144】
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 1300))(this, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x4D8FE0 sub_4D8FE0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8FE0(uint32_t *this)
{
  bool v2; // zf
  int result; // eax

  v2 = (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 5) == 0;
  result = 10;
  if ( v2 )
    return *(this + 1880);
  return result;
}



// ------------------------------------------------------------
// 0x4D9000 sub_4D9000
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4D9000(uint32_t *this)
{
  int fld_e1787; // eax

  fld_e1787 = *(this + 1787);
  return fld_e1787 == 7 || fld_e1787 == 5 || fld_e1787 == 9 || fld_e1787 == 10 || fld_e1787 == 11 || fld_e1787 == 12 || fld_e1787 == 24 || fld_e1787 == 6;
}



// ------------------------------------------------------------
// 0x4D9040 sub_4D9040
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9040(uint32_t *this, int nArg2)
{
  int v3; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1096))(this, *(this + 1787));
  v3 = *this;
  *(this + 1787) = nArg2;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v3 + 1100))(this, nArg2);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 620))(this);
  if ( result != 1 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 620))(this);
    if ( result != 2 )
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1240))(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D90A0 sub_4D90A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D90A0(uint8_t *this, int *pDwArg2)
{
  int result; // eax

  switch ( *pDwArg2 )
  {
    case 4:
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1104))(this, 13);
      result = sub_4D5200(this, pDwArg2);
      break;
    case 5:
      if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) != 11 )
        goto LABEL_7;
      (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 12, 0, 1, 1);
      (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 0, 0, 1, 1);
      result = sub_4D5200(this, pDwArg2);
      break;
    case 8:
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1104))(this, 16);
      result = sub_4D5200(this, pDwArg2);
      break;
    case 9:
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1104))(this, 13);
      goto LABEL_7;
    default:
LABEL_7:
      result = sub_4D5200(this, pDwArg2);
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D9170 sub_4D9170
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9170(uint32_t *this, int nArg2)
{
  int result; // eax

  result = sub_4D6E40(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
  {
    result = dword_8F7A24;
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 64))(this);
      *(uint8_t *)(result + 40) = 0;
    }
  }
  if ( *(this + 1813) == nArg2 )
    *(this + 1813) = 0;
  if ( *(this + 1812) == nArg2 )
    *(this + 1812) = 0;
  if ( *(this + 1814) == nArg2 )
    *(this + 1814) = 0;
  if ( *(this + 1815) == nArg2 )
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1044))(this, 0);
  if ( *(this + 2088) == nArg2 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1164))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x4D9200 sub_4D9200
// ------------------------------------------------------------
BOOL /*stdcall*/ sub_4D9200(int nArg1)
{
  return sub_4D58E0(nArg1);
}



// ------------------------------------------------------------
// 0x4D9210 sub_4D9210
// ------------------------------------------------------------
bool /*thiscall*/ sub_4D9210(uint32_t *this, int nArg2, int nArg3, uint32_t *uArg4)
{
  uint32_t *fld_e28; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // edi
  int v10; // ebx
  int v11; // [esp+4h] [ebp-10h]
  int v12; // [esp+8h] [ebp-Ch]
  int v13; // [esp+Ch] [ebp-8h]
  char v14; // [esp+10h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 16) != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 5;
  v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 436))(this) > 0;
  if ( sub_58AD30(nArg2 / 16, nArg3 / 12, v14) == 0 )
    return false;
  if ( uArg4 != nullptr )
    *uArg4 = 0;
  if ( *(this + 29) != 0 )
  {
    fld_e28 = (uint32_t *)*(this + 28);
    v7 = *this;
    v11 = fld_e28[1];
    v12 = fld_e28[2];
    v13 = fld_e28[3];
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(v7 + 112))(this, nArg2, nArg3, v8);
    *(uint8_t *)(*(this + 28) + 108) = 0;
    v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 32);
    v10 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 36);
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 32) = 1;
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 36) = 1;
    *(uint32_t *)(*(this + 28) + 4) = v11;
    *(uint32_t *)(*(this + 28) + 8) = v12;
    *(uint32_t *)(*(this + 28) + 12) = v13;
    *(uint8_t *)(*(this + 28) + 108) = 1;
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 32) = v9;
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 36) = v10;
  }
  return true;
}



// ------------------------------------------------------------
// 0x4D9360 sub_4D9360
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9360(uint32_t *this)
{
  int result; // eax
  int fld_e1890; // ebx
  unsigned int v4; // edi
  int v5; // eax
  int v6; // edx

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 616))(this) == 0
    || (result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 620))(this)) != 1 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 612))(this, 1, 1);
    fld_e1890 = *(this + 1890);
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 466;
    v5 = sub_41A5E0(v4);
    sub_41A590(v4, v6, fld_e1890 + v5);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D93D0 sub_4D93D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D93D0(uint32_t *this)
{
  int result; // eax
  int fld_e1890; // ebx
  unsigned int v4; // edi
  int v5; // eax
  int v6; // edx

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 616))(this) == 1
    || (result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 620))(this)) == 1 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 612))(this, 0, 0);
    fld_e1890 = *(this + 1890);
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 466;
    v5 = sub_41A5E0(v4);
    sub_41A590(v4, v6, v5 - fld_e1890);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D9440 sub_4D9440
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9440(uint32_t *this)
{
  int result; // eax
  int nRand; // eax
  int v4; // et2
  int v5; // eax
  int v6; // [esp-18h] [ebp-1Ch]
  int v7; // [esp-10h] [ebp-14h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 && *(this + 1943) == 3 )
  {
    nRand = rand();
    v4 = nRand % 100;
    result = nRand / 100;
    if ( v4 < 30 )
    {
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      return sub_4E4A50(this, 30022, 0, v5, v6, 0, v7, 0, 0, 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D94A0 sub_4D94A0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4D94A0(int this, int pArg2, uint8_t *uArg3)
{
  char *pMem; // eax
  int fld_20A8; // eax
  uint8_t *result; // eax
  int fld_20A0; // edx

  if ( pArg2 != 0 )
  {
    if ( *(uint32_t *)(this + 8360) == 0 )
    {
      pMem = (char *)operator new(7u);
      if ( pMem != nullptr )
      {
        *pMem = 0;
        pMem[1] = 0;
        pMem[2] = 0;
        *(uint32_t *)(pMem + 3) = 0;
      }
      else
      {
        pMem = nullptr;
      }
      *(uint32_t *)(this + 8360) = pMem;
    }
    fld_20A8 = *(uint32_t *)(this + 8360);
    *(uint32_t *)fld_20A8 = *(uint32_t *)pArg2;
    *(uint16_t *)(fld_20A8 + 4) = *(uint16_t *)(pArg2 + 4);
    *(uint8_t *)(fld_20A8 + 6) = *(uint8_t *)(pArg2 + 6);
  }
  else
  {
    if ( *(uint32_t *)(this + 8360) != 0 )
      j__free(*(void **)(this + 8360));
    *(uint32_t *)(this + 8360) = 0;
  }
  result = *(uint8_t **)(this + 8360);
  if ( result != nullptr )
  {
    if ( *result != 0 )
    {
      fld_20A0 = *(uint32_t *)(this + 8352);
      result = uArg3;
      *(uint32_t *)(this + 672) = 1;
      *(uint32_t *)(this + 668) = fld_20A0;
    }
    *(uint32_t *)(this + 8356) = uArg3;
  }
  else
  {
    *(uint32_t *)(this + 8356) = uArg3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D9570 sub_4D9570
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9570(int *this, int nArg2, uint32_t *pArg3, int nArg4)
{
  uint32_t *pMem; // eax
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax

  (*(void (/*thiscall*/ **)(int *))(*this + 320))(this);
  if ( nArg2 == 1 && nArg4 == 8 )
  {
    pMem = operator new(8u);
    *(this + 1955) = (int)pMem;
    *pMem = *pArg3;
    pMem[1] = pArg3[1];
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 436))(this) > 0 )
  {
    v6 = *this;
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 436))(this);
    v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v7);
    v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);
    (*(void (/*thiscall*/ **)(int *, int))(v6 + 112))(this, v9);
  }
  sub_49C620(this, 1, 1, 0);
  return sub_49C5F0(this, 1, 0, 0, 1000);
}



// ------------------------------------------------------------
// 0x4D9600 sub_4D9600
// ------------------------------------------------------------
void /*thiscall*/ sub_4D9600(int16_t **this)
{
  if ( *(this + 1955) != nullptr )
  {
    (*((void (/*thiscall*/ **)(int16_t **, int, uint32_t, int, int))*this + 118))(this, 11, 0, 1, 1);
    (*((void (/*thiscall*/ **)(int16_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))*this + 219))(
      this,
      0,
      **(this + 1955),
      **(this + 1955),
      0,
      0,
      0);
    (*((void (/*thiscall*/ **)(int16_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))*this + 219))(
      this,
      1,
      (*(this + 1955))[1],
      (*(this + 1955))[1],
      0,
      0,
      0);
    (*((void (/*thiscall*/ **)(int16_t **, uint32_t, uint32_t))*this + 224))(
      this,
      *((uint8_t *)*(this + 1955) + 6),
      *((uint8_t *)*(this + 1955) + 7));
    sub_495890((int *)this, 2, 0);
    sub_4A0550((float *)*(this + 28), (*(this + 1955))[2]);
    sub_49C5F0((int *)this, 5, 0, 0, 1000);
    if ( *(this + 1955) != nullptr )
      j__free(*(this + 1955));
    *(this + 1955) = nullptr;
  }
}



// ------------------------------------------------------------
// 0x4D96D0 sub_4D96D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D96D0(uint32_t *this)
{
  int v2; // edi
  int v3; // ebx
  int v4; // ebx
  int v5; // eax
  int v7; // [esp+10h] [ebp-4h]

  v2 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
  v7 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  v4 = v2 + v3 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  srand((v7 + v5) * v4);
  rand();
  if ( *(this + 1943) == 3 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
}



// ------------------------------------------------------------
// 0x4D9760 sub_4D9760
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9760(uint32_t *this)
{
  int result; // eax

  sub_4D5C50(this);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);
  if ( result == 529 )
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 656))(this);
  return result;
}



// ------------------------------------------------------------
// 0x4D9790 sub_4D9790
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9790(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1288))(this, nArg5, nArg4);
  if ( nArg2 != -2 )
    *(this + 1908) = nArg2;
  if ( nArg3 != -2 )
    *(this + 1909) = nArg3;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1292))(this, nArg3, nArg2);
}



// ------------------------------------------------------------
// 0x4D97E0 sub_4D97E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4D97E0(void *this, int nArg2)
{
  int pThis_14; // edi
  int pThis_1DD8; // ebx

  pThis_14 = *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1032))(this) + 20);
  *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1032))(this) + 20) = nArg2;
  pThis_1DD8 = sub_699000((int)this + 7640);  // 【clock_now(clk)】
  *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1032))(this) + 32) = pThis_1DD8;
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 1184))(this, nArg2, pThis_14);
}



// ------------------------------------------------------------
// 0x4D9840 sub_4D9840 —— ★ 主状态写入器包装器（研究 20 §4.2 定案）
// 先调 vt+228 基实现 0x49A320(this, 新状态 a2, 时长 a3, 起点 a4)，随后按
// "跨 0↔1 边界"补冻 **this+7640 时钟**（this+1910 word 下标）：
//   v5 >= 1 且 a2 < 1 → sub_698FE0(+7640) 解冻；v5 < 1 且 a2 >= 1 → sub_699030(+7640) 冻结。
// 研究 §4.2 原文："包装器 sub_4D9840 再冻 this+7640 时钟" —— 与研究 §2 字段表
// "+7640 另一支冻结时钟（0x4D9840 包装器使用）"逐条吻合。
// 即：受击硬直的冻结 = 基写入器（自身+36/动作子对象+6560/全部子对象）+ 本包装器（+7640）双层。
// ------------------------------------------------------------
uint8_t /*thiscall*/ sub_4D9840(int *this, int nArg2, uint32_t **uArg3, int nArg4)
{
  int fld_e50; // ebx
  uint8_t result; // al

  fld_e50 = *(this + 50);
  result = (uint8_t)sub_49A320(this, nArg2, uArg3, nArg4);
  if ( fld_e50 != nArg2 )
  {
    if ( fld_e50 >= 1 )
    {
      if ( nArg2 < 1 )
        return sub_698FE0((int)(this + 1910));  // 【clock_unfreeze(clk)】
    }
    else if ( nArg2 >= 1 )
    {
      return sub_699030((int)(this + 1910));  // 【clock_freeze(clk)】
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D98A0 sub_4D98A0
// ------------------------------------------------------------
int /*usercall*/ sub_4D98A0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int pObj; // ecx
  uint64_t v5; // rax
  int dword_99FB8C2; // edi
  unsigned int v7; // ebx
  int v8; // eax
  double v9; // st7
  unsigned int v10; // ebx
  uint64_t v11; // rax
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  double v15; // st7
  int v16; // ebx
  unsigned int v17; // ebx
  int v18; // eax
  double v19; // st7
  unsigned int v20; // ebx
  uint64_t v21; // rax
  unsigned int v22; // ebx
  int v23; // eax
  double v24; // st7
  unsigned int v25; // ebx
  uint64_t v26; // rax
  unsigned int v27; // ebx
  uint64_t v28; // rax
  unsigned int v29; // ebx
  uint64_t v30; // rax
  unsigned int v31; // ebx
  uint64_t v32; // rax
  unsigned int v33; // ebx
  int v34; // eax
  double v35; // st7
  uint32_t v38[4]; // [esp+4h] [ebp-BCh]
  uint32_t v39[4]; // [esp+14h] [ebp-ACh]
  uint32_t v40[4]; // [esp+24h] [ebp-9Ch]
  uint32_t v41[4]; // [esp+34h] [ebp-8Ch]
  uint32_t v42[4]; // [esp+44h] [ebp-7Ch]
  uint32_t v43[4]; // [esp+54h] [ebp-6Ch]
  uint32_t v44[4]; // [esp+64h] [ebp-5Ch]
  uint32_t v45[4]; // [esp+74h] [ebp-4Ch]
  uint32_t v46[4]; // [esp+84h] [ebp-3Ch]
  uint32_t v47[4]; // [esp+94h] [ebp-2Ch]
  uint32_t v48[4]; // [esp+A4h] [ebp-1Ch]
  char ArgList[4]; // [esp+B4h] [ebp-Ch]
  int v50; // [esp+B8h] [ebp-8h]
  int v51; // [esp+BCh] [ebp-4h]

  pObj = pArg1[2088];
  v41[0] = 0;
  v41[1] = 1092616192;
  v41[2] = 1101004800;
  v41[3] = 1114636288;
  v46[0] = 1065353216;
  v46[1] = 1069547520;
  v46[2] = 1072064102;
  v46[3] = 1075838976;
  v39[0] = 0;
  v39[1] = 1084227584;
  v39[2] = 1092616192;
  v39[3] = 1101004800;
  v43[0] = 0;
  v43[1] = 1106247680;
  v43[2] = 1114636288;
  v43[3] = 1125515264;
  v44[0] = 1065353216;
  v44[1] = 1065772646;
  v44[2] = 1066192077;
  v44[3] = 1067030938;
  v42[0] = 0;
  v42[1] = 1106247680;
  v42[2] = 1112014848;
  v42[3] = 1120403456;
  v45[0] = 0;
  v45[1] = 1084227584;
  v45[2] = 1092616192;
  v45[3] = 1106247680;
  v48[0] = 1065353216;
  v48[1] = 1065772646;
  v48[2] = 1066192077;
  v48[3] = 1067030938;
  v47[0] = 1065353216;
  v47[1] = 1066192077;
  v47[2] = 1066611507;
  v47[3] = 1067869798;
  v40[0] = 0;
  v40[1] = 1120403456;
  v40[2] = 1128792064;
  v40[3] = 1133903872;
  v38[0] = 0;
  v38[1] = 1101004800;
  v38[2] = 1106247680;
  v38[3] = 1116471296;
  if ( pObj == 0 || (LODWORD(v5) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273), (uint8_t)v5 == 0) )
  {
    dword_99FB8C2 = dword_99FB8C;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, int))(*pArg1 + 672))(pArg1, 0, nArg3, nArg2) + 466;
    v8 = sub_41A5E0(v7);
    v9 = *(float *)&v41[dword_99FB8C2];
    v50 = v8;
    sub_41A590(v7, (uint64_t)v9 >> 32, v8 + (uint64_t)v9);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 676))(pArg1, 0);
    *(uint32_t *)ArgList = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1);
    v10 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 4;
    v50 = sub_41A5E0(v10);
    v11 = (uint64_t)((double)v50 * *(float *)&v46[dword_99FB8C2]);
    sub_41A590(v10, SHIDWORD(v11), v11);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 676))(pArg1, 0);
    v12 = *pArg1;
    v13 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 740))(pArg1, 0, 1);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v12 + 732))(pArg1, v13);
    v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1);
    off_77F3FC(aApplydifficult, *(uint32_t *)ArgList, v14);
    v15 = *(float *)&v39[dword_99FB8C2];
    pArg1[1880] += (uint64_t)*(float *)&v43[dword_99FB8C2];
    v16 = 0;
    pArg1[1898] += (uint64_t)v15;
    *(uint32_t *)ArgList = 0;
    v50 = 0;
    do
    {
      if ( sub_497040(*(uint32_t *)ArgList) != 17 )
      {
        v17 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + v16 + 284;
        v18 = sub_41A5E0(v17);
        v19 = *(float *)&v45[dword_99FB8C2];
        v51 = v18;
        sub_41A590(v17, (uint64_t)v19 >> 32, v18 + (uint64_t)v19);
        v16 = v50;
      }
      v16 += 14;
      ++*(uint32_t *)ArgList;
      v50 = v16;
    }
    while ( v16 < 224 );
    v20 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 844;
    v51 = sub_41A5E0(v20);
    v21 = (uint64_t)((double)v51 * *(float *)&v44[dword_99FB8C2]);
    sub_41A590(v20, SHIDWORD(v21), v21);
    v22 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 816;
    v23 = sub_41A5E0(v22);
    v24 = *(float *)&v42[dword_99FB8C2];
    v51 = v23;
    sub_41A590(v22, (uint64_t)v24 >> 32, v23 + (uint64_t)v24);
    v25 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 1012;
    v51 = sub_41A5E0(v25);
    v26 = (uint64_t)((double)v51 * *(float *)&v48[dword_99FB8C2]);
    sub_41A590(v25, SHIDWORD(v26), v26);
    v27 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 1068;
    v51 = sub_41A5E0(v27);
    v28 = (uint64_t)((double)v51 * *(float *)&v48[dword_99FB8C2]);
    sub_41A590(v27, SHIDWORD(v28), v28);
    v29 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 1040;
    v51 = sub_41A5E0(v29);
    v30 = (uint64_t)((double)v51 * *(float *)&v47[dword_99FB8C2]);
    sub_41A590(v29, SHIDWORD(v30), v30);
    v31 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 1096;
    v51 = sub_41A5E0(v31);
    v32 = (uint64_t)((double)v51 * *(float *)&v47[dword_99FB8C2]);
    sub_41A590(v31, SHIDWORD(v32), v32);
    v33 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 900;
    v34 = sub_41A5E0(v33);
    v35 = *(float *)&v40[dword_99FB8C2];
    v51 = v34;
    sub_41A590(v33, (uint64_t)v35 >> 32, v34 + (uint64_t)v35);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 676))(pArg1, 0);
    v5 = (uint64_t)*(float *)&v38[dword_99FB8C2];
    *((uint64_t *)pArg1 + 1059) = (unsigned int)v5;
  }
  return v5;
}


// ------------------------------------------------------------
// 0x4D9D10 sub_4D9D10
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4D9D10(uint32_t *this)
{
  return *(this + 1943) == 3 && *(uint32_t *)(dword_8F7A24 + 12) == 3 && *(this + 1545) != 0;
}



// ------------------------------------------------------------
// 0x4D9D40 sub_4D9D40
// ------------------------------------------------------------
char /*thiscall*/ sub_4D9D40(uint8_t *this, char pszArg2)
{
  bool pThis_3FC; // zf
  char result; // al

  pThis_3FC = (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1020))(this) == 0;
  result = pszArg2;
  if ( pThis_3FC || pszArg2 != 0 )
  {
    *(this + 156) = pszArg2;
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);
    return sub_53F6A0(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D9D80 sub_4D9D80
// ------------------------------------------------------------
int /*stdcall*/ sub_4D9D80(int nArg1, uint32_t *pArg2, int nArg3, int nArg4)
{
  int result; // eax

  result = nArg1;
  if ( pArg2[1787] != nArg1 )
  {
    pArg2[1919] = nArg3;
    pArg2[1918] = nArg4;
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 1104))(pArg2, nArg1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D9DB0 sub_4D9DB0
// ------------------------------------------------------------
char /*thiscall*/ sub_4D9DB0(uint32_t *this, int nArg2, int nArg3)
{
  int fld_e1813; // ecx
  int v6; // edi
  int v7; // eax
  int fld_e18132; // ecx
  int v9; // edi
  int v10; // eax
  int v11; // edx

  fld_e1813 = *(this + 1813);
  if ( fld_e1813 == 0 )
    return 0;
  if ( nArg2 == -1 && nArg3 == -1 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813);
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) >= v6 )
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + 300;
    else
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - 300;
    fld_e18132 = *(this + 1813);
    *(this + 1919) = v7;
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 124))(fld_e18132);
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) >= v9 )
      *(this + 1918) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) - 50;
    else
      *(this + 1918) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) + 50;
  }
  else
  {
    *(this + 1919) = nArg2;
    *(this + 1918) = nArg3;
  }
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  v11 = *this;
  *(this + 1921) = v10;
  *(this + 1920) = (*(int (/*thiscall*/ **)(uint32_t *))(v11 + 124))(this);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 6);
  return 1;
}



// ------------------------------------------------------------
// 0x4D9E80 sub_4D9E80
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9E80(uint32_t *this, int nArg2, int nArg3)
{
  int v4; // edx
  int v5; // eax
  int v6; // edx

  v4 = *this;
  *(this + 1918) = nArg3;
  *(this + 1919) = nArg2;
  *(this + 1921) = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 120))(this);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v6 = *this;
  *(this + 1920) = v5;
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(v6 + 1104))(this, 25);
}



// ------------------------------------------------------------
// 0x4D9ED0 sub_4D9ED0 —— 大状态 ID 区间判定（50000..51000 = 特殊演出态族）【待验证：具体语义】
// 读 vt+340 的 +0 字段（技能/动作 id）。研究 §16 P41 定案：技能过场无独立引擎，
// 走大状态 tick case 硬编码 —— 50000 段疑为过场/演出类 id 区间。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4D9ED0(void *this)
{
  return *(int *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 340))(this) >= 50000
      && *(int *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 340))(this) <= 51000;
}



// ------------------------------------------------------------
// 0x4D9F00 sub_4D9F00
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9F00(void *this, int nArg2)
{
  int pThis_40; // eax

  pThis_40 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 64))(this);
  return sub_50EF20(pThis_40, nArg2, 0, -1);
}



// ------------------------------------------------------------
// 0x4D9F20 sub_4D9F20 —— ★ 格挡时刻戳 vt+548（研究 §1.2 定案）
// `this+1673 = sub_699000(this+16)` —— 记录 this+64 时钟（word 下标 +16）当前时刻。
// 研究 §1.2 槽表：+548 = 0x4D9F20 记录 this+64 时钟当前时刻 → this+6692（格挡时刻戳）。
// 调用点：0x4D4D40 命中的格挡分支、sub_4D6D90 ④（a4 != 0）、0x4D9F50 等。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9F20(uint32_t *this, int nArg2)
{
  int result; // eax

  result = sub_699000((int)(this + 16));  // 【clock_now(clk)】
  *(this + 1673) = result;
  return result;
}



// ------------------------------------------------------------
// 0x4D9F50 sub_4D9F50
// ------------------------------------------------------------
char /*thiscall*/ sub_4D9F50(uint32_t *this, int nArg2)
{
  int fld_e2090; // eax

  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 1032))(this) + 16) = nArg2;
  fld_e2090 = *(this + 2090);
  *(this + 2088) = nArg2;
  if ( fld_e2090 != 0 && nArg2 == 0 )
  {
    LOBYTE(fld_e2090) = *(uint8_t *)(fld_e2090 + 1);
    if ( (uint8_t)fld_e2090 == 1 )
    {
      LOBYTE(fld_e2090) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 101);
    }
    else if ( (uint8_t)fld_e2090 == 2 )
    {
      LOBYTE(fld_e2090) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)fld_e2090 != 0 )
        LOBYTE(fld_e2090) = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t))(*this + 560))(this, 13, 0, 2, 0);
    }
  }
  return fld_e2090;
}



// ------------------------------------------------------------
// 0x4D9FC0 sub_4D9FC0
// ------------------------------------------------------------
int /*userpurge*/ sub_4D9FC0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, uint32_t *pArg3)
{
  int result; // eax
  uint32_t *pArg32; // esi

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 724))(pArg1);
  if ( (uint8_t)result == 0 )
  {
    pArg32 = nullptr;
    if ( pArg3 != nullptr )
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 576))(pArg3, nArg2) != 0 )
        pArg32 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 576))(pArg3);
      else
        pArg32 = pArg3;
      result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg32 + 40))(pArg32, 529);
      if ( (uint8_t)result != 0 )
      {
        result = pArg32[2088];
        if ( result != 0 )
          pArg32 = (uint32_t *)pArg32[2088];
      }
    }
    pArg1[1814] = pArg32;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA030 sub_4DA030
// ------------------------------------------------------------
int /*thiscall*/ sub_4DA030(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 12;
  return result;
}



// ------------------------------------------------------------
// 0x4DA050 sub_4DA050
// ------------------------------------------------------------
char */*cdecl*/ sub_4DA050(char *pszArg1, char *pszArg2, const void *pArg3)
{
  char *result; // eax
  void *v4; // edi

  for ( result = pszArg1; result != pszArg2; result += 32 )
  {
    v4 = result;
    qmemcpy(v4, pArg3, 0x20u);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA080 sub_4DA080
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4DA080(void *this)
{
  int pThis_58; // [esp+8h] [ebp-4h]

  pThis_58 = sub_41A5E0((unsigned int)this + 88);
  return (uint64_t)((double)pThis_58 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 102)));
}



// ------------------------------------------------------------
// 0x4DA0B0 sub_4DA0B0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4DA0B0(void *this)
{
  int pThis_90; // [esp+8h] [ebp-4h]

  pThis_90 = sub_41A5E0((unsigned int)this + 144);
  return (uint64_t)((double)pThis_90 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 158)));
}



// ------------------------------------------------------------
// 0x4DA0F0 sub_4DA0F0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4DA0F0(char *this, int nArg2)
{
  char *pThis_E; // esi
  int v4; // [esp+10h] [ebp+8h]

  pThis_E = this + 14 * nArg2;
  v4 = sub_41A5E0((unsigned int)(pThis_E + 172));
  return (uint64_t)((double)v4 * COERCE_FLOAT(sub_41A5E0((unsigned int)(pThis_E + 228))));
}



// ------------------------------------------------------------
// 0x4DA130 sub_4DA130
// ------------------------------------------------------------
int /*thiscall*/ sub_4DA130(uint32_t *this)
{
  uint32_t *pThis_6FD; // ebx
  int v3; // edi
  uint32_t *v4; // eax
  int result; // eax
  int fld_e29; // ecx

  sub_4D6970((int)this);
  if ( *(this + 1794) < 0x10u )
    pThis_6FD = this + 1789;
  else
    pThis_6FD = (uint32_t *)*(this + 1789);
  v3 = *this;
  v4 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t *))(v3 + 1024))(this, *v4, pThis_6FD);
  fld_e29 = *(this + 29);
  *(this + 1813) = 0;
  *(this + 1814) = 0;
  *(this + 1815) = 0;
  *(this + 1816) = 0;
  *(this + 1817) = 0;
  *(this + 1818) = 0;
  *(this + 1819) = 0;
  *(this + 1917) = 0;
  if ( *(uint8_t *)(fld_e29 + 153) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this);
    if ( result == 100 )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(*this + 732))(this, 0, 0, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA1D0 sub_4DA1D0
// ------------------------------------------------------------
int /*usercall*/ sub_4DA1D0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // ebx
  int nRand; // edx
  int v13; // eax
  int v14; // edi
  int v15; // [esp+4h] [ebp-8h] BYREF
  int v16; // [esp+8h] [ebp-4h] BYREF

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0
    && ((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 0
     || (result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1)) == 6) )
  {
    v5 = pArg1[29];
    v15 = 4;
    v16 = 4;
    v6 = *(uint32_t *)(*(uint32_t *)(v5 + 132) + 44);
    v7 = *(uint32_t *)(v6 + 364);
    v8 = v6 + 360;
    if ( v7 != 0 )
      v9 = (*(uint32_t *)(v8 + 8) - v7) >> 5;
    else
      v9 = 0;
    (*(void (/*thiscall*/ **)(uint32_t *, int *, int *, int, int, int))(*pArg1 + 1156))(pArg1, &v15, &v16, 224 * v9, nArg3, nArg2);
    if ( v15 == 4 && v16 == 4 )
    {
      v10 = 4 * pArg1[1787];
      v11 = sub_699000((int)(pArg1 + 1910));  // 【clock_now(clk)】
      nRand = rand() % dword_6F89D4[v10];
      v13 = dword_6F89D0[v10];
    }
    else
    {
      v14 = 4 * pArg1[1787];
      v11 = sub_699000((int)(pArg1 + 1910));  // 【clock_now(clk)】
      nRand = rand() % dword_6F89CC[v14];
      v13 = dword_6F89C8[v14];
    }
    pArg1[1818] = v13 + nRand + v11;
    if ( rand() % 100 < SLOWORD(pArg1[pArg1[1787] + 2092]) )
      v15 = 4;
    if ( rand() % 100 < SHIWORD(pArg1[pArg1[1787] + 2092]) )
      v16 = 4;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 776))(pArg1, 15) != 0 && rand() % 100 < 60 )
    {
      v15 = sub_432E50(v15);
      v16 = sub_432E50(v16);
    }
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 896))(pArg1, v15, v16);
    sub_5FDFE0(pArg1[1932]);
    if ( v16 != 4 )
    {
      if ( (int)pArg1[1654] < 100 )
        pArg1[1654] = 100;
      if ( (int)pArg1[1655] < 100 )
        pArg1[1655] = 100;
      if ( (int)pArg1[1652] < 100 )
        pArg1[1652] = 100;
      if ( (int)pArg1[1653] < 100 )
        pArg1[1653] = 100;
    }
    return (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1080))(pArg1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA3B0 sub_4DA3B0 —— ★ 命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
// 与命中主处理器同链路的前置判：a3 受方 vt+368 + a1 vt+1304 + a1 vt+308 三门通过 →
// a3 vt+312(1)（受击盒使能）+ 取 a3 车主容器 vt+340 与 v6(+104) → sub_4E4C10
// （动作数据包发送，会话 3 定案）。
// 否则：attackinfo 有伤害门（+16 != 0 或 float+0 > 0）→ 把 a4 的 6 个 float 存到
// a1+7777..7797（**命中盒缓存**）→ sub_4D9FC0（攻击者参照解析）→ 条件分支
// （a1[1787]==11 → vt+1104(4) 大状态切换）→ 尾调 **sub_4D71B0(a1, a3, a4, a5)**
// = 本地直接走命中主处理器（服务端包之外的第二条入口）。
// ------------------------------------------------------------
int /*fastcall*/ sub_4DA3B0(uint32_t *pArg1, int nArg2, uint32_t *pArg3, uint32_t *pArg4, int nArg5)
{
  int pObj; // ebx
  uint32_t *v7; // edi
  int v8; // eax
  int v10; // eax
  int v11; // [esp-10h] [ebp-84h]
  uint8_t v12[100]; // [esp+Ch] [ebp-68h] BYREF
  int dword_796E502; // [esp+70h] [ebp-4h]
  int v14; // [esp+80h] [ebp+Ch]

  dword_796E502 = dword_796E50;
  if ( pArg1[1943] == 3 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1064))(pArg1);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg3 + 368))(pArg3) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t *))(*pArg1 + 1304))(pArg1, pArg3) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 312))(pArg3, 1);
    pObj = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 60))(pArg3) + 104);
    v7 = (uint8_t)sub_4E5CA0(pArg3) == 0 ? pArg1 : nullptr;
    v14 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 340))(pArg3);
    (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj + 20))(pObj, v12);
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 672))(pArg3);
    sub_4E4C10(v7, v14, *(uint32_t *)(v8 + 24), v12, v11, 0, 0, 0);
    return 0;
  }
  else
  {
    v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 348))(pArg3);
    if ( *(uint8_t *)(v10 + 16) != 0 || *(float *)v10 > 0.0 )
    {
      *(uint32_t *)((char *)pArg1 + 7777) = *pArg4;
      *(uint32_t *)((char *)pArg1 + 7781) = pArg4[1];
      *(uint32_t *)((char *)pArg1 + 7785) = pArg4[2];
      *(uint32_t *)((char *)pArg1 + 7789) = pArg4[3];
      *(uint32_t *)((char *)pArg1 + 7793) = pArg4[4];
      *(uint32_t *)((char *)pArg1 + 7797) = pArg4[5];
      sub_4D9FC0(pArg1, (int)pArg1, pArg3);
      if ( *((uint8_t *)pArg1 + 7530) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1236))(pArg1);
      if ( pArg1[1787] == 11 )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 4);
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 576))(pArg3) != 0
        && (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 576))(pArg3) != pArg3 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t *))(*pArg1 + 1136))(pArg1, pArg3) == 1 && rand() % 100 < 70 )
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*pArg1 + 1280))(pArg1, pArg3);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0
          && rand() % 100 < pArg1[2120]
          && sub_699000((int)(pArg1 + 2122)) > pArg1[2121] )  // 【clock_now(clk)】
        {
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*pArg1 + 1180))(pArg1, pArg3);
          *((uint8_t *)pArg1 + 8501) = 0;
          *((uint8_t *)pArg1 + 8502) = 0;
          sub_698F90((int)(pArg1 + 2122), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        }
      }
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 348))(pArg3) + 124) == 2 )
        rand();
    }
    return sub_4D71B0(pArg1, *(float *)&pArg3, (int)pArg4, nArg5);  // 【命中主处理器 vt+512（§2 全文定案）】
  }
}



// ------------------------------------------------------------
// 0x4DA5F0 sub_4DA5F0
// ------------------------------------------------------------
bool /*thiscall*/ sub_4DA5F0(int *this, int nArg2)
{
  int v3; // ebx
  int v5; // edi
  int fld_e1880; // [esp+10h] [ebp+8h]

  if ( nArg2 == 0 )
    return false;
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);
  if ( v3 != (*(int (/*thiscall*/ **)(int *))(*this + 376))(this)
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 940))(nArg2) == 1 )
  {
    return false;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 776))(this, 5) == 0 && *(this + 1880) == 0 )
    return true;
  v5 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, nArg2, 0);
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 776))(this, 5) != 0 )
    fld_e1880 = 10;
  else
    fld_e1880 = *(this + 1880);
  return v5 <= (int)(uint64_t)((double)fld_e1880 * 1.4);
}



// ------------------------------------------------------------
// 0x4DA6B0 sub_4DA6B0
// ------------------------------------------------------------
char /*thiscall*/ sub_4DA6B0(uint32_t *this, uint32_t *uArg2)
{
  int fld_e29; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // esi

  fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
  v4 = *(uint32_t *)(fld_e29 + 364);
  v5 = fld_e29 + 360;
  if ( v4 != 0 )
    v6 = (*(uint32_t *)(v5 + 8) - v4) >> 5;
  else
    v6 = 0;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) >= 80 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) <= 224 * v6 - 80 )
    {
      return 0;
    }
    else
    {
      *uArg2 = 0;
      return 1;
    }
  }
  else
  {
    *uArg2 = 1;
    return 1;
  }
}



// ------------------------------------------------------------
// 0x4DA730 sub_4DA730
// ------------------------------------------------------------
char /*thiscall*/ sub_4DA730(uint32_t *this)
{
  int fld_e2147; // eax
  int fld_e2145; // ebx
  char *pThis_855; // eax
  int fld_e2146; // ebx
  unsigned int nRand; // eax

  fld_e2147 = *(this + 2147);
  if ( fld_e2147 != 0 )
  {
    fld_e2147 = *(this + 2146);
    if ( fld_e2147 != 0 )
    {
      fld_e2145 = *(this + 2145);
      fld_e2147 = sub_699000((int)(this + 2139));  // 【clock_now(clk)】
      if ( fld_e2147 >= fld_e2145 )
      {
        if ( *(this + 2138) < 0x10u )
          pThis_855 = (char *)(this + 2133);
        else
          pThis_855 = (char *)*(this + 2133);
        (*(void (/*thiscall*/ **)(uint32_t *, char *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_855, -1, 0, 0);
        *((uint8_t *)this + 8569) = 0;
        *((uint8_t *)this + 8570) = 0;
        fld_e2146 = *(this + 2146);
        nRand = rand();
        LOBYTE(fld_e2147) = sub_698F90((int)(this + 2139), fld_e2146 + nRand % (*(this + 2147) - fld_e2146), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
    }
  }
  return fld_e2147;
}



// ------------------------------------------------------------
// 0x4DA7C0 sub_4DA7C0
// ------------------------------------------------------------
char */*cdecl*/ sub_4DA7C0(char *pszArg1, char *pszArg2, char *pszArg3)
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
    pszArg12 += 32;
    result += 32;
    qmemcpy(v6, pszArg122, 0x20u);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA7F0 sub_4DA7F0
// ------------------------------------------------------------
char */*cdecl*/ sub_4DA7F0(char *pszArg1, char *pszArg2, char *pszArg3)
{
  char *pszArg22; // edx
  char *result; // eax

  pszArg22 = pszArg2;
  result = pszArg3;
  while ( pszArg22 != pszArg1 )
  {
    pszArg22 -= 32;
    result -= 32;
    qmemcpy(result, pszArg22, 0x20u);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA820 sub_4DA820
// ------------------------------------------------------------
char */*cdecl*/ sub_4DA820(char *pszArg1, char *pszArg2, char *pszArg3)
{
  char *pszArg12; // edx
  char *result; // eax

  pszArg12 = pszArg1;
  for ( result = pszArg3; pszArg12 != pszArg2; result += 32 )
  {
    if ( result != nullptr )
      qmemcpy(result, pszArg12, 0x20u);
    pszArg12 += 32;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA860 sub_4DA860
// ------------------------------------------------------------
void */*thiscall*/ sub_4DA860(void *Block, char pszArg2)
{
  sub_4DA890();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4DA890 sub_4DA890
// ------------------------------------------------------------
int /*thiscall*/ sub_4DA890(uint32_t *this)
{
  int result; // eax

  *this = &CNSpeedControl::`vftable';
  nullsub_3(this);
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4DA8F0 sub_4DA8F0
// ------------------------------------------------------------
void */*thiscall*/ sub_4DA8F0(void *Block, char pszArg2)
{
  sub_4DA920();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4DA920 sub_4DA920
// ------------------------------------------------------------
int /*thiscall*/ sub_4DA920(uint32_t *this)
{
  int result; // eax

  *this = &CNMovementController::`vftable';
  nullsub_3(this);
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ============================================================
// 【分区 7】PO/装备对象表现族 + 内嵌技能执行器（0x4DA980 起）
//   - 0x4DA890 (CNSpeedControl 析构) 与 0x4DA920 (CNMovementController 析构)
//     均 IRDAppendage 基 → 装备/被动对象挂件的实现类
//   - 0x4DAE50 起 = 头顶称号/名字 HUD（"Lv.%d %s" 格式 + 状态图标 15px 梯次堆叠，
//     图标映射 sub_422E70(状态id + 1573)，131091 为特殊哨兵跳过）
//   - 0x4DB480 = 反击/架招判定（六个 id 阈值表 261396..261402 → 反应档位 3/11/15/0/6/2/5）
// ============================================================

// ------------------------------------------------------------
// 0x4DA980 sub_4DA980 —— 死亡/淘汰确认包（type 42；off_77F3FC 日志双分支）
// 分支 A（byte_77F280 != 0 或 +7801 == 0）：条件 308 成立则 vt+312(0) 后打日志
// 分支 B（PVP 场景 6 且 +1032 容器 +24 车主条件 273）→ 取车主 id
//   写包：v11 = vt+52 → sub_423290(&v11, 2)；v11 = v4（车主 id）→ 同上；sub_423380 提交
//   this+264 = 1（已上报标志）
// 与 0x4DB130/0x4DB200（随机语音/表情触发）同属"淘汰/胜负"表现族。
// ------------------------------------------------------------
char /*thiscall*/ sub_4DA980(char *this)
{
  char result; // al
  int pThis_609; // ecx
  int v4; // ebx
  int pThis_408; // eax
  int pThis_4082; // eax
  char *pThis_1242; // edi
  int pThis_343; // eax
  char *pThis_124; // edi
  int pThis_34; // eax
  int pThis_342; // [esp+4h] [ebp-4h] BYREF

  result = *(this + 264);
  if ( result == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1020))(this) != 0 )
    {
      pThis_609 = *((uint32_t *)this + 1545);
      if ( pThis_609 != 0 && *((uint32_t *)this + 30) != pThis_609 )
      {
        sub_493400(pThis_609, *((uint32_t *)this + 1702));
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *((uint32_t *)this + 1545));
      }
    }
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1072))(this);
    if ( byte_77F280 != 0 || *(this + 7801) == 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
      if ( *((uint32_t *)this + 78) < 0x10u )
        pThis_124 = this + 292;
      else
        pThis_124 = *((char **)this + 73);
      pThis_34 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 52))(this);
      return off_77F3FC((char *)&byte_6F8F34, pThis_124, pThis_34);
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this);
      if ( result != 0 )
      {
        v4 = 0xFFFF;
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 6
          && *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1032))(this) + 24) != 0 )
        {
          pThis_408 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1032))(this);
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pThis_408 + 24) + 40))(*(uint32_t *)(pThis_408 + 24), 273) != 0 )
          {
            pThis_4082 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1032))(this);
            v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pThis_4082 + 24) + 52))(*(uint32_t *)(pThis_4082 + 24));
          }
        }
        sub_423200(dword_8F7B08, 42);  // 【发送网络包API】
        pThis_342 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 52))(this);
        sub_423290(&pThis_342, 2);
        pThis_342 = v4;
        sub_423290(&pThis_342, 2);
        sub_423380(dword_8F7B08);
        *(this + 264) = 1;
        if ( *((uint32_t *)this + 78) < 0x10u )
          pThis_1242 = this + 292;
        else
          pThis_1242 = *((char **)this + 73);
        pThis_343 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 52))(this, v4);
        return off_77F3FC((char *)&byte_6F8F64, pThis_1242, pThis_343);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DAB30 sub_4DAB30
// ------------------------------------------------------------
char */*cdecl*/ sub_4DAB30(char *pszArg1, char *pszArg2, const void *pArg3)
{
  char *result; // eax
  char *pszArg22; // edx

  result = pszArg2;
  if ( pszArg2 != nullptr )
  {
    pszArg22 = pszArg2;
    result = pszArg1;
    do
    {
      if ( result != nullptr )
        qmemcpy(result, pArg3, 0x20u);
      result += 32;
      --pszArg22;
    }
    while ( pszArg22 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DAB60 sub_4DAB60
// ------------------------------------------------------------
bool /*thiscall*/ sub_4DAB60(uint32_t *this, int nArg2)
{
  uint32_t *fld_e84; // edx
  uint32_t *i; // eax

  fld_e84 = (uint32_t *)*(this + 84);
  for ( i = (uint32_t *)*(this + 83); i != fld_e84; ++i )
  {
    if ( *i == nArg2 )
      break;
  }
  return i != fld_e84;
}



// ------------------------------------------------------------
// 0x4DAB90 sub_4DAB90
// ------------------------------------------------------------
void /*stdcall*/ sub_4DAB90(uint32_t *pArg1, int *pDwArg2)
{
  int *pDwArg22; // esi
  int v3; // edi
  int v4; // eax
  int v5; // eax
  float *j; // esi
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  int i; // [esp+4h] [ebp-4h]

  pDwArg22 = pDwArg2;
  if ( pDwArg2 != nullptr )
  {
    v3 = 0;
    for ( i = 0; ; v3 = i )
    {
      v4 = pDwArg22[11];
      if ( v4 != 0 )
        v4 = (pDwArg22[12] - v4) / 88;
      if ( v3 >= v4 )
        break;
      v5 = sub_4924C0(pDwArg22, v3);
      for ( j = *(float **)(v5 + 60); j != *(float **)(v5 + 64); j += 6 )
      {
        v7 = -*j;
        if ( (double)(int)pArg1[5] < v7 )
          pArg1[5] = (uint64_t)v7;
        v8 = j[3] + *j;
        if ( (double)(int)pArg1[4] < v8 )
          pArg1[4] = (uint64_t)v8;
        v9 = -j[1];
        if ( (double)(int)pArg1[6] < v9 )
          pArg1[6] = (uint64_t)v9;
        v10 = j[4] + j[1];
        if ( (double)(int)pArg1[7] < v10 )
          pArg1[7] = (uint64_t)v10;
      }
      pDwArg22 = pDwArg2;
      ++i;
    }
  }
}



// ------------------------------------------------------------
// 0x4DAC90 sub_4DAC90
// ------------------------------------------------------------
void /*thiscall*/ sub_4DAC90(int *this)
{
  int v2; // eax
  int v3; // eax
  int fld_e1813; // edi
  uint16_t v5; // [esp+4h] [ebp-8h] BYREF
  uint16_t v6; // [esp+8h] [ebp-4h] BYREF

  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v5);
  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v6);
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1108))(this) == 0 )
  {
    v2 = sub_45EBE0(v5, v6);
    v3 = __RTDynamicCast(v2, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    if ( v3 != 0 )
    {
      fld_e1813 = *(this + 1813);
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1148))(this, v3);
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1132))(this) == 0 )
      {
        if ( sub_4DAB60(this, 10) )
        {
          (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 9);
        }
        else if ( sub_4DAB60(this, 11) )
        {
          (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 10);
        }
      }
      if ( fld_e1813 != *(this + 1813) )
        sub_4D84F0(this, 0, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x4DAD70 sub_4DAD70
// ------------------------------------------------------------
char /*usercall*/ sub_4DAD70@<al>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  int pObj; // edi
  int v5; // edi
  int pObj2; // edi
  double v7; // st7
  double v8; // st7
  int v9; // edx
  float v11; // [esp+4h] [ebp-8h]

  if ( pArg1[1787] == 7 )
    return 0;
  if ( rand() % 100 >= 50 )
    return 0;
  pObj = pArg1[1813];
  if ( pObj == 0 || sub_4DAB60(pArg1, 11) )
    return 0;
  v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, nArg2);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) >= v5 )
  {
    v8 = (double)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 120))(pArg1[1813]);
    v7 = v8 - (double)sub_4D8FE0(pArg1) * 0.5;
  }
  else
  {
    pObj2 = pArg1[1813];
    v11 = (double)sub_4D8FE0(pArg1) * 0.5;
    v7 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2) + v11;
  }
  v9 = *pArg1;
  pArg1[1919] = (uint64_t)v7;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 1104))(pArg1, 11);
  return 1;
}



// ------------------------------------------------------------
// 0x4DAE50 sub_4DAE50
// ------------------------------------------------------------
char /*thiscall*/ sub_4DAE50(char *this, int nArg2, int nArg3)
{
  uint32_t *pThis_154; // eax
  int pThis_C0; // eax
  int v6; // ebx
  int v7; // edx
  const char *pThis_124; // eax
  int pThis_797; // eax
  const char *pThis_1243; // eax
  int pThis_178; // edi
  const char *pThis_1244; // edi
  uint32_t *pThis_2A0; // eax
  int pThis_7972; // eax
  unsigned int v15; // edi
  int pThis_7A0; // ecx
  int v17; // ebx
  int pThis_7A02; // eax
  uint32_t *pThis_1242; // [esp-Ch] [ebp-88h]
  int v21; // [esp-Ch] [ebp-88h]
  int i; // [esp+4h] [ebp-78h]
  char Buffer[109]; // [esp+8h] [ebp-74h] BYREF
  int16_t v24; // [esp+75h] [ebp-7h]
  int dword_796E502; // [esp+78h] [ebp-4h]

  dword_796E502 = dword_796E50;
  pThis_154 = (uint32_t *)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this);
  if ( *pThis_154 == 60001 )
    return (char)pThis_154;
  LOBYTE(pThis_154) = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 940))(this);
  if ( (uint8_t)pThis_154 != 0 )
    return (char)pThis_154;
  pThis_C0 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 192))(this);
  nArg3 += -30 - pThis_C0;
  sub_424680((int)&nArg2, (int)&nArg3, 0.0, 0.0);
  v6 = 0;
  memset(Buffer, 0, sizeof(Buffer));
  nArg2 -= 75;
  v7 = *(uint32_t *)this;
  v24 = 0;
  if ( (*(uint8_t (/*thiscall*/ **)(char *))(v7 + 1296))(this) != 0 )
  {
    if ( *((uint32_t *)this + 78) < 0x10u )
      pThis_124 = this + 292;
    else
      pThis_124 = *((const char **)this + 73);
    sprintf(Buffer, "%s", pThis_124);
    v6 = -14745706;
  }
  pThis_797 = *((uint32_t *)this + 1943);
  switch ( pThis_797 )
  {
    case 3:
      if ( *((uint32_t *)this + 78) < 0x10u )
        pThis_1242 = this + 292;
      else
        pThis_1242 = *((uint32_t **)this + 73);
      sprintf(Buffer, "%s", pThis_1242);
      goto LABEL_20;
    case 1:
      if ( *((uint32_t *)this + 78) < 0x10u )
        pThis_1243 = this + 292;
      else
        pThis_1243 = *((const char **)this + 73);
      sprintf(Buffer, "%s", pThis_1243);
      v6 = -37965;
      break;
    case 2:
      v21 = sub_4633B0(this);
      sprintf(Buffer, "%s", v21);
LABEL_20:
      v6 = -1048321;
      break;
    default:
      break;
  }
  pThis_178 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 376))(this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) == pThis_178 )
  {
    if ( *((uint32_t *)this + 78) < 0x10u )
      pThis_1244 = this + 292;
    else
      pThis_1244 = *((const char **)this + 73);
    pThis_2A0 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 672))(this, 3);
    sprintf(Buffer, "Lv.%d %s", *pThis_2A0, pThis_1244);
    v6 = -6400;
  }
  LOBYTE(pThis_154) = Buffer[0];
  if ( Buffer[0] != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (uint32_t *)this + 1795);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, nArg2, nArg3, v6, Buffer);
    pThis_7972 = *((uint32_t *)this + 1943);
    if ( pThis_7972 == 1 || pThis_7972 == 2 )
    {
      v15 = 0;
      for ( i = 0; ; i += 15 )
      {
        pThis_7A0 = *((uint32_t *)this + 1952);
        if ( pThis_7A0 == 0 || v15 >= (*((uint32_t *)this + 1953) - pThis_7A0) >> 2 )
          break;
        if ( *(uint32_t *)(pThis_7A0 + 4 * v15) != 131091 )
        {
          v17 = *(uint32_t *)dword_79C0B0;
          pThis_7A02 = sub_422E70((uint8_t)*(uint32_t *)(*((uint32_t *)this + 1952) + 4 * v15) + 1573);
          (*(void (/*cdecl*/ **)(int, int, int, int, int))(v17 + 80))(dword_79C0B0, nArg2, nArg3 - i - 15, -1, pThis_7A02);
        }
        ++v15;
      }
    }
    LOBYTE(pThis_154) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  }
  return (char)pThis_154;
}


// ------------------------------------------------------------
// 0x4DB0E0 sub_4DB0E0 —— ★ 技能/被动标签查询（"是否持有某 id"；id 从 261396 段到 196625）
// 遍历 this+1952 vector（4 字节 id 数组）线性查找。**全库高频判据**：
//   261396..261402 → 0x4DB480 反击/架招档位表（3/11/15/0/6/2/5）
//   196616 → 0x4DCC60 技能施加强度 PVP 修正门
//   196612..196615 → 0x4DC390 伤害类型映射（attackinfo+20 = 0/1/3/2 → 4 个 id）
//   65281/130816 → 0x4DC390 魔法/物理分类
//   196625 → 0x4DB230 落点/位移修正
//   131091 → 0x4E4430 死亡终局（BOSS 终极表现）
// 这些 id 疑为"技能/被动效果 id"【待验证：id 空间分段规则】。
// ------------------------------------------------------------
char /*thiscall*/ sub_4DB0E0(uint32_t *this, int nArg2)
{
  int fld_e1952; // esi
  unsigned int i; // edx

  fld_e1952 = *(this + 1952);
  for ( i = 0; fld_e1952 != 0 && i < (*(this + 1953) - fld_e1952) >> 2; ++i )
  {
    if ( *(uint32_t *)(*(this + 1952) + 4 * i) == nArg2 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4DB130 sub_4DB130
// ------------------------------------------------------------
int /*thiscall*/ sub_4DB130(uint32_t *this, int pArg2, unsigned int uArg3)
{
  int result; // eax
  int v5; // ecx
  char *v6; // edi
  int v7; // ebx
  int v8; // ebx
  int v9; // eax
  unsigned int nRand; // edx
  unsigned int v11; // edi
  int v12; // eax
  const CHAR *pThis_4; // [esp-Ch] [ebp-14h]

  result = 16 * (pArg2 + 489);
  v5 = *(uint32_t *)((char *)this + result + 4);
  v6 = (char *)this + result;
  if ( v5 != 0 )
  {
    result = (*((uint32_t *)v6 + 2) - v5) >> 2;
    if ( result != 0 )
    {
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + v7;
      v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
      srand(v9 + v8);
      nRand = uArg3;
      result = *((uint32_t *)v6 + 1);
      if ( uArg3 == -1 )
      {
        if ( result != 0 )
        {
          v11 = (*((uint32_t *)v6 + 2) - result) >> 2;
          nRand = rand() % v11;
        }
        else
        {
          nRand = rand() % 0u;
        }
LABEL_9:
        pThis_4 = sub_41ACF0((unsigned int **)(*(this + 4 * pArg2 + 1957) + 4 * nRand));
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 64))(this);
        return sub_50EF20(v12, pThis_4, 0, -1);
      }
      if ( result != 0 && uArg3 < (*((uint32_t *)v6 + 2) - result) >> 2 )
        goto LABEL_9;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DB200 sub_4DB200
// ------------------------------------------------------------
int /*thiscall*/ sub_4DB200(uint32_t *this, int nArg2, unsigned int uArg3)
{
  int nRand; // eax
  int result; // eax
  int v6; // et2

  nRand = rand();
  v6 = nRand % 100;
  result = nRand / 100;
  if ( v6 < 15 )
    return sub_4DB130(this, nArg2, uArg3);
  return result;
}



// ------------------------------------------------------------
// 0x4DB230 sub_4DB230
// ------------------------------------------------------------
int /*userpurge*/ sub_4DB230@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4)
{
  int result; // eax
  int v6; // eax
  uint64_t v7; // rax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // edx
  int v13; // eax
  uint64_t v14; // rax
  int v15; // eax
  int v16; // eax
  int v17; // edi
  int64_t v18; // rax
  int v20; // [esp+4h] [ebp-8h]
  int v21; // [esp+8h] [ebp-4h]
  int v22; // [esp+8h] [ebp-4h]

  result = pArg1[1943];
  if ( result == 3 || result == 1 || result == 2 )
  {
    if ( pArg1[2129] == -1 && pArg1[2130] == -1 )
    {
      if ( result == 3 )
      {
        v6 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0);
        v20 = sub_41A5E0(v6 + 760);
        v7 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1) * 0.15000001 + (double)v20);
        pArg1[2129] = v7;
        v8 = (*(int (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t))(*pArg1 + 672))(pArg1, HIDWORD(v7), 0);
        v21 = sub_41A5E0(v8 + 760);
        pArg1[2130] = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1) * 0.60000002
                                    + (double)v21);
      }
      v9 = pArg1[1943];
      if ( v9 == 1 || v9 == 2 )
      {
        if ( sub_4DB0E0(pArg1, 196625) != 0 )
        {
          v10 = (*(int (/*stdcall*/ **)(uint32_t))(*pArg1 + 672))(0);
          v11 = sub_41A5E0(v10 + 760);
          v12 = *pArg1;
          pArg1[2129] = v11;
          v13 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v12 + 672))(pArg1, 0);
          v22 = sub_41A5E0(v13 + 760);
          v14 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1) * 0.30000001 + (double)v22);
        }
        else
        {
          v15 = (*(int (/*stdcall*/ **)(uint32_t))(*pArg1 + 672))(0);
          pArg1[2129] = sub_41A5E0(v15 + 760);
          v16 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0);
          LODWORD(v14) = sub_41A5E0(v16 + 760);
        }
        pArg1[2130] = v14;
      }
    }
    if ( nArg3 != 0 )
    {
      v17 = pArg1[2129];
      v18 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t, int))*(uint32_t *)(*pArg1 + 672))(pArg1, 0, nArg2);
    }
    else
    {
      v17 = pArg1[2130];
      LODWORD(v18) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 672))(pArg1, 0, nArg2);
    }
    sub_41A590(v18 + 760, SHIDWORD(v18), v17);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 676))(pArg1, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DB3F0 sub_4DB3F0
// ------------------------------------------------------------
char */*stdcall*/ sub_4DB3F0(char *pszArg1, char *pszArg2, char *pszArg3)
{
  return sub_4DA820(pszArg1, pszArg2, pszArg3);
}



// ------------------------------------------------------------
// 0x4DB410 sub_4DB410
// ------------------------------------------------------------
int /*thiscall*/ sub_4DB410(void *this, int ArgList, int nArg3)
{
  int v3; // edi
  int v5; // eax
  int v7; // [esp+8h] [ebp-4h] BYREF

  v3 = ArgList;
  sub_442D00(&v7, &ArgList);
  if ( v7 == dword_9B7C34 )
    return off_77F3FC("MONSTER CREATE FAIL! INDEX %d", v3);
  v5 = *(uint32_t *)(v7 + 40) < 0x10u ? v7 + 20 : *(uint32_t *)(v7 + 20);
  if ( v5 == 0 )
    return off_77F3FC("MONSTER CREATE FAIL! INDEX %d", v3);
  else
    return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 1196))(this, v5, nArg3);
}



// ------------------------------------------------------------
// 0x4DB480 sub_4DB480 —— ★ 反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
// 前置：+7772（反击态 1/2）+ 受方条件 17 + vt+308 门。
// 架招档位表（by id，逐条 if-else 查找 this+1952 标签 vector）：
//   261396 → 3 ；261397 → 11 ；261398 → 15 ；261399 → 0 ；261400 → 6 ；261401 → 2 ；261402 → 5
// 档位 = (vt+672(3) 值 / 10) + 1；sub_4D6750(id, 20.0f, 0) 概率门通过 → vt+764 施加。
// 尾调 **sub_4D6D90(this, a2, a3, a4)** = 走攻方完整反应（研究 §8 双向卡肉入口）——
// 即"架招成功 = 攻方走完整反应用"这一语义的代码直证。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DB480(int this, uint32_t *pArg2, int nArg3, int nArg4)
{
  int fld_1E5C; // eax
  int v6; // edi
  int pThis_2A0; // ebx
  int v8; // edi
  int fld_1BEC; // eax

  fld_1E5C = *(uint32_t *)(this + 7772);
  if ( (fld_1E5C == 1 || fld_1E5C == 2)
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
  {
    if ( sub_4DB0E0((uint32_t *)this, 261396) != 0 )
    {
      v6 = 3;
    }
    else if ( sub_4DB0E0((uint32_t *)this, 261397) != 0 )
    {
      v6 = 11;
    }
    else if ( sub_4DB0E0((uint32_t *)this, 261398) != 0 )
    {
      v6 = 15;
    }
    else if ( sub_4DB0E0((uint32_t *)this, 261399) != 0 )
    {
      v6 = 0;
    }
    else if ( sub_4DB0E0((uint32_t *)this, 261400) != 0 )
    {
      v6 = 6;
    }
    else if ( sub_4DB0E0((uint32_t *)this, 261401) != 0 )
    {
      v6 = 2;
    }
    else
    {
      if ( sub_4DB0E0((uint32_t *)this, 261402) == 0 )
        goto LABEL_21;
      v6 = 5;
    }
    pThis_2A0 = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 672))(this, 3) / 10 + 1;
    if ( sub_4D6750(pArg2, v6, 20.0, nullptr) )
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*pArg2 + 764))(pArg2, v6, pThis_2A0, this, 1);
  }
LABEL_21:
  v8 = sub_4D6D90((int *)this, pArg2, nArg3, nArg4);  // 【攻方完整反应 vt+500（§8 双向卡肉入口）】
  if ( *(uint8_t *)(this + 7529) != 0 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1236))(this);
  fld_1BEC = *(uint32_t *)(this + 7148);
  if ( fld_1BEC == 11 || fld_1BEC == 12 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 4);
  return v8;
}



// ------------------------------------------------------------
// 0x4DB600 sub_4DB600
// ------------------------------------------------------------
bool /*thiscall*/ sub_4DB600(uint32_t *this, unsigned int pArg2, int nArg3)
{
  int v5; // ebx
  int fld_e1550; // ecx
  int fld_e1905; // ecx
  int fld_e19052; // ecx
  int v9; // edx
  uint32_t *v10; // eax
  int v11; // ecx
  int v12; // ebx
  int v13; // eax
  int v14; // ebx
  int v15; // ebx
  int v16; // ebx
  int v17; // ebx
  int v19; // ebx
  int v20; // ebx
  int v21; // ebx
  int v22; // ebx
  int v23; // ebx
  int v24; // ebx
  int v25; // ebx
  int v26; // esi
  int v27; // [esp+Ch] [ebp-Ch]
  int v28; // [esp+10h] [ebp-8h]
  int v29; // [esp+20h] [ebp+8h]
  int v30; // [esp+24h] [ebp+Ch]

  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 376))(nArg3);
  if ( v5 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 40))(nArg3, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 940))(nArg3) == 1 )
  {
    return false;
  }
  fld_e1550 = *(this + 1550);
  if ( fld_e1550 == 0 )
    return false;
  if ( (*(this + 1551) - fld_e1550) >> 2 <= pArg2 )
    return false;
  fld_e1905 = *(this + 1905);
  if ( fld_e1905 == 0 )
    return false;
  if ( (*(this + 1906) - fld_e1905) >> 5 <= pArg2 )
    return false;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, nArg3) == 0 )
    return false;
  fld_e19052 = *(this + 1905);
  v9 = *(uint32_t *)(fld_e19052 + 32 * pArg2 + 16);
  v10 = (uint32_t *)(fld_e19052 + 32 * pArg2);
  v11 = v10[5];
  v12 = v10[6];
  v13 = v10[7];
  v30 = v11;
  v29 = v9;
  v28 = v12;
  v27 = v13;
  if ( v11 == 0 && v9 == 0 )
    return false;
  if ( v12 == 0 && v13 == 0 )
    return false;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )
  {
    v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 428))(nArg3) / 4;
    v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3) + v19;
    if ( v20 < (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v30 )
      return false;
    v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 428))(nArg3) / 4;
    v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3) - v21;
    if ( v22 > v29 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) )
      return false;
  }
  else
  {
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 428))(nArg3) / 4;
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3) - v14;
    if ( v15 > v30 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) )
      return false;
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 428))(nArg3) / 4;
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3) + v16;
    if ( v17 < (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v29 )
      return false;
  }
  v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 432))(nArg3) / 4;
  v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 124))(nArg3) + v23;
  if ( v24 < (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) - v28 )
    return false;
  v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 432))(nArg3) / 4;
  v26 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 124))(nArg3) - v25;
  return v26 <= v27 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
}



// ------------------------------------------------------------
// 0x4DB810 sub_4DB810
// ------------------------------------------------------------
bool /*thiscall*/ sub_4DB810(uint32_t *this, unsigned int pArg2)
{
  unsigned int v3; // ebx
  int fld_e29; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int pObj2; // ecx
  char v9; // al
  int fld_e292; // ecx
  int v11; // edx
  uint32_t *v12; // edi
  int fld_e1576; // eax
  char v14; // bl
  int fld_e15762; // edx
  int fld_e1905; // edi
  int pObj; // ecx
  int fld_e293; // ecx
  int v19; // edx
  int v20; // edi
  int fld_e19052; // edi
  int fld_e19053; // esi
  unsigned int v24; // [esp+10h] [ebp-4h]

  v3 = 0;
  while ( 1 )
  {
    fld_e29 = *(this + 29);
    v5 = *(uint32_t *)(fld_e29 + 120);
    v24 = v3;
    v6 = v5 != 0 ? (*(uint32_t *)(fld_e29 + 124) - v5) >> 2 : 0;
    if ( (int)v3 >= v6 )
      break;
    v7 = *(uint32_t *)(fld_e29 + 120);
    if ( v7 != 0 && v3 < (*(uint32_t *)(fld_e29 + 124) - v7) >> 2 )
      pObj2 = *(uint32_t *)(v7 + 4 * v3);
    else
      pObj2 = 0;
    v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17);
    fld_e292 = *(this + 29);
    v11 = *(uint32_t *)(fld_e292 + 120);
    if ( v9 != 0 )
    {
      if ( v11 != 0 && v3 < (*(uint32_t *)(fld_e292 + 124) - v11) >> 2 )
        v12 = *(uint32_t **)(v11 + 4 * v3);
      else
        v12 = nullptr;
      if ( v12 != this )
      {
        fld_e1576 = *(this + 1576);
        v14 = 0;
        if ( (fld_e1576 == 0
           || (*(this + 1577) - fld_e1576) / 152 <= pArg2
           || (fld_e15762 = *(this + 1576), v14 = *(uint8_t *)(fld_e15762 + 152 * pArg2 + 18), *(uint8_t *)(fld_e15762 + 152 * pArg2 + 19) != 0))
          && (uint8_t)sub_4E4630(v12) != 0
          || v14 != 0 && (uint8_t)sub_4E4630(v12) == 0 )
        {
          if ( (uint8_t)sub_4E5CA0(v12) == 0
            && ((*(int (/*thiscall*/ **)(uint32_t *))(*v12 + 840))(v12) != 4
             || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v12 + 776))(v12, 8) != 0)
            && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v12 + 724))(v12) == 0
            && (*(uint8_t (/*thiscall*/ **)(uint32_t *, unsigned int, uint32_t *))(*this + 1248))(this, pArg2, v12) != 0 )
          {
            fld_e1905 = *(this + 1905) + 32 * pArg2;
            if ( *(float *)(fld_e1905 + 4) * 100.0 > (double)(rand() % 10000) )
              return true;
          }
        }
        v3 = v24;
      }
LABEL_29:
      ++v3;
    }
    else
    {
      if ( v11 != 0 && v3 < (*(uint32_t *)(fld_e292 + 124) - v11) >> 2 )
        pObj = *(uint32_t *)(*(uint32_t *)(fld_e292 + 120) + 4 * v3);
      else
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 545) == 0 )
        goto LABEL_29;
      fld_e293 = *(this + 29);
      v19 = *(uint32_t *)(fld_e293 + 120);
      if ( v19 != 0 && v3 < (*(uint32_t *)(fld_e293 + 124) - v19) >> 2 )
        v20 = *(uint32_t *)(v19 + 4 * v3);
      else
        v20 = 0;
      if ( (uint8_t)sub_4E4630(v20) == 0
        || (*(uint8_t (/*thiscall*/ **)(uint32_t *, unsigned int, int))(*this + 1248))(this, pArg2, v20) == 0 )
      {
        goto LABEL_29;
      }
      fld_e19052 = *(this + 1905) + 32 * pArg2;
      if ( *(float *)(fld_e19052 + 12) * 100.0 > (double)(rand() % 10000) )
        return true;
      ++v3;
    }
  }
  fld_e19053 = *(this + 1905) + 32 * pArg2;
  return *(float *)(fld_e19053 + 8) * 100.0 > (double)(rand() % 10000);
}



// ------------------------------------------------------------
// 0x4DBA80 sub_4DBA80
// ------------------------------------------------------------
int /*thiscall*/ sub_4DBA80(int *this, int pArg2)
{
  unsigned int v3; // ecx
  int i; // edi
  int fld_e1905; // edx
  int v6; // eax
  double v7; // st7
  int result; // eax

  *(this + 1926) = sub_699000((int)(this + 1910));
  switch ( pArg2 )
  {
    case 6:
      (*(void (/*thiscall*/ **)(int *))(*this + 1080))(this);
      break;
    case 9:
    case 10:
      *(this + 1899) = 50;
      v3 = 0;
      *(this + pArg2 + 1826) = 100;
      *(this + pArg2 + 1852) = 100;
      for ( i = 0; ; i += 32 )
      {
        fld_e1905 = *(this + 1905);
        if ( fld_e1905 == 0 || v3 >= (*(this + 1906) - fld_e1905) >> 5 )
          break;
        v6 = i + fld_e1905;
        v7 = *(float *)(fld_e1905 + i + 4) * 1.3;
        ++v3;
        *(float *)(v6 + 4) = v7;
      }
      break;
    case 12:
      *(this + 1880) = (uint64_t)((double)*(this + 1880) * 1.5);
      if ( sub_4DAB60(this, 14) || sub_4DAB60(this, 15) )
      {
        sub_49C620(this, 2, 1, 0);
        *(this + 1838) = 200;
      }
      break;
    case 14:
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 2, 0, 0, 0);
      break;
    case 15:
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
      break;
    case 24:
      *(this + 1850) = 200;
      break;
    default:
      break;
  }
  *(uint32_t *)(*(this + 1931) + 80) = *(this + pArg2 + 1826);
  result = *(this + pArg2 + 1852);
  *(uint32_t *)(*(this + 1931) + 84) = result;
  return result;
}



// ------------------------------------------------------------
// 0x4DBC20 sub_4DBC20
// ------------------------------------------------------------
int /*thiscall*/ sub_4DBC20(int *this, int pArg2)
{
  int v3; // edi
  unsigned int i; // ecx
  int fld_e1905; // edx
  int v6; // eax
  double v7; // st7
  int result; // eax

  switch ( pArg2 )
  {
    case 0:
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *))(*this + 1204))(this);
      break;
    case 9:
    case 10:
      v3 = 0;
      *(this + 1899) = 0;
      *(this + pArg2 + 1826) = 100;
      *(this + pArg2 + 1852) = 100;
      for ( i = 0; ; ++i )
      {
        fld_e1905 = *(this + 1905);
        if ( fld_e1905 == 0 || i >= (*(this + 1906) - fld_e1905) >> 5 )
          break;
        v6 = v3 + fld_e1905;
        v7 = *(float *)(fld_e1905 + v3 + 4) * 0.76923078;
        v3 += 32;
        *(float *)(v6 + 4) = v7;
      }
      break;
    case 12:
      *(this + 1880) = (uint64_t)((double)*(this + 1880) * 0.66666669);
      if ( sub_4DAB60(this, 14) || sub_4DAB60(this, 15) )
      {
        sub_49C620(this, 2, 0, 0);
        *(this + 1838) = 200;
      }
      break;
    case 14:
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
      break;
    case 24:
      *(this + 1850) = 200;
      break;
    default:
      break;
  }
  *(uint32_t *)(*(this + 1931) + 80) = -*(this + pArg2 + 1826);
  result = *(this + 1931);
  *(uint32_t *)(result + 84) = -*(this + pArg2 + 1852);
  return result;
}



// ------------------------------------------------------------
// 0x4DBDB0 sub_4DBDB0 —— ★ 空间栅格重叠检测（碰撞/挤压分离轴；研究第 24/25 轮族）
// 用动画盒 (=this+1905 加载的属性表，32 字节记录，+16/+24/+28 三向尺寸) 与参照对象
// vt+1813 的位置做**四方向重叠判定**（x 三档 0/1/4、y 三档 2/3/4 —— 0/1 与 2/3 表示
// 左右/上下越界，4 = 重叠）；
// 随后 16/12 取整算栅格坐标 (v10/16, v12/12) 与对方栅格 (v24/16, v23/12)，
// 调 sub_58AD30（栅格相交判定）→ 返回 1 时调 sub_58B200（栅格推挤解算，输出 v26/v25
// 为修正后坐标）→ 缓存到 +2080..2083 / +2078/+2079（previous frame 对比）。
// 与 0x4DC130（单向拒绝测试）、0x4D87B0（同族栅格调）配套 ——
// 这是**客户端本地的角色间推挤/防重叠**，与服务端命中判定无关（研究 §1.1 结论一致）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4DBDB0(int *this, uint32_t *uArg2, uint32_t *uArg3)
{
  int fld_e1813; // ecx
  int fld_e1905; // edx
  int fld_e19052; // edi
  int fld_e19053; // edi
  int fld_e19054; // edi
  int fld_e19055; // edi
  int v10; // kr04_4
  int v11; // edi
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int fld_e2082; // ecx
  int fld_e2083; // edx
  int fld_e1898; // ebx
  int v18; // [esp+4h] [ebp-14h]
  float v19; // [esp+8h] [ebp-10h]
  float fld_e18132; // [esp+8h] [ebp-10h]
  float fld_e18133; // [esp+8h] [ebp-10h]
  float fld_e18134; // [esp+8h] [ebp-10h]
  int fld_e18136; // [esp+8h] [ebp-10h]
  int fld_e18135; // [esp+Ch] [ebp-Ch]
  int fld_e20832; // [esp+10h] [ebp-8h] BYREF
  int fld_e20822; // [esp+14h] [ebp-4h] BYREF

  fld_e1813 = *(this + 1813);
  if ( fld_e1813 == 0 )
    return;
  fld_e1905 = *(this + 1905);
  if ( fld_e1905 == 0 || (*(this + 1906) - fld_e1905) >> 5 == 0 )
    return;
  fld_e19052 = *(this + 1905);
  v19 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813);
  if ( (double)(*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - (double)*(int *)(fld_e19052 + 16) * 0.75 <= v19 )
  {
    fld_e19053 = *(this + 1905);
    fld_e18132 = (float)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
    if ( (double)(*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + (double)*(int *)(fld_e19053 + 16) * 0.75 >= fld_e18132 )
      *uArg2 = 4;
    else
      *uArg2 = 1;
  }
  else
  {
    *uArg2 = 0;
  }
  fld_e19054 = *(this + 1905);
  fld_e18133 = (float)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
  v18 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  if ( (double)v18 - (double)*(int *)(fld_e19054 + 24) * 0.75 <= fld_e18133 )
  {
    fld_e19055 = *(this + 1905);
    fld_e18134 = (float)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
    v18 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    if ( (double)v18 + (double)*(int *)(fld_e19055 + 28) * 0.75 >= fld_e18134 )
      *uArg3 = 4;
    else
      *uArg3 = 3;
  }
  else
  {
    *uArg3 = 2;
  }
  v10 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
  v11 = v10 / 16;
  v12 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) / 12;
  fld_e18135 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)) / 16;
  fld_e18136 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813)) / 12;
  v13 = *this;
  fld_e20822 = v10 / 16;
  fld_e20832 = v12;
  LOBYTE(v18) = (*(int (/*thiscall*/ **)(int *))(v13 + 436))(this) > 0;
  v14 = sub_58AD30(fld_e18135, fld_e18136, v18);
  if ( (v10 / 16 != *(this + 2078)
     || v12 != *(this + 2079)
     || fld_e18135 != *(this + 2080)
     || fld_e18136 != *(this + 2081)
     || *(this + 2082) == -1
     || *(this + 2083) == -1)
    && v14 == 1 )
  {
    sub_58B200(v10 / 16, v12, fld_e18135, fld_e18136, &fld_e20822, &fld_e20832, v18);
    fld_e2082 = fld_e20822;
    fld_e2083 = fld_e20832;
    *(this + 2082) = fld_e20822;
    *(this + 2083) = fld_e2083;
LABEL_25:
    *(this + 2080) = fld_e18135;
    *(this + 2081) = fld_e18136;
    goto LABEL_26;
  }
  fld_e2082 = *(this + 2082);
  fld_e2083 = *(this + 2083);
  fld_e20822 = fld_e2082;
  fld_e20832 = fld_e2083;
  if ( v14 != 0 )
  {
    if ( v14 == 1 )
      goto LABEL_25;
  }
  else
  {
    sub_58B200(v10 / 16, v12, *(this + 2080), *(this + 2081), &fld_e20822, &fld_e20832, v18);
    fld_e2082 = fld_e20822;
    fld_e2083 = fld_e20832;
    *(this + 2082) = fld_e20822;
    *(this + 2083) = fld_e2083;
  }
LABEL_26:
  *(this + 2078) = v11;
  *(this + 2079) = v12;
  *(this + 2082) = fld_e2082;
  *(this + 2083) = fld_e2083;
  if ( v11 >= fld_e2082 )
    *uArg2 = v11 > fld_e2082 ? 0 : 4;
  else
    *uArg2 = 1;
  if ( v12 <= fld_e2083 )
    *uArg3 = (v12 >= fld_e2083) + 3;
  else
    *uArg3 = 2;
  if ( (uint8_t)sub_4E4630(*(this + 1813)) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1108))(this) == 0 )
  {
    fld_e1898 = *(this + 1898) + *(this + 1899);
    if ( rand() % 100 >= fld_e1898 )
    {
      *uArg2 = sub_432E50(*uArg2);
      *uArg3 = sub_432E50(*uArg3);
    }
  }
}


// ------------------------------------------------------------
// 0x4DC130 sub_4DC130
// ------------------------------------------------------------
void /*thiscall*/ sub_4DC130(uint32_t *this, int nArg2, uint32_t *uArg3, uint32_t *uArg4)
{
  int fld_e1905; // ecx
  int fld_e19053; // edi
  int v7; // ebx
  int v8; // eax
  int fld_e19052; // ebx
  int v10; // esi

  fld_e1905 = *(this + 1905);
  if ( fld_e1905 != 0 && (*(this + 1906) - fld_e1905) >> 5 != 0 )
  {
    fld_e19053 = fld_e1905;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    v8 = *(uint32_t *)(fld_e19053 + 16);
    *uArg3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2) > v8 / 2 + v7;
    fld_e19052 = *(this + 1905);
    v10 = *(uint32_t *)(fld_e19052 + 24) / 2 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    *uArg4 = ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2) > v10) + 2;
  }
}



// ------------------------------------------------------------
// 0x4DC1C0 sub_4DC1C0
// ------------------------------------------------------------
void /*thiscall*/ sub_4DC1C0(uint32_t *this)
{
  unsigned int v1; // edi
  int i; // ebx
  int fld_e1905; // ecx
  uint32_t *fld_e19052; // eax

  v1 = 0;
  for ( i = 0; ; i += 32 )
  {
    fld_e1905 = *(this + 1905);
    if ( fld_e1905 == 0 || v1 >= (*(this + 1906) - fld_e1905) >> 5 )
      break;
    fld_e19052 = (uint32_t *)(i + *(this + 1905));
    if ( *(uint32_t *)(fld_e1905 + i + 16) == 0 && fld_e19052[6] == 0 && fld_e19052[7] == 0 && fld_e19052[5] == 0 )
      (*(void (/*thiscall*/ **)(uint32_t *, unsigned int))(*this + 1212))(this, v1);
    ++v1;
  }
}



// ------------------------------------------------------------
// 0x4DC220 sub_4DC220
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4DC220(unsigned int *this)
{
  int v1; // eax
  unsigned int result; // eax
  int fld_e1809; // edi
  int v5; // eax
  unsigned int v6; // esi
  uint64_t v7; // rax
  int v8; // edi
  float v9; // [esp+Ch] [ebp-10h]
  int v10; // [esp+14h] [ebp-8h]
  unsigned int i; // [esp+18h] [ebp-4h]

  v1 = 0;
  for ( i = 0; ; ++i )
  {
    v10 = v1;
    result = *(this + 1809);
    if ( result == 0 )
      break;
    result = (int)(*(this + 1810) - result) / 12;
    if ( i >= result )
      break;
    fld_e1809 = v10 + *(this + 1809);
    v5 = (*(int (/*thiscall*/ **)(unsigned int *, uint32_t))(*this + 672))(this, 0);
    switch ( *(uint32_t *)fld_e1809 )
    {
      case 0:
        v6 = v5 + 844;
        goto LABEL_18;
      case 1:
        v6 = v5 + 816;
        goto LABEL_18;
      case 2:
        v6 = v5 + 60;
        goto LABEL_18;
      case 3:
        v6 = v5 + 88;
        goto LABEL_18;
      case 4:
        v6 = v5 + 116;
        goto LABEL_18;
      case 5:
        v6 = v5 + 144;
        goto LABEL_18;
      case 6:
        v6 = v5 + 1012;
        goto LABEL_18;
      case 7:
        v6 = v5 + 1040;
        goto LABEL_18;
      case 8:
        v6 = v5 + 1068;
        goto LABEL_18;
      case 9:
        v6 = v5 + 1096;
        goto LABEL_18;
      case 0xA:
        v6 = v5 + 4;
        goto LABEL_18;
      case 0xB:
        v6 = v5 + 900;
        goto LABEL_18;
      case 0xC:
        v6 = v5 + 466;
LABEL_18:
        if ( v6 != 0 )
        {
          if ( *(uint8_t *)(fld_e1809 + 4) != 0 )
          {
            v9 = (double)*(int *)(fld_e1809 + 8) * 0.0099999998;
            v7 = (uint64_t)((double)sub_41A5E0(v6) * v9);
          }
          else
          {
            v8 = *(uint32_t *)(fld_e1809 + 8) / 100;
            LODWORD(v7) = v8 + sub_41A5E0(v6);
          }
          sub_41A590(v6, SHIDWORD(v7), v7);
        }
        break;
      default:
        break;
    }
    v1 = v10 + 12;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DC390 sub_4DC390
// ------------------------------------------------------------
int /*thiscall*/ sub_4DC390(uint8_t *this, uint32_t *uArg2, int nArg3)
{
  int result; // eax
  int v6; // [esp+18h] [ebp+Ch]

  result = sub_4D5A60(this, uArg2, nArg3);
  v6 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12) == 1 && sub_4DB0E0(this, 130816) != 0
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12) == 0 && sub_4DB0E0(this, 65281) != 0
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 20) == 0 && sub_4DB0E0(this, 196612) != 0
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 20) == 1 && sub_4DB0E0(this, 196613) != 0
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 20) == 3 && sub_4DB0E0(this, 196614) != 0
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 20) == 2 && sub_4DB0E0(this, 196615) != 0 )
    {
      *uArg2 = 0;
      return 2;
    }
    else if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 128) != 0 || !sub_4DAB60(this, 6) )
    {
      return v6;
    }
    else
    {
      return 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DC4D0 sub_4DC4D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4DC4D0(uint32_t *this, int nArg2)
{
  uint32_t *pThis; // ebx
  unsigned int v3; // edi
  int v4; // ecx
  int v5; // edx
  int result; // eax
  int v7; // edx
  int pObj2; // ecx
  char v9; // al
  int v10; // ecx
  int v11; // edx
  int pObj; // esi
  int v13; // ebx
  int pObj3; // ecx
  int v15; // ecx
  int v16; // edx
  uint32_t *v17; // esi
  int v18; // ebx

  pThis = this;
  v3 = 0;
  while ( 1 )
  {
    v4 = pThis[29];
    v5 = *(uint32_t *)(v4 + 8);
    result = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;
    if ( (int)v3 >= result )
      return result;
    v7 = *(uint32_t *)(v4 + 8);
    if ( v7 != 0 && v3 < (*(uint32_t *)(v4 + 12) - v7) >> 2 )
      pObj2 = *(uint32_t *)(v7 + 4 * v3);
    else
      pObj2 = 0;
    v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529);
    v10 = pThis[29];
    v11 = *(uint32_t *)(v10 + 8);
    if ( v9 != 0 )
    {
      if ( v11 != 0 && v3 < (*(uint32_t *)(v10 + 12) - v11) >> 2 )
        pObj = *(uint32_t *)(v11 + 4 * v3);
      else
        pObj = 0;
      v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2) != v13
        || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) == 0 )
      {
        goto LABEL_31;
      }
      (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t))(*(uint32_t *)pObj + 728))(pObj, 0, 1, 0);
      pThis = this;
      ++v3;
    }
    else
    {
      if ( v11 != 0 && v3 < (*(uint32_t *)(v10 + 12) - v11) >> 2 )
        pObj3 = *(uint32_t *)(*(uint32_t *)(v10 + 8) + 4 * v3);
      else
        pObj3 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 33) != 0 )
      {
        v15 = pThis[29];
        v16 = *(uint32_t *)(v15 + 8);
        if ( v16 != 0 && v3 < (*(uint32_t *)(v15 + 12) - v16) >> 2 )
          v17 = *(uint32_t **)(v16 + 4 * v3);
        else
          v17 = nullptr;
        if ( v17[169] == 1 )
        {
          v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*v17 + 376))(v17);
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2) == v18
            && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v17 + 308))(v17) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v17 + 312))(v17, 0);
          }
LABEL_31:
          pThis = this;
        }
      }
      ++v3;
    }
  }
}



// ------------------------------------------------------------
// 0x4DC630 sub_4DC630
// ------------------------------------------------------------
int /*thiscall*/ sub_4DC630(uint32_t *this)
{
  int fld_e1815; // eax
  int result; // eax
  int v4; // eax
  int v5; // eax
  int v6; // [esp+4h] [ebp-10h] BYREF
  uint16_t v7; // [esp+8h] [ebp-Ch] BYREF
  uint16_t v8; // [esp+Ch] [ebp-8h] BYREF
  uint16_t v9; // [esp+10h] [ebp-4h] BYREF

  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v9);
  fld_e1815 = *(this + 1815);
  if ( fld_e1815 != 0 && (*(int (**)(void))(*(uint32_t *)fld_e1815 + 52))() == v9 )
  {
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v6);
    result = (uint16_t)v6;
    switch ( (uint16_t)v6 )
    {
      case 0xAu:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1272))(this, v6);
        break;
      case 0xBu:
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1268))(this);
        sub_4DB200(this, 23, 0xFFFFFFFF);
        return -1;
      case 0xCu:
        (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v7);
        (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v8);
        v4 = sub_45EBE0(v7, v8);
        v5 = __RTDynamicCast(v4, 0, &CNRDObject `RTTI Type Descriptor', &IRDCollisionObject `RTTI Type Descriptor', 0);
        if ( v5 != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1136))(this, v5);
          return -1;
        }
        break;
      default:
        return result;
    }
  }
  return -1;
}



// ------------------------------------------------------------
// 0x4DC730 sub_4DC730
// ------------------------------------------------------------
void /*thiscall*/ sub_4DC730(int *this)
{
  unsigned int i; // esi
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj3; // esi
  int v11; // ebx
  int v12; // eax
  int pObj2; // esi
  int v14; // ebx
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  int pObj4; // eax
  int v19; // esi
  int v20; // eax
  int v21; // esi
  int fld_e1814; // eax
  int v23; // esi
  int fld_e18142; // eax
  unsigned int v25; // [esp+4h] [ebp-4h]

  if ( *(this + 1814) != 0 )
  {
    for ( i = 0; ; ++i )
    {
      fld_e29 = *(this + 29);
      v4 = *(uint32_t *)(fld_e29 + 120);
      v25 = i;
      v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 124) - v4) >> 2 : 0;
      if ( (int)i >= v5 )
        break;
      v6 = *(uint32_t *)(fld_e29 + 120);
      if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 124) - v6) >> 2 )
        pObj = *(uint32_t *)(v6 + 4 * i);
      else
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )
      {
        fld_e292 = *(this + 29);
        v9 = *(uint32_t *)(fld_e292 + 120);
        if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 124) - v9) >> 2 )
          pObj3 = *(uint32_t *)(v9 + 4 * i);
        else
          pObj3 = 0;
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 376))(pObj3);
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 376))(this) == v11 && this != (int *)pObj3 )
        {
          v12 = __RTDynamicCast(
                  pObj3,
                  0,
                  &IRDCollisionObject `RTTI Type Descriptor',
                  &IRDMonster `RTTI Type Descriptor',
                  0);
          pObj2 = v12;
          if ( v12 != 0
            && *(uint32_t *)(v12 + 7772) != 3
            && (*(this + 1943) == 3 || (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 1244))(this, v12) != 0)
            && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 304))(pObj2) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
            v14 = *(uint32_t *)dword_8F8520;
            v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);
            (*(void (/*thiscall*/ **)(int, int))(v14 + 36))(dword_8F8520, v15);
            v16 = *(uint32_t *)dword_8F8520;
            v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);
            (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);
            pObj4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 304))(pObj2);
            v19 = *(uint32_t *)dword_8F8520;
            v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 52))(pObj4);
            (*(void (/*thiscall*/ **)(int, int))(v19 + 36))(dword_8F8520, v20);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 11);
            v21 = *(uint32_t *)dword_8F8520;
            fld_e1814 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1814) + 48))(*(this + 1814));
            (*(void (/*thiscall*/ **)(int, int))(v21 + 36))(dword_8F8520, fld_e1814);
            v23 = *(uint32_t *)dword_8F8520;
            fld_e18142 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1814) + 52))(*(this + 1814));
            (*(void (/*thiscall*/ **)(int, int))(v23 + 36))(dword_8F8520, fld_e18142);
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
          }
        }
        i = v25;
      }
    }
    sub_4D83E0(this, 0, 0);
  }
}



// ------------------------------------------------------------
// 0x4DC920 sub_4DC920
// ------------------------------------------------------------
int /*thiscall*/ sub_4DC920(uint32_t *this, uint32_t *uArg2, uint32_t *uArg3)
{
  unsigned int v3; // edi
  uint32_t *pThis; // esi
  int v5; // ebx
  int v6; // ecx
  int v7; // edx
  int result; // eax
  int v9; // edx
  int pObj2; // ecx
  int v11; // ecx
  int v12; // edx
  int pObj; // esi
  int v14; // edi
  int v15; // edi
  int v16; // [esp+Ch] [ebp-10h]
  unsigned int v18; // [esp+14h] [ebp-8h]
  int v19; // [esp+18h] [ebp-4h]

  v3 = 0;
  pThis = this;
  v19 = 0;
  v5 = 0;
  v16 = 1;
  while ( 1 )
  {
    v6 = pThis[29];
    v7 = *(uint32_t *)(v6 + 120);
    v18 = v3;
    result = v7 != 0 ? (*(uint32_t *)(v6 + 124) - v7) >> 2 : 0;
    if ( (int)v3 >= result )
      return result;
    v9 = *(uint32_t *)(v6 + 120);
    if ( v9 != 0 && v3 < (*(uint32_t *)(v6 + 124) - v9) >> 2 )
      pObj2 = *(uint32_t *)(v9 + 4 * v3);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0 )
      goto LABEL_30;
    v11 = pThis[29];
    v12 = *(uint32_t *)(v11 + 120);
    if ( v12 != 0 && v3 < (*(uint32_t *)(v11 + 124) - v12) >> 2 )
      pObj = *(uint32_t *)(v12 + 4 * v3);
    else
      pObj = 0;
    if ( (uint8_t)sub_4E4630(pObj) == 0
      || (uint8_t)sub_4E5CA0(pObj) != 0
      || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj) == 0 )
    {
      goto LABEL_30;
    }
    if ( v16 == 1 )
    {
      v19 = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);
      v5 = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);
      *uArg2 = pObj;
      *uArg3 = pObj;
      pThis = this;
      v16 = 0;
      ++v3;
    }
    else
    {
      v14 = v19;
      if ( v19 >= *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3) )
        v14 = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);
      if ( v14 == *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3) )
      {
        *uArg2 = pObj;
        v19 = v14;
      }
      if ( v5 <= *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3) )
        v15 = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);
      else
        v15 = v5;
      if ( v15 == *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3) )
      {
        *uArg3 = pObj;
        v5 = v15;
      }
      v3 = v18;
LABEL_30:
      pThis = this;
      ++v3;
    }
  }
}



// ------------------------------------------------------------
// 0x4DCAB0 sub_4DCAB0
// ------------------------------------------------------------
int /*thiscall*/ sub_4DCAB0(uint32_t *this, uint32_t *uArg2, uint32_t *uArg3)
{
  unsigned int v3; // ebx
  uint32_t *pThis; // edi
  int v5; // ecx
  int v6; // edx
  int result; // eax
  int v8; // edx
  int pObj; // ecx
  int v10; // ecx
  int v11; // edx
  int pObj2; // esi
  unsigned int v13; // eax
  unsigned int v14; // eax
  unsigned int v15; // eax
  int v16; // edi
  unsigned int v17; // eax
  unsigned int v18; // eax
  unsigned int v19; // eax
  int v20; // edi
  unsigned int v21; // eax
  unsigned int v22; // eax
  int v24; // [esp+10h] [ebp-Ch]
  int v25; // [esp+14h] [ebp-8h]
  int v26; // [esp+18h] [ebp-4h]

  v3 = 0;
  pThis = this;
  v26 = 0;
  v25 = 0;
  v24 = 1;
  while ( 1 )
  {
    v5 = pThis[29];
    v6 = *(uint32_t *)(v5 + 120);
    result = v6 != 0 ? (*(uint32_t *)(v5 + 124) - v6) >> 2 : 0;
    if ( (int)v3 >= result )
      return result;
    v8 = *(uint32_t *)(v5 + 120);
    if ( v8 != 0 && v3 < (*(uint32_t *)(v5 + 124) - v8) >> 2 )
      pObj = *(uint32_t *)(v8 + 4 * v3);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) == 0 )
      goto LABEL_29;
    v10 = pThis[29];
    v11 = *(uint32_t *)(v10 + 120);
    if ( v11 != 0 && v3 < (*(uint32_t *)(v10 + 124) - v11) >> 2 )
      pObj2 = *(uint32_t *)(v11 + 4 * v3);
    else
      pObj2 = 0;
    if ( (uint8_t)sub_4E4630(pObj2) == 0
      || (uint8_t)sub_4E5CA0(pObj2) != 0
      || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pThis + 1244))(pThis, pObj2) == 0 )
    {
      goto LABEL_29;
    }
    if ( v24 == 1 )
    {
      v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 684))(pObj2);
      v26 = sub_41A5E0(v13);
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 684))(pObj2);
      v25 = sub_41A5E0(v14);
      *uArg2 = pObj2;
      *uArg3 = pObj2;
      v24 = 0;
      ++v3;
    }
    else
    {
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 684))(pObj2);
      v16 = v26;
      if ( v26 >= sub_41A5E0(v15) )
      {
        v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 684))(pObj2);
        v16 = sub_41A5E0(v17);
      }
      v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 684))(pObj2);
      if ( v16 == sub_41A5E0(v18) )
      {
        *uArg2 = pObj2;
        v26 = v16;
      }
      v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 684))(pObj2);
      v20 = v25;
      if ( v25 <= sub_41A5E0(v19) )
      {
        v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 684))(pObj2);
        v20 = sub_41A5E0(v21);
      }
      v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 684))(pObj2);
      if ( v20 == sub_41A5E0(v22) )
      {
        *uArg3 = pObj2;
        v25 = v20;
      }
      pThis = this;
LABEL_29:
      ++v3;
    }
  }
}



// ------------------------------------------------------------
// 0x4DCC60 sub_4DCC60
// ------------------------------------------------------------
char /*thiscall*/ sub_4DCC60(uint32_t *this, int nArg2, float fArg3, int nArg4, int nArg5)
{
  char result; // al
  void *v6; // ecx

  if ( *(this + 1943) == 3 )
    fArg3 = fArg3 * 0.1;
  result = sub_4DB0E0(this, 196616);
  if ( result == 0 )
    return sub_4D6910(v6, nArg2, fArg3, nArg4, nArg5, 0);
  return result;
}



// ------------------------------------------------------------
// 0x4DCCB0 sub_4DCCB0
// ------------------------------------------------------------
int /*thiscall*/ sub_4DCCB0(int *this, int pArg2, int nArg3, float fArg4)
{
  int pObj; // ebx
  uint32_t *v6; // edi
  int v7; // edx
  int v8; // ebx
  bool v9; // cc
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // edx
  float fArg42; // ecx
  int fld_e1894; // eax
  int v16; // eax
  int v17; // edx
  int v18; // ebx
  int v19; // ebx
  double v20; // st7
  int v21; // eax
  int v22; // edx
  int v23; // ebx
  int v24; // ebx
  int fld_e1895; // eax
  int v26; // eax
  int v27; // edx
  int v28; // ebx
  int v29; // ebx
  double v30; // st7
  int v31; // eax
  int v32; // edx
  int v33; // ebx
  int v34; // ebx
  int fld_e1896; // eax
  int v36; // eax
  int v37; // edx
  int v38; // ebx
  int v39; // ebx
  double v40; // st7
  int v41; // eax
  int v42; // edx
  int v43; // ebx
  int v44; // ebx
  int fld_e1897; // eax
  int v46; // eax
  int v47; // edx
  int v48; // ebx
  int v49; // ebx
  double v50; // st7
  int v51; // eax
  int v52; // edx
  int v53; // ebx
  int v54; // ebx
  int v55; // eax
  int v56; // edx
  int v57; // ebx
  int v58; // ebx
  uint64_t v59; // rax
  int v60; // eax
  uint64_t v61; // rax
  int result; // eax
  int nArg32; // [esp-8h] [ebp-2Ch]
  float v64; // [esp+Ch] [ebp-18h]
  int v65; // [esp+Ch] [ebp-18h]
  int v66; // [esp+Ch] [ebp-18h]
  int v67; // [esp+Ch] [ebp-18h]
  int v68; // [esp+Ch] [ebp-18h]
  int v69; // [esp+Ch] [ebp-18h]
  int v70; // [esp+Ch] [ebp-18h]
  int v71; // [esp+Ch] [ebp-18h]
  int v72; // [esp+Ch] [ebp-18h]
  int v73; // [esp+Ch] [ebp-18h]
  int v74; // [esp+10h] [ebp-14h]
  float v75; // [esp+10h] [ebp-14h]
  float v76; // [esp+10h] [ebp-14h]
  float v77; // [esp+10h] [ebp-14h]
  float v78; // [esp+10h] [ebp-14h]
  float v79; // [esp+10h] [ebp-14h]
  float v80; // [esp+10h] [ebp-14h]
  float v81; // [esp+10h] [ebp-14h]
  float v82; // [esp+10h] [ebp-14h]
  float v83; // [esp+14h] [ebp-10h]
  int v84; // [esp+14h] [ebp-10h]
  int v85; // [esp+14h] [ebp-10h]
  int v86; // [esp+14h] [ebp-10h]
  int v87; // [esp+14h] [ebp-10h]
  int v88; // [esp+14h] [ebp-10h]
  int v89; // [esp+14h] [ebp-10h]
  int v90; // [esp+14h] [ebp-10h]
  int v91; // [esp+14h] [ebp-10h]
  int v92; // [esp+18h] [ebp-Ch]
  float v93; // [esp+18h] [ebp-Ch]
  float v94; // [esp+18h] [ebp-Ch]
  float v95; // [esp+18h] [ebp-Ch]
  float v96; // [esp+18h] [ebp-Ch]
  float v97; // [esp+18h] [ebp-Ch]
  float v98; // [esp+18h] [ebp-Ch]
  float v99; // [esp+18h] [ebp-Ch]
  float v100; // [esp+18h] [ebp-Ch]
  int v101; // [esp+1Ch] [ebp-8h]
  int v102; // [esp+1Ch] [ebp-8h]
  int v103; // [esp+1Ch] [ebp-8h]
  int v104; // [esp+1Ch] [ebp-8h]
  int v105; // [esp+1Ch] [ebp-8h]
  int v106; // [esp+1Ch] [ebp-8h]
  int v107; // [esp+1Ch] [ebp-8h]
  int v108; // [esp+1Ch] [ebp-8h]
  int v109; // [esp+1Ch] [ebp-8h]
  int v110; // [esp+20h] [ebp-4h] BYREF

  pObj = nArg3;
  v6 = (uint32_t *)pArg2;
  nArg32 = nArg3;
  *(uint32_t *)pArg2 += *(this + 1814) != nArg3 ? 0 : 0x64;
  *(float *)&v110 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, nArg32, 0));
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 776))(this, 5) != 0 )
  {
    pArg2 = 10;
  }
  else
  {
    pArg2 = *(this + 1880);
    if ( *(float *)&pArg2 == 0.0 )
      pArg2 = 640;
  }
  *v6 += (uint64_t)sub_4049C0(100.0, 0.0, v110, (uint64_t)((double)pArg2 * 1.4));
  v7 = *this;
  HIBYTE(pArg2) = 0;
  if ( (*(int (/*thiscall*/ **)(int *))(v7 + 152))(this) == 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) <= v8;
    pObj = nArg3;
    if ( !v9 )
      HIBYTE(pArg2) = 1;
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 1
    && (v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj),
        v9 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < v10,
        pObj = nArg3,
        v9)
    || HIBYTE(pArg2) != 0 )
  {
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 160))(this, pObj);
    *v6 += (uint64_t)sub_4049C0(100.0, 50.0, v11, 300);
  }
  pArg2 = pObj;
  sub_4BE520(&v110, &pArg2);
  if ( v110 == *(this + 1902) )
    v12 = 0;
  else
    v12 = *(uint32_t *)(v110 + 16);
  v13 = v12 + *v6;
  *v6 = v13;
  fArg42 = fArg4;
  if ( *(this + 1893) == 2 && pObj == *(uint32_t *)(LODWORD(fArg4) + 20) )
    *v6 = v13 + 100;
  if ( *(this + 1893) == 1 && pObj == *(uint32_t *)(LODWORD(fArg42) + 16) )
    *v6 += 100;
  if ( *(this + 1891) == 1 && pObj == *(uint32_t *)LODWORD(fArg42) )
    *v6 += 100;
  if ( *(this + 1891) == 2 && pObj == *(uint32_t *)(LODWORD(fArg42) + 4) )
    *v6 += 100;
  if ( *(this + 1892) == 1 && pObj == *(uint32_t *)(LODWORD(fArg42) + 8) )
    *v6 += 100;
  if ( *(this + 1892) == 2 && pObj == *(uint32_t *)(LODWORD(fArg42) + 12) )
    *v6 += 100;
  fld_e1894 = *(this + 1894);
  if ( fld_e1894 == 1 )
  {
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 60));
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(pArg2 + 74));
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    v101 = sub_41A5E0(pArg2 + 60);
    *(float *)&v16 = COERCE_FLOAT(sub_41A5E0(pArg2 + 74));
    v17 = *(uint32_t *)pObj;
    pArg2 = v16;
    v18 = (*(int (/*thiscall*/ **)(int, int))(v17 + 672))(pObj, 3);
    v74 = sub_41A5E0(v18 + 60);
    v64 = COERCE_FLOAT(sub_41A5E0(v18 + 74));
    v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
    v92 = sub_41A5E0(v19 + 60);
    v83 = COERCE_FLOAT(sub_41A5E0(v19 + 74));
    v20 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            100.0,
            1.0,
            (unsigned int)(uint64_t)((double)v74 * v64) - (int)(uint64_t)((double)v92 * v83) / 2,
            2 * (unsigned int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&v110)
          - (int)(uint64_t)((double)v101 * *(float *)&pArg2) / 2);
  }
  else
  {
    if ( fld_e1894 != 2 )
      goto LABEL_38;
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    v65 = sub_41A5E0(pArg2 + 60);
    v75 = COERCE_FLOAT(sub_41A5E0(pArg2 + 74));
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 60));
    *(float *)&v21 = COERCE_FLOAT(sub_41A5E0(pArg2 + 74));
    v22 = *(uint32_t *)pObj;
    pArg2 = v21;
    v23 = (*(int (/*thiscall*/ **)(int, int))(v22 + 672))(pObj, 3);
    v102 = sub_41A5E0(v23 + 60);
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v23 + 74));
    v24 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
    v84 = sub_41A5E0(v24 + 60);
    v93 = COERCE_FLOAT(sub_41A5E0(v24 + 74));
    v20 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            1.0,
            100.0,
            (unsigned int)(uint64_t)((double)v102 * *(float *)&v110)
          - (int)(uint64_t)((double)v84 * v93) / 2,
            2 * (unsigned int)(uint64_t)((double)v65 * v75)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);
  }
  pObj = nArg3;
  *v6 += (uint64_t)v20;
LABEL_38:
  fld_e1895 = *(this + 1895);
  if ( fld_e1895 == 1 )
  {
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    v66 = sub_41A5E0(pArg2 + 88);
    v76 = COERCE_FLOAT(sub_41A5E0(pArg2 + 102));
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 88));
    *(float *)&v26 = COERCE_FLOAT(sub_41A5E0(pArg2 + 102));
    v27 = *(uint32_t *)pObj;
    pArg2 = v26;
    v28 = (*(int (/*thiscall*/ **)(int, int))(v27 + 672))(pObj, 3);
    v103 = sub_41A5E0(v28 + 88);
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v28 + 102));
    v29 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
    v85 = sub_41A5E0(v29 + 88);
    v94 = COERCE_FLOAT(sub_41A5E0(v29 + 102));
    v30 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            100.0,
            1.0,
            (unsigned int)(uint64_t)((double)v103 * *(float *)&v110)
          - (int)(uint64_t)((double)v85 * v94) / 2,
            2 * (unsigned int)(uint64_t)((double)v66 * v76)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);
  }
  else
  {
    if ( fld_e1895 != 2 )
      goto LABEL_43;
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    v67 = sub_41A5E0(pArg2 + 88);
    v77 = COERCE_FLOAT(sub_41A5E0(pArg2 + 102));
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 88));
    *(float *)&v31 = COERCE_FLOAT(sub_41A5E0(pArg2 + 102));
    v32 = *(uint32_t *)pObj;
    pArg2 = v31;
    v33 = (*(int (/*thiscall*/ **)(int, int))(v32 + 672))(pObj, 3);
    v104 = sub_41A5E0(v33 + 88);
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v33 + 102));
    v34 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
    v86 = sub_41A5E0(v34 + 88);
    v95 = COERCE_FLOAT(sub_41A5E0(v34 + 102));
    v30 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            1.0,
            100.0,
            (unsigned int)(uint64_t)((double)v104 * *(float *)&v110)
          - (int)(uint64_t)((double)v86 * v95) / 2,
            2 * (unsigned int)(uint64_t)((double)v67 * v77)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);
  }
  pObj = nArg3;
  *v6 += (uint64_t)v30;
LABEL_43:
  fld_e1896 = *(this + 1896);
  if ( fld_e1896 == 1 )
  {
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    v68 = sub_41A5E0(pArg2 + 116);
    v78 = COERCE_FLOAT(sub_41A5E0(pArg2 + 130));
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 116));
    *(float *)&v36 = COERCE_FLOAT(sub_41A5E0(pArg2 + 130));
    v37 = *(uint32_t *)pObj;
    pArg2 = v36;
    v38 = (*(int (/*thiscall*/ **)(int, int))(v37 + 672))(pObj, 3);
    v105 = sub_41A5E0(v38 + 116);
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v38 + 130));
    v39 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
    v87 = sub_41A5E0(v39 + 116);
    v96 = COERCE_FLOAT(sub_41A5E0(v39 + 130));
    v40 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            100.0,
            1.0,
            (unsigned int)(uint64_t)((double)v105 * *(float *)&v110)
          - (int)(uint64_t)((double)v87 * v96) / 2,
            2 * (unsigned int)(uint64_t)((double)v68 * v78)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);
  }
  else
  {
    if ( fld_e1896 != 2 )
      goto LABEL_48;
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    v69 = sub_41A5E0(pArg2 + 116);
    v79 = COERCE_FLOAT(sub_41A5E0(pArg2 + 130));
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 116));
    *(float *)&v41 = COERCE_FLOAT(sub_41A5E0(pArg2 + 130));
    v42 = *(uint32_t *)pObj;
    pArg2 = v41;
    v43 = (*(int (/*thiscall*/ **)(int, int))(v42 + 672))(pObj, 3);
    v106 = sub_41A5E0(v43 + 116);
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v43 + 130));
    v44 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
    v88 = sub_41A5E0(v44 + 116);
    v97 = COERCE_FLOAT(sub_41A5E0(v44 + 130));
    v40 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            1.0,
            100.0,
            (unsigned int)(uint64_t)((double)v106 * *(float *)&v110)
          - (int)(uint64_t)((double)v88 * v97) / 2,
            2 * (unsigned int)(uint64_t)((double)v69 * v79)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);
  }
  pObj = nArg3;
  *v6 += (uint64_t)v40;
LABEL_48:
  fld_e1897 = *(this + 1897);
  if ( fld_e1897 == 1 )
  {
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    v70 = sub_41A5E0(pArg2 + 144);
    v80 = COERCE_FLOAT(sub_41A5E0(pArg2 + 158));
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 144));
    *(float *)&v46 = COERCE_FLOAT(sub_41A5E0(pArg2 + 158));
    v47 = *(uint32_t *)pObj;
    pArg2 = v46;
    v48 = (*(int (/*thiscall*/ **)(int, int))(v47 + 672))(pObj, 3);
    v107 = sub_41A5E0(v48 + 144);
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v48 + 158));
    v49 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
    v89 = sub_41A5E0(v49 + 144);
    v98 = COERCE_FLOAT(sub_41A5E0(v49 + 158));
    v50 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            100.0,
            1.0,
            (unsigned int)(uint64_t)((double)v107 * *(float *)&v110)
          - (int)(uint64_t)((double)v89 * v98) / 2,
            2 * (unsigned int)(uint64_t)((double)v70 * v80)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);
  }
  else
  {
    if ( fld_e1897 != 2 )
      goto LABEL_53;
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    v71 = sub_41A5E0(pArg2 + 144);
    v81 = COERCE_FLOAT(sub_41A5E0(pArg2 + 158));
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 144));
    *(float *)&v51 = COERCE_FLOAT(sub_41A5E0(pArg2 + 158));
    v52 = *(uint32_t *)pObj;
    pArg2 = v51;
    v53 = (*(int (/*thiscall*/ **)(int, int))(v52 + 672))(pObj, 3);
    v108 = sub_41A5E0(v53 + 144);
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v53 + 158));
    v54 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
    v90 = sub_41A5E0(v54 + 144);
    v99 = COERCE_FLOAT(sub_41A5E0(v54 + 158));
    v50 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            1.0,
            100.0,
            (unsigned int)(uint64_t)((double)v108 * *(float *)&v110)
          - (int)(uint64_t)((double)v90 * v99) / 2,
            2 * (unsigned int)(uint64_t)((double)v71 * v81)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);
  }
  pObj = nArg3;
  *v6 += (uint64_t)v50;
LABEL_53:
  if ( *((uint8_t *)this + 7534) != 0 )
  {
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    v72 = sub_41A5E0(pArg2 + 816);
    v82 = COERCE_FLOAT(sub_41A5E0(pArg2 + 830));
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 816));
    *(float *)&v55 = COERCE_FLOAT(sub_41A5E0(pArg2 + 830));
    v56 = *(uint32_t *)pObj;
    pArg2 = v55;
    v57 = (*(int (/*thiscall*/ **)(int, int))(v56 + 672))(pObj, 3);
    v109 = sub_41A5E0(v57 + 816);
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v57 + 830));
    v58 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
    v91 = sub_41A5E0(v58 + 816);
    v100 = COERCE_FLOAT(sub_41A5E0(v58 + 830));
    v59 = (uint64_t)sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
                              100.0,
                              1.0,
                              (unsigned int)(uint64_t)((double)v109 * *(float *)&v110)
                            - (int)(uint64_t)((double)v91 * v100) / 2,
                              2 * (unsigned int)(uint64_t)((double)v72 * v82)
                            - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);
    pObj = nArg3;
    *v6 += v59;
  }
  if ( *((uint8_t *)this + 7558) != 0 )
  {
    v60 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj);
    *v6 += (uint64_t)sub_4049C0(100.0, 1.0, v60 != 4 ? 100 : -100, 100);
  }
  nArg3 = 0;
  pArg2 = (int)this + 7535;
  do
  {
    if ( *(uint8_t *)pArg2 != 0 )
    {
      fArg4 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3));
      v73 = sub_41A5E0(nArg3 + LODWORD(fArg4) + 172);
      fArg4 = COERCE_FLOAT(sub_41A5E0(nArg3 + LODWORD(fArg4) + 228));
      v61 = (uint64_t)((double)v73 * fArg4);
      if ( (int)v61 >= -100 )
      {
        if ( (int)v61 > 100 )
          LODWORD(v61) = 100;
      }
      else
      {
        LODWORD(v61) = -100;
      }
      *v6 += (uint64_t)sub_4049C0(100.0, 1.0, v61, 100);
    }
    ++pArg2;
    nArg3 += 14;
  }
  while ( nArg3 < 56 );
  result = 0;
  nArg3 = 0;
  do
  {
    if ( *((uint8_t *)this + result + 7539) != 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 776))(pObj, result) != 0 )
        *v6 += 100;
      result = nArg3;
    }
    nArg3 = ++result;
  }
  while ( result < 17 );
  if ( *((uint8_t *)this + 7557) == 1 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);
    result = sub_53FD00(pObj);
    if ( (uint8_t)result == 1 )
      *v6 += 100;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4DD8F0 sub_4DD8F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4DD8F0(uint32_t *this, int nArg2, int nArg3)
{
  int v4; // eax
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // ecx
  int v8; // ebx
  int v9; // eax
  unsigned int v10; // edx
  char *v11; // ecx
  int v12; // eax
  int v13; // eax
  int64_t v14; // rax
  int64_t v15; // rax
  int64_t v16; // rax
  int64_t v17; // rax
  int64_t v18; // rax
  int64_t v19; // rax
  int64_t v20; // rax
  int64_t v21; // rax
  int64_t v22; // rax
  int64_t v23; // rax
  int *v24; // eax
  int v25; // eax
  int *v26; // eax
  int v27; // eax
  uint64_t v28; // rax
  int64_t v29; // rax
  int64_t v30; // rax
  int64_t v31; // rax
  int64_t v32; // rax
  int64_t v33; // rax
  int64_t v34; // rax
  int64_t v35; // rax
  int v36; // edi
  unsigned int v37; // edi
  uint64_t v38; // rax
  int v39; // edi
  unsigned int v40; // edi
  uint64_t v41; // rax
  int v42; // edi
  int v43; // eax
  int v44; // edi
  int v45; // eax
  float v47; // [esp+58h] [ebp-2Ch]
  float v48; // [esp+58h] [ebp-2Ch]
  float v49; // [esp+58h] [ebp-2Ch]
  float v50; // [esp+58h] [ebp-2Ch]
  float v51; // [esp+58h] [ebp-2Ch]
  float v52; // [esp+58h] [ebp-2Ch]
  float v53; // [esp+58h] [ebp-2Ch]
  float v54; // [esp+58h] [ebp-2Ch]
  float v55; // [esp+58h] [ebp-2Ch]
  float v56; // [esp+58h] [ebp-2Ch]
  float v57; // [esp+58h] [ebp-2Ch]
  float v58; // [esp+58h] [ebp-2Ch]
  float v59; // [esp+58h] [ebp-2Ch]
  float v60; // [esp+5Ch] [ebp-28h]
  float v61; // [esp+5Ch] [ebp-28h]
  float v62; // [esp+5Ch] [ebp-28h]
  float v63; // [esp+5Ch] [ebp-28h]
  float v64; // [esp+5Ch] [ebp-28h]
  float v65; // [esp+5Ch] [ebp-28h]
  float v66; // [esp+5Ch] [ebp-28h]
  float v67; // [esp+5Ch] [ebp-28h]
  float v68; // [esp+5Ch] [ebp-28h]
  float v69; // [esp+5Ch] [ebp-28h]
  float v70; // [esp+5Ch] [ebp-28h]
  float v71; // [esp+5Ch] [ebp-28h]
  float v72; // [esp+5Ch] [ebp-28h]
  int v73; // [esp+74h] [ebp-10h]
  int v74; // [esp+74h] [ebp-10h]
  int v75; // [esp+74h] [ebp-10h]
  float v76; // [esp+74h] [ebp-10h]
  int i; // [esp+78h] [ebp-Ch]
  int v78; // [esp+78h] [ebp-Ch]
  int v79; // [esp+78h] [ebp-Ch]
  int v80; // [esp+78h] [ebp-Ch]
  uint32_t *v81; // [esp+80h] [ebp-4h]
  int v82; // [esp+8Ch] [ebp+8h]
  int v83; // [esp+8Ch] [ebp+8h]
  int v84; // [esp+8Ch] [ebp+8h]
  int v85; // [esp+8Ch] [ebp+8h]
  int v86; // [esp+8Ch] [ebp+8h]
  int v87; // [esp+8Ch] [ebp+8h]
  int v88; // [esp+8Ch] [ebp+8h]
  int v89; // [esp+8Ch] [ebp+8h]
  int v90; // [esp+8Ch] [ebp+8h]
  int v91; // [esp+8Ch] [ebp+8h]
  int *j; // [esp+8Ch] [ebp+8h]
  int *k; // [esp+8Ch] [ebp+8h]
  int v94; // [esp+8Ch] [ebp+8h]
  int v95; // [esp+8Ch] [ebp+8h]
  int v96; // [esp+8Ch] [ebp+8h]
  int v97; // [esp+8Ch] [ebp+8h]
  int v98; // [esp+8Ch] [ebp+8h]
  int v99; // [esp+8Ch] [ebp+8h]
  int v100; // [esp+8Ch] [ebp+8h]
  int v101; // [esp+8Ch] [ebp+8h]
  int v102; // [esp+8Ch] [ebp+8h]
  int v103; // [esp+90h] [ebp+Ch]
  float v104; // [esp+90h] [ebp+Ch]
  float v105; // [esp+90h] [ebp+Ch]

  v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0);
  sub_4A1210(v4);
  v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84C4 + 4))(dword_8F84C4, nArg3);
  *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) = nArg2;
  *(this + 1820) = v5[47];
  *(this + 1821) = v5[48];
  v6 = v5[47];
  v7 = v5[48] - v6;
  v8 = nArg2 - v6;
  v9 = v5[36];
  v103 = v7;
  v73 = v9;
  if ( byte_77F280 == 0 && v9 == 2 )
  {
    nArg2 = **(uint32_t **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 108);
    off_77F3FC((char *)&byte_6F9028, nArg2);
    v9 = v73;
  }
  v10 = 0;
  v81 = nullptr;
  v11 = (char *)dword_9B7C64 + 16 * v9;
  for ( i = 0; ; i += 44 )
  {
    v12 = *((uint32_t *)v11 + 1);
    if ( v12 == 0 || v10 >= (*((uint32_t *)v11 + 2) - v12) / 44 )
      break;
    if ( *(uint32_t *)(i + *((uint32_t *)v11 + 1)) == nArg2 )
    {
      v81 = (uint32_t *)(*((uint32_t *)v11 + 1) + 44 * v10);
      if ( v73 == 2 )
      {
        v13 = *((uint32_t *)dword_9B7C64 + 9);
        if ( v13 != 0 )
          v13 = (*((uint32_t *)dword_9B7C64 + 10) - v13) / 44;
        off_77F3FC((char *)&byte_6F8FE0, 2, v10, v13);
      }
      break;
    }
    ++v10;
  }
  v82 = v81[1];
  v14 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v14 + 4, SHIDWORD(v14), v82);
  v83 = v81[2];
  v15 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v15 + 32, SHIDWORD(v15), v83);
  v84 = v81[3];
  v16 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v16 + 60, SHIDWORD(v16), v84);
  v85 = v81[4];
  v17 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v17 + 88, SHIDWORD(v17), v85);
  v86 = v81[5];
  v18 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v18 + 116, SHIDWORD(v18), v86);
  v87 = v81[6];
  v19 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v19 + 144, SHIDWORD(v19), v87);
  v88 = v81[7];
  v20 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v20 + 1012, SHIDWORD(v20), v88);
  v89 = v81[8];
  v21 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v21 + 1040, SHIDWORD(v21), v89);
  v90 = v81[9];
  v22 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v22 + 1068, SHIDWORD(v22), v90);
  v91 = v81[10];
  v23 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v23 + 1096, SHIDWORD(v23), v91);
  v24 = v5 + 49;
  v78 = 0;
  for ( j = v5 + 49; ; v24 = j )
  {
    v60 = (float)v24[1];
    v47 = (float)*v24;
    v74 = (uint64_t)sub_4049C0(v47, v60, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v25 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0);
    sub_41A590(v25 + v78 + 172, v74, v74);
    j += 2;
    v78 += 14;
    if ( v78 >= 56 )
      break;
  }
  v26 = v5 + 57;
  v79 = 0;
  for ( k = v5 + 57; ; v26 = k )
  {
    v61 = (float)v26[1];
    v48 = (float)*v26;
    v75 = (uint64_t)sub_4049C0(v48, v61, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v27 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0);
    sub_41A590(v27 + v79 + 284, v75, v75);
    k += 2;
    v79 += 14;
    if ( v79 >= 224 )
      break;
  }
  v62 = (float)(int)v5[94];
  v49 = (float)(int)v5[93];
  v28 = (uint64_t)sub_4049C0(v49, v62, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v94 = v28;
  v29 = ((int64_t (/*fastcall*/ *)(uint32_t *, uint32_t, uint32_t))*(uint32_t *)(*this + 672))(this, HIDWORD(v28), 0);
  sub_41A590(v29 + 816, SHIDWORD(v29), v94);
  v63 = (float)(int)v5[96];
  v50 = (float)(int)v5[95];
  v95 = (uint64_t)sub_4049C0(v50, v63, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v30 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v30 + 844, SHIDWORD(v30), v95);
  v64 = (float)(int)v5[98];
  v51 = (float)(int)v5[97];
  v96 = (uint64_t)sub_4049C0(v51, v64, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v31 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v31 + 872, SHIDWORD(v31), v96);
  v65 = (float)(int)v5[100];
  v52 = (float)(int)v5[99];
  v97 = (uint64_t)sub_4049C0(v52, v65, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v32 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v32 + 900, SHIDWORD(v32), v97);
  v66 = (float)(int)v5[102];
  v53 = (float)(int)v5[101];
  v98 = (uint64_t)sub_4049C0(v53, v66, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v33 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v33 + 928, SHIDWORD(v33), v98);
  v67 = (float)(int)v5[104];
  v54 = (float)(int)v5[103];
  v99 = (uint64_t)sub_4049C0(v54, v67, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v34 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v34 + 956, SHIDWORD(v34), v99);
  v68 = (float)(int)v5[106];
  v55 = (float)(int)v5[105];
  v100 = (uint64_t)sub_4049C0(v55, v68, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v35 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);
  sub_41A590(v35 + 984, SHIDWORD(v35), v100);
  v69 = (float)(int)v5[108];
  v56 = (float)(int)v5[107];
  *(this + 1878) = (uint64_t)sub_4049C0(v56, v69, v8, v103);
  v70 = (float)(int)v5[110];
  v57 = (float)(int)v5[109];
  *(this + 1879) = (uint64_t)sub_4049C0(v57, v70, v8, v103);
  v71 = (float)(int)v5[90];
  v58 = (float)(int)v5[89];
  v80 = (uint64_t)sub_4049C0(v58, v71, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v72 = (float)(int)v5[92];
  v59 = (float)(int)v5[91];
  v76 = (double)(int)(uint64_t)sub_4049C0(v59, v72, v8, v103) * 0.001;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v36 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0);
  v101 = sub_41A5E0(v36 + 4);
  v104 = COERCE_FLOAT(sub_41A5E0(v36 + 18));
  v37 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 760;
  v38 = (uint64_t)((double)(int)(uint64_t)((double)v101 * v104) * ((double)v80 * 0.001));
  sub_41A590(v37, SHIDWORD(v38), v38);
  v39 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0);
  v102 = sub_41A5E0(v39 + 32);
  v105 = COERCE_FLOAT(sub_41A5E0(v39 + 46));
  v40 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 788;
  v41 = (uint64_t)((double)(int)(uint64_t)((double)v102 * v105) * v76);
  sub_41A590(v40, SHIDWORD(v41), v41);
  sub_4DC220(this);
  sub_4D98A0(this);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  v42 = *this;
  v43 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 740))(this, 0, 1);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v42 + 732))(this, v43);
  v44 = *this;
  v45 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 756))(this, 1);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(v44 + 748))(this, v45);
}


// ------------------------------------------------------------
// 0x4DE0E0 sub_4DE0E0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4DE0E0(uint32_t *this, int nArg2)
{
  int fld_e1952; // edx
  unsigned int i; // ecx
  unsigned int result; // eax
  int fld_e19522; // eax
  int v7; // ebx

  fld_e1952 = *(this + 1952);
  for ( i = 0; fld_e1952 != 0; ++i )
  {
    result = (*(this + 1953) - fld_e1952) >> 2;
    if ( i >= result )
      break;
    fld_e19522 = *(this + 1952);
    v7 = *(uint32_t *)(fld_e19522 + 4 * i);
    result = fld_e19522 + 4 * i;
    if ( v7 == nArg2 )
    {
      memcpy_0(
        (void *)(*(this + 1952) + 4 * i),
        (const void *)(*(this + 1952) + 4 * i + 4),
        4 * ((int)(*(this + 1953) - (*(this + 1952) + 4 * i + 4)) >> 2));
      result = *(this + 1953) - 4;
      *(this + 1953) = result;
      return result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DE160 sub_4DE160
// ------------------------------------------------------------
char /*thiscall*/ sub_4DE160(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int v6; // ebx
  int v7; // eax
  int v8; // ebx
  int fld_e2090; // eax
  int v10; // eax
  int v12; // [esp-1Ch] [ebp-28h]
  int v13; // [esp-1Ch] [ebp-28h]

  if ( (uint8_t)nArg2 != 0 )
    goto LABEL_13;
  if ( dword_8F7C04 == 0 )
    goto LABEL_7;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) != v6 )
    goto LABEL_7;
  if ( *(this + 2090) == 0 )
  {
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) != 60001 )
    {
      sub_491530(2, 0);
      v7 = sub_418DD0(100);
      sub_424760(dword_79C0B0, nArg3 - 63, nArg4 - 21, v7, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      sub_491630(2);
    }
LABEL_7:
    if ( *(this + 2090) == 0 )
      goto LABEL_13;
  }
  sub_491530(2, 0);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this);
  if ( v8 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) )
  {
    if ( dword_8F7C04 == *(this + 1815) )
    {
      v13 = sub_418DD0(1);
      sub_424760(dword_79C0B0, nArg3 - 35, nArg4 - 12, v13, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
    }
  }
  else
  {
    v12 = sub_418DD0(0);
    sub_424760(dword_79C0B0, nArg3 - 35, nArg4 - 12, v12, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
  }
  sub_491630(2);
LABEL_13:
  LOBYTE(fld_e2090) = sub_58E750(nArg2, nArg3, nArg4, nArg5);  // 【IRDActiveObject__vmt148】
  if ( (uint8_t)nArg2 != 0 )
  {
    LOBYTE(fld_e2090) = *((uint8_t *)this + 8524);
    if ( (uint8_t)fld_e2090 != 0 )
    {
      fld_e2090 = *(this + 2090);
      if ( fld_e2090 == 0 )
      {
        fld_e2090 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 436))(this);
        if ( fld_e2090 > 0 )
        {
          sub_491530(2, 0);
          v10 = sub_418DD0(0);
          sub_424760(dword_79C0B0, nArg3 - 33, nArg4 - 10, v10, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
          LOBYTE(fld_e2090) = sub_491630(2);
        }
      }
    }
  }
  return fld_e2090;
}



// ------------------------------------------------------------
// 0x4DE360 sub_4DE360
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4DE360(char **this, uint32_t *uArg2, char *pszArg3, char *pszArg4)
{
  char *pszArg42; // eax
  char *pszArg32; // esi
  char *fld_e2; // ebx
  char *pszArg33; // edx
  const void *pszArg422; // esi
  void *pszArg332; // edi

  pszArg42 = pszArg4;
  pszArg32 = pszArg3;
  if ( pszArg3 != pszArg4 )
  {
    fld_e2 = *(this + 2);
    pszArg33 = pszArg3;
    if ( pszArg4 != fld_e2 )
    {
      do
      {
        pszArg422 = pszArg42;
        pszArg332 = pszArg33;
        pszArg42 += 32;
        pszArg33 += 32;
        qmemcpy(pszArg332, pszArg422, 0x20u);
      }
      while ( pszArg42 != fld_e2 );
      pszArg32 = pszArg3;
    }
    *(this + 2) = pszArg33;
  }
  *uArg2 = pszArg32;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4DE3B0 sub_4DE3B0
// ------------------------------------------------------------
char */*stdcall*/ sub_4DE3B0(char *pszArg1, char *pszArg2, const void *pArg3)
{
  sub_4DAB30(pszArg1, pszArg2, pArg3);
  return &pszArg1[32 * (uint32_t)pszArg2];
}



// ------------------------------------------------------------
// 0x4DE3E0 sub_4DE3E0
// ------------------------------------------------------------
void /*thiscall*/ sub_4DE3E0(int *this)
{
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 && rand() % 100 < 50 )
    sub_4DC730(this);
}



// ------------------------------------------------------------
// 0x4DE410 sub_4DE410
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4DE410(uint32_t *this)
{
  int fld_e162; // edx
  int v3; // eax
  int v4; // ebx
  unsigned int v5; // edi
  uint64_t v6; // rax
  int v7; // edi
  int v8; // eax
  int v9; // eax
  unsigned int v10; // edi
  int v11; // eax
  int v12; // edx
  int *v13; // eax
  int v14; // edx
  char *pThis_49; // eax
  const char *v16; // eax
  size_t *v17; // eax
  char *pThis_492; // [esp-4h] [ebp-A4h]
  char Buffer[128]; // [esp+10h] [ebp-90h] BYREF
  int dword_796E502; // [esp+90h] [ebp-10h]
  int v22; // [esp+9Ch] [ebp-4h]

  fld_e162 = *(this + 162);
  dword_796E502 = dword_796E50;
  v3 = *this;
  *(this + 1943) = 3;
  *(this + 162) = fld_e162 | 2;
  *((uint8_t *)this + 6668) = 1;
  v4 = (*(int (**)(void))(v3 + 740))();
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 4;
  v6 = (uint64_t)((double)sub_41A5E0(v5) * 2.5);
  sub_41A590(v5, SHIDWORD(v6), v6);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  v7 = *this;
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 740))(this, 0, 1);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v7 + 732))(this, v8);
  v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this);
  off_77F3FC(aApplyboss, v4, v9);
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 466;
  v11 = sub_41A5E0(v10);
  sub_41A590(v10, v12, v11 + 50);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  *(this + 1822) = -1;
  v22 = 0;
  if ( operator new(0x84u) != nullptr )
    v13 = (int *)sub_5FE2C0(1120403456);
  else
    v13 = nullptr;
  v14 = *v13;
  v22 = -1;
  (*(void (/*thiscall*/ **)(int *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v14 + 56))(
    v13,
    this,
    this,
    0,
    0,
    0,
    -1);
  if ( *(this + 78) < 0x10u )
    pThis_49 = (char *)(this + 73);
  else
    pThis_49 = (char *)*(this + 73);
  pThis_492 = pThis_49;
  v16 = (const char *)sub_422E70(873);
  sprintf(Buffer, v16, pThis_492);
  v17 = (size_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 4);
  return sub_4015C0(v17, Buffer, strlen(Buffer));  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x4DE5E0 sub_4DE5E0
// ------------------------------------------------------------
void /*thiscall*/ sub_4DE5E0(
        int this,
        size_t a2,
        void *Block,
        int a4,
        int a5,
        int a6,
        int a7,
        unsigned int a8,
        int a9,
        int a10)
{
  int v11; // edx
  int v12; // ebx
  unsigned int v13; // eax

  sub_4014D0((size_t *)(this + 8528), &a2, 0, 0xFFFFFFFF);
  v11 = a10;
  *(uint32_t *)(this + 8584) = a9;
  *(uint32_t *)(this + 8588) = v11;
  *(uint8_t *)(this + 8569) = 0;
  *(uint8_t *)(this + 8570) = 0;
  v12 = *(uint32_t *)(this + 8584);
  v13 = rand();
  sub_698F90(this + 8556, v12 + v13 % (*(uint32_t *)(this + 8588) - v12), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( a8 >= 0x10 )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x4DE680 sub_4DE680
// ------------------------------------------------------------
void /*noreturn*/ sub_4DE680()
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4DE6F0 sub_4DE6F0
// ------------------------------------------------------------
void /*thiscall*/ sub_4DE6F0(void *this)
{
  sub_4017E0((int)this + 28);
}



// ------------------------------------------------------------
// 0x4DE700 sub_4DE700
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4DE700(int this)
{
  unsigned int fld_1C08; // edx
  int pThis_1BF4; // edi
  int pThis_1BF42; // edx
  int pThis_1E94; // eax
  void **v6; // ecx
  void **v7; // edi
  int v8; // ecx
  size_t *result; // eax
  void **v10; // [esp+Ch] [ebp-Ch] BYREF
  int v11; // [esp+10h] [ebp-8h]
  int pThis_1E942; // [esp+14h] [ebp-4h]

  if ( dword_9A05D4 == 0 && dword_9A05D8 == 0 )
  {
    dword_9A05D8 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                     dword_8F84B8,
                     "Monster/FlyingMonsterMark.img");
    dword_9A05DC = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                     dword_8F84B8,
                     "Monster/SummonMonsterMark.img");
  }
  ++dword_9A05D4;
  *(uint32_t *)(this + 96) = 529;
  *(uint32_t *)(this + 608) = 100;
  *(uint32_t *)(this + 7668) = 0;
  *(uint32_t *)(this + 7688) = 0;
  *(uint32_t *)(this + 7148) = 0;
  *(uint32_t *)(this + 7672) = -1;
  *(uint32_t *)(this + 7676) = -1;
  *(uint32_t *)(this + 7720) = 0;
  *(uint32_t *)(this + 7716) = 0;
  *(uint32_t *)(this + 7712) = 0;
  *(uint32_t *)(this + 7708) = 0;
  *(uint32_t *)(this + 648) = 0;
  *(uint8_t *)(this + 7764) = 0;
  *(uint32_t *)(this + 7768) = 0;
  *(uint32_t *)(this + 7772) = 0;
  *(uint8_t *)(this + 7776) = 0;
  *(uint8_t *)(this + 7801) = 0;
  *(uint32_t *)(this + 7632) = -1;
  *(uint32_t *)(this + 7636) = -1;
  fld_1C08 = *(uint32_t *)(this + 7176);
  if ( fld_1C08 < 0x10 )
    pThis_1BF4 = this + 7156;
  else
    pThis_1BF4 = *(uint32_t *)(this + 7156);
  if ( fld_1C08 < 0x10 )
    pThis_1BF42 = this + 7156;
  else
    pThis_1BF42 = *(uint32_t *)(this + 7156);
  sub_406D00((uint32_t *)(this + 7152), &v10, pThis_1BF42, pThis_1BF4 + *(uint32_t *)(this + 7172));
  if ( *(uint32_t *)(this + 7808) != 0 )
    j__free(*(void **)(this + 7808));
  pThis_1E94 = this + 7828;
  *(uint32_t *)(this + 7808) = 0;
  *(uint32_t *)(this + 7812) = 0;
  *(uint32_t *)(this + 7816) = 0;
  *(uint32_t *)(this + 7820) = 0;
  pThis_1E942 = this + 7828;
  v11 = 29;
  do
  {
    v6 = *(void ***)pThis_1E94;
    if ( *(uint32_t *)pThis_1E94 != 0 )
    {
      v7 = *(void ***)pThis_1E94;
      v10 = *(void ***)(pThis_1E94 + 4);
      if ( v6 != v10 )
      {
        do
          sub_41B010(v7++);
        while ( v7 != v10 );
        pThis_1E94 = pThis_1E942;
      }
      j__free(*(void **)pThis_1E94);
      pThis_1E94 = pThis_1E942;
    }
    v8 = v11;
    *(uint32_t *)pThis_1E94 = 0;
    *(uint32_t *)(pThis_1E94 + 4) = 0;
    *(uint32_t *)(pThis_1E94 + 8) = 0;
    pThis_1E94 += 16;
    pThis_1E942 = pThis_1E94;
    v11 = v8 - 1;
  }
  while ( v8 != 1 );
  *(uint32_t *)(this + 8288) = -1;
  *(uint32_t *)(this + 8332) = -1;
  *(uint32_t *)(this + 8328) = -1;
  *(uint32_t *)(this + 8324) = -1;
  *(uint32_t *)(this + 8320) = -1;
  *(uint32_t *)(this + 8316) = -1;
  *(uint32_t *)(this + 8312) = -1;
  *(uint32_t *)(this + 8292) = 1000;
  if ( *(uint32_t *)(this + 8340) != 0 )
    j__free(*(void **)(this + 8340));
  *(uint32_t *)(this + 8340) = 0;
  *(uint32_t *)(this + 8344) = 0;
  *(uint32_t *)(this + 8348) = 0;
  *(uint32_t *)(this + 8352) = 0;
  *(uint32_t *)(this + 8356) = 0;
  *(uint32_t *)(this + 8360) = 0;
  *(uint32_t *)(this + 8364) = 0;
  *(uint32_t *)(this + 8472) = 0;
  *(uint32_t *)(this + 8476) = 0;
  *(uint32_t *)(this + 8300) = -1;
  *(uint32_t *)(this + 8304) = -1;
  *(uint32_t *)(this + 8308) = -1;
  *(uint8_t *)(this + 8296) = 0;
  *(uint32_t *)(this + 8516) = -1;
  *(uint32_t *)(this + 8520) = -1;
  *(uint8_t *)(this + 8524) = 1;
  result = sub_4015C0((size_t *)(this + 8528), szPassword, 0);  // 【std::string构造赋值】
  *(uint32_t *)(this + 8584) = 0;
  *(uint32_t *)(this + 8588) = 0;
  *(uint8_t *)(this + 8569) = 0;
  *(uint8_t *)(this + 8570) = 0;
  *(uint32_t *)(this + 7732) = 200;
  return result;
}


// ------------------------------------------------------------
// 0x4DE980 sub_4DE980
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4DE980(int this, char *pszArg2, unsigned int uArg3, void *Block)
{
  int fld_4; // edx
  unsigned int result; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v10; // eax
  int fld_87; // ecx
  int fld_88; // eax
  char *v13; // edi
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v16; // esi
  char *fld_83; // eax
  int fld_86; // esi
  char *v19; // esi
  char *fld_42; // [esp-18h] [ebp-54h]
  char *fld_85; // [esp-Ch] [ebp-48h]
  char *fld_84; // [esp-8h] [ebp-44h]
  int v23; // [esp+0h] [ebp-3Ch] BYREF
  uint32_t v24[9]; // [esp+Ch] [ebp-30h] BYREF
  int v25; // [esp+38h] [ebp-4h]
  int v26; // [esp+48h] [ebp+Ch]
  char *Blocka; // [esp+4Ch] [ebp+10h]
  char *Blockb; // [esp+4Ch] [ebp+10h]

  fld_4 = *(uint32_t *)(this + 4);
  v24[8] = &v23;
  qmemcpy(v24, Block, 0x20u);
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 5;
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 5;
    else
      fld_8 = 0;
    if ( 0x7FFFFFF - fld_8 < uArg3 )
      sub_4A30C0();
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 5;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(char **)(this + 8);
      Blockb = fld_83;
      if ( (fld_83 - pszArg2) >> 5 >= uArg3 )
      {
        v19 = &fld_83[-32 * uArg3];
        *(uint32_t *)(this + 8) = sub_4DA820(v19, fld_83, fld_83);
        sub_4DA7F0(pszArg2, v19, Blockb);
        return (unsigned int)sub_4DA050(pszArg2, &pszArg2[32 * uArg3], v24);
      }
      else
      {
        sub_4DA820(pszArg2, fld_83, &pszArg2[32 * uArg3]);
        fld_84 = (char *)(uArg3 - ((*(uint32_t *)(this + 8) - (int)pszArg2) >> 5));
        fld_85 = *(char **)(this + 8);
        v25 = 2;
        sub_4DE3B0(fld_85, fld_84, v24);
        fld_86 = 32 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        return (unsigned int)sub_4DA050(pszArg2, (char *)(fld_86 - 32 * uArg3), v24);
      }
    }
    else
    {
      if ( 0x7FFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 5;
      else
        fld_87 = 0;
      if ( v10 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 5;
        else
          fld_88 = 0;
        v10 = uArg3 + fld_88;
      }
      v26 = 32 * v10;
      Blocka = (char *)operator new(32 * v10);
      fld_42 = *(char **)(this + 4);
      v25 = 0;
      v13 = sub_4DA820(fld_42, pszArg2, Blocka);
      sub_4DAB30(v13, (char *)uArg3, v24);
      sub_4DA820(pszArg2, *(char **)(this + 8), &v13[32 * uArg3]);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 5;
      else
        fld_89 = 0;
      v16 = fld_89 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &Blocka[v26];
      *(uint32_t *)(this + 8) = &Blocka[32 * v16];
      *(uint32_t *)(this + 4) = Blocka;
      return (unsigned int)Blocka;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DEBD0 sub_4DEBD0
// ------------------------------------------------------------
void /*thiscall*/ sub_4DEBD0(int this, int nArg2, unsigned int uArg3, int pArg4)
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
      sub_4DE680(this);
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
// 0x4DEE20 sub_4DEE20
// ------------------------------------------------------------
int */*thiscall*/ sub_4DEE20(int **this, int nArg2, int *pDwArg3)
{
  int pObj; // edi
  int **pThis_15; // ebx
  int *result; // eax
  uint8_t v7[8]; // [esp+Ch] [ebp-10h] BYREF
  int v8; // [esp+14h] [ebp-8h] BYREF
  int *pDwArg32; // [esp+18h] [ebp-4h] BYREF

  pObj = nArg2;
  pThis_15 = this + 21;
  nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);
  sub_4BE520(pThis_15, &pDwArg32, &nArg2);
  result = pDwArg32;
  if ( pDwArg32 == *(this + 22) )
  {
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 576))(pObj);
    pDwArg32 = pDwArg3;
    return (int *)sub_42CDB0(v7, &v8);
  }
  else
  {
    pDwArg32[4] += (int)pDwArg3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DEEA0 sub_4DEEA0
// ------------------------------------------------------------
int /*thiscall*/ sub_4DEEA0(int this, int pArg2)
{
  char *v3; // ebx
  unsigned int v4; // eax
  int fld_4; // ecx
  unsigned int fld_8; // edx
  int v8; // eax
  int fld_42; // edi
  unsigned int fld_C; // edx
  int fld_82; // eax
  char *v12; // ebx
  int v13; // ecx
  unsigned int v14; // eax

  if ( this == pArg2 )
    return this;
  v3 = *(char **)(pArg2 + 4);
  if ( v3 == nullptr || (v4 = (*(uint32_t *)(pArg2 + 8) - (int)v3) >> 5) == 0 )
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
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 5;
  else
    fld_8 = 0;
  if ( v4 <= fld_8 )
  {
    sub_4DA7C0(v3, *(char **)(pArg2 + 8), *(char **)(this + 4));
    v8 = *(uint32_t *)(pArg2 + 4);
    if ( v8 != 0 )
      fld_42 = *(uint32_t *)(this + 4) + 32 * ((*(uint32_t *)(pArg2 + 8) - v8) >> 5);
    else
      fld_42 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = fld_42;
    return this;
  }
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 5;
  else
    fld_C = 0;
  if ( v4 > fld_C )
  {
    if ( fld_4 != 0 )
      j__free(*(void **)(this + 4));
    v13 = *(uint32_t *)(pArg2 + 4);
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(pArg2 + 8) - v13) >> 5;
    else
      v14 = 0;
    if ( sub_4A35C0((uint32_t *)this, v14) != 0 )
      *(uint32_t *)(this + 8) = sub_4DB3F0(*(char **)(pArg2 + 4), *(char **)(pArg2 + 8), *(char **)(this + 4));
    return this;
  }
  if ( fld_4 != 0 )
    fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 5;
  else
    fld_82 = 0;
  v12 = (char *)(*(uint32_t *)(pArg2 + 4) + 32 * fld_82);
  sub_4DA7C0(*(char **)(pArg2 + 4), v12, *(char **)(this + 4));
  *(uint32_t *)(this + 8) = sub_4DA820(v12, *(char **)(pArg2 + 8), *(char **)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x4DEFF0 sub_4DEFF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4DEFF0(
        int this,
        unsigned int a2,
        char Block,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10)
{
  int v10; // esi
  unsigned int v11; // edx
  uint32_t *result; // eax
  int v13; // edx

  v10 = *(uint32_t *)(this + 4);
  if ( v10 != 0 )
    v11 = (*(uint32_t *)(this + 8) - v10) >> 5;
  else
    v11 = 0;
  result = (uint32_t *)a2;
  if ( v11 >= a2 )
  {
    if ( v10 != 0 && a2 < (*(uint32_t *)(this + 8) - v10) >> 5 )
      return sub_4DE360((char **)this, &a2, (char *)(v10 + 32 * a2), *(char **)(this + 8));
  }
  else
  {
    if ( v10 != 0 )
      v13 = (*(uint32_t *)(this + 8) - v10) >> 5;
    else
      v13 = 0;
    return (uint32_t *)sub_4DE980(this, *(char **)(this + 8), a2 - v13, &Block);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DF060 sub_4DF060
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4DF060(uint32_t *this)
{
  uint32_t *pThis_7; // ecx

  pThis_7 = this + 7;
  pThis_7[1] = 0;
  pThis_7[2] = 0;
  pThis_7[3] = 0;
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *((uint8_t *)this + 20) = 1;
  *((uint8_t *)this + 21) = 0;
  *(this + 6) = 0;
  sub_4017E0((int)pThis_7);
  return this;
}



// ------------------------------------------------------------
// 0x4DF0C0 sub_4DF0C0
// ------------------------------------------------------------
uint32_t */*userpurge*/ sub_4DF0C0@<eax>(uint32_t *uArg1@<ecx>, double fArg2@<st0>, void *Block, int nArg4, int nArg5, int nArg6, int nArg7)
{
  sub_42AAB0();
  *uArg1 = &CNPieceDestroyEffect::`vftable';
  sub_5FE330((int)uArg1);
  sub_5FE3A0((int)uArg1, fArg2, Block, nArg4, nArg5, nArg6, nArg7);
  return uArg1;
}



// ------------------------------------------------------------
// 0x4DF130 sub_4DF130
// ------------------------------------------------------------
void */*thiscall*/ sub_4DF130(void *Block, char pszArg2)
{
  sub_4DF160();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4DF160 sub_4DF160
// ------------------------------------------------------------
int /*thiscall*/ sub_4DF160(uint32_t *this)
{
  *this = &CNPieceDestroyEffect::`vftable';
  sub_5FE380();
  return sub_42A450(this);
}



// ------------------------------------------------------------
// 0x4DF1B0 sub_4DF1B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4DF1B0(int this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  sub_4B1030((uint8_t *)this);
  *(uint32_t *)this = &CNEnchantWeapon::`vftable';
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  sub_5FEEB0(this);
  sub_5FEEE0(nArg2, nArg3, nArg4, nArg5);
  return this;
}



// ------------------------------------------------------------
// 0x4DF220 sub_4DF220
// ------------------------------------------------------------
void */*thiscall*/ sub_4DF220(void *Block, char pszArg2)
{
  sub_4DF250();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4DF250 sub_4DF250
// ------------------------------------------------------------
int /*thiscall*/ sub_4DF250(void **this)
{
  int result; // eax

  *this = &CNEnchantWeapon::`vftable';
  nullsub_3(this);
  if ( *(this + 30) != nullptr )
    j__free(*(this + 30));
  *(this + 30) = nullptr;
  *(this + 31) = nullptr;
  *(this + 32) = nullptr;
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *((uint8_t *)this + 12) = 0;
  *(this + 2) = &nengine::IObject::`vftable';
  return result;
}



// ------------------------------------------------------------
// 0x4DF2D0 sub_4DF2D0
// ------------------------------------------------------------
void /*thiscall*/ sub_4DF2D0(int *this, int *pDwArg2, int *pDwArg3, int nArg4)
{
  int v5; // edi
  int v6; // ebx
  int v7; // eax
  int fld_e79; // edi
  signed int v9; // edi
  int fld_e1814; // edi
  int *pThis; // ecx
  int v12; // eax
  int fld_e18142; // ecx
  int fld_e18139; // ecx
  int v15; // edi
  int fld_e1919; // edi
  int fld_e1918; // edi
  int *pDwArg22; // edi
  int fld_e1813; // ecx
  int v20; // edi
  int fld_e19052; // edi
  int fld_e18133; // eax
  int fld_e18132; // edi
  int fld_e1905; // edi
  int fld_e18134; // edi
  bool v26; // cc
  int fld_e18135; // eax
  int v28; // edi
  double v29; // st7
  int v30; // edi
  int fld_e18136; // edi
  double v32; // st7
  int fld_e18137; // ecx
  int v34; // edi
  int fld_e18138; // edi
  int fld_e1812; // eax
  double v37; // st7
  int fld_e19192; // edi
  int fld_e19182; // edi
  unsigned int v40; // edi
  int fld_e29; // ecx
  int v42; // edx
  int v43; // eax
  int v44; // edx
  int *v45; // edi
  uint32_t *v46; // ebx
  int v47; // ebx
  int v48; // edi
  double v49; // st7
  double v50; // st6
  unsigned int v51; // eax
  double i; // st5
  unsigned int v53; // eax
  double v54; // st5
  double j; // st4
  double v56; // st7
  double v57; // st7
  double v58; // st6
  float v59; // [esp+1Ch] [ebp-44h]
  float v60; // [esp+28h] [ebp-38h]
  float v61; // [esp+2Ch] [ebp-34h]
  float v62; // [esp+2Ch] [ebp-34h]
  float v63; // [esp+2Ch] [ebp-34h]
  float v64; // [esp+34h] [ebp-2Ch]
  float v65; // [esp+34h] [ebp-2Ch]
  float v66; // [esp+34h] [ebp-2Ch]
  float v67; // [esp+34h] [ebp-2Ch]
  float v68; // [esp+38h] [ebp-28h]
  float v69; // [esp+38h] [ebp-28h]
  float v70; // [esp+38h] [ebp-28h]
  float fld_e1933; // [esp+40h] [ebp-20h]
  float v72; // [esp+48h] [ebp-18h]
  unsigned int v73; // [esp+4Ch] [ebp-14h]
  int v74; // [esp+50h] [ebp-10h]
  float fld_e181310; // [esp+68h] [ebp+8h]
  int v76; // [esp+70h] [ebp+10h]

  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);
  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 188))(this);
  switch ( *(this + 1787) )
  {
    case 1:
      pDwArg22 = pDwArg2;
      if ( (uint8_t)sub_4DA6B0(pDwArg2) == 0 && rand() % 100 < 30 )
        goto LABEL_48;
      return;
    case 2:
    case 10:
      fld_e1813 = *(this + 1813);
      if ( fld_e1813 == 0 )
        goto LABEL_45;
      v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 124))(fld_e1813);
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) > v20 )
      {
        fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) <= fld_e18132 )
          goto LABEL_55;
        *pDwArg3 = 2;
        fld_e1905 = *(this + 1905);
        fld_e18133 = *(uint32_t *)(fld_e1905 + 24) + (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
      }
      else
      {
        *pDwArg3 = 3;
        fld_e19052 = *(this + 1905);
        fld_e18133 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813)) - *(uint32_t *)(fld_e19052 + 28);
      }
      *(this + 1918) = fld_e18133;
LABEL_55:
      fld_e18134 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
      v26 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) <= fld_e18134;
      fld_e18135 = *(uint32_t *)*(this + 1813);
      if ( v26 )
      {
        v28 = (*(int (**)(void))(fld_e18135 + 120))();
        v29 = (double)(int)abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - v28);
        if ( v29 >= (double)sub_4D8FE0(this) * 0.89999998 )
        {
          *pDwArg2 = 1;
          return;
        }
        if ( v29 <= (double)sub_4D8FE0(this) * 0.5 )
        {
          *pDwArg2 = 0;
          return;
        }
        goto LABEL_60;
      }
      v30 = (*(int (**)(void))(fld_e18135 + 120))();
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > v30 )
      {
        fld_e18136 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
        v32 = (double)(int)abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - fld_e18136);
        if ( v32 < (double)sub_4D8FE0(this) * 0.89999998 )
        {
          if ( v32 > (double)sub_4D8FE0(this) * 0.5 )
          {
LABEL_60:
            *pDwArg2 = 4;
            return;
          }
          *pDwArg2 = 1;
        }
        else
        {
          *pDwArg2 = 0;
        }
      }
      return;
    case 3:
      fld_e18137 = *(this + 1813);
      if ( fld_e18137 != 0 )
      {
        v34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18137 + 120))(fld_e18137);
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > v34 )
        {
          fld_e18138 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > fld_e18138 )
          {
            *pDwArg2 = 1;
            if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + 70 >= nArg4 - 40 )
              *(this + 1919) = nArg4 - 40;
            else
              *(this + 1919) = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + 70;
          }
        }
        else
        {
          *pDwArg2 = 0;
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 70 <= 40 )
            *(this + 1919) = 40;
          else
            *(this + 1919) = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 70;
        }
      }
      return;
    case 4:
      if ( rand() % 100 < 80 )
      {
        pDwArg22 = pDwArg2;
        if ( (uint8_t)sub_4DA6B0(pDwArg2) == 0 )
LABEL_48:
          sub_4DBDB0(pDwArg22, pDwArg3);
      }
      return;
    case 5:
    case 7:
    case 9:
      if ( *(this + 1813) == 0 )
        goto LABEL_45;
      sub_4DBDB0(pDwArg2, pDwArg3);
      return;
    case 6:
      pThis = this;
      if ( *(this + 1813) == 0 )
        goto LABEL_32;
      *pDwArg2 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) <= *(this + 1919);
      *pDwArg3 = ((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) <= *(this + 1918)) + 2;
      fld_e1919 = *(this + 1919);
      if ( *(this + 1921) >= fld_e1919 )
        goto LABEL_36;
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > fld_e1919 )
        goto LABEL_37;
      if ( *(this + 1921) >= fld_e1919 )
      {
LABEL_36:
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < *(this + 1919) )
LABEL_37:
          *pDwArg2 = 4;
      }
      fld_e1918 = *(this + 1918);
      if ( *(this + 1920) >= fld_e1918 )
        goto LABEL_41;
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) > fld_e1918 )
        goto LABEL_42;
      if ( *(this + 1920) >= fld_e1918 )
      {
LABEL_41:
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) < *(this + 1918) )
LABEL_42:
          *pDwArg3 = 4;
      }
      if ( *pDwArg2 == 4 && *pDwArg3 == 4 )
        goto LABEL_45;
      return;
    case 8:
    case 17:
      v76 = 0;
      v74 = 0;
      v64 = 0.0;
      v68 = 0.0;
      v60 = 0.0;
      v61 = 0.0;
      v40 = 0;
      while ( 1 )
      {
        fld_e29 = *(this + 29);
        v42 = *(uint32_t *)(fld_e29 + 8);
        v73 = v40;
        v43 = v42 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v42) >> 2 : 0;
        if ( (int)v40 >= v43 )
          break;
        v44 = *(uint32_t *)(fld_e29 + 8);
        if ( v44 != 0 && v40 < (*(uint32_t *)(fld_e29 + 12) - v44) >> 2 )
          v45 = *(int **)(v44 + 4 * v40);
        else
          v45 = nullptr;
        if ( v45 == this )
          goto LABEL_124;
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v45 + 40))(v45, 529) == 0 )
          goto LABEL_124;
        v46 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 340))(this);
        if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v45 + 340))(v45) != *v46 )
          goto LABEL_124;
        ++v76;
        v64 = (double)(*(int (/*thiscall*/ **)(int *))(*v45 + 120))(v45) + v64;
        v68 = (double)(*(int (/*thiscall*/ **)(int *))(*v45 + 124))(v45) + v68;
        fld_e1933 = (float)*(this + 1933);
        v47 = (*(int (/*thiscall*/ **)(int *))(*v45 + 120))(v45);
        v59 = (float)((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - v47);
        v48 = (*(int (/*thiscall*/ **)(int *))(*v45 + 124))(v45);
        v49 = (double)((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - v48);
        v50 = 1.0;
        v51 = 2;
        for ( i = v59; ; i = i * i )
        {
          if ( (v51 & 1) != 0 )
            v50 = v50 * i;
          v51 >>= 1;
          if ( v51 == 0 )
            break;
        }
        v53 = 2;
        v72 = v49;
        v54 = 1.0;
        for ( j = v72; ; j = j * j )
        {
          if ( (v53 & 1) != 0 )
            v54 = v54 * j;
          v53 >>= 1;
          if ( v53 == 0 )
            break;
        }
        if ( sqrt(v50 + v54) < fld_e1933 )
        {
          v40 = v73 + 1;
          v60 = v59 + v60;
          ++v74;
          v61 = v49 + v61;
        }
        else
        {
LABEL_124:
          v40 = v73 + 1;
        }
      }
      if ( v76 == 0 )
        goto LABEL_126;
      v56 = 1.0 / (double)v76;
      v65 = v64 * v56;
      v69 = v56 * v68;
      v66 = v65 - (double)(*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      v67 = v66 * 0.0099999998;
      v70 = (v69 - (double)(*(int (/*thiscall*/ **)(int *))(*this + 124))(this)) * 0.0099999998;
      if ( v74 != 0 )
      {
        v58 = 1.0 / (double)v74;
        v63 = v58 * v61;
        v57 = v60 * v58 + v67;
        v62 = v63 + v70;
      }
      else
      {
        v57 = v67;
        v62 = v70;
      }
      *pDwArg2 = v57 >= 0.0;
      if ( v62 < 0.0 )
        *pDwArg3 = 2;
      else
        *pDwArg3 = 3;
      return;
    case 11:
      fld_e18139 = *(this + 1813);
      if ( fld_e18139 == 0 )
        goto LABEL_45;
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18139 + 120))(fld_e18139);
      *pDwArg2 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < v15;
      *pDwArg3 = 4;
      return;
    case 12:
      *pDwArg2 = *(this + 1919) >= (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      *pDwArg3 = (*(this + 1918) >= (*(int (/*thiscall*/ **)(int *))(*this + 124))(this)) + 2;
      if ( *(this + 30) != 0 )
      {
        v7 = sub_42F220();
        fld_e79 = sub_4918E0(v7, 0);
      }
      else
      {
        fld_e79 = *(this + 79) / 2;
      }
      v9 = fld_e79 + 10;
      if ( (int)abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - *(this + 1919)) < v9 )
        *pDwArg2 = 4;
      if ( (int)abs32((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - *(this + 1918)) < v9 )
        *pDwArg3 = 4;
      if ( *pDwArg2 == 4 && *pDwArg3 == 4
        || *(this + 1813) != 0
        && ((double)sub_4D8FE0(this) * 0.1 <= 70.0 ? (fld_e181310 = 70.0) : (fld_e181310 = (double)sub_4D8FE0(this) * 0.1),
            (double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 8))(this, *(this + 1813), 0) < fld_e181310) )
      {
        if ( (uint8_t)sub_4DAB60(12) != 0 || (uint8_t)sub_4DAB60(13) != 0 )
        {
          fld_e1814 = *(this + 1814);
          pThis = this;
          if ( fld_e1814 == 0 )
            goto LABEL_32;
          if ( (uint8_t)sub_4DAB60(10) == 0 )
            goto LABEL_45;
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1814 + 120))(fld_e1814);
          fld_e18142 = *(this + 1814);
          *(this + 1919) = v12;
          *(this + 1918) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18142 + 124))(fld_e18142);
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1132))(this) == 0 )
        {
          if ( (uint8_t)sub_4DAB60(10) != 0 )
          {
            (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 9);
          }
          else if ( (uint8_t)sub_4DAB60(11) != 0 )
          {
            (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 10);
          }
        }
      }
      return;
    case 13:
      if ( rand() % 100 < 40 )
      {
LABEL_126:
        if ( (uint8_t)sub_4DA6B0(pDwArg2) == 0 )
          *pDwArg2 = rand() % 2;
        *pDwArg3 = rand() % 2 + 2;
      }
      return;
    case 19:
      *pDwArg2 = v5;
      *pDwArg3 = v6;
      return;
    case 21:
      *pDwArg2 = sub_432E50(v5);
      *pDwArg3 = sub_432E50(v6);
      return;
    case 23:
      (*(void (/*thiscall*/ **)(int *, int *, int *))(*this + 1232))(this, pDwArg2, pDwArg3);
      return;
    case 24:
      fld_e1812 = *(this + 1812);
      pThis = this;
      if ( fld_e1812 != 0 )
      {
        v37 = (double)(*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, fld_e1812, 0);
        if ( (double)sub_4D8FE0(this) * 0.5 >= v37 )
LABEL_45:
          (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
        else
          sub_4DC130(*(this + 1812), pDwArg2, pDwArg3);
      }
      else
      {
LABEL_32:
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(pThis, 13);
      }
      return;
    case 25:
      *pDwArg2 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) <= *(this + 1919);
      *pDwArg3 = ((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) <= *(this + 1918)) + 2;
      fld_e19192 = *(this + 1919);
      if ( *(this + 1921) >= fld_e19192 )
        goto LABEL_85;
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > fld_e19192 )
        goto LABEL_86;
      if ( *(this + 1921) >= fld_e19192 )
      {
LABEL_85:
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < *(this + 1919) )
LABEL_86:
          *pDwArg2 = 4;
      }
      fld_e19182 = *(this + 1918);
      if ( *(this + 1920) >= fld_e19182 )
        goto LABEL_90;
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) > fld_e19182 )
        goto LABEL_91;
      if ( *(this + 1920) >= fld_e19182 )
      {
LABEL_90:
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) < *(this + 1918) )
LABEL_91:
          *pDwArg3 = 4;
      }
      if ( *pDwArg2 == 4 && *pDwArg3 == 4 )
        (*(void (/*thiscall*/ **)(int *))(*this + 1076))(this);
      return;
    default:
      return;
  }
}


// ------------------------------------------------------------
// 0x4DFF40 sub_4DFF40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4DFF40(void *this, unsigned int uArg2)
{
  int pBuf[7]; // [esp+Ch] [ebp-1Ch] BYREF

  memset(pBuf, 0, sizeof(pBuf));
  return sub_4DEFF0((int)this, uArg2, 0, pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4], pBuf[5], pBuf[6]);
}



// ------------------------------------------------------------
// 0x4DFF90 sub_4DFF90
// ------------------------------------------------------------
void /*thiscall*/ sub_4DFF90(uint32_t *this, int nArg2)
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 3;
  else
    fld_e2 = 0;
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) >> 3 )
  {
    fld_e22 = *(this + 2);
    sub_63A7C0(fld_e22, 1, nArg2);
    *(this + 2) = fld_e22 + 8;
  }
  else
  {
    sub_4DEBD0((int)this, (uint32_t *)*(this + 2), 1u, nArg2);
  }
}


