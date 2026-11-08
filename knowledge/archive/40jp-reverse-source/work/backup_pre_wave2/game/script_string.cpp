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
  int fld_88; // ecx
  uint16_t v3; // ax
  int v4; // esi
  int fld_120; // ecx
  int v6; // eax
  int pThis_128; // edi
  int v8; // eax
  int fld_5A4; // ecx
  int pThis_148; // eax
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
  void **Block2; // eax
  int v22; // eax
  int v23; // eax
  uint32_t *v24; // ecx
  int v25; // eax
  void **Block5; // eax
  int v27; // eax
  int v28; // esi
  int v29; // eax
  void **Block3; // eax
  int v31; // esi
  void **Block4; // eax
  int v33; // eax
  int v34; // esi
  char result; // al
  int v36; // [esp+Ch] [ebp-3Ch] BYREF
  int v37; // [esp+10h] [ebp-38h]
  const char *psz; // [esp+14h] [ebp-34h] BYREF
  char v39[4]; // [esp+18h] [ebp-30h] BYREF
  uint8_t v40[4]; // [esp+1Ch] [ebp-2Ch] BYREF
  void *Block[4]; // [esp+20h] [ebp-28h] BYREF
  int v42; // [esp+30h] [ebp-18h]
  unsigned int v43; // [esp+34h] [ebp-14h]
  int dword_796E502; // [esp+38h] [ebp-10h]
  int v45; // [esp+44h] [ebp-4h]

  fld_88 = *(uint32_t *)(this + 136);
  dword_796E502 = dword_796E50;
  psz = (const char *)sub_69B740(fld_88);
  if ( strcmp(psz, szPassword) == 0 )
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
          pThis_128 = this + 296;
        else
          pThis_128 = *(uint32_t *)(this + 296);
        v8 = sub_43BF40(pThis_128);
      }
      else
      {
        fld_5A4 = 28 * *(uint32_t *)(this + 1444);
        if ( *(uint32_t *)(fld_5A4 + this + 348) < 0x10u )
          pThis_148 = fld_5A4 + this + 328;
        else
          pThis_148 = *(uint32_t *)(fld_5A4 + this + 328);
        v8 = sub_43BF40(pThis_148);
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
      fld_120 = *(uint32_t *)(this + 288);
      if ( fld_120 == 2 )
      {
        v4 = 6;
      }
      else if ( fld_120 == 3 )
      {
        v4 = 8;
      }
      else
      {
        v6 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v6 == 2 || v6 == 3 || fld_120 == 1 )
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
  if ( (uint8_t)sub_43F740(this, psz) != 0 )
    goto LABEL_104;
  v11 = sub_43F210(&v36, &psz, v40, psz);
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
      Block2 = (void **)Block[0];
      if ( v43 < 0x10 )
        Block2 = Block;
      v22 = sub_43BF40(Block2);
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
        Block3 = (void **)Block[0];
        if ( v43 < 0x10 )
          Block3 = Block;
        v31 = sub_43BF40(Block3);
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
        Block4 = (void **)Block[0];
        if ( v43 < 0x10 )
          Block4 = Block;
        v33 = sub_43BF40(Block4);
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
        Block5 = (void **)Block[0];
        if ( v43 < 0x10 )
          Block5 = Block;
        v27 = sub_43BF40(Block5);
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
          psz = (const char *)*(uint16_t *)(v28 + 4);
          sub_423290(&psz, 2);
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
          psz = nullptr;
          sub_423290(&psz, 4);
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
char /*usercall*/ sub_441750@<al>(int pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>)
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
  int pObj; // edi
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
  int pObj2; // esi
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

  v4 = *(uint32_t *)(pArg1 + 124);
  v5 = *(uint8_t *)(v4 + 116);
  *(uint8_t *)(v4 + 116) = 0;
  if ( v5 != 0
    && (uint8_t)sub_44C410(2) == 0
    && (uint8_t)sub_44C410(1) == 0
    && (uint8_t)sub_44C410(0) == 0 )
  {
    sub_43B920(1);
  }
  v6 = *(uint32_t *)(pArg1 + 136);
  v7 = *(uint8_t *)(v6 + 116);
  *(uint8_t *)(v6 + 116) = 0;
  if ( v7 != 0 )
    sub_440F90(pArg1);
  v8 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v8 != 2 && v8 != 5 )
  {
    v9 = *(uint8_t *)(pArg1 + 1474) == 0;
    v10 = *(uint32_t *)(pArg1 + 12);
    *(uint32_t *)(v10 + 28) = 317;
    if ( v9 )
    {
      *(uint32_t *)(v10 + 32) = 162;
      sub_69A5F0(*(uint32_t **)(pArg1 + 24), 5, 144);
      sub_69A5F0(*(uint32_t **)(pArg1 + 112), 2, 198);
      sub_69A5F0(*(uint32_t **)(pArg1 + 100), 2, 182);
      sub_69A5F0(*(uint32_t **)(pArg1 + 104), 20, 182);
      *(uint8_t *)(*(uint32_t *)(pArg1 + 104) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(pArg1 + 108) + 16) = 0;
      v13 = (int *)(pArg1 + 76);
      for ( i = 4; i != 0; --i )
        sub_69C3E0(*v13++, 8);
    }
    else
    {
      *(uint32_t *)(v10 + 32) = 354;
      sub_69A5F0(*(uint32_t **)(pArg1 + 24), 2, 336);
      sub_69A5F0(*(uint32_t **)(pArg1 + 112), 2, 390);
      sub_69A5F0(*(uint32_t **)(pArg1 + 100), 2, 374);
      sub_69A5F0(*(uint32_t **)(pArg1 + 108), 20, 374);
      *(uint8_t *)(*(uint32_t *)(pArg1 + 104) + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(pArg1 + 108) + 16) = 1;
      v11 = (int *)(pArg1 + 76);
      for ( j = 4; j != 0; --j )
        sub_69C3E0(*v11++, 20);
    }
    sub_69A5F0(*(uint32_t **)(pArg1 + 116), 59, 319);
    v15 = 0;
    v16 = (uint32_t **)(pArg1 + 28);
    do
    {
      v17 = *v16;
      if ( *(uint8_t *)(pArg1 + 1474) != 0 )
        sub_69A5F0(v17, v15 * v17[7] + 38, 371);
      else
        sub_69A5F0(v17, v15 * v17[7] + 38, 179);
      ++v15;
      ++v16;
    }
    while ( v15 < 4 );
    v18 = 0;
    pObj = pArg1 + 28;
    do
    {
      if ( *(uint8_t *)(*(uint32_t *)pObj + 17) != 0 && dword_79BE34 == *(uint32_t *)(*(uint32_t *)pObj + 12) )
        sub_43BA20(v18);
      ++v18;
      pObj += 4;
    }
    while ( v18 < 4 );
    if ( *(uint8_t *)(pArg1 + 1475) == 0 && *(uint8_t *)(pArg1 + 1474) != 0 )
    {
      x = pt.x;
      y = pt.y;
      v66 = pt.x;
      if ( pt.x >= 38 && pt.x <= 83 && pt.y >= 371 && pt.y <= 385 && byte_89D274 != 0 )
      {
        *(uint32_t *)(pArg1 + 144) = 0;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 76) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 28) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 80) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 32) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 84) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 36) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 88) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 40) + 16) = 1;
        v22 = sub_69C3A0(*(uint32_t *)(pArg1 + 76));
        v23 = sub_69C500(*(uint32_t *)(pArg1 + 76)) - v22;
        if ( *(uint8_t *)(pArg1 + 1474) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 72) + 32))(*(uint32_t *)(pArg1 + 72), v23 <= 0 ? 0 : v23);
          v24 = sub_69C6A0(*(uint32_t *)(pArg1 + 72));
        }
        else
        {
          (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 56) + 32))(*(uint32_t *)(pArg1 + 56), v23 <= 0 ? 0 : v23);
          v24 = sub_69C6A0(*(uint32_t *)(pArg1 + 56));
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
        *(uint32_t *)(pArg1 + 144) = 1;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 76) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 28) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 80) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 32) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 84) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 36) + 16) = 1;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 88) + 16) = 0;
        *(uint8_t *)(*(uint32_t *)(pArg1 + 40) + 16) = 1;
        v25 = sub_69C3A0(*(uint32_t *)(pArg1 + 80));
        v26 = sub_69C500(*(uint32_t *)(pArg1 + 80)) - v25;
        if ( *(uint8_t *)(pArg1 + 1474) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 72) + 32))(*(uint32_t *)(pArg1 + 72), v26 <= 0 ? 0 : v26);
          v27 = sub_69C6A0(*(uint32_t *)(pArg1 + 72));
        }
        else
        {
          (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 56) + 32))(*(uint32_t *)(pArg1 + 56), v26 <= 0 ? 0 : v26);
          v27 = sub_69C6A0(*(uint32_t *)(pArg1 + 56));
        }
        sub_69C680(v27);
      }
    }
    if ( *(uint32_t *)(pArg1 + 144) != 4 )
    {
      if ( *(uint8_t *)(pArg1 + 1474) != 0 )
      {
        v28 = sub_69C690(*(uint32_t **)(pArg1 + 72));
        sub_69C400(*(uint32_t *)(pArg1 + 4 * *(uint32_t *)(pArg1 + 144) + 76), v28);
      }
      else
      {
        v63 = sub_69C690(*(uint32_t **)(pArg1 + 56));
        sub_69C400(*(uint32_t *)(pArg1 + 4 * *(uint32_t *)(pArg1 + 144) + 76), v63);
      }
    }
    v29 = sub_699000(pArg1 + 148);
    v30 = sub_69C500(*(uint32_t *)(pArg1 + 96)) - 1;
    if ( v30 >= 0 )
    {
      v31 = (uint32_t *)(pArg1 + 4 * v30 + 176);
      while ( v29 <= *v31 + 10000 )
      {
        --v30;
        --v31;
        if ( v30 < 0 )
          goto LABEL_60;
      }
      v32 = v30 + 1;
      sub_69C340(*(uint8_t **)(pArg1 + 96), v30 + 1);
      v33 = 20 - v32;
      if ( 20 - v32 > 0 )
      {
        v34 = (uint32_t *)(pArg1 + 176);
        v35 = (uint32_t *)(pArg1 + 4 * v32 + 176);
        do
        {
          *v34++ = *v35++;
          --v33;
        }
        while ( v33 != 0 );
      }
    }
LABEL_60:
    v36 = *(uint32_t *)(pArg1 + 100);
    if ( *(uint8_t *)(v36 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v36 + 12) )
      *(uint8_t *)(pArg1 + 1473) = *(uint8_t *)(pArg1 + 1473) == 0;
    v37 = *(uint32_t *)(pArg1 + 104);
    if ( *(uint8_t *)(v37 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v37 + 12)
      || *(uint8_t *)((v38 = *(uint32_t *)(pArg1 + 108)) + 17) != 0 && dword_79BE34 == *(uint32_t *)(v38 + 12) )
    {
      v39 = *(uint32_t *)(pArg1 + 108);
      v40 = *(uint8_t *)(pArg1 + 1474) == 0;
      *(uint8_t *)(pArg1 + 1474) = v40;
      if ( *(uint8_t *)(v39 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v39 + 12) )
      {
        if ( v40 )
        {
          v41 = sub_69C6A0(*(uint32_t *)(pArg1 + 72));
          v42 = *(uint32_t **)(pArg1 + 72);
        }
        else
        {
          v41 = sub_69C6A0(*(uint32_t *)(pArg1 + 56));
          v42 = *(uint32_t **)(pArg1 + 56);
        }
        v67 = sub_69C690(v42) == v41;
        v43 = *(uint8_t *)(pArg1 + 1474) != 0 ? 20 : 8;
        v44 = sub_69C500(*(uint32_t *)(pArg1 + 4 * *(uint32_t *)(pArg1 + 144) + 76)) - v43;
        pObj2 = *(uint8_t *)(pArg1 + 1474) != 0 ? *(uint32_t *)(pArg1 + 72) : *(uint32_t *)(pArg1 + 56);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 32))(pObj2, v44 <= 0 ? 0 : v44);
        if ( v67 )
        {
          if ( *(uint8_t *)(pArg1 + 1474) != 0 )
            v46 = sub_69C6A0(*(uint32_t *)(pArg1 + 72));
          else
            v46 = sub_69C6A0(*(uint32_t *)(pArg1 + 56));
          sub_69C680(v46);
        }
      }
    }
    v47 = dword_79BE54 == *(uint32_t *)(*(uint32_t *)(pArg1 + 136) + 12);
    if ( v47 != *(uint8_t *)(pArg1 + 256) )
      sub_43B920(v47);
    if ( *(uint8_t *)(pArg1 + 1473) != 0 )
    {
      v48 = *(uint32_t *)(pArg1 + 112);
      if ( *(uint8_t *)(v48 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v48 + 12) )
      {
        v49 = sub_43BBC0(pArg1);
        *(uint32_t *)(pArg1 + 4) = v49;
        if ( v49 != -1 )
        {
          switch ( v49 )
          {
            case 0:
              v50 = (bool *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1453);
              goto LABEL_92;
            case 1:
              v50 = (bool *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1457);
              goto LABEL_92;
            case 2:
              v50 = (bool *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1461);
              goto LABEL_92;
            case 3:
              v50 = (bool *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1465);
              goto LABEL_92;
            case 4:
              v50 = (bool *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1469);
LABEL_92:
              *v50 = !*v50;
              break;
            default:
              break;
          }
        }
      }
    }
    if ( *(uint8_t *)(pArg1 + 1475) != 0 )
    {
      v51 = *(uint32_t *)(pArg1 + 116);
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
                *(uint32_t *)(pArg1 + 288) = 0;
            }
            else if ( sub_429830((uint16_t)word_77F804) != 0
                   && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) != 0 )
            {
              *(uint32_t *)(pArg1 + 288) = 1;
            }
          }
          else if ( sub_429830((uint16_t)word_77F804) != 0
                 && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 120) != 0 )
          {
            *(uint32_t *)(pArg1 + 288) = 2;
          }
        }
      }
    }
LABEL_114:
    LOBYTE(v8) = *(uint8_t *)(pArg1 + 256);
    if ( (uint8_t)v8 != 0 )
    {
      sub_4BF300(0, 0);
      if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_79C0B4 + 16))(
             dword_79C0B4,
             31,
             nArg2,
             nArg3) != 0 )
      {
        if ( *(uint32_t *)(pArg1 + 312) != 0 )
        {
          sub_43DA50(pArg1, 0, 0);
        }
        else
        {
          switch ( *(uint32_t *)(pArg1 + 288) )
          {
            case 0:
              if ( sub_429830((uint16_t)word_77F804) != 0
                && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) != 0 )
              {
                if ( sub_429830((uint16_t)word_77F804) != 0
                  && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) != 0 )
                {
                  *(uint32_t *)(pArg1 + 288) = 1;
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
                  *(uint32_t *)(pArg1 + 288) = 2;
              }
              break;
            case 2:
LABEL_132:
              *(uint32_t *)(pArg1 + 288) = 3;
              break;
            case 3:
              *(uint32_t *)(pArg1 + 288) = 0;
              break;
            default:
              break;
          }
        }
      }
      v56 = *(uint32_t *)(pArg1 + 132);
      if ( *(uint8_t *)(v56 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v56 + 12) )
        *(uint8_t *)(pArg1 + 1475) = *(uint8_t *)(pArg1 + 1475) == 0;
      sub_43DBE0((uint32_t *)pArg1);
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 15) != 0
        && (*(uint32_t *)(pArg1 + 312) != 0 && *(uint8_t *)(pArg1 + 1794) != 0
         || *(uint8_t *)(pArg1 + 320) != 0 && *(uint8_t *)(pArg1 + 1794) != 0) )
      {
        *(uint8_t *)(pArg1 + 320) = 0;
        sub_43DA50(pArg1, 0, 0);
      }
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 2) != 0
        && *(int *)(pArg1 + 1448) > 0 )
      {
        v57 = *(uint32_t *)(pArg1 + 1444);
        if ( v57 > 0 )
        {
          if ( *(uint8_t *)(pArg1 + 320) != 0 )
            *(uint32_t *)(pArg1 + 1444) = v57 - 1;
        }
        else
        {
          *(uint32_t *)(pArg1 + 1444) = 0;
        }
        *(uint8_t *)(pArg1 + 1452) = 0;
        *(uint8_t *)(pArg1 + 320) = 1;
      }
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 3) != 0 )
      {
        v58 = *(uint32_t *)(pArg1 + 1448);
        if ( v58 > 0 )
        {
          v59 = *(uint32_t *)(pArg1 + 1444);
          v60 = v58 - 1;
          if ( v59 < v60 )
          {
            if ( *(uint8_t *)(pArg1 + 320) != 0 )
              *(uint32_t *)(pArg1 + 1444) = v59 + 1;
          }
          else
          {
            *(uint32_t *)(pArg1 + 1444) = v60;
          }
          *(uint8_t *)(pArg1 + 1452) = 0;
          *(uint8_t *)(pArg1 + 320) = 1;
        }
      }
      v61 = *(uint32_t *)(pArg1 + 136);
      if ( *(uint32_t *)(v61 + 192) != 0 )
        v8 = v61 + 180;
      else
        v8 = v61 + 160;
      LOBYTE(v8) = *(uint32_t *)(v8 + 12) == 0;
      *(uint8_t *)(pArg1 + 1794) = v8;
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
// 0x442280 sub_442280 —— 日志转发桩
// 转发 off_77F3FC（游戏日志 printf）—— 变参原样透传
// ------------------------------------------------------------
int /*stdcall*/ sub_442280(char *Format)
{
  return off_77F3FC(Format);
}



// ------------------------------------------------------------
// 0x4422A0 sub_4422A0 —— 日志转发桩（忽略次参）
// —— 与 ·sub_442280 同构（差异：次参 nArg2 不参与转发）
// ------------------------------------------------------------
int /*stdcall*/ sub_4422A0(char *Format, int nArg2)
{
  return off_77F3FC(Format);
}



// ------------------------------------------------------------
// 0x4422C0 sub_4422C0
// ------------------------------------------------------------
// 脚本包根路径设置：拷贝路径到 byte_8F8898（补 \\ 或 / 结尾）；
// "_ScriptPacks" 存在 → byte_78FF3C=1；"!ScriptPacks" 不存在且标志置位 →
// sub_528DB0("Script.pvf") 打开脚本包体（0x528DB0 = pvf 挂载器）。
char /*cdecl*/ sub_4422C0(const char *pArg1)
{
  strcpy(byte_8F8898, pArg1);
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
int /*cdecl*/ sub_4423D0(uint8_t *uArg1)
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
    if ( uArg1 != nullptr )
    {
      *uArg1 = 1;
      LODWORD(v2) = v5;
      return v2;
    }
LABEL_13:
    LODWORD(v2) = v5;
    return v2;
  }
  if ( v1 != 4 )
  {
    if ( uArg1 != nullptr )
      *uArg1 = 0;
    goto LABEL_13;
  }
  sscanf(dword_9789A4, "%f", &v4);
  if ( uArg1 != nullptr )
    *uArg1 = 1;
  return (uint64_t)v4;
}



// ------------------------------------------------------------
// 0x442480 sub_442480 —— 脚本 token 数值解析（double 版）
// token 型别 2/3/4 分别按 %d/%x/%f 解析；*uArg1 回写是否可解析
// 与 ·sub_4423D0 同构（差异：返回 double，%f 走浮点直返）
// ------------------------------------------------------------
double /*cdecl*/ sub_442480(uint8_t *uArg1)
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
      if ( uArg1 != nullptr )
        *uArg1 = 1;
      return (double)v3;
    case 3:
      sscanf(dword_9789A4 + 2, "%x", &v3);
      goto LABEL_3;
    case 4:
      sscanf(dword_9789A4, "%f", &v4);
      result = v4;
      if ( uArg1 != nullptr )
        *uArg1 = 1;
      break;
    default:
      result = v4;
      if ( uArg1 != nullptr )
        *uArg1 = 0;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x442520 sub_442520 —— 方括号 token 转整数
// 剥掉首尾方括号（pArg1[1..len-2]）后走 j__atol —— [数字] 型脚本 token 取值
// ------------------------------------------------------------
int /*cdecl*/ sub_442520(const char *pArg1)
{
  unsigned int nLen; // ecx
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
  int dword_796E502; // [esp+30h] [ebp-4h]

  dword_796E502 = dword_796E50;
  nLen = strlen(pArg1);
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
  v3 = nLen - 1;
  String = 0;
  if ( v3 > 1 )
  {
    do
    {
      *(&v5 + v2) = pArg1[v2];
      ++v2;
    }
    while ( v2 < v3 );
  }
  return j__atol(&String);
}



// ------------------------------------------------------------
// 0x4425A0 sub_4425A0 —— 方括号 token 转字符串
// 剥掉首尾方括号拷入全局 byte_97B358 并补 0，返回缓冲地址（字符串型 token）
// ------------------------------------------------------------
uint8_t */*cdecl*/ sub_4425A0(const char *pArg1)
{
  unsigned int nLen; // ecx
  int v2; // eax
  int v3; // ecx

  nLen = strlen(pArg1);
  v2 = 1;
  v3 = nLen - 1;
  if ( v3 > 1 )
  {
    do
    {
      byte_97B358[v2 - 1] = pArg1[v2];
      ++v2;
    }
    while ( v2 < v3 );
  }
  byte_97B357[v2] = 0;
  return byte_97B358;
}



// ------------------------------------------------------------
// 0x4425F0 sub_4425F0 —— 场景前景/背景档位标签→索引
// [close]=0 [normal]=1 [bottom]=2 [closeback]=3 [middleback]=4 [distantback]=5；均不匹配返回 6（strcmp 链自证）
// ------------------------------------------------------------
int /*cdecl*/ sub_4425F0(const char *pArg1)
{
  if ( strcmp(pArg1, "[close]") == 0 )
    return 0;
  if ( strcmp(pArg1, "[normal]") == 0 )
    return 1;
  if ( strcmp(pArg1, "[bottom]") == 0 )
    return 2;
  if ( strcmp(pArg1, "[closeback]") == 0 )
    return 3;
  if ( strcmp(pArg1, "[middleback]") == 0 )
    return 4;
  return (strcmp(pArg1, "[distantback]") != 0) + 5;
}



// ------------------------------------------------------------
// 0x4426A0 sub_4426A0
// ------------------------------------------------------------
// 职业标签→索引：[swordman]=0 / [fighter]=1 / [gunner]=2 / [mage]=3（strcmp 链自证）
int /*cdecl*/ sub_4426A0(const char *pArg1)
{
  if ( strcmp(pArg1, "[swordman]") == 0 )
    return 0;
  if ( strcmp(pArg1, "[fighter]") == 0 )
    return 1;
  if ( strcmp(pArg1, "[gunner]") == 0 )
    return 2;
  return (strcmp(pArg1, "[mage]") != 0) + 3;
}



// ------------------------------------------------------------
// 0x442710 sub_442710
// ------------------------------------------------------------
// 元素标签→索引：[fire]=0 / [water]=1 / [dark]=2 / [light]=3（strcmp 链自证）
int /*cdecl*/ sub_442710(const char *pArg1)
{
  if ( strcmp(pArg1, "[fire element]") == 0 )
    return 0;
  if ( strcmp(pArg1, "[water element]") == 0 )
    return 1;
  if ( strcmp(pArg1, "[dark element]") == 0 )
    return 2;
  return (strcmp(pArg1, "[light element]") != 0) + 3;
}



// ------------------------------------------------------------
// 0x442780 sub_442780
// ------------------------------------------------------------
// 当前元素标签 setter：按入参写全局 dword_97B384
// （"[water element]"/"[dark element]"/"[light element]"/缺省 "[fire element]"，
// 与 0x442710 索引一一对应；该全局即 UI/技能元素着色取词源）
int */*cdecl*/ sub_442780(int nArg1)
{
  if ( nArg1 != 0 )
  {
    if ( nArg1 == 1 )
    {
      strcpy((char *)&dword_97B384, "[water element]");
      return &dword_97B384;
    }
    else if ( nArg1 == 2 )
    {
      strcpy((char *)&dword_97B384, "[dark element]");
      return &dword_97B384;
    }
    else
    {
      if ( nArg1 == 3 )
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
// 0x4428C0 sub_4428C0 —— 磁盘脚本文件整体读入
// ·sub_442390 拼根路径后 fopen(rb) 读入全局缓冲 byte_8F8998；超 0x80000 或打不开返回 -1，成功返回字节数
// ------------------------------------------------------------
int /*cdecl*/ sub_4428C0(const char *ArgList, const char *pArg2)
{
  FILE *pFile; // eax
  FILE *pFile2; // esi
  signed int nPos; // edi

  sub_442390(byte_97B398, "%s%s", ArgList, pArg2);
  pFile = fopen(byte_97B398, "rb");
  pFile2 = pFile;
  if ( pFile == nullptr )
    return -1;
  fseek(pFile, 0, 2);
  nPos = ftell(pFile2);
  fseek(pFile2, 0, 0);
  if ( nPos > 0x80000 )
    return -1;
  sub_66BD5A(byte_8F8998, nPos, 1u, pFile2);
  fclose(pFile2);
  return nPos;
}



// ------------------------------------------------------------
// 0x442950 sub_442950 —— PVF 脚本条目读入
// ·sub_528650 从脚本包抽条目到 byte_8F8998（上限 0x80000）；失败播报 readScriptFromPVF : script error %s%s 并返回 -1
// ------------------------------------------------------------
int /*cdecl*/ sub_442950(const char *ArgList, const char *pArg2)
{
  int result; // eax
  char Buffer[512]; // [esp+8h] [ebp-204h] BYREF
  int dword_796E502; // [esp+208h] [ebp-4h]

  dword_796E502 = dword_796E50;
  sprintf(Buffer, "%s%s", ArgList, pArg2);
  result = sub_528650((int)Buffer, byte_8F8998, 0x80000);
  if ( result == 0 )
  {
    off_77F3FC("readScriptFromPVF : script error %s%s ", ArgList, pArg2);
    return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4429C0 sub_4429C0 —— 60 字节元素 vector 计数
// 返回 (end - begin) / 60；begin 为空返回 0
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
// 0x4429F0 sub_4429F0 —— 红黑树最小键节点
// 沿 +8 左子指针下探到 +45 哨兵为真的节点 —— map/set 最左（_Min）
// ------------------------------------------------------------
int /*cdecl*/ sub_4429F0(int pArg1)
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 45) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x442A10 sub_442A10 —— 脚本载入调度（PVF 或磁盘）
// 前置钩 dword_978998；判据 byte_78FF3C=0（或 ../DebugConfig.txt 强制磁盘）走 ·sub_4428C0，否则 ·sub_442950 读包；
// 成功后 ·sub_65D4D0 解析；返回 0/1
// ------------------------------------------------------------
char /*cdecl*/ sub_442A10(const char *ArgList, const char *pArg2)
{
  char *v2; // esi
  int v3; // eax

  if ( dword_978998 != nullptr )
    dword_978998();
  if ( byte_78FF3C == 0 || strcmp(pArg2, "../DebugConfig.txt") == 0 )
  {
    v2 = (char *)ArgList;
    v3 = sub_4428C0(ArgList, pArg2);
  }
  else
  {
    v2 = (char *)ArgList;
    v3 = sub_442950(ArgList, pArg2);
  }
  if ( v3 == -1 )
    return 0;
  sub_65D4D0(v2, (int)pArg2, byte_8F8998, v3);
  return 1;
}



// ------------------------------------------------------------
// 0x442A80 sub_442A80 —— std::string 字符指针获取
// 长度 ≤ 下标时抛 _Xran；容量 <0x10 取内联缓冲 +4，否则取堆指针 +uArg2
// ------------------------------------------------------------
int /*thiscall*/ sub_442A80(std::_String_base *this, unsigned int uArg2)
{
  if ( *((uint32_t *)this + 5) <= uArg2 )
    std::_String_base::_Xran(this);
  if ( *((uint32_t *)this + 6) < 0x10u )
    return (int)this + uArg2 + 4;
  else
    return *((uint32_t *)this + 1) + uArg2;
}



// ------------------------------------------------------------
// 0x442AC0 sub_442AC0 —— 红黑树左旋
// 节点 0x30 版左旋：右子上提并修正三段父子指针；与 ·sub_433290（右旋）成对
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_442AC0(uint32_t *this, int pArg2)
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);
  *(uint32_t *)(pArg2 + 8) = *result;
  if ( *(uint8_t *)(*result + 45) == 0 )
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
// 0x442B20 sub_442B20 —— 国家码标签配对校验（void）
// 全局国家码 dword_78FF38 非 -1 时取串首字节低 7 位，比对后续 token 型别 14..16；
// 不配对播报 ignoreNationalTag - Nation code pair mismatch
// ------------------------------------------------------------
void /*cdecl*/ sub_442B20(std::_String_base *uArg1)
{
  char *v1; // esi
  int v2; // esi
  int v3; // eax

  if ( dword_78FF38 != -1 )
  {
    if ( *((uint32_t *)uArg1 + 5) == 0 )
      std::_String_base::_Xran(uArg1);
    v1 = *((uint32_t *)uArg1 + 6) < 0x10u ? (char *)uArg1 + 4 : *((char **)uArg1 + 1);
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
// 0x442BC0 sub_442BC0 —— 国家码标签配对校验（bool）
// —— 与 ·sub_442B20 同构（差异：返回 1/0 供判定；首字节为方括号或国家码 -1 直接 0）
// ------------------------------------------------------------
char /*cdecl*/ sub_442BC0(std::_String_base *uArg1)
{
  char *v1; // esi
  int v2; // esi
  int v3; // eax

  if ( dword_78FF38 == -1 )
    return 0;
  if ( *((uint32_t *)uArg1 + 5) == 0 )
    std::_String_base::_Xran(uArg1);
  v1 = *((uint32_t *)uArg1 + 6) < 0x10u ? (char *)uArg1 + 4 : *((char **)uArg1 + 1);
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
// 0x442C50 sub_442C50 —— std::string 析构（+8 区）
// 容量（+28）≥ 0x10 释放堆块 +8；随后 容量=15 长度=0 首字节=0
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
// 0x442C80 sub_442C80 —— 判首字符方括号并析构
// 读串首字符，为 0x5B（[）返回 0 否则 1；两条路径都先释放堆块 —— 短命 string 的标签判定
// ------------------------------------------------------------
char /*cdecl*/ sub_442C80(char pszArg1, void **Block, int nArg3, int nArg4, int nArg5, int nArg6, unsigned int uArg7)
{
  void **p_Block; // ecx

  if ( nArg6 == 0 )
    std::_String_base::_Xran((std::_String_base *)&pszArg1);
  p_Block = Block;
  if ( uArg7 < 0x10 )
    p_Block = (void **)&Block;
  if ( *(uint8_t *)p_Block == 91 )
  {
    if ( uArg7 >= 0x10 )
      j__free(Block);
    return 0;
  }
  else
  {
    if ( uArg7 >= 0x10 )
      j__free(Block);
    return 1;
  }
}



// ------------------------------------------------------------
// 0x442D00 sub_442D00 —— 红黑树等键查找（_Find）
// 等键下探：键值相等返回节点、未命中回 header —— map 按键查找基元（值为串指针）
// ------------------------------------------------------------
int **/*thiscall*/ sub_442D00(int **this, int **pDwArg2, uint32_t *uArg3)
{
  int *fld_e1; // edx
  int *v4; // eax

  fld_e1 = *(this + 1);
  v4 = (int *)fld_e1[1];
  while ( *((uint8_t *)v4 + 45) == 0 )
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
// 0x442D70 sub_442D70 —— std::string 析构（+20 区）
// —— 与 ·sub_442C50 同构（差异：字段偏移 20/36/40）
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
// 0x442DA0 sub_442DA0 —— map 按键查串指针
// ·sub_442D00 定位后命中键返回其 string 数据指针，未命中 nullptr
// ------------------------------------------------------------
int */*thiscall*/ sub_442DA0(int **this, int nArg2)
{
  int *v4; // [esp+4h] [ebp-4h] BYREF

  sub_442D00(this, &v4, &nArg2);
  if ( v4 == *(this + 1) )
    return nullptr;
  if ( (unsigned int)v4[10] < 0x10 )
    return v4 + 5;
  return (int *)v4[5];
}



// ------------------------------------------------------------
// 0x442DF0 sub_442DF0 —— map 迭代器前进并回旧值
// 先存旧值于 *uArg2 再 ·sub_40BEA0 前进 —— 迭代器 advance（后置 ++ 语义）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_442DF0(int *this, uint32_t *uArg2, int nArg3)
{
  int v3; // esi

  v3 = *this;
  sub_40BEA0(this);
  *uArg2 = v3;
  return uArg2;
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
// 0x442EB0 sub_442EB0 —— 28 字节元素区间构造
// 逐元素 ·sub_4014D0（std::string 拷贝构造），步长 28；返回尾指针
// ------------------------------------------------------------
std::_String_base */*cdecl*/ sub_442EB0(int nArg1, int nArg2, std::_String_base *uArg3)
{
  int nArg12; // esi
  std::_String_base *uArg32; // edi

  nArg12 = nArg1;
  if ( nArg1 == nArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    sub_4014D0(uArg32, nArg12, 0, -1);
    nArg12 += 28;
    uArg32 = (std::_String_base *)((char *)uArg32 + 28);
  }
  while ( nArg12 != nArg2 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x442EF0 sub_442EF0 —— vector 长度溢出抛出
// 构造并抛 std::length_error，文案 vector<T> too long（CRT 模板实体）
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
// 0x442F60 sub_442F60 —— 红黑树节点摘除 + 再平衡
// 迭代器失效防御（invalid map/set<T> iterator）→ 摘除节点 → 双旋再平衡
// → 析构内联 string 并 free 0x30 节点、计数 -1
// ------------------------------------------------------------
int ***/*thiscall*/ sub_442F60(uint32_t *this, int ***uArg2, int **pDwArg3)
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
  int pObj; // eax
  uint32_t *Block2; // eax
  int v19; // eax
  void **pExceptionObject; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v22[20]; // [esp+34h] [ebp-34h] BYREF
  int v23; // [esp+48h] [ebp-20h]
  int v24; // [esp+4Ch] [ebp-1Ch]
  int v25; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v28; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 45) != 0 )
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
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_40BEA0(&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 45) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 45) == 0 )
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
      if ( *((uint8_t *)v4 + 45) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = sub_6600D0(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
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
  if ( *((uint8_t *)pDwArg32[2] + 45) != 0 )
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
    if ( *((uint8_t *)v4 + 45) == 0 )
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
  v14 = *((uint8_t *)v5 + 44);
  *((uint8_t *)v5 + 44) = *((uint8_t *)pDwArg32 + 44);
  *((uint8_t *)pDwArg32 + 44) = v14;
LABEL_35:
  v15 = (void **)Block;
  if ( *((uint8_t *)Block + 44) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 44) != 1 )
          break;
        pObj = *v6;
        if ( v4 == (int *)*v6 )
        {
          pObj = v6[2];
          if ( *(uint8_t *)(pObj + 44) == 0 )
          {
            *(uint8_t *)(pObj + 44) = 1;
            *((uint8_t *)v6 + 44) = 0;
            sub_442AC0(v6);
            pObj = v6[2];
            pThis3 = pThis;
          }
          if ( *(uint8_t *)(pObj + 45) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)pObj + 44) != 1 || *(uint8_t *)(*(uint32_t *)(pObj + 8) + 44) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)(pObj + 8) + 44) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)pObj + 44) = 1;
              *(uint8_t *)(pObj + 44) = 0;
              sub_433290(pObj);
              pObj = v6[2];
            }
            *(uint8_t *)(pObj + 44) = *((uint8_t *)v6 + 44);
            *((uint8_t *)v6 + 44) = 1;
            *(uint8_t *)(*(uint32_t *)(pObj + 8) + 44) = 1;
            sub_442AC0(v6);
            break;
          }
        }
        else
        {
          if ( *(uint8_t *)(pObj + 44) == 0 )
          {
            *(uint8_t *)(pObj + 44) = 1;
            *((uint8_t *)v6 + 44) = 0;
            sub_433290(v6);
            pObj = *v6;
            pThis3 = pThis;
          }
          if ( *(uint8_t *)(pObj + 45) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)(pObj + 8) + 44) != 1 || *(uint8_t *)(*(uint32_t *)pObj + 44) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)pObj + 44) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)(pObj + 8) + 44) = 1;
              *(uint8_t *)(pObj + 44) = 0;
              sub_442AC0(pObj);
              pObj = *v6;
            }
            *(uint8_t *)(pObj + 44) = *((uint8_t *)v6 + 44);
            *((uint8_t *)v6 + 44) = 1;
            *(uint8_t *)(*(uint32_t *)pObj + 44) = 1;
            sub_433290(v6);
            break;
          }
        }
        *(uint8_t *)(pObj + 44) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    v15 = (void **)Block;
    *((uint8_t *)v4 + 44) = 1;
  }
  if ( (unsigned int)v15[10] >= 0x10 )
    j__free(v15[5]);
  Block2 = Block;
  *((uint32_t *)Block + 10) = 15;
  Block2[9] = 0;
  *((uint8_t *)Block2 + 20) = 0;
  j__free(Block2);
  v19 = pThis[2];
  if ( v19 != 0 )
    pThis[2] = v19 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x443240 sub_443240 —— 0x30 map 节点构造
// 写 key/值三字段 + 内联 string（+16 起）+ 颜色（+44）置参数、哨兵（+45）置 0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_443240(uint32_t *this, int nArg2, int nArg3, int nArg4, uint32_t *uArg5, char pszArg6)
{
  *this = nArg2;
  *(this + 1) = nArg3;
  *(this + 2) = nArg4;
  *(this + 3) = *uArg5;
  *(this + 10) = 15;
  *(this + 9) = 0;
  *((uint8_t *)this + 20) = 0;
  sub_4014D0((std::_String_base *)(this + 4), uArg5 + 1, 0, -1);
  *((uint8_t *)this + 44) = pszArg6;
  *((uint8_t *)this + 45) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4432A0 sub_4432A0 —— 28 字节区间构造转发
// —— 与 ·sub_442EB0 同构（纯转发）
// ------------------------------------------------------------
std::_String_base */*cdecl*/ sub_4432A0(int nArg1, int nArg2, std::_String_base *uArg3)
{
  return sub_442EB0(nArg1, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x4432C0 sub_4432C0 —— 32 字节元素区间拷贝
// 逐元素拷 key（+0）并以 ·sub_4014D0 拷 string（+4），步长 32；返回尾指针
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4432C0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
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
    sub_4014D0((std::_String_base *)(uArg32 + 1), uArg12 + 1, 0, -1);
    uArg12 += 8;
    uArg32 += 8;
  }
  while ( uArg12 != uArg2 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x443300 sub_443300 —— 格式化串取目录前缀
// vsprintf 到 byte_97B598 后从尾部回找最后一个 \ 或 /，在分隔符后截断（保留尾分隔符，即取目录段）；
// 无分隔符则清首字节；末行回写全局串·sub_4015C0
// ------------------------------------------------------------
int sub_443300(int nArg1, char *Format, ...)
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
// 0x443370 sub_443370 —— 脚本 token 取串（第三入口）
// 型别 7 取默认串；9→10 取数值+串经 ·sub_529100 解析；空串防御 RDARScriptStringManager::ERROR::input NULL string
// 与 ·sub_442E10 同构（差异：赋值走 ·sub_4015C0）
// ------------------------------------------------------------
char sub_443370()
{
  int v0; // eax
  int v1; // eax
  char *psz; // eax

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
          psz = (char *)sub_529100(v1);
        else
          psz = "RDARScriptStringManager::ERROR::input NULL string";
        sub_4015C0(psz, strlen(psz));
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
// 0x443430 sub_443430 —— 读 token 到 string + 国家码标记
// 型别 5 直取字符串；11..13 取串后把首字节写 (型别-10)|0x80 国家码标记（·sub_442A80 定位首字节）
// ------------------------------------------------------------
char /*cdecl*/ sub_443430(std::_String_base *uArg1)
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
    *(uint8_t *)sub_442A80(uArg1, 0) = (v2 - 10) | 0x80;
    return 1;
  }
}



// ------------------------------------------------------------
// 0x4434C0 sub_4434C0 —— 红黑树整棵递归析构
// 后序递归：先 ·sub_4434C0 子树，再 ·sub_442D70 清 string 并 free 本节点；返回哨兵标志
// ------------------------------------------------------------
char /*stdcall*/ sub_4434C0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 45);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4434C0(i[2]);
    i = (void **)*i;
    sub_442D70((int)Block2);
    j__free(Block2);
    result = *((uint8_t *)i + 45);
  }
  return result;
}



// ------------------------------------------------------------
// 0x443510 sub_443510 —— 0x30 map 节点分配构造
// operator new(0x30) 后 ·sub_443240 构造五字段；分配失败返回空
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_443510(int nArg1, int nArg2, int nArg3, uint32_t *uArg4, char pszArg5)
{
  uint32_t *pMem; // esi
  void *v7[9]; // [esp+0h] [ebp-24h] BYREF

  v7[5] = v7;
  pMem = operator new(0x30u);
  v7[4] = pMem;
  v7[8] = (void *)1;
  v7[3] = pMem;
  if ( pMem != nullptr )
    sub_443240(pMem, nArg1, nArg2, nArg3, uArg4, pszArg5);
  return pMem;
}



// ------------------------------------------------------------
// 0x4435A0 sub_4435A0 —— 32 字节区间拷贝转发
// —— 与 ·sub_4432C0 同构（纯转发）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4435A0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  return sub_4432C0(uArg1, uArg2, uArg3);
}



// ------------------------------------------------------------
// 0x4435C0 sub_4435C0 —— 28 字节元素区间拷贝构造
// 逐元素就地初始化 string（容量 15/长度 0）再 ·sub_4014D0 拷贝，步长 28 —— 原始存储构造版
// ------------------------------------------------------------
int /*cdecl*/ sub_4435C0(int nArg1, int nArg2, int nArg3)
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
    {
      *(uint32_t *)(nArg32 + 24) = 15;
      *(uint32_t *)(nArg32 + 20) = 0;
      *(uint8_t *)(nArg32 + 4) = 0;
      sub_4014D0((std::_String_base *)nArg32, nArg1, 0, -1);
    }
    nArg32 += 28;
    LOBYTE(v7) = 0;
    nArg1 += 28;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x443660 sub_443660 —— 红黑树插入 + 再平衡
// 长度上限抛 map/set<T> too long；·sub_443510 造节点后按父/叔色双旋调平（·sub_442AC0 左旋 / ·sub_433290 右旋）；返回新节点
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_443660(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, uint32_t *uArg5)
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
  fld_e1 = sub_443510(*(this + 1), (int)pArg4, *(this + 1), uArg5, 0);
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
  if ( *(uint8_t *)(fld_e1[1] + 44) == 0 )
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
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 44) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x443810 sub_443810 —— 红黑树区间删除
// 全区间特例先整树递归析构；否则迭代推进逐节点 ·sub_442F60 摘除 —— erase(first,last) 实现
// ------------------------------------------------------------
int */*thiscall*/ sub_443810(int **this, int *pDwArg2, int nArg3, int nArg4)
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
    sub_4434C0(*(void ***)(fld_e1 + 4));
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
        if ( *(uint8_t *)(nArg32 + 45) == 0 )
        {
          v11 = *(uint32_t *)(nArg32 + 8);
          if ( *(uint8_t *)(v11 + 45) != 0 )
          {
            for ( i = *(uint32_t *)(nArg32 + 4); *(uint8_t *)(i + 45) == 0; i = *(uint32_t *)(i + 4) )
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
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 45) == 0; j = *(uint32_t *)j )
              nArg32 = j;
          }
        }
        sub_442F60(this, &nArg3, nArg322);
      }
      while ( nArg32 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4438D0 sub_4438D0 —— vector 清空析构
// ·sub_4166A0 区间元素析构后 free 块；三字段清零
// ------------------------------------------------------------
void /*thiscall*/ sub_4438D0(int *this)
{
  int fld_e1; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
  {
    sub_4166A0(fld_e1, *(this + 2));
    j__free((void *)*(this + 1));
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
}



// ------------------------------------------------------------
// 0x443920 sub_443920 —— 32 字节元素区间拷贝构造
// 逐元素拷 key（+0）并就地初始化+拷贝 string（+4），步长 32 —— 原始存储构造版
// ------------------------------------------------------------
int /*cdecl*/ sub_443920(uint32_t *uArg1, uint32_t *uArg2, int nArg3)
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( uArg1 != uArg2 )
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
    {
      *(uint32_t *)nArg32 = *uArg1;
      *(uint32_t *)(nArg32 + 28) = 15;
      *(uint32_t *)(nArg32 + 24) = 0;
      *(uint8_t *)(nArg32 + 8) = 0;
      sub_4014D0((std::_String_base *)(nArg32 + 4), uArg1 + 1, 0, -1);
    }
    nArg32 += 32;
    LOBYTE(v7) = 0;
    uArg1 += 8;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x4439F0 sub_4439F0 —— map 插入（重键返回既有）
// 下探定位（+3 键比较）后：键在则回既有节点、不在则 ·sub_443660 插入；出参 +4 标是否新插
// ------------------------------------------------------------
int /*thiscall*/ sub_4439F0(int *this, int pArg2, uint32_t *uArg3)
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
  if ( *((uint8_t *)v6 + 45) == 0 )
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
    while ( *((uint8_t *)v6 + 45) == 0 );
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_443660(this, &uArg3, 1, fld_e1, uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_501430(&uArg3);
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
    v12 = *sub_443660(this, &uArg3, v13, fld_e1, uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x443AB0 sub_443AB0 —— 60 字节元素 vector 赋值
// 三支路容量策略：源短则覆盖并析构余量；容量足则复用缓冲搬移；
// 不足则 ·sub_52AEF0 取上限校验（·sub_41D930）后新分配（·sub_416840）
// ------------------------------------------------------------
int /*thiscall*/ sub_443AB0(int this, int pArg2)
{
  int pArg22; // edi
  int v4; // eax
  unsigned int v5; // ecx
  std::_String_base *pThis_4; // ebx
  unsigned int fld_8; // eax
  std::_String_base *v9; // eax
  int v10; // eax
  unsigned int fld_C; // eax
  int v12; // edi
  int v13; // eax

  pArg22 = pArg2;
  if ( this == pArg2 )
    return this;
  v4 = *(uint32_t *)(pArg2 + 4);
  if ( v4 == 0 || (v5 = (*(uint32_t *)(pArg2 + 8) - v4) / 28) == 0 )
  {
    sub_4438D0((int *)this);
    return this;
  }
  pThis_4 = *(std::_String_base **)(this + 4);
  if ( pThis_4 != nullptr )
  {
    pArg22 = pArg2;
    fld_8 = (*(uint32_t *)(this + 8) - (int)pThis_4) / 28;
  }
  else
  {
    fld_8 = 0;
  }
  if ( v5 > fld_8 )
  {
    if ( pThis_4 != nullptr )
    {
      pArg22 = pArg2;
      fld_C = (*(uint32_t *)(this + 12) - (int)pThis_4) / 28;
    }
    else
    {
      fld_C = 0;
    }
    if ( v5 <= fld_C )
    {
      v12 = *(uint32_t *)(pArg2 + 4) + 28 * sub_52AEF0(this);
      sub_4432A0(*(uint32_t *)(pArg2 + 4), v12, pThis_4);
      *(uint32_t *)(this + 8) = sub_4166E0(v12, *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 8), this);
      return this;
    }
    if ( pThis_4 != nullptr )
    {
      sub_416820(pThis_4, *(uint32_t *)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v13 = sub_52AEF0(pArg22);
    if ( (uint8_t)sub_41D930(v13) != 0 )
      *(uint32_t *)(this + 8) = sub_416840(*(uint32_t *)(pArg22 + 4), *(uint32_t *)(pArg22 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  v9 = sub_442EB0(*(uint32_t *)(pArg22 + 4), *(uint32_t *)(pArg22 + 8), pThis_4);
  sub_4166A0(v9, *(uint32_t *)(this + 8));
  v10 = *(uint32_t *)(pArg22 + 4);
  if ( v10 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 28 * ((*(uint32_t *)(pArg22 + 8) - v10) / 28);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x443C40 sub_443C40 —— 脚本文件列表装表
// ·sub_442A10 读文件后逐对 token（·sub_4423D0 数值 + ·sub_443370 串）插 dword_97B22C map；
// 重键播报 SCRIPT FILE LIST LOAD FAIL!
// ------------------------------------------------------------
char /*cdecl*/ sub_443C40(int *pDwArg1, const char *ArgList, const char *pArg3)
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
  int dword_796E502; // [esp+4Ch] [ebp-10h]
  int v20; // [esp+58h] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_442A10(ArgList, pArg3);
  if ( result != 0 )
  {
    sub_4434C0(*(void ***)(pDwArg1[1] + 4));
    *(uint32_t *)(pDwArg1[1] + 4) = pDwArg1[1];
    v4 = (uint32_t *)pDwArg1[1];
    pDwArg1[2] = 0;
    *v4 = v4;
    *(uint32_t *)(pDwArg1[1] + 8) = pDwArg1[1];
    v18 = 15;
    v17 = 0;
    LOBYTE(v16) = 0;
    v20 = 0;
    v5 = sub_4423D0(&v14);
    for ( i = v5; v14 != 0; i = v5 )
    {
      if ( sub_443370() == 0 )
        break;
      if ( *sub_442D00((int **)pDwArg1, &v6, &i) == (int *)pDwArg1[1] )
      {
        v7 = v5;
        v11 = 15;
        v10 = 0;
        LOBYTE(Block) = 0;
        sub_4014D0((std::_String_base *)v8, v15, 0, -1);
        LOBYTE(v20) = 1;
        sub_4439F0(pDwArg1, (int)v12, &v7);
        LOBYTE(v20) = 0;
        if ( v11 >= 0x10 )
          j__free(Block);
        v11 = 15;
        v10 = 0;
        LOBYTE(Block) = 0;
      }
      else
      {
        off_77F3FC("SCRIPT FILE LIST LOAD FAIL! [%s%s][%d]", ArgList, pArg3, v5);
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
// 0x443DB0 sub_443DB0 —— vector 拷贝构造辅助（28 步长）
// 源区间按 28 字节步长构造：·sub_41D930 预检 → ·sub_4435C0 就地构造（·sub_4441E0 拷贝构造配套）
// ------------------------------------------------------------
int */*thiscall*/ sub_443DB0(int *this, int pArg2)
{
  int v2; // eax
  int v5; // [esp-14h] [ebp-34h]
  int v6; // [esp-10h] [ebp-30h]
  int fld_e1; // [esp-Ch] [ebp-2Ch]
  uint32_t v8[8]; // [esp+0h] [ebp-20h] BYREF

  v2 = *(uint32_t *)(pArg2 + 4);
  v8[4] = v8;
  v8[3] = this;
  if ( v2 != 0 )
    v2 = (*(uint32_t *)(pArg2 + 8) - v2) / 28;
  if ( (uint8_t)sub_41D930(v2) != 0 )
  {
    fld_e1 = *(this + 1);
    v6 = *(uint32_t *)(pArg2 + 8);
    v5 = *(uint32_t *)(pArg2 + 4);
    v8[7] = 0;
    *(this + 2) = sub_4435C0(v5, v6, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x443E50 sub_443E50 —— 32 字节 vector 赋值运算符
// 与 ·sub_443AB0 同构（差异：元素 32 字节，走 ·sub_421B80 / ·sub_422250 / ·sub_421C10 分配与区间拷贝）
// ------------------------------------------------------------
int */*thiscall*/ sub_443E50(int *this, int *pDwArg2)
{
  uint32_t *v3; // ebx
  unsigned int v4; // eax
  uint32_t *fld_e1; // ecx
  unsigned int fld_e2; // edx
  uint32_t *v8; // eax
  int v9; // eax
  int fld_e12; // edi
  unsigned int fld_e3; // edx
  int fld_e22; // eax
  uint32_t *v13; // ebx
  int v14; // ecx
  unsigned int v15; // eax

  if ( this == pDwArg2 )
    return this;
  v3 = (uint32_t *)pDwArg2[1];
  if ( v3 == nullptr || (v4 = (pDwArg2[2] - (int)v3) >> 5) == 0 )
  {
    sub_422340(this);
    return this;
  }
  fld_e1 = (uint32_t *)*(this + 1);
  if ( fld_e1 != nullptr )
    fld_e2 = (*(this + 2) - (int)fld_e1) >> 5;
  else
    fld_e2 = 0;
  if ( v4 <= fld_e2 )
  {
    v8 = sub_4432C0(v3, (uint32_t *)pDwArg2[2], fld_e1);
    sub_422220((int)v8, *(this + 2));
    v9 = pDwArg2[1];
    if ( v9 != 0 )
      fld_e12 = *(this + 1) + 32 * ((pDwArg2[2] - v9) >> 5);
    else
      fld_e12 = *(this + 1);
    *(this + 2) = fld_e12;
    return this;
  }
  if ( fld_e1 != nullptr )
    fld_e3 = (*(this + 3) - (int)fld_e1) >> 5;
  else
    fld_e3 = 0;
  if ( v4 > fld_e3 )
  {
    if ( fld_e1 != nullptr )
    {
      sub_422220((int)fld_e1, *(this + 2));
      j__free((void *)*(this + 1));
    }
    v14 = pDwArg2[1];
    if ( v14 != 0 )
      v15 = (pDwArg2[2] - v14) >> 5;
    else
      v15 = 0;
    if ( sub_421B80(this, v15) != 0 )
      *(this + 2) = sub_422250((uint32_t *)pDwArg2[1], (uint32_t *)pDwArg2[2], *(this + 1));
    return this;
  }
  if ( fld_e1 != nullptr )
    fld_e22 = (*(this + 2) - (int)fld_e1) >> 5;
  else
    fld_e22 = 0;
  v13 = (uint32_t *)(pDwArg2[1] + 32 * fld_e22);
  sub_4435A0((uint32_t *)pDwArg2[1], v13, (uint32_t *)*(this + 1));
  *(this + 2) = sub_421C10(v13, (uint32_t *)pDwArg2[2], *(this + 2));
  return this;
}



// ------------------------------------------------------------
// 0x443FB0 sub_443FB0 —— 60 字节 record 析构
// 依次析构成员：+44 vector（·sub_4166A0 区间析构 + free）、+28 vector（·sub_422340 32 字节整体析构）、
// +4 string（容量 ≥0x10 释放）
// ------------------------------------------------------------
void /*thiscall*/ sub_443FB0(int this)
{
  int fld_30; // eax
  int pThis_2C; // esi

  fld_30 = *(uint32_t *)(this + 48);
  pThis_2C = this + 44;
  if ( fld_30 != 0 )
  {
    sub_4166A0(fld_30, *(uint32_t *)(this + 52));
    j__free(*(void **)(pThis_2C + 4));
  }
  *(uint32_t *)(pThis_2C + 4) = 0;
  *(uint32_t *)(pThis_2C + 8) = 0;
  *(uint32_t *)(pThis_2C + 12) = 0;
  sub_422340((int *)(this + 28));
  if ( *(uint32_t *)(this + 24) >= 0x10u )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 15;
  *(uint8_t *)(this + 4) = 0;
}



// ------------------------------------------------------------
// 0x444020 sub_444020 —— map 整表清空
// ·sub_443810 erase(begin,end) 后 free header；容器三字段清零
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
// 0x444060 sub_444060 —— 32 字节 vector 拷贝构造
// 源计数除 32 → ·sub_421B80 预分配 → ·sub_443920 区间构造（·sub_4441E0 的 +28 成员配套）
// ------------------------------------------------------------
int */*thiscall*/ sub_444060(int *this, int pArg2)
{
  int v3; // ecx
  unsigned int v4; // eax
  uint32_t *v6; // [esp-14h] [ebp-34h]
  uint32_t *v7; // [esp-10h] [ebp-30h]
  int fld_e1; // [esp-Ch] [ebp-2Ch]
  uint32_t v9[8]; // [esp+0h] [ebp-20h] BYREF

  v3 = *(uint32_t *)(pArg2 + 4);
  v9[4] = v9;
  v9[3] = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 5;
  else
    v4 = 0;
  if ( sub_421B80(this, v4) != 0 )
  {
    fld_e1 = *(this + 1);
    v7 = *(uint32_t **)(pArg2 + 8);
    v6 = *(uint32_t **)(pArg2 + 4);
    v9[7] = 0;
    *(this + 2) = sub_443920(v6, v7, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x444100 sub_444100 —— 60 字节元素逆向区间拷贝
// 自尾向头逐元素：string 覆盖 + ·sub_443E50（+28 成员）+ ·sub_443AB0（+44 成员），步长 60
// ------------------------------------------------------------
int */*cdecl*/ sub_444100(int nArg1, int nArg2, int *pDwArg3)
{
  int nArg22; // esi
  int *pDwArg32; // edi

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return pDwArg3;
  pDwArg32 = pDwArg3;
  do
  {
    nArg22 -= 60;
    pDwArg32 -= 15;
    sub_4014D0((std::_String_base *)pDwArg32, nArg22, 0, -1);
    sub_443E50(pDwArg32 + 7, (int *)(nArg22 + 28));
    sub_443AB0((int)(pDwArg32 + 11), nArg22 + 44);
  }
  while ( nArg22 != nArg1 );
  return pDwArg32;
}



// ------------------------------------------------------------
// 0x444150 sub_444150 —— map 初始化（header 自环）
// ·sub_433B80 造 header 并置哨兵位；left/right/parent 自环、计数归零（空 map）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_444150(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *fld_e1; // eax

  v2 = sub_433B80();
  *(this + 1) = v2;
  *((uint8_t *)v2 + 45) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  sub_4434C0(*(void ***)(*(this + 1) + 4));
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  fld_e1 = (uint32_t *)*(this + 1);
  *(this + 2) = 0;
  *fld_e1 = fld_e1;
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  return this;
}



// ------------------------------------------------------------
// 0x4441E0 sub_4441E0 —— 60 字节 record 三段拷贝构造
// string（+0）+ 32 字节成员 vector（+28，·sub_444060）+ 28 步长成员 vector（+44，·sub_443DB0）
// ------------------------------------------------------------
int /*thiscall*/ sub_4441E0(int this, int nArg2)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((std::_String_base *)this, nArg2, 0, -1);
  sub_444060((int *)(this + 28), nArg2 + 28);
  sub_443DB0((int *)(this + 44), nArg2 + 44);
  return this;
}



// ------------------------------------------------------------
// 0x444260 sub_444260 —— 60 字节元素区间覆盖赋值
// 与 ·sub_444100 同构（差异：正向头到尾，三段走赋值语义）
// ------------------------------------------------------------
int */*cdecl*/ sub_444260(int *pDwArg1, int *pDwArg2, int pArg3)
{
  int *result; // eax
  int *i; // esi

  result = pDwArg2;
  for ( i = pDwArg1; i != pDwArg2; i += 15 )
  {
    sub_4014D0((std::_String_base *)i, pArg3, 0, -1);
    sub_443E50(i + 7, (int *)(pArg3 + 28));
    sub_443AB0((int)(i + 11), pArg3 + 44);
    result = pDwArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4442B0 sub_4442B0 —— 逆向区间拷贝转发
// —— 与 ·sub_444100 同构（纯转发）
// ------------------------------------------------------------
int */*cdecl*/ sub_4442B0(int nArg1, int nArg2, int *pDwArg3)
{
  return sub_444100(nArg1, nArg2, pDwArg3);
}



// ------------------------------------------------------------
// 0x4442D0 sub_4442D0 —— 60 字节元素区间构造
// 正向逐元素 ·sub_4441E0 拷贝构造，步长 60；返回尾指针
// ------------------------------------------------------------
int /*cdecl*/ sub_4442D0(int nArg1, int nArg2, int nArg3)
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
      sub_4441E0(nArg32, nArg1);
    nArg32 += 60;
    LOBYTE(v7) = 0;
    nArg1 += 60;
  }
  return nArg32;
}



// ============================================================
// 【分区 4】CNMainGameModule 虚表槽（0x444360-0x444E70）
// vmt8=0x444C20 模块退出清理 / vmt4=0x444C60 每帧 tick（模块心跳）。
// 两函数已由 docs/13 §1 定案并 L1 逐行精修于 src/game/module/CNMainGameModule.cpp
// （vmt4 流程：帧钩→场景推进→震动档→fade 状态机→发包 type=40），此处保留 L2 转写体。
// ============================================================
// ------------------------------------------------------------
// 0x444360 sub_444360 —— 60 字节填值构造 N 个
// 以 nArg3 为源重复 ·sub_4441E0 共 nArg2 次（fill-construct），返回尾指针
// ------------------------------------------------------------
int /*cdecl*/ sub_444360(int nArg1, int nArg2, int nArg3)
{
  int nArg12; // esi
  int result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg12 = nArg1;
  v6[4] = v6;
  v6[3] = nArg1;
  v7 = 0;
  while ( nArg2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( nArg12 != 0 )
      result = sub_4441E0(nArg12, nArg3);
    --nArg2;
    nArg12 += 60;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4443F0 sub_4443F0 —— 60 字节填充 + 尾指针公式
// ·sub_444360 填充后返回 begin + 60*count —— 尾部地址包装
// ------------------------------------------------------------
int /*stdcall*/ sub_4443F0(int nArg1, int nArg2, int nArg3)
{
  sub_444360(nArg1, nArg2, nArg3);
  return nArg1 + 60 * nArg2;
}



// ------------------------------------------------------------
// 0x444420 sub_444420 —— 60 字节元素区间析构
// 逐元素 ·sub_443FB0 析构，步长 60
// ------------------------------------------------------------
void /*stdcall*/ sub_444420(int nArg1, int nArg2)
{
  int i; // esi

  for ( i = nArg1; i != nArg2; i += 60 )
    sub_443FB0(i);
}



// ------------------------------------------------------------
// 0x444450 sub_444450 —— 60 字节 vector 单元素插入（_Insert_n）
// 先构造 nArg4 临时副本 v27；容量足则原位后移（·sub_4442D0 搬移 / ·sub_4442B0 后向拷 / ·sub_444260 赋值，
// 跨界走 ·sub_4443F0 填充），不足则按 1.5 倍增长重分配（·sub_4429C0 取长）；末尾 ·sub_443FB0 析构临时
// ------------------------------------------------------------
int /*thiscall*/ sub_444450(int *this, int pArg2, unsigned int uArg3, int nArg4)
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
  int fld_e12; // [esp-18h] [ebp-80h]
  int fld_e28; // [esp-10h] [ebp-78h]
  int fld_e25; // [esp-Ch] [ebp-74h]
  unsigned int fld_e24; // [esp-8h] [ebp-70h]
  uint32_t v24[4]; // [esp+0h] [ebp-68h] BYREF
  void *Block; // [esp+10h] [ebp-58h]
  char *pMem2; // [esp+14h] [ebp-54h]
  uint8_t v27[60]; // [esp+18h] [ebp-50h] BYREF
  int dword_796E502; // [esp+54h] [ebp-14h]
  uint32_t *v29; // [esp+58h] [ebp-10h]
  int v30; // [esp+64h] [ebp-4h]
  char *v31; // [esp+70h] [ebp+8h]
  int v32; // [esp+74h] [ebp+Ch]

  dword_796E502 = dword_796E50;
  v29 = v24;
  v24[3] = this;
  sub_4441E0(nArg4);
  fld_e1 = *(this + 1);
  fld_e3 = 0;
  v30 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 60;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - *(this + 1)) / 60;
    else
      fld_e2 = 0;
    if ( 71582788 - fld_e2 < uArg3 )
      sub_442EF0(this);
    if ( *(this + 1) != 0 )
      fld_e22 = (*(this + 2) - *(this + 1)) / 60;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (char *)*(this + 2);
      Block = fld_e23;
      if ( (int)&fld_e23[-pArg2] / 60 >= uArg3 )
      {
        v31 = &fld_e23[-60 * uArg3];
        *(this + 2) = sub_4442D0(v31, fld_e23, fld_e23);
        sub_4442B0(pArg2, v31, Block);
        sub_444260(pArg2, pArg2 + 60 * uArg3, v27);
      }
      else
      {
        sub_4442D0(pArg2, fld_e23, pArg2 + 60 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 60;
        fld_e25 = *(this + 2);
        LOBYTE(v30) = 3;
        sub_4443F0(fld_e25, fld_e24, v27);
        fld_e26 = 60 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v30 = 0;
        sub_444260(pArg2, fld_e26 - 60 * uArg3, v27);
      }
    }
    else
    {
      if ( 71582788 - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        fld_e27 = (*(this + 2) - *(this + 1)) / 60;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_4429C0(this);
      v32 = 60 * v10;
      pMem = (char *)operator new(60 * v10);
      fld_e12 = *(this + 1);
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v30) = 1;
      pMem2 = (char *)sub_4442D0(fld_e12, pArg2, pMem);
      sub_444360(pMem2, uArg3, v27);
      fld_e28 = *(this + 2);
      pMem2 += 60 * uArg3;
      sub_4442D0(pArg2, fld_e28, pMem2);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 60;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);
      if ( fld_e14 != 0 )
      {
        sub_444420(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v32];
      *(this + 2) = (int)&pMem[60 * v14];
      *(this + 1) = (int)pMem;
    }
  }
  return sub_443FB0(v27);
}


// ------------------------------------------------------------
// 0x444770 sub_444770 —— vector 迭代器位置插入
// 先算索引 (pDwArg3 - begin)/60 → ·sub_444450 插入 → *uArg2 回填新元素地址
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_444770(int *this, uint32_t *uArg2, int *pDwArg3, int nArg4)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 60 != 0 )
    v6 = ((int)pDwArg3 - fld_e1) / 60;
  else
    v6 = 0;
  sub_444450(this, pDwArg3, 1u, nArg4);
  *uArg2 = *(this + 1) + 60 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4447E0 sub_4447E0 —— 60 字节 vector 整体清空
// 逐元素 ·sub_443FB0 析构 + free 块；三字段清零
// ------------------------------------------------------------
int /*thiscall*/ sub_4447E0(int *this)
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);
  result = 0;
  if ( fld_e1 != 0 )
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 60 )
      sub_443FB0(fld_e1);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x444820 sub_444820 —— 60 字节 vector emplace_back
// 容量未满：尾部就地构造；已满：·sub_444770 扩容插入；返回新元素地址
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_444820(int this, int nArg2)
{
  int fld_4; // ebx
  unsigned int fld_8; // esi
  int fld_82; // esi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 60;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 60 )
    return sub_444770((int *)this, &nArg2, *(int **)(this + 8), nArg2);
  fld_82 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_444360(fld_82, 1, nArg2);
  *(uint32_t *)(this + 8) = fld_82 + 60;
  return result;
}



// ------------------------------------------------------------
// 0x4448B0 sub_4448B0 —— 脚本条目表宿主初始化
// ·sub_444150 建空 map 后清 +16/+20/+24（即 +12 处 60 字节 vector 三字段）—— ·sub_444930 装载宿主
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
// 0x444930 sub_444930 —— 装载单个脚本条目
// ·sub_5297C0（PVF）或 ·sub_529920（磁盘）解出条目；成功 ·sub_444820 push 到 +12 vector 返回 1；
// 错误码 -1/-2/-3 播报 aErrorAddstring 系列
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
  int dword_796E502; // [esp+44h] [ebp-10h]
  int v15; // [esp+50h] [ebp-4h]

  dword_796E502 = dword_796E50;
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
// 0x444A40 sub_444A40 —— 脚本目录批量装载
// ·sub_443C40 先读列表（键源 szPassword）；逐条拼前缀（PVF 态 szPassword / 磁盘态 Script/）后 ·sub_444930 装载；
// 失败返回 0
// ------------------------------------------------------------
char /*cdecl*/ sub_444A40(const char *pArg1)
{
  const char *v1; // edi
  char result; // al
  int dword_97B2342; // ebx
  int v4; // esi
  const char *v5; // eax
  int v6; // [esp+4h] [ebp-20Ch] BYREF
  int *v7; // [esp+8h] [ebp-208h] BYREF
  char Buffer[512]; // [esp+Ch] [ebp-204h] BYREF
  int dword_796E502; // [esp+20Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  v1 = "Script/";
  if ( byte_78FF3C != 0 )
    v1 = szPassword;
  result = sub_443C40((int *)&dword_97B22C, szPassword, pArg1);
  if ( result != 0 )
  {
    dword_97B2342 = dword_97B234;
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
        if ( ++v4 >= dword_97B2342 )
          return 1;
      }
      return 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x444B30 sub_444B30 —— fade 状态机复位
// 写 fade 状态（+20）= nArg2、复位 +24 计时器与 +60 alpha；CNMainGameModule::vmt4 case 3 淡出支调用
// ------------------------------------------------------------
char /*thiscall*/ sub_444B30(uint32_t *this, int nArg2)
{
  int pThis_6; // ecx
  char result; // al

  pThis_6 = (int)(this + 6);
  *(this + 5) = nArg2;
  *(uint8_t *)(pThis_6 + 13) = 0;
  *(uint8_t *)(pThis_6 + 14) = 0;
  result = sub_698F90(pThis_6, 0, 0);
  *(this + 15) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x444B60 sub_444B60 —— 未激活态字段复位
// +4 为 0 时清 +12/+16/+20/+52/+56/+60 与旗标；复位 97B698/97B6B4 两个 100ms 计时器和 +92 时钟后冻结（·sub_699030）
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
// 0x444BE0 sub_444BE0 —— 激活态复位
// +4 非 0 时清 +20/+37/+38、复位 +24 与 +60；把 +16 对象数字缩放写 1.0（·sub_424EA0）
// ------------------------------------------------------------
char /*thiscall*/ sub_444BE0(int this)
{
  char result; // al
  float *fld_10; // ecx

  result = *(uint8_t *)(this + 4);
  if ( result != 0 )
  {
    *(uint32_t *)(this + 20) = 0;
    *(uint8_t *)(this + 37) = 0;
    *(uint8_t *)(this + 38) = 0;
    sub_698F90(this + 24, 0, 0);
    fld_10 = *(float **)(this + 16);
    *(uint32_t *)(this + 60) = 0;
    return sub_424EA0(fld_10, 1.0);
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
  int pThis_5C; // eax
  int fld_78; // edx
  uint64_t v5; // rax
  int pThis_18; // eax
  int pThis_182; // eax
  int pThis_183; // eax
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
    pThis_5C = sub_699000(this + 92);
    fld_78 = *(uint32_t *)(this + 120);
    *(uint32_t *)(this + 120) = pThis_5C;
    v10 = (double)(pThis_5C - fld_78) * 0.001;
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
          pThis_18 = sub_699000(this + 24);
          v5 = (uint64_t)sub_4049C0(0.0, 255.0, pThis_18, 250);
          *(uint32_t *)(this + 60) = v5;
          *((uint32_t *)dword_8F8528 + 621) = v5;
        }
        break;
      case 2:
LABEL_27:
        break;
      case 3:
        pThis_182 = sub_699000(this + 24);
        v5 = (uint64_t)sub_4049C0(255.0, 0.0, pThis_182, 250);
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
          pThis_183 = sub_699000(this + 24);
          LODWORD(v5) = sub_423A80(0, 255, pThis_183, 500);
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
// 0x444E70 sub_444E70 —— fade 启动 + 播放广播
// 置 +20=1、记 +52/+56、复位 +24 与 +60；进临界区 ·sub_65DC70 后 ·sub_425960(1) 级联播放广播（+16 对象 +44/+104 两表）
// ------------------------------------------------------------
char /*thiscall*/ sub_444E70(uint32_t *this, int nArg2, int nArg3)
{
  int pThis_6; // ecx

  *(this + 14) = nArg3;
  pThis_6 = (int)(this + 6);
  *(this + 13) = nArg2;
  *(this + 5) = 1;
  *(uint8_t *)(pThis_6 + 13) = 0;
  *(uint8_t *)(pThis_6 + 14) = 0;
  sub_698F90(pThis_6, 0, 0);
  *(this + 15) = 0;
  sub_65DC70(lpCriticalSection);
  return sub_425960(1, *(uint32_t *)(*(this + 4) + 44), *(int ***)(*(this + 4) + 104));
}



// ------------------------------------------------------------
// 0x444ED0 sub_444ED0 —— fade 收尾（暂停广播）
// ·sub_425960(0) 暂停广播后状态 +20 置 3，复位 +24/+60
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
// 0x444F10 sub_444F10 —— 激活对象释放
// 置 +4=0；虚调首槽释放 +12 对象；+16 走 ·sub_42BD40（CNRDStage 析构）后 free
// ------------------------------------------------------------
void /*thiscall*/ sub_444F10(int this)
{
  void (/*thiscall*/ ***pThis_C)(uint32_t, int); // ecx
  void *fld_10; // edi

  if ( *(uint8_t *)(this + 4) != 0 )
  {
    pThis_C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);
    *(uint8_t *)(this + 4) = 0;
    if ( pThis_C != nullptr )
      (**pThis_C)(pThis_C, 1);
    fld_10 = *(void **)(this + 16);
    *(uint32_t *)(this + 12) = 0;
    if ( fld_10 != nullptr )
    {
      sub_42BD40((int)fld_10);
      j__free(fld_10);
    }
    *(uint32_t *)(this + 16) = 0;
  }
}



// ------------------------------------------------------------
// 0x444F60 sub_444F60 —— 激活初始化（控件 + 场景）
// 置 +4=1；new 0x68 经 ·sub_426BD0（IControl 构造）存 +12 并回写宿主指针；new 0x558 经 ·sub_42B7E0（CNRDStage 构造）存 +16
// 并 ·sub_69A840 登记各纹理对象；随后复位 +24/+60 与缩放 1.0
// ------------------------------------------------------------
char /*thiscall*/ sub_444F60(int this)
{
  char result; // al
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  char *pMem2; // eax
  char *v6; // eax
  float *fld_10; // ecx

  result = *(uint8_t *)(this + 4);
  if ( result == 0 )
  {
    *(uint8_t *)(this + 4) = 1;
    pMem = operator new(0x68u);
    if ( pMem != nullptr )
      v4 = sub_426BD0(pMem);
    else
      v4 = nullptr;
    *(uint32_t *)(this + 12) = v4;
    *((uint32_t *)v4 + 17) = this + 8;
    pMem2 = (char *)operator new(0x558u);
    if ( pMem2 != nullptr )
      v6 = sub_42B7E0(pMem2);
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
      fld_10 = *(float **)(this + 16);
      *(uint32_t *)(this + 60) = 0;
      return sub_424EA0(fld_10, 1.0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x445080 sub_445080 —— 槽位表值查询
// ·sub_656710()[pArg2] 为 -1 未启用返回 0；否则取 this[pArg2 + 262162]（+1048648 槽位状态表）
// ------------------------------------------------------------
int /*thiscall*/ sub_445080(uint32_t *this, int pArg2)
{
  if ( *(uint32_t *)(sub_656710() + 4 * pArg2) == -1 )
    return 0;
  else
    return *(this + pArg2 + 262162);
}



// ------------------------------------------------------------
// 0x4450B0 sub_4450B0 —— 计数器加值
// ·sub_41A5E0 读后 + nArg2 经 ·sub_41A590 写回并返回新值【推断】（与 ·sub_4450E0 同族）
// ------------------------------------------------------------
int /*thiscall*/ sub_4450B0(void *this, int nArg2)
{
  int v3; // esi
  int v4; // edx

  v3 = nArg2 + sub_41A5E0((unsigned int)this);
  sub_41A590((unsigned int)this, v4, v3);
  return v3;
}



// ------------------------------------------------------------
// 0x4450E0 sub_4450E0
// ------------------------------------------------------------
// 分发器 case 0x18 落点：场景级事件处理【推断】
int /*thiscall*/ sub_4450E0(void *this)
{
  unsigned int pThis_94; // esi
  int pThis_942; // eax
  int v3; // edx

  pThis_94 = (unsigned int)this + 148;
  pThis_942 = sub_41A5E0((unsigned int)this + 148);
  return sub_41A590(pThis_94, v3, pThis_942 + 1);
}



// ------------------------------------------------------------
// 0x445100 sub_445100 —— 释放转发
// —— 转发 ·sub_657740（按尺寸释放）
// ------------------------------------------------------------
int /*cdecl*/ sub_445100(int nArg1, int nArg2)
{
  return sub_657740(nArg1, nArg2);
}



// ------------------------------------------------------------
// 0x445120 sub_445120
// ------------------------------------------------------------
// 分发器 case 0x14 落点：命中侧查询（返回真走 sub_495470(+v174[1668]) 分支）
BOOL /*thiscall*/ sub_445120(int *this)
{
  int fld_e1639; // eax

  fld_e1639 = *(this + 1639);
  return fld_e1639 == 4 || fld_e1639 == 9 || *(this + 81) <= 0 && (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) > 0;
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
char /*thiscall*/ sub_4451C0(uint8_t *this, char pszArg2)
{
  int pThis_21C; // ecx

  *(this + 552) = pszArg2;
  pThis_21C = (int)(this + 540);
  *(uint8_t *)(pThis_21C + 13) = 0;
  *(uint8_t *)(pThis_21C + 14) = 0;
  return sub_698F90(pThis_21C, 1500, 0);
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
// 0x4451F0 CNRDUdpModule__vmtA8 —— 网络模块大复位
// 删 UDP.log/PACKET.log；清 +1048596 起全部统计字段、45×4 计数块与各标志（+1048645 置 1）；vmt 槽 A8
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmtA8(int this)
{
  int result; // eax
  uint32_t *pThis_100344; // ecx
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
  pThis_100344 = (uint32_t *)(this + 1049412);
  for ( i = 45; i != 0; --i )
  {
    *(pThis_100344 - 45) = 0;
    *pThis_100344 = 0;
    pThis_100344[45] = 0;
    pThis_100344[90] = 0;
    ++pThis_100344;
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
// 0x445320 CNRDUdpModule__vmtAC —— 网络对象重建
// 复位 +1048604 计时器；new 0xA00 后 ·sub_657410(this+1) 构造网络对象存 +1049988【推断】；vmt 槽 AC
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmtAC(uint32_t *this)
{
  int pThis_40007; // ecx
  int result; // eax

  pThis_40007 = (int)(this + 262151);
  *(uint8_t *)(pThis_40007 + 13) = 0;
  *(uint8_t *)(pThis_40007 + 14) = 0;
  sub_698F90(pThis_40007, 0, 0);
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
// 0x4453B0 CNRDUdpModule__vmtB0 —— 套接字关闭
// ·sub_6676C0 后 closesocket(网络对象 +2492) 并置 -1；vmt 槽 B0
// ------------------------------------------------------------
char /*thiscall*/ CNRDUdpModule__vmtB0(uint32_t *this)
{
  int fld_e262497; // esi

  fld_e262497 = *(this + 262497);
  sub_6676C0();
  if ( *(uint32_t *)(fld_e262497 + 2492) != -1 )
  {
    closesocket(*(uint32_t *)(fld_e262497 + 2492));
    *(uint32_t *)(fld_e262497 + 2492) = -1;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x4453C0 CNRDUdpModule__vmt8 —— 发包一步（类型 + 标志）
// vtbl+20 清/备包 → 包对象 +1048588 写 int16 类型与首字节标志 → vtbl+12 提交（指针 +7 越过包头）；vmt 槽 8
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt8(uint32_t *this, int16_t uArg2, char pszArg3)
{
  int fld_e262147; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 20))(this);
  fld_e262147 = *(this + 262147);
  *(uint16_t *)(fld_e262147 + 1) = uArg2;
  *(uint8_t *)fld_e262147 = pszArg3;
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 12))(this, *(this + 262147) + 7);
}



// ------------------------------------------------------------
// 0x445400 CNRDUdpModule__vmt3C —— UDP 发包主流程
// SEND %d %d 日志；长度=vtbl+16-7 上做 ·sub_48BE40 校验和与 ·sub_48BD40 加扰；按包型 0/1/2 经 ·sub_656EF0 发送；
// 含 8 槽位特权循环与 ·sub_445080 表值判定；vmt 槽 3C
// ------------------------------------------------------------
char /*userpurge*/ sub_445400@<al>(int pArg1@<ecx>, int nArg2@<edi>, void *pArg3, void *Block)
{
  int v5; // eax
  uint8_t *v6; // ebx
  int v7; // edi
  void *Block2; // ecx
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
  void *Block22; // [esp-Ch] [ebp-18h]
  int v22; // [esp-8h] [ebp-14h]
  int v24; // [esp+8h] [ebp-4h]
  uint32_t *Blocka; // [esp+18h] [ebp+Ch]

  LOWORD(v5) = *(uint16_t *)(pArg1 + 13);
  v6 = (uint8_t *)(pArg1 + 12);
  if ( (uint16_t)v5 == 0 || *(uint8_t *)(pArg1 + 1048645) != 0 )
  {
    (*(void (**)(int, const char *, ...))(*(uint32_t *)pArg1 + 140))(pArg1, "SEND %d %d", (uint16_t)v5, *v6);
    if ( (*v6 == 1 || *v6 == 2) && (uint8_t)pArg3 != 0 )
    {
      *(uint8_t *)(pArg1 + 1049217) = 0;
      *(uint8_t *)(pArg1 + 1049218) = 0;
      sub_698F90(pArg1 + 1049204, 0, 0);
    }
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 16))(pArg1) - 7;
    *(uint32_t *)(v6 + 3) = sub_48BE40(pArg1 + 19, v7);
    sub_48BD40(pArg1 + 19, v7, 0);
    if ( *(uint16_t *)(v6 + 1) == 0 )
    {
      Block2 = Block;
LABEL_9:
      v22 = (uint8_t)pArg3;
      Block22 = Block2;
LABEL_10:
      v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 16))(pArg1);
LABEL_11:
      v18 = v9;
      sub_656710(v6);
      LOBYTE(v5) = sub_656EF0(v17, v18, Block22, v22);
      return v5;
    }
    if ( *(int *)(pArg1 + 1048600) > 0 )
    {
      LOBYTE(v5) = *v6;
      if ( *v6 != 0 )
      {
        if ( (uint8_t)v5 != 1 )
        {
          if ( (uint8_t)v5 != 2 )
            return v5;
          v22 = (int)Block;
          Block22 = pArg3;
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 136))(pArg1);
          v12 = sub_656710((uint8_t)pArg3);
          v13 = sub_656840(v12);
          v9 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 16))(pArg1, v13, v19);
          goto LABEL_11;
        }
      }
      else
      {
        v10 = sub_656710(nArg2);
        v11 = (void *)sub_656840(v10);
        Block2 = Block;
        if ( Block == v11 )
          goto LABEL_9;
      }
      LOBYTE(v5) = (*(int (/*thiscall*/ **)(int, void *, void *))(*(uint32_t *)pArg1 + 136))(pArg1, pArg3, Block);
      return v5;
    }
    if ( *v6 == 0 )
    {
      v5 = sub_445080(Block);
      if ( v5 != 0 )
        return v5;
      v22 = (uint8_t)pArg3;
      Block22 = Block;
      goto LABEL_10;
    }
    v14 = ((int (*)(void))sub_656710)();
    v24 = sub_656840(v14);
    LOBYTE(v5) = pArg1 + 72;
    v15 = 0;
    Blocka = (uint32_t *)(pArg1 + 1048648);
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
            v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 16))(pArg1);
            ((void (*)(void))sub_656710)();
            LOBYTE(v5) = sub_656EF0((int)v6, v20, (void *)v15, (uint8_t)pArg3);
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
// 0x4455F0 CNRDUdpModule__vmt5C —— 双槽提交
// vtbl+80 取一值 v5 → vtbl+88(nArg2, v5) 二次提交并返回 v5；vmt 槽 5C
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt5C(int *this, int nArg2)
{
  int v3; // eax
  int v5; // [esp+4h] [ebp-4h] BYREF

  v3 = *this;
  v5 = 0;
  (*(void (/*thiscall*/ **)(int *, int *))(v3 + 80))(this, &v5);
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 88))(this, nArg2, v5);
  return v5;
}



// ------------------------------------------------------------
// 0x445630 CNRDUdpModule__vmt60 —— 取缓冲并补串尾
// vtbl+92(this, nArg2) 取指针后在 +nArg2 处写 0 —— 定长字段 NUL 收尾；vmt 槽 60
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt60(void *this, int nArg2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 92))(this, nArg2);
  *(uint8_t *)(result + nArg2) = 0;
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
int /*thiscall*/ sub_4456C0(void *this, int pArg2, int nArg3, char pszArg4)
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
    v6 = sub_48F690(pArg2);
    result = sub_48F5A0();
  }
  else if ( result == 6 )
  {
    if ( dword_99FF08 == 0 )
      return result;
    v6 = sub_578E80(pArg2);
    result = sub_48FCA0();
  }
  else
  {
    v6 = *(uint32_t *)(dword_8F850C + 4 * pArg2 + 16);
    result = sub_456420(dword_8F850C);
  }
  v7 = result;
  if ( v6 != 0 && result != -1 )
  {
    (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t))(*(uint32_t *)this + 8))(this, 0, 0);
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 32))(this, v7);
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 32))(this, nArg3);
    if ( pszArg4 != 0 )
      (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 32))(this, 1);
    else
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 32))(this, 0);
    v8 = *(uint32_t *)dword_8F8520;
    if ( nArg3 == 2 )
      return (*(int (/*stdcall*/ **)(int, int))(v8 + 60))(1, pArg2);
    else
      return (*(int (/*stdcall*/ **)(uint32_t, int))(v8 + 60))(0, pArg2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4457A0 CNRDUdpModule__vmt68 —— 命令派发链
// ·sub_656710 上下文 → ·sub_6568C0 设置 → ·sub_656560 落地；vmt 槽 68
// ------------------------------------------------------------
int /*stdcall*/ CNRDUdpModule__vmt68(int nArg1)
{
  int v2; // [esp-4h] [ebp-8h]

  sub_656710(nArg1);
  sub_6568C0(v2);
  return sub_656560(nArg1);
}



// ------------------------------------------------------------
// 0x4457D0 sub_4457D0 —— 旗标置位 + PVP 通知
// 写 +1048645 旗标；场景 == 4（PVP）时通知 ·sub_52AF20
// ------------------------------------------------------------
char /*thiscall*/ sub_4457D0(uint8_t *this, char pszArg2)
{
  char result; // al

  result = pszArg2;
  *(this + 1048645) = pszArg2;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
    return sub_52AF20(*((uint32_t *)dword_8F8528 + 8));
  return result;
}



// ------------------------------------------------------------
// 0x445800 CNRDUdpModule__vmt7C —— 模块上下文指针写回
// 存上下文于 +1048596；非空时取 +44 对象的 +356 写全局 dword_9A012C（对局信息）；vmt 槽 7C
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt7C(uint32_t *this, int pArg2)
{
  int result; // eax

  result = pArg2;
  *(this + 262149) = pArg2;
  if ( pArg2 != 0 )
  {
    result = *(uint32_t *)(pArg2 + 44);
    if ( result != 0 )
    {
      result = *(uint32_t *)(result + 356);
      dword_9A012C = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x445830 sub_445830 —— 槽快照区复位
// 写 +1048944 旗标；置位时清 8 组 28 字节记录（两标志位 + 计时器复位）
// ------------------------------------------------------------
char /*thiscall*/ sub_445830(uint8_t *this, char pszArg2)
{
  char result; // al
  uint8_t *pThis_100182; // esi
  int i; // edi

  result = pszArg2;
  *(this + 1048944) = pszArg2;
  if ( pszArg2 != 0 )
  {
    pThis_100182 = this + 1048962;
    for ( i = 8; i != 0; --i )
    {
      *(pThis_100182 - 1) = 0;
      *pThis_100182 = 0;
      result = sub_698F90((int)(pThis_100182 - 14), 0, 0);
      pThis_100182 += 28;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x445870 sub_445870 —— 槽表随机数
// 基址 +1049984 + 10*槽号 经 ·sub_4D33A0 取值；nArg3 非 0 时取模【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_445870(uint32_t *this, int nArg2, int nArg3)
{
  int nArg32; // esi

  nArg32 = nArg3;
  nArg2 = *(this + 262496) + 10 * nArg2;
  if ( nArg3 != 0 )
    return sub_4D33A0(&nArg2) % nArg32;
  else
    return sub_4D33A0(&nArg2);
}



// ------------------------------------------------------------
// 0x4458C0 sub_4458C0 —— 网络对象连接初始化
// ·sub_6572C0 探测网络对象，未就绪返回 0；就绪取 ·sub_656800 上下文后 ·sub_657670 绑定到 +1049988【推断】
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
// 0x4458F0 sub_4458F0 —— 标签任务清扫调度
// 标签对象 +8 命中当前上下文（·sub_656800）走清扫分支（Concurrency::SweepUnstructured 为符号误认），
// 否则 ·sub_40BE20 摘链【推断】
// ------------------------------------------------------------
void /*stdcall*/ sub_4458F0(bool (/*cdecl*/ *uArg1)(struct Concurrency::details::_UnrealizedChore *, void *), void *pArg2)
{
  int v2; // edi
  Concurrency::details::ContextBase *v3; // eax
  bool (/*cdecl*/ *v4)(struct Concurrency::details::_UnrealizedChore *, void *); // [esp+0h] [ebp-8h]

  sub_656710();
  v2 = *((uint32_t *)uArg1 + 2);
  if ( v2 == sub_656800() )
  {
    v3 = (Concurrency::details::ContextBase *)sub_656710();
    Concurrency::details::ContextBase::SweepUnstructured(v3, uArg1, pArg2, v4);
  }
  else
  {
    sub_40BE20((char *)&byte_6C6044, *((uint32_t *)uArg1 + 1));
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
// 0x445960 sub_445960 —— 四槽状态快照刷新
// 置 +1050008=1；复位 +1049996 计时器（周期 dword_78FF60）；按场景取 4 槽通道对象（4→·sub_48F690 / 6→·sub_578E80 / 其余上下文表），
// 把通道 +12 与 +172(+10) 抓入快照表
// ------------------------------------------------------------
void /*thiscall*/ sub_445960(uint8_t *this)
{
  int pThis_10058C; // ecx
  int v3; // ebx
  int v4; // ecx
  uint32_t *pThis_1005C8; // edi
  int v6; // eax
  int v7; // esi
  Concurrency::details::ContextBase *v8; // eax
  char v9; // al
  void *v10; // [esp+0h] [ebp-10h]
  bool (/*cdecl*/ *v11)(struct Concurrency::details::_UnrealizedChore *, void *); // [esp+4h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-4h]

  pThis_10058C = (int)(this + 1049996);
  *(uint8_t *)(pThis_10058C + 13) = 0;
  *(uint8_t *)(pThis_10058C + 14) = 0;
  *(this + 1050008) = 1;
  sub_698F90(pThis_10058C, dword_78FF60, 0);
  v3 = 0;
  v4 = -1050040 - (uint32_t)this;
  pThis_1005C8 = this + 1050056;
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
      v7 = *(uint32_t *)((char *)pThis_1005C8 + v4 + dword_8F850C);
    }
    if ( v7 != 0 )
    {
      *(pThis_1005C8 - 8) = *(uint32_t *)(v7 + 12);
      v8 = (Concurrency::details::ContextBase *)sub_656710();
      Concurrency::details::ContextBase::SweepUnstructured(
        v8,
        (bool (/*cdecl*/ *)(struct Concurrency::details::_UnrealizedChore *, void *))v3,
        v10,
        v11);
      if ( v9 != 0 )
        *pThis_1005C8 = *(uint32_t *)(v7 + 172) + 10;
      else
        *pThis_1005C8 = *(uint32_t *)(v7 + 172);
    }
LABEL_14:
    ++v3;
    ++pThis_1005C8;
    if ( v3 >= 4 )
      break;
  }
}



// ------------------------------------------------------------
// 0x445A30 sub_445A30 —— 组包命令 39
// vtbl+8(39, 2) 开命令 → vtbl+40(nArg2) 写参 → vtbl+60(1, -1) 提交；宿主 this-2（CNRDStage 族）【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_445A30(uint32_t *this, int nArg2)
{
  char *pObj; // esi

  pObj = (char *)(this - 2);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*(this - 2) + 8))(this - 2, 39, 2);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)pObj + 40))(pObj, nArg2);
  return (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)pObj + 60))(pObj, 1, -1);
}



// ------------------------------------------------------------
// 0x445A60 sub_445A60 —— 组包命令 40
// —— 与 ·sub_445A30 同构（差异：命令号 40，末参 nArg2 直走 vtbl+60）
// ------------------------------------------------------------
int /*thiscall*/ sub_445A60(uint32_t *this, int nArg2)
{
  char *pObj; // esi

  pObj = (char *)(this - 2);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*(this - 2) + 8))(this - 2, 40, 0);
  return (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)pObj + 60))(pObj, 1, nArg2);
}



// ------------------------------------------------------------
// 0x445A90 sub_445A90 —— 组包命令 41
// —— 与 ·sub_445A30 同构（差异：命令号 41）
// ------------------------------------------------------------
int /*thiscall*/ sub_445A90(uint32_t *this, int nArg2)
{
  char *pObj; // esi

  pObj = (char *)(this - 2);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*(this - 2) + 8))(this - 2, 41, 2);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)pObj + 40))(pObj, nArg2);
  return (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)pObj + 60))(pObj, 1, -1);
}



// ------------------------------------------------------------
// 0x445AC0 sub_445AC0 —— 组包命令 42
// —— 与 ·sub_445A60 同构（差异：命令号 42）【推断：39..44 连号命令族】
// ------------------------------------------------------------
int /*thiscall*/ sub_445AC0(uint32_t *this, int nArg2)
{
  char *pObj; // esi

  pObj = (char *)(this - 2);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*(this - 2) + 8))(this - 2, 42, 0);
  return (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)pObj + 60))(pObj, 1, nArg2);
}



// ------------------------------------------------------------
// 0x445AF0 sub_445AF0 —— 组包命令 43
// vtbl+8(43,2) → vtbl+32(nArg2) 存对象引用 → vtbl+52 以 4 字节整块写 ·pszArg3 → vtbl+60(1,-1) 提交
// ------------------------------------------------------------
int /*thiscall*/ sub_445AF0(uint32_t *this, int nArg2, char pszArg3)
{
  char *pObj; // esi

  pObj = (char *)(this - 2);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*(this - 2) + 8))(this - 2, 43, 2);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)pObj + 32))(pObj, nArg2);
  (*(void (/*thiscall*/ **)(char *, char *, int))(*(uint32_t *)pObj + 52))(pObj, &pszArg3, 4);
  return (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)pObj + 60))(pObj, 1, -1);
}



// ------------------------------------------------------------
// 0x445B30 sub_445B30 —— 组包命令 44
// vtbl+8(44,0) → vtbl+40(nArg3)/vtbl+32(nArg4) 双参写入 → vtbl+60(1,nArg2) 提交
// ------------------------------------------------------------
int /*thiscall*/ sub_445B30(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  char *pObj; // esi

  pObj = (char *)(this - 2);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*(this - 2) + 8))(this - 2, 44, 0);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)pObj + 40))(pObj, nArg3);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)pObj + 32))(pObj, nArg4);
  return (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)pObj + 60))(pObj, 1, nArg2);
}



// ------------------------------------------------------------
// 0x445B70 sub_445B70 —— 字节区间填充（fill）
// 把 ·uArg3 首字节写入 [uArg1,uArg2) 全区间（fill 字节实例，与 ·sub_446100 定长版配对）
// ------------------------------------------------------------
uint8_t */*cdecl*/ sub_445B70(uint8_t *uArg1, uint8_t *uArg2, uint8_t *uArg3)
{
  uint8_t *result; // eax

  for ( result = uArg1; result != uArg2; ++result )
    *result = *uArg3;
  return result;
}



// ------------------------------------------------------------
// 0x445B90 sub_445B90 —— CNRDParticle 构造
// 挂 ·vftbl_CNRDParticle + 初始化 +4 起 0x62 字节参数块（·sub_423A20，0-100 刻度）+
// +104 内嵌 CNTimer，尾调 ·sub_529CE0/·sub_529D10 收尾
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
// 0x445C10 CNRDParticleCreater__vmt18 —— CNRDParticleCreater::vmt18 参数块整块拷贝
// 把 98 字节创建参数整块拷入 +4 参数区（与 ·sub_445B90 初始化的同一块，创建时装载）
// ------------------------------------------------------------
void /*thiscall*/ CNRDParticleCreater__vmt18(int this, const void *pArg2)
{
  qmemcpy((void *)(this + 4), pArg2, 0x62u);
}



// ------------------------------------------------------------
// 0x445C60 CNRDParticle__vmt24 —— CNRDParticle::vmt24 索引槽 setter
// 写 dword[34+nArg2]（+136 起参数槽）并回写值，与 ·CNRDParticle__vmt28 getter 成对
// ------------------------------------------------------------
int /*thiscall*/ CNRDParticle__vmt24(uint32_t *this, int pArg2, int nArg3)
{
  *(this + pArg2 + 34) = nArg3;
  return nArg3;
}



// ------------------------------------------------------------
// 0x445C80 CNRDParticle__vmt28 —— CNRDParticle::vmt28 索引槽 getter
// 读 dword[34+nArg2]（+136 起参数槽）—— 与 ·CNRDParticle__vmt24 成对
// ------------------------------------------------------------
int /*thiscall*/ CNRDParticle__vmt28(uint32_t *this, int pArg2)
{
  return *(this + pArg2 + 34);
}



// ------------------------------------------------------------
// 0x445CA0 CNRDParticle__vmt2C —— CNRDParticle::vmt2C 字段读取
// 返回 dword[33]（+132）【推断：参数槽计数或编号】
// ------------------------------------------------------------
int /*thiscall*/ CNRDParticle__vmt2C(uint32_t *this)
{
  return *(this + 33);
}



// ------------------------------------------------------------
// 0x445CB0 CNRDParticle__vmt30 —— CNRDParticle::vmt30 开关位写
// 写字节 +152（对应 ·0x445CC0 读同一字节）【推断：粒子显式挂接标志】
// ------------------------------------------------------------
char /*thiscall*/ CNRDParticle__vmt30(uint8_t *this, char pszArg2)
{
  *(this + 152) = pszArg2;
  return pszArg2;
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
// 0x445CF0 CNRDParticle__vmt44 —— CNRDParticle::vmt44 时钟换域转发
// 转 ·sub_699070(this+104, uArg2)：给内嵌 CNTimer 绑定时钟域
// ------------------------------------------------------------
void /*thiscall*/ CNRDParticle__vmt44(void *this, unsigned int uArg2)
{
  sub_699070((int)this + 104, uArg2);
}



// ------------------------------------------------------------
// 0x445D00 sub_445D00 —— CRT 一次性池初始化（池 &unk_97B6D4）
// 门 dword_9B7FC0：首建以 ·sub_657800(nArg1,256) 建池并 atexit ·sub_6BF5B0，随后转 ·sub_6578B0 分配
// ------------------------------------------------------------
int /*cdecl*/ sub_445D00(int nArg1)
{
  if ( dword_9B7FC0 == 0 )
  {
    if ( (dword_97B6F4 & 1) == 0 )
    {
      dword_97B6F4 |= 1u;
      sub_657800(nArg1, 256);
      atexit(sub_6BF5B0);
    }
    dword_9B7FC0 = (int)&unk_97B6D4;
  }
  return sub_6578B0(nArg1);
}



// ------------------------------------------------------------
// 0x445D90 CNRDParticle__vmt0 —— CNRDParticle::vmt0 删除析构壳
// ·sub_445DC0 基体清理；pszArg2 位 0 时 ·sub_657740(this,156) 归还池
// ------------------------------------------------------------
void */*thiscall*/ CNRDParticle__vmt0(void *this, char pszArg2)
{
  sub_445DC0();
  if ( (pszArg2 & 1) != 0 )
    sub_657740(this, 156);
  return this;
}



// ------------------------------------------------------------
// 0x445DC0 sub_445DC0 —— CNRDParticle 析构体
// 虚表回写 CNRDParticle，+104 内嵌定时器虚表降级 nengine::IObject，+108 字节清零
// ------------------------------------------------------------
void /*thiscall*/ sub_445DC0(uint32_t *this)
{
  *this = &vftbl_CNRDParticle;
  nullsub_3();
  *(this + 26) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 108) = 0;
}



// ------------------------------------------------------------
// 0x445E10 sub_445E10 —— UDP 全槽就绪探测（失败按 FINISH 子码 2 收尾）
// 查 8 槽（+1048648 起 4 字节步长）是否处于 1/2/5/7 就绪态；全无则置 +1048645 旗标，
// 对状态 0 的槽调 ·sub_4456C0(_,2) 与 ·sub_52D970 收尾（PVP 场景 4 另 ·sub_52AF20 刷新房间表）
// ------------------------------------------------------------
char /*thiscall*/ sub_445E10(uint8_t *this)
{
  int v1; // eax
  uint32_t *pThis_100048; // ebx
  int v3; // esi
  uint32_t *pThis_1000482; // edi
  int v5; // esi
  uint32_t *pThis_1000483; // edi

  LOBYTE(v1) = *(this + 1048645);
  if ( (uint8_t)v1 == 0 )
  {
    pThis_100048 = this + 1048648;
    v3 = 0;
    pThis_1000482 = this + 1048648;
    do
    {
      v1 = sub_656710();
      if ( *(uint32_t *)(v1 + 4 * v3) != -1 && *pThis_1000482 == 1 )
        break;
      v1 = sub_656710();
      if ( *(uint32_t *)(v1 + 4 * v3) != -1 && *pThis_1000482 == 2 )
        break;
      v1 = sub_656710();
      if ( *(uint32_t *)(v1 + 4 * v3) != -1 && *pThis_1000482 == 5 )
        break;
      v1 = sub_656710();
      if ( *(uint32_t *)(v1 + 4 * v3) != -1 && *pThis_1000482 == 7 )
        break;
      ++v3;
      ++pThis_1000482;
    }
    while ( v3 < 8 );
    if ( v3 == 8 )
    {
      *(this + 1048645) = 1;
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
        sub_52AF20(*((uint32_t *)dword_8F8528 + 8));
      v5 = 0;
      pThis_1000483 = pThis_100048;
      do
      {
        v1 = sub_656710();
        if ( *(uint32_t *)(v1 + 4 * v5) != -1 )
        {
          v1 = sub_656710();
          if ( *(uint32_t *)(v1 + 4 * v5) == -1 || *pThis_1000483 == 0 )
          {
            sub_4456C0(this, v5, 2, 0);
            LOBYTE(v1) = sub_52D970(v5, 1);
          }
        }
        ++v5;
        ++pThis_1000483;
      }
      while ( v5 < 8 );
    }
  }
  return v1;
}



// ------------------------------------------------------------
// 0x445EF0 sub_445EF0 —— 坏 ping 计数与上报（包 52）
// 逐槽以 ·sub_656850 读 ping，≥4000ms 且 1500ms 冷却到（·sub_699000/·sub_698F90）则累计计数；
// 达 3 次经包 52（·sub_423200/·sub_423290/·sub_423380）上报，日志 BAD PING COUNTER INCREASE / BAD PING REPORT
// ------------------------------------------------------------
char /*thiscall*/ sub_445EF0(uint8_t *this)
{
  int v1; // eax
  int v2; // ebx
  int *pThis_100254; // esi
  uint8_t *pThis_100181; // edi
  int v5; // eax
  int v7; // [esp+0h] [ebp-Ch]
  int v8; // [esp+4h] [ebp-8h]
  uint8_t v9[4]; // [esp+8h] [ebp-4h] BYREF

  LOBYTE(v1) = *(this + 1048944);
  if ( (uint8_t)v1 != 0 )
  {
    v2 = 0;
    pThis_100254 = (int *)(this + 1049172);
    pThis_100181 = this + 1048961;
    v8 = -1049172 - (uint32_t)this;
    do
    {
      v1 = sub_656710();
      if ( *(int *)((char *)pThis_100254 + v8 + v1) != -1 )
      {
        v5 = sub_656710();
        v1 = sub_656840(v5);
        if ( v2 != v1 )
        {
          v7 = *(uint32_t *)(pThis_100181 + 11);
          v1 = sub_699000((int)(pThis_100181 - 13));
          if ( v1 >= v7 && *pThis_100254 < 3 )
          {
            sub_656710();
            v1 = sub_656850(v2);
            if ( v1 >= 4000 )
            {
              ++*pThis_100254;
              *pThis_100181 = 0;
              pThis_100181[1] = 0;
              sub_698F90((int)(pThis_100181 - 13), 1500, 0);
              off_77F3FC("BAD PING COUNTER INCREASE %d %d", v2, *pThis_100254);
              v1 = *pThis_100254;
              if ( *pThis_100254 == 3 )
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
      ++pThis_100254;
      pThis_100181 += 28;
    }
    while ( v2 < 8 );
  }
  return v1;
}



// ------------------------------------------------------------
// 0x446000 sub_446000 —— 网络对象字符串/数值写入 + 绑定
// 向 +1049988 网络对象写 +2232 字符串与 +2488 数值；就绪门（·sub_657120/·sub_6572C0）通过后取
// ·sub_656800 上下文经 ·sub_657670 绑定【推断：与 ·sub_4458C0 同族】
// ------------------------------------------------------------
char /*thiscall*/ sub_446000(uint32_t *this, const char *pArg2, int nArg3)
{
  int fld_e262497; // esi
  int v5; // eax

  fld_e262497 = *(this + 262497);
  if ( *(uint8_t *)(fld_e262497 + 2224) == 0 )
    return 0;
  strcpy((char *)(fld_e262497 + 2232), pArg2);
  *(uint32_t *)(fld_e262497 + 2488) = nArg3;
  if ( (uint8_t)sub_657120(*(this + 262497)) != 1 || (uint8_t)sub_6572C0(*(this + 262497)) == 0 )
    return 0;
  sub_656710();
  v5 = sub_656800();
  sub_657670(*(this + 262497), v5);
  return 1;
}



// ------------------------------------------------------------
// 0x446080 sub_446080 —— range 区间拷贝 1
// (首, 末, 目标) 参数序 memmove 包装，返回目标末指针
// ------------------------------------------------------------
int /*cdecl*/ sub_446080(void *Src, int nArg2, void *pArg3)
{
  return (int)memcpy_0(pArg3, Src, nArg2 - (uint32_t)Src) + nArg2 - (uint32_t)Src;
}



// ------------------------------------------------------------
// 0x4460A0 sub_4460A0 —— range 区间拷贝 2
// —— 与 ·sub_446080 同构（差异：stdcall 约定，调用方不同）
// ------------------------------------------------------------
int /*stdcall*/ sub_4460A0(void *Src, int nArg2, void *pArg3)
{
  return (int)memcpy_0(pArg3, Src, nArg2 - (uint32_t)Src) + nArg2 - (uint32_t)Src;
}



// ------------------------------------------------------------
// 0x4460D0 sub_4460D0 —— 带空判区间拷贝
// [uArg1,uArg2) 逐字节拷至 uArg3，目标为 null 时仅推进指针（对照 ·sub_445B70 无条件填充）
// ------------------------------------------------------------
uint8_t */*cdecl*/ sub_4460D0(uint8_t *uArg1, uint8_t *uArg2, uint8_t *uArg3)
{
  uint8_t *uArg12; // ecx
  uint8_t *result; // eax

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; ++uArg12 )
  {
    if ( result != nullptr )
      *result = *uArg12;
    ++result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x446100 sub_446100 —— 定长填充
// 自 uArg1 起连续写 nArg2 个 ·uArg3 字节，返回 uArg1+nArg2
// ------------------------------------------------------------
uint8_t */*stdcall*/ sub_446100(uint8_t *uArg1, int nArg2, uint8_t *uArg3)
{
  uint8_t *uArg12; // eax
  int i; // ecx

  uArg12 = uArg1;
  if ( nArg2 != 0 )
  {
    for ( i = nArg2; i != 0; --i )
      *uArg12++ = *uArg3;
  }
  return &uArg1[nArg2];
}



// ------------------------------------------------------------
// 0x446130 sub_446130
// ------------------------------------------------------------
// 分发器 case 8/0x15/0x16 配套：PVP（模块类型 4）被动物体特殊绑定
int /*thiscall*/ sub_446130(uint32_t *this, int nArg2, int nArg3)
{
  int v5; // [esp+4h] [ebp-4h] BYREF

  sub_4BE520(&v5, &nArg3);
  if ( v5 == *(this + 18) )
    return sub_452880(nArg2, -1);
  else
    return sub_452880(nArg2, *(uint32_t *)(v5 + 16));
}



// ------------------------------------------------------------
// 0x446190 sub_446190
// ------------------------------------------------------------
// 分发器 case 8/0x15/0x16 配套：WARROOM（模块类型 6）被动物体特殊绑定
void /*thiscall*/ sub_446190(uint32_t *this, int nArg2, int nArg3)
{
  int v4; // [esp+4h] [ebp-4h] BYREF

  sub_4BE520(&v4, &nArg3);
  if ( v4 == *(this + 17) )
    sub_42D780(this, *(float *)&this, nArg2, -1);
  else
    sub_42D780(this, *(float *)&this, nArg2, *(uint32_t *)(v4 + 16));
}



// ------------------------------------------------------------
// 0x4461F0 sub_4461F0 —— PVP ping/SNAT 日志上报（包 105）
// 逐槽 4 组 ping 结果表（+1050108 起 8×16 字节）与 SNAT 记录向量（+1050092）经 105 号包分块（30 项）上报
// （·sub_423200/·sub_423290/·sub_423380）；尾段补发平均 ping 表（userindex/ntype/mtu/ping）并释放记录
// 向量，日志 Send SNATLog#/Send All SNATLog【推断：SNAT 打点回传】
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
  int fld_1005EC; // ecx
  unsigned int v11; // edi
  int v12; // ebx
  int fld_1005EC2; // ecx
  int fld_1005EC3; // ecx
  int fld_1005F0; // eax
  int v16; // eax
  int fld_1005EC4; // ecx
  int fld_1005F02; // eax
  int fld_1005EC5; // ecx
  int fld_1005F03; // eax
  int fld_1005EC6; // ecx
  int fld_1005F04; // eax
  int fld_1005EC7; // ecx
  int v24; // ebx
  int *pThis_1005FC2; // edi
  uint32_t *v26; // eax
  int v27; // eax
  int v28; // ebx
  unsigned int j; // edx
  unsigned int v30; // ecx
  int v31; // edi
  int v32; // edi
  uint32_t *pThis_1005A8; // esi
  int v34; // ebx
  int v35; // esi
  void **v36; // esi
  int k; // ebx
  uint8_t *v38; // ecx
  uint32_t v39[8]; // [esp+4h] [ebp-34h]
  int *pThis_1005FC; // [esp+24h] [ebp-14h]
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
    pThis_1005FC = (int *)(this + 1050108);
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
    if ( v5 != 0 || (fld_1005EC = *(uint32_t *)(this + 1050092)) != 0 && (result = (*(uint32_t *)(this + 1050096) - fld_1005EC) >> 2) != 0 )
    {
      v11 = 0;
      v12 = 0;
      *(uint32_t *)ArgList = 0;
      while ( 1 )
      {
        fld_1005EC2 = *(uint32_t *)(this + 1050092);
        if ( fld_1005EC2 == 0 || v11 >= (*(uint32_t *)(this + 1050096) - fld_1005EC2) >> 2 )
          break;
        sub_423200(dword_8F7B08, 105);
        fld_1005EC3 = *(uint32_t *)(this + 1050092);
        if ( fld_1005EC3 != 0 )
          fld_1005F0 = (*(uint32_t *)(this + 1050096) - fld_1005EC3) >> 2;
        else
          fld_1005F0 = 0;
        if ( fld_1005F0 - v11 <= 0x1E )
        {
          fld_1005EC4 = *(uint32_t *)(this + 1050092);
          if ( fld_1005EC4 != 0 )
            fld_1005F02 = (*(uint32_t *)(this + 1050096) - fld_1005EC4) >> 2;
          else
            fld_1005F02 = 0;
          v16 = fld_1005F02 - v11;
        }
        else
        {
          v16 = 30;
        }
        off_77F3FC("p2p try count:%d", v16);
        v44[0] = *(uint8_t *)(v41 + 172);
        sub_423290(v44, 1);
        fld_1005EC5 = *(uint32_t *)(this + 1050092);
        if ( fld_1005EC5 != 0 )
          fld_1005F03 = (*(uint32_t *)(this + 1050096) - fld_1005EC5) >> 2;
        else
          fld_1005F03 = 0;
        if ( fld_1005F03 - v11 <= 0x1E )
        {
          fld_1005EC6 = *(uint32_t *)(this + 1050092);
          if ( fld_1005EC6 != 0 )
            fld_1005F04 = (*(uint32_t *)(this + 1050096) - fld_1005EC6) >> 2;
          else
            fld_1005F04 = 0;
          v42 = fld_1005F04 - v11;
        }
        else
        {
          v42 = 30;
        }
        sub_423290(&v42, 2);
        while ( 1 )
        {
          fld_1005EC7 = *(uint32_t *)(this + 1050092);
          if ( fld_1005EC7 == 0 || v11 >= (*(uint32_t *)(this + 1050096) - fld_1005EC7) >> 2 || v12 >= 30 )
            break;
          off_77F3FC("p2p result%d :%d", v12, *(uint32_t *)(fld_1005EC7 + 4 * v11));
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
      pThis_1005FC2 = pThis_1005FC;
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
          v27 = *pThis_1005FC2;
          v28 = 0;
          for ( j = 0; v27 != 0 && j < (pThis_1005FC2[1] - v27) >> 2; ++j )
            v28 += *(uint32_t *)(*pThis_1005FC2 + 4 * j);
          if ( v28 <= 0 )
          {
            v39[*(uint32_t *)ArgList] = -1;
          }
          else
          {
            if ( v27 != 0 )
              v30 = (pThis_1005FC2[1] - v27) >> 2;
            else
              v30 = 0;
            v39[*(uint32_t *)ArgList] = v28 / v30;
            ++v42;
          }
          v12 = *(uint32_t *)ArgList;
        }
        ++v12;
        pThis_1005FC2 += 4;
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
        pThis_1005A8 = (uint32_t *)(this + 1050024);
        do
        {
          v34 = v39[v32];
          if ( v34 != -1 )
          {
            off_77F3FC("userindex :%d(ntype:%d,mtu:%d) - ping:%d", v32, pThis_1005A8[8], *pThis_1005A8, v39[v32]);
            v44[0] = *((uint8_t *)pThis_1005A8 + 32);
            sub_423290(v44, 1);
            v42 = *pThis_1005A8;
            sub_423290(&v42, 4);
            v42 = v34;
            sub_423290(&v42, 4);
          }
          ++v32;
          ++pThis_1005A8;
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
        v36 = (void **)pThis_1005FC;
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
// 0x4466A0 sub_4466A0 —— vector 长度溢出异常
// 构造 std::length_error（vector<T> too long）经 _CxxThrowException 抛出；对照 ·sub_4468D0 的 list 版
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
uint8_t */*thiscall*/ sub_446710(int this, char *Src, unsigned int uArg3, uint8_t *uArg4)
{
  uint8_t *result; // eax
  unsigned int fld_C; // ecx
  int fld_8; // edx
  int fld_82; // edx
  size_t v10; // ecx
  int fld_85; // edx
  int fld_86; // ecx
  void *pMem; // eax
  char *fld_4; // ebx
  uint8_t *fld_42; // eax
  uint8_t *v16; // eax
  int fld_43; // eax
  int fld_87; // ecx
  int v19; // edi
  int fld_83; // ebx
  unsigned int fld_84; // edx
  size_t Size; // [esp+8h] [ebp-4h]
  int v23; // [esp+18h] [ebp+Ch]

  result = *(uint8_t **)(this + 4);
  HIBYTE(uArg4) = *uArg4;
  if ( result != nullptr )
    fld_C = *(uint32_t *)(this + 12) - (uint32_t)result;
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( result != nullptr )
      fld_8 = *(uint32_t *)(this + 8) - (uint32_t)result;
    else
      fld_8 = 0;
    if ( -1 - fld_8 < uArg3 )
      sub_4466A0(this);
    if ( result != nullptr )
      fld_82 = *(uint32_t *)(this + 8) - (uint32_t)result;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint32_t *)(this + 8);
      if ( fld_83 - (int)Src >= uArg3 )
      {
        *(uint32_t *)(this + 8) = sub_4460A0((void *)(fld_83 - uArg3), fld_83, *(void **)(this + 8));
        memcpy_0(&Src[uArg3], Src, fld_83 - (uint32_t)Src - uArg3);
        return sub_445B70(Src, &Src[uArg3], (uint8_t *)&uArg4 + 3);
      }
      else
      {
        sub_4460A0(Src, fld_83, &Src[uArg3]);
        sub_446100(*(uint8_t **)(this + 8), (int)&Src[uArg3 - *(uint32_t *)(this + 8)], (uint8_t *)&uArg4 + 3);
        fld_84 = uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_84;
        return sub_445B70(Src, (uint8_t *)(fld_84 - uArg3), (uint8_t *)&uArg4 + 3);
      }
    }
    else
    {
      if ( -1 - (fld_C >> 1) >= fld_C )
      {
        v10 = (fld_C >> 1) + fld_C;
        Size = v10;
      }
      else
      {
        Size = 0;
        v10 = 0;
      }
      if ( result != nullptr )
        fld_85 = *(uint32_t *)(this + 8) - (uint32_t)result;
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )
      {
        if ( result != nullptr )
          fld_86 = *(uint32_t *)(this + 8) - (uint32_t)result;
        else
          fld_86 = 0;
        v10 = uArg3 + fld_86;
        Size = v10;
      }
      pMem = operator new(v10);
      fld_4 = &Src[-*(uint32_t *)(this + 4)];
      v23 = (int)pMem;
      fld_42 = memcpy_0(pMem, *(const void **)(this + 4), (size_t)fld_4);
      v16 = sub_446100(&fld_42[(uint32_t)fld_4], uArg3, (uint8_t *)&uArg4 + 3);
      memcpy_0(v16, Src, *(uint32_t *)(this + 8) - (uint32_t)Src);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_87 = *(uint32_t *)(this + 8) - fld_43;
      else
        fld_87 = 0;
      v19 = fld_87 + uArg3;
      if ( fld_43 != 0 )
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
// 0x4468D0 sub_4468D0 —— list 计数累加 + 溢出异常
// 上限 0x7FFFFFFF 比对后把 uArg2 累加进 +8 计数；溢出抛 std::length_error（list<T> too long）
// ------------------------------------------------------------
int /*thiscall*/ sub_4468D0(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);
  if ( 214748364 - fld_e2 < uArg2 )
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
  result = uArg2 + fld_e2;
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
  int fld_4; // ecx
  int fld_82; // ebx
  unsigned int result; // eax
  char *pMem; // edi
  int fld_43; // eax
  uint8_t *fld_42; // [esp-18h] [ebp-38h]
  uint8_t *fld_8; // [esp-14h] [ebp-34h]
  int v10; // [esp+0h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-14h]
  int *v12; // [esp+10h] [ebp-10h]
  int v13; // [esp+1Ch] [ebp-4h]

  v12 = &v10;
  fld_4 = *(uint32_t *)(this + 4);
  fld_82 = 0;
  if ( fld_4 != 0 )
    result = *(uint32_t *)(this + 12) - fld_4;
  else
    result = 0;
  if ( result < Size )
  {
    pMem = (char *)operator new(Size);
    fld_8 = *(uint8_t **)(this + 8);
    fld_42 = *(uint8_t **)(this + 4);
    Block = pMem;
    v13 = 0;
    sub_4460D0(fld_42, fld_8, pMem);
    fld_43 = *(uint32_t *)(this + 4);
    if ( fld_43 != 0 )
    {
      fld_82 = *(uint32_t *)(this + 8) - fld_43;
      j__free(*(void **)(this + 4));
    }
    *(uint32_t *)(this + 12) = &pMem[Size];
    *(uint32_t *)(this + 8) = &pMem[fld_82];
    *(uint32_t *)(this + 4) = pMem;
    return Size;
  }
  return result;
}



// ------------------------------------------------------------
// 0x446A60 sub_446A60 —— 缓冲分配三元组
// 置 +4 基/+8 使用位/+12 容量；Size 为 0 时三槽清零并返回 0
// ------------------------------------------------------------
char /*thiscall*/ sub_446A60(uint32_t *this, size_t Size)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( Size == 0 )
    return 0;
  pMem = (char *)operator new(Size);
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  *(this + 3) = &pMem[Size];
  return 1;
}



// ------------------------------------------------------------
// 0x446AB0 sub_446AB0
// ------------------------------------------------------------
// 分发器 case 5 配套：填充 3 float 向量结构（sub_4E7DA0 取数）【推断】
int /*thiscall*/ sub_446AB0(int this, int pArg2)
{
  int v3; // eax
  unsigned int v4; // ebx
  void *fld_4; // eax
  unsigned int fld_8; // edx
  int v8; // eax
  unsigned int fld_C; // ecx
  int fld_82; // edx
  void *v11; // ebx
  int v12; // ecx
  size_t v13; // eax

  if ( this == pArg2 )
    return this;
  v3 = *(uint32_t *)(pArg2 + 4);
  if ( v3 == 0 || (v4 = *(uint32_t *)(pArg2 + 8) - v3) == 0 )
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
    fld_8 = *(uint32_t *)(this + 8) - (uint32_t)fld_4;
  else
    fld_8 = 0;
  if ( v4 <= fld_8 )
  {
    memcpy_0(fld_4, *(const void **)(pArg2 + 4), *(uint32_t *)(pArg2 + 8) - *(uint32_t *)(pArg2 + 4));
    v8 = *(uint32_t *)(pArg2 + 4);
    if ( v8 != 0 )
      *(uint32_t *)(this + 8) = *(uint32_t *)(pArg2 + 8) - v8 + *(uint32_t *)(this + 4);
    else
      *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
    return this;
  }
  if ( fld_4 != nullptr )
    fld_C = *(uint32_t *)(this + 12) - (uint32_t)fld_4;
  else
    fld_C = 0;
  if ( v4 > fld_C )
  {
    if ( fld_4 != nullptr )
      j__free(*(void **)(this + 4));
    v12 = *(uint32_t *)(pArg2 + 4);
    if ( v12 != 0 )
      v13 = *(uint32_t *)(pArg2 + 8) - v12;
    else
      v13 = 0;
    if ( sub_446A60((uint32_t *)this, v13) != 0 )
      *(uint32_t *)(this + 8) = sub_4460A0(*(void **)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(void **)(this + 4));
    return this;
  }
  if ( fld_4 != nullptr )
    fld_82 = *(uint32_t *)(this + 8) - (uint32_t)fld_4;
  else
    fld_82 = 0;
  v11 = (void *)(*(uint32_t *)(pArg2 + 4) + fld_82);
  sub_446080(*(void **)(pArg2 + 4), (int)v11, *(void **)(this + 4));
  *(uint32_t *)(this + 8) = sub_4460A0(v11, *(uint32_t *)(pArg2 + 8), *(void **)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x446BE0 sub_446BE0
// ------------------------------------------------------------
// 分发器 case 5 配套：逐项读入状态字节【推断】
uint8_t */*thiscall*/ sub_446BE0(int this, uint8_t *uArg2)
{
  int fld_4; // esi
  unsigned int fld_8; // edx
  uint8_t *fld_82; // eax
  uint8_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = *(uint32_t *)(this + 8) - fld_4;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= *(uint32_t *)(this + 12) - fld_4 )
    return sub_446710(this, *(char **)(this + 8), 1u, uArg2);
  fld_82 = *(uint8_t **)(this + 8);
  *fld_82 = *uArg2;
  result = fld_82 + 1;
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x446C30 CNRDUdpModule__vmt88 —— CNRDUdpModule::vmt88 延迟包入队
// 按 vmt+16 尺寸复制自身快照，触发点 = ·sub_699000(this+262151) + rand()%100+50 加权系数 this[262150]，
// 经 ·sub_499C20 挂入 +262159 链表、·sub_4468D0 增计数【推断：延迟/重发队列】
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDUdpModule__vmt88(uint32_t *this, char pszArg2, int nArg3)
{
  size_t v4; // eax
  void *pMem; // eax
  int v6; // edx
  int pThis_40007; // esi
  int nRand; // eax
  int fld_e262159; // edi
  unsigned int fld_e262150; // eax
  int v11; // eax
  uint32_t *pThis_4000E; // ecx
  int v13; // ebx
  uint32_t *result; // eax
  int v15; // [esp-8h] [ebp-28h]
  uint32_t v16[2]; // [esp+Ch] [ebp-14h] BYREF
  char pszArg22; // [esp+14h] [ebp-Ch]
  int nArg32; // [esp+18h] [ebp-8h]
  int v19; // [esp+1Ch] [ebp-4h]

  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 16))(this);
  pMem = operator new(v4);
  v6 = *this;
  v16[0] = pMem;
  qmemcpy(pMem, this + 3, (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 16))(this));
  v16[1] = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 16))(this);
  nArg32 = nArg3;
  pszArg22 = pszArg2;
  pThis_40007 = sub_699000((int)(this + 262151));
  nRand = rand();
  fld_e262159 = *(this + 262159);
  fld_e262150 = (int)((uint64_t)(1374389535LL * *(this + 262150) * (nRand % 100 + 50)) >> 32) >> 5;
  v15 = *(uint32_t *)(fld_e262159 + 4);
  v19 = fld_e262150 + pThis_40007 + (fld_e262150 >> 31);
  v11 = sub_499C20(fld_e262159, v15, v16);
  pThis_4000E = this + 262158;
  v13 = v11;
  sub_4468D0(pThis_4000E, 1u);
  *(uint32_t *)(fld_e262159 + 4) = v13;
  result = *(uint32_t **)(v13 + 4);
  *result = v13;
  return result;
}



// ------------------------------------------------------------
// 0x446CF0 sub_446CF0
// ------------------------------------------------------------
// 分发器 case 0 配套：UDP RETURN/FINISH 分支处理（子码 1/2）【推断】
int /*thiscall*/ sub_446CF0(uint32_t *this, int pArg2, int nArg3, int nArg4)
{
  bool v6; // zf
  uint8_t *pThis_7; // eax
  int v8; // eax
  int v9; // esi
  int result; // eax
  int v11; // [esp+14h] [ebp+8h]

  v11 = *(this + pArg2 + 262162);
  v6 = (uint8_t)nArg4 == 0;
  *(this + pArg2 + 262162) = nArg3;
  if ( v6 )
  {
    *((uint8_t *)this + 28 * pArg2 + 1048692) = 0;
  }
  else
  {
    pThis_7 = this + 7 * pArg2;
    pThis_7[1048692] = 1;
    pThis_7[1048693] = 0;
    pThis_7[1048694] = 0;
    sub_698F90((int)(pThis_7 + 1048680), 0, 0);
  }
  *(this + pArg2 + 262226) = -150;
  switch ( nArg3 )
  {
    case 0:
    case 7:
      if ( *((uint8_t *)this + pArg2 + 1048936) == 0 )
        break;
      *((uint8_t *)this + pArg2 + 1048936) = 0;
      v8 = *(uint32_t *)(dword_8F7A24 + 12);
      if ( v8 == 4 )
      {
        if ( dword_99FEC0 == 0 )
          break;
        v9 = sub_48F690(pArg2);
      }
      else if ( v8 == 6 )
      {
        if ( dword_99FF08 == 0 )
          break;
        v9 = sub_578E80(pArg2);
      }
      else
      {
        v9 = *(uint32_t *)(dword_8F850C + 4 * pArg2 + 16);
      }
      if ( v9 != 0 && rand() % 100 < 10 )
      {
        sub_423200(dword_8F7B08, 100);
        HIBYTE(nArg4) = nArg3 == 0;
        sub_423290(dword_8F7B08, (int)&nArg4 + 3, 1);
        nArg4 = *(uint16_t *)(v9 + 4);
        sub_423290(dword_8F7B08, (int)&nArg4, 2);
        sub_423380(dword_8F7B08);
      }
      break;
    case 1:
    case 2:
    case 5:
      if ( *(uint32_t *)(sub_656710() + 4 * pArg2) != -1 )
        *((uint8_t *)this + pArg2 + 1048936) = 1;
      break;
    default:
      *((uint8_t *)this + pArg2 + 1048936) = 0;
      break;
  }
  result = nArg3;
  if ( nArg3 != 0 )
  {
    if ( nArg3 == 7 )
    {
      nArg4 = 3;
      return sub_431230((int)(this + 262522), &nArg4);
    }
  }
  else
  {
    result = v11 - 1;
    switch ( v11 )
    {
      case 1:
      case 3:
        nArg4 = 0;
        result = sub_431230((int)(this + 262522), &nArg4);
        break;
      case 2:
      case 4:
        nArg4 = 1;
        result = sub_431230((int)(this + 262522), &nArg4);
        break;
      case 5:
      case 6:
        nArg4 = 2;
        return sub_431230((int)(this + 262522), &nArg4);
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
char /*thiscall*/ CNRDUdpModule__vmt64(uint8_t *this, int ArgList, int pArg3, char pszArg4, char pszArg5)
{
  int v6; // eax
  int v7; // esi
  int v8; // esi
  char *v9; // eax
  uint8_t *pThis_1C; // ebx
  char *v12; // [esp-10h] [ebp-1Ch]
  char *v13; // [esp-10h] [ebp-1Ch]
  int16_t v14; // [esp-Ch] [ebp-18h]
  int v15; // [esp-8h] [ebp-14h]
  int v16; // [esp-8h] [ebp-14h]
  int v17; // [esp-4h] [ebp-10h]

  v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
  v7 = v6;
  if ( pArg3 != 0 )
  {
    v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    if ( pArg3 != v6 )
    {
      if ( *(uint32_t *)(v7 + 160) == *(uint32_t *)(v7 + 164) || *(uint32_t *)(pArg3 + 160) == *(uint32_t *)(pArg3 + 164) )
      {
        v16 = *(uint32_t *)(pArg3 + 8);
        v14 = *(uint16_t *)(pArg3 + 168);
        v8 = ArgList;
        v13 = sub_42A380((unsigned int *)pArg3, 1);
        sub_656710();
        sub_656880(ArgList, v13, v14, v16, 0);
        off_77F3FC("@@ADD PEER 2 %d", ArgList);
        if ( pszArg4 != 0 )
        {
          *((uint32_t *)this + ArgList + 262162) = 2;
          if ( pszArg5 != 0 )
          {
            pThis_1C = this + 28 * ArgList;
            goto LABEL_17;
          }
          pThis_1C = this + 28 * ArgList;
LABEL_9:
          pThis_1C[1048692] = 0;
LABEL_10:
          *((uint32_t *)this + v8 + 262226) = -150;
          if ( *(uint32_t *)(sub_656710() + 4 * v8) != -1 )
            *(this + v8 + 1048936) = 1;
          sub_4457D0(this, 0);
          goto LABEL_21;
        }
        *((uint32_t *)this + ArgList + 262162) = 4;
        pThis_1C = this + 28 * ArgList;
      }
      else
      {
        v15 = *(uint32_t *)(pArg3 + 8);
        v8 = ArgList;
        v12 = sub_42A380((unsigned int *)pArg3, 0);
        sub_656710();
        sub_656880(ArgList, v12, 5063, v15, 0);
        v9 = sub_42A380((unsigned int *)pArg3, 0);
        off_77F3FC("@@ADD PEER 1 %d [%s] %d", ArgList, v9, 5063);
        if ( pszArg4 != 0 )
        {
          *((uint32_t *)this + ArgList + 262162) = 1;
          if ( pszArg5 != 0 )
          {
            pThis_1C = this + 28 * ArgList;
LABEL_17:
            pThis_1C[1048692] = 1;
            pThis_1C[1048693] = 0;
            pThis_1C[1048694] = 0;
            sub_698F90((int)(pThis_1C + 1048680), 0, 0);
            goto LABEL_10;
          }
          pThis_1C = this + 28 * ArgList;
          goto LABEL_9;
        }
        *((uint32_t *)this + ArgList + 262162) = 3;
        pThis_1C = this + 28 * ArgList;
      }
      pThis_1C[1048692] = 1;
      pThis_1C[1048694] = 0;
      pThis_1C[1048693] = 0;
      sub_698F90((int)(pThis_1C + 1048680), 0, 0);
      *((uint32_t *)this + v8 + 262226) = -150;
      *(this + v8 + 1048936) = 0;
LABEL_21:
      sub_656630(v8);
      v17 = *(uint32_t *)(pArg3 + 12);
      sub_656710();
      sub_656950(v8, v17);
      pThis_1C[1048961] = 0;
      pThis_1C[1048962] = 0;
      LOBYTE(v6) = sub_698F90((int)(pThis_1C + 1048948), 0, 0);
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
  int pThis_4000F; // ebx
  int v3; // esi
  int *v4; // eax
  uint32_t *v5; // eax
  int v6; // esi
  int *v7; // eax
  uint32_t ***pThis_4000F2; // ecx
  uint32_t **v9; // eax
  int v10; // esi
  char pThis_1C; // cl
  char *pThis_1C2; // eax
  int pThis_10058C22; // ebx
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
  char *pThis_1000482; // edx
  const char *v34; // eax
  char *v35; // eax
  int v36; // ebx
  uint32_t *v37; // eax
  char *pThis_1C4; // eax
  char *pThis_1C3; // eax
  const char *v40; // eax
  int dword_79692C2; // esi
  uint32_t *v42; // eax
  int v43; // esi
  int pThis_10058C; // eax
  int pThis_40169; // ebx
  int v46; // ebx
  char *pThis_1005FC; // edi
  uint32_t *v48; // eax
  uint32_t *v49; // eax
  int v50; // edx
  bool v51; // zf
  unsigned int v52; // esi
  int *pThis_10058C3; // ecx
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
  int pThis_10058C2; // [esp+14h] [ebp-110h] BYREF
  char *pThis_100048; // [esp+18h] [ebp-10Ch]
  int v77; // [esp+1Ch] [ebp-108h]
  char Buffer[256]; // [esp+20h] [ebp-104h] BYREF
  int dword_796E502; // [esp+120h] [ebp-4h]

  dword_796E502 = dword_796E50;
  while ( *((uint32_t *)this + 262160) != 0 )
  {
    pThis_4000F = **((uint32_t **)this + 262159) + 8;
    if ( sub_699000((int)(this + 1048604)) < *(uint32_t *)(pThis_4000F + 16) )
      break;
    if ( **(uint8_t **)pThis_4000F != 0 )
    {
      v5 = (uint32_t *)sub_656710();
      sub_656840(v5);
      v6 = 0;
      pThis_100048 = this + 1048648;
      do
      {
        if ( *(uint32_t *)(sub_656710() + 4 * v6) != -1
          && (*(uint32_t *)(sub_656710() + 4 * v6) == -1 || *(uint32_t *)pThis_100048 == 0) )
        {
          v67 = *(uint8_t *)(pThis_4000F + 8);
          v60 = *(uint32_t *)(pThis_4000F + 4);
          v56 = *(uint8_t **)pThis_4000F;
          v7 = (int *)sub_656710();
          sub_656EF0(v7, v56, v60, v6, v67);
        }
        ++v6;
        pThis_100048 += 4;
      }
      while ( v6 < 8 );
    }
    else
    {
      v3 = *(uint32_t *)(pThis_4000F + 12);
      if ( *(uint32_t *)(sub_656710() + 4 * v3) == -1 || *((uint32_t *)this + v3 + 262162) == 0 )
      {
        v66 = *(uint8_t *)(pThis_4000F + 8);
        v63 = *(uint32_t *)(pThis_4000F + 12);
        v59 = *(uint32_t *)(pThis_4000F + 4);
        v55 = *(uint8_t **)pThis_4000F;
        v4 = (int *)sub_656710();
        sub_656EF0(v4, v55, v59, v63, v66);
      }
    }
    if ( *(uint32_t *)pThis_4000F != 0 )
      j__free(*(void **)pThis_4000F);
    *(uint32_t *)pThis_4000F = 0;
    pThis_4000F2 = *((uint32_t ****)this + 262159);
    v9 = *pThis_4000F2;
    if ( *pThis_4000F2 != pThis_4000F2 )
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
    pThis_1C = *(this + 28 * v10 + 1048692);
    pThis_1C2 = this + 28 * v10;
    pThis_100048 = pThis_1C2;
    if ( pThis_1C == 0 )
      goto LABEL_123;
    pThis_10058C22 = (int)(pThis_1C2 + 1048680);
    pThis_10058C2 = (int)(pThis_1C2 + 1048680);
    sub_698F90((int)(pThis_1C2 + 1048680), 0, 0);
    v14 = sub_699000(pThis_10058C22);
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
        pThis_10058C22 = pThis_10058C2;
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
        pThis_1000482 = pThis_100048;
        *((uint32_t *)this + v10 + 262162) = 4;
        pThis_1000482[1048692] = 1;
        *(uint8_t *)(pThis_10058C22 + 13) = 0;
        *(uint8_t *)(pThis_10058C22 + 14) = 0;
        sub_698F90(pThis_10058C22, 0, 0);
        *((uint32_t *)this + v10 + 262226) = -150;
        *(this + v10 + 1048936) = 0;
      }
      else
      {
        pThis_100048[1048692] = 1;
        *((uint32_t *)this + v10 + 262162) = 2;
        *(uint8_t *)(pThis_10058C22 + 13) = 0;
        *(uint8_t *)(pThis_10058C22 + 14) = 0;
        sub_698F90(pThis_10058C22, 0, 0);
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
    pThis_100048[1048692] = 1;
    *((uint32_t *)this + v10 + 262162) = 7;
    *(uint8_t *)(pThis_10058C22 + 13) = 0;
    *(uint8_t *)(pThis_10058C22 + 14) = 0;
    sub_698F90(pThis_10058C22, 0, 0);
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
          pThis_10058C2 = *(uint16_t *)(v30 + 4);
          sub_423290(&pThis_10058C2, 2);
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
    pThis_10058C2 = 3;
    sub_431230((int)(this + 1050088), &pThis_10058C2);
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
    pThis_1C3 = this + 28 * v10;
    *((uint32_t *)this + v10 + 262162) = 6;
    pThis_1C3[1048692] = 1;
    pThis_1C3[1048693] = 0;
    pThis_1C3[1048694] = 0;
    sub_698F90((int)(pThis_1C3 + 1048680), 0, 0);
    *((uint32_t *)this + v10 + 262226) = -150;
    *(this + v10 + 1048936) = 0;
  }
  else
  {
    pThis_1C4 = this + 28 * v10;
    *((uint32_t *)this + v10 + 262162) = 5;
    pThis_1C4[1048692] = 1;
    pThis_1C4[1048693] = 0;
    pThis_1C4[1048694] = 0;
    sub_698F90((int)(pThis_1C4 + 1048680), 0, 0);
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
    dword_79692C2 = dword_79692C;
    if ( sub_699000((int)(this + 1049204)) >= dword_79692C2 )
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
  LOBYTE(pThis_10058C) = *(this + 1050008);
  if ( (uint8_t)pThis_10058C != 0 )
  {
    pThis_40169 = *((uint32_t *)this + 262505);
    pThis_10058C = sub_699000((int)(this + 1049996));
    if ( pThis_10058C >= pThis_40169 )
    {
      *(this + 1050009) = 0;
      *(this + 1050010) = 0;
      *(this + 1050008) = 1;
      sub_698F90((int)(this + 1049996), dword_78FF60, 0);
      v46 = 0;
      pThis_1005FC = this + 1050108;
      do
      {
        pThis_10058C = sub_656710();
        if ( *(uint32_t *)(pThis_10058C + 4 * v46) != -1 )
        {
          v48 = (uint32_t *)sub_656710();
          pThis_10058C = sub_656840(v48);
          if ( v46 != pThis_10058C )
          {
            v49 = (uint32_t *)sub_656710();
            pThis_10058C = sub_656850(v49, v46);
            v50 = *(uint32_t *)pThis_1005FC;
            v51 = *(uint32_t *)pThis_1005FC == 0;
            pThis_10058C2 = pThis_10058C;
            if ( v51 )
              v52 = 0;
            else
              v52 = (*((uint32_t *)pThis_1005FC + 1) - v50) >> 2;
            if ( v50 != 0 && v52 < (*((uint32_t *)pThis_1005FC + 2) - v50) >> 2 )
            {
              pThis_10058C3 = *((int **)pThis_1005FC + 1);
              *pThis_10058C3 = pThis_10058C;
              *((uint32_t *)pThis_1005FC + 1) = pThis_10058C3 + 1;
            }
            else
            {
              LOBYTE(pThis_10058C) = sub_430C80(*((void **)pThis_1005FC + 1), 1, (int)&pThis_10058C2);
            }
          }
        }
        ++v46;
        pThis_1005FC += 16;
      }
      while ( v46 < 8 );
    }
  }
  return pThis_10058C;
}


// ============================================================
// 【分区 8】窗口族 vmt4 存根 + 界面管理器（0x44A950-0x44FF60）
// IRDWindow/CNRD*Window 各窗口类 vmt4 槽（多为调用 0x44A950 共享实现或空存根）；
// CNRDInterfaceManager 构造 0x44BA00；模块切换收尾 0x44EA20（docs/13 §3 定案）。
// ============================================================
// ------------------------------------------------------------
// 0x44A950 IRDWindow__vmt4 —— IRDWindow::vmt4 删除析构壳
// 虚表回写 ·vftbl_IRDWindow + 基体清理，pszArg2 位 0 时 j__free —— 窗口族 vmt4 槽共享实现
// ------------------------------------------------------------
uint32_t */*thiscall*/ IRDWindow__vmt4(uint32_t *Block, char pszArg2)
{
  *Block = &vftbl_IRDWindow;
  nullsub_3();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44A980 sub_44A980 —— 带界索引 getter
// nArg2 ≥ [2]（计数）返回 0，否则返回 ·[3]（数组）+ 4·nArg2 项【推断：窗口子件取用】
// ------------------------------------------------------------
int /*thiscall*/ sub_44A980(uint32_t *this, int nArg2)
{
  if ( nArg2 >= *(this + 2) )
    return 0;
  else
    return *(uint32_t *)(*(this + 3) + 4 * nArg2);
}



// ------------------------------------------------------------
// 0x44A9A0 sub_44A9A0 —— 池归还转发
// 转 ·sub_657740(nArg1, nArg2) 按尺寸归还池
// ------------------------------------------------------------
int /*cdecl*/ sub_44A9A0(int nArg1, int nArg2)
{
  return sub_657740(nArg1, nArg2);
}



// ------------------------------------------------------------
// 0x44A9C0 sub_44A9C0 —— 摊位窗析构体
// 挂 ·vftbl_CNRDPrivateStoreWindow → ·sub_544960 子窗清理 → 虚表降级 ·vftbl_IRDWindow
// ------------------------------------------------------------
void /*thiscall*/ sub_44A9C0(uint32_t *this)
{
  *this = &vftbl_CNRDPrivateStoreWindow;
  sub_544960();
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44AA20 CNRDPrivateStoreWindow__vmt4 —— CNRDPrivateStoreWindow::vmt4 删除析构壳
// ·sub_44A9C0 后按位 0 j__free
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDPrivateStoreWindow__vmt4(uint32_t *Block, char pszArg2)
{
  sub_44A9C0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44AA50 sub_44AA50 —— 界面管理器大字段区复位
// 清 +8..+128 与 +2420..+2536 字段组，并把 +2456 内嵌 CNTimer 绑到时钟域 2（·sub_699070）；
// 与 ·0x44BA00 使用同一 +2456 计时器【推断：界面管理器族初始化】
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
// 0x44AB50 sub_44AB50 —— 页签切换
// 读页索引 [26+pArg2]（12 = 空页）；非空则取旧页对象 [14+旧索引]，经 ·sub_69A580 注销其资源后
// 写新索引 [26+pArg2]=nArg3，并以旧页对象 vtbl+16 收尾【推断：面板显隐切换】
// ------------------------------------------------------------
int /*thiscall*/ sub_44AB50(uint32_t *this, int pArg2, int nArg3)
{
  int result; // eax
  int pObj; // esi
  int v6; // eax

  result = *(this + pArg2 + 26);
  if ( result != 12 )
  {
    pObj = *(this + result + 14);
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 48))(pObj);
    sub_69A580(v6);
    *(this + pArg2 + 26) = nArg3;
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);
  }
  return result;
}



// ------------------------------------------------------------
// 0x44AB90 sub_44AB90 —— 标签页选中联动（TAB_SELECT 音效）
// 比对 [17]/[18] 两管理器各自 +20 对象的 +104 槽是否指向 pArg2，变更经 ·sub_69CE50 同步，
// 播 TAB_SELECT 音效（·sub_432EA0）
// ------------------------------------------------------------
void */*thiscall*/ sub_44AB90(uint32_t *this, void *pArg2)
{
  int fld_e18; // edi
  void *result; // eax
  char v4; // dl

  fld_e18 = *(this + 18);
  result = *(void **)(*(uint32_t *)(*(this + 17) + 20) + 104);
  v4 = 0;
  if ( result != pArg2 )
  {
    result = (void *)sub_69CE50(pArg2);
    v4 = 1;
  }
  if ( *(void **)(*(uint32_t *)(fld_e18 + 20) + 104) == pArg2 )
  {
    if ( v4 == 0 )
      return result;
  }
  else
  {
    sub_69CE50(pArg2);
  }
  return sub_432EA0("TAB_SELECT", -1, 0, 0);
}



// ------------------------------------------------------------
// 0x44ABE0 sub_44ABE0 —— 选中索引 setter
// 写 [626]（+2504）并回写值
// ------------------------------------------------------------
int /*thiscall*/ sub_44ABE0(uint32_t *this, int nArg2)
{
  *(this + 626) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x44ABF0 sub_44ABF0 —— 选中索引置 17
// [626]=17 且全局 byte_89D27C=1 后转发 ·CNCommandChecker__vmt40(0,0) 刷新命令检查器
// ------------------------------------------------------------
int /*thiscall*/ sub_44ABF0(uint32_t *this)
{
  *(this + 626) = 17;
  byte_89D27C = 1;
  return CNCommandChecker__vmt40(0, 0);
}



// ------------------------------------------------------------
// 0x44AC10 sub_44AC10 —— 选中索引归零
// [626]=0，·sub_4071D0 复位后转发 ·CNCommandChecker__vmt40(0,1)
// ------------------------------------------------------------
int /*thiscall*/ sub_44AC10(uint32_t *this)
{
  *(this + 626) = 0;
  sub_4071D0();
  return CNCommandChecker__vmt40(0, 1);
}



// ------------------------------------------------------------
// 0x44AC30 sub_44AC30 —— CNRDCursor 构造
// 挂 ·vftbl_CNRDCursor → ·sub_48B720 释放 +4 关联对象 → +12 内嵌 IObject 虚表与 +16 字节复位
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
// 0x44AC80 sub_44AC80 —— 选中态复位
// [626] 为 1/2 时清零并置 [627]=12、[628..630]=0 返回 0【推断：拾取态收尾】
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
// 0x44ACC0 sub_44ACC0 —— 槽字段取值转发
// 转 ·sub_41A5E0(this + 14·nArg2 + 496)：按 14 字节步长取槽字段【推断：快捷/技能槽字段访问】
// ------------------------------------------------------------
int /*thiscall*/ sub_44ACC0(void *this, int nArg2)
{
  return sub_41A5E0((unsigned int)this + 14 * nArg2 + 496);
}



// ------------------------------------------------------------
// 0x44ACE0 sub_44ACE0 —— CNRDCommunityMenu 构造
// 挂 ·vftbl_CNRDCommunityMenu 并铺 +144..+168 参数区；eh vector 构造 5 项 0x1C 子控件（+92 起），
// 尾调 ·sub_545480/·sub_545D80 装配社区菜单页
// ------------------------------------------------------------
char */*thiscall*/ sub_44ACE0(char *this, int nArg2)
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
  sub_545D80(nArg2);
  return this;
}



// ------------------------------------------------------------
// 0x44AD80 sub_44AD80 —— CNRDCommunityMenu 析构
// ·sub_5454C0 子件清理 + 5 项子控件数组析构（eh vector destructor iterator），DeleteObject(+80 图)后整区清零
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
// 0x44AE20 sub_44AE20 —— CNRDTutorial 构造
// 挂 ·vftbl_CNRDTutorial → ·sub_546060 子件装配 → +20 内嵌 IObject 虚表与 +24 字节复位
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
// 0x44AE70 sub_44AE70 —— CNRDCountDown 构造
// 挂 ·vftbl_CNRDCountDown 与 +72 内嵌 CNTimer；·sub_49BD60 做 COUNT_DOWN 事件复位，
// ·sub_49C380 读入 Block 帧字段组（+40..+56）
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
// 0x44AF20 sub_44AF20 —— CNRDCountDown 析构
// ·sub_49BD80 子控件析构，+72 定时器虚表降级 IObject，DeleteObject(+64) 后字段组清零
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
// 0x44AFB0 sub_44AFB0 —— CNRDWarRoomResult 构造
// 建 +8/+60/+88 三枚内嵌 CNTimer；·sub_49DB10 窗口字段清零，·sub_49E340 结算动画装配
// （+56 图像、+48/+52 帧字段、M_RESULT 事件）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44AFB0(uint8_t *this, void *Block, int nArg3)
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
  sub_49E340(Block, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x44B060 sub_44B060 —— CNRDWarRoomResult 析构
// ·sub_49DB30 子件批量析构后三定时器虚表降级 IObject，+92/+64/+12 字节清零
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
// 0x44B0C0 sub_44B0C0 —— CNRDResult 构造
// 挂 ·vftbl_CNRDResult 并建 +8/+92 两枚内嵌 CNTimer；·sub_476C10 字段初始，·sub_478C70 结算装配
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44B0C0(uint8_t *this, void *Block, int nArg3)
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
  sub_478C70(Block, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x44B160 sub_44B160 —— CNRDResult 析构
// ·sub_476C50 清理后两定时器虚表降级 IObject，+96/+12 字节清零
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
// 0x44B1C0 CNRDItemInventoryWindow__vmt4 —— CNRDItemInventoryWindow::vmt4 删除析构壳
// ·sub_44B1F0 后按位 0 j__free
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemInventoryWindow__vmt4(void *Block, char pszArg2)
{
  sub_44B1F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B1F0 sub_44B1F0 —— 物品栏窗析构体
// 挂 ·vftbl_CNRDItemInventoryWindow → ·sub_547000 清理 → 虚表降级 ·vftbl_IRDWindow
// ------------------------------------------------------------
void /*thiscall*/ sub_44B1F0(uint32_t *this)
{
  *this = &vftbl_CNRDItemInventoryWindow;
  sub_547000();
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44B250 CNRDAvatarInventoryWindow__vmt4 —— CNRDAvatarInventoryWindow::vmt4 删除析构壳
// ·sub_44B280 后按位 0 j__free
// ------------------------------------------------------------
void */*thiscall*/ CNRDAvatarInventoryWindow__vmt4(void *Block, char pszArg2)
{
  sub_44B280();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B280 sub_44B280 —— 角色装备栏窗析构体
// 挂 ·vftbl_CNRDAvatarInventoryWindow → ·sub_548D40 清理 → 虚表降级 ·vftbl_IRDWindow
// ------------------------------------------------------------
void /*thiscall*/ sub_44B280(uint32_t *this)
{
  *this = &vftbl_CNRDAvatarInventoryWindow;
  sub_548D40();
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44B2E0 sub_44B2E0 —— CNRDItemTradeWindow 构造（双参数块）
// 先 IRDWindow 基构造（·sub_540330/·sub_540340）再挂派生虚表；建 +28 与 +80 两组 6/12/0/1600 参数块，
// 尾调 ·sub_549DC0/·sub_54A930（Interface/ItemTradeWindowReady.img 就绪绘制）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44B2E0(uint8_t *this, int nArg2)
{
  *(uint32_t *)this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(nArg2, 0);
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
// 0x44B3B0 CNRDItemTradeWindow__vmt4 —— CNRDItemTradeWindow::vmt4 删除析构壳
// ·sub_44B3E0 后按位 0 j__free
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemTradeWindow__vmt4(void *Block, char pszArg2)
{
  sub_44B3E0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B3E0 sub_44B3E0 —— 交易窗析构体
// ·sub_54A8B0 清理后 DeleteObject(+124)/DeleteObject(+72) 两处资源句柄，清零 +40..+76 与
// +92..+128 两组参数块，虚表降级 ·vftbl_IRDWindow
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
// 0x44B4C0 CNRDSkillInventoryWindow__vmt4 —— CNRDSkillInventoryWindow::vmt4 删除析构壳
// ·sub_44B4F0 后按位 0 j__free
// ------------------------------------------------------------
void */*thiscall*/ CNRDSkillInventoryWindow__vmt4(void *Block, char pszArg2)
{
  sub_44B4F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B4F0 sub_44B4F0 —— 技能栏窗析构体
// 挂 ·vftbl_CNRDSkillInventoryWindow → ·sub_54ABE0 清理 → 虚表降级 ·vftbl_IRDWindow
// ------------------------------------------------------------
void /*thiscall*/ sub_44B4F0(uint32_t *this)
{
  *this = &vftbl_CNRDSkillInventoryWindow;
  sub_54ABE0();
  *this = &vftbl_IRDWindow;
  nullsub_3();
}



// ------------------------------------------------------------
// 0x44B550 sub_44B550 —— CNRDStatusWindow 构造
// 基构造（·sub_540330/·sub_540340）后挂虚拟表并铺参数块（6/12/0/1600）；
// ·sub_54B770/·sub_54B8B0 装配状态窗页
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44B550(uint8_t *this, int nArg2)
{
  *(uint32_t *)this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(nArg2, 0);
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
// 0x44B5F0 CNRDStatusWindow__vmt4 —— CNRDStatusWindow::vmt4 删除析构壳
// ·sub_44B620 后按位 0 j__free
// ------------------------------------------------------------
void */*thiscall*/ CNRDStatusWindow__vmt4(void *Block, char pszArg2)
{
  sub_44B620();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B620 sub_44B620 —— 状态窗析构体
// ·sub_54B780 清理后 DeleteObject(+72)，清零 +40..+76 参数块并降级 ·vftbl_IRDWindow
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
// 0x44B6C0 sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
// —— 与 ·sub_445D00 同构（差异：池 &unk_98B6F8 / atexit ·sub_6BF5C0）
// ------------------------------------------------------------
int /*cdecl*/ sub_44B6C0(int nArg1)
{
  if ( dword_9A0228 == 0 )
  {
    if ( (dword_98B718 & 1) == 0 )
    {
      dword_98B718 |= 1u;
      sub_657800(nArg1, 256);
      atexit(sub_6BF5C0);
    }
    dword_9A0228 = (int)&unk_98B6F8;
  }
  return sub_6578B0(nArg1);
}



// ------------------------------------------------------------
// 0x44B750 sub_44B750 —— CNRDItemToolWindow 构造
// 基构造后挂虚拟表；+36 内嵌 CNTimer 与工具窗字段组，尾调 ·sub_54C8B0/·sub_54D6E0 工具窗页绘制
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44B750(uint8_t *this, int nArg2)
{
  *(uint32_t *)this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(nArg2, 0);
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
// 0x44B7F0 CNRDItemToolWindow__vmt4 —— CNRDItemToolWindow::vmt4 删除析构壳
// ·sub_44B820 后按位 0 j__free
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemToolWindow__vmt4(void *Block, char pszArg2)
{
  sub_44B820();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B820 sub_44B820 —— 工具窗析构体
// ·sub_54C8F0 清理后 +36 定时器虚表降级 IObject，随后降级 ·vftbl_IRDWindow
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
// 0x44B880 CNRDPrivateStoreWindow_Display__vmt4 —— CNRDPrivateStoreWindow_Display::vmt4 删除析构壳
// ·sub_44B8B0 后按位 0 j__free
// ------------------------------------------------------------
void */*thiscall*/ CNRDPrivateStoreWindow_Display__vmt4(void *Block, char pszArg2)
{
  sub_44B8B0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B8B0 sub_44B8B0 —— 展示摊位窗析构体
// 挂展示窗虚表后 ·sub_544960 清理收购子窗，再转 ·sub_44A9C0 做摊位窗基析构
// ------------------------------------------------------------
void /*thiscall*/ sub_44B8B0(uint32_t *this)
{
  *this = &vftbl_CNRDPrivateStoreWindow_Display;
  sub_544960();
  sub_44A9C0(this);
}



// ------------------------------------------------------------
// 0x44B900 CNRDPrivateStoreWindow_Sell__vmt4 —— CNRDPrivateStoreWindow_Sell::vmt4 删除析构壳
// ·sub_44B930 后按位 0 j__free
// ------------------------------------------------------------
void */*thiscall*/ CNRDPrivateStoreWindow_Sell__vmt4(void *Block, char pszArg2)
{
  sub_44B930();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B930 sub_44B930 —— 收购摊位窗析构体
// —— 与 ·sub_44B8B0 同构（差异：派生窗虚表 CNRDPrivateStoreWindow_Sell）
// ------------------------------------------------------------
void /*thiscall*/ sub_44B930(uint32_t *this)
{
  *this = &vftbl_CNRDPrivateStoreWindow_Sell;
  sub_544960();
  sub_44A9C0(this);
}



// ------------------------------------------------------------
// 0x44B980 CNRDPrivateStoreWindow_Buy__vmt4 —— CNRDPrivateStoreWindow_Buy::vmt4 删除析构壳
// ·sub_44B9B0 后按位 0 j__free
// ------------------------------------------------------------
void */*thiscall*/ CNRDPrivateStoreWindow_Buy__vmt4(void *Block, char pszArg2)
{
  sub_44B9B0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44B9B0 sub_44B9B0 —— 购买摊位窗析构体
// —— 与 ·sub_44B8B0 同构（差异：派生窗虚表 CNRDPrivateStoreWindow_Buy）
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
int /*thiscall*/ CNRDInterfaceManager__vmt0(int this, int nArg2)
{
  int result; // eax
  int fld_9B0; // ebx
  int fld_994; // ecx
  int fld_9B8; // ecx
  int fld_9C0; // ecx

  result = nArg2;
  if ( *(uint32_t *)(this + 4) != 0 || nArg2 != *(uint32_t *)(this + 112) )
  {
    if ( nArg2 == *(uint32_t *)(this + 2448) )
    {
      if ( *(uint8_t *)(this + 2468) != 0 )
      {
        sub_698F90(this + 2456, 30, 0);
        fld_9B0 = *(uint32_t *)(this + 2480);
        if ( sub_699000(this + 2456) < fld_9B0 )
        {
          fld_994 = *(uint32_t *)(this + 2452);
          if ( fld_994 != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_994 + 128))(
              fld_994,
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
        fld_9B8 = *(uint32_t *)(this + 2488);
        if ( fld_9B8 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_9B8 + 128))(
            fld_9B8,
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
        fld_9C0 = *(uint32_t *)(this + 2496);
        if ( fld_9C0 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_9C0 + 128))(
            fld_9C0,
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
// 0x44BBA0 sub_44BBA0 —— 窗口显示切换（WINDOW_SHOW 音效）
// 页索引 [26+pArg2] 比对：已选中且 uArg3 置位 → ·sub_44AB50(_,12) 收起；否则改写索引并
// ·sub_69A840 登记 5 处资源，播 WINDOW_SHOW 音效（·sub_432EA0）
// ------------------------------------------------------------
uint8_t /*thiscall*/ sub_44BBA0(uint32_t *this, int pArg2, uint8_t uArg3)
{
  uint8_t result; // al
  int pObj; // edi
  int v6; // ebx
  int v7; // eax

  result = pArg2;
  if ( pArg2 != 12 )
  {
    pObj = *(this + pArg2 + 14);
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);
    if ( *(this + v6 + 26) == pArg2 )
    {
      result = uArg3;
      if ( uArg3 != 0 )
        return sub_44AB50(this, v6, 12);
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 12))(pObj);
      if ( result != 0 )
      {
        sub_44AB50(this, v6, pArg2);
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 48))(pObj);
        sub_69A840(v7);
        *(this + v6 + 26) = pArg2;
        return (uint8_t)sub_432EA0("WINDOW_SHOW", -1, 0, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x44BC30 sub_44BC30 —— 拾取模式状态 + ICON_PICK/ITEM_PICK 音效
// 写 [627..630]（+2508..+2520）状态组后：模式 1 播 ICON_PICK 并 ·sub_41A590(pArg7+572, 1)；
// 模式 2 播 ITEM_PICK 并调 pArg7 vtbl+88
// ------------------------------------------------------------
void */*thiscall*/ sub_44BC30(uint32_t *this, void *pArg2, int nArg3, int nArg4, int nArg5, int nArg6, void *pArg7)
{
  void *result; // eax
  int v8; // edx

  result = pArg2;
  *(this + 627) = nArg3;
  *(this + 628) = nArg4;
  *(this + 629) = nArg5;
  *(this + 626) = pArg2;
  *(this + 630) = nArg6;
  if ( pArg2 == (void *)1 )
  {
    sub_432EA0("ICON_PICK", -1, 0, 0);
    result = pArg7;
    if ( pArg7 != nullptr )
      return (void *)sub_41A590((unsigned int)pArg7 + 572, v8, 1);
  }
  else if ( pArg2 == (void *)2 )
  {
    result = sub_432EA0("ITEM_PICK", -1, 0, 0);
    if ( pArg7 != nullptr )
      return (void *)(*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)pArg7 + 88))(pArg7, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x44BCC0 sub_44BCC0 —— 71 组条目表非空检查
// 以 16 字节步长（4 dword）自 +136 起扫 71 组，任一组基址非空且末址与基址差非 0 即返回 1，全空返回 0
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
// 0x44BD00 sub_44BD00 —— 8 字节元素反向拷贝
// 自 nArg2 向前逐 8 字节元素（双 dword 对）拷至 uArg3，返回目标首指针
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_44BD00(int nArg1, int nArg2, uint32_t *uArg3)
{
  int nArg22; // ecx
  uint32_t *result; // eax
  int v5; // esi

  nArg22 = nArg2;
  for ( result = uArg3; nArg22 != nArg1; result[1] = *(uint32_t *)(nArg22 + 4) )
  {
    v5 = *(uint32_t *)(nArg22 - 8);
    nArg22 -= 8;
    result -= 2;
    *result = v5;
  }
  return result;
}



// ------------------------------------------------------------
// 0x44BD30 sub_44BD30 —— 8 字节元素正向拷贝
// —— 与 ·sub_44BD00 同构（差异：正向 + 目标为 null 仅跳过）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_44BD30(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; result += 2 )
  {
    if ( result != nullptr )
    {
      *result = *uArg12;
      result[1] = uArg12[1];
    }
    uArg12 += 2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x44BD60 sub_44BD60 —— 节点树递归释放
// 先递归释放 [2] 子节点，再取 [0] 后继并 j__free 本节点；节点 +21 标志非 0 时终止
// （哨兵节点不释放）【推断：容器节点链表清理】
// ------------------------------------------------------------
char /*stdcall*/ sub_44BD60(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_44BD60(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x44BDA0 sub_44BDA0 —— CNRDChatting 构造
// 建 5 枚内嵌 CNTimer 与两组 20 元素 0x1C 子控件数组（+324/+884）；尾调 ·sub_43C730 字段初始化与
// ·sub_43E150 聊天窗口控件装配（输入框/频道页/滚动条）
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
// 0x44BF40 sub_44BF40 —— CNRDChatting 析构
// ·sub_43B6A0 子控件群释放 + 两组 20 元素数组析构（eh vector destructor iterator）+ 3 处 CNString
// 缓冲释放，各内嵌 IObject 虚表降级
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
// 0x44C050 sub_44C050 —— 元素成对释放弃构体
// 释放 [0] 对象（vtbl+4 位 1）置空，再按 +28 容量 ≥16 判断释放 +8 缓冲并复位为 15
// 【推断：含智能指针 + CNString 的小结构析构】
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
// 0x44C0C0 sub_44C0C0 —— 单字符串元素析构
// 按 +72 容量 ≥16 释放 +52 缓冲并复位（15/0/0）【推断：与 ·sub_44C050 同族的容器元素析构】
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
// 0x44C0F0 sub_44C0F0 —— 链表节点摘除
// 把 pszArg3+4 起元素整体左移 4 字节覆盖被摘项，[2] 尾指针回退 4，输出迭代器 {pszArg3}
// 【推断：list 中部 erase】
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44C0F0(uint32_t *this, uint32_t *uArg2, char *pszArg3)
{
  memcpy_0(pszArg3, pszArg3 + 4, 4 * ((*(this + 2) - (int)(pszArg3 + 4)) >> 2));
  *(this + 2) -= 4;
  *uArg2 = pszArg3;
  return uArg2;
}



// ------------------------------------------------------------
// 0x44C130 sub_44C130 —— CNRDWarRoomInterface 析构
// ·sub_49C9E0 子控件批量析构后 DeleteObject 三处（+224/+172/+120），逐组清零并释放 +12 缓冲
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
// 0x44C2A0 sub_44C2A0 —— 对象 + 字符串成对释放弃构体
// +80 门非 0 时以 vtbl+4(this,1) 释放 [19]（+76）对象；再按 +72 容量 ≥16 释放 +52 缓冲
// 【推断：与 ·sub_44C050 同族，弹出菜单条目】
// ------------------------------------------------------------
void /*thiscall*/ sub_44C2A0(void *this)
{
  int pThis_13; // ecx

  if ( *((uint8_t *)this + 80) != 0 )
  {
    pThis_13 = *((uint32_t *)this + 19);
    if ( pThis_13 != 0 )
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_13 + 4))(pThis_13, 1);
  }
  if ( *((uint32_t *)this + 18) >= 0x10u )
    j__free(*((void **)this + 13));
  *((uint32_t *)this + 18) = 15;
  *((uint32_t *)this + 17) = 0;
  *((uint8_t *)this + 52) = 0;
}



// ------------------------------------------------------------
// 0x44C310 sub_44C310 —— CNRDPopupMenu 析构
// ·sub_5256E0 清理后 DeleteObject(+208)，释放 +148 条目数组与 +24 起 CNString 缓冲（容量 +44）并整组清零
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
// 0x44C410 sub_44C410 —— 界面条目与对象树匹配查询
// 取 [30+pArg2] 记录（+92 环形链表）逐节点，在 +136 起 71 组条目表中比对 vtbl+36 与节点 +8 且条目
// vtbl+20 可见，命中返回 1【推断：列表项与对象绑定校验】
// ------------------------------------------------------------
char /*thiscall*/ sub_44C410(uint32_t *this, int pArg2)
{
  int v2; // edx
  uint32_t *v3; // eax
  int v4; // edx
  uint32_t *pThis_232; // ebx
  uint32_t *v6; // esi
  int v7; // edi
  int v9; // [esp+Ch] [ebp-Ch]
  uint32_t *pThis_23; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]
  uint32_t *v12; // [esp+20h] [ebp+8h]

  v2 = *(this + pArg2 + 30);
  v3 = *(uint32_t **)(v2 + 96);
  v4 = v2 + 92;
  v9 = v4;
  v12 = v3;
  if ( v3 != (uint32_t *)*v3 )
  {
    pThis_23 = this + 35;
    while ( 2 )
    {
      pThis_232 = pThis_23;
      for ( i = 0; i < 71; ++i )
      {
        v6 = (uint32_t *)*(pThis_232 - 1);
        if ( v6 != (uint32_t *)*pThis_232 )
        {
          while ( 1 )
          {
            v7 = v12[1];
            if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v6 + 36))(*v6) == *(uint32_t *)(v7 + 8)
              && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v6 + 20))(*v6) != 0 )
            {
              return 1;
            }
            if ( ++v6 == (uint32_t *)*pThis_232 )
            {
              v4 = v9;
              break;
            }
          }
        }
        pThis_232 += 4;
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
// 0x44C4C0 sub_44C4C0 —— CNRDBaseInterface 析构
// 逐区把内嵌 IObject 虚表降级基类；析构 2/3/8 元素向量组（0x34/0x1C）；删除 5 组 HGDIOBJ；
// 清理 +896/+712/+696 容器（·sub_6569D0）并 free 各缓冲【推断：界面基类大析构】
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
// 0x44C830 sub_44C830 —— CNRDCharacterTalkBox 析构
// ·sub_49B370 子控件析构后降级 +60 内嵌 IObject，释放 +48 条目数组与 +16 字符串（容量 +36）
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
// 0x44C8C0 sub_44C8C0 —— 战房对话框析构
// 挂派生虚表后转 ·sub_44C830 做 CNRDCharacterTalkBox 基析构
// ------------------------------------------------------------
void /*thiscall*/ sub_44C8C0(uint32_t *this)
{
  *this = &vftbl_CNRDWarRoomBattleTalkBox;
  nullsub_3();
  sub_44C830(this);
}



// ------------------------------------------------------------
// 0x44C910 CNRDMakePriceWindow__vmt0 —— CNRDMakePriceWindow::vmt0 删除析构壳
// ·sub_44C940（挂虚表 + ·sub_5449D0 + ·sub_43C2E0）后按位 0 j__free
// ------------------------------------------------------------
void */*thiscall*/ CNRDMakePriceWindow__vmt0(void *Block, char pszArg2)
{
  sub_44C940();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44C940 sub_44C940 —— CNRDMakePriceWindow 析构主体
// 挂 vftbl_CNRDMakePriceWindow → ·sub_5449D0（数量/价格子对象）→ 返回 ·sub_43C2E0（nengine::CNFrame 析构）
// ------------------------------------------------------------
int /*thiscall*/ sub_44C940(void **this)
{
  *this = &vftbl_CNRDMakePriceWindow;
  sub_5449D0();
  return sub_43C2E0(this);
}



// ------------------------------------------------------------
// 0x44C990 sub_44C990 —— 52 字节记录数组析构遍历
// [nArg1,nArg2) 步长 52（0x34）逐元素调用 ·sub_477AF0（字符串/文本框成员析构）
// ------------------------------------------------------------
int /*stdcall*/ sub_44C990(int nArg1, int nArg2)
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 52 )
    result = sub_477AF0(i);
  return result;
}



// ------------------------------------------------------------
// 0x44C9C0 sub_44C9C0 —— 槽位记录默认值初始化
// -1 哨兵位 +0/+4/+12/+16/+44，其余字段清零；末尾 ·sub_4015C0 复位全局 szPassword
// （与 ·sub_44CEA0 同构，差异：不含 +48 处内嵌 std::string 置空）
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
// 0x44CA10 sub_44CA10 —— 槽位记录复位（内嵌 std::string 置空 + 首字段清零）
// std::string 置空三件套（cap=15 / size=0 / buf[0]=0）；首 dword 归 0 + szPassword 复位
// ------------------------------------------------------------
void /*thiscall*/ sub_44CA10(char *this)
{
  char *pThis_4; // ecx

  pThis_4 = this + 4;
  *((uint32_t *)pThis_4 + 6) = 15;
  *((uint32_t *)pThis_4 + 5) = 0;
  pThis_4[4] = 0;
  *(uint32_t *)this = 0;
  sub_4015C0((void *)szPassword, 0);
}



// ------------------------------------------------------------
// 0x44CA70 sub_44CA70 —— 52 字节记录数组析构释放
// [this+4,this+8) 步长 52 逐元素 ·sub_477AF0 后 j__free 基址并三指针清零
// （与 ·sub_44C990 同构，差异：自带存储释放）
// ------------------------------------------------------------
int /*thiscall*/ sub_44CA70(int *this)
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);
  result = 0;
  if ( fld_e1 != 0 )
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 52 )
      sub_477AF0(fld_e1);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x44CAB0 sub_44CAB0 —— vector 超长抛 std::length_error
// 构造异常文案 vector<T> too long（0x12 字节，自证）后 _CxxThrowException；noreturn
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
// 0x44CB20 sub_44CB20 —— 红黑树单节点摘除与重平衡（_Rb_tree erase 单节点）
// 迭代器非法先抛 std::out_of_range（invalid map/set<T> iterator 自证）；min/max 取 ·sub_52E300/·sub_542490
// 左旋 ·sub_433130、右旋重连 ·sub_4296E0；节点计数 -1，新迭代器经 uArg2 输出
// ------------------------------------------------------------
int ***/*thiscall*/ sub_44CB20(uint32_t *this, int ***uArg2, int **pDwArg3)
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
  void **pExceptionObject; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v20[20]; // [esp+34h] [ebp-34h] BYREF
  int v21; // [esp+48h] [ebp-20h]
  int v22; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v26; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 21) != 0 )
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
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C5E0(&pDwArg3);
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
// 0x44CDE0 sub_44CDE0 —— CNRDPVPResult 析构主体
// 挂 vftbl_CNRDPVPResult → ·sub_54DA10（PVP 结算子对象）→ 释放 +156 缓冲、DeleteObject +120 位图
// 文本框字段与内嵌 IObject 虚表（vftbl_nengine__IObject）复位
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
// 0x44CEA0 sub_44CEA0 —— 槽位记录全量初始化（含内嵌 std::string 置空）
// 先置空 +48 std::string（cap/size/buf 三件套），再 -1/0 默认值与 szPassword 复位，末字节 +80 清零
// （与 ·sub_44C9C0 同构，差异：多内嵌 std::string 与 +80 字段）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44CEA0(uint32_t *this)
{
  char *pThis_C; // ecx

  pThis_C = (char *)(this + 12);
  *((uint32_t *)pThis_C + 6) = 15;
  *((uint32_t *)pThis_C + 5) = 0;
  pThis_C[4] = 0;
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
// 0x44CF30 sub_44CF30 —— 记录初始化转发壳
// 直接尾调 ·sub_44CEA0，无附加逻辑（与 ·sub_44CEA0 同构，差异：仅转发）
// ------------------------------------------------------------
void /*thiscall*/ sub_44CF30(uint32_t *this)
{
  sub_44CEA0(this);
}



// ------------------------------------------------------------
// 0x44CF50 sub_44CF50 —— 16 字节元素容器预留（首次分配）
// 三指针归零；uArg2=0 直返 0；>0xFFFFFFF 走 ·sub_44CAB0 抛 length_error
// 否则 operator new(16*uArg2) 并回填 begin/end/cap
// ------------------------------------------------------------
char /*thiscall*/ sub_44CF50(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0xFFFFFFF )
    sub_44CAB0(this);
  pMem = (char *)operator new(16 * uArg2);
  *(this + 3) = &pMem[16 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x44CFA0 sub_44CFA0 —— 4 字节元素容器区间插入 N 个同值（vector<uint32> insert）
// 容量内：·sub_55E7F0 右移腾位 + ·sub_5DAF70 搬移；跨尾扩容：new + memcpy + ·sub_523700
// 填充统一走 ·sub_49A9D0（逐 uint32 写同值）；超界先经 ·sub_434730 抛 length_error
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_44CFA0(int this, int Src, unsigned int uArg3, int *pDwArg4)
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
      sub_434730(this);
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
// 0x44D180 sub_44D180 —— 红黑树区间删除（_Rb_tree erase(first,last)）
// 整树路径 ·sub_44BD60 递归释放后复位哨兵头；否则逐节点求前驱/后继 + ·sub_44CB20 摘除
// 结果迭代器经 pDwArg2 输出
// ------------------------------------------------------------
int */*thiscall*/ sub_44D180(int **this, int *pDwArg2, int nArg3, int nArg4)
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
    sub_44BD60(*(void ***)(fld_e1 + 4));
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
        sub_44CB20(this, &nArg3, nArg322);
      }
      while ( nArg32 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x44D240 sub_44D240 —— 8 字节元素容器区间插入 N 个同值（vector insert 8B 版）
// 容量内：·sub_44BD30 正向搬移 / ·sub_44BD00 反向搬移 + ·sub_41FEB0 填充锚点
// 扩容：operator new(8*n) + ·sub_63A7C0 就地构造；超界抛 ·sub_44CAB0
// ------------------------------------------------------------
void /*thiscall*/ sub_44D240(int this, uint32_t *uArg2, unsigned int uArg3, int pArg4)
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
      sub_44CAB0(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint32_t *)(this + 8);
      v20 = (fld_83 - (int)uArg2) >> 3 < uArg3;
      v21 = 8 * uArg3;
      v30 = 8 * uArg3;
      fld_832 = fld_83;
      if ( v20 )
      {
        sub_44BD30(uArg2, fld_83, &uArg2[v21 / 4u]);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - (int)uArg2) >> 3);
        fld_85 = *(uint32_t *)(this + 8);
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);
        fld_86 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        sub_41FEB0(uArg2, (uint32_t *)(fld_86 - v30), v28);
      }
      else
      {
        v23 = fld_83 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);
        sub_44BD00(uArg2, v23, fld_832);
        sub_41FEB0(uArg2, &uArg2[v30 / 4u], v28);
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
      v32 = sub_44BD30(fld_42, uArg2, pMem);
      sub_63A7C0(v32, uArg3, v28);
      sub_44BD30(uArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);
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
// 0x44D490 sub_44D490 —— 4 字节元素容器整体拷贝赋值
// 按源长度 ·sub_4349E0 预留目标，·sub_497E70 逐元素拷贝；返回 this
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44D490(uint32_t *this, int pArg2)
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
// 0x44D530 sub_44D530 —— CNRDBaseInterface 虚表起步的大型界面对象构造（自证 vftable）
// 挂 CNRDBaseInterface::vftable；多组布局模板（0/6/12/0/1600）与 off_6C2B88 内嵌对象虚表
// 【推断】界面/模块对象构造：eh vector 批装配 0x1C×8 / 0x1C×3 / 0x34×2 子数组
// 收尾 ·sub_4605F0(this) + ·sub_469DD0(this, Block)（派生类身份未定）【推断】
// ------------------------------------------------------------
char */*thiscall*/ sub_44D530(char *this, void *Block)
{
  uint32_t *pThis_3D0; // eax
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
// 0x44DA60 sub_44DA60 —— CNRDWarRoomInterface 构造
// 挂 vftbl_CNRDWarRoomInterface；三组布局模板（0/6/12/0/1600）
// 收尾 ·sub_49C990 字段清零 + ·sub_49CFF0 窗口对象装配
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
// 0x44DBB0 sub_44DBB0 —— CNRDPVPResult 构造
// 挂 vftbl_CNRDPVPResult；两组 nengine::CNTimer（vftbl_nengine__CNTimer）+ 布局模板
// 收尾 ·sub_54F530（转发 54F4C0）+ ·sub_54F870 结算触发
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
// 0x44DC90 sub_44DC90 —— CNRDSkillBuyWindow 构造
// IRDWindow 基类起步（·sub_540330 + ·sub_540340(nArg2,0)）后挂 vftbl_CNRDSkillBuyWindow
// 批装配 0x10×5 控件数组 + 0x34×3 文本数组；收尾 ·sub_5502A0 + ·sub_550D20 页绘制
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44DC90(uint32_t *this, int nArg2)
{
  *this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(nArg2, 0);
  *this = &vftbl_CNRDSkillBuyWindow;
  `eh vector constructor iterator'(this + 16, 0x10u, 5, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  `eh vector constructor iterator'(this + 39, 0x34u, 3, sub_416D10, sub_416D50);
  sub_5502A0(this);
  sub_550D20((int)this);
  return this;
}



// ------------------------------------------------------------
// 0x44DD30 CNRDSkillBuyWindow__vmt4 —— CNRDSkillBuyWindow::vmt4 删除析构壳
// ·sub_44DD60 后按位 0 j__free（窗口族 vmt4 删除壳统一形态）
// ------------------------------------------------------------
void */*thiscall*/ CNRDSkillBuyWindow__vmt4(void *Block, char pszArg2)
{
  sub_44DD60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44DD60 sub_44DD60 —— CNRDSkillBuyWindow 析构主体
// ·sub_550300（结果数据子对象）→ 0x34×3 + 0x10×5 eh vector destructor → 回退 vftbl_IRDWindow
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
// 0x44DDF0 sub_44DDF0 —— CNRDQuestInfoWindow 构造
// IRDWindow 基类起步后挂 vftbl_CNRDQuestInfoWindow；CNTimer + 布局模板
// 收尾 ·sub_551730（任务文本辅助）+ ·sub_552070 任务信息页绘制
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44DDF0(uint8_t *this, int nArg2)
{
  *(uint32_t *)this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(nArg2, 0);
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
// 0x44DEF0 CNRDQuestInfoWindow__vmt4 —— CNRDQuestInfoWindow::vmt4 删除析构壳
// ·sub_44DF20 后按位 0 j__free；与 ·0x44DD30 同构（差异：析构主体）
// ------------------------------------------------------------
void */*thiscall*/ CNRDQuestInfoWindow__vmt4(void *Block, char pszArg2)
{
  sub_44DF20();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44DF20 sub_44DF20 —— CNRDQuestInfoWindow 析构主体
// ·sub_551A60（任务文本释放）→ ·sub_44CA70 释放 52 字节数组 → DeleteObject 位图 → 回退 vftbl_IRDWindow
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
// 0x44E000 sub_44E000 —— CNRDPopupMenu 构造
// 挂 vftbl_CNRDPopupMenu；内嵌 std::string 置空（cap 15）+ 布局模板
// 收尾 ·sub_525660 + ·sub_526440(Block)
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
// 0x44E0D0 sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
// vftbl_KMessenger → ·sub_498AB0 全局链节点追加 → 覆盖 vftbl_CNRDObject；三组 CNTimer
// ·sub_433A60 建 28B 链表哨兵头（+124）；收尾 ·sub_498B70 快照复位 + ·sub_499A20 对象重建(nArg2,pszArg3)
// ------------------------------------------------------------
char */*thiscall*/ sub_44E0D0(char *this, int nArg2, char pszArg3)
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
  sub_499A20(nArg2, pszArg3);
  return this;
}



// ------------------------------------------------------------
// 0x44E1F0 sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
// 转发 ·sub_44E0D0 后改写 vftbl_CNRDPooledObject（与 ·sub_44E0D0 同构，差异：派生虚表）
// ------------------------------------------------------------
char */*thiscall*/ sub_44E1F0(char *this, int nArg2, char pszArg3)
{
  sub_44E0D0(this, nArg2, pszArg3);
  *(uint32_t *)this = &vftbl_CNRDPooledObject;
  return this;
}



// ------------------------------------------------------------
// 0x44E220 CNRDPooledObject__vmt0 —— CNRDPooledObject::vmt0 删除析构壳
// ·sub_44E250 后按位 0 走 ·sub_657740(this, 284) 池回收（284 字节）
// ------------------------------------------------------------
void **/*thiscall*/ CNRDPooledObject__vmt0(void **this, char pszArg2)
{
  sub_44E250(this);
  if ( (pszArg2 & 1) != 0 )
    sub_657740(this, 284);
  return this;
}



// ------------------------------------------------------------
// 0x44E260 sub_44E260 —— CNRDCharacterTalkBox 构造
// 挂 vftbl_CNRDCharacterTalkBox；文本框 + CNTimer + 布局模板
// 收尾 ·sub_49B520 帧字段读组 + ·sub_49B150 子控件构造与宿主回指
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
// 0x44E2F0 sub_44E2F0 —— 4 字节元素容器尾插单值
// 有空位就地写入并前移 end；否则走 ·sub_44CFA0 扩容插入
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_44E2F0(int *this, int *pDwArg2)
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 2;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 2 )
    return sub_44CFA0((int)this, *(this + 2), 1u, pDwArg2);
  fld_e22 = (int *)*(this + 2);
  *fld_e22 = *pDwArg2;
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x44E340 sub_44E340 —— 8 字节元素容器尾插单值
// 有空位 ·sub_63A7C0 就地构造 +8 前移；否则 ·sub_44D240 扩容插入
// ------------------------------------------------------------
void /*thiscall*/ sub_44E340(int this, int nArg2)
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
    sub_44D240(this, *(char **)(this + 8), 1u, nArg2);
  }
}



// ------------------------------------------------------------
// 0x44E3B0 sub_44E3B0 —— 28 字节记录数组析构遍历（不释放存储）
// [pszArg1,pszArg2) 步长 28 逐元素 ·sub_501490；带 free 的完整版见 ·sub_44F730
// ------------------------------------------------------------
void /*stdcall*/ sub_44E3B0(char *pszArg1, char *pszArg2)
{
  char *i; // esi

  for ( i = pszArg1; i != pszArg2; i += 28 )
    sub_501490(i);
}



// ------------------------------------------------------------
// 0x44E3E0 sub_44E3E0 —— 4 字节元素容器尾插单值（子容器版）
// 与 ·sub_44E2F0 同构（差异：容器基址在宿主 +2404 字节处）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_44E3E0(uint32_t *this, int nArg2)
{
  uint32_t *pThis_259; // ecx
  int v3; // esi
  unsigned int v4; // edx
  int *nArg22; // eax
  unsigned int result; // eax

  pThis_259 = this + 601;
  v3 = pThis_259[1];
  if ( v3 != 0 )
    v4 = (pThis_259[2] - v3) >> 2;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (pThis_259[3] - v3) >> 2 )
    return sub_44CFA0((int)pThis_259, pThis_259[2], 1u, &nArg2);
  nArg22 = (int *)pThis_259[2];
  *nArg22 = nArg2;
  result = (unsigned int)(nArg22 + 1);
  pThis_259[2] = result;
  return result;
}



// ------------------------------------------------------------
// 0x44E440 sub_44E440 —— CNRDQuestListWindow 构造
// IRDWindow 基类起步后挂 vftbl_CNRDQuestListWindow；两组布局模板
// ·sub_433AC0 建两棵 map 哨兵头（+192/+204）；收尾 ·sub_553040 + ·sub_553B70 任务页绘制
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_44E440(uint8_t *this, int nArg2)
{
  uint32_t *v3; // eax
  uint32_t *v4; // eax

  *(uint32_t *)this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(nArg2, 1);
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
// 0x44E590 CNRDQuestListWindow__vmt4 —— CNRDQuestListWindow::vmt4 删除析构壳
// ·sub_44E5C0 后按位 0 j__free；与 ·0x44DD30 同构（差异：析构主体）
// ------------------------------------------------------------
void */*thiscall*/ CNRDQuestListWindow__vmt4(void *Block, char pszArg2)
{
  sub_44E5C0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44E5C0 sub_44E5C0 —— CNRDQuestListWindow 析构主体
// ·sub_553080（任务数据释放）→ 两棵 map 经 ·sub_41D980 递归释放后 j__free；DeleteObject 位图
// 字段清零后回退 vftbl_IRDWindow
// ------------------------------------------------------------
void /*thiscall*/ sub_44E5C0(HGDIOBJ *this)
{
  int v2; // [esp-8h] [ebp-28h]
  int v3; // [esp-8h] [ebp-28h]
  int *fld_e51; // [esp-4h] [ebp-24h]
  int *fld_e48; // [esp-4h] [ebp-24h]
  char v6[4]; // [esp+Ch] [ebp-14h] BYREF
  HGDIOBJ *pThis; // [esp+10h] [ebp-10h]
  int v8; // [esp+1Ch] [ebp-4h]

  pThis = this;
  *this = &vftbl_CNRDQuestListWindow;
  v8 = 5;
  sub_553080();
  fld_e51 = (int *)*(this + 51);
  v2 = *fld_e51;
  LOBYTE(v8) = 4;
  sub_41D980(v6, v2, fld_e51);
  j__free(*(this + 51));
  *(this + 51) = nullptr;
  *(this + 52) = nullptr;
  fld_e48 = (int *)*(this + 48);
  v3 = *fld_e48;
  LOBYTE(v8) = 3;
  sub_41D980(v6, v3, fld_e48);
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
// 0x44E740 sub_44E740 —— 红黑树整体清空
// ·sub_44D180 全区间删除（含递归释放）+ j__free 根哨兵 + 三指针清零
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
// 0x44E780 sub_44E780 —— 对象池归位（活动对象回收）
// 按虚表 +40 取池号 → 活动表线性查得对象 → 虚表 +16 收尾 + ·sub_44C0F0 自活动表摘除
// + ·sub_44E2F0 追加空闲表 + 虚表 +36 经 ·sub_69A580 通知
// ------------------------------------------------------------
void /*thiscall*/ sub_44E780(uint32_t *this, int nArg2)
{
  int pObj; // esi
  int v4; // ebx
  uint32_t *pThis_4; // eax
  uint32_t *pThis_42; // edi
  uint32_t *v7; // ecx
  char *v8; // ecx
  char *v9; // eax
  int v10; // eax
  int v11[2]; // [esp+8h] [ebp-8h] BYREF

  pObj = nArg2;
  v11[1] = (int)this;
  if ( nArg2 != 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 40))(nArg2);
    pThis_4 = (uint32_t *)*(this + 4 * v4 + 34);
    pThis_42 = this + 4 * v4;
    v7 = (uint32_t *)pThis_42[35];
    if ( pThis_4 != v7 )
    {
      do
      {
        if ( *pThis_4 == pObj )
          break;
        ++pThis_4;
      }
      while ( pThis_4 != v7 );
      if ( pThis_4 != v7 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);
        v8 = (char *)pThis_42[35];
        v9 = (char *)pThis_42[34];
        if ( v9 != v8 )
        {
          do
          {
            if ( *(uint32_t *)v9 == pObj )
              break;
            v9 += 4;
          }
          while ( v9 != v8 );
          if ( v9 != v8 )
            sub_44C0F0(pThis_42 + 33, v11, v9);
        }
        sub_44E2F0(pThis_42 + 317, &nArg2);
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 36))(pObj);
        sub_69A580(v10);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x44E850 sub_44E850 —— 按池号批量回收活动对象
// pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项 ·sub_44E3E0 入空闲表
// byte_9D3BE4 为非 0 即跳过（全局标志）【推断】
// ------------------------------------------------------------
char /*thiscall*/ sub_44E850(uint32_t *this, int pArg2)
{
  int v3; // eax
  uint32_t *pThis_4; // ecx
  char *pThis_42; // edi
  uint32_t *j; // esi
  int i; // esi

  if ( pArg2 == 71 )
  {
    for ( i = 0; i < 71; ++i )
      LOBYTE(v3) = sub_44E850(i);
  }
  else
  {
    LOBYTE(v3) = 16 * pArg2;
    pThis_4 = (uint32_t *)*(this + 4 * pArg2 + 34);
    pThis_42 = (char *)(this + 4 * pArg2);
    if ( pThis_4 != nullptr )
    {
      v3 = (*((uint32_t *)pThis_42 + 35) - (int)pThis_4) >> 2;
      if ( v3 != 0 )
      {
        LOBYTE(v3) = byte_9D3BE4;
        if ( byte_9D3BE4 == 0 )
        {
          v3 = *((uint32_t *)pThis_42 + 35);
          for ( j = pThis_4; j != (uint32_t *)v3; ++j )
          {
            sub_44E3E0(*j);
            v3 = *((uint32_t *)pThis_42 + 35);
          }
        }
      }
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x44E8D0 sub_44E8D0 —— 对象池借出（按池号取可用对象）
// 活动数不足阈值 dword_724A98[池] 时从空闲表弹栈，否则回收活动表首项复用；无可用则 ·sub_55B070 新建
// 虚表 +12 初始化失败即归还；成功 ·sub_69A840 通知并返回对象
// ------------------------------------------------------------
int /*thiscall*/ sub_44E8D0(char *this, void *Block, int nArg3, int nArg4)
{
  void *Block2; // edx
  char *pThis_10; // esi
  int v7; // ecx
  unsigned int v8; // eax
  int pObj; // edi
  int *v10; // ecx
  uint32_t *v11; // ecx
  uint32_t *v12; // eax
  int v14; // eax
  int pObj2; // [esp+10h] [ebp-4h] BYREF

  Block2 = Block;
  pThis_10 = this + 16 * (uint32_t)Block;
  v7 = *((uint32_t *)pThis_10 + 34);
  if ( v7 != 0 )
    v8 = (*((uint32_t *)pThis_10 + 35) - v7) >> 2;
  else
    v8 = 0;
  if ( dword_724A98[(uint32_t)Block] > v8 )
  {
    v10 = *((int **)pThis_10 + 318);
    if ( v10 == nullptr || (*((uint32_t *)pThis_10 + 319) - (int)v10) >> 2 == 0 )
      goto LABEL_15;
    pObj = *v10;
    pObj2 = *v10;
  }
  else
  {
    pObj2 = **((uint32_t **)pThis_10 + 34);
    pObj = pObj2;
    sub_44E780(pObj2);
    Block2 = Block;
  }
  if ( pObj == 0 )
  {
LABEL_15:
    pObj = sub_55B070(Block2, (int)this);
    pObj2 = pObj;
    goto LABEL_16;
  }
  v11 = *((uint32_t **)pThis_10 + 319);
  v12 = *((uint32_t **)pThis_10 + 318);
  if ( v12 != v11 )
  {
    do
    {
      if ( *v12 == pObj )
        break;
      ++v12;
    }
    while ( v12 != v11 );
    if ( v12 != v11 )
    {
      memcpy_0(v12, v12 + 1, 4 * ((*((uint32_t *)pThis_10 + 319) - (int)(v12 + 1)) >> 2));
      *((uint32_t *)pThis_10 + 319) -= 4;
    }
  }
LABEL_16:
  if ( pObj == 0 )
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 12))(pObj, nArg3, nArg4) == 0 )
  {
    sub_44E2F0(&pObj2);
    return 0;
  }
  sub_44E2F0(&pObj2);
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 36))(pObj);
  sub_69A840(v14);
  return pObj;
}



// ------------------------------------------------------------
// 0x44EA20 sub_44EA20
// ------------------------------------------------------------
// 模块切换收尾 sub_44EA20(from, to) —— docs/13 §3 定案调用：
// sub_41CC80 迁移矩阵执行后的资源收尾（窗口/声音/上下文按 from/to 清理）
int /*thiscall*/ sub_44EA20(int this, int nArg2, int nArg3)
{
  int nArg32; // ebx
  int i; // edi
  int fld_68; // eax
  int pThis_42; // edi
  int v8; // eax
  int fld_6C2; // eax
  int pThis_43; // edi
  int v11; // eax
  int j; // edi
  int fld_258; // ecx
  uint32_t *fld_2582; // edi
  int fld_278; // ecx
  uint32_t *fld_2782; // edi
  int fld_2B8; // ecx
  uint32_t *fld_2B82; // edi
  int fld_88; // ecx
  uint32_t *fld_882; // edi
  int fld_348; // ecx
  uint32_t *fld_3482; // edi
  int fld_6C; // eax
  int pThis_4; // edi
  int v25; // eax
  int pThis_14; // edi
  int k; // ebx
  int fld_1C; // eax
  int v29; // eax
  int fld_A8; // ecx
  int *fld_A82; // ebx
  int fld_968; // ecx
  unsigned int fld_96C; // edx
  int *fld_96C2; // eax
  int result; // eax
  int v36; // [esp+Ch] [ebp-4h] BYREF

  nArg32 = nArg3;
  if ( dword_9B8880 != 0 )
    sub_5620B0(nArg3);
  if ( nArg3 == 5 )
  {
    for ( i = 0; i < 71; ++i )
      sub_44E850((uint32_t *)this, i);
  }
  else if ( nArg3 != 0 )
  {
    *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 16) + 8) + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 28) + 92) + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 28) + 120) + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 28) + 136) + 17) = 1;
    sub_44E850(dword_8F8528, 30);
LABEL_7:
    if ( nArg3 != 0 )
    {
      if ( nArg3 == 2 || nArg3 == 4 || nArg3 == 6 )
      {
        fld_258 = *(uint32_t *)(this + 600);
        if ( fld_258 != 0 && (*(uint32_t *)(this + 604) - fld_258) >> 2 != 0 && byte_9D3BE4 == 0 )
        {
          fld_2582 = *(uint32_t **)(this + 600);
          if ( fld_258 != *(uint32_t *)(this + 604) )
          {
            do
              sub_44E3E0(*fld_2582++);
            while ( fld_2582 != *(uint32_t **)(this + 604) );
          }
        }
        fld_278 = *(uint32_t *)(this + 632);
        if ( fld_278 != 0 && (*(uint32_t *)(this + 636) - fld_278) >> 2 != 0 && byte_9D3BE4 == 0 )
        {
          fld_2782 = *(uint32_t **)(this + 632);
          if ( fld_278 != *(uint32_t *)(this + 636) )
          {
            do
              sub_44E3E0(*fld_2782++);
            while ( fld_2782 != *(uint32_t **)(this + 636) );
          }
        }
        fld_2B8 = *(uint32_t *)(this + 696);
        if ( fld_2B8 != 0 && (*(uint32_t *)(this + 700) - fld_2B8) >> 2 != 0 && byte_9D3BE4 == 0 )
        {
          fld_2B82 = *(uint32_t **)(this + 696);
          if ( fld_2B8 != *(uint32_t *)(this + 700) )
          {
            do
              sub_44E3E0(*fld_2B82++);
            while ( fld_2B82 != *(uint32_t **)(this + 700) );
          }
        }
        fld_88 = *(uint32_t *)(this + 136);
        if ( fld_88 != 0 && (*(uint32_t *)(this + 140) - fld_88) >> 2 != 0 && byte_9D3BE4 == 0 )
        {
          fld_882 = *(uint32_t **)(this + 136);
          if ( fld_88 != *(uint32_t *)(this + 140) )
          {
            do
              sub_44E3E0(*fld_882++);
            while ( fld_882 != *(uint32_t **)(this + 140) );
          }
        }
        fld_348 = *(uint32_t *)(this + 840);
        if ( fld_348 != 0 && (*(uint32_t *)(this + 844) - fld_348) >> 2 != 0 && byte_9D3BE4 == 0 )
        {
          fld_3482 = *(uint32_t **)(this + 840);
          if ( fld_348 != *(uint32_t *)(this + 844) )
          {
            do
              sub_44E3E0(*fld_3482++);
            while ( fld_3482 != *(uint32_t **)(this + 844) );
          }
        }
        if ( *(uint32_t *)(this + 108) == 7 && *(uint32_t *)(*(uint32_t *)(this + 84) + 16) == 1 )
        {
          fld_6C = *(uint32_t *)(this + 108);
          if ( fld_6C != 12 )
          {
            pThis_4 = *(uint32_t *)(this + 4 * fld_6C + 56);
            v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_4 + 48))(pThis_4);
            sub_69A580(v25);
            *(uint32_t *)(this + 108) = 12;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pThis_4 + 16))(pThis_4);
          }
          nArg32 = nArg3;
        }
        sub_560610(0);
        sub_5403D0(0);
        sub_49A9A0(*(uint32_t *)(this + 2536));
      }
      if ( nArg32 == 1 )
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
      fld_68 = *(uint32_t *)(this + 104);
      if ( fld_68 != 12 )
      {
        pThis_42 = *(uint32_t *)(this + 4 * fld_68 + 56);
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_42 + 48))(pThis_42);
        sub_69A580(v8);
        *(uint32_t *)(this + 104) = 12;
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pThis_42 + 16))(pThis_42);
      }
      fld_6C2 = *(uint32_t *)(this + 108);
      if ( fld_6C2 != 12 )
      {
        pThis_43 = *(uint32_t *)(this + 4 * fld_6C2 + 56);
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_43 + 48))(pThis_43);
        sub_69A580(v11);
        *(uint32_t *)(this + 108) = 12;
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pThis_43 + 16))(pThis_43);
      }
      for ( j = 0; j < 71; ++j )
      {
        if ( j != 27 && j != 36 && j != 43 )
          sub_44E850((uint32_t *)this, j);
      }
      sub_5465E0(*(uint32_t *)(this + 44));
    }
    sub_52C7F0(nArg3 == 4);
    sub_49CD70(nArg3 == 6);
    sub_461470(nArg3 == 6);
    if ( nArg3 == 0 || nArg3 == 2 )
      sub_4BF300(0, 0);
    else
      sub_4BF300(0, 1);
    pThis_14 = this + 20;
    for ( k = 2; k != 0; --k )
    {
      sub_69A580(*(uint32_t *)(*(uint32_t *)(this + 28) + 12));
      sub_69A580(*(uint32_t *)(*(uint32_t *)(this + 28) + 92));
      pThis_14 += 4;
    }
    switch ( nArg3 )
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
        fld_1C = *(uint32_t *)(this + 28);
        if ( *(uint8_t *)(fld_1C + 1474) != 0 )
          v29 = *(uint32_t *)(fld_1C + 20);
        else
          v29 = *(uint32_t *)(fld_1C + 16);
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
        fld_A8 = *(uint32_t *)(this + 168);
        if ( fld_A8 != 0 && (*(uint32_t *)(this + 172) - fld_A8) >> 2 != 0 && byte_9D3BE4 == 0 )
        {
          fld_A82 = *(int **)(this + 168);
          if ( fld_A8 != *(uint32_t *)(this + 172) )
          {
            do
            {
              fld_968 = *(uint32_t *)(this + 2408);
              v36 = *fld_A82;
              if ( fld_968 != 0 )
                fld_96C = (*(uint32_t *)(this + 2412) - fld_968) >> 2;
              else
                fld_96C = 0;
              if ( fld_968 != 0 && fld_96C < (*(uint32_t *)(this + 2416) - fld_968) >> 2 )
              {
                fld_96C2 = *(int **)(this + 2412);
                *fld_96C2 = v36;
                *(uint32_t *)(this + 2412) = fld_96C2 + 1;
              }
              else
              {
                sub_44CFA0(*(void **)(this + 2412), 1, (int)&v36);
              }
              ++fld_A82;
            }
            while ( fld_A82 != *(int **)(this + 172) );
          }
        }
        break;
      default:
        break;
    }
    sub_545860(nArg2, nArg3);
    sub_5466C0(nArg2, nArg3);
    if ( nArg2 == 3 && nArg3 == 1 && word_8F7C10 == word_8F7C14 )
      sub_546170(*(uint32_t *)(this + 44));
    sub_4684F0(*(uint32_t *)(this + 16), nullptr);
    sub_525740(*(uint32_t *)(this + 48));
    result = sub_540960(*(uint32_t *)(this + 116));
    if ( nArg2 == 3 )
    {
      if ( nArg3 != 1 )
        return result;
      return sub_461580(0);
    }
    if ( nArg2 == 6 && nArg3 == 1 )
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
// 0x44F080 sub_44F080 —— 界面切换收尾（关当前子窗 + 批量回收池）
// 按 +104/+108 槽位表关子窗（虚表 +48 取句柄交 ·sub_69A580，虚表 +16 关闭）；·sub_525740 释放
// 批量回收池 17/46/15/16/13/14/19/20/22/23/37；末 ·sub_546730 引导步骤推进
// ------------------------------------------------------------
int /*thiscall*/ sub_44F080(uint32_t *this)
{
  int fld_e26; // eax
  int fld_e262; // eax
  int pObj; // edi
  int v5; // eax
  int fld_e27; // eax
  int pObj2; // edi
  int v8; // eax
  int fld_e11; // ecx

  fld_e26 = *(this + 26);
  if ( fld_e26 == 6 || fld_e26 == 3 || fld_e26 == 9 || fld_e26 == 11 || fld_e26 == 10 )
  {
    fld_e262 = *(this + 26);
    if ( fld_e262 != 12 )
    {
      pObj = *(this + fld_e262 + 14);
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 48))(pObj);
      sub_69A580(v5);
      *(this + 26) = 12;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);
    }
  }
  if ( *(this + 27) == 7 && *(uint32_t *)(*(this + 21) + 16) == 1 )
  {
    fld_e27 = *(this + 27);
    if ( fld_e27 != 12 )
    {
      pObj2 = *(this + fld_e27 + 14);
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);
      sub_69A580(v8);
      *(this + 27) = 12;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2);
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
  fld_e11 = *(this + 11);
  *(this + 626) = 0;
  return sub_546730(fld_e11);
}



// ------------------------------------------------------------
// 0x44F190 sub_44F190 —— 摊位物品点击购入
// 取摊位列表（+80 对象 → +96 向量）第 uArg2 项 → ·sub_44E340 组参数 → ·sub_5634F0 购买执行
// 成功分支：GUI 走 ·sub_540DE0（摊位列表）或 ·sub_44E8D0 包 0x13，否则 ·sub_563410 确认参数
// ------------------------------------------------------------
void /*thiscall*/ sub_44F190(int this, unsigned int uArg2, char pszArg3)
{
  int fld_50; // ecx
  int v5; // edx
  int pObj; // edi
  int fld_9C8; // edi
  int v8; // eax
  int dword_8F84B02; // [esp-Ch] [ebp-34h]
  uint8_t v10[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  int v12; // [esp+Ch] [ebp-1Ch]
  int v13; // [esp+10h] [ebp-18h]
  uint32_t v14[5]; // [esp+14h] [ebp-14h] BYREF

  fld_50 = *(uint32_t *)(this + 80);
  v5 = *(uint32_t *)(fld_50 + 96);
  if ( v5 != 0 && uArg2 < (*(uint32_t *)(fld_50 + 100) - v5) >> 2 )
  {
    pObj = *(uint32_t *)(v5 + 4 * uArg2);
    if ( pObj != 0 )
    {
      Block = nullptr;
      v12 = 0;
      v13 = 0;
      v14[4] = 0;
      v14[0] = pObj;
      v14[1] = 1;
      sub_44E340((int)v10, (int)v14);
      if ( (uint8_t)sub_5634F0(v10, 1) != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 20))(pObj, 1) != 0
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, 8) != 0 )
        {
          fld_9C8 = *(uint32_t *)(this + 2504);
          *(uint32_t *)(this + 2504) = 0;
          sub_540DE0(2, 7, uArg2, 7, 0, fld_9C8 == 4, pszArg3 != 0);
        }
        else if ( pszArg3 != 0 )
        {
          byte_9B8889 = *(uint32_t *)(this + 2504) == 4;
          *(uint32_t *)(this + 2504) = 0;
          sub_44E8D0((char *)this, (void *)0x13, pObj, 1);
        }
        else
        {
          dword_8F84B02 = dword_8F84B0;
          v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);
          sub_563410(*(uint32_t *)(v8 + 4), dword_8F84B02);
        }
      }
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// ------------------------------------------------------------
// 0x44F2E0 sub_44F2E0 —— 出售入口分发
// 不可交易 → 文案 402 经 ·sub_422E70 取串后发包 0x1B；数量<=1 或类型 1/2 走 ·sub_563E90 出售执行
// pszArg3 时改发包 0x14（byte_9B888A=+2504 前值==5）；多件在 dword_8F852C 列表定位后走摊位 ·sub_540DE0(3,...)
// ------------------------------------------------------------
int /*thiscall*/ sub_44F2E0(int this, int nArg2, char pszArg3)
{
  char *v4; // eax
  int result; // eax
  int v6; // edx
  BOOL fld_9C8; // ecx

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 72))(nArg2) == 0 )
  {
    v4 = sub_422E70(402);
    return sub_44E8D0((char *)this, (void *)0x1B, (int)v4, 0);
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 20))(nArg2, 2) != 0 )
    goto LABEL_11;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 20))(nArg2, 1);
  if ( (uint8_t)result == 0 )
    return result;
  if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 44))(nArg2) <= 1 )
  {
LABEL_11:
    if ( pszArg3 != 0 )
    {
      byte_9B888A = *(uint32_t *)(this + 2504) == 5;
      *(uint32_t *)(this + 2504) = 0;
      return sub_44E8D0((char *)this, (void *)0x14, nArg2, 1);
    }
    else
    {
      return sub_563E90(nArg2, 1, this);
    }
  }
  else
  {
    v6 = *((uint32_t *)dword_8F852C + 2);
    for ( result = 0; result < v6; ++result )
    {
      if ( *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * result) == nArg2 )
        break;
    }
    if ( result != v6 )
    {
      fld_9C8 = *(uint32_t *)(this + 2504) == 5;
      *(uint32_t *)(this + 2504) = 0;
      return sub_540DE0(3, 0, result, 7, 0, fld_9C8, pszArg3 != 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x44F400 sub_44F400 —— 修理入口
// 拒绝文案 403/404/405/406/407（·sub_422E70 + 包 0x1B，407 用 sprintf 填差额）
// 费用/耐久经 ·sub_5640D0 修理费计算比对；通过则 ·sub_5641E0 修理执行或发包 0x16（byte_9B888B=+2504 前值==6）
// ------------------------------------------------------------
int /*thiscall*/ sub_44F400(int this, int nArg2, char pszArg3)
{
  int pObj; // esi
  char *v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // eax
  unsigned int v10; // edi
  char *v12; // eax
  bool fld_9C8; // zf
  char *v14; // [esp-8h] [ebp-58h]
  unsigned int v15; // [esp-4h] [ebp-54h]
  char Buffer[64]; // [esp+Ch] [ebp-44h] BYREF
  int dword_796E502; // [esp+4Ch] [ebp-4h]

  pObj = nArg2;
  dword_796E502 = dword_796E50;
  if ( nArg2 != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 20))(nArg2, 2) == 0 )
    {
      v5 = sub_422E70(403);
LABEL_10:
      v14 = v5;
      return sub_44E8D0((char *)this, (void *)0x1B, (int)v14, 0);
    }
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj);
    if ( sub_41A5E0(v6 + 18) == 0 )
    {
      v5 = sub_422E70(404);
      goto LABEL_10;
    }
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 188))(pObj);
    v8 = sub_41A5E0(v7 + 32);
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj);
    if ( v8 >= sub_41A5E0(v9 + 18) )
    {
      v5 = sub_422E70(405);
      goto LABEL_10;
    }
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 180))(pObj);
  }
  else
  {
    nArg2 = 0;
    v10 = sub_5640D0(&nArg2);
    if ( nArg2 == 0 )
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
  if ( pszArg3 == 0 )
    return sub_5641E0(pObj, this);
  if ( pObj == 0 || (fld_9C8 = *(uint32_t *)(this + 2504) == 6, byte_9B888B = 1, !fld_9C8) )
    byte_9B888B = 0;
  *(uint32_t *)(this + 2504) = 0;
  return sub_44E8D0((char *)this, (void *)0x16, pObj, 0);
}



// ------------------------------------------------------------
// 0x44F580 sub_44F580 —— 道具二次校验分发（拒绝文案 408/409/410/411）
// 校验属性 2 与属性 64；以 ·sub_47DC90 全局对象 +510 字段为系数与对象 +24 字段比较
// 达标发包 0x17（第 4 参为 +2504 前值==7），否则包 0x1B
// ------------------------------------------------------------
char /*thiscall*/ sub_44F580(int this, int nArg2, char pszArg3)
{
  char *v4; // eax
  char result; // al
  int v6; // eax
  int v7; // ebx
  char *v8; // eax
  char *v9; // eax
  int fld_9C8; // ebx

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 20))(nArg2, 2) == 0 )
  {
    v4 = sub_422E70(408);
    return sub_44E8D0((char *)this, (void *)0x1B, (int)v4, 0);
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 64))(nArg2) == 0 )
  {
    v4 = sub_422E70(409);
    return sub_44E8D0((char *)this, (void *)0x1B, (int)v4, 0);
  }
  v6 = sub_47DC90(dword_791ED8);
  v7 = sub_41A5E0(v6 + 510);
  if ( v7 != 0 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2) + 24) <= 10 * v7 )
    {
      result = pszArg3;
      if ( pszArg3 != 0 )
      {
        fld_9C8 = *(uint32_t *)(this + 2504);
        *(uint32_t *)(this + 2504) = 0;
        return sub_44E8D0((char *)this, (void *)0x17, nArg2, fld_9C8 == 7);
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
// 0x44F670 sub_44F670 —— 道具校验分发 2（拒绝文案 1652/1653/1664）
// 属性 2 校验；属性 172==9 拒（1664），属性 68 通过后发包 0x3B（第 4 参为 +2504 前值==18）
// ------------------------------------------------------------
char /*thiscall*/ sub_44F670(int this, int nArg2, char pszArg3)
{
  char *v4; // eax
  char result; // al
  char *v6; // eax
  char *v7; // eax
  BOOL fld_9C8; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 20))(nArg2, 2) != 0 )
  {
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 172))(nArg2) == 9 )
    {
      v6 = sub_422E70(1664);
      return sub_44E8D0((char *)this, (void *)0x1B, (int)v6, 0);
    }
    else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 68))(nArg2) != 0 )
    {
      result = pszArg3;
      if ( pszArg3 != 0 )
      {
        fld_9C8 = *(uint32_t *)(this + 2504) == 18;
        *(uint32_t *)(this + 2504) = 0;
        return sub_44E8D0((char *)this, (void *)0x3B, nArg2, fld_9C8);
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
// 0x44F730 sub_44F730 —— 28 字节记录数组析构释放
// 遍历 ·sub_501490 后 j__free 基址 + 三指针清零（与 ·sub_44E3B0 同构，差异：自持存储并释放）
// ------------------------------------------------------------
int /*thiscall*/ sub_44F730(int this)
{
  char *fld_4; // esi
  int result; // eax
  char *i; // edi

  fld_4 = *(char **)(this + 4);
  result = 0;
  if ( fld_4 != nullptr )
  {
    for ( i = *(char **)(this + 8); fld_4 != i; fld_4 += 28 )
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
// 0x44F770 sub_44F770 —— 84 字节记录数组析构释放
// 遍历 ·sub_44C2A0（对象+字符串成对释放弃构体）后 j__free 基址 + 三指针清零
// ------------------------------------------------------------
int /*thiscall*/ sub_44F770(int this)
{
  char *fld_4; // esi
  int result; // eax
  char *i; // edi

  fld_4 = *(char **)(this + 4);
  result = 0;
  if ( fld_4 != nullptr )
  {
    for ( i = *(char **)(this + 8); fld_4 != i; fld_4 += 84 )
      sub_44C2A0(fld_4);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x44F7B0 sub_44F7B0 —— CNRDItemShopWindow 构造
// IRDWindow 基类起步后挂 vftbl_CNRDItemShopWindow；双 CNTimer + ·sub_433AC0 建 map 哨兵头（+144）
// 收尾 ·sub_564650（道具商店数据）+ ·sub_5654D0 商品页绘制
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_44F7B0(uint32_t *this, int nArg2)
{
  uint32_t *v3; // eax

  *this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(nArg2, 0);
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
// 0x44F8C0 CNRDItemShopWindow__vmt4 —— CNRDItemShopWindow::vmt4 删除析构壳
// ·sub_44F8F0 后按位 0 j__free；与 ·0x44DD30 同构（差异：析构主体）
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemShopWindow__vmt4(void *Block, char pszArg2)
{
  sub_44F8F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44F8F0 sub_44F8F0 —— CNRDItemShopWindow 析构主体
// ·sub_565AD0（商品数据释放）→ 内嵌 IObject 虚表复位 + ·sub_44D180 树清 + j__free 缓冲
// 回退 vftbl_IRDWindow
// ------------------------------------------------------------
void /*thiscall*/ sub_44F8F0(int this)
{
  int v2; // [esp-8h] [ebp-28h]
  int *fld_90; // [esp-4h] [ebp-24h]
  int v4[2]; // [esp+Ch] [ebp-14h] BYREF
  int v5; // [esp+1Ch] [ebp-4h]

  v4[1] = this;
  *(uint32_t *)this = &vftbl_CNRDItemShopWindow;
  v5 = 4;
  sub_565AD0();
  *(uint32_t *)(this + 152) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 156) = 0;
  fld_90 = *(int **)(this + 144);
  v2 = *fld_90;
  LOBYTE(v5) = 2;
  sub_44D180((int **)(this + 140), v4, v2, (int)fld_90);
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
// 0x44F9B0 sub_44F9B0 —— CNRDItemProductWindow 构造
// IRDWindow 基类起步后挂 vftbl_CNRDItemProductWindow；CNTimer + map 哨兵头（+132）+ 0x10×5 控件数组
// 收尾 ·sub_566570（橱窗数据）+ ·sub_566C60 橱窗页绘制
// ------------------------------------------------------------
char */*thiscall*/ sub_44F9B0(char *this, int nArg2)
{
  uint32_t *v3; // eax

  *(uint32_t *)this = &vftbl_IRDWindow;
  sub_540330();
  sub_540340(nArg2, 0);
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
// 0x44FAF0 CNRDItemProductWindow__vmt4 —— CNRDItemProductWindow::vmt4 删除析构壳
// ·sub_44FB20 后按位 0 j__free；与 ·0x44DD30 同构（差异：析构主体）
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemProductWindow__vmt4(void *Block, char pszArg2)
{
  sub_44FB20();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x44FB20 sub_44FB20 —— CNRDItemProductWindow 析构主体
// ·sub_5672B0（橱窗数据释放）→ DeleteObject 位图 + 0x10×5 eh vector destructor + map 树清
// （·sub_44D180）+ j__free；回退 vftbl_IRDWindow
// ------------------------------------------------------------
void /*thiscall*/ sub_44FB20(char *this)
{
  int v2; // [esp-8h] [ebp-28h]
  int *pThis_21; // [esp-4h] [ebp-24h]
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
  pThis_21 = *((int **)this + 33);
  v2 = *pThis_21;
  LOBYTE(v5) = 1;
  sub_44D180((int **)this + 32, v4, v2, (int)pThis_21);
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
// 0x44FC40 sub_44FC40 —— NPC 交互主分发（点击/输入状态机）
// 关闭当前子窗（虚表 +28）并校验全局上下文后，·sub_45E870 点击取目标对象；按属性 40 分派
// 摊位/商店支路：·sub_541D80 上架 / ·sub_44ABE0 选中 / ·sub_541A60 子页 / ·sub_541ED0 上架参数 /
// ·sub_526BF0 与 ·sub_567F40 联动；拒绝文案 399/400 发包 0x1B
// ------------------------------------------------------------
char /*thiscall*/ sub_44FC40(int this)
{
  int fld_68; // eax
  int pThis_4; // edi
  int pThis_42; // ebx
  int fld_6C; // eax
  int fld_9C8; // eax
  int pObj2; // edi
  int v8; // eax
  int pObj; // edi
  int v10; // eax

  fld_68 = *(uint32_t *)(this + 104);
  pThis_4 = 0;
  pThis_42 = 0;
  if ( fld_68 != 12 )
    pThis_4 = *(uint32_t *)(this + 4 * fld_68 + 56);
  fld_6C = *(uint32_t *)(this + 108);
  if ( fld_6C != 12 )
    pThis_42 = *(uint32_t *)(this + 4 * fld_6C + 56);
  LOBYTE(fld_9C8) = sub_4633D0(*(uint32_t *)(this + 16));
  if ( (uint8_t)fld_9C8 == 0 )
  {
    if ( pThis_4 == 0 || (LOBYTE(fld_9C8) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_4 + 28))(pThis_4), (uint8_t)fld_9C8 == 0) )
    {
      if ( pThis_42 == 0 || (LOBYTE(fld_9C8) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_42 + 28))(pThis_42), (uint8_t)fld_9C8 == 0) )
      {
        fld_9C8 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 36);
        if ( *(uint8_t *)(fld_9C8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_9C8 + 12) )
        {
          fld_9C8 = *(uint32_t *)(this + 2504);
          if ( fld_9C8 != 1 && fld_9C8 != 2 )
          {
            fld_9C8 = *(uint32_t *)(dword_8F7A24 + 12);
            if ( fld_9C8 == 1 )
            {
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
              fld_9C8 = sub_45E870(pt.x, pt.y, 1);
              pObj = fld_9C8;
              if ( fld_9C8 == 0 )
              {
                if ( *(uint32_t *)(this + 2504) == 16 )
                  LOBYTE(fld_9C8) = sub_541D80();
                return fld_9C8;
              }
              if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_9C8 + 40))(fld_9C8, 34) == 0 )
              {
                if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 66) != 0 )
                {
                  LOBYTE(fld_9C8) = *(uint8_t *)(pObj + 284);
                  if ( *(uint32_t *)(dword_8F7C08 + 648) == pObj )
                  {
                    if ( (uint8_t)fld_9C8 == 0 || *(uint8_t *)(pObj + 285) != 0 )
                      LOBYTE(fld_9C8) = sub_44ABE0(16);
                    else
                      LOBYTE(fld_9C8) = sub_541A60(1);
                  }
                  else if ( (uint8_t)fld_9C8 != 0 )
                  {
                    LOBYTE(fld_9C8) = *(uint8_t *)(pObj + 285);
                    if ( (uint8_t)fld_9C8 == 0 )
                    {
                      v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pObj + 288) + 52))(*(uint32_t *)(pObj + 288));
                      LOBYTE(fld_9C8) = sub_541ED0(v10);
                    }
                  }
                }
                else
                {
                  LOBYTE(fld_9C8) = sub_526BF0(pObj, 1);
                }
                return fld_9C8;
              }
            }
            else
            {
              if ( fld_9C8 != 6 )
                return fld_9C8;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
              fld_9C8 = sub_45E870(pt.x, pt.y, 1);
              if ( fld_9C8 == 0 )
                return fld_9C8;
              LOBYTE(fld_9C8) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_9C8 + 40))(fld_9C8, 34);
              if ( (uint8_t)fld_9C8 == 0 )
                return fld_9C8;
            }
            LOBYTE(fld_9C8) = sub_567F40(1);
            return fld_9C8;
          }
          if ( fld_9C8 != 2 )
            return fld_9C8;
          fld_9C8 = *(uint32_t *)(this + 2508);
          if ( fld_9C8 == 3 || fld_9C8 == 4 )
          {
            fld_9C8 = sub_44A980(*(uint32_t *)(this + 2516));
            pObj2 = fld_9C8;
            if ( fld_9C8 != 0 )
            {
              fld_9C8 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_9C8 + 16))(fld_9C8) + 4);
              if ( fld_9C8 == *(uint32_t *)(this + 2512) )
              {
                if ( *(uint32_t *)(dword_8F7A24 + 12) != 3
                  || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 76))(pObj2) == 0 )
                {
                  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 84))(pObj2) == 0 )
                  {
                    v8 = sub_422E70(399);
                    goto LABEL_25;
                  }
                  if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2) > 1 )
                  {
                    LOBYTE(fld_9C8) = sub_540DE0(0, 0, *(uint32_t *)(this + 2516), 7, 0, 0, 0);
                    return fld_9C8;
                  }
LABEL_36:
                  LOBYTE(fld_9C8) = sub_44E8D0((char *)this, (void *)0x15, pObj2, 1);
                  return fld_9C8;
                }
                if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 44))(pObj2) <= 1 )
                  LOBYTE(fld_9C8) = sub_486330(*(uint32_t *)(this + 2516), 1);
                else
                  LOBYTE(fld_9C8) = sub_540DE0(4, 0, *(uint32_t *)(this + 2516), 7, 0, 0, 0);
              }
            }
          }
          else if ( fld_9C8 == 2 )
          {
            fld_9C8 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(
                   dword_8F7C04,
                   *(uint32_t *)(this + 2516));
            pObj2 = fld_9C8;
            if ( fld_9C8 != 0 )
            {
              fld_9C8 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_9C8 + 16))(fld_9C8) + 4);
              if ( fld_9C8 == *(uint32_t *)(this + 2512) )
              {
                if ( *(uint32_t *)(dword_8F7A24 + 12) == 3
                  && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 76))(pObj2) != 0 )
                {
                  LOBYTE(fld_9C8) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1088))(
                                 dword_8F7C04,
                                 *(uint32_t *)(this + 2516));
                  return fld_9C8;
                }
                if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 84))(pObj2) == 0 )
                {
                  v8 = sub_422E70(400);
LABEL_25:
                  LOBYTE(fld_9C8) = sub_44E8D0((char *)this, (void *)0x1B, v8, 0);
                  return fld_9C8;
                }
                goto LABEL_36;
              }
            }
          }
        }
      }
    }
  }
  return fld_9C8;
}


// ------------------------------------------------------------
// 0x44FF60 sub_44FF60 —— CNRDPVPInterface 构造
// 挂 vftbl_CNRDPVPInterface；四组布局模板（0/6/12/0/1600 序列，源码自证）
// 收尾 ·sub_52A730 + ·sub_52CA40(Block)
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


