// ============================================================
// 【40JP逆向源代码工程】ui/http_item_info.cpp
// 模块: 0x57 区块 —— GenericHTTPClient(WinINet) + 物品/技能信息窗 + 掉落物 + 角色构造族
// 来源: work/dump_uilogin.txt  区块: 0x570000-0x580000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
// 函数数: 162
// ------------------------------------------------------------
// ★ HTTP 协议核心（本文件最重要的可读资产，0x575FF0-0x577330）:
//   GenericHTTPClient = WinINet 封装，三种请求模式：
//     1=GET            0x5760E0  HttpSendRequestA 无正文
//     2=POST-urlenc    0x5767E0  Content-Type: application/x-www-form-urlencoded
//     3=POST-multipart 0x576C40  boundary=--MULTI-PARTS-FORM-DATA-BOUNDARY
//   统一入口 0x576F10 Request(): 解析 URL(0x5763D0)→Connect(0x575FF0,
//   InternetOpenA+InternetConnectA+InternetAttemptConnect)→按模式发送→
//   ReadResponse(0x576180, InternetReadFile 0x400 块循环, 上限 100000 字节)→
//   HttpQueryInfoA(0x16=RAW_HEADERS_CRLF) 取原始响应头→关闭 3 级句柄。
//   应答解码链: 0x576640 取 this+20 应答体 → 0x577250 Base64 解码 +
//   按 dword 与密钥 XOR（调用方 ui_icon_perf.cpp 0x46EB70 线程：UA=
//   "MERONG(0.9/;p)"、密钥 dword_99FB68=2857617、目标 URL=全局 unk_98BA60）。
//   对象布局: +200020=hInternet、+200024=hConnect、+200028=hRequest、
//   +200032=LastError、+20=应答体(0x186A0)、+100020=响应头、+2..=字段表
//   （表项步进 1284 字节: name[256]+value[1024]+type@+1280）。
// ------------------------------------------------------------
// 其余内容: 技能/物品信息窗绘制链（0x570240-0x575FF0）、CNPathGate、
//   CNRDStackable/CNRDItemObject 掉落物（Item/FieldImage.img、ITEM_DROP、
//   GOLD_DROP1/2 金币）、IRDCharacter 四职业构造族（0x579020-0x579F90）、
//   CBIniFile INI 解析与字符串辅助（0x57A0A0-0x57A8F0）。
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】社区窗口析构与技能信息窗入口（0x570240-0x5704A0）
// CNRDCommunityWindow__vmt0 = 析构（释放好友/公会列表）；
// CNRDSkillInfoWindow vmt10/vmt0 = 打开状态切换与构造。
// ============================================================
// ------------------------------------------------------------
// 0x570240 CNRDCommunityWindow__vmt0 —— CNRDCommunityWindow 析构：418DD0 取控件 + 56FB50/56F890 释放好友/公会列表
// ------------------------------------------------------------
void /*thiscall*/ CNRDCommunityWindow__vmt0(int *this, int pArg2)  // 实现：CNRDCommunityWindow 析构：418DD0 取控件 + 56FB50/56F890 释放好友/公会列表
{
  int v4; // ebx
  int pObj; // eax
  int nPanelTab; // eax  | +0x002C → 面板页签（CNRDCommunityWindow；va=0056E0D0）
  int nPanelTab_; // eax  | +0x002C → 面板页签（CNRDCommunityWindow；va=0056E0D0）
  int v8; // [esp+10h] [ebp+8h]

  IRDPopupWindow__vmt0(this, pArg2);  // 调 IRDPopupWindow__vmt0 构造
  if ( pArg2 == *(this + 2) )  // 若 pArg2 == *(this + 2)
  {
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v8 = *(uint32_t *)(pArg2 + 24);  // v8 = pArg2+24
    pObj = sub_418DD0(165);  // pObj = 调 sub_418DD0 返回值
    if ( pObj != 0 )  // 若 pObj 非 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v4 + 6, v8 + 6, dword_79C0B0);  // 调虚槽 +152：效果通道 3
    nPanelTab = sub_418DD0(*(this + 11) + 270);  // this+44〔nPanelTab〕
    if ( nPanelTab != 0 )  // 若 fld_e11 非 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)nPanelTab + 152))(nPanelTab, v4 + 2, v8 + 33, dword_79C0B0);  // 调虚槽 +152：效果通道 3
    nPanelTab_ = *(this + 11);  // this+44〔nPanelTab〕
    if ( nPanelTab_ != 0 )  // 若 fld_e112 非 0
    {
      if ( nPanelTab_ == 1 )  // 若 fld_e112 == 1
        sub_56FB50(this, pArg2);  // CNRDCommunityWindow 社区窗构造（291 行：429830/429900/4BF0F0/56F660/418DD0/40FC80/4BE3…
    }
    else  // 否则分支
    {
      sub_56F890(this, pArg2);  // 社区好友页装配（56F460/418DD0/69C690/56E120/479240/42B340/4B0EC0/56E000/491530/491630）
    }
  }
}



// ------------------------------------------------------------
// 0x5702F0 sub_5702F0 —— 社区/技能窗公共辅助（70 行：控件遍历与状态复位）
// ------------------------------------------------------------
int /*thiscall*/ sub_5702F0(int this)  // 实现：社区/技能窗公共辅助（70 行：控件遍历与状态复位）
{
  int result; // eax

  *(uint32_t *)(this + 80) = 12;  // this+80 = 12
  *(uint32_t *)(this + 88) = 1600;  // this+88 = 1600
  *(uint8_t *)(this + 60) = 0;  // this+60 = 0
  *(uint8_t *)(this + 61) = 0;  // this+61〔bReadyFlagA〕
  *(uint8_t *)(this + 62) = 0;  // this+62〔bReadyFlagB〕
  *(uint8_t *)(this + 63) = 0;  // this+63 = 0
  *(uint32_t *)(this + 72) = 0;  // this+72 = 0
  *(uint32_t *)(this + 84) = 0;  // this+84 = 0
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 96) = 0;  // this+96 = 0
  *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  *(uint32_t *)(this + 104) = 0;  // this+104 = 0
  *(uint32_t *)(this + 108) = 0;  // this+108 = 0
  *(uint32_t *)(this + 76) = 6;  // this+76〔pBtnActionE〕
  *(uint32_t *)(this + 108) = dword_99FCCC;  // this+108 = dword_99FCCC
  *(uint32_t *)(this + 88) = 170;  // this+88 = 170
  *(uint32_t *)(this + 72) = 0;  // this+72 = 0
  *(uint32_t *)(this + 64) = -16777216;  // this+64 = -16777216
  *(uint8_t *)(this + 62) = 1;  // this+62〔bReadyFlagB〕
  *(uint32_t *)(this + 128) = 6;  // this+128 = 6
  *(uint8_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
  *(uint8_t *)(this + 113) = 0;  // this+113 = 0
  *(uint8_t *)(this + 114) = 0;  // this+114 = 0
  *(uint8_t *)(this + 115) = 0;  // this+115 = 0
  *(uint32_t *)(this + 124) = 0;  // this+124 = 0
  *(uint32_t *)(this + 132) = 12;  // this+132 = 12
  *(uint32_t *)(this + 136) = 0;  // this+136 = 0
  *(uint32_t *)(this + 140) = 1600;  // this+140 = 1600
  *(uint32_t *)(this + 144) = 0;  // this+144 = 0
  *(uint32_t *)(this + 148) = 0;  // this+148 = 0
  *(uint32_t *)(this + 152) = 0;  // this+152 = 0
  *(uint32_t *)(this + 156) = 0;  // this+156 = 0
  *(uint32_t *)(this + 160) = 0;  // this+160 = 0
  *(uint32_t *)(this + 160) = dword_99FCCC;  // this+160 = dword_99FCCC
  *(uint8_t *)(this + 114) = 1;  // this+114 = 1
  *(uint32_t *)(this + 140) = 170;  // this+140 = 170
  *(uint32_t *)(this + 124) = 2;  // this+124 = 2
  *(uint32_t *)(this + 116) = -16777216;  // this+116 = -16777216
  *(uint8_t *)(this + 164) = 0;  // this+164 = 0
  *(uint8_t *)(this + 165) = 0;  // this+165 = 0
  *(uint8_t *)(this + 166) = 0;  // this+166 = 0
  *(uint8_t *)(this + 167) = 0;  // this+167 = 0
  *(uint32_t *)(this + 176) = 0;  // this+176 = 0
  *(uint32_t *)(this + 180) = 6;  // this+180 = 6
  *(uint32_t *)(this + 184) = 12;  // this+184 = 12
  *(uint32_t *)(this + 188) = 0;  // this+188 = 0
  *(uint32_t *)(this + 192) = 1600;  // this+192 = 1600
  *(uint32_t *)(this + 196) = 0;  // this+196 = 0
  *(uint32_t *)(this + 200) = 0;  // this+200 = 0
  *(uint32_t *)(this + 204) = 0;  // this+204 = 0
  *(uint32_t *)(this + 208) = 0;  // this+208 = 0
  *(uint32_t *)(this + 212) = 0;  // this+212 = 0
  result = dword_99FCCC;
  *(uint32_t *)(this + 212) = dword_99FCCC;  // this+212 = dword_99FCCC
  *(uint8_t *)(this + 166) = 1;  // this+166 = 1
  *(uint32_t *)(this + 192) = 170;  // this+192 = 170
  *(uint32_t *)(this + 176) = 1;  // this+176 = 1
  *(uint32_t *)(this + 168) = -16777216;  // this+168 = -16777216
  return result;
}



// ------------------------------------------------------------
// 0x570450 CNRDSkillInfoWindow__vmt10 —— CNRDSkillInfoWindow vmt10：打开时状态切换（44ABE0/44E850）
// ------------------------------------------------------------
int /*thiscall*/ CNRDSkillInfoWindow__vmt10(uint32_t *this)  // 实现：CNRDSkillInfoWindow vmt10：打开时状态切换（44ABE0/44E850）
{
  int result; // eax

  dword_9B88CC = 0;
  result = *(this + 4);  // result = this+4
  *(uint32_t *)(*(uint32_t *)(result + 2500) + 60) = 255;
  return result;
}



// ------------------------------------------------------------
// 0x570470 sub_570470 —— 技能信息窗小辅助（13 行）
// ------------------------------------------------------------
bool /*thiscall*/ sub_570470(uint32_t *this)  // 实现：技能信息窗小辅助（13 行）
{
  int pVecEnd_4; // eax

  pVecEnd_4 = *(this + 1);  // fld_e1 = this+1
  return pVecEnd_4 == 0 || (*(this + 2) - pVecEnd_4) / 12 == 0;
}



// ------------------------------------------------------------
// 0x5704A0 CNRDSkillInfoWindow__vmt0 —— CNRDSkillInfoWindow vmt0：主构造（59 行）
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDSkillInfoWindow__vmt0(int *this, int nArg2)  // 实现：CNRDSkillInfoWindow vmt0：主构造（59 行）
{
  unsigned int result; // eax
  LONG v4; // ecx
  LONG v5; // eax
  int pHostCtrl; // eax
  int v7; // edi
  uint32_t *fld_e12; // eax
  uint32_t *v9; // edx
  int v10; // [esp+8h] [ebp-8h]
  int v11; // [esp+Ch] [ebp-4h]
  unsigned int i; // [esp+18h] [ebp+8h]

  IRDPopupWindow__vmt0(this, nArg2);  // 调 IRDPopupWindow__vmt0 构造
  result = *(this + 2);  // result = this+2
  if ( nArg2 == result )  // 若 nArg2 == result
  {
    v4 = *(uint32_t *)(result + 20);  // v4 = result+20
    v5 = *(uint32_t *)(result + 24);  // v5 = result+24
    if ( v4 < pt.x && v5 < pt.y && v4 + *(this + 9) > pt.x && v5 + *(this + 10) > pt.y )  // 若 v4 < pt 与/或 v5 < pt
      *(uint32_t *)(*(uint32_t *)(*(this + 4) + 2500) + 60) = 120;
    pHostCtrl = *(this + 2);  // fld_e2 = this+2
    v7 = 0;
    v10 = *(uint32_t *)(pHostCtrl + 20) + 7;
    v11 = *(uint32_t *)(pHostCtrl + 24) + 7;
    for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
    {
      result = *(this + 12);  // result = this+12
      if ( result == 0 )  // 若 result 为 0
        break;  // 跳出循环/分支
      result = (int)(*(this + 13) - result) / 40;
      if ( i >= result )  // 若 i >= result
        break;  // 跳出循环/分支
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B0 + 72))(  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
        dword_79C0B0,  // 默认字体/绘制资源
        *(uint32_t *)(v7 + *(this + 12) + 4));
      fld_e12 = (uint32_t *)(*(this + 12) + v7);
      if ( fld_e12[9] < 0x10u )  // 若 fld_e12[9] < 0x10u
        v9 = fld_e12 + 4;
      else  // 否则分支
        v9 = (uint32_t *)fld_e12[4];
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        dword_79C0B0,  // 默认字体/绘制资源
        v10,
        v11 + 13 * *fld_e12,
        fld_e12[2],
        v9);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
      v7 += 40;
    }
  }
  return result;
}



// ============================================================
// 【分区 2】技能信息窗文本行组装辅助（0x5705A0-0x5707B0）
// 4014D0=std::string 赋值；5705A0/570610/570660/570710/5707B0 组成
// "标题/数值行"逐行拼装链，供 0x5707E0 主文本构建调用。
// ============================================================
// ------------------------------------------------------------
// 0x5705A0 sub_5705A0 —— 文本行组装起点：4014D0 字符串赋值（标题行）
// ------------------------------------------------------------
int /*cdecl*/ sub_5705A0(int pArg1, uint32_t *pArg2)  // 实现：文本行组装起点：4014D0 字符串赋值（标题行）
{
  int result; // eax

  result = pArg1;
  if ( pArg1 != 0 )  // 若 pArg1 非 0
  {
    *(uint32_t *)pArg1 = *pArg2;
    *(uint32_t *)(pArg1 + 4) = pArg2[1];  // pArg1+4 = pArg2[1]
    *(uint32_t *)(pArg1 + 8) = pArg2[2];  // pArg1+8 = pArg2[2]
    *(uint32_t *)(pArg1 + 36) = 15;  // pArg1+36 = 15
    *(uint32_t *)(pArg1 + 32) = 0;  // pArg1+32 = 0
    *(uint8_t *)(pArg1 + 16) = 0;  // pArg1+16 = 0
    return sub_4014D0((std::_String_base *)(pArg1 + 12), pArg2 + 3, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  }
  return result;
}



// ------------------------------------------------------------
// 0x570610 sub_570610 —— 文本行组装：4014D0 拼接（数值行）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_570610(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)  // 实现：文本行组装：4014D0 拼接（数值行）
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 10 )  // 遍历循环
  {
    *i = *pArg3;  // *i 写入 *pArg3
    i[1] = pArg3[1];  // i[1] = 取 pArg3[1]
    i[2] = pArg3[2];  // i[2] = 取 pArg3[2]
    sub_4014D0((std::_String_base *)(i + 3), pArg3 + 3, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    result = uArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x570660 sub_570660 —— 文本行组装中层（转发 5705A0）
// ------------------------------------------------------------
int /*cdecl*/ sub_570660(uint32_t *uArg1, uint32_t *uArg2, int nArg3)  // 实现：文本行组装中层（转发 5705A0）
{
  int nArg32; // edi
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v6[7] = 0;
  while ( uArg1 != uArg2 )  // 条件循环
  {
    sub_5705A0(nArg32, uArg1);  // 文本行组装起点：4014D0 字符串赋值（标题行）
    nArg32 += 40;
    uArg1 += 10;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x570710 sub_570710 —— 文本行组装中层 2（24 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_570710(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：文本行组装中层 2（24 行）
{
  int nArg12; // esi
  int result; // eax
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  nArg12 = nArg1;
  v6[4] = v6;
  v6[3] = nArg1;
  v6[7] = 0;
  while ( nArg2 != 0 )  // 条件循环
  {
    result = sub_5705A0(nArg12, uArg3);  // 文本行组装起点：4014D0 字符串赋值（标题行）
    --nArg2;  // 自减nArg2
    nArg12 += 40;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5707B0 sub_5707B0 —— 转发 570710（尾调用桩）
// ------------------------------------------------------------
int /*stdcall*/ sub_5707B0(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：转发 570710（尾调用桩）
{
  sub_570710(nArg1, nArg2, uArg3);  // 文本行组装中层 2（24 行）
  return nArg1 + 40 * nArg2;
}



// ============================================================
// 【分区 3】技能信息窗绘制链（0x5707E0-0x571AF0）
// 文本构建主函数 0x5707E0（136 行）；部件构建 0x570CB0（184 行）；
// 打开/绘制主函数 CNRDSkillInfoWindow__vmtC 在 0x570FD0（431 行）。
// ============================================================
// ------------------------------------------------------------
// 0x5707E0 sub_5707E0 —— 技能信息窗文本构建主函数：558090 分隔符 + 572550/5721D0 属性行 + 55A010 尾串
// ------------------------------------------------------------
void /*thiscall*/ sub_5707E0(int *this, int pArg2, unsigned int uArg3, int *pDwArg4)  // 实现：技能信息窗文本构建主函数：558090 分隔符 + 572550/5721D0 属性行 + 55A010 尾串
{
  int v4; // edx
  int v6; // ecx
  int pVecEnd_14; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v12; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e28; // ecx
  int fld_e13; // eax
  unsigned int v17; // edi
  void *fld_e14; // eax
  int fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-6Ch]
  int fld_e25; // [esp-Ch] [ebp-60h]
  unsigned int fld_e24; // [esp-8h] [ebp-5Ch]
  int v25; // [esp+0h] [ebp-54h] BYREF
  void *Block; // [esp+Ch] [ebp-48h]
  int *pThis; // [esp+10h] [ebp-44h]
  char *pMem2; // [esp+14h] [ebp-40h]
  uint32_t v29[3]; // [esp+18h] [ebp-3Ch] BYREF
  char v30[4]; // [esp+24h] [ebp-30h] BYREF
  void *v31; // [esp+28h] [ebp-2Ch]
  int v32; // [esp+38h] [ebp-1Ch]
  unsigned int v33; // [esp+3Ch] [ebp-18h]
  int dword_796E502; // [esp+40h] [ebp-14h]
  int *v35; // [esp+44h] [ebp-10h]
  int v36; // [esp+50h] [ebp-4h]
  int v37; // [esp+5Ch] [ebp+8h]
  int v38; // [esp+60h] [ebp+Ch]
  int fld_e232; // [esp+64h] [ebp+10h]

  dword_796E502 = dword_796E50;
  v4 = pDwArg4[1];  // v4 = 取 pDwArg4[1]
  v6 = *pDwArg4;
  v35 = &v25;
  v29[0] = v6;
  v29[2] = pDwArg4[2];  // v29[2] = 取 pDwArg4[2]
  pThis = this;
  v29[1] = v4;
  v33 = 15;
  v32 = 0;
  LOBYTE(v31) = 0;
  sub_4014D0((std::_String_base *)v30, pDwArg4 + 3, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  pVecEnd_14 = *(this + 1);  // fld_e1 = this+1
  v36 = 0;
  if ( pVecEnd_14 != 0 )  // 若 fld_e1 非 0
    fld_e3 = (*(this + 3) - pVecEnd_14) / 40;
  else  // 否则分支
    fld_e3 = 0;
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( pVecEnd_14 != 0 )  // 若 fld_e1 非 0
      fld_e2 = (*(this + 2) - pVecEnd_14) / 40;
    else  // 否则分支
      fld_e2 = 0;
    if ( 107374182 - fld_e2 < uArg3 )  // 若 107374182 - fld_e2 < uArg3
      sub_558090(this);  // 信息窗共用）
    if ( pVecEnd_14 != 0 )  // 若 fld_e1 非 0
      fld_e22 = (*(this + 2) - pVecEnd_14) / 40;
    else  // 否则分支
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )  // 若 fld_e3 >= uArg3 + fld_e22
    {
      fld_e23 = *(this + 2);  // fld_e23 = this+2
      fld_e232 = fld_e23;
      if ( (fld_e23 - pArg2) / 40 >= uArg3 )  // 若 (fld_e23 - pArg2) / 40 >= uArg3
      {
        v37 = fld_e23 - 40 * uArg3;
        *(this + 2) = sub_570660(v37, fld_e23, fld_e23);  // 文本行组装中层（转发 5705A0）
        sub_572550(pArg2, v37, fld_e232);  // 转发 572400
        sub_570610(pArg2, pArg2 + 40 * uArg3, v29);  // 文本行组装：4014D0 拼接（数值行）
      }
      else  // 否则分支
      {
        sub_570660(pArg2, fld_e23, pArg2 + 40 * uArg3);  // 文本行组装中层（转发 5705A0）
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 40;
        fld_e25 = *(this + 2);  // fld_e25 = this+2
        LOBYTE(v36) = 3;
        sub_5707B0(fld_e25, fld_e24, v29);  // 转发 570710（尾调用桩）
        fld_e26 = 40 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8 = fld_e26
        v36 = 0;
        sub_570610(pArg2, fld_e26 - 40 * uArg3, v29);  // 文本行组装：4014D0 拼接（数值行）
      }
    }
    else  // 否则分支
    {
      if ( 107374182 - (fld_e3 >> 1) >= fld_e3 )  // 若 107374182 - (fld_e3 >> 1) >= fld_e3
        v12 = (fld_e3 >> 1) + fld_e3;
      else  // 否则分支
        v12 = 0;
      if ( pVecEnd_14 != 0 )  // 若 fld_e1 非 0
        fld_e27 = (*(this + 2) - pVecEnd_14) / 40;
      else  // 否则分支
        fld_e27 = 0;
      if ( v12 < uArg3 + fld_e27 )  // 若 v12 < uArg3 + fld_e27
        v12 = uArg3 + sub_5721D0(this);  // 物品信息窗小辅助（15 行）
      v38 = 40 * v12;
      pMem = (char *)operator new(40 * v12);
      fld_e12 = *(this + 1);  // fld_e12 = this+1
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v36) = 1;
      pMem2 = (char *)sub_570660(fld_e12, pArg2, pMem);  // 文本行组装中层（转发 5705A0）
      sub_570710(pMem2, uArg3, v29);  // 文本行组装中层 2（24 行）
      fld_e28 = *(this + 2);  // fld_e28 = this+2
      pMem2 += 40 * uArg3;
      sub_570660(pArg2, fld_e28, pMem2);  // 文本行组装中层（转发 5705A0）
      fld_e13 = *(this + 1);  // fld_e13 = this+1
      if ( fld_e13 != 0 )  // 若 fld_e13 非 0
        fld_e13 = (*(this + 2) - fld_e13) / 40;
      v17 = fld_e13 + uArg3;
      fld_e14 = (void *)*(this + 1);
      if ( fld_e14 != nullptr )  // 若 fld_e14 有效（非空）
      {
        sub_55A010(fld_e14, *(this + 2));  // 信息窗文本（5014C0）
        j__free((void *)*(this + 1));  // 调 j__free
      }
      *(this + 3) = (int)&pMem[v38];  // this+12 = (int)&pMem[v38]
      *(this + 2) = (int)&pMem[40 * v17];  // this+8 = (int)&pMem[40 * v17]
      *(this + 1) = (int)pMem;  // this+4 = (int)pMem
    }
  }
  if ( v33 >= 0x10 )  // 若 v33 >= 0x10
    j__free(v31);  // 调 j__free
}


// ------------------------------------------------------------
// 0x570B10 sub_570B10 —— 绘制链中层（转发 5707E0 文本构建）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_570B10(int *this, uint32_t *uArg2, char *pszArg3, int *pDwArg4)  // 实现：绘制链中层（转发 5707E0 文本构建）
{
  int pVecEnd_6; // esi
  int v6; // esi

  pVecEnd_6 = *(this + 1);  // fld_e1 = this+1
  if ( pVecEnd_6 != 0 && (*(this + 2) - pVecEnd_6) / 40 != 0 )  // 若 pVecEnd_6 != 0
    v6 = (int)&pszArg3[-pVecEnd_6] / 40;
  else  // 否则分支
    v6 = 0;
  sub_5707E0(this, pszArg3, 1u, pDwArg4);  // 技能信息窗文本构建主函数：558090 分隔符 + 572550/5721D0 属性行 + 55A010 尾串
  *uArg2 = *(this + 1) + 40 * v6;  // *uArg2 写入 *(this + 1) + 40 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x570B80 sub_570B80 —— 绘制链中层 2（570B10 + 570710）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_570B80(int this, int *pDwArg2)  // 实现：绘制链中层 2（570B10 + 570710）
{
  int pVecEnd_8; // edi
  unsigned int fld_8; // ecx
  int fld_82; // edi
  uint32_t *result; // eax

  pVecEnd_8 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  if ( pVecEnd_8 != 0 )  // 若 fld_4 非 0
    fld_8 = (*(uint32_t *)(this + 8) - pVecEnd_8) / 40;
  else  // 否则分支
    fld_8 = 0;
  if ( pVecEnd_8 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - pVecEnd_8) / 40 )  // 若 pVecEnd_8 == 0
    return sub_570B10((int *)this, &pDwArg2, *(char **)(this + 8), pDwArg2);  // 绘制链中层（转发 5707E0 文本构建）
  fld_82 = *(uint32_t *)(this + 8);  // fld_82 = 读 this+8
  result = (uint32_t *)sub_570710(fld_82, 1, pDwArg2);  // 文本行组装中层 2（24 行）
  *(uint32_t *)(this + 8) = fld_82 + 40;  // this+8 = fld_82 + 40
  return result;
}



// ------------------------------------------------------------
// 0x570C10 sub_570C10 —— 绘制链中层 3（4015C0 字符串 + 570B80）
// ------------------------------------------------------------
void /*thiscall*/ sub_570C10(void *this, int nArg2, void *Src, int nArg4, int nArg5)  // 实现：绘制链中层 3（4015C0 字符串 + 570B80）
{
  int v6[3]; // [esp+Ch] [ebp-38h] BYREF
  void *Block; // [esp+1Ch] [ebp-28h]
  int v8; // [esp+2Ch] [ebp-18h]
  unsigned int v9; // [esp+30h] [ebp-14h]
  int dword_796E502; // [esp+34h] [ebp-10h]
  int v11; // [esp+40h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  v6[0] = nArg2;
  v6[2] = nArg5;
  v11 = 0;
  v6[1] = nArg4;
  sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  sub_570B80((int)this + 44, v6);  // 绘制链中层 2（570B10 + 570710）
  if ( v9 >= 0x10 )  // 若 v9 >= 0x10
    j__free(Block);  // 调 j__free
}



// ------------------------------------------------------------
// 0x570CB0 sub_570CB0 —— 技能信息窗部件构建（184 行：416C40/406D00/4164C0 文本块装配）
// ------------------------------------------------------------
int /*cdecl*/ sub_570CB0(const char *pArg1, int nArg2, int nArg3)  // 实现：技能信息窗部件构建（184 行：416C40/406D00/4164C0 文本块装配）
{
  const char *pArg12; // ebx
  int v4; // esi
  int v5; // edi
  char v6; // al
  int16_t v7; // cx
  void **Block4; // eax
  char *v9; // eax
  void **Block3; // ecx
  void **Block2; // eax
  void **Block5; // eax
  char *v14; // eax
  void **Block6; // ecx
  uint8_t v16[4]; // [esp+8h] [ebp-40h] BYREF
  int nLen; // [esp+Ch] [ebp-3Ch]
  int v18; // [esp+10h] [ebp-38h]
  int16_t v19; // [esp+14h] [ebp-34h] BYREF
  char v20; // [esp+16h] [ebp-32h]
  int v21; // [esp+18h] [ebp-30h]
  uint8_t v22[4]; // [esp+1Ch] [ebp-2Ch] BYREF
  void *Block[4]; // [esp+20h] [ebp-28h] BYREF
  int v24; // [esp+30h] [ebp-18h]
  unsigned int v25; // [esp+34h] [ebp-14h]
  int dword_796E502; // [esp+38h] [ebp-10h]
  int v27; // [esp+44h] [ebp-4h]

  pArg12 = pArg1;
  v4 = 0;
  dword_796E502 = dword_796E50;
  if ( pArg1 == nullptr )  // 若 pArg1 为空
    return 0;
  --nArg2;  // 自减nArg2
  v25 = 15;
  v24 = 0;
  LOBYTE(Block[0]) = 0;
  v27 = 0;
  v21 = 1;
  nLen = strlen(pArg1);  // nLen = 调 strlen
  v5 = 0;
  if ( nLen > 0 )  // 若 nLen > 0
  {
    v18 = 1;
    do  // do-while 循环体起点
    {
      v6 = pArg12[v5];  // v6 = 取 pArg12[v5]
      if ( v6 < 0  // 若 v6 < 0
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
        v7 = *(uint16_t *)&pArg12[v5];
        v20 = 0;
        v19 = v7;
        sub_4022F0((std::_String_base *)v22, &v19, strlen((const char *)&v19));  // std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
        ++v5;  // 自增v5
        ++v18;  // 自增v18
        ++v4;  // 自增v4
      }
      else  // 否则分支
      {
        if ( v6 == 10 || v18 < nLen && (v6 == 13 && pArg12[v5 + 1] == 10 || v6 == 92 && pArg12[v5 + 1] == 110) )  // 若 v6 == 10 与/或 v18 < nLen 与/或 v6 == 13
        {
          if ( nArg3 != 0 )  // 若 nArg3 非 0
          {
            sub_5724C0();  // 信息窗共用
            sub_416C40(v22);  // 尾插一条 28B 记录（满则走插入路径）
            Block2 = (void **)Block[0];
            if ( v25 < 0x10 )  // 若 v25 < 0x10
              Block2 = Block;
            v9 = (char *)Block2 + v24;
            Block3 = (void **)Block[0];
            if ( v25 < 0x10 )  // 若 v25 < 0x10
              Block3 = Block;
LABEL_70:  // 标签 LABEL_70（跳转合流点）
            sub_406D00(v16, Block3, v9);  // std::string 中段擦除（·sub_401230 erase，pos 与 n 由指针差换算）
            pArg12 = pArg1;
          }
LABEL_71:  // 标签 LABEL_71（跳转合流点）
          v4 = 0;
          ++v21;  // 自增v21
          goto LABEL_72;  // 跳转 LABEL_72
        }
        sub_4164C0((std::_String_base *)v22, 1, v6);  // 【string/vector 容器工具】
      }
      if ( ++v4 >= nArg2 )  // 若 ++v4 >= nArg2
      {
        if ( nArg3 != 0 )  // 若 nArg3 非 0
        {
          sub_5724C0();  // 信息窗共用
          sub_416C40(v22);  // 尾插一条 28B 记录（满则走插入路径）
          Block4 = (void **)Block[0];
          if ( v25 < 0x10 )  // 若 v25 < 0x10
            Block4 = Block;
          v9 = (char *)Block4 + v24;
          Block3 = (void **)Block[0];
          if ( v25 < 0x10 )  // 若 v25 < 0x10
            Block3 = Block;
          goto LABEL_70;  // 跳转 LABEL_70
        }
        goto LABEL_71;  // 跳转 LABEL_71
      }
LABEL_72:  // 标签 LABEL_72（跳转合流点）
      ++v5;  // 自增v5
      ++v18;  // 自增v18
    }
    while ( v5 < nLen );  // 条件循环
  }
  if ( nLen == 0 )  // 若 nLen 为 0
  {
    if ( v25 >= 0x10 )  // 若 v25 >= 0x10
      j__free(Block[0]);  // 调 j__free
    return 0;
  }
  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    if ( v24 != 0 )  // 若 v24 非 0
    {
      sub_416C40(v22);  // 尾插一条 28B 记录（满则走插入路径）
      Block5 = (void **)Block[0];
      if ( v25 < 0x10 )  // 若 v25 < 0x10
        Block5 = Block;
      v14 = (char *)Block5 + v24;
      Block6 = (void **)Block[0];
      if ( v25 < 0x10 )  // 若 v25 < 0x10
        Block6 = Block;
      sub_406D00(&pArg1, Block6, v14);  // std::string 中段擦除（·sub_401230 erase，pos 与 n 由指针差换算）
    }
    else  // 否则分支
    {
      --v21;  // 自减v21
    }
  }
  if ( v25 >= 0x10 )  // 若 v25 >= 0x10
    j__free(Block[0]);  // 调 j__free
  return v21;
}


// ------------------------------------------------------------
// 0x570FD0 CNRDSkillInfoWindow__vmtC —— CNRDSkillInfoWindow__vmtC 打开/绘制主函数（431 行：47DCC0 技能查询 + 570C10/570CB0 分支 + 4B1C40/47EA80/4C0360 状态）
// ------------------------------------------------------------
char /*thiscall*/ sub_570FD0(char *this, int nArg2, void *pArg3)  // 【CNRDSkillInfoWindow__vmtC】
{
  int v5; // ebx
  int v6; // esi
  const char *v7; // eax
  const CHAR *v8; // eax
  int pThis_3C; // eax
  CHAR *v10; // eax
  int v11; // esi
  const CHAR *v12; // eax
  int pThis_3C2; // eax
  const char *v14; // eax
  int v15; // esi
  const char *v16; // eax
  int pThis_3C3; // eax
  const char *v18; // eax
  int pThis_3C4; // eax
  int v20; // eax
  int v21; // esi
  const char *v22; // eax
  int v23; // eax
  CHAR *v24; // eax
  void *v25; // edx
  int v26; // eax
  int pObj; // eax
  const char *v28; // eax
  int pThis_3C6; // eax
  void *v30; // edx
  int v31; // eax
  int v32; // ecx
  int v33; // eax
  const char *v34; // eax
  int pThis_3C7; // eax
  bool v36; // zf
  int v37; // eax
  void *v38; // eax
  void *v39; // eax
  int pThis_3C8; // eax
  int v41; // esi
  void *v42; // eax
  int v43; // eax
  void *v44; // eax
  int v45; // eax
  int pThis_3C9; // eax
  int v47; // eax
  const CHAR *v48; // eax
  int v49; // eax
  void *v50; // eax
  int v51; // eax
  int pThis_3C10; // eax
  void *Block2; // ebx
  int v54; // eax
  int v55; // esi
  void *v56; // eax
  int pThis_1B; // eax
  uint32_t *v58; // edx
  int pThis_2; // eax
  int pThis_38; // eax
  uint32_t *v61; // edx
  int v62; // [esp+0h] [ebp-248h]
  const char *v63; // [esp+4h] [ebp-244h]
  int pThis_3C5; // [esp+4h] [ebp-244h]
  int v65; // [esp+4h] [ebp-244h]
  const CHAR *v66; // [esp+4h] [ebp-244h]
  int pThis_A4; // [esp+4h] [ebp-244h]
  int v68; // [esp+8h] [ebp-240h]
  int v69; // [esp+8h] [ebp-240h]
  int v70; // [esp+8h] [ebp-240h]
  int v71; // [esp+8h] [ebp-240h]
  int v72; // [esp+18h] [ebp-230h]
  unsigned int v73; // [esp+18h] [ebp-230h]
  int v74; // [esp+18h] [ebp-230h]
  char v75[4]; // [esp+1Ch] [ebp-22Ch] BYREF
  void *Block; // [esp+20h] [ebp-228h]
  int v77; // [esp+24h] [ebp-224h]
  int v78; // [esp+28h] [ebp-220h]
  int v79; // [esp+2Ch] [ebp-21Ch]
  int v80; // [esp+30h] [ebp-218h]
  void *Src; // [esp+34h] [ebp-214h]
  char Buffer[512]; // [esp+38h] [ebp-210h] BYREF
  int dword_796E502; // [esp+238h] [ebp-10h]
  int v84; // [esp+244h] [ebp-4h]
  int pThis_3C11; // [esp+250h] [ebp+8h]
  char *v86; // [esp+254h] [ebp+Ch]
  char *v87; // [esp+254h] [ebp+Ch]

  dword_796E502 = dword_796E50;
  dword_9B88CC = nArg2;
  if ( nArg2 == 0 )  // 若 nArg2 为 0
    return 0;
  dword_795374 = (int)pArg3;
  if ( dword_8F7C04 == 0 )  // 本地玩家对象
    return 0;
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 28))(this, 1);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
  sub_55A050(this + 44);  // 信息窗文本 2（5014C0）
  v79 = dword_9B88CC + 4;
  if ( dword_795374 == 3 || dword_795374 == 2 )  // 若 dword_795374 == 3 与/或 dword_795374 == 2
    v5 = sub_41A5E0(dword_9B88CC + 496) + 1;  // crypt4byte 解密校验（·0x41A590 逆运算）
  else  // 否则分支
    v5 = sub_41A5E0(dword_9B88CC + 510);  // crypt4byte 解密校验（·0x41A590 逆运算）
  if ( v5 <= sub_47DCC0(dword_9B88CC) && v5 != 0 )  // 若 v5 <= sub_47DCC0 与/或 v5 != 0
  {
    pThis_3C11 = 170;
    Src = (void *)-3618616;  // Src = 转换(-3618616)
    if ( dword_795374 != 3 && dword_795374 != 2 )  // 若 dword_795374 != 3 与/或 dword_795374 != 2
    {
      v6 = sub_44ACC0(1);  // 槽字段取值转发
      if ( sub_44ACC0(0) < v6 )  // 槽字段取值转发
        Src = (void *)-12973;  // Src = 转换(-12973)
    }
    v7 = sub_41ACF0((unsigned int **)(v79 + 16));  // 驻留串句柄 → 字符串指针
    sprintf(Buffer, "%s Lv %d", v7, v5);  // 拼字符串（模板 %s Lv %d）
    sub_570C10(0, Buffer, (int)(this + 60), (int)Src);  // 绘制链中层 3（4015C0 字符串 + 570B80）
    v8 = sub_41ACF0((unsigned int **)(v79 + 16));  // 驻留串句柄 → 字符串指针
    pThis_3C = sub_4883E0((int)(this + 60), (int)v8);  // 转发到 +48 对象虚表 +16
    if ( pThis_3C > 170 )  // 若 pThis_3C > 170
      pThis_3C11 = pThis_3C;
    v10 = (CHAR *)sub_41ACF0((unsigned int **)(v79 + 20));  // 驻留串句柄 → 字符串指针
    sub_570C10(1, v10, (int)(this + 60), (int)Src);  // 绘制链中层 3（4015C0 字符串 + 570B80）
    v11 = 3;
    v12 = sub_41ACF0((unsigned int **)(v79 + 20));  // 驻留串句柄 → 字符串指针
    pThis_3C2 = sub_4883E0((int)(this + 60), (int)v12);  // 转发到 +48 对象虚表 +16
    if ( pThis_3C11 < pThis_3C2 )  // 若 pThis_3C11 < pThis_3C2
      pThis_3C11 = pThis_3C2;
    if ( dword_795374 == 2 )  // 若 dword_795374 == 2
    {
      v68 = sub_47DE90(v5);  // v68 = 调 sub_47DE90 返回值
      v14 = (const char *)sub_422E70(1144);  // v14 = 调 sub_422E70 返回值
      sprintf(Buffer, v14, v68);  // 拼字符串
      sub_570C10(3, Buffer, (int)(this + 60), -1);  // 绘制链中层 3（4015C0 字符串 + 570B80）
    }
    else  // 否则分支
    {
      if ( dword_795374 != 3 )  // 若 dword_795374 != 3
        goto LABEL_24;  // 跳转 LABEL_24
      v15 = dword_9B88CC + 4;
      v69 = *(uint32_t *)(v15 + 488) + sub_47DE90(v5);
      v16 = (const char *)sub_422E70(1145);  // v16 = 调 sub_422E70 返回值
      sprintf(Buffer, v16, v69);  // 拼字符串
      sub_570C10(3, Buffer, (int)(this + 60), -1);  // 绘制链中层 3（4015C0 字符串 + 570B80）
    }
    v11 = 4;
    pThis_3C3 = sub_4883E0((int)(this + 60), (int)Buffer);  // 转发到 +48 对象虚表 +16
    if ( pThis_3C11 < pThis_3C3 )  // 若 pThis_3C11 < pThis_3C3
      pThis_3C11 = pThis_3C3;
LABEL_24:  // 标签 LABEL_24（跳转合流点）
    v80 = sub_4B1C40((uint32_t *)dword_9B88CC, v5);  // 14 字节表按 1 基索引取值
    if ( v80 <= 0 )  // 若 v80 <= 0
    {
      if ( *(uint32_t *)(v79 + 120) != 0 )  // 若 *(uint32_t *)(v79 + 120) != 0
        v63 = (const char *)sub_422E70(1148);  // v63 = 调 sub_422E70 返回值
      else  // 否则分支
        v63 = (const char *)sub_422E70(1147);  // v63 = 调 sub_422E70 返回值
      sprintf(Buffer, v63);  // 拼字符串
    }
    else  // 否则分支
    {
      v18 = (const char *)sub_422E70(1146);  // v18 = 调 sub_422E70 返回值
      sprintf(Buffer, v18, (double)v80 * 0.001);  // 拼字符串
    }
    sub_570C10(v11, Buffer, (int)(this + 60), -1);  // 绘制链中层 3（4015C0 字符串 + 570B80）
    pThis_3C4 = sub_4883E0((int)(this + 60), (int)Buffer);  // 转发到 +48 对象虚表 +16
    if ( pThis_3C11 < pThis_3C4 )  // 若 pThis_3C11 < pThis_3C4
      pThis_3C11 = pThis_3C4;
    if ( v5 > 0 && (int)sub_47EA80(v5) > 0 )  // 若 v5 > 0
    {
      v20 = sub_47EA80(v5);  // v20 = 调 sub_47EA80 返回值
      sprintf(Buffer, "MP %d", v20);  // 拼字符串（模板 MP %d）
      if ( sub_4C0360((void *)dword_9B88CC) >= 1.0 )  // 若调用结果为真
        sub_570C10(v11, Buffer, (int)(this + 112), -1);  // 绘制链中层 3（4015C0 字符串 + 570B80）
      else  // 否则分支
        sub_570C10(v11, Buffer, (int)(this + 112), -12973);  // 绘制链中层 3（4015C0 字符串 + 570B80）
    }
    v21 = v11 + 1;
    if ( (int)sub_47EAD0(v5) > 0 )  // 若调用结果为真
    {
      v80 = sub_47EAD0(v5);  // v80 = 调 sub_47EAD0 返回值
      v22 = (const char *)sub_422E70(1149);  // v22 = 调 sub_422E70 返回值
      sprintf(Buffer, v22, (double)v80 * 0.001);  // 拼字符串
      sub_570C10(v21++, Buffer, (int)(this + 60), -1);  // 绘制链中层 3（4015C0 字符串 + 570B80）
    }
    v23 = *(uint32_t *)(v79 + 400);  // v23 = v79+400
    if ( v23 != 0 && *(uint32_t *)(v23 + 4) != 0 )  // 若 v23 != 0
    {
      if ( (uint8_t)sub_461710(dword_9B88CC) == 0 || dword_795374 == 3 || dword_795374 == 2 )  // 子对象存在性判定（+558）
      {
        v70 = -1;
        pThis_3C5 = (int)(this + 60);
        v24 = (CHAR *)sub_41ACF0((unsigned int **)(v79 + 400));  // 驻留串句柄 → 字符串指针
      }
      else  // 否则分支
      {
        v70 = -13487361;
        pThis_3C5 = (int)(this + 60);
        v24 = (CHAR *)sub_422E70(1150);  // v24 = 调 sub_422E70 返回值
      }
      sub_570C10(v21++, v24, pThis_3C5, v70);  // 绘制链中层 3（4015C0 字符串 + 570B80）
    }
    if ( (uint8_t)sub_570470(v79 + 324) == 0 )  // 技能信息窗小辅助（13 行）
    {
      v25 = *(void **)(v79 + 332);
      ++v21;  // 自增v21
      Src = *(void **)(v79 + 328);
      if ( Src != v25 )  // 若 Src != v25
      {
        do  // do-while 循环体起点
        {
          v80 = -346530;
          v72 = sub_41A5E0(dword_9B88CC + 510);  // crypt4byte 解密校验（·0x41A590 逆运算）
          v73 = *((uint32_t *)Src + 1)
              + (v72 - 1) * (*((uint32_t *)Src + 2) - *((uint32_t *)Src + 1)) / (sub_47DCC0(dword_9B88CC) - 1);
          v26 = sub_484E80((int *)dword_8F852C, *(uint32_t *)Src);  // 按类型查找下标（同一匹配规则，未命中 -1）
          if ( v26 == -1
            || (v26 >= *((uint32_t *)dword_8F852C + 2)  // 角色/物品栏管理器
              ? (pObj = 0)
              : (pObj = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v26)),  // 角色/物品栏管理器
                (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj) < v73) )  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420…
          {
            v80 = -13487361;
          }
          v65 = sub_4F2CE0(*(uint32_t *)Src);  // v65 = 调 sub_4F2CE0 返回值
          v28 = (const char *)sub_422E70(1151);  // v28 = 调 sub_422E70 返回值
          sprintf(Buffer, v28, v65, v73);  // 拼字符串
          sub_570C10(v21++, Buffer, (int)(this + 60), v80);  // 绘制链中层 3（4015C0 字符串 + 570B80）
          pThis_3C6 = sub_4883E0((int)(this + 60), (int)Buffer);  // 转发到 +48 对象虚表 +16
          if ( pThis_3C11 < pThis_3C6 )  // 若 pThis_3C11 < pThis_3C6
            pThis_3C11 = pThis_3C6;
          v30 = *(void **)(v79 + 332);
          Src = (char *)Src + 12;
        }
        while ( Src != v30 );  // 条件循环
      }
    }
    if ( dword_795374 == 3 || dword_795374 == 2 )  // 若 dword_795374 == 3 与/或 dword_795374 == 2
    {
      v31 = *(uint32_t *)(v79 + 92);  // v31 = v79+92
      if ( v31 != 0 )  // 若 v31 非 0
      {
        v32 = *(uint32_t *)(v79 + 96) - v31;
        if ( v32 / 14 > 0 )  // 若 v32 / 14 > 0
        {
          ++v21;  // 自增v21
          Src = nullptr;  // Src = 空指针
          v80 = v32 / 14;
          do  // do-while 循环体起点
          {
            v33 = sub_41A5E0((unsigned int)Src + *(uint32_t *)(v79 + 92));  // crypt4byte 解密校验（·0x41A590 逆运算）
            v74 = sub_47DC90(v33);  // v74 = 调 sub_47DC90 返回值
            if ( v74 != 0 )  // 若 v74 非 0
            {
              v71 = sub_41A5E0((unsigned int)Src + *(uint32_t *)(v79 + 108));  // crypt4byte 解密校验（·0x41A590 逆运算）
              v66 = sub_41ACF0((unsigned int **)(v74 + 20));  // 驻留串句柄 → 字符串指针
              v34 = (const char *)sub_422E70(1152);  // v34 = 调 sub_422E70 返回值
              sprintf(Buffer, v34, v66, v71);  // 拼字符串
              sub_570C10(v21++, Buffer, (int)(this + 60), -1);  // 绘制链中层 3（4015C0 字符串 + 570B80）
              pThis_3C7 = sub_4883E0((int)(this + 60), (int)Buffer);  // 转发到 +48 对象虚表 +16
              if ( pThis_3C11 < pThis_3C7 )  // 若 pThis_3C11 < pThis_3C7
                pThis_3C11 = pThis_3C7;
            }
            v36 = v80 == 1;
            Src = (char *)Src + 14;
            --v80;  // 自减v80
          }
          while ( !v36 );  // 条件循环
        }
      }
    }
    if ( (uint8_t)sub_47F310(Buffer, v5) != 0 )  // 若调用结果为真
    {
      ++v21;  // 自增v21
      Block = nullptr;  // Block = 空指针
      v77 = 0;
      v78 = 0;
      v84 = 0;
      v37 = sub_570CB0(Buffer, 34, v75);  // 技能信息窗部件构建（184 行：416C40/406D00/4164C0 文本块装配）
      if ( v37 > 0 )  // 若 v37 > 0
      {
        Src = (char *)Block + 4;
        v80 = v37;
        do  // do-while 循环体起点
        {
          v38 = Src;
          if ( *((uint32_t *)Src + 5) >= 0x10u )  // 若 *((uint32_t *)Src + 5) >= 0x10u
            v38 = *(void **)Src;
          sub_570C10(v21++, v38, (int)(this + 60), -1);  // 绘制链中层 3（4015C0 字符串 + 570B80）
          v39 = Src;
          if ( *((uint32_t *)Src + 5) >= 0x10u )  // 若 *((uint32_t *)Src + 5) >= 0x10u
            v39 = *(void **)Src;
          pThis_3C8 = sub_4883E0((int)(this + 60), (int)v39);  // 转发到 +48 对象虚表 +16
          if ( pThis_3C11 < pThis_3C8 )  // 若 pThis_3C11 < pThis_3C8
            pThis_3C11 = pThis_3C8;
          v36 = v80 == 1;
          Src = (char *)Src + 28;
          --v80;  // 自减v80
        }
        while ( !v36 );  // 条件循环
      }
      v84 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4166A0((int)Block, v77);  // 析构区间内 28B string 元素
        j__free(Block);  // 调 j__free
      }
    }
    if ( (dword_795374 == 3 || dword_795374 == 2) && v5 > 1 && (uint8_t)sub_47F310(Buffer, v5 - 1) != 0 )  // 若 dword_795374 == 3 与/或 dword_795374 == 2 与/或 v5 > 1
    {
      v41 = v21 + 1;
      v42 = (void *)sub_422E70(1153);  // v42 = 调 sub_422E70 返回值
      sub_570C10(v41, v42, (int)(this + 164), -1);  // 绘制链中层 3（4015C0 字符串 + 570B80）
      v21 = v41 + 1;
      Block = nullptr;  // Block = 空指针
      v77 = 0;
      v78 = 0;
      v84 = 1;
      v43 = sub_570CB0(Buffer, 34, v75);  // 技能信息窗部件构建（184 行：416C40/406D00/4164C0 文本块装配）
      if ( v43 > 0 )  // 若 v43 > 0
      {
        v86 = (char *)Block + 4;
        v80 = v43;
        do  // do-while 循环体起点
        {
          v44 = v86;
          if ( *((uint32_t *)v86 + 5) >= 0x10u )  // 若 *((uint32_t *)v86 + 5) >= 0x10u
            v44 = *(void **)v86;
          sub_570C10(v21++, v44, (int)(this + 60), -1);  // 绘制链中层 3（4015C0 字符串 + 570B80）
          if ( *((uint32_t *)v86 + 5) < 0x10u )  // 若 *((uint32_t *)v86 + 5) < 0x10u
            v45 = (int)v86;
          else  // 否则分支
            v45 = *(uint32_t *)v86;  // v45 = v86
          pThis_3C9 = sub_4883E0((int)(this + 60), v45);  // 转发到 +48 对象虚表 +16
          if ( pThis_3C11 < pThis_3C9 )  // 若 pThis_3C11 < pThis_3C9
            pThis_3C11 = pThis_3C9;
          v36 = v80 == 1;
          v86 += 28;
          --v80;  // 自减v80
        }
        while ( !v36 );  // 条件循环
      }
      v84 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        sub_4166A0((int)Block, v77);  // 析构区间内 28B string 元素
        j__free(Block);  // 调 j__free
      }
    }
    v47 = *(uint32_t *)(v79 + 24);  // v47 = v79+24
    if ( v47 != 0 && *(uint32_t *)(v47 + 4) != 0 )  // 若 v47 != 0
    {
      ++v21;  // 自增v21
      Block = nullptr;  // Block = 空指针
      v77 = 0;
      v78 = 0;
      v84 = 2;
      v48 = sub_41ACF0((unsigned int **)(v79 + 24));  // 驻留串句柄 → 字符串指针
      v49 = sub_570CB0(v48, 34, v75);  // 技能信息窗部件构建（184 行：416C40/406D00/4164C0 文本块装配）
      if ( v49 > 0 )  // 若 v49 > 0
      {
        v87 = (char *)Block + 4;
        v80 = v49;
        do  // do-while 循环体起点
        {
          v50 = v87;
          if ( *((uint32_t *)v87 + 5) >= 0x10u )  // 若 *((uint32_t *)v87 + 5) >= 0x10u
            v50 = *(void **)v87;
          sub_570C10(v21++, v50, (int)(this + 60), -2302756);  // 绘制链中层 3（4015C0 字符串 + 570B80）
          v51 = (int)v87;
          if ( *((uint32_t *)v87 + 5) >= 0x10u )  // 若 *((uint32_t *)v87 + 5) >= 0x10u
            v51 = *(uint32_t *)v87;  // v51 = v87
          pThis_3C10 = sub_4883E0((int)(this + 60), v51);  // 转发到 +48 对象虚表 +16
          if ( pThis_3C11 < pThis_3C10 )  // 若 pThis_3C11 < pThis_3C10
            pThis_3C11 = pThis_3C10;
          v36 = v80 == 1;
          v87 += 28;
          --v80;  // 自减v80
        }
        while ( !v36 );  // 条件循环
      }
      v84 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
      {
        Block2 = Block;
        sub_4166A0((int)Block, v77);  // 析构区间内 28B string 元素
        j__free(Block2);  // 调 j__free
      }
    }
    if ( dword_795374 == 3 )  // 若 dword_795374 == 3
      goto LABEL_117;  // 跳转 LABEL_117
    if ( dword_795374 == 2 )  // 若 dword_795374 == 2
      goto LABEL_117;  // 跳转 LABEL_117
    v54 = *(uint32_t *)(dword_9B88CC + 392);  // v54 = dword_9B88CC+392
    if ( v54 == 0 || (*(uint32_t *)(dword_9B88CC + 396) - v54) / 44 == 0 )  // 若 v54 == 0
      goto LABEL_117;  // 跳转 LABEL_117
    if ( sub_41A5E0(dword_9B88CC + 558) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      pThis_A4 = (int)(this + 164);
      v62 = 1154;
    }
    else  // 否则分支
    {
      if ( sub_41A5E0(dword_9B88CC + 558) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
LABEL_117:  // 标签 LABEL_117（跳转合流点）
        pThis_1B = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 27) + 20))(*((uint32_t *)this + 27));  // 调用虚函数槽 +20
        v58 = *(uint32_t **)this;
        *((uint32_t *)this + 22) = pThis_3C11;
        ((void (/*thiscall*/ *)(char *, int, int))v58[13])(this, pThis_3C11, v21 * (pThis_1B + 1));
        pThis_2 = *((uint32_t *)this + 2);
        *(uint32_t *)(pThis_2 + 28) = 0;  // pThis_2+28 = 0
        *(uint32_t *)(pThis_2 + 32) = 0;  // pThis_2+32 = 0
        pThis_38 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 56))(this);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
        v61 = *(uint32_t **)this;
        *((uint32_t *)this + 9) = pThis_38;
        *((uint32_t *)this + 10) = ((int (/*thiscall*/ *)(char *))v61[15])(this);
        return 1;  // 返回 1(成功)
      }
      pThis_A4 = (int)(this + 164);
      v62 = 1155;
    }
    v55 = v21 + 1;
    v56 = (void *)sub_422E70(v62);  // v56 = 调 sub_422E70 返回值
    sub_570C10(v55, v56, pThis_A4, -346530);  // 绘制链中层 3（4015C0 字符串 + 570B80）
    v21 = v55 + 1;
    goto LABEL_117;  // 跳转 LABEL_117
  }
  return 0;
}


// ============================================================
// 【分区 4】物品信息窗（CNRDItemInfoWindow）绘制链（0x571AF0-0x575FF0）
// 属性文本组装 0x571B80（497120/4971B0/497150 物品属性查询）；
// 部件构建 0x572BC0（186 行）；绘制主函数 0x572EF0（725 行）；
// 完整绘制 0x5745B0（1226 行，全文件最大——含各稀有度/类型说明分支）；
// 打开入口 CNRDItemInfoWindow__vmtC 在 0x575F80。
// ============================================================
// ------------------------------------------------------------
// 0x571AF0 sub_571AF0 —— 物品说明文本辅助（422E70 字符串表取串）
// ------------------------------------------------------------
char */*cdecl*/ sub_571AF0(int nArg1)  // 实现：物品说明文本辅助（422E70 字符串表取串）
{
  if ( nArg1 >= 100 )  // 若 nArg1 >= 100
    return sub_422E70(965);  // 返回 调 sub_422E70 返回值
  if ( nArg1 >= 30 )  // 若 nArg1 >= 30
    return sub_422E70(966);  // 返回 调 sub_422E70 返回值
  if ( nArg1 >= -29 )  // 若 nArg1 >= -29
    return sub_422E70(967);  // 返回 调 sub_422E70 返回值
  if ( nArg1 < -99 )  // 若 nArg1 < -99
    return sub_422E70(969);  // 返回 调 sub_422E70 返回值
  return sub_422E70(968);  // 返回 调 sub_422E70 返回值
}



// ------------------------------------------------------------
// 0x571B80 sub_571B80 —— 物品属性文本组装（135 行：497120/4971B0/497150 属性枚举）
// ------------------------------------------------------------
int /*usercall*/ sub_571B80@<eax>(double fArg1@<st0>, int nArg2, float fArg3, int nArg4, char *Buffer)  // 实现：物品属性文本组装（135 行：497120/4971B0/497150 属性枚举）
{
  int result; // eax
  char *v6; // eax
  char *v7; // eax
  char *v8; // eax
  char *v9; // eax
  char *v10; // eax
  char *v11; // eax
  char *v12; // eax
  char *v13; // eax
  char *v14; // eax
  char *v15; // eax
  char *v16; // eax
  char *v17; // eax
  double fArg32; // [esp+0h] [ebp-18h]
  double fArg33; // [esp+4h] [ebp-14h]
  double v20; // [esp+8h] [ebp-10h]
  double v21; // [esp+8h] [ebp-10h]
  double v22; // [esp+8h] [ebp-10h]
  double v23; // [esp+8h] [ebp-10h]
  double v24; // [esp+8h] [ebp-10h]
  double v25; // [esp+8h] [ebp-10h]
  double v26; // [esp+Ch] [ebp-Ch]
  double v27; // [esp+Ch] [ebp-Ch]
  double v28; // [esp+Ch] [ebp-Ch]
  double v29; // [esp+Ch] [ebp-Ch]
  double v30; // [esp+Ch] [ebp-Ch]
  int v31; // [esp+10h] [ebp-8h]
  int v32; // [esp+10h] [ebp-8h]
  const char *future_error_what; // [esp+10h] [ebp-8h]

  result = nArg2;
  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      sub_497120(0, nArg4);  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      v31 = (uint64_t)(fArg1 * 100.0);
      v20 = (double)(int)sub_4971B0(0, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      fArg32 = fArg3;
      v11 = sub_422E70(977);  // v11 = 调 sub_422E70 返回值
      goto LABEL_10;  // 跳转 LABEL_10
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      v26 = (double)(int)sub_4971B0(1, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      fArg33 = fArg3;
      v6 = sub_422E70(971);  // v6 = 调 sub_422E70 返回值
      goto LABEL_3;  // 跳转 LABEL_3
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      sub_497120(2, nArg4);  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      v23 = (double)(int)sub_4971B0(2, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      v14 = sub_422E70(981);  // v14 = 调 sub_422E70 返回值
      return sprintf(Buffer, v14, fArg3, v23, (unsigned int)(uint64_t)fArg1);  // 拼字符串
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      v27 = (double)(int)sub_4971B0(3, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      v7 = sub_422E70(972);  // v7 = 调 sub_422E70 返回值
      return sprintf(Buffer, v7, fArg3, v27);  // 拼字符串
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      sub_497120(4, nArg4);  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      v21 = (double)(int)sub_4971B0(4, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      v12 = sub_422E70(978);  // v12 = 调 sub_422E70 返回值
      return sprintf(Buffer, v12, fArg3, v21, 100 - (unsigned int)(uint64_t)(fArg1 * 100.0));  // 拼字符串
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      v28 = (double)(int)sub_4971B0(5, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      v8 = sub_422E70(973);  // v8 = 调 sub_422E70 返回值
      return sprintf(Buffer, v8, fArg3, v28);  // 拼字符串
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      sub_497120(6, nArg4);  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      v24 = (double)(int)sub_4971B0(6, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      v15 = sub_422E70(983);  // v15 = 调 sub_422E70 返回值
      return sprintf(Buffer, v15, fArg3, v24, (unsigned int)(uint64_t)fArg1);  // 拼字符串
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      v32 = (uint64_t)sub_497150(7, nArg4);  // 第二组状态时长插值（flt_6CB2F0 → flt_6CB2F4）
      v25 = (double)(int)sub_4971B0(7, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      v16 = sub_422E70(984);  // v16 = 调 sub_422E70 返回值
      return sprintf(Buffer, v16, fArg3, v25, v32);  // 拼字符串
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      v29 = (double)(int)sub_4971B0(8, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      v9 = sub_422E70(975);  // v9 = 调 sub_422E70 返回值
      return sprintf(Buffer, v9, fArg3, v29);  // 拼字符串
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      sub_497120(9, nArg4);  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      v31 = (uint64_t)fArg1;
      v20 = (double)(int)sub_4971B0(9, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      fArg32 = fArg3;
      v11 = sub_422E70(3001);  // v11 = 调 sub_422E70 返回值
      goto LABEL_10;  // 跳转 LABEL_10
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      future_error_what = std::_Get_future_error_what(nArg2);  // future_error_what = 调 std::_Get_future_error_what
      v17 = sub_422E70(985);  // v17 = 调 sub_422E70 返回值
      return sprintf(Buffer, v17, future_error_what);  // 拼字符串
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
      sub_497120(11, nArg4);  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      v31 = (uint64_t)fArg1;
      v20 = (double)(int)sub_4971B0(11, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      fArg32 = fArg3;
      v11 = sub_422E70(982);  // v11 = 调 sub_422E70 返回值
      goto LABEL_10;  // 跳转 LABEL_10
    case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
      sub_497120(12, nArg4);  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      v31 = (uint64_t)(fArg1 * 100.0);
      v20 = (double)(int)sub_4971B0(12, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      fArg32 = fArg3;
      v11 = sub_422E70(979);  // v11 = 调 sub_422E70 返回值
LABEL_10:  // 标签 LABEL_10（跳转合流点）
      result = sprintf(Buffer, v11, fArg32, v20, v31);  // 拼字符串
      break;  // 跳出循环/分支
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      sub_497120(13, nArg4);  // 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
      v22 = (double)(int)sub_4971B0(13, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      v13 = sub_422E70(980);  // v13 = 调 sub_422E70 返回值
      result = sprintf(Buffer, v13, fArg3, v22, (unsigned int)(uint64_t)(fArg1 * 100.0));  // 拼字符串
      break;  // 跳出循环/分支
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      v26 = (double)(int)sub_4971B0(15, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      fArg33 = fArg3;
      v6 = sub_422E70(974);  // v6 = 调 sub_422E70 返回值
LABEL_3:  // 标签 LABEL_3（跳转合流点）
      result = sprintf(Buffer, v6, fArg33, v26);  // 拼字符串
      break;  // 跳出循环/分支
    case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
      v30 = (double)(int)sub_4971B0(16, nArg4, 0) * 0.001;  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
      v10 = sub_422E70(976);  // v10 = 调 sub_422E70 返回值
      result = sprintf(Buffer, v10, fArg3, v30);  // 拼字符串
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}


// ------------------------------------------------------------
// 0x572040 sub_572040 —— 物品信息窗数据准备（70 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_572040(int this)  // 实现：物品信息窗数据准备（70 行）
{
  int result; // eax

  *(uint32_t *)(this + 72) = 12;  // this+72 = 12
  *(uint32_t *)(this + 80) = 1600;  // this+80 = 1600
  *(uint8_t *)(this + 52) = 0;  // this+52 = 0
  *(uint8_t *)(this + 53) = 0;  // this+53 = 0
  *(uint8_t *)(this + 54) = 0;  // this+54 = 0
  *(uint8_t *)(this + 55) = 0;  // this+55 = 0
  *(uint32_t *)(this + 64) = 0;  // this+64 = 0
  *(uint32_t *)(this + 76) = 0;  // this+76〔pBtnActionE〕
  *(uint32_t *)(this + 84) = 0;  // this+84 = 0
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 96) = 0;  // this+96 = 0
  *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  *(uint32_t *)(this + 68) = 6;  // this+68 = 6
  *(uint32_t *)(this + 100) = dword_99FCCC;  // this+100 = dword_99FCCC
  *(uint32_t *)(this + 80) = 170;  // this+80 = 170
  *(uint32_t *)(this + 64) = 0;  // this+64 = 0
  *(uint32_t *)(this + 56) = -16777216;  // this+56 = -16777216
  *(uint8_t *)(this + 54) = 1;  // this+54 = 1
  *(uint32_t *)(this + 120) = 6;  // this+120〔pAnimObj〕
  *(uint8_t *)(this + 104) = 0;  // this+104 = 0
  *(uint8_t *)(this + 105) = 0;  // this+105〔bGuildFlagD〕
  *(uint8_t *)(this + 106) = 0;  // this+106 = 0
  *(uint8_t *)(this + 107) = 0;  // this+107 = 0
  *(uint32_t *)(this + 116) = 0;  // this+116 = 0
  *(uint32_t *)(this + 124) = 12;  // this+124 = 12
  *(uint32_t *)(this + 128) = 0;  // this+128 = 0
  *(uint32_t *)(this + 132) = 1600;  // this+132 = 1600
  *(uint32_t *)(this + 136) = 0;  // this+136 = 0
  *(uint32_t *)(this + 140) = 0;  // this+140 = 0
  *(uint32_t *)(this + 144) = 0;  // this+144 = 0
  *(uint32_t *)(this + 148) = 0;  // this+148 = 0
  *(uint32_t *)(this + 152) = 0;  // this+152 = 0
  *(uint8_t *)(this + 106) = 1;  // this+106 = 1
  *(uint32_t *)(this + 152) = dword_99FCCC;  // this+152 = dword_99FCCC
  *(uint32_t *)(this + 132) = 170;  // this+132 = 170
  *(uint32_t *)(this + 116) = 2;  // this+116 = 2
  *(uint32_t *)(this + 108) = -16777216;  // this+108 = -16777216
  *(uint8_t *)(this + 156) = 0;  // this+156 = 0
  *(uint8_t *)(this + 157) = 0;  // this+157 = 0
  *(uint8_t *)(this + 158) = 0;  // this+158 = 0
  *(uint8_t *)(this + 159) = 0;  // this+159 = 0
  *(uint32_t *)(this + 168) = 0;  // this+168 = 0
  *(uint32_t *)(this + 172) = 6;  // this+172 = 6
  *(uint32_t *)(this + 176) = 12;  // this+176 = 12
  *(uint32_t *)(this + 180) = 0;  // this+180 = 0
  *(uint32_t *)(this + 184) = 1600;  // this+184 = 1600
  *(uint32_t *)(this + 188) = 0;  // this+188 = 0
  *(uint32_t *)(this + 192) = 0;  // this+192 = 0
  *(uint32_t *)(this + 196) = 0;  // this+196 = 0
  *(uint32_t *)(this + 200) = 0;  // this+200 = 0
  *(uint32_t *)(this + 204) = 0;  // this+204 = 0
  *(uint8_t *)(this + 158) = 1;  // this+158 = 1
  result = dword_99FCCC;
  *(uint32_t *)(this + 204) = dword_99FCCC;  // this+204 = dword_99FCCC
  *(uint32_t *)(this + 184) = 170;  // this+184 = 170
  *(uint32_t *)(this + 168) = 1;  // this+168 = 1
  *(uint32_t *)(this + 160) = -16777216;  // this+160 = -16777216
  return result;
}



// ------------------------------------------------------------
// 0x5721B0 CNRDItemInfoWindow__vmt10 —— CNRDItemInfoWindow vmt10：打开状态切换（44ABE0/44E850）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemInfoWindow__vmt10(uint32_t *this)  // 实现：CNRDItemInfoWindow vmt10：打开状态切换（44ABE0/44E850）
{
  int result; // eax

  dword_9B88D0 = 0;
  result = *(this + 4);  // result = this+4
  *(uint32_t *)(*(uint32_t *)(result + 2500) + 60) = 255;
  return result;
}



// ------------------------------------------------------------
// 0x5721D0 sub_5721D0 —— 物品信息窗小辅助（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5721D0(int *this)  // 实现：物品信息窗小辅助（15 行）
{
  int result; // eax

  result = *(this + 1);  // result = this+1
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(this + 2) - result) / 40;
  return result;
}



// ------------------------------------------------------------
// 0x5721F0 CNRDItemInfoWindow__vmt0 —— CNRDItemInfoWindow vmt0：主构造（71 行）
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDItemInfoWindow__vmt0(int *this, int nArg2)  // 实现：CNRDItemInfoWindow vmt0：主构造（71 行）
{
  unsigned int result; // eax
  LONG v4; // ecx
  int v5; // eax
  int v6; // esi
  int v7; // eax
  uint32_t *fld_e10; // ebx
  int v9; // esi
  uint32_t *fld_e102; // eax
  uint32_t *v11; // edx
  int fld_e22; // [esp+8h] [ebp-Ch]
  int fld_e2; // [esp+Ch] [ebp-8h]
  unsigned int i; // [esp+10h] [ebp-4h]
  int v15; // [esp+1Ch] [ebp+8h]

  IRDPopupWindow__vmt0(this, nArg2);  // 调 IRDPopupWindow__vmt0 构造
  result = *(this + 2);  // result = this+2
  if ( nArg2 == result )  // 若 nArg2 == result
  {
    v4 = *(uint32_t *)(result + 20);  // v4 = result+20
    v5 = *(uint32_t *)(result + 24);  // v5 = result+24
    v6 = pt.y + 30;
    if ( v4 < pt.x && v5 < v6 && v4 + *(this + 67) > pt.x && v5 + *(this + 68) > v6 )  // 若 v4 < pt 与/或 v5 < v6
      *(uint32_t *)(*(uint32_t *)(*(this + 4) + 2500) + 60) = 120;
    fld_e2 = *(uint32_t *)(*(this + 2) + 24) + 7;  // fld_e2 = 读 this+2
    v7 = 0;
    for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
    {
      v15 = v7;
      result = *(this + 10);  // result = this+10
      if ( result == 0 )  // 若 result 为 0
        break;  // 跳出循环/分支
      result = (int)(*(this + 11) - result) / 40;
      if ( i >= result )  // 若 i >= result
        break;  // 跳出循环/分支
      fld_e10 = (uint32_t *)(v15 + *(this + 10));
      if ( *fld_e10 / 36 != 0 )  // 若 *fld_e10 / 36 != 0
      {
        v9 = fld_e2 + 13 * (*fld_e10 % 36 + 3);
        fld_e22 = 180 * (*fld_e10 / 36) + *(uint32_t *)(*(this + 2) + 20) + 7;
      }
      else  // 否则分支
      {
        v9 = fld_e2 + 13 * *fld_e10;
        fld_e22 = *(uint32_t *)(*(this + 2) + 20) + 7;  // fld_e22 = 读 this+2
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, fld_e10[1]);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
      fld_e102 = (uint32_t *)(v15 + *(this + 10));
      if ( fld_e102[9] < 0x10u )  // 若 fld_e102[9] < 0x10u
        v11 = fld_e102 + 4;
      else  // 否则分支
        v11 = (uint32_t *)fld_e102[4];
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        dword_79C0B0,  // 默认字体/绘制资源
        fld_e22,
        v9,
        fld_e102[2],
        v11);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
      v7 = v15 + 40;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x572360 sub_572360 —— 物品信息文本行辅助（4015C0/4021F0/4014D0）
// ------------------------------------------------------------
int /*cdecl*/ sub_572360(int pArg1, void *Src, int nArg3)  // 实现：物品信息文本行辅助（4015C0/4021F0/4014D0）
{
  int v3; // eax
  uint8_t v5[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  int v7; // [esp+1Ch] [ebp-18h]
  unsigned int v8; // [esp+20h] [ebp-14h]
  int v9; // [esp+24h] [ebp-10h]
  int v10; // [esp+30h] [ebp-4h]

  v9 = 0;
  v8 = 15;
  v7 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  v10 = 0;
  v3 = sub_4021F0((std::_String_base *)v5, nArg3, 0, -1);  // std::string::append(str, pos, n) 模板实例（含自引用重叠路径）
  *(uint32_t *)(pArg1 + 24) = 15;  // pArg1+24 = 15
  *(uint32_t *)(pArg1 + 20) = 0;  // pArg1+20 = 0
  *(uint8_t *)(pArg1 + 4) = 0;  // pArg1+4 = 0
  sub_4014D0((std::_String_base *)pArg1, v3, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  if ( v8 >= 0x10 )  // 若 v8 >= 0x10
    j__free(Block);  // 调 j__free
  return pArg1;
}



// ------------------------------------------------------------
// 0x572400 sub_572400 —— 文本行辅助（4014D0）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_572400(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：文本行辅助（4014D0）
{
  int nArg22; // esi
  uint32_t *uArg32; // edi
  int v5; // eax

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )  // 若 nArg1 == nArg2
    return uArg3;
  uArg32 = uArg3;
  do  // do-while 循环体起点
  {
    v5 = *(uint32_t *)(nArg22 - 40);
    nArg22 -= 40;
    uArg32 -= 10;
    *uArg32 = v5;  // *uArg32 写入 v5
    uArg32[1] = *(uint32_t *)(nArg22 + 4);  // uArg32[1] 写入 *(uint32_t *)(nArg22 + 4)
    uArg32[2] = *(uint32_t *)(nArg22 + 8);  // uArg32[2] 写入 *(uint32_t *)(nArg22 + 8)
    sub_4014D0((std::_String_base *)(uArg32 + 3), nArg22 + 12, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  }
  while ( nArg22 != nArg1 );  // 条件循环
  return uArg32;
}



// ------------------------------------------------------------
// 0x572450 sub_572450 —— 文本行辅助 2（4014D0）
// ------------------------------------------------------------
int /*cdecl*/ sub_572450(int pArg1, uint32_t *pArg2)  // 实现：文本行辅助 2（4014D0）
{
  int result; // eax

  result = pArg1;
  if ( pArg1 != 0 )  // 若 pArg1 非 0
  {
    *(uint32_t *)pArg1 = *pArg2;
    *(uint32_t *)(pArg1 + 4) = pArg2[1];  // pArg1+4 = pArg2[1]
    *(uint32_t *)(pArg1 + 8) = pArg2[2];  // pArg1+8 = pArg2[2]
    *(uint32_t *)(pArg1 + 36) = 15;  // pArg1+36 = 15
    *(uint32_t *)(pArg1 + 32) = 0;  // pArg1+32 = 0
    *(uint8_t *)(pArg1 + 16) = 0;  // pArg1+16 = 0
    return sub_4014D0((std::_String_base *)(pArg1 + 12), pArg2 + 3, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  }
  return result;
}



// ------------------------------------------------------------
// 0x5724C0 sub_5724C0 —— 字符串处理（4015C0）——信息窗共用
// ------------------------------------------------------------
unsigned int /*usercall*/ sub_5724C0@<eax>(int pArg1@<ebx>)  // 实现：信息窗共用
{
  unsigned int v1; // ecx
  const char *psz2; // esi
  const char *v3; // eax
  const char *psz; // eax
  unsigned int result; // eax
  char *v6; // ecx

  v1 = *(uint32_t *)(pArg1 + 24);  // v1 = pArg1+24
  psz2 = (const char *)(pArg1 + 4);
  if ( v1 < 0x10 )  // 若 v1 < 0x10
    v3 = (const char *)(pArg1 + 4);
  else  // 否则分支
    v3 = *(const char **)psz2;
  if ( *v3 == 32 )  // 若 *v3 == 32
  {
    if ( v1 < 0x10 )  // 若 v1 < 0x10
      psz = (const char *)(pArg1 + 4);
    else  // 否则分支
      psz = *(const char **)psz2;
    sub_4015C0((void *)(psz + 1), strlen(psz + 1));  // 【std::string构造赋值】
  }
  result = *(uint32_t *)(pArg1 + 24);  // result = pArg1+24
  if ( result < 0x10 )  // 若 result < 0x10
    v6 = (char *)(pArg1 + 4);
  else  // 否则分支
    v6 = *(char **)psz2;
  if ( *v6 == 23662 )  // 若 *v6 == 23662
  {
    if ( result >= 0x10 )  // 若 result >= 0x10
      psz2 = *(const char **)psz2;
    return sub_4015C0((void *)(psz2 + 1), strlen(psz2 + 1));  // 【std::string构造赋值】
  }
  return result;
}



// ------------------------------------------------------------
// 0x572550 sub_572550 —— 转发 572400
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_572550(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：转发 572400
{
  return sub_572400(nArg1, nArg2, uArg3);  // 文本行辅助（4014D0）
}



// ------------------------------------------------------------
// 0x572570 sub_572570 —— 转发 572450
// ------------------------------------------------------------
int /*cdecl*/ sub_572570(uint32_t *uArg1, uint32_t *uArg2, int nArg3)  // 实现：转发 572450
{
  int nArg32; // edi
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v6[7] = 0;
  while ( uArg1 != uArg2 )  // 条件循环
  {
    sub_572450(nArg32, uArg1);  // 文本行辅助 2（4014D0）
    nArg32 += 40;
    uArg1 += 10;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x572620 sub_572620 —— 转发 572450（第二挂点）
// ------------------------------------------------------------
int /*cdecl*/ sub_572620(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：转发 572450（第二挂点）
{
  int nArg12; // esi
  int result; // eax
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  nArg12 = nArg1;
  v6[4] = v6;
  v6[3] = nArg1;
  v6[7] = 0;
  while ( nArg2 != 0 )  // 条件循环
  {
    result = sub_572450(nArg12, uArg3);  // 文本行辅助 2（4014D0）
    --nArg2;  // 自减nArg2
    nArg12 += 40;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5726C0 sub_5726C0 —— 转发 572620
// ------------------------------------------------------------
int /*stdcall*/ sub_5726C0(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：转发 572620
{
  sub_572620(nArg1, nArg2, uArg3);  // 转发 572450（第二挂点）
  return nArg1 + 40 * nArg2;
}



// ------------------------------------------------------------
// 0x5726F0 sub_5726F0 —— 物品信息窗文本构建主函数（136 行，与 5707E0 同构：558090 分隔 + 572570/5726C0 行组装 + 55A010）
// ------------------------------------------------------------
void /*thiscall*/ sub_5726F0(int *this, int pArg2, unsigned int uArg3, int *pDwArg4)  // 实现：物品信息窗文本构建主函数（136 行，与 5707E0 同构：558090 分隔 + 572570/5726C0 行组装 + 55A010）
{
  int v4; // edx
  int v6; // ecx
  int pVecEnd_14; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v12; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e28; // ecx
  int fld_e13; // eax
  unsigned int v17; // edi
  void *fld_e14; // eax
  int fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-6Ch]
  int fld_e25; // [esp-Ch] [ebp-60h]
  unsigned int fld_e24; // [esp-8h] [ebp-5Ch]
  int v25; // [esp+0h] [ebp-54h] BYREF
  void *Block; // [esp+Ch] [ebp-48h]
  int *pThis; // [esp+10h] [ebp-44h]
  char *pMem2; // [esp+14h] [ebp-40h]
  uint32_t v29[3]; // [esp+18h] [ebp-3Ch] BYREF
  char v30[4]; // [esp+24h] [ebp-30h] BYREF
  void *v31; // [esp+28h] [ebp-2Ch]
  int v32; // [esp+38h] [ebp-1Ch]
  unsigned int v33; // [esp+3Ch] [ebp-18h]
  int dword_796E502; // [esp+40h] [ebp-14h]
  int *v35; // [esp+44h] [ebp-10h]
  int v36; // [esp+50h] [ebp-4h]
  int v37; // [esp+5Ch] [ebp+8h]
  int v38; // [esp+60h] [ebp+Ch]
  int fld_e232; // [esp+64h] [ebp+10h]

  dword_796E502 = dword_796E50;
  v4 = pDwArg4[1];  // v4 = 取 pDwArg4[1]
  v6 = *pDwArg4;
  v35 = &v25;
  v29[0] = v6;
  v29[2] = pDwArg4[2];  // v29[2] = 取 pDwArg4[2]
  pThis = this;
  v29[1] = v4;
  v33 = 15;
  v32 = 0;
  LOBYTE(v31) = 0;
  sub_4014D0((std::_String_base *)v30, pDwArg4 + 3, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  pVecEnd_14 = *(this + 1);  // fld_e1 = this+1
  v36 = 0;
  if ( pVecEnd_14 != 0 )  // 若 fld_e1 非 0
    fld_e3 = (*(this + 3) - pVecEnd_14) / 40;
  else  // 否则分支
    fld_e3 = 0;
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( pVecEnd_14 != 0 )  // 若 fld_e1 非 0
      fld_e2 = (*(this + 2) - pVecEnd_14) / 40;
    else  // 否则分支
      fld_e2 = 0;
    if ( 107374182 - fld_e2 < uArg3 )  // 若 107374182 - fld_e2 < uArg3
      sub_558090(this);  // 信息窗共用）
    if ( pVecEnd_14 != 0 )  // 若 fld_e1 非 0
      fld_e22 = (*(this + 2) - pVecEnd_14) / 40;
    else  // 否则分支
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )  // 若 fld_e3 >= uArg3 + fld_e22
    {
      fld_e23 = *(this + 2);  // fld_e23 = this+2
      fld_e232 = fld_e23;
      if ( (fld_e23 - pArg2) / 40 >= uArg3 )  // 若 (fld_e23 - pArg2) / 40 >= uArg3
      {
        v37 = fld_e23 - 40 * uArg3;
        *(this + 2) = sub_572570(v37, fld_e23, fld_e23);  // 转发 572450
        sub_572550(pArg2, v37, fld_e232);  // 转发 572400
        sub_570610(pArg2, pArg2 + 40 * uArg3, v29);  // 文本行组装：4014D0 拼接（数值行）
      }
      else  // 否则分支
      {
        sub_572570(pArg2, fld_e23, pArg2 + 40 * uArg3);  // 转发 572450
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 40;
        fld_e25 = *(this + 2);  // fld_e25 = this+2
        LOBYTE(v36) = 3;
        sub_5726C0(fld_e25, fld_e24, v29);  // 转发 572620
        fld_e26 = 40 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8 = fld_e26
        v36 = 0;
        sub_570610(pArg2, fld_e26 - 40 * uArg3, v29);  // 文本行组装：4014D0 拼接（数值行）
      }
    }
    else  // 否则分支
    {
      if ( 107374182 - (fld_e3 >> 1) >= fld_e3 )  // 若 107374182 - (fld_e3 >> 1) >= fld_e3
        v12 = (fld_e3 >> 1) + fld_e3;
      else  // 否则分支
        v12 = 0;
      if ( pVecEnd_14 != 0 )  // 若 fld_e1 非 0
        fld_e27 = (*(this + 2) - pVecEnd_14) / 40;
      else  // 否则分支
        fld_e27 = 0;
      if ( v12 < uArg3 + fld_e27 )  // 若 v12 < uArg3 + fld_e27
        v12 = uArg3 + sub_5721D0(this);  // 物品信息窗小辅助（15 行）
      v38 = 40 * v12;
      pMem = (char *)operator new(40 * v12);
      fld_e12 = *(this + 1);  // fld_e12 = this+1
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v36) = 1;
      pMem2 = (char *)sub_572570(fld_e12, pArg2, pMem);  // 转发 572450
      sub_572620(pMem2, uArg3, v29);  // 转发 572450（第二挂点）
      fld_e28 = *(this + 2);  // fld_e28 = this+2
      pMem2 += 40 * uArg3;
      sub_572570(pArg2, fld_e28, pMem2);  // 转发 572450
      fld_e13 = *(this + 1);  // fld_e13 = this+1
      if ( fld_e13 != 0 )  // 若 fld_e13 非 0
        fld_e13 = (*(this + 2) - fld_e13) / 40;
      v17 = fld_e13 + uArg3;
      fld_e14 = (void *)*(this + 1);
      if ( fld_e14 != nullptr )  // 若 fld_e14 有效（非空）
      {
        sub_55A010(fld_e14, *(this + 2));  // 信息窗文本（5014C0）
        j__free((void *)*(this + 1));  // 调 j__free
      }
      *(this + 3) = (int)&pMem[v38];  // this+12 = (int)&pMem[v38]
      *(this + 2) = (int)&pMem[40 * v17];  // this+8 = (int)&pMem[40 * v17]
      *(this + 1) = (int)pMem;  // this+4 = (int)pMem
    }
  }
  if ( v33 >= 0x10 )  // 若 v33 >= 0x10
    j__free(v31);  // 调 j__free
}


// ------------------------------------------------------------
// 0x572A20 sub_572A20 —— 绘制链中层（转发 5726F0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_572A20(int *this, uint32_t *uArg2, char *pszArg3, int *pDwArg4)  // 实现：绘制链中层（转发 5726F0）
{
  int pVecEnd_6; // esi
  int v6; // esi

  pVecEnd_6 = *(this + 1);  // fld_e1 = this+1
  if ( pVecEnd_6 != 0 && (*(this + 2) - pVecEnd_6) / 40 != 0 )  // 若 pVecEnd_6 != 0
    v6 = (int)&pszArg3[-pVecEnd_6] / 40;
  else  // 否则分支
    v6 = 0;
  sub_5726F0(this, pszArg3, 1u, pDwArg4);  // 物品信息窗文本构建主函数（136 行，与 5707E0 同构：558090 分隔 + 572570/5726C0 行组装 + 55A010）
  *uArg2 = *(this + 1) + 40 * v6;  // *uArg2 写入 *(this + 1) + 40 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x572A90 sub_572A90 —— 绘制链中层 2（572A20 + 572620）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_572A90(int this, int *pDwArg2)  // 实现：绘制链中层 2（572A20 + 572620）
{
  int pVecEnd_8; // edi
  unsigned int fld_8; // ecx
  int fld_82; // edi
  uint32_t *result; // eax

  pVecEnd_8 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  if ( pVecEnd_8 != 0 )  // 若 fld_4 非 0
    fld_8 = (*(uint32_t *)(this + 8) - pVecEnd_8) / 40;
  else  // 否则分支
    fld_8 = 0;
  if ( pVecEnd_8 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - pVecEnd_8) / 40 )  // 若 pVecEnd_8 == 0
    return sub_572A20((int *)this, &pDwArg2, *(char **)(this + 8), pDwArg2);  // 绘制链中层（转发 5726F0）
  fld_82 = *(uint32_t *)(this + 8);  // fld_82 = 读 this+8
  result = (uint32_t *)sub_572620(fld_82, 1, pDwArg2);  // 转发 572450（第二挂点）
  *(uint32_t *)(this + 8) = fld_82 + 40;  // this+8 = fld_82 + 40
  return result;
}



// ------------------------------------------------------------
// 0x572B20 sub_572B20 —— 绘制链中层 3（4015C0 + 572A90）
// ------------------------------------------------------------
void /*thiscall*/ sub_572B20(void *this, int nArg2, void *Src, int nArg4, int nArg5)  // 实现：绘制链中层 3（4015C0 + 572A90）
{
  int v6[3]; // [esp+Ch] [ebp-38h] BYREF
  void *Block; // [esp+1Ch] [ebp-28h]
  int v8; // [esp+2Ch] [ebp-18h]
  unsigned int v9; // [esp+30h] [ebp-14h]
  int dword_796E502; // [esp+34h] [ebp-10h]
  int v11; // [esp+40h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  v6[0] = nArg2;
  v6[2] = nArg5;
  v11 = 0;
  v6[1] = nArg4;
  sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  sub_572A90((int)this + 36, v6);  // 绘制链中层 2（572A20 + 572620）
  if ( v9 >= 0x10 )  // 若 v9 >= 0x10
    j__free(Block);  // 调 j__free
}



// ------------------------------------------------------------
// 0x572BC0 sub_572BC0 —— 物品信息窗部件构建（186 行：416C40/406D00/4164C0 文本块装配）
// ------------------------------------------------------------
int /*cdecl*/ sub_572BC0(const char *pArg1, int nArg2, int nArg3)  // 实现：物品信息窗部件构建（186 行：416C40/406D00/4164C0 文本块装配）
{
  int v3; // esi
  int v5; // ebx
  int v6; // edi
  char v7; // al
  int16_t v8; // cx
  void **Block4; // eax
  unsigned int v10; // eax
  void **Block5; // ecx
  void **Block2; // ecx
  unsigned int v13; // ecx
  void **Block3; // eax
  void **Block6; // eax
  unsigned int v16; // eax
  void **Block7; // ecx
  int v18; // [esp+4h] [ebp-3Ch] BYREF
  int nLen; // [esp+8h] [ebp-38h]
  int16_t v20; // [esp+Ch] [ebp-34h] BYREF
  char v21; // [esp+Eh] [ebp-32h]
  int v22; // [esp+10h] [ebp-30h]
  size_t v23; // [esp+14h] [ebp-2Ch] BYREF
  void *Block[4]; // [esp+18h] [ebp-28h] BYREF
  int v25; // [esp+28h] [ebp-18h]
  unsigned int v26; // [esp+2Ch] [ebp-14h]
  int dword_796E502; // [esp+30h] [ebp-10h]
  int v28; // [esp+3Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  v3 = 0;
  if ( pArg1 == nullptr )  // 若 pArg1 为空
    return 0;
  --nArg2;  // 自减nArg2
  v26 = 15;
  v25 = 0;
  LOBYTE(Block[0]) = 0;
  v28 = 0;
  v22 = 1;
  v5 = 0;
  nLen = strlen(pArg1);  // nLen = 调 strlen
  if ( nLen > 0 )  // 若 nLen > 0
  {
    v6 = 1;
    do  // do-while 循环体起点
    {
      v7 = pArg1[v3];  // v7 = 取 pArg1[v3]
      if ( v7 < 0  // 若 v7 < 0
        && (v7 == -127
         || v7 == -126
         || v7 == -125
         || v7 == -124
         || v7 == -121
         || v7 == -120
         || v7 == -119
         || v7 == -118
         || v7 == -117
         || v7 == -116
         || v7 == -115
         || v7 == -114
         || v7 == -113
         || v7 == -112
         || v7 == -111
         || v7 == -110
         || v7 == -109
         || v7 == -108
         || v7 == -107
         || v7 == -106
         || v7 == -105
         || v7 == -104
         || v7 == -103
         || v7 == -102
         || v7 == -101
         || v7 == -100
         || v7 == -99
         || v7 == -98
         || v7 == -97
         || v7 == -32
         || v7 == -31
         || v7 == -30
         || v7 == -29
         || v7 == -28
         || v7 == -27
         || v7 == -26
         || v7 == -25
         || v7 == -24
         || v7 == -23
         || v7 == -22
         || v7 == -19
         || v7 == -18
         || v7 == -6
         || v7 == -5
         || v7 == -4) )
      {
        v8 = *(uint16_t *)&pArg1[v3];
        v21 = 0;
        v20 = v8;
        sub_4022F0((std::_String_base *)&v23, (int)&v20, (char *)&v20, strlen((const char *)&v20));  // std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
        ++v3;  // 自增v3
        ++v6;  // 自增v6
        ++v5;  // 自增v5
      }
      else  // 否则分支
      {
        if ( v7 == 10 || v6 < nLen && (v7 == 13 && pArg1[v3 + 1] == 10 || v7 == 92 && pArg1[v3 + 1] == 110) )  // 若 v7 == 10 与/或 v6 < nLen 与/或 v7 == 13
        {
          if ( nArg3 != 0 )  // 若 nArg3 非 0
          {
            ++v3;  // 自增v3
            ++v6;  // 自增v6
            sub_5724C0();  // 信息窗共用
            sub_416C40(nArg3, &v23);  // 尾插一条 28B 记录（满则走插入路径）
            Block2 = (void **)Block[0];
            if ( v26 < 0x10 )  // 若 v26 < 0x10
              Block2 = Block;
            v13 = (unsigned int)Block2 + v25;
            Block3 = (void **)Block[0];
            if ( v26 < 0x10 )  // 若 v26 < 0x10
              Block3 = Block;
            sub_406D00(&v23, &v18, (int)Block3, v13);  // std::string 中段擦除（·sub_401230 erase，pos 与 n 由指针差换算）
          }
          goto LABEL_72;  // 跳转 LABEL_72
        }
        sub_4164C0(&v23, 1u, v7);  // 【string/vector 容器工具】
      }
      if ( ++v5 >= nArg2 )  // 若 ++v5 >= nArg2
      {
        if ( nArg3 != 0 )  // 若 nArg3 非 0
        {
          sub_5724C0();  // 信息窗共用
          sub_416C40(nArg3, &v23);  // 尾插一条 28B 记录（满则走插入路径）
          Block4 = (void **)Block[0];
          if ( v26 < 0x10 )  // 若 v26 < 0x10
            Block4 = Block;
          v10 = (unsigned int)Block4 + v25;
          Block5 = (void **)Block[0];
          if ( v26 < 0x10 )  // 若 v26 < 0x10
            Block5 = Block;
          sub_406D00(&v23, &v18, (int)Block5, v10);  // std::string 中段擦除（·sub_401230 erase，pos 与 n 由指针差换算）
        }
LABEL_72:  // 标签 LABEL_72（跳转合流点）
        v5 = 0;
        ++v22;  // 自增v22
      }
      ++v3;  // 自增v3
      ++v6;  // 自增v6
    }
    while ( v3 < nLen );  // 条件循环
  }
  if ( nLen != 0 )  // 若 nLen 非 0
  {
    if ( nArg3 != 0 )  // 若 nArg3 非 0
    {
      if ( v25 != 0 )  // 若 v25 非 0
      {
        sub_5724C0();  // 信息窗共用
        sub_416C40(nArg3, &v23);  // 尾插一条 28B 记录（满则走插入路径）
        Block6 = (void **)Block[0];
        if ( v26 < 0x10 )  // 若 v26 < 0x10
          Block6 = Block;
        v16 = (unsigned int)Block6 + v25;
        Block7 = (void **)Block[0];
        if ( v26 < 0x10 )  // 若 v26 < 0x10
          Block7 = Block;
        sub_406D00(&v23, &pArg1, (int)Block7, v16);  // std::string 中段擦除（·sub_401230 erase，pos 与 n 由指针差换算）
      }
      else  // 否则分支
      {
        --v22;  // 自减v22
      }
    }
    if ( v26 >= 0x10 )  // 若 v26 >= 0x10
      j__free(Block[0]);  // 调 j__free
    return v22;
  }
  else  // 否则分支
  {
    if ( v26 >= 0x10 )  // 若 v26 >= 0x10
      j__free(Block[0]);  // 调 j__free
    return 0;
  }
}


// ------------------------------------------------------------
// 0x572EF0 sub_572EF0 —— 物品信息窗绘制主函数（725 行：497040 属性枚举 + 571B80/572BC0/572B20 分支 + 47E720 说明）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_572EF0(void *this, int pArg2, int nArg3, int *pDwArg4, int nArg5, int nArg6)  // 实现：物品信息窗绘制主函数（725 行：497040 属性枚举 + 571B80/572BC0/572B20 分支 + 47E720 说明）
{
  int nArg32; // ebx
  int v9; // eax
  char *v10; // eax
  int v11; // eax
  char *v12; // eax
  char *v13; // eax
  char *v14; // eax
  char *v15; // eax
  char *v16; // eax
  char *v17; // eax
  char *v18; // eax
  char *v19; // eax
  char *v20; // eax
  char *v21; // eax
  char *v22; // eax
  char *v23; // eax
  char *v24; // eax
  char *v25; // eax
  char *v26; // eax
  double v27; // st7
  char *v28; // eax
  char *v29; // eax
  char *v30; // eax
  char *v31; // eax
  char *v32; // eax
  int v33; // eax
  unsigned int v34; // ecx
  char *v35; // eax
  char *v36; // eax
  int v37; // eax
  unsigned int v38; // ecx
  char *v39; // eax
  char *v40; // eax
  int v41; // eax
  unsigned int v42; // ecx
  char *v43; // eax
  char *v44; // eax
  char *v45; // eax
  char *v46; // eax
  char *v47; // eax
  char *v48; // eax
  char *v49; // eax
  char *v50; // eax
  bool v51; // cc
  char *v52; // eax
  char *v53; // eax
  char *v54; // eax
  int v55; // eax
  int v56; // eax
  int v57; // et2
  char *v58; // eax
  char *v59; // eax
  char *v60; // eax
  int v61; // eax
  char *v62; // eax
  int v63; // eax
  int v64; // eax
  uint32_t *v65; // ecx
  bool v66; // zf
  uint32_t *v67; // ebx
  uint32_t *v68; // ecx
  char *v69; // eax
  char *v70; // eax
  char *v71; // eax
  char *v72; // eax
  double v73; // st7
  char *v74; // eax
  int nArg322; // eax
  char *v76; // eax
  char *v77; // eax
  char *v78; // eax
  char *v79; // eax
  char *v80; // eax
  uint32_t *result; // eax
  int v82; // eax
  char *v83; // eax
  int v84; // [esp-4h] [ebp-C0h]
  int v85; // [esp-4h] [ebp-C0h]
  int v86; // [esp-4h] [ebp-C0h]
  int v87; // [esp-4h] [ebp-C0h]
  double v88; // [esp+0h] [ebp-BCh]
  double v89; // [esp+0h] [ebp-BCh]
  double v90; // [esp+0h] [ebp-BCh]
  double v91; // [esp+0h] [ebp-BCh]
  int v92; // [esp+0h] [ebp-BCh]
  int v93; // [esp+0h] [ebp-BCh]
  int v94; // [esp+0h] [ebp-BCh]
  const char *future_error_what; // [esp+0h] [ebp-BCh]
  char *v96; // [esp+0h] [ebp-BCh]
  char *v97; // [esp+0h] [ebp-BCh]
  double v98; // [esp+0h] [ebp-BCh]
  double v99; // [esp+0h] [ebp-BCh]
  double v100; // [esp+0h] [ebp-BCh]
  double v101; // [esp+0h] [ebp-BCh]
  int v102; // [esp+0h] [ebp-BCh]
  int v103; // [esp+4h] [ebp-B8h]
  int v104; // [esp+4h] [ebp-B8h]
  int v105; // [esp+4h] [ebp-B8h]
  int v106; // [esp+4h] [ebp-B8h]
  int v107; // [esp+4h] [ebp-B8h]
  int v108; // [esp+4h] [ebp-B8h]
  int v109; // [esp+4h] [ebp-B8h]
  int v110; // [esp+4h] [ebp-B8h]
  int v111; // [esp+4h] [ebp-B8h]
  int v112; // [esp+4h] [ebp-B8h]
  int v113; // [esp+4h] [ebp-B8h]
  int v114; // [esp+4h] [ebp-B8h]
  int v115; // [esp+4h] [ebp-B8h]
  int v116; // [esp+4h] [ebp-B8h]
  int v117; // [esp+4h] [ebp-B8h]
  int v118; // [esp+4h] [ebp-B8h]
  int v119; // [esp+4h] [ebp-B8h]
  int v120; // [esp+4h] [ebp-B8h]
  int v121; // [esp+4h] [ebp-B8h]
  int v122; // [esp+4h] [ebp-B8h]
  int v123; // [esp+4h] [ebp-B8h]
  int v124; // [esp+4h] [ebp-B8h]
  int v125; // [esp+4h] [ebp-B8h]
  int v126; // [esp+4h] [ebp-B8h]
  int v127; // [esp+4h] [ebp-B8h]
  int v128; // [esp+4h] [ebp-B8h]
  int v129; // [esp+4h] [ebp-B8h]
  int v130; // [esp+4h] [ebp-B8h]
  int v131; // [esp+4h] [ebp-B8h]
  char v132[4]; // [esp+14h] [ebp-A8h] BYREF
  void *Block; // [esp+18h] [ebp-A4h]
  uint32_t *v134; // [esp+1Ch] [ebp-A0h]
  int v135; // [esp+20h] [ebp-9Ch]
  int v136; // [esp+24h] [ebp-98h]
  int v137; // [esp+28h] [ebp-94h]
  char Buffer[128]; // [esp+2Ch] [ebp-90h] BYREF
  int dword_796E502; // [esp+ACh] [ebp-10h]
  int v140; // [esp+B8h] [ebp-4h]
  uint32_t *i; // [esp+C8h] [ebp+Ch]
  int v142; // [esp+CCh] [ebp+10h]
  int v143; // [esp+CCh] [ebp+10h]
  int v144; // [esp+CCh] [ebp+10h]
  int v145; // [esp+CCh] [ebp+10h]
  int v146; // [esp+CCh] [ebp+10h]
  int v147; // [esp+CCh] [ebp+10h]
  int v148; // [esp+CCh] [ebp+10h]
  unsigned int v149; // [esp+CCh] [ebp+10h]
  int v150; // [esp+CCh] [ebp+10h]
  int v151; // [esp+CCh] [ebp+10h]
  char *v152; // [esp+CCh] [ebp+10h]
  int v153; // [esp+D4h] [ebp+18h]
  int v154; // [esp+D4h] [ebp+18h]

  dword_796E502 = dword_796E50;
  nArg32 = nArg3;
  if ( sub_41A5E0(pArg2 + 14) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v9 = sub_41A5E0(pArg2 + 14);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sprintf(Buffer, "HP MAX %+d", v9);  // 拼字符串（模板 HP MAX %+d）
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 630) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v88 = (double)sub_41A5E0(pArg2 + 630) * 0.59999996;  // crypt4byte 解密校验（·0x41A590 逆运算）
    v10 = sub_422E70(1063);  // v10 = 调 sub_422E70 返回值
    sprintf(Buffer, v10, v88);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 28) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v11 = sub_41A5E0(pArg2 + 28);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sprintf(Buffer, "MP MAX %+d", v11);  // 拼字符串（模板 MP MAX %+d）
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 644) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v89 = (double)sub_41A5E0(pArg2 + 644) * 3.0;  // crypt4byte 解密校验（·0x41A590 逆运算）
    v12 = sub_422E70(1064);  // v12 = 调 sub_422E70 返回值
    sprintf(Buffer, v12, v89);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(pArg2 + 658)) != 0.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v90 = COERCE_FLOAT(sub_41A5E0(pArg2 + 658));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v13 = sub_422E70(1065);  // v13 = 调 sub_422E70 返回值
    sprintf(Buffer, v13, v90);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 112) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( sub_41A5E0(pArg2 + 168) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v142 = sub_41A5E0(pArg2 + 168);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v136 = sub_41A5E0(pArg2 + 112);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v137 = sub_41A5E0(pArg2 + 168);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v84 = sub_41A5E0(pArg2 + 112);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v14 = sub_422E70(1665);  // v14 = 调 sub_422E70 返回值
      sprintf(Buffer, v14, v84, v136 - v137, v142);  // 拼字符串
    }
    else  // 否则分支
    {
      v103 = sub_41A5E0(pArg2 + 112);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v15 = sub_422E70(1066);  // v15 = 调 sub_422E70 返回值
      sprintf(Buffer, v15, v103);  // 拼字符串
    }
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 224) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v104 = sub_41A5E0(pArg2 + 224);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v16 = sub_422E70(2041);  // v16 = 调 sub_422E70 返回值
    sprintf(Buffer, v16, v104);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 126) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( sub_41A5E0(pArg2 + 182) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v143 = sub_41A5E0(pArg2 + 182);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v137 = sub_41A5E0(pArg2 + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v136 = sub_41A5E0(pArg2 + 182);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v85 = sub_41A5E0(pArg2 + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v17 = sub_422E70(1666);  // v17 = 调 sub_422E70 返回值
      sprintf(Buffer, v17, v85, v137 - v136, v143);  // 拼字符串
    }
    else  // 否则分支
    {
      v105 = sub_41A5E0(pArg2 + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v18 = sub_422E70(1067);  // v18 = 调 sub_422E70 返回值
      sprintf(Buffer, v18, v105);  // 拼字符串
    }
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 238) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v106 = sub_41A5E0(pArg2 + 238);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v19 = sub_422E70(2043);  // v19 = 调 sub_422E70 返回值
    sprintf(Buffer, v19, v106);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(pArg2 + 252)) != 0.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v91 = COERCE_FLOAT(sub_41A5E0(pArg2 + 252));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v20 = sub_422E70(2045);  // v20 = 调 sub_422E70 返回值
    sprintf(Buffer, v20, v91);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 140) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( sub_41A5E0(pArg2 + 196) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v144 = sub_41A5E0(pArg2 + 196);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v137 = sub_41A5E0(pArg2 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v136 = sub_41A5E0(pArg2 + 196);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v86 = sub_41A5E0(pArg2 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v21 = sub_422E70(1667);  // v21 = 调 sub_422E70 返回值
      sprintf(Buffer, v21, v86, v137 - v136, v144);  // 拼字符串
    }
    else  // 否则分支
    {
      v107 = sub_41A5E0(pArg2 + 140);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v22 = sub_422E70(1068);  // v22 = 调 sub_422E70 返回值
      sprintf(Buffer, v22, v107);  // 拼字符串
    }
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 266) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v108 = sub_41A5E0(pArg2 + 266);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v23 = sub_422E70(2042);  // v23 = 调 sub_422E70 返回值
    sprintf(Buffer, v23, v108);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 154) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    if ( sub_41A5E0(pArg2 + 210) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v145 = sub_41A5E0(pArg2 + 210);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v137 = sub_41A5E0(pArg2 + 154);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v136 = sub_41A5E0(pArg2 + 210);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v87 = sub_41A5E0(pArg2 + 154);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v24 = sub_422E70(1668);  // v24 = 调 sub_422E70 返回值
      sprintf(Buffer, v24, v87, v137 - v136, v145);  // 拼字符串
    }
    else  // 否则分支
    {
      v109 = sub_41A5E0(pArg2 + 154);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v25 = sub_422E70(1069);  // v25 = 调 sub_422E70 返回值
      sprintf(Buffer, v25, v109);  // 拼字符串
    }
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 280) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v110 = sub_41A5E0(pArg2 + 280);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v26 = sub_422E70(2044);  // v26 = 调 sub_422E70 返回值
    sprintf(Buffer, v26, v110);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  v27 = 0.0;
  if ( COERCE_FLOAT(sub_41A5E0(pArg2 + 294)) != 0.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v27 = COERCE_FLOAT(sub_41A5E0(pArg2 + 294));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v28 = sub_422E70(2046);  // v28 = 调 sub_422E70 返回值
    sprintf(Buffer, v28, v27);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 42) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v111 = sub_41A5E0(pArg2 + 42);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v29 = sub_422E70(1070);  // v29 = 调 sub_422E70 返回值
    sprintf(Buffer, v29, v111);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 56) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v112 = sub_41A5E0(pArg2 + 56);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v30 = sub_422E70(1071);  // v30 = 调 sub_422E70 返回值
    sprintf(Buffer, v30, v112);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 70) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v113 = sub_41A5E0(pArg2 + 70);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v31 = sub_422E70(1072);  // v31 = 调 sub_422E70 返回值
    sprintf(Buffer, v31, v113);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 98) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v114 = sub_41A5E0(pArg2 + 98);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v32 = sub_422E70(1073);  // v32 = 调 sub_422E70 返回值
    sprintf(Buffer, v32, v114);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 686) != 0 && nArg6 != 8 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v33 = sub_41A5E0(pArg2 + 686);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v34 = pArg2 + 686;
    if ( v33 % 10 != 0 )  // 若 v33 % 10 != 0
    {
      v146 = sub_41A5E0(v34);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v92 = sub_41A5E0(pArg2 + 686) / 10;  // crypt4byte 解密校验（·0x41A590 逆运算）
      v36 = sub_422E70(1075);  // v36 = 调 sub_422E70 返回值
      sprintf(Buffer, v36, v92, abs32(v146 % 10));  // 拼字符串
    }
    else  // 否则分支
    {
      v115 = sub_41A5E0(v34) / 10;  // crypt4byte 解密校验（·0x41A590 逆运算）
      v35 = sub_422E70(1074);  // v35 = 调 sub_422E70 返回值
      sprintf(Buffer, v35, v115);  // 拼字符串
    }
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 672) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v37 = sub_41A5E0(pArg2 + 672);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v38 = pArg2 + 672;
    if ( v37 % 10 != 0 )  // 若 v37 % 10 != 0
    {
      v147 = sub_41A5E0(v38);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v93 = sub_41A5E0(pArg2 + 672) / 10;  // crypt4byte 解密校验（·0x41A590 逆运算）
      v40 = sub_422E70(1077);  // v40 = 调 sub_422E70 返回值
      sprintf(Buffer, v40, v93, abs32(v147 % 10));  // 拼字符串
    }
    else  // 否则分支
    {
      v116 = sub_41A5E0(v38) / 10;  // crypt4byte 解密校验（·0x41A590 逆运算）
      v39 = sub_422E70(1076);  // v39 = 调 sub_422E70 返回值
      sprintf(Buffer, v39, v116);  // 拼字符串
    }
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 700) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v41 = sub_41A5E0(pArg2 + 700);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v42 = pArg2 + 700;
    if ( v41 % 10 != 0 )  // 若 v41 % 10 != 0
    {
      v148 = sub_41A5E0(v42);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v94 = sub_41A5E0(pArg2 + 700) / 10;  // crypt4byte 解密校验（·0x41A590 逆运算）
      v44 = sub_422E70(1079);  // v44 = 调 sub_422E70 返回值
      sprintf(Buffer, v44, v94, abs32(v148 % 10));  // 拼字符串
    }
    else  // 否则分支
    {
      v117 = sub_41A5E0(v42) / 10;  // crypt4byte 解密校验（·0x41A590 逆运算）
      v43 = sub_422E70(1078);  // v43 = 调 sub_422E70 返回值
      sprintf(Buffer, v43, v117);  // 拼字符串
    }
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 308) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v118 = sub_41A5E0(pArg2 + 308);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v45 = sub_422E70(1080);  // v45 = 调 sub_422E70 返回值
    sprintf(Buffer, v45, v118);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 322) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v119 = sub_41A5E0(pArg2 + 322);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v46 = sub_422E70(1081);  // v46 = 调 sub_422E70 返回值
    sprintf(Buffer, v46, v119);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 350) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v120 = sub_41A5E0(pArg2 + 350);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v47 = sub_422E70(1082);  // v47 = 调 sub_422E70 返回值
    sprintf(Buffer, v47, v120);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 336) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v121 = sub_41A5E0(pArg2 + 336);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v48 = sub_422E70(1083);  // v48 = 调 sub_422E70 返回值
    sprintf(Buffer, v48, v121);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 364) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v122 = sub_41A5E0(pArg2 + 364);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v49 = sub_422E70(1084);  // v49 = 调 sub_422E70 返回值
    sprintf(Buffer, v49, v122);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  v153 = 0;
  v149 = pArg2 + 378;
  do  // do-while 循环体起点
  {
    if ( sub_41A5E0(v149) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      v137 = sub_497040(v153);  // 状态号映射表（12 直通、14→15、15→16，其余→17）
      if ( v137 != 17 )  // 若 v137 != 17
      {
        v123 = sub_41A5E0(v149);  // crypt4byte 解密校验（·0x41A590 逆运算）
        future_error_what = std::_Get_future_error_what(v137);  // future_error_what = 调 std::_Get_future_error_what
        v50 = sub_422E70(1085);  // v50 = 调 sub_422E70 返回值
        sprintf(Buffer, v50, future_error_what, v123);  // 拼字符串
        sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
        ++*pDwArg4;
      }
    }
    v51 = ++v153 < 16;
    v149 += 14;
  }
  while ( v51 );  // 条件循环
  if ( sub_41A5E0(pArg2 + 602) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v124 = sub_41A5E0(pArg2 + 602);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v52 = sub_422E70(1086);  // v52 = 调 sub_422E70 返回值
    sprintf(Buffer, v52, v124);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 546) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v125 = sub_41A5E0(pArg2 + 546);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v53 = sub_422E70(1087);  // v53 = 调 sub_422E70 返回值
    sprintf(Buffer, v53, v125);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 560) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v27 = (double)sub_41A5E0(pArg2 + 560) * 0.1;  // crypt4byte 解密校验（·0x41A590 逆运算）
    v54 = sub_422E70(1088);  // v54 = 调 sub_422E70 返回值
    sprintf(Buffer, v54, v27);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 616) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v55 = sub_41A5E0(pArg2 + 616);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v136 = v55;
    if ( v55 != 0 )  // 若 v55 非 0
    {
      v57 = v55 % 1000;
      v56 = v55 / 1000;
      v150 = v57;
      if ( v57 != 0 )  // 若 v57 非 0
      {
        if ( v136 % 100 != 0 )  // 若 v136 % 100 != 0
        {
          if ( v136 % 10 != 0 )  // 若 v136 % 10 != 0
            sprintf(&byte_9B8994, "+%d.%03dkg", v56, abs32(v150));  // 拼字符串（模板 +%d.%03dkg）
          else  // 否则分支
            sprintf(&byte_9B8994, "%+d.%02dkg", v56, abs32(v150 / 10));  // 拼字符串（模板 %+d.%02dkg）
        }
        else  // 否则分支
        {
          sprintf(&byte_9B8994, "%+d.%dkg", v56, abs32(v150 / 100));  // 拼字符串（模板 %+d.%dkg）
        }
      }
      else  // 否则分支
      {
        sprintf(&byte_9B8994, "%+dkg", v56);  // 拼字符串（模板 %+dkg）
      }
      v55 = (int)&byte_9B8994;
    }
    v126 = v55;
    v58 = sub_422E70(1089);  // v58 = 调 sub_422E70 返回值
    sprintf(Buffer, v58, v126);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 714) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v127 = sub_41A5E0(pArg2 + 714);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v59 = sub_422E70(1090);  // v59 = 调 sub_422E70 返回值
    sprintf(Buffer, v59, v127);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 728) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v128 = sub_41A5E0(pArg2 + 728);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v60 = sub_422E70(1091);  // v60 = 调 sub_422E70 返回值
    sprintf(Buffer, v60, v128);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  v61 = *(uint32_t *)(pArg2 + 772);  // v61 = pArg2+772
  if ( v61 != 4 )  // 若 v61 != 4
  {
    switch ( v61 )  // 按 v61 分派
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        v62 = sub_422E70(1092);  // v62 = 调 sub_422E70 返回值
LABEL_112:  // 标签 LABEL_112（跳转合流点）
        sprintf(Buffer, v62);  // 拼字符串
        break;  // 跳出循环/分支
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        v96 = sub_422E70(1093);  // v96 = 调 sub_422E70 返回值
        sprintf(Buffer, v96);  // 拼字符串
        break;  // 跳出循环/分支
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        v97 = sub_422E70(1094);  // v97 = 调 sub_422E70 返回值
        sprintf(Buffer, v97);  // 拼字符串
        break;  // 跳出循环/分支
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        v62 = sub_422E70(1095);  // v62 = 调 sub_422E70 返回值
        goto LABEL_112;  // 跳转 LABEL_112
      default:  // 默认分支
        break;  // 跳出循环/分支
    }
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( *(uint32_t *)(pArg2 + 776) != 17 )  // 若 *(uint32_t *)(pArg2 + 776) != 17
  {
    v151 = sub_41A5E0(pArg2 + 794);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v63 = sub_41A5E0(pArg2 + 780);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_571B80(v27, *(uint32_t *)(pArg2 + 776), *(float *)&v63, v151, Buffer);  // 物品属性文本组装（135 行：497120/4971B0/497150 属性枚举）
    Block = nullptr;  // Block = 空指针
    v134 = nullptr;  // v134 = 空指针
    v135 = 0;
    v140 = 0;
    v64 = sub_572BC0(Buffer, 34, v132);  // 物品信息窗部件构建（186 行：416C40/406D00/4164C0 文本块装配）
    if ( v64 > 0 )  // 若 v64 > 0
    {
      v65 = (char *)Block + 4;
      v152 = (char *)Block + 4;
      v154 = v64;
      while ( 1 )  // 条件循环
      {
        if ( v65[5] >= 0x10u )  // 若 v65[5] >= 0x10u
          v65 = (uint32_t *)*v65;
        sub_572B20(*pDwArg4, v65, (int)this + 52, nArg3);  // 绘制链中层 3（4015C0 + 572A90）
        v66 = v154 == 1;
        ++*pDwArg4;
        v152 += 28;
        --v154;  // 自减v154
        if ( v66 )  // 若 v66
          break;  // 跳出循环/分支
        v65 = v152;
      }
    }
    v140 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
    {
      if ( Block != v134 )  // 若 Block != v134
      {
        v67 = (char *)Block + 24;
        do  // do-while 循环体起点
        {
          if ( *v67 >= 0x10u )  // 若 *v67 >= 0x10u
            j__free((void *)*(v67 - 5));  // 调 j__free
          v68 = v134;
          *v67 = 15;  // *v67 写入 15
          *(v67 - 1) = 0;
          *((uint8_t *)v67 - 20) = 0;
          v67 += 7;
        }
        while ( v67 - 6 != v68 );  // 条件循环
        nArg32 = nArg3;
      }
      j__free(Block);  // 调 j__free
    }
  }
  if ( sub_41A5E0(pArg2 + 808) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v129 = sub_41A5E0(pArg2 + 808);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v69 = sub_422E70(1096);  // v69 = 调 sub_422E70 返回值
    sprintf(Buffer, v69, v129);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg32);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( sub_41A5E0(pArg2 + 822) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v130 = sub_41A5E0(pArg2 + 822);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v70 = sub_422E70(1097);  // v70 = 调 sub_422E70 返回值
    sprintf(Buffer, v70, v130);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg32);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(pArg2 + 742)) != 0.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v98 = COERCE_FLOAT(sub_41A5E0(pArg2 + 742));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v71 = sub_422E70(2107);  // v71 = 调 sub_422E70 返回值
    sprintf(Buffer, v71, v98);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg32);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(pArg2 + 756)) != 0.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v99 = COERCE_FLOAT(sub_41A5E0(pArg2 + 756));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v72 = sub_422E70(2108);  // v72 = 调 sub_422E70 返回值
    sprintf(Buffer, v72, v99);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg32);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(pArg2 + 836)) != 0.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v73 = COERCE_FLOAT(sub_41A5E0(pArg2 + 836));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v74 = sub_422E70(1099);  // v74 = 调 sub_422E70 返回值
    sprintf(Buffer, v74, v73);  // 拼字符串
    nArg322 = -5468241;
    if ( v73 <= 0.0 )  // 若 v73 <= 0.0
      nArg322 = nArg32;
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg322);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( *(uint8_t *)(pArg2 + 879) != 0 )  // 若 *(uint8_t *)(pArg2 + 879) != 0
  {
    v76 = sub_422E70(1100);  // v76 = 调 sub_422E70 返回值
    sub_572B20(*pDwArg4, v76, (int)this + 52, nArg32);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( *(uint8_t *)(pArg2 + 880) != 0 )  // 若 *(uint8_t *)(pArg2 + 880) != 0
  {
    v77 = sub_422E70(1101);  // v77 = 调 sub_422E70 返回值
    sub_572B20(*pDwArg4, v77, (int)this + 52, nArg32);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( *(uint8_t *)(pArg2 + 850) != 0 )  // 若 *(uint8_t *)(pArg2 + 850) != 0
  {
    v78 = sub_422E70(1102);  // v78 = 调 sub_422E70 返回值
    sub_572B20(*pDwArg4, v78, (int)this + 52, nArg32);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(pArg2 + 851)) != 0.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v100 = COERCE_FLOAT(sub_41A5E0(pArg2 + 851));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v79 = sub_422E70(2105);  // v79 = 调 sub_422E70 返回值
    sprintf(Buffer, v79, v100);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg32);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(pArg2 + 865)) != 0.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v101 = COERCE_FLOAT(sub_41A5E0(pArg2 + 865));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v80 = sub_422E70(2106);  // v80 = 调 sub_422E70 返回值
    sprintf(Buffer, v80, v101);  // 拼字符串
    sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg32);  // 绘制链中层 3（4015C0 + 572A90）
    ++*pDwArg4;
  }
  result = *(uint32_t **)(pArg2 + 888);
  for ( i = result; i != *(uint32_t **)(pArg2 + 892); i += 8 )  // 遍历循环
  {
    v82 = sub_41A5E0((unsigned int)(i + 1));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v137 = sub_47E720(*i, v82);  // v137 = 调 sub_47E720 返回值
    if ( v137 != 0 )  // 若 v137 非 0
    {
      v131 = sub_41A5E0((unsigned int)i + 18);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v102 = sub_41ACF0(v137 + 20);  // 驻留串句柄 → 字符串指针
      v83 = sub_422E70(1103);  // v83 = 调 sub_422E70 返回值
      sprintf(Buffer, v83, v102, v131);  // 拼字符串
      sub_572B20(*pDwArg4, Buffer, (int)this + 52, nArg32);  // 绘制链中层 3（4015C0 + 572A90）
      ++*pDwArg4;
    }
    result = i + 8;
  }
  return result;
}


// ------------------------------------------------------------
// 0x5745B0 sub_5745B0 —— 物品信息窗完整绘制（1226 行·全文件最大：5486B0/541A30/542AB0 各类型说明 + 406D60/402410 文本 + 572EF0 收尾）
// ------------------------------------------------------------
char /*userpurge*/ sub_5745B0@<al>(int *pDwArg1@<ecx>, int nArg2@<edi>, void **pArg3)  // 实现：物品信息窗完整绘制（1226 行·全文件最大：5486B0/541A30/542AB0 各类型说明 + 406D60/402410 文本 +…
{
  uint8_t *pObj4; // eax
  int (/*thiscall*/ **v6)(void **, uint32_t); // eax
  void *v7; // eax
  int v8; // eax
  void **v9; // eax
  int v10; // eax
  int v11; // eax
  void *v12; // eax
  void **v13; // ebx
  int v14; // eax
  void **v15; // eax
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // et2
  int v21; // eax
  char v22; // cl
  int (/*thiscall*/ **v23)(void **); // eax
  int v24; // eax
  void *v25; // eax
  int v26; // eax
  void **Block2; // eax
  int v28; // eax
  void *v29; // eax
  const char *psz; // eax
  int (/*thiscall*/ **v31)(void **); // edx
  int v32; // eax
  void *v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // eax
  void *v37; // eax
  uint8_t *pObj7; // eax
  int v39; // eax
  int v40; // ecx
  int v41; // eax
  int v42; // eax
  uint32_t *v43; // eax
  int v44; // edx
  int v45; // eax
  int v46; // eax
  const char *v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // eax
  int v52; // eax
  int v53; // eax
  int v54; // eax
  const char *v55; // eax
  char v56; // al
  int v57; // eax
  int v58; // eax
  int v59; // eax
  void *v60; // eax
  int v61; // eax
  const char *v62; // eax
  int v63; // eax
  void *v64; // eax
  const char *v65; // eax
  void *v66; // eax
  const char *v67; // eax
  void *v68; // eax
  int v69; // ebx
  int v70; // eax
  int v71; // edx
  int v72; // eax
  const char *v73; // eax
  const char *v74; // eax
  int v75; // eax
  int v76; // eax
  uint32_t *v77; // eax
  int v78; // eax
  const char *v79; // eax
  uint32_t *v80; // eax
  int v81; // eax
  int v82; // eax
  int v83; // eax
  int v84; // eax
  int v85; // edi
  int v86; // eax
  const char *v87; // eax
  int v88; // eax
  uint8_t *pObj6; // edi
  int v90; // edx
  int v91; // eax
  int v92; // edi
  int v93; // eax
  int v94; // ebx
  void *v95; // eax
  int v96; // ebx
  unsigned int v97; // edi
  int v98; // eax
  uint32_t *v99; // eax
  char *v100; // eax
  void *v101; // eax
  char *v102; // edi
  void *v103; // ecx
  uint32_t *v104; // edi
  uint32_t *v105; // eax
  void *v106; // eax
  unsigned int v107; // eax
  int v108; // ebx
  void *v109; // eax
  int v110; // ebx
  int v111; // edi
  int v112; // ecx
  int v113; // eax
  int (/*thiscall*/ **v114)(void **); // edx
  int v115; // eax
  int v116; // eax
  void *v117; // eax
  char *v118; // esi
  void *v119; // eax
  int *v120; // edi
  char *v121; // eax
  int v122; // eax
  uint32_t *v123; // esi
  uint32_t *v124; // eax
  uint8_t *pObj2; // esi
  int v126; // edx
  int v127; // eax
  int v128; // eax
  int v129; // edi
  int v130; // ecx
  int v131; // eax
  int v132; // edi
  int pObj; // eax
  int *v134; // esi
  int v135; // eax
  int v136; // edx
  int v137; // eax
  int v138; // esi
  int *v139; // edi
  void *v140; // eax
  int v141; // eax
  int v142; // eax
  int v143; // edi
  int pObj5; // esi
  int v145; // eax
  bool v146; // zf
  int v147; // eax
  void *v148; // eax
  int *v149; // eax
  void *pObj8; // esi
  int v151; // eax
  void *v152; // eax
  void **Block3; // eax
  void *v154; // eax
  char *v155; // esi
  void *v156; // eax
  int *v157; // edi
  char *v158; // eax
  int v159; // eax
  uint32_t *v160; // edi
  uint32_t *v161; // esi
  int v162; // eax
  int (/*thiscall*/ **v163)(void **); // edx
  int v164; // eax
  int v165; // eax
  void *v166; // eax
  int *pDwArg122; // esi
  char *v168; // edi
  void *v169; // eax
  char *v170; // eax
  int v171; // eax
  uint32_t *v172; // edi
  uint32_t *v173; // eax
  int v174; // eax
  int v175; // ebx
  void *v176; // eax
  int v177; // ebx
  void *v178; // eax
  void *v179; // eax
  int v180; // ebx
  void *v181; // eax
  int v182; // ebx
  void *v183; // eax
  int v184; // eax
  int v185; // ecx
  int v186; // edx
  int v187; // esi
  unsigned int v188; // [esp+0h] [ebp-1A8h]
  int v189; // [esp+4h] [ebp-1A4h]
  int v190; // [esp+4h] [ebp-1A4h]
  void *v191; // [esp+4h] [ebp-1A4h]
  int v192; // [esp+4h] [ebp-1A4h]
  const char *v193; // [esp+4h] [ebp-1A4h]
  const char *v194; // [esp+4h] [ebp-1A4h]
  int v195; // [esp+4h] [ebp-1A4h]
  int v196; // [esp+4h] [ebp-1A4h]
  int v197; // [esp+8h] [ebp-1A0h]
  int v198; // [esp+8h] [ebp-1A0h]
  int v199; // [esp+8h] [ebp-1A0h]
  int v200; // [esp+8h] [ebp-1A0h]
  double v201; // [esp+8h] [ebp-1A0h]
  double v202; // [esp+8h] [ebp-1A0h]
  int v203; // [esp+8h] [ebp-1A0h]
  int v204; // [esp+8h] [ebp-1A0h]
  int v205; // [esp+8h] [ebp-1A0h]
  int v206; // [esp+8h] [ebp-1A0h]
  int v207; // [esp+8h] [ebp-1A0h]
  int v208; // [esp+8h] [ebp-1A0h]
  int v209; // [esp+8h] [ebp-1A0h]
  int v210; // [esp+8h] [ebp-1A0h]
  int v211; // [esp+8h] [ebp-1A0h]
  int nArg22; // [esp+Ch] [ebp-19Ch]
  int v213; // [esp+Ch] [ebp-19Ch]
  int v214; // [esp+Ch] [ebp-19Ch]
  int v215; // [esp+Ch] [ebp-19Ch]
  int v216; // [esp+Ch] [ebp-19Ch]
  void *v217; // [esp+Ch] [ebp-19Ch]
  int v218; // [esp+Ch] [ebp-19Ch]
  char v219[4]; // [esp+18h] [ebp-190h] BYREF
  void *v220; // [esp+1Ch] [ebp-18Ch]
  unsigned int v221; // [esp+30h] [ebp-178h]
  int nLen; // [esp+34h] [ebp-174h]
  int pObj3; // [esp+38h] [ebp-170h]
  int *pDwArg12; // [esp+3Ch] [ebp-16Ch]
  char v225; // [esp+43h] [ebp-165h]
  unsigned int v226; // [esp+44h] [ebp-164h]
  int v227; // [esp+48h] [ebp-160h]
  void *j; // [esp+4Ch] [ebp-15Ch]
  void *Src; // [esp+50h] [ebp-158h]
  uint8_t *pObj9; // [esp+54h] [ebp-154h]
  int v231; // [esp+58h] [ebp-150h] BYREF
  int i; // [esp+5Ch] [ebp-14Ch]
  bool v233; // [esp+62h] [ebp-146h]
  bool v234; // [esp+63h] [ebp-145h]
  char v235[64]; // [esp+64h] [ebp-144h] BYREF
  uint8_t v236[32]; // [esp+A4h] [ebp-104h] BYREF
  char Buffer[128]; // [esp+C4h] [ebp-E4h] BYREF
  void *v238[5]; // [esp+148h] [ebp-60h] BYREF
  unsigned int v239; // [esp+15Ch] [ebp-4Ch]
  int v240; // [esp+160h] [ebp-48h] BYREF
  void *Block[4]; // [esp+164h] [ebp-44h] BYREF
  int v242; // [esp+174h] [ebp-34h]
  unsigned int v243; // [esp+178h] [ebp-30h]
  char v244[4]; // [esp+17Ch] [ebp-2Ch] BYREF
  void *v245; // [esp+180h] [ebp-28h] BYREF
  char v246[4]; // [esp+188h] [ebp-20h] BYREF
  void *v247; // [esp+18Ch] [ebp-1Ch]
  uint32_t *v248; // [esp+190h] [ebp-18h]
  unsigned int v249; // [esp+194h] [ebp-14h]
  int dword_796E502; // [esp+198h] [ebp-10h]
  int v251; // [esp+1A4h] [ebp-4h]

  dword_796E502 = dword_796E50;
  pDwArg12 = pDwArg1;
  pObj3 = dword_8F7C04;  // 本地玩家对象
  if ( dword_8F7C04 == 0 )  // 本地玩家对象
    return 0;
  nArg22 = nArg2;
  pObj4 = __RTDynamicCast(pArg3, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);  // pObj4 = 调 __RTDynamicCast
  pObj9 = pObj4;
  v233 = false;
  if ( pObj4 != nullptr )  // 若 pObj4 有效（非空）
    v233 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pObj4 + 172))(pObj4, nArg2) <= 7;  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
  sub_55A050(pDwArg1 + 9);  // 信息窗文本 2（5014C0）
  v227 = 170;
  v239 = 15;
  v238[4] = nullptr;  // v238[4] = 空指针
  LOBYTE(v238[0]) = 0;
  v6 = (int (/*thiscall*/ **)(void **, uint32_t))*pArg3;
  v251 = 0;
  v7 = (void *)v6[27](pArg3, nArg22);
  sub_4015C0(v7, strlen((const char *)v7));  // 【std::string构造赋值】
  Src = v238;
  v8 = (*((int (/*thiscall*/ **)(void **))*pArg3 + 6))(pArg3);  // 调用虚函数槽 +6
  sub_572B20(0, v238, (int)(pDwArg1 + 13), v8);  // 绘制链中层 3（4015C0 + 572A90）
  v9 = (void **)v238[0];
  if ( v239 < 0x10 )  // 若 v239 < 0x10
    v9 = v238;
  v10 = sub_4883E0(pDwArg1 + 13, v9);  // 转发到 +48 对象虚表 +16
  if ( v10 > 170 )  // 若 v10 > 170
    v227 = v10;
  v11 = (*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3);  // 调用虚函数槽 +4
  v12 = (void *)sub_41ACF0(v11 + 12);  // 驻留串句柄 → 字符串指针
  sub_4015C0(v12, strlen((const char *)v12));  // 【std::string构造赋值】
  v13 = (void **)v238[0];
  if ( v239 < 0x10 )  // 若 v239 < 0x10
    v13 = v238;
  v14 = (*((int (/*thiscall*/ **)(void **))*pArg3 + 6))(pArg3);  // 调用虚函数槽 +6
  sub_572B20(1, v13, (int)(pDwArg1 + 13), v14);  // 绘制链中层 3（4015C0 + 572A90）
  v15 = (void **)v238[0];
  v16 = 3;
  if ( v239 < 0x10 )  // 若 v239 < 0x10
    v15 = v238;
  v17 = sub_4883E0(pDwArg1 + 13, v15);  // 转发到 +48 对象虚表 +16
  if ( v227 < v17 )  // 若 v227 < v17
    v227 = v17;
  v18 = *(uint32_t *)((*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3) + 56);
  Src = (void *)v18;
  if ( v18 != 0 )  // 若 v18 非 0
  {
    v20 = v18 % 1000;
    v19 = v18 / 1000;
    v231 = v20;
    i = v19;
    if ( v20 != 0 )  // 若 v20 非 0
    {
      if ( (int)Src % 100 != 0 )  // 若 (int)Src % 100 != 0
      {
        if ( (int)Src % 10 != 0 )  // 若 (int)Src % 10 != 0
          sprintf(byte_9B8994, "%d.%03dkg", i, abs32(v231));  // 拼字符串（模板 %d.%03dkg）
        else  // 否则分支
          sprintf(byte_9B8994, "%d.%02dkg", i, abs32(v231 / 10));  // 拼字符串（模板 %d.%02dkg）
      }
      else  // 否则分支
      {
        sprintf(byte_9B8994, "%d.%dkg", i, abs32(v231 / 100));  // 拼字符串（模板 %d.%dkg）
      }
    }
    else  // 否则分支
    {
      sprintf(byte_9B8994, "%dkg", v19);  // 拼字符串（模板 %dkg）
    }
    v21 = 0;
    do  // do-while 循环体起点
    {
      v22 = byte_9B8994[v21];  // v22 = 取 byte_9B8994[v21]
      v236[v21++] = v22;
    }
    while ( v22 != 0 );  // 条件循环
  }
  else  // 否则分支
  {
    v236[0] = 0;
  }
  sub_572B20(3, v236, (int)(pDwArg1 + 13), -1);  // 绘制链中层 3（4015C0 + 572A90）
  if ( dword_795378 != 4 && dword_795378 != 5 && dword_795378 != 9 )  // 若 dword_795378 != 4 与/或 dword_795378 != 5 与/或 dword_795378 != 9
  {
    if ( !v233 )  // 若 !v233
    {
      if ( (*((int (/*thiscall*/ **)(void **))*pArg3 + 24))(pArg3) != 0 )
      {
        sub_401710((char *)szPassword);  // std::string 复位并赋值 C 串（+24=15/+20=0/+4=0 → ·sub_4015C0）
        v23 = (int (/*thiscall*/ **)(void **))*pArg3;
        LOBYTE(v251) = 5;
        v24 = v23[24](pArg3);
        v25 = (void *)sub_5486B0(v24);  // 物品栏标题组装（4015C0/4014D0/548610/548540，113 行）
        sub_406D60(v25);  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        v26 = sub_422E70(424);  // v26 = 调 sub_422E70 返回值
        sub_402410(v26);  // std::string::insert(pos, C串) 薄封装（strlen + ·sub_4022F0）
        Block2 = (void **)Block[0];
        if ( v243 < 0x10 )  // 若 v243 < 0x10
          Block2 = Block;
        sub_572B20(3, Block2, (int)(pDwArg1 + 26), -1);  // 绘制链中层 3（4015C0 + 572A90）
        LOBYTE(v251) = 0;
        sub_501490(&v240);  // 调 sub_501490
      }
      v16 = 4;
    }
    goto LABEL_50;  // 跳转 LABEL_50
  }
  v249 = 15;
  v248 = nullptr;  // v248 = 空指针
  LOBYTE(v245) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  LOBYTE(v251) = 1;
  if ( dword_795378 != 9 )  // 若 dword_795378 != 9
  {
    v31 = (int (/*thiscall*/ **)(void **))*pArg3;
    if ( v233 )  // 若 v233
    {
      v213 = *(uint32_t *)(v31[4](pArg3) + 52);
      v197 = *(uint32_t *)((*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3) + 40);
      v189 = *(uint32_t *)((*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3) + 44);
      v32 = (*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3);  // 调用虚函数槽 +4
      v214 = sub_4F36B0(v219, *(uint32_t *)(v32 + 36), v189, v197, v213);  // v214 = 调 sub_4F36B0 返回值
      LOBYTE(v251) = 2;
      v33 = (void *)sub_422E70(1031);  // v33 = 调 sub_422E70 返回值
      v34 = sub_572360((int)&v240, v33, v214);  // 物品信息文本行辅助（4015C0/4021F0/4014D0）
      LOBYTE(v251) = 3;
      sub_4014D0((std::_String_base *)v244, v34, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      if ( v243 >= 0x10 )  // 若 v243 >= 0x10
        j__free(Block[0]);  // 调 j__free
      v243 = 15;
      v242 = 0;
      LOBYTE(Block[0]) = 0;
      LOBYTE(v251) = 1;
      if ( v221 < 0x10 )  // 若 v221 < 0x10
        goto LABEL_44;  // 跳转 LABEL_44
    }
    else  // 否则分支
    {
      v215 = *(uint32_t *)(v31[4](pArg3) + 52);
      v198 = *(uint32_t *)((*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3) + 40);
      v190 = *(uint32_t *)((*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3) + 44);
      v35 = (*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3);  // 调用虚函数槽 +4
      v36 = sub_4F36B0(v219, *(uint32_t *)(v35 + 36), v190, v198, v215);  // v36 = 调 sub_4F36B0 返回值
      LOBYTE(v251) = 4;
      sub_4014D0((std::_String_base *)v244, v36, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      LOBYTE(v251) = 1;
      if ( v221 < 0x10 )  // 若 v221 < 0x10
        goto LABEL_44;  // 跳转 LABEL_44
    }
    j__free(v220);  // 调 j__free
    goto LABEL_44;  // 跳转 LABEL_44
  }
  sub_541A30();  // 摊位条目名取串（10 行）
  v28 = sub_542AB0((char)pArg3);  // 摊位数据释放（4BE520）
  v29 = (void *)sub_5486B0(v28);  // 物品栏标题组装（4015C0/4014D0/548610/548540，113 行）
  sub_4015C0(v29, strlen((const char *)v29));  // 【std::string构造赋值】
  psz = (const char *)sub_422E70(424);  // psz = 调 sub_422E70 返回值
  sub_4022F0((std::_String_base *)v244, psz, strlen(psz));  // std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
LABEL_44:  // 标签 LABEL_44（跳转合流点）
  if ( v248 != nullptr )  // 若 v248 有效（非空）
  {
    v37 = v245;
    if ( v249 < 0x10 )  // 若 v249 < 0x10
      v37 = &v245;
    sub_572B20(3, v37, (int)(pDwArg1 + 26), -1);  // 绘制链中层 3（4015C0 + 572A90）
  }
  v16 = 4;
  LOBYTE(v251) = 0;
  if ( v249 >= 0x10 )  // 若 v249 >= 0x10
    j__free(v245);  // 调 j__free
LABEL_50:  // 标签 LABEL_50（跳转合流点）
  pObj7 = pObj9;
  if ( pObj9 != nullptr )  // 若 pObj9 有效（非空）
  {
    pDwArg1[65] = (int)pObj9;  // pDwArg1[65] 写入 (int)pObj9
    if ( *(uint32_t *)(*(int (**)(void))(*(uint32_t *)pObj7 + 172))() != 8 )  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
    {
      switch ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 172))(pObj9) )  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
      {
        case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
        case 0xF:  // case 15
        case 0x10:  // case 16
        case 0x11:  // case 17
          goto LABEL_63;  // 跳转 LABEL_63
        case 0xA:  // case 10
        case 0xB:  // case 11
        case 0xC:  // case 12
        case 0xD:  // case 13
        case 0xE:  // case 14
          v50 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 172))(pObj9);  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
          v51 = sub_41A5E0(v50 + 4);  // crypt4byte 解密校验（·0x41A590 逆运算）
          sub_572B20(v16, *(&dword_9B8980 + v51), (int)(pDwArg1 + 13), -1);  // 绘制链中层 3（4015C0 + 572A90）
LABEL_63:  // 标签 LABEL_63（跳转合流点）
          v191 = *(&dword_9B88D8 + *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 172))(pObj9));  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
          sub_572B20(v16, v191, (int)(pDwArg1 + 26), -1);  // 绘制链中层 3（4015C0 + 572A90）
          goto LABEL_64;  // 跳转 LABEL_64
        default:  // 默认分支
          goto LABEL_65;  // 跳转 LABEL_65
      }
    }
    *((uint8_t *)pDwArg1 + 264) = 1;
    i = 4;
    v231 = 0;
    while ( 1 )  // 条件循环
    {
      v39 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 16))(pObj9);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
      v40 = v231;
      if ( *(uint8_t *)(v39 + v231 + 60) != 0 )  // 若 *(uint8_t *)(v39 + v231 + 60) != 0
        break;  // 跳出循环/分支
      ++v231;  // 自增v231
      if ( v40 + 1 >= 4 )  // 若 v40 + 1 >= 4
        goto LABEL_57;  // 跳转 LABEL_57
    }
    i = v231;
LABEL_57:  // 标签 LABEL_57（跳转合流点）
    v41 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 172))(pObj9);  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
    v42 = sub_41A5E0(v41 + 4);  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_572B20(v16, *(&dword_9B8920 + 6 * i + v42), (int)(pDwArg1 + 13), -1);  // 绘制链中层 3（4015C0 + 572A90）
    v43 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 172))(pObj9);  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
    sub_572B20(v16, *(&dword_9B88D8 + *v43), (int)(pDwArg1 + 26), -1);  // 绘制链中层 3（4015C0 + 572A90）
    v44 = *(uint32_t *)pObj9;  // v44 = pObj9
    ++v16;  // 自增v16
    if ( i == 2 )  // 若 i == 2
    {
      v45 = (*(int (**)(void))(v44 + 176))();  // 调用虚函数槽 +176
      v46 = sub_41A5E0(v45 + 686);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v216 = sub_571AF0(v46);  // 物品说明文本辅助（422E70 字符串表取串）
      v47 = (const char *)sub_422E70(1033);  // v47 = 调 sub_422E70 返回值
    }
    else  // 否则分支
    {
      v48 = (*(int (**)(void))(v44 + 176))();  // 调用虚函数槽 +176
      v49 = sub_41A5E0(v48 + 686);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v216 = sub_571AF0(v49);  // 物品说明文本辅助（422E70 字符串表取串）
      v47 = (const char *)sub_422E70(1034);  // v47 = 调 sub_422E70 返回值
    }
    sprintf(Buffer, v47, v216);  // 拼字符串
    sub_572B20(v16, Buffer, (int)(pDwArg1 + 13), -1);  // 绘制链中层 3（4015C0 + 572A90）
LABEL_64:  // 标签 LABEL_64（跳转合流点）
    ++v16;  // 自增v16
LABEL_65:  // 标签 LABEL_65（跳转合流点）
    v52 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 172))(pObj9);  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
    j = (void *)sub_41A5E0(v52 + 18);  // crypt4byte 解密校验（·0x41A590 逆运算）
    if ( j != nullptr )  // 若 j 有效（非空）
    {
      v53 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 188))(pObj9);  // 调虚槽 +188：动画对象 z 倾斜转状态码
      v54 = sub_41A5E0(v53 + 32);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v217 = j;
      v199 = v54;
      v55 = (const char *)sub_422E70(1035);  // v55 = 调 sub_422E70 返回值
      sprintf(Buffer, v55, v199, v217);  // 拼字符串
      v56 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 200))(pObj9);  // 调虚槽 +200：取动画对象
      sub_572B20(v16, Buffer, (int)(pDwArg1 + 13), v56 != 0 ? -13487361 : -1);  // 绘制链中层 3（4015C0 + 572A90）
    }
    if ( !v233 )  // 若 !v233
    {
      v57 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 16))(pObj9) + 28) - 1;  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
      if ( v57 != 0 )  // 若 v57 非 0
      {
        v58 = v57 - 1;
        if ( v58 != 0 )  // 若 v58 非 0
        {
          if ( v58 != 1 )  // 若 v58 != 1
            goto LABEL_91;  // 跳转 LABEL_91
          if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 16))(pObj9) + 32) == 1 )  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
          {
            v59 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 188))(pObj9);  // 调虚槽 +188：动画对象 z 倾斜转状态码
            if ( sub_41A5E0(v59 + 46) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
            {
              v61 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 188))(pObj9);  // 调虚槽 +188：动画对象 z 倾斜转状态码
              v218 = sub_41A5E0(v61 + 46);  // crypt4byte 解密校验（·0x41A590 逆运算）
              v62 = (const char *)sub_422E70(1701);  // v62 = 调 sub_422E70 返回值
              sprintf(v235, v62, v218);  // 拼字符串
              sub_572B20(v16, v235, (int)(pDwArg1 + 26), -1);  // 绘制链中层 3（4015C0 + 572A90）
              goto LABEL_91;  // 跳转 LABEL_91
            }
            v200 = (int)(pDwArg1 + 26);
            v60 = (void *)sub_422E70(1038);  // v60 = 调 sub_422E70 返回值
          }
          else  // 否则分支
          {
            v200 = (int)(pDwArg1 + 26);
            v60 = (void *)sub_422E70(1039);  // v60 = 调 sub_422E70 返回值
          }
        }
        else  // 否则分支
        {
          v200 = (int)(pDwArg1 + 26);
          v60 = (void *)sub_422E70(1037);  // v60 = 调 sub_422E70 返回值
        }
      }
      else  // 否则分支
      {
        v200 = (int)(pDwArg1 + 26);
        v60 = (void *)sub_422E70(1036);  // v60 = 调 sub_422E70 返回值
      }
      goto LABEL_90;  // 跳转 LABEL_90
    }
  }
  else  // 否则分支
  {
    Src = *pArg3;
    v63 = (*((int (/*thiscall*/ **)(void **))Src + 4))(pArg3);  // 调用虚函数槽 +4
    if ( (*((uint8_t (/*thiscall*/ **)(void **, uint32_t))Src + 15))(pArg3, *(uint32_t *)(v63 + 4)) == 0 )
    {
      v200 = (int)(pDwArg1 + 13);
      v60 = (void *)sub_422E70(1050);  // v60 = 调 sub_422E70 返回值
LABEL_90:  // 标签 LABEL_90（跳转合流点）
      sub_572B20(v16, v60, v200, -1);  // 绘制链中层 3（4015C0 + 572A90）
      goto LABEL_91;  // 跳转 LABEL_91
    }
    switch ( *(uint32_t *)(*((int (/*thiscall*/ **)(void **))*pArg3 + 33))(pArg3) )  // 按 *(uint32_t *)(*((int (thisca… 分派
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        v64 = (void *)sub_422E70(1040);  // v64 = 调 sub_422E70 返回值
        sub_572B20(v16, v64, (int)(pDwArg1 + 13), -1);  // 绘制链中层 3（4015C0 + 572A90）
        v201 = (double)*(int *)((*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3) + 64) * 0.001;
        v65 = (const char *)sub_422E70(1041);  // v65 = 调 sub_422E70 返回值
        goto LABEL_83;  // 跳转 LABEL_83
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        v200 = (int)(pDwArg1 + 13);
        v60 = (void *)sub_422E70(1046);  // v60 = 调 sub_422E70 返回值
        goto LABEL_90;  // 跳转 LABEL_90
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        v200 = (int)(pDwArg1 + 13);
        v60 = (void *)sub_422E70(1047);  // v60 = 调 sub_422E70 返回值
        goto LABEL_90;  // 跳转 LABEL_90
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        v66 = (void *)sub_422E70(1042);  // v66 = 调 sub_422E70 返回值
        sub_572B20(v16, v66, (int)(pDwArg1 + 13), -1);  // 绘制链中层 3（4015C0 + 572A90）
        v202 = (double)*(int *)((*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3) + 64) * 0.001;
        v67 = (const char *)sub_422E70(1043);  // v67 = 调 sub_422E70 返回值
        sprintf(Buffer, v67, v202);  // 拼字符串
        sub_572B20(v16, Buffer, (int)(pDwArg1 + 26), -1);  // 绘制链中层 3（4015C0 + 572A90）
        break;  // 跳出循环/分支
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        v68 = (void *)sub_422E70(1044);  // v68 = 调 sub_422E70 返回值
        sub_572B20(v16, v68, (int)(pDwArg1 + 13), -1);  // 绘制链中层 3（4015C0 + 572A90）
        v201 = (double)*(int *)((*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3) + 64) * 0.001;
        v65 = (const char *)sub_422E70(1045);  // v65 = 调 sub_422E70 返回值
LABEL_83:  // 标签 LABEL_83（跳转合流点）
        sprintf(Buffer, v65, v201);  // 拼字符串
        sub_572B20(v16, Buffer, (int)(pDwArg1 + 26), -1);  // 绘制链中层 3（4015C0 + 572A90）
        break;  // 跳出循环/分支
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        v200 = (int)(pDwArg1 + 13);
        v60 = (void *)sub_422E70(1048);  // v60 = 调 sub_422E70 返回值
        goto LABEL_90;  // 跳转 LABEL_90
      case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
        v200 = (int)(pDwArg1 + 13);
        v60 = (void *)sub_422E70(1049);  // v60 = 调 sub_422E70 返回值
        goto LABEL_90;  // 跳转 LABEL_90
      case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
        v16 -= 2;
        break;  // 跳出循环/分支
      default:  // 默认分支
        break;  // 跳出循环/分支
    }
  }
LABEL_91:  // 标签 LABEL_91（跳转合流点）
  v69 = v16 + 1;
  i = (int)pArg3[2];
  v70 = sub_667620(pArg3);  // 取 +8 字段（getter）
  v71 = *(uint32_t *)dword_8F7C04;  // 本地玩家对象
  v226 = v70;
  v72 = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(v71 + 672))(dword_8F7C04, 3);  // 本地玩家对象
  if ( i > 1 )  // 若 i > 1
  {
    v234 = i != v226;
    if ( i - 5 <= 0 )  // 若 i - 5 <= 0
      v234 = false;
    if ( v72 < i )  // 若 v72 < i
      v231 = v72 < (int)v226 ? -13487361 : -13435086;
    else  // 否则分支
      v231 = -1;
    if ( v234 )  // 若 v234
    {
      v192 = i;
      v188 = v226;
      v73 = (const char *)sub_422E70(1051);  // v73 = 调 sub_422E70 返回值
      sprintf(Buffer, v73, v188, v192, 5);  // 拼字符串
    }
    else  // 否则分支
    {
      v203 = i;
      v74 = (const char *)sub_422E70(3000);  // v74 = 调 sub_422E70 返回值
      sprintf(Buffer, v74, v203);  // 拼字符串
    }
    sub_572B20(v69, Buffer, (int)(pDwArg1 + 13), v231);  // 绘制链中层 3（4015C0 + 572A90）
    if ( (*(int (/*thiscall*/ **)(void **))*pArg3)(pArg3) == 2 )
    {
      j = (void *)(*((int (/*thiscall*/ **)(void **))*pArg3 + 73))(pArg3);
      nLen = strlen((const char *)j);  // nLen = 调 strlen
      if ( nLen != 0 )  // 若 nLen 非 0
      {
        v75 = (*((int (/*thiscall*/ **)(void **))*pArg3 + 74))(pArg3);  // 调用虚函数槽 +74
        sub_572B20(v69, j, (int)(pDwArg1 + 26), v75);  // 绘制链中层 3（4015C0 + 572A90）
      }
    }
    ++v69;  // 自增v69
  }
  v234 = false;
  v225 = 1;
  for ( i = 0; i < 4; ++i )  // 循环：i 从 0 递增到 4
  {
    v76 = (*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3);  // 调用虚函数槽 +4
    if ( *(uint8_t *)(v76 + i + 60) != 0 )  // 若 *(uint8_t *)(v76 + i + 60) != 0
    {
      v77 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);  // 调虚槽 +1032
      if ( i == *v77 )  // 若 i == *v77
        v234 = true;
    }
    else  // 否则分支
    {
      v225 = 0;
    }
  }
  if ( v225 == 0 )  // 若 v225 为 0
  {
    i = 0;
    v231 = v234 ? -1 : -13487361;
    do  // do-while 循环体起点
    {
      v78 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_9B88D0 + 16))(dword_9B88D0);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
      if ( *(uint8_t *)(v78 + i + 60) != 0 )  // 若 *(uint8_t *)(v78 + i + 60) != 0
      {
        v204 = sub_4B0EC0(i, 0);  // 表记录字符串取值（28 字节/条）
        v79 = (const char *)sub_422E70(1052);  // v79 = 调 sub_422E70 返回值
        sprintf(Buffer, v79, v204);  // 拼字符串
        sub_572B20(v69, Buffer, (int)(pDwArg1 + 13), v231);  // 绘制链中层 3（4015C0 + 572A90）
        if ( v233 )  // 若 v233
        {
          v80 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 172))(pObj9);  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
          sub_572B20(v69, *(&dword_9B88D8 + *v80), (int)(pDwArg1 + 26), v231);  // 绘制链中层 3（4015C0 + 572A90）
        }
        ++v69;  // 自增v69
      }
      ++i;  // 自增i
    }
    while ( i < 4 );  // 条件循环
  }
  if ( pObj9 != nullptr )  // 若 pObj9 有效（非空）
  {
    v81 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 172))(pObj9);  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
    if ( sub_41A5E0(v81 + 32) != -1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      ++v69;  // 自增v69
      v82 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 172))(pObj9);  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
      Src = (void *)sub_41A5E0(v82 + 32);  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( v234 )  // 若 v234
      {
        v83 = sub_47DC90(Src);  // v83 = 调 sub_47DC90 返回值
      }
      else  // 否则分支
      {
        i = 0;
        while ( 1 )  // 条件循环
        {
          v84 = (*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3);  // 调用虚函数槽 +4
          if ( *(uint8_t *)(v84 + i + 60) != 0 )  // 若 *(uint8_t *)(v84 + i + 60) != 0
            break;  // 跳出循环/分支
          if ( ++i >= 4 )  // 若 ++i >= 4
            goto LABEL_132;  // 跳转 LABEL_132
        }
        v83 = sub_47E720(i, Src);  // v83 = 调 sub_47E720 返回值
      }
      v85 = v83;
      if ( v83 != 0 )  // 若 v83 非 0
      {
        if ( !v234 || (v86 = sub_41A5E0(v83 + 510), v231 = -1, v86 <= 0) )  // crypt4byte 解密校验（·0x41A590 逆运算）
          v231 = -13487361;
        v205 = sub_41ACF0(v85 + 20);  // 驻留串句柄 → 字符串指针
        v87 = (const char *)sub_422E70(1053);  // v87 = 调 sub_422E70 返回值
        sprintf(Buffer, v87, v205);  // 拼字符串
        sub_572B20(v69++, Buffer, (int)(pDwArg1 + 13), v231);  // 绘制链中层 3（4015C0 + 572A90）
        v88 = sub_4883E0(pDwArg1 + 13, Buffer);  // 转发到 +48 对象虚表 +16
        if ( v227 < v88 )  // 若 v227 < v88
          v227 = v88;
      }
    }
LABEL_132:  // 标签 LABEL_132（跳转合流点）
    pObj6 = pObj9;
    if ( !v233 )  // 若 !v233
    {
      v90 = *(uint32_t *)pObj9;  // v90 = pObj9
      v231 = v69 + 1;
      v206 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(v90 + 172))(pObj9);
      v91 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj6 + 176))(pObj6);  // 调虚槽 +176：目标是否在前方/后方（按 walkDir 朝向 +152）
      sub_572EF0(v91, -1, &v231, 0, v206);  // 物品信息窗绘制主函数（725 行：497040 属性枚举 + 571B80/572BC0/572B20 分支 + 47E720 说明）
      v69 = v231;
      goto LABEL_172;  // 跳转 LABEL_172
    }
    v231 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 176))(pObj9) + 916;  // 调虚槽 +176：目标是否在前方/后方（按 walkDir 朝向 +152）
    if ( dword_795378 == 5 )  // 若 dword_795378 == 5
    {
      v92 = *(uint32_t *)(v231 + 4);  // v92 = v231+4
      v93 = 0;
      v226 = 0;
      while ( 1 )  // 条件循环
      {
        i = v93;
        if ( v92 == 0 )  // 若 v92 为 0
          goto LABEL_158;  // 跳转 LABEL_158
        if ( v226 >= (*(uint32_t *)(v231 + 8) - v92) / 80 || *(uint32_t *)(i + v92) != 0 )  // 复合条件判定（与/或）
          break;  // 跳出循环/分支
        ++v226;  // 自增v226
        v93 = i + 80;
      }
      j = (void *)((*(uint32_t *)(v231 + 8) - v92) / 80);
      if ( j == nullptr )  // 若 j 为空
      {
LABEL_158:  // 标签 LABEL_158（跳转合流点）
        v96 = v69 + 1;
        v106 = (void *)sub_422E70(1055);  // v106 = 调 sub_422E70 返回值
        sub_572B20(v96, v106, (int)(pDwArg1 + 13), -346530);  // 绘制链中层 3（4015C0 + 572A90）
        goto LABEL_159;  // 跳转 LABEL_159
      }
      v94 = v69 + 1;
      v95 = (void *)sub_422E70(1054);  // v95 = 调 sub_422E70 返回值
      sub_572B20(v94, v95, (int)(pDwArg1 + 13), -346530);  // 绘制链中层 3（4015C0 + 572A90）
      v96 = v94 + 1;
      v97 = 0;
      while ( 1 )  // 条件循环
      {
        v98 = *(uint32_t *)(v231 + 4);  // v98 = v231+4
        if ( v98 == 0 || v97 >= (*(uint32_t *)(v231 + 8) - v98) / 80 )  // 若 v98 == 0
          break;  // 跳出循环/分支
        v99 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 176))(pObj9);  // 调虚槽 +176：目标是否在前方/后方（按 walkDir 朝向 +152）
        v100 = sub_4EB900(v99, v97);  // 属性条目文本格式化（按条目 id 分支，输出静态缓冲 byte_9B0990）
        j = (void *)(v97 + 1);
        sprintf(Buffer, "%d: %s", v97 + 1, v100);  // 拼字符串（模板 %d: %s）
        v247 = nullptr;  // v247 = 空指针
        v248 = nullptr;  // v248 = 空指针
        v249 = 0;
        LOBYTE(v251) = 6;
        v101 = (void *)sub_572BC0(Buffer, 34, v246);  // 物品信息窗部件构建（186 行：416C40/406D00/4164C0 文本块装配）
        if ( (int)v101 > 0 )  // 若 (int)v101 > 0
        {
          v102 = (char *)v247 + 4;
          for ( Src = v101; Src != nullptr; Src = (char *)Src - 1 )  // 遍历循环
          {
            if ( *((uint32_t *)v102 + 5) < 0x10u )  // 若 *((uint32_t *)v102 + 5) < 0x10u
              v103 = v102;
            else  // 否则分支
              v103 = *(void **)v102;
            sub_572B20(v96++, v103, (int)(pDwArg1 + 13), -1);  // 绘制链中层 3（4015C0 + 572A90）
            v102 += 28;
          }
        }
        LOBYTE(v251) = 0;
        if ( v247 != nullptr )  // 若 v247 有效（非空）
        {
          if ( v247 != v248 )  // 若 v247 != v248
          {
            v104 = (char *)v247 + 24;
            do  // do-while 循环体起点
            {
              if ( *v104 >= 0x10u )  // 若 *v104 >= 0x10u
                j__free((void *)*(v104 - 5));  // 调 j__free
              v105 = v248;
              *v104 = 15;  // *v104 写入 15
              *(v104 - 1) = 0;
              *((uint8_t *)v104 - 20) = 0;
              v104 += 7;
            }
            while ( v104 - 6 != v105 );  // 条件循环
          }
          j__free(v247);  // 调 j__free
        }
        v97 = (unsigned int)j;
        v247 = nullptr;  // v247 = 空指针
        v248 = nullptr;  // v248 = 空指针
        v249 = 0;
      }
LABEL_159:  // 标签 LABEL_159（跳转合流点）
      pObj6 = pObj9;
    }
    else  // 否则分支
    {
      j = (void *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj6 + 176))(pObj6);  // 调虚槽 +176：目标是否在前方/后方（按 walkDir 朝向 +152）
      v107 = sub_41A5E0((unsigned int)j + 932);  // crypt4byte 解密校验（·0x41A590 逆运算）
      j = sub_4EB900(j, v107);  // 属性条目文本格式化（按条目 id 分支，输出静态缓冲 byte_9B0990）
      if ( j == nullptr )  // 若 j 为空
      {
LABEL_163:  // 标签 LABEL_163（跳转合流点）
        if ( dword_795378 != 4 && dword_795378 != 5 )  // 若 dword_795378 != 4 与/或 dword_795378 != 5
        {
          v110 = v69 + 1;
          v111 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj6 + 204))(pObj6);  // 调虚槽 +204：定时器插入
          v112 = v111 / 3600;
          if ( v111 / 3600 < 24 )  // 若 v111 / 3600 < 24
          {
            if ( v111 != 0 )  // 若 v111 非 0
            {
              v208 = v112 + 1;
              v194 = (const char *)sub_422E70(1058);  // v194 = 调 sub_422E70 返回值
            }
            else  // 否则分支
            {
              v194 = (const char *)sub_422E70(1059);  // v194 = 调 sub_422E70 返回值
            }
            sprintf(Buffer, v194, v208);  // 拼字符串
          }
          else  // 否则分支
          {
            v207 = v112 / 24 + 1;
            v193 = (const char *)sub_422E70(1057);  // v193 = 调 sub_422E70 返回值
            sprintf(Buffer, v193, v207);  // 拼字符串
          }
          sub_572B20(v110, Buffer, (int)(pDwArg1 + 13), -1);  // 绘制链中层 3（4015C0 + 572A90）
          v69 = v110 + 1;
        }
        goto LABEL_172;  // 跳转 LABEL_172
      }
      v108 = v69 + 1;
      v109 = (void *)sub_422E70(1056);  // v109 = 调 sub_422E70 返回值
      sub_572B20(v108, v109, (int)(pDwArg1 + 13), -346530);  // 绘制链中层 3（4015C0 + 572A90）
      v96 = v108 + 1;
      sprintf(Buffer, "%s", (const char *)j);  // 拼字符串
      sub_572B20(v96, Buffer, (int)(pDwArg1 + 13), -1);  // 绘制链中层 3（4015C0 + 572A90）
    }
    v69 = v96 + 1;
    goto LABEL_163;  // 跳转 LABEL_163
  }
LABEL_172:  // 标签 LABEL_172（跳转合流点）
  v113 = (*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3);  // 调用虚函数槽 +4
  if ( strcmp((const char *)sub_41ACF0(v113 + 16), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
  {
    ++v69;  // 自增v69
    v247 = nullptr;  // v247 = 空指针
    v248 = nullptr;  // v248 = 空指针
    v249 = 0;
    v114 = (int (/*thiscall*/ **)(void **))*pArg3;
    LOBYTE(v251) = 7;
    v115 = v114[4](pArg3);
    v116 = sub_41ACF0(v115 + 16);  // 驻留串句柄 → 字符串指针
    v117 = (void *)sub_572BC0(v116, 34, v246);  // 物品信息窗部件构建（186 行：416C40/406D00/4164C0 文本块装配）
    if ( (int)v117 > 0 )  // 若 (int)v117 > 0
    {
      v118 = (char *)v247 + 4;
      for ( Src = v117; Src != nullptr; Src = (char *)Src - 1 )  // 遍历循环
      {
        if ( *((uint32_t *)v118 + 5) < 0x10u )  // 若 *((uint32_t *)v118 + 5) < 0x10u
          v119 = v118;
        else  // 否则分支
          v119 = *(void **)v118;
        v120 = pDwArg12 + 13;
        sub_572B20(v69++, v119, (int)(pDwArg12 + 13), -346530);  // 绘制链中层 3（4015C0 + 572A90）
        if ( *((uint32_t *)v118 + 5) < 0x10u )  // 若 *((uint32_t *)v118 + 5) < 0x10u
          v121 = v118;
        else  // 否则分支
          v121 = *(char **)v118;
        v122 = sub_4883E0(v120, v121);  // 转发到 +48 对象虚表 +16
        if ( v227 < v122 )  // 若 v227 < v122
          v227 = v122;
        v118 += 28;
      }
    }
    LOBYTE(v251) = 0;
    if ( v247 != nullptr )  // 若 v247 有效（非空）
    {
      if ( v247 != v248 )  // 若 v247 != v248
      {
        v123 = (char *)v247 + 24;
        do  // do-while 循环体起点
        {
          if ( *v123 >= 0x10u )  // 若 *v123 >= 0x10u
            j__free((void *)*(v123 - 5));  // 调 j__free
          v124 = v248;
          *v123 = 15;  // *v123 写入 15
          *(v123 - 1) = 0;
          *((uint8_t *)v123 - 20) = 0;
          v123 += 7;
        }
        while ( v123 - 6 != v124 );  // 条件循环
      }
      j__free(v247);  // 调 j__free
    }
  }
  pObj2 = pObj9;
  if ( pObj9 != nullptr )  // 若 pObj9 有效（非空）
  {
    v126 = *(uint32_t *)pObj9;  // v126 = pObj9
    i = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(v126 + 236))(pObj9) != 0 )
    {
      v127 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj2 + 272))(pObj2);  // 调虚槽 +272
    }
    else  // 否则分支
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj2 + 240))(pObj2) == 0 )  // 调虚槽 +240：已历时 = clock_now(clockMain) − this+52*4
        goto LABEL_197;  // 跳转 LABEL_197
      v128 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj2 + 244))(pObj2);  // 调虚槽 +244：时长/剩余
      v127 = sub_4CE8A0(v128);  // v127 = 调 sub_4CE8A0 返回值
    }
    i = v127;
LABEL_197:  // 标签 LABEL_197（跳转合流点）
    v234 = false;
    v129 = 0;
    while ( pObj2 != (uint8_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 792))(pObj3, v129) )  // 调虚槽 +792：18 观察者槽数组访问（+6468+4*a2）
    {
      if ( ++v129 >= 18 )  // 若 ++v129 >= 18
        goto LABEL_202;  // 跳转 LABEL_202
    }
    v234 = true;
LABEL_202:  // 标签 LABEL_202（跳转合流点）
    if ( i != 0 )  // 若 i 非 0
    {
      v130 = *(uint32_t *)(i + 1112);  // v130 = i+1112
      v231 = ++v69;
      if ( v130 != 0 )  // 若 v130 非 0
        v131 = (*(uint32_t *)(i + 1116) - v130) >> 2;
      else  // 否则分支
        v131 = 0;
      v132 = 0;
      nLen = v131 + 1;
      j = nullptr;  // j = 空指针
      while ( 1 )  // 条件循环
      {
        pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 792))(pObj3, v132);  // 调虚槽 +792：18 观察者槽数组访问（+6468+4*a2）
        v134 = (int *)pObj;
        if ( pObj != 0 )  // 若 pObj 非 0
        {
          v135 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
          if ( *(uint32_t *)(v135 + 4) == *(uint32_t *)i )  // 若 *(uint32_t *)(v135 + 4) == *(uint32_t *)i
            break;  // 跳出循环/分支
        }
        if ( ++v132 >= 18 )  // 若 ++v132 >= 18
          goto LABEL_213;  // 跳转 LABEL_213
      }
      v136 = *v134;
      j = v134;
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(v136 + 224))(v134) == 0 || (v233 = true, !v234) )  // 若 v233 = true
LABEL_213:  // 标签 LABEL_213（跳转合流点）
        v233 = false;
      v137 = *(uint32_t *)(i + 1104);  // v137 = i+1104
      v138 = i + 1104;
      if ( v137 != 0 && *(uint32_t *)(v137 + 4) != 0 )  // 若 v137 != 0
      {
        v209 = v233 ? -4993059 : -4934476;
        v139 = pDwArg12 + 13;
        v195 = (int)(pDwArg12 + 13);
        v140 = (void *)sub_41ACF0(i + 1104);  // 驻留串句柄 → 字符串指针
        sub_572B20(v69++, v140, v195, v209);  // 绘制链中层 3（4015C0 + 572A90）
        v231 = v69;
        v141 = sub_41ACF0(v138);  // 驻留串句柄 → 字符串指针
        v142 = sub_4883E0(v139, v141);  // 转发到 +48 对象虚表 +16
        if ( v227 < v142 )  // 若 v227 < v142
          v227 = v142;
      }
      Src = nullptr;  // Src = 空指针
      if ( nLen > 0 )  // 若 nLen > 0
      {
        do  // do-while 循环体起点
        {
          if ( Src != nullptr )  // 若 Src 有效（非空）
            v226 = *(uint32_t *)(*(uint32_t *)(i + 1112) + 4 * (uint32_t)Src - 4);
          else  // 否则分支
            v226 = *(uint32_t *)i;  // v226 = i
          if ( !v234 )  // 若 !v234
            goto LABEL_229;  // 跳转 LABEL_229
          v143 = 0;
          while ( 1 )  // 条件循环
          {
            pObj5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 792))(pObj3, v143);  // 调虚槽 +792：18 观察者槽数组访问（+6468+4*a2）
            if ( pObj5 != 0 )  // 若 pObj5 非 0
            {
              v145 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 16))(pObj5);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
              if ( *(uint32_t *)(v145 + 4) == v226 )  // 若 *(uint32_t *)(v145 + 4) == v226
                break;  // 跳出循环/分支
            }
            if ( ++v143 >= 18 )  // 若 ++v143 >= 18
              goto LABEL_229;  // 跳转 LABEL_229
          }
          v146 = (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 200))(pObj5) == 0;  // 调虚槽 +200：取动画对象
          v147 = -14745736;
          if ( !v146 )  // 若 !v146
LABEL_229:  // 标签 LABEL_229（跳转合流点）
            v147 = -8355712;
          v210 = v147;
          v196 = (int)(pDwArg12 + 13);
          v148 = (void *)sub_4F2CE0(v226);  // v148 = 调 sub_4F2CE0 返回值
          sub_572B20(v69++, v148, v196, v210);  // 绘制链中层 3（4015C0 + 572A90）
          Src = (char *)Src + 1;
        }
        while ( (int)Src < nLen );  // 条件循环
        v231 = v69;
      }
      if ( v233 )  // 若 v233
      {
        v149 = (int *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj9 + 172))(pObj9);  // 调虚槽 +172：朝目标方向按比例取点: p = this + (target − this) × (1 − …
        pObj8 = j;
        v211 = *v149;
        v151 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)j + 228))(j);  // 调虚槽 +228：主状态写入(0自由/1硬直/2冻结)
        sub_572EF0(v151, -14745736, &v231, 1, v211);  // 物品信息窗绘制主函数（725 行：497040 属性枚举 + 571B80/572BC0/572B20 分支 + 47E720 说明）
        v152 = (void *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pObj8 + 232))(pObj8);  // 调虚槽 +232：CNRDObject__vmtE8
        v243 = 15;
        v242 = 0;
        LOBYTE(Block[0]) = 0;
        sub_4015C0(v152, strlen((const char *)v152));  // 【std::string构造赋值】
        v69 = v231;
        if ( v242 != 0 )  // 若 v242 非 0
        {
          v69 = v231 + 1;
          v247 = nullptr;  // v247 = 空指针
          v248 = nullptr;  // v248 = 空指针
          v249 = 0;
          Block3 = (void **)Block[0];
          LOBYTE(v251) = 9;
          if ( v243 < 0x10 )  // 若 v243 < 0x10
            Block3 = Block;
          v154 = (void *)sub_572BC0(Block3, 34, v246);  // 物品信息窗部件构建（186 行：416C40/406D00/4164C0 文本块装配）
          if ( (int)v154 > 0 )  // 若 (int)v154 > 0
          {
            v155 = (char *)v247 + 4;
            for ( j = v154; j != nullptr; j = (char *)j - 1 )  // 遍历循环
            {
              if ( *((uint32_t *)v155 + 5) < 0x10u )  // 若 *((uint32_t *)v155 + 5) < 0x10u
                v156 = v155;
              else  // 否则分支
                v156 = *(void **)v155;
              v157 = pDwArg12 + 13;
              sub_572B20(v69++, v156, (int)(pDwArg12 + 13), -346530);  // 绘制链中层 3（4015C0 + 572A90）
              if ( *((uint32_t *)v155 + 5) < 0x10u )  // 若 *((uint32_t *)v155 + 5) < 0x10u
                v158 = v155;
              else  // 否则分支
                v158 = *(char **)v155;
              v159 = sub_4883E0(v157, v158);  // 转发到 +48 对象虚表 +16
              if ( v227 < v159 )  // 若 v227 < v159
                v227 = v159;
              v155 += 28;
            }
          }
          if ( v247 != nullptr )  // 若 v247 有效（非空）
          {
            v160 = v248;
            if ( v247 != v248 )  // 若 v247 != v248
            {
              v161 = (char *)v247 + 24;
              do  // do-while 循环体起点
              {
                if ( *v161 >= 0x10u )  // 若 *v161 >= 0x10u
                  j__free((void *)*(v161 - 5));  // 调 j__free
                *v161 = 15;  // *v161 写入 15
                *(v161 - 1) = 0;
                *((uint8_t *)v161 - 20) = 0;
                v161 += 7;
              }
              while ( v161 - 6 != v160 );  // 条件循环
            }
            j__free(v247);  // 调 j__free
          }
        }
        LOBYTE(v251) = 0;
        if ( v243 >= 0x10 )  // 若 v243 >= 0x10
          j__free(Block[0]);  // 调 j__free
      }
    }
  }
  v162 = (*((int (/*thiscall*/ **)(void **))*pArg3 + 4))(pArg3);  // 调用虚函数槽 +4
  if ( strcmp((const char *)sub_41ACF0(v162 + 20), szPassword) == 0 )  // 驻留串句柄 → 字符串指针
  {
    pDwArg122 = pDwArg12;
  }
  else  // 否则分支
  {
    ++v69;  // 自增v69
    v247 = nullptr;  // v247 = 空指针
    v248 = nullptr;  // v248 = 空指针
    v249 = 0;
    v163 = (int (/*thiscall*/ **)(void **))*pArg3;
    LOBYTE(v251) = 10;
    v164 = v163[4](pArg3);
    v165 = sub_41ACF0(v164 + 20);  // 驻留串句柄 → 字符串指针
    v166 = (void *)sub_572BC0(v165, 34, v246);  // 物品信息窗部件构建（186 行：416C40/406D00/4164C0 文本块装配）
    pDwArg122 = pDwArg12;
    if ( (int)v166 > 0 )  // 若 (int)v166 > 0
    {
      v168 = (char *)v247 + 4;
      for ( j = v166; j != nullptr; j = (char *)j - 1 )  // 遍历循环
      {
        if ( *((uint32_t *)v168 + 5) < 0x10u )  // 若 *((uint32_t *)v168 + 5) < 0x10u
          v169 = v168;
        else  // 否则分支
          v169 = *(void **)v168;
        sub_572B20(v69++, v169, (int)(pDwArg122 + 13), -6908266);  // 绘制链中层 3（4015C0 + 572A90）
        if ( *((uint32_t *)v168 + 5) < 0x10u )  // 若 *((uint32_t *)v168 + 5) < 0x10u
          v170 = v168;
        else  // 否则分支
          v170 = *(char **)v168;
        v171 = sub_4883E0(pDwArg122 + 13, v170);  // 转发到 +48 对象虚表 +16
        if ( v227 < v171 )  // 若 v227 < v171
          v227 = v171;
        v168 += 28;
      }
    }
    LOBYTE(v251) = 0;
    if ( v247 != nullptr )  // 若 v247 有效（非空）
    {
      if ( v247 != v248 )  // 若 v247 != v248
      {
        v172 = (char *)v247 + 24;
        do  // do-while 循环体起点
        {
          if ( *v172 >= 0x10u )  // 若 *v172 >= 0x10u
            j__free((void *)*(v172 - 5));  // 调 j__free
          v173 = v248;
          *v172 = 15;  // *v172 写入 15
          *(v172 - 1) = 0;
          *((uint8_t *)v172 - 20) = 0;
          v172 += 7;
        }
        while ( v172 - 6 != v173 );  // 条件循环
      }
      j__free(v247);  // 调 j__free
    }
  }
  if ( pObj9 == nullptr && (unsigned int)dword_795378 <= 1 )  // 若 pObj9 == nullptr
  {
    Src = *pArg3;
    v174 = (*((int (/*thiscall*/ **)(void **))Src + 4))(pArg3);  // 调用虚函数槽 +4
    if ( (*((uint8_t (/*thiscall*/ **)(void **, uint32_t))Src + 15))(pArg3, *(uint32_t *)(v174 + 4)) != 0
      && *(uint32_t *)(*((int (/*thiscall*/ **)(void **))*pArg3 + 33))(pArg3) == 0 )
    {
      v175 = v69 + 1;
      v176 = (void *)sub_422E70(1060);  // v176 = 调 sub_422E70 返回值
      sub_572B20(v175, v176, (int)(pDwArg122 + 39), -346530);  // 绘制链中层 3（4015C0 + 572A90）
      v69 = v175 + 1;
    }
  }
  if ( dword_795378 == 4 )  // 若 dword_795378 == 4
  {
    v177 = v69 + 1;
    v178 = (void *)sub_422E70(1061);  // v178 = 调 sub_422E70 返回值
    sub_572B20(v177, v178, (int)(pDwArg122 + 39), -346530);  // 绘制链中层 3（4015C0 + 572A90）
    if ( pObj9 == nullptr )  // 若 pObj9 为空
    {
      ++v177;  // 自增v177
      v179 = (void *)sub_422E70(1062);  // v179 = 调 sub_422E70 返回值
      sub_572B20(v177, v179, (int)(pDwArg122 + 39), -346530);  // 绘制链中层 3（4015C0 + 572A90）
    }
    v69 = v177 + 1;
  }
  if ( dword_795378 == 9 && sub_541A40() == 2 )  // 摊位结构初始化（18 行）
  {
    v180 = v69 + 1;
    v181 = (void *)sub_422E70(1061);  // v181 = 调 sub_422E70 返回值
    sub_572B20(v180, v181, (int)(pDwArg122 + 39), -346530);  // 绘制链中层 3（4015C0 + 572A90）
    v69 = v180 + 1;
  }
  if ( dword_795378 == 12 )  // 若 dword_795378 == 12
  {
    v182 = v69 + 1;
    v183 = (void *)sub_422E70(2055);  // v183 = 调 sub_422E70 返回值
    sub_572B20(v182, v183, (int)(pDwArg122 + 39), -346530);  // 绘制链中层 3（4015C0 + 572A90）
    v69 = v182 + 1;
  }
  pDwArg122[69] = v69 / 36;
  v184 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg122[25] + 20))(pDwArg122[25]);  // 调用虚函数槽 +20
  v185 = v227;
  v186 = *pDwArg122;
  pDwArg122[20] = v227;
  (*(void (/*thiscall*/ **)(int *, int, int))(v186 + 52))(pDwArg122, v185, v69 * (v184 + 1));  // 调用虚函数槽 +52
  v187 = pDwArg122[2];  // v187 = 取 pDwArg122[2]
  *(uint32_t *)(v187 + 28) = 0;  // v187+28 = 0
  *(uint32_t *)(v187 + 32) = 0;  // v187+32 = 0
  if ( v239 >= 0x10 )  // 若 v239 >= 0x10
    j__free(v238[0]);  // 调 j__free
  return 1;  // 返回 1(成功)
}


// ------------------------------------------------------------
// 0x575F80 CNRDItemInfoWindow__vmtC —— CNRDItemInfoWindow__vmtC 打开入口（直接调 5745B0 完整绘制）
// ------------------------------------------------------------
char /*userpurge*/ CNRDItemInfoWindow__vmtC@<al>(char *pszArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4)  // 实现：CNRDItemInfoWindow__vmtC 打开入口（直接调 5745B0 完整绘制）
{
  int v6; // eax
  int v7; // edx

  dword_9B88D0 = nArg3;
  *((uint32_t *)pszArg1 + 69) = 0;
  if ( nArg3 == 0 )  // 若 nArg3 为 0
    return 0;
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)pszArg1 + 28))(pszArg1, 1);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
  dword_795378 = nArg4;
  if ( sub_5745B0(pszArg1, nArg2, dword_9B88D0) == 0 )  // 物品信息窗完整绘制（1226 行·全文件最大：5486B0/541A30/542AB0 各类型说明 + 406D60/402410 文本 + 572EF0 …
    return 0;
  v6 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pszArg1 + 56))(pszArg1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
  v7 = *(uint32_t *)pszArg1;  // v7 = pszArg1
  *((uint32_t *)pszArg1 + 67) = v6;
  *((uint32_t *)pszArg1 + 68) = (*(int (/*thiscall*/ **)(char *))(v7 + 60))(pszArg1);
  return 1;  // 返回 1(成功)
}



// ============================================================
// 【分区 5】GenericHTTPClient —— WinINet HTTP 客户端·连接与发送（0x575FF0-0x576ED0）
// 句柄链: InternetOpenA(代理预配置) → InternetConnectA(SERVICE_HTTP=3,
//   flags 0x4400000=DONT_CACHE|KEEP_CONNECTION) → HttpOpenRequestA("HTTP/1.0",
//   Accept */*) → HttpSendRequestA / HttpSendRequestExA+InternetWriteFile。
// 每步失败均把 GetLastError() 存 this+200032 并逐级关句柄。
// ============================================================
// ------------------------------------------------------------
// 0x575FF0 sub_575FF0 —— Connect()：InternetOpenA(代理预配置)→InternetConnectA(SERVICE_HTTP=3, flags 0x4400000)→InternetAttemptConnect(0)；句柄入 +200020/+200024，日志 "_hHTTPConnection=::InternetConnect()  start/end"
// ------------------------------------------------------------
// this+200020 = hInternet（InternetOpenA 句柄）；this+200024 = hConnect（InternetConnectA 句柄）；
// 任一步失败：+200032 = GetLastError() 并逐级 CloseHandle 返回 0。
int /*thiscall*/ sub_575FF0(  // Connect()：InternetOpenA(代理预配置)→InternetConnectA(SERVICE_HTTP=3, flags 0x440000…
        int this,
        const CHAR *lpszServerName,
        const CHAR *lpszAgent,
        INTERNET_PORT nServerPort,
        const CHAR *lpszUserName,
        const CHAR *lpszPassword)
{
  HINTERNET v7; // eax
  DWORD LastError; // eax
  void *v10; // [esp-8h] [ebp-Ch]

  v7 = InternetOpenA(lpszAgent, 0, szPassword, szPassword, 0);  // v7 = 调 InternetOpenA
  *(uint32_t *)(this + 200020) = v7;  // this+200020 = v7
  if ( v7 != nullptr )  // 若 v7 有效（非空）
  {
    off_77F3FC("_hHTTPConnection=::InternetConnect()  start");
    *(uint32_t *)(this + 200024) = InternetConnectA(
                                   *(HINTERNET *)(this + 200020),
                                   lpszServerName,
                                   nServerPort,
                                   lpszUserName,
                                   lpszPassword,
                                   3u,
                                   0x4400000u,
                                   0);
    off_77F3FC("_hHTTPConnection=::InternetConnect()  end");
    if ( *(uint32_t *)(this + 200024) != 0 )  // 若 *(uint32_t *)(this + 200024) != 0
    {
      if ( InternetAttemptConnect(0) != 0 )  // 若 InternetAttemptConnect(0) != 0
      {
        LastError = GetLastError();  // LastError = 调 GetLastError
        v10 = *(void **)(this + 200024);
        *(uint32_t *)(this + 200032) = LastError;  // this+200032 = LastError
        CloseHandle(v10);  // 调 CloseHandle 关闭句柄
        CloseHandle(*(HANDLE *)(this + 200020));  // 调 CloseHandle 关闭句柄
        return 0;
      }
      else  // 否则分支
      {
        return 1;  // 返回 1(成功)
      }
    }
    else  // 否则分支
    {
      *(uint32_t *)(this + 200032) = GetLastError();  // this+200032 = GetLastError()
      CloseHandle(*(HANDLE *)(this + 200020));  // 调 CloseHandle 关闭句柄
      return 0;
    }
  }
  else  // 否则分支
  {
    *(uint32_t *)(this + 200032) = GetLastError();  // this+200032 = GetLastError()
    return 0;
  }
}



// ------------------------------------------------------------
// 0x5760E0 sub_5760E0 —— 请求 GET：HttpOpenRequestA(hConnect, 动词=off_726478("GET"), obj, "HTTP/1.0", Accept */*, flags 0x4400000)→头 "Accept: */*\r\n"→HttpSendRequestA(无正文)；句柄入 +200028
// ------------------------------------------------------------
// off_726478 指向动词串 "GET"；本函数即模式 1 的发送实现。
int /*thiscall*/ sub_5760E0(int this, LPCSTR lpszObjectName)  // 实现：请求 GET：HttpOpenRequestA(hConnect, 动词=off_726478(GET), obj, HTTP/1.0, A…
{
  void *v3; // eax
  void *fld_30D58; // [esp-20h] [ebp-28h]
  LPCSTR lpszAcceptTypes; // [esp+4h] [ebp-4h] BYREF

  fld_30D58 = *(void **)(this + 200024);
  lpszAcceptTypes = "*/*";
  v3 = HttpOpenRequestA(fld_30D58, off_726478, lpszObjectName, "HTTP/1.0", szPassword, &lpszAcceptTypes, 0x4400000u, 0);  // v3 = 调 HttpOpenRequestA
  *(uint32_t *)(this + 200028) = v3;  // this+200028 = v3
  if ( v3 != nullptr  // 若 v3 != nullptr
    && HttpAddRequestHeadersA(v3, "Accept: */*\r\n", 0xDu, 0x80000000)
    && HttpSendRequestA(*(HINTERNET *)(this + 200028), nullptr, 0, nullptr, 0) )  // 函数: 恒返回 1
  {
    return 1;  // 返回 1(成功)
  }
  *(uint32_t *)(this + 200032) = GetLastError();  // this+200032 = GetLastError()
  return 0;
}



// ------------------------------------------------------------
// 0x576180 sub_576180 —— ReadResponse()：InternetReadFile 按 0x400(1024) 字节块循环读入 this+20（累计上限 0x186A0=100000），随后 HttpQueryInfoA(0x16=RAW_HEADERS_CRLF) 取原始响应头入 this+100020
// ------------------------------------------------------------
// dwNumberOfBytesRead==0（对端关闭）即结束读取；读失败/查询失败把错误存 +200032（dword 索引 50008）。
BOOL /*thiscall*/ sub_576180(  // ReadResponse()：InternetReadFile 按 0x400(1024) 字节块循环读入 this+20（累计上限 0x186A0=100…
        uint32_t *this,
        LPVOID lpBuffer,
        DWORD dwBufferLength,
        char *a4,
        unsigned int a5,
        unsigned int *a6)
{
  uint32_t *v6; // esi
  unsigned int *v8; // ebx
  void *v9; // edx
  DWORD v10; // edx
  uint32_t Buffer[257]; // [esp+Ch] [ebp-404h] BYREF

  Buffer[256] = dword_796E50;
  v6 = this;
  memset(Buffer, 0, 1024);  // 清零 Buffer 起 1024 字节
  if ( *(this + 50007) != 0 )  // 若 *(this + 50007) != 0
  {
    memset(a4, 0, a5);  // 调 memset 按字节填充
    v8 = a6;
    *a6 = 0;  // *a6 写入 0
    while ( 1 )  // 条件循环
    {
      v9 = (void *)v6[50007];
      if ( v9 == nullptr )  // 若 v9 为空
        break;  // 跳出循环/分支
      memset(Buffer, 0, 0x400u);  // 清零 Buffer 起 0x400 字节
      if ( !InternetReadFile(v9, Buffer, 0x400u, &dwNumberOfBytesRead) )  // 若 !InternetReadFile(v9, Buffer, 0x400u, &dwNumberOfBytesRead)
        break;  // 跳出循环/分支
      v10 = dwNumberOfBytesRead;
      if ( dwNumberOfBytesRead == 0 || *v8 >= a5 )  // 若 dwNumberOfBytesRead == 0
        goto LABEL_10;  // 跳转 LABEL_10
      qmemcpy(&a4[*v8], Buffer, dwNumberOfBytesRead);  // 调 qmemcpy 内联块拷贝
      v6 = this;
      *v8 += v10;
    }
    v6[50008] = GetLastError();  // v6[50008] = 调 GetLastError
LABEL_10:  // 标签 LABEL_10（跳转合流点）
    memset(lpBuffer, 0, dwBufferLength);  // 调 memset 按字节填充
    if ( HttpQueryInfoA((HINTERNET)v6[50007], 0x16u, lpBuffer, &dwBufferLength, nullptr) )  // 空指针判定
    {
      return *v8 != 0;
    }
    else  // 否则分支
    {
      v6[50008] = GetLastError();  // v6[50008] = 调 GetLastError
      return false;
    }
  }
  else  // 否则分支
  {
    *(this + 50008) = GetLastError();  // this+200032 = GetLastError()
    return false;
  }
}



// ------------------------------------------------------------
// 0x5762F0 sub_5762F0 —— LocalFree 包装：释放 *a1 并置空（multipart 正文缓冲清理用）
// ------------------------------------------------------------
HLOCAL /*stdcall*/ sub_5762F0(HLOCAL *uArg1)  // LocalFree 包装：释放 *a1 并置空（multipart 正文缓冲清理用）
{
  HLOCAL result; // eax

  result = *uArg1;
  if ( *uArg1 != nullptr )  // 空指针判定
  {
    result = LocalFree(*uArg1);  // result = 调 LocalFree
    *uArg1 = nullptr;  // *uArg1 写入 nullptr
  }
  return result;
}



// ------------------------------------------------------------
// 0x576310 sub_576310 —— 文件扩展名→Content-Type：RegOpenKeyExA(HKEY_CLASSES_ROOT, ".ext") 查 "Content Type"，失败/缺省 "application/octet-stream"
// ------------------------------------------------------------
BYTE */*stdcall*/ sub_576310(HKEY phkResult)  // 实现：文件扩展名→Content-Type：RegOpenKeyExA(HKEY_CLASSES_ROOT, .ext) 查 Content Ty…
{
  HKEY v1; // edi
  unsigned int i; // esi
  DWORD cbData; // [esp+8h] [ebp-4h] BYREF

  v1 = phkResult;
  cbData = 1024;
  for ( i = strlen((const char *)phkResult); i != 0; --i )  // 遍历循环
  {
    if ( strncmp((const char *)v1 + i, ".", 1u) == 0 )
      break;  // 跳出循环/分支
  }
  if ( RegOpenKeyExA(HKEY_CLASSES_ROOT, (LPCSTR)v1 + i, 0, 1u, &phkResult) != 0 )  // 若 RegOpenKeyExA(HKEY_CLASSES_ROOT, (LPCSTR)v1 + i, 0, 1u, &phkRe..
  {
    strncpy((char *)Destination, "application/octet-stream", 0x18u);  // 调 strncpy 限长串拷贝
    return Destination;
  }
  else  // 否则分支
  {
    if ( RegQueryValueExA(phkResult, "Content Type", nullptr, nullptr, Destination, &cbData) != 0 )  // 空指针判定
      strncpy((char *)Destination, "application/octet-stream", 0x18u);  // 调 strncpy 限长串拷贝
    RegCloseKey(phkResult);
    return Destination;
  }
}



// ------------------------------------------------------------
// 0x5763D0 sub_5763D0 —— URL 解析器：拆 scheme(缺省 http；https→端口 443 否则 80)/host[:port]/path 四段输出；端口显式存在时 atol 提取
// ------------------------------------------------------------
char */*stdcall*/ sub_5763D0(char *Source, char *Destination, char *pszArg3, int *pDwArg4, char *pszArg5)  // 实现：URL 解析器：拆 scheme(缺省 http；https→端口 443 否则 80)/host/path 四段输出；端口显式存在时 at…
{
  size_t i; // ebx
  unsigned int psz4; // ebx
  unsigned int psz5; // edx
  unsigned int psz3; // esi
  const char *psz; // edi
  unsigned int psz2; // [esp+Ch] [ebp-408h]
  char String[1024]; // [esp+10h] [ebp-404h] BYREF
  int dword_796E502; // [esp+410h] [ebp-4h]

  dword_796E502 = dword_796E50;
  for ( i = 0; strlen(Source) != 0; ++i )  // 遍历循环
  {
    if ( i >= strlen(Source) )  // 若 i >= strlen(Source)
      break;  // 跳出循环/分支
    if ( strncmp(&Source[i], ":", 1u) == 0 )
      break;  // 跳出循环/分支
  }
  if ( strncmp(&Source[i + 1], "/", 1u) == 0 )
  {
    if ( Destination != nullptr )  // 若 Destination 有效（非空）
    {
      strncpy(Destination, Source, i);  // 调 strncpy 限长串拷贝
      Destination[i] = 0;
    }
    psz4 = i + 3;
    psz5 = psz4;
    psz2 = psz4;
  }
  else  // 否则分支
  {
    if ( Destination != nullptr )  // 若 Destination 有效（非空）
    {
      strncpy(Destination, "http", 4u);  // 调 strncpy 限长串拷贝
      Destination[5] = 0;
    }
    psz4 = 0;
    psz2 = 0;
    psz5 = 0;
  }
  if ( strlen(Source) != 0 )  // 若 strlen(Source) != 0
  {
    while ( psz4 < strlen(Source) )  // 条件循环
    {
      if ( strncmp(&Source[psz4], "/", 1u) == 0 || (++psz4, strlen(Source) == 0) )  // 复合条件判定（与/或）
      {
        psz5 = psz2;
        break;  // 跳出循环/分支
      }
      psz5 = psz2;
    }
  }
  psz3 = psz5;
  if ( psz5 > psz4 )  // 若 psz5 > psz4
  {
LABEL_23:  // 标签 LABEL_23（跳转合流点）
    if ( strcmp(Destination, "https") == 0 )
      *pDwArg4 = 443;  // *pDwArg4 写入 443
    else  // 否则分支
      *pDwArg4 = 80;  // *pDwArg4 写入 80
    strncpy(pszArg3, &Source[psz5], psz4 - psz5);  // 调 strncpy 限长串拷贝
    psz = Source;
  }
  else  // 否则分支
  {
    while ( strncmp(&Source[psz3], ":", 1u) != 0 )  // 条件循环
    {
      if ( ++psz3 > psz4 )  // 若 ++psz3 > psz4
      {
        psz5 = psz2;
        goto LABEL_23;  // 跳转 LABEL_23
      }
    }
    memset(String, 0, sizeof(String));  // 调 memset 按字节填充
    psz = Source;
    strncpy(String, &Source[psz3 + 1], psz4 - psz3);  // 调 strncpy 限长串拷贝
    *pDwArg4 = atol(String);  // *pDwArg4 写入 atol(String)
    strncpy(pszArg3, &Source[psz2], psz3 - psz2);  // 调 strncpy 限长串拷贝
  }
  if ( psz4 < strlen(psz) )  // 若 psz4 < strlen(psz)
    return strncpy(pszArg5, &psz[psz4], strlen(psz) - psz4);  // 返回 调 strncpy
  *pszArg5 = 0;  // *pszArg5 写入 0
  return pszArg5;
}



// ------------------------------------------------------------
// 0x576650 sub_576650 —— urlencoded 正文构造：遍历字段表（步进 1284）拼 name=value，分隔符 61'='/38'&'，容量 0x400
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_576650(const char **this, char *pszArg2, unsigned int uArg3)  // 实现：urlencoded 正文构造：遍历字段表（步进 1284）拼 name=value，分隔符 61=/38&，容量 0x400
{
  const char *fld_e2; // eax
  const char *v5; // ecx
  const char *psz; // [esp+18h] [ebp+8h]

  memset(pszArg2, 0, uArg3);  // 调 memset 按字节填充
  fld_e2 = *(this + 2);  // fld_e2 = this+2
  psz = fld_e2;
  if ( fld_e2 < *(this + 3) )  // 若 fld_e2 < *(this + 3)
  {
    while ( 1 )  // 条件循环
    {
      strcat(pszArg2, fld_e2);  // 拼字符串
      *(uint16_t *)&pszArg2[strlen(pszArg2)] = 61;
      strcat(pszArg2, psz + 256);  // 拼字符串
      v5 = psz + 1284;
      psz += 1284;
      if ( psz >= *(this + 3) )  // 若 psz >= *(this + 3)
        break;  // 跳出循环/分支
      *(uint16_t *)&pszArg2[strlen(pszArg2)] = 38;
      if ( v5 >= *(this + 3) )  // 若 v5 >= *(this + 3)
        break;  // 跳出循环/分支
      fld_e2 = psz;
    }
  }
  pszArg2[uArg3] = 0;
  return strlen(pszArg2);  // 返回 调 strlen
}



// ------------------------------------------------------------
// 0x576760 sub_576760 —— multipart 正文长度预算：文本字段 0x2000/个、文件字段 GetFileSize+6144/个（字段类型在表项 +1280：1=文本 2=文件）
// ------------------------------------------------------------
int /*fastcall*/ sub_576760(int pArg1)  // 实现：multipart 正文长度预算：文本字段 0x2000/个、文件字段 GetFileSize+6144/个（字段类型在表项 +1280：1…
{
  unsigned int v1; // ebx
  int v2; // edi
  HANDLE FileA; // esi
  int i; // [esp+8h] [ebp-4h]

  v1 = *(uint32_t *)(pArg1 + 8);  // v1 = pArg1+8
  v2 = 0;
  for ( i = pArg1; v1 < *(uint32_t *)(pArg1 + 12); v1 += 1284 )  // 遍历循环
  {
    if ( *(uint32_t *)(v1 + 1280) == 1 )  // 若 *(uint32_t *)(v1 + 1280) == 1
    {
      v2 += 0x2000;
    }
    else if ( *(uint32_t *)(v1 + 1280) == 2 )  // 否则若 *(uint32_t *)(v1 + 1280) == 2
    {
      FileA = CreateFileA((LPCSTR)(v1 + 256), 0x80000000, 1u, nullptr, 3u, 0x80u, nullptr);  // FileA = 调 CreateFileA
      v2 += GetFileSize(FileA, nullptr) + 6144;
      CloseHandle(FileA);  // 调 CloseHandle 关闭句柄
      pArg1 = i;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x5767E0 sub_5767E0 —— 请求 POST-urlencoded（模式 2）：HttpOpenRequestA("POST", flags 0x4400040) + 头 "Content-Type: application/x-www-form-urlencoded\r\n" + HttpSendRequestA(正文=576650 产物)
// ------------------------------------------------------------
// 正文即 k=v&k=v 串，经 HttpSendRequestA 的 lpOptional 参数随请求体发送。
int /*thiscall*/ sub_5767E0(int this, LPCSTR lpszObjectName)  // 实现：请求 POST-urlencoded（模式 2）：HttpOpenRequestA(POST, flags 0x4400040) + 头 C…
{
  void *fld_30D58; // eax
  LPCSTR lpszAcceptTypes; // [esp+8h] [ebp-408h] BYREF
  char Optional[1024]; // [esp+Ch] [ebp-404h] BYREF
  int dword_796E502; // [esp+40Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  memset(Optional, 0, sizeof(Optional));  // 调 memset 按字节填充
  lpszAcceptTypes = "*/*";
  sub_576650((const char **)this, Optional, 0x400u);  // urlencoded 正文构造：遍历字段表（步进 1284）拼 name=value，分隔符 61=/38&，容量 0x400
  fld_30D58 = HttpOpenRequestA(
         *(HINTERNET *)(this + 200024),
         "POST",
         lpszObjectName,
         "HTTP/1.0",
         szPassword,
         &lpszAcceptTypes,
         0x4400040u,
         0);
  *(uint32_t *)(this + 200028) = fld_30D58;  // this+200028 = fld_30D58
  if ( fld_30D58 != nullptr  // 若 fld_30D58 != nullptr
    && HttpAddRequestHeadersA(fld_30D58, "Accept: */*\r\n", 0xDu, 0x80000000)
    && HttpSendRequestA(
         *(HINTERNET *)(this + 200028),
         "Content-Type: application/x-www-form-urlencoded\r\n",
         strlen("Content-Type: application/x-www-form-urlencoded\r\n"),
         Optional,
         strlen(Optional)) )  // 函数: 恒返回 1
  {
    return 1;  // 返回 1(成功)
  }
  *(uint32_t *)(this + 200032) = GetLastError();  // this+200032 = GetLastError()
  return 0;
}



// ------------------------------------------------------------
// 0x576900 sub_576900 —— multipart 正文装配（LocalAlloc 缓冲）：文本项 "--BOUNDARY\r\nContent-Disposition: form-data; name=\"%s\"\r\n\r\n%s\r\n"；文件项 + filename=\"%s\" + Content-Type(576310) + 文件字节（ReadFile 0x400 循环）+ 0x0A0D("\r\n")；收尾 "--"+BOUNDARY+"--"+'\r'
// ------------------------------------------------------------
// word 常量：2573=0x0A0D("\r\n")、11565=0x2D2D("--")；字段名/路径在表项 +256，类型在 +1280。
unsigned int /*thiscall*/ sub_576900(const char **this, HLOCAL *uArg2, const char *pArg3)  // 实现：multipart 正文装配（LocalAlloc 缓冲）：文本项 --BOUNDARY\r\nContent-Disposition: f…
{
  HLOCAL *uArg22; // ebx
  SIZE_T v5; // eax
  HLOCAL (/*stdcall*/ *v6)(UINT, SIZE_T); // edi
  const char *fld_e2; // eax
  unsigned int fld_e3; // edx
  HKEY v9; // esi
  char *psz; // ebx
  const char *v11; // eax
  unsigned int nLen4; // edx
  unsigned int v13; // esi
  int v14; // eax
  unsigned int nLen5; // edx
  bool fld_e32; // cf
  unsigned int nLen2; // ecx
  char *v18; // eax
  int v19; // ebx
  unsigned int nLen3; // eax
  DWORD FileSize; // [esp+8h] [ebp-42Ch]
  unsigned int j; // [esp+Ch] [ebp-428h]
  HKEY i; // [esp+14h] [ebp-420h]
  HANDLE hFile; // [esp+18h] [ebp-41Ch]
  DWORD NumberOfBytesRead; // [esp+1Ch] [ebp-418h] BYREF
  int v28; // [esp+20h] [ebp-414h]
  const char *fld_e22; // [esp+24h] [ebp-410h]
  DWORD nLen; // [esp+28h] [ebp-40Ch]
  uint8_t Buffer[1028]; // [esp+2Ch] [ebp-408h] BYREF
  int dword_796E502; // [esp+430h] [ebp-4h]

  uArg22 = uArg2;
  dword_796E502 = dword_796E50;
  if ( *uArg2 != nullptr )  // 空指针判定
  {
    LocalFree(*uArg2);
    *uArg2 = nullptr;  // *uArg2 写入 nullptr
  }
  v5 = sub_576760(this);  // multipart 正文长度预算：文本字段 0x2000/个、文件字段 GetFileSize+6144/个（字段类型在表项 +1280：1=文本 2=文件…
  v6 = LocalAlloc;
  *uArg2 = LocalAlloc(0x40u, v5);  // *uArg2 写入 LocalAlloc(0x40u, v5)
  fld_e2 = *(this + 2);  // fld_e2 = this+2
  fld_e3 = (unsigned int)*(this + 3);
  v28 = 0;
  nLen = 0;
  fld_e22 = fld_e2;
  if ( (unsigned int)fld_e2 < fld_e3 )  // 若 (unsigned int)fld_e2 < fld_e3
  {
    v9 = (HKEY)(fld_e2 + 256);
    for ( i = (HKEY)(fld_e2 + 256); ; v9 = i )  // 遍历循环
    {
      psz = nullptr;  // psz = 空指针
      if ( *((uint32_t *)v9 + 256) == 1 )  // 若 *((uint32_t *)v9 + 256) == 1
      {
        psz = (char *)v6(0x40u, 0x2000u);
        sprintf(psz, "--%s\r\nContent-Disposition: form-data; name=\"%s\"\r\n\r\n%s\r\n", pArg3, fld_e22, (const char *)v9);  // 拼字符串（模板 --%s\r\nContent-Disposition: f…）
        nLen = strlen(psz);  // nLen = 调 strlen
      }
      else if ( *((uint32_t *)v9 + 256) == 2 )  // 否则若 *((uint32_t *)v9 + 256) == 2
      {
        NumberOfBytesRead = 0;
        nLen = 0;
        hFile = CreateFileA((LPCSTR)v9, 0x80000000, 1u, nullptr, 3u, 0x8000080u, nullptr);  // hFile = 调 CreateFileA
        FileSize = GetFileSize(hFile, nullptr);  // FileSize = 调 GetFileSize
        psz = (char *)v6(0x40u, FileSize + 6145);
        memset(Buffer, 0, 1025);  // 清零 Buffer 起 1025 字节
        v11 = (const char *)sub_576310(v9);  // 文件扩展名→Content-Type：RegOpenKeyExA(HKEY_CLASSES_ROOT, .ext) 查 Content Type，失败/缺省…
        sprintf(  // 拼字符串
          psz,
          "--%s\r\nContent-Disposition: form-data; name=\"%s\"; filename=\"%s\"\r\nContent-Type: %s\r\n\r\n",
          pArg3,
          fld_e22,
          (const char *)v9,
          v11);
        for ( j = strlen(psz); ReadFile(hFile, Buffer, 0x400u, &NumberOfBytesRead, nullptr); nLen = NumberOfBytesRead  // 遍历循环
                                                                                                 + nLen4 )
        {
          if ( NumberOfBytesRead == 0 )  // 若 NumberOfBytesRead 为 0
            break;  // 跳出循环/分支
          nLen4 = nLen;
          if ( nLen > FileSize )  // 若 nLen > FileSize
            break;  // 跳出循环/分支
          qmemcpy(&psz[j + nLen], Buffer, NumberOfBytesRead);  // 调 qmemcpy 内联块拷贝
          memset(Buffer, 0, 1025);  // 清零 Buffer 起 1025 字节
        }
        v13 = j + nLen;
        *(uint16_t *)&psz[j + nLen] = 2573;
        CloseHandle(hFile);  // 调 CloseHandle 关闭句柄
        nLen = v13 + 2;
      }
      v14 = v28;
      nLen5 = nLen;
      qmemcpy((char *)*uArg2 + v28, psz, nLen);  // 调 qmemcpy 内联块拷贝
      v28 = nLen5 + v14;
      if ( psz != nullptr )  // 若 psz 有效（非空）
        LocalFree(psz);
      fld_e32 = fld_e22 + 1284 < *(this + 3);
      fld_e22 += 1284;
      i += 321;
      if ( !fld_e32 )  // 若 !fld_e32
        break;  // 跳出循环/分支
      v6 = LocalAlloc;
    }
    uArg22 = uArg2;
  }
  *(uint16_t *)((char *)*uArg22 + v28) = 11565;
  nLen2 = strlen(pArg3);  // nLen2 = 调 strlen
  v18 = (char *)*uArg22;
  v19 = v28;
  qmemcpy(&v18[v28 + 2], pArg3, nLen2);  // 调 qmemcpy 内联块拷贝
  nLen3 = (unsigned int)*uArg2 + strlen(pArg3) + v19 + 2;
  *(uint16_t *)nLen3 = 11565;
  *(uint8_t *)(nLen3 + 2) = 13;  // nLen3+2 = 13
  return strlen(pArg3) + v19 + 5;  // 返回 调 strlen
}


// ------------------------------------------------------------
// 0x576C40 sub_576C40 —— 请求 POST-multipart（模式 3）：boundary=--MULTI-PARTS-FORM-DATA-BOUNDARY；头 Accept + Content-Type(multipart) + "Content-Length: %d"（均 ADDREQ_FLAG_REPLACE 0x10000000）；HttpSendRequestExA→InternetWriteFile(576900 缓冲)→HttpEndRequestA
// ------------------------------------------------------------
// 发送完成后 5762F0 释放正文缓冲；任一步失败错误入 +200032。
int /*thiscall*/ sub_576C40(int this, LPCSTR lpszObjectName)  // 实现：请求 POST-multipart（模式 3）：boundary=--MULTI-PARTS-FORM-DATA-BOUNDARY；头 Ac…
{
  void *fld_30D58; // eax
  DWORD v5; // edi
  void *fld_30D5C; // ecx
  void *v7; // [esp-18h] [ebp-458h]
  struct _INTERNET_BUFFERSA BuffersIn; // [esp+4h] [ebp-43Ch] BYREF
  DWORD dwNumberOfBytesWritten; // [esp+2Ch] [ebp-414h] BYREF
  LPCSTR lpszAcceptTypes; // [esp+30h] [ebp-410h] BYREF
  DWORD dwNumberOfBytesToWrite; // [esp+34h] [ebp-40Ch]
  LPCVOID lpBuffer; // [esp+38h] [ebp-408h] BYREF
  CHAR szHeaders[1024]; // [esp+3Ch] [ebp-404h] BYREF
  int dword_796E502; // [esp+43Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  lpszAcceptTypes = "*/*";
  lpBuffer = nullptr;  // lpBuffer = 空指针
  dwNumberOfBytesToWrite = sub_576900((const char **)this, (HLOCAL *)&lpBuffer, "--MULTI-PARTS-FORM-DATA-BOUNDARY");  // multipart 正文装配（LocalAlloc 缓冲）：文本项 --BOUNDARY\r\nContent-Disposition: form-data…
  fld_30D58 = HttpOpenRequestA(
         *(HINTERNET *)(this + 200024),
         "POST",
         lpszObjectName,
         "HTTP/1.0",
         szPassword,
         &lpszAcceptTypes,
         0x4400040u,
         0);
  *(uint32_t *)(this + 200028) = fld_30D58;  // this+200028 = fld_30D58
  if ( fld_30D58 != nullptr  // 若 fld_30D58 != nullptr
    && HttpAddRequestHeadersA(fld_30D58, "Accept: */*\r\n", 0xDu, 0x80000000)
    && HttpAddRequestHeadersA(
         *(HINTERNET *)(this + 200028),
         "Content-Type: multipart/form-data; boundary=--MULTI-PARTS-FORM-DATA-BOUNDARY\r\n",
         strlen("Content-Type: multipart/form-data; boundary=--MULTI-PARTS-FORM-DATA-BOUNDARY\r\n"),
         0x10000000u) )
  {
    memset(szHeaders, 0, sizeof(szHeaders));  // 调 memset 按字节填充
    v5 = dwNumberOfBytesToWrite;
    sprintf(szHeaders, "Content-Length: %d\r\n", dwNumberOfBytesToWrite);  // 拼字符串（模板 Content-Length: %d\r\n）
    if ( HttpAddRequestHeadersA(*(HINTERNET *)(this + 200028), szHeaders, strlen(szHeaders), 0x10000000u)  // 若 HttpAddRequestHeadersA(*(HINTERNET *)(this + 200028), szHeader..
      && (fld_30D5C = *(void **)(this + 200028),
          BuffersIn.dwStructSize = 40,
          memset(&BuffersIn.Next, 0, 36),
          HttpSendRequestExA(fld_30D5C, &BuffersIn, nullptr, 8u, 0))
      && (v7 = *(void **)(this + 200028),
          dwNumberOfBytesWritten = 0,
          InternetWriteFile(v7, lpBuffer, v5, &dwNumberOfBytesWritten))
      && HttpEndRequestA(*(HINTERNET *)(this + 200028), nullptr, 8u, 0) )
    {
      sub_5762F0((HLOCAL *)&lpBuffer);  // LocalFree 包装：释放 *a1 并置空（multipart 正文缓冲清理用）
      return 1;  // 返回 1(成功)
    }
    else  // 否则分支
    {
      *(uint32_t *)(this + 200032) = GetLastError();  // this+200032 = GetLastError()
      return 0;
    }
  }
  else  // 否则分支
  {
    *(uint32_t *)(this + 200032) = GetLastError();  // this+200032 = GetLastError()
    return 0;
  }
}



// ------------------------------------------------------------
// 0x576E90 sub_576E90 —— 请求模式分发：a3==2→5767E0(urlencoded POST)；a3==3→576C40(multipart POST)；其余→5760E0(GET)
// ------------------------------------------------------------
int /*thiscall*/ sub_576E90(void *this, LPCSTR lpszObjectName, int nArg3)  // 实现：请求模式分发：a3==2→5767E0(urlencoded POST)；a3==3→576C40(multipart POST)；其余→5…
{
  if ( nArg3 == 2 )  // 若 nArg3 == 2
    return sub_5767E0((int)this, lpszObjectName);  // 请求 POST-urlencoded（模式 2）：HttpOpenRequestA(POST, flags 0x4400040) + 头 Content-T…
  if ( nArg3 == 3 )  // 若 nArg3 == 3
    return sub_576C40((int)this, lpszObjectName);  // 请求 POST-multipart（模式 3）：boundary=--MULTI-PARTS-FORM-DATA-BOUNDARY；头 Accept + C…
  return sub_5760E0((int)this, lpszObjectName);  // 请求 GET：HttpOpenRequestA(hConnect, 动词=off_726478(GET), obj, HTTP/1.0, Accept *,…
}



// ------------------------------------------------------------
// 0x576ED0 sub_576ED0 —— GenericHTTPClient 构造/复位：vftbl 装配、清句柄 50005/50006/50007（+200020/24/28），释放并清空字段表指针（+2..+4）
// ------------------------------------------------------------
void /*thiscall*/ sub_576ED0(void *this)  // 实现：GenericHTTPClient 构造/复位：vftbl 装配、清句柄 50005/50006/50007（+200020/24/28），…
{
  *(uint32_t *)this = &vftbl_GenericHTTPClient;
  *((uint32_t *)this + 50007) = 0;
  *((uint32_t *)this + 50006) = 0;
  *((uint32_t *)this + 50005) = 0;
  if ( *((uint32_t *)this + 2) != 0 )  // 若 *((uint32_t *)this + 2) != 0
    j__free(*((void **)this + 2));  // 调 j__free
  *((uint32_t *)this + 2) = 0;  // this[2] = 0
  *((uint32_t *)this + 3) = 0;  // this[3] = 0
  *((uint32_t *)this + 4) = 0;  // this[4] = 0
}



// ------------------------------------------------------------
// 0x576F10 sub_576F10 —— Request() 总入口：5763D0 解析 URL→575FF0 Connect→576E90 按模式发送→576180 读应答→关闭 hRequest/hConnect/hInternet 三级句柄；Connect 失败日志 "GenericHTTPClient::Request::Connect()  false"
// ------------------------------------------------------------
// 调用方：ui_icon_perf.cpp 0x46EB70 StartAddress 线程，GET 模式，UA="MERONG(0.9/;p)"，URL=全局 unk_98BA60。
int /*thiscall*/ sub_576F10(int this, char *Source, int nArg3, const CHAR *uArg4)  // 实现：Request() 总入口：5763D0 解析 URL→575FF0 Connect→576E90 按模式发送→576180 读应答→关闭 …
{
  void *fld_30D54; // esi
  int v7; // [esp+Ch] [ebp-C10h] BYREF
  int v8; // [esp+10h] [ebp-C0Ch] BYREF
  int v9; // [esp+14h] [ebp-C08h]
  char Destination[1024]; // [esp+18h] [ebp-C04h] BYREF
  CHAR szObjectName[1024]; // [esp+418h] [ebp-804h] BYREF
  char pBuf[1024]; // [esp+818h] [ebp-404h] BYREF
  int dword_796E502; // [esp+C18h] [ebp-4h]

  dword_796E502 = dword_796E50;
  memset(Destination, 0, sizeof(Destination));  // 调 memset 按字节填充
  memset(pBuf, 0, sizeof(pBuf));  // 调 memset 按字节填充
  memset(szObjectName, 0, sizeof(szObjectName));  // 调 memset 按字节填充
  v9 = 1;
  v8 = 0;
  v7 = 0;
  sub_5763D0(Source, Destination, pBuf, &v8, szObjectName);  // URL 解析器：拆 scheme(缺省 http；https→端口 443 否则 80)/host/path 四段输出；端口显式存在时 atol 提取
  if ( sub_575FF0(this, pBuf, uArg4, v8, nullptr, nullptr) != 0 )  // Connect()：InternetOpenA(代理预配置)→InternetConnectA(SERVICE_HTTP=3, flags 0x440000…
  {
    if ( sub_576E90((void *)this, szObjectName, nArg3) == 0  // 请求模式分发：a3==2→5767E0(urlencoded POST)；a3==3→576C40(multipart POST)；其余→5760E0(GE…
      || !sub_576180(  // ReadResponse()：InternetReadFile 按 0x400(1024) 字节块循环读入 this+20（累计上限 0x186A0=100…
            (uint32_t *)this,
            (LPVOID)(this + 100020),
            0x186A0u,
            (char *)(this + 20),
            0x186A0u,
            (unsigned int *)&v7) )
    {
      v9 = 0;
    }
    if ( *(uint32_t *)(this + 200028) != 0 )  // 若 *(uint32_t *)(this + 200028) != 0
      InternetCloseHandle(*(HINTERNET *)(this + 200028));  // 调 InternetCloseHandle 关 WinINet 句柄
    if ( *(uint32_t *)(this + 200024) != 0 )  // 若 *(uint32_t *)(this + 200024) != 0
      InternetCloseHandle(*(HINTERNET *)(this + 200024));  // 调 InternetCloseHandle 关 WinINet 句柄
    fld_30D54 = *(void **)(this + 200020);
    if ( fld_30D54 != nullptr )  // 若 fld_30D54 有效（非空）
      InternetCloseHandle(fld_30D54);  // 调 InternetCloseHandle 关 WinINet 句柄
    return v9;
  }
  else  // 否则分支
  {
    off_77F3FC("GenericHTTPClient::Request::Connect()  false");
    return 0;
  }
}



// ============================================================
// 【分区 6】HTTP 客户端公共 API 与应答处理（0x577080-0x577330）
// 构造/析构、Base64 解码（0x5770E0）、应答缓冲复位（0x577220，两块 0xA000）、
// 应答解码（0x577250：Base64 + dword 级 XOR 密钥 this+20480）、
// 字段表项写入（0x5772E0：name/value/len 三元组，步进 1284 字节）。
// ============================================================
// ------------------------------------------------------------
// 0x577080 GenericHTTPClient__vmt0 —— GenericHTTPClient 标量删除析构（576ED0 复位 + a2&1 时 j__free）
// ------------------------------------------------------------
void */*thiscall*/ GenericHTTPClient__vmt0(void *Block, char pszArg2)  // 实现：GenericHTTPClient 标量删除析构（576ED0 复位 + a2&1 时 j__free）
{
  sub_576ED0(Block);  // GenericHTTPClient 构造/复位：vftbl 装配、清句柄 50005/50006/50007（+200020/24/28），释放并清空字段表…
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x5770B0 sub_5770B0 —— GenericHTTPClient 平凡构造：清字段表指针与 50005/50006/50007 句柄（不装配 vftbl）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5770B0(uint32_t *this)  // 实现：GenericHTTPClient 平凡构造：清字段表指针与 50005/50006/50007 句柄（不装配 vftbl）
{
  *this = &vftbl_GenericHTTPClient;  // *this 写入 &vftbl_GenericHTTPClient
  *(this + 2) = 0;  // this+8 = 0
  *(this + 3) = 0;  // this+12 = 0
  *(this + 4) = 0;  // this+16 = 0
  *(this + 50007) = 0;  // this+200028 = 0
  *(this + 50006) = 0;  // this+200024 = 0
  *(this + 50005) = 0;  // this+200020 = 0
  return this;
}



// ------------------------------------------------------------
// 0x5770E0 sub_5770E0 —— Base64 解码：A-Za-z0-9+/ 四字符组 6bit 拼装，非法字符回退重试；输出上限 *a4 保护（0x577250 的解码核）
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_5770E0(char *pszArg1, int nArg2, uint8_t *uArg3, uint32_t *uArg4)  // Base64 解码：A-Za-z0-9+/ 四字符组 6bit 拼装，非法字符回退重试；输出上限 *a4 保护（0x577250 的解码核）
{
  char *pszArg12; // ebx
  int v5; // esi
  int v6; // edi
  int i; // ecx
  unsigned int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // esi
  unsigned int v13; // [esp+4h] [ebp-8h]
  BOOL v14; // [esp+8h] [ebp-4h]
  int v15; // [esp+14h] [ebp+8h]

  pszArg12 = pszArg1;
  if ( pszArg1 == nullptr || uArg4 == nullptr )  // 若 pszArg1 == nullptr 与/或 uArg4 == nullptr
    return false;
  v13 = (unsigned int)&pszArg1[nArg2];
  v15 = 0;
  v14 = uArg3 == nullptr;
  if ( pszArg12 < &pszArg12[nArg2] )  // 若 pszArg12 < &pszArg12[nArg2]
  {
    do  // do-while 循环体起点
    {
      v5 = 0;
      v6 = 0;
      for ( i = 0; i < 4; ++i )  // 循环：i 从 0 递增到 4
      {
        if ( (unsigned int)pszArg12 >= v13 )  // 若 (unsigned int)pszArg12 >= v13
          break;  // 跳出循环/分支
        v8 = *pszArg12;
        if ( v8 < 0x41 || v8 > 0x5A )  // 若 v8 < 0x41 与/或 v8 > 0x5A
        {
          if ( v8 < 0x61 || v8 > 0x7A )  // 若 v8 < 0x61 与/或 v8 > 0x7A
          {
            if ( v8 < 0x30 || v8 > 0x39 )  // 若 v8 < 0x30 与/或 v8 > 0x39
              v9 = v8 == 43 ? 62 : v8 != 47 ? -1 : 63;
            else  // 否则分支
              v9 = v8 + 4;
          }
          else  // 否则分支
          {
            v9 = v8 - 71;
          }
        }
        else  // 否则分支
        {
          v9 = v8 - 65;
        }
        ++pszArg12;  // 自增pszArg12
        if ( v9 == -1 )  // 若 v9 == -1
        {
          --i;  // 自减i
        }
        else  // 否则分支
        {
          v5 = v9 | (v5 << 6);
          v6 += 6;
        }
      }
      if ( !v14 )  // 若 !v14
        v14 = v15 + v6 / 8 > *uArg4;
      v10 = v6 / 8;
      v11 = v5 << (24 - v6);
      if ( v6 / 8 > 0 )  // 若 v6 / 8 > 0
      {
        v15 += v10;
        do  // do-while 循环体起点
        {
          if ( !v14 )  // 若 !v14
            *uArg3++ = BYTE2(v11);  // *uArg3++ 写入 BYTE2(v11)
          v11 <<= 8;
          --v10;  // 自减v10
        }
        while ( v10 != 0 );  // 条件循环
      }
    }
    while ( (unsigned int)pszArg12 < v13 );  // 条件循环
  }
  *uArg4 = v15;  // *uArg4 写入 v15
  return !v14;
}



// ------------------------------------------------------------
// 0x577220 sub_577220 —— 应答缓冲复位：+20480 XOR 密钥清零 + 两块 0xA000(40KB) 应答区清零（全局单例 unk_98BB68 的初始化）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_577220(uint32_t *this)  // 实现：应答缓冲复位：+20480 XOR 密钥清零 + 两块 0xA000(40KB) 应答区清零（全局单例 unk_98BB68 的初始化）
{
  *(this + 20480) = 0;  // this+81920 = 0
  memset(this, 0, 0xA000u);  // 清零 this 起 0xA000 字节
  memset(this + 10240, 0, 0xA000u);  // 清零 this+10240 起 0xA000 字节
  return this;
}



// ------------------------------------------------------------
// 0x577250 sub_577250 —— 应答解码：Base64 解码入 this（容量上限 40960）后按 dword 与密钥 this+20480 逐 4 字节 XOR（每 4 字节）
// ------------------------------------------------------------
// 调用方 ui_icon_perf.cpp 0x46EB70：密钥 dword_99FB68=2857617(0x2B9551)。
uint32_t */*thiscall*/ sub_577250(uint32_t *this, int nArg2)  // 实现：应答解码：Base64 解码入 this（容量上限 40960）后按 dword 与密钥 this+20480 逐 4 字节 XOR（每 4…
{
  char *v2; // ebx
  int nLen; // edx
  int v5; // ecx
  int i; // eax

  v2 = (char *)nArg2;
  nLen = strlen((const char *)nArg2);  // nLen = 调 strlen
  memset(this, 0, 0xA000u);  // 清零 this 起 0xA000 字节
  nArg2 = 40960;
  sub_5770E0(v2, nLen, this, &nArg2);  // Base64 解码：A-Za-z0-9+/ 四字符组 6bit 拼装，非法字符回退重试；输出上限 *a4 保护（0x577250 的解码核）
  v5 = nArg2 / 4 + (nArg2 % 4 > 0);
  for ( i = 0; i < v5; ++i )  // 遍历循环
    *(this + i) ^= *(this + 20480);
  return this;
}



// ------------------------------------------------------------
// 0x5772E0 sub_5772E0 —— 字段表项写入：[0]=name 指针、[1]=value 指针、[9]=strlen(value)（1284 字节表项的前 1/3 视图）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5772E0(const char **this, const char *pArg2)  // 实现：字段表项写入：=name 指针、=value 指针、=strlen(value)（1284 字节表项的前 1/3 视图）
{
  unsigned int result; // eax

  *this = pArg2;  // *this 写入 pArg2
  result = strlen(pArg2);  // result = 调 strlen
  *(this + 1) = pArg2;  // this+4 = pArg2
  *(this + 9) = (const char *)result;  // this+36 = (const char *)result
  return result;
}



// ------------------------------------------------------------
// 0x577310 sub_577310 —— multipart 文件项 Content-Type 查询转发（32 行，576900 装配文件项时调用）
// ------------------------------------------------------------
char */*thiscall*/ sub_577310(char *this, char *pszArg2)  // 实现：multipart 文件项 Content-Type 查询转发（32 行，576900 装配文件项时调用）
{
  char *result; // eax
  int pThis_38; // edx
  char v4; // cl

  result = pszArg2;
  pThis_38 = this + 56 - pszArg2;
  do  // do-while 循环体起点
  {
    v4 = *result;
    result[pThis_38] = *result;  // result[pThis_38] 写入 *result
    ++result;  // 自增result
  }
  while ( v4 != 0 );  // 条件循环
  return result;
}



// ============================================================
// 【分区 7】应答文本 Token 解析器（0x577330-0x577990）
// Token 扫描 0x577330：跳过分隔串(this+56)、匹配 28 字节 string 表项
// （+20 键长/+24 容量，SSO 判定 +0x10）、逐字符累计到下一分隔符；
// vector<string>(28 字节/项) 拷贝/扩容/释放链 0x5775D0-0x577850。
// ============================================================
// ------------------------------------------------------------
// 0x577330 sub_577330 —— 应答 Token 扫描器：先跳过前导分隔串(this+56)，匹配 28 字节 string 表（SSO 判定容量 +0x10，键长 +20），命中则跳过等长值并返回缓冲串；否则逐字符累计至分隔符
// ------------------------------------------------------------
// 这是 HTTP 应答"key=value"文本的通用取值器；返回 this+8 处 std::string（SSO 判定 +8 视图）。
char */*thiscall*/ sub_577330(char *this)  // 实现：应答 Token 扫描器：先跳过前导分隔串(this+56)，匹配 28 字节 string 表（SSO 判定容量 +0x10，键长 +20…
{
  unsigned int nLen; // ebx
  unsigned int v3; // edi
  int i; // ebx
  int pThis_B; // eax
  int pThis_B2; // ecx
  unsigned int v7; // edx
  int v8; // eax
  size_t v9; // ecx
  const char *v10; // eax
  char *pThis_8; // esi
  int64_t pThis_1; // rax
  unsigned int pThis_82; // edi
  char *pThis_C; // ecx
  char *pThis_C2; // edx
  char *pThis_7; // eax
  char *pThis_C3; // ebx
  int v19; // edx
  int64_t pThis_12; // rax
  unsigned int v21; // edi
  int j; // ebx
  int pThis_B3; // eax
  int pThis_B4; // edx
  int v25; // eax
  const char *v26; // eax
  int pThis_B5; // eax
  char *pThis_13; // eax
  int64_t pThis_14; // rax
  char v30; // [esp+Ch] [ebp-8h]

  if ( (signed int)abs32(*((uint32_t *)this + 1) - *(uint32_t *)this) < *((uint32_t *)this + 9) )  // 若 (signed int)abs32(*((uint32_t *)this + 1) - *(uint32_t *)this)..
  {
    do  // do-while 循环体起点
    {
      if ( strncmp(*((const char **)this + 1), this + 56, strlen(this + 56)) != 0 )  // 若 strncmp(*((const char **)this + 1), this + 56, strlen(this + 5..
        break;  // 跳出循环/分支
      nLen = strlen(this + 56) + *((uint32_t *)this + 1);  // nLen = 调 strlen
      *((uint32_t *)this + 1) = nLen;  // this[1] = nLen
    }
    while ( (signed int)abs32(nLen - *(uint32_t *)this) < *((uint32_t *)this + 9) );  // 条件循环
  }
  v3 = 0;
  for ( i = 0; ; i += 28 )  // 遍历循环
  {
    pThis_B = *((uint32_t *)this + 11);
    if ( pThis_B == 0 || v3 >= (*((uint32_t *)this + 12) - pThis_B) / 28 )  // 若 pThis_B == 0
      break;  // 跳出循环/分支
    pThis_B2 = *((uint32_t *)this + 11);
    v7 = *(uint32_t *)(pThis_B2 + i + 24);
    v8 = pThis_B2 + i;
    v9 = *(uint32_t *)(pThis_B2 + i + 20);
    if ( v7 < 0x10 )  // 若 v7 < 0x10
      v10 = (const char *)(v8 + 4);
    else  // 否则分支
      v10 = *(const char **)(v8 + 4);
    if ( strncmp(*((const char **)this + 1), v10, v9) == 0 )  // 若 strncmp(*((const char **)this + 1), v10, v9) == 0
    {
      *((uint32_t *)this + 1) += *(uint32_t *)(28 * v3 + *((uint32_t *)this + 11) + 20);
      pThis_8 = this + 8;
      sub_4015C0("NULL", 4u);  // 【std::string构造赋值】
      if ( *((uint32_t *)pThis_8 + 6) < 0x10u )  // 若 *((uint32_t *)pThis_8 + 6) < 0x10u
        return pThis_8 + 4;  // 返回 pThis_8 + 4
      else  // 否则分支
        return *((char **)pThis_8 + 1);
    }
    ++v3;  // 自增v3
  }
  pThis_1 = *((uint32_t *)this + 1) - *(uint32_t *)this;
  if ( (signed int)((HIDWORD(pThis_1) ^ pThis_1) - HIDWORD(pThis_1)) >= *((uint32_t *)this + 9) )  // 若 (signed int)((HIDWORD(pThis_1) ^ pThis_1) - HIDWORD(pThis_1)) ..
    return nullptr;  // 返回 空指针
  pThis_82 = *((uint32_t *)this + 8);
  pThis_C = this + 12;
  if ( pThis_82 < 0x10 )  // 若 pThis_82 < 0x10
    pThis_C2 = this + 12;
  else  // 否则分支
    pThis_C2 = *(char **)pThis_C;
  pThis_7 = &pThis_C2[*((uint32_t *)this + 7)];
  if ( pThis_82 < 0x10 )  // 若 pThis_82 < 0x10
    pThis_C3 = this + 12;
  else  // 否则分支
    pThis_C3 = *(char **)pThis_C;
  if ( pThis_82 >= 0x10 )  // 若 pThis_82 >= 0x10
    pThis_C = *(char **)pThis_C;
  if ( pThis_C3 != nullptr )  // 若 pThis_C3 有效（非空）
    v19 = pThis_C3 - pThis_C;
  else  // 否则分支
    v19 = 0;
  if ( pThis_7 != nullptr )  // 若 pThis_7 有效（非空）
    pThis_7 -= (int)pThis_C3;
  sub_401230(v19, pThis_7);  // std::string::erase(pos, n) 模板实例（越界走 _Xran；memcpy_0 左移尾部）
  pThis_12 = *((uint32_t *)this + 1) - *(uint32_t *)this;
  if ( (signed int)((HIDWORD(pThis_12) ^ pThis_12) - HIDWORD(pThis_12)) < *((uint32_t *)this + 9) )  // 若 (signed int)((HIDWORD(pThis_12) ^ pThis_12) - HIDWORD(pThis_12..
  {
    while ( strncmp(*((const char **)this + 1), this + 56, strlen(this + 56)) != 0 )  // 条件循环
    {
      v21 = 0;
      for ( j = 0; ; j += 28 )  // 遍历循环
      {
        pThis_B3 = *((uint32_t *)this + 11);
        if ( pThis_B3 == 0 || v21 >= (*((uint32_t *)this + 12) - pThis_B3) / 28 )  // 若 pThis_B3 == 0
          break;  // 跳出循环/分支
        pThis_B4 = *((uint32_t *)this + 11);
        v25 = pThis_B4 + j;
        if ( *(uint32_t *)(pThis_B4 + j + 24) < 0x10u )  // 若 *(uint32_t *)(pThis_B4 + j + 24) < 0x10u
          v26 = (const char *)(v25 + 4);
        else  // 否则分支
          v26 = *(const char **)(v25 + 4);
        if ( strncmp(*((const char **)this + 1), v26, *(uint32_t *)(pThis_B4 + j + 20)) == 0 )  // 若 strncmp(*((const char **)this + 1), v26, *(uint32_t *)(pThis_B..
        {
          *((uint32_t *)this + 1) += *(uint32_t *)(*((uint32_t *)this + 11) + 28 * v21 + 20);
          break;  // 跳出循环/分支
        }
        ++v21;  // 自增v21
      }
      pThis_B5 = *((uint32_t *)this + 11);
      if ( pThis_B5 == 0 || v21 >= (*((uint32_t *)this + 12) - pThis_B5) / 28 )  // 若 pThis_B5 == 0
      {
        pThis_13 = *((char **)this + 1);
        v30 = *pThis_13;
        *((uint32_t *)this + 1) = pThis_13 + 1;  // this[1] = pThis_13 + 1
        sub_4164C0((std::_String_base *)(this + 8), 1, v30);  // 【string/vector 容器工具】
        pThis_14 = *((uint32_t *)this + 1) - *(uint32_t *)this;
        if ( (signed int)((HIDWORD(pThis_14) ^ pThis_14) - HIDWORD(pThis_14)) < *((uint32_t *)this + 9) )  // 若 (signed int)((HIDWORD(pThis_14) ^ pThis_14) - HIDWORD(pThis_14..
          continue;  // 进入下一轮循环
      }
      goto LABEL_46;  // 跳转 LABEL_46
    }
    *((uint32_t *)this + 1) += strlen(this + 56);
  }
LABEL_46:  // 标签 LABEL_46（跳转合流点）
  if ( *((uint32_t *)this + 8) < 0x10u )  // 若 *((uint32_t *)this + 8) < 0x10u
    return this + 12;  // 返回 this + 12
  else  // 否则分支
    return *((char **)this + 3);
}


// ------------------------------------------------------------
// 0x5775D0 sub_5775D0 —— std::vector<string>(28 字节/项) 区间拷贝（4014D0 逐项赋值）
// ------------------------------------------------------------
int /*cdecl*/ sub_5775D0(int nArg1, int nArg2, int nArg3)  // 实现：std::vector<string>(28 字节/项) 区间拷贝（4014D0 逐项赋值）
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )  // 条件循环
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )  // 若 nArg32 非 0
    {
      *(uint32_t *)(nArg32 + 24) = 15;  // nArg32+24 = 15
      *(uint32_t *)(nArg32 + 20) = 0;  // nArg32+20 = 0
      *(uint8_t *)(nArg32 + 4) = 0;  // nArg32+4 = 0
      sub_4014D0((std::_String_base *)nArg32, nArg1, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    }
    nArg32 += 28;
    LOBYTE(v7) = 0;
    nArg1 += 28;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x577670 sub_577670 —— vector<string> 扩容：Block>0x9249249 抛 length_error(416610)；operator new(28n) 迁移
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_577670(uint32_t *this, unsigned int Block)  // 实现：vector<string> 扩容：Block>0x9249249 抛 length_error(416610)；operator new(…
{
  unsigned int result; // eax
  int v4; // ebx
  int fld_e12; // eax
  int fld_e22; // edi
  int fld_e13; // eax
  int fld_e1; // [esp-18h] [ebp-34h]
  int fld_e2; // [esp-14h] [ebp-30h]
  uint32_t v10[7]; // [esp+0h] [ebp-1Ch] BYREF
  char *Blocka; // [esp+24h] [ebp+8h]

  v10[3] = v10;
  if ( Block > 0x9249249 )  // 若 Block > 0x9249249
    sub_416610();  // 调 sub_416610
  result = *(this + 1);  // result = this+1
  if ( result != 0 )  // 若结果非 0（成功）
    result = (int)(*(this + 3) - result) / 28;
  if ( result < Block )  // 若 result < Block
  {
    v4 = 28 * Block;
    Blocka = (char *)operator new(28 * Block);
    fld_e2 = *(this + 2);  // fld_e2 = this+2
    fld_e1 = *(this + 1);  // fld_e1 = this+1
    v10[6] = 0;
    sub_5775D0(fld_e1, fld_e2, (int)Blocka);  // std::vector<string>(28 字节/项) 区间拷贝（4014D0 逐项赋值）
    fld_e12 = *(this + 1);  // fld_e12 = this+1
    if ( fld_e12 != 0 )  // 若 fld_e12 非 0
      fld_e22 = (*(this + 2) - fld_e12) / 28;
    else  // 否则分支
      fld_e22 = 0;
    fld_e13 = *(this + 1);  // fld_e13 = this+1
    if ( fld_e13 != 0 )  // 若 fld_e13 非 0
    {
      sub_4166A0(fld_e13, *(this + 2));  // 析构区间内 28B string 元素
      j__free((void *)*(this + 1));  // 调 j__free
    }
    *(this + 3) = &Blocka[v4];  // this+12 = &Blocka[v4]
    *(this + 2) = &Blocka[28 * fld_e22];  // this+8 = &Blocka[28 * fld_e22]
    *(this + 1) = Blocka;  // this+4 = Blocka
    return (unsigned int)Blocka;
  }
  return result;
}



// ------------------------------------------------------------
// 0x577780 sub_577780 —— vector 扩容转发（调 577670）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_577780(uint32_t *this)  // 实现：vector 扩容转发（调 577670）
{
  uint32_t *pThis_A; // ecx

  *(this + 8) = 15;  // this+32 = 15
  *(this + 7) = 0;  // this+28 = 0
  *((uint8_t *)this + 12) = 0;  // this[12] = 0
  pThis_A = this + 10;
  pThis_A[1] = 0;
  pThis_A[2] = 0;
  pThis_A[3] = 0;
  *this = 0;  // *this 写入 0
  *(this + 1) = 0;  // this+4 = 0
  *(this + 9) = 0;  // this+36 = 0
  *((uint8_t *)this + 56) = 0;  // this[56] = 0
  sub_577670(pThis_A, 0xAu);  // vector<string> 扩容：Block>0x9249249 抛 length_error(416610)；operator new(28n) 迁移
  return this;
}



// ------------------------------------------------------------
// 0x5777F0 sub_5777F0 —— vector 尾部释放（4166A0）
// ------------------------------------------------------------
void /*thiscall*/ sub_5777F0(int this)  // 实现：vector 尾部释放（4166A0）
{
  int fld_2C; // eax
  int pThis_28; // esi

  fld_2C = *(uint32_t *)(this + 44);  // fld_2C = 读 this+44
  pThis_28 = this + 40;
  if ( fld_2C != 0 )  // 若 fld_2C 非 0
  {
    sub_4166A0(fld_2C, *(uint32_t *)(this + 48));  // 析构区间内 28B string 元素
    j__free(*(void **)(pThis_28 + 4));  // 调 j__free
  }
  *(uint32_t *)(pThis_28 + 4) = 0;  // pThis_28+4 = 0
  *(uint32_t *)(pThis_28 + 8) = 0;  // pThis_28+8 = 0
  *(uint32_t *)(pThis_28 + 12) = 0;  // pThis_28+12 = 0
  if ( *(uint32_t *)(this + 32) >= 0x10u )  // 若 *(uint32_t *)(this + 32) >= 0x10u
    j__free(*(void **)(this + 12));  // 调 j__free
  *(uint32_t *)(this + 28) = 0;  // this+28 = 0
  *(uint32_t *)(this + 32) = 15;  // this+32 = 15
  *(uint8_t *)(this + 12) = 0;  // this+12 = 0
}



// ------------------------------------------------------------
// 0x577850 sub_577850 —— vector 头插/重配（4015C0 + 416C40）
// ------------------------------------------------------------
void /*thiscall*/ sub_577850(uint32_t *this, char *Src)  // 实现：vector 头插/重配（4015C0 + 416C40）
{
  unsigned int v2; // edi
  uint32_t *pThis_A; // ebx
  int v4; // eax
  int fld_e11; // eax
  unsigned int v6; // ecx
  int v7; // eax
  const char *psz; // eax
  uint8_t v9[4]; // [esp+Ch] [ebp-30h] BYREF
  void *Block; // [esp+10h] [ebp-2Ch]
  int v11; // [esp+20h] [ebp-1Ch]
  unsigned int v12; // [esp+24h] [ebp-18h]
  uint32_t *pThis; // [esp+28h] [ebp-14h]
  int i; // [esp+2Ch] [ebp-10h]
  int v15; // [esp+38h] [ebp-4h]

  v2 = 0;
  pThis = this;
  pThis_A = this + 10;
  for ( i = 0; ; i += 28 )  // 遍历循环
  {
    v4 = pThis_A[1];  // v4 = 取 pThis_A[1]
    if ( v4 == 0 || v2 >= (pThis_A[2] - v4) / 28 )  // 若 v4 == 0
      break;  // 跳出循环/分支
    fld_e11 = *(this + 11);  // fld_e11 = this+11
    v6 = *(uint32_t *)(fld_e11 + i + 24);
    v7 = i + fld_e11;
    if ( v6 < 0x10 )  // 若 v6 < 0x10
      psz = (const char *)(v7 + 4);
    else  // 否则分支
      psz = *(const char **)(v7 + 4);
    if ( strcmp(psz, Src) == 0 )  // 若 strcmp(psz, Src) == 0
      return;
    this = pThis;
    ++v2;  // 自增v2
  }
  v12 = 15;
  v11 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(Src, strlen(Src));  // 【std::string构造赋值】
  v15 = 0;
  sub_416C40(v9);  // 尾插一条 28B 记录（满则走插入路径）
  if ( v12 >= 0x10 )  // 若 v12 >= 0x10
    j__free(Block);  // 调 j__free
}



// ------------------------------------------------------------
// 0x577960 sub_577960 —— 15 行小辅助（栈帧守卫）
// ------------------------------------------------------------
int /*thiscall*/ sub_577960(int this)  // 实现：15 行小辅助（栈帧守卫）
{
  *(uint8_t *)(this + 972) = 0;  // this+972 = 0
  *(uint8_t *)(this + 973) = 0;  // this+973 = 0
  *(uint32_t *)(this + 992) = 0;  // this+992 = 0
  *(uint32_t *)(this + 996) = 0;  // this+996 = 0
  *(uint32_t *)(this + 1000) = 0;  // this+1000 = 0
  return 0;
}



// ============================================================
// 【分区 8】CNPathGate 传送门与杂项（0x577990-0x578000）
// ============================================================
// ------------------------------------------------------------
// 0x577990 CNPathGate__vmt14C —— CNPathGate__vmt14C 传送门路径槽（49 行）
// ------------------------------------------------------------
char /*thiscall*/ CNPathGate__vmt14C(uint8_t *this)  // 实现：CNPathGate__vmt14C 传送门路径槽（49 行）
{
  uint32_t *pThis_1D; // eax
  int pThis_F6; // ebx
  int i; // edi

  CNRDPassiveObject__vmt14C((int)this);
  LOBYTE(pThis_1D) = *(this + 973);
  if ( (uint8_t)pThis_1D == 0 )  // 若 (uint8_t)pThis_1D == 0
  {
    pThis_1D = *((uint32_t **)this + 29);
    if ( *((uint8_t *)pThis_1D + 152) == 0 )  // 若 *((uint8_t *)pThis_1D + 152) == 0
    {
      LOBYTE(pThis_1D) = *(this + 972);
      if ( (uint8_t)pThis_1D == 0 )  // 若 (uint8_t)pThis_1D == 0
      {
        pThis_1D = *((uint32_t **)this + 245);
        pThis_F6 = pThis_1D != nullptr ? (*((uint32_t *)this + 246) - (int)pThis_1D) >> 3 : 0;
        for ( i = 0; i < pThis_F6; ++i )  // 遍历循环
        {
          pThis_1D = (uint32_t *)(*((uint32_t *)this + 245) + 8 * i);
          if ( pThis_1D[1] == 1 )  // 若 pThis_1D[1] == 1
          {
            LOBYTE(pThis_1D) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_1D);  // 调虚槽 +208：定时器移除
          }
          else if ( pThis_1D[1] == 2 )  // 否则若 pThis_1D[1] == 2
          {
            LOBYTE(pThis_1D) = (*(int (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 调虚槽 +204：定时器插入
                           this,
                           i,
                           *pThis_1D,
                           0,
                           0,
                           0,
                           0);
          }
        }
      }
      *(this + 973) = 1;  // this+3892 = 1
    }
  }
  return (char)pThis_1D;
}



// ------------------------------------------------------------
// 0x577A30 sub_577A30 —— 传送/路径辅助（48C070/424FF0/48CC70/48CCF0，109 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_577A30(uint32_t *this, uint32_t *pArg2, int nArg3)  // 实现：传送/路径辅助（48C070/424FF0/48CC70/48CCF0，109 行）
{
  int v4; // esi
  uint32_t *pThis; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // esi
  int v12; // esi
  int v13; // eax
  bool v14; // cc
  int v15; // edx
  int v16; // ecx
  int v17; // eax
  uint32_t *v18; // ebx
  int v19; // [esp-4h] [ebp-30h]
  uint32_t *v20; // [esp+Ch] [ebp-20h]
  int v21; // [esp+10h] [ebp-1Ch]
  int v23; // [esp+18h] [ebp-14h] BYREF
  int v24; // [esp+1Ch] [ebp-10h] BYREF
  uint32_t *i; // [esp+20h] [ebp-Ch]
  int v26; // [esp+24h] [ebp-8h]
  int v27; // [esp+28h] [ebp-4h]
  int v28; // [esp+34h] [ebp+8h]

  v4 = 0;
  pThis = this;
  if ( pArg2 != nullptr && *(this + 248) != 0 )  // 若 pArg2 != nullptr
  {
    v6 = *this;
    v24 = 0;
    v23 = 0;
    v19 = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 124))(this);  // 调用虚函数槽 +124
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 120))(pThis);  // 调虚槽 +120：动画对象
    sub_48C070(&v24, &v23, v7, v19);  // 像素坐标 → 格子行列换算
    v26 = 0;
    do  // do-while 循环体起点
    {
      v8 = v24 + v4 - pThis[249];
      v27 = v8;
      if ( v8 >= 0 )  // 若 v8 >= 0
      {
        v9 = pArg2[91];  // v9 = 取 pArg2[91]
        v10 = v9 != 0 ? (pArg2[92] - v9) >> 5 : 0;
        if ( v8 < 14 * v10 )  // 若 v8 < 14 * v10
        {
          v11 = 0;
          v21 = 0;
          v28 = 0;
          do  // do-while 循环体起点
          {
            v12 = v23 + v11 - pThis[250];
            if ( v12 >= 0 && v12 < (int)(10 * (sub_424FF0(pArg2) + 3)) )  // 列数换算
            {
              i = (uint32_t *)(4 * v26 + *(uint32_t *)(v28 + *(uint32_t *)(pThis[248] + 40) + 4));
              v13 = sub_48CC70(v27, v12);  // 取地牢格值（14 列折行、层分块）
              if ( *i > v13 )  // 若 *i > v13
                sub_48CCF0(v27, v12, *(uint32_t *)(4 * v26 + *(uint32_t *)(v28 + *(uint32_t *)(pThis[248] + 40) + 4)));  // 写地牢格值（同 ·sub_48CC70 索引）
              if ( v26 != 0 )  // 若 v26 非 0
              {
                if ( v26 == 13 && nArg3 == 1 )  // 若 v26 == 13 与/或 nArg3 == 1
                {
                  v15 = v27 + 1;
                  for ( i = (uint32_t *)(v27 + 1); ; v15 = (int)i )  // 遍历循环
                  {
                    v16 = pArg2[91];  // v16 = 取 pArg2[91]
                    v17 = v16 != 0 ? (pArg2[92] - v16) >> 5 : 0;
                    if ( v15 >= 14 * v17 )  // 若 v15 >= 14 * v17
                      break;  // 跳出循环/分支
                    v18 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(pThis[248] + 40) + v28 + 4) + 52);
                    if ( *v18 > sub_48CC70(v15, v12) )  // 取地牢格值（14 列折行、层分块）
                      sub_48CCF0(i, v12, *(uint32_t *)(*(uint32_t *)(v28 + *(uint32_t *)(*(this + 248) + 40) + 4) + 52));  // 写地牢格值（同 ·sub_48CC70 索引）
                    pThis = this;
                    i = (uint32_t *)((char *)i + 1);
                  }
                }
              }
              else if ( nArg3 == 0 )  // 否则若 nArg3 == 0
              {
                for ( i = nullptr; (int)i < v27; i = (uint32_t *)((char *)i + 1) )  // 遍历循环
                {
                  v20 = *(uint32_t **)(*(uint32_t *)(pThis[248] + 40) + v28 + 4);
                  if ( *v20 > sub_48CC70(i, v12) )  // 取地牢格值（14 列折行、层分块）
                    sub_48CCF0(i, v12, **(uint32_t **)(v28 + *(uint32_t *)(pThis[248] + 40) + 4));  // 写地牢格值（同 ·sub_48CC70 索引）
                }
              }
            }
            v11 = v21 + 1;
            v14 = v28 + 16 < 480;
            ++v21;  // 自增v21
            v28 += 16;
          }
          while ( v14 );  // 条件循环
          v4 = v26;
        }
      }
      v26 = ++v4;
    }
    while ( v4 < 14 );  // 条件循环
  }
}



// ------------------------------------------------------------
// 0x577C80 sub_577C80 —— 路径对象更新（144 行：4D0B30/507690/42FCB0/431920/4319E0/48D630）
// ------------------------------------------------------------
char /*thiscall*/ sub_577C80(char *this, int nArg2)  // 实现：路径对象更新（144 行：4D0B30/507690/42FCB0/431920/4319E0/48D630）
{
  int v3; // ebx
  unsigned int pThis_B3; // eax
  int pThis_B2; // ecx
  int pThis_57; // ecx
  const char *pThis_B22; // edi
  int pThis_572; // eax
  int v9; // edx
  int v10; // ebx
  void *pMem; // eax
  int v12; // eax
  bool pThis_60; // cf
  const char *pThis_16C; // eax
  void *v15; // eax
  int pThis_6C; // eax
  int v17; // ebx
  int pThis_6C2; // edi
  bool v19; // cc
  uint32_t v21[2]; // [esp+8h] [ebp-128h] BYREF
  void *Block; // [esp+10h] [ebp-120h]
  int v23; // [esp+14h] [ebp-11Ch]
  unsigned int v24; // [esp+18h] [ebp-118h]
  int pThis_B32; // [esp+1Ch] [ebp-114h]
  char Buffer[256]; // [esp+20h] [ebp-110h] BYREF
  int dword_796E502; // [esp+120h] [ebp-10h]
  int v28; // [esp+12Ch] [ebp-4h]
  int v29; // [esp+138h] [ebp+8h]

  v3 = 0;
  dword_796E502 = dword_796E50;
  LOBYTE(pThis_B3) = nArg2 != 0;
  *(this + 972) = nArg2 != 0;  // this+3888 = nArg2 != 0
  pThis_B2 = *((uint32_t *)this + 178);  // this+712〔pResTbl712〕
  if ( pThis_B2 != 0 )  // 若 pThis_B2 非 0
  {
    pThis_B3 = (*((uint32_t *)this + 179) - pThis_B2) >> 2;
    pThis_B32 = pThis_B3;
  }
  else  // 否则分支
  {
    pThis_B32 = 0;
  }
  v29 = 0;
  if ( pThis_B32 > 0 )  // 若 pThis_B32 > 0
  {
    v24 = 1;
    while ( 1 )  // 条件循环
    {
      pThis_57 = *((uint32_t *)this + 87);  // this+348〔pParamTbl348〕
      if ( pThis_57 == 0 )  // 若 pThis_57 为 0
        return pThis_B3;
      pThis_B3 = (*((uint32_t *)this + 88) - pThis_57) >> 2;  // this+352〔uHitCtx352〕
      if ( pThis_B3 <= v24 )  // 若 pThis_B3 <= v24
        return pThis_B3;
      pThis_B22 = (const char *)sub_41ACF0(*((uint32_t *)this + 178) + 4 * v3);  // 驻留串句柄 → 字符串指针
      pThis_572 = *((uint32_t *)this + 87);  // this+348〔pParamTbl348〕
      v9 = *(uint32_t *)(8 * v3 + pThis_572);
      v10 = *(uint32_t *)(8 * v3 + pThis_572 + 4);
      v23 = v9;
      if ( strstr(pThis_B22, ".til") != nullptr )  // 空指针判定
      {
        if ( *((uint32_t *)this + 248) == 0 )  // 若 *((uint32_t *)this + 248) == 0
        {
          pMem = operator new(0x34u);  // new(52 字节) 分配对象
          Block = pMem;
          v28 = 0;
          if ( pMem != nullptr )  // 若 pMem 有效（非空）
            v12 = sub_4D0B30(pMem);  // v12 = 调 sub_4D0B30 返回值
          else  // 否则分支
            v12 = 0;
          *((uint32_t *)this + 248) = v12;
          pThis_60 = *((uint32_t *)this + 96) < 0x10u;
          v28 = -1;
          if ( pThis_60 )  // 若 pThis_60
            pThis_16C = this + 364;
          else  // 否则分支
            pThis_16C = *((const char **)this + 91);
          sprintf(Buffer, "%s%s", pThis_16C, pThis_B22);  // 拼字符串（模板 %s%s）
          sub_507690(*((uint32_t *)this + 248), (char)Buffer);  // 瓦片(tile)定义解析器
          *((uint32_t *)this + 249) = v23;
          *((uint32_t *)this + 250) = v10;
        }
        goto LABEL_33;  // 跳转 LABEL_33
      }
      v15 = (void *)sub_42FCB0(228);  // CRT 一次性初始化
      Block = v15;
      if ( v10 == -1 )  // 若 v10 == -1
      {
        v28 = 1;
        if ( v15 != nullptr )  // 若 v15 有效（非空）
        {
          if ( *((uint32_t *)this + 96) < 0x10u )  // 若 *((uint32_t *)this + 96) < 0x10u
            pThis_6C = sub_431920((uint8_t)this + 108, (char)pThis_B22, 1);  // 动画件构造（文件名版）
          else  // 否则分支
            pThis_6C = sub_431920(*((uint32_t *)this + 91), (char)pThis_B22, 1);  // 动画件构造（文件名版）
          goto LABEL_28;  // 跳转 LABEL_28
        }
      }
      else  // 否则分支
      {
        v28 = 2;
        if ( v15 != nullptr )  // 若 v15 有效（非空）
        {
          if ( *((uint32_t *)this + 96) < 0x10u )  // 若 *((uint32_t *)this + 96) < 0x10u
            pThis_6C = sub_4319E0((int)v15, 0, v10, this + 364, pThis_B22, 1);  // 动画件构造（文件名与参数版）
          else  // 否则分支
            pThis_6C = sub_4319E0((int)v15, 0, v10, *((const char **)this + 91), pThis_B22, 1);  // 动画件构造（文件名与参数版）
          goto LABEL_28;  // 跳转 LABEL_28
        }
      }
      pThis_6C = 0;
LABEL_28:  // 标签 LABEL_28（跳转合流点）
      v17 = v23;
      v28 = -1;
      pThis_6C2 = pThis_6C;
      if ( v23 == 0 || v23 == 1 && *(this + 972) == 0 )  // 若 v23 == 0 与/或 v23 == 1
        (*(void (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 调虚槽 +204：定时器插入
          this,
          v29,
          pThis_6C,
          0,
          0,
          0,
          0);
      v21[0] = pThis_6C2;
      v21[1] = v17;
      sub_48D630(v21);  // 8 字节元素尾插（原位构造或回落插入器）
LABEL_33:  // 标签 LABEL_33（跳转合流点）
      LOBYTE(pThis_B3) = v29 + 1;
      v19 = ++v29 < pThis_B32;
      v24 += 2;
      if ( !v19 )  // 若 !v19
        return pThis_B3;
      v3 = v29;
    }
  }
  return pThis_B3;
}


// ------------------------------------------------------------
// 0x577F30 sub_577F30 —— 路径/掉落前置（42AF90/657740/4D10A0）
// ------------------------------------------------------------
void /*thiscall*/ sub_577F30(uint32_t *this)  // 实现：路径/掉落前置（42AF90/657740/4D10A0）
{
  int fld_e245; // ecx
  int i; // esi
  void **fld_e2452; // ecx
  void *fld_e248; // esi
  int fld_e2453; // [esp+Ch] [ebp-8h]
  int fld_e246; // [esp+10h] [ebp-4h]

  fld_e245 = *(this + 245);  // fld_e245 = this+245
  if ( fld_e245 != 0 )  // 若 fld_e245 非 0
    fld_e246 = (*(this + 246) - fld_e245) >> 3;
  else  // 否则分支
    fld_e246 = 0;
  for ( i = 0; i < fld_e246; ++i )  // 遍历循环
  {
    fld_e2452 = *(void ***)(*(this + 245) + 8 * i);
    if ( fld_e2452 != nullptr )  // 若 fld_e2452 有效（非空）
    {
      fld_e2453 = *(uint32_t *)(*(this + 245) + 8 * i);  // fld_e2453 = 读 this+245
      sub_42AF90(fld_e2452);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(fld_e2453, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *(uint32_t *)(8 * i + *(this + 245)) = 0;
  }
  fld_e248 = (void *)*(this + 248);
  if ( fld_e248 != nullptr )  // 若 fld_e248 有效（非空）
  {
    sub_4D10A0(*(this + 248));  // 调 sub_4D10A0
    j__free(fld_e248);  // 调 j__free
  }
  *(this + 248) = 0;  // this+992 = 0
}



// ------------------------------------------------------------
// 0x577FF0 sub_577FF0 —— 10 行小函数
// ------------------------------------------------------------
void /*thiscall*/ sub_577FF0(uint32_t *this)  // 实现：10 行小函数
{
  *(this + 1) = 1;  // this+4 = 1
}



// ============================================================
// 【分区 9】CNRDStackable 可堆叠物品对象（0x578000-0x5785E0）
// 覆写槽: vmt8C=更新、vmt88/vmt78/vmt74/vmt70=外观与数量表现；
// 数量/外观计算 0x578240（4F3360/4B2BF0）。
// ============================================================
// ------------------------------------------------------------
// 0x578000 CNRDStackable__vmt8C —— CNRDStackable__vmt8C 更新槽（41C210）
// ------------------------------------------------------------
int /*thiscall*/ CNRDStackable__vmt8C(uint32_t *this)  // 实现：CNRDStackable__vmt8C 更新槽（41C210）
{
  int result; // eax

  switch ( *(this + 37) )  // 按 *(this + 37) 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( (uint8_t)sub_41C210(dword_8F7A24) == 0  // 状态判定（三路或）(推断)
        || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1196))(dword_8F7C04) != 0  // 调虚槽 +1196：IRDCharacter__vmt4AC 默认虚槽桩（10 行 return）
        || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 724))(dword_8F7C04) != 0 )  // 调虚槽 +724：读 +6552 霸体字节
      {
        goto LABEL_10;  // 跳转 LABEL_10
      }
      result = 1;
      break;  // 跳出循环/分支
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      switch ( *(this + 3) )  // this+12〔nItemType〕
      {
        case 0xFC9:  // case 4041
        case 0xFCA:  // case 4042
        case 0xFCB:  // case 4043
        case 0xFCC:  // case 4044
        case 0xFCD:  // case 4045
        case 0xFCE:  // case 4046
        case 0xFCF:  // case 4047
        case 0xFD0:  // case 4048
        case 0xFD1:  // case 4049
        case 0xFD2:  // case 4050
        case 0xFD3:  // case 4051
        case 0xFD4:  // case 4052
        case 0xFEF:  // case 4079
        case 0xFF0:  // case 4080
        case 0xFF1:  // case 4081
        case 0xFF2:  // case 4082
        case 0xFF7:  // case 4087
        case 0xFF8:  // case 4088
        case 0xFF9:  // case 4089
        case 0xFFA:  // case 4090
        case 0xFFB:  // case 4091
        case 0xFFC:  // case 4092
        case 0xFFD:  // case 4093
        case 0xFFE:  // case 4094
        case 0xFFF:  // case 4095
        case 0x1000:  // case 4096
        case 0x1001:  // case 4097
        case 0x1002:  // case 4098
        case 0x1003:  // case 4099
        case 0x1004:  // case 4100
        case 0x1005:  // case 4101
        case 0x1006:  // case 4102
          goto LABEL_7;  // 跳转 LABEL_7
        default:  // 默认分支
          goto LABEL_10;  // 跳转 LABEL_10
      }
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      goto LABEL_7;  // 跳转 LABEL_7
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      if ( (uint8_t)sub_41C210(dword_8F7A24) == 0  // 状态判定（三路或）(推断)
        || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1272))(dword_8F7C04) == 0 )  // 调虚槽 +1272
      {
        goto LABEL_10;  // 跳转 LABEL_10
      }
LABEL_7:  // 标签 LABEL_7（跳转合流点）
      result = 2;
      break;  // 跳出循环/分支
    default:  // 默认分支
LABEL_10:  // 标签 LABEL_10（跳转合流点）
      result = 0;
      break;  // 跳出循环/分支
  }
  return result;
}



// ------------------------------------------------------------
// 0x578100 CNRDStackable__vmt88 —— CNRDStackable__vmt88 槽位（41ACF0 粒子挂载）
// ------------------------------------------------------------
int /*thiscall*/ CNRDStackable__vmt88(uint32_t *this, int *pDwArg2, int nArg3, int nArg4)  // 实现：CNRDStackable__vmt88 槽位（41ACF0 粒子挂载）
{
  int v5; // ebx
  int v6; // eax
  int v7; // esi
  int v8; // eax

  if ( *(this + 37) == 0
    && ((int *)dword_8F7C04 == pDwArg2  // 本地玩家对象
     || *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 132))(this) + 12) == 1  // 调虚槽 +132：CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽…
     && (v5 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 376))(pDwArg2)) == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04  // 调虚槽 +376：坐标同步包（type 37）
                                                                                            + 376))(dword_8F7C04)) )  // 本地玩家对象
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 100))(this);  // 调虚槽 +100：CNRDPrivateStoreWindow_Display__vmt64 槽（16 行）
  }
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 16))(this);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
  v7 = *pDwArg2;
  v8 = sub_41ACF0(v6 + 80);  // 驻留串句柄 → 字符串指针
  return (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v7 + 212))(pDwArg2, v8, -1, 0, 0);  // 调用虚函数槽 +212
}



// ------------------------------------------------------------
// 0x578180 CNRDStackable__vmt78 —— CNRDStackable__vmt78 槽位（4B1BA0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDStackable__vmt78(uint32_t *this)  // 实现：CNRDStackable__vmt78 槽位（4B1BA0）
{
  int dword_9B8DBC2; // ecx
  uint32_t *pThis; // [esp+0h] [ebp-4h] BYREF

  pThis = this;
  if ( *(this + 38) == -1 )  // 若 *(this + 38) == -1
  {
    sub_4B1BA0(&pThis, this + 3);  // map lower_bound（键在 +12）
    dword_9B8DBC2 = dword_9B8DBC;
  }
  else  // 否则分支
  {
    sub_4B1BA0(&pThis, this + 38);  // map lower_bound（键在 +12）
    dword_9B8DBC2 = dword_9B8DC8;
  }
  if ( pThis == (uint32_t *)dword_9B8DBC2 )  // 若 pThis == (uint32_t *)dword_9B8DBC2
    return 0;
  else  // 否则分支
    return pThis[4];  // 返回 取 pThis[4]
}



// ------------------------------------------------------------
// 0x5781E0 CNRDStackable__vmt74 —— CNRDStackable__vmt74 槽位（4B1BA0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDStackable__vmt74(uint32_t *this)  // 实现：CNRDStackable__vmt74 槽位（4B1BA0）
{
  int dword_9B8DBC2; // ecx
  uint32_t *pThis; // [esp+0h] [ebp-4h] BYREF

  pThis = this;
  if ( *(this + 38) == -1 )  // 若 *(this + 38) == -1
  {
    sub_4B1BA0(&pThis, this + 3);  // map lower_bound（键在 +12）
    dword_9B8DBC2 = dword_9B8DBC;
  }
  else  // 否则分支
  {
    sub_4B1BA0(&pThis, this + 38);  // map lower_bound（键在 +12）
    dword_9B8DBC2 = dword_9B8DC8;
  }
  if ( pThis == (uint32_t *)dword_9B8DBC2 )  // 若 pThis == (uint32_t *)dword_9B8DBC2
    return 0;
  else  // 否则分支
    return pThis[5];  // 返回 取 pThis[5]
}



// ------------------------------------------------------------
// 0x578240 sub_578240 —— 堆叠物数量/外观计算（4F3360 物品数据 + 4B2BF0 表现，66 行）
// ------------------------------------------------------------
int **/*thiscall*/ sub_578240(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)  // 实现：堆叠物数量/外观计算（4F3360 物品数据 + 4B2BF0 表现，66 行）
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int *pDwArg322; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )  // 复合条件判定（与/或）
  {
    sub_4F3360(*(void **)(fld_e1 + 4));  // 调 sub_4F3360
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);  // fld_e12 = this+1
    *(this + 2) = nullptr;  // this+8 = nullptr
    *fld_e12 = fld_e12;  // *fld_e12 写入 fld_e12
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);  // *pDwArg2 写入 **(this + 1)
    return pDwArg2;
  }
  else  // 否则分支
  {
    if ( pDwArg3 != pDwArg4 )  // 若 pDwArg3 != pDwArg4
    {
      do  // do-while 循环体起点
      {
        pDwArg322 = pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 25) == 0 )  // 若 *((uint8_t *)pDwArg32 + 25) == 0
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 25) != 0 )  // 若 *((uint8_t *)v11 + 25) != 0
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 25) == 0; i = (int *)i[1] )  // 遍历循环
            {
              if ( pDwArg32 != (int *)i[2] )  // 若 pDwArg32 != (int *)i[2]
                break;  // 跳出循环/分支
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else  // 否则分支
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 25) == 0; j = (int *)*j )  // 遍历循环
              pDwArg32 = j;
          }
        }
        sub_4B2BF0(&pDwArg3, pDwArg322);  // std::map 节点删除（RB 再平衡）
      }
      while ( pDwArg32 != pDwArg42 );  // 条件循环
    }
    *pDwArg2 = pDwArg32;  // *pDwArg2 写入 pDwArg32
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x578300 sub_578300 —— 转发 578240
// ------------------------------------------------------------
int /*thiscall*/ sub_578300(int this)  // 实现：转发 578240
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_578240((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));  // 堆叠物数量/外观计算（4F3360 物品数据 + 4B2BF0 表现，66 行）
  j__free(*(void **)(this + 4));  // 调 j__free
  *(uint32_t *)(this + 4) = 0;  // this+4 = 0
  *(uint32_t *)(this + 8) = 0;  // this+8 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x578340 sub_578340 —— 堆叠物初始化/绘制（106 行：41B0D0/418DD0/4ED3F0/41FFE0/4206D0）
// ------------------------------------------------------------
int /*thiscall*/ sub_578340(int this, const char *ArgList)  // 实现：堆叠物初始化/绘制（106 行：41B0D0/418DD0/4ED3F0/41FFE0/4206D0）
{
  uint32_t *v3; // eax
  uint32_t *v4; // ebx
  int result; // eax
  int v6; // eax
  int v7; // eax
  int pThis; // edi
  unsigned int v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // esi
  unsigned int v13; // edx
  uint32_t *v14; // edi
  int v15; // [esp-4h] [ebp-18h]
  int v16; // [esp-4h] [ebp-18h]
  int v17; // [esp+Ch] [ebp-8h]
  int ArgLista; // [esp+1Ch] [ebp+8h]

  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84D4 + 4))(dword_8F84D4, ArgList);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  v4 = v3;
  if ( v3 == nullptr )  // 若 v3 为空
    return off_77F3FC("STACKABLE CREATE FAIL! FILENAME[%s]", ArgList);  // 返回 调 off_77F3FC
  *(uint32_t *)(this + 12) = *v3;  // this+12 = *v3
  sub_41B0D0(v3 + 1);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(v4 + 2);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(v4 + 3);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  sub_41B0D0(v4 + 4);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(uint32_t *)(this + 32) = v4[5];  // this+32 = v4[5]
  *(uint32_t *)(this + 36) = v4[6];  // this+36 = v4[6]
  *(uint32_t *)(this + 44) = v4[9];  // this+44 = v4[9]
  *(uint32_t *)(this + 60) = v4[10];  // this+60 = v4[10]
  *(uint32_t *)(this + 48) = v4[11];  // this+48 = v4[11]
  *(uint32_t *)(this + 52) = v4[12];  // this+52 = v4[12]
  *(uint32_t *)(this + 56) = v4[13];  // this+56 = v4[13]
  *(uint32_t *)(this + 64) = v4[14];  // this+64 = v4[14]
  *(uint8_t *)(this + 68) = *((uint8_t *)v4 + 60);  // this+68 = *((uint8_t *)v4 + 60)
  *(uint8_t *)(this + 69) = *((uint8_t *)v4 + 61);  // this+69 = *((uint8_t *)v4 + 61)
  *(uint8_t *)(this + 70) = *((uint8_t *)v4 + 62);  // this+70 = *((uint8_t *)v4 + 62)
  *(uint8_t *)(this + 71) = *((uint8_t *)v4 + 63);  // this+71〔bMoveType〕
  *(uint32_t *)(this + 8) = v4[16];  // this+8 = v4[16]
  *(uint32_t *)(this + 72) = v4[17];  // this+72 = v4[17]
  if ( strcmp((const char *)sub_41ACF0(v4 + 20), szPassword) != 0 )  // 驻留串句柄 → 字符串指针
  {
    v6 = sub_41ACF0(v4 + 20);  // 驻留串句柄 → 字符串指针
    v15 = v4[21];  // v15 = 取 v4[21]
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v6);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    *(uint32_t *)(this + 76) = sub_418DD0(v15);  // this+76〔pBtnActionE〕
  }
  if ( strcmp((const char *)sub_41ACF0(v4 + 22), szPassword) == 0 )  // 驻留串句柄 → 字符串指针
  {
    pThis = this;
  }
  else  // 否则分支
  {
    v7 = sub_41ACF0(v4 + 22);  // 驻留串句柄 → 字符串指针
    v16 = v4[23];  // v16 = 取 v4[23]
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v7);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    pThis = this;
    *(uint32_t *)(this + 80) = sub_418DD0(v16);  // this+80 = sub_418DD0(v16)
  }
  sub_41B0D0(v4 + 26);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(uint32_t *)(pThis + 92) = v4[8];  // pThis+92 = v4[8]
  sub_4ED3F0(pThis + 96, (int)(v4 + 30));  // int 向量拷贝赋值（全容量路径）
  v9 = 0;
  ArgLista = 0;
  while ( 1 )  // 条件循环
  {
    v10 = v4[35];  // v10 = 取 v4[35]
    if ( v10 == 0 || v9 >= (v4[36] - v10) >> 2 )  // 若 v10 == 0
      break;  // 跳出循环/分支
    v11 = *(uint32_t *)(pThis + 116);  // v11 = pThis+116
    v12 = pThis + 112;
    v17 = v10 + 4 * v9;
    if ( v11 != 0 )  // 若 v11 非 0
      v13 = (*(uint32_t *)(pThis + 120) - v11) >> 2;
    else  // 否则分支
      v13 = 0;
    if ( v11 != 0 && v13 < (*(uint32_t *)(pThis + 124) - v11) >> 2 )  // 若 v11 != 0
    {
      v14 = *(uint32_t **)(pThis + 120);
      sub_41FFE0(v14, 1, v17);  // 驻留句柄区间填充 nArg2 个元素
      *(uint32_t *)(v12 + 8) = v14 + 1;  // v12+8 = v14 + 1
      pThis = this;
      v9 = ++ArgLista;
    }
    else  // 否则分支
    {
      sub_4206D0(pThis + 112, *(uint32_t *)(pThis + 120), 1u, v17);  // vector 中间插入（4 字节元素）
      v9 = ++ArgLista;
    }
  }
  sub_41B0D0(v4 + 29);  // 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(uint32_t *)(pThis + 148) = v4[25];  // pThis+148 = v4[25]
  *(uint32_t *)(pThis + 152) = v4[18];  // pThis+152 = v4[18]
  *(uint8_t *)(pThis + 160) = *((uint8_t *)v4 + 76);  // pThis+160 = *((uint8_t *)v4 + 76)
  result = v4[24];  // result = 取 v4[24]
  *(uint32_t *)(pThis + 156) = result;  // pThis+156 = result
  return result;
}



// ------------------------------------------------------------
// 0x578580 CNRDStackable__vmt70 —— CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDStackable__vmt70(uint32_t *this, int nArg2)  // 实现：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
{
  int v3; // esi
  uint32_t *result; // eax
  uint32_t *pThis_3; // [esp-4h] [ebp-14h]
  uint32_t *pThis_26; // [esp+Ch] [ebp-4h]

  pThis_26 = this + 38;  // this+38〔bFadeFlag38〕
  if ( *(this + 38) == -1 )  // 若 *(this + 38) == -1
  {
    v3 = sub_699000((int)&unk_9B0C70);  // 【clock_now(clk)】
    pThis_3 = this + 3;
  }
  else  // 否则分支
  {
    v3 = sub_699000((int)&unk_9B0C70);  // 【clock_now(clk)】
    pThis_3 = pThis_26;
  }
  result = (uint32_t *)sub_4B44E0(pThis_3);  // map 查或插入返回 +16
  *result = nArg2;  // *result 写入 nArg2
  result[1] = nArg2 + v3;
  return result;
}



// ============================================================
// 【分区 10】地面掉落物/金币（0x5785E0-0x5787A0）
// 金币绘制 0x578680：资源 Item/FieldImage.img，事件标签 GOLD_DROP1/GOLD_DROP2。
// ============================================================
// ------------------------------------------------------------
// 0x5785E0 sub_5785E0 —— 地面掉落物初始化（433B00 对象登记）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5785E0(uint32_t *this)  // 实现：地面掉落物初始化（433B00 对象登记）
{
  uint32_t *v2; // eax

  v2 = sub_433B00();  // map 节点分配（0x1C）
  *(this + 1) = v2;  // this+4 = v2
  *((uint8_t *)v2 + 25) = 1;  // v2[25] = 1
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;  // this+8 = 0
  return this;
}



// ------------------------------------------------------------
// 0x578610 sub_578610 —— 掉落物动画驱动（442D00 + 578340）
// ------------------------------------------------------------
int /*thiscall*/ sub_578610(void *this, int ArgList)  // 实现：掉落物动画驱动（442D00 + 578340）
{
  int v2; // edi
  const char *v4; // eax
  int *v6; // [esp+8h] [ebp-4h] BYREF

  v2 = ArgList;
  sub_442D00(&dword_9B6C60, &v6, &ArgList);  // 红黑树等键查找（_Find）
  if ( v6 == (int *)dword_9B6C64 )  // 若 v6 == (int *)dword_9B6C64
    return off_77F3FC("STACKABLE CREATE FAIL! INDEX %d", v2);  // 返回 调 off_77F3FC
  v4 = (unsigned int)v6[10] < 0x10 ? (const char *)(v6 + 5) : (const char *)v6[5];
  if ( v4 == nullptr )  // 若 v4 为空
    return off_77F3FC("STACKABLE CREATE FAIL! INDEX %d", v2);  // 返回 调 off_77F3FC
  else  // 否则分支
    return sub_578340((int)this, v4);  // 堆叠物初始化/绘制（106 行：41B0D0/418DD0/4ED3F0/41FFE0/4206D0）
}



// ------------------------------------------------------------
// 0x578680 sub_578680 —— 金币掉落绘制：资源 Item/FieldImage.img，事件标签 GOLD_DROP1/GOLD_DROP2（418DD0 取精灵 + 41BFE0/41A590）
// ------------------------------------------------------------
void /*thiscall*/ sub_578680(int this, unsigned int uArg2)  // 实现：金币掉落绘制：资源 Item/FieldImage.img，事件标签 GOLD_DROP1/GOLD_DROP2（418DD0 取精灵 + …
{
  char *v3; // eax
  char *v4; // eax
  int v5; // edx
  int v6; // [esp-4h] [ebp-Ch]

  *(uint32_t *)(this + 12) = 0;  // this+12 = 0
  v3 = sub_422E70(424);  // v3 = 调 sub_422E70 返回值
  sub_41BFE0((void **)(this + 16), v3);  // 驻留字符串设置（set(const char*)）
  v4 = sub_422E70(424);  // v4 = 调 sub_422E70 返回值
  sub_41BFE0((void **)(this + 24), v4);  // 驻留字符串设置（set(const char*)）
  *(uint32_t *)(this + 64) = 0;  // this+64 = 0
  sub_41A590(this + 132, v5, uArg2);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  if ( uArg2 >= 0x64 )  // 若 uArg2 >= 0x64
  {
    if ( uArg2 >= 0x1F4 )  // 若 uArg2 >= 0x1F4
      v6 = 25;
    else  // 否则分支
      v6 = 27;
    (*(void (/*stdcall*/ **)(const char *))(*(uint32_t *)dword_8F84B8 + 60))("Item/FieldImage.img");  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    *(uint32_t *)(this + 80) = sub_418DD0(v6);  // this+80 = sub_418DD0(v6)
    sub_41BFE0((void **)(this + 84), "GOLD_DROP2");  // 驻留字符串设置（set(const char*)）
  }
  else  // 否则分支
  {
    (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Item/FieldImage.img");  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    *(uint32_t *)(this + 80) = sub_418DD0(26);  // this+80 = sub_418DD0(26)
    sub_41BFE0((void **)(this + 84), "GOLD_DROP1");  // 驻留字符串设置（set(const char*)）
  }
}



// ------------------------------------------------------------
// 0x578740 sub_578740 —— 粒子/动画辅助（41A590）
// ------------------------------------------------------------
int /*fastcall*/ sub_578740(int pArg1, int nArg2)  // 实现：粒子/动画辅助（41A590）
{
  *(uint32_t *)(pArg1 + 96) = 289;  // pArg1+96 = 289
  *(uint32_t *)(pArg1 + 972) = 0;  // pArg1+972 = 0
  *(uint8_t *)(pArg1 + 976) = 0;  // pArg1+976 = 0
  *(uint8_t *)(pArg1 + 977) = 0;  // pArg1+977 = 0
  *(uint32_t *)(pArg1 + 980) = 0;  // pArg1+980 = 0
  *(uint8_t *)(pArg1 + 984) = 0;  // pArg1+984 = 0
  *(uint8_t *)(pArg1 + 1000) = 0;  // pArg1+1000 = 0
  return sub_41A590(pArg1 + 1016, nArg2, 0xFFFF);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x578780 sub_578780 —— 17 行小辅助（表现参数）
// ------------------------------------------------------------
int /*thiscall*/ sub_578780(uint32_t *this)  // 实现：17 行小辅助（表现参数）
{
  int fld_e243; // ecx
  int result; // eax

  fld_e243 = *(this + 243);  // fld_e243 = this+243
  if ( fld_e243 != 0 )  // 若 fld_e243 非 0
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e243 + 4))(fld_e243, 1);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  *(this + 243) = 0;  // this+972 = 0
  return result;
}



// ============================================================
// 【分区 11】CNRDItemObject 掉落物品对象（0x5787A0-0x579020）
// vmtC=打开/生成、vmt144=绘制前置、vmt14C=主状态（148 行，ITEM_DROP 标签:
// 落地弹跳/旋转/拾取判定）；0x578C40=物理更新、0x578D50=表现更新。
// ============================================================
// ------------------------------------------------------------
// 0x5787A0 CNRDItemObject__vmtC —— CNRDItemObject__vmtC 打开/生成槽（460110）
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDItemObject__vmtC(int this)  // 实现：CNRDItemObject__vmtC 打开/生成槽（460110）
{
  int v2; // eax
  int v3; // edx
  unsigned int result; // eax
  uint32_t *fld_74; // ecx

  CNRDPassiveObject__vmtC((int *)this);
  v2 = *(uint32_t *)this;  // v2 = this
  *(uint8_t *)(this + 976) = 0;  // this+976〔bItemLand976〕
  (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t, int))(v2 + 284))(this, 0, -16715521, 0, 1);  // 调用虚函数槽 +284
  v3 = *(uint32_t *)this;  // v3 = this
  *(uint8_t *)(this + 984) = 0;  // this+984〔bItemInit984〕
  result = ((*(int (/*thiscall*/ **)(int))(v3 + 128))(this) <= 0) + 1;
  fld_74 = *(uint32_t **)(this + 116);  // fld_74 = 读 this+116
  if ( fld_74 != nullptr )  // 若 fld_74 有效（非空）
  {
    result = sub_460110(fld_74, this, result);  // 图标对象换槽（重写槽号后重挂）
    *(uint8_t *)(this + 1044) = 0;  // this+1044〔bPickupOk1044〕
  }
  else  // 否则分支
  {
    *(uint8_t *)(this + 1044) = 0;  // this+1044〔bPickupOk1044〕
    *(uint32_t *)(this + 108) = result;  // this+108〔pDropCtx108〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x578810 CNRDItemObject__vmt144 —— CNRDItemObject__vmt144 绘制前置槽（25 行）
// ------------------------------------------------------------
void /*thiscall*/ CNRDItemObject__vmt144(int this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：CNRDItemObject__vmt144 绘制前置槽（25 行）
{
  int nItemPhase972; // eax  | +0x03CC → 掉落物状态槽（5787A0：fld_3CC = *(+972)）（证据 va=00578810）（CNRDItemObject；va=00578810）

  if ( (uint8_t)nArg2 != 0 )  // 若 (uint8_t)nArg2 != 0
  {
    if ( *(uint8_t *)(this + 976) != 0 )  // this+976〔bItemLand976〕
    {
      nItemPhase972 = *(uint32_t *)(this + 972);  // this+972〔nItemPhase972〕
      if ( nItemPhase972 != 0 )  // 若 fld_3CC 非 0
        (*(void (**)(void))(*(uint32_t *)nItemPhase972 + 16))();  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
    }
    nullsub_2(nArg2, nArg3, nArg4, nArg5);
  }
  else  // 否则分支
  {
    nullsub_2(0, nArg3, nArg4, nArg5);
  }
}



// ------------------------------------------------------------
// 0x578870 sub_578870 —— 掉落物字符串初始化（41A590 + 698F90）
// ------------------------------------------------------------
char /*fastcall*/ sub_578870(uint8_t *pArg1, int nArg2, int nArg3, int nArg4)  // 实现：掉落物字符串初始化（41A590 + 698F90）
{
  char result; // al

  result = nArg3;
  if ( nArg3 != 0xFFFF )  // 若 nArg3 != 0xFFFF
  {
    sub_41A590((unsigned int)(pArg1 + 1016), nArg2, nArg3);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    pArg1[1000] = 1;
    pArg1[1001] = 0;
    pArg1[1002] = 0;
    return sub_698F90((int)(pArg1 + 988), nArg4, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return result;
}



// ------------------------------------------------------------
// 0x5788B0 sub_5788B0 —— 掉落物表现（41A5E0/422E70/43BEE0）
// ------------------------------------------------------------
char /*thiscall*/ sub_5788B0(uint32_t *this, int nArg2)  // 实现：掉落物表现（41A5E0/422E70/43BEE0）
{
  unsigned int pThis_FE; // edi
  char *v4; // eax
  int fld_e253; // [esp-4h] [ebp-210h]
  char Buffer[512]; // [esp+8h] [ebp-204h] BYREF
  int dword_796E502; // [esp+208h] [ebp-4h]

  pThis_FE = (unsigned int)(this + 254);  // this+254〔field_00FE〕
  dword_796E502 = dword_796E50;
  if ( sub_41A5E0((unsigned int)(this + 254)) == 0xFFFF || sub_41A5E0(pThis_FE) == nArg2 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    return 1;  // 返回 1(成功)
  fld_e253 = *(this + 253) / 1000;  // this+1012〔uGrabA1012〕
  v4 = sub_422E70(2015);  // v4 = 调 sub_422E70 返回值
  sprintf(Buffer, v4, fld_e253);  // 拼字符串
  sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // 主管理器(消息/弹窗)
  return 0;
}



// ------------------------------------------------------------
// 0x578960 CNRDItemObject__vmt14C —— CNRDItemObject__vmt14C 主状态（148 行）：ITEM_DROP 标签——落地弹跳/旋转/拾取判定（460110/699000/4600B0）
// ------------------------------------------------------------
void /*thiscall*/ sub_578960(uint32_t *this)  // 【CNRDItemObject__vmt14C】
{
  bool v2; // cc
  int pDropCtx108; // eax  | +0x006C → 掉落上下文槽（CNRDItemObject；va=005787A0）
  int pThis_9; // eax
  int fld_e28; // ecx  | +0x0070 → 宿主/共享组件槽 = 观察者 vector 首针（CNRDPassiveObject·基类；va=00600890）
  int v6; // eax
  int pObj; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  void *fld_e29; // ecx
  int pThis_10; // edi
  int nRand; // edx
  void *Block2; // eax
  bool v16; // zf
  int nItemPhase972; // ecx  | +0x03CC → 掉落物状态槽（5787A0：fld_3CC = *(+972)）（证据 va=00578810）（CNRDItemObject；va=00578810）
  int v18; // edi
  int v19; // eax
  int pThis_102; // eax
  int v21; // eax
  int v22; // eax
  int v23; // ebx
  int v24; // eax
  int v25; // eax
  int v26; // edx
  int fld_e253; // edi
  int v28; // edx
  int v29; // [esp-Ch] [ebp-40h]
  int v30; // [esp-8h] [ebp-3Ch]
  uint8_t v31[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  int v33; // [esp+1Ch] [ebp-18h] BYREF
  int v34; // [esp+20h] [ebp-14h] BYREF
  float pThis_108; // [esp+24h] [ebp-10h]
  int v36; // [esp+30h] [ebp-4h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) <= 0;  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  pDropCtx108 = *(this + 27);  // this+108〔pDropCtx108〕
  if ( v2 )  // 若 v2
  {
    if ( pDropCtx108 != 2 )  // 若 fld_e27 != 2
      sub_460110(this, 2);  // 图标对象换槽（重写槽号后重挂）
    if ( sub_699000((int)(this + 16)) >= *(this + 245) )  // 【clock_now(clk)】
    {
      pObj = dword_8F82B8;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F82B8 + 12))(dword_8F82B8, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
      v8 = *(uint32_t *)pObj;  // v8 = pObj
      v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v9 + 1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
      v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v10);  // 调虚槽 +120：动画对象
      (*(void (/*thiscall*/ **)(int, int))(v8 + 40))(pObj, v11);  // 调用虚函数槽 +40
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pObj + 92))(pObj, v31);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
      fld_e29 = (void *)*(this + 29);
      v36 = 0;
      sub_4600B0(fld_e29, 2, 0, (int)v31);  // 调 sub_4600B0
      pThis_10 = sub_699000((int)(this + 16));  // 【clock_now(clk)】
      nRand = rand() % 1000;  // nRand = 调 rand
      Block2 = Block;
      v16 = Block == nullptr;
      v36 = -1;
      *(this + 245) = pThis_10 + nRand + 1500;  // this+980 = pThis_10 + nRand + 1500
      if ( !v16 )  // 若 !v16
        j__free(Block2);  // 调 j__free
    }
    if ( *((uint8_t *)this + 984) != 0 )  // this+984〔bItemInit984〕
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 272))(this, 0, 0);  // 调虚槽 +272
      nItemPhase972 = *(this + 243);  // this+972〔nItemPhase972〕
      if ( nItemPhase972 != 0 )  // 若 fld_e243 非 0
      {
        v18 = *this;
        v19 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)nItemPhase972 + 56))(nItemPhase972, -1, 0, 0);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
        (*(void (/*thiscall*/ **)(uint32_t *, int))(v18 + 212))(this, v19);  // 调用虚函数槽 +212
      }
      *((uint8_t *)this + 984) = 0;  // this+984〔bItemInit984〕
      *((uint8_t *)this + 1044) = 1;  // this+1044〔bPickupOk1044〕
      *((uint8_t *)this + 1045) = 0;
      *((uint8_t *)this + 1046) = 0;
      sub_698F90((int)(this + 258), 1000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    if ( *((uint8_t *)this + 1044) != 0 )  // this+1044〔bPickupOk1044〕
    {
      pThis_108 = *((float *)this + 264);
      pThis_102 = sub_699000((int)(this + 258));  // 【clock_now(clk)】
      if ( pThis_102 >= SLODWORD(pThis_108) && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 调虚槽 +308：是否本地玩家
      {
        pThis_108 = *(float *)this;
        v21 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(LODWORD(pThis_108) + 124))(this, 0);  // 调用虚函数槽 +124
        v22 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v21);  // 调虚槽 +120：动画对象
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(LODWORD(pThis_108) + 136))(this, v22) == 0 )
        {
          v23 = *this;
          v24 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 124))(this, 300, 1, 5);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v24);  // 调虚槽 +120：动画对象
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int *, int *, int))(v23 + 140))(this, &v33, &v34, v25) != 0 )
          {
            off_77F3FC((char *)&byte_726738);
            v26 = *this;
            v30 = v34;
            v29 = v33;
            *((uint8_t *)this + 1044) = 0;  // this+1044〔bPickupOk1044〕
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(v26 + 108))(this, v29, v30, 0);  // 调用虚函数槽 +108
          }
          else  // 否则分支
          {
            off_77F3FC((char *)&byte_7266E8);
            *((uint8_t *)this + 1045) = 0;
            *((uint8_t *)this + 1046) = 0;
            sub_698F90((int)(this + 258), 1000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
          }
        }
      }
    }
  }
  else  // 否则分支
  {
    if ( pDropCtx108 != 1 )  // 若 fld_e27 != 1
      sub_460110(this, 1);  // 图标对象换槽（重写槽号后重挂）
    pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    fld_e28 = *(uint32_t *)(*(this + 28) + 104);  // this+112〔pHostComp112〕
    pThis_108 = (double)pThis_9 * 0.0099999998;
    if ( fld_e28 != 0 )  // 若 fld_e28 非 0
    {
      v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e28 + 16))(fld_e28) + 72);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
      if ( v6 < 90 || v6 > 270 )  // 若 v6 < 90 与/或 v6 > 270
        pThis_108 = -pThis_108;
    }
    (*(void (/*thiscall*/ **)(uint32_t *, int, float))(*this + 272))(this, 1, COERCE_FLOAT(LODWORD(pThis_108)));  // 调虚槽 +272
    if ( *((uint8_t *)this + 984) == 0 )  // this+984〔bItemInit984〕
    {
      sub_432EA0("ITEM_DROP", -1, 0, 0);  // 音效播放包装（非空判定）
      *((uint8_t *)this + 984) = 1;  // this+984〔bItemInit984〕
    }
  }
  if ( *((uint8_t *)this + 1000) != 0 )  // 若 *((uint8_t *)this + 1000) != 0
  {
    fld_e253 = *(this + 253);  // this+1012〔uGrabA1012〕
    if ( sub_699000((int)(this + 247)) >= fld_e253 )  // 【clock_now(clk)】
      sub_41A590((unsigned int)(this + 254), v28, 0xFFFF);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
}


// ------------------------------------------------------------
// 0x578C40 sub_578C40 —— 掉落物物理步进（42AF90/657740/42FCB0/498530/4924C0：重力/地面碰撞）
// ------------------------------------------------------------
int /*thiscall*/ sub_578C40(void ***this, void **pArg2)  // 实现：掉落物物理步进（42AF90/657740/42FCB0/498530/4924C0：重力/地面碰撞）
{
  void **fld_e34; // ebx
  void **v5; // eax
  int result; // eax
  void **v7; // eax
  int v8; // eax
  int v9; // ebx
  int v10; // [esp+20h] [ebp+8h]

  fld_e34 = *(this + 34);  // fld_e34 = this+34
  *(this + 243) = pArg2;  // this+972 = pArg2
  if ( fld_e34 != nullptr )  // 若 fld_e34 有效（非空）
  {
    sub_42AF90(fld_e34);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_e34, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  v5 = *this;
  *(this + 34) = nullptr;  // this+136 = nullptr
  result = ((int (/*thiscall*/ *)(void ***, uint32_t))v5[49])(this, 0);
  if ( pArg2 != nullptr )  // 若 pArg2 有效（非空）
  {
    result = (*((int (/*thiscall*/ **)(void **))*pArg2 + 4))(pArg2);  // 调用虚函数槽 +4
    if ( *(uint32_t *)(result + 72) != 0 )  // 若 *(uint32_t *)(result + 72) != 0
    {
      v10 = sub_42FCB0(228);  // CRT 一次性初始化
      v7 = nullptr;  // v7 = 空指针
      if ( v10 != 0 )  // 若 v10 非 0
      {
        v8 = (*((int (/*thiscall*/ **)(void **))*pArg2 + 4))(pArg2);  // 调用虚函数槽 +4
        v7 = (void **)sub_498530(*(uint32_t *)(v8 + 72));  // 动画对象构造（vftable 装配 + 复位 + 首帧占位）
      }
      *(this + 34) = v7;  // this+136 = v7
      v9 = sub_4924C0(0);  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      *(uint32_t *)(v9 + 12) = *(uint32_t *)(*(uint32_t *)((*((int (/*thiscall*/ **)(void **))*pArg2 + 4))(pArg2) + 72) + 36) / -2;
      *(uint32_t *)(v9 + 16) = *(uint32_t *)(*(uint32_t *)((*((int (/*thiscall*/ **)(void **))*pArg2 + 4))(pArg2) + 72) + 40) / -2;
      return ((int (/*thiscall*/ *)(void ***, uint32_t))(*this)[49])(this, *(this + 34));
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x578D50 sub_578D50 —— 掉落物更新（578C40 物理 + 4D33A0/445D00/445B90/4A0B60 表现）
// ------------------------------------------------------------
int /*thiscall*/ sub_578D50(int this, void **pArg2, int nArg3, int nArg4)  // 实现：掉落物更新（578C40 物理 + 4D33A0/445D00/445B90/4A0B60 表现）
{
  int pThis_40; // edi
  int result; // eax
  char *pObj; // edi
  char *v8; // eax

  *(uint32_t *)(this + 316) = 1;  // this+316 = 1
  *(uint32_t *)(this + 320) = 1;  // this+320 = 1
  sub_578C40((void ***)this, pArg2);  // 掉落物物理步进（42AF90/657740/42FCB0/498530/4924C0：重力/地面碰撞）
  *(uint8_t *)(this + 700) = 0;  // this+700〔bSnapshot700〕
  *(uint8_t *)(this + 701) = 1;  // this+701〔bSnapshot701〕
  *(uint32_t *)(this + 108) = 1;  // this+108 = 1
  pThis_40 = sub_699000(this + 64);  // 【clock_now(clk)】
  *(uint32_t *)(this + 980) = pThis_40 + rand() % 1000 + 1500;  // this+980 = pThis_40 + rand() % 1000 + 1500
  if ( byte_9B8DD0 == 0 )  // 若 byte_9B8DD0 为 0
  {
    byte_9B8DE4 = 1;
    dword_9B8DE7 = 400;
    dword_9B8DEB = 400;
    dword_9B8E1C = 1500;
    byte_9B8E31 = 2;
    dword_9B8DE0 = 1;
    byte_9B8DD0 = 1;
  }
  result = nArg3;
  pObj = nullptr;  // pObj = 空指针
  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    dword_9B8E24 = sub_4D33A0(nArg3) % 20 + 65;  // dword_9B8E24 = 调 sub_4D33A0 返回值
    dword_9B8E20 = nArg4;
    v8 = (char *)sub_445D00(156);  // CRT 一次性池初始化（池 &unk_97B6D4）
    if ( v8 != nullptr )  // 若 v8 有效（非空）
      pObj = sub_445B90(v8);  // CNRDParticle 构造
    (*(void (/*thiscall*/ **)(char *, void *))(*(uint32_t *)pObj + 12))(pObj, &unk_9B8DD8);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
    (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pObj + 4))(pObj, 0);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
    sub_4A0B60(pObj);  // 调 sub_4A0B60
    result = *(uint32_t *)(this + 112);  // this+112〔pHostComp112〕
    *(uint32_t *)(result + 112) = 1;  // result+112 = 1
  }
  return result;
}



// ------------------------------------------------------------
// 0x578E90 sub_578E90 —— 掉落物成员访问（41A580）
// ------------------------------------------------------------
int /*thiscall*/ sub_578E90(int this)  // 实现：掉落物成员访问（41A580）
{
  sub_41A580(this + 282);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 268);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  `eh vector destructor iterator'((void *)(this + 240), 0xEu, 2, sub_432D10);  // this+240〔nSyncArgB〕
  `eh vector destructor iterator'((void *)(this + 184), 0x1Cu, 2, sub_501490);
  `eh vector destructor iterator'((void *)(this + 128), 0x1Cu, 2, sub_501490);
  sub_41A580(this + 112);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 98);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 84);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 70);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  `eh vector destructor iterator'((void *)(this + 42), 0xEu, 2, sub_432D10);
  sub_41A580(this + 28);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  return sub_41A580(this + 8);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
}



// ------------------------------------------------------------
// 0x578F90 sub_578F90 —— 物品说明请求（406D00）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_578F90(uint32_t *this)  // 实现：物品说明请求（406D00）
{
  uint32_t *pThis_4; // ecx
  unsigned int v3; // edx
  uint32_t *v4; // edi
  uint32_t *v5; // ebx
  uint8_t v7[4]; // [esp+Ch] [ebp-14h] BYREF
  uint32_t *pThis; // [esp+10h] [ebp-10h]
  int v9; // [esp+1Ch] [ebp-4h]

  pThis_4 = this + 4;
  pThis_4[6] = 15;
  pThis_4[5] = 0;
  pThis = this;
  *((uint8_t *)pThis_4 + 4) = 0;
  v9 = 0;
  *this = -1;  // *this 写入 -1
  *(this + 1) = -1;  // this+4 = -1
  *(this + 2) = -1;  // this+8 = -1
  *(this + 3) = -1;  // this+12 = -1
  v3 = pThis_4[6];  // v3 = 取 pThis_4[6]
  v4 = pThis_4 + 1;
  if ( v3 < 0x10 )  // 若 v3 < 0x10
    v5 = pThis_4 + 1;
  else  // 否则分支
    v5 = (uint32_t *)*v4;
  if ( v3 >= 0x10 )  // 若 v3 >= 0x10
    v4 = (uint32_t *)*v4;
  sub_406D00(v7, v4, (char *)v5 + pThis_4[5]);  // std::string 中段擦除（·sub_401230 erase，pos 与 n 由指针差换算）
  return this;
}



// ============================================================
// 【分区 12】角色构造族 IRDCharacter + 四职业（0x579020-0x57A0A0）
// 构造主体 0x579730（107 行）；基类默认虚槽桩 0x5794A0-0x5796C0；
// 虚槽桩（vmt380..vmt534，10-25 行 return 0/转发）；四职业构造链:
// Swordman 0x579AC0(5F0D40) / Fighter 0x579BD0(5E6C50) / Gunner 0x579D90(4C4260)
// / Mage 0x579EE0(5DDCA0)；0x579F90=按职业 id 分派各后段构造。
// ============================================================
// ------------------------------------------------------------
// 0x579020 sub_579020 —— 角色对象辅助（4015C0 字符串）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_579020(uint32_t *this)  // 实现：角色对象辅助（4015C0 字符串）
{
  char *pThis_3; // ecx

  pThis_3 = (char *)(this + 3);
  *((uint32_t *)pThis_3 + 6) = 15;
  *((uint32_t *)pThis_3 + 5) = 0;  // pThis_3[5] = 0
  pThis_3[4] = 0;
  *this = 4;  // *this 写入 4
  *(this + 1) = -1;  // this+4 = -1
  *((uint8_t *)this + 8) = 0;  // this[8] = 0
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 10) = 0;  // this+40 = 0
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 13) = 0;  // this+52 = 0
  *(this + 14) = 0;  // this+56 = 0
  *(this + 15) = 0;  // this+60 = 0
  return this;
}



// ------------------------------------------------------------
// 0x5790A0 sub_5790A0 —— 角色对象辅助 2（41A630 + 4C1BA0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5790A0(uint32_t *this)  // 实现：角色对象辅助 2（41A630 + 4C1BA0）
{
  uint32_t *pThis_2; // edi

  pThis_2 = this + 2;
  sub_41A630((unsigned int)(this + 2));  // 调 sub_41A630
  *pThis_2 = &vftbl_clong;  // *pThis_2 写入 &vftbl_clong
  sub_41A630((unsigned int)(this + 7));  // 调 sub_41A630
  *(this + 7) = &vftbl_clong;  // this+28 = &vftbl_clong
  `eh vector constructor iterator'((char *)this + 42, 0xEu, 2, sub_401040, sub_432D10);  // clong 构造（·sub_41A630 随机源初始化 + 挂 clong::vftable）
  sub_41A630((unsigned int)this + 70);  // 调 sub_41A630
  *(uint32_t *)((char *)this + 70) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 21));  // this+21〔bArmorState〕
  *(this + 21) = &vftbl_clong;  // this+84 = &vftbl_clong
  sub_41A630((unsigned int)this + 98);  // 调 sub_41A630
  *(uint32_t *)((char *)this + 98) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 28));  // 调 sub_41A630
  *(this + 28) = &vftbl_clong;  // this+112〔pHostComp112〕
  `eh vector constructor iterator'(this + 32, 0x1Cu, 2, sub_40C120, sub_501490);  // 空串初始化（len 0 / cap 15 / 首字节 0；this+4 系）
  `eh vector constructor iterator'(this + 46, 0x1Cu, 2, sub_40C120, sub_501490);  // 空串初始化（len 0 / cap 15 / 首字节 0；this+4 系）
  `eh vector constructor iterator'(this + 60, 0xEu, 2, sub_401040, sub_432D10);  // clong 构造（·sub_41A630 随机源初始化 + 挂 clong::vftable）
  sub_41A630((unsigned int)(this + 67));  // this+67〔nPeriodMs〕
  *(this + 67) = &vftbl_clong;  // this+268 = &vftbl_clong
  sub_41A630((unsigned int)this + 282);  // 调 sub_41A630
  *(uint32_t *)((char *)this + 282) = &vftbl_clong;
  sub_4C1BA0(this);  // 调 sub_4C1BA0
  return this;
}



// ------------------------------------------------------------
// 0x579200 sub_579200 —— 角色构造前置（4015C0/401740）
// ------------------------------------------------------------
void /*noreturn*/ sub_579200()  // 实现：角色构造前置（4015C0/401740）
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
  sub_401740(v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x579270 sub_579270 —— 角色对象初始化（85 行：4A49B0/4A3450/433B00/4CE550/4BA8A0 部件与动画装配）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_579270(uint32_t *this, char ArgList)  // 实现：角色对象初始化（85 行：4A49B0/4A3450/433B00/4CE550/4BA8A0 部件与动画装配）
{
  uint32_t *pThis_710; // eax
  int i; // ecx
  uint32_t *v5; // eax

  sub_4A49B0();  // 调 sub_4A49B0
  *this = &vftbl_IRDCharacter;  // *this 写入 &vftbl_IRDCharacter
  sub_579020(this + 1787);  // 角色对象辅助（4015C0 字符串）
  *(this + 1803) = 0;  // this+7212 = 0
  pThis_710 = this + 1808;
  for ( i = 4; i != 0; --i )  // 循环：i 从 4 递减到 0
  {
    *(pThis_710 - 4) = 0;
    *pThis_710++ = 0;  // *pThis_710++ 写入 0
  }
  *(this + 1812) = 0;  // this+7248 = 0
  *(this + 1813) = 0;  // this+7252〔pTarget7252〕
  *(this + 1814) = 0;  // this+7256〔pAuraObject〕
  *(this + 1815) = 0;  // this+7260 = 0
  *(this + 1845) = 15;  // this+7380 = 15
  *(this + 1844) = 0;  // this+7376 = 0
  *((uint8_t *)this + 7360) = 0;
  sub_4A3450(this + 1816);  // 调 sub_4A3450
  v5 = sub_433B00();  // map 节点分配（0x1C）
  *(this + 1855) = v5;  // this+7420〔map7416End〕
  *((uint8_t *)v5 + 25) = 1;  // v5[25] = 1
  *(uint32_t *)(*(this + 1855) + 4) = *(this + 1855);  // this+7420〔map7416End〕
  *(uint32_t *)*(this + 1855) = *(this + 1855);  // this+7420〔map7416End〕
  *(uint32_t *)(*(this + 1855) + 8) = *(this + 1855);  // this+7420〔map7416End〕
  *(this + 1856) = 0;  // this+7424 = 0
  sub_4CE550(this + 1858);  // 调 sub_4CE550
  *(this + 1904) = 0;  // this+7616 = 0
  *(this + 1905) = 0;  // this+7620 = 0
  *(this + 1906) = 0;  // this+7624 = 0
  *(this + 1908) = 0;  // this+7632 = 0
  *(this + 1909) = 0;  // this+7636〔nPosWinY〕
  *(this + 1910) = 0;  // this+7640 = 0
  *(this + 1912) = 0;  // this+7648 = 0
  *(this + 1913) = 0;  // this+7652 = 0
  *(this + 1914) = 0;  // this+7656 = 0
  *(this + 1916) = 0;  // this+7664 = 0
  *(this + 1917) = 0;  // this+7668〔nSwitchGuardT〕
  *(this + 1918) = 0;  // this+7672〔f_1DF8〕
  *(this + 1920) = 0;  // this+7680 = 0
  *(this + 1921) = 0;  // this+7684 = 0
  *(this + 1922) = 0;  // this+7688〔f_1E08〕
  *(this + 1931) = 15;  // this+7724 = 15
  *(this + 1930) = 0;  // this+7720〔f_1E28〕
  *((uint8_t *)this + 7704) = 0;
  *(this + 1939) = 15;  // this+7756 = 15
  *(this + 1938) = 0;  // this+7752 = 0
  *((uint8_t *)this + 7736) = 0;
  *(this + 1970) = 15;  // this+7880 = 15
  *(this + 1969) = 0;  // this+7876 = 0
  *((uint8_t *)this + 7860) = 0;
  *(this + 1974) = 0;  // this+7896 = 0
  *(this + 1975) = 0;  // this+7900 = 0
  *(this + 1976) = 0;  // this+7904 = 0
  *(this + 1989) = 15;  // this+7956 = 15
  *(this + 1988) = 0;  // this+7952 = 0
  *((uint8_t *)this + 7936) = 0;
  sub_578F90(this + 2002);  // 物品说明请求（406D00）
  *((uint8_t *)this + 8092) = 0;
  *(this + 2022) = &vftbl_nengine__CNTimer;  // this+8088 = &vftbl_nengine__CNTimer
  *(this + 2024) = 0;  // this+8096 = 0
  *((uint8_t *)this + 8100) = 1;
  *((uint8_t *)this + 8102) = 0;
  *((uint8_t *)this + 8101) = 0;
  *(this + 2028) = 0;  // this+8112 = 0
  *(this + 2027) = 0;  // this+8108 = 0
  *(this + 2026) = 0;  // this+8104 = 0
  *(this + 2030) = 0;  // this+8120 = 0
  *(this + 2031) = 0;  // this+8124 = 0
  *(this + 2032) = 0;  // this+8128 = 0
  sub_4AEDD0(this);  // 调 sub_4AEDD0
  sub_4BA8A0(ArgList);  // 角色创建入口
  return this;
}



// ------------------------------------------------------------
// 0x5794A0 IRDCharacter__vmt424 —— IRDCharacter__vmt424 默认虚槽桩（11 行 return）
// ------------------------------------------------------------
char /*thiscall*/ IRDCharacter__vmt424(uint8_t *this, char pszArg2)  // 实现：IRDCharacter__vmt424 默认虚槽桩（11 行 return）
{
  *(this + 7510) = pszArg2;  // this+30040 = pszArg2
  return pszArg2;
}



// ------------------------------------------------------------
// 0x5794B0 IRDCharacter__vmt428 —— IRDCharacter__vmt428 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt428(uint8_t *this)  // 实现：IRDCharacter__vmt428 默认虚槽桩（10 行 return）
{
  return *(this + 7510);  // 返回 this + 30040 处指针
}



// ------------------------------------------------------------
// 0x5794F0 IRDCharacter__vmt45C —— IRDCharacter__vmt45C 默认虚槽桩（11 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt45C(uint32_t *this, int nArg2)  // 实现：IRDCharacter__vmt45C 默认虚槽桩（11 行 return）
{
  *(this + 1923) = nArg2;  // this+7692 = nArg2
  return nArg2;
}



// ------------------------------------------------------------
// 0x579500 IRDCharacter__vmt460 —— IRDCharacter__vmt460 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt460(uint32_t *this)  // 实现：IRDCharacter__vmt460 默认虚槽桩（10 行 return）
{
  return *(this + 1923);  // 返回成员 this+7692
}



// ------------------------------------------------------------
// 0x579530 IRDCharacter__vmt380 —— IRDCharacter__vmt380 默认虚槽桩（11 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt380(int *this, int nArg2, int nArg3)  // 实现：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
{
  IRDActiveObject__vmt380(this, nArg2, nArg3);
  return (*(int (/*thiscall*/ **)(int *))(*this + 1324))(this);  // 调虚槽 +1324：Olrek 卖油摊位交互：加载 RedRock.ptl/RedOilFlask.ptl（41…
}



// ------------------------------------------------------------
// 0x579560 IRDCharacter__vmt478 —— IRDCharacter__vmt478 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
char */*thiscall*/ IRDCharacter__vmt478(char *this)  // 实现：IRDCharacter__vmt478 默认虚槽桩（10 行 return）
{
  return this + 7416;  // this+7416〔map7416〕
}



// ------------------------------------------------------------
// 0x579570 IRDCharacter__vmt4A8 —— IRDCharacter__vmt4A8 默认虚槽桩（11 行 return）
// ------------------------------------------------------------
char /*thiscall*/ IRDCharacter__vmt4A8(uint8_t *this, char pszArg2)  // 实现：IRDCharacter__vmt4A8 默认虚槽桩（11 行 return）
{
  *(this + 7729) = pszArg2;  // this+30916 = pszArg2
  return pszArg2;
}



// ------------------------------------------------------------
// 0x579580 IRDCharacter__vmt4AC —— IRDCharacter__vmt4AC 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
char /*thiscall*/ IRDCharacter__vmt4AC(uint8_t *this)  // 实现：IRDCharacter__vmt4AC 默认虚槽桩（10 行 return）
{
  return *(this + 7729);  // 返回 this + 30916 处指针
}



// ------------------------------------------------------------
// 0x5795B0 IRDCharacter__vmt4BC —— IRDCharacter__vmt4BC 默认虚槽桩（11 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt4BC(uint32_t *this, int nArg2)  // 实现：IRDCharacter__vmt4BC 默认虚槽桩（11 行 return）
{
  *(this + 1878) = nArg2;  // this+7512 = nArg2
  return nArg2;
}



// ------------------------------------------------------------
// 0x5795C0 IRDCharacter__vmt4C0 —— IRDCharacter__vmt4C0 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt4C0(uint32_t *this)  // 实现：IRDCharacter__vmt4C0 默认虚槽桩（10 行 return）
{
  return *(this + 1878);  // 返回成员 this+7512
}



// ------------------------------------------------------------
// 0x5795D0 IRDCharacter__vmt4C4 —— IRDCharacter__vmt4C4 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt4C4(uint32_t *this)  // 实现：IRDCharacter__vmt4C4 默认虚槽桩（10 行 return）
{
  return *(this + 1878) + 61440;
}



// ------------------------------------------------------------
// 0x5795E0 IRDCharacter__vmt4CC —— IRDCharacter__vmt4CC 默认虚槽桩（11 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt4CC(uint32_t *this, int nArg2)  // 实现：IRDCharacter__vmt4CC 默认虚槽桩（11 行 return）
{
  *(this + 1940) = nArg2;  // this+7760 = nArg2
  return nArg2;
}



// ------------------------------------------------------------
// 0x5795F0 IRDCharacter__vmt4D4 —— IRDCharacter__vmt4D4 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
char /*thiscall*/ IRDCharacter__vmt4D4(uint8_t *this)  // 实现：IRDCharacter__vmt4D4 默认虚槽桩（10 行 return）
{
  return *(this + 7764);  // 返回 this + 31056 处指针
}



// ------------------------------------------------------------
// 0x579650 IRDCharacter__vmt510 —— IRDCharacter__vmt510 默认虚槽桩（19 行）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt510(void *this, int nArg2, int nArg3)  // 实现：IRDCharacter__vmt510 默认虚槽桩（19 行）
{
  int result; // eax
  int pThis_488; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    pThis_488 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1160))(this, nArg2);  // 调虚槽 +1160
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_488 + 4))(pThis_488, nArg3);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  }
  return result;
}



// ------------------------------------------------------------
// 0x579680 IRDCharacter__vmt47C —— IRDCharacter__vmt47C 默认虚槽桩（4F3360 物品数据查询）
// ------------------------------------------------------------
uint32_t */*thiscall*/ IRDCharacter__vmt47C(uint32_t *this)  // 实现：IRDCharacter__vmt47C 默认虚槽桩（4F3360 物品数据查询）
{
  uint32_t *pThis_73E; // esi
  uint32_t *result; // eax

  pThis_73E = this + 1854;
  sub_4F3360(*(void **)(*(this + 1855) + 4));  // this+7420〔map7416End〕
  *(uint32_t *)(pThis_73E[1] + 4) = pThis_73E[1];
  result = (uint32_t *)pThis_73E[1];
  pThis_73E[2] = 0;
  *result = result;  // *result 写入 result
  *(uint32_t *)(pThis_73E[1] + 8) = pThis_73E[1];
  return result;
}



// ------------------------------------------------------------
// 0x5796C0 IRDCharacter__vmt404 —— IRDCharacter__vmt404 默认虚槽桩（4014D0 字符串）
// ------------------------------------------------------------
uint32_t */*thiscall*/ IRDCharacter__vmt404(int this, int pArg2)  // 实现：IRDCharacter__vmt404 默认虚槽桩（4014D0 字符串）
{
  uint32_t *pThis_1BEC; // esi
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  pThis_1BEC = (uint32_t *)(this + 7148);  // this+7148〔nBigState〕
  *(uint32_t *)(this + 7148) = *(uint32_t *)pArg2;  // this+7148〔nBigState〕
  *(uint32_t *)(this + 7152) = *(uint32_t *)(pArg2 + 4);  // this+7152〔uChar7152〕
  *(uint8_t *)(this + 7156) = *(uint8_t *)(pArg2 + 8);  // this+7156〔bChar7156〕
  sub_4014D0((std::_String_base *)(this + 7160), pArg2 + 12, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  pThis_1BEC[10] = *(uint32_t *)(pArg2 + 40);  // pThis_1BEC[10] 写入 *(uint32_t *)(pArg2 + 40)
  pThis_1BEC[11] = *(uint32_t *)(pArg2 + 44);  // pThis_1BEC[11] 写入 *(uint32_t *)(pArg2 + 44)
  pThis_1BEC[12] = *(uint32_t *)(pArg2 + 48);  // pThis_1BEC[12] 写入 *(uint32_t *)(pArg2 + 48)
  pThis_1BEC[13] = *(uint32_t *)(pArg2 + 52);  // pThis_1BEC[13] 写入 *(uint32_t *)(pArg2 + 52)
  pThis_1BEC[14] = *(uint32_t *)(pArg2 + 56);  // pThis_1BEC[14] 写入 *(uint32_t *)(pArg2 + 56)
  pThis_1BEC[15] = *(uint32_t *)(pArg2 + 60);  // pThis_1BEC[15] 写入 *(uint32_t *)(pArg2 + 60)
  return pThis_1BEC;
}



// ------------------------------------------------------------
// 0x579730 sub_579730 —— IRDCharacter 构造主体（107 行：4B7110/4B4950 部件 + 578240 外观 + 4B5A50/4A4BD0 动画）
// ------------------------------------------------------------
int /*thiscall*/ sub_579730(int this)  // 实现：IRDCharacter 构造主体（107 行：4B7110/4B4950 部件 + 578240 外观 + 4B5A50/4A4BD0 动…
{
  int fld_1DC0; // eax
  int *v4; // [esp-Ch] [ebp-28h]
  int *fld_1CFC; // [esp-8h] [ebp-24h]
  int *v6[2]; // [esp+8h] [ebp-14h] BYREF
  int v7; // [esp+18h] [ebp-4h]

  v6[1] = (int *)this;  // v6[1] 写入 (int *)this
  *(uint32_t *)this = &vftbl_IRDCharacter;
  v7 = 17;
  sub_4B7110();  // 角色演出资源释放（宿主 +7428..+8172 大段槽清理）
  if ( *(uint32_t *)(this + 8120) != 0 )  // 若 *(uint32_t *)(this + 8120) != 0
    j__free(*(void **)(this + 8120));  // 调 j__free
  *(uint32_t *)(this + 8120) = 0;  // this+8120 = 0
  *(uint32_t *)(this + 8124) = 0;  // this+8124 = 0
  *(uint32_t *)(this + 8128) = 0;  // this+8128 = 0
  *(uint32_t *)(this + 8088) = &vftbl_nengine__IObject;  // this+8088 = &vftbl_nengine__IObject
  *(uint8_t *)(this + 8092) = 0;  // this+8092 = 0
  if ( *(uint32_t *)(this + 8048) >= 0x10u )  // 若 *(uint32_t *)(this + 8048) >= 0x10u
    j__free(*(void **)(this + 8028));  // 调 j__free
  *(uint32_t *)(this + 8048) = 15;  // this+8048 = 15
  *(uint32_t *)(this + 8044) = 0;  // this+8044 = 0
  *(uint8_t *)(this + 8028) = 0;  // this+8028 = 0
  if ( *(uint32_t *)(this + 7956) >= 0x10u )  // 若 *(uint32_t *)(this + 7956) >= 0x10u
    j__free(*(void **)(this + 7936));  // 调 j__free
  *(uint32_t *)(this + 7956) = 15;  // this+7956 = 15
  *(uint32_t *)(this + 7952) = 0;  // this+7952 = 0
  *(uint8_t *)(this + 7936) = 0;  // this+7936 = 0
  if ( *(uint32_t *)(this + 7896) != 0 )  // 若 *(uint32_t *)(this + 7896) != 0
    j__free(*(void **)(this + 7896));  // 调 j__free
  *(uint32_t *)(this + 7896) = 0;  // this+7896 = 0
  *(uint32_t *)(this + 7900) = 0;  // this+7900 = 0
  *(uint32_t *)(this + 7904) = 0;  // this+7904 = 0
  if ( *(uint32_t *)(this + 7880) >= 0x10u )  // 若 *(uint32_t *)(this + 7880) >= 0x10u
    j__free(*(void **)(this + 7860));  // 调 j__free
  *(uint32_t *)(this + 7880) = 15;  // this+7880 = 15
  *(uint32_t *)(this + 7876) = 0;  // this+7876 = 0
  *(uint8_t *)(this + 7860) = 0;  // this+7860 = 0
  if ( *(uint32_t *)(this + 7756) >= 0x10u )  // 若 *(uint32_t *)(this + 7756) >= 0x10u
    j__free(*(void **)(this + 7736));  // 调 j__free
  *(uint32_t *)(this + 7756) = 15;  // this+7756 = 15
  *(uint32_t *)(this + 7752) = 0;  // this+7752 = 0
  *(uint8_t *)(this + 7736) = 0;  // this+7736 = 0
  if ( *(uint32_t *)(this + 7724) >= 0x10u )  // 若 *(uint32_t *)(this + 7724) >= 0x10u
    j__free(*(void **)(this + 7704));  // 调 j__free
  *(uint32_t *)(this + 7724) = 15;  // this+7724 = 15
  *(uint32_t *)(this + 7720) = 0;  // this+7720〔f_1E28〕
  *(uint8_t *)(this + 7704) = 0;  // this+7704 = 0
  if ( *(uint32_t *)(this + 7680) != 0 )  // 若 *(uint32_t *)(this + 7680) != 0
    j__free(*(void **)(this + 7680));  // 调 j__free
  *(uint32_t *)(this + 7680) = 0;  // this+7680 = 0
  *(uint32_t *)(this + 7684) = 0;  // this+7684 = 0
  *(uint32_t *)(this + 7688) = 0;  // this+7688〔f_1E08〕
  if ( *(uint32_t *)(this + 7664) != 0 )  // 若 *(uint32_t *)(this + 7664) != 0
    j__free(*(void **)(this + 7664));  // 调 j__free
  *(uint32_t *)(this + 7664) = 0;  // this+7664 = 0
  *(uint32_t *)(this + 7668) = 0;  // this+7668〔nSwitchGuardT〕
  *(uint32_t *)(this + 7672) = 0;  // this+7672〔f_1DF8〕
  if ( *(uint32_t *)(this + 7648) != 0 )  // 若 *(uint32_t *)(this + 7648) != 0
    j__free(*(void **)(this + 7648));  // 调 j__free
  *(uint32_t *)(this + 7648) = 0;  // this+7648 = 0
  *(uint32_t *)(this + 7652) = 0;  // this+7652 = 0
  *(uint32_t *)(this + 7656) = 0;  // this+7656 = 0
  if ( *(uint32_t *)(this + 7632) != 0 )  // 若 *(uint32_t *)(this + 7632) != 0
    j__free(*(void **)(this + 7632));  // 调 j__free
  *(uint32_t *)(this + 7632) = 0;  // this+7632 = 0
  *(uint32_t *)(this + 7636) = 0;  // this+7636〔nPosWinY〕
  *(uint32_t *)(this + 7640) = 0;  // this+7640 = 0
  fld_1DC0 = *(uint32_t *)(this + 7616);  // fld_1DC0 = 读 this+7616
  LOBYTE(v7) = 4;
  if ( fld_1DC0 != 0 )  // 若 fld_1DC0 非 0
  {
    sub_4B4950(fld_1DC0, *(uint32_t *)(this + 7620));  // 16 字节记录数组析构（逐元素清 +4 向量后 free）
    j__free(*(void **)(this + 7616));  // 调 j__free
  }
  *(uint32_t *)(this + 7616) = 0;  // this+7616 = 0
  *(uint32_t *)(this + 7620) = 0;  // this+7620 = 0
  *(uint32_t *)(this + 7624) = 0;  // this+7624 = 0
  fld_1CFC = *(int **)(this + 7420);  // this+7420〔map7416End〕
  v4 = (int *)*fld_1CFC;
  LOBYTE(v7) = 3;
  sub_578240((int ***)(this + 7416), v6, v4, fld_1CFC);  // 堆叠物数量/外观计算（4F3360 物品数据 + 4B2BF0 表现，66 行）
  j__free(*(void **)(this + 7420));  // this+7420〔map7416End〕
  *(uint32_t *)(this + 7420) = 0;  // this+7420〔map7416End〕
  *(uint32_t *)(this + 7424) = 0;  // this+7424 = 0
  if ( *(uint32_t *)(this + 7380) >= 0x10u )  // 若 *(uint32_t *)(this + 7380) >= 0x10u
    j__free(*(void **)(this + 7360));  // 调 j__free
  *(uint32_t *)(this + 7380) = 15;  // this+7380 = 15
  *(uint32_t *)(this + 7376) = 0;  // this+7376 = 0
  *(uint8_t *)(this + 7360) = 0;  // this+7360 = 0
  LOBYTE(v7) = 1;
  sub_4B5A50(this + 7212);  // 帧对象数组析构（·0x42AF90 后 228 字节池回收）
  if ( *(uint32_t *)(this + 7184) >= 0x10u )  // 若 *(uint32_t *)(this + 7184) >= 0x10u
    j__free(*(void **)(this + 7164));  // 调 j__free
  *(uint32_t *)(this + 7184) = 15;  // this+7184 = 15
  *(uint32_t *)(this + 7180) = 0;  // this+7180 = 0
  *(uint8_t *)(this + 7164) = 0;  // this+7164 = 0
  v7 = -1;
  return sub_4A4BD0(this);  // 返回 调 sub_4A4BD0 返回值
}



// ------------------------------------------------------------
// 0x579A30 IRDCharacter__vmt0 —— IRDCharacter__vmt0 标量删除析构（转发 579730 系成员清理）
// ------------------------------------------------------------
void */*thiscall*/ IRDCharacter__vmt0(void *Block, char pszArg2)  // 实现：IRDCharacter__vmt0 标量删除析构（转发 579730 系成员清理）
{
  sub_579730((int)Block);  // IRDCharacter 构造主体（107 行：4B7110/4B4950 部件 + 578240 外观 + 4B5A50/4A4BD0 动画）
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x579A60 sub_579A60 —— 职业构造后段·剑士分支（579270 + 5EDDC0/5EEE40）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_579A60(uint32_t *this)  // 实现：职业构造后段·剑士分支（579270 + 5EDDC0/5EEE40）
{
  sub_579270(this, 0);  // 角色对象初始化（85 行：4A49B0/4A3450/433B00/4CE550/4BA8A0 部件与动画装配）
  *this = &vftbl_CNSwordman;  // *this 写入 &vftbl_CNSwordman
  sub_5EDDC0((int)this);  // 调 sub_5EDDC0
  sub_5EEE40(this);  // 调 sub_5EEE40
  return this;
}



// ------------------------------------------------------------
// 0x579AC0 CNSwordman__vmt0 —— CNSwordman__vmt0 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNSwordman__vmt0(void *Block, char pszArg2)  // 实现：CNSwordman__vmt0 标量删除析构
{
  sub_579AF0();  // CNSwordman 构造（5F0D40 + 579730 基类主体）
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x579AF0 sub_579AF0 —— CNSwordman 构造（5F0D40 + 579730 基类主体）
// ------------------------------------------------------------
int /*thiscall*/ sub_579AF0(uint32_t *this)  // 实现：CNSwordman 构造（5F0D40 + 579730 基类主体）
{
  *this = &vftbl_CNSwordman;  // *this 写入 &vftbl_CNSwordman
  sub_5F0D40((int)this);  // 调 sub_5F0D40
  return sub_579730((int)this);  // IRDCharacter 构造主体（107 行：4B7110/4B4950 部件 + 578240 外观 + 4B5A50/4A4BD0 动画）
}



// ------------------------------------------------------------
// 0x579B40 sub_579B40 —— 职业构造后段·格斗家分支（579270 + 5E44C0/5E5F30）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_579B40(uint32_t *this)  // 实现：职业构造后段·格斗家分支（579270 + 5E44C0/5E5F30）
{
  sub_579270(this, 1);  // 角色对象初始化（85 行：4A49B0/4A3450/433B00/4CE550/4BA8A0 部件与动画装配）
  *this = &vftbl_CNFighter;  // *this 写入 &vftbl_CNFighter
  *(this + 2105) = 0;  // this+8420〔pVecBegin〕
  *(this + 2106) = 0;  // this+8424〔pVecEnd〕
  *(this + 2107) = 0;  // this+8428 = 0
  sub_5E44C0((int)this);  // 调 sub_5E44C0
  sub_5E5F30(this);  // 调 sub_5E5F30
  return this;
}



// ------------------------------------------------------------
// 0x579BB0 sub_579BB0 —— 10 行小函数
// ------------------------------------------------------------
int /*thiscall*/ sub_579BB0(uint32_t *this)  // 实现：10 行小函数
{
  return *(this + 2075);  // 返回成员 this+8300
}



// ------------------------------------------------------------
// 0x579BD0 CNFighter__vmt0 —— CNFighter__vmt0 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNFighter__vmt0(void *Block, char pszArg2)  // 实现：CNFighter__vmt0 标量删除析构
{
  sub_579C00();  // CNFighter 构造（5E6C50 + 579730 基类主体）
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x579C00 sub_579C00 —— CNFighter 构造（5E6C50 + 579730 基类主体）
// ------------------------------------------------------------
int /*thiscall*/ sub_579C00(void **this)  // 实现：CNFighter 构造（5E6C50 + 579730 基类主体）
{
  *this = &vftbl_CNFighter;  // *this 写入 &vftbl_CNFighter
  sub_5E6C50((int)this);  // 调 sub_5E6C50
  if ( *(this + 2105) != nullptr )  // this+8420〔pVecBegin〕
    j__free(*(this + 2105));  // this+8420〔pVecBegin〕
  *(this + 2105) = nullptr;  // this+8420〔pVecBegin〕
  *(this + 2106) = nullptr;  // this+8424〔pVecEnd〕
  *(this + 2107) = nullptr;  // this+8428 = nullptr
  return sub_579730((int)this);  // IRDCharacter 构造主体（107 行：4B7110/4B4950 部件 + 578240 外观 + 4B5A50/4A4BD0 动画）
}



// ------------------------------------------------------------
// 0x579C80 sub_579C80 —— 职业构造后段·神枪手分支（579270 + 5790A0/425940/41A630/4C0430/4C3810）
// ------------------------------------------------------------
int /*thiscall*/ sub_579C80(int this)  // 实现：职业构造后段·神枪手分支（579270 + 5790A0/425940/41A630/4C0430/4C3810）
{
  sub_579270((uint32_t *)this, 2);  // 角色对象初始化（85 行：4A49B0/4A3450/433B00/4CE550/4BA8A0 部件与动画装配）
  *(uint32_t *)this = &vftbl_CNGunner;
  sub_5790A0((uint32_t *)(this + 8220));  // 角色对象辅助 2（41A630 + 4C1BA0）
  *(uint32_t *)(this + 8524) = sub_425940();  // 链表哨兵节点
  *(uint32_t *)(this + 8528) = 0;  // this+8528 = 0
  sub_41A630(this + 8544);  // this+8544〔nFxCtx〕
  *(uint32_t *)(this + 8544) = &vftbl_clong;  // this+8544〔nFxCtx〕
  sub_41A630(this + 8577);  // 调 sub_41A630
  *(uint32_t *)(this + 8577) = &vftbl_clong;  // this+8577 = &vftbl_clong
  *(uint8_t *)(this + 9492) = 0;  // this+9492 = 0
  *(uint32_t *)(this + 9488) = &vftbl_nengine__CNTimer;  // this+9488 = &vftbl_nengine__CNTimer
  *(uint32_t *)(this + 9496) = 0;  // this+9496 = 0
  *(uint8_t *)(this + 9500) = 1;  // this+9500 = 1
  *(uint8_t *)(this + 9502) = 0;  // this+9502 = 0
  *(uint8_t *)(this + 9501) = 0;  // this+9501 = 0
  *(uint32_t *)(this + 9512) = 0;  // this+9512 = 0
  *(uint32_t *)(this + 9508) = 0;  // this+9508 = 0
  *(uint32_t *)(this + 9504) = 0;  // this+9504 = 0
  sub_4C0430(this);  // 调 sub_4C0430
  sub_4C3810((uint32_t *)this);  // 调 sub_4C3810
  return this;
}



// ------------------------------------------------------------
// 0x579D70 CNGunner__vmt534 —— CNGunner__vmt534 默认虚槽桩
// ------------------------------------------------------------
int /*thiscall*/ CNGunner__vmt534(uint32_t *this)  // 实现：CNGunner__vmt534 默认虚槽桩
{
  return *(this + 2129);  // this+8516〔nItemCtx〕
}



// ------------------------------------------------------------
// 0x579D90 CNGunner__vmt0 —— CNGunner__vmt0 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNGunner__vmt0(void *Block, char pszArg2)  // 实现：CNGunner__vmt0 标量删除析构
{
  sub_579DC0();  // CNGunner 构造（4C4260/41A580/6569D0/578E90 + 579730 基类主体）
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x579DC0 sub_579DC0 —— CNGunner 构造（4C4260/41A580/6569D0/578E90 + 579730 基类主体）
// ------------------------------------------------------------
int /*thiscall*/ sub_579DC0(char *this)  // 实现：CNGunner 构造（4C4260/41A580/6569D0/578E90 + 579730 基类主体）
{
  *(uint32_t *)this = &vftbl_CNGunner;
  sub_4C4260();  // 调 sub_4C4260
  *((uint32_t *)this + 2372) = &vftbl_nengine__IObject;  // this+9488 = &vftbl_nengine__IObject
  *(this + 9492) = 0;  // this+37968 = 0
  sub_41A580(this + 8577);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 8544);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_6569D0(this + 8520);  // 调 sub_6569D0
  j__free(*((void **)this + 2131));  // 调 j__free
  *((uint32_t *)this + 2131) = 0;  // this+8524〔bMonCfgFlag〕
  sub_578E90((int)(this + 8220));  // 掉落物成员访问（41A580）
  return sub_579730((int)this);  // IRDCharacter 构造主体（107 行：4B7110/4B4950 部件 + 578240 外观 + 4B5A50/4A4BD0 动画）
}



// ------------------------------------------------------------
// 0x579E70 sub_579E70 —— 职业构造后段·魔法师分支（579270 + 5DA220/5DD470）
// ------------------------------------------------------------
int /*thiscall*/ sub_579E70(int this)  // 实现：职业构造后段·魔法师分支（579270 + 5DA220/5DD470）
{
  sub_579270((uint32_t *)this, 3);  // 角色对象初始化（85 行：4A49B0/4A3450/433B00/4CE550/4BA8A0 部件与动画装配）
  *(uint32_t *)this = &vftbl_CNMage;
  *(uint32_t *)(this + 8624) = 15;  // this+8624 = 15
  *(uint32_t *)(this + 8620) = 0;  // this+8620 = 0
  *(uint8_t *)(this + 8604) = 0;  // this+8604 = 0
  sub_5DA220(this);  // 邪眼相位大区复位（this+8216..8628，57 槽批量置初值）
  sub_5DD470(this);  // CNMage/白魔 WZ 构造后段资源装配（由·0x579E70 接·0x5DA220 之后调用）：
  return this;
}



// ------------------------------------------------------------
// 0x579EE0 CNMage__vmt0 —— CNMage__vmt0 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNMage__vmt0(void *Block, char pszArg2)  // 实现：CNMage__vmt0 标量删除析构
{
  sub_579F10();  // CNMage 构造（5DDCA0 + 579730 基类主体）
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x579F10 sub_579F10 —— CNMage 构造（5DDCA0 + 579730 基类主体）
// ------------------------------------------------------------
int /*thiscall*/ sub_579F10(void **this)  // 实现：CNMage 构造（5DDCA0 + 579730 基类主体）
{
  *this = &vftbl_CNMage;  // *this 写入 &vftbl_CNMage
  sub_5DDCA0();  // CNMage 白魔字段块总析构（this+8232..8564 全槽清理，由·0x579F10 构造链对偶调用）：
  if ( (unsigned int)*(this + 2156) >= 0x10 )  // 若 (unsigned int)*(this + 2156) >= 0x10
    j__free(*(this + 2151));  // 调 j__free
  *(this + 2156) = (void *)15;  // this+8624 = (void *)15
  *(this + 2155) = nullptr;  // this+8620 = nullptr
  *((uint8_t *)this + 8604) = 0;
  return sub_579730((int)this);  // IRDCharacter 构造主体（107 行：4B7110/4B4950 部件 + 578240 外观 + 4B5A50/4A4BD0 动画）
}



// ------------------------------------------------------------
// 0x579F90 sub_579F90 —— 职业构造分发：调 579A60(剑士)/579B40(格斗)/579C80(枪手)/579E70(法师)——按职业 id 走对应后段
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_579F90(void *Block)  // 实现：按职业 id 走对应后段
{
  uint32_t *pMem; // eax
  uint32_t *result; // eax
  uint32_t *pMem2; // eax
  void *pMem3; // eax
  void *pMem4; // eax

  switch ( (unsigned int)Block )  // 按 (unsigned int)Block 分派
  {
    case 0u:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      pMem = operator new(0x2170u);  // new(8560 字节) 分配对象
      if ( pMem == nullptr )  // 若 pMem 为空
        goto LABEL_10;  // 跳转 LABEL_10
      result = sub_579A60(pMem);  // 职业构造后段·剑士分支（579270 + 5EDDC0/5EEE40）
      break;  // 跳出循环/分支
    case 1u:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      pMem2 = operator new(0x215Cu);  // new(8540 字节) 分配对象
      if ( pMem2 == nullptr )  // 若 pMem2 为空
        goto LABEL_10;  // 跳转 LABEL_10
      result = sub_579B40(pMem2);  // 职业构造后段·格斗家分支（579270 + 5E44C0/5E5F30）
      break;  // 跳出循环/分支
    case 2u:  // case 2 = ENUM_CMDPACKET_LOGIN
      pMem3 = operator new(0x2530u);  // new(9520 字节) 分配对象
      if ( pMem3 == nullptr )  // 若 pMem3 为空
        goto LABEL_10;  // 跳转 LABEL_10
      result = (uint32_t *)sub_579C80((int)pMem3);  // 职业构造后段·神枪手分支（579270 + 5790A0/425940/41A630/4C0430/4C3810）
      break;  // 跳出循环/分支
    case 3u:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      pMem4 = operator new(0x21B8u);  // new(8632 字节) 分配对象
      if ( pMem4 == nullptr )  // 若 pMem4 为空
        goto LABEL_10;  // 跳转 LABEL_10
      result = (uint32_t *)sub_579E70((int)pMem4);  // 职业构造后段·魔法师分支（579270 + 5DA220/5DD470）
      break;  // 跳出循环/分支
    default:  // 默认分支
LABEL_10:  // 标签 LABEL_10（跳转合流点）
      result = nullptr;  // result = 空指针
      break;  // 跳出循环/分支
  }
  return result;
}



// ============================================================
// 【分区 13】CBIniFile INI 解析与字符串辅助（0x57A0A0-0x57A8F0）
// 节点/键查找 0x57A1C0；取值 0x57A220；std::string 桩 0x57A2F0-0x57A4F0
// 构造/析构小桩（41A5E0/41A590/698F90/698FE0）；0x57A5C0=主更新辅助。
// ============================================================
// ------------------------------------------------------------
// 0x57A0A0 sub_57A0A0 —— CBIniFile 桩（12 行 return）
// ------------------------------------------------------------
CHAR */*thiscall*/ sub_57A0A0(CHAR *this, LPCSTR lpString2)  // CBIniFile 桩（12 行 return）
{
  *(uint32_t *)this = &vftbl_CBIniFile;
  lstrcpyA(this + 4, lpString2);
  return this;
}



// ------------------------------------------------------------
// 0x57A0D0 sub_57A0D0 —— CBIniFile 桩（10 行 return）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_57A0D0(const CHAR *this, LPCSTR lpszSection, LPCSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct)  // CBIniFile 桩（10 行 return）
{
  return WritePrivateProfileStructA(lpszSection, lpszKey, lpStruct, uSizeStruct, this + 4);  // 返回 调 WritePrivateProfileStructA
}



// ------------------------------------------------------------
// 0x57A100 sub_57A100 —— CBIniFile 桩（10 行 return）
// ------------------------------------------------------------
UINT /*thiscall*/ sub_57A100(const CHAR *this, LPCSTR lpAppName, LPCSTR lpKeyName, INT nDefault)  // CBIniFile 桩（10 行 return）
{
  return GetPrivateProfileIntA(lpAppName, lpKeyName, nDefault, this + 4);  // 返回 调 GetPrivateProfileIntA
}



// ------------------------------------------------------------
// 0x57A120 sub_57A120 —— CBIniFile 桩（10 行 return）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_57A120(const CHAR *this, LPCSTR lpszSection, LPCSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct)  // CBIniFile 桩（10 行 return）
{
  return GetPrivateProfileStructA(lpszSection, lpszKey, lpStruct, uSizeStruct, this + 4);  // 返回 调 GetPrivateProfileStructA
}



// ------------------------------------------------------------
// 0x57A150 CBIniFile__vmt0 —— CBIniFile__vmt0 析构（13 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CBIniFile__vmt0(uint32_t *Block, char pszArg2)  // 实现：CBIniFile__vmt0 析构（13 行）
{
  *Block = &vftbl_CBIniFile;  // *Block 写入 &vftbl_CBIniFile
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x57A180 sub_57A180 —— CBIniFile 桩（11 行 return）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_57A180(const CHAR *this, LPCSTR lpAppName, LPCSTR lpKeyName, int nArg4)  // CBIniFile 桩（11 行 return）
{
  sprintf(String, "%d", nArg4);  // 拼字符串
  return WritePrivateProfileStringA(lpAppName, lpKeyName, String, this + 4);  // 返回 调 WritePrivateProfileStringA
}



// ------------------------------------------------------------
// 0x57A1C0 sub_57A1C0 —— INI 节点/键查找（32 行：逐节比对）
// ------------------------------------------------------------
unsigned int sub_57A1C0()  // 【CRC32表初始化】
{
  unsigned int v0; // ecx
  unsigned int i; // edi
  int v2; // esi
  unsigned int *v3; // edx
  unsigned int result; // eax

  v0 = 1;
  dword_9B8E80[0] = 0;
  for ( i = 128; i != 0; i >>= 1 )  // 遍历循环
  {
    v2 = 8 * i;
    v3 = (unsigned int *)(4 * i + 10194560);
    v0 = ((v0 & 1) != 0 ? 0xEDB88320 : 0) ^ (v0 >> 1);
    result = 0;
    do  // do-while 循环体起点
    {
      *v3 = v0 ^ *(int *)((char *)dword_9B8E80 + result);  // *v3 写入 v0 ^ *(int *)((char *)dword_9B8E80 + result)
      result += v2;
      v3 = (unsigned int *)((char *)v3 + v2);
    }
    while ( result < 0x400 );  // 条件循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x57A220 sub_57A220 —— INI 取值（转发 57A1C0）
// ------------------------------------------------------------
int /*cdecl*/ sub_57A220(int nArg1, uint8_t *uArg2, int nArg3)  // 实现：INI 取值（转发 57A1C0）
{
  int nArg32; // esi
  unsigned int i; // eax

  if ( byte_9B9280 == 0 )  // 若 byte_9B9280 为 0
  {
    sub_57A1C0();  // 【CRC32表初始化】
    byte_9B9280 = 1;
  }
  nArg32 = nArg3;
  for ( i = ~nArg1; nArg32 != 0; --nArg32 )  // 遍历循环
    i = dword_9B8E80[(uint8_t)(i ^ *uArg2++)] ^ (i >> 8);
  return ~i;
}



// ------------------------------------------------------------
// 0x57A280 sub_57A280 —— INI/字符串小桩（15 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_57A280(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 实现：INI/字符串小桩（15 行）
{
  *this = nArg2;  // *this 写入 nArg2
  *(this + 1) = nArg3;  // this+4 = nArg3
  *(this + 2) = nArg4;  // this+8 = nArg4
  *(this + 3) = nArg5;  // this+12 = nArg5
  *(this + 4) = nArg6;  // this+16 = nArg6
  return this;
}



// ------------------------------------------------------------
// 0x57A2B0 sub_57A2B0 —— 字符串小桩（12 行 return）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A2B0(uint32_t *this, int nArg2)  // 实现：字符串小桩（12 行 return）
{
  *(this + 41) = nArg2;  // this+164 = nArg2
  *(this + 42) = 0;  // this+168 = 0
  return nArg2;
}



// ------------------------------------------------------------
// 0x57A2D0 sub_57A2D0 —— 字符串小桩（12 行 return）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A2D0(uint32_t *this, int nArg2, int nArg3)  // 实现：字符串小桩（12 行 return）
{
  *(this + 41) = nArg2;  // this+164 = nArg2
  *(this + 42) = nArg3;  // this+168 = nArg3
  return nArg2;
}



// ------------------------------------------------------------
// 0x57A2F0 sub_57A2F0 —— std::string 构造辅助（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A2F0(void *this)  // 实现：std::string 构造辅助（41A5E0/41A590）
{
  unsigned int pThis_78; // esi
  int pThis_782; // eax
  int v3; // edx

  pThis_78 = (unsigned int)this + 120;  // this+120〔pAnimObj〕
  pThis_782 = sub_41A5E0((unsigned int)this + 120);  // crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(pThis_78, v3, pThis_782 + 1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x57A310 sub_57A310 —— std::string 构造辅助 2（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A310(void *this)  // 实现：std::string 构造辅助 2（41A5E0/41A590）
{
  unsigned int pThis_86; // esi
  int pThis_862; // eax
  int v3; // edx

  pThis_86 = (unsigned int)this + 134;
  pThis_862 = sub_41A5E0((unsigned int)this + 134);  // crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(pThis_86, v3, pThis_862 + 1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x57A330 sub_57A330 —— 字符串小桩（699030）
// ------------------------------------------------------------
char /*thiscall*/ sub_57A330(void *this)  // 实现：字符串小桩（699030）
{
  return sub_699030((int)this + 164);  // 【clock_freeze(clk)】
}



// ------------------------------------------------------------
// 0x57A340 sub_57A340 —— std::string 析构辅助（698F90/698FE0）
// ------------------------------------------------------------
char /*thiscall*/ sub_57A340(void *this)  // 实现：std::string 析构辅助（698F90/698FE0）
{
  int pThis_A4; // esi

  pThis_A4 = (int)this + 164;
  sub_698F90((int)this + 164, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  return sub_698FE0(pThis_A4);  // 【clock_unfreeze(clk)】
}



// ------------------------------------------------------------
// 0x57A360 sub_57A360 —— 字符串辅助（578C40 掉落物理复用）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A360(int this)  // 实现：字符串辅助（578C40 掉落物理复用）
{
  int fld_3CC; // esi

  fld_3CC = *(uint32_t *)(this + 972);  // fld_3CC = 读 this+972
  sub_578C40((void ***)this, nullptr);  // 掉落物物理步进（42AF90/657740/42FCB0/498530/4924C0：重力/地面碰撞）
  return fld_3CC;
}



// ------------------------------------------------------------
// 0x57A380 sub_57A380 —— 13 行小函数
// ------------------------------------------------------------
char /*thiscall*/ sub_57A380(int this, int16_t uArg2)  // 实现：13 行小函数
{
  *(uint16_t *)(this + 4) = uArg2;  // this+4 = uArg2
  *(uint8_t *)(this + 36) = 0;  // this+36 = 0
  *(uint8_t *)(this + 64) = 0;  // this+64 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x57A3A0 sub_57A3A0 —— std::string 构造辅助 3（698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_57A3A0(uint8_t *this)  // 实现：std::string 构造辅助 3（698F90）
{
  int pThis_18; // ecx

  *(this + 36) = 1;  // this+144 = 1
  pThis_18 = (int)(this + 24);
  *(uint8_t *)(pThis_18 + 13) = 0;  // pThis_18+13 = 0
  *(uint8_t *)(pThis_18 + 14) = 0;  // pThis_18+14 = 0
  return sub_698F90(pThis_18, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x57A3C0 sub_57A3C0 —— 对象/控件辅助（47DC90/483D50）
// ------------------------------------------------------------
int /*stdcall*/ sub_57A3C0(int nArg1, int nArg2)  // 实现：对象/控件辅助（47DC90/483D50）
{
  int v2; // eax

  v2 = sub_47DC90(nArg2);  // v2 = 调 sub_47DC90 返回值
  return sub_483D50(nArg1, v2);  // 技能槽绑定（替换索引 nArg2 处对象，旧对象解引用）
}



// ------------------------------------------------------------
// 0x57A3F0 sub_57A3F0 —— std::string 构造辅助 4（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A3F0(void *this, int nArg2)  // 实现：std::string 构造辅助 4（41A5E0/41A590）
{
  unsigned int pThis_70; // esi
  int pThis_702; // eax
  int v4; // edx

  pThis_70 = (unsigned int)this + 112;  // this+112〔pHostComp112〕
  pThis_702 = sub_41A5E0((unsigned int)this + 112);  // crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(pThis_70, v4, nArg2 + pThis_702);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x57A410 sub_57A410 —— std::string 构造辅助 5（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A410(void *this, int nArg2)  // 实现：std::string 构造辅助 5（41A5E0/41A590）
{
  unsigned int pThis_7E; // esi
  int pThis_7E2; // eax
  int v4; // edx

  pThis_7E = (unsigned int)this + 126;  // this+126〔field_007E〕
  pThis_7E2 = sub_41A5E0((unsigned int)this + 126);  // crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(pThis_7E, v4, nArg2 + pThis_7E2);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x57A430 sub_57A430 —— std::string 构造辅助 6（698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_57A430(uint8_t *this, char pszArg2)  // 实现：std::string 构造辅助 6（698F90）
{
  int pThis_200; // ecx

  *(this + 524) = pszArg2;  // this+2096 = pszArg2
  pThis_200 = (int)(this + 512);  // this+512〔nAbilityId〕
  *(uint8_t *)(pThis_200 + 13) = 0;  // pThis_200+13 = 0
  *(uint8_t *)(pThis_200 + 14) = 0;  // pThis_200+14 = 0
  return sub_698F90(pThis_200, 1000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x57A460 sub_57A460 —— 11 行小函数
// ------------------------------------------------------------
int /*thiscall*/ sub_57A460(uint32_t *this, int nArg2)  // 实现：11 行小函数
{
  *(this + 306) += nArg2;  // this+1224〔field_04C8〕
  return nArg2;
}



// ------------------------------------------------------------
// 0x57A480 sub_57A480 —— 字符串辅助 7（41A5E0）
// ------------------------------------------------------------
double /*thiscall*/ sub_57A480(void *this)  // 实现：字符串辅助 7（41A5E0）
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this + 934));  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x57A4A0 sub_57A4A0 —— 辅助（4FBD90）
// ------------------------------------------------------------
int /*cdecl*/ sub_57A4A0(int nArg1, int nArg2, int nArg3)  // 实现：辅助（4FBD90）
{
  return sub_4FBD90(nArg1, nArg2, nArg3);  // 20 字节元素反向搬移（5 双字直拷）
}



// ------------------------------------------------------------
// 0x57A4C0 sub_57A4C0 —— 辅助（655A40）
// ------------------------------------------------------------
int /*stdcall*/ sub_57A4C0(int nArg1, int nArg2, int nArg3)  // 实现：辅助（655A40）
{
  sub_655A40(nArg1, nArg2, nArg3);  // 20 字节记录逐元素填充
  return nArg1 + 20 * nArg2;
}



// ------------------------------------------------------------
// 0x57A4F0 sub_57A4F0 —— 14 行小函数
// ------------------------------------------------------------
void /*thiscall*/ sub_57A4F0(int this)  // 实现：14 行小函数
{
  if ( *(uint32_t *)(this + 24) != 0 )  // 若 *(uint32_t *)(this + 24) != 0
    j__free(*(void **)(this + 24));  // 调 j__free
  *(uint32_t *)(this + 24) = 0;  // this+24 = 0
  *(uint32_t *)(this + 28) = 0;  // this+28 = 0
  *(uint32_t *)(this + 32) = 0;  // this+32 = 0
}



// ------------------------------------------------------------
// 0x57A520 sub_57A520 —— 文本组装（4015C0/401740）
// ------------------------------------------------------------
void /*noreturn*/ sub_57A520()  // 实现：文本组装（4015C0/401740）
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
  sub_401740(v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject = &std::out_of_range::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// ------------------------------------------------------------
// 0x57A590 sub_57A590 —— 转发 57A520
// ------------------------------------------------------------
int /*thiscall*/ sub_57A590(uint32_t *this, unsigned int uArg2)  // 实现：转发 57A520
{
  int pVecEnd_6; // edx

  pVecEnd_6 = *(this + 1);  // fld_e1 = this+1
  if ( pVecEnd_6 == 0 || (*(this + 2) - pVecEnd_6) >> 2 <= uArg2 )  // 若 fld_e1 == 0
    sub_57A520();  // 文本组装（4015C0/401740）
  return pVecEnd_6 + 4 * uArg2;
}



// ------------------------------------------------------------
// 0x57A5C0 sub_57A5C0 —— 主更新辅助（121 行：4735F0/4FBDE0/655A00/655A40/45E580）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A5C0(int *this, int pArg2, unsigned int uArg3, uint32_t *Block)  // 实现：主更新辅助（121 行：4735F0/4FBDE0/655A00/655A40/45E580）
{
  int v5; // edx
  int pVecEnd_15; // ebx
  int v7; // ecx
  int v8; // edx
  int result; // eax
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v14; // ecx
  int fld_e27; // eax
  int v16; // ebx
  int fld_e13; // eax
  unsigned int v18; // edi
  void *fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-48h]
  int fld_e25; // [esp-Ch] [ebp-3Ch]
  unsigned int fld_e24; // [esp-8h] [ebp-38h]
  int v25; // [esp+0h] [ebp-30h] BYREF
  uint32_t v26[6]; // [esp+Ch] [ebp-24h] BYREF
  int v27; // [esp+2Ch] [ebp-4h]
  int v28; // [esp+38h] [ebp+8h]
  int v29; // [esp+3Ch] [ebp+Ch]
  char *Blocka; // [esp+40h] [ebp+10h]
  void *Blockb; // [esp+40h] [ebp+10h]

  v5 = Block[1];  // v5 = 取 Block[1]
  pVecEnd_15 = *(this + 1);  // fld_e1 = this+1
  v26[0] = *Block;  // v26[0] 写入 *Block
  v7 = Block[2];  // v7 = 取 Block[2]
  v26[1] = v5;
  v8 = Block[3];  // v8 = 取 Block[3]
  result = Block[4];  // result = 取 Block[4]
  v26[5] = &v25;
  v26[2] = v7;
  v26[3] = v8;
  v26[4] = result;
  if ( pVecEnd_15 != 0 )  // 若 fld_e1 非 0
  {
    result = 1717986919 * (*(this + 3) - pVecEnd_15);
    fld_e3 = (*(this + 3) - pVecEnd_15) / 20;
  }
  else  // 否则分支
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( pVecEnd_15 != 0 )  // 若 fld_e1 非 0
      fld_e2 = (*(this + 2) - pVecEnd_15) / 20;
    else  // 否则分支
      fld_e2 = 0;
    if ( 214748364 - fld_e2 < uArg3 )  // 若 214748364 - fld_e2 < uArg3
      sub_4735F0(this);  // 调 sub_4735F0
    if ( pVecEnd_15 != 0 )  // 若 fld_e1 非 0
      fld_e22 = (*(this + 2) - pVecEnd_15) / 20;
    else  // 否则分支
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )  // 若 fld_e3 >= uArg3 + fld_e22
    {
      fld_e23 = (void *)*(this + 2);
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 20 >= uArg3 )  // 若 ((int)fld_e23 - pArg2) / 20 >= uArg3
      {
        v28 = (int)fld_e23 - 20 * uArg3;
        *(this + 2) = sub_4FBDE0(v28, fld_e23, fld_e23);  // 20 字节元素正向区间拷贝（逐槽空目标防御）
        sub_57A4A0(pArg2, v28, Blockb);  // 辅助（4FBD90）
        return sub_655A00(pArg2, pArg2 + 20 * uArg3, v26);  // 20 字节记录正向区间拷贝
      }
      else  // 否则分支
      {
        sub_4FBDE0(pArg2, fld_e23, pArg2 + 20 * uArg3);  // 20 字节元素正向区间拷贝（逐槽空目标防御）
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 20;
        fld_e25 = *(this + 2);  // fld_e25 = this+2
        v27 = 2;
        sub_57A4C0(fld_e25, fld_e24, v26);  // 辅助（655A40）
        fld_e26 = 20 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8 = fld_e26
        return sub_655A00(pArg2, fld_e26 - 20 * uArg3, v26);  // 20 字节记录正向区间拷贝
      }
    }
    else  // 否则分支
    {
      if ( 214748364 - (fld_e3 >> 1) >= fld_e3 )  // 若 214748364 - (fld_e3 >> 1) >= fld_e3
        v14 = (fld_e3 >> 1) + fld_e3;
      else  // 否则分支
        v14 = 0;
      if ( pVecEnd_15 != 0 )  // 若 fld_e1 非 0
        fld_e27 = (*(this + 2) - pVecEnd_15) / 20;
      else  // 否则分支
        fld_e27 = 0;
      if ( v14 < uArg3 + fld_e27 )  // 若 v14 < uArg3 + fld_e27
        v14 = uArg3 + sub_45E580(this);  // 容器计数（跨度 / 20）
      v16 = 20 * v14;
      Blocka = (char *)operator new(20 * v14);
      fld_e12 = *(this + 1);  // fld_e12 = this+1
      v27 = 0;
      v29 = sub_4FBDE0(fld_e12, pArg2, Blocka);  // 20 字节元素正向区间拷贝（逐槽空目标防御）
      sub_655A40(v29, uArg3, v26);  // 20 字节记录逐元素填充
      sub_4FBDE0(pArg2, *(this + 2), v29 + 20 * uArg3);  // 20 字节元素正向区间拷贝（逐槽空目标防御）
      fld_e13 = *(this + 1);  // fld_e13 = this+1
      if ( fld_e13 != 0 )  // 若 fld_e13 非 0
        fld_e13 = (*(this + 2) - fld_e13) / 20;
      v18 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )  // 若 *(this + 1) != 0
        j__free((void *)*(this + 1));  // 调 j__free
      *(this + 3) = (int)&Blocka[v16];  // this+12 = (int)&Blocka[v16]
      *(this + 2) = (int)&Blocka[20 * v18];  // this+8 = (int)&Blocka[20 * v18]
      *(this + 1) = (int)Blocka;  // this+4 = (int)Blocka
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x57A880 sub_57A880 —— 转发 57A5C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_57A880(int *this, uint32_t *uArg2, int nArg3, uint32_t *Block)  // 实现：转发 57A5C0
{
  int pVecEnd_6; // esi
  int v6; // esi

  pVecEnd_6 = *(this + 1);  // fld_e1 = this+1
  if ( pVecEnd_6 != 0 && (*(this + 2) - pVecEnd_6) / 20 != 0 )  // 若 pVecEnd_6 != 0
    v6 = (nArg3 - pVecEnd_6) / 20;
  else  // 否则分支
    v6 = 0;
  sub_57A5C0(this, nArg3, 1u, Block);  // 主更新辅助（121 行：4735F0/4FBDE0/655A00/655A40/45E580）
  *uArg2 = *(this + 1) + 20 * v6;  // *uArg2 写入 *(this + 1) + 20 * v6
  return uArg2;
}



// ------------------------------------------------------------
// 0x57A8F0 sub_57A8F0 —— 转发 57A880 + 655A40 收尾
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_57A8F0(int *this, uint32_t *Block)  // 实现：转发 57A880 + 655A40 收尾
{
  int pVecEnd_8; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  pVecEnd_8 = *(this + 1);  // fld_e1 = this+1
  if ( pVecEnd_8 != 0 )  // 若 fld_e1 非 0
    fld_e2 = (*(this + 2) - pVecEnd_8) / 20;
  else  // 否则分支
    fld_e2 = 0;
  if ( pVecEnd_8 == 0 || fld_e2 >= (*(this + 3) - pVecEnd_8) / 20 )  // 若 pVecEnd_8 == 0
    return sub_57A880(this, &Block, *(this + 2), Block);  // 转发 57A5C0
  fld_e22 = *(this + 2);  // fld_e22 = this+2
  result = (uint32_t *)sub_655A40(fld_e22, 1, Block);  // 20 字节记录逐元素填充
  *(this + 2) = fld_e22 + 20;  // this+8 = fld_e22 + 20
  return result;
}


