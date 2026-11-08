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
// 【定案】对象工厂 case 1 构造器（0x4D2D60 case 1：new 0x5A0 → 本函数 → 解析器
// sub_509C90；析构分派 0x4D2B30 case 1 → sub_4CF5C0）——即 0x5A0 角色/怪物数据对象
//（[hit recovery] +396/+400、[jump power] +404、[stuckbonus on damage] +428..440 四档，
// 这些属性字段由解析器填充，本函数只做默认初始化）。
// 初始化模式：`+28=15, +24=0, +8=0` 三连 = MSVC std::string 的 SSO 空串初始化
// （buf 内联 16 字节时 capacity 恒为 15），本函数共初始化 9 个这样的字符串成员
//（+8/+512/+544/+572/+600/+684/+712/+740/+768）；`eh vector constructor iterator` =
// 对象数组逐元素调构造器（+64 处 4×0x10、+624 处 2×0x1C、+956 处 29×0x10 三组）。
// 尾调 sub_4CEB80 做二段初始化（见 gunner_state.cpp 同名函数）。返回 this。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D01E0(int this)  // 实现：尾调 sub_4CEB80 做二段初始化（见 gunner_state.cpp 同名函数）。返回 this
{
  *(uint32_t *)(this + 28) = 15;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // 写 this+8 = 0（技能槽记录首字）
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 60) = 0;  // this+60〔nFadeValue60(推断)〕等 2 字段
  `eh vector constructor iterator'(
    (void *)(this + 64),  // this+64 服务器页签按钮组 6 个
    0x10u,
    4,
    (void (/*thiscall*/ *)(void *))sub_4019A0,  // 指针 vector 三字段清零（起/止/容量 = 0）
    (void (/*thiscall*/ *)(void *))sub_5E5260);  // 调 动画子对象清理临时缓冲
  *(uint32_t *)(this + 132) = 0;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 136) = 0;  // this+136〔nCtx136(推断)〕等 2 字段
  *(uint32_t *)(this + 140) = 0;  // this+140〔nAdd140(推断)〕
  *(uint32_t *)(this + 532) = 15;
  *(uint32_t *)(this + 528) = 0;  // 字段 this+528〔命中目标 list 终点〕
  *(uint8_t *)(this + 512) = 0;  // this+512〔nAbilityId〕
  *(uint32_t *)(this + 564) = 15;
  *(uint32_t *)(this + 560) = 0;
  *(uint8_t *)(this + 544) = 0;  // this+544〔nFaction〕
  *(uint32_t *)(this + 592) = 15;  // 字段 this+592〔位置采样时刻(副本)〕
  *(uint32_t *)(this + 588) = 0;  // 字段 this+588〔位置采样时刻〕
  *(uint8_t *)(this + 572) = 0;  // this+572 最后一次受击
  *(uint32_t *)(this + 620) = 15;
  *(uint32_t *)(this + 616) = 0;  // 写 this+616 = 0（受击反应态）
  *(uint8_t *)(this + 600) = 0;  // 字段 this+600〔命中列表边界〕
  `eh vector constructor iterator'((void *)(this + 624), 0x1Cu, 2, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);  // 空串初始化（len 0 / cap 15 / 首字节 0；this+4 系）
  *(uint32_t *)(this + 704) = 15;  // 写 this+704 = 15（表现/名字快照[24]）
  *(uint32_t *)(this + 700) = 0;  // 写 this+700 = 0（表现/名字快照[20] 字节槽）
  *(uint8_t *)(this + 684) = 0;  // 写 this+684 = 0（表现/名字快照[1]）
  *(uint32_t *)(this + 732) = 15;
  *(uint32_t *)(this + 728) = 0;
  *(uint8_t *)(this + 712) = 0;  // 写 this+712 = 0（资源/动画句柄表基指针）
  *(uint32_t *)(this + 760) = 15;  // this+760〔fVal760(推断)〕
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
  *(uint32_t *)(this + 876) = 0;  // this+876 句柄走虚
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
  `eh vector constructor iterator'((void *)(this + 956), 0x10u, 29, (void (/*thiscall*/ *)(void *))sub_4019A0, sub_401940);  // 指针 vector 三字段清零（起/止/容量 = 0）
  *(uint32_t *)(this + 1424) = 0;
  *(uint32_t *)(this + 1428) = 0;
  *(uint32_t *)(this + 1432) = 0;  // 写 this+1432 = 0（效果触发锁存标志）
  sub_4CEB80((char *)this);
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4D03E0 sub_4D03E0
// 【定案】对象工厂 case 2 构造器（0x4D2D60 case 2：new 0xF8 → 本函数 → 解析器
// sub_50AF40；析构 → sub_4CF8F0）。初始化 5 个 std::string 成员
//（+8/+76/+120/+148/+224，SSO cap=15 模式），无数组成员；尾调 sub_4CF050 二段初始化。
// 返回 this。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D03E0(int this)  // vt+548（§1.2）、0x4D6690 硬直强度 vt+704（第 27 轮）
{
  *(uint32_t *)(this + 28) = 15;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // 写 this+8 = 0（技能槽记录首字）
  *(uint32_t *)(this + 60) = 0;  // this+60〔nFadeValue60(推断)〕等 2 字段
  *(uint32_t *)(this + 64) = 0;  // this+64〔apServerTabBtn(推断)〕等 2 字段
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 96) = 15;  // this+96〔nStatusMode(推断)〕等 2 字段
  *(uint32_t *)(this + 92) = 0;  // this+92〔pFxObjC(推断)〕等 2 字段
  *(uint8_t *)(this + 76) = 0;  // this+76〔pBtnActionE〕
  *(uint32_t *)(this + 104) = 0;  // this+104〔nTimerEnd(推断)〕
  *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
  *(uint32_t *)(this + 112) = 0;  // 写 this+112 = 0（宿主组件）
  *(uint32_t *)(this + 140) = 15;  // this+140〔nAdd140(推断)〕
  *(uint32_t *)(this + 136) = 0;  // this+136〔nCtx136(推断)〕等 2 字段
  *(uint8_t *)(this + 120) = 0;  // 写 this+120 = 0（动画对象）
  *(uint32_t *)(this + 168) = 15;  // this+168〔pAppendVec(推断)〕等 2 字段
  *(uint32_t *)(this + 164) = 0;  // this+164〔fAdd164(推断)〕
  *(uint8_t *)(this + 148) = 0;  // 写 this+148 = 0（动画帧计数）
  *(uint32_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  *(uint32_t *)(this + 180) = 0;  // this+180〔nRadius(推断)〕
  *(uint32_t *)(this + 184) = 0;  // this+184〔bSingleTarget(推断)〕
  *(uint32_t *)(this + 192) = 0;  // this+192〔nDlgId(推断)〕
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;  // this+200〔nMainState(推断)〕
  *(uint32_t *)(this + 208) = 0;  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 212) = 0;  // this+212〔nField212(推断)〕
  *(uint32_t *)(this + 216) = 0;  // this+216〔bField216(推断)〕
  *(uint32_t *)(this + 244) = 15;  // 写 this+244 = 15（浮点时刻槽）
  *(uint32_t *)(this + 240) = 0;  // 写 this+240 = 0（同步参数B）
  *(uint8_t *)(this + 224) = 0;  // this+224〔nSnapDst224(推断)〕
  sub_4CF050((void *)this);  // 调 二段初始化
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4D04C0 sub_4D04C0
// 【定案】对象工厂 case 3 构造器（0x4D2D60 case 3：new 0xC8 → 本函数 → 解析器
// sub_50B400；析构 → sub_4CFA50）。初始化 3 个 std::string 成员（+8/+84/+176，
// SSO cap=15 模式）+ 一段连续标量字段；尾调 sub_4CF120 二段初始化。返回 this。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D04C0(int this)  // 实现：SSO cap=15 模式）+ 一段连续标量字段；尾调 sub_4CF120 二段初始化。返回 this
{
  *(uint32_t *)(this + 28) = 15;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // 写 this+8 = 0（技能槽记录首字）
  *(uint32_t *)(this + 104) = 15;  // this+104〔nTimerEnd(推断)〕
  *(uint32_t *)(this + 100) = 0;  // this+100〔bEnchantDone(推断)〕
  *(uint8_t *)(this + 84) = 0;  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 112) = 0;  // 写 this+112 = 0（宿主组件）
  *(uint32_t *)(this + 116) = 0;  // 写 this+116 = 0（观察者容器）
  *(uint32_t *)(this + 120) = 0;  // 写 this+120 = 0（动画对象）
  *(uint32_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  *(uint32_t *)(this + 132) = 0;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 136) = 0;  // this+136〔nCtx136(推断)〕等 2 字段
  *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 0;  // 写 this+148 = 0（动画帧计数）
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 160) = 0;  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 164) = 0;  // this+164〔fAdd164(推断)〕
  *(uint32_t *)(this + 168) = 0;  // this+168〔pAppendVec(推断)〕等 2 字段
  *(uint32_t *)(this + 196) = 15;
  *(uint32_t *)(this + 192) = 0;  // this+192〔nDlgId(推断)〕
  *(uint8_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  sub_4CF120((char *)this);  // 调 二段初始化
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4D0570 sub_4D0570
// 【定案】对象工厂 case 0xE 构造器（0x4D2D60 case 0xE：new 0x168 → 本函数 → 解析器
// sub_50B840；析构 → sub_4CFC80）。初始化 8 个 std::string 成员
//（+8/+104/+132/+160/+188/+216/+244/+336，SSO cap=15 模式）——本家族里字符串
// 成员最多的一个对象；尾调 sub_4CF290 二段初始化。返回 this。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D0570(int this)  // 实现：成员最多的一个对象；尾调 sub_4CF290 二段初始化。返回 this
{
  *(uint32_t *)(this + 28) = 15;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // 写 this+8 = 0（技能槽记录首字）
  *(uint32_t *)(this + 124) = 15;  // 写 this+124 = 15（光环动画件）
  *(uint32_t *)(this + 120) = 0;  // 写 this+120 = 0（动画对象）
  *(uint8_t *)(this + 104) = 0;  // this+104〔nTimerEnd(推断)〕
  *(uint32_t *)(this + 152) = 15;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 0;  // 写 this+148 = 0（动画帧计数）
  *(uint8_t *)(this + 132) = 0;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 180) = 15;  // this+180〔nRadius(推断)〕
  *(uint32_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  *(uint8_t *)(this + 160) = 0;  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 208) = 15;  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 204) = 0;  // this+204〔pSubAnim204(推断)〕
  *(uint8_t *)(this + 188) = 0;  // this+188〔nStatusIdx(推断)〕
  *(uint32_t *)(this + 236) = 15;  // 写 this+236 = 15（同步参数A）
  *(uint32_t *)(this + 232) = 0;  // 写 this+232 = 0（时刻同步开关位）
  *(uint8_t *)(this + 216) = 0;  // this+216〔bField216(推断)〕
  *(uint32_t *)(this + 264) = 15;  // this+264〔nAnimHandle(推断)〕
  *(uint32_t *)(this + 260) = 0;  // 写 this+260 = 0（基类四元组 dword 槽 4）
  *(uint8_t *)(this + 244) = 0;  // 写 this+244 = 0（浮点时刻槽）
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;  // this+276〔pMapEntry〕
  *(uint32_t *)(this + 280) = 0;  // this+280〔pMapEntryVecEnd〕
  *(uint32_t *)(this + 288) = 0;  // this+288〔pMaster288(推断)〕
  *(uint32_t *)(this + 292) = 0;  // this+292〔nOpenMode292(推断)〕
  *(uint32_t *)(this + 296) = 0;  // this+296〔bInitFlag296(推断)〕
  *(uint32_t *)(this + 304) = 0;  // this+304〔pLayer304(推断)〕
  *(uint32_t *)(this + 308) = 0;  // this+1232〔pNameTagCtrl(推断)〕
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 324) = 0;  // this+324〔nRandPick324〕
  *(uint32_t *)(this + 328) = 0;  // this+1312〔pRowVec1312〕
  *(uint32_t *)(this + 356) = 15;
  *(uint32_t *)(this + 352) = 0;  // this+352〔uHitCtx352〕
  *(uint8_t *)(this + 336) = 0;
  sub_4CF290((char *)this);  // 调 二段初始化
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4D0680 sub_4D0680
// 【定案】对象工厂 case 5 构造器（0x4D2D60 case 5：new 0xA4 → 本函数 → 解析器
// sub_4F5B90；析构 → sub_4CFB40）。逐个构造 10 个 std::string 成员后清零若干标量
// 字段，返回 this。sub_41BFE0 = std::string 构造（szPassword 即空串 "" 常量，
// 语义化工具对默认实参空串的标注）；尾调 sub_4CF480 二段初始化。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D0680(int this)  // 实现：语义化工具对默认实参空串的标注）；尾调 sub_4CF480 二段初始化
{
  void **pThis_4; // ecx

  pThis_4 = (void **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  *pThis_4 = nullptr;  // pThis_4=this+16 nChannelTypeSel
  sub_41BFE0(pThis_4, szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 8) = 0;  // 写 this+8 = 0（技能槽记录首字）
  sub_41BFE0((void **)(this + 8), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 12) = 0;  // 写 this+12 = 0（技能槽记录次字）
  sub_41BFE0((void **)(this + 12), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 16) = 0;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
  sub_41BFE0((void **)(this + 16), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  sub_41BFE0((void **)(this + 80), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 88) = 0;  // this+88〔pFxObjB(推断)〕等 2 字段
  sub_41BFE0((void **)(this + 88), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 104) = 0;  // this+104〔nTimerEnd(推断)〕
  sub_41BFE0((void **)(this + 104), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
  sub_41BFE0((void **)(this + 108), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 112) = 0;  // 写 this+112 = 0（宿主组件）
  sub_41BFE0((void **)(this + 112), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 116) = 0;  // 写 this+116 = 0（观察者容器）
  sub_41BFE0((void **)(this + 116), szPassword);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 124) = 0;  // 写 this+124 = 0（光环动画件）
  *(uint32_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  *(uint32_t *)(this + 132) = 0;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 140) = 0;  // this+140〔nAdd140(推断)〕
  *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 0;  // 写 this+148 = 0（动画帧计数）
  sub_4CF480((void *)this);  // 调 二段初始化
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4D07A0 sub_4D07A0
// 【定案】对象工厂 case 0xA 构造器（0x4D2D60 case 0xA：new 0x3C → 本函数 → 解析器
// sub_500330）。在 this+16 处构造 1 个 std::string（sub_4015C0 = string::assign 空串），
// 清零 this+0..12 的标量头与 this+48 起的 vector 头（+48/+52/+56 = begin/end/cap）；
// 若 vector 已持有堆缓冲（begin 非空）则先释放——说明该函数也可对复用对象做整体复位。
// 返回 this。
// ------------------------------------------------------------
char */*thiscall*/ sub_4D07A0(char *this)
{
  char *pThis_10; // ecx

  pThis_10 = this + 16;  // this+16 频道型选中索引
  *((uint32_t *)pThis_10 + 6) = 15;  // pThis_10=this+16 频道型选中索引
  *((uint32_t *)pThis_10 + 5) = 0;  // pThis_10=this+16 频道型选中索引
  pThis_10[4] = 0;  // pThis_10=this+16 频道型选中索引
  *((uint32_t *)this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *((uint32_t *)this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *((uint32_t *)this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  *(uint32_t *)this = 0;  // *this = 0
  *((uint32_t *)this + 1) = 0;  // 写 this+4 = 0（宿主对象指针）
  *((uint32_t *)this + 2) = 0;  // 写 this+8 = 0（技能槽记录首字）
  *(this + 12) = 0;  // 写 this+12 = 0（技能槽记录次字）
  sub_4015C0((size_t *)pThis_10, szPassword, 0);  // 【std::string构造赋值】
  if ( *((uint32_t *)this + 12) != 0 )  // this+48〔pCmdVecBegin48(推断)〕
    j__free(*((void **)this + 12));  // this+12 物品类型号
  *((uint32_t *)this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *((uint32_t *)this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *((uint32_t *)this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4D0830 sub_4D0830
// 【定案】对象工厂 case 0xD 构造器（0x4D2D60 case 0xD：new 0x50 → 本函数 → 解析器
// sub_4FD4C0；析构 → sub_4CFC20）。在 this+4 与 this+32 处各构造 1 个 std::string，清零标量头与
// this+68 起的 vector 头（+68/+72/+76 = begin/end/cap，持有堆缓冲则先释放——
// 兼具对复用对象的复位职能）。返回 this。
// ------------------------------------------------------------
char */*thiscall*/ sub_4D0830(char *this)  // 实现：兼具对复用对象的复位职能）。返回 this
{
  char *pThis_4; // ecx

  pThis_4 = this + 4;  // this+4 宿主对象
  *((uint32_t *)pThis_4 + 6) = 15;  // pThis_4=this+4 宿主对象
  *((uint32_t *)pThis_4 + 5) = 0;  // pThis_4=this+4 宿主对象
  pThis_4[4] = 0;  // pThis_4=this+4 宿主对象
  *((uint32_t *)this + 14) = 15;  // this+56〔pCmdVecCap56(推断)〕
  *((uint32_t *)this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *(this + 36) = 0;  // 写 this+36 = 0（状态字）
  *((uint32_t *)this + 17) = 0;  // this+68〔nCharCount(推断)〕
  *((uint32_t *)this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
  *((uint32_t *)this + 19) = 0;  // this+76〔pBtnActionE〕
  *(uint32_t *)this = 0;  // *this = 0
  sub_4015C0((size_t *)pThis_4, szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 8, szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 15) = 0;  // this+60〔nFadeValue60(推断)〕
  if ( *((uint32_t *)this + 17) != 0 )  // this+68〔nCharCount(推断)〕
    j__free(*((void **)this + 17));  // this+17〔bEnable〕
  *((uint32_t *)this + 17) = 0;  // this+68〔nCharCount(推断)〕
  *((uint32_t *)this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
  *((uint32_t *)this + 19) = 0;  // this+76〔pBtnActionE〕
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4D1680 sub_4D1680
// 数据对象构造器（对象工厂 case 0..14 家族成员）：整对象清零 + 成员初始化，返回 this。
// this+4 似乎是个子对象头（先取 sub_425940(this+4) 存入 +8）；+40/+52/+84/+96 处
// 各挂一个空链表哨兵（sub_4CE710/730/750/770 = 分配 8 字节环形链表头节点，
// 配对析构 0x4D1860 里 next=prev=自身 的初始化可证）；+284/+312 两个 std::string；
// +344 起 3 组×4 dword 清零；+396 处对象经 sub_4CE9F0
// 构造后其指针回填 +424（链表/容器头指向自身首元素）；尾调 sub_4D13A0 三段初始化。
// 【定案】对象工厂 case 7 构造器（0x4D2D60 case 7：new 0x1D8 → 本函数 → 解析器
// sub_5078C0；析构分派 → 0x4D1860）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D1680(int this)  // 实现：sub_5078C0；析构分派 → 0x4D1860）
{
  int pThis_4; // edi
  uint32_t *pThis_158; // eax
  int i; // ecx

  pThis_4 = this + 4;  // this+4 宿主对象
  *(uint32_t *)(this + 8) = sub_425940(this + 4);  // 链表哨兵节点
  *(uint32_t *)(pThis_4 + 8) = 0;  // pThis_4+8〔nSkillRec8(推断)〕
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  *(uint32_t *)(this + 40) = sub_4CE710();  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = sub_4CE730();  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 64) = 0;  // this+64〔apServerTabBtn(推断)〕等 2 字段
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 72) = 0;  // this+72〔nSnapshot72(推断)〕等 2 字段
  *(uint32_t *)(this + 84) = sub_4CE750();  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 88) = 0;  // this+88〔pFxObjB(推断)〕等 2 字段
  *(uint32_t *)(this + 96) = sub_4CE770();  // this+96〔nStatusMode(推断)〕等 2 字段
  *(uint32_t *)(this + 100) = 0;  // this+100〔bEnchantDone(推断)〕
  *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
  *(uint32_t *)(this + 112) = 0;  // 写 this+112 = 0（宿主组件）
  *(uint32_t *)(this + 116) = 0;  // 写 this+116 = 0（观察者容器）
  *(uint32_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  *(uint32_t *)(this + 132) = 0;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 136) = 0;  // this+136〔nCtx136(推断)〕等 2 字段
  *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 0;  // 写 this+148 = 0（动画帧计数）
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 172) = 0;  // this+172〔pAppendVecEnd(推断)〕等 2 字段
  *(uint32_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  *(uint32_t *)(this + 180) = 0;  // this+180〔nRadius(推断)〕
  *(uint32_t *)(this + 188) = 0;  // this+188〔nStatusIdx(推断)〕
  *(uint32_t *)(this + 192) = 0;  // this+192〔nDlgId(推断)〕
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 204) = 0;  // this+204〔pSubAnim204(推断)〕
  *(uint32_t *)(this + 208) = 0;  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 212) = 0;  // this+212〔nField212(推断)〕
  *(uint32_t *)(this + 248) = 0;  // 写 this+248 = 0（基类四元组字节槽 1）
  *(uint32_t *)(this + 252) = 0;  // 写 this+252 = 0（基类四元组 dword 槽 2）
  *(uint32_t *)(this + 256) = 0;  // 写 this+256 = 0（基类四元组字节槽 3）
  *(uint32_t *)(this + 260) = 0;  // 写 this+260 = 0（基类四元组 dword 槽 4）
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;  // this+276〔pMapEntry〕
  *(uint32_t *)(this + 304) = 15;  // this+304〔pLayer304(推断)〕
  *(uint32_t *)(this + 300) = 0;  // this+300〔pAnim300〕
  *(uint8_t *)(this + 284) = 0;  // this+284〔bBindGate284(推断)〕
  *(uint32_t *)(this + 332) = 15;  // this+332〔bReservedConn〕
  *(uint32_t *)(this + 328) = 0;  // this+1312〔pRowVec1312〕
  *(uint8_t *)(this + 312) = 0;
  pThis_158 = (uint32_t *)(this + 344);  // this+344〔nReservedDelay〕
  for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
  {
    *pThis_158 = 0;  // pThis_158=this+344 nReservedDelay
    pThis_158[1] = 0;  // pThis_158=this+344 nReservedDelay
    pThis_158[2] = 0;  // pThis_158=this+344 nReservedDelay
    pThis_158[3] = 0;  // pThis_158=this+344 nReservedDelay
    pThis_158 += 4;  // pThis_158=this+344 nReservedDelay
  }
  sub_4CE9F0((uint32_t *)(this + 396));  // this+396〔uReflectCtx(推断)〕
  *(uint32_t *)(this + 444) = 0;  // 字段 this+444〔包围盒右界〕
  *(uint32_t *)(this + 448) = 0;  // this+448〔uAtkStage448(推断)〕
  *(uint32_t *)(this + 452) = 0;  // this+452〔nAtkRollVal(推断)〕
  *(uint32_t *)(this + 460) = 0;  // 写 this+460 = 0（累积伤害）
  *(uint32_t *)(this + 464) = 0;  // this+464 仅见复位
  *(uint32_t *)(this + 468) = 0;
  *(uint32_t *)(this + 424) = 0;  // 写 this+424 = 0（攻击倍率×10）
  *(uint32_t *)(this + 428) = 0;
  *(uint32_t *)(this + 432) = 0;  // this+1728〔nDblClickSlotA(推断)〕
  *(uint32_t *)(this + 436) = 0;  // 写 this+436 = 0（攻击数据表取值）
  *(uint32_t *)(this + 424) = this + 396;  // 写 this+424 = this + 396（攻击倍率×10）
  sub_4D13A0(this);  // 调 三段初始化
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4D1860 sub_4D1860
// 对象工厂 case 7 类的析构器（0x4D2B30 分派表 case 7 可证；构造器 = 0x4D1680）：
// 先析构 +428 处 3 个"内含 std::string 的小对象"数组元素，再按套路拆掉各容器——
// vector（+268/+172/+144/+128/+64）先逐元素析构再 free 存储块；环形链表
// （+96/+84/+52/+40/+8）先 next=prev=自身 断链，再沿 next 逐节点 free
//（+84/+40 节点内还有 std::string 要 tidy）；散字符串（+400/+312/+284）按 SSO
// 惯例 cap>=0x10 才 free；裸堆块（+460/+444/+204/+188/+108/+24）直接 free。无返回值。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D1860(int this)  // 实现：惯例 cap>=0x10 才 free；裸堆块（+460/+444/+204/+188/+108/+24）直接 free。无返回值
{
  uint32_t *pThis_1AC; // eax
  int pStrElem; // edi
  void **fld_10C; // edi
  uint32_t *fld_AC; // edi
  uint32_t *fld_B0; // eax
  uint32_t *pElemCap; // edi
  void **fld_90; // edi
  void **fld_80; // edi
  void **fld_60; // eax
  void **pNodeWalk96; // edi
  bool bListEmpty; // zf
  uint32_t **fld_54; // eax
  uint32_t *pNodeWalk84; // edi
  uint32_t *fld_542; // eax
  void *pInnerVecData; // eax
  int fld_40; // eax
  int fld_44; // edx
  int pInnerVecWalk; // edi
  uint32_t **fld_34; // ecx
  uint32_t *pNodeWalk52; // eax
  uint32_t *pNextNode52; // edi
  void **fld_28; // eax
  void **pNodeWalk40; // edi
  void **fld_282; // eax
  uint32_t **nStrCap_6; // ecx
  uint32_t *pNodeWalk8; // eax
  uint32_t *pNextNode8; // edi
  int i; // [esp+10h] [ebp-14h]
  void **j; // [esp+10h] [ebp-14h]
  uint32_t *fld_B02; // [esp+10h] [ebp-14h]
  void **k; // [esp+10h] [ebp-14h]
  void **m; // [esp+10h] [ebp-14h]
  void **pNextNode96; // [esp+10h] [ebp-14h]
  uint32_t *pNextNode84; // [esp+10h] [ebp-14h]
  int fld_402; // [esp+10h] [ebp-14h]
  void **pNextNode40; // [esp+10h] [ebp-14h]
  uint32_t *pThis_1AC2; // [esp+14h] [ebp-10h]
  int fld_442; // [esp+14h] [ebp-10h]

  pThis_1AC = (uint32_t *)(this + 428);
  pThis_1AC2 = (uint32_t *)(this + 428);
  for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
  {
    pStrElem = *pThis_1AC;
    if ( *pThis_1AC != 0 )
    {
      if ( *(uint32_t *)(pStrElem + 24) >= 0x10u )
        j__free(*(void **)(pStrElem + 4));  // 调 堆释放
      *(uint32_t *)(pStrElem + 24) = 15;
      *(uint32_t *)(pStrElem + 20) = 0;
      *(uint8_t *)(pStrElem + 4) = 0;
      j__free((void *)pStrElem);  // 调 堆释放
      pThis_1AC = pThis_1AC2;
    }
    *pThis_1AC++ = 0;
    pThis_1AC2 = pThis_1AC;
  }
  if ( *(uint32_t *)(this + 460) != 0 )  // 判定 “+460 累积伤害”
    j__free(*(void **)(this + 460));  // 释放 this+460〔bSpiritFlag(推断)〕堆块
  *(uint32_t *)(this + 460) = 0;  // 写 this+460 = 0（累积伤害）
  *(uint32_t *)(this + 464) = 0;  // this+464 仅见复位
  *(uint32_t *)(this + 468) = 0;
  if ( *(uint32_t *)(this + 444) != 0 )  // 字段 this+444〔包围盒右界〕
    j__free(*(void **)(this + 444));  // 调 堆释放
  *(uint32_t *)(this + 444) = 0;  // 字段 this+444〔包围盒右界〕
  *(uint32_t *)(this + 448) = 0;  // this+448〔uAtkStage448(推断)〕
  *(uint32_t *)(this + 452) = 0;  // this+452〔nAtkRollVal(推断)〕
  if ( *(uint32_t *)(this + 420) >= 0x10u )
    j__free(*(void **)(this + 400));  // 调 堆释放
  *(uint32_t *)(this + 420) = 15;
  *(uint32_t *)(this + 416) = 0;
  *(uint8_t *)(this + 400) = 0;
  if ( *(uint32_t *)(this + 332) >= 0x10u )  // this+332〔bReservedConn〕
    j__free(*(void **)(this + 312));  // 调 堆释放
  *(uint32_t *)(this + 332) = 15;  // this+332〔bReservedConn〕
  *(uint32_t *)(this + 328) = 0;  // this+1312〔pRowVec1312〕
  *(uint8_t *)(this + 312) = 0;
  if ( *(uint32_t *)(this + 304) >= 0x10u )  // this+304〔pLayer304(推断)〕
    j__free(*(void **)(this + 284));  // 释放 this+284〔bBindGate284(推断)〕堆块
  *(uint32_t *)(this + 304) = 15;  // this+304〔pLayer304(推断)〕
  *(uint32_t *)(this + 300) = 0;  // this+300〔pAnim300〕
  *(uint8_t *)(this + 284) = 0;  // this+284〔bBindGate284(推断)〕
  fld_10C = *(void ***)(this + 268);
  if ( fld_10C != nullptr )  // 若 fld_10C 有效（非空）
  {
    for ( j = *(void ***)(this + 272); fld_10C != j; ++fld_10C )
      sub_41B010(fld_10C);  // 驻留句柄析构（引用计数减到 0 释放）
    j__free(*(void **)(this + 268));  // 调 堆释放
  }
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;  // this+276〔pMapEntry〕
  if ( *(uint32_t *)(this + 204) != 0 )  // this+204〔pSubAnim204(推断)〕
    j__free(*(void **)(this + 204));  // 释放 this+204〔pSubAnim204(推断)〕堆块
  *(uint32_t *)(this + 204) = 0;  // this+204〔pSubAnim204(推断)〕
  *(uint32_t *)(this + 208) = 0;  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 212) = 0;  // this+212〔nField212(推断)〕
  if ( *(uint32_t *)(this + 188) != 0 )  // this+188〔nStatusIdx(推断)〕
    j__free(*(void **)(this + 188));  // 释放 this+188〔nStatusIdx(推断)〕堆块
  *(uint32_t *)(this + 188) = 0;  // this+188〔nStatusIdx(推断)〕
  *(uint32_t *)(this + 192) = 0;  // this+192〔nDlgId(推断)〕
  *(uint32_t *)(this + 196) = 0;
  fld_AC = *(uint32_t **)(this + 172);  // this+688〔nSnapshot688〕
  if ( fld_AC != nullptr )  // 若 fld_AC 有效（非空）
  {
    fld_B0 = *(uint32_t **)(this + 176);  // this+704〔nSnapshot704〕
    fld_B02 = fld_B0;  // fld_B0=this+704 nSnapshot704
    if ( fld_AC != fld_B0 )  // fld_AC=this+688 nSnapshot688
    {
      pElemCap = fld_AC + 6;  // fld_AC=this+688 nSnapshot688
      do
      {
        if ( *pElemCap >= 0x10u )
        {
          j__free((void *)*(pElemCap - 5));  // 调 堆释放
          fld_B0 = fld_B02;  // fld_B0=this+704 nSnapshot704
        }
        *pElemCap = 15;
        *(pElemCap - 1) = 0;
        *((uint8_t *)pElemCap - 20) = 0;
        pElemCap += 9;
      }
      while ( pElemCap - 6 != fld_B0 );  // fld_B0=this+704 nSnapshot704
    }
    j__free(*(void **)(this + 172));  // 释放 this+172〔pAppendVecEnd(推断)〕堆块
  }
  *(uint32_t *)(this + 172) = 0;  // this+172〔pAppendVecEnd(推断)〕等 2 字段
  *(uint32_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  *(uint32_t *)(this + 180) = 0;  // this+180〔nRadius(推断)〕
  fld_90 = *(void ***)(this + 144);  // this+576〔uOffset576(推断)〕
  if ( fld_90 != nullptr )  // 若 fld_90 有效（非空）
  {
    for ( k = *(void ***)(this + 148); fld_90 != k; ++fld_90 )  // this+148 第 4 组·+802 增量子倍率
      sub_41B010(fld_90);  // 驻留句柄析构（引用计数减到 0 释放）
    j__free(*(void **)(this + 144));  // 释放 this+144〔pFrameList144(推断)〕堆块
  }
  *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 0;  // 写 this+148 = 0（动画帧计数）
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  fld_80 = *(void ***)(this + 128);  // this+512〔nAbilityId(推断)〕
  if ( fld_80 != nullptr )  // 若 fld_80 有效（非空）
  {
    for ( m = *(void ***)(this + 132); fld_80 != m; ++fld_80 )  // this+132 第 3 组·+60 增量项
      sub_41B010(fld_80);  // 驻留句柄析构（引用计数减到 0 释放）
    j__free(*(void **)(this + 128));  // 释放 this+128〔szStatusKeyBuf(推断)〕堆块
  }
  *(uint32_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  *(uint32_t *)(this + 132) = 0;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 136) = 0;  // this+136〔nCtx136(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 108) != 0 )  // this+108〔nAdd108(推断)〕
    j__free(*(void **)(this + 108));  // 释放 this+108〔nAdd108(推断)〕堆块
  *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
  *(uint32_t *)(this + 112) = 0;  // 写 this+112 = 0（宿主组件）
  *(uint32_t *)(this + 116) = 0;  // 写 this+116 = 0（观察者容器）
  fld_60 = *(void ***)(this + 96);  // this+384〔nAnimNameCap(推断)〕
  pNodeWalk96 = (void **)*fld_60;  // fld_60=this+384 nAnimNameCap
  *fld_60 = fld_60;  // fld_60=this+384 nAnimNameCap
  *(uint32_t *)(*(uint32_t *)(this + 96) + 4) = *(uint32_t *)(this + 96);  // this+96〔nStatusMode(推断)〕等 2 字段
  bListEmpty = pNodeWalk96 == *(void ***)(this + 96);  // this+384〔nAnimNameCap(推断)〕
  *(uint32_t *)(this + 100) = 0;  // this+100〔bEnchantDone(推断)〕
  if ( !bListEmpty )  // bListEmpty=this+384 nAnimNameCap
  {
    do
    {
      pNextNode96 = (void **)*pNodeWalk96;
      if ( pNodeWalk96[7] != nullptr )
        j__free(pNodeWalk96[7]);  // 调 堆释放
      pNodeWalk96[7] = nullptr;
      pNodeWalk96[8] = nullptr;
      pNodeWalk96[9] = nullptr;
      j__free(pNodeWalk96);  // 调 堆释放
      pNodeWalk96 = pNextNode96;
    }
    while ( pNextNode96 != *(void ***)(this + 96) );  // this+384〔nAnimNameCap(推断)〕
  }
  j__free(*(void **)(this + 96));  // 释放 this+96〔nStatusMode(推断)〕堆块
  *(uint32_t *)(this + 96) = 0;  // this+96〔nStatusMode(推断)〕等 2 字段
  fld_54 = *(uint32_t ***)(this + 84);  // this+84 插值起点 X
  pNodeWalk84 = *fld_54;  // fld_54=this+84 插值起点 X
  *fld_54 = fld_54;  // fld_54=this+84 插值起点 X
  *(uint32_t *)(*(uint32_t *)(this + 84) + 4) = *(uint32_t *)(this + 84);  // this+84〔pFxObjA(推断)〕
  fld_542 = *(uint32_t **)(this + 84);  // this+84 插值起点 X
  *(uint32_t *)(this + 88) = 0;  // this+88〔pFxObjB(推断)〕等 2 字段
  if ( pNodeWalk84 != fld_542 )  // fld_542=this+84 插值起点 X
  {
    do
    {
      pInnerVecData = (void *)pNodeWalk84[12];
      pNextNode84 = (uint32_t *)*pNodeWalk84;
      if ( pInnerVecData != nullptr )  // 若 pInnerVecData 有效（非空）
        j__free(pInnerVecData);  // 调 堆释放
      pNodeWalk84[12] = 0;
      pNodeWalk84[13] = 0;
      pNodeWalk84[14] = 0;
      j__free(pNodeWalk84);  // 调 堆释放
      pNodeWalk84 = pNextNode84;
    }
    while ( pNextNode84 != *(uint32_t **)(this + 84) );  // this+84 插值起点 X
  }
  j__free(*(void **)(this + 84));  // 释放 this+84〔pFxObjA(推断)〕堆块
  *(uint32_t *)(this + 84) = 0;  // this+84〔pFxObjA(推断)〕
  fld_40 = *(uint32_t *)(this + 64);  // this+64〔apServerTabBtn(推断)〕等 2 字段
  if ( fld_40 != 0 )  // fld_40=this+64 apServerTabBtn
  {
    fld_44 = *(uint32_t *)(this + 68);  // this+68〔nCharCount(推断)〕
    fld_442 = fld_44;  // fld_44=this+68 nCharCount
    fld_402 = *(uint32_t *)(this + 64);  // this+64〔apServerTabBtn(推断)〕等 2 字段
    if ( fld_40 != fld_44 )  // fld_40=this+64 apServerTabBtn
    {
      pInnerVecWalk = fld_40 + 44;  // fld_40=this+64 apServerTabBtn
      do
      {
        if ( *(uint32_t *)pInnerVecWalk != 0 )
        {
          j__free(*(void **)pInnerVecWalk);  // 调 堆释放
          fld_40 = fld_402;  // fld_40=this+64 apServerTabBtn
          fld_44 = fld_442;  // fld_44=this+68 nCharCount
        }
        fld_40 += 56;  // fld_40=this+64 apServerTabBtn
        *(uint32_t *)pInnerVecWalk = 0;  // *pInnerVecWalk = 0
        *(uint32_t *)(pInnerVecWalk + 4) = 0;
        *(uint32_t *)(pInnerVecWalk + 8) = 0;
        pInnerVecWalk += 56;
        fld_402 = fld_40;  // fld_402=this+64 apServerTabBtn
      }
      while ( fld_40 != fld_44 );  // fld_40=this+64 apServerTabBtn
    }
    j__free(*(void **)(this + 64));  // 释放 this+64〔apServerTabBtn(推断)〕堆块
  }
  *(uint32_t *)(this + 64) = 0;  // this+64〔apServerTabBtn(推断)〕等 2 字段
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 72) = 0;  // this+72〔nSnapshot72(推断)〕等 2 字段
  fld_34 = *(uint32_t ***)(this + 52);  // this+208〔nField208(推断)〕
  pNodeWalk52 = *fld_34;  // fld_34=this+208 nField208
  *fld_34 = fld_34;  // fld_34=this+208 nField208
  *(uint32_t *)(*(uint32_t *)(this + 52) + 4) = *(uint32_t *)(this + 52);  // this+52〔bAuraState(推断)〕等 2 字段
  bListEmpty = pNodeWalk52 == *(uint32_t **)(this + 52);  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  if ( !bListEmpty )  // bListEmpty=this+208 nField208
  {
    do
    {
      pNextNode52 = (uint32_t *)*pNodeWalk52;
      j__free(pNodeWalk52);  // 调 堆释放
      pNodeWalk52 = pNextNode52;
    }
    while ( pNextNode52 != *(uint32_t **)(this + 52) );  // this+208〔nField208(推断)〕
  }
  j__free(*(void **)(this + 52));  // 释放 this+52〔bAuraState(推断)〕堆块
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  fld_28 = *(void ***)(this + 40);  // this+160〔fAdd160(推断)〕
  pNodeWalk40 = (void **)*fld_28;  // fld_28=this+160 fAdd160
  *fld_28 = fld_28;  // fld_28=this+160 fAdd160
  *(uint32_t *)(*(uint32_t *)(this + 40) + 4) = *(uint32_t *)(this + 40);  // 涉及字段 “+40 状态子标志”
  fld_282 = *(void ***)(this + 40);  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
  if ( pNodeWalk40 != fld_282 )  // fld_282=this+160 fAdd160
  {
    do
    {
      pNextNode40 = (void **)*pNodeWalk40;
      if ( (unsigned int)pNodeWalk40[8] >= 0x10 )
        j__free(pNodeWalk40[3]);  // 调 堆释放
      pNodeWalk40[8] = (void *)15;  // pNodeWalk40[8] = 转换(15)
      pNodeWalk40[7] = nullptr;
      *((uint8_t *)pNodeWalk40 + 12) = 0;
      j__free(pNodeWalk40);  // 调 堆释放
      pNodeWalk40 = pNextNode40;
    }
    while ( pNextNode40 != *(void ***)(this + 40) );  // this+160〔fAdd160(推断)〕
  }
  j__free(*(void **)(this + 40));  // 释放 this+40〔bStateSub40(推断)〕堆块
  *(uint32_t *)(this + 40) = 0;  // 写 this+40 = 0（状态子标志）
  if ( *(uint32_t *)(this + 24) != 0 )  // this+24〔nPageMax(推断)〕等 2 字段
    j__free(*(void **)(this + 24));  // 释放 this+24〔nPageMax(推断)〕堆块
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  nStrCap_6 = *(uint32_t ***)(this + 8);  // this+32〔nHeight(推断)〕
  pNodeWalk8 = *nStrCap_6;  // fld_8=this+32 nHeight
  *nStrCap_6 = nStrCap_6;  // fld_8=this+32 nHeight
  *(uint32_t *)(*(uint32_t *)(this + 8) + 4) = *(uint32_t *)(this + 8);  // 涉及字段 “+8 技能槽记录首字”
  bListEmpty = pNodeWalk8 == *(uint32_t **)(this + 8);  // this+32〔nHeight(推断)〕
  *(uint32_t *)(this + 12) = 0;  // 写 this+12 = 0（技能槽记录次字）
  if ( !bListEmpty )  // bListEmpty=this+32 nHeight
  {
    do
    {
      pNextNode8 = (uint32_t *)*pNodeWalk8;
      j__free(pNodeWalk8);  // 调 堆释放
      pNodeWalk8 = pNextNode8;
    }
    while ( pNextNode8 != *(uint32_t **)(this + 8) );  // this+32〔nHeight(推断)〕
  }
  j__free(*(void **)(this + 8));  // 释放 this+8〔nSkillRec8(推断)〕堆块
  *(uint32_t *)(this + 8) = 0;  // 写 this+8 = 0（技能槽记录首字）
}


// ------------------------------------------------------------
// 0x4D1D70 sub_4D1D70
// 链表成员拆除辅助：把 this+4 处链表的节点经 sub_4D0A20（list 迁移/拼接）挪进栈上
// 临时头，再 free 原链表哨兵节点并清零 +4/+8。固定返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D1D70(int this)  // 实现：临时头，再 free 原链表哨兵节点并清零 +4/+8。固定返回 0
{
  int tmpListHead; // [esp+4h] [ebp-4h] BYREF

  sub_4D0A20((int)&tmpListHead, **(void ***)(this + 4), *(uint32_t *)(this + 4));  // 调 迁出后 free 其哨兵并清零 +100/+104
  j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
  *(uint32_t *)(this + 4) = 0;  // 写 this+4 = 0（宿主对象指针）
  *(uint32_t *)(this + 8) = 0;  // 写 this+8 = 0（技能槽记录首字）
  return 0;
}



// ------------------------------------------------------------
// 0x4D1DB0 sub_4D1DB0
// 【定案】对象工厂 case 0xC 析构器（0x4D2B30 case 0xC → 本函数；构造器 0x4D2640）：
// 先 free 四个 std::string 成员（+112/+64/+36/+8，cap>=0x10 才动堆），
// 中途把 this+100 链表的节点经 sub_4D0A20 迁出后 free 其哨兵并清零 +100/+104。
// 栈上 tmpHead5 为传给 sub_4D0A20 的接收头（v3[1]=this、v3[4]=2 的具体含义未确证）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D1DB0(int this)  // 实现：栈上 tmpHead5 为传给 sub_4D0A20 的接收头（v3[1]=this、v3[4]=2 的具体含义未确证）
{
  bool fld_84; // cf
  int tmpHead5[5]; // [esp+Ch] [ebp-14h] BYREF

  tmpHead5[1] = this;
  fld_84 = *(uint32_t *)(this + 132) < 0x10u;  // this+132〔nAgeTicks〕
  tmpHead5[4] = 2;
  if ( !fld_84 )  // fld_84=this+132 nAgeTicks
    j__free(*(void **)(this + 112));  // this+112〔pHostComp112〕
  *(uint32_t *)(this + 132) = 15;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  *(uint8_t *)(this + 112) = 0;  // 写 this+112 = 0（宿主组件）
  sub_4D0A20((int)tmpHead5, **(void ***)(this + 100), *(uint32_t *)(this + 100));  // 调 迁出后 free 其哨兵并清零 +100/+104
  j__free(*(void **)(this + 100));  // 释放 this+100〔bEnchantDone(推断)〕堆块
  *(uint32_t *)(this + 100) = 0;  // this+100〔bEnchantDone(推断)〕
  *(uint32_t *)(this + 104) = 0;  // this+104〔nTimerEnd(推断)〕
  if ( *(uint32_t *)(this + 84) >= 0x10u )  // this+84〔pFxObjA(推断)〕
    j__free(*(void **)(this + 64));  // 释放 this+64〔apServerTabBtn(推断)〕堆块
  *(uint32_t *)(this + 84) = 15;  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  *(uint8_t *)(this + 64) = 0;  // this+64〔apServerTabBtn(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 56) >= 0x10u )  // this+56〔pCmdVecCap56(推断)〕等 2 字段
    j__free(*(void **)(this + 36));  // 释放 this+36〔nStateWord36(推断)〕堆块
  *(uint32_t *)(this + 56) = 15;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint8_t *)(this + 36) = 0;  // 写 this+36 = 0（状态字）
  if ( *(uint32_t *)(this + 28) >= 0x10u )  // this+28〔pPanelVec(推断)〕等 2 字段
    j__free(*(void **)(this + 8));  // 释放 this+8〔nSkillRec8(推断)〕堆块
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 28) = 15;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // 写 this+8 = 0（技能槽记录首字）
}



// ------------------------------------------------------------
// 0x4D1EA0 sub_4D1EA0
// 大对象复位/构造辅助（对象工厂数据面）：开头写对象类型码 this+0 = 4，随后
// ① this+4 起 5 个步长 28 的 std::string 空串初始化；② this+152 起 6 条步长 79
// 的记录整体清零，并释放两组各 6 项小结构（+632、+728 区）里持有的堆指针；
// ③ 再初始化十余个 std::string（908/1216 区两组 0x1C×N 数组等）；
// ④ 清空 4 个 vector（+1444/+1452/+1532/+1548 段的 begin/end/cap）与 4 个裸堆块；
// ⑤ 收尾 this+820 = 100（【推断】某百分比/等级类默认值），返回最后一次 string 初始化值。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D1EA0(char *this)  // 实现：⑤ 收尾 this+820 = 100（(推断)某百分比/等级类默认值），返回最后一次 string 初始化值
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

  *(uint32_t *)this = 4;  // *this = 4
  *((uint32_t *)this + 36) = 0;  // this+144〔pFrameList144(推断)〕
  *((uint32_t *)this + 37) = 0;  // 写 this+148 = 0（动画帧计数）
  pThis_4 = this + 4;  // this+4 宿主对象
  for ( i = 5; i != 0; --i )  // 循环：i 从 5 递减到 0
  {
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    pThis_4 += 28;  // pThis_4=this+4 宿主对象
  }
  pThis_278 = this + 632;
  pThis_2782 = this + 632;
  pThis_A0 = this + 160;  // this+160 第 5 组·+1040 增量子倍率
  for ( j = 6; j != 0; --j )  // 循环：j 从 6 递减到 0
  {
    *((uint32_t *)pThis_A0 - 2) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint32_t *)pThis_A0 - 1) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *(uint16_t *)pThis_A0 = 0;  // *pThis_A0 = 0
    *((uint16_t *)pThis_A0 + 1) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint16_t *)pThis_A0 + 2) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint16_t *)pThis_A0 + 3) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint32_t *)pThis_A0 + 2) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint32_t *)pThis_A0 + 3) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint32_t *)pThis_A0 + 4) = 0;  // this+4 宿主对象
    *((uint32_t *)pThis_A0 + 5) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint32_t *)pThis_A0 + 6) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint32_t *)pThis_A0 + 7) = 0;  // this+7 【推断】路径尾终止位
    *((uint32_t *)pThis_A0 + 8) = 0;  // this+8 物品 id
    *((uint32_t *)pThis_A0 + 9) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint32_t *)pThis_A0 + 10) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint32_t *)pThis_A0 + 11) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint32_t *)pThis_A0 + 12) = 0;  // this+12 物品类型号
    *((uint16_t *)pThis_A0 + 26) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint16_t *)pThis_A0 + 27) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint16_t *)pThis_A0 + 28) = 0;  // this+28 【推断】逐帧驱动对象
    *((uint16_t *)pThis_A0 + 29) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint16_t *)pThis_A0 + 30) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint16_t *)pThis_A0 + 31) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    *((uint16_t *)pThis_A0 + 32) = 0;  // this+32 格子像素尺寸
    *(uint32_t *)(pThis_A0 + 66) = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    pThis_A0[70] = 0;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    if ( *(uint32_t *)pThis_278 != 0 )
    {
      j__free(*(void **)pThis_278);  // 调 堆释放
      pThis_278 = pThis_2782;
    }
    *(uint32_t *)pThis_278 = 0;  // *pThis_278 = 0
    *((uint32_t *)pThis_278 + 1) = 0;
    *((uint32_t *)pThis_278 + 2) = 0;
    if ( *((uint32_t *)pThis_278 + 24) != 0 )  // this+24 页数上限
    {
      j__free(*((void **)pThis_278 + 24));  // this+24 页数上限
      pThis_278 = pThis_2782;
    }
    *((uint32_t *)pThis_278 + 24) = 0;  // this+24 页数上限
    *((uint32_t *)pThis_278 + 25) = 0;
    *((uint32_t *)pThis_278 + 26) = 0;
    pThis_278 += 16;
    pThis_A0 += 79;  // pThis_A0=this+160 第 5 组·+1040 增量子倍率
    pThis_2782 = pThis_278;
  }
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_38C = this + 908;
  for ( k = 2; k != 0; --k )  // 循环：k 从 2 递减到 0
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
  for ( m = 4; m != 0; --m )  // 循环：m 从 4 递减到 0
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
  if ( pThis_169 != nullptr )  // 若 pThis_169 有效（非空）
  {
    for ( n = *((void ***)this + 362); pThis_169 != n; ++pThis_169 )
      sub_41B010(pThis_169);  // 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 361));  // 调 堆释放
  }
  *((uint32_t *)this + 361) = 0;
  *((uint32_t *)this + 362) = 0;
  *((uint32_t *)this + 363) = 0;
  pThis_16D = *((void ***)this + 365);  // pThis_16D=this+1460 M_CHARACTER_SELECT 一次性发送标志
  if ( pThis_16D != nullptr )  // 若 pThis_16D 有效（非空）
  {
    for ( ii = *((void ***)this + 366); pThis_16D != ii; ++pThis_16D )  // pThis_16D=this+1460 M_CHARACTER_SELECT 一次性发送标志
      sub_41B010(pThis_16D);  // 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 365));  // 调 堆释放
  }
  *((uint32_t *)this + 365) = 0;  // this+1460〔bCharSelSent〕
  *((uint32_t *)this + 366) = 0;  // this+1464〔nSelState〕
  *((uint32_t *)this + 367) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pThis_17F = *((void ***)this + 383);
  if ( pThis_17F != nullptr )  // 若 pThis_17F 有效（非空）
  {
    for ( jj = *((void ***)this + 384); pThis_17F != jj; ++pThis_17F )  // this+384 【推断】动画件名 SSO 容量判据
      sub_41B010(pThis_17F);  // 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 383));  // 调 堆释放
  }
  *((uint32_t *)this + 383) = 0;
  *((uint32_t *)this + 384) = 0;  // this+384 【推断】动画件名 SSO 容量判据
  *((uint32_t *)this + 385) = 0;
  pThis_183 = *((void ***)this + 387);
  if ( pThis_183 != nullptr )  // 若 pThis_183 有效（非空）
  {
    for ( kk = *((void ***)this + 388); pThis_183 != kk; ++pThis_183 )  // this+388 【推断】攻击上下文浮点值
      sub_41B010(pThis_183);  // 驻留句柄析构（引用计数减到 0 释放）
    j__free(*((void **)this + 387));  // 调 堆释放
  }
  *((uint32_t *)this + 387) = 0;
  *((uint32_t *)this + 388) = 0;  // this+388 【推断】攻击上下文浮点值
  *((uint32_t *)this + 389) = 0;
  pThis_187 = *((uint32_t *)this + 391);
  if ( pThis_187 != 0 )
  {
    sub_4B4950(pThis_187, *((uint32_t *)this + 392));  // 16 字节记录数组析构（逐元素清 +4 向量后 free）
    j__free(*((void **)this + 391));  // 调 堆释放
  }
  *((uint32_t *)this + 391) = 0;
  *((uint32_t *)this + 392) = 0;  // 写 字段 this+392〔对象的当前格（+112/+116）〕
  *((uint32_t *)this + 393) = 0;
  if ( *((uint32_t *)this + 395) != 0 )
    j__free(*((void **)this + 395));  // 调 堆释放
  *((uint32_t *)this + 395) = 0;
  *((uint32_t *)this + 396) = 0;  // this+396 【推断】技能参数索引槽
  *((uint32_t *)this + 397) = 0;
  if ( *((uint32_t *)this + 399) != 0 )
    j__free(*((void **)this + 399));  // 调 堆释放
  *((uint32_t *)this + 399) = 0;
  *((uint32_t *)this + 400) = 0;
  *((uint32_t *)this + 401) = 0;
  if ( *((uint32_t *)this + 403) != 0 )
    j__free(*((void **)this + 403));  // 调 堆释放
  *((uint32_t *)this + 403) = 0;
  *((uint32_t *)this + 404) = 0;
  *((uint32_t *)this + 405) = 0;
  if ( *((uint32_t *)this + 407) != 0 )
    j__free(*((void **)this + 407));  // 调 堆释放
  *((uint32_t *)this + 407) = 0;
  *((uint32_t *)this + 408) = 0;  // this+408 【推断】攻击盒肢体槽 A
  *((uint32_t *)this + 409) = 0;
  result = sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *((uint32_t *)this + 205) = 100;
  return result;
}


// ------------------------------------------------------------
// 0x4D2320 sub_4D2320
// 大对象构造器（对象工厂 case 0..14 家族成员）：+4 处 0x1C×5 对象数组、
// this+152 起 6 条步长 79 的记录清零、+628/+724 两处 0x10×6 string 数组、
// 十余个独立 std::string（SSO cap=15 模式）、+908/+1104/+1216 三处 0x1C 数组，
// 最后清零尾部标量字段。返回 this。
// 【定案】对象工厂 case 0 类的构造器：0x4D26E0（case 0 析构器，0x4D2B30 分派表可证）
// 拆的数组/字符串布局与本函数一一对应。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D2320(int this)  // 实现：拆的数组/字符串布局与本函数一一对应
{
  int pThis_98; // eax
  int i; // ecx

  `eh vector constructor iterator'((void *)(this + 4), 0x1Cu, 5, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);  // 空串初始化（len 0 / cap 15 / 首字节 0；this+4 系）
  pWalk152 = this + 152;  // this+152 第 4 组·+886 增量
  for ( i = 6; i != 0; --i )  // 循环：i 从 6 递减到 0
  {
    *(uint32_t *)pWalk152 = 0;  // *pWalk152 = 0
    *(uint32_t *)(pWalk152 + 4) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint16_t *)(pWalk152 + 8) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint16_t *)(pWalk152 + 10) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint16_t *)(pWalk152 + 12) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint16_t *)(pWalk152 + 14) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint32_t *)(pWalk152 + 16) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint32_t *)(pWalk152 + 20) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint32_t *)(pWalk152 + 24) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint32_t *)(pWalk152 + 28) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint32_t *)(pWalk152 + 32) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint32_t *)(pWalk152 + 36) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint32_t *)(pWalk152 + 40) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint32_t *)(pWalk152 + 44) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint32_t *)(pWalk152 + 48) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint32_t *)(pWalk152 + 52) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint32_t *)(pWalk152 + 56) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint16_t *)(pWalk152 + 60) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint16_t *)(pWalk152 + 62) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint16_t *)(pWalk152 + 64) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint16_t *)(pWalk152 + 66) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint16_t *)(pWalk152 + 68) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint16_t *)(pWalk152 + 70) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint16_t *)(pWalk152 + 72) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint32_t *)(pWalk152 + 74) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    *(uint8_t *)(pWalk152 + 78) = 0;  // pWalk152=this+152 第 4 组·+886 增量
    pWalk152 += 79;  // pWalk152=this+152 第 4 组·+886 增量
  }
  `eh vector constructor iterator'(
    (void *)(this + 628),
    0x10u,
    6,
    (void (/*thiscall*/ *)(void *))sub_4019A0,  // 指针 vector 三字段清零（起/止/容量 = 0）
    (void (/*thiscall*/ *)(void *))sub_5E5260);  // 调 动画子对象清理临时缓冲
  `eh vector constructor iterator'(
    (void *)(this + 724),  // this+724 叉子攻击浮点
    0x10u,
    6,
    (void (/*thiscall*/ *)(void *))sub_4019A0,  // 指针 vector 三字段清零（起/止/容量 = 0）
    (void (/*thiscall*/ *)(void *))sub_5E5260);  // 调 动画子对象清理临时缓冲
  *(uint32_t *)(this + 848) = 15;
  *(uint32_t *)(this + 844) = 0;
  *(uint8_t *)(this + 828) = 0;
  *(uint32_t *)(this + 876) = 15;  // this+876 句柄走虚
  *(uint32_t *)(this + 872) = 0;
  *(uint8_t *)(this + 856) = 0;
  *(uint32_t *)(this + 904) = 15;
  *(uint32_t *)(this + 900) = 0;
  *(uint8_t *)(this + 884) = 0;
  `eh vector constructor iterator'((void *)(this + 908), 0x1Cu, 2, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);  // 空串初始化（len 0 / cap 15 / 首字节 0；this+4 系）
  *(uint32_t *)(this + 988) = 15;  // this+988〔uCfgA988(推断)〕
  *(uint32_t *)(this + 984) = 0;  // this+984〔aStateBlk984(推断)〕
  *(uint8_t *)(this + 968) = 0;  // 写 this+968 = 0（载荷缓冲指针）
  *(uint32_t *)(this + 1016) = 15;  // this+1016〔uGrabB1016(推断)〕
  *(uint32_t *)(this + 1012) = 0;  // this+1012〔uGrabA1012〕
  *(uint8_t *)(this + 996) = 0;  // this+996〔bCfgC996(推断)〕
  *(uint32_t *)(this + 1044) = 15;  // this+1044〔bPickupOk1044〕
  *(uint32_t *)(this + 1040) = 0;
  *(uint8_t *)(this + 1024) = 0;  // this+1024〔nBurnT1_1024〕
  *(uint32_t *)(this + 1072) = 15;
  *(uint32_t *)(this + 1068) = 0;
  *(uint8_t *)(this + 1052) = 0;
  *(uint32_t *)(this + 1100) = 15;  // this+1100〔nFairyGrade(推断)〕
  *(uint32_t *)(this + 1096) = 0;
  *(uint8_t *)(this + 1080) = 0;  // this+1080〔nAnimIdx1080〕
  `eh vector constructor iterator'((void *)(this + 1104), 0x1Cu, 4, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);  // 空串初始化（len 0 / cap 15 / 首字节 0；this+4 系）
  `eh vector constructor iterator'((void *)(this + 1216), 0x1Cu, 4, (void (/*thiscall*/ *)(void *))sub_40C120, sub_501490);  // 空串初始化（len 0 / cap 15 / 首字节 0；this+4 系）
  *(uint32_t *)(this + 1352) = 15;
  *(uint32_t *)(this + 1348) = 0;
  *(uint8_t *)(this + 1332) = 0;  // 写 this+1332 = 0（装备/动画定义对象）
  *(uint32_t *)(this + 1380) = 15;
  *(uint32_t *)(this + 1376) = 0;
  *(uint8_t *)(this + 1360) = 0;
  *(uint32_t *)(this + 1408) = 15;
  *(uint32_t *)(this + 1404) = 0;
  *(uint8_t *)(this + 1388) = 0;
  *(uint32_t *)(this + 1436) = 15;  // 写 this+1436 = 15（场景类型/装备类别）
  *(uint32_t *)(this + 1432) = 0;  // 写 this+1432 = 0（效果触发锁存标志）
  *(uint8_t *)(this + 1416) = 0;
  *(uint32_t *)(this + 1444) = 0;
  *(uint32_t *)(this + 1448) = 0;
  *(uint32_t *)(this + 1452) = 0;
  *(uint32_t *)(this + 1460) = 0;  // this+1460〔bCharSelSent〕
  *(uint32_t *)(this + 1464) = 0;  // this+1464〔nSelState〕
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
  *(uint32_t *)(this + 1664) = 15;  // this+6656〔nRateDen(推断)〕
  *(uint32_t *)(this + 1660) = 0;
  *(uint8_t *)(this + 1644) = 0;
  sub_4D1EA0((char *)this);  // 调 ⑤ 收尾 this+820 = 100（(推断)某百分比/等级类默认值），返回最后一次 string 初始化值
  return this;  // 返回自身指针
}


// ------------------------------------------------------------
// 0x4D2640 sub_4D2640
// 【定案】对象工厂 case 0xC 构造器（0x4D2D60 case 0xC：new 0x88 → 本函数 → 解析器
// sub_4FD040；析构 → sub_4D1DB0）：4 个 std::string（+8/+36/+64/+112）+ +96 处一个环形链表
// （sub_4CE790 分配 72+ 字节哨兵节点，+69 置 1，next/prev/第3指针均指自身），
// 尾调 sub_4D1020 二段初始化。返回 this。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D2640(int this)  // 实现：尾调 sub_4D1020 二段初始化。返回 this
{
  int pThis_60; // edi
  uint32_t *pSentinel; // eax

  *(uint32_t *)(this + 28) = 15;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // 写 this+8 = 0（技能槽记录首字）
  *(uint32_t *)(this + 56) = 15;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint8_t *)(this + 36) = 0;  // 写 this+36 = 0（状态字）
  *(uint32_t *)(this + 84) = 15;  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  *(uint8_t *)(this + 64) = 0;  // this+64〔apServerTabBtn(推断)〕等 2 字段
  pThis_60 = this + 96;  // this+96 插值终点 X / 落点偏移
  pSentinel = sub_4CE790();  // 调 分配 72+ 字节哨兵节点
  *(uint32_t *)(pThis_60 + 4) = pSentinel;  // pThis_60+4〔宿主对象〕
  *((uint8_t *)pSentinel + 69) = 1;
  *(uint32_t *)(*(uint32_t *)(pThis_60 + 4) + 4) = *(uint32_t *)(pThis_60 + 4);  // pThis_60+4〔宿主对象〕
  **(uint32_t **)(pThis_60 + 4) = *(uint32_t *)(pThis_60 + 4);  // pThis_60+4〔宿主对象〕
  *(uint32_t *)(*(uint32_t *)(pThis_60 + 4) + 8) = *(uint32_t *)(pThis_60 + 4);  // pThis_60+4〔宿主对象〕
  *(uint32_t *)(pThis_60 + 8) = 0;  // pThis_60+8〔nSkillRec8(推断)〕
  *(uint32_t *)(this + 132) = 15;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  *(uint8_t *)(this + 112) = 0;  // 写 this+112 = 0（宿主组件）
  sub_4D1020(this);  // 调 二段初始化
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4D26E0 sub_4D26E0
// 对象工厂 case 0 类的析构器（0x4D2B30 分派表 case 0 可证；构造器 = 0x4D2320，
// 两侧 eh vector 数组布局 +4(0x1C×5)/+628/+724(0x10×6)/+908(0x1C×2)/+1104/+1216(0x1C×4)
// 逐一对应）。套路同 0x4D1860：散字符串 SSO cap>=0x10 才 free、裸堆块直接 free、
// +1564 处对象经 sub_4B4950 通告后释放；无返回值。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D26E0(int this)  // 实现：+1564 处对象经 sub_4B4950 通告后释放；无返回值
{
  int fld_61C; // eax

  if ( *(uint32_t *)(this + 1664) >= 0x10u )  // this+6656〔nRateDen(推断)〕
    j__free(*(void **)(this + 1644));  // 调 堆释放
  *(uint32_t *)(this + 1664) = 15;  // this+6656〔nRateDen(推断)〕
  *(uint32_t *)(this + 1660) = 0;
  *(uint8_t *)(this + 1644) = 0;
  if ( *(uint32_t *)(this + 1628) != 0 )
    j__free(*(void **)(this + 1628));  // 调 堆释放
  *(uint32_t *)(this + 1628) = 0;
  *(uint32_t *)(this + 1632) = 0;
  *(uint32_t *)(this + 1636) = 0;
  if ( *(uint32_t *)(this + 1612) != 0 )
    j__free(*(void **)(this + 1612));  // 调 堆释放
  *(uint32_t *)(this + 1612) = 0;
  *(uint32_t *)(this + 1616) = 0;
  *(uint32_t *)(this + 1620) = 0;
  if ( *(uint32_t *)(this + 1596) != 0 )
    j__free(*(void **)(this + 1596));  // 调 堆释放
  *(uint32_t *)(this + 1596) = 0;
  *(uint32_t *)(this + 1600) = 0;
  *(uint32_t *)(this + 1604) = 0;
  if ( *(uint32_t *)(this + 1580) != 0 )
    j__free(*(void **)(this + 1580));  // 调 堆释放
  *(uint32_t *)(this + 1580) = 0;
  *(uint32_t *)(this + 1584) = 0;
  *(uint32_t *)(this + 1588) = 0;
  fld_61C = *(uint32_t *)(this + 1564);
  if ( fld_61C != 0 )
  {
    sub_4B4950(fld_61C, *(uint32_t *)(this + 1568));  // 16 字节记录数组析构（逐元素清 +4 向量后 free）
    j__free(*(void **)(this + 1564));  // 调 堆释放
  }
  *(uint32_t *)(this + 1564) = 0;
  *(uint32_t *)(this + 1568) = 0;
  *(uint32_t *)(this + 1572) = 0;
  sub_4017E0(this + 1544);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  sub_4017E0(this + 1528);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 1524) >= 0x10u )
    j__free(*(void **)(this + 1504));  // 调 堆释放
  *(uint32_t *)(this + 1524) = 15;
  *(uint32_t *)(this + 1520) = 0;
  *(uint8_t *)(this + 1504) = 0;
  if ( *(uint32_t *)(this + 1496) >= 0x10u )
    j__free(*(void **)(this + 1476));  // 调 堆释放
  *(uint32_t *)(this + 1496) = 15;
  *(uint32_t *)(this + 1492) = 0;
  *(uint8_t *)(this + 1476) = 0;
  sub_4017E0(this + 1456);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  sub_4017E0(this + 1440);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  if ( *(uint32_t *)(this + 1436) >= 0x10u )  // 判定 “+1436 场景类型/装备类别”
    j__free(*(void **)(this + 1416));  // 调 堆释放
  *(uint32_t *)(this + 1436) = 15;  // 写 this+1436 = 15（场景类型/装备类别）
  *(uint32_t *)(this + 1432) = 0;  // 写 this+1432 = 0（效果触发锁存标志）
  *(uint8_t *)(this + 1416) = 0;
  if ( *(uint32_t *)(this + 1408) >= 0x10u )
    j__free(*(void **)(this + 1388));  // 调 堆释放
  *(uint32_t *)(this + 1408) = 15;
  *(uint32_t *)(this + 1404) = 0;
  *(uint8_t *)(this + 1388) = 0;
  if ( *(uint32_t *)(this + 1380) >= 0x10u )
    j__free(*(void **)(this + 1360));  // 调 堆释放
  *(uint32_t *)(this + 1380) = 15;
  *(uint32_t *)(this + 1376) = 0;
  *(uint8_t *)(this + 1360) = 0;
  if ( *(uint32_t *)(this + 1352) >= 0x10u )
    j__free(*(void **)(this + 1332));  // this+1332〔pEquipDef1332〕
  *(uint32_t *)(this + 1352) = 15;
  *(uint32_t *)(this + 1348) = 0;
  *(uint8_t *)(this + 1332) = 0;  // 写 this+1332 = 0（装备/动画定义对象）
  `eh vector destructor iterator'((void *)(this + 1216), 0x1Cu, 4, sub_501490);  // 调 对象析构后释放堆块
  `eh vector destructor iterator'((void *)(this + 1104), 0x1Cu, 4, sub_501490);  // 调 对象析构后释放堆块
  if ( *(uint32_t *)(this + 1100) >= 0x10u )  // this+1100〔nFairyGrade(推断)〕
    j__free(*(void **)(this + 1080));  // this+1080〔nAnimIdx1080〕
  *(uint32_t *)(this + 1100) = 15;  // this+1100〔nFairyGrade(推断)〕
  *(uint32_t *)(this + 1096) = 0;
  *(uint8_t *)(this + 1080) = 0;  // this+1080〔nAnimIdx1080〕
  if ( *(uint32_t *)(this + 1072) >= 0x10u )
    j__free(*(void **)(this + 1052));  // 调 堆释放
  *(uint32_t *)(this + 1072) = 15;
  *(uint32_t *)(this + 1068) = 0;
  *(uint8_t *)(this + 1052) = 0;
  if ( *(uint32_t *)(this + 1044) >= 0x10u )  // this+1044〔bPickupOk1044〕
    j__free(*(void **)(this + 1024));  // this+1024〔nBurnT1_1024〕
  *(uint32_t *)(this + 1044) = 15;  // this+1044〔bPickupOk1044〕
  *(uint32_t *)(this + 1040) = 0;
  *(uint8_t *)(this + 1024) = 0;  // this+1024〔nBurnT1_1024〕
  if ( *(uint32_t *)(this + 1016) >= 0x10u )  // this+1016〔uGrabB1016(推断)〕
    j__free(*(void **)(this + 996));  // 释放 this+996〔bCfgC996(推断)〕堆块
  *(uint32_t *)(this + 1016) = 15;  // this+1016〔uGrabB1016(推断)〕
  *(uint32_t *)(this + 1012) = 0;  // this+1012〔uGrabA1012〕
  *(uint8_t *)(this + 996) = 0;  // this+996〔bCfgC996(推断)〕
  if ( *(uint32_t *)(this + 988) >= 0x10u )  // this+988〔uCfgA988(推断)〕
    j__free(*(void **)(this + 968));  // this+968〔pBlobData〕
  *(uint32_t *)(this + 988) = 15;  // this+988〔uCfgA988(推断)〕
  *(uint32_t *)(this + 984) = 0;  // this+984〔aStateBlk984(推断)〕
  *(uint8_t *)(this + 968) = 0;  // 写 this+968 = 0（载荷缓冲指针）
  `eh vector destructor iterator'((void *)(this + 908), 0x1Cu, 2, sub_501490);  // 调 对象析构后释放堆块
  if ( *(uint32_t *)(this + 904) >= 0x10u )
    j__free(*(void **)(this + 884));  // 调 堆释放
  *(uint32_t *)(this + 904) = 15;
  *(uint32_t *)(this + 900) = 0;
  *(uint8_t *)(this + 884) = 0;
  if ( *(uint32_t *)(this + 876) >= 0x10u )  // this+876 句柄走虚
    j__free(*(void **)(this + 856));  // 调 堆释放
  *(uint32_t *)(this + 876) = 15;  // this+876 句柄走虚
  *(uint32_t *)(this + 872) = 0;
  *(uint8_t *)(this + 856) = 0;
  if ( *(uint32_t *)(this + 848) >= 0x10u )
    j__free(*(void **)(this + 828));  // 调 堆释放
  *(uint32_t *)(this + 848) = 15;
  *(uint32_t *)(this + 844) = 0;
  *(uint8_t *)(this + 828) = 0;
  `eh vector destructor iterator'((void *)(this + 724), 0x10u, 6, (void (/*thiscall*/ *)(void *))sub_5E5260);  // 调 动画子对象清理临时缓冲
  `eh vector destructor iterator'((void *)(this + 628), 0x10u, 6, (void (/*thiscall*/ *)(void *))sub_5E5260);  // 调 动画子对象清理临时缓冲
  `eh vector destructor iterator'((void *)(this + 4), 0x1Cu, 5, sub_501490);  // 调 对象析构后释放堆块
}


// ------------------------------------------------------------
// 0x4D2B30 sub_4D2B30
// ------------------------------------------------------------
// 对象工厂析构分派：按 this+288(运行期 case id) 分发到对应类的析构器 + free。
// 与 0x4D2D60（构造侧）成对；case 表 = 14 类对象（0x4D26E0/0x4CF5C0/...）。
// 依据：研究 18/19 —— 对象工厂 case 1 = 0x5A0 角色/怪物数据对象。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D2B30(uint32_t *this, void *Block)  // 实现：依据：研究 18/19 —— 对象工厂 case 1 = 0x5A0 角色/怪物数据对象
{
  switch ( *(this + 72) )  // 按 *(this + 72) 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4D26E0(Block);  // 调 +1564 处对象经 sub_4B4950 通告后释放；无返回值
        j__free(Block);  // 调 堆释放
      }
      break;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4CF5C0(Block);
        j__free(Block);  // 调 堆释放
      }
      break;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4CF8F0(Block);
        j__free(Block);  // 调 堆释放
      }
      break;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4CFA50(Block);
        j__free(Block);  // 调 堆释放
      }
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_439810(Block);  // 装备数据对象析构
        j__free(Block);  // 调 堆释放
      }
      break;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4CFB40(Block);
        j__free(Block);  // 调 堆释放
      }
      break;
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4D10A0(Block);  // 调 容器清理（19L）
        j__free(Block);  // 调 堆释放
      }
      break;
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4D1860(Block);  // 调 惯例 cap>=0x10 才 free；裸堆块（+460/+444/+204/+188/+108/+24）直接 free。无返回值
        j__free(Block);  // 调 堆释放
      }
      break;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4A2EB0(Block);  // 【推断】单个 MSVC std::string 析构
        j__free(Block);  // 调 堆释放
      }
      break;
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4D1100(Block);  // 调 容器清理（8L）
        j__free(Block);  // 调 堆释放
      }
      break;
    case 0xA:
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4CE850(Block);
        j__free(Block);  // 调 堆释放
      }
      break;
    case 0xB:
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4D1140((int)Block);  // 调 大清理（67L）：+304/+284/+260… 多段 vector 逐段 free 清零
        j__free(Block);  // 调 堆释放
      }
      break;
    case 0xC:
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4D1DB0(Block);  // 调 栈上 tmpHead5 为传给 sub_4D0A20 的接收头（v3[1]=this、v3[4]=2 的具体含义未确证）
        j__free(Block);  // 调 堆释放
      }
      break;
    case 0xD:
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4CFC20(Block);
        j__free(Block);  // 调 堆释放
      }
      break;
    case 0xE:
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4CFC80(Block);
        j__free(Block);  // 调 堆释放
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
int /*thiscall*/ sub_4D2D60(uint32_t *this, const char *ArgList, int nArg3)  // 实现：与 0x4D2B30（析构分派）成对
{
  void *pMem; // eax
  int pObj; // esi
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

  switch ( *(this + 72) )  // 按 *(this + 72) 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      pMem = operator new(0x684u);  // 堆分配 1668 字节对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        pObj = sub_4D2320(pMem);  // 调 构造 → 本函数
      else
        pObj = 0;
      if ( (uint8_t)sub_50C290(pObj, ArgList) != 0 )  // 职业(growtype/角色成长)定义解析器（67 标签，本文件唯一大 解析器）
        return pObj;
      if ( pObj == 0 )
        return 0;
      sub_4D26E0(pObj);  // 调 +1564 处对象经 sub_4B4950 通告后释放；无返回值
      goto LABEL_101;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      pMem2 = operator new(0x5A0u);  // 堆分配 1440 字节对象
      if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
        pObj = sub_4D01E0(pMem2);  // 调 尾调 sub_4CEB80 做二段初始化（见 gunner_state.cpp 同名函数）。返回 this
      else
        pObj = 0;
      if ( sub_509C90(pObj, (int)ArgList) != 0 )  // 怪物数据文件解析器（MonsterBaseParameter.tbl 族；技能/属性块通用）
        return pObj;
      if ( pObj == 0 )
        return 0;
      sub_4CF5C0(pObj);
      goto LABEL_101;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      pMem3 = operator new(0xF8u);  // 堆分配 248 字节对象
      if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
        pObj = sub_4D03E0(pMem3);
      else
        pObj = 0;
      if ( (uint8_t)sub_50AF40(pObj, ArgList) != 0 )  // 地图物件(map object)定义解析器
        return pObj;
      if ( pObj == 0 )
        return 0;
      sub_4CF8F0(pObj);
      goto LABEL_101;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      pMem4 = operator new(0xC8u);  // 堆分配 200 字节对象
      if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
        pObj = sub_4D04C0(pMem4);  // 调 SSO cap=15 模式）+ 一段连续标量字段；尾调 sub_4CF120 二段初始化。返回 this
      else
        pObj = 0;
      if ( (uint8_t)sub_50B400(pObj, ArgList) != 0 )  // PassiveObject(PO)定义解析器（普通物件，非技能 PO）
        return pObj;
      if ( pObj == 0 )
        return 0;
      sub_4CFA50(pObj);
      goto LABEL_101;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      pMem5 = operator new(0x85Cu);  // 堆分配 2140 字节对象
      if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
        pObj = sub_439680(pMem5);  // 结果 = 装备数据对象构造（0x85C）
      else
        pObj = 0;
      if ( (uint8_t)sub_4F7C60(pObj, (char)ArgList) != 0 )  // 装备(equipment/avatar)定义解析器（81 标签，全库单函数标签数第一）
        return pObj;
      if ( pObj == 0 )
        return 0;
      sub_439810(pObj);  // 装备数据对象析构
      goto LABEL_101;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      pMem6 = operator new(0xA4u);  // 堆分配 164 字节对象
      if ( pMem6 != nullptr )  // 若 pMem6 有效（非空）
        pObj = sub_4D0680(pMem6);  // 调 语义化工具对默认实参空串的标注）；尾调 sub_4CF480 二段初始化
      else
        pObj = 0;
      if ( (uint8_t)sub_4F5B90(pObj, (char)ArgList) != 0 )  // 可堆叠物品(stackable)定义解析器（39 标签）
        return pObj;
      if ( pObj == 0 )
        return 0;
      sub_4CFB40(pObj);
      goto LABEL_101;
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      pMem7 = operator new(0x34u);  // 堆分配 52 字节对象
      if ( pMem7 != nullptr )  // 若 pMem7 有效（非空）
        pObj = sub_4D0B30(pMem7);  // 调 容器清理（10L）
      else
        pObj = 0;
      if ( (uint8_t)sub_507690(pObj, (char)ArgList) != 0 )  // 瓦片(tile)定义解析器
        return pObj;
      if ( pObj == 0 )
        return 0;
      sub_4D10A0(pObj);  // 调 容器清理（19L）
      goto LABEL_101;
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      pMem8 = operator new(0x1D8u);  // 堆分配 472 字节对象
      if ( pMem8 != nullptr )  // 若 pMem8 有效（非空）
        pObj = sub_4D1680(pMem8);  // 调 析构分派 → 0x4D1860）
      else
        pObj = 0;
      if ( (uint8_t)sub_5078C0(pObj, (char)ArgList) != 0 )  // 副本地图(dungeon map)定义解析器（0x1D8 字节对象，sub_4D1680 构
        return pObj;
      if ( pObj == 0 )
        return 0;
      sub_4D1860(pObj);  // 调 惯例 cap>=0x10 才 free；裸堆块（+460/+444/+204/+188/+108/+24）直接 free。无返回值
      goto LABEL_101;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      pMem9 = operator new(0x98u);  // 堆分配 152 字节对象
      if ( pMem9 != nullptr )  // 若 pMem9 有效（非空）
        pObj = sub_4A3520(pMem9);  // 调 (推断)攻击上下文重置（string 复位 + 0x4A3450 默认值）—— 复合重置器
      else
        pObj = 0;
      if ( sub_503BA0(pObj, ArgList) != 0 )  // 怪物/PassiveObject 攻击定义解析器（attackinfo 结构填充）
        return pObj;
      if ( pObj == 0 )
        return 0;
      if ( *(uint32_t *)(pObj + 116) >= 0x10u )  // pObj+116〔会话上下文〕
        j__free(*(void **)(pObj + 96));  // pObj+96〔nStatusMode(推断)〕
      *(uint32_t *)(pObj + 116) = 15;  // pObj+116〔会话上下文〕
      *(uint32_t *)(pObj + 112) = 0;  // pObj+112〔pHostComp112〕
      *(uint8_t *)(pObj + 96) = 0;  // pObj+96〔nStatusMode(推断)〕
      goto LABEL_101;
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      pMem10 = operator new(0xE0u);  // 堆分配 224 字节对象
      if ( pMem10 != nullptr )  // 若 pMem10 有效（非空）
        pObj = sub_4D0C30(pMem10);  // 调 容器清理（29L）
      else
        pObj = 0;
      if ( (uint8_t)sub_500B30(pObj, ArgList) != 0 )  // 对象创建/运动定义解析器（PassiveObject 生成器，[creation pos]
        return pObj;
      if ( pObj == 0 )
        return 0;
      if ( *(uint32_t *)(pObj + 220) >= 0x10u )  // pObj+220〔nSnapDst220(推断)〕
        j__free(*(void **)(pObj + 200));  // pObj+200〔nMainState(推断)〕
      *(uint32_t *)(pObj + 220) = 15;  // pObj+220〔nSnapDst220(推断)〕
      *(uint32_t *)(pObj + 216) = 0;  // pObj+216〔bField216(推断)〕
      *(uint8_t *)(pObj + 200) = 0;  // pObj+200〔nMainState(推断)〕
      sub_428480(pObj + 180);  // 32B 元素容器清空
      goto LABEL_101;
    case 0xA:
      pMem11 = operator new(0x3Cu);  // 堆分配 60 字节对象
      if ( pMem11 != nullptr )  // 若 pMem11 有效（非空）
        pObj = sub_4D07A0(pMem11);
      else
        pObj = 0;
      if ( (uint8_t)sub_500330(pObj, (char)ArgList) != 0 )  // NPC 商店(npc shop)定义解析器
        return pObj;
      if ( pObj == 0 )
        return 0;
      if ( *(uint32_t *)(pObj + 48) != 0 )  // pObj+48〔pCmdVecBegin48(推断)〕
        j__free(*(void **)(pObj + 48));  // pObj+48〔pCmdVecBegin48(推断)〕
      *(uint32_t *)(pObj + 48) = 0;  // pObj+48〔pCmdVecBegin48(推断)〕
      *(uint32_t *)(pObj + 52) = 0;  // pObj+52〔bAuraState(推断)〕
      *(uint32_t *)(pObj + 56) = 0;  // pObj+56〔pCmdVecCap56(推断)〕
      if ( *(uint32_t *)(pObj + 40) >= 0x10u )  // pObj+40〔bStateSub40(推断)〕
        j__free(*(void **)(pObj + 20));  // pObj+20〔nPage(推断)〕
      *(uint32_t *)(pObj + 40) = 15;  // pObj+40〔bStateSub40(推断)〕
      *(uint32_t *)(pObj + 36) = 0;  // pObj+36〔nStateWord36(推断)〕
      *(uint8_t *)(pObj + 20) = 0;  // pObj+20〔nPage(推断)〕
      goto LABEL_101;
    case 0xB:
      pMem12 = operator new(0x144u);  // 堆分配 324 字节对象
      if ( pMem12 != nullptr )  // 若 pMem12 有效（非空）
        pObj = sub_4D0F00((int)pMem12);  // 调 字段族重置（44L）：+24..+112 三元组（容量15/首0/标志0）连清 —— std::string/vector 槽复位
      else
        pObj = 0;
      if ( (uint8_t)sub_4FF870(pObj, (char)ArgList) != 0 )  // 任务(quest)定义解析器
        return pObj;
      if ( pObj == 0 )
        return 0;
      sub_4D1140(pObj);  // 调 大清理（67L）：+304/+284/+260… 多段 vector 逐段 free 清零
      goto LABEL_101;
    case 0xC:
      pMem13 = operator new(0x88u);  // 堆分配 136 字节对象
      if ( pMem13 != nullptr )  // 若 pMem13 有效（非空）
        pObj = sub_4D2640(pMem13);  // 调 尾调 sub_4D1020 二段初始化。返回 this
      else
        pObj = 0;
      if ( (uint8_t)sub_4FD040(pObj, (char)ArgList) != 0 )  // 副本(dungeon)定义解析器
        return pObj;
      if ( pObj == 0 )
        return 0;
      sub_4D1DB0(pObj);  // 调 栈上 tmpHead5 为传给 sub_4D0A20 的接收头（v3[1]=this、v3[4]=2 的具体含义未确证）
      goto LABEL_101;
    case 0xD:
      pMem14 = operator new(0x50u);  // 堆分配 80 字节对象
      if ( pMem14 != nullptr )  // 若 pMem14 有效（非空）
        pObj = sub_4D0830(pMem14);  // 调 兼具对复用对象的复位职能）。返回 this
      else
        pObj = 0;
      if ( (uint8_t)sub_4FD4C0(pObj, (char)ArgList) != 0 )  // 地图(map)定义解析器
        return pObj;
      if ( pObj == 0 )
        return 0;
      sub_4CFC20(pObj);
      goto LABEL_101;
    case 0xE:
      pMem15 = operator new(0x168u);  // 堆分配 360 字节对象
      if ( pMem15 != nullptr )  // 若 pMem15 有效（非空）
        pObj = sub_4D0570(pMem15);  // 调 成员最多的一个对象；尾调 sub_4CF290 二段初始化。返回 this
      else
        pObj = 0;
      if ( (uint8_t)sub_50B840(pObj, ArgList) != 0 )  // 技能 PassiveObject / 觉醒(overskill)定义解析器
        return pObj;
      if ( pObj != 0 )
      {
        sub_4CFC80(pObj);
LABEL_101:
        j__free((void *)pObj);  // 调 堆释放
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
// 入参/出参：pDwArg1 = 随机数状态槽（读旧值、写回新值，调用方持槽复用）。
// ------------------------------------------------------------
int /*cdecl*/ sub_4D33A0(unsigned int *pDwArg1)  // 实现：入参/出参：pDwArg1 = 随机数状态槽（读旧值、写回新值，调用方持槽复用）
{
  unsigned int rnd1; // edx
  unsigned int rnd2; // ecx
  unsigned int rnd3; // eax

  rnd1 = 1103515245 * *pDwArg1 + 12345;
  rnd2 = 1103515245 * rnd1 + 12345;
  rnd3 = 1103515245 * rnd2 + 12345;
  *pDwArg1 = rnd3;
  return ((((HIWORD(rnd1) & 0x7FF) << 10) ^ HIWORD(rnd2) & 0x3FF) << 10) ^ HIWORD(rnd3) & 0x3FF;  // 调 取 32 位值高 16 位
}



// ------------------------------------------------------------
// 0x4D3400 sub_4D3400
// 去空白拷贝：把 pArg2 逐字符拷入 uArg1，跳过 9(TAB)/10(LF)/32(空格) 三种空白，
// 返回 strlen(pArg2)（非新串长）。【转写注意】uArg1[v3] = v6 的 v6 是 Hex-Rays
// 未定义寄存器残留（原意应为写 '\0' 终结符），忠实保留。
// ------------------------------------------------------------
signed int /*cdecl*/ sub_4D3400(uint8_t *uArg1, const char *pArg2)  // 实现：未定义寄存器残留（原意应为写 \0 终结符），忠实保留
{
  signed int nReadPos; // edx
  int nWritePos; // ebx
  char cCur; // al
  signed int result; // eax
  char v6; // cl

  nReadPos = 0;
  nWritePos = 0;
  if ( (int)strlen(pArg2) <= 0 )  // 调 求串长
  {
    *uArg1 = 0;
    return (signed int)uArg1;
  }
  else
  {
    do
    {
      cCur = pArg2[nReadPos];
      if ( cCur < 9 || cCur > 10 && cCur != 32 )  // 若 cCur < 9 与/或 cCur > 10 与/或 cCur != 32
        uArg1[nWritePos++] = cCur;
      ++nReadPos;
      result = strlen(pArg2);  // result = 调 strlen
    }
    while ( nReadPos < result );
    uArg1[nWritePos] = v6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D3470 sub_4D3470
// 定界拷贝（strncpy 语义，0x4D34D0 子串搜索的内部件）：源串长 > uArg3 时拷 uArg3
// 字节并补 '\0'；否则整串连 '\0' 逐字符拷入。返回值无业务意义（走拷贝分支时返回
// 源串末指针）。
// ------------------------------------------------------------
char */*cdecl*/ sub_4D3470(void *pArg1, void *pArg2, unsigned int uArg3)  // 实现：源串末指针）
{
  char *result; // eax
  char cCur; // cl

  if ( strlen((const char *)pArg2) > uArg3 )  // 调 求串长
  {
    qmemcpy(pArg1, pArg2, uArg3);  // 调 内存块拷贝(内联展开)
    *((uint8_t *)pArg1 + uArg3) = 0;
    return (char *)pArg1;
  }
  else
  {
    result = (char *)pArg2;
    do
    {
      cCur = *result;
      result[(uint8_t *)pArg1 - (uint8_t *)pArg2] = *result;
      ++result;
    }
    while ( cCur != 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D34D0 sub_4D34D0
// Shift-JIS 感知的子串搜索（strstr 变体）：在 pArg1 中找 pArg2 首次出现，命中返回
// &pArg1[命中位]，否则 nullptr。逐扫描位 malloc 临时串（sub_4D3470 定界拷贝）后
// strcmp 比较；负值字节长链 = Shift-JIS 双字节首字节区段（0x81..0x9F / 0xE0..0xEF /
// 0xFA..0xFC），扫描位落在首字节上时步进 2 跳过整个双字节字符，避免"半个汉字"假命中。
// ------------------------------------------------------------
const char */*cdecl*/ sub_4D34D0(const char *pArg1, const char *pArg2)  // this+24〔nPageMax(推断)〕等 2 字段
{
  const char *psz; // esi
  void *pMem; // edi
  char *pScan; // ebx
  char cLead; // al
  unsigned int nNextPos; // eax
  unsigned int nScanPos; // [esp+Ch] [ebp-4h]

  psz = pArg2;
  if ( strlen(pArg1) < strlen(pArg2) )  // 调 求串长
    return nullptr;
  nScanPos = 0;
  if ( strlen(pArg1) - strlen(pArg2) == -1 )  // 调 求串长
    return nullptr;
  while ( 1 )  // 无限循环
  {
    pMem = malloc(strlen(psz) + 1);  // pMem = 调 malloc
    pScan = (char *)&pArg1[nScanPos];
    sub_4D3470(pMem, (void *)&pArg1[nScanPos], strlen(psz));  // 调 求串长
    if ( strcmp((const char *)pMem, pArg2) == 0 )  // 调 串比较
      break;
    free(pMem);  // 调 堆释放
    cLead = *pScan;
    if ( *pScan < 0
      && (cLead == -127
       || cLead == -126
       || cLead == -125
       || cLead == -124
       || cLead == -121
       || cLead == -120
       || cLead == -119
       || cLead == -118
       || cLead == -117
       || cLead == -116
       || cLead == -115
       || cLead == -114
       || cLead == -113
       || cLead == -112
       || cLead == -111
       || cLead == -110
       || cLead == -109
       || cLead == -108
       || cLead == -107
       || cLead == -106
       || cLead == -105
       || cLead == -104
       || cLead == -103
       || cLead == -102
       || cLead == -101
       || cLead == -100
       || cLead == -99
       || cLead == -98
       || cLead == -97
       || cLead == -32
       || cLead == -31
       || cLead == -30
       || cLead == -29
       || cLead == -28
       || cLead == -27
       || cLead == -26
       || cLead == -25
       || cLead == -24
       || cLead == -23
       || cLead == -22
       || cLead == -19
       || cLead == -18
       || cLead == -6
       || cLead == -5
       || cLead == -4) )
    {
      nNextPos = nScanPos + 2;
    }
    else
    {
      nNextPos = nScanPos + 1;
    }
    nScanPos = nNextPos;
    if ( nNextPos >= strlen(pArg1) - strlen(pArg2) + 1 )  // 调 求串长
      return nullptr;
    psz = pArg2;
  }
  free(pMem);  // 调 堆释放
  return &pArg1[nScanPos];
}



// ------------------------------------------------------------
// 0x4D3710 sub_4D3710
// 键值配置表头复位（0x4D3720 加载的表对象）：仅清零 条目数(+32)/key 表指针(+24)/
// value 表指针(+28) 三个字段，不释放堆块（释放走 0x4D3950）。返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D3710(uint32_t *this)  // 实现：value 表指针(+28) 三个字段，不释放堆块（释放走 0x4D3950）。返回 0
{
  *(this + 8) = 0;  // this+32〔nHeight(推断)〕
  *(this + 6) = 0;  // this+24〔nPageMax(推断)〕
  *(this + 7) = 0;  // this+28〔pPanelVec(推断)〕
  return 0;
}



// ------------------------------------------------------------
// 0x4D3720 sub_4D3720
// 键值配置表加载器：读文本文件（"key:value" 每行一条），两遍扫描——第一遍经
// sub_4D3400 去空白后统计有效行（跳过 '#' 注释行与空行），第二遍按首个 ':' 拆分，
// 存入两个 0x20(32) 字节定长串数组：+24=key 表、+28=value 表、+32=条目数；
// 无 ':' 的行 = key=整行、value=空串。成功返回 1，文件打不开返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D3720(uint32_t *this, char *FileName)  // 实现：无 : 的行 = key=整行、value=空串。成功返回 1，文件打不开返回 0
{
  FILE *pFile; // eax
  FILE *pFile2; // ebx
  int nSlot; // esi
  int nBytePos; // esi
  char *pColon; // eax
  char Buffer[1024]; // [esp+Ch] [ebp-404h] BYREF
  int dword_796E502; // [esp+40Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  pFile = fopen(FileName, "r");  // pFile = 调 fopen
  pFile2 = pFile;
  nSlot = 0;
  if ( pFile == nullptr )  // 若 pFile 为空
    return 0;
  *(this + 8) = 0;  // this+32〔nHeight(推断)〕
  if ( fgets(Buffer, 1023, pFile) != nullptr )  // 调 读一行
  {
    do
    {
      sub_4D3400(Buffer, Buffer);  // 调 未定义寄存器残留（原意应为写 \0 终结符），忠实保留
      if ( Buffer[0] != 35 && strlen(Buffer) != 0 )  // 调 求串长
        ++*(this + 8);  // this+32〔nHeight(推断)〕
    }
    while ( fgets(Buffer, 1023, pFile2) != nullptr );  // 调 读一行
  }
  *(this + 6) = operator new(4 * *(this + 8));  // this+24〔nPageMax(推断)〕等 2 字段
  *(this + 7) = operator new(4 * *(this + 8));  // this+28〔pPanelVec(推断)〕等 2 字段
  if ( (int)*(this + 8) > 0 )  // this+32〔nHeight(推断)〕
  {
    do
    {
      *(uint32_t *)(*(this + 6) + 4 * nSlot) = operator new(0x20u);  // 堆分配 32 字节对象
      *(uint32_t *)(*(this + 7) + 4 * nSlot++) = operator new(0x20u);  // 堆分配 32 字节对象
    }
    while ( nSlot < *(this + 8) );  // this+32〔nHeight(推断)〕
  }
  fseek(pFile2, 0, 0);  // 调 文件定位
  if ( fgets(Buffer, 1023, pFile2) != nullptr )  // 调 读一行
  {
    nBytePos = 0;
    do
    {
      sub_4D3400(Buffer, Buffer);  // 调 未定义寄存器残留（原意应为写 \0 终结符），忠实保留
      if ( Buffer[0] != 35 && strlen(Buffer) != 0 )  // 调 求串长
      {
        if ( strstr(Buffer, ":") != nullptr )  // 调 查子串
        {
          pColon = strstr(Buffer, ":");  // pColon = 调 strstr
          sub_4D3470(*(void **)(*(this + 6) + nBytePos), Buffer, pColon - Buffer);  // this+24〔nPageMax(推断)〕
          strcpy(*(char **)(nBytePos + *(this + 7)), strstr(Buffer, ":") + 1);  // this+28〔pPanelVec(推断)〕
        }
        else
        {
          strcpy(*(char **)(nBytePos + *(this + 6)), Buffer);  // this+24〔nPageMax(推断)〕
          **(uint8_t **)(nBytePos + *(this + 7)) = 0;  // this+28〔pPanelVec(推断)〕
        }
        nBytePos += 4;
      }
    }
    while ( fgets(Buffer, 1023, pFile2) != nullptr );  // 调 读一行
  }
  fclose(pFile2);  // 调 关闭文件
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4D3950 sub_4D3950
// 键值配置表卸载（0x4D3720 加载的表对象）：+4 处加载标志为 0 直接返回 0；否则
// 逐条 free 两个 0x20 定长串（key 表 +24 / value 表 +28），再 free 数组本体并清零
// 表头，返回 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D3950(int this)  // 实现：表头，返回 1
{
  int nEntryCount; // eax  | +0x0020 → 条目数（0x4D3950: *(this+32) 循环上界；0x4D39F0 SJIS 匹配）（CNSlangTextFilter；va=004D3950）
  int nSlot; // edi
  int pValueTable; // edx  | +0x001C → value 表指针数组（0x4D3950: *(this+28) 同组 free）（CNSlangTextFilter；va=004D3950）
  void *pValueTable_; // eax

  if ( *(uint8_t *)(this + 4) == 0 )  // 判定 “+4 宿主对象指针”
    return 0;
  nEntryCount = *(uint32_t *)(this + 32);  // this+32〔nHeight(推断)〕等 2 字段
  nSlot = 0;
  *(uint8_t *)(this + 4) = 0;  // 写 this+4 = 0（宿主对象指针）
  if ( nEntryCount > 0 )  // fld_20=this+32 nHeight
  {
    do
    {
      if ( *(uint32_t *)(*(uint32_t *)(this + 24) + 4 * nSlot) != 0 )  // this+24〔nPageMax(推断)〕等 2 字段
        j__free(*(void **)(*(uint32_t *)(this + 24) + 4 * nSlot));  // this+24〔nPageMax(推断)〕等 2 字段
      *(uint32_t *)(*(uint32_t *)(this + 24) + 4 * nSlot) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
      pValueTable = *(uint32_t *)(this + 28);  // this+28〔pPanelVec(推断)〕等 2 字段
      if ( *(uint32_t *)(pValueTable + 4 * nSlot) != 0 )  // fld_1C=this+28 pPanelVec
        j__free(*(void **)(pValueTable + 4 * nSlot));  // 调 堆释放
      *(uint32_t *)(*(uint32_t *)(this + 28) + 4 * nSlot++) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
    }
    while ( nSlot < *(uint32_t *)(this + 32) );  // this+32〔nHeight(推断)〕等 2 字段
  }
  if ( *(uint32_t *)(this + 24) != 0 )  // this+24〔nPageMax(推断)〕等 2 字段
    j_j__free(*(void **)(this + 24));  // this+96〔nStatusMode(推断)〕
  pValueTable_ = *(void **)(this + 28);  // this+112〔pHostComp112〕
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  if ( pValueTable_ != nullptr )  // 若 fld_1C2 有效（非空）
    j_j__free(pValueTable_);  // fld_1C2=this+112 pHostComp112
  *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4D39F0 sub_4D39F0
// 命令文本关键字匹配：在 pArg3（原文）里找配置表 key 的首次出现（先把 pArg3 去空白
// 存 pMem，再用 SJIS 感知搜索 0x4D34D0 对 key 表逐条比对），命中返回原文中 key 的
// 起始指针，未命中返回 nullptr；uArg2 非空时回填 key 跨度长（含 key 前后的空白）。
// 因为 pMem 是去空白版，这里用两段小循环把"去空白坐标"折算回原文坐标：
//   第一段数出匹配点之前的空白数 nWsBefore，第二段从匹配点数到 key 的第 strlen(key)
//   个非空白字符为止的空白数 nWsInside。
// ------------------------------------------------------------
const char */*thiscall*/ sub_4D39F0(int this, uint32_t *uArg2, const char *pArg3)  // 命令文本关键字匹配：在 pArg3（原文）里找配置表 key 的首次出现，命中返回原文中
{
  uint8_t *pMem; // esi
  int nEntry; // ebx
  const char *pMatchPos; // eax
  int nScan; // ecx
  int nMatchOff; // edx
  int i; // esi
  char cCur; // al
  const char *pKeyStr; // edi
  const char *pWalk; // esi
  char cCur2; // al
  int nMatchOff2; // [esp+8h] [ebp-18h]
  void *Block; // [esp+10h] [ebp-10h]
  int nWsBefore; // [esp+14h] [ebp-Ch]
  int nWsInside; // [esp+18h] [ebp-8h]
  unsigned int nNonWs; // [esp+1Ch] [ebp-4h]

  if ( *(uint8_t *)(this + 4) == 0 )  // 判定 “+4 宿主对象指针”
    return nullptr;
  pMem = malloc(strlen(pArg3) + 1);  // pMem = 调 malloc
  Block = pMem;
  sub_4D3400(pMem, pArg3);  // 调 未定义寄存器残留（原意应为写 \0 终结符），忠实保留
  nEntry = 0;
  if ( *(int *)(this + 32) <= 0 )  // this+32〔nHeight(推断)〕等 2 字段
  {
LABEL_6:
    free(pMem);  // 调 堆释放
    return nullptr;
  }
  else
  {
    while ( sub_4D34D0(pMem, *(const char **)(*(uint32_t *)(this + 24) + 4 * nEntry)) == nullptr )  // this+24〔nPageMax(推断)〕等 2 字段
    {
      if ( ++nEntry >= *(uint32_t *)(this + 32) )  // this+32〔nHeight(推断)〕等 2 字段
        goto LABEL_6;
    }
    pMatchPos = sub_4D34D0(pMem, *(const char **)(*(uint32_t *)(this + 24) + 4 * nEntry));  // this+24〔nPageMax(推断)〕等 2 字段
    nScan = 0;
    nMatchOff = pMatchPos - pMem;
    nMatchOff2 = pMatchPos - pMem;
    nWsBefore = 0;
    nWsInside = 0;
    for ( i = 0; ; ++i )
    {
      while ( 1 )  // 无限循环
      {
        cCur = pArg3[i];
        if ( cCur != 32 && cCur != 9 && cCur != 10 )  // 若 cCur != 32 与/或 cCur != 9 与/或 cCur != 10
          break;
        ++nWsBefore;
        ++i;
      }
      if ( nScan >= nMatchOff )
        break;
      ++nScan;
    }
    pKeyStr = *(const char **)(*(uint32_t *)(this + 24) + 4 * nEntry);  // this+24〔nPageMax(推断)〕等 2 字段
    nNonWs = 0;
    if ( strlen(pKeyStr) != 0 )  // 调 求串长
    {
      pWalk = &pArg3[i];
      do
      {
        cCur2 = *pWalk;
        if ( *pWalk == 32 || cCur2 == 9 || cCur2 == 10 )  // 若 cCur2 == 9 与/或 cCur2 == 10
          ++nWsInside;
        else
          ++nNonWs;
        ++pWalk;
      }
      while ( nNonWs < strlen(pKeyStr) );  // 调 求串长
    }
    free(Block);  // 调 堆释放
    if ( uArg2 != nullptr )  // 若 uArg2 有效（非空）
      *uArg2 = nWsInside + strlen(*(const char **)(*(uint32_t *)(this + 24) + 4 * nEntry));  // this+24〔nPageMax(推断)〕等 2 字段
    return &pArg3[nWsBefore + nMatchOff2];
  }
}



// ------------------------------------------------------------
// 0x4D3B50 sub_4D3B50
// 键值配置表精确查找（0x4D3720 表 + 0x4D39F0 前缀匹配的对偶）：把 pArg3 去空白后
// 与 key 表逐条 strcmp 全等比较，命中则把对应 value 以 uArg4 上限定界拷入 uArg2；
// 未命中（或表未加载/为空）写 *uArg2 = 0。无返回值。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D3B50(int this, uint8_t *uArg2, const char *pArg3, unsigned int uArg4)  // 实现：未命中（或表未加载/为空）写 *uArg2 = 0。无返回值
{
  uint8_t *pMem; // edi
  int nEntry; // edx
  const char **pKeyCur; // ebx
  int nEntryCount; // [esp+8h] [ebp-4h]  | +0x0020 → 条目数（0x4D3950: *(this+32) 循环上界；0x4D39F0 SJIS 匹配）（CNSlangTextFilter；va=004D3950）
  const char **pKeyNext; // [esp+18h] [ebp+Ch]

  if ( *(uint8_t *)(this + 4) != 0 )  // 判定 “+4 宿主对象指针”
  {
    pMem = malloc(strlen(pArg3) + 1);  // pMem = 调 malloc
    sub_4D3400(pMem, pArg3);  // 调 未定义寄存器残留（原意应为写 \0 终结符），忠实保留
    nEntry = 0;
    nEntryCount = *(uint32_t *)(this + 32);  // this+32〔nHeight(推断)〕等 2 字段
    if ( nEntryCount <= 0 )  // fld_20=this+32 nHeight
    {
LABEL_6:
      *uArg2 = 0;
      free(pMem);  // 调 堆释放
    }
    else
    {
      pKeyCur = *(const char ***)(this + 24);  // this+96〔nStatusMode(推断)〕
      pKeyNext = pKeyCur;  // pKeyCur=this+96 nStatusMode
      while ( strcmp(pMem, *pKeyCur) != 0 )  // 当 strcmp(pMem, *pKeyCur) != 0 循环
      {
        ++nEntry;
        pKeyCur = ++pKeyNext;  // pKeyCur=this+96 nStatusMode
        if ( nEntry >= nEntryCount )  // fld_20=this+32 nHeight
          goto LABEL_6;
      }
      sub_4D3470(uArg2, *(void **)(*(uint32_t *)(this + 28) + 4 * nEntry), uArg4);  // this+28〔pPanelVec(推断)〕等 2 字段
      free(pMem);  // 调 堆释放
    }
  }
}



// ------------------------------------------------------------
// 0x4D3C30 sub_4D3C30
// 富文本转义序列扫描器（DNF 描述文本用 HTML 式标记）：在 Str 里找第一个
// "&#NN;" 数字字符引用（38='&' 35='#' 起头、59=';' 收尾，*uArg2 = 序列字节长）、
// "<br>"（长 4）、CR(13)（长 1）或 &nbsp;/&nbsp/&quot;/&amp;/&lt;/&gt; 各固定长；
// 命中返回序列起始指针，*uArg2 回填长度，全无则返回 nullptr。
// ------------------------------------------------------------
char */*thiscall*/ sub_4D3C30(uint8_t *this, uint32_t *uArg2, char *Str)  // 实现：命中返回序列起始指针，*uArg2 回填长度，全无则返回 nullptr
{
  char *result; // eax
  char cCur; // dl
  int i; // ecx
  int nPos; // edx

  if ( *(this + 4) == 0 )  // 判定 “+4 宿主对象指针”
    return nullptr;
  if ( strstr(Str, "&#") != nullptr )  // 调 查子串
  {
    result = strstr(Str, "&#");  // result = 调 strstr
    cCur = result[2];
    for ( i = (int)(result + 2); cCur != 0; cCur = *(uint8_t *)++i )
    {
      if ( cCur == 38 )
      {
        if ( *(uint8_t *)(i + 1) == 35 )
          result = (char *)i;
      }
      else if ( cCur == 59 )
      {
        if ( uArg2 != nullptr )  // 若 uArg2 有效（非空）
          *uArg2 = i - (uint32_t)result + 1;
        return result;
      }
    }
  }
  if ( strstr(Str, "<br>") != nullptr )  // 字符串 “<br>”
  {
    if ( uArg2 != nullptr )  // 若 uArg2 有效（非空）
      *uArg2 = 4;
    return strstr(Str, "<br>");  // 字符串 “<br>”
  }
  else
  {
    nPos = 0;
    if ( (int)strlen(Str) <= 0 )  // 调 求串长
    {
LABEL_19:
      if ( strstr(Str, "&nbsp;") != nullptr )  // 字符串 “&nbsp;”
      {
        if ( uArg2 != nullptr )  // 若 uArg2 有效（非空）
          *uArg2 = 6;
        return strstr(Str, "&nbsp;");  // 字符串 “&nbsp;”
      }
      else if ( strstr(Str, "&nbsp") != nullptr )  // 字符串 “&nbsp”
      {
        if ( uArg2 != nullptr )  // 若 uArg2 有效（非空）
          *uArg2 = 5;
        return strstr(Str, "&nbsp");  // 字符串 “&nbsp”
      }
      else if ( strstr(Str, "&quot;") != nullptr )  // 字符串 “&quot;”
      {
        if ( uArg2 != nullptr )  // 若 uArg2 有效（非空）
          *uArg2 = 6;
        return strstr(Str, "&quot;");  // 字符串 “&quot;”
      }
      else if ( strstr(Str, "&amp;") != nullptr )  // 字符串 “&amp;”
      {
        if ( uArg2 != nullptr )  // 若 uArg2 有效（非空）
          *uArg2 = 5;
        return strstr(Str, "&amp;");  // 字符串 “&amp;”
      }
      else if ( strstr(Str, "&lt;") != nullptr )  // 字符串 “&lt;”
      {
        if ( uArg2 != nullptr )  // 若 uArg2 有效（非空）
          *uArg2 = 4;
        return strstr(Str, "&lt;");  // 字符串 “&lt;”
      }
      else if ( strstr(Str, "&gt;") != nullptr )  // 字符串 “&gt;”
      {
        if ( uArg2 != nullptr )  // 若 uArg2 有效（非空）
          *uArg2 = 4;
        return strstr(Str, "&gt;");  // 字符串 “&gt;”
      }
      else
      {
        return nullptr;
      }
    }
    else
    {
      while ( Str[nPos] != 13 )  // 当 Str[nPos] != 13 循环
      {
        if ( ++nPos >= (int)strlen(Str) )  // 调 求串长
          goto LABEL_19;
      }
      if ( uArg2 != nullptr )  // 若 uArg2 有效（非空）
        *uArg2 = 1;
      return &Str[nPos];
    }
  }
}



// ------------------------------------------------------------
// 0x4D3E60 sub_4D3E60
// 转义序列展开器（0x4D3C30 扫描结果的落地端，单条转换）： "&#NN;" 取十进制 N 作
// Unicode 码点经 WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK) 转成 ANSI/Shift-JIS
// 本地字符；"<br>"→换行、CR→空串、&nbsp(;)→空格、&quot;→双引号、&amp;→&、
// &lt;→'<'、&gt;→'>'；其余写 *uArg2 = 0。结果以 uArg4 上限定界拷入 uArg2。
// ------------------------------------------------------------
uint8_t /*thiscall*/ sub_4D3E60(uint8_t *this, uint8_t *uArg2, char *Str, unsigned int uArg4)  // 实现：&lt;→<、&gt;→>；其余写 *uArg2 = 0。结果以 uArg4 上限定界拷入 uArg2
{
  uint8_t result; // al
  char *pFound; // eax
  WCHAR WideCharStr[256]; // [esp+0h] [ebp-404h] BYREF
  char String[256]; // [esp+200h] [ebp-204h] BYREF
  CHAR MultiByteStr[256]; // [esp+300h] [ebp-104h] BYREF
  int dword_796E502; // [esp+400h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = *(this + 4);  // 读 result = this+4（宿主对象指针）
  if ( result != 0 )  // 若结果非 0（成功）
  {
    if ( *Str == 38 && Str[1] == 35 )
    {
      pFound = strstr(Str, ";");  // pFound = 调 strstr
      sub_4D3470(String, Str + 2, (unsigned int)&pFound[-2 - (uint32_t)Str]);  // 调 源串末指针）
      WideCharStr[0] = j__atol(String);  // WideCharStr[0] = 调 j__atol
      WideCharToMultiByte(0, 0x200u, WideCharStr, 1, MultiByteStr, 256, nullptr, nullptr);  // 调 宽字符转多字节
      MultiByteStr[2] = 0;
      return (uint8_t)sub_4D3470(uArg2, MultiByteStr, uArg4);  // 返回 源串末指针）
    }
    else if ( strcmp(Str, "<br>") == 0 )  // 字符串 “<br>”
    {
      return (uint8_t)sub_4D3470(uArg2, (void *)"\n", uArg4);  // 字符串 “\n”
    }
    else if ( *Str == 13 )
    {
      return (uint8_t)sub_4D3470(uArg2, (void *)szPassword, uArg4);  // 返回 源串末指针）
    }
    else
    {
      if ( strcmp(Str, "&nbsp;") == 0 )  // 字符串 “&nbsp;”
        return (uint8_t)sub_4D3470(uArg2, (void *)" ", uArg4);  // 返回 源串末指针）
      result = 0;  // result=this+16 频道型选中索引
      if ( strcmp(Str, "&nbsp") == 0 )  // 字符串 “&nbsp”
      {
        return (uint8_t)sub_4D3470(uArg2, (void *)" ", uArg4);  // 返回 源串末指针）
      }
      else if ( strcmp(Str, "&quot;") == 0 )  // 字符串 “&quot;”
      {
        return (uint8_t)sub_4D3470(uArg2, &unk_6F8688, uArg4);  // 返回 源串末指针）
      }
      else if ( strcmp(Str, "&amp;") == 0 )  // 字符串 “&amp;”
      {
        return (uint8_t)sub_4D3470(uArg2, &word_6F8684, uArg4);  // 返回 源串末指针）
      }
      else if ( strcmp(Str, "&lt;") == 0 )  // 字符串 “&lt;”
      {
        return (uint8_t)sub_4D3470(uArg2, (void *)"<", uArg4);  // 返回 源串末指针）
      }
      else if ( strcmp(Str, "&gt;") == 0 )  // 字符串 “&gt;”
      {
        return (uint8_t)sub_4D3470(uArg2, (void *)">", uArg4);  // 返回 源串末指针）
      }
      else
      {
        *uArg2 = 0;
      }
    }
  }
  return result;  // result=this+16 频道型选中索引
}



// ------------------------------------------------------------
// 0x4D4040 sub_4D4040
// 键值配置表构建（内存源版本，表布局同 0x4D3720：+24=key 表、+28=value 表、
// +32=条目数）：pArg2 指向扁平化的字符串指针数组（begin=+4/end=+8，相邻两项为一对
// key/value，故条目数 = 元素数 >> 1），逐对经 sub_41ACF0（string::c_str 族）取串后
// strcpy 进两块 0x20 字节定长串槽。成功返回 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D4040(uint32_t *this, int pArg2)  // 实现：strcpy 进两块 0x20 字节定长串槽。成功返回 1
{
  int nBegin; // ecx
  unsigned int nCount; // eax
  unsigned int nPairs; // eax
  void *pMem; // eax
  int i; // edi
  int nSlot; // edi
  int nBytePos; // ebx
  size_t fld_e8; // [esp-8h] [ebp-10h]

  nBegin = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( nBegin != 0 )
    nCount = (*(uint32_t *)(pArg2 + 8) - nBegin) >> 2;  // pArg2+8〔nSkillRec8(推断)〕
  else
    nCount = 0;
  nPairs = nCount >> 1;
  *(this + 8) = nPairs;  // this+32〔nHeight(推断)〕
  pMem = operator new(4 * nPairs);
  fld_e8 = 4 * *(this + 8);  // 字段 this+8〔状态模式号〕
  *(this + 6) = pMem;  // this+24〔nPageMax(推断)〕
  *(this + 7) = operator new(fld_e8);  // this+28〔pPanelVec(推断)〕
  for ( i = 0; i < *(this + 8); ++i )  // this+32〔nHeight(推断)〕
  {
    *(uint32_t *)(*(this + 6) + 4 * i) = operator new(0x20u);  // 堆分配 32 字节对象
    *(uint32_t *)(*(this + 7) + 4 * i) = operator new(0x20u);  // 堆分配 32 字节对象
  }
  nSlot = 0;
  if ( (int)*(this + 8) > 0 )  // this+32〔nHeight(推断)〕
  {
    nBytePos = 0;
    do
    {
      strcpy(*(char **)(*(this + 6) + 4 * nSlot), sub_41ACF0((unsigned int **)(nBytePos + *(uint32_t *)(pArg2 + 4))));  // 驻留串句柄 → 字符串指针
      strcpy(*(char **)(*(this + 7) + 4 * nSlot++), sub_41ACF0((unsigned int **)(nBytePos + *(uint32_t *)(pArg2 + 4) + 4)));  // 驻留串句柄 → 字符串指针
      nBytePos += 8;
    }
    while ( nSlot < *(this + 8) );  // this+32〔nHeight(推断)〕
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4D4120 sub_4D4120
// 弹窗行列表绘制（pArg2 = 窗口对象，与 this+8 记录的"当前窗口"一致时才画）：
// 先画底板（资源 0xD7），再循环 3 行画列表项——数据取 this+116..120 的 vector
// （元素 52 字节：内嵌子对象指针 +0x04、一个 std::string +0x00、色值/参数 +0x24），
// 每行画槽底（资源 0x5A）→ 子对象 → 渲染器 dword_79C0B0 文本；行高 39px，
// sub_418DD0 = 资源管理器按 id 取绘制对象，0x5A 处 vt+128 传 1.0f/1.0f 浮点（
// 1065353216 = float 1.0 的位模式）与两色值。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4D4120(int this, int pArg2)  // 实现：1065353216 = float 1.0 的位模式）与两色值
{
  unsigned int result; // eax
  int nX; // ebx
  int nY; // edi
  int fld_38; // eax
  int nRow; // ebx
  int pListCtrl; // edi  | +0x0034 → 列表控件（0x4D4120: sub_69C690(*(this+52)) 取滚动偏移）（CNRDSeriasPresentListWindow；va=004D4120）
  unsigned int nRowAbs; // edi
  int fld_382; // eax
  int nByteOff; // edi
  int pEntryVecBegin; // ecx  | +0x0074 → 条目向量 begin（0x4D4120: *(this+116)；元素 52 字节，行高 39px）（CNRDSeriasPresentListWindow；va=004D4120）
  uint32_t *fld_742; // eax
  uint32_t *pStrData; // edx
  int nRowPersist; // [esp+8h] [ebp-8h]
  int nXSave; // [esp+Ch] [ebp-4h]
  int nRowY; // [esp+18h] [ebp+8h]

  result = sub_554930(pArg2);  // 【IRDPopupWindow__vmt0】
  if ( pArg2 == *(uint32_t *)(this + 8) )  // 判定 “+8 技能槽记录首字”
  {
    nX = *(uint32_t *)(pArg2 + 20);  // pArg2+20〔nPage(推断)〕
    nY = *(uint32_t *)(pArg2 + 24);  // pArg2+24〔nPageMax(推断)〕
    nXSave = nX;
    fld_38 = sub_418DD0(*(uint32_t **)(this + 56), 0xD7u);  // 调 资源句柄 (101)
    if ( fld_38 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_38 + 152))(fld_38, nX + 9, nY + 7, dword_79C0B0);  // 调虚槽 +152：效果通道 3
    nRow = 0;
    nRowPersist = 0;
    nRowY = nY + 48;
    do
    {
      pListCtrl = sub_69C690(*(uint32_t *)(this + 52));  // 结果 = 取设备对象 +112 字段（类型或句柄）
      result = *(uint32_t *)(this + 116);  // 读 result = this+116（观察者容器）
      nRowAbs = nRow + pListCtrl;
      if ( result != 0 )  // 若结果非 0（成功）
      {
        result = (int)(*(uint32_t *)(this + 120) - result) / 52;  // 涉及字段 “+120 动画对象”
        if ( result > nRowAbs )  // result=this+116 pEntryVecBegin
        {
          fld_382 = sub_418DD0(*(uint32_t **)(this + 56), 0x5Au);  // 调 资源句柄 (101)
          if ( fld_382 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_382 + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
              fld_382,
              nXSave + 11,
              nRowY - 10,
              dword_79C0B0,  // 默认字体/绘制资源
              1065353216,
              1065353216,
              0,
              872415231,
              1333788672,
              1333788672);
          nByteOff = 52 * nRowAbs;
          pEntryVecBegin = *(uint32_t *)(*(uint32_t *)(this + 116) + nByteOff + 4);  // 涉及字段 “+116 观察者容器”
          if ( pEntryVecBegin != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pEntryVecBegin + 152))(pEntryVecBegin, nXSave + 12, nRowY - 9, dword_79C0B0);  // 调虚槽 +152：效果通道 3
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 60);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
          fld_742 = (uint32_t *)(*(uint32_t *)(this + 116) + nByteOff);  // 涉及字段 “+116 观察者容器”
          if ( fld_742[8] < 0x10u )
            pStrData = fld_742 + 3;
          else
            pStrData = (uint32_t *)fld_742[3];
          (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
            dword_79C0B0,  // 默认字体/绘制资源
            nXSave + 6,
            nRowY,
            fld_742[9],
            pStrData);
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
          nRow = nRowPersist;
        }
      }
      nRowPersist = ++nRow;
      nRowY += 39;
    }
    while ( nRow < 3 );
  }
  return result;  // result=this+116 pEntryVecBegin
}



// ------------------------------------------------------------
// 0x4D42A0 sub_4D42A0
// UI 窗口装配：从 UI 管理器 dword_99FCC8 取窗口配置后，创建 1 个控件（sub_43C410，
// 定位 87,73）挂 this+9；循环创建 2 个 nengine::CNButton（this+10 起的槽）；再建
// CNSlider+CNVSlider 双虚表滑条挂 this+12；最后 sub_43C630 把三件套组合成复合控件
// 挂 this+13（定位 218,49）。尾部写窗口样式字段：+64/65/66/63 标志字节清零、
// +76=6、+80=12、+88=1600 后改 228、+72=1、this+64 = 0xFF000000（不透明黑 ARGB）、
// +108 = dword_99FCCC。注：原转写体的 v6/v13/v7/v8/v9 为 Hex-Rays 寄存器伪变量
//（声明不可见），现已按语义改名为 pBtn/pBtnSlot/pMem4/pSlider/pCfgF60。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D42A0(uint32_t *this)  // 实现：（声明不可见），现已按语义改名为 pBtn/pBtnSlot/pMem4/pSlider/pCfgF60
{
  int pVt; // edx
  uint32_t *pMem; // eax
  uint32_t *pCtrl; // eax
  int nY; // ebx
  uint8_t *pMem2; // edi
  uint8_t *pMem3; // eax
  uint32_t *pMem32; // edi
  int fld_e14; // ebx
  uint32_t *fld_e10; // eax
  int result; // eax
  void *Block; // [esp+Ch] [ebp-14h]
  uint32_t *pThis_A; // [esp+10h] [ebp-10h]

  pVt = *this;
  *(this + 14) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // this+56〔pCmdVecCap56(推断)〕
  (*(void (/*stdcall*/ **)(int, int))(pVt + 24))(18, 7);  // 调虚槽 +24：CNRDSkillInventoryWindow__vmt18 页签动作（41A5E0 + 44…
  pMem = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    pCtrl = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    pCtrl = nullptr;
  *(this + 9) = pCtrl;  // 写 this+36 = pCtrl（状态字）
  sub_69A5F0(pCtrl, 87, 73);  // 调 设位、sub_69A840 登记
  sub_69A840(*(this + 9));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  nY = 4;
  pThis_A = this + 10;
  do
  {
    pMem2 = operator new(0x84u);  // 堆分配 132 字节对象
    if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);  // nengine::CNSlider 全局实例
      sub_426BD0(pMem2);  // nengine::IControl 构造
      *(uint32_t *)pMem2 = &nengine::CNButton::`vftable';  // 写 vftable 指针（对象重定位/复位）
      sub_69C780(pBtn);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(Block, nY, nY, nY + 1, nY, 0, 0);  // 按钮 SetTextures：解析 常态(+104)/悬停(+112)/按下(+108)
    }
    else
    {
      pBtn = nullptr;
    }
    *pBtnSlot = pBtn;
    nY += 2;
    ++pBtnSlot;
  }
  while ( nY < 8 );
  pMem4 = operator new(0x88u);  // 堆分配 136 字节对象
  pSlider = pMem4;
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
  {
    pCfgF60 = *(this + 14);  // this+56〔pCmdVecCap56(推断)〕
    sub_426BD0(pMem4);  // nengine::IControl 构造
    *pSlider = &nengine::CNSlider::`vftable';  // 写 vftable 指针（对象重定位/复位）
    sub_69CA20(pMem32);  // 调 初始化 → ·vmt20(nArg2
    sub_69CA50(fld_e14, 87, 88);  // 滑条 SetTexture：a3!=-1 解析滑块纹理(+104)，a4!=-1 解析轨
    *pMem32 = &nengine::CNVSlider::`vftable';  // 写 vftable 指针（对象重定位/复位）
  }
  else
  {
    pMem32 = nullptr;
  }
  *(this + 12) = pMem32;  // this+48〔pCmdVecBegin48(推断)〕
  if ( operator new(0x74u) != nullptr )  // 堆分配 116 字节对象
    fld_e10 = (uint32_t *)sub_43C630(*(this + 10), *(this + 11), *(this + 12));  // 结果 = nengine::CNVScroll 构造
  else
    fld_e10 = nullptr;
  *(this + 13) = fld_e10;  // this+52〔bAuraState(推断)〕
  sub_69A5F0(fld_e10, 218, 49);  // 调 设位、sub_69A840 登记
  sub_69A840(*(this + 13));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  result = *(this + 13);  // this+52〔bAuraState(推断)〕
  *(uint8_t *)(result + 16) = 0;  // result=this+52 bAuraState
  *(this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
  *(this + 21) = 0;  // this+84〔pFxObjA(推断)〕
  *(this + 23) = 0;  // this+92〔pFxObjC(推断)〕
  *(this + 24) = 0;  // this+96〔nStatusMode(推断)〕
  *(this + 25) = 0;  // this+100〔bEnchantDone(推断)〕
  *(this + 26) = 0;  // this+104〔nTimerEnd(推断)〕
  *(this + 27) = 0;  // this+108〔nAdd108(推断)〕
  *((uint8_t *)this + 60) = 0;  // this+60〔nFadeValue60(推断)〕
  *((uint8_t *)this + 61) = 0;  // this+61〔bReadyFlagA〕
  *((uint8_t *)this + 62) = 0;  // this+62〔bReadyFlagB〕
  *((uint8_t *)this + 63) = 0;
  *(this + 19) = 6;  // this+76〔pBtnActionE〕
  *(this + 20) = 12;  // this+80〔nAuraStage(推断)〕
  *(this + 22) = 1600;  // this+88〔pFxObjB(推断)〕
  *(this + 27) = dword_99FCCC;  // this+108〔nAdd108(推断)〕
  *(this + 22) = 228;  // this+88〔pFxObjB(推断)〕
  *(this + 18) = 1;  // this+72〔nSnapshot72(推断)〕
  *(this + 16) = -16777216;  // this+64〔apServerTabBtn(推断)〕
  return result;  // result=this+52 bAuraState
}



// ------------------------------------------------------------
// 0x4D44E0 sub_4D44E0
// 弹窗打开/布局回调：把控件（this+2，字段 7/8 = 宽/高）居中到 640×480 屏幕中心，
// 刷新 this+28 起的子布局（sub_44CA70），再对 this+13 控件调 vt+32 传 0。返回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D44E0(uint32_t **this, int nArg2, int nArg3)  // 实现：刷新 this+28 起的子布局（sub_44CA70），再对 this+13 控件调 vt+32 传 0。返回 1
{
  sub_69A5F0(*(this + 2), (640 - (*(this + 2))[7]) / 2, (480 - (*(this + 2))[8]) / 2);  // 调 设位、sub_69A840 登记
  sub_44CA70(this + 28);  // 52 字节记录数组析构释放
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 13) + 32))(*(this + 13), 0);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90/4…
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4D4530 sub_4D4530
// 弹窗文本行装配：从行对象 pDwArg2 经虚表取数据（vt+16=数据对象、+24/+44=数量类
// 字段、+108=名称串），按数量分支——<=1 直接用名称，>1 用本地化模板 id 1116
//（sub_422E70 取格式串）sprintf 拼"名称×数量"样式；结果写入栈上字符串
//（nRowF68 / strRowText / nItemCountSaved 区）。随后按 this+116..120 列表
//（52 字节/行）行数，对 this+52 控件调 vt+32 设置滚动量（行数-3，夹 0）。
// tmpGuard = RAII 守卫对象（sub_459700 构造 / sub_477AF0 收尾）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D4530(int this, int *pDwArg2)  // 实现：tmpGuard = RAII 守卫对象（sub_459700 构造 / sub_477AF0 收尾）
{
  int pRowVt; // eax
  int pRowData; // eax
  int pRowVt2; // edx
  int nItemCount; // eax
  int pRowVt3; // edx
  int pIconRes; // eax
  const char *pFmt; // eax
  char *psz; // eax
  int nRowCount; // eax —— this+116..120 列表行数 = (end-begin)/52
  int nItemCountCopy; // [esp-4h] [ebp-D0h]
  char Buffer[128]; // [esp+8h] [ebp-C4h] BYREF
  uint8_t tmpGuard[4]; // [esp+88h] [ebp-44h] BYREF —— RAII 守卫（sub_459700 构造 / sub_45A340 刷新 / sub_477AF0 收尾）
  int nRowF68; // [esp+8Ch] [ebp-40h] —— 行数据 +68 / 图标资源 id 共用栈槽
  size_t strRowText[8]; // [esp+90h] [ebp-3Ch] BYREF —— 栈上 std::string（行文本）
  int nItemCountSaved; // [esp+B0h] [ebp-1Ch] —— 数量副本（sprintf 参数）
  int dword_796E502; // [esp+BCh] [ebp-10h]
  int nGuardState; // [esp+C8h] [ebp-4h] —— RAII 守卫状态变量（0 进行中 / -1 完成）

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  sub_459700(tmpGuard);  // 52 字节元素默认初始化
  pRowVt = *pDwArg2;
  nGuardState = 0;
  pRowData = (*(int (/*thiscall*/ **)(int *))(pRowVt + 16))(pDwArg2);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE…
  pRowVt2 = *pDwArg2;
  nRowF68 = *(uint32_t *)(pRowData + 68);
  strRowText[7] = (*(int (/*thiscall*/ **)(int *))(pRowVt2 + 24))(pDwArg2);  // 调虚槽 +24：CNRDSkillInventoryWindow__vmt18 页签动作（41A5E0 + 44…
  nItemCount = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 44))(pDwArg2);  // 结果 = 虚调用 vt+44
  pRowVt3 = *pDwArg2;
  nItemCountSaved = nItemCount;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(pRowVt3 + 16))(pDwArg2) + 4) != 0 )  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE…
  {
    psz = (char *)(*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 108))(pDwArg2);  // 结果 = 虚调用 vt+108
    if ( nItemCountSaved <= 1 )
    {
      sub_4015C0(strRowText, psz, strlen(psz));  // 【std::string构造赋值】
    }
    else
    {
      sprintf(Buffer, "%s", psz);  // 字符串 “%s”
      sub_4015C0(strRowText, Buffer, strlen(Buffer));  // 【std::string构造赋值】
    }
  }
  else
  {
    pIconRes = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 88), 0xAu);  // 调 资源句柄 (101)
    nItemCountCopy = nItemCountSaved;
    nRowF68 = pIconRes;
    pFmt = (const char *)sub_422E70(1116);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, pFmt, nItemCountCopy);  // 调 格式化到缓冲
    sub_4015C0(strRowText, Buffer, strlen(Buffer));  // 【std::string构造赋值】
  }
  sub_45A340(tmpGuard);  // 52 字节向量尾插
  nRowCount = *(uint32_t *)(this + 116);  // 读 nRowCount = this+116（观察者容器）
  if ( nRowCount != 0 )  // nRowCount=this+116 观察者 vector 尾针
    nRowCount = (*(uint32_t *)(this + 120) - nRowCount) / 52;  // 涉及字段 “+120 动画对象”
  (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 52) + 32))(  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90/4…
    *(uint32_t *)(this + 52),  // this+52 光环状态字节
    nRowCount - 3 <= 0 ? 0 : nRowCount - 3);  // nRowCount=this+116 观察者 vector 尾针
  nGuardState = -1;
  return sub_477AF0(tmpGuard);  // 调 后 j__free 基址并三指针清零
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
int /*thiscall*/ sub_4D46C0(uint32_t *this)  // 实现：ActiveObject 构造初始化（研究 20 §13 定案）
{
  int nGroup; // ecx
  uint32_t *pThis_676; // eax
  int result; // eax

  *(this + 24) = 17;  // this+96〔nStatusMode(推断)〕
  *(this + 1557) = 0;  // this+6228〔anState17〕
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
  *(this + 1617) = 0;  // this+6468〔apObserver18〕
  *(this + 1618) = 0;
  *(this + 1619) = 0;
  *(this + 1620) = 0;
  *(this + 1621) = 0;
  *(this + 1622) = 0;
  *(this + 1623) = 0;
  *(this + 1624) = 0;
  *(this + 1625) = 0;  // 写 this+6500 = 0（当前武器/弹药物件id）
  *(this + 1626) = 0;
  *(this + 1627) = 0;
  *(this + 1628) = 0;
  *(this + 1629) = 0;
  *(this + 1630) = 0;
  *(this + 1631) = 0;
  *(this + 1632) = 0;
  *(this + 1633) = 0;
  *(this + 1634) = 0;
  *((uint8_t *)this + 6552) = 0;  // this+6552〔bSuperArmor〕
  *(this + 1639) = 0;  // 写 this+6556 = 0（大状态ID）
  sub_699070(1);  // 【clock_bind_domain(clk, newDomainId)】
  *(this + 1647) = 0;  // this+6588〔nRencT0_6588〕
  *(this + 1649) = 0;  // this+6596〔uRenc6596〕
  *(this + 1648) = 0;  // this+6592〔uRenc6592〕
  *(this + 1650) = -1;
  *(this + 1651) = -1;
  nGroup = 0;
  pThis_676 = this + 1654;
  do
  {
    *(pThis_676 - 2) = 0;
    *pThis_676 = 0;
    pThis_676[2] = 0;
    *((uint8_t *)this + nGroup + 6634) = 0;
    pThis_676[5] = 4;
    ++nGroup;
    ++pThis_676;
  }
  while ( nGroup < 2 );
  *(this + 1661) = 0;  // this+6644〔nSubGate〕
  *(this + 1662) = 0;
  *(this + 1663) = 1000;  // this+6652〔nRateNum〕
  *(this + 1664) = 1000;  // this+6656〔nRateDen〕
  *(this + 1665) = 0;
  *(this + 1666) = 0;  // this+6664〔uUI6664〕
  *((uint8_t *)this + 6668) = 0;
  *(this + 1668) = 0;  // this+6672〔uUI6672〕
  *(this + 1669) = 0;
  *((uint8_t *)this + 6680) = 0;  // this+6680〔bUI6680〕
  *((uint8_t *)this + 6681) = 0;
  *((uint8_t *)this + 6682) = 0;  // this+6682〔bUI6682〕
  *(this + 1671) = 0;  // this+6684〔uUI6684〕
  *(this + 1672) = -1;  // this+6688〔uUI6688〕
  *(this + 1673) = -1;  // this+6692〔uUI6692〕
  *(this + 1674) = -1;
  *(this + 1675) = 4;
  *(this + 1676) = 4;
  *(this + 1677) = 0;
  *((uint8_t *)this + 6740) = 1;  // this+6740〔bFreeze6740〕
  *(this + 1686) = -1;  // this+6744〔nFrozenFlag〕
  *(this + 1687) = 0;
  *((uint8_t *)this + 6752) = 1;  // this+6752〔nReviveTimer〕
  *(this + 1689) = 0;
  *(this + 1690) = 0;
  *(this + 1698) = 0;  // this+6792〔nVoiceParam0(推断)〕
  *(this + 1699) = 0;  // this+6796〔nVoiceParam1(推断)〕
  *(this + 1700) = 0;  // this+6800〔nVoiceParam2(推断)〕
  *(this + 1701) = 0;  // this+6804〔nVoiceParam3(推断)〕
  *(this + 1702) = 0;  // this+6808〔nVoiceParam4(推断)〕
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
  *(this + 1723) = 0;  // this+6892〔nSkillCtxVal〕
  *(this + 1724) = 0;  // 写 this+6896 = 0（tick计数器）
  *(this + 1725) = 0;
  *((uint8_t *)this + 6988) = 0;
  *(this + 1748) = 20;
  *((uint8_t *)this + 6996) = 0;
  sub_41A590(0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 932))(this);  // 结果 = 虚调用 vt+932
  *((uint8_t *)this + 7092) = 0;  // 写 字段 this+7092〔标志（濒死/大伤害标记）〕
  *((uint8_t *)this + 7093) = 0;  // 写 字段 this+7093〔大伤害标志〕
  *(this + 1774) = -1;  // 写 this+7096 = -1（影身/伪装窗口起始时刻）
  *(this + 1775) = -1;  // 写 this+7100 = -1（影身/伪装窗口时长 ms）
  *((uint8_t *)this + 7105) = 0;  // this+7105〔bSet7105〕
  *(this + 1777) = -1;  // this+7108〔uSet7108〕
  *(this + 1778) = -1;  // this+7112〔uSet7112〕
  *((uint8_t *)this + 7104) = 1;  // 写 this+7104 = 1（影身/伪装开关字节）
  *((uint8_t *)this + 7129) = 0;
  *((uint8_t *)this + 7130) = 0;
  *((uint8_t *)this + 7144) = 1;  // this+7144〔bPhase7144(推断)〕
  return result;
}


// 0x4D49A0 sub_4D49A0 —— 场景判定 → +7088 = 0 / 7
// 已精修版见 src/cnrd/IRDActiveObject.cpp:134（0x4D49A0 vmt3A4）。
// 取全局对象 vmt120 的容器 +108 表首元素；15/16 号场景（PVP/战场？【待验证】）→ 7。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D49A0(uint32_t *this)  // 实现：场景 15/16 判定 → +7088 = 0 / 7
{
  int result; // eax

  result = **(uint32_t **)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108);  // 调虚槽 +120：动画对象
  if ( result < 15 || result > 16 )  // 若 result < 15 与/或 result > 16
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
int /*thiscall*/ sub_4D49E0(void *this, int nArg2, int nArg3)  // 实现：播报层 HK_ATTACKED（受击包链路终点，42 轮研究 §1.1 定案）
{
  int pMsgMgr; // edi —— dword_8F8520 vt+120() 返回对象 + 104（播报层数据块）
  int result; // eax

  pMsgMgr = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);  // 调虚槽 +120：动画对象
  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 44))(this);  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420…
  if ( result == 273 )
    return sub_426820(*(uint32_t *)(pMsgMgr + 132), 3, nArg3);  // 【总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTA…】
  return result;
}



// ------------------------------------------------------------
// 0x4D4A20 sub_4D4A20 —— 攻方观察者通知 vt+504（六回调第 5 号，研究 §1.1）
// 已精修版见 src/cnrd/IRDActiveObject.cpp:28（0x4D4A20 vmt1F8）。
// 18 观察者逐个 vt+136(观察者, 攻, 受, 盒, flag=0, this+388) —— 轻量版
// （flag=0，对应 sub_4D6D90 = vt+500 的 flag=1 完整版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D4A20(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：18 观察者通知（flag=0 轻量版；受击包五号回调）
{
  uint32_t *pThis_651; // esi
  int i; // [esp+Ch] [ebp-4h]

  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )  // 循环：i 从 18 递减到 0
  {
    if ( *pThis_651 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t, uint32_t *))(*(uint32_t *)*pThis_651 + 136))(  // 虚调用 vt+136
        *pThis_651,
        nArg2,
        nArg3,
        nArg4,
        0,
        this + 97);  // this+97〔bFlag97〕
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
int /*thiscall*/ sub_4D4A80(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：受击后观察者 vt+516（六回调第 6 号，研究 §1.1/§1.2）
{
  uint32_t *pThis_651; // esi
  int i; // [esp+10h] [ebp-4h]

  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )  // 循环：i 从 18 递减到 0
  {
    if ( *pThis_651 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t))(*(uint32_t *)*pThis_651 + 140))(*pThis_651, nArg2, nArg3, nArg4, 0);  // 虚调用 vt+140
    ++pThis_651;
  }
  return sub_4E48D0(nArg2, nArg3, nArg4);  // 记录最后受击时刻 + 仇人 id（研究 §1.1/§2 字段表定案）
}



// ------------------------------------------------------------
// 0x4D4AE0 sub_4D4AE0
// 状态槽搬运/重施加：nArg2 = 源 ActiveObject。① 对状态 1 与 8 分别查激活
//（vt+776，即 0x4D5140）并在附加条件成立时经 vt+764 移除；② 遍历源对象状态块
//（vt+348 返回，+24 起 3 个槽，0x11(17) = 空槽标记）逐槽经本对象 vt+760 重施加
//（参数 = 槽 id / pSlotWalk[3] / pSlotWalk[6] / 源对象 vt+576(0) 的宿主 id）。
// 【推断】用于对象替换/复活时把旧对象身上的持续状态搬到新对象。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D4AE0(uint32_t *this, int nArg2)  // 实现：(推断)用于对象替换/复活时把旧对象身上的持续状态搬到新对象
{
  int pObj; // ebx
  int pStatusBlk; // edi
  uint32_t *pSlotWalk; // edi
  int nOwnerId; // eax
  int result; // eax
  int pVt; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  pObj = nArg2;
  pStatusBlk = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // 调虚槽 +348：取坐标对象
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 1) != 0 && *(uint32_t *)(pStatusBlk + 20) == 0 )  // 虚调用 vt+776
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 764))(this, 1, 0, 0, 0);  // 虚调用 vt+764
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 8) != 0  // 虚调用 vt+776
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 4  // 虚调用 vt+840
    && *(this + 1708) == 2
    && *(uint32_t *)(pStatusBlk + 60) != 0 )  // 受击后观察者 vt+516（六回调第 6 号，研究 §1.1/§1.2）
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 764))(this, 8, 0, 0, 0);  // 虚调用 vt+764
  }
  pSlotWalk = (uint32_t *)(pStatusBlk + 24);
  for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
  {
    if ( *pSlotWalk != 17 )
    {
      pVt = *this;
      nOwnerId = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 576))(pObj, 0);  // 调虚槽 +576
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int))(pVt + 760))(this, *pSlotWalk, pSlotWalk[3], pSlotWalk[6], nOwnerId);  // 调虚槽 +760：状态槽写入(17 槽异常状态)
      pObj = nArg2;
    }
    ++pSlotWalk;
    result = i - 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D4BC0 sub_4D4BC0
// 命中表现 + 告示包 type 14（打包器 = dword_8F8520，与 HP setter 0x4D4D40 的 type 12
// 同一套路）：pszArg7（强制）或 vt+308（本地玩家）门通过后，先走 vt+768 本地命中
// 表现，再打包（自 id vt+48、自 vt+52、nArg4、nArg5、攻击者 nArg6 的 vt+48 与两次
// vt+52 —— 攻击者缺席一律填 0xFFFF，再补 0, 0）发送（vt+60(1,-1)）。
// ------------------------------------------------------------
int /*userpurge*/ sub_4D4BC0@<eax>(int nArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4, int nArg5, int nArg6, char pszArg7)  // 实现：vt+52 —— 攻击者缺席一律填 0xFFFF，再补 0, 0）发送（vt+60(1,-1)）
{
  int result; // eax
  int pPktVt; // ebx —— 打包器当前虚表指针（vt+36 写坐标）
  int nSelfX; // eax
  int pPktVt2; // ebx
  int nSelfY; // eax
  int nAtkX; // eax
  int nAtkY; // eax
  int nAtkY2; // eax

  if ( pszArg7 != 0 || (uint8_t)(result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 308))(nArg1)) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)nArg1 + 768))(nArg1, nArg4, nArg5, nArg6, nArg3, nArg2);  // 调虚槽 +768
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 14, 1);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
    pPktVt = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    nSelfX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 48))(nArg1);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, int))(pPktVt + 36))(dword_8F8520, nSelfX);  // 会话/UDP 管理器
    pPktVt2 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    nSelfY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 52))(nArg1);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    (*(void (/*thiscall*/ **)(int, int))(pPktVt2 + 36))(dword_8F8520, nSelfY);  // 会话/UDP 管理器
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nArg4);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg5);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    if ( nArg6 != 0 )
      nAtkX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg6 + 48))(nArg6);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    else
      nAtkX = 0xFFFF;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nAtkX);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    if ( nArg6 != 0 )
      nAtkY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg6 + 52))(nArg6);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    else
      nAtkY = 0xFFFF;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nAtkY);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    if ( nArg6 != 0 )
      nAtkY2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg6 + 52))(nArg6);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    else
      nAtkY2 = 0xFFFF;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nAtkY2);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 0);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D4CE0 sub_4D4CE0
// 观察者广播收尾：先 sub_4E7440(nArg2)（【推断】停摆/关闭开关），再对 18 个观察者
//（this+6468 起）逐个调 vt+128 并传入 this+388 子上下文（六回调族共用的上下文块，
// 参见 0x4D4A20 尾参 this+97*4），尾调 sub_53F7A0(this+388) 做该上下文的收束并返回。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D4CE0(char *this, int nArg2)  // 实现：参见 0x4D4A20 尾参 this+97*4），尾调 sub_53F7A0(this+388) 做该上下文的收束并返回
{
  char *pThis_1944; // esi
  int i; // ebx

  sub_4E7440(nArg2);  // 攻击上下文设置（研究 P29 已引: sub_4B2970 拷贝/4A3450 默认）
  pThis_1944 = this + 6468;  // this+6468〔apObserver18〕
  for ( i = 18; i != 0; --i )  // 循环：i 从 18 递减到 0
  {
    if ( *(uint32_t *)pThis_1944 != 0 )  // pThis_1944=this+6468 apObserver18
      (*(void (/*stdcall*/ **)(char *))(**(uint32_t **)pThis_1944 + 128))(this + 388);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
    pThis_1944 += 4;  // pThis_1944=this+6468 apObserver18
  }
  return sub_53F7A0(this + 388);  // this+388 【推断】攻击上下文浮点值
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
int /*userpurge*/ sub_4D4D40@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4, char pszArg5, int nArg6)  // 实现：HP setter / DMGAPPLY vt+728（研究 20 §1.1 定案；DLL 锚点 ）
{
  int result; // eax
  int nHpCur; // eax
  int nHpDelta; // edi
  int pObj2; // eax
  int *pOwner; // edi
  int nKillId; // eax
  int pObj; // ecx
  int pObj3; // eax
  int nNewHp; // edi
  int pPacket; // ebx
  int nSelfX; // eax
  int pPacket2; // ebx
  int nSelfY; // eax
  float nDamage; // [esp+4h] [ebp-8h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 结果 = 虚调用 vt+308
  if ( (uint8_t)result == 0 )
    return result;
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 724))(pArg1);  // 结果 = 虚调用 vt+724
  if ( (uint8_t)result != 0 )
    return result;
  nHpCur = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 736))(pArg1, nArg3, nArg2);  // 结果 = 虚调用 vt+736
  nHpDelta = nArg4;
  if ( nArg4 < 0 )
  {
    nDamage = (float)(nHpCur - nArg4);
    if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1) * 0.30000001 <= nDamage )  // 虚调用 vt+740
    {
      *((uint8_t *)pArg1 + 7092) = 1;
      if ( nArg6 != 0 )
      {
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 4  // 全局 dword_8F7A24 = 登录/选区管理器
          && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 40))(pArg1, 273) == 0  // 虚调用 vt+40
          && (*(uint32_t *)(dword_8F7A24 + 12) != 6  // 全局 dword_8F7A24 = 登录/选区管理器
           || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 40))(pArg1, 273) == 0) )  // 虚调用 vt+40
        {
          goto LABEL_19;
        }
        pObj2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg6 + 576))(nArg6);  // 调虚槽 +576
        pOwner = (int *)pObj2;
        if ( pObj2 == 0 )
          goto LABEL_19;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        {
          nKillId = (*(int (/*thiscall*/ **)(int *))(*pOwner + 52))(pOwner);  // 结果 = 虚调用 vt+52
        }
        else
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*pOwner + 40))(pOwner, 529) == 0 )  // 虚调用 vt+40
            goto LABEL_19;
          pObj = pOwner[2088];
          if ( pObj == 0 )
            goto LABEL_19;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273) == 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
            goto LABEL_19;
          pObj3 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                  pOwner[2088],
                  0,
                  &IRDActiveObject `RTTI Type Descriptor',
                  &IRDCharacter `RTTI Type Descriptor',
                  0);
          if ( pObj3 == 0 )
            goto LABEL_19;
          nKillId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 52))(pObj3);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        }
        sub_495A70(1, 3, nKillId);  // 场景对象动画挂接（+1004 门控；v5==4 PVP 分流 aPvp_2 / v5==6
LABEL_19:
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg6 + 576))(nArg6) == dword_8F7C04 || nArg6 == dword_8F7C04 )  // 全局 dword_8F7C04 = 本机角色对象
          sub_426820(*(uint32_t *)(pArg1[29] + 132), 0, 0);  // 【总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTA…】
        nHpDelta = nArg4;
      }
    }
  }
  nNewHp = nHpDelta < 0 ? 0 : nHpDelta;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1) < nNewHp )  // 虚调用 vt+740
    nNewHp = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1);  // 结果 = 虚调用 vt+740
  if ( pszArg5 != 0 || nNewHp == 0 )  // 若 pszArg5 != 0 与/或 nNewHp == 0
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 12, 1);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
    pPacket = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    nSelfX = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 48))(pArg1);  // 结果 = 虚调用 vt+48
    (*(void (/*thiscall*/ **)(int, int))(pPacket + 36))(dword_8F8520, nSelfX);  // 会话/UDP 管理器
    pPacket2 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    nSelfY = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);  // 结果 = 虚调用 vt+52
    (*(void (/*thiscall*/ **)(int, int))(pPacket2 + 36))(dword_8F8520, nSelfY);  // 会话/UDP 管理器
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nNewHp);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    pArg1[1650] = -1;
  }
  else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 736))(pArg1) != nNewHp && pArg1[1650] == -1 )  // 虚调用 vt+736
  {
    pArg1[1650] = sub_699000(pArg1 + 2);  // 【clock_now(clk)】
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 732))(pArg1, nNewHp);  // 虚调用 vt+732
}



// ------------------------------------------------------------
// 0x4D4F90 sub_4D4F90 —— MP setter vt+748（HP setter 0x4D4D40 的同构对偶）
// 流程镜像：vt+308 门 → vt+724 门 → vt+756(GetMP) 取当前 → 夹取 [0, vt+756] →
// a4(强制) 走告示包 type 13 + a1[1651]=−1；否则变化时戳 a1[1651] → 尾调 vt+748 写回。
// 与 0x4D4D40 共用 a1[1650]/a1[1651] 两个"上次写入时刻戳"字段。
// ------------------------------------------------------------
int /*userpurge*/ sub_4D4F90@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3, char pszArg4)  // 实现：MP setter vt+748（HP setter 0x4D4D40 的同构对偶）
{
  int result; // eax
  int nNewMp; // edi
  int pPacket; // ebx
  int nSelfX; // eax
  int pPacket2; // ebx
  int nSelfY; // eax
  int pVt; // edx

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 结果 = 虚调用 vt+308
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 724))(pArg1);  // 结果 = 虚调用 vt+724
    if ( (uint8_t)result == 0 )
    {
      nNewMp = nArg3 < 0 ? 0 : nArg3;
      if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 756))(pArg1, nArg2) < nNewMp )  // 虚调用 vt+756
        nNewMp = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 756))(pArg1);  // 结果 = 虚调用 vt+756
      if ( pszArg4 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 13, 1);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
        pPacket = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        nSelfX = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 48))(pArg1);  // 结果 = 虚调用 vt+48
        (*(void (/*thiscall*/ **)(int, int))(pPacket + 36))(dword_8F8520, nSelfX);  // 会话/UDP 管理器
        pPacket2 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        nSelfY = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);  // 结果 = 虚调用 vt+52
        (*(void (/*thiscall*/ **)(int, int))(pPacket2 + 36))(dword_8F8520, nSelfY);  // 会话/UDP 管理器
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nNewMp);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
        pVt = *pArg1;
        pArg1[1651] = -1;
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(pVt + 748))(pArg1, nNewMp);  // 调虚槽 +748：[RTTI: IRDActiveObject__vmt2EC · 槽位 IRDActiveObj…
      }
      else
      {
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 752))(pArg1) != nNewMp && pArg1[1651] == -1 )  // 虚调用 vt+752
          pArg1[1651] = sub_699000(pArg1 + 2);  // 【clock_now(clk)】
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 748))(pArg1, nNewMp);  // 虚调用 vt+748
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D50A0 sub_4D50A0
// 挂接宿主/场景对象：this+120 = pArg2；绑定时钟域（this+92，clock_bind_domain），
// pArg2+168 标志成立时先 sub_4938F0 初始化；随后把 this+6656（构造默认 1000）
// ×0.1 = 100.0 经 sub_493D00 传给宿主（【推断】时间流速/缩放类参数）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D50A0(int *this, int pArg2)  // 实现：×0.1 = 100.0 经 sub_493D00 传给宿主（(推断)时间流速/缩放类参数）
{
  int pHost; // ecx
  float fScale; // [esp+0h] [ebp-Ch]

  *(this + 30) = pArg2;  // 写 this+120 = pArg2（动画对象）
  if ( pArg2 != 0 )
  {
    sub_699070(*(this + 23));  // 【clock_bind_domain(clk, newDomainId)】
    if ( *(uint8_t *)(pArg2 + 168) != 0 )  // pArg2+168〔pAppendVec(推断)〕
      sub_4938F0(pArg2);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  }
  pHost = *(this + 30);  // 读 pHost = this+120（动画对象）
  if ( pHost != 0 )  // pHost=this+120 pAnimObj
  {
    fScale = (double)*(this + 1664) * 0.1;  // this+6656〔nRateDen〕
    sub_493D00(pHost, fScale);  // 变速（研究§26）
  }
}



// ------------------------------------------------------------
// 0x4D50F0 sub_4D50F0
// ·0x4D50A0 的通知侧对偶：把 (nArg2..pszArg7) 六参透传给 sub_49A7B0（【推断】宿主
// 对象变更回调），随后对 nArg3（宿主对象）应用 this+6656×0.1 缩放（与 0x4D50A0
// 尾段同参，构造默认 1000 → 100.0）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D50F0(int *this, int nArg2, int nArg3, int nArg4, int nArg5, char pszArg6, char pszArg7)  // 实现：尾段同参，构造默认 1000 → 100.0）
{
  float fld_e1664; // [esp+0h] [ebp-Ch]

  sub_49A7B0(nArg2, nArg3, nArg4, nArg5, pszArg6, pszArg7);  // 定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
  if ( nArg3 != 0 )
  {
    fld_e1664 = (double)*(this + 1664) * 0.1;  // this+6656〔nRateDen〕
    sub_493D00(nArg3, fld_e1664);  // 变速（研究§26）
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
BOOL /*thiscall*/ sub_4D5140(uint32_t *this, int pArg2)  // 异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
{
  int pObj; // edx

  pObj = *(this + pArg2 + 1557);
  return pObj != 0 && (*(uint8_t (**)(void))(*(uint32_t *)pObj + 24))() != 0;  // 调虚槽 +24：CNRDSkillInventoryWindow__vmt18 页签动作（41A5E0 + …
}



// ------------------------------------------------------------
// 0x4D5170 sub_4D5170 —— ★ 霸体 setter vt+720（研究 20 §1.2 + §14#10 定案）
// 写 this+6552 霸体字节；**开启（a2!=0）时通知全部 17 个"已激活"的状态对象
// ->vt+68()**（逐槽 vt+776 查询 → 状态对象 vt+68 回调）—— 与反编译体循环
// `for v4<17，vt+776 非 0 才调 *v5+68` 逐条吻合。
// 研究 §14#10：调用者 = ~94 张子类虚表（霸体开启由子类/技能逻辑驱动）；
// `.ani` 帧 DAMAGE TYPE(+52) → +6552 的直连仍未证实【待验证】。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D5170(uint8_t *this, char pszArg2)  // 实现：霸体 setter vt+720（研究 20 §1.2 + §14#10 定案）
{
  char result; // al
  int nSlotId; // esi
  uint32_t *pStatusSlotCur; // edi —— 17 状态槽数组(this+6228)游标，*pStatusSlotCur = 状态对象

  result = pszArg2;
  if ( pszArg2 != *(this + 6552) )  // this+6552 霸体字节
  {
    *(this + 6552) = pszArg2;  // this+6552 霸体字节
    if ( pszArg2 != 0 )
    {
      nSlotId = 0;
      pStatusSlotCur = this + 6228;  // this+6228〔anState17〕
      do
      {
        result = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 776))(this, nSlotId);  // 调虚槽 +776：异常状态查询
        if ( result != 0 )  // 若结果非 0（成功）
          result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pStatusSlotCur + 68))(*pStatusSlotCur);  // 结果 = 虚调用 vt+68
        ++nSlotId;
        ++pStatusSlotCur;  // pStatusSlotCur=this+6228 anState17
      }
      while ( nSlotId < 17 );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D51C0 sub_4D51C0
// 状态全清：遍历 17 个异常状态槽，vt+776 查得激活的槽对其状态对象调 vt+4(0,0)
//（【推断】解除/复位回调；与 0x4D5700 的 vt+80 移交成族）。返回最后一次调用值。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D51C0(uint32_t *this)  // 实现：（(推断)解除/复位回调；与 0x4D5700 的 vt+80 移交成族）。返回最后一次调用值
{
  int nSlotId; // esi
  uint32_t *pThis_615; // edi
  int result; // eax

  nSlotId = 0;
  pThis_615 = this + 1557;
  do
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, nSlotId);  // 结果 = 虚调用 vt+776
    if ( (uint8_t)result != 0 )
      result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)*pThis_615 + 4))(*pThis_615, 0, 0);  // 结果 = 虚调用 vt+4
    ++nSlotId;
    ++pThis_615;
  }
  while ( nSlotId < 17 );
  return result;
}



// ------------------------------------------------------------
// 0x4D5200 sub_4D5200
// 事件包分派器：pDwArg2[0] = 事件 id（0..3），pDwArg2[3] = 开关位。
//   case 0 → vt+604(this, 开关==0)；case 1 → 置 this+7093 大伤害标志 +
//   stdcall vt+252(3, 开关?100:-1)；case 2/3 → 用 vt+616()/vt+620() 的返回值组合
//   （1/2）得 nMode 后走 vt+612(this, 开关==1, nMode)。细节语义未定案【待验证】。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5200(uint8_t *this, int *pDwArg2)  // 实现：（1/2）得 nMode 后走 vt+612(this, 开关==1, nMode)。细节语义未定案(待验证)
{
  int result; // eax
  uint8_t *pThis; // esi
  int pVt0; // eax
  int pVt1; // edx
  int pVt2; // eax
  int pVt3; // edx
  int pVt4; // edx
  int nOnFlag; // eax
  int nMode; // [esp-8h] [ebp-10h]

  result = *pDwArg2;
  pThis = this;
  switch ( *pDwArg2 )  // 按 *pDwArg2 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      pVt0 = *(uint32_t *)this;
      LOBYTE(this) = pDwArg2[3] == 0;  // 调 取 16 位值低 8 位
      return (*(int (/*thiscall*/ **)(uint8_t *, uint8_t *))(pVt0 + 604))(pThis, this);  // 调虚槽 +604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( pDwArg2[3] != 0 )
      {
        pVt1 = *(uint32_t *)this;
        *(this + 7093) = 1;  // 字段 this+7093〔大伤害标志〕
        return (*(int (/*stdcall*/ **)(int, int))(pVt1 + 252))(3, 100);  // 虚函数调用 槽+252：时刻槽写入（-1 语义为推进并释放）
      }
      else
      {
        pVt2 = *(uint32_t *)this;
        *(this + 7093) = 0;  // 字段 this+7093〔大伤害标志〕
        return (*(int (/*stdcall*/ **)(int, int))(pVt2 + 252))(3, -1);  // 虚函数调用 槽+252：时刻槽写入（-1 语义为推进并释放）
      }
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      pVt3 = *(uint32_t *)this;
      if ( pDwArg2[3] == 1 )
      {
        if ( (*(uint8_t (**)(void))(pVt3 + 616))() == 0  // 虚函数调用 槽+616
          || (result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pThis + 620))(pThis)) != 1 )  // 调虚槽 +620
        {
          nMode = 1;
          goto LABEL_20;
        }
      }
      else
      {
        result = (*(int (**)(void))(pVt3 + 616))();  // 虚函数调用 槽+616
        if ( (uint8_t)result == 1 )
        {
          result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pThis + 620))(pThis);  // 调虚槽 +620
          if ( result == 1 )
          {
            nMode = 1;
            goto LABEL_20;
          }
        }
      }
      return result;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      pVt4 = *(uint32_t *)this;
      if ( pDwArg2[3] == 1 )
      {
        if ( (*(uint8_t (**)(void))(pVt4 + 616))() != 0 )  // 虚函数调用 槽+616
        {
          result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pThis + 620))(pThis);  // 调虚槽 +620
          if ( result == 2 )
            return result;
        }
      }
      else
      {
        result = (*(int (**)(void))(pVt4 + 616))();  // 虚函数调用 槽+616
        if ( (uint8_t)result != 1 )
          return result;
        result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pThis + 620))(pThis);  // 调虚槽 +620
        if ( result != 2 )
          return result;
      }
      nMode = 2;
LABEL_20:
      nOnFlag = pDwArg2[3];
      LOBYTE(nOnFlag) = nOnFlag == 1;  // 调 取 16 位值低 8 位
      return (*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pThis + 612))(pThis, nOnFlag, nMode);  // 调虚槽 +612
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
int /*cdecl*/ sub_4D5330(int nArg1, int nArg2, float *pArg3, int nArg4, int nArg5, char pszArg6, int nArg7, int nArg8)  // 实现：伤害日志写出（DNF.trc；研究 §2⑦ 定案勿与 HP setter 混淆）
{
  int pPktVt; // edi
  int nArg1F48; // eax
  int pPktVt2; // edi
  int nArg1F52; // eax
  int pPktVt3; // edi
  int nArg2F48; // eax
  int pPktVt4; // edi
  int nArg2F52; // eax
  int pPktVt5; // edi
  int nHpSnapshot; // eax
  int nFlagByte; // edx
  int tmpWord; // [esp+8h] [ebp-4h] BYREF

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 20, 2);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
  pPktVt = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
  nArg1F48 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 48))(nArg1);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
  (*(void (/*thiscall*/ **)(int, int))(pPktVt + 36))(dword_8F8520, nArg1F48);  // 会话/UDP 管理器
  pPktVt2 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
  nArg1F52 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 52))(nArg1);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  (*(void (/*thiscall*/ **)(int, int))(pPktVt2 + 36))(dword_8F8520, nArg1F52);  // 会话/UDP 管理器
  pPktVt3 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
  nArg2F48 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 48))(nArg2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
  (*(void (/*thiscall*/ **)(int, int))(pPktVt3 + 36))(dword_8F8520, nArg2F48);  // 会话/UDP 管理器
  pPktVt4 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
  nArg2F52 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 52))(nArg2);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  (*(void (/*thiscall*/ **)(int, int))(pPktVt4 + 36))(dword_8F8520, nArg2F52);  // 会话/UDP 管理器
  (*(void (/*thiscall*/ **)(int, float *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, pArg3, 4);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
  tmpWord = (uint64_t)pArg3[1];
  (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &tmpWord, 2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
  tmpWord = (uint64_t)pArg3[2];
  (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &tmpWord, 2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
  tmpWord = (uint64_t)pArg3[3];
  (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &tmpWord, 2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
  tmpWord = (uint64_t)pArg3[4];
  (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &tmpWord, 2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
  tmpWord = (uint64_t)pArg3[5];
  (*(void (/*thiscall*/ **)(int, int *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &tmpWord, 2);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
  (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, abs32(nArg4));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, abs32(nArg5));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  pPktVt5 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
  nHpSnapshot = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 736))(nArg2);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
  (*(void (/*thiscall*/ **)(int, int))(pPktVt5 + 40))(dword_8F8520, nHpSnapshot);  // 会话/UDP 管理器
  LOBYTE(nFlagByte) = pszArg6 != 0;  // 调 取 16 位值低 8 位
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nFlagByte);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
  (*(void (/*thiscall*/ **)(int, unsigned int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, abs32(nArg7));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nArg8);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
}



// ------------------------------------------------------------
// 0x4D54E0 sub_4D54E0
// 受击闪烁/淡出 alpha 控制（受击表现侧）：以 this+7108（窗起点）计时，
// 1000ms 内用 sub_4049C0 在 255→0（受击变暗）或 0→255（恢复）间插值 alpha；
// 每帧 sub_4938F0 刷新宿主（this+120）后 sub_491F80(host,-1,-1,-1,alpha,1) 上色；
// 本地玩家（条件 273 且 dword_8F7C04 同主）alpha 下限 128 保证可见；
// 窗过期（>1000ms）置 this+7112 = -1。vt+940 = 总门。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D54E0(int *this)  // 实现：窗过期（>1000ms）置 this+7112 = -1。vt+940 = 总门
{
  int nAlpha; // edi
  int nElapsed; // eax
  int pHost; // ecx
  int nOwnerId; // ebx
  uint64_t nNow; // rax
  int pHost2; // ecx
  int nAlpha2; // edi

  sub_53F960(*(this + 1574));  // 调 批量广播器 vt+16 槽（无参）
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) != 0 )  // 虚调用 vt+940
  {
    nAlpha = 0;
    nElapsed = sub_699000((int)(this + 9)) - *(this + 1777);  // 【clock_now(clk)】
    if ( nElapsed <= 1000 )
      nAlpha = (uint64_t)sub_4049C0(255.0, 0.0, nElapsed, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    pHost = *(this + 30);  // 读 pHost = this+120（动画对象）
    if ( pHost != 0 )  // pHost=this+120 pAnimObj
    {
      sub_4938F0(pHost);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      if ( ((*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 40))(this, 273) != 0 && (int *)dword_8F7C04 == this  // 虚调用 vt+40
         || (nOwnerId = (*(int (/*thiscall*/ **)(int *))(*this + 376))(this)) == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04))  // 虚调用 vt+376
        && nAlpha <= 128 )
      {
        nAlpha = 128;
      }
      sub_491F80(*(this + 30), -1, -1, -1, nAlpha, 1);  // RGBA 设置（打包于 +92；-1=保留原通道；a6≠0 时广播子链 +204）
    }
    LODWORD(nNow) = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( (int)nNow >= *(this + 1778) )  // this+7112〔uSet7112〕
      LOBYTE(nNow) = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 944))(this, 0, -1);  // 虚调用 vt+944
  }
  else
  {
    LODWORD(nNow) = *(this + 1778);  // this+7112〔uSet7112〕
    if ( (uint32_t)nNow != -1 )
    {
      LODWORD(nNow) = sub_699000((int)(this + 9)) - *(this + 1777);  // 【clock_now(clk)】
      if ( (int)nNow > 1000 )
      {
        *(this + 1778) = -1;  // this+7112〔uSet7112〕
      }
      else
      {
        nNow = (uint64_t)sub_4049C0(0.0, 255.0, nNow, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        pHost2 = *(this + 30);  // 读 pHost2 = this+120（动画对象）
        nAlpha2 = nNow;
        if ( pHost2 != 0 )  // pHost2=this+120 pAnimObj
        {
          sub_4938F0(pHost2);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
          if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 40))(this, 273) != 0  // 虚调用 vt+40
            && (int *)dword_8F7C04 == this  // 全局 dword_8F7C04 = 本机角色对象
            && nAlpha2 <= 128 )
          {
            nAlpha2 = 128;
          }
          LOBYTE(nNow) = sub_491F80(*(this + 30), -1, -1, -1, nAlpha2, 1);  // RGBA 设置（打包于 +92；-1=保留原通道；a6≠0 时广播子链 +204）
        }
      }
    }
  }
  return nNow;
}



// ------------------------------------------------------------
// 0x4D5650 sub_4D5650 —— ★ HP 吸收/回复量折算（研究 §12 [HP drain]/[MP drain] 消费侧）
// vt+716 取"基础值+加成"两路浮点（&v10/&v11），按 a4 选全局系数
// （0 → flt_9A05FC；1 → flt_9A0614 —— 运行时从数据文件加载，PE 内全 0，研究 §11）；
// 场景 4/6（PVP/战场）系数 ×2（研究 §11 "PVP/战场速率走查表修正"同族）；
// 最终 `a3 × (v10+v11) × 系数 / (1 − (v10+v11))`，比率上限 0.99000001。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4D5650(int *this, uint32_t *uArg2, int nArg3, int nArg4, int nArg5)  // 实现：HP 吸收/回复量折算（研究 §12 / 消费侧）
{
  int pVt; // eax
  double fCoef; // st7
  int nSceneId; // eax
  double fRatio; // st6
  uint64_t result; // rax
  float fBase; // [esp+4h] [ebp-8h] BYREF
  float fBonus; // [esp+8h] [ebp-4h] BYREF

  pVt = *this;
  fBase = 0.0;
  fBonus = 0.0;
  (*(void (/*thiscall*/ **)(int *, float *, float *, int, int))(pVt + 716))(this, &fBase, &fBonus, nArg3, nArg4);  // 调虚槽 +716：音效地板停播 vmt2CC
  fCoef = 0.0;
  if ( nArg4 != 0 )
  {
    if ( nArg4 == 1 )
      fCoef = flt_9A0614;
  }
  else
  {
    fCoef = flt_9A05FC;
  }
  nSceneId = *(uint32_t *)(dword_8F7A24 + 12);  // 全局 dword_8F7A24 = 登录/选区管理器
  if ( nSceneId == 4 || nSceneId == 6 )  // 若 nSceneId == 4 与/或 nSceneId == 6
    fCoef = fCoef + fCoef;
  fRatio = fBonus + fBase;
  if ( fRatio >= 0.99000001 )
    fRatio = 0.99000001;
  result = (uint64_t)((double)nArg3 * fRatio * fCoef / (1.0 - fRatio));
  *uArg2 = result;
  return result;
}



// ------------------------------------------------------------
// 0x4D5700 sub_4D5700 —— 状态对象引用移交（self == a2 时对 17 个激活状态 ->vt+80）
// 与 0x4D51C0（17 槽 ->vt+4 清理）成族 —— 研究 §10 状态对象生命周期。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5700(uint32_t *this, uint32_t *uArg2)  // 实现：状态对象引用移交（self == a2 时对 17 个激活状态 ->vt+80）
{
  int result; // eax
  int nSlotId; // esi
  uint32_t *pThis_615; // edi

  result = (int)uArg2;
  if ( uArg2 == this )
  {
    nSlotId = 0;
    pThis_615 = this + 1557;
    do
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, nSlotId);  // 结果 = 虚调用 vt+776
      if ( (uint8_t)result != 0 )
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t *))(*(uint32_t *)*pThis_615 + 80))(*pThis_615, uArg2);  // 结果 = 虚调用 vt+80
      ++nSlotId;
      ++pThis_615;
    }
    while ( nSlotId < 17 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D5750 sub_4D5750
// 骑乘中换帧处理（骑乘态 this+6556==9，与 0x4D5820 同门）：nArg3 决定目标帧取
// vt+120(nArg3)+1 或 -1（正/反向），nArg2 作 vt+124(0,nArg2) 的速度参数；
// vt+136(当前帧,目标帧) 校验不过则回退换向重算，通过则再经 vt+128/vt+124 取值后
// vt+112(帧,值) 落地。pArg1[1687] 经 sub_432E50 布尔化（0/1 方向标志）。
// ------------------------------------------------------------
void /*usercall*/ sub_4D5750(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：vt+112(帧,值) 落地。pArg1[1687] 经 sub_432E50 布尔化（0/1 方向标志）
{
  int nTargetFrame; // edi
  int nTurnFlag; // eax
  int pVt0; // ebx
  int nFrameCur; // eax
  int pVt1; // ebx
  int nFrameCur2; // eax
  int pVt2; // ebx
  int nFrameMax; // eax
  int nFrameNew; // eax

  if ( pArg1[1639] == 9 )
  {
    if ( pArg1[1687] != 0 )
      nTargetFrame = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg3) + 1;  // 结果 = 虚调用 vt+120
    else
      nTargetFrame = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg3) - 1;  // 结果 = 虚调用 vt+120
    nTurnFlag = sub_432E50(pArg1[1687]);  // 结果 = 关系码对调映射
    pVt0 = *pArg1;
    pArg1[1687] = nTurnFlag;
    nFrameCur = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(pVt0 + 124))(pArg1, 0, nArg2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int))(pVt0 + 136))(pArg1, nTargetFrame, nFrameCur) == 0 )  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
    {
      if ( pArg1[1687] != 0 )
        nTargetFrame = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) + 1;  // 结果 = 虚调用 vt+120
      else
        nTargetFrame = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - 1;  // 结果 = 虚调用 vt+120
      pArg1[1687] = sub_432E50(pArg1[1687]);  // 结果 = 关系码对调映射
    }
    pVt1 = *pArg1;
    nFrameCur2 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 124))(pArg1, 0);  // 结果 = 虚调用 vt+124
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int))(pVt1 + 136))(pArg1, nTargetFrame, nFrameCur2) != 0 )  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
    {
      pVt2 = *pArg1;
      nFrameMax = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);  // 结果 = 虚调用 vt+128
      nFrameNew = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, nFrameMax);  // 结果 = 虚调用 vt+124
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(pVt2 + 112))(pArg1, nTargetFrame, nFrameNew);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    }
  }
}



// ------------------------------------------------------------
// 0x4D5820 sub_4D5820
// 骑乘解除检查（this+6556==9）：在 this+6172/+6176 两个槽里找 宿主(this+120) 匹配
// 且非空的项，命中则调 vt+196 传槽值，并 sub_4926A0 / sub_4939E0(宿主,1) 刷新表现。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D5820(int *this)  // 实现：且非空的项，命中则调 vt+196 传槽值，并 sub_4926A0 / sub_4939E0(宿主,1) 刷新表现
{
  int pHost; // edi
  int nSlotIdx; // eax
  uint32_t *pThis_607; // ecx
  uint32_t *i; // edx

  if ( *(this + 1639) == 9 )  // 判定 “+6556 大状态ID”
  {
    pHost = *(this + 30);  // 读 pHost = this+120（动画对象）
    nSlotIdx = 0;
    pThis_607 = this + 1543;
    for ( i = this + 1544; pHost != *pThis_607 || *i == 0; --i )  // pHost=this+120 pAnimObj
    {
      ++nSlotIdx;
      ++pThis_607;
      if ( nSlotIdx >= 2 )
        return;
    }
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1544 - nSlotIdx));  // 虚调用 vt+196
    sub_4926A0(*(this + 30));  // 帧游标复位（+44 帧数组；递归子链 +204）
    sub_4939E0(*(this + 30), 1);  // 播放/暂停级联（递归子链 +204）
  }
}



// ------------------------------------------------------------
// 0x4D5890 sub_4D5890
// 被抓取/举起判定：状态 16（hold，研究 §10 枚举）激活时返回 vt+840()==5
//（【推断】"被举起"子态码），否则转 sub_4E4950(nArg2,nArg3,nArg4) 判定。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D5890(void *this, int nArg2, int nArg3, int nArg4)  // 实现：（(推断)被举起子态码），否则转 sub_4E4950(nArg2,nArg3,nArg4) 判定
{
  if ( (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 776))(this, 16) != 0 )  // 调虚槽 +776：异常状态查询
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) == 5;  // 调虚槽 +840：大状态 getter（this+6556）
  else
    return sub_4E4950(nArg2, nArg3, nArg4);  // 朝向/位置偏移判定（研究 §1.2 vt+688 骨架的消费侧）
}



// ------------------------------------------------------------
// 0x4D58E0 sub_4D58E0
// 小比较回调（stdcall）：返回 nArg1 >= 0（排序/过滤族回调，【推断】qsort 谓词）。
// ------------------------------------------------------------
BOOL /*stdcall*/ sub_4D58E0(int nArg1)  // 实现：小比较回调（stdcall）：返回 nArg1 >= 0（排序/过滤族回调，(推断)qsort 谓词）
{
  return nArg1 >= 0;
}



// ------------------------------------------------------------
// 0x4D5900 sub_4D5900
// 动画/状态收尾回调：sub_41A590(nArg2)（全局临时槽释放，构造 0x4D46C0 也以 0 调用）；
// nArg2==0 时开霸体（vt+720 = 0x4D5170）；pszArg4 置位时重置 HP 写入时刻戳
// this+6600 = -1（HP setter 0x4D4D40 的 a1[1650] 字段）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D5900(uint32_t *this, int nArg2, int nArg3, char pszArg4)  // 实现：this+6600 = -1（HP setter 0x4D4D40 的 a1[1650] 字段）
{
  char result; // al

  sub_41A590(nArg2);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  if ( nArg2 == 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 720))(this, 1);  // 虚调用 vt+720
  result = pszArg4;
  if ( pszArg4 != 0 )
    *(this + 1650) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x4D5940 sub_4D5940
// 场景相关动作编号映射：场景码 this+7088（0x4D49A0 写 0 或 7）× nArg2（0/1/2，
// 【推断】待机/走/跑档位）→ 动画编号：场景 2:30-32、3:33-35、7:36-38、8:40-42、
// 其余:10-12。返回编号，无副作用。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5940(uint32_t *this, int nArg2)  // 实现：其余:10-12。返回编号，无副作用
{
  int result; // eax

  switch ( *(this + 1772) )  // 按 *(this + 1772) 分派
  {
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
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
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
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
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
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
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
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
int /*thiscall*/ sub_4D5A60(uint8_t *this, uint32_t *uArg2, int nArg3)  // 实现：伤害类型/命中类型计算 vt+648（研究 §1.2 定案 6 版本之一）
{
  if ( *(this + 7093) == 1 )  // 字段 this+7093〔大伤害标志〕
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
// 0x4D5A90 sub_4D5A90 —— 影身计时三连写
// this+7096 = clock_now(this+36)（起始时刻）、this+7100 = nArg2（时长 ms）、
// this+7104 = pszArg3（开关字节）。返回 nArg2。【推断】隐身/伪装窗口参数（配合 0x4D7F30）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5A90(int this, int nArg2, char pszArg3)  // 实现：影身计时三连写
{
  *(uint32_t *)(this + 7096) = sub_699000(this + 36);  // clock_now(clk)
  *(uint32_t *)(this + 7100) = nArg2;  // 写 this+7100 = nArg2（影身/伪装窗口时长 ms）
  *(uint8_t *)(this + 7104) = pszArg3;  // 写 this+7104 = pszArg3（影身/伪装开关字节）
  return nArg2;
}



// ------------------------------------------------------------
// 0x4D5AC0 sub_4D5AC0 —— 影身剩余量折算
// vt+1000() 门通过后取 this+7100（时长）：this+7104 置位时按 1000×时长/this+6656
//（基准时长）折算返回，否则原值。【推断】隐身渐进透明度的分母换算（0x4D54E0 消费）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5AC0(int *this)  // 实现：影身剩余量折算
{
  int result; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1000))(this) == 0 )  // 虚调用 vt+1000
    return 0;
  result = *(this + 1775);  // 读 result = this+7100（影身/伪装窗口时长 ms）
  if ( *((uint8_t *)this + 7104) != 0 )  // this+7104〔bStealthFlag〕
    return 1000 * result / *(this + 1664);  // this+6656〔nRateDen〕
  return result;  // result=this+7100 nInvisibleDur
}



// ------------------------------------------------------------
// 0x4D5B00 sub_4D5B00
// 取 vt+1004() / vt+1008() 两个值后在 [0.0, 50.0] 区间做 sub_4049C0 插值并取整返回。
// 两个 vtable 槽的具体业务含义未定案【待验证】（观察者/状态族回调，疑为概率或权重对）。
// ------------------------------------------------------------
int64_t /*thiscall*/ sub_4D5B00(void *this)  // 影身剩余量折算
{
  int nVt1004Ret; // edi
  int nVt1008Ret; // eax
  double fLerpRet; // st7

  nVt1004Ret = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1004))(this);  // 调虚槽 +1004
  nVt1008Ret = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1008))(this);  // 调虚槽 +1008：复活已计时（clockAux 域差值）
  fLerpRet = sub_4049C0(0.0, 50.0, nVt1008Ret, nVt1004Ret);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  return _ftol2(fLerpRet);  // 返回 调 _ftol2
}



// ------------------------------------------------------------
// 0x4D5B30 sub_4D5B30
// 可行动判定（移动/操作输入门，返回 bool）：聚合 非死亡/特殊态（vt+840 != 9）、
// this+612 标志、vt+688 对象 +12/+20 两字段非 0、非冻结(1)/石化(7)（vt+776），
// 以及演出层状态（this+642 本地标志，否则查宿主 this+120 的 +112/+148 → 0/1）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4D5B30(uint32_t *this)  // 实现：以及演出层状态（this+642 本地标志，否则查宿主 this+120 的 +112/+148 → 0/1）
{
  int nCineState; // edi —— 演出层状态值（0/1 可行动）
  int pHostObj; // edi —— 宿主对象（this+120）
  bool bObjF12; // bl —— vt+688 对象 +12 非零
  bool bObjF20; // [esp+Dh] [ebp-3h] —— vt+688 对象 +20 非零
  char bCineStateOk; // [esp+Fh] [ebp-1h] —— 演出层状态为 0/1
  char bNotFrozPet; // [esp+Eh] [ebp-2h] —— 非冻结(1)且非石化(7)

  if ( *((uint8_t *)this + 642) != 0 )  // this+642〔bHitBoxSnap642〕
  {
    nCineState = *(this + 161);  // 读 nCineState = this+644（帧时刻覆盖值）
  }
  else
  {
    pHostObj = *(this + 30);  // 读 pHostObj = this+120（动画对象）
    if ( pHostObj == 0 )  // pHostObj=this+120 pAnimObj
    {
LABEL_9:
      bCineStateOk = 1;
      goto LABEL_10;
    }
    if ( *(uint32_t *)(pHostObj + 148) == -1 )  // pHostObj=this+120 pAnimObj
      sub_4938F0(*(this + 30));  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    nCineState = *(uint32_t *)(pHostObj + 112);  // nCineState=this+644 nFrameOverrideTime
  }
  if ( nCineState == 0 )  // nCineState=this+644 nFrameOverrideTime
    goto LABEL_9;
  bCineStateOk = 0;
  if ( nCineState == 1 )  // nCineState=this+644 nFrameOverrideTime
    goto LABEL_9;
LABEL_10:
  bObjF12 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 688))(this) + 12) != 0;  // 结果 = 虚调用 vt+688
  bObjF20 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 688))(this) + 20) != 0;  // 结果 = 虚调用 vt+688
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 1) != 0  // 虚调用 vt+776
    || (bNotFrozPet = 1, (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 7) != 0) )  // 虚调用 vt+776
  {
    bNotFrozPet = 0;
  }
  return *((uint8_t *)this + 612) != 0
      && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 9  // 虚调用 vt+840
      && bCineStateOk != 0
      && bObjF12
      && bObjF20
      && bNotFrozPet != 0;
}



// ------------------------------------------------------------
// 0x4D5C10 sub_4D5C10
// 可被施加控制判定（返回 bool）：this+6740 使能 && 非霸体（this+6552==0，
// ·0x4D5170 写入）&& 非冻结(1) && 非石化(7)。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4D5C10(uint8_t *this)  // 实现：·0x4D5170 写入）&& 非冻结(1) && 非石化(7)
{
  return *(this + 6740) != 0  // this+6740 【推断】落地/使能位
      && *(this + 6552) == 0  // this+6552 霸体字节
      && (*(uint8_t (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 776))(this, 1) == 0  // 调虚槽 +776：异常状态查询
      && (*(uint8_t (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 776))(this, 7) == 0;  // 调虚槽 +776：异常状态查询
}



// ------------------------------------------------------------
// 0x4D5C50 sub_4D5C50
// 观察者广播（vt+160 号回调）：sub_499790() 全局收点后，对 18 个观察者逐个调
// vt+160()，尾调 sub_53F8F0(this+6296)（与 0x4D4CE0 的 sub_53F7A0 同区收束）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5C50(uint32_t *this)  // 实现：vt+160()，尾调 sub_53F8F0(this+6296)（与 0x4D4CE0 的 sub_53F7A0 同区收束）
{
  uint32_t *pThis_651; // esi
  int i; // edi

  sub_499790();
  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )  // 循环：i 从 18 递减到 0
  {
    if ( *pThis_651 != 0 )
      (*(void (**)(void))(*(uint32_t *)*pThis_651 + 160))();  // 虚调用 vt+160
    ++pThis_651;
  }
  return sub_53F8F0(*(this + 1574));  // 返回 批量广播器 vt+52 槽（无参）
}



// ------------------------------------------------------------
// 0x4D5C90 sub_4D5C90
// 事件 6 回调（nullsub_1 分派表同族）：HP > 0 时新HP = HP(0,1) × 1.2 经 vt+732
// 写回 —— 回复 20%（与 0x4D5CF0 的 ×5/6 减量互为逆操作）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5C90(int *this, int nArg2)  // 实现：写回 —— 回复 20%（与 0x4D5CF0 的 ×5/6 减量互为逆操作）
{
  int result; // eax
  int pVtbl; // edi —— *this 虚表指针（尾调 vt+732 写回用）
  uint64_t nNewHp64; // rax —— HP×1.2（+20% 回复，截断取整）

  result = nullsub_1(nArg2);  // result = 调 nullsub_1
  if ( nArg2 == 6 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);  // 结果 = 虚调用 vt+736
    if ( result > 0 )
    {
      pVtbl = *this;
      nNewHp64 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 736))(this, 0, 1) * 1.2);  // 结果 = 虚调用 vt+736
      return (*(int (/*fastcall*/ **)(int *, uint32_t, uint32_t))(pVtbl + 732))(this, HIDWORD(nNewHp64), nNewHp64);  // 调虚槽 +732：CNMapObject__vmt2DC
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D5CF0 sub_4D5CF0
// 事件 6 回调（0x4D5C90 的对偶）：HP > 0 时新HP = max(HP × 0.83333331(=5/6), 1)
// 经 vt+732 写回 —— 减少 1/6（下限 1 防 0 血）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5CF0(void *this, int nArg2)  // 实现：经 vt+732 写回 —— 减少 1/6（下限 1 防 0 血）
{
  int result; // eax
  double pThis_2E0; // st7

  result = nullsub_1(nArg2);  // result = 调 nullsub_1
  if ( nArg2 == 6 )
  {
    result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 736))(this);  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
    if ( result > 0 )
    {
      if ( (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 736))(this) * 0.83333331 <= 1.0 )  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
        pThis_2E0 = 1.0;
      else
        pThis_2E0 = (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 736))(this) * 0.83333331;  // 调虚槽 +736：属性块首值（GetHP 族，此处索引）
      return (*(int (/*fastcall*/ **)(void *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 732))(  // 调虚槽 +732：CNMapObject__vmt2DC
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
// 事件驱动的属性修正回调（stdcall，pArg2 = 属性块）：事件 6 → +18 处浮点 ×1.2
// 写回；事件 18 → +260 与 +274 两处计数各 += dword_9A05C8 × *pArg2（单位标量，
// 运行期全局）。sub_41A5E0/sub_41A590 = 属性字段读/写器。
// ------------------------------------------------------------
int /*stdcall*/ sub_4D5D70(int nArg1, uint32_t *pArg2)  // 实现：运行期全局）。sub_41A5E0/sub_41A590 = 属性字段读/写器
{
  int result; // eax
  unsigned int pFld18; // esi —— 属性块 +18 字段址
  int nPad1; // edx —— sub_41A590 占位（寄存器残影）
  int nAdd260; // edi —— dword_9A05C8 × 单位标量（+260 路增量）
  int nCur260; // eax
  int nPad2; // edx
  int nAdd274; // edi —— 同上（+274 路增量）
  int nCur274; // eax
  int nPad3; // edx
  int nFld18; // [esp+10h] [ebp+Ch] —— +18 字段槽（以 float 位型读写）

  result = nArg1;
  if ( nArg1 == 6 )
  {
    pFld18 = (unsigned int)pArg2 + 18;
    *(float *)&nFld18 = COERCE_FLOAT(sub_41A5E0((unsigned int)pArg2 + 18)) * 1.2;  // crypt4byte 解密校验（·0x41A590 逆运算）
    return sub_41A590(pFld18, nPad1, nFld18);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
  else if ( nArg1 == 18 )
  {
    nAdd260 = dword_9A05C8 * *pArg2;
    nCur260 = sub_41A5E0((unsigned int)(pArg2 + 260));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590((unsigned int)(pArg2 + 260), nPad2, nAdd260 + nCur260);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    nAdd274 = dword_9A05C8 * *pArg2;
    nCur274 = sub_41A5E0((unsigned int)(pArg2 + 274));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    return sub_41A590((unsigned int)(pArg2 + 274), nPad3, nAdd274 + nCur274);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D5E00 sub_4D5E00
// 属性读取（浮点积）：this+116 与 this+130 两属性字段（sub_41A5E0 取值）相乘返回。
// 【推断】基础值 × 系数 类属性项。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4D5E00(void *this)  // 实现：(推断)基础值 × 系数 类属性项
{
  int pThis_74; // [esp+8h] [ebp-4h]

  pThis_74 = sub_41A5E0((unsigned int)this + 116);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)((double)pThis_74 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 130)));  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4D5E40 sub_4D5E40
// 属性读取（按 nArg2 选条目，步长 14 dword = 56 字节）：取 (this+56×nArg2+1136)
// 与 (+2032) 两字段相乘返回（0x4D5E00 的多槽版本）。【推断】技能等级条目属性。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4D5E40(char *this, int nArg2)  // 实现：与 (+2032) 两字段相乘返回（0x4D5E00 的多槽版本）。(推断)技能等级条目属性
{
  char *pSlotEntry; // esi —— 属性条目（56 字节步距）
  int nEntryVal; // [esp+10h] [ebp+8h] —— 条目 +284 属性

  pSlotEntry = this + 14 * nArg2;
  nEntryVal = sub_41A5E0((unsigned int)(pSlotEntry + 284));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)((double)nEntryVal * COERCE_FLOAT(sub_41A5E0((unsigned int)(pSlotEntry + 508))));  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4D5E80 sub_4D5E80 —— CNRDActiveStatus 构造（17 槽状态对象的实现类）
// 设 CNRDActiveStatus::vftable + 内嵌两个 nengine::IObject 子块（+60/+156）
// 各带 off_6C2B88 子表，随后 sub_496CE0（基类）+ sub_497840（本类初始化，
// 携带 Block=状态 id、a3=宿主）—— 研究 §10 "状态对象自身持有独立时钟（状态+60）"
// 与此处 +60 子块吻合；状态对象由 0x4D6030 懒创建。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D5E80(int this, void *Block, int nArg3)  // 实现：CNRDActiveStatus 构造（17 槽状态对象的实现类）
{
  *(uint32_t *)this = &CNRDActiveStatus::`vftable';  // 构造装配 vftable：CNRDActiveStatus
  *(uint8_t *)(this + 64) = 0;  // this+64〔apServerTabBtn(推断)〕等 2 字段
  *(uint32_t *)(this + 60) = &off_6C2B88;  // this+60〔nFadeValue60(推断)〕等 2 字段
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint8_t *)(this + 72) = 1;  // this+72〔nSnapshot72(推断)〕等 2 字段
  *(uint8_t *)(this + 74) = 0;  // this+74〔bResetB74(推断)〕等 2 字段
  *(uint8_t *)(this + 73) = 0;  // 写 this+73 = 0（基类名字缓冲 SSO 首字节）
  *(uint32_t *)(this + 84) = 0;  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  *(uint32_t *)(this + 76) = 0;  // this+76〔pBtnActionE〕
  *(uint8_t *)(this + 160) = 0;  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 156) = &off_6C2B88;  // this+156〔nAdd156(推断)〕
  *(uint32_t *)(this + 164) = 0;  // this+164〔fAdd164(推断)〕
  *(uint8_t *)(this + 168) = 1;  // this+168〔pAppendVec(推断)〕等 2 字段
  *(uint8_t *)(this + 170) = 0;  // 写 this+170 = 0（动画状态字节）
  *(uint8_t *)(this + 169) = 0;  // this+676〔nResetFlag676(推断)〕
  *(uint32_t *)(this + 180) = 0;  // this+180〔nRadius(推断)〕
  *(uint32_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  *(uint32_t *)(this + 172) = 0;  // this+172〔pAppendVecEnd(推断)〕等 2 字段
  sub_496CE0(this);  // 播放状态对象复位（+104=4、+104..120 连续 5 格 1065353216=1.
  sub_497840((int *)this, Block, nArg3);  // 异常状态→动画/粒子 装配总表
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4D5FA0 sub_4D5FA0
// CNRDActiveStatus 析构壳：先 0x4D5FD0（成员析构），pszArg2 & 1（free 标志位）
// 为真时 free(Block)。返回 Block。
// ------------------------------------------------------------
void */*thiscall*/ sub_4D5FA0(void *Block, char pszArg2)  // 实现：为真时 free(Block)。返回 Block
{
  sub_4D5FD0();  // 调 IObject 子块（+60/+156）复位，再调 sub_497500 基类初始化
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4D5FD0 sub_4D5FD0
// CNRDActiveStatus 基础构造（0x4D5E80 全量构造的前段）：挂 vftable，两个内嵌
// IObject 子块（+60/+156）复位，再调 sub_497500 基类初始化。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D5FD0(int this)  // 实现：IObject 子块（+60/+156）复位，再调 sub_497500 基类初始化
{
  *(uint32_t *)this = &CNRDActiveStatus::`vftable';  // 构造装配 vftable：CNRDActiveStatus
  sub_497500((char *)this);  // 5 组指针对释放（228 字节对象 + 虚析构）
  *(uint32_t *)(this + 156) = &nengine::IObject::`vftable';  // this+156〔nAdd156(推断)〕
  *(uint8_t *)(this + 160) = 0;  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 60) = &nengine::IObject::`vftable';  // this+60〔nFadeValue60(推断)〕等 2 字段
  *(uint8_t *)(this + 64) = 0;  // this+64〔apServerTabBtn(推断)〕等 2 字段
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
int /*thiscall*/ sub_4D6030(uint32_t *this, void *Block, int nArg3, int nArg4)  // 实现：状态施加入口（17 状态槽懒创建 + 转发）
{
  int result; // eax
  void *pMem; // eax
  int pNewStatus; // eax —— 新建状态对象（sub_4D5E80 构造失败时为 0）

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 724))(this);  // 结果 = 虚调用 vt+724
  if ( (uint8_t)result == 0 )
  {
    if ( Block == (void *)1 || Block == (void *)7 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);  // 结果 = 虚调用 vt+688
      if ( *(uint32_t *)(result + 12) == 0 )
        return result;
    }
    else if ( Block == (void *)8 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);  // 结果 = 虚调用 vt+688
      if ( *(uint32_t *)(result + 20) == 0 )
        return result;
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);  // 结果 = 虚调用 vt+840
      if ( result == 9 )
        return result;
    }
    result = *(this + (uint32_t)Block + 1557);
    if ( result == 0 )
    {
      if ( nArg3 == 0 )
        return result;
      pMem = operator new(0xD0u);  // 堆分配 208 字节对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        pNewStatus = sub_4D5E80((int)pMem, Block, (int)this);  // 结果 = CNRDActiveStatus 构造（17 槽状态对象的实现类）
      else
        pNewStatus = 0;
      *(this + (uint32_t)Block + 1557) = pNewStatus;
    }
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)*(this + (uint32_t)Block + 1557) + 4))(  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 699000/…
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
void /*thiscall*/ sub_4D6130(float *this)  // 实现：HP/MP 自然回复逐帧累加（小数累积器模式）
{
  int pClock; // edi —— 时钟对象（this+16）
  int pAttrCont; // edi —— vt+672(this,3) 属性容器（HP 路）
  long double fHpAcc; // st7 —— HP 回复小数累积器（this+1649）
  unsigned int nHpCurRet; // eax —— vt+684() 当前 HP
  int nHpAttr; // eax
  int pAttrCont2; // edi —— 属性容器（MP 路）
  long double fMpAcc; // st7 —— MP 回复小数累积器（this+1648）
  int nMpCurRet; // eax —— vt+684() 当前 MP（+14 = MP 侧偏移）
  int nMpAttr; // eax
  float fStat774; // [esp+8h] [ebp-Ch]
  int nHpInt; // [esp+8h] [ebp-Ch] —— 本帧落地 HP 整数部分
  int nStat788; // [esp+8h] [ebp-Ch]
  int nMpInt; // [esp+8h] [ebp-Ch] —— 本帧落地 MP 整数部分
  int nStat760; // [esp+Ch] [ebp-8h]
  int nDtRaw; // [esp+10h] [ebp-4h] —— 本帧历时 = clock_now − this+1647（上次时钟）
  float fDt; // [esp+10h] [ebp-4h]

  pClock = (int)(this + 16);  // this+64〔apServerTabBtn(推断)〕
  nDtRaw = sub_699000((int)(this + 16)) - *((uint32_t *)this + 1647);  // 【clock_now(clk)】
  *((uint32_t *)this + 1647) = sub_699000(pClock);  // clock_now(clk)
  pAttrCont = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  nStat760 = sub_41A5E0(pAttrCont + 760);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  fDt = (float)nDtRaw;
  fStat774 = COERCE_FLOAT(sub_41A5E0(pAttrCont + 774));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  fHpAcc = sub_433F60((int)this, 2) * ((double)(int)(uint64_t)((double)nStat760 * fStat774) * fDt * 0.0099999998 * 0.001)  // 调 PVP 平衡系数路由（研究第 17/27 轮）
     + *(this + 1649);  // this+6596〔uRenc6596〕
  *(this + 1649) = fHpAcc;  // this+6596〔uRenc6596〕
  if ( fabs(fHpAcc) >= 1.0 )  // 调 浮点绝对值
  {
    nHpInt = (uint64_t)fHpAcc;
    nHpCurRet = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 684))(this);  // 调虚槽 +684：取攻击上下文
    nHpAttr = sub_41A5E0(nHpCurRet);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    (*(void (/*thiscall*/ **)(float *, int, uint32_t, uint32_t))(*(uint32_t *)this + 728))(this, nHpInt + nHpAttr, 0, 0);  // 调虚槽 +728：HP setter/扣血
    *(this + 1649) = *(this + 1649) - (double)nHpInt;  // this+6596〔uRenc6596〕
  }
  pAttrCont2 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  nStat788 = sub_41A5E0(pAttrCont2 + 788);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  fMpAcc = (double)(int)(uint64_t)((double)nStat788 * COERCE_FLOAT(sub_41A5E0(pAttrCont2 + 802))) * fDt * 0.050000001 * 0.001  // 0.05 = MP 回复系数（HP 路 0.01 的 5 倍）
     + *(this + 1648);  // this+6592〔uRenc6592〕
  *(this + 1648) = fMpAcc;  // this+6592〔uRenc6592〕
  if ( fabs(fMpAcc) >= 1.0 )  // 调 浮点绝对值
  {
    nMpInt = (uint64_t)fMpAcc;
    nMpCurRet = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 684))(this);  // 调虚槽 +684：取攻击上下文
    nMpAttr = sub_41A5E0(nMpCurRet + 14);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    (*(void (/*thiscall*/ **)(float *, int, uint32_t))(*(uint32_t *)this + 744))(this, nMpInt + nMpAttr, 0);  // 调虚槽 +744：物件破坏三连（表现/掉落/广播）
    *(this + 1648) = *(this + 1648) - (double)nMpInt;  // this+6592〔uRenc6592〕
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
uint64_t /*thiscall*/ sub_4D62D0(void *this, int nArg2, int nArg3)  // 实现：物理/魔法攻击力基值（研究 §5.1/§12 的攻击力项）
{
  int pThis_2A0; // esi
  double fPctBonus; // st7
  float fStat1026; // [esp+8h] [ebp-8h]
  int nStat1068; // [esp+8h] [ebp-8h]
  int nStat1012; // [esp+Ch] [ebp-4h]
  float fStat1082; // [esp+Ch] [ebp-4h]
  float fStat74; // [esp+18h] [ebp+8h]
  float fStat130; // [esp+18h] [ebp+8h]
  float fResult; // [esp+1Ch] [ebp+Ch]
  int nStat60; // [esp+1Ch] [ebp+Ch]
  float fPhysBase; // [esp+1Ch] [ebp+Ch]
  int nStat116; // [esp+1Ch] [ebp+Ch]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, nArg3);  // 调虚槽 +672：自身 HP
  fResult = 0.0;
  if ( nArg2 == 0 )
  {
    nStat1012 = sub_41A5E0(pThis_2A0 + 1012);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    fStat1026 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 1026));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    nStat60 = sub_41A5E0(pThis_2A0 + 60);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    fStat74 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 74));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    fPhysBase = (double)(int)(uint64_t)((double)nStat1012 * fStat1026)  // ★ 物理/魔法攻击力基值（研究 §5.1/§12 的「攻击力「项）
        * (sub_433F60(this, 3) * (double)(int)(uint64_t)((double)nStat60 * fStat74) / flt_9A05F4 + 1.0);  // 调 PVP 平衡系数路由（研究第 17/27 轮）
    fPctBonus = (double)sub_41A5E0(pThis_2A0 + 1306);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
LABEL_5:
    fResult = (fPctBonus * 0.0099999998 + 1.0) * fPhysBase;
    return (uint64_t)(sub_433F60(this, 0) * fResult);  // 调 PVP 平衡系数路由（研究第 17/27 轮）
  }
  if ( nArg2 == 1 )
  {
    nStat1068 = sub_41A5E0(pThis_2A0 + 1068);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    fStat1082 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 1082));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    nStat116 = sub_41A5E0(pThis_2A0 + 116);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    fStat130 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 130));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    fPhysBase = (double)(int)(uint64_t)((double)nStat1068 * fStat1082)
        * (sub_433F60(this, 5) * (double)(int)(uint64_t)((double)nStat116 * fStat130) / flt_9A060C + 1.0);  // 调 PVP 平衡系数路由（研究第 17/27 轮）
    fPctBonus = (double)sub_41A5E0(pThis_2A0 + 1334);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    goto LABEL_5;
  }
  return (uint64_t)(sub_433F60(this, 0) * fResult);  // 调 PVP 平衡系数路由（研究第 17/27 轮）
}



// ------------------------------------------------------------
// 0x4D6450 sub_4D6450 —— ★ 减伤率与抗性取值（研究 §5.1 的"防御×(1−减伤)"项）
// 输出两路：*a2 = 有效伤害比（v11/v14 归一）、*a3 = 抗性项 v16。
// 物理(0)/魔法(1) 取属性块 (+1040/+1054，+1096/+1110) × (1 + +1320/+1348 × 0.01)；
// 抗性来自 +1152/+1194 × 0.01；场景 4/6（PVP/战场）抗性 ×2；分母下限 1.0 防除零。
// 与研究 §16"PVP/战场走查表"一致：本函数是 PVE/PVP 分离的另一处体现。
// ------------------------------------------------------------
float */*thiscall*/ sub_4D6450(void *this, float *pArg2, float *pArg3, int nArg4, int nArg5, int nArg6)  // 实现：减伤率与抗性取值（研究 §5.1 的防御×(1−减伤)项）
{
  int pAttrCont; // edi —— vt+672(this,nArg6) 属性容器（+1040/+1054/+1320 族所在）
  double dRateMul; // st7 —— 1 + 率×0.01（+1320/+1348）
  double nDefProduct; // st6 —— 攻防积（int 截断）
  int pResistFld; // ecx —— 抗性字段（+1152/+1194）
  double fDmgBase; // st7 —— 防御折减后的伤害基项
  int nSceneId; // eax —— dword_8F7A24+12 场景 id（4=PVP 6=战场）
  double fResistWt; // st6
  double fDenom; // st6 —— 分母（下限 1.0 防除零）
  float fResist; // [esp+8h] [ebp-8h] —— 抗性项（×0.01 后），输出 *pArg3
  int nDefAttrA; // [esp+8h] [ebp-8h] —— 防御属性 A（物理 +1040）
  int nDefAttrA2; // [esp+8h] [ebp-8h] —— 防御属性 A（魔法 +1096）
  float fDefTerm; // [esp+Ch] [ebp-4h] —— dRateMul × nDefProduct
  float fDefAttrB; // [esp+Ch] [ebp-4h] —— 防御属性 B（物理 +1054）
  float fDefAttrB2; // [esp+Ch] [ebp-4h] —— 防御属性 B（魔法 +1110）
  float fResistK; // [esp+28h] [ebp+18h] —— 单点抗性权重常量（flt_9A05FC/9A0614，PVP ×2）

  pAttrCont = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, nArg6);  // 调虚槽 +672：自身 HP
  fDefTerm = 0.0;
  fResist = 0.0;
  fResistK = 0.0;
  if ( nArg5 == 0 )
  {
    nDefAttrA = sub_41A5E0(pAttrCont + 1040);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    fDefAttrB = COERCE_FLOAT(sub_41A5E0(pAttrCont + 1054));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    dRateMul = (double)sub_41A5E0(pAttrCont + 1320) * 0.0099999998 + 1.0;  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    nDefProduct = (double)(int)(uint64_t)((double)nDefAttrA * fDefAttrB);
    fResistK = flt_9A05FC;
    pResistFld = pAttrCont + 1152;
LABEL_5:
    fDefTerm = dRateMul * nDefProduct;
    fResist = COERCE_FLOAT(sub_41A5E0(pResistFld)) * 0.0099999998;  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    goto LABEL_6;
  }
  if ( nArg5 == 1 )
  {
    nDefAttrA2 = sub_41A5E0(pAttrCont + 1096);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    fDefAttrB2 = COERCE_FLOAT(sub_41A5E0(pAttrCont + 1110));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    dRateMul = (double)sub_41A5E0(pAttrCont + 1348) * 0.0099999998 + 1.0;  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    nDefProduct = (double)(int)(uint64_t)((double)nDefAttrA2 * fDefAttrB2);
    fResistK = flt_9A0614;
    pResistFld = pAttrCont + 1194;
    goto LABEL_5;
  }
LABEL_6:
  fDmgBase = sub_433F60(this, 1) * fDefTerm;  // 调 PVP 平衡系数路由（研究第 17/27 轮）
  nSceneId = *(uint32_t *)(dword_8F7A24 + 12);  // 全局 dword_8F7A24 = 登录/选区管理器
  if ( nSceneId == 4 || nSceneId == 6 )  // 若 nSceneId == 4 与/或 nSceneId == 6
    fResistWt = fResistK + fResistK;
  else
    fResistWt = fResistK;
  fDenom = fResistWt * (double)nArg4 + fDmgBase;
  if ( fDenom <= 1.0 )
    fDenom = 1.0;
  *pArg2 = fDmgBase / fDenom;
  *pArg3 = fResist;
  return pArg3;
}



// ------------------------------------------------------------
// 0x4D65C0 sub_4D65C0 —— 攻速/施放速度取值（带技能对象修正分支）
// this+1625 != 0（存在技能对象）时多减一项 vt+176 技能容器 (+686 × 0.001)；
// 属性对 = (+844, +858) —— 研究 §12 的 [attack speed] a1+380/384 属另一种聚合路径
// 【待验证：+844/+858 是速度还是其它乘率，需 0x5A0 数据对象布局对读】。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4D65C0(uint32_t **this, int nArg2)  // 实现：攻速/施放速度取值（带技能对象修正分支）
{
  int pSkillAttr; // eax —— vt+168(this,nArg2) 属性容器（持技能时）
  int pSkillAttr2; // eax
  int pSkillObjRet; // eax —— 技能对象(this+1625)->vt+176() 返回容器（扣 +686）
  int pAttrCont; // esi —— vt+168(this,nArg2) 属性容器（无技能分支）
  int nSpdAttr1; // [esp+8h] [ebp-8h] —— 速度属性 1（+844）
  float fSpdAttr2; // [esp+Ch] [ebp-4h] —— 速度属性 2（+858）【推断：属性对相乘】
  int nSpdAttr1b; // [esp+18h] [ebp+8h]

  if ( nArg2 != 0 && *(this + 1625) != nullptr )  // 判定 “+6500 当前武器/弹药物件id”
  {
    pSkillAttr = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[168])(this, nArg2);
    nSpdAttr1 = sub_41A5E0(pSkillAttr + 844);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    pSkillAttr2 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[168])(this, nArg2);
    fSpdAttr2 = COERCE_FLOAT(sub_41A5E0(pSkillAttr2 + 858));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    pSkillObjRet = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1625) + 176))(*(this + 1625));  // this+6500〔nWeaponItemId〕
    return (uint64_t)((fSpdAttr2 - (double)sub_41A5E0(pSkillObjRet + 686) * 0.001) * (double)nSpdAttr1);  // crypt4byte 解密校验（·0x41A590 逆运算）
  }
  else
  {
    pAttrCont = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[168])(this, nArg2);
    nSpdAttr1b = sub_41A5E0(pAttrCont + 844);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    return (uint64_t)((double)nSpdAttr1b * COERCE_FLOAT(sub_41A5E0(pAttrCont + 858)));  // crypt4byte 解密校验（·0x41A590 逆运算）
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
double /*thiscall*/ sub_4D6690(void *this, int nArg2)  // 实现：硬直强度 vt+704（研究 第 27 轮定案：sub_4D6690）
{
  int pAttrCont; // edi —— vt+672(this,3) 属性容器
  int nStuckBase; // [esp+Ch] [ebp-4h] —— [stuck resistance] 基值（+466）
  float fStuckRet; // [esp+Ch] [ebp-4h] —— 扣除项 = nStuckBase × (+690) × 0.1

  pAttrCont = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  nStuckBase = sub_41A5E0(pAttrCont + 466);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  fStuckRet = (double)(int)(uint64_t)((double)nStuckBase * COERCE_FLOAT(sub_41A5E0(pAttrCont + 690))) * 0.1;  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  if ( (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 40))(this, 529) == 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0 )  // 调虚槽 +348：取坐标对象
  {
    return fStuckRet;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 368))(nArg2) != 0 )  // 调虚槽 +368：位移预测写入
    return (double)*(int *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1032))(this) + 280) + fStuckRet;  // 调虚槽 +1032
  return (double)*(int *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1032))(this) + 284) + fStuckRet;  // 调虚槽 +1032
}


// ------------------------------------------------------------
// 0x4D6750 sub_4D6750 —— 状态施加"概率/抗性"掷（rand%10000 < 率×100）
// 结构 = 研究 §5.1 的判定掷同构：nResistVal 由 sub_41A5E0（防篡读）取；受方条件 17（有血）
// 时从属性对 (+284/+508，14 字节步距) 扣抵抗；a4 非空时用 sub_4D33A0（LCG）替代 rand。
// 调用点：状态附加（命中携带异常状态，研究 §3 attackinfo+24..48）与霸体/受击门。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4D6750(void *this, int nArg2, float fArg3, unsigned int *pDwArg4)  // 实现：状态施加概率/抗性掷（rand%10000 < 率×100）
{
  int nResistIdx; // esi —— 状态属性类别（sub_496F80 取，16 = 无对应类别）
  int pResistEntry; // esi —— 属性容器 + 14×nResistIdx 条目
  int nRand; // eax
  int nResistVal; // [esp+14h] [ebp+8h] —— 抵抗值（+284）

  nResistIdx = sub_496F80(nArg2);  // 结果 = 状态号映射表（12 直通、15→14、16→15，其余→16）
  if ( nResistIdx != 16 )
  {
    pResistEntry = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3) + 14 * nResistIdx;  // 调虚槽 +672：自身 HP
    nResistVal = sub_41A5E0(pResistEntry + 284);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    fArg3 = (100.0 - (double)(int)(uint64_t)((double)nResistVal * COERCE_FLOAT(sub_41A5E0(pResistEntry + 508)))) * fArg3 * 0.0099999998;  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  }
  if ( pDwArg4 != nullptr )  // 若 pDwArg4 有效（非空）
  {
    nRand = sub_4D33A0(pDwArg4);  // 调 掷 0..9999
  }
  else
  {
    sub_432FA0();  // srand 播种
    nRand = rand();  // nRand = 调 rand
  }
  return fArg3 * 100.0 > (double)(nRand % 10000);
}



// ------------------------------------------------------------
// 0x4D6810 sub_4D6810 —— ★ CNChangeHp 构造（研究 §2⑦ 的"延滞伤"分支）
// 命中主处理器 0x4D71B0 判 attackinfo+124 == 2（burn/延滞伤）时 new 本对象
// （伤害值, 1000ms, …）—— 研究 §2⑦ 已定案"new CNChangeHp(伤害, 1000ms, …)"；
// 本体 = sub_4B1030 基类 + CNChangeHp::vftable + sub_5FD600/5FD630 参数装载。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4D6810(uint8_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：CNChangeHp 构造（研究 §2⑦ 的延滞伤分支）
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *(uint32_t *)this = &CNChangeHp::`vftable';  // 构造装配 vftable：CNChangeHp
  sub_5FD600(this);
  sub_5FD630(this, nArg2, nArg3, nArg4, nArg5);
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4D6880 sub_4D6880 —— CNChangeHp 析构壳
// 先调 0x4D68B0（二段析构复位），pszArg2 位 0 置位时 free 块本身（delete 对象，
// 比特 1 = 是否堆分配标志）。返回块指针。
// ------------------------------------------------------------
void */*thiscall*/ sub_4D6880(void *Block, char pszArg2)  // CNChangeHp 析构壳
{
  sub_4D68B0();  // 调 最后内嵌 IObject 子块（+8）复位 + +12 字节清零
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4D68B0 sub_4D68B0
// CNChangeHp / IRDAppendage 二段构造壳（0x4D6810 CNChangeHp 构造的收尾件）：
// 先挂 CNChangeHp::vftable 走 sub_5FDC90，再换挂 IRDAppendage::vftable 走
// sub_5F6640，最后内嵌 IObject 子块（+8）复位 + +12 字节清零。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D68B0(uint32_t *this)  // 实现：sub_5F6640，最后内嵌 IObject 子块（+8）复位 + +12 字节清零
{
  int result; // eax

  *this = &CNChangeHp::`vftable';  // 构造装配 vftable：CNChangeHp
  sub_5FDC90();
  *this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // 调 基类析构
  *(this + 2) = &nengine::IObject::`vftable';  // 写 this+8 = &nengine::IObject::`vftable’（技能槽记录首字）
  *((uint8_t *)this + 12) = 0;  // 写 this+12 = 0（技能槽记录次字）
  return result;
}



// ------------------------------------------------------------
// 0x4D6910 sub_4D6910 —— ★ 状态施加通用壳（a2=状态id, a3=强度, a4/a5=参数, a6=强制位）
// 门：a6 != 0 或 vt+308（本地玩家对象）；a2 != 17（17 = 无状态哨兵，研究 §10 枚举
// "17=none"）；a4 != 0（参数非零）→ sub_4D6750(状态id, 强度, 0) 概率掷通过后
// 调 vt+764(this, 状态id, a4, a5, a6) —— 与 0x4D4AE0（三连调 vt+764 施加异常状态）
// 同一转发目标。调用点：0x4DCC60（技能/被动施加，带 1943==3 时强度×0.1 的 PVP 修正）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D6910(void *this, int nArg2, float fArg3, int nArg4, int nArg5, int nArg6)  // 实现：状态施加通用壳（a2=状态id, a3=强度, a4/a5=参数, a6=强制位）
{
  char result; // al

  result = nArg6;
  if ( ((uint8_t)nArg6 != 0 || (result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this)) != 0)  // 调虚槽 +308：是否本地玩家
    && nArg2 != 17
    && nArg4 != 0 )
  {
    result = sub_4D6750(nArg2, fArg3, 0);  // 结果 = 状态施加”概率/抗性”掷（rand%10000 < 率×100）
    if ( result != 0 )  // 若结果非 0（成功）
      return (*(int (/*thiscall*/ **)(void *, int, int, int, int))(*(uint32_t *)this + 764))(this, nArg2, nArg4, nArg5, nArg6);  // 调虚槽 +764
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
char /*thiscall*/ sub_4D6970(int this)  // 实现：角色出生/复活初始化（尾调 0x4E73B0 复活重置）
{
  int nClockNow; // eax —— clock_now() 返回值（记入 +6588）
  int pVtbl1; // edx —— *this 虚表（vt+848 清冻结用）
  int pszSoundBuf; // eax —— this+6716 SSO 字符串数据指针（出生音效名）
  int pVtbl2; // eax —— *this 虚表（vt+472 复位用）
  int pHostObj; // ecx —— this+112 宿主/管理器指针（sub_49FD20 参数）

  sub_4E73B0((int *)this);  // 出生/复活重置（研究 P35 第 31 轮定案）
  *(uint32_t *)(this + 6664) = *(uint32_t *)(this + 324) != 0 ? 0 : 0xFFFFFA24;  // this+6664〔uUI6664〕
  sub_6569D0(this + 6540);  // 调 清 +28
  nClockNow = sub_699000(this + 64);  // 【clock_now(clk)】
  pVtbl1 = *(uint32_t *)this;
  *(uint32_t *)(this + 6588) = nClockNow;  // this+6588〔nRencT0_6588〕
  *(uint32_t *)(this + 6596) = 0;  // this+6596〔uRenc6596〕
  *(uint32_t *)(this + 6592) = 0;  // this+6592〔uRenc6592〕
  (*(void (/*thiscall*/ **)(int, uint32_t))(pVtbl1 + 848))(this, 0);  // 调虚槽 +848：冻结标志写入（+6744，0→-1 / 非0→0）
  if ( *(uint32_t *)(this + 6736) < 0x10u )  // this+6736〔nBirthSndCap〕
    pszSoundBuf = this + 6716;  // this+6716〔szBirthSnd6716〕
  else
    pszSoundBuf = *(uint32_t *)(this + 6716);  // this+6716〔szBirthSnd6716〕
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int))(*(uint32_t *)this + 212))(this, pszSoundBuf, 0, 0, 5000);  // 调虚槽 +212：播放音效 TAG(→50 声道)
  pVtbl2 = *(uint32_t *)this;
  *(uint32_t *)(this + 6672) = 0;  // this+6672〔uUI6672〕
  *(uint8_t *)(this + 6680) = 0;  // this+6680〔bUI6680〕
  *(uint8_t *)(this + 6682) = 0;  // this+6682〔bUI6682〕
  *(uint32_t *)(this + 6684) = 0;  // this+6684〔uUI6684〕
  *(uint32_t *)(this + 6688) = -1;  // this+6688〔uUI6688〕
  *(uint32_t *)(this + 6692) = -1;  // this+6692〔uUI6692〕
  (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(pVtbl2 + 472))(this, 0, 0, 1, 1);  // 虚函数调用 槽+472：主状态机（874 行）：CONDITION_STUN/DOWN_HEAV
  if ( *(uint32_t *)(this + 6172) == 0 || *(uint32_t *)(this + 6176) == 0 || *(uint32_t *)(this + 6180) == 0 )  // this+6172〔pAtkCtxA6172〕
    *(uint8_t *)(this + 6740) = 0;  // this+6740〔bFreeze6740〕
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 932))(this);  // 调虚槽 +932：场景 15/16 判定 → +7088 = 0 / 7
  pHostObj = *(uint32_t *)(this + 112);  // 读 pHostObj = this+112（宿主组件）
  *(uint8_t *)(this + 7105) = 0;  // this+7105〔bSet7105〕
  *(uint32_t *)(this + 7112) = 0;  // this+7112〔uSet7112〕
  *(uint32_t *)(this + 7108) = -1;  // this+7108〔uSet7108〕
  return sub_49FD20(pHostObj);  // +200 状态位（sub_698F90 复位）
}



// ------------------------------------------------------------
// 0x4D6A80 sub_4D6A80 —— ★ 多命中盒碰撞测试 vt+480（研究 §1.2/§11 定案）
// 主盒：sub_4E62B0(this, this+120 动画对象, 目标, 目标 vt+200, a3) —— 研究 P29 的
//   "攻击盒=动画+116/受击盒=动画+132，24B/盒"族（会话 3 定案的 0x4E62B0 调用方）。
// 附加盒：动画对象 +204 双向链表（研究 §1.2 "主盒 + this+120+204 附加盒链表逐盒
//   sub_4E62B0"）—— 逐节点取 v9[3] 作盒对象再测。
// 任一命中即返回 1。调用者 = 本地扫掠 sub_4E82B0（vt+476，研究 §1.2/§11 第 11 轮）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D6A80(uint32_t *this, int nArg2, int nArg3)  // 实现：多命中盒碰撞测试 vt+480（研究 §1.2/§11 定案）
{
  int nTargetBox; // eax
  int pAnim; // eax
  uint32_t *pListHead; // eax
  uint32_t *pNode; // edi
  int nTargetBox2; // eax
  int pAnimSave; // [esp+10h] [ebp+8h]

  nTargetBox = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 200))(nArg2);  // 调虚槽 +200：取动画对象
  if ( (uint8_t)sub_4E62B0(this, *(this + 30), nArg2, nTargetBox, nArg3) != 0 )  // 【攻击盒 vs 受击盒碰撞（研究 P29 盒模型，会话 3 交叉引用）】
    return 1;  // 返回 1(成功)
  pAnim = *(this + 30);  // 读 pAnim = this+120（动画对象）
  pAnimSave = pAnim;  // pAnim=this+120 pAnimObj
  if ( pAnim == 0 )  // pAnim=this+120 pAnimObj
    return 0;
  pListHead = *(uint32_t **)(pAnim + 204);  // pAnim=this+120 pAnimObj
  pNode = (uint32_t *)*pListHead;
  if ( (uint32_t *)*pListHead == pListHead )
    return 0;
  while ( 1 )  // 无限循环
  {
    nTargetBox2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 200))(nArg2);  // 调虚槽 +200：取动画对象
    if ( (uint8_t)sub_4E62B0(this, pNode[3], nArg2, nTargetBox2, nArg3) != 0 )  // 【攻击盒 vs 受击盒碰撞（研究 P29 盒模型，会话 3 交叉引用）】
      break;
    pNode = (uint32_t *)*pNode;
    if ( pNode == *(uint32_t **)(pAnimSave + 204) )
      return 0;
  }
  return 1;  // 返回 1(成功)
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
int /*thiscall*/ sub_4D6B10(uint32_t *this, int nArg2)  // 实现：观察者/状态的对象绑定与解绑（a2 = 0/1/2）
{
  int result; // eax
  uint32_t *pThis_651; // edi
  unsigned int k; // edi
  int pVecBegin; // ecx
  uint32_t *pThis_615; // edi
  int nMaxHp; // edi
  int pVt0; // edi
  int nHpCur; // eax
  int nMaxMp; // edi
  int pVt1; // edi
  int nMpCur; // eax
  int j; // [esp+14h] [ebp+8h]
  int i; // [esp+14h] [ebp+8h]

  result = nArg2;
  if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 )
    {
      sub_4A2480(this + 510);  // 【怪物属性块大拷贝（vmt29C）】
      pThis_615 = this + 1557;
      for ( i = 17; i != 0; --i )  // 循环：i 从 17 递减到 0
      {
        if ( *pThis_615 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)*pThis_615 + 24))() != 0 )  // 虚调用 vt+24
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t *))(*(uint32_t *)*pThis_615 + 48))(*pThis_615, this + 851);  // 虚调用 vt+48
        ++pThis_615;
      }
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 676))(this, 2);  // 虚调用 vt+676
    }
    else if ( nArg2 == 2 )
    {
      sub_4A2480(this + 851);  // 【怪物属性块大拷贝（vmt29C）】
      sub_53F820(this + 1192);  // 调 批量广播器 vt+12 槽
      nMaxHp = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this);  // 结果 = 虚调用 vt+740
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) > nMaxHp )  // 虚调用 vt+736
      {
        pVt0 = *this;
        nHpCur = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 736))(this, 0, 1);  // 结果 = 虚调用 vt+736
        (*(void (/*thiscall*/ **)(uint32_t *, int))(pVt0 + 732))(this, nHpCur);  // 调虚槽 +732：CNMapObject__vmt2DC
      }
      nMaxMp = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 756))(this);  // 结果 = 虚调用 vt+756
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 752))(this);  // 结果 = 虚调用 vt+752
      if ( result > nMaxMp )
      {
        pVt1 = *this;
        nMpCur = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 752))(this, 1);  // 结果 = 虚调用 vt+752
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(pVt1 + 748))(this, nMpCur);  // 调虚槽 +748：[RTTI: IRDActiveObject__vmt2EC · 槽位 IRDActiveObj…
      }
    }
  }
  else
  {
    sub_4A2480(this + 169);  // 【怪物属性块大拷贝（vmt29C）】
    pThis_651 = this + 1617;
    for ( j = 18; j != 0; --j )  // 循环：j 从 18 递减到 0
    {
      if ( *pThis_651 != 0 )
        (*(void (/*stdcall*/ **)(uint32_t *))(*(uint32_t *)*pThis_651 + 132))(this + 510);  // 虚调用 vt+132
      ++pThis_651;
    }
    for ( k = 0; ; ++k )
    {
      pVecBegin = *(this + 83);  // this+332〔bReservedConn〕
      if ( pVecBegin == 0 || k >= (*(this + 84) - pVecBegin) >> 2 )  // this+84 插值起点 X
        break;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t *))(*this + 836))(this, *(uint32_t *)(pVecBegin + 4 * k), this + 510);  // 虚调用 vt+836
    }
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 676))(this, 1);  // 虚调用 vt+676
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
void /*thiscall*/ sub_4D6CA0(uint32_t *this)  // 实现：50% 预表现门（研究 §2① / §8 定案）
{
  int fld_e1769; // ecx
  unsigned int i; // edi
  int fld_e17692; // ecx

  fld_e1769 = *(this + 1769);
  if ( fld_e1769 != 0
    && (*(this + 1770) - fld_e1769) >> 2 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 虚调用 vt+308
    && rand() % 10 >= 5 )  // 调 取伪随机数
  {
    for ( i = 0; ; ++i )
    {
      fld_e17692 = *(this + 1769);
      if ( fld_e17692 == 0 || i >= (*(this + 1770) - fld_e17692) >> 2 )
        break;
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(fld_e17692 + 4 * i) + 60))(*(uint32_t *)(fld_e17692 + 4 * i));  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行…
      sub_49FFC0(1, 0);  // 播放尾帧处理（+48/+52/+40 → sub_49FA20 收尾）
    }
  }
}



// ------------------------------------------------------------
// 0x4D6D20 sub_4D6D20
// ·0x4D6CA0 容器（this+7076 起的 vector）删除成员：遍历指针数组找到值==nArg2 的项，
// memmove 后续项前移一格、end-=4。与 0x4D6CA0（50% 门触发 vt+60）成对管理同一容器。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D6D20(uint32_t *this, int nArg2)  // 实现：memmove 后续项前移一格、end-=4。与 0x4D6CA0（50% 门触发 vt+60）成对管理同一容器
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
        (const void *)(*(this + 1769) + 4 * i + 4),  // 虚调用 vt+4
        4 * ((int)(*(this + 1770) - (*(this + 1769) + 4 * i + 4)) >> 2));  // 虚调用 vt+4
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
  int nSlotId; // ebx
  uint32_t *pThis_615; // edi

  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )  // 循环：i 从 18 递减到 0
  {
    if ( *pThis_651 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, int, int, int, int *))(*(uint32_t *)*pThis_651 + 136))(  // 虚调用 vt+136
        *pThis_651,
        uArg2,
        nArg3,
        nArg4,
        1,
        this + 97);  // this+97〔bFlag97〕
    ++pThis_651;
  }
  nSlotId = 0;
  pThis_615 = this + 1557;
  do
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 776))(this, nSlotId) != 0 )  // 虚调用 vt+776
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, int, int))(*(uint32_t *)*pThis_615 + 72))(*pThis_615, uArg2, nArg3, nArg4);  // 虚调用 vt+72
    ++nSlotId;
    ++pThis_615;
  }
  while ( nSlotId < 17 );
  sub_4D6CA0(this);  // 50% 预表现门（研究 §2① / §8 定案）
  if ( (uint8_t)nArg4 != 0 )
    (*(void (/*thiscall*/ **)(int *, int))(*this + 548))(this, nArg3);  // 虚调用 vt+548
  return sub_4E4710(this, uArg2, nArg3, nArg4);  // 【攻方表现载荷（ 双向卡肉，研究 §8 全文定案）】
}



// ------------------------------------------------------------
// 0x4D6E40 sub_4D6E40
// 对象移除/退场处理（0x4D6B10 绑定的对偶）：① sub_4E7480(nArg2) 预清理；
// ② nArg2 满足条件 33（【推断】召唤物/车辆）时从 0x4D6CA0 容器（0x4D6D20）摘除；
// ③ 17 状态槽中"归属==nArg2"的激活态调 vt+16(0) 解除；
// ④ nArg2 == 自身时：vt+216 依次清 0/1/2/4/5/6/7/8 号挂接，并处理 dword_8F8528
//    的队伍/队友引用回退（+856 标志、+736 引用清零或 sub_4684F0）。
// 尾调 sub_53F8A0(nArg2)。0x4D6CA0 注释的 50% 预表现容器成员即条件 33 对象。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D6E40(uint32_t *this, int nArg2)  // 实现：尾调 sub_53F8A0(nArg2)。0x4D6CA0 注释的 50% 预表现容器成员即条件 33 对象
{
  int pObj; // ebx
  uint32_t *pThis_615; // edi
  uint8_t *pPartyObj; // eax
  int pPartyObj2; // ecx
  int i; // [esp+8h] [ebp-4h]

  pObj = nArg2;
  sub_4E7480(nArg2);  // 目标移除联动（命中列表清除 + 双向链表更新）
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 33) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    sub_4D6D20(this, nArg2);  // 调 memmove 后续项前移一格、end-=4。与 0x4D6CA0（50% 门触发 vt+60）成对管理同一容器
  pThis_615 = this + 1557;
  for ( i = 17; i != 0; --i )  // 循环：i 从 17 递减到 0
  {
    if ( *pThis_615 != 0
      && (*(uint8_t (**)(void))(*(uint32_t *)*pThis_615 + 24))() != 0  // 虚调用 vt+24
      && (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_615 + 20))(*pThis_615) == nArg2 )  // 虚调用 vt+20
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*pThis_615 + 16))(*pThis_615, 0);  // 虚调用 vt+16
    }
    ++pThis_615;
  }
  if ( (uint32_t *)nArg2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);  // 虚调用 vt+216
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 1);  // 虚调用 vt+216
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 2);  // 虚调用 vt+216
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 4);  // 虚调用 vt+216
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 5);  // 虚调用 vt+216
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 6);  // 虚调用 vt+216
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 7);  // 虚调用 vt+216
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 8);  // 虚调用 vt+216
    if ( *(uint32_t **)(*((uint32_t *)dword_8F8528 + 4) + 736) == this )  // 全局 dword_8F8528 = 消息/弹窗管理器
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) == 0 )  // 虚调用 vt+736
      {
        pPartyObj = *((uint8_t **)dword_8F8528 + 4);  // 全局 dword_8F8528 = 消息/弹窗管理器
        if ( pPartyObj[856] != 1 )
        {
          pPartyObj[856] = 1;
          pPartyObj[873] = 0;
          pPartyObj[874] = 0;
          sub_698F90((int)(pPartyObj + 860), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        }
      }
      pPartyObj2 = *((uint32_t *)dword_8F8528 + 4);  // 全局 dword_8F8528 = 消息/弹窗管理器
      if ( *(uint8_t *)(pPartyObj2 + 856) != 0 )
        *(uint32_t *)(pPartyObj2 + 736) = 0;
      else
        sub_4684F0(pPartyObj2, nullptr);  // 观察对象数据装载（名称/血量/装备）
    }
    pObj = nArg2;
  }
  return sub_53F8A0(pObj);  // 返回 批量广播器 vt+48 槽（带返回值，取最后一个）
}



// ------------------------------------------------------------
// 0x4D6FA0 sub_4D6FA0
// 辅助对象析构（this+4 处堆块释放 + 三字段清零；头调 sub_53FD50 全局收束）。
// 被 ActiveObject 析构 0x4D7000 以 this+6296 的对象调用。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D6FA0(int this)  // 实现：被 ActiveObject 析构 0x4D7000 以 this+6296 的对象调用
{
  sub_53FD50();  // 调 逐个拆除（vt+32(1) 显隐 + vt+76/vt+68 解绑 + 池析构判定）→ vector 弹出
  if ( *(uint32_t *)(this + 4) != 0 )  // 判定 “+4 宿主对象指针”
    j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
  *(uint32_t *)(this + 4) = 0;  // 写 this+4 = 0（宿主对象指针）
  *(uint32_t *)(this + 8) = 0;  // 写 this+8 = 0（技能槽记录首字）
  *(uint32_t *)(this + 12) = 0;  // 写 this+12 = 0（技能槽记录次字）
}



// ------------------------------------------------------------
// 0x4D7000 sub_4D7000 —— ★ ActiveObject 析构（研究 20 §13 定案）
// 17 状态槽逐个 ->vt+0(对象, 1) 销毁（this+1557 起）+ 槽指针清零；
// this+1574 的辅助对象 → sub_4D6FA0（转发 sub_53FD50）+ free；
// 18 观察者槽逐个 ->vt+4(观察者, 1) 引用计数释放（this+1617 起）+ 清零。
// 研究 §13："观察者是引用计数组件" —— 此处 vt+4 释放即其据。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D7000(uint32_t *this)  // 实现：ActiveObject 析构（研究 20 §13 定案）
{
  uint32_t *pThis_615; // esi
  int i; // ebx
  void *fld_e1574; // esi
  uint32_t *pThis_651; // esi
  int j; // edi

  pThis_615 = this + 1557;
  for ( i = 17; i != 0; --i )  // 循环：i 从 17 递减到 0
  {
    if ( *pThis_615 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_615)(*pThis_615, 1);
    *pThis_615++ = 0;
  }
  fld_e1574 = (void *)*(this + 1574);
  if ( fld_e1574 != nullptr )  // 若 fld_e1574 有效（非空）
  {
    sub_4D6FA0(*(this + 1574));  // 调 被 ActiveObject 析构 0x4D7000 以 this+6296 的对象调用
    j__free(fld_e1574);  // 调 堆释放
  }
  *(this + 1574) = 0;
  pThis_651 = this + 1617;
  for ( j = 18; j != 0; --j )  // 循环：j 从 18 递减到 0
  {
    if ( *pThis_651 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*pThis_651 + 4))(*pThis_651, 1);  // 虚调用 vt+4
    *pThis_651++ = 0;
  }
}



// ------------------------------------------------------------
// 0x4D7080 sub_4D7080
// std::length_error("vector<T> too long") 抛出器（MSVC vector 扩容越界的标准掷出点，
// noreturn）。非业务函数。
// ------------------------------------------------------------
void /*noreturn*/ sub_4D7080()  // 实现：noreturn）。非业务函数
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
  sub_401740(pExceptionObject, &v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
  pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4D70F0 sub_4D70F0
// 小对象构造（0x10 字节）：三字段清零 + nullsub_3 + sub_540270 基类初始化，
// 返回 this（被 0x4D7140 new 出后挂 this+6296，即 ActiveObject 的辅助/状态容器）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4D70F0(uint32_t *this)  // ★ ActiveObject 析构（研究 20 §13 定案）
{
  *(this + 1) = 0;  // 写 this+4 = 0（宿主对象指针）
  *(this + 2) = 0;  // 写 this+8 = 0（技能槽记录首字）
  *(this + 3) = 0;  // 写 this+12 = 0（技能槽记录次字）
  nullsub_3(this);
  sub_540270(this);  // 调 基类初始化
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4D7140 sub_4D7140
// 辅助容器装配：new 0x10 字节经 0x4D70F0 构造后挂 this+6296；给场景对象
//（this+112）的 +200 写 500（【推断】默认值：HP/计时参数），置 this+6740 使能位。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D7140(int this)  // 实现：（this+112）的 +200 写 500（(推断)默认值：HP/计时参数），置 this+6740 使能位
{
  uint32_t *pMem; // eax
  uint32_t *pAuxCont; // eax —— new 0x10 经 0x4D70F0 构造的辅助容器
  int result; // eax

  pMem = operator new(0x10u);  // 堆分配 16 字节对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    pAuxCont = sub_4D70F0(pMem);  // 小对象构造：三字段清零 + nullsub_3 + sub_540270 基类初始化，
  else
    pAuxCont = nullptr;
  *(uint32_t *)(this + 6296) = pAuxCont;  // 字段 this+6296〔的对象调用〕
  result = *(uint32_t *)(this + 112);  // 读 result = this+112（宿主组件）
  *(uint32_t *)(result + 200) = 500;  // result=this+112 第 1 组·宿主属性 +46 增量子倍率
  *(uint8_t *)(this + 6740) = 1;  // this+6740〔bFreeze6740〕
  return result;  // result=this+112 第 1 组·宿主属性 +46 增量子倍率
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
  int pHost; // ebx
  unsigned int nStateCode; // ebx
  int nDmgTypeSrc; // edx
  unsigned int pVt0; // edx
  int nTypeOut; // eax
  unsigned int pVt1; // edx
  int nDmg; // ebx
  int pObj2; // eax
  int *pDelayedHp; // eax
  int pVt2; // edx
  int nHpAttr; // eax
  int nReaction; // ebx
  bool bNear; // cc
  int nAtkX; // ebx
  int nDefX; // eax
  bool bLt0; // sf
  bool bOvfl; // of
  char *pCueName; // eax
  int nDmgType3; // eax
  int pVt3; // eax
  int pVt4; // edx
  int pStatCopy; // ebx
  int nGuardTime; // eax
  uint32_t *pThis_615; // ebx
  int pAtkStat2; // eax
  int nDmgFinal2; // ebx
  float fNegDmg; // [esp+38h] [ebp-60h]
  char strBuf[4]; // [esp+54h] [ebp-44h] BYREF
  void *Block; // [esp+58h] [ebp-40h]
  int strSize; // [esp+5Ch] [ebp-3Ch]
  int strCap; // [esp+60h] [ebp-38h]
  void *pMem; // [esp+64h] [ebp-34h]
  int nRxArg1; // [esp+68h] [ebp-30h] BYREF
  int nRxArg2; // [esp+6Ch] [ebp-2Ch] BYREF
  int nRxArg3; // [esp+70h] [ebp-28h] BYREF
  int nTypeIn; // [esp+74h] [ebp-24h] BYREF
  int nWorkVal; // [esp+78h] [ebp-20h] BYREF
  int nDmgType; // [esp+7Ch] [ebp-1Ch] BYREF
  int nHitKind; // [esp+80h] [ebp-18h]
  int nDmgFinal; // [esp+84h] [ebp-14h]
  int pAtkStat; // [esp+88h] [ebp-10h]
  int nEhState; // [esp+94h] [ebp-4h]

  sub_4D6CA0(this);  // 50% 预表现门（研究 §2① / §8 定案）
  pObj = LODWORD(fArg2);  // pObj = 调 LODWORD
  pThis_651 = this + 1617;
  for ( nWorkVal = 18; nWorkVal != 0; --nWorkVal )  // 循环：nWorkVal 从 18 递减到 0
  {
    if ( *pThis_651 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int))(*(uint32_t *)*pThis_651 + 140))(*pThis_651, pObj, nArg3, nArg4, 1);  // 虚调用 vt+140
    ++pThis_651;
  }
  nArg42 = nArg4;
  sub_4E5DC0(pObj, nArg3, nArg4);  // 【表现壳（hit stop 施加点，研究 §3 全文定案）】
  nDmgFinal = 0;
  HIBYTE(fArg2) = sub_4E5B50((int)this, pObj);  // 暴击/有效命中判定（研究 20 §5.1 全文定案）
  if ( nArg42 != 0 )
  {
    (*(void (/*thiscall*/ **)(unsigned int *, int))(*this + 552))(this, nArg3);  // 虚调用 vt+552
    goto LABEL_101;
  }
  pAtkStat = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj);  // 调虚槽 +348：取坐标对象
  if ( (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 308))(this) == 0 || (pHost = *(this + 30)) == 0 )  // 虚调用 vt+308
  {
    nDmgFinal = -1;
    goto LABEL_101;
  }
  if ( *((uint8_t *)this + 642) != 0 )  // this+642〔bHitBoxSnap642〕
  {
    nStateCode = *(this + 161);  // this+644〔uHitBoxSnap644〕
  }
  else
  {
    if ( *(uint32_t *)(pHost + 148) == -1 )
      sub_4938F0(*(this + 30));  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    nStateCode = *(uint32_t *)(pHost + 112);  // nStateCode=this+644 uHitBoxSnap644
  }
  nDmgTypeSrc = *(uint32_t *)(pAtkStat + 60);
  nHitKind = nStateCode;  // nStateCode=this+644 uHitBoxSnap644
  nDmgType = nDmgTypeSrc;
  if ( nStateCode <= 1 )  // nStateCode=this+644 uHitBoxSnap644
  {
    (*(void (/*thiscall*/ **)(unsigned int *, int))(*this + 964))(this, pObj);  // 虚调用 vt+964
    pVt0 = *this;
    LOBYTE(nRxArg2) = 0;  // 调 取 16 位值低 8 位
    nTypeIn = 100;
    nRxArg3 = 0;
    nTypeOut = (*(int (/*thiscall*/ **)(unsigned int *, int *, int))(pVt0 + 648))(this, &nTypeIn, pObj);  // 调虚槽 +648：写入 100（格挡/减伤基础值槽）
    pVt1 = *this;
    nRxArg1 = nTypeOut;
    nDmg = (*(int (/*thiscall*/ **)(unsigned int *, int *, int *, int, int, int, uint32_t))(pVt1 + 628))(  // 调虚槽 +628：伤害流水线九步
            this,
            &nRxArg2,
            &nRxArg3,
            nTypeIn,
            pObj,
            nArg3,
            0);
    nDmgFinal = nDmg;
    if ( HIBYTE(fArg2) != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 576))(pObj) != 0 )  // 调虚槽 +576
    {
      pObj2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 576))(pObj);  // 调虚槽 +576
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      {
        nDmg += (uint64_t)((double)nDmgFinal * 0.25);  // 【条件追加 +25%：暴击 && 受有车主 && 车主 273 受击态（§2⑥ 差异标注见函数头）】
        nDmgFinal = nDmg;
        if ( nDmgType == 1 )
          nDmgType = 2;  // 伤害类型 1 → 2（该加成路径改记类型 2）
        sub_424AB0(500, 50);  // （寄存器对 500/50：【推断】表现计时/优先级入参）
      }
    }
    if ( nDmg >= (*(int (/*thiscall*/ **)(unsigned int *))(*this + 736))(this) )  // 虚调用 vt+736
      nWorkVal = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 736))(this);  // 结果 = 虚调用 vt+736
    else
      nWorkVal = nDmg;  // 日志用夹取：min(伤害, 当前HP)
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj) + 124) == 2 )  // 调虚槽 +348：取坐标对象
    {
      pMem = operator new(0x80u);  // 攻方属性块 +124==2 → 延滞伤路径（研究 §2⑦：new CNChangeHp 延滞 1000ms）
      nEhState = 0;
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
      {
        nRxArg1 = -nWorkVal;
        fNegDmg = (float)-nWorkVal;
        pDelayedHp = (int *)sub_4D6810(LODWORD(fNegDmg), 1000, 0, 1);  // CNChangeHp 构造（研究 §2⑦ 的延滞伤分支）
      }
      else
      {
        pDelayedHp = nullptr;
      }
      pVt2 = *pDelayedHp;
      nEhState = -1;
      (*(void (/*thiscall*/ **)(int *, unsigned int *, int, uint32_t, uint32_t, uint32_t, int))(pVt2 + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
        pDelayedHp,
        this,
        pObj,
        0,
        0,
        0,
        -1);
    }
    else
    {
      nHpAttr = sub_41A5E0(this + 1533);  // 当前 HP（属性块读数）
      (*(void (/*thiscall*/ **)(unsigned int *, int, uint32_t, int))(*this + 728))(this, nHpAttr - nDmg, 0, pObj);  // HP setter vt+728：delta = 当前HP − 伤害（DLL 锚点 [13]）
      *(this + 1650) = -1;  // 重置 HP 写入时刻戳（0x4D4D40 的 a1[1650]）
      if ( nDmg != 0 || *(uint8_t *)(pAtkStat + 16) != 0 || *(float *)pAtkStat > 0.0 )
        sub_4D5330(pObj, this, nArg3, nDmg, nWorkVal, nRxArg2, nRxArg3, nRxArg1);  // DNF.trc 伤害日志（研究 §2⑦）
      if ( nHitKind != 2 && (nRxArg1 == 1 || nRxArg1 == 2) )  // 若 nHitKind != 2 与/或 nRxArg1 == 1 与/或 nRxArg1 == 2
        nHitKind = 1;
    }
  }
  nWorkVal = 0;
  nRxArg1 = 0;
  if ( nDmgType == 0 )
    goto LABEL_101;
  if ( (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 724))(this) != 0 )  // 虚调用 vt+724
  {
    if ( *(this + 1639) == 5 || *(this + 154) == 5 )  // this+6556〔大状态ID〕
      goto LABEL_101;
    if ( (*(uint8_t (/*thiscall*/ **)(unsigned int *, int))(*this + 40))(this, 273) != 0 )  // 虚调用 vt+40
    {
      nReaction = 4;
    }
    else
    {
      if ( (*(uint8_t (/*thiscall*/ **)(unsigned int *, int))(*this + 40))(this, 529) == 0 )  // 虚调用 vt+40
        goto LABEL_101;
      if ( *(uint32_t *)(dword_8F7A24 + 244) == 2 )  // 全局 dword_8F7A24 = 登录/选区管理器
      {
        nReaction = 4;
      }
      else if ( ((*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 936))(this) != 0 || *(this + 1639) == 9)  // 虚调用 vt+936
             && (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 1020))(this) == 0  // 虚调用 vt+1020
             || *(this + 1545) == 0 )  // this+6180〔pAtkCtxC6180〕
      {
        bNear = *(uint32_t *)(pAtkStat + 64) < 150;
        nReaction = 5;
        nRxArg2 = 5;
        if ( bNear )
        {
          nWorkVal = *(uint32_t *)(pAtkStat + 68) < 400 ? 2 : 5;
        }
        else
        {
          nAtkX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 调虚槽 +120：动画对象
          nDefX = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
          bOvfl = __OFSUB__(nAtkX, nDefX);  // bOvfl = 调 __OFSUB__
          bLt0 = nAtkX - nDefX < 0;
          nReaction = nRxArg2;
          nWorkVal = (bLt0 ^ bOvfl) + 3;  // 远距：按攻受 x 差符号给方向码 3/4（击退朝向）
        }
      }
      else
      {
        nReaction = 4;
      }
    }
    goto LABEL_67;
  }
  if ( nHitKind != 0
    || (*(uint8_t (/*thiscall*/ **)(unsigned int *, int))(*this + 776))(this, 1) != 0  // 虚调用 vt+776
    || (*(uint8_t (/*thiscall*/ **)(unsigned int *, int))(*this + 776))(this, 7) != 0 )  // 虚调用 vt+776
  {
    goto LABEL_101;
  }
  if ( nDmgType == 1 )
  {
    if ( ((*(int (/*thiscall*/ **)(unsigned int *))(*this + 436))(this) > 0  // 虚调用 vt+436
       || (*(int (/*thiscall*/ **)(unsigned int *))(*this + 128))(this) <= 0)  // 虚调用 vt+128
      && *(this + 1639) != 4 )  // this+6556〔大状态ID〕
    {
      nReaction = 3;
      goto LABEL_67;
    }
  }
  else if ( nDmgType != 2 )
  {
    goto LABEL_101;
  }
  nReaction = 4;
  if ( *(this + 1545) != 0 )  // this+6180〔pAtkCtxC6180〕
  {
    if ( *(this + 1639) == 4 && (int)*(this + 1708) >= 1 )  // this+6556〔大状态ID〕
      nRxArg1 = 1;  // 击退可被墙体/边界截停的标志（this+6832 大状态联动）【推断】
  }
  else
  {
    nReaction = 3;
  }
LABEL_67:
  if ( *((uint8_t *)this + 612) != 0 )  // 语音/台词触发位：放受击语音（this+6768 串，vt+212）
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj) + 124) == 2 )  // 调虚槽 +348：取坐标对象
      rand();  // 调 取伪随机数
    if ( *(this + 1697) < 0x10 )
      pCueName = (char *)(this + 1692);  // this+1692〔szCueName1692〕
    else
      pCueName = (char *)*(this + 1692);  // this+1692 播报提示串缓冲
    (*(void (/*thiscall*/ **)(unsigned int *, char *, int, uint32_t, uint32_t))(*this + 212))(this, pCueName, -1, 0, 0);  // 虚调用 vt+212
  }
  switch ( nReaction )  // 按 nReaction 分派
  {
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      if ( *(this + 1544) != 0 )  // this+6176〔pAtkCtxB6176〕
      {
        if ( *(this + 1543) != 0 )  // this+6172〔pAtkCtxA6172〕
        {
          if ( *(this + 1639) == 3 )  // this+6556〔大状态ID〕
            nDmgType3 = 1 - *(this + 1689);
          else
            nDmgType3 = rand() % 2;  // nDmgType3 = 调 rand
          nDmgType = nDmgType3;
        }
        else
        {
          nDmgType = 1;
        }
      }
      else
      {
        nDmgType = 0;
      }
      fArg2 = *(float *)(pAtkStat + 136);  // 攻方属性块 +136：硬直系数（-1 = 用默认 1.0）
      if ( fArg2 == -1.0 )
        fArg2 = 1.0;
      if ( *(uint32_t *)(pAtkStat + 12) == 1 )
        fArg2 = fArg2 * 0.69999999;  // 硬直反应系数 ×0.7（攻方属性块 +12==1 时，研究 §1.2 反应档）
      Block = nullptr;
      strSize = 0;
      strCap = 0;
      pVt3 = *(uint32_t *)pObj;
      nEhState = 1;
      nRxArg1 = (*(int (/*thiscall*/ **)(int, unsigned int *))(pVt3 + 660))(pObj, this);
      sub_431230(&nRxArg1);  // uint32 vector push_back
      if ( *(uint8_t *)(pAtkStat + 81) != 0 )
        fArg2 = NAN;  // 属性块 +81 标志 → 序列化 NaN（反应包"无该段"哨兵）
      else
        LODWORD(fArg2) = (uint64_t)(fArg2 * 100.0);  // 定点化 ×100
      sub_431230(&fArg2);  // uint32 vector push_back
      sub_431230(&nDmgType);  // uint32 vector push_back
      fArg2 = *(float *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj) + 124);  // 调虚槽 +348：取坐标对象
      sub_431230(&fArg2);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(unsigned int *, int, char *, int, uint32_t))(*this + 560))(this, 3, strBuf, 2, 0);  // 虚调用 vt+560
      nEhState = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
LABEL_91:
        j__free(Block);  // 调 堆释放
      break;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      Block = nullptr;
      strSize = 0;
      strCap = 0;
      pVt4 = *(uint32_t *)pObj;
      nEhState = 2;
      nRxArg2 = (*(int (/*thiscall*/ **)(int, unsigned int *))(pVt4 + 660))(pObj, this);
      sub_431230(&nRxArg2);  // uint32 vector push_back
      sub_431230(&nRxArg1);  // uint32 vector push_back
      nRxArg1 = 1;
      sub_431230(&nRxArg1);  // uint32 vector push_back
      pStatCopy = pAtkStat;
      sub_431230(pAtkStat + 64);  // uint32 vector push_back
      nGuardTime = 0;
      if ( HIBYTE(fArg2) != 0 )  // 调 取 16 位值高 8 位
        nGuardTime = *(uint32_t *)(pStatCopy + 60) != 1 ? 50 : 250;  // 击退帧时长：暴击(+60==1) 250 / 普通 50
      LODWORD(fArg2) = nGuardTime + *(uint32_t *)(pStatCopy + 68);  // + 攻方属性块 +68 的附加时长
      sub_431230(&fArg2);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(unsigned int *, int, char *, int, uint32_t))(*this + 560))(this, 4, strBuf, 2, 0);  // 虚调用 vt+560
      nEhState = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        goto LABEL_91;
      break;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      Block = nullptr;
      strSize = 0;
      strCap = 0;
      nEhState = 3;
      sub_431230(&nWorkVal);  // uint32 vector push_back
      (*(void (/*thiscall*/ **)(unsigned int *, int, char *, int, uint32_t))(*this + 560))(this, 5, strBuf, 2, 0);  // 虚调用 vt+560
      nEhState = -1;
      sub_5E5260(strBuf);  // 调 动画子对象清理临时缓冲
      break;
    default:
      break;
  }
LABEL_101:
  fArg2 = 0.0;
  pThis_615 = this + 1557;
  do
  {
    if ( (*(uint8_t (/*thiscall*/ **)(unsigned int *, float))(*this + 776))(this, COERCE_FLOAT(LODWORD(fArg2))) != 0 )  // 虚调用 vt+776
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*pThis_615 + 76))(*pThis_615, pObj, nArg3, nArg4);  // 虚调用 vt+76
    ++pThis_615;
    ++LODWORD(fArg2);  // 调 取 64 位值低 32 位
  }
  while ( SLODWORD(fArg2) < 17 );  // 调 取 64 位值低 32 位(带符号)
  pAtkStat2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj);  // 调虚槽 +348：取坐标对象
  if ( *(uint8_t *)(pAtkStat2 + 16) == 0 && *(float *)pAtkStat2 <= 0.0 )
    return nDmgFinal;
  nDmgFinal2 = nDmgFinal;
  (*(void (/*thiscall*/ **)(unsigned int *, int, int))(*this + 544))(this, pObj, nDmgFinal);  // vt+544 终结算：播报层 HK_ATTACKED（0x4D49E0）
  return nDmgFinal2;
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
int /*usercall*/ sub_4D7960@<eax>(  // 飘字咽喉（研究 20 §1.1 case 0x14；第 34/39 轮 P39 全套）
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
  int nDigits; // kr04_4
  int nTotalW; // edi
  int i; // esi
  int nXOffset; // ebx
  int result; // eax
  int nLayer; // esi
  int pGlyph; // edi
  int pSprite; // ecx
  int nW2; // eax
  int nDy; // edx
  int pPooled; // esi
  int pPooledVt; // edx
  bool bMore; // cc
  int pStageCtx; // [esp+4h] [ebp-64h]
  int pGuard; // [esp+10h] [ebp-58h]
  int pFxObj; // [esp+10h] [ebp-58h]
  int nFontBase; // [esp+14h] [ebp-54h]
  char Buffer[64]; // [esp+18h] [ebp-50h] BYREF
  int nCookieCopy; // [esp+58h] [ebp-10h] —— 安全 Cookie 副本（dword_796E50 惯例）
  int nEhState; // [esp+64h] [ebp-4h]
  int nCharIdx; // [esp+88h] [ebp+20h]

  nCookieCopy = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  sprintf(Buffer, "%d", abs32(a7));  // 字符串 “%d”
  nDigits = strlen(Buffer);  // nDigits = 调 strlen
  nFontBase = 44;
  if ( a8 == 2 )
  {
    nFontBase = 64;
  }
  else if ( a8 == 3 )
  {
    nFontBase = 74;
  }
  else if ( a8 == 4 || a9 != 0 )
  {
    nFontBase = 54;
  }
  if ( a10 == 1 )
    nFontBase = 143;
  nTotalW = 0;
  for ( i = 0; i < nDigits; ++i )
    nTotalW += *(uint32_t *)(sub_418DD0(Buffer[i] + nFontBase - 48) + 20);  // 逐位取字形资源（字符+字体基址−48）的 +20 宽度
  nXOffset = (5 - 5 * nDigits + nTotalW) / -2;
  pStageCtx = *(uint32_t *)((*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 120))(  // 调虚槽 +120：动画对象
                      dword_8F8520,  // 会话/UDP 管理器
                      a2,
                      a3,
                      a1)
                  + 104);
  result = nDigits;
  nLayer = 0;
  nCharIdx = 0;
  if ( nDigits <= 0 )
    return result;
  while ( 2 )
  {
    pGlyph = sub_418DD0(Buffer[nCharIdx] + nFontBase - 48);  // 调 资源句柄 (101)
    pGuard = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
    nEhState = 0;
    if ( pGuard != 0 )
      pFxObj = sub_4B59A0(5);  // 结果 = 角色动画包装器复位（+204 子动画链、sub_493BD0 复位 / sub_494610
    else
      pFxObj = 0;
    nEhState = -1;
    do
    {
      pSprite = sub_4924C0(nLayer);  // 结果 = 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
      *(uint32_t *)pSprite = pGlyph;  // *pSprite = pGlyph
      *(uint32_t *)(pSprite + 12) = nXOffset;
      if ( a8 == 4 )
      {
        *(uint32_t *)(pSprite + 20) = 1067030938;
        *(uint32_t *)(pSprite + 24) = 1067030938;
      }
      if ( nLayer != 0 )
      {
        switch ( nLayer )  // 按 nLayer 分派
        {
          case 1:  // 幽灵层 1：延迟 200ms，水平居中
            *(uint32_t *)(pSprite + 48) = 200;
            *(uint32_t *)(pSprite + 16) = *(uint32_t *)(pGlyph + 24) / -2;
            goto LABEL_36;
          case 2:  // 幽灵层 2：延迟 100ms，半透明标志
            *(uint32_t *)(pSprite + 48) = 100;
            *(uint32_t *)(pSprite + 16) = *(uint32_t *)(pGlyph + 24) / -2;
            *(uint8_t *)(pSprite + 36) = 1;
            goto LABEL_36;
          case 3:  // 幽灵层 3：延迟 100ms，y−15 梯次 + 半透明色
            *(uint32_t *)(pSprite + 48) = 100;
            nW2 = *(uint32_t *)(pGlyph + 24) - (*(int *)(pGlyph + 24) >> 31);
            nDy = -15;
            *(uint8_t *)(pSprite + 36) = 1;
            *(uint32_t *)(pSprite + 32) = -2130706433;  // 0x80FFFFFF：alpha=0x80 白
            break;
          case 4:  // 幽灵层 4：无延迟，y−30 梯次
            *(uint32_t *)(pSprite + 48) = 0;
            nW2 = *(uint32_t *)(pGlyph + 24) - (*(int *)(pGlyph + 24) >> 31);
            nDy = -30;
            *(uint32_t *)(pSprite + 32) = 0xFFFFFF;  // 常量 0xFFFFFF（= 0xFFFFFF）
            break;
          default:
            goto LABEL_36;
        }
        *(uint32_t *)(pSprite + 16) = nDy - (nW2 >> 1);
      }
      else
      {
        *(uint32_t *)(pSprite + 48) = 100;  // 主层（层 0）：延迟 100ms
        *(uint32_t *)(pSprite + 16) = *(uint32_t *)(pGlyph + 24) / -2;  // 水平居中
        if ( a8 != 4 )
        {
          *(uint32_t *)(pSprite + 20) = 0x40000000;  // 缩放 2.0f（类型 4 除外——它用上面的 1.4f）
          *(uint32_t *)(pSprite + 24) = 0x40000000;
        }
        *(uint8_t *)(pSprite + 36) = 1;
        if ( a8 == 1 || a8 == 4 )  // 若 a8 == 1 与/或 a8 == 4
        {
          *(uint32_t *)(pSprite + 40) = 5;   // 类型 1/4：弹跳参数（5 段/−1 循环）
          *(uint32_t *)(pSprite + 44) = -1;
        }
      }
LABEL_36:
      ++nLayer;
    }
    while ( nLayer < 5 );
    pPooled = sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
    nEhState = 1;
    if ( pPooled != 0 )
    {
      sub_44E0D0(pFxObj, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)pPooled = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
    }
    else
    {
      pPooled = 0;
    }
    pPooledVt = *(uint32_t *)pPooled;
    nEhState = -1;
    (*(void (/*thiscall*/ **)(int, int))(pPooledVt + 72))(pPooled, 2);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520/4…
    sub_45FE80(pStageCtx, pGlyph, 2, 0, pPooled, 0, 0);  // 调 实体对象注册到演播层
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pPooled + 112))(pPooled, a4, a5, a6);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    result = nCharIdx + 1;
    bMore = nCharIdx + 1 < nDigits;
    nXOffset = nXOffset + *(uint32_t *)(pGlyph + 20) - 5;
    ++nCharIdx;
    if ( bMore )
    {
      nLayer = 0;
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
  int pAni; // ebx
  char *pAlloc; // eax
  int pObj; // edi
  int pPooledVt; // ebx
  int nAnimX; // edi
  int nOffY; // eax
  int nBaseY2; // eax
  int nBarX2; // eax
  int nReturnId; // eax
  int nBarX0; // eax
  int nBarX; // edi
  int nAnimY; // eax
  int nBarY; // ebx
  int nBarY2; // ebx
  int pResL; // eax
  int pResL2; // eax
  int pResM; // eax
  int pResR; // eax
  int nBaseY; // [esp-14h] [ebp-28h]
  int nBarH2; // [esp-10h] [ebp-24h]
  int nBarH; // [esp-Ch] [ebp-20h]
  int nProgress; // [esp+4h] [ebp-10h]
  int pObj2; // [esp+4h] [ebp-10h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1000))(this) != 0 )  // 虚调用 vt+1000
  {
    nProgress = (*(int (/*thiscall*/ **)(int *))(*this + 1012))(this);  // 吟唱进度（0..100）
    if ( nProgress < 50 )  // <50 画进度条；否则播收尾 ani
    {
      (*(void (/*thiscall*/ **)(int *))(*this + 80))(this);  // 虚调用 vt+80
      nBarH = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 36))(this) + 8);  // 结果 = 虚调用 vt+36
      nBarX0 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
      nBarX = sub_45E490(nBarX0, nBarH) - 25;  // 结果 = 屏幕 y → 演出层坐标（减基线）
      (*(void (/*thiscall*/ **)(int *))(*this + 80))(this);  // 虚调用 vt+80
      nBarH2 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 36))(this) + 8);  // 结果 = 虚调用 vt+36
      nBaseY = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
      nAnimY = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
      nBarY = sub_45E4D0(nAnimY, nBaseY, nBarH2, 1.0);  // 结果 = 带比例的回换算（nArg2 - nArg3*f + 120）
      nBarY2 = -10 - (*(int (/*thiscall*/ **)(int *))(*this + 192))(this) + nBarY;  // 结果 = 虚调用 vt+192
      pResL = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 148), 0);  // 调 资源句柄 (101)
      sub_424760(dword_79C0B0, nBarX - 1, nBarY2 - 1, pResL, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      pResL2 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 148), 2u);  // 调 资源句柄 (101)
      sub_424760(dword_79C0B0, nBarX - 4, nBarY2 - 3, pResL2, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      sub_424980(dword_79C0B0, nBarX, 0, nBarX + nProgress, 480);  // 填充条：宽度 = vt+1012 进度值
      pResM = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 148), 1u);  // 资源族 148 的槽 1 = 中段贴图
      sub_424760(dword_79C0B0, nBarX, nBarY2, pResM, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      sub_488670((uint32_t *)dword_79C0B0);  // 视口重置 640x480
      pResR = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 148), 3u);  // 调 资源句柄 (101)
      sub_424760(dword_79C0B0, nBarX + nProgress, nBarY2, pResR, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
    }
    else
    {
      pAni = 0;
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        pAni = sub_431860((char)"Common/Etc/Animation/EndofCasting.ani", 1);  // 字符串 “Common/Etc/Animation/EndofCasting.ani”
      pAlloc = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
      pObj = (int)pAlloc;
      if ( pAlloc != nullptr )  // 若 pAlloc 有效（非空）
      {
        sub_44E0D0(pAlloc, pAni, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)pObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
      }
      else
      {
        pObj = 0;
      }
      pObj2 = pObj;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 72))(pObj);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
      sub_45FE80(*(this + 29), pObj, 2, 0, pObj, (int)this, 0);  // 调 实体对象注册到演播层
      pPooledVt = *(uint32_t *)pObj;
      nAnimX = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);  // 结果 = 虚调用 vt+192
      nOffY = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
      nBaseY2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nAnimX + nOffY + 10);  // 结果 = 虚调用 vt+124
      nBarX2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nBaseY2 + 1);  // 结果 = 虚调用 vt+120
      (*(void (/*thiscall*/ **)(int, int))(pPooledVt + 112))(pObj2, nBarX2);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      nReturnId = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj2 + 60))(pObj2, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
      sub_4A06D0(nReturnId, 2);  // 调 绑定目标对象并记录相对偏移
      (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);  // 虚调用 vt+996
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
  int pStage; // eax
  int pAni; // ebx
  char *pAlloc; // eax
  int pFxObj; // edi
  int pFxVt; // ebx
  int nPosA; // eax
  int nPosB; // eax
  int nPosC; // eax
  int nReturnId; // eax
  int pAni2; // ebx
  char *pAlloc2; // eax
  int pFxObj2; // edi
  int pFxVt2; // ebx
  int nPosA2; // eax
  int nPosB2; // eax
  int nPosC2; // eax
  int nReturnId2; // eax
  char oldFlag7105; // [esp+Fh] [ebp-Dh]

  oldFlag7105 = *((uint8_t *)this + 7105);  // this+7105〔bSet7105〕
  *((uint8_t *)this + 7105) = pszArg2;  // this+7105〔bSet7105〕
  pStage = *(this + 29);  // this+116〔会话上下文〕
  if ( pszArg2 != 0 )
  {
    pAni = 0;
    if ( pStage != 0 )  // pStage=this+116 会话上下文
    {
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        pAni = sub_431860((char)"Common/CommonEffect/Animation/Camouflage.ani", 1);  // 字符串 “Common/CommonEffect/Animation/Camouflage.ani”
      pAlloc = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
      pFxObj = (int)pAlloc;
      if ( pAlloc != nullptr )  // 若 pAlloc 有效（非空）
      {
        sub_44E0D0(pAlloc, pAni, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)pFxObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
      }
      else
      {
        pFxObj = 0;
      }
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pFxObj + 72))(pFxObj);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
      sub_45FE80(*(this + 29), pFxObj, 2, 0, pFxObj, (int)this, 0);  // 调 实体对象注册到演播层
      pFxVt = *(uint32_t *)pFxObj;
      nPosA = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
      nPosB = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nPosA);  // 结果 = 虚调用 vt+124
      nPosC = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nPosB);  // 结果 = 虚调用 vt+120
      (*(void (/*thiscall*/ **)(int, int))(pFxVt + 112))(pFxObj, nPosC);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      nReturnId = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pFxObj + 60))(pFxObj, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
      sub_4A06D0(nReturnId, 2);  // 调 绑定目标对象并记录相对偏移
    }
    if ( oldFlag7105 != 1 )  // oldFlag7105=this+7105 bSet7105
      *(this + 1777) = sub_699000((int)(this + 9));  // clock_now(clk)
    *(this + 1778) = nArg3 + sub_699000((int)(this + 9));  // clock_now(clk)
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212
             this,
             "CAMOUFLAGE_DISAPPEAR",  // 字符串 “CAMOUFLAGE_DISAPPEAR”
             -1,
             0,
             0);
  }
  else
  {
    if ( pStage != 0 )  // pStage=this+116 会话上下文
    {
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        pAni2 = sub_431860((char)"Common/CommonEffect/Animation/Decamouflage.ani", 1);  // 字符串 “Common/CommonEffect/Animation/Decamouflage.a”
      else
        pAni2 = 0;
      pAlloc2 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
      pFxObj2 = (int)pAlloc2;
      if ( pAlloc2 != nullptr )  // 若 pAlloc2 有效（非空）
      {
        sub_44E0D0(pAlloc2, pAni2, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)pFxObj2 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
      }
      else
      {
        pFxObj2 = 0;
      }
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pFxObj2 + 72))(pFxObj2);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
      sub_45FE80(*(this + 29), pFxObj2, 2, 0, pFxObj2, (int)this, 0);  // 调 实体对象注册到演播层
      pFxVt2 = *(uint32_t *)pFxObj2;
      nPosA2 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
      nPosB2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nPosA2);  // 结果 = 虚调用 vt+124
      nPosC2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nPosB2);  // 结果 = 虚调用 vt+120
      (*(void (/*thiscall*/ **)(int, int))(pFxVt2 + 112))(pFxObj2, nPosC2);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      nReturnId2 = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pFxObj2 + 60))(pFxObj2, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
      sub_4A06D0(nReturnId2, 2);  // 调 绑定目标对象并记录相对偏移
    }
    *(this + 1777) = sub_699000((int)(this + 9));  // clock_now(clk)
    *(this + 1778) = 0;  // this+7112〔uSet7112〕
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212
             this,
             "CAMOUFLAGE_APPEAR",  // 字符串 “CAMOUFLAGE_APPEAR”
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
  int *pFxList; // ecx
  int *pFxNode; // edi
  int nBound0; // ebx
  int nBound1; // eax
  uint32_t *pAni; // ebx
  char *pPath; // eax
  int pObj; // edi
  int pPooledVt; // ebx
  int nPosB; // eax
  int nPosC; // eax
  int nReturnId; // eax
  int nPosA; // [esp-Ch] [ebp-28h]
  float fScaleX; // [esp+8h] [ebp-14h]
  float fScaleY; // [esp+Ch] [ebp-10h]

  if ( *(this + 29) != 0 )  // this+116〔会话上下文〕
  {
    pFxList = (int *)*(this + 1540);
    fScaleX = 1.0;
    fScaleY = 1.0;
    if ( pFxList != nullptr )  // 若 pFxList 有效（非空）
    {
      pFxNode = (int *)sub_4924C0(pFxList, 0);  // 结果 = 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
      nBound0 = sub_4918E0(pFxNode, 0);  // 结果 = 动画盒四边界提取（研究 P29 族）
      nBound1 = sub_4918E0(pFxNode, 1);  // 结果 = 动画盒四边界提取（研究 P29 族）
      if ( nBound0 > nBound1 )
        nBound1 = nBound0;
      fScaleX = (double)(2 * nBound1) * 0.014705882;
      fScaleY = (double)(*(this + 40) + 40) * 0.0078125;  // this+160〔fAdd160(推断)〕
    }
    pAni = nullptr;
    if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
      pAni = (uint32_t *)sub_431860((char)"Common/CommonEffect/Animation/Disenchanted.ani", 1);  // 字符串 “Common/CommonEffect/Animation/Disenchanted.a”
    sub_4920E0(pAni, fScaleX, fScaleY);  // 批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
    pPath = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
    pObj = (int)pPath;
    if ( pPath != nullptr )  // 若 pPath 有效（非空）
    {
      sub_44E0D0(pPath, (int)pAni, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)pObj = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
    }
    else
    {
      pObj = 0;
    }
    sub_45FE80(*(this + 29), pObj, 2, 0, pObj, 0, 0);  // 调 实体对象注册到演播层
    pPooledVt = *(uint32_t *)pObj;
    nPosA = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
    nPosB = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
    nPosC = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nPosB + 1);  // 结果 = 虚调用 vt+120
    (*(void (/*thiscall*/ **)(int, int))(pPooledVt + 112))(pObj, nPosC);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    nReturnId = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    sub_4A06D0(nReturnId, nPosA);  // 调 绑定目标对象并记录相对偏移
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
void /*thiscall*/ sub_4D82D0(int *this, int nArg2, int nArg3)  // 实现：头顶气泡 Command.ani（a2/a3 = 定位偏移）
{
  int pAni; // ebx
  char *pAlloc; // eax
  int pObj2; // edi
  int pFxVt; // ebx
  int nFrameOff; // edi
  int nBaseY; // eax
  int nBubbleY; // edi
  int nPosY; // eax
  int nPosZ; // eax
  int nReturnId; // eax
  int pObj; // [esp+Ch] [ebp-10h]

  pAni = 0;
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    pAni = sub_431860((char)"Common/CommonEffect/Animation/Command.ani", 1);  // 字符串 “Common/CommonEffect/Animation/Command.ani”
  pAlloc = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  pObj2 = (int)pAlloc;
  if ( pAlloc != nullptr )  // 若 pAlloc 有效（非空）
  {
    sub_44E0D0(pAlloc, pAni, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)pObj2 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
  }
  else
  {
    pObj2 = 0;
  }
  pObj = pObj2;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 72))(pObj2);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
  sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, (int)this, 0);  // 调 实体对象注册到演播层
  pFxVt = *(uint32_t *)pObj2;
  nFrameOff = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);  // 结果 = 虚调用 vt+192
  nBaseY = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
  nBubbleY = nArg3 - *(uint32_t *)((*(int (/*thiscall*/ **)(int *, int))(*this + 340))(this, nBaseY + nFrameOff) + 40);  // 结果 = 虚调用 vt+340
  nPosY = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
  nPosZ = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nPosY + nBubbleY);  // 结果 = 虚调用 vt+120
  (*(void (/*thiscall*/ **)(int, int))(pFxVt + 112))(pObj, nArg2 + nPosZ);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  nReturnId = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
  sub_4A06D0(nReturnId, 2);  // 调 绑定目标对象并记录相对偏移
}



// ------------------------------------------------------------
// 0x4D83E0 sub_4D83E0 —— 头顶气泡 "Exclamation.ani"（惊叹；同 0x4D82D0 结构）
// ------------------------------------------------------------
void /*thiscall*/ sub_4D83E0(int *this, int nArg2, int nArg3)  // 实现：头顶气泡 Exclamation.ani（惊叹；同 0x4D82D0 结构）
{
  int pAni; // ebx
  char *pAlloc; // eax
  int pObj2; // edi
  int pFxVt; // ebx
  int nFrameOff; // edi
  int nBaseY; // eax
  int nBubbleY; // edi
  int nPosY; // eax
  int nPosZ; // eax
  int nReturnId; // eax
  int pObj; // [esp+Ch] [ebp-10h]

  pAni = 0;
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    pAni = sub_431860((char)"Common/CommonEffect/Animation/Exclamation.ani", 1);  // 字符串 “Common/CommonEffect/Animation/Exclamation.an”
  pAlloc = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  pObj2 = (int)pAlloc;
  if ( pAlloc != nullptr )  // 若 pAlloc 有效（非空）
  {
    sub_44E0D0(pAlloc, pAni, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)pObj2 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
  }
  else
  {
    pObj2 = 0;
  }
  pObj = pObj2;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 72))(pObj2);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
  sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, (int)this, 0);  // 调 实体对象注册到演播层
  pFxVt = *(uint32_t *)pObj2;
  nFrameOff = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);  // 结果 = 虚调用 vt+192
  nBaseY = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
  nBubbleY = nArg3 - *(uint32_t *)((*(int (/*thiscall*/ **)(int *, int))(*this + 340))(this, nBaseY + nFrameOff) + 40);  // 结果 = 虚调用 vt+340
  nPosY = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
  nPosZ = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nPosY + nBubbleY);  // 结果 = 虚调用 vt+120
  (*(void (/*thiscall*/ **)(int, int))(pFxVt + 112))(pObj, nArg2 + nPosZ);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  nReturnId = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
  sub_4A06D0(nReturnId, 2);  // 调 绑定目标对象并记录相对偏移
}



// ------------------------------------------------------------
// 0x4D84F0 sub_4D84F0 —— 头顶气泡 "CommandReceive.ani"（同 0x4D82D0 结构）
// ------------------------------------------------------------
void /*thiscall*/ sub_4D84F0(int *this, int nArg2, int nArg3)  // 实现：头顶气泡 CommandReceive.ani（同 0x4D82D0 结构）
{
  int pAni; // ebx
  char *pAlloc; // eax
  int pObj2; // edi
  int pFxVt; // ebx
  int nFrameOff; // edi
  int nBaseY; // eax
  int nBubbleY; // edi
  int nPosY; // eax
  int nPosZ; // eax
  int nReturnId; // eax
  int pObj; // [esp+Ch] [ebp-10h]

  pAni = 0;
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    pAni = sub_431860((char)"Common/CommonEffect/Animation/CommandReceive.ani", 1);  // 字符串 “Common/CommonEffect/Animation/CommandReceive”
  pAlloc = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  pObj2 = (int)pAlloc;
  if ( pAlloc != nullptr )  // 若 pAlloc 有效（非空）
  {
    sub_44E0D0(pAlloc, pAni, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)pObj2 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
  }
  else
  {
    pObj2 = 0;
  }
  pObj = pObj2;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 72))(pObj2);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
  sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, (int)this, 0);  // 调 实体对象注册到演播层
  pFxVt = *(uint32_t *)pObj2;
  nFrameOff = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);  // 结果 = 虚调用 vt+192
  nBaseY = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
  nBubbleY = nArg3 - *(uint32_t *)((*(int (/*thiscall*/ **)(int *, int))(*this + 340))(this, nBaseY + nFrameOff) + 40);  // 结果 = 虚调用 vt+340
  nPosY = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
  nPosZ = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nPosY + nBubbleY);  // 结果 = 虚调用 vt+120
  (*(void (/*thiscall*/ **)(int, int))(pFxVt + 112))(pObj, nArg2 + nPosZ);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  nReturnId = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
  sub_4A06D0(nReturnId, 2);  // 调 绑定目标对象并记录相对偏移
}



// ------------------------------------------------------------
// 0x4D8600 sub_4D8600 —— 头顶气泡 "Question.ani"（疑问；结构同上但少一层坐标补偿）
// 被 0x4D8A80 调用：位置 1000ms 未变且大状态 == 0 时进入"发呆"表现并切大状态 21。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D8600(int *this, int nArg2, int nArg3)  // 实现：头顶气泡 Question.ani（疑问；结构同上但少一层坐标补偿）
{
  int pAni; // ebx
  char *pAlloc; // eax
  int pObj2; // edi
  int pFxVt; // ebx
  int nFrameOff; // edi
  int nBaseY; // eax
  int nBubbleY; // eax
  int nPosY; // eax
  int nPosZ; // eax
  int pObj; // [esp+Ch] [ebp-10h]

  pAni = 0;
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    pAni = sub_431860((char)"Common/CommonEffect/Animation/Question.ani", 1);  // 字符串 “Common/CommonEffect/Animation/Question.ani”
  pAlloc = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  pObj2 = (int)pAlloc;
  if ( pAlloc != nullptr )  // 若 pAlloc 有效（非空）
  {
    sub_44E0D0(pAlloc, pAni, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)pObj2 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
  }
  else
  {
    pObj2 = 0;
  }
  pObj = pObj2;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 72))(pObj2);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
  sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, (int)this, 0);  // 调 实体对象注册到演播层
  pFxVt = *(uint32_t *)pObj2;
  nFrameOff = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);  // 结果 = 虚调用 vt+192
  nBaseY = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
  nBubbleY = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nBaseY + nFrameOff);  // 结果 = 虚调用 vt+124
  nPosY = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nArg3 + nBubbleY);  // 结果 = 虚调用 vt+120
  (*(void (/*thiscall*/ **)(int, int))(pFxVt + 112))(pObj, nArg2 + nPosY);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  nPosZ = (*(int (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
  sub_4A06D0(nPosZ, 2);  // 调 绑定目标对象并记录相对偏移
}



// ------------------------------------------------------------
// 0x4D8700 sub_4D8700
// 属性递减：新值 = 字段(this) − nArg2，写回（sub_41A5E0/sub_41A590 读/写器）。
// 返回新值。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8700(void *this, int nArg2)  // 头顶气泡 「Question.ani「（疑问；结构同上但少一层坐标补偿）
{
  int nNewVal; // esi
  int nPad; // edx —— sub_41A590 写器的占位实参（寄存器残影，值未使用）

  nNewVal = sub_41A5E0((unsigned int)this) - nArg2;  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)this, nPad, nNewVal);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return nNewVal;
}



// ------------------------------------------------------------
// 0x4D8730 sub_4D8730
// 时刻戳记录：this+6692 = 当前时钟 —— 即研究 §1.2 的"格挡时刻戳"字段
//（0x4D9F20 vt+548 写同一槽），0x4D8730 为无虚表直写版。返回时钟值。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8730(uint32_t *this)  // 实现：（0x4D9F20 vt+548 写同一槽），0x4D8730 为无虚表直写版。返回时钟值
{
  int result; // eax

  result = sub_699000((int)(this + 16));  // 【clock_now(clk)】
  *(this + 1673) = result;  // this+6692〔uUI6692〕
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
int /*thiscall*/ sub_4D8750(int *this)  // 实现：朝向决策（依据参照对象 vt+1813 的 x 比较得方向码 0/4）
{
  int pRefObj; // edi
  int nMyX; // ebx
  int nRefX; // eax
  bool bLt0; // sf
  bool bOvfl; // of
  int result; // eax
  int nDir; // ecx
  int nDirCopy; // edi

  (*(void (/*thiscall*/ **)(int *))(*this + 184))(this);  // 虚调用 vt+184
  pRefObj = *(this + 1813);  // this+7252〔pTarget7252〕
  nMyX = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
  nRefX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pRefObj + 120))(pRefObj);  // 调虚槽 +120：动画对象
  bOvfl = __OFSUB__(nMyX, nRefX);  // bOvfl = 调 __OFSUB__
  bLt0 = nMyX - nRefX < 0;
  result = *(this + 1639);  // 读 result = this+6556（大状态ID）
  nDir = bLt0 ^ bOvfl;
  nDirCopy = nDir;
  if ( result == 0 && nDir != 4 )  // 若 result == 0 与/或 nDir != 4
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, nDir);  // 虚调用 vt+148
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 144))(this, nDirCopy);  // 虚调用 vt+144
  }
  return result;  // result=this+6556 主状态镜像
}



// ------------------------------------------------------------
// 0x4D87B0 sub_4D87B0 —— 键盘方向键换算（vt+892 双轴下发）
// vt+308 本地玩家门 && this+200 大状态 0 && 非状态 16：nArg2/nArg3 = X/Y 轴键值
//（4 = 松开 → bDirFlag=0），vt+892(轴, 键值, 方向标志) 下发后取动画对象方向键槽
// sub_4A0650 除以 16/12 得栅格位移（0x4D9210 的键值换算同族）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D87B0(int *this, int nArg2, int nArg3)  // 实现：键盘方向键换算（vt+892 双轴下发）
{
  int nKeyX; // ebx
  int nKeyY; // edi
  int nHoldCnt; // eax
  int nKeyXRaw; // eax
  int pKeyCtx; // ecx
  int nKeyYRaw; // eax
  int pKeyCtx2; // ecx
  int *pSlotWalk; // ebx
  int nKeyXRaw2; // eax
  int pKeyCtx3; // ecx
  int nKeyYRaw2; // eax
  int pKeyCtx4; // ecx
  int i; // edi
  char bDirFlag; // [esp+4h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0  // 虚调用 vt+308
    && *(this + 50) == 0  // this+200〔nMainState(推断)〕
    && (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 776))(this, 16) == 0 )  // 虚调用 vt+776
  {
    bDirFlag = 1;
    if ( nArg2 == 4 || nArg3 == 4 )  // 若 nArg2 == 4 与/或 nArg3 == 4
      bDirFlag = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t, int, char))(*this + 892))(this, 0, nArg2, bDirFlag);  // 虚调用 vt+892
    (*(void (/*thiscall*/ **)(int *, int, int, char))(*this + 892))(this, 1, nArg3, bDirFlag);  // 虚调用 vt+892
    nKeyX = sub_4A0650(*(this + 28), 0) / 16;  // this+112〔pHostComp112〕
    nKeyY = sub_4A0650(*(this + 28), 1) / 12;  // this+112〔pHostComp112〕
    nHoldCnt = (*(int (/*thiscall*/ **)(int *))(*this + 436))(this);  // 结果 = 虚调用 vt+436
    if ( sub_58AD30(nKeyX, nKeyY, nHoldCnt > 0) == 1 )  // 可行走判定：网格值≠2 且（允许对角 或 网格值≠1）→ true
    {
      nKeyXRaw = sub_4A0650(*(this + 28), 0);  // this+112〔pHostComp112〕
      pKeyCtx = *(this + 28);  // 读 pKeyCtx = this+112（宿主组件）
      *(this + 2075) = nKeyXRaw;  // this+8300〔pHoldObj(推断)〕
      nKeyYRaw = sub_4A0650(pKeyCtx, 1);  // 调 与 0x4A0790 的 v10/v17/v20 读法完全一致 —— 同一族
      pKeyCtx2 = *(this + 28);  // 读 pKeyCtx2 = this+112（宿主组件）
      *(this + 2076) = nKeyYRaw;  // this+8304〔nHoldPosX(推断)〕
      *(this + 2077) = sub_4A0650(pKeyCtx2, 2);  // this+8308〔nHoldPosY(推断)〕
    }
    else
    {
      pSlotWalk = this + 2075;  // this+2075 pHoldObj
      if ( *(this + 2075) == -1 && *(this + 2076) == -1 && *(this + 2077) == -1 )  // this+8300〔pHoldObj(推断)〕等 3 字段
      {
        nKeyXRaw2 = sub_4A0650(*(this + 28), 0);  // this+112〔pHostComp112〕
        pKeyCtx3 = *(this + 28);  // 读 pKeyCtx3 = this+112（宿主组件）
        *pSlotWalk = nKeyXRaw2;  // pSlotWalk=this+2075 pHoldObj
        nKeyYRaw2 = sub_4A0650(pKeyCtx3, 1);  // 调 与 0x4A0790 的 v10/v17/v20 读法完全一致 —— 同一族
        pKeyCtx4 = *(this + 28);  // 读 pKeyCtx4 = this+112（宿主组件）
        *(this + 2076) = nKeyYRaw2;  // this+8304〔nHoldPosX(推断)〕
        *(this + 2077) = sub_4A0650(pKeyCtx4, 2);  // this+8308〔nHoldPosY(推断)〕
      }
      for ( i = 0; i < 3; ++i )  // 循环：i 从 0 递增到 3
        sub_498B00((float *)*(this + 28), i, *pSlotWalk++);  // 浮点属性条件写入（置 +124 与 +196）
    }
  }
}



// ------------------------------------------------------------
// 0x4D8920 sub_4D8920
// 转发垫片（stdcall 4 参 → sub_53FC10），固定返回 0。【推断】回调表占位/注册用。
// ------------------------------------------------------------
int /*stdcall*/ sub_4D8920(int nArg1, int nArg2, int nArg3, int nArg4)  // 实现：转发垫片（stdcall 4 参 → sub_53FC10），固定返回 0。(推断)回调表占位/注册用
{
  sub_53FC10(nArg1, nArg2, nArg3, nArg4);  // 调 批量广播器 vt+40 槽
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
int /*thiscall*/ sub_4D8950(uint32_t *this)  // 实现：技能活动帧 tick 主入口（本区最核心的逐帧驱动）
{
  int result; // eax
  int fld_e1639; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 结果 = 虚调用 vt+308
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 724))(this);  // 结果 = 虚调用 vt+724
    if ( (uint8_t)result == 0 )
    {
      if ( *(this + 1813) == 0 && sub_699000((int)(this + 1910)) >= *(this + 1816) + 1000  // 【clock_now(clk)】
        || *(this + 1813) != 0 && (uint8_t)sub_45E680(*(this + 1813)) == 0  // 对象表归属判定
        || *(this + 1813) != 0  // this+7252〔pTarget7252〕
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1244))(this, *(this + 1813)) == 0  // 虚调用 vt+1244
        || *(this + 1881) != 0 && sub_699000((int)(this + 1910)) >= *(this + 1881) + *(this + 1816) )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1236))(this);  // 虚调用 vt+1236
      }
      if ( sub_699000((int)(this + 1910)) - *(this + 1922) > 333 )  // 【clock_now(clk)】
      {
        fld_e1639 = *(this + 1639);  // 读 fld_e1639 = this+6556（大状态ID）
        if ( fld_e1639 != 3 && fld_e1639 != 4 && fld_e1639 != 8 && fld_e1639 != 9 && fld_e1639 != 5 )  // 若 fld_e1639 != 3 与/或 fld_e1639 != 4 与/或 fld_e1639 != 8
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1092))(this);  // 虚调用 vt+1092
        *(this + 1922) = sub_699000((int)(this + 1910));  // clock_now(clk)
      }
      if ( sub_699000((int)(this + 1910)) > *(this + 1818) )  // 【clock_now(clk)】
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1240))(this);  // 虚调用 vt+1240
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1228))(this);  // 虚调用 vt+1228
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1224))(this);  // 虚调用 vt+1224
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D8A80 sub_4D8A80
// 发呆（idle）检测：非 hold(16) 时，x/y/z（vt+120/124/128）任一变化就刷新
// this+7708 时刻戳；当反应主状态一致（vt+200 == 状态块 +4）、vt+840()==0 且
// 1000ms 无位移时：放 Question 气泡（0x4D8600）并把大状态切 21（vt+1104）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8A80(int *this)  // 实现：1000ms 无位移时：放 Question 气泡（0x4D8600）并把大状态切 21（vt+1104）
{
  int result; // eax
  int pStateBlk; // edi

  result = (*(int (/*thiscall*/ **)(int *, int))(*this + 776))(this, 16);  // 结果 = 虚调用 vt+776
  if ( (uint8_t)result == 0 )
  {
    if ( *(this + 1928) != (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) )  // 虚调用 vt+120
    {
      *(this + 1928) = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 虚调用 vt+120
      *(this + 1927) = sub_699000((int)(this + 1910));  // clock_now(clk)
    }
    if ( *(this + 1929) != (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) )  // 虚调用 vt+124
    {
      *(this + 1929) = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 虚调用 vt+124
      *(this + 1927) = sub_699000((int)(this + 1910));  // clock_now(clk)
    }
    if ( *(this + 1930) != (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) )  // 虚调用 vt+128
    {
      *(this + 1930) = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 虚调用 vt+128
      *(this + 1927) = sub_699000((int)(this + 1910));  // clock_now(clk)
    }
    pStateBlk = (*(int (/*thiscall*/ **)(int *))(*this + 688))(this);  // 结果 = 虚调用 vt+688
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) == *(uint32_t *)(pStateBlk + 4) )  // 虚调用 vt+200
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);  // 结果 = 虚调用 vt+840
      if ( result == 0 )
      {
        result = sub_699000((int)(this + 1910)) - *(this + 1927);  // 【clock_now(clk)】
        if ( result > 1000 )
        {
          sub_4D8600(this, 0, 0);  // 头顶气泡 ”Question.ani”（疑问；结构同上但少一层坐标补偿）
          (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 21);  // 虚调用 vt+1104
          result = sub_699000((int)(this + 1910));  // 【clock_now(clk)】
          *(this + 1927) = result;  // this+7708〔nIdleStamp〕
        }
      }
    }
    else
    {
      result = sub_699000((int)(this + 1910));  // 【clock_now(clk)】
      *(this + 1927) = result;  // this+7708〔nIdleStamp〕
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D8BB0 sub_4D8BB0
// 参照对象设置门：vt+1244 校验失败或目标 == 当前参照（this+7252）时返回 0；
// 否则经 vt+1152 正式设置并返回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D8BB0(uint32_t *this, int nArg2)  // 实现：否则经 vt+1152 正式设置并返回 1
{
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, nArg2) == 0 || *(this + 1813) == nArg2 )  // 虚调用 vt+1244
    return 0;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1152))(this, nArg2);  // 虚调用 vt+1152
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4D8BF0 sub_4D8BF0
// 告示包 type 7（本地玩家门）：打包 (vt+48, vt+52) 两字段 → vt+1084 本地收尾 →
// 发送 (0,-1)。【推断】位置/状态上报类。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8BF0(void *this)  // 实现：发送 (0,-1)。(推断)位置/状态上报类
{
  int result; // eax
  int pPktVt; // edi
  int pThis_30; // eax
  int pPktVt2; // edi
  int pThis_34; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 7, 1);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
    pPktVt = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    pThis_30 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, int))(pPktVt + 36))(dword_8F8520, pThis_30);  // 会话/UDP 管理器
    pPktVt2 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    pThis_34 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    (*(void (/*thiscall*/ **)(int, int))(pPktVt2 + 36))(dword_8F8520, pThis_34);  // 会话/UDP 管理器
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1084))(this);  // 调虚槽 +1084
    return (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D8C60 sub_4D8C60
// 技能时间窗同步包（上行）：先写本地玩家（dword_8F7C04）vt+52 的 id，再打包 6 个
// dword —— v12 = {+7272−now(动作结束倒计时), +7148, +7676, +7672, +7684, +7680}
// 共 24 字节。与 0x4D8CE0（下行回填）配对，为服务器校验的时间窗快照【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8C60(uint32_t *this)  // 实现：共 24 字节。与 0x4D8CE0（下行回填）配对，为服务器校验的时间窗快照(推断)
{
  int pPktVt; // edi
  int nLeaderId; // eax
  int nNow; // eax
  int nW1; // edx
  int nW0; // ecx
  int nW2; // eax
  int nW3; // ecx
  int nW5; // eax
  int nW4; // edx
  uint32_t nWindow[6]; // [esp+8h] [ebp-18h] BYREF —— 6×dword 时间窗快照（24 字节上行）

  pPktVt = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
  nLeaderId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 全局 dword_8F7C04 = 本机角色对象
  (*(void (/*thiscall*/ **)(int, int))(pPktVt + 36))(dword_8F8520, nLeaderId);  // 会话/UDP 管理器
  nNow = sub_699000((int)(this + 1910));  // 【clock_now(clk)】
  nW1 = *(this + 1787);  // 读 nW1 = this+7148（大状态镜像槽）
  nW0 = *(this + 1818) - nNow;
  nW2 = *(this + 1919);  // this+7676〔f_1DFC〕
  nWindow[0] = nW0;
  nW3 = *(this + 1918);  // this+7672〔f_1DF8〕
  nWindow[2] = nW2;  // nW2=this+7676 f_1DFC
  nW5 = *(this + 1920);
  nWindow[1] = nW1;  // nW1=this+7148 nBigState
  nW4 = *(this + 1921);
  nWindow[3] = nW3;  // nW3=this+7672 f_1DF8
  nWindow[5] = nW5;
  nWindow[4] = nW4;
  return (*(int (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, nWindow, 24);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
}



// ------------------------------------------------------------
// 0x4D8CE0 sub_4D8CE0
// 技能时间窗同步包（下行）：从包里读 1 个 word（vt+76），与 this+7260 关联对象
// 的 vt+52 id 匹配成功才读 24 字节（vt+88），并回填 this+7272 = 包[0] + 当前时钟
//（服务器校准后的动作结束时刻）。与 0x4D8C60 配对。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8CE0(uint32_t *this)  // 实现：（服务器校准后的动作结束时刻）。与 0x4D8C60 配对
{
  int result; // eax
  int pSyncPeer; // ecx
  int nNow; // eax
  uint32_t nRxBuf[6]; // [esp+4h] [ebp-1Ch] BYREF
  uint16_t nRxId; // [esp+1Ch] [ebp-4h] BYREF

  result = (*(int (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &nRxId);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
  pSyncPeer = *(this + 1815);  // pSyncPeer=this+7260 this
  if ( pSyncPeer != 0 )  // pSyncPeer=this+7260 this
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pSyncPeer + 52))(pSyncPeer);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    if ( result == nRxId )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 88))(dword_8F8520, nRxBuf, 24);  // 调虚槽 +88：CNRDPrivateStoreWindow__vmt58 槽（16 行）
      nNow = sub_699000((int)(this + 1910));  // 【clock_now(clk)】
      result = nRxBuf[0] + nNow;
      *(this + 1818) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D8D40 sub_4D8D40
// 告示包 type 32（本地玩家门 + this+7252 参照对象非空）：打包 (自身 vt+48/vt+52、
// 参照对象 vt+48/vt+52) 后发送 (1,-1)。【推断】跟随/锁定目标的位置播报。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8D40(int *this)  // 实现：参照对象 vt+48/vt+52) 后发送 (1,-1)。(推断)跟随/锁定目标的位置播报
{
  int result; // eax
  int pPktVt; // edi
  int nSelfX; // eax
  int pPktVt2; // edi
  int nSelfY; // eax
  int pPktVt3; // edi
  int nRefX; // eax
  int pRefObj; // ecx
  int pPktVt4; // esi
  int nRefY; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 结果 = 虚调用 vt+308
  if ( (uint8_t)result != 0 )
  {
    result = *(this + 1813);  // this+7252〔pTarget7252〕
    if ( result != 0 )  // 若结果非 0（成功）
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 32, 1);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
      pPktVt = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      nSelfX = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);  // 结果 = 虚调用 vt+48
      (*(void (/*thiscall*/ **)(int, int))(pPktVt + 36))(dword_8F8520, nSelfX);  // 会话/UDP 管理器
      pPktVt2 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      nSelfY = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);  // 结果 = 虚调用 vt+52
      (*(void (/*thiscall*/ **)(int, int))(pPktVt2 + 36))(dword_8F8520, nSelfY);  // 会话/UDP 管理器
      pPktVt3 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      nRefX = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 48))(*(this + 1813));  // this+7252〔pTarget7252〕
      (*(void (/*thiscall*/ **)(int, int))(pPktVt3 + 36))(dword_8F8520, nRefX);  // 会话/UDP 管理器
      pRefObj = *(this + 1813);  // this+7252〔pTarget7252〕
      pPktVt4 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      nRefY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pRefObj + 52))(pRefObj);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      (*(void (/*thiscall*/ **)(int, int))(pPktVt4 + 36))(dword_8F8520, nRefY);  // 会话/UDP 管理器
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    }
  }
  return result;  // result=this+7252 pTarget7252
}



// ------------------------------------------------------------
// 0x4D8DF0 sub_4D8DF0
// HP 变化请求（带 PVP 归属解析）：转调 HP setter 0x4D4D40(this, hpDelta=nArg4,
// force=nArg2, attacker=nArg4)；场景 3（PVP）且攻击者车主条件 273 成立时，在
// dword_8F850C+16 起 4 项槽表里找 +196==攻击者 的槽位号 nSlotIdx，发包 type 24
//（单字节标志 = vt+936 非零）。【推断】PVP 击杀/受击公告通道。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8DF0(uint32_t *this, int nArg2, char pszArg3, int nArg4)  // 实现：（单字节标志 = vt+936 非零）。(推断)PVP 击杀/受击公告通道
{
  int result; // eax
  int pObj; // eax
  int nSlotIdx; // esi
  int *pSlotWalk; // ecx
  int pPktVt; // ebx
  int nKillerFlag; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 结果 = 虚调用 vt+308
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 724))(this);  // 结果 = 虚调用 vt+724
    if ( (uint8_t)result == 0 )
    {
      result = sub_4D4D40(this, nArg4, (int)this, nArg2, pszArg3, nArg4);  // 【HP setter vt+728（§1.1；DLL 锚点 [13]）】
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )  // 全局 dword_8F7A24 = 登录/选区管理器
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 724))(this);  // 结果 = 虚调用 vt+724
        if ( (uint8_t)result != 0 && nArg4 != 0 )
        {
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 576))(nArg4);  // 调虚槽 +576
          if ( result != 0 )  // 若结果非 0（成功）
          {
            pObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 576))(nArg4);  // 调虚槽 +576
            result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
            if ( (uint8_t)result != 0 )
            {
              nSlotIdx = 0;
              for ( pSlotWalk = (int *)(dword_8F850C + 16); ; ++pSlotWalk )  // 房间/席位表
              {
                result = *pSlotWalk;
                if ( *pSlotWalk != 0 && *(uint32_t *)(result + 196) == nArg4 )
                  break;
                if ( ++nSlotIdx >= 4 )
                  return result;
              }
              (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 24, 0);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
              pPktVt = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
              nKillerFlag = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 936))(this);  // 结果 = 虚调用 vt+936
              LOBYTE(nKillerFlag) = (uint8_t)nKillerFlag != 0;  // 调 取 16 位值低 8 位
              (*(void (/*thiscall*/ **)(int, int))(pPktVt + 32))(dword_8F8520, nKillerFlag);  // 会话/UDP 管理器
              return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, nSlotIdx);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
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
// 关联对象切换（this+7260 = 当前关联/宿主对象指针，与下行包 0x4D8CE0 的 id 匹配字段
// 同槽）：a2 = 新对象。流程 = this+7668 记 now+2000（【推断】2 秒切换保护窗）→
// 新对象 ≠ 旧对象时：若新对象是本地玩家 dword_8F7C04，先取 vt+60() 快照缓冲，
// 把 +4 起 0x31 字节复制到 +53，再经 sub_49FFC0(buf, +102, +53, 1, 0) 登记一份
//（【推断】玩家侧数据快照/上报）；然后写 this+7260 = 新对象；若 this+7776 标志
// 未置 → 置 1 并调 vt+1116()（【推断】首次关联初始化）。返回 vt+1116() 或标志值。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D8F00(uint32_t *this, int nArg2)  // 实现：未置 → 置 1 并调 vt+1116()（(推断)首次关联初始化）。返回 vt+1116() 或标志值
{
  int nClockNow; // eax
  int pCurPeer; // ecx —— this+7260 当前关联对象
  int nNewPeer; // eax —— 新对象（兼作返回值）
  int pSnapBuf; // eax —— vt+60() 快照缓冲
  int pSnapB; // edi —— 快照缓冲 +102
  int pSnapA; // esi —— 快照缓冲 +53
  uint32_t *pSnapBuf2; // eax
  int nRet; // eax

  nClockNow = sub_699000((int)(this + 2));  // 【clock_now(clk)】
  pCurPeer = *(this + 1815);  // pCurPeer=this+7260 this
  *(this + 1917) = nClockNow + 2000;  // this+7668〔nSwitchGuardT〕
  nNewPeer = nArg2;
  if ( nArg2 != pCurPeer )  // pCurPeer=this+7260 this
  {
    if ( nArg2 == dword_8F7C04 && nArg2 != 0 )  // 全局 dword_8F7C04 = 本机角色对象
    {
      pSnapBuf = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 60))(this);  // 结果 = 虚调用 vt+60
      qmemcpy((void *)(pSnapBuf + 53), (const void *)(pSnapBuf + 4), 0x31u);  // 调 内存块拷贝(内联展开)
      pSnapA = pSnapBuf + 53;
      pSnapB = pSnapBuf + 102;
      pSnapBuf2 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 60))(this);  // 结果 = 虚调用 vt+60
      sub_49FFC0(pSnapBuf2, pSnapB, pSnapA, 1, 0);  // 播放尾帧处理（+48/+52/+40 → sub_49FA20 收尾）
      nNewPeer = nArg2;
    }
    *(this + 1815) = nNewPeer;
    LOBYTE(nNewPeer) = *((uint8_t *)this + 7776);  // this+7776〔bPeerInit〕
    if ( (uint8_t)nNewPeer == 0 )
    {
      nRet = *this;
      *((uint8_t *)this + 7776) = 1;  // this+7776〔bPeerInit〕
      LOBYTE(nNewPeer) = (*(int (/*thiscall*/ **)(uint32_t *))(nRet + 1116))(this);  // 调虚槽 +1116：IRDCharacter__vmt45C 默认虚槽桩（11 行 return）
    }
  }
  return nNewPeer;
}



// ------------------------------------------------------------
// 0x4D8F90 sub_4D8F90 —— vmt144 转发垫片（IRDActiveObject__vmt144 族）
// nArg2 == 0 时直调 sub_58E550(0,…)；否则先 sub_58E550(基实现) 再转发
// vt+1300(this, nArg3, nArg4)。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8F90(void *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：vmt144 转发垫片（IRDActiveObject__vmt144 族）
{
  if ( (uint8_t)nArg2 == 0 )
    return sub_58E550(0, nArg3, nArg4, nArg5);  // 【IRDActiveObject__vmt144】
  sub_58E550(nArg2, nArg3, nArg4, nArg5);  // 【IRDActiveObject__vmt144】
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 1300))(this, nArg3, nArg4);  // 调虚槽 +1300：CNSwordman__vmt514
}



// ------------------------------------------------------------
// 0x4D8FE0 sub_4D8FE0
// 视野/侦测值：状态 5（blind，研究 §10 枚举）激活时返回 10，否则返回 this+7520。
// 【推断】失明时把可视距离压到固定小值。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D8FE0(uint32_t *this)  // 实现：(推断)失明时把可视距离压到固定小值
{
  bool bNotBlind; // zf
  int result; // eax

  bNotBlind = (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 5) == 0;  // 结果 = 虚调用 vt+776
  result = 10;
  if ( bNotBlind )
    return *(this + 1880);  // this+7520〔nSightRange(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x4D9000 sub_4D9000
// 大状态白名单查询：this+7148 ∈ {5,6,7,9,10,11,12,24} 返回真。【推断】"允许被打断/
// 可交互"的大状态集合判定。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4D9000(uint32_t *this)  // 实现：可交互的大状态集合判定
{
  int nBigState; // eax  | +0x1BEC → ★大状态 ID（CNGhoulOilSellerOlrek；va=004DB480）

  nBigState = *(this + 1787);  // 读 fld_e1787 = this+7148（大状态镜像槽）
  return nBigState == 7 || nBigState == 5 || nBigState == 9 || nBigState == 10 || nBigState == 11 || nBigState == 12 || nBigState == 24 || nBigState == 6;  // fld_e1787=this+7148 nBigState
}



// ------------------------------------------------------------
// 0x4D9040 sub_4D9040
// 大状态切换（this+7148）：先 vt+1096(旧值) 通告 → 写新值 → vt+1100(新值) 通告；
// vt+620 子态不在 {1,2} 时尾调 vt+1240 收招。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9040(uint32_t *this, int nArg2)  // 实现：vt+620 子态不在 {1,2} 时尾调 vt+1240 收招
{
  int pVtbl; // edx —— *this 虚表（vt+1100 新值通告用）
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1096))(this, *(this + 1787));  // 虚调用 vt+1096
  pVtbl = *this;
  *(this + 1787) = nArg2;  // 写 this+7148 = nArg2（大状态镜像槽）
  (*(void (/*thiscall*/ **)(uint32_t *, int))(pVtbl + 1100))(this, nArg2);  // 虚函数调用 槽+1100
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 620))(this);  // 结果 = 虚调用 vt+620
  if ( result != 1 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 620))(this);  // 结果 = 虚调用 vt+620
    if ( result != 2 )
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1240))(this);  // 虚调用 vt+1240
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D90A0 sub_4D90A0
// 大状态联动事件分派：事件 4/9 → 先切大状态 13；事件 8 → 切 16；事件 5 → 要求
// vt+840()==11 且连调 vt+472 两次（12/0 号槽），否则直落默认；最终统一交给
// ·0x4D5200（事件包分派器）处理。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D90A0(uint8_t *this, int *pDwArg2)  // 实现：·0x4D5200（事件包分派器）处理
{
  int result; // eax

  switch ( *pDwArg2 )  // 按 *pDwArg2 分派
  {
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1104))(this, 13);  // 调虚槽 +1104
      result = sub_4D5200(this, pDwArg2);  // 调 （1/2）得 nMode 后走 vt+612(this, 开关==1, nMode)。细节语义未定案(待验证)
      break;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) != 11 )  // 调虚槽 +840：大状态 getter（this+6556）
        goto LABEL_7;
      (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 12, 0, 1, 1);  // 调虚槽 +472：IRDActiveObject__vmt1D8 主状态机（874 行）：CONDITION_…
      (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 0, 0, 1, 1);  // 调虚槽 +472：IRDActiveObject__vmt1D8 主状态机（874 行）：CONDITION_…
      result = sub_4D5200(this, pDwArg2);  // 调 （1/2）得 nMode 后走 vt+612(this, 开关==1, nMode)。细节语义未定案(待验证)
      break;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1104))(this, 16);  // 调虚槽 +1104
      result = sub_4D5200(this, pDwArg2);  // 调 （1/2）得 nMode 后走 vt+612(this, 开关==1, nMode)。细节语义未定案(待验证)
      break;
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1104))(this, 13);  // 调虚槽 +1104
      goto LABEL_7;
    default:
LABEL_7:
      result = sub_4D5200(this, pDwArg2);  // 调 （1/2）得 nMode 后走 vt+612(this, 开关==1, nMode)。细节语义未定案(待验证)
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D9170 sub_4D9170
// 对象移除时的引用清理（0x4D6E40 的壳 + 引用表清扫）：PVP 场景 3 且移除自身时
// 清场景对象 +40；this+7252/7248/7256 三处参照指针命中即清零，this+7260 命中走
// vt+1044(0)，this+8352 命中走 vt+1164(0)。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9170(uint32_t *this, int nArg2)  // 实现：vt+1044(0)，this+8352 命中走 vt+1164(0)
{
  int result; // eax

  result = sub_4D6E40(this, nArg2);  // 调 尾调 sub_53F8A0(nArg2)。0x4D6CA0 注释的 50% 预表现容器成员即条件 33 对象
  if ( (uint32_t *)nArg2 == this )
  {
    result = dword_8F7A24;  // 全局 dword_8F7A24 = 登录/选区管理器
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )  // 全局 dword_8F7A24 = 登录/选区管理器
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 64))(this);  // 结果 = 虚调用 vt+64
      *(uint8_t *)(result + 40) = 0;
    }
  }
  if ( *(this + 1813) == nArg2 )  // this+7252〔pTarget7252〕
    *(this + 1813) = 0;  // this+7252〔pTarget7252〕
  if ( *(this + 1812) == nArg2 )
    *(this + 1812) = 0;
  if ( *(this + 1814) == nArg2 )  // 判定 “+7256 光环状态”
    *(this + 1814) = 0;  // 写 this+7256 = 0（光环状态）
  if ( *(this + 1815) == nArg2 )
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1044))(this, 0);  // 结果 = 虚调用 vt+1044
  if ( *(this + 2088) == nArg2 )  // 判定 “+8352 骑乘/宿主槽”
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1164))(this, 0);  // 虚调用 vt+1164
  return result;
}



// ------------------------------------------------------------
// 0x4D9200 sub_4D9200
// 转发垫片（stdcall）→ 0x4D58E0（nArg1 >= 0 判定回调）。
// ------------------------------------------------------------
BOOL /*stdcall*/ sub_4D9200(int nArg1)  // 实现：转发垫片（stdcall）→ 0x4D58E0（nArg1 >= 0 判定回调）
{
  return sub_4D58E0(nArg1);  // 返回 小比较回调（stdcall）：返回 nArg1 >= 0（排序/过滤族回调，(推断)qsort 谓词）
}



// ------------------------------------------------------------
// 0x4D9210 sub_4D9210
// 位移尝试（键盘走位）：hold(16) 时只认 vt+840()==5；sub_58AD30(nArg2/16,
// nArg3/12, vt+436>0) 门（与 0x4D87B0 的键值换算同族）通过后：保存动画对象
// +4/+8/+12 三轴并置 +108=0，vt+112 试移，动画帧表 +32/+36 暂置 1 后回填原值，
// uArg4 非空回填 0。成功 true。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4D9210(uint32_t *this, int nArg2, int nArg3, uint32_t *uArg4)  // 实现：uArg4 非空回填 0。成功 true
{
  uint32_t *pAnim; // eax —— 动画对象（this+112）
  int pVtbl; // ebx —— *this 虚表（vt+112 试移用）
  int nZ; // eax —— vt+128() 第三轴
  int nSaveX; // edi —— 动画 +32 暂存
  int nSaveY; // ebx —— 动画 +36 暂存
  int nAxis1; // [esp+4h] [ebp-10h] —— 动画 +4 快照
  int nAxis2; // [esp+8h] [ebp-Ch] —— 动画 +8 快照
  int nAxis3; // [esp+Ch] [ebp-8h] —— 动画 +12 快照
  char bHasTarget; // [esp+10h] [ebp-4h] —— vt+436()>0

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 16) != 0 )  // 虚调用 vt+776
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 5;  // 虚调用 vt+840
  bHasTarget = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 436))(this) > 0;  // 结果 = 虚调用 vt+436
  if ( sub_58AD30(nArg2 / 16, nArg3 / 12, bHasTarget) == 0 )  // 可行走判定：网格值≠2 且（允许对角 或 网格值≠1）→ true
    return false;
  if ( uArg4 != nullptr )  // 若 uArg4 有效（非空）
    *uArg4 = 0;
  if ( *(this + 29) != 0 )  // 判定 “+116 观察者容器”
  {
    pAnim = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
    pVtbl = *this;
    nAxis1 = pAnim[1];  // pAnim=this+112 pHostComp112
    nAxis2 = pAnim[2];  // pAnim=this+112 pHostComp112
    nAxis3 = pAnim[3];  // pAnim=this+112 pHostComp112
    nZ = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 结果 = 虚调用 vt+128
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(pVtbl + 112))(this, nArg2, nArg3, nZ);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    *(uint8_t *)(*(this + 28) + 108) = 0;  // this+112〔pHostComp112〕
    nSaveX = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 32);  // 结果 = 虚调用 vt+340
    nSaveY = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 36);  // 结果 = 虚调用 vt+340
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 32) = 1;  // 虚调用 vt+340
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 36) = 1;  // 虚调用 vt+340
    *(uint32_t *)(*(this + 28) + 4) = nAxis1;  // this+112〔pHostComp112〕
    *(uint32_t *)(*(this + 28) + 8) = nAxis2;  // this+112〔pHostComp112〕
    *(uint32_t *)(*(this + 28) + 12) = nAxis3;  // this+112〔pHostComp112〕
    *(uint8_t *)(*(this + 28) + 108) = 1;  // this+112〔pHostComp112〕
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 32) = nSaveX;  // 虚调用 vt+340
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 36) = nSaveY;  // 虚调用 vt+340
  }
  return true;
}



// ------------------------------------------------------------
// 0x4D9360 sub_4D9360
// 属性 +466 计数加 nDelta（this+7560），伴随 vt+612(1,1) 切换 —— 与 0x4D93D0
// （减、vt+612(0,0)）成对的增益开关；尾调 vt+676(0) 广播。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9360(uint32_t *this)  // 实现：（减、vt+612(0,0)）成对的增益开关；尾调 vt+676(0) 广播
{
  int result; // eax
  int nDelta; // ebx
  unsigned int pStatPtr; // edi
  int nCurVal; // eax
  int nPad; // edx —— sub_41A590 写器占位实参（寄存器残影）

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 616))(this) == 0  // 虚调用 vt+616
    || (result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 620))(this)) != 1 )  // 虚调用 vt+620
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 612))(this, 1, 1);  // 虚调用 vt+612
    nDelta = *(this + 1890);
    pStatPtr = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 466;  // 结果 = 虚调用 vt+672
    nCurVal = sub_41A5E0(pStatPtr);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pStatPtr, nPad, nDelta + nCurVal);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 虚调用 vt+676
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D93D0 sub_4D93D0
// 属性 +466 计数减 nDelta（0x4D9360 的对偶），vt+612(0,0) 切换回，尾调 vt+676(0)。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D93D0(uint32_t *this)  // 实现：属性 +466 计数减 nDelta（0x4D9360 的对偶），vt+612(0,0) 切换回，尾调 vt+676(0)
{
  int result; // eax
  int nDelta; // ebx
  unsigned int pStatPtr; // edi
  int nCurVal; // eax
  int nPad; // edx —— sub_41A590 写器占位实参（寄存器残影）

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 616))(this) == 1  // 虚调用 vt+616
    || (result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 620))(this)) == 1 )  // 虚调用 vt+620
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 612))(this, 0, 0);  // 虚调用 vt+612
    nDelta = *(this + 1890);
    pStatPtr = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 466;  // 结果 = 虚调用 vt+672
    nCurVal = sub_41A5E0(pStatPtr);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pStatPtr, nPad, nCurVal - nDelta);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 虚调用 vt+676
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D9440 sub_4D9440
// PVP 受击随机表现：场景 3 且 this+7772==3 时 rand()%100 < 30 →
// sub_4E4A50(this, 30022, 0, x, y, 0, vt+152, 0,0,0)。【推断】30% 概率的受击
// 附加表现（30022 = 表现资源 id）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9440(uint32_t *this)  // 实现：附加表现（30022 = 表现资源 id）
{
  int result; // eax
  int nRand; // eax
  int nPct; // et2
  int nPosX; // eax
  int nPosY; // [esp-18h] [ebp-1Ch]
  int nDirArg; // [esp-10h] [ebp-14h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 结果 = 虚调用 vt+308
  if ( (uint8_t)result != 0 && *(this + 1943) == 3 )  // 判定 “+7772 反击态”
  {
    nRand = rand();  // nRand = 调 rand
    nPct = nRand % 100;
    result = nRand / 100;
    if ( nPct < 30 )
    {
      nDirArg = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 结果 = 虚调用 vt+152
      nPosY = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
      nPosX = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
      return sub_4E4A50(this, 30022, 0, nPosX, nPosY, 0, nDirArg, 0, 0, 0);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D94A0 sub_4D94A0 —— 拾取信息快照读写（this+8360 的 7 字节对象）
// pArg2 非空：懒创建 7 字节对象后拷入 7 字节（dword+word+byte）；空则释放。
// 对象首字节非零时把 this+8352 写入 this+668/+672（【推断】拾取目标坐标缓存）
// 并把 uArg3 存 this+8356。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4D94A0(int this, int pArg2, uint8_t *uArg3)  // 拾取信息快照读写（this+8360 的 7 字节对象）
{
  char *pMem; // eax
  int pPickInfo8360; // eax  | +0x20A8 → 拾取信息 7 字节对象指针（4D94A0 懒创建/释放）【推断】（证据 va=004D94A0）（CNGhoulOilSellerOlrek；va=004D94A0）
  uint8_t *result; // eax
  int nRideHost8352; // edx  | +0x20A0 → 骑乘/宿主槽（★全库通用 this+8352）（证据 va=004D94A0）（CNGhoulOilSellerOlrek；va=004D94A0）

  if ( pArg2 != 0 )
  {
    if ( *(uint32_t *)(this + 8360) == 0 )  // 判定 “+8360 拾取信息 7 字节对象指针”
    {
      pMem = (char *)operator new(7u);  // 堆分配 7 字节对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
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
      *(uint32_t *)(this + 8360) = pMem;  // 写 this+8360 = pMem（拾取信息 7 字节对象指针）
    }
    pPickInfo8360 = *(uint32_t *)(this + 8360);  // 读 fld_20A8 = this+8360（拾取信息 7 字节对象指针）
    *(uint32_t *)pPickInfo8360 = *(uint32_t *)pArg2;  // fld_20A8=this+8360 pPickInfo8360
    *(uint16_t *)(pPickInfo8360 + 4) = *(uint16_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    *(uint8_t *)(pPickInfo8360 + 6) = *(uint8_t *)(pArg2 + 6);  // fld_20A8=this+8360 pPickInfo8360
  }
  else
  {
    if ( *(uint32_t *)(this + 8360) != 0 )  // 判定 “+8360 拾取信息 7 字节对象指针”
      j__free(*(void **)(this + 8360));  // 释放 this+8360〔pPickInfo8360(推断)〕堆块
    *(uint32_t *)(this + 8360) = 0;  // 写 this+8360 = 0（拾取信息 7 字节对象指针）
  }
  result = *(uint8_t **)(this + 8360);  // this+8360 拾取信息 7 字节对象指针
  if ( result != nullptr )  // 若 result 有效（非空）
  {
    if ( *result != 0 )  // result=this+8360 pPickInfo8360
    {
      nRideHost8352 = *(uint32_t *)(this + 8352);  // 读 fld_20A0 = this+8352（骑乘/宿主槽）
      result = uArg3;  // result=this+8360 pPickInfo8360
      *(uint32_t *)(this + 672) = 1;  // 写 this+672 = 1（拾取/交互目标有效标志）
      *(uint32_t *)(this + 668) = nRideHost8352;  // 写 this+668 = fld_20A0（拾取/交互目标坐标缓存）
    }
    *(uint32_t *)(this + 8356) = uArg3;  // 写 this+8356 = uArg3（拾取信息槽 B）
  }
  else
  {
    *(uint32_t *)(this + 8356) = uArg3;  // 写 this+8356 = uArg3（拾取信息槽 B）
  }
  return result;  // result=this+8360 pPickInfo8360
}



// ------------------------------------------------------------
// 0x4D9570 sub_4D9570
// 目标交互/拾取启动（【推断】：nArg2=1 且 nArg4=8 时 new 8 字节把 pArg3 双 dword
// 存入 this+7820 —— 疑为交互对象信息快照；随后 vt+436()>0 有目标时经 vt+124/vt+120
// 换算坐标走 vt+112 试移；尾调 sub_49C620(1,1,0) + sub_49C5F0(1,0,0,1000ms)）。
// vt+320 为交互前置通知。语义全链未定案【待验证】。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9570(int *this, int nArg2, uint32_t *pArg3, int nArg4)  // 实现：vt+320 为交互前置通知。语义全链未定案(待验证)
{
  uint32_t *pPickInfo; // eax —— new 8 字节的交互信息对象
  int pVtbl; // edi
  int nTargetId; // eax —— vt+436() 目标 id
  int nPosY; // eax
  int nPosX; // eax

  (*(void (/*thiscall*/ **)(int *))(*this + 320))(this);  // 虚调用 vt+320
  if ( nArg2 == 1 && nArg4 == 8 )  // 若 nArg2 == 1 与/或 nArg4 == 8
  {
    pPickInfo = operator new(8u);  // 堆分配 8 字节对象
    *(this + 1955) = (int)pPickInfo;  // this+7820〔pInteractSnap(推断)〕
    *pPickInfo = *pArg3;
    pPickInfo[1] = pArg3[1];  // pPickInfo[1] = 取 pArg3[1]
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 436))(this) > 0 )  // 虚调用 vt+436
  {
    pVtbl = *this;
    nTargetId = (*(int (/*thiscall*/ **)(int *))(*this + 436))(this);  // 结果 = 虚调用 vt+436
    nPosY = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, nTargetId);  // 结果 = 虚调用 vt+124
    nPosX = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, nPosY);  // 结果 = 虚调用 vt+120
    (*(void (/*thiscall*/ **)(int *, int))(pVtbl + 112))(this, nPosX);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  }
  sub_49C620(this, 1, 1, 0);  // 命令下发包装（组 id = this+4，值重复两遍）
  return sub_49C5F0(this, 1, 0, 0, 1000);  // 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
}



// ------------------------------------------------------------
// 0x4D9600 sub_4D9600 —— 交互收尾（this+7820 的 8 字节信息消费）
// this+1955（0x4D9570 存入的交互信息）非空时：vt+472(11,0,1,1) + 两次 vt+219
//（X/Y 双轴 0 归位）+ vt+224（+6/+7 字节），sub_495890(2,0)、sub_4A0550 动画
// 定位（+8 dword），sub_49C5F0(5,0,0,1000) 后 free 并清指针。【推断】拾取完成落地。
// ------------------------------------------------------------
void /*thiscall*/ sub_4D9600(int16_t **this)  // 实现：交互收尾（this+7820 的 8 字节信息消费）
{
  if ( *(this + 1955) != nullptr )  // this+7820〔pInteractSnap(推断)〕
  {
    (*((void (/*thiscall*/ **)(int16_t **, int, uint32_t, int, int))*this + 118))(this, 11, 0, 1, 1);  // 虚调用 vt+118
    (*((void (/*thiscall*/ **)(int16_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))*this + 219))(  // 虚调用 vt+219
      this,
      0,
      **(this + 1955),  // this+1955 pInteractSnap
      **(this + 1955),  // this+1955 pInteractSnap
      0,
      0,
      0);
    (*((void (/*thiscall*/ **)(int16_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))*this + 219))(  // 虚调用 vt+219
      this,
      1,
      (*(this + 1955))[1],  // this+1955 pInteractSnap
      (*(this + 1955))[1],  // this+1955 pInteractSnap
      0,
      0,
      0);
    (*((void (/*thiscall*/ **)(int16_t **, uint32_t, uint32_t))*this + 224))(  // 虚调用 vt+224
      this,
      *((uint8_t *)*(this + 1955) + 6),  // this+1955 pInteractSnap
      *((uint8_t *)*(this + 1955) + 7));  // this+7820〔pInteractSnap(推断)〕
    sub_495890((int *)this, 2, 0);  // 模式选择式方位设置（1/2/其他 三分支）
    sub_4A0550((float *)*(this + 28), (*(this + 1955))[2]);  // this+112〔pHostComp112〕
    sub_49C5F0((int *)this, 5, 0, 0, 1000);  // 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
    if ( *(this + 1955) != nullptr )  // this+7820〔pInteractSnap(推断)〕
      j__free(*(this + 1955));  // this+7820〔pInteractSnap(推断)〕
    *(this + 1955) = nullptr;  // this+7820〔pInteractSnap(推断)〕
  }
}



// ------------------------------------------------------------
// 0x4D96D0 sub_4D96D0
// 播种随机 + 大状态切换：取播报管理器（dword_8F8520→vt+120()）的 +112/+116，
// 与本对象 vt+120()/vt+52()/vt+124() 的返回值组合成种子 srand((F116+Y)*(F112+X+52))
// 并丢弃一次 rand()；再按 this+7772（word 下标 1943，同 0x4D9440 的场景字段）==3
// 切大状态 15，否则 13（vt+1104）。【推断】入场/重生时的位置相关随机化 + 状态复位。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D96D0(uint32_t *this)  // 实现：切大状态 15，否则 13（vt+1104）。(推断)入场/重生时的位置相关随机化 + 状态复位
{
  int nMgrF112; // edi —— 管理器数据块 +112
  int nPosX; // ebx —— vt+120() 自身 X
  int nSeedA; // ebx —— (F112 + X + vt+52()) 乘法左项
  int nPosY; // eax —— vt+124() 自身 Y
  int nMgrF116; // [esp+10h] [ebp-4h] —— 管理器数据块 +116

  nMgrF112 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);  // 调虚槽 +120：动画对象
  nMgrF116 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);  // 调虚槽 +120：动画对象
  nPosX = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
  nSeedA = nMgrF112 + nPosX + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);  // 结果 = 虚调用 vt+52
  nPosY = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
  srand((nMgrF116 + nPosY) * nSeedA);  // 调 设置随机种子
  rand();  // 调 取伪随机数
  if ( *(this + 1943) == 3 )  // 判定 “+7772 反击态”
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);  // 虚调用 vt+1104
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);  // 虚调用 vt+1104
}



// ------------------------------------------------------------
// 0x4D9760 sub_4D9760 —— 观察者广播后条件收尾
// 先调 0x4D5C50（18 观察者 vt+160 广播），再取 vt+48() 条件：== 529（受击态族）
// 时调 vt+656()（【推断】受击后置收尾）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9760(uint32_t *this)  // 实现：观察者广播后条件收尾
{
  int result; // eax

  sub_4D5C50(this);  // 调 vt+160()，尾调 sub_53F8F0(this+6296)（与 0x4D4CE0 的 sub_53F7A0 同区收束）
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);  // 结果 = 虚调用 vt+48
  if ( result == 529 )
    return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 656))(this);  // 虚调用 vt+656
  return result;
}



// ------------------------------------------------------------
// 0x4D9790 sub_4D9790 —— 坐标窗口直写（vt+1288/vt+1292 对）
// vt+1288(this, nArg5, nArg4) 前置，nArg2/nArg3 != -2 时分别写 this+7632/7636
//（X/Y 窗口，-2 = 保持不变），尾调 vt+1292(this, nArg3, nArg2)。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9790(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：坐标窗口直写（vt+1288/vt+1292 对）
{
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1288))(this, nArg5, nArg4);  // 虚调用 vt+1288
  if ( nArg2 != -2 )
    *(this + 1908) = nArg2;  // this+7632〔uWindow7632(推断)〕
  if ( nArg3 != -2 )
    *(this + 1909) = nArg3;  // this+7636〔nPosWinY〕
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1292))(this, nArg3, nArg2);  // 虚调用 vt+1292
}



// ------------------------------------------------------------
// 0x4D97E0 sub_4D97E0 —— 动作子对象状态槽直写
// 取 vt+1032() 动作数据块的 +20 旧值后写 nArg2，+32 记 clock_now(this+7640)，
// 尾调 vt+1184(this, 新值, 旧值) 通告。【推断】动作/姿态切换（研究 §4.2 的动作子对象侧）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D97E0(void *this, int nArg2)  // 实现：动作子对象状态槽直写
{
  int pThis_14; // edi
  int pThis_1DD8; // ebx

  pThis_14 = *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1032))(this) + 20);  // 调虚槽 +1032
  *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1032))(this) + 20) = nArg2;  // 调虚槽 +1032
  pThis_1DD8 = sub_699000((int)this + 7640);  // 【clock_now(clk)】
  *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1032))(this) + 32) = pThis_1DD8;  // 调虚槽 +1032
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 1184))(this, nArg2, pThis_14);  // 调虚槽 +1184
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
uint8_t /*thiscall*/ sub_4D9840(int *this, int nArg2, uint32_t **uArg3, int nArg4)  // 实现：主状态写入器包装器（研究 20 §4.2 定案）
{
  int fld_e50; // ebx
  uint8_t result; // al

  fld_e50 = *(this + 50);  // this+200〔nMainState(推断)〕
  result = (uint8_t)sub_49A320(this, nArg2, uArg3, nArg4);  // 结果 = 播放状态切换（+50/+51/+52 位组、子链级联、特效槽 +40）
  if ( fld_e50 != nArg2 )  // fld_e50=this+200 nMainState
  {
    if ( fld_e50 >= 1 )  // fld_e50=this+200 nMainState
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
// ★ 副本难度系数施加（日志标签 aApplydifficult 可证）：宿主对象（pArg1[2088] 车主）
// 处于条件 273（受击/在场）时，按全局难度下标 dword_99FB8C（0..3）从 11 张 4 元素
// float 表取系数，对属性块批量修正：+466 += 表、+4(最大HP) ×表、HP 写回 vt+732、
// +7520/+7592 += 表、16 个技能条目（+284 步长 14 dword）各 += 表、+844 ×表、
// +816 += 表、物理/魔法攻击 (+1012/+1068) ×表、防/魔防 (+1040/+1096) ×表、
// +900 += 表，最后把表值写 this+8472。off_77F3FC("Applydifficult", 旧, 新) 记日志。
// pArg1 无车主或车主不在场 → 只做 +466/+4/HP/技能/其余同样的修正（另一分支同表）。
// ------------------------------------------------------------
int /*usercall*/ sub_4D98A0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：pArg1 无车主或车主不在场 → 只做 +466/+4/HP/技能/其余同样的修正（另一分支同表）
{
  int pObj; // ecx
  uint64_t nRet; // rax
  int nDiffIdx; // edi
  unsigned int pStat466; // ebx
  int nStat466; // eax
  double fCoef466; // st7
  unsigned int pStatHp; // ebx
  uint64_t nHpNew; // rax
  int pVt; // ebx
  int nMaxHp2; // eax
  int nMaxHp; // eax
  double fCoef7592; // st7
  int nOff; // ebx
  unsigned int pSkillPtr; // ebx
  int nSkillVal; // eax
  double fCoefSkill; // st7
  unsigned int pStat844; // ebx
  uint64_t n844New; // rax
  unsigned int pStat816; // ebx
  int n816Val; // eax
  double fCoef816; // st7
  unsigned int pStatAtk; // ebx
  uint64_t nAtkNew; // rax
  unsigned int pStatMatk; // ebx
  uint64_t nMatkNew; // rax
  unsigned int pStatDef; // ebx
  uint64_t nDefNew; // rax
  unsigned int pStatMdef; // ebx
  uint64_t nMdefNew; // rax
  unsigned int pStat900; // ebx
  int n900Val; // eax
  double fCoef900; // st7
  uint32_t tab8472Set[4]; // [esp+4h] [ebp-BCh]
  uint32_t tab7592Add[4]; // [esp+14h] [ebp-ACh]
  uint32_t tab900Add[4]; // [esp+24h] [ebp-9Ch]
  uint32_t tab466Add[4]; // [esp+34h] [ebp-8Ch]
  uint32_t tab816Add[4]; // [esp+44h] [ebp-7Ch]
  uint32_t tab7520Add[4]; // [esp+54h] [ebp-6Ch]
  uint32_t tab844Mul[4]; // [esp+64h] [ebp-5Ch]
  uint32_t tabSkillAdd[4]; // [esp+74h] [ebp-4Ch]
  uint32_t tabHpMul[4]; // [esp+84h] [ebp-3Ch]
  uint32_t tabDefMul[4]; // [esp+94h] [ebp-2Ch]
  uint32_t tabAtkMul[4]; // [esp+A4h] [ebp-1Ch]
  char nLoopIdx[4]; // [esp+B4h] [ebp-Ch]
  int nScratch; // [esp+B8h] [ebp-8h]
  int nStatVal; // [esp+BCh] [ebp-4h] —— sub_41A5E0 读出的当前属性值（防篡读中转）

  pObj = pArg1[2088];
  tab466Add[0] = 0;
  tab466Add[1] = 1092616192;  // 常量 10.0f
  tab466Add[2] = 1101004800;  // 常量 20.0f
  tab466Add[3] = 1114636288;  // 常量 60.0f
  tabHpMul[0] = 1065353216;  // 常量 1.0f
  tabHpMul[1] = 1069547520;  // 常量 1.5f
  tabHpMul[2] = 1072064102;
  tabHpMul[3] = 1075838976;
  tab7592Add[0] = 0;
  tab7592Add[1] = 1084227584;  // 常量 5.0f
  tab7592Add[2] = 1092616192;  // 常量 10.0f
  tab7592Add[3] = 1101004800;  // 常量 20.0f
  tab7520Add[0] = 0;
  tab7520Add[1] = 1106247680;  // 常量 30.0f
  tab7520Add[2] = 1114636288;  // 常量 60.0f
  tab7520Add[3] = 1125515264;
  tab844Mul[0] = 1065353216;  // 常量 1.0f
  tab844Mul[1] = 1065772646;
  tab844Mul[2] = 1066192077;
  tab844Mul[3] = 1067030938;
  tab816Add[0] = 0;
  tab816Add[1] = 1106247680;  // 常量 30.0f
  tab816Add[2] = 1112014848;  // 常量 50.0f
  tab816Add[3] = 1120403456;  // 常量 100.0f
  tabSkillAdd[0] = 0;
  tabSkillAdd[1] = 1084227584;  // 常量 5.0f
  tabSkillAdd[2] = 1092616192;  // 常量 10.0f
  tabSkillAdd[3] = 1106247680;  // 常量 30.0f
  tabAtkMul[0] = 1065353216;  // 常量 1.0f
  tabAtkMul[1] = 1065772646;
  tabAtkMul[2] = 1066192077;
  tabAtkMul[3] = 1067030938;
  tabDefMul[0] = 1065353216;  // 常量 1.0f
  tabDefMul[1] = 1066192077;
  tabDefMul[2] = 1066611507;
  tabDefMul[3] = 1067869798;
  tab900Add[0] = 0;
  tab900Add[1] = 1120403456;  // 常量 100.0f
  tab900Add[2] = 1128792064;
  tab900Add[3] = 1133903872;  // 常量 180.0f
  tab8472Set[0] = 0;
  tab8472Set[1] = 1101004800;  // 常量 20.0f
  tab8472Set[2] = 1106247680;  // 常量 30.0f
  tab8472Set[3] = 1116471296;
  if ( pObj == 0 || (LODWORD(nRet) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273), (uint8_t)nRet == 0) )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    nDiffIdx = dword_99FB8C;  // 触发条件评估器：遍历条件对象
    pStat466 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, int))(*pArg1 + 672))(pArg1, 0, nArg3, nArg2) + 466;  // 结果 = 虚调用 vt+672
    nStat466 = sub_41A5E0(pStat466);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    fCoef466 = *(float *)&tab466Add[nDiffIdx];
    nScratch = nStat466;
    sub_41A590(pStat466, (uint64_t)fCoef466 >> 32, nStat466 + (uint64_t)fCoef466);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 676))(pArg1, 0);  // 虚调用 vt+676
    *(uint32_t *)nLoopIdx = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1);  // 虚调用 vt+740
    pStatHp = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 4;  // 结果 = 虚调用 vt+672
    nScratch = sub_41A5E0(pStatHp);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    nHpNew = (uint64_t)((double)nScratch * *(float *)&tabHpMul[nDiffIdx]);
    sub_41A590(pStatHp, SHIDWORD(nHpNew), nHpNew);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 676))(pArg1, 0);  // 虚调用 vt+676
    pVt = *pArg1;
    nMaxHp2 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 740))(pArg1, 0, 1);  // 结果 = 虚调用 vt+740
    (*(void (/*thiscall*/ **)(uint32_t *, int))(pVt + 732))(pArg1, nMaxHp2);  // 调虚槽 +732：CNMapObject__vmt2DC
    nMaxHp = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1);  // 结果 = 虚调用 vt+740
    off_77F3FC(aApplydifficult, *(uint32_t *)nLoopIdx, nMaxHp);  // 引擎日志输出函数(printf 风格)
    fCoef7592 = *(float *)&tab7592Add[nDiffIdx];
    pArg1[1880] += (uint64_t)*(float *)&tab7520Add[nDiffIdx];
    nOff = 0;
    pArg1[1898] += (uint64_t)fCoef7592;
    *(uint32_t *)nLoopIdx = 0;  // *nLoopIdx = 0
    nScratch = 0;
    do
    {
      if ( sub_497040(*(uint32_t *)nLoopIdx) != 17 )  // 状态号映射表（12 直通、14→15、15→16，其余→17）
      {
        pSkillPtr = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + nOff + 284;  // 结果 = 虚调用 vt+672
        nSkillVal = sub_41A5E0(pSkillPtr);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        fCoefSkill = *(float *)&tabSkillAdd[nDiffIdx];
        nStatVal = nSkillVal;
        sub_41A590(pSkillPtr, (uint64_t)fCoefSkill >> 32, nSkillVal + (uint64_t)fCoefSkill);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        nOff = nScratch;
      }
      nOff += 14;
      ++*(uint32_t *)nLoopIdx;
      nScratch = nOff;
    }
    while ( nOff < 224 );
    pStat844 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 844;  // 结果 = 虚调用 vt+672
    nStatVal = sub_41A5E0(pStat844);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    n844New = (uint64_t)((double)nStatVal * *(float *)&tab844Mul[nDiffIdx]);
    sub_41A590(pStat844, SHIDWORD(n844New), n844New);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pStat816 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 816;  // 结果 = 虚调用 vt+672
    n816Val = sub_41A5E0(pStat816);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    fCoef816 = *(float *)&tab816Add[nDiffIdx];
    nStatVal = n816Val;
    sub_41A590(pStat816, (uint64_t)fCoef816 >> 32, n816Val + (uint64_t)fCoef816);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pStatAtk = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 1012;  // 结果 = 虚调用 vt+672
    nStatVal = sub_41A5E0(pStatAtk);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    nAtkNew = (uint64_t)((double)nStatVal * *(float *)&tabAtkMul[nDiffIdx]);
    sub_41A590(pStatAtk, SHIDWORD(nAtkNew), nAtkNew);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pStatMatk = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 1068;  // 结果 = 虚调用 vt+672
    nStatVal = sub_41A5E0(pStatMatk);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    nMatkNew = (uint64_t)((double)nStatVal * *(float *)&tabAtkMul[nDiffIdx]);
    sub_41A590(pStatMatk, SHIDWORD(nMatkNew), nMatkNew);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pStatDef = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 1040;  // 结果 = 虚调用 vt+672
    nStatVal = sub_41A5E0(pStatDef);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    nDefNew = (uint64_t)((double)nStatVal * *(float *)&tabDefMul[nDiffIdx]);
    sub_41A590(pStatDef, SHIDWORD(nDefNew), nDefNew);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pStatMdef = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 1096;  // 结果 = 虚调用 vt+672
    nStatVal = sub_41A5E0(pStatMdef);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    nMdefNew = (uint64_t)((double)nStatVal * *(float *)&tabDefMul[nDiffIdx]);
    sub_41A590(pStatMdef, SHIDWORD(nMdefNew), nMdefNew);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pStat900 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0) + 900;  // 结果 = 虚调用 vt+672
    n900Val = sub_41A5E0(pStat900);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    fCoef900 = *(float *)&tab900Add[nDiffIdx];
    nStatVal = n900Val;
    sub_41A590(pStat900, (uint64_t)fCoef900 >> 32, n900Val + (uint64_t)fCoef900);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 676))(pArg1, 0);  // 虚调用 vt+676
    nRet = (uint64_t)*(float *)&tab8472Set[nDiffIdx];
    *((uint64_t *)pArg1 + 1059) = (unsigned int)nRet;
  }
  return nRet;
}


// ------------------------------------------------------------
// 0x4D9D10 sub_4D9D10
// PVP 环境三重判定：this+7772==3（对象侧场景 3）&& 全局 dword_8F7A24+12==3 &&
// this+6180（技能槽非空）。返回 BOOL。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4D9D10(uint32_t *this)  // 实现：this+6180（技能槽非空）。返回 BOOL
{
  return *(this + 1943) == 3 && *(uint32_t *)(dword_8F7A24 + 12) == 3 && *(this + 1545) != 0;  // 全局 dword_8F7A24 = 登录/选区管理器
}



// ------------------------------------------------------------
// 0x4D9D40 sub_4D9D40
// 挂接标志写入（this+624）：vt+1020 为 0 或 pszArg2 显式置位 → 直接写；
// 否则走 vt+700 拆除 + sub_53F6A0 收尾路径。【推断】宿主/附属物挂接开关。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D9D40(uint8_t *this, char pszArg2)  // 实现：否则走 vt+700 拆除 + sub_53F6A0 收尾路径。(推断)宿主/附属物挂接开关
{
  bool pThis_3FC; // zf
  char result; // al

  pThis_3FC = (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1020))(this) == 0;  // 调虚槽 +1020：CNSwordman__vmt3FC
  result = pszArg2;
  if ( pThis_3FC || pszArg2 != 0 )
  {
    *(this + 156) = pszArg2;  // this+156 第 4 组·+858/+1292 增量
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);  // 调虚槽 +700：读 +6296 槽
    return sub_53F6A0(this);  // 调 收尾路径
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D9D80 sub_4D9D80
// 大状态变更（带坐标窗口，stdcall）：pArg2 当前大状态（+7148）≠ nArg1 才生效；
// 先记 nArg3/nArg4 到 +7676/+7672（目标点窗口），再 vt+1104(nArg1) 切换。
// ------------------------------------------------------------
int /*stdcall*/ sub_4D9D80(int nArg1, uint32_t *pArg2, int nArg3, int nArg4)  // 实现：先记 nArg3/nArg4 到 +7676/+7672（目标点窗口），再 vt+1104(nArg1) 切换
{
  int result; // eax

  result = nArg1;
  if ( pArg2[1787] != nArg1 )
  {
    pArg2[1919] = nArg3;
    pArg2[1918] = nArg4;
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 1104))(pArg2, nArg1);  // 虚调用 vt+1104
  }
  return result;
}



// ------------------------------------------------------------
// 0x4D9DB0 sub_4D9DB0
// 追击移动指令（切大状态 6）：参照对象（this+7252）为空返回 0；(−1,−1) = 自动
// 朝向目标算停点（x±300 / y±50），否则直接用 nArg2/nArg3；记录当前 x/y 到
// +7684/+7680 后 vt+1104(6)。【推断】AI 追击/走位。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D9DB0(uint32_t *this, int nArg2, int nArg3)  // 实现：+7684/+7680 后 vt+1104(6)。(推断)AI 追击/走位
{
  int pRefObj; // ecx —— 参照对象（this+7252）
  int nRefX; // edi —— 参照对象 vt+120() X
  int nStopX; // eax —— 停点 X（自身 X±300）
  int pRefObj2; // ecx
  int nRefY; // edi —— 参照对象 vt+124() Y
  int nCurX; // eax —— 自身当前 X
  int pVtbl; // edx

  pRefObj = *(this + 1813);  // this+7252〔pTarget7252〕
  if ( pRefObj == 0 )  // pRefObj=this+7252 pTarget7252
    return 0;
  if ( nArg2 == -1 && nArg3 == -1 )  // 若 nArg2 == -1 与/或 nArg3 == -1
  {
    nRefX = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pRefObj + 120))(pRefObj);  // 调虚槽 +120：动画对象
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) >= nRefX )  // 虚调用 vt+120
      nStopX = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + 300;  // 结果 = 虚调用 vt+120
    else
      nStopX = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - 300;  // 结果 = 虚调用 vt+120
    pRefObj2 = *(this + 1813);  // this+7252〔pTarget7252〕
    *(this + 1919) = nStopX;  // this+7676〔f_1DFC〕
    nRefY = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pRefObj2 + 124))(pRefObj2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) >= nRefY )  // 虚调用 vt+124
      *(this + 1918) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) - 50;  // 虚调用 vt+124
    else
      *(this + 1918) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) + 50;  // 虚调用 vt+124
  }
  else
  {
    *(this + 1919) = nArg2;  // this+7676〔f_1DFC〕
    *(this + 1918) = nArg3;  // this+7672〔f_1DF8〕
  }
  nCurX = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
  pVtbl = *this;
  *(this + 1921) = nCurX;
  *(this + 1920) = (*(int (/*thiscall*/ **)(uint32_t *))(pVtbl + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 6);  // 虚调用 vt+1104
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4D9E80 sub_4D9E80
// 大状态 25 直接设置：+7676=nArg2、+7672=nArg3（目标点），+7684/+7680 = 当前
// x/y，vt+1104(25)。与 0x4D9DB0 同族（无参照对象检查的直设版）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9E80(uint32_t *this, int nArg2, int nArg3)  // 实现：x/y，vt+1104(25)。与 0x4D9DB0 同族（无参照对象检查的直设版）
{
  int pVtbl; // edx
  int nCurY; // eax —— 自身当前 Y
  int pVtbl2; // edx

  pVtbl = *this;
  *(this + 1918) = nArg3;  // this+7672〔f_1DF8〕
  *(this + 1919) = nArg2;  // this+7676〔f_1DFC〕
  *(this + 1921) = (*(int (/*thiscall*/ **)(uint32_t *))(pVtbl + 120))(this);  // 调虚槽 +120：动画对象
  nCurY = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
  pVtbl2 = *this;
  *(this + 1920) = nCurY;
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(pVtbl2 + 1104))(this, 25);  // 虚函数调用 槽+1104
}



// ------------------------------------------------------------
// 0x4D9ED0 sub_4D9ED0 —— 大状态 ID 区间判定（50000..51000 = 特殊演出态族）【待验证：具体语义】
// 读 vt+340 的 +0 字段（技能/动作 id）。研究 §16 P41 定案：技能过场无独立引擎，
// 走大状态 tick case 硬编码 —— 50000 段疑为过场/演出类 id 区间。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4D9ED0(void *this)  // 大状态 ID 区间判定（50000..51000 = 特殊演出态族）(待验证：具体语义)
{
  return *(int *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 340))(this) >= 50000  // 调虚槽 +340：三元组基址（+284，vt+340）
      && *(int *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 340))(this) <= 51000;  // 调虚槽 +340：三元组基址（+284，vt+340）
}



// ------------------------------------------------------------
// 0x4D9F00 sub_4D9F00
// 参数对象转发：取 vt+64() 的参数/条目对象，调 sub_50EF20(obj, nArg2, 0, -1)。
//（【推断】nArg2 = 条目 id，0/-1 为默认区间的通用查询尾参。）
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9F00(void *this, int nArg2)  // 实现：（(推断)nArg2 = 条目 id，0/-1 为默认区间的通用查询尾参。）
{
  int pParamObj; // eax —— vt+64() 参数/条目对象

  pParamObj = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 64))(this);  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
  return sub_50EF20(pParamObj, nArg2, 0, -1);  // 气泡文本设置与量算
}



// ------------------------------------------------------------
// 0x4D9F20 sub_4D9F20 —— ★ 格挡时刻戳 vt+548（研究 §1.2 定案）
// `this+1673 = sub_699000(this+16)` —— 记录 this+64 时钟（word 下标 +16）当前时刻。
// 研究 §1.2 槽表：+548 = 0x4D9F20 记录 this+64 时钟当前时刻 → this+6692（格挡时刻戳）。
// 调用点：0x4D4D40 命中的格挡分支、sub_4D6D90 ④（a4 != 0）、0x4D9F50 等。
// ------------------------------------------------------------
int /*thiscall*/ sub_4D9F20(uint32_t *this, int nArg2)  // 实现：格挡时刻戳 vt+548（研究 §1.2 定案）
{
  int result; // eax

  result = sub_699000((int)(this + 16));  // 【clock_now(clk)】
  *(this + 1673) = result;  // this+6692〔uUI6692〕
  return result;
}



// ------------------------------------------------------------
// 0x4D9F50 sub_4D9F50 —— 骑乘/宿主槽写入（this+8352 双写）
// vt+1032() +16 与 this+8352 都写 nArg2；旧值 this+8360 非空且 nArg2==0（卸下）时
// 按旧值 +1 字节分派：1 → vt+372(101)；2 → 本地玩家时 vt+560(13,0,2,0)（受击姿态）。
// 【推断】骑乘坐骑/载具的挂载与卸载表现。
// ------------------------------------------------------------
char /*thiscall*/ sub_4D9F50(uint32_t *this, int nArg2)  // 实现：骑乘/宿主槽写入（this+8352 双写）
{
  int fld_e2090; // eax  | +0x20A8 → 拾取信息 7 字节对象指针（4D94A0 懒创建/释放）【推断】（证据 va=004D94A0）（CNGhoulOilSellerOlrek；va=004D94A0）

  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 1032))(this) + 16) = nArg2;  // 虚调用 vt+1032
  fld_e2090 = *(this + 2090);  // 读 fld_e2090 = this+8360（拾取信息 7 字节对象指针）
  *(this + 2088) = nArg2;  // 写 this+8352 = nArg2（骑乘/宿主槽）
  if ( fld_e2090 != 0 && nArg2 == 0 )  // 若 fld_e2090 != 0 与/或 nArg2 == 0
  {
    LOBYTE(fld_e2090) = *(uint8_t *)(fld_e2090 + 1);  // 调 取 16 位值低 8 位
    if ( (uint8_t)fld_e2090 == 1 )  // fld_e2090=this+8360 pPickInfo8360
    {
      LOBYTE(fld_e2090) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 101);  // 虚调用 vt+372
    }
    else if ( (uint8_t)fld_e2090 == 2 )  // fld_e2090=this+8360 pPickInfo8360
    {
      LOBYTE(fld_e2090) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 虚调用 vt+308
      if ( (uint8_t)fld_e2090 != 0 )  // fld_e2090=this+8360 pPickInfo8360
        LOBYTE(fld_e2090) = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t))(*this + 560))(this, 13, 0, 2, 0);  // 虚调用 vt+560
    }
  }
  return fld_e2090;  // +0x20A8 → 拾取信息 7 字节对象指针（4D94A0 懒创建/释放）【推断】（证据 va=004D94A0）（CNGhoulOilSellerOlrek；va=004D94A0）
}



// ------------------------------------------------------------
// 0x4D9FC0 sub_4D9FC0
// 攻击者引用记录（this+7256）：无敌门（vt+724）不通过才处理。pArg3 解析链：
// vt+576(车主) 非空取车主、否则自身；再验条件 529（受击态族）成立且 +8352 非空
// 时再上一层宿主。结果写入 this+7256。
// ------------------------------------------------------------
int /*userpurge*/ sub_4D9FC0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, uint32_t *pArg3)  // 实现：时再上一层宿主。结果写入 this+7256
{
  int result; // eax
  uint32_t *pOwnerObj; // esi

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 724))(pArg1);  // 结果 = 虚调用 vt+724
  if ( (uint8_t)result == 0 )
  {
    pOwnerObj = nullptr;
    if ( pArg3 != nullptr )  // 若 pArg3 有效（非空）
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 576))(pArg3, nArg2) != 0 )  // 虚调用 vt+576
        pOwnerObj = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 576))(pArg3);  // 结果 = 虚调用 vt+576
      else
        pOwnerObj = pArg3;
      result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pOwnerObj + 40))(pOwnerObj, 529);  // 结果 = 虚调用 vt+40
      if ( (uint8_t)result != 0 )
      {
        result = pOwnerObj[2088];
        if ( result != 0 )  // 若结果非 0（成功）
          pOwnerObj = (uint32_t *)pOwnerObj[2088];
      }
    }
    pArg1[1814] = pOwnerObj;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA030 sub_4DA030
// 容器计数：this+4 起、元素 12 字节（(end−begin)/12）。begin 为 0 返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DA030(int *this)  // 实现：容器计数：this+4 起、元素 12 字节（(end−begin)/12）。begin 为 0 返回 0
{
  int result; // eax

  result = *(this + 1);  // 读 result = this+4（宿主对象指针）
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(this + 2) - result) / 12;  // this+8〔nSkillRec8(推断)〕
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x4DA050 sub_4DA050
// 32 字节槽批量填充：把 pArg3 的 0x20 字节重复拷入 [pszArg1, pszArg2) 的每个槽
//（步长 32，std::fill 的定长 POD 版）。返回 end。
// ------------------------------------------------------------
char */*cdecl*/ sub_4DA050(char *pszArg1, char *pszArg2, const void *pArg3)  // 实现：（步长 32，std::fill 的定长 POD 版）。返回 end
{
  char *result; // eax
  void *pSlotPtr; // edi

  for ( result = pszArg1; result != pszArg2; result += 32 )
  {
    pSlotPtr = result;
    qmemcpy(pSlotPtr, pArg3, 0x20u);  // 调 内存块拷贝(内联展开)
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA080 sub_4DA080
// 属性读取（浮点积）：+88 与 +102 两字段相乘返回（0x4D5E00 同族，不同偏移）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4DA080(void *this)  // 实现：属性读取（浮点积）：+88 与 +102 两字段相乘返回（0x4D5E00 同族，不同偏移）
{
  int pThis_58; // [esp+8h] [ebp-4h]

  pThis_58 = sub_41A5E0((unsigned int)this + 88);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)((double)pThis_58 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 102)));  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4DA0B0 sub_4DA0B0
// 属性读取（浮点积）：+144 与 +158 两字段相乘返回（0x4DA080 同族）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4DA0B0(void *this)  // 实现：属性读取（浮点积）：+144 与 +158 两字段相乘返回（0x4DA080 同族）
{
  int pThis_90; // [esp+8h] [ebp-4h]

  pThis_90 = sub_41A5E0((unsigned int)this + 144);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)((double)pThis_90 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 158)));  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4DA0F0 sub_4DA0F0
// 属性读取（按 nArg2 选槽，步长 14 dword = 56 字节）：(this+56×nArg2+688) 与
// (+912) 相乘返回（0x4D5E40 同族、不同偏移）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4DA0F0(char *this, int nArg2)  // 实现：(+912) 相乘返回（0x4D5E40 同族、不同偏移）
{
  char *pSlotEntry; // esi —— 属性槽条目（56 字节步距）
  int nAttrA; // [esp+10h] [ebp+8h] —— 条目 +172 属性

  pSlotEntry = this + 14 * nArg2;
  nAttrA = sub_41A5E0((unsigned int)(pSlotEntry + 172));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)((double)nAttrA * COERCE_FLOAT(sub_41A5E0((unsigned int)(pSlotEntry + 228))));  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4DA130 sub_4DA130
// 完全复位（死亡/退场清理）：0x4D6970（出生/复活重置）→ vt+1024(状态块首值,
// this+7156 名字串) 上载 → 清 this+7252..7276 与 +7668 全部参照/窗口字段；
// 宿主（this+116）+153 标志且 vt+376()==100 时 vt+732(0,0,1) 直接归零 HP。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DA130(uint32_t *this)  // 实现：宿主（this+116）+153 标志且 vt+376()==100 时 vt+732(0,0,1) 直接归零 HP
{
  uint32_t *pNameStr; // ebx
  int pVt; // edi
  uint32_t *pStatBlk; // eax
  int result; // eax
  int pHost; // ecx

  sub_4D6970((int)this);  // 角色出生/复活初始化（尾调 0x4E73B0 复活重置）
  if ( *(this + 1794) < 0x10u )  // this+7176〔nNameStrCap〕
    pNameStr = this + 1789;
  else
    pNameStr = (uint32_t *)*(this + 1789);  // this+7156〔bParam3(推断)〕
  pVt = *this;
  pStatBlk = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);  // 结果 = 虚调用 vt+672
  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t *))(pVt + 1024))(this, *pStatBlk, pNameStr);  // 虚函数调用 槽+1024
  pHost = *(this + 29);  // 读 pHost = this+116（观察者容器）
  *(this + 1813) = 0;  // this+7252〔pTarget7252〕
  *(this + 1814) = 0;  // 写 this+7256 = 0（光环状态）
  *(this + 1815) = 0;
  *(this + 1816) = 0;
  *(this + 1817) = 0;
  *(this + 1818) = 0;
  *(this + 1819) = 0;
  *(this + 1917) = 0;  // this+7668〔nSwitchGuardT〕
  if ( *(uint8_t *)(pHost + 153) != 0 )  // pHost=this+116 观察者 vector 尾针
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this);  // 结果 = 虚调用 vt+376
    if ( result == 100 )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(*this + 732))(this, 0, 0, 1);  // 虚调用 vt+732
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA1D0 sub_4DA1D0
// 技能动作开始（随机前后摇掷定）：vt+308 门 + vt+840 ∈ {0,6}；宿主 +132 容器 +44
// 的技能槽数目经 vt+1156(&flagA,&flagB, 224×槽数, nArg3, nArg2) 检查；动作时长
// = dword_6F89C8/6F89CC（或大状态分支 6F89D0/6F89D4 表）[4×槽] + rand()%上限
// + 当前时钟 → this+7272；双掷 rand%100 < pArg1[2092+槽] 的两个 word（前后摇
// 通过位）写 nSlotFlagA/B；状态 15（霸体）时 60% 概率经 sub_432E50 翻转；
// vt+896 应用，sub_5FDFE0 收尾，未通过时把 +6616..6620 四个下限抬到 100，
// 尾调 vt+1080。
// ------------------------------------------------------------
int /*usercall*/ sub_4DA1D0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：尾调 vt+1080
{
  int result; // eax
  int pHost; // ecx
  int pVecHdr; // eax
  int pVecBegin; // ecx
  int pVecEnd; // eax
  int nSlotCount; // eax
  int nIdxA; // edi
  int nNow; // ebx
  int nRand; // edx
  int nBaseTime; // eax
  int nIdxB; // edi
  int nSlotFlagA; // [esp+4h] [ebp-8h] BYREF
  int nSlotFlagB; // [esp+8h] [ebp-4h] BYREF

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 结果 = 虚调用 vt+308
  if ( (uint8_t)result != 0
    && ((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 0  // 虚调用 vt+840
     || (result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1)) == 6) )  // 虚调用 vt+840
  {
    pHost = pArg1[29];  // pHost=this+116 观察者 vector 尾针
    nSlotFlagA = 4;
    nSlotFlagB = 4;
    pVecHdr = *(uint32_t *)(*(uint32_t *)(pHost + 132) + 44);  // pHost=this+116 观察者 vector 尾针
    pVecBegin = *(uint32_t *)(pVecHdr + 364);
    pVecEnd = pVecHdr + 360;
    if ( pVecBegin != 0 )
      nSlotCount = (*(uint32_t *)(pVecEnd + 8) - pVecBegin) >> 5;
    else
      nSlotCount = 0;
    (*(void (/*thiscall*/ **)(uint32_t *, int *, int *, int, int, int))(*pArg1 + 1156))(pArg1, &nSlotFlagA, &nSlotFlagB, 224 * nSlotCount, nArg3, nArg2);  // 虚调用 vt+1156
    if ( nSlotFlagA == 4 && nSlotFlagB == 4 )  // 若 nSlotFlagA == 4 与/或 nSlotFlagB == 4
    {
      nIdxA = 4 * pArg1[1787];
      nNow = sub_699000((int)(pArg1 + 1910));  // 【clock_now(clk)】
      nRand = rand() % dword_6F89D4[nIdxA];  // nRand = 调 rand
      nBaseTime = dword_6F89D0[nIdxA];
    }
    else
    {
      nIdxB = 4 * pArg1[1787];
      nNow = sub_699000((int)(pArg1 + 1910));  // 【clock_now(clk)】
      nRand = rand() % dword_6F89CC[nIdxB];  // nRand = 调 rand
      nBaseTime = dword_6F89C8[nIdxB];
    }
    pArg1[1818] = nBaseTime + nRand + nNow;
    if ( rand() % 100 < SLOWORD(pArg1[pArg1[1787] + 2092]) )  // 调 取伪随机数
      nSlotFlagA = 4;
    if ( rand() % 100 < SHIWORD(pArg1[pArg1[1787] + 2092]) )  // 调 取伪随机数
      nSlotFlagB = 4;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 776))(pArg1, 15) != 0 && rand() % 100 < 60 )  // 虚调用 vt+776
    {
      nSlotFlagA = sub_432E50(nSlotFlagA);  // 结果 = 关系码对调映射
      nSlotFlagB = sub_432E50(nSlotFlagB);  // 结果 = 关系码对调映射
    }
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 896))(pArg1, nSlotFlagA, nSlotFlagB);  // 虚调用 vt+896
    sub_5FDFE0(pArg1[1932]);  // 调 粒子与 vt+1080 收手
    if ( nSlotFlagB != 4 )
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
    return (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1080))(pArg1);  // 虚调用 vt+1080
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
int /*fastcall*/ sub_4DA3B0(uint32_t *pArg1, int nArg2, uint32_t *pArg3, uint32_t *pArg4, int nArg5)  // 实现：命中包分发前置（研究 §1.1 case 0x13 的客户端入口之一）
{
  int pObj; // ebx —— 受方 vt+60() 容器 +104（动作数据宿主）
  uint32_t *pActVt; // edi —— sub_4E5CA0 为 0 时 = pArg1，否则 nullptr（包发送的目标）
  int pAtkBlk; // eax —— vt+672 属性块（+24 = 伤害门字段）
  int nPktLen; // eax —— 动作数据长度（pObj vt+44）
  int nDataLen; // [esp-10h] [ebp-84h]
  uint8_t actBuf[100]; // [esp+Ch] [ebp-68h] BYREF —— 动作数据（pObj vt+20 装载）
  int dword_796E502; // [esp+70h] [ebp-4h]
  int nAtkDef; // [esp+80h] [ebp+Ch] —— 受方 vt+340() 动作 id

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  if ( pArg1[1943] == 3 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1064))(pArg1);  // 虚调用 vt+1064
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg3 + 368))(pArg3) != 0  // 虚调用 vt+368
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t *))(*pArg1 + 1304))(pArg1, pArg3) != 0  // 虚调用 vt+1304
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )  // 虚调用 vt+308
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 312))(pArg3, 1);  // 虚调用 vt+312
    pObj = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 60))(pArg3) + 104);  // 结果 = 虚调用 vt+60
    pActVt = (uint8_t)sub_4E5CA0(pArg3) == 0 ? pArg1 : nullptr;  // 结果 = 阵营号 200..204 判定（200 起逐个比较）
    nAtkDef = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 340))(pArg3);  // 结果 = 虚调用 vt+340
    (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj + 20))(pObj, actBuf);  // 调虚槽 +20：CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认…
    nDataLen = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj);  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420…
    pAtkBlk = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 672))(pArg3);  // 结果 = 虚调用 vt+672
    sub_4E4C10(pActVt, nAtkDef, *(uint32_t *)(pAtkBlk + 24), actBuf, nDataLen, 0, 0, 0);  // 与 ·0x4E4A50 同构（差异：上下文使能位固定 1 + 数据块打包）
    return 0;
  }
  else
  {
    pAtkBlk = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 348))(pArg3);  // 结果 = 虚调用 vt+348
    if ( *(uint8_t *)(pAtkBlk + 16) != 0 || *(float *)pAtkBlk > 0.0 )
    {
      *(uint32_t *)((char *)pArg1 + 7777) = *pArg4;
      *(uint32_t *)((char *)pArg1 + 7781) = pArg4[1];
      *(uint32_t *)((char *)pArg1 + 7785) = pArg4[2];
      *(uint32_t *)((char *)pArg1 + 7789) = pArg4[3];
      *(uint32_t *)((char *)pArg1 + 7793) = pArg4[4];
      *(uint32_t *)((char *)pArg1 + 7797) = pArg4[5];
      sub_4D9FC0(pArg1, (int)pArg1, pArg3);  // 调 时再上一层宿主。结果写入 this+7256
      if ( *((uint8_t *)pArg1 + 7530) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1236))(pArg1);  // 虚调用 vt+1236
      if ( pArg1[1787] == 11 )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 4);  // 虚调用 vt+1104
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 576))(pArg3) != 0  // 虚调用 vt+576
        && (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 576))(pArg3) != pArg3 )  // 虚调用 vt+576
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t *))(*pArg1 + 1136))(pArg1, pArg3) == 1 && rand() % 100 < 70 )  // 虚调用 vt+1136
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*pArg1 + 1280))(pArg1, pArg3);  // 虚调用 vt+1280
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0  // 虚调用 vt+308
          && rand() % 100 < pArg1[2120]  // 调 取伪随机数
          && sub_699000((int)(pArg1 + 2122)) > pArg1[2121] )  // 【clock_now(clk)】
        {
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*pArg1 + 1180))(pArg1, pArg3);  // 虚调用 vt+1180
          *((uint8_t *)pArg1 + 8501) = 0;
          *((uint8_t *)pArg1 + 8502) = 0;
          sub_698F90((int)(pArg1 + 2122), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        }
      }
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 348))(pArg3) + 124) == 2 )  // 虚调用 vt+348
        rand();  // 调 取伪随机数
    }
    return sub_4D71B0(pArg1, *(float *)&pArg3, (int)pArg4, nArg5);  // 【命中主处理器 vt+512（§2 全文定案）】
  }
}



// ------------------------------------------------------------
// 0x4DA5F0 sub_4DA5F0
// 目标可锁定判定（索敌/Tab 选定门）：目标空 → false；目标车主不同且条件 17 成立
// 且 vt+940==1 → false（隐身/不可见）；非盲眼且 this+7520 视野加成为 0 → true；
// 否则距离（vt+8）≤ 视野值×1.4（盲眼取 10）。返回 bool。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4DA5F0(int *this, int nArg2)  // 实现：否则距离（vt+8）≤ 视野值×1.4（盲眼取 10）。返回 bool
{
  int nTgtOwner; // ebx
  int nDist; // edi
  int nSight; // [esp+10h] [ebp+8h]

  if ( nArg2 == 0 )
    return false;
  nTgtOwner = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);  // 调虚槽 +376：坐标同步包（type 37）
  if ( nTgtOwner != (*(int (/*thiscall*/ **)(int *))(*this + 376))(this)  // 虚调用 vt+376
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 940))(nArg2) == 1 )  // 调虚槽 +940
  {
    return false;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 776))(this, 5) == 0 && *(this + 1880) == 0 )  // 虚调用 vt+776
    return true;
  nDist = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, nArg2, 0);  // 结果 = 虚调用 vt+8
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 776))(this, 5) != 0 )  // 虚调用 vt+776
    nSight = 10;
  else
    nSight = *(this + 1880);  // 读 nSight = this+7520（攻击参数面）
  return nDist <= (int)(uint64_t)((double)nSight * 1.4);  // nSight=this+7520 nSightRange
}



// ------------------------------------------------------------
// 0x4DA6B0 sub_4DA6B0
// 技能槽坐标越界检查：宿主 +132 容器 +44 处槽表（32 字节/项）计数 nSlotCount；
// x（vt+120）< 80 → *uArg2=1 返 1（在顶部外）；x > 224×nSlotCount−80 →
// *uArg2=0 返 1（在底部外）；界内返 0。【推断】技能栏 UI 命中判定。
// ------------------------------------------------------------
char /*thiscall*/ sub_4DA6B0(uint32_t *this, uint32_t *uArg2)  // 实现：*uArg2=0 返 1（在底部外）；界内返 0。(推断)技能栏 UI 命中判定
{
  int pSkillVec; // eax
  int pVecBegin; // ecx
  int pVecEnd; // eax
  int nSlotCount; // esi

  pSkillVec = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);  // this+116〔会话上下文〕
  pVecBegin = *(uint32_t *)(pSkillVec + 364);  // pSkillVec=this+116 会话上下文
  pVecEnd = pSkillVec + 360;  // pSkillVec=this+116 会话上下文
  if ( pVecBegin != 0 )
    nSlotCount = (*(uint32_t *)(pVecEnd + 8) - pVecBegin) >> 5;
  else
    nSlotCount = 0;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) >= 80 )  // 虚调用 vt+120
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) <= 224 * nSlotCount - 80 )  // 虚调用 vt+120
    {
      return 0;
    }
    else
    {
      *uArg2 = 0;
      return 1;  // 返回 1(成功)
    }
  }
  else
  {
    *uArg2 = 1;
    return 1;  // 返回 1(成功)
  }
}



// ------------------------------------------------------------
// 0x4DA730 sub_4DA730
// 随机间隔喊话：this+8584(最小间隔)/8588(最大间隔)/8580(下次时刻) + 时钟
// this+8556；到期（now ≥ +8580）→ vt+212 放 this+8532 字符串、清 +8569/+8570
// 标志、重新 countdown = +8584 + rand%(+8588−+8584)。
// ------------------------------------------------------------
char /*thiscall*/ sub_4DA730(uint32_t *this)  // 实现：标志、重新 countdown = +8584 + rand%(+8588−+8584)
{
  int fld_e2147; // eax
  int nNextAt; // ebx
  char *pShoutStr; // eax
  int nMinGap; // ebx
  unsigned int nRand; // eax

  fld_e2147 = *(this + 2147);  // this+8588〔f_218C〕
  if ( fld_e2147 != 0 )  // fld_e2147=this+8588 f_218C
  {
    fld_e2147 = *(this + 2146);  // this+8584〔bPhaseDone(推断)〕
    if ( fld_e2147 != 0 )  // fld_e2147=this+8584 bPhaseDone
    {
      nNextAt = *(this + 2145);  // this+8580〔nPhaseStage〕
      fld_e2147 = sub_699000((int)(this + 2139));  // 【clock_now(clk)】
      if ( fld_e2147 >= nNextAt )  // fld_e2147=this+8584 bPhaseDone
      {
        if ( *(this + 2138) < 0x10u )
          pShoutStr = (char *)(this + 2133);  // this+8532〔nPhaseValB(推断)〕
        else
          pShoutStr = (char *)*(this + 2133);  // this+8532〔nPhaseValB〕
        (*(void (/*thiscall*/ **)(uint32_t *, char *, int, uint32_t, uint32_t))(*this + 212))(this, pShoutStr, -1, 0, 0);  // 虚调用 vt+212
        *((uint8_t *)this + 8569) = 0;  // this+8569〔f_2179〕
        *((uint8_t *)this + 8570) = 0;  // this+8570〔f_217A〕
        nMinGap = *(this + 2146);  // this+8584〔bPhaseDone(推断)〕
        nRand = rand();  // nRand = 调 rand
        LOBYTE(fld_e2147) = sub_698F90((int)(this + 2139), nMinGap + nRand % (*(this + 2147) - nMinGap), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
    }
  }
  return fld_e2147;  // fld_e2147=this+8584 bPhaseDone
}



// ------------------------------------------------------------
// 0x4DA7C0 sub_4DA7C0
// 32 字节槽正向拷贝：[pszArg1, pszArg2) 逐 0x20 槽 memcpy 到 pszArg3 起。
// std::copy<POD> 的展开形（0x4DA820 的无判空版）。
// ------------------------------------------------------------
char */*cdecl*/ sub_4DA7C0(char *pszArg1, char *pszArg2, char *pszArg3)  // 实现：std::copy<POD> 的展开形（0x4DA820 的无判空版）
{
  char *pszArg12; // edx
  char *result; // eax
  const void *pszArg122; // esi
  void *pDstSlot; // edi

  pszArg12 = pszArg1;
  result = pszArg3;
  while ( pszArg12 != pszArg2 )  // 当 pszArg12 != pszArg2 循环
  {
    pszArg122 = pszArg12;
    pDstSlot = result;
    pszArg12 += 32;
    result += 32;
    qmemcpy(pDstSlot, pszArg122, 0x20u);  // 调 内存块拷贝(内联展开)
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA7F0 sub_4DA7F0
// 32 字节槽反向拷贝（copy_backward）：从 pszArg2 向 pszArg1 逆向逐 0x20 槽拷到
// pszArg3 起（重叠区间向前移时用）。
// ------------------------------------------------------------
char */*cdecl*/ sub_4DA7F0(char *pszArg1, char *pszArg2, char *pszArg3)  // 实现：pszArg3 起（重叠区间向前移时用）
{
  char *pszArg22; // edx
  char *result; // eax

  pszArg22 = pszArg2;
  result = pszArg3;
  while ( pszArg22 != pszArg1 )  // 当 pszArg22 != pszArg1 循环
  {
    pszArg22 -= 32;
    result -= 32;
    qmemcpy(result, pszArg22, 0x20u);  // 调 内存块拷贝(内联展开)
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA820 sub_4DA820
// 32 字节槽正向拷贝（带目标判空版）：[pszArg1, pszArg2) 逐 0x20 槽 memcpy 到
// pszArg3 起，目标非空才拷。
// ------------------------------------------------------------
char */*cdecl*/ sub_4DA820(char *pszArg1, char *pszArg2, char *pszArg3)  // 实现：pszArg3 起，目标非空才拷
{
  char *pszArg12; // edx
  char *result; // eax

  pszArg12 = pszArg1;
  for ( result = pszArg3; pszArg12 != pszArg2; result += 32 )
  {
    if ( result != nullptr )  // 若 result 有效（非空）
      qmemcpy(result, pszArg12, 0x20u);  // 调 内存块拷贝(内联展开)
    pszArg12 += 32;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DA860 sub_4DA860
// CNSpeedControl 析构壳：0x4DA890 成员析构 + pszArg2&1 时 free（MSVC 删除器形）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4DA860(void *Block, char pszArg2)  // 实现：CNSpeedControl 析构壳：0x4DA890 成员析构 + pszArg2&1 时 free（MSVC 删除器形）
{
  sub_4DA890();  // 调 IObject 子块（+8）复位
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4DA890 sub_4DA890
// CNSpeedControl 析构：换挂 IRDAppendage::vftable 走 sub_5F6640 基类析构，
// IObject 子块（+8）复位。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DA890(uint32_t *this)  // 实现：IObject 子块（+8）复位
{
  int result; // eax

  *this = &CNSpeedControl::`vftable';  // 构造装配 vftable：CNSpeedControl
  nullsub_3(this);
  *this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // 调 基类析构
  *(this + 2) = &nengine::IObject::`vftable';  // 写 this+8 = &nengine::IObject::`vftable’（技能槽记录首字）
  *((uint8_t *)this + 12) = 0;  // 写 this+12 = 0（技能槽记录次字）
  return result;
}



// ------------------------------------------------------------
// 0x4DA8F0 sub_4DA8F0
// CNMovementController 析构壳：0x4DA920 成员析构 + pszArg2&1 时 free。
// ------------------------------------------------------------
void */*thiscall*/ sub_4DA8F0(void *Block, char pszArg2)  // 实现：CNMovementController 析构壳：0x4DA920 成员析构 + pszArg2&1 时 free
{
  sub_4DA920();  // 调 CNMovementController 析构：IRDAppendage 基类析构（同 0x4DA890 形态）
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4DA920 sub_4DA920
// CNMovementController 析构：IRDAppendage 基类析构（同 0x4DA890 形态）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DA920(uint32_t *this)  // 实现：CNMovementController 析构：IRDAppendage 基类析构（同 0x4DA890 形态）
{
  int result; // eax

  *this = &CNMovementController::`vftable';  // 构造装配 vftable：CNMovementController
  nullsub_3(this);
  *this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // 调 基类析构
  *(this + 2) = &nengine::IObject::`vftable';  // 写 this+8 = &nengine::IObject::`vftable’（技能槽记录首字）
  *((uint8_t *)this + 12) = 0;  // 写 this+12 = 0（技能槽记录次字）
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
char /*thiscall*/ sub_4DA980(char *this)  // 实现：死亡/淘汰确认包（type 42；off_77F3FC 日志双分支）
{
  char result; // al
  int pRideObj; // ecx —— this+6180 骑乘/宿主对象
  int nKillerId; // ebx —— 车主 id（PVP 场景 6 解析，缺省 0xFFFF）
  int pHostBlk; // eax —— vt+1032 宿主数据块
  int pHostBlk2; // eax
  char *pszName; // edi —— this+292 SSO 名字串数据
  int nSelfId; // eax —— vt+52() 自身 id
  char *pszName2; // edi
  int nSelfId2; // eax
  int pPktWord; // [esp+4h] [ebp-4h] BYREF —— 包写入暂存 word

  result = *(this + 264);  // this+264 动画句柄
  if ( result == 0 )  // result=this+264 动画句柄
  {
    if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1020))(this) != 0 )  // 调虚槽 +1020：CNSwordman__vmt3FC
    {
      pRideObj = *((uint32_t *)this + 1545);  // this+6180〔pAtkCtxC6180〕
      if ( pRideObj != 0 && *((uint32_t *)this + 30) != pRideObj )  // this+120〔pAnimObj〕
      {
        sub_493400(pRideObj, *((uint32_t *)this + 1702));  // 应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *((uint32_t *)this + 1545));  // 调虚槽 +196：动画对象设置（换域 + 播放）
      }
    }
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1072))(this);  // 调虚槽 +1072
    if ( byte_77F280 != 0 || *(this + 7801) == 0 )  // 调试机标志(DebugConfig.txt 校验)
    {
      if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 312))(this, 0);  // 调虚槽 +312：濒死/一击表现(LAST STRIKE)
      if ( *((uint32_t *)this + 78) < 0x10u )  // this+78 【推断】公会标志字节 C
        pszName = this + 292;  // this+292 打开槽模式号
      else
        pszName = *((char **)this + 73);  // this+73 基类名字缓冲 SSO 首字节
      nSelfId = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      return off_77F3FC((char *)&byte_6F8F34, pszName, nSelfId);  // 返回 调 off_77F3FC
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
      if ( result != 0 )  // 若结果非 0（成功）
      {
        nKillerId = 0xFFFF;
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 6  // 全局 dword_8F7A24 = 登录/选区管理器
          && *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1032))(this) + 24) != 0 )  // 调虚槽 +1032
        {
          pHostBlk = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1032))(this);  // 调虚槽 +1032
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pHostBlk + 24) + 40))(*(uint32_t *)(pHostBlk + 24), 273) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
          {
            pHostBlk2 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1032))(this);  // 调虚槽 +1032
            nKillerId = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pHostBlk2 + 24) + 52))(*(uint32_t *)(pHostBlk2 + 24));  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15 行…
          }
        }
        sub_423200(dword_8F7B08, 42);  // 【发送网络包API】
        pPktWord = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        sub_423290(&pPktWord, 2);  // 调 写 4B 长度
        pPktWord = nKillerId;
        sub_423290(&pPktWord, 2);  // 调 写 4B 长度
        sub_423380(dword_8F7B08);  // 发包提交：Commit()
        *(this + 264) = 1;  // this+264 动画句柄
        if ( *((uint32_t *)this + 78) < 0x10u )  // this+78 【推断】公会标志字节 C
          pszName2 = this + 292;  // this+292 打开槽模式号
        else
          pszName2 = *((char **)this + 73);  // this+73 基类名字缓冲 SSO 首字节
        nSelfId2 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 52))(this, nKillerId);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
        return off_77F3FC((char *)&byte_6F8F64, pszName2, nSelfId2);  // 返回 调 off_77F3FC
      }
    }
  }
  return result;  // result=this+264 动画句柄
}



// ------------------------------------------------------------
// 0x4DAB30 sub_4DAB30 —— 定长块批量填充（cdecl）
// 从 pszArg2 起以 pszArg2 自身为计数（do-while 指针递减，非典型用法）将 pArg3 的
// 0x20 字节块逐个 qmemcpy 到 pszArg1 起的 32 字节槽列。Hex-Rays 忠实转写，
// 实参即 (dst, count, src)。【推断】32 字节/条的结构数组批量初始化。
// ------------------------------------------------------------
char */*cdecl*/ sub_4DAB30(char *pszArg1, char *pszArg2, const void *pArg3)  // 定长块批量填充（cdecl）
{
  char *result; // eax
  char *pszArg22; // edx

  result = pszArg2;
  if ( pszArg2 != nullptr )  // 若 pszArg2 有效（非空）
  {
    pszArg22 = pszArg2;
    result = pszArg1;
    do
    {
      if ( result != nullptr )  // 若 result 有效（非空）
        qmemcpy(result, pArg3, 0x20u);  // 调 内存块拷贝(内联展开)
      result += 32;
      --pszArg22;
    }
    while ( pszArg22 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DAB60 sub_4DAB60 —— 标签/条件集合成员判定
// 线性查找 this+332..336 的 dword vector 是否含 nArg2（0x4DAC90/0x4DAD70 的
// sub_4DAB60(10/11/14/15) 与 0x4DF2D0 tick 内多次调用均走此查询）。
// 【推断】对象支持的 AI 行为/状态集合。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4DAB60(uint32_t *this, int nArg2)  // 实现：标签/条件集合成员判定
{
  uint32_t *fld_e84; // edx
  uint32_t *i; // eax

  fld_e84 = (uint32_t *)*(this + 84);  // this+84 插值起点 X
  for ( i = (uint32_t *)*(this + 83); i != fld_e84; ++i )  // this+332〔bReservedConn〕
  {
    if ( *i == nArg2 )
      break;
  }
  return i != fld_e84;  // fld_e84=this+84 插值起点 X
}



// ------------------------------------------------------------
// 0x4DAB90 sub_4DAB90 —— 动画帧包围盒聚合（包围盒只扩不缩）
// 遍历 pDwArg2 动作数据的帧表（88 字节/条，帧 +60..+64 float 三对），对每帧取
// -x0、x0+w、-y0、y0+h 与 pArg1（ActiveObject）+16/+20/+24/+28 四向边界比较取最大。
// 【推断】碰撞/可视盒随帧集扩张（研究 P29 盒模型族）。
// ------------------------------------------------------------
void /*stdcall*/ sub_4DAB90(uint32_t *pArg1, int *pDwArg2)  // 实现：动画帧包围盒聚合（包围盒只扩不缩）
{
  int *pDwArg22; // esi
  int nFrameIdx; // edi
  int nFrameCount; // eax
  int pFrameEntry; // eax
  float *j; // esi
  double fEdgeNegX; // st7
  double fEdgePosX; // st7
  double fEdgeNegY; // st7
  double fEdgePosY; // st7
  int nFrameIdxCopy; // [esp+4h] [ebp-4h]

  pDwArg22 = pDwArg2;
  if ( pDwArg2 != nullptr )  // 若 pDwArg2 有效（非空）
  {
    nFrameIdx = 0;
    for ( nFrameIdxCopy = 0; ; nFrameIdx = nFrameIdxCopy )
    {
      nFrameCount = pDwArg22[11];
      if ( nFrameCount != 0 )
        nFrameCount = (pDwArg22[12] - nFrameCount) / 88;
      if ( nFrameIdx >= nFrameCount )
        break;
      pFrameEntry = sub_4924C0(pDwArg22, nFrameIdx);  // 结果 = 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0
      for ( j = *(float **)(pFrameEntry + 60); j != *(float **)(pFrameEntry + 64); j += 6 )
      {
        fEdgeNegX = -*j;
        if ( (double)(int)pArg1[5] < fEdgeNegX )
          pArg1[5] = (uint64_t)fEdgeNegX;
        fEdgePosX = j[3] + *j;
        if ( (double)(int)pArg1[4] < fEdgePosX )
          pArg1[4] = (uint64_t)fEdgePosX;
        fEdgeNegY = -j[1];
        if ( (double)(int)pArg1[6] < fEdgeNegY )
          pArg1[6] = (uint64_t)fEdgeNegY;
        fEdgePosY = j[4] + j[1];
        if ( (double)(int)pArg1[7] < fEdgePosY )
          pArg1[7] = (uint64_t)fEdgePosY;
      }
      pDwArg22 = pDwArg2;
      ++nFrameIdxCopy;
    }
  }
}



// ------------------------------------------------------------
// 0x4DAC90 sub_4DAC90
// 点选目标处理（下行包驱动）：从包读 2 个 word（vt+76 读坐标，0x4D8CE0 同包格式）
// → sub_45EBE0(x,y) 拾取对象 → __RTDynamicCast 到 IRDActiveObject → vt+1148 设置
// 为参照/目标对象；vt+1132 未就绪时按 sub_4DAB60(10/11) 的条件切大状态 9/10；
// 参照对象（this+7252）发生变化时尾调 sub_4D84F0(0,0) 复位。【推断】鼠标点选/AO 目标。
// ------------------------------------------------------------
void /*thiscall*/ sub_4DAC90(int *this)  // 实现：参照对象（this+7252）发生变化时尾调 sub_4D84F0(0,0) 复位。(推断)鼠标点选/AO 目标
{
  int pPicked; // eax —— sub_45EBE0 拾取的对象
  int pTarget; // eax —— RTTI 转换后的 IRDActiveObject
  int pOldRef; // edi —— 旧参照对象（this+7252）
  uint16_t nPktX; // [esp+4h] [ebp-8h] BYREF —— 包内坐标 word 1
  uint16_t nPktY; // [esp+8h] [ebp-4h] BYREF —— 包内坐标 word 2

  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &nPktX);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &nPktY);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1108))(this) == 0 )  // 虚调用 vt+1108
  {
    pPicked = sub_45EBE0(nPktX, nPktY);  // 调 对象查找
    pTarget = __RTDynamicCast(pPicked, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // pTarget = 调 __RTDynamicCast
    if ( pTarget != 0 )
    {
      pOldRef = *(this + 1813);  // this+7252〔pTarget7252〕
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1148))(this, pTarget);  // 虚调用 vt+1148
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1132))(this) == 0 )  // 虚调用 vt+1132
      {
        if ( sub_4DAB60(this, 10) )  // 标签/条件集合成员判定
        {
          (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 9);  // 虚调用 vt+1104
        }
        else if ( sub_4DAB60(this, 11) )  // 标签/条件集合成员判定
        {
          (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 10);  // 虚调用 vt+1104
        }
      }
      if ( pOldRef != *(this + 1813) )  // this+7252〔pTarget7252〕
        sub_4D84F0(this, 0, 0);  // 头顶气泡 ”CommandReceive.ani”（同 0x4D82D0 结构）
    }
  }
}



// ------------------------------------------------------------
// 0x4DAD70 sub_4DAD70
// AI 侧移/绕后走位掷（50% 概率）：大状态 7 或 sub_4DAB60(11) 不成立时退出；
// 参照对象（this+7252）存在时，按自身 X 与参照 vt+120(nArg2) 比较取参照 X ∓
// 视野值×0.5（sub_4D8FE0 视野，0x4D8FE0 盲眼=10）写 +7676 停点，最后 vt+1104(11)
// 切大状态。【推断】怪物 AI 的绕背/保持距离走位。
// ------------------------------------------------------------
char /*usercall*/ sub_4DAD70@<al>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 实现：切大状态。(推断)怪物 AI 的绕背/保持距离走位
{
  int pObj; // edi —— 参照对象（this+7252）
  int nRefX; // edi —— 参照对象 vt+120(nArg2)
  int pObj2; // edi
  double fRefXf; // st7
  double fStopX; // st7 —— 停点 X（写 +7676）
  int pVtbl; // edx
  float fSightHalf; // [esp+4h] [ebp-8h] —— 视野值×0.5

  if ( pArg1[1787] == 7 )
    return 0;
  if ( rand() % 100 >= 50 )  // 调 取伪随机数
    return 0;
  pObj = pArg1[1813];
  if ( pObj == 0 || sub_4DAB60(pArg1, 11) )  // 标签/条件集合成员判定
    return 0;
  nRefX = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, nArg2);  // 调虚槽 +120：动画对象
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) >= nRefX )  // 虚调用 vt+120
  {
    fRefXf = (double)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 120))(pArg1[1813]);  // 调虚槽 +120：动画对象
    fStopX = fRefXf - (double)sub_4D8FE0(pArg1) * 0.5;  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
  }
  else
  {
    pObj2 = pArg1[1813];
    fSightHalf = (double)sub_4D8FE0(pArg1) * 0.5;  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
    fStopX = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2) + fSightHalf;  // 调虚槽 +120：动画对象
  }
  pVtbl = *pArg1;
  pArg1[1919] = (uint64_t)fStopX;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(pVtbl + 1104))(pArg1, 11);  // 虚函数调用 槽+1104
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4DAE50 sub_4DAE50 —— 头顶名牌/文本绘制
// 在 (nArg2-75, nArg3-30-vt+192()) 处经 dword_79C0B0 文本渲染器（vt+72 锚定对象、
// vt+80 画字符串）绘制本对象名牌：颜色按场景 this+7772 分档（1→-37965、
// 2→-1048321、3→-1048321、vt+1296 专名→-14745706）；与本地玩家同 vt+376 宿主时
// 画 "Lv.%d %s"（颜色 -6400，等级取 vt+672(3) +0）。场景 1/2 还逐行画 this+1952
// 标签 vector（id+1573 经 sub_422E70 取本地化串，行距 15px）。动作 id==60001 或
// vt+940() 非零（隐身）则不画。
// ------------------------------------------------------------
char /*thiscall*/ sub_4DAE50(char *this, int nArg2, int nArg3)  // 实现：头顶名牌/文本绘制
{
  uint32_t *nActId; // eax —— vt+340() 动作 id（60001 = 不显示）；后段兼作返回值寄存器
  int nObjHeight; // eax —— vt+192() 对象高度（名牌 y 偏移）
  int nColor; // ebx —— 文本颜色（ARGB）
  int pVtbl; // edx
  const char *pszNameA; // eax —— 名字串（vt+1296 分支）
  int nScene; // eax —— this+7772 场景值
  const char *pszNameB; // eax —— 名字串（case 3）
  int pOwnerId; // edi —— vt+376() 宿主/车主 id
  const char *pszNameC; // edi —— 名字串（case 1）
  uint32_t *pAttrBlk; // eax —— vt+672(3) 属性块（+0 = 等级）
  int pszNameD; // eax —— 名字串（同宿主分支）
  unsigned int nLineIdx; // edi —— 标签行下标
  int pVecBegin; // ecx —— this+1952 标签 vector
  int nTagId; // ebx —— dword_79C0B0 当前虚表
  int pVecBegin2; // eax
  uint32_t *pszNameE; // [esp-Ch] [ebp-88h]
  int pszGuildName; // [esp-Ch] [ebp-88h] —— case 2: sub_4633B0 取公会/团队名
  int nLineOff; // [esp+4h] [ebp-78h] —— 行偏移（15px 步进）
  char Buffer[109]; // [esp+8h] [ebp-74h] BYREF —— 待绘制文本
  int16_t nStackPad; // [esp+75h] [ebp-7h] —— 栈对齐占位
  int dword_796E502; // [esp+78h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  nActId = (uint32_t *)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 340))(this);  // 调虚槽 +340：三元组基址（+284，vt+340）
  if ( *nActId == 60001 )
    return (char)nActId;
  LOBYTE(nActId) = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 940))(this);  // 调虚槽 +940
  if ( (uint8_t)nActId != 0 )
    return (char)nActId;
  nObjHeight = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 192))(this);  // 调虚槽 +192
  nArg3 += -30 - nObjHeight;
  sub_424680((int)&nArg2, (int)&nArg3, 0.0, 0.0);  // 变焦点变换: p’ = pivot + (p − pivot) × globalZoom
  nColor = 0;
  memset(Buffer, 0, sizeof(Buffer));  // 调 内存按字节填充
  nArg2 -= 75;
  pVtbl = *(uint32_t *)this;
  nStackPad = 0;
  if ( (*(uint8_t (/*thiscall*/ **)(char *))(pVtbl + 1296))(this) != 0 )  // 调虚槽 +1296：IRDCharacter__vmt510 默认虚槽桩（19 行）
  {
    if ( *((uint32_t *)this + 78) < 0x10u )  // this+78 【推断】公会标志字节 C
      pszNameA = this + 292;  // this+292 打开槽模式号
    else
      pszNameA = *((const char **)this + 73);  // this+73 基类名字缓冲 SSO 首字节
    sprintf(Buffer, "%s", pszNameA);  // 字符串 “%s”
    nColor = -14745706;
  }
  nScene = *((uint32_t *)this + 1943);  // 读 nScene = this+7772（反击态）
  switch ( nScene )  // 按 nScene 分派
  {
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      if ( *((uint32_t *)this + 78) < 0x10u )  // this+78 【推断】公会标志字节 C
        pszNameE = this + 292;  // this+292 打开槽模式号
      else
        pszNameE = *((uint32_t **)this + 73);  // this+73 基类名字缓冲 SSO 首字节
      sprintf(Buffer, "%s", pszNameE);  // 字符串 “%s”
      goto LABEL_20;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( *((uint32_t *)this + 78) < 0x10u )  // this+78 【推断】公会标志字节 C
        pszNameC = this + 292;  // this+292 打开槽模式号
      else
        pszNameC = *((const char **)this + 73);  // this+73 基类名字缓冲 SSO 首字节
      sprintf(Buffer, "%s", pszNameC);  // 字符串 “%s”
      nColor = -37965;
      break;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      pszGuildName = sub_4633B0(this);  // 结果 = std::string 取数据指针（SSO 判定）
      sprintf(Buffer, "%s", pszGuildName);  // 字符串 “%s”
LABEL_20:
      nColor = -1048321;
      break;
    default:
      break;
  }
  pOwnerId = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 376))(this);  // 调虚槽 +376：坐标同步包（type 37）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) == pOwnerId )  // 全局 dword_8F7C04 = 本机角色对象
  {
    if ( *((uint32_t *)this + 78) < 0x10u )  // this+78 【推断】公会标志字节 C
      pszNameD = this + 292;  // this+292 打开槽模式号
    else
      pszNameD = *((const char **)this + 73);  // this+73 基类名字缓冲 SSO 首字节
    pAttrBlk = (uint32_t *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
    sprintf(Buffer, "Lv.%d %s", *pAttrBlk, pszNameD);  // 字符串 “Lv.%d %s”
    nColor = -6400;
  }
  LOBYTE(nActId) = Buffer[0];  // 调 取 16 位值低 8 位
  if ( Buffer[0] != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (uint32_t *)this + 1795);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, nArg2, nArg3, nColor, Buffer);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    pVecBegin2 = *((uint32_t *)this + 1943);  // 读 pVecBegin2 = this+7772（反击态）
    if ( pVecBegin2 == 1 || pVecBegin2 == 2 )  // 若 pVecBegin2 == 1 与/或 pVecBegin2 == 2
    {
      nLineIdx = 0;
      for ( nLineOff = 0; ; nLineOff += 15 )
      {
        pVecBegin = *((uint32_t *)this + 1952);  // this+7808〔风格/分支选择〕
        if ( pVecBegin == 0 || nLineIdx >= (*((uint32_t *)this + 1953) - pVecBegin) >> 2 )  // this+7812〔nSubStateA(推断)〕
          break;
        if ( *(uint32_t *)(pVecBegin + 4 * nLineIdx) != 131091 )  // pVecBegin=this+7808 风格/分支选择
        {
          nTagId = *(uint32_t *)dword_79C0B0;  // 默认字体/绘制资源
          pVecBegin2 = sub_422E70((uint8_t)*(uint32_t *)(*((uint32_t *)this + 1952) + 4 * nLineIdx) + 1573);  // this+7808〔风格/分支选择〕
          (*(void (/*cdecl*/ **)(int, int, int, int, int))(nTagId + 80))(dword_79C0B0, nArg2, nArg3 - nLineOff - 15, -1, pVecBegin2);  // 默认字体/绘制资源
        }
        ++nLineIdx;
      }
    }
    LOBYTE(nActId) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
  }
  return (char)nActId;
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
char /*thiscall*/ sub_4DB0E0(uint32_t *this, int nArg2)  // 实现：技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
{
  int fld_e1952; // esi
  unsigned int i; // edx

  fld_e1952 = *(this + 1952);  // this+7808〔风格/分支选择〕
  for ( i = 0; fld_e1952 != 0 && i < (*(this + 1953) - fld_e1952) >> 2; ++i )  // this+7812〔nSubStateA(推断)〕
  {
    if ( *(uint32_t *)(*(this + 1952) + 4 * i) == nArg2 )  // this+7808〔风格/分支选择〕
      return 1;  // 返回 1(成功)
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4DB130 sub_4DB130 —— 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
// pArg2 = 文案类别（条目表 this+7828 + 16×类别：+0 begin/+4 end 的 dword vector）；
// uArg3 = 强制下标（-1 = rand()%条数，先 srand(id+X+Y) 播种）；选中条目经
// sub_41ACF0 取字符串后 sub_50EF20(vt+64(), 串, 0, -1) 查询/播放（同 0x4D9F00 尾参）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DB130(uint32_t *this, int pArg2, unsigned int uArg3)  // 实现：随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
{
  int result; // eax
  int pVecBegin; // ecx —— 条目 vector begin
  char *pEntry; // edi —— 类别条目（16 字节）
  int nPosY; // ebx —— vt+124() 自身 Y（播种用）
  int nSeedB; // ebx —— X+Y 累加
  int nSelfId; // eax —— vt+52() 自身 id（播种用）
  unsigned int nRand; // edx —— 选中下标
  unsigned int nCount; // edi —— 条目数
  int pParamObj; // eax —— vt+64() 参数对象
  const CHAR *pszText; // [esp-Ch] [ebp-14h] —— 选中文案

  result = 16 * (pArg2 + 489);
  pVecBegin = *(uint32_t *)((char *)this + result + 4);
  pEntry = (char *)this + result;
  if ( pVecBegin != 0 )
  {
    result = (*((uint32_t *)pEntry + 2) - pVecBegin) >> 2;
    if ( result != 0 )  // 若结果非 0（成功）
    {
      nPosY = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
      nSeedB = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + nPosY;  // 结果 = 虚调用 vt+120
      nSelfId = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);  // 结果 = 虚调用 vt+52
      srand(nSelfId + nSeedB);  // 调 设置随机种子
      nRand = uArg3;
      result = *((uint32_t *)pEntry + 1);
      if ( uArg3 == -1 )
      {
        if ( result != 0 )  // 若结果非 0（成功）
        {
          nCount = (*((uint32_t *)pEntry + 2) - result) >> 2;
          nRand = rand() % nCount;  // nRand = 调 rand
        }
        else
        {
          nRand = rand() % 0u;  // nRand = 调 rand
        }
LABEL_9:
        pszText = sub_41ACF0((unsigned int **)(*(this + 4 * pArg2 + 1957) + 4 * nRand));  // 结果 = 驻留串句柄 → 字符串指针
        pParamObj = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 64))(this);  // 结果 = 虚调用 vt+64
        return sub_50EF20(pParamObj, pszText, 0, -1);  // 气泡文本设置与量算
      }
      if ( result != 0 && uArg3 < (*((uint32_t *)pEntry + 2) - result) >> 2 )
        goto LABEL_9;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DB200 sub_4DB200 —— 15% 概率随机文案触发（0x4DB130 的门包装）
// rand()%100 < 15 才调 sub_4DB130(this, nArg2, uArg3)（淘汰/胜负文案族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DB200(uint32_t *this, int nArg2, unsigned int uArg3)  // 实现：15% 概率随机文案触发（0x4DB130 的门包装）
{
  int nRand; // eax
  int result; // eax
  int nPct; // et2 —— nRand % 100

  nRand = rand();  // nRand = 调 rand
  nPct = nRand % 100;
  result = nRand / 100;
  if ( nPct < 15 )
    return sub_4DB130(this, nArg2, uArg3);  // 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
  return result;
}



// ------------------------------------------------------------
// 0x4DB230 sub_4DB230 —— HP/MP 槽位延迟同步（+8516/+8520 双槽）
// PVP/场景 1/2/3 且双槽 == -1（未初始化）时按场景初始化（场景 3：当前 +760 属性
// + 最大HP×15%），随后按 nArg2 场景分支经 vt+672/vt+736/vt+740 与 sub_41A590
// 把槽值写回 +760 并 vt+676(0) 广播。【推断】PVP 入场/退场的 HP 缓冲补偿。
// userpurge 寄存器传参见函数体注释。
// ------------------------------------------------------------
int /*userpurge*/ sub_4DB230@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4)  // 实现：HP/MP 槽位延迟同步（+8516/+8520 双槽）
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
  if ( result == 3 || result == 1 || result == 2 )  // 若 result == 3 与/或 result == 1 与/或 result == 2
  {
    if ( pArg1[2129] == -1 && pArg1[2130] == -1 )
    {
      if ( result == 3 )
      {
        v6 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0);  // 结果 = 虚调用 vt+672
        v20 = sub_41A5E0(v6 + 760);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        v7 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1) * 0.15000001 + (double)v20);  // 结果 = 虚调用 vt+740
        pArg1[2129] = v7;
        v8 = (*(int (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t))(*pArg1 + 672))(pArg1, HIDWORD(v7), 0);  // 结果 = 虚调用 vt+672
        v21 = sub_41A5E0(v8 + 760);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        pArg1[2130] = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1) * 0.60000002  // 结果 = 虚调用 vt+740
                                    + (double)v21);
      }
      v9 = pArg1[1943];
      if ( v9 == 1 || v9 == 2 )  // 若 v9 == 1 与/或 v9 == 2
      {
        if ( sub_4DB0E0(pArg1, 196625) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
        {
          v10 = (*(int (/*stdcall*/ **)(uint32_t))(*pArg1 + 672))(0);  // 结果 = 虚调用 vt+672
          v11 = sub_41A5E0(v10 + 760);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          v12 = *pArg1;
          pArg1[2129] = v11;
          v13 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v12 + 672))(pArg1, 0);  // 调虚槽 +672：自身 HP
          v22 = sub_41A5E0(v13 + 760);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          v14 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1) * 0.30000001 + (double)v22);  // 结果 = 虚调用 vt+740
        }
        else
        {
          v15 = (*(int (/*stdcall*/ **)(uint32_t))(*pArg1 + 672))(0);  // 结果 = 虚调用 vt+672
          pArg1[2129] = sub_41A5E0(v15 + 760);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          v16 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0);  // 结果 = 虚调用 vt+672
          LODWORD(v14) = sub_41A5E0(v16 + 760);  // crypt4byte 解密校验（·0x41A590 逆运算）
        }
        pArg1[2130] = v14;
      }
    }
    if ( nArg3 != 0 )
    {
      v17 = pArg1[2129];
      v18 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t, int))*(uint32_t *)(*pArg1 + 672))(pArg1, 0, nArg2);  // 调虚槽 +672：自身 HP
    }
    else
    {
      v17 = pArg1[2130];
      LODWORD(v18) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 672))(pArg1, 0, nArg2);  // 虚调用 vt+672
    }
    sub_41A590(v18 + 760, SHIDWORD(v18), v17);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 676))(pArg1, 0);  // 虚调用 vt+676
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DB3F0 sub_4DB3F0 —— 转发垫片（stdcall）→ 0x4DA820（三参直传）。
char */*stdcall*/ sub_4DB3F0(char *pszArg1, char *pszArg2, char *pszArg3)  // 转发垫片（stdcall）→ 0x4DA820（三参直传）。
{
  return sub_4DA820(pszArg1, pszArg2, pszArg3);  // 返回 pszArg3 起，目标非空才拷
}



// ------------------------------------------------------------
// 0x4DB410 sub_4DB410 —— 怪物生成入口（MONSTER CREATE）
// sub_442D00 按索引查怪物表（名字 SSO 出参），查无（== dword_9B7C34 哨兵）或
// 名字数据为空 → off_77F3FC 打 "MONSTER CREATE FAIL! INDEX %d" 日志；
// 否则 vt+1196(this, 名字数据, nArg3) 生成。失败日志是本函数的字符串铁证。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DB410(void *this, int ArgList, int nArg3)  // 实现：怪物生成入口（MONSTER CREATE）
{
  int nIndex; // edi —— ArgList 副本（失败日志用）
  int pNameEntry; // eax —— sub_442D00 查得的怪物表条目
  int pszNameBuf; // [esp+8h] [ebp-4h] BYREF —— 名字 SSO 缓冲（sub_442D0 0 出参）

  nIndex = ArgList;
  sub_442D00(&pszNameBuf, &ArgList);  // 红黑树等键查找（_Find）
  if ( pszNameBuf == dword_9B7C34 )
    return off_77F3FC("MONSTER CREATE FAIL! INDEX %d", nIndex);  // 字符串 “MONSTER CREATE FAIL! INDEX %d”
  pNameEntry = *(uint32_t *)(pszNameBuf + 40) < 0x10u ? pszNameBuf + 20 : *(uint32_t *)(pszNameBuf + 20);
  if ( pNameEntry == 0 )
    return off_77F3FC("MONSTER CREATE FAIL! INDEX %d", nIndex);  // 字符串 “MONSTER CREATE FAIL! INDEX %d”
  else
    return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 1196))(this, pNameEntry, nArg3);  // 调虚槽 +1196：IRDCharacter__vmt4AC 默认虚槽桩（10 行 return）
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
int /*thiscall*/ sub_4DB480(int this, uint32_t *pArg2, int nArg3, int nArg4)  // 实现：反击/架招触发判定（尾调 sub_4D6D90 攻方完整反应）
{
  int nCounterState; // eax —— this+7772 反击态（1/2）
  int nGuardGrade; // edi —— 架招档位（261396..261402 → 3/11/15/0/6/2/5）
  int pAttrCont; // ebx —— vt+672(3) 属性容器（档位 = 值/10+1）
  int nGuardLvl; // edi —— 施加强度
  int nBigState; // eax —— this+7148 大状态（11/12 → 切 4）

  nCounterState = *(uint32_t *)(this + 7772);  // 读 nCounterState = this+7772（反击态）
  if ( (nCounterState == 1 || nCounterState == 2)  // 若 nCounterState == 1 与/或 nCounterState == 2
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0  // 虚调用 vt+40
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    if ( sub_4DB0E0((uint32_t *)this, 261396) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
    {
      nGuardGrade = 3;
    }
    else if ( sub_4DB0E0((uint32_t *)this, 261397) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
    {
      nGuardGrade = 11;
    }
    else if ( sub_4DB0E0((uint32_t *)this, 261398) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
    {
      nGuardGrade = 15;
    }
    else if ( sub_4DB0E0((uint32_t *)this, 261399) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
    {
      nGuardGrade = 0;
    }
    else if ( sub_4DB0E0((uint32_t *)this, 261400) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
    {
      nGuardGrade = 6;
    }
    else if ( sub_4DB0E0((uint32_t *)this, 261401) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
    {
      nGuardGrade = 2;
    }
    else
    {
      if ( sub_4DB0E0((uint32_t *)this, 261402) == 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
        goto LABEL_21;
      nGuardGrade = 5;
    }
    pAttrCont = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 672))(this, 3) / 10 + 1;  // 调虚槽 +672：自身 HP
    if ( sub_4D6750(pArg2, nGuardGrade, 20.0, nullptr) )  // 状态施加”概率/抗性”掷（rand%10000 < 率×100）
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*pArg2 + 764))(pArg2, nGuardGrade, pAttrCont, this, 1);  // 虚调用 vt+764
  }
LABEL_21:
  nAtkReaction = sub_4D6D90((int *)this, pArg2, nArg3, nArg4);  // 【攻方完整反应 vt+500（§8 双向卡肉入口）】
  if ( *(uint8_t *)(this + 7529) != 0 )  // 判定 “+7529 反击/架招生效标志”
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1236))(this);  // 调虚槽 +1236：IRDCharacter__vmt4D4 默认虚槽桩（10 行 return）
  nBigState = *(uint32_t *)(this + 7148);  // 读 nBigState = this+7148（大状态镜像槽）
  if ( nBigState == 11 || nBigState == 12 )  // 若 nBigState == 11 与/或 nBigState == 12
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 4);  // 调虚槽 +1104
  return nAtkReaction;
}



// ------------------------------------------------------------
// 0x4DB600 sub_4DB600 —— 技能作用域 AABB 相交测试【推断】
// pArg2 = 作用域槽 id：this+1550 起 4 字节表（begin/end）第 pArg2 项须非零；
// this+1905 起 32 字节/槽的作用域表第 pArg2 槽 +16/+20（X 正/负外延）与
// +24/+28（Y 正/负外延）须非全零；vt+1244(this,nArg3) 门通过后，按自身朝向
//（vt+152）决定 X 外延取侧，对 nArg3 对象做盒相交：对象 +428/+432（宽/高）÷4
// 为半宽/半高，与对象 vt+120/vt+124 坐标和自身坐标比较（X 负/正、Y 负/正四向）。
// nArg2（fastcall 第二参）在本转写体中未参与运算（寄存器残影）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4DB600(uint32_t *this, unsigned int pArg2, int nArg3)  // 实现：技能作用域 AABB 相交测试(推断)
{
  int nTgtOwner; // ebx —— 目标 vt+376() 宿主
  int pTagVec; // ecx —— this+1550 4 字节标签表 begin
  int pScopeTbl; // ecx —— this+1905 32 字节作用域表 begin
  int pScopeTbl2; // ecx
  int nExtXNeg; // edx —— 槽 +16（X 负向外延）
  uint32_t *pScopeSlot; // eax —— 作用域槽首址
  int nExtXPos; // ecx —— 槽 +20（X 正向外延）
  int nExtYNeg; // ebx —— 槽 +24（Y 负向外延）
  int nExtYPos; // eax —— 槽 +28（Y 正向外延）
  int nHalfW; // ebx —— 目标半宽（+428/4）
  int nTgtRight; // ebx —— 目标右缘 X
  int nTgtLeftA; // ebx
  int nHalfW2; // ebx
  int nTgtLeft; // ebx —— 目标左缘 X
  int nHalfW3; // ebx
  int nTgtRight2; // ebx
  int nHalfW4; // ebx
  int nHalfH; // ebx —— 目标半高（+432/4）
  int nTgtTop; // ebx —— 目标上缘 Y
  int nHalfH2; // ebx
  int nTgtBottom; // esi —— 目标下缘 Y
  int nExtXPosSave; // [esp+Ch] [ebp-Ch]
  int nExtYNegSave; // [esp+10h] [ebp-8h]
  int nExtXNegSave; // [esp+20h] [ebp+8h]
  int nExtYPosSave; // [esp+24h] [ebp+Ch]

  nTgtOwner = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 376))(nArg3);  // 调虚槽 +376：坐标同步包（type 37）
  if ( nTgtOwner != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)  // 虚调用 vt+376
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 40))(nArg3, 17) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 940))(nArg3) == 1 )  // 调虚槽 +940
  {
    return false;
  }
  pTagVec = *(this + 1550);  // this+6200〔pTbl6200〕
  if ( pTagVec == 0 )  // pTagVec=this+6200 pTbl6200
    return false;
  if ( (*(this + 1551) - pTagVec) >> 2 <= pArg2 )  // pTagVec=this+6200 pTbl6200
    return false;
  pScopeTbl = *(this + 1905);  // 读 pScopeTbl = this+7620（速度/属性参数对象）
  if ( pScopeTbl == 0 )  // pScopeTbl=this+7620 【推断】属性/速度面板对象
    return false;
  if ( (*(this + 1906) - pScopeTbl) >> 5 <= pArg2 )  // pScopeTbl=this+7620 【推断】属性/速度面板对象
    return false;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, nArg3) == 0 )  // 虚调用 vt+1244
    return false;
  pScopeTbl2 = *(this + 1905);  // 读 pScopeTbl2 = this+7620（速度/属性参数对象）
  nExtXNeg = *(uint32_t *)(pScopeTbl2 + 32 * pArg2 + 16);  // pScopeTbl2=this+7620 【推断】属性/速度面板对象
  pScopeSlot = (uint32_t *)(pScopeTbl2 + 32 * pArg2);  // pScopeTbl2=this+7620 【推断】属性/速度面板对象
  nExtXPos = pScopeSlot[5];
  nExtYNeg = pScopeSlot[6];
  nExtYPos = pScopeSlot[7];
  nExtXPosSave = nExtXPos;
  nExtXNegSave = nExtXNeg;
  nExtYNegSave = nExtYNeg;
  nExtYPosSave = nExtYPos;
  if ( nExtXPos == 0 && nExtXNeg == 0 )  // 若 nExtXPos == 0 与/或 nExtXNeg == 0
    return false;
  if ( nExtYNeg == 0 && nExtYPos == 0 )  // 若 nExtYNeg == 0 与/或 nExtYPos == 0
    return false;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )  // 虚调用 vt+152
  {
    nHalfW = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 428))(nArg3) / 4;  // 调虚槽 +428
    nTgtRight = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3) + nHalfW;  // 调虚槽 +120：动画对象
    if ( nTgtRight < (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - nExtXPosSave )  // 虚调用 vt+120
      return false;
    nHalfW2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 428))(nArg3) / 4;  // 调虚槽 +428
    nTgtLeftA = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3) - nHalfW2;  // 调虚槽 +120：动画对象
    if ( nTgtLeftA > nExtXNegSave + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) )  // 虚调用 vt+120
      return false;
  }
  else
  {
    nHalfW3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 428))(nArg3) / 4;  // 调虚槽 +428
    nTgtLeft = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3) - nHalfW3;  // 调虚槽 +120：动画对象
    if ( nTgtLeft > nExtXPosSave + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) )  // 虚调用 vt+120
      return false;
    nHalfW4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 428))(nArg3) / 4;  // 调虚槽 +428
    nTgtRight2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3) + nHalfW4;  // 调虚槽 +120：动画对象
    if ( nTgtRight2 < (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - nExtXNegSave )  // 虚调用 vt+120
      return false;
  }
  nHalfH = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 432))(nArg3) / 4;  // 调虚槽 +432
  nTgtTop = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 124))(nArg3) + nHalfH;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  if ( nTgtTop < (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) - nExtYNegSave )  // 虚调用 vt+124
    return false;
  nHalfH2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 432))(nArg3) / 4;  // 调虚槽 +432
  nTgtBottom = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 124))(nArg3) - nHalfH2;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  return nTgtBottom <= nExtYPosSave + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 虚调用 vt+124
}



// ------------------------------------------------------------
// 0x4DB810 sub_4DB810 —— 范围命中概率掷（对宿主 this+120 对象列表逐个判定）
// pArg2 = 作用域槽 id（this+1905 起 32 字节/槽）。分三档概率（槽内 float×100 vs
// rand()%10000）：+4 = 条件 17（存活）且焦点表（this+1576，152 字节/条）允许的目标；
// +12 = 条件 545 的目标；+8 = 兜底（循环走完仍未命中时）。目标还须过 sub_4E4630
// （可见/可选）、非本对象、sub_4E5CA0==0、大状态!=4 或状态 8、无敌门 vt+724==0、
// vt+1248(this,槽,目标) 门。命中即返回 true。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4DB810(uint32_t *this, unsigned int pArg2)  // 实现：范围命中概率掷（对宿主 this+120 对象列表逐个判定）
{
  unsigned int nObjIdx; // ebx —— 对象列表下标
  int pHostObj1; // ecx —— 宿主对象（this+116）
  int pObjVec1; // edx —— 对象 vector begin
  int nVecCount; // eax —— 对象数
  int pObjVec2; // edx
  int pListObj; // ecx —— 列表对象（条件 17 检查用）
  char bCond17; // al —— 条件 17（存活）结果
  int pHostObj2; // ecx
  int pObjVec3; // edx
  uint32_t *pTarget; // edi —— 候选目标（条件 17 分支）
  int pFocusTbl1; // eax —— 焦点表（this+1576，152 字节/条）
  char nFocusFlag; // bl —— 焦点条目 +18 标志
  int pFocusTbl2; // edx
  int pScopeSlot1; // edi —— 作用域槽（+4 概率）
  int pListObj2; // ecx —— 列表对象（条件 545 分支）
  int pHostObj3; // ecx
  int pObjVec4; // edx
  int pTarget2; // edi —— 候选目标（条件 545 分支）
  int pScopeSlot2; // edi —— 作用域槽（+12 概率）
  int pScopeSlot3; // esi —— 作用域槽（+8 兜底概率）
  unsigned int nObjIdxSave; // [esp+10h] [ebp-4h]

  nObjIdx = 0;
  while ( 1 )  // 无限循环
  {
    pHostObj1 = *(this + 29);  // 读 pHostObj1 = this+116（观察者容器）
    pObjVec1 = *(uint32_t *)(pHostObj1 + 120);  // pHostObj1=this+116 观察者 vector 尾针
    nObjIdxSave = nObjIdx;
    nVecCount = pObjVec1 != 0 ? (*(uint32_t *)(pHostObj1 + 124) - pObjVec1) >> 2 : 0;  // pHostObj1=this+116 观察者 vector 尾针
    if ( (int)nObjIdx >= nVecCount )
      break;
    pObjVec2 = *(uint32_t *)(pHostObj1 + 120);  // pHostObj1=this+116 观察者 vector 尾针
    if ( pObjVec2 != 0 && nObjIdx < (*(uint32_t *)(pHostObj1 + 124) - pObjVec2) >> 2 )  // pHostObj1=this+116 观察者 vector 尾针
      pListObj = *(uint32_t *)(pObjVec2 + 4 * nObjIdx);
    else
      pListObj = 0;
    bCond17 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj + 40))(pListObj, 17);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    pHostObj2 = *(this + 29);  // 读 pHostObj2 = this+116（观察者容器）
    pObjVec3 = *(uint32_t *)(pHostObj2 + 120);  // pHostObj2=this+116 观察者 vector 尾针
    if ( bCond17 != 0 )
    {
      if ( pObjVec3 != 0 && nObjIdx < (*(uint32_t *)(pHostObj2 + 124) - pObjVec3) >> 2 )  // pHostObj2=this+116 观察者 vector 尾针
        pTarget = *(uint32_t **)(pObjVec3 + 4 * nObjIdx);
      else
        pTarget = nullptr;
      if ( pTarget != this )
      {
        pFocusTbl1 = *(this + 1576);
        nFocusFlag = 0;
        if ( (pFocusTbl1 == 0
           || (*(this + 1577) - pFocusTbl1) / 152 <= pArg2
           || (pFocusTbl2 = *(this + 1576), nFocusFlag = *(uint8_t *)(pFocusTbl2 + 152 * pArg2 + 18), *(uint8_t *)(pFocusTbl2 + 152 * pArg2 + 19) != 0))  // 范围命中概率掷（对宿主 this+120 对象列表逐个判定）
          && (uint8_t)sub_4E4630(pTarget) != 0  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
          || nFocusFlag != 0 && (uint8_t)sub_4E4630(pTarget) == 0 )  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
        {
          if ( (uint8_t)sub_4E5CA0(pTarget) == 0  // 阵营号 200..204 判定（200 起逐个比较）
            && ((*(int (/*thiscall*/ **)(uint32_t *))(*pTarget + 840))(pTarget) != 4  // 虚调用 vt+840
             || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pTarget + 776))(pTarget, 8) != 0)  // 虚调用 vt+776
            && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pTarget + 724))(pTarget) == 0  // 虚调用 vt+724
            && (*(uint8_t (/*thiscall*/ **)(uint32_t *, unsigned int, uint32_t *))(*this + 1248))(this, pArg2, pTarget) != 0 )  // 虚调用 vt+1248
          {
            pScopeSlot1 = *(this + 1905) + 32 * pArg2;  // this+7620〔pStatusPanel(推断)〕
            if ( *(float *)(pScopeSlot1 + 4) * 100.0 > (double)(rand() % 10000) )  // 调 取伪随机数
              return true;
          }
        }
        nObjIdx = nObjIdxSave;
      }
LABEL_29:
      ++nObjIdx;
    }
    else
    {
      if ( pObjVec3 != 0 && nObjIdx < (*(uint32_t *)(pHostObj2 + 124) - pObjVec3) >> 2 )  // pHostObj2=this+116 观察者 vector 尾针
        pListObj2 = *(uint32_t *)(*(uint32_t *)(pHostObj2 + 120) + 4 * nObjIdx);  // pHostObj2=this+116 观察者 vector 尾针
      else
        pListObj2 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 40))(pListObj2, 545) == 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        goto LABEL_29;
      pHostObj3 = *(this + 29);  // 读 pHostObj3 = this+116（观察者容器）
      pObjVec4 = *(uint32_t *)(pHostObj3 + 120);  // pHostObj3=this+116 观察者 vector 尾针
      if ( pObjVec4 != 0 && nObjIdx < (*(uint32_t *)(pHostObj3 + 124) - pObjVec4) >> 2 )  // pHostObj3=this+116 观察者 vector 尾针
        pTarget2 = *(uint32_t *)(pObjVec4 + 4 * nObjIdx);
      else
        pTarget2 = 0;
      if ( (uint8_t)sub_4E4630(pTarget2) == 0  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
        || (*(uint8_t (/*thiscall*/ **)(uint32_t *, unsigned int, int))(*this + 1248))(this, pArg2, pTarget2) == 0 )  // 虚调用 vt+1248
      {
        goto LABEL_29;
      }
      pScopeSlot2 = *(this + 1905) + 32 * pArg2;  // this+7620〔pStatusPanel(推断)〕
      if ( *(float *)(pScopeSlot2 + 12) * 100.0 > (double)(rand() % 10000) )  // 调 取伪随机数
        return true;
      ++nObjIdx;
    }
  }
  pScopeSlot3 = *(this + 1905) + 32 * pArg2;  // this+7620〔pStatusPanel(推断)〕
  return *(float *)(pScopeSlot3 + 8) * 100.0 > (double)(rand() % 10000);  // 调 取伪随机数
}



// 0x4DBA80 sub_4DBA80 —— 大状态进入副作用处理器（增益侧）
// pArg2 = 新大状态 id：6 → vt+1080 收招；9/10 → +7596=50、作用域表（this+1905，
// 32 字节/槽）全体槽 +4 权重 ×1.3（怒气/爆发加成）；12 → 视野 +7520 ×1.5 且
// sub_4DAB60(14/15) 时 sub_49C620(2,1,0)+1838=200；14/15 → vt+560 姿态；24 → +7400=200。
// 收尾把 this+{pArg2+1826}/+{pArg2+1852} 两个槽值写入 *(this+1931)+80/+84
//（【推断】攻/防权重槽快照）。与退出侧 0x4DBC20 成对（×0.769 还原）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DBA80(int *this, int pArg2)  // 实现：大状态进入副作用处理器（增益侧）
{
  unsigned int nScopeIdx; // ecx —— 作用域表下标
  int nScopeOff; // edi —— 32 字节步进偏移
  int pScopeTbl; // edx —— this+1905 作用域表
  int pScopeSlot; // eax —— 当前槽
  double fNewWeight; // st7 —— 槽 +4 权重 ×1.3
  int result; // eax

  *(this + 1926) = sub_699000((int)(this + 1910));  // clock_now(clk)
  switch ( pArg2 )  // 按 pArg2 分派
  {
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      (*(void (/*thiscall*/ **)(int *))(*this + 1080))(this);  // 虚调用 vt+1080
      break;
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
      *(this + 1899) = 50;  // 写 this+7596 = 50（段号横向偏置）
      nScopeIdx = 0;
      *(this + pArg2 + 1826) = 100;
      *(this + pArg2 + 1852) = 100;
      for ( nScopeOff = 0; ; nScopeOff += 32 )
      {
        pScopeTbl = *(this + 1905);  // 读 pScopeTbl = this+7620（速度/属性参数对象）
        if ( pScopeTbl == 0 || nScopeIdx >= (*(this + 1906) - pScopeTbl) >> 5 )  // pScopeTbl=this+7620 【推断】属性/速度面板对象
          break;
        pScopeSlot = nScopeOff + pScopeTbl;
        fNewWeight = *(float *)(pScopeTbl + nScopeOff + 4) * 1.3;  // pScopeTbl=this+7620 【推断】属性/速度面板对象
        ++nScopeIdx;
        *(float *)(pScopeSlot + 4) = fNewWeight;
      }
      break;
    case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
      *(this + 1880) = (uint64_t)((double)*(this + 1880) * 1.5);  // 写 this+7520 = (uint64_t)((double)*(this + 1880) * 1.5)（攻击参数面）
      if ( sub_4DAB60(this, 14) || sub_4DAB60(this, 15) )  // 标签/条件集合成员判定
      {
        sub_49C620(this, 2, 1, 0);  // 命令下发包装（组 id = this+4，值重复两遍）
        *(this + 1838) = 200;
      }
      break;
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 2, 0, 0, 0);  // 虚调用 vt+560
      break;
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 虚调用 vt+560
      break;
    case 24:  // case 24 = ENUM_CMDPACKET_EXTEND_AVATAR
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
// 0x4DBC20 sub_4DBC20 —— 大状态退出副作用处理器（0x4DBA80 的还原对偶）
// pArg2 = 旧大状态 id：0 → vt+560+vt+1204 复位；9/10 → +7596=0、作用域表 +4 权重
// ×0.76923078（=1/1.3 还原）；12 → 视野 ×0.66666669（=2/3 还原）；14/24 同入口侧。
// 收尾把槽值取负写 *(this+1931)+80（退出标记）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DBC20(int *this, int pArg2)  // 实现：大状态退出副作用处理器（0x4DBA80 的还原对偶）
{
  int nScopeOff; // edi —— 32 字节步进偏移
  unsigned int nScopeIdx; // ecx —— 作用域表下标
  int pScopeTbl; // edx —— this+1905 作用域表
  int pScopeSlot; // eax —— 当前槽
  double fRestoredWeight; // st7 —— 槽 +4 权重 ÷1.3（×0.769 还原）
  int result; // eax

  switch ( pArg2 )  // 按 pArg2 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 虚调用 vt+560
      (*(void (/*thiscall*/ **)(int *))(*this + 1204))(this);  // 虚调用 vt+1204
      break;
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
      nScopeOff = 0;
      *(this + 1899) = 0;  // 写 this+7596 = 0（段号横向偏置）
      *(this + pArg2 + 1826) = 100;
      *(this + pArg2 + 1852) = 100;
      for ( nScopeIdx = 0; ; ++nScopeIdx )
      {
        pScopeTbl = *(this + 1905);  // 读 pScopeTbl = this+7620（速度/属性参数对象）
        if ( pScopeTbl == 0 || nScopeIdx >= (*(this + 1906) - pScopeTbl) >> 5 )  // pScopeTbl=this+7620 【推断】属性/速度面板对象
          break;
        pScopeSlot = nScopeOff + pScopeTbl;
        fRestoredWeight = *(float *)(pScopeTbl + nScopeOff + 4) * 0.76923078;  // pScopeTbl=this+7620 【推断】属性/速度面板对象
        nScopeOff += 32;
        *(float *)(pScopeSlot + 4) = fRestoredWeight;
      }
      break;
    case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
      *(this + 1880) = (uint64_t)((double)*(this + 1880) * 0.66666669);  // 写 this+7520 = (uint64_t)((double)*(this + 1880) * 0.66666669)（攻击参数面）
      if ( sub_4DAB60(this, 14) || sub_4DAB60(this, 15) )  // 标签/条件集合成员判定
      {
        sub_49C620(this, 2, 0, 0);  // 命令下发包装（组 id = this+4，值重复两遍）
        *(this + 1838) = 200;
      }
      break;
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 虚调用 vt+560
      break;
    case 24:  // case 24 = ENUM_CMDPACKET_EXTEND_AVATAR
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
// 随后 16/12 取整算栅格坐标 (nSelfX/16, nSelfGridY/12) 与对方栅格 (v24/16, v23/12)，
// 调 sub_58AD30（栅格相交判定）→ 返回 1 时调 sub_58B200（栅格推挤解算，输出 v26/v25
// 为修正后坐标）→ 缓存到 +2080..2083 / +2078/+2079（previous frame 对比）。
// 与 0x4DC130（单向拒绝测试）、0x4D87B0（同族栅格调）配套 ——
// 这是**客户端本地的角色间推挤/防重叠**，与服务端命中判定无关（研究 §1.1 结论一致）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4DBDB0(int *this, uint32_t *uArg2, uint32_t *uArg3)  // 实现：空间栅格重叠检测（碰撞/挤压分离轴；研究第 24/25 轮族）
{
  int pRefObj; // ecx
  int pScopeTbl1; // edx
  int pScopeTbl2; // edi
  int pScopeTbl3; // edi
  int pScopeTbl4; // edi
  int pScopeTbl5; // edi
  int nSelfX; // kr04_4
  int nSelfGridX; // edi
  int nSelfGridY; // ebx
  int pVtbl; // eax
  int nGridCmp; // eax
  int nPushX; // ecx
  int nPushY; // edx
  int nJitterPct; // ebx
  int nHasTarget; // [esp+4h] [ebp-14h]
  float fRefX; // [esp+8h] [ebp-10h]
  float fRefX2; // [esp+8h] [ebp-10h]
  float fRefY1; // [esp+8h] [ebp-10h]
  float fRefY2; // [esp+8h] [ebp-10h]
  int nRefGridY; // [esp+8h] [ebp-10h]
  int nRefGridX; // [esp+Ch] [ebp-Ch]
  int nPushYOut; // [esp+10h] [ebp-8h] BYREF
  int nPushXOut; // [esp+14h] [ebp-4h] BYREF

  pRefObj = *(this + 1813);  // this+7252〔pTarget7252〕
  if ( pRefObj == 0 )  // pRefObj=this+7252 pTarget7252
    return;
  pScopeTbl1 = *(this + 1905);  // 读 pScopeTbl1 = this+7620（速度/属性参数对象）
  if ( pScopeTbl1 == 0 || (*(this + 1906) - pScopeTbl1) >> 5 == 0 )  // pScopeTbl1=this+7620 【推断】属性/速度面板对象
    return;
  pScopeTbl2 = *(this + 1905);  // 读 pScopeTbl2 = this+7620（速度/属性参数对象）
  fRefX = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pRefObj + 120))(pRefObj);  // 调虚槽 +120：动画对象
  if ( (double)(*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - (double)*(int *)(pScopeTbl2 + 16) * 0.75 <= fRefX )  // 虚调用 vt+120
  {
    pScopeTbl3 = *(this + 1905);  // 读 pScopeTbl3 = this+7620（速度/属性参数对象）
    fRefX2 = (float)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
    if ( (double)(*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + (double)*(int *)(pScopeTbl3 + 16) * 0.75 >= fRefX2 )  // 虚调用 vt+120
      *uArg2 = 4;
    else
      *uArg2 = 1;
  }
  else
  {
    *uArg2 = 0;
  }
  pScopeTbl4 = *(this + 1905);  // 读 pScopeTbl4 = this+7620（速度/属性参数对象）
  fRefY1 = (float)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));  // this+7252〔pTarget7252〕
  nHasTarget = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
  if ( (double)nHasTarget - (double)*(int *)(pScopeTbl4 + 24) * 0.75 <= fRefY1 )  // pScopeTbl4=this+7620 【推断】属性/速度面板对象
  {
    pScopeTbl5 = *(this + 1905);  // 读 pScopeTbl5 = this+7620（速度/属性参数对象）
    fRefY2 = (float)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));  // this+7252〔pTarget7252〕
    nHasTarget = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
    if ( (double)nHasTarget + (double)*(int *)(pScopeTbl5 + 28) * 0.75 >= fRefY2 )  // pScopeTbl5=this+7620 【推断】属性/速度面板对象
      *uArg3 = 4;
    else
      *uArg3 = 3;
  }
  else
  {
    *uArg3 = 2;
  }
  nSelfX = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
  nSelfGridX = nSelfX / 16;
  nSelfGridY = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) / 12;  // 结果 = 虚调用 vt+124
  nRefGridX = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)) / 16;  // this+7252〔pTarget7252〕
  nRefGridY = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813)) / 12;  // this+7252〔pTarget7252〕
  pVtbl = *this;
  nPushXOut = nSelfX / 16;
  nPushYOut = nSelfGridY;
  LOBYTE(nHasTarget) = (*(int (/*thiscall*/ **)(int *))(pVtbl + 436))(this) > 0;  // 虚函数调用 槽+436
  nGridCmp = sub_58AD30(nRefGridX, nRefGridY, nHasTarget);  // 结果 = 可行走判定：网格值≠2 且（允许对角 或 网格值≠1）→ true
  if ( (nSelfX / 16 != *(this + 2078)  // this+8312〔nHoldPosZ(推断)〕
     || nSelfGridY != *(this + 2079)  // this+8316〔nHoldSrc(推断)〕
     || nRefGridX != *(this + 2080)  // this+8320〔pHoldHost(推断)〕
     || nRefGridY != *(this + 2081)  // this+8324〔bHoldMode(推断)〕
     || *(this + 2082) == -1  // this+8328〔f_2088〕
     || *(this + 2083) == -1)  // this+8332〔f_208C〕
    && nGridCmp == 1 )
  {
    sub_58B200(nSelfX / 16, nSelfGridY, nRefGridX, nRefGridY, &nPushXOut, &nPushYOut, nHasTarget);  // 寻路总入口：复位→58B140 搜索→沿父链回溯到第 1 步→输出目标格 (a6,a7)→复
    nPushX = nPushXOut;
    nPushY = nPushYOut;
    *(this + 2082) = nPushXOut;  // this+8328〔f_2088〕
    *(this + 2083) = nPushY;  // this+8332〔f_208C〕
LABEL_25:
    *(this + 2080) = nRefGridX;  // this+8320〔pHoldHost(推断)〕
    *(this + 2081) = nRefGridY;  // this+8324〔bHoldMode(推断)〕
    goto LABEL_26;
  }
  nPushX = *(this + 2082);  // this+8328〔f_2088〕
  nPushY = *(this + 2083);  // this+8332〔f_208C〕
  nPushXOut = nPushX;  // nPushX=this+8328 f_2088
  nPushYOut = nPushY;  // nPushY=this+8332 f_208C
  if ( nGridCmp != 0 )
  {
    if ( nGridCmp == 1 )
      goto LABEL_25;
  }
  else
  {
    sub_58B200(nSelfX / 16, nSelfGridY, *(this + 2080), *(this + 2081), &nPushXOut, &nPushYOut, nHasTarget);  // 寻路总入口：复位→58B140 搜索→沿父链回溯到第 1 步→输出目标格 (a6,a7)→复
    nPushX = nPushXOut;  // nPushX=this+8328 f_2088
    nPushY = nPushYOut;  // nPushY=this+8332 f_208C
    *(this + 2082) = nPushXOut;  // this+8328〔f_2088〕
    *(this + 2083) = nPushY;  // this+8332〔f_208C〕
  }
LABEL_26:
  *(this + 2078) = nSelfGridX;  // this+8312〔nHoldPosZ(推断)〕
  *(this + 2079) = nSelfGridY;  // this+8316〔nHoldSrc(推断)〕
  *(this + 2082) = nPushX;  // this+8328〔f_2088〕
  *(this + 2083) = nPushY;  // this+8332〔f_208C〕
  if ( nSelfGridX >= nPushX )  // nPushX=this+8328 f_2088
    *uArg2 = nSelfGridX > nPushX ? 0 : 4;  // nPushX=this+8328 f_2088
  else
    *uArg2 = 1;
  if ( nSelfGridY <= nPushY )  // nPushY=this+8332 f_208C
    *uArg3 = (nSelfGridY >= nPushY) + 3;  // nPushY=this+8332 f_208C
  else
    *uArg3 = 2;
  if ( (uint8_t)sub_4E4630(*(this + 1813)) != 0  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1108))(this) == 0 )  // 虚调用 vt+1108
  {
    nJitterPct = *(this + 1898) + *(this + 1899);  // this+7592〔nAtkSegSlot7592〕
    if ( rand() % 100 >= nJitterPct )  // 调 取伪随机数
    {
      *uArg2 = sub_432E50(*uArg2);  // 结果 = 关系码对调映射
      *uArg3 = sub_432E50(*uArg3);  // 结果 = 关系码对调映射
    }
  }
}


// ------------------------------------------------------------
// 0x4DC130 sub_4DC130 —— 单向拒绝测试（0x4DBDB0 的简化版，只判越界方向）
// 取作用域表(this+1905)首槽 +16（X 尺寸）/+24（Y 尺寸）的一半为阈值：目标 X >
// 自身X + W/2 → *uArg3=1（在右侧外）；目标 Y > 自身Y + H/2 → *uArg4=3（在下侧外）；
// 否则 0/2。表空时不动出参。
// ------------------------------------------------------------
void /*thiscall*/ sub_4DC130(uint32_t *this, int nArg2, uint32_t *uArg3, uint32_t *uArg4)  // 实现：单向拒绝测试（0x4DBDB0 的简化版，只判越界方向）
{
  int pScopeTbl1; // ecx
  int pScopeTbl2; // edi
  int nSelfX; // ebx
  int nScopeW; // eax
  int pScopeTbl3; // ebx
  int nYThresh; // esi

  pScopeTbl1 = *(this + 1905);  // 读 pScopeTbl1 = this+7620（速度/属性参数对象）
  if ( pScopeTbl1 != 0 && (*(this + 1906) - pScopeTbl1) >> 5 != 0 )  // pScopeTbl1=this+7620 【推断】属性/速度面板对象
  {
    pScopeTbl2 = pScopeTbl1;  // pScopeTbl1=this+7620 【推断】属性/速度面板对象
    nSelfX = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
    nScopeW = *(uint32_t *)(pScopeTbl2 + 16);
    *uArg3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2) > nScopeW / 2 + nSelfX;  // 调虚槽 +120：动画对象
    pScopeTbl3 = *(this + 1905);  // 读 pScopeTbl3 = this+7620（速度/属性参数对象）
    nYThresh = *(uint32_t *)(pScopeTbl3 + 24) / 2 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 结果 = 虚调用 vt+124
    *uArg4 = ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2) > nYThresh) + 2;  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  }
}



// ------------------------------------------------------------
// 0x4DC1C0 sub_4DC1C0 —— 空作用域槽回收
// 遍历 this+1905 作用域表（32 字节/槽），槽 +16/+20/+24/+28 四向外延全为 0
//（无范围）时调 vt+1212(槽id) 移除该槽。【推断】无范围槽的清理。
// ------------------------------------------------------------
void /*thiscall*/ sub_4DC1C0(uint32_t *this)  // 实现：空作用域槽回收
{
  unsigned int nSlotIdx; // edi
  int i; // ebx
  int pScopeTbl; // ecx
  uint32_t *pScopeSlot; // eax

  nSlotIdx = 0;
  for ( i = 0; ; i += 32 )
  {
    pScopeTbl = *(this + 1905);  // 读 pScopeTbl = this+7620（速度/属性参数对象）
    if ( pScopeTbl == 0 || nSlotIdx >= (*(this + 1906) - pScopeTbl) >> 5 )  // pScopeTbl=this+7620 【推断】属性/速度面板对象
      break;
    pScopeSlot = (uint32_t *)(i + *(this + 1905));  // this+7620〔pStatusPanel(推断)〕
    if ( *(uint32_t *)(pScopeTbl + i + 16) == 0 && pScopeSlot[6] == 0 && pScopeSlot[7] == 0 && pScopeSlot[5] == 0 )  // pScopeTbl=this+7620 【推断】属性/速度面板对象
      (*(void (/*thiscall*/ **)(uint32_t *, unsigned int))(*this + 1212))(this, nSlotIdx);  // 虚调用 vt+1212
    ++nSlotIdx;
  }
}



// ------------------------------------------------------------
// 0x4DC220 sub_4DC220 —— 属性修改器表批量应用（buff/加成侧）【推断】
// 遍历 this+7236/+7240 的 12 字节条目：+0 = 属性类别（0..0xC → 属性块偏移
// 844/816/60/88/116/144/1012/1040/1068/1096/4/900/466），+4 = 百分比标志，
// +8 = 数值。对 vt+672(0) 属性块写入：百分比 ×0.01 乘算（防篡读对），否则加算。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4DC220(unsigned int *this)  // 实现：属性修改器表批量应用（buff/加成侧）(推断)
{
  int nTblOff; // eax
  unsigned int result; // eax
  int pEntry; // edi
  int pAttrBlk; // eax
  unsigned int pStatFld; // esi
  uint64_t nNewVal64; // rax
  int nAddVal; // edi
  float fPct; // [esp+Ch] [ebp-10h]
  int nTblOffSave; // [esp+14h] [ebp-8h]
  unsigned int nEntryIdx; // [esp+18h] [ebp-4h]

  nTblOff = 0;
  for ( nEntryIdx = 0; ; ++nEntryIdx )
  {
    nTblOffSave = nTblOff;
    result = *(this + 1809);
    if ( result == 0 )
      break;
    result = (int)(*(this + 1810) - result) / 12;
    if ( nEntryIdx >= result )
      break;
    pEntry = nTblOffSave + *(this + 1809);
    pAttrBlk = (*(int (/*thiscall*/ **)(unsigned int *, uint32_t))(*this + 672))(this, 0);  // 结果 = 虚调用 vt+672
    switch ( *(uint32_t *)pEntry )  // 按 *(uint32_t *)pEntry 分派
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        pStatFld = pAttrBlk + 844;
        goto LABEL_18;
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        pStatFld = pAttrBlk + 816;
        goto LABEL_18;
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        pStatFld = pAttrBlk + 60;
        goto LABEL_18;
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        pStatFld = pAttrBlk + 88;
        goto LABEL_18;
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        pStatFld = pAttrBlk + 116;
        goto LABEL_18;
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        pStatFld = pAttrBlk + 144;
        goto LABEL_18;
      case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
        pStatFld = pAttrBlk + 1012;
        goto LABEL_18;
      case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
        pStatFld = pAttrBlk + 1040;
        goto LABEL_18;
      case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
        pStatFld = pAttrBlk + 1068;
        goto LABEL_18;
      case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
        pStatFld = pAttrBlk + 1096;
        goto LABEL_18;
      case 0xA:
        pStatFld = pAttrBlk + 4;
        goto LABEL_18;
      case 0xB:
        pStatFld = pAttrBlk + 900;
        goto LABEL_18;
      case 0xC:
        pStatFld = pAttrBlk + 466;
LABEL_18:
        if ( pStatFld != 0 )
        {
          if ( *(uint8_t *)(pEntry + 4) != 0 )
          {
            fPct = (double)*(int *)(pEntry + 8) * 0.0099999998;
            nNewVal64 = (uint64_t)((double)sub_41A5E0(pStatFld) * fPct);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          }
          else
          {
            nAddVal = *(uint32_t *)(pEntry + 8) / 100;
            LODWORD(nNewVal64) = nAddVal + sub_41A5E0(pStatFld);  // crypt4byte 解密校验（·0x41A590 逆运算）
          }
          sub_41A590(pStatFld, SHIDWORD(nNewVal64), nNewVal64);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
        }
        break;
      default:
        break;
    }
    nTblOff = nTblOffSave + 12;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DC390 sub_4DC390 —— 伤害类型过滤（0x4D5A60 vt+648 的标签门包装）
// 先取 vt+648(this,uArg2,nArg3) 的命中类型：==3 直接透传；否则对照受方 attackinfo
// +12（0=物理/1=魔法）与 +20（命中子类型）查标签 130816/65281/196612..196615
//（sub_4DB0E0，0x4DB0E0 头注的 id 表）命中任一 → *uArg2=0 返 2（无效化）；
// attackinfo+128 非零或 sub_4DAB60(6) 不成立 → 透传原类型，否则返 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DC390(uint8_t *this, uint32_t *uArg2, int nArg3)  // 实现：伤害类型过滤（0x4D5A60 vt+648 的标签门包装）
{
  int result; // eax
  int nDmgTypeSaved; // [esp+18h] [ebp+Ch]

  result = sub_4D5A60(this, uArg2, nArg3);  // 伤害类型/命中类型计算 vt+648（研究 §1.2 定案 6 版本之一）
  nDmgTypeSaved = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12) == 1 && sub_4DB0E0(this, 130816) != 0  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12) == 0 && sub_4DB0E0(this, 65281) != 0  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 20) == 0 && sub_4DB0E0(this, 196612) != 0  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 20) == 1 && sub_4DB0E0(this, 196613) != 0  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 20) == 3 && sub_4DB0E0(this, 196614) != 0  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 20) == 2 && sub_4DB0E0(this, 196615) != 0 )  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
    {
      *uArg2 = 0;
      return 2;
    }
    else if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 128) != 0 || !sub_4DAB60(this, 6) )  // 标签/条件集合成员判定
    {
      return nDmgTypeSaved;
    }
    else
    {
      return 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DC4D0 sub_4DC4D0 —— 宿主对象列表连带处理（死亡/清除族）【推断】
// 遍历宿主（this+116）+8/+12 对象列表：条件 529（受击态族）且车主 == nArg2 车主
// 且 vt+308（本地）→ vt+728(0,1,0) HP 归零；条件 33 且 +676==1 且车主匹配 →
// vt+312(0) 关受击盒。nArg2 = 参照对象（疑为被淘汰者/触发源）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DC4D0(uint32_t *this, int nArg2)  // 实现：宿主对象列表连带处理（死亡/清除族）(推断)
{
  uint32_t *pSelf; // ebx
  unsigned int nObjIdx; // edi
  int pHostObj1; // ecx
  int pObjVec1; // edx
  int result; // eax
  int pObjVec2; // edx
  int pListObj1; // ecx
  char bCond529; // al
  int pHostObj2; // ecx
  int pObjVec3; // edx
  int pListObj2; // esi
  int nObjOwner; // ebx
  int pListObj3; // ecx
  int pHostObj3; // ecx
  int pObjVec4; // edx
  uint32_t *pListObj4; // esi
  int nObjOwner2; // ebx

  pSelf = this;
  nObjIdx = 0;
  while ( 1 )  // 无限循环
  {
    pHostObj1 = pSelf[29];
    pObjVec1 = *(uint32_t *)(pHostObj1 + 8);
    result = pObjVec1 != 0 ? (*(uint32_t *)(pHostObj1 + 12) - pObjVec1) >> 2 : 0;
    if ( (int)nObjIdx >= result )
      return result;
    pObjVec2 = *(uint32_t *)(pHostObj1 + 8);
    if ( pObjVec2 != 0 && nObjIdx < (*(uint32_t *)(pHostObj1 + 12) - pObjVec2) >> 2 )
      pListObj1 = *(uint32_t *)(pObjVec2 + 4 * nObjIdx);
    else
      pListObj1 = 0;
    bCond529 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj1 + 40))(pListObj1, 529);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    pHostObj2 = pSelf[29];
    pObjVec3 = *(uint32_t *)(pHostObj2 + 8);
    if ( bCond529 != 0 )
    {
      if ( pObjVec3 != 0 && nObjIdx < (*(uint32_t *)(pHostObj2 + 12) - pObjVec3) >> 2 )
        pListObj2 = *(uint32_t *)(pObjVec3 + 4 * nObjIdx);
      else
        pListObj2 = 0;
      nObjOwner = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pListObj2 + 376))(pListObj2);  // 调虚槽 +376：坐标同步包（type 37）
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2) != nObjOwner  // 调虚槽 +376：坐标同步包（type 37）
        || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pListObj2 + 308))(pListObj2) == 0 )  // 调虚槽 +308：是否本地玩家
      {
        goto LABEL_31;
      }
      (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t))(*(uint32_t *)pListObj2 + 728))(pListObj2, 0, 1, 0);  // 调虚槽 +728：HP setter/扣血
      pSelf = this;
      ++nObjIdx;
    }
    else
    {
      if ( pObjVec3 != 0 && nObjIdx < (*(uint32_t *)(pHostObj2 + 12) - pObjVec3) >> 2 )
        pListObj3 = *(uint32_t *)(*(uint32_t *)(pHostObj2 + 8) + 4 * nObjIdx);
      else
        pListObj3 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj3 + 40))(pListObj3, 33) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      {
        pHostObj3 = pSelf[29];
        pObjVec4 = *(uint32_t *)(pHostObj3 + 8);
        if ( pObjVec4 != 0 && nObjIdx < (*(uint32_t *)(pHostObj3 + 12) - pObjVec4) >> 2 )
          pListObj4 = *(uint32_t **)(pObjVec4 + 4 * nObjIdx);
        else
          pListObj4 = nullptr;
        if ( pListObj4[169] == 1 )
        {
          nObjOwner2 = (*(int (/*thiscall*/ **)(uint32_t *))(*pListObj4 + 376))(pListObj4);  // 结果 = 虚调用 vt+376
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2) == nObjOwner2  // 调虚槽 +376：坐标同步包（type 37）
            && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pListObj4 + 308))(pListObj4) != 0 )  // 虚调用 vt+308
          {
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pListObj4 + 312))(pListObj4, 0);  // 虚调用 vt+312
          }
LABEL_31:
          pSelf = this;
        }
      }
      ++nObjIdx;
    }
  }
}



// ------------------------------------------------------------
// 0x4DC630 sub_4DC630 —— 关卡/交互事件包处理（关联对象 this+7260 校验）
// 读包 word（vt+76）作 id，与关联对象 vt+52() 比对通过后读事件 word：
// 0xA → vt+1272；0xB → vt+1268 + sub_4DB200(23,-1) 后返 -1；0xC → 再读 2 word 坐标，
// sub_45EBE0 拾取并 RTTI 转换为 IRDCollisionObject 后 vt+1136 设置。未匹配返 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DC630(uint32_t *this)  // 实现：关卡/交互事件包处理（关联对象 this+7260 校验）
{
  int pSyncPeer; // eax
  int result; // eax
  int pPicked; // eax
  int pCollision; // eax
  int nEvtWord; // [esp+4h] [ebp-10h] BYREF
  uint16_t nPktX; // [esp+8h] [ebp-Ch] BYREF
  uint16_t nPktY; // [esp+Ch] [ebp-8h] BYREF
  uint16_t nPktId; // [esp+10h] [ebp-4h] BYREF

  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &nPktId);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
  pSyncPeer = *(this + 1815);  // pSyncPeer=this+7260 this
  if ( pSyncPeer != 0 && (*(int (**)(void))(*(uint32_t *)pSyncPeer + 52))() == nPktId )  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
  {
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &nEvtWord);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
    result = (uint16_t)nEvtWord;
    switch ( (uint16_t)nEvtWord )  // 按 (uint16_t)nEvtWord 分派
    {
      case 0xAu:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1272))(this, nEvtWord);  // 虚调用 vt+1272
        break;
      case 0xBu:
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1268))(this);  // 虚调用 vt+1268
        sub_4DB200(this, 23, 0xFFFFFFFF);  // 15% 概率随机文案触发（0x4DB130 的门包装）
        return -1;
      case 0xCu:
        (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &nPktX);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
        (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &nPktY);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
        pPicked = sub_45EBE0(nPktX, nPktY);  // 调 对象查找
        pCollision = __RTDynamicCast(pPicked, 0, &CNRDObject `RTTI Type Descriptor', &IRDCollisionObject `RTTI Type Descriptor', 0);  // pCollision = 调 __RTDynamicCast
        if ( pCollision != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1136))(this, pCollision);  // 虚调用 vt+1136
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
// 0x4DC730 sub_4DC730 —— 同队怪物聚合广播（包 type 29）
// this+1814（队长/召唤宿主对象）非空时遍历宿主（this+116）+120 对象列表：
// 条件 17、车主 == 自身车主、非自身、RTTI 转换 IRDMonster 成功、+7772 != 3、
// （PVP 场景或 vt+1244 门）、vt+304() 容器非空 → 打包 [怪 vt+48, 怪 vt+52,
// 容器对象 vt+52, 11, 宿主对象 vt+48, 宿主对象 vt+52] 发送；尾调 sub_4D83E0(0,0)。
// 【推断】召唤物/同队成员状态聚合上报。
// ------------------------------------------------------------
void /*thiscall*/ sub_4DC730(int *this)  // 实现：同队怪物聚合广播（包 type 29）
{
  unsigned int nObjIdx; // esi
  int pHostObj1; // ecx
  int pObjVec1; // edx
  int nVecCount; // eax
  int pObjVec2; // edx
  int pListObj1; // ecx
  int pHostObj2; // ecx
  int pObjVec3; // edx
  int pListObj2; // esi
  int nObjOwner; // ebx
  int pMonster; // eax
  int pMonster; // esi
  int pPktVt1; // ebx
  int nMonId; // eax
  int pPktVt2; // ebx
  int nMonKey; // eax
  int pCont304; // eax
  int pPktVt3; // esi
  int nContId; // eax
  int pPktVt4; // esi
  int pLinkObj1; // eax
  int pPktVt5; // esi
  int pLinkObj2; // eax
  unsigned int nObjIdxSave; // [esp+4h] [ebp-4h]

  if ( *(this + 1814) != 0 )  // 判定 “+7256 光环状态”
  {
    for ( nObjIdx = 0; ; ++nObjIdx )
    {
      pHostObj1 = *(this + 29);  // 读 pHostObj1 = this+116（观察者容器）
      pObjVec1 = *(uint32_t *)(pHostObj1 + 120);  // pHostObj1=this+116 观察者 vector 尾针
      nObjIdxSave = nObjIdx;
      nVecCount = pObjVec1 != 0 ? (*(uint32_t *)(pHostObj1 + 124) - pObjVec1) >> 2 : 0;  // pHostObj1=this+116 观察者 vector 尾针
      if ( (int)nObjIdx >= nVecCount )
        break;
      pObjVec2 = *(uint32_t *)(pHostObj1 + 120);  // pHostObj1=this+116 观察者 vector 尾针
      if ( pObjVec2 != 0 && nObjIdx < (*(uint32_t *)(pHostObj1 + 124) - pObjVec2) >> 2 )  // pHostObj1=this+116 观察者 vector 尾针
        pListObj1 = *(uint32_t *)(pObjVec2 + 4 * nObjIdx);
      else
        pListObj1 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj1 + 40))(pListObj1, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      {
        pHostObj2 = *(this + 29);  // 读 pHostObj2 = this+116（观察者容器）
        pObjVec3 = *(uint32_t *)(pHostObj2 + 120);  // pHostObj2=this+116 观察者 vector 尾针
        if ( pObjVec3 != 0 && nObjIdx < (*(uint32_t *)(pHostObj2 + 124) - pObjVec3) >> 2 )  // pHostObj2=this+116 观察者 vector 尾针
          pListObj2 = *(uint32_t *)(pObjVec3 + 4 * nObjIdx);
        else
          pListObj2 = 0;
        nObjOwner = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pListObj2 + 376))(pListObj2);  // 调虚槽 +376：坐标同步包（type 37）
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 376))(this) == nObjOwner && this != (int *)pListObj2 )  // 虚调用 vt+376
        {
          pMonster = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                  pListObj2,
                  0,
                  &IRDCollisionObject `RTTI Type Descriptor',
                  &IRDMonster `RTTI Type Descriptor',
                  0);
          pMonster = pMonster;
          if ( pMonster != 0
            && *(uint32_t *)(pMonster + 7772) != 3
            && (*(this + 1943) == 3 || (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 1244))(this, pMonster) != 0)  // 虚调用 vt+1244
            && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pMonster + 304))(pMonster) != 0 )  // 调虚槽 +304：是否本地玩家
          {
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
            pPktVt1 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
            nMonId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pMonster + 48))(pMonster);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
            (*(void (/*thiscall*/ **)(int, int))(pPktVt1 + 36))(dword_8F8520, nMonId);  // 会话/UDP 管理器
            pPktVt2 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
            nMonKey = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pMonster + 52))(pMonster);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
            (*(void (/*thiscall*/ **)(int, int))(pPktVt2 + 36))(dword_8F8520, nMonKey);  // 会话/UDP 管理器
            pCont304 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pMonster + 304))(pMonster);  // 调虚槽 +304：是否本地玩家
            pPktVt3 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
            nContId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pCont304 + 52))(pCont304);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
            (*(void (/*thiscall*/ **)(int, int))(pPktVt3 + 36))(dword_8F8520, nContId);  // 会话/UDP 管理器
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 11);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
            pPktVt4 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
            pLinkObj1 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1814) + 48))(*(this + 1814));  // this+7256〔pAuraObject〕
            (*(void (/*thiscall*/ **)(int, int))(pPktVt4 + 36))(dword_8F8520, pLinkObj1);  // 会话/UDP 管理器
            pPktVt5 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
            pLinkObj2 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1814) + 52))(*(this + 1814));  // this+7256〔pAuraObject〕
            (*(void (/*thiscall*/ **)(int, int))(pPktVt5 + 36))(dword_8F8520, pLinkObj2);  // 会话/UDP 管理器
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
          }
        }
        nObjIdx = nObjIdxSave;
      }
    }
    sub_4D83E0(this, 0, 0);  // 头顶气泡 ”Exclamation.ani”（惊叹；同 0x4D82D0 结构）
  }
}



// ------------------------------------------------------------
// 0x4DC920 sub_4DC920 —— 对象列表属性极值挑选（等级）
// 遍历宿主 +120 对象列表（条件 17、sub_4E4630 可见、sub_4E5CA0==0、vt+1244 门），
// 取 vt+672(obj,3) 属性块 +0（等级，同 0x4DAE50 的 Lv 显示）：*uArg2 = 最低等级
// 对象、*uArg3 = 最高等级对象。【推断】AI 目标挑选（最低/最高等级优先）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DC920(uint32_t *this, uint32_t *uArg2, uint32_t *uArg3)  // 实现：对象列表属性极值挑选（等级）
{
  unsigned int nObjIdx; // edi
  uint32_t *pSelf; // esi
  int nMaxVal; // ebx
  int pHostObj1; // ecx
  int pObjVec1; // edx
  int result; // eax
  int pObjVec2; // edx
  int pListObj1; // ecx
  int pHostObj2; // ecx
  int pObjVec3; // edx
  int pListObj2; // esi
  int nMinCmp; // edi
  int nMaxCmp; // edi
  int bFirst; // [esp+Ch] [ebp-10h]
  unsigned int nObjIdxSave; // [esp+14h] [ebp-8h]
  int nMinVal; // [esp+18h] [ebp-4h]

  nObjIdx = 0;
  pSelf = this;
  nMinVal = 0;
  nMaxVal = 0;
  bFirst = 1;
  while ( 1 )  // 无限循环
  {
    pHostObj1 = pSelf[29];
    pObjVec1 = *(uint32_t *)(pHostObj1 + 120);
    nObjIdxSave = nObjIdx;
    result = pObjVec1 != 0 ? (*(uint32_t *)(pHostObj1 + 124) - pObjVec1) >> 2 : 0;
    if ( (int)nObjIdx >= result )
      return result;
    pObjVec2 = *(uint32_t *)(pHostObj1 + 120);
    if ( pObjVec2 != 0 && nObjIdx < (*(uint32_t *)(pHostObj1 + 124) - pObjVec2) >> 2 )
      pListObj1 = *(uint32_t *)(pObjVec2 + 4 * nObjIdx);
    else
      pListObj1 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj1 + 40))(pListObj1, 17) == 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      goto LABEL_30;
    pHostObj2 = pSelf[29];
    pObjVec3 = *(uint32_t *)(pHostObj2 + 120);
    if ( pObjVec3 != 0 && nObjIdx < (*(uint32_t *)(pHostObj2 + 124) - pObjVec3) >> 2 )
      pListObj2 = *(uint32_t *)(pObjVec3 + 4 * nObjIdx);
    else
      pListObj2 = 0;
    if ( (uint8_t)sub_4E4630(pListObj2) == 0  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
      || (uint8_t)sub_4E5CA0(pListObj2) != 0  // 阵营号 200..204 判定（200 起逐个比较）
      || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pListObj2) == 0 )  // 虚调用 vt+1244
    {
      goto LABEL_30;
    }
    if ( bFirst == 1 )
    {
      nMinVal = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 672))(pListObj2, 3);  // 调虚槽 +672：自身 HP
      nMaxVal = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 672))(pListObj2, 3);  // 调虚槽 +672：自身 HP
      *uArg2 = pListObj2;
      *uArg3 = pListObj2;
      pSelf = this;
      bFirst = 0;
      ++nObjIdx;
    }
    else
    {
      nMinCmp = nMinVal;
      if ( nMinVal >= *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 672))(pListObj2, 3) )  // 调虚槽 +672：自身 HP
        nMinCmp = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 672))(pListObj2, 3);  // 调虚槽 +672：自身 HP
      if ( nMinCmp == *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 672))(pListObj2, 3) )  // 调虚槽 +672：自身 HP
      {
        *uArg2 = pListObj2;
        nMinVal = nMinCmp;
      }
      if ( nMaxVal <= *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 672))(pListObj2, 3) )  // 调虚槽 +672：自身 HP
        nMaxCmp = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 672))(pListObj2, 3);  // 调虚槽 +672：自身 HP
      else
        nMaxCmp = nMaxVal;
      if ( nMaxCmp == *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj2 + 672))(pListObj2, 3) )  // 调虚槽 +672：自身 HP
      {
        *uArg3 = pListObj2;
        nMaxVal = nMaxCmp;
      }
      nObjIdx = nObjIdxSave;
LABEL_30:
      pSelf = this;
      ++nObjIdx;
    }
  }
}



// ------------------------------------------------------------
// 0x4DCAB0 sub_4DCAB0 —— 对象列表 HP 极值挑选（0x4DC920 的 HP 版对偶）
// 同样的列表/门条件，取 vt+684(obj)（GetHP，0x4D6130 同源）经 sub_41A5E0 防篡读：
// *uArg2 = 最低 HP 对象、*uArg3 = 最高 HP 对象。【推断】AI 治疗目标/集火目标挑选。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DCAB0(uint32_t *this, uint32_t *uArg2, uint32_t *uArg3)  // 实现：对象列表 HP 极值挑选（0x4DC920 的 HP 版对偶）
{
  unsigned int nObjIdx; // ebx
  uint32_t *pSelf; // edi
  int pHostObj1; // ecx
  int pObjVec1; // edx
  int result; // eax
  int pObjVec2; // edx
  int pListObj1; // ecx
  int pHostObj2; // ecx
  int pObjVec3; // edx
  int pListObj2; // esi
  unsigned int nHpRet1; // eax
  unsigned int nHpRet2; // eax
  unsigned int nHpRet3; // eax
  int nMinHp; // edi
  unsigned int nHpRet4; // eax
  unsigned int nHpRet5; // eax
  unsigned int nHpRet6; // eax
  int nMaxHp; // edi
  unsigned int nHpRet7; // eax
  unsigned int nHpRet8; // eax
  int bFirst; // [esp+10h] [ebp-Ch]
  int nMaxHpSave; // [esp+14h] [ebp-8h]
  int nMinHpSave; // [esp+18h] [ebp-4h]

  nObjIdx = 0;
  pSelf = this;
  nMinHpSave = 0;
  nMaxHpSave = 0;
  bFirst = 1;
  while ( 1 )  // 无限循环
  {
    pHostObj1 = pSelf[29];
    pObjVec1 = *(uint32_t *)(pHostObj1 + 120);
    result = pObjVec1 != 0 ? (*(uint32_t *)(pHostObj1 + 124) - pObjVec1) >> 2 : 0;
    if ( (int)nObjIdx >= result )
      return result;
    pObjVec2 = *(uint32_t *)(pHostObj1 + 120);
    if ( pObjVec2 != 0 && nObjIdx < (*(uint32_t *)(pHostObj1 + 124) - pObjVec2) >> 2 )
      pListObj1 = *(uint32_t *)(pObjVec2 + 4 * nObjIdx);
    else
      pListObj1 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pListObj1 + 40))(pListObj1, 17) == 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      goto LABEL_29;
    pHostObj2 = pSelf[29];
    pObjVec3 = *(uint32_t *)(pHostObj2 + 120);
    if ( pObjVec3 != 0 && nObjIdx < (*(uint32_t *)(pHostObj2 + 124) - pObjVec3) >> 2 )
      pListObj2 = *(uint32_t *)(pObjVec3 + 4 * nObjIdx);
    else
      pListObj2 = 0;
    if ( (uint8_t)sub_4E4630(pListObj2) == 0  // 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
      || (uint8_t)sub_4E5CA0(pListObj2) != 0  // 阵营号 200..204 判定（200 起逐个比较）
      || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pSelf + 1244))(pSelf, pListObj2) == 0 )  // 虚调用 vt+1244
    {
      goto LABEL_29;
    }
    if ( bFirst == 1 )
    {
      nHpRet1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pListObj2 + 684))(pListObj2);  // 调虚槽 +684：取攻击上下文
      nMinHpSave = sub_41A5E0(nHpRet1);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      nHpRet2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pListObj2 + 684))(pListObj2);  // 调虚槽 +684：取攻击上下文
      nMaxHpSave = sub_41A5E0(nHpRet2);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      *uArg2 = pListObj2;
      *uArg3 = pListObj2;
      bFirst = 0;
      ++nObjIdx;
    }
    else
    {
      nHpRet3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pListObj2 + 684))(pListObj2);  // 调虚槽 +684：取攻击上下文
      nMinHp = nMinHpSave;
      if ( nMinHpSave >= sub_41A5E0(nHpRet3) )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        nHpRet4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pListObj2 + 684))(pListObj2);  // 调虚槽 +684：取攻击上下文
        nMinHp = sub_41A5E0(nHpRet4);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      }
      nHpRet5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pListObj2 + 684))(pListObj2);  // 调虚槽 +684：取攻击上下文
      if ( nMinHp == sub_41A5E0(nHpRet5) )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        *uArg2 = pListObj2;
        nMinHpSave = nMinHp;
      }
      nHpRet6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pListObj2 + 684))(pListObj2);  // 调虚槽 +684：取攻击上下文
      nMaxHp = nMaxHpSave;
      if ( nMaxHpSave <= sub_41A5E0(nHpRet6) )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        nHpRet7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pListObj2 + 684))(pListObj2);  // 调虚槽 +684：取攻击上下文
        nMaxHp = sub_41A5E0(nHpRet7);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      }
      nHpRet8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pListObj2 + 684))(pListObj2);  // 调虚槽 +684：取攻击上下文
      if ( nMaxHp == sub_41A5E0(nHpRet8) )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        *uArg3 = pListObj2;
        nMaxHpSave = nMaxHp;
      }
      pSelf = this;
LABEL_29:
      ++nObjIdx;
    }
  }
}



// ------------------------------------------------------------
// 0x4DCC60 sub_4DCC60 —— 状态施加强度门（0x4D6910 状态施加通用壳的包装）
// PVP 场景（this+7772 == 3）时施加强度 fArg3 ×0.1；本对象持有标签 196616
//（0x4DB0E0 头注 id 表：技能施加强度 PVP 修正门）时跳过施加，否则转发
// sub_4D6910(this, nArg2, fArg3, nArg4, nArg5, 0)。
// ------------------------------------------------------------
char /*thiscall*/ sub_4DCC60(uint32_t *this, int nArg2, float fArg3, int nArg4, int nArg5)  // 实现：状态施加强度门（0x4D6910 状态施加通用壳的包装）
{
  char result; // al
  void *pThisArg; // ecx —— 寄存器残影（this 传参）

  if ( *(this + 1943) == 3 )  // 判定 “+7772 反击态”
    fArg3 = fArg3 * 0.1;
  result = sub_4DB0E0(this, 196616);  // 技能/被动标签查询（是否持有某 id；id 从 261396 段到 196625）
  if ( result == 0 )
    return sub_4D6910(pThisArg, nArg2, fArg3, nArg4, nArg5, 0);  // 状态施加通用壳（a2=状态id, a3=强度, a4/a5=参数, a6=强制位）
  return result;
}



// ------------------------------------------------------------
// 0x4DCCB0 sub_4DCCB0 —— ★ AI 威胁值累加（仇恨打分）
// pArg2 = 威胁值累加指针（*pArg2 += …）、nArg3 = 事件源对象、fArg4 = 攻击信息
//（attackinfo：+0/+4/+8/+12/+16/+20 各槽对象指针）。加分项依次：
// ① 源 == this+1814（当前攻击者）+100；② 距离衰减（vt+8 距离 vs 视野：盲眼 10、
//    视野字段 this+7520 否则 640，×1.4 后 sub_4049C0 在 [100,0] 内插值）；
// ③ 朝向差（vt+152 朝向与目标 X 比较，sub_4049C0 [100,50] 内插 300 上限）；
// ④ sub_4BE520 方向表查询，命中 *(this+7608) 时加表项 +16；
// ⑤ this+1891/1892/1893 规则槽（1/2 档）与 attackinfo 各槽对象匹配各 +100；
// ⑥ this+1894/1895/1896 模式 1/2：取双方属性对（+60/+74、+88/+102、…）
//    差值经 sub_4049C0 在 [100,1]/[1,100] 内插累加。
// 【推断】结果供怪物 AI 挑选仇恨最高目标（与 0x4DC920/0x4DCAB0 极值挑选配套）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DCCB0(int *this, int pArg2, int nArg3, float fArg4)  // 实现：AI 威胁值累加（仇恨打分）
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
  *(uint32_t *)pArg2 += *(this + 1814) != nArg3 ? 0 : 0x64;  // this+7256〔pAuraObject〕
  *(float *)&v110 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, nArg32, 0));  // 虚调用 vt+8
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 776))(this, 5) != 0 )  // 虚调用 vt+776
  {
    pArg2 = 10;
  }
  else
  {
    pArg2 = *(this + 1880);  // 读 pArg2 = this+7520（攻击参数面）
    if ( *(float *)&pArg2 == 0.0 )  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
      pArg2 = 640;  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
  }
  *v6 += (uint64_t)sub_4049C0(100.0, 0.0, v110, (uint64_t)((double)pArg2 * 1.4));  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from
  v7 = *this;
  HIBYTE(pArg2) = 0;  // 调 取 16 位值高 8 位
  if ( (*(int (/*thiscall*/ **)(int *))(v7 + 152))(this) == 0 )  // 调虚槽 +152：效果通道 3
  {
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 调虚槽 +120：动画对象
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) <= v8;  // 结果 = 虚调用 vt+120
    pObj = nArg3;
    if ( !v9 )
      HIBYTE(pArg2) = 1;  // 调 取 16 位值高 8 位
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 1  // 虚调用 vt+152
    && (v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj),  // 调虚槽 +120：动画对象
        v9 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < v10,  // 结果 = 虚调用 vt+120
        pObj = nArg3,
        v9)
    || HIBYTE(pArg2) != 0 )  // 调 取 16 位值高 8 位
  {
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 160))(this, pObj);  // 结果 = 虚调用 vt+160
    *v6 += (uint64_t)sub_4049C0(100.0, 50.0, v11, 300);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from
  }
  pArg2 = pObj;  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
  sub_4BE520(&v110, &pArg2);  // 映射下界查找（lower_bound）
  if ( v110 == *(this + 1902) )
    v12 = 0;
  else
    v12 = *(uint32_t *)(v110 + 16);
  v13 = v12 + *v6;
  *v6 = v13;
  fArg42 = fArg4;
  if ( *(this + 1893) == 2 && pObj == *(uint32_t *)(LODWORD(fArg4) + 20) )  // 判定 “+7572 模式 2 档”
    *v6 = v13 + 100;
  if ( *(this + 1893) == 1 && pObj == *(uint32_t *)(LODWORD(fArg42) + 16) )  // 判定 “+7572 模式 2 档”
    *v6 += 100;
  if ( *(this + 1891) == 1 && pObj == *(uint32_t *)LODWORD(fArg42) )  // 判定 “+7564 形态/模式槽”
    *v6 += 100;
  if ( *(this + 1891) == 2 && pObj == *(uint32_t *)(LODWORD(fArg42) + 4) )  // 判定 “+7564 形态/模式槽”
    *v6 += 100;
  if ( *(this + 1892) == 1 && pObj == *(uint32_t *)(LODWORD(fArg42) + 8) )  // 判定 “+7568 激活/模式槽”
    *v6 += 100;
  if ( *(this + 1892) == 2 && pObj == *(uint32_t *)(LODWORD(fArg42) + 12) )  // 判定 “+7568 激活/模式槽”
    *v6 += 100;
  fld_e1894 = *(this + 1894);  // 读 fld_e1894 = this+7576（攻击参数面槽）
  if ( fld_e1894 == 1 )  // fld_e1894=this+7576 攻击参数面槽【推断】
  {
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 60));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(pArg2 + 74));  // crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    v101 = sub_41A5E0(pArg2 + 60);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v16 = COERCE_FLOAT(sub_41A5E0(pArg2 + 74));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v17 = *(uint32_t *)pObj;
    pArg2 = v16;  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
    v18 = (*(int (/*thiscall*/ **)(int, int))(v17 + 672))(pObj, 3);  // 调虚槽 +672：自身 HP
    v74 = sub_41A5E0(v18 + 60);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v64 = COERCE_FLOAT(sub_41A5E0(v18 + 74));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 结果 = 虚调用 vt+672
    v92 = sub_41A5E0(v19 + 60);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v83 = COERCE_FLOAT(sub_41A5E0(v19 + 74));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v20 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            100.0,
            1.0,
            (unsigned int)(uint64_t)((double)v74 * v64) - (int)(uint64_t)((double)v92 * v83) / 2,
            2 * (unsigned int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&v110)  // 调 取 64 位值低 32 位(带符号)
          - (int)(uint64_t)((double)v101 * *(float *)&pArg2) / 2);  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
  }
  else
  {
    if ( fld_e1894 != 2 )  // fld_e1894=this+7576 攻击参数面槽【推断】
      goto LABEL_38;
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    v65 = sub_41A5E0(pArg2 + 60);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v75 = COERCE_FLOAT(sub_41A5E0(pArg2 + 74));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 60));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v21 = COERCE_FLOAT(sub_41A5E0(pArg2 + 74));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v22 = *(uint32_t *)pObj;
    pArg2 = v21;  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
    v23 = (*(int (/*thiscall*/ **)(int, int))(v22 + 672))(pObj, 3);  // 调虚槽 +672：自身 HP
    v102 = sub_41A5E0(v23 + 60);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v23 + 74));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v24 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 结果 = 虚调用 vt+672
    v84 = sub_41A5E0(v24 + 60);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v93 = COERCE_FLOAT(sub_41A5E0(v24 + 74));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v20 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            1.0,
            100.0,
            (unsigned int)(uint64_t)((double)v102 * *(float *)&v110)  // ★ AI 威胁值累加（仇恨打分）
          - (int)(uint64_t)((double)v84 * v93) / 2,
            2 * (unsigned int)(uint64_t)((double)v65 * v75)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);  // 调 取 64 位值低 32 位(带符号)
  }
  pObj = nArg3;
  *v6 += (uint64_t)v20;
LABEL_38:
  fld_e1895 = *(this + 1895);  // 读 fld_e1895 = this+7580（攻击面门字节）
  if ( fld_e1895 == 1 )  // fld_e1895=this+7580 攻击面门字节
  {
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    v66 = sub_41A5E0(pArg2 + 88);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v76 = COERCE_FLOAT(sub_41A5E0(pArg2 + 102));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 88));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v26 = COERCE_FLOAT(sub_41A5E0(pArg2 + 102));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v27 = *(uint32_t *)pObj;
    pArg2 = v26;  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
    v28 = (*(int (/*thiscall*/ **)(int, int))(v27 + 672))(pObj, 3);  // 调虚槽 +672：自身 HP
    v103 = sub_41A5E0(v28 + 88);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v28 + 102));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v29 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 结果 = 虚调用 vt+672
    v85 = sub_41A5E0(v29 + 88);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v94 = COERCE_FLOAT(sub_41A5E0(v29 + 102));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v30 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            100.0,
            1.0,
            (unsigned int)(uint64_t)((double)v103 * *(float *)&v110)
          - (int)(uint64_t)((double)v85 * v94) / 2,
            2 * (unsigned int)(uint64_t)((double)v66 * v76)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);  // 调 取 64 位值低 32 位(带符号)
  }
  else
  {
    if ( fld_e1895 != 2 )  // fld_e1895=this+7580 攻击面门字节
      goto LABEL_43;
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    v67 = sub_41A5E0(pArg2 + 88);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v77 = COERCE_FLOAT(sub_41A5E0(pArg2 + 102));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 88));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v31 = COERCE_FLOAT(sub_41A5E0(pArg2 + 102));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v32 = *(uint32_t *)pObj;
    pArg2 = v31;  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
    v33 = (*(int (/*thiscall*/ **)(int, int))(v32 + 672))(pObj, 3);  // 调虚槽 +672：自身 HP
    v104 = sub_41A5E0(v33 + 88);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v33 + 102));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v34 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 结果 = 虚调用 vt+672
    v86 = sub_41A5E0(v34 + 88);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v95 = COERCE_FLOAT(sub_41A5E0(v34 + 102));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v30 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            1.0,
            100.0,
            (unsigned int)(uint64_t)((double)v104 * *(float *)&v110)
          - (int)(uint64_t)((double)v86 * v95) / 2,
            2 * (unsigned int)(uint64_t)((double)v67 * v77)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);  // 调 取 64 位值低 32 位(带符号)
  }
  pObj = nArg3;
  *v6 += (uint64_t)v30;
LABEL_43:
  fld_e1896 = *(this + 1896);  // 读 fld_e1896 = this+7584（形态槽）
  if ( fld_e1896 == 1 )  // fld_e1896=this+7584 形态槽（0x5B7CD0 清面后置 1）【推断】
  {
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    v68 = sub_41A5E0(pArg2 + 116);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v78 = COERCE_FLOAT(sub_41A5E0(pArg2 + 130));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 116));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v36 = COERCE_FLOAT(sub_41A5E0(pArg2 + 130));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v37 = *(uint32_t *)pObj;
    pArg2 = v36;  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
    v38 = (*(int (/*thiscall*/ **)(int, int))(v37 + 672))(pObj, 3);  // 调虚槽 +672：自身 HP
    v105 = sub_41A5E0(v38 + 116);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v38 + 130));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v39 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 结果 = 虚调用 vt+672
    v87 = sub_41A5E0(v39 + 116);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v96 = COERCE_FLOAT(sub_41A5E0(v39 + 130));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v40 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            100.0,
            1.0,
            (unsigned int)(uint64_t)((double)v105 * *(float *)&v110)
          - (int)(uint64_t)((double)v87 * v96) / 2,
            2 * (unsigned int)(uint64_t)((double)v68 * v78)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);  // 调 取 64 位值低 32 位(带符号)
  }
  else
  {
    if ( fld_e1896 != 2 )  // fld_e1896=this+7584 形态槽（0x5B7CD0 清面后置 1）【推断】
      goto LABEL_48;
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    v69 = sub_41A5E0(pArg2 + 116);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v79 = COERCE_FLOAT(sub_41A5E0(pArg2 + 130));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 116));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v41 = COERCE_FLOAT(sub_41A5E0(pArg2 + 130));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v42 = *(uint32_t *)pObj;
    pArg2 = v41;  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
    v43 = (*(int (/*thiscall*/ **)(int, int))(v42 + 672))(pObj, 3);  // 调虚槽 +672：自身 HP
    v106 = sub_41A5E0(v43 + 116);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v43 + 130));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v44 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 结果 = 虚调用 vt+672
    v88 = sub_41A5E0(v44 + 116);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v97 = COERCE_FLOAT(sub_41A5E0(v44 + 130));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v40 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            1.0,
            100.0,
            (unsigned int)(uint64_t)((double)v106 * *(float *)&v110)
          - (int)(uint64_t)((double)v88 * v97) / 2,
            2 * (unsigned int)(uint64_t)((double)v69 * v79)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);  // 调 取 64 位值低 32 位(带符号)
  }
  pObj = nArg3;
  *v6 += (uint64_t)v40;
LABEL_48:
  fld_e1897 = *(this + 1897);  // 读 fld_e1897 = this+7588（形态槽）
  if ( fld_e1897 == 1 )  // fld_e1897=this+7588 形态槽（0x5B7D60/0x5B3420 置 …
  {
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    v70 = sub_41A5E0(pArg2 + 144);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v80 = COERCE_FLOAT(sub_41A5E0(pArg2 + 158));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 144));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v46 = COERCE_FLOAT(sub_41A5E0(pArg2 + 158));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v47 = *(uint32_t *)pObj;
    pArg2 = v46;  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
    v48 = (*(int (/*thiscall*/ **)(int, int))(v47 + 672))(pObj, 3);  // 调虚槽 +672：自身 HP
    v107 = sub_41A5E0(v48 + 144);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v48 + 158));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v49 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 结果 = 虚调用 vt+672
    v89 = sub_41A5E0(v49 + 144);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v98 = COERCE_FLOAT(sub_41A5E0(v49 + 158));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v50 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            100.0,
            1.0,
            (unsigned int)(uint64_t)((double)v107 * *(float *)&v110)
          - (int)(uint64_t)((double)v89 * v98) / 2,
            2 * (unsigned int)(uint64_t)((double)v70 * v80)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);  // 调 取 64 位值低 32 位(带符号)
  }
  else
  {
    if ( fld_e1897 != 2 )  // fld_e1897=this+7588 形态槽（0x5B7D60/0x5B3420 置 …
      goto LABEL_53;
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    v71 = sub_41A5E0(pArg2 + 144);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v81 = COERCE_FLOAT(sub_41A5E0(pArg2 + 158));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 144));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v51 = COERCE_FLOAT(sub_41A5E0(pArg2 + 158));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v52 = *(uint32_t *)pObj;
    pArg2 = v51;  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
    v53 = (*(int (/*thiscall*/ **)(int, int))(v52 + 672))(pObj, 3);  // 调虚槽 +672：自身 HP
    v108 = sub_41A5E0(v53 + 144);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v53 + 158));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v54 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 结果 = 虚调用 vt+672
    v90 = sub_41A5E0(v54 + 144);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v99 = COERCE_FLOAT(sub_41A5E0(v54 + 158));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v50 = sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
            1.0,
            100.0,
            (unsigned int)(uint64_t)((double)v108 * *(float *)&v110)
          - (int)(uint64_t)((double)v90 * v99) / 2,
            2 * (unsigned int)(uint64_t)((double)v71 * v81)
          - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);  // 调 取 64 位值低 32 位(带符号)
  }
  pObj = nArg3;
  *v6 += (uint64_t)v50;
LABEL_53:
  if ( *((uint8_t *)this + 7534) != 0 )  // this+7534〔bCfgBlock14(推断)〕
  {
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    v72 = sub_41A5E0(pArg2 + 816);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v82 = COERCE_FLOAT(sub_41A5E0(pArg2 + 830));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&pArg2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3));  // 虚调用 vt+672
    fArg4 = COERCE_FLOAT(sub_41A5E0(pArg2 + 816));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v55 = COERCE_FLOAT(sub_41A5E0(pArg2 + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v56 = *(uint32_t *)pObj;
    pArg2 = v55;  // pArg2=this+7520 内嵌配置块首 DWORD / 视野值
    v57 = (*(int (/*thiscall*/ **)(int, int))(v56 + 672))(pObj, 3);  // 调虚槽 +672：自身 HP
    v109 = sub_41A5E0(v57 + 816);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(float *)&v110 = COERCE_FLOAT(sub_41A5E0(v57 + 830));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v58 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 结果 = 虚调用 vt+672
    v91 = sub_41A5E0(v58 + 816);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v100 = COERCE_FLOAT(sub_41A5E0(v58 + 830));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    v59 = (uint64_t)sub_4049C0(  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
                              100.0,
                              1.0,
                              (unsigned int)(uint64_t)((double)v109 * *(float *)&v110)
                            - (int)(uint64_t)((double)v91 * v100) / 2,
                              2 * (unsigned int)(uint64_t)((double)v72 * v82)
                            - (int)(uint64_t)((double)SLODWORD(fArg4) * *(float *)&pArg2) / 2);  // 调 取 64 位值低 32 位(带符号)
    pObj = nArg3;
    *v6 += v59;
  }
  if ( *((uint8_t *)this + 7558) != 0 )  // this+7558〔bAtk7558(推断)〕
  {
    v60 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj);  // 调虚槽 +840：大状态 getter（this+6556）
    *v6 += (uint64_t)sub_4049C0(100.0, 1.0, v60 != 4 ? 100 : -100, 100);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from
  }
  nArg3 = 0;
  pArg2 = (int)this + 7535;  // this+7535 内嵌配置块 +15 字节
  do
  {
    if ( *(uint8_t *)pArg2 != 0 )  // pArg2=this+7535 内嵌配置块 +15 字节
    {
      fArg4 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3));  // 调虚槽 +672：自身 HP
      v73 = sub_41A5E0(nArg3 + LODWORD(fArg4) + 172);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      fArg4 = COERCE_FLOAT(sub_41A5E0(nArg3 + LODWORD(fArg4) + 228));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v61 = (uint64_t)((double)v73 * fArg4);
      if ( (int)v61 >= -100 )
      {
        if ( (int)v61 > 100 )
          LODWORD(v61) = 100;  // 调 取 64 位值低 32 位
      }
      else
      {
        LODWORD(v61) = -100;  // 调 取 64 位值低 32 位
      }
      *v6 += (uint64_t)sub_4049C0(100.0, 1.0, v61, 100);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from
    }
    ++pArg2;  // pArg2=this+7535 内嵌配置块 +15 字节
    nArg3 += 14;
  }
  while ( nArg3 < 56 );
  result = 0;
  nArg3 = 0;
  do
  {
    if ( *((uint8_t *)this + result + 7539) != 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 776))(pObj, result) != 0 )  // 调虚槽 +776：异常状态查询
        *v6 += 100;
      result = nArg3;
    }
    nArg3 = ++result;
  }
  while ( result < 17 );
  if ( *((uint8_t *)this + 7557) == 1 )  // this+7557〔bAtk7557(推断)〕
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);  // 调虚槽 +700：读 +6296 槽
    result = sub_53FD00(pObj);
    if ( (uint8_t)result == 1 )
      *v6 += 100;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4DD8F0 sub_4DD8F0 —— 属性块整体重算（全量成长）
// sub_4A1210 重置后对属性块批量写入：基础属性对 +4/+32/+60/+88/+116/+144
//（28 字节步距）与攻击/防御四项 +1012/+1040/+1068/+1096，再按等级经 sub_4049C0
// 在区间内插值成长（+172 起条目族，sub_41A590 防篡读写器）。
// 与 0x4DC220（增量修改器表）互为全量/增量两路。【推断】召唤/升级时属性重建。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DD8F0(uint32_t *this, int nArg2, int nArg3)  // 实现：属性块整体重算（全量成长）
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

  v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0);  // 结果 = 虚调用 vt+672
  sub_4A1210(v4);  // 调 重置后对属性块批量写入：基础属性对 +4/+32/+60/+88/+116/+14
  v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84C4 + 4))(dword_8F84C4, nArg3);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) = nArg2;  // 虚调用 vt+672
  *(this + 1820) = v5[47];
  *(this + 1821) = v5[48];
  v6 = v5[47];
  v7 = v5[48] - v6;
  v8 = nArg2 - v6;
  v9 = v5[36];
  v103 = v7;
  v73 = v9;
  if ( byte_77F280 == 0 && v9 == 2 )  // 若 byte_77F280 == 0 与/或 v9 == 2
  {
    nArg2 = **(uint32_t **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 108);  // 全局 dword_8F7A24 = 登录/选区管理器
    off_77F3FC((char *)&byte_6F9028, nArg2);  // 引擎日志输出函数(printf 风格)
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
        off_77F3FC((char *)&byte_6F8FE0, 2, v10, v13);  // 引擎日志输出函数(printf 风格)
      }
      break;
    }
    ++v10;
  }
  v82 = v81[1];
  v14 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v14 + 4, SHIDWORD(v14), v82);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v83 = v81[2];
  v15 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v15 + 32, SHIDWORD(v15), v83);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v84 = v81[3];
  v16 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v16 + 60, SHIDWORD(v16), v84);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v85 = v81[4];
  v17 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v17 + 88, SHIDWORD(v17), v85);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v86 = v81[5];
  v18 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v18 + 116, SHIDWORD(v18), v86);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v87 = v81[6];
  v19 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v19 + 144, SHIDWORD(v19), v87);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v88 = v81[7];
  v20 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v20 + 1012, SHIDWORD(v20), v88);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v89 = v81[8];
  v21 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v21 + 1040, SHIDWORD(v21), v89);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v90 = v81[9];
  v22 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v22 + 1068, SHIDWORD(v22), v90);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v91 = v81[10];
  v23 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v23 + 1096, SHIDWORD(v23), v91);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v24 = v5 + 49;
  v78 = 0;
  for ( j = v5 + 49; ; v24 = j )
  {
    v60 = (float)v24[1];
    v47 = (float)*v24;
    v74 = (uint64_t)sub_4049C0(v47, v60, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v25 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0);  // 结果 = 虚调用 vt+672
    sub_41A590(v25 + v78 + 172, v74, v74);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
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
    v27 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0);  // 结果 = 虚调用 vt+672
    sub_41A590(v27 + v79 + 284, v75, v75);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    k += 2;
    v79 += 14;
    if ( v79 >= 224 )
      break;
  }
  v62 = (float)(int)v5[94];
  v49 = (float)(int)v5[93];
  v28 = (uint64_t)sub_4049C0(v49, v62, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v94 = v28;
  v29 = ((int64_t (/*fastcall*/ *)(uint32_t *, uint32_t, uint32_t))*(uint32_t *)(*this + 672))(this, HIDWORD(v28), 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v29 + 816, SHIDWORD(v29), v94);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v63 = (float)(int)v5[96];
  v50 = (float)(int)v5[95];
  v95 = (uint64_t)sub_4049C0(v50, v63, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v30 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v30 + 844, SHIDWORD(v30), v95);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v64 = (float)(int)v5[98];
  v51 = (float)(int)v5[97];
  v96 = (uint64_t)sub_4049C0(v51, v64, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v31 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v31 + 872, SHIDWORD(v31), v96);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v65 = (float)(int)v5[100];
  v52 = (float)(int)v5[99];
  v97 = (uint64_t)sub_4049C0(v52, v65, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v32 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v32 + 900, SHIDWORD(v32), v97);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v66 = (float)(int)v5[102];
  v53 = (float)(int)v5[101];
  v98 = (uint64_t)sub_4049C0(v53, v66, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v33 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v33 + 928, SHIDWORD(v33), v98);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v67 = (float)(int)v5[104];
  v54 = (float)(int)v5[103];
  v99 = (uint64_t)sub_4049C0(v54, v67, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v34 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v34 + 956, SHIDWORD(v34), v99);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v68 = (float)(int)v5[106];
  v55 = (float)(int)v5[105];
  v100 = (uint64_t)sub_4049C0(v55, v68, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v35 = ((int64_t (/*thiscall*/ *)(uint32_t *, uint32_t))*(uint32_t *)(*this + 672))(this, 0);  // 调虚槽 +672：自身 HP
  sub_41A590(v35 + 984, SHIDWORD(v35), v100);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v69 = (float)(int)v5[108];
  v56 = (float)(int)v5[107];
  *(this + 1878) = (uint64_t)sub_4049C0(v56, v69, v8, v103);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from
  v70 = (float)(int)v5[110];
  v57 = (float)(int)v5[109];
  *(this + 1879) = (uint64_t)sub_4049C0(v57, v70, v8, v103);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from
  v71 = (float)(int)v5[90];
  v58 = (float)(int)v5[89];
  v80 = (uint64_t)sub_4049C0(v58, v71, v8, v103);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v72 = (float)(int)v5[92];
  v59 = (float)(int)v5[91];
  v76 = (double)(int)(uint64_t)sub_4049C0(v59, v72, v8, v103) * 0.001;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v36 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0);  // 结果 = 虚调用 vt+672
  v101 = sub_41A5E0(v36 + 4);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v104 = COERCE_FLOAT(sub_41A5E0(v36 + 18));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v37 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 760;  // 结果 = 虚调用 vt+672
  v38 = (uint64_t)((double)(int)(uint64_t)((double)v101 * v104) * ((double)v80 * 0.001));
  sub_41A590(v37, SHIDWORD(v38), v38);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v39 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0);  // 结果 = 虚调用 vt+672
  v102 = sub_41A5E0(v39 + 32);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v105 = COERCE_FLOAT(sub_41A5E0(v39 + 46));  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v40 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 788;  // 结果 = 虚调用 vt+672
  v41 = (uint64_t)((double)(int)(uint64_t)((double)v102 * v105) * v76);
  sub_41A590(v40, SHIDWORD(v41), v41);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_4DC220(this);  // 属性修改器表批量应用（buff/加成侧）【推断】
  sub_4D98A0(this);  // 调 pArg1 无车主或车主不在场 → 只做 +466/+4/HP/技能/其余同样的修正（另一分支同表）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 虚调用 vt+676
  v42 = *this;
  v43 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 740))(this, 0, 1);  // 结果 = 虚调用 vt+740
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v42 + 732))(this, v43);  // 调虚槽 +732：CNMapObject__vmt2DC
  v44 = *this;
  v45 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 756))(this, 1);  // 结果 = 虚调用 vt+756
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(v44 + 748))(this, v45);  // 调虚槽 +748：[RTTI: IRDActiveObject__vmt2EC · 槽位 IRDActiveObj…
}


// ------------------------------------------------------------
// 0x4DE0E0 sub_4DE0E0 —— 标签 vector 移除（this+1952 dword 表）
// 线性查找 nArg2 命中后 memmove 后续元素前移、end −4（0x4DB0E0 查询的配对写入侧）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4DE0E0(uint32_t *this, int nArg2)  // 实现：标签 vector 移除（this+1952 dword 表）
{
  int pTagVec; // edx —— this+1952 标签 vector begin
  unsigned int nTagIdx; // ecx
  unsigned int result; // eax
  int pTagVec2; // eax
  int nTagId; // ebx —— 当前标签 id

  pTagVec = *(this + 1952);  // this+7808〔风格/分支选择〕
  for ( nTagIdx = 0; pTagVec != 0; ++nTagIdx )  // pTagVec=this+7808 风格/分支选择
  {
    result = (*(this + 1953) - pTagVec) >> 2;  // this+7812〔nSubStateA(推断)〕
    if ( nTagIdx >= result )  // result=this+7812 nSubStateA
      break;
    pTagVec2 = *(this + 1952);  // this+7808〔风格/分支选择〕
    nTagId = *(uint32_t *)(pTagVec2 + 4 * nTagIdx);  // pTagVec2=this+7808 风格/分支选择
    result = pTagVec2 + 4 * nTagIdx;  // result=this+7812 nSubStateA
    if ( nTagId == nArg2 )
    {
      memcpy_0(
        (void *)(*(this + 1952) + 4 * i),  // this+7808〔风格/分支选择〕
        (const void *)(*(this + 1952) + 4 * i + 4),  // 虚调用 vt+4
        4 * ((int)(*(this + 1953) - (*(this + 1952) + 4 * i + 4)) >> 2));  // 虚调用 vt+4
      result = *(this + 1953) - 4;  // this+7812〔nSubStateA(推断)〕
      *(this + 1953) = result;  // this+7812〔nSubStateA(推断)〕
      return result;  // result=this+7812 nSubStateA
    }
  }
  return result;  // result=this+7812 nSubStateA
}



// ------------------------------------------------------------
// 0x4DE160 sub_4DE160 —— 目标选中标记绘制（本地玩家相关对象）
// nArg2==0 且车主与本地玩家车主一致时：this+8360 为空且动作 id != 60001 →
// sub_424760 画选中标记（nArg3-63, nArg4-21）；this+8360 非空按车主/关联对象
// 匹配再画（sub_418DD0 取光标资源 0/1/100）。【推断】鼠标点选光标/标记渲染。
// ------------------------------------------------------------
char /*thiscall*/ sub_4DE160(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：目标选中标记绘制（本地玩家相关对象）
{
  int nSelfOwner; // ebx
  int nImg100; // eax
  int nSelfOwner2; // ebx
  int nRet; // eax
  int nImg0; // eax
  int nCursor0; // [esp-1Ch] [ebp-28h]
  int nCursor1; // [esp-1Ch] [ebp-28h]

  if ( (uint8_t)nArg2 != 0 )
    goto LABEL_13;
  if ( dword_8F7C04 == 0 )  // 全局 dword_8F7C04 = 本机角色对象
    goto LABEL_7;
  nSelfOwner = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this);  // 结果 = 虚调用 vt+376
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) != nSelfOwner )  // 全局 dword_8F7C04 = 本机角色对象
    goto LABEL_7;
  if ( *(this + 2090) == 0 )  // 判定 “+8360 拾取信息 7 字节对象指针”
  {
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) != 60001 )  // 虚调用 vt+340
    {
      sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      nImg100 = sub_418DD0(100);  // 调 资源句柄 (101)
      sub_424760(dword_79C0B0, nArg3 - 63, nArg4 - 21, nImg100, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
    }
LABEL_7:
    if ( *(this + 2090) == 0 )  // 判定 “+8360 拾取信息 7 字节对象指针”
      goto LABEL_13;
  }
  sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
  nSelfOwner2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this);  // 结果 = 虚调用 vt+376
  if ( nSelfOwner2 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) )  // 全局 dword_8F7C04 = 本机角色对象
  {
    if ( dword_8F7C04 == *(this + 1815) )  // 全局 dword_8F7C04 = 本机角色对象
    {
      nCursor1 = sub_418DD0(1);  // 调 资源句柄 (101)
      sub_424760(dword_79C0B0, nArg3 - 35, nArg4 - 12, nCursor1, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
    }
  }
  else
  {
    nCursor0 = sub_418DD0(0);  // 调 资源句柄 (101)
    sub_424760(dword_79C0B0, nArg3 - 35, nArg4 - 12, nCursor0, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
  }
  sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
LABEL_13:
  LOBYTE(nRet) = sub_58E750(nArg2, nArg3, nArg4, nArg5);  // 【IRDActiveObject__vmt148】
  if ( (uint8_t)nArg2 != 0 )
  {
    LOBYTE(nRet) = *((uint8_t *)this + 8524);  // this+8524〔bMonCfgFlag〕
    if ( (uint8_t)nRet != 0 )
    {
      nRet = *(this + 2090);  // 读 nRet = this+8360（拾取信息 7 字节对象指针）
      if ( nRet == 0 )  // nRet=this+8360 pPickInfo8360
      {
        nRet = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 436))(this);  // 结果 = 虚调用 vt+436
        if ( nRet > 0 )  // nRet=this+8360 pPickInfo8360
        {
          sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
          nImg0 = sub_418DD0(0);  // 调 资源句柄 (101)
          sub_424760(dword_79C0B0, nArg3 - 33, nArg4 - 10, nImg0, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
          LOBYTE(nRet) = sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
        }
      }
    }
  }
  return nRet;  // nRet=this+8360 pPickInfo8360
}



// ------------------------------------------------------------
// 0x4DE360 sub_4DE360 —— 32 字节/条容器区间搬移（vector erase/insert 族内核）
// 把 [pszArg3, pszArg4) 的 32 字节条目块前移到 uArg2 处（qmemcpy 逐条），
// 更新 this+8 端点并经 uArg2 返回新起点。0x4DEFF0 的删除路径内核。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4DE360(char **this, uint32_t *uArg2, char *pszArg3, char *pszArg4)  // 32 字节/条容器区间搬移（vector erase/insert 族内核）
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
    fld_e2 = *(this + 2);  // 读 fld_e2 = this+8（技能槽记录首字）
    pszArg33 = pszArg3;
    if ( pszArg4 != fld_e2 )  // fld_e2=this+8 物品 id
    {
      do
      {
        pszArg422 = pszArg42;
        pszArg332 = pszArg33;
        pszArg42 += 32;
        pszArg33 += 32;
        qmemcpy(pszArg332, pszArg422, 0x20u);  // 调 内存块拷贝(内联展开)
      }
      while ( pszArg42 != fld_e2 );  // fld_e2=this+8 物品 id
      pszArg32 = pszArg3;
    }
    *(this + 2) = pszArg33;  // 写 this+8 = pszArg33（技能槽记录首字）
  }
  *uArg2 = pszArg32;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4DE3B0 sub_4DE3B0 ——（短函数，转写体未含可辨字符串证据；语义待定【待验证】）
char */*stdcall*/ sub_4DE3B0(char *pszArg1, char *pszArg2, const void *pArg3)  // 短函数，转写体未含可辨字符串证据；语义待定【待验证】
{
  sub_4DAB30(pszArg1, pszArg2, pArg3);  // 定长块批量填充（cdecl）
  return &pszArg1[32 * (uint32_t)pszArg2];
}



// ------------------------------------------------------------
// 0x4DE3E0 sub_4DE3E0 ——（短函数，转写体未含可辨字符串证据；语义待定【待验证】）
void /*thiscall*/ sub_4DE3E0(int *this)  // 实现：（短函数，转写体未含可辨字符串证据；语义待定(待验证)）
{
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 && rand() % 100 < 50 )  // 虚调用 vt+308
    sub_4DC730(this);  // 同队怪物聚合广播（包 type 29）
}



// ------------------------------------------------------------
// 0x4DE410 sub_4DE410 —— 名称模板写入 + 随机倒计时
// new 0x84 → sub_5FE2C0(100.0f) 构造参数对象；取本地化模板 873（sub_422E70）
// sprintf 本对象名字（this+292 SSO）写入动作对象（vt+340()）+4 字符串；
// 尾段经 sub_698F90 给 this+8556 时钟设随机倒计时、sub_4DE5E0 收尾。
// 【推断】命名怪/称号类对象的名称装配与出现计时。
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4DE410(uint32_t *this)  // 名称模板写入 + 随机倒计时
{
  int uMonFlagBits; // edx  | +0x0288 → 怪物位标志字（0x5908E0 掩码清 bit0 = APPEAR 已播标志）（IRDMonster·基类；va=004DE700）
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

  uMonFlagBits = *(this + 162);  // this+648〔uMonFlagBits〕
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v3 = *this;
  *(this + 1943) = 3;  // 写 this+7772 = 3（反击态）
  *(this + 162) = uMonFlagBits | 2;  // this+648〔uMonFlagBits〕
  *((uint8_t *)this + 6668) = 1;
  v4 = (*(int (**)(void))(v3 + 740))();  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 4;  // 结果 = 虚调用 vt+672
  v6 = (uint64_t)((double)sub_41A5E0(v5) * 2.5);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(v5, SHIDWORD(v6), v6);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 虚调用 vt+676
  v7 = *this;
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 740))(this, 0, 1);  // 结果 = 虚调用 vt+740
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v7 + 732))(this, v8);  // 调虚槽 +732：CNMapObject__vmt2DC
  v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this);  // 结果 = 虚调用 vt+740
  off_77F3FC(aApplyboss, v4, v9);  // 引擎日志输出函数(printf 风格)
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 466;  // 结果 = 虚调用 vt+672
  v11 = sub_41A5E0(v10);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(v10, v12, v11 + 50);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 虚调用 vt+676
  *(this + 1822) = -1;
  v22 = 0;
  if ( operator new(0x84u) != nullptr )  // 堆分配 132 字节对象
    v13 = (int *)sub_5FE2C0(1120403456);  // 常量 100.0f
  else
    v13 = nullptr;
  v14 = *v13;
  v22 = -1;
  (*(void (/*thiscall*/ **)(int *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v14 + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
    v13,
    this,
    this,
    0,
    0,
    0,
    -1);
  if ( *(this + 78) < 0x10u )  // this+78 【推断】公会标志字节 C
    pThis_49 = (char *)(this + 73);  // this+73〔szDigitalName(推断)〕等 2 字段
  else
    pThis_49 = (char *)*(this + 73);  // this+292〔nOpenMode292(推断)〕
  pThis_492 = pThis_49;  // pThis_49=this+292 nOpenMode292
  v16 = (const char *)sub_422E70(873);  // 调 存 CStringManager::getStr 取本地化串
  sprintf(Buffer, v16, pThis_492);  // 调 格式化到缓冲
  v17 = (size_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 4);  // 结果 = 虚调用 vt+340
  return sub_4015C0(v17, Buffer, strlen(Buffer));  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x4DE5E0 sub_4DE5E0 —— 文案条目装载 + 随机倒计时（0x4DE410 的配套件）
// sub_4014D0 把 a2 文案挂 this+8528，a9/a10 记 this+8584/8588（随机区间），
// 清 +8569/+8570 标志后 sub_698F90 给 this+8556 时钟设 [a9, a10) 随机倒计时；
// a8 >= 0x10 时 free 文案块（SSO 堆释放约定）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4DE5E0(  // 文案条目装载 + 随机倒计时（0x4DE410 的配套件）
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
  int nRangeEnd; // edx —— 随机区间上限（a10）
  int nRangeStart; // ebx —— 随机区间下限（a9）
  unsigned int nRand; // eax

  sub_4014D0((size_t *)(this + 8528), &a2, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
  nRangeEnd = a10;
  *(uint32_t *)(this + 8584) = a9;  // this+8584〔bPhaseDone(推断)〕
  *(uint32_t *)(this + 8588) = nRangeEnd;  // this+8588〔f_218C〕
  *(uint8_t *)(this + 8569) = 0;  // this+8569〔f_2179〕
  *(uint8_t *)(this + 8570) = 0;  // this+8570〔f_217A〕
  nRangeStart = *(uint32_t *)(this + 8584);  // this+8584〔bPhaseDone(推断)〕
  nRand = rand();  // nRand = 调 rand
  sub_698F90(this + 8556, nRangeStart + nRand % (*(uint32_t *)(this + 8588) - nRangeStart), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( a8 >= 0x10 )
    j__free(Block);  // 调 堆释放
}



// ------------------------------------------------------------
// 0x4DE680 sub_4DE680 —— noreturn 异常抛出（"vector<T> too long"）
// 构造 std::string 消息后经异常机制抛出 —— MSVC vector 越界保护，非业务逻辑。
// ------------------------------------------------------------
void /*noreturn*/ sub_4DE680()  // noreturn 异常抛出（”vector<T> too long”）
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
  sub_401740(pExceptionObject, &v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_err
  pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4DE6F0 sub_4DE6F0 —— 成员字符串析构（this+28 的 std::string 调 sub_4017E0；0x4DF060 构造的配对件）
void /*thiscall*/ sub_4DE6F0(void *this)  // 实现：成员字符串析构（this+28 的 std::string 调 sub_4017E0；0x4DF060 构造的配对件）
{
  sub_4017E0((int)this + 28);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
}



// ------------------------------------------------------------
// 0x4DE700 sub_4DE700 —— 怪物扩展字段重置（+ 飞行/召唤标记图懒加载）
// 懒加载 Monster/FlyingMonsterMark.img 与 Monster/SummonMonsterMark.img
//（dword_9A05D4 引用计数，dword_8F84B8 资源管理器 vt+60）；随后清怪物侧字段：
// +96=529（条件 id）、+608=100、+7148 大状态=0、+7632/7636 窗口=-1、骑乘/名牌/
// 拾取族（+7808/+7828 起 29 类 × 16 字节文案表 = 0x4DB130 的条目侧、+8300..8364、
// +8516/+8520=-1、+8528 文案串、+8584/8588 随机区间），尾段 +7732=200。
// 【推断】怪物生成/复位的扩展段（0x4DB410 MONSTER CREATE 路径下游）。
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4DE700(int this)  // 怪物扩展字段重置
{
  unsigned int nNameCap; // edx
  int pszNameBuf1; // edi
  int pszNameBuf2; // edx
  int pCatEntry; // eax
  void **pVecBegin; // ecx
  void **pVecWalk; // edi
  int nLoopCnt; // ecx
  size_t *result; // eax
  void **pVecEnd; // [esp+Ch] [ebp-Ch] BYREF
  int nCatCount; // [esp+10h] [ebp-8h]
  int pCatEntry2; // [esp+14h] [ebp-4h]

  if ( dword_9A05D4 == 0 && dword_9A05D8 == 0 )  // 若 dword_9A05D4 == 0 与/或 dword_9A05D8 == 0
  {
    dword_9A05D8 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
                     dword_8F84B8,  // ）对象销毁/释放
                     "Monster/FlyingMonsterMark.img");  // 字符串 “Monster/FlyingMonsterMark.img”
    dword_9A05DC = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
                     dword_8F84B8,  // ）对象销毁/释放
                     "Monster/SummonMonsterMark.img");  // 字符串 “Monster/SummonMonsterMark.img”
  }
  ++dword_9A05D4;  // 全局 竞技场/PVP 深度计数
  *(uint32_t *)(this + 96) = 529;  // this+96〔nStatusMode(推断)〕等 2 字段
  *(uint32_t *)(this + 608) = 100;  // this+608〔nAttackGate〕
  *(uint32_t *)(this + 7668) = 0;  // this+7668〔nSwitchGuardT〕
  *(uint32_t *)(this + 7688) = 0;  // this+7688〔f_1E08〕
  *(uint32_t *)(this + 7148) = 0;  // 写 this+7148 = 0（大状态镜像槽）
  *(uint32_t *)(this + 7672) = -1;  // this+7672〔f_1DF8〕
  *(uint32_t *)(this + 7676) = -1;  // this+7676〔f_1DFC〕
  *(uint32_t *)(this + 7720) = 0;  // this+7720〔f_1E28〕
  *(uint32_t *)(this + 7716) = 0;  // this+7716〔f_1E24〕
  *(uint32_t *)(this + 7712) = 0;  // this+7712〔f_1E20〕
  *(uint32_t *)(this + 7708) = 0;  // this+7708〔nIdleStamp〕
  *(uint32_t *)(this + 648) = 0;  // this+648〔uMonFlagBits〕
  *(uint8_t *)(this + 7764) = 0;  // this+7764〔bTimerObj〕
  *(uint32_t *)(this + 7768) = 0;  // this+7768〔pObj7768〕
  *(uint32_t *)(this + 7772) = 0;  // 写 this+7772 = 0（反击态）
  *(uint8_t *)(this + 7776) = 0;  // this+7776〔bPeerInit〕
  *(uint8_t *)(this + 7801) = 0;  // this+7801〔bActiveRender〕
  *(uint32_t *)(this + 7632) = -1;  // this+7632〔uWindow7632(推断)〕
  *(uint32_t *)(this + 7636) = -1;  // this+7636〔nPosWinY〕
  nNameCap = *(uint32_t *)(this + 7176);  // this+7176〔nNameStrCap〕
  if ( nNameCap < 0x10 )  // nNameCap=this+7176 nNameStrCap
    pszNameBuf1 = this + 7156;  // this+7156 std::string SSO 内联缓冲
  else
    pszNameBuf1 = *(uint32_t *)(this + 7156);  // this+7156〔bParam3(推断)〕
  if ( nNameCap < 0x10 )  // nNameCap=this+7176 nNameStrCap
    pszNameBuf2 = this + 7156;  // this+7156 std::string SSO 内联缓冲
  else
    pszNameBuf2 = *(uint32_t *)(this + 7156);  // this+7156〔bParam3(推断)〕
  sub_406D00((uint32_t *)(this + 7152), &pVecEnd, pszNameBuf2, pszNameBuf1 + *(uint32_t *)(this + 7172));  // std::string 中段擦除（·sub_401230 erase，pos 与 n 由指针
  if ( *(uint32_t *)(this + 7808) != 0 )  // this+7808〔风格/分支选择〕
    j__free(*(void **)(this + 7808));  // this+7808〔风格/分支选择〕
  pCatEntry = this + 7828;  // this+7828〔nSubStateD〕
  *(uint32_t *)(this + 7808) = 0;  // this+7808〔风格/分支选择〕
  *(uint32_t *)(this + 7812) = 0;  // this+7812〔nSubStateA(推断)〕
  *(uint32_t *)(this + 7816) = 0;  // this+7816〔nSubStateB(推断)〕
  *(uint32_t *)(this + 7820) = 0;  // this+7820〔pInteractSnap(推断)〕
  pCatEntry2 = this + 7828;  // this+7828〔nSubStateD〕
  nCatCount = 29;
  do
  {
    pVecBegin = *(void ***)pCatEntry;  // pCatEntry=this+7828 nSubStateD
    if ( *(uint32_t *)pCatEntry != 0 )  // pCatEntry=this+7828 nSubStateD
    {
      pVecWalk = *(void ***)pCatEntry;  // pCatEntry=this+7828 nSubStateD
      pVecEnd = *(void ***)(pCatEntry + 4);  // pCatEntry=this+7828 nSubStateD
      if ( pVecBegin != pVecEnd )
      {
        do
          sub_41B010(pVecWalk++);  // 驻留句柄析构（引用计数减到 0 释放）
        while ( pVecWalk != pVecEnd );
        pCatEntry = pCatEntry2;  // pCatEntry=this+7828 nSubStateD
      }
      j__free(*(void **)pCatEntry);  // 调 堆释放
      pCatEntry = pCatEntry2;  // pCatEntry=this+7828 nSubStateD
    }
    nLoopCnt = nCatCount;
    *(uint32_t *)pCatEntry = 0;  // *pCatEntry = 0
    *(uint32_t *)(pCatEntry + 4) = 0;  // pCatEntry=this+7828 nSubStateD
    *(uint32_t *)(pCatEntry + 8) = 0;  // pCatEntry=this+7828 nSubStateD
    pCatEntry += 16;  // pCatEntry=this+7828 nSubStateD
    pCatEntry2 = pCatEntry;  // pCatEntry2=this+7828 nSubStateD
    nCatCount = nLoopCnt - 1;
  }
  while ( nLoopCnt != 1 );
  *(uint32_t *)(this + 8288) = -1;  // this+8288〔nGrabDataVal(推断)〕
  *(uint32_t *)(this + 8332) = -1;  // this+8332〔f_208C〕
  *(uint32_t *)(this + 8328) = -1;  // this+8328〔f_2088〕
  *(uint32_t *)(this + 8324) = -1;  // this+8324〔bHoldMode(推断)〕
  *(uint32_t *)(this + 8320) = -1;  // this+8320〔pHoldHost(推断)〕
  *(uint32_t *)(this + 8316) = -1;  // this+8316〔nHoldSrc(推断)〕
  *(uint32_t *)(this + 8312) = -1;  // this+8312〔nHoldPosZ(推断)〕
  *(uint32_t *)(this + 8292) = 1000;  // this+8292〔bModeFlag(推断)〕
  if ( *(uint32_t *)(this + 8340) != 0 )  // this+8340〔pAnimA(推断)〕
    j__free(*(void **)(this + 8340));  // 释放 this+8340〔pAnimA(推断)〕堆块
  *(uint32_t *)(this + 8340) = 0;  // this+8340〔pAnimA(推断)〕
  *(uint32_t *)(this + 8344) = 0;  // this+8344〔nRideMode(推断)〕
  *(uint32_t *)(this + 8348) = 0;  // this+8348〔nPhaseParity(推断)〕
  *(uint32_t *)(this + 8352) = 0;  // 写 this+8352 = 0（骑乘/宿主槽）
  *(uint32_t *)(this + 8356) = 0;  // 写 this+8356 = 0（拾取信息槽 B）
  *(uint32_t *)(this + 8360) = 0;  // 写 this+8360 = 0（拾取信息 7 字节对象指针）
  *(uint32_t *)(this + 8364) = 0;  // this+8364〔pFrameObject(推断)〕
  *(uint32_t *)(this + 8472) = 0;  // this+8472〔nFinishFlag(推断)〕
  *(uint32_t *)(this + 8476) = 0;  // this+8476〔bFinishFlag(推断)〕
  *(uint32_t *)(this + 8300) = -1;  // this+8300〔pHoldObj(推断)〕
  *(uint32_t *)(this + 8304) = -1;  // this+8304〔nHoldPosX(推断)〕
  *(uint32_t *)(this + 8308) = -1;  // this+8308〔nHoldPosY(推断)〕
  *(uint8_t *)(this + 8296) = 0;  // this+8296〔nOffsetVal(推断)〕
  *(uint32_t *)(this + 8516) = -1;  // this+8516 随机区间下界
  *(uint32_t *)(this + 8520) = -1;  // this+8520〔bUseCtx(推断)〕
  *(uint8_t *)(this + 8524) = 1;  // this+8524〔bMonCfgFlag〕
  result = sub_4015C0((size_t *)(this + 8528), szPassword, 0);  // 【std::string构造赋值】
  *(uint32_t *)(this + 8584) = 0;  // this+8584〔bPhaseDone(推断)〕
  *(uint32_t *)(this + 8588) = 0;  // this+8588〔f_218C〕
  *(uint8_t *)(this + 8569) = 0;  // this+8569〔f_2179〕
  *(uint8_t *)(this + 8570) = 0;  // this+8570〔f_217A〕
  *(uint32_t *)(this + 7732) = 200;  // this+7732〔f_1E34〕
  return result;
}


// ------------------------------------------------------------
// 0x4DE980 sub_4DE980 —— vector<32B>::_Insert_n（在 pszArg2 位置填充插入 uArg3 个值）
// 标准 MSVC vector 扩容/搬移内核：0x7FFFFFF 条上限、1.5×（(cap>>1)+cap）增长、
// sub_4DA820/4DA7F0/4DA050 区间搬移、sub_4DE3B0/4DAB30 填充，容器 = this+4/+8/+12，
// 插入值 = Block 起的 32 字节（qmemcpy 到 valBuf）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4DE980(int this, char *pszArg2, unsigned int uArg3, void *Block)  // 实现：vector<32B>::_Insert_n（在 pszArg2 位置填充插入 uArg3 个值）
{
  int pMyBegin; // edx
  unsigned int result; // eax
  int nMyCount; // ecx
  int nMyCount2; // ecx
  unsigned int nGrowCount; // eax
  int nMyCount3; // ecx
  int nMyCount4; // eax
  char *pNewBegin; // edi
  int pMyBegin2; // ecx
  int nMyCount5; // eax
  unsigned int nNewCount; // esi
  char *pOldEnd; // eax
  int nNewEnd; // esi
  char *pInsertEnd; // esi
  char *fld_42; // [esp-18h] [ebp-54h]
  char *pOldEnd2; // [esp-Ch] [ebp-48h]
  char *nTailCount; // [esp-8h] [ebp-44h]
  int tmpHdr; // [esp+0h] [ebp-3Ch] BYREF
  uint32_t valBuf[9]; // [esp+Ch] [ebp-30h] BYREF
  int nGuardState; // [esp+38h] [ebp-4h]
  int nAllocBytes; // [esp+48h] [ebp+Ch]
  char *pNewBuf; // [esp+4Ch] [ebp+10h]
  char *pOldEnd3; // [esp+4Ch] [ebp+10h]

  pMyBegin = *(uint32_t *)(this + 4);  // 读 pMyBegin = this+4（宿主对象指针）
  valBuf[8] = &tmpHdr;
  qmemcpy(valBuf, Block, 0x20u);  // 调 内存块拷贝(内联展开)
  if ( pMyBegin != 0 )  // pMyBegin=this+4 宿主对象
    result = (*(uint32_t *)(this + 12) - pMyBegin) >> 5;  // 涉及字段 “+12 技能槽记录次字”
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( pMyBegin != 0 )  // pMyBegin=this+4 宿主对象
      nMyCount = (*(uint32_t *)(this + 8) - pMyBegin) >> 5;  // 涉及字段 “+8 技能槽记录首字”
    else
      nMyCount = 0;
    if ( 0x7FFFFFF - nMyCount < uArg3 )
      sub_4A30C0();
    if ( pMyBegin != 0 )  // pMyBegin=this+4 宿主对象
      nMyCount2 = (*(uint32_t *)(this + 8) - pMyBegin) >> 5;  // 涉及字段 “+8 技能槽记录首字”
    else
      nMyCount2 = 0;
    if ( result >= uArg3 + nMyCount2 )
    {
      pOldEnd = *(char **)(this + 8);  // this+32〔nHeight(推断)〕
      pOldEnd3 = pOldEnd;  // pOldEnd=this+32 nHeight
      if ( (pOldEnd - pszArg2) >> 5 >= uArg3 )  // pOldEnd=this+32 nHeight
      {
        pInsertEnd = &pOldEnd[-32 * uArg3];  // pOldEnd=this+32 nHeight
        *(uint32_t *)(this + 8) = sub_4DA820(pInsertEnd, pOldEnd, pOldEnd);  // this+8〔nSkillRec8(推断)〕等 2 字段
        sub_4DA7F0(pszArg2, pInsertEnd, pOldEnd3);  // 调 pszArg3 起（重叠区间向前移时用）
        return (unsigned int)sub_4DA050(pszArg2, &pszArg2[32 * uArg3], valBuf);  // 返回 （步长 32，std::fill 的定长 POD 版）。返回 end
      }
      else
      {
        sub_4DA820(pszArg2, pOldEnd, &pszArg2[32 * uArg3]);  // 调 pszArg3 起，目标非空才拷
        nTailCount = (char *)(uArg3 - ((*(uint32_t *)(this + 8) - (int)pszArg2) >> 5));  // 涉及字段 “+8 技能槽记录首字”
        pOldEnd2 = *(char **)(this + 8);  // this+32〔nHeight(推断)〕
        nGuardState = 2;
        sub_4DE3B0(pOldEnd2, nTailCount, valBuf);  // 短函数，转写体未含可辨字符串证据；语义待定【待验证】
        nNewEnd = 32 * uArg3 + *(uint32_t *)(this + 8);  // 涉及字段 “+8 技能槽记录首字”
        *(uint32_t *)(this + 8) = nNewEnd;  // 写 this+8 = nNewEnd（技能槽记录首字）
        return (unsigned int)sub_4DA050(pszArg2, (char *)(nNewEnd - 32 * uArg3), valBuf);  // 返回 （步长 32，std::fill 的定长 POD 版）。返回 end
      }
    }
    else
    {
      if ( 0x7FFFFFF - (result >> 1) >= result )
        nGrowCount = (result >> 1) + result;
      else
        nGrowCount = 0;
      if ( pMyBegin != 0 )  // pMyBegin=this+4 宿主对象
        nMyCount3 = (*(uint32_t *)(this + 8) - pMyBegin) >> 5;  // 涉及字段 “+8 技能槽记录首字”
      else
        nMyCount3 = 0;
      if ( nGrowCount < uArg3 + nMyCount3 )
      {
        if ( pMyBegin != 0 )  // pMyBegin=this+4 宿主对象
          nMyCount4 = (*(uint32_t *)(this + 8) - pMyBegin) >> 5;  // 涉及字段 “+8 技能槽记录首字”
        else
          nMyCount4 = 0;
        nGrowCount = uArg3 + nMyCount4;
      }
      nAllocBytes = 32 * nGrowCount;
      pNewBuf = (char *)operator new(32 * nGrowCount);
      fld_42 = *(char **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
      nGuardState = 0;
      pNewBegin = sub_4DA820(fld_42, pszArg2, pNewBuf);  // 调 pszArg3 起，目标非空才拷
      sub_4DAB30(pNewBegin, (char *)uArg3, valBuf);  // 定长块批量填充（cdecl）
      sub_4DA820(pszArg2, *(char **)(this + 8), &pNewBegin[32 * uArg3]);  // this+32〔nHeight(推断)〕
      pMyBegin2 = *(uint32_t *)(this + 4);  // 读 pMyBegin2 = this+4（宿主对象指针）
      if ( pMyBegin2 != 0 )  // pMyBegin2=this+4 宿主对象
        nMyCount5 = (*(uint32_t *)(this + 8) - pMyBegin2) >> 5;  // 涉及字段 “+8 技能槽记录首字”
      else
        nMyCount5 = 0;
      nNewCount = nMyCount5 + uArg3;
      if ( pMyBegin2 != 0 )  // pMyBegin2=this+4 宿主对象
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      *(uint32_t *)(this + 12) = &pNewBuf[nAllocBytes];  // 写 this+12 = &pNewBuf[nAllocBytes]（技能槽记录次字）
      *(uint32_t *)(this + 8) = &pNewBuf[32 * nNewCount];  // 写 this+8 = &pNewBuf[32 * nNewCount]（技能槽记录首字）
      *(uint32_t *)(this + 4) = pNewBuf;  // 写 this+4 = pNewBuf（宿主对象指针）
      return (unsigned int)pNewBuf;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DEBD0 sub_4DEBD0 —— 容器重建/释放（a2 对象的 +4/+8/+C 字段族）
// 4 处 sub_44BD30（容器插入/搬运）+ 2 处 sub_41FEB0，尾段 sub_63A7C0/sub_5E51F0
//（析构/释放族）与 sub_4DE680（noreturn 收尾）。【推断】列表迁移与清理；细节未定案【待验证】。
// ------------------------------------------------------------
void /*thiscall*/ sub_4DEBD0(int this, int nArg2, unsigned int uArg3, int pArg4)  // 实现：容器重建/释放（a2 对象的 +4/+8/+C 字段族）
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

  v4 = *(void **)(pArg4 + 4);  // pArg4+4〔宿主对象〕
  v28[0] = *(void **)pArg4;
  fld_4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;  // 涉及字段 “+12 技能槽记录次字”
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // 涉及字段 “+8 技能槽记录首字”
    else
      fld_8 = 0;
    if ( 0x1FFFFFFF - fld_8 < uArg3 )
      sub_4DE680(this);  // noreturn 异常抛出（”vector<T> too long”）
    if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // 涉及字段 “+8 技能槽记录首字”
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint32_t *)(this + 8);  // 读 fld_83 = this+8（技能槽记录首字）
      v20 = (fld_83 - nArg2) >> 3 < uArg3;  // fld_83=this+8 物品 id
      v21 = 8 * uArg3;
      v30 = 8 * uArg3;
      fld_832 = fld_83;  // fld_83=this+8 物品 id
      if ( v20 )
      {
        sub_44BD30(nArg2, fld_83, nArg2 + v21);  // 8 字节元素正向拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - nArg2) >> 3);  // 涉及字段 “+8 技能槽记录首字”
        fld_85 = *(uint32_t *)(this + 8);  // 读 fld_85 = this+8（技能槽记录首字）
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);  // 调 填充补足尾段
        fld_86 = v30 + *(uint32_t *)(this + 8);  // 涉及字段 “+8 技能槽记录首字”
        *(uint32_t *)(this + 8) = fld_86;  // 写 this+8 = fld_86（技能槽记录首字）
        sub_41FEB0(nArg2, fld_86 - v30, v28);  // 8B 元素区间拷贝
      }
      else
      {
        v23 = fld_83 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);  // 8 字节元素正向拷贝
        sub_44BD00(nArg2, v23, fld_832);  // 8 字节元素反向拷贝
        sub_41FEB0(nArg2, nArg2 + v30, v28);  // 8B 元素区间拷贝
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )
        v11 = (fld_C >> 1) + fld_C;
      else
        v11 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // 涉及字段 “+8 技能槽记录首字”
      else
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )  // fld_4=this+4 宿主对象
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // 涉及字段 “+8 技能槽记录首字”
        else
          fld_88 = 0;
        v11 = uArg3 + fld_88;
      }
      v31 = 8 * v11;
      pMem = (char *)operator new(8 * v11);
      fld_42 = *(uint32_t *)(this + 4);  // 读 fld_42 = this+4（宿主对象指针）
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, nArg2, pMem);  // 结果 = 8 字节元素正向拷贝
      sub_63A7C0(v32, uArg3, v28);  // 强化结果公共件
      sub_44BD30(nArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);  // 8 字节元素正向拷贝
      fld_43 = *(uint32_t *)(this + 4);  // 读 fld_43 = this+4（宿主对象指针）
      if ( fld_43 != 0 )  // fld_43=this+4 宿主对象
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;  // 涉及字段 “+8 技能槽记录首字”
      else
        fld_89 = 0;
      v17 = fld_89 + uArg3;
      if ( fld_43 != 0 )  // fld_43=this+4 宿主对象
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      *(uint32_t *)(this + 12) = &pMem[v31];  // 写 this+12 = &pMem[v31]（技能槽记录次字）
      *(uint32_t *)(this + 8) = &pMem[8 * v17];  // 写 this+8 = &pMem[8 * v17]（技能槽记录首字）
      *(uint32_t *)(this + 4) = pMem;  // 写 this+4 = pMem（宿主对象指针）
    }
  }
}


// ------------------------------------------------------------
// 0x4DEE20 sub_4DEE20 —— 按车主 id 的映射表查找/插入
// 键 = nArg2 的 vt+576 车主 id，经 sub_4BE520 在 this+84 起的树/有序容器定位
//（端点 this+88），未命中（== 端点）走插入路径。【推断】宿主→数据映射；
// 与 0x4DEEA0/0x4DE700/0x4DEFF0（vector 内核族）配套。
// ------------------------------------------------------------
int */*thiscall*/ sub_4DEE20(int **this, int nArg2, int *pDwArg3)  // 按车主 id 的映射表查找/插入
{
  int pObj; // edi
  int **pThis_15; // ebx
  int *result; // eax
  uint8_t tmpEntry[8]; // [esp+Ch] [ebp-10h] BYREF —— 新条目（sub_42CDB0 构造）
  int nOwnerId; // [esp+14h] [ebp-8h] BYREF —— 车主 id（键）
  int *pDwArg32; // [esp+18h] [ebp-4h] BYREF

  pObj = nArg2;
  pThis_15 = this + 21;  // this+21〔bArmorState〕
  nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // 调虚槽 +576
  sub_4BE520(pThis_15, &pDwArg32, &nArg2);  // 映射下界查找（lower_bound）
  result = pDwArg32;
  if ( pDwArg32 == *(this + 22) )  // this+88〔pFxObjB(推断)〕
  {
    nOwnerId = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 576))(pObj);  // 调虚槽 +576
    pDwArg32 = pDwArg3;
    return (int *)sub_42CDB0(tmpEntry, &nOwnerId);  // std::map 插入定位
  }
  else
  {
    pDwArg32[4] += (int)pDwArg3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DEEA0 sub_4DEEA0 —— 32 字节/条容器拷贝赋值（vector::operator= 内核）
// 源（pArg2）空 → 清空本容器并 free；源条数 ≤ 容量 → sub_4DA7C0 拷贝后收端点；
// 条数 > 容量 → free 旧缓冲重新分配。与 0x4DEE20/0x4DE700/0x4DEFF0 同族。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DEEA0(int this, int pArg2)  // 实现：32 字节/条容器拷贝赋值（vector::operator= 内核）
{
  char *pSrcBegin; // ebx
  unsigned int nSrcCount; // eax
  int pMyBegin; // ecx
  unsigned int nMyCount; // edx
  int pSrcBegin2; // eax
  int nNewEnd; // edi
  unsigned int nMyCap; // edx
  int nMyCount2; // eax
  char *pSrcMid; // ebx
  int pSrcBegin3; // ecx
  unsigned int nSrcCount2; // eax

  if ( this == pArg2 )
    return this;  // 返回自身指针
  pSrcBegin = *(char **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( pSrcBegin == nullptr || (nSrcCount = (*(uint32_t *)(pArg2 + 8) - (int)pSrcBegin) >> 5) == 0 )  // pArg2+8〔nSkillRec8(推断)〕
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // 判定 “+4 宿主对象指针”
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    *(uint32_t *)(this + 4) = 0;  // 写 this+4 = 0（宿主对象指针）
    *(uint32_t *)(this + 8) = 0;  // 写 this+8 = 0（技能槽记录首字）
    *(uint32_t *)(this + 12) = 0;  // 写 this+12 = 0（技能槽记录次字）
    return this;  // 返回自身指针
  }
  pMyBegin = *(uint32_t *)(this + 4);  // 读 pMyBegin = this+4（宿主对象指针）
  if ( pMyBegin != 0 )  // pMyBegin=this+4 宿主对象
    nMyCount = (*(uint32_t *)(this + 8) - pMyBegin) >> 5;  // 涉及字段 “+8 技能槽记录首字”
  else
    nMyCount = 0;
  if ( nSrcCount <= nMyCount )
  {
    sub_4DA7C0(pSrcBegin, *(char **)(pArg2 + 8), *(char **)(this + 4));  // 调 拷贝后收端点
    pSrcBegin2 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( pSrcBegin2 != 0 )
      nNewEnd = *(uint32_t *)(this + 4) + 32 * ((*(uint32_t *)(pArg2 + 8) - pSrcBegin2) >> 5);  // 涉及字段 “+4 宿主对象指针”
    else
      nNewEnd = *(uint32_t *)(this + 4);  // 读 nNewEnd = this+4（宿主对象指针）
    *(uint32_t *)(this + 8) = nNewEnd;  // 写 this+8 = nNewEnd（技能槽记录首字）
    return this;  // 返回自身指针
  }
  if ( pMyBegin != 0 )  // pMyBegin=this+4 宿主对象
    nMyCap = (*(uint32_t *)(this + 12) - pMyBegin) >> 5;  // 涉及字段 “+12 技能槽记录次字”
  else
    nMyCap = 0;
  if ( nSrcCount > nMyCap )
  {
    if ( pMyBegin != 0 )  // pMyBegin=this+4 宿主对象
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    pSrcBegin3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( pSrcBegin3 != 0 )
      nSrcCount2 = (*(uint32_t *)(pArg2 + 8) - pSrcBegin3) >> 5;  // pArg2+8〔nSkillRec8(推断)〕
    else
      nSrcCount2 = 0;
    if ( sub_4A35C0((uint32_t *)this, nSrcCount2) != 0 )  // 调 (推断)与 0x4A3570 同构的第二个 reserve（另一元素类型/容器）
      *(uint32_t *)(this + 8) = sub_4DB3F0(*(char **)(pArg2 + 4), *(char **)(pArg2 + 8), *(char **)(this + 4));  // 转发垫片（stdcall）→ 0x4DA820（三参直传）。
    return this;  // 返回自身指针
  }
  if ( pMyBegin != 0 )  // pMyBegin=this+4 宿主对象
    nMyCount2 = (*(uint32_t *)(this + 8) - pMyBegin) >> 5;  // 涉及字段 “+8 技能槽记录首字”
  else
    nMyCount2 = 0;
  pSrcMid = (char *)(*(uint32_t *)(pArg2 + 4) + 32 * nMyCount2);  // pArg2+4〔宿主对象〕
  sub_4DA7C0(*(char **)(pArg2 + 4), pSrcMid, *(char **)(this + 4));  // 调 拷贝后收端点
  *(uint32_t *)(this + 8) = sub_4DA820(pSrcMid, *(char **)(pArg2 + 8), *(char **)(this + 8));  // this+8〔nSkillRec8(推断)〕等 2 字段
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4DEFF0 sub_4DEFF0 —— 32 字节/条容器随机访问写（vector operator[] 写侧）
// 下标 a2 在界内 → sub_4DE360 区间搬移覆盖；越界（容量不足）→ sub_4DE980
// 扩容插入。【推断】std::vector<32字节T>::operator[] / resize 写路径。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4DEFF0(  // 32 字节/条容器随机访问写（vector operator[] 写侧）
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
  int pMyBegin; // esi
  unsigned int nMyCount; // edx
  uint32_t *result; // eax
  int nMyCount2; // edx

  pMyBegin = *(uint32_t *)(this + 4);  // 读 pMyBegin = this+4（宿主对象指针）
  if ( pMyBegin != 0 )  // pMyBegin=this+4 宿主对象
    nMyCount = (*(uint32_t *)(this + 8) - pMyBegin) >> 5;  // 涉及字段 “+8 技能槽记录首字”
  else
    nMyCount = 0;
  result = (uint32_t *)a2;
  if ( nMyCount >= a2 )
  {
    if ( pMyBegin != 0 && a2 < (*(uint32_t *)(this + 8) - pMyBegin) >> 5 )  // 判定 “+8 技能槽记录首字”
      return sub_4DE360((char **)this, &a2, (char *)(pMyBegin + 32 * a2), *(char **)(this + 8));  // 32 字节/条容器区间搬移（vector erase/insert 族内核）
  }
  else
  {
    if ( pMyBegin != 0 )  // pMyBegin=this+4 宿主对象
      nMyCount2 = (*(uint32_t *)(this + 8) - pMyBegin) >> 5;  // 涉及字段 “+8 技能槽记录首字”
    else
      nMyCount2 = 0;
    return (uint32_t *)sub_4DE980(this, *(char **)(this + 8), a2 - nMyCount2, &Block);  // vector<32B>::_Insert_n（在 pszArg2 位置填充插入 uArg3
  }
  return result;
}



// ------------------------------------------------------------
// 0x4DF060 sub_4DF060 —— 表现对象构造（清零 + +20/=1 使能 + sub_4017E0 字符串构造）。
// 【推断】成员表现效果对象的默认初始化。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4DF060(uint32_t *this)  // 表现对象构造（清零 + +20/=1 使能 + sub_4017E0 字符串构造）。
{
  uint32_t *pThis_7; // ecx

  pThis_7 = this + 7;  // this+7 【推断】路径尾终止位
  pThis_7[1] = 0;  // pThis_7=this+7 路径尾终止位
  pThis_7[2] = 0;  // pThis_7=this+7 路径尾终止位
  pThis_7[3] = 0;  // pThis_7=this+7 路径尾终止位
  *this = 0;
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = 0;  // this+12〔nSkillRec12(推断)〕
  *(this + 4) = 0;  // 写 this+4 = 0（宿主对象指针）
  *((uint8_t *)this + 20) = 1;  // this+20〔nPage(推断)〕
  *((uint8_t *)this + 21) = 0;  // this+21〔bArmorState〕
  *(this + 6) = 0;  // this+24〔nPageMax(推断)〕
  sub_4017E0((int)pThis_7);  // 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4DF0C0 sub_4DF0C0 —— CNPieceDestroyEffect 构造（vftable + sub_5FE330 基类 +
// sub_5FE3A0 参数装载，fArg2 = st0 浮点参）。掉落物/碎块销毁表现。【推断】。
// ------------------------------------------------------------
uint32_t */*userpurge*/ sub_4DF0C0@<eax>(uint32_t *uArg1@<ecx>, double fArg2@<st0>, void *Block, int nArg4, int nArg5, int nArg6, int nArg7)  // 实现：CNPieceDestroyEffect 构造（vftable + sub_5FE330 基类 +
{
  sub_42AAB0();  // CNRDObject 构造（三内嵌 CNTimer）
  *uArg1 = &CNPieceDestroyEffect::`vftable';  // 构造装配 vftable：CNPieceDestroyEffect
  sub_5FE330((int)uArg1);  // 调 基类 +
  sub_5FE3A0((int)uArg1, fArg2, Block, nArg4, nArg5, nArg6, nArg7);  // 调 参数装载
  return uArg1;
}



// ------------------------------------------------------------
// 0x4DF130 sub_4DF130 —— CNPieceDestroyEffect 析构壳
// 先调 0x4DF160 二段析构，pszArg2 位 0 置位时 free 块本身（同 0x4D6880 约定）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4DF130(void *Block, char pszArg2)  // CNPieceDestroyEffect 析构壳
{
  sub_4DF160();  // CNPieceDestroyEffect 二段析构（成员释放）。
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4DF160 sub_4DF160 —— CNPieceDestroyEffect 二段析构（成员释放）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DF160(uint32_t *this)  // 实现：CNPieceDestroyEffect 二段析构（成员释放）。
{
  *this = &CNPieceDestroyEffect::`vftable';  // 构造装配 vftable：CNPieceDestroyEffect
  sub_5FE380();
  return sub_42A450(this);  // CNRDObject 析构主体
}



// ------------------------------------------------------------
// 0x4DF1B0 sub_4DF1B0 —— CNEnchantWeapon 构造
// sub_4B1030 基类 + 换挂 CNEnchantWeapon::vftable，+120/+124/+128 清零，
// sub_5FEEB0/sub_5FEEE0 两段初始化（nArg2..nArg5 = 强化参数）。武器强化表现。【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DF1B0(int this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：CNEnchantWeapon 构造
{
  sub_4B1030((uint8_t *)this);  // IRDAppendage 基类构造
  *(uint32_t *)this = &CNEnchantWeapon::`vftable';  // 构造装配 vftable：CNEnchantWeapon
  *(uint32_t *)(this + 120) = 0;  // 写 this+120 = 0（动画对象）
  *(uint32_t *)(this + 124) = 0;  // 写 this+124 = 0（光环动画件）
  *(uint32_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  sub_5FEEB0(this);
  sub_5FEEE0(nArg2, nArg3, nArg4, nArg5);
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x4DF220 sub_4DF220 —— CNEnchantWeapon 析构壳
// 先调 0x4DF250 二段析构，pszArg2 位 0 置位时 free 块本身（同 0x4D6880 约定）。
// ------------------------------------------------------------
void */*thiscall*/ sub_4DF220(void *Block, char pszArg2)  // CNEnchantWeapon 析构壳
{
  sub_4DF250();  // CNEnchantWeapon 二段析构
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x4DF250 sub_4DF250 —— CNEnchantWeapon 二段析构
// nullsub_3 + 释放 this+120 起的 vector 缓冲（+120/124/128 三件套），换挂回
// IRDAppendage::vftable 走 sub_5F6640，内嵌 IObject 子块复位（同 0x4D68B0 尾段）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4DF250(void **this)  // 实现：CNEnchantWeapon 二段析构
{
  int result; // eax

  *this = &CNEnchantWeapon::`vftable';  // 构造装配 vftable：CNEnchantWeapon
  nullsub_3(this);
  if ( *(this + 30) != nullptr )  // 判定 “+120 动画对象”
    j__free(*(this + 30));  // this+120〔pAnimObj〕
  *(this + 30) = nullptr;  // 写 this+120 = nullptr（动画对象）
  *(this + 31) = nullptr;  // 写 this+124 = nullptr（光环动画件）
  *(this + 32) = nullptr;  // this+128〔szStatusKeyBuf(推断)〕
  *this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // 调 基类析构
  *((uint8_t *)this + 12) = 0;  // 写 this+12 = 0（技能槽记录次字）
  *(this + 2) = &nengine::IObject::`vftable';  // 写 this+8 = &nengine::IObject::`vftable’（技能槽记录首字）
  return result;
}



// ------------------------------------------------------------
// 0x4DF2D0 sub_4DF2D0 —— ★ 大状态逐帧 tick 分派器（研究 §16 P41：tick case 硬编码）
// 按 this+7148 大状态 switch 分派（case 3/4/5/6/7/8/9/11/12/17），各 case 组合调用
// sub_4D8FE0（视野）、sub_4DAB60（条件查询）、sub_4DBDB0（栅格推挤）、
// sub_4DA6B0（技能栏越界）、sub_4918E0/sub_42F220（计时器）—— 即怪物 AI 的
// 逐帧行为状态机宿主（走位/追击/绕后均在此驱动）。pDwArg2/pDwArg3 = 输入/输出
// 参数块，nArg4 = 帧上下文【推断】。
// ------------------------------------------------------------
void /*thiscall*/ sub_4DF2D0(int *this, int *pDwArg2, int *pDwArg3, int nArg4)  // 实现：大状态逐帧 tick 分派器（研究 §16 P41：tick case 硬编码）
{
  int v5; // edi
  int v6; // ebx
  int v7; // eax
  int fld_e79; // edi
  signed int v9; // edi
  int pAuraObject; // edi  | +0x1C58 → 光环对象（★已确证偏移语义 this+7256）（证据 va=确证语义）（IRDActiveObject·基类）
  int *pThis; // ecx
  int v12; // eax
  int pAuraObject_; // ecx  | +0x1C58 → 光环对象（★已确证偏移语义 this+7256）（证据 va=确证语义）（IRDActiveObject·基类）
  int pTarget7252_2; // ecx  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int v15; // edi
  int fld_e1919; // edi  | +0x1DFC → 名牌/骑乘族槽（-1 哨兵）（IRDMonster·基类；va=004DE700）
  int fld_e1918; // edi  | +0x1DF8 → 名牌/骑乘族槽（-1 哨兵）（IRDMonster·基类；va=004DE700）
  int *pDwArg22; // edi
  int pTarget7252; // ecx  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int v20; // edi
  int fld_e19052; // edi
  int fld_e18133; // eax  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int fld_e18132; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int fld_e1905; // edi
  int fld_e18134; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  bool v26; // cc
  int fld_e18135; // eax  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int v28; // edi
  double v29; // st7
  int v30; // edi
  int fld_e18136; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  double v32; // st7
  int pTarget7252_; // ecx  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int v34; // edi
  int fld_e18138; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  int fld_e1812; // eax
  double v37; // st7
  int fld_e19192; // edi  | +0x1DFC → 名牌/骑乘族槽（-1 哨兵）（IRDMonster·基类；va=004DE700）
  int fld_e19182; // edi  | +0x1DF8 → 名牌/骑乘族槽（-1 哨兵）（IRDMonster·基类；va=004DE700）
  unsigned int v40; // edi
  int pObserverVecEnd; // ecx
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
  float fld_e1933; // [esp+40h] [ebp-20h]  | +0x1E34 → 【推断】复位批尾置 200（与 +608=100 同风格：数值型门限初值）（IRDMonster·基类；va=004DE700）
  float v72; // [esp+48h] [ebp-18h]
  unsigned int v73; // [esp+4Ch] [ebp-14h]
  int v74; // [esp+50h] [ebp-10h]
  float fld_e181310; // [esp+68h] [ebp+8h]
  int v76; // [esp+70h] [ebp+10h]

  v5 = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);  // 结果 = 虚调用 vt+184
  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 188))(this);  // 结果 = 虚调用 vt+188
  switch ( *(this + 1787) )  // this+7148〔nBigState〕
  {
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      pDwArg22 = pDwArg2;
      if ( (uint8_t)sub_4DA6B0(pDwArg2) == 0 && rand() % 100 < 30 )  // 调 滚动格判定
        goto LABEL_48;
      return;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
      pTarget7252 = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( pTarget7252 == 0 )  // fld_e1813=this+7252 pTarget7252
        goto LABEL_45;
      v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget7252 + 124))(pTarget7252);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) > v20 )  // 虚调用 vt+124
      {
        fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));  // this+7252〔pTarget7252〕
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) <= fld_e18132 )  // 虚调用 vt+124
          goto LABEL_55;
        *pDwArg3 = 2;
        fld_e1905 = *(this + 1905);  // 读 fld_e1905 = this+7620（速度/属性参数对象）
        fld_e18133 = *(uint32_t *)(fld_e1905 + 24) + (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));  // this+7252〔pTarget7252〕
      }
      else
      {
        *pDwArg3 = 3;
        fld_e19052 = *(this + 1905);  // 读 fld_e19052 = this+7620（速度/属性参数对象）
        fld_e18133 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813)) - *(uint32_t *)(fld_e19052 + 28);  // this+7252〔pTarget7252〕
      }
      *(this + 1918) = fld_e18133;  // this+7672〔f_1DF8〕
LABEL_55:
      fld_e18134 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
      v26 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) <= fld_e18134;  // 结果 = 虚调用 vt+120
      fld_e18135 = *(uint32_t *)*(this + 1813);  // this+7252〔pTarget7252〕
      if ( v26 )
      {
        v28 = (*(int (**)(void))(fld_e18135 + 120))();  // 调虚槽 +120：动画对象
        v29 = (double)(int)abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - v28);  // 结果 = 虚调用 vt+120
        if ( v29 >= (double)sub_4D8FE0(this) * 0.89999998 )  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
        {
          *pDwArg2 = 1;
          return;
        }
        if ( v29 <= (double)sub_4D8FE0(this) * 0.5 )  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
        {
          *pDwArg2 = 0;
          return;
        }
        goto LABEL_60;
      }
      v30 = (*(int (**)(void))(fld_e18135 + 120))();  // 调虚槽 +120：动画对象
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > v30 )  // 虚调用 vt+120
      {
        fld_e18136 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
        v32 = (double)(int)abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - fld_e18136);  // 结果 = 虚调用 vt+120
        if ( v32 < (double)sub_4D8FE0(this) * 0.89999998 )  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
        {
          if ( v32 > (double)sub_4D8FE0(this) * 0.5 )  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
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
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      pTarget7252_ = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( pTarget7252_ != 0 )  // fld_e18137=this+7252 pTarget7252
      {
        v34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget7252_ + 120))(pTarget7252_);  // 调虚槽 +120：动画对象
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > v34 )  // 虚调用 vt+120
        {
          fld_e18138 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));  // this+7252〔pTarget7252〕
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > fld_e18138 )  // 虚调用 vt+120
          {
            *pDwArg2 = 1;
            if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + 70 >= nArg4 - 40 )  // 虚调用 vt+120
              *(this + 1919) = nArg4 - 40;  // this+7676〔f_1DFC〕
            else
              *(this + 1919) = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + 70;  // 虚调用 vt+120
          }
        }
        else
        {
          *pDwArg2 = 0;
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 70 <= 40 )  // 虚调用 vt+120
            *(this + 1919) = 40;  // this+7676〔f_1DFC〕
          else
            *(this + 1919) = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 70;  // 虚调用 vt+120
        }
      }
      return;
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( rand() % 100 < 80 )  // 调 取伪随机数
      {
        pDwArg22 = pDwArg2;
        if ( (uint8_t)sub_4DA6B0(pDwArg2) == 0 )  // 调 滚动格判定
LABEL_48:
          sub_4DBDB0(pDwArg22, pDwArg3);  // 空间栅格重叠检测（碰撞/挤压分离轴；研究第 24/25 轮族）
      }
      return;
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_45;
      sub_4DBDB0(pDwArg2, pDwArg3);  // 空间栅格重叠检测（碰撞/挤压分离轴；研究第 24/25 轮族）
      return;
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      pThis = this;
      if ( *(this + 1813) == 0 )  // this+7252〔pTarget7252〕
        goto LABEL_32;
      *pDwArg2 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) <= *(this + 1919);  // 结果 = 虚调用 vt+120
      *pDwArg3 = ((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) <= *(this + 1918)) + 2;  // 结果 = 虚调用 vt+124
      fld_e1919 = *(this + 1919);  // this+7676〔f_1DFC〕
      if ( *(this + 1921) >= fld_e1919 )  // fld_e1919=this+7676 f_1DFC
        goto LABEL_36;
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > fld_e1919 )  // 虚调用 vt+120
        goto LABEL_37;
      if ( *(this + 1921) >= fld_e1919 )  // fld_e1919=this+7676 f_1DFC
      {
LABEL_36:
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < *(this + 1919) )  // 虚调用 vt+120
LABEL_37:
          *pDwArg2 = 4;
      }
      fld_e1918 = *(this + 1918);  // this+7672〔f_1DF8〕
      if ( *(this + 1920) >= fld_e1918 )  // fld_e1918=this+7672 f_1DF8
        goto LABEL_41;
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) > fld_e1918 )  // 虚调用 vt+124
        goto LABEL_42;
      if ( *(this + 1920) >= fld_e1918 )  // fld_e1918=this+7672 f_1DF8
      {
LABEL_41:
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) < *(this + 1918) )  // 虚调用 vt+124
LABEL_42:
          *pDwArg3 = 4;
      }
      if ( *pDwArg2 == 4 && *pDwArg3 == 4 )
        goto LABEL_45;
      return;
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
    case 17:  // case 17 = ENUM_CMDPACKET_SELECT_DUNGEON
      v76 = 0;
      v74 = 0;
      v64 = 0.0;
      v68 = 0.0;
      v60 = 0.0;
      v61 = 0.0;
      v40 = 0;
      while ( 1 )  // 无限循环
      {
        pObserverVecEnd = *(this + 29);  // 读 fld_e29 = this+116（观察者容器）
        v42 = *(uint32_t *)(pObserverVecEnd + 8);  // fld_e29=this+116 观察者 vector 尾针
        v73 = v40;
        v43 = v42 != 0 ? (*(uint32_t *)(pObserverVecEnd + 12) - v42) >> 2 : 0;  // fld_e29=this+116 观察者 vector 尾针
        if ( (int)v40 >= v43 )
          break;
        v44 = *(uint32_t *)(pObserverVecEnd + 8);  // fld_e29=this+116 观察者 vector 尾针
        if ( v44 != 0 && v40 < (*(uint32_t *)(pObserverVecEnd + 12) - v44) >> 2 )  // fld_e29=this+116 观察者 vector 尾针
          v45 = *(int **)(v44 + 4 * v40);
        else
          v45 = nullptr;
        if ( v45 == this )
          goto LABEL_124;
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v45 + 40))(v45, 529) == 0 )  // 虚调用 vt+40
          goto LABEL_124;
        v46 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 340))(this);  // 结果 = 虚调用 vt+340
        if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v45 + 340))(v45) != *v46 )  // 虚调用 vt+340
          goto LABEL_124;
        ++v76;
        v64 = (double)(*(int (/*thiscall*/ **)(int *))(*v45 + 120))(v45) + v64;  // 结果 = 虚调用 vt+120
        v68 = (double)(*(int (/*thiscall*/ **)(int *))(*v45 + 124))(v45) + v68;  // 结果 = 虚调用 vt+124
        fld_e1933 = (float)*(this + 1933);  // this+7732〔f_1E34〕
        v47 = (*(int (/*thiscall*/ **)(int *))(*v45 + 120))(v45);  // 结果 = 虚调用 vt+120
        v59 = (float)((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - v47);  // 结果 = 虚调用 vt+120
        v48 = (*(int (/*thiscall*/ **)(int *))(*v45 + 124))(v45);  // 结果 = 虚调用 vt+124
        v49 = (double)((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - v48);  // 结果 = 虚调用 vt+124
        v50 = 1.0;
        v51 = 2;
        for ( i = v59; ; i = i * i )
        {
          if ( (v51 & 1) != 0 )  // 若 v51 位 1 测试
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
          if ( (v53 & 1) != 0 )  // 若 v53 位 1 测试
            v54 = v54 * j;
          v53 >>= 1;
          if ( v53 == 0 )
            break;
        }
        if ( sqrt(v50 + v54) < fld_e1933 )  // 调 平方根
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
      v66 = v65 - (double)(*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
      v67 = v66 * 0.0099999998;
      v70 = (v69 - (double)(*(int (/*thiscall*/ **)(int *))(*this + 124))(this)) * 0.0099999998;  // 结果 = 虚调用 vt+124
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
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
      pTarget7252_2 = *(this + 1813);  // this+7252〔pTarget7252〕
      if ( pTarget7252_2 == 0 )  // fld_e18139=this+7252 pTarget7252
        goto LABEL_45;
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pTarget7252_2 + 120))(pTarget7252_2);  // 调虚槽 +120：动画对象
      *pDwArg2 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < v15;  // 结果 = 虚调用 vt+120
      *pDwArg3 = 4;
      return;
    case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
      *pDwArg2 = *(this + 1919) >= (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 结果 = 虚调用 vt+120
      *pDwArg3 = (*(this + 1918) >= (*(int (/*thiscall*/ **)(int *))(*this + 124))(this)) + 2;  // 结果 = 虚调用 vt+124
      if ( *(this + 30) != 0 )  // 判定 “+120 动画对象”
      {
        v7 = sub_42F220();  // 结果 = 取动画帧对象
        fld_e79 = sub_4918E0(v7, 0);  // 结果 = 动画盒四边界提取（研究 P29 族）
      }
      else
      {
        fld_e79 = *(this + 79) / 2;
      }
      v9 = fld_e79 + 10;
      if ( (int)abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - *(this + 1919)) < v9 )  // 虚调用 vt+120
        *pDwArg2 = 4;
      if ( (int)abs32((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - *(this + 1918)) < v9 )  // 虚调用 vt+124
        *pDwArg3 = 4;
      if ( *pDwArg2 == 4 && *pDwArg3 == 4
        || *(this + 1813) != 0  // this+7252〔pTarget7252〕
        && ((double)sub_4D8FE0(this) * 0.1 <= 70.0 ? (fld_e181310 = 70.0) : (fld_e181310 = (double)sub_4D8FE0(this) * 0.1),  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
            (double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 8))(this, *(this + 1813), 0) < fld_e181310) )  // 虚调用 vt+8
      {
        if ( (uint8_t)sub_4DAB60(12) != 0 || (uint8_t)sub_4DAB60(13) != 0 )  // 标签/条件集合成员判定
        {
          pAuraObject = *(this + 1814);  // 读 fld_e1814 = this+7256（光环状态）
          pThis = this;
          if ( pAuraObject == 0 )  // fld_e1814=this+7256 光环对象
            goto LABEL_32;
          if ( (uint8_t)sub_4DAB60(10) == 0 )  // 标签/条件集合成员判定
            goto LABEL_45;
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAuraObject + 120))(pAuraObject);  // 调虚槽 +120：动画对象
          pAuraObject_ = *(this + 1814);  // 读 fld_e18142 = this+7256（光环状态）
          *(this + 1919) = v12;  // this+7676〔f_1DFC〕
          *(this + 1918) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pAuraObject_ + 124))(pAuraObject_);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 1132))(this) == 0 )  // 虚调用 vt+1132
        {
          if ( (uint8_t)sub_4DAB60(10) != 0 )  // 标签/条件集合成员判定
          {
            (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 9);  // 虚调用 vt+1104
          }
          else if ( (uint8_t)sub_4DAB60(11) != 0 )  // 标签/条件集合成员判定
          {
            (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 10);  // 虚调用 vt+1104
          }
        }
      }
      return;
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      if ( rand() % 100 < 40 )  // 调 取伪随机数
      {
LABEL_126:
        if ( (uint8_t)sub_4DA6B0(pDwArg2) == 0 )  // 调 滚动格判定
          *pDwArg2 = rand() % 2;  // 调 取伪随机数
        *pDwArg3 = rand() % 2 + 2;  // 调 取伪随机数
      }
      return;
    case 19:  // case 19 = ENUM_CMDPACKET_DELETE_ITEM
      *pDwArg2 = v5;
      *pDwArg3 = v6;
      return;
    case 21:  // case 21 = ENUM_CMDPACKET_SORT_ITEM
      *pDwArg2 = sub_432E50(v5);  // 结果 = 关系码对调映射
      *pDwArg3 = sub_432E50(v6);  // 结果 = 关系码对调映射
      return;
    case 23:  // case 23 = ENUM_CMDPACKET_RENT_AVATAR
      (*(void (/*thiscall*/ **)(int *, int *, int *))(*this + 1232))(this, pDwArg2, pDwArg3);  // 虚调用 vt+1232
      return;
    case 24:  // case 24 = ENUM_CMDPACKET_EXTEND_AVATAR
      fld_e1812 = *(this + 1812);
      pThis = this;
      if ( fld_e1812 != 0 )
      {
        v37 = (double)(*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, fld_e1812, 0);  // 结果 = 虚调用 vt+8
        if ( (double)sub_4D8FE0(this) * 0.5 >= v37 )  // 调 取半径 → sub_591C90 计数<2 且 HP vt+736 ≥ vt+74
LABEL_45:
          (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);  // 虚调用 vt+1104
        else
          sub_4DC130(*(this + 1812), pDwArg2, pDwArg3);  // 单向拒绝测试（0x4DBDB0 的简化版，只判越界方向）
      }
      else
      {
LABEL_32:
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(pThis, 13);  // 虚调用 vt+1104
      }
      return;
    case 25:  // case 25 = ENUM_CMDPACKET_SELL_ITEM
      *pDwArg2 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) <= *(this + 1919);  // 结果 = 虚调用 vt+120
      *pDwArg3 = ((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) <= *(this + 1918)) + 2;  // 结果 = 虚调用 vt+124
      fld_e19192 = *(this + 1919);  // this+7676〔f_1DFC〕
      if ( *(this + 1921) >= fld_e19192 )  // fld_e19192=this+7676 f_1DFC
        goto LABEL_85;
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > fld_e19192 )  // 虚调用 vt+120
        goto LABEL_86;
      if ( *(this + 1921) >= fld_e19192 )  // fld_e19192=this+7676 f_1DFC
      {
LABEL_85:
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < *(this + 1919) )  // 虚调用 vt+120
LABEL_86:
          *pDwArg2 = 4;
      }
      fld_e19182 = *(this + 1918);  // this+7672〔f_1DF8〕
      if ( *(this + 1920) >= fld_e19182 )  // fld_e19182=this+7672 f_1DF8
        goto LABEL_90;
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) > fld_e19182 )  // 虚调用 vt+124
        goto LABEL_91;
      if ( *(this + 1920) >= fld_e19182 )  // fld_e19182=this+7672 f_1DF8
      {
LABEL_90:
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) < *(this + 1918) )  // 虚调用 vt+124
LABEL_91:
          *pDwArg3 = 4;
      }
      if ( *pDwArg2 == 4 && *pDwArg3 == 4 )
        (*(void (/*thiscall*/ **)(int *))(*this + 1076))(this);  // 虚调用 vt+1076
      return;
    default:
      return;
  }
}


// ------------------------------------------------------------
// 0x4DFF40 sub_4DFF40 —— 32 字节/条容器下标访问包装（零初始化临时块）
// memset 清 28 字节临时块后转发 0x4DEFF0(this, uArg2, 0, pBuf[0..6])。
// 【推断】取第 uArg2 条目（不存在则返回零块）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4DFF40(void *this, unsigned int uArg2)  // 32 字节/条容器下标访问包装（零初始化临时块）
{
  int pBuf[7]; // [esp+Ch] [ebp-1Ch] BYREF

  memset(pBuf, 0, sizeof(pBuf));  // 调 内存按字节填充
  return sub_4DEFF0((int)this, uArg2, 0, pBuf[0], pBuf[1], pBuf[2], pBuf[3], pBuf[4], pBuf[5], pBuf[6]);  // 32 字节/条容器随机访问写（vector operator[] 写侧）
}



// ------------------------------------------------------------
// 0x4DFF90 sub_4DFF90 —— 8 字节/条容器访问（this+4/+8/+12 三件套）
// 边界检查后取条目。【推断】std::vector<8字节T> 访问器；语义未定案【待验证】。
// ------------------------------------------------------------
void /*thiscall*/ sub_4DFF90(uint32_t *this, int nArg2)  // 实现：8 字节/条容器访问（this+4/+8/+12 三件套）
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi

  fld_e1 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 3;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) >> 3 )  // 判定 “+12 技能槽记录次字”
  {
    fld_e22 = *(this + 2);  // 读 fld_e22 = this+8（技能槽记录首字）
    sub_63A7C0(fld_e22, 1, nArg2);  // 强化结果公共件
    *(this + 2) = fld_e22 + 8;  // 写 this+8 = fld_e22 + 8（技能槽记录首字）
  }
  else
  {
    sub_4DEBD0((int)this, (uint32_t *)*(this + 2), 1u, nArg2);  // 容器重建/释放（a2 对象的 +4/+8/+C 字段族）
  }
}


