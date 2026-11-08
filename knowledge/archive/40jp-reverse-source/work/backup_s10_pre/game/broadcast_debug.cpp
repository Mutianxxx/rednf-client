// ============================================================
// 【40JP逆向源代码工程】src/game/broadcast_debug.cpp  —— L1 精修层
// 模块: 播报层(HUD 评价横幅)/调试引导/游戏Socket 封装/转职·驴子/数据总装
// 来源: work/dump_combat.txt  区块: 0x420000-0x440000（0x42/0x43 两个 64K 块, 644 函数）
// 层级: L1 —— 在 L2 转写之上升级注释与分区；函数体零改动（剥离注释后逐行可比对）
//
// 字符串证据（本区身份）:
//   播报层    HK_ATTACKED / HK_TECHNIC / HK_STYLE / HK1_AIRIAL / HK2_AIRIAL / R_HK2_*GOOD
//   调试      'ScreenShot' 'Shell_TrayWnd' 'ConsoleDebug' 'DebugConfig.txt' 'Run Error'
//             'Fatal Error' 'DNF.trc' 'CStringManager::getStr(%d)'
//   Socket    '[-> COMMAND PACKET] Packet : %s…' 'SOCKET CLOSE %d' 'SendLock '
//   转职/驴子 'JOB_CONVERTER' ClassChange%02d.ptl 'Donkey exist already'
//   数据总装  'PriceTable.tbl' 'PVPPriceTable.tbl' 'ExpTable.tbl' 'Sprite/' 'SHUTTER_ON'
//   GM 命令   '//level' '//levelto' '//add skill/item' '//warroomtime' '//pvprank'
//
// ★ 播报层 sub_426820（研究 §12 定案：HUD 三轴评价横幅系统）—— 本文件内三轴读写点:
//   写: 0x426820 case3 HK_ATTACKED this+556 += 伤害 / case6 HK_STYLE this+628 = a3 /
//       case7 HK_TECHNIC this+592 = a3 / case5 this+900 = a3；显示窗 1500ms(sub_698F90)
//   读: 0x426080(+556, 图98, id248) / 0x425DA0(+592, 图99, id277/278) /
//       0x425F10(+628, 图43, id298/299)；窗钟对 +560/+584、+596/+620、+632/+656
//   复位: 0x423C10(全轴清零, +1252=8) / 0x424D80(28 字节槽, 500ms) / 0x42F250(全组清零)
//   tick 汇聚: 0x427E90 → 4271B0(组队双槽) → 426080 → 426200 → 425DA0 → 425F10
//   组队双槽: 0x4271B0（+248[i] vs 阈值 dword_6C38A4[i] → 'HK_STYLE' 语音 + 串 496/497）
//   语音广播: dword_8F7C04 vt+212（标签播放）
//   跨文件调用面（grep src/ 实证，研究空白补全）:
//     src/cnrd/IRDActiveObject.cpp:61  = 0x4D49E0(vmt220 = vt+544 终结算) → (…, 3, a3)
//     src/game/combat_core.cpp:2709    0x4D49E0 L2 副本 → (…, 3, 伤害)
//     src/game/combat_core.cpp:2973    (…, 0, 0) 横幅模式 0（限本机玩家 dword_8F7C04）
//     src/game/hiteff_monster.cpp:3208 (…, 4, 0) 死亡播报
//     src/game/hiteff_monster.cpp:4531 (…, 1, 0) 横幅模式 1
//     src/game/hiteff_monster.cpp:4538 (…, 2, 0) 横幅模式 2
//     src/game/anim_parser.cpp:5378    (…, 6, v) HK_STYLE（动画帧事件）
//     src/game/anim_parser.cpp:5386    (…, 7, v) HK_TECHNIC（动画帧事件）
//     src/combat/bigfunc_57A980_sub_57A980.cpp:3506  (…, 5, v) 伤害数字（命中主处理器）
//
// 交叉引用: 0x423200/0x423290/0x423380 两步式发包 —— 已精修版见 src/nengine/net_socket.cpp
//           0x428050 连击宿主（研究 §9）；0x4D49E0 精修版见 src/cnrd/IRDActiveObject.cpp
//
// 函数数: 644（VA 标记计数，L1 未增删）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// §1 启动 · 关停（0x420070-0x420550）
//   关停清理链 / 图形与资源启动(640x480·ImagePacks2·'ScreenShot') / CRT 异常桩
// ============================================================
// ------------------------------------------------------------
// 0x420070 sub_420070
// ------------------------------------------------------------
// 【关停清理链】逐个释放全局管理器（各虚表槽0=析构、实参1）：dword_99FCC8 /
//   dword_8F7B08(CNGameSocket 全局实例) / dword_99FD5C / 99FD60 / 99FD64 / 99FD68；
//   字符串管理器本体 dword_99FD6C → sub_41FF40 + free；dword_8F7A24 复位；
//   sub_438910 资源回收；this+4 复位。与退出清理 sub_41C1E0（0x433690 调试退出引用）同链。
int /*thiscall*/ sub_420070(uint8_t *this)
{
  void *dword_99FD6C2; // esi

  if ( dword_79C0A0 != 0 )
  {
    *(uint32_t *)(dword_79C0A0 + 124) = 0;
    *(uint32_t *)(dword_79C0A0 + 128) = 0;
  }
  sub_41C240(this);
  dword_8F7A24 = 0;
  sub_438910();
  if ( dword_99FCC8 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_99FCC8)(dword_99FCC8, 1);
  dword_99FCC8 = 0;
  if ( dword_8F7B08 != 0 )
  {
    (**(void (/*thiscall*/ ***)(int, int))dword_8F7B08)(dword_8F7B08, 1);
    dword_8F7B08 = 0;
  }
  if ( dword_99FD5C != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_99FD5C)(dword_99FD5C, 1);
  dword_99FD5C = 0;
  if ( dword_99FD60 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_99FD60)(dword_99FD60, 1);
  dword_99FD60 = 0;
  if ( dword_99FD64 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_99FD64)(dword_99FD64, 1);
  dword_99FD64 = 0;
  if ( dword_99FD6C != nullptr )
  {
    dword_99FD6C2 = dword_99FD6C;
    sub_41FF40();
    j__free(dword_99FD6C2);
  }
  dword_99FD6C = nullptr;
  if ( dword_99FD68 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_99FD68)(dword_99FD68, 1);
  dword_99FD68 = 0;
  sub_41FD50();
  sub_403BE0();
  *(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x420160 sub_420160
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_420160(uint32_t *uArg1, int nArg2, int nArg3)
{
  sub_41FFE0(uArg1, nArg2, nArg3);
  return &uArg1[nArg2];
}



// ------------------------------------------------------------
// 0x420190 sub_420190
// ------------------------------------------------------------
// 【图形/资源启动】sub_432F70 校验 → 主控 vt+4(3) 申领设备 → '!ImagePacks' 探测
//   （缺省改用 'ImagePacks2/'）→ 640x480x16 主画面（窗口模式字节 dword_8F7A24+112）→
//   'ScreenShot' 目录（sub_401710 ×2）→ dword_79C0A4 vt+8(7) 申领渲染器 dword_79C0B0。
//   失败弹串 588-593（CStringManager）。被 0x420DA0 引导调用。
int /*usercall*/ sub_420190@<eax>(int nArg1@<ebx>, int nArg2@<esi>)
{
  int v3; // esi
  const CHAR *v4; // eax
  int dword_79C0A42; // esi
  int v6; // esi
  int v7; // esi
  const CHAR *v8; // eax
  const CHAR *v9; // [esp-10h] [ebp-78h]
  const CHAR *v10; // [esp-10h] [ebp-78h]
  uint8_t v12[4]; // [esp+4h] [ebp-64h] BYREF
  void *Block; // [esp+8h] [ebp-60h]
  int v14; // [esp+18h] [ebp-50h]
  unsigned int v15; // [esp+1Ch] [ebp-4Ch]
  uint8_t v16[28]; // [esp+20h] [ebp-48h] BYREF
  uint8_t v17[28]; // [esp+3Ch] [ebp-2Ch] BYREF
  int dword_796E502; // [esp+58h] [ebp-10h]
  int v19; // [esp+64h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( (uint8_t)sub_432F70() == 0 )
    return 0x80000000;
  v3 = (*(int (/*thiscall*/ **)(int, int, int *))(*(uint32_t *)dword_79C0A0 + 4))(dword_79C0A0, 3, &dword_79C0A4);
  _access("_ImagePacks", 0);
  if ( _access("!ImagePacks", 0) != 0 )
  {
    v15 = 15;
    v14 = 0;
    LOBYTE(Block) = 0;
    sub_4015C0("ImagePacks2/", 0xCu);
    v19 = 0;
    sub_407CB0(v12);
    v19 = -1;
    if ( v15 >= 0x10 )
      j__free(Block);
    v15 = 15;
    v14 = 0;
    LOBYTE(Block) = 0;
  }
  if ( v3 < 0 )
  {
    v9 = (const CHAR *)sub_422E70(589);
    v4 = (const CHAR *)sub_422E70(588);
LABEL_9:
    MessageBoxA(nullptr, v4, v9, 0);
    return v3;
  }
  sub_404330(640, 480);
  v3 = sub_407C40(640, 480, 16, *(uint8_t *)(dword_8F7A24 + 112));
  if ( v3 < 0 )
  {
    v9 = (const CHAR *)sub_422E70(591);
    v4 = (const CHAR *)sub_422E70(590);
    goto LABEL_9;
  }
  dword_79C0A42 = dword_79C0A4;
  sub_401710("ScreenShot");
  v19 = 1;
  sub_401710("ScreenShot");
  v6 = *(uint32_t *)(dword_79C0A42 + 8252);
  LOBYTE(v19) = 2;
  dword_9D3BE0 = sub_699760(v6, v16, v17, 1);
  v7 = (*(int (/*thiscall*/ **)(int, int, int *))(*(uint32_t *)dword_79C0A4 + 8))(dword_79C0A4, 7, &dword_79C0B0);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(593);
    v8 = (const CHAR *)sub_422E70(592);
LABEL_32:
    MessageBoxA(nullptr, v8, v10, 0);
    sub_501490(v17);
    sub_501490(v16);
    return v7;
  }
  v7 = (*(int (/*thiscall*/ **)(int, int, int *))(*(uint32_t *)dword_79C0A0 + 12))(dword_79C0A0, 2, &dword_79C0A8);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(595);
    v8 = (const CHAR *)sub_422E70(594);
    goto LABEL_32;
  }
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0A8 + 8))(dword_79C0A8);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(597);
    v8 = (const CHAR *)sub_422E70(596);
    goto LABEL_32;
  }
  v7 = (*(int (/*thiscall*/ **)(int, uint32_t, int *))(*(uint32_t *)dword_79C0A8 + 16))(dword_79C0A8, 0, &dword_79C0B4);
  if ( dword_79C0B4 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(599);
    v8 = (const CHAR *)sub_422E70(598);
    goto LABEL_32;
  }
  v7 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B4 + 4))(dword_79C0B4, 0);
  if ( dword_79C0B4 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(601);
    v8 = (const CHAR *)sub_422E70(600);
    goto LABEL_32;
  }
  (*(void (/*thiscall*/ **)(int, int, int *, int, int))(*(uint32_t *)dword_79C0A8 + 16))(
    dword_79C0A8,
    1,
    &dword_79C0B8,
    nArg2,
    nArg1);
  if ( dword_79C0B8 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B8 + 4))(dword_79C0B8, 0);
  v7 = (*(int (/*thiscall*/ **)(int, int, int *))(*(uint32_t *)dword_79C0A0 + 16))(dword_79C0A0, 2, &dword_79C0AC);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(603);
    v8 = (const CHAR *)sub_422E70(602);
    goto LABEL_32;
  }
  v7 = sub_407AE0(dword_79C0A4);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(605);
    v8 = (const CHAR *)sub_422E70(604);
    goto LABEL_32;
  }
  v7 = (*(int (/*thiscall*/ **)(int, int, int *))(*(uint32_t *)dword_79C0AC + 4))(dword_79C0AC, 3, &dword_99FCCC);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(607);
    v8 = (const CHAR *)sub_422E70(606);
    goto LABEL_32;
  }
  v7 = sub_4163F0(dword_99FCCC);
  if ( v7 < 0 )
  {
    v10 = (const CHAR *)sub_422E70(609);
    v8 = (const CHAR *)sub_422E70(608);
    goto LABEL_32;
  }
  dword_9D3BD8 = dword_99FCCC;
  SetClassLongA(*(HWND *)(dword_79C0A0 + 16), -26, 3);
  sub_501490(v17);
  sub_501490(v16);
  return 1;
}


// ------------------------------------------------------------
// 0x420550 sub_420550
// ------------------------------------------------------------
// 【CRT 桩】std::length_error("vector<T> too long") 抛出 —— vector 扩容越界共用路径。
void /*noreturn*/ sub_420550()
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



// ============================================================
// §2 窗口最小化与容器辅助（0x4205C0-0x420D80）
//   nmodule::nMinimizeWindows('Shell_TrayWnd' 任务栏消息) / vector push·insert 辅助 /
//   窗口枚举；0x420DA0 = 引擎主引导入口（'ConsoleDebug'·'DebugConfig.txt' 校验）
// ============================================================
// ------------------------------------------------------------
// 0x4205C0 sub_4205C0
// ------------------------------------------------------------
// 【最小化窗口模块】v2==1 → FindWindowA("Shell_TrayWnd") + SendMessageA(WM_COMMAND,
//   0x1A0) 收起任务栏；v2==0 → 逐项 ShowWindow 恢复并清空句柄表。'Shell_TrayWnd' 证据。
int /*thiscall*/ sub_4205C0(void *this)
{
  int pThis_1; // eax
  int v3; // eax
  HWND WindowA; // eax
  int i; // esi

  *(uint32_t *)this = &vftbl_nmodule__nMinimizeWindows;
  pThis_1 = *((uint32_t *)this + 1);
  if ( pThis_1 != 0 )
  {
    v3 = pThis_1 - 1;
    if ( v3 != 0 )
    {
      if ( v3 == 1 )
        sub_41FCF0();
    }
    else
    {
      WindowA = FindWindowA("Shell_TrayWnd", nullptr);
      if ( WindowA != nullptr )
        SendMessageA(WindowA, 0x111u, 0x1A0u, 0);
    }
  }
  else
  {
    for ( i = *((uint32_t *)this + 3); i != *((uint32_t *)this + 4); i += 8 )
      ShowWindow(*(HWND *)i, *(uint32_t *)(i + 4));
    if ( *((uint32_t *)this + 3) != 0 )
      j__free(*((void **)this + 3));
    *((uint32_t *)this + 3) = 0;
    *((uint32_t *)this + 4) = 0;
    *((uint32_t *)this + 5) = 0;
  }
  if ( *((uint32_t *)this + 3) != 0 )
    j__free(*((void **)this + 3));
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4206A0 nmodule__nMinimizeWindows__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nmodule__nMinimizeWindows__vmt0(void *Block, char pszArg2)
{
  sub_4205C0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4206D0 sub_4206D0
// ------------------------------------------------------------
void /*thiscall*/ sub_4206D0(int this, unsigned int **pDwArg2, unsigned int uArg3, unsigned int **pDwArg4)
{
  int fld_4; // edx
  unsigned int fld_C; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v10; // eax
  int fld_87; // ecx
  int fld_88; // eax
  char *pMem; // edi
  void **fld_43; // ecx
  int fld_89; // eax
  unsigned int v16; // ebx
  char *fld_83; // eax
  int v18; // ecx
  int fld_86; // ebx
  unsigned int **v20; // ebx
  unsigned int **v21; // eax
  unsigned int **fld_42; // [esp-18h] [ebp-40h]
  unsigned int **v23; // [esp-18h] [ebp-40h]
  int fld_85; // [esp-Ch] [ebp-34h]
  unsigned int fld_84; // [esp-8h] [ebp-30h]
  int v26; // [esp+0h] [ebp-28h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int pThis; // [esp+10h] [ebp-18h]
  void *v29[2]; // [esp+14h] [ebp-14h] BYREF
  int v30; // [esp+24h] [ebp-4h]
  unsigned int **v31; // [esp+34h] [ebp+Ch]
  int v32; // [esp+38h] [ebp+10h]
  int v33; // [esp+38h] [ebp+10h]

  v29[1] = &v26;
  pThis = this;
  v29[0] = nullptr;
  sub_41B0D0((unsigned int **)v29, pDwArg4);
  fld_4 = *(uint32_t *)(this + 4);
  v30 = 0;
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 2;
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_401830(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(char **)(this + 8);
      v18 = 4 * uArg3;
      Block = fld_83;
      v33 = 4 * uArg3;
      if ( (fld_83 - (char *)pDwArg2) >> 2 >= uArg3 )
      {
        v20 = (unsigned int **)&fld_83[-v18];
        v21 = sub_41CB60((unsigned int **)&fld_83[-v18], (unsigned int **)fld_83, (unsigned int **)fld_83);
        v23 = (unsigned int **)Block;
        *(uint32_t *)(this + 8) = v21;
        sub_41FF20(pDwArg2, v20, v23);
        sub_41FE80(pDwArg2, &pDwArg2[v33 / 4u], (unsigned int **)v29);
      }
      else
      {
        sub_41CB60(pDwArg2, (unsigned int **)fld_83, &pDwArg2[v18 / 4u]);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - (int)pDwArg2) >> 2);
        fld_85 = *(uint32_t *)(this + 8);
        LOBYTE(v30) = 3;
        sub_420160(fld_85, fld_84, v29);
        fld_86 = v33 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        v30 = 0;
        sub_41FE80(pDwArg2, (unsigned int **)(fld_86 - v33), (unsigned int **)v29);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (fld_C >> 1) >= fld_C )
        v10 = (fld_C >> 1) + fld_C;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
      else
        fld_87 = 0;
      if ( v10 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
        else
          fld_88 = 0;
        v10 = uArg3 + fld_88;
      }
      v32 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      fld_42 = *(unsigned int ***)(this + 4);
      Block = pMem;
      LOBYTE(v30) = 1;
      v31 = sub_41CB60(fld_42, pDwArg2, (unsigned int **)pMem);
      sub_41FFE0(v31, uArg3, (unsigned int **)v29);
      sub_41CB60(pDwArg2, *(unsigned int ***)(this + 8), &v31[uArg3]);
      fld_43 = *(void ***)(this + 4);
      v30 = 0;
      if ( fld_43 != nullptr )
        fld_89 = (*(uint32_t *)(this + 8) - (int)fld_43) >> 2;
      else
        fld_89 = 0;
      v16 = fld_89 + uArg3;
      if ( fld_43 != nullptr )
      {
        sub_4016E0(fld_43, *(void ***)(this + 8));
        j__free(*(void **)(this + 4));
      }
      *(uint32_t *)(this + 12) = &pMem[v32];
      *(uint32_t *)(this + 8) = &pMem[4 * v16];
      *(uint32_t *)(this + 4) = pMem;
    }
  }
  v30 = -1;
  sub_41B010(v29);
}


// ------------------------------------------------------------
// 0x420960 sub_420960
// ------------------------------------------------------------
void /*thiscall*/ sub_420960(int this, int nArg2, unsigned int uArg3, int pArg4)
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
      sub_420550(this);
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
// 0x420BB0 sub_420BB0
// ------------------------------------------------------------
void /*thiscall*/ sub_420BB0(int *this, int nArg2)
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  uint32_t *fld_e22; // edi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 2;
  else
    fld_e2 = 0;
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) >> 2 )
  {
    fld_e22 = (uint32_t *)*(this + 2);
    sub_41FFE0(fld_e22, 1, nArg2);
    *(this + 2) = (int)(fld_e22 + 1);
  }
  else
  {
    sub_4206D0((int)this, *(this + 2), 1u, nArg2);
  }
}



// ------------------------------------------------------------
// 0x420C20 sub_420C20
// ------------------------------------------------------------
void /*thiscall*/ sub_420C20(int *this, int nArg2)
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
    sub_420960((int)this, *(this + 2), 1u, nArg2);
  }
}



// ------------------------------------------------------------
// 0x420C90 sub_420C90
// ------------------------------------------------------------
char /*thiscall*/ sub_420C90(int *this, HWND hWnd)
{
  struct tagWINDOWINFO pwi; // [esp+8h] [ebp-148h] BYREF
  HWND v5; // [esp+44h] [ebp-10Ch] BYREF
  int v6; // [esp+48h] [ebp-108h]
  CHAR String[256]; // [esp+4Ch] [ebp-104h] BYREF
  int dword_796E502; // [esp+14Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( GetWindowTextLengthA(hWnd) == 0 )
    return 0;
  if ( !IsWindowVisible(hWnd) )
    return 0;
  GetWindowInfo(hWnd, &pwi);
  if ( SLOBYTE(pwi.dwExStyle) < 0 )
    return 0;
  GetWindowTextA(hWnd, String, 255);
  OutputDebugStringA("*Minimize::");
  OutputDebugStringA(String);
  OutputDebugStringA("\n");
  v5 = hWnd;
  if ( IsZoomed(hWnd) )
    v6 = 3;
  else
    v6 = IsIconic(hWnd) ? 6 : 1;
  sub_420C20(this + 2, (int)&v5);
  ShowWindow(hWnd, 6);
  return 1;
}



// ------------------------------------------------------------
// 0x420D80 EnumFunc
// ------------------------------------------------------------
BOOL /*stdcall*/ EnumFunc(HWND hWnd, int *pDwArg2)
{
  sub_420C90(pDwArg2, hWnd);
  return true;
}



// ------------------------------------------------------------
// 0x420DA0 sub_420DA0
// ------------------------------------------------------------
// 【引擎主引导入口】DNF.trc 跟踪(sub_403990) → 'ConsoleDebug' 文件探测置 byte_79C7B0 →
//   'ModeWindow' 窗口模式 → 'Script/' 缺失弹串612("Run Error")并退出 → sub_420190
//   图形启动 → 'DebugConfig.txt' 校验（byte_77F280 = 调试机标志）弹串613 → sub_439AB0
//   全局数据总装 → 玩家名/服务器名装载（串614/615 兜底）→ dword_79C0A0+124 = this。
int /*thiscall*/ sub_420DA0(int this, int nArg2)
{
  int v4; // ecx
  const char *fld_110; // eax
  int fld_1102; // eax
  int fld_1103; // ecx
  const char *fld_1104; // eax
  int fld_1105; // eax
  HWND v10; // ebx
  const CHAR *v11; // eax
  HWND v12; // esi
  const CHAR *v13; // eax
  int fld_1106; // eax
  uint8_t v15[4]; // [esp+4h] [ebp-18h] BYREF
  int v16; // [esp+8h] [ebp-14h]
  void *v17; // [esp+Ch] [ebp-10h] BYREF
  int v18; // [esp+18h] [ebp-4h]
  bool v19; // [esp+27h] [ebp+Bh]

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  sub_403920();
  nullsub_3(v4);
  sub_403990("DNF.trc", 2, 1, 0);
  byte_79C7B0 = _access("ConsoleDebug", 0) == 0;
  byte_79C7B8 = 0;
  dword_79C7B4 = 0;
  sub_48BB30((LPCVOID)0xA000);
  byte_77F280 = 0;
  *(uint8_t *)(this + 60) = 0;
  *(uint8_t *)(this + 92) = 0;
  dword_8F7A24 = this;
  *(uint8_t *)(this + 112) = 1;
  if ( _access("ModeWindow", 0) == 0 )
    *(uint8_t *)(this + 112) = 0;
  dword_79C0A0 = nArg2;
  sub_4017E0(this + 268);
  sub_488690(this + 268, *(uint32_t *)(dword_79C0A0 + 100), "?", 0);
  fld_110 = (const char *)sub_41ACF0(*(uint32_t *)(this + 272) + 20);
  *(uint8_t *)(this + 112) = j__atol(fld_110) != 1;
  fld_1102 = *(uint32_t *)(this + 272);
  if ( fld_1102 == 0 || (unsigned int)((*(uint32_t *)(this + 276) - fld_1102) >> 2) < 5 )
  {
    byte_77F280 = 1;
    while ( 1 )
    {
      fld_1103 = *(uint32_t *)(this + 272);
      if ( fld_1103 != 0 && (unsigned int)((*(uint32_t *)(this + 276) - fld_1103) >> 2) >= 5 )
        break;
      v17 = nullptr;
      sub_41BFE0(&v17, szPassword);
      v18 = 0;
      sub_420BB0(&v17);
      v18 = -1;
      sub_41B010(&v17);
    }
  }
  fld_1104 = (const char *)sub_41ACF0(*(uint32_t *)(this + 272));
  v19 = j__atol(fld_1104) < 10;
  fld_1105 = *(uint32_t *)(*(uint32_t *)(this + 272) + 16);
  if ( fld_1105 == 0 || *(uint32_t *)(fld_1105 + 4) == 0 )
    byte_77F280 = 1;
  if ( (uint8_t)sub_4422C0("Script/") == 0 )
  {
    ShowCursor(true);
    v10 = *(HWND *)(dword_79C0A0 + 16);
    v11 = (const CHAR *)sub_422E70(612);
    MessageBoxA(v10, v11, "Run Error", 0);
    PostQuitMessage(0);
  }
  if ( sub_420190(0, this) < 0 )
    return 0;
  dword_9D3BC8 = dword_79C0B0;
  byte_790700 = 0;
  byte_790701 = 0;
  byte_790702 = 0;
  byte_790703 = 0;
  dword_79070C = 0;
  dword_790710 = 6;
  dword_790714 = 12;
  dword_790718 = 0;
  dword_79071C = 1600;
  dword_790720 = 0;
  dword_790724 = 0;
  dword_790728 = 0;
  dword_79072C = 0;
  dword_790730 = dword_99FCCC;
  if ( byte_77F280 != 0 && _access("DebugConfig.txt", 0) != 0 )
  {
    ShowCursor(true);
    v12 = *(HWND *)(dword_79C0A0 + 16);
    v13 = (const CHAR *)sub_422E70(613);
    MessageBoxA(v12, v13, "Run Error", 0);
    PostQuitMessage(0);
    return 0x80000000;
  }
  else
  {
    sub_41F2C0(this);
    sub_419EE0(v15);
    v16 = sub_418DD0(91);
    sub_419EB0(v15);
    sub_41FC50();
    sub_439AB0();
    sub_41FAA0(this);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 124))(
      dword_8F8520,
      *(uint32_t *)(*(uint32_t *)(this + 20) + 44));
    *(uint32_t *)(dword_79C0A0 + 124) = this;
    fld_1106 = *(uint32_t *)(this + 272);
    if ( fld_1106 != 0 && (unsigned int)((*(uint32_t *)(this + 276) - fld_1106) >> 2) >= 4 )
    {
      strcpy((char *)(this + 113), (const char *)sub_41ACF0(*(uint32_t *)(this + 272) + 12));
      strcpy((char *)(this + 177), (const char *)sub_41ACF0(*(uint32_t *)(this + 272) + 16));
      off_77F3FC((char *)&byte_6C36B8, this + 113);
      sub_48BA30(this + 113);
    }
    else
    {
      strcpy((char *)(this + 113), (const char *)sub_422E70(614));
      strcpy((char *)(this + 177), (const char *)sub_422E70(615));
    }
    if ( v19 )
    {
      if ( byte_77F280 != 0 )
        sub_41D300(0);
      else
        sub_41D300(5);
    }
    else
    {
      sub_41D300(0);
      if ( byte_77F280 == 0 )
        sub_41E4F0(this + 268);
    }
    sub_488670(dword_79C0B0);
    if ( byte_77F280 != 0 )
    {
      sub_489800((uint32_t *)this);
      dword_978998 = 0;
    }
    *(uint8_t *)(this + 4) = 1;
    return 1;
  }
}


// ============================================================
// §3 字符串表容器与排序/查找辅助（0x421220-0x422BD0）
//   std::vector/sort/lower_bound 同族的展开形态；为 §4 字符串表供底层
// ============================================================
// ------------------------------------------------------------
// 0x421220 sub_421220
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_421220(uint32_t *lParam, int nArg2)
{
  HWND WindowA; // eax

  *lParam = &vftbl_nmodule__nMinimizeWindows;
  *(lParam + 1) = nArg2;
  *(lParam + 3) = 0;
  *(lParam + 4) = 0;
  *(lParam + 5) = 0;
  if ( *(lParam + 1) != 0 )
  {
    if ( *(lParam + 1) == 1 )
    {
      WindowA = FindWindowA("Shell_TrayWnd", nullptr);
      if ( WindowA != nullptr )
      {
        SendMessageA(WindowA, 0x111u, 0x19Fu, 0);
        return lParam;
      }
    }
    else if ( *(lParam + 1) == 2 )
    {
      sub_41FCF0();
      return lParam;
    }
  }
  else
  {
    EnumWindows((WNDENUMPROC)EnumFunc, (LPARAM)lParam);
  }
  return lParam;
}



// ------------------------------------------------------------
// 0x4212E0 sub_4212E0
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_4212E0(uint32_t *uArg1, uint32_t *uArg2)
{
  return *uArg1 < *uArg2;
}



// ------------------------------------------------------------
// 0x421300 sub_421300
// ------------------------------------------------------------
int /*cdecl*/ sub_421300(char *FileName)
{
  HMODULE AllocationBase; // ebx
  HRSRC ResourceA; // eax
  HRSRC v3; // esi
  HGLOBAL Resource; // edi
  size_t v6; // ebx
  FILE *pFile; // esi
  struct _MEMORY_BASIC_INFORMATION Buffer; // [esp+14h] [ebp-20h] BYREF
  LPCVOID lpAddress; // [esp+30h] [ebp-4h]

  lpAddress = &loc_421311;
  VirtualQuery(&loc_421311, &Buffer, 0x1Cu);
  AllocationBase = (HMODULE)Buffer.AllocationBase;
  ResourceA = FindResourceA((HMODULE)Buffer.AllocationBase, (LPCSTR)0x73, "File");
  v3 = ResourceA;
  if ( ResourceA == nullptr )
    return -1;
  Resource = LoadResource(AllocationBase, ResourceA);
  if ( Resource == nullptr )
    return -2;
  v6 = SizeofResource(AllocationBase, v3);
  pFile = fopen(FileName, "wb");
  sub_66BC25(Resource, v6, 1u, pFile);
  fclose(pFile);
  return 1;
}



// ------------------------------------------------------------
// 0x4213A0 sub_4213A0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4213A0(uint32_t *uArg1, int nArg2, int nArg3, int nArg4, uint8_t (/*cdecl*/ *uArg5)(int, int))
{
  int nArg22; // ecx
  int v6; // ebx
  int v7; // esi

  nArg22 = nArg2;
  v6 = (nArg3 - nArg2) >> 5;
  if ( v6 <= 0 )
  {
    *uArg1 = nArg2;
    return uArg1;
  }
  else
  {
    while ( 1 )
    {
      v7 = nArg22 + 32 * (v6 / 2);
      if ( uArg5(v7, nArg4) != 0 )
      {
        nArg2 = v7 + 32;
        v6 += -1 - v6 / 2;
      }
      else
      {
        v6 /= 2;
      }
      if ( v6 <= 0 )
        break;
      nArg22 = nArg2;
    }
    *uArg1 = nArg2;
    return uArg1;
  }
}



// ------------------------------------------------------------
// 0x421410 sub_421410
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_421410(uint32_t *uArg1, int nArg2, int nArg3, int nArg4, uint8_t (/*cdecl*/ *uArg5)(int, int))
{
  int nArg22; // ecx
  int v6; // ebx
  int v7; // esi

  nArg22 = nArg2;
  v6 = (nArg3 - nArg2) >> 5;
  if ( v6 <= 0 )
  {
    *uArg1 = nArg2;
    return uArg1;
  }
  else
  {
    while ( 1 )
    {
      v7 = nArg22 + 32 * (v6 / 2);
      if ( uArg5(nArg4, v7) != 0 )
      {
        v6 /= 2;
      }
      else
      {
        nArg2 = v7 + 32;
        v6 += -1 - v6 / 2;
      }
      if ( v6 <= 0 )
        break;
      nArg22 = nArg2;
    }
    *uArg1 = nArg2;
    return uArg1;
  }
}



// ------------------------------------------------------------
// 0x421480 sub_421480
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_421480(uint32_t *this, size_t Size, size_t uArg3, uint32_t *pArg4, unsigned int uArg5, size_t uArg6)
{
  uint32_t *pThis; // esi
  unsigned int uArg33; // edi
  size_t fld_e5; // ebx
  size_t uArg62; // edx
  size_t uArg32; // edx
  unsigned int fld_e52; // ebx
  unsigned int fld_e6; // eax
  uint8_t *pThis_1; // eax
  int *v14; // ebx
  unsigned int v15; // eax
  int v16; // ecx
  int v17; // eax
  uint32_t *v18; // edx
  int v19; // eax
  unsigned int v20; // eax
  int v21; // ecx
  int v22; // eax
  unsigned int v23; // eax
  int v24; // ecx
  int v25; // eax
  unsigned int v26; // eax
  int v27; // ecx
  int v28; // eax
  unsigned int v29; // eax
  int v30; // ecx
  unsigned int v31; // eax
  int v32; // ecx
  int v33; // eax
  unsigned int v34; // ecx
  int v35; // eax
  unsigned int v36; // edx
  const void *v37; // eax
  int v38; // ecx
  uint32_t *v39; // eax
  unsigned int v40; // eax
  uint32_t *v41; // ecx
  uint32_t *v42; // eax
  unsigned int v43; // eax
  bool v44; // cf
  const void *v46; // [esp-8h] [ebp-1Ch]
  size_t uArg63; // [esp-4h] [ebp-18h]
  unsigned int fld_e522; // [esp+Ch] [ebp-8h]
  size_t Sizea; // [esp+1Ch] [ebp+8h]
  size_t Sizeb; // [esp+1Ch] [ebp+8h]
  int v52; // [esp+24h] [ebp+10h]

  pThis = this;
  uArg33 = Size;
  if ( *(this + 5) < Size || pArg4[5] < uArg5 )
    std::_String_base::_Xran((std::_String_base *)this);
  fld_e5 = uArg3;
  if ( *(this + 5) - Size < uArg3 )
  {
    fld_e5 = *(this + 5) - Size;
    uArg3 = fld_e5;
  }
  uArg62 = uArg6;
  if ( pArg4[5] - uArg5 < uArg6 )
  {
    uArg62 = pArg4[5] - uArg5;
    uArg6 = uArg62;
  }
  if ( -1 - uArg62 <= *(this + 5) - fld_e5 )
    std::_String_base::_Xlen((std::_String_base *)this);
  uArg32 = uArg3;
  Sizea = *(this + 5) - Size - uArg3;
  fld_e52 = uArg6 + *(this + 5) - uArg3;
  fld_e522 = fld_e52;
  if ( *(this + 5) < fld_e52 )
  {
    if ( fld_e52 == -1 )
      std::_String_base::_Xlen((std::_String_base *)this);
    fld_e6 = *(this + 6);
    if ( fld_e6 >= fld_e52 )
    {
      if ( fld_e52 == 0 )
      {
        *(this + 5) = 0;
        if ( fld_e6 < 0x10 )
          pThis_1 = this + 1;
        else
          pThis_1 = (uint8_t *)*(this + 1);
        *pThis_1 = 0;
      }
    }
    else
    {
      sub_4012B0(this, fld_e52, *(this + 5));
      uArg32 = uArg3;
    }
  }
  v14 = pThis + 1;
  if ( pThis == pArg4 )
  {
    if ( uArg6 > uArg32 )
    {
      if ( uArg5 > uArg33 )
      {
        v31 = pThis[6];
        if ( uArg33 + uArg32 > uArg5 )
        {
          if ( v31 < 0x10 )
            v38 = (int)(pThis + 1);
          else
            v38 = *v14;
          if ( v31 < 0x10 )
            v39 = pThis + 1;
          else
            v39 = (uint32_t *)*v14;
          memcpy_0((char *)v39 + uArg33, (const void *)(uArg5 + v38), uArg3);
          v40 = pThis[6];
          if ( v40 < 0x10 )
            v41 = pThis + 1;
          else
            v41 = (uint32_t *)*v14;
          if ( v40 < 0x10 )
            v42 = pThis + 1;
          else
            v42 = (uint32_t *)*v14;
          memcpy_0((char *)v42 + uArg33 + uArg6, (char *)v41 + uArg33 + uArg3, Sizea);
          v43 = pThis[6];
          if ( v43 < 0x10 )
            v52 = (int)(pThis + 1);
          else
            v52 = *v14;
          if ( v43 < 0x10 )
            Sizeb = (size_t)(pThis + 1);
          else
            Sizeb = *v14;
          uArg63 = uArg6 - uArg3;
          v36 = uArg33 + Sizeb;
          uArg33 = uArg3;
          v46 = (const void *)(uArg6 + uArg5 + v52);
        }
        else
        {
          if ( v31 < 0x10 )
            v32 = (int)(pThis + 1);
          else
            v32 = *v14;
          if ( v31 < 0x10 )
            v33 = (int)(pThis + 1);
          else
            v33 = *v14;
          memcpy_0((void *)(uArg6 + uArg33 + v33), (const void *)(uArg3 + uArg33 + v32), Sizea);
          v34 = pThis[6];
          if ( v34 < 0x10 )
            v35 = (int)(pThis + 1);
          else
            v35 = *v14;
          if ( v34 < 0x10 )
          {
            uArg63 = uArg6;
            v37 = (const void *)(uArg6 + uArg5 + v35 - uArg3);
            v36 = (unsigned int)(pThis + 1);
          }
          else
          {
            v36 = *v14;
            uArg63 = uArg6;
            v37 = (const void *)(uArg6 + uArg5 + v35 - uArg3);
          }
          v46 = v37;
        }
        memcpy_0((void *)(uArg33 + v36), v46, uArg63);
      }
      else
      {
        v26 = pThis[6];
        if ( v26 < 0x10 )
          v27 = (int)(pThis + 1);
        else
          v27 = *v14;
        if ( v26 < 0x10 )
          v28 = (int)(pThis + 1);
        else
          v28 = *v14;
        memcpy_0((void *)(uArg6 + uArg33 + v28), (const void *)(uArg3 + uArg33 + v27), Sizea);
        v29 = pThis[6];
        if ( v29 < 0x10 )
          v30 = (int)(pThis + 1);
        else
          v30 = *v14;
        if ( v29 < 0x10 )
          memcpy_0((char *)v14 + uArg33, (const void *)(uArg5 + v30), uArg6);
        else
          memcpy_0((void *)(uArg33 + *v14), (const void *)(uArg5 + v30), uArg6);
      }
    }
    else
    {
      v20 = pThis[6];
      if ( v20 < 0x10 )
        v21 = (int)(pThis + 1);
      else
        v21 = *v14;
      if ( v20 < 0x10 )
        v22 = (int)(pThis + 1);
      else
        v22 = *v14;
      memcpy_0((void *)(uArg33 + v22), (const void *)(uArg5 + v21), uArg6);
      v23 = pThis[6];
      if ( v23 < 0x10 )
        v24 = (int)(pThis + 1);
      else
        v24 = *v14;
      if ( v23 < 0x10 )
        v25 = (int)(pThis + 1);
      else
        v25 = *v14;
      memcpy_0((void *)(uArg6 + uArg33 + v25), (const void *)(uArg3 + uArg33 + v24), Sizea);
    }
  }
  else
  {
    v15 = pThis[6];
    if ( v15 < 0x10 )
      v16 = (int)(pThis + 1);
    else
      v16 = *v14;
    if ( v15 < 0x10 )
      v17 = (int)(pThis + 1);
    else
      v17 = *v14;
    memcpy_0((void *)(uArg6 + uArg33 + v17), (const void *)(uArg3 + uArg33 + v16), Sizea);
    if ( pArg4[6] < 0x10u )
      v18 = pArg4 + 1;
    else
      v18 = (uint32_t *)pArg4[1];
    if ( pThis[6] < 0x10u )
      v19 = (int)(pThis + 1);
    else
      v19 = *v14;
    qmemcpy((void *)(v19 + uArg33), (char *)v18 + uArg5, uArg6);
    pThis = this;
  }
  v44 = pThis[6] < 0x10u;
  pThis[5] = fld_e522;
  if ( !v44 )
    v14 = (int *)*v14;
  *((uint8_t *)v14 + fld_e522) = 0;
  return pThis;
}


// ------------------------------------------------------------
// 0x4217E0 sub_4217E0
// ------------------------------------------------------------
int */*cdecl*/ sub_4217E0(int *pDwArg1, int nArg2, int nArg3, int nArg4, uint8_t (/*cdecl*/ *uArg5)(int, int))
{
  int nArg22; // ecx
  int v6; // edi
  int v7; // esi
  int nArg23; // ebx
  int nArg24; // ecx

  nArg22 = nArg2;
  v6 = (nArg3 - nArg2) >> 5;
  if ( v6 <= 0 )
  {
LABEL_7:
    pDwArg1[1] = nArg22;
    *pDwArg1 = nArg22;
    return pDwArg1;
  }
  while ( 1 )
  {
    v7 = nArg22 + 32 * (v6 / 2);
    if ( uArg5(v7, nArg4) == 0 )
      break;
    nArg2 = v7 + 32;
    v6 += -1 - v6 / 2;
LABEL_6:
    nArg22 = nArg2;
    if ( v6 <= 0 )
      goto LABEL_7;
  }
  if ( uArg5(nArg4, v7) != 0 )
  {
    v6 /= 2;
    goto LABEL_6;
  }
  nArg23 = nArg2;
  sub_4213A0(&nArg2, nArg2, v7, nArg4, uArg5);
  sub_421410(&nArg3, v7 + 32, nArg23 + 32 * v6, nArg4, uArg5);
  nArg24 = nArg2;
  pDwArg1[1] = nArg3;
  *pDwArg1 = nArg24;
  return pDwArg1;
}



// ------------------------------------------------------------
// 0x4218A0 sub_4218A0
// ------------------------------------------------------------
unsigned int */*thiscall*/ sub_4218A0(unsigned int *this, size_t uArg2, size_t Size, uint8_t *uArg4, size_t uArg5)
{
  unsigned int fld_e6; // esi
  unsigned int pThis_1; // eax
  uint32_t *pThis_12; // eax
  int pThis_13; // ecx
  size_t fld_e5; // edi
  size_t uArg52; // ecx
  size_t fld_e52; // edx
  uint32_t *pThis_14; // eax
  unsigned int fld_e53; // esi
  unsigned int fld_e62; // eax
  bool v17; // zf
  unsigned int fld_e63; // ecx
  uint32_t *pThis_16; // eax
  uint32_t *pThis_17; // esi
  uint32_t *pThis_18; // eax
  bool fld_e64; // cf
  uint32_t *pThis_15; // [esp+Ch] [ebp-4h]
  unsigned int fld_e532; // [esp+Ch] [ebp-4h]
  size_t Sizea; // [esp+1Ch] [ebp+Ch]

  fld_e6 = *(this + 6);
  if ( fld_e6 < 0x10 )
    pThis_1 = (unsigned int)(this + 1);
  else
    pThis_1 = *(this + 1);
  if ( (unsigned int)uArg4 >= pThis_1 )
  {
    pThis_12 = this + 1;
    pThis_13 = fld_e6 < 0x10 ? (int)(this + 1) : *pThis_12;
    if ( pThis_13 + *(this + 5) > (unsigned int)uArg4 )
    {
      if ( fld_e6 >= 0x10 )
        pThis_12 = (uint32_t *)*pThis_12;
      return (unsigned int *)sub_421480(uArg2, Size, (int)this, uArg4 - (uint8_t *)pThis_12, uArg5);
    }
  }
  if ( *(this + 5) < uArg2 )
    std::_String_base::_Xran((std::_String_base *)this);
  fld_e5 = Size;
  if ( *(this + 5) - uArg2 < Size )
    fld_e5 = *(this + 5) - uArg2;
  uArg52 = uArg5;
  if ( -1 - uArg5 <= *(this + 5) - fld_e5 )
    std::_String_base::_Xlen((std::_String_base *)this);
  fld_e52 = *(this + 5) - uArg2 - fld_e5;
  Sizea = fld_e52;
  if ( uArg5 < fld_e5 )
  {
    pThis_14 = this + 1;
    if ( *(this + 6) < 0x10 )
      pThis_15 = this + 1;
    else
      pThis_15 = (uint32_t *)*pThis_14;
    if ( *(this + 6) >= 0x10 )
      pThis_14 = (uint32_t *)*pThis_14;
    memcpy_0((char *)pThis_14 + uArg2 + uArg5, (char *)pThis_15 + uArg2 + fld_e5, fld_e52);
    fld_e52 = Sizea;
    uArg52 = uArg5;
  }
  if ( uArg52 == 0 && fld_e5 == 0 )
    return this;
  fld_e53 = *(this + 5) + uArg52 - fld_e5;
  fld_e532 = fld_e53;
  if ( fld_e53 == -1 )
    std::_String_base::_Xlen((std::_String_base *)this);
  fld_e62 = *(this + 6);
  if ( fld_e62 < fld_e53 )
  {
    sub_4012B0(this, fld_e53, *(this + 5));
    fld_e52 = Sizea;
    v17 = fld_e53 == 0;
    goto LABEL_31;
  }
  v17 = fld_e53 == 0;
  if ( fld_e53 != 0 )
  {
LABEL_31:
    if ( !v17 )
    {
      if ( fld_e5 < uArg5 )
      {
        fld_e63 = *(this + 6);
        pThis_16 = this + 1;
        if ( fld_e63 < 0x10 )
          pThis_17 = this + 1;
        else
          pThis_17 = (uint32_t *)*pThis_16;
        if ( fld_e63 >= 0x10 )
          pThis_16 = (uint32_t *)*pThis_16;
        memcpy_0((char *)pThis_16 + uArg2 + uArg5, (char *)pThis_17 + uArg2 + fld_e5, fld_e52);
      }
      if ( *(this + 6) < 0x10 )
        pThis_18 = this + 1;
      else
        pThis_18 = (uint32_t *)*(this + 1);
      qmemcpy((char *)pThis_18 + uArg2, uArg4, uArg5);
      fld_e64 = *(this + 6) < 0x10;
      *(this + 5) = fld_e532;
      if ( !fld_e64 )
      {
        *(uint8_t *)(*(this + 1) + fld_e532) = 0;
        return this;
      }
      *((uint8_t *)this + fld_e532 + 4) = 0;
    }
    return this;
  }
  *(this + 5) = 0;
  if ( fld_e62 < 0x10 )
    *((uint8_t *)this + 4) = 0;
  else
    *(uint8_t *)*(this + 1) = 0;
  return this;
}


// ------------------------------------------------------------
// 0x421A80 sub_421A80
// ------------------------------------------------------------
void /*noreturn*/ sub_421A80()
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
// 0x421AF0 sub_421AF0
// ------------------------------------------------------------
int /*thiscall*/ sub_421AF0(uint32_t *this, uint32_t *pArg2)
{
  int fld_e5; // eax
  int v3; // edx
  int result; // eax
  int fld_e1; // [esp+Ch] [ebp-14h]
  int fld_e2; // [esp+10h] [ebp-10h]
  int fld_e3; // [esp+14h] [ebp-Ch]
  int fld_e4; // [esp+18h] [ebp-8h]

  fld_e1 = *(this + 1);
  fld_e2 = *(this + 2);
  fld_e3 = *(this + 3);
  fld_e4 = *(this + 4);
  *(this + 1) = pArg2[1];
  *(this + 2) = pArg2[2];
  *(this + 3) = pArg2[3];
  *(this + 4) = pArg2[4];
  pArg2[1] = fld_e1;
  pArg2[2] = fld_e2;
  pArg2[3] = fld_e3;
  pArg2[4] = fld_e4;
  fld_e5 = *(this + 5);
  *(this + 5) = pArg2[5];
  v3 = pArg2[6];
  pArg2[5] = fld_e5;
  result = *(this + 6);
  *(this + 6) = v3;
  pArg2[6] = result;
  return result;
}



// ------------------------------------------------------------
// 0x421B80 sub_421B80
// ------------------------------------------------------------
char /*thiscall*/ sub_421B80(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x7FFFFFF )
    sub_421A80(this);
  pMem = (char *)operator new(32 * uArg2);
  *(this + 3) = &pMem[32 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x421BD0 sub_421BD0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_421BD0(int nArg1, int nArg2, uint32_t *uArg3)
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
    v5 = *(uint32_t *)(nArg22 - 32);
    nArg22 -= 32;
    uArg32 -= 8;
    *uArg32 = v5;
    sub_4014D0((std::_String_base *)(uArg32 + 1), nArg22 + 4, 0, -1);
  }
  while ( nArg22 != nArg1 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x421C10 sub_421C10
// ------------------------------------------------------------
int /*cdecl*/ sub_421C10(uint32_t *uArg1, uint32_t *uArg2, int nArg3)
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
// 0x421CE0 sub_421CE0
// ------------------------------------------------------------
void /*cdecl*/ sub_421CE0(
        int a1,
        int a2,
        int a3,
        int a4,
        char a5,
        void *Block,
        int a7,
        int a8,
        int a9,
        int a10,
        unsigned int a11,
        uint8_t (/*cdecl*/ *a12)(uint32_t *, int *))
{
  int v12; // esi
  int i; // edi
  uint32_t *v14; // ebx
  uint32_t *v15; // eax
  uint32_t *v16; // esi

  v12 = a2;
  for ( i = (a2 - 1) / 2; a3 < v12; i = (i - 1) / 2 )
  {
    v14 = (uint32_t *)(32 * i + a1);
    if ( a12(v14, &a4) == 0 )
      break;
    v15 = (uint32_t *)(a1 + 32 * v12);
    *v15 = *v14;
    sub_4014D0((std::_String_base *)(v15 + 1), v14 + 1, 0, -1);
    v12 = i;
  }
  v16 = (uint32_t *)(a1 + 32 * v12);
  *v16 = a4;
  sub_4014D0((std::_String_base *)(v16 + 1), &a5, 0, -1);
  if ( a11 >= 0x10 )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x421DA0 sub_421DA0
// ------------------------------------------------------------
int /*cdecl*/ sub_421DA0(int pArg1, int nArg2, char *pszArg3)
{
  int v3; // ecx
  int result; // eax
  int v5; // ebx
  int v6; // edx
  int nArg22; // ecx
  char *v8; // ebx
  int v9; // edx
  char *v10; // esi
  char *v11; // edi
  char **v12; // eax
  char *v13; // esi
  int v14; // eax
  char **v15; // eax
  bool v16; // zf
  char *v17; // [esp+Ch] [ebp-48h] BYREF
  int v18; // [esp+10h] [ebp-44h]
  int v19; // [esp+14h] [ebp-40h] BYREF
  char *v20; // [esp+18h] [ebp-3Ch] BYREF
  int v21; // [esp+1Ch] [ebp-38h]
  int v22; // [esp+20h] [ebp-34h]
  int v23; // [esp+24h] [ebp-30h]
  char v24[4]; // [esp+28h] [ebp-2Ch] BYREF
  void *Block; // [esp+2Ch] [ebp-28h]
  int v26; // [esp+3Ch] [ebp-18h]
  unsigned int v27; // [esp+40h] [ebp-14h]
  int dword_796E502; // [esp+44h] [ebp-10h]
  int v29; // [esp+50h] [ebp-4h]

  v3 = (nArg2 - pArg1) >> 5;
  dword_796E502 = dword_796E50;
  v21 = v3;
  result = (int)&pszArg3[-pArg1] >> 5;
  v5 = v3;
  if ( v3 != 0 )
  {
    do
    {
      v6 = result % v5;
      result = v5;
      v5 = v6;
    }
    while ( v6 != 0 );
  }
  if ( result < (int)&pszArg3[-pArg1] >> 5 && result > 0 )
  {
    nArg22 = 32 * v3;
    v8 = (char *)(pArg1 + 32 * result);
    v9 = 4 - nArg22;
    nArg2 = nArg22;
    v18 = 4 - nArg22;
    v22 = result;
    while ( 1 )
    {
      v10 = &v8[nArg22];
      v11 = v8;
      v23 = *(uint32_t *)v8;
      v27 = 15;
      v26 = 0;
      LOBYTE(Block) = 0;
      sub_4014D0((std::_String_base *)v24, &v8[nArg22 + v9], 0, -1);
      v29 = 0;
      if ( v10 == pszArg3 )
      {
        v12 = (char **)&pArg1;
      }
      else
      {
        v17 = v10;
        v12 = &v17;
      }
      v13 = *v12;
      if ( *v12 != v8 )
      {
        do
        {
          *(uint32_t *)v11 = *(uint32_t *)v13;
          sub_4014D0((std::_String_base *)(v11 + 4), v13 + 4, 0, -1);
          v14 = (pszArg3 - v13) >> 5;
          v11 = v13;
          if ( v21 >= v14 )
          {
            v19 = pArg1 + 32 * (v21 - v14);
            v15 = (char **)&v19;
          }
          else
          {
            v20 = &v13[nArg2];
            v15 = &v20;
          }
          v13 = *v15;
        }
        while ( *v15 != v8 );
      }
      *(uint32_t *)v11 = v23;
      sub_4014D0((std::_String_base *)(v11 + 4), v24, 0, -1);
      v29 = -1;
      if ( v27 >= 0x10 )
        j__free(Block);
      v8 -= 32;
      result = v22 - 1;
      v16 = v22 == 1;
      v27 = 15;
      v26 = 0;
      LOBYTE(Block) = 0;
      --v22;
      if ( v16 )
        break;
      nArg22 = nArg2;
      v9 = v18;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x421F30 sub_421F30
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_421F30(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 8 )
  {
    *i = *uArg3;
    sub_4014D0((std::_String_base *)(i + 1), uArg3 + 1, 0, -1);
    result = uArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x421F70 sub_421F70
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_421F70(int nArg1, int nArg2, uint32_t *uArg3)
{
  return sub_421BD0(nArg1, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x421F90 sub_421F90
// ------------------------------------------------------------
int /*cdecl*/ sub_421F90(int nArg1, int nArg2, uint32_t *uArg3)
{
  int nArg12; // esi
  int result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  nArg12 = nArg1;
  v5[5] = v5;
  v5[4] = nArg1;
  v6 = 0;
  while ( nArg2 != 0 )
  {
    v5[3] = nArg12;
    LOBYTE(v6) = 1;
    if ( nArg12 != 0 )
    {
      *(uint32_t *)nArg12 = *uArg3;
      *(uint32_t *)(nArg12 + 28) = 15;
      *(uint32_t *)(nArg12 + 24) = 0;
      *(uint8_t *)(nArg12 + 8) = 0;
      result = sub_4014D0((std::_String_base *)(nArg12 + 4), uArg3 + 1, 0, -1);
    }
    nArg12 += 32;
    LOBYTE(v6) = 0;
    --nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x422060 sub_422060
// ------------------------------------------------------------
void /*cdecl*/ sub_422060(
        int a1,
        int a2,
        int a3,
        int a4,
        char a5,
        void *Block,
        int a7,
        int a8,
        int a9,
        int a10,
        unsigned int a11,
        uint8_t (/*cdecl*/ *a12)(int, int))
{
  int v12; // edi
  int v13; // eax
  int v14; // esi
  bool v15; // zf
  int v16; // edx
  uint32_t *v17; // ecx
  int v18; // eax
  int v19; // ecx
  uint32_t *v20; // edi
  char v21; // [esp-20h] [ebp-38h] BYREF
  void *v22; // [esp-1Ch] [ebp-34h]
  int v23; // [esp-18h] [ebp-30h]
  int v24; // [esp-14h] [ebp-2Ch]
  int v25; // [esp-10h] [ebp-28h]
  int v26; // [esp-Ch] [ebp-24h]
  unsigned int v27; // [esp-8h] [ebp-20h]
  int v28; // [esp-4h] [ebp-1Ch]
  int v29; // [esp+14h] [ebp-4h]

  v12 = a2;
  v13 = a3;
  v14 = 2 * a2 + 2;
  v15 = v14 == a3;
  v29 = 0;
  if ( v14 < a3 )
  {
    do
    {
      if ( a12(a1 + 32 * v14, a1 + 32 * v14 - 32) != 0 )
        --v14;
      v16 = *(uint32_t *)(32 * v14 + a1);
      v28 = -1;
      v17 = (uint32_t *)(a1 + 32 * v12);
      v27 = 0;
      *v17 = v16;
      sub_4014D0((std::_String_base *)(v17 + 1), a1 + 32 * v14 + 4, v27, v28);
      v13 = a3;
      v12 = v14;
      v14 = 2 * v14 + 2;
    }
    while ( v14 < a3 );
    v15 = v14 == a3;
  }
  if ( v15 )
  {
    v18 = 32 * v13;
    v19 = *(uint32_t *)(v18 + a1 - 32);
    v28 = -1;
    v20 = (uint32_t *)(a1 + 32 * v12);
    v27 = 0;
    *v20 = v19;
    sub_4014D0((std::_String_base *)(v20 + 1), v18 + a1 - 32 + 4, v27, v28);
    v12 = a3 - 1;
  }
  v28 = (int)a12;
  v27 = 15;
  v26 = 0;
  LOBYTE(v22) = 0;
  sub_4014D0((std::_String_base *)&v21, &a5, 0, -1);
  sub_421CE0(a1, v12, a2, a4, v21, v22, v23, v24, v25, v26, v27, (uint8_t (/*cdecl*/ *)(uint32_t *, int *))v28);
  if ( a11 >= 0x10 )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x422170 sub_422170
// ------------------------------------------------------------
void /*cdecl*/ sub_422170(
        int *a1,
        int a2,
        uint32_t *a3,
        int a4,
        char a5,
        void *Block,
        int a7,
        int a8,
        int a9,
        int a10,
        unsigned int a11,
        uint8_t (/*cdecl*/ *a12)(int, int))
{
  int v12; // ecx
  char v13; // [esp-20h] [ebp-30h] BYREF
  void *v14; // [esp-1Ch] [ebp-2Ch]
  int v15; // [esp-18h] [ebp-28h]
  int v16; // [esp-14h] [ebp-24h]
  int v17; // [esp-10h] [ebp-20h]
  int v18; // [esp-Ch] [ebp-1Ch]
  unsigned int v19; // [esp-8h] [ebp-18h]
  int v20; // [esp-4h] [ebp-14h]
  int v21; // [esp+Ch] [ebp-4h]

  v12 = *a1;
  v20 = -1;
  v19 = 0;
  *a3 = v12;
  v21 = 0;
  sub_4014D0((std::_String_base *)(a3 + 1), a1 + 1, v19, v20);
  v20 = (int)a12;
  v19 = 15;
  v18 = 0;
  LOBYTE(v14) = 0;
  sub_4014D0((std::_String_base *)&v13, &a5, 0, -1);
  sub_422060(
    (int)a1,
    0,
    (a2 - (int)a1) >> 5,
    a4,
    v13,
    v14,
    v15,
    v16,
    v17,
    v18,
    v19,
    (uint8_t (/*cdecl*/ *)(int, int))v20);
  if ( a11 >= 0x10 )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x422220 sub_422220
// ------------------------------------------------------------
int /*stdcall*/ sub_422220(int nArg1, int nArg2)
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 32 )
    result = sub_442C50(i);
  return result;
}



// ------------------------------------------------------------
// 0x422250 sub_422250
// ------------------------------------------------------------
int /*stdcall*/ sub_422250(uint32_t *uArg1, uint32_t *uArg2, int nArg3)
{
  return sub_421C10(uArg1, uArg2, nArg3);
}



// ------------------------------------------------------------
// 0x422270 sub_422270
// ------------------------------------------------------------
void /*cdecl*/ sub_422270(int nArg1, int nArg2, uint8_t (/*cdecl*/ *uArg3)(int, int))
{
  int v3; // esi
  int v4; // edi
  int v5; // ecx
  int v6; // [esp-24h] [ebp-30h]
  char v7; // [esp-20h] [ebp-2Ch] BYREF
  void *v8; // [esp-1Ch] [ebp-28h]
  int v9; // [esp-18h] [ebp-24h]
  int v10; // [esp-14h] [ebp-20h]
  int v11; // [esp-10h] [ebp-1Ch]
  int v12; // [esp-Ch] [ebp-18h]
  unsigned int v13; // [esp-8h] [ebp-14h]
  uint8_t (/*cdecl*/ *uArg32)(int, int); // [esp-4h] [ebp-10h]

  v3 = ((nArg2 - nArg1) >> 5) / 2;
  if ( v3 > 0 )
  {
    v4 = nArg1 + 32 * v3;
    do
    {
      v5 = *(uint32_t *)(v4 - 32);
      uArg32 = uArg3;
      v4 -= 32;
      v6 = v5;
      v13 = 15;
      v12 = 0;
      --v3;
      LOBYTE(v8) = 0;
      sub_4014D0((std::_String_base *)&v7, v4 + 4, 0, -1);
      sub_422060(nArg1, v3, (nArg2 - nArg1) >> 5, v6, v7, v8, v9, v10, v11, v12, v13, uArg32);
    }
    while ( v3 > 0 );
  }
}



// ------------------------------------------------------------
// 0x4222F0 sub_4222F0
// ------------------------------------------------------------
void /*cdecl*/ sub_4222F0(int *pDwArg1, int nArg2, uint8_t (/*cdecl*/ *uArg3)(int, int))
{
  int v3; // ecx
  int v4; // [esp-28h] [ebp-2Ch]
  char v5; // [esp-24h] [ebp-28h] BYREF
  void *v6; // [esp-20h] [ebp-24h]
  int v7; // [esp-1Ch] [ebp-20h]
  int v8; // [esp-18h] [ebp-1Ch]
  int v9; // [esp-14h] [ebp-18h]
  int v10; // [esp-10h] [ebp-14h]
  unsigned int v11; // [esp-Ch] [ebp-10h]
  uint8_t (/*cdecl*/ *uArg32)(int, int); // [esp-8h] [ebp-Ch]
  int v13; // [esp-4h] [ebp-8h]

  v3 = *(uint32_t *)(nArg2 - 32);
  v13 = 0;
  uArg32 = uArg3;
  v4 = v3;
  v10 = 0;
  v11 = 15;
  LOBYTE(v6) = 0;
  sub_4014D0((std::_String_base *)&v5, nArg2 - 32 + 4, 0, -1);
  sub_422170(pDwArg1, nArg2 - 32, (uint32_t *)(nArg2 - 32), v4, v5, v6, v7, v8, v9, v10, v11, uArg32);
}



// ------------------------------------------------------------
// 0x422340 sub_422340
// ------------------------------------------------------------
int /*thiscall*/ sub_422340(int *this)
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);
  result = 0;
  if ( fld_e1 != 0 )
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 32 )
      sub_442C50(fld_e1);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x422380 sub_422380
// ------------------------------------------------------------
int /*stdcall*/ sub_422380(int nArg1, int nArg2, uint32_t *uArg3)
{
  sub_421F90(nArg1, nArg2, uArg3);
  return nArg1 + 32 * nArg2;
}



// ------------------------------------------------------------
// 0x4223B0 sub_4223B0
// ------------------------------------------------------------
void /*thiscall*/ sub_4223B0(int this, int pArg2, unsigned int uArg3, uint32_t *pArg4)
{
  int fld_4; // ecx
  unsigned int fld_C; // eax
  int fld_8; // edx
  int fld_82; // edx
  unsigned int v10; // eax
  int fld_87; // edx
  int fld_88; // eax
  char *pMem; // ebx
  int fld_43; // ecx
  int fld_810; // eax
  unsigned int v16; // edi
  char *fld_83; // eax
  int fld_86; // edi
  char *v19; // edi
  int v20; // eax
  int fld_42; // [esp-18h] [ebp-64h]
  void *Block2; // [esp-18h] [ebp-64h]
  int fld_89; // [esp-10h] [ebp-5Ch]
  int fld_85; // [esp-Ch] [ebp-58h]
  unsigned int fld_84; // [esp-8h] [ebp-54h]
  uint32_t v26[4]; // [esp+0h] [ebp-4Ch] BYREF
  void *Block; // [esp+10h] [ebp-3Ch]
  char *pMem2; // [esp+14h] [ebp-38h]
  int v29; // [esp+18h] [ebp-34h] BYREF
  size_t v30; // [esp+1Ch] [ebp-30h] BYREF
  void *v31; // [esp+20h] [ebp-2Ch]
  int v32; // [esp+30h] [ebp-1Ch]
  unsigned int v33; // [esp+34h] [ebp-18h]
  int dword_796E502; // [esp+38h] [ebp-14h]
  uint32_t *v35; // [esp+3Ch] [ebp-10h]
  int v36; // [esp+48h] [ebp-4h]
  int v37; // [esp+58h] [ebp+Ch]

  dword_796E502 = dword_796E50;
  v35 = v26;
  v29 = *pArg4;
  v26[3] = this;
  v33 = 15;
  v32 = 0;
  LOBYTE(v31) = 0;
  sub_4014D0(&v30, pArg4 + 1, 0, 0xFFFFFFFF);
  fld_4 = *(uint32_t *)(this + 4);
  v36 = 0;
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 5;
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 5;
    else
      fld_8 = 0;
    if ( 0x7FFFFFF - fld_8 < uArg3 )
      sub_421A80(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 5;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(char **)(this + 8);
      Block = fld_83;
      if ( (int)&fld_83[-pArg2] >> 5 >= uArg3 )
      {
        v19 = &fld_83[-32 * uArg3];
        v20 = sub_421C10(v19, fld_83, fld_83);
        Block2 = Block;
        *(uint32_t *)(this + 8) = v20;
        sub_421F70(pArg2, v19, Block2);
        sub_421F30(pArg2, pArg2 + 32 * uArg3, &v29);
      }
      else
      {
        sub_421C10(pArg2, fld_83, pArg2 + 32 * uArg3);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 5);
        fld_85 = *(uint32_t *)(this + 8);
        LOBYTE(v36) = 3;
        sub_422380(fld_85, fld_84, &v29);
        fld_86 = 32 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        v36 = 0;
        sub_421F30(pArg2, fld_86 - 32 * uArg3, &v29);
      }
    }
    else
    {
      if ( 0x7FFFFFF - (fld_C >> 1) >= fld_C )
        v10 = (fld_C >> 1) + fld_C;
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
      v37 = 32 * v10;
      pMem = (char *)operator new(32 * v10);
      fld_42 = *(uint32_t *)(this + 4);
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v36) = 1;
      pMem2 = (char *)sub_421C10(fld_42, pArg2, pMem);
      sub_421F90(pMem2, uArg3, &v29);
      fld_89 = *(uint32_t *)(this + 8);
      pMem2 += 32 * uArg3;
      sub_421C10(pArg2, fld_89, pMem2);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_810 = (*(uint32_t *)(this + 8) - fld_43) >> 5;
      else
        fld_810 = 0;
      v16 = fld_810 + uArg3;
      if ( fld_43 != 0 )
      {
        sub_422220(fld_43, *(uint32_t *)(this + 8));
        j__free(*(void **)(this + 4));
      }
      *(uint32_t *)(this + 12) = &pMem[v37];
      *(uint32_t *)(this + 8) = &pMem[32 * v16];
      *(uint32_t *)(this + 4) = pMem;
    }
  }
  if ( v33 >= 0x10 )
    j__free(v31);
}


// ------------------------------------------------------------
// 0x422670 sub_422670
// ------------------------------------------------------------
int /*cdecl*/ sub_422670(int pArg1, int nArg2, uint8_t (/*cdecl*/ *uArg3)(int, int))
{
  int result; // eax
  int pArg12; // ebx
  int i; // esi
  int v6; // edi
  int v7; // ebx

  result = nArg2;
  pArg12 = pArg1;
  if ( pArg1 != nArg2 )
  {
    for ( i = pArg1 + 32; i != nArg2; i += 32 )
    {
      if ( uArg3(i, pArg12) != 0 )
      {
        if ( pArg12 != i && i != i + 32 )
          sub_421DA0(pArg12, i, (char *)(i + 32));
      }
      else
      {
        v6 = i - 32;
        if ( uArg3(i, i - 32) != 0 )
        {
          do
          {
            v7 = v6;
            v6 -= 32;
          }
          while ( uArg3(i, v6) != 0 );
          if ( v7 != i )
            sub_421DA0(v7, i, (char *)(i + 32));
          pArg12 = pArg1;
        }
      }
      result = nArg2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x422700 sub_422700
// ------------------------------------------------------------
int /*cdecl*/ sub_422700(int *pDwArg1, int *pDwArg2, int *pDwArg3, uint8_t (/*cdecl*/ *uArg4)(int *, int *))
{
  int v4; // eax
  int v5; // eax
  int result; // eax
  int v7; // eax

  if ( uArg4(pDwArg2, pDwArg1) != 0 )
  {
    v4 = *pDwArg2;
    *pDwArg2 = *pDwArg1;
    *pDwArg1 = v4;
    sub_421AF0(pDwArg2 + 1, pDwArg1 + 1);
  }
  if ( uArg4(pDwArg3, pDwArg2) != 0 )
  {
    v5 = *pDwArg3;
    *pDwArg3 = *pDwArg2;
    *pDwArg2 = v5;
    sub_421AF0(pDwArg3 + 1, pDwArg2 + 1);
  }
  result = ((int (/*cdecl*/ *)(int *, int *))uArg4)(pDwArg2, pDwArg1);
  if ( (uint8_t)result != 0 )
  {
    v7 = *pDwArg2;
    *pDwArg2 = *pDwArg1;
    *pDwArg1 = v7;
    return sub_421AF0(pDwArg2 + 1, pDwArg1 + 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x422780 sub_422780
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_422780(int *this)
{
  return sub_422340(this);
}



// ------------------------------------------------------------
// 0x422790 sub_422790
// ------------------------------------------------------------
int /*cdecl*/ sub_422790(int *pDwArg1, int nArg2, uint8_t (/*cdecl*/ *uArg3)(int, int))
{
  int nArg22; // esi
  int result; // eax

  nArg22 = nArg2;
  for ( result = (nArg2 - (int)pDwArg1) >> 5; result > 1; result = (nArg22 - (int)pDwArg1) >> 5 )
  {
    sub_4222F0(pDwArg1, nArg22, uArg3);
    nArg22 -= 32;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4227D0 sub_4227D0
// ------------------------------------------------------------
int /*cdecl*/ sub_4227D0(int *pDwArg1, int *pDwArg2, int *pDwArg3, uint8_t (/*cdecl*/ *uArg4)(int *, int *))
{
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // edi
  int *v9; // [esp-3Ch] [ebp-3Ch]
  int *v12; // [esp-14h] [ebp-14h]
  int *v13; // [esp+8h] [ebp+8h]
  int *v14; // [esp+10h] [ebp+10h]

  v4 = ((char *)pDwArg3 - (char *)pDwArg1) >> 5;
  if ( v4 <= 40 )
    return sub_422700(pDwArg1, pDwArg2, pDwArg3, uArg4);
  v5 = (v4 + 1) / 8;
  v6 = 8 * v5;
  v5 <<= 6;
  v7 = v6 * 4;
  v12 = (int *)((char *)pDwArg1 + v5);
  v13 = &pDwArg1[v6];
  sub_422700(pDwArg1, v13, v12, uArg4);
  sub_422700((int *)((char *)pDwArg2 - v7), pDwArg2, (int *)((char *)pDwArg2 + v7), uArg4);
  v9 = (int *)((char *)pDwArg3 - v5);
  v14 = (int *)((char *)pDwArg3 - v7);
  sub_422700(v9, v14, pDwArg3, uArg4);
  return sub_422700(v13, pDwArg2, v14, uArg4);
}



// ------------------------------------------------------------
// 0x422870 sub_422870
// ------------------------------------------------------------
void /*thiscall*/ sub_422870(int *this, int *pDwArg2)
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 5;
  else
    fld_e2 = 0;
  if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) >> 5 )
  {
    fld_e22 = *(this + 2);
    sub_421F90(fld_e22, 1, pDwArg2);
    *(this + 2) = fld_e22 + 32;
  }
  else
  {
    sub_4223B0(this, (char *)*(this + 2), 1u, pDwArg2);
  }
}



// ------------------------------------------------------------
// 0x4228E0 sub_4228E0
// ------------------------------------------------------------
int **/*cdecl*/ sub_4228E0(int **pDwArg1, unsigned int pArg2, int *pDwArg3, uint8_t (/*cdecl*/ *uArg4)(int *, int *))
{
  int *v4; // esi
  int *v5; // ebx
  int *v6; // eax
  int *v7; // edi
  int v8; // ecx
  bool v9; // zf
  int *v10; // ebx
  int v11; // eax
  bool v12; // cf
  int v13; // eax
  int *v14; // eax
  int *v15; // ecx
  int v16; // ecx
  int v17; // eax
  int v18; // edx
  int v20; // [esp+Ch] [ebp-Ch]
  int *v21; // [esp+10h] [ebp-8h]
  int *v22; // [esp+14h] [ebp-4h]
  int *i; // [esp+14h] [ebp-4h]

  v4 = (int *)(pArg2 + 32 * (((int)((int)pDwArg3 - pArg2) >> 5) / 2));
  sub_4227D0(pArg2, v4, pDwArg3 - 8, uArg4);
  v5 = v4 + 8;
  v21 = v4 + 8;
  if ( pArg2 < (unsigned int)v4 )
  {
    do
    {
      v22 = v4 - 8;
      if ( uArg4(v4 - 8, v4) != 0 )
        break;
      if ( uArg4(v4, v22) != 0 )
        break;
      v4 -= 8;
    }
    while ( pArg2 < (unsigned int)v22 );
  }
  if ( v5 < pDwArg3 )
  {
    do
    {
      if ( uArg4(v5, v4) != 0 )
        break;
      if ( uArg4(v4, v5) != 0 )
        break;
      v5 += 8;
    }
    while ( v5 < pDwArg3 );
    v21 = v5;
  }
  v6 = v4;
  v7 = v5;
  for ( i = v4; ; v6 = i )
  {
    while ( 1 )
    {
      if ( v7 < pDwArg3 )
      {
        do
        {
          if ( uArg4(v4, v7) == 0 )
          {
            if ( uArg4(v7, v4) != 0 )
              break;
            v8 = *v5;
            *v5 = *v7;
            *v7 = v8;
            v5 += 8;
            sub_421AF0(v7 + 1);
          }
          v7 += 8;
        }
        while ( v7 < pDwArg3 );
        v6 = i;
        v21 = v5;
      }
      v9 = v6 == (int *)pArg2;
      if ( (unsigned int)v6 > pArg2 )
      {
        v10 = v6 - 8;
        do
        {
          if ( uArg4(v10, v4) == 0 )
          {
            if ( uArg4(v4, v10) != 0 )
              break;
            v11 = *(v4 - 8);
            v4 -= 8;
            *v4 = *v10;
            *v10 = v11;
            sub_421AF0(v10 + 1);
          }
          v10 -= 8;
          v12 = pArg2 < (unsigned int)(i - 8);
          i -= 8;
        }
        while ( v12 );
        v6 = i;
        v5 = v21;
        v9 = i == (int *)pArg2;
      }
      if ( v9 )
        break;
      v14 = v6 - 8;
      i = v14;
      if ( v7 != pDwArg3 )
      {
        v15 = v7;
        v7 += 8;
        goto LABEL_29;
      }
      v4 -= 8;
      if ( v14 != v4 )
      {
        v16 = *v14;
        *v14 = *v4;
        *v4 = v16;
        sub_421AF0(v4 + 1);
      }
      v17 = *v4;
      v18 = *(v5 - 8);
      v5 -= 8;
      *v4 = v18;
      *v5 = v17;
      v21 = v5;
      sub_421AF0(v5 + 1);
      v6 = i;
    }
    if ( v7 == pDwArg3 )
      break;
    if ( v5 != v7 )
    {
      v13 = *v4;
      *v4 = *v5;
      *v5 = v13;
      sub_421AF0(v5 + 1);
    }
    v5 += 8;
    v14 = v7;
    v7 += 8;
    v15 = v4;
    v21 = v5;
    v4 += 8;
LABEL_29:
    v20 = *v15;
    *v15 = *v14;
    *v14 = v20;
    sub_421AF0(v14 + 1);
  }
  *pDwArg1 = v4;
  pDwArg1[1] = v5;
  return pDwArg1;
}


// ------------------------------------------------------------
// 0x422AE0 sub_422AE0
// ------------------------------------------------------------
int /*cdecl*/ sub_422AE0(int *pDwArg1, int *pDwArg2, int nArg3, uint8_t (/*cdecl*/ *uArg4)(int, int))
{
  int *pDwArg12; // ebx
  int *pDwArg22; // edi
  int result; // eax
  int *v8; // [esp+Ch] [ebp-8h] BYREF
  int *v9; // [esp+10h] [ebp-4h]

  pDwArg12 = pDwArg1;
  pDwArg22 = pDwArg2;
  result = ((char *)pDwArg2 - (char *)pDwArg1) >> 5;
  if ( result <= 32 )
  {
LABEL_7:
    if ( result > 1 )
      return sub_422670((int)pDwArg12, (int)pDwArg22, uArg4);
  }
  else
  {
    while ( nArg3 > 0 )
    {
      sub_4228E0(&v8, pDwArg12, pDwArg22, (uint8_t (/*cdecl*/ *)(int *, int *))uArg4);
      nArg3 = nArg3 / 2 / 2 + nArg3 / 2;
      if ( (int)(((char *)v8 - (char *)pDwArg12) & 0xFFFFFFE0) >= (int)(((char *)pDwArg22 - (char *)v9) & 0xFFFFFFE0) )
      {
        sub_422AE0(v9, pDwArg22, nArg3, uArg4);
        pDwArg22 = v8;
      }
      else
      {
        sub_422AE0(pDwArg12, v8, nArg3, uArg4);
        pDwArg12 = v9;
      }
      result = ((char *)pDwArg22 - (char *)pDwArg12) >> 5;
      if ( result <= 32 )
        goto LABEL_7;
    }
    if ( (int)(((char *)pDwArg22 - (char *)pDwArg12) & 0xFFFFFFE0) > 32 )
      sub_422270((int)pDwArg12, (int)pDwArg22, uArg4);
    return sub_422790(pDwArg12, (int)pDwArg22, uArg4);
  }
  return result;
}



// ============================================================
// §4 CStringManager 字符串表（0x422BD0-0x422E70）
//   文件加载（"N>文本" 行格式）+ 按 ID 二分取串；全工程 UI/播报取串总入口
// ============================================================
// ------------------------------------------------------------
// 0x422BD0 sub_422BD0
// ------------------------------------------------------------
// 【字符串表加载】逐行解析 "N>文本"（'//' 注释行跳过；'>' 前至多 10 位数字），
//   "\\n" → "\n" 替换（sub_4218A0），装入 dword_8F7A74 映射 + dword_8F7A78/8F7A7C
//   数组并排序（sub_422AE0，比较器 sub_4212E0）。返回条目数。
int /*cdecl*/ sub_422BD0(char *FileName)
{
  FILE *pFile; // eax
  FILE *pFile2; // edi
  unsigned int nLen; // kr00_4
  signed int nLen2; // eax
  int i; // esi
  char v7; // cl
  int v8; // edi
  size_t j; // esi
  int v10; // [esp+8h] [ebp-85Ch] BYREF
  uint8_t v11[4]; // [esp+Ch] [ebp-858h] BYREF
  void *Block; // [esp+10h] [ebp-854h]
  int v13; // [esp+20h] [ebp-844h]
  unsigned int v14; // [esp+24h] [ebp-840h]
  FILE *pFile3; // [esp+28h] [ebp-83Ch]
  char Buffer; // [esp+2Ch] [ebp-838h] BYREF
  char Src[2047]; // [esp+2Dh] [ebp-837h] BYREF
  char String[12]; // [esp+82Ch] [ebp-38h] BYREF
  int v19; // [esp+838h] [ebp-2Ch] BYREF
  void *v20; // [esp+83Ch] [ebp-28h]
  int v21; // [esp+84Ch] [ebp-18h]
  unsigned int v22; // [esp+850h] [ebp-14h]
  int dword_796E502; // [esp+854h] [ebp-10h]
  int v24; // [esp+860h] [ebp-4h]

  dword_796E502 = dword_796E50;
  pFile = fopen(FileName, "r");
  pFile2 = pFile;
  pFile3 = pFile;
  if ( pFile == nullptr )
    return -1;
  if ( fgets(&Buffer, 2048, pFile) != nullptr )
  {
    do
    {
      nLen = strlen(&Buffer);
      nLen2 = nLen;
      if ( nLen != 0 )
      {
        if ( *((uint8_t *)&pFile3 + nLen + 3) == 10 )
        {
          *((uint8_t *)&pFile3 + nLen + 3) = 0;
          nLen2 = nLen - 1;
        }
        if ( nLen2 != 0 && (Buffer != 47 || Src[0] != 47) )
        {
          for ( i = 0; i < nLen2; String[i++] = v7 )
          {
            v7 = Src[i - 1];
            if ( v7 == 62 )
              break;
            if ( i >= 10 || v7 < 48 || v7 > 57 )
              goto LABEL_24;
          }
          if ( i != nLen2 )
          {
            String[i] = 0;
            v8 = j__atol(String);
            v22 = 15;
            v21 = 0;
            LOBYTE(v20) = 0;
            v24 = 0;
            sub_4015C0(&Src[i], strlen(&Src[i]));
            for ( j = sub_4027F0("\\n", 0, 2); j != -1; j = sub_4027F0("\\n", j, 2) )
              sub_4218A0((unsigned int *)&v19, j, 2u, "\n", 1u);
            v10 = v8;
            v14 = 15;
            v13 = 0;
            LOBYTE(Block) = 0;
            sub_4014D0((std::_String_base *)v11, &v19, 0, -1);
            LOBYTE(v24) = 1;
            sub_422870(&dword_8F7A74, &v10);
            if ( v14 >= 0x10 )
              j__free(Block);
            v14 = 15;
            v13 = 0;
            LOBYTE(Block) = 0;
            v24 = -1;
            if ( v22 >= 0x10 )
              j__free(v20);
            pFile2 = pFile3;
            v22 = 15;
            v21 = 0;
            LOBYTE(v20) = 0;
          }
        }
      }
LABEL_24:
      ;
    }
    while ( fgets(&Buffer, 2048, pFile2) != nullptr );
  }
  fclose(pFile2);
  sub_422AE0(
    (int *)dword_8F7A78,
    (int *)dword_8F7A7C,
    (dword_8F7A7C - dword_8F7A78) >> 5,
    (uint8_t (/*cdecl*/ *)(int, int))sub_4212E0);
  if ( dword_8F7A78 != 0 )
    return (dword_8F7A7C - dword_8F7A78) >> 5;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x422E70 sub_422E70
// ------------------------------------------------------------
// 【CStringManager::getStr(id)】懒加载：sub_421300 解包提取失败 → "String Table
//   extraction failed"/"Fatal Error" + exit(1)；sub_422BD0 装载失败 → "String Table
//   load failed" + 删临时文件 lpFileName。命中返回串体；未命中 sprintf
//   "CStringManager::getStr(%d) == NULL" 至 byte_8F7A88。全工程取串总入口
//   （net_socket.cpp 与各播报点均引用）。
char */*cdecl*/ sub_422E70(int nArg1)
{
  HWND DesktopWindow; // eax
  HWND v2; // eax
  uint32_t *v3; // esi
  int nArg12; // [esp+Ch] [ebp-50h] BYREF
  uint8_t v6[4]; // [esp+10h] [ebp-4Ch] BYREF
  void *Block; // [esp+14h] [ebp-48h]
  int v8; // [esp+24h] [ebp-38h]
  unsigned int v9; // [esp+28h] [ebp-34h]
  uint8_t v10[4]; // [esp+2Ch] [ebp-30h] BYREF
  void *v11; // [esp+30h] [ebp-2Ch]
  int v12; // [esp+40h] [ebp-1Ch]
  unsigned int v13; // [esp+44h] [ebp-18h]
  uint32_t *v14; // [esp+48h] [ebp-14h] BYREF
  int v15; // [esp+58h] [ebp-4h]

  if ( byte_8F7A60 == 0 )
  {
    if ( sub_421300((char *)lpFileName) <= 0 )
    {
      DesktopWindow = GetDesktopWindow();
      MessageBoxA(DesktopWindow, "String Table extraction failed", "Fatal Error", 0);
      exit(1);
    }
    if ( sub_422BD0((char *)lpFileName) <= 0 )
    {
      v2 = GetDesktopWindow();
      MessageBoxA(v2, "String Table load failed", "Fatal Error", 0);
      DeleteFileA(lpFileName);
      exit(1);
    }
    DeleteFileA(lpFileName);
    byte_8F7A60 = 1;
  }
  v13 = 15;
  v12 = 0;
  LOBYTE(v11) = 0;
  sub_4015C0((void *)szPassword, 0);
  v15 = 0;
  nArg12 = nArg1;
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  sub_4014D0((std::_String_base *)v6, v10, 0, -1);
  LOBYTE(v15) = 1;
  sub_4217E0((int *)&v14, dword_8F7A78, dword_8F7A7C, (int)&nArg12, (uint8_t (/*cdecl*/ *)(int, int))sub_4212E0);
  v3 = v14;
  if ( v9 >= 0x10 )
    j__free(Block);
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  if ( v13 >= 0x10 )
    j__free(v11);
  if ( *v3 == nArg1 )
  {
    if ( v3[7] < 0x10u )
      return (char *)(v3 + 2);
    else
      return (char *)v3[2];
  }
  else
  {
    sprintf(byte_8F7A88, "CStringManager::getStr(%d) == NULL", nArg1);
    return byte_8F7A88;
  }
}



// ============================================================
// §5 游戏 Socket —— 两步式发包（0x423020-0x423340）
//   Begin(0x423200) / Append(0x423290) / Commit(0x423380)
//   ★ 已精修版见 src/nengine/net_socket.cpp（含字段表与协议注解）
// ============================================================
// ------------------------------------------------------------
// 0x423020 sub_423020
// ------------------------------------------------------------
int /*thiscall*/ sub_423020(__time64_t *Time)
{
  struct tm *v1; // eax

  v1 = _localtime64(Time);
  if ( v1 != nullptr )
    return v1->tm_mon + 1;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x423040 sub_423040
// ------------------------------------------------------------
int /*thiscall*/ sub_423040(__time64_t *Time)
{
  struct tm *v1; // eax

  v1 = _localtime64(Time);
  if ( v1 != nullptr )
    return v1->tm_mday;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x423060 sub_423060
// ------------------------------------------------------------
int /*thiscall*/ sub_423060(__time64_t *Time)
{
  struct tm *v1; // eax

  v1 = _localtime64(Time);
  if ( v1 != nullptr )
    return v1->tm_hour;
  else
    return -1;
}



// ------------------------------------------------------------
// 0x423080 sub_423080
// ------------------------------------------------------------
int /*thiscall*/ sub_423080(__time64_t *Time)
{
  struct tm *v1; // eax

  v1 = _localtime64(Time);
  if ( v1 != nullptr )
    return v1->tm_min;
  else
    return -1;
}



// ------------------------------------------------------------
// 0x4230A0 sub_4230A0
// ------------------------------------------------------------
// 【CNGameSocket 构造】sub_698870(socket 族) 申领 0x100000 缓冲；发送序号(+464)/
//   发送锁(+466) 复位。全局实例 = dword_8F7B08（见 net_socket.cpp 文件头）。
uint32_t */*thiscall*/ sub_4230A0(uint32_t *this)
{
  sub_6986D0();
  *this = &vftbl_CNGameSocket;
  *(this + 112) = 0;
  *(this + 113) = 0;
  *(this + 114) = 0;
  if ( sub_698870(*(void **)(dword_79C0A0 + 16), 0x100000u) >= 0 )
  {
    *(this + 115) = rand();
    *((uint16_t *)this + 232) = 0;
    *((uint8_t *)this + 466) = 0;
  }
  return this;
}



// ------------------------------------------------------------
// 0x423130 CNGameSocket__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNGameSocket__vmt0(void *Block, char pszArg2)
{
  sub_423160();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x423160 sub_423160
// ------------------------------------------------------------
int /*thiscall*/ sub_423160(uint32_t *this)
{
  *this = &vftbl_CNGameSocket;
  sub_6987C0();
  return sub_698720(this);
}



// ------------------------------------------------------------
// 0x4231B0 sub_4231B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4231B0(int this, const char *ArgList, int nArg3)
{
  int result; // eax

  *(uint8_t *)(this + 466) = 0;
  *(uint32_t *)(this + 456) = 0;
  *(uint16_t *)(this + 464) = 0;
  off_77F3FC("[%s][%d]", ArgList, nArg3);
  result = sub_698DC0(this, (int)ArgList, nArg3);
  if ( result >= 0 )
    return 1;
  return result;
}



// ------------------------------------------------------------
// 0x423200 sub_423200
// ------------------------------------------------------------
// 【发包 Begin(type) · 两步式第一步】★已精修：src/nengine/net_socket.cpp packet_send_begin
//   未连接 → 0x80000004；上一包未提交 → asc_6C37C8 日志 + 0x80000000；
//   申领发送上下文(+452) + 12 字节包头框架 {01,type}（sub_698C80）。
int /*thiscall*/ sub_423200(int this, char pszArg2)
{
  uint8_t v4[2]; // [esp+4h] [ebp-Ch] BYREF
  int v5; // [esp+6h] [ebp-Ah]

  if ( *(uint8_t *)(this + 8) == 0 )
    return -2147483564;
  if ( *(uint32_t *)(this + 452) != 0 || *(uint32_t *)(this + 448) != 0 )
  {
    off_77F3FC(asc_6C37C8);
    return 0x80000000;
  }
  else
  {
    v4[0] = 1;
    v4[1] = pszArg2;
    v5 = 0;
    *(uint32_t *)(this + 452) = sub_698D70(this);
    sub_698C80(v4, 12);
    *(uint32_t *)(this + 448) = 0;
    return 1;
  }
}



// ------------------------------------------------------------
// 0x423290 sub_423290
// ------------------------------------------------------------
// 【发包 Append(buf,len)】校验连接/参数 → +448 计数累加 + sub_698C80 包体入队。
int /*thiscall*/ sub_423290(int this, int nArg2, int nArg3)
{
  if ( *(uint8_t *)(this + 8) == 0 )
    return -2147483564;
  if ( nArg2 == 0 )
    return -2147483640;
  *(uint32_t *)(this + 448) += nArg3;
  return sub_698C80(nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x4232E0 sub_4232E0
// ------------------------------------------------------------
__time64_t */*stdcall*/ sub_4232E0(__time64_t *uArg1)
{
  *uArg1 = _time64(nullptr);
  return uArg1;
}



// ------------------------------------------------------------
// 0x423300 sub_423300
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_423300(unsigned int *pDwArg1, const char *pArg2)
{
  return sub_40BF00((std::_String_base *)pDwArg1, 0, pDwArg1[5], pArg2, strlen(pArg2)) == 0;
}



// ------------------------------------------------------------
// 0x423340 sub_423340
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_423340(unsigned int *pDwArg1, const char *pArg2)
{
  return sub_40BF00((std::_String_base *)pDwArg1, 0, pDwArg1[5], pArg2, strlen(pArg2)) != 0;
}



// ------------------------------------------------------------
// 0x423380 sub_423380
// ------------------------------------------------------------
// 【发包 Commit() · 两步式第二步】★已精修：src/nengine/net_socket.cpp packet_send_commit
//   'SendLock ' 检查(+466) → 包总长(ctx+2)/序号(ctx+10, +464 自增)/校验和 sub_48BE40 →
//   包体拷贝 sub_48BD40 → '[-> COMMAND PACKET]' 日志（包名表 off_790928 + 时间戳）→
//   type==3 置发送锁 → sub_698A50 实发，失败 → 串145 播报（sub_44E8D0, id 0x1B）。
int /*thiscall*/ sub_423380(int this)
{
  int fld_1C4; // edi
  int fld_1C42; // eax
  int16_t fld_1D0; // dx
  int v6; // ecx
  int v7; // ebx
  int fld_1C0; // eax
  struct tm *v9; // eax
  struct tm *v10; // eax
  struct tm *v11; // eax
  struct tm *v12; // eax
  int tm_min; // ebx
  struct tm *v14; // eax
  int tm_sec; // eax
  int v16; // esi
  char *v17; // eax
  uint32_t *v18; // eax
  int tm_hour; // [esp+4h] [ebp-40h]
  int tm_mday; // [esp+8h] [ebp-3Ch]
  int v21; // [esp+Ch] [ebp-38h]
  __time64_t Time; // [esp+10h] [ebp-34h] BYREF
  uint8_t v23[4]; // [esp+18h] [ebp-2Ch] BYREF
  uint32_t v24[10]; // [esp+1Ch] [ebp-28h] BYREF

  v24[6] = dword_796E50;
  if ( *(uint8_t *)(this + 466) != 0 )
  {
    off_77F3FC(aSendlock);
    return 0x80000000;
  }
  else if ( *(uint8_t *)(this + 8) != 0 )
  {
    fld_1C4 = *(uint32_t *)(this + 452);
    if ( fld_1C4 != 0 )
    {
      *(uint32_t *)(fld_1C4 + 2) = *(uint32_t *)(this + 448) + 12;
      fld_1C42 = *(uint32_t *)(this + 452);
      fld_1D0 = *(uint16_t *)(this + 464);
      v6 = fld_1C42 + 10;
      v7 = fld_1C42 + 12;
      *(uint16_t *)(fld_1C4 + 10) = fld_1D0;
      fld_1C0 = *(uint32_t *)(this + 448);
      ++*(uint16_t *)(this + 464);
      *(uint32_t *)(fld_1C4 + 6) = sub_48BE40(v6, fld_1C0 + 2);
      sub_48BD40(v7, *(uint32_t *)(this + 448), this + 460);
      *(uint32_t *)(this + 452) = 0;
      *(uint32_t *)(this + 448) = 0;
      Time = _time64(nullptr);
      v9 = _localtime64(&Time);
      if ( v9 != nullptr )
        v21 = v9->tm_mon + 1;
      else
        v21 = 0;
      v10 = _localtime64(&Time);
      if ( v10 != nullptr )
        tm_mday = v10->tm_mday;
      else
        tm_mday = 0;
      v11 = _localtime64(&Time);
      if ( v11 != nullptr )
        tm_hour = v11->tm_hour;
      else
        tm_hour = -1;
      v12 = _localtime64(&Time);
      if ( v12 != nullptr )
        tm_min = v12->tm_min;
      else
        tm_min = -1;
      v14 = _localtime64(&Time);
      if ( v14 != nullptr )
        tm_sec = v14->tm_sec;
      else
        tm_sec = -1;
      off_77F3FC(
        "\n[-> COMMAND PACKET] Packet : %s, Size : %d, CheckSum : %d (%2d%2d-%2d:%2d:%2d)",
        *(const char **)&off_790928[4 * *(uint8_t *)(fld_1C4 + 1)],
        *(uint32_t *)(fld_1C4 + 2),
        *(uint32_t *)(fld_1C4 + 6),
        v21,
        tm_mday,
        tm_hour,
        tm_min,
        tm_sec);
      if ( *(uint8_t *)(fld_1C4 + 1) == 3 )
        *(uint8_t *)(this + 466) = 1;
      v16 = sub_698A50(this);
      if ( v16 != 1 && dword_8F8528 != nullptr )
      {
        v17 = (char *)sub_422E70(145);
        sub_401710(v17);
        v18 = (uint32_t *)v24[0];
        v24[9] = 0;
        if ( v24[5] < 0x10u )
          v18 = v24;
        sub_44E8D0(dword_8F8528, (void *)0x1B, v18, 1);
        sub_501490(v23);
      }
      return v16;
    }
    else
    {
      return 0x80000000;
    }
  }
  else
  {
    return -2147483564;
  }
}


// ============================================================
// §6 CNGameSocket 收包派发（0x4235A0-0x4238E0）
//   vmt4 收包循环（nLen:ISocket/GameSocket 日志）→ sub_48BE70 喂分发器；'SOCKET CLOSE %d'
// ============================================================
// ------------------------------------------------------------
// 0x4235A0 CNGameSocket__vmt4
// ------------------------------------------------------------
// 【CNGameSocket vmt4 · 收包派发】case1: sub_698B50 拉长（'nLen:ISocket/GameSocket'
//   日志）循环 → sub_48BE70 喂 dword_8F7A24 分发器；'SOCKET CLOSE %d' 关闭分支。
int /*thiscall*/ sub_4235A0(int this, int nArg2, int nArg3, int nArg4, unsigned int uArg5)
{
  int fld_1C8; // eax
  int v7; // edi
  char *v8; // eax
  char *v9; // eax
  char *psz; // eax
  void *p_Block; // eax
  int v12; // eax
  int v13; // esi
  char *v14; // eax
  char v15; // cl
  char *v16; // eax
  char v17; // cl
  char *v18; // eax
  char v19; // cl
  int pThis_2; // esi
  int dword_8F7A242; // edi
  int v22; // eax
  size_t v24; // [esp+Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+10h] [ebp-28h] BYREF
  unsigned int v26; // [esp+20h] [ebp-18h]
  unsigned int v27; // [esp+24h] [ebp-14h]
  int dword_796E502; // [esp+28h] [ebp-10h]
  int v29; // [esp+34h] [ebp-4h]

  dword_796E502 = dword_796E50;
  switch ( (uint16_t)uArg5 )
  {
    case 1u:
      v13 = sub_698B50(this);
      off_77F3FC("nLen:ISocket : %d", v13);
      if ( v13 >= 0 )
      {
        while ( 1 )
        {
          if ( *(uint8_t *)(this + 8) != 0 )
          {
            if ( (uint8_t)sub_698D90(this) != 0 )
              pThis_2 = *(uint32_t *)(sub_698D80(this) + 2);
            else
              pThis_2 = sub_698B50(this);
          }
          else
          {
            pThis_2 = 0;
          }
          off_77F3FC("nLen:GameSocket : %d", pThis_2);
          if ( pThis_2 == 0 )
            break;
          dword_8F7A242 = dword_8F7A24;
          if ( dword_8F7A24 != 0 )
          {
            v22 = sub_698D80(this);
            if ( sub_48BE70(dword_8F7A242, v22, pThis_2) < 0 )
              break;
          }
        }
      }
      else
      {
        switch ( v13 )
        {
          case -2147483647:
            v18 = (char *)sub_422E70(146);
            off_77F3F8(v19, v18);
            break;
          case -2147483564:
            v16 = (char *)sub_422E70(147);
            off_77F3F8(v17, v16);
            break;
          case -2147483563:
            v14 = (char *)sub_422E70(148);
            off_77F3F8(v15, v14);
            break;
          default:
            break;
        }
      }
      break;
    case 0x10u:
      if ( HIWORD(uArg5) != 0 )
      {
        v12 = sub_422E70(149);
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v12, 1);
      }
      break;
    case 0x20u:
      off_77F3FC("SOCKET CLOSE %d", *(uint32_t *)(this + 436));
      v27 = 15;
      v26 = 0;
      LOBYTE(Block) = 0;
      sub_4015C0(&v24, szPassword, 0);
      fld_1C8 = *(uint32_t *)(this + 456);
      v29 = 0;
      v7 = 1;
      switch ( fld_1C8 )
      {
        case 0:
          if ( *(uint32_t *)(dword_8F7A24 + 12) == 5 )
          {
            sub_406D60(&v24, (char *)szPassword);
            v7 = 0;
          }
          else if ( *(uint32_t *)(dword_8F7A24 + 108) == 0 )
          {
            v8 = (char *)sub_422E70(150);
            goto LABEL_19;
          }
          break;
        case 1:
          v8 = (char *)sub_422E70(151);
          goto LABEL_19;
        case 2:
          v8 = (char *)sub_422E70(152);
          goto LABEL_19;
        case 3:
          v9 = (char *)sub_422E70(153);
          goto LABEL_21;
        case 4:
          v9 = (char *)sub_422E70(154);
          goto LABEL_21;
        case 5:
          v9 = (char *)sub_422E70(155);
          goto LABEL_21;
        case 6:
          v9 = (char *)sub_422E70(156);
          goto LABEL_21;
        case 7:
          v8 = (char *)sub_422E70(157);
          goto LABEL_19;
        case 8:
          v9 = (char *)sub_422E70(158);
          goto LABEL_21;
        case 9:
          v9 = (char *)sub_422E70(159);
          goto LABEL_21;
        case 10:
          v8 = (char *)sub_422E70(160);
LABEL_19:
          sub_406D60(&v24, v8);
          v7 = 2;
          break;
        case 11:
          v9 = (char *)sub_422E70(161);
LABEL_21:
          sub_406D60(&v24, v9);
          break;
        default:
          psz = (char *)sub_422E70(162);
          sub_4015C0(&v24, psz, strlen(psz));
          break;
      }
      if ( sub_40BF00((std::_String_base *)&v24, 0, v26, szPassword, 0) != 0 )
      {
        p_Block = Block;
        if ( v27 < 0x10 )
          p_Block = &Block;
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)p_Block, v7);
      }
      if ( *(uint32_t *)(this + 436) == 0 )
        sub_46E360(*(uint32_t *)(dword_8F7A24 + 36));
      v29 = -1;
      if ( v27 >= 0x10 )
        j__free(Block);
      v27 = 15;
      v26 = 0;
      LOBYTE(Block) = 0;
      break;
    default:
      break;
  }
  return sub_698CA0(nArg2, nArg3, nArg4, uArg5);
}


// ============================================================
// §7 屏幕过渡与整型/浮点杂项辅助（0x4238E0-0x424680）
//   淡入淡出 0x424530（被连击宿主作命中脉冲复用）
// ============================================================
// ------------------------------------------------------------
// 0x4238E0 sub_4238E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4238E0(int *this)
{
  int fld_e6; // esi
  int fld_e62; // esi

  fld_e6 = *(this + 6);
  if ( fld_e6 < sub_699000((int)this) )
    return 0;
  fld_e62 = *(this + 6);
  return fld_e62 - sub_699000((int)this);
}



// ------------------------------------------------------------
// 0x423910 sub_423910
// ------------------------------------------------------------
int /*thiscall*/ sub_423910(uint32_t *this)
{
  *(this + 298) = 0;
  dword_77F6DC = 1065353216;
  dword_8F7BD0 = 0;
  dword_8F7BD4 = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x423930 sub_423930
// ------------------------------------------------------------
int /*thiscall*/ sub_423930(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7, int nArg8, int nArg9, int nArg10)
{
  int result; // eax

  result = nArg4;
  if ( nArg4 != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, void *, int, int, int, int, int, int))(*(uint32_t *)nArg4 + 156))(
             nArg4,
             nArg2,
             nArg3,
             this,
             nArg5,
             nArg6,
             nArg7,
             nArg8,
             nArg9,
             nArg10);
  return result;
}



// ------------------------------------------------------------
// 0x423970 sub_423970
// ------------------------------------------------------------
int /*cdecl*/ sub_423970(int nArg1, int nArg2)
{
  int v2; // eax
  int v4; // [esp-8h] [ebp-Ch]

  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 124))(nArg1);
  v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 120))(nArg1);
  return sub_48C0A0(v2, v4, nArg2);
}



// ------------------------------------------------------------
// 0x4239A0 sub_4239A0
// ------------------------------------------------------------
int /*stdcall*/ sub_4239A0(int nArg1)
{
  int v1; // eax
  int v3; // [esp-4h] [ebp-Ch]

  v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 36))(nArg1) + 8);
  v1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 120))(nArg1);
  return sub_45E490(v1, v3);
}



// ------------------------------------------------------------
// 0x4239D0 sub_4239D0
// ------------------------------------------------------------
int /*stdcall*/ sub_4239D0(int nArg1, float fArg2)
{
  int v3; // eax
  int v5; // [esp-Ch] [ebp-14h]
  int v6; // [esp-8h] [ebp-10h]

  v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 36))(nArg1) + 8);
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 128))(nArg1);
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 124))(nArg1);
  return sub_45E4D0(v3, v5, v6, fArg2);
}



// ------------------------------------------------------------
// 0x423A20 sub_423A20
// ------------------------------------------------------------
int /*thiscall*/ sub_423A20(int this)
{
  int v1; // edx
  uint32_t *pThis_27; // eax
  int i; // esi

  v1 = 0;
  pThis_27 = (uint32_t *)(this + 39);
  do
  {
    *(uint32_t *)(this + 4 * v1) = 0;
    *(uint8_t *)(this + v1 + 12) = 0;
    for ( i = 2; i != 0; --i )
    {
      *(pThis_27 - 6) = 0;
      *pThis_27++ = 0;
    }
    ++v1;
  }
  while ( v1 < 3 );
  *(uint32_t *)(this + 63) = 0;
  *(uint8_t *)(this + 67) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint8_t *)(this + 84) = 0;
  *(uint32_t *)(this + 85) = 0;
  *(uint8_t *)(this + 89) = 0;
  *(uint32_t *)(this + 90) = 100;
  *(uint32_t *)(this + 94) = 100;
  return 100;
}



// ------------------------------------------------------------
// 0x423A80 sub_423A80
// ------------------------------------------------------------
int64_t /*cdecl*/ sub_423A80(int nArg1, int nArg2, int nArg3, int nArg4)
{
  double v4; // st7
  float v6; // [esp+0h] [ebp-10h]
  float v7; // [esp+4h] [ebp-Ch]

  v7 = (float)nArg2;
  v6 = (float)nArg1;
  v4 = sub_4049C0(v6, v7, nArg3, nArg4);
  return _ftol2(v4);
}



// ------------------------------------------------------------
// 0x423AB0 sub_423AB0
// ------------------------------------------------------------
int64_t /*cdecl*/ sub_423AB0(int nArg1, int nArg2, int nArg3, int nArg4, char pszArg5)
{
  double v5; // st7
  float v7; // [esp+0h] [ebp-14h]
  float v8; // [esp+4h] [ebp-10h]

  v8 = (float)nArg2;
  v5 = (double)nArg1;
  v7 = v5;
  sub_4049F0(v7, v8, nArg3, nArg4, pszArg5);
  return _ftol2(v5);
}



// ------------------------------------------------------------
// 0x423AE0 sub_423AE0
// ------------------------------------------------------------
BOOL /*cdecl*/ sub_423AE0(int nArg1, int nArg2)
{
  return dword_99FB7C == nArg1 && dword_99FB80 == nArg2;
}



// ------------------------------------------------------------
// 0x423B10 sub_423B10
// ------------------------------------------------------------
int /*thiscall*/ sub_423B10(uint32_t *this)
{
  if ( sub_456480(this) == -1 )
    return 0;
  else
    return *(this + sub_456480(this) + 4);
}



// ------------------------------------------------------------
// 0x423B30 sub_423B30
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_423B30(uint8_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__CNNumberSet;
  sub_699E20(this);
  sub_699E40(nArg2, nArg3, nArg4, nArg5);
  return this;
}



// ------------------------------------------------------------
// 0x423B90 nengine__CNNumberSet__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nengine__CNNumberSet__vmt0(void *Block, char pszArg2)
{
  sub_423BC0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x423BC0 sub_423BC0
// ------------------------------------------------------------
int /*thiscall*/ sub_423BC0(uint8_t *this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_nengine__CNNumberSet;
  result = sub_699EC0();
  *(uint32_t *)this = &vftbl_nengine__IObject;
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x423C10 sub_423C10
// ------------------------------------------------------------
// 【评价值复位】+556/+900/+592(+609/610)/+628(+645/646) 清零、+1252 = 8（模式复位值）。
//   被 0x42B7E0 构造器调用。
void /*fastcall*/ sub_423C10(int pArg1, int nArg2)
{
  int v3; // edx
  int v4; // edx
  uint32_t *v5; // edi
  int v6; // eax
  uint8_t *v7; // ecx
  int v8; // ebx
  int v9; // ebx
  int v10; // edi
  int m; // ebx
  int i; // [esp+Ch] [ebp-Ch]
  int j; // [esp+Ch] [ebp-Ch]
  int k; // [esp+Ch] [ebp-Ch]
  uint32_t *v15; // [esp+10h] [ebp-8h]
  int v16; // [esp+14h] [ebp-4h]

  *(uint32_t *)(pArg1 + 36) = 0;
  *(uint32_t *)(pArg1 + 40) = 0;
  *(uint32_t *)(pArg1 + 44) = 0;
  *(uint8_t *)(pArg1 + 48) = 0;
  *(uint32_t *)(pArg1 + 52) = 0;
  *(uint32_t *)(pArg1 + 84) = -1;
  *(uint32_t *)(pArg1 + 88) = -1;
  *(uint32_t *)(pArg1 + 92) = -1;
  *(uint32_t *)(pArg1 + 96) = -1;
  *(uint32_t *)(pArg1 + 100) = 4;
  *(uint32_t *)(pArg1 + 1256) = 1;
  *(uint32_t *)(pArg1 + 104) = 0;
  *(uint32_t *)(pArg1 + 108) = 0;
  *(uint32_t *)(pArg1 + 112) = 0;
  *(uint32_t *)(pArg1 + 116) = 0;
  sub_41A590(pArg1 + 120, nArg2, 0);
  sub_41A590(pArg1 + 134, v3, 0);
  sub_41A590(pArg1 + 148, v4, 0);
  *(uint32_t *)(pArg1 + 192) = 0;
  *(uint32_t *)(pArg1 + 196) = 0;
  *(uint32_t *)(pArg1 + 200) = 0;
  *(uint32_t *)(pArg1 + 204) = 0;
  sub_699070(pArg1 + 208, 2u);
  *(uint32_t *)(pArg1 + 240) = 0;
  *(uint32_t *)(pArg1 + 236) = 0;
  *(uint32_t *)(pArg1 + 244) = 0;
  v15 = (uint32_t *)(pArg1 + 376);
  v5 = (uint32_t *)(pArg1 + 312);
  v16 = pArg1 + 256;
  for ( i = 2; i != 0; --i )
  {
    *(v5 - 16) = 0;
    sub_699070(v16, 1u);
    *v5 = 0;
    *v15 = 0;
    v15[1] = 0;
    v15[2] = 0;
    v15 += 3;
    v5[22] = 0;
    v5[38] = 0;
    ++v5;
    v16 += 28;
  }
  *(uint32_t *)(pArg1 + 556) = 0;
  *(uint32_t *)(pArg1 + 588) = 0;
  *(uint32_t *)(pArg1 + 1168) = 0;
  *(uint32_t *)(pArg1 + 1172) = 0;
  *(uint32_t *)(pArg1 + 1176) = 0;
  *(uint32_t *)(pArg1 + 1180) = -1;
  *(uint32_t *)(pArg1 + 1184) = -1;
  *(uint32_t *)(pArg1 + 1188) = -1;
  *(uint32_t *)(pArg1 + 1192) = 0;
  sub_699070(pArg1 + 1196, 2u);
  *(uint32_t *)(pArg1 + 1224) = 0;
  *(uint32_t *)(pArg1 + 1228) = 0;
  *(uint32_t *)(pArg1 + 1240) = 0;
  *(uint32_t *)(pArg1 + 1236) = 0;
  *(uint32_t *)(pArg1 + 1244) = 0;
  *(uint32_t *)(pArg1 + 1248) = 0;
  *(uint32_t *)(pArg1 + 840) = -1;
  *(uint32_t *)(pArg1 + 932) = 0;
  *(uint32_t *)(pArg1 + 728) = 0;
  *(uint32_t *)(pArg1 + 724) = 0;
  *(uint8_t *)(pArg1 + 721) = 0;
  *(uint8_t *)(pArg1 + 677) = 0;
  *(uint8_t *)(pArg1 + 678) = 0;
  *(uint32_t *)(pArg1 + 832) = 0;
  *(uint32_t *)(pArg1 + 828) = 0;
  *(uint8_t *)(pArg1 + 824) = 0;
  *(uint8_t *)(pArg1 + 809) = 0;
  *(uint8_t *)(pArg1 + 810) = 0;
  *(uint32_t *)(pArg1 + 836) = 0;
  v6 = 0;
  v7 = (uint8_t *)(pArg1 + 950);
  do
  {
    *(v7 - 1) = 0;
    *v7 = 0;
    *(uint8_t *)(pArg1 + v6++ + 1160) = 0;
    v7 += 28;
  }
  while ( v6 < 8 );
  *(uint32_t *)(pArg1 + 900) = 0;
  *(uint8_t *)(pArg1 + 720) = 0;
  *(uint32_t *)(pArg1 + 592) = 0;
  *(uint8_t *)(pArg1 + 609) = 0;
  *(uint8_t *)(pArg1 + 610) = 0;
  *(uint32_t *)(pArg1 + 624) = 0;
  *(uint32_t *)(pArg1 + 628) = 0;
  *(uint8_t *)(pArg1 + 645) = 0;
  *(uint8_t *)(pArg1 + 646) = 0;
  *(uint32_t *)(pArg1 + 660) = 0;
  *(uint32_t *)(pArg1 + 1252) = 8;
  *(uint32_t *)(pArg1 + 1316) = 0;
  *(uint32_t *)(pArg1 + 1320) = 0;
  *(uint32_t *)(pArg1 + 1324) = 0;
  *(uint32_t *)(pArg1 + 788) = 0;
  *(uint32_t *)(pArg1 + 792) = 0;
  *(uint8_t *)(pArg1 + 773) = 0;
  *(uint8_t *)(pArg1 + 774) = 0;
  *(uint32_t *)(pArg1 + 752) = 0;
  *(uint32_t *)(pArg1 + 1356) = 1065353216;
  *(uint32_t *)(pArg1 + 1360) = 1065353216;
  *(uint32_t *)(pArg1 + 1364) = 1065353216;
  sub_699070(pArg1 + 164, 3u);
  sub_699070(pArg1 + 56, 3u);
  v8 = pArg1 + 320;
  for ( j = 2; j != 0; --j )
  {
    sub_699070(v8, 3u);
    v8 += 28;
  }
  v9 = pArg1 + 408;
  for ( k = 2; k != 0; --k )
  {
    sub_699070(v9, 3u);
    v9 += 28;
  }
  sub_699070(pArg1 + 472, 3u);
  sub_699070(pArg1 + 500, 3u);
  sub_699070(pArg1 + 528, 3u);
  sub_699070(pArg1 + 560, 3u);
  sub_699070(pArg1 + 596, 3u);
  sub_699070(pArg1 + 632, 3u);
  sub_699070(pArg1 + 664, 3u);
  sub_699070(pArg1 + 692, 3u);
  sub_699070(pArg1 + 760, 3u);
  sub_699070(pArg1 + 796, 3u);
  sub_699070(pArg1 + 844, 3u);
  sub_699070(pArg1 + 872, 3u);
  sub_699070(pArg1 + 904, 3u);
  v10 = pArg1 + 936;
  for ( m = 8; m != 0; --m )
  {
    sub_699070(v10, 3u);
    v10 += 28;
  }
  sub_699070(pArg1 + 1260, 3u);
  sub_699070(pArg1 + 1288, 3u);
  sub_699070(pArg1 + 1328, 3u);
}


// ------------------------------------------------------------
// 0x423FD0 sub_423FD0
// ------------------------------------------------------------
int /*thiscall*/ sub_423FD0(uint32_t *this)
{
  int fld_e11; // eax
  int fld_e26; // eax
  void (/*thiscall*/ ***fld_e9)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e147)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e156)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e165)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e197)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e198)(uint32_t, int); // ecx
  uint32_t *pThis_5E; // esi
  int j; // ebx
  int result; // eax
  int (/*thiscall*/ ***fld_e209)(uint32_t, int); // ecx
  int i; // [esp+8h] [ebp-8h]
  uint32_t *pThis_74; // [esp+Ch] [ebp-4h]

  fld_e11 = *(this + 11);
  if ( fld_e11 != 0 )
    *(uint32_t *)(fld_e11 + 392) = 0;
  fld_e26 = *(this + 26);
  if ( fld_e26 != 0 )
    *(uint32_t *)(fld_e26 + 132) = 0;
  fld_e9 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  *(this + 27) = 0;
  if ( fld_e9 != nullptr )
    (**fld_e9)(fld_e9, 1);
  fld_e10 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  *(this + 9) = 0;
  if ( fld_e10 != nullptr )
    (**fld_e10)(fld_e10, 1);
  fld_e147 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 147);
  *(this + 10) = 0;
  if ( fld_e147 != nullptr )
    (**fld_e147)(fld_e147, 1);
  fld_e156 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 156);
  *(this + 147) = 0;
  if ( fld_e156 != nullptr )
    (**fld_e156)(fld_e156, 1);
  fld_e165 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 165);
  *(this + 156) = 0;
  if ( fld_e165 != nullptr )
    (**fld_e165)(fld_e165, 1);
  fld_e197 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 197);
  *(this + 165) = 0;
  if ( fld_e197 != nullptr )
    (**fld_e197)(fld_e197, 1);
  fld_e198 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 198);
  *(this + 197) = 0;
  if ( fld_e198 != nullptr )
    (**fld_e198)(fld_e198, 1);
  *(this + 198) = 0;
  pThis_74 = this + 116;
  pThis_5E = this + 94;
  for ( i = 2; i != 0; --i )
  {
    for ( j = 3; j != 0; --j )
    {
      if ( *pThis_5E != 0 )
        (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_5E)(*pThis_5E, 1);
      *pThis_5E++ = 0;
    }
    if ( *pThis_74 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_74)(*pThis_74, 1);
    *pThis_74 = 0;
    result = (int)++pThis_74;
  }
  fld_e209 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 209);
  if ( fld_e209 != nullptr )
    result = (**fld_e209)(fld_e209, 1);
  *(this + 209) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x424100 sub_424100
// ------------------------------------------------------------
int /*thiscall*/ sub_424100(uint32_t *this, int pArg2)
{
  int result; // eax

  result = pArg2;
  *(this + 26) = pArg2;
  if ( pArg2 != 0 )
    *(uint32_t *)(pArg2 + 132) = this;
  return result;
}



// ------------------------------------------------------------
// 0x424120 sub_424120
// ------------------------------------------------------------
int /*thiscall*/ sub_424120(uint32_t *this, int nArg2, int nArg3)
{
  uint32_t *pThis_34; // ecx
  int result; // eax

  pThis_34 = this + 52;
  *(this + 50) = nArg2;
  *(this + 51) = nArg3;
  *((uint8_t *)pThis_34 + 13) = 0;
  *((uint8_t *)pThis_34 + 14) = 0;
  result = sub_698F90(0, 0);
  if ( nArg2 == 0 )
  {
    *(this + 59) = 0;
    *(this + 60) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x424170 sub_424170
// ------------------------------------------------------------
int /*thiscall*/ sub_424170(uint32_t *this)
{
  int result; // eax
  int v3; // eax

  result = *(uint32_t *)(dword_8F7A24 + 12);
  if ( result == 3 || result == 4 || result == 6 )
  {
    if ( dword_8F7C04 == 0 || (result = *((uint32_t *)dword_8F8528 + 1)) != 0 )
    {
      *(this + 61) = 0;
    }
    else
    {
      v3 = (*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 128))() / 5;
      if ( v3 > 35 )
        v3 = 35;
      result = v3 - 35;
      *(this + 61) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4241E0 sub_4241E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4241E0(int this)
{
  int fld_C8; // eax
  int v3; // eax
  int v4; // ebx
  int v5; // edi

  fld_C8 = *(uint32_t *)(this + 200);
  if ( fld_C8 != 0 && *(uint32_t *)(this + 1224) == 0 )
  {
    v3 = 2 * fld_C8;
    v4 = v3 + 1;
    v5 = v3 / 2;
    *(uint32_t *)(this + 236) = rand() % (v3 + 1) - v3 / 2;
    *(uint32_t *)(this + 240) = rand() % v4 - v5;
    fld_C8 = sub_699000(this + 208);
    if ( fld_C8 >= *(uint32_t *)(this + 204) )
    {
      *(uint32_t *)(this + 200) = 0;
      *(uint32_t *)(this + 204) = 0;
      *(uint8_t *)(this + 221) = 0;
      *(uint8_t *)(this + 222) = 0;
      LOBYTE(fld_C8) = sub_698F90(this + 208, 0, 0);
      *(uint32_t *)(this + 236) = 0;
      *(uint32_t *)(this + 240) = 0;
    }
  }
  return fld_C8;
}



// ------------------------------------------------------------
// 0x424270 sub_424270
// ------------------------------------------------------------
int /*thiscall*/ sub_424270(int this, int nArg2, int nArg3)
{
  int v5; // eax
  int v7; // [esp-4h] [ebp-10h]

  v7 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 36))(nArg2) + 8);
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);
  *(uint32_t *)(this + 732) = sub_45E490(v5, v7) - 50;
  *(uint32_t *)(this + 736) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2) - 32;
  *(uint32_t *)(this + 740) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 128))(nArg2);
  *(uint32_t *)(this + 752) = nArg3;
  *(uint8_t *)(this + 773) = 0;
  *(uint8_t *)(this + 774) = 0;
  sub_698F90(this + 760, 1500, 0);
  *(uint32_t *)(this + 744) = 0;
  *(uint32_t *)(this + 748) = 1065353216;
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);
}



// ------------------------------------------------------------
// 0x424310 sub_424310
// ------------------------------------------------------------
int /*thiscall*/ sub_424310(uint32_t *this, uint8_t *pArg2)
{
  int v2; // ebx
  uint8_t *pArg22; // esi
  int v4; // eax
  int v5; // eax
  int pObj5; // edi
  int i; // ebx
  int v8; // eax
  int pObj; // esi
  int v10; // eax
  int v12; // eax
  int v13; // esi
  int pObj3; // ecx
  int pObj4; // edi
  int v16; // edi
  int v17; // eax
  int pObj2; // ecx
  int v19; // [esp+Ch] [ebp-8h]
  int v20; // [esp+10h] [ebp-4h]
  int v21; // [esp+1Ch] [ebp+8h]

  v2 = 0;
  if ( *(this + 26) == 0 )
    return 0;
  pArg22 = pArg2;
  if ( pArg2 == nullptr )
    return 0;
  v4 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v4 == 3 )
  {
    if ( (uint8_t)sub_45E680(pArg2) == 0 )
    {
      v5 = sub_423B10(dword_8F850C);
      if ( v5 == 0 || (pArg22 = *(uint8_t **)(v5 + 196)) == nullptr || (uint8_t)sub_45E680(*(uint32_t *)(v5 + 196)) == 0 )
      {
        v21 = 0;
        pObj5 = 0;
        for ( i = 16; i < 32; i += 4 )
        {
          v8 = *(uint32_t *)(i + dword_8F850C);
          if ( v8 != 0 )
          {
            pObj = *(uint32_t *)(v8 + 196);
            if ( pObj != 0 && (uint8_t)sub_45E680(*(uint32_t *)(v8 + 196)) != 0 )
            {
              v10 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1032))(pObj) + 48);
              if ( pObj5 == 0 || v10 > v21 )
              {
                pObj5 = pObj;
                v21 = v10;
              }
            }
          }
        }
        return pObj5;
      }
    }
    return (int)pArg22;
  }
  if ( v4 != 4 && v4 != 6 )
  {
    if ( v4 == 1 )
      return dword_8F7C08;
    return 0;
  }
  if ( dword_8F7C04 == 0 )
    return 0;
  if ( v4 == 4 && dword_99FEC0 != 0 )
  {
    v20 = dword_99FEC0 + 4;
  }
  else
  {
    if ( v4 != 6 || dword_99FF08 == 0 )
      return 0;
    v20 = dword_99FF08 + 4;
  }
  if ( v20 == 0 )
    return 0;
  if ( *(uint8_t *)(dword_8F7C04 + 8052) != 0 || pArg2[8052] != 0 )
    return *(this + 13);
  if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg2 + 1196))(pArg2) == 0 )
    return (int)pArg22;
  while ( 1 )
  {
    v12 = sub_48F660(v2);
    v13 = v12;
    if ( v12 != 0 )
    {
      pObj3 = *(uint32_t *)(v12 + 196);
      if ( pObj3 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 1196))(pObj3) == 0 )
      {
        pObj4 = *(uint32_t *)(v13 + 196);
        v19 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg2 + 376))(pArg2);
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 376))(pObj4) == v19 )
          break;
      }
    }
    if ( ++v2 >= 8 )
    {
      v16 = 0;
      while ( 1 )
      {
        v17 = sub_48F660(v16);
        v13 = v17;
        if ( v17 != 0 )
        {
          pObj2 = *(uint32_t *)(v17 + 196);
          if ( pObj2 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 1196))(pObj2) == 0 )
            break;
        }
        if ( ++v16 >= 8 )
          return 0;
      }
      return *(uint32_t *)(v13 + 196);
    }
  }
  return *(uint32_t *)(v13 + 196);
}


// ------------------------------------------------------------
// 0x424530 sub_424530
// ------------------------------------------------------------
// 【屏幕淡入淡出】sub_48B740(2) 遮罩层 + dword_77F6DC 全局透明度插值（被连击宿主
//   0x428050 作命中脉冲调用）。
char /*thiscall*/ sub_424530(int this, float fArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7, char pszArg8)
{
  int fld_4A8; // eax
  double v10; // st7
  long double v11; // st7

  fld_4A8 = sub_48B740(2);
  if ( fld_4A8 != 0 )
  {
    if ( pszArg8 != 0 && (fld_4A8 = *(uint32_t *)(this + 1192)) != 0 )
    {
      if ( fld_4A8 == 1 )
      {
        fld_4A8 = *(uint32_t *)(this + 1176);
        if ( fld_4A8 <= nArg4 )
          fld_4A8 = nArg4;
        *(uint32_t *)(this + 1176) = fld_4A8;
      }
      else if ( fld_4A8 == 2 )
      {
        fld_4A8 = sub_4238E0(this + 1196);
        if ( nArg4 > fld_4A8 )
        {
          *(uint32_t *)(this + 1176) = nArg4;
          *(uint8_t *)(this + 1209) = 0;
          *(uint8_t *)(this + 1210) = 0;
          LOBYTE(fld_4A8) = sub_698F90(this + 1196, *(uint32_t *)(this + 1176), 0);
        }
      }
    }
    else
    {
      v10 = *(float *)&dword_77F6DC;
      *(float *)(this + 1168) = fArg2;
      *(uint32_t *)(this + 1172) = nArg3;
      *(uint32_t *)(this + 1176) = nArg4;
      if ( pszArg8 != 0 )
        v11 = fabs(v10 - 1.0);
      else
        v11 = fabs(fArg2 - v10);
      *(uint32_t *)(this + 1192) = 2 * (pszArg8 == 0) + 1;
      *(uint8_t *)(this + 1209) = 0;
      *(uint8_t *)(this + 1210) = 0;
      sub_698F90(this + 1196, *(uint32_t *)(this + 1172), (uint64_t)((double)nArg3 * v11 / (fArg2 - 1.0)));
      *(uint32_t *)(this + 1180) = nArg5;
      *(uint32_t *)(this + 1184) = nArg6;
      *(uint32_t *)(this + 1188) = nArg7;
      LOBYTE(fld_4A8) = nArg5;
    }
  }
  else
  {
    *(uint32_t *)(this + 1192) = 0;
    dword_8F7BD0 = 0;
    dword_8F7BD4 = 0;
    dword_77F6DC = 1065353216;
  }
  return fld_4A8;
}



// ============================================================
// §8 HUD 绘制基元（0x424680-0x425940）
//   0x424760 = 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）——播报层横幅/三轴动画共用出口
// ============================================================
// ------------------------------------------------------------
// 0x424680 sub_424680
// ------------------------------------------------------------
int /*cdecl*/ sub_424680(int *pDwArg1, int *pDwArg2, float fArg3, float fArg4)
{
  uint64_t v4; // rax
  double v5; // st7
  double v6; // st6
  float v8; // [esp+14h] [ebp+10h]

  if ( fArg3 == 0.0 && fArg4 == 0.0 )
  {
    *pDwArg1 = dword_8F7BD0 + (uint64_t)((double)(*pDwArg1 - dword_8F7BD0) * *(float *)&dword_77F6DC);
    LODWORD(v4) = dword_8F7BD4 + (uint64_t)((double)(*pDwArg2 - dword_8F7BD4) * *(float *)&dword_77F6DC);
    *pDwArg2 = v4;
  }
  else
  {
    v5 = (double)*pDwArg1;
    v6 = fArg3 + v5;
    v8 = ((double)*pDwArg2 + fArg4 - (double)dword_8F7BD4) * *(float *)&dword_77F6DC + (double)dword_8F7BD4 - ((double)*pDwArg2 + fArg4);
    *pDwArg1 = (uint64_t)((v6 - (double)dword_8F7BD0) * *(float *)&dword_77F6DC + (double)dword_8F7BD0 - v6 + v5);
    v4 = (uint64_t)((double)*pDwArg2 + v8);
    *pDwArg2 = v4;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x424760 sub_424760
// ------------------------------------------------------------
// 【HUD 图像绘制基元】(顶点缓冲 dword_79C0B0, x, y, 图像槽, 缩放, 1065353216=1.0f,
//   ARGB) —— 0x426200 横幅 tick 与三轴动画器的共用出口。
void /*cdecl*/ sub_424760(int nArg1, int nArg2, int nArg3, int pArg4, float fArg5, int nArg6, float fArg7, int nArg8, float fArg9, float fArg10)
{
  bool v10; // bl
  double v11; // st7
  bool v12; // c0
  float fArg102; // esi
  float fArg92; // edi
  double v15; // st7
  bool v16; // c0
  float v17; // [esp+0h] [ebp-30h]
  float v18; // [esp+4h] [ebp-2Ch]
  float v19; // [esp+28h] [ebp-8h]
  float v20; // [esp+28h] [ebp-8h]
  float v21; // [esp+28h] [ebp-8h]
  float v22; // [esp+28h] [ebp-8h]
  float v23; // [esp+2Ch] [ebp-4h]
  float v24; // [esp+2Ch] [ebp-4h]

  v10 = *(uint32_t *)(dword_8F7A24 + 12) == 1 || fArg7 == 0.0;
  if ( *(float *)&dword_77F6DC == 1.0 )
  {
    if ( !v10 )
      goto LABEL_13;
    v19 = (double)*(int *)(pArg4 + 28) - fArg9;
    v23 = (float)nArg2;
    v11 = v19 * fArg5 + v23 + fArg9;
    v20 = ((double)*(unsigned int *)(pArg4 + 20) + v19) * fArg5 + v23 + fArg9;
    if ( fArg5 < 0.0 )
    {
      if ( v20 >= 640.0 )
        return;
      v12 = v11 < 0.0;
    }
    else
    {
      if ( v11 >= 640.0 )
        return;
      v12 = v20 < 0.0;
    }
    if ( !v12 )
    {
LABEL_13:
      if ( pArg4 != 0 )
        (*(void (/*stdcall*/ **)(int, int, int, uint32_t, int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)pArg4 + 156))(
          nArg2,
          nArg3,
          nArg1,
          LODWORD(fArg5),
          nArg6,
          LODWORD(fArg7),
          nArg8,
          LODWORD(fArg9),
          LODWORD(fArg10));
    }
  }
  else
  {
    fArg102 = fArg10;
    fArg92 = fArg9;
    sub_424680((int)&nArg2, (int)&nArg3, fArg9, fArg10);
    if ( !v10 )
      goto LABEL_22;
    v21 = (double)*(int *)(pArg4 + 28) - fArg9;
    v24 = (float)nArg2;
    v15 = v21 * *(float *)&dword_77F6DC * fArg5 + v24 + fArg9;
    v22 = ((double)*(unsigned int *)(pArg4 + 20) + v21) * *(float *)&dword_77F6DC * fArg5 + v24 + fArg9;
    if ( fArg5 < 0.0 )
    {
      if ( v22 >= 640.0 )
        return;
      v16 = v15 < 0.0;
    }
    else
    {
      if ( v15 >= 640.0 )
        return;
      v16 = v22 < 0.0;
    }
    if ( !v16 )
    {
LABEL_22:
      if ( pArg4 != 0 )
      {
        v18 = *(float *)&dword_77F6DC * *(float *)&nArg6;
        v17 = *(float *)&dword_77F6DC * fArg5;
        (*(void (/*stdcall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, int, float, float))(*(uint32_t *)pArg4 + 156))(
          nArg2,
          nArg3,
          nArg1,
          LODWORD(v17),
          LODWORD(v18),
          LODWORD(fArg7),
          nArg8,
          COERCE_FLOAT(LODWORD(fArg92)),
          COERCE_FLOAT(LODWORD(fArg102)));
      }
    }
  }
}



// ------------------------------------------------------------
// 0x424980 sub_424980
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_424980(uint32_t *pArg1, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int nArg43; // eax
  int nArg53; // ecx
  bool v7; // bl
  int v8; // esi
  int v9; // edi
  int nArg22; // edx
  int nArg32; // ecx
  int nArg42; // esi
  int nArg52; // edi
  bool v15; // [esp+Bh] [ebp-1h]

  if ( *(float *)&dword_77F6DC == 1.0 )
  {
    nArg52 = nArg5;
    nArg42 = nArg4;
    nArg32 = nArg3;
    nArg22 = nArg2;
  }
  else
  {
    nArg43 = nArg4;
    nArg53 = nArg5;
    v7 = nArg2 == 0;
    v15 = nArg3 == 0;
    HIBYTE(nArg4) = nArg4 == 640;
    HIBYTE(nArg5) = nArg5 == 480;
    v8 = nArg43 - nArg2;
    v9 = nArg53 - nArg3;
    sub_424680(&nArg2, &nArg3, 0.0, 0.0);
    nArg22 = nArg2;
    nArg32 = nArg3;
    nArg42 = nArg2 + v8;
    nArg52 = nArg3 + v9;
    if ( v7 )
      nArg22 = 0;
    if ( v15 )
      nArg32 = 0;
    if ( HIBYTE(nArg4) != 0 )
      nArg42 = 640;
    if ( HIBYTE(nArg5) != 0 )
      nArg52 = 480;
  }
  pArg1[15] = nArg52;
  pArg1[14] = nArg42;
  pArg1[12] = nArg22;
  pArg1[13] = nArg32;
  return pArg1;
}



// ------------------------------------------------------------
// 0x424A40 sub_424A40
// ------------------------------------------------------------
int /*thiscall*/ sub_424A40(uint32_t *this, int nArg2)
{
  int result; // eax

  result = nArg2;
  *(this + 13) = nArg2;
  if ( *(this + 11) != 0 && nArg2 != 0 )
    return sub_48C500(nArg2);
  return result;
}



// ------------------------------------------------------------
// 0x424A60 sub_424A60
// ------------------------------------------------------------
void /*thiscall*/ sub_424A60(uint32_t *this)
{
  int pThis_13B; // eax

  if ( *(this + 314) == 2 )
  {
    pThis_13B = sub_699000((int)(this + 315));
    sub_69A110(285, 220, 5 - pThis_13B / 1000, -1);
  }
}



// ------------------------------------------------------------
// 0x424AB0 sub_424AB0
// ------------------------------------------------------------
int /*thiscall*/ sub_424AB0(int this, int nArg2, int nArg3)
{
  uint64_t fld_54C; // rax
  DWORD TickCount; // eax
  double v6; // st7

  LODWORD(fld_54C) = *(uint32_t *)(this + 1236);
  if ( (uint32_t)fld_54C == 0 )
  {
    LODWORD(fld_54C) = GetTickCount() - *(uint32_t *)(this + 1240);
    if ( (unsigned int)fld_54C >= 0x3E8 )
    {
      TickCount = GetTickCount();
      v6 = (double)nArg3;
      *(uint32_t *)(this + 1236) = TickCount;
      *(uint32_t *)(this + 1240) = TickCount;
      *(float *)(this + 1364) = 0.0099999998 * v6;
      *(uint32_t *)(this + 1244) = nArg2 + TickCount;
      *(float *)(this + 1360) = 0.0099999998 * v6;
      *(uint32_t *)(this + 1248) = nArg3;
      dword_79D0C4 = (uint64_t)(v6 * *(float *)(this + 1356));
      fld_54C = (uint64_t)(v6 * *(float *)(this + 1356));
      dword_79D0C8 = fld_54C;
    }
  }
  return fld_54C;
}



// ------------------------------------------------------------
// 0x424B40 sub_424B40
// ------------------------------------------------------------
int /*thiscall*/ sub_424B40(int this)
{
  uint64_t fld_54C2; // rax
  double fld_54C; // st7

  LODWORD(fld_54C2) = *(uint32_t *)(this + 1236);
  if ( (uint32_t)fld_54C2 != 0 )
  {
    LODWORD(fld_54C2) = GetTickCount() - *(uint32_t *)(this + 1236);
    if ( (unsigned int)fld_54C2 >= 0xFA )
    {
      fld_54C = *(float *)(this + 1356) * 100.0;
      *(uint32_t *)(this + 1236) = 0;
      *(uint32_t *)(this + 1364) = 1065353216;
      *(uint32_t *)(this + 1360) = 1065353216;
      dword_79D0C4 = (uint64_t)fld_54C;
      fld_54C2 = (uint64_t)(*(float *)(this + 1356) * 100.0);
      dword_79D0C8 = fld_54C2;
    }
  }
  return fld_54C2;
}



// ------------------------------------------------------------
// 0x424BB0 sub_424BB0
// ------------------------------------------------------------
char /*thiscall*/ sub_424BB0(int this, int nArg2, int nArg3, char pszArg4)
{
  DWORD TickCount; // eax
  double fld_54C; // st7
  char result; // al

  TickCount = GetTickCount();
  fld_54C = *(float *)(this + 1356) * 5.0;
  *(uint32_t *)(this + 1224) = TickCount;
  *(uint32_t *)(this + 1228) = nArg2 + TickCount;
  *(uint32_t *)(this + 1232) = nArg3;
  *(uint32_t *)(this + 1364) = 1028443341;
  *(uint32_t *)(this + 1360) = 1028443341;
  dword_79D0C4 = (uint64_t)fld_54C;
  dword_79D0C8 = (uint64_t)(*(float *)(this + 1356) * 5.0);
  result = pszArg4;
  if ( pszArg4 != 0 )
    return sub_424530(*(uint32_t *)(*(uint32_t *)(this + 104) + 132), 1.2, 100, 150, -1, -1, -1, 1);
  return result;
}



// ------------------------------------------------------------
// 0x424C50 sub_424C50
// ------------------------------------------------------------
int /*thiscall*/ sub_424C50(int this)
{
  uint64_t fld_54C2; // rax
  double fld_4D02; // st7
  double fld_4D0; // st7
  double fld_54C; // st7

  LODWORD(fld_54C2) = *(uint32_t *)(this + 1224);
  if ( (uint32_t)fld_54C2 != 0 )
  {
    LODWORD(fld_54C2) = GetTickCount() - *(uint32_t *)(this + 1224);
    if ( (unsigned int)fld_54C2 >= 0xBB8 )
    {
      if ( (unsigned int)fld_54C2 >= 0x157C )
      {
        if ( (unsigned int)fld_54C2 >= 0x15E0 )
        {
          fld_54C = *(float *)(this + 1356) * 100.0;
          *(uint32_t *)(this + 1224) = 0;
          *(uint32_t *)(this + 1364) = 1065353216;
          *(uint32_t *)(this + 1360) = 1065353216;
          dword_79D0C4 = (uint64_t)fld_54C;
          fld_54C2 = (uint64_t)(*(float *)(this + 1356) * 100.0);
        }
        else
        {
          fld_4D0 = (double)(int)sub_423A80(*(uint32_t *)(this + 1232), 100, fld_54C2, 5600);
          *(float *)(this + 1364) = 0.0099999998 * fld_4D0;
          *(float *)(this + 1360) = 0.0099999998 * fld_4D0;
          dword_79D0C4 = (uint64_t)(fld_4D0 * *(float *)(this + 1356));
          fld_54C2 = (uint64_t)(fld_4D0 * *(float *)(this + 1356));
        }
        dword_79D0C8 = fld_54C2;
      }
      else
      {
        fld_4D02 = (double)*(int *)(this + 1232);
        *(float *)(this + 1364) = 0.0099999998 * fld_4D02;
        *(float *)(this + 1360) = 0.0099999998 * fld_4D02;
        dword_79D0C4 = (uint64_t)(fld_4D02 * *(float *)(this + 1356));
        fld_54C2 = (uint64_t)((double)*(int *)(this + 1232) * *(float *)(this + 1356));
        dword_79D0C8 = fld_54C2;
      }
    }
  }
  return fld_54C2;
}



// ------------------------------------------------------------
// 0x424D80 sub_424D80
// ------------------------------------------------------------
// 【评价槽复位】this+936 + 28*a2 槽：+13/+14 标志清零 + 500ms 钟；this+1160+a2 置位。
//   被 0x426820 case 2/4/5 调用（28 字节节奏与 case0/1 清 +949/950、+977/978 一致）。
char /*thiscall*/ sub_424D80(uint8_t *this, int pArg2)
{
  int pThis_1C; // ecx
  char result; // al

  pThis_1C = (int)(this + 28 * pArg2 + 936);
  *(uint8_t *)(pThis_1C + 13) = 0;
  *(uint8_t *)(pThis_1C + 14) = 0;
  result = sub_698F90(pThis_1C, 500, 0);
  *(this + pArg2 + 1160) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x424DC0 sub_424DC0
// ------------------------------------------------------------
int /*thiscall*/ sub_424DC0(uint32_t *this)
{
  int fld_e295; // eax
  int fld_e13; // esi
  int v4; // eax
  int v5; // [esp-Ch] [ebp-Ch]

  fld_e295 = *(this + 295);
  if ( fld_e295 != -1 )
    return sub_45E490(fld_e295, 1);
  fld_e13 = *(this + 13);
  if ( fld_e13 == 0 )
    return 320;
  v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 36))(fld_e13) + 8);
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 120))(fld_e13);
  return sub_45E490(v4, v5);
}



// ------------------------------------------------------------
// 0x424E10 sub_424E10
// ------------------------------------------------------------
int /*thiscall*/ sub_424E10(int *this)
{
  int fld_e296; // edx
  int fld_e297; // eax
  int fld_e13; // esi
  int fld_e132; // edi
  int v6; // eax
  int v7; // eax
  int v8; // [esp-18h] [ebp-18h]
  int v9; // [esp-14h] [ebp-14h]

  fld_e296 = *(this + 296);
  if ( fld_e296 != -1 )
  {
    fld_e297 = *(this + 297);
    if ( fld_e297 != -1 )
      return sub_45E4D0(fld_e296, fld_e297, 1, 1.0);
  }
  fld_e13 = *(this + 13);
  if ( fld_e13 == 0 )
    return 240;
  fld_e132 = *(this + 13);
  v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 36))(fld_e13) + 8);
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 128))(fld_e13);
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 124))(fld_e13);
  v7 = sub_45E4D0(v6, v8, v9, 1.0);
  return v7 - 2 * (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e132 + 192))(fld_e13) / 3;
}



// ------------------------------------------------------------
// 0x424EA0 sub_424EA0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_424EA0(float *this, float fArg2)
{
  uint64_t result; // rax

  *(this + 339) = fArg2;
  dword_79D0CC = (uint64_t)(fArg2 * 100.0);
  dword_79D0C4 = (uint64_t)(*(this + 340) * *(this + 339) * 100.0);
  result = (uint64_t)(*(this + 341) * *(this + 339) * 100.0);
  dword_79D0C8 = result;
  return result;
}



// ------------------------------------------------------------
// 0x424F00 sub_424F00
// ------------------------------------------------------------
int /*thiscall*/ sub_424F00(int this)
{
  int fld_4A0; // ebx
  int fld_4A4; // edi
  int result; // eax
  long double v5; // st7
  int fld_49C; // [esp+Ch] [ebp-10h]
  int fld_498; // [esp+10h] [ebp-Ch]
  int fld_494; // [esp+14h] [ebp-8h]
  float fld_490; // [esp+18h] [ebp-4h]

  fld_4A0 = *(uint32_t *)(this + 1184);
  fld_4A4 = *(uint32_t *)(this + 1188);
  fld_49C = *(uint32_t *)(this + 1180);
  fld_498 = *(uint32_t *)(this + 1176);
  fld_494 = *(uint32_t *)(this + 1172);
  fld_490 = *(float *)(this + 1168);
  result = sub_48B740(2);
  if ( result != 0 )
  {
    v5 = fld_490 - *(float *)&dword_77F6DC;
    *(float *)(this + 1168) = fld_490;
    *(uint32_t *)(this + 1172) = fld_494;
    *(uint32_t *)(this + 1176) = fld_498;
    *(uint32_t *)(this + 1192) = 3;
    *(uint8_t *)(this + 1209) = 0;
    *(uint8_t *)(this + 1210) = 0;
    sub_698F90(this + 1196, *(uint32_t *)(this + 1172), (uint64_t)(fabs(v5) * (double)fld_494 / (fld_490 - 1.0)));
    *(uint32_t *)(this + 1188) = fld_4A4;
    *(uint32_t *)(this + 1184) = fld_4A0;
    *(uint32_t *)(this + 1180) = fld_49C;
    return fld_49C;
  }
  else
  {
    *(uint32_t *)(this + 1192) = 0;
    dword_77F6DC = 1065353216;
    dword_8F7BD0 = 0;
    dword_8F7BD4 = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x424FF0 sub_424FF0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_424FF0(uint32_t *this)
{
  int fld_e91; // edx
  int fld_e95; // edx
  unsigned int fld_e96; // eax
  int fld_e912; // edx

  fld_e91 = *(this + 91);
  if ( fld_e91 == 0 || (*(this + 92) - fld_e91) >> 5 == 0 )
    return 0;
  fld_e95 = *(this + 95);
  if ( fld_e95 != 0 )
    fld_e96 = (*(this + 96) - fld_e95) >> 5;
  else
    fld_e96 = 0;
  fld_e912 = *(this + 91);
  if ( fld_e912 != 0 )
    return fld_e96 / ((*(this + 92) - fld_e912) >> 5);
  else
    return fld_e96 / 0;
}



// ------------------------------------------------------------
// 0x425050 sub_425050
// ------------------------------------------------------------
int /*thiscall*/ sub_425050(uint32_t *this)
{
  int fld_e91; // edx

  fld_e91 = *(this + 91);
  if ( fld_e91 != 0 )
    return 224 * ((*(this + 92) - fld_e91) >> 5);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x425080 sub_425080
// ------------------------------------------------------------
int /*thiscall*/ sub_425080(uint32_t *this)
{
  int fld_e91; // edx
  int fld_e92; // eax
  int fld_e912; // edx

  fld_e91 = *(this + 91);
  if ( fld_e91 != 0 )
    fld_e92 = (*(this + 92) - fld_e91) >> 5;
  else
    fld_e92 = 0;
  if ( 224 * fld_e92 - 640 <= 0 )
    return 0;
  fld_e912 = *(this + 91);
  if ( fld_e912 != 0 )
    return 224 * ((*(this + 92) - fld_e912) >> 5) - 640;
  else
    return -640;
}



// ------------------------------------------------------------
// 0x4250E0 sub_4250E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4250E0(uint32_t *this)
{
  int fld_e2; // edx

  fld_e2 = *(this + 2);
  if ( fld_e2 != 0 )
    return (*(this + 3) - fld_e2) >> 2;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x425100 sub_425100
// ------------------------------------------------------------
int /*thiscall*/ sub_425100(uint32_t *this)
{
  int fld_e30; // edx

  fld_e30 = *(this + 30);
  if ( fld_e30 != 0 )
    return (*(this + 31) - fld_e30) >> 2;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x425120 sub_425120
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_425120(uint32_t *this)
{
  *this = &vftbl_CNRDParticleCreater;
  sub_423A20((int)(this + 1));
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  *(this + 32) = 0;
  *(this + 33) = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
  *(this + 36) = 0;
  *(this + 37) = 0;
  *(this + 38) = 0;
  *((uint8_t *)this + 156) = 0;
  *(this + 40) = 100;
  *(this + 41) = 100;
  *(this + 42) = 100;
  *((uint8_t *)this + 172) = 1;
  *((uint8_t *)this + 180) = 0;
  *(this + 44) = &vftbl_nengine__CNTimer;
  *(this + 46) = 0;
  *((uint8_t *)this + 188) = 1;
  *((uint8_t *)this + 190) = 0;
  *((uint8_t *)this + 189) = 0;
  *(this + 50) = 0;
  *(this + 49) = 0;
  *(this + 48) = 0;
  sub_4902C0(this);
  sub_490BD0(this);
  return this;
}



// ------------------------------------------------------------
// 0x425210 CNRDParticleCreater__vmt14
// ------------------------------------------------------------
int /*thiscall*/ CNRDParticleCreater__vmt14(uint32_t *this, int nArg2)
{
  return sub_490460(nArg2, (int)(this + 1), this + 26);
}



// ------------------------------------------------------------
// 0x425230 CNRDParticleCreater__vmt20
// ------------------------------------------------------------
void /*thiscall*/ CNRDParticleCreater__vmt20(int this, const void *pArg2)
{
  qmemcpy((void *)(this + 104), pArg2, 0x48u);
}



// ------------------------------------------------------------
// 0x425260 CNRDParticleCreater__vmt28
// ------------------------------------------------------------
int /*thiscall*/ CNRDParticleCreater__vmt28(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  *(this + 1) = nArg2;
  *(this + 2) = nArg3;
  *(this + 3) = nArg4;
  return nArg4;
}



// ------------------------------------------------------------
// 0x4252A0 CNRDParticleCreater__vmt40
// ------------------------------------------------------------
char /*thiscall*/ CNRDParticleCreater__vmt40(uint8_t *this, char pszArg2)
{
  *(this + 216) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4252B0 CNRDParticleCreater__vmt44
// ------------------------------------------------------------
char /*thiscall*/ CNRDParticleCreater__vmt44(uint8_t *this)
{
  return *(this + 216);
}



// ------------------------------------------------------------
// 0x4252D0 CNRDParticleCreater__vmt54
// ------------------------------------------------------------
int /*thiscall*/ CNRDParticleCreater__vmt54(uint32_t *this, int nArg2)
{
  int fld_e58; // eax

  fld_e58 = *(this + 58);
  if ( fld_e58 == -1 )
    return nArg2;
  else
    return nArg2 * *(this + fld_e58 + 40) / 100;
}



// ------------------------------------------------------------
// 0x425310 CNRDParticleCreater__vmt50
// ------------------------------------------------------------
double /*thiscall*/ CNRDParticleCreater__vmt50(uint32_t *this, float fArg2)
{
  int fld_e58; // eax

  fld_e58 = *(this + 58);
  if ( fld_e58 == -1 )
    return fArg2;
  else
    return (double)(int)*(this + fld_e58 + 40) * fArg2 * 0.0099999998;
}



// ------------------------------------------------------------
// 0x425340 CNRDParticleCreater__vmt58
// ------------------------------------------------------------
void /*thiscall*/ CNRDParticleCreater__vmt58(void *this, unsigned int uArg2)
{
  sub_699070((int)this + 176, uArg2);
}



// ------------------------------------------------------------
// 0x425350 sub_425350
// ------------------------------------------------------------
void /*thiscall*/ sub_425350(uint32_t *this)
{
  *this = &vftbl_CNRDParticleCreater;
  nullsub_3();
  *(this + 44) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 180) = 0;
}



// ------------------------------------------------------------
// 0x4253B0 CNRDParticleCreater__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDParticleCreater__vmt0(uint32_t *Block, char pszArg2)
{
  sub_425350(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4253E0 sub_4253E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4253E0(int this)
{
  int pThis_D0; // ecx

  pThis_D0 = this + 208;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint8_t *)(pThis_D0 + 13) = 0;
  *(uint8_t *)(pThis_D0 + 14) = 0;
  sub_698F90(pThis_D0, 0, 0);
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  dword_77F6DC = 1065353216;
  dword_8F7BD0 = 0;
  dword_8F7BD4 = 0;
  *(uint32_t *)(this + 84) = -1;
  *(uint32_t *)(this + 88) = -1;
  *(uint32_t *)(this + 92) = -1;
  *(uint32_t *)(this + 96) = -1;
  *(uint32_t *)(this + 100) = 4;
  *(uint32_t *)(this + 1256) = 1;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  return sub_698F90(this + 56, 0, 0);
}



// ------------------------------------------------------------
// 0x425460 sub_425460
// ------------------------------------------------------------
int /*fastcall*/ sub_425460(int pArg1, int nArg2)
{
  int v3; // edx
  int v4; // edx
  int v5; // ecx
  int result; // eax
  int v7; // ecx

  sub_41A590(pArg1 + 120, nArg2, 0);
  sub_41A590(pArg1 + 134, v3, 0);
  sub_41A590(pArg1 + 148, v4, 0);
  *(uint8_t *)(pArg1 + 177) = 0;
  *(uint8_t *)(pArg1 + 178) = 0;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 && *(uint32_t *)(pArg1 + 108) != 0 )
    sub_472B30(1, 0);
  v5 = *(uint32_t *)(dword_8F7A24 + 12);
  result = dword_8F7C04;
  if ( v5 != 4 && v5 != 6 || dword_8F7C04 == 0 || *(uint8_t *)(dword_8F7C04 + 8052) == 0 )
  {
    v7 = *(uint32_t *)(pArg1 + 44);
    *(uint32_t *)(pArg1 + 52) = dword_8F7C04;
    if ( v7 != 0 && result != 0 )
      result = sub_48C500(result);
  }
  *(uint32_t *)(pArg1 + 1320) = 0;
  *(uint32_t *)(pArg1 + 1324) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x425500 sub_425500
// ------------------------------------------------------------
char /*thiscall*/ sub_425500(int this, int pArg2)
{
  int fld_2C; // eax
  int fld_2C2; // eax

  sub_65DC70(lpCriticalSection);
  fld_2C = *(uint32_t *)(this + 44);
  if ( fld_2C != 0 )
    *(uint32_t *)(fld_2C + 392) = 0;
  *(uint32_t *)(this + 44) = pArg2;
  if ( pArg2 != 0 )
    *(uint32_t *)(pArg2 + 392) = this;
  *(uint8_t *)(this + 48) = 0;
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) == this )
  {
    fld_2C2 = *(uint32_t *)(this + 44);
    if ( fld_2C2 != 0 )
      dword_9A012C = *(uint32_t *)(fld_2C2 + 356);
  }
  return sub_4253E0(this);
}



// ------------------------------------------------------------
// 0x425570 sub_425570
// ------------------------------------------------------------
char /*thiscall*/ sub_425570(int this)
{
  int fld_4A8; // eax
  uint32_t *fld_2C; // ecx
  int v4; // edi
  int fld_2C32; // ebx
  int v6; // eax
  int fld_49C; // ecx
  int fld_34; // ecx
  int fld_4A0; // eax
  int fld_4A4; // ecx
  int fld_342; // eax
  int fld_4A82; // eax
  int pThis_4AC; // eax
  int fld_4C42; // edi
  int pThis_4AC2; // eax
  int pThis_4AC3; // eax
  uint64_t v17; // rax
  int pThis_4AC4; // eax
  int pThis_4AC5; // eax
  int pThis_4AC6; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // eax
  int fld_2C5; // edi
  int fld_4C47; // ebx
  float v27; // [esp+0h] [ebp-34h]
  float v28; // [esp+0h] [ebp-34h]
  float v29; // [esp+4h] [ebp-30h]
  float v30; // [esp+4h] [ebp-30h]
  int fld_4C4; // [esp+Ch] [ebp-28h]
  int fld_4C44; // [esp+Ch] [ebp-28h]
  int fld_4C45; // [esp+Ch] [ebp-28h]
  int fld_4C46; // [esp+Ch] [ebp-28h]
  int v35; // [esp+1Ch] [ebp-18h]
  int fld_4C43; // [esp+1Ch] [ebp-18h]
  int fld_2C2; // [esp+20h] [ebp-14h]
  int v38; // [esp+20h] [ebp-14h]
  int v39; // [esp+24h] [ebp-10h]
  float fld_490; // [esp+28h] [ebp-Ch]
  int v41; // [esp+2Ch] [ebp-8h]
  int fld_2C4; // [esp+2Ch] [ebp-8h]
  int v43; // [esp+2Ch] [ebp-8h]
  int fld_2C3; // [esp+30h] [ebp-4h]
  int fld_343; // [esp+30h] [ebp-4h]
  int v46; // [esp+30h] [ebp-4h]

  fld_4A8 = *(uint32_t *)(this + 1192);
  if ( fld_4A8 == 0 )
    return fld_4A8;
  fld_2C = *(uint32_t **)(this + 44);
  if ( fld_2C == nullptr )
    return fld_4A8;
  fld_490 = 1.0;
  v4 = 0;
  fld_2C32 = 0;
  v6 = sub_48C1C0(fld_2C, 1);
  fld_49C = *(uint32_t *)(this + 1180);
  v39 = v6;
  if ( fld_49C == -1 )
  {
    fld_34 = *(uint32_t *)(this + 52);
    if ( fld_34 != 0 )
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_34 + 120))(fld_34) - 320;
    v41 = v6;
  }
  else
  {
    v41 = fld_49C - 320;
  }
  fld_4A0 = *(uint32_t *)(this + 1184);
  fld_2C2 = *(uint32_t *)(*(uint32_t *)(this + 44) + 468);
  if ( fld_4A0 == -1 || (fld_4A4 = *(uint32_t *)(this + 1188)) == -1 )
  {
    fld_342 = *(uint32_t *)(this + 52);
    if ( fld_342 != 0 )
    {
      fld_343 = *(uint32_t *)(this + 52);
      v35 = -120 - (*(int (**)(void))(*(uint32_t *)fld_342 + 128))();
      fld_2C3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_343 + 124))(fld_343) + v35;
    }
    else
    {
      fld_2C3 = *(uint32_t *)(*(uint32_t *)(this + 44) + 468);
    }
  }
  else
  {
    fld_2C3 = fld_4A0 - fld_4A4 - 120;
  }
  fld_4A82 = *(uint32_t *)(this + 1192);
  switch ( fld_4A82 )
  {
    case 1:
      fld_4C4 = *(uint32_t *)(this + 1220);
      pThis_4AC = sub_699000(this + 1196);
      fld_490 = sub_4049C0(1.0, *(float *)(this + 1168), pThis_4AC, fld_4C4);
      fld_4C42 = *(uint32_t *)(this + 1220);
      pThis_4AC2 = sub_699000(this + 1196);
      v29 = (float)v41;
      v27 = (float)v39;
      v4 = (uint64_t)sub_4049C0(v27, v29, pThis_4AC2, fld_4C42);
      fld_4C43 = *(uint32_t *)(this + 1220);
      pThis_4AC3 = sub_699000(this + 1196);
      v30 = (float)fld_2C3;
      v28 = (float)fld_2C2;
      v17 = (uint64_t)sub_4049C0(v28, v30, pThis_4AC3, fld_4C43);
LABEL_20:
      fld_2C32 = v17;
      break;
    case 2:
      v4 = v41;
      fld_2C32 = fld_2C3;
      fld_490 = *(float *)(this + 1168);
      break;
    case 3:
      fld_4C44 = *(uint32_t *)(this + 1220);
      pThis_4AC4 = sub_699000(this + 1196);
      fld_490 = sub_4049C0(*(float *)(this + 1168), 1.0, pThis_4AC4, fld_4C44);
      fld_4C45 = *(uint32_t *)(this + 1220);
      pThis_4AC5 = sub_699000(this + 1196);
      v4 = sub_423A80(v41, v39, pThis_4AC5, fld_4C45);
      fld_4C46 = *(uint32_t *)(this + 1220);
      pThis_4AC6 = sub_699000(this + 1196);
      LODWORD(v17) = sub_423A80(fld_2C3, fld_2C2, pThis_4AC6, fld_4C46);
      goto LABEL_20;
    default:
      break;
  }
  fld_2C4 = *(uint32_t *)(this + 44);
  v21 = sub_424FF0(fld_2C4);
  v22 = fld_2C32 <= 0 ? 0 : fld_2C32;
  if ( v22 >= 120 * v21 )
    v22 = 120 * sub_424FF0(fld_2C4);
  v38 = v22;
  if ( (v4 <= 0 ? 0 : v4) >= sub_425080(fld_2C4) )
    v23 = sub_425080(fld_2C4);
  else
    v23 = v4 <= 0 ? 0 : v4;
  *(uint32_t *)(fld_2C4 + 464) = v23;
  *(uint32_t *)(fld_2C4 + 468) = v38;
  v46 = sub_424DC0(this);
  v43 = sub_424E10(this);
  if ( v4 >= 0 )
  {
    if ( v4 > sub_425080(*(uint32_t *)(this + 44)) )
    {
      v46 += v4 - sub_425080(*(uint32_t *)(this + 44));
      if ( v46 >= 640 )
        v46 = 640;
    }
  }
  else
  {
    v46 = v46 + v4 <= 0 ? 0 : v46 + v4;
  }
  if ( fld_2C32 >= 0 )
  {
    fld_2C5 = *(uint32_t *)(this + 44);
    if ( fld_2C32 > 120 * sub_424FF0(fld_2C5) )
    {
      v43 += fld_2C32 - 120 * sub_424FF0(fld_2C5);
      if ( v43 >= 480 )
        v43 = 480;
    }
  }
  else
  {
    v43 = v43 + fld_2C32 <= 0 ? 0 : v43 + fld_2C32;
  }
  dword_77F6DC = LODWORD(fld_490);
  dword_8F7BD0 = v46;
  dword_8F7BD4 = v43;
  fld_4A8 = *(uint32_t *)(this + 1192);
  switch ( fld_4A8 )
  {
    case 1:
      fld_4C47 = *(uint32_t *)(this + 1220);
      fld_4A8 = sub_699000(this + 1196);
      if ( fld_4A8 >= fld_4C47 )
      {
        if ( *(uint32_t *)(this + 1176) != 0 )
        {
          *(uint8_t *)(this + 1209) = 0;
          *(uint8_t *)(this + 1210) = 0;
          LOBYTE(fld_4A8) = sub_698F90(this + 1196, *(uint32_t *)(this + 1176) == -1 ? 0 : *(uint32_t *)(this + 1176), 0);
          *(uint32_t *)(this + 1192) = 2;
          return fld_4A8;
        }
LABEL_43:
        LOBYTE(fld_4A8) = sub_424F00(this);
      }
      break;
    case 2:
      if ( *(uint32_t *)(this + 1176) != -1 )
      {
        LOBYTE(fld_4A8) = sub_41C6E0((int *)(this + 1196));
        if ( (uint8_t)fld_4A8 != 0 )
          goto LABEL_43;
      }
      break;
    case 3:
      LOBYTE(fld_4A8) = sub_41C6E0((int *)(this + 1196));
      if ( (uint8_t)fld_4A8 != 0 )
        LOBYTE(fld_4A8) = sub_423910(this);
      break;
    default:
      break;
  }
  return fld_4A8;
}


// ============================================================
// §9 播报层 · 三轴评价动画器（0x425940-0x426200）
//   HK_TECHNIC(+592)@0x425DA0 / HK_STYLE(+628)@0x425F10 / HK_ATTACKED(+556)@0x426080
//   滑入滑出 50/100ms·250/300ms 两档（值==2 用宽档），窗钟对 +596/+620·+632/+656·+560/+584
// ============================================================
// ------------------------------------------------------------
// 0x425940 sub_425940
// ------------------------------------------------------------
uint32_t *sub_425940()
{
  uint32_t *result; // eax

  result = operator new(0xCu);
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x425960 sub_425960
// ------------------------------------------------------------
char /*cdecl*/ sub_425960(char pszArg1, int pArg2, int **pDwArg3)
{
  char result; // al
  int **v4; // edi
  int *k; // esi
  int i; // [esp+14h] [ebp+Ch]
  int j; // [esp+18h] [ebp+10h]

  if ( pDwArg3 != nullptr )
    result = sub_45ED10(pDwArg3, pszArg1);
  if ( pArg2 != 0 )
  {
    v4 = (int **)(pArg2 + 28);
    for ( i = 6; i != 0; --i )
    {
      for ( j = 2; j != 0; --j )
      {
        for ( k = *(v4 - 1); k != *v4; k += 2 )
          sub_4939E0(*k, pszArg1);
        v4 += 4;
        result = j - 1;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4259D0 sub_4259D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4259D0(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // edx

  fld_e2 = *(this + 2);
  if ( fld_e2 != 0 && uArg2 < (*(this + 3) - fld_e2) >> 2 )
    return *(uint32_t *)(*(this + 2) + 4 * uArg2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x425A00 sub_425A00
// ------------------------------------------------------------
int /*thiscall*/ sub_425A00(uint32_t *this, unsigned int uArg2)
{
  int fld_e30; // edx

  fld_e30 = *(this + 30);
  if ( fld_e30 != 0 && uArg2 < (*(this + 31) - fld_e30) >> 2 )
    return *(uint32_t *)(*(this + 30) + 4 * uArg2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x425A30 sub_425A30
// ------------------------------------------------------------
int /*thiscall*/ sub_425A30(int *this)
{
  int result; // eax
  int fld_e196; // ebx
  int pThis_BE; // edi
  char v5; // bl
  double pThis_BB; // st7
  uint8_t v8; // c0
  uint8_t v9; // c3
  int fld_e184; // edx
  double v11; // st7
  unsigned int v12; // ebx
  int v13; // edi
  int v14; // eax
  int v15; // eax
  double pThis_BB2; // st7
  int v17; // eax
  unsigned int v18; // ebx
  int v19; // edi
  double pThis_BB3; // st7
  int v21; // eax
  int fld_e187; // [esp-1Ch] [ebp-6Ch]
  int fld_e1872; // [esp-1Ch] [ebp-6Ch]
  int v24; // [esp-14h] [ebp-64h]
  int v25; // [esp-14h] [ebp-64h]
  uint32_t v26[8]; // [esp+4h] [ebp-4Ch]
  int v27; // [esp+24h] [ebp-2Ch]
  int v28; // [esp+28h] [ebp-28h]
  int v29; // [esp+2Ch] [ebp-24h]
  unsigned int nLen; // [esp+30h] [ebp-20h]
  int nLen2; // [esp+34h] [ebp-1Ch]
  int fld_e183; // [esp+38h] [ebp-18h]
  char Buffer[16]; // [esp+3Ch] [ebp-14h] BYREF
  int dword_796E502; // [esp+4Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = *(this + 188);
  if ( result > 0 )
  {
    fld_e196 = *(this + 196);
    result = sub_699000((int)(this + 190));
    if ( result < fld_e196 )
    {
      pThis_BE = sub_699000((int)(this + 190));
      sprintf(Buffer, "%d", *(this + 188));
      v5 = 0;
      v28 = 255;
      if ( pThis_BE >= 200 )
      {
        if ( pThis_BE >= 300 )
        {
          if ( pThis_BE >= 700 )
          {
            fld_e184 = *(this + 184) - 1;
            *(this + 187) = 1065353216;
            *(this + 184) = fld_e184;
            if ( sub_4049C0(255.0, 0.0, pThis_BE, 1500) >= 1.0 )
              v11 = sub_4049C0(255.0, 0.0, pThis_BE, 1500);
            else
              v11 = 1.0;
            v28 = (uint64_t)(v11 * 0.5);
          }
          else
          {
            pThis_BB = *((float *)this + 187) - 0.1;
            *((float *)this + 187) = pThis_BB;
            if ( (v8 | v9) != 0 )
              pThis_BB = 1.0;
            *((float *)this + 187) = pThis_BB;
          }
        }
        else
        {
          v5 = 1;
          *(this + 187) = 1069547520;
        }
      }
      else
      {
        *((float *)this + 187) = sub_4049C0(0.5, 1.2, pThis_BE, 200);
      }
      v27 = v5 != 1 ? 0 : 5;
      nLen2 = (v5 != 1) - 1;
      sub_491530(2, 0);
      fld_e183 = *(this + 183);
      v12 = 0;
      nLen = strlen(Buffer);
      if ( nLen != 0 )
      {
        v29 = ((uint8_t)v28 << 24) | 0xFFFFFF;
        do
        {
          v13 = Buffer[v12] + 64;
          v14 = *(uint32_t *)(sub_418DD0(v13) + 20);
          v26[v12] = v14;
          v15 = v14 - 30;
          nLen = v15;
          if ( v12 != 0 )
            pThis_BB2 = (double)v15 * *((float *)this + 187);
          else
            pThis_BB2 = (double)v15 * (1.0 - *((float *)this + 187));
          v24 = v29;
          fld_e183 += (uint64_t)pThis_BB2;
          fld_e187 = *(this + 187);
          v17 = sub_418DD0(v13);
          sub_424760(dword_79C0B0, fld_e183, *(this + 184), v17, *(float *)&fld_e187, fld_e187, 0.0, v24, 0.0, 0.0);
          ++v12;
        }
        while ( v12 < strlen(Buffer) );
      }
      sub_491630(2);
      sub_491530(v27, nLen2);
      fld_e183 = *(this + 183);
      v18 = 0;
      nLen2 = strlen(Buffer);
      if ( nLen2 != 0 )
      {
        v29 = ((uint8_t)v28 << 24) | 0xFFFFFF;
        do
        {
          v19 = Buffer[v18] + 75;
          if ( v18 != 0 )
          {
            nLen2 = v26[v18] - 30;
            pThis_BB3 = (double)nLen2 * *((float *)this + 187);
          }
          else
          {
            nLen2 = v26[0] - 30;
            pThis_BB3 = (double)(v26[0] - 30) * (1.0 - *((float *)this + 187));
          }
          fld_e183 += (uint64_t)pThis_BB3;
          v25 = v29;
          fld_e1872 = *(this + 187);
          v21 = sub_418DD0(v19);
          sub_424760(dword_79C0B0, fld_e183, *(this + 184), v21, *(float *)&fld_e1872, fld_e1872, 0.0, v25, 0.0, 0.0);
          ++v18;
        }
        while ( v18 < strlen(Buffer) );
      }
      return sub_491630(v27);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x425DA0 sub_425DA0
// ------------------------------------------------------------
// 【播报层 · 技巧轴 HK_TECHNIC 动画器】读 this+592（1/2 档）：50/100ms（普通）或
//   250/300ms（==2 宽档）滑入滑出（sub_4049F0 插值）；图槽 sub_418DD0(99) vt+152 id 278；
//   计数 sub_69A110(…,277,值)；窗 this+620 / 钟 this+596，超窗清零。
int /*usercall*/ sub_425DA0@<eax>(int pArg1@<ecx>, double fArg2@<st0>)
{
  int result; // eax
  int v4; // esi
  int v5; // eax
  int v6; // edi
  int pObj; // eax
  int v8; // esi
  int v9; // esi
  int v10; // [esp-14h] [ebp-18h]

  result = *(uint32_t *)(pArg1 + 592);
  if ( result > 0 )
  {
    v4 = 518;
    v5 = sub_699000(pArg1 + 596);
    v6 = v5;
    if ( *(uint32_t *)(pArg1 + 592) == 2 )
    {
      if ( v5 < 250 )
      {
        sub_4049F0(110.0, 0.0, v5, 250, 1);
LABEL_12:
        v4 = (uint64_t)fArg2 + 513;
LABEL_13:
        pObj = sub_418DD0(99);
        if ( pObj != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v4, 278, dword_79C0B0);
        v8 = 513 - sub_699FC0(*(uint32_t *)(pArg1 + 592));
        if ( v6 >= 250 )
        {
          if ( v6 >= 300 )
            goto LABEL_20;
          sub_4049F0(0.0, 5.0, v6 - 250, 50, 0);
        }
        else
        {
          sub_4049F0(110.0, 0.0, v6, 250, 1);
        }
        v8 = v8 + (uint64_t)fArg2 - 5;
LABEL_20:
        sub_69A110(v8, 277, *(uint32_t *)(pArg1 + 592), -1);
        v9 = *(uint32_t *)(pArg1 + 620);
        result = sub_699000(pArg1 + 596);
        if ( result >= v9 )
          *(uint32_t *)(pArg1 + 592) = 0;
        return result;
      }
      if ( v5 >= 300 )
        goto LABEL_13;
      v10 = v5 - 250;
    }
    else
    {
      if ( v5 < 50 )
      {
        sub_4049F0(5.0, 0.0, v5, 250, 1);
        goto LABEL_12;
      }
      if ( v5 >= 100 )
        goto LABEL_13;
      v10 = v5 - 50;
    }
    sub_4049F0(0.0, 5.0, v10, 50, 0);
    goto LABEL_12;
  }
  return result;
}



// ------------------------------------------------------------
// 0x425F10 sub_425F10
// ------------------------------------------------------------
// 【播报层 · 风格轴 HK_STYLE 动画器】同构 this+628：图槽 sub_418DD0(43)，id 298/299；
//   窗 this+656 / 钟 this+632。
int /*usercall*/ sub_425F10@<eax>(int pArg1@<ecx>, double fArg2@<st0>)
{
  int result; // eax
  int v4; // esi
  int v5; // eax
  int v6; // edi
  int pObj; // eax
  int v8; // esi
  int v9; // esi
  int v10; // [esp-14h] [ebp-18h]

  result = *(uint32_t *)(pArg1 + 628);
  if ( result > 0 )
  {
    v4 = 518;
    v5 = sub_699000(pArg1 + 632);
    v6 = v5;
    if ( *(uint32_t *)(pArg1 + 628) == 2 )
    {
      if ( v5 < 250 )
      {
        sub_4049F0(110.0, 0.0, v5, 250, 1);
LABEL_12:
        v4 = (uint64_t)fArg2 + 513;
LABEL_13:
        pObj = sub_418DD0(43);
        if ( pObj != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v4, 298, dword_79C0B0);
        v8 = 513 - sub_699FC0(*(uint32_t *)(pArg1 + 628));
        if ( v6 >= 250 )
        {
          if ( v6 >= 300 )
            goto LABEL_20;
          sub_4049F0(0.0, 5.0, v6 - 250, 50, 0);
        }
        else
        {
          sub_4049F0(110.0, 0.0, v6, 250, 1);
        }
        v8 = v8 + (uint64_t)fArg2 - 5;
LABEL_20:
        sub_69A110(v8, 299, *(uint32_t *)(pArg1 + 628), -1);
        v9 = *(uint32_t *)(pArg1 + 656);
        result = sub_699000(pArg1 + 632);
        if ( result >= v9 )
          *(uint32_t *)(pArg1 + 628) = 0;
        return result;
      }
      if ( v5 >= 300 )
        goto LABEL_13;
      v10 = v5 - 250;
    }
    else
    {
      if ( v5 < 50 )
      {
        sub_4049F0(5.0, 0.0, v5, 250, 1);
        goto LABEL_12;
      }
      if ( v5 >= 100 )
        goto LABEL_13;
      v10 = v5 - 50;
    }
    sub_4049F0(0.0, 5.0, v10, 50, 0);
    goto LABEL_12;
  }
  return result;
}



// ------------------------------------------------------------
// 0x426080 sub_426080
// ------------------------------------------------------------
// 【播报层 · 被击轴 HK_ATTACKED 动画器】this+556：图槽 sub_418DD0(98)，id 248 +
//   计数（y 478/573 两行）；窗 this+584 / 钟 this+560，超窗清零。
int /*usercall*/ sub_426080@<eax>(int pArg1@<ecx>, double fArg2@<st0>)
{
  int result; // eax
  int v4; // esi
  int v5; // eax
  int v6; // eax
  int pObj; // eax
  int v8; // esi
  int v9; // esi
  int v10; // eax
  int v11; // esi

  result = *(uint32_t *)(pArg1 + 556);
  if ( result <= 0 )
    return result;
  v4 = 483;
  v5 = sub_699000(pArg1 + 560);
  if ( *(uint32_t *)(pArg1 + 556) != 2 )
  {
    if ( v5 < 50 )
    {
      sub_4049F0(5.0, 0.0, v5, 250, 1);
      goto LABEL_12;
    }
    if ( v5 >= 100 )
      goto LABEL_13;
    v6 = v5 - 50;
LABEL_11:
    sub_4049F0(0.0, 5.0, v6, 50, 0);
    goto LABEL_12;
  }
  if ( v5 >= 250 )
  {
    if ( v5 >= 300 )
      goto LABEL_13;
    v6 = v5 - 250;
    goto LABEL_11;
  }
  sub_4049F0(110.0, 0.0, v5, 250, 1);
LABEL_12:
  v4 = (uint64_t)fArg2 + 478;
LABEL_13:
  pObj = sub_418DD0(98);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v4, 248, dword_79C0B0);
  v8 = *(uint32_t *)(pArg1 + 584);
  if ( sub_699000(pArg1 + 560) >= v8 )
    *(uint32_t *)(pArg1 + 556) = 0;
  result = *(uint32_t *)(pArg1 + 556);
  if ( result > 0 )
  {
    v9 = 578;
    v10 = sub_699000(pArg1 + 560);
    if ( v10 >= 250 )
    {
      if ( v10 >= 300 )
        goto LABEL_23;
      sub_4049F0(0.0, 5.0, v10 - 250, 50, 0);
    }
    else
    {
      sub_4049F0(110.0, 0.0, v10, 250, 1);
    }
    v9 = (uint64_t)fArg2 + 573;
LABEL_23:
    sub_69A110(v9, 248, *(uint32_t *)(pArg1 + 556), -1);
    v11 = *(uint32_t *)(pArg1 + 584);
    result = sub_699000(pArg1 + 560);
    if ( result >= v11 )
      *(uint32_t *)(pArg1 + 556) = 0;
  }
  return result;
}



// ============================================================
// §10 播报层主体 —— 横幅 tick 与总入口 sub_426820（0x426200-0x426C60）
//   0x426200 横幅模式逐帧绘制（85/86/87 三段图 ×1.5 宽，200/500/200ms 相位）
//   0x426820 总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTACKED · 4 死亡 ·
//   5 伤害数字(+900) · 6 HK_STYLE · 7 HK_TECHNIC；语音经 dword_8F7C04 vt+212
// ============================================================
// ------------------------------------------------------------
// 0x426200 sub_426200
// ------------------------------------------------------------
// 【播报层 · 横幅模式逐帧绘制】三段图 85/86/87（sub_418DD0），宽 ×1.5（dword_8F7B88/
//   8F7B7C/8F7B70 = 基宽+基宽>>1），相位 200/500/200ms（dword_8F7B28/8F7B1C/8F7B10），
//   阶段计数 dword_8F7BE4/8F7BE0/8F7BDC；锚定玩家 vt+120/124/128/192 屏幕投影。
void /*thiscall*/ sub_426200(int this)
{
  int pObj2; // edi
  int v3; // eax
  int pObj; // edi
  int v5; // eax
  int dword_8F7BE42; // ebx
  int pThis_1F4; // eax
  double v8; // st7
  int v9; // edi
  int v10; // eax
  int pObj6; // edi
  int v12; // eax
  int pObj3; // edi
  int v14; // eax
  int v15; // eax
  int dword_8F7BE02; // ebx
  int pThis_1D8; // eax
  double v18; // st7
  int v19; // edi
  int v20; // eax
  int pObj4; // edi
  int v22; // eax
  int pObj5; // edi
  int v24; // eax
  int v25; // eax
  int dword_8F7BDC2; // ebx
  int pThis_210; // edi
  int fld_2283; // esi
  int v29; // eax
  double v30; // st7
  int v31; // esi
  int v32; // eax
  int v33; // [esp-14h] [ebp-34h]
  int v34; // [esp-14h] [ebp-34h]
  int v35; // [esp-14h] [ebp-34h]
  int v36; // [esp-10h] [ebp-30h]
  int v37; // [esp-10h] [ebp-30h]
  int v38; // [esp-10h] [ebp-30h]
  int v39; // [esp-Ch] [ebp-2Ch]
  int v40; // [esp-Ch] [ebp-2Ch]
  int v41; // [esp-Ch] [ebp-2Ch]
  int fld_20C3; // [esp+4h] [ebp-1Ch]
  int fld_1F0; // [esp+4h] [ebp-1Ch]
  int fld_1F02; // [esp+4h] [ebp-1Ch]
  int v45; // [esp+4h] [ebp-1Ch]
  int fld_228; // [esp+4h] [ebp-1Ch]
  int fld_2282; // [esp+4h] [ebp-1Ch]
  int v48; // [esp+4h] [ebp-1Ch]
  int fld_20C; // [esp+8h] [ebp-18h]
  int fld_20C2; // [esp+8h] [ebp-18h]
  int v51; // [esp+8h] [ebp-18h]
  int v52; // [esp+8h] [ebp-18h]
  int fld_1F03; // [esp+8h] [ebp-18h]
  int v54; // [esp+8h] [ebp-18h]
  int v55; // [esp+8h] [ebp-18h]
  int v56; // [esp+Ch] [ebp-14h]
  int v57; // [esp+10h] [ebp-10h]
  int v58; // [esp+10h] [ebp-10h]
  int v59; // [esp+10h] [ebp-10h]
  int v60; // [esp+14h] [ebp-Ch]
  int v61; // [esp+14h] [ebp-Ch]
  int v62; // [esp+14h] [ebp-Ch]
  float v63; // [esp+18h] [ebp-8h]
  char v64; // [esp+1Fh] [ebp-1h]
  char v65; // [esp+1Fh] [ebp-1h]
  char v66; // [esp+1Fh] [ebp-1h]

  if ( dword_8F7C04 == 0 )
    return;
  pObj2 = dword_8F7C04;
  v39 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);
  v60 = sub_45E490(v3, v39);
  pObj = dword_8F7C04;
  v36 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);
  v33 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
  v57 = sub_45E4D0(v5, v33, v36, 1.0);
  v56 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 192))(dword_8F7C04);
  sub_418DD0(85);
  sub_418DD0(86);
  sub_418DD0(87);
  dword_8F7BE42 = dword_8F7BE4;
  LOBYTE(v63) = 0;
  v64 = 0;
  fld_20C = *(uint32_t *)(this + 524);
  if ( sub_699000(this + 500) >= fld_20C && dword_8F7BE4 < 2 && sub_699000(this + 500) > dword_8F7B28[dword_8F7BE42] )
  {
    dword_8F7BE42 = ++dword_8F7BE4;
    *(uint8_t *)(this + 513) = 0;
    *(uint8_t *)(this + 514) = 0;
    sub_698F90(this + 500, dword_8F7B28[dword_8F7BE42], 0);
    v64 = 1;
  }
  fld_20C2 = *(uint32_t *)(this + 524);
  if ( sub_699000(this + 500) < fld_20C2 )
  {
    fld_20C3 = *(uint32_t *)(this + 524);
    v51 = dword_8F7B88[dword_8F7BE42];
    pThis_1F4 = sub_699000(this + 500);
    v8 = (double)v51;
    v63 = v8;
    sub_4049F0(0.0, v63, pThis_1F4, fld_20C3, 1);
    v52 = (uint64_t)v8;
    v9 = *(uint32_t *)(sub_418DD0(85) + 20) - v52 + v60;
    if ( dword_8F7BE42 != 0 )
    {
      if ( dword_8F7BE42 == 1 )
        LOBYTE(v63) = -1;
      else
        LOBYTE(v63) = -1 - (uint64_t)((double)v52 / v63 * 255.0);
      v9 -= dword_8F7B88[0];
    }
    else
    {
      LODWORD(v63) = (uint64_t)((double)v52 / v63 * 255.0);
    }
    goto LABEL_15;
  }
  if ( v64 == 1 )
  {
    v9 = v60;
LABEL_15:
    v10 = sub_418DD0(85);
    sub_424760(dword_79C0B0, v9, v57 - v56 - 64, v10, 1.0, 1065353216, 0.0, (LOBYTE(v63) << 24) | 0xFFFFFF, 0.0, 0.0);
  }
  pObj6 = dword_8F7C04;
  v40 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj6 + 120))(pObj6);
  v61 = sub_45E490(v12, v40);
  pObj3 = dword_8F7C04;
  v37 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);
  v34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 128))(pObj3);
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 124))(pObj3);
  v15 = sub_45E4D0(v14, v34, v37, 1.0);
  dword_8F7BE02 = dword_8F7BE0;
  fld_1F0 = *(uint32_t *)(this + 496);
  v58 = v15;
  v65 = 0;
  if ( sub_699000(this + 472) >= fld_1F0 && dword_8F7BE0 < 2 && sub_699000(this + 472) > dword_8F7B1C[dword_8F7BE02] )
  {
    dword_8F7BE02 = ++dword_8F7BE0;
    *(uint8_t *)(this + 485) = 0;
    *(uint8_t *)(this + 486) = 0;
    sub_698F90(this + 472, dword_8F7B1C[dword_8F7BE02], 0);
    v65 = 1;
  }
  fld_1F02 = *(uint32_t *)(this + 496);
  if ( sub_699000(this + 472) >= fld_1F02 )
  {
    if ( v65 != 1 )
      goto LABEL_31;
    v19 = v61;
  }
  else
  {
    v45 = dword_8F7B7C[dword_8F7BE02];
    fld_1F03 = *(uint32_t *)(this + 496);
    pThis_1D8 = sub_699000(this + 472);
    v18 = (double)v45;
    v63 = v18;
    sub_4049F0(0.0, v63, pThis_1D8, fld_1F03, 1);
    v54 = (uint64_t)v18;
    if ( dword_8F7BE02 != 0 )
    {
      if ( dword_8F7BE02 == 1 )
        LOBYTE(v63) = -1;
      else
        LOBYTE(v63) = -1 - (uint64_t)((double)v54 / v63 * 255.0);
    }
    else
    {
      LODWORD(v63) = (uint64_t)((double)v54 / v63 * 255.0);
    }
    v19 = *(uint32_t *)(sub_418DD0(86) + 20) - (uint64_t)v18 + v61;
    if ( dword_8F7BE02 != 0 )
      v19 -= dword_8F7B7C[0];
  }
  v20 = sub_418DD0(86);
  sub_424760(dword_79C0B0, v19, v58 - v56 - 64, v20, 1.0, 1065353216, 0.0, (LOBYTE(v63) << 24) | 0xFFFFFF, 0.0, 0.0);
LABEL_31:
  pObj4 = dword_8F7C04;
  v41 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);
  v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 120))(pObj4);
  v62 = sub_45E490(v22, v41);
  pObj5 = dword_8F7C04;
  v38 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);
  v35 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 128))(pObj5);
  v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 124))(pObj5);
  v25 = sub_45E4D0(v24, v35, v38, 1.0);
  dword_8F7BDC2 = dword_8F7BDC;
  pThis_210 = this + 528;
  fld_228 = *(uint32_t *)(this + 552);
  v59 = v25;
  v66 = 0;
  if ( sub_699000(this + 528) >= fld_228 && dword_8F7BDC < 2 && sub_699000(this + 528) > dword_8F7B10[dword_8F7BDC2] )
  {
    dword_8F7BDC2 = ++dword_8F7BDC;
    *(uint8_t *)(this + 541) = 0;
    *(uint8_t *)(this + 542) = 0;
    sub_698F90(this + 528, dword_8F7B10[dword_8F7BDC2], 0);
    v66 = 1;
  }
  fld_2282 = *(uint32_t *)(this + 552);
  if ( sub_699000(this + 528) >= fld_2282 )
  {
    if ( v66 != 1 )
      return;
    v31 = v62;
  }
  else
  {
    fld_2283 = *(uint32_t *)(this + 552);
    v48 = dword_8F7B70[dword_8F7BDC2];
    v29 = sub_699000(pThis_210);
    v30 = (double)v48;
    v63 = v30;
    sub_4049F0(0.0, v63, v29, fld_2283, 1);
    v55 = (uint64_t)v30;
    if ( dword_8F7BDC2 != 0 )
    {
      if ( dword_8F7BDC2 == 1 )
        LOBYTE(v63) = -1;
      else
        LOBYTE(v63) = -1 - (uint64_t)((double)v55 / v63 * 255.0);
    }
    else
    {
      LODWORD(v63) = (uint64_t)((double)v55 / v63 * 255.0);
    }
    v31 = *(uint32_t *)(sub_418DD0(87) + 20) - (uint64_t)v30 + v62;
    if ( dword_8F7BDC2 != 0 )
      v31 -= dword_8F7B70[0];
  }
  v32 = sub_418DD0(87);
  sub_424760(dword_79C0B0, v31, v59 - v56 - 64, v32, 1.0, 1065353216, 0.0, (LOBYTE(v63) << 24) | 0xFFFFFF, 0.0, 0.0);
}


// ------------------------------------------------------------
// 0x426820 sub_426820
// ------------------------------------------------------------
// ★★【播报层总入口】（研究 §12 定案：HUD 三轴评价横幅系统）
//   case0/1/2 横幅模式切换：基宽 sub_418DD0(87/86/85)+20、×1.5 锁存、200/500/200ms、
//     模式锁存 this+1252 = 0/1/2（复位值 8 由 0x423C10 写；读者未见于本文件【待验证】）；
//     case2 需 dword_8F7C04 就绪
//   case3 HK_ATTACKED：this+556 += a3（伤害累积），1500ms，语音 "HK_ATTACKED"
//   case4 死亡播报：→ sub_424D80(4)
//   case5 伤害数字：this+900 = a3，1500ms，→ sub_424D80(5)
//   case6 HK_STYLE：this+628 = a3，语音 "HK_STYLE"
//   case7 HK_TECHNIC：this+592 = a3，语音 "HK_TECHNIC"
//   语音 = dword_8F7C04 vt+212(标签,-1,0,0)。三轴动画器见 §9；tick 汇聚 0x427E90；
//   跨文件调用面见文件头清单。
int /*thiscall*/ sub_426820(int this, int nArg2, int nArg3)
{
  int result; // eax

  result = nArg2;
  if ( nArg2 != 0 )
  {
    switch ( nArg2 )
    {
      case 1:
        dword_8F7B84 = *(uint32_t *)(sub_418DD0(86) + 20);
        dword_8F7B7C = dword_8F7B84 + ((unsigned int)dword_8F7B84 >> 1);
        dword_8F7B1C = 200;
        dword_8F7B80 = 0;
        dword_8F7B20 = 500;
        dword_8F7B24 = 200;
        dword_8F7BE0 = 0;
        *(uint32_t *)(this + 1252) = 1;
        *(uint8_t *)(this + 485) = 0;
        *(uint8_t *)(this + 486) = 0;
        sub_698F90(dword_8F7B1C, 0);
        *(uint8_t *)(this + 977) = 0;
        *(uint8_t *)(this + 978) = 0;
        result = sub_698F90(500, 0);
        *(uint8_t *)(this + 1161) = 1;
        break;
      case 2:
        if ( dword_8F7C04 != 0 )
        {
          dword_8F7B90 = *(uint32_t *)(sub_418DD0(85) + 20);
          dword_8F7B88 = dword_8F7B90 + ((unsigned int)dword_8F7B90 >> 1);
          dword_8F7B28 = 200;
          dword_8F7B8C = 0;
          dword_8F7B2C = 500;
          dword_8F7B30 = 200;
          *(uint32_t *)(this + 1252) = 2;
          dword_8F7BE4 = 0;
          *(uint8_t *)(this + 513) = 0;
          *(uint8_t *)(this + 514) = 0;
          sub_698F90(dword_8F7B28, 0);
          return sub_424D80(2);
        }
        break;
      case 3:
        *(uint8_t *)(this + 573) = 0;
        *(uint8_t *)(this + 574) = 0;
        sub_698F90(1500, 0);
        *(uint32_t *)(this + 556) += nArg3;
        return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
                 dword_8F7C04,
                 "HK_ATTACKED",
                 -1,
                 0,
                 0);
      case 4:
        return sub_424D80(4);
      case 5:
        *(uint32_t *)(this + 900) = nArg3;
        *(uint8_t *)(this + 885) = 0;
        *(uint8_t *)(this + 886) = 0;
        sub_698F90(1500, 0);
        return sub_424D80(5);
      case 7:
        *(uint32_t *)(this + 592) = nArg3;
        *(uint8_t *)(this + 609) = 0;
        *(uint8_t *)(this + 610) = 0;
        sub_698F90(1500, 0);
        return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
                 dword_8F7C04,
                 "HK_TECHNIC",
                 -1,
                 0,
                 0);
      case 6:
        *(uint32_t *)(this + 628) = nArg3;
        *(uint8_t *)(this + 645) = 0;
        *(uint8_t *)(this + 646) = 0;
        sub_698F90(1500, 0);
        return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
                 dword_8F7C04,
                 "HK_STYLE",
                 -1,
                 0,
                 0);
      default:
        break;
    }
  }
  else
  {
    dword_8F7B78 = *(uint32_t *)(sub_418DD0(87) + 20);
    dword_8F7B70 = dword_8F7B78 + ((unsigned int)dword_8F7B78 >> 1);
    dword_8F7B10 = 200;
    dword_8F7B74 = 0;
    dword_8F7B14 = 500;
    dword_8F7B18 = 200;
    *(uint32_t *)(this + 1252) = 0;
    dword_8F7BDC = 0;
    *(uint8_t *)(this + 541) = 0;
    *(uint8_t *)(this + 542) = 0;
    sub_698F90(dword_8F7B10, 0);
    *(uint8_t *)(this + 949) = 0;
    *(uint8_t *)(this + 950) = 0;
    result = sub_698F90(500, 0);
    *(uint8_t *)(this + 1160) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x426B10 sub_426B10
// ------------------------------------------------------------
// 【横幅模式副作用】+330/+331 记录旧/新模式 + +332 钟；对可视对象集广播
//   （__RTTI IRDActiveObject 过滤 +1665 ∈ {1,2} → sub_495890）。被 0x4294E0 调用。
uint32_t */*thiscall*/ sub_426B10(uint32_t *this, int nArg2, int nArg3)
{
  int fld_e331; // eax
  int pThis_14C; // ecx
  uint32_t *result; // eax
  int v7; // ecx
  int v8; // ebx
  unsigned int i; // esi
  int fld_e26; // ecx
  int v11; // edx
  int v12; // eax
  int v13; // ecx

  fld_e331 = *(this + 331);
  *(this + 331) = nArg2;
  pThis_14C = (int)(this + 332);
  *(this + 330) = fld_e331;
  *(uint8_t *)(pThis_14C + 13) = 0;
  *(uint8_t *)(pThis_14C + 14) = 0;
  sub_698F90(pThis_14C, nArg3, 0);
  result = (uint32_t *)*(this + 26);
  if ( result != nullptr )
  {
    v7 = result[30];
    v8 = v7 != 0 ? (result[31] - v7) >> 2 : 0;
    for ( i = 0; (int)i < v8; ++i )
    {
      fld_e26 = *(this + 26);
      v11 = *(uint32_t *)(fld_e26 + 120);
      if ( v11 != 0 && i < (*(uint32_t *)(fld_e26 + 124) - v11) >> 2 )
        v12 = *(uint32_t *)(v11 + 4 * i);
      else
        v12 = 0;
      result = (uint32_t *)__RTDynamicCast(
                           v12,
                           0,
                           &IRDCollisionObject `RTTI Type Descriptor',
                           &IRDActiveObject `RTTI Type Descriptor',
                           0);
      if ( result != nullptr )
      {
        v13 = result[1665];
        if ( v13 == 2 || v13 == 1 )
          result = (uint32_t *)sub_495890(v13, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x426BD0 sub_426BD0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_426BD0(uint8_t *this)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__IControl;
  *(this + 76) = 0;
  *((uint32_t *)this + 18) = &vftbl_nengine__CNString;
  sub_402A50();
  *((uint32_t *)this + 24) = sub_425940(this + 92);
  *((uint32_t *)this + 25) = 0;
  nengine__IControl__vmt10(this);
  nengine__IControl__vmt4(this);
  return this;
}



// ============================================================
// §11 评价家族扩展 —— 组队双槽/AIRIAL/GOOD（0x426C60-0x428050）
//   0x4271B0 组队双槽评价(+248[i] vs 阈值 dword_6C38A4[i] → 'HK_STYLE' 语音+串496/497)
//   与 HK1/HK2_AIRIAL 横幅状态机；0x4278D0 计数写入器；0x427E90 HUD 逐帧更新分发器
// ============================================================
// ------------------------------------------------------------
// 0x426C60 nengine__IControl__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nengine__IControl__vmt0(void *Block, char pszArg2)
{
  sub_426C90();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x426C90 sub_426C90
// ------------------------------------------------------------
int /*thiscall*/ sub_426C90(void **this)
{
  int result; // eax

  *this = &vftbl_nengine__IControl;
  nengine__IControl__vmt14();
  sub_6569D0(this + 23);
  j__free(*(this + 24));
  *(this + 24) = nullptr;
  *(this + 18) = &vftbl_nengine__CNString;
  result = sub_402A60(this + 18);
  *(this + 18) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 76) = 0;
  *this = &vftbl_nengine__IObject;
  *((uint8_t *)this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x426D20 sub_426D20
// ------------------------------------------------------------
void /*thiscall*/ sub_426D20(int this)
{
  int fld_348; // eax
  int v3; // esi
  int v4; // esi
  int v5; // kr08_4
  int v6; // esi
  int v7; // edi
  int fld_3A4; // eax
  int pObj; // eax
  int pObj2; // eax
  int pObj3; // eax
  int v12; // eax
  int v13; // eax
  int fld_364; // edi
  int fld_3A42; // eax
  bool fld_3A43; // sf
  int v17; // eax
  int fld_2C; // edi
  int v19; // esi
  void *fld_68; // ecx
  void *Block2; // eax
  bool v22; // zf
  int v23; // [esp-14h] [ebp-40h]
  uint8_t v24[4]; // [esp+4h] [ebp-28h] BYREF
  void *Block; // [esp+8h] [ebp-24h]
  int v26; // [esp+14h] [ebp-18h]
  int v27; // [esp+18h] [ebp-14h]
  int v28; // [esp+1Ch] [ebp-10h]
  int v29; // [esp+28h] [ebp-4h]

  fld_348 = *(uint32_t *)(this + 840);
  if ( fld_348 == -1 )
  {
    dword_77F7AC = 0;
    dword_8F7C00 = 0;
    return;
  }
  if ( fld_348 != 0 )
  {
    if ( fld_348 == 1 )
    {
      dword_8F7C00 = 104;
    }
    else if ( fld_348 == 2 )
    {
      dword_8F7C00 = 106;
    }
  }
  else
  {
    dword_8F7C00 = 102;
  }
  v3 = *(uint32_t *)(sub_418DD0(dword_8F7C00 + 1) + 20);
  v27 = (int)abs32(v3 - *(uint32_t *)(sub_418DD0(dword_8F7C00) + 20)) / 2;
  v4 = *(uint32_t *)(sub_418DD0(dword_8F7C00 + 1) + 24);
  v28 = (int)abs32(v4 - *(uint32_t *)(sub_418DD0(dword_8F7C00) + 24)) / 2;
  v5 = *(uint32_t *)(sub_418DD0(dword_8F7C00) + 20);
  v6 = 320 - v5 / 2;
  v7 = 240 - *(uint32_t *)(sub_418DD0(dword_8F7C00) + 24) / 2;
  fld_3A4 = *(uint32_t *)(this + 932);
  switch ( fld_3A4 )
  {
    case 0:
      sub_491530(5, -1);
      v27 = ((uint8_t)dword_77F7AC << 24) | 0xFFFFFF;
      pObj = sub_418DD0(dword_8F7C00 + 1);
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 156))(
          pObj,
          320 - v5 / 2,
          v7,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v27,
          1115947008,
          1333788672);
      goto LABEL_22;
    case 1:
      sub_491530(5, -1);
      v26 = ((uint8_t)dword_77F7AC << 24) | 0xFFFFFF;
      pObj2 = sub_418DD0(dword_8F7C00);
      if ( pObj2 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 156))(
          pObj2,
          v27 + v6,
          v28 + v7,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          v26,
          1115947008,
          1333788672);
      goto LABEL_22;
    case 2:
      pObj3 = sub_418DD0(dword_8F7C00);
      if ( pObj3 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 156))(
          pObj3,
          v27 + v6,
          v28 + v7,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          -1,
          1115947008,
          1333788672);
      break;
    case 3:
      v12 = sub_418DD0(dword_8F7C00 + 1);
      sub_423930(320 - v5 / 2, v7, v12, 1065353216, 1065353216, 0, -1, 1115947008, 1333788672);
      break;
    case 4:
      sub_491530(5, -1);
      v23 = ((uint8_t)dword_77F7AC << 24) | 0xFFFFFF;
      v13 = sub_418DD0(dword_8F7C00 + 1);
      sub_423930(320 - v5 / 2, v7, v13, 1065353216, 1065353216, 0, v23, 1115947008, 1333788672);
LABEL_22:
      sub_491630(5);
      break;
    default:
      break;
  }
  dword_77F7AC -= 10;
  if ( dword_77F7AC <= 128 )
    dword_77F7AC = 128;
  fld_364 = *(uint32_t *)(this + 868);
  if ( sub_699000(this + 844) >= fld_364 )
  {
    fld_3A42 = *(uint32_t *)(this + 932) + 1;
    fld_3A43 = *(uint32_t *)(this + 932) - 4 < 0;
    *(uint32_t *)(this + 932) = fld_3A42;
    if ( fld_3A43 != __OFSUB__(fld_3A42, 5) )
    {
      *(uint8_t *)(this + 857) = 0;
      *(uint8_t *)(this + 858) = 0;
      sub_698F90(this + 844, dword_6C38CC[*(uint32_t *)(this + 932)], 0);
      dword_77F7AC = 255;
    }
    else
    {
      v17 = sub_48C1C0(0);
      fld_2C = *(uint32_t *)(*(uint32_t *)(this + 44) + 468) + 128;
      v19 = v17 + 320;
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 836) + 12))(*(uint32_t *)(this + 836), 0);
      (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 836) + 40))(
        *(uint32_t *)(this + 836),
        v19,
        fld_2C,
        0);
      *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 836) + 28))(*(uint32_t *)(this + 836)) + 84) = 0;
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 836) + 92))(*(uint32_t *)(this + 836), v24);
      fld_68 = *(void **)(this + 104);
      v29 = 0;
      sub_4600B0(fld_68, 2, 0, (int)v24);
      Block2 = Block;
      v22 = Block == nullptr;
      *(uint32_t *)(this + 840) = -1;
      if ( !v22 )
        j__free(Block2);
    }
  }
}


// ------------------------------------------------------------
// 0x4271B0 sub_4271B0
// ------------------------------------------------------------
// 【播报层 · 组队双槽评价 + 空中连击横幅】i ∈ {0,1}：
//   +248[i] 达阈值 dword_6C38A4[i] → +400[i] = 5*(超出+1) 分 + 1500ms + 语音 "HK_STYLE"
//     + 串 496/497（sub_422E70 → sub_495A70）；
//   +312[i] 计数显示（档位图 10+11*档，id 131；计数 id 123；窗 +320[i]+24）；
//   +720 状态机 → 语音 "HK1_AIRIAL"/"HK2_AIRIAL"（dword_8F7A24+12 ∈ {4,6} 选 HK1）
//     + 图 108/109/110；+824 状态机 → 图 141/142。
void /*usercall*/ sub_4271B0(int pArg1@<ecx>, double fArg2@<st0>)
{
  int i; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int pObj3; // eax
  int v13; // edi
  int v14; // edi
  int v15; // eax
  char *psz; // edx
  int v17; // edi
  int v18; // eax
  int v19; // ebx
  int pObj6; // eax
  int pObj2; // eax
  int pObj4; // eax
  int v23; // edi
  int v24; // eax
  int pObj5; // eax
  int pObj; // eax
  int v27; // [esp+8h] [ebp-38h]
  int v28; // [esp+Ch] [ebp-34h]
  int v29; // [esp+10h] [ebp-30h]
  void *Block[4]; // [esp+18h] [ebp-28h] BYREF
  int v31; // [esp+28h] [ebp-18h]
  unsigned int v32; // [esp+2Ch] [ebp-14h]
  int dword_796E502; // [esp+30h] [ebp-10h]
  int v34; // [esp+3Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  for ( i = 0; i < 2; ++i )
  {
    if ( *(int *)(pArg1 + 4 * i + 248) >= 1 )
    {
      v4 = 28 * i + pArg1;
      v29 = *(uint32_t *)(v4 + 280);
      if ( sub_699000(v4 + 256) >= v29 )
      {
        v5 = *(uint32_t *)(pArg1 + 4 * i + 248);
        v6 = dword_6C38A4[i];
        if ( v5 >= v6 )
        {
          *(uint32_t *)(pArg1 + 4 * i + 400) = 5 * (v5 - v6 + 1);
          *(uint8_t *)(v4 + 421) = 0;
          *(uint8_t *)(v4 + 422) = 0;
          sub_698F90(v4 + 408, 1500, 0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
            dword_8F7C04,
            "HK_STYLE",
            -1,
            0,
            0);
        }
        if ( *(uint32_t *)(pArg1 + 4 * i + 248) >= dword_6C38A4[i] )
        {
          if ( i != 0 )
            sub_422E70(497);
          else
            sub_422E70(496);
          v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
          sub_495A70(dword_99FD58, *(uint32_t *)(pArg1 + 4 * i + 248), i != 0 ? 2 : 0, v7);
        }
        *(uint32_t *)(pArg1 + 4 * i + 248) = 0;
      }
    }
    if ( *(int *)(pArg1 + 312) >= 2 && *(int *)(pArg1 + 316) >= 1 )
      *(uint32_t *)(pArg1 + 316) = 0;
    if ( *(uint32_t *)(pArg1 + 4 * i + 312) >= dword_6C38AC[i] )
    {
      v8 = 515;
      v28 = 28 * i + pArg1 + 320;
      v9 = sub_699000(v28);
      if ( *(uint32_t *)(pArg1 + 4 * i + 312) == 2 )
      {
        if ( v9 < 250 )
        {
          sub_4049F0(110.0, 0.0, v9, 250, 1);
LABEL_26:
          v8 = (uint64_t)fArg2 + 510;
          goto LABEL_27;
        }
        if ( v9 < 300 )
        {
          v10 = v9 - 250;
LABEL_25:
          sub_4049F0(0.0, 5.0, v10, 50, 0);
          goto LABEL_26;
        }
      }
      else
      {
        if ( v9 < 50 )
        {
          sub_4049F0(5.0, 0.0, v9, 250, 1);
          goto LABEL_26;
        }
        if ( v9 < 100 )
        {
          v10 = v9 - 50;
          goto LABEL_25;
        }
      }
LABEL_27:
      v11 = *(uint32_t *)(pArg1 + 4 * i + 312);
      if ( v11 > 10 )
        v29 = (v11 > 20) + 1;
      else
        v29 = 0;
      pObj3 = sub_418DD0(11 * v29 + 10);
      if ( pObj3 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v8, 131, dword_79C0B0);
      sub_69A110(v8, 123, *(uint32_t *)(pArg1 + 4 * i + 312), -1);
      v13 = *(uint32_t *)(v28 + 24);
      if ( sub_699000(v28) >= v13 )
        *(uint32_t *)(pArg1 + 4 * i + 312) = 0;
      continue;
    }
  }
  if ( *(uint8_t *)(pArg1 + 720) == 1 )
  {
    v14 = *(uint32_t *)(pArg1 + 716);
    if ( sub_699000(pArg1 + 692) >= v14 )
    {
      *(uint8_t *)(pArg1 + 720) = 0;
      *(uint8_t *)(pArg1 + 677) = 0;
      *(uint8_t *)(pArg1 + 678) = 0;
      sub_698F90(pArg1 + 664, 125, 0);
      *(uint8_t *)(pArg1 + 721) = 1;
      *(uint32_t *)(pArg1 + 728) = 108;
      *(uint32_t *)(pArg1 + 724) = 0;
      v15 = *(uint32_t *)(dword_8F7A24 + 12);
      if ( v15 == 4 || (psz = "HK2_AIRIAL", v15 == 6) )
        psz = "HK1_AIRIAL";
      v31 = 0;
      v32 = 15;
      LOBYTE(Block[0]) = 0;
      sub_4015C0(psz, strlen(psz));
      v34 = 0;
      (*(void (/*thiscall*/ **)(int, void **, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
        dword_8F7C04,
        Block,
        -1,
        0,
        0);
      v34 = -1;
      if ( v32 >= 0x10 )
        j__free(Block[0]);
    }
  }
  if ( *(uint8_t *)(pArg1 + 824) == 1 )
  {
    v17 = *(uint32_t *)(pArg1 + 820);
    if ( sub_699000(pArg1 + 796) >= v17 )
    {
      v18 = *(uint32_t *)(pArg1 + 828);
      if ( v18 != 0 )
      {
        switch ( v18 )
        {
          case 1:
            *(uint32_t *)(pArg1 + 828) = 2;
            *(uint32_t *)(pArg1 + 832) = 142;
            *(uint8_t *)(pArg1 + 809) = 0;
            *(uint8_t *)(pArg1 + 810) = 0;
            sub_698F90(pArg1 + 796, dword_6C38E0[*(uint32_t *)(pArg1 + 828)], 0);
            break;
          case 2:
            *(uint32_t *)(pArg1 + 828) = 3;
            *(uint8_t *)(pArg1 + 809) = 0;
            *(uint8_t *)(pArg1 + 810) = 0;
            sub_698F90(pArg1 + 796, dword_6C38E0[*(uint32_t *)(pArg1 + 828)], 0);
            break;
          case 3:
            *(uint32_t *)(pArg1 + 828) = 0;
            *(uint8_t *)(pArg1 + 824) = 0;
            break;
          default:
            break;
        }
      }
      else
      {
        *(uint32_t *)(pArg1 + 828) = 1;
        *(uint32_t *)(pArg1 + 832) = 141;
        *(uint8_t *)(pArg1 + 809) = 0;
        *(uint8_t *)(pArg1 + 810) = 0;
        sub_698F90(pArg1 + 796, dword_6C38E0[*(uint32_t *)(pArg1 + 828)], 0);
      }
    }
    Block[0] = (void *)134;
    Block[1] = (void *)135;
    Block[2] = (void *)136;
    Block[3] = (void *)137;
    v31 = 138;
    v32 = 139;
    sub_491530(2, 0);
    v19 = *(uint32_t *)(sub_418DD0(*(&v27 + 2 * *(uint32_t *)(pArg1 + 756))) + 20);
    pObj6 = sub_418DD0(*(&v27 + 2 * *(uint32_t *)(pArg1 + 756)));
    if ( pObj6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, 640 - v19, 145, dword_79C0B0);
    sub_491630(2);
    pObj2 = sub_418DD0(*(&v28 + 2 * *(uint32_t *)(pArg1 + 756)));
    if ( pObj2 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, 640 - v19, 145, dword_79C0B0);
    if ( *(int *)(pArg1 + 828) <= 2 && *(uint8_t *)(pArg1 + 824) == 1 )
    {
      sub_491530(2, 0);
      pObj4 = sub_418DD0(*(uint32_t *)(pArg1 + 832));
      if ( pObj4 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 200, 155, dword_79C0B0);
      sub_491630(2);
    }
  }
  if ( *(uint8_t *)(pArg1 + 721) == 1 )
  {
    v23 = *(uint32_t *)(pArg1 + 688);
    if ( sub_699000(pArg1 + 664) >= v23 )
    {
      v24 = *(uint32_t *)(pArg1 + 724);
      if ( v24 != 0 )
      {
        switch ( v24 )
        {
          case 1:
            *(uint32_t *)(pArg1 + 724) = 2;
            *(uint32_t *)(pArg1 + 728) = 110;
            *(uint8_t *)(pArg1 + 677) = 0;
            *(uint8_t *)(pArg1 + 678) = 0;
            sub_698F90(pArg1 + 664, dword_6C38E0[*(uint32_t *)(pArg1 + 724)], 0);
            break;
          case 2:
            *(uint32_t *)(pArg1 + 724) = 3;
            *(uint8_t *)(pArg1 + 677) = 0;
            *(uint8_t *)(pArg1 + 678) = 0;
            sub_698F90(pArg1 + 664, dword_6C38E0[*(uint32_t *)(pArg1 + 724)], 0);
            break;
          case 3:
            *(uint32_t *)(pArg1 + 724) = 0;
            *(uint8_t *)(pArg1 + 721) = 0;
            break;
          default:
            break;
        }
      }
      else
      {
        *(uint32_t *)(pArg1 + 724) = 1;
        *(uint32_t *)(pArg1 + 728) = 109;
        *(uint8_t *)(pArg1 + 677) = 0;
        *(uint8_t *)(pArg1 + 678) = 0;
        sub_698F90(pArg1 + 664, dword_6C38E0[*(uint32_t *)(pArg1 + 724)], 0);
      }
    }
    pObj5 = sub_418DD0(100);
    if ( pObj5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, 555, 200, dword_79C0B0);
    if ( *(int *)(pArg1 + 724) <= 2 && *(uint8_t *)(pArg1 + 721) == 1 )
    {
      sub_491530(2, 0);
      pObj = sub_418DD0(*(uint32_t *)(pArg1 + 728));
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, 415, 195, dword_79C0B0);
      sub_491630(2);
    }
  }
}


// ------------------------------------------------------------
// 0x4278D0 sub_4278D0
// ------------------------------------------------------------
// 【评价计数写入器】a2 选槽（a2=1 → +756 快照 + +824 状态机启动）—— 连击宿主
//   0x428050 收尾回调（sub_4278D0(0,0)）。
void /*thiscall*/ sub_4278D0(int this, int nArg2, int nArg3)
{
  int v4; // eax
  bool v5; // zf
  char *v6; // eax
  void *p_Block; // eax
  void *Block; // [esp+Ch] [ebp-28h] BYREF
  unsigned int v9; // [esp+20h] [ebp-14h]
  int dword_796E502; // [esp+24h] [ebp-10h]
  int v11; // [esp+30h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 )
    {
      *(uint32_t *)(this + 756) = nArg3;
      if ( *(uint8_t *)(this + 824) == 0 )
      {
        *(uint8_t *)(this + 809) = 0;
        *(uint8_t *)(this + 810) = 0;
        sub_698F90(this + 796, 125, 0);
        *(uint8_t *)(this + 824) = 1;
        *(uint32_t *)(this + 832) = 140;
        *(uint32_t *)(this + 828) = 0;
        v4 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v4 == 4 || (v5 = v4 == 6, v6 = "R_HK2_DOUBLE", v5) )
          v6 = "R_HK1_DOUBLE";
        sub_401710(v6);
        p_Block = Block;
        v11 = 0;
        if ( v9 < 0x10 )
          p_Block = &Block;
        (*(void (/*thiscall*/ **)(int, void *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
          dword_8F7C04,
          p_Block,
          -1,
          0,
          0);
        if ( v9 >= 0x10 )
          j__free(Block);
      }
    }
  }
  else if ( *(uint8_t *)(this + 721) == 0 )
  {
    *(uint8_t *)(this + 705) = 0;
    *(uint8_t *)(this + 706) = 0;
    sub_698F90(this + 692, 1000, 0);
    *(uint8_t *)(this + 720) = 1;
  }
}



// ------------------------------------------------------------
// 0x427A00 sub_427A00
// ------------------------------------------------------------
HGDIOBJ /*usercall*/ sub_427A00@<eax>(int pArg1@<ecx>, double fArg2@<st0>)
{
  int v2; // esi
  int v3; // edi
  HGDIOBJ result; // eax
  int v5; // edi
  int v6; // eax
  int pObj; // eax
  int v8; // eax
  void *v9; // esi
  int v10; // esi
  int v11; // eax
  int pObj2; // eax
  uint8_t v13[4]; // [esp+8h] [ebp-68h] BYREF
  int v14; // [esp+Ch] [ebp-64h]
  int v15; // [esp+14h] [ebp-5Ch]
  int v16; // [esp+18h] [ebp-58h]
  int v17; // [esp+1Ch] [ebp-54h]
  int v18; // [esp+20h] [ebp-50h]
  int v19; // [esp+24h] [ebp-4Ch]
  int v20; // [esp+28h] [ebp-48h]
  int v21; // [esp+2Ch] [ebp-44h]
  int v22; // [esp+30h] [ebp-40h]
  HGDIOBJ ho; // [esp+34h] [ebp-3Ch]
  int dword_99FCCC2; // [esp+38h] [ebp-38h]
  int pArg12; // [esp+3Ch] [ebp-34h]
  int v26; // [esp+40h] [ebp-30h]
  void *Block; // [esp+48h] [ebp-28h]
  int v28; // [esp+58h] [ebp-18h]
  unsigned int v29; // [esp+5Ch] [ebp-14h]
  int dword_796E502; // [esp+60h] [ebp-10h]
  int v31; // [esp+6Ch] [ebp-4h]

  v2 = pArg1 + 872;
  pArg12 = pArg1;
  v3 = *(uint32_t *)(pArg1 + 896);
  dword_796E502 = dword_796E50;
  result = (HGDIOBJ)sub_699000(pArg1 + 872);
  if ( (int)result >= v3 )
    return result;
  v5 = 10;
  v6 = sub_699000(v2);
  if ( v6 < 250 )
  {
    sub_4049F0(-110.0, 0.0, v6, 250, 1);
LABEL_6:
    v5 = (uint64_t)fArg2 + 5;
    goto LABEL_7;
  }
  if ( v6 < 300 )
  {
    sub_4049F0(0.0, 5.0, v6 - 250, 50, 0);
    goto LABEL_6;
  }
LABEL_7:
  pObj = sub_418DD0(104);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v5, 218, dword_79C0B0);
  dword_99FCCC2 = dword_99FCCC;
  v13[0] = 0;
  v13[1] = 0;
  v13[3] = 0;
  v15 = 0;
  v16 = 6;
  v17 = 12;
  v18 = 0;
  v19 = 1600;
  v20 = 0;
  v21 = 0;
  v22 = 0;
  ho = nullptr;
  v13[2] = 1;
  v14 = -16777216;
  v8 = *(uint32_t *)dword_79C0B0;
  v31 = 0;
  (*(void (/*thiscall*/ **)(int, uint8_t *))(v8 + 72))(dword_79C0B0, v13);
  v26 = 0;
  v9 = (void *)sub_422E70(498);
  v29 = 15;
  v28 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(v9, strlen((const char *)v9));
  LOBYTE(v31) = 1;
  if ( dword_99FEC0 != 0 )
  {
    v10 = sub_48F690(*(uint32_t *)(pArg12 + 900));
    if ( v10 != 0 && v10 != -16 )
    {
      if ( *(uint32_t *)(v10 + 40) < 0x10u )
        v11 = v10 + 20;
      else
        v11 = *(uint32_t *)(v10 + 20);
      (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v5 + 33,
        204,
        -16776961,
        v11);
    }
  }
  else
  {
    v10 = v26;
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  if ( v10 != 0 )
  {
    pObj2 = sub_42B340(v10);
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)pObj2 + 384))(pObj2, v5 + 10, 191, 24, 24, 1065353216);
  }
  if ( v29 >= 0x10 )
    j__free(Block);
  result = ho;
  v28 = 0;
  LOBYTE(Block) = 0;
  v29 = 15;
  if ( ho != nullptr )
    return (HGDIOBJ)DeleteObject(ho);
  return result;
}


// ------------------------------------------------------------
// 0x427C20 sub_427C20
// ------------------------------------------------------------
void /*thiscall*/ sub_427C20(uint32_t *this)
{
  int i; // edi
  int pThis_7; // esi
  char *psz; // edx
  void *p_Block; // eax
  int v6; // [esp+10h] [ebp-30h]
  void *Block; // [esp+18h] [ebp-28h] BYREF
  int v8; // [esp+28h] [ebp-18h]
  unsigned int v9; // [esp+2Ch] [ebp-14h]
  int dword_796E502; // [esp+30h] [ebp-10h]
  int v11; // [esp+3Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  v6 = *(uint32_t *)(dword_8F7A24 + 12);
  for ( i = 0; i < 8; ++i )
  {
    pThis_7 = *(this + 7 * i + 240);
    if ( sub_699000((int)(this + 7 * i + 234)) >= pThis_7 && *((uint8_t *)this + i + 1160) == 1 )
    {
      v9 = 15;
      v8 = 0;
      LOBYTE(Block) = 0;
      sub_4015C0((void *)szPassword, 0);
      v11 = 0;
      switch ( i )
      {
        case 0:
          if ( v6 == 4 || (psz = "HK2_OVERKILL", v6 == 6) )
            psz = "HK1_OVERKILL";
          goto LABEL_24;
        case 1:
          if ( v6 == 4 || (psz = "HK2_BACK_ATK", v6 == 6) )
            psz = "HK1_BACK_ATK";
          goto LABEL_24;
        case 2:
          if ( v6 == 4 || (psz = "HK2_COUNTER", v6 == 6) )
            psz = "HK1_COUNTER";
          goto LABEL_24;
        case 4:
          if ( v6 == 4 || (psz = "HK2_FINISH_01", v6 == 6) )
            psz = "HK1_FINISH_01";
          goto LABEL_24;
        case 5:
          if ( v6 == 4 || (psz = "R_HK2_KILL", v6 == 6) )
            psz = "R_HK1_KILL";
LABEL_24:
          sub_4015C0(psz, strlen(psz));
          break;
        default:
          break;
      }
      p_Block = Block;
      if ( v9 < 0x10 )
        p_Block = &Block;
      (*(void (/*thiscall*/ **)(int, void *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
        dword_8F7C04,
        p_Block,
        -1,
        0,
        0);
      *((uint8_t *)this + i + 1160) = 0;
      v11 = -1;
      if ( v9 >= 0x10 )
        j__free(Block);
      v9 = 15;
      v8 = 0;
      LOBYTE(Block) = 0;
    }
  }
}



// ------------------------------------------------------------
// 0x427E20 sub_427E20
// ------------------------------------------------------------
void /*noreturn*/ sub_427E20()
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
// 0x427E90 sub_427E90
// ------------------------------------------------------------
// 【HUD 逐帧更新分发器】依次调 0x4271B0(组队双槽) → 0x426080(被击) → 0x426200(横幅)
//   → 0x425DA0(技巧) → 0x425F10(风格) —— 三轴动画唯一 tick 汇聚点。
HGDIOBJ /*usercall*/ sub_427E90@<eax>(int *pDwArg1@<ecx>, double fArg2@<st0>)
{
  HGDIOBJ result; // eax
  int pObj2; // eax
  int pObj; // edi
  int v6; // eax
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7

  result = (HGDIOBJ)pDwArg1[11];
  if ( result != nullptr )
  {
    result = (HGDIOBJ)pDwArg1[26];
    if ( result != nullptr )
    {
      pObj2 = pDwArg1[13];
      pObj = 0;
      if ( pObj2 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )
        pObj = pDwArg1[13];
      sub_48CA20(5, 0);
      sub_45E740(5);
      sub_48CA20(5, 1);
      sub_48CA20(4, 0);
      sub_45E740(4);
      sub_48CA20(4, 1);
      sub_48CA20(3, 0);
      sub_45E740(3);
      sub_48CA20(3, 1);
      sub_48CA20(2, 0);
      sub_45E740(2);
      sub_48CA20(2, 1);
      if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 776))(pObj, 5) != 0 )
        sub_496DD0(1);
      sub_48CA20(1, 0);
      sub_45E740(1);
      sub_48CA20(1, 1);
      sub_48CA20(0, 0);
      sub_45E740(0);
      sub_48CA20(0, 1);
      if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 776))(pObj, 5) != 0 )
      {
        sub_496DD0(0);
      }
      else
      {
        v6 = *(uint32_t *)(*((uint32_t *)dword_8F8528 + 609) + 4);
        if ( v6 == 8 || v6 == 9 )
          sub_459190(0);
      }
      sub_4271B0((int)pDwArg1, fArg2);
      sub_426080((int)pDwArg1, v7);
      sub_426200((int)pDwArg1);
      sub_426D20((int)pDwArg1);
      sub_425DA0((int)pDwArg1, v8);
      sub_425F10((int)pDwArg1, v9);
      sub_425A30(pDwArg1);
      sub_424A60(pDwArg1);
      result = *(HGDIOBJ *)(dword_8F7A24 + 12);
      if ( result == (HGDIOBJ)4 || result == (HGDIOBJ)6 )
        return sub_427A00((int)pDwArg1, v10);
    }
  }
  return result;
}



// ============================================================
// §12 连击宿主与 Stage（0x428050-0x428AD0）
//   0x428050 连击宿主（研究 §9）：阈值分级语音 R_HK2_1/2/3GOOD + 屏幕脉冲 sub_424530
// ============================================================
// ------------------------------------------------------------
// 0x428050 sub_428050
// ------------------------------------------------------------
// ★【连击宿主】（研究 §9）a2+1 槽逐个：清 +269/+270 标志 + 1500ms 钟；计数 ++ 达
//   dword_6C38AC[v4] → +78 快照 + 3000ms 钟；v4==1 时 sub_424530 屏幕脉冲 +
//   sub_4278D0(0,0) 收尾。阈值分级语音：≥20&≥8 → R_HK2_1GOOD；≥10&≥4 → R_HK2_2GOOD；
//   ≥2&≥2 → R_HK2_3GOOD（sub_432EA0）。
char /*thiscall*/ sub_428050(int *this, int pArg2, char pszArg3, float *pArg4)
{
  int v4; // ebx
  int *pThis_7; // eax
  int fld_e62; // eax
  int v8; // edx
  int v10; // [esp+Ch] [ebp-4h]
  int *pThis_72; // [esp+18h] [ebp+8h]

  v4 = 0;
  v10 = pArg2 + 1;
  if ( pArg2 + 1 <= 0 )
  {
LABEL_8:
    fld_e62 = *(this + 62);
    if ( fld_e62 < 20 || *(this + 63) < 8 )
    {
      if ( fld_e62 < 10 || *(this + 63) < 4 )
      {
        if ( fld_e62 >= 2 && *(this + 63) >= 2 )
          LOBYTE(fld_e62) = (uint8_t)sub_432EA0("R_HK2_3GOOD", -1, 0, 0);
      }
      else
      {
        LOBYTE(fld_e62) = (uint8_t)sub_432EA0("R_HK2_2GOOD", -1, 0, 0);
      }
    }
    else
    {
      LOBYTE(fld_e62) = (uint8_t)sub_432EA0("R_HK2_1GOOD", -1, 0, 0);
    }
  }
  else
  {
    while ( 1 )
    {
      pThis_7 = this + 7 * v4;
      pThis_72 = pThis_7;
      *((uint8_t *)pThis_7 + 269) = 0;
      *((uint8_t *)pThis_7 + 270) = 0;
      sub_698F90((int)(pThis_7 + 64), 1500, 0);
      LOBYTE(fld_e62) = pszArg3;
      if ( pszArg3 != 0 )
        break;
      v8 = *(this + v4 + 62) + 1;
      *(this + v4 + 62) = v8;
      if ( v8 >= dword_6C38AC[v4] )
      {
        *(this + v4 + 78) = v8;
        *((uint8_t *)pThis_72 + 333) = 0;
        *((uint8_t *)pThis_72 + 334) = 0;
        sub_698F90((int)(pThis_72 + 80), 3000, 0);
      }
      if ( v4 == 1 )
      {
        sub_424530(
          0x40000000,
          300,
          1000,
          (uint64_t)(pArg4[3] * 0.5 + *pArg4),
          (uint64_t)(pArg4[4] * 0.5 + pArg4[1]),
          (uint64_t)(pArg4[5] * 0.5 + pArg4[2]),
          1);
        sub_4278D0(0, 0);
      }
      if ( ++v4 >= v10 )
        goto LABEL_8;
    }
  }
  return fld_e62;
}



// ------------------------------------------------------------
// 0x4281D0 sub_4281D0
// ------------------------------------------------------------
char /*thiscall*/ sub_4281D0(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x7FFFFFF )
    sub_427E20(this);
  pMem = (char *)operator new(32 * uArg2);
  *(this + 3) = &pMem[32 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x428220 sub_428220
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_428220(int this, int Src, unsigned int uArg3, int *pDwArg4)
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
      sub_427E20(this);
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
// 0x428400 CNRDStage__vmt0
// ------------------------------------------------------------
HGDIOBJ /*userpurge*/ CNRDStage__vmt0@<eax>(int *pDwArg1@<ecx>, double fArg2@<st0>, void *pArg3)
{
  HGDIOBJ result; // eax

  result = pArg3;
  if ( pArg3 == (void *)pDwArg1[9] )
    return sub_427E90(pDwArg1, fArg2);
  if ( pArg3 == (void *)pDwArg1[10] && pDwArg1[27] != 0 )
    return (HGDIOBJ)sub_472B80();
  return result;
}



// ------------------------------------------------------------
// 0x428430 sub_428430
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_428430(int *this, int *pDwArg2)
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
    return sub_428220((int)this, *(this + 2), 1u, pDwArg2);
  fld_e22 = (int *)*(this + 2);
  *fld_e22 = *pDwArg2;
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x428480 sub_428480
// ------------------------------------------------------------
int /*thiscall*/ sub_428480(int this)
{
  char *fld_4; // esi
  int result; // eax
  char *i; // edi

  fld_4 = *(char **)(this + 4);
  result = 0;
  if ( fld_4 != nullptr )
  {
    for ( i = *(char **)(this + 8); fld_4 != i; fld_4 += 32 )
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
// 0x4284C0 sub_4284C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4284C0(uint32_t *this, int pArg2, int nArg3)
{
  int nArg32; // esi
  int fld_e28; // eax
  int fld_e29; // ecx
  int fld_e11; // edx
  int fld_e27; // eax
  int fld_e272; // eax
  int fld_e112; // ecx
  int v11; // esi
  int pObj; // ebx
  int v13; // ecx
  unsigned int v14; // esi
  int fld_e265; // edx
  int v16; // ecx
  int fld_e262; // ecx
  int fld_e282; // eax
  int fld_e329; // eax
  int pObj2; // ebx
  int fld_e263; // ecx
  unsigned int v22; // ebx
  int fld_e264; // ecx
  int v24; // edx
  int result; // eax
  int v26; // edx
  int fld_e292; // [esp+20h] [ebp-44h]
  int fld_e283; // [esp+24h] [ebp-40h]
  int fld_e113; // [esp+28h] [ebp-3Ch]
  int v30; // [esp+2Ch] [ebp-38h]
  int i; // [esp+34h] [ebp-30h]
  uint32_t v32[3]; // [esp+38h] [ebp-2Ch] BYREF
  int v33; // [esp+44h] [ebp-20h] BYREF
  int v34; // [esp+48h] [ebp-1Ch] BYREF
  int fld_e26; // [esp+54h] [ebp-10h]
  int v36; // [esp+60h] [ebp-4h]
  int v37; // [esp+6Ch] [ebp+8h]

  nArg32 = nArg3;
  fld_e28 = *(this + 28);
  fld_e29 = *(this + 29);
  fld_e11 = *(this + 11);
  fld_e283 = fld_e28;
  fld_e26 = *(this + 26);
  fld_e27 = *(this + 27);
  *(this + 28) = pArg2;
  *(this + 29) = nArg32;
  fld_e292 = fld_e29;
  fld_e113 = fld_e11;
  sub_425500(*(uint32_t *)(dword_99FBC4 + 4 * (pArg2 + nArg32 * *(uint32_t *)(*(uint32_t *)(fld_e27 + 168) + 8 * dword_99FB78))));
  fld_e272 = *(uint32_t *)(dword_99FBD4 + 4 * (pArg2 + nArg32 * *(uint32_t *)(*(uint32_t *)(*(this + 27) + 168) + 8 * dword_99FB78)));
  *(this + 26) = fld_e272;
  if ( fld_e272 != 0 )
    *(uint32_t *)(fld_e272 + 132) = this;
  fld_e112 = *(this + 11);
  if ( fld_e112 != 0 )
    sub_48E870(fld_e112, *(this + 26));
  *(this + 329) = 0;
  for ( i = 16; i < 32; i += 4 )
  {
    v11 = *(uint32_t *)(i + dword_8F850C);
    v30 = v11;
    if ( v11 != 0 )
    {
      pObj = *(uint32_t *)(v11 + 196);
      if ( pObj != 0 )
      {
        if ( fld_e26 != 0 )
        {
          if ( (uint8_t)sub_45E680(pObj) == 0 )
            continue;
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1196))(pObj) != 0 )
        {
          continue;
        }
        v36 = 0;
        if ( fld_e26 != 0 )
        {
          if ( *(this + 26) != 0 )
          {
            v13 = *(uint32_t *)(fld_e26 + 120);
            v37 = v13 != 0 ? (*(uint32_t *)(fld_e26 + 124) - v13) >> 2 : 0;
            v14 = 0;
            if ( v37 > 0 )
            {
              fld_e265 = fld_e26;
              do
              {
                v16 = *(uint32_t *)(fld_e265 + 120);
                if ( v16 != 0 && v14 < (*(uint32_t *)(fld_e265 + 124) - v16) >> 2 )
                {
                  v32[0] = *(uint32_t *)(v16 + 4 * v14);
                  if ( v32[0] != 0 && *(uint32_t *)(v32[0] + 668) == pObj && *(uint32_t *)(v32[0] + 672) != 0 )
                  {
                    sub_428430(v32);
                    fld_e265 = fld_e26;
                  }
                }
                ++v14;
              }
              while ( (int)v14 < v37 );
            }
          }
          sub_45F1E0(pObj);
          v11 = v30;
        }
        fld_e262 = *(this + 26);
        if ( fld_e262 != 0 )
          sub_45FE80(fld_e262, (int)this, 273, *(uint16_t *)(v11 + 4), pObj, 0, 0);
        v33 = 0;
        v34 = 0;
        if ( fld_e113 != 0 )
        {
          fld_e282 = *(this + 28);
          if ( fld_e283 >= fld_e282 )
          {
            if ( fld_e283 <= fld_e282 )
              *(this + 329) = (fld_e292 >= *(this + 29)) + 2;
            else
              *(this + 329) = 1;
          }
          else
          {
            *(this + 329) = 0;
          }
          sub_48C2A0(
            (uint32_t *)*(this + 11),
            &v33,
            &v34,
            *(this + 329),
            pObj,
            *(uint32_t *)*(this + 11) * *(uint16_t *)(v11 + 4));
        }
        else
        {
          sub_48C330((uint32_t *)*(this + 11), &v33, &v34, pObj, *(uint32_t *)*(this + 11) * *(uint16_t *)(v11 + 4));
        }
        if ( fld_e26 != 0 && *(this + 26) != 0 )
          v32[2] = 0;
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 112))(pObj, v33, v34, 0);
        fld_e329 = *(this + 329);
        if ( fld_e329 != 0 )
        {
          if ( fld_e329 == 1 )
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 148))(pObj, 0);
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 148))(pObj, 1);
        }
        (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 228))(pObj, 2, -1, 0);
        pObj2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1120))(pObj);
        if ( pObj2 != 0 )
        {
          if ( fld_e26 != 0 )
            sub_45F1E0(pObj2);
          fld_e263 = *(this + 26);
          if ( fld_e263 != 0 )
            sub_45FE80(fld_e263, (int)this, 65, *(uint16_t *)(v11 + 4), pObj2, 0, 0);
          (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj2 + 228))(pObj2, 2, -1, 0);
        }
        v36 = -1;
      }
    }
  }
  if ( fld_e113 != 0 )
    *(uint8_t *)(fld_e113 + 472) = 0;
  sub_44F080(dword_8F8528);
  v22 = 0;
  while ( 1 )
  {
    fld_e264 = *(this + 26);
    v24 = *(uint32_t *)(fld_e264 + 8);
    result = v24 != 0 ? (*(uint32_t *)(fld_e264 + 12) - v24) >> 2 : 0;
    if ( (int)v22 >= result )
      break;
    v26 = *(uint32_t *)(fld_e264 + 8);
    if ( v26 != 0 && v22 < (*(uint32_t *)(fld_e264 + 12) - v26) >> 2 )
    {
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v26 + 4 * v22) + 320))(*(uint32_t *)(v26 + 4 * v22));
      ++v22;
    }
    else
    {
      (*(void (**)(void))(MEMORY[0] + 320))();
      ++v22;
    }
  }
  return result;
}


// ============================================================
// §13 战场演出大函数与粒子生成器（0x428AD0-0x429F40）
//   CNRDObjectParticleCreater 虚表家族；0x428F30 = 粒子构造（0x431590 转职演出复用）
// ============================================================
// ------------------------------------------------------------
// 0x428AD0 sub_428AD0
// ------------------------------------------------------------
void /*thiscall*/ sub_428AD0(uint32_t *this)
{
  int v1; // eax
  uint32_t *pThis; // edi
  int fld_e26; // eax
  int i; // esi
  int v5; // ebx
  int pObj4; // ecx
  int v7; // ebx
  int v8; // esi
  int v9; // eax
  char *pObj3; // edi
  int v11; // eax
  int pObj5; // esi
  int v13; // eax
  int v14; // ecx
  char *v15; // edx
  char *v16; // esi
  void *Block2; // ebx
  int v18; // eax
  int v19; // esi
  int v20; // ecx
  BOOL v21; // ecx
  unsigned int j; // ebx
  int v23; // ecx
  int v24; // edx
  int v25; // eax
  int v26; // edx
  int pObj; // ecx
  int v28; // ecx
  int v29; // edx
  int pObj2; // esi
  int v31; // eax
  char v32; // al
  int dword_8F850C2; // esi
  int v34; // esi
  int v35; // [esp-10h] [ebp-54h]
  int v36; // [esp-10h] [ebp-54h]
  int v37; // [esp-Ch] [ebp-50h]
  int v38; // [esp-Ch] [ebp-50h]
  void *pBuf[4]; // [esp+4h] [ebp-40h] BYREF
  void *Block; // [esp+18h] [ebp-2Ch]
  char *v41; // [esp+1Ch] [ebp-28h]
  int v42; // [esp+20h] [ebp-24h]
  int v43; // [esp+24h] [ebp-20h] BYREF
  int v44; // [esp+28h] [ebp-1Ch]
  int v45; // [esp+2Ch] [ebp-18h]
  int v46; // [esp+30h] [ebp-14h]
  uint32_t *pThis2; // [esp+34h] [ebp-10h]
  int v48; // [esp+40h] [ebp-4h]

  v1 = *(uint32_t *)(dword_8F7A24 + 12);
  pThis = this;
  pThis2 = this;
  if ( v1 == 3 )
  {
    fld_e26 = *(this + 26);
    if ( fld_e26 != 0 && *(this + 11) != 0 )
    {
      if ( *(uint8_t *)(fld_e26 + 152) != 0 )
      {
        *(this + 314) = 1;
        return;
      }
      if ( (uint8_t)sub_423AE0(*(this + 28), *(this + 29)) == 0 )
      {
        Block = nullptr;
        v41 = nullptr;
        v42 = 0;
        v48 = 0;
        for ( i = 16; i < 32; i += 4 )
        {
          v43 = *(uint32_t *)(i + dword_8F850C);
          v5 = v43;
          if ( v43 != 0 )
          {
            pObj4 = *(uint32_t *)(v43 + 196);
            if ( pObj4 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 724))(pObj4) == 0 )
            {
              sub_428430(&v43);
              (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v5 + 196) + 1228))(*(uint32_t *)(v5 + 196), 4);
            }
          }
        }
        v7 = 0;
        memset(pBuf, 0, sizeof(pBuf));
        v8 = 400;
        v46 = 0;
        v45 = 4;
        v44 = 400;
        do
        {
          if ( sub_48C220((uint8_t *)pThis[11], v7) )
          {
            v9 = pThis[11];
            pObj3 = (char *)Block;
            v11 = v8 + v9;
            v43 = v11;
            if ( Block != v41 )
            {
              while ( 1 )
              {
                pObj5 = *(uint32_t *)(*(uint32_t *)pObj3 + 196);
                v37 = v11;
                v35 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 124))(pObj5);
                v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 120))(pObj5);
                if ( (uint8_t)sub_48C0A0(v13, v35, v37) == 1 )
                {
                  v14 = pThis2[314];
                  v15 = (char *)pBuf[v7] + 1;
                  pBuf[v7] = v15;
                  v16 = v15;
                  if ( v14 != 1 )
                    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(*(uint32_t *)pObj3 + 196) + 1228))(
                      *(uint32_t *)(*(uint32_t *)pObj3 + 196),
                      v7);
                  if ( (int)v16 > v46 )
                  {
                    ++v46;
                    v45 = v7;
                  }
                }
                pObj3 += 4;
                if ( pObj3 == v41 )
                  break;
                v11 = v43;
              }
              v8 = v44;
            }
            pThis = pThis2;
          }
          v8 += 16;
          ++v7;
          v44 = v8;
        }
        while ( v8 < 464 );
        Block2 = Block;
        if ( Block != nullptr )
          v18 = (v41 - (uint8_t *)Block) >> 2;
        else
          v18 = 0;
        v19 = v46;
        v46 = v18 == v46;
        if ( Block != nullptr )
          v20 = (v41 - (uint8_t *)Block) >> 2;
        else
          v20 = 0;
        v21 = (int)(uint64_t)((double)(unsigned int)v20 * 0.5 + 1.0) <= v19;
        v43 = 0;
        v44 = v21;
        if ( v21 )
        {
          for ( j = 0; ; ++j )
          {
            v23 = pThis[26];
            v24 = *(uint32_t *)(v23 + 8);
            v25 = v24 != 0 ? (*(uint32_t *)(v23 + 12) - v24) >> 2 : 0;
            if ( (int)j >= v25 )
              break;
            v26 = *(uint32_t *)(v23 + 8);
            if ( v26 != 0 && j < (*(uint32_t *)(v23 + 12) - v26) >> 2 )
              pObj = *(uint32_t *)(v26 + 4 * j);
            else
              pObj = 0;
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 289) != 0 )
            {
              v28 = pThis[26];
              v29 = *(uint32_t *)(v28 + 8);
              if ( v29 != 0 && j < (*(uint32_t *)(v28 + 12) - v29) >> 2 )
                pObj2 = *(uint32_t *)(v29 + 4 * j);
              else
                pObj2 = 0;
              v38 = pThis2[11] + 16 * (v45 + 25);
              v36 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 124))(pObj2);
              v31 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);
              v32 = sub_48C0A0(v31, v36, v38);
              pThis = pThis2;
              if ( v32 == 1 )
              {
                v43 = 1;
                break;
              }
            }
          }
          Block2 = Block;
          v21 = v44;
        }
        switch ( pThis[314] )
        {
          case 0:
            if ( v46 == 1 )
              goto LABEL_59;
            if ( v21 )
            {
              sub_698F90((int)(pThis + 315), 0, 0);
              pThis[314] = 2;
            }
            goto LABEL_74;
          case 1:
            if ( !v21 )
              goto LABEL_61;
            goto LABEL_74;
          case 2:
            if ( v46 == 1 )
              goto LABEL_59;
            if ( v21 )
            {
              if ( v21 && sub_699000((int)(pThis + 315)) > 5000 )
              {
LABEL_59:
                sub_698F90((int)(pThis + 322), 0, 0);
                pThis[314] = 3;
              }
            }
            else
            {
LABEL_61:
              *((uint8_t *)pThis + 1273) = 0;
              *((uint8_t *)pThis + 1274) = 0;
              *((uint8_t *)pThis + 1301) = 0;
              *((uint8_t *)pThis + 1302) = 0;
              pThis[314] = 0;
            }
LABEL_74:
            if ( Block2 != nullptr )
              j__free(Block2);
            return;
          case 3:
            if ( v43 != 0 )
            {
              if ( sub_699000((int)(pThis + 322)) > 2000 )
                pThis[314] = 4;
            }
            else
            {
              pThis[314] = 4;
            }
            goto LABEL_74;
          case 4:
            dword_8F850C2 = dword_8F850C;
            if ( sub_456480(dword_8F850C) == -1 )
              v34 = 0;
            else
              v34 = *(uint32_t *)(dword_8F850C2 + 4 * sub_456480(dword_8F850C2) + 16);
            if ( v34 == sub_429830((uint16_t)word_77F804) )
              sub_48C680(v45);
            goto LABEL_74;
          default:
            goto LABEL_74;
        }
      }
    }
  }
}


// ------------------------------------------------------------
// 0x428F30 sub_428F30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_428F30(uint32_t *this, int nArg2, int nArg3)
{
  sub_425120();
  *this = &vftbl_CNRDObjectParticleCreater;
  *(this + 63) = 0;
  *(this + 64) = 0;
  *(this + 65) = 0;
  *(this + 74) = 15;
  *(this + 73) = 0;
  *((uint8_t *)this + 276) = 0;
  sub_498190(this);
  sub_497E40(szPassword, nArg2, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x428FC0 CNRDObjectParticleCreater__vmt60
// ------------------------------------------------------------
int /*thiscall*/ CNRDObjectParticleCreater__vmt60(uint32_t *this, int nArg2)
{
  *(this + 59) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x428FD0 CNRDObjectParticleCreater__vmt68
// ------------------------------------------------------------
int /*thiscall*/ CNRDObjectParticleCreater__vmt68(uint32_t *this, int nArg2)
{
  *(this + 60) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x428FE0 ?GetIScheduler@SchedulerBase@details@Concurrency@@QAEPAUIScheduler@3@XZ
// ------------------------------------------------------------
struct Concurrency::IScheduler */*thiscall*/ Concurrency::details::SchedulerBase::GetIScheduler(
        Concurrency::details::SchedulerBase *this)
{
  return *((struct Concurrency::IScheduler **)this + 60);
}



// ------------------------------------------------------------
// 0x428FF0 CNRDObjectParticleCreater__vmt70
// ------------------------------------------------------------
int /*thiscall*/ CNRDObjectParticleCreater__vmt70(uint32_t *this, int nArg2)
{
  *(this + 67) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x429000 CNRDObjectParticleCreater__vmt74
// ------------------------------------------------------------
int /*thiscall*/ CNRDObjectParticleCreater__vmt74(uint32_t *this)
{
  return *(this + 67);
}



// ------------------------------------------------------------
// 0x429010 CNRDObjectParticleCreater__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDObjectParticleCreater__vmt0(void *Block, char pszArg2)
{
  sub_429040();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x429040 sub_429040
// ------------------------------------------------------------
void /*thiscall*/ sub_429040(int this)
{
  *(uint32_t *)this = &vftbl_CNRDObjectParticleCreater;
  nullsub_3();
  if ( *(uint32_t *)(this + 296) >= 0x10u )
    j__free(*(void **)(this + 276));
  *(uint32_t *)(this + 296) = 15;
  *(uint32_t *)(this + 292) = 0;
  *(uint8_t *)(this + 276) = 0;
  sub_428480(this + 248);
  sub_425350((uint32_t *)this);
}



// ------------------------------------------------------------
// 0x4290D0 sub_4290D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4290D0(uint32_t *this)
{
  void *pMem; // eax
  int v3; // eax
  void *pMem2; // eax
  int v5; // eax
  uint32_t *pThis_5E; // edi
  int v7; // ebx
  uint8_t *pMem3; // esi
  uint8_t *pMem4; // eax
  uint8_t *pMem42; // esi
  int dword_79C0B02; // ebx
  int v12; // ecx
  bool v13; // zf
  uint8_t *pMem5; // eax
  uint8_t *pMem52; // esi
  int dword_79C0B03; // edi
  uint8_t *pMem522; // eax
  uint32_t *pMem6; // eax
  uint32_t *v19; // eax
  uint8_t *pMem7; // eax
  uint8_t *pMem72; // edi
  int dword_79C0B04; // ebx
  uint8_t *pMem8; // eax
  uint8_t *pMem82; // edi
  int dword_79C0B05; // ebx
  uint8_t *pMem9; // eax
  uint8_t *pMem92; // edi
  int dword_79C0B06; // ebx
  uint8_t *pMem10; // eax
  uint8_t *pMem102; // edi
  int dword_79C0B07; // ebx
  int result; // eax
  void *Block; // [esp+14h] [ebp-20h]
  int v35; // [esp+18h] [ebp-1Ch]
  int *pThis_74; // [esp+1Ch] [ebp-18h]
  int i; // [esp+20h] [ebp-14h]
  int v38; // [esp+24h] [ebp-10h]

  pMem = operator new(0x68u);
  if ( pMem != nullptr )
    v3 = sub_426BD0(pMem);
  else
    v3 = 0;
  *(this + 9) = v3;
  *(uint32_t *)(v3 + 28) = 640;
  *(uint32_t *)(v3 + 32) = 480;
  *(uint32_t *)(*(this + 9) + 68) = this;
  pMem2 = operator new(0x68u);
  if ( pMem2 != nullptr )
    v5 = sub_426BD0(pMem2);
  else
    v5 = 0;
  *(this + 10) = v5;
  *(uint32_t *)(v5 + 68) = this;
  v38 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 120);
  pThis_74 = this + 116;
  pThis_5E = this + 94;
  v35 = 2;
  do
  {
    v7 = -1;
    for ( i = 3; i != 0; --i )
    {
      pMem3 = operator new(0x2Cu);
      if ( pMem3 != nullptr )
      {
        Block = (void *)dword_79C0B0;
        pMem3[4] = 0;
        *(uint32_t *)pMem3 = &nengine::CNNumberSet::`vftable';
        sub_699E20(v8);
        sub_699E40(Block, v38, v7, 5);
      }
      else
      {
        v8 = nullptr;
      }
      *v6 = v8;
      *((uint32_t *)v8 + 9) = 2;
      *(uint32_t *)(*v6++ + 40) = -6;
      v7 += 11;
    }
    v9 = operator new(0x2Cu);
    v10 = v9;
    if ( v9 != nullptr )
    {
      v11 = dword_79C0B0;
      v9[4] = 0;
      *(uint32_t *)v9 = &nengine::CNNumberSet::`vftable';
      sub_699E20(pMem4);
      sub_699E40(dword_79C0B02, v38, 32, 10);
    }
    else
    {
      pMem42 = nullptr;
    }
    *pThis_74 = (int)pMem42;
    *((uint32_t *)pMem42 + 9) = 2;
    v12 = *pThis_74++;
    v13 = v35 == 1;
    *(uint32_t *)(v12 + 40) = -4;
    --v35;
  }
  while ( !v13 );
  pMem5 = operator new(0x2Cu);
  pMem52 = pMem5;
  if ( pMem5 != nullptr )
  {
    dword_79C0B03 = dword_79C0B0;
    pMem5[4] = 0;
    *(uint32_t *)pMem5 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v14);
    sub_699E40(v16, v38, 87, 10);
    v17 = v15;
  }
  else
  {
    v17 = nullptr;
  }
  *(this + 147) = v17;
  *((uint32_t *)v17 + 9) = 0;
  *(uint32_t *)(*(this + 147) + 40) = -4;
  v18 = operator new(0x12Cu);
  if ( v18 != nullptr )
    v19 = sub_428F30(v18, (int)"Common/Etc/Particle/finishfx00.ptl", 0);
  else
    v19 = nullptr;
  *(this + 209) = v19;
  v20 = operator new(0x2Cu);
  v21 = v20;
  if ( v20 != nullptr )
  {
    v22 = dword_79C0B0;
    v20[4] = 0;
    *(uint32_t *)v20 = &nengine::CNNumberSet::`vftable';
    sub_699E20(pMem7);
    sub_699E40(dword_79C0B04, v38, 32, 10);
  }
  else
  {
    pMem72 = nullptr;
  }
  *(this + 156) = pMem72;
  *((uint32_t *)pMem72 + 9) = 0;
  *(uint32_t *)(*(this + 156) + 40) = -4;
  pMem8 = operator new(0x2Cu);
  pMem82 = pMem8;
  if ( pMem8 != nullptr )
  {
    dword_79C0B05 = dword_79C0B0;
    pMem8[4] = 0;
    *(uint32_t *)pMem8 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v23);
    sub_699E40(v25, v38, 32, 10);
  }
  else
  {
    v24 = nullptr;
  }
  *(this + 165) = v24;
  *((uint32_t *)v24 + 9) = 0;
  *(uint32_t *)(*(this + 165) + 40) = -4;
  v26 = operator new(0x2Cu);
  v27 = v26;
  if ( v26 != nullptr )
  {
    v28 = dword_79C0B0;
    v26[4] = 0;
    *(uint32_t *)v26 = &nengine::CNNumberSet::`vftable';
    sub_699E20(pMem9);
    sub_699E40(dword_79C0B06, v38, 122, 10);
  }
  else
  {
    pMem92 = nullptr;
  }
  *(this + 197) = pMem92;
  *((uint32_t *)pMem92 + 9) = 0;
  *(uint32_t *)(*(this + 197) + 40) = -4;
  pMem10 = operator new(0x2Cu);
  pMem102 = pMem10;
  if ( pMem10 != nullptr )
  {
    dword_79C0B07 = dword_79C0B0;
    pMem10[4] = 0;
    *(uint32_t *)pMem10 = &nengine::CNNumberSet::`vftable';
    sub_699E20(pMem10);
    result = sub_699E40(dword_79C0B07, v38, 121, 10);
    *(this + 198) = pMem102;
  }
  else
  {
    *(this + 198) = 0;
    return 0;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4294E0 sub_4294E0
// ------------------------------------------------------------
void /*usercall*/ sub_4294E0(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int pObj; // ecx
  uint32_t *v5; // ecx
  unsigned int v6; // ebx
  int v7; // ecx
  int v8; // edx
  int pObj2; // edi
  int v10; // eax
  unsigned int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // ecx
  int v16; // edx
  int v17; // eax
  int v20; // [esp+4h] [ebp-4h]

  pObj = *(uint32_t *)(pArg1 + 52);
  if ( pObj != 0 )
  {
    flt_77FD6C = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
    flt_77FD70 = (float)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 52) + 124))(*(uint32_t *)(pArg1 + 52));
    flt_77FD74 = (float)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 52) + 128))(*(uint32_t *)(pArg1 + 52));
  }
  sub_483CF0();
  v5 = *(uint32_t **)(pArg1 + 44);
  if ( v5 != nullptr && *(uint8_t *)(pArg1 + 48) == 0 && *(uint32_t *)(dword_8F7A24 + 12) != 2 && dword_8F7C04 != 0 )
  {
    sub_48C8E0(v5);
    *(uint8_t *)(pArg1 + 48) = 1;
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
    {
      v6 = 0;
      v20 = sub_4250E0(*(uint32_t **)(pArg1 + 104));
      if ( v20 > 0 )
      {
        do
        {
          v7 = *(uint32_t *)(pArg1 + 104);
          v8 = *(uint32_t *)(v7 + 8);
          if ( v8 != 0 && v6 < (*(uint32_t *)(v7 + 12) - v8) >> 2 )
            pObj2 = *(uint32_t *)(v8 + 4 * v6);
          else
            pObj2 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 34) != 0 )
          {
            v10 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj2 + 340))(pObj2, nArg2, nArg3);
            v11 = *(uint32_t *)(v10 + 124);
            v12 = v10 + 100;
            if ( v11 < 0x10 )
              v13 = v12 + 4;
            else
              v13 = *(uint32_t *)(v12 + 4);
            nArg3 = 10000;
            nArg2 = 0;
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj2 + 212))(pObj2, v13, -1);
          }
          ++v6;
        }
        while ( (int)v6 < v20 );
      }
    }
  }
  if ( *(uint32_t *)(pArg1 + 1324) != 0 && *(uint32_t *)(pArg1 + 1352) != 0 )
  {
    v14 = *(uint32_t *)(pArg1 + 1352);
    if ( sub_699000(pArg1 + 1328) >= v14 )
      sub_426B10((uint32_t *)pArg1, 0, 0);
  }
  if ( *(uint32_t *)(pArg1 + 104) != 0 )
    sub_45F6C0();
  sub_428AD0((int *)pArg1);
  sub_4241E0(pArg1);
  sub_424170((uint32_t *)pArg1);
  v15 = *(uint32_t *)(pArg1 + 244);
  v16 = *(uint32_t *)(pArg1 + 240);
  *(uint32_t *)(pArg1 + 192) = *(uint32_t *)(pArg1 + 236);
  v17 = *(uint32_t *)(pArg1 + 52);
  *(uint32_t *)(pArg1 + 196) = v16 + v15;
  if ( v17 != 0 && *(uint32_t *)(pArg1 + 44) != 0 )
    sub_48C500(v17);
  sub_425570(pArg1);
  sub_424C50(pArg1);
  if ( *(uint32_t *)(pArg1 + 1224) == 0 )
    sub_424B40(pArg1);
  sub_427C20((uint32_t *)pArg1);
}



// ------------------------------------------------------------
// 0x4296C0 sub_4296C0
// ------------------------------------------------------------
bool /*thiscall*/ sub_4296C0(uint32_t *this, uint32_t *uArg2)
{
  return *this != *uArg2;
}



// ------------------------------------------------------------
// 0x4296E0 sub_4296E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4296E0(uint32_t *this, uint32_t *pArg2)
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 21) == 0 )
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
// 0x429740 sub_429740
// ------------------------------------------------------------
char /*stdcall*/ sub_429740(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_429740(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x429780 sub_429780
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_429780(int *this, uint32_t *uArg2, int nArg3)
{
  int v3; // esi

  v3 = *this;
  sub_41C5E0(this);
  *uArg2 = v3;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4297A0 sub_4297A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4297A0(uint32_t *this)
{
  uint32_t *fld_e2; // ecx
  uint32_t *v3; // eax
  void (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  void *i; // ebx
  uint32_t *pThis_1; // edi
  uint32_t *fld_e22; // esi
  uint32_t *result; // eax
  uint32_t *v9; // [esp+Ch] [ebp-4h] BYREF

  fld_e2 = (uint32_t *)*(this + 2);
  v3 = (uint32_t *)*fld_e2;
  v9 = (uint32_t *)*fld_e2;
  if ( v9 != fld_e2 )
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
  pThis_1 = this + 1;
  fld_e22 = *(uint32_t **)(*(this + 2) + 4);
  for ( i = fld_e22; *((uint8_t *)fld_e22 + 21) == 0; i = fld_e22 )
  {
    sub_429740((void **)fld_e22[2]);
    fld_e22 = (uint32_t *)*fld_e22;
    j__free(i);
  }
  *(uint32_t *)(pThis_1[1] + 4) = pThis_1[1];
  result = (uint32_t *)pThis_1[1];
  pThis_1[2] = 0;
  *result = result;
  *(uint32_t *)(pThis_1[1] + 8) = pThis_1[1];
  return result;
}



// ------------------------------------------------------------
// 0x429830 sub_429830
// ------------------------------------------------------------
int /*thiscall*/ sub_429830(uint32_t *this, int nArg2)
{
  int v4; // [esp+4h] [ebp-4h] BYREF

  nArg2 = (uint16_t)nArg2;
  sub_472E30(&v4, &nArg2);
  if ( v4 == *(this + 2) )
    return 0;
  else
    return *(uint32_t *)(v4 + 16);
}



// ------------------------------------------------------------
// 0x429870 sub_429870
// ------------------------------------------------------------
int /*thiscall*/ sub_429870(int **this, const char *pArg2)
{
  int *fld_e2; // eax
  int *v3; // ebx
  bool v4; // zf
  int *v7; // [esp+10h] [ebp-4h] BYREF

  fld_e2 = *(this + 2);
  v3 = (int *)*fld_e2;
  v4 = *fld_e2 == (uint32_t)fld_e2;
  v7 = (int *)*fld_e2;
  if ( v4 )
    return 0;
  while ( sub_40BF00((std::_String_base *)(v3[4] + 16), 0, *(uint32_t *)(v3[4] + 36), pArg2, strlen(pArg2)) != 0 )
  {
    sub_41C5E0(&v7);
    v3 = v7;
    if ( v7 == *(this + 2) )
      return 0;
  }
  return v3[4];
}



// ------------------------------------------------------------
// 0x4298F0 sub_4298F0
// ------------------------------------------------------------
// attributes: thunk
uint32_t */*thiscall*/ sub_4298F0(uint32_t *this)
{
  return sub_4297A0(this);
}



// ------------------------------------------------------------
// 0x429900 sub_429900
// ------------------------------------------------------------
int /*thiscall*/ sub_429900(uint32_t *this)
{
  int v2; // eax
  int v4; // [esp+4h] [ebp-8h] BYREF
  int v5; // [esp+8h] [ebp-4h] BYREF

  v5 = (uint16_t)word_77F804;
  sub_472E30(&v4, &v5);
  if ( v4 != *(this + 2) && (v2 = *(uint32_t *)(v4 + 16)) != 0 )
    return *(uint32_t *)(v2 + 120);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x429950 sub_429950
// ------------------------------------------------------------
int ***/*thiscall*/ sub_429950(uint32_t *this, int ***uArg2, int **pDwArg3)
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
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);
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
// 0x429C10 sub_429C10
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_429C10(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)
{
  int fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
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

  if ( *(this + 2) >= 0x1FFFFFFEu )
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
  fld_e1 = sub_5648C0(*(this + 1), pArg4, *(this + 1), nArg5, 0);
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
  v10 = (uint32_t *)(fld_e1 + 4);
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
            sub_433130(*v10);
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
        sub_433130(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x429DC0 sub_429DC0
// ------------------------------------------------------------
int /*thiscall*/ sub_429DC0(int this)
{
  int v2; // edx

  sub_4015C0((void *)szPassword, 0);
  *(uint32_t *)(this + 28) = 4;
  *(uint32_t *)(this + 32) = 0;
  *(uint8_t *)(this + 36) = 1;
  sub_41A590(this + 37, v2, 0);
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0xFFFF;
  *(uint32_t *)(this + 60) = 0xFFFF;
  *(uint32_t *)(this + 64) = 0xFFFF;
  *(uint32_t *)(this + 68) = 0xFFFF;
  *(uint32_t *)(this + 72) = 0xFFFF;
  *(uint32_t *)(this + 76) = 0xFFFF;
  *(uint32_t *)(this + 80) = 0xFFFF;
  *(uint32_t *)(this + 84) = 0xFFFF;
  *(uint32_t *)(this + 88) = 0xFFFF;
  *(uint32_t *)(this + 92) = 0xFFFF;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  return sub_4015C0((void *)szPassword, 0);
}



// ------------------------------------------------------------
// 0x429E30 sub_429E30
// ------------------------------------------------------------
int /*thiscall*/ sub_429E30(int this)
{
  uint32_t *pThis_25; // edi

  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  pThis_25 = (uint32_t *)(this + 37);
  sub_41A630(this + 37);
  *pThis_25 = &vftbl_clong;
  *(uint32_t *)(this + 140) = 15;
  *(uint32_t *)(this + 136) = 0;
  *(uint8_t *)(this + 120) = 0;
  sub_429DC0(this);
  return this;
}



// ------------------------------------------------------------
// 0x429EB0 sub_429EB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_429EB0(uint32_t *this, int16_t uArg2)
{
  *this = &vftbl_CNUser;
  sub_429E30((int)(this + 4));
  *(this + 40) = 0;
  *(this + 41) = 0;
  *((uint16_t *)this + 84) = 0;
  *(this + 44) = 0;
  *(this + 45) = 0;
  *(this + 46) = 0;
  *((uint8_t *)this + 188) = 0;
  sub_42A230(this);
  sub_42A250(uArg2);
  return this;
}



// ============================================================
// §14 CNUser / KMessenger（0x429F40-0x42A1D0）
// ============================================================
// ------------------------------------------------------------
// 0x429F40 CNUser__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNUser__vmt0(void *Block, char pszArg2)
{
  sub_429F70();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x429F70 sub_429F70
// ------------------------------------------------------------
int /*thiscall*/ sub_429F70(uint32_t *this)
{
  *this = &vftbl_CNUser;
  sub_42A260();
  return sub_41CBF0(this + 4);
}



// ------------------------------------------------------------
// 0x429FC0 sub_429FC0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_429FC0(uint32_t *this, int nArg2)
{
  uint16_t nArg22; // di
  int v4; // edx
  int pObj; // esi
  uint32_t *result; // eax
  int v7; // esi
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  int v9; // [esp+Ch] [ebp-4h] BYREF

  nArg22 = nArg2;
  v4 = 0;
  pObj = dword_8F850C + 16;
  while ( *(uint32_t *)pObj == 0 || *(uint16_t *)(*(uint32_t *)pObj + 4) != (uint16_t)nArg2 )
  {
    ++v4;
    pObj += 4;
    if ( v4 >= 4 )
      goto LABEL_7;
  }
  sub_456300(v4, 0);
LABEL_7:
  nArg2 = nArg22;
  result = (uint32_t *)sub_472E30(&v9, &nArg2);
  v7 = v9;
  if ( v9 != *(this + 2) )
  {
    v8 = *(void (/*thiscall*/ ****)(uint32_t, int))(v9 + 16);
    if ( v8 != nullptr )
      (**v8)(v8, 1);
    return sub_429950(this + 1, &nArg2, v7);
  }
  return result;
}



// ------------------------------------------------------------
// 0x42A040 sub_42A040
// ------------------------------------------------------------
int /*thiscall*/ sub_42A040(uint32_t *this, int pArg2, uint32_t *uArg3)
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
  if ( *((uint8_t *)v6 + 21) == 0 )
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
    while ( *((uint8_t *)v6 + 21) == 0 );
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_429C10(this, &uArg3, 1, fld_e1, (int)uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4A3B30(&uArg3);
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
    v12 = *sub_429C10(this, &uArg3, v13, fld_e1, (int)uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x42A100 sub_42A100
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42A100(void **this, uint16_t uArg2)
{
  uint32_t *pThis_1; // ebx
  uint32_t *result; // eax
  uint32_t *pMem; // eax
  uint32_t *v6; // esi
  int uArg23; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h] BYREF
  uint8_t v9[4]; // [esp+14h] [ebp-14h] BYREF
  int uArg22; // [esp+18h] [ebp-10h] BYREF
  int v11; // [esp+24h] [ebp-4h]

  pThis_1 = this + 1;
  uArg22 = uArg2;
  sub_472E30(&Block, &uArg22);
  if ( Block == *(this + 2) || (result = *((uint32_t **)Block + 4)) == nullptr )
  {
    pMem = operator new(0xC8u);
    Block = pMem;
    v6 = nullptr;
    v11 = 0;
    if ( pMem != nullptr )
      v6 = sub_429EB0(pMem, uArg2);
    v11 = -1;
    uArg23 = uArg2;
    Block = v6;
    sub_42A040(pThis_1, (int)v9, &uArg23);
    return v6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42A1B0 sub_42A1B0
// ------------------------------------------------------------
int /*cdecl*/ sub_42A1B0(int nArg1, int nArg2)
{
  return sub_657740(nArg1, nArg2);
}



// ============================================================
// §15 CNRDObject 虚表家族（0x42A1D0-0x42B270）
// ============================================================
// ------------------------------------------------------------
// 0x42A1D0 KMessenger__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ KMessenger__vmt0(uint32_t *Block, char pszArg2)
{
  *Block = &vftbl_KMessenger;
  sub_4989B0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x42A200 sub_42A200
// ------------------------------------------------------------
int /*thiscall*/ sub_42A200(uint32_t *this)
{
  *this = &vftbl_KMessenger;
  return sub_4989B0();
}



// ------------------------------------------------------------
// 0x42A210 sub_42A210
// ------------------------------------------------------------
char */*cdecl*/ sub_42A210(int pArg1)
{
  return sub_422E70(pArg1 + 1207);
}



// ------------------------------------------------------------
// 0x42A230 sub_42A230
// ------------------------------------------------------------
int /*thiscall*/ sub_42A230(int this)
{
  *(uint16_t *)(this + 4) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x42A250 sub_42A250
// ------------------------------------------------------------
int16_t /*thiscall*/ sub_42A250(uint16_t *this, int16_t uArg2)
{
  *(this + 2) = uArg2;
  return uArg2;
}



// ------------------------------------------------------------
// 0x42A260 sub_42A260
// ------------------------------------------------------------
int /*thiscall*/ sub_42A260(int *this)
{
  int fld_e48; // ecx
  uint32_t *fld_e482; // edi
  void (/*thiscall*/ ***fld_e484)(uint32_t, int); // ecx
  int result; // eax
  int fld_e49; // ecx
  uint32_t *fld_e492; // edi
  int v8; // eax
  int (/*thiscall*/ ***fld_e494)(uint32_t, int); // ecx
  int fld_e483; // [esp-4h] [ebp-10h]
  int fld_e493; // [esp-4h] [ebp-10h]

  if ( *(this + 48) == dword_8F7C08 )
    dword_8F7C08 = 0;
  fld_e48 = *(this + 48);
  if ( fld_e48 != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e48 + 80))(fld_e48) != 0 )
    {
      fld_e482 = *(uint32_t **)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 48) + 80))(*(this + 48)) + 132);
      fld_e483 = *(this + 48);
      (*(void (**)(void))(*(uint32_t *)fld_e483 + 80))();
      sub_45F1E0(fld_e483);
      if ( fld_e482 != nullptr && fld_e482[13] == *(this + 48) )
        sub_424A40(fld_e482, dword_8F7C08);
    }
    fld_e484 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 48);
    if ( fld_e484 != nullptr )
      (**fld_e484)(fld_e484, 1);
    *(this + 48) = 0;
  }
  result = *(this + 49);
  if ( result == dword_8F7C04 )
    dword_8F7C04 = 0;
  fld_e49 = *(this + 49);
  if ( fld_e49 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e49 + 80))(fld_e49);
    if ( result != 0 )
    {
      fld_e492 = *(uint32_t **)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 49) + 80))(*(this + 49)) + 132);
      fld_e493 = *(this + 49);
      (*(void (**)(void))(*(uint32_t *)fld_e493 + 80))();
      result = sub_45F1E0(fld_e493);
      if ( fld_e492 != nullptr )
      {
        result = fld_e492[13];
        if ( result == *(this + 49) )
        {
          v8 = sub_424310(fld_e492, (uint8_t *)dword_8F7C04);
          result = sub_424A40(fld_e492, v8);
        }
      }
    }
    fld_e494 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 49);
    if ( fld_e494 != nullptr )
      result = (**fld_e494)(fld_e494, 1);
    *(this + 49) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42A380 sub_42A380
// ------------------------------------------------------------
char */*thiscall*/ sub_42A380(unsigned int *this, char pszArg2)
{
  unsigned int fld_e41; // eax

  if ( pszArg2 != 0 )
    fld_e41 = *(this + 41);
  else
    fld_e41 = *(this + 40);
  sprintf(byte_8F7C20, "%d.%d.%d.%d", (uint8_t)fld_e41, BYTE1(fld_e41), BYTE2(fld_e41), HIBYTE(fld_e41));
  return byte_8F7C20;
}



// ------------------------------------------------------------
// 0x42A3D0 sub_42A3D0
// ------------------------------------------------------------
void /*thiscall*/ sub_42A3D0(int this, int nArg2)
{
  int fld_4; // edi

  *(uint32_t *)(this + 196) = nArg2;
  if ( nArg2 != 0 )
  {
    fld_4 = *(uint16_t *)(this + 4);
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 36))(nArg2) + 4) = fld_4;
  }
  if ( *(uint16_t *)(this + 4) == (uint16_t)word_77F804 )
    dword_8F7C04 = *(uint32_t *)(this + 196);
}



// ------------------------------------------------------------
// 0x42A410 sub_42A410
// ------------------------------------------------------------
int /*thiscall*/ sub_42A410(uint32_t *this)
{
  return sub_418DD0(*(this + 29));
}



// ------------------------------------------------------------
// 0x42A430 sub_42A430
// ------------------------------------------------------------
int /*thiscall*/ sub_42A430(uint32_t *this)
{
  return sub_418DD0(*(this + 29));
}



// ------------------------------------------------------------
// 0x42A450 sub_42A450
// ------------------------------------------------------------
int /*thiscall*/ sub_42A450(void **this)
{
  *this = &vftbl_CNRDObject;
  sub_49A850();
  sub_660080(this + 44);
  if ( *(this + 36) != nullptr )
    j__free(*(this + 36));
  *(this + 36) = nullptr;
  *(this + 37) = nullptr;
  *(this + 38) = nullptr;
  sub_6569D0(this + 31);
  j__free(*(this + 32));
  *(this + 32) = nullptr;
  *(this + 16) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 68) = 0;
  *(this + 9) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 40) = 0;
  *(this + 2) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 12) = 0;
  *this = &vftbl_KMessenger;
  return sub_4989B0(this);
}



// ------------------------------------------------------------
// 0x42A510 CNRDObject__vmt20
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmt20(uint32_t *this, uint32_t *pArg2)
{
  uint32_t *pThis_19; // ecx
  int result; // eax

  pThis_19 = this + 25;
  *pThis_19 = *pArg2;
  pThis_19[1] = pArg2[1];
  result = pArg2[2];
  pThis_19[2] = result;
  return result;
}



// ------------------------------------------------------------
// 0x42A5B0 CNRDObject__vmt54
// ------------------------------------------------------------
char /*thiscall*/ CNRDObject__vmt54(uint8_t *this, char pszArg2)
{
  *(this + 156) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x42A5C0 CNRDObject__vmt58
// ------------------------------------------------------------
char /*thiscall*/ CNRDObject__vmt58(uint8_t *this)
{
  return *(this + 156);
}



// ------------------------------------------------------------
// 0x42A5D0 CNRDObject__vmt5C
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmt5C(uint32_t *this, int nArg2)
{
  int fld_e30; // edx
  int result; // eax

  fld_e30 = *(this + 30);
  result = nArg2;
  *(this + 34) = nArg2;
  if ( fld_e30 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 196))(this, nArg2);
  return result;
}



// ------------------------------------------------------------
// 0x42A5F0 CNRDObject__vmt78
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmt78(void *this)
{
  return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 116))(this, 0);
}



// ------------------------------------------------------------
// 0x42A620 CNRDObject__vmt88
// ------------------------------------------------------------
char /*stdcall*/ CNRDObject__vmt88(int nArg1, int nArg2, uint32_t *uArg3)
{
  if ( uArg3 != nullptr )
    *uArg3 = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x42A640 CNRDObject__vmt9C
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDObject__vmt9C(void *this, int nArg2)
{
  int v3; // edi

  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);
  return abs32((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) - v3);
}



// ------------------------------------------------------------
// 0x42A670 CNRDObject__vmtA0
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNRDObject__vmtA0(void *this, int nArg2)
{
  int v3; // edi

  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);
  return abs32((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this) - v3);
}



// ------------------------------------------------------------
// 0x42A6A0 CNRDObject__vmt8
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmt8(void *this, int nArg2, int nArg3)
{
  int pThis_78; // eax
  int pThis_7C; // [esp-10h] [ebp-18h]
  int v7; // [esp-Ch] [ebp-14h]
  int v8; // [esp-8h] [ebp-10h]

  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);
  pThis_7C = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);
  pThis_78 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
  return sub_499240(pThis_78, pThis_7C, v7, v8, nArg3);
}



// ------------------------------------------------------------
// 0x42A6E0 CNRDObject__vmtB0
// ------------------------------------------------------------
BOOL /*thiscall*/ CNRDObject__vmtB0(void *this, int nArg2)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this) == 1
      && nArg2 > (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this)
      || (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this) == 0
      && nArg2 < (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
}



// ------------------------------------------------------------
// 0x42A730 CNRDObject__vmtB4
// ------------------------------------------------------------
BOOL /*thiscall*/ CNRDObject__vmtB4(void *this, int nArg2)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this) == 1
      && nArg2 < (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this)
      || (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this) == 0
      && nArg2 > (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
}



// ------------------------------------------------------------
// 0x42A790 CNRDObject__vmtC4
// ------------------------------------------------------------
uint8_t /*thiscall*/ CNRDObject__vmtC4(unsigned int *this, int pArg2)
{
  uint8_t result; // al

  *(this + 30) = pArg2;
  if ( pArg2 != 0 )
  {
    sub_699070(pArg2, *(this + 23));
    result = *(uint8_t *)(pArg2 + 168);
    if ( result != 0 )
      return (uint8_t)sub_4938F0(pArg2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x42A7D0 CNRDObject__vmtDC
// ------------------------------------------------------------
char /*thiscall*/ CNRDObject__vmtDC(uint8_t *this, char pszArg2)
{
  *(this + 172) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x42A7E0 CNRDObject__vmtE0
// ------------------------------------------------------------
char /*thiscall*/ CNRDObject__vmtE0(uint8_t *this)
{
  return *(this + 172);
}



// ------------------------------------------------------------
// 0x42A7F0 CNRDObject__vmtE8
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmtE8(void *this)
{
  return (*(int (/*thiscall*/ **)(void *, uint32_t, int, uint32_t))(*(uint32_t *)this + 228))(this, 0, -1, 0);
}



// ------------------------------------------------------------
// 0x42A810 CNRDObject__vmtF0
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmtF0(uint32_t *this)
{
  return sub_699000((int)(this + 2)) - *(this + 52);
}



// ------------------------------------------------------------
// 0x42A830 CNRDObject__vmtF4
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmtF4(uint32_t *this)
{
  return *(this + 51);
}



// ------------------------------------------------------------
// 0x42A840 CNRDObject__vmtF8
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmtF8(void *this)
{
  int pThis_F4; // edi

  pThis_F4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 244))(this);
  return pThis_F4 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 240))(this);
}



// ------------------------------------------------------------
// 0x42A860 CNRDObject__vmt100
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmt100(uint32_t *this, int pArg2)
{
  return *(this + pArg2 + 54);
}



// ------------------------------------------------------------
// 0x42A880 CNRDObject__vmt108
// ------------------------------------------------------------
char /*thiscall*/ CNRDObject__vmt108(uint8_t *this)
{
  return *(this + 232);
}



// ------------------------------------------------------------
// 0x42A8A0 CNRDObject__vmt114
// ------------------------------------------------------------
BOOL /*thiscall*/ CNRDObject__vmt114(float *this)
{
  return *(this + 61) != 0.0;
}



// ------------------------------------------------------------
// 0x42A8D0 CNRDObject__vmt11C
// ------------------------------------------------------------
char /*thiscall*/ CNRDObject__vmt11C(int this, char pszArg2, int nArg3, char pszArg4, int nArg5)
{
  *(uint8_t *)(this + 248) = pszArg2;
  *(uint32_t *)(this + 252) = nArg3;
  *(uint8_t *)(this + 256) = pszArg4;
  *(uint32_t *)(this + 260) = nArg5;
  return pszArg4;
}



// ------------------------------------------------------------
// 0x42A930 CNRDObject__vmt68
// ------------------------------------------------------------
int /*thiscall*/ CNRDObject__vmt68(uint32_t *this, unsigned int uArg2)
{
  int fld_e36; // edx

  fld_e36 = *(this + 36);
  if ( fld_e36 != 0 && uArg2 < (*(this + 37) - fld_e36) >> 2 )
    return *(uint32_t *)(*(this + 36) + 4 * uArg2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x42A970 CNRDObject__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDObject__vmt0(void *Block, char pszArg2)
{
  sub_42A450();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x42A9A0 sub_42A9A0
// ------------------------------------------------------------
void /*noreturn*/ sub_42A9A0()
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
// 0x42AA10 sub_42AA10
// ------------------------------------------------------------
void /*thiscall*/ sub_42AA10(int this)
{
  if ( *(uint32_t *)(this + 76) != 0 )
    j__free(*(void **)(this + 76));
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  if ( *(uint32_t *)(this + 60) != 0 )
    j__free(*(void **)(this + 60));
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
}



// ------------------------------------------------------------
// 0x42AA50 sub_42AA50
// ------------------------------------------------------------
char /*thiscall*/ sub_42AA50(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x3FFFFFFF )
    sub_42A9A0(this);
  pMem = (char *)operator new(4 * uArg2);
  *(this + 3) = &pMem[4 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x42AAB0 sub_42AAB0
// ------------------------------------------------------------
char */*thiscall*/ sub_42AAB0(char *this)
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
  sub_499B40(this);
  return this;
}



// ------------------------------------------------------------
// 0x42ABC0 CNRDObject__vmt64
// ------------------------------------------------------------
int /*stdcall*/ CNRDObject__vmt64(char pszArg1)
{
  return sub_42ABE0(&pszArg1);
}



// ------------------------------------------------------------
// 0x42ABE0 sub_42ABE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42ABE0(int this, uint32_t *uArg2)
{
  int fld_4; // esi
  unsigned int fld_8; // edx
  uint32_t *fld_82; // eax
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) >> 2 )
    return (uint32_t *)sub_42AC40(&uArg2, *(void **)(this + 8), uArg2);
  fld_82 = *(uint32_t **)(this + 8);
  *fld_82 = *uArg2;
  result = fld_82 + 1;
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x42AC40 sub_42AC40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42AC40(uint32_t *this, uint32_t *uArg2, void *Src, int nArg4)
{
  int fld_e1; // ecx
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) >> 2 != 0 )
    v6 = ((int)Src - fld_e1) >> 2;
  else
    v6 = 0;
  sub_42AC90(Src, 1, nArg4);
  *uArg2 = *(this + 1) + 4 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x42AC90 sub_42AC90
// ------------------------------------------------------------
int */*thiscall*/ sub_42AC90(int this, char *Src, unsigned int uArg3, int *pDwArg4)
{
  int v5; // ecx
  int *result; // eax
  unsigned int fld_C; // edi
  int fld_8; // edx
  int fld_82; // edx
  unsigned int v10; // edi
  int fld_85; // edx
  int fld_86; // edx
  char *pMem; // ebx
  int v14; // eax
  unsigned int uArg32; // edx
  int *v16; // ecx
  void *fld_42; // ecx
  int fld_87; // eax
  uint8_t *fld_83; // ebx
  int *v20; // edi
  unsigned int v21; // eax
  int fld_84; // edx
  char *v23; // esi
  char *v24; // eax
  void *fld_4; // [esp-18h] [ebp-38h]
  int v26; // [esp+0h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-14h]
  int *v28; // [esp+10h] [ebp-10h]
  int v29; // [esp+1Ch] [ebp-4h]
  void *Srca; // [esp+28h] [ebp+8h]
  int v31; // [esp+2Ch] [ebp+Ch]
  size_t v32; // [esp+2Ch] [ebp+Ch]
  int v33; // [esp+30h] [ebp+10h]

  v5 = *pDwArg4;
  result = *(int **)(this + 4);
  v28 = &v26;
  Block = (void *)this;
  v33 = v5;
  if ( result != nullptr )
    fld_C = (*(uint32_t *)(this + 12) - (int)result) >> 2;
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( result != nullptr )
      fld_8 = (*(uint32_t *)(this + 8) - (int)result) >> 2;
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_42A9A0(this);
    if ( result != nullptr )
      fld_82 = (*(uint32_t *)(this + 8) - (int)result) >> 2;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint8_t **)(this + 8);
      v20 = (int *)Src;
      v21 = (fld_83 - Src) >> 2;
      if ( v21 >= uArg3 )
      {
        Srca = (void *)(4 * uArg3);
        v23 = &fld_83[-4 * uArg3];
        v32 = 4 * ((int)(4 * uArg3) >> 2);
        v24 = (char *)memcpy_0(fld_83, v23, v32);
        *((uint32_t *)Block + 2) = &v24[v32];
        memcpy_0(&fld_83[-4 * ((v23 - (char *)v20) >> 2)], v20, 4 * ((v23 - (char *)v20) >> 2));
        for ( result = (int *)((char *)v20 + (uint32_t)Srca); v20 != result; ++v20 )
          *v20 = v33;
      }
      else
      {
        memcpy_0(&Src[4 * uArg3], Src, 4 * v21);
        memset32(*(void **)(this + 8), v33, uArg3 - ((*(uint32_t *)(this + 8) - (int)Src) >> 2));
        result = nullptr;
        fld_84 = 4 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_84;
        if ( Src != (char *)(fld_84 - 4 * uArg3) )
        {
          do
          {
            result = (int *)v33;
            *v20++ = v33;
          }
          while ( v20 != (int *)(fld_84 - 4 * uArg3) );
        }
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (fld_C >> 1) >= fld_C )
        v10 = (fld_C >> 1) + fld_C;
      else
        v10 = 0;
      if ( result != nullptr )
        fld_85 = (*(uint32_t *)(this + 8) - (int)result) >> 2;
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )
      {
        if ( result != nullptr )
          fld_86 = (*(uint32_t *)(this + 8) - (int)result) >> 2;
        else
          fld_86 = 0;
        v10 = fld_86 + uArg3;
      }
      pMem = (char *)operator new(4 * v10);
      fld_4 = *(void **)(this + 4);
      Block = pMem;
      v29 = 0;
      v14 = sub_433A30(fld_4, (int)Src, pMem);
      uArg32 = uArg3;
      v16 = (int *)v14;
      while ( uArg32 != 0 )
      {
        *v16 = v33;
        pMem = (char *)Block;
        --uArg32;
        ++v16;
      }
      sub_433A30(Src, *(uint32_t *)(this + 8), (void *)(v14 + 4 * uArg3));
      fld_42 = *(void **)(this + 4);
      if ( fld_42 != nullptr )
        fld_87 = (*(uint32_t *)(this + 8) - (int)fld_42) >> 2;
      else
        fld_87 = 0;
      v31 = fld_87 + uArg3;
      if ( fld_42 != nullptr )
        j__free(fld_42);
      result = (int *)&pMem[4 * v31];
      *(uint32_t *)(this + 12) = &pMem[4 * v10];
      *(uint32_t *)(this + 8) = result;
      *(uint32_t *)(this + 4) = pMem;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x42AF10 sub_42AF10
// ------------------------------------------------------------
void /*stdcall*/ sub_42AF10(int nArg1, int nArg2)
{
  int i; // esi

  for ( i = nArg1; i != nArg2; i += 88 )
    sub_42AA10(i);
}



// ------------------------------------------------------------
// 0x42AF40 sub_42AF40
// ------------------------------------------------------------
int /*thiscall*/ sub_42AF40(int *this)
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);
  result = 0;
  if ( fld_e1 != 0 )
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 88 )
      sub_42AA10(fld_e1);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42AF90 sub_42AF90
// ------------------------------------------------------------
int /*thiscall*/ sub_42AF90(void **this)
{
  int result; // eax

  sub_493C80();
  sub_6569D0(this + 50);
  j__free(*(this + 51));
  *(this + 51) = nullptr;
  if ( *(this + 34) != nullptr )
    j__free(*(this + 34));
  *(this + 34) = nullptr;
  *(this + 35) = nullptr;
  *(this + 36) = nullptr;
  if ( *(this + 30) != nullptr )
    j__free(*(this + 30));
  *(this + 30) = nullptr;
  *(this + 31) = nullptr;
  *(this + 32) = nullptr;
  result = sub_42AF40(this + 10);
  *((uint8_t *)this + 4) = 0;
  *this = &vftbl_nengine__IObject;
  return result;
}



// ------------------------------------------------------------
// 0x42B040 sub_42B040
// ------------------------------------------------------------
int /*thiscall*/ sub_42B040(void ***this)
{
  int result; // eax
  void **v3; // edi
  int fld_e1; // edi
  int fld_e2; // edi

  if ( *this != nullptr )
  {
    result = sub_4942D0();
    v3 = *this;
    if ( *this != nullptr )
    {
      sub_42AF90(*this);
      result = sub_657740(v3, 228);
    }
    *this = nullptr;
  }
  if ( *(this + 1) != nullptr )
  {
    result = sub_4942D0();
    fld_e1 = (int)*(this + 1);
    if ( fld_e1 != 0 )
    {
      sub_42AF90(*(this + 1));
      result = sub_657740(fld_e1, 228);
    }
    *(this + 1) = nullptr;
  }
  if ( *(this + 2) != nullptr )
  {
    result = sub_4942D0();
    fld_e2 = (int)*(this + 2);
    if ( fld_e2 != 0 )
    {
      sub_42AF90(*(this + 2));
      result = sub_657740(fld_e2, 228);
    }
    *(this + 2) = nullptr;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42B0F0 sub_42B0F0
// ------------------------------------------------------------
int /*thiscall*/ sub_42B0F0(int this)
{
  sub_42AAB0((char *)this);
  *(uint32_t *)this = &vftbl_CNRDVirtualCharacter;
  *(uint32_t *)(this + 284) = 4;
  *(uint32_t *)(this + 288) = -1;
  *(uint8_t *)(this + 292) = 0;
  *(uint32_t *)(this + 296) = 0;
  *(uint32_t *)(this + 300) = 0;
  *(uint32_t *)(this + 304) = 0;
  `eh vector constructor iterator'((void *)(this + 380), 0x10u, 10, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  *(uint32_t *)(this + 544) = 0;
  *(uint32_t *)(this + 548) = 0;
  *(uint32_t *)(this + 552) = 0;
  *(uint32_t *)(this + 608) = 15;
  *(uint32_t *)(this + 604) = 0;
  *(uint8_t *)(this + 588) = 0;
  sub_42F250(this);
  nullsub_3();
  return this;
}



// ------------------------------------------------------------
// 0x42B1C0 CNRDVirtualCharacter__vmt150
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt150(uint32_t *this, uint32_t *pArg2)
{
  uint32_t *pThis_47; // ecx
  int result; // eax

  pThis_47 = this + 71;
  *pThis_47 = *pArg2;
  pThis_47[1] = pArg2[1];
  result = pArg2[2];
  pThis_47[2] = result;
  return result;
}



// ------------------------------------------------------------
// 0x42B1E0 IRDCollisionObject__vmt154
// ------------------------------------------------------------
char */*thiscall*/ IRDCollisionObject__vmt154(char *this)
{
  return this + 284;
}



// ------------------------------------------------------------
// 0x42B220 CNRDVirtualCharacter__vmt164
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDVirtualCharacter__vmt164(uint32_t *this)
{
  if ( *(this + 152) < 0x10u )
    return this + 147;
  else
    return (uint32_t *)*(this + 147);
}



// ------------------------------------------------------------
// 0x42B240 CNRDVirtualCharacter__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDVirtualCharacter__vmt0(void *Block, char pszArg2)
{
  sub_42B270();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ============================================================
// §16 杂项与评价 HUD 构造器（0x42B270-0x42BD40）
//   0x42B7E0 = 评价/横幅对象大构造器（36 字节槽组 ×N，尾调 0x423C10 复位评价值）
// ============================================================
// ------------------------------------------------------------
// 0x42B270 sub_42B270
// ------------------------------------------------------------
int /*thiscall*/ sub_42B270(int this)
{
  *(uint32_t *)this = &vftbl_CNRDVirtualCharacter;
  sub_431AE0();
  if ( *(uint32_t *)(this + 608) >= 0x10u )
    j__free(*(void **)(this + 588));
  *(uint32_t *)(this + 608) = 15;
  *(uint32_t *)(this + 604) = 0;
  *(uint8_t *)(this + 588) = 0;
  if ( *(uint32_t *)(this + 544) != 0 )
    j__free(*(void **)(this + 544));
  *(uint32_t *)(this + 544) = 0;
  *(uint32_t *)(this + 548) = 0;
  *(uint32_t *)(this + 552) = 0;
  `eh vector destructor iterator'((void *)(this + 380), 0x10u, 10, (void (/*thiscall*/ *)(void *))sub_5E5260);
  sub_42B040((void ***)(this + 296));
  return sub_42A450((void **)this);
}



// ------------------------------------------------------------
// 0x42B340 sub_42B340
// ------------------------------------------------------------
int /*thiscall*/ sub_42B340(int this)
{
  void *pMem; // eax
  int v3; // eax
  int16_t fld_4; // cx
  int fld_42; // edi

  if ( *(uint32_t *)(this + 192) == 0 )
  {
    pMem = operator new(0x294u);
    if ( pMem != nullptr )
      v3 = sub_42B0F0((int)pMem);
    else
      v3 = 0;
    fld_4 = *(uint16_t *)(this + 4);
    *(uint32_t *)(this + 192) = v3;
    if ( fld_4 == (uint16_t)word_77F804 )
      dword_8F7C08 = v3;
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 192) + 348))(*(uint32_t *)(this + 192), this + 16);
    fld_42 = *(uint16_t *)(this + 4);
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 192) + 36))(*(uint32_t *)(this + 192)) + 4) = fld_42;
  }
  return *(uint32_t *)(this + 192);
}



// ------------------------------------------------------------
// 0x42B3F0 sub_42B3F0
// ------------------------------------------------------------
int /*thiscall*/ sub_42B3F0(void *this, float fArg2)
{
  uint64_t v3; // rax
  int v4; // edi

  v3 = (uint64_t)((double)sub_41A5E0((unsigned int)this) * fArg2);
  v4 = v3;
  sub_41A590((unsigned int)this, SHIDWORD(v3), v3);
  return v4;
}



// ------------------------------------------------------------
// 0x42B420 sub_42B420
// ------------------------------------------------------------
int64_t /*cdecl*/ sub_42B420(int nArg1, int nArg2, int nArg3, int nArg4)
{
  int v4; // edx
  double v5; // st7
  float v7; // [esp+0h] [ebp-10h]
  float v8; // [esp+0h] [ebp-10h]
  float v9; // [esp+4h] [ebp-Ch]
  float v10; // [esp+4h] [ebp-Ch]

  v4 = nArg3 % (2 * nArg4);
  if ( v4 >= nArg4 )
  {
    v10 = (float)nArg1;
    v8 = (float)nArg2;
    v5 = sub_4049C0(v8, v10, v4 - nArg4, nArg4);
  }
  else
  {
    v9 = (float)nArg2;
    v7 = (float)nArg1;
    v5 = sub_4049C0(v7, v9, nArg3 % (2 * nArg4), nArg4);
  }
  return _ftol2(v5);
}



// ------------------------------------------------------------
// 0x42B480 sub_42B480
// ------------------------------------------------------------
char /*thiscall*/ sub_42B480(uint8_t *this, int nArg2, int nArg3)
{
  int pThis_4A0; // ecx

  *(this + 1196) = 1;
  pThis_4A0 = (int)(this + 1184);
  *(uint8_t *)(pThis_4A0 + 13) = 0;
  *(uint8_t *)(pThis_4A0 + 14) = 0;
  return sub_698F90(pThis_4A0, nArg3, -nArg2);
}



// ------------------------------------------------------------
// 0x42B4B0 ?_Get_future_error_what@std@@YAPBDH@Z
// ------------------------------------------------------------
const char */*cdecl*/ std::_Get_future_error_what(int nArg1)
{
  return (const char *)dword_8F7D28[nArg1];
}



// ------------------------------------------------------------
// 0x42B4C0 sub_42B4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_42B4C0(int this)
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
    *(uint32_t *)(this + 32) = -1;
    *(uint32_t *)(this + 84) = 0;
    *(uint32_t *)(this + 88) = 0;
    *(uint32_t *)(this + 92) = 0;
    *(uint32_t *)(this + 124) = 0;
    *(uint32_t *)(this + 152) = 2;
    *(uint32_t *)(this + 76) = -1;
    *(uint8_t *)(this + 184) = 0;
    *(uint32_t *)(this + 188) = 0;
    *(uint32_t *)(this + 132) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42B510 sub_42B510
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_42B510(uint32_t *this)
{
  int fld_e8; // eax

  fld_e8 = *(this + 8);
  return fld_e8 == 2 || fld_e8 == 3 || fld_e8 == 4;
}



// ------------------------------------------------------------
// 0x42B530 sub_42B530
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_42B530(uint32_t *this)
{
  int fld_e8; // eax

  fld_e8 = *(this + 8);
  return fld_e8 != 2 && fld_e8 != 3 && fld_e8 != 4;
}



// ------------------------------------------------------------
// 0x42B560 sub_42B560
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_42B560(uint32_t *this)
{
  int fld_e8; // eax

  fld_e8 = *(this + 8);
  return fld_e8 == 2 || fld_e8 == 3;
}



// ------------------------------------------------------------
// 0x42B580 sub_42B580
// ------------------------------------------------------------
int /*stdcall*/ sub_42B580(int nArg1, int pArg2)
{
  if ( pArg2 != sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 104))(dword_8F8520, nArg1);
    off_77F3FC("@@REMOVE PEER : WARROOM");
  }
  if ( pArg2 != 0 && *(uint32_t *)(pArg2 + 196) != 0 )
    sub_45F1E0(*(uint32_t *)(pArg2 + 196));
  return sub_4632D0(*((uint32_t *)dword_8F8528 + 4));
}



// ------------------------------------------------------------
// 0x42B5F0 sub_42B5F0
// ------------------------------------------------------------
char /*thiscall*/ sub_42B5F0(uint8_t *this)
{
  int pThis_60; // ecx

  *(this + 108) = 1;
  pThis_60 = (int)(this + 96);
  *(uint8_t *)(pThis_60 + 13) = 0;
  *(uint8_t *)(pThis_60 + 14) = 0;
  return sub_698F90(pThis_60, 0, 0);
}



// ------------------------------------------------------------
// 0x42B610 sub_42B610
// ------------------------------------------------------------
void */*thiscall*/ sub_42B610(uint32_t *this, int ArgList)
{
  void *result; // eax

  off_77F3FC((char *)&byte_6C3EB0, ArgList);
  sub_49BDB0(0);
  sub_432EA0("GRENSELOS_TRUCE", -1, 0, 0);
  result = (void *)*(this + 22);
  if ( result == (void *)1 )
  {
    sub_49AA90("first battle end");
    result = dword_8F8528;
    *(uint32_t *)(*((uint32_t *)dword_8F8528 + 634) + 88) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42B690 sub_42B690
// ------------------------------------------------------------
int /*stdcall*/ sub_42B690(int nArg1)
{
  int i; // esi
  int result; // eax
  int pObj; // ecx

  for ( i = 0; i < 8; ++i )
  {
    result = sub_578E80(i);
    if ( result != 0 )
    {
      pObj = *(uint32_t *)(result + 196);
      if ( pObj != 0 )
        result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1200))(pObj, nArg1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42B6D0 sub_42B6D0
// ------------------------------------------------------------
void /*thiscall*/ sub_42B6D0(int *this)
{
  int i; // esi
  int v3; // eax
  int v4; // ecx

  for ( i = 0; i < 8; ++i )
  {
    v3 = sub_578E80(i);
    if ( v3 != 0 )
    {
      v4 = *(uint32_t *)(v3 + 196);
      if ( v4 != 0 )
        sub_45FE80(*(this + 7), (int)this, 273, *(uint16_t *)(v3 + 4), v4, 0, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x42B720 sub_42B720
// ------------------------------------------------------------
int /*stdcall*/ sub_42B720(int nArg1, int nArg2)
{
  int i; // edi
  int result; // eax

  for ( i = 0; i < 8; ++i )
  {
    result = sub_578E80(i);
    if ( result != 0 && *(uint32_t *)(result + 196) != 0 )
    {
      sub_49C620(1, 1, 0);
      result = sub_49C5F0(1, 0, 0, nArg2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42B780 sub_42B780
// ------------------------------------------------------------
int /*stdcall*/ sub_42B780(int nArg1)
{
  int i; // esi
  int result; // eax
  int pObj; // ecx

  for ( i = 0; i < 8; ++i )
  {
    result = sub_578E80(i);
    if ( result != 0 )
    {
      pObj = *(uint32_t *)(result + 196);
      if ( pObj != 0 )
        result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 604))(pObj, nArg1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42B7C0 sub_42B7C0
// ------------------------------------------------------------
int /*thiscall*/ sub_42B7C0(uint32_t *this, int nArg2, int nArg3)
{
  *(this + 31) = nArg2;
  *(this + 32) = nArg3;
  *(this + 33) = 0;
  return nArg2;
}



// ------------------------------------------------------------
// 0x42B7E0 sub_42B7E0
// ------------------------------------------------------------
// 【评价/横幅对象大构造器】36 字节槽组 ×N（{+0 激活, +1/+2 渐隐标志}，见 +572/573/574、
//   +608/609/610、+644/645/646…），EH 向量构造 ×3（+256/+320/+408，元素 0x1C ×2）；
//   尾调 sub_423C10 复位评价值。0x426820 的 this 即此对象。
char */*thiscall*/ sub_42B7E0(char *this)
{
  *(uint32_t *)this = &off_6C3EE0;
  *(this + 8) = 0;
  *((uint32_t *)this + 1) = &off_6C2B88;
  *((uint32_t *)this + 3) = 0;
  *(this + 16) = 1;
  *(this + 18) = 0;
  *(this + 17) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 5) = 0;
  *(this + 60) = 0;
  *((uint32_t *)this + 14) = &off_6C2B88;
  *((uint32_t *)this + 16) = 0;
  *(this + 68) = 1;
  *(this + 70) = 0;
  *(this + 69) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 18) = 0;
  sub_41A630(this + 120);
  *((uint32_t *)this + 30) = &clong::`vftable';
  sub_41A630(this + 134);
  *(uint32_t *)(this + 134) = &clong::`vftable';
  sub_41A630(this + 148);
  *((uint32_t *)this + 37) = &clong::`vftable';
  *(this + 168) = 0;
  *((uint32_t *)this + 41) = &off_6C2B88;
  *((uint32_t *)this + 43) = 0;
  *(this + 176) = 1;
  *(this + 178) = 0;
  *(this + 177) = 0;
  *((uint32_t *)this + 47) = 0;
  *((uint32_t *)this + 46) = 0;
  *((uint32_t *)this + 45) = 0;
  *(this + 212) = 0;
  *((uint32_t *)this + 52) = &off_6C2B88;
  *((uint32_t *)this + 54) = 0;
  *(this + 220) = 1;
  *(this + 222) = 0;
  *(this + 221) = 0;
  *((uint32_t *)this + 58) = 0;
  *((uint32_t *)this + 57) = 0;
  *((uint32_t *)this + 56) = 0;
  `eh vector constructor iterator'(this + 256, 0x1Cu, 2, sub_401170, sub_401000);
  `eh vector constructor iterator'(this + 320, 0x1Cu, 2, sub_401170, sub_401000);
  `eh vector constructor iterator'(this + 408, 0x1Cu, 2, sub_401170, sub_401000);
  *(this + 476) = 0;
  *((uint32_t *)this + 118) = &off_6C2B88;
  *((uint32_t *)this + 120) = 0;
  *(this + 484) = 1;
  *(this + 486) = 0;
  *(this + 485) = 0;
  *((uint32_t *)this + 124) = 0;
  *((uint32_t *)this + 123) = 0;
  *((uint32_t *)this + 122) = 0;
  *(this + 504) = 0;
  *((uint32_t *)this + 125) = &off_6C2B88;
  *((uint32_t *)this + 127) = 0;
  *(this + 512) = 1;
  *(this + 514) = 0;
  *(this + 513) = 0;
  *((uint32_t *)this + 131) = 0;
  *((uint32_t *)this + 130) = 0;
  *((uint32_t *)this + 129) = 0;
  *(this + 532) = 0;
  *((uint32_t *)this + 132) = &off_6C2B88;
  *((uint32_t *)this + 134) = 0;
  *(this + 540) = 1;
  *(this + 542) = 0;
  *(this + 541) = 0;
  *((uint32_t *)this + 138) = 0;
  *((uint32_t *)this + 137) = 0;
  *((uint32_t *)this + 136) = 0;
  *(this + 564) = 0;
  *((uint32_t *)this + 140) = &off_6C2B88;
  *((uint32_t *)this + 142) = 0;
  *(this + 572) = 1;
  *(this + 574) = 0;
  *(this + 573) = 0;
  *((uint32_t *)this + 146) = 0;
  *((uint32_t *)this + 145) = 0;
  *((uint32_t *)this + 144) = 0;
  *(this + 600) = 0;
  *((uint32_t *)this + 149) = &off_6C2B88;
  *((uint32_t *)this + 151) = 0;
  *(this + 608) = 1;
  *(this + 610) = 0;
  *(this + 609) = 0;
  *((uint32_t *)this + 155) = 0;
  *((uint32_t *)this + 154) = 0;
  *((uint32_t *)this + 153) = 0;
  *(this + 636) = 0;
  *((uint32_t *)this + 158) = &off_6C2B88;
  *((uint32_t *)this + 160) = 0;
  *(this + 644) = 1;
  *(this + 646) = 0;
  *(this + 645) = 0;
  *((uint32_t *)this + 164) = 0;
  *((uint32_t *)this + 163) = 0;
  *((uint32_t *)this + 162) = 0;
  *(this + 668) = 0;
  *((uint32_t *)this + 166) = &off_6C2B88;
  *((uint32_t *)this + 168) = 0;
  *(this + 676) = 1;
  *(this + 678) = 0;
  *(this + 677) = 0;
  *((uint32_t *)this + 172) = 0;
  *((uint32_t *)this + 171) = 0;
  *((uint32_t *)this + 170) = 0;
  *(this + 696) = 0;
  *((uint32_t *)this + 173) = &off_6C2B88;
  *((uint32_t *)this + 175) = 0;
  *(this + 704) = 1;
  *(this + 706) = 0;
  *(this + 705) = 0;
  *((uint32_t *)this + 179) = 0;
  *((uint32_t *)this + 178) = 0;
  *((uint32_t *)this + 177) = 0;
  *(this + 764) = 0;
  *((uint32_t *)this + 190) = &off_6C2B88;
  *((uint32_t *)this + 192) = 0;
  *(this + 772) = 1;
  *(this + 774) = 0;
  *(this + 773) = 0;
  *((uint32_t *)this + 196) = 0;
  *((uint32_t *)this + 195) = 0;
  *((uint32_t *)this + 194) = 0;
  *(this + 800) = 0;
  *((uint32_t *)this + 199) = &off_6C2B88;
  *((uint32_t *)this + 201) = 0;
  *(this + 808) = 1;
  *(this + 810) = 0;
  *(this + 809) = 0;
  *((uint32_t *)this + 205) = 0;
  *((uint32_t *)this + 204) = 0;
  *((uint32_t *)this + 203) = 0;
  *(this + 848) = 0;
  *((uint32_t *)this + 211) = &off_6C2B88;
  *((uint32_t *)this + 213) = 0;
  *(this + 856) = 1;
  *(this + 858) = 0;
  *(this + 857) = 0;
  *((uint32_t *)this + 217) = 0;
  *((uint32_t *)this + 216) = 0;
  *((uint32_t *)this + 215) = 0;
  *(this + 876) = 0;
  *((uint32_t *)this + 218) = &off_6C2B88;
  *((uint32_t *)this + 220) = 0;
  *(this + 884) = 1;
  *(this + 886) = 0;
  *(this + 885) = 0;
  *((uint32_t *)this + 224) = 0;
  *((uint32_t *)this + 223) = 0;
  *((uint32_t *)this + 222) = 0;
  *(this + 908) = 0;
  *((uint32_t *)this + 226) = &off_6C2B88;
  *((uint32_t *)this + 228) = 0;
  *(this + 916) = 1;
  *(this + 918) = 0;
  *(this + 917) = 0;
  *((uint32_t *)this + 232) = 0;
  *((uint32_t *)this + 231) = 0;
  *((uint32_t *)this + 230) = 0;
  `eh vector constructor iterator'(this + 936, 0x1Cu, 8, sub_401170, sub_401000);
  *(this + 1200) = 0;
  *((uint32_t *)this + 299) = &off_6C2B88;
  *((uint32_t *)this + 301) = 0;
  *(this + 1208) = 1;
  *(this + 1210) = 0;
  *(this + 1209) = 0;
  *((uint32_t *)this + 305) = 0;
  *((uint32_t *)this + 304) = 0;
  *((uint32_t *)this + 303) = 0;
  *(this + 1264) = 0;
  *((uint32_t *)this + 315) = &off_6C2B88;
  *((uint32_t *)this + 317) = 0;
  *(this + 1272) = 1;
  *(this + 1274) = 0;
  *(this + 1273) = 0;
  *((uint32_t *)this + 321) = 0;
  *((uint32_t *)this + 320) = 0;
  *((uint32_t *)this + 319) = 0;
  *(this + 1292) = 0;
  *((uint32_t *)this + 322) = &off_6C2B88;
  *((uint32_t *)this + 324) = 0;
  *(this + 1300) = 1;
  *(this + 1302) = 0;
  *(this + 1301) = 0;
  *((uint32_t *)this + 328) = 0;
  *((uint32_t *)this + 327) = 0;
  *((uint32_t *)this + 326) = 0;
  *(this + 1332) = 0;
  *((uint32_t *)this + 332) = &off_6C2B88;
  *((uint32_t *)this + 334) = 0;
  *(this + 1340) = 1;
  *(this + 1342) = 0;
  *(this + 1341) = 0;
  *((uint32_t *)this + 338) = 0;
  *((uint32_t *)this + 337) = 0;
  *((uint32_t *)this + 336) = 0;
  sub_423C10(this);
  sub_4290D0(this);
  return this;
}


// ============================================================
// §17 战场/界面杂项（0x42BD40-0x42E010）
// ============================================================
// ------------------------------------------------------------
// 0x42BD40 sub_42BD40
// ------------------------------------------------------------
int /*thiscall*/ sub_42BD40(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNRDStage;
  sub_423FD0((uint32_t *)this);
  *(uint8_t *)(this + 1332) = 0;
  *(uint32_t *)(this + 1328) = &vftbl_nengine__IObject;
  *(uint32_t *)(this + 1288) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1292) = 0;
  *(uint32_t *)(this + 1260) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1264) = 0;
  *(uint32_t *)(this + 1196) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1200) = 0;
  `eh vector destructor iterator'((void *)(this + 936), 0x1Cu, 8, sub_401000);
  *(uint32_t *)(this + 904) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 908) = 0;
  *(uint32_t *)(this + 872) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 876) = 0;
  *(uint32_t *)(this + 844) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 848) = 0;
  *(uint32_t *)(this + 796) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 800) = 0;
  *(uint32_t *)(this + 760) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 764) = 0;
  *(uint32_t *)(this + 692) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 696) = 0;
  *(uint32_t *)(this + 664) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 668) = 0;
  *(uint32_t *)(this + 632) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 636) = 0;
  *(uint32_t *)(this + 596) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 600) = 0;
  *(uint32_t *)(this + 560) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 564) = 0;
  *(uint32_t *)(this + 528) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 532) = 0;
  *(uint32_t *)(this + 500) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 504) = 0;
  *(uint32_t *)(this + 472) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 476) = 0;
  `eh vector destructor iterator'((void *)(this + 408), 0x1Cu, 2, sub_401000);
  `eh vector destructor iterator'((void *)(this + 320), 0x1Cu, 2, sub_401000);
  `eh vector destructor iterator'((void *)(this + 256), 0x1Cu, 2, sub_401000);
  *(uint32_t *)(this + 208) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 212) = 0;
  *(uint32_t *)(this + 164) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 168) = 0;
  sub_41A580(this + 148);
  sub_41A580(this + 134);
  result = sub_41A580(this + 120);
  *(uint32_t *)(this + 56) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 60) = 0;
  *(uint32_t *)(this + 4) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 8) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42BF10 sub_42BF10
// ------------------------------------------------------------
char /*thiscall*/ sub_42BF10(int this, int ArgList)
{
  int v3; // eax
  int fld_10; // eax
  int fld_98; // eax

  off_77F3FC((char *)&byte_6C3EF4, ArgList);
  sub_49E050(0);
  v3 = sub_432F00(0);
  sub_487080(v3);
  sub_49CD70(1);
  sub_45FC60(*(uint32_t *)(this + 28));
  sub_4602C0(*(uint32_t *)(*(uint32_t *)(this + 24) + 476));
  sub_48E870(*(uint32_t *)(this + 28));
  sub_42B6D0((int *)this);
  sub_42B690(0);
  sub_42B780(0);
  sub_48FDE0(dword_99FF08);
  fld_10 = *(uint32_t *)(this + 16);
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = *(uint32_t *)(*(uint32_t *)(fld_10 + 108) + 280);
  sub_432EA0("GRENSELOS_READY", -1, 0, 0);
  fld_98 = *(uint32_t *)(this + 152);
  if ( fld_98 == 1 )
  {
    *(uint32_t *)(this + 152) = 0;
    *(uint8_t *)(this + 168) = 1;
    *(uint8_t *)(this + 169) = 0;
    *(uint8_t *)(this + 170) = 0;
    LOBYTE(fld_98) = sub_698F90(this + 156, 500, 0);
  }
  return fld_98;
}



// ------------------------------------------------------------
// 0x42C000 sub_42C000
// ------------------------------------------------------------
int /*thiscall*/ sub_42C000(int *this, int ArgList)
{
  int v3; // edi
  int v4; // edx
  uint32_t *v6; // esi
  char *v7; // eax
  uint32_t *v8; // esi
  char *v9; // eax
  uint32_t *v10; // esi
  char *v11; // eax
  int v12; // edx

  off_77F3FC((char *)&byte_6C3F44, ArgList);
  if ( ArgList == 4 )
  {
    v3 = sub_48FCA0();
    if ( (int)sub_48FD70(v3) <= 0 )
    {
      sub_48FC30(v3, 255);
      *(this + 47) = 2;
    }
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1024))(dword_8F7C04);
  }
  else if ( ArgList == 0 )
  {
    v6 = *((uint32_t **)dword_8F8528 + 7);
    v7 = sub_422E70(1910);
    sub_43BEE0(v6, (int)v7, -13435036, 0, -1);
    v8 = *((uint32_t **)dword_8F8528 + 7);
    v9 = sub_422E70(1911);
    sub_43BEE0(v8, (int)v9, -13435036, 0, -1);
    v10 = *((uint32_t **)dword_8F8528 + 7);
    v11 = sub_422E70(1927);
    sub_43BEE0(v10, (int)v11, -13435036, 0, -1);
    return sub_425460(*(this + 4), v12);
  }
  off_77F3FC(aOldstateWait);
  sub_42BF10((int)this, ArgList);
  return sub_425460(*(this + 4), v4);
}



// ------------------------------------------------------------
// 0x42C110 sub_42C110
// ------------------------------------------------------------
char /*thiscall*/ sub_42C110(int this)
{
  int fld_98; // eax
  int fld_B4; // edi
  int pThis_9C; // eax
  int fld_B42; // ebx
  int pThis_9C2; // eax
  uint64_t v7; // rax
  int fld_B43; // ebx
  int pThis_24; // eax
  bool v10; // cc

  if ( *(uint8_t *)(this + 168) != 0 )
  {
    fld_98 = *(uint32_t *)(this + 152);
    if ( fld_98 == 1 )
    {
      fld_B4 = *(uint32_t *)(this + 180);
      pThis_9C = sub_699000(this + 156);
      *((uint32_t *)dword_8F8528 + 621) = (uint64_t)sub_4049C0(0.0, 255.0, pThis_9C, fld_B4);
    }
    else if ( fld_98 == 0 )
    {
      fld_B42 = *(uint32_t *)(this + 180);
      pThis_9C2 = sub_699000(this + 156);
      v7 = (uint64_t)sub_4049C0(255.0, 0.0, pThis_9C2, fld_B42);
      *((uint32_t *)dword_8F8528 + 621) = v7;
      fld_B43 = *(uint32_t *)(this + 180);
      if ( sub_699000(this + 156) >= fld_B43 )
      {
        *(uint32_t *)(this + 152) = 2;
        *(uint8_t *)(this + 168) = 0;
      }
    }
  }
  if ( *(uint32_t *)(this + 32) == 3 )
  {
    pThis_24 = sub_699000(this + 36);
    v10 = pThis_24 < 9200;
  }
  else
  {
    pThis_24 = *(uint32_t *)(this + 32) - 4;
    if ( *(uint32_t *)(this + 32) != 4 )
      return pThis_24;
    pThis_24 = sub_699000(this + 36);
    v10 = pThis_24 < 16200;
  }
  if ( !v10 && *(uint32_t *)(this + 152) == 2 )
  {
    *(uint8_t *)(this + 168) = 1;
    *(uint32_t *)(this + 152) = 1;
    *(uint8_t *)(this + 170) = 0;
    *(uint8_t *)(this + 169) = 0;
    LOBYTE(pThis_24) = sub_698F90(this + 156, 300, 0);
  }
  return pThis_24;
}



// ------------------------------------------------------------
// 0x42C220 sub_42C220
// ------------------------------------------------------------
void /*thiscall*/ sub_42C220(int this)
{
  if ( *(uint32_t *)(this + 12) != 0 )
    j__free(*(void **)(this + 12));
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
}



// ------------------------------------------------------------
// 0x42C250 sub_42C250
// ------------------------------------------------------------
void **/*thiscall*/ sub_42C250(void **this)
{
  char *pThis_2; // edi
  char *pThis_1D; // edi
  int i; // [esp+Ch] [ebp-4h]
  int j; // [esp+Ch] [ebp-4h]

  *this = (void *)-1;
  pThis_2 = (char *)(this + 2);
  for ( i = 4; i != 0; --i )
  {
    if ( *(uint32_t *)pThis_2 != 0 )
      j__free(*(void **)pThis_2);
    *(uint32_t *)pThis_2 = 0;
    *((uint32_t *)pThis_2 + 1) = 0;
    *((uint32_t *)pThis_2 + 2) = 0;
    pThis_2 += 16;
  }
  if ( *(this + 18) != nullptr )
    j__free(*(this + 18));
  *(this + 18) = nullptr;
  *(this + 19) = nullptr;
  *(this + 20) = nullptr;
  *(this + 21) = nullptr;
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *(this + 24) = nullptr;
  *(this + 25) = nullptr;
  *(this + 26) = nullptr;
  *(this + 27) = nullptr;
  pThis_1D = (char *)(this + 29);
  for ( j = 4; j != 0; --j )
  {
    if ( *(uint32_t *)pThis_1D != 0 )
      j__free(*(void **)pThis_1D);
    *(uint32_t *)pThis_1D = 0;
    *((uint32_t *)pThis_1D + 1) = 0;
    *((uint32_t *)pThis_1D + 2) = 0;
    pThis_1D += 16;
  }
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
  *(this + 54) = nullptr;
  *(this + 55) = nullptr;
  *(this + 56) = nullptr;
  *(this + 57) = nullptr;
  *(this + 59) = nullptr;
  *(this + 60) = nullptr;
  *(this + 61) = nullptr;
  *(this + 62) = nullptr;
  *(this + 58) = nullptr;
  *(this + 63) = nullptr;
  *(this + 64) = nullptr;
  *(this + 65) = nullptr;
  *(this + 66) = nullptr;
  return this + 59;
}



// ------------------------------------------------------------
// 0x42C370 sub_42C370
// ------------------------------------------------------------
void /*thiscall*/ sub_42C370(int this)
{
  `eh vector destructor iterator'((void *)(this + 112), 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);
  if ( *(uint32_t *)(this + 72) != 0 )
    j__free(*(void **)(this + 72));
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  `eh vector destructor iterator'((void *)(this + 4), 0x10u, 4, (void (/*thiscall*/ *)(void *))sub_5E5260);
}



// ------------------------------------------------------------
// 0x42C400 sub_42C400
// ------------------------------------------------------------
double /*cdecl*/ sub_42C400(int nArg1, int nArg2)
{
  if ( nArg1 == -1 )
    return 1.0;
  else
    return *(float *)(*(uint32_t *)(dword_8F7C40 + 8) + 44 * nArg1 - 44 + 4 * nArg2);
}



// ------------------------------------------------------------
// 0x42C430 sub_42C430
// ------------------------------------------------------------
int /*thiscall*/ sub_42C430(uint32_t *this)
{
  unsigned int v2; // esi
  int fld_e7; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj; // ecx
  int fld_e72; // ecx
  int v9; // edx

  v2 = 0;
  while ( 1 )
  {
    fld_e7 = *(this + 7);
    v4 = *(uint32_t *)(fld_e7 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e7 + 12) - v4) >> 2 : 0;
    if ( (int)v2 >= v5 )
      return sub_45F550(*(this + 7));
    v6 = *(uint32_t *)(fld_e7 + 8);
    if ( v6 != 0 && v2 < (*(uint32_t *)(fld_e7 + 12) - v6) >> 2 )
      pObj = *(uint32_t *)(v6 + 4 * v2);
    else
      pObj = 0;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj) == 289 )
    {
      fld_e72 = *(this + 7);
      v9 = *(uint32_t *)(fld_e72 + 8);
      if ( v9 == 0 || v2 >= (*(uint32_t *)(fld_e72 + 12) - v9) >> 2 )
      {
        (*(void (/*stdcall*/ **)(uint32_t))(MEMORY[0] + 84))(0);
        goto LABEL_15;
      }
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v9 + 4 * v2) + 84))(*(uint32_t *)(v9 + 4 * v2), 0);
      ++v2;
    }
    else
    {
LABEL_15:
      ++v2;
    }
  }
}



// ------------------------------------------------------------
// 0x42C4C0 sub_42C4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_42C4C0(uint32_t *this)
{
  unsigned int v2; // esi
  int fld_e7; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // edx

  v2 = 0;
  while ( 1 )
  {
    fld_e7 = *(this + 7);
    v4 = *(uint32_t *)(fld_e7 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e7 + 12) - v4) >> 2 : 0;
    if ( (int)v2 >= v5 )
      return sub_45F550(*(this + 7));
    v6 = *(uint32_t *)(fld_e7 + 8);
    if ( v6 != 0 && v2 < (*(uint32_t *)(fld_e7 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * v2);
    else
      v7 = 0;
    if ( *(uint8_t *)(v7 + 277) == 1 )
    {
      v8 = *(uint32_t *)(fld_e7 + 8);
      if ( v8 == 0 || v2 >= (*(uint32_t *)(fld_e7 + 12) - v8) >> 2 )
      {
        (*(void (/*stdcall*/ **)(uint32_t))(MEMORY[0] + 84))(0);
        goto LABEL_15;
      }
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(v8 + 4 * v2) + 84))(*(uint32_t *)(v8 + 4 * v2), 0);
      ++v2;
    }
    else
    {
LABEL_15:
      ++v2;
    }
  }
}



// ------------------------------------------------------------
// 0x42C540 sub_42C540
// ------------------------------------------------------------
char */*stdcall*/ sub_42C540(int nArg1)
{
  char *v1; // eax

  v1 = (char *)dword_8F7C58 + 28 * nArg1;
  if ( *((uint32_t *)v1 + 6) < 0x10u )
    return v1 + 4;
  else
    return *((char **)v1 + 1);
}



// ------------------------------------------------------------
// 0x42C570 sub_42C570
// ------------------------------------------------------------
int /*stdcall*/ sub_42C570(int ArgList, int nArg2, int nArg3)
{
  int result; // eax
  int v4; // esi
  char *v5; // eax
  int v6; // [esp-Ch] [ebp-210h]
  char Buffer[512]; // [esp+0h] [ebp-204h] BYREF
  int dword_796E502; // [esp+200h] [ebp-4h]

  dword_796E502 = dword_796E50;
  result = sub_48B740(6);
  if ( result != 1 )
  {
    v4 = sub_49EDC0(ArgList, -1);
    if ( v4 != 0 )
    {
      sub_422E70(10033);
      result = nArg2;
      if ( nArg2 == -1 )
      {
        if ( nArg3 != -1 )
        {
          v6 = sub_48FE30(v4);
          v5 = sub_422E70(1920);
LABEL_11:
          sprintf(Buffer, v5, v6);
          return sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
        }
      }
      else
      {
        result = nArg3 + 1;
        switch ( nArg3 )
        {
          case -1:
            v6 = sub_48FE30(v4);
            v5 = sub_422E70(1921);
            goto LABEL_11;
          case 0:
          case 1:
            v6 = sub_48FE30(v4);
            v5 = sub_422E70(1922);
            goto LABEL_11;
          case 4:
            v6 = sub_48FE30(v4);
            v5 = sub_422E70(1923);
            goto LABEL_11;
          default:
            return result;
        }
      }
    }
    else
    {
      return off_77F3FC((char *)&byte_6C3F6C, ArgList);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42C6A0 sub_42C6A0
// ------------------------------------------------------------
char */*stdcall*/ sub_42C6A0(int ArgList)
{
  char *result; // eax

  result = (char *)sub_48B740(6);
  if ( result != (char *)1 )
  {
    if ( sub_49EDC0(ArgList, -1) != 0 )
      return sub_422E70(10033);
    else
      return (char *)off_77F3FC((char *)&byte_6C3F9C, ArgList);
  }
  return result;
}



// ------------------------------------------------------------
// 0x42C710 sub_42C710
// ------------------------------------------------------------
double /*thiscall*/ sub_42C710(uint32_t *this, int nArg2, int nArg3)
{
  int v4; // eax
  int v6; // [esp+4h] [ebp-4h] BYREF

  sub_4BE520(&v6, &nArg2);
  if ( v6 == *(this + 17) )
    return 1.0;
  v4 = *(uint32_t *)(v6 + 16);
  if ( v4 == -1 )
    return 1.0;
  else
    return *(float *)(44 * v4 + *(uint32_t *)(dword_8F7C40 + 8) - 44 + 4 * nArg3);
}



// ------------------------------------------------------------
// 0x42C770 sub_42C770
// ------------------------------------------------------------
void /*thiscall*/ sub_42C770(int this)
{
  sub_45F080();
  if ( *(uint32_t *)(this + 140) != 0 )
    j__free(*(void **)(this + 140));
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  if ( *(uint32_t *)(this + 120) != 0 )
    j__free(*(void **)(this + 120));
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  `eh vector destructor iterator'((void *)(this + 20), 0x10u, 6, (void (/*thiscall*/ *)(void *))sub_5E5260);
  if ( *(uint32_t *)(this + 8) != 0 )
    j__free(*(void **)(this + 8));
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
}



// ------------------------------------------------------------
// 0x42C820 sub_42C820
// ------------------------------------------------------------
int /*thiscall*/ sub_42C820(uint32_t *this, int ArgList)
{
  uint8_t *v3; // ecx
  _BOOL2 v4; // dx
  int v5; // eax

  off_77F3FC((char *)&byte_6C3FCC, ArgList);
  sub_49AA90("result");
  *(uint32_t *)(*((uint32_t *)dword_8F8528 + 634) + 88) = -1;
  *(uint32_t *)(*((uint32_t *)dword_8F8528 + 4) + 1212) = (uint16_t)word_8F7C10;
  if ( (uint16_t)word_8F7C10 < (uint16_t)word_8F7C14 )
  {
    word_8F7C10 += *(uint16_t *)(*(this + 5) + 460);
    v3 = *((uint8_t **)dword_8F8528 + 4);
    v4 = word_8F7C10 != word_8F7C14;
    v3[1196] = 1;
    v3 += 1184;
    v3[13] = 0;
    v3[14] = 0;
    sub_698F90((int)v3, v4 ? 1000 : 5000, -500);
  }
  sub_49BDB0(0);
  v5 = sub_432F00(0);
  sub_487080(v5);
  sub_42B690(0);
  return sub_42C430(this);
}



// ------------------------------------------------------------
// 0x42C920 sub_42C920
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42C920(uint32_t *this, uint32_t *uArg2, int pArg3)
{
  sub_48C4B0(pArg3 + 24, *(this + 2), pArg3);
  *(this + 2) -= 24;
  *uArg2 = pArg3;
  return uArg2;
}



// ------------------------------------------------------------
// 0x42C960 sub_42C960
// ------------------------------------------------------------
void /*stdcall*/ sub_42C960(int pArg1)
{
  if ( *(uint32_t *)(pArg1 + 4) != 0 )
    j__free(*(void **)(pArg1 + 4));
  *(uint32_t *)(pArg1 + 4) = 0;
  *(uint32_t *)(pArg1 + 8) = 0;
  *(uint32_t *)(pArg1 + 12) = 0;
}



// ------------------------------------------------------------
// 0x42C9A0 sub_42C9A0
// ------------------------------------------------------------
void /*thiscall*/ sub_42C9A0(int this)
{
  if ( *(uint32_t *)(this + 140) != 0 )
    j__free(*(void **)(this + 140));
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
}



// ------------------------------------------------------------
// 0x42C9E0 sub_42C9E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42C9E0(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)
{
  int fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
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

  if ( *(this + 2) >= 0x1FFFFFFEu )
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
  fld_e1 = sub_5648C0(*(this + 1), pArg4, *(this + 1), nArg5, 0);
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
  v10 = (uint32_t *)(fld_e1 + 4);
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
            sub_433130(*v10);
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
        sub_433130(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x42CB90 sub_42CB90
// ------------------------------------------------------------
void /*noreturn*/ sub_42CB90()
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
// 0x42CC00 sub_42CC00
// ------------------------------------------------------------
void /*cdecl*/ sub_42CC00(int nArg1, int nArg2)
{
  int i; // esi

  for ( i = nArg1; i != nArg2; i += 16 )
  {
    if ( *(uint32_t *)(i + 4) != 0 )
      j__free(*(void **)(i + 4));
    *(uint32_t *)(i + 4) = 0;
    *(uint32_t *)(i + 8) = 0;
    *(uint32_t *)(i + 12) = 0;
  }
}



// ------------------------------------------------------------
// 0x42CC40 sub_42CC40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42CC40(char *this)
{
  char *pThis_18; // esi
  int pThis_4A; // esi
  uint32_t *result; // eax
  int m; // ecx
  int i; // [esp+Ch] [ebp-8h]
  int k; // [esp+Ch] [ebp-8h]
  int j; // [esp+10h] [ebp-4h]

  *(uint32_t *)this = 0;
  *((uint32_t *)this + 1) = 4;
  *((uint32_t *)this + 2) = 100;
  *((uint32_t *)this + 3) = 100;
  *((uint32_t *)this + 4) = 100;
  pThis_18 = this + 24;
  for ( i = 6; i != 0; --i )
  {
    for ( j = 2; j != 0; --j )
    {
      if ( *(uint32_t *)pThis_18 != 0 )
        j__free(*(void **)pThis_18);
      *(uint32_t *)pThis_18 = 0;
      *((uint32_t *)pThis_18 + 1) = 0;
      *((uint32_t *)pThis_18 + 2) = 0;
      pThis_18 += 16;
    }
  }
  if ( *((uint32_t *)this + 54) != 0 )
    j__free(*((void **)this + 54));
  *((uint32_t *)this + 54) = 0;
  *((uint32_t *)this + 55) = 0;
  *((uint32_t *)this + 56) = 0;
  if ( *((uint32_t *)this + 58) != 0 )
    j__free(*((void **)this + 58));
  *((uint32_t *)this + 58) = 0;
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
  *((uint32_t *)this + 69) = 0;
  *((uint32_t *)this + 70) = 0;
  *((uint32_t *)this + 71) = 0;
  *((uint32_t *)this + 72) = 0;
  pThis_4A = *((uint32_t *)this + 74);
  if ( pThis_4A != 0 )
  {
    for ( k = *((uint32_t *)this + 75); pThis_4A != k; pThis_4A += 4 )
      sub_41B010(pThis_4A);
    j__free(*((void **)this + 74));
  }
  *((uint32_t *)this + 74) = 0;
  *((uint32_t *)this + 75) = 0;
  *((uint32_t *)this + 76) = 0;
  result = this + 316;
  for ( m = 3; m != 0; --m )
  {
    *(result - 2) = 0;
    *(result - 1) = 0;
    *result = 0;
    result[1] = 0;
    result += 4;
  }
  *((uint32_t *)this + 89) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42CDB0 sub_42CDB0
// ------------------------------------------------------------
int /*thiscall*/ sub_42CDB0(uint32_t *this, int pArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // ebx
  uint32_t *fld_e1; // esi
  int *v6; // eax
  bool v7; // cl
  unsigned int v8; // edx
  uint32_t *fld_e12; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  uArg32 = uArg3;
  fld_e1 = (uint32_t *)*(this + 1);
  v6 = (int *)fld_e1[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 21) == 0 )
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
    while ( *((uint8_t *)v6 + 21) == 0 );
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_42C9E0(this, &uArg3, 1, fld_e1, (int)uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4A3B30(&uArg3);
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
    v12 = *sub_42C9E0(this, &uArg3, v13, fld_e1, (int)uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x42CE70 sub_42CE70
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42CE70(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_42C9E0((uint32_t *)this, uArg2, 1, *(uint32_t **)(this + 4), (int)pArg4);
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_42C9E0((uint32_t *)this, uArg2, 1, pArg3, (int)pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_4 )
  {
    v8 = (uint32_t *)fld_4[2];
    if ( v8[3] < *pArg4 )
    {
      sub_42C9E0((uint32_t *)this, uArg2, 0, v8, (int)pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4A3B30(&pArg4), pArg4[3] >= *pArg42) )
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_41C5E0(&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_42CDB0((uint32_t *)this, (int)v10, pArg42);
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 21) != 0 )
      sub_42C9E0((uint32_t *)this, uArg2, 0, pArg3, (int)pArg42);
    else
      sub_42C9E0((uint32_t *)this, uArg2, 1, pArg4, (int)pArg42);
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 21) != 0 )
      sub_42C9E0((uint32_t *)this, uArg2, 0, pArg4, (int)pArg42);
    else
      sub_42C9E0((uint32_t *)this, uArg2, 1, pArg3, (int)pArg42);
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x42CFD0 sub_42CFD0
// ------------------------------------------------------------
char /*thiscall*/ sub_42CFD0(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x3FFFFFFF )
    sub_42CB90(this);
  pMem = (char *)operator new(4 * uArg2);
  *(this + 3) = &pMem[4 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x42D030 sub_42D030
// ------------------------------------------------------------
char /*thiscall*/ sub_42D030(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x1FFFFFFF )
    sub_42CB90(this);
  pMem = (char *)operator new(8 * uArg2);
  *(this + 3) = &pMem[8 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x42D090 sub_42D090
// ------------------------------------------------------------
char /*thiscall*/ sub_42D090(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0xFFFFFFF )
    sub_42CB90(this);
  pMem = (char *)operator new(16 * uArg2);
  *(this + 3) = &pMem[16 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x42D0E0 sub_42D0E0
// ------------------------------------------------------------
char /*thiscall*/ sub_42D0E0(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0xAAAAAAA )
    sub_42CB90(this);
  pMem = (char *)operator new(24 * uArg2);
  *(this + 3) = &pMem[24 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x42D130 sub_42D130
// ------------------------------------------------------------
int /*thiscall*/ sub_42D130(int *this, int pArg2, unsigned int uArg3, uint32_t *Block)
{
  int result; // eax
  int v6; // edx
  int fld_e1; // ebx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v16; // ecx
  int fld_e27; // eax
  int v18; // ebx
  int fld_e13; // eax
  unsigned int v20; // edi
  void *fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-4Ch]
  int fld_e25; // [esp-Ch] [ebp-40h]
  unsigned int fld_e24; // [esp-8h] [ebp-3Ch]
  int v27; // [esp+0h] [ebp-34h] BYREF
  uint32_t v28[7]; // [esp+Ch] [ebp-28h] BYREF
  int v29; // [esp+30h] [ebp-4h]
  int v30; // [esp+3Ch] [ebp+8h]
  int v31; // [esp+40h] [ebp+Ch]
  char *Blocka; // [esp+44h] [ebp+10h]
  void *Blockb; // [esp+44h] [ebp+10h]

  result = (int)Block;
  v6 = Block[1];
  fld_e1 = *(this + 1);
  v28[0] = *Block;
  v8 = Block[2];
  v28[1] = v6;
  v9 = Block[3];
  v28[2] = v8;
  v10 = Block[4];
  v28[3] = v9;
  v11 = Block[5];
  v28[6] = &v27;
  v28[4] = v10;
  v28[5] = v11;
  if ( fld_e1 != 0 )
  {
    result = 715827883 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 24;
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 24;
    else
      fld_e2 = 0;
    if ( 178956970 - fld_e2 < uArg3 )
      sub_41D5A0(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 24;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 24 >= uArg3 )
      {
        v30 = (int)fld_e23 - 24 * uArg3;
        *(this + 2) = sub_4FF050(v30, fld_e23, fld_e23);
        sub_504430(pArg2, v30, Blockb);
        return sub_4FEF50(pArg2, pArg2 + 24 * uArg3, v28);
      }
      else
      {
        sub_4FF050(pArg2, fld_e23, pArg2 + 24 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 24;
        fld_e25 = *(this + 2);
        v29 = 2;
        sub_504620(fld_e25, fld_e24, v28);
        fld_e26 = 24 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        return sub_4FEF50(pArg2, fld_e26 - 24 * uArg3, v28);
      }
    }
    else
    {
      if ( 178956970 - (fld_e3 >> 1) >= fld_e3 )
        v16 = (fld_e3 >> 1) + fld_e3;
      else
        v16 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 24;
      else
        fld_e27 = 0;
      if ( v16 < uArg3 + fld_e27 )
        v16 = uArg3 + sub_4FEF30(this);
      v18 = 24 * v16;
      Blocka = (char *)operator new(24 * v16);
      fld_e12 = *(this + 1);
      v29 = 0;
      v31 = sub_4FF050(fld_e12, pArg2, Blocka);
      sub_5044B0(v31, uArg3, v28);
      sub_4FF050(pArg2, *(this + 2), v31 + 24 * uArg3);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 24;
      v20 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v18];
      *(this + 2) = (int)&Blocka[24 * v20];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x42D400 sub_42D400
// ------------------------------------------------------------
void /*thiscall*/ sub_42D400(void **this)
{
  if ( *(this + 2) != nullptr )
    j__free(*(this + 2));
  *(this + 2) = nullptr;
  *(this + 3) = nullptr;
  *(this + 4) = nullptr;
}



// ------------------------------------------------------------
// 0x42D430 sub_42D430
// ------------------------------------------------------------
int /*thiscall*/ sub_42D430(uint32_t *this, uint32_t *uArg2)
{
  uint32_t *fld_e1; // edx
  int *v3; // eax
  uint32_t v5[2]; // [esp+Ch] [ebp-8h] BYREF

  fld_e1 = (uint32_t *)*(this + 1);
  v3 = (int *)fld_e1[1];
  while ( *((uint8_t *)v3 + 21) == 0 )
  {
    if ( (unsigned int)v3[3] >= *uArg2 )
    {
      fld_e1 = v3;
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  if ( fld_e1 != (uint32_t *)*(this + 1) && *uArg2 >= fld_e1[3] )
    return (int)(fld_e1 + 4);
  v5[0] = *uArg2;
  v5[1] = 0;
  return *sub_42CE70((int)this, &uArg2, fld_e1, v5) + 16;
}



// ------------------------------------------------------------
// 0x42D4B0 sub_42D4B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42D4B0(int *this, uint32_t *uArg2, int nArg3, uint32_t *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 24 != 0 )
    v6 = (nArg3 - fld_e1) / 24;
  else
    v6 = 0;
  sub_42D130(this, nArg3, 1u, Block);
  *uArg2 = *(this + 1) + 24 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x42D520 sub_42D520
// ------------------------------------------------------------
void /*stdcall*/ sub_42D520(int nArg1, int nArg2)
{
  sub_42CC00(nArg1, nArg2);
}



// ------------------------------------------------------------
// 0x42D540 sub_42D540
// ------------------------------------------------------------
void /*thiscall*/ sub_42D540(int *this)
{
  int fld_e1; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
  {
    sub_42CC00(fld_e1, *(this + 2));
    j__free((void *)*(this + 1));
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
}



// ------------------------------------------------------------
// 0x42D590 sub_42D590
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42D590(uint32_t *this, int nArg2)
{
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  `eh vector constructor iterator'(this + 5, 0x10u, 6, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  *(this + 30) = 0;
  *(this + 31) = 0;
  *(this + 32) = 0;
  *(this + 35) = 0;
  *(this + 36) = 0;
  *(this + 37) = 0;
  sub_45F040(this);
  sub_45FA80(nArg2);
  return this;
}



// ------------------------------------------------------------
// 0x42D620 sub_42D620
// ------------------------------------------------------------
int /*thiscall*/ sub_42D620(int this)
{
  `eh vector constructor iterator'((void *)(this + 4), 0x10u, 4, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  `eh vector constructor iterator'((void *)(this + 112), 0x10u, 4, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  sub_42C250((void **)this);
  return this;
}



// ------------------------------------------------------------
// 0x42D6A0 sub_42D6A0
// ------------------------------------------------------------
int /*thiscall*/ sub_42D6A0(int this)
{
  `eh vector constructor iterator'((void *)(this + 20), 0x10u, 12, sub_4019A0, sub_5E5260);
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 276) = 0;
  *(uint32_t *)(this + 280) = 0;
  *(uint32_t *)(this + 284) = 0;
  *(uint32_t *)(this + 288) = 0;
  *(uint32_t *)(this + 296) = 0;
  *(uint32_t *)(this + 300) = 0;
  *(uint32_t *)(this + 304) = 0;
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 324) = 0;
  *(uint32_t *)(this + 328) = 0;
  *(uint32_t *)(this + 332) = 0;
  *(uint32_t *)(this + 336) = 0;
  *(uint32_t *)(this + 340) = 0;
  *(uint32_t *)(this + 344) = 0;
  *(uint32_t *)(this + 348) = 0;
  *(uint32_t *)(this + 352) = 0;
  sub_42CC40((char *)this);
  return this;
}



// ------------------------------------------------------------
// 0x42D780 sub_42D780
// ------------------------------------------------------------
void /*userpurge*/ sub_42D780(uint32_t *pArg1@<ecx>, float fArg2@<esi>, int nArg3, int nArg4)
{
  int nArg32; // edi
  uint32_t *v5; // esi
  uint32_t *v6; // eax
  int nArg42; // ebx
  int pObj; // esi
  double v9; // st7
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int *v13; // eax
  int *v14; // esi
  int *v15; // ebx
  int *v16; // esi
  float v17; // [esp+0h] [ebp-14h]

  nArg32 = nArg3;
  if ( *(float *)&nArg3 != 0.0 )
  {
    v5 = pArg1 + 16;
    v6 = (uint32_t *)sub_42D430(pArg1 + 16, &nArg3);
    nArg42 = nArg4;
    if ( *v6 != nArg4 )
    {
      *(uint32_t *)sub_42D430(v5, &nArg3) = nArg42;
      pObj = __RTDynamicCast(nArg32, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      if ( pObj != 0 )
      {
        nArg3 = dword_77F884;
        v9 = sub_42C710(pArg1, nArg32, 2);
        v17 = v9 * *(float *)&nArg3;
        v10 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pObj + 672))(pObj, 0, LODWORD(v17));
        sub_42B3F0((void *)(v10 + 4), fArg2);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 676))(pObj, 0);
        v11 = *(uint32_t *)pObj;
        v12 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj + 740))(pObj, 0, 1);
        (*(void (/*thiscall*/ **)(int, int))(v11 + 732))(pObj, v12);
      }
      v13 = (int *)__RTDynamicCast(
                     nArg32,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &CNRDPassiveObject `RTTI Type Descriptor',
                     0);
      v14 = v13;
      if ( v13 != nullptr && v13[171] > 0 )
      {
        v15 = (int *)((*(int (/*thiscall*/ **)(int *))(*v13 + 672))(v13) + 4);
        *v15 = (uint64_t)(sub_42C710(pArg1, nArg32, 2) * (double)*v15 * *(float *)&dword_77F884);
        v16 = (int *)(*(int (/*thiscall*/ **)(int *))(*v14 + 672))(v14);
        *v16 = (uint64_t)(sub_42C710(pArg1, nArg32, 2) * (double)*v16 * *(float *)&dword_77F884);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x42D8B0 sub_42D8B0
// ------------------------------------------------------------
char /*fastcall*/ sub_42D8B0(uint32_t *pArg1)
{
  int v1; // eax
  unsigned int v2; // edi
  int *v3; // ebx
  int v4; // esi
  int v5; // edx
  int v6; // eax
  int v7; // ecx
  int pObj2; // ecx
  int v9; // ecx
  int pObj3; // ecx
  int v11; // edx
  void *v12; // esi
  unsigned int v13; // edi
  int v14; // eax
  int v15; // edx
  int v16; // ebx
  int pObj; // eax
  uint8_t *pObj4; // esi
  int v19; // ebx
  int v20; // eax
  int v21; // eax
  int v22; // ecx
  int v23; // ebx
  int v24; // eax
  int v25; // eax
  uint32_t *pArg122; // ecx
  int v27; // ebx
  int v28; // eax
  int v29; // eax
  int v30; // edx
  int v31; // eax
  int v32; // edx
  int v33; // ebx
  int v34; // eax
  int v35; // eax
  int v36; // ebx
  uint32_t *v37; // eax
  uint32_t *pArg123; // edi
  uint32_t *v39; // esi
  int v40; // ecx
  int v41; // edx
  int v43; // [esp-10h] [ebp-50h]
  int v44; // [esp-8h] [ebp-48h]
  int v45; // [esp-8h] [ebp-48h]
  char v46; // [esp-4h] [ebp-44h]
  void *pBuf[4]; // [esp+0h] [ebp-40h] BYREF
  int v48; // [esp+10h] [ebp-30h]
  int v49; // [esp+14h] [ebp-2Ch]
  int v50; // [esp+18h] [ebp-28h] BYREF
  int v51; // [esp+1Ch] [ebp-24h]
  int v52; // [esp+20h] [ebp-20h]
  int v53; // [esp+24h] [ebp-1Ch]
  int v54; // [esp+28h] [ebp-18h] BYREF
  int v55; // [esp+2Ch] [ebp-14h] BYREF
  uint32_t *pArg12; // [esp+30h] [ebp-10h]
  int v57; // [esp+3Ch] [ebp-4h]

  v1 = pArg1[8];
  pArg12 = pArg1;
  if ( v1 == 2 )
  {
    LOBYTE(v1) = *((uint8_t *)pArg1 + 108);
    if ( (uint8_t)v1 != 0 )
    {
      v1 = pArg1[35];
      v2 = 0;
      if ( v1 != 0 )
      {
        v1 = (pArg1[36] - v1) / 24;
        v48 = v1;
        if ( v1 != 0 )
        {
          v3 = (int *)pArg1[35];
          v4 = *(uint32_t *)(pArg1[4] + 104);
          v55 = 0;
          while ( 1 )
          {
            v5 = *(uint32_t *)(v4 + 120);
            v6 = v5 != 0 ? (*(uint32_t *)(v4 + 124) - v5) >> 2 : 0;
            if ( (int)v2 >= v6 )
              break;
            v7 = *(uint32_t *)(v4 + 120);
            if ( v7 != 0 && v2 < (*(uint32_t *)(v4 + 124) - v7) >> 2 )
              pObj2 = *(uint32_t *)(v7 + 4 * v2);
            else
              pObj2 = 0;
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529) != 0 )
            {
              v9 = *(uint32_t *)(v4 + 120);
              if ( v9 != 0 && v2 < (*(uint32_t *)(v4 + 124) - v9) >> 2 )
                pObj3 = *(uint32_t *)(v9 + 4 * v2);
              else
                pObj3 = 0;
              if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 376))(pObj3) == 100 )
                ++v55;
            }
            pArg1 = pArg12;
            ++v2;
          }
          v11 = v3[1];
          v12 = (void *)v3[2];
          v13 = v3[4];
          v51 = *v3;
          v14 = v3[3];
          v53 = v11;
          v15 = v3[5];
          v16 = pArg1[30];
          v52 = v14;
          v48 = v15;
          v49 = (int)(pArg1 + 24);
          v1 = sub_699000((int)(pArg1 + 24));
          if ( v1 >= v16 )
          {
            LOBYTE(v1) = (uint8_t)pArg12;
            if ( v55 < pArg12[31] )
            {
              v50 = *(uint32_t *)(*(uint32_t *)(16 * v53 + pArg12[5] + 204) + 4 * v52);
              pObj = sub_4ABE10(v50, v12, 0);
              pObj4 = (uint8_t *)pObj;
              if ( pObj != 0 )
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, 100);
                v19 = *(uint32_t *)(pArg12[6] + 476);
                v20 = *(uint32_t *)(v19 + 444);
                if ( v20 == 0 || v13 >= (*(uint32_t *)(v19 + 448) - v20) / 12 )
                {
                  v21 = sub_4DA030(v19 + 440);
                  off_77F3FC((char *)&byte_6C4088, v13, v21);
                  v13 = 0;
                }
                v22 = *(uint32_t *)(*(uint32_t *)(pArg12[6] + 476) + 444);
                v23 = *(uint32_t *)pObj4;
                v24 = *(uint32_t *)(12 * v13 + v22 + 4);
                v55 = *(uint32_t *)(12 * v13 + v22);
                v54 = v24;
                v25 = (*(int (/*thiscall*/ **)(uint8_t *))(v23 + 436))(pObj4);
                (*(void (/*thiscall*/ **)(uint8_t *, int, int, int))(v23 + 112))(pObj4, v55, v54, v25);
                pArg122 = pArg12;
                v43 = v51;
                pObj4[7801] = 1;
                sub_45FE80(pArg122[7], v13, 529, v43, (int)pObj4, 0, 0);
                v27 = *(uint32_t *)pObj4;
                v28 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 144))(dword_8F8520);
                (*(void (/*thiscall*/ **)(uint8_t *, int))(v27 + 1044))(pObj4, v28);
                (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj4 + 320))(pObj4);
                if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj4 + 308))(pObj4) != 0 )
                {
                  v29 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj4 + 120))(pObj4);
                  v30 = *(uint32_t *)pObj4;
                  v55 = v29;
                  v31 = (*(int (/*thiscall*/ **)(uint8_t *))(v30 + 124))(pObj4);
                  v32 = *(uint32_t *)pObj4;
                  v54 = v31;
                  if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(v32 + 136))(pObj4, v55, v31, 0) == 0 )
                  {
                    v33 = *(uint32_t *)pObj4;
                    v34 = (*(int (/*thiscall*/ **)(uint8_t *, int, int, int))(*(uint32_t *)pObj4 + 124))(pObj4, 300, 1, 5);
                    v35 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pObj4 + 120))(pObj4, v34);
                    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int *, int *, int))(v33 + 140))(
                           pObj4,
                           &v55,
                           &v54,
                           v35) != 0 )
                    {
                      v36 = *(uint32_t *)pObj4;
                      pBuf[0] = (void *)(*(int (/*thiscall*/ **)(uint8_t *, void *))(*(uint32_t *)pObj4 + 128))(pObj4, pBuf[0]);
                      v46 = v54;
                      v44 = v55;
                      (*(void (/*thiscall*/ **)(uint8_t *))(v36 + 108))(pObj4);
                      v37 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pObj4 + 60))(pObj4, 1, 1);
                      sub_49FFC0(v37, v13, (int)pObj4, v44, v46);
                      off_77F3FC((char *)&byte_6C4058, v13, v55, v54);
                    }
                    else
                    {
                      off_77F3FC((char *)&byte_6C402C, v13);
                    }
                  }
                }
                if ( v53 == 1 || v53 == 2 )
                {
                  memset(&pBuf[1], 0, 12);
                  v41 = *(uint32_t *)pObj4;
                  v57 = 0;
                  (*(void (/*thiscall*/ **)(uint8_t *, unsigned int, void **, int))(v41 + 1160))(
                    pObj4,
                    v52 + v13 + v50,
                    pBuf,
                    v53);
                  v57 = -1;
                  sub_5E5260(pBuf);
                }
                else if ( v53 == 3 )
                {
                  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj4 + 1120))(pObj4);
                }
                sub_495C00(1);
                pArg123 = pArg12;
                v39 = pArg12 + 34;
                sub_42C920(&v50, pArg12[35]);
                v1 = sub_4FEF30(v39);
                if ( v1 != 0 )
                {
                  v40 = v49;
                  v45 = v48;
                  *(uint8_t *)(v49 + 13) = 0;
                  *(uint8_t *)(v40 + 14) = 0;
                  LOBYTE(v1) = sub_698F90(v40, v45, 0);
                }
                else
                {
                  *((uint8_t *)pArg123 + 108) = 0;
                }
              }
              else
              {
                LOBYTE(v1) = off_77F3FC((char *)&byte_6C3FF4, v50);
              }
            }
          }
        }
      }
    }
  }
  return v1;
}


// ------------------------------------------------------------
// 0x42DCA0 sub_42DCA0
// ------------------------------------------------------------
void /*thiscall*/ sub_42DCA0(uint32_t *this)
{
  uint32_t *pThis_10; // esi
  uint32_t *v3; // eax
  int v4; // edi
  int v5; // eax
  int pObj; // esi
  int v7; // eax

  pThis_10 = this + 16;
  sub_41CAA0(*(void **)(*(this + 17) + 4));
  *(uint32_t *)(pThis_10[1] + 4) = pThis_10[1];
  v3 = (uint32_t *)pThis_10[1];
  v4 = 0;
  pThis_10[2] = 0;
  *v3 = v3;
  *(uint32_t *)(pThis_10[1] + 8) = pThis_10[1];
  do
  {
    v5 = sub_578E80(v4);
    if ( v5 != 0 )
    {
      pObj = *(uint32_t *)(v5 + 196);
      if ( pObj != 0 )
      {
        v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj + 388))(*(uint32_t *)(v5 + 196));
        sub_42D780(this, *(float *)&pObj, pObj, v7);
      }
    }
    ++v4;
  }
  while ( v4 < 8 );
}



// ------------------------------------------------------------
// 0x42DD10 sub_42DD10
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42DD10(int *this, uint32_t *Block)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 24;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 24 )
    return sub_42D4B0(this, &Block, *(this + 2), Block);
  fld_e22 = *(this + 2);
  result = (uint32_t *)sub_5044B0(fld_e22, 1, Block);
  *(this + 2) = fld_e22 + 24;
  return result;
}



// ------------------------------------------------------------
// 0x42DDA0 sub_42DDA0
// ------------------------------------------------------------
void /*stdcall*/ sub_42DDA0(int nArg1, int nArg2)
{
  int i; // esi

  for ( i = nArg1; i != nArg2; i += 44 )
    sub_42C220(i);
}



// ------------------------------------------------------------
// 0x42DDD0 sub_42DDD0
// ------------------------------------------------------------
void /*thiscall*/ sub_42DDD0(int *this)
{
  int fld_e5; // eax
  uint32_t *pThis_4; // esi

  fld_e5 = *(this + 5);
  pThis_4 = this + 4;
  if ( fld_e5 != 0 )
  {
    sub_42CC00(fld_e5, *(this + 6));
    j__free((void *)pThis_4[1]);
  }
  pThis_4[1] = 0;
  pThis_4[2] = 0;
  pThis_4[3] = 0;
}



// ------------------------------------------------------------
// 0x42DE20 sub_42DE20
// ------------------------------------------------------------
void **/*thiscall*/ sub_42DE20(void *this)
{
  int pThis_2E; // edi
  int pThis_2F; // ecx
  void **result; // eax
  int i; // [esp+Ch] [ebp-4h]

  *(uint32_t *)this = 0;
  sub_4015C0((void *)szPassword, 0);
  sub_4015C0((void *)szPassword, 0);
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 24) = 0xFFFF;
  *((uint32_t *)this + 25) = 0;
  *((uint8_t *)this + 104) = 0;
  *((uint32_t *)this + 27) = -1;
  *((uint32_t *)this + 28) = 1;
  *((uint32_t *)this + 29) = -1;
  *((uint32_t *)this + 30) = -1;
  *((uint32_t *)this + 31) = -1;
  *((uint32_t *)this + 32) = -1;
  *((uint32_t *)this + 33) = -1;
  *((uint32_t *)this + 34) = -1;
  *((uint32_t *)this + 35) = -1;
  *((uint32_t *)this + 36) = -1;
  *((uint32_t *)this + 37) = -1;
  *((uint32_t *)this + 38) = -1;
  *((uint32_t *)this + 39) = -1;
  *((uint32_t *)this + 40) = -1;
  if ( *((uint32_t *)this + 42) != 0 )
    j__free(*((void **)this + 42));
  *((uint32_t *)this + 42) = 0;
  *((uint32_t *)this + 43) = 0;
  *((uint32_t *)this + 44) = 0;
  pThis_2E = *((uint32_t *)this + 46);
  if ( pThis_2E != 0 )
  {
    pThis_2F = *((uint32_t *)this + 47);
    for ( i = pThis_2F; pThis_2E != pThis_2F; pThis_2E += 16 )
    {
      if ( *(uint32_t *)(pThis_2E + 4) != 0 )
      {
        j__free(*(void **)(pThis_2E + 4));
        pThis_2F = i;
      }
      *(uint32_t *)(pThis_2E + 4) = 0;
      *(uint32_t *)(pThis_2E + 8) = 0;
      *(uint32_t *)(pThis_2E + 12) = 0;
    }
    j__free(*((void **)this + 46));
  }
  *((uint32_t *)this + 46) = 0;
  *((uint32_t *)this + 47) = 0;
  *((uint32_t *)this + 48) = 0;
  result = sub_42C250((void **)this + 49);
  *((uint8_t *)this + 464) = 0;
  *((uint32_t *)this + 117) = 0;
  *((uint32_t *)this + 118) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42DF70 sub_42DF70
// ------------------------------------------------------------
int /*thiscall*/ sub_42DF70(int this)
{
  *(uint32_t *)(this + 28) = 15;
  *(uint32_t *)(this + 24) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 56) = 15;
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 36) = 0;
  *(uint32_t *)(this + 96) = 0xFFFF;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 104) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  sub_42D620(this + 196);
  sub_42DE20((void *)this);
  return this;
}



// ============================================================
// §18 CNWarRoomModule 战争房间模块（0x42E010-0x42F350）
//   0x42F250 = 评价 HUD 状态复位（+556/+592/+628 全组清零，见函数注）
// ============================================================
// ------------------------------------------------------------
// 0x42E010 CNWarRoomModule__vmt4
// ------------------------------------------------------------
char /*usercall*/ CNWarRoomModule__vmt4@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // edi
  int v5; // eax
  int v6; // eax
  uint8_t v7; // al
  uint8_t *v8; // eax
  int i; // ecx

  sub_4AEB30(&unk_9A02B0);
  sub_433690();
  sub_4294E0(*(uint32_t *)(pArg1 + 16), nArg2, nArg3);
  v4 = 0;
  if ( *(uint8_t *)(*((uint32_t *)dword_8F8528 + 625) + 44) != 0 )
    v4 = sub_45E870(pt.x, pt.y, 1);
  v5 = *(uint32_t *)(pArg1 + 84);
  if ( v5 != v4 )
  {
    if ( v5 != 0 && (uint8_t)sub_45E680(*(uint32_t *)(pArg1 + 84)) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(**(uint32_t **)(pArg1 + 84) + 284))(
        *(uint32_t *)(pArg1 + 84),
        0,
        0,
        1,
        2);
    *(uint32_t *)(pArg1 + 84) = v4;
  }
  if ( *(uint32_t *)(pArg1 + 84) != 0 )
  {
    v6 = sub_699000(pArg1 + 36);
    v7 = sub_42B420(100, 255, v6, 500);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, int))(**(uint32_t **)(pArg1 + 84) + 284))(
      *(uint32_t *)(pArg1 + 84),
      1,
      (v7 << 24) | 0xFF9B,
      0,
      1);
  }
  sub_42D8B0((uint32_t *)pArg1);
  sub_42C110(pArg1);
  LOBYTE(v8) = *(uint8_t *)(pArg1 + 184);
  if ( (uint8_t)v8 == 0 )
  {
    *(uint8_t *)(pArg1 + 184) = 1;
    v8 = (uint8_t *)(dword_8F8520 + 1048692);
    for ( i = 8; i != 0; --i )
    {
      if ( *v8 == 0 )
      {
        *v8 = 1;
        v8[1] = 0;
        v8[2] = 0;
      }
      v8 += 28;
    }
  }
  return (char)v8;
}



// ------------------------------------------------------------
// 0x42E120 sub_42E120
// ------------------------------------------------------------
void /*thiscall*/ sub_42E120(int *this, int ArgList, int nArg3, char pszArg4)
{
  int nArg32; // edi
  int v6; // eax
  int pObj; // esi
  int v8; // ecx
  int v9; // eax
  int v10; // [esp+8h] [ebp-4h] BYREF

  nArg32 = nArg3;
  if ( nArg3 != 0 )
  {
    v6 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
    if ( nArg32 != v6 )
    {
      LOBYTE(v6) = pszArg4 == 0;
      (*(void (/*thiscall*/ **)(int, int, int, int, uint32_t))(*(uint32_t *)dword_8F8520 + 100))(
        dword_8F8520,
        ArgList,
        nArg32,
        v6,
        0);
    }
    pObj = *(uint32_t *)(nArg32 + 196);
    if ( pObj != 0 )
    {
      sub_45FE80(*(this + 7), nArg32, 273, *(uint16_t *)(nArg32 + 4), pObj, 0, 0);
      v8 = *(uint16_t *)(nArg32 + 4);
      v10 = 0;
      nArg3 = 0;
      sub_48C2A0(&v10, &nArg3, 0, pObj, ArgList * v8);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 112))(pObj, v10, nArg3, 0);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 148))(pObj, 1);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1020))(pObj);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1212))(pObj, ArgList);
      v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);
      sub_42D780(this, *(float *)&pObj, pObj, v9);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1056))(pObj, 1);
      sub_4632D0(*((uint32_t *)dword_8F8528 + 4));
    }
    else
    {
      off_77F3FC(aCriticalErrorW_0, ArgList);
    }
  }
}



// ------------------------------------------------------------
// 0x42E230 sub_42E230
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42E230(int *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7)
{
  uint32_t Block[6]; // [esp+0h] [ebp-18h] BYREF

  Block[0] = nArg2;
  Block[2] = nArg4;
  Block[1] = nArg3;
  Block[4] = nArg6;
  Block[3] = nArg5;
  Block[5] = nArg7;
  return sub_42DD10(this + 34, Block);
}



// ------------------------------------------------------------
// 0x42E270 sub_42E270
// ------------------------------------------------------------
int /*thiscall*/ sub_42E270(int this, int ArgList)
{
  uint8_t *v3; // ecx
  _BOOL2 v4; // dx
  int fld_4C; // edi
  int v6; // eax
  const char *v7; // eax
  unsigned int v8; // edi
  int fld_1C; // ecx
  int v10; // edx
  int v11; // eax
  int v12; // edx
  unsigned int v13; // edi
  int fld_1C2; // ecx
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // ebx
  int v19; // eax
  int v20; // edi
  int fld_7C; // edi
  int v22; // edi
  uint32_t *v23; // eax
  int v24; // eax
  int fld_58; // edx
  int dword_99FF082; // [esp+Ch] [ebp-210h]
  int v28; // [esp+10h] [ebp-20Ch] BYREF
  int v29; // [esp+14h] [ebp-208h] BYREF
  char Buffer[512]; // [esp+18h] [ebp-204h] BYREF
  int dword_796E502; // [esp+218h] [ebp-4h]
  int ArgLista; // [esp+224h] [ebp+8h]

  dword_796E502 = dword_796E50;
  off_77F3FC((char *)&byte_6C4154, ArgList);
  sub_49CD70(0);
  sub_44E850(dword_8F8528, 42);
  *(uint32_t *)(*((uint32_t *)dword_8F8528 + 4) + 1212) = (uint16_t)word_8F7C10;
  if ( (uint16_t)word_8F7C10 < (uint16_t)word_8F7C14 )
  {
    word_8F7C10 += *(uint16_t *)(*(uint32_t *)(this + 20) + 456);
    v3 = *((uint8_t **)dword_8F8528 + 4);
    v4 = word_8F7C10 != word_8F7C14;
    v3[1196] = 1;
    v3 += 1184;
    v3[13] = 0;
    v3[14] = 0;
    sub_698F90((int)v3, v4 ? 1000 : 5000, -500);
  }
  if ( *(uint32_t *)(this + 152) == 1 )
  {
    *(uint32_t *)(this + 152) = 0;
    *(uint8_t *)(this + 168) = 1;
    *(uint8_t *)(this + 169) = 0;
    *(uint8_t *)(this + 170) = 0;
    sub_698F90(this + 156, 500, 0);
  }
  if ( ArgList == 1 )
  {
    fld_4C = dword_8F7D28[dword_77F888 + *(uint32_t *)(this + 76)];
    v6 = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) - fld_4C;
    if ( v6 < 0 )
      v6 = 0;
    (*(void (/*thiscall*/ **)(uint32_t, int))(***((uint32_t ***)dword_8F852C + 3) + 40))(**((uint32_t **)dword_8F852C + 3), v6);
    v7 = (const char *)sub_422E70(1940);
    sprintf(Buffer, v7, fld_4C);
    sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -13435036, 0, -1);
    sub_42B690(1);
    sub_42DCA0(this);
    v8 = 0;
    while ( 1 )
    {
      fld_1C = *(uint32_t *)(this + 28);
      v10 = *(uint32_t *)(fld_1C + 120);
      v11 = v10 != 0 ? (*(uint32_t *)(fld_1C + 124) - v10) >> 2 : 0;
      if ( (int)v8 >= v11 )
        break;
      v12 = *(uint32_t *)(fld_1C + 120);
      if ( v12 != 0 && v8 < (*(uint32_t *)(fld_1C + 124) - v12) >> 2 )
      {
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v12 + 4 * v8) + 320))(*(uint32_t *)(v12 + 4 * v8));
        ++v8;
      }
      else
      {
        (*(void (**)(void))(MEMORY[0] + 320))();
        ++v8;
      }
    }
  }
  else if ( ArgList == 3 )
  {
    sub_42C4C0(this);
    sub_4602C0(*(uint32_t *)(*(uint32_t *)(this + 24) + 476));
    sub_48E870(*(uint32_t *)(this + 28));
    sub_42B720(1, 3000);
    v13 = 0;
    while ( 1 )
    {
      fld_1C2 = *(uint32_t *)(this + 28);
      v15 = *(uint32_t *)(fld_1C2 + 120);
      v16 = v15 != 0 ? (*(uint32_t *)(fld_1C2 + 124) - v15) >> 2 : 0;
      if ( (int)v13 >= v16 )
        break;
      v17 = *(uint32_t *)(fld_1C2 + 120);
      if ( v17 != 0 && v13 < (*(uint32_t *)(fld_1C2 + 124) - v17) >> 2 )
      {
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v17 + 4 * v13) + 320))(*(uint32_t *)(v17 + 4 * v13));
        ++v13;
      }
      else
      {
        (*(void (**)(void))(MEMORY[0] + 320))();
        ++v13;
      }
    }
    if ( *(uint8_t *)(dword_8F7C04 + 8052) == 0 )
    {
      v18 = *(uint32_t *)(dword_99FF08 + 4);
      dword_99FF082 = dword_99FF08;
      v19 = sub_48FCA0();
      v20 = sub_48FD70(v19);
      ArgLista = v18 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
      fld_7C = *(uint32_t *)(this + 124) * (*(uint32_t *)(this + 88) + sub_48FCA0()) * ArgLista + v20;
      v22 = sub_48FBB0(dword_99FF082) + fld_7C;
      sub_48C3A0(0, &v28, &v29, dword_8F7C04, v22);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)dword_8F7C04 + 108))(dword_8F7C04, v28, v29, 0);
      v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 60))(dword_8F7C04);
      sub_49FFC0(v23, v22, this, 1, 1);
    }
  }
  sub_432EA0("R_GRENSELOS_BATTLE", -1, 0, 0);
  sub_42B780(1);
  v24 = sub_4B09A0(dword_8F7C04);
  sub_4B09B0(v24);
  fld_58 = *(uint32_t *)(this + 88) + 1;
  *(uint32_t *)(this + 88) = fld_58;
  *(uint32_t *)(*((uint32_t *)dword_8F8528 + 634) + 88) = fld_58;
  if ( *(uint32_t *)(this + 88) == *(uint32_t *)(this + 92) )
    return sub_49AA90("last battle start");
  else
    return sub_49AA90("battle start");
}


// ------------------------------------------------------------
// 0x42E620 sub_42E620
// ------------------------------------------------------------
int /*thiscall*/ sub_42E620(int *this)
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);
  result = 0;
  if ( fld_e1 != 0 )
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 44 )
      sub_42C220(fld_e1);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42E670 sub_42E670
// ------------------------------------------------------------
void /*stdcall*/ sub_42E670(void **pArg1, void **pArg2)
{
  void **i; // esi

  for ( i = pArg1; i != pArg2; i += 5 )
    sub_42D400(i);
}



// ------------------------------------------------------------
// 0x42E6A0 sub_42E6A0
// ------------------------------------------------------------
int /*thiscall*/ sub_42E6A0(void ****this)
{
  void ****pThis_7; // ebx
  void ***k; // esi
  void **v3; // edi
  int result; // eax
  int i; // [esp+Ch] [ebp-8h]
  int j; // [esp+10h] [ebp-4h]

  pThis_7 = this + 7;
  for ( i = 6; i != 0; --i )
  {
    for ( j = 2; j != 0; --j )
    {
      for ( k = *(pThis_7 - 1); k != *pThis_7; k += 2 )
      {
        v3 = *k;
        if ( *k != nullptr )
        {
          sub_42AF90(*k);
          sub_657740(v3, 228);
        }
        *k = nullptr;
      }
      pThis_7 += 4;
      result = j - 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42E710 sub_42E710
// ------------------------------------------------------------
void /*thiscall*/ sub_42E710(int this)
{
  sub_42E6A0((void ****)this);
  sub_4017E0(this + 292);
  if ( *(uint32_t *)(this + 232) != 0 )
    j__free(*(void **)(this + 232));
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  if ( *(uint32_t *)(this + 216) != 0 )
    j__free(*(void **)(this + 216));
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  `eh vector destructor iterator'((void *)(this + 20), 0x10u, 12, (void (/*thiscall*/ *)(void *))sub_5E5260);
}



// ------------------------------------------------------------
// 0x42E7C0 sub_42E7C0
// ------------------------------------------------------------
void /*stdcall*/ sub_42E7C0(int *pDwArg1, int *pDwArg2)
{
  int *i; // esi

  for ( i = pDwArg1; i != pDwArg2; i += 8 )
    sub_42DDD0(i);
}



// ------------------------------------------------------------
// 0x42E7F0 sub_42E7F0
// ------------------------------------------------------------
void /*thiscall*/ sub_42E7F0(int this)
{
  void **fld_3C; // edi
  int fld_B8; // eax

  fld_3C = *(void ***)(this + 60);
  if ( fld_3C != nullptr )
  {
    sub_42AF90(fld_3C);
    sub_657740(fld_3C, 228);
  }
  *(uint32_t *)(this + 60) = 0;
  sub_42C370(this + 196);
  fld_B8 = *(uint32_t *)(this + 184);
  if ( fld_B8 != 0 )
  {
    sub_42CC00(fld_B8, *(uint32_t *)(this + 188));
    j__free(*(void **)(this + 184));
  }
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  if ( *(uint32_t *)(this + 168) != 0 )
    j__free(*(void **)(this + 168));
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
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
// 0x42E8F0 sub_42E8F0
// ------------------------------------------------------------
void */*thiscall*/ sub_42E8F0(void *this, char ArgList)
{
  sub_42DF70((int)this);
  nullsub_3();
  sub_476AF0(ArgList);
  return this;
}



// ------------------------------------------------------------
// 0x42E940 sub_42E940
// ------------------------------------------------------------
void /*thiscall*/ sub_42E940(void *this)
{
  nullsub_3();
  sub_42E7F0((int)this);
}



// ------------------------------------------------------------
// 0x42E990 sub_42E990
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42E990(uint32_t *this, void *Block)
{
  void *fld_e5; // edi
  uint32_t *result; // eax
  void *pMem; // eax
  int fld_e4; // edx

  off_77F3FC((char *)&byte_6C4180, Block);
  *(this + 20) = Block;
  fld_e5 = (void *)*(this + 5);
  if ( Block == (void *)-1 )
  {
    if ( fld_e5 != nullptr )
    {
      nullsub_3();
      sub_42E7F0((int)fld_e5);
      j__free(fld_e5);
    }
    result = (uint32_t *)*(this + 4);
    *(this + 5) = 0;
    result[27] = 0;
  }
  else
  {
    if ( fld_e5 != nullptr )
    {
      nullsub_3();
      sub_42E7F0((int)fld_e5);
      j__free(fld_e5);
    }
    *(this + 5) = 0;
    pMem = operator new(0x1F0u);
    if ( pMem != nullptr )
      result = sub_42E8F0(pMem, *(this + 20));
    else
      result = nullptr;
    fld_e4 = *(this + 4);
    *(this + 5) = result;
    *(uint32_t *)(fld_e4 + 108) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42EA90 sub_42EA90
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42EA90(uint32_t *this)
{
  uint32_t *result; // eax

  sub_487080(dword_8F852C);
  sub_49A9A0(*((uint32_t *)dword_8F8528 + 634));
  *(this + 19) = -1;
  result = sub_42E990(this, (void *)0xFFFFFFFF);
  *(this + 8) = -1;
  if ( dword_99FF08 != 0 )
  {
    result = (uint32_t *)sub_48FD80(dword_99FF08);
    if ( result == nullptr )
      *(this + 47) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42EAF0 sub_42EAF0
// ------------------------------------------------------------
char /*thiscall*/ sub_42EAF0(uint32_t *this, int pArg2)
{
  int v3; // esi
  int v4; // ebx
  unsigned int v5; // ebx
  int v8; // [esp+18h] [ebp+8h]

  v3 = 20 * pArg2;
  v4 = *((int16_t *)dword_8F7C48 + 10 * pArg2);
  v8 = *((int16_t *)dword_8F7C48 + 10 * pArg2 + 1);
  if ( *(uint32_t *)(*(int (/*stdcall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 672))(3) >= v4
    && *(uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3) <= v8 )
  {
    v5 = dword_8F7D28[pArg2];
    if ( (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3)) < v5 )
      return 0;
  }
  *(this + 19) = pArg2;
  dword_8F7C40 = (int)dword_8F7C48 + v3;
  sub_42E990(this, (void *)(pArg2 + 2000));
  return 1;
}



// ------------------------------------------------------------
// 0x42EB90 sub_42EB90
// ------------------------------------------------------------
int /*thiscall*/ sub_42EB90(int this)
{
  int *fld_4; // esi
  int result; // eax
  int *i; // edi

  fld_4 = *(int **)(this + 4);
  result = 0;
  if ( fld_4 != nullptr )
  {
    for ( i = *(int **)(this + 8); fld_4 != i; fld_4 += 8 )
      sub_42DDD0(fld_4);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42EBD0 sub_42EBD0
// ------------------------------------------------------------
uint8_t /*thiscall*/ sub_42EBD0(int this)
{
  uint8_t result; // al
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  char *pMem2; // eax
  char *v6; // eax

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
    sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));
    *(uint32_t *)(this + 76) = -1;
    result = (uint8_t)sub_42E990((uint32_t *)this, (void *)0xFFFFFFFF);
    *(uint8_t *)(this + 108) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42ECF0 sub_42ECF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42ECF0(uint32_t *this, int nArg2, int nArg3)
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
  sub_48F470(nArg2, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x42EDE0 sub_42EDE0
// ------------------------------------------------------------
void /*thiscall*/ sub_42EDE0(int this)
{
  sub_48EAA0();
  sub_42E620((int *)(this + 504));
  if ( *(uint32_t *)(this + 492) != 0 )
    j__free(*(void **)(this + 492));
  *(uint32_t *)(this + 492) = 0;
  *(uint32_t *)(this + 496) = 0;
  *(uint32_t *)(this + 500) = 0;
  sub_42EB90(this + 376);
  sub_42EB90(this + 360);
  sub_42E710(this);
}



// ------------------------------------------------------------
// 0x42EE80 sub_42EE80
// ------------------------------------------------------------
char /*thiscall*/ sub_42EE80(int this)
{
  char result; // al
  void *fld_1C; // edi
  uint32_t *pMem; // eax
  uint32_t *v5; // eax
  uint32_t *fld_10; // ecx
  void *fld_18; // edi
  uint32_t *pMem2; // eax
  uint32_t *v9; // eax
  int fld_102; // ecx
  uint32_t *fld_44; // eax
  int v12; // [esp+Ch] [ebp-10h]

  result = *(uint8_t *)(this + 4);
  if ( result != 0 )
  {
    if ( dword_99FF08 != 0 )
    {
      nullsub_3();
      v12 = dword_99FF08 + 4;
      sub_424100(*(uint32_t **)(this + 16), 0);
      fld_1C = *(void **)(this + 28);
      if ( fld_1C != nullptr )
      {
        sub_42C770(*(uint32_t *)(this + 28));
        j__free(fld_1C);
      }
      *(uint32_t *)(this + 28) = 0;
      pMem = operator new(0xA0u);
      if ( pMem != nullptr )
        v5 = sub_42D590(pMem, 0);
      else
        v5 = nullptr;
      fld_10 = *(uint32_t **)(this + 16);
      *(uint32_t *)(this + 28) = v5;
      sub_424100(fld_10, (int)v5);
      sub_425500(*(uint32_t *)(this + 16), 0);
      fld_18 = *(void **)(this + 24);
      if ( fld_18 != nullptr )
      {
        sub_42EDE0(*(uint32_t *)(this + 24));
        j__free(fld_18);
      }
      *(uint32_t *)(this + 24) = 0;
      pMem2 = operator new(0x208u);
      if ( pMem2 != nullptr )
        v9 = sub_42ECF0(pMem2, *(uint32_t *)(v12 + 72), 0);
      else
        v9 = nullptr;
      fld_102 = *(uint32_t *)(this + 16);
      *(uint32_t *)(this + 24) = v9;
      sub_425500(fld_102, (int)v9);
      *(uint32_t *)(this + 88) = 0;
      *(uint32_t *)(this + 92) = 0;
      *(uint32_t *)(this + 124) = 0;
      *(uint32_t *)(this + 132) = 0;
      *(uint32_t *)(this + 128) = 0;
      if ( *(uint32_t *)(this + 140) != 0 )
        j__free(*(void **)(this + 140));
      *(uint32_t *)(this + 140) = 0;
      *(uint32_t *)(this + 144) = 0;
      *(uint32_t *)(this + 148) = 0;
      *(uint8_t *)(this + 108) = 0;
      *(uint32_t *)(this + 152) = 2;
      *(uint8_t *)(this + 168) = 0;
      sub_41CAA0(*(void **)(*(uint32_t *)(this + 68) + 4));
      *(uint32_t *)(*(uint32_t *)(this + 68) + 4) = *(uint32_t *)(this + 68);
      fld_44 = *(uint32_t **)(this + 68);
      *(uint32_t *)(this + 72) = 0;
      *fld_44 = fld_44;
      *(uint32_t *)(*(uint32_t *)(this + 68) + 8) = *(uint32_t *)(this + 68);
      result = sub_49B930(*((uint32_t **)dword_8F8528 + 634), "dungeon/warroom/warroomBattleTalk.tlk");
      *(uint8_t *)(this + 184) = 0;
      *(uint32_t *)(this + 188) = 0;
    }
    else
    {
      return off_77F3FC(aCnwarroomGetmy);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42F050 sub_42F050
// ------------------------------------------------------------
void /*thiscall*/ sub_42F050(int *this, int ArgList)
{
  void *fld_e7; // edi
  void *fld_e6; // edi
  void *fld_e5; // edi

  off_77F3FC((char *)&byte_6C41F8, ArgList);
  fld_e7 = (void *)*(this + 7);
  if ( fld_e7 != nullptr )
  {
    sub_42C770(*(this + 7));
    j__free(fld_e7);
  }
  fld_e6 = (void *)*(this + 6);
  *(this + 7) = 0;
  if ( fld_e6 != nullptr )
  {
    sub_42EDE0((int)fld_e6);
    j__free(fld_e6);
  }
  fld_e5 = (void *)*(this + 5);
  *(this + 6) = 0;
  if ( fld_e5 != nullptr )
  {
    sub_42E940(fld_e5);
    j__free(fld_e5);
  }
  *(this + 5) = 0;
}



// ------------------------------------------------------------
// 0x42F0D0 sub_42F0D0
// ------------------------------------------------------------
void /*thiscall*/ sub_42F0D0(int this)
{
  void (/*thiscall*/ ***pThis_C)(uint32_t, int); // ecx
  void *fld_10; // edi
  void *fld_14; // edi
  void *fld_18; // edi
  void *fld_1C; // edi

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
    fld_14 = *(void **)(this + 20);
    *(uint32_t *)(this + 16) = 0;
    if ( fld_14 != nullptr )
    {
      sub_42E940(fld_14);
      j__free(fld_14);
    }
    fld_18 = *(void **)(this + 24);
    *(uint32_t *)(this + 20) = 0;
    if ( fld_18 != nullptr )
    {
      sub_42EDE0((int)fld_18);
      j__free(fld_18);
    }
    fld_1C = *(void **)(this + 28);
    *(uint32_t *)(this + 24) = 0;
    if ( fld_1C != nullptr )
    {
      sub_42C770((int)fld_1C);
      j__free(fld_1C);
    }
    *(uint32_t *)(this + 28) = 0;
  }
}



// ------------------------------------------------------------
// 0x42F160 sub_42F160
// ------------------------------------------------------------
void /*thiscall*/ sub_42F160(int this, unsigned int uArg2, int nArg3)
{
  int fld_20; // edi
  int pThis_24; // ecx

  fld_20 = *(uint32_t *)(this + 32);
  pThis_24 = this + 36;
  *(uint32_t *)(this + 32) = uArg2;
  *(uint8_t *)(pThis_24 + 13) = 0;
  *(uint8_t *)(pThis_24 + 14) = 0;
  sub_698F90(pThis_24, 0, nArg3);
  if ( uArg2 <= 1 )
    sub_424A40(*(uint32_t **)(this + 16), dword_8F7C04);
  switch ( uArg2 )
  {
    case 0xFFFFFFFF:
      sub_42F050((int *)this, fld_20);
      break;
    case 0u:
      sub_42BF10(this, fld_20);
      break;
    case 1u:
      sub_42C000((int *)this, fld_20);
      break;
    case 2u:
      sub_42E270(this, fld_20);
      break;
    case 3u:
      sub_42B610((uint32_t *)this, fld_20);
      break;
    case 4u:
      sub_42C820((uint32_t *)this, fld_20);
      break;
    default:
      return;
  }
}



// ------------------------------------------------------------
// 0x42F220 sub_42F220
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_42F220(uint32_t *this)
{
  if ( *(this + 37) == -1 )
    sub_4938F0((int)this);
  return this + 15;
}



// ------------------------------------------------------------
// 0x42F240 sub_42F240
// ------------------------------------------------------------
int /*thiscall*/ sub_42F240(uint32_t *this)
{
  int fld_e26; // eax

  fld_e26 = *(this + 26);
  if ( fld_e26 != 0 )
    return *(uint32_t *)fld_e26;
  else
    return -1;
}



// ------------------------------------------------------------
// 0x42F250 sub_42F250
// ------------------------------------------------------------
// 【评价 HUD 状态复位】+556 值/+560 钟/+584 窗、+592/+596/+620、+628/+632/+656 全组
//   清零，+636 = -1【推断：评价 HUD 的关卡进出复位；位于 VirtualCharacter 虚表区，
//   字段布局与 0x426820 的 this 同构】。
int /*thiscall*/ sub_42F250(int this)
{
  *(uint32_t *)(this + 96) = 18;
  *(uint32_t *)(this + 308) = 4;
  *(uint32_t *)(this + 312) = 4;
  *(uint32_t *)(this + 316) = 0;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 324) = 0;
  *(uint32_t *)(this + 328) = 0;
  *(uint32_t *)(this + 332) = 0;
  *(uint32_t *)(this + 336) = 0;
  *(uint32_t *)(this + 340) = 0xFFFF;
  *(uint32_t *)(this + 344) = 0xFFFF;
  *(uint32_t *)(this + 348) = 0xFFFF;
  *(uint32_t *)(this + 352) = 0xFFFF;
  *(uint32_t *)(this + 356) = 0xFFFF;
  *(uint32_t *)(this + 360) = 0xFFFF;
  *(uint32_t *)(this + 364) = 0xFFFF;
  *(uint32_t *)(this + 368) = 0xFFFF;
  *(uint32_t *)(this + 372) = 0xFFFF;
  *(uint32_t *)(this + 376) = 0xFFFF;
  *(uint32_t *)(this + 556) = 0;
  *(uint32_t *)(this + 560) = 0;
  *(uint32_t *)(this + 564) = 0;
  *(uint32_t *)(this + 568) = 0;
  *(uint8_t *)(this + 572) = 0;
  *(uint8_t *)(this + 573) = 0;
  *(uint32_t *)(this + 576) = 0;
  *(uint32_t *)(this + 580) = 0;
  *(uint32_t *)(this + 612) = 0;
  *(uint8_t *)(this + 616) = 0;
  *(uint32_t *)(this + 620) = 0;
  *(uint32_t *)(this + 624) = 0;
  *(uint32_t *)(this + 628) = 0;
  *(uint32_t *)(this + 632) = 0;
  *(uint32_t *)(this + 636) = -1;
  *(uint32_t *)(this + 640) = 0;
  *(uint32_t *)(this + 644) = 0;
  *(uint32_t *)(this + 656) = 0;
  *(uint32_t *)(this + 648) = 0;
  *(uint8_t *)(this + 652) = 0;
  return 0;
}



// ============================================================
// §19 CNRDVirtualCharacter 虚表家族 · 转职 · 驴子（0x42F350-0x432C70）
//   0x431590 转职演出(ClassChange01-03.ptl + 'JOB_CONVERTER' 语音)
//   0x431080/0x431160 CNRDDonkey 构造/开关('Donkey exist already')
// ============================================================
// ------------------------------------------------------------
// 0x42F350 CNRDVirtualCharacter__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmtC(int *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int result; // eax

  CNRDObject__vmtC(this);
  sub_49FD20(*(this + 28));
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v3);
  result = (*(int (/*thiscall*/ **)(int *, int))(v2 + 372))(this, v4);
  *((uint8_t *)this + 573) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x42F390 CNRDVirtualCharacter__vmt19C
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt19C(int *this)
{
  int fld_e81; // eax
  int fld_e79; // edi
  bool fld_e812; // cc
  int fld_e80; // edi
  bool fld_e82; // cc
  int v7; // eax
  int fld_e78; // ecx
  int result; // eax
  int v10; // [esp-8h] [ebp-18h]
  int fld_e802; // [esp-8h] [ebp-18h]
  int v12; // [esp-4h] [ebp-14h]
  int v13; // [esp-4h] [ebp-14h]
  int v14; // [esp+8h] [ebp-8h]
  int v15; // [esp+Ch] [ebp-4h]

  fld_e81 = *(this + 81);
  fld_e79 = *(this + 79);
  fld_e812 = fld_e81 <= fld_e79;
  if ( fld_e81 < fld_e79 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > fld_e79 && *(this + 77) == 1 )
      goto LABEL_4;
    fld_e812 = *(this + 81) <= fld_e79;
  }
  if ( !fld_e812 && (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < *(this + 79) && *(this + 77) == 0 )
  {
LABEL_4:
    v12 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    CNRDObject__vmt70(this, *(this + 79), v10, v12);
LABEL_5:
    *(this + 77) = 4;
    goto LABEL_6;
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) >= *(this + 79) )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) <= *(this + 79) )
      goto LABEL_5;
    *(this + 77) = 0;
  }
  else
  {
    *(this + 77) = 1;
  }
LABEL_6:
  fld_e80 = *(this + 80);
  fld_e82 = *(this + 82) <= fld_e80;
  if ( *(this + 82) < fld_e80 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) > fld_e80 && *(this + 78) == 3 )
      goto LABEL_9;
    fld_e82 = *(this + 82) <= fld_e80;
  }
  if ( !fld_e82 && (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) < *(this + 80) && *(this + 78) == 2 )
  {
LABEL_9:
    v13 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    fld_e802 = *(this + 80);
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    CNRDObject__vmt70(this, v7, fld_e802, v13);
LABEL_10:
    *(this + 78) = 4;
    goto LABEL_11;
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) >= *(this + 80) )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) <= *(this + 80) )
      goto LABEL_10;
    *(this + 78) = 2;
  }
  else
  {
    *(this + 78) = 3;
  }
LABEL_11:
  fld_e78 = *(this + 78);
  result = *(this + 77);
  v15 = fld_e78 != 4 ? 186 : 223;
  v14 = result != 4 ? 122 : 149;
  if ( result == 4 )
  {
    v15 = 0;
  }
  else if ( result == 0 )
  {
    v15 = -(fld_e78 != 4 ? 186 : 223);
  }
  if ( fld_e78 == 4 )
  {
    v14 = 0;
  }
  else if ( fld_e78 == 2 )
  {
    v14 = -(result != 4 ? 122 : 149);
  }
  *(float *)(*(this + 28) + 16) = (float)v15;
  *(float *)(*(this + 28) + 20) = (float)v14;
  return result;
}



// ------------------------------------------------------------
// 0x42F5D0 CNRDVirtualCharacter__vmt170
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt170(void *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int pThis_78; // ebx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int pThis_7C; // edi

  pThis_78 = nArg2;
  v7 = nArg5 != 4 ? 186 : 223;
  v8 = nArg4 != 4 ? 122 : 149;
  if ( nArg4 != 0 )
  {
    if ( nArg4 != 1 )
      goto LABEL_6;
    v9 = 500 * v7;
  }
  else
  {
    v9 = -500 * v7;
  }
  pThis_78 = v9 / 1000 + nArg2;
LABEL_6:
  if ( nArg5 == 2 )
  {
    pThis_7C = -500 * v8 / 1000 + nArg3;
  }
  else
  {
    pThis_7C = nArg3;
    if ( nArg5 == 3 )
      pThis_7C = 500 * v8 / 1000 + nArg3;
  }
  if ( nArg4 == 4 && nArg5 == 4 )
  {
    if ( (int)abs32(pThis_78 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this)) < 50 )
      pThis_78 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
    if ( (int)abs32(pThis_7C - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this)) < 50 )
      pThis_7C = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);
  }
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 372))(this, pThis_78, pThis_7C);
}



// ------------------------------------------------------------
// 0x42F6E0 CNRDVirtualCharacter__vmt16C
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt16C(int *this, int nArg2, int nArg3, uint8_t uArg4)
{
  int result; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax

  result = *(this + 162);
  if ( result == 0 || *(uint8_t *)(result + 284) == 0 )
  {
    v5 = (uArg4 - 1) / 3;
    v6 = (uArg4 - 1) % 3;
    if ( v6 != 0 )
      v6 = v6 != 1 ? 1 : 4;
    if ( v5 != 0 )
      v7 = 2 * (v5 == 1) + 2;
    else
      v7 = 3;
    return (*(int (/*thiscall*/ **)(int *, int, int, int, int))(*this + 368))(this, nArg2, nArg3, v6, v7);
  }
  return result;
}



// ------------------------------------------------------------
// 0x42F750 CNRDVirtualCharacter__vmt174
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt174(int *this, int nArg2, int nArg3)
{
  int result; // eax
  int v4; // eax

  result = *(this + 162);
  if ( result == 0 || *(uint8_t *)(result + 284) == 0 )
  {
    *(this + 79) = nArg2;
    v4 = *this;
    *(this + 80) = nArg3;
    return (*(int (**)(void))(v4 + 412))();
  }
  return result;
}



// ------------------------------------------------------------
// 0x42F790 CNRDVirtualCharacter__vmt17C
// ------------------------------------------------------------
bool /*thiscall*/ CNRDVirtualCharacter__vmt17C(uint32_t *this, int nArg2, int nArg3)
{
  bool result; // al
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // [esp-10h] [ebp-18h]
  int v10; // [esp-Ch] [ebp-14h]
  int v11; // [esp-8h] [ebp-10h]

  result = *(this + 29) != 0
        && (v11 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 8),
            v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this),
            v6 = sub_45E490(v5, v11),
            v10 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 8),
            v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this),
            v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this),
            v8 = sub_45E4D0(v7, v9, v10, 1.0),
            nArg2 >= v6 - 30)
        && nArg2 < v6 + 30
        && nArg3 >= v8 - 100
        && nArg3 < v8 + 10;
  return result;
}



// ------------------------------------------------------------
// 0x42F820 CNRDVirtualCharacter__vmt178
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt178(uint32_t *this)
{
  int result; // eax
  int fld_e78; // eax
  char v4; // bl
  int fld_e77; // eax
  int dword_8F7B082; // edi
  int dword_8F7B083; // edi
  int v8; // [esp+4h] [ebp-8h] BYREF
  uint8_t v9[4]; // [esp+8h] [ebp-4h] BYREF

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) != *(this + 83)
    || (result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this)) != *(this + 84) )
  {
    fld_e78 = *(this + 78);
    v4 = 0;
    if ( fld_e78 == 4 )
    {
      v4 = 3;
    }
    else if ( fld_e78 == 2 )
    {
      v4 = 6;
    }
    fld_e77 = *(this + 77);
    if ( fld_e77 == 4 )
    {
      ++v4;
    }
    else if ( fld_e77 == 1 )
    {
      v4 += 2;
    }
    sub_423200(dword_8F7B08, 37);
    dword_8F7B082 = dword_8F7B08;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    sub_423290(dword_8F7B082, (int)&v8, 2);
    dword_8F7B083 = dword_8F7B08;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    sub_423290(dword_8F7B083, (int)&v8, 2);
    v9[0] = v4 + 1;
    sub_423290(dword_8F7B08, (int)v9, 1);
    sub_423380(dword_8F7B08);
    *(this + 83) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    *(this + 84) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42F910 CNRDVirtualCharacter__vmt180
// ------------------------------------------------------------
void /*thiscall*/ CNRDVirtualCharacter__vmt180(int *this, int nArg2, int nArg3, int nArg4, int nArg5, float fArg6)
{
  int fld_e76; // ebx
  uint32_t *v7; // eax
  int dword_77F6DC2; // [esp+8h] [ebp-10h]
  float v10; // [esp+10h] [ebp-8h]
  float v11; // [esp+14h] [ebp-4h]

  fld_e76 = *(this + 76);
  dword_77F6DC2 = dword_77F6DC;
  dword_77F6DC = 1065353216;
  if ( *(uint32_t *)(fld_e76 + 148) == -1 )
    sub_4938F0(fld_e76);
  v10 = *(float *)(fld_e76 + 80);
  if ( *(uint32_t *)(fld_e76 + 148) == -1 )
    sub_4938F0(fld_e76);
  v11 = *(float *)(fld_e76 + 84);
  if ( v10 != fArg6 || v11 != fArg6 )
    sub_4920E0((uint32_t *)fld_e76, fArg6, fArg6);
  v7 = (uint32_t *)dword_79C0B0;
  *(uint32_t *)(dword_79C0B0 + 56) = nArg2 + nArg4;
  v7[12] = nArg2;
  v7[13] = nArg3;
  v7[15] = nArg3 + nArg5;
  sub_492550(
    dword_79C0B0,
    nArg2 + (uint64_t)((double)*(this + 144) * fArg6) + nArg4 / 2,
    nArg3 + (uint64_t)((double)*(this + 145) * fArg6) + nArg5 / 2,
    0.0,
    0);
  sub_488670(dword_79C0B0);
  if ( v10 == fArg6 && v11 == fArg6 )
  {
    dword_77F6DC = dword_77F6DC2;
  }
  else
  {
    sub_4920E0((uint32_t *)fld_e76, v10, v11);
    dword_77F6DC = dword_77F6DC2;
  }
}



// ------------------------------------------------------------
// 0x42FA60 CNRDVirtualCharacter__vmt160
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt160(uint32_t *this, int nArg2, int nArg3)
{
  int fld_e71; // eax
  int v5; // edx

  if ( nArg3 != 0xFFFF )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 404))(this, nArg3);
  fld_e71 = sub_4B0210(*(this + 71), nArg2);
  v5 = *this;
  if ( fld_e71 == 0xFFFF )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 408))(this, nArg2);
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 404))(this, fld_e71);
}



// ------------------------------------------------------------
// 0x42FAC0 CNRDVirtualCharacter__vmt12C
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt12C(uint32_t *this, int nArg2)
{
  int result; // eax

  result = CNRDObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x42FB00 sub_42FB00
// ------------------------------------------------------------
int /*thiscall*/ sub_42FB00(uint32_t *this, int nArg2)
{
  uint32_t *pThis_A0; // esi
  int i; // edi
  int result; // eax

  pThis_A0 = this + 160;
  for ( i = 2; i != 0; --i )
  {
    if ( *pThis_A0 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_A0)(*pThis_A0, 1);
    *pThis_A0++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42FB30 sub_42FB30
// ------------------------------------------------------------
bool /*thiscall*/ sub_42FB30(uint32_t *this, int nArg2)
{
  int fld_e162; // eax
  bool result; // al

  result = false;
  if ( nArg2 != 0 )
  {
    fld_e162 = *(this + 162);
    if ( fld_e162 != 0 && nArg2 == fld_e162 )
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42FB60 CNRDVirtualCharacter__vmt70
// ------------------------------------------------------------
int /*thiscall*/ CNRDVirtualCharacter__vmt70(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int result; // eax
  int fld_e162; // ecx

  result = CNRDObject__vmt70(this, nArg2, nArg3, nArg4);
  fld_e162 = *(this + 162);
  if ( fld_e162 != 0 )
    result = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e162 + 112))(fld_e162, nArg2, nArg3, nArg4);
  *(this + 80) = nArg3;
  *(this + 82) = nArg3;
  *(this + 79) = nArg2;
  *(this + 81) = nArg2;
  return result;
}



// ------------------------------------------------------------
// 0x42FBB0 sub_42FBB0
// ------------------------------------------------------------
int /*thiscall*/ sub_42FBB0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  if ( *(this + 162) != 0 )
    return sub_4BD440(nArg2, nArg3, nArg4, nArg5);
  else
    return off_77F3FC("Cannot prepare private store.");
}



// ------------------------------------------------------------
// 0x42FBE0 sub_42FBE0
// ------------------------------------------------------------
char /*thiscall*/ sub_42FBE0(uint32_t *this)
{
  uint8_t *fld_e162; // ecx
  char result; // al

  fld_e162 = (uint8_t *)*(this + 162);
  if ( fld_e162 != nullptr )
  {
    fld_e162[284] = 0;
    fld_e162[285] = 0;
    fld_e162[340] = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x42FBF0 sub_42FBF0
// ------------------------------------------------------------
char /*thiscall*/ sub_42FBF0(uint32_t *this)
{
  int fld_e162; // ecx
  char result; // al

  fld_e162 = *(this + 162);
  if ( fld_e162 != 0 )
  {
    result = *(uint8_t *)(fld_e162 + 284);
    if ( result != 0 )
    {
      result = *(uint8_t *)(fld_e162 + 285);
      if ( result != 0 )
        *(uint8_t *)(fld_e162 + 285) = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x42FC00 sub_42FC00
// ------------------------------------------------------------
int /*thiscall*/ sub_42FC00(int *this, void *pArg2)
{
  int result; // eax

  result = *(this + 162);
  if ( result != 0 )
  {
    *(uint8_t *)(result + 285) = 0;
    return sub_4BD690(pArg2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x42FC30 sub_42FC30
// ------------------------------------------------------------
int /*thiscall*/ sub_42FC30(int this, int nArg2)
{
  int result; // eax

  result = nArg2;
  *(uint8_t *)(this + 652) = nArg2;
  if ( *(uint32_t *)(this + 648) != 0 )
    return sub_4BD500(nArg2);
  return result;
}



// ------------------------------------------------------------
// 0x42FC50 sub_42FC50
// ------------------------------------------------------------
int /*thiscall*/ sub_42FC50(uint32_t *this)
{
  int result; // eax

  result = *(this + 164);
  if ( result != 0 )
    return sub_4BE180(result + 284);
  return result;
}



// ------------------------------------------------------------
// 0x42FC70 sub_42FC70
// ------------------------------------------------------------
int /*thiscall*/ sub_42FC70(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 88;
  return result;
}



// ------------------------------------------------------------
// 0x42FC90 sub_42FC90
// ------------------------------------------------------------
int /*thiscall*/ sub_42FC90(int *this)
{
  int result; // eax

  result = *(this + 11);
  if ( result != 0 )
    return (*(this + 12) - result) / 88;
  return result;
}



// ------------------------------------------------------------
// 0x42FCB0 sub_42FCB0
// ------------------------------------------------------------
int /*cdecl*/ sub_42FCB0(int nArg1)
{
  if ( dword_9A0128 == 0 )
  {
    if ( (dword_8F8150 & 1) == 0 )
    {
      dword_8F8150 |= 1u;
      sub_657800(nArg1, 256);
      atexit(sub_6BF450);
    }
    dword_9A0128 = (int)&unk_8F8130;
  }
  return sub_6578B0(nArg1);
}



// ------------------------------------------------------------
// 0x42FD40 sub_42FD40
// ------------------------------------------------------------
bool /*thiscall*/ sub_42FD40(void *this, const char *pArg2)
{
  return strcmp((const char *)sub_41ACF0(this), pArg2) != 0;
}



// ------------------------------------------------------------
// 0x42FDA0 sub_42FDA0
// ------------------------------------------------------------
int /*usercall*/ sub_42FDA0@<eax>(int nArg1@<ebx>, int nArg2@<esi>, int nArg3, int nArg4, int nArg5, int pArg6, int nArg7)
{
  int result; // eax
  int pArg62; // edi
  int pObj; // esi
  int v10; // ebx
  uint64_t v11; // rax
  int nArg72; // ebx
  int v13; // esi
  int v14; // eax
  const char *v15; // eax
  int v16; // eax
  unsigned int v17; // eax
  const char *v18; // esi
  int v19; // eax
  const char *v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // esi
  int v24; // eax
  int v25; // eax
  int pArg63; // ebx
  uint32_t *v27; // ebx
  int pObj2; // edi
  int v29; // eax
  int v31; // [esp-8h] [ebp-94h]
  int dword_77F6DC2; // [esp+4h] [ebp-88h]
  int v34; // [esp+4h] [ebp-88h]
  char Buffer[64]; // [esp+8h] [ebp-84h] BYREF
  char v36[64]; // [esp+48h] [ebp-44h] BYREF
  int dword_796E502; // [esp+88h] [ebp-4h]

  result = dword_796E50;
  pArg62 = pArg6;
  dword_796E502 = dword_796E50;
  if ( pArg6 != 0 )
  {
    pObj = nArg5;
    if ( nArg5 != 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg5 + 40))(nArg5, 17) == 0
        || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 940))(pObj) == 0
        || (v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj),
            result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04),
            v10 == result) )
      {
        sub_424680((int)&nArg3, (int)&nArg4, 0.0, 0.0);
        v11 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 192))(pObj, nArg1, nArg2)
                               * *(float *)&dword_77F6DC);
        nArg72 = nArg7;
        pArg6 = nArg4 - v11 - 34;
        if ( nArg7 != 0 )
        {
          v13 = nArg3 - (*(uint32_t *)(*(uint32_t *)sub_4924C0(0) + 36) >> 1);
          dword_77F6DC2 = dword_77F6DC;
          dword_77F6DC = 1065353216;
          sub_4938F0(nArg72);
          sub_491D00(dword_79C0B0, v13, pArg6 - 26, 0.0);
          dword_77F6DC = dword_77F6DC2;
        }
        v34 = -5000269;
        if ( *(uint32_t *)(pArg62 + 112) == 1 )
        {
          v34 = -6567706;
        }
        else if ( pArg62 != sub_429830((uint16_t)word_77F804) || *(uint32_t *)(pArg62 + 184) != 0 )
        {
          if ( *(uint8_t *)(pArg62 + 188) != 0 )
            v34 = -6400;
        }
        else
        {
          v34 = -1;
        }
        v14 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v14 == 4 || v14 == 6 )
        {
          v36[0] = 0;
          v17 = *(uint32_t *)(pArg62 + 40);
          if ( *(uint32_t *)(dword_8F7A24 + 12) == 6 )
          {
            if ( v17 < 0x10 )
              v18 = (const char *)(pArg62 + 20);
            else
              v18 = *(const char **)(pArg62 + 20);
            v19 = sub_41A5E0(pArg62 + 53);
            sprintf(Buffer, "Lv.%d %s", v19, v18);
          }
          else
          {
            if ( v17 < 0x10 )
              v20 = (const char *)(pArg62 + 20);
            else
              v20 = *(const char **)(pArg62 + 20);
            sprintf(Buffer, "%s", v20);
          }
          if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 && dword_99FEC0 != 0 && (uint8_t)sub_48F620() != 0
            || *(uint32_t *)(dword_8F7A24 + 12) == 6 && dword_99FF08 != 0 && (uint8_t)sub_48FD20() != 0 )
          {
            v21 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg62 + 196) + 376))(*(uint32_t *)(pArg62 + 196));
            if ( v21 != 0 )
            {
              if ( v21 == 1 )
                v34 = -20736;
            }
            else
            {
              v34 = -16771841;
            }
          }
        }
        else
        {
          if ( *(uint32_t *)(pArg62 + 40) < 0x10u )
            v15 = (const char *)(pArg62 + 20);
          else
            v15 = *(const char **)(pArg62 + 20);
          sprintf(Buffer, "%s", v15);
          v16 = sub_41A5E0(pArg62 + 53);
          sprintf(v36, "Lv.%d", v16);
        }
        v22 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, Buffer);
        v23 = nArg3 - v22 / 2;
        if ( *(uint32_t *)(pArg62 + 112) == 1 )
        {
          v23 += 11;
          if ( dword_8F8124 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8124 + 152))(
              dword_8F8124,
              v23 - 18,
              pArg6 - 2,
              dword_79C0B0);
        }
        else if ( *(uint32_t *)(pArg62 + 120) != 0 )
        {
          v24 = sub_4BF0F0(*(void **)(pArg62 + 120));
          v25 = sub_4BE300(v24);
          if ( v25 != 0 )
            sub_40FC80(v23 - 26, pArg6 - 2, v25);
        }
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_77F8FC);
        if ( dword_8F7C04 != 0 && *(uint8_t *)(dword_8F7C04 + 8052) != 0 )
        {
          pArg63 = pArg6;
          (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v23,
            pArg6 - 38,
            v34,
            Buffer);
        }
        else
        {
          pArg63 = pArg6;
          (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v23,
            pArg6 - 9,
            v34,
            Buffer);
        }
        if ( v36[0] != 0 )
          (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            v23,
            pArg63 + 7,
            v34,
            v36);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        result = dword_8F7C04;
        if ( dword_8F7C04 == 0 || *(uint8_t *)(dword_8F7C04 + 8052) == 0 )
        {
          v27 = (uint32_t *)sub_42A410(pArg62);
          pObj2 = sub_42A430(pArg62);
          if ( v36[0] != 0 )
          {
            sub_491530(2, 0);
            v29 = v23 + (*(int (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v36, v31);
            if ( pObj2 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v29, pArg6 + 4, dword_79C0B0);
            sub_491630(2);
            result = v23 + (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v36);
            if ( v27 != nullptr )
              return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*v27 + 152))(v27, result, pArg6 + 4, dword_79C0B0);
          }
          else
          {
            sub_491530(2, 0);
            if ( pObj2 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(
                pObj2,
                nArg3 - (v27[5] >> 1),
                pArg6 + 4,
                dword_79C0B0);
            result = sub_491630(2);
            if ( v27 != nullptr )
              return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*v27 + 152))(
                       v27,
                       nArg3 - (v27[5] >> 1),
                       pArg6 + 4,
                       dword_79C0B0);
          }
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x430230 sub_430230
// ------------------------------------------------------------
char /*thiscall*/ sub_430230(uint32_t **this)
{
  int v2; // eax
  int *v3; // eax
  int v5; // [esp+4h] [ebp-10h] BYREF
  int v6; // [esp+8h] [ebp-Ch] BYREF
  int v7; // [esp+Ch] [ebp-8h] BYREF
  int v8; // [esp+10h] [ebp-4h] BYREF

  if ( *(this + 162) != nullptr )
  {
    sub_4BD470(&v6, &v5, &v7, &v8);
    v2 = *(uint32_t *)(dword_8F7A24 + 20);
    if ( *(uint32_t *)(v2 + 100) == v6 )
    {
      v3 = *(int **)(v2 + 104);
      if ( v3 != nullptr )
        v2 = *v3;
      else
        v2 = -1;
      if ( v2 == v5 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(this + 162) + 112))(*(this + 162), v7, v8, 0);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[93])(this, v7, v8);
        sub_4BD4B0(*(this + 162));
        LOBYTE(v2) = *((uint8_t *)this + 652);
        if ( (uint8_t)v2 != 0 )
          LOBYTE(v2) = sub_42FC30((int)this, 0);
      }
    }
  }
  else
  {
    LOBYTE(v2) = off_77F3FC("Cannot create private store.");
  }
  return v2;
}



// ------------------------------------------------------------
// 0x4302E0 sub_4302E0
// ------------------------------------------------------------
int sub_4302E0()
{
  int result; // eax

  dword_77F92C = dword_99FCCC;
  byte_77F8FC = 0;
  byte_77F8FD = 0;
  byte_77F8FF = 0;
  dword_77F908 = 0;
  dword_77F90C = 6;
  dword_77F910 = 12;
  dword_77F914 = 0;
  dword_77F918 = 1600;
  dword_77F91C = 0;
  dword_77F920 = 0;
  dword_77F924 = 0;
  dword_77F928 = 0;
  byte_77F8FE = 1;
  dword_77F900 = -16777216;
  dword_8F811C = sub_418DD0(100);
  dword_8F8120 = sub_418DD0(99);
  (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Temp/AdminIcon.img");
  result = sub_418DD0(0);
  dword_8F8124 = result;
  return result;
}



// ------------------------------------------------------------
// 0x4303B0 CNRDVirtualCharacter__vmt88
// ------------------------------------------------------------
bool /*thiscall*/ CNRDVirtualCharacter__vmt88(uint32_t *this, int nArg2, int nArg3, uint32_t *uArg4)
{
  int fld_e29; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // esi
  int v9; // ebx
  int v10; // edi
  int v11; // [esp+10h] [ebp+10h]

  if ( uArg4 != nullptr )
    *uArg4 = 0;
  fld_e29 = *(this + 29);
  if ( fld_e29 == 0 )
    return true;
  v6 = *(uint32_t *)(*(uint32_t *)(fld_e29 + 132) + 44);
  v11 = v6;
  if ( v6 == 0 )
    return true;
  v7 = *(uint32_t *)(v6 + 232);
  if ( v7 != 0 )
    v8 = (*(uint32_t *)(v6 + 236) - v7) >> 4;
  else
    v8 = 0;
  v9 = 0;
  if ( v8 > 0 )
  {
    v10 = 0;
    while ( (uint8_t)sub_48C0A0(nArg2, nArg3, v10 + *(uint32_t *)(v6 + 232)) == 0 )
    {
      ++v9;
      v10 += 16;
      if ( v9 >= v8 )
        break;
      v6 = v11;
    }
  }
  return v9 != v8;
}



// ------------------------------------------------------------
// 0x430450 sub_430450
// ------------------------------------------------------------
// attributes: thunk
int sub_430450()
{
  return sub_406E40();
}



// ------------------------------------------------------------
// 0x430460 sub_430460
// ------------------------------------------------------------
int /*thiscall*/ sub_430460(uint32_t *this)
{
  int result; // eax
  void *v2; // edi
  uint32_t *pThis_A0; // esi
  uint8_t v4[4]; // [esp+0h] [ebp-20h] BYREF
  void *Block; // [esp+4h] [ebp-1Ch]
  int v6; // [esp+8h] [ebp-18h]
  int v7; // [esp+Ch] [ebp-14h]
  int i; // [esp+10h] [ebp-10h]
  int v9; // [esp+1Ch] [ebp-4h]

  result = dword_8F7A24;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
  {
    result = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 20) + 44);
    v2 = *(void **)(result + 104);
    if ( v2 != nullptr )
    {
      pThis_A0 = this + 160;
      for ( i = 2; i != 0; --i )
      {
        if ( *pThis_A0 != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*pThis_A0 + 12))(*pThis_A0, 0);
          (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*pThis_A0 + 92))(*pThis_A0, v4);
          v9 = 0;
          sub_4600B0(v2, 2, 0, (int)v4);
          v9 = -1;
          if ( Block != nullptr )
            j__free(Block);
          Block = nullptr;
          v6 = 0;
          v7 = 0;
        }
        ++pThis_A0;
        result = i - 1;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x430510 CNRDVirtualCharacter__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ sub_430510(int *this)
{
  unsigned int v2; // ebx
  int fld_e77; // edi
  int fld_e30; // edi
  bool fld_e159; // cc
  int fld_e302; // eax
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int fld_e1592; // ecx
  int fld_e139; // ecx
  int fld_e140; // ebx
  int fld_e1392; // edi
  int v14; // eax
  int fld_e142; // eax
  void *fld_e29; // ecx
  void *Block2; // eax
  bool v18; // zf
  int *pThis; // ecx
  int fld_e162; // eax
  int pObj; // edi
  int *v22; // edi
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // eax
  int v27; // edi
  int v28; // eax
  int fld_e1622; // eax
  int v30; // eax
  int v31; // edx
  int fld_e292; // eax
  int v33; // ebx
  uint32_t *pThis_9C; // edi
  void *fld_e293; // ecx
  int fld_e1623; // ecx
  int fld_e164; // ecx
  int fld_e1593; // [esp-8h] [ebp-48h]
  int fld_e93; // [esp-4h] [ebp-44h]
  int fld_e932; // [esp-4h] [ebp-44h]
  char v42[4]; // [esp+Ch] [ebp-34h] BYREF
  void *Block; // [esp+10h] [ebp-30h]
  char v44[4]; // [esp+1Ch] [ebp-24h] BYREF
  void *v45; // [esp+20h] [ebp-20h]
  int v46; // [esp+24h] [ebp-1Ch]
  int v47; // [esp+28h] [ebp-18h]
  int v48; // [esp+2Ch] [ebp-14h]
  int v49; // [esp+30h] [ebp-10h]
  int v50; // [esp+3Ch] [ebp-4h]

  nullsub_3(this);
  v2 = 4;
  if ( *(this + 77) != 4 )
  {
    fld_e77 = *(this + 77);
    if ( fld_e77 != (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) )
      (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, fld_e77);
  }
  if ( *(this + 50) == 0 )
  {
    if ( *(this + 77) == 4 && *(this + 78) == 4 )
    {
      if ( *(this + 30) != *(this + 74) )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 74));
        sub_4926A0(*(this + 30));
        if ( *(this + 71) == 2 )
          *(this + 159) = -1;
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 216))(this, 0);
      }
      if ( *(this + 71) == 2 )
      {
        fld_e30 = *(uint32_t *)(*(this + 30) + 148);
        fld_e159 = *(this + 159) < fld_e30;
        if ( *(this + 159) > fld_e30 )
        {
          while ( 1 )
          {
            fld_e302 = *(this + 30);
            v7 = *(uint32_t *)(fld_e302 + 44);
            v8 = fld_e302 + 40;
            v9 = v7 != 0 ? (*(uint32_t *)(v8 + 8) - v7) / 88 : 0;
            fld_e1592 = *(this + 159);
            if ( fld_e1592 >= v9 )
              break;
            fld_e93 = *(this + 93);
            *(this + 159) = fld_e1592 + 1;
            sub_4C23A0(this, fld_e1592 + 1, fld_e93);
          }
          *(this + 159) = -1;
          fld_e159 = *(this + 159) < fld_e30;
        }
        if ( fld_e159 )
        {
          do
          {
            fld_e932 = *(this + 93);
            fld_e1593 = *(this + 159) + 1;
            *(this + 159) = fld_e1593;
            sub_4C23A0(this, fld_e1593, fld_e932);
          }
          while ( *(this + 159) < fld_e30 );
        }
      }
    }
    else if ( *(this + 30) != *(this + 75) )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 75));
      sub_4926A0(*(this + 30));
      (*(void (/*thiscall*/ **)(int *, const char *, uint32_t, uint32_t, uint32_t))(*this + 212))(
        this,
        "WALK_STONE_LOOP",
        0,
        0,
        0);
    }
  }
  fld_e139 = *(this + 139);
  if ( fld_e139 != 0 && *(this + 29) != 0 )
  {
    if ( *((uint8_t *)this + 572) == 0 || *(this + 30) == *(this + 74) )
    {
      if ( *((uint8_t *)this + 573) == 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e139 + 12))(fld_e139, 0);
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )
        fld_e140 = *(this + 140) + (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      else
        fld_e140 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - *(this + 140);
      fld_e1392 = *(uint32_t *)*(this + 139);
      v14 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      fld_e142 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, *(this + 142) + v14);
      (*(void (/*thiscall*/ **)(uint32_t, int, int))(fld_e1392 + 40))(*(this + 139), fld_e140, *(this + 141) + fld_e142);
      (*(void (/*thiscall*/ **)(uint32_t, char *))(*(uint32_t *)*(this + 139) + 92))(*(this + 139), v42);
      fld_e29 = (void *)*(this + 29);
      v50 = 0;
      sub_4600B0(fld_e29, 2, 0, (int)v42);
      Block2 = Block;
      v18 = Block == nullptr;
      *((uint8_t *)this + 573) = 1;
      v50 = -1;
      if ( !v18 )
        j__free(Block2);
      v2 = 4;
    }
    else
    {
      *((uint8_t *)this + 573) = 0;
    }
  }
  pThis = this;
  if ( (int *)dword_8F7C08 != this )
    goto LABEL_68;
  sub_430460(this);
  fld_e162 = *(this + 162);
  if ( fld_e162 == 0 || *(uint8_t *)(fld_e162 + 284) == 0 )
  {
    pObj = *(uint32_t *)(*((uint32_t *)dword_8F8528 + 12) + 8);
    v49 = 4;
    if ( pObj != 0
      && (uint8_t)sub_45E680(pObj) != 0
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 34) == 0 )
    {
      v22 = *(int **)(*((uint32_t *)dword_8F8528 + 12) + 8);
      if ( (*(int (/*thiscall*/ **)(int *, int *, uint32_t))(*v22 + 8))(v22, this, 0) <= 80 )
      {
        v26 = v49;
        byte_8F8118 = 0;
        goto LABEL_46;
      }
      v23 = (*(int (/*thiscall*/ **)(int *))(*v22 + 120))(v22);
      v24 = *v22;
      v48 = v23;
      v25 = (*(int (/*thiscall*/ **)(int *))(v24 + 124))(v22);
      byte_8F8118 = 1;
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 372))(this, v48, v25);
      v26 = 4;
    }
    else
    {
      v27 = sub_4BF3D0(&unk_9A0310);
      v28 = sub_4BF3D0(&unk_9A0320);
      v2 = 0;
      if ( v27 != 2 )
      {
        LOBYTE(v2) = v27 != 3;
        v2 = ((v2 - 1) & 0xFFFFFFFD) + 4;
      }
      if ( v28 != 0 )
      {
        v49 = (v28 != 1) + 3;
        v26 = v49;
      }
      else
      {
        v26 = 2;
      }
      if ( v2 != 4 || v26 != 4 )
      {
        byte_8F8118 = 0;
        goto LABEL_46;
      }
    }
    if ( byte_8F8118 == 0 )
    {
LABEL_46:
      *(this + 77) = v2;
      *(this + 78) = v26;
      v49 = v26 != 4 ? 186 : 223;
      v48 = v2 != 4 ? 122 : 149;
      if ( v2 == 4 )
      {
        v49 = 0;
      }
      else if ( v2 == 0 )
      {
        v49 = -(v26 != 4 ? 186 : 223);
      }
      if ( v26 == 4 )
      {
        v48 = 0;
      }
      else if ( v26 == 2 )
      {
        v48 = -(v2 != 4 ? 122 : 149);
      }
      fld_e1622 = *(this + 162);
      if ( fld_e1622 != 0 && *(uint8_t *)(fld_e1622 + 284) != 0 )
      {
        v49 = 0;
        v48 = 0;
      }
      *(float *)(*(this + 28) + 16) = (float)v49;
      *(float *)(*(this + 28) + 20) = (float)v48;
LABEL_69:
      v30 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      v31 = *this;
      *(this + 81) = v30;
      *(this + 82) = (*(int (/*thiscall*/ **)(int *))(v31 + 124))(this);
      LOBYTE(fld_e292) = *((uint8_t *)this + 616);
      if ( (uint8_t)fld_e292 != 0 )
      {
        fld_e292 = *(this + 29);
        if ( fld_e292 != 0 )
        {
          v33 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
          v49 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
          pThis_9C = this + 156;
          v48 = 3;
          do
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*pThis_9C + 40))(*pThis_9C, v33, v49, 0);
            (*(void (/*thiscall*/ **)(uint32_t, char *))(*(uint32_t *)*pThis_9C + 92))(*pThis_9C, v44);
            fld_e293 = (void *)*(this + 29);
            v50 = 1;
            sub_4600B0(fld_e293, 2, 0, (int)v44);
            v50 = -1;
            if ( v45 != nullptr )
              j__free(v45);
            ++pThis_9C;
            v18 = v48 == 1;
            v45 = nullptr;
            v46 = 0;
            v47 = 0;
            --v48;
          }
          while ( !v18 );
          fld_e292 = sub_699000((int)(this + 2));
          if ( fld_e292 >= *(this + 155) + 1300 )
          {
            if ( (int *)dword_8F7C08 == this )
              LOBYTE(fld_e292) = sub_44E8D0((char *)dword_8F8528, (void *)0x29, 0, *(this + 72));
            *((uint8_t *)this + 616) = 0;
          }
        }
      }
      fld_e1623 = *(this + 162);
      if ( fld_e1623 != 0 )
      {
        fld_e292 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1623 + 80))(fld_e1623);
        if ( fld_e292 != *(this + 29) )
          LOBYTE(fld_e292) = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 162) + 28))(*(this + 162));
      }
      fld_e164 = *(this + 164);
      if ( fld_e164 != 0 )
      {
        fld_e292 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e164 + 80))(fld_e164);
        if ( fld_e292 != *(this + 29) )
          LOBYTE(fld_e292) = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 164) + 28))(*(this + 164));
      }
      return fld_e292;
    }
  }
  pThis = this;
LABEL_68:
  (*(void (/*thiscall*/ **)(int *))(*this + 412))(pThis);
  goto LABEL_69;
}


// ------------------------------------------------------------
// 0x430A90 sub_430A90
// ------------------------------------------------------------
void /*noreturn*/ sub_430A90()
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
// 0x430B00 sub_430B00
// ------------------------------------------------------------
void /*noreturn*/ sub_430B00()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0("deque<T> too long", 0x11u);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x430B70 sub_430B70
// ------------------------------------------------------------
void /*thiscall*/ sub_430B70(void *this)
{
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 1) = -1;
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 1065353216;
  *((uint32_t *)this + 6) = 1065353216;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 8) = -1;
  *((uint8_t *)this + 36) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  if ( *((uint32_t *)this + 15) != 0 )
    j__free(*((void **)this + 15));
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  if ( *((uint32_t *)this + 19) != 0 )
    j__free(*((void **)this + 19));
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 13) = 0;
}



// ------------------------------------------------------------
// 0x430BE0 sub_430BE0
// ------------------------------------------------------------
char /*thiscall*/ sub_430BE0(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0xAAAAAAA )
    sub_430A90(this);
  pMem = (char *)operator new(24 * uArg2);
  *(this + 3) = &pMem[24 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x430C30 sub_430C30
// ------------------------------------------------------------
char /*thiscall*/ sub_430C30(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x2E8BA2E )
    sub_430A90(this);
  pMem = (char *)operator new(88 * uArg2);
  *(this + 3) = &pMem[88 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x430C80 sub_430C80
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_430C80(int this, int Src, unsigned int uArg3, int *pDwArg4)
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
      sub_42A9A0(this);
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
// 0x430E60 sub_430E60
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_430E60(int this, unsigned int uArg2)
{
  unsigned int uArg22; // edx
  unsigned int fld_8; // eax
  unsigned int v5; // ecx
  unsigned int fld_C; // edi
  int v7; // esi
  char *fld_4; // eax
  const void *fld_42; // ecx
  char *v10; // eax
  char *pBuf3; // edx
  unsigned int pBuf; // ecx
  char *pBuf2; // edi
  size_t v14; // esi
  char *fld_43; // eax
  unsigned int result; // eax
  size_t fld_82; // [esp+8h] [ebp-Ch]
  char *pMem; // [esp+10h] [ebp-4h]

  uArg22 = uArg2;
  fld_8 = *(uint32_t *)(this + 8);
  if ( 0xFFFFFFF - fld_8 < uArg2 )
    sub_430B00(this);
  v5 = fld_8 >> 1;
  if ( fld_8 >> 1 < 8 )
    v5 = 8;
  if ( uArg2 < v5 && fld_8 <= 0xFFFFFFF - v5 )
  {
    uArg2 = v5;
    uArg22 = v5;
  }
  fld_C = *(uint32_t *)(this + 12) >> 2;
  v7 = 4 * fld_C;
  pMem = (char *)operator new(4 * (uArg22 + fld_8));
  fld_82 = 4 * ((int)(4 * *(uint32_t *)(this + 8) - 4 * fld_C) >> 2);
  fld_4 = (char *)memcpy_0(&pMem[4 * fld_C], (const void *)(4 * fld_C + *(uint32_t *)(this + 4)), fld_82);
  fld_42 = *(const void **)(this + 4);
  v10 = &fld_4[fld_82];
  if ( fld_C > uArg2 )
  {
    memcpy_0(v10, fld_42, 4 * ((int)(4 * uArg2) >> 2));
    v14 = 4 * ((int)(v7 - 4 * uArg2) >> 2);
    fld_43 = (char *)memcpy_0(pMem, (const void *)(4 * uArg2 + *(uint32_t *)(this + 4)), v14);
    pBuf = uArg2;
    pBuf2 = &fld_43[v14];
    if ( uArg2 == 0 )
      goto LABEL_15;
    goto LABEL_14;
  }
  pBuf3 = (char *)memcpy_0(v10, fld_42, 4 * (v7 >> 2)) + 4 * (v7 >> 2);
  if ( uArg2 != fld_C )
    memset(pBuf3, 0, 4 * (uArg2 - fld_C));
  if ( fld_C != 0 )
  {
    pBuf = fld_C;
    pBuf2 = pMem;
LABEL_14:
    memset(pBuf2, 0, 4 * pBuf);
  }
LABEL_15:
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  result = uArg2 + *(uint32_t *)(this + 8);
  *(uint32_t *)(this + 4) = pMem;
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x430FB0 sub_430FB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_430FB0(uint32_t *this, uint32_t *uArg2, void *Src, int *pDwArg4)
{
  int fld_e1; // ecx
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) >> 2 != 0 )
    v6 = ((int)Src - fld_e1) >> 2;
  else
    v6 = 0;
  sub_430C80((int)this, (int)Src, 1u, pDwArg4);
  *uArg2 = *(this + 1) + 4 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x431000 sub_431000
// ------------------------------------------------------------
int /*thiscall*/ sub_431000(int this, uint32_t *uArg2)
{
  int fld_10; // eax
  unsigned int fld_8; // eax
  unsigned int fld_102; // edi
  unsigned int v6; // ebx
  uint32_t *fld_4; // edi
  int result; // eax

  fld_10 = *(uint32_t *)(this + 16);
  if ( (((uint8_t)fld_10 + *(uint8_t *)(this + 12)) & 3) == 0 && *(uint32_t *)(this + 8) <= (unsigned int)(fld_10 + 4) >> 2 )
    sub_430E60(this, 1u);
  fld_8 = *(uint32_t *)(this + 8);
  fld_102 = *(uint32_t *)(this + 16) + *(uint32_t *)(this + 12);
  v6 = fld_102 >> 2;
  if ( fld_8 <= fld_102 >> 2 )
    v6 -= fld_8;
  if ( *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) == 0 )
    *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) = operator new(0x10u);
  fld_4 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) + 4 * (fld_102 & 3));
  if ( fld_4 != nullptr )
    *fld_4 = *uArg2;
  result = *(uint32_t *)(this + 16) + 1;
  *(uint32_t *)(this + 16) = result;
  return result;
}



// ------------------------------------------------------------
// 0x431080 sub_431080
// ------------------------------------------------------------
// 【CNRDDonkey 构造】operator new(0x17Cu) → 挂宿主 +162 槽（见 0x431160）。
char */*thiscall*/ sub_431080(char *this, int nArg2)
{
  sub_42AAB0(this);
  *(uint32_t *)this = &vftbl_CNRDDonkey;
  sub_4BCCA0(this);
  sub_4BCD50(this);
  sub_4BD5E0(nArg2);
  return this;
}



// ------------------------------------------------------------
// 0x4310E0 CNRDDonkey__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDDonkey__vmt0(void *Block, char pszArg2)
{
  sub_431110();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x431110 sub_431110
// ------------------------------------------------------------
int /*thiscall*/ sub_431110(void **this)
{
  *this = &vftbl_CNRDDonkey;
  sub_4BDC40();
  return sub_42A450(this);
}



// ------------------------------------------------------------
// 0x431160 sub_431160
// ------------------------------------------------------------
// 【驴子开关】Block=1：已存在 → off_77F3FC("Donkey exist already")，否则 new CNRDDonkey
//   (0x431080) 挂 +162；Block=0：vt+0(1) 析构释放并清槽。
char /*thiscall*/ sub_431160(uint32_t *this, char Block)
{
  char *v2; // eax
  char *pMem; // eax
  int (/*thiscall*/ ***fld_e162)(uint32_t, int); // ecx

  LOBYTE(v2) = Block;
  if ( Block != 0 )
  {
    if ( *(this + 162) != 0 )
    {
      LOBYTE(v2) = off_77F3FC("Donkey exist already");
    }
    else
    {
      pMem = (char *)operator new(0x17Cu);
      if ( pMem != nullptr )
      {
        v2 = sub_431080(pMem, (int)this);
        *(this + 162) = v2;
      }
      else
      {
        *(this + 162) = 0;
        LOBYTE(v2) = 0;
      }
    }
  }
  else
  {
    fld_e162 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 162);
    if ( fld_e162 != nullptr )
      LOBYTE(v2) = (**fld_e162)(fld_e162, 1);
    *(this + 162) = 0;
  }
  return (char)v2;
}



// ------------------------------------------------------------
// 0x431230 sub_431230
// ------------------------------------------------------------
int /*thiscall*/ sub_431230(int this, uint32_t *uArg2)
{
  int fld_4; // esi
  unsigned int fld_8; // edx
  uint32_t *fld_82; // eax
  int result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) >> 2 )
    return sub_430C80(*(void **)(this + 8), 1, (int)uArg2);
  fld_82 = *(uint32_t **)(this + 8);
  *fld_82 = *uArg2;
  result = (int)(fld_82 + 1);
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x431280 CNRDVirtualCharacter__vmt15C
// ------------------------------------------------------------
// 【vmt15C · 全量状态应用】vt+392/396 外观参数 + vt+352×10 装备槽 + 尾调驴子开关
//   （a2+108 字节）。
char /*thiscall*/ CNRDVirtualCharacter__vmt15C(uint32_t *this, int pArg2)
{
  int v3; // edi
  uint32_t *v4; // ebx

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 392))(this, *(uint32_t *)(pArg2 + 28));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 396))(
    this,
    *(uint32_t *)(pArg2 + 32),
    *(uint8_t *)(pArg2 + 36));
  v3 = 0;
  v4 = (uint32_t *)(pArg2 + 56);
  do
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 352))(this, v3++, *v4++);
  while ( v3 < 10 );
  return sub_431160(this, *(uint8_t *)(pArg2 + 108));
}



// ------------------------------------------------------------
// 0x4312E0 CNRDVirtualCharacter__vmt184
// ------------------------------------------------------------
int /*thiscall*/ sub_4312E0(int *this, int nArg2, int nArg3, int nArg4, int nArg5, float fArg6, int nArg7)
{
  int fld_e76; // edi
  int v8; // eax
  bool v9; // zf
  uint32_t *v10; // eax
  int v11; // eax
  uint32_t **v12; // eax
  uint32_t *v13; // esi
  int v14; // eax
  unsigned int v15; // eax
  int v16; // ebx
  unsigned int v17; // ebx
  unsigned int v18; // ecx
  uint32_t **v19; // eax
  unsigned int v20; // eax
  int v21; // ebx
  char v23[4]; // [esp+Ch] [ebp-30h] BYREF
  int v24; // [esp+10h] [ebp-2Ch]
  unsigned int v25; // [esp+14h] [ebp-28h]
  unsigned int v26; // [esp+18h] [ebp-24h]
  int v27; // [esp+1Ch] [ebp-20h]
  int dword_77F6DC2; // [esp+20h] [ebp-1Ch]
  int *pThis; // [esp+24h] [ebp-18h]
  float v30; // [esp+28h] [ebp-14h]
  float v31; // [esp+2Ch] [ebp-10h]
  int v32; // [esp+38h] [ebp-4h]
  uint32_t *v33; // [esp+58h] [ebp+1Ch]

  fld_e76 = *(this + 76);
  dword_77F6DC2 = dword_77F6DC;
  dword_77F6DC = 1065353216;
  v8 = *(uint32_t *)(fld_e76 + 148);
  pThis = this;
  if ( v8 == -1 )
    sub_4938F0(fld_e76);
  v9 = *(uint32_t *)(fld_e76 + 148) == -1;
  v30 = *(float *)(fld_e76 + 80);
  if ( v9 )
    sub_4938F0(fld_e76);
  v31 = *(float *)(fld_e76 + 84);
  if ( v30 != fArg6 || v31 != fArg6 )
    sub_4920E0((uint32_t *)fld_e76, fArg6, fArg6);
  v10 = (uint32_t *)dword_79C0B0;
  *(uint32_t *)(dword_79C0B0 + 56) = nArg2 + nArg4;
  v10[13] = nArg3;
  v10[12] = nArg2;
  v10[15] = nArg5 + nArg3;
  v24 = 0;
  v25 = 0;
  v26 = 0;
  v27 = 0;
  v32 = 0;
  v11 = sub_4924C0(0);
  sub_431000(v11 + 32);
  *(uint32_t *)(sub_4924C0(0) + 32) = nArg7;
  v12 = *(uint32_t ***)(fld_e76 + 204);
  v13 = *v12;
  if ( *v12 != v12 )
  {
    do
    {
      v14 = sub_4924C0(0);
      sub_431000(v14 + 32);
      *(uint32_t *)(sub_4924C0(0) + 32) = nArg7;
      v13 = (uint32_t *)*v13;
    }
    while ( v13 != *(uint32_t **)(fld_e76 + 204) );
  }
  sub_492550(
    dword_79C0B0,
    nArg2 + (uint64_t)((double)pThis[144] * fArg6) + nArg4 / 2,
    nArg3 + (uint64_t)((double)pThis[145] * fArg6) + nArg5 / 2,
    0.0,
    0);
  v15 = v26 >> 2;
  if ( v25 <= v26 >> 2 )
    v15 -= v25;
  v16 = *(uint32_t *)(v24 + 4 * v15);
  *(uint32_t *)(sub_4924C0(0) + 32) = *(uint32_t *)(v16 + 4 * (v26 - 4 * (v26 >> 2)));
  v17 = v25;
  v18 = v26;
  if ( v27 != 0 )
  {
    v18 = v26 + 1;
    v26 = v18;
    if ( 4 * v25 <= v18 )
    {
      v18 = 0;
      v26 = 0;
    }
    if ( --v27 == 0 )
    {
      v18 = 0;
      v26 = 0;
    }
  }
  v19 = *(uint32_t ***)(fld_e76 + 204);
  v33 = *v19;
  if ( *v19 != v19 )
  {
    do
    {
      v20 = v18 >> 2;
      if ( v17 <= v18 >> 2 )
        v20 -= v17;
      v21 = *(uint32_t *)(v24 + 4 * v20);
      *(uint32_t *)(sub_4924C0(0) + 32) = *(uint32_t *)(v21 + 4 * (v18 - 4 * (v18 >> 2)));
      v17 = v25;
      v18 = v26;
      if ( v27 != 0 )
      {
        v18 = v26 + 1;
        v26 = v18;
        if ( 4 * v25 <= v18 )
        {
          v18 = 0;
          v26 = 0;
        }
        if ( --v27 == 0 )
        {
          v18 = 0;
          v26 = 0;
        }
      }
      v33 = (uint32_t *)*v33;
    }
    while ( v33 != *(uint32_t **)(fld_e76 + 204) );
  }
  sub_488670(dword_79C0B0);
  if ( v30 != fArg6 || v31 != fArg6 )
    sub_4920E0((uint32_t *)fld_e76, v30, v31);
  dword_77F6DC = dword_77F6DC2;
  return sub_406E40(v23);
}


// ------------------------------------------------------------
// 0x431590 CNRDVirtualCharacter__vmt190
// ------------------------------------------------------------
// 【转职演出】+616 = 1；懒建 ClassChange01-03.ptl 粒子（sprintf
//   "Common/CommonEffect/Particle/ClassChange%02d.ptl"，0x12Cu 对象 ×3）→ vt+12(0)
//   复位 → 语音 "JOB_CONVERTER"（vt+212）。
int /*thiscall*/ CNRDVirtualCharacter__vmt190(char *this)
{
  uint32_t *pThis_270; // ebx
  int v3; // eax
  int v4; // edi
  uint32_t *pMem; // eax
  uint32_t *v6; // eax
  uint32_t *pThis_2702; // edi
  int i; // ebx

  *(this + 616) = 1;
  pThis_270 = this + 624;
  *((uint32_t *)this + 155) = sub_699000((int)(this + 8));
  if ( *pThis_270 == 0 )
  {
    v3 = 0;
    do
    {
      v4 = v3 + 1;
      sprintf(byte_8F8158, "Common/CommonEffect/Particle/ClassChange%02d.ptl", v3 + 1);
      pMem = operator new(0x12Cu);
      if ( pMem != nullptr )
        v6 = sub_428F30(pMem, (int)byte_8F8158, (int)this);
      else
        v6 = nullptr;
      *pThis_270 = v6;
      (*(void (/*thiscall*/ **)(uint32_t *, char *))(*v6 + 112))(v6, this);
      v3 = v4;
      ++pThis_270;
    }
    while ( v4 < 3 );
  }
  pThis_2702 = this + 624;
  for ( i = 3; i != 0; --i )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*pThis_2702 + 12))(*pThis_2702, 0);
    ++pThis_2702;
  }
  return (*(int (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
           this,
           "JOB_CONVERTER",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x431670 sub_431670
// ------------------------------------------------------------
int /*userpurge*/ sub_431670@<eax>(uint32_t *uArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4@<esi>, int nArg5)
{
  int result; // eax
  int v6; // edx
  int v7; // esi
  uint32_t *v8; // edi
  int v9; // ebx
  uint32_t *pMem; // eax
  uint32_t *v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // edx
  int v16; // esi
  int v17; // ecx
  int v18; // eax
  int v23; // [esp+4h] [ebp-218h]
  int Block; // [esp+8h] [ebp-214h]
  char Buffer[512]; // [esp+Ch] [ebp-210h] BYREF
  int dword_796E502; // [esp+20Ch] [ebp-10h]
  int v27; // [esp+218h] [ebp-4h]
  int v28; // [esp+224h] [ebp+8h]

  dword_796E502 = dword_796E50;
  result = dword_8F7A24;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
  {
    result = *(uint32_t *)(dword_8F7A24 + 20);
    v23 = *(uint32_t *)(*(uint32_t *)(result + 44) + 104);
    if ( v23 != 0 && nArg5 == 1 )
    {
      v6 = *(uint32_t *)(result + 104);
      if ( *(uint32_t *)(v6 + 32) == 0 || *(uint32_t *)(v6 + 32) == 4 )
      {
        v7 = 0;
        v8 = uArg1 + 160;
        do
        {
          if ( *v8 != 0 )
            (**(void (/*thiscall*/ ***)(uint32_t, int))*v8)(*v8, 1);
          v9 = v7 + 1;
          *v8 = 0;
          sprintf(Buffer, "PassiveObject/MapObject/ParticleFactory/Particle/snowflake%d.ptl", v7 + 1);
          pMem = operator new(0x12Cu);
          v27 = 0;
          if ( pMem != nullptr )
            v11 = sub_428F30(pMem, (int)Buffer, (int)uArg1);
          else
            v11 = nullptr;
          *v8 = v11;
          v12 = *(uint32_t *)(*(uint32_t *)(v23 + 132) + 44);
          v13 = *(uint32_t *)(v12 + 364);
          v14 = v12 + 360;
          v27 = -1;
          if ( v13 != 0 )
            v15 = (*(uint32_t *)(v14 + 8) - v13) >> 5;
          else
            v15 = 0;
          v16 = 224 * v15;
          Block = 224 * v15;
          v17 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*v11 + 36))(v11, nArg3, nArg2, nArg4);
          v28 = *(uint32_t *)(v17 + 12);
          if ( *(uint32_t *)v17 != -1082130432 )
            *(float *)v17 = (double)Block * *(float *)v17 / (double)v28;
          v18 = v16 * *(uint32_t *)(v17 + 4) / v28;
          *(uint32_t *)(v17 + 12) = v16;
          nArg4 = 380;
          nArg2 = 280;
          *(uint32_t *)(v17 + 4) = v18;
          nArg3 = v16 / 2;
          result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v8 + 40))(*v8);
          v7 = v9;
          ++v8;
        }
        while ( v9 < 2 );
      }
      else
      {
        return sub_42FB00(uArg1, 1);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x431820 sub_431820
// ------------------------------------------------------------
int /*userpurge*/ sub_431820@<eax>(uint32_t *uArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4@<esi>, char pszArg5)
{
  int result; // eax

  result = dword_8F7A24;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )
  {
    result = *(uint32_t *)(dword_8F7A24 + 292) - 1;
    if ( *(uint32_t *)(dword_8F7A24 + 292) == 1 )
    {
      if ( pszArg5 != 0 )
        return sub_431670(uArg1, nArg2, nArg3, nArg4, 1);
      else
        return sub_42FB00(uArg1, 1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x431860 sub_431860
// ------------------------------------------------------------
int /*thiscall*/ sub_431860(int this, const char *ArgList, char pszArg3)
{
  uint32_t *pThis_3C; // ecx

  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 8) = 0;
  *(uint8_t *)(this + 12) = 1;
  *(uint8_t *)(this + 14) = 0;
  *(uint8_t *)(this + 13) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  pThis_3C = (uint32_t *)(this + 60);
  pThis_3C[15] = 0;
  pThis_3C[16] = 0;
  pThis_3C[17] = 0;
  pThis_3C[19] = 0;
  pThis_3C[20] = 0;
  pThis_3C[21] = 0;
  sub_430B70(pThis_3C);
  *(uint32_t *)(this + 204) = sub_4A2CF0(this + 200);
  *(uint32_t *)(this + 208) = 0;
  sub_493BD0(this);
  sub_494E40((uint8_t *)this, szPassword, ArgList, pszArg3, 0, 0, 0, 0);
  return this;
}



// ------------------------------------------------------------
// 0x431920 sub_431920
// ------------------------------------------------------------
int /*thiscall*/ sub_431920(int this, const char *pArg2, const char *ArgList, char pszArg4)
{
  uint32_t *pThis_3C; // ecx

  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 8) = 0;
  *(uint8_t *)(this + 12) = 1;
  *(uint8_t *)(this + 14) = 0;
  *(uint8_t *)(this + 13) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  pThis_3C = (uint32_t *)(this + 60);
  pThis_3C[15] = 0;
  pThis_3C[16] = 0;
  pThis_3C[17] = 0;
  pThis_3C[19] = 0;
  pThis_3C[20] = 0;
  pThis_3C[21] = 0;
  sub_430B70(pThis_3C);
  *(uint32_t *)(this + 204) = sub_4A2CF0(this + 200);
  *(uint32_t *)(this + 208) = 0;
  sub_493BD0(this);
  sub_494E40((uint8_t *)this, pArg2, ArgList, pszArg4, 0, 0, 0, 0);
  return this;
}



// ------------------------------------------------------------
// 0x4319E0 sub_4319E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4319E0(int this, int nArg2, int nArg3, const char *pArg4, const char *ArgList, char pszArg6)
{
  uint32_t *pThis_3C; // ecx

  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 8) = 0;
  *(uint8_t *)(this + 12) = 1;
  *(uint8_t *)(this + 14) = 0;
  *(uint8_t *)(this + 13) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  pThis_3C = (uint32_t *)(this + 60);
  pThis_3C[15] = 0;
  pThis_3C[16] = 0;
  pThis_3C[17] = 0;
  pThis_3C[19] = 0;
  pThis_3C[20] = 0;
  pThis_3C[21] = 0;
  sub_430B70(pThis_3C);
  *(uint32_t *)(this + 204) = sub_4A2CF0(this + 200);
  *(uint32_t *)(this + 208) = 0;
  sub_493BD0(this);
  sub_494E40((uint8_t *)this, pArg4, ArgList, pszArg6, 1, 0, nArg2, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x431AA0 sub_431AA0
// ------------------------------------------------------------
int sub_431AA0()
{
  void ***v0; // esi
  void **v1; // edi
  int result; // eax

  v0 = (void ***)&dword_8F8128;
  do
  {
    v1 = *v0;
    if ( *v0 != nullptr )
    {
      sub_42AF90(*v0);
      result = sub_657740(v1, 228);
    }
    *v0++ = nullptr;
  }
  while ( (int)v0 < (int)&unk_8F8130 );
  return result;
}



// ------------------------------------------------------------
// 0x431AE0 sub_431AE0
// ------------------------------------------------------------
int /*thiscall*/ sub_431AE0(uint32_t *this)
{
  void (/*thiscall*/ ***fld_e139)(uint32_t, int); // ecx
  void **fld_e153; // esi
  uint32_t *pThis_9C; // esi
  int i; // ebx
  uint32_t *pThis_A0; // esi
  int j; // ebx
  void (/*thiscall*/ ***fld_e162)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e164)(uint32_t, int); // ecx
  int result; // eax

  fld_e139 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 139);
  if ( fld_e139 != nullptr )
    (**fld_e139)(fld_e139, 1);
  fld_e153 = (void **)*(this + 153);
  *(this + 139) = 0;
  if ( fld_e153 != nullptr )
  {
    sub_42AF90(fld_e153);
    sub_657740(fld_e153, 228);
  }
  *(this + 153) = 0;
  pThis_9C = this + 156;
  for ( i = 3; i != 0; --i )
  {
    if ( *pThis_9C != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_9C)(*pThis_9C, 1);
    *pThis_9C++ = 0;
  }
  pThis_A0 = this + 160;
  for ( j = 2; j != 0; --j )
  {
    if ( *pThis_A0 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_A0)(*pThis_A0, 1);
    *pThis_A0++ = 0;
  }
  fld_e162 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 162);
  if ( fld_e162 != nullptr )
    (**fld_e162)(fld_e162, 1);
  fld_e164 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 164);
  result = 0;
  *(this + 162) = 0;
  if ( fld_e164 != nullptr )
    result = (**fld_e164)(fld_e164, 1);
  *(this + 164) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x431BB0 CNRDVirtualCharacter__vmt18C
// ------------------------------------------------------------
char /*thiscall*/ sub_431BB0(void *this, int nArg2, char pszArg3)
{
  int pThis_48; // eax
  int nArg22; // esi
  void (/*thiscall*/ ***pThis_8B)(uint32_t, int); // ecx
  uint32_t *pThis_88; // esi
  bool pThis_89; // zf
  int pThis_230; // eax
  int pThis_482; // edx
  uint32_t *v11; // ecx
  int v12; // esi
  char v13; // di
  char v14; // al
  char v15; // al
  int v16; // esi
  char v17; // di
  char v18; // al
  int v19; // esi
  uint32_t *v20; // edi
  int pThis_882; // esi
  unsigned int pThis_892; // edx
  uint32_t *pThis_893; // eax
  char v25; // [esp+Ch] [ebp-14h]
  uint32_t *v26; // [esp+10h] [ebp-10h]
  uint32_t *v27; // [esp+28h] [ebp+8h]
  uint32_t *v28; // [esp+2Ch] [ebp+Ch]

  pThis_48 = *((uint32_t *)this + 72);
  nArg22 = nArg2;
  if ( pThis_48 != nArg2 || *((uint8_t *)this + 292) != pszArg3 )
  {
    if ( pThis_48 != -1
      && pThis_48 != nArg2
      && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104) != 0
      && (uint8_t)sub_45E680(this) != 0 )
    {
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 400))(this);
    }
    if ( *((uint8_t *)this + 292) != 0 )
    {
      pThis_8B = *((void (/*thiscall*/ ****)(uint32_t, int))this + 139);
      if ( pThis_8B != nullptr )
        (**pThis_8B)(pThis_8B, 1);
      pThis_88 = *((uint32_t **)this + 136);
      pThis_89 = pThis_88 == *((uint32_t **)this + 137);
      *((uint32_t *)this + 139) = 0;
      if ( !pThis_89 )
      {
        do
        {
          sub_494500(*pThis_88);
          sub_494500(*pThis_88);
          sub_494500(*pThis_88++);
        }
        while ( pThis_88 != *((uint32_t **)this + 137) );
      }
      if ( *((uint32_t *)this + 136) != 0 )
        j__free(*((void **)this + 136));
      nArg22 = nArg2;
      *((uint32_t *)this + 136) = 0;
      *((uint32_t *)this + 137) = 0;
      *((uint32_t *)this + 138) = 0;
    }
    LOBYTE(pThis_48) = pszArg3;
    *((uint32_t *)this + 72) = nArg22;
    *((uint8_t *)this + 292) = pszArg3;
    if ( pszArg3 != 0 )
    {
      pThis_230 = sub_4B50F0(
             (int)this + 560,
             (int)this + 564,
             (int)this + 568,
             (int)this + 572,
             *((void **)this + 71),
             nArg22,
             (int)this);
      pThis_482 = *((uint32_t *)this + 72);
      *((uint32_t *)this + 139) = pThis_230;
      pThis_48 = sub_4B0080(*((uint32_t *)this + 71), pThis_482);
      if ( pThis_48 != 0 )
      {
        pThis_48 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84D0 + 4))(dword_8F84D0, pThis_48);
        v26 = (uint32_t *)pThis_48;
        if ( pThis_48 != 0 )
        {
          v11 = *(uint32_t **)(pThis_48 + 1056);
          v27 = v11;
          if ( v11 != *(uint32_t **)(pThis_48 + 1060) )
          {
            v28 = v11 + 2;
            do
            {
              if ( strcmp((const char *)sub_41ACF0(v28 + 8), szPassword) != 0 )
              {
                v12 = 0;
                if ( sub_42FCB0(228) != 0 )
                {
                  v13 = sub_41ACF0(v26 + 272);
                  v14 = sub_41ACF0(v28 + 8);
                  v12 = sub_4319E0(v26[273], v26[274], v13, v14, 1);
                }
                sub_4B0DF0(*((uint32_t *)this + 74), v12);
                sub_494240(*v27, v12);
              }
              if ( strcmp((const char *)sub_41ACF0(v28), szPassword) != 0 )
              {
                if ( sub_42FCB0(228) != 0 )
                {
                  v25 = sub_41ACF0(v26 + 272);
                  v15 = sub_41ACF0(v28);
                  v16 = sub_4319E0(v26[273], v26[274], v25, v15, 1);
                }
                else
                {
                  v16 = 0;
                }
                sub_4B0DF0(*((uint32_t *)this + 75), v16);
                sub_494240(*v27, v16);
              }
              if ( strcmp((const char *)sub_41ACF0(v28 - 1), szPassword) == 0 )
              {
                v20 = v27;
              }
              else
              {
                if ( sub_42FCB0(228) != 0 )
                {
                  v17 = sub_41ACF0(v26 + 272);
                  v18 = sub_41ACF0(v28 - 1);
                  v19 = sub_4319E0(v26[273], v26[274], v17, v18, 1);
                }
                else
                {
                  v19 = 0;
                }
                sub_4B0DF0(*((uint32_t *)this + 76), v19);
                v20 = v27;
                sub_494240(*v27, v19);
              }
              pThis_882 = *((uint32_t *)this + 136);
              if ( pThis_882 != 0 )
                pThis_892 = (*((uint32_t *)this + 137) - pThis_882) >> 2;
              else
                pThis_892 = 0;
              if ( pThis_882 != 0 && pThis_892 < (*((uint32_t *)this + 138) - pThis_882) >> 2 )
              {
                pThis_893 = *((uint32_t **)this + 137);
                *pThis_893 = *v20;
                *((uint32_t *)this + 137) = pThis_893 + 1;
              }
              else
              {
                sub_430C80(*((void **)this + 137), 1, (int)v20);
              }
              LOBYTE(pThis_48) = (uint8_t)v26;
              v27 = v20 + 31;
              v28 += 31;
            }
            while ( v20 + 31 != (uint32_t *)v26[265] );
          }
        }
      }
    }
  }
  return pThis_48;
}


// ------------------------------------------------------------
// 0x431FB0 CNRDVirtualCharacter__vmt194
// ------------------------------------------------------------
void /*thiscall*/ sub_431FB0(uint32_t *this, int nArg2)
{
  uint32_t *pThis; // edi
  uint32_t *v3; // eax
  uint32_t *v4; // esi
  int v5; // eax
  int v6; // ecx
  char v7; // al
  int v8; // eax
  uint32_t *v9; // ebx
  char v10; // al
  int v11; // eax
  char v12; // al
  int v13; // eax
  char v14; // bl
  char v15; // al
  int v16; // eax
  int v17; // [esp-8h] [ebp-50h]
  int v18; // [esp-8h] [ebp-50h]
  int v19; // [esp-8h] [ebp-50h]
  int v20; // [esp+Ch] [ebp-3Ch]
  int v21; // [esp+Ch] [ebp-3Ch]
  int v22; // [esp+Ch] [ebp-3Ch]
  char v23; // [esp+10h] [ebp-38h]
  uint32_t *v24; // [esp+10h] [ebp-38h]
  int v25; // [esp+14h] [ebp-34h]
  char v26; // [esp+14h] [ebp-34h]
  char v27; // [esp+14h] [ebp-34h]
  uint8_t v29[20]; // [esp+1Ch] [ebp-2Ch] BYREF
  int v30; // [esp+30h] [ebp-18h]
  int v31; // [esp+34h] [ebp-14h]
  int dword_796E502; // [esp+38h] [ebp-10h]
  int v33; // [esp+44h] [ebp-4h]
  int v34; // [esp+50h] [ebp+8h]
  uint32_t *v35; // [esp+50h] [ebp+8h]

  pThis = this;
  dword_796E502 = dword_796E50;
  v3 = (uint32_t *)sub_4CE8A0(nArg2);
  v4 = v3;
  if ( v3 != nullptr )
  {
    v5 = v3[23];
    if ( v5 <= 9 )
    {
      if ( pThis[v5 + 85] != nArg2 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pThis + 408))(pThis, v4[23]);
        pThis[v4[23] + 85] = nArg2;
        if ( v4[23] == 9 )
        {
          v31 = 15;
          v30 = 0;
          v29[4] = 0;
          v33 = 0;
          sub_4014D0((std::_String_base *)(pThis + 146), v29, 0, -1);
          v6 = v4[20];
          if ( v6 != 0 && (v4[21] - v6) >> 2 != 0 && (uint8_t)sub_42FD40(szPassword) != 0 )
          {
            v25 = sub_42FCB0(228);
            LOBYTE(v33) = 1;
            if ( v25 != 0 )
            {
              v34 = v4[20];
              v23 = sub_41ACF0(v4 + 272);
              v7 = sub_41ACF0(v34);
              v8 = sub_431920(v23, v7, 1);
            }
            else
            {
              v8 = 0;
            }
            LOBYTE(v33) = 0;
            pThis[153] = v8;
            sub_699070(2);
          }
          v33 = -1;
          sub_501490(v29);
        }
        v9 = (uint32_t *)v4[264];
        v24 = v9;
        if ( v9 != (uint32_t *)v4[265] )
        {
          v35 = v9 + 2;
          do
          {
            if ( (uint8_t)sub_42FD40(szPassword) != 0 )
            {
              v20 = sub_42FCB0(228);
              v33 = 2;
              if ( v20 != 0 )
              {
                v26 = sub_41ACF0(v4 + 272);
                v10 = sub_41ACF0(v35 + 8);
                v11 = sub_4319E0(v4[273], v4[274], v26, v10, 1);
              }
              else
              {
                v11 = 0;
              }
              v17 = *v9;
              v33 = -1;
              sub_494240(v17, v11);
              pThis = this;
            }
            if ( (uint8_t)sub_42FD40(szPassword) != 0 )
            {
              v21 = sub_42FCB0(228);
              v33 = 3;
              if ( v21 != 0 )
              {
                v27 = sub_41ACF0(v4 + 272);
                v12 = sub_41ACF0(v35);
                v13 = sub_4319E0(v4[273], v4[274], v27, v12, 1);
              }
              else
              {
                v13 = 0;
              }
              v18 = *v9;
              v33 = -1;
              sub_494240(v18, v13);
              pThis = this;
            }
            if ( (uint8_t)sub_42FD40(szPassword) != 0 )
            {
              v22 = sub_42FCB0(228);
              v33 = 4;
              if ( v22 != 0 )
              {
                v14 = sub_41ACF0(v4 + 272);
                v15 = sub_41ACF0(v35 - 1);
                v16 = sub_4319E0(v4[273], v4[274], v14, v15, 1);
                v9 = v24;
              }
              else
              {
                v16 = 0;
              }
              v19 = *v9;
              v33 = -1;
              sub_494240(v19, v16);
              pThis = this;
            }
            sub_431230((int)&pThis[4 * v4[23] + 95], v9);
            v9 += 31;
            v24 = v9;
            v35 += 31;
          }
          while ( v9 != (uint32_t *)v4[265] );
        }
      }
    }
    else
    {
      off_77F3FC(aCriticalErrorD, v4[23]);
    }
  }
}


// ------------------------------------------------------------
// 0x4322F0 CNRDVirtualCharacter__vmt198
// ------------------------------------------------------------
void /*thiscall*/ CNRDVirtualCharacter__vmt198(void ***this, int pArg2)
{
  int fld_e153; // edi
  void **pThis_4; // edi
  void ***i; // ebx

  if ( *(this + pArg2 + 85) != (void **)0xFFFF )
  {
    *(this + pArg2 + 85) = (void **)0xFFFF;
    if ( pArg2 == 9 )
    {
      sub_4015C0((void *)szPassword, 0);
      fld_e153 = (int)*(this + 153);
      if ( fld_e153 != 0 )
      {
        sub_42AF90(*(this + 153));
        sub_657740(fld_e153, 228);
      }
      *(this + 153) = nullptr;
    }
    pThis_4 = *(this + 4 * pArg2 + 96);
    for ( i = this + 4 * pArg2; pThis_4 != i[97]; ++pThis_4 )
    {
      sub_494500(*pThis_4);
      sub_494500(*pThis_4);
      sub_494500(*pThis_4);
    }
    if ( i[96] != nullptr )
      j__free(i[96]);
    i[96] = nullptr;
    i[97] = nullptr;
    i[98] = nullptr;
  }
}



// ------------------------------------------------------------
// 0x4323E0 sub_4323E0
// ------------------------------------------------------------
void /*cdecl*/ sub_4323E0(char pszArg1, int nArg2, int nArg3, int nArg4, float fArg5, char pszArg6, int nArg7)
{
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  BOOL v13; // edi
  int v14; // eax
  int v15; // [esp+4h] [ebp-10h]
  int v16; // [esp+2Ch] [ebp+18h]

  if ( LODWORD(fArg5) != 0xFFFF
    && nArg7 != 0
    && (pszArg6 == 0
     || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 200))(nArg4) == 0
     || *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 200))(nArg4) + 161) != 0)
    && LODWORD(fArg5) == 26029
    && pszArg1 == 0 )
  {
    if ( dword_8F8128[0] == 0 )
    {
      v7 = sub_42FCB0(228);
      if ( v7 != 0 )
        v8 = sub_431860(v7, "equipment/character/common/title/etcanimation/RainbowHopeBalloonStay.ani", 1);
      else
        v8 = 0;
      dword_8F8128[0] = v8;
      v9 = sub_42FCB0(228);
      if ( v9 != 0 )
        v10 = sub_431860(v9, "equipment/character/common/title/etcanimation/RainbowHopeBalloonMove.ani", 1);
      else
        v10 = 0;
      dword_8F812C = v10;
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 152))(nArg4) != 0 )
      v15 = nArg2 - 45;
    else
      v15 = nArg2 + 45;
    timeGetTime();
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 192))(nArg4);
    v11 = (uint64_t)((double)v16 * 0.34999999);
    LOBYTE(v16) = 0;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 184))(nArg4);
    v13 = v12 != 4;
    if ( v12 == 0 || v12 == 4 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 152))(nArg4) == 0 )
      LOBYTE(v16) = 1;
    sub_4938F0(dword_8F8128[v13]);
    sub_491F80(-1, -1, -1, nArg7, 1);
    if ( pszArg6 != 0 )
    {
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 128))(nArg4);
      sub_491EA0(dword_79C0B0, v15, nArg3, *(float *)&v16, v11 + v14, 0.40000001, 0.30000001, 100);
    }
    else
    {
      sub_491D00(dword_79C0B0, v15, nArg3 - v11, *(float *)&v16);
    }
  }
}



// ------------------------------------------------------------
// 0x432600 sub_432600
// ------------------------------------------------------------
void /*cdecl*/ sub_432600(char pszArg1, int nArg2, int nArg3, int nArg4, int nArg5, char pszArg6, int nArg7)
{
  int v7; // eax

  if ( nArg5 != 0 )
    v7 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg5 + 16))(nArg5) + 4);
  else
    v7 = 0xFFFF;
  sub_4323E0(pszArg1, nArg2, nArg3, nArg4, *(float *)&v7, pszArg6, nArg7);
}



// ------------------------------------------------------------
// 0x432640 CNRDVirtualCharacter__vmt188
// ------------------------------------------------------------
int /*thiscall*/ sub_432640(int this, int ArgList)
{
  int result; // eax
  uint32_t *pThis_154; // edi
  int pThis_180; // esi
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  int v8; // esi
  int v9; // eax
  int v10; // esi
  int v11; // eax
  int v12; // esi
  int v13; // eax
  int v14; // eax
  int i; // [esp+4h] [ebp-10h]

  result = ArgList;
  if ( ArgList != *(uint32_t *)(this + 284) )
  {
    sub_42B040(this + 296);
    pThis_154 = (uint32_t *)(this + 340);
    pThis_180 = this + 384;
    for ( i = 10; i != 0; --i )
    {
      *pThis_154 = 0xFFFF;
      if ( *(uint32_t *)pThis_180 != 0 )
        j__free(*(void **)pThis_180);
      *(uint32_t *)pThis_180 = 0;
      *(uint32_t *)(pThis_180 + 4) = 0;
      *(uint32_t *)(pThis_180 + 8) = 0;
      ++pThis_154;
      pThis_180 += 16;
    }
    if ( *(uint32_t *)(this + 544) != 0 )
      j__free(*(void **)(this + 544));
    *(uint32_t *)(this + 544) = 0;
    *(uint32_t *)(this + 548) = 0;
    *(uint32_t *)(this + 552) = 0;
    *(uint32_t *)(this + 284) = ArgList;
    *(uint32_t *)(this + 288) = -1;
    v6 = (uint32_t *)sub_4CE8A0(ArgList);
    v7 = v6;
    if ( v6 != nullptr )
    {
      if ( sub_40BF00((std::_String_base *)(v6 + 269), 0, v6[274], szPassword, 0) != 0 )
      {
        if ( sub_42FCB0(228) != 0 )
        {
          if ( v7[275] < 0x10u )
            LOBYTE(v8) = (uint8_t)v7 + 56;
          else
            v8 = v7[270];
          if ( v7[416] < 0x10u )
            v9 = sub_431920((uint8_t)v7 + 108, v8, 1);
          else
            v9 = sub_431920(v7[411], v8, 1);
        }
        else
        {
          v9 = 0;
        }
        *(uint32_t *)(this + 296) = v9;
      }
      if ( sub_40BF00((std::_String_base *)(v7 + 213), 0, v7[218], szPassword, 0) != 0 )
      {
        if ( sub_42FCB0(228) != 0 )
        {
          if ( v7[219] < 0x10u )
            LOBYTE(v10) = (uint8_t)v7 + 88;
          else
            v10 = v7[214];
          if ( v7[416] < 0x10u )
            v11 = sub_431920((uint8_t)v7 + 108, v10, 1);
          else
            v11 = sub_431920(v7[411], v10, 1);
        }
        else
        {
          v11 = 0;
        }
        *(uint32_t *)(this + 300) = v11;
        sub_493D00(v11, 120.0);
      }
      if ( sub_40BF00((std::_String_base *)(v7 + 206), 0, v7[211], szPassword, 0) != 0 )
      {
        if ( sub_42FCB0(228) != 0 )
        {
          if ( v7[212] < 0x10u )
            LOBYTE(v12) = (uint8_t)v7 + 60;
          else
            v12 = v7[207];
          if ( v7[416] < 0x10u )
            v13 = sub_431920((uint8_t)v7 + 108, v12, 1);
          else
            v13 = sub_431920(v7[411], v12, 1);
        }
        else
        {
          v13 = 0;
        }
        *(uint32_t *)(this + 304) = v13;
      }
      v14 = sub_4924C0(0);
      *(uint32_t *)(this + 160) = sub_4918E0(v14, 2);
      result = ArgList;
      if ( ArgList != 0 )
      {
        switch ( ArgList )
        {
          case 1:
            *(uint32_t *)(this + 576) = 2;
            *(uint32_t *)(this + 580) = 91;
            break;
          case 2:
            *(uint32_t *)(this + 576) = -3;
            *(uint32_t *)(this + 580) = 120;
            break;
          case 3:
            *(uint32_t *)(this + 576) = 0;
            *(uint32_t *)(this + 580) = 76;
            break;
          default:
            break;
        }
      }
      else
      {
        *(uint32_t *)(this + 576) = -10;
        *(uint32_t *)(this + 580) = 92;
      }
    }
    else
    {
      return off_77F3FC("VIRTUAL CHARACTER ANIMATION SETTING FAIL! JOB : %d", ArgList);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4329C0 CNRDVirtualCharacter__vmt144
// ------------------------------------------------------------
void /*thiscall*/ CNRDVirtualCharacter__vmt144(void *this, int nArg2, int pArg3, int nArg4, int nArg5)
{
  int v6; // eax
  int pObj2; // eax
  int pObj; // eax
  int pThis_A2; // eax
  int pThis_34; // eax
  int v11; // eax
  int pThis_99; // [esp-4h] [ebp-10h]

  if ( (uint8_t)nArg2 != 0 )
  {
    nullsub_2(nArg2, pArg3, nArg4, nArg5);
    if ( *((uint32_t *)this + 71) == 2 && *((uint32_t *)this + 72) == 3 )
      sub_4C4EF0(this, pArg3, nArg4, 0, 255);
    v6 = *((uint32_t *)dword_8F8528 + 12);
    if ( *(void **)(v6 + 8) == this )
    {
      if ( *(uint32_t *)(v6 + 12) != 0 )
      {
        pObj = sub_418DD0(73);
        if ( pObj != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(
            pObj,
            pArg3 + 10,
            nArg4 - *((uint32_t *)this + 40) - 10,
            dword_79C0B0);
      }
      else
      {
        pObj2 = sub_418DD0(74);
        if ( pObj2 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(
            pObj2,
            pArg3 - 33,
            nArg4 - *((uint32_t *)this + 40) - 10,
            dword_79C0B0);
      }
    }
    pThis_A2 = *((uint32_t *)this + 162);
    if ( pThis_A2 == 0 || *(uint8_t *)(pThis_A2 + 284) == 0 )
    {
      pThis_99 = *((uint32_t *)this + 153);
      pThis_34 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
      v11 = sub_429830((uint32_t *)dword_8F8500, pThis_34);
      sub_42FDA0(pArg3, (int)this, pArg3, nArg4, (int)this, v11, pThis_99);
    }
    sub_4323E0(1, pArg3, nArg4, (int)this, *((float *)this + 94), 0, 255);
  }
  else
  {
    sub_4323E0(0, pArg3, nArg4, (int)this, *((float *)this + 94), 0, 255);
    nullsub_2(0, pArg3, nArg4, nArg5);
  }
}



// ------------------------------------------------------------
// 0x432B20 CNRDVirtualCharacter__vmt148
// ------------------------------------------------------------
void /*thiscall*/ CNRDVirtualCharacter__vmt148(float *this, char pszArg2, int nArg3, int nArg4, int nArg5)
{
  int pThis_34; // eax
  int v9; // eax
  int v10; // eax
  int v11; // [esp+Ch] [ebp-4h]
  int v12; // [esp+1Ch] [ebp+Ch]
  int dword_8F850C2; // [esp+20h] [ebp+10h]

  if ( pszArg2 == 0 )
  {
    sub_4323E0(0, nArg3, nArg4, (int)this, *(this + 94), 1, 255);
    pThis_34 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 52))(this);
    v9 = sub_429830((uint32_t *)dword_8F8500, pThis_34);
    v11 = v9;
    if ( v9 != 0 && *(uint8_t *)(v9 + 188) != 0 && ((float *)dword_8F7C08 != this || *(uint32_t *)(v9 + 184) != 0) )
    {
      v12 = 0;
      dword_8F850C2 = dword_8F850C;
      if ( sub_456480(dword_8F850C) == -1 )
        v10 = 0;
      else
        v10 = *(uint32_t *)(dword_8F850C2 + 4 * sub_456480(dword_8F850C2) + 16);
      if ( v10 == v11 )
        v12 = 1;
      sub_491530(2, 0);
      sub_424760(dword_79C0B0, nArg3 - 63, nArg4 - 21, *(&dword_8F811C + v12), 1.0, 1065353216, 0.0, -1, 0.0, 0.0);
      sub_491630(2);
    }
  }
  CNRDObject__vmt148(this, pszArg2, nArg3, nArg4, nArg5);
  if ( pszArg2 != 0 )
  {
    if ( *((uint32_t *)this + 71) == 2 && *((uint32_t *)this + 72) == 3 )
      sub_4C4EF0(this, nArg3, nArg4, 1, 255);
    sub_4323E0(1, nArg3, nArg4, (int)this, *(this + 94), 1, 255);
  }
}



// ============================================================
// §20 房间/命令检查/配置/过滤（0x432C70-0x433540）
//   CNWarRoomManager·CNCommandChecker·CNRDConfigFile·CNRDAStar·CNWebTextFilter·
//   CNRDItemTradeModule 虚表家族
// ============================================================
// ------------------------------------------------------------
// 0x432C70 CNWarRoomManager__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNWarRoomManager__vmt0(uint32_t *Block, char pszArg2)
{
  *Block = &vftbl_CNWarRoomManager;
  sub_49F9F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x432CA0 CNCommandChecker__vmt14
// ------------------------------------------------------------
int /*thiscall*/ CNCommandChecker__vmt14(void *this, int nArg2, int nArg3, int nArg4)
{
  uint32_t v5[2]; // [esp+0h] [ebp-8h] BYREF

  v5[1] = nArg4;
  v5[0] = nArg3;
  return (*(int (/*thiscall*/ **)(void *, int, uint32_t *))(*(uint32_t *)this + 16))(this, nArg2, v5);
}



// ------------------------------------------------------------
// 0x432CD0 sub_432CD0
// ------------------------------------------------------------
void /*thiscall*/ sub_432CD0(uint32_t *this)
{
  sub_41A630((unsigned int)this);
  *this = &vftbl_cfloat;
}



// ------------------------------------------------------------
// 0x432CF0 sub_432CF0
// ------------------------------------------------------------
double /*stdcall*/ sub_432CF0(float fArg1)
{
  sub_41A590(LODWORD(fArg1));
  return fArg1;
}



// ------------------------------------------------------------
// 0x432D10 sub_432D10
// ------------------------------------------------------------
// attributes: thunk
void /*thiscall*/ sub_432D10(void *this)
{
  sub_41A580(this);
}



// ------------------------------------------------------------
// 0x432D20 sub_432D20
// ------------------------------------------------------------
void /*thiscall*/ sub_432D20(void **this)
{
  *this = nullptr;
  sub_41BFE0(this, szPassword);
}



// ------------------------------------------------------------
// 0x432D40 sub_432D40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_432D40(uint32_t *this)
{
  *this = 1065353216;
  *(this + 1) = 1065353216;
  *(this + 2) = 1065353216;
  *(this + 3) = 1065353216;
  *(this + 4) = 1065353216;
  *(this + 5) = 1065353216;
  *(this + 6) = 1065353216;
  *(this + 7) = 1065353216;
  *(this + 8) = 1065353216;
  *(this + 9) = 1065353216;
  *(this + 10) = 1065353216;
  return this;
}



// ------------------------------------------------------------
// 0x432D70 CNRDConfigFile__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDConfigFile__vmt0(uint32_t *Block, char pszArg2)
{
  *Block = &vftbl_CNRDConfigFile;
  sub_48B720();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x432DC0 sub_432DC0
// ------------------------------------------------------------
int /*thiscall*/ sub_432DC0(char *this)
{
  sub_41A580(this + 18);
  return sub_41A580(this + 4);
}



// ------------------------------------------------------------
// 0x432E10 CNRDAStar__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDAStar__vmt0(uint32_t *Block, char pszArg2)
{
  *Block = &vftbl_CNRDAStar;
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x432E40 CNWebTextFilter__vmt4
// ------------------------------------------------------------
int /*thiscall*/ CNWebTextFilter__vmt4(uint8_t *this)
{
  *(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x432E50 sub_432E50
// ------------------------------------------------------------
int /*cdecl*/ sub_432E50(int nArg1)
{
  int result; // eax

  switch ( nArg1 )
  {
    case 0:
      result = 1;
      break;
    case 1:
      result = 0;
      break;
    case 2:
      result = 3;
      break;
    case 3:
      result = 2;
      break;
    default:
      result = 4;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x432EA0 sub_432EA0
// ------------------------------------------------------------
void */*cdecl*/ sub_432EA0(void *Src, int nArg2, int nArg3, int nArg4)
{
  void *result; // eax

  result = Src;
  if ( strcmp((const char *)Src, szPassword) != 0 )
    return (void *)sub_65FE10(Src, 0, nArg3, nArg4, 0, 0xFFFF, nArg2);
  return result;
}



// ------------------------------------------------------------
// 0x432EE0 sub_432EE0
// ------------------------------------------------------------
int /*cdecl*/ sub_432EE0(int nArg1)
{
  return sub_65DE30(0xFFFF, nArg1);
}



// ------------------------------------------------------------
// 0x432F00 sub_432F00
// ------------------------------------------------------------
void */*cdecl*/ sub_432F00(int nArg1)
{
  switch ( nArg1 )
  {
    case 0:
      return dword_8F852C;
    case 1:
      return dword_8F8534;
    case 2:
      return dword_8F8530;
    case 4:
      return *(void **)(dword_8F8538 + 16);
    default:
      break;
  }
  return nullptr;
}



// ------------------------------------------------------------
// 0x432F40 sub_432F40
// ------------------------------------------------------------
uint64_t /*cdecl*/ sub_432F40(float fArg1)
{
  double fArg12; // st7
  char v3; // c0

  fArg12 = fArg1;
  if ( v3 != 0 )
    return (uint64_t)(fArg12 - 0.5);
  else
    return (uint64_t)(fArg12 + 0.5);
}



// ------------------------------------------------------------
// 0x432F70 sub_432F70
// ------------------------------------------------------------
bool sub_432F70()
{
  dword_8F84B4 = operator new(1u);
  return dword_8F84B4 != nullptr;
}



// ------------------------------------------------------------
// 0x432FA0 sub_432FA0
// ------------------------------------------------------------
void sub_432FA0()
{
  int v0; // esi
  DWORD Time; // eax

  v0 = sub_4D33A0(&unk_77F9D8);
  Time = timeGetTime();
  srand(1000 * Time + v0);
}



// ------------------------------------------------------------
// 0x432FD0 sub_432FD0
// ------------------------------------------------------------
double /*cdecl*/ sub_432FD0(int nArg1, int nArg2)
{
  double result; // st7

  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
  {
    sub_4527C0(nArg1, nArg2);
  }
  else if ( *(uint32_t *)(dword_8F7A24 + 12) == 6 )
  {
    return sub_42C400(nArg1, nArg2);
  }
  else
  {
    return 1.0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x433000 sub_433000
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_433000(uint32_t *this, int pArg2)
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);
  *(uint32_t *)(pArg2 + 8) = *result;
  if ( *(uint8_t *)(*result + 137) == 0 )
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
// 0x433060 sub_433060
// ------------------------------------------------------------
int /*cdecl*/ sub_433060(int pArg1)
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 137) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x433090 sub_433090
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_433090(uint32_t *pArg1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 137) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 137) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4330C0 sub_4330C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4330C0(uint32_t *this, uint32_t *pArg2)
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 137) == 0 )
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
// 0x433130 sub_433130
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_433130(uint32_t *this, int pArg2)
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);
  *(uint32_t *)(pArg2 + 8) = *result;
  if ( *(uint8_t *)(*result + 21) == 0 )
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
// 0x433190 sub_433190
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_433190(uint32_t *pArg1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 25) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 25) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4331B0 sub_4331B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4331B0(uint32_t *this, int pArg2)
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);
  *(uint32_t *)(pArg2 + 8) = *result;
  if ( *(uint8_t *)(*result + 33) == 0 )
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
// 0x433210 sub_433210
// ------------------------------------------------------------
int /*cdecl*/ sub_433210(int pArg1)
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 33) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x433230 sub_433230
// ------------------------------------------------------------
int /*thiscall*/ sub_433230(uint32_t *this, uint32_t *pArg2)
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 33) == 0 )
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
// 0x433290 sub_433290
// ------------------------------------------------------------
int /*thiscall*/ sub_433290(uint32_t *this, uint32_t *pArg2)
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 45) == 0 )
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
// 0x4332F0 sub_4332F0
// ------------------------------------------------------------
int */*thiscall*/ sub_4332F0(int *this)
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 137) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 137) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 137) == 0; result = (int *)result[1] )
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
      if ( *(uint8_t *)(*v2 + 137) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 137) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x433360 sub_433360
// ------------------------------------------------------------
int /*thiscall*/ sub_433360(int this)
{
  *(uint8_t *)(this + 372) = 0;
  *(uint32_t *)(this + 368) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 376) = 0;
  *(uint8_t *)(this + 380) = 1;
  *(uint8_t *)(this + 382) = 0;
  *(uint8_t *)(this + 381) = 0;
  *(uint32_t *)(this + 392) = 0;
  *(uint32_t *)(this + 388) = 0;
  *(uint32_t *)(this + 384) = 0;
  *(uint8_t *)(this + 412) = 0;
  *(uint32_t *)(this + 408) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 416) = 0;
  *(uint8_t *)(this + 420) = 1;
  *(uint8_t *)(this + 422) = 0;
  *(uint8_t *)(this + 421) = 0;
  *(uint32_t *)(this + 432) = 0;
  *(uint32_t *)(this + 428) = 0;
  *(uint32_t *)(this + 424) = 0;
  sub_45D410(this);
  sub_45D4C0(this);
  return this;
}



// ------------------------------------------------------------
// 0x433420 sub_433420
// ------------------------------------------------------------
char /*thiscall*/ sub_433420(int this)
{
  nullsub_3();
  *(uint32_t *)(this + 408) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 412) = 0;
  *(uint32_t *)(this + 368) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 372) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x433480 sub_433480
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_433480(uint8_t *this)
{
  *(uint32_t *)this = &vftbl_CNRDItemTradeModule;
  *(this + 28) = 0;
  *((uint32_t *)this + 6) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 8) = 0;
  *(this + 36) = 1;
  *(this + 38) = 0;
  *(this + 37) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 10) = 0;
  *(this + 56) = 0;
  *((uint32_t *)this + 13) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 15) = 0;
  *(this + 64) = 1;
  *(this + 66) = 0;
  *(this + 65) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 17) = 0;
  sub_484490(this);
  sub_4847F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x433510 CNRDItemTradeModule__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDItemTradeModule__vmt0(void *Block, char pszArg2)
{
  sub_433540();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ============================================================
// §21 Camera/文本过滤与主帧 tick（0x433540-0x4337E0）
//   0x433690 = 主帧 tick（timeGetTime 驱动；'SHUTTER_ON' 截屏音效；调试退出键）
// ============================================================
// ------------------------------------------------------------
// 0x433540 sub_433540
// ------------------------------------------------------------
char /*thiscall*/ sub_433540(uint32_t *this)
{
  *this = &vftbl_CNRDItemTradeModule;
  sub_4847B0();
  *(this + 13) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 56) = 0;
  *(this + 6) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 28) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4335A0 cfloat__vmt0
// ------------------------------------------------------------
void */*thiscall*/ cfloat__vmt0(void *Block, char pszArg2)
{
  sub_432D10(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4335D0 Camera__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ Camera__vmt0(uint32_t *Block, char pszArg2)
{
  *Block = &vftbl_Camera;
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x433600 sub_433600
// ------------------------------------------------------------
void /*thiscall*/ sub_433600(uint32_t *this)
{
  *this = &vftbl_ITextFilter;
}



// ------------------------------------------------------------
// 0x433610 ITextFilter__vmt0
// ------------------------------------------------------------
uint32_t */*thiscall*/ ITextFilter__vmt0(uint32_t *Block, char pszArg2)
{
  *Block = &vftbl_ITextFilter;
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x433640 IRDCollisionObject__vmt28C
// ------------------------------------------------------------
int /*stdcall*/ IRDCollisionObject__vmt28C(int nArg1)
{
  return 0;
}



// ------------------------------------------------------------
// 0x433650 CNWebTextFilter__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNWebTextFilter__vmt0(void *Block, char pszArg2)
{
  sub_433680();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x433680 sub_433680
// ------------------------------------------------------------
void /*thiscall*/ sub_433680(uint8_t *this)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &vftbl_ITextFilter;
}



// ------------------------------------------------------------
// 0x433690 sub_433690
// ------------------------------------------------------------
// 【主帧 tick】timeGetTime 增量 → sub_65FAF0；CNCommandChecker/聊天过滤 tick；
//   热键 sub_415660(44) → "SHUTTER_ON" 音效（sub_65FE10，strcmp 防重）+ sub_43BEE0
//   播报【推断：截屏快门】；byte_77F280 调试机：dword_79C0B4 vt+20(10)+vt+16(84) 双键
//   → sub_41C1E0 退出清理。
char sub_433690()
{
  int dwNow; // eax
  int v1; // eax
  int v2; // ebx
  char result; // al

  LeaveCriticalSection(&stru_8F8258);
  EnterCriticalSection(&stru_8F8258);
  if ( (dword_8F8764 & 1) == 0 )
  {
    dword_8F8764 |= 1u;
    dword_8F8760 = timeGetTime();
  }
  dwNow = timeGetTime() - dword_8F8760;
  if ( byte_8F8554 != 0 )
  {
    sub_65FAF0(lpCriticalSection, dwNow);
    dword_8F8760 = timeGetTime();
  }
  v1 = sub_656710();
  sub_656AA0(v1);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 116))(dword_8F8520);
  sub_45E1A0(dword_8F8524);
  CNCommandChecker__vmt4(&dword_8F8558);
  sub_451D50(dword_8F8528);
  if ( *(uint32_t *)(dword_79C0A0 + 32) != 0 && sub_415660(44, byte_8F875C) != 0 )
  {
    v2 = sub_6997C0(dword_9D3BE0);
    if ( strcmp("SHUTTER_ON", szPassword) != 0 )
      sub_65FE10(lpCriticalSection, "SHUTTER_ON", 0, 0, 0, 0, 0xFFFF, -1);
    sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), v2, -5000269, 0, -1);
  }
  result = byte_77F280;
  if ( byte_77F280 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, 10);
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 84);
      if ( result != 0 )
        sub_41C1E0(dword_8F7A24);
    }
  }
  return result;
}



// ============================================================
// §22 物品播报与 PVP 房间（0x4337E0-0x434CB0）
//   0x4337E0 物品获得播报（串1179/1180 → sub_43BEE0 上屏）；0x434020 CNPvpRoom
// ============================================================
// ------------------------------------------------------------
// 0x4337E0 sub_4337E0
// ------------------------------------------------------------
// 【物品获得播报】串 1179/1180 格式化（本体/带强化者两版）→ CNRDStackable RTTI 且
//   subtype==6 → 紫 -16715009，否则物品品质色 → sub_43BEE0 上屏；a4≠-1 时回调 +1268。
int /*cdecl*/ sub_4337E0(int nArg1, int nArg2, uint32_t *pArg3, int nArg4)
{
  int nArg22; // edi
  char *v5; // eax
  uint32_t *v6; // eax
  char *v7; // eax
  int result; // eax
  int pObj; // ecx
  int v10; // edi
  char *v11; // eax
  uint32_t *v12; // eax
  char *v13; // eax
  int pObj2; // edi
  int v15; // eax
  int pObj3; // ecx
  int v17; // eax
  uint32_t *v18; // [esp-10h] [ebp-9Ch]
  uint32_t *v19; // [esp-8h] [ebp-94h]
  char Buffer[128]; // [esp+8h] [ebp-84h] BYREF
  int dword_796E502; // [esp+88h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 16))(nArg1) + 4) != 0 )
  {
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 108))(nArg1);
    if ( pArg3 == (uint32_t *)sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )
    {
      v11 = sub_422E70(1179);
      sprintf(Buffer, v11, v10, nArg2);
    }
    else
    {
      if ( pArg3[10] < 0x10u )
        v12 = pArg3 + 5;
      else
        v12 = (uint32_t *)pArg3[5];
      v18 = v12;
      v13 = sub_422E70(1180);
      sprintf(Buffer, v13, v18, v10, nArg2);
    }
    pObj2 = __RTDynamicCast(nArg1, 0, &IRDItem `RTTI Type Descriptor', &CNRDStackable `RTTI Type Descriptor', 0);
    if ( pObj2 != 0 && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 132))(pObj2) == 6 )
      v15 = -16715009;
    else
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 24))(nArg1);
    sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, v15, 0, -1);
    result = nArg4;
    if ( nArg4 != -1 )
    {
      pObj3 = pArg3[49];
      if ( pObj3 != 0 )
        result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 1268))(pObj3, nArg1, nArg4);
    }
    if ( pObj2 != 0
      && (*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 4) == 1086
       || *(uint32_t *)((result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2)) + 4) == 7039) )
    {
      v17 = sub_44E8D0((char *)dword_8F8528, (void *)0x44, 0, 0);
      result = __RTDynamicCast(
                 v17,
                 0,
                 &IRDPopupWindow `RTTI Type Descriptor',
                 &CNRDSeriasPresentListWindow `RTTI Type Descriptor',
                 0);
      if ( result != 0 )
        return sub_4D4530(pObj2);
    }
  }
  else
  {
    if ( pArg3 == (uint32_t *)sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) )
    {
      nArg22 = nArg2;
      v5 = sub_422E70(1177);
      sprintf(Buffer, v5, nArg2);
    }
    else
    {
      if ( pArg3[10] < 0x10u )
        v6 = pArg3 + 5;
      else
        v6 = (uint32_t *)pArg3[5];
      nArg22 = nArg2;
      v19 = v6;
      v7 = sub_422E70(1178);
      sprintf(Buffer, v7, v19, nArg2);
    }
    sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
    result = nArg4;
    if ( nArg4 != -1 )
    {
      pObj = pArg3[49];
      if ( pObj != 0 )
        return (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj + 1260))(
                 pObj,
                 1,
                 nArg22,
                 0,
                 nArg4,
                 0,
                 0,
                 0,
                 0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x433A30 sub_433A30
// ------------------------------------------------------------
int /*cdecl*/ sub_433A30(void *Src, int nArg2, void *pArg3)
{
  return (int)memcpy_0(pArg3, Src, 4 * ((nArg2 - (int)Src) >> 2)) + 4 * ((nArg2 - (int)Src) >> 2);
}



// ------------------------------------------------------------
// 0x433A60 sub_433A60
// ------------------------------------------------------------
uint32_t *sub_433A60()
{
  uint32_t *result; // eax

  result = operator new(0x1Cu);
  if ( result != nullptr )
    *result = result;
  if ( result != (uint32_t *)-4 )
    result[1] = result;
  return result;
}



// ------------------------------------------------------------
// 0x433A80 sub_433A80
// ------------------------------------------------------------
uint32_t *sub_433A80()
{
  uint32_t *result; // eax

  result = operator new(0x8Cu);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 136) = 1;
  *((uint8_t *)result + 137) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x433AC0 sub_433AC0
// ------------------------------------------------------------
uint32_t *sub_433AC0()
{
  uint32_t *result; // eax

  result = operator new(0x18u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 20) = 1;
  *((uint8_t *)result + 21) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x433B00 sub_433B00
// ------------------------------------------------------------
uint32_t *sub_433B00()
{
  uint32_t *result; // eax

  result = operator new(0x1Cu);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 24) = 1;
  *((uint8_t *)result + 25) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x433B40 sub_433B40
// ------------------------------------------------------------
uint32_t *sub_433B40()
{
  uint32_t *result; // eax

  result = operator new(0x24u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 32) = 1;
  *((uint8_t *)result + 33) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x433B80 sub_433B80
// ------------------------------------------------------------
uint32_t *sub_433B80()
{
  uint32_t *result; // eax

  result = operator new(0x30u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 44) = 1;
  *((uint8_t *)result + 45) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x433BC0 sub_433BC0
// ------------------------------------------------------------
char /*stdcall*/ sub_433BC0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_433BC0(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x433C00 sub_433C00
// ------------------------------------------------------------
char /*stdcall*/ sub_433C00(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 25);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_433C00(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 25);
  }
  return result;
}



// ------------------------------------------------------------
// 0x433C40 sub_433C40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_433C40(uint32_t *this)
{
  *this = &vftbl_CNRDTutorialTip;
  `eh vector constructor iterator'(this + 2, 0x1Cu, 256, sub_40C120, sub_501490);
  `eh vector constructor iterator'(this + 1794, 0x1Cu, 256, sub_40C120, sub_501490);
  `eh vector constructor iterator'(this + 3586, 0x1Cu, 64, sub_40C120, sub_501490);
  sub_488870(this);
  sub_488940(this);
  return this;
}



// ------------------------------------------------------------
// 0x433CF0 sub_433CF0
// ------------------------------------------------------------
int /*stdcall*/ sub_433CF0(int nArg1, int nArg2, int nArg3)
{
  return sub_508EA0(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x433D10 sub_433D10
// ------------------------------------------------------------
int /*thiscall*/ sub_433D10(int this)
{
  if ( *(uint32_t *)(this + 76) >= 0x10u )
    j__free(*(void **)(this + 56));
  *(uint32_t *)(this + 76) = 15;
  *(uint32_t *)(this + 72) = 0;
  *(uint8_t *)(this + 56) = 0;
  sub_41A580(this + 38);
  sub_41A580(this + 24);
  return sub_41A580(this + 5);
}



// ------------------------------------------------------------
// 0x433DA0 sub_433DA0
// ------------------------------------------------------------
void /*thiscall*/ sub_433DA0(int this)
{
  `eh vector destructor iterator'((void *)(this + 16), 0x10u, 8, (void (/*thiscall*/ *)(void *))sub_5E5260);
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x433FB0 sub_433FB0
// ------------------------------------------------------------
void /*thiscall*/ sub_433FB0(void **this)
{
  *this = &vftbl_CNPvpRoom;
  nullsub_3();
  if ( (unsigned int)*(this + 26) >= 0x10 )
    j__free(*(this + 21));
  *(this + 26) = (void *)15;
  *(this + 25) = nullptr;
  *((uint8_t *)this + 84) = 0;
}



// ------------------------------------------------------------
// 0x434020 CNPvpRoom__vmt0
// ------------------------------------------------------------
void **/*thiscall*/ CNPvpRoom__vmt0(void **Block, char pszArg2)
{
  sub_433FB0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x434050 sub_434050
// ------------------------------------------------------------
void /*thiscall*/ sub_434050(char *this)
{
  *(uint32_t *)this = &vftbl_CNRDInterfaceManager;
  sub_451750();
  *((uint32_t *)this + 614) = &vftbl_nengine__IObject;
  *(this + 2460) = 0;
  if ( *((uint32_t *)this + 602) != 0 )
    j__free(*((void **)this + 602));
  *((uint32_t *)this + 602) = 0;
  *((uint32_t *)this + 603) = 0;
  *((uint32_t *)this + 604) = 0;
  `eh vector destructor iterator'(this + 1268, 0x10u, 71, (void (/*thiscall*/ *)(void *))sub_5E5260);
  `eh vector destructor iterator'(this + 132, 0x10u, 71, (void (/*thiscall*/ *)(void *))sub_5E5260);
}



// ------------------------------------------------------------
// 0x434100 sub_434100
// ------------------------------------------------------------
int /*stdcall*/ sub_434100(char *pszArg1, char *pszArg2)
{
  char *i; // esi
  int result; // eax

  for ( i = pszArg1; i != pszArg2; i += 32 )
    result = sub_432DC0(i);
  return result;
}



// ------------------------------------------------------------
// 0x434130 sub_434130
// ------------------------------------------------------------
void /*thiscall*/ sub_434130(void **this)
{
  sub_433FB0(this + 1);
}



// ------------------------------------------------------------
// 0x434140 sub_434140
// ------------------------------------------------------------
int /*thiscall*/ sub_434140(int this)
{
  char *fld_4; // esi
  int result; // eax
  char *i; // edi

  fld_4 = *(char **)(this + 4);
  result = 0;
  if ( fld_4 != nullptr )
  {
    for ( i = *(char **)(this + 8); fld_4 != i; fld_4 += 32 )
      sub_432DC0(fld_4);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x434180 sub_434180
// ------------------------------------------------------------
int /*stdcall*/ sub_434180(int nArg1, int nArg2)
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 20 )
    result = sub_433350(i);
  return result;
}



// ------------------------------------------------------------
// 0x4341B0 sub_4341B0
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4341B0(uint32_t *this, int ***uArg2, int **pDwArg3)
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
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);
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
// 0x434470 sub_434470
// ------------------------------------------------------------
int ***/*thiscall*/ sub_434470(uint32_t *this, int ***uArg2, int **pDwArg3)
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
  uint8_t v20[20]; // [esp+34h] [ebp-34h] BYREF
  int v21; // [esp+48h] [ebp-20h]
  int v22; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v26; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 25) != 0 )
  {
    v22 = 15;
    v21 = 0;
    v20[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);
    v26 = 0;
    sub_401740(pExceptionObject, (int)v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_4B0C60(&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 25) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 25) == 0 )
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
      if ( *((uint8_t *)v4 + 25) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_433190(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 25) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_4B0BE0(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 25) != 0 )
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
    if ( *((uint8_t *)v4 + 25) == 0 )
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
  v14 = *((uint8_t *)v5 + 24);
  *((uint8_t *)v5 + 24) = *((uint8_t *)pDwArg32 + 24);
  *((uint8_t *)pDwArg32 + 24) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 24) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 24) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 24) == 0 )
          {
            *((uint8_t *)v16 + 24) = 1;
            *((uint8_t *)v6 + 24) = 0;
            sub_4B0FD0(v6);
            v16 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 25) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 24) != 1 || *(uint8_t *)(v16[2] + 24) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 24) == 1 )
            {
              *(uint8_t *)(*v16 + 24) = 1;
              *((uint8_t *)v16 + 24) = 0;
              sub_4B0C00(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 24) = *((uint8_t *)v6 + 24);
            *((uint8_t *)v6 + 24) = 1;
            *(uint8_t *)(v16[2] + 24) = 1;
            sub_4B0FD0(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 24) == 0 )
          {
            *((uint8_t *)v16 + 24) = 1;
            *((uint8_t *)v6 + 24) = 0;
            sub_4B0C00(v6);
            v16 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 25) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 24) != 1 || *(uint8_t *)(*v16 + 24) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 24) == 1 )
            {
              *(uint8_t *)(v16[2] + 24) = 1;
              *((uint8_t *)v16 + 24) = 0;
              sub_4B0FD0(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 24) = *((uint8_t *)v6 + 24);
            *((uint8_t *)v6 + 24) = 1;
            *(uint8_t *)(*v16 + 24) = 1;
            sub_4B0C00(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 24) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 24) = 1;
  }
  j__free(Block);
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x434730 sub_434730
// ------------------------------------------------------------
void /*noreturn*/ sub_434730()
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
// 0x4347A0 sub_4347A0
// ------------------------------------------------------------
void /*thiscall*/ sub_4347A0(void **this)
{
  sub_433FB0(this + 4);
}



// ------------------------------------------------------------
// 0x4347B0 sub_4347B0
// ------------------------------------------------------------
void /*thiscall*/ sub_4347B0(void **this)
{
  sub_4017E0(this + 27);
  sub_4017E0(this + 23);
  sub_41B010(this + 22);
  sub_41B010(this + 21);
  sub_41B010(this + 20);
  sub_41B010(this + 19);
  `eh vector destructor iterator'(this + 15, 4u, 4, sub_401060);
  `eh vector destructor iterator'(this + 11, 4u, 4, sub_401060);
  sub_41B010(this + 10);
  sub_41B010(this + 9);
  sub_41B010(this + 8);
  sub_41B010(this + 7);
  sub_41B010(this + 6);
  `eh vector destructor iterator'(this + 4, 4u, 2, sub_401060);
  sub_41B010(this + 3);
  sub_41B010(this + 2);
  sub_41B010(this + 1);
}



// ------------------------------------------------------------
// 0x434950 sub_434950
// ------------------------------------------------------------
char /*thiscall*/ sub_434950(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0xAAAAAAA )
    sub_434730(this);
  pMem = (char *)operator new(24 * uArg2);
  *(this + 3) = &pMem[24 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x4349A0 sub_4349A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4349A0(int *this)
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);
  result = 0;
  if ( fld_e1 != 0 )
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 20 )
      sub_433350(fld_e1);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4349E0 sub_4349E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4349E0(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x3FFFFFFF )
    sub_434730(this);
  pMem = (char *)operator new(4 * uArg2);
  *(this + 3) = &pMem[4 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x434A40 sub_434A40
// ------------------------------------------------------------
char /*thiscall*/ sub_434A40(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x7FFFFFF )
    sub_434730(this);
  pMem = (char *)operator new(32 * uArg2);
  *(this + 3) = &pMem[32 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x434A90 sub_434A90
// ------------------------------------------------------------
char /*thiscall*/ sub_434A90(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x3333333 )
    sub_434730(this);
  pMem = (char *)operator new(80 * uArg2);
  *(this + 3) = &pMem[80 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x434AE0 sub_434AE0
// ------------------------------------------------------------
char /*thiscall*/ sub_434AE0(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x6666666 )
    sub_434730(this);
  pMem = (char *)operator new(40 * uArg2);
  *(this + 3) = &pMem[40 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x434B30 sub_434B30
// ------------------------------------------------------------
int */*thiscall*/ sub_434B30(int **this, int *pDwArg2, int nArg3, int nArg4)
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
    sub_429740(*(void ***)(fld_e1 + 4));
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
        sub_429950(this, &nArg3, nArg322);
      }
      while ( nArg32 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x434BF0 sub_434BF0
// ------------------------------------------------------------
int */*thiscall*/ sub_434BF0(int **this, int *pDwArg2, int nArg3, int nArg4)
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
    sub_433BC0(*(void ***)(fld_e1 + 4));
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
        sub_4341B0(this, &nArg3, nArg322);
      }
      while ( nArg32 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ============================================================
// §23 脏话/文本过滤（0x434CB0-0x435DE0）
//   CNSlangTextFilter（0x435700）等
// ============================================================
// ------------------------------------------------------------
// 0x434CB0 sub_434CB0
// ------------------------------------------------------------
int **/*thiscall*/ sub_434CB0(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_433C00(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 25) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 25) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 25) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 25) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_434470(this, (int ***)&pDwArg3, v10);
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x434D70 sub_434D70
// ------------------------------------------------------------
void /*thiscall*/ sub_434D70(int *this, int pArg2, unsigned int uArg3, void *Block)
{
  int fld_e1; // edi
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  int v12; // edi
  int fld_e13; // eax
  unsigned int v14; // esi
  void *fld_e23; // ecx
  int fld_e26; // esi
  int fld_e12; // [esp-18h] [ebp-60h]
  int fld_e25; // [esp-Ch] [ebp-54h]
  unsigned int fld_e24; // [esp-8h] [ebp-50h]
  int v21; // [esp+0h] [ebp-48h] BYREF
  uint32_t v22[12]; // [esp+Ch] [ebp-3Ch] BYREF
  int v23; // [esp+44h] [ebp-4h]
  int v24; // [esp+50h] [ebp+8h]
  int v25; // [esp+54h] [ebp+Ch]
  char *Blocka; // [esp+58h] [ebp+10h]
  void *Blockb; // [esp+58h] [ebp+10h]

  qmemcpy(v22, Block, 0x2Cu);
  fld_e1 = *(this + 1);
  v22[11] = &v21;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 44;
  else
    fld_e3 = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 44;
    else
      fld_e2 = 0;
    if ( 97612893 - fld_e2 < uArg3 )
      sub_434730(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 44;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 44 >= uArg3 )
      {
        v24 = (int)fld_e23 - 44 * uArg3;
        *(this + 2) = sub_508EA0(v24, fld_e23, fld_e23);
        sub_4F8D90(pArg2, v24, Blockb);
        sub_508E70(pArg2, pArg2 + 44 * uArg3, v22);
      }
      else
      {
        sub_508EA0(pArg2, fld_e23, pArg2 + 44 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 44;
        fld_e25 = *(this + 2);
        v23 = 2;
        sub_508EE0(fld_e25, fld_e24, v22);
        fld_e26 = 44 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        sub_508E70(pArg2, fld_e26 - 44 * uArg3, v22);
      }
    }
    else
    {
      if ( 97612893 - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 44;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_527B90(this);
      v12 = 44 * v10;
      Blocka = (char *)operator new(44 * v10);
      fld_e12 = *(this + 1);
      v23 = 0;
      v25 = sub_508EA0(fld_e12, pArg2, Blocka);
      sub_4F8DF0(v25, uArg3, v22);
      sub_508EA0(pArg2, *(this + 2), 44 * uArg3 + v25);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 44;
      v14 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v12];
      *(this + 2) = (int)&Blocka[44 * v14];
      *(this + 1) = (int)Blocka;
    }
  }
}



// ------------------------------------------------------------
// 0x435020 sub_435020
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_435020(uint32_t *this, uint32_t *pArg2)
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

  v3 = pArg2[1];
  v11 = &v9;
  pThis = this;
  if ( v3 != 0 )
    v4 = (pArg2[2] - v3) >> 2;
  else
    v4 = 0;
  if ( sub_42AA50(this, v4) != 0 )
  {
    fld_e1 = *(this + 1);
    v7 = pArg2[2];
    v6 = pArg2[1];
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x4350C0 sub_4350C0
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_4350C0(int *this)
{
  return sub_4349A0(this);
}



// ------------------------------------------------------------
// 0x4350D0 sub_4350D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4350D0(int *this, uint32_t *uArg2, int nArg3, void *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 44 != 0 )
    v6 = (nArg3 - fld_e1) / 44;
  else
    v6 = 0;
  sub_434D70(this, nArg3, 1u, Block);
  *uArg2 = *(this + 1) + 44 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x435140 sub_435140
// ------------------------------------------------------------
int ***/*thiscall*/ sub_435140(uint32_t *this, int ***uArg2, int **pDwArg3)
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
// 0x435420 sub_435420
// ------------------------------------------------------------
char /*stdcall*/ sub_435420(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 45);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_435420(i[2]);
    i = (void **)*i;
    sub_5014C0(Block2);
    j__free(Block2);
    result = *((uint8_t *)i + 45);
  }
  return result;
}



// ------------------------------------------------------------
// 0x435470 sub_435470
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_435470(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  `eh vector constructor iterator'(this + 4, 0x10u, 8, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  return this;
}



// ------------------------------------------------------------
// 0x4354D0 sub_4354D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4354D0(uint32_t *this, void *Block, int nArg3)
{
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  sub_484CA0();
  sub_485E80(Block, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x435530 sub_435530
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_435530(uint32_t *this)
{
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 33) = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
  *(this + 54) = 0;
  *(this + 55) = 0;
  *(this + 56) = 0;
  sub_433EF0();
  return this;
}



// ------------------------------------------------------------
// 0x4355A0 sub_4355A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4355A0(uint32_t *Block)
{
  *Block = &vftbl_CNRDInterfaceManager;
  `eh vector constructor iterator'(Block + 33, 0x10u, 71, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  `eh vector constructor iterator'(Block + 317, 0x10u, 71, sub_4019A0, (void (/*thiscall*/ *)(void *))sub_5E5260);
  *(Block + 602) = 0;
  *(Block + 603) = 0;
  *(Block + 604) = 0;
  *((uint8_t *)Block + 2460) = 0;
  *(Block + 614) = &vftbl_nengine__CNTimer;
  *(Block + 616) = 0;
  *((uint8_t *)Block + 2468) = 1;
  *((uint8_t *)Block + 2470) = 0;
  *((uint8_t *)Block + 2469) = 0;
  *(Block + 620) = 0;
  *(Block + 619) = 0;
  *(Block + 618) = 0;
  *(Block + 627) = 12;
  *(Block + 628) = 0;
  *(Block + 629) = 0;
  *(Block + 630) = 0;
  sub_44AA50(Block);
  sub_450C80(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x435690 sub_435690
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_435690(uint8_t *this, int nArg2)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &vftbl_CNSlangTextFilter;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  sub_4D3710();
  *(this + 4) = 1;
  sub_4D4040(nArg2);
  return this;
}



// ------------------------------------------------------------
// 0x435700 CNSlangTextFilter__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNSlangTextFilter__vmt0(void *Block, char pszArg2)
{
  sub_435730();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x435730 sub_435730
// ------------------------------------------------------------
int /*thiscall*/ sub_435730(uint32_t *this)
{
  int result; // eax

  *this = &vftbl_CNSlangTextFilter;
  CNSlangTextFilter__vmt8();
  result = sub_4017E0(this + 2);
  *this = &vftbl_ITextFilter;
  return result;
}



// ------------------------------------------------------------
// 0x435790 sub_435790
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_435790(int *this, void *Block)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 44;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 44 )
    return sub_4350D0(this, &Block, *(this + 2), Block);
  fld_e22 = *(this + 2);
  result = (uint32_t *)sub_4F8DF0(fld_e22, 1, Block);
  *(this + 2) = fld_e22 + 44;
  return result;
}



// ------------------------------------------------------------
// 0x435820 sub_435820
// ------------------------------------------------------------
void /*stdcall*/ sub_435820(void **pArg1, void **pArg2)
{
  void **i; // esi

  for ( i = pArg1; i != pArg2; i += 6 )
    sub_5E5260(i);
}



// ------------------------------------------------------------
// 0x435850 sub_435850
// ------------------------------------------------------------
int /*thiscall*/ sub_435850(int this)
{
  void **fld_4; // esi
  int result; // eax
  void **i; // edi

  fld_4 = *(void ***)(this + 4);
  result = 0;
  if ( fld_4 != nullptr )
  {
    for ( i = *(void ***)(this + 8); fld_4 != i; fld_4 += 6 )
      sub_5E5260(fld_4);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x435890 sub_435890
// ------------------------------------------------------------
int /*stdcall*/ sub_435890(int nArg1, int nArg2)
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 80 )
    result = sub_433D10(i);
  return result;
}



// ------------------------------------------------------------
// 0x4358C0 sub_4358C0
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4358C0(uint32_t *this, int ***uArg2, int **pDwArg3)
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
  int pObj; // eax
  uint32_t *Block2; // eax
  int v18; // eax
  void *Block3; // [esp-4h] [ebp-64h]
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-5Ch] BYREF
  size_t v22; // [esp+2Ch] [ebp-34h] BYREF
  char v23; // [esp+30h] [ebp-30h]
  int v24; // [esp+40h] [ebp-20h]
  int v25; // [esp+44h] [ebp-1Ch]
  int v26; // [esp+48h] [ebp-18h]
  void *Block; // [esp+4Ch] [ebp-14h]
  uint32_t *pThis; // [esp+50h] [ebp-10h]
  int v29; // [esp+5Ch] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 33) != 0 )
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
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C640((int *)&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 33) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 33) == 0 )
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
      if ( *((uint8_t *)v4 + 33) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = sub_41C5C0(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v26 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 33) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v26 + 8) = sub_433210(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 33) != 0 )
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
    if ( *((uint8_t *)v4 + 33) == 0 )
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
  v14 = *((uint8_t *)v5 + 32);
  *((uint8_t *)v5 + 32) = *((uint8_t *)pDwArg32 + 32);
  *((uint8_t *)pDwArg32 + 32) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 32) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 32) != 1 )
          break;
        pObj = *v6;
        if ( v4 == (int *)*v6 )
        {
          pObj = v6[2];
          if ( *(uint8_t *)(pObj + 32) == 0 )
          {
            *(uint8_t *)(pObj + 32) = 1;
            *((uint8_t *)v6 + 32) = 0;
            sub_4331B0(v6);
            pObj = v6[2];
            pThis3 = pThis;
          }
          if ( *(uint8_t *)(pObj + 33) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)pObj + 32) != 1 || *(uint8_t *)(*(uint32_t *)(pObj + 8) + 32) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)(pObj + 8) + 32) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)pObj + 32) = 1;
              *(uint8_t *)(pObj + 32) = 0;
              sub_433230(pObj);
              pObj = v6[2];
            }
            *(uint8_t *)(pObj + 32) = *((uint8_t *)v6 + 32);
            *((uint8_t *)v6 + 32) = 1;
            *(uint8_t *)(*(uint32_t *)(pObj + 8) + 32) = 1;
            sub_4331B0(v6);
            break;
          }
        }
        else
        {
          if ( *(uint8_t *)(pObj + 32) == 0 )
          {
            *(uint8_t *)(pObj + 32) = 1;
            *((uint8_t *)v6 + 32) = 0;
            sub_433230(v6);
            pObj = *v6;
            pThis3 = pThis;
          }
          if ( *(uint8_t *)(pObj + 33) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)(pObj + 8) + 32) != 1 || *(uint8_t *)(*(uint32_t *)pObj + 32) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)pObj + 32) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)(pObj + 8) + 32) = 1;
              *(uint8_t *)(pObj + 32) = 0;
              sub_4331B0(pObj);
              pObj = *v6;
            }
            *(uint8_t *)(pObj + 32) = *((uint8_t *)v6 + 32);
            *((uint8_t *)v6 + 32) = 1;
            *(uint8_t *)(*(uint32_t *)pObj + 32) = 1;
            sub_433230(v6);
            break;
          }
        }
        *(uint8_t *)(pObj + 32) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 32) = 1;
  }
  if ( *((uint32_t *)Block + 5) != 0 )
    j__free(*((void **)Block + 5));
  Block2 = Block;
  Block3 = Block;
  *((uint32_t *)Block + 5) = 0;
  Block2[6] = 0;
  Block2[7] = 0;
  j__free(Block3);
  v18 = pThis[2];
  if ( v18 != 0 )
    pThis[2] = v18 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x435BA0 sub_435BA0
// ------------------------------------------------------------
char /*stdcall*/ sub_435BA0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 33);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_435BA0(i[2]);
    i = (void **)*i;
    sub_4CEB50(Block2);
    j__free(Block2);
    result = *((uint8_t *)i + 33);
  }
  return result;
}



// ------------------------------------------------------------
// 0x435BF0 sub_435BF0
// ------------------------------------------------------------
int /*cdecl*/ sub_435BF0(int nArg1, int nArg2, int nArg3)
{
  int nArg12; // esi
  int nArg32; // edi

  nArg12 = nArg1;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    sub_4ED3F0(nArg32, nArg12);
    *(uint32_t *)(nArg32 + 16) = *(uint32_t *)(nArg12 + 16);
    *(uint32_t *)(nArg32 + 20) = *(uint32_t *)(nArg12 + 20);
    nArg12 += 24;
    nArg32 += 24;
  }
  while ( nArg12 != nArg2 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x435C30 sub_435C30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_435C30(uint32_t *this)
{
  char *pThis_4000E; // edi

  *this = &vftbl_CNRDUdpModule;
  *(this + 1) = &CNRDUdpModule::`vftable';
  *(this + 2) = &CNRDUdpModule::`vftable';
  *((uint8_t *)this + 1048608) = 0;
  *(this + 262151) = &vftbl_nengine__CNTimer;
  *(this + 262153) = 0;
  *((uint8_t *)this + 1048616) = 1;
  *((uint8_t *)this + 1048618) = 0;
  *((uint8_t *)this + 1048617) = 0;
  *(this + 262157) = 0;
  *(this + 262156) = 0;
  *(this + 262155) = 0;
  pThis_4000E = (char *)(this + 262158);
  *(this + 262159) = sub_433A60();
  *((uint32_t *)pThis_4000E + 2) = 0;
  `eh vector constructor iterator'(this + 262170, 0x1Cu, 8, sub_401170, sub_401000);
  `eh vector constructor iterator'(this + 262237, 0x1Cu, 8, sub_401170, sub_401000);
  *((uint8_t *)this + 1049208) = 0;
  *(this + 262301) = &vftbl_nengine__CNTimer;
  *(this + 262303) = 0;
  *((uint8_t *)this + 1049216) = 1;
  *((uint8_t *)this + 1049218) = 0;
  *((uint8_t *)this + 1049217) = 0;
  *(this + 262307) = 0;
  *(this + 262306) = 0;
  *(this + 262305) = 0;
  *((uint8_t *)this + 1049960) = 0;
  *(this + 262489) = &vftbl_nengine__CNTimer;
  *(this + 262491) = 0;
  *((uint8_t *)this + 1049968) = 1;
  *((uint8_t *)this + 1049970) = 0;
  *((uint8_t *)this + 1049969) = 0;
  *(this + 262495) = 0;
  *(this + 262494) = 0;
  *(this + 262493) = 0;
  *((uint8_t *)this + 1050000) = 0;
  *(this + 262499) = &vftbl_nengine__CNTimer;
  *(this + 262501) = 0;
  *((uint8_t *)this + 1050008) = 1;
  *((uint8_t *)this + 1050010) = 0;
  *((uint8_t *)this + 1050009) = 0;
  *(this + 262505) = 0;
  *(this + 262504) = 0;
  *(this + 262503) = 0;
  sub_435470(this + 262522);
  CNRDUdpModule__vmtA8(this);
  CNRDUdpModule__vmtAC(this);
  return this;
}



// ============================================================
// §24 CNRDUdpModule UDP 模块（0x435DE0-0x436160）
// ============================================================
// ------------------------------------------------------------
// 0x435DE0 CNRDUdpModule__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmtC(uint32_t *this, int nArg2)
{
  *(this + 262147) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x435DF0 CNRDUdpModule__vmt10
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt10(uint32_t *this)
{
  return *(this + 262147) - (uint32_t)this - 12;
}



// ------------------------------------------------------------
// 0x435E30 CNRDUdpModule__vmt20
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDUdpModule__vmt20(uint32_t *this, char pszArg2)
{
  uint8_t *result; // eax

  result = (uint8_t *)*(this + 262147);
  *result = pszArg2;
  ++*(this + 262147);
  return result;
}



// ------------------------------------------------------------
// 0x435E50 CNRDUdpModule__vmt24
// ------------------------------------------------------------
uint16_t */*thiscall*/ CNRDUdpModule__vmt24(uint32_t *this, int16_t uArg2)
{
  uint16_t *result; // eax

  result = (uint16_t *)*(this + 262147);
  *result = uArg2;
  *(this + 262147) += 2;
  return result;
}



// ------------------------------------------------------------
// 0x435E70 CNRDUdpModule__vmt28
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDUdpModule__vmt28(uint32_t *this, int nArg2)
{
  uint32_t *result; // eax

  result = (uint32_t *)*(this + 262147);
  *result = nArg2;
  *(this + 262147) += 4;
  return result;
}



// ------------------------------------------------------------
// 0x435E90 CNRDUdpModule__vmt2C
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDUdpModule__vmt2C(uint32_t *this, int nArg2, int nArg3)
{
  uint32_t *result; // eax

  result = (uint32_t *)*(this + 262147);
  *result = nArg2;
  result[1] = nArg3;
  *(this + 262147) += 8;
  return result;
}



// ------------------------------------------------------------
// 0x435EB0 CNRDUdpModule__vmt30
// ------------------------------------------------------------
void **/*thiscall*/ CNRDUdpModule__vmt30(void **this, const void *pArg2, unsigned int uArg3)
{
  void **result; // eax

  result = this;
  if ( pArg2 != nullptr )
  {
    qmemcpy(*(this + 262147), pArg2, uArg3);
    *(this + 262147) = (char *)*(this + 262147) + uArg3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x435EF0 CNRDUdpModule__vmt34
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt34(void *this, int nArg2, int nArg3)
{
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 40))(this, nArg3);
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 48))(this, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x435F20 CNRDUdpModule__vmt38
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt38(void *this, const char *pArg2)
{
  return (*(int (/*thiscall*/ **)(void *, const char *, unsigned int))(*(uint32_t *)this + 52))(this, pArg2, strlen(pArg2));
}



// ------------------------------------------------------------
// 0x435F50 CNRDUdpModule__vmt40
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt40(uint32_t *this, int nArg2)
{
  *(this + 262148) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x435F60 CNRDUdpModule__vmt44
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt44(uint32_t *this)
{
  return *(this + 262148);
}



// ------------------------------------------------------------
// 0x435F70 CNRDUdpModule__vmt48
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDUdpModule__vmt48(uint32_t *this, uint8_t *uArg2)
{
  *uArg2 = *(uint8_t *)(*(this + 262148))++;
  return uArg2;
}



// ------------------------------------------------------------
// 0x435F90 CNRDUdpModule__vmt4C
// ------------------------------------------------------------
uint16_t */*thiscall*/ CNRDUdpModule__vmt4C(uint16_t **this, uint16_t *uArg2)
{
  *uArg2 = *(*(this + 262148))++;
  return uArg2;
}



// ------------------------------------------------------------
// 0x435FB0 CNRDUdpModule__vmt50
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDUdpModule__vmt50(uint32_t **this, uint32_t *uArg2)
{
  *uArg2 = *(*(this + 262148))++;
  return uArg2;
}



// ------------------------------------------------------------
// 0x435FD0 CNRDUdpModule__vmt54
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDUdpModule__vmt54(uint32_t *this, uint32_t *pArg2)
{
  uint32_t *fld_e262148; // edx

  fld_e262148 = (uint32_t *)*(this + 262148);
  *pArg2 = *fld_e262148;
  pArg2[1] = fld_e262148[1];
  *(this + 262148) += 8;
  return pArg2;
}



// ------------------------------------------------------------
// 0x436000 CNRDUdpModule__vmt58
// ------------------------------------------------------------
const void **/*thiscall*/ CNRDUdpModule__vmt58(const void **this, void *pArg2, unsigned int uArg3)
{
  qmemcpy(pArg2, *(this + 262148), uArg3);
  *(this + 262148) = (char *)*(this + 262148) + uArg3;
  return this;
}



// ------------------------------------------------------------
// 0x436040 CNRDUdpModule__vmt6C
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt6C(uint32_t *this, int pArg2)
{
  return *(this + pArg2 + 262293);
}



// ------------------------------------------------------------
// 0x436060 CNRDUdpModule__vmt70
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt70(uint32_t *this)
{
  *(this + 262293) = 0;
  *(this + 262294) = 0;
  *(this + 262295) = 0;
  *(this + 262296) = 0;
  *(this + 262297) = 0;
  *(this + 262298) = 0;
  *(this + 262299) = 0;
  *(this + 262300) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4360A0 CNRDUdpModule__vmt78
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt78(uint32_t *this)
{
  return *(this + 262149);
}



// ------------------------------------------------------------
// 0x4360B0 CNRDUdpModule__vmt80
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt80(uint32_t *this, int nArg2)
{
  *(this + 262150) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x4360C0 CNRDUdpModule__vmt84
// ------------------------------------------------------------
int /*thiscall*/ CNRDUdpModule__vmt84(uint32_t *this)
{
  return *(this + 262150);
}



// ------------------------------------------------------------
// 0x4360D0 CNRDUdpModule__vmt94
// ------------------------------------------------------------
char /*thiscall*/ CNRDUdpModule__vmt94(char *this, int nArg2)
{
  char result; // al

  result = *(this + 1048644);
  if ( result == 0 )
  {
    sub_656710();
    sub_6567B0(nArg2);
    *(this + 1048644) = 1;
    *(this + 1049217) = 0;
    *(this + 1049218) = 0;
    return sub_698F90((int)(this + 1049204), 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x436120 CNRDUdpModule__vmt9C
// ------------------------------------------------------------
char /*thiscall*/ CNRDUdpModule__vmt9C(uint8_t *this)
{
  return *(this + 1048644);
}



// ------------------------------------------------------------
// 0x436130 CNRDUdpModule__vmt4
// ------------------------------------------------------------
void */*thiscall*/ CNRDUdpModule__vmt4(void *Block, char pszArg2)
{
  sub_436160();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ============================================================
// §25 用户/组队/命令检查器（0x436160-0x437B00）
//   CNUserManager·CNRDPartyManager·CNCommandChecker 虚表家族
// ============================================================
// ------------------------------------------------------------
// 0x436160 sub_436160
// ------------------------------------------------------------
void /*thiscall*/ sub_436160(char *this)
{
  *(uint32_t *)this = &vftbl_CNRDUdpModule;
  *((uint32_t *)this + 1) = &CNRDUdpModule::`vftable';
  *((uint32_t *)this + 2) = &CNRDUdpModule::`vftable';
  CNRDUdpModule__vmtB0();
  sub_433DA0((int)(this + 1050088));
  *((uint32_t *)this + 262499) = &vftbl_nengine__IObject;
  *(this + 1050000) = 0;
  *((uint32_t *)this + 262489) = &vftbl_nengine__IObject;
  *(this + 1049960) = 0;
  *((uint32_t *)this + 262301) = &vftbl_nengine__IObject;
  *(this + 1049208) = 0;
  `eh vector destructor iterator'(this + 1048948, 0x1Cu, 8, sub_401000);
  `eh vector destructor iterator'(this + 1048680, 0x1Cu, 8, sub_401000);
  sub_6569D0(this + 1048632);
  j__free(*((void **)this + 262159));
  *((uint32_t *)this + 262159) = 0;
  *(this + 1048608) = 0;
  *((uint32_t *)this + 262151) = &vftbl_nengine__IObject;
}



// ------------------------------------------------------------
// 0x436250 sub_436250
// ------------------------------------------------------------
int /*thiscall*/ sub_436250(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_434B30((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x436290 sub_436290
// ------------------------------------------------------------
int /*thiscall*/ sub_436290(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_434BF0((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4362D0 sub_4362D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4362D0(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_434CB0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x436310 sub_436310
// ------------------------------------------------------------
char sub_436310()
{
  int v1; // esi
  int v2; // esi
  float *v3; // esi
  int j; // esi
  double v5; // st7
  char *v6; // esi
  int dword_98B7342; // edi
  char *v8; // esi
  int dword_98BA102; // edi
  float v10[11]; // [esp+0h] [ebp-64h] BYREF
  float i; // [esp+2Ch] [ebp-38h]
  int v12; // [esp+30h] [ebp-34h] BYREF
  char v13; // [esp+37h] [ebp-2Dh] BYREF
  char v14[4]; // [esp+38h] [ebp-2Ch] BYREF
  void *Block; // [esp+3Ch] [ebp-28h]
  int v16; // [esp+4Ch] [ebp-18h]
  unsigned int v17; // [esp+50h] [ebp-14h]
  int dword_796E502; // [esp+54h] [ebp-10h]
  int v19; // [esp+60h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( (uint8_t)sub_442A10((char)szPassword, (int)"Etc/EtcParameter.etc") == 0 )
  {
    off_77F3FC(aCriticalError);
    return 0;
  }
  v17 = 15;
  v16 = 0;
  LOBYTE(Block) = 0;
  v19 = 1;
  v12 = 0;
  sub_41BFE0(szPassword);
  v13 = 0;
  while ( (uint8_t)sub_443430(v14) != 0 )
  {
    sub_442B20(v14);
    if ( sub_40BF00(0, v16, "[nation code]", 13) == 0 )
    {
      v1 = sub_4423D0(0);
      sub_41C570(v1);
      dword_9B0AB0 = (int)&dword_9B0C08;
      if ( v1 != 1 )
        dword_9B0AB0 = (int)&dword_9B0BC8;
    }
    if ( sub_40BF00(0, v16, "[script version]", 16) != 0 )
    {
      if ( sub_40BF00(0, v16, "[durability decrease rate]", 26) != 0 )
      {
        if ( sub_40BF00(0, v16, "[equipment weight constant]", 27) != 0 )
        {
          if ( sub_40BF00(0, v16, "[damage fomula constant]", 24) != 0 )
          {
            if ( (uint8_t)sub_423300(v14, "[summoned monster status up rate]") != 0 )
            {
              v3 = (float *)&unk_9A05E0;
              do
                *v3++ = sub_442480(0);
              while ( (int)v3 < (int)&byte_9A05F0 );
            }
            else if ( (uint8_t)sub_423300(v14, "[divine armor defense constant]") != 0 )
            {
              dword_9A05C8 = sub_4423D0(0);
            }
            else if ( (uint8_t)sub_423300(v14, "[PVP equalization]") != 0 )
            {
              sub_5E5260(&unk_98B71C);
              sub_432D40(v10);
              for ( i = sub_442480(&v13); v13 != 0; i = sub_442480(&v13) )
              {
                for ( j = 0; j < 11; ++j )
                {
                  if ( j != 0 )
                    v5 = sub_442480(0);
                  else
                    v5 = i;
                  v10[j] = v5;
                }
                sub_435790(v10);
              }
            }
            else if ( (uint8_t)sub_423300(v14, "[PVP slave hp equalization]") != 0 )
            {
              flt_7904FC = sub_442480(0);
            }
            else if ( (uint8_t)sub_423300(v14, "[tutorial message]") != 0 )
            {
              v6 = (char *)dword_98B730;
              if ( dword_98B730 != nullptr )
              {
                dword_98B7342 = dword_98B734;
                if ( dword_98B730 != (void *)dword_98B734 )
                {
                  do
                  {
                    sub_41B010(v6);
                    v6 += 4;
                  }
                  while ( v6 != (char *)dword_98B7342 );
                  v6 = (char *)dword_98B730;
                }
                j__free(v6);
              }
              dword_98B730 = nullptr;
              dword_98B734 = 0;
              dword_98B738 = 0;
              while ( (uint8_t)sub_442E10(&v12) != 0 )
                sub_420BB0(&v12);
            }
            else if ( (uint8_t)sub_423300(v14, "[prohibited name]") != 0 )
            {
              v8 = (char *)dword_98BA0C;
              if ( dword_98BA0C != nullptr )
              {
                dword_98BA102 = dword_98BA10;
                if ( dword_98BA0C != (void *)dword_98BA10 )
                {
                  do
                  {
                    sub_41B010(v8);
                    v8 += 4;
                  }
                  while ( v8 != (char *)dword_98BA102 );
                  v8 = (char *)dword_98BA0C;
                }
                j__free(v8);
              }
              dword_98BA0C = nullptr;
              dword_98BA10 = 0;
              dword_98BA14 = 0;
              while ( (uint8_t)sub_442E10(&v12) != 0 )
                sub_420BB0(&v12);
            }
          }
          else
          {
            flt_9A05F4 = sub_442480(0);
            flt_9A05F8 = sub_442480(0);
            flt_9A05FC = sub_442480(0);
            flt_9A0600 = sub_442480(0);
            flt_9A0604 = sub_442480(0);
            flt_9A0608 = sub_442480(0);
            flt_9A060C = sub_442480(0);
            flt_9A0610 = sub_442480(0);
            flt_9A0614 = sub_442480(0);
            flt_9A0618 = sub_442480(0);
            flt_9A061C = sub_442480(0);
            flt_9A0620 = sub_442480(0);
            flt_9A0624 = sub_442480(0);
            flt_9A0628 = sub_442480(0);
          }
        }
        else
        {
          flt_791E20 = sub_442480(0);
          flt_9B06D0 = sub_442480(0);
        }
      }
      else
      {
        dword_9A0308 = sub_4423D0(0);
        dword_9A030C = sub_4423D0(0);
        dword_9A0594 = sub_4423D0(0);
      }
    }
    else
    {
      v2 = sub_4423D0(0);
      off_77F3FC("script version : %d", v2);
      if ( v2 != 30060504 )
      {
        off_77F3FC("g_scriptVersion != curVersion");
        LOBYTE(v19) = 0;
        sub_41B010(&v12);
        if ( v17 >= 0x10 )
          j__free(Block);
        return 0;
      }
    }
  }
  LOBYTE(v19) = 0;
  sub_41B010(&v12);
  if ( v17 >= 0x10 )
    j__free(Block);
  return 1;
}


// ------------------------------------------------------------
// 0x436840 sub_436840
// ------------------------------------------------------------
int /*thiscall*/ sub_436840(int *this)
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);
  result = 0;
  if ( fld_e1 != 0 )
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 80 )
      sub_433D10(fld_e1);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x436880 sub_436880
// ------------------------------------------------------------
int */*thiscall*/ sub_436880(int **this, int *pDwArg2, int nArg3, int nArg4)
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
    sub_435420(*(void ***)(fld_e1 + 4));
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
        sub_435140(this, &nArg3, nArg322);
      }
      while ( nArg32 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x436940 sub_436940
// ------------------------------------------------------------
int ***/*thiscall*/ sub_436940(uint32_t *this, int ***uArg2, int **pDwArg3)
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
  if ( *((uint8_t *)pDwArg3 + 137) != 0 )
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
  sub_4332F0(&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 137) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 137) == 0 )
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
      if ( *((uint8_t *)v4 + 137) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_433090(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 137) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_433060(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 137) != 0 )
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
    if ( *((uint8_t *)v4 + 137) == 0 )
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
  v14 = *((uint8_t *)v5 + 136);
  *((uint8_t *)v5 + 136) = *((uint8_t *)pDwArg32 + 136);
  *((uint8_t *)pDwArg32 + 136) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 136) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 136) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 136) == 0 )
          {
            *((uint8_t *)v16 + 136) = 1;
            *((uint8_t *)v6 + 136) = 0;
            sub_433000(v6);
            v16 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 137) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 136) != 1 || *(uint8_t *)(v16[2] + 136) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 136) == 1 )
            {
              *(uint8_t *)(*v16 + 136) = 1;
              *((uint8_t *)v16 + 136) = 0;
              sub_4330C0(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 136) = *((uint8_t *)v6 + 136);
            *((uint8_t *)v6 + 136) = 1;
            *(uint8_t *)(v16[2] + 136) = 1;
            sub_433000(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 136) == 0 )
          {
            *((uint8_t *)v16 + 136) = 1;
            *((uint8_t *)v6 + 136) = 0;
            sub_4330C0(v6);
            v16 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 137) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 136) != 1 || *(uint8_t *)(*v16 + 136) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 136) == 1 )
            {
              *(uint8_t *)(v16[2] + 136) = 1;
              *((uint8_t *)v16 + 136) = 0;
              sub_433000(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 136) = *((uint8_t *)v6 + 136);
            *((uint8_t *)v6 + 136) = 1;
            *(uint8_t *)(*v16 + 136) = 1;
            sub_4330C0(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 136) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 136) = 1;
  }
  sub_433FB0((char *)Block + 16);
  j__free(Block);
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x436CA0 sub_436CA0
// ------------------------------------------------------------
char /*stdcall*/ sub_436CA0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 137);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_436CA0(i[2]);
    i = (void **)*i;
    sub_4347A0(Block2);
    j__free(Block2);
    result = *((uint8_t *)i + 137);
  }
  return result;
}



// ------------------------------------------------------------
// 0x436CF0 sub_436CF0
// ------------------------------------------------------------
int /*cdecl*/ sub_436CF0(int nArg1, int nArg2, int nArg3)
{
  return sub_435BF0(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x436D10 sub_436D10
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_436D10(uint32_t *this)
{
  uint32_t *pThis_1; // esi
  uint32_t *v3; // eax

  pThis_1 = this + 1;
  *this = &vftbl_CNUserManager;
  v3 = sub_433AC0();
  pThis_1[1] = v3;
  *((uint8_t *)v3 + 21) = 1;
  *(uint32_t *)(pThis_1[1] + 4) = pThis_1[1];
  *(uint32_t *)pThis_1[1] = pThis_1[1];
  *(uint32_t *)(pThis_1[1] + 8) = pThis_1[1];
  pThis_1[2] = 0;
  sub_4296B0(this);
  sub_4298F0(this);
  return this;
}



// ------------------------------------------------------------
// 0x436D80 CNUserManager__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNUserManager__vmt0(void *Block, char pszArg2)
{
  sub_436DB0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x436DB0 sub_436DB0
// ------------------------------------------------------------
void /*thiscall*/ sub_436DB0(int **this)
{
  int **pThis; // esi
  int *v2; // eax
  int v3; // [esp-8h] [ebp-1Ch]
  int **pThis2; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  pThis = this;
  pThis2 = this;
  *this = (int *)&vftbl_CNUserManager;
  v5 = 0;
  sub_4297A0(this);
  v2 = pThis[2];
  ++pThis;
  v3 = *v2;
  v5 = -1;
  sub_434B30(pThis, (int *)&pThis2, v3, (int)v2);
  j__free(pThis[1]);
  pThis[1] = nullptr;
  pThis[2] = nullptr;
}



// ------------------------------------------------------------
// 0x436E30 sub_436E30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_436E30(uint32_t *this)
{
  uint32_t *pThis_1; // esi
  uint32_t *v3; // eax

  pThis_1 = this + 1;
  *this = &vftbl_CNRDPartyManager;
  v3 = sub_433AC0();
  pThis_1[1] = v3;
  *((uint8_t *)v3 + 21) = 1;
  *(uint32_t *)(pThis_1[1] + 4) = pThis_1[1];
  *(uint32_t *)pThis_1[1] = pThis_1[1];
  *(uint32_t *)(pThis_1[1] + 8) = pThis_1[1];
  pThis_1[2] = 0;
  sub_4562E0(this);
  sub_456A30(this);
  return this;
}



// ------------------------------------------------------------
// 0x436EA0 CNRDPartyManager__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDPartyManager__vmt0(void *Block, char pszArg2)
{
  sub_436ED0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x436ED0 sub_436ED0
// ------------------------------------------------------------
void /*thiscall*/ sub_436ED0(int **this)
{
  int **pThis; // esi
  int *v2; // eax
  int v3; // [esp-8h] [ebp-1Ch]
  int **pThis2; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  pThis = this;
  pThis2 = this;
  *this = (int *)&vftbl_CNRDPartyManager;
  v5 = 0;
  sub_4568C0();
  v2 = pThis[2];
  ++pThis;
  v3 = *v2;
  v5 = -1;
  sub_434BF0(pThis, (int *)&pThis2, v3, (int)v2);
  j__free(pThis[1]);
  pThis[1] = nullptr;
  pThis[2] = nullptr;
}



// ------------------------------------------------------------
// 0x436F50 sub_436F50
// ------------------------------------------------------------
int /*thiscall*/ sub_436F50(int this)
{
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  sub_435850(this);
  if ( *(uint32_t *)(this + 20) != 0 )
    j__free(*(void **)(this + 20));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 32) = 1;
  *(uint8_t *)(this + 40) = 1;
  return this;
}



// ------------------------------------------------------------
// 0x436FC0 sub_436FC0
// ------------------------------------------------------------
char */*thiscall*/ sub_436FC0(char *this)
{
  char *pThis_20; // edi
  uint32_t *v3; // eax

  *(uint32_t *)this = &vftbl_CNCommandChecker;
  *(this + 8) = 0;
  *((uint32_t *)this + 1) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 3) = 0;
  *(this + 16) = 1;
  *(this + 18) = 0;
  *(this + 17) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 5) = 0;
  pThis_20 = this + 32;
  v3 = sub_433B00();
  *((uint32_t *)pThis_20 + 1) = v3;
  *((uint8_t *)v3 + 25) = 1;
  *(uint32_t *)(*((uint32_t *)pThis_20 + 1) + 4) = *((uint32_t *)pThis_20 + 1);
  **((uint32_t **)pThis_20 + 1) = *((uint32_t *)pThis_20 + 1);
  *(uint32_t *)(*((uint32_t *)pThis_20 + 1) + 8) = *((uint32_t *)pThis_20 + 1);
  *((uint32_t *)pThis_20 + 2) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 18) = sub_425940();
  *((uint32_t *)this + 19) = 0;
  *((uint32_t *)this + 21) = sub_425940();
  *((uint32_t *)this + 22) = 0;
  CNCommandChecker__vmt64(this);
  CNCommandChecker__vmt68(this);
  return this;
}



// ------------------------------------------------------------
// 0x4370B0 ?set_bound@?$source_link_manager@V?$multi_link_registry@V?$ISource@W4agent_status@Concurrency@@@Concurrency@@@Concurrency@@@Concurrency@@QAEXI@Z
// ------------------------------------------------------------
int /*thiscall*/ Concurrency::source_link_manager<Concurrency::multi_link_registry<Concurrency::ISource<enum Concurrency::agent_status>>>::set_bound(
        uint32_t *this,
        int nArg2)
{
  *(this + 15) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x4370D0 CNCommandChecker__vmt44
// ------------------------------------------------------------
char /*thiscall*/ CNCommandChecker__vmt44(uint8_t *this, int pArg2)
{
  return *(this + pArg2 + 64);
}



// ------------------------------------------------------------
// 0x437100 CNCommandChecker__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNCommandChecker__vmtC(uint32_t *this, char pszArg2)
{
  int v4; // [esp+4h] [ebp-4h] BYREF

  sub_437140(&v4, &pszArg2);
  if ( v4 == *(this + 9) )
    return 0;
  else
    return v4 + 16;
}



// ------------------------------------------------------------
// 0x437140 sub_437140
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_437140(uint32_t *this, uint32_t *uArg2, uint32_t *uArg3)
{
  int v5; // eax
  int fld_e1; // esi
  int v8; // [esp+18h] [ebp+Ch]

  v5 = sub_437190(uArg3);
  fld_e1 = *(this + 1);
  v8 = v5;
  if ( v5 == fld_e1 || *uArg3 < *(uint32_t *)(v5 + 12) )
  {
    *uArg2 = fld_e1;
    return uArg2;
  }
  else
  {
    *uArg2 = v8;
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x437190 sub_437190
// ------------------------------------------------------------
int */*thiscall*/ sub_437190(uint32_t *this, uint32_t *uArg2)
{
  int *result; // eax
  int *v3; // ecx

  result = (int *)*(this + 1);
  v3 = (int *)result[1];
  while ( *((uint8_t *)v3 + 25) == 0 )
  {
    if ( v3[3] >= *uArg2 )
    {
      result = v3;
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4371C0 CNCommandChecker__vmt54
// ------------------------------------------------------------
int /*stdcall*/ CNCommandChecker__vmt54(char pszArg1)
{
  return sub_437240(&pszArg1);
}



// ------------------------------------------------------------
// 0x4371E0 sub_4371E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4371E0(int this, uint32_t *uArg2, uint32_t **Block)
{
  uint32_t *v4; // edi

  v4 = *Block;
  if ( Block != *(uint32_t ***)(this + 4) )
  {
    *Block[1] = *Block;
    (*Block)[1] = Block[1];
    j__free(Block);
    --*(uint32_t *)(this + 8);
  }
  *uArg2 = v4;
  return uArg2;
}



// ------------------------------------------------------------
// 0x437220 CNCommandChecker__vmt60
// ------------------------------------------------------------
int /*stdcall*/ CNCommandChecker__vmt60(char pszArg1)
{
  return sub_437240(&pszArg1);
}



// ------------------------------------------------------------
// 0x437240 sub_437240
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_437240(uint32_t *this, int nArg2)
{
  uint32_t **fld_e1; // edi
  uint32_t *result; // eax
  uint32_t *v5; // ebx

  fld_e1 = (uint32_t **)*(this + 1);
  result = *fld_e1;
  if ( *fld_e1 != fld_e1 )
  {
    v5 = (uint32_t *)nArg2;
    do
    {
      if ( result[2] == *v5 )
        result = sub_4371E0((int)this, &nArg2, (uint32_t **)result);
      result = (uint32_t *)*result;
    }
    while ( result != fld_e1 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x437280 CNCommandChecker__vmt1C
// ------------------------------------------------------------
void /*thiscall*/ CNCommandChecker__vmt1C(void **this)
{
  sub_6569D0(this + 17);
  sub_5E5260(this + 11);
}



// ------------------------------------------------------------
// 0x4372A0 CNCommandChecker__vmt5C
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNCommandChecker__vmt5C(uint32_t *this, int nArg2)
{
  uint32_t *fld_e18; // edx
  uint32_t *result; // eax

  fld_e18 = (uint32_t *)*(this + 18);
  result = (uint32_t *)*fld_e18;
  if ( (uint32_t *)*fld_e18 == fld_e18 )
    return (uint32_t *)sub_4372E0(*(this + 18), &nArg2);
  do
  {
    if ( result[2] == nArg2 )
      break;
    result = (uint32_t *)*result;
  }
  while ( result != fld_e18 );
  if ( result == fld_e18 )
    return (uint32_t *)sub_4372E0(*(this + 18), &nArg2);
  return result;
}



// ------------------------------------------------------------
// 0x4372E0 sub_4372E0
// ------------------------------------------------------------
int /*stdcall*/ sub_4372E0(int pArg1, int nArg2)
{
  int v2; // esi
  int result; // eax

  v2 = sub_40C0F0(pArg1, *(uint32_t *)(pArg1 + 4), nArg2);
  result = sub_437320(1);
  *(uint32_t *)(pArg1 + 4) = v2;
  **(uint32_t **)(v2 + 4) = v2;
  return result;
}



// ------------------------------------------------------------
// 0x437320 sub_437320
// ------------------------------------------------------------
int /*thiscall*/ sub_437320(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
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
// 0x4373B0 CNCommandChecker__vmt10
// ------------------------------------------------------------
uint32_t */*stdcall*/ CNCommandChecker__vmt10(char pszArg1, uint32_t *pArg2)
{
  uint32_t *result; // eax
  int v3; // ecx

  result = (uint32_t *)sub_4373D0(&pszArg1);
  v3 = pArg2[1];
  *result = *pArg2;
  result[1] = v3;
  return result;
}



// ------------------------------------------------------------
// 0x4373D0 sub_4373D0
// ------------------------------------------------------------
int */*thiscall*/ sub_4373D0(uint32_t *this, int *pDwArg2)
{
  int *pDwArg22; // edi
  int *v4; // eax
  int v5; // edi
  uint32_t v7[3]; // [esp+8h] [ebp-Ch] BYREF

  pDwArg22 = pDwArg2;
  v4 = sub_437190(this, pDwArg2);
  if ( v4 == (int *)*(this + 1) || *pDwArg22 < v4[3] )
  {
    v5 = *pDwArg22;
    v7[2] = 0;
    v7[1] = 2;
    v7[0] = v5;
    v4 = *(int **)sub_437420(&pDwArg2, v4, v7);
  }
  return v4 + 4;
}



// ------------------------------------------------------------
// 0x437420 sub_437420
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_437420(uint32_t *this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *uArg4)
{
  int fld_e2; // eax
  uint32_t *fld_e1; // eax
  int v8; // eax
  int v9; // ecx
  char v10[8]; // [esp+8h] [ebp-Ch] BYREF
  uint32_t *fld_e12; // [esp+10h] [ebp-4h] BYREF

  fld_e2 = *(this + 2);
  fld_e12 = nullptr;
  if ( fld_e2 == 0 )
  {
    sub_437590(uArg2, 1, *(this + 1), uArg4);
    return uArg2;
  }
  fld_e1 = (uint32_t *)*(this + 1);
  if ( pArg3 == (uint32_t *)*fld_e1 )
  {
    if ( *uArg4 < pArg3[3] )
    {
      sub_437590(uArg2, 1, pArg3, uArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_e1 )
  {
    v8 = fld_e1[2];
    if ( *(uint32_t *)(v8 + 12) < *uArg4 )
    {
      sub_437590(uArg2, 0, v8, uArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *uArg4 >= pArg3[3] || (fld_e12 = pArg3, sub_4B0CC0(&fld_e12), fld_e12[3] >= *uArg4) )
  {
    if ( pArg3[3] >= *uArg4 || (fld_e12 = pArg3, sub_4B0C60(&fld_e12), fld_e12 != (uint32_t *)*(this + 1)) && *uArg4 >= fld_e12[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_437790(v10, uArg4);
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 25) != 0 )
      sub_437590(uArg2, 0, pArg3, uArg4);
    else
      sub_437590(uArg2, 1, fld_e12, uArg4);
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(fld_e12[2] + 25) != 0 )
      sub_437590(uArg2, 0, fld_e12, uArg4);
    else
      sub_437590(uArg2, 1, pArg3, uArg4);
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x437590 sub_437590
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_437590(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)
{
  int fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
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

  if ( *(this + 2) >= 0x15555554u )
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
  fld_e1 = sub_437740(*(this + 1), pArg4, *(this + 1), nArg5, 0);
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
  v10 = (uint32_t *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 24) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 24) != 0 )
        {
          if ( fld_e16 == v12[2] )
          {
            fld_e16 = *v10;
            sub_4B0FD0(*v10);
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 24) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 24) = 0;
          sub_4B0C00(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 24) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4B0C00(*v10);
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 24) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 24) = 0;
        sub_4B0FD0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 24) = 1;
      *(uint8_t *)(v14 + 24) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 24) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 24) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 24) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x437740 sub_437740
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_437740(int nArg1, int nArg2, int nArg3, uint32_t *pArg4, char pszArg5)
{
  uint32_t *result; // eax

  result = operator new(0x1Cu);
  if ( result != nullptr )
  {
    *result = nArg1;
    result[1] = nArg2;
    result[2] = nArg3;
    result[3] = *pArg4;
    result[4] = pArg4[1];
    result[5] = pArg4[2];
    *((uint8_t *)result + 24) = pszArg5;
    *((uint8_t *)result + 25) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x437790 sub_437790
// ------------------------------------------------------------
int /*thiscall*/ sub_437790(uint32_t *this, int pArg2, uint32_t *uArg3)
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
  if ( *((uint8_t *)v6 + 25) == 0 )
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
    while ( *((uint8_t *)v6 + 25) == 0 );
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_437590(this, &uArg3, 1, fld_e1, (int)uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4B0CC0(&uArg3);
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
    v12 = *sub_437590(this, &uArg3, v13, fld_e1, (int)uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x437850 sub_437850
// ------------------------------------------------------------
void /*thiscall*/ sub_437850(int this)
{
  int *v2; // [esp-8h] [ebp-28h]
  int *fld_24; // [esp-4h] [ebp-24h]
  int *v4[2]; // [esp+Ch] [ebp-14h] BYREF
  int v5; // [esp+1Ch] [ebp-4h]

  v4[1] = (int *)this;
  *(uint32_t *)this = &vftbl_CNCommandChecker;
  v5 = 4;
  nullsub_3();
  sub_6569D0(this + 80);
  j__free(*(void **)(this + 84));
  *(uint32_t *)(this + 84) = 0;
  sub_6569D0(this + 68);
  j__free(*(void **)(this + 72));
  *(uint32_t *)(this + 72) = 0;
  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  fld_24 = *(int **)(this + 36);
  v2 = (int *)*fld_24;
  LOBYTE(v5) = 0;
  sub_434CB0((int ***)(this + 32), v4, v2, fld_24);
  j__free(*(void **)(this + 36));
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 4) = &vftbl_nengine__IObject;
}



// ------------------------------------------------------------
// 0x437920 CNCommandChecker__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNCommandChecker__vmt0(void *Block, char pszArg2)
{
  sub_437850((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x437950 sub_437950
// ------------------------------------------------------------
int /*thiscall*/ sub_437950(int this)
{
  if ( *(uint32_t *)(this + 20) != 0 )
    j__free(*(void **)(this + 20));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  return sub_435850(this);
}



// ------------------------------------------------------------
// 0x437980 sub_437980
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_437980(int *this)
{
  return sub_436840(this);
}



// ------------------------------------------------------------
// 0x437990 sub_437990
// ------------------------------------------------------------
int */*thiscall*/ sub_437990(int **this, int *pDwArg2, int nArg3, int nArg4)
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
    sub_435BA0(*(void ***)(fld_e1 + 4));
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
        if ( *(uint8_t *)(nArg32 + 33) == 0 )
        {
          v11 = *(uint32_t *)(nArg32 + 8);
          if ( *(uint8_t *)(v11 + 33) != 0 )
          {
            for ( i = *(uint32_t *)(nArg32 + 4); *(uint8_t *)(i + 33) == 0; i = *(uint32_t *)(i + 4) )
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
            for ( j = *(uint32_t *)v11; *(uint8_t *)(j + 33) == 0; j = *(uint32_t *)j )
              nArg32 = j;
          }
        }
        sub_4358C0(this, &nArg3, nArg322);
      }
      while ( nArg32 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x437A50 sub_437A50
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_437A50(uint32_t *pArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg32 = uArg3;
  v6[4] = v6;
  v6[3] = uArg3;
  v7 = 0;
  while ( pArg1 != uArg2 )
  {
    LOBYTE(v7) = 1;
    if ( uArg32 != nullptr )
    {
      sub_435020(uArg32, pArg1);
      uArg32[4] = pArg1[4];
      uArg32[5] = pArg1[5];
    }
    uArg32 += 6;
    LOBYTE(v7) = 0;
    pArg1 += 6;
  }
  return uArg32;
}



// ============================================================
// §26 资源加载器与全局数据总装（0x437B00-0x43B4C0）
//   IFileResourceManager·CNScriptLoader·CNAnimationLoader·CNRDQuestModule·
//   CNPvpRoomManager；0x439AB0 = 全局数据总装（.lst/.tbl 数据表族，被引导 0x420DA0 调用）
// ============================================================
// ------------------------------------------------------------
// 0x437B00 sub_437B00
// ------------------------------------------------------------
int /*fastcall*/ sub_437B00(unsigned int pArg1, int nArg2)
{
  int v3; // edx
  int v4; // edx
  int v5; // edx
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // edx
  int v14; // edx
  int v15; // edx
  int v16; // edx
  int v17; // edx
  int v18; // edx
  int v19; // edx
  int v20; // edx
  int v21; // edx
  int v22; // edx
  int v23; // edx
  unsigned int v24; // ebx
  int i; // edi
  int v26; // edx
  unsigned int v27; // ebx
  int j; // edi
  int v29; // edx
  int v30; // edx
  int v31; // edx
  int v32; // edx
  int v33; // edx
  int v34; // edx
  int v35; // edx
  int v36; // edx
  int v37; // edx
  int v38; // edx
  int v39; // edx
  int v40; // edx
  int v41; // edx
  int v42; // edx
  int v43; // edx
  unsigned int v44; // ebx
  int k; // edi
  unsigned int v46; // ebx
  char *v47; // edi
  int v48; // ebx
  int n; // edi
  char *v51; // [esp+Ch] [ebp-8h]
  int m; // [esp+10h] [ebp-4h]

  sub_41A590(pArg1, nArg2, 2);
  sub_41A590(pArg1 + 14, v3, 0);
  sub_41A590(pArg1 + 28, v4, 0);
  sub_41A590(pArg1 + 42, v5, 0);
  sub_41A590(pArg1 + 56, v6, 0);
  sub_41A590(pArg1 + 70, v7, 0);
  sub_41A590(pArg1 + 98, v8, 0);
  sub_41A590(pArg1 + 112, v9, 0);
  sub_41A590(pArg1 + 126, v10, 0);
  sub_41A590(pArg1 + 140, v11, 0);
  sub_41A590(pArg1 + 154, v12, 0);
  sub_41A590(pArg1 + 168, v13, 0);
  sub_41A590(pArg1 + 182, v14, 0);
  sub_41A590(pArg1 + 196, v15, 0);
  sub_41A590(pArg1 + 210, v16, 0);
  sub_41A590(pArg1 + 224, v17, 0);
  sub_41A590(pArg1 + 238, v18, 0);
  sub_41A590(pArg1 + 252, v19, 0);
  sub_41A590(pArg1 + 266, v20, 0);
  sub_41A590(pArg1 + 280, v21, 0);
  sub_41A590(pArg1 + 294, v22, 0);
  v24 = pArg1 + 308;
  for ( i = 4; i != 0; --i )
  {
    sub_41A590(v24, v23, 0);
    v24 += 14;
  }
  sub_41A590(pArg1 + 364, v23, 0);
  v27 = pArg1 + 378;
  for ( j = 16; j != 0; --j )
  {
    sub_41A590(v27, v26, 0);
    v27 += 14;
  }
  sub_41A590(pArg1 + 602, v26, 0);
  sub_41A590(pArg1 + 616, v29, 0);
  sub_41A590(pArg1 + 630, v30, 0);
  sub_41A590(pArg1 + 644, v31, 0);
  sub_41A590(pArg1 + 658, 0, 0);
  sub_41A590(pArg1 + 672, v32, 0);
  sub_41A590(pArg1 + 686, v33, 0);
  sub_41A590(pArg1 + 700, v34, 0);
  sub_41A590(pArg1 + 714, v35, 0);
  sub_41A590(pArg1 + 728, v36, 0);
  sub_41A590(pArg1 + 742, v37, 0);
  sub_41A590(pArg1 + 756, v38, 0);
  *(uint32_t *)(pArg1 + 772) = 4;
  *(uint32_t *)(pArg1 + 776) = 17;
  sub_41A590(pArg1 + 780, 0, 0);
  sub_41A590(pArg1 + 794, v39, 0);
  sub_41A590(pArg1 + 808, v40, 0);
  sub_41A590(pArg1 + 822, v41, 0);
  sub_41A590(pArg1 + 836, v42, 0);
  *(uint8_t *)(pArg1 + 850) = 0;
  v44 = pArg1 + 851;
  for ( k = 2; k != 0; --k )
  {
    sub_41A590(v44, v43, 0);
    v44 += 14;
  }
  *(uint8_t *)(pArg1 + 879) = 0;
  *(uint8_t *)(pArg1 + 880) = 0;
  v46 = pArg1 + 888;
  for ( m = 2; m != 0; --m )
  {
    if ( *(uint32_t *)v46 != 0 )
    {
      v47 = *(char **)v46;
      v51 = *(char **)(v46 + 4);
      if ( *(char **)v46 != v51 )
      {
        do
        {
          sub_432DC0(v47);
          v47 += 32;
        }
        while ( v47 != v51 );
      }
      j__free(*(void **)v46);
    }
    *(uint32_t *)v46 = 0;
    *(uint32_t *)(v46 + 4) = 0;
    *(uint32_t *)(v46 + 8) = 0;
    v46 += 16;
  }
  v48 = *(uint32_t *)(pArg1 + 920);
  if ( v48 != 0 )
  {
    for ( n = *(uint32_t *)(pArg1 + 924); v48 != n; v48 += 80 )
      sub_433D10(v48);
    j__free(*(void **)(pArg1 + 920));
  }
  *(uint32_t *)(pArg1 + 920) = 0;
  *(uint32_t *)(pArg1 + 924) = 0;
  *(uint32_t *)(pArg1 + 928) = 0;
  return sub_41A590(pArg1 + 932, v43, -1);
}


// ------------------------------------------------------------
// 0x437E70 sub_437E70
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_437E70(uint32_t *this)
{
  int v2; // edx

  sub_41A630((unsigned int)this);
  *this = &vftbl_clong;
  sub_41A630((unsigned int)this + 14);
  *(uint32_t *)((char *)this + 14) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 7));
  *(this + 7) = &vftbl_clong;
  sub_41A630((unsigned int)this + 42);
  *(uint32_t *)((char *)this + 42) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 14));
  *(this + 14) = &vftbl_clong;
  sub_41A630((unsigned int)this + 70);
  *(uint32_t *)((char *)this + 70) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 21));
  *(this + 21) = &vftbl_clong;
  sub_41A630((unsigned int)this + 98);
  *(uint32_t *)((char *)this + 98) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 28));
  *(this + 28) = &vftbl_clong;
  sub_41A630((unsigned int)this + 126);
  *(uint32_t *)((char *)this + 126) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 35));
  *(this + 35) = &vftbl_clong;
  sub_41A630((unsigned int)this + 154);
  *(uint32_t *)((char *)this + 154) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 42));
  *(this + 42) = &vftbl_clong;
  sub_41A630((unsigned int)this + 182);
  *(uint32_t *)((char *)this + 182) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 49));
  *(this + 49) = &vftbl_clong;
  sub_41A630((unsigned int)this + 210);
  *(uint32_t *)((char *)this + 210) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 56));
  *(this + 56) = &vftbl_clong;
  sub_41A630((unsigned int)this + 238);
  *(uint32_t *)((char *)this + 238) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 63));
  *(this + 63) = &vftbl_cfloat;
  sub_41A630((unsigned int)this + 266);
  *(uint32_t *)((char *)this + 266) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 70));
  *(this + 70) = &vftbl_clong;
  sub_41A630((unsigned int)this + 294);
  *(uint32_t *)((char *)this + 294) = &vftbl_cfloat;
  `eh vector constructor iterator'(this + 77, 0xEu, 4, sub_401040, sub_432D10);
  sub_41A630((unsigned int)(this + 91));
  *(this + 91) = &vftbl_clong;
  `eh vector constructor iterator'((char *)this + 378, 0xEu, 16, sub_401040, sub_432D10);
  sub_41A630((unsigned int)this + 602);
  *(uint32_t *)((char *)this + 602) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 154));
  *(this + 154) = &vftbl_clong;
  sub_41A630((unsigned int)this + 630);
  *(uint32_t *)((char *)this + 630) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 161));
  *(this + 161) = &vftbl_clong;
  sub_41A630((unsigned int)this + 658);
  *(uint32_t *)((char *)this + 658) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 168));
  *(this + 168) = &vftbl_clong;
  sub_41A630((unsigned int)this + 686);
  *(uint32_t *)((char *)this + 686) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 175));
  *(this + 175) = &vftbl_clong;
  sub_41A630((unsigned int)this + 714);
  *(uint32_t *)((char *)this + 714) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 182));
  *(this + 182) = &vftbl_clong;
  sub_41A630((unsigned int)this + 742);
  *(uint32_t *)((char *)this + 742) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 189));
  *(this + 189) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 195));
  *(this + 195) = &vftbl_cfloat;
  sub_41A630((unsigned int)this + 794);
  *(uint32_t *)((char *)this + 794) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 202));
  *(this + 202) = &vftbl_clong;
  sub_41A630((unsigned int)this + 822);
  *(uint32_t *)((char *)this + 822) = &vftbl_clong;
  sub_41A630((unsigned int)(this + 209));
  *(this + 209) = &vftbl_cfloat;
  `eh vector constructor iterator'((char *)this + 851, 0xEu, 2, (void (/*thiscall*/ *)(void *))sub_432CD0, sub_432D10);
  `eh vector constructor iterator'(this + 221, 0x10u, 2, sub_4019A0, sub_434940);
  *(this + 230) = 0;
  *(this + 231) = 0;
  *(this + 232) = 0;
  sub_41A630((unsigned int)(this + 233));
  *(this + 233) = &vftbl_clong;
  sub_437B00((unsigned int)this, v2);
  return this;
}



// ------------------------------------------------------------
// 0x4382D0 sub_4382D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4382D0(int *this)
{
  sub_41A580(this + 233);
  sub_436840(this + 229);
  `eh vector destructor iterator'(this + 221, 0x10u, 2, sub_434940);
  `eh vector destructor iterator'((char *)this + 851, 0xEu, 2, sub_432D10);
  sub_41A580(this + 209);
  sub_41A580((char *)this + 822);
  sub_41A580(this + 202);
  sub_41A580((char *)this + 794);
  sub_41A580(this + 195);
  sub_41A580(this + 189);
  sub_41A580((char *)this + 742);
  sub_41A580(this + 182);
  sub_41A580((char *)this + 714);
  sub_41A580(this + 175);
  sub_41A580((char *)this + 686);
  sub_41A580(this + 168);
  sub_41A580((char *)this + 658);
  sub_41A580(this + 161);
  sub_41A580((char *)this + 630);
  sub_41A580(this + 154);
  sub_41A580((char *)this + 602);
  `eh vector destructor iterator'((char *)this + 378, 0xEu, 16, sub_432D10);
  sub_41A580(this + 91);
  `eh vector destructor iterator'(this + 77, 0xEu, 4, sub_432D10);
  sub_41A580((char *)this + 294);
  sub_41A580(this + 70);
  sub_41A580((char *)this + 266);
  sub_41A580(this + 63);
  sub_41A580((char *)this + 238);
  sub_41A580(this + 56);
  sub_41A580((char *)this + 210);
  sub_41A580(this + 49);
  sub_41A580((char *)this + 182);
  sub_41A580(this + 42);
  sub_41A580((char *)this + 154);
  sub_41A580(this + 35);
  sub_41A580((char *)this + 126);
  sub_41A580(this + 28);
  sub_41A580((char *)this + 98);
  sub_41A580(this + 21);
  sub_41A580((char *)this + 70);
  sub_41A580(this + 14);
  sub_41A580((char *)this + 42);
  sub_41A580(this + 7);
  sub_41A580((char *)this + 14);
  return sub_41A580(this);
}



// ------------------------------------------------------------
// 0x4385C0 sub_4385C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4385C0(uint32_t *this)
{
  char *pThis; // edx
  int i; // ebx
  void *pBuf; // edi

  pThis = (char *)this;
  for ( i = 8; i != 0; --i )
  {
    memset(pThis, 0, 0x30u);
    pBuf = pThis + 48;
    pThis += 96;
    memset(pBuf, 0, 0x30u);
  }
  memset(this + 192, 0, 0x30u);
  memset(this + 204, 0, 0x30u);
  sub_41A630((unsigned int)(this + 216));
  *(this + 216) = &vftbl_clong;
  sub_41A630((unsigned int)this + 878);
  *(uint32_t *)((char *)this + 878) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 223));
  *(this + 223) = &vftbl_cfloat;
  sub_41A630((unsigned int)this + 906);
  *(uint32_t *)((char *)this + 906) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 230));
  *(this + 230) = &vftbl_cfloat;
  sub_41A630((unsigned int)this + 934);
  *(uint32_t *)((char *)this + 934) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 237));
  *(this + 237) = &vftbl_cfloat;
  sub_41A630((unsigned int)(this + 244));
  *(this + 244) = &vftbl_cfloat;
  sub_41A630((unsigned int)this + 990);
  *(uint32_t *)((char *)this + 990) = &vftbl_cfloat;
  *(this + 253) = 0;
  *(this + 254) = 0;
  *(this + 255) = 0;
  *(this + 257) = 0;
  *(this + 258) = 0;
  *(this + 259) = 0;
  sub_4968E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x438740 sub_438740
// ------------------------------------------------------------
int /*thiscall*/ sub_438740(char *this)
{
  sub_55A050(this + 1024);
  sub_55A050(this + 1008);
  sub_41A580(this + 990);
  sub_41A580(this + 976);
  sub_41A580(this + 948);
  sub_41A580(this + 934);
  sub_41A580(this + 920);
  sub_41A580(this + 906);
  sub_41A580(this + 892);
  sub_41A580(this + 878);
  return sub_41A580(this + 864);
}



// ------------------------------------------------------------
// 0x438820 sub_438820
// ------------------------------------------------------------
int */*thiscall*/ sub_438820(int **this, int *pDwArg2, int nArg3, int nArg4)
{
  int nArg42; // ebx
  int fld_e1; // eax
  int nArg32; // ecx
  uint32_t *fld_e12; // eax
  int nArg322; // edi

  nArg42 = nArg4;
  fld_e1 = (int)*(this + 1);
  nArg32 = nArg3;
  if ( nArg3 == *(uint32_t *)fld_e1 && nArg4 == fld_e1 )
  {
    sub_436CA0(*(void ***)(fld_e1 + 4));
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
        sub_4332F0(&nArg3);
        sub_436940(this, &nArg4, nArg322);
        nArg32 = nArg3;
      }
      while ( nArg3 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4388A0 sub_4388A0
// ------------------------------------------------------------
void /*stdcall*/ sub_4388A0(void **pArg1, void **pArg2)
{
  void **i; // esi

  for ( i = pArg1; i != pArg2; i += 31 )
    sub_4347B0(i);
}



// ------------------------------------------------------------
// 0x4388D0 sub_4388D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4388D0(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_436880((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x438910 sub_438910
// ------------------------------------------------------------
// 【资源回收】被关停清理链 0x420070 调用。
void sub_438910()
{
  void *dword_99FD582; // esi
  void *dword_8F851C2; // esi
  void *dword_8F85242; // esi
  void *dword_8F85282; // esi
  void *dword_8F852C2; // esi
  void *dword_8F85302; // esi
  void *dword_8F85342; // esi
  void *dword_8F853C2; // esi
  int *dword_8F82702; // esi
  LPCRITICAL_SECTION v9; // esi

  if ( dword_8F84B4 != nullptr )
    j__free(dword_8F84B4);
  dword_8F84B4 = nullptr;
  if ( dword_8F84B8 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84B8)(dword_8F84B8, 1);
  dword_8F84B8 = 0;
  if ( dword_8F84BC != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84BC)(dword_8F84BC, 1);
  dword_8F84BC = 0;
  if ( dword_8F84C0 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84C0)(dword_8F84C0, 1);
  dword_8F84C0 = 0;
  if ( dword_8F84C4 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84C4)(dword_8F84C4, 1);
  dword_8F84C4 = 0;
  if ( dword_8F84C8 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84C8)(dword_8F84C8, 1);
  dword_8F84C8 = 0;
  if ( dword_8F84CC != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84CC)(dword_8F84CC, 1);
  dword_8F84CC = 0;
  if ( dword_8F84D0 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84D0)(dword_8F84D0, 1);
  dword_8F84D0 = 0;
  if ( dword_8F84D4 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84D4)(dword_8F84D4, 1);
  dword_8F84D4 = 0;
  if ( dword_8F84D8 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84D8)(dword_8F84D8, 1);
  dword_8F84D8 = 0;
  if ( dword_8F84DC != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84DC)(dword_8F84DC, 1);
  dword_8F84DC = 0;
  if ( dword_8F84E0 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84E0)(dword_8F84E0, 1);
  dword_8F84E0 = 0;
  if ( dword_8F84E4 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84E4)(dword_8F84E4, 1);
  dword_8F84E4 = 0;
  if ( dword_8F84E8 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84E8)(dword_8F84E8, 1);
  dword_8F84E8 = 0;
  if ( dword_8F84EC != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84EC)(dword_8F84EC, 1);
  dword_8F84EC = 0;
  if ( dword_8F84F0 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84F0)(dword_8F84F0, 1);
  dword_8F84F0 = 0;
  if ( dword_8F84F4 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84F4)(dword_8F84F4, 1);
  dword_8F84F4 = 0;
  if ( dword_8F84F8 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84F8)(dword_8F84F8, 1);
  dword_8F84F8 = 0;
  if ( dword_8F84FC != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F84FC)(dword_8F84FC, 1);
  dword_8F84FC = 0;
  if ( dword_99FD58 != nullptr )
  {
    dword_99FD582 = dword_99FD58;
    sub_438740((char *)dword_99FD58);
    j__free(dword_99FD582);
  }
  dword_99FD58 = nullptr;
  if ( dword_8F8500 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8500)(dword_8F8500, 1);
  dword_8F8500 = 0;
  if ( dword_8F8504 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8504)(dword_8F8504, 1);
  dword_8F8504 = 0;
  if ( dword_8F8508 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8508)(dword_8F8508, 1);
  dword_8F8508 = 0;
  if ( dword_8F850C != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F850C)(dword_8F850C, 1);
  dword_8F850C = 0;
  if ( dword_8F8510 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8510)(dword_8F8510, 1);
  dword_8F8510 = 0;
  if ( dword_8F8514 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8514)(dword_8F8514, 1);
  dword_8F8514 = 0;
  if ( dword_8F851C != nullptr )
  {
    dword_8F851C2 = dword_8F851C;
    sub_4BF080(dword_8F851C);
    j__free(dword_8F851C2);
  }
  dword_8F851C = nullptr;
  if ( dword_8F8518 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8518)(dword_8F8518, 1);
  dword_8F8518 = 0;
  sub_475EF0();
  sub_47EC40();
  if ( dword_8F8520 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 4))(dword_8F8520, 1);
  dword_8F8520 = 0;
  if ( dword_8F8524 != nullptr )
  {
    dword_8F85242 = dword_8F8524;
    sub_433420();
    j__free(dword_8F85242);
  }
  dword_8F8524 = nullptr;
  if ( dword_8F8528 != nullptr )
  {
    dword_8F85282 = dword_8F8528;
    sub_434050((char *)dword_8F8528);
    j__free(dword_8F85282);
  }
  dword_8F8528 = nullptr;
  if ( dword_8F852C != nullptr )
  {
    dword_8F852C2 = dword_8F852C;
    sub_433E30((int)dword_8F852C);
    j__free(dword_8F852C2);
  }
  dword_8F852C = nullptr;
  if ( dword_8F8530 != nullptr )
  {
    dword_8F85302 = dword_8F8530;
    sub_433E30((int)dword_8F8530);
    j__free(dword_8F85302);
  }
  dword_8F8530 = nullptr;
  if ( dword_8F8534 != nullptr )
  {
    dword_8F85342 = dword_8F8534;
    sub_433E30((int)dword_8F8534);
    j__free(dword_8F85342);
  }
  dword_8F8534 = nullptr;
  if ( dword_8F8538 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8538)(dword_8F8538, 1);
  dword_8F8538 = 0;
  if ( dword_8F853C != nullptr )
  {
    dword_8F853C2 = dword_8F853C;
    sub_483CD0();
    j__free(dword_8F853C2);
  }
  dword_8F853C = nullptr;
  if ( dword_8F8540 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8540)(dword_8F8540, 1);
  dword_8F8540 = 0;
  if ( dword_8F8544 != 0 )
    (**(void (/*thiscall*/ ***)(int, int))dword_8F8544)(dword_8F8544, 1);
  dword_8F8544 = 0;
  dword_8F82702 = dword_8F8270;
  do
  {
    if ( *dword_8F82702 != 0 )
      (**(void (/*thiscall*/ ***)(int, int))*dword_8F82702)(*dword_8F82702, 1);
    *dword_8F82702++ = 0;
  }
  while ( (int)dword_8F82702 < (int)&dword_8F831C );
  sub_4AEDB0();
  sub_431AA0();
  sub_4F2BC0();
  v9 = lpCriticalSection;
  if ( lpCriticalSection != nullptr )
  {
    sub_65FC70(lpCriticalSection);
    j__free(v9);
  }
  DeleteCriticalSection(&stru_8F8258);
}


// ------------------------------------------------------------
// 0x438D10 sub_438D10
// ------------------------------------------------------------
int /*thiscall*/ sub_438D10(int this)
{
  void **fld_4; // esi
  int result; // eax
  void **i; // edi

  fld_4 = *(void ***)(this + 4);
  result = 0;
  if ( fld_4 != nullptr )
  {
    for ( i = *(void ***)(this + 8); fld_4 != i; fld_4 += 31 )
      sub_4347B0(fld_4);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x438D50 sub_438D50
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_438D50(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  return sub_437A50(uArg1, uArg2, uArg3);
}



// ------------------------------------------------------------
// 0x438D70 sub_438D70
// ------------------------------------------------------------
int /*thiscall*/ sub_438D70(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_437990((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x438DB0 sub_438DB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_438DB0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  uint32_t *pThis_43; // esi
  uint32_t *v6; // eax

  pThis_43 = this + 67;
  *this = &vftbl_IFileResourceManager;
  v6 = sub_433B80();
  pThis_43[1] = v6;
  *((uint8_t *)v6 + 45) = 1;
  *(uint32_t *)(pThis_43[1] + 4) = pThis_43[1];
  *(uint32_t *)pThis_43[1] = pThis_43[1];
  *(uint32_t *)(pThis_43[1] + 8) = pThis_43[1];
  pThis_43[2] = 0;
  IFileResourceManager__vmt20(this);
  IFileResourceManager__vmt24(nArg2, nArg3, nArg4);
  return this;
}



// ------------------------------------------------------------
// 0x438E40 IFileResourceManager__vmt4
// ------------------------------------------------------------
int /*thiscall*/ IFileResourceManager__vmt4(void *this, int nArg2)
{
  return (*(int (/*thiscall*/ **)(void *, uint32_t, int))(*(uint32_t *)this + 8))(this, 0, nArg2);
}



// ------------------------------------------------------------
// 0x438E60 IFileResourceManager__vmt1C
// ------------------------------------------------------------
char /*thiscall*/ IFileResourceManager__vmt1C(uint8_t *this, char pszArg2)
{
  *(this + 280) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x438E70 IFileResourceManager__vmt14
// ------------------------------------------------------------
int /*thiscall*/ IFileResourceManager__vmt14(uint32_t *this)
{
  int result; // eax

  for ( result = *(this + 69); result != 0; result = *(this + 69) )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 44))(this, *(uint32_t *)*(this + 68));
  return result;
}



// ------------------------------------------------------------
// 0x438EA0 sub_438EA0
// ------------------------------------------------------------
void /*thiscall*/ sub_438EA0(int **this)
{
  int **pThis; // esi
  int *v2; // eax
  int v3; // [esp-8h] [ebp-1Ch]
  int **pThis2; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  pThis = this;
  pThis2 = this;
  *this = (int *)&vftbl_IFileResourceManager;
  v5 = 0;
  IFileResourceManager__vmt28();
  v2 = pThis[68];
  pThis += 67;
  v3 = *v2;
  v5 = -1;
  sub_436880(pThis, (int *)&pThis2, v3, (int)v2);
  j__free(pThis[1]);
  pThis[1] = nullptr;
  pThis[2] = nullptr;
}



// ------------------------------------------------------------
// 0x438F20 IFileResourceManager__vmt0
// ------------------------------------------------------------
int **/*thiscall*/ IFileResourceManager__vmt0(int **Block, char pszArg2)
{
  sub_438EA0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x438F50 CNScriptLoader__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNScriptLoader__vmt0(void *Block, char pszArg2)
{
  sub_438F80();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x438F80 sub_438F80
// ------------------------------------------------------------
void /*thiscall*/ sub_438F80(int **this)
{
  *this = (int *)&vftbl_CNScriptLoader;
  IFileResourceManager__vmt28();
  sub_438EA0(this);
}



// ------------------------------------------------------------
// 0x438FD0 CNAnimationLoader__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNAnimationLoader__vmt0(void *Block, char pszArg2)
{
  sub_439000();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x439000 sub_439000
// ------------------------------------------------------------
void /*thiscall*/ sub_439000(int **this)
{
  *this = (int *)&vftbl_CNAnimationLoader;
  IFileResourceManager__vmt28();
  sub_438EA0(this);
}



// ------------------------------------------------------------
// 0x439050 sub_439050
// ------------------------------------------------------------
int /*thiscall*/ sub_439050(int this, uint32_t *pArg2)
{
  int v4; // eax
  unsigned int v5; // ecx
  void **fld_4; // edi
  unsigned int fld_8; // eax
  void **v9; // eax
  int v10; // eax
  int fld_42; // ecx
  unsigned int fld_C; // eax
  unsigned int v13; // eax
  uint32_t *v14; // [esp+10h] [ebp+8h]

  if ( (uint32_t *)this == pArg2 )
    return this;
  v4 = pArg2[1];
  if ( v4 == 0 || (v5 = (pArg2[2] - v4) / 24) == 0 )
  {
    sub_435850(this);
    return this;
  }
  fld_4 = *(void ***)(this + 4);
  if ( fld_4 != nullptr )
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 24;
  else
    fld_8 = 0;
  if ( v5 > fld_8 )
  {
    if ( fld_4 != nullptr )
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 24;
    else
      fld_C = 0;
    if ( v5 <= fld_C )
    {
      v14 = (uint32_t *)(pArg2[1] + 24 * sub_4FEF30(this));
      sub_436CF0(pArg2[1], (int)v14, (int)fld_4);
      *(uint32_t *)(this + 8) = sub_437A50(v14, (uint32_t *)pArg2[2], *(uint32_t **)(this + 8));
      return this;
    }
    if ( fld_4 != nullptr )
    {
      sub_435820(fld_4, *(void ***)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v13 = sub_4FEF30(pArg2);
    if ( sub_434950((uint32_t *)this, v13) != 0 )
      *(uint32_t *)(this + 8) = sub_438D50((uint32_t *)pArg2[1], (uint32_t *)pArg2[2], *(uint32_t **)(this + 4));
    return this;
  }
  v9 = (void **)sub_435BF0(pArg2[1], pArg2[2], (int)fld_4);
  sub_435820(v9, *(void ***)(this + 8));
  v10 = pArg2[1];
  if ( v10 != 0 )
    fld_42 = *(uint32_t *)(this + 4) + 24 * ((pArg2[2] - v10) / 24);
  else
    fld_42 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 8) = fld_42;
  return this;
}



// ------------------------------------------------------------
// 0x4391E0 sub_4391E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4391E0(int this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_438820((int **)this, &v3, **(uint32_t **)(this + 4), *(uint32_t *)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x439220 sub_439220
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_439220(uint32_t *this)
{
  uint32_t *pThis_9; // edi
  uint32_t *v3; // eax
  uint32_t *v4; // eax

  *this = &vftbl_CNRDQuestModule;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  pThis_9 = this + 9;
  v3 = sub_433B40();
  pThis_9[1] = v3;
  *((uint8_t *)v3 + 33) = 1;
  *(uint32_t *)(pThis_9[1] + 4) = pThis_9[1];
  *(uint32_t *)pThis_9[1] = pThis_9[1];
  *(uint32_t *)(pThis_9[1] + 8) = pThis_9[1];
  pThis_9[2] = 0;
  v4 = sub_433AC0();
  *(this + 13) = v4;
  *((uint8_t *)v4 + 21) = 1;
  *(uint32_t *)(*(this + 13) + 4) = *(this + 13);
  *(uint32_t *)*(this + 13) = *(this + 13);
  *(uint32_t *)(*(this + 13) + 8) = *(this + 13);
  *(this + 14) = 0;
  nullsub_3();
  nullsub_3();
  return this;
}



// ------------------------------------------------------------
// 0x4392E0 CNRDQuestModule__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNRDQuestModule__vmt0(void *Block, char pszArg2)
{
  sub_439310();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x439310 sub_439310
// ------------------------------------------------------------
int /*thiscall*/ sub_439310(int this)
{
  int v3; // [esp-8h] [ebp-28h]
  int v4; // [esp-8h] [ebp-28h]
  int *fld_34; // [esp-4h] [ebp-24h]
  int *fld_28; // [esp-4h] [ebp-24h]
  int v7[2]; // [esp+Ch] [ebp-14h] BYREF
  int v8; // [esp+1Ch] [ebp-4h]

  v7[1] = this;
  *(uint32_t *)this = &vftbl_CNRDQuestModule;
  v8 = 3;
  nullsub_3();
  fld_34 = *(int **)(this + 52);
  v3 = *fld_34;
  LOBYTE(v8) = 2;
  sub_41D980(v7, v3, fld_34);
  j__free(*(void **)(this + 52));
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  fld_28 = *(int **)(this + 40);
  v4 = *fld_28;
  LOBYTE(v8) = 1;
  sub_437990((int **)(this + 36), v7, v4, (int)fld_28);
  j__free(*(void **)(this + 40));
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  if ( *(uint32_t *)(this + 24) != 0 )
    j__free(*(void **)(this + 24));
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  v8 = -1;
  return sub_4349A0((int *)(this + 4));
}



// ------------------------------------------------------------
// 0x4393E0 sub_4393E0
// ------------------------------------------------------------
void /*thiscall*/ sub_4393E0(char *this)
{
  void **pThis_14; // eax
  void **pThis_142; // edi
  int pThis_108; // eax
  int pThis_1082; // edi
  void **pThis_10D; // eax
  void **pThis_10D2; // edi
  void **pThis_20C; // eax
  void **pThis_20C2; // edi
  void **pThis_15; // [esp+Ch] [ebp-4h]
  int pThis_109; // [esp+Ch] [ebp-4h]
  void **pThis_10E; // [esp+Ch] [ebp-4h]
  void **pThis_20D; // [esp+Ch] [ebp-4h]

  *(uint32_t *)this = 0;
  sub_41BFE0((void **)this + 530, szPassword);
  sub_41BFE0((void **)this + 531, szPassword);
  sub_41BFE0((void **)this + 532, szPassword);
  sub_41BFE0((void **)this + 533, szPassword);
  sub_41BFE0((void **)this + 534, szPassword);
  sub_41BFE0((void **)this + 276, szPassword);
  *((uint32_t *)this + 1) = 1;
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 9) = -1;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = -1;
  *((uint32_t *)this + 14) = 0;
  sub_41BFE0((void **)this + 15, szPassword);
  *((uint32_t *)this + 16) = 0;
  sub_41BFE0((void **)this + 17, szPassword);
  *((uint32_t *)this + 18) = 0;
  pThis_14 = *((void ***)this + 20);
  if ( pThis_14 != nullptr )
  {
    pThis_142 = *((void ***)this + 20);
    pThis_15 = *((void ***)this + 21);
    if ( pThis_14 != pThis_15 )
    {
      do
        sub_41B010(pThis_142++);
      while ( pThis_142 != pThis_15 );
    }
    j__free(*((void **)this + 20));
  }
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 23) = 18;
  *((uint32_t *)this + 24) = 0;
  *((uint32_t *)this + 25) = 0;
  sub_437B00(this + 104);
  pThis_108 = *((uint32_t *)this + 264);
  if ( pThis_108 != 0 )
  {
    pThis_1082 = *((uint32_t *)this + 264);
    pThis_109 = *((uint32_t *)this + 265);
    if ( pThis_108 != pThis_109 )
    {
      do
      {
        sub_4347B0(pThis_1082);
        pThis_1082 += 124;
      }
      while ( pThis_1082 != pThis_109 );
    }
    j__free(*((void **)this + 264));
  }
  *((uint32_t *)this + 264) = 0;
  *((uint32_t *)this + 265) = 0;
  *((uint32_t *)this + 266) = 0;
  sub_41BFE0((void **)this + 267, szPassword);
  pThis_10D = *((void ***)this + 269);
  if ( pThis_10D != nullptr )
  {
    pThis_10D2 = *((void ***)this + 269);
    pThis_10E = *((void ***)this + 270);
    if ( pThis_10D != pThis_10E )
    {
      do
        sub_41B010(pThis_10D2++);
      while ( pThis_10D2 != pThis_10E );
    }
    j__free(*((void **)this + 269));
  }
  *((uint32_t *)this + 269) = 0;
  *((uint32_t *)this + 270) = 0;
  *((uint32_t *)this + 271) = 0;
  sub_41BFE0((void **)this + 272, szPassword);
  *((uint32_t *)this + 273) = -1;
  *((uint32_t *)this + 274) = -1;
  *(this + 1100) = 0;
  if ( *((uint32_t *)this + 278) != 0 )
    j__free(*((void **)this + 278));
  *((uint32_t *)this + 278) = 0;
  *((uint32_t *)this + 279) = 0;
  *((uint32_t *)this + 280) = 0;
  sub_437B00(this + 1124);
  *((uint32_t *)this + 518) = -1;
  if ( *((uint32_t *)this + 520) != 0 )
    j__free(*((void **)this + 520));
  *((uint32_t *)this + 520) = 0;
  *((uint32_t *)this + 521) = 0;
  *((uint32_t *)this + 522) = 0;
  pThis_20C = *((void ***)this + 524);
  if ( pThis_20C != nullptr )
  {
    pThis_20C2 = *((void ***)this + 524);
    pThis_20D = *((void ***)this + 525);
    if ( pThis_20C != pThis_20D )
    {
      do
        sub_41B010(pThis_20C2++);
      while ( pThis_20C2 != pThis_20D );
    }
    j__free(*((void **)this + 524));
  }
  *((uint32_t *)this + 524) = 0;
  *((uint32_t *)this + 525) = 0;
  *((uint32_t *)this + 526) = 0;
  *((uint32_t *)this + 529) = -1;
  *(this + 2108) = 0;
  *((uint32_t *)this + 528) = 0;
}


// ------------------------------------------------------------
// 0x439680 sub_439680
// ------------------------------------------------------------
int /*thiscall*/ sub_439680(int this)
{
  void **pThis_3C; // ecx

  pThis_3C = (void **)(this + 60);
  *pThis_3C = nullptr;
  sub_41BFE0(pThis_3C, szPassword);
  *(uint32_t *)(this + 68) = 0;
  sub_41BFE0((void **)(this + 68), szPassword);
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  sub_437E70((uint32_t *)(this + 104));
  *(uint32_t *)(this + 1056) = 0;
  *(uint32_t *)(this + 1060) = 0;
  *(uint32_t *)(this + 1064) = 0;
  *(uint32_t *)(this + 1068) = 0;
  sub_41BFE0((void **)(this + 1068), szPassword);
  *(uint32_t *)(this + 1076) = 0;
  *(uint32_t *)(this + 1080) = 0;
  *(uint32_t *)(this + 1084) = 0;
  *(uint32_t *)(this + 1088) = 0;
  sub_41BFE0((void **)(this + 1088), szPassword);
  *(uint32_t *)(this + 1104) = 0;
  sub_41BFE0((void **)(this + 1104), szPassword);
  *(uint32_t *)(this + 1112) = 0;
  *(uint32_t *)(this + 1116) = 0;
  *(uint32_t *)(this + 1120) = 0;
  sub_437E70((uint32_t *)(this + 1124));
  *(uint32_t *)(this + 2080) = 0;
  *(uint32_t *)(this + 2084) = 0;
  *(uint32_t *)(this + 2088) = 0;
  *(uint32_t *)(this + 2096) = 0;
  *(uint32_t *)(this + 2100) = 0;
  *(uint32_t *)(this + 2104) = 0;
  *(uint32_t *)(this + 2120) = 0;
  sub_41BFE0((void **)(this + 2120), szPassword);
  *(uint32_t *)(this + 2124) = 0;
  sub_41BFE0((void **)(this + 2124), szPassword);
  *(uint32_t *)(this + 2128) = 0;
  sub_41BFE0((void **)(this + 2128), szPassword);
  *(uint32_t *)(this + 2132) = 0;
  sub_41BFE0((void **)(this + 2132), szPassword);
  *(uint32_t *)(this + 2136) = 0;
  sub_41BFE0((void **)(this + 2136), szPassword);
  sub_4393E0((void *)this);
  return this;
}



// ------------------------------------------------------------
// 0x439810 sub_439810
// ------------------------------------------------------------
void /*thiscall*/ sub_439810(int this)
{
  sub_41B010((void **)(this + 2136));
  sub_41B010((void **)(this + 2132));
  sub_41B010((void **)(this + 2128));
  sub_41B010((void **)(this + 2124));
  sub_41B010((void **)(this + 2120));
  sub_4017E0(this + 2092);
  if ( *(uint32_t *)(this + 2080) != 0 )
    j__free(*(void **)(this + 2080));
  *(uint32_t *)(this + 2080) = 0;
  *(uint32_t *)(this + 2084) = 0;
  *(uint32_t *)(this + 2088) = 0;
  sub_4382D0((int *)(this + 1124));
  if ( *(uint32_t *)(this + 1112) != 0 )
    j__free(*(void **)(this + 1112));
  *(uint32_t *)(this + 1112) = 0;
  *(uint32_t *)(this + 1116) = 0;
  *(uint32_t *)(this + 1120) = 0;
  sub_41B010((void **)(this + 1104));
  sub_41B010((void **)(this + 1088));
  sub_4017E0(this + 1072);
  sub_41B010((void **)(this + 1068));
  sub_438D10(this + 1052);
  sub_4382D0((int *)(this + 104));
  sub_4017E0(this + 76);
  sub_41B010((void **)(this + 68));
  sub_41B010((void **)(this + 60));
}



// ------------------------------------------------------------
// 0x439980 sub_439980
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_439980(uint32_t *this)
{
  uint32_t *pThis_1; // esi
  uint32_t *v3; // eax

  pThis_1 = this + 1;
  *this = &vftbl_CNPvpRoomManager;
  v3 = sub_433A80();
  pThis_1[1] = v3;
  *((uint8_t *)v3 + 137) = 1;
  *(uint32_t *)(pThis_1[1] + 4) = pThis_1[1];
  *(uint32_t *)pThis_1[1] = pThis_1[1];
  *(uint32_t *)(pThis_1[1] + 8) = pThis_1[1];
  pThis_1[2] = 0;
  nullsub_3();
  sub_4878B0(this);
  return this;
}



// ------------------------------------------------------------
// 0x439A00 CNPvpRoomManager__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNPvpRoomManager__vmt0(void *Block, char pszArg2)
{
  sub_439A30();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x439A30 sub_439A30
// ------------------------------------------------------------
void /*thiscall*/ sub_439A30(int **this)
{
  int **pThis; // esi
  int *v2; // eax
  int v3; // [esp-8h] [ebp-1Ch]
  int **pThis2; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  pThis = this;
  pThis2 = this;
  *this = (int *)&vftbl_CNPvpRoomManager;
  v5 = 0;
  nullsub_3();
  v2 = pThis[2];
  ++pThis;
  v3 = *v2;
  v5 = -1;
  sub_438820(pThis, (int *)&pThis2, v3, (int)v2);
  j__free(pThis[1]);
  pThis[1] = nullptr;
  pThis[2] = nullptr;
}



// ------------------------------------------------------------
// 0x439AB0 sub_439AB0
// ------------------------------------------------------------
// 【全局数据总装】（被引导 0x420DA0 调用）'IMAGE LOAD ERROR' 检查 →
//   Etc/ServerParameter.etc · EmoticonTypeTags.etc · SlangList.etc（失败弹串1176
//   "Run Error"）→ 数据表族：Character/Monster/PassiveObject/Pet/Equipment/Stackable/
//   Map/Dungeon/Skill/ItemShop/Quest/Npc/WorldMap/Town（.lst）+ ExpTable.tbl ·
//   PVPPriceTable.tbl · PriceTable.tbl → 管理器单例群（dword_99FD5C WebTextFilter、
//   dword_99FD60/99FD68…）。
void sub_439AB0()
{
  struct _RTL_CRITICAL_SECTION *pMem; // eax
  void *pMem2; // eax
  uint32_t *v2; // eax
  void *pMem3; // eax
  int v4; // edx
  char *v5; // eax
  bool v6; // zf
  HWND v7; // edi
  const CHAR *v8; // eax
  HWND v9; // edi
  const CHAR *v10; // eax
  HWND v11; // edi
  const CHAR *v12; // eax
  HWND v13; // edi
  const CHAR *v14; // eax
  int v15; // eax
  uint8_t *pMem5; // eax
  void *pMem6; // eax
  char *v18; // eax
  void *pMem7; // eax
  char *v20; // eax
  uint32_t *pMem8; // esi
  uint32_t *pMem9; // esi
  uint32_t *pMem10; // esi
  uint32_t *pMem11; // esi
  uint32_t *pMem12; // esi
  uint32_t *pMem13; // esi
  uint32_t *pMem14; // esi
  uint32_t *pMem15; // esi
  uint32_t *pMem16; // esi
  uint32_t *pMem17; // esi
  uint32_t *pMem18; // esi
  uint32_t *pMem19; // esi
  uint32_t *pMem20; // esi
  uint32_t *pMem21; // esi
  uint32_t *pMem22; // esi
  uint32_t *pMem23; // esi
  void *pMem24; // eax
  void *v38; // eax
  void *pMem25; // eax
  int v40; // eax
  void *pMem26; // eax
  int v42; // eax
  uint32_t *pMem27; // eax
  uint32_t *pMem272; // esi
  int v45; // eax
  void *pMem28; // eax
  int v47; // eax
  void *pMem29; // eax
  int v49; // eax
  void *pMem30; // eax
  int v51; // eax
  void *pMem31; // eax
  int v53; // eax
  uint8_t *pMem32; // eax
  uint8_t *v55; // eax
  void *pMem33; // eax
  uint32_t *v57; // eax
  uint32_t *v58; // eax
  void *pMem34; // eax
  int v60; // esi
  int v61; // eax
  bool (/*cdecl*/ *v62)(struct Concurrency::details::_UnrealizedChore *, void *); // eax
  void *pMem35; // eax
  void *v64; // eax
  void *pMem36; // eax
  void *v66; // eax
  void *v67; // eax
  void *v68; // eax
  void *v69; // eax
  void *pMem37; // eax
  int v71; // eax
  uint32_t *pMem38; // eax
  uint32_t *pMem382; // esi
  void *pMem39; // eax
  int v75; // eax
  uint32_t *pMem40; // eax
  uint32_t *pMem402; // esi
  uint32_t *pMem41; // eax
  uint32_t *v79; // eax
  uint32_t *pMem42; // eax
  uint32_t *v81; // eax
  uint32_t *pMem43; // eax
  uint32_t *v83; // eax
  uint32_t *pMem44; // eax
  uint32_t *v85; // eax
  uint32_t *pMem45; // eax
  uint32_t *v87; // eax
  uint32_t *pMem46; // eax
  uint32_t *v89; // eax
  uint32_t *pMem47; // eax
  uint32_t *v91; // eax
  uint32_t *pMem48; // eax
  uint32_t *v93; // eax
  uint32_t *pMem49; // eax
  uint32_t *v95; // eax
  uint32_t *pMem50; // eax
  uint32_t *v97; // eax
  uint32_t *pMem51; // eax
  uint32_t *v99; // eax
  uint32_t *pMem52; // eax
  uint32_t *v101; // eax
  uint32_t *pMem53; // eax
  uint32_t *v103; // eax
  uint32_t *pMem54; // eax
  uint32_t *v105; // eax
  uint32_t *pMem55; // eax
  uint32_t *v107; // eax
  uint32_t *pMem56; // eax
  uint32_t *v109; // eax
  uint32_t *pMem57; // eax
  uint32_t *v111; // eax
  uint32_t *pMem58; // eax
  uint32_t *v113; // eax
  uint32_t *pMem59; // eax
  uint32_t *v115; // eax
  uint32_t *pMem60; // eax
  uint32_t *v117; // eax
  uint32_t *pMem61; // eax
  uint32_t *v119; // eax
  uint32_t *pMem62; // eax
  uint32_t *v121; // eax
  uint32_t *pMem63; // eax
  uint32_t *v123; // eax
  uint32_t *pMem64; // eax
  uint32_t *v125; // eax
  uint32_t *pMem65; // eax
  uint32_t *v127; // eax
  uint32_t *pMem66; // eax
  uint32_t *v129; // eax
  uint32_t *pMem67; // eax
  uint32_t *v131; // eax
  uint32_t *pMem68; // eax
  uint32_t *v133; // eax
  uint32_t *pMem69; // eax
  uint32_t *v135; // eax
  uint32_t *pMem70; // eax
  uint32_t *v137; // eax
  uint32_t *pMem71; // eax
  uint32_t *v139; // eax
  uint32_t *pMem72; // eax
  uint32_t *v141; // eax
  uint32_t *pMem73; // eax
  uint32_t *v143; // eax
  uint32_t *pMem74; // eax
  uint32_t *v145; // eax
  uint32_t *pMem75; // eax
  uint32_t *v147; // eax
  uint32_t *pMem76; // eax
  uint32_t *v149; // eax
  uint32_t *pMem77; // eax
  uint32_t *v151; // eax
  uint32_t *pMem78; // eax
  uint32_t *v153; // eax
  uint32_t *pMem79; // eax
  uint32_t *v155; // eax
  uint32_t *pMem80; // eax
  uint32_t *v157; // eax
  uint32_t *pMem81; // eax
  uint32_t *v159; // eax
  uint32_t *pMem82; // eax
  uint32_t *v161; // eax
  uint32_t *pMem83; // eax
  uint32_t *v163; // eax
  int i; // eax
  uint32_t *v165; // eax
  char *byte_77FD082; // eax
  int j; // eax
  void **v168; // esi
  void **v169; // edi
  int v170; // [esp-4h] [ebp-89Ch]
  int v171; // [esp-4h] [ebp-89Ch]
  bool (/*cdecl*/ *v172)(struct Concurrency::details::_UnrealizedChore *, void *); // [esp-4h] [ebp-89Ch]
  void *v173; // [esp+0h] [ebp-898h]
  bool (/*cdecl*/ *v174)(struct Concurrency::details::_UnrealizedChore *, void *); // [esp+4h] [ebp-894h]
  char v175[4]; // [esp+Ch] [ebp-88Ch] BYREF
  void *Block; // [esp+10h] [ebp-888h]
  void **v177; // [esp+14h] [ebp-884h]
  int v178; // [esp+18h] [ebp-880h]
  uint16_t v179[2]; // [esp+1Ch] [ebp-87Ch] BYREF
  int v180; // [esp+20h] [ebp-878h]
  int v181; // [esp+24h] [ebp-874h] BYREF
  void *pMem4; // [esp+28h] [ebp-870h]
  int v183[536]; // [esp+2Ch] [ebp-86Ch] BYREF
  int v184; // [esp+894h] [ebp-4h]

  v183[535] = dword_796E50;
  pMem = (struct _RTL_CRITICAL_SECTION *)operator new(0xA14u);
  pMem4 = pMem;
  v184 = 0;
  if ( pMem != nullptr )
    sub_65FED0(pMem);
  v170 = *(uint32_t *)(dword_79C0A0 + 16);
  v184 = -1;
  if ( sub_65D680(lpCriticalSection, v170) != 0 && (uint8_t)sub_65EDD0("audio.xml") != 0 )
    byte_8F8554 = 1;
  else
    off_77F3FC("Audio Manager Create Failed!");
  sub_65DAF0(0);
  sub_65D8A0(&off_77FD68);
  _access("_SoundPacks", 0);
  if ( _access("!SoundPacks", 0) != 0 )
  {
    sub_40F2B0("SoundPacks/", 1);
    lpCriticalSection[107].LockCount = (LONG)&unk_8A76C8;
  }
  Block = nullptr;
  v177 = nullptr;
  v178 = 0;
  v184 = 2;
  sub_444A40("String.lst");
  pMem2 = operator new(0x4318u);
  pMem4 = pMem2;
  if ( pMem2 != nullptr )
    v2 = (uint32_t *)sub_433C40(pMem2);
  else
    v2 = nullptr;
  dword_99FD6C = v2;
  sub_488AB0(v2);
  pMem3 = operator new(0x68u);
  pMem4 = pMem3;
  LOBYTE(v184) = 3;
  if ( pMem3 != nullptr )
  {
    v4 = 28 * *((uint32_t *)dword_99FD6C + 1);
    if ( *(uint32_t *)((char *)dword_99FD6C + v4 + 14368) < 0x10u )
      v5 = sub_4198A0((char *)pMem3, dword_79C0A4, (char *)dword_99FD6C + v4 + 14348);
    else
      v5 = sub_4198A0((char *)pMem3, dword_79C0A4, *(char **)((char *)dword_99FD6C + v4 + 14348));
  }
  else
  {
    v5 = nullptr;
  }
  dword_99FD68 = (int)v5;
  v6 = v5[4] == 0;
  LOBYTE(v184) = 1;
  if ( v6 )
    off_77F3FC("IMAGE LOAD ERROR");
  dword_978998 = (int)sub_488440;
  if ( sub_436310() == 0 )
  {
    v7 = *(HWND *)(dword_79C0A0 + 16);
    v8 = (const CHAR *)sub_422E70(1176);
    MessageBoxA(v7, v8, "Run Error", 0);
  }
  if ( (uint8_t)sub_4F8E20(&unk_8F8320) == 0 )
  {
    v9 = *(HWND *)(dword_79C0A0 + 16);
    v10 = (const CHAR *)sub_422E70(1176);
    MessageBoxA(v9, v10, "Run Error", 0);
  }
  if ( (uint8_t)sub_4FA630("Etc/EmoticonTypeTags.etc") == 0 )
  {
    v11 = *(HWND *)(dword_79C0A0 + 16);
    v12 = (const CHAR *)sub_422E70(1176);
    MessageBoxA(v11, v12, "Run Error", 0);
  }
  if ( (uint8_t)sub_4FA820("Etc/SlangList.etc", v175) == 0 )
  {
    ShowCursor(true);
    v13 = *(HWND *)(dword_79C0A0 + 16);
    v14 = (const CHAR *)sub_422E70(1176);
    MessageBoxA(v13, v14, "Run Error", 0);
    PostQuitMessage(0);
  }
  sub_508C30("Character/", "Character.lst", "ExpTable.tbl", "PVPPriceTable.tbl");
  sub_50D260("Monster/", "Monster.lst");
  sub_508D50("PassiveObject/", "PassiveObject.lst");
  sub_508DE0("Pet/", "Pet.lst");
  sub_4F4BE0("Equipment/", "Equipment.lst", "PriceTable.tbl");
  sub_4F4D50("Stackable/", "Stackable.lst", "PriceTable.tbl");
  sub_4AB6A0();
  sub_504300("Map/", "Map.lst");
  sub_4F0600("Dungeon/", "Dungeon.lst");
  sub_4AB6A0();
  sub_502B30("Skill/", "SkillList.lst");
  sub_4AB6A0();
  sub_5002A0("ItemShop/", "ItemShop.lst");
  sub_4FEEA0("Quest/", "Quest.lst");
  sub_4FD770("Npc/", "Npc.lst");
  sub_4FD430("WorldMap/", "WorldMap.lst");
  sub_4FC840("Town/", "Town.lst");
  sub_4FC1E0((int)byte_8F85E0, (char)"Etc/ServerParameter.etc");
  sub_4FBA70();
  sub_4F9240(&unk_8F7C68);
  sub_439680(v183);
  LOBYTE(v184) = 4;
  sub_4F7C60((int)v183, (char)"character/gunner/weapon/revolver/n_rev_coltpats.equ");
  pMem4 = operator new(0x24u);
  LOBYTE(v184) = 5;
  if ( pMem4 != nullptr )
    v15 = sub_435690(v175);
  else
    v15 = 0;
  LOBYTE(v184) = 4;
  dword_99FD60 = v15;
  pMem5 = operator new(8u);
  if ( pMem5 != nullptr )
  {
    *(uint32_t *)pMem5 = &CNWebTextFilter::`vftable';
    v16[4] = 1;
  }
  else
  {
    v16 = nullptr;
  }
  dword_99FD5C = (int)v16;
  v17 = operator new(0x164u);
  v182 = v17;
  LOBYTE(v184) = 6;
  if ( v17 != nullptr )
    v18 = sub_4BC900((char *)v17, (int)"Sprite/", 0, 0);
  else
    v18 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F84B8 = (int)v18;
  v19 = operator new(0x164u);
  v182 = v19;
  LOBYTE(v184) = 7;
  if ( v19 != nullptr )
    v20 = sub_4BC900((char *)v19, (int)"Sprite/", 1, 0);
  else
    v20 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F84BC = (int)v20;
  v21 = operator new(0x124u);
  v182 = v21;
  LOBYTE(v184) = 8;
  if ( v21 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v21 = &CNScriptLoader::`vftable';
    pMem8[72] = 0;
  }
  else
  {
    pMem8 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84C0 = (int)pMem8;
  pMem9 = operator new(0x124u);
  pMem4 = pMem9;
  LOBYTE(v184) = 9;
  if ( pMem9 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *pMem9 = &CNScriptLoader::`vftable';
    v22[72] = 1;
  }
  else
  {
    v22 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84C4 = (int)v22;
  v23 = operator new(0x124u);
  v182 = v23;
  LOBYTE(v184) = 10;
  if ( v23 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v23 = &CNScriptLoader::`vftable';
    pMem10[72] = 2;
  }
  else
  {
    pMem10 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84C8 = (int)pMem10;
  pMem11 = operator new(0x124u);
  pMem4 = pMem11;
  LOBYTE(v184) = 11;
  if ( pMem11 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *pMem11 = &CNScriptLoader::`vftable';
    v24[72] = 3;
  }
  else
  {
    v24 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84CC = (int)v24;
  v25 = operator new(0x124u);
  v182 = v25;
  LOBYTE(v184) = 12;
  if ( v25 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v25 = &CNScriptLoader::`vftable';
    pMem12[72] = 4;
  }
  else
  {
    pMem12 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84D0 = (int)pMem12;
  pMem13 = operator new(0x124u);
  pMem4 = pMem13;
  LOBYTE(v184) = 13;
  if ( pMem13 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *pMem13 = &CNScriptLoader::`vftable';
    v26[72] = 5;
  }
  else
  {
    v26 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84D4 = (int)v26;
  v27 = operator new(0x124u);
  v182 = v27;
  LOBYTE(v184) = 14;
  if ( v27 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v27 = &CNScriptLoader::`vftable';
    pMem14[72] = 6;
  }
  else
  {
    pMem14 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84D8 = (int)pMem14;
  pMem15 = operator new(0x124u);
  pMem4 = pMem15;
  LOBYTE(v184) = 15;
  if ( pMem15 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *pMem15 = &CNScriptLoader::`vftable';
    v28[72] = 7;
  }
  else
  {
    v28 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84DC = (int)v28;
  v29 = operator new(0x124u);
  v182 = v29;
  LOBYTE(v184) = 16;
  if ( v29 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v29 = &CNScriptLoader::`vftable';
    pMem16[72] = 8;
  }
  else
  {
    pMem16 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84E0 = (int)pMem16;
  pMem17 = operator new(0x124u);
  pMem4 = pMem17;
  LOBYTE(v184) = 17;
  if ( pMem17 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *pMem17 = &CNScriptLoader::`vftable';
    v30[72] = 9;
  }
  else
  {
    v30 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84E4 = (int)v30;
  v31 = operator new(0x124u);
  v182 = v31;
  LOBYTE(v184) = 18;
  if ( v31 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v31 = &CNScriptLoader::`vftable';
    pMem18[72] = 10;
  }
  else
  {
    pMem18 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84E8 = (int)pMem18;
  pMem19 = operator new(0x124u);
  pMem4 = pMem19;
  LOBYTE(v184) = 19;
  if ( pMem19 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *pMem19 = &CNScriptLoader::`vftable';
    v32[72] = 11;
  }
  else
  {
    v32 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84EC = (int)v32;
  v33 = operator new(0x124u);
  v182 = v33;
  LOBYTE(v184) = 20;
  if ( v33 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v33 = &CNScriptLoader::`vftable';
    pMem20[72] = 12;
  }
  else
  {
    pMem20 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84F0 = (int)pMem20;
  pMem21 = operator new(0x124u);
  pMem4 = pMem21;
  LOBYTE(v184) = 21;
  if ( pMem21 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *pMem21 = &CNScriptLoader::`vftable';
    v34[72] = 13;
  }
  else
  {
    v34 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84F4 = (int)v34;
  v35 = operator new(0x124u);
  v182 = v35;
  LOBYTE(v184) = 22;
  if ( v35 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *v35 = &CNScriptLoader::`vftable';
    pMem22[72] = 14;
  }
  else
  {
    pMem22 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84F8 = (int)pMem22;
  pMem23 = operator new(0x120u);
  pMem4 = pMem23;
  LOBYTE(v184) = 23;
  if ( pMem23 != nullptr )
  {
    sub_438DB0(0, szPassword, 0);
    *pMem23 = &CNAnimationLoader::`vftable';
  }
  else
  {
    v36 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F84FC = (int)v36;
  v37 = operator new(0x410u);
  v182 = v37;
  LOBYTE(v184) = 24;
  if ( v37 != nullptr )
    v38 = (void *)sub_4385C0(v37);
  else
    v38 = nullptr;
  LOBYTE(v184) = 4;
  dword_99FD58 = v38;
  v39 = operator new(0x14u);
  v182 = v39;
  LOBYTE(v184) = 25;
  if ( v39 != nullptr )
    v40 = sub_436D10(v39);
  else
    v40 = 0;
  LOBYTE(v184) = 4;
  dword_8F8500 = v40;
  v41 = operator new(0x10u);
  v182 = v41;
  LOBYTE(v184) = 26;
  if ( v41 != nullptr )
    v42 = sub_439980(v41);
  else
    v42 = 0;
  LOBYTE(v184) = 4;
  dword_8F8504 = v42;
  v43 = operator new(0xCu);
  v44 = v43;
  v182 = v43;
  LOBYTE(v184) = 27;
  if ( v43 != nullptr )
  {
    *v43 = &off_6C45C8;
    sub_49EA10(v43);
    sub_49F320(v44);
  }
  else
  {
    v44 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F8508 = (int)v44;
  if ( dword_8F7C48 != nullptr )
    v45 = (dword_8F7C4C - (int)dword_8F7C48) / 20;
  else
    v45 = 0;
  sub_49F970(v44, v45);
  v46 = operator new(0x24u);
  v182 = v46;
  LOBYTE(v184) = 28;
  if ( v46 != nullptr )
    v47 = sub_436E30(v46);
  else
    v47 = 0;
  LOBYTE(v184) = 4;
  dword_8F850C = v47;
  v48 = operator new(0x14u);
  v182 = v48;
  LOBYTE(v184) = 29;
  if ( v48 != nullptr )
    v49 = sub_47A9B0(v48);
  else
    v49 = 0;
  LOBYTE(v184) = 4;
  dword_8F8510 = v49;
  v50 = operator new(0x78u);
  v182 = v50;
  LOBYTE(v184) = 30;
  if ( v50 != nullptr )
    v51 = sub_47A9E0(v50);
  else
    v51 = 0;
  LOBYTE(v184) = 4;
  dword_8F8514 = v51;
  v52 = operator new(0x8Cu);
  v182 = v52;
  LOBYTE(v184) = 31;
  if ( v52 != nullptr )
    v53 = sub_47AB30(v52);
  else
    v53 = 0;
  LOBYTE(v184) = 4;
  dword_8F8518 = v53;
  v54 = operator new(0x10u);
  v182 = v54;
  LOBYTE(v184) = 32;
  if ( v54 != nullptr )
    v55 = sub_4BF200(v54);
  else
    v55 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F851C = v55;
  sub_472AF0();
  sub_483870();
  v56 = operator new(0x1C0u);
  v182 = v56;
  LOBYTE(v184) = 33;
  if ( v56 != nullptr )
    v57 = (uint32_t *)sub_433360(v56);
  else
    v57 = nullptr;
  dword_8F8524 = v57;
  v171 = v57[4];
  LOBYTE(v184) = 4;
  v58 = (uint32_t *)sub_656710();
  sub_656790(v58, v171);
  v59 = operator new(0x100678u);
  v182 = v59;
  LOBYTE(v184) = 34;
  if ( v59 != nullptr )
    v60 = sub_435C30(v59);
  else
    v60 = 0;
  LOBYTE(v184) = 4;
  dword_8F8520 = v60;
  *(uint32_t *)(sub_656710() + 36) = v60;
  v61 = *(uint32_t *)(dword_8F8520 + 1049988);
  if ( v61 != 0 )
    v62 = (bool (/*cdecl*/ *)(struct Concurrency::details::_UnrealizedChore *, void *))(v61 + 2220);
  else
    v62 = nullptr;
  v172 = v62;
  sub_656710();
  Concurrency::details::ContextBase::SweepUnstructured(v172, v173, v174);
  v63 = operator new(0x3Cu);
  v182 = v63;
  LOBYTE(v184) = 35;
  if ( v63 != nullptr )
  {
    if ( dword_8F8520 != 0 )
      v64 = sub_656470(v63, dword_8F8520 + 8);
    else
      v64 = sub_656470(v63, 0);
  }
  else
  {
    v64 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F8548 = (int)v64;
  v65 = operator new(0x9ECu);
  v182 = v65;
  LOBYTE(v184) = 36;
  if ( v65 != nullptr )
    v66 = (void *)sub_4355A0(v65);
  else
    v66 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8528 = v66;
  v182 = operator new(0x20u);
  LOBYTE(v184) = 37;
  if ( v182 != nullptr )
    v67 = (void *)sub_4354D0(nullptr, 137);
  else
    v67 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F852C = v67;
  v182 = operator new(0x20u);
  LOBYTE(v184) = 38;
  if ( v182 != nullptr )
    v68 = (void *)sub_4354D0((void *)2, 64);
  else
    v68 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8530 = v68;
  v182 = operator new(0x20u);
  LOBYTE(v184) = 39;
  if ( v182 != nullptr )
    v69 = (void *)sub_4354D0((void *)1, 105);
  else
    v69 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8534 = v69;
  v70 = operator new(0x50u);
  v182 = v70;
  LOBYTE(v184) = 40;
  if ( v70 != nullptr )
    v71 = sub_433480(v70);
  else
    v71 = 0;
  LOBYTE(v184) = 4;
  dword_8F8538 = v71;
  v72 = operator new(0xCu);
  v73 = v72;
  v182 = v72;
  LOBYTE(v184) = 41;
  if ( v72 != nullptr )
  {
    unknown_libname_4(v72);
    sub_483C60(v73, 216);
  }
  else
  {
    v73 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F853C = v73;
  v74 = operator new(0x3Cu);
  v182 = v74;
  LOBYTE(v184) = 42;
  if ( v74 != nullptr )
    v75 = sub_439220(v74);
  else
    v75 = 0;
  LOBYTE(v184) = 4;
  dword_8F8540 = v75;
  v76 = operator new(0xB0u);
  v77 = v76;
  v182 = v76;
  LOBYTE(v184) = 43;
  if ( v76 != nullptr )
  {
    *v76 = &CNRDConfigFile::`vftable';
    sub_48B700((int)pMem40);
    sub_48B9C0(pMem402, "./ARAD.cfg");
  }
  else
  {
    pMem402 = nullptr;
  }
  LOBYTE(v184) = 4;
  dword_8F8544 = (int)pMem402;
  pMem41 = operator new(0x12Cu);
  pMem4 = pMem41;
  LOBYTE(v184) = 44;
  if ( pMem41 != nullptr )
    v79 = sub_428F30(pMem41, (int)"Common/HitEffect/Particle/LargeHitParticle.ptl", 0);
  else
    v79 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8270[0] = (int)v79;
  pMem42 = operator new(0x12Cu);
  pMem4 = pMem42;
  LOBYTE(v184) = 45;
  if ( pMem42 != nullptr )
    v81 = sub_428F30(pMem42, (int)"Common/HitEffect/Particle/SmallHitParticle.ptl", 0);
  else
    v81 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8274 = (int)v81;
  pMem43 = operator new(0x12Cu);
  pMem4 = pMem43;
  LOBYTE(v184) = 46;
  if ( pMem43 != nullptr )
    v83 = sub_428F30(pMem43, (int)"Common/HitEffect/Particle/FireHitParticle.ptl", 0);
  else
    v83 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8278 = (int)v83;
  pMem44 = operator new(0x12Cu);
  pMem4 = pMem44;
  LOBYTE(v184) = 47;
  if ( pMem44 != nullptr )
    v85 = sub_428F30(pMem44, (int)"Common/HitEffect/Particle/FireHitParticleLight.ptl", 0);
  else
    v85 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F827C = (int)v85;
  pMem45 = operator new(0x12Cu);
  pMem4 = pMem45;
  LOBYTE(v184) = 48;
  if ( pMem45 != nullptr )
    v87 = sub_428F30(pMem45, (int)"Common/HitEffect/Particle/WaterHitParticle.ptl", 0);
  else
    v87 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8280 = (int)v87;
  pMem46 = operator new(0x12Cu);
  pMem4 = pMem46;
  LOBYTE(v184) = 49;
  if ( pMem46 != nullptr )
    v89 = sub_428F30(pMem46, (int)"Common/HitEffect/Particle/WaterHitParticleLight.ptl", 0);
  else
    v89 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8284 = (int)v89;
  pMem47 = operator new(0x12Cu);
  pMem4 = pMem47;
  LOBYTE(v184) = 50;
  if ( pMem47 != nullptr )
    v91 = sub_428F30(pMem47, (int)"Common/HitEffect/Particle/DarkHitParticleLight.ptl", 0);
  else
    v91 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8288 = (int)v91;
  pMem48 = operator new(0x12Cu);
  pMem4 = pMem48;
  LOBYTE(v184) = 51;
  if ( pMem48 != nullptr )
    v93 = sub_428F30(pMem48, (int)"Common/HitEffect/Particle/LightHitParticleLight.ptl", 0);
  else
    v93 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F828C = (int)v93;
  pMem49 = operator new(0x12Cu);
  pMem4 = pMem49;
  LOBYTE(v184) = 52;
  if ( pMem49 != nullptr )
    v95 = sub_428F30(pMem49, (int)"Common/HitEffect/Particle/MagicHitParticle1.ptl", 0);
  else
    v95 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8290 = (int)v95;
  pMem50 = operator new(0x12Cu);
  pMem4 = pMem50;
  LOBYTE(v184) = 53;
  if ( pMem50 != nullptr )
    v97 = sub_428F30(pMem50, (int)"Common/HitEffect/Particle/MagicHitParticle2.ptl", 0);
  else
    v97 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8294 = (int)v97;
  pMem51 = operator new(0x12Cu);
  pMem4 = pMem51;
  LOBYTE(v184) = 54;
  if ( pMem51 != nullptr )
    v99 = sub_428F30(pMem51, (int)"Common/CommonEffect/Particle/DustDownLarge.ptl", 0);
  else
    v99 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8298 = (int)v99;
  pMem52 = operator new(0x12Cu);
  pMem4 = pMem52;
  LOBYTE(v184) = 55;
  if ( pMem52 != nullptr )
    v101 = sub_428F30(pMem52, (int)"Common/CommonEffect/Particle/DustDownSmall.ptl", 0);
  else
    v101 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F829C = (int)v101;
  pMem53 = operator new(0x12Cu);
  pMem4 = pMem53;
  LOBYTE(v184) = 56;
  if ( pMem53 != nullptr )
    v103 = sub_428F30(pMem53, (int)"Common/CommonEffect/Particle/DustMove.ptl", 0);
  else
    v103 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82A0 = (int)v103;
  pMem54 = operator new(0x12Cu);
  pMem4 = pMem54;
  LOBYTE(v184) = 57;
  if ( pMem54 != nullptr )
    v105 = sub_428F30(pMem54, (int)"PassiveObject/Character/Swordman/Particle/IceWaveParticleSmoke.ptl", 0);
  else
    v105 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82A4 = (int)v105;
  pMem55 = operator new(0x12Cu);
  pMem4 = pMem55;
  LOBYTE(v184) = 58;
  if ( pMem55 != nullptr )
    v107 = sub_428F30(pMem55, (int)"PassiveObject/Character/Swordman/Particle/IceWaveParticle.ptl", 0);
  else
    v107 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82A8 = (int)v107;
  pMem56 = operator new(0x12Cu);
  pMem4 = pMem56;
  LOBYTE(v184) = 59;
  if ( pMem56 != nullptr )
    v109 = sub_428F30(pMem56, (int)"PassiveObject/Character/Swordman/Particle/IceWaveParticleStar.ptl", 0);
  else
    v109 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82AC = (int)v109;
  pMem57 = operator new(0x12Cu);
  pMem4 = pMem57;
  LOBYTE(v184) = 60;
  if ( pMem57 != nullptr )
    v111 = sub_428F30(pMem57, (int)"PassiveObject/Common/Particle/ThunderBoltParticle.ptl", 0);
  else
    v111 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82B0 = (int)v111;
  pMem58 = operator new(0x12Cu);
  pMem4 = pMem58;
  LOBYTE(v184) = 61;
  if ( pMem58 != nullptr )
    v113 = sub_428F30(pMem58, (int)"Common/CommonEffect/Particle/HealParticle.ptl", 0);
  else
    v113 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82B4 = (int)v113;
  pMem59 = operator new(0x12Cu);
  pMem4 = pMem59;
  LOBYTE(v184) = 62;
  if ( pMem59 != nullptr )
    v115 = sub_428F30(pMem59, (int)"Common/CommonEffect/Particle/FieldItemParticle.ptl", 0);
  else
    v115 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82B8 = (int)v115;
  pMem60 = operator new(0x12Cu);
  pMem4 = pMem60;
  LOBYTE(v184) = 63;
  if ( pMem60 != nullptr )
    v117 = sub_428F30(pMem60, (int)"Common/ActiveStatus/Particle/FreezeParticle.ptl", 0);
  else
    v117 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82BC = (int)v117;
  pMem61 = operator new(0x12Cu);
  pMem4 = pMem61;
  LOBYTE(v184) = 64;
  if ( pMem61 != nullptr )
    v119 = sub_428F30(pMem61, (int)"PassiveObject/Character/Fighter/Particle/ThrowSandParticle1.ptl", 0);
  else
    v119 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82C0 = (int)v119;
  pMem62 = operator new(0x12Cu);
  pMem4 = pMem62;
  LOBYTE(v184) = 65;
  if ( pMem62 != nullptr )
    v121 = sub_428F30(pMem62, (int)"PassiveObject/Character/Fighter/Particle/ThrowSandParticle2.ptl", 0);
  else
    v121 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82C4 = (int)v121;
  pMem63 = operator new(0x12Cu);
  pMem4 = pMem63;
  LOBYTE(v184) = 66;
  if ( pMem63 != nullptr )
    v123 = sub_428F30(pMem63, (int)"PassiveObject/Common/Particle/ShootingStarPath.ptl", 0);
  else
    v123 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82C8 = (int)v123;
  pMem64 = operator new(0x12Cu);
  pMem4 = pMem64;
  LOBYTE(v184) = 67;
  if ( pMem64 != nullptr )
    v125 = sub_428F30(pMem64, (int)"Monster/Common/Particle/MonsterDieBlood.ptl", 0);
  else
    v125 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82CC = (int)v125;
  pMem65 = operator new(0x12Cu);
  pMem4 = pMem65;
  LOBYTE(v184) = 68;
  if ( pMem65 != nullptr )
    v127 = sub_428F30(pMem65, (int)"Monster/Common/Particle/MonsterDieBloodYoung.ptl", 0);
  else
    v127 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82D0 = (int)v127;
  pMem66 = operator new(0x12Cu);
  pMem4 = pMem66;
  LOBYTE(v184) = 69;
  if ( pMem66 != nullptr )
    v129 = sub_428F30(pMem66, (int)"Monster/Common/Particle/MonsterDiePiece.ptl", 0);
  else
    v129 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82D4 = (int)v129;
  pMem67 = operator new(0x12Cu);
  pMem4 = pMem67;
  LOBYTE(v184) = 70;
  if ( pMem67 != nullptr )
    v131 = sub_428F30(pMem67, (int)"Monster/Common/Particle/MonsterDiePieceYoung.ptl", 0);
  else
    v131 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82D8 = (int)v131;
  pMem68 = operator new(0x12Cu);
  pMem4 = pMem68;
  LOBYTE(v184) = 71;
  if ( pMem68 != nullptr )
    v133 = sub_428F30(pMem68, (int)"Monster/Common/Particle/MonsterDiePieceVeryYoung.ptl", 0);
  else
    v133 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82DC = (int)v133;
  pMem69 = operator new(0x12Cu);
  pMem4 = pMem69;
  LOBYTE(v184) = 72;
  if ( pMem69 != nullptr )
    v135 = sub_428F30(pMem69, (int)"Monster/Common/Particle/MonsterDieFlashYoung.ptl", 0);
  else
    v135 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82E0 = (int)v135;
  pMem70 = operator new(0x12Cu);
  pMem4 = pMem70;
  LOBYTE(v184) = 73;
  if ( pMem70 != nullptr )
    v137 = sub_428F30(pMem70, (int)"Common/CommonEffect/Particle/BuffStartParticle.ptl", 0);
  else
    v137 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82E4 = (int)v137;
  pMem71 = operator new(0x12Cu);
  pMem4 = pMem71;
  LOBYTE(v184) = 74;
  if ( pMem71 != nullptr )
    v139 = sub_428F30(pMem71, (int)"Common/CommonEffect/Particle/SwampSpoutDownLarge.ptl", 0);
  else
    v139 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82E8 = (int)v139;
  pMem72 = operator new(0x12Cu);
  pMem4 = pMem72;
  LOBYTE(v184) = 75;
  if ( pMem72 != nullptr )
    v141 = sub_428F30(pMem72, (int)"Common/CommonEffect/Particle/SwampSpoutDownSmall.ptl", 0);
  else
    v141 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82EC = (int)v141;
  pMem73 = operator new(0x12Cu);
  pMem4 = pMem73;
  LOBYTE(v184) = 76;
  if ( pMem73 != nullptr )
    v143 = sub_428F30(pMem73, (int)"Common/CommonEffect/Particle/SwampSpoutMove.ptl", 0);
  else
    v143 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82F0 = (int)v143;
  pMem74 = operator new(0x12Cu);
  pMem4 = pMem74;
  LOBYTE(v184) = 77;
  if ( pMem74 != nullptr )
    v145 = sub_428F30(pMem74, (int)"Common/CommonEffect/Particle/PoisonSpoutDownLarge.ptl", 0);
  else
    v145 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82F4 = (int)v145;
  pMem75 = operator new(0x12Cu);
  pMem4 = pMem75;
  LOBYTE(v184) = 78;
  if ( pMem75 != nullptr )
    v147 = sub_428F30(pMem75, (int)"Common/CommonEffect/Particle/PoisonSpoutDownSmall.ptl", 0);
  else
    v147 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82F8 = (int)v147;
  pMem76 = operator new(0x12Cu);
  pMem4 = pMem76;
  LOBYTE(v184) = 79;
  if ( pMem76 != nullptr )
    v149 = sub_428F30(pMem76, (int)"Common/CommonEffect/Particle/PoisonSpoutMove.ptl", 0);
  else
    v149 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F82FC = (int)v149;
  pMem77 = operator new(0x12Cu);
  pMem4 = pMem77;
  LOBYTE(v184) = 80;
  if ( pMem77 != nullptr )
    v151 = sub_428F30(pMem77, (int)"Common/CommonEffect/Particle/WaterBubbleLarge.ptl", 0);
  else
    v151 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8300 = (int)v151;
  pMem78 = operator new(0x12Cu);
  pMem4 = pMem78;
  LOBYTE(v184) = 81;
  if ( pMem78 != nullptr )
    v153 = sub_428F30(pMem78, (int)"Common/CommonEffect/Particle/WaterBubbleSmall.ptl", 0);
  else
    v153 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8304 = (int)v153;
  pMem79 = operator new(0x12Cu);
  pMem4 = pMem79;
  LOBYTE(v184) = 82;
  if ( pMem79 != nullptr )
    v155 = sub_428F30(pMem79, (int)"Common/CommonEffect/Particle/WaterBubbleMove.ptl", 0);
  else
    v155 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8308 = (int)v155;
  pMem80 = operator new(0x12Cu);
  pMem4 = pMem80;
  LOBYTE(v184) = 83;
  if ( pMem80 != nullptr )
    v157 = sub_428F30(pMem80, (int)"Character/Gunner/Effect/Particle/AutomaticShell.ptl", 0);
  else
    v157 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F830C = (int)v157;
  pMem81 = operator new(0x12Cu);
  pMem4 = pMem81;
  LOBYTE(v184) = 84;
  if ( pMem81 != nullptr )
    v159 = sub_428F30(pMem81, (int)"Common/CommonEffect/Particle/MAGMASpoutDownLarge.ptl", 0);
  else
    v159 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8310 = (int)v159;
  pMem82 = operator new(0x12Cu);
  pMem4 = pMem82;
  LOBYTE(v184) = 85;
  if ( pMem82 != nullptr )
    v161 = sub_428F30(pMem82, (int)"Common/CommonEffect/Particle/MAGMASpoutDownSmall.ptl", 0);
  else
    v161 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8314 = (int)v161;
  pMem83 = operator new(0x12Cu);
  pMem4 = pMem83;
  LOBYTE(v184) = 86;
  if ( pMem83 != nullptr )
    v163 = sub_428F30(pMem83, (int)"Common/CommonEffect/Particle/MAGMASpoutMove.ptl", 0);
  else
    v163 = nullptr;
  LOBYTE(v184) = 4;
  dword_8F8318 = (int)v163;
  sub_4F3960();
  sub_4302E0();
  sub_4B5B80();
  v181 = 0;
  pMem4 = (void *)2;
  (*(void (/*thiscall*/ **)(int *, uint32_t, int *))(dword_8F8558 + 16))(&dword_8F8558, 0, &v181);
  v181 = 0;
  pMem4 = (void *)3;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 1, &v181);
  v181 = 0;
  pMem4 = nullptr;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 2, &v181);
  v181 = 0;
  pMem4 = (void *)1;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 3, &v181);
  v181 = 0;
  pMem4 = (void *)80;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 4, &v181);
  v181 = 0;
  pMem4 = (void *)78;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 5, &v181);
  v181 = 0;
  pMem4 = (void *)57;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 6, &v181);
  v181 = 0;
  pMem4 = (void *)76;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 7, &v181);
  v181 = 0;
  pMem4 = (void *)13;
  (*(void (/*thiscall*/ **)(int *, int, int *))(dword_8F8558 + 16))(&dword_8F8558, 8, &v181);
  if ( dword_79C0B8 != 0 )
  {
    *(uint32_t *)(dword_79C0B8 + 2064) = 80;
    *(uint32_t *)(dword_79C0B8 + 2068) = 78;
    *(uint32_t *)(dword_79C0B8 + 2072) = 57;
    *(uint32_t *)(dword_79C0B8 + 2076) = 55;
    *(uint32_t *)(dword_79C0B8 + 2080) = 73;
    *(uint32_t *)(dword_79C0B8 + 2084) = 58;
    *(uint32_t *)(dword_79C0B8 + 2088) = 60;
    *(uint32_t *)(dword_79C0B8 + 2092) = 61;
  }
  for ( i = 0; i < 6; ++i )
  {
    dword_77FCA8[2 * i] = 0;
    dword_77FCAC[2 * i] = i + 46;
  }
  v165 = &unk_77FCD8;
  do
  {
    *v165 = 0;
    v165 += 2;
  }
  while ( (int)v165 < (int)byte_77FD08 );
  dword_77FCDC = 55;
  dword_77FCE4 = 73;
  dword_77FCEC = 58;
  dword_77FCF4 = 60;
  dword_77FCFC = 61;
  dword_77FD04 = 62;
  byte_77FD082 = byte_77FD08;
  do
  {
    *(uint32_t *)byte_77FD082 = 0;
    byte_77FD082 += 8;
  }
  while ( (int)byte_77FD082 < (int)dword_77FD48 );
  dword_77FD0C = 67;
  dword_77FD14 = 65;
  dword_77FD1C = 74;
  dword_77FD24 = 63;
  dword_77FD2C = 69;
  dword_77FD34 = 71;
  dword_77FD3C = 75;
  dword_77FD44 = 68;
  for ( j = 0; j < 4; ++j )
  {
    dword_77FD48[2 * j] = 0;
    dword_77FD4C[2 * j] = j + 81;
  }
  sub_439050(&unk_9A0330);
  sub_4ED3F0((int)&unk_8F85C4, (int)&unk_9A0340);
  dword_8F85D4 = dword_9A0350;
  dword_8F85D8 = dword_9A0354;
  byte_8F85DC = byte_9A0358;
  v179[0] = 100;
  v179[1] = 2;
  v180 = 0;
  sub_4F49C0(&unk_8F86D0, v179);
  InitializeCriticalSection(&stru_8F8258);
  EnterCriticalSection(&stru_8F8258);
  LOBYTE(v184) = 1;
  sub_439810(v183);
  v168 = (void **)Block;
  v184 = -1;
  if ( Block != nullptr )
  {
    v169 = v177;
    if ( Block != v177 )
    {
      do
        sub_41B010(v168++);
      while ( v168 != v169 );
      v168 = (void **)Block;
    }
    j__free(v168);
  }
}


// ============================================================
// §27 聊天文本工具（0x43B4C0-0x43C150）
//   0x43BCF0 命令匹配(strcmp) · 0x43BD50 聊天日志 · 0x43BEE0 播报上屏
// ============================================================
// ------------------------------------------------------------
// 0x43B4C0 sub_43B4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_43B4C0(void *this, char pszArg2)
{
  return sub_423290((int)this, (int)&pszArg2, 4);
}



// ------------------------------------------------------------
// 0x43B4E0 sub_43B4E0
// ------------------------------------------------------------
int /*thiscall*/ sub_43B4E0(void *this, char pszArg2, int nArg3)
{
  return sub_423290((int)this, (int)&pszArg2, 8);
}



// ------------------------------------------------------------
// 0x43B500 sub_43B500
// ------------------------------------------------------------
bool /*thiscall*/ sub_43B500(int this)
{
  return *(uint8_t *)(this + 17) != 0 && dword_79BE34 == *(uint32_t *)(this + 12);
}



// ------------------------------------------------------------
// 0x43B520 sub_43B520
// ------------------------------------------------------------
bool /*thiscall*/ sub_43B520(int this)
{
  return *(uint8_t *)(this + 17) != 0 && dword_79BE38 == *(uint32_t *)(this + 12);
}



// ------------------------------------------------------------
// 0x43B540 sub_43B540
// ------------------------------------------------------------
char /*thiscall*/ sub_43B540(uint32_t *this)
{
  int v1; // eax
  uint32_t *i; // ecx

  v1 = 0;
  for ( i = this + 4; *i != 0; ++i )
  {
    if ( ++v1 >= 4 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x43B560 sub_43B560
// ------------------------------------------------------------
int /*thiscall*/ sub_43B560(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7, int nArg8, int nArg9, int nArg10)
{
  int result; // eax

  result = nArg4;
  if ( nArg4 != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, void *, int, int, int, int, int, int))(*(uint32_t *)nArg4 + 128))(
             nArg4,
             nArg2,
             nArg3,
             this,
             nArg5,
             nArg6,
             nArg7,
             nArg8,
             nArg9,
             nArg10);
  return result;
}



// ------------------------------------------------------------
// 0x43B5A0 sub_43B5A0
// ------------------------------------------------------------
double /*thiscall*/ sub_43B5A0(void *this)
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this));
}



// ------------------------------------------------------------
// 0x43B5C0 sub_43B5C0
// ------------------------------------------------------------
double /*thiscall*/ sub_43B5C0(void *this)
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this + 892));
}



// ------------------------------------------------------------
// 0x43B5E0 sub_43B5E0
// ------------------------------------------------------------
double /*thiscall*/ sub_43B5E0(void *this)
{
  return COERCE_FLOAT(sub_41A5E0((unsigned int)this + 920));
}



// ------------------------------------------------------------
// 0x43B600 sub_43B600
// ------------------------------------------------------------
bool /*cdecl*/ sub_43B600(const char *pArg1, unsigned int uArg2, char *SubStr, char pszArg4)
{
  if ( strlen(pArg1) < uArg2 )
    return false;
  if ( pszArg4 != 0 )
    return strcmp(&pArg1[uArg2], SubStr) == 0;
  return &pArg1[uArg2] == strstr(&pArg1[uArg2], SubStr);
}



// ------------------------------------------------------------
// 0x43B6A0 sub_43B6A0
// ------------------------------------------------------------
int /*thiscall*/ sub_43B6A0(uint32_t *this)
{
  void (/*thiscall*/ ***fld_e3)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e5)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e6)(uint32_t, int); // ecx
  uint32_t *pThis_7; // edi
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  bool v9; // zf
  void (/*thiscall*/ ****pThis_F)(uint32_t, int); // edi
  void (/*thiscall*/ ***v11)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v12)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e14)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e17)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e18)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e23)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e24)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e30)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e31)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e32)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e33)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e34)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e28)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e29)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e25)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e26)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e27)(uint32_t, int); // ecx
  int i; // [esp+8h] [ebp-4h]
  int v31; // [esp+8h] [ebp-4h]

  fld_e3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  if ( fld_e3 != nullptr )
    (**fld_e3)(fld_e3, 1);
  fld_e4 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 4);
  *(this + 3) = 0;
  if ( fld_e4 != nullptr )
    (**fld_e4)(fld_e4, 1);
  fld_e5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 5);
  *(this + 4) = 0;
  if ( fld_e5 != nullptr )
    (**fld_e5)(fld_e5, 1);
  fld_e6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  *(this + 5) = 0;
  if ( fld_e6 != nullptr )
    (**fld_e6)(fld_e6, 1);
  *(this + 6) = 0;
  pThis_7 = this + 7;
  for ( i = 4; i != 0; --i )
  {
    v7 = (void (/*thiscall*/ ***)(uint32_t, int))pThis_7[12];
    if ( v7 != nullptr )
      (**v7)(v7, 1);
    v8 = (void (/*thiscall*/ ***)(uint32_t, int))*pThis_7;
    v9 = *pThis_7 == 0;
    pThis_7[12] = 0;
    if ( !v9 )
      (**v8)(v8, 1);
    *pThis_7++ = 0;
  }
  pThis_F = (void (/*thiscall*/ ****)(uint32_t, int))(this + 15);
  v31 = 2;
  do
  {
    v11 = *(pThis_F - 4);
    if ( v11 != nullptr )
      (**v11)(v11, 1);
    v12 = *pThis_F;
    v9 = *pThis_F == nullptr;
    *(pThis_F - 4) = nullptr;
    if ( !v9 )
      (**v12)(v12, 1);
    *pThis_F++ = nullptr;
    result = v31 - 1;
    v31 = result;
  }
  while ( result != 0 );
  fld_e13 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  if ( fld_e13 != nullptr )
    result = (**fld_e13)(fld_e13, 1);
  fld_e14 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;
  if ( fld_e14 != nullptr )
    result = (**fld_e14)(fld_e14, 1);
  fld_e17 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 17);
  *(this + 14) = 0;
  if ( fld_e17 != nullptr )
    result = (**fld_e17)(fld_e17, 1);
  fld_e18 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 18);
  *(this + 17) = 0;
  if ( fld_e18 != nullptr )
    result = (**fld_e18)(fld_e18, 1);
  fld_e23 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 23);
  *(this + 18) = 0;
  if ( fld_e23 != nullptr )
    result = (**fld_e23)(fld_e23, 1);
  fld_e24 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 24);
  *(this + 23) = 0;
  if ( fld_e24 != nullptr )
    result = (**fld_e24)(fld_e24, 1);
  fld_e30 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 30);
  *(this + 24) = 0;
  if ( fld_e30 != nullptr )
    result = (**fld_e30)(fld_e30, 1);
  fld_e31 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 31);
  *(this + 30) = 0;
  if ( fld_e31 != nullptr )
    result = (**fld_e31)(fld_e31, 1);
  fld_e32 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 32);
  *(this + 31) = 0;
  if ( fld_e32 != nullptr )
    result = (**fld_e32)(fld_e32, 1);
  fld_e33 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 33);
  *(this + 32) = 0;
  if ( fld_e33 != nullptr )
    result = (**fld_e33)(fld_e33, 1);
  fld_e34 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 34);
  *(this + 33) = 0;
  if ( fld_e34 != nullptr )
    result = (**fld_e34)(fld_e34, 1);
  fld_e28 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 28);
  *(this + 34) = 0;
  if ( fld_e28 != nullptr )
    result = (**fld_e28)(fld_e28, 1);
  fld_e29 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 29);
  *(this + 28) = 0;
  if ( fld_e29 != nullptr )
    result = (**fld_e29)(fld_e29, 1);
  fld_e25 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 25);
  *(this + 29) = 0;
  if ( fld_e25 != nullptr )
    result = (**fld_e25)(fld_e25, 1);
  fld_e26 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 26);
  *(this + 25) = 0;
  if ( fld_e26 != nullptr )
    result = (**fld_e26)(fld_e26, 1);
  fld_e27 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 27);
  *(this + 26) = 0;
  if ( fld_e27 != nullptr )
    result = (**fld_e27)(fld_e27, 1);
  *(this + 27) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x43B880 sub_43B880
// ------------------------------------------------------------
void /*thiscall*/ sub_43B880(uint32_t *this, int nArg2)
{
  if ( nArg2 == 1 )
  {
    if ( sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) == 0
      || *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 184) == 0 )
    {
      return;
    }
LABEL_8:
    *(this + 72) = nArg2;
    return;
  }
  if ( nArg2 != 2
    || sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) != 0
    && *(uint32_t *)(sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804) + 120) != 0 )
  {
    goto LABEL_8;
  }
}



// ------------------------------------------------------------
// 0x43B920 sub_43B920
// ------------------------------------------------------------
char /*thiscall*/ sub_43B920(int this, char pszArg2)
{
  char result; // al

  if ( *(uint8_t *)(this + 256) != pszArg2 )
  {
    if ( pszArg2 != 0 )
    {
      result = *(uint8_t *)(*(uint32_t *)(this + 136) + 17);
      if ( result == 0 )
        return result;
      sub_69BCC0();
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(this + 136) + 12);
      dword_79BE54 = dword_79BE4C;
      *(uint32_t *)(*(uint32_t *)(this + 136) + 108) = 475;
      *(uint8_t *)(this + 1794) = 1;
    }
    else
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(this + 124) + 12);
      dword_79BE54 = dword_79BE4C;
    }
    *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = pszArg2;
    *(uint8_t *)(this + 273) = 0;
    *(uint8_t *)(this + 274) = 0;
    result = sub_698F90(this + 260, 100, 0);
    *(uint8_t *)(this + 256) = pszArg2;
    if ( pszArg2 == 0 )
      return CNCommandChecker__vmt40(0, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x43B9D0 sub_43B9D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_43B9D0(uint32_t *this, int nArg2)
{
  uint32_t *result; // eax
  int v4; // edx
  uint32_t *pThis_2C; // ecx

  result = (uint32_t *)sub_69C340(nArg2);
  v4 = 20 - nArg2;
  if ( 20 - nArg2 > 0 )
  {
    pThis_2C = this + 44;
    result = this + nArg2 + 44;
    do
    {
      *pThis_2C++ = *result++;
      --v4;
    }
    while ( v4 != 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x43BA20 sub_43BA20
// ------------------------------------------------------------
int /*thiscall*/ sub_43BA20(int this, int pArg2)
{
  int pThis_4; // ebx
  int pThis_42; // eax
  BOOL v5; // ebx
  int fld_48; // eax

  *(uint32_t *)(this + 144) = pArg2;
  *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = pArg2 == 0;
  *(uint8_t *)(*(uint32_t *)(this + 28) + 16) = pArg2 != 0;
  *(uint8_t *)(*(uint32_t *)(this + 80) + 16) = pArg2 == 1;
  *(uint8_t *)(*(uint32_t *)(this + 32) + 16) = pArg2 != 1;
  *(uint8_t *)(*(uint32_t *)(this + 84) + 16) = pArg2 == 2;
  *(uint8_t *)(*(uint32_t *)(this + 36) + 16) = pArg2 != 2;
  *(uint8_t *)(*(uint32_t *)(this + 88) + 16) = pArg2 == 3;
  *(uint8_t *)(*(uint32_t *)(this + 40) + 16) = pArg2 != 3;
  pThis_4 = sub_69C3A0(*(uint32_t *)(this + 4 * pArg2 + 76));
  pThis_42 = sub_69C500(*(uint32_t *)(this + 4 * pArg2 + 76)) - pThis_4;
  v5 = pThis_42 <= 0;
  if ( *(uint8_t *)(this + 1474) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 72) + 32))(*(uint32_t *)(this + 72), v5 ? 0 : pThis_42);
    fld_48 = sub_69C6A0(*(uint32_t *)(this + 72));
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), v5 ? 0 : pThis_42);
    fld_48 = sub_69C6A0(*(uint32_t *)(this + 56));
  }
  return sub_69C680(fld_48);
}



// ------------------------------------------------------------
// 0x43BB10 sub_43BB10
// ------------------------------------------------------------
int /*thiscall*/ sub_43BB10(uint32_t *this, int pArg2, char pszArg3)
{
  *(uint8_t *)(*(this + pArg2 + 7) + 17) = pszArg3;
  return pArg2;
}



// ------------------------------------------------------------
// 0x43BB30 sub_43BB30
// ------------------------------------------------------------
int /*thiscall*/ sub_43BB30(int this)
{
  int pThis_4C; // esi
  int i; // ebx

  pThis_4C = this + 76;
  for ( i = 4; i != 0; --i )
  {
    sub_69C340(-1);
    pThis_4C += 4;
  }
  if ( *(uint8_t *)(this + 1474) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 72) + 32))(*(uint32_t *)(this + 72), 0);
  else
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), 0);
  sub_69C340(-1);
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 228) = 0;
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  *(uint32_t *)(this + 248) = 0;
  *(uint32_t *)(this + 252) = 0;
  return this + 176;
}



// ------------------------------------------------------------
// 0x43BBC0 sub_43BBC0
// ------------------------------------------------------------
int /*thiscall*/ sub_43BBC0(uint8_t *this)
{
  char fld_e1474; // bl
  int result; // eax
  int v3; // ecx
  LONG v4; // edx

  fld_e1474 = *(this + 1474);
  result = 0;
  v3 = 202;
  while ( 1 )
  {
    v4 = v3 + 192;
    if ( fld_e1474 == 0 )
      v4 = v3;
    if ( pt.x >= 9 && pt.x < 42 && pt.y >= v4 && pt.y < v4 + 16 )
      break;
    v3 += 16;
    ++result;
    if ( v3 >= 282 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x43BC20 sub_43BC20
// ------------------------------------------------------------
int sub_43BC20()
{
  int result; // eax
  LONG v1; // ecx

  result = 0;
  v1 = 322;
  while ( pt.x < 61 || pt.x >= 94 || pt.y < v1 || pt.y >= v1 + 16 )
  {
    v1 += 17;
    ++result;
    if ( v1 >= 390 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x43BC60 sub_43BC60
// ------------------------------------------------------------
int /*thiscall*/ sub_43BC60(int this, char pszArg2)
{
  int result; // eax
  int fld_C; // ecx
  bool fld_5C2; // zf
  int fld_C2; // ecx

  result = 0;
  if ( pszArg2 != 0 || *(uint8_t *)(*(uint32_t *)(this + 16) + 16) != 0 )
  {
    fld_C = *(uint32_t *)(this + 12);
    *(uint32_t *)(fld_C + 28) = 0;
    *(uint32_t *)(fld_C + 32) = 0;
  }
  else
  {
    fld_5C2 = *(uint8_t *)(this + 1474) == 0;
    fld_C2 = *(uint32_t *)(this + 12);
    *(uint32_t *)(fld_C2 + 28) = 317;
    if ( fld_5C2 )
      *(uint32_t *)(fld_C2 + 32) = 162;
    else
      *(uint32_t *)(fld_C2 + 32) = 354;
  }
  return result;
}



// ------------------------------------------------------------
// 0x43BCB0 sub_43BCB0
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_43BCB0(int this)
{
  int fld_C; // esi
  BOOL result; // eax

  result = false;
  if ( *(uint8_t *)(this + 17) != 0 )
  {
    fld_C = *(uint32_t *)(this + 12);
    if ( dword_79BE3C == fld_C || dword_79BE34 == fld_C || dword_79BE38 == fld_C )
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x43BCF0 sub_43BCF0
// ------------------------------------------------------------
// 【命令匹配】strcmp(sub_41ACF0(str), cmd) == 0 —— GM 命令分发的基本砖。
bool /*thiscall*/ sub_43BCF0(void *this, const char *pArg2)
{
  return strcmp((const char *)sub_41ACF0(this), pArg2) == 0;
}



// ------------------------------------------------------------
// 0x43BD50 sub_43BD50
// ------------------------------------------------------------
char /*thiscall*/ sub_43BD50(int this, int pArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int fld_60; // ebx
  int fld_602; // eax
  int fld_6022; // edi
  int v11; // eax
  int v12; // edi
  int pThis_94; // ebx
  bool fld_90; // zf
  int fld_48; // eax
  int fld_482; // ecx
  int fld_5C2; // ebx
  int pThis_4; // eax
  int v19; // ebx
  int fld_5C22; // ecx
  int fld_483; // eax
  bool v23; // [esp+17h] [ebp+Bh]
  int v24; // [esp+1Ch] [ebp+10h]

  if ( pArg2 == 4 )
  {
    fld_60 = sub_69C500(*(uint32_t *)(this + 96));
    sub_69C440(nArg4);
    sub_69C4A0(nArg5);
    sub_69C360(nArg3, nArg6);
    fld_602 = sub_69C500(*(uint32_t *)(this + 96));
    fld_6022 = fld_602;
    if ( fld_602 > 8 )
      sub_43B9D0((uint32_t *)this, fld_602 - 8);
    v11 = fld_6022 - fld_60;
    if ( fld_6022 - fld_60 > 0 )
    {
      v12 = 43;
      v24 = v11;
      do
      {
        pThis_94 = sub_699000(this + 148);
        *(uint32_t *)(this + 4 * (v12 + sub_69C500(*(uint32_t *)(this + 96)))) = pThis_94;
        --v12;
        LOBYTE(v11) = --v24;
      }
      while ( v24 != 0 );
    }
  }
  else
  {
    fld_90 = *(uint32_t *)(this + 144) == pArg2;
    v23 = false;
    if ( fld_90 )
    {
      if ( *(uint8_t *)(this + 1474) != 0 )
      {
        fld_48 = sub_69C6A0(*(uint32_t *)(this + 72));
        fld_482 = *(uint32_t *)(this + 72);
      }
      else
      {
        fld_48 = sub_69C6A0(*(uint32_t *)(this + 56));
        fld_482 = *(uint32_t *)(this + 56);
      }
      v23 = sub_69C690(fld_482) == fld_48;
    }
    sub_69C440(nArg4);
    sub_69C4A0(nArg5);
    LOBYTE(v11) = sub_69C360(nArg3, nArg6);
    if ( *(uint32_t *)(this + 144) == pArg2 )
    {
      fld_5C2 = *(uint8_t *)(this + 1474) != 0 ? 20 : 8;
      pThis_4 = sub_69C500(*(uint32_t *)(this + 4 * pArg2 + 76)) - fld_5C2;
      v19 = 0;
      fld_5C22 = *(uint8_t *)(this + 1474) != 0 ? *(uint32_t *)(this + 72) : *(uint32_t *)(this + 56);
      LOBYTE(v19) = pThis_4 <= 0;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_5C22 + 32))(fld_5C22, pThis_4 & (v19 - 1));
      LOBYTE(v11) = v23;
      if ( v23 )
      {
        if ( *(uint8_t *)(this + 1474) != 0 )
          fld_483 = sub_69C6A0(*(uint32_t *)(this + 72));
        else
          fld_483 = sub_69C6A0(*(uint32_t *)(this + 56));
        LOBYTE(v11) = sub_69C680(fld_483);
      }
    }
  }
  return v11;
}



// ------------------------------------------------------------
// 0x43BEE0 sub_43BEE0
// ------------------------------------------------------------
// 【播报上屏】(聊天窗宿主, 文本, 颜色, 0, -1) —— 物品/GM/系统消息的统一上屏出口。
int /*thiscall*/ sub_43BEE0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int v5; // eax

  v5 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v5 == 3 || v5 == 4 || v5 == 6 )
    return sub_43BD50(4, nArg2, nArg3, nArg4, nArg5);
  else
    return sub_43BD50(*(this + 36), nArg2, nArg3, nArg4, nArg5);
}



// ------------------------------------------------------------
// 0x43BF40 sub_43BF40
// ------------------------------------------------------------
int /*thiscall*/ sub_43BF40(int *this, const char *pArg2)
{
  int v3; // esi
  char *v4; // eax
  int v5; // eax
  char Buffer[256]; // [esp+Ch] [ebp-104h] BYREF
  int dword_796E502; // [esp+10Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  v3 = sub_429870((int **)dword_8F8500, pArg2);
  if ( v3 == 0 )
  {
    v4 = sub_422E70(328);
    sprintf(Buffer, v4, pArg2);
    v5 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v5 == 3 || v5 == 4 || v5 == 6 )
      sub_43BD50((int)this, 4, (int)Buffer, -6567706, 0, -1);
    else
      sub_43BD50((int)this, *(this + 36), (int)Buffer, -6567706, 0, -1);
  }
  return v3;
}



// ------------------------------------------------------------
// 0x43BFF0 sub_43BFF0
// ------------------------------------------------------------
char /*stdcall*/ sub_43BFF0(int pArg1)
{
  int v1; // ecx
  int v3; // ebx
  int v4; // edi

  v1 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v1 == 4 )
    return 1;
  if ( v1 == 6 )
  {
    v3 = *((int16_t *)dword_8F7C48 + 10 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 76) + 1);
    v4 = *((int16_t *)dword_8F7C48 + 10 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 76));
    if ( sub_41A5E0(pArg1 + 53) >= v4 && sub_41A5E0(pArg1 + 53) <= v3 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x43C060 sub_43C060
// ------------------------------------------------------------
int /*thiscall*/ sub_43C060(int this, int nArg2, int nArg3)
{
  sub_426BD0((uint8_t *)this);
  *(uint32_t *)this = &vftbl_nengine__CNEdit;
  *(uint8_t *)(this + 136) = 0;
  *(uint32_t *)(this + 132) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 140) = 0;
  *(uint8_t *)(this + 144) = 1;
  *(uint8_t *)(this + 146) = 0;
  *(uint8_t *)(this + 145) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint8_t *)(this + 164) = 0;
  *(uint32_t *)(this + 160) = &vftbl_nengine__CNString;
  sub_402A50();
  *(uint8_t *)(this + 184) = 0;
  *(uint32_t *)(this + 180) = &vftbl_nengine__CNString;
  sub_402A50();
  *(uint8_t *)(this + 204) = 0;
  *(uint32_t *)(this + 200) = &vftbl_nengine__CNString;
  sub_402A50();
  sub_69AB50(this);
  nengine__CNEdit__vmt20(nArg2, nArg3);
  return this;
}



// ============================================================
// §28 nengine UI 控件（0x43C150-0x43C960）
//   CNEdit·CNFrame·CNTextBox·CNSlider·CNScroll·CNVSlider·CNVScroll
// ============================================================
// ------------------------------------------------------------
// 0x43C150 nengine__CNEdit__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nengine__CNEdit__vmt0(void *Block, char pszArg2)
{
  sub_43C180();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C180 sub_43C180
// ------------------------------------------------------------
int /*thiscall*/ sub_43C180(int this)
{
  *(uint32_t *)this = &vftbl_nengine__CNEdit;
  nengine__CNEdit__vmt8();
  *(uint32_t *)(this + 200) = &vftbl_nengine__CNString;
  sub_402A60(this + 200);
  *(uint32_t *)(this + 200) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 204) = 0;
  *(uint32_t *)(this + 180) = &vftbl_nengine__CNString;
  sub_402A60(this + 180);
  *(uint32_t *)(this + 180) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 184) = 0;
  *(uint32_t *)(this + 160) = &vftbl_nengine__CNString;
  sub_402A60(this + 160);
  *(uint32_t *)(this + 160) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 164) = 0;
  *(uint32_t *)(this + 132) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 136) = 0;
  return sub_426C90((void **)this);
}



// ------------------------------------------------------------
// 0x43C250 sub_43C250
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_43C250(uint8_t *this, int nArg2, int nArg3)
{
  sub_426BD0(this);
  *(uint32_t *)this = &vftbl_nengine__CNFrame;
  sub_69C6B0(this);
  nengine__CNFrame__vmt20(nArg2, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x43C2B0 nengine__CNFrame__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nengine__CNFrame__vmt0(void *Block, char pszArg2)
{
  sub_43C2E0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C2E0 sub_43C2E0
// ------------------------------------------------------------
int /*thiscall*/ sub_43C2E0(void **this)
{
  *this = &vftbl_nengine__CNFrame;
  nengine__CNFrame__vmt8();
  return sub_426C90(this);
}



// ------------------------------------------------------------
// 0x43C330 sub_43C330
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_43C330(uint8_t *this, int nArg2, int nArg3)
{
  sub_426BD0(this);
  *(uint32_t *)this = &vftbl_nengine__CNTextBox;
  sub_69C2D0(this);
  nengine__CNTextBox__vmt20(nArg2, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x43C390 nengine__CNTextBox__vmt0
// ------------------------------------------------------------
void */*thiscall*/ nengine__CNTextBox__vmt0(void *Block, char pszArg2)
{
  sub_43C3C0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C3C0 sub_43C3C0
// ------------------------------------------------------------
int /*thiscall*/ sub_43C3C0(void **this)
{
  *this = &vftbl_nengine__CNTextBox;
  nengine__CNTextBox__vmt8();
  return sub_426C90(this);
}



// ------------------------------------------------------------
// 0x43C410 sub_43C410
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_43C410(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7, int nArg8)
{
  sub_426BD0(this);
  *this = &vftbl_nengine__CNButton;
  sub_69C780(this);
  nengine__CNButton__vmt20(nArg2, nArg3, nArg4, nArg5, nArg6, nArg7, nArg8);
  return this;
}



// ------------------------------------------------------------
// 0x43C480 sub_43C480
// ------------------------------------------------------------
void /*thiscall*/ sub_43C480(void **this)
{
  *this = &vftbl_nengine__CNButton;
  nengine__CNButton__vmt8();
  sub_426C90(this);
}



// ------------------------------------------------------------
// 0x43C4D0 sub_43C4D0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_43C4D0(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  sub_426BD0(this);
  *(uint32_t *)this = &vftbl_nengine__CNSlider;
  sub_69CA20(this);
  nengine__CNSlider__vmt20(nArg2, nArg3, nArg4);
  return this;
}



// ------------------------------------------------------------
// 0x43C530 sub_43C530
// ------------------------------------------------------------
int /*thiscall*/ sub_43C530(void **this)
{
  *this = &vftbl_nengine__CNSlider;
  nengine__CNSlider__vmt8();
  return sub_426C90(this);
}



// ------------------------------------------------------------
// 0x43C580 nengine__CNSlider__vmt0
// ------------------------------------------------------------
void **/*thiscall*/ nengine__CNSlider__vmt0(void **Block, char pszArg2)
{
  sub_43C530(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C5B0 sub_43C5B0
// ------------------------------------------------------------
int /*thiscall*/ sub_43C5B0(void **this)
{
  *this = &vftbl_nengine__CNScroll;
  nengine__CNScroll__vmt8();
  return sub_426C90(this);
}



// ------------------------------------------------------------
// 0x43C600 nengine__CNScroll__vmt0
// ------------------------------------------------------------
void **/*thiscall*/ nengine__CNScroll__vmt0(void **Block, char pszArg2)
{
  sub_43C5B0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C630 sub_43C630
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_43C630(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  sub_426BD0(this);
  *(uint32_t *)this = &vftbl_nengine__CNScroll;
  sub_69C5D0(this);
  *(uint32_t *)this = &vftbl_nengine__CNVScroll;
  sub_69C5D0(this);
  nengine__CNVScroll__vmt24(nArg2, nArg3, nArg4);
  return this;
}



// ------------------------------------------------------------
// 0x43C6B0 nengine__CNVSlider__vmt0
// ------------------------------------------------------------
void **/*thiscall*/ nengine__CNVSlider__vmt0(void **Block, char pszArg2)
{
  sub_43C6E0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C6E0 sub_43C6E0
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_43C6E0(void **this)
{
  return sub_43C530(this);
}



// ------------------------------------------------------------
// 0x43C6F0 nengine__CNVScroll__vmt0
// ------------------------------------------------------------
void **/*thiscall*/ nengine__CNVScroll__vmt0(void **Block, char pszArg2)
{
  sub_43C720(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x43C720 sub_43C720
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_43C720(void **this)
{
  return sub_43C5B0(this);
}



// ------------------------------------------------------------
// 0x43C730 sub_43C730
// ------------------------------------------------------------
int /*thiscall*/ sub_43C730(int this)
{
  int pThis_374; // edi
  int result; // eax
  int i; // [esp+Ch] [ebp-4h]

  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 228) = 0;
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  *(uint32_t *)(this + 248) = 0;
  *(uint32_t *)(this + 252) = 0;
  *(uint8_t *)(this + 256) = 1;
  *(uint32_t *)(this + 288) = 0;
  sub_4015C0((void *)szPassword, 0);
  *(uint8_t *)(this + 1532) = 0;
  *(uint32_t *)(this + 1788) = 3;
  *(uint16_t *)(this + 1792) = -1;
  *(uint8_t *)(this + 1794) = 0;
  *(uint8_t *)(this + 320) = 0;
  pThis_374 = this + 884;
  for ( i = 20; i != 0; --i )
  {
    sub_4015C0((void *)szPassword, 0);
    sub_4015C0((void *)szPassword, 0);
    pThis_374 += 28;
    result = i - 1;
  }
  *(uint8_t *)(this + 1454) = 0;
  *(uint8_t *)(this + 1462) = 0;
  *(uint8_t *)(this + 1466) = 0;
  *(uint8_t *)(this + 1455) = 0;
  *(uint8_t *)(this + 1459) = 0;
  *(uint8_t *)(this + 1467) = 0;
  *(uint8_t *)(this + 1460) = 0;
  *(uint8_t *)(this + 1456) = 0;
  *(uint8_t *)(this + 1464) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint8_t *)(this + 1473) = 0;
  *(uint8_t *)(this + 1475) = 0;
  *(uint8_t *)(this + 1474) = 0;
  *(uint32_t *)(this + 1444) = 0;
  *(uint32_t *)(this + 1448) = 0;
  *(uint8_t *)(this + 1452) = 0;
  *(uint8_t *)(this + 1453) = 1;
  *(uint8_t *)(this + 1457) = 1;
  *(uint8_t *)(this + 1461) = 1;
  *(uint8_t *)(this + 1465) = 1;
  *(uint8_t *)(this + 1469) = 1;
  *(uint8_t *)(this + 1458) = 1;
  *(uint8_t *)(this + 1470) = 1;
  *(uint8_t *)(this + 1463) = 1;
  *(uint8_t *)(this + 1471) = 1;
  *(uint8_t *)(this + 1468) = 1;
  *(uint8_t *)(this + 1472) = 1;
  *(uint32_t *)(this + 4) = -1;
  return result;
}



// ============================================================
// §29 CNRDChatting 聊天模块（0x43C960-0x43D900）
// ============================================================
// ------------------------------------------------------------
// 0x43C960 sub_43C960
// ------------------------------------------------------------
const char */*thiscall*/ sub_43C960(int this, const char *pArg2, int nArg3, int nArg4, char *Src)
{
  int fld_48; // eax
  int nArg32; // esi
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  const char *result; // eax
  unsigned int nLen; // ebx
  int v13; // eax
  int i; // esi
  int v15; // [esp+1Ch] [ebp+10h]

  if ( (uint16_t)nArg4 == (uint16_t)word_77F804 )
  {
    if ( *(uint8_t *)(this + 1474) != 0 )
      fld_48 = sub_69C6A0(*(uint32_t **)(this + 72));
    else
      fld_48 = sub_69C6A0(*(uint32_t **)(this + 56));
    sub_69C680(fld_48);
  }
  nArg32 = nArg3;
  if ( nArg3 == 0 )
  {
    v8 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v8 == 3 || v8 == 4 || v8 == 6 )
    {
      sub_43BD50(4, pArg2, -6567706, 0, -1);
    }
    else
    {
      do
        sub_43BD50(nArg32++, pArg2, -6567706, 0, -1);
      while ( nArg32 <= 4 );
    }
    return (const char *)sub_432EA0("CHAT_MESSAGE", -1, 0, 0);
  }
  v9 = sub_429830(nArg4);
  v10 = v9;
  if ( v9 != 0 )
  {
    if ( *(uint32_t *)(v9 + 40) < 0x10u )
      result = (const char *)(v9 + 20);
    else
      result = *(const char **)(v9 + 20);
  }
  else
  {
    result = "Someone";
  }
  if ( nArg3 == 4 )
    result = (const char *)sub_422E70(1850);
  if ( v10 != 0 || nArg3 == 6 || nArg3 == 8 || nArg3 == 4 )
  {
    switch ( nArg3 )
    {
      case 2:
        v15 = -1190552;
        break;
      case 6:
        v15 = -701185;
        goto LABEL_33;
      case 8:
        result = Src;
        v15 = -16739585;
        break;
      default:
        v15 = -8934503;
        if ( nArg3 != 1 )
          v15 = -1;
        break;
    }
    Src = (char *)result;
LABEL_33:
    sprintf(byte_8F8768, "%s : %s", Src, pArg2);
    nLen = strlen(Src) + 3;
    v13 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v13 == 3 || v13 == 4 || v13 == 6 )
    {
      sub_43BD50(4, byte_8F8768, v15, nLen, nArg3);
    }
    else
    {
      for ( i = 0; i < 4; ++i )
      {
        switch ( nArg3 )
        {
          case 2:
            if ( *(uint8_t *)(i + this + 1457) != 0 )
              sub_43BD50(i, byte_8F8768, v15, nLen, 2);
            break;
          case 6:
            if ( *(uint8_t *)(i + this + 1461) != 0 )
              sub_43BD50(i, byte_8F8768, v15, nLen, 6);
            break;
          case 8:
            if ( *(uint8_t *)(i + this + 1465) != 0 )
              sub_43BD50(i, byte_8F8768, v15, nLen, 8);
            break;
          case 1:
            if ( *(uint8_t *)(i + this + 1469) != 0 )
              sub_43BD50(i, byte_8F8768, v15, nLen, 1);
            break;
          case 3:
            if ( *(uint8_t *)(i + this + 1453) != 0 )
              sub_43BD50(i, byte_8F8768, v15, nLen, 3);
            break;
          case 4:
            off_77F3FC((char *)&byte_6C5718, byte_8F8768);
            sub_43BD50(i, byte_8F8768, v15, nLen, 4);
            break;
          default:
            if ( *(uint8_t *)(i + this + 1453) != 0 )
              sub_43BD50(i, byte_8F8768, v15, nLen, nArg3);
            break;
        }
      }
      nArg32 = nArg3;
    }
    if ( nArg32 == 1 )
      sub_4015C0(Src, strlen(Src));
    return (const char *)sub_432EA0("CHAT_MESSAGE", -1, 0, 0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x43CC10 CNRDChatting__vmt0
// ------------------------------------------------------------
char /*userpurge*/ sub_43CC10@<al>(int pArg1@<ecx>, char pszArg2@<dil>, int pArg3)
{
  int v4; // ecx
  LONG y; // eax
  int v6; // edx
  int v7; // ecx
  bool v8; // cc
  int v9; // edx
  int v10; // edx
  bool v11; // cc
  int v12; // ecx
  int v13; // edi
  int v14; // eax
  uint64_t v15; // rax
  int v16; // ecx
  int v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // ebx
  int v23; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  unsigned int v27; // ecx
  int v28; // eax
  int v29; // eax
  int v30; // ebx
  int v31; // eax
  char *v32; // eax
  uint32_t *v33; // eax
  int v34; // eax
  int v35; // eax
  unsigned int v36; // ecx
  int v37; // eax
  char *v38; // eax
  int v39; // eax
  int v40; // edi
  int v41; // eax
  int v42; // eax
  int v43; // ebx
  int v44; // eax
  int v45; // eax
  signed int i; // edi
  int pObj7; // eax
  int pObj; // eax
  LONG x; // ebx
  int pObj9; // eax
  int pObj10; // eax
  int pObj4; // eax
  int pObj8; // eax
  int pObj11; // eax
  int pObj12; // eax
  int v56; // edi
  int pObj5; // eax
  int pObj6; // eax
  int pObj3; // eax
  int pObj14; // eax
  int pObj2; // eax
  int pObj13; // eax
  int pObj15; // eax
  LONG v64; // edi
  int v66; // [esp-8h] [ebp-44h]
  int v68; // [esp+8h] [ebp-34h]
  int v69; // [esp+Ch] [ebp-30h]
  int v70; // [esp+Ch] [ebp-30h]
  int v71; // [esp+Ch] [ebp-30h]
  char v72[4]; // [esp+10h] [ebp-2Ch] BYREF
  uint32_t v73[7]; // [esp+14h] [ebp-28h] BYREF
  int v74; // [esp+38h] [ebp-4h]
  int v75; // [esp+44h] [ebp+8h]
  unsigned int v76; // [esp+44h] [ebp+8h]
  int v77; // [esp+44h] [ebp+8h]
  int v78; // [esp+44h] [ebp+8h]
  int v79; // [esp+44h] [ebp+8h]
  LONG v80; // [esp+44h] [ebp+8h]

  v73[6] = dword_796E50;
  v4 = *(uint32_t *)(dword_8F7A24 + 12);
  LOBYTE(y) = pArg3;
  if ( pArg3 == *(uint32_t *)(pArg1 + 12) && v4 != 2 && v4 != 5 )
  {
    if ( *(uint8_t *)(pArg1 + 1474) == 0 )
    {
      v6 = *(uint32_t *)(pArg1 + 16);
      LOBYTE(y) = pt.x;
      if ( *(uint8_t *)(v6 + 16) != 0 )
      {
        if ( *(uint8_t *)(pArg1 + 1473) != 0 )
        {
          if ( pt.x < 2 || (pt.x > 319 || pt.y < 35 || pt.y > 195) && (pt.x > 54 || pt.y < 196 || pt.y > 287) )
          {
            *(uint8_t *)(v6 + 16) = 0;
            LOBYTE(y) = sub_43BC60(0);
            v7 = *(uint32_t *)(pArg1 + 20);
            *(uint8_t *)(pArg1 + 1473) = 0;
            *(uint8_t *)(v7 + 16) = 0;
            return y;
          }
        }
        else if ( pt.x < 2 || pt.x > 319 || pt.y < 35 || pt.y > 195 )
        {
          *(uint8_t *)(v6 + 16) = 0;
          LOBYTE(y) = sub_43BC60(0);
          *(uint8_t *)(*(uint32_t *)(pArg1 + 20) + 16) = 0;
          return y;
        }
LABEL_34:
        *(uint8_t *)(*(uint32_t *)(pArg1 + 20) + 16) = 0;
        return y;
      }
      if ( *(uint8_t *)(pArg1 + 1473) != 0 )
      {
        if ( pt.x < 2 )
          goto LABEL_34;
        if ( pt.x <= 319 && pt.y >= 35 && pt.y <= 195 )
        {
LABEL_33:
          *(uint8_t *)(v6 + 16) = 1;
          y = *(uint32_t *)(pArg1 + 12);
          *(uint32_t *)(y + 28) = 0;
          *(uint32_t *)(y + 32) = 0;
          goto LABEL_34;
        }
        if ( pt.x > 54 || pt.y < 196 )
          goto LABEL_34;
        v8 = pt.y <= 287;
      }
      else
      {
        if ( pt.x < 2 || pt.x > 319 || pt.y < 35 )
          goto LABEL_34;
        v8 = pt.y <= 195;
      }
      if ( !v8 )
        goto LABEL_34;
      goto LABEL_33;
    }
    v9 = *(uint32_t *)(pArg1 + 20);
    LOBYTE(y) = pt.x;
    if ( *(uint8_t *)(v9 + 16) != 0 )
    {
      if ( *(uint8_t *)(pArg1 + 1473) != 0 )
      {
        if ( pt.x < 2 || (pt.x > 319 || pt.y < 35 || pt.y > 387) && (pt.x > 54 || pt.y < 388 || pt.y > 479) )
        {
          *(uint8_t *)(v9 + 16) = 0;
          LOBYTE(y) = sub_43BC60(0);
          v10 = *(uint32_t *)(pArg1 + 16);
          *(uint8_t *)(pArg1 + 1473) = 0;
          *(uint8_t *)(v10 + 16) = 0;
          return y;
        }
      }
      else if ( pt.x < 2 || pt.x > 319 || pt.y < 35 || pt.y > 387 )
      {
        *(uint8_t *)(v9 + 16) = 0;
        LOBYTE(y) = sub_43BC60(0);
        *(uint8_t *)(*(uint32_t *)(pArg1 + 16) + 16) = 0;
        return y;
      }
LABEL_64:
      *(uint8_t *)(*(uint32_t *)(pArg1 + 16) + 16) = 0;
      return y;
    }
    if ( *(uint8_t *)(pArg1 + 1473) != 0 )
    {
      if ( pt.x < 2 )
        goto LABEL_64;
      if ( pt.x <= 319 && pt.y >= 35 && pt.y <= 387 )
      {
LABEL_63:
        *(uint8_t *)(v9 + 16) = 1;
        y = *(uint32_t *)(pArg1 + 12);
        *(uint32_t *)(y + 28) = 0;
        *(uint32_t *)(y + 32) = 0;
        goto LABEL_64;
      }
      if ( pt.x > 54 || pt.y < 388 )
        goto LABEL_64;
      v11 = pt.y <= 479;
    }
    else
    {
      if ( pt.x < 2 || pt.x > 319 || pt.y < 35 )
        goto LABEL_64;
      v11 = pt.y <= 387;
    }
    if ( !v11 )
      goto LABEL_64;
    goto LABEL_63;
  }
  v12 = *(uint32_t *)(pArg1 + 16);
  if ( pArg3 != v12 && pArg3 != *(uint32_t *)(pArg1 + 20) )
  {
    if ( pArg3 != *(uint32_t *)(pArg1 + 120) )
      return y;
    v13 = *(uint32_t *)(pArg1 + 284);
    v14 = sub_699000(pArg1 + 260);
    v15 = (uint64_t)sub_4049C0(0.0, 255.0, v14, v13);
    if ( *(uint8_t *)(pArg1 + 256) == 0 )
      LODWORD(v15) = 255 - v15;
    if ( (uint32_t)v15 == 0 )
      goto LABEL_100;
    switch ( *(uint32_t *)(pArg1 + 288) )
    {
      case 0:
        *(uint32_t *)(*(uint32_t *)(pArg1 + 136) + 128) = -1;
        break;
      case 1:
        *(uint32_t *)(*(uint32_t *)(pArg1 + 136) + 128) = -1190552;
        break;
      case 2:
        *(uint32_t *)(*(uint32_t *)(pArg1 + 136) + 128) = -701185;
        break;
      case 3:
        *(uint32_t *)(*(uint32_t *)(pArg1 + 136) + 128) = -16739585;
        break;
      default:
        break;
    }
    v16 = *(uint32_t *)(pArg1 + 128);
    v17 = (uint8_t)v15 << 24;
    v69 = *(uint32_t *)(v16 + 20);
    v75 = *(uint32_t *)(v16 + 24);
    v18 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x23u);
    sub_43B560(v69, v75, v18, 1065353216, 1065353216, 0, v17 | 0xFFFFFF, 1333788672, 1333788672);
    v76 = 2 * *(uint32_t *)(pArg1 + 288) + 36;
    if ( (uint8_t)sub_43BCB0(*(uint32_t *)(pArg1 + 132)) != 0 )
      ++v76;
    v19 = *(uint32_t *)(pArg1 + 132);
    v70 = *(uint32_t *)(v19 + 24);
    v68 = *(uint32_t *)(v19 + 20);
    v20 = sub_418DD0(*(uint32_t **)(pArg1 + 140), v76);
    sub_43B560(v68, v70, v20, 1065353216, 1065353216, 0, v17 | 0xFFFFFF, 1333788672, 1333788672);
    if ( (uint8_t)sub_69AC60(*(uint32_t *)(pArg1 + 136)) != 0 )
    {
      v21 = *(uint32_t *)(pArg1 + 132);
      v22 = *(uint32_t *)(v21 + 24);
      v77 = *(uint32_t *)(v21 + 20);
      v23 = sub_69AC70(*(uint32_t *)(pArg1 + 136));
      sub_464740(v77 + 15, v22 - 150, v23 + 10, 11, 0, 0);
    }
    if ( (uint8_t)sub_423340(pArg1 + 292, szPassword) != 0 )
    {
      if ( *(uint8_t *)(pArg1 + 320) != 0 )
        goto LABEL_87;
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
      if ( *(uint32_t *)(pArg1 + 316) < 0x10u )
        v24 = pArg1 + 296;
      else
        v24 = *(uint32_t *)(pArg1 + 296);
      v78 = *(uint32_t *)dword_79C0B0;
      v25 = sub_422E70(276);
      (*(void (/*cdecl*/ **)(int, int, int, unsigned int, int, int))(v78 + 80))(
        dword_79C0B0,
        93,
        402,
        (unsigned int)&unk_9BC8E6 | v17,
        v25,
        v24);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      *(uint32_t *)(*(uint32_t *)(pArg1 + 136) + 128) = -6567706;
    }
    if ( *(uint8_t *)(pArg1 + 320) == 0 )
    {
LABEL_97:
      if ( *(uint8_t *)(pArg1 + 1475) != 0 )
      {
        v39 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x11u);
        sub_43B560(59, 319, v39, 1065353216, 1065353216, 0, -1, 1333788672, 1333788672);
        v40 = sub_43BC20(pArg1);
        if ( v40 != -1 )
        {
          v41 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x12u);
          sub_43B560(61, 17 * v40 + 322, v41, 1065353216, 1065353216, 0, -2130706433, 1333788672, 1333788672);
        }
      }
LABEL_100:
      LOBYTE(y) = sub_43BCB0(*(uint32_t *)(pArg1 + 128));
      if ( (uint8_t)y != 0 )
      {
        LOBYTE(y) = sub_69AC60(*(uint32_t *)(pArg1 + 136));
        if ( (uint8_t)y == 0 )
        {
          v42 = sub_422E70(279);
          LOBYTE(y) = sub_4649B0(59, 396, -1, -16777216, 1, v42, 0, 0, 1600, 0);
        }
      }
      return y;
    }
LABEL_87:
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_790700);
    v26 = 28 * *(uint32_t *)(pArg1 + 1444);
    v27 = *(uint32_t *)(v26 + pArg1 + 348);
    v28 = v26 + pArg1 + 324;
    if ( v27 < 0x10 )
      v29 = v28 + 4;
    else
      v29 = *(uint32_t *)(v28 + 4);
    v30 = *(uint32_t *)dword_79C0B0;
    v66 = v29;
    v31 = sub_422E70(277);
    (*(void (/*cdecl*/ **)(int, int, int, unsigned int, int, int))(v30 + 80))(
      dword_79C0B0,
      93,
      402,
      (unsigned int)&unk_9BC8E6 | v17,
      v31,
      v66);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    if ( *(uint8_t *)(pArg1 + 1452) == 0 )
    {
      sub_401690((int)v72, (size_t *)(28 * *(uint32_t *)(pArg1 + 1444) + pArg1 + 324));
      v74 = 0;
      v32 = (char *)sub_422E70(278);
      sub_402410((std::_String_base *)v72, v32);
      v33 = (uint32_t *)v73[0];
      if ( v73[5] < 0x10u )
        v33 = v73;
      v34 = (*(int (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v33);
      sub_69A5F0(*(uint32_t **)(pArg1 + 136), v34 + 93, 402);
      v35 = 28 * *(uint32_t *)(pArg1 + 1444);
      v36 = *(uint32_t *)(v35 + pArg1 + 908);
      v37 = v35 + pArg1 + 884;
      if ( v36 < 0x10 )
        v38 = (char *)(v37 + 4);
      else
        v38 = *(char **)(v37 + 4);
      sub_69BD90(*(uint32_t *)(pArg1 + 136), v38, pszArg2);
      *(uint8_t *)(pArg1 + 1452) = 1;
      v74 = -1;
      sub_501490(v72);
    }
    goto LABEL_97;
  }
  v43 = *(uint32_t *)(pArg3 + 20) + 36;
  v44 = *(uint32_t *)(pArg3 + 24);
  if ( pArg3 == v12 )
    v45 = v44 + 144;
  else
    v45 = v44 + 336;
  v79 = v45;
  v71 = 0;
  for ( i = 19; i < 39; i += 4 )
  {
    if ( *(uint32_t *)(pArg1 + 144) == v71 )
    {
      pObj7 = sub_418DD0(*(uint32_t **)(pArg1 + 140), i);
      if ( pObj7 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v43, v79, dword_79C0B0);
    }
    pObj = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x2Cu);
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v43, v79, dword_79C0B0);
    v43 += 45;
    ++v71;
  }
  LOBYTE(y) = *(uint8_t *)(pArg1 + 1473);
  if ( (uint8_t)y != 0 )
  {
    y = pt.y;
    x = pt.x;
    v80 = pt.y;
    if ( *(uint8_t *)(pArg1 + 1474) != 0 )
      goto LABEL_147;
    if ( pt.x >= 2 && (pt.x <= 319 && pt.y >= 35 && pt.y <= 195 || pt.x <= 54 && pt.y >= 198 && pt.y <= 287) )
    {
      sub_69A5F0(*(uint32_t **)(pArg1 + 112), 2, 198);
      pObj9 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0xFu);
      if ( pObj9 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj9 + 128))(
          pObj9,
          2,
          198,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          -1,
          1333788672,
          1333788672);
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1453) != 0 )
      {
        pObj10 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x10u);
        if ( pObj10 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj10 + 128))(
            pObj10,
            11,
            208,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1457) != 0 )
      {
        pObj4 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x10u);
        if ( pObj4 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(
            pObj4,
            11,
            224,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1461) != 0 )
      {
        pObj8 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x10u);
        if ( pObj8 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj8 + 128))(
            pObj8,
            11,
            240,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1465) != 0 )
      {
        pObj11 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x10u);
        if ( pObj11 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj11 + 128))(
            pObj11,
            11,
            256,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1469) != 0 )
      {
        pObj12 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x10u);
        if ( pObj12 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj12 + 128))(
            pObj12,
            11,
            272,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      v56 = sub_43BBC0(pArg1);
      if ( v56 != -1 )
      {
        pObj5 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x12u);
        if ( pObj5 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(
            pObj5,
            1,
            16 * v56 + 202,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -2130706433,
            1333788672,
            1333788672);
      }
      y = v80;
    }
    if ( *(uint8_t *)(pArg1 + 1474) != 0 )
    {
LABEL_147:
      if ( x < 2 )
        return y;
      if ( x <= 319 && y >= 35 && y <= 387 )
        goto LABEL_152;
    }
    if ( x >= 2 && x <= 54 && y >= 390 && y <= 479 )
    {
LABEL_152:
      sub_69A5F0(*(uint32_t **)(pArg1 + 112), 2, 390);
      pObj6 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0xFu);
      if ( pObj6 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj6 + 128))(
          pObj6,
          2,
          390,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          -1,
          1333788672,
          1333788672);
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1453) != 0 )
      {
        pObj3 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x10u);
        if ( pObj3 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(
            pObj3,
            11,
            400,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1457) != 0 )
      {
        pObj14 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x10u);
        if ( pObj14 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj14 + 128))(
            pObj14,
            11,
            416,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1461) != 0 )
      {
        pObj2 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x10u);
        if ( pObj2 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(
            pObj2,
            11,
            432,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1465) != 0 )
      {
        pObj13 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x10u);
        if ( pObj13 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj13 + 128))(
            pObj13,
            11,
            448,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 144) + pArg1 + 1469) != 0 )
      {
        pObj15 = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x10u);
        if ( pObj15 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj15 + 128))(
            pObj15,
            11,
            464,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1,
            1333788672,
            1333788672);
      }
      y = sub_43BBC0(pArg1);
      v64 = y;
      if ( y != -1 )
      {
        y = sub_418DD0(*(uint32_t **)(pArg1 + 140), 0x12u);
        if ( y != 0 )
          LOBYTE(y) = (*(int (/*thiscall*/ **)(LONG, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)y + 128))(
                        y,
                        1,
                        16 * v64 + 394,
                        dword_79C0B0,
                        1065353216,
                        1065353216,
                        0,
                        -2130706433,
                        1333788672,
                        1333788672);
      }
    }
  }
  return y;
}


// ============================================================
// §30 聊天/杂项大函数（0x43D900-0x43F210）
// ============================================================
// ------------------------------------------------------------
// 0x43D900 sub_43D900
// ------------------------------------------------------------
char */*thiscall*/ sub_43D900(uint32_t *this, char *Str, int nArg3, int nArg4, char *Src)
{
  int v5; // eax
  int v6; // ecx
  int pObj2; // esi
  int v8; // eax
  int16_t v9; // ax
  int v10; // eax
  char *result; // eax
  int v12; // eax
  int v13; // eax
  const char *psz; // eax
  int pObj; // eax

  if ( nArg3 != 1 || (uint16_t)nArg4 != (uint16_t)word_77F804 )
  {
    sub_43C960((int)this, Str, nArg3, nArg4, Src);
    if ( nArg3 == 0 )
      goto LABEL_20;
  }
  v5 = sub_429830((uint32_t *)dword_8F8500, nArg4);
  if ( v5 != 0 )
  {
    v6 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v6 == 1 || v6 == 2 )
    {
      pObj2 = *(uint32_t *)(v5 + 192);
LABEL_12:
      if ( pObj2 != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2);
        sub_50EF20(v8, Str, 0, -1);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 68))(pObj2);
        sub_50EAA0(Str);
      }
      goto LABEL_14;
    }
    if ( v6 == 3 || v6 == 4 || v6 == 6 )
    {
      pObj2 = *(uint32_t *)(v5 + 196);
      goto LABEL_12;
    }
  }
LABEL_14:
  v9 = *(uint16_t *)(dword_8F8538 + 4);
  if ( v9 == -1 )
    goto LABEL_20;
  if ( (uint16_t)nArg4 == (uint16_t)word_77F804 )
  {
    v10 = 0;
  }
  else
  {
    if ( (uint16_t)nArg4 != v9 )
      goto LABEL_20;
    v10 = 1;
  }
  sub_50EF20(*(uint32_t *)(*(uint32_t *)(*(this + 2) + 64) + 4 * v10 + 220), Str, 0, -1);
LABEL_20:
  result = (char *)sub_4BE170();
  if ( result != nullptr )
  {
    v12 = sub_4BE170();
    result = (char *)sub_4BE190(v12);
    if ( result != nullptr )
    {
      if ( (result = (char *)dword_8F7A24, *(uint32_t *)(dword_8F7A24 + 12) == 3) && nArg3 == 2 || nArg3 == 3 )
      {
        v13 = sub_4BE170();
        psz = (const char *)sub_4BE190(v13);
        result = strstr(Str, psz);
        if ( result != nullptr )
        {
          pObj = sub_4BE170();
          return (char *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 4))(pObj);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x43DA50 sub_43DA50
// ------------------------------------------------------------
int /*thiscall*/ sub_43DA50(int this, CHAR *uArg2, char *Format)
{
  char *psz; // eax
  void *p_Block; // eax
  int v6; // esi
  int result; // eax
  char v8; // [esp+0h] [ebp-38h]
  uint8_t v9[4]; // [esp+Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+10h] [ebp-28h] BYREF
  int v11; // [esp+20h] [ebp-18h]
  unsigned int v12; // [esp+24h] [ebp-14h]
  int dword_796E502; // [esp+28h] [ebp-10h]
  int v14; // [esp+34h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( uArg2 != nullptr && uArg2 != szPassword && sub_43BF40((int *)this, uArg2) != 0 )
    sub_4015C0(uArg2, strlen(uArg2));
  else
    sub_4015C0((void *)szPassword, 0);
  if ( sub_40BF00((std::_String_base *)(this + 292), 0, *(uint32_t *)(this + 312), szPassword, 0) != 0 )
  {
    v12 = 15;
    v11 = 0;
    LOBYTE(Block) = 0;
    sub_4014D0((std::_String_base *)v9, this + 292, 0, -1);
    v14 = 0;
    psz = sub_422E70(294);
    sub_4022F0((std::_String_base *)v9, psz, strlen(psz));
    p_Block = Block;
    if ( v12 < 0x10 )
      p_Block = &Block;
    v6 = (*(int (/*thiscall*/ **)(int, void *))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, p_Block);
    sub_69A5F0(*(uint32_t **)(this + 136), v6 + 93, 402);
    *(uint32_t *)(*(uint32_t *)(this + 136) + 108) = 475 - v6;
    v14 = -1;
    if ( v12 >= 0x10 )
      j__free(Block);
    v12 = 15;
    v11 = 0;
    LOBYTE(Block) = 0;
  }
  else
  {
    sub_69A5F0(*(uint32_t **)(this + 136), 93, 402);
    *(uint32_t *)(*(uint32_t *)(this + 136) + 108) = 475;
  }
  result = (int)Format;
  if ( Format != nullptr )
    return sub_69BD90(*(uint32_t *)(this + 136), Format, v8);
  return result;
}



// ------------------------------------------------------------
// 0x43DBE0 sub_43DBE0
// ------------------------------------------------------------
char /*thiscall*/ sub_43DBE0(uint32_t *this)
{
  int fld_e34; // ecx
  int fld_e72; // eax
  int v4; // esi
  char *v5; // eax
  int v6; // edi
  int nLen; // edi
  char *v8; // eax
  char *v9; // eax
  uint32_t *pThis_1C2; // edi
  char *pFound; // eax
  char *v12; // eax
  char *v13; // eax
  char *v14; // eax
  char *v15; // eax
  char *v16; // eax
  char *v17; // eax
  char *v18; // eax
  char *Source; // [esp+8h] [ebp-8Ch]
  int psz; // [esp+Ch] [ebp-88h]
  int v22; // [esp+Ch] [ebp-88h]
  char Destination[128]; // [esp+10h] [ebp-84h] BYREF
  int dword_796E502; // [esp+90h] [ebp-4h]

  fld_e34 = *(this + 34);
  dword_796E502 = dword_796E50;
  LOBYTE(fld_e72) = *(uint8_t *)(fld_e34 + 220);
  if ( (uint8_t)fld_e72 == 0 )
    return fld_e72;
  v4 = sub_69B740(fld_e34);
  if ( strstr((const char *)v4, "/w ") == (char *)v4 || strstr((const char *)v4, "/W ") == (char *)v4 )
  {
    psz = 3;
    v6 = 3;
  }
  else
  {
    v5 = sub_422E70(321);
    if ( (uint8_t)sub_43B600(v4, 0, v5, 0) == 0 )
      goto LABEL_11;
    v6 = 4;
    psz = 4;
  }
  Source = (char *)(v6 + v4);
  if ( *(uint8_t *)(v6 + v4) == 32 || (nLen = v6 + 1) >= strlen((const char *)v4) )
  {
LABEL_11:
    if ( strstr((const char *)v4, "/r ") == (char *)v4 || strstr((const char *)v4, "/R ") == (char *)v4 )
    {
      v22 = 3;
    }
    else
    {
      v8 = sub_422E70(322);
      if ( strstr((const char *)v4, v8) != (char *)v4 )
        goto LABEL_23;
      v22 = 4;
    }
    if ( sub_40BF00((std::_String_base *)(this + 449), 0, *(this + 454), szPassword, 0) != 0 )
    {
      if ( *(this + 455) < 0x10u )
        pThis_1C2 = this + 450;
      else
        pThis_1C2 = (uint32_t *)*(this + 450);
      sub_43DA50(this, pThis_1C2, v4 + v22);
    }
    else
    {
      v9 = sub_422E70(323);
      sub_43BEE0(this, (int)v9, -6567706, 0, -1);
      sub_69BD90(*(this + 34), (char *)szPassword);
    }
LABEL_23:
    if ( (*(this + 72) != 1 || sub_40BF00((std::_String_base *)(this + 73), 0, *(this + 78), szPassword, 0) != 0)
      && (strstr((const char *)v4, "/p ") == (char *)v4
       || strstr((const char *)v4, "/P ") == (char *)v4
       || (pFound = sub_422E70(324), strstr((const char *)v4, pFound) == (char *)v4)) )
    {
      if ( sub_40BF00((std::_String_base *)(this + 73), 0, *(this + 78), szPassword, 0) != 0 )
        sub_43DA50(this, 0, 0);
      if ( *(this + 72) != 1
        && sub_429830((uint16_t)word_77F804) != 0
        && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) != 0 )
      {
        *(this + 72) = 1;
      }
      v18 = sub_422E70(325);
      if ( strstr((const char *)v4, v18) == (char *)v4 )
        goto LABEL_48;
    }
    else
    {
      if ( *(this + 72) == 2
        || strstr((const char *)v4, "/g ") != (char *)v4
        && (uint8_t)sub_43B600(v4, 0, "/G ", 0) == 0
        && (v12 = sub_422E70(326), (uint8_t)sub_43B600(v4, 0, v12, 0) == 0) )
      {
        if ( *(this + 72) != 3
          && ((uint8_t)sub_43B600(v4, 0, "/m ", 0) != 0
           || (uint8_t)sub_43B600(v4, 0, "/M ", 0) != 0
           || (v14 = sub_422E70(1521), (uint8_t)sub_43B600(v4, 0, v14, 0) != 0)) )
        {
          *(this + 72) = 3;
          v15 = sub_422E70(1521);
          if ( (uint8_t)sub_43B600(v4, 0, v15, 0) == 0 )
            goto LABEL_57;
        }
        else
        {
          fld_e72 = *(this + 72);
          if ( fld_e72 == 0 )
            return fld_e72;
          if ( (uint8_t)sub_43B600(v4, 0, "/a ", 0) == 0 && (uint8_t)sub_43B600(v4, 0, "/A ", 0) == 0 )
          {
            v16 = sub_422E70(3003);
            LOBYTE(fld_e72) = sub_43B600(v4, 0, v16, 0);
            if ( (uint8_t)fld_e72 == 0 )
              return fld_e72;
          }
          *(this + 72) = 0;
          v17 = sub_422E70(3003);
          if ( (uint8_t)sub_43B600(v4, 0, v17, 0) == 0 )
            goto LABEL_57;
        }
LABEL_48:
        LOBYTE(fld_e72) = sub_69BD90(*(this + 34), (char *)(v4 + 4));
        return fld_e72;
      }
      if ( sub_429830((uint16_t)word_77F804) != 0
        && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 120) != 0 )
      {
        *(this + 72) = 2;
      }
      v13 = sub_422E70(327);
      if ( strstr((const char *)v4, v13) == (char *)v4 )
        goto LABEL_48;
    }
LABEL_57:
    LOBYTE(fld_e72) = sub_69BD90(*(this + 34), (char *)(v4 + 3));
    return fld_e72;
  }
  while ( *(uint8_t *)(nLen + v4) != 32 )
  {
    if ( ++nLen >= strlen((const char *)v4) )
      goto LABEL_11;
  }
  strncpy(Destination, Source, nLen - psz);
  Destination[nLen - psz] = 0;
  sub_40BE20("\n.......6 <%s><%s>", (char)Destination);
  LOBYTE(fld_e72) = sub_43DA50(this, Destination, nLen + v4 + 1);
  return fld_e72;
}


// ------------------------------------------------------------
// 0x43E150 sub_43E150
// ------------------------------------------------------------
int /*thiscall*/ sub_43E150(int this, void *Block)
{
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  int fld_8C; // eax
  int fld_8C2; // eax
  uint8_t *pMem2; // eax
  uint8_t *v8; // eax
  uint32_t *pThis_1C; // ebx
  uint8_t *pMem3; // eax
  uint32_t *pMem32; // edi
  char *v12; // eax
  int v13; // edi
  uint8_t *pMem4; // ebx
  uint8_t *pMem5; // ebx
  uint8_t *pMem6; // eax
  uint32_t *pMem62; // edi
  int fld_8C4; // ebx
  uint8_t *pMem7; // edi
  int fld_34; // ebx
  uint8_t *pMem8; // eax
  uint32_t *pMem82; // edi
  int fld_8C5; // ebx
  uint8_t *pMem9; // eax
  uint32_t *pMem92; // edi
  int fld_44; // ebx
  uint32_t *pThis_4C; // edi
  uint8_t *pMem10; // eax
  uint32_t *pMem102; // ebx
  uint32_t *pMem1022; // ecx
  uint8_t *pMem11; // eax
  uint8_t *v32; // eax
  uint8_t *pMem12; // eax
  uint32_t *pMem122; // edi
  uint32_t *pMem1222; // ecx
  uint8_t *pMem13; // eax
  uint8_t *v37; // eax
  uint8_t *pMem14; // eax
  uint8_t *v39; // eax
  uint8_t *pMem15; // eax
  uint32_t *pMem152; // edi
  int fld_8C6; // ebx
  uint8_t *pMem16; // eax
  uint32_t *pMem162; // edi
  int fld_8C7; // ebx
  uint8_t *pMem17; // eax
  uint32_t *pMem172; // edi
  int fld_8C8; // ebx
  uint8_t *pMem18; // eax
  uint8_t *v50; // eax
  uint32_t *v51; // eax
  uint8_t *pMem19; // eax
  uint8_t *v53; // eax
  uint8_t *pMem20; // eax
  uint8_t *v55; // eax
  int v56; // eax
  int v57; // eax
  int *pThis_1C2; // ecx
  int v59; // edi
  bool v60; // dl
  int fld_4C; // edi
  int fld_4C2; // eax
  BOOL v63; // ebx
  int fld_48; // eax
  int fld_8C3; // [esp+10h] [ebp-20h]
  int v67; // [esp+10h] [ebp-20h]
  int v68; // [esp+10h] [ebp-20h]
  int fld_2C; // [esp+10h] [ebp-20h]
  int fld_3C; // [esp+10h] [ebp-20h]
  char *Blocka; // [esp+38h] [ebp+8h]
  uint32_t *Blockb; // [esp+38h] [ebp+8h]
  void *Blockd; // [esp+38h] [ebp+8h]
  void *Blocke; // [esp+38h] [ebp+8h]
  int Blockc; // [esp+38h] [ebp+8h]

  *(uint32_t *)(this + 8) = Block;
  *(uint32_t *)(this + 140) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 92);
  pMem = operator new(0x68u);
  if ( pMem != nullptr )
    v4 = sub_426BD0(pMem);
  else
    v4 = nullptr;
  *(uint32_t *)(this + 12) = v4;
  sub_69A5F0(v4, 2, 35);
  *(uint32_t *)(*(uint32_t *)(this + 12) + 68) = this;
  if ( operator new(0x6Cu) != nullptr )
    fld_8C = sub_43C250(*(uint32_t *)(this + 140), 0);
  else
    fld_8C = 0;
  *(uint32_t *)(this + 16) = fld_8C;
  *(uint32_t *)(fld_8C + 28) = 317;
  *(uint32_t *)(fld_8C + 32) = 180;
  *(uint32_t *)(*(uint32_t *)(this + 16) + 68) = this;
  if ( operator new(0x6Cu) != nullptr )
    fld_8C2 = sub_43C250(*(uint32_t *)(this + 140), 1);
  else
    fld_8C2 = 0;
  *(uint32_t *)(this + 20) = fld_8C2;
  *(uint32_t *)(fld_8C2 + 28) = 317;
  *(uint32_t *)(fld_8C2 + 32) = 352;
  *(uint32_t *)(*(uint32_t *)(this + 20) + 68) = this;
  *(uint8_t *)(*(uint32_t *)(this + 20) + 16) = 0;
  pMem2 = operator new(0x68u);
  if ( pMem2 != nullptr )
    v8 = sub_426BD0(pMem2);
  else
    v8 = nullptr;
  *(uint32_t *)(this + 24) = v8;
  *((uint32_t *)v8 + 7) = 180;
  *((uint32_t *)v8 + 8) = 18;
  sub_69A840(*(uint32_t *)(this + 24));
  sub_69A840(*(uint32_t *)(this + 24));
  Blocka = nullptr;
  pThis_1C = (uint32_t *)(this + 28);
  do
  {
    pMem3 = operator new(0x84u);
    pMem32 = pMem3;
    if ( pMem3 != nullptr )
    {
      fld_8C3 = *(uint32_t *)(this + 140);
      sub_426BD0(pMem3);
      *pMem32 = &nengine::CNButton::`vftable';
      sub_69C780(v11);
      sub_69C7B0(v66, (char *)v9 - 8 - this, (char *)v9 - 9 - this, (char *)v9 - 7 - this, (char *)v9 - 6 - this, 0, 0);
    }
    else
    {
      v11 = nullptr;
    }
    *v9 = v11;
    sub_69A840(v11);
    sub_69A840(*v9);
    v12 = Blocka;
    if ( Blocka == (char *)2 || Blocka == (char *)3 )
      *(uint8_t *)(*v9 + 17) = 0;
    ++v9;
    ++Blocka;
  }
  while ( (int)(v12 + 1) < 4 );
  v13 = 4;
  Blockb = (uint32_t *)(this + 60);
  do
  {
    v14 = operator new(0x84u);
    if ( v14 != nullptr )
    {
      v67 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v14);
      *(uint32_t *)v14 = &nengine::CNButton::`vftable';
      sub_69C780(pMem4);
      sub_69C7B0(v67, v13, v13, v13 + 1, v13, 0, 0);
    }
    else
    {
      pMem4 = nullptr;
    }
    *(Blockb - 4) = pMem4;
    pMem5 = operator new(0x84u);
    if ( pMem5 != nullptr )
    {
      v68 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(pMem5);
      *(uint32_t *)pMem5 = &nengine::CNButton::`vftable';
      sub_69C780(v15);
      sub_69C7B0(v68, v13, v13, v13 + 1, v13, 0, 0);
    }
    else
    {
      v15 = nullptr;
    }
    *Blockb = v15;
    v13 += 2;
    ++Blockb;
  }
  while ( v13 < 8 );
  v16 = operator new(0x88u);
  v17 = v16;
  if ( v16 != nullptr )
  {
    v18 = *(uint32_t *)(this + 140);
    sub_426BD0(v16);
    *v17 = &nengine::CNSlider::`vftable';
    sub_69CA20(pMem62);
    sub_69CA50(fld_8C4, 6, 8);
    *pMem62 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v17 = nullptr;
  }
  *(uint32_t *)(this + 52) = v17;
  v19 = operator new(0x74u);
  if ( v19 != nullptr )
  {
    v20 = *(uint32_t *)(this + 52);
    Blockd = *(void **)(this + 48);
    v69 = *(uint32_t *)(this + 44);
    sub_426BD0(v19);
    *(uint32_t *)v19 = &nengine::CNScroll::`vftable';
    sub_69C5D0(pMem7);
    *(uint32_t *)pMem7 = &nengine::CNVScroll::`vftable';
    sub_69C5D0(v19);
    sub_69CD70(v69, Blockd, v20);
  }
  else
  {
    v19 = nullptr;
  }
  *(uint32_t *)(this + 56) = v19;
  sub_69A5F0(v19, 302, 10);
  sub_69A840(*(uint32_t *)(this + 56));
  v21 = operator new(0x88u);
  v22 = v21;
  if ( v21 != nullptr )
  {
    v23 = *(uint32_t *)(this + 140);
    sub_426BD0(v21);
    *v22 = &nengine::CNSlider::`vftable';
    sub_69CA20(pMem82);
    sub_69CA50(fld_8C5, 7, 8);
    *pMem82 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v22 = nullptr;
  }
  *(uint32_t *)(this + 68) = v22;
  v24 = operator new(0x74u);
  v25 = v24;
  if ( v24 != nullptr )
  {
    v26 = *(uint32_t *)(this + 68);
    Blocke = *(void **)(this + 64);
    v70 = *(uint32_t *)(this + 60);
    sub_426BD0(v24);
    *v25 = &nengine::CNScroll::`vftable';
    sub_69C5D0(pMem92);
    *pMem92 = &nengine::CNVScroll::`vftable';
    sub_69C5D0(v25);
    sub_69CD70(v70, Blocke, v26);
  }
  else
  {
    v25 = nullptr;
  }
  *(uint32_t *)(this + 72) = v25;
  sub_69A5F0(v25, 302, 10);
  sub_69A840(*(uint32_t *)(this + 72));
  sub_69A5F0(*(uint32_t **)(this + 16), 2, 35);
  sub_69A5F0(*(uint32_t **)(this + 20), 2, 35);
  sub_69A840(*(uint32_t *)(this + 16));
  sub_69A840(*(uint32_t *)(this + 20));
  v27 = (uint32_t *)(this + 76);
  for ( Blockc = 4; Blockc != 0; --Blockc )
  {
    v28 = operator new(0x6Cu);
    v29 = v28;
    if ( v28 != nullptr )
    {
      sub_426BD0(v28);
      *v29 = &nengine::CNTextBox::`vftable';
      sub_69C2D0(pMem102);
      sub_69C520(290, 2048);
      pMem1022 = pMem102;
    }
    else
    {
      pMem1022 = nullptr;
    }
    *pThis_4C = pMem1022;
    sub_69A5F0(pMem1022, 8, 46);
    sub_69C420(4);
    sub_69C460(1);
    sub_69C480(-16777216);
    sub_69C4C0(dword_99FCCC);
    *(uint32_t *)(*pThis_4C + 68) = this;
    sub_69A840(*pThis_4C++);
  }
  pMem11 = operator new(0x68u);
  if ( pMem11 != nullptr )
    v32 = sub_426BD0(pMem11);
  else
    v32 = nullptr;
  *(uint32_t *)(this + 92) = v32;
  pMem12 = operator new(0x6Cu);
  pMem122 = pMem12;
  if ( pMem12 != nullptr )
  {
    sub_426BD0(pMem12);
    *pMem122 = &nengine::CNTextBox::`vftable';
    sub_69C2D0(v34);
    sub_69C520(330, 2048);
    v35 = v34;
  }
  else
  {
    v35 = nullptr;
  }
  *(uint32_t *)(this + 96) = v35;
  sub_69A5F0(v35, 9, 74);
  sub_69C3E0(20);
  sub_69C420(2);
  sub_69C460(1);
  sub_69C480(-16777216);
  sub_69C4C0(dword_99FCCC);
  sub_69A840(*(uint32_t *)(this + 96));
  v36 = operator new(0x68u);
  if ( v36 != nullptr )
    v37 = sub_426BD0(v36);
  else
    v37 = nullptr;
  *(uint32_t *)(this + 112) = v37;
  *((uint32_t *)v37 + 7) = 52;
  *((uint32_t *)v37 + 8) = 89;
  sub_69A840(*(uint32_t *)(this + 112));
  sub_69A840(*(uint32_t *)(this + 112));
  v38 = operator new(0x68u);
  if ( v38 != nullptr )
    v39 = sub_426BD0(v38);
  else
    v39 = nullptr;
  *(uint32_t *)(this + 116) = v39;
  *((uint32_t *)v39 + 7) = 61;
  *((uint32_t *)v39 + 8) = 70;
  v40 = operator new(0x84u);
  v41 = v40;
  if ( v40 != nullptr )
  {
    v42 = *(uint32_t *)(this + 140);
    sub_426BD0(v40);
    *v41 = &nengine::CNButton::`vftable';
    sub_69C780(pMem152);
    sub_69C7B0(fld_8C6, 9, 10, 10, 9, 0, 0);
  }
  else
  {
    pMem152 = nullptr;
  }
  *(uint32_t *)(this + 100) = pMem152;
  sub_69A840(pMem152);
  sub_69A840(*(uint32_t *)(this + 100));
  pMem16 = operator new(0x84u);
  pMem162 = pMem16;
  if ( pMem16 != nullptr )
  {
    fld_8C7 = *(uint32_t *)(this + 140);
    sub_426BD0(pMem16);
    *pMem162 = &nengine::CNButton::`vftable';
    sub_69C780(v44);
    sub_69C7B0(v45, 11, 12, 12, 11, 0, 0);
  }
  else
  {
    v44 = nullptr;
  }
  *(uint32_t *)(this + 104) = v44;
  sub_69A840(v44);
  sub_69A840(*(uint32_t *)(this + 104));
  v46 = operator new(0x84u);
  v47 = v46;
  if ( v46 != nullptr )
  {
    v48 = *(uint32_t *)(this + 140);
    sub_426BD0(v46);
    *v47 = &nengine::CNButton::`vftable';
    sub_69C780(pMem172);
    sub_69C7B0(fld_8C8, 13, 14, 14, 13, 0, 0);
  }
  else
  {
    pMem172 = nullptr;
  }
  *(uint32_t *)(this + 108) = pMem172;
  sub_69A840(pMem172);
  sub_69A840(*(uint32_t *)(this + 108));
  pMem18 = operator new(0x68u);
  if ( pMem18 != nullptr )
    v50 = sub_426BD0(pMem18);
  else
    v50 = nullptr;
  *(uint32_t *)(this + 120) = v50;
  *((uint32_t *)v50 + 17) = this;
  if ( operator new(0xE4u) != nullptr )
    v51 = (uint32_t *)sub_43C060(1, -1);
  else
    v51 = nullptr;
  *(uint32_t *)(this + 124) = v51;
  sub_69A5F0(v51, 640, 480);
  sub_69A840(*(uint32_t *)(this + 124));
  *(uint8_t *)(*(uint32_t *)(this + 124) + 221) = 1;
  pMem19 = operator new(0x68u);
  if ( pMem19 != nullptr )
    v53 = sub_426BD0(pMem19);
  else
    v53 = nullptr;
  *(uint32_t *)(this + 128) = v53;
  *((uint32_t *)v53 + 7) = 520;
  *((uint32_t *)v53 + 8) = 22;
  sub_69A5F0(*(uint32_t **)(this + 128), 59, 396);
  sub_69A840(*(uint32_t *)(this + 128));
  pMem20 = operator new(0x68u);
  if ( pMem20 != nullptr )
    v55 = sub_426BD0(pMem20);
  else
    v55 = nullptr;
  *(uint32_t *)(this + 132) = v55;
  *((uint32_t *)v55 + 7) = 28;
  *((uint32_t *)v55 + 8) = 16;
  sub_69A5F0(*(uint32_t **)(this + 132), 62, 399);
  sub_69A840(*(uint32_t *)(this + 132));
  if ( operator new(0xE4u) != nullptr )
    v56 = sub_43C060(95, 480);
  else
    v56 = 0;
  *(uint32_t *)(this + 136) = v56;
  *(uint32_t *)(v56 + 128) = -1;
  sub_69A840(*(uint32_t *)(this + 136));
  sub_69A840(*(uint32_t *)(this + 116));
  if ( *(uint8_t *)(this + 256) != 0 )
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(this + 124) + 12);
    dword_79BE54 = dword_79BE4C;
    *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 0;
    *(uint8_t *)(this + 273) = 0;
    *(uint8_t *)(this + 274) = 0;
    sub_698F90(this + 260, 100, 0);
    *(uint8_t *)(this + 256) = 0;
    sub_4BF300(0, 1);
  }
  *(uint8_t *)(this + 161) = 0;
  *(uint8_t *)(this + 162) = 0;
  sub_698F90(this + 148, 0, 0);
  *(uint8_t *)(this + 273) = 0;
  *(uint8_t *)(this + 274) = 0;
  sub_698F90(this + 260, 0, 0);
  *(uint8_t *)(this + 1489) = 0;
  *(uint8_t *)(this + 1490) = 0;
  sub_698F90(this + 1476, 0, 0);
  *(uint8_t *)(this + 1517) = 0;
  *(uint8_t *)(this + 1518) = 0;
  sub_698F90(this + 1504, 0, 0);
  *(uint32_t *)(this + 144) = 0;
  v57 = 0;
  pThis_1C2 = (int *)(this + 28);
  do
  {
    *(uint8_t *)(pThis_1C2[12] + 16) = v57 == 0;
    v59 = *pThis_1C2;
    v60 = v57++ != 0;
    ++pThis_1C2;
    *(uint8_t *)(v59 + 16) = v60;
  }
  while ( v57 < 4 );
  fld_4C = sub_69C3A0(*(uint32_t *)(this + 76));
  fld_4C2 = sub_69C500(*(uint32_t *)(this + 76)) - fld_4C;
  v63 = fld_4C2 <= 0;
  if ( *(uint8_t *)(this + 1474) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 72) + 32))(*(uint32_t *)(this + 72), v63 ? 0 : fld_4C2);
    fld_48 = sub_69C6A0(*(uint32_t **)(this + 72));
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), v63 ? 0 : fld_4C2);
    fld_48 = sub_69C6A0(*(uint32_t **)(this + 56));
  }
  sub_69C680(fld_48);
  return sub_43DA50(this, 0, 0);
}


// ------------------------------------------------------------
// 0x43ECC0 sub_43ECC0
// ------------------------------------------------------------
int /*thiscall*/ sub_43ECC0(int this)
{
  int fld_4C; // edi
  int fld_4C2; // eax
  int fld_48; // eax

  *(uint8_t *)(this + 1532) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 76) + 16) = 1;
  *(uint8_t *)(*(uint32_t *)(this + 28) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 80) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 32) + 16) = 1;
  *(uint8_t *)(*(uint32_t *)(this + 84) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 36) + 16) = 1;
  *(uint8_t *)(*(uint32_t *)(this + 88) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 40) + 16) = 1;
  fld_4C = sub_69C3A0(*(uint32_t *)(this + 76));
  fld_4C2 = sub_69C500(*(uint32_t *)(this + 76)) - fld_4C;
  if ( *(uint8_t *)(this + 1474) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 72) + 32))(*(uint32_t *)(this + 72), fld_4C2 <= 0 ? 0 : fld_4C2);
    fld_48 = sub_69C6A0(*(uint32_t *)(this + 72));
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), fld_4C2 <= 0 ? 0 : fld_4C2);
    fld_48 = sub_69C6A0(*(uint32_t *)(this + 56));
  }
  sub_69C680(fld_48);
  return sub_43DA50(this, nullptr, nullptr);
}



// ------------------------------------------------------------
// 0x43ED90 sub_43ED90
// ------------------------------------------------------------
char /*thiscall*/ sub_43ED90(int this, int nArg2, int nArg3, int nArg4)
{
  const char *psz; // edi
  unsigned int nLen; // eax
  int fld_5DC; // ebx
  int pThis_5C4; // eax
  int pThis_5C42; // ecx
  int fld_5F8; // edi
  int nArg22; // ecx
  int i; // eax
  int v13; // eax
  int nArg32; // ebx
  int v15; // eax
  int v16; // eax
  int nArg42; // edi
  size_t *v18; // ebx
  int j; // edi
  size_t *v20; // eax
  const char *v21; // eax
  int fld_5A8; // eax
  size_t *pThis_144; // edi
  bool v24; // zf
  char *v25; // eax
  char v26; // cl
  size_t *v28; // [esp-Ch] [ebp-21Ch]
  char Buffer[256]; // [esp+Ch] [ebp-204h] BYREF
  char Src[256]; // [esp+10Ch] [ebp-104h] BYREF
  int dword_796E502; // [esp+20Ch] [ebp-4h]

  psz = (const char *)nArg2;
  dword_796E502 = dword_796E50;
  nLen = strlen((const char *)nArg2);
  nArg2 = nLen;
  if ( nLen < 0xFF )
  {
    strcpy(Src, psz);
    fld_5DC = *(uint32_t *)(this + 1500);
    pThis_5C4 = sub_699000(this + 1476);
    pThis_5C42 = this + 1476;
    *(uint8_t *)(this + 1490) = 0;
    *(uint8_t *)(this + 1489) = 0;
    if ( pThis_5C4 < fld_5DC )
    {
      LOBYTE(nLen) = sub_698F90(pThis_5C42, 100, 0);
      return nLen;
    }
    sub_698F90(pThis_5C42, 100, 0);
    fld_5F8 = *(uint32_t *)(this + 1528);
    if ( sub_699000(this + 1504) >= fld_5F8 || (nLen = strcmp((const char *)(this + 1532), Src)) != 0 )
    {
      nArg22 = nArg2;
      for ( i = 0; i < nArg22; ++i )
      {
        if ( Src[i] == 37 )
          Src[i] = 32;
      }
      if ( (*(int (/*thiscall*/ **)(int, uint32_t, char *))(*(uint32_t *)dword_99FD60 + 20))(dword_99FD60, 0, Src) != 0 )
      {
        v13 = sub_422E70(281);
LABEL_12:
        LOBYTE(nLen) = sub_43BEE0((uint32_t *)this, v13, -6567706, 0, -1);
        return nLen;
      }
      nArg32 = nArg3;
      if ( nArg3 == 2 )
      {
        v15 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( (v15 == 1 || v15 == 4 || v15 == 6) && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) == 0 )
        {
          v13 = sub_422E70(282);
          goto LABEL_12;
        }
      }
      else if ( nArg3 == 6 )
      {
        v16 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( (v16 == 1 || v16 == 4 || v16 == nArg3) && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 120) == 0 )
        {
          v13 = sub_422E70(283);
          goto LABEL_12;
        }
      }
      sub_423200(dword_8F7B08, 17);
      HIBYTE(nArg2) = nArg32;
      sub_423290((char *)&nArg2 + 3, 1);
      nArg42 = nArg4;
      nArg2 = nArg4;
      sub_423290(&nArg2, 2);
      nArg2 = 0;
      sub_423290(&nArg2, 4);
      sub_41C100(Src);
      sub_423380(dword_8F7B08);
      if ( nArg32 == 1 )
      {
        v18 = (size_t *)sub_429830(nArg42);
        if ( v18 != nullptr )
        {
          for ( j = 0; j < 4; ++j )
          {
            if ( *(uint8_t *)(this + j + 1469) != 0 )
            {
              if ( v18[10] < 0x10 )
                v20 = v18 + 5;
              else
                v20 = (size_t *)v18[5];
              v28 = v20;
              v21 = (const char *)sub_422E70(284);
              sprintf(Buffer, v21, v28, Src);
              sub_43BD50(j, Buffer, -8934503, 1, -1);
            }
          }
          fld_5A8 = *(uint32_t *)(this + 1448);
          if ( fld_5A8 >= 20 )
          {
            pThis_144 = (size_t *)(this + 324);
            nArg2 = 19;
            do
            {
              sub_4014D0(pThis_144, pThis_144 + 7, 0, 0xFFFFFFFF);
              sub_4014D0(pThis_144 + 140, pThis_144 + 147, 0, 0xFFFFFFFF);
              v24 = nArg2 == 1;
              pThis_144 += 7;
              --nArg2;
            }
            while ( !v24 );
            sub_4014D0((size_t *)(28 * *(uint32_t *)(this + 1448) + this + 296), v18 + 4, 0, 0xFFFFFFFF);
            sub_4015C0((size_t *)(28 * *(uint32_t *)(this + 1448) + this + 856), Src, strlen(Src));
          }
          else
          {
            sub_4014D0((size_t *)(28 * fld_5A8 + this + 324), v18 + 4, 0, 0xFFFFFFFF);
            sub_4015C0((size_t *)(28 * *(uint32_t *)(this + 1448) + this + 884), Src, strlen(Src));
            ++*(uint32_t *)(this + 1448);
          }
          *(uint32_t *)(this + 1444) = *(uint32_t *)(this + 1448) - 1;
        }
        sub_43D900(Src, 1, (uint16_t)word_77F804, nullptr);
        nArg32 = nArg3;
        LOWORD(nArg42) = nArg4;
      }
      v25 = Src;
      do
      {
        v26 = *v25;
        v25[this - (uint32_t)Src + 1532] = *v25;
        ++v25;
      }
      while ( v26 != 0 );
      *(uint32_t *)(this + 1788) = nArg32;
      *(uint16_t *)(this + 1792) = nArg42;
      *(uint8_t *)(this + 1517) = 0;
      *(uint8_t *)(this + 1518) = 0;
      sub_698F90(this + 1504, 1000, 0);
      LOBYTE(nLen) = byte_77F280;
      if ( byte_77F280 != 0 && nArg32 != 1 )
        LOBYTE(nLen) = sub_43D900(Src, nArg32, (uint16_t)word_77F804, nullptr);
    }
  }
  return nLen;
}


// ============================================================
// §31 聊天命令与 GM "//" 分发（0x43F210-0x43F740）
//   0x43F210 分词（首字符 '/'）→ 0x43F740 '//level'·'//add'·'//warroomtime' 等
//   → 两步式发包实战场（sub_423200/423290/423380，见 §5）
// ============================================================
// ------------------------------------------------------------
// 0x43F210 sub_43F210
// ------------------------------------------------------------
// 【聊天命令分词】按 ' ' 切块；首字符非 '/' 放弃（返回原文）；"/OUT" 等与
//   off_6C57B0/off_6C57AC/串285 对照。产出词表供 0x43F740 消费。
int /*cdecl*/ sub_43F210(uint32_t *uArg1, int nArg2, int nArg3, int nArg4)
{
  void **v4; // ecx
  int v5; // esi
  void *v6; // edi
  char *v7; // eax
  void **v8; // esi
  bool v9; // zf
  void **v10; // edi
  void *v11; // edi
  char *v12; // eax
  void *v13; // edi
  char *v14; // eax
  void *v15; // edi
  char *v16; // eax
  char *v17; // ecx
  void *v18; // eax
  void **v19; // edi
  void *v20; // edi
  char *v21; // eax
  void **v22; // edi
  void *v23; // edi
  char *v24; // eax
  void *v25; // edi
  char *v26; // eax
  void *v27; // edi
  char *v28; // eax
  char *v29; // ecx
  void *v30; // eax
  void **v31; // edi
  void *v32; // edi
  char *v33; // eax
  char *v34; // ecx
  void *v35; // eax
  void **v36; // edi
  void *v37; // edi
  char *v38; // eax
  void **v39; // esi
  void **v40; // edi
  void *v42; // esi
  char *v43; // eax
  char *v44; // ecx
  void *v45; // eax
  void **v46; // edi
  void **v47; // edi
  void **v48; // edi
  void **v49; // esi
  char v50[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  void **v52; // [esp+14h] [ebp-14h]
  int v53; // [esp+18h] [ebp-10h]
  int v54; // [esp+24h] [ebp-4h]

  Block = nullptr;
  v52 = nullptr;
  v53 = 0;
  v54 = 0;
  sub_488690(v50, nArg4, " ", 2);
  v4 = (void **)Block;
  if ( Block == nullptr || (v5 = ((char *)v52 - (uint8_t *)Block) >> 2) == 0 )
  {
LABEL_66:
    *uArg1 = 0;
    v54 = -1;
    if ( v4 != nullptr )
    {
      v48 = v52;
      v49 = v4;
      if ( v4 != v52 )
      {
        do
          sub_41B010(v49++);
        while ( v49 != v48 );
        v4 = (void **)Block;
      }
      j__free(v4);
    }
    return nArg4;
  }
  if ( *(uint8_t *)sub_41ACF0(Block) != 47 )
  {
    v4 = (void **)Block;
    goto LABEL_66;
  }
  if ( v5 == 1 )
  {
    if ( sub_43BCF0(Block, (const char *)&off_6C57B0)
      || sub_43BCF0(Block, (const char *)&off_6C57AC)
      || (v6 = Block, v7 = sub_422E70(285), sub_43BCF0(v6, v7)) )
    {
      v8 = (void **)Block;
      v9 = Block == nullptr;
      *uArg1 = 2;
      v54 = -1;
      if ( !v9 )
      {
        v10 = v52;
        if ( v8 != v52 )
        {
          do
            sub_41B010(v8++);
          while ( v8 != v10 );
LABEL_59:
          j__free(Block);
          return nArg4;
        }
        goto LABEL_64;
      }
      return nArg4;
    }
    if ( sub_43BCF0(Block, "/OUT")
      || sub_43BCF0(Block, "/out")
      || (v20 = Block, v21 = sub_422E70(289), sub_43BCF0(v20, v21)) )
    {
      v8 = (void **)Block;
      v9 = Block == nullptr;
      *uArg1 = 4;
      v54 = -1;
      if ( !v9 )
      {
        v22 = v52;
        if ( v8 != v52 )
        {
          do
            sub_41B010(v8++);
          while ( v8 != v22 );
          goto LABEL_59;
        }
LABEL_64:
        j__free(v8);
      }
      return nArg4;
    }
  }
  else if ( v5 == 2 )
  {
    if ( sub_43BCF0(Block, "/j")
      || sub_43BCF0(Block, "/J")
      || (v11 = Block, v12 = sub_422E70(286), sub_43BCF0(v11, v12))
      || (v13 = Block, v14 = sub_422E70(287), sub_43BCF0(v13, v14))
      || (v15 = Block, v16 = sub_422E70(288), sub_43BCF0(v15, v16)) )
    {
      v17 = (char *)Block + 4;
      *uArg1 = 3;
      v18 = (void *)sub_41ACF0(v17);
      sub_406D60(v18);
      v8 = (void **)Block;
      v54 = -1;
      if ( Block != nullptr )
      {
        v19 = v52;
        if ( Block != v52 )
        {
          do
            sub_41B010(v8++);
          while ( v8 != v19 );
          goto LABEL_59;
        }
        goto LABEL_64;
      }
      return nArg4;
    }
    if ( sub_43BCF0(Block, "/v")
      || sub_43BCF0(Block, "/V")
      || (v23 = Block, v24 = sub_422E70(290), sub_43BCF0(v23, v24))
      || (v25 = Block, v26 = sub_422E70(2030), sub_43BCF0(v25, v26))
      || (v27 = Block, v28 = sub_422E70(2031), sub_43BCF0(v27, v28)) )
    {
      v29 = (char *)Block + 4;
      *uArg1 = 5;
      v30 = (void *)sub_41ACF0(v29);
      sub_406D60(v30);
      v8 = (void **)Block;
      v54 = -1;
      if ( Block != nullptr )
      {
        v31 = v52;
        if ( Block != v52 )
        {
          do
            sub_41B010(v8++);
          while ( v8 != v31 );
          goto LABEL_59;
        }
        goto LABEL_64;
      }
      return nArg4;
    }
    if ( sub_43BCF0(Block, (const char *)&off_6C5788)
      || sub_43BCF0(Block, (const char *)&off_6C5784)
      || (v32 = Block, v33 = sub_422E70(291), sub_43BCF0(v32, v33)) )
    {
      v34 = (char *)Block + 4;
      *uArg1 = 6;
      v35 = (void *)sub_41ACF0(v34);
      sub_406D60(v35);
      v8 = (void **)Block;
      v54 = -1;
      if ( Block != nullptr )
      {
        v36 = v52;
        if ( Block != v52 )
        {
          do
            sub_41B010(v8++);
          while ( v8 != v36 );
          goto LABEL_59;
        }
        goto LABEL_64;
      }
      return nArg4;
    }
  }
  if ( *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 112) != 1
    || (v37 = Block, v38 = sub_422E70(292), !sub_43BCF0(v37, v38)) )
  {
    if ( v5 != 2 || !sub_43BCF0(Block, "/target") && (v42 = Block, v43 = sub_422E70(293), !sub_43BCF0(v42, v43)) )
    {
      v8 = (void **)Block;
      v9 = Block == nullptr;
      *uArg1 = 8;
      v54 = -1;
      if ( v9 )
        return nArg4;
      v47 = v52;
      if ( v8 != v52 )
      {
        do
          sub_41B010(v8++);
        while ( v8 != v47 );
        v8 = (void **)Block;
      }
      goto LABEL_64;
    }
    v44 = (char *)Block + 4;
    *uArg1 = 9;
    v45 = (void *)sub_41ACF0(v44);
    sub_406D60(v45);
    v8 = (void **)Block;
    v54 = -1;
    if ( Block != nullptr )
    {
      v46 = v52;
      if ( Block != v52 )
      {
        do
          sub_41B010(v8++);
        while ( v8 != v46 );
        goto LABEL_59;
      }
      goto LABEL_64;
    }
    return nArg4;
  }
  v39 = (void **)Block;
  v9 = Block == nullptr;
  *uArg1 = 7;
  v54 = -1;
  if ( !v9 )
  {
    v40 = v52;
    if ( v39 != v52 )
    {
      do
        sub_41B010(v39++);
      while ( v39 != v40 );
      v39 = (void **)Block;
    }
    j__free(v39);
  }
  return nArg4 + 5;
}


// ------------------------------------------------------------
// 0x43F740 sub_43F740
// ------------------------------------------------------------
// 【GM "//" 命令分发器】'//level up/down' · '//levelto' · '//pvprank' ·
//   '//add skill/item' · '//warroomtime' · '//godqhrdmlans' 等 → 权限门
//   sub_41C290(dword_8F7A24) → 两步式发包实战场：sub_423200(dword_8F7B08, 65) Begin +
//   sub_423290 逐字节 Append + sub_423380 Commit（包 type 65 = GM 命令通道）。
char /*thiscall*/ sub_43F740(uint32_t *this, char *Str)
{
  char *v2; // esi
  int v4; // edi
  uint8_t *Block2; // ecx
  uint8_t *v6; // eax
  uint8_t *v7; // esi
  bool v8; // zf
  const char *v9; // eax
  const char *v10; // eax
  int v11; // eax
  const char *v12; // eax
  int v13; // eax
  void **v14; // esi
  void **v15; // edi
  bool v16; // al
  char v17; // bl
  int v18; // esi
  char *v19; // ecx
  int v20; // edi
  const char *v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  uint32_t *v27; // eax
  void **v28; // edi
  void **v29; // edi
  void **v30; // edi
  const char *v31; // eax
  int v32; // ebx
  const char *v33; // eax
  int v34; // ebx
  void **v35; // edi
  const char *v36; // eax
  int v37; // ebx
  void **v38; // edi
  void **v39; // edi
  const char *v40; // eax
  int v41; // ebx
  const char *v42; // eax
  void **v43; // edi
  const char *v44; // eax
  char *v45; // esi
  void **v46; // edi
  void **v47; // edi
  int v48; // eax
  void **v49; // edi
  int v50; // eax
  int v51; // eax
  int v52; // edi
  int v53; // ebx
  uint8_t *pObj; // esi
  int v55; // eax
  const char *v56; // eax
  char *v57; // esi
  int v58; // eax
  void **v59; // edi
  const char *v60; // eax
  double v61; // st7
  void **v62; // edi
  const char *v63; // eax
  double v64; // st7
  const char *v65; // eax
  const char *v66; // eax
  const char *v67; // eax
  char v68; // al
  int v69; // eax
  int v70; // eax
  int v71; // eax
  int v72; // eax
  int dword_8F7B082; // esi
  const char *v74; // eax
  char v75; // al
  const char *v76; // eax
  int v77; // eax
  int v78; // esi
  char *v79; // edi
  char *v80; // ebx
  void *v81; // eax
  int v82; // eax
  const char *v83; // eax
  const char *v84; // eax
  const char *v85; // eax
  int v86; // eax
  int v88; // [esp+Ch] [ebp-248h]
  int i; // [esp+Ch] [ebp-248h]
  int v91; // [esp+10h] [ebp-244h]
  bool v92; // [esp+17h] [ebp-23Dh]
  char v93[4]; // [esp+18h] [ebp-23Ch] BYREF
  void *Block; // [esp+1Ch] [ebp-238h]
  uint8_t *v95; // [esp+20h] [ebp-234h]
  int v96; // [esp+24h] [ebp-230h]
  char Buffer[512]; // [esp+28h] [ebp-22Ch] BYREF
  char v98[4]; // [esp+228h] [ebp-2Ch] BYREF
  uint32_t *v99; // [esp+22Ch] [ebp-28h] BYREF
  int v100; // [esp+23Ch] [ebp-18h]
  unsigned int v101; // [esp+240h] [ebp-14h]
  int dword_796E502; // [esp+244h] [ebp-10h]
  int v103; // [esp+250h] [ebp-4h]

  v2 = Str;
  dword_796E502 = dword_796E50;
  v4 = 0;
  if ( strstr(Str, "//") != v2 )
    return 0;
  Block = nullptr;
  v95 = nullptr;
  v96 = 0;
  v103 = 0;
  sub_488690(v93, v2, " ", 0);
  Block2 = Block;
  v6 = v95;
  if ( Block != nullptr )
  {
    v4 = (v95 - (uint8_t *)Block) >> 2;
    v88 = v4;
  }
  else
  {
    v88 = 0;
  }
  while ( Block2 == nullptr || (unsigned int)((v6 - Block2) >> 2) < 0xA )
  {
    *(float *)&Str = 0.0;
    sub_41BFE0((void **)&Str, szPassword);
    LOBYTE(v103) = 1;
    if ( Block != nullptr && (v95 - (uint8_t *)Block) >> 2 < (unsigned int)((v96 - (int)Block) >> 2) )
    {
      v7 = v95;
      sub_41FFE0(v95, 1, &Str);
      v95 = v7 + 4;
    }
    else
    {
      sub_4206D0(v95, 1, &Str);
    }
    LOBYTE(v103) = 0;
    sub_41B010((void **)&Str);
    v6 = v95;
    Block2 = Block;
  }
  if ( sub_43BCF0(Block2, "//monitor") )
  {
    *(uint8_t *)(*((uint32_t *)dword_8F8528 + 4) + 508) = *(uint8_t *)(*((uint32_t *)dword_8F8528 + 4) + 508) == 0;
    off_77F3FC((char *)&byte_6C5CE8);
LABEL_241:
    v103 = -1;
    sub_4017E0(v93);
    return 1;
  }
  if ( sub_43BCF0(Block, "//rrs") )
    goto LABEL_241;
  if ( sub_43BCF0(Block, "//rp2p") )
  {
    v8 = byte_97B6D0 != 0;
    byte_97B6D0 = byte_97B6D0 == 0;
    if ( v8 )
      sub_43BEE0(this, (int)"RelayP2p: false", -6567706, 0, -1);
    else
      sub_43BEE0(this, (int)"RelayP2p: true", -6567706, 0, -1);
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//rmark") )
  {
    v8 = byte_98B74E != 0;
    byte_98B74E = byte_98B74E == 0;
    if ( v8 )
      sub_43BEE0(this, (int)"ShowRelayMark: false", -6567706, 0, -1);
    else
      sub_43BEE0(this, (int)"ShowRelayMark: true", -6567706, 0, -1);
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//drop") )
  {
    v9 = (const char *)sub_41ACF0((char *)Block + 4);
    dword_796938 = j__atol(v9);
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//lth") )
  {
    sub_657920(2);
    *(float *)(dword_8F8548 + 24) = (double)dword_79692C * 0.001;
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//ltm") )
  {
    sub_657920(1);
    *(float *)(dword_8F8548 + 24) = (double)dword_79692C * 0.001;
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//ltl") )
  {
    sub_657920(0);
    *(float *)(dword_8F8548 + 24) = (double)dword_79692C * 0.001;
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//lt") )
  {
    v10 = (const char *)sub_41ACF0((char *)Block + 4);
    v11 = j__atol(v10);
    sub_657900(v11);
    *(float *)(dword_8F8548 + 24) = (double)dword_79692C * 0.001;
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//st") )
  {
    if ( sub_43BCF0((char *)Block + 4, (const char *)&off_6C5C4C) )
    {
      *(uint8_t *)(*(uint32_t *)(dword_8F8520 + 1049988) + 2520) = 0;
    }
    else if ( sub_43BCF0((char *)Block + 4, (const char *)&off_6C5C48) )
    {
      *(uint8_t *)(*(uint32_t *)(dword_8F8520 + 1049988) + 2520) = 1;
    }
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//bt") )
  {
    v12 = (const char *)sub_41ACF0((char *)Block + 4);
    v13 = j__atol(v12);
    sub_657260(*(uint32_t *)(dword_8F8520 + 1049988), v13);
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//full") )
  {
    sub_41C1C0(1);
    sub_408FA0(1);
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//normal") )
  {
    sub_41C1C0(0);
    sub_408FA0(0);
    goto LABEL_241;
  }
  if ( sub_43BCF0(Block, "//repel") && *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 112) == 1 )
  {
    if ( v4 <= 2 )
    {
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v15 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v15 );
          v14 = (void **)Block;
        }
LABEL_191:
        j__free(v14);
        return 0;
      }
      return 0;
    }
    v16 = sub_43BCF0((char *)Block + 4, "m_id");
    v17 = 0;
    v18 = 0xFFFF;
    v19 = (char *)Block + 8;
    v92 = v16;
    v20 = 0xFFFF;
    if ( v16 )
    {
      v21 = (const char *)sub_41ACF0(v19);
      v20 = j__atol(v21);
    }
    else
    {
      v22 = sub_41ACF0(v19);
      v23 = sub_429870(v22);
      if ( v23 == 0 )
      {
LABEL_57:
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 12;
        sub_423290((char *)&Str + 3, 1);
        if ( v92 )
        {
          HIBYTE(Str) = 1;
          sub_423290((char *)&Str + 3, 1);
          Str = (char *)v20;
        }
        else
        {
          HIBYTE(Str) = 0;
          sub_423290((char *)&Str + 3, 1);
          Str = (char *)v18;
        }
        sub_423290(&Str, 4);
        sub_423380(dword_8F7B08);
        v101 = 15;
        v100 = 0;
        LOBYTE(v99) = 0;
        LOBYTE(v103) = 2;
        v24 = sub_41ACF0(Block);
        sub_402410(v24);
        sub_402410(" ");
        v25 = sub_41ACF0((char *)Block + 4);
        sub_402410(v25);
        sub_402410(" ");
        v26 = sub_41ACF0((char *)Block + 8);
        sub_402410(v26);
        if ( v17 != 0 )
          sub_402410(" Success");
        else
          sub_402410(" Fail");
        v27 = v99;
        if ( v101 < 0x10 )
          v27 = &v99;
        sub_43BEE0(this, (int)v27, -6567706, 0, -1);
LABEL_240:
        sub_501490(v98);
        goto LABEL_241;
      }
      v18 = *(uint16_t *)(v23 + 4);
    }
    v17 = 1;
    goto LABEL_57;
  }
  if ( sub_43BCF0(Block, "//godqhrdmlans") )
  {
    sub_423200(dword_8F7B08, 65);
    HIBYTE(Str) = 0;
    sub_423290((char *)&Str + 3, 1);
    sub_423380(dword_8F7B08);
    off_77F3FC((char *)&byte_6C5BD8);
    goto LABEL_241;
  }
  if ( !sub_43BCF0(Block, "//level") || !sub_43BCF0((char *)Block + 4, "up") )
  {
    if ( sub_43BCF0(Block, "//level") && sub_43BCF0((char *)Block + 4, "down") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
      {
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 2;
        sub_423290((char *)&Str + 3, 1);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5B90);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v29 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v29 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//levelto") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
      {
        v31 = (const char *)sub_41ACF0((char *)Block + 4);
        v32 = j__atol(v31);
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 7;
        sub_423290((char *)&Str + 3, 1);
        HIBYTE(Str) = v32;
        sub_423290((char *)&Str + 3, 1);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5B68, v32);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v30 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v30 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//pvprank") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && v4 > 1 )
      {
        v33 = (const char *)sub_41ACF0((char *)Block + 4);
        v34 = j__atol(v33);
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 8;
        sub_423290((char *)&Str + 3, 1);
        HIBYTE(Str) = v34;
        sub_423290((char *)&Str + 3, 1);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5B40, v34);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v35 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v35 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//grow") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && v4 > 1 )
      {
        v36 = (const char *)sub_41ACF0((char *)Block + 4);
        v37 = j__atol(v36);
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 3;
        sub_423290((char *)&Str + 3, 1);
        HIBYTE(Str) = v37;
        sub_423290((char *)&Str + 3, 1);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5B20, v37);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v38 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v38 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//clear")
      && sub_43BCF0((char *)Block + 4, "[all]")
      && sub_43BCF0((char *)Block + 8, "skill") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
      {
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 4;
        sub_423290((char *)&Str + 3, 1);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5AE8);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v39 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v39 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//add") && sub_43BCF0((char *)Block + 4, "skill") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && v4 > 3 )
      {
        v40 = (const char *)sub_41ACF0((char *)Block + 8);
        v41 = j__atol(v40);
        v42 = (const char *)sub_41ACF0((char *)Block + 12);
        v91 = j__atol(v42);
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 5;
        sub_423290((char *)&Str + 3, 1);
        HIBYTE(Str) = v41;
        sub_423290((char *)&Str + 3, 1);
        HIBYTE(Str) = v91;
        sub_423290((char *)&Str + 3, 1);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5AB8, v41, v91);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v43 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v43 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//add") && sub_43BCF0((char *)Block + 4, "item") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && v4 > 2 )
      {
        v44 = (const char *)sub_41ACF0((char *)Block + 8);
        v45 = (char *)j__atol(v44);
        sub_423200(dword_8F7B08, 65);
        HIBYTE(Str) = 6;
        sub_423290((char *)&Str + 3, 1);
        Str = v45;
        sub_423290(&Str, 2);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5A90, v45);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v46 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v46 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//no") && sub_43BCF0((char *)Block + 4, "random") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
      {
        v8 = byte_9A05F0 != 0;
        byte_9A05F0 = byte_9A05F0 == 0;
        if ( v8 )
          v48 = sub_422E70(330);
        else
          v48 = sub_422E70(329);
        sub_43BEE0(this, v48, -6567706, 0, -1);
        off_77F3FC((char *)&byte_6C5A5C);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v47 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v47 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//kill") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
      {
        v50 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v50 == 3 || v50 == 6 )
        {
          v51 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
          v52 = sub_425100(*(uint32_t *)(v51 + 104));
          v53 = 0;
          for ( i = v52; v53 < v52; ++v53 )
          {
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
            pObj = (uint8_t *)sub_425A00(v53);
            if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )
            {
              if ( byte_77F280 != 0 )
              {
                (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 732))(pObj, 0, 0, 1);
              }
              else if ( pObj[7801] != 0 )
              {
                sub_423200(dword_8F7B08, 42);
                *(float *)&Str = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 52))(pObj));
                sub_423290(&Str, 2);
                *(float *)&Str = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04));
                sub_423290(&Str, 2);
                sub_423380(dword_8F7B08);
                v52 = i;
              }
              else
              {
                (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pObj + 312))(pObj, 1);
              }
            }
          }
          off_77F3FC((char *)&byte_6C5A38);
          v55 = sub_422E70(331);
          sub_43BEE0(this, v55, -6567706, 0, -1);
        }
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v49 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v49 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//quest") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && *(uint32_t *)(dword_8F7A24 + 12) == 1 && v4 > 1 )
      {
        v56 = (const char *)sub_41ACF0((char *)Block + 4);
        v57 = (char *)j__atol(v56);
        sub_423200(dword_8F7B08, 33);
        Str = v57;
        sub_423290(&Str, 2);
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C5A14);
        v58 = sub_422E70(332);
        sub_43BEE0(this, v58, -6567706, 0, -1);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v59 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v59 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//style") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && *(uint32_t *)(dword_8F7A24 + 12) == 3 && v4 > 1 )
      {
        v60 = (const char *)sub_41ACF0((char *)Block + 4);
        *(float *)&Str = (double)j__atol(v60) * 0.0099999998;
        v61 = sub_43B5C0(dword_99FD58);
        *((float *)dword_99FD58 + 241) = v61 * *(float *)&Str;
        off_77F3FC((char *)&byte_6C59E8);
        sub_43BEE0(this, (int)"//style : setting complete", -6567706, 0, -1);
        goto LABEL_241;
      }
      v14 = (void **)Block;
      v103 = -1;
      if ( Block != nullptr )
      {
        v62 = (void **)v95;
        if ( Block != v95 )
        {
          do
            sub_41B010(v14++);
          while ( v14 != v62 );
          v14 = (void **)Block;
        }
        goto LABEL_191;
      }
      return 0;
    }
    if ( sub_43BCF0(Block, "//technic") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && *(uint32_t *)(dword_8F7A24 + 12) == 3 && v4 > 1 )
      {
        v63 = (const char *)sub_41ACF0((char *)Block + 4);
        *(float *)&Str = (double)j__atol(v63) * 0.0099999998;
        v64 = sub_43B5E0(dword_99FD58);
        *((float *)dword_99FD58 + 242) = v64 * *(float *)&Str;
        off_77F3FC((char *)&byte_6C599C);
        sub_43BEE0(this, (int)"//technic : setting complete", -6567706, 0, -1);
        goto LABEL_241;
      }
    }
    else if ( sub_43BCF0(Block, "//attacked") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && *(uint32_t *)(dword_8F7A24 + 12) == 3 && v4 > 1 )
      {
        v65 = (const char *)sub_41ACF0((char *)Block + 4);
        *(float *)&Str = COERCE_FLOAT(j__atol(v65));
        *((float *)dword_99FD58 + 243) = (float)(int)Str;
        off_77F3FC((char *)&byte_6C5950);
        sub_43BEE0(this, (int)"//attacked : setting complete", -6567706, 0, -1);
        goto LABEL_241;
      }
    }
    else if ( sub_43BCF0(Block, "//upgrade") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
      {
        if ( sub_43BCF0((char *)Block + 4, "success") )
        {
          sub_423200(dword_8F7B08, 65);
          sub_41C0C0(9);
          off_77F3FC(byte_6C58F4);
        }
        else if ( sub_43BCF0((char *)Block + 4, "fail") )
        {
          sub_423200(dword_8F7B08, 65);
          sub_41C0C0(10);
          off_77F3FC(byte_6C58C4);
        }
        else
        {
          if ( !sub_43BCF0((char *)Block + 4, "random") )
            goto LABEL_241;
          sub_423200(dword_8F7B08, 65);
          sub_41C0C0(11);
          off_77F3FC((char *)&byte_6C589C);
        }
        sub_423380(dword_8F7B08);
        v66 = (const char *)sub_41ACF0((char *)Block + 4);
        sprintf(Buffer, "//upgrade %s - ok", v66);
        sub_43BEE0(this, (int)Buffer, -6567706, 0, -1);
        goto LABEL_241;
      }
    }
    else if ( sub_43BCF0(Block, "//warroomtime") )
    {
      if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 && *(uint32_t *)(dword_8F7A24 + 12) == 1 && v4 > 1 )
      {
        sub_423200(dword_8F7B08, 65);
        sub_41C0C0(13);
        v67 = (const char *)sub_41ACF0((char *)Block + 4);
        v68 = j__atol(v67);
        sub_43B4C0(v68);
        sub_423380(dword_8F7B08);
        v69 = sub_41ACF0((char *)Block + 4);
        off_77F3FC((char *)&byte_6C5854, v69);
        sub_43BEE0(this, (int)"//warroomtime", -6567706, 0, -1);
        goto LABEL_241;
      }
    }
    else
    {
      if ( sub_43BCF0(Block, "//mail") )
      {
        v70 = sub_524330();
        sub_523800(v70);
        sub_524AF0(1, 432000, &unk_6C5840, (void *)0x2710, 0);
        v71 = sub_522300((void *)0x699E, 1, 0, 0, -1, 1);
        sub_524AF0(2, 3630, &unk_6C5840, nullptr, v71);
        v72 = sub_522300((void *)0x699E, 1, 0, 0, -1, 1);
        sub_524AF0(3, 180, &unk_6C5840, nullptr, v72);
        sub_44E8D0((char *)dword_8F8528, (void *)0xD, 0, 0);
        goto LABEL_241;
      }
      if ( sub_43BCF0(Block, "//packet") && (uint8_t)sub_41C290(dword_8F7A24) != 0 && v4 > 1 )
      {
        v101 = 15;
        v100 = 0;
        LOBYTE(v99) = 0;
        dword_8F7B082 = dword_8F7B08;
        LOBYTE(v103) = 3;
        v74 = (const char *)sub_41ACF0((char *)Block + 4);
        v75 = j__atol(v74);
        sub_423200(dword_8F7B082, v75);
        v76 = (const char *)sub_41ACF0((char *)Block + 4);
        v77 = j__atol(v76);
        off_77F3FC("commands : %d", v77);
        v78 = 2;
        if ( v4 > 2 )
        {
          v79 = Str;
          v80 = Str;
          do
          {
            if ( v78 % 2 == 1 )
            {
              if ( v79 == (char *)-1 )
              {
                v81 = (void *)sub_41ACF0((char *)Block + 4 * v78);
                sub_406D60(v81);
                v82 = unknown_libname_2(v98);
                sub_41C100(v82);
              }
              else
              {
                if ( (int)v79 > 0 )
                {
                  v84 = (const char *)sub_41ACF0((char *)Block + 4 * v78);
                  v80 = (char *)j__atol(v84);
                }
                if ( v79 == (char *)1 )
                {
                  sub_41C0C0((char)v80);
                  off_77F3FC("WriteByte : %d", 1);
                }
                else if ( v79 == (char *)2 )
                {
                  sub_41C0E0((char)v80);
                }
                else if ( v79 == (char *)4 )
                {
                  sub_43B4C0((char)v80);
                }
                else if ( v79 == (char *)8 )
                {
                  sub_43B4E0((char)v80, (int)v80 >> 31);
                }
              }
              v83 = (const char *)unknown_libname_2(v98);
              off_77F3FC("k : %d\tpacketFieldByteSize : %d\tnumPacket : %d\tstring : %s", v78, v79, v80, v83);
            }
            else
            {
              v85 = (const char *)sub_41ACF0((char *)Block + 4 * v78);
              v79 = (char *)j__atol(v85);
            }
            ++v78;
          }
          while ( v78 < v88 );
        }
        sub_423380(dword_8F7B08);
        off_77F3FC((char *)&byte_6C57B4);
        v86 = sub_422E70(332);
        sub_43BEE0(this, v86, -6567706, 0, -1);
        goto LABEL_240;
      }
    }
    v103 = -1;
    sub_4017E0(v93);
    return 0;
  }
  if ( (uint8_t)sub_41C290(dword_8F7A24) != 0 )
  {
    sub_423200(dword_8F7B08, 65);
    HIBYTE(Str) = 1;
    sub_423290((char *)&Str + 3, 1);
    sub_423380(dword_8F7B08);
    off_77F3FC((char *)&byte_6C5BB4);
    goto LABEL_241;
  }
  v14 = (void **)Block;
  v103 = -1;
  if ( Block != nullptr )
  {
    v28 = (void **)v95;
    if ( Block != v95 )
    {
      do
        sub_41B010(v14++);
      while ( v14 != v28 );
      v14 = (void **)Block;
    }
    goto LABEL_191;
  }
  return 0;
}

