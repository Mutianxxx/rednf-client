// ============================================================
// 【40JP逆向源代码工程】game/script_string.cpp
// 模块: 脚本字符串管理/元素/职业标签/战斗分发器宿主类(CNRDUdpModule)/窗口族存根
// 来源: work/dump_combat.txt  区块: 0x440000-0x450000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
// 函数数: 268
// ------------------------------------------------------------
// ★ 本文件已按以下定案升级注释（锚点速查）：
//   0x4422C0  脚本包根路径 + Script.pvf 挂载判定（_ScriptPacks/!ScriptPacks 自证）
//   0x4426A0  职业标签→索引（[swordman]/[fighter]/[gunner]/[mage]）
//   0x442710  元素标签→索引（[fire/water/dark/light element]）
//   0x442780  当前元素标签 setter（全局 dword_97B384）
//   0x442E10  RDARScriptStringManager 入口（"::ERROR::input NULL string" 自证）【推断】
//   0x444C20/0x444C60  CNMainGameModule vmt8/vmt4 —— L1 逐行精修版见
//             src/game/module/CNMainGameModule.cpp（docs/13 §1），此处保留 L2 转写体
//   0x445650  CNRDUdpModule::vmt90 按场景取操作角色（本会话早前已由主代理补齐，未改动）
//   0x446130/0x446190  PVP/WARROOM 被动物体特殊绑定（分发器 case 8/0x15/0x16 配套）
//   0x446710/0x446F00/0x449EB0  peer 加入/清理广播（@@ADD/REMOVE PEER 自证）
//   0x44EA20  模块切换收尾（docs/13 §3 末行定案调用）
// ★ 战斗分发器本体 sub_4471E0（CNRDUdpModule::vmt0，11KB 巨函数）单独成文件：
//   src/game/bigfunc_4471E0_sub_4471E0.cpp（含全 case 语义表）
// 交叉引用：发包 API 0x423200/0x423380 已 L1 精修于 src/nengine/net_socket.cpp（docs/13 §5）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】脚本字符串管理核心（0x440F90-0x442280）
// RDARScriptStringManager 巨函数对（0x440F90 ~360 行 / 0x441750 ~470 行，
// std::string 容器操作 sub_40BF00/43BF40/43DA50）+ 容器/vector 辅助。
// 词条与标签的具体取值见分区 2 的标签族。
// ============================================================
// ------------------------------------------------------------
// 0x440F90 sub_440F90
// ------------------------------------------------------------
// 【推断】RDARScriptStringManager 词条表操作（std::string 容器 + sub_43BF40/43DA50）
char /*thiscall*/ sub_440F90(int this)
{
  int v2; // ecx
  uint16_t v3; // ax
  int v4; // esi
  int v5; // ecx
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  void **v21; // eax
  int v22; // eax
  int v23; // eax
  uint32_t *v24; // ecx
  int v25; // eax
  void **v26; // eax
  int v27; // eax
  int v28; // esi
  int v29; // eax
  void **v30; // eax
  int v31; // esi
  void **v32; // eax
  int v33; // eax
  int v34; // esi
  char result; // al
  int v36; // [esp+Ch] [ebp-3Ch] BYREF
  int v37; // [esp+10h] [ebp-38h]
  const char *v38; // [esp+14h] [ebp-34h] BYREF
  char v39[4]; // [esp+18h] [ebp-30h] BYREF
  uint8_t v40[4]; // [esp+1Ch] [ebp-2Ch] BYREF
  void *Block[4]; // [esp+20h] [ebp-28h] BYREF
  int v42; // [esp+30h] [ebp-18h]
  unsigned int v43; // [esp+34h] [ebp-14h]
  int v44; // [esp+38h] [ebp-10h]
  int v45; // [esp+44h] [ebp-4h]

  v2 = *(uint32_t *)(this + 136);
  v44 = dword_796E50;
  v38 = (const char *)sub_69B740(v2);
  if ( strcmp(v38, szPassword) == 0 )
    goto LABEL_107;
  v3 = *(uint16_t *)(dword_8F8538 + 4);
  v4 = 3;
  v37 = (uint16_t)word_77F804;
  if ( v3 == 0xFFFF )
  {
    if ( sub_40BF00((std::_String_base *)(this + 292), 0, *(uint32_t *)(this + 312), szPassword, 0) != 0
      || *(uint8_t *)(this + 320) != 0 )
    {
      if ( sub_40BF00((std::_String_base *)(this + 292), 0, *(uint32_t *)(this + 312), szPassword, 0) != 0 )
      {
        if ( *(uint32_t *)(this + 316) < 0x10u )
          v7 = this + 296;
        else
          v7 = *(uint32_t *)(this + 296);
        v8 = sub_43BF40(v7);
      }
      else
      {
        v9 = 28 * *(uint32_t *)(this + 1444);
        if ( *(uint32_t *)(v9 + this + 348) < 0x10u )
          v10 = v9 + this + 328;
        else
          v10 = *(uint32_t *)(v9 + this + 328);
        v8 = sub_43BF40(v10);
      }
      if ( v8 != 0 )
      {
        v4 = 1;
        v37 = *(uint16_t *)(v8 + 4);
      }
      else
      {
        sub_43DA50(this, 0, szPassword);
        v4 = 10;
      }
    }
    else
    {
      v5 = *(uint32_t *)(this + 288);
      if ( v5 == 2 )
      {
        v4 = 6;
      }
      else if ( v5 == 3 )
      {
        v4 = 8;
      }
      else
      {
        v6 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v6 == 2 || v6 == 3 || v5 == 1 )
        {
          v4 = 2;
        }
        else if ( v6 == 4 )
        {
          v4 = 5;
        }
        else if ( v6 == 6 )
        {
          v4 = 9;
        }
      }
    }
  }
  else
  {
    v4 = 1;
    v37 = v3;
  }
  v36 = 0;
  v43 = 15;
  v42 = 0;
  LOBYTE(Block[0]) = 0;
  v45 = 0;
  if ( (uint8_t)sub_43F740(this, v38) != 0 )
    goto LABEL_104;
  v11 = sub_43F210(&v36, &v38, v40, v38);
  switch ( v36 )
  {
    case 1:
      v4 = 4;
LABEL_103:
      sub_43ED90(this, v11, v4, v37);
      goto LABEL_104;
    case 7:
      v4 = 0;
      goto LABEL_103;
    case 8:
      v12 = sub_422E70(295);
      sub_43BEE0((uint32_t *)this, v12, -6567706, 0, -1);
      v13 = sub_422E70(296);
      sub_43BEE0((uint32_t *)this, v13, -6567706, 0, -1);
      v14 = sub_422E70(297);
      sub_43BEE0((uint32_t *)this, v14, -6567706, 0, -1);
      v15 = sub_422E70(298);
      sub_43BEE0((uint32_t *)this, v15, -6567706, 0, -1);
      v16 = sub_422E70(299);
      sub_43BEE0((uint32_t *)this, v16, -6567706, 0, -1);
      v17 = sub_422E70(300);
      sub_43BEE0((uint32_t *)this, v17, -6567706, 0, -1);
      v18 = sub_422E70(301);
      sub_43BEE0((uint32_t *)this, v18, -6567706, 0, -1);
      v19 = sub_422E70(302);
      sub_43BEE0((uint32_t *)this, v19, -6567706, 0, -1);
      v20 = sub_422E70(303);
LABEL_101:
      sub_43BEE0((uint32_t *)this, v20, -6567706, 0, -1);
      goto LABEL_104;
    default:
      break;
  }
  if ( v36 != 2 )
  {
    if ( v36 == 3 )
    {
      if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
      {
        v20 = sub_422E70(306);
        goto LABEL_101;
      }
      if ( (uint8_t)sub_43B540(dword_8F850C) == 0 )
      {
        v20 = sub_422E70(307);
        goto LABEL_101;
      }
      v21 = (void **)Block[0];
      if ( v43 < 0x10 )
        v21 = Block;
      v22 = sub_43BF40(v21);
      if ( v22 == 0 )
      {
        v20 = sub_422E70(308);
        goto LABEL_101;
      }
      sub_4564A0(*(uint16_t *)(v22 + 4));
      goto LABEL_104;
    }
    if ( v36 == 4 )
    {
      if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
      {
        v20 = sub_422E70(309);
        goto LABEL_101;
      }
      if ( *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) == 0 )
      {
        v20 = sub_422E70(310);
        goto LABEL_101;
      }
      sub_423200(dword_8F7B08, 13);
      sub_423380(dword_8F7B08);
      goto LABEL_104;
    }
    if ( v36 != 5 )
    {
      if ( v36 == 6 )
      {
        if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
        {
          v20 = sub_422E70(316);
          goto LABEL_101;
        }
        v30 = (void **)Block[0];
        if ( v43 < 0x10 )
          v30 = Block;
        v31 = sub_43BF40(v30);
        if ( v31 == 0 )
          goto LABEL_104;
        if ( v31 == sub_429830((uint16_t)word_77F804) )
        {
          v20 = sub_422E70(317);
          goto LABEL_101;
        }
        if ( *(uint32_t *)(v31 + 68) != 0 )
        {
          v20 = sub_422E70(318);
          goto LABEL_101;
        }
        sub_484640((uint16_t *)dword_8F8538, *(uint16_t *)(v31 + 4));
      }
      else if ( v36 == 9 )
      {
        if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
        {
          v20 = sub_422E70(319);
          goto LABEL_101;
        }
        v32 = (void **)Block[0];
        if ( v43 < 0x10 )
          v32 = Block;
        v33 = sub_43BF40(v32);
        v34 = v33;
        if ( v33 == 0 )
          goto LABEL_104;
        if ( *(uint32_t *)(v33 + 192) == 0 || (uint8_t)sub_45E680(*(uint32_t *)(v33 + 192)) == 0 )
        {
          v20 = sub_422E70(320);
          goto LABEL_101;
        }
        sub_526BF0(*(uint32_t *)(v34 + 192), 1);
      }
      else if ( v4 != 10 )
      {
        goto LABEL_103;
      }
      goto LABEL_104;
    }
    v23 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v23 == 6 )
    {
      v24 = (uint32_t *)dword_99FF08;
      if ( dword_99FF08 != 0 )
      {
LABEL_62:
        if ( sub_48F4C0(v24) == 0 )
        {
          v25 = sub_422E70(312);
          sub_43BEE0((uint32_t *)this, v25, -6567706, 0, -1);
        }
        v26 = (void **)Block[0];
        if ( v43 < 0x10 )
          v26 = Block;
        v27 = sub_43BF40(v26);
        v28 = v27;
        if ( v27 == 0 || (uint8_t)sub_43BFF0(v27) == 0 )
          goto LABEL_104;
        if ( v28 == sub_429830((uint16_t)word_77F804) )
        {
          v20 = sub_422E70(313);
        }
        else if ( *(uint32_t *)(v28 + 68) != 0 )
        {
          v20 = sub_422E70(314);
        }
        else
        {
          sub_423200(dword_8F7B08, 10);
          v38 = (const char *)*(uint16_t *)(v28 + 4);
          sub_423290(&v38, 2);
          v29 = *(uint32_t *)(dword_8F7A24 + 12);
          if ( v29 == 4 )
          {
            v39[0] = 2;
            sub_423290(v39, 1);
          }
          else if ( v29 == 6 )
          {
            v39[0] = 3;
            sub_423290(v39, 1);
          }
          v38 = nullptr;
          sub_423290(&v38, 4);
          sub_423380(dword_8F7B08);
          v20 = sub_422E70(315);
        }
        goto LABEL_101;
      }
    }
    else if ( v23 == 4 )
    {
      v24 = (uint32_t *)dword_99FEC0;
      if ( dword_99FEC0 != 0 )
        goto LABEL_62;
    }
    v20 = sub_422E70(311);
    goto LABEL_101;
  }
  if ( strcmp((const char *)(this + 1532), szPassword) == 0 )
  {
    v20 = sub_422E70(304);
    goto LABEL_101;
  }
  if ( sub_699000(this + 1476) <= 3000 )
  {
    v20 = sub_422E70(305);
    goto LABEL_101;
  }
  sub_43ED90(this, this + 1532, *(uint32_t *)(this + 1788), *(uint16_t *)(this + 1792));
LABEL_104:
  sub_69BCC0(*(uint32_t *)(this + 136));
  v45 = -1;
  if ( v43 >= 0x10 )
    j__free(Block[0]);
  v43 = 15;
  v42 = 0;
  LOBYTE(Block[0]) = 0;
LABEL_107:
  result = *(uint8_t *)(this + 256);
  if ( result != 0 )
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(this + 124) + 12);
    dword_79BE54 = dword_79BE4C;
    *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 0;
    *(uint8_t *)(this + 273) = 0;
    *(uint8_t *)(this + 274) = 0;
    sub_698F90(this + 260, 100, 0);
    *(uint8_t *)(this + 256) = 0;
    result = sub_4BF300(dword_8F8558, 0, 1);
  }
  *(uint8_t *)(this + 1475) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x441750 sub_441750
// ------------------------------------------------------------
// 【推断】RDARScriptStringManager 词条表操作 II（usercall，ecx/edi/esi 三隐参）
char /*usercall*/ sub_441750@<al>(int a1@<ecx>, int a2@<edi>, int a3@<esi>)
{
  int v4; // eax
  char v5; // cl
  int v6; // eax
  char v7; // cl
  int v8; // eax
  bool v9; // zf
  int v10; // eax
  int *v11; // esi
  int j; // edi
  int *v13; // esi
  int i; // edi
  int v15; // esi
  uint32_t **v16; // edi
  uint32_t *v17; // ecx
  int v18; // esi
  int v19; // edi
  LONG x; // eax
  LONG y; // edi
  int v22; // esi
  int v23; // eax
  int v24; // eax
  int v25; // esi
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // esi
  int v30; // eax
  uint32_t *v31; // ecx
  int v32; // esi
  int v33; // eax
  uint32_t *v34; // edx
  uint32_t *v35; // ecx
  int v36; // eax
  int v37; // eax
  int v38; // eax
  int v39; // eax
  bool v40; // cl
  int v41; // eax
  uint32_t *v42; // ecx
  int v43; // esi
  int v44; // eax
  int v45; // esi
  int v46; // eax
  char v47; // al
  int v48; // eax
  int v49; // eax
  bool *v50; // eax
  int v51; // eax
  int v52; // ecx
  LONG v53; // eax
  int v54; // ecx
  int v55; // ecx
  int v56; // eax
  int v57; // eax
  int v58; // eax
  int v59; // ecx
  int v60; // eax
  int v61; // eax
  int v63; // [esp-Ch] [ebp-18h]
  LONG v66; // [esp+4h] [ebp-8h]
  bool v67; // [esp+Bh] [ebp-1h]

  v4 = *(uint32_t *)(a1 + 124);
  v5 = *(uint8_t *)(v4 + 116);
  *(uint8_t *)(v4 + 116) = 0;
  if ( v5 != 0
    && (uint8_t)sub_44C410(2) == 0
    && (uint8_t)sub_44C410(1) == 0
    && (uint8_t)sub_44C410(0) == 0 )
  {
    sub_43B920(1);
  }
  v6 = *(uint32_t *)(a1 + 136);
  v7 = *(uint8_t *)(v6 + 116);
  *(uint8_t *)(v6 + 116) = 0;
  if ( v7 != 0 )
    sub_440F90(a1);
  v8 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v8 != 2 && v8 != 5 )
  {
    v9 = *(uint8_t *)(a1 + 1474) == 0;
    v10 = *(uint32_t *)(a1 + 12);
    *(uint32_t *)(v10 + 28) = 317;
    if ( v9 )
    {
      *(uint32_t *)(v10 + 32) = 162;
      sub_69A5F0(*(uint32_t **)(a1 + 24), 5, 144);
      sub_69A5F0(*(uint32_t **)(a1 + 112), 2, 198);
      sub_69A5F0(*(uint32_t **)(a1 + 100), 2, 182);
      sub_69A5F0(*(uint32_t **)(a1 + 104), 20, 182);
      *(uint8_t *)(*(uint32_t *)(a1 + 104) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(a1 + 108) + 16) = 0;
      v13 = (int *)(a1 + 76);
      for ( i = 4; i != 0; --i )
        sub_69C3E0(*v13++, 8);
    }
    else
    {
      *(uint32_t *)(v10 + 32) = 354;
      sub_69A5F0(*(uint32_t **)(a1 + 24), 2, 336);
      sub_69A5F0(*(uint32_t **)(a1 + 112), 2, 390);
      sub_69A5F0(*(uint32_t **)(a1 + 100), 2, 374);
      sub_69A5F0(*(uint32_t **)(a1 + 108), 20, 374);
      *(uint8_t *)(*(uint32_t *)(a1 + 104) + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(a1 + 108) + 16) = 1;
      v11 = (int *)(a1 + 76);
      for ( j = 4; j != 0; --j )
        sub_69C3E0(*v11++, 20);
    }
    sub_69A5F0(*(uint32_t **)(a1 + 116), 59, 319);
    v15 = 0;
    v16 = (uint32_t **)(a1 + 28);
    do
    {
      v17 = *v16;
      if ( *(uint8_t *)(a1 + 1474) != 0 )
        sub_69A5F0(v17, v15 * v17[7] + 38, 371);
      else
        sub_69A5F0(v17, v15 * v17[7] + 38, 179);
      ++v15;
      ++v16;
    }
    while ( v15 < 4 );
    v18 = 0;
    v19 = a1 + 28;
    do
    {
      if ( *(uint8_t *)(*(uint32_t *)v19 + 17) != 0 && dword_79BE34 == *(uint32_t *)(*(uint32_t *)v19 + 12) )
        sub_43BA20(v18);
      ++v18;
      v19 += 4;
    }
    while ( v18 < 4 );
    if ( *(uint8_t *)(a1 + 1475) == 0 && *(uint8_t *)(a1 + 1474) != 0 )
    {
      x = pt.x;
      y = pt.y;
      v66 = pt.x;
      if ( pt.x >= 38 && pt.x <= 83 && pt.y >= 371 && pt.y <= 385 && byte_89D274 != 0 )
      {
        *(uint32_t *)(a1 + 144) = 0;
        *(uint8_t *)(*(uint32_t *)(a1 + 76) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(a1 + 28) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(a1 + 80) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(a1 + 32) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(a1 + 84) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(a1 + 36) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(a1 + 88) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(a1 + 40) + 16) = 1;
        v22 = sub_69C3A0(*(uint32_t *)(a1 + 76));
        v23 = sub_69C500(*(uint32_t *)(a1 + 76)) - v22;
        if ( *(uint8_t *)(a1 + 1474) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 72) + 32))(*(uint32_t *)(a1 + 72), v23 <= 0 ? 0 : v23);
          v24 = sub_69C6A0(*(uint32_t *)(a1 + 72));
        }
        else
        {
          (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 56) + 32))(*(uint32_t *)(a1 + 56), v23 <= 0 ? 0 : v23);
          v24 = sub_69C6A0(*(uint32_t *)(a1 + 56));
        }
        sub_69C680(v24);
        x = v66;
      }
      if ( x >= 84
        && x <= 128
        && y >= 371
        && y <= 385
        && byte_89D274 != 0
        && sub_429830((uint16_t)word_77F804) != 0
        && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) != 0 )
      {
        *(uint32_t *)(a1 + 144) = 1;
        *(uint8_t *)(*(uint32_t *)(a1 + 76) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(a1 + 28) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(a1 + 80) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(a1 + 32) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(a1 + 84) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(a1 + 36) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(a1 + 88) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(a1 + 40) + 16) = 1;
        v25 = sub_69C3A0(*(uint32_t *)(a1 + 80));
        v26 = sub_69C500(*(uint32_t *)(a1 + 80)) - v25;
        if ( *(uint8_t *)(a1 + 1474) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 72) + 32))(*(uint32_t *)(a1 + 72), v26 <= 0 ? 0 : v26);
          v27 = sub_69C6A0(*(uint32_t *)(a1 + 72));
        }
        else
        {
          (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 56) + 32))(*(uint32_t *)(a1 + 56), v26 <= 0 ? 0 : v26);
          v27 = sub_69C6A0(*(uint32_t *)(a1 + 56));
        }
        sub_69C680(v27);
      }
    }
    if ( *(uint32_t *)(a1 + 144) != 4 )
    {
      if ( *(uint8_t *)(a1 + 1474) != 0 )
      {
        v28 = sub_69C690(*(uint32_t **)(a1 + 72));
        sub_69C400(*(uint32_t *)(a1 + 4 * *(uint32_t *)(a1 + 144) + 76), v28);
      }
      else
      {
        v63 = sub_69C690(*(uint32_t **)(a1 + 56));
        sub_69C400(*(uint32_t *)(a1 + 4 * *(uint32_t *)(a1 + 144) + 76), v63);
      }
    }
    v29 = sub_699000(a1 + 148);
    v30 = sub_69C500(*(uint32_t *)(a1 + 96)) - 1;
    if ( v30 >= 0 )
    {
      v31 = (uint32_t *)(a1 + 4 * v30 + 176);
      while ( v29 <= *v31 + 10000 )
      {
        --v30;
        --v31;
        if ( v30 < 0 )
          goto LABEL_60;
      }
      v32 = v30 + 1;
      sub_69C340(*(uint8_t **)(a1 + 96), v30 + 1);
      v33 = 20 - v32;
      if ( 20 - v32 > 0 )
      {
        v34 = (uint32_t *)(a1 + 176);
        v35 = (uint32_t *)(a1 + 4 * v32 + 176);
        do
        {
          *v34++ = *v35++;
          --v33;
        }
        while ( v33 != 0 );
      }
    }
LABEL_60:
    v36 = *(uint32_t *)(a1 + 100);
    if ( *(uint8_t *)(v36 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v36 + 12) )
      *(uint8_t *)(a1 + 1473) = *(uint8_t *)(a1 + 1473) == 0;
    v37 = *(uint32_t *)(a1 + 104);
    if ( *(uint8_t *)(v37 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v37 + 12)
      || *(uint8_t *)((v38 = *(uint32_t *)(a1 + 108)) + 17) != 0 && dword_79BE34 == *(uint32_t *)(v38 + 12) )
    {
      v39 = *(uint32_t *)(a1 + 108);
      v40 = *(uint8_t *)(a1 + 1474) == 0;
      *(uint8_t *)(a1 + 1474) = v40;
      if ( *(uint8_t *)(v39 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v39 + 12) )
      {
        if ( v40 )
        {
          v41 = sub_69C6A0(*(uint32_t *)(a1 + 72));
          v42 = *(uint32_t **)(a1 + 72);
        }
        else
        {
          v41 = sub_69C6A0(*(uint32_t *)(a1 + 56));
          v42 = *(uint32_t **)(a1 + 56);
        }
        v67 = sub_69C690(v42) == v41;
        v43 = *(uint8_t *)(a1 + 1474) != 0 ? 20 : 8;
        v44 = sub_69C500(*(uint32_t *)(a1 + 4 * *(uint32_t *)(a1 + 144) + 76)) - v43;
        v45 = *(uint8_t *)(a1 + 1474) != 0 ? *(uint32_t *)(a1 + 72) : *(uint32_t *)(a1 + 56);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v45 + 32))(v45, v44 <= 0 ? 0 : v44);
        if ( v67 )
        {
          if ( *(uint8_t *)(a1 + 1474) != 0 )
            v46 = sub_69C6A0(*(uint32_t *)(a1 + 72));
          else
            v46 = sub_69C6A0(*(uint32_t *)(a1 + 56));
          sub_69C680(v46);
        }
      }
    }
    v47 = dword_79BE54 == *(uint32_t *)(*(uint32_t *)(a1 + 136) + 12);
    if ( v47 != *(uint8_t *)(a1 + 256) )
      sub_43B920(v47);
    if ( *(uint8_t *)(a1 + 1473) != 0 )
    {
      v48 = *(uint32_t *)(a1 + 112);
      if ( *(uint8_t *)(v48 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v48 + 12) )
      {
        v49 = sub_43BBC0(a1);
        *(uint32_t *)(a1 + 4) = v49;
        if ( v49 != -1 )
        {
          switch ( v49 )
          {
            case 0:
              v50 = (bool *)(*(uint32_t *)(a1 + 144) + a1 + 1453);
              goto LABEL_92;
            case 1:
              v50 = (bool *)(*(uint32_t *)(a1 + 144) + a1 + 1457);
              goto LABEL_92;
            case 2:
              v50 = (bool *)(*(uint32_t *)(a1 + 144) + a1 + 1461);
              goto LABEL_92;
            case 3:
              v50 = (bool *)(*(uint32_t *)(a1 + 144) + a1 + 1465);
              goto LABEL_92;
            case 4:
              v50 = (bool *)(*(uint32_t *)(a1 + 144) + a1 + 1469);
LABEL_92:
              *v50 = !*v50;
              break;
            default:
              break;
          }
        }
      }
    }
    if ( *(uint8_t *)(a1 + 1475) != 0 )
    {
      v51 = *(uint32_t *)(a1 + 116);
      if ( *(uint8_t *)(v51 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v51 + 12) )
      {
        v52 = 0;
        v53 = 322;
        while ( pt.x < 61 || pt.x >= 94 || pt.y < v53 || pt.y >= v53 + 16 )
        {
          v53 += 17;
          ++v52;
          if ( v53 >= 390 )
            goto LABEL_114;
        }
        if ( v52 != -1 )
        {
          v54 = v52 - 1;
          if ( v54 != 0 )
          {
            v55 = v54 - 1;
            if ( v55 != 0 )
            {
              if ( v55 == 1 )
                *(uint32_t *)(a1 + 288) = 0;
            }
            else if ( sub_429830((uint16_t)word_77F804) != 0
                   && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) != 0 )
            {
              *(uint32_t *)(a1 + 288) = 1;
            }
          }
          else if ( sub_429830((uint16_t)word_77F804) != 0
                 && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 120) != 0 )
          {
            *(uint32_t *)(a1 + 288) = 2;
          }
        }
      }
    }
LABEL_114:
    LOBYTE(v8) = *(uint8_t *)(a1 + 256);
    if ( (uint8_t)v8 != 0 )
    {
      sub_4BF300(0, 0);
      if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_79C0B4 + 16))(
             dword_79C0B4,
             31,
             a2,
             a3) != 0 )
      {
        if ( *(uint32_t *)(a1 + 312) != 0 )
        {
          sub_43DA50(a1, 0, 0);
        }
        else
        {
          switch ( *(uint32_t *)(a1 + 288) )
          {
            case 0:
              if ( sub_429830((uint16_t)word_77F804) != 0
                && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) != 0 )
              {
                if ( sub_429830((uint16_t)word_77F804) != 0
                  && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) != 0 )
                {
                  *(uint32_t *)(a1 + 288) = 1;
                }
              }
              else
              {
                if ( *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 120) == 0 )
                  goto LABEL_132;
                if ( sub_429830((uint16_t)word_77F804) != 0 )
                  goto LABEL_130;
              }
              break;
            case 1:
              if ( dword_8F8500 == 0 || *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 120) == 0 )
                goto LABEL_132;
              if ( sub_429830((uint16_t)word_77F804) != 0 )
              {
LABEL_130:
                if ( *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 120) != 0 )
                  *(uint32_t *)(a1 + 288) = 2;
              }
              break;
            case 2:
LABEL_132:
              *(uint32_t *)(a1 + 288) = 3;
              break;
            case 3:
              *(uint32_t *)(a1 + 288) = 0;
              break;
            default:
              break;
          }
        }
      }
      v56 = *(uint32_t *)(a1 + 132);
      if ( *(uint8_t *)(v56 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v56 + 12) )
        *(uint8_t *)(a1 + 1475) = *(uint8_t *)(a1 + 1475) == 0;
      sub_43DBE0((uint32_t *)a1);
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 15) != 0
        && (*(uint32_t *)(a1 + 312) != 0 && *(uint8_t *)(a1 + 1794) != 0
         || *(uint8_t *)(a1 + 320) != 0 && *(uint8_t *)(a1 + 1794) != 0) )
      {
        *(uint8_t *)(a1 + 320) = 0;
        sub_43DA50(a1, 0, 0);
      }
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 2) != 0
        && *(int *)(a1 + 1448) > 0 )
      {
        v57 = *(uint32_t *)(a1 + 1444);
        if ( v57 > 0 )
        {
          if ( *(uint8_t *)(a1 + 320) != 0 )
            *(uint32_t *)(a1 + 1444) = v57 - 1;
        }
        else
        {
          *(uint32_t *)(a1 + 1444) = 0;
        }
        *(uint8_t *)(a1 + 1452) = 0;
        *(uint8_t *)(a1 + 320) = 1;
      }
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 3) != 0 )
      {
        v58 = *(uint32_t *)(a1 + 1448);
        if ( v58 > 0 )
        {
          v59 = *(uint32_t *)(a1 + 1444);
          v60 = v58 - 1;
          if ( v59 < v60 )
          {
            if ( *(uint8_t *)(a1 + 320) != 0 )
              *(uint32_t *)(a1 + 1444) = v59 + 1;
          }
          else
          {
            *(uint32_t *)(a1 + 1444) = v60;
          }
          *(uint8_t *)(a1 + 1452) = 0;
          *(uint8_t *)(a1 + 320) = 1;
        }
      }
      v61 = *(uint32_t *)(a1 + 136);
      if ( *(uint32_t *)(v61 + 192) != 0 )
        v8 = v61 + 180;
      else
        v8 = v61 + 160;
      LOBYTE(v8) = *(uint32_t *)(v8 + 12) == 0;
      *(uint8_t *)(a1 + 1794) = v8;
    }
  }
  return v8;
}


// ============================================================
// 【分区 2】脚本包体与标签解析（0x442280-0x4428C0）
// 日志转发桩 → Script.pvf 包体挂载（0x4422C0，_ScriptPacks/!ScriptPacks 目录探针）
// → token 数值解析族（0x4423D0/0x442480/0x442520/0x4425A0，%d/%x/%f 三型）
// → 职业标签族（0x4426A0）与元素标签族（0x442710/0x442780）。
// ============================================================
// ------------------------------------------------------------
// 0x442280 sub_442280
// ------------------------------------------------------------
int /*stdcall*/ sub_442280(char *Format)
{
  return off_77F3FC(Format);
}



// ------------------------------------------------------------
// 0x4422A0 sub_4422A0
// ------------------------------------------------------------
int /*stdcall*/ sub_4422A0(char *Format, int a2)
{
  return off_77F3FC(Format);
}



// ------------------------------------------------------------
// 0x4422C0 sub_4422C0
// ------------------------------------------------------------
// 脚本包根路径设置：拷贝路径到 byte_8F8898（补 \\ 或 / 结尾）；
// "_ScriptPacks" 存在 → byte_78FF3C=1；"!ScriptPacks" 不存在且标志置位 →
// sub_528DB0("Script.pvf") 打开脚本包体（0x528DB0 = pvf 挂载器）。
char /*cdecl*/ sub_4422C0(const char *a1)
{
  strcpy(byte_8F8898, a1);
  if ( byte_8F8897[strlen(byte_8F8898)] != 92 && byte_8F8897[strlen(byte_8F8898)] != 47 )
    *(uint16_t *)&byte_8F8898[strlen(byte_8F8898)] = 92;
  byte_78FF3C = 1;
  if ( _access("_ScriptPacks", 0) == 0 )
    byte_78FF3C = 1;
  if ( _access("!ScriptPacks", 0) != 0 )
  {
    if ( byte_78FF3C != 0 )
      sub_528DB0("Script.pvf");
    return 1;
  }
  else
  {
    byte_78FF3C = 0;
    return 1;
  }
}



// ------------------------------------------------------------
// 0x442390 sub_442390
// ------------------------------------------------------------
// 路径拼接：sprintf(出, "%s%s", 包根 byte_8F8898, vsprintf 后的格式串)
int sub_442390(char *Buffer, char *Format, ...)
{
  va_list va; // [esp+10h] [ebp+10h] BYREF

  va_start(va, Format);
  vsprintf(byte_97B258, Format, va);
  return sprintf(Buffer, "%s%s", byte_8F8898, byte_97B258);
}



// ------------------------------------------------------------
// 0x4423D0 sub_4423D0
// ------------------------------------------------------------
// token 数值解析：按 sub_65BE30 词法型别 2=%d / 3=%x / 4=%f 取值；*a1=是否可解析
int /*cdecl*/ sub_4423D0(uint8_t *a1)
{
  int v1; // eax
  int64_t v2; // rax
  float v4; // [esp+0h] [ebp-8h] BYREF
  int v5; // [esp+4h] [ebp-4h] BYREF

  v5 = 0;
  v1 = sub_65BE30(&unk_9789A0);
  if ( v1 == 2 )
  {
    sscanf(dword_9789A4, "%d", &v5);
    goto LABEL_5;
  }
  if ( v1 == 3 )
  {
    sscanf(dword_9789A4 + 2, "%x", &v5);
LABEL_5:
    if ( a1 != nullptr )
    {
      *a1 = 1;
      LODWORD(v2) = v5;
      return v2;
    }
LABEL_13:
    LODWORD(v2) = v5;
    return v2;
  }
  if ( v1 != 4 )
  {
    if ( a1 != nullptr )
      *a1 = 0;
    goto LABEL_13;
  }
  sscanf(dword_9789A4, "%f", &v4);
  if ( a1 != nullptr )
    *a1 = 1;
  return (uint64_t)v4;
}



// ------------------------------------------------------------
// 0x442480 sub_442480
// ------------------------------------------------------------
double /*cdecl*/ sub_442480(uint8_t *a1)
{
  int v1; // eax
  double result; // st7
  int v3; // [esp+0h] [ebp-8h] BYREF
  float v4; // [esp+4h] [ebp-4h] BYREF

  v4 = 0.0;
  v1 = sub_65BE30(&unk_9789A0);
  switch ( v1 )
  {
    case 2:
      sscanf(dword_9789A4, "%d", &v3);
LABEL_3:
      if ( a1 != nullptr )
        *a1 = 1;
      return (double)v3;
    case 3:
      sscanf(dword_9789A4 + 2, "%x", &v3);
      goto LABEL_3;
    case 4:
      sscanf(dword_9789A4, "%f", &v4);
      result = v4;
      if ( a1 != nullptr )
        *a1 = 1;
      break;
    default:
      result = v4;
      if ( a1 != nullptr )
        *a1 = 0;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x442520 sub_442520
// ------------------------------------------------------------
int /*cdecl*/ sub_442520(const char *a1)
{
  unsigned int v1; // ecx
  int v2; // eax
  int v3; // ecx
  char v5; // [esp+3h] [ebp-31h]
  char String; // [esp+4h] [ebp-30h] BYREF
  int v7; // [esp+5h] [ebp-2Fh]
  int v8; // [esp+9h] [ebp-2Bh]
  int v9; // [esp+Dh] [ebp-27h]
  int v10; // [esp+11h] [ebp-23h]
  int v11; // [esp+15h] [ebp-1Fh]
  int v12; // [esp+19h] [ebp-1Bh]
  int v13; // [esp+1Dh] [ebp-17h]
  int v14; // [esp+21h] [ebp-13h]
  int v15; // [esp+25h] [ebp-Fh]
  int v16; // [esp+29h] [ebp-Bh]
  int v17; // [esp+30h] [ebp-4h]

  v17 = dword_796E50;
  v1 = strlen(a1);
  v7 = 0;
  v8 = 0;
  v9 = 0;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  v13 = 0;
  v14 = 0;
  v15 = 0;
  v16 = 0;
  v2 = 1;
  v3 = v1 - 1;
  String = 0;
  if ( v3 > 1 )
  {
    do
    {
      *(&v5 + v2) = a1[v2];
      ++v2;
    }
    while ( v2 < v3 );
  }
  return j__atol(&String);
}



// ------------------------------------------------------------
// 0x4425A0 sub_4425A0
// ------------------------------------------------------------
uint8_t */*cdecl*/ sub_4425A0(const char *a1)
{
  unsigned int v1; // ecx
  int v2; // eax
  int v3; // ecx

  v1 = strlen(a1);
  v2 = 1;
  v3 = v1 - 1;
  if ( v3 > 1 )
  {
    do
    {
      byte_97B358[v2 - 1] = a1[v2];
      ++v2;
    }
    while ( v2 < v3 );
  }
  byte_97B357[v2] = 0;
  return byte_97B358;
}



// ------------------------------------------------------------
// 0x4425F0 sub_4425F0
// ------------------------------------------------------------
int /*cdecl*/ sub_4425F0(const char *a1)
{
  if ( strcmp(a1, "[close]") == 0 )
    return 0;
  if ( strcmp(a1, "[normal]") == 0 )
    return 1;
  if ( strcmp(a1, "[bottom]") == 0 )
    return 2;
  if ( strcmp(a1, "[closeback]") == 0 )
    return 3;
  if ( strcmp(a1, "[middleback]") == 0 )
    return 4;
  return (strcmp(a1, "[distantback]") != 0) + 5;
}



// ------------------------------------------------------------
// 0x4426A0 sub_4426A0
// ------------------------------------------------------------
// 职业标签→索引：[swordman]=0 / [fighter]=1 / [gunner]=2 / [mage]=3（strcmp 链自证）
int /*cdecl*/ sub_4426A0(const char *a1)
{
  if ( strcmp(a1, "[swordman]") == 0 )
    return 0;
  if ( strcmp(a1, "[fighter]") == 0 )
    return 1;
  if ( strcmp(a1, "[gunner]") == 0 )
    return 2;
  return (strcmp(a1, "[mage]") != 0) + 3;
}



// ------------------------------------------------------------
// 0x442710 sub_442710
// ------------------------------------------------------------
// 元素标签→索引：[fire]=0 / [water]=1 / [dark]=2 / [light]=3（strcmp 链自证）
int /*cdecl*/ sub_442710(const char *a1)
{
  if ( strcmp(a1, "[fire element]") == 0 )
    return 0;
  if ( strcmp(a1, "[water element]") == 0 )
    return 1;
  if ( strcmp(a1, "[dark element]") == 0 )
    return 2;
  return (strcmp(a1, "[light element]") != 0) + 3;
}



// ------------------------------------------------------------
// 0x442780 sub_442780
// ------------------------------------------------------------
// 当前元素标签 setter：按入参写全局 dword_97B384
// （"[water element]"/"[dark element]"/"[light element]"/缺省 "[fire element]"，
// 与 0x442710 索引一一对应；该全局即 UI/技能元素着色取词源）
int */*cdecl*/ sub_442780(int a1)
{
  if ( a1 != 0 )
  {
    if ( a1 == 1 )
    {
      strcpy((char *)&dword_97B384, "[water element]");
      return &dword_97B384;
    }
    else if ( a1 == 2 )
    {
      strcpy((char *)&dword_97B384, "[dark element]");
      return &dword_97B384;
    }
    else
    {
      if ( a1 == 3 )
        strcpy((char *)&dword_97B384, "[light element]");
      else
        strcpy((char *)&dword_97B384, "[no element]");
      return &dword_97B384;
    }
  }
  else
  {
    strcpy((char *)&dword_97B384, "[fire element]");
    return &dword_97B384;
  }
}



// ============================================================
// 【分区 3】字符串容器/管理器辅助（0x4428C0-0x444360）
// 28 字节/项的 std::string 数组搬运与查重；0x442E10 为
// RDARScriptStringManager 入口（"::ERROR::input NULL string" 自证）【推断】；
// 错误串二次使用于 0x443370；0x442EF0 = vector length_error 抛出（CRT 模板实体）。
// ============================================================
// ------------------------------------------------------------
// 0x4428C0 sub_4428C0
// ------------------------------------------------------------
int /*cdecl*/ sub_4428C0(const char *ArgList, const char *a2)
{
  FILE *v2; // eax
  FILE *v3; // esi
  signed int v5; // edi

  sub_442390(byte_97B398, "%s%s", ArgList, a2);
  v2 = fopen(byte_97B398, "rb");
  v3 = v2;
  if ( v2 == nullptr )
    return -1;
  fseek(v2, 0, 2);
  v5 = ftell(v3);
  fseek(v3, 0, 0);
  if ( v5 > 0x80000 )
    return -1;
  sub_66BD5A(byte_8F8998, v5, 1u, v3);
  fclose(v3);
  return v5;
}



// ------------------------------------------------------------
// 0x442950 sub_442950
// ------------------------------------------------------------
int /*cdecl*/ sub_442950(const char *ArgList, const char *a2)
{
  int result; // eax
  char Buffer[512]; // [esp+8h] [ebp-204h] BYREF
  int v4; // [esp+208h] [ebp-4h]

  v4 = dword_796E50;
  sprintf(Buffer, "%s%s", ArgList, a2);
  result = sub_528650((int)Buffer, byte_8F8998, 0x80000);
  if ( result == 0 )
  {
    off_77F3FC("readScriptFromPVF : script error %s%s ", ArgList, a2);
    return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4429C0 sub_4429C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4429C0(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 60;
  return result;
}



// ------------------------------------------------------------
// 0x4429F0 sub_4429F0
// ------------------------------------------------------------
int /*cdecl*/ sub_4429F0(int a1)
{
  int result; // eax
  int i; // ecx

  result = a1;
  for ( i = *(uint32_t *)(a1 + 8); *(uint8_t *)(i + 45) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x442A10 sub_442A10
// ------------------------------------------------------------
char /*cdecl*/ sub_442A10(const char *ArgList, const char *a2)
{
  char *v2; // esi
  int v3; // eax

  if ( dword_978998 != nullptr )
    dword_978998();
  if ( byte_78FF3C == 0 || strcmp(a2, "../DebugConfig.txt") == 0 )
  {
    v2 = (char *)ArgList;
    v3 = sub_4428C0(ArgList, a2);
  }
  else
  {
    v2 = (char *)ArgList;
    v3 = sub_442950(ArgList, a2);
  }
  if ( v3 == -1 )
    return 0;
  sub_65D4D0(v2, (int)a2, byte_8F8998, v3);
  return 1;
}



// ------------------------------------------------------------
// 0x442A80 sub_442A80
// ------------------------------------------------------------
int /*thiscall*/ sub_442A80(std::_String_base *this, unsigned int a2)
{
  if ( *((uint32_t *)this + 5) <= a2 )
    std::_String_base::_Xran(this);
  if ( *((uint32_t *)this + 6) < 0x10u )
    return (int)this + a2 + 4;
  else
    return *((uint32_t *)this + 1) + a2;
}



// ------------------------------------------------------------
// 0x442AC0 sub_442AC0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_442AC0(uint32_t *this, int a2)
{
  uint32_t *result; // eax
  int v3; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(a2 + 8);
  *(uint32_t *)(a2 + 8) = *result;
  if ( *(uint8_t *)(*result + 45) == 0 )
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
// 0x442B20 sub_442B20
// ------------------------------------------------------------
void /*cdecl*/ sub_442B20(std::_String_base *a1)
{
  char *v1; // esi
  int v2; // esi
  int v3; // eax

  if ( dword_78FF38 != -1 )
  {
    if ( *((uint32_t *)a1 + 5) == 0 )
      std::_String_base::_Xran(a1);
    v1 = *((uint32_t *)a1 + 6) < 0x10u ? (char *)a1 + 4 : *((char **)a1 + 1);
    if ( *v1 != 91 )
    {
      v2 = *v1 & 0x7F;
      if ( v2 != dword_78FF38 )
      {
        v3 = sub_65BE30(&unk_9789A0);
        if ( v3 != 0 )
        {
          while ( v3 < 14 || v3 >= 17 || v2 != v3 - 13 )
          {
            v3 = sub_65BE30(&unk_9789A0);
            if ( v3 == 0 )
              goto LABEL_16;
          }
        }
        else
        {
LABEL_16:
          off_77F3FC("ignoreNationalTag - Nation code pair mismatch");
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x442BC0 sub_442BC0
// ------------------------------------------------------------
char /*cdecl*/ sub_442BC0(std::_String_base *a1)
{
  char *v1; // esi
  int v2; // esi
  int v3; // eax

  if ( dword_78FF38 == -1 )
    return 0;
  if ( *((uint32_t *)a1 + 5) == 0 )
    std::_String_base::_Xran(a1);
  v1 = *((uint32_t *)a1 + 6) < 0x10u ? (char *)a1 + 4 : *((char **)a1 + 1);
  if ( *v1 == 91 )
    return 0;
  v2 = *v1 & 0x7F;
  v3 = sub_65BE30(&unk_9789A0);
  if ( v3 == 0 )
  {
LABEL_15:
    off_77F3FC("ignoreNationalTag - Nation code pair mismatch");
    return 0;
  }
  while ( v3 < 14 || v3 >= 17 || v2 != v3 - 13 )
  {
    v3 = sub_65BE30(&unk_9789A0);
    if ( v3 == 0 )
      goto LABEL_15;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x442C50 sub_442C50
// ------------------------------------------------------------
int /*thiscall*/ sub_442C50(int this)
{
  if ( *(uint32_t *)(this + 28) >= 0x10u )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x442C80 sub_442C80
// ------------------------------------------------------------
char /*cdecl*/ sub_442C80(char a1, void **Block, int a3, int a4, int a5, int a6, unsigned int a7)
{
  void **p_Block; // ecx

  if ( a6 == 0 )
    std::_String_base::_Xran((std::_String_base *)&a1);
  p_Block = Block;
  if ( a7 < 0x10 )
    p_Block = (void **)&Block;
  if ( *(uint8_t *)p_Block == 91 )
  {
    if ( a7 >= 0x10 )
      j__free(Block);
    return 0;
  }
  else
  {
    if ( a7 >= 0x10 )
      j__free(Block);
    return 1;
  }
}



// ------------------------------------------------------------
// 0x442D00 sub_442D00
// ------------------------------------------------------------
int **/*thiscall*/ sub_442D00(int **this, int **a2, uint32_t *a3)
{
  int *v3; // edx
  int *v4; // eax

  v3 = *(this + 1);
  v4 = (int *)v3[1];
  while ( *((uint8_t *)v4 + 45) == 0 )
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
// 0x442D70 sub_442D70
// ------------------------------------------------------------
int /*thiscall*/ sub_442D70(int this)
{
  if ( *(uint32_t *)(this + 40) >= 0x10u )
    j__free(*(void **)(this + 20));
  *(uint32_t *)(this + 40) = 15;
  *(uint32_t *)(this + 36) = 0;
  *(uint8_t *)(this + 20) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x442DA0 sub_442DA0
// ------------------------------------------------------------
int */*thiscall*/ sub_442DA0(int **this, int a2)
{
  int *v4; // [esp+4h] [ebp-4h] BYREF

  sub_442D00(this, &v4, &a2);
  if ( v4 == *(this + 1) )
    return nullptr;
  if ( (unsigned int)v4[10] < 0x10 )
    return v4 + 5;
  return (int *)v4[5];
}



// ------------------------------------------------------------
// 0x442DF0 sub_442DF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_442DF0(int *this, uint32_t *a2, int a3)
{
  int v3; // esi

  v3 = *this;
  sub_40BEA0(this);
  *a2 = v3;
  return a2;
}



// ------------------------------------------------------------
// 0x442E10 sub_442E10
// ------------------------------------------------------------
// RDARScriptStringManager 入口：空串防御 "RDARScriptStringManager::ERROR::input NULL string"【推断】
char sub_442E10()
{
  int v0; // eax
  int v1; // eax
  int v3; // eax

  v0 = sub_65BE30(&unk_9789A0) - 7;
  if ( v0 != 0 )
  {
    if ( v0 == 2 )
    {
      sub_442520(dword_9789A4);
      if ( sub_65BE30(&unk_9789A0) == 10 )
      {
        v1 = sub_4425A0(dword_9789A4);
        if ( v1 != 0 )
        {
          v3 = sub_529100(v1);
          sub_41BFE0(v3);
        }
        else
        {
          sub_41BFE0("RDARScriptStringManager::ERROR::input NULL string");
        }
        return 1;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    sub_41BFE0(byte_979DF8);
    return 1;
  }
}



// ------------------------------------------------------------
// 0x442EB0 sub_442EB0
// ------------------------------------------------------------
std::_String_base */*cdecl*/ sub_442EB0(int a1, int a2, std::_String_base *a3)
{
  int v3; // esi
  std::_String_base *v4; // edi

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    sub_4014D0(v4, v3, 0, -1);
    v3 += 28;
    v4 = (std::_String_base *)((char *)v4 + 28);
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x442EF0 sub_442EF0
// ------------------------------------------------------------
void /*noreturn*/ sub_442EF0()
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
// 0x442F60 sub_442F60
// ------------------------------------------------------------
int ***/*thiscall*/ sub_442F60(uint32_t *this, int ***a2, int **a3)
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
  int v17; // eax
  uint32_t *v18; // eax
  int v19; // eax
  void **pExceptionObject; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v22[20]; // [esp+34h] [ebp-34h] BYREF
  int v23; // [esp+48h] [ebp-20h]
  int v24; // [esp+4Ch] [ebp-1Ch]
  int v25; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *v27; // [esp+58h] [ebp-10h]
  int v28; // [esp+64h] [ebp-4h]

  v27 = this;
  if ( *((uint8_t *)a3 + 45) != 0 )
  {
    v24 = 15;
    v23 = 0;
    v22[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);
    v28 = 0;
    sub_401740(v22);
    pExceptionObject = &std::out_of_range::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_40BEA0(&a3);
  if ( *((uint8_t *)*v3 + 45) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 45) == 0 )
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
      if ( *((uint8_t *)v4 + 45) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = sub_6600D0(v4);
        v7 = v27;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v25 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 45) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v25 + 8) = sub_4429F0(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)v3[2] + 45) != 0 )
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
    if ( *((uint8_t *)v4 + 45) == 0 )
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
  v14 = *((uint8_t *)v5 + 44);
  *((uint8_t *)v5 + 44) = *((uint8_t *)v3 + 44);
  *((uint8_t *)v3 + 44) = v14;
LABEL_35:
  v15 = (void **)Block;
  if ( *((uint8_t *)Block + 44) == 1 )
  {
    v16 = v27;
    if ( v4 != *(int **)(v27[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 44) != 1 )
          break;
        v17 = *v6;
        if ( v4 == (int *)*v6 )
        {
          v17 = v6[2];
          if ( *(uint8_t *)(v17 + 44) == 0 )
          {
            *(uint8_t *)(v17 + 44) = 1;
            *((uint8_t *)v6 + 44) = 0;
            sub_442AC0(v6);
            v17 = v6[2];
            v16 = v27;
          }
          if ( *(uint8_t *)(v17 + 45) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)v17 + 44) != 1 || *(uint8_t *)(*(uint32_t *)(v17 + 8) + 44) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)(v17 + 8) + 44) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)v17 + 44) = 1;
              *(uint8_t *)(v17 + 44) = 0;
              sub_433290(v17);
              v17 = v6[2];
            }
            *(uint8_t *)(v17 + 44) = *((uint8_t *)v6 + 44);
            *((uint8_t *)v6 + 44) = 1;
            *(uint8_t *)(*(uint32_t *)(v17 + 8) + 44) = 1;
            sub_442AC0(v6);
            break;
          }
        }
        else
        {
          if ( *(uint8_t *)(v17 + 44) == 0 )
          {
            *(uint8_t *)(v17 + 44) = 1;
            *((uint8_t *)v6 + 44) = 0;
            sub_433290(v6);
            v17 = *v6;
            v16 = v27;
          }
          if ( *(uint8_t *)(v17 + 45) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)(v17 + 8) + 44) != 1 || *(uint8_t *)(*(uint32_t *)v17 + 44) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)v17 + 44) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)(v17 + 8) + 44) = 1;
              *(uint8_t *)(v17 + 44) = 0;
              sub_442AC0(v17);
              v17 = *v6;
            }
            *(uint8_t *)(v17 + 44) = *((uint8_t *)v6 + 44);
            *((uint8_t *)v6 + 44) = 1;
            *(uint8_t *)(*(uint32_t *)v17 + 44) = 1;
            sub_433290(v6);
            break;
          }
        }
        *(uint8_t *)(v17 + 44) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(v16[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    v15 = (void **)Block;
    *((uint8_t *)v4 + 44) = 1;
  }
  if ( (unsigned int)v15[10] >= 0x10 )
    j__free(v15[5]);
  v18 = Block;
  *((uint32_t *)Block + 10) = 15;
  v18[9] = 0;
  *((uint8_t *)v18 + 20) = 0;
  j__free(v18);
  v19 = v27[2];
  if ( v19 != 0 )
    v27[2] = v19 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x443240 sub_443240
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_443240(uint32_t *this, int a2, int a3, int a4, uint32_t *a5, char a6)
{
  *this = a2;
  *(this + 1) = a3;
  *(this + 2) = a4;
  *(this + 3) = *a5;
  *(this + 10) = 15;
  *(this + 9) = 0;
  *((uint8_t *)this + 20) = 0;
  sub_4014D0((std::_String_base *)(this + 4), a5 + 1, 0, -1);
  *((uint8_t *)this + 44) = a6;
  *((uint8_t *)this + 45) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4432A0 sub_4432A0
// ------------------------------------------------------------
std::_String_base */*cdecl*/ sub_4432A0(int a1, int a2, std::_String_base *a3)
{
  return sub_442EB0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4432C0 sub_4432C0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4432C0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
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
    sub_4014D0((std::_String_base *)(v4 + 1), v3 + 1, 0, -1);
    v3 += 8;
    v4 += 8;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x443300 sub_443300
// ------------------------------------------------------------
int sub_443300(int a1, char *Format, ...)
{
  signed int i; // eax
  char v3; // cl
  va_list va; // [esp+10h] [ebp+10h] BYREF

  va_start(va, Format);
  vsprintf(&byte_97B598, Format, va);
  for ( i = strlen(&byte_97B598) - 1; i >= 0; --i )
  {
    v3 = *(&byte_97B598 + i);
    if ( v3 == 92 )
      break;
    if ( v3 == 47 )
      break;
  }
  byte_97B599[i] = 0;
  return sub_4015C0(&byte_97B598, strlen(&byte_97B598));
}



// ------------------------------------------------------------
// 0x443370 sub_443370
// ------------------------------------------------------------
char sub_443370()
{
  int v0; // eax
  int v1; // eax
  char *v2; // eax

  v0 = sub_65BE30(&unk_9789A0) - 7;
  if ( v0 != 0 )
  {
    if ( v0 == 2 )
    {
      sub_442520(dword_9789A4);
      if ( sub_65BE30(&unk_9789A0) == 10 )
      {
        v1 = sub_4425A0(dword_9789A4);
        if ( v1 != 0 )
          v2 = (char *)sub_529100(v1);
        else
          v2 = "RDARScriptStringManager::ERROR::input NULL string";
        sub_4015C0(v2, strlen(v2));
        return 1;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    sub_4015C0(byte_979DF8, strlen(byte_979DF8));
    return 1;
  }
}



// ------------------------------------------------------------
// 0x443430 sub_443430
// ------------------------------------------------------------
char /*cdecl*/ sub_443430(std::_String_base *a1)
{
  int v1; // eax
  char v2; // bl

  v1 = sub_65BE30(&unk_9789A0);
  v2 = v1;
  if ( v1 == 5 )
  {
    sub_4015C0(dword_9789A4, strlen(dword_9789A4));
    return 1;
  }
  else if ( v1 < 11 || v1 >= 14 )
  {
    return 0;
  }
  else
  {
    sub_4015C0(dword_9789A4, strlen(dword_9789A4));
    *(uint8_t *)sub_442A80(a1, 0) = (v2 - 10) | 0x80;
    return 1;
  }
}



// ------------------------------------------------------------
// 0x4434C0 sub_4434C0
// ------------------------------------------------------------
char /*stdcall*/ sub_4434C0(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 45);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_4434C0(i[2]);
    i = (void **)*i;
    sub_442D70((int)v1);
    j__free(v1);
    result = *((uint8_t *)i + 45);
  }
  return result;
}



// ------------------------------------------------------------
// 0x443510 sub_443510
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_443510(int a1, int a2, int a3, uint32_t *a4, char a5)
{
  uint32_t *v5; // esi
  void *v7[9]; // [esp+0h] [ebp-24h] BYREF

  v7[5] = v7;
  v5 = operator new(0x30u);
  v7[4] = v5;
  v7[8] = (void *)1;
  v7[3] = v5;
  if ( v5 != nullptr )
    sub_443240(v5, a1, a2, a3, a4, a5);
  return v5;
}



// ------------------------------------------------------------
// 0x4435A0 sub_4435A0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4435A0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_4432C0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4435C0 sub_4435C0
// ------------------------------------------------------------
int /*cdecl*/ sub_4435C0(int a1, int a2, int a3)
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
// 0x443660 sub_443660
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_443660(int *this, uint32_t *a2, char a3, uint32_t *a4, uint32_t *a5)
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

  if ( (unsigned int)*(this + 2) >= 0x7FFFFFE )
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
  v6 = sub_443510(*(this + 1), (int)a4, *(this + 1), a5, 0);
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
  if ( *(uint8_t *)(v6[1] + 44) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 44) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_442AC0(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 44) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 44) = 0;
          sub_433290(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 44) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_433290(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 44) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 44) = 0;
        sub_442AC0(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 44) = 1;
      *(uint8_t *)(v14 + 44) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 44) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 44) != 0 )
      {
        v6 = v21;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 44) = 1;
  *a2 = v6;
  return a2;
}



// ------------------------------------------------------------
// 0x443810 sub_443810
// ------------------------------------------------------------
int */*thiscall*/ sub_443810(int **this, int *a2, int a3, int a4)
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
    sub_4434C0(*(void ***)(v7 + 4));
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
        if ( *(uint8_t *)(v5 + 45) == 0 )
        {
          v11 = *(uint32_t *)(v5 + 8);
          if ( *(uint8_t *)(v11 + 45) != 0 )
          {
            for ( i = *(uint32_t *)(v5 + 4); *(uint8_t *)(i + 45) == 0; i = *(uint32_t *)(i + 4) )
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
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 45) == 0; j = *(uint32_t *)j )
              v5 = j;
          }
        }
        sub_442F60(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x4438D0 sub_4438D0
// ------------------------------------------------------------
void /*thiscall*/ sub_4438D0(int *this)
{
  int v2; // eax

  v2 = *(this + 1);
  if ( v2 != 0 )
  {
    sub_4166A0(v2, *(this + 2));
    j__free((void *)*(this + 1));
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
}



// ------------------------------------------------------------
// 0x443920 sub_443920
// ------------------------------------------------------------
int /*cdecl*/ sub_443920(uint32_t *a1, uint32_t *a2, int a3)
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
      *(uint32_t *)(v3 + 28) = 15;
      *(uint32_t *)(v3 + 24) = 0;
      *(uint8_t *)(v3 + 8) = 0;
      sub_4014D0((std::_String_base *)(v3 + 4), a1 + 1, 0, -1);
    }
    v3 += 32;
    LOBYTE(v7) = 0;
    a1 += 8;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x4439F0 sub_4439F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4439F0(int *this, int a2, uint32_t *a3)
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
  if ( *((uint8_t *)v6 + 45) == 0 )
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
    while ( *((uint8_t *)v6 + 45) == 0 );
  }
  v9 = v5;
  a3 = v5;
  if ( v7 )
  {
    if ( v5 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_443660(this, &a3, 1, v5, v3);
      *(uint8_t *)(a2 + 4) = 1;
      *(uint32_t *)a2 = v10;
      return a2;
    }
    sub_501430(&a3);
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
    v12 = *sub_443660(this, &a3, v13, v5, v3);
    *(uint32_t *)a2 = v12;
    *(uint8_t *)(a2 + 4) = 1;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x443AB0 sub_443AB0
// ------------------------------------------------------------
int /*thiscall*/ sub_443AB0(int this, int a2)
{
  int v2; // edi
  int v4; // eax
  unsigned int v5; // ecx
  std::_String_base *v7; // ebx
  unsigned int v8; // eax
  std::_String_base *v9; // eax
  int v10; // eax
  unsigned int v11; // eax
  int v12; // edi
  int v13; // eax

  v2 = a2;
  if ( this == a2 )
    return this;
  v4 = *(uint32_t *)(a2 + 4);
  if ( v4 == 0 || (v5 = (*(uint32_t *)(a2 + 8) - v4) / 28) == 0 )
  {
    sub_4438D0((int *)this);
    return this;
  }
  v7 = *(std::_String_base **)(this + 4);
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
      v11 = (*(uint32_t *)(this + 12) - (int)v7) / 28;
    }
    else
    {
      v11 = 0;
    }
    if ( v5 <= v11 )
    {
      v12 = *(uint32_t *)(a2 + 4) + 28 * sub_52AEF0(this);
      sub_4432A0(*(uint32_t *)(a2 + 4), v12, v7);
      *(uint32_t *)(this + 8) = sub_4166E0(v12, *(uint32_t *)(a2 + 8), *(uint32_t *)(this + 8), this);
      return this;
    }
    if ( v7 != nullptr )
    {
      sub_416820(v7, *(uint32_t *)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v13 = sub_52AEF0(v2);
    if ( (uint8_t)sub_41D930(v13) != 0 )
      *(uint32_t *)(this + 8) = sub_416840(*(uint32_t *)(v2 + 4), *(uint32_t *)(v2 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  v9 = sub_442EB0(*(uint32_t *)(v2 + 4), *(uint32_t *)(v2 + 8), v7);
  sub_4166A0(v9, *(uint32_t *)(this + 8));
  v10 = *(uint32_t *)(v2 + 4);
  if ( v10 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 28 * ((*(uint32_t *)(v2 + 8) - v10) / 28);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x443C40 sub_443C40
// ------------------------------------------------------------
char /*cdecl*/ sub_443C40(int *a1, const char *ArgList, const char *a3)
{
  char result; // al
  uint32_t *v4; // eax
  int v5; // edi
  int *v6; // [esp+0h] [ebp-5Ch] BYREF
  int v7; // [esp+4h] [ebp-58h] BYREF
  uint8_t v8[4]; // [esp+8h] [ebp-54h] BYREF
  void *Block; // [esp+Ch] [ebp-50h]
  int v10; // [esp+1Ch] [ebp-40h]
  unsigned int v11; // [esp+20h] [ebp-3Ch]
  uint8_t v12[4]; // [esp+24h] [ebp-38h] BYREF
  int i; // [esp+28h] [ebp-34h] BYREF
  char v14; // [esp+2Fh] [ebp-2Dh] BYREF
  uint8_t v15[4]; // [esp+30h] [ebp-2Ch] BYREF
  void *v16; // [esp+34h] [ebp-28h]
  int v17; // [esp+44h] [ebp-18h]
  unsigned int v18; // [esp+48h] [ebp-14h]
  int v19; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]

  v19 = dword_796E50;
  result = sub_442A10(ArgList, a3);
  if ( result != 0 )
  {
    sub_4434C0(*(void ***)(a1[1] + 4));
    *(uint32_t *)(a1[1] + 4) = a1[1];
    v4 = (uint32_t *)a1[1];
    a1[2] = 0;
    *v4 = v4;
    *(uint32_t *)(a1[1] + 8) = a1[1];
    v18 = 15;
    v17 = 0;
    LOBYTE(v16) = 0;
    v20 = 0;
    v5 = sub_4423D0(&v14);
    for ( i = v5; v14 != 0; i = v5 )
    {
      if ( sub_443370() == 0 )
        break;
      if ( *sub_442D00((int **)a1, &v6, &i) == (int *)a1[1] )
      {
        v7 = v5;
        v11 = 15;
        v10 = 0;
        LOBYTE(Block) = 0;
        sub_4014D0((std::_String_base *)v8, v15, 0, -1);
        LOBYTE(v20) = 1;
        sub_4439F0(a1, (int)v12, &v7);
        LOBYTE(v20) = 0;
        if ( v11 >= 0x10 )
          j__free(Block);
        v11 = 15;
        v10 = 0;
        LOBYTE(Block) = 0;
      }
      else
      {
        off_77F3FC("SCRIPT FILE LIST LOAD FAIL! [%s%s][%d]", ArgList, a3, v5);
      }
      v5 = sub_4423D0(&v14);
    }
    if ( v18 >= 0x10 )
      j__free(v16);
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x443DB0 sub_443DB0
// ------------------------------------------------------------
int */*thiscall*/ sub_443DB0(int *this, int a2)
{
  int v2; // eax
  int v5; // [esp-14h] [ebp-34h]
  int v6; // [esp-10h] [ebp-30h]
  int v7; // [esp-Ch] [ebp-2Ch]
  uint32_t v8[8]; // [esp+0h] [ebp-20h] BYREF

  v2 = *(uint32_t *)(a2 + 4);
  v8[4] = v8;
  v8[3] = this;
  if ( v2 != 0 )
    v2 = (*(uint32_t *)(a2 + 8) - v2) / 28;
  if ( (uint8_t)sub_41D930(v2) != 0 )
  {
    v7 = *(this + 1);
    v6 = *(uint32_t *)(a2 + 8);
    v5 = *(uint32_t *)(a2 + 4);
    v8[7] = 0;
    *(this + 2) = sub_4435C0(v5, v6, v7);
  }
  return this;
}



// ------------------------------------------------------------
// 0x443E50 sub_443E50
// ------------------------------------------------------------
int */*thiscall*/ sub_443E50(int *this, int *a2)
{
  uint32_t *v3; // ebx
  unsigned int v4; // eax
  uint32_t *v6; // ecx
  unsigned int v7; // edx
  uint32_t *v8; // eax
  int v9; // eax
  int v10; // edi
  unsigned int v11; // edx
  int v12; // eax
  uint32_t *v13; // ebx
  int v14; // ecx
  unsigned int v15; // eax

  if ( this == a2 )
    return this;
  v3 = (uint32_t *)a2[1];
  if ( v3 == nullptr || (v4 = (a2[2] - (int)v3) >> 5) == 0 )
  {
    sub_422340(this);
    return this;
  }
  v6 = (uint32_t *)*(this + 1);
  if ( v6 != nullptr )
    v7 = (*(this + 2) - (int)v6) >> 5;
  else
    v7 = 0;
  if ( v4 <= v7 )
  {
    v8 = sub_4432C0(v3, (uint32_t *)a2[2], v6);
    sub_422220((int)v8, *(this + 2));
    v9 = a2[1];
    if ( v9 != 0 )
      v10 = *(this + 1) + 32 * ((a2[2] - v9) >> 5);
    else
      v10 = *(this + 1);
    *(this + 2) = v10;
    return this;
  }
  if ( v6 != nullptr )
    v11 = (*(this + 3) - (int)v6) >> 5;
  else
    v11 = 0;
  if ( v4 > v11 )
  {
    if ( v6 != nullptr )
    {
      sub_422220((int)v6, *(this + 2));
      j__free((void *)*(this + 1));
    }
    v14 = a2[1];
    if ( v14 != 0 )
      v15 = (a2[2] - v14) >> 5;
    else
      v15 = 0;
    if ( sub_421B80(this, v15) != 0 )
      *(this + 2) = sub_422250((uint32_t *)a2[1], (uint32_t *)a2[2], *(this + 1));
    return this;
  }
  if ( v6 != nullptr )
    v12 = (*(this + 2) - (int)v6) >> 5;
  else
    v12 = 0;
  v13 = (uint32_t *)(a2[1] + 32 * v12);
  sub_4435A0((uint32_t *)a2[1], v13, (uint32_t *)*(this + 1));
  *(this + 2) = sub_421C10(v13, (uint32_t *)a2[2], *(this + 2));
  return this;
}



// ------------------------------------------------------------
// 0x443FB0 sub_443FB0
// ------------------------------------------------------------
void /*thiscall*/ sub_443FB0(int this)
{
  int v2; // eax
  int v3; // esi

  v2 = *(uint32_t *)(this + 48);
  v3 = this + 44;
  if ( v2 != 0 )
  {
    sub_4166A0(v2, *(uint32_t *)(this + 52));
    j__free(*(void **)(v3 + 4));
  }
  *(uint32_t *)(v3 + 4) = 0;
  *(uint32_t *)(v3 + 8) = 0;
  *(uint32_t *)(v3 + 12) = 0;
  sub_422340((int *)(this + 28));
  if ( *(uint32_t *)(this + 24) >= 0x10u )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 15;
  *(uint8_t *)(this + 4) = 0;
}



// ------------------------------------------------------------
// 0x444020 sub_444020
// ------------------------------------------------------------
int /*thiscall*/ sub_444020(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_443810((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x444060 sub_444060
// ------------------------------------------------------------
int */*thiscall*/ sub_444060(int *this, int a2)
{
  int v3; // ecx
  unsigned int v4; // eax
  uint32_t *v6; // [esp-14h] [ebp-34h]
  uint32_t *v7; // [esp-10h] [ebp-30h]
  int v8; // [esp-Ch] [ebp-2Ch]
  uint32_t v9[8]; // [esp+0h] [ebp-20h] BYREF

  v3 = *(uint32_t *)(a2 + 4);
  v9[4] = v9;
  v9[3] = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(a2 + 8) - v3) >> 5;
  else
    v4 = 0;
  if ( sub_421B80(this, v4) != 0 )
  {
    v8 = *(this + 1);
    v7 = *(uint32_t **)(a2 + 8);
    v6 = *(uint32_t **)(a2 + 4);
    v9[7] = 0;
    *(this + 2) = sub_443920(v6, v7, v8);
  }
  return this;
}



// ------------------------------------------------------------
// 0x444100 sub_444100
// ------------------------------------------------------------
int */*cdecl*/ sub_444100(int a1, int a2, int *a3)
{
  int v3; // esi
  int *v4; // edi

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v3 -= 60;
    v4 -= 15;
    sub_4014D0((std::_String_base *)v4, v3, 0, -1);
    sub_443E50(v4 + 7, (int *)(v3 + 28));
    sub_443AB0((int)(v4 + 11), v3 + 44);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x444150 sub_444150
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_444150(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax

  v2 = sub_433B80();
  *(this + 1) = v2;
  *((uint8_t *)v2 + 45) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  sub_4434C0(*(void ***)(*(this + 1) + 4));
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  v3 = (uint32_t *)*(this + 1);
  *(this + 2) = 0;
  *v3 = v3;
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  return this;
}



// ------------------------------------------------------------
// 0x4441E0 sub_4441E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4441E0(int this, int a2)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((std::_String_base *)this, a2, 0, -1);
  sub_444060((int *)(this + 28), a2 + 28);
  sub_443DB0((int *)(this + 44), a2 + 44);
  return this;
}



// ------------------------------------------------------------
// 0x444260 sub_444260
// ------------------------------------------------------------
int */*cdecl*/ sub_444260(int *a1, int *a2, int a3)
{
  int *result; // eax
  int *i; // esi

  result = a2;
  for ( i = a1; i != a2; i += 15 )
  {
    sub_4014D0((std::_String_base *)i, a3, 0, -1);
    sub_443E50(i + 7, (int *)(a3 + 28));
    sub_443AB0((int)(i + 11), a3 + 44);
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4442B0 sub_4442B0
// ------------------------------------------------------------
int */*cdecl*/ sub_4442B0(int a1, int a2, int *a3)
{
  return sub_444100(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4442D0 sub_4442D0
// ------------------------------------------------------------
int /*cdecl*/ sub_4442D0(int a1, int a2, int a3)
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
      sub_4441E0(v3, a1);
    v3 += 60;
    LOBYTE(v7) = 0;
    a1 += 60;
  }
  return v3;
}



// ============================================================
// 【分区 4】CNMainGameModule 虚表槽（0x444360-0x444E70）
// vmt8=0x444C20 模块退出清理 / vmt4=0x444C60 每帧 tick（模块心跳）。
// 两函数已由 docs/13 §1 定案并 L1 逐行精修于 src/game/module/CNMainGameModule.cpp
// （vmt4 流程：帧钩→场景推进→震动档→fade 状态机→发包 type=40），此处保留 L2 转写体。
// ============================================================
// ------------------------------------------------------------
// 0x444360 sub_444360
// ------------------------------------------------------------
int /*cdecl*/ sub_444360(int a1, int a2, int a3)
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
      result = sub_4441E0(v3, a3);
    --a2;
    v3 += 60;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4443F0 sub_4443F0
// ------------------------------------------------------------
int /*stdcall*/ sub_4443F0(int a1, int a2, int a3)
{
  sub_444360(a1, a2, a3);
  return a1 + 60 * a2;
}



// ------------------------------------------------------------
// 0x444420 sub_444420
// ------------------------------------------------------------
void /*stdcall*/ sub_444420(int a1, int a2)
{
  int i; // esi

  for ( i = a1; i != a2; i += 60 )
    sub_443FB0(i);
}



// ------------------------------------------------------------
// 0x444450 sub_444450
// ------------------------------------------------------------
int /*thiscall*/ sub_444450(int *this, int a2, unsigned int a3, int a4)
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
  int v20; // [esp-18h] [ebp-80h]
  int v21; // [esp-10h] [ebp-78h]
  int v22; // [esp-Ch] [ebp-74h]
  unsigned int v23; // [esp-8h] [ebp-70h]
  uint32_t v24[4]; // [esp+0h] [ebp-68h] BYREF
  void *Block; // [esp+10h] [ebp-58h]
  char *v26; // [esp+14h] [ebp-54h]
  uint8_t v27[60]; // [esp+18h] [ebp-50h] BYREF
  int v28; // [esp+54h] [ebp-14h]
  uint32_t *v29; // [esp+58h] [ebp-10h]
  int v30; // [esp+64h] [ebp-4h]
  char *v31; // [esp+70h] [ebp+8h]
  int v32; // [esp+74h] [ebp+Ch]

  v28 = dword_796E50;
  v29 = v24;
  v24[3] = this;
  sub_4441E0(a4);
  v5 = *(this + 1);
  v6 = 0;
  v30 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 60;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - *(this + 1)) / 60;
    else
      v8 = 0;
    if ( 71582788 - v8 < a3 )
      sub_442EF0(this);
    if ( *(this + 1) != 0 )
      v9 = (*(this + 2) - *(this + 1)) / 60;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = (char *)*(this + 2);
      Block = v16;
      if ( (int)&v16[-a2] / 60 >= a3 )
      {
        v31 = &v16[-60 * a3];
        *(this + 2) = sub_4442D0(v31, v16, v16);
        sub_4442B0(a2, v31, Block);
        sub_444260(a2, a2 + 60 * a3, v27);
      }
      else
      {
        sub_4442D0(a2, v16, a2 + 60 * a3);
        v23 = a3 - (*(this + 2) - a2) / 60;
        v22 = *(this + 2);
        LOBYTE(v30) = 3;
        sub_4443F0(v22, v23, v27);
        v18 = 60 * a3 + *(this + 2);
        *(this + 2) = v18;
        v30 = 0;
        sub_444260(a2, v18 - 60 * a3, v27);
      }
    }
    else
    {
      if ( 71582788 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        v11 = (*(this + 2) - *(this + 1)) / 60;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_4429C0(this);
      v32 = 60 * v10;
      v12 = (char *)operator new(60 * v10);
      v20 = *(this + 1);
      Block = v12;
      v26 = v12;
      LOBYTE(v30) = 1;
      v26 = (char *)sub_4442D0(v20, a2, v12);
      sub_444360(v26, a3, v27);
      v21 = *(this + 2);
      v26 += 60 * a3;
      sub_4442D0(a2, v21, v26);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 60;
      v14 = v13 + a3;
      v15 = *(this + 1);
      if ( v15 != 0 )
      {
        sub_444420(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v32];
      *(this + 2) = (int)&v12[60 * v14];
      *(this + 1) = (int)v12;
    }
  }
  return sub_443FB0(v27);
}


// ------------------------------------------------------------
// 0x444770 sub_444770
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_444770(int *this, uint32_t *a2, int *a3, int a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 60 != 0 )
    v6 = ((int)a3 - v5) / 60;
  else
    v6 = 0;
  sub_444450(this, a3, 1u, a4);
  *a2 = *(this + 1) + 60 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x4447E0 sub_4447E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4447E0(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 60 )
      sub_443FB0(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x444820 sub_444820
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_444820(int this, int a2)
{
  int v3; // ebx
  unsigned int v4; // esi
  int v5; // esi
  uint32_t *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 60;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 60 )
    return sub_444770((int *)this, &a2, *(int **)(this + 8), a2);
  v5 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_444360(v5, 1, a2);
  *(uint32_t *)(this + 8) = v5 + 60;
  return result;
}



// ------------------------------------------------------------
// 0x4448B0 sub_4448B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4448B0(uint32_t *this)
{
  sub_444150(this);
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x444930 sub_444930
// ------------------------------------------------------------
char /*thiscall*/ sub_444930(void *this, void *ArgList)
{
  int v3; // eax
  uint8_t v5[20]; // [esp+8h] [ebp-4Ch] BYREF
  int v6; // [esp+1Ch] [ebp-38h]
  int v7; // [esp+20h] [ebp-34h]
  int v8; // [esp+28h] [ebp-2Ch]
  int v9; // [esp+2Ch] [ebp-28h]
  int v10; // [esp+30h] [ebp-24h]
  int v11; // [esp+38h] [ebp-1Ch]
  int v12; // [esp+3Ch] [ebp-18h]
  int v13; // [esp+40h] [ebp-14h]
  int v14; // [esp+44h] [ebp-10h]
  int v15; // [esp+50h] [ebp-4h]

  v14 = dword_796E50;
  v7 = 15;
  v6 = 0;
  v5[4] = 0;
  v8 = 0;
  v9 = 0;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  v13 = 0;
  v15 = 2;
  if ( byte_78FF3C != 0 )
    v3 = sub_5297C0(ArgList);
  else
    v3 = sub_529920(ArgList);
  switch ( v3 )
  {
    case -3:
      off_77F3FC(aErrorAddstring_1, ArgList);
      goto LABEL_10;
    case -2:
      off_77F3FC(aErrorAddstring_0, ArgList);
      goto LABEL_10;
    case -1:
      off_77F3FC(aErrorAddstring, ArgList);
      goto LABEL_10;
    case 0:
      sub_444820((int)this + 12, (int)v5);
      sub_443FB0((int)v5);
      return 1;
    default:
      off_77F3FC(aErrorAddstring_2, ArgList, v3);
LABEL_10:
      sub_443FB0((int)v5);
      return 0;
  }
}



// ------------------------------------------------------------
// 0x444A40 sub_444A40
// ------------------------------------------------------------
char /*cdecl*/ sub_444A40(const char *a1)
{
  const char *v1; // edi
  char result; // al
  int v3; // ebx
  int v4; // esi
  const char *v5; // eax
  int v6; // [esp+4h] [ebp-20Ch] BYREF
  int *v7; // [esp+8h] [ebp-208h] BYREF
  char Buffer[512]; // [esp+Ch] [ebp-204h] BYREF
  int v9; // [esp+20Ch] [ebp-4h]

  v9 = dword_796E50;
  v1 = "Script/";
  if ( byte_78FF3C != 0 )
    v1 = szPassword;
  result = sub_443C40((int *)&dword_97B22C, szPassword, a1);
  if ( result != 0 )
  {
    v3 = dword_97B234;
    v4 = 0;
    if ( dword_97B234 <= 0 )
    {
      return 1;
    }
    else
    {
      while ( 1 )
      {
        v6 = v4;
        sub_442D00(&dword_97B22C, &v7, &v6);
        if ( v7 == (int *)dword_97B230 )
          v5 = nullptr;
        else
          v5 = (unsigned int)v7[10] < 0x10 ? (const char *)(v7 + 5) : (const char *)v7[5];
        sprintf(Buffer, "%s%s", v1, v5);
        if ( sub_444930(&dword_97B22C, Buffer) == 0 )
          break;
        if ( ++v4 >= v3 )
          return 1;
      }
      return 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x444B30 sub_444B30
// ------------------------------------------------------------
char /*thiscall*/ sub_444B30(uint32_t *this, int a2)
{
  int v3; // ecx
  char result; // al

  v3 = (int)(this + 6);
  *(this + 5) = a2;
  *(uint8_t *)(v3 + 13) = 0;
  *(uint8_t *)(v3 + 14) = 0;
  result = sub_698F90(v3, 0, 0);
  *(this + 15) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x444B60 sub_444B60
// ------------------------------------------------------------
char /*thiscall*/ sub_444B60(int this)
{
  char result; // al

  result = *(uint8_t *)(this + 4);
  if ( result == 0 )
  {
    *(uint32_t *)(this + 12) = 0;
    *(uint32_t *)(this + 16) = 0;
    *(uint32_t *)(this + 20) = 0;
    *(uint32_t *)(this + 52) = 0;
    *(uint32_t *)(this + 56) = 0;
    *(uint32_t *)(this + 60) = 0;
    byte_97B6A5 = 0;
    byte_97B6A6 = 0;
    byte_97B6C1 = 0;
    byte_97B6C2 = 0;
    sub_698F90((int)&unk_97B698, 100, 0);
    sub_698F90((int)&unk_97B6B4, 100, 0);
    *(uint8_t *)(this + 105) = 0;
    *(uint8_t *)(this + 106) = 0;
    sub_698F90(this + 92, 0, 0);
    *(uint32_t *)(this + 120) = 0;
    return sub_699030(this + 92);
  }
  return result;
}



// ------------------------------------------------------------
// 0x444BE0 sub_444BE0
// ------------------------------------------------------------
char /*thiscall*/ sub_444BE0(int this)
{
  char result; // al
  float *v3; // ecx

  result = *(uint8_t *)(this + 4);
  if ( result != 0 )
  {
    *(uint32_t *)(this + 20) = 0;
    *(uint8_t *)(this + 37) = 0;
    *(uint8_t *)(this + 38) = 0;
    sub_698F90(this + 24, 0, 0);
    v3 = *(float **)(this + 16);
    *(uint32_t *)(this + 60) = 0;
    return sub_424EA0(v3, 1.0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x444C20 CNMainGameModule__vmt8
// ------------------------------------------------------------
// CNMainGameModule::vmt8 模块退出清理 —— L1 精修版见 src/game/module/CNMainGameModule.cpp:238
int /*thiscall*/ CNMainGameModule__vmt8(uint32_t *this)
{
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B0 + 28))(dword_79C0B0, 0);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 84))(dword_79C0B0);
  sub_69AB00(*(this + 3));
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 88))(dword_79C0B0);
  return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_79C0A4 + 4))(dword_79C0A4, 0, 0);
}



// ------------------------------------------------------------
// 0x444C60 CNMainGameModule__vmt4
// ------------------------------------------------------------
// CNMainGameModule::vmt4 每帧 tick（模块心跳）—— docs/13 §1 定案全流程：
// 帧钩 sub_4AEB30 → 主帧循环 sub_433690 → 场景推进 → 用户震动档 → fade 状态机。
// L1 逐行精修版见 src/game/module/CNMainGameModule.cpp:152；此处保留 L2 转写体。
char /*thiscall*/ CNMainGameModule__vmt4(int this)
{
  int v3; // eax
  int v4; // edx
  uint64_t v5; // rax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  float v10; // [esp+4h] [ebp-4h]

  sub_4AEB30(&unk_9A02B0);
  sub_433690();
  if ( *(uint32_t *)(this + 20) != 0 )
  {
    sub_699030(this + 92);
  }
  else
  {
    if ( *(uint8_t *)(this + 106) != 0 )
      sub_698FE0(this + 92);
    v3 = sub_699000(this + 92);
    v4 = *(uint32_t *)(this + 120);
    *(uint32_t *)(this + 120) = v3;
    v10 = (double)(v3 - v4) * 0.001;
    sub_655A90(v10);
  }
  switch ( *(uint32_t *)(dword_8F8548 + 8) )
  {
    case 0:
      sub_424EA0(*(float **)(this + 16), 0.0);
      break;
    case 1:
      sub_424EA0(*(float **)(this + 16), 0.30000001);
      break;
    case 2:
      sub_424EA0(*(float **)(this + 16), 0.69999999);
      break;
    case 3:
      sub_424EA0(*(float **)(this + 16), 1.0);
      break;
    default:
      break;
  }
  sub_4294E0(*(uint32_t *)(this + 16));
  LODWORD(v5) = *(uint32_t *)(this + 20);
  if ( (uint32_t)v5 != 0 )
  {
    switch ( (uint32_t)v5 )
    {
      case 1:
        if ( *(uint32_t *)(this + 60) == 255 )
        {
          sub_475810(*(int **)(*(uint32_t *)(this + 16) + 108), this, *(uint32_t *)(this + 52), *(uint32_t *)(this + 56));
          sub_4284C0(*(uint32_t *)(this + 52), *(uint32_t *)(this + 56));
          sub_423200(dword_8F7B08, 40);
          sub_423380(dword_8F7B08);
          *(uint32_t *)(this + 20) = 2;
          *(uint8_t *)(this + 37) = 0;
          *(uint8_t *)(this + 38) = 0;
          LOBYTE(v5) = sub_698F90(this + 24, 0, 0);
          *(uint32_t *)(this + 60) = 0;
        }
        else
        {
          v6 = sub_699000(this + 24);
          v5 = (uint64_t)sub_4049C0(0.0, 255.0, v6, 250);
          *(uint32_t *)(this + 60) = v5;
          *((uint32_t *)dword_8F8528 + 621) = v5;
        }
        break;
      case 2:
LABEL_27:
        break;
      case 3:
        v7 = sub_699000(this + 24);
        v5 = (uint64_t)sub_4049C0(255.0, 0.0, v7, 250);
        *(uint32_t *)(this + 60) = v5;
        *((uint32_t *)dword_8F8528 + 621) = v5;
        LODWORD(v5) = *(uint32_t *)(this + 60);
        if ( (uint32_t)v5 == 0 )
          LOBYTE(v5) = sub_444B30(0);
        break;
      case 4:
        if ( *(uint32_t *)(this + 60) == 255 )
        {
          LOBYTE(v5) = sub_41D300(1);
        }
        else
        {
          v8 = sub_699000(this + 24);
          LODWORD(v5) = sub_423A80(0, 255, v8, 500);
          *(uint32_t *)(this + 60) = v5;
          *((uint32_t *)dword_8F8528 + 621) = v5;
        }
        break;
      default:
        goto LABEL_27;
    }
  }
  return v5;
}



// ============================================================
// 【分区 5】战斗分发器共享工具（0x444E70-0x4451F0）
// 被 bigfunc_4471E0（sub_4471E0 = CNRDUdpModule::vmt0）直接调用：
//   0x4450E0 ← case 0x18 / 0x445120 ← case 0x14 / 0x445150 ← case 0xA 收尾 /
//   0x4451C0 ← case 0xF（进图音效旗标）。
// ============================================================
// ------------------------------------------------------------
// 0x444E70 sub_444E70
// ------------------------------------------------------------
char /*thiscall*/ sub_444E70(uint32_t *this, int a2, int a3)
{
  int v4; // ecx

  *(this + 14) = a3;
  v4 = (int)(this + 6);
  *(this + 13) = a2;
  *(this + 5) = 1;
  *(uint8_t *)(v4 + 13) = 0;
  *(uint8_t *)(v4 + 14) = 0;
  sub_698F90(v4, 0, 0);
  *(this + 15) = 0;
  sub_65DC70(lpCriticalSection);
  return sub_425960(1, *(uint32_t *)(*(this + 4) + 44), *(int ***)(*(this + 4) + 104));
}



// ------------------------------------------------------------
// 0x444ED0 sub_444ED0
// ------------------------------------------------------------
char /*thiscall*/ sub_444ED0(int this)
{
  char result; // al

  sub_425960(0, *(uint32_t *)(*(uint32_t *)(this + 16) + 44), *(int ***)(*(uint32_t *)(this + 16) + 104));
  *(uint32_t *)(this + 20) = 3;
  *(uint8_t *)(this + 37) = 0;
  *(uint8_t *)(this + 38) = 0;
  result = sub_698F90(this + 24, 0, 0);
  *(uint32_t *)(this + 60) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x444F10 sub_444F10
// ------------------------------------------------------------
void /*thiscall*/ sub_444F10(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void *v3; // edi

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
    *(uint32_t *)(this + 16) = 0;
  }
}



// ------------------------------------------------------------
// 0x444F60 sub_444F60
// ------------------------------------------------------------
char /*thiscall*/ sub_444F60(int this)
{
  char result; // al
  uint8_t *v3; // eax
  uint8_t *v4; // eax
  char *v5; // eax
  char *v6; // eax
  float *v7; // ecx

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
    sub_69A840(*((uint32_t *)dword_8F8528 + 2));
    sub_69A840(*((uint32_t *)dword_8F8528 + 3));
    sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 16) + 40));
    result = sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));
    if ( *(uint8_t *)(this + 4) != 0 )
    {
      *(uint32_t *)(this + 20) = 0;
      *(uint8_t *)(this + 37) = 0;
      *(uint8_t *)(this + 38) = 0;
      sub_698F90(this + 24, 0, 0);
      v7 = *(float **)(this + 16);
      *(uint32_t *)(this + 60) = 0;
      return sub_424EA0(v7, 1.0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x445080 sub_445080
// ------------------------------------------------------------
int /*thiscall*/ sub_445080(uint32_t *this, int a2)
{
  if ( *(uint32_t *)(sub_656710() + 4 * a2) == -1 )
    return 0;
  else
    return *(this + a2 + 262162);
}



// ------------------------------------------------------------
// 0x4450B0 sub_4450B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4450B0(void *this, int a2)
{
  int v3; // esi
  int v4; // edx

  v3 = a2 + sub_41A5E0((unsigned int)this);
  sub_41A590((unsigned int)this, v4, v3);
  return v3;
}



// ------------------------------------------------------------
// 0x4450E0 sub_4450E0
// ------------------------------------------------------------
// 分发器 case 0x18 落点：场景级事件处理【推断】
int /*thiscall*/ sub_4450E0(void *this)
{
  unsigned int v1; // esi
  int v2; // eax
  int v3; // edx

  v1 = (unsigned int)this + 148;
  v2 = sub_41A5E0((unsigned int)this + 148);
  return sub_41A590(v1, v3, v2 + 1);
}



// ------------------------------------------------------------
// 0x445100 sub_445100
// ------------------------------------------------------------
int /*cdecl*/ sub_445100(int a1, int a2)
{
  return sub_657740(a1, a2);
}



// ------------------------------------------------------------
// 0x445120 sub_445120
// ------------------------------------------------------------
// 分发器 case 0x14 落点：命中侧查询（返回真走 sub_495470(+v174[1668]) 分支）
BOOL /*thiscall*/ sub_445120(int *this)
{
  int v1; // eax

  v1 = *(this + 1639);
  return v1 == 4 || v1 == 9 || *(this + 81) <= 0 && (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) > 0;
}



// ------------------------------------------------------------
// 0x445150 sub_445150
// ------------------------------------------------------------
// 分发器 case 0xA 收尾：装备同步资源清理（v306 结构池回收）
int /*thiscall*/ sub_445150(char *this)
{
  sub_41A580(this + 46);
  sub_41A580(this + 32);
  sub_41A580(this + 18);
  return sub_41A580(this + 4);
}



// ------------------------------------------------------------
// 0x4451C0 sub_4451C0
// ------------------------------------------------------------
// 分发器 case 0xF 落点：进图音效旗标（48001 已播标记）
char /*thiscall*/ sub_4451C0(uint8_t *this, char a2)
{
  int v2; // ecx

  *(this + 552) = a2;
  v2 = (int)(this + 540);
  *(uint8_t *)(v2 + 13) = 0;
  *(uint8_t *)(v2 + 14) = 0;
  return sub_698F90(v2, 1500, 0);
}



// ============================================================
// 【分区 6】CNRDUdpModule 虚表族 + CNRDParticle 族（0x4451F0-0x449EB0）
// 战斗分发器宿主类（VT 006C46B4，docs/11 排期表）。vmt 槽实测：
// vmt8/3C/5C/60/64(队友入场 @@ADD PEER 2)/68/7C/88/90(按场景取操作角色)/98/A8/AC/B0；
// UDP 回报落地 0x4456C0；PVP/WARROOM 被动物体绑定 0x446130/0x446190；
// 分发器 case 2/5 读包配套 0x446960-0x446CF0；粒子族 0x445C10-0x445EF0。
// 分发器本体见 src/game/bigfunc_4471E0_sub_4471E0.cpp。
// ============================================================
// ------------------------------------------------------------
// 0x4451F0 CNRDUdpModule__vmtA8
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmtA8(int this)
{
  int result; // eax
  uint32_t *v3; // ecx
  int i; // edx

  DeleteFileA("UDP.log");
  DeleteFileA("PACKET.log");
  result = 0;
  *(uint32_t *)(this + 1048596) = 0;
  *(uint32_t *)(this + 1048600) = 0;
  *(uint8_t *)(this + 1048644) = 0;
  *(uint32_t *)(this + 1048648) = 0;
  *(uint32_t *)(this + 1048904) = 0;
  *(uint32_t *)(this + 1048652) = 0;
  *(uint32_t *)(this + 1048908) = 0;
  *(uint32_t *)(this + 1048656) = 0;
  *(uint32_t *)(this + 1048912) = 0;
  *(uint32_t *)(this + 1048660) = 0;
  *(uint32_t *)(this + 1048916) = 0;
  *(uint32_t *)(this + 1048664) = 0;
  *(uint32_t *)(this + 1048920) = 0;
  *(uint32_t *)(this + 1048668) = 0;
  *(uint32_t *)(this + 1048924) = 0;
  *(uint32_t *)(this + 1048672) = 0;
  *(uint32_t *)(this + 1048928) = 0;
  *(uint32_t *)(this + 1048676) = 0;
  *(uint32_t *)(this + 1048932) = 0;
  *(uint8_t *)(this + 1048645) = 1;
  *(uint8_t *)(this + 1048944) = 0;
  *(uint32_t *)(this + 1049172) = 0;
  *(uint32_t *)(this + 1049176) = 0;
  *(uint32_t *)(this + 1049180) = 0;
  *(uint32_t *)(this + 1049184) = 0;
  *(uint32_t *)(this + 1049188) = 0;
  *(uint32_t *)(this + 1049192) = 0;
  *(uint32_t *)(this + 1049196) = 0;
  *(uint32_t *)(this + 1049200) = 0;
  v3 = (uint32_t *)(this + 1049412);
  for ( i = 45; i != 0; --i )
  {
    *(v3 - 45) = 0;
    *v3 = 0;
    v3[45] = 0;
    v3[90] = 0;
    ++v3;
  }
  *(uint32_t *)(this + 1049952) = 0;
  *(uint8_t *)(this + 1049992) = 0;
  *(uint16_t *)(this + 1049994) = 0;
  *(uint8_t *)(this + 1050009) = 0;
  *(uint8_t *)(this + 1050010) = 0;
  *(uint8_t *)(this + 1050008) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x445320 CNRDUdpModule__vmtAC
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmtAC(uint32_t *this)
{
  int v2; // ecx
  int result; // eax

  v2 = (int)(this + 262151);
  *(uint8_t *)(v2 + 13) = 0;
  *(uint8_t *)(v2 + 14) = 0;
  sub_698F90(v2, 0, 0);
  if ( operator new(0xA00u) != nullptr )
  {
    if ( this != nullptr )
      result = sub_657410(this + 1);
    else
      result = sub_657410(0);
  }
  else
  {
    result = 0;
  }
  *(this + 262497) = result;
  return result;
}



// ------------------------------------------------------------
// 0x4453B0 CNRDUdpModule__vmtB0
// ------------------------------------------------------------
char /*thiscall*/ CNRDUdpModule__vmtB0(uint32_t *this)
{
  int v1; // esi

  v1 = *(this + 262497);
  sub_6676C0();
  if ( *(uint32_t *)(v1 + 2492) != -1 )
  {
    closesocket(*(uint32_t *)(v1 + 2492));
    *(uint32_t *)(v1 + 2492) = -1;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x4453C0 CNRDUdpModule__vmt8
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt8(uint32_t *this, int16_t a2, char a3)
{
  int v4; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 20))(this);
  v4 = *(this + 262147);
  *(uint16_t *)(v4 + 1) = a2;
  *(uint8_t *)v4 = a3;
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 12))(this, *(this + 262147) + 7);
}



// ------------------------------------------------------------
// 0x445400 CNRDUdpModule__vmt3C
// ------------------------------------------------------------
char /*userpurge*/ sub_445400@<al>(int a1@<ecx>, int a2@<edi>, void *a3, void *Block)
{
  int v5; // eax
  uint8_t *v6; // ebx
  int v7; // edi
  void *v8; // ecx
  int v9; // eax
  int v10; // eax
  void *v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edi
  int v17; // [esp-14h] [ebp-20h]
  int v18; // [esp-10h] [ebp-1Ch]
  int v19; // [esp-10h] [ebp-1Ch]
  int v20; // [esp-10h] [ebp-1Ch]
  void *v21; // [esp-Ch] [ebp-18h]
  int v22; // [esp-8h] [ebp-14h]
  int v24; // [esp+8h] [ebp-4h]
  uint32_t *Blocka; // [esp+18h] [ebp+Ch]

  LOWORD(v5) = *(uint16_t *)(a1 + 13);
  v6 = (uint8_t *)(a1 + 12);
  if ( (uint16_t)v5 == 0 || *(uint8_t *)(a1 + 1048645) != 0 )
  {
    (*(void (**)(int, const char *, ...))(*(uint32_t *)a1 + 140))(a1, "SEND %d %d", (uint16_t)v5, *v6);
    if ( (*v6 == 1 || *v6 == 2) && (uint8_t)a3 != 0 )
    {
      *(uint8_t *)(a1 + 1049217) = 0;
      *(uint8_t *)(a1 + 1049218) = 0;
      sub_698F90(a1 + 1049204, 0, 0);
    }
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 16))(a1) - 7;
    *(uint32_t *)(v6 + 3) = sub_48BE40(a1 + 19, v7);
    sub_48BD40(a1 + 19, v7, 0);
    if ( *(uint16_t *)(v6 + 1) == 0 )
    {
      v8 = Block;
LABEL_9:
      v22 = (uint8_t)a3;
      v21 = v8;
LABEL_10:
      v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 16))(a1);
LABEL_11:
      v18 = v9;
      sub_656710(v6);
      LOBYTE(v5) = sub_656EF0(v17, v18, v21, v22);
      return v5;
    }
    if ( *(int *)(a1 + 1048600) > 0 )
    {
      LOBYTE(v5) = *v6;
      if ( *v6 != 0 )
      {
        if ( (uint8_t)v5 != 1 )
        {
          if ( (uint8_t)v5 != 2 )
            return v5;
          v22 = (int)Block;
          v21 = a3;
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 136))(a1);
          v12 = sub_656710((uint8_t)a3);
          v13 = sub_656840(v12);
          v9 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 16))(a1, v13, v19);
          goto LABEL_11;
        }
      }
      else
      {
        v10 = sub_656710(a2);
        v11 = (void *)sub_656840(v10);
        v8 = Block;
        if ( Block == v11 )
          goto LABEL_9;
      }
      LOBYTE(v5) = (*(int (/*thiscall*/ **)(int, void *, void *))(*(uint32_t *)a1 + 136))(a1, a3, Block);
      return v5;
    }
    if ( *v6 == 0 )
    {
      v5 = sub_445080(Block);
      if ( v5 != 0 )
        return v5;
      v22 = (uint8_t)a3;
      v21 = Block;
      goto LABEL_10;
    }
    v14 = ((int (*)(void))sub_656710)();
    v24 = sub_656840(v14);
    LOBYTE(v5) = a1 + 72;
    v15 = 0;
    Blocka = (uint32_t *)(a1 + 1048648);
    do
    {
      if ( *v6 != 1 || v15 != v24 )
      {
        v5 = ((int (*)(void))sub_656710)();
        if ( *(uint32_t *)(v5 + 4 * v15) != -1 || v15 == v24 )
        {
          v5 = ((int (*)(void))sub_656710)();
          if ( *(uint32_t *)(v5 + 4 * v15) == -1 || *Blocka == 0 )
          {
            v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 16))(a1);
            ((void (*)(void))sub_656710)();
            LOBYTE(v5) = sub_656EF0((int)v6, v20, (void *)v15, (uint8_t)a3);
          }
        }
      }
      ++v15;
      ++Blocka;
    }
    while ( v15 < 8 );
  }
  return v5;
}


// ------------------------------------------------------------
// 0x4455F0 CNRDUdpModule__vmt5C
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt5C(int *this, int a2)
{
  int v3; // eax
  int v5; // [esp+4h] [ebp-4h] BYREF

  v3 = *this;
  v5 = 0;
  (*(void (/*thiscall*/ **)(int *, int *))(v3 + 80))(this, &v5);
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 88))(this, a2, v5);
  return v5;
}



// ------------------------------------------------------------
// 0x445630 CNRDUdpModule__vmt60
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt60(void *this, int a2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 92))(this, a2);
  *(uint8_t *)(result + a2) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x445650 CNRDUdpModule__vmt90
// ------------------------------------------------------------
// 按当前场景取"操作角色"：城镇/普通场景取模块上下文槽[v0]，PVP(场景4)走 sub_48F690、
// WARROOM(场景6)走 sub_578E80；越界或目标 +0xC4 字段为空时回退本地玩家 0x8F7C04。
// （会话 5 审计后重跑补齐：原为 decomp failed）
int sub_445650()
{
  int v0 = *(int*)(sub_656710() + 40);          // 声音通道表 +40 = 当前席位索引
  if (v0 < 0)
    return dword_8F7C04;
  int scene = *(int*)(dword_8F7A24 + 12);       // 场景状态
  int v2;
  if (scene == 4) {                             // PVP
    if (v0 >= 8 || dword_99FEC0 == 0)
      return dword_8F7C04;
    v2 = sub_48F690(v0);
  } else if (scene == 6) {                      // WARROOM
    if (v0 >= 8 || dword_99FF08 == 0)
      return dword_8F7C04;
    v2 = sub_578E80(v0);
  } else {                                      // 城镇/副本
    if (v0 >= 4)
      return dword_8F7C04;
    v2 = *(int*)(dword_8F850C + 4 * v0 + 16);   // 模块上下文表
  }
  if (v2 == 0)
    return dword_8F7C04;
  if (*(int*)(v2 + 0xC4) != 0)
    return *(int*)(v2 + 0xC4);                  // 目标角色
  return dword_8F7C04;
}


// ------------------------------------------------------------
// 0x4456C0 sub_4456C0
// ------------------------------------------------------------
// 分发器 case 0 配套：UDP 回报落地 —— 按模块类型 4(PVP)→sub_48F690 通道、
// 6(WARROOM)→对应通道分发【推断】；与 0x446CF0 成对使用
int /*thiscall*/ sub_4456C0(void *this, int a2, int a3, char a4)
{
  int result; // eax
  int v6; // ebx
  int v7; // edi
  int v8; // edx

  result = *(uint32_t *)(dword_8F7A24 + 12);
  if ( result == 4 )
  {
    if ( dword_99FEC0 == 0 )
      return result;
    v6 = sub_48F690(a2);
    result = sub_48F5A0();
  }
  else if ( result == 6 )
  {
    if ( dword_99FF08 == 0 )
      return result;
    v6 = sub_578E80(a2);
    result = sub_48FCA0();
  }
  else
  {
    v6 = *(uint32_t *)(dword_8F850C + 4 * a2 + 16);
    result = sub_456420(dword_8F850C);
  }
  v7 = result;
  if ( v6 != 0 && result != -1 )
  {
    (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t))(*(uint32_t *)this + 8))(this, 0, 0);
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 32))(this, v7);
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 32))(this, a3);
    if ( a4 != 0 )
      (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 32))(this, 1);
    else
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 32))(this, 0);
    v8 = *(uint32_t *)dword_8F8520;
    if ( a3 == 2 )
      return (*(int (/*stdcall*/ **)(int, int))(v8 + 60))(1, a2);
    else
      return (*(int (/*stdcall*/ **)(uint32_t, int))(v8 + 60))(0, a2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4457A0 CNRDUdpModule__vmt68
// ------------------------------------------------------------
int /*stdcall*/ CNRDUdpModule__vmt68(int a1)
{
  int v2; // [esp-4h] [ebp-8h]

  sub_656710(a1);
  sub_6568C0(v2);
  return sub_656560(a1);
}



// ------------------------------------------------------------
// 0x4457D0 sub_4457D0
// ------------------------------------------------------------
char /*thiscall*/ sub_4457D0(uint8_t *this, char a2)
{
  char result; // al

  result = a2;
  *(this + 1048645) = a2;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
    return sub_52AF20(*((uint32_t *)dword_8F8528 + 8));
  return result;
}



// ------------------------------------------------------------
// 0x445800 CNRDUdpModule__vmt7C
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt7C(uint32_t *this, int a2)
{
  int result; // eax

  result = a2;
  *(this + 262149) = a2;
  if ( a2 != 0 )
  {
    result = *(uint32_t *)(a2 + 44);
    if ( result != 0 )
    {
      result = *(uint32_t *)(result + 356);
      dword_9A012C = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x445830 sub_445830
// ------------------------------------------------------------
char /*thiscall*/ sub_445830(uint8_t *this, char a2)
{
  char result; // al
  uint8_t *v3; // esi
  int i; // edi

  result = a2;
  *(this + 1048944) = a2;
  if ( a2 != 0 )
  {
    v3 = this + 1048962;
    for ( i = 8; i != 0; --i )
    {
      *(v3 - 1) = 0;
      *v3 = 0;
      result = sub_698F90((int)(v3 - 14), 0, 0);
      v3 += 28;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x445870 sub_445870
// ------------------------------------------------------------
int /*thiscall*/ sub_445870(uint32_t *this, int a2, int a3)
{
  int v3; // esi

  v3 = a3;
  a2 = *(this + 262496) + 10 * a2;
  if ( a3 != 0 )
    return sub_4D33A0(&a2) % v3;
  else
    return sub_4D33A0(&a2);
}



// ------------------------------------------------------------
// 0x4458C0 sub_4458C0
// ------------------------------------------------------------
char /*thiscall*/ sub_4458C0(uint32_t *this)
{
  int v2; // eax

  if ( (uint8_t)sub_6572C0(*(this + 262497)) == 0 )
    return 0;
  sub_656710();
  v2 = sub_656800();
  sub_657670(*(this + 262497), v2);
  return 1;
}



// ------------------------------------------------------------
// 0x4458F0 sub_4458F0
// ------------------------------------------------------------
void /*stdcall*/ sub_4458F0(bool (/*cdecl*/ *a1)(struct Concurrency::details::_UnrealizedChore *, void *), void *a2)
{
  int v2; // edi
  Concurrency::details::ContextBase *v3; // eax
  bool (/*cdecl*/ *v4)(struct Concurrency::details::_UnrealizedChore *, void *); // [esp+0h] [ebp-8h]

  sub_656710();
  v2 = *((uint32_t *)a1 + 2);
  if ( v2 == sub_656800() )
  {
    v3 = (Concurrency::details::ContextBase *)sub_656710();
    Concurrency::details::ContextBase::SweepUnstructured(v3, a1, a2, v4);
  }
  else
  {
    sub_40BE20((char *)&byte_6C6044, *((uint32_t *)a1 + 1));
  }
}



// ------------------------------------------------------------
// 0x445940 sub_445940
// ------------------------------------------------------------
// 对端就绪查询：宿主(+0x100200 处指针)+2224 标志为 0 即就绪（分发器配套）
bool /*thiscall*/ sub_445940(uint32_t *this)
{
  return *(uint8_t *)(*(this + 262497) + 2224) == 0;
}



// ------------------------------------------------------------
// 0x445960 sub_445960
// ------------------------------------------------------------
void /*thiscall*/ sub_445960(uint8_t *this)
{
  int v2; // ecx
  int v3; // ebx
  int v4; // ecx
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // esi
  Concurrency::details::ContextBase *v8; // eax
  char v9; // al
  void *v10; // [esp+0h] [ebp-10h]
  bool (/*cdecl*/ *v11)(struct Concurrency::details::_UnrealizedChore *, void *); // [esp+4h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-4h]

  v2 = (int)(this + 1049996);
  *(uint8_t *)(v2 + 13) = 0;
  *(uint8_t *)(v2 + 14) = 0;
  *(this + 1050008) = 1;
  sub_698F90(v2, dword_78FF60, 0);
  v3 = 0;
  v4 = -1050040 - (uint32_t)this;
  v5 = this + 1050056;
  for ( i = -1050040 - (uint32_t)this; ; v4 = i )
  {
    v6 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v6 == 4 )
    {
      if ( dword_99FEC0 == 0 )
        goto LABEL_14;
      v7 = sub_48F690(v3);
    }
    else if ( v6 == 6 )
    {
      if ( dword_99FF08 == 0 )
        goto LABEL_14;
      v7 = sub_578E80(v3);
    }
    else
    {
      v7 = *(uint32_t *)((char *)v5 + v4 + dword_8F850C);
    }
    if ( v7 != 0 )
    {
      *(v5 - 8) = *(uint32_t *)(v7 + 12);
      v8 = (Concurrency::details::ContextBase *)sub_656710();
      Concurrency::details::ContextBase::SweepUnstructured(
        v8,
        (bool (/*cdecl*/ *)(struct Concurrency::details::_UnrealizedChore *, void *))v3,
        v10,
        v11);
      if ( v9 != 0 )
        *v5 = *(uint32_t *)(v7 + 172) + 10;
      else
        *v5 = *(uint32_t *)(v7 + 172);
    }
LABEL_14:
    ++v3;
    ++v5;
    if ( v3 >= 4 )
      break;
  }
}



// ------------------------------------------------------------
// 0x445A30 sub_445A30
// ------------------------------------------------------------
int /*thiscall*/ sub_445A30(uint32_t *this, int a2)
{
  char *v2; // esi

  v2 = (char *)(this - 2);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*(this - 2) + 8))(this - 2, 39, 2);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)v2 + 40))(v2, a2);
  return (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)v2 + 60))(v2, 1, -1);
}



// ------------------------------------------------------------
// 0x445A60 sub_445A60
// ------------------------------------------------------------
int /*thiscall*/ sub_445A60(uint32_t *this, int a2)
{
  char *v2; // esi

  v2 = (char *)(this - 2);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*(this - 2) + 8))(this - 2, 40, 0);
  return (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)v2 + 60))(v2, 1, a2);
}



// ------------------------------------------------------------
// 0x445A90 sub_445A90
// ------------------------------------------------------------
int /*thiscall*/ sub_445A90(uint32_t *this, int a2)
{
  char *v2; // esi

  v2 = (char *)(this - 2);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*(this - 2) + 8))(this - 2, 41, 2);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)v2 + 40))(v2, a2);
  return (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)v2 + 60))(v2, 1, -1);
}



// ------------------------------------------------------------
// 0x445AC0 sub_445AC0
// ------------------------------------------------------------
int /*thiscall*/ sub_445AC0(uint32_t *this, int a2)
{
  char *v2; // esi

  v2 = (char *)(this - 2);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*(this - 2) + 8))(this - 2, 42, 0);
  return (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)v2 + 60))(v2, 1, a2);
}



// ------------------------------------------------------------
// 0x445AF0 sub_445AF0
// ------------------------------------------------------------
int /*thiscall*/ sub_445AF0(uint32_t *this, int a2, char a3)
{
  char *v3; // esi

  v3 = (char *)(this - 2);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*(this - 2) + 8))(this - 2, 43, 2);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)v3 + 32))(v3, a2);
  (*(void (/*thiscall*/ **)(char *, char *, int))(*(uint32_t *)v3 + 52))(v3, &a3, 4);
  return (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)v3 + 60))(v3, 1, -1);
}



// ------------------------------------------------------------
// 0x445B30 sub_445B30
// ------------------------------------------------------------
int /*thiscall*/ sub_445B30(uint32_t *this, int a2, int a3, int a4)
{
  char *v4; // esi

  v4 = (char *)(this - 2);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*(this - 2) + 8))(this - 2, 44, 0);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)v4 + 40))(v4, a3);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)v4 + 32))(v4, a4);
  return (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)v4 + 60))(v4, 1, a2);
}



// ------------------------------------------------------------
// 0x445B70 sub_445B70
// ------------------------------------------------------------
uint8_t */*cdecl*/ sub_445B70(uint8_t *a1, uint8_t *a2, uint8_t *a3)
{
  uint8_t *result; // eax

  for ( result = a1; result != a2; ++result )
    *result = *a3;
  return result;
}



// ------------------------------------------------------------
// 0x445B90 sub_445B90
// ------------------------------------------------------------
char */*thiscall*/ sub_445B90(char *this)
{
  *(uint32_t *)this = &vftbl_CNRDParticle;
  sub_423A20(this + 4);
  *(this + 108) = 0;
  *((uint32_t *)this + 26) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 28) = 0;
  *(this + 116) = 1;
  *(this + 118) = 0;
  *(this + 117) = 0;
  *((uint32_t *)this + 32) = 0;
  *((uint32_t *)this + 31) = 0;
  *((uint32_t *)this + 30) = 0;
  sub_529CE0(this);
  sub_529D10(this);
  return this;
}



// ------------------------------------------------------------
// 0x445C10 CNRDParticleCreater__vmt18
// ------------------------------------------------------------
void /*thiscall*/ CNRDParticleCreater__vmt18(int this, const void *a2)
{
  qmemcpy((void *)(this + 4), a2, 0x62u);
}



// ------------------------------------------------------------
// 0x445C60 CNRDParticle__vmt24
// ------------------------------------------------------------
int /*thiscall*/ CNRDParticle__vmt24(uint32_t *this, int a2, int a3)
{
  *(this + a2 + 34) = a3;
  return a3;
}



// ------------------------------------------------------------
// 0x445C80 CNRDParticle__vmt28
// ------------------------------------------------------------
int /*thiscall*/ CNRDParticle__vmt28(uint32_t *this, int a2)
{
  return *(this + a2 + 34);
}



// ------------------------------------------------------------
// 0x445CA0 CNRDParticle__vmt2C
// ------------------------------------------------------------
int /*thiscall*/ CNRDParticle__vmt2C(uint32_t *this)
{
  return *(this + 33);
}



// ------------------------------------------------------------
// 0x445CB0 CNRDParticle__vmt30
// ------------------------------------------------------------
char /*thiscall*/ CNRDParticle__vmt30(uint8_t *this, char a2)
{
  *(this + 152) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x445CC0 ?WasExplicitlyAttached@ExternalContextBase@details@Concurrency@@QBE_NXZ
// ------------------------------------------------------------
bool /*thiscall*/ Concurrency::details::ExternalContextBase::WasExplicitlyAttached(
        Concurrency::details::ExternalContextBase *this)
{
  return *((uint8_t *)this + 152);
}



// ------------------------------------------------------------
// 0x445CF0 CNRDParticle__vmt44
// ------------------------------------------------------------
void /*thiscall*/ CNRDParticle__vmt44(void *this, unsigned int a2)
{
  sub_699070((int)this + 104, a2);
}



// ------------------------------------------------------------
// 0x445D00 sub_445D00
// ------------------------------------------------------------
int /*cdecl*/ sub_445D00(int a1)
{
  if ( dword_9B7FC0 == 0 )
  {
    if ( (dword_97B6F4 & 1) == 0 )
    {
      dword_97B6F4 |= 1u;
      sub_657800(a1, 256);
      atexit(sub_6BF5B0);
    }
    dword_9B7FC0 = (int)&unk_97B6D4;
  }
  return sub_6578B0(a1);
}



// ------------------------------------------------------------
// 0x445D90 CNRDParticle__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDParticle__vmt0(void *this, char a2)
{
  sub_445DC0();
  if ( (a2 & 1) != 0 )
    sub_657740(this, 156);
  return this;
}



// ------------------------------------------------------------
// 0x445DC0 sub_445DC0
// ------------------------------------------------------------
void /*thiscall*/ sub_445DC0(uint32_t *this)
{
  *this = &vftbl_CNRDParticle;
  nullsub_3();
  *(this + 26) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 108) = 0;
}



// ------------------------------------------------------------
// 0x445E10 sub_445E10
// ------------------------------------------------------------
char /*thiscall*/ sub_445E10(uint8_t *this)
{
  int v1; // eax
  uint32_t *v2; // ebx
  int v3; // esi
  uint32_t *v4; // edi
  int v5; // esi
  uint32_t *v6; // edi

  LOBYTE(v1) = *(this + 1048645);
  if ( (uint8_t)v1 == 0 )
  {
    v2 = this + 1048648;
    v3 = 0;
    v4 = this + 1048648;
    do
    {
      v1 = sub_656710();
      if ( *(uint32_t *)(v1 + 4 * v3) != -1 && *v4 == 1 )
        break;
      v1 = sub_656710();
      if ( *(uint32_t *)(v1 + 4 * v3) != -1 && *v4 == 2 )
        break;
      v1 = sub_656710();
      if ( *(uint32_t *)(v1 + 4 * v3) != -1 && *v4 == 5 )
        break;
      v1 = sub_656710();
      if ( *(uint32_t *)(v1 + 4 * v3) != -1 && *v4 == 7 )
        break;
      ++v3;
      ++v4;
    }
    while ( v3 < 8 );
    if ( v3 == 8 )
    {
      *(this + 1048645) = 1;
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
        sub_52AF20(*((uint32_t *)dword_8F8528 + 8));
      v5 = 0;
      v6 = v2;
      do
      {
        v1 = sub_656710();
        if ( *(uint32_t *)(v1 + 4 * v5) != -1 )
        {
          v1 = sub_656710();
          if ( *(uint32_t *)(v1 + 4 * v5) == -1 || *v6 == 0 )
          {
            sub_4456C0(this, v5, 2, 0);
            LOBYTE(v1) = sub_52D970(v5, 1);
          }
        }
        ++v5;
        ++v6;
      }
      while ( v5 < 8 );
    }
  }
  return v1;
}



// ------------------------------------------------------------
// 0x445EF0 sub_445EF0
// ------------------------------------------------------------
char /*thiscall*/ sub_445EF0(uint8_t *this)
{
  int v1; // eax
  int v2; // ebx
  int *v3; // esi
  uint8_t *v4; // edi
  int v5; // eax
  int v7; // [esp+0h] [ebp-Ch]
  int v8; // [esp+4h] [ebp-8h]
  uint8_t v9[4]; // [esp+8h] [ebp-4h] BYREF

  LOBYTE(v1) = *(this + 1048944);
  if ( (uint8_t)v1 != 0 )
  {
    v2 = 0;
    v3 = (int *)(this + 1049172);
    v4 = this + 1048961;
    v8 = -1049172 - (uint32_t)this;
    do
    {
      v1 = sub_656710();
      if ( *(int *)((char *)v3 + v8 + v1) != -1 )
      {
        v5 = sub_656710();
        v1 = sub_656840(v5);
        if ( v2 != v1 )
        {
          v7 = *(uint32_t *)(v4 + 11);
          v1 = sub_699000((int)(v4 - 13));
          if ( v1 >= v7 && *v3 < 3 )
          {
            sub_656710();
            v1 = sub_656850(v2);
            if ( v1 >= 4000 )
            {
              ++*v3;
              *v4 = 0;
              v4[1] = 0;
              sub_698F90((int)(v4 - 13), 1500, 0);
              off_77F3FC("BAD PING COUNTER INCREASE %d %d", v2, *v3);
              v1 = *v3;
              if ( *v3 == 3 )
              {
                sub_423200(dword_8F7B08, 52);
                v9[0] = v2;
                sub_423290(dword_8F7B08, (int)v9, 1);
                sub_423380(dword_8F7B08);
                LOBYTE(v1) = off_77F3FC("BAD PING REPORT %d", v2);
              }
            }
          }
        }
      }
      ++v2;
      ++v3;
      v4 += 28;
    }
    while ( v2 < 8 );
  }
  return v1;
}



// ------------------------------------------------------------
// 0x446000 sub_446000
// ------------------------------------------------------------
char /*thiscall*/ sub_446000(uint32_t *this, const char *a2, int a3)
{
  int v4; // esi
  int v5; // eax

  v4 = *(this + 262497);
  if ( *(uint8_t *)(v4 + 2224) == 0 )
    return 0;
  strcpy((char *)(v4 + 2232), a2);
  *(uint32_t *)(v4 + 2488) = a3;
  if ( (uint8_t)sub_657120(*(this + 262497)) != 1 || (uint8_t)sub_6572C0(*(this + 262497)) == 0 )
    return 0;
  sub_656710();
  v5 = sub_656800();
  sub_657670(*(this + 262497), v5);
  return 1;
}



// ------------------------------------------------------------
// 0x446080 sub_446080
// ------------------------------------------------------------
int /*cdecl*/ sub_446080(void *Src, int a2, void *a3)
{
  return (int)memcpy_0(a3, Src, a2 - (uint32_t)Src) + a2 - (uint32_t)Src;
}



// ------------------------------------------------------------
// 0x4460A0 sub_4460A0
// ------------------------------------------------------------
int /*stdcall*/ sub_4460A0(void *Src, int a2, void *a3)
{
  return (int)memcpy_0(a3, Src, a2 - (uint32_t)Src) + a2 - (uint32_t)Src;
}



// ------------------------------------------------------------
// 0x4460D0 sub_4460D0
// ------------------------------------------------------------
uint8_t */*cdecl*/ sub_4460D0(uint8_t *a1, uint8_t *a2, uint8_t *a3)
{
  uint8_t *v3; // ecx
  uint8_t *result; // eax

  v3 = a1;
  for ( result = a3; v3 != a2; ++v3 )
  {
    if ( result != nullptr )
      *result = *v3;
    ++result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x446100 sub_446100
// ------------------------------------------------------------
uint8_t */*stdcall*/ sub_446100(uint8_t *a1, int a2, uint8_t *a3)
{
  uint8_t *v3; // eax
  int i; // ecx

  v3 = a1;
  if ( a2 != 0 )
  {
    for ( i = a2; i != 0; --i )
      *v3++ = *a3;
  }
  return &a1[a2];
}



// ------------------------------------------------------------
// 0x446130 sub_446130
// ------------------------------------------------------------
// 分发器 case 8/0x15/0x16 配套：PVP（模块类型 4）被动物体特殊绑定
int /*thiscall*/ sub_446130(uint32_t *this, int a2, int a3)
{
  int v5; // [esp+4h] [ebp-4h] BYREF

  sub_4BE520(&v5, &a3);
  if ( v5 == *(this + 18) )
    return sub_452880(a2, -1);
  else
    return sub_452880(a2, *(uint32_t *)(v5 + 16));
}



// ------------------------------------------------------------
// 0x446190 sub_446190
// ------------------------------------------------------------
// 分发器 case 8/0x15/0x16 配套：WARROOM（模块类型 6）被动物体特殊绑定
void /*thiscall*/ sub_446190(uint32_t *this, int a2, int a3)
{
  int v4; // [esp+4h] [ebp-4h] BYREF

  sub_4BE520(&v4, &a3);
  if ( v4 == *(this + 17) )
    sub_42D780(this, *(float *)&this, a2, -1);
  else
    sub_42D780(this, *(float *)&this, a2, *(uint32_t *)(v4 + 16));
}



// ------------------------------------------------------------
// 0x4461F0 sub_4461F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4461F0(int this)
{
  int v2; // eax
  int v3; // edx
  int result; // eax
  char v5; // bl
  int i; // edi
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  unsigned int v11; // edi
  int v12; // ebx
  int v13; // ecx
  int v14; // ecx
  int v15; // eax
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // ecx
  int v24; // ebx
  int *v25; // edi
  uint32_t *v26; // eax
  int v27; // eax
  int v28; // ebx
  unsigned int j; // edx
  unsigned int v30; // ecx
  int v31; // edi
  int v32; // edi
  uint32_t *v33; // esi
  int v34; // ebx
  int v35; // esi
  void **v36; // esi
  int k; // ebx
  uint8_t *v38; // ecx
  uint32_t v39[8]; // [esp+4h] [ebp-34h]
  int *v40; // [esp+24h] [ebp-14h]
  int v41; // [esp+28h] [ebp-10h] BYREF
  int v42; // [esp+2Ch] [ebp-Ch] BYREF
  char ArgList[4]; // [esp+30h] [ebp-8h]
  char v44[4]; // [esp+34h] [ebp-4h] BYREF

  v2 = sub_429830((uint16_t)word_77F804);
  v3 = *(uint32_t *)(dword_8F7A24 + 20);
  v41 = v2;
  result = *(uint32_t *)(v3 + 104);
  if ( result != 0 && *(uint32_t *)(result + 32) != 1 )
  {
    result = this + 1050108;
    *(uint8_t *)(this + 1050008) = 0;
    v5 = 0;
    v40 = (int *)(this + 1050108);
    for ( i = 2; i != 0; --i )
    {
      if ( *(uint32_t *)result != 0 && (*(uint32_t *)(result + 4) - *(uint32_t *)result) >> 2 != 0 )
        v5 = 1;
      v7 = *(uint32_t *)(result + 16);
      if ( v7 != 0 && (*(uint32_t *)(result + 20) - v7) >> 2 != 0 )
        v5 = 1;
      v8 = *(uint32_t *)(result + 32);
      if ( v8 != 0 && (*(uint32_t *)(result + 36) - v8) >> 2 != 0 )
        v5 = 1;
      v9 = *(uint32_t *)(result + 48);
      if ( v9 != 0 && (*(uint32_t *)(result + 52) - v9) >> 2 != 0 )
        v5 = 1;
      result += 64;
    }
    if ( v5 != 0 || (v10 = *(uint32_t *)(this + 1050092)) != 0 && (result = (*(uint32_t *)(this + 1050096) - v10) >> 2) != 0 )
    {
      v11 = 0;
      v12 = 0;
      *(uint32_t *)ArgList = 0;
      while ( 1 )
      {
        v13 = *(uint32_t *)(this + 1050092);
        if ( v13 == 0 || v11 >= (*(uint32_t *)(this + 1050096) - v13) >> 2 )
          break;
        sub_423200(dword_8F7B08, 105);
        v14 = *(uint32_t *)(this + 1050092);
        if ( v14 != 0 )
          v15 = (*(uint32_t *)(this + 1050096) - v14) >> 2;
        else
          v15 = 0;
        if ( v15 - v11 <= 0x1E )
        {
          v17 = *(uint32_t *)(this + 1050092);
          if ( v17 != 0 )
            v18 = (*(uint32_t *)(this + 1050096) - v17) >> 2;
          else
            v18 = 0;
          v16 = v18 - v11;
        }
        else
        {
          v16 = 30;
        }
        off_77F3FC("p2p try count:%d", v16);
        v44[0] = *(uint8_t *)(v41 + 172);
        sub_423290(v44, 1);
        v19 = *(uint32_t *)(this + 1050092);
        if ( v19 != 0 )
          v20 = (*(uint32_t *)(this + 1050096) - v19) >> 2;
        else
          v20 = 0;
        if ( v20 - v11 <= 0x1E )
        {
          v21 = *(uint32_t *)(this + 1050092);
          if ( v21 != 0 )
            v22 = (*(uint32_t *)(this + 1050096) - v21) >> 2;
          else
            v22 = 0;
          v42 = v22 - v11;
        }
        else
        {
          v42 = 30;
        }
        sub_423290(&v42, 2);
        while ( 1 )
        {
          v23 = *(uint32_t *)(this + 1050092);
          if ( v23 == 0 || v11 >= (*(uint32_t *)(this + 1050096) - v23) >> 2 || v12 >= 30 )
            break;
          off_77F3FC("p2p result%d :%d", v12, *(uint32_t *)(v23 + 4 * v11));
          v44[0] = *(uint8_t *)(*(uint32_t *)(this + 1050092) + 4 * v11);
          sub_423290(v44, 1);
          ++v12;
          ++v11;
        }
        off_77F3FC("!!!!!!!______");
        v42 = 0;
        sub_423290(&v42, 2);
        off_77F3FC("!!!!!!!______2");
        sub_423380(dword_8F7B08);
        v24 = *(uint32_t *)ArgList;
        off_77F3FC("Send SNATLog#%d", *(uint32_t *)ArgList);
        *(uint32_t *)ArgList = v24 + 1;
        v12 = 0;
      }
      if ( *(uint32_t *)(this + 1050092) != 0 )
        j__free(*(void **)(this + 1050092));
      v25 = v40;
      *(uint32_t *)(this + 1050092) = 0;
      *(uint32_t *)(this + 1050096) = 0;
      *(uint32_t *)(this + 1050100) = 0;
      v42 = 0;
      *(uint32_t *)ArgList = 0;
      do
      {
        v26 = sub_656710();
        if ( v12 == sub_656840(v26) )
        {
          v39[v12] = -1;
        }
        else
        {
          v27 = *v25;
          v28 = 0;
          for ( j = 0; v27 != 0 && j < (v25[1] - v27) >> 2; ++j )
            v28 += *(uint32_t *)(*v25 + 4 * j);
          if ( v28 <= 0 )
          {
            v39[*(uint32_t *)ArgList] = -1;
          }
          else
          {
            if ( v27 != 0 )
              v30 = (v25[1] - v27) >> 2;
            else
              v30 = 0;
            v39[*(uint32_t *)ArgList] = v28 / v30;
            ++v42;
          }
          v12 = *(uint32_t *)ArgList;
        }
        ++v12;
        v25 += 4;
        *(uint32_t *)ArgList = v12;
      }
      while ( v12 < 8 );
      if ( v42 > 0 )
      {
        v31 = v42 + 1;
        sub_423200(dword_8F7B08, 105);
        v44[0] = *(uint8_t *)(v41 + 172);
        sub_423290(v44, 1);
        v42 = 0;
        sub_423290(&v42, 2);
        off_77F3FC("play ave ping count:%d", v31);
        v42 = v31;
        sub_423290(&v42, 2);
        v32 = 0;
        v33 = (uint32_t *)(this + 1050024);
        do
        {
          v34 = v39[v32];
          if ( v34 != -1 )
          {
            off_77F3FC("userindex :%d(ntype:%d,mtu:%d) - ping:%d", v32, v33[8], *v33, v39[v32]);
            v44[0] = *((uint8_t *)v33 + 32);
            sub_423290(v44, 1);
            v42 = *v33;
            sub_423290(&v42, 4);
            v42 = v34;
            sub_423290(&v42, 4);
          }
          ++v32;
          ++v33;
        }
        while ( v32 < 8 );
        v35 = v41;
        v44[0] = *(uint8_t *)(v41 + 172);
        sub_423290(v44, 1);
        v41 = *(uint32_t *)(v35 + 12);
        sub_423290(&v41, 4);
        v41 = 0;
        sub_423290(&v41, 4);
        sub_423380(dword_8F7B08);
        v36 = (void **)v40;
        for ( k = 8; k != 0; --k )
        {
          v38 = *v36;
          if ( *v36 != nullptr && ((uint8_t *)v36[1] - v38) >> 2 != 0 )
          {
            if ( v38 != nullptr )
              j__free(*v36);
            *v36 = nullptr;
            v36[1] = nullptr;
            v36[2] = nullptr;
          }
          v36 += 4;
        }
      }
      return off_77F3FC("Send All SNATLog");
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4466A0 sub_4466A0
// ------------------------------------------------------------
void /*noreturn*/ sub_4466A0()
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
// 0x446710 sub_446710
// ------------------------------------------------------------
// 【推断】队伍成员信息广播：@@ADD PEER 2 %d / @@ADD PEER 1 %d [%s] %d（名字+5063）
// —— 与 0x446F00(vmt64) 同族，操作 this+0x100000 级 peer 表
uint8_t */*thiscall*/ sub_446710(int this, char *Src, unsigned int a3, uint8_t *a4)
{
  uint8_t *result; // eax
  unsigned int v6; // ecx
  int v8; // edx
  int v9; // edx
  size_t v10; // ecx
  int v11; // edx
  int v12; // ecx
  void *v13; // eax
  char *v14; // ebx
  uint8_t *v15; // eax
  uint8_t *v16; // eax
  int v17; // eax
  int v18; // ecx
  int v19; // edi
  int v20; // ebx
  unsigned int v21; // edx
  size_t Size; // [esp+8h] [ebp-4h]
  int v23; // [esp+18h] [ebp+Ch]

  result = *(uint8_t **)(this + 4);
  HIBYTE(a4) = *a4;
  if ( result != nullptr )
    v6 = *(uint32_t *)(this + 12) - (uint32_t)result;
  else
    v6 = 0;
  if ( a3 != 0 )
  {
    if ( result != nullptr )
      v8 = *(uint32_t *)(this + 8) - (uint32_t)result;
    else
      v8 = 0;
    if ( -1 - v8 < a3 )
      sub_4466A0(this);
    if ( result != nullptr )
      v9 = *(uint32_t *)(this + 8) - (uint32_t)result;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v20 = *(uint32_t *)(this + 8);
      if ( v20 - (int)Src >= a3 )
      {
        *(uint32_t *)(this + 8) = sub_4460A0((void *)(v20 - a3), v20, *(void **)(this + 8));
        memcpy_0(&Src[a3], Src, v20 - (uint32_t)Src - a3);
        return sub_445B70(Src, &Src[a3], (uint8_t *)&a4 + 3);
      }
      else
      {
        sub_4460A0(Src, v20, &Src[a3]);
        sub_446100(*(uint8_t **)(this + 8), (int)&Src[a3 - *(uint32_t *)(this + 8)], (uint8_t *)&a4 + 3);
        v21 = a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v21;
        return sub_445B70(Src, (uint8_t *)(v21 - a3), (uint8_t *)&a4 + 3);
      }
    }
    else
    {
      if ( -1 - (v6 >> 1) >= v6 )
      {
        v10 = (v6 >> 1) + v6;
        Size = v10;
      }
      else
      {
        Size = 0;
        v10 = 0;
      }
      if ( result != nullptr )
        v11 = *(uint32_t *)(this + 8) - (uint32_t)result;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( result != nullptr )
          v12 = *(uint32_t *)(this + 8) - (uint32_t)result;
        else
          v12 = 0;
        v10 = a3 + v12;
        Size = v10;
      }
      v13 = operator new(v10);
      v14 = &Src[-*(uint32_t *)(this + 4)];
      v23 = (int)v13;
      v15 = memcpy_0(v13, *(const void **)(this + 4), (size_t)v14);
      v16 = sub_446100(&v15[(uint32_t)v14], a3, (uint8_t *)&a4 + 3);
      memcpy_0(v16, Src, *(uint32_t *)(this + 8) - (uint32_t)Src);
      v17 = *(uint32_t *)(this + 4);
      if ( v17 != 0 )
        v18 = *(uint32_t *)(this + 8) - v17;
      else
        v18 = 0;
      v19 = v18 + a3;
      if ( v17 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = v23 + Size;
      *(uint32_t *)(this + 8) = v23 + v19;
      *(uint32_t *)(this + 4) = v23;
      return (uint8_t *)v23;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4468D0 sub_4468D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4468D0(uint32_t *this, unsigned int a2)
{
  int v2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  v2 = *(this + 2);
  if ( 214748364 - v2 < a2 )
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
// 0x446960 sub_446960
// ------------------------------------------------------------
// 分发器 case 2 配套：对象可见表重置【推断】
void /*thiscall*/ sub_446960(int this)
{
  if ( *(uint32_t *)(this + 276) != 0 )
    j__free(*(void **)(this + 276));
  *(uint32_t *)(this + 276) = 0;
  *(uint32_t *)(this + 280) = 0;
  *(uint32_t *)(this + 284) = 0;
  *(uint32_t *)(this + 288) = -1;
}



// ------------------------------------------------------------
// 0x4469A0 sub_4469A0
// ------------------------------------------------------------
// 分发器 case 5 配套：按计数建表（逐项 0x446BE0 读取）【推断】
unsigned int /*thiscall*/ sub_4469A0(int this, size_t Size)
{
  int v3; // ecx
  int v4; // ebx
  unsigned int result; // eax
  char *v6; // edi
  int v7; // eax
  uint8_t *v8; // [esp-18h] [ebp-38h]
  uint8_t *v9; // [esp-14h] [ebp-34h]
  int v10; // [esp+0h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-14h]
  int *v12; // [esp+10h] [ebp-10h]
  int v13; // [esp+1Ch] [ebp-4h]

  v12 = &v10;
  v3 = *(uint32_t *)(this + 4);
  v4 = 0;
  if ( v3 != 0 )
    result = *(uint32_t *)(this + 12) - v3;
  else
    result = 0;
  if ( result < Size )
  {
    v6 = (char *)operator new(Size);
    v9 = *(uint8_t **)(this + 8);
    v8 = *(uint8_t **)(this + 4);
    Block = v6;
    v13 = 0;
    sub_4460D0(v8, v9, v6);
    v7 = *(uint32_t *)(this + 4);
    if ( v7 != 0 )
    {
      v4 = *(uint32_t *)(this + 8) - v7;
      j__free(*(void **)(this + 4));
    }
    *(uint32_t *)(this + 12) = &v6[Size];
    *(uint32_t *)(this + 8) = &v6[v4];
    *(uint32_t *)(this + 4) = v6;
    return Size;
  }
  return result;
}



// ------------------------------------------------------------
// 0x446A60 sub_446A60
// ------------------------------------------------------------
char /*thiscall*/ sub_446A60(uint32_t *this, size_t Size)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( Size == 0 )
    return 0;
  v4 = (char *)operator new(Size);
  *(this + 1) = v4;
  *(this + 2) = v4;
  *(this + 3) = &v4[Size];
  return 1;
}



// ------------------------------------------------------------
// 0x446AB0 sub_446AB0
// ------------------------------------------------------------
// 分发器 case 5 配套：填充 3 float 向量结构（sub_4E7DA0 取数）【推断】
int /*thiscall*/ sub_446AB0(int this, int a2)
{
  int v3; // eax
  unsigned int v4; // ebx
  void *v6; // eax
  unsigned int v7; // edx
  int v8; // eax
  unsigned int v9; // ecx
  int v10; // edx
  void *v11; // ebx
  int v12; // ecx
  size_t v13; // eax

  if ( this == a2 )
    return this;
  v3 = *(uint32_t *)(a2 + 4);
  if ( v3 == 0 || (v4 = *(uint32_t *)(a2 + 8) - v3) == 0 )
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
    v7 = *(uint32_t *)(this + 8) - (uint32_t)v6;
  else
    v7 = 0;
  if ( v4 <= v7 )
  {
    memcpy_0(v6, *(const void **)(a2 + 4), *(uint32_t *)(a2 + 8) - *(uint32_t *)(a2 + 4));
    v8 = *(uint32_t *)(a2 + 4);
    if ( v8 != 0 )
      *(uint32_t *)(this + 8) = *(uint32_t *)(a2 + 8) - v8 + *(uint32_t *)(this + 4);
    else
      *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
    return this;
  }
  if ( v6 != nullptr )
    v9 = *(uint32_t *)(this + 12) - (uint32_t)v6;
  else
    v9 = 0;
  if ( v4 > v9 )
  {
    if ( v6 != nullptr )
      j__free(*(void **)(this + 4));
    v12 = *(uint32_t *)(a2 + 4);
    if ( v12 != 0 )
      v13 = *(uint32_t *)(a2 + 8) - v12;
    else
      v13 = 0;
    if ( sub_446A60((uint32_t *)this, v13) != 0 )
      *(uint32_t *)(this + 8) = sub_4460A0(*(void **)(a2 + 4), *(uint32_t *)(a2 + 8), *(void **)(this + 4));
    return this;
  }
  if ( v6 != nullptr )
    v10 = *(uint32_t *)(this + 8) - (uint32_t)v6;
  else
    v10 = 0;
  v11 = (void *)(*(uint32_t *)(a2 + 4) + v10);
  sub_446080(*(void **)(a2 + 4), (int)v11, *(void **)(this + 4));
  *(uint32_t *)(this + 8) = sub_4460A0(v11, *(uint32_t *)(a2 + 8), *(void **)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x446BE0 sub_446BE0
// ------------------------------------------------------------
// 分发器 case 5 配套：逐项读入状态字节【推断】
uint8_t */*thiscall*/ sub_446BE0(int this, uint8_t *a2)
{
  int v2; // esi
  unsigned int v3; // edx
  uint8_t *v4; // eax
  uint8_t *result; // eax

  v2 = *(uint32_t *)(this + 4);
  if ( v2 != 0 )
    v3 = *(uint32_t *)(this + 8) - v2;
  else
    v3 = 0;
  if ( v2 == 0 || v3 >= *(uint32_t *)(this + 12) - v2 )
    return sub_446710(this, *(char **)(this + 8), 1u, a2);
  v4 = *(uint8_t **)(this + 8);
  *v4 = *a2;
  result = v4 + 1;
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x446C30 CNRDUdpModule__vmt88
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDUdpModule__vmt88(uint32_t *this, char a2, int a3)
{
  size_t v4; // eax
  void *v5; // eax
  int v6; // edx
  int v7; // esi
  int v8; // eax
  int v9; // edi
  unsigned int v10; // eax
  int v11; // eax
  uint32_t *v12; // ecx
  int v13; // ebx
  uint32_t *result; // eax
  int v15; // [esp-8h] [ebp-28h]
  uint32_t v16[2]; // [esp+Ch] [ebp-14h] BYREF
  char v17; // [esp+14h] [ebp-Ch]
  int v18; // [esp+18h] [ebp-8h]
  int v19; // [esp+1Ch] [ebp-4h]

  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 16))(this);
  v5 = operator new(v4);
  v6 = *this;
  v16[0] = v5;
  qmemcpy(v5, this + 3, (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 16))(this));
  v16[1] = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 16))(this);
  v18 = a3;
  v17 = a2;
  v7 = sub_699000((int)(this + 262151));
  v8 = rand();
  v9 = *(this + 262159);
  v10 = (int)((uint64_t)(1374389535LL * *(this + 262150) * (v8 % 100 + 50)) >> 32) >> 5;
  v15 = *(uint32_t *)(v9 + 4);
  v19 = v10 + v7 + (v10 >> 31);
  v11 = sub_499C20(v9, v15, v16);
  v12 = this + 262158;
  v13 = v11;
  sub_4468D0(v12, 1u);
  *(uint32_t *)(v9 + 4) = v13;
  result = *(uint32_t **)(v13 + 4);
  *result = v13;
  return result;
}



// ------------------------------------------------------------
// 0x446CF0 sub_446CF0
// ------------------------------------------------------------
// 分发器 case 0 配套：UDP RETURN/FINISH 分支处理（子码 1/2）【推断】
int /*thiscall*/ sub_446CF0(uint32_t *this, int a2, int a3, int a4)
{
  bool v6; // zf
  uint8_t *v7; // eax
  int v8; // eax
  int v9; // esi
  int result; // eax
  int v11; // [esp+14h] [ebp+8h]

  v11 = *(this + a2 + 262162);
  v6 = (uint8_t)a4 == 0;
  *(this + a2 + 262162) = a3;
  if ( v6 )
  {
    *((uint8_t *)this + 28 * a2 + 1048692) = 0;
  }
  else
  {
    v7 = this + 7 * a2;
    v7[1048692] = 1;
    v7[1048693] = 0;
    v7[1048694] = 0;
    sub_698F90((int)(v7 + 1048680), 0, 0);
  }
  *(this + a2 + 262226) = -150;
  switch ( a3 )
  {
    case 0:
    case 7:
      if ( *((uint8_t *)this + a2 + 1048936) == 0 )
        break;
      *((uint8_t *)this + a2 + 1048936) = 0;
      v8 = *(uint32_t *)(dword_8F7A24 + 12);
      if ( v8 == 4 )
      {
        if ( dword_99FEC0 == 0 )
          break;
        v9 = sub_48F690(a2);
      }
      else if ( v8 == 6 )
      {
        if ( dword_99FF08 == 0 )
          break;
        v9 = sub_578E80(a2);
      }
      else
      {
        v9 = *(uint32_t *)(dword_8F850C + 4 * a2 + 16);
      }
      if ( v9 != 0 && rand() % 100 < 10 )
      {
        sub_423200(dword_8F7B08, 100);
        HIBYTE(a4) = a3 == 0;
        sub_423290(dword_8F7B08, (int)&a4 + 3, 1);
        a4 = *(uint16_t *)(v9 + 4);
        sub_423290(dword_8F7B08, (int)&a4, 2);
        sub_423380(dword_8F7B08);
      }
      break;
    case 1:
    case 2:
    case 5:
      if ( *(uint32_t *)(sub_656710() + 4 * a2) != -1 )
        *((uint8_t *)this + a2 + 1048936) = 1;
      break;
    default:
      *((uint8_t *)this + a2 + 1048936) = 0;
      break;
  }
  result = a3;
  if ( a3 != 0 )
  {
    if ( a3 == 7 )
    {
      a4 = 3;
      return sub_431230((int)(this + 262522), &a4);
    }
  }
  else
  {
    result = v11 - 1;
    switch ( v11 )
    {
      case 1:
      case 3:
        a4 = 0;
        result = sub_431230((int)(this + 262522), &a4);
        break;
      case 2:
      case 4:
        a4 = 1;
        result = sub_431230((int)(this + 262522), &a4);
        break;
      case 5:
      case 6:
        a4 = 2;
        return sub_431230((int)(this + 262522), &a4);
      default:
        return result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x446F00 CNRDUdpModule__vmt64
// ------------------------------------------------------------
// CNRDUdpModule::vmt64 —— 队友入场同步（"@@ADD PEER 2 %d" 日志自证）：
// 加入者座位/名字经 sub_42A380 取名、声音通道表(sub_656710/656880)广播；
// a4/a5 控制 peer 表(+28*槽) 状态写入
char /*thiscall*/ CNRDUdpModule__vmt64(uint8_t *this, int ArgList, int a3, char a4, char a5)
{
  int v6; // eax
  int v7; // esi
  int v8; // esi
  char *v9; // eax
  uint8_t *v10; // ebx
  char *v12; // [esp-10h] [ebp-1Ch]
  char *v13; // [esp-10h] [ebp-1Ch]
  int16_t v14; // [esp-Ch] [ebp-18h]
  int v15; // [esp-8h] [ebp-14h]
  int v16; // [esp-8h] [ebp-14h]
  int v17; // [esp-4h] [ebp-10h]

  v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  v7 = v6;
  if ( a3 != 0 )
  {
    v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    if ( a3 != v6 )
    {
      if ( *(uint32_t *)(v7 + 160) == *(uint32_t *)(v7 + 164) || *(uint32_t *)(a3 + 160) == *(uint32_t *)(a3 + 164) )
      {
        v16 = *(uint32_t *)(a3 + 8);
        v14 = *(uint16_t *)(a3 + 168);
        v8 = ArgList;
        v13 = sub_42A380((unsigned int *)a3, 1);
        sub_656710();
        sub_656880(ArgList, v13, v14, v16, 0);
        off_77F3FC("@@ADD PEER 2 %d", ArgList);
        if ( a4 != 0 )
        {
          *((uint32_t *)this + ArgList + 262162) = 2;
          if ( a5 != 0 )
          {
            v10 = this + 28 * ArgList;
            goto LABEL_17;
          }
          v10 = this + 28 * ArgList;
LABEL_9:
          v10[1048692] = 0;
LABEL_10:
          *((uint32_t *)this + v8 + 262226) = -150;
          if ( *(uint32_t *)(sub_656710() + 4 * v8) != -1 )
            *(this + v8 + 1048936) = 1;
          sub_4457D0(this, 0);
          goto LABEL_21;
        }
        *((uint32_t *)this + ArgList + 262162) = 4;
        v10 = this + 28 * ArgList;
      }
      else
      {
        v15 = *(uint32_t *)(a3 + 8);
        v8 = ArgList;
        v12 = sub_42A380((unsigned int *)a3, 0);
        sub_656710();
        sub_656880(ArgList, v12, 5063, v15, 0);
        v9 = sub_42A380((unsigned int *)a3, 0);
        off_77F3FC("@@ADD PEER 1 %d [%s] %d", ArgList, v9, 5063);
        if ( a4 != 0 )
        {
          *((uint32_t *)this + ArgList + 262162) = 1;
          if ( a5 != 0 )
          {
            v10 = this + 28 * ArgList;
LABEL_17:
            v10[1048692] = 1;
            v10[1048693] = 0;
            v10[1048694] = 0;
            sub_698F90((int)(v10 + 1048680), 0, 0);
            goto LABEL_10;
          }
          v10 = this + 28 * ArgList;
          goto LABEL_9;
        }
        *((uint32_t *)this + ArgList + 262162) = 3;
        v10 = this + 28 * ArgList;
      }
      v10[1048692] = 1;
      v10[1048694] = 0;
      v10[1048693] = 0;
      sub_698F90((int)(v10 + 1048680), 0, 0);
      *((uint32_t *)this + v8 + 262226) = -150;
      *(this + v8 + 1048936) = 0;
LABEL_21:
      sub_656630(v8);
      v17 = *(uint32_t *)(a3 + 12);
      sub_656710();
      sub_656950(v8, v17);
      v10[1048961] = 0;
      v10[1048962] = 0;
      LOBYTE(v6) = sub_698F90((int)(v10 + 1048948), 0, 0);
      *((uint32_t *)this + v8 + 262293) = 0;
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x447140 CNRDUdpModule__vmt98
// ------------------------------------------------------------
// CNRDUdpModule::vmt98【推断】peer 表操作（与本分区 vmt 族同宿主）
char /*thiscall*/ CNRDUdpModule__vmt98(int this)
{
  char result; // al
  int i; // esi
  int v4; // eax

  result = *(uint8_t *)(this + 1048644);
  if ( result != 0 )
  {
    for ( i = 0; i < 8; ++i )
    {
      if ( *(uint32_t *)(sub_656710() + 4 * i) != -1 )
      {
        sub_656710();
        sub_6568C0(i);
        sub_656560(i);
      }
      *(uint8_t *)(this + i + 1048936) = 0;
      sub_446CF0((uint32_t *)this, i, 0, 1);
    }
    *(uint8_t *)(this + 1048645) = 1;
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
      sub_52AF20(*((uint32_t *)dword_8F8528 + 8));
    v4 = sub_656710();
    sub_656A10(v4);
    sub_657230(*(uint32_t *)(this + 1049988));
    result = sub_45DF90(dword_8F8524);
    *(uint8_t *)(this + 1048644) = 0;
  }
  return result;
}



// ============================================================
// 【分区 7】CNRDUdpModule__vmt74（0x449EB0-0x44A950）
// peer 表重建/清理：@@REMOVE PEER + @@ADD PEER 4（日志自证）。
// ============================================================
// ------------------------------------------------------------
// 0x449EB0 CNRDUdpModule__vmt74
// ------------------------------------------------------------
// CNRDUdpModule::vmt74 —— peer 表重建/清理（日志自证）：
// "@@REMOVE PEER" 逐席移除后按需 "@@ADD PEER 4 %d" 重建
char /*thiscall*/ sub_449EB0(char *this)
{
  int v2; // ebx
  int v3; // esi
  int *v4; // eax
  uint32_t *v5; // eax
  int v6; // esi
  int *v7; // eax
  uint32_t ***v8; // ecx
  uint32_t **v9; // eax
  int v10; // esi
  char v11; // cl
  char *v12; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  const char *v18; // eax
  int v19; // ecx
  int v20; // edx
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  const char *v28; // eax
  int v29; // eax
  int v30; // ebx
  char *v31; // eax
  uint32_t *v32; // eax
  char *v33; // edx
  const char *v34; // eax
  char *v35; // eax
  int v36; // ebx
  uint32_t *v37; // eax
  char *v38; // eax
  char *v39; // eax
  const char *v40; // eax
  int v41; // esi
  uint32_t *v42; // eax
  int v43; // esi
  int v44; // eax
  int v45; // ebx
  int v46; // ebx
  char *v47; // edi
  uint32_t *v48; // eax
  uint32_t *v49; // eax
  int v50; // edx
  bool v51; // zf
  unsigned int v52; // esi
  int *v53; // ecx
  uint8_t *v55; // [esp-10h] [ebp-134h]
  uint8_t *v56; // [esp-10h] [ebp-134h]
  void *v57; // [esp-10h] [ebp-134h]
  void *v58; // [esp-10h] [ebp-134h]
  int v59; // [esp-Ch] [ebp-130h]
  int v60; // [esp-Ch] [ebp-130h]
  int16_t v61; // [esp-Ch] [ebp-130h]
  int16_t v62; // [esp-Ch] [ebp-130h]
  int v63; // [esp-8h] [ebp-12Ch]
  int v64; // [esp-8h] [ebp-12Ch]
  int v65; // [esp-8h] [ebp-12Ch]
  int v66; // [esp-4h] [ebp-128h]
  int v67; // [esp-4h] [ebp-128h]
  int v68; // [esp-4h] [ebp-128h]
  int v69; // [esp-4h] [ebp-128h]
  int v70; // [esp-4h] [ebp-128h]
  int v71; // [esp-4h] [ebp-128h]
  int v72; // [esp-4h] [ebp-128h]
  int v73; // [esp+Ch] [ebp-118h]
  char v74[4]; // [esp+10h] [ebp-114h] BYREF
  int v75; // [esp+14h] [ebp-110h] BYREF
  char *v76; // [esp+18h] [ebp-10Ch]
  int v77; // [esp+1Ch] [ebp-108h]
  char Buffer[256]; // [esp+20h] [ebp-104h] BYREF
  int v79; // [esp+120h] [ebp-4h]

  v79 = dword_796E50;
  while ( *((uint32_t *)this + 262160) != 0 )
  {
    v2 = **((uint32_t **)this + 262159) + 8;
    if ( sub_699000((int)(this + 1048604)) < *(uint32_t *)(v2 + 16) )
      break;
    if ( **(uint8_t **)v2 != 0 )
    {
      v5 = (uint32_t *)sub_656710();
      sub_656840(v5);
      v6 = 0;
      v76 = this + 1048648;
      do
      {
        if ( *(uint32_t *)(sub_656710() + 4 * v6) != -1
          && (*(uint32_t *)(sub_656710() + 4 * v6) == -1 || *(uint32_t *)v76 == 0) )
        {
          v67 = *(uint8_t *)(v2 + 8);
          v60 = *(uint32_t *)(v2 + 4);
          v56 = *(uint8_t **)v2;
          v7 = (int *)sub_656710();
          sub_656EF0(v7, v56, v60, v6, v67);
        }
        ++v6;
        v76 += 4;
      }
      while ( v6 < 8 );
    }
    else
    {
      v3 = *(uint32_t *)(v2 + 12);
      if ( *(uint32_t *)(sub_656710() + 4 * v3) == -1 || *((uint32_t *)this + v3 + 262162) == 0 )
      {
        v66 = *(uint8_t *)(v2 + 8);
        v63 = *(uint32_t *)(v2 + 12);
        v59 = *(uint32_t *)(v2 + 4);
        v55 = *(uint8_t **)v2;
        v4 = (int *)sub_656710();
        sub_656EF0(v4, v55, v59, v63, v66);
      }
    }
    if ( *(uint32_t *)v2 != 0 )
      j__free(*(void **)v2);
    *(uint32_t *)v2 = 0;
    v8 = *((uint32_t ****)this + 262159);
    v9 = *v8;
    if ( *v8 != v8 )
    {
      *v9[1] = *v9;
      (*v9)[1] = v9[1];
      j__free(v9);
      --*((uint32_t *)this + 262160);
    }
  }
  v10 = 0;
  while ( 1 )
  {
    if ( *(uint32_t *)(sub_656710() + 4 * v10) == -1
      || *((uint32_t *)this + v10 + 262162) == 0
      || *(uint32_t *)(sub_656710() + 4 * v10) != -1 && *((uint32_t *)this + v10 + 262162) == 7 )
    {
      goto LABEL_123;
    }
    v11 = *(this + 28 * v10 + 1048692);
    v12 = this + 28 * v10;
    v76 = v12;
    if ( v11 == 0 )
      goto LABEL_123;
    v13 = (int)(v12 + 1048680);
    v75 = (int)(v12 + 1048680);
    sub_698F90((int)(v12 + 1048680), 0, 0);
    v14 = sub_699000(v13);
    v73 = v14;
    if ( v14 > *((uint32_t *)this + v10 + 262226) + 150 )
    {
      v77 = 3;
      if ( *(uint32_t *)(sub_656710() + 4 * v10) != -1 && *((uint32_t *)this + v10 + 262162) == 1
        || *(uint32_t *)(sub_656710() + 4 * v10) != -1 && *((uint32_t *)this + v10 + 262162) == 2
        || *(uint32_t *)(sub_656710() + 4 * v10) != -1 && *((uint32_t *)this + v10 + 262162) == 5 )
      {
        v77 = 0;
      }
      if ( *(uint32_t *)(sub_656710() + 4 * v10) != -1 && *((uint32_t *)this + v10 + 262162) == 1 )
        goto LABEL_50;
      if ( *(uint32_t *)(sub_656710() + 4 * v10) != -1 && *((uint32_t *)this + v10 + 262162) == 3 )
        goto LABEL_50;
      v15 = *((uint32_t *)dword_8F8524 + 18);
      if ( v15 != 3 && v15 != 4 )
        goto LABEL_50;
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
      {
        v16 = sub_48F690((uint32_t *)dword_99FEC0, v10);
        v17 = sub_48F5A0();
      }
      else
      {
        v16 = *(uint32_t *)(dword_8F850C + 4 * v10 + 16);
        v17 = sub_456420(dword_8F850C);
      }
      if ( *(uint32_t *)(v16 + 172) != 3 || v10 == v17 )
        goto LABEL_50;
      if ( *(this + 1049992) != 0 )
      {
LABEL_49:
        v68 = *(uint16_t *)(v16 + 168);
        v18 = (const char *)sub_42A380(1);
        off_77F3FC("!SYMMETRIC PORT CHANGE [%d] %s:%d", v10, v18, v68);
LABEL_50:
        if ( byte_97B6D0 != 0 )
        {
          if ( *(uint32_t *)(sub_656710() + 4 * v10) != -1 && *((uint32_t *)this + v10 + 262162) == 5 )
            sub_4456C0(v10, v77, 1);
        }
        else
        {
          sub_4456C0(v10, v77, 0);
        }
        *((uint32_t *)this + v10 + 262226) = v73;
        off_77F3FC("!UDP SEND CHECK PACKET TO [%d]", v10);
        v13 = v75;
        v14 = v73;
        goto LABEL_56;
      }
      *((uint16_t *)this + 524997) = *(uint16_t *)(v16 + 168);
      if ( v10 >= v17 )
      {
        if ( v10 <= v17 )
        {
LABEL_48:
          *(this + 1049992) = 1;
          goto LABEL_49;
        }
        LOWORD(v17) = v17 + 1;
      }
      *(uint16_t *)(v16 + 168) += v17;
      goto LABEL_48;
    }
LABEL_56:
    v19 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v19 == 4 || (v20 = 3000, v19 == 6) )
      v20 = 6000;
    if ( v14 <= v20 )
      goto LABEL_123;
    if ( v19 == 4 )
    {
      if ( dword_99FEC0 == 0 )
        goto LABEL_63;
      v21 = sub_48F690((uint32_t *)dword_99FEC0, v10);
    }
    else if ( v19 == 6 )
    {
      if ( dword_99FF08 == 0 )
      {
LABEL_63:
        v77 = 0;
        goto LABEL_69;
      }
      v21 = sub_578E80(v10);
    }
    else
    {
      v21 = *(uint32_t *)(dword_8F850C + 4 * v10 + 16);
    }
    v77 = v21;
LABEL_69:
    if ( *(uint32_t *)(sub_656710() + 4 * v10) != -1 && *((uint32_t *)this + v10 + 262162) == 1
      || *(uint32_t *)(sub_656710() + 4 * v10) != -1 && *((uint32_t *)this + v10 + 262162) == 3 )
    {
      v31 = (char *)sub_656710();
      sub_6568C0(v31, v10);
      off_77F3FC("@@REMOVE PEER");
      if ( v77 != 0 )
      {
        v64 = *(uint32_t *)(v77 + 8);
        v61 = *(uint16_t *)(v77 + 168);
        v57 = (void *)sub_42A380(1);
        v32 = (uint32_t *)sub_656710();
        sub_656880(v32, v10, v57, v61, v64, 0);
        off_77F3FC("@@ADD PEER 4 %d", v10);
      }
      if ( *(uint32_t *)(sub_656710() + 4 * v10) == -1 || *((uint32_t *)this + v10 + 262162) != 1 )
      {
        v33 = v76;
        *((uint32_t *)this + v10 + 262162) = 4;
        v33[1048692] = 1;
        *(uint8_t *)(v13 + 13) = 0;
        *(uint8_t *)(v13 + 14) = 0;
        sub_698F90(v13, 0, 0);
        *((uint32_t *)this + v10 + 262226) = -150;
        *(this + v10 + 1048936) = 0;
      }
      else
      {
        v76[1048692] = 1;
        *((uint32_t *)this + v10 + 262162) = 2;
        *(uint8_t *)(v13 + 13) = 0;
        *(uint8_t *)(v13 + 14) = 0;
        sub_698F90(v13, 0, 0);
        *((uint32_t *)this + v10 + 262226) = -150;
        if ( *(uint32_t *)(sub_656710() + 4 * v10) != -1 )
          *(this + v10 + 1048936) = 1;
      }
      if ( v77 != 0 )
      {
        v70 = *(uint16_t *)(v77 + 168);
        v34 = (const char *)sub_42A380(1);
        off_77F3FC("!UDP CHANGE TO PUBLIC IP [%d] %s %d", v10, v34, v70);
      }
      goto LABEL_123;
    }
    if ( *(uint32_t *)(sub_656710() + 4 * v10) != -1 && *((uint32_t *)this + v10 + 262162) == 2
      || *(uint32_t *)(sub_656710() + 4 * v10) != -1 && *((uint32_t *)this + v10 + 262162) == 4 )
    {
      break;
    }
    if ( *(uint32_t *)(sub_656710() + 4 * v10) == -1 || *((uint32_t *)this + v10 + 262162) != 5 )
      goto LABEL_123;
    v22 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v22 == 4 )
    {
      if ( dword_99FEC0 == 0 )
        goto LABEL_82;
      v23 = sub_48F690((uint32_t *)dword_99FEC0, v10);
    }
    else if ( v22 == 6 )
    {
      if ( dword_99FF08 == 0 )
      {
LABEL_82:
        v77 = 0;
        goto LABEL_88;
      }
      v23 = sub_578E80(v10);
    }
    else
    {
      v23 = *(uint32_t *)(dword_8F850C + 4 * v10 + 16);
    }
    v77 = v23;
LABEL_88:
    v24 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v24 == 4 )
    {
      v25 = sub_48F5A0();
      if ( v25 != -1 )
        sub_48F500(v25, 254);
    }
    else if ( v24 == 6 )
    {
      v26 = sub_48FCA0();
      if ( v26 != -1 )
        sub_48FC30(v26, 255);
    }
    else
    {
      sub_423200(dword_8F7B08, 13);
      sub_423380(dword_8F7B08);
    }
    if ( v77 == 0 || v77 == -16 )
    {
      strcpy(Buffer, (const char *)sub_422E70(507));
    }
    else
    {
      if ( *(uint32_t *)(v77 + 40) < 0x10u )
        v27 = v77 + 20;
      else
        v27 = *(uint32_t *)(v77 + 20);
      v69 = v27;
      v28 = (const char *)sub_422E70(506);
      sprintf(Buffer, v28, v69);
    }
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);
    off_77F3FC("!UDP CONNECT FAIL [%d]", v10);
    v76[1048692] = 1;
    *((uint32_t *)this + v10 + 262162) = 7;
    *(uint8_t *)(v13 + 13) = 0;
    *(uint8_t *)(v13 + 14) = 0;
    sub_698F90(v13, 0, 0);
    *((uint32_t *)this + v10 + 262226) = -150;
    if ( *(this + v10 + 1048936) == 0 )
      goto LABEL_113;
    *(this + v10 + 1048936) = 0;
    v29 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v29 == 4 )
    {
      if ( dword_99FEC0 != 0 )
      {
        v30 = sub_48F690((uint32_t *)dword_99FEC0, v10);
LABEL_110:
        if ( v30 != 0 && rand() % 100 < 10 )
        {
          sub_423200(dword_8F7B08, 100);
          v74[0] = 0;
          sub_423290(v74, 1);
          v75 = *(uint16_t *)(v30 + 4);
          sub_423290(&v75, 2);
          sub_423380(dword_8F7B08);
        }
      }
    }
    else
    {
      if ( v29 != 6 )
      {
        v30 = *(uint32_t *)(dword_8F850C + 4 * v10 + 16);
        goto LABEL_110;
      }
      if ( dword_99FF08 != 0 )
      {
        v30 = sub_578E80(v10);
        goto LABEL_110;
      }
    }
LABEL_113:
    v75 = 3;
    sub_431230((int)(this + 1050088), &v75);
LABEL_123:
    if ( ++v10 >= 8 )
      goto LABEL_134;
  }
  v35 = (char *)sub_656710();
  sub_6568C0(v35, v10);
  off_77F3FC("@@REMOVE PEER");
  v36 = v77;
  if ( v77 != 0 )
  {
    v65 = *(uint32_t *)(v77 + 8);
    v62 = sub_45DB10(dword_8F8524);
    v58 = (void *)sub_45DB00(dword_8F8524);
    v37 = (uint32_t *)sub_656710();
    sub_656880(v37, v10, v58, v62, v65, 1);
    off_77F3FC("@@ADD PEER 4 %d", v10);
  }
  if ( *(uint32_t *)(sub_656710() + 4 * v10) == -1 || *((uint32_t *)this + v10 + 262162) != 2 )
  {
    v39 = this + 28 * v10;
    *((uint32_t *)this + v10 + 262162) = 6;
    v39[1048692] = 1;
    v39[1048693] = 0;
    v39[1048694] = 0;
    sub_698F90((int)(v39 + 1048680), 0, 0);
    *((uint32_t *)this + v10 + 262226) = -150;
    *(this + v10 + 1048936) = 0;
  }
  else
  {
    v38 = this + 28 * v10;
    *((uint32_t *)this + v10 + 262162) = 5;
    v38[1048692] = 1;
    v38[1048693] = 0;
    v38[1048694] = 0;
    sub_698F90((int)(v38 + 1048680), 0, 0);
    *((uint32_t *)this + v10 + 262226) = -150;
    if ( *(uint32_t *)(sub_656710() + 4 * v10) != -1 )
      *(this + v10 + 1048936) = 1;
  }
  if ( v36 != 0 )
  {
    v71 = sub_45DB10(dword_8F8524);
    v40 = (const char *)sub_45DB00(dword_8F8524);
    off_77F3FC("!UDP CHANGE TO RELAY IP [%d] %s %d", v10, v40, v71);
  }
LABEL_134:
  sub_445E10(this);
  sub_445EF0(this);
  if ( *(this + 1048644) != 0 )
  {
    v41 = dword_79692C;
    if ( sub_699000((int)(this + 1049204)) >= v41 )
    {
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 8))(this, 1, 1);
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 60))(this, 1, -1);
    }
    v72 = *(uint32_t *)(sub_656710() + 40);
    v42 = (uint32_t *)sub_656710();
    *(uint32_t *)(*((uint32_t *)this + 262497) + 2516) = sub_656850(v42, v72);
    sub_6570D0(*((uint32_t *)this + 262497));
    v43 = *(uint32_t *)(dword_8F8548 + 32);
    if ( v43 >= 0 && sub_655E70((uint32_t *)dword_8F8548, *(uint32_t *)(dword_8F8548 + 32)) < 0.0 )
      sub_655E90((uint32_t *)dword_8F8548, v43);
  }
  LOBYTE(v44) = *(this + 1050008);
  if ( (uint8_t)v44 != 0 )
  {
    v45 = *((uint32_t *)this + 262505);
    v44 = sub_699000((int)(this + 1049996));
    if ( v44 >= v45 )
    {
      *(this + 1050009) = 0;
      *(this + 1050010) = 0;
      *(this + 1050008) = 1;
      sub_698F90((int)(this + 1049996), dword_78FF60, 0);
      v46 = 0;
      v47 = this + 1050108;
      do
      {
        v44 = sub_656710();
        if ( *(uint32_t *)(v44 + 4 * v46) != -1 )
        {
          v48 = (uint32_t *)sub_656710();
          v44 = sub_656840(v48);
          if ( v46 != v44 )
          {
            v49 = (uint32_t *)sub_656710();
            v44 = sub_656850(v49, v46);
            v50 = *(uint32_t *)v47;
            v51 = *(uint32_t *)v47 == 0;
            v75 = v44;
            if ( v51 )
              v52 = 0;
            else
              v52 = (*((uint32_t *)v47 + 1) - v50) >> 2;
            if ( v50 != 0 && v52 < (*((uint32_t *)v47 + 2) - v50) >> 2 )
            {
              v53 = *((int **)v47 + 1);
              *v53 = v44;
              *((uint32_t *)v47 + 1) = v53 + 1;
            }
            else
            {
              LOBYTE(v44) = sub_430C80(*((void **)v47 + 1), 1, (int)&v75);
            }
          }
        }
        ++v46;
        v47 += 16;
      }
      while ( v46 < 8 );
    }
  }
  return v44;
}


// ============================================================
// 【分区 8】窗口族 vmt4 存根 + 界面管理器（0x44A950-0x44FF60）
// IRDWindow/CNRD*Window 各窗口类 vmt4 槽（多为调用 0x44A950 共享实现或空存根）；
// CNRDInterfaceManager 构造 0x44BA00；模块切换收尾 0x44EA20（docs/13 §3 定案）。
// ============================================================
// ------------------------------------------------------------
// 0x44A950 IRDWindow__vmt4
// ------------------------------------------------------------
uint32_t */*thiscall*/ IRDWindow__vmt4(uint32_t *Block, char a2)
{
  *Block = &vftbl_IRDWindow;
  nullsub_3();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44A980 sub_44A980
// ------------------------------------------------------------
int /*thiscall*/ sub_44A980(uint32_t *this, int a2)
{
  if ( a2 >= *(this + 2) )
    return 0;
  else
    return *(uint32_t *)(*(this + 3) + 4 * a2);
}



// ------------------------------------------------------------
// 0x44A9A0 sub_44A9A0
// ------------------------------------------------------------
int /*cdecl*/ sub_44A9A0(int a1, int a2)
{
  return sub_657740(a1, a2);
}



// ------------------------------------------------------------
// 0x44A9C0 sub_44A9C0
// ------------------------------------------------------------
void /*thiscall*/ sub_44A9C0(uint32_t *this)
{
  *this = &vftbl_CNRDPrivateStoreWindow;
  sub_544960();
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44AA20 CNRDPrivateStoreWindow__vmt4
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDPrivateStoreWindow__vmt4(uint32_t *Block, char a2)
{
  sub_44A9C0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44AA50 sub_44AA50
// ------------------------------------------------------------
void /*thiscall*/ sub_44AA50(int this)
{
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 112) = 0;
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
  *(uint32_t *)(this + 104) = 12;
  *(uint32_t *)(this + 108) = 12;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 2420) = 0;
  *(uint32_t *)(this + 2424) = 0;
  *(uint32_t *)(this + 2428) = 0;
  *(uint32_t *)(this + 2432) = 0;
  *(uint32_t *)(this + 2436) = 0;
  *(uint32_t *)(this + 2440) = 0;
  *(uint32_t *)(this + 2444) = 0;
  *(uint32_t *)(this + 2532) = 0;
  *(uint32_t *)(this + 2536) = 0;
  *(uint32_t *)(this + 2448) = 0;
  *(uint32_t *)(this + 2452) = 0;
  sub_699070(this + 2456, 2u);
  *(uint32_t *)(this + 2484) = 0;
  *(uint32_t *)(this + 2488) = 0;
  *(uint32_t *)(this + 2492) = 0;
  *(uint32_t *)(this + 2496) = 0;
  *(uint32_t *)(this + 2500) = 0;
  *(uint32_t *)(this + 2504) = 0;
  *(uint8_t *)(this + 2524) = 0;
  *(uint8_t *)(this + 2525) = 0;
  *(uint32_t *)(this + 2528) = 0;
  *(uint32_t *)(this + 4) = 0;
}



// ------------------------------------------------------------
// 0x44AB50 sub_44AB50
// ------------------------------------------------------------
int /*thiscall*/ sub_44AB50(uint32_t *this, int a2, int a3)
{
  int result; // eax
  int v5; // esi
  int v6; // eax

  result = *(this + a2 + 26);
  if ( result != 12 )
  {
    v5 = *(this + result + 14);
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 48))(v5);
    sub_69A580(v6);
    *(this + a2 + 26) = a3;
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 16))(v5);
  }
  return result;
}



// ------------------------------------------------------------
// 0x44AB90 sub_44AB90
// ------------------------------------------------------------
void */*thiscall*/ sub_44AB90(uint32_t *this, void *a2)
{
  int v2; // edi
  void *result; // eax
  char v4; // dl

  v2 = *(this + 18);
  result = *(void **)(*(uint32_t *)(*(this + 17) + 20) + 104);
  v4 = 0;
  if ( result != a2 )
  {
    result = (void *)sub_69CE50(a2);
    v4 = 1;
  }
  if ( *(void **)(*(uint32_t *)(v2 + 20) + 104) == a2 )
  {
    if ( v4 == 0 )
      return result;
  }
  else
  {
    sub_69CE50(a2);
  }
  return sub_432EA0("TAB_SELECT", -1, 0, 0);
}



// ------------------------------------------------------------
// 0x44ABE0 sub_44ABE0
// ------------------------------------------------------------
int /*thiscall*/ sub_44ABE0(uint32_t *this, int a2)
{
  *(this + 626) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x44ABF0 sub_44ABF0
// ------------------------------------------------------------
int /*thiscall*/ sub_44ABF0(uint32_t *this)
{
  *(this + 626) = 17;
  byte_89D27C = 1;
  return CNCommandChecker__vmt40(0, 0);
}



// ------------------------------------------------------------
// 0x44AC10 sub_44AC10
// ------------------------------------------------------------
int /*thiscall*/ sub_44AC10(uint32_t *this)
{
  *(this + 626) = 0;
  sub_4071D0();
  return CNCommandChecker__vmt40(0, 1);
}



// ------------------------------------------------------------
// 0x44AC30 sub_44AC30
// ------------------------------------------------------------
int /*thiscall*/ sub_44AC30(uint32_t *this)
{
  int result; // eax

  *this = &vftbl_CNRDCursor;
  result = sub_48B720();
  *(this + 3) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 16) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x44AC80 sub_44AC80
// ------------------------------------------------------------
int /*thiscall*/ sub_44AC80(uint32_t *this)
{
  int result; // eax

  result = *(this + 626);
  if ( result == 1 || result == 2 )
  {
    *(this + 626) = 0;
    *(this + 627) = 12;
    *(this + 628) = 0;
    *(this + 629) = 0;
    *(this + 630) = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x44ACC0 sub_44ACC0
// ------------------------------------------------------------
int /*thiscall*/ sub_44ACC0(void *this, int a2)
{
  return sub_41A5E0((unsigned int)this + 14 * a2 + 496);
}



// ------------------------------------------------------------
// 0x44ACE0 sub_44ACE0
// ------------------------------------------------------------
char */*thiscall*/ sub_44ACE0(char *this, int a2)
{
  *(uint32_t *)this = &vftbl_CNRDCommunityMenu;
  *(this + 36) = 0;
  *(this + 37) = 0;
  *(this + 38) = 0;
  *(this + 39) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 6;
  *((uint32_t *)this + 14) = 12;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 1600;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 21) = 0;
  `eh vector constructor iterator'(this + 92, 0x1Cu, 5, sub_401170, sub_401000);
  sub_545480(this);
  sub_545D80(a2);
  return this;
}



// ------------------------------------------------------------
// 0x44AD80 sub_44AD80
// ------------------------------------------------------------
int /*thiscall*/ sub_44AD80(char *this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNRDCommunityMenu;
  sub_5454C0();
  `eh vector destructor iterator'(this + 92, 0x1Cu, 5, sub_401000);
  result = *((uint32_t *)this + 20);
  if ( result != 0 )
  {
    result = DeleteObject(*((HGDIOBJ *)this + 20));
    *((uint32_t *)this + 20) = 0;
  }
  *(this + 36) = 0;
  *(this + 37) = 0;
  *(this + 38) = 0;
  *(this + 39) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 21) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x44AE20 sub_44AE20
// ------------------------------------------------------------
int /*thiscall*/ sub_44AE20(uint32_t *this)
{
  int result; // eax

  *this = &vftbl_CNRDTutorial;
  result = sub_546060();
  *(this + 5) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 24) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x44AE70 sub_44AE70
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44AE70(uint8_t *this, void *Block)
{
  *(uint32_t *)this = &vftbl_CNRDCountDown;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 6;
  *((uint32_t *)this + 10) = 12;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 1600;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *(this + 76) = 0;
  *((uint32_t *)this + 18) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 20) = 0;
  *(this + 84) = 1;
  *(this + 86) = 0;
  *(this + 85) = 0;
  *((uint32_t *)this + 24) = 0;
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 22) = 0;
  sub_49BD60(this);
  sub_49C380(Block);
  return this;
}



// ------------------------------------------------------------
// 0x44AF20 sub_44AF20
// ------------------------------------------------------------
int /*thiscall*/ sub_44AF20(void *this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNRDCountDown;
  sub_49BD80();
  *((uint32_t *)this + 18) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 76) = 0;
  result = *((uint32_t *)this + 16);
  if ( result != 0 )
  {
    result = DeleteObject(*((HGDIOBJ *)this + 16));
    *((uint32_t *)this + 16) = 0;
  }
  *((uint8_t *)this + 20) = 0;
  *((uint8_t *)this + 21) = 0;
  *((uint8_t *)this + 22) = 0;
  *((uint8_t *)this + 23) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x44AFB0 sub_44AFB0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44AFB0(uint8_t *this, void *Block, int a3)
{
  *(uint32_t *)this = &vftbl_CNRDWarRoomResult;
  *(this + 12) = 0;
  *((uint32_t *)this + 2) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 4) = 0;
  *(this + 20) = 1;
  *(this + 22) = 0;
  *(this + 21) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 6) = 0;
  *(this + 64) = 0;
  *((uint32_t *)this + 15) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 17) = 0;
  *(this + 72) = 1;
  *(this + 74) = 0;
  *(this + 73) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 19) = 0;
  *(this + 92) = 0;
  *((uint32_t *)this + 22) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 24) = 0;
  *(this + 100) = 1;
  *(this + 102) = 0;
  *(this + 101) = 0;
  *((uint32_t *)this + 28) = 0;
  *((uint32_t *)this + 27) = 0;
  *((uint32_t *)this + 26) = 0;
  sub_49DB10(this);
  sub_49E340(Block, a3);
  return this;
}



// ------------------------------------------------------------
// 0x44B060 sub_44B060
// ------------------------------------------------------------
char /*thiscall*/ sub_44B060(uint32_t *this)
{
  *this = &vftbl_CNRDWarRoomResult;
  sub_49DB30();
  *(this + 22) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 92) = 0;
  *(this + 15) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 64) = 0;
  *(this + 2) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 12) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x44B0C0 sub_44B0C0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44B0C0(uint8_t *this, void *Block, int a3)
{
  *(uint32_t *)this = &vftbl_CNRDResult;
  *(this + 12) = 0;
  *((uint32_t *)this + 2) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 4) = 0;
  *(this + 20) = 1;
  *(this + 22) = 0;
  *(this + 21) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 6) = 0;
  *(this + 96) = 0;
  *((uint32_t *)this + 23) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 25) = 0;
  *(this + 104) = 1;
  *(this + 106) = 0;
  *(this + 105) = 0;
  *((uint32_t *)this + 29) = 0;
  *((uint32_t *)this + 28) = 0;
  *((uint32_t *)this + 27) = 0;
  sub_476C10(this);
  sub_478C70(Block, a3);
  return this;
}



// ------------------------------------------------------------
// 0x44B160 sub_44B160
// ------------------------------------------------------------
char /*thiscall*/ sub_44B160(uint32_t *this)
{
  *this = &vftbl_CNRDResult;
  sub_476C50();
  *(this + 23) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 96) = 0;
  *(this + 2) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 12) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x44B1C0 CNRDItemInventoryWindow__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemInventoryWindow__vmt4(void *Block, char a2)
{
  sub_44B1F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B1F0 sub_44B1F0
// ------------------------------------------------------------
void /*thiscall*/ sub_44B1F0(uint32_t *this)
{
  *this = &vftbl_CNRDItemInventoryWindow;
  sub_547000();
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44B250 CNRDAvatarInventoryWindow__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDAvatarInventoryWindow__vmt4(void *Block, char a2)
{
  sub_44B280();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B280 sub_44B280
// ------------------------------------------------------------
void /*thiscall*/ sub_44B280(uint32_t *this)
{
  *this = &vftbl_CNRDAvatarInventoryWindow;
  sub_548D40();
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44B2E0 sub_44B2E0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44B2E0(uint8_t *this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(a2, 0);
  *(uint32_t *)this = &vftbl_CNRDItemTradeWindow;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 6;
  *((uint32_t *)this + 12) = 12;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 1600;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  *(this + 80) = 0;
  *(this + 81) = 0;
  *(this + 82) = 0;
  *(this + 83) = 0;
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 24) = 6;
  *((uint32_t *)this + 25) = 12;
  *((uint32_t *)this + 26) = 0;
  *((uint32_t *)this + 27) = 1600;
  *((uint32_t *)this + 28) = 0;
  *((uint32_t *)this + 29) = 0;
  *((uint32_t *)this + 30) = 0;
  *((uint32_t *)this + 31) = 0;
  *((uint32_t *)this + 32) = 0;
  sub_549DC0(this);
  sub_54A930(this);
  return this;
}



// ------------------------------------------------------------
// 0x44B3B0 CNRDItemTradeWindow__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemTradeWindow__vmt4(void *Block, char a2)
{
  sub_44B3E0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B3E0 sub_44B3E0
// ------------------------------------------------------------
void /*thiscall*/ sub_44B3E0(HGDIOBJ *this)
{
  *this = &vftbl_CNRDItemTradeWindow;
  sub_54A8B0();
  if ( *(this + 31) != nullptr )
  {
    DeleteObject(*(this + 31));
    *(this + 31) = nullptr;
  }
  *((uint8_t *)this + 80) = 0;
  *((uint8_t *)this + 81) = 0;
  *((uint8_t *)this + 82) = 0;
  *((uint8_t *)this + 83) = 0;
  *(this + 23) = nullptr;
  *(this + 24) = nullptr;
  *(this + 25) = nullptr;
  *(this + 26) = nullptr;
  *(this + 27) = nullptr;
  *(this + 28) = nullptr;
  *(this + 29) = nullptr;
  *(this + 30) = nullptr;
  *(this + 31) = nullptr;
  *(this + 32) = nullptr;
  if ( *(this + 18) != nullptr )
  {
    DeleteObject(*(this + 18));
    *(this + 18) = nullptr;
  }
  *((uint8_t *)this + 28) = 0;
  *((uint8_t *)this + 29) = 0;
  *((uint8_t *)this + 30) = 0;
  *((uint8_t *)this + 31) = 0;
  *(this + 10) = nullptr;
  *(this + 11) = nullptr;
  *(this + 12) = nullptr;
  *(this + 13) = nullptr;
  *(this + 14) = nullptr;
  *(this + 15) = nullptr;
  *(this + 16) = nullptr;
  *(this + 17) = nullptr;
  *(this + 18) = nullptr;
  *(this + 19) = nullptr;
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44B4C0 CNRDSkillInventoryWindow__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDSkillInventoryWindow__vmt4(void *Block, char a2)
{
  sub_44B4F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B4F0 sub_44B4F0
// ------------------------------------------------------------
void /*thiscall*/ sub_44B4F0(uint32_t *this)
{
  *this = &vftbl_CNRDSkillInventoryWindow;
  sub_54ABE0();
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44B550 sub_44B550
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44B550(uint8_t *this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(a2, 0);
  *(uint32_t *)this = &vftbl_CNRDStatusWindow;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 6;
  *((uint32_t *)this + 12) = 12;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 1600;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  sub_54B770(this);
  sub_54B8B0(this);
  return this;
}



// ------------------------------------------------------------
// 0x44B5F0 CNRDStatusWindow__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDStatusWindow__vmt4(void *Block, char a2)
{
  sub_44B620();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B620 sub_44B620
// ------------------------------------------------------------
void /*thiscall*/ sub_44B620(HGDIOBJ *this)
{
  *this = &vftbl_CNRDStatusWindow;
  sub_54B780();
  if ( *(this + 18) != nullptr )
  {
    DeleteObject(*(this + 18));
    *(this + 18) = nullptr;
  }
  *((uint8_t *)this + 28) = 0;
  *((uint8_t *)this + 29) = 0;
  *((uint8_t *)this + 30) = 0;
  *((uint8_t *)this + 31) = 0;
  *(this + 10) = nullptr;
  *(this + 11) = nullptr;
  *(this + 12) = nullptr;
  *(this + 13) = nullptr;
  *(this + 14) = nullptr;
  *(this + 15) = nullptr;
  *(this + 16) = nullptr;
  *(this + 17) = nullptr;
  *(this + 18) = nullptr;
  *(this + 19) = nullptr;
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44B6C0 sub_44B6C0
// ------------------------------------------------------------
int /*cdecl*/ sub_44B6C0(int a1)
{
  if ( dword_9A0228 == 0 )
  {
    if ( (dword_98B718 & 1) == 0 )
    {
      dword_98B718 |= 1u;
      sub_657800(a1, 256);
      atexit(sub_6BF5C0);
    }
    dword_9A0228 = (int)&unk_98B6F8;
  }
  return sub_6578B0(a1);
}



// ------------------------------------------------------------
// 0x44B750 sub_44B750
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44B750(uint8_t *this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(a2, 0);
  *(uint32_t *)this = &vftbl_CNRDItemToolWindow;
  *(this + 40) = 0;
  *((uint32_t *)this + 9) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 11) = 0;
  *(this + 48) = 1;
  *(this + 50) = 0;
  *(this + 49) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 25) = 0;
  *(this + 104) = 0;
  *((uint32_t *)this + 27) = 0;
  *((uint32_t *)this + 28) = 0;
  *((uint32_t *)this + 29) = 0;
  sub_54C8B0(this);
  sub_54D6E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x44B7F0 CNRDItemToolWindow__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemToolWindow__vmt4(void *Block, char a2)
{
  sub_44B820();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B820 sub_44B820
// ------------------------------------------------------------
void /*thiscall*/ sub_44B820(uint32_t *this)
{
  *this = &vftbl_CNRDItemToolWindow;
  sub_54C8F0();
  *(this + 9) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 40) = 0;
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44B880 CNRDPrivateStoreWindow_Display__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDPrivateStoreWindow_Display__vmt4(void *Block, char a2)
{
  sub_44B8B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B8B0 sub_44B8B0
// ------------------------------------------------------------
void /*thiscall*/ sub_44B8B0(uint32_t *this)
{
  *this = &vftbl_CNRDPrivateStoreWindow_Display;
  sub_544960();
  sub_44A9C0(this);
}



// ------------------------------------------------------------
// 0x44B900 CNRDPrivateStoreWindow_Sell__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDPrivateStoreWindow_Sell__vmt4(void *Block, char a2)
{
  sub_44B930();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B930 sub_44B930
// ------------------------------------------------------------
void /*thiscall*/ sub_44B930(uint32_t *this)
{
  *this = &vftbl_CNRDPrivateStoreWindow_Sell;
  sub_544960();
  sub_44A9C0(this);
}



// ------------------------------------------------------------
// 0x44B980 CNRDPrivateStoreWindow_Buy__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDPrivateStoreWindow_Buy__vmt4(void *Block, char a2)
{
  sub_44B9B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B9B0 sub_44B9B0
// ------------------------------------------------------------
void /*thiscall*/ sub_44B9B0(uint32_t *this)
{
  *this = &vftbl_CNRDPrivateStoreWindow_Buy;
  sub_544960();
  sub_44A9C0(this);
}



// ------------------------------------------------------------
// 0x44BA00 CNRDInterfaceManager__vmt0
// ------------------------------------------------------------
// CNRDInterfaceManager 构造：窗口族 vmt4 存根的宿主
int /*thiscall*/ CNRDInterfaceManager__vmt0(int this, int a2)
{
  int result; // eax
  int v4; // ebx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  result = a2;
  if ( *(uint32_t *)(this + 4) != 0 || a2 != *(uint32_t *)(this + 112) )
  {
    if ( a2 == *(uint32_t *)(this + 2448) )
    {
      if ( *(uint8_t *)(this + 2468) != 0 )
      {
        sub_698F90(this + 2456, 30, 0);
        v4 = *(uint32_t *)(this + 2480);
        if ( sub_699000(this + 2456) < v4 )
        {
          v5 = *(uint32_t *)(this + 2452);
          if ( v5 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v5 + 128))(
              v5,
              0,
              0,
              dword_79C0B0,
              1098907648,
              1094713344,
              0,
              1694498815,
              1333788672,
              1333788672);
        }
      }
      if ( *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 216) != -1 )
        *((uint32_t *)dword_8F8528 + 621) = 255;
      if ( *(uint32_t *)(this + 2484) != 0
        && (*(uint32_t *)(dword_8F7A24 + 12) == 5 || byte_77F280 != 0 || *(uint8_t *)(dword_8F7B08 + 8) != 0) )
      {
        v6 = *(uint32_t *)(this + 2488);
        if ( v6 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v6 + 128))(
            v6,
            0,
            0,
            dword_79C0B0,
            1098907648,
            1094713344,
            0,
            (*(uint8_t *)(this + 2484) << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
      }
      result = *(uint32_t *)(this + 2492);
      if ( result != 0 )
      {
        sub_491530(2, 0);
        v7 = *(uint32_t *)(this + 2496);
        if ( v7 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v7 + 128))(
            v7,
            0,
            0,
            dword_79C0B0,
            1098907648,
            1094713344,
            0,
            (*(uint8_t *)(this + 2492) << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        return sub_491630(2);
      }
    }
  }
  else
  {
    sub_468FC0(1);
    return sub_464C60(*(uint32_t *)(this + 16));
  }
  return result;
}



// ------------------------------------------------------------
// 0x44BBA0 sub_44BBA0
// ------------------------------------------------------------
uint8_t /*thiscall*/ sub_44BBA0(uint32_t *this, int a2, uint8_t a3)
{
  uint8_t result; // al
  int v5; // edi
  int v6; // ebx
  int v7; // eax

  result = a2;
  if ( a2 != 12 )
  {
    v5 = *(this + a2 + 14);
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 52))(v5);
    if ( *(this + v6 + 26) == a2 )
    {
      result = a3;
      if ( a3 != 0 )
        return sub_44AB50(this, v6, 12);
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 12))(v5);
      if ( result != 0 )
      {
        sub_44AB50(this, v6, a2);
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 48))(v5);
        sub_69A840(v7);
        *(this + v6 + 26) = a2;
        return (uint8_t)sub_432EA0("WINDOW_SHOW", -1, 0, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x44BC30 sub_44BC30
// ------------------------------------------------------------
void */*thiscall*/ sub_44BC30(uint32_t *this, void *a2, int a3, int a4, int a5, int a6, void *a7)
{
  void *result; // eax
  int v8; // edx

  result = a2;
  *(this + 627) = a3;
  *(this + 628) = a4;
  *(this + 629) = a5;
  *(this + 626) = a2;
  *(this + 630) = a6;
  if ( a2 == (void *)1 )
  {
    sub_432EA0("ICON_PICK", -1, 0, 0);
    result = a7;
    if ( a7 != nullptr )
      return (void *)sub_41A590((unsigned int)a7 + 572, v8, 1);
  }
  else if ( a2 == (void *)2 )
  {
    result = sub_432EA0("ITEM_PICK", -1, 0, 0);
    if ( a7 != nullptr )
      return (void *)(*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)a7 + 88))(a7, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x44BCC0 sub_44BCC0
// ------------------------------------------------------------
char /*thiscall*/ sub_44BCC0(uint32_t *this)
{
  int v1; // esi
  uint32_t *i; // ecx

  v1 = 0;
  for ( i = this + 34; *i == 0 || (i[1] - *i) >> 2 == 0; i += 4 )
  {
    if ( ++v1 >= 71 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x44BD00 sub_44BD00
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_44BD00(int a1, int a2, uint32_t *a3)
{
  int v3; // ecx
  uint32_t *result; // eax
  int v5; // esi

  v3 = a2;
  for ( result = a3; v3 != a1; result[1] = *(uint32_t *)(v3 + 4) )
  {
    v5 = *(uint32_t *)(v3 - 8);
    v3 -= 8;
    result -= 2;
    *result = v5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x44BD30 sub_44BD30
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_44BD30(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax

  v3 = a1;
  for ( result = a3; v3 != a2; result += 2 )
  {
    if ( result != nullptr )
    {
      *result = *v3;
      result[1] = v3[1];
    }
    v3 += 2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x44BD60 sub_44BD60
// ------------------------------------------------------------
char /*stdcall*/ sub_44BD60(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_44BD60(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x44BDA0 sub_44BDA0
// ------------------------------------------------------------
char */*thiscall*/ sub_44BDA0(char *this, void *Block)
{
  *(uint32_t *)this = &vftbl_CNRDChatting;
  *(this + 152) = 0;
  *((uint32_t *)this + 37) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 39) = 0;
  *(this + 160) = 1;
  *(this + 162) = 0;
  *(this + 161) = 0;
  *((uint32_t *)this + 43) = 0;
  *((uint32_t *)this + 42) = 0;
  *((uint32_t *)this + 41) = 0;
  *(this + 264) = 0;
  *((uint32_t *)this + 65) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 67) = 0;
  *(this + 272) = 1;
  *(this + 274) = 0;
  *(this + 273) = 0;
  *((uint32_t *)this + 71) = 0;
  *((uint32_t *)this + 70) = 0;
  *((uint32_t *)this + 69) = 0;
  *((uint32_t *)this + 79) = 15;
  *((uint32_t *)this + 78) = 0;
  *(this + 296) = 0;
  `eh vector constructor iterator'(this + 324, 0x1Cu, 20, sub_40C120, sub_501490);
  `eh vector constructor iterator'(this + 884, 0x1Cu, 20, sub_40C120, sub_501490);
  *(this + 1480) = 0;
  *((uint32_t *)this + 369) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 371) = 0;
  *(this + 1488) = 1;
  *(this + 1490) = 0;
  *(this + 1489) = 0;
  *((uint32_t *)this + 375) = 0;
  *((uint32_t *)this + 374) = 0;
  *((uint32_t *)this + 373) = 0;
  *(this + 1508) = 0;
  *((uint32_t *)this + 376) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 378) = 0;
  *(this + 1516) = 1;
  *(this + 1518) = 0;
  *(this + 1517) = 0;
  *((uint32_t *)this + 382) = 0;
  *((uint32_t *)this + 381) = 0;
  *((uint32_t *)this + 380) = 0;
  *((uint32_t *)this + 455) = 15;
  *((uint32_t *)this + 454) = 0;
  *(this + 1800) = 0;
  sub_43C730((int)this);
  sub_43E150((int)this, Block);
  return this;
}



// ------------------------------------------------------------
// 0x44BF40 sub_44BF40
// ------------------------------------------------------------
void /*thiscall*/ sub_44BF40(int this)
{
  *(uint32_t *)this = &vftbl_CNRDChatting;
  sub_43B6A0((uint32_t *)this);
  if ( *(uint32_t *)(this + 1820) >= 0x10u )
    j__free(*(void **)(this + 1800));
  *(uint32_t *)(this + 1820) = 15;
  *(uint32_t *)(this + 1816) = 0;
  *(uint8_t *)(this + 1800) = 0;
  *(uint32_t *)(this + 1504) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1508) = 0;
  *(uint32_t *)(this + 1476) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1480) = 0;
  `eh vector destructor iterator'((void *)(this + 884), 0x1Cu, 20, sub_501490);
  `eh vector destructor iterator'((void *)(this + 324), 0x1Cu, 20, sub_501490);
  if ( *(uint32_t *)(this + 316) >= 0x10u )
    j__free(*(void **)(this + 296));
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 15;
  *(uint8_t *)(this + 296) = 0;
  *(uint32_t *)(this + 260) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 264) = 0;
  *(uint32_t *)(this + 148) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 152) = 0;
}



// ------------------------------------------------------------
// 0x44C050 sub_44C050
// ------------------------------------------------------------
void /*thiscall*/ sub_44C050(void **this)
{
  void (/*thiscall*/ ***v2)(void *, int); // ecx

  v2 = (void (/*thiscall*/ ***)(void *, int))*this;
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *this = nullptr;
  if ( (unsigned int)*(this + 7) >= 0x10 )
    j__free(*(this + 2));
  *(this + 7) = (void *)15;
  *(this + 6) = nullptr;
  *((uint8_t *)this + 8) = 0;
}



// ------------------------------------------------------------
// 0x44C0C0 sub_44C0C0
// ------------------------------------------------------------
int /*thiscall*/ sub_44C0C0(int this)
{
  if ( *(uint32_t *)(this + 72) >= 0x10u )
    j__free(*(void **)(this + 52));
  *(uint32_t *)(this + 72) = 15;
  *(uint32_t *)(this + 68) = 0;
  *(uint8_t *)(this + 52) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x44C0F0 sub_44C0F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44C0F0(uint32_t *this, uint32_t *a2, char *a3)
{
  memcpy_0(a3, a3 + 4, 4 * ((*(this + 2) - (int)(a3 + 4)) >> 2));
  *(this + 2) -= 4;
  *a2 = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x44C130 sub_44C130
// ------------------------------------------------------------
void /*thiscall*/ sub_44C130(HGDIOBJ *this)
{
  *this = &vftbl_CNRDWarRoomInterface;
  sub_49C9E0();
  if ( *(this + 56) != nullptr )
  {
    DeleteObject(*(this + 56));
    *(this + 56) = nullptr;
  }
  *((uint8_t *)this + 180) = 0;
  *((uint8_t *)this + 181) = 0;
  *((uint8_t *)this + 182) = 0;
  *((uint8_t *)this + 183) = 0;
  *(this + 48) = nullptr;
  *(this + 49) = nullptr;
  *(this + 50) = nullptr;
  *(this + 51) = nullptr;
  *(this + 52) = nullptr;
  *(this + 53) = nullptr;
  *(this + 54) = nullptr;
  *(this + 55) = nullptr;
  *(this + 56) = nullptr;
  *(this + 57) = nullptr;
  if ( *(this + 43) != nullptr )
  {
    DeleteObject(*(this + 43));
    *(this + 43) = nullptr;
  }
  *((uint8_t *)this + 128) = 0;
  *((uint8_t *)this + 129) = 0;
  *((uint8_t *)this + 130) = 0;
  *((uint8_t *)this + 131) = 0;
  *(this + 35) = nullptr;
  *(this + 36) = nullptr;
  *(this + 37) = nullptr;
  *(this + 38) = nullptr;
  *(this + 39) = nullptr;
  *(this + 40) = nullptr;
  *(this + 41) = nullptr;
  *(this + 42) = nullptr;
  *(this + 43) = nullptr;
  *(this + 44) = nullptr;
  if ( *(this + 30) != nullptr )
  {
    DeleteObject(*(this + 30));
    *(this + 30) = nullptr;
  }
  *((uint8_t *)this + 76) = 0;
  *((uint8_t *)this + 77) = 0;
  *((uint8_t *)this + 78) = 0;
  *((uint8_t *)this + 79) = 0;
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *(this + 24) = nullptr;
  *(this + 25) = nullptr;
  *(this + 26) = nullptr;
  *(this + 27) = nullptr;
  *(this + 28) = nullptr;
  *(this + 29) = nullptr;
  *(this + 30) = nullptr;
  *(this + 31) = nullptr;
  if ( *(this + 3) != nullptr )
    j__free(*(this + 3));
  *(this + 3) = nullptr;
  *(this + 4) = nullptr;
  *(this + 5) = nullptr;
}



// ------------------------------------------------------------
// 0x44C2A0 sub_44C2A0
// ------------------------------------------------------------
void /*thiscall*/ sub_44C2A0(void *this)
{
  int v2; // ecx

  if ( *((uint8_t *)this + 80) != 0 )
  {
    v2 = *((uint32_t *)this + 19);
    if ( v2 != 0 )
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 4))(v2, 1);
  }
  if ( *((uint32_t *)this + 18) >= 0x10u )
    j__free(*((void **)this + 13));
  *((uint32_t *)this + 18) = 15;
  *((uint32_t *)this + 17) = 0;
  *((uint8_t *)this + 52) = 0;
}



// ------------------------------------------------------------
// 0x44C310 sub_44C310
// ------------------------------------------------------------
void /*thiscall*/ sub_44C310(HGDIOBJ *this)
{
  *this = &vftbl_CNRDPopupMenu;
  sub_5256E0();
  if ( *(this + 52) != nullptr )
  {
    DeleteObject(*(this + 52));
    *(this + 52) = nullptr;
  }
  *((uint8_t *)this + 164) = 0;
  *((uint8_t *)this + 165) = 0;
  *((uint8_t *)this + 166) = 0;
  *((uint8_t *)this + 167) = 0;
  *(this + 44) = nullptr;
  *(this + 45) = nullptr;
  *(this + 46) = nullptr;
  *(this + 47) = nullptr;
  *(this + 48) = nullptr;
  *(this + 49) = nullptr;
  *(this + 50) = nullptr;
  *(this + 51) = nullptr;
  *(this + 52) = nullptr;
  *(this + 53) = nullptr;
  if ( *(this + 37) != nullptr )
    j__free(*(this + 37));
  *(this + 37) = nullptr;
  *(this + 38) = nullptr;
  *(this + 39) = nullptr;
  if ( (unsigned int)*(this + 11) >= 0x10 )
    j__free(*(this + 6));
  *(this + 10) = nullptr;
  *(this + 11) = (HGDIOBJ)15;
  *((uint8_t *)this + 24) = 0;
}



// ------------------------------------------------------------
// 0x44C410 sub_44C410
// ------------------------------------------------------------
char /*thiscall*/ sub_44C410(uint32_t *this, int a2)
{
  int v2; // edx
  uint32_t *v3; // eax
  int v4; // edx
  uint32_t *v5; // ebx
  uint32_t *v6; // esi
  int v7; // edi
  int v9; // [esp+Ch] [ebp-Ch]
  uint32_t *v10; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]
  uint32_t *v12; // [esp+20h] [ebp+8h]

  v2 = *(this + a2 + 30);
  v3 = *(uint32_t **)(v2 + 96);
  v4 = v2 + 92;
  v9 = v4;
  v12 = v3;
  if ( v3 != (uint32_t *)*v3 )
  {
    v10 = this + 35;
    while ( 2 )
    {
      v5 = v10;
      for ( i = 0; i < 71; ++i )
      {
        v6 = (uint32_t *)*(v5 - 1);
        if ( v6 != (uint32_t *)*v5 )
        {
          while ( 1 )
          {
            v7 = v12[1];
            if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v6 + 36))(*v6) == *(uint32_t *)(v7 + 8)
              && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v6 + 20))(*v6) != 0 )
            {
              return 1;
            }
            if ( ++v6 == (uint32_t *)*v5 )
            {
              v4 = v9;
              break;
            }
          }
        }
        v5 += 4;
      }
      v12 = (uint32_t *)v12[1];
      if ( v12 != **(uint32_t ***)(v4 + 4) )
        continue;
      break;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x44C4C0 sub_44C4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_44C4C0(char *this)
{
  int result; // eax

  *(uint32_t *)this = &CNRDBaseInterface::`vftable';
  sub_46ABB0();
  *((uint32_t *)this + 358) = &nengine::IObject::`vftable';
  *(this + 1436) = 0;
  *((uint32_t *)this + 351) = &nengine::IObject::`vftable';
  *(this + 1408) = 0;
  *((uint32_t *)this + 328) = &nengine::IObject::`vftable';
  *(this + 1316) = 0;
  *((uint32_t *)this + 312) = &nengine::IObject::`vftable';
  *(this + 1252) = 0;
  *((uint32_t *)this + 296) = &nengine::IObject::`vftable';
  *(this + 1188) = 0;
  *((uint32_t *)this + 289) = &nengine::IObject::`vftable';
  *(this + 1160) = 0;
  *((uint32_t *)this + 282) = &nengine::IObject::`vftable';
  *(this + 1132) = 0;
  `eh vector destructor iterator'(this + 1024, 0x34u, 2, sub_416D50);
  if ( *((uint32_t *)this + 239) != 0 )
  {
    DeleteObject(*((HGDIOBJ *)this + 239));
    *((uint32_t *)this + 239) = 0;
  }
  *(this + 912) = 0;
  *(this + 913) = 0;
  *(this + 914) = 0;
  *(this + 915) = 0;
  *((uint32_t *)this + 231) = 0;
  *((uint32_t *)this + 232) = 0;
  *((uint32_t *)this + 233) = 0;
  *((uint32_t *)this + 234) = 0;
  *((uint32_t *)this + 235) = 0;
  *((uint32_t *)this + 236) = 0;
  *((uint32_t *)this + 237) = 0;
  *((uint32_t *)this + 238) = 0;
  *((uint32_t *)this + 239) = 0;
  *((uint32_t *)this + 240) = 0;
  sub_6569D0(this + 896);
  j__free(*((void **)this + 225));
  *((uint32_t *)this + 225) = 0;
  *((uint32_t *)this + 215) = &nengine::IObject::`vftable';
  *(this + 864) = 0;
  if ( *((uint32_t *)this + 208) != 0 )
    j__free(*((void **)this + 208));
  *((uint32_t *)this + 208) = 0;
  *((uint32_t *)this + 209) = 0;
  *((uint32_t *)this + 210) = 0;
  if ( *((uint32_t *)this + 204) != 0 )
  {
    DeleteObject(*((HGDIOBJ *)this + 204));
    *((uint32_t *)this + 204) = 0;
  }
  *(this + 772) = 0;
  *(this + 773) = 0;
  *(this + 774) = 0;
  *(this + 775) = 0;
  *((uint32_t *)this + 196) = 0;
  *((uint32_t *)this + 197) = 0;
  *((uint32_t *)this + 198) = 0;
  *((uint32_t *)this + 199) = 0;
  *((uint32_t *)this + 200) = 0;
  *((uint32_t *)this + 201) = 0;
  *((uint32_t *)this + 202) = 0;
  *((uint32_t *)this + 203) = 0;
  *((uint32_t *)this + 204) = 0;
  *((uint32_t *)this + 205) = 0;
  if ( *((uint32_t *)this + 192) >= 0x10u )
    j__free(*((void **)this + 187));
  *((uint32_t *)this + 192) = 15;
  *((uint32_t *)this + 191) = 0;
  *(this + 748) = 0;
  sub_6569D0(this + 712);
  j__free(*((void **)this + 179));
  *((uint32_t *)this + 179) = 0;
  sub_6569D0(this + 696);
  j__free(*((void **)this + 175));
  *((uint32_t *)this + 175) = 0;
  *((uint32_t *)this + 167) = &nengine::IObject::`vftable';
  *(this + 672) = 0;
  `eh vector destructor iterator'(this + 584, 0x1Cu, 3, sub_401000);
  *((uint32_t *)this + 135) = &nengine::IObject::`vftable';
  *(this + 544) = 0;
  *((uint32_t *)this + 128) = &nengine::IObject::`vftable';
  *(this + 516) = 0;
  if ( *((uint32_t *)this + 125) != 0 )
  {
    DeleteObject(*((HGDIOBJ *)this + 125));
    *((uint32_t *)this + 125) = 0;
  }
  *(this + 456) = 0;
  *(this + 457) = 0;
  *(this + 458) = 0;
  *(this + 459) = 0;
  *((uint32_t *)this + 117) = 0;
  *((uint32_t *)this + 118) = 0;
  *((uint32_t *)this + 119) = 0;
  *((uint32_t *)this + 120) = 0;
  *((uint32_t *)this + 121) = 0;
  *((uint32_t *)this + 122) = 0;
  *((uint32_t *)this + 123) = 0;
  *((uint32_t *)this + 124) = 0;
  *((uint32_t *)this + 125) = 0;
  *((uint32_t *)this + 126) = 0;
  `eh vector destructor iterator'(this + 232, 0x1Cu, 8, sub_401000);
  result = *((uint32_t *)this + 42);
  if ( result != 0 )
  {
    result = DeleteObject(*((HGDIOBJ *)this + 42));
    *((uint32_t *)this + 42) = 0;
  }
  *(this + 124) = 0;
  *(this + 125) = 0;
  *(this + 126) = 0;
  *(this + 127) = 0;
  *((uint32_t *)this + 34) = 0;
  *((uint32_t *)this + 35) = 0;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 39) = 0;
  *((uint32_t *)this + 40) = 0;
  *((uint32_t *)this + 41) = 0;
  *((uint32_t *)this + 42) = 0;
  *((uint32_t *)this + 43) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x44C830 sub_44C830
// ------------------------------------------------------------
void /*thiscall*/ sub_44C830(void *this)
{
  *(uint32_t *)this = &vftbl_CNRDCharacterTalkBox;
  sub_49B370();
  *((uint32_t *)this + 15) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 64) = 0;
  if ( *((uint32_t *)this + 12) != 0 )
    j__free(*((void **)this + 12));
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  if ( *((uint32_t *)this + 9) >= 0x10u )
    j__free(*((void **)this + 4));
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 15;
  *((uint8_t *)this + 16) = 0;
}



// ------------------------------------------------------------
// 0x44C8C0 sub_44C8C0
// ------------------------------------------------------------
void /*thiscall*/ sub_44C8C0(uint32_t *this)
{
  *this = &vftbl_CNRDWarRoomBattleTalkBox;
  nullsub_3();
  sub_44C830(this);
}



// ------------------------------------------------------------
// 0x44C910 CNRDMakePriceWindow__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDMakePriceWindow__vmt0(void *Block, char a2)
{
  sub_44C940();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44C940 sub_44C940
// ------------------------------------------------------------
int /*thiscall*/ sub_44C940(void **this)
{
  *this = &vftbl_CNRDMakePriceWindow;
  sub_5449D0();
  return sub_43C2E0(this);
}



// ------------------------------------------------------------
// 0x44C990 sub_44C990
// ------------------------------------------------------------
int /*stdcall*/ sub_44C990(int a1, int a2)
{
  int i; // esi
  int result; // eax

  for ( i = a1; i != a2; i += 52 )
    result = sub_477AF0(i);
  return result;
}



// ------------------------------------------------------------
// 0x44C9C0 sub_44C9C0
// ------------------------------------------------------------
int /*thiscall*/ sub_44C9C0(uint32_t *this)
{
  int result; // eax

  *this = -1;
  *(this + 1) = -1;
  *(this + 2) = 0;
  *(this + 3) = -1;
  *((uint8_t *)this + 16) = -1;
  *(this + 5) = 0;
  *((uint8_t *)this + 24) = 0;
  *((uint16_t *)this + 13) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *((uint8_t *)this + 44) = -1;
  result = sub_4015C0((void *)szPassword, 0);
  *(this + 19) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x44CA10 sub_44CA10
// ------------------------------------------------------------
void /*thiscall*/ sub_44CA10(char *this)
{
  char *v2; // ecx

  v2 = this + 4;
  *((uint32_t *)v2 + 6) = 15;
  *((uint32_t *)v2 + 5) = 0;
  v2[4] = 0;
  *(uint32_t *)this = 0;
  sub_4015C0((void *)szPassword, 0);
}



// ------------------------------------------------------------
// 0x44CA70 sub_44CA70
// ------------------------------------------------------------
int /*thiscall*/ sub_44CA70(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 52 )
      sub_477AF0(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x44CAB0 sub_44CAB0
// ------------------------------------------------------------
void /*noreturn*/ sub_44CAB0()
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
// 0x44CB20 sub_44CB20
// ------------------------------------------------------------
int ***/*thiscall*/ sub_44CB20(uint32_t *this, int ***a2, int **a3)
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
  if ( *((uint8_t *)a3 + 21) != 0 )
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
  sub_41C5E0(&a3);
  if ( *((uint8_t *)*v3 + 21) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
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
      if ( *((uint8_t *)v4 + 21) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_52E300(v4);
        v7 = v25;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_542490(v4);
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
  v14 = *((uint8_t *)v5 + 20);
  *((uint8_t *)v5 + 20) = *((uint8_t *)v3 + 20);
  *((uint8_t *)v3 + 20) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 20) == 1 )
  {
    v15 = v25;
    if ( v4 != *(int **)(v25[1] + 4) )
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
            v15 = v25;
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
            v15 = v25;
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
  v17 = v25[2];
  if ( v17 != 0 )
    v25[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x44CDE0 sub_44CDE0
// ------------------------------------------------------------
int (/*thiscall*/ **/*thiscall*/ sub_44CDE0(void **this))(void *Block, char)
{
  *this = &vftbl_CNRDPVPResult;
  sub_54DA10();
  if ( *(this + 39) != nullptr )
    j__free(*(this + 39));
  *(this + 39) = nullptr;
  *(this + 40) = nullptr;
  *(this + 41) = nullptr;
  if ( *(this + 30) != nullptr )
  {
    DeleteObject(*(this + 30));
    *(this + 30) = nullptr;
  }
  *((uint8_t *)this + 76) = 0;
  *((uint8_t *)this + 77) = 0;
  *((uint8_t *)this + 78) = 0;
  *((uint8_t *)this + 79) = 0;
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *(this + 24) = nullptr;
  *(this + 25) = nullptr;
  *(this + 26) = nullptr;
  *(this + 27) = nullptr;
  *(this + 28) = nullptr;
  *(this + 29) = nullptr;
  *(this + 30) = nullptr;
  *(this + 31) = nullptr;
  *((uint8_t *)this + 44) = 0;
  *(this + 10) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 16) = 0;
  *(this + 3) = &vftbl_nengine__IObject;
  return &vftbl_nengine__IObject;
}



// ------------------------------------------------------------
// 0x44CEA0 sub_44CEA0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44CEA0(uint32_t *this)
{
  char *v2; // ecx

  v2 = (char *)(this + 12);
  *((uint32_t *)v2 + 6) = 15;
  *((uint32_t *)v2 + 5) = 0;
  v2[4] = 0;
  *this = -1;
  *(this + 1) = -1;
  *(this + 2) = 0;
  *(this + 3) = -1;
  *((uint8_t *)this + 16) = -1;
  *(this + 5) = 0;
  *((uint8_t *)this + 24) = 0;
  *((uint16_t *)this + 13) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *((uint8_t *)this + 44) = -1;
  sub_4015C0((void *)szPassword, 0);
  *(this + 19) = 0;
  *((uint8_t *)this + 80) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x44CF30 sub_44CF30
// ------------------------------------------------------------
void /*thiscall*/ sub_44CF30(uint32_t *this)
{
  sub_44CEA0(this);
}



// ------------------------------------------------------------
// 0x44CF50 sub_44CF50
// ------------------------------------------------------------
char /*thiscall*/ sub_44CF50(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0xFFFFFFF )
    sub_44CAB0(this);
  v4 = (char *)operator new(16 * a2);
  *(this + 3) = &v4[16 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x44CFA0 sub_44CFA0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_44CFA0(int this, int Src, unsigned int a3, int *a4)
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
      sub_434730(this);
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
// 0x44D180 sub_44D180
// ------------------------------------------------------------
int */*thiscall*/ sub_44D180(int **this, int *a2, int a3, int a4)
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
    sub_44BD60(*(void ***)(v7 + 4));
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
        sub_44CB20(this, &a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x44D240 sub_44D240
// ------------------------------------------------------------
void /*thiscall*/ sub_44D240(int this, uint32_t *a2, unsigned int a3, int a4)
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
      sub_44CAB0(this);
    if ( v6 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v6) >> 3;
    else
      v10 = 0;
    if ( v7 >= a3 + v10 )
    {
      v18 = *(uint32_t *)(this + 8);
      v20 = (v18 - (int)a2) >> 3 < a3;
      v21 = 8 * a3;
      v30 = 8 * a3;
      v33 = v18;
      if ( v20 )
      {
        sub_44BD30(a2, v18, &a2[v21 / 4u]);
        v26 = a3 - ((*(uint32_t *)(this + 8) - (int)a2) >> 3);
        v25 = *(uint32_t *)(this + 8);
        v29 = 2;
        sub_5E51F0(v25, v26, v28);
        v22 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v22;
        sub_41FEB0(a2, (uint32_t *)(v22 - v30), v28);
      }
      else
      {
        v23 = v18 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(v18 - v21, v18, v18);
        sub_44BD00(a2, v23, v33);
        sub_41FEB0(a2, &a2[v30 / 4u], v28);
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
// 0x44D490 sub_44D490
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44D490(uint32_t *this, int a2)
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
// 0x44D530 sub_44D530
// ------------------------------------------------------------
char */*thiscall*/ sub_44D530(char *this, void *Block)
{
  uint32_t *v3; // eax
  int i; // ecx

  *(uint32_t *)this = &CNRDBaseInterface::`vftable';
  *(this + 124) = 0;
  *(this + 125) = 0;
  *(this + 126) = 0;
  *(this + 127) = 0;
  *((uint32_t *)this + 34) = 0;
  *((uint32_t *)this + 35) = 6;
  *((uint32_t *)this + 36) = 12;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 1600;
  *((uint32_t *)this + 39) = 0;
  *((uint32_t *)this + 40) = 0;
  *((uint32_t *)this + 41) = 0;
  *((uint32_t *)this + 42) = 0;
  *((uint32_t *)this + 43) = 0;
  `eh vector constructor iterator'(this + 232, 0x1Cu, 8, sub_401170, sub_401000);
  *(this + 456) = 0;
  *(this + 457) = 0;
  *(this + 458) = 0;
  *(this + 459) = 0;
  *((uint32_t *)this + 117) = 0;
  *((uint32_t *)this + 118) = 6;
  *((uint32_t *)this + 119) = 12;
  *((uint32_t *)this + 120) = 0;
  *((uint32_t *)this + 121) = 1600;
  *((uint32_t *)this + 122) = 0;
  *((uint32_t *)this + 123) = 0;
  *((uint32_t *)this + 124) = 0;
  *((uint32_t *)this + 125) = 0;
  *((uint32_t *)this + 126) = 0;
  *(this + 516) = 0;
  *((uint32_t *)this + 128) = &off_6C2B88;
  *((uint32_t *)this + 130) = 0;
  *(this + 524) = 1;
  *(this + 526) = 0;
  *(this + 525) = 0;
  *((uint32_t *)this + 134) = 0;
  *((uint32_t *)this + 133) = 0;
  *((uint32_t *)this + 132) = 0;
  *(this + 544) = 0;
  *((uint32_t *)this + 135) = &off_6C2B88;
  *((uint32_t *)this + 137) = 0;
  *(this + 552) = 1;
  *(this + 554) = 0;
  *(this + 553) = 0;
  *((uint32_t *)this + 141) = 0;
  *((uint32_t *)this + 140) = 0;
  *((uint32_t *)this + 139) = 0;
  `eh vector constructor iterator'(this + 584, 0x1Cu, 3, sub_401170, sub_401000);
  *(this + 672) = 0;
  *((uint32_t *)this + 167) = &off_6C2B88;
  *((uint32_t *)this + 169) = 0;
  *(this + 680) = 1;
  *(this + 682) = 0;
  *(this + 681) = 0;
  *((uint32_t *)this + 173) = 0;
  *((uint32_t *)this + 172) = 0;
  *((uint32_t *)this + 171) = 0;
  *((uint32_t *)this + 175) = sub_4A2CF0(this + 696);
  *((uint32_t *)this + 176) = 0;
  *((uint32_t *)this + 179) = sub_4A2CF0(this + 712);
  *((uint32_t *)this + 180) = 0;
  *((uint32_t *)this + 192) = 15;
  *((uint32_t *)this + 191) = 0;
  *(this + 748) = 0;
  *(this + 772) = 0;
  *(this + 773) = 0;
  *(this + 774) = 0;
  *(this + 775) = 0;
  *((uint32_t *)this + 196) = 0;
  *((uint32_t *)this + 197) = 6;
  *((uint32_t *)this + 198) = 12;
  *((uint32_t *)this + 199) = 0;
  *((uint32_t *)this + 200) = 1600;
  *((uint32_t *)this + 201) = 0;
  *((uint32_t *)this + 202) = 0;
  *((uint32_t *)this + 203) = 0;
  *((uint32_t *)this + 204) = 0;
  *((uint32_t *)this + 205) = 0;
  *((uint32_t *)this + 208) = 0;
  *((uint32_t *)this + 209) = 0;
  *((uint32_t *)this + 210) = 0;
  *(this + 864) = 0;
  *((uint32_t *)this + 215) = &off_6C2B88;
  *((uint32_t *)this + 217) = 0;
  *(this + 872) = 1;
  *(this + 874) = 0;
  *(this + 873) = 0;
  *((uint32_t *)this + 221) = 0;
  *((uint32_t *)this + 220) = 0;
  *((uint32_t *)this + 219) = 0;
  *((uint32_t *)this + 225) = sub_4A2CF0(this + 896);
  *((uint32_t *)this + 226) = 0;
  *(this + 912) = 0;
  *(this + 913) = 0;
  *(this + 914) = 0;
  *(this + 915) = 0;
  *((uint32_t *)this + 231) = 0;
  *((uint32_t *)this + 232) = 6;
  *((uint32_t *)this + 233) = 12;
  *((uint32_t *)this + 234) = 0;
  *((uint32_t *)this + 235) = 1600;
  *((uint32_t *)this + 236) = 0;
  *((uint32_t *)this + 237) = 0;
  *((uint32_t *)this + 238) = 0;
  *((uint32_t *)this + 239) = 0;
  *((uint32_t *)this + 240) = 0;
  *((uint32_t *)this + 242) = 2;
  *((uint32_t *)this + 243) = 0;
  v3 = this + 976;
  for ( i = 2; i != 0; --i )
  {
    *v3 = 2;
    v3[1] = 0;
    v3 += 2;
  }
  `eh vector constructor iterator'(this + 1024, 0x34u, 2, sub_416D10, sub_416D50);
  *(this + 1132) = 0;
  *((uint32_t *)this + 282) = &off_6C2B88;
  *((uint32_t *)this + 284) = 0;
  *(this + 1140) = 1;
  *(this + 1142) = 0;
  *(this + 1141) = 0;
  *((uint32_t *)this + 288) = 0;
  *((uint32_t *)this + 287) = 0;
  *((uint32_t *)this + 286) = 0;
  *(this + 1160) = 0;
  *((uint32_t *)this + 289) = &off_6C2B88;
  *((uint32_t *)this + 291) = 0;
  *(this + 1168) = 1;
  *(this + 1170) = 0;
  *(this + 1169) = 0;
  *((uint32_t *)this + 295) = 0;
  *((uint32_t *)this + 294) = 0;
  *((uint32_t *)this + 293) = 0;
  *(this + 1188) = 0;
  *((uint32_t *)this + 296) = &off_6C2B88;
  *((uint32_t *)this + 298) = 0;
  *(this + 1196) = 1;
  *(this + 1198) = 0;
  *(this + 1197) = 0;
  *((uint32_t *)this + 302) = 0;
  *((uint32_t *)this + 301) = 0;
  *((uint32_t *)this + 300) = 0;
  *(this + 1252) = 0;
  *((uint32_t *)this + 312) = &off_6C2B88;
  *((uint32_t *)this + 314) = 0;
  *(this + 1260) = 1;
  *(this + 1262) = 0;
  *(this + 1261) = 0;
  *((uint32_t *)this + 318) = 0;
  *((uint32_t *)this + 317) = 0;
  *((uint32_t *)this + 316) = 0;
  *(this + 1316) = 0;
  *((uint32_t *)this + 328) = &off_6C2B88;
  *((uint32_t *)this + 330) = 0;
  *(this + 1324) = 1;
  *(this + 1326) = 0;
  *(this + 1325) = 0;
  *((uint32_t *)this + 334) = 0;
  *((uint32_t *)this + 333) = 0;
  *((uint32_t *)this + 332) = 0;
  *(this + 1408) = 0;
  *((uint32_t *)this + 351) = &off_6C2B88;
  *((uint32_t *)this + 353) = 0;
  *(this + 1416) = 1;
  *(this + 1418) = 0;
  *(this + 1417) = 0;
  *((uint32_t *)this + 357) = 0;
  *((uint32_t *)this + 356) = 0;
  *((uint32_t *)this + 355) = 0;
  *(this + 1436) = 0;
  *((uint32_t *)this + 358) = &off_6C2B88;
  *((uint32_t *)this + 360) = 0;
  *(this + 1444) = 1;
  *(this + 1446) = 0;
  *(this + 1445) = 0;
  *((uint32_t *)this + 364) = 0;
  *((uint32_t *)this + 363) = 0;
  *((uint32_t *)this + 362) = 0;
  sub_4605F0(this);
  sub_469DD0((int)this, Block);
  return this;
}


// ------------------------------------------------------------
// 0x44DA60 sub_44DA60
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44DA60(uint32_t *this, void *Block)
{
  *this = &vftbl_CNRDWarRoomInterface;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *((uint8_t *)this + 76) = 0;
  *((uint8_t *)this + 77) = 0;
  *((uint8_t *)this + 78) = 0;
  *((uint8_t *)this + 79) = 0;
  *(this + 22) = 0;
  *(this + 23) = 6;
  *(this + 24) = 12;
  *(this + 25) = 0;
  *(this + 26) = 1600;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  *((uint8_t *)this + 128) = 0;
  *((uint8_t *)this + 129) = 0;
  *((uint8_t *)this + 130) = 0;
  *((uint8_t *)this + 131) = 0;
  *(this + 35) = 0;
  *(this + 36) = 6;
  *(this + 37) = 12;
  *(this + 38) = 0;
  *(this + 39) = 1600;
  *(this + 40) = 0;
  *(this + 41) = 0;
  *(this + 42) = 0;
  *(this + 43) = 0;
  *(this + 44) = 0;
  *((uint8_t *)this + 180) = 0;
  *((uint8_t *)this + 181) = 0;
  *((uint8_t *)this + 182) = 0;
  *((uint8_t *)this + 183) = 0;
  *(this + 48) = 0;
  *(this + 49) = 6;
  *(this + 50) = 12;
  *(this + 51) = 0;
  *(this + 52) = 1600;
  *(this + 53) = 0;
  *(this + 54) = 0;
  *(this + 55) = 0;
  *(this + 56) = 0;
  *(this + 57) = 0;
  sub_49C990(this);
  sub_49CFF0(Block);
  return this;
}



// ------------------------------------------------------------
// 0x44DBB0 sub_44DBB0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44DBB0(uint8_t *this, void *Block)
{
  *(uint32_t *)this = &vftbl_CNRDPVPResult;
  *(this + 16) = 0;
  *((uint32_t *)this + 3) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 5) = 0;
  *(this + 24) = 1;
  *(this + 26) = 0;
  *(this + 25) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 7) = 0;
  *(this + 44) = 0;
  *((uint32_t *)this + 10) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 12) = 0;
  *(this + 52) = 1;
  *(this + 54) = 0;
  *(this + 53) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 14) = 0;
  *(this + 76) = 0;
  *(this + 77) = 0;
  *(this + 78) = 0;
  *(this + 79) = 0;
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 23) = 6;
  *((uint32_t *)this + 24) = 12;
  *((uint32_t *)this + 25) = 0;
  *((uint32_t *)this + 26) = 1600;
  *((uint32_t *)this + 27) = 0;
  *((uint32_t *)this + 28) = 0;
  *((uint32_t *)this + 29) = 0;
  *((uint32_t *)this + 30) = 0;
  *((uint32_t *)this + 31) = 0;
  *((uint32_t *)this + 39) = 0;
  *((uint32_t *)this + 40) = 0;
  *((uint32_t *)this + 41) = 0;
  sub_54F530(this);
  sub_54F870(Block);
  return this;
}



// ------------------------------------------------------------
// 0x44DC90 sub_44DC90
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44DC90(uint32_t *this, int a2)
{
  *this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(a2, 0);
  *this = &vftbl_CNRDSkillBuyWindow;
  `eh vector constructor iterator'(this + 16, 0x10u, 5, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  `eh vector constructor iterator'(this + 39, 0x34u, 3, sub_416D10, sub_416D50);
  sub_5502A0(this);
  sub_550D20((int)this);
  return this;
}



// ------------------------------------------------------------
// 0x44DD30 CNRDSkillBuyWindow__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDSkillBuyWindow__vmt4(void *Block, char a2)
{
  sub_44DD60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44DD60 sub_44DD60
// ------------------------------------------------------------
void /*thiscall*/ sub_44DD60(uint32_t *this)
{
  *this = &vftbl_CNRDSkillBuyWindow;
  sub_550300();
  `eh vector destructor iterator'(this + 39, 0x34u, 3, sub_416D50);
  `eh vector destructor iterator'(this + 16, 0x10u, 5, (void (/*thiscall*/ *)(void *))sub_5E5260);
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44DDF0 sub_44DDF0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44DDF0(uint8_t *this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(a2, 0);
  *(uint32_t *)this = &vftbl_CNRDQuestInfoWindow;
  *(this + 36) = 0;
  *((uint32_t *)this + 8) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 10) = 0;
  *(this + 44) = 1;
  *(this + 46) = 0;
  *(this + 45) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 12) = 0;
  *(this + 128) = 0;
  *(this + 129) = 0;
  *(this + 130) = 0;
  *(this + 131) = 0;
  *((uint32_t *)this + 35) = 0;
  *((uint32_t *)this + 36) = 6;
  *((uint32_t *)this + 37) = 12;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 39) = 1600;
  *((uint32_t *)this + 40) = 0;
  *((uint32_t *)this + 41) = 0;
  *((uint32_t *)this + 42) = 0;
  *((uint32_t *)this + 43) = 0;
  *((uint32_t *)this + 44) = 0;
  *((uint32_t *)this + 47) = 0;
  *((uint32_t *)this + 48) = 0;
  *((uint32_t *)this + 49) = 0;
  sub_551730(this);
  sub_552070(this);
  return this;
}



// ------------------------------------------------------------
// 0x44DEF0 CNRDQuestInfoWindow__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDQuestInfoWindow__vmt4(void *Block, char a2)
{
  sub_44DF20();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44DF20 sub_44DF20
// ------------------------------------------------------------
void /*thiscall*/ sub_44DF20(void *this)
{
  *(uint32_t *)this = &vftbl_CNRDQuestInfoWindow;
  sub_551A60();
  sub_44CA70((int *)this + 46);
  if ( *((uint32_t *)this + 43) != 0 )
  {
    DeleteObject(*((HGDIOBJ *)this + 43));
    *((uint32_t *)this + 43) = 0;
  }
  *((uint8_t *)this + 128) = 0;
  *((uint8_t *)this + 129) = 0;
  *((uint8_t *)this + 130) = 0;
  *((uint8_t *)this + 131) = 0;
  *((uint32_t *)this + 35) = 0;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 39) = 0;
  *((uint32_t *)this + 40) = 0;
  *((uint32_t *)this + 41) = 0;
  *((uint32_t *)this + 42) = 0;
  *((uint32_t *)this + 43) = 0;
  *((uint32_t *)this + 44) = 0;
  *((uint32_t *)this + 8) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 36) = 0;
  *(uint32_t *)this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44E000 sub_44E000
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44E000(uint32_t *this, void *Block)
{
  *this = &vftbl_CNRDPopupMenu;
  *(this + 11) = 15;
  *(this + 10) = 0;
  *((uint8_t *)this + 24) = 0;
  *(this + 37) = 0;
  *(this + 38) = 0;
  *(this + 39) = 0;
  *((uint8_t *)this + 164) = 0;
  *((uint8_t *)this + 165) = 0;
  *((uint8_t *)this + 166) = 0;
  *((uint8_t *)this + 167) = 0;
  *(this + 44) = 0;
  *(this + 45) = 6;
  *(this + 46) = 12;
  *(this + 47) = 0;
  *(this + 48) = 1600;
  *(this + 49) = 0;
  *(this + 50) = 0;
  *(this + 51) = 0;
  *(this + 52) = 0;
  *(this + 53) = 0;
  sub_525660();
  sub_526440(Block);
  return this;
}



// ------------------------------------------------------------
// 0x44E0D0 sub_44E0D0
// ------------------------------------------------------------
char */*thiscall*/ sub_44E0D0(char *this, int a2, char a3)
{
  *(uint32_t *)this = &vftbl_KMessenger;
  sub_498AB0();
  *(uint32_t *)this = &vftbl_CNRDObject;
  *(this + 12) = 0;
  *((uint32_t *)this + 2) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 4) = 0;
  *(this + 20) = 1;
  *(this + 22) = 0;
  *(this + 21) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 6) = 0;
  *(this + 40) = 0;
  *((uint32_t *)this + 9) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 11) = 0;
  *(this + 48) = 1;
  *(this + 50) = 0;
  *(this + 49) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 13) = 0;
  *(this + 68) = 0;
  *((uint32_t *)this + 16) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 18) = 0;
  *(this + 76) = 1;
  *(this + 78) = 0;
  *(this + 77) = 0;
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 25) = 0;
  *((uint32_t *)this + 26) = 0;
  *((uint32_t *)this + 27) = 1;
  *((uint32_t *)this + 32) = sub_433A60(this + 124);
  *((uint32_t *)this + 33) = 0;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 44) = 0;
  *((uint32_t *)this + 45) = 0;
  *((uint32_t *)this + 46) = 0;
  *((uint32_t *)this + 47) = 0;
  *((uint32_t *)this + 48) = 0;
  *((uint32_t *)this + 49) = 0;
  sub_498B70((int)this);
  sub_499A20(a2, a3);
  return this;
}



// ------------------------------------------------------------
// 0x44E1F0 sub_44E1F0
// ------------------------------------------------------------
char */*thiscall*/ sub_44E1F0(char *this, int a2, char a3)
{
  sub_44E0D0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNRDPooledObject;
  return this;
}



// ------------------------------------------------------------
// 0x44E220 CNRDPooledObject__vmt0
// ------------------------------------------------------------
void **/*thiscall*/ CNRDPooledObject__vmt0(void **this, char a2)
{
  sub_44E250(this);
  if ( (a2 & 1) != 0 )
    sub_657740(this, 284);
  return this;
}



// ------------------------------------------------------------
// 0x44E260 sub_44E260
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44E260(uint32_t *this)
{
  *this = &vftbl_CNRDCharacterTalkBox;
  *(this + 9) = 15;
  *(this + 8) = 0;
  *((uint8_t *)this + 16) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *((uint8_t *)this + 64) = 0;
  *(this + 15) = &vftbl_nengine__CNTimer;
  *(this + 17) = 0;
  *((uint8_t *)this + 72) = 1;
  *((uint8_t *)this + 74) = 0;
  *((uint8_t *)this + 73) = 0;
  *(this + 21) = 0;
  *(this + 20) = 0;
  *(this + 19) = 0;
  sub_49B520();
  sub_49B150(this);
  return this;
}



// ------------------------------------------------------------
// 0x44E2F0 sub_44E2F0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_44E2F0(int *this, int *a2)
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
    return sub_44CFA0((int)this, *(this + 2), 1u, a2);
  v4 = (int *)*(this + 2);
  *v4 = *a2;
  result = (unsigned int)(v4 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x44E340 sub_44E340
// ------------------------------------------------------------
void /*thiscall*/ sub_44E340(int this, int a2)
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
    sub_44D240(this, *(char **)(this + 8), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x44E3B0 sub_44E3B0
// ------------------------------------------------------------
void /*stdcall*/ sub_44E3B0(char *a1, char *a2)
{
  char *i; // esi

  for ( i = a1; i != a2; i += 28 )
    sub_501490(i);
}



// ------------------------------------------------------------
// 0x44E3E0 sub_44E3E0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_44E3E0(uint32_t *this, int a2)
{
  uint32_t *v2; // ecx
  int v3; // esi
  unsigned int v4; // edx
  int *v5; // eax
  unsigned int result; // eax

  v2 = this + 601;
  v3 = v2[1];
  if ( v3 != 0 )
    v4 = (v2[2] - v3) >> 2;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (v2[3] - v3) >> 2 )
    return sub_44CFA0((int)v2, v2[2], 1u, &a2);
  v5 = (int *)v2[2];
  *v5 = a2;
  result = (unsigned int)(v5 + 1);
  v2[2] = result;
  return result;
}



// ------------------------------------------------------------
// 0x44E440 sub_44E440
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44E440(uint8_t *this, int a2)
{
  uint32_t *v3; // eax
  uint32_t *v4; // eax

  *(uint32_t *)this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(a2, 1);
  *(uint32_t *)this = &vftbl_CNRDQuestListWindow;
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
  *((uint32_t *)this + 42) = 0;
  *((uint32_t *)this + 43) = 0;
  *((uint32_t *)this + 44) = 0;
  v3 = sub_433AC0();
  *((uint32_t *)this + 48) = v3;
  *((uint8_t *)v3 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)this + 48) + 4) = *((uint32_t *)this + 48);
  **((uint32_t **)this + 48) = *((uint32_t *)this + 48);
  *(uint32_t *)(*((uint32_t *)this + 48) + 8) = *((uint32_t *)this + 48);
  *((uint32_t *)this + 49) = 0;
  v4 = sub_433AC0();
  *((uint32_t *)this + 51) = v4;
  *((uint8_t *)v4 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)this + 51) + 4) = *((uint32_t *)this + 51);
  **((uint32_t **)this + 51) = *((uint32_t *)this + 51);
  *(uint32_t *)(*((uint32_t *)this + 51) + 8) = *((uint32_t *)this + 51);
  *((uint32_t *)this + 52) = 0;
  sub_553040(this);
  sub_553B70(this);
  return this;
}



// ------------------------------------------------------------
// 0x44E590 CNRDQuestListWindow__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDQuestListWindow__vmt4(void *Block, char a2)
{
  sub_44E5C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44E5C0 sub_44E5C0
// ------------------------------------------------------------
void /*thiscall*/ sub_44E5C0(HGDIOBJ *this)
{
  int v2; // [esp-8h] [ebp-28h]
  int v3; // [esp-8h] [ebp-28h]
  int *v4; // [esp-4h] [ebp-24h]
  int *v5; // [esp-4h] [ebp-24h]
  char v6[4]; // [esp+Ch] [ebp-14h] BYREF
  HGDIOBJ *v7; // [esp+10h] [ebp-10h]
  int v8; // [esp+1Ch] [ebp-4h]

  v7 = this;
  *this = &vftbl_CNRDQuestListWindow;
  v8 = 5;
  sub_553080();
  v4 = (int *)*(this + 51);
  v2 = *v4;
  LOBYTE(v8) = 4;
  sub_41D980(v6, v2, v4);
  j__free(*(this + 51));
  *(this + 51) = nullptr;
  *(this + 52) = nullptr;
  v5 = (int *)*(this + 48);
  v3 = *v5;
  LOBYTE(v8) = 3;
  sub_41D980(v6, v3, v5);
  j__free(*(this + 48));
  *(this + 48) = nullptr;
  *(this + 49) = nullptr;
  if ( *(this + 42) != nullptr )
    j__free(*(this + 42));
  *(this + 42) = nullptr;
  *(this + 43) = nullptr;
  *(this + 44) = nullptr;
  if ( *(this + 38) != nullptr )
  {
    DeleteObject(*(this + 38));
    *(this + 38) = nullptr;
  }
  *((uint8_t *)this + 108) = 0;
  *((uint8_t *)this + 109) = 0;
  *((uint8_t *)this + 110) = 0;
  *((uint8_t *)this + 111) = 0;
  *(this + 30) = nullptr;
  *(this + 31) = nullptr;
  *(this + 32) = nullptr;
  *(this + 33) = nullptr;
  *(this + 34) = nullptr;
  *(this + 35) = nullptr;
  *(this + 36) = nullptr;
  *(this + 37) = nullptr;
  *(this + 38) = nullptr;
  *(this + 39) = nullptr;
  if ( *(this + 25) != nullptr )
  {
    DeleteObject(*(this + 25));
    *(this + 25) = nullptr;
  }
  *((uint8_t *)this + 56) = 0;
  *((uint8_t *)this + 57) = 0;
  *((uint8_t *)this + 58) = 0;
  *((uint8_t *)this + 59) = 0;
  *(this + 17) = nullptr;
  *(this + 18) = nullptr;
  *(this + 19) = nullptr;
  *(this + 20) = nullptr;
  *(this + 21) = nullptr;
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *(this + 24) = nullptr;
  *(this + 25) = nullptr;
  *(this + 26) = nullptr;
  v8 = -1;
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44E740 sub_44E740
// ------------------------------------------------------------
int /*thiscall*/ sub_44E740(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_44D180((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x44E780 sub_44E780
// ------------------------------------------------------------
void /*thiscall*/ sub_44E780(uint32_t *this, int a2)
{
  int v2; // esi
  int v4; // ebx
  uint32_t *v5; // eax
  uint32_t *v6; // edi
  uint32_t *v7; // ecx
  char *v8; // ecx
  char *v9; // eax
  int v10; // eax
  int v11[2]; // [esp+8h] [ebp-8h] BYREF

  v2 = a2;
  v11[1] = (int)this;
  if ( a2 != 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 40))(a2);
    v5 = (uint32_t *)*(this + 4 * v4 + 34);
    v6 = this + 4 * v4;
    v7 = (uint32_t *)v6[35];
    if ( v5 != v7 )
    {
      do
      {
        if ( *v5 == v2 )
          break;
        ++v5;
      }
      while ( v5 != v7 );
      if ( v5 != v7 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 16))(v2);
        v8 = (char *)v6[35];
        v9 = (char *)v6[34];
        if ( v9 != v8 )
        {
          do
          {
            if ( *(uint32_t *)v9 == v2 )
              break;
            v9 += 4;
          }
          while ( v9 != v8 );
          if ( v9 != v8 )
            sub_44C0F0(v6 + 33, v11, v9);
        }
        sub_44E2F0(v6 + 317, &a2);
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 36))(v2);
        sub_69A580(v10);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x44E850 sub_44E850
// ------------------------------------------------------------
char /*thiscall*/ sub_44E850(uint32_t *this, int a2)
{
  int v3; // eax
  uint32_t *v4; // ecx
  char *v5; // edi
  uint32_t *j; // esi
  int i; // esi

  if ( a2 == 71 )
  {
    for ( i = 0; i < 71; ++i )
      LOBYTE(v3) = sub_44E850(i);
  }
  else
  {
    LOBYTE(v3) = 16 * a2;
    v4 = (uint32_t *)*(this + 4 * a2 + 34);
    v5 = (char *)(this + 4 * a2);
    if ( v4 != nullptr )
    {
      v3 = (*((uint32_t *)v5 + 35) - (int)v4) >> 2;
      if ( v3 != 0 )
      {
        LOBYTE(v3) = byte_9D3BE4;
        if ( byte_9D3BE4 == 0 )
        {
          v3 = *((uint32_t *)v5 + 35);
          for ( j = v4; j != (uint32_t *)v3; ++j )
          {
            sub_44E3E0(*j);
            v3 = *((uint32_t *)v5 + 35);
          }
        }
      }
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x44E8D0 sub_44E8D0
// ------------------------------------------------------------
int /*thiscall*/ sub_44E8D0(char *this, void *Block, int a3, int a4)
{
  void *v4; // edx
  char *v6; // esi
  int v7; // ecx
  unsigned int v8; // eax
  int v9; // edi
  int *v10; // ecx
  uint32_t *v11; // ecx
  uint32_t *v12; // eax
  int v14; // eax
  int v15; // [esp+10h] [ebp-4h] BYREF

  v4 = Block;
  v6 = this + 16 * (uint32_t)Block;
  v7 = *((uint32_t *)v6 + 34);
  if ( v7 != 0 )
    v8 = (*((uint32_t *)v6 + 35) - v7) >> 2;
  else
    v8 = 0;
  if ( dword_724A98[(uint32_t)Block] > v8 )
  {
    v10 = *((int **)v6 + 318);
    if ( v10 == nullptr || (*((uint32_t *)v6 + 319) - (int)v10) >> 2 == 0 )
      goto LABEL_15;
    v9 = *v10;
    v15 = *v10;
  }
  else
  {
    v15 = **((uint32_t **)v6 + 34);
    v9 = v15;
    sub_44E780(v15);
    v4 = Block;
  }
  if ( v9 == 0 )
  {
LABEL_15:
    v9 = sub_55B070(v4, (int)this);
    v15 = v9;
    goto LABEL_16;
  }
  v11 = *((uint32_t **)v6 + 319);
  v12 = *((uint32_t **)v6 + 318);
  if ( v12 != v11 )
  {
    do
    {
      if ( *v12 == v9 )
        break;
      ++v12;
    }
    while ( v12 != v11 );
    if ( v12 != v11 )
    {
      memcpy_0(v12, v12 + 1, 4 * ((*((uint32_t *)v6 + 319) - (int)(v12 + 1)) >> 2));
      *((uint32_t *)v6 + 319) -= 4;
    }
  }
LABEL_16:
  if ( v9 == 0 )
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v9 + 12))(v9, a3, a4) == 0 )
  {
    sub_44E2F0(&v15);
    return 0;
  }
  sub_44E2F0(&v15);
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 36))(v9);
  sub_69A840(v14);
  return v9;
}



// ------------------------------------------------------------
// 0x44EA20 sub_44EA20
// ------------------------------------------------------------
// 模块切换收尾 sub_44EA20(from, to) —— docs/13 §3 定案调用：
// sub_41CC80 迁移矩阵执行后的资源收尾（窗口/声音/上下文按 from/to 清理）
int /*thiscall*/ sub_44EA20(int this, int a2, int a3)
{
  int v3; // ebx
  int i; // edi
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int j; // edi
  int v13; // ecx
  uint32_t *v14; // edi
  int v15; // ecx
  uint32_t *v16; // edi
  int v17; // ecx
  uint32_t *v18; // edi
  int v19; // ecx
  uint32_t *v20; // edi
  int v21; // ecx
  uint32_t *v22; // edi
  int v23; // eax
  int v24; // edi
  int v25; // eax
  int v26; // edi
  int k; // ebx
  int v28; // eax
  int v29; // eax
  int v30; // ecx
  int *v31; // ebx
  int v32; // ecx
  unsigned int v33; // edx
  int *v34; // eax
  int result; // eax
  int v36; // [esp+Ch] [ebp-4h] BYREF

  v3 = a3;
  if ( dword_9B8880 != 0 )
    sub_5620B0(a3);
  if ( a3 == 5 )
  {
    for ( i = 0; i < 71; ++i )
      sub_44E850((uint32_t *)this, i);
  }
  else if ( a3 != 0 )
  {
    *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 16) + 8) + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 28) + 92) + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 28) + 120) + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 28) + 136) + 17) = 1;
    sub_44E850(dword_8F8528, 30);
LABEL_7:
    if ( a3 != 0 )
    {
      if ( a3 == 2 || a3 == 4 || a3 == 6 )
      {
        v13 = *(uint32_t *)(this + 600);
        if ( v13 != 0 && (*(uint32_t *)(this + 604) - v13) >> 2 != 0 && byte_9D3BE4 == 0 )
        {
          v14 = *(uint32_t **)(this + 600);
          if ( v13 != *(uint32_t *)(this + 604) )
          {
            do
              sub_44E3E0(*v14++);
            while ( v14 != *(uint32_t **)(this + 604) );
          }
        }
        v15 = *(uint32_t *)(this + 632);
        if ( v15 != 0 && (*(uint32_t *)(this + 636) - v15) >> 2 != 0 && byte_9D3BE4 == 0 )
        {
          v16 = *(uint32_t **)(this + 632);
          if ( v15 != *(uint32_t *)(this + 636) )
          {
            do
              sub_44E3E0(*v16++);
            while ( v16 != *(uint32_t **)(this + 636) );
          }
        }
        v17 = *(uint32_t *)(this + 696);
        if ( v17 != 0 && (*(uint32_t *)(this + 700) - v17) >> 2 != 0 && byte_9D3BE4 == 0 )
        {
          v18 = *(uint32_t **)(this + 696);
          if ( v17 != *(uint32_t *)(this + 700) )
          {
            do
              sub_44E3E0(*v18++);
            while ( v18 != *(uint32_t **)(this + 700) );
          }
        }
        v19 = *(uint32_t *)(this + 136);
        if ( v19 != 0 && (*(uint32_t *)(this + 140) - v19) >> 2 != 0 && byte_9D3BE4 == 0 )
        {
          v20 = *(uint32_t **)(this + 136);
          if ( v19 != *(uint32_t *)(this + 140) )
          {
            do
              sub_44E3E0(*v20++);
            while ( v20 != *(uint32_t **)(this + 140) );
          }
        }
        v21 = *(uint32_t *)(this + 840);
        if ( v21 != 0 && (*(uint32_t *)(this + 844) - v21) >> 2 != 0 && byte_9D3BE4 == 0 )
        {
          v22 = *(uint32_t **)(this + 840);
          if ( v21 != *(uint32_t *)(this + 844) )
          {
            do
              sub_44E3E0(*v22++);
            while ( v22 != *(uint32_t **)(this + 844) );
          }
        }
        if ( *(uint32_t *)(this + 108) == 7 && *(uint32_t *)(*(uint32_t *)(this + 84) + 16) == 1 )
        {
          v23 = *(uint32_t *)(this + 108);
          if ( v23 != 12 )
          {
            v24 = *(uint32_t *)(this + 4 * v23 + 56);
            v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v24 + 48))(v24);
            sub_69A580(v25);
            *(uint32_t *)(this + 108) = 12;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v24 + 16))(v24);
          }
          v3 = a3;
        }
        sub_560610(0);
        sub_5403D0(0);
        sub_49A9A0(*(uint32_t *)(this + 2536));
      }
      if ( v3 == 1 )
      {
        sub_49BDB0(0);
        sub_49E050(0);
        sub_4772A0(0);
        sub_45A420(0);
        sub_54F540(0);
      }
    }
    else
    {
      v6 = *(uint32_t *)(this + 104);
      if ( v6 != 12 )
      {
        v7 = *(uint32_t *)(this + 4 * v6 + 56);
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 48))(v7);
        sub_69A580(v8);
        *(uint32_t *)(this + 104) = 12;
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 16))(v7);
      }
      v9 = *(uint32_t *)(this + 108);
      if ( v9 != 12 )
      {
        v10 = *(uint32_t *)(this + 4 * v9 + 56);
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 48))(v10);
        sub_69A580(v11);
        *(uint32_t *)(this + 108) = 12;
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 16))(v10);
      }
      for ( j = 0; j < 71; ++j )
      {
        if ( j != 27 && j != 36 && j != 43 )
          sub_44E850((uint32_t *)this, j);
      }
      sub_5465E0(*(uint32_t *)(this + 44));
    }
    sub_52C7F0(a3 == 4);
    sub_49CD70(a3 == 6);
    sub_461470(a3 == 6);
    if ( a3 == 0 || a3 == 2 )
      sub_4BF300(0, 0);
    else
      sub_4BF300(0, 1);
    v26 = this + 20;
    for ( k = 2; k != 0; --k )
    {
      sub_69A580(*(uint32_t *)(*(uint32_t *)(this + 28) + 12));
      sub_69A580(*(uint32_t *)(*(uint32_t *)(this + 28) + 92));
      v26 += 4;
    }
    switch ( a3 )
    {
      case 1:
        sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 12));
        sub_43BC60(0);
        sub_43BB10(0, 1);
        if ( sub_429830((uint16_t)word_77F804) == 0
          || *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) == 0 )
        {
          sub_43BB10(1, 0);
          sub_43BA20(0);
          sub_43B880(0);
        }
        sub_43BB30(*(uint32_t *)(this + 28));
        break;
      case 2:
        sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 12));
        v28 = *(uint32_t *)(this + 28);
        if ( *(uint8_t *)(v28 + 1474) != 0 )
          v29 = *(uint32_t *)(v28 + 20);
        else
          v29 = *(uint32_t *)(v28 + 16);
        *(uint8_t *)(v29 + 16) = 0;
        sub_43BC60(1);
        sub_43BB10(0, 0);
        sub_43BB10(1, 1);
        *(uint32_t *)(this + 2484) = 0;
        break;
      case 3:
      case 4:
      case 6:
        sub_69A840(*(uint32_t *)(*(uint32_t *)(this + 28) + 92));
        sub_43BB30(*(uint32_t *)(this + 28));
        v30 = *(uint32_t *)(this + 168);
        if ( v30 != 0 && (*(uint32_t *)(this + 172) - v30) >> 2 != 0 && byte_9D3BE4 == 0 )
        {
          v31 = *(int **)(this + 168);
          if ( v30 != *(uint32_t *)(this + 172) )
          {
            do
            {
              v32 = *(uint32_t *)(this + 2408);
              v36 = *v31;
              if ( v32 != 0 )
                v33 = (*(uint32_t *)(this + 2412) - v32) >> 2;
              else
                v33 = 0;
              if ( v32 != 0 && v33 < (*(uint32_t *)(this + 2416) - v32) >> 2 )
              {
                v34 = *(int **)(this + 2412);
                *v34 = v36;
                *(uint32_t *)(this + 2412) = v34 + 1;
              }
              else
              {
                sub_44CFA0(*(void **)(this + 2412), 1, (int)&v36);
              }
              ++v31;
            }
            while ( v31 != *(int **)(this + 172) );
          }
        }
        break;
      default:
        break;
    }
    sub_545860(a2, a3);
    sub_5466C0(a2, a3);
    if ( a2 == 3 && a3 == 1 && word_8F7C10 == word_8F7C14 )
      sub_546170(*(uint32_t *)(this + 44));
    sub_4684F0(*(uint32_t *)(this + 16), nullptr);
    sub_525740(*(uint32_t *)(this + 48));
    result = sub_540960(*(uint32_t *)(this + 116));
    if ( a2 == 3 )
    {
      if ( a3 != 1 )
        return result;
      return sub_461580(0);
    }
    if ( a2 == 6 && a3 == 1 )
      return sub_461580(0);
    return result;
  }
  *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 16) + 8) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 28) + 92) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 0;
  sub_43B920(0);
  *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 28) + 136) + 17) = 0;
  sub_49E050(0);
  sub_4772A0(0);
  sub_45A420(0);
  sub_54F540(0);
  sub_560610(0);
  sub_5403D0(0);
  sub_49A9A0(*(uint32_t *)(this + 2536));
  goto LABEL_7;
}


// ------------------------------------------------------------
// 0x44F080 sub_44F080
// ------------------------------------------------------------
int /*thiscall*/ sub_44F080(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int v9; // ecx

  v2 = *(this + 26);
  if ( v2 == 6 || v2 == 3 || v2 == 9 || v2 == 11 || v2 == 10 )
  {
    v3 = *(this + 26);
    if ( v3 != 12 )
    {
      v4 = *(this + v3 + 14);
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 48))(v4);
      sub_69A580(v5);
      *(this + 26) = 12;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 16))(v4);
    }
  }
  if ( *(this + 27) == 7 && *(uint32_t *)(*(this + 21) + 16) == 1 )
  {
    v6 = *(this + 27);
    if ( v6 != 12 )
    {
      v7 = *(this + v6 + 14);
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 48))(v7);
      sub_69A580(v8);
      *(this + 27) = 12;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 16))(v7);
    }
  }
  sub_525740(*(this + 12));
  sub_44E850(this, 17);
  sub_44E850(this, 46);
  sub_44E850(this, 15);
  sub_44E850(this, 16);
  sub_44E850(this, 13);
  sub_44E850(this, 14);
  sub_44E850(this, 19);
  sub_44E850(this, 20);
  sub_44E850(this, 22);
  sub_44E850(this, 23);
  sub_44E850(this, 37);
  v9 = *(this + 11);
  *(this + 626) = 0;
  return sub_546730(v9);
}



// ------------------------------------------------------------
// 0x44F190 sub_44F190
// ------------------------------------------------------------
void /*thiscall*/ sub_44F190(int this, unsigned int a2, char a3)
{
  int v4; // ecx
  int v5; // edx
  int v6; // edi
  int v7; // edi
  int v8; // eax
  int v9; // [esp-Ch] [ebp-34h]
  uint8_t v10[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  int v12; // [esp+Ch] [ebp-1Ch]
  int v13; // [esp+10h] [ebp-18h]
  uint32_t v14[5]; // [esp+14h] [ebp-14h] BYREF

  v4 = *(uint32_t *)(this + 80);
  v5 = *(uint32_t *)(v4 + 96);
  if ( v5 != 0 && a2 < (*(uint32_t *)(v4 + 100) - v5) >> 2 )
  {
    v6 = *(uint32_t *)(v5 + 4 * a2);
    if ( v6 != 0 )
    {
      Block = nullptr;
      v12 = 0;
      v13 = 0;
      v14[4] = 0;
      v14[0] = v6;
      v14[1] = 1;
      sub_44E340((int)v10, (int)v14);
      if ( (uint8_t)sub_5634F0(v10, 1) != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 20))(v6, 1) != 0
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, 8) != 0 )
        {
          v7 = *(uint32_t *)(this + 2504);
          *(uint32_t *)(this + 2504) = 0;
          sub_540DE0(2, 7, a2, 7, 0, v7 == 4, a3 != 0);
        }
        else if ( a3 != 0 )
        {
          byte_9B8889 = *(uint32_t *)(this + 2504) == 4;
          *(uint32_t *)(this + 2504) = 0;
          sub_44E8D0((char *)this, (void *)0x13, v6, 1);
        }
        else
        {
          v9 = dword_8F84B0;
          v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 16))(v6);
          sub_563410(*(uint32_t *)(v8 + 4), v9);
        }
      }
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// ------------------------------------------------------------
// 0x44F2E0 sub_44F2E0
// ------------------------------------------------------------
int /*thiscall*/ sub_44F2E0(int this, int a2, char a3)
{
  char *v4; // eax
  int result; // eax
  int v6; // edx
  BOOL v7; // ecx

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 72))(a2) == 0 )
  {
    v4 = sub_422E70(402);
    return sub_44E8D0((char *)this, (void *)0x1B, (int)v4, 0);
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 20))(a2, 2) != 0 )
    goto LABEL_11;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 20))(a2, 1);
  if ( (uint8_t)result == 0 )
    return result;
  if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 44))(a2) <= 1 )
  {
LABEL_11:
    if ( a3 != 0 )
    {
      byte_9B888A = *(uint32_t *)(this + 2504) == 5;
      *(uint32_t *)(this + 2504) = 0;
      return sub_44E8D0((char *)this, (void *)0x14, a2, 1);
    }
    else
    {
      return sub_563E90(a2, 1, this);
    }
  }
  else
  {
    v6 = *((uint32_t *)dword_8F852C + 2);
    for ( result = 0; result < v6; ++result )
    {
      if ( *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * result) == a2 )
        break;
    }
    if ( result != v6 )
    {
      v7 = *(uint32_t *)(this + 2504) == 5;
      *(uint32_t *)(this + 2504) = 0;
      return sub_540DE0(3, 0, result, 7, 0, v7, a3 != 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x44F400 sub_44F400
// ------------------------------------------------------------
int /*thiscall*/ sub_44F400(int this, int a2, char a3)
{
  int v3; // esi
  char *v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // eax
  unsigned int v10; // edi
  char *v12; // eax
  bool v13; // zf
  char *v14; // [esp-8h] [ebp-58h]
  unsigned int v15; // [esp-4h] [ebp-54h]
  char Buffer[64]; // [esp+Ch] [ebp-44h] BYREF
  int v17; // [esp+4Ch] [ebp-4h]

  v3 = a2;
  v17 = dword_796E50;
  if ( a2 != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 20))(a2, 2) == 0 )
    {
      v5 = sub_422E70(403);
LABEL_10:
      v14 = v5;
      return sub_44E8D0((char *)this, (void *)0x1B, (int)v14, 0);
    }
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 172))(v3);
    if ( sub_41A5E0(v6 + 18) == 0 )
    {
      v5 = sub_422E70(404);
      goto LABEL_10;
    }
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 188))(v3);
    v8 = sub_41A5E0(v7 + 32);
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 172))(v3);
    if ( v8 >= sub_41A5E0(v9 + 18) )
    {
      v5 = sub_422E70(405);
      goto LABEL_10;
    }
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 180))(v3);
  }
  else
  {
    a2 = 0;
    v10 = sub_5640D0(&a2);
    if ( a2 == 0 )
    {
      v5 = sub_422E70(406);
      goto LABEL_10;
    }
  }
  if ( v10 > (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) )
  {
    v15 = v10
        - (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3));
    v12 = sub_422E70(407);
    sprintf(Buffer, v12, v15);
    v14 = Buffer;
    return sub_44E8D0((char *)this, (void *)0x1B, (int)v14, 0);
  }
  if ( a3 == 0 )
    return sub_5641E0(v3, this);
  if ( v3 == 0 || (v13 = *(uint32_t *)(this + 2504) == 6, byte_9B888B = 1, !v13) )
    byte_9B888B = 0;
  *(uint32_t *)(this + 2504) = 0;
  return sub_44E8D0((char *)this, (void *)0x16, v3, 0);
}



// ------------------------------------------------------------
// 0x44F580 sub_44F580
// ------------------------------------------------------------
char /*thiscall*/ sub_44F580(int this, int a2, char a3)
{
  char *v4; // eax
  char result; // al
  int v6; // eax
  int v7; // ebx
  char *v8; // eax
  char *v9; // eax
  int v10; // ebx

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 20))(a2, 2) == 0 )
  {
    v4 = sub_422E70(408);
    return sub_44E8D0((char *)this, (void *)0x1B, (int)v4, 0);
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 64))(a2) == 0 )
  {
    v4 = sub_422E70(409);
    return sub_44E8D0((char *)this, (void *)0x1B, (int)v4, 0);
  }
  v6 = sub_47DC90(dword_791ED8);
  v7 = sub_41A5E0(v6 + 510);
  if ( v7 != 0 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 16))(a2) + 24) <= 10 * v7 )
    {
      result = a3;
      if ( a3 != 0 )
      {
        v10 = *(uint32_t *)(this + 2504);
        *(uint32_t *)(this + 2504) = 0;
        return sub_44E8D0((char *)this, (void *)0x17, a2, v10 == 7);
      }
    }
    else
    {
      v9 = sub_422E70(411);
      return sub_44E8D0((char *)this, (void *)0x1B, (int)v9, 0);
    }
  }
  else
  {
    v8 = sub_422E70(410);
    return sub_44E8D0((char *)this, (void *)0x1B, (int)v8, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x44F670 sub_44F670
// ------------------------------------------------------------
char /*thiscall*/ sub_44F670(int this, int a2, char a3)
{
  char *v4; // eax
  char result; // al
  char *v6; // eax
  char *v7; // eax
  BOOL v8; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 20))(a2, 2) != 0 )
  {
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 172))(a2) == 9 )
    {
      v6 = sub_422E70(1664);
      return sub_44E8D0((char *)this, (void *)0x1B, (int)v6, 0);
    }
    else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 68))(a2) != 0 )
    {
      result = a3;
      if ( a3 != 0 )
      {
        v8 = *(uint32_t *)(this + 2504) == 18;
        *(uint32_t *)(this + 2504) = 0;
        return sub_44E8D0((char *)this, (void *)0x3B, a2, v8);
      }
    }
    else
    {
      v7 = sub_422E70(1653);
      return sub_44E8D0((char *)this, (void *)0x1B, (int)v7, 0);
    }
  }
  else
  {
    v4 = sub_422E70(1652);
    return sub_44E8D0((char *)this, (void *)0x1B, (int)v4, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x44F730 sub_44F730
// ------------------------------------------------------------
int /*thiscall*/ sub_44F730(int this)
{
  char *v2; // esi
  int result; // eax
  char *i; // edi

  v2 = *(char **)(this + 4);
  result = 0;
  if ( v2 != nullptr )
  {
    for ( i = *(char **)(this + 8); v2 != i; v2 += 28 )
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
// 0x44F770 sub_44F770
// ------------------------------------------------------------
int /*thiscall*/ sub_44F770(int this)
{
  char *v2; // esi
  int result; // eax
  char *i; // edi

  v2 = *(char **)(this + 4);
  result = 0;
  if ( v2 != nullptr )
  {
    for ( i = *(char **)(this + 8); v2 != i; v2 += 84 )
      sub_44C2A0(v2);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x44F7B0 sub_44F7B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44F7B0(uint32_t *this, int a2)
{
  uint32_t *v3; // eax

  *this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(a2, 0);
  *this = &vftbl_CNRDItemShopWindow;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *((uint8_t *)this + 116) = 0;
  *(this + 28) = &vftbl_nengine__CNTimer;
  *(this + 30) = 0;
  *((uint8_t *)this + 124) = 1;
  *((uint8_t *)this + 126) = 0;
  *((uint8_t *)this + 125) = 0;
  *(this + 34) = 0;
  *(this + 33) = 0;
  *(this + 32) = 0;
  v3 = sub_433AC0();
  *(this + 36) = v3;
  *((uint8_t *)v3 + 21) = 1;
  *(uint32_t *)(*(this + 36) + 4) = *(this + 36);
  *(uint32_t *)*(this + 36) = *(this + 36);
  *(uint32_t *)(*(this + 36) + 8) = *(this + 36);
  *(this + 37) = 0;
  *((uint8_t *)this + 156) = 0;
  *(this + 38) = &vftbl_nengine__CNTimer;
  *(this + 40) = 0;
  *((uint8_t *)this + 164) = 1;
  *((uint8_t *)this + 166) = 0;
  *((uint8_t *)this + 165) = 0;
  *(this + 44) = 0;
  *(this + 43) = 0;
  *(this + 42) = 0;
  sub_564650(this);
  sub_5654D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x44F8C0 CNRDItemShopWindow__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemShopWindow__vmt4(void *Block, char a2)
{
  sub_44F8F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44F8F0 sub_44F8F0
// ------------------------------------------------------------
void /*thiscall*/ sub_44F8F0(int this)
{
  int v2; // [esp-8h] [ebp-28h]
  int *v3; // [esp-4h] [ebp-24h]
  int v4[2]; // [esp+Ch] [ebp-14h] BYREF
  int v5; // [esp+1Ch] [ebp-4h]

  v4[1] = this;
  *(uint32_t *)this = &vftbl_CNRDItemShopWindow;
  v5 = 4;
  sub_565AD0();
  *(uint32_t *)(this + 152) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 156) = 0;
  v3 = *(int **)(this + 144);
  v2 = *v3;
  LOBYTE(v5) = 2;
  sub_44D180((int **)(this + 140), v4, v2, (int)v3);
  j__free(*(void **)(this + 144));
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 112) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 116) = 0;
  if ( *(uint32_t *)(this + 96) != 0 )
    j__free(*(void **)(this + 96));
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  v5 = -1;
  *(uint32_t *)this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44F9B0 sub_44F9B0
// ------------------------------------------------------------
char */*thiscall*/ sub_44F9B0(char *this, int a2)
{
  uint32_t *v3; // eax

  *(uint32_t *)this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(a2, 0);
  *(uint32_t *)this = &vftbl_CNRDItemProductWindow;
  *(this + 88) = 0;
  *((uint32_t *)this + 21) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 23) = 0;
  *(this + 96) = 1;
  *(this + 98) = 0;
  *(this + 97) = 0;
  *((uint32_t *)this + 27) = 0;
  *((uint32_t *)this + 26) = 0;
  *((uint32_t *)this + 25) = 0;
  v3 = sub_433AC0();
  *((uint32_t *)this + 33) = v3;
  *((uint8_t *)v3 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)this + 33) + 4) = *((uint32_t *)this + 33);
  **((uint32_t **)this + 33) = *((uint32_t *)this + 33);
  *(uint32_t *)(*((uint32_t *)this + 33) + 8) = *((uint32_t *)this + 33);
  *((uint32_t *)this + 34) = 0;
  `eh vector constructor iterator'(this + 140, 0x10u, 5, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  *(this + 224) = 0;
  *(this + 225) = 0;
  *(this + 226) = 0;
  *(this + 227) = 0;
  *((uint32_t *)this + 59) = 0;
  *((uint32_t *)this + 60) = 6;
  *((uint32_t *)this + 61) = 12;
  *((uint32_t *)this + 62) = 0;
  *((uint32_t *)this + 63) = 1600;
  *((uint32_t *)this + 64) = 0;
  *((uint32_t *)this + 65) = 0;
  *((uint32_t *)this + 66) = 0;
  *((uint32_t *)this + 67) = 0;
  *((uint32_t *)this + 68) = 0;
  sub_566570(this);
  sub_566C60(this);
  return this;
}



// ------------------------------------------------------------
// 0x44FAF0 CNRDItemProductWindow__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemProductWindow__vmt4(void *Block, char a2)
{
  sub_44FB20();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44FB20 sub_44FB20
// ------------------------------------------------------------
void /*thiscall*/ sub_44FB20(char *this)
{
  int v2; // [esp-8h] [ebp-28h]
  int *v3; // [esp-4h] [ebp-24h]
  int v4[2]; // [esp+Ch] [ebp-14h] BYREF
  int v5; // [esp+1Ch] [ebp-4h]

  v4[1] = (int)this;
  *(uint32_t *)this = &vftbl_CNRDItemProductWindow;
  v5 = 4;
  sub_5672B0();
  if ( *((uint32_t *)this + 67) != 0 )
  {
    DeleteObject(*((HGDIOBJ *)this + 67));
    *((uint32_t *)this + 67) = 0;
  }
  *(this + 224) = 0;
  *(this + 225) = 0;
  *(this + 226) = 0;
  *(this + 227) = 0;
  *((uint32_t *)this + 59) = 0;
  *((uint32_t *)this + 60) = 0;
  *((uint32_t *)this + 61) = 0;
  *((uint32_t *)this + 62) = 0;
  *((uint32_t *)this + 63) = 0;
  *((uint32_t *)this + 64) = 0;
  *((uint32_t *)this + 65) = 0;
  *((uint32_t *)this + 66) = 0;
  *((uint32_t *)this + 67) = 0;
  *((uint32_t *)this + 68) = 0;
  LOBYTE(v5) = 2;
  `eh vector destructor iterator'(this + 140, 0x10u, 5, (void (/*thiscall*/ *)(void *))sub_5E5260);
  v3 = *((int **)this + 33);
  v2 = *v3;
  LOBYTE(v5) = 1;
  sub_44D180((int **)this + 32, v4, v2, (int)v3);
  j__free(*((void **)this + 33));
  *((uint32_t *)this + 33) = 0;
  *((uint32_t *)this + 34) = 0;
  *((uint32_t *)this + 21) = &vftbl_nengine__IObject;
  *(this + 88) = 0;
  v5 = -1;
  *(uint32_t *)this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44FC40 sub_44FC40
// ------------------------------------------------------------
char /*thiscall*/ sub_44FC40(int this)
{
  int v2; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int v9; // edi
  int v10; // eax

  v2 = *(uint32_t *)(this + 104);
  v3 = 0;
  v4 = 0;
  if ( v2 != 12 )
    v3 = *(uint32_t *)(this + 4 * v2 + 56);
  v5 = *(uint32_t *)(this + 108);
  if ( v5 != 12 )
    v4 = *(uint32_t *)(this + 4 * v5 + 56);
  LOBYTE(v6) = sub_4633D0(*(uint32_t *)(this + 16));
  if ( (uint8_t)v6 == 0 )
  {
    if ( v3 == 0 || (LOBYTE(v6) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 28))(v3), (uint8_t)v6 == 0) )
    {
      if ( v4 == 0 || (LOBYTE(v6) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 28))(v4), (uint8_t)v6 == 0) )
      {
        v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 36);
        if ( *(uint8_t *)(v6 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v6 + 12) )
        {
          v6 = *(uint32_t *)(this + 2504);
          if ( v6 != 1 && v6 != 2 )
          {
            v6 = *(uint32_t *)(dword_8F7A24 + 12);
            if ( v6 == 1 )
            {
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
              v6 = sub_45E870(pt.x, pt.y, 1);
              v9 = v6;
              if ( v6 == 0 )
              {
                if ( *(uint32_t *)(this + 2504) == 16 )
                  LOBYTE(v6) = sub_541D80();
                return v6;
              }
              if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 40))(v6, 34) == 0 )
              {
                if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 40))(v9, 66) != 0 )
                {
                  LOBYTE(v6) = *(uint8_t *)(v9 + 284);
                  if ( *(uint32_t *)(dword_8F7C08 + 648) == v9 )
                  {
                    if ( (uint8_t)v6 == 0 || *(uint8_t *)(v9 + 285) != 0 )
                      LOBYTE(v6) = sub_44ABE0(16);
                    else
                      LOBYTE(v6) = sub_541A60(1);
                  }
                  else if ( (uint8_t)v6 != 0 )
                  {
                    LOBYTE(v6) = *(uint8_t *)(v9 + 285);
                    if ( (uint8_t)v6 == 0 )
                    {
                      v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v9 + 288) + 52))(*(uint32_t *)(v9 + 288));
                      LOBYTE(v6) = sub_541ED0(v10);
                    }
                  }
                }
                else
                {
                  LOBYTE(v6) = sub_526BF0(v9, 1);
                }
                return v6;
              }
            }
            else
            {
              if ( v6 != 6 )
                return v6;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
              v6 = sub_45E870(pt.x, pt.y, 1);
              if ( v6 == 0 )
                return v6;
              LOBYTE(v6) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 40))(v6, 34);
              if ( (uint8_t)v6 == 0 )
                return v6;
            }
            LOBYTE(v6) = sub_567F40(1);
            return v6;
          }
          if ( v6 != 2 )
            return v6;
          v6 = *(uint32_t *)(this + 2508);
          if ( v6 == 3 || v6 == 4 )
          {
            v6 = sub_44A980(*(uint32_t *)(this + 2516));
            v7 = v6;
            if ( v6 != 0 )
            {
              v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 16))(v6) + 4);
              if ( v6 == *(uint32_t *)(this + 2512) )
              {
                if ( *(uint32_t *)(dword_8F7A24 + 12) != 3
                  || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 76))(v7) == 0 )
                {
                  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 84))(v7) == 0 )
                  {
                    v8 = sub_422E70(399);
                    goto LABEL_25;
                  }
                  if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 44))(v7) > 1 )
                  {
                    LOBYTE(v6) = sub_540DE0(0, 0, *(uint32_t *)(this + 2516), 7, 0, 0, 0);
                    return v6;
                  }
LABEL_36:
                  LOBYTE(v6) = sub_44E8D0((char *)this, (void *)0x15, v7, 1);
                  return v6;
                }
                if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 44))(v7) <= 1 )
                  LOBYTE(v6) = sub_486330(*(uint32_t *)(this + 2516), 1);
                else
                  LOBYTE(v6) = sub_540DE0(4, 0, *(uint32_t *)(this + 2516), 7, 0, 0, 0);
              }
            }
          }
          else if ( v6 == 2 )
          {
            v6 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(
                   dword_8F7C04,
                   *(uint32_t *)(this + 2516));
            v7 = v6;
            if ( v6 != 0 )
            {
              v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 16))(v6) + 4);
              if ( v6 == *(uint32_t *)(this + 2512) )
              {
                if ( *(uint32_t *)(dword_8F7A24 + 12) == 3
                  && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 76))(v7) != 0 )
                {
                  LOBYTE(v6) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1088))(
                                 dword_8F7C04,
                                 *(uint32_t *)(this + 2516));
                  return v6;
                }
                if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 84))(v7) == 0 )
                {
                  v8 = sub_422E70(400);
LABEL_25:
                  LOBYTE(v6) = sub_44E8D0((char *)this, (void *)0x1B, v8, 0);
                  return v6;
                }
                goto LABEL_36;
              }
            }
          }
        }
      }
    }
  }
  return v6;
}


// ------------------------------------------------------------
// 0x44FF60 sub_44FF60
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44FF60(uint32_t *this, void *Block)
{
  *this = &vftbl_CNRDPVPInterface;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *((uint8_t *)this + 144) = 0;
  *((uint8_t *)this + 145) = 0;
  *((uint8_t *)this + 146) = 0;
  *((uint8_t *)this + 147) = 0;
  *(this + 39) = 0;
  *(this + 40) = 6;
  *(this + 41) = 12;
  *(this + 42) = 0;
  *(this + 43) = 1600;
  *(this + 44) = 0;
  *(this + 45) = 0;
  *(this + 46) = 0;
  *(this + 47) = 0;
  *(this + 48) = 0;
  *((uint8_t *)this + 196) = 0;
  *((uint8_t *)this + 197) = 0;
  *((uint8_t *)this + 198) = 0;
  *((uint8_t *)this + 199) = 0;
  *(this + 52) = 0;
  *(this + 53) = 6;
  *(this + 54) = 12;
  *(this + 55) = 0;
  *(this + 56) = 1600;
  *(this + 57) = 0;
  *(this + 58) = 0;
  *(this + 59) = 0;
  *(this + 60) = 0;
  *(this + 61) = 0;
  *((uint8_t *)this + 248) = 0;
  *((uint8_t *)this + 249) = 0;
  *((uint8_t *)this + 250) = 0;
  *((uint8_t *)this + 251) = 0;
  *(this + 65) = 0;
  *(this + 66) = 6;
  *(this + 67) = 12;
  *(this + 68) = 0;
  *(this + 69) = 1600;
  *(this + 70) = 0;
  *(this + 71) = 0;
  *(this + 72) = 0;
  *(this + 73) = 0;
  *(this + 74) = 0;
  *((uint8_t *)this + 300) = 0;
  *((uint8_t *)this + 301) = 0;
  *((uint8_t *)this + 302) = 0;
  *((uint8_t *)this + 303) = 0;
  *(this + 78) = 0;
  *(this + 79) = 6;
  *(this + 80) = 12;
  *(this + 81) = 0;
  *(this + 82) = 1600;
  *(this + 83) = 0;
  *(this + 84) = 0;
  *(this + 85) = 0;
  *(this + 86) = 0;
  *(this + 87) = 0;
  sub_52A730(this);
  sub_52CA40(Block);
  return this;
}


