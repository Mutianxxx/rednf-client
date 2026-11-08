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
void /*thiscall*/ CNRDCommunityWindow__vmt0(int *this, int a2)
{
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // [esp+10h] [ebp+8h]

  IRDPopupWindow__vmt0(this, a2);
  if ( a2 == *(this + 2) )
  {
    v4 = *(uint32_t *)(a2 + 20);
    v8 = *(uint32_t *)(a2 + 24);
    v5 = sub_418DD0(165);
    if ( v5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v5 + 152))(v5, v4 + 6, v8 + 6, dword_79C0B0);
    v6 = sub_418DD0(*(this + 11) + 270);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v4 + 2, v8 + 33, dword_79C0B0);
    v7 = *(this + 11);
    if ( v7 != 0 )
    {
      if ( v7 == 1 )
        sub_56FB50(this, a2);
    }
    else
    {
      sub_56F890(this, a2);
    }
  }
}



// ------------------------------------------------------------
// 0x5702F0 sub_5702F0 —— 社区/技能窗公共辅助（70 行：控件遍历与状态复位）
// ------------------------------------------------------------
int /*thiscall*/ sub_5702F0(int this)
{
  int result; // eax

  *(uint32_t *)(this + 80) = 12;
  *(uint32_t *)(this + 88) = 1600;
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 61) = 0;
  *(uint8_t *)(this + 62) = 0;
  *(uint8_t *)(this + 63) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 76) = 6;
  *(uint32_t *)(this + 108) = dword_99FCCC;
  *(uint32_t *)(this + 88) = 170;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 64) = -16777216;
  *(uint8_t *)(this + 62) = 1;
  *(uint32_t *)(this + 128) = 6;
  *(uint8_t *)(this + 112) = 0;
  *(uint8_t *)(this + 113) = 0;
  *(uint8_t *)(this + 114) = 0;
  *(uint8_t *)(this + 115) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 132) = 12;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 1600;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 160) = dword_99FCCC;
  *(uint8_t *)(this + 114) = 1;
  *(uint32_t *)(this + 140) = 170;
  *(uint32_t *)(this + 124) = 2;
  *(uint32_t *)(this + 116) = -16777216;
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
  result = dword_99FCCC;
  *(uint32_t *)(this + 212) = dword_99FCCC;
  *(uint8_t *)(this + 166) = 1;
  *(uint32_t *)(this + 192) = 170;
  *(uint32_t *)(this + 176) = 1;
  *(uint32_t *)(this + 168) = -16777216;
  return result;
}



// ------------------------------------------------------------
// 0x570450 CNRDSkillInfoWindow__vmt10 —— CNRDSkillInfoWindow vmt10：打开时状态切换（44ABE0/44E850）
// ------------------------------------------------------------
int /*thiscall*/ CNRDSkillInfoWindow__vmt10(uint32_t *this)
{
  int result; // eax

  dword_9B88CC = 0;
  result = *(this + 4);
  *(uint32_t *)(*(uint32_t *)(result + 2500) + 60) = 255;
  return result;
}



// ------------------------------------------------------------
// 0x570470 sub_570470 —— 技能信息窗小辅助（13 行）
// ------------------------------------------------------------
bool /*thiscall*/ sub_570470(uint32_t *this)
{
  int v1; // eax

  v1 = *(this + 1);
  return v1 == 0 || (*(this + 2) - v1) / 12 == 0;
}



// ------------------------------------------------------------
// 0x5704A0 CNRDSkillInfoWindow__vmt0 —— CNRDSkillInfoWindow vmt0：主构造（59 行）
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDSkillInfoWindow__vmt0(int *this, int a2)
{
  unsigned int result; // eax
  LONG v4; // ecx
  LONG v5; // eax
  int v6; // eax
  int v7; // edi
  uint32_t *v8; // eax
  uint32_t *v9; // edx
  int v10; // [esp+8h] [ebp-8h]
  int v11; // [esp+Ch] [ebp-4h]
  unsigned int i; // [esp+18h] [ebp+8h]

  IRDPopupWindow__vmt0(this, a2);
  result = *(this + 2);
  if ( a2 == result )
  {
    v4 = *(uint32_t *)(result + 20);
    v5 = *(uint32_t *)(result + 24);
    if ( v4 < pt.x && v5 < pt.y && v4 + *(this + 9) > pt.x && v5 + *(this + 10) > pt.y )
      *(uint32_t *)(*(uint32_t *)(*(this + 4) + 2500) + 60) = 120;
    v6 = *(this + 2);
    v7 = 0;
    v10 = *(uint32_t *)(v6 + 20) + 7;
    v11 = *(uint32_t *)(v6 + 24) + 7;
    for ( i = 0; ; ++i )
    {
      result = *(this + 12);
      if ( result == 0 )
        break;
      result = (int)(*(this + 13) - result) / 40;
      if ( i >= result )
        break;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B0 + 72))(
        dword_79C0B0,
        *(uint32_t *)(v7 + *(this + 12) + 4));
      v8 = (uint32_t *)(*(this + 12) + v7);
      if ( v8[9] < 0x10u )
        v9 = v8 + 4;
      else
        v9 = (uint32_t *)v8[4];
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v10,
        v11 + 13 * *v8,
        v8[2],
        v9);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
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
int /*cdecl*/ sub_5705A0(int a1, uint32_t *a2)
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
// 0x570610 sub_570610 —— 文本行组装：4014D0 拼接（数值行）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_570610(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = a2;
  for ( i = a1; i != a2; i += 10 )
  {
    *i = *a3;
    i[1] = a3[1];
    i[2] = a3[2];
    sub_4014D0((std::_String_base *)(i + 3), a3 + 3, 0, -1);
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x570660 sub_570660 —— 文本行组装中层（转发 5705A0）
// ------------------------------------------------------------
int /*cdecl*/ sub_570660(uint32_t *a1, uint32_t *a2, int a3)
{
  int v4; // edi
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  v4 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v6[7] = 0;
  while ( a1 != a2 )
  {
    sub_5705A0(v4, a1);
    v4 += 40;
    a1 += 10;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x570710 sub_570710 —— 文本行组装中层 2（24 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_570710(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  int result; // eax
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  v3 = a1;
  v6[4] = v6;
  v6[3] = a1;
  v6[7] = 0;
  while ( a2 != 0 )
  {
    result = sub_5705A0(v3, a3);
    --a2;
    v3 += 40;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5707B0 sub_5707B0 —— 转发 570710（尾调用桩）
// ------------------------------------------------------------
int /*stdcall*/ sub_5707B0(int a1, int a2, uint32_t *a3)
{
  sub_570710(a1, a2, a3);
  return a1 + 40 * a2;
}



// ============================================================
// 【分区 3】技能信息窗绘制链（0x5707E0-0x571AF0）
// 文本构建主函数 0x5707E0（136 行）；部件构建 0x570CB0（184 行）；
// 打开/绘制主函数 CNRDSkillInfoWindow__vmtC 在 0x570FD0（431 行）。
// ============================================================
// ------------------------------------------------------------
// 0x5707E0 sub_5707E0 —— 技能信息窗文本构建主函数：558090 分隔符 + 572550/5721D0 属性行 + 55A010 尾串
// ------------------------------------------------------------
void /*thiscall*/ sub_5707E0(int *this, int a2, unsigned int a3, int *a4)
{
  int v4; // edx
  int v6; // ecx
  int v7; // ebx
  unsigned int v8; // ecx
  int v10; // eax
  int v11; // eax
  unsigned int v12; // ecx
  int v13; // eax
  char *v14; // ebx
  int v15; // ecx
  int v16; // eax
  unsigned int v17; // edi
  void *v18; // eax
  int v19; // ecx
  int v21; // edi
  int v22; // [esp-18h] [ebp-6Ch]
  int v23; // [esp-Ch] [ebp-60h]
  unsigned int v24; // [esp-8h] [ebp-5Ch]
  int v25; // [esp+0h] [ebp-54h] BYREF
  void *Block; // [esp+Ch] [ebp-48h]
  int *v27; // [esp+10h] [ebp-44h]
  char *v28; // [esp+14h] [ebp-40h]
  uint32_t v29[3]; // [esp+18h] [ebp-3Ch] BYREF
  char v30[4]; // [esp+24h] [ebp-30h] BYREF
  void *v31; // [esp+28h] [ebp-2Ch]
  int v32; // [esp+38h] [ebp-1Ch]
  unsigned int v33; // [esp+3Ch] [ebp-18h]
  int v34; // [esp+40h] [ebp-14h]
  int *v35; // [esp+44h] [ebp-10h]
  int v36; // [esp+50h] [ebp-4h]
  int v37; // [esp+5Ch] [ebp+8h]
  int v38; // [esp+60h] [ebp+Ch]
  int v39; // [esp+64h] [ebp+10h]

  v34 = dword_796E50;
  v4 = a4[1];
  v6 = *a4;
  v35 = &v25;
  v29[0] = v6;
  v29[2] = a4[2];
  v27 = this;
  v29[1] = v4;
  v33 = 15;
  v32 = 0;
  LOBYTE(v31) = 0;
  sub_4014D0((std::_String_base *)v30, a4 + 3, 0, -1);
  v7 = *(this + 1);
  v36 = 0;
  if ( v7 != 0 )
    v8 = (*(this + 3) - v7) / 40;
  else
    v8 = 0;
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v10 = (*(this + 2) - v7) / 40;
    else
      v10 = 0;
    if ( 107374182 - v10 < a3 )
      sub_558090(this);
    if ( v7 != 0 )
      v11 = (*(this + 2) - v7) / 40;
    else
      v11 = 0;
    if ( v8 >= a3 + v11 )
    {
      v19 = *(this + 2);
      v39 = v19;
      if ( (v19 - a2) / 40 >= a3 )
      {
        v37 = v19 - 40 * a3;
        *(this + 2) = sub_570660(v37, v19, v19);
        sub_572550(a2, v37, v39);
        sub_570610(a2, a2 + 40 * a3, v29);
      }
      else
      {
        sub_570660(a2, v19, a2 + 40 * a3);
        v24 = a3 - (*(this + 2) - a2) / 40;
        v23 = *(this + 2);
        LOBYTE(v36) = 3;
        sub_5707B0(v23, v24, v29);
        v21 = 40 * a3 + *(this + 2);
        *(this + 2) = v21;
        v36 = 0;
        sub_570610(a2, v21 - 40 * a3, v29);
      }
    }
    else
    {
      if ( 107374182 - (v8 >> 1) >= v8 )
        v12 = (v8 >> 1) + v8;
      else
        v12 = 0;
      if ( v7 != 0 )
        v13 = (*(this + 2) - v7) / 40;
      else
        v13 = 0;
      if ( v12 < a3 + v13 )
        v12 = a3 + sub_5721D0(this);
      v38 = 40 * v12;
      v14 = (char *)operator new(40 * v12);
      v22 = *(this + 1);
      Block = v14;
      v28 = v14;
      LOBYTE(v36) = 1;
      v28 = (char *)sub_570660(v22, a2, v14);
      sub_570710(v28, a3, v29);
      v15 = *(this + 2);
      v28 += 40 * a3;
      sub_570660(a2, v15, v28);
      v16 = *(this + 1);
      if ( v16 != 0 )
        v16 = (*(this + 2) - v16) / 40;
      v17 = v16 + a3;
      v18 = (void *)*(this + 1);
      if ( v18 != nullptr )
      {
        sub_55A010(v18, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v14[v38];
      *(this + 2) = (int)&v14[40 * v17];
      *(this + 1) = (int)v14;
    }
  }
  if ( v33 >= 0x10 )
    j__free(v31);
}


// ------------------------------------------------------------
// 0x570B10 sub_570B10 —— 绘制链中层（转发 5707E0 文本构建）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_570B10(int *this, uint32_t *a2, char *a3, int *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 40 != 0 )
    v6 = (int)&a3[-v5] / 40;
  else
    v6 = 0;
  sub_5707E0(this, a3, 1u, a4);
  *a2 = *(this + 1) + 40 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x570B80 sub_570B80 —— 绘制链中层 2（570B10 + 570710）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_570B80(int this, int *a2)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi
  uint32_t *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 40;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 40 )
    return sub_570B10((int *)this, &a2, *(char **)(this + 8), a2);
  v5 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_570710(v5, 1, a2);
  *(uint32_t *)(this + 8) = v5 + 40;
  return result;
}



// ------------------------------------------------------------
// 0x570C10 sub_570C10 —— 绘制链中层 3（4015C0 字符串 + 570B80）
// ------------------------------------------------------------
void /*thiscall*/ sub_570C10(void *this, int a2, void *Src, int a4, int a5)
{
  int v6[3]; // [esp+Ch] [ebp-38h] BYREF
  void *Block; // [esp+1Ch] [ebp-28h]
  int v8; // [esp+2Ch] [ebp-18h]
  unsigned int v9; // [esp+30h] [ebp-14h]
  int v10; // [esp+34h] [ebp-10h]
  int v11; // [esp+40h] [ebp-4h]

  v10 = dword_796E50;
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  v6[0] = a2;
  v6[2] = a5;
  v11 = 0;
  v6[1] = a4;
  sub_4015C0(Src, strlen((const char *)Src));
  sub_570B80((int)this + 44, v6);
  if ( v9 >= 0x10 )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x570CB0 sub_570CB0 —— 技能信息窗部件构建（184 行：416C40/406D00/4164C0 文本块装配）
// ------------------------------------------------------------
int /*cdecl*/ sub_570CB0(const char *a1, int a2, int a3)
{
  const char *v3; // ebx
  int v4; // esi
  int v5; // edi
  char v6; // al
  int16_t v7; // cx
  void **v8; // eax
  char *v9; // eax
  void **v10; // ecx
  void **v11; // eax
  void **v13; // eax
  char *v14; // eax
  void **v15; // ecx
  uint8_t v16[4]; // [esp+8h] [ebp-40h] BYREF
  int v17; // [esp+Ch] [ebp-3Ch]
  int v18; // [esp+10h] [ebp-38h]
  int16_t v19; // [esp+14h] [ebp-34h] BYREF
  char v20; // [esp+16h] [ebp-32h]
  int v21; // [esp+18h] [ebp-30h]
  uint8_t v22[4]; // [esp+1Ch] [ebp-2Ch] BYREF
  void *Block[4]; // [esp+20h] [ebp-28h] BYREF
  int v24; // [esp+30h] [ebp-18h]
  unsigned int v25; // [esp+34h] [ebp-14h]
  int v26; // [esp+38h] [ebp-10h]
  int v27; // [esp+44h] [ebp-4h]

  v3 = a1;
  v4 = 0;
  v26 = dword_796E50;
  if ( a1 == nullptr )
    return 0;
  --a2;
  v25 = 15;
  v24 = 0;
  LOBYTE(Block[0]) = 0;
  v27 = 0;
  v21 = 1;
  v17 = strlen(a1);
  v5 = 0;
  if ( v17 > 0 )
  {
    v18 = 1;
    do
    {
      v6 = v3[v5];
      if ( v6 < 0
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
        v7 = *(uint16_t *)&v3[v5];
        v20 = 0;
        v19 = v7;
        sub_4022F0((std::_String_base *)v22, &v19, strlen((const char *)&v19));
        ++v5;
        ++v18;
        ++v4;
      }
      else
      {
        if ( v6 == 10 || v18 < v17 && (v6 == 13 && v3[v5 + 1] == 10 || v6 == 92 && v3[v5 + 1] == 110) )
        {
          if ( a3 != 0 )
          {
            sub_5724C0();
            sub_416C40(v22);
            v11 = (void **)Block[0];
            if ( v25 < 0x10 )
              v11 = Block;
            v9 = (char *)v11 + v24;
            v10 = (void **)Block[0];
            if ( v25 < 0x10 )
              v10 = Block;
LABEL_70:
            sub_406D00(v16, v10, v9);
            v3 = a1;
          }
LABEL_71:
          v4 = 0;
          ++v21;
          goto LABEL_72;
        }
        sub_4164C0((std::_String_base *)v22, 1, v6);
      }
      if ( ++v4 >= a2 )
      {
        if ( a3 != 0 )
        {
          sub_5724C0();
          sub_416C40(v22);
          v8 = (void **)Block[0];
          if ( v25 < 0x10 )
            v8 = Block;
          v9 = (char *)v8 + v24;
          v10 = (void **)Block[0];
          if ( v25 < 0x10 )
            v10 = Block;
          goto LABEL_70;
        }
        goto LABEL_71;
      }
LABEL_72:
      ++v5;
      ++v18;
    }
    while ( v5 < v17 );
  }
  if ( v17 == 0 )
  {
    if ( v25 >= 0x10 )
      j__free(Block[0]);
    return 0;
  }
  if ( a3 != 0 )
  {
    if ( v24 != 0 )
    {
      sub_416C40(v22);
      v13 = (void **)Block[0];
      if ( v25 < 0x10 )
        v13 = Block;
      v14 = (char *)v13 + v24;
      v15 = (void **)Block[0];
      if ( v25 < 0x10 )
        v15 = Block;
      sub_406D00(&a1, v15, v14);
    }
    else
    {
      --v21;
    }
  }
  if ( v25 >= 0x10 )
    j__free(Block[0]);
  return v21;
}


// ------------------------------------------------------------
// 0x570FD0 CNRDSkillInfoWindow__vmtC —— CNRDSkillInfoWindow__vmtC 打开/绘制主函数（431 行：47DCC0 技能查询 + 570C10/570CB0 分支 + 4B1C40/47EA80/4C0360 状态）
// ------------------------------------------------------------
char /*thiscall*/ sub_570FD0(char *this, int a2, void *a3)
{
  int v5; // ebx
  int v6; // esi
  const char *v7; // eax
  const CHAR *v8; // eax
  int v9; // eax
  CHAR *v10; // eax
  int v11; // esi
  const CHAR *v12; // eax
  int v13; // eax
  const char *v14; // eax
  int v15; // esi
  const char *v16; // eax
  int v17; // eax
  const char *v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // esi
  const char *v22; // eax
  int v23; // eax
  CHAR *v24; // eax
  void *v25; // edx
  int v26; // eax
  int v27; // eax
  const char *v28; // eax
  int v29; // eax
  void *v30; // edx
  int v31; // eax
  int v32; // ecx
  int v33; // eax
  const char *v34; // eax
  int v35; // eax
  bool v36; // zf
  int v37; // eax
  void *v38; // eax
  void *v39; // eax
  int v40; // eax
  int v41; // esi
  void *v42; // eax
  int v43; // eax
  void *v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  const CHAR *v48; // eax
  int v49; // eax
  void *v50; // eax
  int v51; // eax
  int v52; // eax
  void *v53; // ebx
  int v54; // eax
  int v55; // esi
  void *v56; // eax
  int v57; // eax
  uint32_t *v58; // edx
  int v59; // eax
  int v60; // eax
  uint32_t *v61; // edx
  int v62; // [esp+0h] [ebp-248h]
  const char *v63; // [esp+4h] [ebp-244h]
  int v64; // [esp+4h] [ebp-244h]
  int v65; // [esp+4h] [ebp-244h]
  const CHAR *v66; // [esp+4h] [ebp-244h]
  int v67; // [esp+4h] [ebp-244h]
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
  int v83; // [esp+238h] [ebp-10h]
  int v84; // [esp+244h] [ebp-4h]
  int v85; // [esp+250h] [ebp+8h]
  char *v86; // [esp+254h] [ebp+Ch]
  char *v87; // [esp+254h] [ebp+Ch]

  v83 = dword_796E50;
  dword_9B88CC = a2;
  if ( a2 == 0 )
    return 0;
  dword_795374 = (int)a3;
  if ( dword_8F7C04 == 0 )
    return 0;
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 28))(this, 1);
  sub_55A050(this + 44);
  v79 = dword_9B88CC + 4;
  if ( dword_795374 == 3 || dword_795374 == 2 )
    v5 = sub_41A5E0(dword_9B88CC + 496) + 1;
  else
    v5 = sub_41A5E0(dword_9B88CC + 510);
  if ( v5 <= sub_47DCC0(dword_9B88CC) && v5 != 0 )
  {
    v85 = 170;
    Src = (void *)-3618616;
    if ( dword_795374 != 3 && dword_795374 != 2 )
    {
      v6 = sub_44ACC0(1);
      if ( sub_44ACC0(0) < v6 )
        Src = (void *)-12973;
    }
    v7 = sub_41ACF0((unsigned int **)(v79 + 16));
    sprintf(Buffer, "%s Lv %d", v7, v5);
    sub_570C10(0, Buffer, (int)(this + 60), (int)Src);
    v8 = sub_41ACF0((unsigned int **)(v79 + 16));
    v9 = sub_4883E0((int)(this + 60), (int)v8);
    if ( v9 > 170 )
      v85 = v9;
    v10 = (CHAR *)sub_41ACF0((unsigned int **)(v79 + 20));
    sub_570C10(1, v10, (int)(this + 60), (int)Src);
    v11 = 3;
    v12 = sub_41ACF0((unsigned int **)(v79 + 20));
    v13 = sub_4883E0((int)(this + 60), (int)v12);
    if ( v85 < v13 )
      v85 = v13;
    if ( dword_795374 == 2 )
    {
      v68 = sub_47DE90(v5);
      v14 = (const char *)sub_422E70(1144);
      sprintf(Buffer, v14, v68);
      sub_570C10(3, Buffer, (int)(this + 60), -1);
    }
    else
    {
      if ( dword_795374 != 3 )
        goto LABEL_24;
      v15 = dword_9B88CC + 4;
      v69 = *(uint32_t *)(v15 + 488) + sub_47DE90(v5);
      v16 = (const char *)sub_422E70(1145);
      sprintf(Buffer, v16, v69);
      sub_570C10(3, Buffer, (int)(this + 60), -1);
    }
    v11 = 4;
    v17 = sub_4883E0((int)(this + 60), (int)Buffer);
    if ( v85 < v17 )
      v85 = v17;
LABEL_24:
    v80 = sub_4B1C40((uint32_t *)dword_9B88CC, v5);
    if ( v80 <= 0 )
    {
      if ( *(uint32_t *)(v79 + 120) != 0 )
        v63 = (const char *)sub_422E70(1148);
      else
        v63 = (const char *)sub_422E70(1147);
      sprintf(Buffer, v63);
    }
    else
    {
      v18 = (const char *)sub_422E70(1146);
      sprintf(Buffer, v18, (double)v80 * 0.001);
    }
    sub_570C10(v11, Buffer, (int)(this + 60), -1);
    v19 = sub_4883E0((int)(this + 60), (int)Buffer);
    if ( v85 < v19 )
      v85 = v19;
    if ( v5 > 0 && (int)sub_47EA80(v5) > 0 )
    {
      v20 = sub_47EA80(v5);
      sprintf(Buffer, "MP %d", v20);
      if ( sub_4C0360((void *)dword_9B88CC) >= 1.0 )
        sub_570C10(v11, Buffer, (int)(this + 112), -1);
      else
        sub_570C10(v11, Buffer, (int)(this + 112), -12973);
    }
    v21 = v11 + 1;
    if ( (int)sub_47EAD0(v5) > 0 )
    {
      v80 = sub_47EAD0(v5);
      v22 = (const char *)sub_422E70(1149);
      sprintf(Buffer, v22, (double)v80 * 0.001);
      sub_570C10(v21++, Buffer, (int)(this + 60), -1);
    }
    v23 = *(uint32_t *)(v79 + 400);
    if ( v23 != 0 && *(uint32_t *)(v23 + 4) != 0 )
    {
      if ( (uint8_t)sub_461710(dword_9B88CC) == 0 || dword_795374 == 3 || dword_795374 == 2 )
      {
        v70 = -1;
        v64 = (int)(this + 60);
        v24 = (CHAR *)sub_41ACF0((unsigned int **)(v79 + 400));
      }
      else
      {
        v70 = -13487361;
        v64 = (int)(this + 60);
        v24 = (CHAR *)sub_422E70(1150);
      }
      sub_570C10(v21++, v24, v64, v70);
    }
    if ( (uint8_t)sub_570470(v79 + 324) == 0 )
    {
      v25 = *(void **)(v79 + 332);
      ++v21;
      Src = *(void **)(v79 + 328);
      if ( Src != v25 )
      {
        do
        {
          v80 = -346530;
          v72 = sub_41A5E0(dword_9B88CC + 510);
          v73 = *((uint32_t *)Src + 1)
              + (v72 - 1) * (*((uint32_t *)Src + 2) - *((uint32_t *)Src + 1)) / (sub_47DCC0(dword_9B88CC) - 1);
          v26 = sub_484E80((int *)dword_8F852C, *(uint32_t *)Src);
          if ( v26 == -1
            || (v26 >= *((uint32_t *)dword_8F852C + 2)
              ? (v27 = 0)
              : (v27 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v26)),
                (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v27 + 44))(v27) < v73) )
          {
            v80 = -13487361;
          }
          v65 = sub_4F2CE0(*(uint32_t *)Src);
          v28 = (const char *)sub_422E70(1151);
          sprintf(Buffer, v28, v65, v73);
          sub_570C10(v21++, Buffer, (int)(this + 60), v80);
          v29 = sub_4883E0((int)(this + 60), (int)Buffer);
          if ( v85 < v29 )
            v85 = v29;
          v30 = *(void **)(v79 + 332);
          Src = (char *)Src + 12;
        }
        while ( Src != v30 );
      }
    }
    if ( dword_795374 == 3 || dword_795374 == 2 )
    {
      v31 = *(uint32_t *)(v79 + 92);
      if ( v31 != 0 )
      {
        v32 = *(uint32_t *)(v79 + 96) - v31;
        if ( v32 / 14 > 0 )
        {
          ++v21;
          Src = nullptr;
          v80 = v32 / 14;
          do
          {
            v33 = sub_41A5E0((unsigned int)Src + *(uint32_t *)(v79 + 92));
            v74 = sub_47DC90(v33);
            if ( v74 != 0 )
            {
              v71 = sub_41A5E0((unsigned int)Src + *(uint32_t *)(v79 + 108));
              v66 = sub_41ACF0((unsigned int **)(v74 + 20));
              v34 = (const char *)sub_422E70(1152);
              sprintf(Buffer, v34, v66, v71);
              sub_570C10(v21++, Buffer, (int)(this + 60), -1);
              v35 = sub_4883E0((int)(this + 60), (int)Buffer);
              if ( v85 < v35 )
                v85 = v35;
            }
            v36 = v80 == 1;
            Src = (char *)Src + 14;
            --v80;
          }
          while ( !v36 );
        }
      }
    }
    if ( (uint8_t)sub_47F310(Buffer, v5) != 0 )
    {
      ++v21;
      Block = nullptr;
      v77 = 0;
      v78 = 0;
      v84 = 0;
      v37 = sub_570CB0(Buffer, 34, v75);
      if ( v37 > 0 )
      {
        Src = (char *)Block + 4;
        v80 = v37;
        do
        {
          v38 = Src;
          if ( *((uint32_t *)Src + 5) >= 0x10u )
            v38 = *(void **)Src;
          sub_570C10(v21++, v38, (int)(this + 60), -1);
          v39 = Src;
          if ( *((uint32_t *)Src + 5) >= 0x10u )
            v39 = *(void **)Src;
          v40 = sub_4883E0((int)(this + 60), (int)v39);
          if ( v85 < v40 )
            v85 = v40;
          v36 = v80 == 1;
          Src = (char *)Src + 28;
          --v80;
        }
        while ( !v36 );
      }
      v84 = -1;
      if ( Block != nullptr )
      {
        sub_4166A0((int)Block, v77);
        j__free(Block);
      }
    }
    if ( (dword_795374 == 3 || dword_795374 == 2) && v5 > 1 && (uint8_t)sub_47F310(Buffer, v5 - 1) != 0 )
    {
      v41 = v21 + 1;
      v42 = (void *)sub_422E70(1153);
      sub_570C10(v41, v42, (int)(this + 164), -1);
      v21 = v41 + 1;
      Block = nullptr;
      v77 = 0;
      v78 = 0;
      v84 = 1;
      v43 = sub_570CB0(Buffer, 34, v75);
      if ( v43 > 0 )
      {
        v86 = (char *)Block + 4;
        v80 = v43;
        do
        {
          v44 = v86;
          if ( *((uint32_t *)v86 + 5) >= 0x10u )
            v44 = *(void **)v86;
          sub_570C10(v21++, v44, (int)(this + 60), -1);
          if ( *((uint32_t *)v86 + 5) < 0x10u )
            v45 = (int)v86;
          else
            v45 = *(uint32_t *)v86;
          v46 = sub_4883E0((int)(this + 60), v45);
          if ( v85 < v46 )
            v85 = v46;
          v36 = v80 == 1;
          v86 += 28;
          --v80;
        }
        while ( !v36 );
      }
      v84 = -1;
      if ( Block != nullptr )
      {
        sub_4166A0((int)Block, v77);
        j__free(Block);
      }
    }
    v47 = *(uint32_t *)(v79 + 24);
    if ( v47 != 0 && *(uint32_t *)(v47 + 4) != 0 )
    {
      ++v21;
      Block = nullptr;
      v77 = 0;
      v78 = 0;
      v84 = 2;
      v48 = sub_41ACF0((unsigned int **)(v79 + 24));
      v49 = sub_570CB0(v48, 34, v75);
      if ( v49 > 0 )
      {
        v87 = (char *)Block + 4;
        v80 = v49;
        do
        {
          v50 = v87;
          if ( *((uint32_t *)v87 + 5) >= 0x10u )
            v50 = *(void **)v87;
          sub_570C10(v21++, v50, (int)(this + 60), -2302756);
          v51 = (int)v87;
          if ( *((uint32_t *)v87 + 5) >= 0x10u )
            v51 = *(uint32_t *)v87;
          v52 = sub_4883E0((int)(this + 60), v51);
          if ( v85 < v52 )
            v85 = v52;
          v36 = v80 == 1;
          v87 += 28;
          --v80;
        }
        while ( !v36 );
      }
      v84 = -1;
      if ( Block != nullptr )
      {
        v53 = Block;
        sub_4166A0((int)Block, v77);
        j__free(v53);
      }
    }
    if ( dword_795374 == 3 )
      goto LABEL_117;
    if ( dword_795374 == 2 )
      goto LABEL_117;
    v54 = *(uint32_t *)(dword_9B88CC + 392);
    if ( v54 == 0 || (*(uint32_t *)(dword_9B88CC + 396) - v54) / 44 == 0 )
      goto LABEL_117;
    if ( sub_41A5E0(dword_9B88CC + 558) != 0 )
    {
      v67 = (int)(this + 164);
      v62 = 1154;
    }
    else
    {
      if ( sub_41A5E0(dword_9B88CC + 558) != 0 )
      {
LABEL_117:
        v57 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 27) + 20))(*((uint32_t *)this + 27));
        v58 = *(uint32_t **)this;
        *((uint32_t *)this + 22) = v85;
        ((void (/*thiscall*/ *)(char *, int, int))v58[13])(this, v85, v21 * (v57 + 1));
        v59 = *((uint32_t *)this + 2);
        *(uint32_t *)(v59 + 28) = 0;
        *(uint32_t *)(v59 + 32) = 0;
        v60 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 56))(this);
        v61 = *(uint32_t **)this;
        *((uint32_t *)this + 9) = v60;
        *((uint32_t *)this + 10) = ((int (/*thiscall*/ *)(char *))v61[15])(this);
        return 1;
      }
      v67 = (int)(this + 164);
      v62 = 1155;
    }
    v55 = v21 + 1;
    v56 = (void *)sub_422E70(v62);
    sub_570C10(v55, v56, v67, -346530);
    v21 = v55 + 1;
    goto LABEL_117;
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
char */*cdecl*/ sub_571AF0(int a1)
{
  if ( a1 >= 100 )
    return sub_422E70(965);
  if ( a1 >= 30 )
    return sub_422E70(966);
  if ( a1 >= -29 )
    return sub_422E70(967);
  if ( a1 < -99 )
    return sub_422E70(969);
  return sub_422E70(968);
}



// ------------------------------------------------------------
// 0x571B80 sub_571B80 —— 物品属性文本组装（135 行：497120/4971B0/497150 属性枚举）
// ------------------------------------------------------------
int /*usercall*/ sub_571B80@<eax>(double a1@<st0>, int a2, float a3, int a4, char *Buffer)
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
  double v18; // [esp+0h] [ebp-18h]
  double v19; // [esp+4h] [ebp-14h]
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

  result = a2;
  switch ( a2 )
  {
    case 0:
      sub_497120(0, a4);
      v31 = (uint64_t)(a1 * 100.0);
      v20 = (double)(int)sub_4971B0(0, a4, 0) * 0.001;
      v18 = a3;
      v11 = sub_422E70(977);
      goto LABEL_10;
    case 1:
      v26 = (double)(int)sub_4971B0(1, a4, 0) * 0.001;
      v19 = a3;
      v6 = sub_422E70(971);
      goto LABEL_3;
    case 2:
      sub_497120(2, a4);
      v23 = (double)(int)sub_4971B0(2, a4, 0) * 0.001;
      v14 = sub_422E70(981);
      return sprintf(Buffer, v14, a3, v23, (unsigned int)(uint64_t)a1);
    case 3:
      v27 = (double)(int)sub_4971B0(3, a4, 0) * 0.001;
      v7 = sub_422E70(972);
      return sprintf(Buffer, v7, a3, v27);
    case 4:
      sub_497120(4, a4);
      v21 = (double)(int)sub_4971B0(4, a4, 0) * 0.001;
      v12 = sub_422E70(978);
      return sprintf(Buffer, v12, a3, v21, 100 - (unsigned int)(uint64_t)(a1 * 100.0));
    case 5:
      v28 = (double)(int)sub_4971B0(5, a4, 0) * 0.001;
      v8 = sub_422E70(973);
      return sprintf(Buffer, v8, a3, v28);
    case 6:
      sub_497120(6, a4);
      v24 = (double)(int)sub_4971B0(6, a4, 0) * 0.001;
      v15 = sub_422E70(983);
      return sprintf(Buffer, v15, a3, v24, (unsigned int)(uint64_t)a1);
    case 7:
      v32 = (uint64_t)sub_497150(7, a4);
      v25 = (double)(int)sub_4971B0(7, a4, 0) * 0.001;
      v16 = sub_422E70(984);
      return sprintf(Buffer, v16, a3, v25, v32);
    case 8:
      v29 = (double)(int)sub_4971B0(8, a4, 0) * 0.001;
      v9 = sub_422E70(975);
      return sprintf(Buffer, v9, a3, v29);
    case 9:
      sub_497120(9, a4);
      v31 = (uint64_t)a1;
      v20 = (double)(int)sub_4971B0(9, a4, 0) * 0.001;
      v18 = a3;
      v11 = sub_422E70(3001);
      goto LABEL_10;
    case 10:
    case 14:
      future_error_what = std::_Get_future_error_what(a2);
      v17 = sub_422E70(985);
      return sprintf(Buffer, v17, future_error_what);
    case 11:
      sub_497120(11, a4);
      v31 = (uint64_t)a1;
      v20 = (double)(int)sub_4971B0(11, a4, 0) * 0.001;
      v18 = a3;
      v11 = sub_422E70(982);
      goto LABEL_10;
    case 12:
      sub_497120(12, a4);
      v31 = (uint64_t)(a1 * 100.0);
      v20 = (double)(int)sub_4971B0(12, a4, 0) * 0.001;
      v18 = a3;
      v11 = sub_422E70(979);
LABEL_10:
      result = sprintf(Buffer, v11, v18, v20, v31);
      break;
    case 13:
      sub_497120(13, a4);
      v22 = (double)(int)sub_4971B0(13, a4, 0) * 0.001;
      v13 = sub_422E70(980);
      result = sprintf(Buffer, v13, a3, v22, (unsigned int)(uint64_t)(a1 * 100.0));
      break;
    case 15:
      v26 = (double)(int)sub_4971B0(15, a4, 0) * 0.001;
      v19 = a3;
      v6 = sub_422E70(974);
LABEL_3:
      result = sprintf(Buffer, v6, v19, v26);
      break;
    case 16:
      v30 = (double)(int)sub_4971B0(16, a4, 0) * 0.001;
      v10 = sub_422E70(976);
      result = sprintf(Buffer, v10, a3, v30);
      break;
    default:
      return result;
  }
  return result;
}


// ------------------------------------------------------------
// 0x572040 sub_572040 —— 物品信息窗数据准备（70 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_572040(int this)
{
  int result; // eax

  *(uint32_t *)(this + 72) = 12;
  *(uint32_t *)(this + 80) = 1600;
  *(uint8_t *)(this + 52) = 0;
  *(uint8_t *)(this + 53) = 0;
  *(uint8_t *)(this + 54) = 0;
  *(uint8_t *)(this + 55) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 68) = 6;
  *(uint32_t *)(this + 100) = dword_99FCCC;
  *(uint32_t *)(this + 80) = 170;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 56) = -16777216;
  *(uint8_t *)(this + 54) = 1;
  *(uint32_t *)(this + 120) = 6;
  *(uint8_t *)(this + 104) = 0;
  *(uint8_t *)(this + 105) = 0;
  *(uint8_t *)(this + 106) = 0;
  *(uint8_t *)(this + 107) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 124) = 12;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 1600;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint8_t *)(this + 106) = 1;
  *(uint32_t *)(this + 152) = dword_99FCCC;
  *(uint32_t *)(this + 132) = 170;
  *(uint32_t *)(this + 116) = 2;
  *(uint32_t *)(this + 108) = -16777216;
  *(uint8_t *)(this + 156) = 0;
  *(uint8_t *)(this + 157) = 0;
  *(uint8_t *)(this + 158) = 0;
  *(uint8_t *)(this + 159) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 6;
  *(uint32_t *)(this + 176) = 12;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 1600;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint8_t *)(this + 158) = 1;
  result = dword_99FCCC;
  *(uint32_t *)(this + 204) = dword_99FCCC;
  *(uint32_t *)(this + 184) = 170;
  *(uint32_t *)(this + 168) = 1;
  *(uint32_t *)(this + 160) = -16777216;
  return result;
}



// ------------------------------------------------------------
// 0x5721B0 CNRDItemInfoWindow__vmt10 —— CNRDItemInfoWindow vmt10：打开状态切换（44ABE0/44E850）
// ------------------------------------------------------------
int /*thiscall*/ CNRDItemInfoWindow__vmt10(uint32_t *this)
{
  int result; // eax

  dword_9B88D0 = 0;
  result = *(this + 4);
  *(uint32_t *)(*(uint32_t *)(result + 2500) + 60) = 255;
  return result;
}



// ------------------------------------------------------------
// 0x5721D0 sub_5721D0 —— 物品信息窗小辅助（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_5721D0(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 40;
  return result;
}



// ------------------------------------------------------------
// 0x5721F0 CNRDItemInfoWindow__vmt0 —— CNRDItemInfoWindow vmt0：主构造（71 行）
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDItemInfoWindow__vmt0(int *this, int a2)
{
  unsigned int result; // eax
  LONG v4; // ecx
  int v5; // eax
  int v6; // esi
  int v7; // eax
  uint32_t *v8; // ebx
  int v9; // esi
  uint32_t *v10; // eax
  uint32_t *v11; // edx
  int v12; // [esp+8h] [ebp-Ch]
  int v13; // [esp+Ch] [ebp-8h]
  unsigned int i; // [esp+10h] [ebp-4h]
  int v15; // [esp+1Ch] [ebp+8h]

  IRDPopupWindow__vmt0(this, a2);
  result = *(this + 2);
  if ( a2 == result )
  {
    v4 = *(uint32_t *)(result + 20);
    v5 = *(uint32_t *)(result + 24);
    v6 = pt.y + 30;
    if ( v4 < pt.x && v5 < v6 && v4 + *(this + 67) > pt.x && v5 + *(this + 68) > v6 )
      *(uint32_t *)(*(uint32_t *)(*(this + 4) + 2500) + 60) = 120;
    v13 = *(uint32_t *)(*(this + 2) + 24) + 7;
    v7 = 0;
    for ( i = 0; ; ++i )
    {
      v15 = v7;
      result = *(this + 10);
      if ( result == 0 )
        break;
      result = (int)(*(this + 11) - result) / 40;
      if ( i >= result )
        break;
      v8 = (uint32_t *)(v15 + *(this + 10));
      if ( *v8 / 36 != 0 )
      {
        v9 = v13 + 13 * (*v8 % 36 + 3);
        v12 = 180 * (*v8 / 36) + *(uint32_t *)(*(this + 2) + 20) + 7;
      }
      else
      {
        v9 = v13 + 13 * *v8;
        v12 = *(uint32_t *)(*(this + 2) + 20) + 7;
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v8[1]);
      v10 = (uint32_t *)(v15 + *(this + 10));
      if ( v10[9] < 0x10u )
        v11 = v10 + 4;
      else
        v11 = (uint32_t *)v10[4];
      (*(void (/*cdecl*/ **)(int, int, int, uint32_t, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v12,
        v9,
        v10[2],
        v11);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v7 = v15 + 40;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x572360 sub_572360 —— 物品信息文本行辅助（4015C0/4021F0/4014D0）
// ------------------------------------------------------------
int /*cdecl*/ sub_572360(int a1, void *Src, int a3)
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
  sub_4015C0(Src, strlen((const char *)Src));
  v10 = 0;
  v3 = sub_4021F0((std::_String_base *)v5, a3, 0, -1);
  *(uint32_t *)(a1 + 24) = 15;
  *(uint32_t *)(a1 + 20) = 0;
  *(uint8_t *)(a1 + 4) = 0;
  sub_4014D0((std::_String_base *)a1, v3, 0, -1);
  if ( v8 >= 0x10 )
    j__free(Block);
  return a1;
}



// ------------------------------------------------------------
// 0x572400 sub_572400 —— 文本行辅助（4014D0）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_572400(int a1, int a2, uint32_t *a3)
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
    v5 = *(uint32_t *)(v3 - 40);
    v3 -= 40;
    v4 -= 10;
    *v4 = v5;
    v4[1] = *(uint32_t *)(v3 + 4);
    v4[2] = *(uint32_t *)(v3 + 8);
    sub_4014D0((std::_String_base *)(v4 + 3), v3 + 12, 0, -1);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x572450 sub_572450 —— 文本行辅助 2（4014D0）
// ------------------------------------------------------------
int /*cdecl*/ sub_572450(int a1, uint32_t *a2)
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
// 0x5724C0 sub_5724C0 —— 字符串处理（4015C0）——信息窗共用
// ------------------------------------------------------------
unsigned int /*usercall*/ sub_5724C0@<eax>(int a1@<ebx>)
{
  unsigned int v1; // ecx
  const char *v2; // esi
  const char *v3; // eax
  const char *v4; // eax
  unsigned int result; // eax
  char *v6; // ecx

  v1 = *(uint32_t *)(a1 + 24);
  v2 = (const char *)(a1 + 4);
  if ( v1 < 0x10 )
    v3 = (const char *)(a1 + 4);
  else
    v3 = *(const char **)v2;
  if ( *v3 == 32 )
  {
    if ( v1 < 0x10 )
      v4 = (const char *)(a1 + 4);
    else
      v4 = *(const char **)v2;
    sub_4015C0((void *)(v4 + 1), strlen(v4 + 1));
  }
  result = *(uint32_t *)(a1 + 24);
  if ( result < 0x10 )
    v6 = (char *)(a1 + 4);
  else
    v6 = *(char **)v2;
  if ( *v6 == 23662 )
  {
    if ( result >= 0x10 )
      v2 = *(const char **)v2;
    return sub_4015C0((void *)(v2 + 1), strlen(v2 + 1));
  }
  return result;
}



// ------------------------------------------------------------
// 0x572550 sub_572550 —— 转发 572400
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_572550(int a1, int a2, uint32_t *a3)
{
  return sub_572400(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x572570 sub_572570 —— 转发 572450
// ------------------------------------------------------------
int /*cdecl*/ sub_572570(uint32_t *a1, uint32_t *a2, int a3)
{
  int v4; // edi
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  v4 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v6[7] = 0;
  while ( a1 != a2 )
  {
    sub_572450(v4, a1);
    v4 += 40;
    a1 += 10;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x572620 sub_572620 —— 转发 572450（第二挂点）
// ------------------------------------------------------------
int /*cdecl*/ sub_572620(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  int result; // eax
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  v3 = a1;
  v6[4] = v6;
  v6[3] = a1;
  v6[7] = 0;
  while ( a2 != 0 )
  {
    result = sub_572450(v3, a3);
    --a2;
    v3 += 40;
  }
  return result;
}



// ------------------------------------------------------------
// 0x5726C0 sub_5726C0 —— 转发 572620
// ------------------------------------------------------------
int /*stdcall*/ sub_5726C0(int a1, int a2, uint32_t *a3)
{
  sub_572620(a1, a2, a3);
  return a1 + 40 * a2;
}



// ------------------------------------------------------------
// 0x5726F0 sub_5726F0 —— 物品信息窗文本构建主函数（136 行，与 5707E0 同构：558090 分隔 + 572570/5726C0 行组装 + 55A010）
// ------------------------------------------------------------
void /*thiscall*/ sub_5726F0(int *this, int a2, unsigned int a3, int *a4)
{
  int v4; // edx
  int v6; // ecx
  int v7; // ebx
  unsigned int v8; // ecx
  int v10; // eax
  int v11; // eax
  unsigned int v12; // ecx
  int v13; // eax
  char *v14; // ebx
  int v15; // ecx
  int v16; // eax
  unsigned int v17; // edi
  void *v18; // eax
  int v19; // ecx
  int v21; // edi
  int v22; // [esp-18h] [ebp-6Ch]
  int v23; // [esp-Ch] [ebp-60h]
  unsigned int v24; // [esp-8h] [ebp-5Ch]
  int v25; // [esp+0h] [ebp-54h] BYREF
  void *Block; // [esp+Ch] [ebp-48h]
  int *v27; // [esp+10h] [ebp-44h]
  char *v28; // [esp+14h] [ebp-40h]
  uint32_t v29[3]; // [esp+18h] [ebp-3Ch] BYREF
  char v30[4]; // [esp+24h] [ebp-30h] BYREF
  void *v31; // [esp+28h] [ebp-2Ch]
  int v32; // [esp+38h] [ebp-1Ch]
  unsigned int v33; // [esp+3Ch] [ebp-18h]
  int v34; // [esp+40h] [ebp-14h]
  int *v35; // [esp+44h] [ebp-10h]
  int v36; // [esp+50h] [ebp-4h]
  int v37; // [esp+5Ch] [ebp+8h]
  int v38; // [esp+60h] [ebp+Ch]
  int v39; // [esp+64h] [ebp+10h]

  v34 = dword_796E50;
  v4 = a4[1];
  v6 = *a4;
  v35 = &v25;
  v29[0] = v6;
  v29[2] = a4[2];
  v27 = this;
  v29[1] = v4;
  v33 = 15;
  v32 = 0;
  LOBYTE(v31) = 0;
  sub_4014D0((std::_String_base *)v30, a4 + 3, 0, -1);
  v7 = *(this + 1);
  v36 = 0;
  if ( v7 != 0 )
    v8 = (*(this + 3) - v7) / 40;
  else
    v8 = 0;
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v10 = (*(this + 2) - v7) / 40;
    else
      v10 = 0;
    if ( 107374182 - v10 < a3 )
      sub_558090(this);
    if ( v7 != 0 )
      v11 = (*(this + 2) - v7) / 40;
    else
      v11 = 0;
    if ( v8 >= a3 + v11 )
    {
      v19 = *(this + 2);
      v39 = v19;
      if ( (v19 - a2) / 40 >= a3 )
      {
        v37 = v19 - 40 * a3;
        *(this + 2) = sub_572570(v37, v19, v19);
        sub_572550(a2, v37, v39);
        sub_570610(a2, a2 + 40 * a3, v29);
      }
      else
      {
        sub_572570(a2, v19, a2 + 40 * a3);
        v24 = a3 - (*(this + 2) - a2) / 40;
        v23 = *(this + 2);
        LOBYTE(v36) = 3;
        sub_5726C0(v23, v24, v29);
        v21 = 40 * a3 + *(this + 2);
        *(this + 2) = v21;
        v36 = 0;
        sub_570610(a2, v21 - 40 * a3, v29);
      }
    }
    else
    {
      if ( 107374182 - (v8 >> 1) >= v8 )
        v12 = (v8 >> 1) + v8;
      else
        v12 = 0;
      if ( v7 != 0 )
        v13 = (*(this + 2) - v7) / 40;
      else
        v13 = 0;
      if ( v12 < a3 + v13 )
        v12 = a3 + sub_5721D0(this);
      v38 = 40 * v12;
      v14 = (char *)operator new(40 * v12);
      v22 = *(this + 1);
      Block = v14;
      v28 = v14;
      LOBYTE(v36) = 1;
      v28 = (char *)sub_572570(v22, a2, v14);
      sub_572620(v28, a3, v29);
      v15 = *(this + 2);
      v28 += 40 * a3;
      sub_572570(a2, v15, v28);
      v16 = *(this + 1);
      if ( v16 != 0 )
        v16 = (*(this + 2) - v16) / 40;
      v17 = v16 + a3;
      v18 = (void *)*(this + 1);
      if ( v18 != nullptr )
      {
        sub_55A010(v18, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v14[v38];
      *(this + 2) = (int)&v14[40 * v17];
      *(this + 1) = (int)v14;
    }
  }
  if ( v33 >= 0x10 )
    j__free(v31);
}


// ------------------------------------------------------------
// 0x572A20 sub_572A20 —— 绘制链中层（转发 5726F0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_572A20(int *this, uint32_t *a2, char *a3, int *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 40 != 0 )
    v6 = (int)&a3[-v5] / 40;
  else
    v6 = 0;
  sub_5726F0(this, a3, 1u, a4);
  *a2 = *(this + 1) + 40 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x572A90 sub_572A90 —— 绘制链中层 2（572A20 + 572620）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_572A90(int this, int *a2)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi
  uint32_t *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 40;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 40 )
    return sub_572A20((int *)this, &a2, *(char **)(this + 8), a2);
  v5 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_572620(v5, 1, a2);
  *(uint32_t *)(this + 8) = v5 + 40;
  return result;
}



// ------------------------------------------------------------
// 0x572B20 sub_572B20 —— 绘制链中层 3（4015C0 + 572A90）
// ------------------------------------------------------------
void /*thiscall*/ sub_572B20(void *this, int a2, void *Src, int a4, int a5)
{
  int v6[3]; // [esp+Ch] [ebp-38h] BYREF
  void *Block; // [esp+1Ch] [ebp-28h]
  int v8; // [esp+2Ch] [ebp-18h]
  unsigned int v9; // [esp+30h] [ebp-14h]
  int v10; // [esp+34h] [ebp-10h]
  int v11; // [esp+40h] [ebp-4h]

  v10 = dword_796E50;
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  v6[0] = a2;
  v6[2] = a5;
  v11 = 0;
  v6[1] = a4;
  sub_4015C0(Src, strlen((const char *)Src));
  sub_572A90((int)this + 36, v6);
  if ( v9 >= 0x10 )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x572BC0 sub_572BC0 —— 物品信息窗部件构建（186 行：416C40/406D00/4164C0 文本块装配）
// ------------------------------------------------------------
int /*cdecl*/ sub_572BC0(const char *a1, int a2, int a3)
{
  int v3; // esi
  int v5; // ebx
  int v6; // edi
  char v7; // al
  int16_t v8; // cx
  void **v9; // eax
  unsigned int v10; // eax
  void **v11; // ecx
  void **v12; // ecx
  unsigned int v13; // ecx
  void **v14; // eax
  void **v15; // eax
  unsigned int v16; // eax
  void **v17; // ecx
  int v18; // [esp+4h] [ebp-3Ch] BYREF
  int v19; // [esp+8h] [ebp-38h]
  int16_t v20; // [esp+Ch] [ebp-34h] BYREF
  char v21; // [esp+Eh] [ebp-32h]
  int v22; // [esp+10h] [ebp-30h]
  size_t v23; // [esp+14h] [ebp-2Ch] BYREF
  void *Block[4]; // [esp+18h] [ebp-28h] BYREF
  int v25; // [esp+28h] [ebp-18h]
  unsigned int v26; // [esp+2Ch] [ebp-14h]
  int v27; // [esp+30h] [ebp-10h]
  int v28; // [esp+3Ch] [ebp-4h]

  v27 = dword_796E50;
  v3 = 0;
  if ( a1 == nullptr )
    return 0;
  --a2;
  v26 = 15;
  v25 = 0;
  LOBYTE(Block[0]) = 0;
  v28 = 0;
  v22 = 1;
  v5 = 0;
  v19 = strlen(a1);
  if ( v19 > 0 )
  {
    v6 = 1;
    do
    {
      v7 = a1[v3];
      if ( v7 < 0
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
        v8 = *(uint16_t *)&a1[v3];
        v21 = 0;
        v20 = v8;
        sub_4022F0((std::_String_base *)&v23, (int)&v20, (char *)&v20, strlen((const char *)&v20));
        ++v3;
        ++v6;
        ++v5;
      }
      else
      {
        if ( v7 == 10 || v6 < v19 && (v7 == 13 && a1[v3 + 1] == 10 || v7 == 92 && a1[v3 + 1] == 110) )
        {
          if ( a3 != 0 )
          {
            ++v3;
            ++v6;
            sub_5724C0();
            sub_416C40(a3, &v23);
            v12 = (void **)Block[0];
            if ( v26 < 0x10 )
              v12 = Block;
            v13 = (unsigned int)v12 + v25;
            v14 = (void **)Block[0];
            if ( v26 < 0x10 )
              v14 = Block;
            sub_406D00(&v23, &v18, (int)v14, v13);
          }
          goto LABEL_72;
        }
        sub_4164C0(&v23, 1u, v7);
      }
      if ( ++v5 >= a2 )
      {
        if ( a3 != 0 )
        {
          sub_5724C0();
          sub_416C40(a3, &v23);
          v9 = (void **)Block[0];
          if ( v26 < 0x10 )
            v9 = Block;
          v10 = (unsigned int)v9 + v25;
          v11 = (void **)Block[0];
          if ( v26 < 0x10 )
            v11 = Block;
          sub_406D00(&v23, &v18, (int)v11, v10);
        }
LABEL_72:
        v5 = 0;
        ++v22;
      }
      ++v3;
      ++v6;
    }
    while ( v3 < v19 );
  }
  if ( v19 != 0 )
  {
    if ( a3 != 0 )
    {
      if ( v25 != 0 )
      {
        sub_5724C0();
        sub_416C40(a3, &v23);
        v15 = (void **)Block[0];
        if ( v26 < 0x10 )
          v15 = Block;
        v16 = (unsigned int)v15 + v25;
        v17 = (void **)Block[0];
        if ( v26 < 0x10 )
          v17 = Block;
        sub_406D00(&v23, &a1, (int)v17, v16);
      }
      else
      {
        --v22;
      }
    }
    if ( v26 >= 0x10 )
      j__free(Block[0]);
    return v22;
  }
  else
  {
    if ( v26 >= 0x10 )
      j__free(Block[0]);
    return 0;
  }
}


// ------------------------------------------------------------
// 0x572EF0 sub_572EF0 —— 物品信息窗绘制主函数（725 行：497040 属性枚举 + 571B80/572BC0/572B20 分支 + 47E720 说明）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_572EF0(void *this, int a2, int a3, int *a4, int a5, int a6)
{
  int v8; // ebx
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
  int v75; // eax
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
  int v139; // [esp+ACh] [ebp-10h]
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

  v139 = dword_796E50;
  v8 = a3;
  if ( sub_41A5E0(a2 + 14) != 0 )
  {
    v9 = sub_41A5E0(a2 + 14);
    sprintf(Buffer, "HP MAX %+d", v9);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 630) != 0 )
  {
    v88 = (double)sub_41A5E0(a2 + 630) * 0.59999996;
    v10 = sub_422E70(1063);
    sprintf(Buffer, v10, v88);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 28) != 0 )
  {
    v11 = sub_41A5E0(a2 + 28);
    sprintf(Buffer, "MP MAX %+d", v11);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 644) != 0 )
  {
    v89 = (double)sub_41A5E0(a2 + 644) * 3.0;
    v12 = sub_422E70(1064);
    sprintf(Buffer, v12, v89);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(a2 + 658)) != 0.0 )
  {
    v90 = COERCE_FLOAT(sub_41A5E0(a2 + 658));
    v13 = sub_422E70(1065);
    sprintf(Buffer, v13, v90);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 112) != 0 )
  {
    if ( sub_41A5E0(a2 + 168) != 0 )
    {
      v142 = sub_41A5E0(a2 + 168);
      v136 = sub_41A5E0(a2 + 112);
      v137 = sub_41A5E0(a2 + 168);
      v84 = sub_41A5E0(a2 + 112);
      v14 = sub_422E70(1665);
      sprintf(Buffer, v14, v84, v136 - v137, v142);
    }
    else
    {
      v103 = sub_41A5E0(a2 + 112);
      v15 = sub_422E70(1066);
      sprintf(Buffer, v15, v103);
    }
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 224) != 0 )
  {
    v104 = sub_41A5E0(a2 + 224);
    v16 = sub_422E70(2041);
    sprintf(Buffer, v16, v104);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 126) != 0 )
  {
    if ( sub_41A5E0(a2 + 182) != 0 )
    {
      v143 = sub_41A5E0(a2 + 182);
      v137 = sub_41A5E0(a2 + 126);
      v136 = sub_41A5E0(a2 + 182);
      v85 = sub_41A5E0(a2 + 126);
      v17 = sub_422E70(1666);
      sprintf(Buffer, v17, v85, v137 - v136, v143);
    }
    else
    {
      v105 = sub_41A5E0(a2 + 126);
      v18 = sub_422E70(1067);
      sprintf(Buffer, v18, v105);
    }
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 238) != 0 )
  {
    v106 = sub_41A5E0(a2 + 238);
    v19 = sub_422E70(2043);
    sprintf(Buffer, v19, v106);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(a2 + 252)) != 0.0 )
  {
    v91 = COERCE_FLOAT(sub_41A5E0(a2 + 252));
    v20 = sub_422E70(2045);
    sprintf(Buffer, v20, v91);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 140) != 0 )
  {
    if ( sub_41A5E0(a2 + 196) != 0 )
    {
      v144 = sub_41A5E0(a2 + 196);
      v137 = sub_41A5E0(a2 + 140);
      v136 = sub_41A5E0(a2 + 196);
      v86 = sub_41A5E0(a2 + 140);
      v21 = sub_422E70(1667);
      sprintf(Buffer, v21, v86, v137 - v136, v144);
    }
    else
    {
      v107 = sub_41A5E0(a2 + 140);
      v22 = sub_422E70(1068);
      sprintf(Buffer, v22, v107);
    }
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 266) != 0 )
  {
    v108 = sub_41A5E0(a2 + 266);
    v23 = sub_422E70(2042);
    sprintf(Buffer, v23, v108);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 154) != 0 )
  {
    if ( sub_41A5E0(a2 + 210) != 0 )
    {
      v145 = sub_41A5E0(a2 + 210);
      v137 = sub_41A5E0(a2 + 154);
      v136 = sub_41A5E0(a2 + 210);
      v87 = sub_41A5E0(a2 + 154);
      v24 = sub_422E70(1668);
      sprintf(Buffer, v24, v87, v137 - v136, v145);
    }
    else
    {
      v109 = sub_41A5E0(a2 + 154);
      v25 = sub_422E70(1069);
      sprintf(Buffer, v25, v109);
    }
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 280) != 0 )
  {
    v110 = sub_41A5E0(a2 + 280);
    v26 = sub_422E70(2044);
    sprintf(Buffer, v26, v110);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  v27 = 0.0;
  if ( COERCE_FLOAT(sub_41A5E0(a2 + 294)) != 0.0 )
  {
    v27 = COERCE_FLOAT(sub_41A5E0(a2 + 294));
    v28 = sub_422E70(2046);
    sprintf(Buffer, v28, v27);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 42) != 0 )
  {
    v111 = sub_41A5E0(a2 + 42);
    v29 = sub_422E70(1070);
    sprintf(Buffer, v29, v111);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 56) != 0 )
  {
    v112 = sub_41A5E0(a2 + 56);
    v30 = sub_422E70(1071);
    sprintf(Buffer, v30, v112);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 70) != 0 )
  {
    v113 = sub_41A5E0(a2 + 70);
    v31 = sub_422E70(1072);
    sprintf(Buffer, v31, v113);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 98) != 0 )
  {
    v114 = sub_41A5E0(a2 + 98);
    v32 = sub_422E70(1073);
    sprintf(Buffer, v32, v114);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 686) != 0 && a6 != 8 )
  {
    v33 = sub_41A5E0(a2 + 686);
    v34 = a2 + 686;
    if ( v33 % 10 != 0 )
    {
      v146 = sub_41A5E0(v34);
      v92 = sub_41A5E0(a2 + 686) / 10;
      v36 = sub_422E70(1075);
      sprintf(Buffer, v36, v92, abs32(v146 % 10));
    }
    else
    {
      v115 = sub_41A5E0(v34) / 10;
      v35 = sub_422E70(1074);
      sprintf(Buffer, v35, v115);
    }
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 672) != 0 )
  {
    v37 = sub_41A5E0(a2 + 672);
    v38 = a2 + 672;
    if ( v37 % 10 != 0 )
    {
      v147 = sub_41A5E0(v38);
      v93 = sub_41A5E0(a2 + 672) / 10;
      v40 = sub_422E70(1077);
      sprintf(Buffer, v40, v93, abs32(v147 % 10));
    }
    else
    {
      v116 = sub_41A5E0(v38) / 10;
      v39 = sub_422E70(1076);
      sprintf(Buffer, v39, v116);
    }
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 700) != 0 )
  {
    v41 = sub_41A5E0(a2 + 700);
    v42 = a2 + 700;
    if ( v41 % 10 != 0 )
    {
      v148 = sub_41A5E0(v42);
      v94 = sub_41A5E0(a2 + 700) / 10;
      v44 = sub_422E70(1079);
      sprintf(Buffer, v44, v94, abs32(v148 % 10));
    }
    else
    {
      v117 = sub_41A5E0(v42) / 10;
      v43 = sub_422E70(1078);
      sprintf(Buffer, v43, v117);
    }
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 308) != 0 )
  {
    v118 = sub_41A5E0(a2 + 308);
    v45 = sub_422E70(1080);
    sprintf(Buffer, v45, v118);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 322) != 0 )
  {
    v119 = sub_41A5E0(a2 + 322);
    v46 = sub_422E70(1081);
    sprintf(Buffer, v46, v119);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 350) != 0 )
  {
    v120 = sub_41A5E0(a2 + 350);
    v47 = sub_422E70(1082);
    sprintf(Buffer, v47, v120);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 336) != 0 )
  {
    v121 = sub_41A5E0(a2 + 336);
    v48 = sub_422E70(1083);
    sprintf(Buffer, v48, v121);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 364) != 0 )
  {
    v122 = sub_41A5E0(a2 + 364);
    v49 = sub_422E70(1084);
    sprintf(Buffer, v49, v122);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  v153 = 0;
  v149 = a2 + 378;
  do
  {
    if ( sub_41A5E0(v149) != 0 )
    {
      v137 = sub_497040(v153);
      if ( v137 != 17 )
      {
        v123 = sub_41A5E0(v149);
        future_error_what = std::_Get_future_error_what(v137);
        v50 = sub_422E70(1085);
        sprintf(Buffer, v50, future_error_what, v123);
        sub_572B20(*a4, Buffer, (int)this + 52, a3);
        ++*a4;
      }
    }
    v51 = ++v153 < 16;
    v149 += 14;
  }
  while ( v51 );
  if ( sub_41A5E0(a2 + 602) != 0 )
  {
    v124 = sub_41A5E0(a2 + 602);
    v52 = sub_422E70(1086);
    sprintf(Buffer, v52, v124);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 546) != 0 )
  {
    v125 = sub_41A5E0(a2 + 546);
    v53 = sub_422E70(1087);
    sprintf(Buffer, v53, v125);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 560) != 0 )
  {
    v27 = (double)sub_41A5E0(a2 + 560) * 0.1;
    v54 = sub_422E70(1088);
    sprintf(Buffer, v54, v27);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 616) != 0 )
  {
    v55 = sub_41A5E0(a2 + 616);
    v136 = v55;
    if ( v55 != 0 )
    {
      v57 = v55 % 1000;
      v56 = v55 / 1000;
      v150 = v57;
      if ( v57 != 0 )
      {
        if ( v136 % 100 != 0 )
        {
          if ( v136 % 10 != 0 )
            sprintf(&byte_9B8994, "+%d.%03dkg", v56, abs32(v150));
          else
            sprintf(&byte_9B8994, "%+d.%02dkg", v56, abs32(v150 / 10));
        }
        else
        {
          sprintf(&byte_9B8994, "%+d.%dkg", v56, abs32(v150 / 100));
        }
      }
      else
      {
        sprintf(&byte_9B8994, "%+dkg", v56);
      }
      v55 = (int)&byte_9B8994;
    }
    v126 = v55;
    v58 = sub_422E70(1089);
    sprintf(Buffer, v58, v126);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 714) != 0 )
  {
    v127 = sub_41A5E0(a2 + 714);
    v59 = sub_422E70(1090);
    sprintf(Buffer, v59, v127);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 728) != 0 )
  {
    v128 = sub_41A5E0(a2 + 728);
    v60 = sub_422E70(1091);
    sprintf(Buffer, v60, v128);
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  v61 = *(uint32_t *)(a2 + 772);
  if ( v61 != 4 )
  {
    switch ( v61 )
    {
      case 0:
        v62 = sub_422E70(1092);
LABEL_112:
        sprintf(Buffer, v62);
        break;
      case 1:
        v96 = sub_422E70(1093);
        sprintf(Buffer, v96);
        break;
      case 3:
        v97 = sub_422E70(1094);
        sprintf(Buffer, v97);
        break;
      case 2:
        v62 = sub_422E70(1095);
        goto LABEL_112;
      default:
        break;
    }
    sub_572B20(*a4, Buffer, (int)this + 52, a3);
    ++*a4;
  }
  if ( *(uint32_t *)(a2 + 776) != 17 )
  {
    v151 = sub_41A5E0(a2 + 794);
    v63 = sub_41A5E0(a2 + 780);
    sub_571B80(v27, *(uint32_t *)(a2 + 776), *(float *)&v63, v151, Buffer);
    Block = nullptr;
    v134 = nullptr;
    v135 = 0;
    v140 = 0;
    v64 = sub_572BC0(Buffer, 34, v132);
    if ( v64 > 0 )
    {
      v65 = (char *)Block + 4;
      v152 = (char *)Block + 4;
      v154 = v64;
      while ( 1 )
      {
        if ( v65[5] >= 0x10u )
          v65 = (uint32_t *)*v65;
        sub_572B20(*a4, v65, (int)this + 52, a3);
        v66 = v154 == 1;
        ++*a4;
        v152 += 28;
        --v154;
        if ( v66 )
          break;
        v65 = v152;
      }
    }
    v140 = -1;
    if ( Block != nullptr )
    {
      if ( Block != v134 )
      {
        v67 = (char *)Block + 24;
        do
        {
          if ( *v67 >= 0x10u )
            j__free((void *)*(v67 - 5));
          v68 = v134;
          *v67 = 15;
          *(v67 - 1) = 0;
          *((uint8_t *)v67 - 20) = 0;
          v67 += 7;
        }
        while ( v67 - 6 != v68 );
        v8 = a3;
      }
      j__free(Block);
    }
  }
  if ( sub_41A5E0(a2 + 808) != 0 )
  {
    v129 = sub_41A5E0(a2 + 808);
    v69 = sub_422E70(1096);
    sprintf(Buffer, v69, v129);
    sub_572B20(*a4, Buffer, (int)this + 52, v8);
    ++*a4;
  }
  if ( sub_41A5E0(a2 + 822) != 0 )
  {
    v130 = sub_41A5E0(a2 + 822);
    v70 = sub_422E70(1097);
    sprintf(Buffer, v70, v130);
    sub_572B20(*a4, Buffer, (int)this + 52, v8);
    ++*a4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(a2 + 742)) != 0.0 )
  {
    v98 = COERCE_FLOAT(sub_41A5E0(a2 + 742));
    v71 = sub_422E70(2107);
    sprintf(Buffer, v71, v98);
    sub_572B20(*a4, Buffer, (int)this + 52, v8);
    ++*a4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(a2 + 756)) != 0.0 )
  {
    v99 = COERCE_FLOAT(sub_41A5E0(a2 + 756));
    v72 = sub_422E70(2108);
    sprintf(Buffer, v72, v99);
    sub_572B20(*a4, Buffer, (int)this + 52, v8);
    ++*a4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(a2 + 836)) != 0.0 )
  {
    v73 = COERCE_FLOAT(sub_41A5E0(a2 + 836));
    v74 = sub_422E70(1099);
    sprintf(Buffer, v74, v73);
    v75 = -5468241;
    if ( v73 <= 0.0 )
      v75 = v8;
    sub_572B20(*a4, Buffer, (int)this + 52, v75);
    ++*a4;
  }
  if ( *(uint8_t *)(a2 + 879) != 0 )
  {
    v76 = sub_422E70(1100);
    sub_572B20(*a4, v76, (int)this + 52, v8);
    ++*a4;
  }
  if ( *(uint8_t *)(a2 + 880) != 0 )
  {
    v77 = sub_422E70(1101);
    sub_572B20(*a4, v77, (int)this + 52, v8);
    ++*a4;
  }
  if ( *(uint8_t *)(a2 + 850) != 0 )
  {
    v78 = sub_422E70(1102);
    sub_572B20(*a4, v78, (int)this + 52, v8);
    ++*a4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(a2 + 851)) != 0.0 )
  {
    v100 = COERCE_FLOAT(sub_41A5E0(a2 + 851));
    v79 = sub_422E70(2105);
    sprintf(Buffer, v79, v100);
    sub_572B20(*a4, Buffer, (int)this + 52, v8);
    ++*a4;
  }
  if ( COERCE_FLOAT(sub_41A5E0(a2 + 865)) != 0.0 )
  {
    v101 = COERCE_FLOAT(sub_41A5E0(a2 + 865));
    v80 = sub_422E70(2106);
    sprintf(Buffer, v80, v101);
    sub_572B20(*a4, Buffer, (int)this + 52, v8);
    ++*a4;
  }
  result = *(uint32_t **)(a2 + 888);
  for ( i = result; i != *(uint32_t **)(a2 + 892); i += 8 )
  {
    v82 = sub_41A5E0((unsigned int)(i + 1));
    v137 = sub_47E720(*i, v82);
    if ( v137 != 0 )
    {
      v131 = sub_41A5E0((unsigned int)i + 18);
      v102 = sub_41ACF0(v137 + 20);
      v83 = sub_422E70(1103);
      sprintf(Buffer, v83, v102, v131);
      sub_572B20(*a4, Buffer, (int)this + 52, v8);
      ++*a4;
    }
    result = i + 8;
  }
  return result;
}


// ------------------------------------------------------------
// 0x5745B0 sub_5745B0 —— 物品信息窗完整绘制（1226 行·全文件最大：5486B0/541A30/542AB0 各类型说明 + 406D60/402410 文本 + 572EF0 收尾）
// ------------------------------------------------------------
char /*userpurge*/ sub_5745B0@<al>(int *a1@<ecx>, int a2@<edi>, void **a3)
{
  uint8_t *v5; // eax
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
  void **v27; // eax
  int v28; // eax
  void *v29; // eax
  const char *v30; // eax
  int (/*thiscall*/ **v31)(void **); // edx
  int v32; // eax
  void *v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // eax
  void *v37; // eax
  uint8_t *v38; // eax
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
  uint8_t *v89; // edi
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
  uint8_t *v125; // esi
  int v126; // edx
  int v127; // eax
  int v128; // eax
  int v129; // edi
  int v130; // ecx
  int v131; // eax
  int v132; // edi
  int v133; // eax
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
  int v144; // esi
  int v145; // eax
  bool v146; // zf
  int v147; // eax
  void *v148; // eax
  int *v149; // eax
  void *v150; // esi
  int v151; // eax
  void *v152; // eax
  void **v153; // eax
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
  int *v167; // esi
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
  int v212; // [esp+Ch] [ebp-19Ch]
  int v213; // [esp+Ch] [ebp-19Ch]
  int v214; // [esp+Ch] [ebp-19Ch]
  int v215; // [esp+Ch] [ebp-19Ch]
  int v216; // [esp+Ch] [ebp-19Ch]
  void *v217; // [esp+Ch] [ebp-19Ch]
  int v218; // [esp+Ch] [ebp-19Ch]
  char v219[4]; // [esp+18h] [ebp-190h] BYREF
  void *v220; // [esp+1Ch] [ebp-18Ch]
  unsigned int v221; // [esp+30h] [ebp-178h]
  int v222; // [esp+34h] [ebp-174h]
  int v223; // [esp+38h] [ebp-170h]
  int *v224; // [esp+3Ch] [ebp-16Ch]
  char v225; // [esp+43h] [ebp-165h]
  unsigned int v226; // [esp+44h] [ebp-164h]
  int v227; // [esp+48h] [ebp-160h]
  void *j; // [esp+4Ch] [ebp-15Ch]
  void *Src; // [esp+50h] [ebp-158h]
  uint8_t *v230; // [esp+54h] [ebp-154h]
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
  int v250; // [esp+198h] [ebp-10h]
  int v251; // [esp+1A4h] [ebp-4h]

  v250 = dword_796E50;
  v224 = a1;
  v223 = dword_8F7C04;
  if ( dword_8F7C04 == 0 )
    return 0;
  v212 = a2;
  v5 = __RTDynamicCast(a3, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
  v230 = v5;
  v233 = false;
  if ( v5 != nullptr )
    v233 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)v5 + 172))(v5, a2) <= 7;
  sub_55A050(a1 + 9);
  v227 = 170;
  v239 = 15;
  v238[4] = nullptr;
  LOBYTE(v238[0]) = 0;
  v6 = (int (/*thiscall*/ **)(void **, uint32_t))*a3;
  v251 = 0;
  v7 = (void *)v6[27](a3, v212);
  sub_4015C0(v7, strlen((const char *)v7));
  Src = v238;
  v8 = (*((int (/*thiscall*/ **)(void **))*a3 + 6))(a3);
  sub_572B20(0, v238, (int)(a1 + 13), v8);
  v9 = (void **)v238[0];
  if ( v239 < 0x10 )
    v9 = v238;
  v10 = sub_4883E0(a1 + 13, v9);
  if ( v10 > 170 )
    v227 = v10;
  v11 = (*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3);
  v12 = (void *)sub_41ACF0(v11 + 12);
  sub_4015C0(v12, strlen((const char *)v12));
  v13 = (void **)v238[0];
  if ( v239 < 0x10 )
    v13 = v238;
  v14 = (*((int (/*thiscall*/ **)(void **))*a3 + 6))(a3);
  sub_572B20(1, v13, (int)(a1 + 13), v14);
  v15 = (void **)v238[0];
  v16 = 3;
  if ( v239 < 0x10 )
    v15 = v238;
  v17 = sub_4883E0(a1 + 13, v15);
  if ( v227 < v17 )
    v227 = v17;
  v18 = *(uint32_t *)((*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3) + 56);
  Src = (void *)v18;
  if ( v18 != 0 )
  {
    v20 = v18 % 1000;
    v19 = v18 / 1000;
    v231 = v20;
    i = v19;
    if ( v20 != 0 )
    {
      if ( (int)Src % 100 != 0 )
      {
        if ( (int)Src % 10 != 0 )
          sprintf(byte_9B8994, "%d.%03dkg", i, abs32(v231));
        else
          sprintf(byte_9B8994, "%d.%02dkg", i, abs32(v231 / 10));
      }
      else
      {
        sprintf(byte_9B8994, "%d.%dkg", i, abs32(v231 / 100));
      }
    }
    else
    {
      sprintf(byte_9B8994, "%dkg", v19);
    }
    v21 = 0;
    do
    {
      v22 = byte_9B8994[v21];
      v236[v21++] = v22;
    }
    while ( v22 != 0 );
  }
  else
  {
    v236[0] = 0;
  }
  sub_572B20(3, v236, (int)(a1 + 13), -1);
  if ( dword_795378 != 4 && dword_795378 != 5 && dword_795378 != 9 )
  {
    if ( !v233 )
    {
      if ( (*((int (/*thiscall*/ **)(void **))*a3 + 24))(a3) != 0 )
      {
        sub_401710((char *)szPassword);
        v23 = (int (/*thiscall*/ **)(void **))*a3;
        LOBYTE(v251) = 5;
        v24 = v23[24](a3);
        v25 = (void *)sub_5486B0(v24);
        sub_406D60(v25);
        v26 = sub_422E70(424);
        sub_402410(v26);
        v27 = (void **)Block[0];
        if ( v243 < 0x10 )
          v27 = Block;
        sub_572B20(3, v27, (int)(a1 + 26), -1);
        LOBYTE(v251) = 0;
        sub_501490(&v240);
      }
      v16 = 4;
    }
    goto LABEL_50;
  }
  v249 = 15;
  v248 = nullptr;
  LOBYTE(v245) = 0;
  sub_4015C0((void *)szPassword, 0);
  LOBYTE(v251) = 1;
  if ( dword_795378 != 9 )
  {
    v31 = (int (/*thiscall*/ **)(void **))*a3;
    if ( v233 )
    {
      v213 = *(uint32_t *)(v31[4](a3) + 52);
      v197 = *(uint32_t *)((*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3) + 40);
      v189 = *(uint32_t *)((*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3) + 44);
      v32 = (*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3);
      v214 = sub_4F36B0(v219, *(uint32_t *)(v32 + 36), v189, v197, v213);
      LOBYTE(v251) = 2;
      v33 = (void *)sub_422E70(1031);
      v34 = sub_572360((int)&v240, v33, v214);
      LOBYTE(v251) = 3;
      sub_4014D0((std::_String_base *)v244, v34, 0, -1);
      if ( v243 >= 0x10 )
        j__free(Block[0]);
      v243 = 15;
      v242 = 0;
      LOBYTE(Block[0]) = 0;
      LOBYTE(v251) = 1;
      if ( v221 < 0x10 )
        goto LABEL_44;
    }
    else
    {
      v215 = *(uint32_t *)(v31[4](a3) + 52);
      v198 = *(uint32_t *)((*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3) + 40);
      v190 = *(uint32_t *)((*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3) + 44);
      v35 = (*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3);
      v36 = sub_4F36B0(v219, *(uint32_t *)(v35 + 36), v190, v198, v215);
      LOBYTE(v251) = 4;
      sub_4014D0((std::_String_base *)v244, v36, 0, -1);
      LOBYTE(v251) = 1;
      if ( v221 < 0x10 )
        goto LABEL_44;
    }
    j__free(v220);
    goto LABEL_44;
  }
  sub_541A30();
  v28 = sub_542AB0((char)a3);
  v29 = (void *)sub_5486B0(v28);
  sub_4015C0(v29, strlen((const char *)v29));
  v30 = (const char *)sub_422E70(424);
  sub_4022F0((std::_String_base *)v244, v30, strlen(v30));
LABEL_44:
  if ( v248 != nullptr )
  {
    v37 = v245;
    if ( v249 < 0x10 )
      v37 = &v245;
    sub_572B20(3, v37, (int)(a1 + 26), -1);
  }
  v16 = 4;
  LOBYTE(v251) = 0;
  if ( v249 >= 0x10 )
    j__free(v245);
LABEL_50:
  v38 = v230;
  if ( v230 != nullptr )
  {
    a1[65] = (int)v230;
    if ( *(uint32_t *)(*(int (**)(void))(*(uint32_t *)v38 + 172))() != 8 )
    {
      switch ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 172))(v230) )
      {
        case 9:
        case 0xF:
        case 0x10:
        case 0x11:
          goto LABEL_63;
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
        case 0xE:
          v50 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 172))(v230);
          v51 = sub_41A5E0(v50 + 4);
          sub_572B20(v16, *(&dword_9B8980 + v51), (int)(a1 + 13), -1);
LABEL_63:
          v191 = *(&dword_9B88D8 + *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 172))(v230));
          sub_572B20(v16, v191, (int)(a1 + 26), -1);
          goto LABEL_64;
        default:
          goto LABEL_65;
      }
    }
    *((uint8_t *)a1 + 264) = 1;
    i = 4;
    v231 = 0;
    while ( 1 )
    {
      v39 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 16))(v230);
      v40 = v231;
      if ( *(uint8_t *)(v39 + v231 + 60) != 0 )
        break;
      ++v231;
      if ( v40 + 1 >= 4 )
        goto LABEL_57;
    }
    i = v231;
LABEL_57:
    v41 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 172))(v230);
    v42 = sub_41A5E0(v41 + 4);
    sub_572B20(v16, *(&dword_9B8920 + 6 * i + v42), (int)(a1 + 13), -1);
    v43 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 172))(v230);
    sub_572B20(v16, *(&dword_9B88D8 + *v43), (int)(a1 + 26), -1);
    v44 = *(uint32_t *)v230;
    ++v16;
    if ( i == 2 )
    {
      v45 = (*(int (**)(void))(v44 + 176))();
      v46 = sub_41A5E0(v45 + 686);
      v216 = sub_571AF0(v46);
      v47 = (const char *)sub_422E70(1033);
    }
    else
    {
      v48 = (*(int (**)(void))(v44 + 176))();
      v49 = sub_41A5E0(v48 + 686);
      v216 = sub_571AF0(v49);
      v47 = (const char *)sub_422E70(1034);
    }
    sprintf(Buffer, v47, v216);
    sub_572B20(v16, Buffer, (int)(a1 + 13), -1);
LABEL_64:
    ++v16;
LABEL_65:
    v52 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 172))(v230);
    j = (void *)sub_41A5E0(v52 + 18);
    if ( j != nullptr )
    {
      v53 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 188))(v230);
      v54 = sub_41A5E0(v53 + 32);
      v217 = j;
      v199 = v54;
      v55 = (const char *)sub_422E70(1035);
      sprintf(Buffer, v55, v199, v217);
      v56 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 200))(v230);
      sub_572B20(v16, Buffer, (int)(a1 + 13), v56 != 0 ? -13487361 : -1);
    }
    if ( !v233 )
    {
      v57 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 16))(v230) + 28) - 1;
      if ( v57 != 0 )
      {
        v58 = v57 - 1;
        if ( v58 != 0 )
        {
          if ( v58 != 1 )
            goto LABEL_91;
          if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 16))(v230) + 32) == 1 )
          {
            v59 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 188))(v230);
            if ( sub_41A5E0(v59 + 46) != 0 )
            {
              v61 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 188))(v230);
              v218 = sub_41A5E0(v61 + 46);
              v62 = (const char *)sub_422E70(1701);
              sprintf(v235, v62, v218);
              sub_572B20(v16, v235, (int)(a1 + 26), -1);
              goto LABEL_91;
            }
            v200 = (int)(a1 + 26);
            v60 = (void *)sub_422E70(1038);
          }
          else
          {
            v200 = (int)(a1 + 26);
            v60 = (void *)sub_422E70(1039);
          }
        }
        else
        {
          v200 = (int)(a1 + 26);
          v60 = (void *)sub_422E70(1037);
        }
      }
      else
      {
        v200 = (int)(a1 + 26);
        v60 = (void *)sub_422E70(1036);
      }
      goto LABEL_90;
    }
  }
  else
  {
    Src = *a3;
    v63 = (*((int (/*thiscall*/ **)(void **))Src + 4))(a3);
    if ( (*((uint8_t (/*thiscall*/ **)(void **, uint32_t))Src + 15))(a3, *(uint32_t *)(v63 + 4)) == 0 )
    {
      v200 = (int)(a1 + 13);
      v60 = (void *)sub_422E70(1050);
LABEL_90:
      sub_572B20(v16, v60, v200, -1);
      goto LABEL_91;
    }
    switch ( *(uint32_t *)(*((int (/*thiscall*/ **)(void **))*a3 + 33))(a3) )
    {
      case 0:
        v64 = (void *)sub_422E70(1040);
        sub_572B20(v16, v64, (int)(a1 + 13), -1);
        v201 = (double)*(int *)((*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3) + 64) * 0.001;
        v65 = (const char *)sub_422E70(1041);
        goto LABEL_83;
      case 1:
        v200 = (int)(a1 + 13);
        v60 = (void *)sub_422E70(1046);
        goto LABEL_90;
      case 2:
        v200 = (int)(a1 + 13);
        v60 = (void *)sub_422E70(1047);
        goto LABEL_90;
      case 3:
        v66 = (void *)sub_422E70(1042);
        sub_572B20(v16, v66, (int)(a1 + 13), -1);
        v202 = (double)*(int *)((*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3) + 64) * 0.001;
        v67 = (const char *)sub_422E70(1043);
        sprintf(Buffer, v67, v202);
        sub_572B20(v16, Buffer, (int)(a1 + 26), -1);
        break;
      case 4:
        v68 = (void *)sub_422E70(1044);
        sub_572B20(v16, v68, (int)(a1 + 13), -1);
        v201 = (double)*(int *)((*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3) + 64) * 0.001;
        v65 = (const char *)sub_422E70(1045);
LABEL_83:
        sprintf(Buffer, v65, v201);
        sub_572B20(v16, Buffer, (int)(a1 + 26), -1);
        break;
      case 5:
        v200 = (int)(a1 + 13);
        v60 = (void *)sub_422E70(1048);
        goto LABEL_90;
      case 6:
        v200 = (int)(a1 + 13);
        v60 = (void *)sub_422E70(1049);
        goto LABEL_90;
      case 7:
        v16 -= 2;
        break;
      default:
        break;
    }
  }
LABEL_91:
  v69 = v16 + 1;
  i = (int)a3[2];
  v70 = sub_667620(a3);
  v71 = *(uint32_t *)dword_8F7C04;
  v226 = v70;
  v72 = *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(v71 + 672))(dword_8F7C04, 3);
  if ( i > 1 )
  {
    v234 = i != v226;
    if ( i - 5 <= 0 )
      v234 = false;
    if ( v72 < i )
      v231 = v72 < (int)v226 ? -13487361 : -13435086;
    else
      v231 = -1;
    if ( v234 )
    {
      v192 = i;
      v188 = v226;
      v73 = (const char *)sub_422E70(1051);
      sprintf(Buffer, v73, v188, v192, 5);
    }
    else
    {
      v203 = i;
      v74 = (const char *)sub_422E70(3000);
      sprintf(Buffer, v74, v203);
    }
    sub_572B20(v69, Buffer, (int)(a1 + 13), v231);
    if ( (*(int (/*thiscall*/ **)(void **))*a3)(a3) == 2 )
    {
      j = (void *)(*((int (/*thiscall*/ **)(void **))*a3 + 73))(a3);
      v222 = strlen((const char *)j);
      if ( v222 != 0 )
      {
        v75 = (*((int (/*thiscall*/ **)(void **))*a3 + 74))(a3);
        sub_572B20(v69, j, (int)(a1 + 26), v75);
      }
    }
    ++v69;
  }
  v234 = false;
  v225 = 1;
  for ( i = 0; i < 4; ++i )
  {
    v76 = (*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3);
    if ( *(uint8_t *)(v76 + i + 60) != 0 )
    {
      v77 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);
      if ( i == *v77 )
        v234 = true;
    }
    else
    {
      v225 = 0;
    }
  }
  if ( v225 == 0 )
  {
    i = 0;
    v231 = v234 ? -1 : -13487361;
    do
    {
      v78 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_9B88D0 + 16))(dword_9B88D0);
      if ( *(uint8_t *)(v78 + i + 60) != 0 )
      {
        v204 = sub_4B0EC0(i, 0);
        v79 = (const char *)sub_422E70(1052);
        sprintf(Buffer, v79, v204);
        sub_572B20(v69, Buffer, (int)(a1 + 13), v231);
        if ( v233 )
        {
          v80 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 172))(v230);
          sub_572B20(v69, *(&dword_9B88D8 + *v80), (int)(a1 + 26), v231);
        }
        ++v69;
      }
      ++i;
    }
    while ( i < 4 );
  }
  if ( v230 != nullptr )
  {
    v81 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 172))(v230);
    if ( sub_41A5E0(v81 + 32) != -1 )
    {
      ++v69;
      v82 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 172))(v230);
      Src = (void *)sub_41A5E0(v82 + 32);
      if ( v234 )
      {
        v83 = sub_47DC90(Src);
      }
      else
      {
        i = 0;
        while ( 1 )
        {
          v84 = (*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3);
          if ( *(uint8_t *)(v84 + i + 60) != 0 )
            break;
          if ( ++i >= 4 )
            goto LABEL_132;
        }
        v83 = sub_47E720(i, Src);
      }
      v85 = v83;
      if ( v83 != 0 )
      {
        if ( !v234 || (v86 = sub_41A5E0(v83 + 510), v231 = -1, v86 <= 0) )
          v231 = -13487361;
        v205 = sub_41ACF0(v85 + 20);
        v87 = (const char *)sub_422E70(1053);
        sprintf(Buffer, v87, v205);
        sub_572B20(v69++, Buffer, (int)(a1 + 13), v231);
        v88 = sub_4883E0(a1 + 13, Buffer);
        if ( v227 < v88 )
          v227 = v88;
      }
    }
LABEL_132:
    v89 = v230;
    if ( !v233 )
    {
      v90 = *(uint32_t *)v230;
      v231 = v69 + 1;
      v206 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(v90 + 172))(v230);
      v91 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v89 + 176))(v89);
      sub_572EF0(v91, -1, &v231, 0, v206);
      v69 = v231;
      goto LABEL_172;
    }
    v231 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 176))(v230) + 916;
    if ( dword_795378 == 5 )
    {
      v92 = *(uint32_t *)(v231 + 4);
      v93 = 0;
      v226 = 0;
      while ( 1 )
      {
        i = v93;
        if ( v92 == 0 )
          goto LABEL_158;
        if ( v226 >= (*(uint32_t *)(v231 + 8) - v92) / 80 || *(uint32_t *)(i + v92) != 0 )
          break;
        ++v226;
        v93 = i + 80;
      }
      j = (void *)((*(uint32_t *)(v231 + 8) - v92) / 80);
      if ( j == nullptr )
      {
LABEL_158:
        v96 = v69 + 1;
        v106 = (void *)sub_422E70(1055);
        sub_572B20(v96, v106, (int)(a1 + 13), -346530);
        goto LABEL_159;
      }
      v94 = v69 + 1;
      v95 = (void *)sub_422E70(1054);
      sub_572B20(v94, v95, (int)(a1 + 13), -346530);
      v96 = v94 + 1;
      v97 = 0;
      while ( 1 )
      {
        v98 = *(uint32_t *)(v231 + 4);
        if ( v98 == 0 || v97 >= (*(uint32_t *)(v231 + 8) - v98) / 80 )
          break;
        v99 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 176))(v230);
        v100 = sub_4EB900(v99, v97);
        j = (void *)(v97 + 1);
        sprintf(Buffer, "%d: %s", v97 + 1, v100);
        v247 = nullptr;
        v248 = nullptr;
        v249 = 0;
        LOBYTE(v251) = 6;
        v101 = (void *)sub_572BC0(Buffer, 34, v246);
        if ( (int)v101 > 0 )
        {
          v102 = (char *)v247 + 4;
          for ( Src = v101; Src != nullptr; Src = (char *)Src - 1 )
          {
            if ( *((uint32_t *)v102 + 5) < 0x10u )
              v103 = v102;
            else
              v103 = *(void **)v102;
            sub_572B20(v96++, v103, (int)(a1 + 13), -1);
            v102 += 28;
          }
        }
        LOBYTE(v251) = 0;
        if ( v247 != nullptr )
        {
          if ( v247 != v248 )
          {
            v104 = (char *)v247 + 24;
            do
            {
              if ( *v104 >= 0x10u )
                j__free((void *)*(v104 - 5));
              v105 = v248;
              *v104 = 15;
              *(v104 - 1) = 0;
              *((uint8_t *)v104 - 20) = 0;
              v104 += 7;
            }
            while ( v104 - 6 != v105 );
          }
          j__free(v247);
        }
        v97 = (unsigned int)j;
        v247 = nullptr;
        v248 = nullptr;
        v249 = 0;
      }
LABEL_159:
      v89 = v230;
    }
    else
    {
      j = (void *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v89 + 176))(v89);
      v107 = sub_41A5E0((unsigned int)j + 932);
      j = sub_4EB900(j, v107);
      if ( j == nullptr )
      {
LABEL_163:
        if ( dword_795378 != 4 && dword_795378 != 5 )
        {
          v110 = v69 + 1;
          v111 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v89 + 204))(v89);
          v112 = v111 / 3600;
          if ( v111 / 3600 < 24 )
          {
            if ( v111 != 0 )
            {
              v208 = v112 + 1;
              v194 = (const char *)sub_422E70(1058);
            }
            else
            {
              v194 = (const char *)sub_422E70(1059);
            }
            sprintf(Buffer, v194, v208);
          }
          else
          {
            v207 = v112 / 24 + 1;
            v193 = (const char *)sub_422E70(1057);
            sprintf(Buffer, v193, v207);
          }
          sub_572B20(v110, Buffer, (int)(a1 + 13), -1);
          v69 = v110 + 1;
        }
        goto LABEL_172;
      }
      v108 = v69 + 1;
      v109 = (void *)sub_422E70(1056);
      sub_572B20(v108, v109, (int)(a1 + 13), -346530);
      v96 = v108 + 1;
      sprintf(Buffer, "%s", (const char *)j);
      sub_572B20(v96, Buffer, (int)(a1 + 13), -1);
    }
    v69 = v96 + 1;
    goto LABEL_163;
  }
LABEL_172:
  v113 = (*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3);
  if ( strcmp((const char *)sub_41ACF0(v113 + 16), szPassword) != 0 )
  {
    ++v69;
    v247 = nullptr;
    v248 = nullptr;
    v249 = 0;
    v114 = (int (/*thiscall*/ **)(void **))*a3;
    LOBYTE(v251) = 7;
    v115 = v114[4](a3);
    v116 = sub_41ACF0(v115 + 16);
    v117 = (void *)sub_572BC0(v116, 34, v246);
    if ( (int)v117 > 0 )
    {
      v118 = (char *)v247 + 4;
      for ( Src = v117; Src != nullptr; Src = (char *)Src - 1 )
      {
        if ( *((uint32_t *)v118 + 5) < 0x10u )
          v119 = v118;
        else
          v119 = *(void **)v118;
        v120 = v224 + 13;
        sub_572B20(v69++, v119, (int)(v224 + 13), -346530);
        if ( *((uint32_t *)v118 + 5) < 0x10u )
          v121 = v118;
        else
          v121 = *(char **)v118;
        v122 = sub_4883E0(v120, v121);
        if ( v227 < v122 )
          v227 = v122;
        v118 += 28;
      }
    }
    LOBYTE(v251) = 0;
    if ( v247 != nullptr )
    {
      if ( v247 != v248 )
      {
        v123 = (char *)v247 + 24;
        do
        {
          if ( *v123 >= 0x10u )
            j__free((void *)*(v123 - 5));
          v124 = v248;
          *v123 = 15;
          *(v123 - 1) = 0;
          *((uint8_t *)v123 - 20) = 0;
          v123 += 7;
        }
        while ( v123 - 6 != v124 );
      }
      j__free(v247);
    }
  }
  v125 = v230;
  if ( v230 != nullptr )
  {
    v126 = *(uint32_t *)v230;
    i = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(v126 + 236))(v230) != 0 )
    {
      v127 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v125 + 272))(v125);
    }
    else
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v125 + 240))(v125) == 0 )
        goto LABEL_197;
      v128 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v125 + 244))(v125);
      v127 = sub_4CE8A0(v128);
    }
    i = v127;
LABEL_197:
    v234 = false;
    v129 = 0;
    while ( v125 != (uint8_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v223 + 792))(v223, v129) )
    {
      if ( ++v129 >= 18 )
        goto LABEL_202;
    }
    v234 = true;
LABEL_202:
    if ( i != 0 )
    {
      v130 = *(uint32_t *)(i + 1112);
      v231 = ++v69;
      if ( v130 != 0 )
        v131 = (*(uint32_t *)(i + 1116) - v130) >> 2;
      else
        v131 = 0;
      v132 = 0;
      v222 = v131 + 1;
      j = nullptr;
      while ( 1 )
      {
        v133 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v223 + 792))(v223, v132);
        v134 = (int *)v133;
        if ( v133 != 0 )
        {
          v135 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v133 + 16))(v133);
          if ( *(uint32_t *)(v135 + 4) == *(uint32_t *)i )
            break;
        }
        if ( ++v132 >= 18 )
          goto LABEL_213;
      }
      v136 = *v134;
      j = v134;
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(v136 + 224))(v134) == 0 || (v233 = true, !v234) )
LABEL_213:
        v233 = false;
      v137 = *(uint32_t *)(i + 1104);
      v138 = i + 1104;
      if ( v137 != 0 && *(uint32_t *)(v137 + 4) != 0 )
      {
        v209 = v233 ? -4993059 : -4934476;
        v139 = v224 + 13;
        v195 = (int)(v224 + 13);
        v140 = (void *)sub_41ACF0(i + 1104);
        sub_572B20(v69++, v140, v195, v209);
        v231 = v69;
        v141 = sub_41ACF0(v138);
        v142 = sub_4883E0(v139, v141);
        if ( v227 < v142 )
          v227 = v142;
      }
      Src = nullptr;
      if ( v222 > 0 )
      {
        do
        {
          if ( Src != nullptr )
            v226 = *(uint32_t *)(*(uint32_t *)(i + 1112) + 4 * (uint32_t)Src - 4);
          else
            v226 = *(uint32_t *)i;
          if ( !v234 )
            goto LABEL_229;
          v143 = 0;
          while ( 1 )
          {
            v144 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v223 + 792))(v223, v143);
            if ( v144 != 0 )
            {
              v145 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v144 + 16))(v144);
              if ( *(uint32_t *)(v145 + 4) == v226 )
                break;
            }
            if ( ++v143 >= 18 )
              goto LABEL_229;
          }
          v146 = (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v144 + 200))(v144) == 0;
          v147 = -14745736;
          if ( !v146 )
LABEL_229:
            v147 = -8355712;
          v210 = v147;
          v196 = (int)(v224 + 13);
          v148 = (void *)sub_4F2CE0(v226);
          sub_572B20(v69++, v148, v196, v210);
          Src = (char *)Src + 1;
        }
        while ( (int)Src < v222 );
        v231 = v69;
      }
      if ( v233 )
      {
        v149 = (int *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v230 + 172))(v230);
        v150 = j;
        v211 = *v149;
        v151 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)j + 228))(j);
        sub_572EF0(v151, -14745736, &v231, 1, v211);
        v152 = (void *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v150 + 232))(v150);
        v243 = 15;
        v242 = 0;
        LOBYTE(Block[0]) = 0;
        sub_4015C0(v152, strlen((const char *)v152));
        v69 = v231;
        if ( v242 != 0 )
        {
          v69 = v231 + 1;
          v247 = nullptr;
          v248 = nullptr;
          v249 = 0;
          v153 = (void **)Block[0];
          LOBYTE(v251) = 9;
          if ( v243 < 0x10 )
            v153 = Block;
          v154 = (void *)sub_572BC0(v153, 34, v246);
          if ( (int)v154 > 0 )
          {
            v155 = (char *)v247 + 4;
            for ( j = v154; j != nullptr; j = (char *)j - 1 )
            {
              if ( *((uint32_t *)v155 + 5) < 0x10u )
                v156 = v155;
              else
                v156 = *(void **)v155;
              v157 = v224 + 13;
              sub_572B20(v69++, v156, (int)(v224 + 13), -346530);
              if ( *((uint32_t *)v155 + 5) < 0x10u )
                v158 = v155;
              else
                v158 = *(char **)v155;
              v159 = sub_4883E0(v157, v158);
              if ( v227 < v159 )
                v227 = v159;
              v155 += 28;
            }
          }
          if ( v247 != nullptr )
          {
            v160 = v248;
            if ( v247 != v248 )
            {
              v161 = (char *)v247 + 24;
              do
              {
                if ( *v161 >= 0x10u )
                  j__free((void *)*(v161 - 5));
                *v161 = 15;
                *(v161 - 1) = 0;
                *((uint8_t *)v161 - 20) = 0;
                v161 += 7;
              }
              while ( v161 - 6 != v160 );
            }
            j__free(v247);
          }
        }
        LOBYTE(v251) = 0;
        if ( v243 >= 0x10 )
          j__free(Block[0]);
      }
    }
  }
  v162 = (*((int (/*thiscall*/ **)(void **))*a3 + 4))(a3);
  if ( strcmp((const char *)sub_41ACF0(v162 + 20), szPassword) == 0 )
  {
    v167 = v224;
  }
  else
  {
    ++v69;
    v247 = nullptr;
    v248 = nullptr;
    v249 = 0;
    v163 = (int (/*thiscall*/ **)(void **))*a3;
    LOBYTE(v251) = 10;
    v164 = v163[4](a3);
    v165 = sub_41ACF0(v164 + 20);
    v166 = (void *)sub_572BC0(v165, 34, v246);
    v167 = v224;
    if ( (int)v166 > 0 )
    {
      v168 = (char *)v247 + 4;
      for ( j = v166; j != nullptr; j = (char *)j - 1 )
      {
        if ( *((uint32_t *)v168 + 5) < 0x10u )
          v169 = v168;
        else
          v169 = *(void **)v168;
        sub_572B20(v69++, v169, (int)(v167 + 13), -6908266);
        if ( *((uint32_t *)v168 + 5) < 0x10u )
          v170 = v168;
        else
          v170 = *(char **)v168;
        v171 = sub_4883E0(v167 + 13, v170);
        if ( v227 < v171 )
          v227 = v171;
        v168 += 28;
      }
    }
    LOBYTE(v251) = 0;
    if ( v247 != nullptr )
    {
      if ( v247 != v248 )
      {
        v172 = (char *)v247 + 24;
        do
        {
          if ( *v172 >= 0x10u )
            j__free((void *)*(v172 - 5));
          v173 = v248;
          *v172 = 15;
          *(v172 - 1) = 0;
          *((uint8_t *)v172 - 20) = 0;
          v172 += 7;
        }
        while ( v172 - 6 != v173 );
      }
      j__free(v247);
    }
  }
  if ( v230 == nullptr && (unsigned int)dword_795378 <= 1 )
  {
    Src = *a3;
    v174 = (*((int (/*thiscall*/ **)(void **))Src + 4))(a3);
    if ( (*((uint8_t (/*thiscall*/ **)(void **, uint32_t))Src + 15))(a3, *(uint32_t *)(v174 + 4)) != 0
      && *(uint32_t *)(*((int (/*thiscall*/ **)(void **))*a3 + 33))(a3) == 0 )
    {
      v175 = v69 + 1;
      v176 = (void *)sub_422E70(1060);
      sub_572B20(v175, v176, (int)(v167 + 39), -346530);
      v69 = v175 + 1;
    }
  }
  if ( dword_795378 == 4 )
  {
    v177 = v69 + 1;
    v178 = (void *)sub_422E70(1061);
    sub_572B20(v177, v178, (int)(v167 + 39), -346530);
    if ( v230 == nullptr )
    {
      ++v177;
      v179 = (void *)sub_422E70(1062);
      sub_572B20(v177, v179, (int)(v167 + 39), -346530);
    }
    v69 = v177 + 1;
  }
  if ( dword_795378 == 9 && sub_541A40() == 2 )
  {
    v180 = v69 + 1;
    v181 = (void *)sub_422E70(1061);
    sub_572B20(v180, v181, (int)(v167 + 39), -346530);
    v69 = v180 + 1;
  }
  if ( dword_795378 == 12 )
  {
    v182 = v69 + 1;
    v183 = (void *)sub_422E70(2055);
    sub_572B20(v182, v183, (int)(v167 + 39), -346530);
    v69 = v182 + 1;
  }
  v167[69] = v69 / 36;
  v184 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v167[25] + 20))(v167[25]);
  v185 = v227;
  v186 = *v167;
  v167[20] = v227;
  (*(void (/*thiscall*/ **)(int *, int, int))(v186 + 52))(v167, v185, v69 * (v184 + 1));
  v187 = v167[2];
  *(uint32_t *)(v187 + 28) = 0;
  *(uint32_t *)(v187 + 32) = 0;
  if ( v239 >= 0x10 )
    j__free(v238[0]);
  return 1;
}


// ------------------------------------------------------------
// 0x575F80 CNRDItemInfoWindow__vmtC —— CNRDItemInfoWindow__vmtC 打开入口（直接调 5745B0 完整绘制）
// ------------------------------------------------------------
char /*userpurge*/ CNRDItemInfoWindow__vmtC@<al>(char *a1@<ecx>, int a2@<edi>, int a3, int a4)
{
  int v6; // eax
  int v7; // edx

  dword_9B88D0 = a3;
  *((uint32_t *)a1 + 69) = 0;
  if ( a3 == 0 )
    return 0;
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)a1 + 28))(a1, 1);
  dword_795378 = a4;
  if ( sub_5745B0(a1, a2, dword_9B88D0) == 0 )
    return 0;
  v6 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)a1 + 56))(a1);
  v7 = *(uint32_t *)a1;
  *((uint32_t *)a1 + 67) = v6;
  *((uint32_t *)a1 + 68) = (*(int (/*thiscall*/ **)(char *))(v7 + 60))(a1);
  return 1;
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
int /*thiscall*/ sub_575FF0(
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

  v7 = InternetOpenA(lpszAgent, 0, szPassword, szPassword, 0);
  *(uint32_t *)(this + 200020) = v7;
  if ( v7 != nullptr )
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
    if ( *(uint32_t *)(this + 200024) != 0 )
    {
      if ( InternetAttemptConnect(0) != 0 )
      {
        LastError = GetLastError();
        v10 = *(void **)(this + 200024);
        *(uint32_t *)(this + 200032) = LastError;
        CloseHandle(v10);
        CloseHandle(*(HANDLE *)(this + 200020));
        return 0;
      }
      else
      {
        return 1;
      }
    }
    else
    {
      *(uint32_t *)(this + 200032) = GetLastError();
      CloseHandle(*(HANDLE *)(this + 200020));
      return 0;
    }
  }
  else
  {
    *(uint32_t *)(this + 200032) = GetLastError();
    return 0;
  }
}



// ------------------------------------------------------------
// 0x5760E0 sub_5760E0 —— 请求 GET：HttpOpenRequestA(hConnect, 动词=off_726478("GET"), obj, "HTTP/1.0", Accept */*, flags 0x4400000)→头 "Accept: */*\r\n"→HttpSendRequestA(无正文)；句柄入 +200028
// ------------------------------------------------------------
// off_726478 指向动词串 "GET"；本函数即模式 1 的发送实现。
int /*thiscall*/ sub_5760E0(int this, LPCSTR lpszObjectName)
{
  void *v3; // eax
  void *v5; // [esp-20h] [ebp-28h]
  LPCSTR lpszAcceptTypes; // [esp+4h] [ebp-4h] BYREF

  v5 = *(void **)(this + 200024);
  lpszAcceptTypes = "*/*";
  v3 = HttpOpenRequestA(v5, off_726478, lpszObjectName, "HTTP/1.0", szPassword, &lpszAcceptTypes, 0x4400000u, 0);
  *(uint32_t *)(this + 200028) = v3;
  if ( v3 != nullptr
    && HttpAddRequestHeadersA(v3, "Accept: */*\r\n", 0xDu, 0x80000000)
    && HttpSendRequestA(*(HINTERNET *)(this + 200028), nullptr, 0, nullptr, 0) )
  {
    return 1;
  }
  *(uint32_t *)(this + 200032) = GetLastError();
  return 0;
}



// ------------------------------------------------------------
// 0x576180 sub_576180 —— ReadResponse()：InternetReadFile 按 0x400(1024) 字节块循环读入 this+20（累计上限 0x186A0=100000），随后 HttpQueryInfoA(0x16=RAW_HEADERS_CRLF) 取原始响应头入 this+100020
// ------------------------------------------------------------
// dwNumberOfBytesRead==0（对端关闭）即结束读取；读失败/查询失败把错误存 +200032（dword 索引 50008）。
BOOL /*thiscall*/ sub_576180(
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
  memset(Buffer, 0, 1024);
  if ( *(this + 50007) != 0 )
  {
    memset(a4, 0, a5);
    v8 = a6;
    *a6 = 0;
    while ( 1 )
    {
      v9 = (void *)v6[50007];
      if ( v9 == nullptr )
        break;
      memset(Buffer, 0, 0x400u);
      if ( !InternetReadFile(v9, Buffer, 0x400u, &dwNumberOfBytesRead) )
        break;
      v10 = dwNumberOfBytesRead;
      if ( dwNumberOfBytesRead == 0 || *v8 >= a5 )
        goto LABEL_10;
      qmemcpy(&a4[*v8], Buffer, dwNumberOfBytesRead);
      v6 = this;
      *v8 += v10;
    }
    v6[50008] = GetLastError();
LABEL_10:
    memset(lpBuffer, 0, dwBufferLength);
    if ( HttpQueryInfoA((HINTERNET)v6[50007], 0x16u, lpBuffer, &dwBufferLength, nullptr) )
    {
      return *v8 != 0;
    }
    else
    {
      v6[50008] = GetLastError();
      return false;
    }
  }
  else
  {
    *(this + 50008) = GetLastError();
    return false;
  }
}



// ------------------------------------------------------------
// 0x5762F0 sub_5762F0 —— LocalFree 包装：释放 *a1 并置空（multipart 正文缓冲清理用）
// ------------------------------------------------------------
HLOCAL /*stdcall*/ sub_5762F0(HLOCAL *a1)
{
  HLOCAL result; // eax

  result = *a1;
  if ( *a1 != nullptr )
  {
    result = LocalFree(*a1);
    *a1 = nullptr;
  }
  return result;
}



// ------------------------------------------------------------
// 0x576310 sub_576310 —— 文件扩展名→Content-Type：RegOpenKeyExA(HKEY_CLASSES_ROOT, ".ext") 查 "Content Type"，失败/缺省 "application/octet-stream"
// ------------------------------------------------------------
BYTE */*stdcall*/ sub_576310(HKEY phkResult)
{
  HKEY v1; // edi
  unsigned int i; // esi
  DWORD cbData; // [esp+8h] [ebp-4h] BYREF

  v1 = phkResult;
  cbData = 1024;
  for ( i = strlen((const char *)phkResult); i != 0; --i )
  {
    if ( strncmp((const char *)v1 + i, ".", 1u) == 0 )
      break;
  }
  if ( RegOpenKeyExA(HKEY_CLASSES_ROOT, (LPCSTR)v1 + i, 0, 1u, &phkResult) != 0 )
  {
    strncpy((char *)Destination, "application/octet-stream", 0x18u);
    return Destination;
  }
  else
  {
    if ( RegQueryValueExA(phkResult, "Content Type", nullptr, nullptr, Destination, &cbData) != 0 )
      strncpy((char *)Destination, "application/octet-stream", 0x18u);
    RegCloseKey(phkResult);
    return Destination;
  }
}



// ------------------------------------------------------------
// 0x5763D0 sub_5763D0 —— URL 解析器：拆 scheme(缺省 http；https→端口 443 否则 80)/host[:port]/path 四段输出；端口显式存在时 atol 提取
// ------------------------------------------------------------
char */*stdcall*/ sub_5763D0(char *Source, char *Destination, char *a3, int *a4, char *a5)
{
  size_t i; // ebx
  unsigned int v6; // ebx
  unsigned int v7; // edx
  unsigned int v8; // esi
  const char *v9; // edi
  unsigned int v11; // [esp+Ch] [ebp-408h]
  char String[1024]; // [esp+10h] [ebp-404h] BYREF
  int v13; // [esp+410h] [ebp-4h]

  v13 = dword_796E50;
  for ( i = 0; strlen(Source) != 0; ++i )
  {
    if ( i >= strlen(Source) )
      break;
    if ( strncmp(&Source[i], ":", 1u) == 0 )
      break;
  }
  if ( strncmp(&Source[i + 1], "/", 1u) == 0 )
  {
    if ( Destination != nullptr )
    {
      strncpy(Destination, Source, i);
      Destination[i] = 0;
    }
    v6 = i + 3;
    v7 = v6;
    v11 = v6;
  }
  else
  {
    if ( Destination != nullptr )
    {
      strncpy(Destination, "http", 4u);
      Destination[5] = 0;
    }
    v6 = 0;
    v11 = 0;
    v7 = 0;
  }
  if ( strlen(Source) != 0 )
  {
    while ( v6 < strlen(Source) )
    {
      if ( strncmp(&Source[v6], "/", 1u) == 0 || (++v6, strlen(Source) == 0) )
      {
        v7 = v11;
        break;
      }
      v7 = v11;
    }
  }
  v8 = v7;
  if ( v7 > v6 )
  {
LABEL_23:
    if ( strcmp(Destination, "https") == 0 )
      *a4 = 443;
    else
      *a4 = 80;
    strncpy(a3, &Source[v7], v6 - v7);
    v9 = Source;
  }
  else
  {
    while ( strncmp(&Source[v8], ":", 1u) != 0 )
    {
      if ( ++v8 > v6 )
      {
        v7 = v11;
        goto LABEL_23;
      }
    }
    memset(String, 0, sizeof(String));
    v9 = Source;
    strncpy(String, &Source[v8 + 1], v6 - v8);
    *a4 = atol(String);
    strncpy(a3, &Source[v11], v8 - v11);
  }
  if ( v6 < strlen(v9) )
    return strncpy(a5, &v9[v6], strlen(v9) - v6);
  *a5 = 0;
  return a5;
}



// ------------------------------------------------------------
// 0x576650 sub_576650 —— urlencoded 正文构造：遍历字段表（步进 1284）拼 name=value，分隔符 61'='/38'&'，容量 0x400
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_576650(const char **this, char *a2, unsigned int a3)
{
  const char *v4; // eax
  const char *v5; // ecx
  const char *v8; // [esp+18h] [ebp+8h]

  memset(a2, 0, a3);
  v4 = *(this + 2);
  v8 = v4;
  if ( v4 < *(this + 3) )
  {
    while ( 1 )
    {
      strcat(a2, v4);
      *(uint16_t *)&a2[strlen(a2)] = 61;
      strcat(a2, v8 + 256);
      v5 = v8 + 1284;
      v8 += 1284;
      if ( v8 >= *(this + 3) )
        break;
      *(uint16_t *)&a2[strlen(a2)] = 38;
      if ( v5 >= *(this + 3) )
        break;
      v4 = v8;
    }
  }
  a2[a3] = 0;
  return strlen(a2);
}



// ------------------------------------------------------------
// 0x576760 sub_576760 —— multipart 正文长度预算：文本字段 0x2000/个、文件字段 GetFileSize+6144/个（字段类型在表项 +1280：1=文本 2=文件）
// ------------------------------------------------------------
int /*fastcall*/ sub_576760(int a1)
{
  unsigned int v1; // ebx
  int v2; // edi
  HANDLE FileA; // esi
  int i; // [esp+8h] [ebp-4h]

  v1 = *(uint32_t *)(a1 + 8);
  v2 = 0;
  for ( i = a1; v1 < *(uint32_t *)(a1 + 12); v1 += 1284 )
  {
    if ( *(uint32_t *)(v1 + 1280) == 1 )
    {
      v2 += 0x2000;
    }
    else if ( *(uint32_t *)(v1 + 1280) == 2 )
    {
      FileA = CreateFileA((LPCSTR)(v1 + 256), 0x80000000, 1u, nullptr, 3u, 0x80u, nullptr);
      v2 += GetFileSize(FileA, nullptr) + 6144;
      CloseHandle(FileA);
      a1 = i;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x5767E0 sub_5767E0 —— 请求 POST-urlencoded（模式 2）：HttpOpenRequestA("POST", flags 0x4400040) + 头 "Content-Type: application/x-www-form-urlencoded\r\n" + HttpSendRequestA(正文=576650 产物)
// ------------------------------------------------------------
// 正文即 k=v&k=v 串，经 HttpSendRequestA 的 lpOptional 参数随请求体发送。
int /*thiscall*/ sub_5767E0(int this, LPCSTR lpszObjectName)
{
  void *v3; // eax
  LPCSTR lpszAcceptTypes; // [esp+8h] [ebp-408h] BYREF
  char Optional[1024]; // [esp+Ch] [ebp-404h] BYREF
  int v7; // [esp+40Ch] [ebp-4h]

  v7 = dword_796E50;
  memset(Optional, 0, sizeof(Optional));
  lpszAcceptTypes = "*/*";
  sub_576650((const char **)this, Optional, 0x400u);
  v3 = HttpOpenRequestA(
         *(HINTERNET *)(this + 200024),
         "POST",
         lpszObjectName,
         "HTTP/1.0",
         szPassword,
         &lpszAcceptTypes,
         0x4400040u,
         0);
  *(uint32_t *)(this + 200028) = v3;
  if ( v3 != nullptr
    && HttpAddRequestHeadersA(v3, "Accept: */*\r\n", 0xDu, 0x80000000)
    && HttpSendRequestA(
         *(HINTERNET *)(this + 200028),
         "Content-Type: application/x-www-form-urlencoded\r\n",
         strlen("Content-Type: application/x-www-form-urlencoded\r\n"),
         Optional,
         strlen(Optional)) )
  {
    return 1;
  }
  *(uint32_t *)(this + 200032) = GetLastError();
  return 0;
}



// ------------------------------------------------------------
// 0x576900 sub_576900 —— multipart 正文装配（LocalAlloc 缓冲）：文本项 "--BOUNDARY\r\nContent-Disposition: form-data; name=\"%s\"\r\n\r\n%s\r\n"；文件项 + filename=\"%s\" + Content-Type(576310) + 文件字节（ReadFile 0x400 循环）+ 0x0A0D("\r\n")；收尾 "--"+BOUNDARY+"--"+'\r'
// ------------------------------------------------------------
// word 常量：2573=0x0A0D("\r\n")、11565=0x2D2D("--")；字段名/路径在表项 +256，类型在 +1280。
unsigned int /*thiscall*/ sub_576900(const char **this, HLOCAL *a2, const char *a3)
{
  HLOCAL *v3; // ebx
  SIZE_T v5; // eax
  HLOCAL (/*stdcall*/ *v6)(UINT, SIZE_T); // edi
  const char *v7; // eax
  unsigned int v8; // edx
  HKEY v9; // esi
  char *v10; // ebx
  const char *v11; // eax
  unsigned int v12; // edx
  unsigned int v13; // esi
  int v14; // eax
  unsigned int v15; // edx
  bool v16; // cf
  unsigned int v17; // ecx
  char *v18; // eax
  int v19; // ebx
  unsigned int v20; // eax
  DWORD FileSize; // [esp+8h] [ebp-42Ch]
  unsigned int j; // [esp+Ch] [ebp-428h]
  HKEY i; // [esp+14h] [ebp-420h]
  HANDLE hFile; // [esp+18h] [ebp-41Ch]
  DWORD NumberOfBytesRead; // [esp+1Ch] [ebp-418h] BYREF
  int v28; // [esp+20h] [ebp-414h]
  const char *v29; // [esp+24h] [ebp-410h]
  DWORD v30; // [esp+28h] [ebp-40Ch]
  uint8_t Buffer[1028]; // [esp+2Ch] [ebp-408h] BYREF
  int v32; // [esp+430h] [ebp-4h]

  v3 = a2;
  v32 = dword_796E50;
  if ( *a2 != nullptr )
  {
    LocalFree(*a2);
    *a2 = nullptr;
  }
  v5 = sub_576760(this);
  v6 = LocalAlloc;
  *a2 = LocalAlloc(0x40u, v5);
  v7 = *(this + 2);
  v8 = (unsigned int)*(this + 3);
  v28 = 0;
  v30 = 0;
  v29 = v7;
  if ( (unsigned int)v7 < v8 )
  {
    v9 = (HKEY)(v7 + 256);
    for ( i = (HKEY)(v7 + 256); ; v9 = i )
    {
      v10 = nullptr;
      if ( *((uint32_t *)v9 + 256) == 1 )
      {
        v10 = (char *)v6(0x40u, 0x2000u);
        sprintf(v10, "--%s\r\nContent-Disposition: form-data; name=\"%s\"\r\n\r\n%s\r\n", a3, v29, (const char *)v9);
        v30 = strlen(v10);
      }
      else if ( *((uint32_t *)v9 + 256) == 2 )
      {
        NumberOfBytesRead = 0;
        v30 = 0;
        hFile = CreateFileA((LPCSTR)v9, 0x80000000, 1u, nullptr, 3u, 0x8000080u, nullptr);
        FileSize = GetFileSize(hFile, nullptr);
        v10 = (char *)v6(0x40u, FileSize + 6145);
        memset(Buffer, 0, 1025);
        v11 = (const char *)sub_576310(v9);
        sprintf(
          v10,
          "--%s\r\nContent-Disposition: form-data; name=\"%s\"; filename=\"%s\"\r\nContent-Type: %s\r\n\r\n",
          a3,
          v29,
          (const char *)v9,
          v11);
        for ( j = strlen(v10); ReadFile(hFile, Buffer, 0x400u, &NumberOfBytesRead, nullptr); v30 = NumberOfBytesRead
                                                                                                 + v12 )
        {
          if ( NumberOfBytesRead == 0 )
            break;
          v12 = v30;
          if ( v30 > FileSize )
            break;
          qmemcpy(&v10[j + v30], Buffer, NumberOfBytesRead);
          memset(Buffer, 0, 1025);
        }
        v13 = j + v30;
        *(uint16_t *)&v10[j + v30] = 2573;
        CloseHandle(hFile);
        v30 = v13 + 2;
      }
      v14 = v28;
      v15 = v30;
      qmemcpy((char *)*a2 + v28, v10, v30);
      v28 = v15 + v14;
      if ( v10 != nullptr )
        LocalFree(v10);
      v16 = v29 + 1284 < *(this + 3);
      v29 += 1284;
      i += 321;
      if ( !v16 )
        break;
      v6 = LocalAlloc;
    }
    v3 = a2;
  }
  *(uint16_t *)((char *)*v3 + v28) = 11565;
  v17 = strlen(a3);
  v18 = (char *)*v3;
  v19 = v28;
  qmemcpy(&v18[v28 + 2], a3, v17);
  v20 = (unsigned int)*a2 + strlen(a3) + v19 + 2;
  *(uint16_t *)v20 = 11565;
  *(uint8_t *)(v20 + 2) = 13;
  return strlen(a3) + v19 + 5;
}


// ------------------------------------------------------------
// 0x576C40 sub_576C40 —— 请求 POST-multipart（模式 3）：boundary=--MULTI-PARTS-FORM-DATA-BOUNDARY；头 Accept + Content-Type(multipart) + "Content-Length: %d"（均 ADDREQ_FLAG_REPLACE 0x10000000）；HttpSendRequestExA→InternetWriteFile(576900 缓冲)→HttpEndRequestA
// ------------------------------------------------------------
// 发送完成后 5762F0 释放正文缓冲；任一步失败错误入 +200032。
int /*thiscall*/ sub_576C40(int this, LPCSTR lpszObjectName)
{
  void *v3; // eax
  DWORD v5; // edi
  void *v6; // ecx
  void *v7; // [esp-18h] [ebp-458h]
  struct _INTERNET_BUFFERSA BuffersIn; // [esp+4h] [ebp-43Ch] BYREF
  DWORD dwNumberOfBytesWritten; // [esp+2Ch] [ebp-414h] BYREF
  LPCSTR lpszAcceptTypes; // [esp+30h] [ebp-410h] BYREF
  DWORD dwNumberOfBytesToWrite; // [esp+34h] [ebp-40Ch]
  LPCVOID lpBuffer; // [esp+38h] [ebp-408h] BYREF
  CHAR szHeaders[1024]; // [esp+3Ch] [ebp-404h] BYREF
  int v14; // [esp+43Ch] [ebp-4h]

  v14 = dword_796E50;
  lpszAcceptTypes = "*/*";
  lpBuffer = nullptr;
  dwNumberOfBytesToWrite = sub_576900((const char **)this, (HLOCAL *)&lpBuffer, "--MULTI-PARTS-FORM-DATA-BOUNDARY");
  v3 = HttpOpenRequestA(
         *(HINTERNET *)(this + 200024),
         "POST",
         lpszObjectName,
         "HTTP/1.0",
         szPassword,
         &lpszAcceptTypes,
         0x4400040u,
         0);
  *(uint32_t *)(this + 200028) = v3;
  if ( v3 != nullptr
    && HttpAddRequestHeadersA(v3, "Accept: */*\r\n", 0xDu, 0x80000000)
    && HttpAddRequestHeadersA(
         *(HINTERNET *)(this + 200028),
         "Content-Type: multipart/form-data; boundary=--MULTI-PARTS-FORM-DATA-BOUNDARY\r\n",
         strlen("Content-Type: multipart/form-data; boundary=--MULTI-PARTS-FORM-DATA-BOUNDARY\r\n"),
         0x10000000u) )
  {
    memset(szHeaders, 0, sizeof(szHeaders));
    v5 = dwNumberOfBytesToWrite;
    sprintf(szHeaders, "Content-Length: %d\r\n", dwNumberOfBytesToWrite);
    if ( HttpAddRequestHeadersA(*(HINTERNET *)(this + 200028), szHeaders, strlen(szHeaders), 0x10000000u)
      && (v6 = *(void **)(this + 200028),
          BuffersIn.dwStructSize = 40,
          memset(&BuffersIn.Next, 0, 36),
          HttpSendRequestExA(v6, &BuffersIn, nullptr, 8u, 0))
      && (v7 = *(void **)(this + 200028),
          dwNumberOfBytesWritten = 0,
          InternetWriteFile(v7, lpBuffer, v5, &dwNumberOfBytesWritten))
      && HttpEndRequestA(*(HINTERNET *)(this + 200028), nullptr, 8u, 0) )
    {
      sub_5762F0((HLOCAL *)&lpBuffer);
      return 1;
    }
    else
    {
      *(uint32_t *)(this + 200032) = GetLastError();
      return 0;
    }
  }
  else
  {
    *(uint32_t *)(this + 200032) = GetLastError();
    return 0;
  }
}



// ------------------------------------------------------------
// 0x576E90 sub_576E90 —— 请求模式分发：a3==2→5767E0(urlencoded POST)；a3==3→576C40(multipart POST)；其余→5760E0(GET)
// ------------------------------------------------------------
int /*thiscall*/ sub_576E90(void *this, LPCSTR lpszObjectName, int a3)
{
  if ( a3 == 2 )
    return sub_5767E0((int)this, lpszObjectName);
  if ( a3 == 3 )
    return sub_576C40((int)this, lpszObjectName);
  return sub_5760E0((int)this, lpszObjectName);
}



// ------------------------------------------------------------
// 0x576ED0 sub_576ED0 —— GenericHTTPClient 构造/复位：vftbl 装配、清句柄 50005/50006/50007（+200020/24/28），释放并清空字段表指针（+2..+4）
// ------------------------------------------------------------
void /*thiscall*/ sub_576ED0(void *this)
{
  *(uint32_t *)this = &vftbl_GenericHTTPClient;
  *((uint32_t *)this + 50007) = 0;
  *((uint32_t *)this + 50006) = 0;
  *((uint32_t *)this + 50005) = 0;
  if ( *((uint32_t *)this + 2) != 0 )
    j__free(*((void **)this + 2));
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
}



// ------------------------------------------------------------
// 0x576F10 sub_576F10 —— Request() 总入口：5763D0 解析 URL→575FF0 Connect→576E90 按模式发送→576180 读应答→关闭 hRequest/hConnect/hInternet 三级句柄；Connect 失败日志 "GenericHTTPClient::Request::Connect()  false"
// ------------------------------------------------------------
// 调用方：ui_icon_perf.cpp 0x46EB70 StartAddress 线程，GET 模式，UA="MERONG(0.9/;p)"，URL=全局 unk_98BA60。
int /*thiscall*/ sub_576F10(int this, char *Source, int a3, const CHAR *a4)
{
  void *v5; // esi
  int v7; // [esp+Ch] [ebp-C10h] BYREF
  int v8; // [esp+10h] [ebp-C0Ch] BYREF
  int v9; // [esp+14h] [ebp-C08h]
  char Destination[1024]; // [esp+18h] [ebp-C04h] BYREF
  CHAR szObjectName[1024]; // [esp+418h] [ebp-804h] BYREF
  char v12[1024]; // [esp+818h] [ebp-404h] BYREF
  int v13; // [esp+C18h] [ebp-4h]

  v13 = dword_796E50;
  memset(Destination, 0, sizeof(Destination));
  memset(v12, 0, sizeof(v12));
  memset(szObjectName, 0, sizeof(szObjectName));
  v9 = 1;
  v8 = 0;
  v7 = 0;
  sub_5763D0(Source, Destination, v12, &v8, szObjectName);
  if ( sub_575FF0(this, v12, a4, v8, nullptr, nullptr) != 0 )
  {
    if ( sub_576E90((void *)this, szObjectName, a3) == 0
      || !sub_576180(
            (uint32_t *)this,
            (LPVOID)(this + 100020),
            0x186A0u,
            (char *)(this + 20),
            0x186A0u,
            (unsigned int *)&v7) )
    {
      v9 = 0;
    }
    if ( *(uint32_t *)(this + 200028) != 0 )
      InternetCloseHandle(*(HINTERNET *)(this + 200028));
    if ( *(uint32_t *)(this + 200024) != 0 )
      InternetCloseHandle(*(HINTERNET *)(this + 200024));
    v5 = *(void **)(this + 200020);
    if ( v5 != nullptr )
      InternetCloseHandle(v5);
    return v9;
  }
  else
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
void */*thiscall*/ GenericHTTPClient__vmt0(void *Block, char a2)
{
  sub_576ED0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5770B0 sub_5770B0 —— GenericHTTPClient 平凡构造：清字段表指针与 50005/50006/50007 句柄（不装配 vftbl）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5770B0(uint32_t *this)
{
  *this = &vftbl_GenericHTTPClient;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 50007) = 0;
  *(this + 50006) = 0;
  *(this + 50005) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x5770E0 sub_5770E0 —— Base64 解码：A-Za-z0-9+/ 四字符组 6bit 拼装，非法字符回退重试；输出上限 *a4 保护（0x577250 的解码核）
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_5770E0(char *a1, int a2, uint8_t *a3, uint32_t *a4)
{
  char *v4; // ebx
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

  v4 = a1;
  if ( a1 == nullptr || a4 == nullptr )
    return false;
  v13 = (unsigned int)&a1[a2];
  v15 = 0;
  v14 = a3 == nullptr;
  if ( v4 < &v4[a2] )
  {
    do
    {
      v5 = 0;
      v6 = 0;
      for ( i = 0; i < 4; ++i )
      {
        if ( (unsigned int)v4 >= v13 )
          break;
        v8 = *v4;
        if ( v8 < 0x41 || v8 > 0x5A )
        {
          if ( v8 < 0x61 || v8 > 0x7A )
          {
            if ( v8 < 0x30 || v8 > 0x39 )
              v9 = v8 == 43 ? 62 : v8 != 47 ? -1 : 63;
            else
              v9 = v8 + 4;
          }
          else
          {
            v9 = v8 - 71;
          }
        }
        else
        {
          v9 = v8 - 65;
        }
        ++v4;
        if ( v9 == -1 )
        {
          --i;
        }
        else
        {
          v5 = v9 | (v5 << 6);
          v6 += 6;
        }
      }
      if ( !v14 )
        v14 = v15 + v6 / 8 > *a4;
      v10 = v6 / 8;
      v11 = v5 << (24 - v6);
      if ( v6 / 8 > 0 )
      {
        v15 += v10;
        do
        {
          if ( !v14 )
            *a3++ = BYTE2(v11);
          v11 <<= 8;
          --v10;
        }
        while ( v10 != 0 );
      }
    }
    while ( (unsigned int)v4 < v13 );
  }
  *a4 = v15;
  return !v14;
}



// ------------------------------------------------------------
// 0x577220 sub_577220 —— 应答缓冲复位：+20480 XOR 密钥清零 + 两块 0xA000(40KB) 应答区清零（全局单例 unk_98BB68 的初始化）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_577220(uint32_t *this)
{
  *(this + 20480) = 0;
  memset(this, 0, 0xA000u);
  memset(this + 10240, 0, 0xA000u);
  return this;
}



// ------------------------------------------------------------
// 0x577250 sub_577250 —— 应答解码：Base64 解码入 this（容量上限 40960）后按 dword 与密钥 this+20480 逐 4 字节 XOR（每 4 字节）
// ------------------------------------------------------------
// 调用方 ui_icon_perf.cpp 0x46EB70：密钥 dword_99FB68=2857617(0x2B9551)。
uint32_t */*thiscall*/ sub_577250(uint32_t *this, int a2)
{
  char *v2; // ebx
  int v4; // edx
  int v5; // ecx
  int i; // eax

  v2 = (char *)a2;
  v4 = strlen((const char *)a2);
  memset(this, 0, 0xA000u);
  a2 = 40960;
  sub_5770E0(v2, v4, this, &a2);
  v5 = a2 / 4 + (a2 % 4 > 0);
  for ( i = 0; i < v5; ++i )
    *(this + i) ^= *(this + 20480);
  return this;
}



// ------------------------------------------------------------
// 0x5772E0 sub_5772E0 —— 字段表项写入：[0]=name 指针、[1]=value 指针、[9]=strlen(value)（1284 字节表项的前 1/3 视图）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5772E0(const char **this, const char *a2)
{
  unsigned int result; // eax

  *this = a2;
  result = strlen(a2);
  *(this + 1) = a2;
  *(this + 9) = (const char *)result;
  return result;
}



// ------------------------------------------------------------
// 0x577310 sub_577310 —— multipart 文件项 Content-Type 查询转发（32 行，576900 装配文件项时调用）
// ------------------------------------------------------------
char */*thiscall*/ sub_577310(char *this, char *a2)
{
  char *result; // eax
  int v3; // edx
  char v4; // cl

  result = a2;
  v3 = this + 56 - a2;
  do
  {
    v4 = *result;
    result[v3] = *result;
    ++result;
  }
  while ( v4 != 0 );
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
char */*thiscall*/ sub_577330(char *this)
{
  unsigned int v2; // ebx
  unsigned int v3; // edi
  int i; // ebx
  int v5; // eax
  int v6; // ecx
  unsigned int v7; // edx
  int v8; // eax
  size_t v9; // ecx
  const char *v10; // eax
  char *v11; // esi
  int64_t v13; // rax
  unsigned int v14; // edi
  char *v15; // ecx
  char *v16; // edx
  char *v17; // eax
  char *v18; // ebx
  int v19; // edx
  int64_t v20; // rax
  unsigned int v21; // edi
  int j; // ebx
  int v23; // eax
  int v24; // edx
  int v25; // eax
  const char *v26; // eax
  int v27; // eax
  char *v28; // eax
  int64_t v29; // rax
  char v30; // [esp+Ch] [ebp-8h]

  if ( (signed int)abs32(*((uint32_t *)this + 1) - *(uint32_t *)this) < *((uint32_t *)this + 9) )
  {
    do
    {
      if ( strncmp(*((const char **)this + 1), this + 56, strlen(this + 56)) != 0 )
        break;
      v2 = strlen(this + 56) + *((uint32_t *)this + 1);
      *((uint32_t *)this + 1) = v2;
    }
    while ( (signed int)abs32(v2 - *(uint32_t *)this) < *((uint32_t *)this + 9) );
  }
  v3 = 0;
  for ( i = 0; ; i += 28 )
  {
    v5 = *((uint32_t *)this + 11);
    if ( v5 == 0 || v3 >= (*((uint32_t *)this + 12) - v5) / 28 )
      break;
    v6 = *((uint32_t *)this + 11);
    v7 = *(uint32_t *)(v6 + i + 24);
    v8 = v6 + i;
    v9 = *(uint32_t *)(v6 + i + 20);
    if ( v7 < 0x10 )
      v10 = (const char *)(v8 + 4);
    else
      v10 = *(const char **)(v8 + 4);
    if ( strncmp(*((const char **)this + 1), v10, v9) == 0 )
    {
      *((uint32_t *)this + 1) += *(uint32_t *)(28 * v3 + *((uint32_t *)this + 11) + 20);
      v11 = this + 8;
      sub_4015C0("NULL", 4u);
      if ( *((uint32_t *)v11 + 6) < 0x10u )
        return v11 + 4;
      else
        return *((char **)v11 + 1);
    }
    ++v3;
  }
  v13 = *((uint32_t *)this + 1) - *(uint32_t *)this;
  if ( (signed int)((HIDWORD(v13) ^ v13) - HIDWORD(v13)) >= *((uint32_t *)this + 9) )
    return nullptr;
  v14 = *((uint32_t *)this + 8);
  v15 = this + 12;
  if ( v14 < 0x10 )
    v16 = this + 12;
  else
    v16 = *(char **)v15;
  v17 = &v16[*((uint32_t *)this + 7)];
  if ( v14 < 0x10 )
    v18 = this + 12;
  else
    v18 = *(char **)v15;
  if ( v14 >= 0x10 )
    v15 = *(char **)v15;
  if ( v18 != nullptr )
    v19 = v18 - v15;
  else
    v19 = 0;
  if ( v17 != nullptr )
    v17 -= (int)v18;
  sub_401230(v19, v17);
  v20 = *((uint32_t *)this + 1) - *(uint32_t *)this;
  if ( (signed int)((HIDWORD(v20) ^ v20) - HIDWORD(v20)) < *((uint32_t *)this + 9) )
  {
    while ( strncmp(*((const char **)this + 1), this + 56, strlen(this + 56)) != 0 )
    {
      v21 = 0;
      for ( j = 0; ; j += 28 )
      {
        v23 = *((uint32_t *)this + 11);
        if ( v23 == 0 || v21 >= (*((uint32_t *)this + 12) - v23) / 28 )
          break;
        v24 = *((uint32_t *)this + 11);
        v25 = v24 + j;
        if ( *(uint32_t *)(v24 + j + 24) < 0x10u )
          v26 = (const char *)(v25 + 4);
        else
          v26 = *(const char **)(v25 + 4);
        if ( strncmp(*((const char **)this + 1), v26, *(uint32_t *)(v24 + j + 20)) == 0 )
        {
          *((uint32_t *)this + 1) += *(uint32_t *)(*((uint32_t *)this + 11) + 28 * v21 + 20);
          break;
        }
        ++v21;
      }
      v27 = *((uint32_t *)this + 11);
      if ( v27 == 0 || v21 >= (*((uint32_t *)this + 12) - v27) / 28 )
      {
        v28 = *((char **)this + 1);
        v30 = *v28;
        *((uint32_t *)this + 1) = v28 + 1;
        sub_4164C0((std::_String_base *)(this + 8), 1, v30);
        v29 = *((uint32_t *)this + 1) - *(uint32_t *)this;
        if ( (signed int)((HIDWORD(v29) ^ v29) - HIDWORD(v29)) < *((uint32_t *)this + 9) )
          continue;
      }
      goto LABEL_46;
    }
    *((uint32_t *)this + 1) += strlen(this + 56);
  }
LABEL_46:
  if ( *((uint32_t *)this + 8) < 0x10u )
    return this + 12;
  else
    return *((char **)this + 3);
}


// ------------------------------------------------------------
// 0x5775D0 sub_5775D0 —— std::vector<string>(28 字节/项) 区间拷贝（4014D0 逐项赋值）
// ------------------------------------------------------------
int /*cdecl*/ sub_5775D0(int a1, int a2, int a3)
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
// 0x577670 sub_577670 —— vector<string> 扩容：Block>0x9249249 抛 length_error(416610)；operator new(28n) 迁移
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_577670(uint32_t *this, unsigned int Block)
{
  unsigned int result; // eax
  int v4; // ebx
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // [esp-18h] [ebp-34h]
  int v9; // [esp-14h] [ebp-30h]
  uint32_t v10[7]; // [esp+0h] [ebp-1Ch] BYREF
  char *Blocka; // [esp+24h] [ebp+8h]

  v10[3] = v10;
  if ( Block > 0x9249249 )
    sub_416610();
  result = *(this + 1);
  if ( result != 0 )
    result = (int)(*(this + 3) - result) / 28;
  if ( result < Block )
  {
    v4 = 28 * Block;
    Blocka = (char *)operator new(28 * Block);
    v9 = *(this + 2);
    v8 = *(this + 1);
    v10[6] = 0;
    sub_5775D0(v8, v9, (int)Blocka);
    v5 = *(this + 1);
    if ( v5 != 0 )
      v6 = (*(this + 2) - v5) / 28;
    else
      v6 = 0;
    v7 = *(this + 1);
    if ( v7 != 0 )
    {
      sub_4166A0(v7, *(this + 2));
      j__free((void *)*(this + 1));
    }
    *(this + 3) = &Blocka[v4];
    *(this + 2) = &Blocka[28 * v6];
    *(this + 1) = Blocka;
    return (unsigned int)Blocka;
  }
  return result;
}



// ------------------------------------------------------------
// 0x577780 sub_577780 —— vector 扩容转发（调 577670）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_577780(uint32_t *this)
{
  uint32_t *v2; // ecx

  *(this + 8) = 15;
  *(this + 7) = 0;
  *((uint8_t *)this + 12) = 0;
  v2 = this + 10;
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = 0;
  *this = 0;
  *(this + 1) = 0;
  *(this + 9) = 0;
  *((uint8_t *)this + 56) = 0;
  sub_577670(v2, 0xAu);
  return this;
}



// ------------------------------------------------------------
// 0x5777F0 sub_5777F0 —— vector 尾部释放（4166A0）
// ------------------------------------------------------------
void /*thiscall*/ sub_5777F0(int this)
{
  int v2; // eax
  int v3; // esi

  v2 = *(uint32_t *)(this + 44);
  v3 = this + 40;
  if ( v2 != 0 )
  {
    sub_4166A0(v2, *(uint32_t *)(this + 48));
    j__free(*(void **)(v3 + 4));
  }
  *(uint32_t *)(v3 + 4) = 0;
  *(uint32_t *)(v3 + 8) = 0;
  *(uint32_t *)(v3 + 12) = 0;
  if ( *(uint32_t *)(this + 32) >= 0x10u )
    j__free(*(void **)(this + 12));
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 15;
  *(uint8_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x577850 sub_577850 —— vector 头插/重配（4015C0 + 416C40）
// ------------------------------------------------------------
void /*thiscall*/ sub_577850(uint32_t *this, char *Src)
{
  unsigned int v2; // edi
  uint32_t *v3; // ebx
  int v4; // eax
  int v5; // eax
  unsigned int v6; // ecx
  int v7; // eax
  const char *v8; // eax
  uint8_t v9[4]; // [esp+Ch] [ebp-30h] BYREF
  void *Block; // [esp+10h] [ebp-2Ch]
  int v11; // [esp+20h] [ebp-1Ch]
  unsigned int v12; // [esp+24h] [ebp-18h]
  uint32_t *v13; // [esp+28h] [ebp-14h]
  int i; // [esp+2Ch] [ebp-10h]
  int v15; // [esp+38h] [ebp-4h]

  v2 = 0;
  v13 = this;
  v3 = this + 10;
  for ( i = 0; ; i += 28 )
  {
    v4 = v3[1];
    if ( v4 == 0 || v2 >= (v3[2] - v4) / 28 )
      break;
    v5 = *(this + 11);
    v6 = *(uint32_t *)(v5 + i + 24);
    v7 = i + v5;
    if ( v6 < 0x10 )
      v8 = (const char *)(v7 + 4);
    else
      v8 = *(const char **)(v7 + 4);
    if ( strcmp(v8, Src) == 0 )
      return;
    this = v13;
    ++v2;
  }
  v12 = 15;
  v11 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(Src, strlen(Src));
  v15 = 0;
  sub_416C40(v9);
  if ( v12 >= 0x10 )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x577960 sub_577960 —— 15 行小辅助（栈帧守卫）
// ------------------------------------------------------------
int /*thiscall*/ sub_577960(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint8_t *)(this + 973) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1000) = 0;
  return 0;
}



// ============================================================
// 【分区 8】CNPathGate 传送门与杂项（0x577990-0x578000）
// ============================================================
// ------------------------------------------------------------
// 0x577990 CNPathGate__vmt14C —— CNPathGate__vmt14C 传送门路径槽（49 行）
// ------------------------------------------------------------
char /*thiscall*/ CNPathGate__vmt14C(uint8_t *this)
{
  uint32_t *v2; // eax
  int v3; // ebx
  int i; // edi

  CNRDPassiveObject__vmt14C((int)this);
  LOBYTE(v2) = *(this + 973);
  if ( (uint8_t)v2 == 0 )
  {
    v2 = *((uint32_t **)this + 29);
    if ( *((uint8_t *)v2 + 152) == 0 )
    {
      LOBYTE(v2) = *(this + 972);
      if ( (uint8_t)v2 == 0 )
      {
        v2 = *((uint32_t **)this + 245);
        v3 = v2 != nullptr ? (*((uint32_t *)this + 246) - (int)v2) >> 3 : 0;
        for ( i = 0; i < v3; ++i )
        {
          v2 = (uint32_t *)(*((uint32_t *)this + 245) + 8 * i);
          if ( v2[1] == 1 )
          {
            LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 208))(this, *v2);
          }
          else if ( v2[1] == 2 )
          {
            LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                           this,
                           i,
                           *v2,
                           0,
                           0,
                           0,
                           0);
          }
        }
      }
      *(this + 973) = 1;
    }
  }
  return (char)v2;
}



// ------------------------------------------------------------
// 0x577A30 sub_577A30 —— 传送/路径辅助（48C070/424FF0/48CC70/48CCF0，109 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_577A30(uint32_t *this, uint32_t *a2, int a3)
{
  int v4; // esi
  uint32_t *v5; // ebx
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
  v5 = this;
  if ( a2 != nullptr && *(this + 248) != 0 )
  {
    v6 = *this;
    v24 = 0;
    v23 = 0;
    v19 = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 124))(this);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 120))(v5);
    sub_48C070(&v24, &v23, v7, v19);
    v26 = 0;
    do
    {
      v8 = v24 + v4 - v5[249];
      v27 = v8;
      if ( v8 >= 0 )
      {
        v9 = a2[91];
        v10 = v9 != 0 ? (a2[92] - v9) >> 5 : 0;
        if ( v8 < 14 * v10 )
        {
          v11 = 0;
          v21 = 0;
          v28 = 0;
          do
          {
            v12 = v23 + v11 - v5[250];
            if ( v12 >= 0 && v12 < (int)(10 * (sub_424FF0(a2) + 3)) )
            {
              i = (uint32_t *)(4 * v26 + *(uint32_t *)(v28 + *(uint32_t *)(v5[248] + 40) + 4));
              v13 = sub_48CC70(v27, v12);
              if ( *i > v13 )
                sub_48CCF0(v27, v12, *(uint32_t *)(4 * v26 + *(uint32_t *)(v28 + *(uint32_t *)(v5[248] + 40) + 4)));
              if ( v26 != 0 )
              {
                if ( v26 == 13 && a3 == 1 )
                {
                  v15 = v27 + 1;
                  for ( i = (uint32_t *)(v27 + 1); ; v15 = (int)i )
                  {
                    v16 = a2[91];
                    v17 = v16 != 0 ? (a2[92] - v16) >> 5 : 0;
                    if ( v15 >= 14 * v17 )
                      break;
                    v18 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(v5[248] + 40) + v28 + 4) + 52);
                    if ( *v18 > sub_48CC70(v15, v12) )
                      sub_48CCF0(i, v12, *(uint32_t *)(*(uint32_t *)(v28 + *(uint32_t *)(*(this + 248) + 40) + 4) + 52));
                    v5 = this;
                    i = (uint32_t *)((char *)i + 1);
                  }
                }
              }
              else if ( a3 == 0 )
              {
                for ( i = nullptr; (int)i < v27; i = (uint32_t *)((char *)i + 1) )
                {
                  v20 = *(uint32_t **)(*(uint32_t *)(v5[248] + 40) + v28 + 4);
                  if ( *v20 > sub_48CC70(i, v12) )
                    sub_48CCF0(i, v12, **(uint32_t **)(v28 + *(uint32_t *)(v5[248] + 40) + 4));
                }
              }
            }
            v11 = v21 + 1;
            v14 = v28 + 16 < 480;
            ++v21;
            v28 += 16;
          }
          while ( v14 );
          v4 = v26;
        }
      }
      v26 = ++v4;
    }
    while ( v4 < 14 );
  }
}



// ------------------------------------------------------------
// 0x577C80 sub_577C80 —— 路径对象更新（144 行：4D0B30/507690/42FCB0/431920/4319E0/48D630）
// ------------------------------------------------------------
char /*thiscall*/ sub_577C80(char *this, int a2)
{
  int v3; // ebx
  unsigned int v4; // eax
  int v5; // ecx
  int v6; // ecx
  const char *v7; // edi
  int v8; // eax
  int v9; // edx
  int v10; // ebx
  void *v11; // eax
  int v12; // eax
  bool v13; // cf
  const char *v14; // eax
  void *v15; // eax
  int v16; // eax
  int v17; // ebx
  int v18; // edi
  bool v19; // cc
  uint32_t v21[2]; // [esp+8h] [ebp-128h] BYREF
  void *Block; // [esp+10h] [ebp-120h]
  int v23; // [esp+14h] [ebp-11Ch]
  unsigned int v24; // [esp+18h] [ebp-118h]
  int v25; // [esp+1Ch] [ebp-114h]
  char Buffer[256]; // [esp+20h] [ebp-110h] BYREF
  int v27; // [esp+120h] [ebp-10h]
  int v28; // [esp+12Ch] [ebp-4h]
  int v29; // [esp+138h] [ebp+8h]

  v3 = 0;
  v27 = dword_796E50;
  LOBYTE(v4) = a2 != 0;
  *(this + 972) = a2 != 0;
  v5 = *((uint32_t *)this + 178);
  if ( v5 != 0 )
  {
    v4 = (*((uint32_t *)this + 179) - v5) >> 2;
    v25 = v4;
  }
  else
  {
    v25 = 0;
  }
  v29 = 0;
  if ( v25 > 0 )
  {
    v24 = 1;
    while ( 1 )
    {
      v6 = *((uint32_t *)this + 87);
      if ( v6 == 0 )
        return v4;
      v4 = (*((uint32_t *)this + 88) - v6) >> 2;
      if ( v4 <= v24 )
        return v4;
      v7 = (const char *)sub_41ACF0(*((uint32_t *)this + 178) + 4 * v3);
      v8 = *((uint32_t *)this + 87);
      v9 = *(uint32_t *)(8 * v3 + v8);
      v10 = *(uint32_t *)(8 * v3 + v8 + 4);
      v23 = v9;
      if ( strstr(v7, ".til") != nullptr )
      {
        if ( *((uint32_t *)this + 248) == 0 )
        {
          v11 = operator new(0x34u);
          Block = v11;
          v28 = 0;
          if ( v11 != nullptr )
            v12 = sub_4D0B30(v11);
          else
            v12 = 0;
          *((uint32_t *)this + 248) = v12;
          v13 = *((uint32_t *)this + 96) < 0x10u;
          v28 = -1;
          if ( v13 )
            v14 = this + 364;
          else
            v14 = *((const char **)this + 91);
          sprintf(Buffer, "%s%s", v14, v7);
          sub_507690(*((uint32_t *)this + 248), (char)Buffer);
          *((uint32_t *)this + 249) = v23;
          *((uint32_t *)this + 250) = v10;
        }
        goto LABEL_33;
      }
      v15 = (void *)sub_42FCB0(228);
      Block = v15;
      if ( v10 == -1 )
      {
        v28 = 1;
        if ( v15 != nullptr )
        {
          if ( *((uint32_t *)this + 96) < 0x10u )
            v16 = sub_431920((uint8_t)this + 108, (char)v7, 1);
          else
            v16 = sub_431920(*((uint32_t *)this + 91), (char)v7, 1);
          goto LABEL_28;
        }
      }
      else
      {
        v28 = 2;
        if ( v15 != nullptr )
        {
          if ( *((uint32_t *)this + 96) < 0x10u )
            v16 = sub_4319E0((int)v15, 0, v10, this + 364, v7, 1);
          else
            v16 = sub_4319E0((int)v15, 0, v10, *((const char **)this + 91), v7, 1);
          goto LABEL_28;
        }
      }
      v16 = 0;
LABEL_28:
      v17 = v23;
      v28 = -1;
      v18 = v16;
      if ( v23 == 0 || v23 == 1 && *(this + 972) == 0 )
        (*(void (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
          this,
          v29,
          v16,
          0,
          0,
          0,
          0);
      v21[0] = v18;
      v21[1] = v17;
      sub_48D630(v21);
LABEL_33:
      LOBYTE(v4) = v29 + 1;
      v19 = ++v29 < v25;
      v24 += 2;
      if ( !v19 )
        return v4;
      v3 = v29;
    }
  }
  return v4;
}


// ------------------------------------------------------------
// 0x577F30 sub_577F30 —— 路径/掉落前置（42AF90/657740/4D10A0）
// ------------------------------------------------------------
void /*thiscall*/ sub_577F30(uint32_t *this)
{
  int v2; // ecx
  int i; // esi
  void **v4; // ecx
  void *v5; // esi
  int v6; // [esp+Ch] [ebp-8h]
  int v7; // [esp+10h] [ebp-4h]

  v2 = *(this + 245);
  if ( v2 != 0 )
    v7 = (*(this + 246) - v2) >> 3;
  else
    v7 = 0;
  for ( i = 0; i < v7; ++i )
  {
    v4 = *(void ***)(*(this + 245) + 8 * i);
    if ( v4 != nullptr )
    {
      v6 = *(uint32_t *)(*(this + 245) + 8 * i);
      sub_42AF90(v4);
      sub_657740(v6, 228);
    }
    *(uint32_t *)(8 * i + *(this + 245)) = 0;
  }
  v5 = (void *)*(this + 248);
  if ( v5 != nullptr )
  {
    sub_4D10A0(*(this + 248));
    j__free(v5);
  }
  *(this + 248) = 0;
}



// ------------------------------------------------------------
// 0x577FF0 sub_577FF0 —— 10 行小函数
// ------------------------------------------------------------
void /*thiscall*/ sub_577FF0(uint32_t *this)
{
  *(this + 1) = 1;
}



// ============================================================
// 【分区 9】CNRDStackable 可堆叠物品对象（0x578000-0x5785E0）
// 覆写槽: vmt8C=更新、vmt88/vmt78/vmt74/vmt70=外观与数量表现；
// 数量/外观计算 0x578240（4F3360/4B2BF0）。
// ============================================================
// ------------------------------------------------------------
// 0x578000 CNRDStackable__vmt8C —— CNRDStackable__vmt8C 更新槽（41C210）
// ------------------------------------------------------------
int /*thiscall*/ CNRDStackable__vmt8C(uint32_t *this)
{
  int result; // eax

  switch ( *(this + 37) )
  {
    case 0:
      if ( (uint8_t)sub_41C210(dword_8F7A24) == 0
        || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1196))(dword_8F7C04) != 0
        || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 724))(dword_8F7C04) != 0 )
      {
        goto LABEL_10;
      }
      result = 1;
      break;
    case 1:
    case 6:
      switch ( *(this + 3) )
      {
        case 0xFC9:
        case 0xFCA:
        case 0xFCB:
        case 0xFCC:
        case 0xFCD:
        case 0xFCE:
        case 0xFCF:
        case 0xFD0:
        case 0xFD1:
        case 0xFD2:
        case 0xFD3:
        case 0xFD4:
        case 0xFEF:
        case 0xFF0:
        case 0xFF1:
        case 0xFF2:
        case 0xFF7:
        case 0xFF8:
        case 0xFF9:
        case 0xFFA:
        case 0xFFB:
        case 0xFFC:
        case 0xFFD:
        case 0xFFE:
        case 0xFFF:
        case 0x1000:
        case 0x1001:
        case 0x1002:
        case 0x1003:
        case 0x1004:
        case 0x1005:
        case 0x1006:
          goto LABEL_7;
        default:
          goto LABEL_10;
      }
    case 2:
    case 5:
    case 7:
      goto LABEL_7;
    case 3:
    case 4:
      if ( (uint8_t)sub_41C210(dword_8F7A24) == 0
        || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1272))(dword_8F7C04) == 0 )
      {
        goto LABEL_10;
      }
LABEL_7:
      result = 2;
      break;
    default:
LABEL_10:
      result = 0;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x578100 CNRDStackable__vmt88 —— CNRDStackable__vmt88 槽位（41ACF0 粒子挂载）
// ------------------------------------------------------------
int /*thiscall*/ CNRDStackable__vmt88(uint32_t *this, int *a2, int a3, int a4)
{
  int v5; // ebx
  int v6; // eax
  int v7; // esi
  int v8; // eax

  if ( *(this + 37) == 0
    && ((int *)dword_8F7C04 == a2
     || *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 132))(this) + 12) == 1
     && (v5 = (*(int (/*thiscall*/ **)(int *))(*a2 + 376))(a2)) == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04
                                                                                            + 376))(dword_8F7C04)) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 100))(this);
  }
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 16))(this);
  v7 = *a2;
  v8 = sub_41ACF0(v6 + 80);
  return (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v7 + 212))(a2, v8, -1, 0, 0);
}



// ------------------------------------------------------------
// 0x578180 CNRDStackable__vmt78 —— CNRDStackable__vmt78 槽位（4B1BA0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDStackable__vmt78(uint32_t *this)
{
  int v1; // ecx
  uint32_t *v3; // [esp+0h] [ebp-4h] BYREF

  v3 = this;
  if ( *(this + 38) == -1 )
  {
    sub_4B1BA0(&v3, this + 3);
    v1 = dword_9B8DBC;
  }
  else
  {
    sub_4B1BA0(&v3, this + 38);
    v1 = dword_9B8DC8;
  }
  if ( v3 == (uint32_t *)v1 )
    return 0;
  else
    return v3[4];
}



// ------------------------------------------------------------
// 0x5781E0 CNRDStackable__vmt74 —— CNRDStackable__vmt74 槽位（4B1BA0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDStackable__vmt74(uint32_t *this)
{
  int v1; // ecx
  uint32_t *v3; // [esp+0h] [ebp-4h] BYREF

  v3 = this;
  if ( *(this + 38) == -1 )
  {
    sub_4B1BA0(&v3, this + 3);
    v1 = dword_9B8DBC;
  }
  else
  {
    sub_4B1BA0(&v3, this + 38);
    v1 = dword_9B8DC8;
  }
  if ( v3 == (uint32_t *)v1 )
    return 0;
  else
    return v3[5];
}



// ------------------------------------------------------------
// 0x578240 sub_578240 —— 堆叠物数量/外观计算（4F3360 物品数据 + 4B2BF0 表现，66 行）
// ------------------------------------------------------------
int **/*thiscall*/ sub_578240(int ***this, int **a2, int *a3, int *a4)
{
  int *v4; // ebx
  int *v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int *v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(int **)v7 && a4 == (int *)v7 )
  {
    sub_4F3360(*(void **)(v7 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    v8 = *(this + 1);
    *(this + 2) = nullptr;
    *v8 = v8;
    (*(this + 1))[2] = (int *)*(this + 1);
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
        if ( *((uint8_t *)v5 + 25) == 0 )
        {
          v11 = (int **)v5[2];
          if ( *((uint8_t *)v11 + 25) != 0 )
          {
            for ( i = (int *)v5[1]; *((uint8_t *)i + 25) == 0; i = (int *)i[1] )
            {
              if ( v5 != (int *)i[2] )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = (int *)v5[2];
            for ( j = *v11; *((uint8_t *)j + 25) == 0; j = (int *)*j )
              v5 = j;
          }
        }
        sub_4B2BF0(&a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x578300 sub_578300 —— 转发 578240
// ------------------------------------------------------------
int /*thiscall*/ sub_578300(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_578240((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x578340 sub_578340 —— 堆叠物初始化/绘制（106 行：41B0D0/418DD0/4ED3F0/41FFE0/4206D0）
// ------------------------------------------------------------
int /*thiscall*/ sub_578340(int this, const char *ArgList)
{
  uint32_t *v3; // eax
  uint32_t *v4; // ebx
  int result; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edi
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

  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84D4 + 4))(dword_8F84D4, ArgList);
  v4 = v3;
  if ( v3 == nullptr )
    return off_77F3FC("STACKABLE CREATE FAIL! FILENAME[%s]", ArgList);
  *(uint32_t *)(this + 12) = *v3;
  sub_41B0D0(v3 + 1);
  sub_41B0D0(v4 + 2);
  sub_41B0D0(v4 + 3);
  sub_41B0D0(v4 + 4);
  *(uint32_t *)(this + 32) = v4[5];
  *(uint32_t *)(this + 36) = v4[6];
  *(uint32_t *)(this + 44) = v4[9];
  *(uint32_t *)(this + 60) = v4[10];
  *(uint32_t *)(this + 48) = v4[11];
  *(uint32_t *)(this + 52) = v4[12];
  *(uint32_t *)(this + 56) = v4[13];
  *(uint32_t *)(this + 64) = v4[14];
  *(uint8_t *)(this + 68) = *((uint8_t *)v4 + 60);
  *(uint8_t *)(this + 69) = *((uint8_t *)v4 + 61);
  *(uint8_t *)(this + 70) = *((uint8_t *)v4 + 62);
  *(uint8_t *)(this + 71) = *((uint8_t *)v4 + 63);
  *(uint32_t *)(this + 8) = v4[16];
  *(uint32_t *)(this + 72) = v4[17];
  if ( strcmp((const char *)sub_41ACF0(v4 + 20), szPassword) != 0 )
  {
    v6 = sub_41ACF0(v4 + 20);
    v15 = v4[21];
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v6);
    *(uint32_t *)(this + 76) = sub_418DD0(v15);
  }
  if ( strcmp((const char *)sub_41ACF0(v4 + 22), szPassword) == 0 )
  {
    v8 = this;
  }
  else
  {
    v7 = sub_41ACF0(v4 + 22);
    v16 = v4[23];
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v7);
    v8 = this;
    *(uint32_t *)(this + 80) = sub_418DD0(v16);
  }
  sub_41B0D0(v4 + 26);
  *(uint32_t *)(v8 + 92) = v4[8];
  sub_4ED3F0(v8 + 96, (int)(v4 + 30));
  v9 = 0;
  ArgLista = 0;
  while ( 1 )
  {
    v10 = v4[35];
    if ( v10 == 0 || v9 >= (v4[36] - v10) >> 2 )
      break;
    v11 = *(uint32_t *)(v8 + 116);
    v12 = v8 + 112;
    v17 = v10 + 4 * v9;
    if ( v11 != 0 )
      v13 = (*(uint32_t *)(v8 + 120) - v11) >> 2;
    else
      v13 = 0;
    if ( v11 != 0 && v13 < (*(uint32_t *)(v8 + 124) - v11) >> 2 )
    {
      v14 = *(uint32_t **)(v8 + 120);
      sub_41FFE0(v14, 1, v17);
      *(uint32_t *)(v12 + 8) = v14 + 1;
      v8 = this;
      v9 = ++ArgLista;
    }
    else
    {
      sub_4206D0(v8 + 112, *(uint32_t *)(v8 + 120), 1u, v17);
      v9 = ++ArgLista;
    }
  }
  sub_41B0D0(v4 + 29);
  *(uint32_t *)(v8 + 148) = v4[25];
  *(uint32_t *)(v8 + 152) = v4[18];
  *(uint8_t *)(v8 + 160) = *((uint8_t *)v4 + 76);
  result = v4[24];
  *(uint32_t *)(v8 + 156) = result;
  return result;
}



// ------------------------------------------------------------
// 0x578580 CNRDStackable__vmt70 —— CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDStackable__vmt70(uint32_t *this, int a2)
{
  int v3; // esi
  uint32_t *result; // eax
  uint32_t *v5; // [esp-4h] [ebp-14h]
  uint32_t *v6; // [esp+Ch] [ebp-4h]

  v6 = this + 38;
  if ( *(this + 38) == -1 )
  {
    v3 = sub_699000((int)&unk_9B0C70);
    v5 = this + 3;
  }
  else
  {
    v3 = sub_699000((int)&unk_9B0C70);
    v5 = v6;
  }
  result = (uint32_t *)sub_4B44E0(v5);
  *result = a2;
  result[1] = a2 + v3;
  return result;
}



// ============================================================
// 【分区 10】地面掉落物/金币（0x5785E0-0x5787A0）
// 金币绘制 0x578680：资源 Item/FieldImage.img，事件标签 GOLD_DROP1/GOLD_DROP2。
// ============================================================
// ------------------------------------------------------------
// 0x5785E0 sub_5785E0 —— 地面掉落物初始化（433B00 对象登记）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5785E0(uint32_t *this)
{
  uint32_t *v2; // eax

  v2 = sub_433B00();
  *(this + 1) = v2;
  *((uint8_t *)v2 + 25) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x578610 sub_578610 —— 掉落物动画驱动（442D00 + 578340）
// ------------------------------------------------------------
int /*thiscall*/ sub_578610(void *this, int ArgList)
{
  int v2; // edi
  const char *v4; // eax
  int *v6; // [esp+8h] [ebp-4h] BYREF

  v2 = ArgList;
  sub_442D00(&dword_9B6C60, &v6, &ArgList);
  if ( v6 == (int *)dword_9B6C64 )
    return off_77F3FC("STACKABLE CREATE FAIL! INDEX %d", v2);
  v4 = (unsigned int)v6[10] < 0x10 ? (const char *)(v6 + 5) : (const char *)v6[5];
  if ( v4 == nullptr )
    return off_77F3FC("STACKABLE CREATE FAIL! INDEX %d", v2);
  else
    return sub_578340((int)this, v4);
}



// ------------------------------------------------------------
// 0x578680 sub_578680 —— 金币掉落绘制：资源 Item/FieldImage.img，事件标签 GOLD_DROP1/GOLD_DROP2（418DD0 取精灵 + 41BFE0/41A590）
// ------------------------------------------------------------
void /*thiscall*/ sub_578680(int this, unsigned int a2)
{
  char *v3; // eax
  char *v4; // eax
  int v5; // edx
  int v6; // [esp-4h] [ebp-Ch]

  *(uint32_t *)(this + 12) = 0;
  v3 = sub_422E70(424);
  sub_41BFE0((void **)(this + 16), v3);
  v4 = sub_422E70(424);
  sub_41BFE0((void **)(this + 24), v4);
  *(uint32_t *)(this + 64) = 0;
  sub_41A590(this + 132, v5, a2);
  if ( a2 >= 0x64 )
  {
    if ( a2 >= 0x1F4 )
      v6 = 25;
    else
      v6 = 27;
    (*(void (/*stdcall*/ **)(const char *))(*(uint32_t *)dword_8F84B8 + 60))("Item/FieldImage.img");
    *(uint32_t *)(this + 80) = sub_418DD0(v6);
    sub_41BFE0((void **)(this + 84), "GOLD_DROP2");
  }
  else
  {
    (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Item/FieldImage.img");
    *(uint32_t *)(this + 80) = sub_418DD0(26);
    sub_41BFE0((void **)(this + 84), "GOLD_DROP1");
  }
}



// ------------------------------------------------------------
// 0x578740 sub_578740 —— 粒子/动画辅助（41A590）
// ------------------------------------------------------------
int /*fastcall*/ sub_578740(int a1, int a2)
{
  *(uint32_t *)(a1 + 96) = 289;
  *(uint32_t *)(a1 + 972) = 0;
  *(uint8_t *)(a1 + 976) = 0;
  *(uint8_t *)(a1 + 977) = 0;
  *(uint32_t *)(a1 + 980) = 0;
  *(uint8_t *)(a1 + 984) = 0;
  *(uint8_t *)(a1 + 1000) = 0;
  return sub_41A590(a1 + 1016, a2, 0xFFFF);
}



// ------------------------------------------------------------
// 0x578780 sub_578780 —— 17 行小辅助（表现参数）
// ------------------------------------------------------------
int /*thiscall*/ sub_578780(uint32_t *this)
{
  int v2; // ecx
  int result; // eax

  v2 = *(this + 243);
  if ( v2 != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 4))(v2, 1);
  *(this + 243) = 0;
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
unsigned int /*thiscall*/ CNRDItemObject__vmtC(int this)
{
  int v2; // eax
  int v3; // edx
  unsigned int result; // eax
  uint32_t *v5; // ecx

  CNRDPassiveObject__vmtC((int *)this);
  v2 = *(uint32_t *)this;
  *(uint8_t *)(this + 976) = 0;
  (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t, int))(v2 + 284))(this, 0, -16715521, 0, 1);
  v3 = *(uint32_t *)this;
  *(uint8_t *)(this + 984) = 0;
  result = ((*(int (/*thiscall*/ **)(int))(v3 + 128))(this) <= 0) + 1;
  v5 = *(uint32_t **)(this + 116);
  if ( v5 != nullptr )
  {
    result = sub_460110(v5, this, result);
    *(uint8_t *)(this + 1044) = 0;
  }
  else
  {
    *(uint8_t *)(this + 1044) = 0;
    *(uint32_t *)(this + 108) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x578810 CNRDItemObject__vmt144 —— CNRDItemObject__vmt144 绘制前置槽（25 行）
// ------------------------------------------------------------
void /*thiscall*/ CNRDItemObject__vmt144(int this, int a2, int a3, int a4, int a5)
{
  int v5; // eax

  if ( (uint8_t)a2 != 0 )
  {
    if ( *(uint8_t *)(this + 976) != 0 )
    {
      v5 = *(uint32_t *)(this + 972);
      if ( v5 != 0 )
        (*(void (**)(void))(*(uint32_t *)v5 + 16))();
    }
    nullsub_2(a2, a3, a4, a5);
  }
  else
  {
    nullsub_2(0, a3, a4, a5);
  }
}



// ------------------------------------------------------------
// 0x578870 sub_578870 —— 掉落物字符串初始化（41A590 + 698F90）
// ------------------------------------------------------------
char /*fastcall*/ sub_578870(uint8_t *a1, int a2, int a3, int a4)
{
  char result; // al

  result = a3;
  if ( a3 != 0xFFFF )
  {
    sub_41A590((unsigned int)(a1 + 1016), a2, a3);
    a1[1000] = 1;
    a1[1001] = 0;
    a1[1002] = 0;
    return sub_698F90((int)(a1 + 988), a4, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x5788B0 sub_5788B0 —— 掉落物表现（41A5E0/422E70/43BEE0）
// ------------------------------------------------------------
char /*thiscall*/ sub_5788B0(uint32_t *this, int a2)
{
  unsigned int v3; // edi
  char *v4; // eax
  int v6; // [esp-4h] [ebp-210h]
  char Buffer[512]; // [esp+8h] [ebp-204h] BYREF
  int v8; // [esp+208h] [ebp-4h]

  v3 = (unsigned int)(this + 254);
  v8 = dword_796E50;
  if ( sub_41A5E0((unsigned int)(this + 254)) == 0xFFFF || sub_41A5E0(v3) == a2 )
    return 1;
  v6 = *(this + 253) / 1000;
  v4 = sub_422E70(2015);
  sprintf(Buffer, v4, v6);
  sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
  return 0;
}



// ------------------------------------------------------------
// 0x578960 CNRDItemObject__vmt14C —— CNRDItemObject__vmt14C 主状态（148 行）：ITEM_DROP 标签——落地弹跳/旋转/拾取判定（460110/699000/4600B0）
// ------------------------------------------------------------
void /*thiscall*/ sub_578960(uint32_t *this)
{
  bool v2; // cc
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  void *v12; // ecx
  int v13; // edi
  int v14; // edx
  void *v15; // eax
  bool v16; // zf
  int v17; // ecx
  int v18; // edi
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // ebx
  int v24; // eax
  int v25; // eax
  int v26; // edx
  int v27; // edi
  int v28; // edx
  int v29; // [esp-Ch] [ebp-40h]
  int v30; // [esp-8h] [ebp-3Ch]
  uint8_t v31[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  int v33; // [esp+1Ch] [ebp-18h] BYREF
  int v34; // [esp+20h] [ebp-14h] BYREF
  float v35; // [esp+24h] [ebp-10h]
  int v36; // [esp+30h] [ebp-4h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) <= 0;
  v3 = *(this + 27);
  if ( v2 )
  {
    if ( v3 != 2 )
      sub_460110(this, 2);
    if ( sub_699000((int)(this + 16)) >= *(this + 245) )
    {
      v7 = dword_8F82B8;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F82B8 + 12))(dword_8F82B8, 0);
      v8 = *(uint32_t *)v7;
      v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v9 + 1);
      v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v10);
      (*(void (/*thiscall*/ **)(int, int))(v8 + 40))(v7, v11);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v7 + 92))(v7, v31);
      v12 = (void *)*(this + 29);
      v36 = 0;
      sub_4600B0(v12, 2, 0, (int)v31);
      v13 = sub_699000((int)(this + 16));
      v14 = rand() % 1000;
      v15 = Block;
      v16 = Block == nullptr;
      v36 = -1;
      *(this + 245) = v13 + v14 + 1500;
      if ( !v16 )
        j__free(v15);
    }
    if ( *((uint8_t *)this + 984) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 272))(this, 0, 0);
      v17 = *(this + 243);
      if ( v17 != 0 )
      {
        v18 = *this;
        v19 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)v17 + 56))(v17, -1, 0, 0);
        (*(void (/*thiscall*/ **)(uint32_t *, int))(v18 + 212))(this, v19);
      }
      *((uint8_t *)this + 984) = 0;
      *((uint8_t *)this + 1044) = 1;
      *((uint8_t *)this + 1045) = 0;
      *((uint8_t *)this + 1046) = 0;
      sub_698F90((int)(this + 258), 1000, 0);
    }
    if ( *((uint8_t *)this + 1044) != 0 )
    {
      v35 = *((float *)this + 264);
      v20 = sub_699000((int)(this + 258));
      if ( v20 >= SLODWORD(v35) && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      {
        v35 = *(float *)this;
        v21 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(LODWORD(v35) + 124))(this, 0);
        v22 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v21);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(LODWORD(v35) + 136))(this, v22) == 0 )
        {
          v23 = *this;
          v24 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 124))(this, 300, 1, 5);
          v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v24);
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int *, int *, int))(v23 + 140))(this, &v33, &v34, v25) != 0 )
          {
            off_77F3FC((char *)&byte_726738);
            v26 = *this;
            v30 = v34;
            v29 = v33;
            *((uint8_t *)this + 1044) = 0;
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(v26 + 108))(this, v29, v30, 0);
          }
          else
          {
            off_77F3FC((char *)&byte_7266E8);
            *((uint8_t *)this + 1045) = 0;
            *((uint8_t *)this + 1046) = 0;
            sub_698F90((int)(this + 258), 1000, 0);
          }
        }
      }
    }
  }
  else
  {
    if ( v3 != 1 )
      sub_460110(this, 1);
    v4 = sub_699000((int)(this + 9));
    v5 = *(uint32_t *)(*(this + 28) + 104);
    v35 = (double)v4 * 0.0099999998;
    if ( v5 != 0 )
    {
      v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 16))(v5) + 72);
      if ( v6 < 90 || v6 > 270 )
        v35 = -v35;
    }
    (*(void (/*thiscall*/ **)(uint32_t *, int, float))(*this + 272))(this, 1, COERCE_FLOAT(LODWORD(v35)));
    if ( *((uint8_t *)this + 984) == 0 )
    {
      sub_432EA0("ITEM_DROP", -1, 0, 0);
      *((uint8_t *)this + 984) = 1;
    }
  }
  if ( *((uint8_t *)this + 1000) != 0 )
  {
    v27 = *(this + 253);
    if ( sub_699000((int)(this + 247)) >= v27 )
      sub_41A590((unsigned int)(this + 254), v28, 0xFFFF);
  }
}


// ------------------------------------------------------------
// 0x578C40 sub_578C40 —— 掉落物物理步进（42AF90/657740/42FCB0/498530/4924C0：重力/地面碰撞）
// ------------------------------------------------------------
int /*thiscall*/ sub_578C40(void ***this, void **a2)
{
  void **v3; // ebx
  void **v5; // eax
  int result; // eax
  void **v7; // eax
  int v8; // eax
  int v9; // ebx
  int v10; // [esp+20h] [ebp+8h]

  v3 = *(this + 34);
  *(this + 243) = a2;
  if ( v3 != nullptr )
  {
    sub_42AF90(v3);
    sub_657740(v3, 228);
  }
  v5 = *this;
  *(this + 34) = nullptr;
  result = ((int (/*thiscall*/ *)(void ***, uint32_t))v5[49])(this, 0);
  if ( a2 != nullptr )
  {
    result = (*((int (/*thiscall*/ **)(void **))*a2 + 4))(a2);
    if ( *(uint32_t *)(result + 72) != 0 )
    {
      v10 = sub_42FCB0(228);
      v7 = nullptr;
      if ( v10 != 0 )
      {
        v8 = (*((int (/*thiscall*/ **)(void **))*a2 + 4))(a2);
        v7 = (void **)sub_498530(*(uint32_t *)(v8 + 72));
      }
      *(this + 34) = v7;
      v9 = sub_4924C0(0);
      *(uint32_t *)(v9 + 12) = *(uint32_t *)(*(uint32_t *)((*((int (/*thiscall*/ **)(void **))*a2 + 4))(a2) + 72) + 36) / -2;
      *(uint32_t *)(v9 + 16) = *(uint32_t *)(*(uint32_t *)((*((int (/*thiscall*/ **)(void **))*a2 + 4))(a2) + 72) + 40) / -2;
      return ((int (/*thiscall*/ *)(void ***, uint32_t))(*this)[49])(this, *(this + 34));
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x578D50 sub_578D50 —— 掉落物更新（578C40 物理 + 4D33A0/445D00/445B90/4A0B60 表现）
// ------------------------------------------------------------
int /*thiscall*/ sub_578D50(int this, void **a2, int a3, int a4)
{
  int v5; // edi
  int result; // eax
  char *v7; // edi
  char *v8; // eax

  *(uint32_t *)(this + 316) = 1;
  *(uint32_t *)(this + 320) = 1;
  sub_578C40((void ***)this, a2);
  *(uint8_t *)(this + 700) = 0;
  *(uint8_t *)(this + 701) = 1;
  *(uint32_t *)(this + 108) = 1;
  v5 = sub_699000(this + 64);
  *(uint32_t *)(this + 980) = v5 + rand() % 1000 + 1500;
  if ( byte_9B8DD0 == 0 )
  {
    byte_9B8DE4 = 1;
    dword_9B8DE7 = 400;
    dword_9B8DEB = 400;
    dword_9B8E1C = 1500;
    byte_9B8E31 = 2;
    dword_9B8DE0 = 1;
    byte_9B8DD0 = 1;
  }
  result = a3;
  v7 = nullptr;
  if ( a3 != 0 )
  {
    dword_9B8E24 = sub_4D33A0(a3) % 20 + 65;
    dword_9B8E20 = a4;
    v8 = (char *)sub_445D00(156);
    if ( v8 != nullptr )
      v7 = sub_445B90(v8);
    (*(void (/*thiscall*/ **)(char *, void *))(*(uint32_t *)v7 + 12))(v7, &unk_9B8DD8);
    (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)v7 + 4))(v7, 0);
    sub_4A0B60(v7);
    result = *(uint32_t *)(this + 112);
    *(uint32_t *)(result + 112) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x578E90 sub_578E90 —— 掉落物成员访问（41A580）
// ------------------------------------------------------------
int /*thiscall*/ sub_578E90(int this)
{
  sub_41A580(this + 282);
  sub_41A580(this + 268);
  `eh vector destructor iterator'((void *)(this + 240), 0xEu, 2, sub_432D10);
  `eh vector destructor iterator'((void *)(this + 184), 0x1Cu, 2, sub_501490);
  `eh vector destructor iterator'((void *)(this + 128), 0x1Cu, 2, sub_501490);
  sub_41A580(this + 112);
  sub_41A580(this + 98);
  sub_41A580(this + 84);
  sub_41A580(this + 70);
  `eh vector destructor iterator'((void *)(this + 42), 0xEu, 2, sub_432D10);
  sub_41A580(this + 28);
  return sub_41A580(this + 8);
}



// ------------------------------------------------------------
// 0x578F90 sub_578F90 —— 物品说明请求（406D00）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_578F90(uint32_t *this)
{
  uint32_t *v2; // ecx
  unsigned int v3; // edx
  uint32_t *v4; // edi
  uint32_t *v5; // ebx
  uint8_t v7[4]; // [esp+Ch] [ebp-14h] BYREF
  uint32_t *v8; // [esp+10h] [ebp-10h]
  int v9; // [esp+1Ch] [ebp-4h]

  v2 = this + 4;
  v2[6] = 15;
  v2[5] = 0;
  v8 = this;
  *((uint8_t *)v2 + 4) = 0;
  v9 = 0;
  *this = -1;
  *(this + 1) = -1;
  *(this + 2) = -1;
  *(this + 3) = -1;
  v3 = v2[6];
  v4 = v2 + 1;
  if ( v3 < 0x10 )
    v5 = v2 + 1;
  else
    v5 = (uint32_t *)*v4;
  if ( v3 >= 0x10 )
    v4 = (uint32_t *)*v4;
  sub_406D00(v7, v4, (char *)v5 + v2[5]);
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
uint32_t */*thiscall*/ sub_579020(uint32_t *this)
{
  char *v2; // ecx

  v2 = (char *)(this + 3);
  *((uint32_t *)v2 + 6) = 15;
  *((uint32_t *)v2 + 5) = 0;
  v2[4] = 0;
  *this = 4;
  *(this + 1) = -1;
  *((uint8_t *)this + 8) = 0;
  sub_4015C0((void *)szPassword, 0);
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x5790A0 sub_5790A0 —— 角色对象辅助 2（41A630 + 4C1BA0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5790A0(uint32_t *this)
{
  uint32_t *v2; // edi

  v2 = this + 2;
  sub_41A630((unsigned int)(this + 2));
  *v2 = &vftbl_clong;
  sub_41A630((unsigned int)(this + 7));
  *(this + 7) = &vftbl_clong;
  `eh vector constructor iterator'((char *)this + 42, 0xEu, 2, sub_401040, sub_432D10);
  sub_41A630((unsigned int)this + 70);
  *(uint32_t *)((char *)this + 70) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 21));
  *(this + 21) = &vftbl_clong;
  sub_41A630((unsigned int)this + 98);
  *(uint32_t *)((char *)this + 98) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 28));
  *(this + 28) = &vftbl_clong;
  `eh vector constructor iterator'(this + 32, 0x1Cu, 2, sub_40C120, sub_501490);
  `eh vector constructor iterator'(this + 46, 0x1Cu, 2, sub_40C120, sub_501490);
  `eh vector constructor iterator'(this + 60, 0xEu, 2, sub_401040, sub_432D10);
  sub_41A630((unsigned int)(this + 67));
  *(this + 67) = &vftbl_clong;
  sub_41A630((unsigned int)this + 282);
  *(uint32_t *)((char *)this + 282) = &vftbl_clong;
  sub_4C1BA0(this);
  return this;
}



// ------------------------------------------------------------
// 0x579200 sub_579200 —— 角色构造前置（4015C0/401740）
// ------------------------------------------------------------
void /*noreturn*/ sub_579200()
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
// 0x579270 sub_579270 —— 角色对象初始化（85 行：4A49B0/4A3450/433B00/4CE550/4BA8A0 部件与动画装配）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_579270(uint32_t *this, char ArgList)
{
  uint32_t *v3; // eax
  int i; // ecx
  uint32_t *v5; // eax

  sub_4A49B0();
  *this = &vftbl_IRDCharacter;
  sub_579020(this + 1787);
  *(this + 1803) = 0;
  v3 = this + 1808;
  for ( i = 4; i != 0; --i )
  {
    *(v3 - 4) = 0;
    *v3++ = 0;
  }
  *(this + 1812) = 0;
  *(this + 1813) = 0;
  *(this + 1814) = 0;
  *(this + 1815) = 0;
  *(this + 1845) = 15;
  *(this + 1844) = 0;
  *((uint8_t *)this + 7360) = 0;
  sub_4A3450(this + 1816);
  v5 = sub_433B00();
  *(this + 1855) = v5;
  *((uint8_t *)v5 + 25) = 1;
  *(uint32_t *)(*(this + 1855) + 4) = *(this + 1855);
  *(uint32_t *)*(this + 1855) = *(this + 1855);
  *(uint32_t *)(*(this + 1855) + 8) = *(this + 1855);
  *(this + 1856) = 0;
  sub_4CE550(this + 1858);
  *(this + 1904) = 0;
  *(this + 1905) = 0;
  *(this + 1906) = 0;
  *(this + 1908) = 0;
  *(this + 1909) = 0;
  *(this + 1910) = 0;
  *(this + 1912) = 0;
  *(this + 1913) = 0;
  *(this + 1914) = 0;
  *(this + 1916) = 0;
  *(this + 1917) = 0;
  *(this + 1918) = 0;
  *(this + 1920) = 0;
  *(this + 1921) = 0;
  *(this + 1922) = 0;
  *(this + 1931) = 15;
  *(this + 1930) = 0;
  *((uint8_t *)this + 7704) = 0;
  *(this + 1939) = 15;
  *(this + 1938) = 0;
  *((uint8_t *)this + 7736) = 0;
  *(this + 1970) = 15;
  *(this + 1969) = 0;
  *((uint8_t *)this + 7860) = 0;
  *(this + 1974) = 0;
  *(this + 1975) = 0;
  *(this + 1976) = 0;
  *(this + 1989) = 15;
  *(this + 1988) = 0;
  *((uint8_t *)this + 7936) = 0;
  sub_578F90(this + 2002);
  *((uint8_t *)this + 8092) = 0;
  *(this + 2022) = &vftbl_nengine__CNTimer;
  *(this + 2024) = 0;
  *((uint8_t *)this + 8100) = 1;
  *((uint8_t *)this + 8102) = 0;
  *((uint8_t *)this + 8101) = 0;
  *(this + 2028) = 0;
  *(this + 2027) = 0;
  *(this + 2026) = 0;
  *(this + 2030) = 0;
  *(this + 2031) = 0;
  *(this + 2032) = 0;
  sub_4AEDD0(this);
  sub_4BA8A0(ArgList);
  return this;
}



// ------------------------------------------------------------
// 0x5794A0 IRDCharacter__vmt424 —— IRDCharacter__vmt424 默认虚槽桩（11 行 return）
// ------------------------------------------------------------
char /*thiscall*/ IRDCharacter__vmt424(uint8_t *this, char a2)
{
  *(this + 7510) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x5794B0 IRDCharacter__vmt428 —— IRDCharacter__vmt428 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt428(uint8_t *this)
{
  return *(this + 7510);
}



// ------------------------------------------------------------
// 0x5794F0 IRDCharacter__vmt45C —— IRDCharacter__vmt45C 默认虚槽桩（11 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt45C(uint32_t *this, int a2)
{
  *(this + 1923) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x579500 IRDCharacter__vmt460 —— IRDCharacter__vmt460 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt460(uint32_t *this)
{
  return *(this + 1923);
}



// ------------------------------------------------------------
// 0x579530 IRDCharacter__vmt380 —— IRDCharacter__vmt380 默认虚槽桩（11 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt380(int *this, int a2, int a3)
{
  IRDActiveObject__vmt380(this, a2, a3);
  return (*(int (/*thiscall*/ **)(int *))(*this + 1324))(this);
}



// ------------------------------------------------------------
// 0x579560 IRDCharacter__vmt478 —— IRDCharacter__vmt478 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
char */*thiscall*/ IRDCharacter__vmt478(char *this)
{
  return this + 7416;
}



// ------------------------------------------------------------
// 0x579570 IRDCharacter__vmt4A8 —— IRDCharacter__vmt4A8 默认虚槽桩（11 行 return）
// ------------------------------------------------------------
char /*thiscall*/ IRDCharacter__vmt4A8(uint8_t *this, char a2)
{
  *(this + 7729) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x579580 IRDCharacter__vmt4AC —— IRDCharacter__vmt4AC 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
char /*thiscall*/ IRDCharacter__vmt4AC(uint8_t *this)
{
  return *(this + 7729);
}



// ------------------------------------------------------------
// 0x5795B0 IRDCharacter__vmt4BC —— IRDCharacter__vmt4BC 默认虚槽桩（11 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt4BC(uint32_t *this, int a2)
{
  *(this + 1878) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x5795C0 IRDCharacter__vmt4C0 —— IRDCharacter__vmt4C0 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt4C0(uint32_t *this)
{
  return *(this + 1878);
}



// ------------------------------------------------------------
// 0x5795D0 IRDCharacter__vmt4C4 —— IRDCharacter__vmt4C4 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt4C4(uint32_t *this)
{
  return *(this + 1878) + 61440;
}



// ------------------------------------------------------------
// 0x5795E0 IRDCharacter__vmt4CC —— IRDCharacter__vmt4CC 默认虚槽桩（11 行 return）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt4CC(uint32_t *this, int a2)
{
  *(this + 1940) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x5795F0 IRDCharacter__vmt4D4 —— IRDCharacter__vmt4D4 默认虚槽桩（10 行 return）
// ------------------------------------------------------------
char /*thiscall*/ IRDCharacter__vmt4D4(uint8_t *this)
{
  return *(this + 7764);
}



// ------------------------------------------------------------
// 0x579650 IRDCharacter__vmt510 —— IRDCharacter__vmt510 默认虚槽桩（19 行）
// ------------------------------------------------------------
int /*thiscall*/ IRDCharacter__vmt510(void *this, int a2, int a3)
{
  int result; // eax
  int v5; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1160))(this, a2);
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 4))(v5, a3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x579680 IRDCharacter__vmt47C —— IRDCharacter__vmt47C 默认虚槽桩（4F3360 物品数据查询）
// ------------------------------------------------------------
uint32_t */*thiscall*/ IRDCharacter__vmt47C(uint32_t *this)
{
  uint32_t *v1; // esi
  uint32_t *result; // eax

  v1 = this + 1854;
  sub_4F3360(*(void **)(*(this + 1855) + 4));
  *(uint32_t *)(v1[1] + 4) = v1[1];
  result = (uint32_t *)v1[1];
  v1[2] = 0;
  *result = result;
  *(uint32_t *)(v1[1] + 8) = v1[1];
  return result;
}



// ------------------------------------------------------------
// 0x5796C0 IRDCharacter__vmt404 —— IRDCharacter__vmt404 默认虚槽桩（4014D0 字符串）
// ------------------------------------------------------------
uint32_t */*thiscall*/ IRDCharacter__vmt404(int this, int a2)
{
  uint32_t *v2; // esi
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  v2 = (uint32_t *)(this + 7148);
  *(uint32_t *)(this + 7148) = *(uint32_t *)a2;
  *(uint32_t *)(this + 7152) = *(uint32_t *)(a2 + 4);
  *(uint8_t *)(this + 7156) = *(uint8_t *)(a2 + 8);
  sub_4014D0((std::_String_base *)(this + 7160), a2 + 12, 0, -1);
  v2[10] = *(uint32_t *)(a2 + 40);
  v2[11] = *(uint32_t *)(a2 + 44);
  v2[12] = *(uint32_t *)(a2 + 48);
  v2[13] = *(uint32_t *)(a2 + 52);
  v2[14] = *(uint32_t *)(a2 + 56);
  v2[15] = *(uint32_t *)(a2 + 60);
  return v2;
}



// ------------------------------------------------------------
// 0x579730 sub_579730 —— IRDCharacter 构造主体（107 行：4B7110/4B4950 部件 + 578240 外观 + 4B5A50/4A4BD0 动画）
// ------------------------------------------------------------
int /*thiscall*/ sub_579730(int this)
{
  int v2; // eax
  int *v4; // [esp-Ch] [ebp-28h]
  int *v5; // [esp-8h] [ebp-24h]
  int *v6[2]; // [esp+8h] [ebp-14h] BYREF
  int v7; // [esp+18h] [ebp-4h]

  v6[1] = (int *)this;
  *(uint32_t *)this = &vftbl_IRDCharacter;
  v7 = 17;
  sub_4B7110();
  if ( *(uint32_t *)(this + 8120) != 0 )
    j__free(*(void **)(this + 8120));
  *(uint32_t *)(this + 8120) = 0;
  *(uint32_t *)(this + 8124) = 0;
  *(uint32_t *)(this + 8128) = 0;
  *(uint32_t *)(this + 8088) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 8092) = 0;
  if ( *(uint32_t *)(this + 8048) >= 0x10u )
    j__free(*(void **)(this + 8028));
  *(uint32_t *)(this + 8048) = 15;
  *(uint32_t *)(this + 8044) = 0;
  *(uint8_t *)(this + 8028) = 0;
  if ( *(uint32_t *)(this + 7956) >= 0x10u )
    j__free(*(void **)(this + 7936));
  *(uint32_t *)(this + 7956) = 15;
  *(uint32_t *)(this + 7952) = 0;
  *(uint8_t *)(this + 7936) = 0;
  if ( *(uint32_t *)(this + 7896) != 0 )
    j__free(*(void **)(this + 7896));
  *(uint32_t *)(this + 7896) = 0;
  *(uint32_t *)(this + 7900) = 0;
  *(uint32_t *)(this + 7904) = 0;
  if ( *(uint32_t *)(this + 7880) >= 0x10u )
    j__free(*(void **)(this + 7860));
  *(uint32_t *)(this + 7880) = 15;
  *(uint32_t *)(this + 7876) = 0;
  *(uint8_t *)(this + 7860) = 0;
  if ( *(uint32_t *)(this + 7756) >= 0x10u )
    j__free(*(void **)(this + 7736));
  *(uint32_t *)(this + 7756) = 15;
  *(uint32_t *)(this + 7752) = 0;
  *(uint8_t *)(this + 7736) = 0;
  if ( *(uint32_t *)(this + 7724) >= 0x10u )
    j__free(*(void **)(this + 7704));
  *(uint32_t *)(this + 7724) = 15;
  *(uint32_t *)(this + 7720) = 0;
  *(uint8_t *)(this + 7704) = 0;
  if ( *(uint32_t *)(this + 7680) != 0 )
    j__free(*(void **)(this + 7680));
  *(uint32_t *)(this + 7680) = 0;
  *(uint32_t *)(this + 7684) = 0;
  *(uint32_t *)(this + 7688) = 0;
  if ( *(uint32_t *)(this + 7664) != 0 )
    j__free(*(void **)(this + 7664));
  *(uint32_t *)(this + 7664) = 0;
  *(uint32_t *)(this + 7668) = 0;
  *(uint32_t *)(this + 7672) = 0;
  if ( *(uint32_t *)(this + 7648) != 0 )
    j__free(*(void **)(this + 7648));
  *(uint32_t *)(this + 7648) = 0;
  *(uint32_t *)(this + 7652) = 0;
  *(uint32_t *)(this + 7656) = 0;
  if ( *(uint32_t *)(this + 7632) != 0 )
    j__free(*(void **)(this + 7632));
  *(uint32_t *)(this + 7632) = 0;
  *(uint32_t *)(this + 7636) = 0;
  *(uint32_t *)(this + 7640) = 0;
  v2 = *(uint32_t *)(this + 7616);
  LOBYTE(v7) = 4;
  if ( v2 != 0 )
  {
    sub_4B4950(v2, *(uint32_t *)(this + 7620));
    j__free(*(void **)(this + 7616));
  }
  *(uint32_t *)(this + 7616) = 0;
  *(uint32_t *)(this + 7620) = 0;
  *(uint32_t *)(this + 7624) = 0;
  v5 = *(int **)(this + 7420);
  v4 = (int *)*v5;
  LOBYTE(v7) = 3;
  sub_578240((int ***)(this + 7416), v6, v4, v5);
  j__free(*(void **)(this + 7420));
  *(uint32_t *)(this + 7420) = 0;
  *(uint32_t *)(this + 7424) = 0;
  if ( *(uint32_t *)(this + 7380) >= 0x10u )
    j__free(*(void **)(this + 7360));
  *(uint32_t *)(this + 7380) = 15;
  *(uint32_t *)(this + 7376) = 0;
  *(uint8_t *)(this + 7360) = 0;
  LOBYTE(v7) = 1;
  sub_4B5A50(this + 7212);
  if ( *(uint32_t *)(this + 7184) >= 0x10u )
    j__free(*(void **)(this + 7164));
  *(uint32_t *)(this + 7184) = 15;
  *(uint32_t *)(this + 7180) = 0;
  *(uint8_t *)(this + 7164) = 0;
  v7 = -1;
  return sub_4A4BD0(this);
}



// ------------------------------------------------------------
// 0x579A30 IRDCharacter__vmt0 —— IRDCharacter__vmt0 标量删除析构（转发 579730 系成员清理）
// ------------------------------------------------------------
void */*thiscall*/ IRDCharacter__vmt0(void *Block, char a2)
{
  sub_579730((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x579A60 sub_579A60 —— 职业构造后段·剑士分支（579270 + 5EDDC0/5EEE40）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_579A60(uint32_t *this)
{
  sub_579270(this, 0);
  *this = &vftbl_CNSwordman;
  sub_5EDDC0((int)this);
  sub_5EEE40(this);
  return this;
}



// ------------------------------------------------------------
// 0x579AC0 CNSwordman__vmt0 —— CNSwordman__vmt0 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNSwordman__vmt0(void *Block, char a2)
{
  sub_579AF0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x579AF0 sub_579AF0 —— CNSwordman 构造（5F0D40 + 579730 基类主体）
// ------------------------------------------------------------
int /*thiscall*/ sub_579AF0(uint32_t *this)
{
  *this = &vftbl_CNSwordman;
  sub_5F0D40((int)this);
  return sub_579730((int)this);
}



// ------------------------------------------------------------
// 0x579B40 sub_579B40 —— 职业构造后段·格斗家分支（579270 + 5E44C0/5E5F30）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_579B40(uint32_t *this)
{
  sub_579270(this, 1);
  *this = &vftbl_CNFighter;
  *(this + 2105) = 0;
  *(this + 2106) = 0;
  *(this + 2107) = 0;
  sub_5E44C0((int)this);
  sub_5E5F30(this);
  return this;
}



// ------------------------------------------------------------
// 0x579BB0 sub_579BB0 —— 10 行小函数
// ------------------------------------------------------------
int /*thiscall*/ sub_579BB0(uint32_t *this)
{
  return *(this + 2075);
}



// ------------------------------------------------------------
// 0x579BD0 CNFighter__vmt0 —— CNFighter__vmt0 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNFighter__vmt0(void *Block, char a2)
{
  sub_579C00();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x579C00 sub_579C00 —— CNFighter 构造（5E6C50 + 579730 基类主体）
// ------------------------------------------------------------
int /*thiscall*/ sub_579C00(void **this)
{
  *this = &vftbl_CNFighter;
  sub_5E6C50((int)this);
  if ( *(this + 2105) != nullptr )
    j__free(*(this + 2105));
  *(this + 2105) = nullptr;
  *(this + 2106) = nullptr;
  *(this + 2107) = nullptr;
  return sub_579730((int)this);
}



// ------------------------------------------------------------
// 0x579C80 sub_579C80 —— 职业构造后段·神枪手分支（579270 + 5790A0/425940/41A630/4C0430/4C3810）
// ------------------------------------------------------------
int /*thiscall*/ sub_579C80(int this)
{
  sub_579270((uint32_t *)this, 2);
  *(uint32_t *)this = &vftbl_CNGunner;
  sub_5790A0((uint32_t *)(this + 8220));
  *(uint32_t *)(this + 8524) = sub_425940();
  *(uint32_t *)(this + 8528) = 0;
  sub_41A630(this + 8544);
  *(uint32_t *)(this + 8544) = &vftbl_clong;
  sub_41A630(this + 8577);
  *(uint32_t *)(this + 8577) = &vftbl_clong;
  *(uint8_t *)(this + 9492) = 0;
  *(uint32_t *)(this + 9488) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 9496) = 0;
  *(uint8_t *)(this + 9500) = 1;
  *(uint8_t *)(this + 9502) = 0;
  *(uint8_t *)(this + 9501) = 0;
  *(uint32_t *)(this + 9512) = 0;
  *(uint32_t *)(this + 9508) = 0;
  *(uint32_t *)(this + 9504) = 0;
  sub_4C0430(this);
  sub_4C3810((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x579D70 CNGunner__vmt534 —— CNGunner__vmt534 默认虚槽桩
// ------------------------------------------------------------
int /*thiscall*/ CNGunner__vmt534(uint32_t *this)
{
  return *(this + 2129);
}



// ------------------------------------------------------------
// 0x579D90 CNGunner__vmt0 —— CNGunner__vmt0 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNGunner__vmt0(void *Block, char a2)
{
  sub_579DC0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x579DC0 sub_579DC0 —— CNGunner 构造（4C4260/41A580/6569D0/578E90 + 579730 基类主体）
// ------------------------------------------------------------
int /*thiscall*/ sub_579DC0(char *this)
{
  *(uint32_t *)this = &vftbl_CNGunner;
  sub_4C4260();
  *((uint32_t *)this + 2372) = &vftbl_nengine__IObject;
  *(this + 9492) = 0;
  sub_41A580(this + 8577);
  sub_41A580(this + 8544);
  sub_6569D0(this + 8520);
  j__free(*((void **)this + 2131));
  *((uint32_t *)this + 2131) = 0;
  sub_578E90((int)(this + 8220));
  return sub_579730((int)this);
}



// ------------------------------------------------------------
// 0x579E70 sub_579E70 —— 职业构造后段·魔法师分支（579270 + 5DA220/5DD470）
// ------------------------------------------------------------
int /*thiscall*/ sub_579E70(int this)
{
  sub_579270((uint32_t *)this, 3);
  *(uint32_t *)this = &vftbl_CNMage;
  *(uint32_t *)(this + 8624) = 15;
  *(uint32_t *)(this + 8620) = 0;
  *(uint8_t *)(this + 8604) = 0;
  sub_5DA220(this);
  sub_5DD470(this);
  return this;
}



// ------------------------------------------------------------
// 0x579EE0 CNMage__vmt0 —— CNMage__vmt0 标量删除析构
// ------------------------------------------------------------
void */*thiscall*/ CNMage__vmt0(void *Block, char a2)
{
  sub_579F10();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x579F10 sub_579F10 —— CNMage 构造（5DDCA0 + 579730 基类主体）
// ------------------------------------------------------------
int /*thiscall*/ sub_579F10(void **this)
{
  *this = &vftbl_CNMage;
  sub_5DDCA0();
  if ( (unsigned int)*(this + 2156) >= 0x10 )
    j__free(*(this + 2151));
  *(this + 2156) = (void *)15;
  *(this + 2155) = nullptr;
  *((uint8_t *)this + 8604) = 0;
  return sub_579730((int)this);
}



// ------------------------------------------------------------
// 0x579F90 sub_579F90 —— 职业构造分发：调 579A60(剑士)/579B40(格斗)/579C80(枪手)/579E70(法师)——按职业 id 走对应后段
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_579F90(void *Block)
{
  uint32_t *v1; // eax
  uint32_t *result; // eax
  uint32_t *v3; // eax
  void *v4; // eax
  void *v5; // eax

  switch ( (unsigned int)Block )
  {
    case 0u:
      v1 = operator new(0x2170u);
      if ( v1 == nullptr )
        goto LABEL_10;
      result = sub_579A60(v1);
      break;
    case 1u:
      v3 = operator new(0x215Cu);
      if ( v3 == nullptr )
        goto LABEL_10;
      result = sub_579B40(v3);
      break;
    case 2u:
      v4 = operator new(0x2530u);
      if ( v4 == nullptr )
        goto LABEL_10;
      result = (uint32_t *)sub_579C80((int)v4);
      break;
    case 3u:
      v5 = operator new(0x21B8u);
      if ( v5 == nullptr )
        goto LABEL_10;
      result = (uint32_t *)sub_579E70((int)v5);
      break;
    default:
LABEL_10:
      result = nullptr;
      break;
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
CHAR */*thiscall*/ sub_57A0A0(CHAR *this, LPCSTR lpString2)
{
  *(uint32_t *)this = &vftbl_CBIniFile;
  lstrcpyA(this + 4, lpString2);
  return this;
}



// ------------------------------------------------------------
// 0x57A0D0 sub_57A0D0 —— CBIniFile 桩（10 行 return）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_57A0D0(const CHAR *this, LPCSTR lpszSection, LPCSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct)
{
  return WritePrivateProfileStructA(lpszSection, lpszKey, lpStruct, uSizeStruct, this + 4);
}



// ------------------------------------------------------------
// 0x57A100 sub_57A100 —— CBIniFile 桩（10 行 return）
// ------------------------------------------------------------
UINT /*thiscall*/ sub_57A100(const CHAR *this, LPCSTR lpAppName, LPCSTR lpKeyName, INT nDefault)
{
  return GetPrivateProfileIntA(lpAppName, lpKeyName, nDefault, this + 4);
}



// ------------------------------------------------------------
// 0x57A120 sub_57A120 —— CBIniFile 桩（10 行 return）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_57A120(const CHAR *this, LPCSTR lpszSection, LPCSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct)
{
  return GetPrivateProfileStructA(lpszSection, lpszKey, lpStruct, uSizeStruct, this + 4);
}



// ------------------------------------------------------------
// 0x57A150 CBIniFile__vmt0 —— CBIniFile__vmt0 析构（13 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CBIniFile__vmt0(uint32_t *Block, char a2)
{
  *Block = &vftbl_CBIniFile;
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x57A180 sub_57A180 —— CBIniFile 桩（11 行 return）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_57A180(const CHAR *this, LPCSTR lpAppName, LPCSTR lpKeyName, int a4)
{
  sprintf(String, "%d", a4);
  return WritePrivateProfileStringA(lpAppName, lpKeyName, String, this + 4);
}



// ------------------------------------------------------------
// 0x57A1C0 sub_57A1C0 —— INI 节点/键查找（32 行：逐节比对）
// ------------------------------------------------------------
unsigned int sub_57A1C0()
{
  unsigned int v0; // ecx
  unsigned int i; // edi
  int v2; // esi
  unsigned int *v3; // edx
  unsigned int result; // eax

  v0 = 1;
  dword_9B8E80[0] = 0;
  for ( i = 128; i != 0; i >>= 1 )
  {
    v2 = 8 * i;
    v3 = (unsigned int *)(4 * i + 10194560);
    v0 = ((v0 & 1) != 0 ? 0xEDB88320 : 0) ^ (v0 >> 1);
    result = 0;
    do
    {
      *v3 = v0 ^ *(int *)((char *)dword_9B8E80 + result);
      result += v2;
      v3 = (unsigned int *)((char *)v3 + v2);
    }
    while ( result < 0x400 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x57A220 sub_57A220 —— INI 取值（转发 57A1C0）
// ------------------------------------------------------------
int /*cdecl*/ sub_57A220(int a1, uint8_t *a2, int a3)
{
  int v3; // esi
  unsigned int i; // eax

  if ( byte_9B9280 == 0 )
  {
    sub_57A1C0();
    byte_9B9280 = 1;
  }
  v3 = a3;
  for ( i = ~a1; v3 != 0; --v3 )
    i = dword_9B8E80[(uint8_t)(i ^ *a2++)] ^ (i >> 8);
  return ~i;
}



// ------------------------------------------------------------
// 0x57A280 sub_57A280 —— INI/字符串小桩（15 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_57A280(uint32_t *this, int a2, int a3, int a4, int a5, int a6)
{
  *this = a2;
  *(this + 1) = a3;
  *(this + 2) = a4;
  *(this + 3) = a5;
  *(this + 4) = a6;
  return this;
}



// ------------------------------------------------------------
// 0x57A2B0 sub_57A2B0 —— 字符串小桩（12 行 return）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A2B0(uint32_t *this, int a2)
{
  *(this + 41) = a2;
  *(this + 42) = 0;
  return a2;
}



// ------------------------------------------------------------
// 0x57A2D0 sub_57A2D0 —— 字符串小桩（12 行 return）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A2D0(uint32_t *this, int a2, int a3)
{
  *(this + 41) = a2;
  *(this + 42) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x57A2F0 sub_57A2F0 —— std::string 构造辅助（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A2F0(void *this)
{
  unsigned int v1; // esi
  int v2; // eax
  int v3; // edx

  v1 = (unsigned int)this + 120;
  v2 = sub_41A5E0((unsigned int)this + 120);
  return sub_41A590(v1, v3, v2 + 1);
}



// ------------------------------------------------------------
// 0x57A310 sub_57A310 —— std::string 构造辅助 2（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A310(void *this)
{
  unsigned int v1; // esi
  int v2; // eax
  int v3; // edx

  v1 = (unsigned int)this + 134;
  v2 = sub_41A5E0((unsigned int)this + 134);
  return sub_41A590(v1, v3, v2 + 1);
}



// ------------------------------------------------------------
// 0x57A330 sub_57A330 —— 字符串小桩（699030）
// ------------------------------------------------------------
char /*thiscall*/ sub_57A330(void *this)
{
  return sub_699030((int)this + 164);
}



// ------------------------------------------------------------
// 0x57A340 sub_57A340 —— std::string 析构辅助（698F90/698FE0）
// ------------------------------------------------------------
char /*thiscall*/ sub_57A340(void *this)
{
  int v1; // esi

  v1 = (int)this + 164;
  sub_698F90((int)this + 164, 0, 0);
  return sub_698FE0(v1);
}



// ------------------------------------------------------------
// 0x57A360 sub_57A360 —— 字符串辅助（578C40 掉落物理复用）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A360(int this)
{
  int v1; // esi

  v1 = *(uint32_t *)(this + 972);
  sub_578C40((void ***)this, nullptr);
  return v1;
}



// ------------------------------------------------------------
// 0x57A380 sub_57A380 —— 13 行小函数
// ------------------------------------------------------------
char /*thiscall*/ sub_57A380(int this, int16_t a2)
{
  *(uint16_t *)(this + 4) = a2;
  *(uint8_t *)(this + 36) = 0;
  *(uint8_t *)(this + 64) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x57A3A0 sub_57A3A0 —— std::string 构造辅助 3（698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_57A3A0(uint8_t *this)
{
  int v1; // ecx

  *(this + 36) = 1;
  v1 = (int)(this + 24);
  *(uint8_t *)(v1 + 13) = 0;
  *(uint8_t *)(v1 + 14) = 0;
  return sub_698F90(v1, 0, 0);
}



// ------------------------------------------------------------
// 0x57A3C0 sub_57A3C0 —— 对象/控件辅助（47DC90/483D50）
// ------------------------------------------------------------
int /*stdcall*/ sub_57A3C0(int a1, int a2)
{
  int v2; // eax

  v2 = sub_47DC90(a2);
  return sub_483D50(a1, v2);
}



// ------------------------------------------------------------
// 0x57A3F0 sub_57A3F0 —— std::string 构造辅助 4（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A3F0(void *this, int a2)
{
  unsigned int v2; // esi
  int v3; // eax
  int v4; // edx

  v2 = (unsigned int)this + 112;
  v3 = sub_41A5E0((unsigned int)this + 112);
  return sub_41A590(v2, v4, a2 + v3);
}



// ------------------------------------------------------------
// 0x57A410 sub_57A410 —— std::string 构造辅助 5（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A410(void *this, int a2)
{
  unsigned int v2; // esi
  int v3; // eax
  int v4; // edx

  v2 = (unsigned int)this + 126;
  v3 = sub_41A5E0((unsigned int)this + 126);
  return sub_41A590(v2, v4, a2 + v3);
}



// ------------------------------------------------------------
// 0x57A430 sub_57A430 —— std::string 构造辅助 6（698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_57A430(uint8_t *this, char a2)
{
  int v2; // ecx

  *(this + 524) = a2;
  v2 = (int)(this + 512);
  *(uint8_t *)(v2 + 13) = 0;
  *(uint8_t *)(v2 + 14) = 0;
  return sub_698F90(v2, 1000, 0);
}



// ------------------------------------------------------------
// 0x57A460 sub_57A460 —— 11 行小函数
// ------------------------------------------------------------
int /*thiscall*/ sub_57A460(uint32_t *this, int a2)
{
  *(this + 306) += a2;
  return a2;
}



// ------------------------------------------------------------
// 0x57A480 sub_57A480 —— 字符串辅助 7（41A5E0）
// ------------------------------------------------------------
double /*thiscall*/ sub_57A480(void *this)
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this + 934));
}



// ------------------------------------------------------------
// 0x57A4A0 sub_57A4A0 —— 辅助（4FBD90）
// ------------------------------------------------------------
int /*cdecl*/ sub_57A4A0(int a1, int a2, int a3)
{
  return sub_4FBD90(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x57A4C0 sub_57A4C0 —— 辅助（655A40）
// ------------------------------------------------------------
int /*stdcall*/ sub_57A4C0(int a1, int a2, int a3)
{
  sub_655A40(a1, a2, a3);
  return a1 + 20 * a2;
}



// ------------------------------------------------------------
// 0x57A4F0 sub_57A4F0 —— 14 行小函数
// ------------------------------------------------------------
void /*thiscall*/ sub_57A4F0(int this)
{
  if ( *(uint32_t *)(this + 24) != 0 )
    j__free(*(void **)(this + 24));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
}



// ------------------------------------------------------------
// 0x57A520 sub_57A520 —— 文本组装（4015C0/401740）
// ------------------------------------------------------------
void /*noreturn*/ sub_57A520()
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
// 0x57A590 sub_57A590 —— 转发 57A520
// ------------------------------------------------------------
int /*thiscall*/ sub_57A590(uint32_t *this, unsigned int a2)
{
  int v2; // edx

  v2 = *(this + 1);
  if ( v2 == 0 || (*(this + 2) - v2) >> 2 <= a2 )
    sub_57A520();
  return v2 + 4 * a2;
}



// ------------------------------------------------------------
// 0x57A5C0 sub_57A5C0 —— 主更新辅助（121 行：4735F0/4FBDE0/655A00/655A40/45E580）
// ------------------------------------------------------------
int /*thiscall*/ sub_57A5C0(int *this, int a2, unsigned int a3, uint32_t *Block)
{
  int v5; // edx
  int v6; // ebx
  int v7; // ecx
  int v8; // edx
  int result; // eax
  unsigned int v10; // ecx
  int v12; // eax
  int v13; // eax
  unsigned int v14; // ecx
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  unsigned int v18; // edi
  void *v19; // ecx
  int v21; // edi
  int v22; // [esp-18h] [ebp-48h]
  int v23; // [esp-Ch] [ebp-3Ch]
  unsigned int v24; // [esp-8h] [ebp-38h]
  int v25; // [esp+0h] [ebp-30h] BYREF
  uint32_t v26[6]; // [esp+Ch] [ebp-24h] BYREF
  int v27; // [esp+2Ch] [ebp-4h]
  int v28; // [esp+38h] [ebp+8h]
  int v29; // [esp+3Ch] [ebp+Ch]
  char *Blocka; // [esp+40h] [ebp+10h]
  void *Blockb; // [esp+40h] [ebp+10h]

  v5 = Block[1];
  v6 = *(this + 1);
  v26[0] = *Block;
  v7 = Block[2];
  v26[1] = v5;
  v8 = Block[3];
  result = Block[4];
  v26[5] = &v25;
  v26[2] = v7;
  v26[3] = v8;
  v26[4] = result;
  if ( v6 != 0 )
  {
    result = 1717986919 * (*(this + 3) - v6);
    v10 = (*(this + 3) - v6) / 20;
  }
  else
  {
    v10 = 0;
  }
  if ( a3 != 0 )
  {
    if ( v6 != 0 )
      v12 = (*(this + 2) - v6) / 20;
    else
      v12 = 0;
    if ( 214748364 - v12 < a3 )
      sub_4735F0(this);
    if ( v6 != 0 )
      v13 = (*(this + 2) - v6) / 20;
    else
      v13 = 0;
    if ( v10 >= a3 + v13 )
    {
      v19 = (void *)*(this + 2);
      Blockb = v19;
      if ( ((int)v19 - a2) / 20 >= a3 )
      {
        v28 = (int)v19 - 20 * a3;
        *(this + 2) = sub_4FBDE0(v28, v19, v19);
        sub_57A4A0(a2, v28, Blockb);
        return sub_655A00(a2, a2 + 20 * a3, v26);
      }
      else
      {
        sub_4FBDE0(a2, v19, a2 + 20 * a3);
        v24 = a3 - (*(this + 2) - a2) / 20;
        v23 = *(this + 2);
        v27 = 2;
        sub_57A4C0(v23, v24, v26);
        v21 = 20 * a3 + *(this + 2);
        *(this + 2) = v21;
        return sub_655A00(a2, v21 - 20 * a3, v26);
      }
    }
    else
    {
      if ( 214748364 - (v10 >> 1) >= v10 )
        v14 = (v10 >> 1) + v10;
      else
        v14 = 0;
      if ( v6 != 0 )
        v15 = (*(this + 2) - v6) / 20;
      else
        v15 = 0;
      if ( v14 < a3 + v15 )
        v14 = a3 + sub_45E580(this);
      v16 = 20 * v14;
      Blocka = (char *)operator new(20 * v14);
      v22 = *(this + 1);
      v27 = 0;
      v29 = sub_4FBDE0(v22, a2, Blocka);
      sub_655A40(v29, a3, v26);
      sub_4FBDE0(a2, *(this + 2), v29 + 20 * a3);
      v17 = *(this + 1);
      if ( v17 != 0 )
        v17 = (*(this + 2) - v17) / 20;
      v18 = v17 + a3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v16];
      *(this + 2) = (int)&Blocka[20 * v18];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x57A880 sub_57A880 —— 转发 57A5C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_57A880(int *this, uint32_t *a2, int a3, uint32_t *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 20 != 0 )
    v6 = (a3 - v5) / 20;
  else
    v6 = 0;
  sub_57A5C0(this, a3, 1u, Block);
  *a2 = *(this + 1) + 20 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x57A8F0 sub_57A8F0 —— 转发 57A880 + 655A40 收尾
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_57A8F0(int *this, uint32_t *Block)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi
  uint32_t *result; // eax

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 20;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(this + 3) - v3) / 20 )
    return sub_57A880(this, &Block, *(this + 2), Block);
  v5 = *(this + 2);
  result = (uint32_t *)sub_655A40(v5, 1, Block);
  *(this + 2) = v5 + 20;
  return result;
}


