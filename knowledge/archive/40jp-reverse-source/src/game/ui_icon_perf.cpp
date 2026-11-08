// ============================================================
// 【40JP逆向源代码工程】game/ui_icon_perf.cpp
// 模块: UI 图标/快捷栏/性能统计/选角界面/CNEntranceChannel 助手
// 来源: work/dump_combat.txt  区块: 0x460000-0x470000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
// 函数数: 156
// ------------------------------------------------------------
// ★ 性能统计系统归类（统计点全表）：
//   初始化  0x460590 —— 动态解析 psapi.dll!GetProcessMemoryInfo 与
//             Kernel32!GetThreadTimes（内存/线程时间采样入口）
//   重置    0x4605F0 —— 统计对象清零（12 槽 + 计数族，+568=-1 哨兵）
//   采样    sub_405030(n)/sub_4050B0(n)（引擎统计查询，n=槽号）
//   HUD     0x461840 —— 每 1000ms 重采样并逐行绘制到 dword_79C0B0 vt+80：
//             "fps : %03d"（=1000000/微秒帧时长 sub_405030(2)，y=163）
//             "texture size : %0.3f MB"（sub_4050B0(1)×0.00000095367432=1/1048576，y=176）
//             "cached chars : %d"（sub_4050B0(2)，y=189）
//             "traversal : %d usec"（sub_405030(9)，y=202）
// ★ UI 事件锚点（sub_432EA0 事件名 = 字符串自证）：
//   ICON_DROP_TO_QUICKSLOT（0x4633D0 快捷栏拖放）/ SELECT_CHARACTER（0x46BD70
//   选角键盘导航）/ SCROLL_ARROW（CNEntranceModule__vmt4 内滚动）/ CLICK_BUTTON2/4
// ★ 登录链路衔接（docs/13 §6；协议阶段图见 login_channel.cpp 文件头）：
//   CNEntranceModule__vmt4 = 0x46C300 选角模块帧（阶段⑤）；
//   CNEntranceChannel 复位 0x46DE70（+12=6/+16=5 与 connectServer 校验上限一致）；
//   vmt8 = 0x46E1F0 离开清理；reserveConnection = 0x46EAA0（阶段④ 预约）；
//   startTimerForReservedConnectChannel = 0x46E360（500ms tick）；
//   HTTP 频道列表线程 = 0x46EB70 "StartAddress"（"MERONG(0.9/;p)" 校验，
//   结果 dword_98BA5C → retrieveServerInfo 的输入；阶段① 数据源）
// 交叉引用：频道表条目搬运族（0x46ECC0/0x46EF10/0x46E6B0 等）被
//   login_channel.cpp 0x470330 调用；对象注册链 0x4600B0 → worldmap_reward 0x45FE80
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】图标容器与对象注册辅助（0x460070-0x460590）
// 批量对象注册 0x4600B0（→ worldmap_reward 0x45FE80 注册链）。
// ============================================================
// ------------------------------------------------------------
// 0x460070 sub_460070
// ------------------------------------------------------------
// 图标 id 查容器槽（命中返回槽指针，未中尾插 sub_431230）
uint32_t */*thiscall*/ sub_460070(uint32_t *this, int nArg2)  // 实现：图标 id 查容器槽（命中返回槽指针，未中尾插 sub_431230）
{
  uint32_t *fld_e36; // edx
  uint32_t *result; // eax

  fld_e36 = (uint32_t *)*(this + 36);  // this+144 = pFrameList144
  result = (uint32_t *)*(this + 35);  // this+140〔nAdd140(推断)〕
  if ( result == fld_e36 )  // result=this+140 nAdd140
    return (uint32_t *)sub_431230((int)(this + 34), &nArg2);  // 调 uint32 vector push_back
  do
  {
    if ( *result == nArg2 )  // result=this+140 nAdd140
      break;
    ++result;  // result=this+140 nAdd140
  }
  while ( result != fld_e36 );  // result=this+140 nAdd140
  if ( result == fld_e36 )  // result=this+140 nAdd140
    return (uint32_t *)sub_431230((int)(this + 34), &nArg2);  // 调 uint32 vector push_back
  return result;  // result=this+140 nAdd140
}



// ------------------------------------------------------------
// 0x4600B0 sub_4600B0
// ------------------------------------------------------------
// 批量对象注册：源表逐 id 调 worldmap_reward 0x45FE80 入场景表
int /*thiscall*/ sub_4600B0(void *this, int nArg2, int nArg3, int pArg4)  // 实现：批量对象注册：源表逐 id 调 worldmap_reward 0x45FE80 入场景表
{
  int *v4; // esi
  int result; // eax

  if ( pArg4 != 0 )
  {
    v4 = *(int **)(pArg4 + 4);  // pArg4+4〔宿主对象〕
    if ( v4 != nullptr )  // 若 v4 有效（非空）
    {
      result = (*(uint32_t *)(pArg4 + 8) - (int)v4) >> 2;  // pArg4+8〔nSkillRec8(推断)〕
      if ( result != 0 && v4 != *(int **)(pArg4 + 8) )  // pArg4+8〔nSkillRec8(推断)〕
      {
        do
        {
          sub_45FE80((int)this, pArg4, nArg2, nArg3, *v4, 0, 0);  // 调 实体对象注册到演播层
          result = *(uint32_t *)(pArg4 + 8);  // pArg4+8〔nSkillRec8(推断)〕
          ++v4;
        }
        while ( v4 != (int *)result );
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x460110 sub_460110 —— 图标对象换槽（重写槽号后重挂）
// 在槽数组 this+8..+12 中定位 nArg2（未命中先经 vt+36 取结构），旧槽号存于该结构 +8；
// 旧槽号非 6 时先从旧槽表摘除，再把 +8 改写为 nArg3 并尾插新槽表 this+20+4*nArg3。
// 表满转 sub_45F8A0 扩容。用于图标换格与背包搬运。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_460110(uint32_t *this, int nArg2, int nArg3)  // 函数: 图标对象换槽（重写槽号后重挂）
{
  uint32_t *pThis; // esi
  int fld_e2; // ecx
  int v5; // eax
  int pObj; // edi
  int v7; // ecx
  uint32_t *v8; // edx
  int v9; // eax
  int nArg32; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  uint32_t *v14; // esi
  int v15; // eax
  int v16; // ecx
  uint32_t *v17; // edx
  int v18; // ebx
  int v19; // edx
  int v20; // ecx
  unsigned int v21; // esi
  int *pObj2; // eax
  unsigned int result; // eax
  uint32_t *pThis2; // [esp+8h] [ebp-4h]

  pThis = this;
  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  pThis2 = pThis;
  if ( fld_e2 != 0 )  // fld_e2=this+8 物品 id
    v5 = (pThis[3] - fld_e2) >> 2;  // fld_e2=this+8 物品 id
  else
    v5 = 0;
  pObj = nArg2;
  v7 = 0;
  if ( v5 <= 0 )
  {
LABEL_8:
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 36))(nArg2);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
    nArg32 = nArg3;
    *(uint32_t *)(v9 + 8) = nArg3;
  }
  else
  {
    v8 = (uint32_t *)pThis[2];
    while ( *v8 != nArg2 )  // 当 *v8 != nArg2 循环
    {
      ++v7;
      ++v8;
      if ( v7 >= v5 )
        goto LABEL_8;
    }
    nArg32 = nArg3;
  }
  v11 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 36))(pObj) + 8);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  if ( v11 != 6 )
  {
    v12 = 4 * v11;
    v13 = pThis[v12 + 6];
    v14 = &pThis[v12];
    if ( v13 != 0 )
      v15 = (v14[7] - v13) >> 2;
    else
      v15 = 0;
    v16 = 0;
    if ( v15 > 0 )
    {
      v17 = (uint32_t *)v14[6];
      while ( *v17 != pObj )  // 当 *v17 != pObj 循环
      {
        ++v16;
        ++v17;
        if ( v16 >= v15 )
          goto LABEL_20;
      }
      memcpy_0(
        (void *)(v14[6] + 4 * v16),
        (const void *)(v14[6] + 4 * v16 + 4),
        4 * ((v14[7] - (v14[6] + 4 * v16 + 4)) >> 2));
      v14[7] -= 4;
LABEL_20:
      nArg32 = nArg3;
    }
    pThis = pThis2;
  }
  *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 36))(pObj) + 8) = nArg32;  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
  v18 = 4 * nArg32;
  v19 = pThis[v18 + 6];
  v20 = (int)&pThis[v18 + 5];
  if ( v19 != 0 )
    v21 = (pThis[v18 + 7] - v19) >> 2;
  else
    v21 = 0;
  if ( v19 == 0 || v21 >= (*(uint32_t *)(v20 + 12) - v19) >> 2 )
    return sub_45F8A0(v20, *(uint32_t *)(v20 + 8), 1u, &nArg2);  // 调 对象指针表插入（内联 vector insert_n：搬移/填值/扩容三路）
  pObj2 = *(int **)(v20 + 8);
  *pObj2 = pObj;
  result = (unsigned int)(pObj2 + 1);
  *(uint32_t *)(v20 + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x460230 sub_460230 —— 图标槽随机 id 分配（线性探测）
// 自 rand()%0xFFFF 起按 +1 线性探测：sub_45EBE0 查占用、this+35 与 +36 表查重，命中空位即
// sub_460070 登记并返回该 id；绕行一整圈仍无空位则返回 0xFFFF 哨兵。
// ------------------------------------------------------------
int /*thiscall*/ sub_460230(uint32_t *this)  // 函数: 图标槽随机 id 分配（线性探测）
{
  int nRand; // ebx
  int nRand2; // esi
  uint32_t *fld_e36; // ecx
  uint32_t *fld_e35; // eax
  int v7; // [esp+Ch] [ebp-4h]

  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);  // 调用虚函数（虚表槽 +1220）
  nRand = rand() % 0xFFFF;  // 调 以 16 位种子状态递推并返回 15 位结果
  nRand2 = nRand;
  while ( 1 )  // 无限循环
  {
    if ( sub_45EBE0(this, v7, nRand2) == 0 )  // 调 对象查找
    {
      fld_e36 = (uint32_t *)*(this + 36);  // this+144 = pFrameList144
      fld_e35 = (uint32_t *)*(this + 35);  // this+140〔nAdd140(推断)〕
      if ( fld_e35 == fld_e36 )  // fld_e35=this+140 nAdd140
        break;
      do
      {
        if ( *fld_e35 == nRand2 )  // fld_e35=this+140 nAdd140
          break;
        ++fld_e35;  // fld_e35=this+140 nAdd140
      }
      while ( fld_e35 != fld_e36 );  // fld_e35=this+140 nAdd140
      if ( fld_e35 == fld_e36 )  // fld_e35=this+140 nAdd140
        break;
    }
    nRand2 = (nRand2 + 1) % 0xFFFF;
    if ( nRand2 == nRand )
      return 0xFFFF;
  }
  sub_460070(this, nRand2);  // 调 登记并返回该 id
  return nRand2;
}



// ------------------------------------------------------------
// 0x4602C0 sub_4602C0 —— 图标容器批量实例化
// 三条源链 pArg2+40/+52/+108 逐个建对象：图标项 new CNRDPooledObject（284 字节，vftable 自证）
// 或 sub_53A220 取图，数值项 new 0x12C 字节 CNRDObject（off_6C7464 虚表）。
// 一律 sub_45FE80 入场景表并置 +277=1 标记。
// ------------------------------------------------------------
int /*thiscall*/ sub_4602C0(void *this, uint32_t *pArg2)  // 函数: 图标容器批量实例化
{
  uint32_t *pArg22; // ebx
  uint32_t *v3; // eax
  uint32_t *v4; // esi
  int v5; // edx
  int v6; // ebx
  char *v7; // eax
  char *pObj2; // edi
  uint32_t *v9; // eax
  uint32_t *v10; // esi
  int v11; // edi
  uint8_t *pObj3; // ebx
  int result; // eax
  int v14; // ebx
  int v15; // edi
  void *pMem; // eax
  int pObj; // esi
  int ArgList; // [esp+10h] [ebp-1Ch]
  int v19; // [esp+14h] [ebp-18h]
  int v21; // [esp+1Ch] [ebp-10h]
  int v22; // [esp+1Ch] [ebp-10h]

  pArg22 = pArg2;
  v3 = (uint32_t *)pArg2[10];
  v4 = (uint32_t *)*v3;
  v21 = 0;
  if ( (uint32_t *)*v3 != v3 )
  {
    do
    {
      if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
      {
        if ( v4[8] < 0x10u )
          LOBYTE(v5) = (uint8_t)v4 + 12;  // 调 取 16 位值低 8 位
        else
          v5 = v4[3];
        if ( pArg22[76] < 0x10u )
          v6 = sub_431920((uint8_t)pArg22 + 28, v5, 1);  // 调 动画件构造（文件名版）
        else
          v6 = sub_431920(pArg22[71], v5, 1);  // 调 动画件构造（文件名版）
      }
      else
      {
        v6 = 0;
      }
      v7 = (char *)sub_44B6C0(284);  // 调 CRT 一次性池初始化 2（池 &unk_98B6F8）
      pObj2 = v7;
      if ( v7 != nullptr )  // 若 v7 有效（非空）
      {
        sub_44E0D0(v7, v6, 0);  // 调 CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)pObj2 = &CNRDPooledObject::`vftable';  // vftable 复位
      }
      else
      {
        pObj2 = nullptr;
      }
      *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj2 + 36))(pObj2) + 8) = v4[9];  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
      sub_45FE80((int)this, (int)pObj2, 0, v21, (int)pObj2, 0, 0);  // 调 实体对象注册到演播层
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj2 + 112))(pObj2, v4[10], v4[11], v4[12]);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
      pObj2[277] = 1;
      v4 = (uint32_t *)*v4;
      ++v21;
      pArg22 = pArg2;
    }
    while ( v4 != (uint32_t *)pArg2[10] );
  }
  v9 = (uint32_t *)pArg22[13];
  v10 = (uint32_t *)*v9;
  v11 = 0;
  if ( (uint32_t *)*v9 != v9 )
  {
    do
    {
      pObj3 = sub_53A220(v10[2], nullptr);  // size=17574
      sub_45FE80((int)this, v11, 33, v11, (int)pObj3, 0, 0);  // 调 实体对象注册到演播层
      (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj3 + 112))(pObj3, v10[3], v10[4], v10[5]);  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
      pObj3[277] = 1;
      v10 = (uint32_t *)*v10;
      ++v11;
    }
    while ( v10 != (uint32_t *)pArg2[13] );
    pArg22 = pArg2;
  }
  result = pArg22[27];
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = (pArg22[28] - result) / 20;
    v19 = result;
  }
  else
  {
    v19 = 0;
  }
  v22 = 0;
  if ( v19 > 0 )
  {
    v14 = 0;
    do
    {
      v15 = pArg2[27];
      if ( *(uint32_t *)(v14 + v15) != 32 )
      {
        pMem = operator new(0x12Cu);  // operator new 分配 300 字节
        pObj = (int)pMem;
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
        {
          ArgList = *(uint32_t *)(v14 + v15);
          sub_42AAB0(pMem);  // 调 CNRDObject 构造（三内嵌 CNTimer）
          *(uint32_t *)pObj = &off_6C7464;  // 写 vftable 指针 off_6C7464
          sub_567760(pObj);  // 调 13 行小辅助
          sub_568310((int *)pObj, ArgList);  // 调 对话表现（56CFE0/568240/4924C0/4918E0）
        }
        else
        {
          pObj = 0;
        }
        sub_45FE80((int)this, v15, 34, v22, pObj, 0, 0);  // 调 实体对象注册到演播层
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 148))(pObj, *(uint32_t *)(v14 + v15 + 4));  // 调用虚函数（虚表槽 +148）【推断: 同 vmt90 但不检查（直接写）】
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj + 112))(  // 调用虚函数（虚表槽 +112）【推断: 坐标三分量直写（无有效性判定版）】
          pObj,
          *(uint32_t *)(v14 + v15 + 8),
          *(uint32_t *)(v14 + v15 + 12),
          *(uint32_t *)(v14 + v15 + 16));
        *(uint8_t *)(pObj + 277) = 1;
      }
      result = v22 + 1;
      v14 += 20;
      ++v22;
    }
    while ( v22 < v19 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x460550 sub_460550 —— 时间片奇偶判定（周期闪烁开关）
// clock_now(this)/uArg2 的奇偶位；uArg2 为闪烁半周期毫秒数。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_460550(void *this, unsigned int uArg2)  // 函数: 时间片奇偶判定（周期闪烁开关）
{
  return (sub_699000((int)this) / uArg2) & 1;  // clock_now(clk)
}



// ------------------------------------------------------------
// 0x460570 sub_460570 —— 索引取值（越界返 0）
// nArg2 超出 *this 时返回 0，否则取 this+4 表第 nArg2 项。
// ------------------------------------------------------------
int /*thiscall*/ sub_460570(uint32_t *this, int nArg2)  // 函数: 索引取值（越界返 0）
{
  if ( nArg2 >= *this )
    return 0;
  else
    return *(uint32_t *)(*(this + 1) + 4 * nArg2);  // this+4 = pHostObj
}



// ============================================================
// 【分区 2】性能统计系统 + 早期图标绘制（0x460590-0x4622A0）
// 统计点归类见文件头；0x460830-0x460DC0 为穿插其中的图标绘制
// （quickslot 布局），0x461C20/0x461F50 为采样/计时辅助【推断】。
// ============================================================
// ------------------------------------------------------------
// 0x460590 sub_460590
// ------------------------------------------------------------
// 性能统计初始化：GetProcessMemoryInfo==0 时 LoadLibraryA("psapi.dll") 动态解析；
// dword_98B754 空时解析 Kernel32!GetThreadTimes —— 内存/线程时间采样入口
HMODULE sub_460590()  // 调 统计初始化
{
  HMODULE LibraryA; // eax
  HMODULE result; // eax

  if ( GetProcessMemoryInfo == 0 )
  {
    LibraryA = LoadLibraryA("psapi.dll");  // 调 加载动态库
    if ( LibraryA != nullptr )  // 若 LibraryA 有效（非空）
      GetProcessMemoryInfo = (int)GetProcAddress(LibraryA, "GetProcessMemoryInfo");  // 调 按名取导出函数地址
  }
  result = (HMODULE)dword_98B754;  // dword_98B754＝空时解析
  if ( dword_98B754 == 0 )
  {
    result = LoadLibraryA("Kernel32.dll");  // 调 加载动态库
    if ( result != nullptr )  // 若 result 有效（非空）
    {
      result = (HMODULE)GetProcAddress(result, "GetThreadTimes");  // 调 按名取导出函数地址
      dword_98B754 = (int)result;  // dword_98B754＝空时解析
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4605F0 sub_4605F0
// ------------------------------------------------------------
// 统计对象清零：两组 6 槽 + 计数族（+100..+116、+204..+228），+568=-1 哨兵
int /*thiscall*/ sub_4605F0(int this)  // 实现：统计对象清零：两组 6 槽 + 计数族（+100..+116、+204..+228），+568=-1 哨兵
{
  int v2; // ecx
  uint32_t *pThis_C; // esi
  int v4; // ecx
  uint32_t *pThis_24; // esi
  uint8_t *pThis_B8; // ecx
  int i; // esi

  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  v2 = 0;
  pThis_C = (uint32_t *)(this + 12);  // this+12〔nSkillRec12(推断)〕等 2 字段
  do
  {
    *pThis_C = 0;  // pThis_C=this+12 nSkillRec12
    *(uint8_t *)(this + v2++ + 192) = 0;
    ++pThis_C;  // pThis_C=this+12 nSkillRec12
  }
  while ( v2 < 6 );
  v4 = 0;
  pThis_24 = (uint32_t *)(this + 36);  // this+144 = pFrameList144
  do
  {
    *pThis_24 = 0;  // pThis_24=this+144 第 4 组·+1040 增量子倍率
    *(uint8_t *)(this + v4++ + 192) = 0;
    ++pThis_24;  // pThis_24=this+144 第 4 组·+1040 增量子倍率
  }
  while ( v4 < 6 );
  *(uint32_t *)(this + 60) = 0;  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 72) = 0;  // this+72〔nSnapshot72(推断)〕等 2 字段
  *(uint32_t *)(this + 76) = 0;  // this+76〔pBtnActionE〕
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  *(uint32_t *)(this + 84) = 0;  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 88) = 0;  // this+88〔pFxObjB(推断)〕等 2 字段
  *(uint32_t *)(this + 92) = 0;  // this+92〔pFxObjC(推断)〕等 2 字段
  pThis_B8 = (uint8_t *)(this + 184);  // this+184〔bSingleTarget(推断)〕
  for ( i = 8; i != 0; --i )  // 循环：i 从 8 递减到 0
  {
    *(pThis_B8 - 8) = 0;  // pThis_B8=this+184 bSingleTarget
    *pThis_B8++ = 0;  // pThis_B8=this+184 bSingleTarget
  }
  *(uint32_t *)(this + 198) = 0;  // this+198〔field_00C6〕
  *(uint8_t *)(this + 202) = 0;
  *(uint32_t *)(this + 100) = 0;  // this+100〔bEnchantDone(推断)〕
  *(uint32_t *)(this + 104) = 0;  // this+104〔nTimerEnd(推断)〕
  *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
  *(uint32_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(this + 116) = 0;  // this+116〔会话上下文〕
  *(uint32_t *)(this + 204) = 0;  // this+204〔pSubAnim204(推断)〕
  *(uint32_t *)(this + 208) = 0;  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 212) = 0;  // this+212〔nField212(推断)〕
  *(uint32_t *)(this + 216) = 0;  // this+216〔bField216(推断)〕
  *(uint32_t *)(this + 220) = 0;  // this+220〔nSnapDst220(推断)〕
  *(uint32_t *)(this + 224) = 0;  // this+224〔nSnapDst224(推断)〕
  *(uint32_t *)(this + 228) = 0;  // this+228〔nSnapDst228(推断)〕
  *(uint8_t *)(this + 508) = 0;  // this+508〔uPetFlag(推断)〕
  *(uint32_t *)(this + 568) = -1;  // this+568〔nAlarmVal〕
  *(uint32_t *)(this + 572) = 0;  // this+572 最后一次受击
  *(uint32_t *)(this + 576) = 0;  // this+576〔uOffset576〕
  *(uint32_t *)(this + 580) = 0;  // this+580〔uOffset580〕
  *(uint32_t *)(this + 708) = 0;  // this+708〔nDamageInfo〕
  *(uint32_t *)(this + 724) = 0;  // this+724〔fVal724(推断)〕
  *(uint32_t *)(this + 728) = 0;
  *(uint8_t *)(this + 732) = 0;
  *(uint32_t *)(this + 736) = 0;
  *(uint32_t *)(this + 740) = 0;
  *(uint32_t *)(this + 824) = 0;
  *(uint32_t *)(this + 844) = 0;
  *(uint32_t *)(this + 848) = 0;
  *(uint32_t *)(this + 852) = 0;
  *(uint8_t *)(this + 856) = 0;
  *(uint32_t *)(this + 888) = 0;
  *(uint32_t *)(this + 892) = 0;
  *(uint32_t *)(this + 908) = 0;
  *(uint32_t *)(this + 964) = 0;  // this+964〔nBlobSize〕
  *(uint32_t *)(this + 992) = 0;  // this+992〔uCfgB992(推断)〕
  *(uint8_t *)(this + 997) = 0;  // this+997〔uStateD997〕
  *(uint8_t *)(this + 996) = 1;  // this+996〔bCfgC996(推断)〕
  *(uint32_t *)(this + 1000) = 0;  // this+1000〔bGrassFilter1000(推断)〕
  *(uint32_t *)(this + 1008) = 0;  // this+1008〔bVineDone1008(推断)〕
  *(uint32_t *)(this + 1004) = 0;  // this+1004〔nOilValD1004(推断)〕
  *(uint32_t *)(this + 1012) = 0;  // this+1012〔uGrabA1012〕
  *(uint32_t *)(this + 1016) = 0;  // this+1016〔uGrabB1016(推断)〕
  *(uint32_t *)(this + 1020) = 0;  // this+1020〔pAnimHandleArr(推断)〕
  *(uint8_t *)(this + 1141) = 0;
  *(uint8_t *)(this + 1142) = 0;
  *(uint8_t *)(this + 1140) = 0;
  *(uint8_t *)(this + 1169) = 0;
  *(uint8_t *)(this + 1170) = 0;
  *(uint8_t *)(this + 1168) = 0;
  *(uint8_t *)(this + 1197) = 0;
  *(uint8_t *)(this + 1198) = 0;
  *(uint32_t *)(this + 1244) = -1;  // this+1244〔nTagTimer〕
  *(uint8_t *)(this + 1196) = 0;
  *(uint32_t *)(this + 1212) = 0;
  *(uint8_t *)(this + 1216) = 0;
  *(uint8_t *)(this + 1217) = 0;
  *(uint32_t *)(this + 1220) = 0;  // this+1220〔pLvTagCtrl〕
  *(uint32_t *)(this + 1224) = 0;  // this+1224〔field_04C8〕
  *(uint8_t *)(this + 1228) = 0;  // this+1228〔bLvTagInited〕
  *(uint32_t *)(this + 1232) = 0;  // this+1232〔pNameTagCtrl〕
  *(uint32_t *)(this + 1236) = 0;  // this+1236〔field_04D4〕
  *(uint8_t *)(this + 1240) = 0;
  *(uint8_t *)(this + 1241) = 0;
  *(uint8_t *)(this + 1260) = 0;  // this+1260〔pCondVec1260〕
  *(uint32_t *)(this + 1276) = 0;  // this+1276〔bEffectArmed1276〕
  *(uint32_t *)(this + 1280) = 0;
  *(uint32_t *)(this + 1284) = 0;  // this+1284〔nEffectCount1284〕
  *(uint32_t *)(this + 1288) = 0;
  *(uint32_t *)(this + 1292) = 0;  // this+1292〔pAnimRow1292〕
  *(uint32_t *)(this + 1300) = 446;
  *(uint32_t *)(this + 1304) = 446;
  *(uint32_t *)(this + 1296) = 0;
  *(uint32_t *)(this + 1308) = 618;  // this+1308〔pRowVec1308〕
  memset((void *)(this + 1340), 0, 0x40u);  // 调 内存按字节填充
  return 0;
}


// ------------------------------------------------------------
// 0x460830 sub_460830 —— 悬停对象拾取/交互触发
// 前 6 槽（this+12）匹配悬停 id dword_79BE3C 时按 dword_8F853C 取对象，后 6 槽按 dword_8F852C 取。
// 两侧各带域号排除（10/11 与 5/6），sub_44BC30 提交拾取/交互（ICON_PICK/ITEM_PICK 音效族）后返回 1。
// 【推断】两张槽表分别对应技能栏与物品栏来源。
// ------------------------------------------------------------
char /*thiscall*/ sub_460830(uint32_t *this)  // 函数: 悬停对象拾取/交互触发
{
  int v2; // eax
  uint32_t *i; // edx
  int v4; // esi
  uint32_t *j; // eax
  int v7; // edi
  void *pObj; // esi
  int fld_e12; // eax
  int v10; // eax
  int *v11; // edi
  int fld_e1; // eax
  int v13; // eax
  int v14; // [esp-8h] [ebp-14h]

  v2 = 0;
  for ( i = this + 3; *(uint8_t *)(*i + 17) == 0 || dword_79BE3C != *(uint32_t *)(*i + 12); ++i )  // 动画对象指针(帧同步比对基准 C)
  {
    if ( ++v2 >= 6 )
    {
      v4 = 0;
      for ( j = this + 9; *(uint8_t *)(*j + 17) == 0 || dword_79BE3C != *(uint32_t *)(*j + 12); ++j )  // 动画对象指针(帧同步比对基准 C)
      {
        if ( ++v4 >= 6 )
          return 0;
      }
      if ( v4 < *(uint32_t *)dword_8F853C )  // 容器对象指针(容量比较)
      {
        v11 = *(int **)(*((uint32_t *)dword_8F853C + 1) + 4 * v4);  // 容器对象指针(容量比较)
        if ( v11 != nullptr )  // 若 v11 有效（非空）
        {
          fld_e1 = *(uint32_t *)(*(this + 1) + 2504);  // this+4 = pHostObj
          if ( fld_e1 != 10 && fld_e1 != 11 )  // 若 fld_e1 != 10 与/或 fld_e1 != 11
          {
            v13 = sub_41A5E0((unsigned int)(v11 + 1));  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
            sub_44BC30((uint32_t *)*(this + 1), (void *)1, 1, v13, v4, v11[95], v11);  // 调 拾取模式状态 + ICON_PICK/ITEM_PICK 音效
          }
          return 1;  // 返回 1(成功)
        }
      }
      return 0;
    }
  }
  v7 = v2 + 3;
  if ( v2 + 3 >= *((uint32_t *)dword_8F852C + 2) )  // dword_8F852C = UI 管理器全局
    return 0;
  pObj = *(void **)(*((uint32_t *)dword_8F852C + 3) + 4 * v7);  // dword_8F852C = UI 管理器全局
  if ( pObj == nullptr )  // 若 pObj 为空
    return 0;
  fld_e12 = *(uint32_t *)(*(this + 1) + 2504);  // this+4 = pHostObj
  if ( fld_e12 != 5 && fld_e12 != 6 )  // 若 fld_e12 != 5 与/或 fld_e12 != 6
  {
    v14 = *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pObj + 16))(pObj) + 68);  // 调用虚函数（虚表槽 +16）
    v10 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pObj + 16))(pObj);  // 调用虚函数（虚表槽 +16）
    sub_44BC30((uint32_t *)*(this + 1), (void *)2, 4, *(uint32_t *)(v10 + 4), v7, v14, pObj);  // 调 拾取模式状态 + ICON_PICK/ITEM_PICK 音效
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x460920 sub_460920
// ------------------------------------------------------------
// 图标绘制（quickslot 主体，477-a4 底边布局，双态 sub_418DD0 取图）【推断】
void /*thiscall*/ sub_460920(int this, unsigned int uArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 实现：图标绘制（quickslot 主体，477-a4 底边布局，双态 sub_418DD0 取图）(推断)
{
  int v7; // edi
  int v8; // ecx
  int v9; // esi
  int v10; // eax
  int v11; // ebx
  int v12; // edx
  int v13; // ebx
  int fld_2E4; // ecx
  int v15; // esi
  uint32_t *v16; // ecx
  int v17; // edx
  int v18; // ebx
  int fld_644; // edi
  signed int dwNow; // esi
  int v21; // ebx
  int fld_645; // eax
  int fld_646; // eax
  int fld_647; // eax
  int pObj; // ecx
  uint32_t *v26; // eax
  char v27; // al
  uint32_t *fld_642; // ecx
  int fld_64; // eax
  int v30; // esi
  int fld_643; // eax
  int v32; // [esp-Ch] [ebp-34h]
  int v33; // [esp-Ch] [ebp-34h]
  int v34; // [esp+Ch] [ebp-1Ch]
  int v35; // [esp+10h] [ebp-18h]
  int v36; // [esp+14h] [ebp-14h]
  int v37; // [esp+18h] [ebp-10h]
  int v38; // [esp+1Ch] [ebp-Ch]
  int v39; // [esp+20h] [ebp-8h]
  int v41; // [esp+30h] [ebp+8h]
  int v42; // [esp+34h] [ebp+Ch]
  int v43; // [esp+38h] [ebp+10h]

  if ( uArg2 < 2 )
  {
    pObj = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
    if ( dword_8F7C04 == 0 )  // dword_8F7C04 = 本地玩家对象
      return;
    v26 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    *(uint32_t *)(dword_79C0B0 + 52) = 477 - nArg4;  // dword_79C0B0 = 文本/图像绘制对象
    v26[12] = 0;
    v26[14] = 640;
    v26[15] = 477 - nArg3;
    if ( uArg2 != 0 )
    {
      fld_64 = sub_418DD0(*(uint32_t **)(this + 100), 2u);  // 调 资源句柄 (101)
      v30 = 599;
    }
    else
    {
      v27 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 776))(pObj, 2);  // 调用虚函数（虚表槽 +776）【推断: ★ 异常状态激活查询 vt+776（研究 20 §1.2/§10…】
      fld_642 = *(uint32_t **)(this + 100);  // this+100 插值终点 Y
      if ( v27 != 0 )
        fld_64 = sub_418DD0(fld_642, 0x68u);  // 调 资源句柄 (101)
      else
        fld_64 = sub_418DD0(fld_642, 1u);  // 调 资源句柄 (101)
      v30 = 6;
    }
    if ( nArg5 != 0 )
    {
      if ( fld_64 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_64 + 128))(  // 调用虚函数（虚表槽 +128）
          fld_64,
          v30,
          412,
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          1065353216,  // 常量 1.0f
          1065353216,  // 常量 1.0f
          0,
          -6908266,
          1333788672,
          1333788672);
      if ( nArg5 == 1 && nArg6 < 500 )  // 若 nArg5 == 1 与/或 nArg6 < 500
      {
        v33 = ((uint8_t)sub_423A80(255, 0, nArg6, 500) << 24) | 0xFFFFFF;  // 调 区间线性插值取整
        fld_643 = sub_418DD0(*(uint32_t **)(this + 100), 0x67u);  // 调 资源句柄 (101)
        sub_43B560(v30, 412, fld_643, 1065353216, 1065353216, 0, v33, 1333788672, 1333788672);  // 调 绘制转发（vt+128）
      }
    }
    else if ( fld_64 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_64 + 152))(fld_64, v30, 412, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    }
  }
  else
  {
    if ( uArg2 != 2 )
      return;
    v7 = (nArg3 - 1) % 475 + 1;
    v37 = v7;
    v8 = (nArg3 - 1) / 475 < 0 ? 0 : (nArg3 - 1) / 475;
    v38 = v8;
    v9 = (nArg4 - 1) % 475 + 1;
    v39 = v9;
    v10 = (nArg4 - 1) / 475 < 0 ? 0 : (nArg4 - 1) / 475;
    v11 = 0;
    v41 = v10;
    v42 = 0;
    v34 = (v8 < v10) + 1;
    if ( v8 < v10 != -1 )
    {
      while ( v8 < v10 )  // 当 v8 < v10 循环
      {
        if ( v11 != 0 )
        {
          v12 = 0;
          goto LABEL_13;
        }
        --v10;
        v13 = 475;
        if ( v8 == v10 )
        {
          v12 = v7;
          v10 = v8;
        }
        else
        {
          v12 = v9;
        }
LABEL_14:
        if ( v12 != v13 )
        {
          fld_2E4 = *(uint32_t *)(this + 740);
          v15 = 33;
          if ( fld_2E4 == 3 )
          {
            v15 = 35;
          }
          else if ( fld_2E4 == 1 || fld_2E4 == 2 )
          {
            v15 = 38;
          }
          v16 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
          v17 = v15 + v12;
          v18 = v15 + v13;
          *(uint32_t *)(dword_79C0B0 + 48) = v17;  // dword_79C0B0 = 文本/图像绘制对象
          v16[13] = 0;
          v16[14] = v18;
          v16[15] = 480;
          v36 = v17;
          v35 = v18;
          if ( *(uint32_t *)(this + 740) == 3 )
          {
            fld_644 = sub_418DD0(*(uint32_t **)(this + 100), v10 % 5 + 137);  // 调 资源句柄 (101)
            dwNow = v15 - timeGetTime() / 0x32 % 0x26;  // 调 取系统毫秒时刻
            if ( dwNow <= v18 )
            {
              v43 = dwNow + 38;
              do
              {
                if ( v43 > v36 )
                {
                  if ( nArg5 != 0 )
                  {
                    if ( fld_644 != 0 )
                      (*(void (/*thiscall*/ **)(int, signed int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_644 + 128))(  // 调用虚函数（虚表槽 +128）
                        fld_644,
                        dwNow,
                        40,
                        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
                        1065353216,  // 常量 1.0f
                        1065353216,  // 常量 1.0f
                        0,
                        -6908266,
                        1333788672,
                        1333788672);
                    if ( nArg5 == 1 && nArg6 < 500 )  // 若 nArg5 == 1 与/或 nArg6 < 500
                    {
                      v21 = (uint64_t)sub_4049C0(255.0, 0.0, nArg6, 500);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
                      fld_645 = sub_418DD0(*(uint32_t **)(this + 100), 0x8Eu);  // 调 资源句柄 (101)
                      if ( fld_645 != 0 )
                        (*(void (/*thiscall*/ **)(int, signed int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_645 + 128))(  // 调用虚函数（虚表槽 +128）
                          fld_645,
                          dwNow,
                          40,
                          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
                          1065353216,  // 常量 1.0f
                          1065353216,  // 常量 1.0f
                          0,
                          ((uint8_t)v21 << 24) | 0xFFFFFF,
                          1333788672,
                          1333788672);
                    }
                  }
                  else if ( fld_644 != 0 )
                  {
                    (*(void (/*thiscall*/ **)(int, signed int, int, int))(*(uint32_t *)fld_644 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                      fld_644,
                      dwNow,
                      40,
                      dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
                  }
                  v18 = v35;
                }
                dwNow += 38;
                v43 += 38;
              }
              while ( dwNow <= v18 );
            }
          }
          else
          {
            fld_646 = sub_418DD0(*(uint32_t **)(this + 100), v10 % 5 + 93);  // 调 资源句柄 (101)
            if ( nArg5 != 0 )
            {
              if ( fld_646 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_646 + 128))(  // 调用虚函数（虚表槽 +128）
                  fld_646,
                  v15,
                  56,
                  dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
                  1065353216,  // 常量 1.0f
                  1065353216,  // 常量 1.0f
                  0,
                  -6908266,
                  1333788672,
                  1333788672);
              if ( nArg5 == 1 && nArg6 < 500 )  // 若 nArg5 == 1 与/或 nArg6 < 500
              {
                v32 = ((uint8_t)sub_423A80(255, 0, nArg6, 500) << 24) | 0xFFFFFF;  // 调 区间线性插值取整
                fld_647 = sub_418DD0(*(uint32_t **)(this + 100), 0x66u);  // 调 资源句柄 (101)
                sub_43B560(v15, 56, fld_647, 1065353216, 1065353216, 0, v32, 1333788672, 1333788672);  // 调 绘制转发（vt+128）
              }
            }
            else if ( fld_646 != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_646 + 152))(fld_646, v15, 56, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            }
          }
        }
        v11 = ++v42;
        if ( v42 >= v34 )
          goto LABEL_61;
        v10 = v41;
        v9 = v39;
        v8 = v38;
        v7 = v37;
      }
      v12 = v7;
      v10 = v8;
LABEL_13:
      v13 = v9;
      goto LABEL_14;
    }
  }
LABEL_61:
  sub_488670((uint32_t *)dword_79C0B0);  // 调 视口重置 640x480
}


// ------------------------------------------------------------
// 0x460DC0 sub_460DC0 —— 【推断】图标序号合成取句柄
// nArg1 为组号（0 特例走 120/121），否则 sub_4D33A0(&pszArg2)%4 得子序，加 8*nArg1-8，pszArg3 非 0 再 +4。
// 末尾 sub_418DD0 取图像句柄；8 个一组、组内 4 变体的排布为推断。
// ------------------------------------------------------------
int /*stdcall*/ sub_460DC0(int nArg1, char pszArg2, char pszArg3, int nArg4)  // 函数: 【推断】图标序号合成取句柄
{
  int v5; // eax

  if ( nArg1 == 0 )
    return sub_418DD0((pszArg3 != 0) + 120);  // 调 资源句柄 (101)
  v5 = sub_4D33A0(&pszArg2) % 4 + 8 * nArg1 - 8;  // 调 掷 0..9999
  if ( pszArg3 != 0 )
    v5 += 4;
  return sub_418DD0(v5);  // 调 资源句柄 (101)
}



// ------------------------------------------------------------
// 0x460E20 sub_460E20 —— 队友低血量警告条绘制
// 遍历本机 dword_8F7C04 vt+792 的 18 个队伍槽（i=17..0）：vt+172 返回对象 +18、vt+188 返回对象 +32
// 各经 sub_41A5E0 取 v5/v7 两值（HP 与上限【推断】）；v5 非 0 且 v7 不超过 v5 的 10% 时，
// 在 x=544 处每行递减 17 绘 406 号底图与 405 号标记，并以 sub_42B420(0,153,timeGetTime(),250) 闪 128 号图（v7 为 0 时相位固定 0x80）。
// ------------------------------------------------------------
void /*thiscall*/ sub_460E20(uint32_t *this)  // 函数: 队友低血量警告条绘制
{
  int pObj2; // edi
  int pObj3; // eax
  int pObj5; // esi
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // ebx
  int pObj4; // eax
  uint8_t v9; // al
  DWORD Time; // eax
  int fld_e248; // ecx
  int pObj; // eax
  int dword_8F7C042; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]
  int v16; // [esp+10h] [ebp-4h]

  pObj2 = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
  dword_8F7C042 = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
  if ( dword_8F7C04 != 0 )  // dword_8F7C04 = 本地玩家对象
  {
    v16 = 544;
    for ( i = 17; i >= 0; --i )
    {
      pObj3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 792))(pObj2, i);  // 调用虚函数（虚表槽 +792）
      pObj5 = pObj3;
      if ( pObj3 != 0 )
      {
        v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 172))(pObj3);  // 调用虚函数（虚表槽 +172）【推断: 朝目标方向按比例取点: p = this + (target −…】
        v5 = sub_41A5E0(v4 + 18);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 188))(pObj5);  // 调用虚函数（虚表槽 +188）【推断: 斜率分档（>5→3、区间内→4、<-5→2）】
        v7 = sub_41A5E0(v6 + 32);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        if ( v5 != 0 && v7 <= 10 * v5 / 100 )  // 若 v5 != 0 与/或 v7 <= 10
        {
          pObj4 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 16))(pObj5) + 68);  // 调用虚函数（虚表槽 +16）
          if ( pObj4 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(  // 调用虚函数（虚表槽 +128）
              pObj4,
              v16,
              406,
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              1056964608,  // 常量 0.5f
              1056964608,  // 常量 0.5f
              0,
              -1,
              1333788672,
              1333788672);
          v9 = 0x80;  // 常量 0x80（= 128）
          if ( v7 != 0 )
          {
            Time = timeGetTime();  // 调 取系统毫秒时刻
            v9 = sub_42B420(0, 153, Time, 250);  // 调 往返插值（三角波）
          }
          fld_e248 = *(this + 248);  // this+992 = uCfgB992
          if ( fld_e248 != 0 )  // fld_e248=this+992 【推断】状态/配置表项 B
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_e248 + 128))(  // 调用虚函数（虚表槽 +128）
              fld_e248,  // fld_e248=this+992 【推断】状态/配置表项 B
              v16,
              406,
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              1056964608,  // 常量 0.5f
              1056964608,  // 常量 0.5f
              0,
              (v9 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          pObj = sub_418DD0(105);  // 调 资源句柄 (101)
          if ( pObj != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v16 - 1, 405, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          v16 -= 17;
        }
        pObj2 = dword_8F7C042;  // 本地玩家对象
      }
    }
  }
}



// ------------------------------------------------------------
// 0x460FB0 sub_460FB0 —— 屏幕坐标双换算与图标层悬挂
// 门控：本机存在 + 本机 vt+852 就绪 + 会话 +52 为本机。首次进入（+997=0）把会话 vt+104 对象的
// vt+120/124/128 经 sub_45E490（减基线）与 sub_45E4D0（带比例回换算）换算成演出层坐标，
// 写 +1000（夹 0..496）与 +1004（-22，超 370 再 -180）；此后每帧对 this+1008 两件驱动播放与绘制。
// ------------------------------------------------------------
int /*thiscall*/ sub_460FB0(int this)  // 函数: 屏幕坐标双换算与图标层悬挂
{
  int result; // eax
  int v3; // edi
  int *pThis_3F0; // edi
  int i; // ebx
  uint32_t *v6; // ebx
  int pObj2; // edi
  int v8; // eax
  int v9; // eax
  bool v10; // sf
  int v11; // eax
  uint32_t *v12; // ebx
  int pObj; // edi
  int v14; // eax
  int v15; // eax
  int *pThis_3F02; // edi
  int j; // ebx
  int v18; // [esp-10h] [ebp-1Ch]
  int v19; // [esp-Ch] [ebp-18h]
  int v20; // [esp-8h] [ebp-14h]
  int v21; // [esp+8h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
  v3 = result;
  v21 = result;
  if ( dword_8F7C04 != 0  // dword_8F7C04 = 本地玩家对象
    && (uint8_t)(result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 852))(dword_8F7C04)) != 0  // 调用虚函数（虚表槽 +852）【推断: [RTTI: IRDActiveObject__vmt354 ·…】
    && (result = *(uint32_t *)(v3 + 52)) == dword_8F7C04 )  // dword_8F7C04 = 本地玩家对象
  {
    if ( *(uint8_t *)(this + 997) == 0 )  // this+997〔uStateD997〕
    {
      pThis_3F0 = (int *)(this + 1008);  // this+1008〔bVineDone1008(推断)〕
      for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
        sub_4926A0(*pThis_3F0++);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
      v6 = *(uint32_t **)(v21 + 104);
      pObj2 = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
      v20 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
      v9 = sub_45E490(v6, v8, v20);  // 调 屏幕 y → 演出层坐标（减基线）
      v10 = v9 - 72 < 0;
      v11 = v9 - 72;
      *(uint32_t *)(this + 1000) = v11;  // this+1000〔bGrassFilter1000(推断)〕
      if ( v10 )
      {
        v11 = 0;
      }
      else if ( v11 > 496 )
      {
        v11 = 496;
      }
      *(uint32_t *)(this + 1000) = v11;  // this+1000〔bGrassFilter1000(推断)〕
      v12 = *(uint32_t **)(v21 + 104);
      pObj = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
      v19 = *(uint32_t *)((*(int (**)(void))(*(uint32_t *)dword_8F7C04 + 36))() + 8);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
      v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);  // 调用虚函数（虚表槽 +128）
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 调用虚函数（虚表槽 +124）
      v15 = sub_45E4D0(v12, v14, v18, v19, 1.0) - 22;  // 调 带比例的回换算（nArg2 - nArg3*f + 120）
      *(uint32_t *)(this + 1004) = v15;  // this+1004〔nOilValD1004(推断)〕
      if ( v15 >= 370 )
        *(uint32_t *)(this + 1004) = v15 - 180;  // this+1004〔nOilValD1004(推断)〕
    }
    *(uint8_t *)(this + 997) = 1;  // this+997〔uStateD997〕
    pThis_3F02 = (int *)(this + 1008);  // this+1008〔bVineDone1008(推断)〕
    for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
    {
      sub_4938F0(*pThis_3F02);  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      result = sub_491D00(dword_79C0B0, *(uint32_t *)(this + 1000), *(uint32_t *)(this + 1004), 0.0);  // 调 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      ++pThis_3F02;  // pThis_3F02=this+1008 bVineDone1008
    }
  }
  else
  {
    *(uint8_t *)(this + 997) = 0;  // this+997〔uStateD997〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x461110 sub_461110 —— 按钮选中态 setter（+1236）
// nArg2 非 0 写 +1236 并以 sub_69C980 换 191/190/190 号图，否则清 0 换 189/182/182。
// ------------------------------------------------------------
int /*thiscall*/ sub_461110(uint32_t *this, int nArg2)  // 函数: 按钮选中态 setter（+1236）
{
  int fld_e25; // edx

  if ( nArg2 != 0 )
  {
    fld_e25 = *(this + 25);  // this+100〔bEnchantDone(推断)〕
    *(this + 309) = nArg2;  // this+1236〔field_04D4〕
    return sub_69C980(fld_e25, 191, 190, 190, -1, 0, 0);  // 调 换 191/190/190 号图
  }
  else
  {
    *(this + 309) = 0;  // this+1236〔field_04D4〕
    return sub_69C980(*(this + 25), 189, 182, 182, -1, 0, 0);  // 调 换 191/190/190 号图
  }
}



// ------------------------------------------------------------
// 0x461170 sub_461170 —— 字节标志 setter（+1240）
// 单字节写 +1240 并原样返回（会员/服务双标志之一，配对见 ·sub_461180）。
// ------------------------------------------------------------
char /*thiscall*/ sub_461170(uint8_t *this, char pszArg2)  // 函数: 字节标志 setter（+1240）
{
  *(this + 1240) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x461180 sub_461180 —— 与 ·sub_461170 同构（差异：偏移 +1241）
// 同为单字节标志 setter 并原样返回；两标志由 ·sub_461190 联合判定后清 +1244。
// ------------------------------------------------------------
char /*thiscall*/ sub_461180(uint8_t *this, char pszArg2)  // 函数: 与 ·sub_461170 同构（差异：偏移 +1241）
{
  *(this + 1241) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x461190 sub_461190 —— 条件清除计时状态 +1244
// sub_41C590(dword_8F7A24) 不为 1 且 +1240/+1241 任一置位时，把 +1244 清 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_461190(int this)  // 函数: 条件清除计时状态 +1244
{
  char result; // al

  result = sub_41C590(dword_8F7A24);  // 调 状态查询（this+348 == 4）
  if ( result != 1 )
  {
    result = *(uint8_t *)(this + 1240);
    if ( result != 0 || (result = *(uint8_t *)(this + 1241)) != 0 )
      *(uint32_t *)(this + 1244) = 0;  // this+1244〔nTagTimer〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x4611D0 sub_4611D0 —— 网络延迟三档指示与 Realy 红字
// sub_656710/656850 取 ping 毫秒：不小于 400 走 sub_42B420(0,2,timeGetTime(),500) 闪烁两态，
// 200..399 与闪烁低态均绘 3 号图加 2 号图（染色 -922746881 半透明）于 (a3-5, a4+11)。
// byte_98B74E 非 0 时以红色 -65536 补绘 Realy（拼写自证）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4611D0(  // 函数: 网络延迟三档指示与 Realy 红字
        void *this,
        bool (/*cdecl*/ *a2)(struct Concurrency::details::_UnrealizedChore *, void *),
        int a3,
        int a4)
{
  int v5; // edi
  int v6; // eax
  DWORD Time; // eax
  int v8; // edi
  int v9; // eax
  int v10; // eax
  Concurrency::details::ContextBase *v11; // eax
  char v12; // al
  void *v13; // [esp+0h] [ebp-2Ch]
  bool (/*cdecl*/ *v14)(struct Concurrency::details::_UnrealizedChore *, void *); // [esp+4h] [ebp-28h]
  uint8_t v15[4]; // [esp+Ch] [ebp-20h] BYREF
  uint8_t v16[4]; // [esp+10h] [ebp-1Ch] BYREF
  uint8_t v17[4]; // [esp+14h] [ebp-18h] BYREF
  uint8_t v18[4]; // [esp+18h] [ebp-14h] BYREF
  uint8_t v19[4]; // [esp+1Ch] [ebp-10h] BYREF
  uint8_t v20[4]; // [esp+20h] [ebp-Ch] BYREF
  uint8_t v21[4]; // [esp+24h] [ebp-8h] BYREF
  uint8_t v22[4]; // [esp+28h] [ebp-4h] BYREF

  sub_656710();  // 调 取全局单例地址（返回 unk_9BD5D0）
  v5 = sub_656850(a2);  // 调 通道延迟查询（70% 分位，毫秒）
  sub_656710();  // 调 取全局单例地址（返回 unk_9BD5D0）
  sub_6568F0(a2, v15, v16, v17, v18, v19, v20, v21, v22);  // 调 通道统计快照导出（·0x4611D0 性能面板取数）
  if ( v5 < 200 )
    goto LABEL_11;
  if ( v5 < 400 )
  {
    v6 = sub_418DD0(3);  // 调 资源句柄 (101)
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, a3 - 5, a4 + 11, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
LABEL_8:
    sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    v10 = sub_418DD0(2);  // 调 资源句柄 (101)
    if ( v10 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 128))(  // 调用虚函数（虚表槽 +128）
        v10,
        a3 - 5,
        a4 + 11,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,  // 常量 1.0f
        1065353216,  // 常量 1.0f
        0,
        -922746881,
        1333788672,
        1333788672);
    sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
    goto LABEL_11;
  }
  Time = timeGetTime();  // 调 取系统毫秒时刻
  v8 = sub_42B420(0, 2, Time, 500);  // 调 往返插值（三角波）
  v9 = sub_418DD0(v8);  // 调 资源句柄 (101)
  if ( v9 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, a3 - 5, a4 + 11, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  if ( v8 == 0 )
    goto LABEL_8;
LABEL_11:
  v11 = (Concurrency::details::ContextBase *)sub_656710();  // 调 取全局单例地址（返回 unk_9BD5D0）
  Concurrency::details::ContextBase::SweepUnstructured(v11, a2, v13, v14);
  if ( v12 != 0 && byte_98B74E != 0 )  // 若 v12 != 0 与/或 byte_98B74E != 0
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (int)this + 124);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    (*(void (/*cdecl*/ **)(int, int, int, int, const char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
      dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
      a3 - 5,
      a4 + 11,
      -65536,
      "Realy");
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  }
}



// ------------------------------------------------------------
// 0x461370 sub_461370 —— 网络统计调试叠字（两行三色）
// this+508 使能时取 ping 与 sub_6568F0 的八个统计值，按 0/蓝 -16776961/红 -65536 三色，
// 在 (nArg3+nArg5, nArg4+nArg6) 绘两行 %d %d %d %d 与 %d %d %d（行距 15）。
// ------------------------------------------------------------
char /*thiscall*/ sub_461370(uint8_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数: 网络统计调试叠字（两行三色）
{
  char result; // al
  int nArg22; // edi
  int v9; // ebx
  int v10; // esi
  int v11; // edi
  int nArg23; // [esp-Ch] [ebp-30h]
  int v13; // [esp+4h] [ebp-20h] BYREF
  int v14; // [esp+8h] [ebp-1Ch] BYREF
  int v15; // [esp+Ch] [ebp-18h] BYREF
  int v16; // [esp+10h] [ebp-14h]
  int v17; // [esp+14h] [ebp-10h] BYREF
  int v18; // [esp+18h] [ebp-Ch] BYREF
  int v19; // [esp+1Ch] [ebp-8h] BYREF
  int v20; // [esp+20h] [ebp-4h] BYREF

  result = *(this + 508);  // this+508 【推断】伙伴/弹体标志
  if ( result != 0 )  // 若结果非 0（成功）
  {
    nArg22 = nArg2;
    nArg23 = nArg2;
    sub_656710();  // 调 取全局单例地址（返回 unk_9BD5D0）
    v16 = sub_656850(nArg23);  // 调 通道延迟查询（70% 分位，毫秒）
    sub_656710();  // 调 取全局单例地址（返回 unk_9BD5D0）
    sub_6568F0(nArg22, &v17, &v18, &v19, &v13, &v14, &v15, &nArg2, &v20);  // 调 通道统计快照导出（·0x4611D0 性能面板取数）
    v9 = -1;
    if ( nArg2 != 0 )
      v9 = -16776961;
    if ( v20 != 0 )
      v9 = -65536;
    (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 124);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    v10 = nArg4 + nArg6;
    v11 = nArg3 + nArg5;
    (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
      dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
      nArg3 + nArg5,
      nArg4 + nArg6,
      v9,
      "%d %d %d %d",  // 日志模板 %d %d %d %d
      v16,
      v17,
      v18,
      v19);
    (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
      dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
      v11,
      v10 + 15,
      v9,
      "%d %d %d",  // 日志模板 %d %d %d
      v13,
      v14,
      v15);
    return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  }
  return result;
}



// ------------------------------------------------------------
// 0x461470 sub_461470 —— 双子控件可见性同步
// 把 this+320 与 this+324 两个子控件的 +16 可见字节同时置为 pszArg2。
// ------------------------------------------------------------
char /*thiscall*/ sub_461470(uint32_t *this, char pszArg2)  // 函数: 双子控件可见性同步
{
  *(uint8_t *)(*(this + 320) + 16) = pszArg2;
  *(uint8_t *)(*(this + 324) + 16) = pszArg2;  // this+324 帧/层参数槽
  return pszArg2;
}



// ------------------------------------------------------------
// 0x461490 sub_461490 —— 618/446 双向切换（页签翻页）
// 读 +1300：为 618 则目标 446（+1308=618、+1304=446），为 446 则反向。
// 每次清 +1325/+1326、重启 this+1312 定时器（0ms），并由 sub_69A5F0 把 +1296 控件移到目标位置。
// 618 与 446 两常量即一对页签的 x 坐标。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_461490(int this)  // 函数: 618/446 双向切换（页签翻页）
{
  uint32_t *result; // eax

  result = *(uint32_t **)(this + 1300);
  if ( result == (uint32_t *)618 )
  {
    *(uint32_t *)(this + 1308) = 618;  // this+1308〔pRowVec1308〕
    *(uint32_t *)(this + 1304) = 446;
    *(uint8_t *)(this + 1325) = 0;
    *(uint8_t *)(this + 1326) = 0;
    sub_698F90(this + 1312, 0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
    return sub_69A5F0(*(uint32_t **)(this + 1296), 446, 61);  // 调 设位、sub_69A840 登记
  }
  else if ( result == (uint32_t *)446 )
  {
    *(uint32_t *)(this + 1308) = 446;  // this+1308〔pRowVec1308〕
    *(uint32_t *)(this + 1304) = 618;
    *(uint8_t *)(this + 1325) = 0;
    *(uint8_t *)(this + 1326) = 0;
    sub_698F90(this + 1312, 0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
    return sub_69A5F0(*(uint32_t **)(this + 1296), 618, 61);  // 调 设位、sub_69A840 登记
  }
  return result;
}



// ------------------------------------------------------------
// 0x461520 sub_461520 —— 对战计数与 2.6 秒定时
// 置 +1416=1，this+1404 定时器 2600ms（+1417/+1418 清零），
// 并把会话 dword_8F7A24+40 的 +132 计数自增 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_461520(uint8_t *this)  // 函数: 对战计数与 2.6 秒定时
{
  int pThis_57C; // ecx
  int result; // eax

  *(this + 1416) = 1;
  pThis_57C = (int)(this + 1404);
  *(uint8_t *)(pThis_57C + 13) = 0;
  *(uint8_t *)(pThis_57C + 14) = 0;
  sub_698F90(pThis_57C, 2600, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
  result = *(uint32_t *)(dword_8F7A24 + 40);  // dword_8F7A24 = 当前场景状态对象
  ++*(uint32_t *)(result + 132);
  return result;
}



// ------------------------------------------------------------
// 0x461550 sub_461550 —— 8 字节项比较器（按第 2 个 dword）
// qsort 回调，供 ·sub_4632D0 对 8 项座位表排序。
// ------------------------------------------------------------
int /*cdecl*/ sub_461550(uint32_t *pArg1, uint32_t *pArg2)  // 函数: 8 字节项比较器（按第 2 个 dword）
{
  int v2; // eax
  int v3; // ecx

  v2 = pArg1[1];
  v3 = pArg2[1];
  if ( v2 >= v3 )
    return (v2 <= v3) - 1;
  else
    return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x461580 sub_461580 —— 界面子控件批量显隐
// 对 +15..+20、+305、+308、+320、+324 共 11 个子控件的 +16 可见字节批量赋值：
// nArg2 为 1/2 置 0；为 0 置 1 且 +320/+324 特判域号 dword_8F7A24+12 是否为 6；其余 nArg2 置 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_461580(uint32_t *this, int nArg2)  // 函数: 界面子控件批量显隐
{
  int fld_e320; // eax

  if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 || nArg2 == 2 )  // 若 nArg2 == 1 与/或 nArg2 == 2
    {
      *(uint8_t *)(*(this + 15) + 16) = 0;  // this+60〔nFadeValue60(推断)〕
      *(uint8_t *)(*(this + 16) + 16) = 0;  // this+64〔apServerTabBtn(推断)〕
      *(uint8_t *)(*(this + 17) + 16) = 0;  // this+68〔nCharCount(推断)〕
      *(uint8_t *)(*(this + 18) + 16) = 0;  // this+72〔nSnapshot72(推断)〕
      *(uint8_t *)(*(this + 19) + 16) = 0;  // this+76〔pBtnActionE〕
      *(uint8_t *)(*(this + 20) + 16) = 0;  // this+80 = nAuraStage
      *(uint8_t *)(*(this + 305) + 16) = 0;  // this+1220〔pLvTagCtrl〕
      *(uint8_t *)(*(this + 308) + 16) = 0;  // this+1232〔pNameTagCtrl〕
      fld_e320 = *(this + 320);
      *(uint8_t *)(fld_e320 + 16) = 0;
      *(uint8_t *)(*(this + 324) + 16) = 0;  // this+324 帧/层参数槽
    }
    else
    {
      *(uint8_t *)(*(this + 15) + 16) = 1;  // this+60〔nFadeValue60(推断)〕
      *(uint8_t *)(*(this + 16) + 16) = 1;  // this+64〔apServerTabBtn(推断)〕
      *(uint8_t *)(*(this + 17) + 16) = 1;  // this+68〔nCharCount(推断)〕
      *(uint8_t *)(*(this + 18) + 16) = 1;  // this+72〔nSnapshot72(推断)〕
      *(uint8_t *)(*(this + 19) + 16) = 1;  // this+76〔pBtnActionE〕
      *(uint8_t *)(*(this + 20) + 16) = 1;  // this+80 = nAuraStage
      *(uint8_t *)(*(this + 305) + 16) = 1;  // this+1220〔pLvTagCtrl〕
      *(uint8_t *)(*(this + 308) + 16) = 1;  // this+1232〔pNameTagCtrl〕
      fld_e320 = *(this + 320);
      *(uint8_t *)(fld_e320 + 16) = 0;
      *(uint8_t *)(*(this + 324) + 16) = 0;  // this+324 帧/层参数槽
    }
  }
  else
  {
    *(uint8_t *)(*(this + 15) + 16) = 1;  // this+60〔nFadeValue60(推断)〕
    *(uint8_t *)(*(this + 16) + 16) = 1;  // this+64〔apServerTabBtn(推断)〕
    *(uint8_t *)(*(this + 17) + 16) = 1;  // this+68〔nCharCount(推断)〕
    *(uint8_t *)(*(this + 18) + 16) = 1;  // this+72〔nSnapshot72(推断)〕
    *(uint8_t *)(*(this + 19) + 16) = 1;  // this+76〔pBtnActionE〕
    *(uint8_t *)(*(this + 20) + 16) = 1;  // this+80 = nAuraStage
    *(uint8_t *)(*(this + 305) + 16) = 1;  // this+1220〔pLvTagCtrl〕
    *(uint8_t *)(*(this + 308) + 16) = 1;  // this+1232〔pNameTagCtrl〕
    LOBYTE(fld_e320) = *(uint32_t *)(dword_8F7A24 + 12) == 6;  // 调 取 16 位值低 8 位
    *(uint8_t *)(*(this + 320) + 16) = fld_e320;
    *(uint8_t *)(*(this + 324) + 16) = fld_e320;  // this+324 帧/层参数槽
  }
  return fld_e320;
}



// ------------------------------------------------------------
// 0x461690 sub_461690 —— 按钮点击（音效加三连图切换）
// sub_4B0A60 翻转开关，sub_432EA0 播 CLICK_BUTTON1（串自证）。
// sub_4B09A0(dword_8F7C04) 取子模式：为 1 换 54/55/56 图组，否则换 57/58/59 图组（落在 this+104 控件）。
// ------------------------------------------------------------
void /*thiscall*/ sub_461690(uint32_t *this)  // 函数: 按钮点击（音效加三连图切换）
{
  if ( dword_8F7C04 != 0 )  // dword_8F7C04 = 本地玩家对象
  {
    sub_4B0A60();  // 调 切换开关（按 +8212 翻转）
    sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 调 音效播放包装（非空判定）
    if ( sub_4B09A0(dword_8F7C04) != 0 )  // dword_8F7C04 = 本地玩家对象
    {
      if ( sub_4B09A0(dword_8F7C04) == 1 )  // dword_8F7C04 = 本地玩家对象
        sub_69C980(*(this + 26), 54, 55, 56, -1, 0, 0);  // 调 换 191/190/190 号图
    }
    else
    {
      sub_69C980(*(this + 26), 57, 58, 59, -1, 0, 0);  // 调 换 191/190/190 号图
    }
  }
}



// ------------------------------------------------------------
// 0x461710 sub_461710 —— 子对象存在性判定（+558）
// sub_41A5E0(this+558) 非空即真（P24 防篡改读包装的读侧）。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_461710(void *this)  // 函数: 子对象存在性判定（+558）
{
  return sub_41A5E0((unsigned int)this + 558) != 0;  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x461730 sub_461730 —— 20 字节项数组计数
// 返回 (this+3 - this+2)/20，即 20 字节每项的项数。
// ------------------------------------------------------------
int /*thiscall*/ sub_461730(int *this)  // 函数: 20 字节项数组计数
{
  int result; // eax

  result = *(this + 2);  // this+8 = 技能槽记录首字
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(this + 3) - result) / 20;  // this+12 = 技能槽记录次字
  return result;  // result=this+8 物品 id
}



// ------------------------------------------------------------
// 0x461750 sub_461750 —— clong 构造（共享 vftbl_clong）
// sub_41A630 起构后写 vftbl_clong 虚表，sub_41A590 写入 nArg2；与 ·sub_46B080 同构。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_461750(uint32_t *this, int nArg2)  // 函数: clong 构造（共享 vftbl_clong）
{
  int v3; // edx

  sub_41A630((unsigned int)this);  // 调 防篡改字段读校验（crypt 逆运算链）
  *this = &vftbl_clong;  // 构造装配 vftable：clong
  sub_41A590((unsigned int)this, v3, nArg2);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  return this;
}



// ------------------------------------------------------------
// 0x4617A0 sub_4617A0 —— 称号路阶文本拼接
// nArg2 为 1/2/3 分别取 EXPERT ROAD、MASTER ROAD、KING ROAD 三段称号（串自证），
// 与本对象首字段串以短横拼接后 sprintf 进全局 byte_98B778；称号为空则不留分隔符。
// ------------------------------------------------------------
char */*thiscall*/ sub_4617A0(const char *this, int nArg2)  // 函数: 称号路阶文本拼接
{
  const char *psz; // eax
  const char *v4; // edx
  const char *v5; // eax
  const char *pThis_8; // ecx
  unsigned int nLen; // [esp+10h] [ebp+8h]

  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      psz = "EXPERT'S ROAD";
      break;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      psz = "MASTER'S ROAD";
      break;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      psz = "KING'S ROAD";
      break;
    default:
      psz = szPassword;
      break;
  }
  nLen = strlen(psz);  // 调 返回字符串长度（逐字节扫描）
  v4 = " - ";
  if ( nLen == 0 )
    v4 = szPassword;
  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      v5 = "EXPERT'S ROAD";
      break;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      v5 = "MASTER'S ROAD";
      break;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      v5 = "KING'S ROAD";
      break;
    default:
      v5 = szPassword;
      break;
  }
  if ( *((uint32_t *)this + 7) < 0x10u )  // this+28〔pPanelVec(推断)〕
    pThis_8 = this + 8;  // this+8 物品 id
  else
    pThis_8 = *((const char **)this + 2);  // pThis_8=this+8 物品 id
  sprintf(byte_98B778, "%s%s%s", pThis_8, v4, v5);  // 调 格式化到缓冲
  return byte_98B778;
}



// ------------------------------------------------------------
// 0x461840 sub_461840
// ------------------------------------------------------------
// ★ 性能统计 HUD 绘制（每 1000ms 经 +358 时钟重采样）：
// fps = 1000000/帧时长 usec（sub_405030(2)）；纹理 MB = sub_4050B0(1)×0.00000095367432
// （1/1048576）；cached chars = sub_4050B0(2)；traversal = sub_405030(9) usec；
// 四行 sprintf → dword_79C0B0 vt+80 绘制（y=163/176/189/202）；"Main" 标签
HGDIOBJ /*thiscall*/ sub_461840(int *this)  // 称号路阶文本拼接
{
  int pThis_166; // esi
  int fld_e364; // edi
  uint64_t v3; // rax
  int v4; // eax
  int v5; // eax
  HGDIOBJ result; // eax
  uint8_t v7[12]; // [esp+18h] [ebp-14Ch] BYREF
  int v8; // [esp+24h] [ebp-140h]
  int v9; // [esp+28h] [ebp-13Ch]
  int v10; // [esp+2Ch] [ebp-138h]
  int v11; // [esp+30h] [ebp-134h]
  int v12; // [esp+34h] [ebp-130h]
  int v13; // [esp+38h] [ebp-12Ch]
  int v14; // [esp+3Ch] [ebp-128h]
  int v15; // [esp+40h] [ebp-124h]
  HGDIOBJ ho; // [esp+44h] [ebp-120h]
  int dword_99FCCC2; // [esp+48h] [ebp-11Ch]
  uint64_t v18; // [esp+4Ch] [ebp-118h]
  char Buffer[256]; // [esp+54h] [ebp-110h] BYREF
  int dword_796E502; // [esp+154h] [ebp-10h]
  int v21; // [esp+160h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  pThis_166 = (int)(this + 358);  // this+1432 = 效果触发锁存标志
  dword_98B898 = (int)"Main";
  fld_e364 = *(this + 364);  // this+1456〔nUdpReportField〕
  v21 = 0;
  v7[0] = 0;
  v7[1] = 0;
  v7[3] = 0;
  v8 = 0;
  v9 = 6;
  v10 = 12;
  v11 = 0;
  v12 = 1600;
  v13 = 0;
  v14 = 0;
  v15 = 0;
  ho = nullptr;
  dword_99FCCC2 = dword_99FCCC;  // dword_99FCCC＝与字距
  v7[2] = 1;
  if ( sub_699000((int)(this + 358)) >= fld_e364 )  // this+1432 = 效果触发锁存标志
  {
    dword_98B88C = (uint64_t)((double)(uint64_t)(sub_405030(4) - qword_98B890) * 0.001);  // 调 NiProfile 槽耗时读取（uArg1 < 100 返回 dword_79CD40 槽值，否则 0）
    qword_98B890 = sub_405030(4);  // 调 NiProfile 槽耗时读取（uArg1 < 100 返回 dword_79CD40 槽值，否则 0）
    dword_98B888 = sub_405030(3);  // 调 NiProfile 槽耗时读取（uArg1 < 100 返回 dword_79CD40 槽值，否则 0）
    dword_98B87C = (uint64_t)((double)(uint64_t)(sub_405030(5) - qword_98B880) * 0.001);  // 调 NiProfile 槽耗时读取（uArg1 < 100 返回 dword_79CD40 槽值，否则 0）
    qword_98B880 = sub_405030(5);  // 调 NiProfile 槽耗时读取（uArg1 < 100 返回 dword_79CD40 槽值，否则 0）
    v3 = sub_405030(2);  // 调 NiProfile 槽耗时读取（uArg1 < 100 返回 dword_79CD40 槽值，否则 0）
    v18 = v3 & 0x8000000000000000uLL;
    dword_98B878 = (uint64_t)(1000000.0 / (double)v3);
    *(uint8_t *)(pThis_166 + 13) = 0;  // pThis_166=this+1432 效果触发锁存标志
    *(uint8_t *)(pThis_166 + 14) = 0;  // pThis_166=this+1432 效果触发锁存标志
    sub_698F90(pThis_166, 1000, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
  }
  (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v7);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
  sprintf(Buffer, "fps : %03d", dword_98B878);  // 调 格式化到缓冲
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 10, 163, -1, Buffer);  // 调用虚函数（虚表槽 +80）
  HIDWORD(v18) = sub_4050B0(1);  // 调 帧计数读取（uArg1 >= 50 返回 0，否则取 dword_79C958 槽值）
  sprintf(Buffer, "texture size : %0.3f MB", (double)SHIDWORD(v18) * 0.00000095367432);  // 调 格式化到缓冲
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 10, 176, -1, Buffer);  // 调用虚函数（虚表槽 +80）
  v4 = sub_4050B0(2);  // 调 帧计数读取（uArg1 >= 50 返回 0，否则取 dword_79C958 槽值）
  sprintf(Buffer, "cached chars : %d", v4);  // 调 格式化到缓冲
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 10, 189, -1, Buffer);  // 调用虚函数（虚表槽 +80）
  v5 = sub_405030(9);  // 调 NiProfile 槽耗时读取（uArg1 < 100 返回 dword_79CD40 槽值，否则 0）
  sprintf(Buffer, "traversal : %d usec", v5);  // 调 格式化到缓冲
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 10, 202, -1, Buffer);  // 调用虚函数（虚表槽 +80）
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  result = ho;
  if ( ho != nullptr )  // 若 ho 有效（非空）
    return (HGDIOBJ)DeleteObject(ho);  // 调 删除 GDI 对象
  return result;
}



// ------------------------------------------------------------
// 0x461B80 sub_461B80 —— 队伍槽命中标志与本机上报
// 前 6 槽（this+12）匹配 dword_79BE38 时把自身 +192 起对应字节置 1。
// 后 6 槽匹配时自 dword_8F853C 取该槽对象，sub_47E7A0(sub_41A5E0(对象+558)==0, 1) 上报。
// ------------------------------------------------------------
char /*thiscall*/ sub_461B80(uint32_t *this)  // 函数: 队伍槽命中标志与本机上报
{
  int v2; // eax
  uint32_t *pThis_3; // esi
  int v4; // eax
  uint32_t *i; // ecx
  int v6; // esi
  int v7; // eax

  if ( *(uint32_t *)(*(this + 1) + 2504) != 0 )  // this+4 = pHostObj
    return 0;
  v2 = 0;
  pThis_3 = this + 3;  // this+12〔nSkillRec12〕
  do
  {
    if ( *(uint8_t *)(*pThis_3 + 17) != 0 && dword_79BE38 == *(uint32_t *)(*pThis_3 + 12) )  // 动画对象指针(帧同步比对基准 B)
    {
      *((uint8_t *)this + v2 + 192) = 1;
      return 1;  // 返回 1(成功)
    }
    ++v2;
    ++pThis_3;
  }
  while ( v2 < 6 );
  v4 = 0;
  for ( i = this + 9; *(uint8_t *)(*i + 17) == 0 || dword_79BE38 != *(uint32_t *)(*i + 12); ++i )  // 动画对象指针(帧同步比对基准 B)
  {
    if ( ++v4 >= 6 )
      return 0;
  }
  if ( v4 < *(uint32_t *)dword_8F853C )  // 容器对象指针(容量比较)
  {
    v6 = *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * v4);  // 容器对象指针(容量比较)
    if ( v6 != 0 )
    {
      v7 = sub_41A5E0(v6 + 558);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
      sub_47E7A0(v7 == 0, 1);  // 调 pszArg3 时播 SEAL_ON/SEAL_OFF（sub_432EA0）+ sub_44E850(18) + sub_48BA…
    }
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x461C20 sub_461C20 —— 周期性提示图闪烁绘制
// 时基：+1196 使能且 this+1184 定时器已过 0 时取之（再夹到 +1208），否则用 timeGetTime（byte_9B88BE 为 0 时）。
// sub_4049C0(0,510,Time%1000,1000) 得 0..510 相位，超 255 取反，据此绘 148 号图于 (255,396)（sub_491530/491630 包夹）。
// 周期走完清 +1196。
// ------------------------------------------------------------
char /*thiscall*/ sub_461C20(int this)  // 函数: 周期性提示图闪烁绘制
{
  int fld_4B8; // ebx
  signed int Time; // eax
  uint64_t v4; // rax
  uint8_t v5; // bl
  int pObj5; // eax
  int pObj2; // eax
  int pObj4; // eax
  int pObj; // eax
  int pThis_4A0; // eax
  uint64_t v11; // rax
  uint32_t *v12; // ecx
  int pObj3; // eax
  uint32_t *v14; // eax
  int pObj6; // eax
  int pThis_4A02; // eax
  int fld_4B82; // edi
  float v19; // [esp+3Ch] [ebp-24h]
  float v20; // [esp+40h] [ebp-20h]
  int fld_4BC; // [esp+58h] [ebp-8h]
  int v22; // [esp+5Ch] [ebp-4h]

  if ( *(uint8_t *)(this + 1196) != 0 && sub_699000(this + 1184) >= 0 )  // clock_now(clk)
  {
    fld_4B8 = *(uint32_t *)(this + 1208);
    if ( sub_699000(this + 1184) >= fld_4B8 )  // clock_now(clk)
      Time = *(uint32_t *)(this + 1208);
    else
      Time = sub_699000(this + 1184);  // clock_now(clk)
  }
  else
  {
    if ( byte_9B88BE == 0 )
      goto LABEL_13;
    Time = timeGetTime();  // 调 取系统毫秒时刻
  }
  v4 = (uint64_t)sub_4049C0(0.0, 510.0, Time % 1000, 1000);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
  v5 = v4;
  if ( (int)v4 > 255 )
    v5 = -2 - v4;
  sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
  pObj5 = sub_418DD0(148);  // 调 资源句柄 (101)
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(  // 调用虚函数（虚表槽 +128）
      pObj5,
      255,
      396,
      dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
      1065353216,  // 常量 1.0f
      1065353216,  // 常量 1.0f
      0,
      (v5 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
LABEL_13:
  pObj2 = sub_418DD0(143);  // 调 资源句柄 (101)
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, 266, 409, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  pObj4 = sub_418DD0(144);  // 调 资源句柄 (101)
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 270, 413, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  if ( word_8F7C10 != 0 )  // 疲劳值
  {
    v22 = (uint64_t)sub_4049C0(100.0, 0.0, (uint16_t)word_8F7C10, (uint16_t)word_8F7C14);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
    if ( *(uint8_t *)(this + 1196) != 0 && sub_699000(this + 1184) >= 0 )  // clock_now(clk)
    {
      fld_4BC = (uint64_t)sub_4049C0(100.0, 0.0, *(uint32_t *)(this + 1212), (uint16_t)word_8F7C14);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
      pThis_4A0 = sub_699000(this + 1184);  // clock_now(clk)
      v20 = (float)v22;
      v19 = (float)fld_4BC;
      v11 = (uint64_t)sub_4049C0(v19, v20, pThis_4A0, 1000);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
      v12 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      *(uint32_t *)(dword_79C0B0 + 48) = 270;  // dword_79C0B0 = 文本/图像绘制对象
      v12[13] = 413;
      v12[14] = v11 + 270;
      v12[15] = 443;
      pObj3 = sub_418DD0(145);  // 调 资源句柄 (101)
      if ( pObj3 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, 270, 413, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      sub_488670(dword_79C0B0);  // 调 视口重置 640x480
    }
    v14 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    *(uint32_t *)(dword_79C0B0 + 56) = v22 + 270;  // dword_79C0B0 = 文本/图像绘制对象
    v14[12] = 270;
    v14[13] = 413;
    v14[15] = 443;
    pObj6 = sub_418DD0(((uint16_t)word_8F7C10 >= (uint16_t)word_8F7C14 - 15) + 146);  // 疲劳值
    if ( pObj6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, 270, 413, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    sub_488670(dword_79C0B0);  // 调 视口重置 640x480
  }
  else
  {
    pObj = sub_418DD0(146);  // 调 资源句柄 (101)
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, 270, 413, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  }
  LOBYTE(pThis_4A02) = *(uint8_t *)(this + 1196);  // 调 取 16 位值低 8 位
  if ( (uint8_t)pThis_4A02 != 0 )
  {
    fld_4B82 = *(uint32_t *)(this + 1208);
    pThis_4A02 = sub_699000(this + 1184);  // clock_now(clk)
    if ( pThis_4A02 >= fld_4B82 )
      *(uint8_t *)(this + 1196) = 0;
  }
  return pThis_4A02;
}



// ------------------------------------------------------------
// 0x461F50 sub_461F50 —— 队友/目标状态板 4 格绘制
// this+51 起 4 组（步进 28），经 dword_8F850C 槽表取实体；设裁剪窗 (0,0,640,..)，vt+384 绘 24x24 头像。
// sub_456480 与槽号相符时叠 192 号图；HP/MP 经 sub_4049C0(0,59,vt+736/740 与 vt+752/756) 映射 59px 条并配 176/177 号图。
// 无实体时走空态分支把 +16 清 0。
// ------------------------------------------------------------
int */*thiscall*/ sub_461F50(int *this)  // 函数: 队友/目标状态板 4 格绘制
{
  int v2; // edi
  int *result; // eax
  int v4; // ecx
  int pObj4; // esi
  int v6; // eax
  int v7; // edi
  uint32_t *v8; // eax
  int pObj; // eax
  int pObj2; // eax
  int pObj6; // eax
  int pObj3; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  uint64_t v16; // rax
  uint32_t *v17; // eax
  int pObj5; // eax
  uint32_t *v19; // eax
  int pObj7; // eax
  int v21; // ecx
  bool v22; // cc
  int v23; // [esp+0h] [ebp-30h]
  int v24; // [esp+Ch] [ebp-24h]
  int v25; // [esp+10h] [ebp-20h]
  int v26; // [esp+14h] [ebp-1Ch]
  int v27; // [esp+18h] [ebp-18h]
  int dword_8F85202; // [esp+18h] [ebp-18h]
  int v29; // [esp+1Ch] [ebp-14h]
  int v30; // [esp+20h] [ebp-10h]
  int v31; // [esp+20h] [ebp-10h]
  int v32; // [esp+20h] [ebp-10h]
  int *pThis_33; // [esp+24h] [ebp-Ch]
  bool (/*cdecl*/ *v34)(struct Concurrency::details::_UnrealizedChore *, void *); // [esp+28h] [ebp-8h]
  int v35; // [esp+2Ch] [ebp-4h]

  v25 = 1048444 - (uint32_t)this;
  v2 = -188 - (uint32_t)this;
  result = this + 51;  // this+204〔主状态参数〕
  v34 = nullptr;
  pThis_33 = this + 51;  // this+204〔主状态参数〕
  v24 = -188 - (uint32_t)this;
  v26 = -204 - (uint32_t)this;
  do
  {
    v4 = *(int *)((char *)result + v2 + dword_8F850C);  // 房间/席位表
    v29 = v4;
    if ( v4 != 0 )
      pObj4 = *(uint32_t *)(v4 + 196);
    else
      pObj4 = 0;
    if ( v4 != 0 )
    {
      v6 = *result;
      v7 = *(uint32_t *)(v6 + 20);
      v35 = *(uint32_t *)(v6 + 24);
      v8 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
      v8[13] = 0;
      v8[14] = v7 + 88;
      v8[15] = 480;
      pObj = sub_418DD0(173);  // 调 资源句柄 (101)
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v7, v35, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      sub_488670(dword_79C0B0);  // 调 视口重置 640x480
      pObj2 = sub_418DD0(174);  // 调 资源句柄 (101)
      if ( pObj2 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v7 + 88, v35 + 13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      pObj6 = sub_42B340(v29);  // 调 虚拟角色惰性创建（0x294 字节）
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)pObj6 + 384))(  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
        pObj6,
        v7 + 2,
        v35 + 2,
        24,
        24,
        1065353216);  // 常量 1.0f
      if ( (bool (/*cdecl*/ *)(struct Concurrency::details::_UnrealizedChore *, void *))sub_456480(dword_8F850C) == v34 )  // 房间/席位表
      {
        pObj3 = sub_418DD0(192);  // 调 资源句柄 (101)
        if ( pObj3 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v7 + 1, v35 + 1, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      }
      v13 = 59;
      v30 = 59;
      if ( pObj4 != 0 )
      {
        v31 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 740))(pObj4);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 736))(pObj4);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
        v27 = (uint64_t)sub_4049C0(0.0, 59.0, v14, v31);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
        v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 756))(pObj4);  // 调用虚函数（虚表槽 +756）【推断: [RTTI: IRDActiveObject__vmt2F4 ·…】
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 752))(pObj4);  // 调用虚函数（虚表槽 +752）
        v16 = (uint64_t)sub_4049C0(0.0, 59.0, v15, v32);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
        v13 = v27;
        v30 = v16;
      }
      v17 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
      v17[13] = 0;
      v17[14] = v13 + v7 + 29;
      v17[15] = 480;
      pObj5 = sub_418DD0(176);  // 调 资源句柄 (101)
      if ( pObj5 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v7 + 29, v35 + 15, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      sub_488670(dword_79C0B0);  // 调 视口重置 640x480
      v19 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
      v19[13] = 0;
      v19[14] = v30 + v7 + 29;
      v19[15] = 480;
      pObj7 = sub_418DD0(177);  // 调 资源句柄 (101)
      if ( pObj7 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v7 + 29, v35 + 23, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      sub_488670(dword_79C0B0);  // 调 视口重置 640x480
      dword_8F85202 = dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
      if ( *(int *)((char *)pThis_33 + v26 + sub_656710(v23)) != -1 && *(int *)((char *)pThis_33 + v25 + dword_8F85202) != 0 )  // 调 取全局单例地址（返回 unk_9BD5D0）
      {
        sub_4938F0(*(this + 55));  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
        sub_491D00(dword_79C0B0, v7 + 6, v35 + 5, 0.0);  // 调 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 31);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
        if ( *(uint32_t *)(v29 + 40) < 0x10u )
          v21 = v29 + 20;
        else
          v21 = *(uint32_t *)(v29 + 20);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          v7 + 31,
          v35,
          -1,
          v21);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
        sub_4611D0(this, v34, v7, v35);  // 调 网络延迟三档指示与 Realy 红字
      }
      v2 = v24;
      *(uint8_t *)(*pThis_33 + 16) = 1;  // this+16 频道型选中索引
      result = pThis_33;
    }
    else
    {
      *(uint8_t *)(*result + 16) = 0;
    }
    ++result;
    v22 = (int)v34 + 1 < 4;
    v34 = (bool (/*cdecl*/ *)(struct Concurrency::details::_UnrealizedChore *, void *))((char *)v34 + 1);
    pThis_33 = result;
  }
  while ( v22 );
  return result;
}


// ============================================================
// 【分区 3】快捷栏与图标拖放（0x4622A0-0x463C90）
// ICON_DROP_TO_QUICKSLOT 自证（0x4633D0）。
// ============================================================
// ------------------------------------------------------------
// 0x4622A0 sub_4622A0 —— 与 ·sub_461F50 同构（差异：门控更严加网络指示）
// 差异：门控为 sub_456390(0) 不为 1 或 dword_8F8528 第 2 槽非 0 且非 2，且额外要求实体 +196 非 0；
// 另多出 sub_698F90/699000 计时、sub_461370 网络统计叠字与尾调 ·sub_4611D0 延迟指示。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4622A0(int *this)  // 函数: 与 ·sub_461F50 同构（差异：门控更严加网络指示）
{
  int v1; // edi
  uint32_t *result; // eax
  int v4; // edx
  int v5; // ecx
  int pObj2; // edi
  int v7; // eax
  int v8; // ebx
  int v9; // edx
  uint32_t *v10; // eax
  int pObj7; // eax
  int pObj3; // eax
  int pObj; // eax
  int pObj6; // eax
  int v15; // eax
  int v16; // eax
  uint32_t *v17; // eax
  int pObj5; // eax
  uint32_t *v19; // eax
  int pObj8; // eax
  int v21; // ecx
  int pObj4; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  bool v27; // cc
  int v28; // [esp-8h] [ebp-38h]
  int v29; // [esp+14h] [ebp-1Ch]
  int dword_8F85202; // [esp+14h] [ebp-1Ch]
  int v31; // [esp+14h] [ebp-1Ch]
  int Valueb; // [esp+18h] [ebp-18h]
  int Valuec; // [esp+18h] [ebp-18h]
  int Value; // [esp+18h] [ebp-18h]
  int Valuea; // [esp+18h] [ebp-18h]
  int v36; // [esp+1Ch] [ebp-14h]
  uint32_t *pThis_33; // [esp+20h] [ebp-10h]
  int pThis_3A; // [esp+24h] [ebp-Ch]
  bool (/*cdecl*/ *v39)(struct Concurrency::details::_UnrealizedChore *, void *); // [esp+28h] [ebp-8h]
  int v40; // [esp+2Ch] [ebp-4h]

  v1 = *((uint32_t *)dword_8F8528 + 1);  // dword_8F8528 = 主管理器
  result = (uint32_t *)sub_456390(0);  // 调 存 座位号查询
  if ( result != (uint32_t *)1 || v1 != 0 && v1 != 2 )  // 若 v1 != 0 与/或 v1 != 2
  {
    pThis_3A = (int)(this + 58);  // this+232 = 基类时刻同步开关位
    v4 = -188 - (uint32_t)this;
    result = this + 51;  // this+204〔主状态参数〕
    v39 = nullptr;
    pThis_33 = this + 51;  // this+204〔主状态参数〕
    do
    {
      v5 = *(uint32_t *)((char *)result + v4 + dword_8F850C);  // 房间/席位表
      v36 = v5;
      if ( v5 != 0 )
        pObj2 = *(uint32_t *)(v5 + 196);
      else
        pObj2 = 0;
      if ( v5 != 0 && pObj2 != 0 )  // 若 v5 != 0 与/或 pObj2 != 0
      {
        v7 = *result;
        v8 = *(uint32_t *)(v7 + 20);
        v9 = *(uint32_t *)(v7 + 24);
        v10 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
        *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
        v10[13] = 0;
        v10[14] = v8 + 88;
        v10[15] = 480;
        v40 = v9;
        pObj7 = sub_418DD0(173);  // 调 资源句柄 (101)
        if ( pObj7 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v8, v40, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        sub_488670(dword_79C0B0);  // 调 视口重置 640x480
        pObj3 = sub_418DD0(174);  // 调 资源句柄 (101)
        if ( pObj3 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v8 + 88, v40 + 13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        pObj = sub_42B340(v36);  // 调 虚拟角色惰性创建（0x294 字节）
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)pObj + 384))(  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
          pObj,
          v8 + 2,
          v40 + 2,
          24,
          24,
          1065353216);  // 常量 1.0f
        if ( (bool (/*cdecl*/ *)(struct Concurrency::details::_UnrealizedChore *, void *))sub_456480(dword_8F850C) == v39 )  // 房间/席位表
        {
          pObj6 = sub_418DD0(192);  // 调 资源句柄 (101)
          if ( pObj6 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, v8 + 1, v40 + 1, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        }
        Valueb = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 740))(pObj2);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 736))(pObj2);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
        v29 = (uint64_t)sub_4049C0(0.0, 59.0, v15, Valueb);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
        Valuec = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 756))(pObj2);  // 调用虚函数（虚表槽 +756）【推断: [RTTI: IRDActiveObject__vmt2F4 ·…】
        v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 752))(pObj2);  // 调用虚函数（虚表槽 +752）
        Value = (uint64_t)sub_4049C0(0.0, 59.0, v16, Valuec);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
        v17 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
        *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
        v17[13] = 0;
        v17[14] = v29 + v8 + 29;
        v17[15] = 480;
        pObj5 = sub_418DD0(176);  // 调 资源句柄 (101)
        if ( pObj5 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v8 + 29, v40 + 15, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        sub_488670(dword_79C0B0);  // 调 视口重置 640x480
        v19 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
        *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
        v19[13] = 0;
        v19[14] = Value + v8 + 29;
        v19[15] = 480;
        pObj8 = sub_418DD0(177);  // 调 资源句柄 (101)
        if ( pObj8 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, v8 + 29, v40 + 23, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        sub_488670(dword_79C0B0);  // 调 视口重置 640x480
        dword_8F85202 = dword_8F8520;  // dword_8F8520 = 会话/UDP 管理器
        if ( *(uint32_t *)((char *)pThis_33 + (uint32_t)((char *)sub_656710() - 204 - (uint32_t)this)) != -1  // 调 取全局单例地址（返回 unk_9BD5D0）
          && *(uint32_t *)((char *)pThis_33 + 1048444 - (uint32_t)this + dword_8F85202) != 0 )  // 会话/UDP 管理器
        {
          sub_4938F0(*(this + 55));  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
          sub_491D00(dword_79C0B0, v8 + 6, v40 + 5, 0.0);  // 调 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 31);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
          if ( *(uint32_t *)(v36 + 40) < 0x10u )
            v21 = v36 + 20;
          else
            v21 = *(uint32_t *)(v36 + 20);
          (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
            dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
            v8 + 31,
            v40,
            -1,
            v21);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
          sub_4611D0(this, v39, v8, v40);  // 调 网络延迟三档指示与 Realy 红字
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 1196))(pObj2) != 0 )  // 调用虚函数（虚表槽 +1196）
        {
          if ( *((uint8_t *)this + (uint32_t)v39 + 224) == 0 )
          {
            *(uint8_t *)(pThis_3A + 13) = 0;  // pThis_3A=this+232 动画时刻同步开关
            *(uint8_t *)(pThis_3A + 14) = 0;  // pThis_3A=this+232 动画时刻同步开关
            sub_698F90(pThis_3A, 0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
            *((uint8_t *)this + (uint32_t)v39 + 224) = 1;
          }
        }
        else if ( *((uint8_t *)this + (uint32_t)v39 + 224) != 0 )
        {
          *((uint8_t *)this + (uint32_t)v39 + 224) = 0;
        }
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 && *((uint8_t *)this + (uint32_t)v39 + 224) != 0 )  // dword_8F7A24 = 当前场景状态对象
        {
          if ( sub_699000(pThis_3A) >= 1000 || ((sub_699000(pThis_3A) / 0xFAu) & 1) == 0 )  // clock_now(clk)
          {
            pObj4 = sub_418DD0(91);  // 调 资源句柄 (101)
            if ( pObj4 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v8 + 2, v40 + 2, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          }
          if ( *(uint32_t *)(dword_8F7A24 + 12) == 3  // dword_8F7A24 = 当前场景状态对象
            && sub_699000(pThis_3A) < 10000  // clock_now(clk)
            && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4)) != 0  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
            && v39 != (bool (/*cdecl*/ *)(struct Concurrency::details::_UnrealizedChore *, void *))sub_456420(dword_8F850C)  // 房间/席位表
            && (uint8_t)sub_49BE70(*(uint32_t *)(*(this + 1) + 2420)) == 0 )  // 调 会话数值 >= 槽值判定（+134 对 +108/+108）
          {
            Valuea = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
            if ( Valuea > 0 )
            {
              v23 = sub_418DD0(12);  // 调 资源句柄 (101)
              sub_40FC80(v8, v40 + 24, v23);  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
              if ( ((sub_699000(pThis_3A) / 0xFAu) & 1) == 0 )  // clock_now(clk)
              {
                v24 = sub_418DD0(13);  // 调 资源句柄 (101)
                sub_40FC80(v8 + 2, v40 + 25, v24);  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
              }
              (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 114);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
              if ( ((uint8_t)v39 & 1) != 0 )
                v25 = sub_422E70(242);  // 调 存 CStringManager::getStr 取本地化串
              else
                v25 = sub_422E70(241);  // 调 存 CStringManager::getStr 取本地化串
              v28 = v25;
              v31 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
              v26 = sub_422E70(240);  // 调 存 CStringManager::getStr 取本地化串
              (*(void (/*cdecl*/ **)(int, int, int, int, int, int, int))(v31 + 80))(  // 调用虚函数（虚表槽 +80）
                dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
                v8 + 29,
                v40 + 45,
                -4331009,
                v26,
                (int)v39 + 1,
                v28);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
              sub_69A110(v8 + 71, v40 + 74, Valuea, -1);
            }
          }
        }
        sub_461370(v39, v8, v40, 2, 33);  // 调 网络统计调试叠字（两行三色）
        *(uint8_t *)(*pThis_33 + 16) = 1;  // this+16 频道型选中索引
        v4 = -188 - (uint32_t)this;
        result = pThis_33;
      }
      else
      {
        *(uint8_t *)(*result + 16) = 0;
      }
      ++result;
      v27 = (int)v39 + 1 < 4;
      v39 = (bool (/*cdecl*/ *)(struct Concurrency::details::_UnrealizedChore *, void *))((char *)v39 + 1);
      pThis_33 = result;
      pThis_3A += 28;  // pThis_3A=this+232 动画时刻同步开关
    }
    while ( v27 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x462870 sub_462870 —— 出屏队友边缘箭头与名字标注
// 仅域号 3/4：遍历 4 槽（域 4 经 sub_48F690 取），跳过自身并 sub_45E680 归属判定。
// sub_4239A0/4239D0 取坐标；越出 -20..660 时按左右选 88..91 号箭头图落 (12 或 619, y-70)。
// 名字文本绘于 (左侧 24 / 右侧 545, y 坐标 -67)，与箭头同色 -1 或 -16776961。
// ------------------------------------------------------------
char /*usercall*/ sub_462870@<al>(int nArg1@<ecx>, int nArg2@<ebx>)  // 实现：出屏队友边缘箭头与名字标注
{
  int v2; // eax
  uint32_t *v3; // esi
  int v4; // edi
  int v5; // eax
  int pObj; // ebx
  int v7; // esi
  int v8; // edi
  int v9; // eax
  bool v10; // bl
  int v11; // eax
  int pObj2; // eax
  int v13; // ebx
  int v14; // ecx
  int v17; // [esp+0h] [ebp-20h]
  int v19; // [esp+8h] [ebp-18h]
  int v20; // [esp+Ch] [ebp-14h]
  int v21; // [esp+10h] [ebp-10h]
  int v22; // [esp+14h] [ebp-Ch]
  uint32_t *v23; // [esp+18h] [ebp-8h]
  char v24; // [esp+1Fh] [ebp-1h]

  v2 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 = 当前场景状态对象
  if ( v2 == 3 || v2 == 4 )  // 若 v2 == 3 与/或 v2 == 4
  {
    v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
    v3 = *(uint32_t **)(v2 + 104);
    v23 = v3;
    if ( v3 != nullptr )  // 若 v3 有效（非空）
    {
      LOBYTE(v2) = *(uint32_t *)(dword_8F7A24 + 12) == 4;  // 调 取 16 位值低 8 位
      v24 = v2;
      if ( *(uint32_t *)(dword_8F7A24 + 12) != 4 || dword_99FEC0 != 0 )  // dword_8F7A24 = 当前场景状态对象
      {
        v4 = 0;
        v19 = 0;
        v17 = 4 * (*(uint32_t *)(dword_8F7A24 + 12) == 4) + 4;  // dword_8F7A24 = 当前场景状态对象
        if ( 4 * (*(uint32_t *)(dword_8F7A24 + 12) == 4) != -4 )  // dword_8F7A24 = 当前场景状态对象
        {
          v22 = 16;
          while ( 1 )  // 无限循环
          {
            if ( (uint8_t)v2 != 0 )
              v5 = sub_48F690(v4);  // 调 槽 id 解析·第二组（偏移 +10）
            else
              v5 = *(uint32_t *)(v22 + dword_8F850C);  // 房间/席位表
            v21 = v5;
            if ( v5 != 0 )
            {
              pObj = *(uint32_t *)(v5 + 196);
              if ( pObj != 0 && pObj != dword_8F7C04 && sub_45E680(v3, *(uint32_t *)(v5 + 196)) != 0 )  // 调 对象表归属判定
              {
                v7 = sub_4239A0(pObj);  // 调 取值后转坐标与方向合成
                v20 = sub_4239D0(pObj, 1.0);  // 调 取值后转插值族
                if ( v7 < -20 || v7 >= 660 )  // 若 v7 < -20 与/或 v7 >= 660
                {
                  v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 376))(pObj, nArg2);  // 调用虚函数（虚表槽 +376）
                  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);  // 调用虚函数（虚表槽 +376）
                  v10 = v8 == v9;
                  if ( v7 >= 0 )
                    v11 = 90 - (v8 == v9);
                  else
                    v11 = 88 - (v8 == v9);
                  pObj2 = sub_418DD0(v11);  // 调 资源句柄 (101)
                  if ( pObj2 != 0 )
                    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                      pObj2,
                      v7 >= 0 ? 619 : 12,
                      v20 - 70,
                      dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
                  v13 = v10 ? -1 : -16776961;
                  nArg2 = 52 * (v7 >= 0) + nArg1 + 1024;
                  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
                  if ( *(uint32_t *)(v21 + 40) < 0x10u )
                    v14 = v21 + 20;
                  else
                    v14 = *(uint32_t *)(v21 + 20);
                  (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
                    dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
                    v7 >= 0 ? 545 : 24,
                    v20 - 67,
                    v13,
                    v14);
                  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
                  v4 = v19;
                }
                v3 = v23;
              }
            }
            LOBYTE(v2) = v17;  // 调 取 16 位值低 8 位
            v19 = ++v4;
            v22 += 4;
            if ( v4 >= v17 )
              break;
            LOBYTE(v2) = v24;  // 调 取 16 位值低 8 位
          }
        }
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x462A90 sub_462A90 —— premiumService 会员面板绘制
// 状态 +1244：为 0 置 -1，为 1 走 4 秒倒计时 this+1248；按 +1240/+1241 双标志选 47/192 与基准 144 号图。
// 图源 Interface/premiumService.img（路径自证），sub_43BEE0 排版上屏。
// dword_796E50 全局解引用守卫为本文件多处通用序言。
// ------------------------------------------------------------
char /*thiscall*/ sub_462A90(int this)  // 函数: premiumService 会员面板绘制
{
  int fld_4DC; // eax
  int v3; // ebx
  int v4; // eax
  double v5; // st7
  int v6; // esi
  int pObj2; // eax
  int pObj3; // eax
  int pObj; // eax
  int pObj4; // eax
  int pObj6; // eax
  int pObj5; // eax
  int fld_4F8; // edi
  int pThis_4E0; // esi
  int v15; // eax
  int dword_8F7A242; // ecx
  int v17; // ebx
  int i; // esi
  int v19; // eax
  double v20; // st7
  int v21; // ecx
  const char *v22; // eax
  const char *v23; // eax
  const char *v24; // eax
  int v26; // [esp-4h] [ebp-128h]
  int pThis_4E02; // [esp+0h] [ebp-124h]
  int pThis_4E03; // [esp+0h] [ebp-124h]
  int v29; // [esp+4h] [ebp-120h]
  int v30; // [esp+14h] [ebp-110h]
  float v31; // [esp+14h] [ebp-110h]
  float v33; // [esp+18h] [ebp-10Ch]
  char v34; // [esp+1Fh] [ebp-105h]
  char Buffer[256]; // [esp+20h] [ebp-104h] BYREF
  int dword_796E502; // [esp+120h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  fld_4DC = *(uint32_t *)(this + 1244);  // this+1244〔nTagTimer〕
  LOBYTE(v3) = -1;  // 调 取 16 位值低 8 位
  if ( fld_4DC != 0 )  // fld_4DC=this+1244 nTagTimer
  {
    v4 = fld_4DC - 1;
    if ( v4 != 0 )
    {
      if ( v4 != 2 )
      {
LABEL_7:
        (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
          dword_8F84B8,  // dword_8F84B8＝vt+60
          "Interface/premiumService.img");  // 资源路径 Interface/premiumService.img
        v6 = 144;
        v30 = 144;
        if ( *(uint8_t *)(this + 1240) == 1 )
        {
          if ( *(uint8_t *)(this + 1241) == 1 )
          {
            v6 = 47;
            v30 = 192;
          }
          sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
          pObj2 = sub_418DD0(0);  // 调 资源句柄 (101)
          if ( pObj2 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 调用虚函数（虚表槽 +128）
              pObj2,
              72,
              v6,
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              1065353216,  // 常量 1.0f
              1065353216,  // 常量 1.0f
              0,
              ((uint8_t)v3 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          pObj3 = sub_418DD0(2);  // 调 资源句柄 (101)
          if ( pObj3 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 调用虚函数（虚表槽 +128）
              pObj3,
              72,
              v6,
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              1065353216,  // 常量 1.0f
              1065353216,  // 常量 1.0f
              0,
              ((uint8_t)v3 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
          pObj = sub_418DD0(1);  // 调 资源句柄 (101)
          if ( pObj != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
              pObj,
              72,
              v6,
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              1065353216,  // 常量 1.0f
              1065353216,  // 常量 1.0f
              0,
              ((uint8_t)v3 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
        }
        if ( *(uint8_t *)(this + 1241) == 1 )
        {
          sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
          pObj4 = sub_418DD0(0);  // 调 资源句柄 (101)
          if ( pObj4 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(  // 调用虚函数（虚表槽 +128）
              pObj4,
              72,
              v30,
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              1065353216,  // 常量 1.0f
              1065353216,  // 常量 1.0f
              0,
              ((uint8_t)v3 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          pObj6 = sub_418DD0(4);  // 调 资源句柄 (101)
          if ( pObj6 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj6 + 128))(  // 调用虚函数（虚表槽 +128）
              pObj6,
              72,
              v30,
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              1065353216,
              1065353216,
              0,
              ((uint8_t)v3 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
          sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
          pObj5 = sub_418DD0(3);  // 调 资源句柄 (101)
          if ( pObj5 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(  // 调用虚函数（虚表槽 +128）
              pObj5,
              72,
              v30,
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              1065353216,
              1065353216,
              0,
              ((uint8_t)v3 << 24) | 0xFFFFFF,
              1333788672,
              1333788672);
        }
        fld_4F8 = *(uint32_t *)(this + 1272);
        pThis_4E0 = this + 1248;
        if ( sub_699000(this + 1248) < fld_4F8 )  // clock_now(clk)
        {
          v15 = sub_699000(pThis_4E0);  // clock_now(clk)
          if ( v15 >= 1000 )
          {
            if ( sub_699000(pThis_4E0) >= 3000 )  // clock_now(clk)
            {
              v15 = sub_699000(pThis_4E0);  // clock_now(clk)
              if ( v15 < 4000 )
                *(uint32_t *)(this + 1244) = 3;  // this+1244〔nTagTimer〕
            }
            else
            {
              *(uint32_t *)(this + 1244) = 2;  // this+1244〔nTagTimer〕
              LOBYTE(v15) = this;  // 调 取 16 位值低 8 位
            }
          }
          else
          {
            *(uint32_t *)(this + 1244) = 1;  // this+1244〔nTagTimer〕
          }
        }
        else
        {
          *(uint8_t *)(this + 1260) = 0;  // this+1260〔pCondVec1260〕
          *(uint32_t *)(this + 1244) = -1;  // this+1244〔nTagTimer〕
          LOBYTE(v15) = this;  // 调 取 16 位值低 8 位
        }
        return v15;
      }
      pThis_4E02 = sub_699000(this + 1248);  // clock_now(clk)
      v5 = sub_4049C0(255.0, 0.0, pThis_4E02, 4000);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
    }
    else
    {
      pThis_4E03 = sub_699000(this + 1248);  // clock_now(clk)
      v5 = sub_4049C0(0.0, 255.0, pThis_4E03, 1000);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
    }
    v3 = (uint64_t)v5;
    goto LABEL_7;
  }
  dword_8F7A242 = dword_8F7A24;  // dword_8F7A24 = 当前场景状态对象
  v34 = 0;
  v17 = 1;
  for ( i = 312; i < 344; i += 4 )
  {
    if ( *(uint8_t *)(dword_8F7A242 + v17 + 297) != 0 )  // 登录/选区管理器
    {
      v19 = *(uint32_t *)(i + dword_8F7A242);  // 登录/选区管理器
      if ( v19 != 0 )
      {
        v20 = (double)*(int *)(i + dword_8F7A242);  // 登录/选区管理器
        if ( v19 < 0 )
          v20 = v20 + 4294967300.0;
        v31 = 0.000011574074 * v20;
        v21 = sub_41C4B0(v17);  // 调 索引取字符串资源（文本表）【推断】
        switch ( v17 )  // 按 v17 分派
        {
          case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
          case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
          case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
          case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
          case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
            v26 = v21;
            if ( v31 <= 1.0 )
            {
              v23 = (const char *)sub_422E70(244);  // 调 存 CStringManager::getStr 取本地化串
              v33 = v20 * 0.00027777778;
              sprintf(Buffer, v23, v26, v33);  // 调 格式化到缓冲
            }
            else
            {
              v22 = (const char *)sub_422E70(243);  // 调 存 CStringManager::getStr 取本地化串
              sprintf(Buffer, v22, v26, v31);  // 调 格式化到缓冲
            }
            break;
          case 4:  // case 4 = ENUM_CMDPACKET_EXIT
            v29 = v21;
            v24 = (const char *)sub_422E70(245);  // 调 存 CStringManager::getStr 取本地化串
            sprintf(Buffer, v24, v29);  // 调 格式化到缓冲
            break;
          default:
            break;
        }
        sub_43BEE0(*(uint32_t **)(*(uint32_t *)(this + 4) + 28), (int)Buffer, -6567706, 0, -1);  // 调 播报 + 面板刷新 ──
        if ( i > 308 && i <= 328 )  // 若 i > 308 与/或 i <= 328
          v34 = 1;
        dword_8F7A242 = dword_8F7A24;  // dword_8F7A24 = 当前场景状态对象
      }
    }
    ++v17;
  }
  LOBYTE(v15) = v34;  // 调 取 16 位值低 8 位
  if ( v34 != 0 )
  {
    *(uint8_t *)(this + 1260) = 1;  // this+1260〔pCondVec1260〕
    *(uint8_t *)(this + 1261) = 0;
    *(uint8_t *)(this + 1262) = 0;
    LOBYTE(v15) = sub_698F90(this + 1248, 4000, 0);  // 调 取 16 位值低 8 位
    *(uint32_t *)(this + 1244) = 1;  // this+1244〔nTagTimer〕
  }
  else
  {
    *(uint32_t *)(this + 1244) = -1;  // this+1244〔nTagTimer〕
  }
  return v15;
}


// ------------------------------------------------------------
// 0x462FD0 sub_462FD0 —— 席位/排行条（8 格与 120ms 滚动）
// dword_99FF08 表 +8 起值为 255 表示空位；pArg1+335 起 8 项由 ·sub_4632D0 排好序。
// 滚动量 pArg1[325] 由 sub_4049F0(当前, 目标=+326, 120, 1) 逐帧插值到 +327。
// 每格 sub_578E80 取角色、sub_42B340 建虚拟角色、vt+384 绘 15x14 头像，sub_418DD0(60) 绘底板，文本 %d/%d fp。
// ------------------------------------------------------------
int /*usercall*/ sub_462FD0@<eax>(uint32_t *pArg1@<ecx>, uint32_t *uArg2@<edi>)  // 实现：席位/排行条（8 格与 120ms 滚动）
{
  int result; // eax
  int v4; // eax
  double v5; // st7
  int v6; // ebx
  int v7; // ebx
  uint32_t *v8; // esi
  int v9; // edi
  int v10; // esi
  int v11; // eax
  int pObj; // eax
  int v13; // eax
  int pObj2; // eax
  int pObj3; // eax
  int v16; // ecx
  bool v17; // zf
  int dword_8F7A242; // eax
  uint32_t *v19; // eax
  const char *v20; // eax
  int v21; // eax
  const char *v22; // eax
  float v23; // [esp+0h] [ebp-98h]
  float v24; // [esp+4h] [ebp-94h]
  int v25; // [esp+4h] [ebp-94h]
  int v26; // [esp+8h] [ebp-90h]
  int v27; // [esp+8h] [ebp-90h]
  int v29; // [esp+Ch] [ebp-8Ch]
  int v30; // [esp+Ch] [ebp-8Ch]
  int v31; // [esp+18h] [ebp-80h]
  int v32; // [esp+1Ch] [ebp-7Ch]
  uint32_t *v33; // [esp+20h] [ebp-78h]
  int v34; // [esp+24h] [ebp-74h]
  int dword_99FF082; // [esp+28h] [ebp-70h]
  char Buffer[100]; // [esp+30h] [ebp-68h] BYREF
  int dword_796E502; // [esp+94h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  result = dword_99FF08;
  if ( dword_99FF08 != 0 )
  {
    if ( pArg1[325] != pArg1[326] )
    {
      v4 = sub_699000((int)(pArg1 + 328));  // clock_now(clk)
      v24 = (float)(int)pArg1[326];
      v5 = (double)(int)pArg1[327];
      v23 = v5;
      sub_4049F0(v23, v24, v4, 120, 1);  // 调 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
      pArg1[325] = (uint64_t)v5;
    }
    v6 = pArg1[325];
    dword_99FF082 = dword_99FF08;  // dword_99FF082＝dword_99FF08
    v32 = v6;
    result = sub_418DD0(60);  // 调 资源句柄 (101)
    if ( result != 0 )  // 若结果非 0（成功）
      result = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(result, v6, 61, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    if ( pArg1[325] != 618 )
    {
      v7 = v6 + 36;
      v8 = pArg1 + 335;
      v9 = 74;
      v33 = v8;
      v34 = 8;
      do
      {
        v10 = *v8;
        if ( *(uint32_t *)(dword_99FF082 + 4 * v10 + 8) != 255 )
        {
          v11 = sub_578E80(v10);  // 调 存 调: sub_578E80 sub_48F660
          v31 = v11;
          if ( v11 != 0 )
          {
            pObj = sub_42B340(v11);  // 调 虚拟角色惰性创建（0x294 字节）
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t *))(*(uint32_t *)pObj + 384))(  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
              pObj,
              v7,
              v9 - 2,
              15,
              14,
              1065353216,  // 常量 1.0f
              uArg2);
            v13 = *(uint32_t *)(dword_99FF082 + 4 * v10 + 8);  // dword_99FF082＝dword_99FF08
            if ( v13 == 1 || v13 == 2 )  // 若 v13 == 1 与/或 v13 == 2
            {
              sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
              pObj2 = sub_418DD0(61);  // 调 资源句柄 (101)
              if ( pObj2 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v7 + 15, v9 - 3, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
              sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
              pObj3 = sub_418DD0(74);  // 调 资源句柄 (101)
              if ( pObj3 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v7 - 1, v9 - 3, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            }
            uArg2 = pArg1 + 193;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
            if ( *(uint32_t *)(v31 + 40) < 0x10u )
              v16 = v31 + 20;
            else
              v16 = *(uint32_t *)(v31 + 20);
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              v7 + 22,
              v9,
              -1,
              v16);
            sprintf(Buffer, "%d/%d fp", *(uint32_t *)(dword_99FF082 + 4 * v10 + 112), *(uint32_t *)(dword_99FF082 + 4 * v10 + 80));  // 调 格式化到缓冲
            (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              v7 + 105,
              v9,
              -16731649,
              Buffer);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
          }
        }
        v8 = v33 + 2;
        v9 += 19;
        v17 = v34 == 1;
        v33 += 2;
        --v34;
      }
      while ( !v17 );
      (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 193);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
      dword_8F7A242 = dword_8F7A24;  // dword_8F7A24 = 当前场景状态对象
      if ( *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 104) != 0 )  // dword_8F7A24 = 当前场景状态对象
      {
        v19 = *(uint32_t **)(dword_8F7A24 + 40);  // dword_8F7A24 = 当前场景状态对象
        v29 = v19[32];
        v26 = v19[33];
        v25 = v19[22];
        v20 = (const char *)sub_422E70(1902);  // 调 存 CStringManager::getStr 取本地化串
        sprintf(Buffer, v20, v25, v26, v29);  // 调 格式化到缓冲
        (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          v32 + 33,
          237,
          -16731649,
          Buffer);
        dword_8F7A242 = dword_8F7A24;  // dword_8F7A24 = 当前场景状态对象
      }
      v21 = *(uint32_t *)(dword_8F7A242 + 40);  // 登录/选区管理器
      v30 = *(uint32_t *)(v21 + 92);
      v27 = *(uint32_t *)(v21 + 88);
      v22 = (const char *)sub_422E70(1903);  // 调 存 CStringManager::getStr 取本地化串
      sprintf(Buffer, v22, v27, v30);  // 调 格式化到缓冲
      (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        v32 + 33,
        253,
        -16731649,
        Buffer);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4632D0 sub_4632D0 —— 席位表快照与排序
// dword_99FF08 表 +80 起 8 个值写入 this+335 起（成对 序号加图像值），255 记为 -1。
// 随后 qsort(this+335, 8, 8, ·sub_461550) 按第 2 字段升序。
// ------------------------------------------------------------
void /*thiscall*/ sub_4632D0(uint32_t *this)  // 函数: 席位表快照与排序
{
  int v1; // esi
  int v2; // eax
  uint32_t *pThis_150; // edx
  int v4; // edi

  if ( dword_99FF08 != 0 )
  {
    v1 = 0;
    v2 = 80;
    pThis_150 = this + 336;
    v4 = dword_99FF08 - 72;
    do
    {
      *(pThis_150 - 1) = v1;
      if ( *(uint32_t *)(v4 + v2) == 255 )
        *pThis_150 = -1;
      else
        *pThis_150 = *(uint32_t *)(v2 + dword_99FF08);
      v2 += 4;
      ++v1;
      pThis_150 += 2;
    }
    while ( v2 < 112 );
    qsort(this + 335, 8u, 8u, (_CoreCrtNonSecureSearchSortCompareFunction)sub_461550);  // 调 快速排序
  }
}



// ------------------------------------------------------------
// 0x463340 sub_463340 —— 池 67 对象回收与借出切换
// 仅域号 3：this 的 +1208..+1212 向量非空则 sub_44E850 回收池 67，否则 sub_44E8D0 借出池 0x43(=67)。
// 两路均补播 CLICK_BUTTON1（串自证）。
// ------------------------------------------------------------
void */*thiscall*/ sub_463340(char **this)  // 函数: 池 67 对象回收与借出切换
{
  void *result; // eax
  char *fld_e1; // ecx
  int v3; // edx

  result = (void *)dword_8F7A24;  // dword_8F7A24 = 当前场景状态对象
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )  // dword_8F7A24 = 当前场景状态对象
  {
    fld_e1 = *(this + 1);  // this+4〔宿主对象〕
    v3 = *((uint32_t *)fld_e1 + 302);  // fld_e1=this+4 宿主对象
    if ( v3 != 0 && (*((uint32_t *)fld_e1 + 303) - v3) >> 2 != 0 )  // fld_e1=this+4 宿主对象
    {
      sub_44E850(fld_e1, 67);  // 调 按池号批量回收活动对象
      return sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 调 音效播放包装（非空判定）
    }
    else
    {
      sub_44E8D0(fld_e1, (void *)0x43, 0, 0);  // 调 对象池借出（按池号取可用对象）
      return sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 调 音效播放包装（非空判定）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4633B0 sub_4633B0 —— std::string 取数据指针（SSO 判定）
// 容量字段 this+78 小于 0x10 时数据在栈内 this+73，否则取堆指针。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4633B0(uint32_t *this)  // 函数: std::string 取数据指针（SSO 判定）
{
  if ( *(this + 78) < 0x10u )  // this+78 【推断】公会标志字节 C
    return this + 73;  // 返回 this + 73
  else
    return (uint32_t *)*(this + 73);  // this+292〔nOpenMode292(推断)〕
}



// ------------------------------------------------------------
// 0x4633D0 sub_4633D0
// ------------------------------------------------------------
// ★ 快捷栏拖放 —— ICON_DROP_TO_QUICKSLOT 自证（2939/2977 行附近）：
// 拖拽源/目标格命中 → 物品换位/落格【推断】
char /*thiscall*/ sub_4633D0(uint32_t *this)  // 实现：拖拽源/目标格命中 → 物品换位/落格(推断)
{
  int v1; // esi
  int v2; // edi
  int v3; // eax
  uint32_t *pThis_3; // ecx
  int v5; // eax
  uint32_t *pThis_9; // ecx
  uint32_t *fld_e1; // ecx
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int fld_e2; // eax
  int v16; // eax
  int v17; // eax
  int v18; // ebx
  int v19; // eax
  unsigned int v20; // edi
  int v21; // esi
  int v22; // eax
  int v23; // esi
  int v24; // eax
  int i; // edi
  int v26; // edx
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int fld_e23; // eax
  int v32; // eax
  int pObj4; // eax
  int pObj; // ebx
  uint32_t *v35; // eax
  char v36; // al
  int v37; // ecx
  int v38; // esi
  int v39; // esi
  int v40; // eax
  uint32_t *v41; // eax
  int fld_e22; // eax
  int v43; // eax
  int v44; // eax
  int v45; // ecx
  int pObj7; // ebx
  int v47; // esi
  int v48; // edx
  int v49; // edi
  int v50; // ebx
  int v51; // edi
  int v52; // eax
  int j; // edx
  int pObj6; // eax
  int v55; // eax
  int v56; // edi
  int pObj3; // ebx
  int pObj5; // eax
  int pObj2; // esi
  int v60; // edi
  int v61; // eax
  int pObj8; // eax
  int pObj9; // esi
  int v64; // eax
  int v65; // eax
  int v66; // ecx
  int v67; // eax
  void *dword_8F852C2; // [esp-8h] [ebp-20h]
  int v69; // [esp+Ch] [ebp-Ch]
  int v70; // [esp+Ch] [ebp-Ch]
  int v71; // [esp+Ch] [ebp-Ch]
  uint32_t *fld_e12; // [esp+14h] [ebp-4h]

  v1 = -1;
  v2 = -1;
  v3 = 0;
  v69 = -1;
  pThis_3 = this + 3;  // this+12〔nSkillRec12〕
  while ( *(uint8_t *)(*pThis_3 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*pThis_3 + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    ++v3;
    ++pThis_3;
    if ( v3 >= 6 )
      goto LABEL_7;
  }
  v2 = v3;
LABEL_7:
  v5 = 0;
  pThis_9 = this + 9;
  while ( *(uint8_t *)(*pThis_9 + 17) == 0 || dword_79BE34 != *(uint32_t *)(*pThis_9 + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    ++v5;
    ++pThis_9;
    if ( v5 >= 6 )
      goto LABEL_13;
  }
  v1 = v5;
  v69 = v5;
LABEL_13:
  fld_e1 = (uint32_t *)*(this + 1);  // this+4 = pHostObj
  v8 = fld_e1[626];  // fld_e1=this+4 宿主对象
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  switch ( v8 )  // 按 v8 分派
  {
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
      if ( v1 == -1 )
        return 0;
      if ( v1 >= *(uint32_t *)dword_8F853C )  // 容器对象指针(容量比较)
        return 0;
      v66 = *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * v1);  // 容器对象指针(容量比较)
      if ( v66 == 0 )
        return 0;
      v67 = *(uint32_t *)(v66 + 392);
      if ( v67 == 0 || (*(uint32_t *)(v66 + 396) - v67) / 44 == 0 )
        return 0;
      if ( v8 == 10 )
      {
        sub_47E7A0(1, 1);  // 调 pszArg3 时播 SEAL_ON/SEAL_OFF（sub_432EA0）+ sub_44E850(18) + sub_48BA…
        return 1;  // 返回 1(成功)
      }
      sub_47E7A0(0, 1);  // 调 pszArg3 时播 SEAL_ON/SEAL_OFF（sub_432EA0）+ sub_44E850(18) + sub_48BA…
      return 1;  // 返回 1(成功)
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( v2 != -1 )
      {
        v9 = v2 + 3;
        if ( v9 < *((uint32_t *)dword_8F852C + 2) )  // dword_8F852C = UI 管理器全局
        {
          v10 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v9);  // dword_8F852C = UI 管理器全局
          if ( v10 != 0 )
          {
            sub_44F2E0(v10, 1);  // 调 出售入口分发
            return 1;  // 返回 1(成功)
          }
        }
      }
      return 0;
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      if ( v2 != -1 )
      {
        v12 = v2 + 3;
        if ( v12 < *((uint32_t *)dword_8F852C + 2) )  // dword_8F852C = UI 管理器全局
        {
          v13 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v12);  // dword_8F852C = UI 管理器全局
          if ( v13 != 0 )
          {
            sub_44F400(v13, 1);  // 调 修理入口
            return 1;  // 返回 1(成功)
          }
        }
      }
      return 0;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      v14 = fld_e1[627];  // fld_e1=this+4 宿主对象
      if ( v14 != 0 )
      {
        if ( v14 == 1 && v1 != -1 )  // 若 v14 == 1 与/或 v1 != -1
        {
          v27 = fld_e1[629];  // fld_e1=this+4 宿主对象
          if ( v27 < *(uint32_t *)dword_8F853C )  // 容器对象指针(容量比较)
          {
            v28 = *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * v27);  // 容器对象指针(容量比较)
            if ( v28 != 0 && sub_41A5E0(v28 + 4) == fld_e1[628] )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
            {
              v29 = fld_e12[629];
              if ( v1 != v29 )
              {
                sub_483E70(v29, v1, 1);  // 调 技能槽交换请求（包 op 30，先做占用校验后本地预交换）
                sub_432EA0("ICON_DROP", -1, 0, 0);  // 调 音效播放包装（非空判定）
                return 1;  // 返回 1(成功)
              }
            }
          }
        }
      }
      else
      {
        if ( v1 != -1 )
          goto LABEL_38;
        fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
        if ( *(uint8_t *)(fld_e2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e2 + 12) )  // 当前动画对象指针(帧同步比对基准)
        {
          v16 = 0;
          while ( v16 < *(uint32_t *)dword_8F853C && *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * v16) != 0 )  // 容器对象指针(容量比较)
          {
            if ( ++v16 >= 6 )
              return 0;
          }
          v1 = v16;
          v69 = v16;
          if ( v16 != -1 )
          {
LABEL_38:
            v17 = fld_e1[629];  // fld_e1=this+4 宿主对象
            if ( v17 < *(uint32_t *)dword_8F853C )  // 容器对象指针(容量比较)
            {
              v18 = *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * v17);  // 容器对象指针(容量比较)
              if ( v18 != 0 && sub_41A5E0(v18 + 4) == fld_e1[628] )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
              {
                if ( v1 >= *(uint32_t *)dword_8F853C  // 容器对象指针(容量比较)
                  || (v19 = *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * v69)) == 0  // 容器对象指针(容量比较)
                  || (v20 = v19 + 128, (v21 = sub_41A5E0(v19 + 128)) == sub_41A5E0(v18 + 128)) )  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
                {
                  sub_483E70(fld_e12[629], v69, 1);  // 调 技能槽交换请求（包 op 30，先做占用校验后本地预交换）
                  sub_432EA0("ICON_DROP_TO_QUICKSLOT", -1, 0, 0);  // 调 音效播放包装（非空判定）
                  return 1;  // 返回 1(成功)
                }
                else
                {
                  v22 = sub_41A5E0(v20);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
                  v23 = *(uint32_t *)dword_8F853C;  // 容器对象指针(容量比较)
                  v24 = 42 * v22 + 6;
                  for ( i = 0; i < 42; i += 6 )
                  {
                    if ( v24 >= v23 )
                      break;
                    v26 = *((uint32_t *)dword_8F853C + 1);  // 容器对象指针(容量比较)
                    if ( *(uint32_t *)(v26 + 4 * v24) == 0 )
                      break;
                    if ( ++v24 >= v23 )
                      break;
                    if ( *(uint32_t *)(v26 + 4 * v24) == 0 )
                      break;
                    if ( ++v24 >= v23 )
                      break;
                    if ( *(uint32_t *)(v26 + 4 * v24) == 0 )
                      break;
                    if ( ++v24 >= v23 )
                      break;
                    if ( *(uint32_t *)(v26 + 4 * v24) == 0 )
                      break;
                    if ( ++v24 >= v23 )
                      break;
                    if ( *(uint32_t *)(v26 + 4 * v24) == 0 )
                      break;
                    if ( ++v24 >= v23 )
                      break;
                    if ( *(uint32_t *)(v26 + 4 * v24) == 0 )
                      break;
                    ++v24;
                  }
                  sub_483F40(v24, v69, fld_e12[629]);  // 调 技能槽两步交换（依次两次 ·sub_483E70，允许数 1、2）
                  sub_432EA0("ICON_DROP_TO_QUICKSLOT", -1, 0, 0);  // 调 音效播放包装（非空判定）
                  return 1;  // 返回 1(成功)
                }
              }
            }
          }
        }
      }
      return 0;
    default:
      break;
  }
  if ( v8 != 2 )
    return 0;
  v30 = fld_e1[627];  // fld_e1=this+4 宿主对象
  if ( v30 != 2 )
  {
    switch ( v30 )  // 按 v30 分派
    {
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        if ( v2 == -1 )
        {
          fld_e22 = *(this + 2);  // this+8 = 技能槽记录首字
          if ( *(uint8_t *)(fld_e22 + 17) == 0 || dword_79BE34 != *(uint32_t *)(fld_e22 + 12) )  // 当前动画对象指针(帧同步比对基准)
            return 0;
          v2 = 0;
          v43 = 12;
          while ( v2 + 3 < *((uint32_t *)dword_8F852C + 2) && *(uint32_t *)(v43 + *((uint32_t *)dword_8F852C + 3)) != 0 )  // dword_8F852C = UI 管理器全局
          {
            v43 += 4;
            ++v2;
            if ( v43 >= 36 )
              return 0;
          }
          if ( v2 == -1 )
            return 0;
        }
        v44 = fld_e1[629];  // fld_e1=this+4 宿主对象
        if ( v44 >= *((uint32_t *)dword_8F852C + 2) )  // dword_8F852C = UI 管理器全局
          return 0;
        v45 = *((uint32_t *)dword_8F852C + 3);  // dword_8F852C = UI 管理器全局
        pObj7 = *(uint32_t *)(v45 + 4 * v44);
        if ( pObj7 == 0
          || *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj7 + 16))(*(uint32_t *)(v45 + 4 * v44)) + 4) != fld_e12[628] )  // 调用虚函数（虚表槽 +16）
        {
          return 0;
        }
        v47 = v2 + 3;
        if ( v2 + 3 >= *((uint32_t *)dword_8F852C + 2)  // dword_8F852C = UI 管理器全局
          || (v48 = *((uint32_t *)dword_8F852C + 3), (v49 = *(uint32_t *)(v48 + 4 * v47)) == 0)  // dword_8F852C = UI 管理器全局
          || (v70 = sub_547350(*(uint32_t *)(v48 + 4 * v47))) == sub_547350(pObj7) )  // 调 物品栏条目（25 行）
        {
          sub_486530(v47, fld_e12[629], 1);  // 调 请求 op 19：两槽交换
          return 1;  // 返回 1(成功)
        }
        v50 = sub_547350(v49);  // 调 物品栏条目（25 行）
        v51 = sub_547300(v50);  // 调 物品栏数据（33 行）
        v52 = sub_547300(v50 + 1);  // 调 物品栏数据（33 行）
        for ( j = v51; j < v52; ++j )
        {
          if ( j >= *((uint32_t *)dword_8F852C + 2) )  // dword_8F852C = UI 管理器全局
            break;
          if ( *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * j) == 0 )  // dword_8F852C = UI 管理器全局
            break;
        }
        if ( j == v52 )
          return 0;
        sub_486690(j, v47, fld_e12[629]);  // 调 连续两次 op 19 交换（三槽轮换）
        return 1;  // 返回 1(成功)
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        if ( v2 != -1 )
        {
          pObj6 = sub_44A980(fld_e1[629]);  // 调 带界索引 getter
          if ( pObj6 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj6 + 16))(pObj6) + 4) == fld_e12[628] )  // 调用虚函数（虚表槽 +16）
          {
            v55 = fld_e12[629];
            v56 = v2 + 3;
            if ( v56 != v55 )
            {
              sub_486530(v56, v55, 1);  // 调 请求 op 19：两槽交换
              return 1;  // 返回 1(成功)
            }
          }
        }
        return 0;
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        pObj3 = sub_44A980(fld_e1[629]);  // 调 带界索引 getter
        if ( pObj3 == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 16))(pObj3) + 4) != fld_e12[628] )  // 调用虚函数（虚表槽 +16）
          return 0;
        if ( v2 == -1 )
        {
          if ( (uint8_t)sub_43B500(*(this + 2)) == 0 )  // 调 焦点窗口判定（34 号）
            return 0;
          v2 = 0;
          while ( 1 )  // 无限循环
          {
            pObj5 = sub_44A980(v2 + 3);  // 调 带界索引 getter
            pObj2 = pObj5;
            if ( pObj5 == 0 )
              break;
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 20))(pObj5, 1) != 0 )  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
            {
              v71 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 16))(pObj3) + 4);  // 调用虚函数（虚表槽 +16）
              if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 4) == v71 )  // 调用虚函数（虚表槽 +16）
                break;
            }
            if ( ++v2 >= 6 )
              return 0;
          }
          if ( v2 == -1 )
            return 0;
        }
        v60 = v2 + 3;
        if ( (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 44))(pObj3) <= 1 )  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
        {
          v61 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 44))(pObj3);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
          sub_484AF0(fld_e12[629], v61, 0, v60);  // 调 技能施放请求（包 op 19 变体：槽/参数/来源字段序不同）
          return 1;  // 返回 1(成功)
        }
        sub_540DE0(1, 4, fld_e12[629], 0, v60, 0, 0);  // 调 摊位列表构建（203 行：540A10/62EE70/540A50/541A30/542AB0 + 484FA0/48FCA…
        return 1;  // 返回 1(成功)
      default:
        break;
    }
    if ( v30 != 8 )
      return 0;
    if ( v2 == -1 )
    {
      if ( (uint8_t)sub_43B500(*(this + 2)) == 0 )  // 调 焦点窗口判定（34 号）
        return 0;
      v2 = 0;
      while ( sub_44A980(v2 + 3) != 0 )  // 调 带界索引 getter
      {
        if ( ++v2 >= 6 )
          return 0;
      }
      if ( v2 == -1 )
        return 0;
    }
    pObj8 = sub_44A980(fld_e12[629]);  // 调 带界索引 getter
    pObj9 = pObj8;
    if ( pObj8 == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 16))(pObj8) + 4) != fld_e12[628] )  // 调用虚函数（虚表槽 +16）
      return 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj9 + 20))(pObj9, 1) != 0  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
      && (unsigned int)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 44))(pObj9) > 1 )  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
    {
      sub_540DE0(1, 2, fld_e12[629], 0, v2 + 3, 0, 0);  // 调 摊位列表构建（203 行：540A10/62EE70/540A50/541A30/542AB0 + 484FA0/48FCA…
      return 1;  // 返回 1(成功)
    }
    v64 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 36))(pObj9);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
    if ( (uint8_t)sub_547170(v64, 1) == 0 )  // 调 物品格子查询（484FA0 + 422E70/44E8D0）
    {
      dword_8F852C2 = dword_8F852C;  // dword_8F852C = UI 管理器全局
      v65 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 44))(pObj9);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
      sub_4866D0(fld_e12[629], v65, dword_8F852C2, v2 + 3);  // 调 请求 op 19 带来源对象（等级 + 来源容器）
      return 1;  // 返回 1(成功)
    }
    return 1;  // 返回 1(成功)
  }
  if ( v2 == -1 )
  {
    fld_e23 = *(this + 2);  // this+8 = 技能槽记录首字
    if ( *(uint8_t *)(fld_e23 + 17) == 0 || dword_79BE34 != *(uint32_t *)(fld_e23 + 12) )  // 当前动画对象指针(帧同步比对基准)
      return 0;
    v2 = 0;
    v32 = 12;
    while ( v2 + 3 < *((uint32_t *)dword_8F852C + 2) && *(uint32_t *)(v32 + *((uint32_t *)dword_8F852C + 3)) != 0 )  // dword_8F852C = UI 管理器全局
    {
      v32 += 4;
      ++v2;
      if ( v32 >= 36 )
        return 0;
    }
    if ( v2 == -1 )
      return 0;
  }
  pObj4 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, fld_e1[629]);  // 调用虚函数（虚表槽 +792）
  pObj = pObj4;
  if ( pObj4 == 0 || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 16))(pObj4) + 4) != fld_e12[628] )  // 调用虚函数（虚表槽 +16）
    return 0;
  v35 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj);  // 调用虚函数（虚表槽 +172）【推断: 朝目标方向按比例取点: p = this + (target −…】
  v36 = sub_486820(v2 + 3, *v35, 1);  // 调 施放拒绝提示（ALERT_1 音效 + sub_485510）
  v37 = *((uint32_t *)dword_8F852C + 2);  // dword_8F852C = UI 管理器全局
  if ( v2 + 3 >= v37 )
    v38 = 0;
  else
    v38 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * (v2 + 3));  // dword_8F852C = UI 管理器全局
  if ( v36 != 0 )
    return 1;  // 返回 1(成功)
  if ( v38 == 0 )
    return 0;
  v39 = 0;
  v40 = 12;
  while ( v39 + 3 < v37 && *(uint32_t *)(v40 + *((uint32_t *)dword_8F852C + 3)) != 0 )  // dword_8F852C = UI 管理器全局
  {
    v40 += 4;
    ++v39;
    if ( v40 >= 36 )
      return 0;
  }
  v41 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj);  // 调用虚函数（虚表槽 +172）【推断: 朝目标方向按比例取点: p = this + (target −…】
  sub_486820(v39 + 3, *v41, 1);  // 调 施放拒绝提示（ALERT_1 音效 + sub_485510）
  return 1;  // 返回 1(成功)
}


// ============================================================
// 【分区 4】界面窗口族（0x463C90-0x469170）
// 图标格/窗口绘制与命中测试（含 ~890 行巨函数 0x464C60）【推断】。
// ============================================================
// ------------------------------------------------------------
// 0x463C90 sub_463C90 —— 界面窗口族逐帧刷新总驱动
// byte_8F8598 使能时遍历 byte_77FD08..dword_77FD48 的槽 id 逐个 sub_4BF250 查存活，写 +176（当前）与 +184（上线沿）。
// dword_79C0B4 vt+16 参数 4 命中则翻转 +996，参数 22（域 6）时 sub_461490 翻页。
// 再串 sub_461690/461580/463340 按钮、sub_545610 输入框、sub_56DDA0 社区面板与 sub_44ABE0(16) 选中索引。
// ------------------------------------------------------------
char /*usercall*/ sub_463C90@<al>(int pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>)  // 实现：界面窗口族逐帧刷新总驱动
{
  int v3; // eax
  int v5; // esi
  char *byte_77FD082; // edi
  char v7; // al
  int v8; // eax
  int v9; // edi
  int v10; // esi
  int v11; // esi
  int v12; // esi
  uint32_t v16[4]; // [esp+4h] [ebp-20h]
  uint32_t v17[3]; // [esp+14h] [ebp-10h]
  int v18; // [esp+20h] [ebp-4h]

  LOBYTE(v3) = byte_8F8598;  // 调 取 16 位值低 8 位
  if ( byte_8F8598 != 0 )
  {
    v18 = *((uint32_t *)dword_8F8528 + 1);  // dword_8F8528 = 主管理器
    v5 = 0;
    byte_77FD082 = byte_77FD08;
    do
    {
      if ( byte_77FD082 != (char *)&unk_77FD18 )
      {
        v7 = sub_4BF250(dword_8F8558, byte_77FD082);  // 调 槽查询（+64 表）
        *(uint8_t *)(v5 + pArg1 + 184) = *(uint8_t *)(v5 + pArg1 + 176) == 0 && v7 != 0;
        *(uint8_t *)(v5 + pArg1 + 176) = v7;
      }
      byte_77FD082 += 8;
      ++v5;
    }
    while ( (int)byte_77FD082 < (int)dword_77FD48 );
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 4, nArg2, nArg3) != 0 )  // 调用虚函数（虚表槽 +16）
      *(uint8_t *)(pArg1 + 996) = *(uint8_t *)(pArg1 + 996) == 0;  // pArg1+996〔bCfgC996(推断)〕
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 6  // dword_8F7A24 = 当前场景状态对象
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 22) != 0 )  // 调用虚函数（虚表槽 +16）
    {
      sub_461490(*((uint32_t *)dword_8F8528 + 4));  // 调 618/446 双向切换（页签翻页）
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 18) != 0 )  // 调用虚函数（虚表槽 +16）
      sub_461690(pArg1);  // 调 按钮点击（音效加三连图切换）
    v8 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 = 当前场景状态对象
    if ( (v8 == 6 || v8 == 3)  // 若 v8 == 6 与/或 v8 == 3
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 31) != 0 )  // 调用虚函数（虚表槽 +16）
    {
      sub_461580(v18);  // 调 界面子控件批量显隐
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 68) != 0 )  // 调用虚函数（虚表槽 +16）
      sub_463340(pArg1);  // 调 池 67 对象回收与借出切换
    LOBYTE(v3) = dword_8F7A24;  // 调 取 16 位值低 8 位
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )  // dword_8F7A24 = 当前场景状态对象
    {
      v16[0] = 70;
      v16[1] = 29;
      v16[2] = 104;
      v16[3] = 105;
      v17[0] = 66;
      v17[1] = 27;
      v17[2] = 106;
      v9 = 0;
      while ( 1 )  // 无限循环
      {
        v10 = v16[v9];
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, v10) != 0  // 调用虚函数（虚表槽 +16）
          && v10 != 70
          && v10 != 29 )
        {
          break;
        }
        if ( ++v9 >= 4 )
          goto LABEL_31;
      }
      sub_545610(v9);  // 调 输入框刷新（545510/545590 + 422E70/44E8D0，69 行）
LABEL_31:
      v11 = 0;
      while ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, v17[v11]) == 0 )  // 调用虚函数（虚表槽 +16）
      {
        if ( ++v11 >= 3 )
          goto LABEL_42;
      }
      sub_545610(4);  // 调 输入框刷新（545510/545590 + 422E70/44E8D0，69 行）
      if ( dword_9B88C0 != 0 )
      {
        v12 = v17[v11];
        switch ( v12 )  // 按 v12 分派
        {
          case 27:  // case 27 = ENUM_CMDPACKET_SET_ITEMTRADE_STATE
            sub_56DDA0((uint32_t *)dword_9B88C0, 1);  // 调 社区面板（429830 + 478EA0/478F40 好友/公会数据）
            break;
          case 66:  // case 66 = ENUM_CMDPACKET_DEBUG_COMMAND
            sub_56DDA0((uint32_t *)dword_9B88C0, 0);  // 调 社区面板（429830 + 478EA0/478F40 好友/公会数据）
            break;
          case 106:  // case 106 = ENUM_CMDPACKET_GATHERING_PARTY_STATUS
            sub_56DDA0((uint32_t *)dword_9B88C0, 2);  // 调 社区面板（429830 + 478EA0/478F40 好友/公会数据）
            break;
          default:
            break;
        }
      }
LABEL_42:
      LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 77);  // 调用虚函数（虚表槽 +16）
      if ( (uint8_t)v3 != 0 )
      {
        LOBYTE(v3) = dword_8F7C08;  // 调 取 16 位值低 8 位
        if ( dword_8F7C08 != 0 )  // dword_8F7C08 = 副玩家/观战者
        {
          v3 = *(uint32_t *)(dword_8F7C08 + 648);  // dword_8F7C08 = 副玩家/观战者
          if ( v3 != 0 && *(uint8_t *)(v3 + 284) == 0 )
            LOBYTE(v3) = sub_44ABE0(16);  // 调 选中索引 setter
        }
      }
    }
  }
  return v3;
}


// ------------------------------------------------------------
// 0x463ED0 sub_463ED0 —— 20 字节项取值（越界返 0）
// uArg2 超出项数返回 0，否则取该项首 dword。
// ------------------------------------------------------------
int /*thiscall*/ sub_463ED0(uint32_t *this, unsigned int uArg2)  // 函数: 20 字节项取值（越界返 0）
{
  int pVecCap_3; // eax

  pVecCap_3 = *(this + 2);  // this+8 = 技能槽记录首字
  if ( pVecCap_3 != 0 && uArg2 < (*(this + 3) - pVecCap_3) / 20 )  // this+12 = 技能槽记录次字
    return *(uint32_t *)(*(this + 2) + 20 * uArg2);  // this+8 = 技能槽记录首字
  else
    return 0;
}



// ------------------------------------------------------------
// 0x463F10 sub_463F10 —— 项内 clong 取值（缺省 -1）
// 有效项返回 sub_41A5E0(项+4 处 clong)；越界则临时构造空 clong（·sub_461750）取 0。
// 两路初值均为 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_463F10(uint32_t *this, unsigned int uArg2)  // 函数: 项内 clong 取值（缺省 -1）
{
  char v2; // bl
  int pVecCap_3; // eax
  uint32_t *fld_e22; // eax
  int v5; // esi
  uint32_t v7[3]; // [esp+Ah] [ebp-1Eh] BYREF
  int v8; // [esp+18h] [ebp-10h]
  int v9; // [esp+24h] [ebp-4h]

  v2 = 0;
  v8 = 0;
  pVecCap_3 = *(this + 2);  // this+8 = 技能槽记录首字
  if ( pVecCap_3 != 0 && uArg2 < (*(this + 3) - pVecCap_3) / 20 )  // this+12 = 技能槽记录次字
  {
    fld_e22 = (uint32_t *)(*(this + 2) + 20 * uArg2 + 4);  // this+8 = 技能槽记录首字
  }
  else
  {
    fld_e22 = sub_461750(v7, 0);  // 调 clong 构造（共享 vftbl_clong）
    v9 = 0;
    v2 = 1;
    v8 = 1;
  }
  v5 = sub_41A5E0((unsigned int)fld_e22);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  v9 = -1;
  if ( (v2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    sub_41A580(v7);  // 调 crypt4byte 析构（vftable 复位 + 实例计数递减）
  return v5;
}



// ------------------------------------------------------------
// 0x463FB0 sub_463FB0 —— 快捷栏逐帧刷新（悬停/点击/商店/任务）
// 槽存活扫描：dword_77FCA8..77FCD8 每 id 经 sub_4BF250 查存活写 dword_98B748，并在 dword_98B740 标出首个可用。
// 6+5 个按钮槽（this+192 起）命中悬停 id dword_79BE34 时播 MOUSE_OVER/CLICK_BUTTON1 并 sub_4872A0 按类型分发使用。
// 再走池 18 号借还、sub_560610 赛丽亚商店、sub_5540D0 任务 NPC 文本；尾两槽 +1280/+1296 命中分别转 sub_461690 与 sub_461490。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_463FB0(int this)  // 函数: 快捷栏逐帧刷新（悬停/点击/商店/任务）
{
  int v2; // edi
  int *dword_77FCA82; // ebx
  char v4; // al
  int v5; // ecx
  uint8_t *pThis_C0; // edi
  uint8_t *pThis_C6; // edi
  int *pThis_3C; // ebx
  int v9; // eax
  int fld_3C; // eax
  int fld_40; // eax
  int fld_44; // eax
  int fld_4; // eax
  int fld_48; // eax
  int fld_4C; // eax
  char *fld_42; // ecx
  int fld_50; // eax
  int fld_60; // eax
  char *fld_43; // ecx
  int v20; // edx
  uint32_t *v21; // ecx
  unsigned int v22; // ebx
  int v23; // edi
  int v24; // eax
  int v25; // eax
  int v26; // eax
  unsigned int v27; // edi
  int v28; // ebx
  int v29; // eax
  int *pThis_23C; // edi
  int k; // ebx
  int v32; // edi
  int *pThis_C; // edx
  int v34; // eax
  int v35; // edi
  int v36; // eax
  int fld_45; // eax
  int v38; // edi
  int *pThis_24; // edx
  int v40; // eax
  int v41; // eax
  int fld_46; // eax
  int v43; // ecx
  int pThis_CC; // edx
  int v45; // ecx
  int v46; // eax
  int fld_4D0; // ecx
  int fld_642; // edx
  int fld_64; // eax
  int fld_500; // eax
  uint8_t *result; // eax
  int v52; // [esp+Ch] [ebp-10h]
  int i; // [esp+10h] [ebp-Ch]
  int j; // [esp+10h] [ebp-Ch]
  int v55; // [esp+10h] [ebp-Ch]
  int pThis_54; // [esp+14h] [ebp-8h]
  char v57; // [esp+1Bh] [ebp-1h]

  v52 = *((uint32_t *)dword_8F8528 + 1);  // dword_8F8528 = 主管理器
  v57 = 0;
  v2 = 0;
  dword_77FCA82 = dword_77FCA8;
  do
  {
    v4 = sub_4BF250(dword_77FCA82);  // 调 槽查询（+64 表）
    if ( *((uint8_t *)&dword_98B748 + v2) != 0 || v4 == 0 || v57 != 0 )  // 若 v4 == 0 与/或 v57 != 0
    {
      *((uint8_t *)&dword_98B740 + v2) = 0;  // dword_98B740＝标出首个可用。
    }
    else
    {
      *((uint8_t *)&dword_98B740 + v2) = 1;  // dword_98B740＝标出首个可用。
      v57 = 1;
    }
    *((uint8_t *)&dword_98B748 + v2) = v4;
    dword_77FCA82 += 2;
    ++v2;
  }
  while ( (int)dword_77FCA82 < (int)&dword_77FCD8 );
  v5 = -189 - this;
  pThis_C0 = (uint8_t *)(this + 192);  // this+192〔nDlgId(推断)〕
  for ( i = 6; i != 0; --i )  // 循环：i 从 6 递减到 0
  {
    if ( pThis_C0[v5 + (uint32_t)&dword_98B740 - 3] != 0 || *pThis_C0 != 0 )  // pThis_C0=this+192 nDlgId
    {
      sub_4872A0(&pThis_C0[v5]);  // 调 槽对象使用分发（按虚表 +20 类型分流）
      v5 = -189 - this;
      *pThis_C0 = 0;  // pThis_C0=this+192 nDlgId
    }
    ++pThis_C0;  // pThis_C0=this+192 nDlgId
  }
  if ( v52 != 0 )
    goto LABEL_117;
  pThis_C6 = (uint8_t *)(this + 198);  // this+198〔field_00C6〕
  pThis_3C = (int *)(this + 60);  // this+240 = 基类时刻同步参数 B
  for ( j = 5; j != 0; --j )  // 循环：j 从 5 递减到 0
  {
    v9 = *pThis_3C;  // pThis_3C=this+240 动画同步参数 B
    if ( *(uint8_t *)(*pThis_3C + 17) != 0  // this+17 激活/可命中标志
      && (dword_79BE3C == *(uint32_t *)(v9 + 12)  // 动画对象指针(帧同步比对基准 C)
       || dword_79BE34 == *(uint32_t *)(v9 + 12)  // 当前动画对象指针(帧同步比对基准)
       || dword_79BE38 == *(uint32_t *)(v9 + 12)) )  // 动画对象指针(帧同步比对基准 B)
    {
      if ( *pThis_C6 == 0 )  // pThis_C6=this+198 field_00C6
      {
        *pThis_C6 = 1;  // pThis_C6=this+198 field_00C6
        sub_432EA0("MOUSE_OVER", -1, 0, 0);  // 调 音效播放包装（非空判定）
      }
    }
    else
    {
      *pThis_C6 = 0;  // pThis_C6=this+198 field_00C6
    }
    ++pThis_3C;  // pThis_3C=this+240 动画同步参数 B
    ++pThis_C6;  // pThis_C6=this+198 field_00C6
  }
  fld_3C = *(uint32_t *)(this + 60);  // this+240 = 基类时刻同步参数 B
  if ( *(uint8_t *)(fld_3C + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_3C + 12) || *(uint8_t *)(this + 184) != 0 )  // this+184〔bSingleTarget(推断)〕
  {
    sub_44BBA0(5, 1);  // 调 窗口显示切换（WINDOW_SHOW 音效）
    sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  fld_40 = *(uint32_t *)(this + 64);  // this+256 = 基类四元组字节槽 3
  if ( *(uint8_t *)(fld_40 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_40 + 12) || *(uint8_t *)(this + 185) != 0 )  // 当前动画对象指针(帧同步比对基准)
  {
    sub_44BBA0(4, 1);  // 调 窗口显示切换（WINDOW_SHOW 音效）
    sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  fld_44 = *(uint32_t *)(this + 68);  // this+68〔nCharCount(推断)〕
  if ( *(uint8_t *)(fld_44 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_44 + 12) || *(uint8_t *)(this + 186) != 0 )  // 当前动画对象指针(帧同步比对基准)
  {
    fld_4 = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
    *(uint8_t *)(this + 1216) = 1;
    sub_560610(*(uint32_t *)(*(uint32_t *)(fld_4 + 2444) + 12) != 1);  // 调 SERA_SHOP 赛丽亚商店事件（698F90/55FDB0/5604F0/432EA0/44E8D0/65FA00/46…
    sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  fld_48 = *(uint32_t *)(this + 72);  // this+72〔nSnapshot72(推断)〕等 2 字段
  if ( *(uint8_t *)(fld_48 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_48 + 12) || *(uint8_t *)(this + 187) != 0 )  // 当前动画对象指针(帧同步比对基准)
  {
    sub_44BBA0(0, 1);  // 调 窗口显示切换（WINDOW_SHOW 音效）
    sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  fld_4C = *(uint32_t *)(this + 76);  // this+76〔pBtnActionE〕
  if ( *(uint8_t *)(fld_4C + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_4C + 12) || *(uint8_t *)(this + 188) != 0 )  // this+188〔nStatusIdx(推断)〕
  {
    fld_42 = *(char **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
    if ( dword_9B8880 != 0 )
      sub_44E850(fld_42, 43);  // 调 按池号批量回收活动对象
    else
      sub_44E8D0(fld_42, (void *)0x2B, 0, 0);  // 调 对象池借出（按池号取可用对象）
    sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  fld_50 = *(uint32_t *)(this + 80);  // this+80〔nAuraStage(推断)〕
  if ( *(uint8_t *)(fld_50 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_50 + 12) || *(uint8_t *)(this + 189) != 0 )  // this+189〔bFlag189〕
  {
    sub_5540D0(nullptr, -1);  // 调 任务 NPC 文本装配（69C730/69A5F0/56CFE0 + 69C340/69C360/69C400/69C500…
    sub_44BBA0(7, 1);  // 调 窗口显示切换（WINDOW_SHOW 音效）
    sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  if ( *(uint8_t *)(this + 190) != 0 )  // this+190〔bFlag190〕
  {
    sub_44BBA0(1, 1);  // 调 窗口显示切换（WINDOW_SHOW 音效）
    sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  fld_60 = *(uint32_t *)(this + 96);  // this+384 = 动画件名 SSO 容量判据
  if ( *(uint8_t *)(fld_60 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_60 + 12) && *(uint32_t *)(dword_8F7A24 + 12) == 3 )  // dword_8F7A24 = 当前场景状态对象
  {
    fld_43 = *(char **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
    v20 = *((uint32_t *)fld_43 + 302);  // fld_43=this+16 nChannelTypeSel
    if ( v20 != 0 && (*((uint32_t *)fld_43 + 303) - v20) >> 2 != 0 )  // fld_43=this+16 nChannelTypeSel
      sub_44E850(fld_43, 67);  // 调 按池号批量回收活动对象
    else
      sub_44E8D0(fld_43, (void *)0x43, 0, 0);  // 调 对象池借出（按池号取可用对象）
    sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  v21 = (uint32_t *)dword_8F8540;  // dword_8F8540 = 技能/条目全局链
  v22 = 0;
  v23 = 0;
  v55 = 0;
  pThis_54 = this + 84;  // this+84 插值起点 X
  do
  {
    if ( *(uint8_t *)(*(uint32_t *)pThis_54 + 17) != 0 && dword_79BE34 == *(uint32_t *)(*(uint32_t *)pThis_54 + 12) )  // 当前动画对象指针(帧同步比对基准)
    {
      sub_5540D0(nullptr, -1);  // 调 任务 NPC 文本装配（69C730/69A5F0/56CFE0 + 69C340/69C360/69C400/69C500…
      sub_44BBA0(7, 0);  // 调 窗口显示切换（WINDOW_SHOW 音效）
      v21 = (uint32_t *)dword_8F8540;  // dword_8F8540 = 技能/条目全局链
      v24 = *(uint32_t *)(dword_8F8540 + 8);  // dword_8F8540 = 技能/条目全局链
      if ( v24 != 0
        && v22 < (*(uint32_t *)(dword_8F8540 + 12) - v24) / 20  // dword_8F8540 = 技能/条目全局链
        && *(uint32_t *)(*(uint32_t *)(dword_8F8540 + 8) + v23) != 0 )  // dword_8F8540 = 技能/条目全局链
      {
        if ( sub_463F10((uint32_t *)dword_8F8540, v22) != -1 )  // 调 项内 clong 取值（缺省 -1）
        {
          v25 = *(uint32_t *)(dword_8F8540 + 8);  // dword_8F8540 = 技能/条目全局链
          if ( v25 != 0 && v22 < (*(uint32_t *)(dword_8F8540 + 12) - v25) / 20 )  // dword_8F8540 = 技能/条目全局链
            v26 = *(uint32_t *)(v55 + *(uint32_t *)(dword_8F8540 + 8));  // dword_8F8540 = 技能/条目全局链
          else
            v26 = 0;
          sub_552BD0(v26);  // 调 任务文本装配（246 行：44AB50/432EE0/44CA70/429830 + 4F33A0/4F2CE0/4F2D6…
          sub_44BBA0(8, 0);  // 调 窗口显示切换（WINDOW_SHOW 音效）
          v23 = v55;
        }
        v21 = (uint32_t *)dword_8F8540;  // dword_8F8540 = 技能/条目全局链
      }
    }
    v23 += 20;
    ++v22;
    pThis_54 += 4;  // pThis_54=this+84 插值起点 X
    v55 = v23;
  }
  while ( v23 < 60 );
  if ( *(uint32_t *)(this + 568) != -1 )  // this+568〔nAlarmVal〕
    goto LABEL_85;
  v27 = 0;
  v28 = 0;
  while ( 1 )  // 无限循环
  {
    v29 = v21[2];
    if ( v29 != 0 && v27 < (v21[3] - v29) / 20 && *(uint32_t *)(v21[2] + v28) != 0 )
    {
      if ( sub_463F10(v21, v27) == -1 )  // 调 项内 clong 取值（缺省 -1）
        break;
      v21 = (uint32_t *)dword_8F8540;  // dword_8F8540 = 技能/条目全局链
    }
    v28 += 20;
    ++v27;
    if ( v28 >= 60 )
      goto LABEL_85;
  }
  *(uint32_t *)(this + 568) = v27;  // this+568〔nAlarmVal〕
  pThis_23C = (int *)(this + 572);  // this+572 最后一次受击
  for ( k = 3; k != 0; --k )  // 循环：k 从 3 递减到 0
    sub_4926A0(*pThis_23C++);  // 调 帧游标复位（+44 帧数组；递归子链 +204）
LABEL_85:
  v32 = 0;
  pThis_C = (int *)(this + 12);  // this+12〔nSkillRec12(推断)〕等 2 字段
  while ( 1 )  // 无限循环
  {
    v34 = *pThis_C;  // pThis_C=this+12 nSkillRec12
    if ( *(uint8_t *)(*pThis_C + 17) != 0  // this+17 激活/可命中标志
      && (dword_79BE3C == *(uint32_t *)(v34 + 12)  // 动画对象指针(帧同步比对基准 C)
       || dword_79BE34 == *(uint32_t *)(v34 + 12)  // 当前动画对象指针(帧同步比对基准)
       || dword_79BE38 == *(uint32_t *)(v34 + 12)) )  // 动画对象指针(帧同步比对基准 B)
    {
      break;
    }
    ++v32;
    ++pThis_C;  // pThis_C=this+12 nSkillRec12
    if ( v32 >= 6 )
      goto LABEL_94;
  }
  v35 = v32 + 3;
  if ( v35 >= *((uint32_t *)dword_8F852C + 2) || (v36 = *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v35)) == 0 )  // dword_8F852C = UI 管理器全局
  {
LABEL_94:
    if ( dword_9B88D0 != 0 && dword_795378 == 0 )  // 若 dword_9B88D0 != 0 与/或 dword_795378 == 0
      sub_44E850(*(uint32_t **)(this + 4), 26);  // 调 按池号批量回收活动对象
    goto LABEL_101;
  }
  if ( dword_9B88D0 != v36 || dword_795378 != 0 )  // 若 dword_9B88D0 != v36 与/或 dword_795378 != 0
  {
    fld_45 = sub_44E8D0(*(char **)(this + 4), (void *)0x1A, v36, 0);  // 调 对象池借出（按池号取可用对象）
    if ( fld_45 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)fld_45 + 48))(  // 调用虚函数（虚表槽 +48）
        fld_45,
        *(uint32_t *)(*(uint32_t *)(this + 4 * v35) + 20),  // this+4 宿主对象
        *(uint32_t *)(*(uint32_t *)(this + 4 * v35) + 24),  // this+4 宿主对象
        *(uint32_t *)(*(uint32_t *)(this + 4 * v35) + 28),  // this+4 宿主对象
        *(uint32_t *)(*(uint32_t *)(this + 4 * v35) + 32));  // this+4 宿主对象
  }
LABEL_101:
  v38 = 0;
  pThis_24 = (int *)(this + 36);  // this+144 = pFrameList144
  while ( 1 )  // 无限循环
  {
    v40 = *pThis_24;  // pThis_24=this+144 第 4 组·+1040 增量子倍率
    if ( *(uint8_t *)(*pThis_24 + 17) != 0  // this+17 激活/可命中标志
      && (dword_79BE3C == *(uint32_t *)(v40 + 12)  // 动画对象指针(帧同步比对基准 C)
       || dword_79BE34 == *(uint32_t *)(v40 + 12)  // 当前动画对象指针(帧同步比对基准)
       || dword_79BE38 == *(uint32_t *)(v40 + 12)) )  // 动画对象指针(帧同步比对基准 B)
    {
      break;
    }
    ++v38;
    ++pThis_24;  // pThis_24=this+144 第 4 组·+1040 增量子倍率
    if ( v38 >= 6 )
      goto LABEL_110;
  }
  if ( v38 >= *(uint32_t *)dword_8F853C || (v41 = *(uint32_t *)(*((uint32_t *)dword_8F853C + 1) + 4 * v38)) == 0 )  // 容器对象指针(容量比较)
  {
LABEL_110:
    if ( dword_9B88CC != 0 && dword_795374 == 0 )  // 若 dword_9B88CC != 0 与/或 dword_795374 == 0
      sub_44E850(*(uint32_t **)(this + 4), 18);  // 调 按池号批量回收活动对象
    goto LABEL_117;
  }
  if ( dword_9B88CC != v41 || dword_795374 != 0 )  // 若 dword_9B88CC != v41 与/或 dword_795374 != 0
  {
    fld_46 = sub_44E8D0(*(char **)(this + 4), (void *)0x12, v41, 0);  // 调 对象池借出（按池号取可用对象）
    if ( fld_46 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)fld_46 + 48))(  // 调用虚函数（虚表槽 +48）
        fld_46,
        *(uint32_t *)(*(uint32_t *)(this + 4 * v38 + 36) + 20),  // this+4 宿主对象
        *(uint32_t *)(*(uint32_t *)(this + 4 * v38 + 36) + 24),  // this+4 宿主对象
        *(uint32_t *)(*(uint32_t *)(this + 4 * v38 + 36) + 28),  // this+4 宿主对象
        *(uint32_t *)(*(uint32_t *)(this + 4 * v38 + 36) + 32));  // this+4 宿主对象
  }
LABEL_117:
  v43 = 0;
  pThis_CC = this + 204;  // this+204 子动画链指针
  while ( *(uint8_t *)(*(uint32_t *)pThis_CC + 17) == 0 || dword_79BE34 != *(uint32_t *)(*(uint32_t *)pThis_CC + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    ++v43;
    pThis_CC += 4;  // pThis_CC=this+204 子动画链指针
    if ( v43 >= 4 )
      goto LABEL_124;
  }
  v45 = *(uint32_t *)(dword_8F850C + 4 * v43 + 16);  // 房间/席位表
  if ( v45 != 0 )
  {
    v46 = sub_42B340(v45);  // 调 虚拟角色惰性创建（0x294 字节）
    sub_526BF0(v46, 1);  // 调 与 ·sub_567F40 联动
  }
LABEL_124:
  if ( *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 28) + 256) == 0 )  // this+4〔宿主对象〕等 2 字段
    sub_463C90(this);  // 调 界面窗口族逐帧刷新总驱动
  *(uint8_t *)(*(uint32_t *)(this + 96) + 16) = *(uint32_t *)(dword_8F7A24 + 12) == 3 && v52 != 2;  // this+384 = 动画件名 SSO 容量判据
  fld_4D0 = *(uint32_t *)(this + 1232);  // this+1232〔pNameTagCtrl〕
  if ( *(uint8_t *)(fld_4D0 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_4D0 + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    if ( *(uint32_t *)(this + 1236) != 0 )  // this+1236〔field_04D4〕
    {
      fld_64 = *(uint32_t *)(this + 100);  // this+100〔bEnchantDone(推断)〕
      *(uint32_t *)(this + 1236) = 0;  // this+1236〔field_04D4〕
      sub_69C980(fld_4D0, fld_64, 189, 182, 182, -1, 0, 0);  // 调 换 191/190/190 号图
    }
    else
    {
      fld_642 = *(uint32_t *)(this + 100);  // this+100〔bEnchantDone(推断)〕
      *(uint32_t *)(this + 1236) = 1;  // this+1236〔field_04D4〕
      sub_69C980(fld_4D0, fld_642, 191, 190, 190, -1, 0, 0);  // 调 换 191/190/190 号图
    }
  }
  fld_500 = *(uint32_t *)(this + 1280);
  if ( *(uint8_t *)(fld_500 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_500 + 12) )  // 当前动画对象指针(帧同步比对基准)
    sub_461690(this);  // 调 按钮点击（音效加三连图切换）
  result = *(uint8_t **)(this + 1296);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 当前动画对象指针(帧同步比对基准)
  {
    sub_461490(this);  // 调 618/446 双向切换（页签翻页）
    return sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}


// ------------------------------------------------------------
// 0x464740 sub_464740 —— 九宫格面板框绘制
// nArg5 为 1 时图号基址 +0x1E（63..71 变 93..101）；按 (nArg1,nArg2) 左上与 (nArg3,nArg4) 宽高拼九宫。
// 四角 63/69、上下边图按 x 步进 12 平铺、左右边 66/68；pszArg6 为 0 时只留角。
// 首次调用缓存 dword_98B8C0（取自 dword_99FCC8 上下文 +60）。
// ------------------------------------------------------------
char /*cdecl*/ sub_464740(int nArg1, int nArg2, int nArg3, int nArg4, int nArg5, char pszArg6)  // 函数: 九宫格面板框绘制
{
  int v6; // edi
  int pObj2; // eax
  int nArg22; // ebx
  int v9; // esi
  int v10; // edi
  int pObj7; // eax
  int pObj3; // eax
  int v13; // ebx
  int pObj6; // eax
  int v15; // esi
  int v16; // edi
  int pObj; // eax
  int pObj5; // eax
  int pObj8; // eax
  int pObj9; // eax
  int v21; // esi
  int v22; // edi
  int pObj4; // eax
  int v25; // [esp+0h] [ebp-4h]
  int v26; // [esp+10h] [ebp+Ch]
  int v27; // [esp+1Ch] [ebp+18h]

  if ( dword_98B8C0 == 0 )
    dword_98B8C0 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60);  // nengine::CNSlider 全局实例
  v6 = nArg5 != 1 ? 0 : 0x1E;
  v27 = v6;
  if ( pszArg6 != 0 )
  {
    pObj2 = sub_418DD0(v6 + 63);  // 调 资源句柄 (101)
    nArg22 = nArg2;
    if ( pObj2 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, nArg1, nArg2, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  }
  else
  {
    nArg22 = nArg2;
  }
  v9 = nArg1 + 5;
  v25 = nArg1 + 5;
  if ( pszArg6 != 0 )
  {
    v10 = nArg1 + nArg3 + 2;
    if ( v9 <= v10 )
    {
      do
      {
        pObj7 = sub_418DD0(v27 + 64);  // 调 资源句柄 (101)
        if ( pObj7 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v9, nArg2, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        v9 += 12;
      }
      while ( v9 <= v10 );
      nArg22 = nArg2;
    }
    pObj3 = sub_418DD0(v27 + 65);  // 调 资源句柄 (101)
    if ( pObj3 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v9, nArg22, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v6 = v27;
  }
  v13 = nArg22 + 5;
  if ( nArg4 > 0 )
  {
    v26 = nArg1 + nArg3 + 2;
    do
    {
      if ( pszArg6 != 0 )
      {
        pObj6 = sub_418DD0(v6 + 66);  // 调 资源句柄 (101)
        if ( pObj6 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, nArg1, v13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      }
      v15 = nArg1 + 5;
      if ( v25 <= v26 )
      {
        v16 = v6 + 67;
        do
        {
          pObj = sub_418DD0(v16);  // 调 资源句柄 (101)
          if ( pObj != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v15, v13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          v15 += 12;
        }
        while ( v15 <= v26 );
        v6 = v27;
      }
      if ( pszArg6 != 0 )
      {
        pObj5 = sub_418DD0(v6 + 68);  // 调 资源句柄 (101)
        if ( pObj5 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v15, v13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      }
      v13 += 13;
      --nArg4;
    }
    while ( nArg4 != 0 );
  }
  LOBYTE(pObj8) = pszArg6;  // 调 取 16 位值低 8 位
  if ( pszArg6 != 0 )
  {
    pObj9 = sub_418DD0(v6 + 69);  // 调 资源句柄 (101)
    if ( pObj9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj9 + 152))(pObj9, nArg1, v13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v21 = nArg1 + 5;
    v22 = nArg1 + nArg3 + 2;
    if ( v25 <= v22 )
    {
      do
      {
        pObj4 = sub_418DD0(v27 + 70);  // 调 资源句柄 (101)
        if ( pObj4 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v21, v13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        v21 += 12;
      }
      while ( v21 <= v22 );
    }
    pObj8 = sub_418DD0(v27 + 71);  // 调 资源句柄 (101)
    if ( pObj8 != 0 )
      LOBYTE(pObj8) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, v21, v13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  }
  return pObj8;
}


// ------------------------------------------------------------
// 0x4649B0 sub_4649B0 —— 带框文本上屏（静态一次性初始化）
// 静态标志 dword_98B8FC 位 0 首次执行时初始化边框色与宽高（+6/+12/1600 等）并 atexit(sub_6BF670)。
// byte_98B8C4 变化时重建；sub_464740 画框、sub_6C0200 量文本宽。
// 末以 dword_79C0B0 vt+72/80/76 包夹上屏。
// ------------------------------------------------------------
int /*cdecl*/ sub_4649B0(int nArg1, int nArg2, int nArg3, int nArg4, int nArg5, const char *pArg6, int nArg7, int nArg8, int nArg9, char pszArg10)  // 函数: 带框文本上屏（静态一次性初始化）
{
  int v10; // edi
  int v11; // eax
  int v12; // edx
  int v13; // ebx
  int v14; // eax
  uint8_t *v15; // esi
  int v16; // eax
  int v17; // edx
  int nArg12; // ebx
  int nArg22; // esi
  int v20; // eax
  int nArg122; // ecx
  int nArg222; // ecx
  int v23; // eax
  int v24; // ecx
  uint8_t v26[204800]; // [esp+Ch] [ebp-32004h] BYREF
  int v27; // [esp+3200Ch] [ebp-4h]
  int v28; // [esp+32038h] [ebp+28h]
  int v29; // [esp+3203Ch] [ebp+2Ch]

  v10 = 0;
  if ( (dword_98B8FC & 1) == 0 )  // 若 dword_98B8FC 位 1 清零
  {
    dword_98B8FC |= 1u;
    byte_98B8C8 = 0;
    byte_98B8C9 = 0;
    byte_98B8CA = 0;
    byte_98B8CB = 0;
    dword_98B8D4 = 0;
    dword_98B8D8 = 6;
    dword_98B8DC = 12;
    dword_98B8E0 = 0;
    dword_98B8E4 = 1600;
    dword_98B8E8 = 0;
    dword_98B8EC = 0;
    dword_98B8F0 = 0;
    ho = nullptr;
    dword_98B8F8 = 0;
    atexit(sub_6BF670);  // 调 登记退出回调（表满返回非 0）
  }
  if ( byte_98B8C4 == 0 )
  {
    byte_98B8C8 = 0;
    byte_98B8C9 = 0;
    byte_98B8CA = 0;
    byte_98B8CB = 0;
    dword_98B8D4 = 0;
    dword_98B8D8 = 6;
    dword_98B8DC = 12;
    dword_98B8E0 = 0;
    dword_98B8E8 = 0;
    dword_98B8F0 = 0;
    ho = nullptr;
    dword_98B8F8 = dword_99FCCC;  // dword_99FCCC＝与字距
    dword_98B8EC = -1;
    byte_98B8C4 = 1;  // byte_98B8C4＝变化时重建
  }
  dword_98B8E4 = nArg9;
  v11 = sub_404B30(v26, pArg6, (int)&byte_98B8C8);  // 调 超长文本按 1024 字节切片（200 段缓冲清 0 + 逐段拷贝，段内按 CR / 多字节字符边界截断）
  v12 = *(uint32_t *)dword_99FCCC;  // dword_99FCCC＝与字距
  v13 = v11;
  v27 = v11;
  v14 = v11 * ((*(int (/*thiscall*/ **)(int))(v12 + 20))(dword_99FCCC) + 1) + 10;  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
  v28 = v14;
  if ( v13 > 0 )
  {
    v15 = v26;
    do
    {
      v16 = (*(int (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_99FCCC + 16))(dword_99FCCC, v15);  // 调用虚函数（虚表槽 +16）
      if ( v16 > v10 )
        v10 = v16;
      v15 += 1024;
      --v13;
    }
    while ( v13 != 0 );
    v14 = v28;
  }
  v17 = v10 + 10;
  if ( nArg5 == 9 || nArg5 == 6 || nArg5 == 3 )  // 若 nArg5 == 9 与/或 nArg5 == 6 与/或 nArg5 == 3
  {
    nArg12 = nArg1 - v17;
  }
  else if ( nArg5 == 8 || nArg5 == 5 || nArg5 == 2 )
  {
    nArg12 = v17 / -2 + nArg1;
    v14 = v28;
  }
  else
  {
    nArg12 = nArg1;
  }
  if ( nArg5 == 1 || nArg5 == 2 || nArg5 == 3 )  // 若 nArg5 == 1 与/或 nArg5 == 2 与/或 nArg5 == 3
  {
    nArg22 = nArg2 - v28;
  }
  else if ( nArg5 == 4 || nArg5 == 5 || nArg5 == 6 )
  {
    nArg22 = v14 / -2 + nArg2;
  }
  else
  {
    nArg22 = nArg2;
  }
  if ( pszArg10 != 0 )
  {
    v20 = 640 - (v10 + 10);
    nArg122 = nArg12;
    if ( nArg12 >= v20 )
      nArg122 = 640 - (v10 + 10);
    if ( nArg122 >= 0 )
    {
      if ( nArg12 >= v20 )
        nArg12 = 640 - (v10 + 10);
    }
    else
    {
      nArg12 = 0;
    }
    nArg222 = nArg22;
    if ( nArg22 >= 480 - v28 )
      nArg222 = 480 - v28;
    if ( nArg222 >= 0 )
    {
      if ( nArg22 >= 480 - v28 )
        nArg22 = 480 - v28;
    }
    else
    {
      nArg22 = 0;
    }
  }
  sub_464740(nArg12, nArg22, v10, v27, nArg7, 1);  // 调 九宫格面板框绘制
  dword_98B8D4 = nArg8;
  dword_98B8CC = nArg4;
  dword_98B8E4 = v10;
  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_98B8C8);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
  v29 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
  v23 = sub_6C0200(nArg3, pArg6);
  (*(void (/*cdecl*/ **)(int, int, int))(v29 + 80))(v24, nArg12 + v23, nArg22 + 6);  // 调用虚函数（虚表槽 +80）
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
}


// ------------------------------------------------------------
// 0x464C60 sub_464C60 —— HUD 悬停提示总绘（血量/蓝量/经验/点数）
// 顶栏区（x 不超过 0x320、y 不超过 0x18）且非某界面态时铺 700 号黑底长条。
// 血量框 (6..41,412..477) 显 HP:%d/%d，蓝量框 (599..640,412..477) 显 MP:%d/%d（串自证）。
// 经验区 (63..265,421..442) 与点数区 (290..350,410..425) 走 190/191/192/193 号文本，全部经 sub_4649B0 带框上屏。
// ------------------------------------------------------------
void /*thiscall*/ sub_464C60(uint32_t *this)  // 函数: HUD 悬停提示总绘（血量/蓝量/经验/点数）
{
  int pObj; // ebx
  uint32_t *pThis; // edi
  bool v3; // zf
  int v4; // eax
  char *v5; // eax
  int i; // esi
  int v7; // eax
  int v8; // ecx
  unsigned int v9; // esi
  uint32_t *j; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  char v17; // dl
  int dword_79BE3C2; // edi
  int dword_79BE342; // esi
  int dword_79BE382; // ecx
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  uint64_t v26; // st7
  int v27; // eax
  char *v28; // eax
  char *v29; // eax
  int v30; // esi
  char *v31; // eax
  int v32; // edi
  int v33; // eax
  int v34; // esi
  int v35; // esi
  char *v36; // eax
  char *v37; // eax
  char *v38; // eax
  char *v39; // eax
  int v40; // eax
  int v41; // esi
  int v42; // edi
  int v43; // ecx
  int v44; // eax
  int v45; // ebx
  int v46; // edx
  int v47; // ebx
  int v48; // eax
  int v49; // ecx
  int v50; // eax
  int v51; // ecx
  int v52; // eax
  int v53; // eax
  uint64_t v54; // rax
  double v55; // st7
  char *v56; // eax
  int v57; // eax
  char *v58; // eax
  int v59; // esi
  int v60; // eax
  int v61; // eax
  double v62; // st7
  double v63; // st7
  double v64; // st7
  char *v65; // eax
  int v66; // esi
  int v67; // eax
  int v68; // eax
  double v69; // st7
  char *v70; // eax
  uint32_t *v71; // ebx
  int v72; // eax
  char *v73; // eax
  char *v74; // eax
  char *v75; // eax
  char *v76; // eax
  int v77; // eax
  int v78; // esi
  char *v79; // eax
  int v80; // eax
  int v81; // esi
  char *v82; // eax
  int v83; // esi
  uint32_t *v84; // edx
  int v85; // eax
  int v86; // eax
  int v87; // esi
  char *v88; // eax
  uint32_t *v89; // eax
  int v90; // ecx
  char v91; // dl
  int v92; // ebx
  char *v93; // eax
  int v94; // ecx
  int v95; // ebx
  int v96; // eax
  int v97; // edx
  int v98; // eax
  int v99; // ecx
  int v100; // edi
  int v101; // eax
  int v102; // esi
  int v103; // eax
  int v104; // ecx
  int v105; // edi
  int v106; // eax
  int v107; // esi
  uint32_t *v108; // esi
  int v109; // eax
  int v110; // edi
  int v111; // esi
  int v112; // eax
  int v113; // edi
  int v114; // esi
  int v115; // edi
  int v116; // esi
  char *v117; // eax
  int v118; // esi
  int v119; // esi
  int v120; // [esp+Ch] [ebp-60h]
  int v121; // [esp+10h] [ebp-5Ch]
  double v122; // [esp+20h] [ebp-4Ch]
  char *v123; // [esp+20h] [ebp-4Ch]
  char *v124; // [esp+20h] [ebp-4Ch]
  char *v125; // [esp+20h] [ebp-4Ch]
  char *v126; // [esp+20h] [ebp-4Ch]
  int v127; // [esp+20h] [ebp-4Ch]
  int v128; // [esp+24h] [ebp-48h]
  double v129; // [esp+24h] [ebp-48h]
  double v130; // [esp+28h] [ebp-44h]
  int v131; // [esp+2Ch] [ebp-40h]
  double v132; // [esp+2Ch] [ebp-40h]
  double v133; // [esp+2Ch] [ebp-40h]
  int v134; // [esp+30h] [ebp-3Ch]
  int v135; // [esp+30h] [ebp-3Ch]
  int v136; // [esp+30h] [ebp-3Ch]
  int v137; // [esp+30h] [ebp-3Ch]
  int v138; // [esp+30h] [ebp-3Ch]
  int v139; // [esp+30h] [ebp-3Ch]
  int v140; // [esp+30h] [ebp-3Ch]
  int v141; // [esp+30h] [ebp-3Ch]
  int v142; // [esp+30h] [ebp-3Ch]
  int v143; // [esp+40h] [ebp-2Ch]
  int v144; // [esp+40h] [ebp-2Ch]
  float v145; // [esp+44h] [ebp-28h]
  int v146; // [esp+44h] [ebp-28h]
  int v147; // [esp+44h] [ebp-28h]
  float v148; // [esp+48h] [ebp-24h]
  float v149; // [esp+48h] [ebp-24h]
  float v150; // [esp+48h] [ebp-24h]
  float v151; // [esp+4Ch] [ebp-20h]
  int v152; // [esp+4Ch] [ebp-20h]
  float v153; // [esp+50h] [ebp-1Ch] BYREF
  float v154; // [esp+54h] [ebp-18h] BYREF
  float v155; // [esp+58h] [ebp-14h] BYREF
  float v156; // [esp+5Ch] [ebp-10h] BYREF
  LONG x; // [esp+60h] [ebp-Ch]
  uint32_t *pThis2; // [esp+64h] [ebp-8h]
  LONG y; // [esp+68h] [ebp-4h]

  pObj = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
  pThis = this;
  pThis2 = this;
  if ( dword_8F7C04 == 0 )  // dword_8F7C04 = 本地玩家对象
    return;
  v3 = *(uint8_t *)(dword_8F7A24 + 112) == 0;  // dword_8F7A24 = 当前场景状态对象
  x = pt.x;
  y = pt.y;
  if ( v3 && pt.x <= 0x320u && pt.y <= 0x18u )
  {
    sub_4649B0(  // 调 带框文本上屏（静态一次性初始化）
      700,
      0,
      -1,
      -16777216,
      9,
      "                                                                                                                  "
      "                                                                                    ",
      0,
      0,
      1600,
      0);
    pObj = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
  }
  v4 = pThis[24];
  if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE3C == *(uint32_t *)(v4 + 12) )  // 动画对象指针(帧同步比对基准 C)
  {
    v5 = sub_422E70(2012);  // 调 存 CStringManager::getStr 取本地化串
    sub_4649B0(605, 35, -1, -16777216, 9, v5, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
    pObj = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
  }
  for ( i = 0; i < 6; ++i )  // 循环：i 从 0 递增到 6
  {
    if ( i == 5 )
      v7 = pThis[20];
    else
      v7 = pThis[i + 15];
    if ( *(uint8_t *)(v7 + 17) != 0 )
    {
      if ( dword_79BE3C == *(uint32_t *)(v7 + 12)  // 动画对象指针(帧同步比对基准 C)
        || (pThis = pThis2, dword_79BE34 == *(uint32_t *)(v7 + 12))  // 当前动画对象指针(帧同步比对基准)
        || dword_79BE38 == *(uint32_t *)(v7 + 12) )  // 动画对象指针(帧同步比对基准 B)
      {
        sub_4649B0(i != 5 ? 320 : 422, 8 * (i == 5) + 416, -1, -16777216, 2, dword_98B75C[i], 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
        return;
      }
    }
  }
  v8 = *(uint32_t *)(dword_8F8540 + 8);  // dword_8F8540 = 技能/条目全局链
  v9 = 0;
  for ( j = pThis2 + 21; ; j = (uint32_t *)(LODWORD(v153) + 4) )  // 调 取 64 位值低 32 位
  {
    v153 = *(float *)&j;
    if ( v8 != 0 )
      v11 = (*(uint32_t *)(dword_8F8540 + 12) - v8) / 20;  // dword_8F8540 = 技能/条目全局链
    else
      v11 = 0;
    if ( (int)v9 >= v11 )
    {
      v16 = pThis2[2];
      v17 = *(uint8_t *)(v16 + 17);
      dword_79BE3C2 = dword_79BE3C;  // 动画对象指针(帧同步比对基准 C)
      if ( v17 != 0 && dword_79BE3C == *(uint32_t *)(v16 + 12) )  // 动画对象指针(帧同步比对基准 C)
      {
        dword_79BE342 = dword_79BE34;  // 当前动画对象指针(帧同步比对基准)
      }
      else
      {
        dword_79BE342 = dword_79BE34;  // 当前动画对象指针(帧同步比对基准)
        if ( v17 == 0 || dword_79BE34 != *(uint32_t *)(v16 + 12) )  // 当前动画对象指针(帧同步比对基准)
        {
          dword_79BE382 = dword_79BE38;  // 动画对象指针(帧同步比对基准 B)
          if ( v17 == 0 || dword_79BE38 != *(uint32_t *)(v16 + 12) )  // 动画对象指针(帧同步比对基准 B)
            goto LABEL_43;
          goto LABEL_54;
        }
      }
      dword_79BE382 = dword_79BE38;  // 动画对象指针(帧同步比对基准 B)
LABEL_54:
      if ( x >= 6 && x <= 41 && y >= 412 && y <= 477 )  // 若 x >= 6 与/或 x <= 41 与/或 y >= 412
      {
        v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 740))(pObj);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
        v24 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 736))(dword_8F7C04, v23);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
        sprintf(&byte_98B900, "HP:%d/%d", v24, v135);  // 调 格式化到缓冲
        sub_4649B0(0, 402, -1, -16777216, 1, &byte_98B900, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
        return;
      }
LABEL_43:
      if ( *(uint8_t *)(v16 + 17) != 0
        && (dword_79BE3C == *(uint32_t *)(v16 + 12) || dword_79BE342 == *(uint32_t *)(v16 + 12) || dword_79BE382 == *(uint32_t *)(v16 + 12))  // 动画对象指针(帧同步比对基准 C)
        && x >= 599
        && x <= 640
        && y >= 412
        && y <= 477 )
      {
        v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 756))(pObj);  // 调用虚函数（虚表槽 +756）【推断: [RTTI: IRDActiveObject__vmt2F4 ·…】
        v22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 752))(dword_8F7C04, v21);  // 调用虚函数（虚表槽 +752）
        sprintf(&byte_98B900, "MP:%d/%d", v22, v134);  // 调 格式化到缓冲
        sub_4649B0(640, 402, -1, -16777216, 3, &byte_98B900, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
        return;
      }
      if ( *(uint8_t *)(v16 + 17) != 0
        && (dword_79BE3C == *(uint32_t *)(v16 + 12) || dword_79BE342 == *(uint32_t *)(v16 + 12) || dword_79BE382 == *(uint32_t *)(v16 + 12))  // 动画对象指针(帧同步比对基准 C)
        && x >= 63
        && x <= 265
        && y >= 421
        && y <= 442
        && *(uint32_t *)(pThis2[1] + 104) == 12 )  // HUD 悬停提示总绘（血量/蓝量/经验/点数）
      {
        v25 = pThis2[309];
        if ( v25 != 0 )
        {
          if ( v25 != 1 )
            return;
          if ( *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 116) == 0 )  // 调 表按键查找（uint16）
          {
            v29 = sub_422E70(191);  // 调 存 CStringManager::getStr 取本地化串
            sub_4649B0(185, 417, -1, -16777216, 2, v29, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
            return;
          }
          v30 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04) + 52);  // 调用虚函数（虚表槽 +1032）
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04);  // 调用虚函数（虚表槽 +1032）
          v151 = (float)(v30
                       - *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04) + 60));  // 调用虚函数（虚表槽 +1032）
          v128 = (uint64_t)v151;
          v28 = sub_422E70(192);  // 调 存 CStringManager::getStr 取本地化串
        }
        else
        {
          v145 = (float)*(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1032))(pObj) + 40);  // 调用虚函数（虚表槽 +1032）
          *(double *)&v26 = v145
                          / (double)*(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1032))(dword_8F7C04)  // 调用虚函数（虚表槽 +1032）
                                           + 44)
                          * 100.0;
          v27 = (*(int (/*cdecl*/ **)(uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 1032))(v26, HIDWORD(v26));  // 调用虚函数（虚表槽 +1032）
          v128 = *(uint32_t *)((*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F7C04 + 1032))(  // 调用虚函数（虚表槽 +1032）
                               dword_8F7C04,  // dword_8F7C04 = 本地玩家对象
                               *(uint32_t *)(v27 + 44))
                           + 40);
          v28 = sub_422E70(190);  // 调 存 CStringManager::getStr 取本地化串
        }
        sprintf(&byte_98B900, v28, v128);  // 调 格式化到缓冲
        sub_4649B0(185, 417, -1, -16777216, 2, &byte_98B900, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
        return;
      }
      if ( *(uint8_t *)(v16 + 17) != 0
        && (dword_79BE3C == *(uint32_t *)(v16 + 12) || dword_79BE342 == *(uint32_t *)(v16 + 12) || dword_79BE382 == *(uint32_t *)(v16 + 12))  // 动画对象指针(帧同步比对基准 C)
        && *(uint32_t *)(dword_8F7A24 + 12) != 0  // dword_8F7A24 = 当前场景状态对象
        && word_8F7C14 != 0 )  // 疲劳上限
      {
        if ( x >= 290 && x <= 350 && y >= 410 && y <= 425 )  // 若 x >= 290 与/或 x <= 350 与/或 y >= 410
        {
          v136 = (uint16_t)word_8F7C14;  // 疲劳上限
          v131 = (uint16_t)word_8F7C14 - (uint16_t)word_8F7C10;  // 疲劳值
          v31 = sub_422E70(193);  // 调 存 CStringManager::getStr 取本地化串
          sprintf(&byte_98B900, v31, v131, v136);  // 调 格式化到缓冲
          sub_4649B0(320, 409, -1, -16777216, 2, &byte_98B900, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
          return;
        }
        dword_79BE3C2 = dword_79BE3C;  // 动画对象指针(帧同步比对基准 C)
      }
      if ( *(uint8_t *)(v16 + 17) == 0
        || dword_79BE3C2 != *(uint32_t *)(v16 + 12) && (v32 = *(uint32_t *)(v16 + 12), dword_79BE342 != v32) && dword_79BE382 != v32 )
      {
        v33 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 36);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        if ( *(uint8_t *)(v33 + 17) == 0
          || (v34 = *(uint32_t *)(v33 + 12), dword_79BE3C != v34) && dword_79BE34 != v34 && dword_79BE38 != v34 )  // 动画对象指针(帧同步比对基准 C)
        {
LABEL_120:
          v152 = 0;
          while ( 1 )  // 无限循环
          {
            v40 = pThis2[1];
            v41 = x;
            v42 = y;
            v43 = *(uint32_t *)(v40 + 4 * (v152 != 0) + 104);
            switch ( v43 )  // 按 v43 分派
            {
              case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
                v44 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v40 + 76) + 48))(*(uint32_t *)(v40 + 76));  // 调用虚函数（虚表槽 +48）
                if ( *(uint8_t *)(v44 + 17) != 0 )
                {
                  v45 = *(uint32_t *)(v44 + 12);
                  if ( dword_79BE3C == v45 || dword_79BE34 == v45 || dword_79BE38 == v45 )  // 若 dword_79BE3C == v45 与/或 dword_79BE34 == v45 与/或 dword_79BE38 == v45
                  {
                    v46 = 2;
                    v146 = 2;
                    v47 = 7;
                    v48 = 0;
                    while ( 1 )  // 无限循环
                    {
                      v49 = dword_6C77A4[v48];
                      if ( v41 >= v49 && v41 < v49 + 126 )  // 若 v41 >= v49 与/或 v41 < v49
                        break;
                      if ( ++v48 >= 2 )
                        goto LABEL_132;
                    }
                    v46 = v48;
                    v146 = v48;
LABEL_132:
                    v50 = 0;
                    while ( 1 )  // 无限循环
                    {
                      v51 = dword_6C7788[v50];
                      if ( v42 >= v51 && v42 < v51 + 22 )  // 若 v42 >= v51 与/或 v42 < v51
                        break;
                      if ( ++v50 >= 7 )
                        goto LABEL_138;
                    }
                    v47 = v50;
LABEL_138:
                    byte_98B900 = 0;
                    if ( v46 == 0 )
                    {
                      if ( v47 != 0 )
                      {
                        if ( v47 == 1 )
                        {
                          strcpy(&byte_98B900, sub_422E70(199));  // 调 字符串拷贝入口（跳到拷贝内核）
                        }
                        else if ( v47 == 2 )
                        {
                          strcpy(&byte_98B900, sub_422E70(200));  // 调 字符串拷贝入口（跳到拷贝内核）
                        }
                        else
                        {
                          if ( v47 == 3 )
                          {
                            v148 = (float)(*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 708))(  // 调虚槽 +708：CMOlreks 油桶构造 vmt2C4
                                            dword_8F7C04,  // dword_8F7C04 = 本地玩家对象
                                            0,
                                            3);
                            v52 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
                            v53 = sub_41A5E0(v52 + 1124);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
                            v139 = 7;
                          }
                          else
                          {
                            if ( v47 != 4 )
                            {
                              if ( v47 == 5 )
                              {
                                strcpy(&byte_98B900, sub_422E70(203));  // 调 字符串拷贝入口（跳到拷贝内核）
                              }
                              else if ( v47 == 6 )
                              {
                                strcpy(&byte_98B900, sub_422E70(204));  // 调 字符串拷贝入口（跳到拷贝内核）
                              }
                              goto LABEL_177;
                            }
                            v148 = (float)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F7C04 + 708))(  // 调虚槽 +708：CMOlreks 油桶构造 vmt2C4
                                            dword_8F7C04,  // dword_8F7C04 = 本地玩家对象
                                            1,
                                            3);
                            v57 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
                            v53 = sub_41A5E0(v57 + 1166);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
                            v139 = 9;
                          }
                          v54 = (uint64_t)(sub_433F60(dword_8F7C04, v139) * (double)v53);  // dword_8F7C04 = 本地玩家对象
                          v55 = v148;
                          if ( (uint32_t)v54 != 0 )
                          {
                            v140 = v54;
                            v58 = sub_422E70(201);  // 调 存 CStringManager::getStr 取本地化串
                            sprintf(&byte_98B900, v58, (unsigned int)(uint64_t)v55, v140);  // 调 格式化到缓冲
                          }
                          else
                          {
                            v56 = sub_422E70(202);  // 调 存 CStringManager::getStr 取本地化串
                            sprintf(&byte_98B900, v56, (unsigned int)(uint64_t)v55);  // 调 格式化到缓冲
                          }
                        }
                      }
                      else
                      {
                        strcpy(&byte_98B900, sub_422E70(198));  // 调 字符串拷贝入口（跳到拷贝内核）
                      }
LABEL_177:
                      if ( strcmp(&byte_98B900, szPassword) != 0 )  // 调 串比较
                        sub_4649B0(  // 调 带框文本上屏（静态一次性初始化）
                          dword_6C77A4[v146] + 63,
                          dword_6C7788[v47],
                          -1,
                          -16777216,
                          2,
                          &byte_98B900,
                          0,
                          0,
                          1600,
                          0);
                      break;
                    }
                    if ( v46 != 1 )
                      goto LABEL_177;
                    if ( v47 == 0 )
                    {
                      strcpy(&byte_98B900, sub_422E70(205));  // 调 字符串拷贝入口（跳到拷贝内核）
                      goto LABEL_177;
                    }
                    if ( v47 == 1 )
                    {
                      strcpy(&byte_98B900, sub_422E70(206));  // 调 字符串拷贝入口（跳到拷贝内核）
                      goto LABEL_177;
                    }
                    if ( v47 == 2 )
                    {
                      strcpy(&byte_98B900, sub_422E70(207));  // 调 字符串拷贝入口（跳到拷贝内核）
                      goto LABEL_177;
                    }
                    if ( v47 == 3 )
                    {
                      v155 = 0.0;
                      v156 = 0.0;
                      v59 = *(uint32_t *)dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
                      v60 = sub_4E66B0(0);  // 调 场景/角色系数查询（PVP 50 / 战场表 / 角色技能表）
                      (*(void (/*thiscall*/ **)(int, float *, float *, int, uint32_t, int))(v59 + 716))(  // 调虚槽 +716：音效地板停播 vmt2CC
                        dword_8F7C04,  // dword_8F7C04 = 本地玩家对象
                        &v155,
                        &v156,
                        v60,
                        0,
                        3);
                      v155 = v155 * 100.0;
                      v156 = v156 * 100.0;
                      v61 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
                      v143 = sub_41A5E0(v61 + 1138);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
                      v62 = sub_433F60(dword_8F7C04, 8) * (double)v143;  // dword_8F7C04 = 本地玩家对象
                      if ( (unsigned int)(uint64_t)v62 == 0 )
                      {
                        v132 = v156;
                        v129 = v155;
                        v63 = v156 + v155;
LABEL_171:
                        v70 = sub_422E70(209);  // 调 存 CStringManager::getStr 取本地化串
                        sprintf(&byte_98B900, v70, v63, v129, v132);  // 调 格式化到缓冲
                        goto LABEL_177;
                      }
                      v149 = v62;
                      v141 = sub_432F40(v149);  // 调 舍入取整（float → int）
                      v130 = v156;
                      v122 = v155;
                      v64 = v156 + v155;
                    }
                    else
                    {
                      if ( v47 != 4 )
                      {
                        if ( v47 == 5 )
                        {
                          strcpy(&byte_98B900, sub_422E70(210));  // 调 字符串拷贝入口（跳到拷贝内核）
                        }
                        else if ( v47 == 6 )
                        {
                          strcpy(&byte_98B900, sub_422E70(211));  // 调 字符串拷贝入口（跳到拷贝内核）
                        }
                        goto LABEL_177;
                      }
                      v153 = 0.0;
                      v154 = 0.0;
                      v66 = *(uint32_t *)dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
                      v67 = sub_4E66B0(0);  // 调 场景/角色系数查询（PVP 50 / 战场表 / 角色技能表）
                      (*(void (/*thiscall*/ **)(int, float *, float *, int, int, int))(v66 + 716))(  // 调虚槽 +716：音效地板停播 vmt2CC
                        dword_8F7C04,  // dword_8F7C04 = 本地玩家对象
                        &v153,
                        &v154,
                        v67,
                        1,
                        3);
                      v153 = v153 * 100.0;
                      v154 = v154 * 100.0;
                      v68 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
                      v144 = sub_41A5E0(v68 + 1180);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
                      v69 = sub_433F60(dword_8F7C04, 10) * (double)v144;  // dword_8F7C04 = 本地玩家对象
                      if ( (unsigned int)(uint64_t)v69 == 0 )
                      {
                        v132 = v154;
                        v129 = v153;
                        v63 = v154 + v153;
                        goto LABEL_171;
                      }
                      v150 = v69;
                      v141 = sub_432F40(v150);  // 调 舍入取整（float → int）
                      v130 = v154;
                      v122 = v153;
                      v64 = v154 + v153;
                    }
                    v65 = sub_422E70(208);  // 调 存 CStringManager::getStr 取本地化串
                    sprintf(&byte_98B900, v65, v64, v122, v130, v141);  // 调 格式化到缓冲
                    goto LABEL_177;
                  }
                }
                break;
              case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
                v71 = *(uint32_t **)(v40 + 56);
                v72 = (*(int (/*thiscall*/ **)(uint32_t *))(*v71 + 48))(v71);  // 调用虚函数（虚表槽 +48）
                if ( *(uint8_t *)(v72 + 17) != 0
                  && (dword_79BE3C == *(uint32_t *)(v72 + 12)  // 动画对象指针(帧同步比对基准 C)
                   || dword_79BE34 == *(uint32_t *)(v72 + 12)  // 当前动画对象指针(帧同步比对基准)
                   || dword_79BE38 == *(uint32_t *)(v72 + 12)) )  // 动画对象指针(帧同步比对基准 B)
                {
                  if ( v41 >= 445 && v41 < 535 && v42 >= 349 && v42 < 359 )  // 若 v41 >= 445 与/或 v41 < 535 与/或 v42 >= 349
                  {
                    v147 = *((uint32_t *)dword_8F852C + 1);  // dword_8F852C = UI 管理器全局
                    v133 = (double)sub_484FA0() * 0.001;  // 调 全局时间系数计算（+732 与 +746 相乘）
                    v73 = sub_422E70(212);  // 调 存 CStringManager::getStr 取本地化串
                    sprintf(&byte_98B900, v73, (double)v147 * 0.001, v133);  // 调 格式化到缓冲
                    sub_4649B0(490, 347, -1, -16777216, 2, &byte_98B900, 0, 1, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                  }
                  if ( v41 >= 336 && v41 < 463 && v42 >= 374 && v42 < 403 )  // 若 v41 >= 336 与/或 v41 < 463 与/或 v42 >= 374
                  {
                    v74 = sub_422E70(213);  // 调 存 CStringManager::getStr 取本地化串
                    sub_4649B0(399, 374, -1, -16777216, 2, v74, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                  }
                  if ( v41 >= 465 && v41 < 592 && v42 >= 374 && v42 < 403 )  // 若 v41 >= 465 与/或 v41 < 592 与/或 v42 >= 374
                  {
                    v75 = sub_422E70(214);  // 调 存 CStringManager::getStr 取本地化串
                    sub_4649B0(528, 374, -1, -16777216, 2, v75, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                  }
                  if ( v41 >= 335 && v41 < 414 && v42 >= 345 && v42 < 364 )  // 若 v41 >= 335 与/或 v41 < 414 与/或 v42 >= 345
                  {
                    v76 = sub_422E70(215);  // 调 存 CStringManager::getStr 取本地化串
                    sub_4649B0(374, 345, -1, -16777216, 2, v76, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                  }
                }
                v77 = v71[12];
                if ( *(uint8_t *)(v77 + 17) != 0 )
                {
                  v78 = *(uint32_t *)(v77 + 12);
                  if ( dword_79BE3C == v78 || dword_79BE34 == v78 || dword_79BE38 == v78 )  // 若 dword_79BE3C == v78 与/或 dword_79BE34 == v78 与/或 dword_79BE38 == v78
                  {
                    if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )  // dword_8F7A24 = 当前场景状态对象
                      v79 = sub_422E70(216);  // 调 存 CStringManager::getStr 取本地化串
                    else
                      v79 = sub_422E70(217);  // 调 存 CStringManager::getStr 取本地化串
                    sub_4649B0(352, 376, -1, -16777216, 2, v79, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                  }
                }
                v80 = v71[11];
                if ( *(uint8_t *)(v80 + 17) != 0 )
                {
                  v81 = *(uint32_t *)(v80 + 12);
                  if ( dword_79BE3C == v81 || dword_79BE34 == v81 || dword_79BE38 == v81 )  // 若 dword_79BE3C == v81 与/或 dword_79BE34 == v81 与/或 dword_79BE38 == v81
                  {
                    v82 = sub_422E70(218);  // 调 存 CStringManager::getStr 取本地化串
                    sub_4649B0(571, 342, -1, -16777216, 2, v82, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                  }
                }
                v83 = 0;
                v84 = v71 + 6;
                while ( 1 )  // 无限循环
                {
                  v85 = *v84;
                  if ( *(uint8_t *)(*v84 + 17) != 0
                    && (dword_79BE3C == *(uint32_t *)(v85 + 12)  // 动画对象指针(帧同步比对基准 C)
                     || dword_79BE34 == *(uint32_t *)(v85 + 12)  // 当前动画对象指针(帧同步比对基准)
                     || dword_79BE38 == *(uint32_t *)(v85 + 12)) )  // 动画对象指针(帧同步比对基准 B)
                  {
                    break;
                  }
                  ++v83;
                  ++v84;
                  if ( v83 >= 4 )
                    goto LABEL_233;
                }
                if ( v83 != 0 )
                {
                  switch ( v83 )  // 按 v83 分派
                  {
                    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
                      strcpy(&byte_98B900, sub_422E70(220));  // 调 字符串拷贝入口（跳到拷贝内核）
                      break;
                    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
                      strcpy(&byte_98B900, sub_422E70(221));  // 调 字符串拷贝入口（跳到拷贝内核）
                      break;
                    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
                      strcpy(&byte_98B900, sub_422E70(222));  // 调 字符串拷贝入口（跳到拷贝内核）
                      break;
                    default:
                      break;
                  }
                }
                else
                {
                  strcpy(&byte_98B900, sub_422E70(219));  // 调 字符串拷贝入口（跳到拷贝内核）
                }
                sub_4649B0((v83 << 6) + 371, 186, -1, -16777216, 2, &byte_98B900, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
LABEL_233:
                v86 = sub_547450(v71);  // 调 物品栏格子重建（28 行）
                v87 = v86;
                if ( v86 != 18
                  && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, v86) == 0 )  // 调用虚函数（虚表槽 +792）
                {
                  v142 = (int)*(&dword_9B88D8 + v87);
                  v88 = sub_422E70(223);  // 调 存 CStringManager::getStr 取本地化串
                  sprintf(&byte_98B900, v88, v142);  // 调 格式化到缓冲
                  v121 = sub_5472B0(v87);  // 调 10 行小辅助 2
                  v120 = sub_547290(v87) + 14;  // 调 10 行小辅助
                  sub_4649B0(v120, v121, -1, -16777216, 2, &byte_98B900, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                }
                break;
              case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
                v89 = *(uint32_t **)(v40 + 88);
                v90 = v89[29];
                v91 = *(uint8_t *)(v90 + 17);
                if ( v91 != 0 && dword_79BE3C == *(uint32_t *)(v90 + 12)  // 动画对象指针(帧同步比对基准 C)
                  || v91 != 0 && ((v92 = *(uint32_t *)(v90 + 12), dword_79BE34 == v92) || dword_79BE38 == v92) )  // 当前动画对象指针(帧同步比对基准)
                {
                  v93 = sub_422E70(224);  // 调 存 CStringManager::getStr 取本地化串
                }
                else
                {
                  v94 = v89[30];
                  if ( *(uint8_t *)(v94 + 17) != 0
                    && ((v95 = *(uint32_t *)(v94 + 12), dword_79BE3C == v95) || dword_79BE34 == v95 || dword_79BE38 == v95) )  // 动画对象指针(帧同步比对基准 C)
                  {
                    v93 = sub_422E70(225);  // 调 存 CStringManager::getStr 取本地化串
                  }
                  else
                  {
                    v96 = v89[31];
                    if ( *(uint8_t *)(v96 + 17) == 0 )
                      break;
                    v97 = *(uint32_t *)(v96 + 12);
                    if ( dword_79BE3C != v97 && dword_79BE34 != v97 && dword_79BE38 != v97 )  // 若 dword_79BE3C != v97 与/或 dword_79BE34 != v97 与/或 dword_79BE38 != v97
                      break;
                    v93 = sub_422E70(226);  // 调 存 CStringManager::getStr 取本地化串
                  }
                }
                sub_4649B0(168, 400, -1, -16777216, 2, v93, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                break;
              case 4:  // case 4 = ENUM_CMDPACKET_EXIT
                v98 = *(uint32_t *)(v40 + 72);
                v99 = *(uint32_t *)(v98 + 44);
                if ( *(uint8_t *)(v99 + 17) != 0
                  && ((v100 = *(uint32_t *)(v99 + 12), dword_79BE3C == v100)  // 动画对象指针(帧同步比对基准 C)
                   || dword_79BE34 == v100  // 当前动画对象指针(帧同步比对基准)
                   || dword_79BE38 == v100) )  // 动画对象指针(帧同步比对基准 B)
                {
                  v123 = sub_422E70(227);  // 调 存 CStringManager::getStr 取本地化串
                  sub_4649B0(434, 395, -1, -16777216, 2, v123, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                }
                else
                {
                  v101 = *(uint32_t *)(v98 + 48);
                  if ( *(uint8_t *)(v101 + 17) != 0 )
                  {
                    v102 = *(uint32_t *)(v101 + 12);
                    if ( dword_79BE3C == v102 || dword_79BE34 == v102 || dword_79BE38 == v102 )  // 若 dword_79BE3C == v102 与/或 dword_79BE34 == v102 与/或 dword_79BE38 == v102
                    {
                      v124 = sub_422E70(228);  // 调 存 CStringManager::getStr 取本地化串
                      sub_4649B0(517, 395, -1, -16777216, 2, v124, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                    }
                  }
                }
                break;
              case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
                v103 = *(uint32_t *)(v40 + 64);
                v104 = *(uint32_t *)(v103 + 20);
                if ( *(uint8_t *)(v104 + 17) != 0
                  && ((v105 = *(uint32_t *)(v104 + 12), dword_79BE3C == v105)  // 动画对象指针(帧同步比对基准 C)
                   || dword_79BE34 == v105  // 当前动画对象指针(帧同步比对基准)
                   || dword_79BE38 == v105) )  // 动画对象指针(帧同步比对基准 B)
                {
                  v125 = sub_422E70(229);  // 调 存 CStringManager::getStr 取本地化串
                  sub_4649B0(174, 266, -1, -16777216, 2, v125, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                }
                else
                {
                  v106 = *(uint32_t *)(v103 + 24);
                  if ( *(uint8_t *)(v106 + 17) != 0 )
                  {
                    v107 = *(uint32_t *)(v106 + 12);
                    if ( dword_79BE3C == v107 || dword_79BE34 == v107 || dword_79BE38 == v107 )  // 若 dword_79BE3C == v107 与/或 dword_79BE34 == v107 与/或 dword_79BE38 == v107
                    {
                      v126 = sub_422E70(230);  // 调 存 CStringManager::getStr 取本地化串
                      sub_4649B0(178, 395, -1, -16777216, 2, v126, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                    }
                  }
                }
                break;
              case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
                v108 = *(uint32_t **)(v40 + 80);
                v109 = v108[15];
                if ( *(uint8_t *)(v109 + 17) != 0 )
                {
                  v110 = *(uint32_t *)(v109 + 12);
                  if ( dword_79BE3C == v110 || dword_79BE34 == v110 || dword_79BE38 == v110 )  // 若 dword_79BE3C == v110 与/或 dword_79BE34 == v110 与/或 dword_79BE38 == v110
                  {
                    v111 = v108[15];
                    v127 = 231;
                    goto LABEL_293;
                  }
                }
                v112 = v108[16];
                if ( *(uint8_t *)(v112 + 17) != 0 )
                {
                  v113 = *(uint32_t *)(v112 + 12);
                  if ( dword_79BE3C == v113 || dword_79BE34 == v113 || dword_79BE38 == v113 )  // 若 dword_79BE3C == v113 与/或 dword_79BE34 == v113 与/或 dword_79BE38 == v113
                  {
                    v111 = v108[16];
                    v127 = 232;
                    goto LABEL_293;
                  }
                }
                if ( (uint8_t)sub_43BCB0(v108[17]) != 0 )  // 调 焦点窗口判定（三选）
                {
                  v111 = v108[17];
                  v127 = 233;
                  goto LABEL_293;
                }
                if ( (uint8_t)sub_43BCB0(v108[18]) != 0 )  // 调 焦点窗口判定（三选）
                {
                  v114 = v108[18];
                  v115 = *(uint32_t *)(v114 + 24);
                  v116 = *(uint32_t *)(v114 + 20);
                  v117 = sub_422E70(234);  // 调 存 CStringManager::getStr 取本地化串
                  v118 = v116 + 25;
                  goto LABEL_294;
                }
                if ( (uint8_t)sub_43BCB0(v108[19]) != 0 )  // 调 焦点窗口判定（三选）
                {
                  v111 = v108[19];
                  v127 = 235;
LABEL_293:
                  v115 = *(uint32_t *)(v111 + 24);
                  v119 = *(uint32_t *)(v111 + 20);
                  v117 = sub_422E70(v127);  // 调 存 CStringManager::getStr 取本地化串
                  v118 = v119 + 17;
LABEL_294:
                  sub_4649B0(v118, v115, -1, -16777216, 2, v117, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
                }
                break;
              default:
                break;
            }
            if ( ++v152 >= 2 )
              return;
          }
        }
        pObj = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
      }
      if ( x < 305 || x > 335 )  // 若 x < 305 与/或 x > 335
      {
        v35 = y;
      }
      else
      {
        v35 = y;
        if ( y >= 455 && y <= 480 )  // 若 y >= 455 与/或 y <= 480
        {
          v137 = Value;
          v36 = sub_422E70(194);  // 调 存 CStringManager::getStr 取本地化串
          sprintf(&byte_98B900, v36, v137);  // 调 格式化到缓冲
          sub_4649B0(320, 416, -1, -16777216, 2, &byte_98B900, 0, 1, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
          return;
        }
      }
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1064))(pObj) != 100  // 调用虚函数（虚表槽 +1064）
        && x >= 62
        && x <= 83
        && v35 >= 398
        && v35 <= 419 )
      {
        v138 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1064))(dword_8F7C04);  // 调用虚函数（虚表槽 +1064）
        v37 = sub_422E70(195);  // 调 存 CStringManager::getStr 取本地化串
        sprintf(&byte_98B900, v37, v138);  // 调 格式化到缓冲
        sub_4649B0(72, 398, -1, -16777216, 2, &byte_98B900, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
        return;
      }
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )  // dword_8F7A24 = 当前场景状态对象
      {
        if ( *(int *)dword_99FB70 > 0 && x >= 526 && x <= 580 && v35 >= 24 && v35 <= 46 )  // 若 x >= 526 与/或 x <= 580
        {
          v38 = sub_422E70(196);  // 调 存 CStringManager::getStr 取本地化串
          sub_4649B0(526, 35, -1, -16777216, 6, v38, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
          return;
        }
        if ( x >= 536 && x <= 629 && v35 >= 24 && v35 <= 117 )  // 若 x >= 536 与/或 x <= 629 与/或 v35 >= 24
        {
          v39 = sub_422E70(197);  // 调 存 CStringManager::getStr 取本地化串
          sub_4649B0(627, 93, -1, -16777216, 9, v39, 0, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
          return;
        }
      }
      goto LABEL_120;
    }
    v12 = *(uint32_t *)LODWORD(v153);  // 调 取 64 位值低 32 位
    if ( *(uint8_t *)(*(uint32_t *)LODWORD(v153) + 17) != 0 )  // 调 取 64 位值低 32 位
    {
      if ( dword_79BE3C == *(uint32_t *)(v12 + 12) )  // 动画对象指针(帧同步比对基准 C)
        break;
      if ( dword_79BE34 == *(uint32_t *)(v12 + 12) )  // 当前动画对象指针(帧同步比对基准)
        break;
      pObj = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
      if ( dword_79BE38 == *(uint32_t *)(v12 + 12) )  // 动画对象指针(帧同步比对基准 B)
        break;
    }
    ++v9;
  }
  v13 = *(uint32_t *)(dword_8F8540 + 8);  // dword_8F8540 = 技能/条目全局链
  if ( v13 != 0 && v9 < (*(uint32_t *)(dword_8F8540 + 12) - v13) / 20 )  // dword_8F8540 = 技能/条目全局链
    v14 = *(uint32_t *)(*(uint32_t *)(dword_8F8540 + 8) + 20 * v9);  // dword_8F8540 = 技能/条目全局链
  else
    v14 = 0;
  if ( *(uint32_t *)(v14 + 28) < 0x10u )
    v15 = v14 + 8;
  else
    v15 = *(uint32_t *)(v14 + 8);
  sub_4649B0(  // 调 带框文本上屏（静态一次性初始化）
    *(uint32_t *)(pThis2[v9 + 21] + 20) + (*(uint32_t *)(pThis2[v9 + 21] + 28) >> 1),
    *(uint32_t *)(pThis2[v9 + 21] + 24) - 4,
    -1,
    -16777216,
    2,
    v15,
    0,
    0,
    1600,
    0);
}


// ------------------------------------------------------------
// 0x466340 sub_466340 —— 地面掉落物名称标签绘制
// 仅域号 3/6：取场景对象 vt+104 的实体数组（+120/+124），__RTDynamicCast 过滤出 CNRDItemObject（RTTI 自证），其 +972 为非空名牌件。
// sub_45E490/45E4D0 坐标换算与 sub_424680 透视变换后按 vt+108 取名串。
// vt+44 不超过 1 直上屏，否则按 %s(%d%s) 拼计数，经 sub_4649B0 落物名上方 -10。
// ------------------------------------------------------------
int sub_466340()  // 函数: 地面掉落物名称标签绘制
{
  int result; // eax
  int v1; // ecx
  int v2; // ebx
  unsigned int v3; // edx
  int v4; // ecx
  int v5; // ecx
  uint32_t *v6; // eax
  uint8_t *pObj; // eax
  uint8_t *pObj2; // edi
  int *v9; // esi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // eax
  const char *v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // [esp-28h] [ebp-244h]
  int v19; // [esp-28h] [ebp-244h]
  int v20; // [esp-18h] [ebp-234h]
  int v21; // [esp-18h] [ebp-234h]
  int v22; // [esp-14h] [ebp-230h]
  int v23; // [esp-10h] [ebp-22Ch]
  int v24; // [esp-Ch] [ebp-228h]
  const char *v25; // [esp-Ch] [ebp-228h]
  int i; // [esp+4h] [ebp-218h]
  int v27; // [esp+8h] [ebp-214h]
  int v28; // [esp+Ch] [ebp-210h] BYREF
  int v29; // [esp+10h] [ebp-20Ch] BYREF
  int v30; // [esp+14h] [ebp-208h]
  char Buffer[512]; // [esp+18h] [ebp-204h] BYREF
  int dword_796E502; // [esp+218h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  result = dword_8F7A24;  // dword_8F7A24 = 当前场景状态对象
  v1 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 = 当前场景状态对象
  if ( v1 == 3 )
  {
    result = *(uint32_t *)(dword_8F7A24 + 28);  // dword_8F7A24 = 当前场景状态对象
    v2 = *(uint32_t *)(*(uint32_t *)(result + 16) + 104);
    v30 = v2;
  }
  else
  {
    if ( v1 != 6 )
      return result;
    result = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16);  // dword_8F7A24 = 当前场景状态对象
    v30 = *(uint32_t *)(result + 104);
    v2 = v30;
  }
  v3 = 0;
  if ( v2 != 0 )
  {
    v4 = *(uint32_t *)(v2 + 120);
    if ( v4 != 0 )
    {
      result = (*(uint32_t *)(v2 + 124) - v4) >> 2;
      v27 = result;
    }
    else
    {
      v27 = 0;
    }
    for ( i = 0; i < v27; ++i )
    {
      v5 = *(uint32_t *)(v2 + 120);
      if ( v5 != 0 && v3 < (*(uint32_t *)(v2 + 124) - v5) >> 2 )
        v6 = *(uint32_t **)(v5 + 4 * v3);
      else
        v6 = nullptr;
      pObj = __RTDynamicCast(v6, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNRDItemObject `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      pObj2 = pObj;
      if ( pObj != nullptr )  // 若 pObj 有效（非空）
      {
        v9 = *((int **)pObj + 243);
        if ( v9 != nullptr )  // 若 v9 有效（非空）
        {
          v24 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 36))(pObj) + 8);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
          v10 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj2 + 120))(pObj2);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          v29 = sub_45E490(v10, v24);  // 调 屏幕 y → 演出层坐标（减基线）
          v23 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj2 + 36))(pObj2) + 8);  // 调用虚函数（虚表槽 +36）【推断: 取坐标三元组指针】
          v22 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj2 + 128))(pObj2);  // 调用虚函数（虚表槽 +128）
          v11 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj2 + 124))(pObj2);  // 调用虚函数（虚表槽 +124）
          v28 = sub_45E4D0(v11, v22, v23, 1.0);  // 调 带比例的回换算（nArg2 - nArg3*f + 120）
          sub_424680((int)&v29, (int)&v28, 0.0, 0.0);  // 调 透明坐标变换
          v12 = (*(int (/*thiscall*/ **)(int *))(*v9 + 16))(v9);  // 调用虚函数（虚表槽 +16）
          v13 = *v9;
          if ( *(uint32_t *)(v12 + 4) != 0 )
          {
            v15 = (const char *)(*(int (/*thiscall*/ **)(int *))(v13 + 108))(v9);  // 调用虚函数（虚表槽 +108）【推断: 坐标三分量设置（+4/+8/+12，带有效性与等值判定）】
            if ( (unsigned int)(*(int (/*thiscall*/ **)(int *))(*v9 + 44))(v9) <= 1 )  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
            {
              v21 = pObj2[976];
              v19 = (*(int (/*thiscall*/ **)(int *))(*v9 + 24))(v9);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
              sub_4649B0(v29, v28 - 10, v19, -16777216, 2, v15, v21, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
            }
            else
            {
              v16 = sub_422E70(20002);  // 调 存 CStringManager::getStr 取本地化串
              v17 = (*(int (/*thiscall*/ **)(int *, int))(*v9 + 44))(v9, v16);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
              sprintf(Buffer, "%s(%d%s)", v15, v17, v25);  // 调 格式化到缓冲
              v20 = pObj2[976];
              v18 = (*(int (/*thiscall*/ **)(int *))(*v9 + 24))(v9);  // 调用虚函数（虚表槽 +24）【推断: 主播放驱动·usercall 变体（ecx/ebx 传参；+44…】
              sub_4649B0(v29, v28 - 10, v18, -16777216, 2, Buffer, v20, 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
            }
            v2 = v30;
          }
          else
          {
            v14 = (*(int (/*thiscall*/ **)(int *))(v13 + 44))(v9);  // 调用虚函数（虚表槽 +44）【推断: vmt2C / 0x42A550 vmt30 / 0x42A56…】
            sprintf(Buffer, off_6C789C, v14);  // 调 格式化到缓冲
            sub_4649B0(v29, v28 - 10, -1, -16777216, 2, Buffer, pObj2[976], 0, 1600, 0);  // 调 带框文本上屏（静态一次性初始化）
          }
        }
      }
      result = v27;
      v3 = i + 1;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4665D0 sub_4665D0 —— PVP 队伍 8 格成员框绘制
// dword_99FEC0 非 0 时：8 格坐标表 (4/39/324/484 混排) 逐格 sub_42B340 建虚拟角色并 vt+384 绘头像。
// vt+376 取职业链、·sub_4633B0 取名串，并 sub_4611D0 叠网络延迟指示。
// 末段对 8 格再走一遍紧凑布局。
// ------------------------------------------------------------
char /*usercall*/ sub_4665D0@<al>(char *pszArg1@<ecx>, char *pszArg2@<edi>)  // 实现：PVP 队伍 8 格成员框绘制
{
  int v2; // eax
  int v3; // edi
  int *v4; // ebx
  int *v5; // esi
  int v6; // ebx
  int v7; // edi
  bool v8; // zf
  int v9; // edi
  uint32_t *v10; // eax
  int pObj6; // eax
  int pObj3; // eax
  int pObj; // eax
  int v14; // eax
  int pObj5; // eax
  int v16; // eax
  uint64_t v17; // rax
  int v18; // eax
  uint64_t v19; // rax
  int pObj8; // eax
  uint32_t *v21; // eax
  int pObj4; // eax
  int v23; // edx
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int pObj2; // eax
  int pObj7; // eax
  int *v29; // esi
  bool (/*cdecl*/ *v30)(struct Concurrency::details::_UnrealizedChore *, void *); // esi
  int v32; // [esp-10h] [ebp-78h]
  int v33; // [esp-10h] [ebp-78h]
  int v35; // [esp+0h] [ebp-68h] BYREF
  uint32_t v36[7]; // [esp+4h] [ebp-64h] BYREF
  int v37; // [esp+20h] [ebp-48h] BYREF
  uint32_t v38[7]; // [esp+24h] [ebp-44h] BYREF
  unsigned int v39; // [esp+40h] [ebp-28h]
  int pObj22; // [esp+44h] [ebp-24h]
  bool (/*cdecl*/ *v41)(struct Concurrency::details::_UnrealizedChore *, void *); // [esp+48h] [ebp-20h]
  int *v42; // [esp+4Ch] [ebp-1Ch]
  int *v43; // [esp+50h] [ebp-18h]
  int v44; // [esp+54h] [ebp-14h]
  int *v45; // [esp+58h] [ebp-10h]
  int *v46; // [esp+5Ch] [ebp-Ch]
  int *v47; // [esp+60h] [ebp-8h]
  char *pszArg12; // [esp+64h] [ebp-4h]

  LOBYTE(v2) = dword_8F7C04;  // 调 取 16 位值低 8 位
  pszArg12 = pszArg1;
  if ( dword_8F7C04 != 0 )  // dword_8F7C04 = 本地玩家对象
  {
    LOBYTE(v2) = dword_99FEC0;  // 调 取 16 位值低 8 位
    if ( dword_99FEC0 != 0 )  // PVP 对局进行中标志
    {
      v35 = 4;
      v36[0] = 4;
      v36[2] = 4;
      v36[4] = 4;
      v36[6] = 4;
      v37 = 4;
      v38[0] = 39;
      v38[2] = 39;
      v38[4] = 39;
      v38[6] = 39;
      v36[5] = 484;
      v38[5] = 484;
      v36[3] = 324;
      v38[3] = 324;
      v45 = v38;
      v3 = 0;
      v4 = &v37;
      v36[1] = 164;
      v38[1] = 164;
      v41 = nullptr;
      v43 = &v37;
      v46 = v36;
      v47 = &v35;
      v42 = v36;
      do
      {
        v2 = sub_48F690(v3);  // 调 槽 id 解析·第二组（偏移 +10）
        v44 = v2;
        if ( v2 != 0 )
          v5 = *(int **)(v2 + 196);
        else
          v5 = nullptr;
        if ( v2 != 0 && v5 != nullptr )  // 若 v2 != 0 与/或 v5 != nullptr
        {
          LOBYTE(v2) = *((uint8_t *)v5 + 8052);  // 调 取 16 位值低 8 位
          if ( (uint8_t)v2 == 0 )
          {
            if ( (uint8_t)sub_48F620(dword_99FEC0) != 0 )  // 调 对局中标志查询
            {
              if ( dword_8F7C04 != 0 && *(uint8_t *)(dword_8F7C04 + 8052) != 0 )  // dword_8F7C04 = 本地玩家对象
              {
                v8 = (*(int (/*thiscall*/ **)(int *))(*v5 + 376))(v5) == 0;  // 调用虚函数（虚表槽 +376）
              }
              else
              {
                v9 = (*(int (/*thiscall*/ **)(int *))(*v5 + 376))(v5);  // 调用虚函数（虚表槽 +376）
                v8 = v9 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);  // 调用虚函数（虚表槽 +376）
              }
              if ( v8 )
              {
                v6 = *v47;
                v7 = *v46;
                v47 += 2;
                v46 += 2;
              }
              else
              {
                v7 = *v45;
                v6 = *v4;
                v43 += 2;
                v45 += 2;
              }
            }
            else
            {
              v6 = *(v42 - 1);
              v7 = *v42;
              v42 += 2;
            }
            v10 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
            *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
            v10[13] = 0;
            v10[14] = v6 + 153;
            v10[15] = 480;
            pObj22 = v6 + 153;
            pObj6 = sub_418DD0(173);  // 调 资源句柄 (101)
            if ( pObj6 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, v6, v7, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            sub_488670(dword_79C0B0);  // 调 视口重置 640x480
            pObj3 = sub_418DD0(174);  // 调 资源句柄 (101)
            if ( pObj3 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, pObj22, v7 + 13, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            if ( (uint8_t)sub_48F620(dword_99FEC0) != 0 )  // 调 对局中标志查询
            {
              if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 376))(v5) != 0 )  // 调用虚函数（虚表槽 +376）
              {
                if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 376))(v5) == 1 )  // 调用虚函数（虚表槽 +376）
                {
                  v33 = sub_418DD0(179);  // 调 资源句柄 (101)
                  sub_40FC80(v6 + 1, v7 + 1, v33);  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
                }
              }
              else
              {
                v32 = sub_418DD0(178);  // 调 资源句柄 (101)
                sub_40FC80(v6 + 1, v7 + 1, v32);  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
              }
            }
            pObj = sub_42B340(v44);  // 调 虚拟角色惰性创建（0x294 字节）
            (*(void (/*thiscall*/ **)(int, int, int, int, int, int, char *))(*(uint32_t *)pObj + 384))(  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
              pObj,
              v6 + 2,
              v7 + 2,
              24,
              24,
              1065353216,  // 常量 1.0f
              pszArg2);
            if ( dword_8F7C04 != 0  // dword_8F7C04 = 本地玩家对象
              && *(uint8_t *)(dword_8F7C04 + 8052) != 0  // dword_8F7C04 = 本地玩家对象
              && *(int **)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 52) == v5 )  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
            {
              sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
              v14 = sub_418DD0(175);  // 调 资源句柄 (101)
              sub_40FC80(v6 + 1, v7 + 1, v14);  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
              sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
            }
            if ( (*(uint8_t (/*thiscall*/ **)(int *))(*v5 + 724))(v5) != 0 )  // 调用虚函数（虚表槽 +724）【推断: [RTTI: IRDActiveObject__vmt2D4 ·…】
            {
              pObj5 = sub_418DD0(91);  // 调 资源句柄 (101)
              if ( pObj5 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v6 + 2, v7 + 2, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            }
            pObj22 = (*(int (/*thiscall*/ **)(int *))(*v5 + 740))(v5);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
            v16 = (*(int (/*thiscall*/ **)(int *))(*v5 + 736))(v5);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
            v17 = (uint64_t)sub_4049C0(0.0, 124.0, v16, pObj22);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
            HIDWORD(v17) = *v5;  // 调 取 64 位值高 32 位
            v39 = v17;
            pObj22 = (*(int (/*thiscall*/ **)(int *))(HIDWORD(v17) + 756))(v5);  // 调用虚函数（虚表槽 +756）【推断: [RTTI: IRDActiveObject__vmt2F4 ·…】
            v18 = (*(int (/*thiscall*/ **)(int *))(*v5 + 752))(v5);  // 调用虚函数（虚表槽 +752）
            pObj22 = (uint64_t)sub_4049C0(0.0, 124.0, v18, pObj22);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
            v19 = __PAIR64__(v39, dword_79C0B0);  // 调 拼装 64 位值(高32,低32)
            *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
            *(uint32_t *)(v19 + 52) = 0;
            *(uint32_t *)(v19 + 56) = HIDWORD(v19) + v6 + 29;  // 调 取 64 位值高 32 位
            *(uint32_t *)(v19 + 60) = 480;
            pObj8 = sub_418DD0(176);  // 调 资源句柄 (101)
            if ( pObj8 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, v6 + 29, v7 + 15, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            sub_488670(dword_79C0B0);  // 调 视口重置 640x480
            v21 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
            *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
            v21[13] = 0;
            v21[14] = pObj22 + v6 + 29;
            v21[15] = 480;
            pObj4 = sub_418DD0(177);  // 调 资源句柄 (101)
            if ( pObj4 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v6 + 29, v7 + 23, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
            sub_488670(dword_79C0B0);  // 调 视口重置 640x480
            if ( dword_8F7C04 != 0 && *(uint8_t *)(dword_8F7C04 + 8052) != 0 )  // dword_8F7C04 = 本地玩家对象
            {
              v23 = *v5;
              v39 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 172);  // nengine::CNSlider 全局实例
              v24 = (*(int (/*thiscall*/ **)(int *))(v23 + 1216))(v5);  // 调用虚函数（虚表槽 +1216）
              v25 = sub_418DD0(v24);  // 调 资源句柄 (101)
              sub_40FC80(v6 + 26, v7 - 3, v25);  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
              pszArg2 = pszArg12 + 772;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
              v39 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
              v26 = sub_4633B0(v5);  // 调 std::string 取数据指针（SSO 判定）
              (*(void (/*cdecl*/ **)(int, int, int, int, int))(v39 + 80))(dword_79C0B0, v6 + 71, v7, -1, v26);  // 调用虚函数（虚表槽 +80）
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
            }
            else
            {
              v39 = *(uint32_t *)(sub_42A410(v44) + 20);  // 调 图标句柄取用（+116 槽）
              pObj2 = sub_42A410(v44);  // 调 图标句柄取用（+116 槽）
              pObj22 = pObj2;
              if ( pObj2 != 0 )
                (*(void (/*thiscall*/ **)(int, unsigned int, int, int))(*(uint32_t *)pObj2 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                  pObj22,
                  v6 - (v39 >> 1) + 43,
                  v7 - 2,
                  dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
              v39 = *(uint32_t *)(sub_42A430(v44) + 20);  // 调 同构 ·0x42A410
              pObj7 = sub_42A430(v44);  // 调 同构 ·0x42A410
              pObj22 = pObj7;
              if ( pObj7 != 0 )
                (*(void (/*thiscall*/ **)(int, unsigned int, int, int))(*(uint32_t *)pObj7 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                  pObj22,
                  v6 - (v39 >> 1) + 43,
                  v7 - 2,
                  dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
              pszArg2 = pszArg12 + 772;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
              if ( (unsigned int)v5[78] < 0x10 )
                v29 = v5 + 73;
              else
                v29 = (int *)v5[73];
              (*(void (/*cdecl*/ **)(int, int, int, int, int *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
                dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
                v6 + 72,
                v7,
                -1,
                v29);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
            }
            v30 = v41;
            sub_4611D0(pszArg12, v41, v6, v7);  // 调 网络延迟三档指示与 Realy 红字
            LOBYTE(v2) = sub_461370(v30, v6, v7 + 50, 2, 33);  // 调 网络统计调试叠字（两行三色）
            v4 = v43;
            v3 = (int)v30;
          }
        }
        v41 = (bool (/*cdecl*/ *)(struct Concurrency::details::_UnrealizedChore *, void *))++v3;
      }
      while ( v3 < 8 );
    }
  }
  return v2;
}


// ------------------------------------------------------------
// 0x466BA0 sub_466BA0 —— 本机血条闪烁与位移动画
// 本机存在且 vt+1064（血量百分比）不为 100 时：byte_9B88BD 置位以 sub_42B420(0,255,250ms) 相位配 27 号图在 (59,395) 闪烁。
// 再 sub_4049C0(21,0,vt+1064-10,90) 得下降相位，在 21..1 间绘 60 号图于 (62, 419-v4)。
// ------------------------------------------------------------
void sub_466BA0()  // 函数: 本机血条闪烁与位移动画
{
  DWORD Time; // eax
  uint8_t v1; // bl
  int pObj2; // eax
  int v3; // eax
  int v4; // esi
  int pObj; // eax
  uint32_t *v6; // eax
  int pObj4; // eax
  int pObj3; // eax

  if ( dword_8F7C04 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1064))(dword_8F7C04) != 100 )  // 调用虚函数（虚表槽 +1064）
  {
    if ( byte_9B88BD != 0 )
    {
      Time = timeGetTime();  // 调 取系统毫秒时刻
      v1 = sub_42B420(0, 255, Time, 250);  // 调 往返插值（三角波）
      sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      pObj2 = sub_418DD0(27);  // 调 资源句柄 (101)
      if ( pObj2 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 调用虚函数（虚表槽 +128）
          pObj2,
          59,
          395,
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          1065353216,  // 常量 1.0f
          1065353216,  // 常量 1.0f
          0,
          (v1 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
    }
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1064))(dword_8F7C04);  // 调用虚函数（虚表槽 +1064）
    v4 = (uint64_t)sub_4049C0(21.0, 0.0, v3 - 10, 90);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
    pObj = sub_418DD0(59);  // 调 资源句柄 (101)
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
        pObj,
        62,
        398,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,  // 常量 1.0f
        1065353216,  // 常量 1.0f
        0,
        -1761607681,
        1333788672,
        1333788672);
    if ( v4 != 0 )
    {
      v6 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
      v6[13] = 423 - v4;
      v6[14] = 640;
      v6[15] = 480;
      pObj4 = sub_418DD0(58);  // 调 资源句柄 (101)
      if ( pObj4 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 62, 398, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      sub_488670(dword_79C0B0);  // 调 视口重置 640x480
    }
    if ( v4 < 21 && v4 > 1 )  // 若 v4 < 21 与/或 v4 > 1
    {
      sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      pObj3 = sub_418DD0(60);  // 调 资源句柄 (101)
      if ( pObj3 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, 62, 419 - v4, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
    }
  }
}



// ------------------------------------------------------------
// 0x466D70 sub_466D70 —— 战场剩余时间数字绘制
// 12 号图铺底；会话 dword_8F7A24+32 对象 +116 取毫秒时间戳，拆 分/秒/百分秒 逐位。
// 数字图号 0..9 落 x=506/522/538/554/602/618，y=366。
// 剩余不超过 15 秒且未播过（+1020）时播 HK1_FIGHT（串自证）并置标志。
// ------------------------------------------------------------
char /*thiscall*/ sub_466D70(int this)  // 函数: 战场剩余时间数字绘制
{
  int pObj2; // eax
  int v2; // ebx
  int v3; // esi
  int pObj3; // eax
  int pObj; // eax
  int pObj8; // eax
  int pObj9; // eax
  int pObj7; // eax
  int pObj4; // eax
  int pObj6; // eax
  int pObj5; // eax
  int v12; // eax
  int fld_3F8; // ecx
  int fld_3F82; // edi
  int v17; // [esp+10h] [ebp-4h]

  pObj2 = sub_418DD0(12);  // 调 资源句柄 (101)
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pObj2 + 152))(pObj2, 0, 0, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  v17 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 116) % 1000;  // dword_8F7A24 = 当前场景状态对象
  v2 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 116) / 1000 % 60;  // dword_8F7A24 = 当前场景状态对象
  v3 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 116) / 60000;  // dword_8F7A24 = 当前场景状态对象
  if ( v3 > 0 )
  {
    if ( v3 > 10 )
    {
      pObj3 = sub_418DD0(v3 / 10);  // 调 资源句柄 (101)
      if ( pObj3 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, 506, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    }
    pObj = sub_418DD0(v3 % 10);  // 调 资源句柄 (101)
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, 522, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj8 = sub_418DD0(10);  // 调 资源句柄 (101)
    if ( pObj8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, 538, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
LABEL_13:
    pObj9 = sub_418DD0(v2 / 10);  // 调 资源句柄 (101)
    if ( pObj9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj9 + 152))(pObj9, 554, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    goto LABEL_15;
  }
  if ( v2 > 0 )
  {
    if ( v2 >= 10 )
      goto LABEL_13;
LABEL_15:
    pObj7 = sub_418DD0(v2 % 10);  // 调 资源句柄 (101)
    if ( pObj7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, 570, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj4 = sub_418DD0(11);  // 调 资源句柄 (101)
    if ( pObj4 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 586, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  }
  pObj6 = sub_418DD0(v17 / 100);  // 调 资源句柄 (101)
  if ( pObj6 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, 602, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  pObj5 = sub_418DD0(v17 / 10 % 10);  // 调 资源句柄 (101)
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, 618, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  v12 = *(uint32_t *)(dword_8F7A24 + 32);  // dword_8F7A24 = 当前场景状态对象
  if ( *(uint32_t *)(v12 + 36) == 2 )
  {
    fld_3F8 = *(uint32_t *)(this + 1016);  // this+1016〔uGrabB1016(推断)〕
    LOBYTE(v12) = *(uint8_t *)(fld_3F8 + 170);  // 调 取 16 位值低 8 位
    if ( (uint8_t)v12 == 0 )
    {
      sub_4938F0(fld_3F8);  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      sub_491D00(dword_79C0B0, 320, 240, 0.0);  // 调 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      fld_3F82 = *(uint32_t *)(*(uint32_t *)(this + 1016) + 148);  // this+1016〔uGrabB1016(推断)〕
      if ( *(uint8_t *)(this + 1023) == 0 && fld_3F82 >= 3 )  // fld_3F82=this+1016 uGrabB1016
      {
        sub_432EA0("HK1_COUNT_3", -1, 0, 0);  // 调 音效播放包装（非空判定）
        *(uint8_t *)(this + 1023) = 1;
      }
      if ( *(uint8_t *)(this + 1022) == 0 && fld_3F82 >= 7 )  // fld_3F82=this+1016 uGrabB1016
      {
        sub_432EA0("HK1_COUNT_2", -1, 0, 0);  // 调 音效播放包装（非空判定）
        *(uint8_t *)(this + 1022) = 1;
      }
      if ( *(uint8_t *)(this + 1021) == 0 && fld_3F82 >= 11 )  // fld_3F82=this+1016 uGrabB1016
      {
        sub_432EA0("HK1_COUNT_1", -1, 0, 0);  // 调 音效播放包装（非空判定）
        *(uint8_t *)(this + 1021) = 1;
      }
      LOBYTE(v12) = *(uint8_t *)(this + 1020);  // 调 取 16 位值低 8 位
      if ( (uint8_t)v12 == 0 && fld_3F82 >= 15 )  // fld_3F82=this+1016 uGrabB1016
      {
        LOBYTE(v12) = (uint8_t)sub_432EA0("HK1_FIGHT", -1, 0, 0);  // 调 音效播放包装（非空判定）
        *(uint8_t *)(this + 1020) = 1;  // this+1020〔pAnimHandleArr(推断)〕
      }
    }
  }
  return v12;
}



// ------------------------------------------------------------
// 0x4670A0 sub_4670A0 —— 与 ·sub_466D70 同构（差异：10 秒倒数）
// 时基改为 10000 减 clock_now(会话 dword_8F7A24+40 的 +36)，且无 HK1_FIGHT 提示分支。
// ------------------------------------------------------------
int sub_4670A0()  // 函数: 与 ·sub_466D70 同构（差异：10 秒倒数）
{
  int result; // eax
  int v1; // ecx
  int v2; // ebx
  int v3; // esi
  int pObj2; // eax
  int pObj; // eax
  int pObj6; // eax
  int pObj7; // eax
  int pObj5; // eax
  int pObj3; // eax
  int pObj4; // eax
  int v11; // [esp+0h] [ebp-4h]

  result = sub_699000(*(uint32_t *)(dword_8F7A24 + 40) + 36);  // dword_8F7A24 = 当前场景状态对象
  v1 = 10000 - result;
  if ( 10000 - result < 0 )
    return result;
  v11 = v1 % 1000;
  v2 = v1 / 1000 % 60;
  v3 = v1 / 60000;
  if ( v1 / 60000 > 0 )
  {
    if ( v3 > 10 )
    {
      pObj2 = sub_418DD0(v3 / 10);  // 调 资源句柄 (101)
      if ( pObj2 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, 506, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    }
    pObj = sub_418DD0(v3 % 10);  // 调 资源句柄 (101)
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, 522, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj6 = sub_418DD0(10);  // 调 资源句柄 (101)
    if ( pObj6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, 538, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    goto LABEL_12;
  }
  if ( v2 > 0 )
  {
    if ( v2 < 10 )
    {
LABEL_14:
      pObj5 = sub_418DD0(v2 % 10);  // 调 资源句柄 (101)
      if ( pObj5 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, 570, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      pObj3 = sub_418DD0(11);  // 调 资源句柄 (101)
      if ( pObj3 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, 586, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      goto LABEL_18;
    }
LABEL_12:
    pObj7 = sub_418DD0(v2 / 10);  // 调 资源句柄 (101)
    if ( pObj7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, 554, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    goto LABEL_14;
  }
LABEL_18:
  pObj4 = sub_418DD0(v11 / 100);  // 调 资源句柄 (101)
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 602, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  result = sub_418DD0(v11 / 10 % 10);  // 调 资源句柄 (101)
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(result, 618, 366, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  return result;
}



// ------------------------------------------------------------
// 0x4672C0 sub_4672C0 —— 底栏座位/排行条绘制
// 会话链 dword_8F7A24+40 到 +16 到 +108 非空时设裁剪窗 (0,0,640,24)，2 号图置 (438,0)。
// sub_488670 复位视口后 sub_48FE30(dword_99FF08) 组显示串在 (480,6) 以 -5783092 上屏。
// sub_48FCA0/48FD60/48FD70 取自身座位下标与字段，11 号图 (573,28)，再循环 4 格（x 步进 32 至 326）逐格画位图。
// ------------------------------------------------------------
char /*thiscall*/ sub_4672C0(int this)  // 函数: 底栏座位/排行条绘制
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  uint32_t *v5; // eax
  int pObj3; // eax
  int v7; // ebx
  int v8; // eax
  int pObj2; // eax
  int fld_508; // edi
  int v11; // edi
  int pObj4; // eax
  int v13; // ebx
  int pThis_57C; // eax
  int pThis_57C2; // ecx
  double v16; // st7
  int pObj; // eax
  int fld_594; // ebx
  uint32_t *v19; // eax
  int v20; // ebx
  int v21; // edi
  int v22; // eax
  unsigned int v23; // ecx
  int v24; // eax
  int v25; // eax
  int v27; // [esp-8h] [ebp-1Ch]
  int pThis_57C3; // [esp-8h] [ebp-1Ch]
  int Value; // [esp+10h] [ebp-4h]
  int Valuea; // [esp+10h] [ebp-4h]

  v2 = sub_48FCA0();  // 调 自身座位下标查找（表 dword_99FF08）
  v3 = sub_48FD60(v2);  // 调 槽字段读取（+80 起）
  v4 = sub_48FCA0();  // 调 自身座位下标查找（表 dword_99FF08）
  Value = sub_48FD70(v4);  // 调 槽字段读取·第二组（基址 +112）
  if ( *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 108) != 0 )  // dword_8F7A24 = 当前场景状态对象
  {
    v5 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
    v5[13] = 0;
    v5[14] = 640;
    v5[15] = 24;
    pObj3 = sub_418DD0(2);  // 调 资源句柄 (101)
    if ( pObj3 != 0 )
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)pObj3 + 152))(pObj3, 438, 0, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    sub_488670(dword_79C0B0);  // 调 视口重置 640x480
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 912);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    v7 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    v8 = sub_48FE30(dword_99FF08);  // 调 组装显示串（串表名 + 表项串 #编号）
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v7 + 80))(dword_79C0B0, 480, 6, -5783092, v8);  // 调用虚函数（虚表槽 +80）
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  }
  pObj2 = sub_418DD0(11);  // 调 资源句柄 (101)
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, 573, 28, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  sub_69A110(*(uint32_t *)(this + 1288), 566, 38, v3, -1);
  fld_508 = 566 - sub_699FC0(*(uint32_t *)(this + 1288), v3);
  v11 = fld_508 - *(uint32_t *)(sub_418DD0(53) + 20);  // 调 资源句柄 (101)
  pObj4 = sub_418DD0(53);  // 调 资源句柄 (101)
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v11 + 4, 32, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  sub_69A110(*(uint32_t *)(this + 1284), v11, 28, Value, -1);  // this+1284〔nEffectCount1284〕
  if ( *(uint8_t *)(this + 1416) != 0 )
  {
    v13 = 255;
    pThis_57C = sub_699000(this + 1404);  // clock_now(clk)
    pThis_57C2 = this + 1404;
    if ( pThis_57C > 200 )
    {
      if ( sub_699000(pThis_57C2) < 2200 )  // clock_now(clk)
      {
LABEL_15:
        pObj = sub_418DD0(77);  // 调 资源句柄 (101)
        if ( pObj != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调用虚函数（虚表槽 +128）
            pObj,
            220,
            99,
            dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
            1065353216,  // 常量 1.0f
            1065353216,  // 常量 1.0f
            0,
            ((uint8_t)v13 << 24) | 0xFFFFFF,
            1333788672,
            1333788672);
        if ( *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 104) != 0 )  // dword_8F7A24 = 当前场景状态对象
          sub_69A110(
            *(uint32_t *)(this + 1292),  // this+1292〔pAnimRow1292〕
            372,
            99,
            *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 128) - *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 132),  // dword_8F7A24 = 当前场景状态对象
            v13);
        fld_594 = *(uint32_t *)(this + 1428);
        if ( sub_699000(this + 1404) >= fld_594 )  // clock_now(clk)
          *(uint8_t *)(this + 1416) = 0;
        goto LABEL_21;
      }
      pThis_57C3 = sub_699000(this + 1404);  // clock_now(clk)
      v16 = sub_4049C0(255.0, 0.0, pThis_57C3, 2600);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
    }
    else
    {
      v27 = sub_699000(pThis_57C2);  // clock_now(clk)
      v16 = sub_4049C0(0.0, 255.0, v27, 200);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
    }
    v13 = (uint64_t)v16;
    goto LABEL_15;
  }
LABEL_21:
  LOBYTE(v19) = *(uint8_t *)(this + 508);  // 调 取 16 位值低 8 位
  if ( (uint8_t)v19 != 0 )
  {
    LOBYTE(v19) = dword_99FF08;  // 调 取 16 位值低 8 位
    if ( dword_99FF08 != 0 )
    {
      v20 = 0;
      v19 = (uint32_t *)(dword_99FF08 + 8);
      v21 = 70;
      Valuea = dword_99FF08 + 8;
      do
      {
        if ( *v19 != 255 )
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 912);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
          v22 = sub_578E80(v20);  // 调 存 调: sub_578E80 sub_48F660
          v23 = *(uint32_t *)(v22 + 40);
          v24 = v22 + 16;
          if ( v23 < 0x10 )
            v25 = v24 + 4;
          else
            v25 = *(uint32_t *)(v24 + 4);
          (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 100, v21, -1, v25);  // 调用虚函数（虚表槽 +80）
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
          sub_461370(v20, 300, v21, 0, 0);  // 调 网络统计调试叠字（两行三色）
        }
        v19 = (uint32_t *)(Valuea + 4);
        v21 += 32;
        ++v20;
        Valuea += 4;  // Valuea 前进 4
      }
      while ( v21 < 326 );
    }
  }
  return (char)v19;
}


// ------------------------------------------------------------
// 0x467600 sub_467600 —— 36 字节网格坐标换算
// 返回 dword_99FBB4 + 36*(pArg2 + nArg3 * 表宽)，表宽取自 this[42] 的第 dword_99FB78 项 +8。
// ------------------------------------------------------------
int /*thiscall*/ sub_467600(uint32_t *this, int pArg2, int nArg3)  // 函数: 36 字节网格坐标换算
{
  return dword_99FBB4 + 36 * (pArg2 + nArg3 * *(uint32_t *)(*(this + 42) + 8 * dword_99FB78));  // this+168〔pAppendVec(推断)〕
}



// ------------------------------------------------------------
// 0x467630 sub_467630 —— 实体状态调试文本绘制
// 取会话 dword_8F7A24+28 的 +16 实体表（+44/+104 双非空门控），sub_416D10/416CD0 建 DIB。
// sub_422E70(236) 取格式串 %s: X%d Y%d, %s, STATE %d ,AISTATE %d（自证），从 dword_99FBB4 网格取数据 sprintf 到 (100, 10*行+126)。
// 收尾 ho 非空则 DeleteObject 释放。
// ------------------------------------------------------------
uint32_t *sub_467630()  // 调 实体状态调试文本绘制
{
  uint32_t *result; // eax
  int v1; // esi
  const char *v2; // eax
  int v3; // edi
  int v4; // ecx
  int v5; // ebx
  int v6; // ecx
  unsigned int v7; // edx
  int v8; // edi
  int v9; // ecx
  uint32_t *v10; // eax
  char *v11; // eax
  char *pObj; // esi
  int v13; // eax
  unsigned int v14; // ecx
  const char *v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // esi
  const char *v20; // eax
  int v21; // [esp-14h] [ebp-38Ch]
  const char *v22; // [esp-10h] [ebp-388h]
  int v23; // [esp-Ch] [ebp-384h]
  int v24; // [esp-8h] [ebp-380h]
  int v25; // [esp-8h] [ebp-380h]
  int v26; // [esp-8h] [ebp-380h]
  uint8_t v27[44]; // [esp+8h] [ebp-370h] BYREF
  HGDIOBJ ho; // [esp+34h] [ebp-344h]
  int dword_99FCCC2; // [esp+38h] [ebp-340h]
  int v30; // [esp+3Ch] [ebp-33Ch] BYREF
  int v31; // [esp+40h] [ebp-338h] BYREF
  int v32; // [esp+44h] [ebp-334h] BYREF
  int v33; // [esp+48h] [ebp-330h]
  int v34; // [esp+4Ch] [ebp-32Ch] BYREF
  int v35; // [esp+50h] [ebp-328h] BYREF
  int v36; // [esp+54h] [ebp-324h]
  int v37; // [esp+58h] [ebp-320h]
  int v38; // [esp+5Ch] [ebp-31Ch]
  unsigned int v39; // [esp+60h] [ebp-318h]
  int v40; // [esp+64h] [ebp-314h]
  char v41[256]; // [esp+68h] [ebp-310h] BYREF
  char Buffer[512]; // [esp+168h] [ebp-210h] BYREF
  int dword_796E502; // [esp+368h] [ebp-10h]
  int v44; // [esp+374h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  result = *(uint32_t **)(dword_8F7A24 + 28);  // dword_8F7A24 = 当前场景状态对象
  v1 = result[4];
  if ( v1 != 0 && *(uint32_t *)(v1 + 44) != 0 && *(uint32_t *)(v1 + 104) != 0 )
  {
    sub_416D10(v27);  // 调 绘制状态结构初始化（void 版）
    v44 = 0;
    sub_416CD0(v27);  // 调 绘制状态结构初始化（返回 0）
    dword_99FCCC2 = dword_99FCCC;  // dword_99FCCC＝与字距
    (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, v27);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    v24 = **(uint32_t **)(v1 + 44);
    v2 = (const char *)sub_422E70(236);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v2, v24);  // 调 格式化到缓冲
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 100, 100, -1, Buffer);  // 调用虚函数（虚表槽 +80）
    v3 = *(uint32_t *)(v1 + 112);
    v4 = *(uint32_t *)(dword_99FBB4
                   + 36
                   * (v3
                    + *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(v1 + 108) + 168) + 8 * dword_99FB78) * *(uint32_t *)(v1 + 116))  // 实体状态调试文本绘制
                   + 8);
    if ( v4 != 0 )
      v36 = (*(uint32_t *)(dword_99FBB4
                       + 36
                       * (v3
                        + *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(v1 + 108) + 168) + 8 * dword_99FB78)
                        * *(uint32_t *)(v1 + 116))
                       + 12)
           - v4)
          / 28;
    else
      v36 = 0;
    v5 = *(uint32_t *)(v1 + 104);
    v6 = *(uint32_t *)(v5 + 120);
    v7 = 0;
    v8 = 0;
    v33 = v5;
    if ( v6 != 0 )
      v40 = (*(uint32_t *)(v5 + 124) - v6) >> 2;
    else
      v40 = 0;
    v39 = 0;
    if ( v40 > 0 )
    {
      v38 = 114;
      while ( 1 )  // 无限循环
      {
        v9 = *(uint32_t *)(v5 + 120);
        if ( v9 != 0 && v7 < (*(uint32_t *)(v5 + 124) - v9) >> 2 )
          v10 = *(uint32_t **)(v9 + 4 * v7);
        else
          v10 = nullptr;
        v11 = __RTDynamicCast(v10, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
        pObj = v11;
        if ( v11 != nullptr )  // 若 v11 有效（非空）
        {
          if ( v11[7801] != 0 )
            v13 = sub_422E70(237);  // 调 存 CStringManager::getStr 取本地化串
          else
            v13 = sub_422E70(238);  // 调 存 CStringManager::getStr 取本地化串
          v14 = *((uint32_t *)pObj + 78);
          v37 = v13;
          if ( v14 < 0x10 )
            v15 = pObj + 292;
          else
            v15 = *((const char **)pObj + 73);
          v16 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pObj + 840))(pObj, *((uint32_t *)pObj + 1787));  // 调用虚函数（虚表槽 +840）【推断: [RTTI: IRDActiveObject__vmt348 ·…】
          v17 = (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)pObj + 124))(pObj, v37, v16);  // 调用虚函数（虚表槽 +124）
          v18 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)pObj + 120))(pObj, v17);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
          sprintf(Buffer, "%s: X%d Y%d, %s, STATE %d ,AISTATE %d", v15, v18, v21, v22, v23, v25);  // 调 格式化到缓冲
          v19 = v38;
          (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
            dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
            100,
            v38,
            -1,
            Buffer);
          v5 = v33;
          ++v8;
          v38 = v19 + 14;
        }
        if ( (int)++v39 >= v40 )
          break;
        v7 = v39;
      }
    }
    v26 = v36;
    v20 = (const char *)sub_422E70(239);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v20, v8, v26);  // 调 格式化到缓冲
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
      dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
      100,
      2 * (5 * v8 + 250),
      -1,
      Buffer);
    v34 = 0;
    v35 = 0;
    sub_65DB10((int)lpCriticalSection, &v34, &v35, &v32, v41, &v31, &v30);  // 调 汇总播放统计（活动通道与 FSOUND 通道数）
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
      dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
      100,
      10 * v8 + 126,
      -1,
      Buffer);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    result = ho;
    if ( ho != nullptr )  // 若 ho 有效（非空）
      return (uint32_t *)DeleteObject(ho);  // 调 删除 GDI 对象
  }
  return result;
}


// ------------------------------------------------------------
// 0x467980 sub_467980 —— 小地图/雷达格网与标记
// v2 为会话 +16，v3 为 v2[27] 地图对象，其 +68 为地图位图；v2[26]+152 为 0 且 sub_423AE0(v2[28],v2[29]) 为 0 时置闪烁标志。
// sub_418DD0(dword_99FCC8 上下文 +84 图容器) 取 0/1 两图落 (546,34)。
// 再按 v3 各字段与 ·sub_460DC0 方图号、·sub_4617A0 称号串铺格与标记。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_467980(uint8_t *this)  // 函数: 小地图/雷达格网与标记
{
  uint32_t *result; // eax
  int *v2; // esi
  int v3; // edi
  int pObj; // eax
  uint32_t *v5; // eax
  int v6; // ecx
  int v7; // esi
  int v8; // edi
  int v9; // ebx
  int v10; // eax
  uint32_t *v11; // ecx
  int *v12; // edi
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int v16; // edi
  uint32_t *v17; // eax
  uint8_t *v18; // ebx
  int pObj11; // eax
  bool v20; // al
  int pObj6; // eax
  int pObj7; // eax
  int v23; // ebx
  int v24; // eax
  int pObj10; // eax
  int pThis_468; // eax
  uint64_t v27; // rax
  int pObj12; // eax
  int pObj9; // eax
  DWORD dwNow2; // edx
  double v31; // st7
  int pObj3; // eax
  int pObj4; // eax
  int pObj2; // eax
  int pObj5; // eax
  int v36; // [esp+8h] [ebp-2Ch]
  int v38; // [esp+10h] [ebp-24h]
  int v39; // [esp+10h] [ebp-24h]
  int pObj8; // [esp+14h] [ebp-20h]
  int v41; // [esp+14h] [ebp-20h]
  int v42; // [esp+18h] [ebp-1Ch]
  int v43; // [esp+1Ch] [ebp-18h]
  int v44; // [esp+20h] [ebp-14h]
  int v45; // [esp+20h] [ebp-14h]
  char v46; // [esp+24h] [ebp-10h]
  int v47; // [esp+28h] [ebp-Ch]
  int *v48; // [esp+2Ch] [ebp-8h]
  uint8_t v49; // [esp+31h] [ebp-3h]
  char dwNow; // [esp+32h] [ebp-2h]
  char v51; // [esp+33h] [ebp-1h]

  result = (uint32_t *)dword_8F7A24;  // dword_8F7A24 = 当前场景状态对象
  v2 = *(int **)(*(uint32_t *)(dword_8F7A24 + 28) + 16);  // dword_8F7A24 = 当前场景状态对象
  v3 = v2[27];
  v48 = v2;
  v47 = v3;
  if ( v3 == 0 )
    return result;
  result = *(uint32_t **)(v3 + 68);
  if ( result == nullptr )  // 若 result 为空
    return result;
  v51 = 0;
  dwNow = 0;
  if ( *(uint8_t *)(v2[26] + 152) == 0 && (uint8_t)sub_423AE0(v2[28], v2[29]) == 0 )  // 调 选中格同判
  {
    v51 = 1;
    dwNow = ((timeGetTime() / 0xFA) & 1) == 0;  // 调 取系统毫秒时刻
  }
  v36 = *(uint32_t *)(v3 + 68);
  pObj8 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 0);  // 调 资源句柄 (101)
  pObj = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 1u);  // 调 资源句柄 (101)
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, 546, 34, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  v5 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
  v6 = 0;
  *(uint32_t *)(dword_79C0B0 + 48) = 546;  // dword_79C0B0 = 文本/图像绘制对象
  v5[13] = 34;
  v5[14] = 620;
  v5[15] = 108;
  v38 = 0;
  v44 = 536;
  while ( 1 )  // 无限循环
  {
    v7 = v6 + v2[28] - 2;
    if ( v7 >= 0 && v7 < *(uint32_t *)(*(uint32_t *)(v3 + 168) + 8 * dword_99FB78) )
    {
      v8 = 0;
      v9 = 22;
      do
      {
        v10 = v48[29] + v8 - 2;
        if ( v10 >= 0 )
        {
          v11 = (uint32_t *)(*(uint32_t *)(v47 + 168) + 8 * dword_99FB78);
          if ( v10 < v11[1]
            && (*(uint32_t *)(dword_99FBC4 + 4 * (v7 + v10 * *v11)) != 0 || v51 != 0 && sub_48C440(v48[11], v7, v10))  // 调 相邻方向码换算并查可动
            && pObj8 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, v44, v9, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          }
        }
        ++v8;
        v9 += 18;
      }
      while ( v8 < 5 );
      v6 = v38;
    }
    v38 = ++v6;
    v44 += 18;
    if ( v6 >= 5 )
      break;
    v2 = v48;
    v3 = v47;
  }
  v12 = v48;
  v13 = 0;
  v41 = 0;
  v39 = 538;
  do
  {
    v14 = v13 + v12[28] - 2;
    v45 = v14;
    if ( v14 >= 0 && v14 < *(uint32_t *)(*(uint32_t *)(v47 + 168) + 8 * dword_99FB78) )
    {
      v15 = 0;
      v43 = 0;
      v42 = 24;
      while ( 1 )  // 无限循环
      {
        v16 = v12[29] + v15 - 2;
        if ( v16 >= 0 )
        {
          v17 = (uint32_t *)(*(uint32_t *)(v47 + 168) + 8 * dword_99FB78);
          if ( v16 >= v17[1] )
            goto LABEL_43;
          v18 = *(uint8_t **)(dword_99FBC4 + 4 * (v14 + v16 * *v17));
          v46 = 0;
          if ( v18 != nullptr )  // 若 v18 有效（非空）
            break;
          if ( v51 != 0 )
          {
            if ( sub_48C440(v48[11], v14, v16) )  // 调 相邻方向码换算并查可动
            {
              pObj11 = sub_460DC0(0, 0, dwNow, v36);  // 调 【推断】图标序号合成取句柄
              goto LABEL_40;
            }
            goto LABEL_42;
          }
        }
LABEL_43:
        v12 = v48;
        v43 = ++v15;
        v42 += 18;
        if ( v15 >= 5 )
        {
          v13 = v41;
          goto LABEL_45;
        }
      }
      v49 = v18[396];
      if ( v41 == 2 )
        v46 = v15 == 2;
      if ( v51 != 0 && dwNow != 0 )  // 若 v51 != 0 与/或 dwNow != 0
      {
        v20 = sub_48C440(v48[11], v14, v16);  // 调 相邻方向码换算并查可动
        LOBYTE(v14) = v45;  // 调 取 16 位值低 8 位
        if ( v20 )
          v46 = 1;
      }
      pObj11 = sub_460DC0(v49, v14 * v16 * *v18, v46, v36);  // 调 【推断】图标序号合成取句柄
LABEL_40:
      if ( pObj11 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj11 + 152))(pObj11, v39, v42, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
LABEL_42:
      v14 = v45;
      v15 = v43;
      goto LABEL_43;
    }
LABEL_45:
    v41 = ++v13;
    v39 += 18;
  }
  while ( v13 < 5 );
  sub_488670((uint32_t *)dword_79C0B0);  // 调 视口重置 640x480
  pObj6 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 2u);  // 调 资源句柄 (101)
  if ( pObj6 != 0 )
    (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)pObj6 + 152))(pObj6, 438, 0, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  pObj7 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 3u);  // 调 资源句柄 (101)
  if ( pObj7 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, 580, 63, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 912);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
  v23 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
  v24 = sub_4617A0(dword_99FB8C);  // 调 称号路阶文本拼接
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(v23 + 80))(dword_79C0B0, 480, 6, -5783092, v24);  // 调用虚函数（虚表槽 +80）
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  if ( *(int *)dword_99FB70 > 0 )
  {
    pObj10 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 4u);  // 调 资源句柄 (101)
    if ( pObj10 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj10 + 152))(pObj10, 526, 24, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    if ( *(int *)dword_99FB70 < 10 )
      sub_69A110(570, 29, *(int *)dword_99FB70, -1);
    else
      sub_69A110(574, 29, *(int *)dword_99FB70, -1);
    if ( *(this + 1140) != 0 )
    {
      pThis_468 = sub_699000((int)(this + 1128));  // clock_now(clk)
      v27 = (uint64_t)sub_4049C0(0.0, 9.0, pThis_468, 330);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
      if ( (int)v27 < 9 )
      {
        pObj12 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 152), v27);  // 调 资源句柄 (101)
        if ( pObj12 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj12 + 152))(pObj12, 436, -111, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      }
      else
      {
        *(this + 1140) = 0;
      }
    }
  }
  result = *(uint32_t **)(dword_99FBC4 + 4 * (v12[28] + *(uint32_t *)(*(uint32_t *)(v47 + 168) + 8 * dword_99FB78) * v12[29]));
  if ( result != nullptr && result[1] != 4 )
  {
    pObj9 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 0xFu);  // 调 资源句柄 (101)
    if ( pObj9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj9 + 152))(pObj9, 538, 92, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    dwNow2 = timeGetTime() % 0x320;  // 调 取系统毫秒时刻
    if ( dwNow2 > 0x190 )
      v31 = sub_4049C0(255.0, 50.0, dwNow2, 800);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
    else
      v31 = sub_4049C0(50.0, 255.0, dwNow2, 400);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
    result = *(uint32_t **)(*(uint32_t *)(dword_99FBC4
                                    + 4 * (v48[28] + v48[29] * *(uint32_t *)(*(uint32_t *)(v47 + 168) + 8 * dword_99FB78)))  // 小地图/雷达格网与标记
                        + 4);
    switch ( (unsigned int)result )  // 按 (unsigned int)result 分派
    {
      case 0u:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        pObj3 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 0x10u);  // 调 资源句柄 (101)
        if ( pObj3 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, 541, 95, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        result = (uint32_t *)sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 0x11u);  // 调 资源句柄 (101)
        goto LABEL_81;
      case 1u:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        pObj4 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 0x12u);  // 调 资源句柄 (101)
        if ( pObj4 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 541, 95, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        result = (uint32_t *)sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 0x13u);  // 调 资源句柄 (101)
        goto LABEL_81;
      case 2u:  // case 2 = ENUM_CMDPACKET_LOGIN
        pObj2 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 0x16u);  // 调 资源句柄 (101)
        if ( pObj2 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, 541, 95, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        result = (uint32_t *)sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 0x17u);  // 调 资源句柄 (101)
        goto LABEL_81;
      case 3u:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        pObj5 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 0x14u);  // 调 资源句柄 (101)
        if ( pObj5 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, 541, 95, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        result = (uint32_t *)sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 84), 0x15u);  // 调 资源句柄 (101)
LABEL_81:
        if ( result != nullptr )  // 若 result 有效（非空）
          result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, int, int, int, uint32_t, int, int, int))(*result + 128))(  // 调用虚函数（虚表槽 +128）
                               result,
                               541,
                               95,
                               dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
                               1065353216,  // 常量 1.0f
                               1065353216,  // 常量 1.0f
                               0,
                               ((uint8_t)(uint64_t)v31 << 24) | 0xFFFFFF,
                               1333788672,
                               1333788672);
        break;
      default:
        return result;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x468090 sub_468090 —— map/set 红黑树插入重平衡
// 元素数达 0x1FFFFFFE 时抛 std::length_error（串 map/set<T> too long 自证）。
// sub_5648C0 建节点后按 pszArg3 方向与 nArg5 挂到 pDwArg4，再自底向上旋转与变色。
// 结果节点经 *pDwArg2 回传。
// ------------------------------------------------------------
int */*thiscall*/ sub_468090(int **this, int *pDwArg2, char pszArg3, int *pDwArg4, int nArg5)  // 函数: map/set 红黑树插入重平衡
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

  if ( (unsigned int)*(this + 2) >= 0x1FFFFFFE )  // this+8 = 技能槽记录首字
  {
    v19 = 15;
    v18 = 0;
    v17[4] = 0;
    sub_4015C0("map/set<T> too long", 0x13u);  // 调 std::string 构造赋值（从 [Src, Src+Size) 拷贝）
    v20 = 0;
    sub_401740(v17);  // 调 std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消…
    pExceptionObject = &std::length_error::`vftable';  // vftable 复位
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常
  }
  fld_e1 = sub_5648C0(*(this + 1), pDwArg4, *(this + 1), nArg5, 0);  // 调 商店文本（23 行）
  fld_e12 = *(this + 1);  // this+4 = pHostObj
  fld_e15 = fld_e1;
  *(this + 2) = (int *)((char *)*(this + 2) + 1);  // this+8 = 技能槽记录首字
  if ( pDwArg4 == fld_e12 )  // fld_e12=this+4 宿主对象
  {
    fld_e12[1] = fld_e1;  // fld_e12=this+4 宿主对象
    **(this + 1) = fld_e1;  // this+4 = pHostObj
    (*(this + 1))[2] = fld_e1;  // this+4 = pHostObj
  }
  else if ( pszArg3 != 0 )
  {
    *pDwArg4 = fld_e1;
    fld_e13 = *(this + 1);  // this+4 = pHostObj
    if ( pDwArg4 == (int *)*fld_e13 )  // fld_e13=this+4 宿主对象
      *fld_e13 = fld_e1;  // fld_e13=this+4 宿主对象
  }
  else
  {
    pDwArg4[2] = fld_e1;
    fld_e14 = (int)*(this + 1);  // this+4 = pHostObj
    if ( pDwArg4 == *(int **)(fld_e14 + 8) )  // fld_e14=this+4 宿主对象
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // fld_e14=this+4 宿主对象
  }
  v10 = (int *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 20) == 0 )
  {
    while ( 1 )  // 无限循环
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
            sub_433130(this, *v10);  // 调 红黑树左旋（节点 0x18 版）
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(this, *(uint32_t **)(*(uint32_t *)(fld_e16 + 4) + 4));  // 调 STL 内联红黑树节点摘除重连
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(this, (uint32_t *)*v10);  // 调 STL 内联红黑树节点摘除重连
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(this, *(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // 调 红黑树左旋（节点 0x18 版）
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
  *(uint8_t *)((*(this + 1))[1] + 20) = 1;  // this+4 = pHostObj
  *pDwArg2 = fld_e1;
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x468240 sub_468240 —— list 元素数预留（溢出抛错）
// 上限 0x1FFFFFFF 减现有值小于 uArg2 时抛 std::length_error（串 list<T> too long 自证）。
// 否则把 this+2 的计数加 uArg2。
// ------------------------------------------------------------
int /*thiscall*/ sub_468240(uint32_t *this, unsigned int uArg2)  // 函数: list 元素数预留（溢出抛错）
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // this+8 = 技能槽记录首字
  if ( 0x1FFFFFFF - fld_e2 < uArg2 )  // fld_e2=this+8 物品 id
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 调 std::string 构造赋值（从 [Src, Src+Size) 拷贝）
    v8 = 0;
    sub_401740(v5);  // 调 std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消…
    pExceptionObject = &std::length_error::`vftable';  // vftable 复位
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // this+8 = 技能槽记录首字
  return result;
}



// ------------------------------------------------------------
// 0x4682D0 sub_4682D0 —— map 插入定位与新增标志
// 自 _Myhead[1] 下探，按 key 大小走左或右找插入点 fld_e1，v7 记是否右侧。
// 命中相等键仅写 (*pArg2,+4)=0，否则调 ·sub_468090 真正插入并写 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4682D0(int **this, int pArg2, int *pDwArg3)  // 函数: map 插入定位与新增标志
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
  fld_e1 = *(this + 1);  // this+4 = pHostObj
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
        v6 = *(uint32_t *)(v6 + 8);
      else
        v6 = *(uint32_t *)v6;
    }
    while ( *(uint8_t *)(v6 + 21) == 0 );
  }
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  pDwArg3 = fld_e1;  // fld_e1=this+4 宿主对象
  if ( v7 )
  {
    if ( fld_e1 == (int *)**(this + 1) )  // this+4 = pHostObj
    {
      v10 = *sub_468090(this, (int *)&pDwArg3, 1, fld_e1, (int)pDwArg32);  // 调 map/set 红黑树插入重平衡
      *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
      *(uint32_t *)pArg2 = v10;  // *pArg2 = v10
      return pArg2;
    }
    sub_4A3B30(&pDwArg3);  // 调 取后继再插
    fld_e12 = pDwArg3;
  }
  if ( fld_e12[3] >= *pDwArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // pArg2+4〔宿主对象〕
    *(uint32_t *)pArg2 = fld_e12;  // *pArg2 = fld_e12
    return pArg2;
  }
  else
  {
    v12 = *sub_468090(this, (int *)&pDwArg3, v13, fld_e1, (int)pDwArg32);  // 调 map/set 红黑树插入重平衡
    *(uint32_t *)pArg2 = v12;  // *pArg2 = v12
    *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x468390 sub_468390 —— map 插入（边界与前驱后继判定）
// 空树先建头节点；pDwArg3 等于 _Myhead 且新键更小于根则左插、更大于最右（_Myhead[2]）则右插。
// 否则以 sub_4A3B30 求前驱、sub_41C5E0 求后继（等价即替换）。
// 末按位置以 ·sub_468090(方向) 落子树并维持红黑平衡。
// ------------------------------------------------------------
int */*thiscall*/ sub_468390(int this, int *pDwArg2, int *pDwArg3, int *pDwArg4)  // 函数: map 插入（边界与前驱后继判定）
{
  int *fld_4; // eax
  int *pDwArg42; // esi
  int *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )  // this+8〔nSkillRec8(推断)〕等 2 字段
  {
    sub_468090((int **)this, pDwArg2, 1, *(int **)(this + 4), (int)pDwArg4);  // 调 map/set 红黑树插入重平衡
    return pDwArg2;
  }
  fld_4 = *(int **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  pDwArg42 = pDwArg4;
  if ( pDwArg3 == (int *)*fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    if ( *pDwArg4 < pDwArg3[3] )
    {
      sub_468090((int **)this, pDwArg2, 1, pDwArg3, (int)pDwArg4);  // 调 map/set 红黑树插入重平衡
      return pDwArg2;
    }
    goto LABEL_22;
  }
  if ( pDwArg3 == fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    v8 = (int *)fld_4[2];  // fld_4=this+16 nChannelTypeSel
    if ( v8[3] < *pDwArg4 )
    {
      sub_468090((int **)this, pDwArg2, 0, v8, (int)pDwArg4);  // 调 map/set 红黑树插入重平衡
      return pDwArg2;
    }
    goto LABEL_22;
  }
  if ( *pDwArg4 >= pDwArg3[3] || (pDwArg4 = pDwArg3, sub_4A3B30(&pDwArg4), pDwArg4[3] >= *pDwArg42) )  // 若 pDwArg4 = pDwArg3
  {
    if ( pDwArg3[3] >= *pDwArg42 || (pDwArg4 = pDwArg3, sub_41C5E0(&pDwArg4), pDwArg4 != *(int **)(this + 4)) && *pDwArg42 >= pDwArg4[3] )  // 调 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4682D0((int **)this, (int)v10, pDwArg42);  // 调 map 插入定位与新增标志
      *pDwArg2 = v9;
      return pDwArg2;
    }
    if ( *(uint8_t *)(pDwArg3[2] + 21) != 0 )
      sub_468090((int **)this, pDwArg2, 0, pDwArg3, (int)pDwArg42);  // 调 map/set 红黑树插入重平衡
    else
      sub_468090((int **)this, pDwArg2, 1, pDwArg4, (int)pDwArg42);  // 调 map/set 红黑树插入重平衡
    return pDwArg2;
  }
  else
  {
    if ( *(uint8_t *)(pDwArg4[2] + 21) != 0 )
      sub_468090((int **)this, pDwArg2, 0, pDwArg4, (int)pDwArg42);  // 调 map/set 红黑树插入重平衡
    else
      sub_468090((int **)this, pDwArg2, 1, pDwArg3, (int)pDwArg42);  // 调 map/set 红黑树插入重平衡
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4684F0 sub_4684F0 —— 观察对象数据装载（名称/血量/装备）
// pArg2 为空清 +732；+736 记录新对象：__RTDynamicCast 到 IRDMonster（RTTI 自证）取 +7772 存 +740（类型决定图号 33/35/38）。
// vt+736 判是否怪物写 +856 并重启 +860 定时器；vt+340 取名串写 +744、+824 = vt+672(3)、+844 = vt+1032+68。
// 按 +332/+336 数组（跳过 22 与 dword_6C75E0 表为 -1 者）重建 +832 有序缓冲，域 4 且 vt+40(273) 时经 sub_429830/42A410/42A430 取装备图标写 +848/+852。
// ------------------------------------------------------------
void /*thiscall*/ sub_4684F0(int this, uint32_t *pArg2)  // 函数: 观察对象数据装载（名称/血量/装备）
{
  int v4; // eax
  char v5; // al
  int v6; // eax
  void *fld_340; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int *i; // eax
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // ecx
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int pObj; // ecx
  int v27; // ebx
  int fld_37C; // eax
  uint32_t **fld_384; // ecx
  uint32_t *v30; // eax
  bool fld_3842; // zf
  uint32_t *v32; // edi
  int fld_2E0; // edi
  int fld_2E02; // eax
  double fld_37C2; // st7
  float fld_37C22; // [esp+4h] [ebp-1Ch]
  int pObj2; // [esp+18h] [ebp-8h]
  int v38; // [esp+1Ch] [ebp-4h] BYREF
  int v39; // [esp+28h] [ebp+8h]

  if ( pArg2 == nullptr )  // 若 pArg2 为空
    *(uint8_t *)(this + 732) = 0;
  if ( *(uint32_t **)(this + 736) != pArg2 )
  {
    *(uint32_t *)(this + 736) = pArg2;
    if ( pArg2 != nullptr )  // 若 pArg2 有效（非空）
    {
      *(uint8_t *)(this + 732) = 1;
      *(uint32_t *)(this + 740) = 0;
      v4 = __RTDynamicCast((int)pArg2, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
      pObj2 = v4;
      if ( v4 != 0 )
        *(uint32_t *)(this + 740) = *(uint32_t *)(v4 + 7772);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 736))(pArg2) == 0;  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
      if ( *(uint8_t *)(this + 856) != v5 )
      {
        *(uint8_t *)(this + 856) = v5;
        *(uint8_t *)(this + 873) = 0;
        *(uint8_t *)(this + 874) = 0;
        sub_698F90(this + 860, 0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
      }
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 340))(pArg2);  // 调用虚函数（虚表槽 +340）【推断: IRDCollisionObject__vmt154 —— 三元…】
      sub_4014D0((std::_String_base *)(this + 744), v6 + 4, 0, -1);  // 调 std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      *(uint32_t *)(this + 824) = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 672))(pArg2, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
      fld_340 = *(void **)(this + 832);
      v8 = 0;
      if ( fld_340 != nullptr )  // 若 fld_340 有效（非空）
      {
        j__free(fld_340);  // 调 堆释放
        v8 = 0;
      }
      *(uint32_t *)(this + 832) = 0;
      *(uint32_t *)(this + 836) = 0;
      *(uint32_t *)(this + 840) = 0;
      while ( 1 )  // 无限循环
      {
        v9 = pArg2[83];
        v39 = v8;
        v10 = v9 != 0 ? (pArg2[84] - v9) >> 2 : 0;
        if ( v8 >= v10 )
          break;
        v11 = pArg2[83];
        if ( v11 != 0 )
          v12 = (pArg2[84] - v11) >> 2;
        else
          v12 = 0;
        if ( v8 < v12 )
        {
          v13 = *(uint32_t *)(pArg2[83] + 4 * v8);
          v38 = v13;
          if ( v13 != 22 && dword_6C75E0[v13] != -1 )
          {
            for ( i = *(int **)(this + 832); i != *(int **)(this + 836); ++i )
            {
              if ( *i <= v13 )
                break;
            }
            sub_430C80(i, 1, (int)&v38);  // 调 uint32 vector 区间插入（同值填充）
            v8 = v39;
          }
        }
        ++v8;
      }
      if ( pObj2 != 0 )
        *(uint32_t *)(this + 844) = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 1032))(pObj2) + 68);  // 调用虚函数（虚表槽 +1032）
      else
        *(uint32_t *)(this + 844) = 0;
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 4  // dword_8F7A24 = 当前场景状态对象
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 273) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
      {
        v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 52))(pArg2);  // 调用虚函数（虚表槽 +52）
        v16 = sub_429830(v15);  // 调 表按键查找（uint16）
        v17 = 0;
        if ( v16 != 0 )
        {
          *(uint32_t *)(this + 848) = sub_42A410(v16);  // 调 图标句柄取用（+116 槽）
          v17 = sub_42A430(v16);  // 调 同构 ·0x42A410
          goto LABEL_36;
        }
      }
      else
      {
        v17 = 0;
      }
      *(uint32_t *)(this + 848) = 0;
LABEL_36:
      *(uint32_t *)(this + 852) = v17;
      v18 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 = 当前场景状态对象
      if ( v18 == 3 )
      {
        v19 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108);  // 调用虚函数（虚表槽 +120）【推断: 转发虚槽 +116（实参 0）】
        if ( v19 != 0 )
        {
          v20 = *((uint32_t *)dword_9B7C64 + 1);
          if ( v20 != 0 )
          {
            if ( *(uint32_t *)(v19 + 112) >= (unsigned int)((*((uint32_t *)dword_9B7C64 + 2) - v20) / 44) )
              v21 = (*((uint32_t *)dword_9B7C64 + 2) - v20) / 44;
            else
              v21 = *(uint32_t *)(v19 + 112);
          }
          else
          {
            v21 = 0;
          }
          v22 = 160 * (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 740))(pArg2) / *(uint32_t *)(44 * v21 + v20 - 44 + 4);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
          goto LABEL_55;
        }
      }
      else
      {
        if ( v18 == 4 )
        {
          if ( dword_99FEC0 == 0 )  // PVP 对局进行中标志
            goto LABEL_56;
          v23 = *(uint32_t *)(dword_99FEC0 + 108);  // PVP 对局进行中标志
          if ( v23 == -1 )
            goto LABEL_56;
          v24 = *(uint32_t *)(dword_99FEC0 + 4 * v23 + 40);  // PVP 对局进行中标志
          if ( v24 == 0xFFFF )
            goto LABEL_56;
          v25 = sub_429830(v24);  // 调 表按键查找（uint16）
          if ( v25 == 0 )
            goto LABEL_56;
          pObj = *(uint32_t *)(v25 + 196);
        }
        else
        {
          if ( v18 != 6 )
            goto LABEL_56;
          pObj = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
        }
        if ( pObj != 0 )
        {
          v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 740))(pObj);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
          v22 = 300 * (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 740))(pArg2) / v27;  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
LABEL_55:
          *(uint32_t *)(this + 892) = v22;
        }
      }
LABEL_56:
      fld_37C = *(uint32_t *)(this + 892);
      if ( fld_37C >= 475 )
        fld_37C = 475;
      *(uint32_t *)(this + 888) = fld_37C;
      fld_384 = *(uint32_t ***)(this + 900);
      v30 = *fld_384;
      *fld_384 = fld_384;
      *(uint32_t *)(*(uint32_t *)(this + 900) + 4) = *(uint32_t *)(this + 900);
      fld_3842 = v30 == *(uint32_t **)(this + 900);
      *(uint32_t *)(this + 904) = 0;
      if ( !fld_3842 )
      {
        do
        {
          v32 = (uint32_t *)*v30;
          j__free(v30);  // 调 堆释放
          v30 = v32;
        }
        while ( v32 != *(uint32_t **)(this + 900) );
      }
      fld_2E0 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 736) + 740))(*(uint32_t *)(this + 736));  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
      fld_2E02 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 736) + 736))(*(uint32_t *)(this + 736));  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
      fld_37C2 = (double)*(int *)(this + 892);
      fld_37C22 = fld_37C2;
      sub_4049C0(0.0, fld_37C22, fld_2E02, fld_2E0);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
      *(uint32_t *)(this + 908) = (uint64_t)fld_37C2;
    }
  }
}


// ------------------------------------------------------------
// 0x4688A0 sub_4688A0 —— 观察对象进度映射（65 档）
// uArg2 为 1：sub_4049C0(0,65, vt+752, vt+756) 得 0..65 档并存 +181/+178 两入参。
// uArg2 为 2：遍历 +184 处链表取对应档位。
// 其余情形转发 sub_460920(uArg2, ...)。
// ------------------------------------------------------------
int /*thiscall*/ sub_4688A0(uint32_t *this, unsigned int uArg2)  // 函数: 观察对象进度映射（65 档）
{
  int result; // eax
  uint32_t *pThis_B2; // edi
  int *fld_e223; // esi
  int pObj2; // esi
  int v7; // edi
  int v8; // eax
  int pObj; // esi
  int v10; // edi
  int v11; // eax
  int fld_e184; // eax
  int fld_e1842; // esi
  int v14; // eax
  int pThis_A7; // eax
  int v16; // edx
  uint32_t *v17; // eax
  int fld_e22332; // eax
  void **v19; // ecx
  uint32_t *v20; // eax
  bool v21; // zf
  uint32_t *v22; // ecx
  void **v23; // eax
  uint32_t *v24; // esi
  int pThis_A72; // eax
  int *v26; // edx
  int pThis_A73; // eax
  int v28; // eax
  int fld_e2232; // ecx
  uint64_t v30; // rax
  uint32_t *v31; // ebx
  float v32; // [esp+0h] [ebp-2Ch]
  int v33; // [esp+4h] [ebp-28h]
  int v34; // [esp+8h] [ebp-24h]
  int v35; // [esp+18h] [ebp-14h] BYREF
  int pThis_A74; // [esp+1Ch] [ebp-10h]
  uint32_t *v37; // [esp+20h] [ebp-Ch]
  int fld_e2233; // [esp+24h] [ebp-8h]
  int *pThis_B5; // [esp+28h] [ebp-4h]

  result = uArg2;
  pThis_B2 = nullptr;
  fld_e223 = nullptr;
  pThis_B5 = nullptr;
  if ( uArg2 != 0 )
  {
    if ( uArg2 == 1 )
    {
      pObj = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
      if ( dword_8F7C04 == 0 )  // dword_8F7C04 = 本地玩家对象
        return result;
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 756))(dword_8F7C04);  // 调用虚函数（虚表槽 +756）【推断: [RTTI: IRDActiveObject__vmt2F4 ·…】
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 752))(pObj);  // 调用虚函数（虚表槽 +752）
      fld_e223 = (int *)(uint64_t)sub_4049C0(0.0, 65.0, v11, v10);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
      pThis_B5 = this + 181;  // this+724〔fVal724〕
      pThis_B2 = this + 178;
    }
    else if ( uArg2 == 2 )
    {
      fld_e184 = *(this + 184);  // this+184 单目标标志
      if ( fld_e184 != 0 )
      {
        fld_e1842 = *(this + 184);  // this+184 单目标标志
        v34 = (*(int (**)(void))(*(uint32_t *)fld_e184 + 740))();  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1842 + 736))(fld_e1842);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
        fld_e223 = (int *)sub_423A80(0, *(this + 223), v14, v34);  // 调 区间线性插值取整
      }
      pThis_B5 = this + 227;
      pThis_B2 = this + 224;  // this+224 对方就绪标签控件
    }
  }
  else
  {
    pObj2 = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
    if ( dword_8F7C04 == 0 )  // dword_8F7C04 = 本地玩家对象
      return result;
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 740))(dword_8F7C04);  // 调用虚函数（虚表槽 +740）【推断: [RTTI: IRDActiveObject__vmt2E4 ·…】
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 736))(pObj2);  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
    fld_e223 = (int *)(uint64_t)sub_4049C0(0.0, 65.0, v8, v7);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
    pThis_B5 = this + 177;  // this+708〔伤害信息〕
    pThis_B2 = this + 174;  // this+174 动画辅助标志
  }
  if ( (int)fld_e223 >= *pThis_B5 )
  {
    if ( (int)fld_e223 <= *pThis_B5 )
      goto LABEL_20;
    v19 = (void **)pThis_B2[1];  // pThis_B2=this+174 动画辅助标志
    v20 = *v19;
    if ( *v19 != v19 )
    {
      do
      {
        if ( v20[2] > (int)fld_e223 )
          break;
        v21 = v20 == (uint32_t *)pThis_B2[1];  // pThis_B2=this+174 动画辅助标志
        v22 = (uint32_t *)*v20;
        v37 = (uint32_t *)*v20;
        if ( !v21 )
        {
          *(uint32_t *)v20[1] = v22;
          *(uint32_t *)(*v20 + 4) = v20[1];
          j__free(v20);  // 调 堆释放
          v22 = v37;
          --pThis_B2[2];  // pThis_B2=this+174 动画辅助标志
        }
        v20 = v22;
      }
      while ( v22 != (uint32_t *)pThis_B2[1] );  // pThis_B2=this+174 动画辅助标志
    }
  }
  else
  {
    pThis_A7 = sub_699000((int)(this + 167));  // this+668 = 拾取/交互目标坐标缓存
    v16 = *pThis_B5;
    pThis_A74 = pThis_A7;  // pThis_A7=this+668 拾取/交互目标坐标缓存
    v17 = *(uint32_t **)pThis_B2[1];  // pThis_B2=this+174 动画辅助标志
    v35 = v16;
    v33 = v17[1];
    v37 = v17;
    fld_e2233 = sub_52DAA0(v17, v33, &v35);  // 调 事件链表有序插入
    sub_468240(1);  // 调 list 元素数预留（溢出抛错）
    fld_e22332 = fld_e2233;
    v37[1] = fld_e2233;
    **(uint32_t **)(fld_e22332 + 4) = fld_e22332;
  }
  *pThis_B5 = (int)fld_e223;
LABEL_20:
  sub_460920(uArg2, 0, fld_e223, 0, 0);  // 调 图标绘制（quickslot 主体，477-a4 底边布局，双态 sub_418DD0 取图）(推断)
  v23 = (void **)pThis_B2[1];  // pThis_B2=this+174 动画辅助标志
  pThis_B5 = fld_e223;
  v24 = *v23;
  if ( *v23 != v23 )
  {
    do
    {
      pThis_A72 = sub_699000((int)(this + 167)) - v24[3];  // this+668 = 拾取/交互目标坐标缓存
      if ( pThis_A72 >= 500 )  // pThis_A72=this+668 拾取/交互目标坐标缓存
        break;
      sub_460920(uArg2, pThis_B5, v24[2], 1, pThis_A72);  // 调 图标绘制（quickslot 主体，477-a4 底边布局，双态 sub_418DD0 取图）(推断)
      v26 = (int *)v24[2];
      v24 = (uint32_t *)*v24;
      v21 = v24 == (uint32_t *)pThis_B2[1];  // pThis_B2=this+174 动画辅助标志
      pThis_B5 = v26;
    }
    while ( !v21 );
  }
  result = pThis_B2[1];  // pThis_B2=this+174 动画辅助标志
  if ( v24 != (uint32_t *)result )
  {
    v37 = *(uint32_t **)(result + 4);
    pThis_A74 = v37[2];
    pThis_A73 = sub_699000((int)(this + 167));  // this+668 = 拾取/交互目标坐标缓存
    v28 = -500 - v37[3] + pThis_A73;  // pThis_A73=this+668 拾取/交互目标坐标缓存
    if ( v28 < 0 )
      v28 = 0;
    fld_e2232 = 0;
    if ( uArg2 < 2 )
    {
      fld_e2232 = 1000;
    }
    else if ( uArg2 == 2 )
    {
      fld_e2232 = 5 * *(this + 223);
      if ( fld_e2232 > 6000 )
        fld_e2232 = 6000;
      fld_e2233 = *(this + 223);
      goto LABEL_34;
    }
    fld_e2233 = 65;
LABEL_34:
    v32 = (float)fld_e2233;
    v30 = (uint64_t)sub_4049C0(0.0, v32, v28, fld_e2232);  // 区间线性插值（float 版，全库通用；t>=tEnd 返回 to，t<=0 返回 from）
    result = pThis_A74 - v30;
    if ( result <= (int)pThis_B5 )
    {
      if ( v24 != (uint32_t *)pThis_B2[1] )  // pThis_B2=this+174 动画辅助标志
      {
        do
        {
          v31 = (uint32_t *)*v24;
          if ( v24 != (uint32_t *)pThis_B2[1] )  // pThis_B2=this+174 动画辅助标志
          {
            *(uint32_t *)v24[1] = v31;
            *(uint32_t *)(*v24 + 4) = v24[1];
            j__free(v24);  // 调 堆释放
            result = pThis_B2[2] - 1;  // pThis_B2=this+174 动画辅助标志
            pThis_B2[2] = result;  // pThis_B2=this+174 动画辅助标志
          }
          v24 = v31;
        }
        while ( v31 != (uint32_t *)pThis_B2[1] );  // pThis_B2=this+174 动画辅助标志
      }
    }
    else
    {
      return sub_460920(uArg2, pThis_B5, result, 2, 0);  // 返回 图标绘制（quickslot 主体，477-a4 底边布局，双态 sub_418DD0 取图）(推断)
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x468BA0 sub_468BA0 —— map 查找或插入（下标语义）
// 自 _Myhead[1] 下探：key 不小于目标走左否则走右，命中返回节点 +16。
// 未命中以 (key,0) 调 ·sub_468390 插入后取 +16。
// ------------------------------------------------------------
int /*thiscall*/ sub_468BA0(int **this, int *pDwArg2)  // 函数: map 查找或插入（下标语义）
{
  int *fld_e1; // edx
  int v3; // eax
  int v5[2]; // [esp+Ch] [ebp-8h] BYREF

  fld_e1 = *(this + 1);  // this+4 = pHostObj
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
      v3 = *(uint32_t *)(v3 + 8);
    }
  }
  if ( fld_e1 != *(this + 1) && *pDwArg2 >= fld_e1[3] )  // this+4 = pHostObj
    return (int)(fld_e1 + 4);  // fld_e1=this+4 宿主对象
  v5[0] = *pDwArg2;
  v5[1] = 0;
  return *sub_468390((int)this, (int *)&pDwArg2, fld_e1, v5) + 16;  // 调 map 插入（边界与前驱后继判定）
}



// ------------------------------------------------------------
// 0x468C20 sub_468C20 —— map 赋值（查插后写值）
// 经 ·sub_468BA0(this+12, ...) 取槽指针后写入 nArg2。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_468C20(int **this, int nArg2)  // 函数: map 赋值（查插后写值）
{
  uint32_t *result; // eax

  result = (uint32_t *)sub_468BA0(this + 12, &nArg2);  // 调 map 查找或插入（下标语义）
  *result = nArg2;
  return result;
}



// ------------------------------------------------------------
// 0x468C40 sub_468C40 —— 观察面板逐帧绘制（等级/名/进度）
// +732 使能且 +736 对象 vt+736 结果变化时写 +856 并重启 +860 定时器；+740 类型映射图号 33/35/38。
// 名称经 Lv%d %s（自证）组装，配 ·sub_4688A0 进度档、sub_429830 图标与 sub_42B340 虚拟角色呈像。
// 尾段 +848/+852 两装备图标以 vt+152 画于 (37,37)。
// ------------------------------------------------------------
char /*thiscall*/ sub_468C40(int this)  // 函数: 观察面板逐帧绘制（等级/名/进度）
{
  int fld_350; // eax
  int fld_2E0; // ecx
  char v4; // al
  int fld_2E4; // eax
  int v6; // edi
  uint32_t *v7; // ecx
  int fld_378; // eax
  int fld_2E42; // eax
  int fld_64; // eax
  int fld_642; // eax
  int fld_2E43; // eax
  int fld_643; // eax
  int fld_645; // eax
  int fld_644; // eax
  int fld_34C; // ecx
  int fld_2E02; // ecx
  int fld_2E03; // eax
  int v19; // eax
  int pObj; // eax
  int fld_646; // eax
  int fld_2E44; // eax
  int v23; // edi
  int v24; // ebx
  int v25; // edi
  int v26; // ebx
  int pThis_2EC; // ecx
  int pThis_2EC2; // ecx
  int fld_354; // ecx
  int fld_3502; // esi

  LOBYTE(fld_350) = *(uint8_t *)(this + 732);  // 调 取 16 位值低 8 位
  if ( (uint8_t)fld_350 == 0 )
    return fld_350;
  fld_2E0 = *(uint32_t *)(this + 736);
  if ( fld_2E0 != 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_2E0 + 736))(fld_2E0) == 0;  // 调用虚函数（虚表槽 +736）【推断: [RTTI: IRDActiveObject__vmt2E0 ·…】
    if ( *(uint8_t *)(this + 856) != v4 )
    {
      *(uint8_t *)(this + 856) = v4;
      *(uint8_t *)(this + 873) = 0;
      *(uint8_t *)(this + 874) = 0;
      sub_698F90(this + 860, 0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
    }
  }
  fld_2E4 = *(uint32_t *)(this + 740);
  v6 = 33;
  if ( fld_2E4 == 3 )
  {
    v6 = 35;
  }
  else if ( fld_2E4 == 1 || fld_2E4 == 2 )
  {
    v6 = 38;
  }
  v7 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
  fld_378 = v6 + *(uint32_t *)(this + 888);
  *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
  v7[13] = 0;
  v7[14] = fld_378;
  v7[15] = 480;
  fld_2E42 = *(uint32_t *)(this + 740);
  if ( fld_2E42 == 3 )
  {
    fld_64 = sub_418DD0(*(uint32_t **)(this + 100), 0x87u);  // 调 资源句柄 (101)
  }
  else
  {
    if ( fld_2E42 != 1 && fld_2E42 != 2 )  // 若 fld_2E42 != 1 与/或 fld_2E42 != 2
    {
      fld_642 = sub_418DD0(*(uint32_t **)(this + 100), 0x5Cu);  // 调 资源句柄 (101)
      if ( fld_642 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_642 + 152))(fld_642, 4, 39, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      goto LABEL_19;
    }
    fld_64 = sub_418DD0(*(uint32_t **)(this + 100), 0x6Au);  // 调 资源句柄 (101)
  }
  if ( fld_64 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_64 + 152))(fld_64, 2, 37, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
LABEL_19:
  sub_488670((uint32_t *)dword_79C0B0);  // 调 视口重置 640x480
  fld_2E43 = *(uint32_t *)(this + 740);
  if ( fld_2E43 == 3 )
  {
    fld_643 = sub_418DD0(*(uint32_t **)(this + 100), 0x88u);  // 调 资源句柄 (101)
    if ( fld_643 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_643 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        fld_643,
        v6 + *(uint32_t *)(this + 888),
        37,
        dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
  }
  else if ( fld_2E43 == 1 || fld_2E43 == 2 )
  {
    fld_644 = sub_418DD0(*(uint32_t **)(this + 100), 0x6Bu);  // 调 资源句柄 (101)
    if ( fld_644 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_644 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        fld_644,
        v6 + *(uint32_t *)(this + 888),
        53,
        dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
  }
  else
  {
    fld_645 = sub_418DD0(*(uint32_t **)(this + 100), 0x62u);  // 调 资源句柄 (101)
    if ( fld_645 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_645 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        fld_645,
        v6 + *(uint32_t *)(this + 888),
        54,
        dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
  }
  fld_34C = *(uint32_t *)(this + 844);
  if ( fld_34C != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_34C + 152))(fld_34C, 6, 41, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  }
  else
  {
    fld_2E02 = *(uint32_t *)(this + 736);
    if ( fld_2E02 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_2E02 + 40))(fld_2E02, 273) != 0 )  // 调用虚函数（虚表槽 +40）【推断: ★ 条件位掩码测试（研究第 20 轮直证: 273/529/17…】
    {
      fld_2E03 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 736) + 52))(*(uint32_t *)(this + 736));  // 调用虚函数（虚表槽 +52）
      v19 = sub_429830(fld_2E03);  // 调 表按键查找（uint16）
      if ( v19 != 0 )
      {
        pObj = sub_42B340(v19);  // 调 虚拟角色惰性创建（0x294 字节）
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)pObj + 384))(pObj, 6, 41, 24, 24, 1065353216);  // 调用虚函数（虚表槽 +384）【推断: [RTTI: IRDCollisionObject__vmt18…】
      }
    }
  }
  if ( *(uint8_t *)(this + 856) != 0 && ((sub_699000(this + 860) / 0xFAu) & 1) == 0 )  // clock_now(clk)
  {
    fld_646 = sub_418DD0(*(uint32_t **)(this + 100), 0x5Bu);  // 调 资源句柄 (101)
    if ( fld_646 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_646 + 152))(fld_646, 6, 41, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  }
  sub_4688A0(2);  // 调 观察对象进度映射（65 档）
  if ( *(uint8_t *)(this + 856) != 0 && sub_699000(this + 860) >= 1000 && *(uint32_t *)(this + 904) == 0 )  // clock_now(clk)
    *(uint8_t *)(this + 732) = 0;
  fld_2E44 = *(uint32_t *)(this + 740);
  if ( fld_2E44 == 3 )
  {
    v23 = 39;
    v24 = 45;
  }
  else if ( fld_2E44 == 1 || fld_2E44 == 2 )
  {
    v23 = 36;
    v24 = 37;
  }
  else
  {
    v23 = 35;
    v24 = 38;
  }
  v25 = v23 + 2;
  v26 = v24 + 3;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 772);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )  // dword_8F7A24 = 当前场景状态对象
  {
    if ( *(uint32_t *)(this + 848) != 0 )
      v25 += 46;
    if ( *(uint32_t *)(this + 768) < 0x10u )
      pThis_2EC = this + 748;
    else
      pThis_2EC = *(uint32_t *)(this + 748);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, v25, v26, -1, pThis_2EC);  // 调用虚函数（虚表槽 +80）
  }
  else
  {
    if ( *(uint32_t *)(this + 768) < 0x10u )
      pThis_2EC2 = this + 748;
    else
      pThis_2EC2 = *(uint32_t *)(this + 748);
    (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
      dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
      v25,
      v26,
      -1,
      "Lv%d %s",  // 日志模板 Lv%d %s
      *(uint32_t *)(this + 824),
      pThis_2EC2);
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
  fld_350 = *(uint32_t *)(this + 848);
  if ( fld_350 != 0 )
  {
    fld_354 = *(uint32_t *)(this + 852);
    if ( fld_354 != 0 )
    {
      LOBYTE(fld_350) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_354 + 152))(fld_354, 37, 37, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      fld_3502 = *(uint32_t *)(this + 848);
      if ( fld_3502 != 0 )
        LOBYTE(fld_350) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_3502 + 152))(fld_3502, 37, 37, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    }
  }
  return fld_350;
}


// ------------------------------------------------------------
// 0x468FC0 sub_468FC0 —— 快捷槽悬浮提示定位与绘制
// +142 槽号有效（dword_8F8540 表 +8/+12 边界、该槽对象非 0 且 ·sub_463F10 为 -1 即无 clong 值）时进入。
// pArg2 小于 2 取槽内 +20/+24 坐标，否则 x=325、y=29*槽号+283；sub_4938F0 播放与 sub_491D00 绘 this+pArg2+143 两件。
// pArg2 为 0 且该件 +170 非 0 时继续内层分支，否则 +142 置 -1 收起。
// ------------------------------------------------------------
void /*thiscall*/ sub_468FC0(unsigned int *this, unsigned int pArg2)  // 函数: 快捷槽悬浮提示定位与绘制
{
  unsigned int fld_e142; // edi
  int v4; // eax
  int fld_e1423; // edi
  int fld_e1422; // eax
  int fld_e1424; // edi
  int v9; // ebx
  int v10; // edi
  int v11; // eax
  int v12; // edi
  int v13; // [esp+10h] [ebp+8h]

  fld_e142 = *(this + 142);  // this+568〔nAlarmVal〕
  if ( fld_e142 != -1 )  // fld_e142=this+568 nAlarmVal
  {
    v4 = *(uint32_t *)(dword_8F8540 + 8);  // dword_8F8540 = 技能/条目全局链
    if ( v4 != 0
      && fld_e142 < (*(uint32_t *)(dword_8F8540 + 12) - v4) / 20  // dword_8F8540 = 技能/条目全局链
      && *(uint32_t *)(*(uint32_t *)(dword_8F8540 + 8) + 20 * fld_e142) != 0  // dword_8F8540 = 技能/条目全局链
      && sub_463F10((uint32_t *)dword_8F8540, fld_e142) == -1 )  // 调 项内 clong 取值（缺省 -1）
    {
      if ( pArg2 < 2 )
      {
        fld_e1422 = *(this + *(this + 142) + 21);  // this+568〔nAlarmVal〕
        fld_e1423 = *(uint32_t *)(fld_e1422 + 24);  // fld_e1422=this+568 nAlarmVal
        v13 = *(uint32_t *)(fld_e1422 + 20);  // fld_e1422=this+568 nAlarmVal
      }
      else
      {
        v13 = 325;
        fld_e1423 = 29 * *(this + 142) + 283;  // this+568〔nAlarmVal〕
      }
      sub_4938F0(*(this + pArg2 + 143));  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      sub_491D00(dword_79C0B0, v13, fld_e1423, 0.0);  // 调 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      if ( pArg2 == 0 && *(uint8_t *)(*(this + 143) + 170) != 0 )  // 若 this+572〔最后命中敌记录〕
      {
        fld_e1424 = sub_463ED0((uint32_t *)dword_8F8540, *(this + 142));  // 调 20 字节项取值（越界返 0）
        v9 = *(uint32_t *)fld_e1424;
        sub_47C540(*(uint32_t *)fld_e1424);  // 调 调用 sub_47C540
        sub_47D9D0(dword_8F8540);  // dword_8F8540 = 技能/条目全局链
        sub_553FB0(*(uint32_t *)(*(this + 1) + 84));  // 调 任务 NPC 查询（47CC80/47CA40）
        if ( *(uint8_t *)(fld_e1424 + 200) != 0 )
          sub_468C20((int **)dword_8F8540, v9);  // 调 map 赋值（查插后写值）
        v10 = *(uint32_t *)(fld_e1424 + 316);
        if ( v10 != -1 )
        {
          v11 = sub_4CE8A0(v10);  // 调 调用 sub_4CE8A0
          v12 = v11;
          if ( v11 != 0 )
          {
            sub_5540D0((void *)1, *(uint32_t *)(v11 + 124));  // 调 任务 NPC 文本装配（69C730/69A5F0/56CFE0 + 69C340/69C360/69C400/69C500…
            sub_44BBA0(dword_8F8528, 7, 0);  // 调 窗口显示切换（WINDOW_SHOW 音效）
            sub_552BD0(v12);  // 调 任务文本装配（246 行：44AB50/432EE0/44CA70/429830 + 4F33A0/4F2CE0/4F2D6…
            sub_44BBA0(dword_8F8528, 8, 0);  // 调 窗口显示切换（WINDOW_SHOW 音效）
          }
        }
        *(this + 142) = -1;  // this+568〔nAlarmVal〕
      }
    }
    else
    {
      *(this + 142) = -1;  // this+568〔nAlarmVal〕
    }
  }
}



// ============================================================
// 【分区 5】CNRDBaseInterface（0x469170-0x469DD0）
// RTTI 自证基接口构造与查询。
// ============================================================
// ------------------------------------------------------------
// 0x469170 CNRDBaseInterface__vmt0
// ------------------------------------------------------------
// CNRDBaseInterface::vmt0 —— 基接口构造（RTTI 自证）
char /*thiscall*/ sub_469170(int this, int pArg2)  // 实现：CNRDBaseInterface::vmt0 —— 基接口构造（RTTI 自证）
{
  int pThis_54; // eax
  int v5; // ecx
  int pObj7; // eax
  int pObj3; // esi
  int v8; // ebx
  int v9; // esi
  int fld_4D4; // eax  | +0x04D4 → 0x469170 读取槽（与 +1232 角色名标签同段，语义未定）（CNRDBaseInterface；va=00469170）
  int pObj11; // eax
  uint32_t *v12; // eax
  int pObj5; // eax
  uint32_t *v14; // eax
  int pObj10; // eax
  int v16; // edx
  int v17; // eax
  int v18; // esi
  int v19; // ebx
  int pObj13; // ecx
  int v21; // eax
  int pThis_242; // ecx
  int v23; // ebx
  int v24; // esi
  char v25; // al
  int v26; // esi
  bool v27; // cc
  int v28; // ebx
  int i; // esi
  int pObj6; // eax
  int pObj4; // eax
  int j; // ebx
  int pObj2; // eax
  int pObj; // eax
  int nCountdownEnd; // esi  | +0x0218 → ★ 倒计时截止时刻（CNRDBaseInterface；va=00469170）
  int pObj8; // eax
  int v37; // eax
  int v38; // esi
  uint32_t *v39; // eax
  int v40; // eax
  int v41; // ebx
  uint8_t *v42; // ebx
  int v43; // esi
  int v44; // ebx
  int pObj12; // eax
  int pObj9; // eax
  int v47; // eax
  int v48; // eax
  int pLvTagCtrl; // eax  | +0x04C4 → ★ 等级标签控件（0x469170: sprintf(Lv.%d) 后按其 +20/+24 定位绘制）（CNRDBaseInterface；va=00469170）
  unsigned int fld_4C42; // esi  | +0x04C4 → ★ 等级标签控件（0x469170: sprintf(Lv.%d) 后按其 +20/+24 定位绘制）（CNRDBaseInterface；va=00469170）
  const char *v51; // eax
  int v52; // eax
  int v53; // ecx
  int v54; // esi
  int v55; // ebx
  int pObj14; // eax
  int fld_4C8; // [esp-4h] [ebp-13Ch]  | +0x04C8 → 0x469170 读取槽（与 +1220 等级标签同段，语义未定）（CNRDBaseInterface；va=00469170）
  int v59; // [esp+Ch] [ebp-12Ch]
  int v60; // [esp+10h] [ebp-128h]
  int v61; // [esp+14h] [ebp-124h]
  int v62; // [esp+18h] [ebp-120h]
  int v63; // [esp+1Ch] [ebp-11Ch]
  int v64; // [esp+20h] [ebp-118h]
  int v65; // [esp+20h] [ebp-118h]
  int v66; // [esp+24h] [ebp-114h]
  int v67; // [esp+24h] [ebp-114h]
  int v68; // [esp+28h] [ebp-110h]
  int v69; // [esp+28h] [ebp-110h]
  int pThis_21C; // [esp+2Ch] [ebp-10Ch]
  int v71; // [esp+2Ch] [ebp-10Ch]
  int v72; // [esp+2Ch] [ebp-10Ch]
  int v73; // [esp+30h] [ebp-108h]
  int v74; // [esp+30h] [ebp-108h]
  int v75; // [esp+30h] [ebp-108h]
  char Buffer[256]; // [esp+34h] [ebp-104h] BYREF
  int dword_796E502; // [esp+134h] [ebp-4h]
  int v78; // [esp+140h] [ebp+8h]
  int pThis_24; // [esp+140h] [ebp+8h]
  unsigned int v80; // [esp+140h] [ebp+8h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  LOBYTE(pThis_54) = (uint8_t)dword_8F8528;  // 调 取 16 位值低 8 位
  v5 = *((uint32_t *)dword_8F8528 + 1);  // dword_8F8528 = 主管理器
  v62 = v5;
  if ( pArg2 == *(uint32_t *)(this + 8) )  // this+8〔nBindId〕
  {
    if ( v5 != 0 )
    {
      if ( v5 != 1 )
        return pThis_54;
      goto LABEL_64;
    }
    pObj7 = sub_418DD0(0);  // 调 资源句柄 (101)
    if ( pObj7 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, 0, 402, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj3 = dword_8F7C04;  // dword_8F7C04 = 本地玩家对象
    if ( dword_8F7C04 == 0 )  // dword_8F7C04 = 本地玩家对象
    {
LABEL_20:
      v69 = 12;
      v16 = 12;
      v71 = 0;
      do
      {
        v17 = *(uint32_t *)(v16 + this);
        v18 = *(uint32_t *)(v17 + 20);
        v19 = *(uint32_t *)(v17 + 24);
        if ( v71 + 3 < *((uint32_t *)dword_8F852C + 2) )  // dword_8F852C = UI 管理器全局
        {
          pObj13 = *(uint32_t *)(v16 + *((uint32_t *)dword_8F852C + 3));  // dword_8F852C = UI 管理器全局
          if ( pObj13 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)pObj13 + 8))(pObj13, v18, v19, 0, 1);  // 调用虚函数（虚表槽 +8）【推断: 像素距离（转发 sub_499240）】
            v16 = v69;
          }
        }
        v21 = *(uint32_t *)(v16 + this);
        if ( *(uint8_t *)(v21 + 17) != 0
          && (dword_79BE3C == *(uint32_t *)(v21 + 12)  // 动画对象指针(帧同步比对基准 C)
           || *(uint8_t *)(v21 + 17) != 0
           && (dword_79BE34 == *(uint32_t *)(v21 + 12) || dword_79BE38 == *(uint32_t *)(v21 + 12))) )  // 当前动画对象指针(帧同步比对基准)
        {
          sub_4F2E40(v18, v19);
          v16 = v69;
        }
        v16 += 4;
        ++v71;
        v69 = v16;
      }
      while ( v16 < 36 );
      v72 = 0;
      pThis_24 = this + 36;  // this+36 物品状态字
      pThis_242 = this + 36;  // this+36 物品状态字
      do
      {
        v23 = *(uint32_t *)(*(uint32_t *)pThis_242 + 20);  // this+20 频道页号
        v74 = *(uint32_t *)(*(uint32_t *)pThis_242 + 24);  // this+24 页数上限
        if ( v72 < *(uint32_t *)dword_8F853C )  // 容器对象指针(容量比较)
        {
          v24 = *(uint32_t *)(-36 - this + *((uint32_t *)dword_8F853C + 1) + pThis_242);  // 容器对象指针(容量比较)
          if ( v24 != 0 )
          {
            v25 = sub_47ED40(v24);  // 调 /dword_8F852C 查对象 vt+44 比较，不足即返回 0；全部通过返回 1
            sub_47DF50(v23, v74, -1, v25 == 0, 0, 1, 1);  // 调 参数；pszArg7 时按 this+630 剩余时间画倒计时
            pThis_242 = pThis_24;  // pThis_242=this+36 物品状态字
          }
        }
        v26 = *(uint32_t *)pThis_242;  // pThis_242=this+36 物品状态字
        if ( *(uint8_t *)(*(uint32_t *)pThis_242 + 17) != 0  // this+17 激活/可命中标志
          && (dword_79BE3C == *(uint32_t *)(v26 + 12)  // 动画对象指针(帧同步比对基准 C)
           || dword_79BE34 == *(uint32_t *)(v26 + 12)  // 当前动画对象指针(帧同步比对基准)
           || dword_79BE38 == *(uint32_t *)(v26 + 12)) )  // 动画对象指针(帧同步比对基准 B)
        {
          sub_4F2E40(v23, v74);
          pThis_242 = pThis_24;  // pThis_242=this+36 物品状态字
        }
        pThis_242 += 4;  // pThis_242=this+36 物品状态字
        v27 = ++v72 < 6;
        pThis_24 = pThis_242;  // pThis_24=this+36 物品状态字
      }
      while ( v27 );
      v28 = 82;
      for ( i = 0; i < 6; ++i )  // 循环：i 从 0 递增到 6
      {
        pObj6 = sub_418DD0(25);  // 调 资源句柄 (101)
        if ( pObj6 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, v28, 470, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        pObj4 = sub_418DD0(i + 38);  // 调 资源句柄 (101)
        if ( pObj4 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v28 + 3, 473, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        v28 += 31;
      }
      for ( j = 387; i < 12; j += 31 )
      {
        pObj2 = sub_418DD0(25);  // 调 资源句柄 (101)
        if ( pObj2 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, j, 470, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        pObj = sub_418DD0(i + 38);  // 调 资源句柄 (101)
        if ( pObj != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, j + 3, 473, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        ++i;
      }
      if ( *(uint8_t *)(this + 524) != 0 && (nCountdownEnd = *(uint32_t *)(this + 536), sub_699000(this + 512) < nCountdownEnd)  // clock_now(clk)
        || byte_9B88BC != 0 )
      {
        if ( ((sub_699000(this + 512) / 0xC8u) & 1) == 0 )  // clock_now(clk)
        {
          pObj8 = sub_418DD0(72);  // 调 资源句柄 (101)
          if ( pObj8 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, 304, 452, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        }
      }
      v37 = sub_699FC0(Value);
      sub_69A110((24 - v37) / 2 + 308, 467, Value, -1);
      sub_461C20(this);  // 调 周期性提示图闪烁绘制
LABEL_64:
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 && *(int *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 2436) + 4) < 7 )  // dword_8F7A24 = 当前场景状态对象
        sub_467980(this);  // 调 小地图/雷达格网与标记
      sub_466BA0();  // 调 本机血条闪烁与位移动画
      sub_460E20(this);  // 调 队友低血量警告条绘制
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )  // dword_8F7A24 = 当前场景状态对象
        sub_4665D0((char *)this, (char *)this);  // 调 PVP 队伍 8 格成员框绘制
      else
        sub_468C40(this);  // 调 观察面板逐帧绘制（等级/名/进度）
      pThis_54 = sub_429830((uint16_t)word_77F804);  // 调 表按键查找（uint16）
      if ( pThis_54 != 0 && *(uint32_t *)((pThis_54 = sub_429830((uint16_t)word_77F804)) + 184) != 0 || v62 == 1 )  // 调 表按键查找（uint16）
      {
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 1 )  // dword_8F7A24 = 当前场景状态对象
        {
          LOBYTE(pThis_54) = sub_461F50(this);  // 调 队友/目标状态板 4 格绘制
        }
        else
        {
          pThis_54 = *(uint32_t *)(dword_8F7A24 + 12) - 3;  // dword_8F7A24 = 当前场景状态对象
          if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )  // dword_8F7A24 = 当前场景状态对象
            LOBYTE(pThis_54) = sub_4622A0(this);  // 调 与 ·sub_461F50 同构（差异：门控更严加网络指示）
        }
      }
      if ( *(uint32_t *)(this + 1244) != -1 )  // this+1244〔nTagTimer〕
        LOBYTE(pThis_54) = sub_462A90(this);  // 调 premiumService 会员面板绘制
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 6 )  // dword_8F7A24 = 当前场景状态对象
      {
        sub_4672C0(this);  // 调 底栏座位/排行条绘制
        LOBYTE(pThis_54) = sub_462FD0((uint32_t *)this, (uint32_t *)this);  // 调 席位/排行条（8 格与 120ms 滚动）
      }
      return pThis_54;
    }
    sub_4688A0(0);  // 调 观察对象进度映射（65 档）
    sub_4688A0(1);  // 调 观察对象进度映射（65 档）
    v78 = 0;
    v60 = 0;
    v68 = 0;
    pThis_21C = 0;
    v61 = 0;
    v63 = 0;
    v66 = 0;
    v73 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 1032))(pObj3) + 40);  // 调用虚函数（虚表槽 +1032）
    v64 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 1032))(pObj3) + 44);  // 调用虚函数（虚表槽 +1032）
    v8 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 1032))(pObj3) + 52);  // 调用虚函数（虚表槽 +1032）
    v59 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 1032))(pObj3) + 56);  // 调用虚函数（虚表槽 +1032）
    v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 1032))(pObj3) + 60);  // 调用虚函数（虚表槽 +1032）
    fld_4D4 = *(uint32_t *)(this + 1236);  // this+1236〔field_04D4〕
    if ( fld_4D4 != 0 )  // fld_4D4=this+1236 field_04D4
    {
      if ( fld_4D4 == 1 )  // fld_4D4=this+1236 field_04D4
      {
        v78 = (uint64_t)((double)(v8 - v9) / (double)(v59 - v9) * 145.0);
        pThis_21C = 187;
        v60 = sub_423A80(0, 145, v73, v64);  // 调 区间线性插值取整
        v61 = 184;
        v63 = 425;
        v66 = 437;
        pObj11 = sub_418DD0(181);  // 调 资源句柄 (101)
        goto LABEL_13;
      }
    }
    else
    {
      if ( *(uint8_t *)(this + 552) == 0 || (uint8_t)sub_41C6E0(this + 540) != 0 )  // 调 超时判定（clock_now(clk) >= this+24 截止时刻）
      {
        v78 = sub_423A80(0, 145, v73, v64);  // 调 区间线性插值取整
        pThis_21C = 183;
      }
      else
      {
        v78 = 145;
        pThis_21C = ((2290649225LL * (unsigned int)sub_699000(this + 540)) & 0x4000000000LL) != 0 ? 185 : 183;  // clock_now(clk)
      }
      v60 = (uint64_t)((double)(v8 - v9) / (double)(v59 - v9) * 145.0);
      v61 = 188;
      v68 = 180;
      v63 = 431;
      v66 = 425;
    }
    pObj11 = sub_418DD0(v68);  // 调 资源句柄 (101)
LABEL_13:
    if ( pObj11 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj11 + 152))(pObj11, 58, 421, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    v12 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
    v12[13] = 0;
    v12[14] = v78 + 118;
    v12[15] = 480;
    pObj5 = sub_418DD0(pThis_21C);  // 调 资源句柄 (101)
    if ( pObj5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, 118, v63, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    sub_488670(dword_79C0B0);  // 调 视口重置 640x480
    v14 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    *(uint32_t *)(dword_79C0B0 + 48) = 0;  // dword_79C0B0 = 文本/图像绘制对象
    v14[13] = 0;
    v14[14] = v60 + 118;
    v14[15] = 480;
    pObj10 = sub_418DD0(v61);  // 调 资源句柄 (101)
    if ( pObj10 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj10 + 152))(pObj10, 118, v66, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    sub_488670(dword_79C0B0);  // 调 视口重置 640x480
    goto LABEL_20;
  }
  v38 = 0;
  pThis_54 = this + 84;  // this+84 插值起点 X
  while ( pArg2 != *(uint32_t *)pThis_54 )  // 当 pArg2 != *(uint32_t *)pThis_54 循环
  {
    ++v38;
    pThis_54 += 4;  // pThis_54=this+84 插值起点 X
    if ( v38 >= 3 )
    {
      if ( pArg2 == *(uint32_t *)(this + 1232) )  // this+1232〔pNameTagCtrl〕
      {
        LOBYTE(pThis_54) = *((uint32_t *)dword_8F8528 + 1);  // 调 取 16 位值低 8 位
        if ( v5 == 0 )
        {
          pThis_54 = *(uint32_t *)(this + 1236);  // this+1236〔field_04D4〕
          if ( pThis_54 != 0 || dword_8F7C04 == 0 )  // dword_8F7C04 = 本地玩家对象
          {
            if ( pThis_54 == 1 )  // pThis_54=this+1236 field_04D4
            {
              pThis_54 = sub_429830((uint16_t)word_77F804);  // 调 表按键查找（uint16）
              if ( pThis_54 != 0 )  // pThis_54=this+1236 field_04D4
              {
                v47 = sub_429830((uint16_t)word_77F804);  // 调 表按键查找（uint16）
                v80 = *(uint32_t *)(sub_42A410(v47) + 20);  // 调 图标句柄取用（+116 槽）
                v48 = sub_429830((uint16_t)word_77F804);  // 调 表按键查找（uint16）
                pThis_54 = sub_42A410(v48);  // 调 图标句柄取用（+116 槽）
                if ( pThis_54 != 0 )  // pThis_54=this+1236 field_04D4
                  LOBYTE(pThis_54) = (*(int (/*thiscall*/ **)(int, unsigned int, int, int))(*(uint32_t *)pThis_54 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
                                 pThis_54,  // pThis_54=this+1236 field_04D4
                                 88 - (v80 >> 1),
                                 424,
                                 dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
              }
            }
          }
          else
          {
            v39 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 672))(dword_8F7C04, 3);  // 调用虚函数（虚表槽 +672）【推断: [RTTI: IRDActiveObject__vmt2A0 ·…】
            sprintf(Buffer, "Lv.%d", *v39);  // 调 格式化到缓冲
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 124);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
            (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
              dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
              *(uint32_t *)(*(uint32_t *)(this + 1232) + 20) + 15,  // this+1232〔pNameTagCtrl〕
              *(uint32_t *)(*(uint32_t *)(this + 1232) + 24) + 3,  // this+1232〔pNameTagCtrl〕
              -1,
              Buffer);
            LOBYTE(pThis_54) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
          }
        }
      }
      if ( pArg2 == *(uint32_t *)(this + 964) )  // this+964〔nSlotId〕
      {
        if ( v62 == 0 )
        {
          pLvTagCtrl = *(uint32_t *)(this + 1220);  // this+1220〔pLvTagCtrl〕
          if ( *(uint8_t *)(pLvTagCtrl + 17) != 0  // fld_4C4=this+1220 pLvTagCtrl
            && dword_79BE3C == *(uint32_t *)(pLvTagCtrl + 12)  // 动画对象指针(帧同步比对基准 C)
            && *(uint32_t *)(*(uint32_t *)(this + 4) + 108) == 12 )  // this+4〔pAvatarStatus〕
          {
            if ( *(uint8_t *)(this + 1228) == 0 )  // this+1228〔bLvTagInited〕
            {
              sub_423200(dword_8F7B08, 69);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
              sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
              *(uint8_t *)(this + 1228) = 1;  // this+1228〔bLvTagInited〕
            }
            fld_4C42 = *(uint32_t *)(*(uint32_t *)(this + 1220) + 28);  // this+1220〔pLvTagCtrl〕
            fld_4C8 = *(uint32_t *)(this + 1224);  // this+1224〔field_04C8〕
            v51 = (const char *)sub_422E70(189);  // 调 存 CStringManager::getStr 取本地化串
            sprintf(Buffer, v51, fld_4C8);  // 调 格式化到缓冲
            sub_4649B0(  // 调 带框文本上屏（静态一次性初始化）
              *(uint32_t *)(*(uint32_t *)(this + 1220) + 20) + (fld_4C42 >> 1),  // this+1220〔pLvTagCtrl〕
              *(uint32_t *)(*(uint32_t *)(this + 1220) + 24) - 15,  // this+1220〔pLvTagCtrl〕
              -1,
              -16777216,
              2,
              Buffer,
              0,
              0,
              1600,
              0);
          }
          sub_468FC0(0);  // 调 快捷槽悬浮提示定位与绘制
          sub_460FB0(this);  // 调 屏幕坐标双换算与图标层悬挂
          v52 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 = 当前场景状态对象
          if ( v52 == 4 && *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 36) != 0 )  // dword_8F7A24 = 当前场景状态对象
          {
            sub_466D70(this);  // 调 战场剩余时间数字绘制
          }
          else if ( v52 == 6 && *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 32) == 3 )  // dword_8F7A24 = 当前场景状态对象
          {
            sub_4670A0(this);  // 调 与 ·sub_466D70 同构（差异：10 秒倒数）
          }
        }
        if ( *(uint8_t *)(this + 996) != 0 )  // this+996〔bStatusFlag〕
        {
          sub_462870(this);  // 调 出屏队友边缘箭头与名字标注
          sub_466340(this);  // 调 地面掉落物名称标签绘制
        }
        LOBYTE(pThis_54) = sub_4BF250(this + 976);  // 调 槽查询（+64 表）
        if ( (uint8_t)pThis_54 != 0 )  // pThis_54=this+1236 field_04D4
        {
          LOBYTE(pThis_54) = sub_4BF250(this + 984);  // 调 槽查询（+64 表）
          if ( (uint8_t)pThis_54 != 0 )  // pThis_54=this+1236 field_04D4
            LOBYTE(pThis_54) = sub_467630(this);  // 调 实体状态调试文本绘制
        }
        if ( *(uint8_t *)(this + 508) == 1 )  // this+508〔bPetFlag〕
          LOBYTE(pThis_54) = sub_461840(this);  // 调 取 16 位值低 8 位
        return pThis_54;  // pThis_54=this+1236 field_04D4
      }
      if ( pArg2 != *(uint32_t *)(this + 96) )  // this+384 = 动画件名 SSO 容量判据
        return pThis_54;  // pThis_54=this+1236 field_04D4
      LOBYTE(pThis_54) = *(uint8_t *)(pArg2 + 17);  // 调 取 16 位值低 8 位
      if ( (uint8_t)pThis_54 == 0 )  // pThis_54=this+1236 field_04D4
        return pThis_54;  // pThis_54=this+1236 field_04D4
      if ( dword_79BE3C != *(uint32_t *)(pArg2 + 12) )  // pArg2+12〔nSkillRec12(推断)〕
      {
        v53 = *(uint32_t *)(pArg2 + 12);  // pArg2+12〔nSkillRec12(推断)〕
        if ( dword_79BE34 != v53 )  // 当前动画对象指针(帧同步比对基准)
        {
          LOBYTE(pThis_54) = dword_79BE38;  // 调 取 16 位值低 8 位
          if ( dword_79BE38 != v53 )  // 动画对象指针(帧同步比对基准 B)
            return pThis_54;  // pThis_54=this+1236 field_04D4
        }
      }
      sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      v54 = *(uint32_t *)(pArg2 + 24);  // pArg2+24〔nPageMax(推断)〕
      v55 = *(uint32_t *)(pArg2 + 20);  // pArg2+20〔nPage(推断)〕
      pObj14 = sub_418DD0(25);  // 调 资源句柄 (101)
      if ( pObj14 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj14 + 152))(pObj14, v55 - 1, v54, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
LABEL_144:
      LOBYTE(pThis_54) = sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
      return pThis_54;  // pThis_54=this+1236 field_04D4
    }
  }
  if ( v5 != 0 )
    return pThis_54;  // pThis_54=this+1236 field_04D4
  v40 = *(uint32_t *)(dword_8F8540 + 8);  // dword_8F8540 = 技能/条目全局链
  v41 = *(uint32_t *)(pArg2 + 24);  // pArg2+24〔nPageMax(推断)〕
  v67 = *(uint32_t *)(pArg2 + 20);  // pArg2+20〔nPage(推断)〕
  v75 = v41;
  if ( v40 != 0
    && v38 < (unsigned int)((*(uint32_t *)(dword_8F8540 + 12) - v40) / 20)  // dword_8F8540 = 技能/条目全局链
    && (v65 = *(uint32_t *)(*(uint32_t *)(dword_8F8540 + 8) + 20 * v38)) != 0 )  // dword_8F8540 = 技能/条目全局链
  {
    v42 = (uint8_t *)(28 * v38 + this);
    LOBYTE(pThis_54) = sub_463F10(v38) == 0;  // 调 项内 clong 取值（缺省 -1）
    if ( v42[596] != (uint8_t)pThis_54 )  // pThis_54=this+1236 field_04D4
    {
      v42[596] = pThis_54;  // pThis_54=this+1236 field_04D4
      if ( (uint8_t)pThis_54 != 0 )  // pThis_54=this+1236 field_04D4
      {
        v42[597] = 0;
        v42[598] = 0;
        LOBYTE(pThis_54) = sub_698F90((int)(v42 + 584), 0, 0);  // 调 取 16 位值低 8 位
      }
    }
    if ( *(uint32_t *)(this + 568) != v38 )  // this+568〔nAlarmVal〕
    {
      v43 = 53;
      if ( *(uint8_t *)(v65 + 120) != 0 )
      {
        v43 = 108;
      }
      else if ( *(uint32_t *)(v65 + 116) == 2 )
      {
        v43 = 85;
      }
      if ( v42[596] != 0 )
      {
        v44 = (int)(v42 + 584);
        if ( sub_699000(v44) >= 2000 || ((sub_699000(v44) / 0xFAu) & 1) != 0 )  // clock_now(clk)
          ++v43;
      }
      pObj12 = sub_418DD0(v43);  // 调 资源句柄 (101)
      if ( pObj12 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj12 + 152))(pObj12, v67, v75, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      LOBYTE(pThis_54) = sub_43BCB0(pArg2);  // 调 焦点窗口判定（三选）
      if ( (uint8_t)pThis_54 != 0 )  // pThis_54=this+1236 field_04D4
      {
        sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
        pObj9 = sub_418DD0(52);  // 调 资源句柄 (101)
        if ( pObj9 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj9 + 152))(pObj9, v67, v75, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
        goto LABEL_144;
      }
    }
  }
  else
  {
    pThis_54 = sub_418DD0(51);  // 调 资源句柄 (101)
    if ( pThis_54 != 0 )  // pThis_54=this+1236 field_04D4
      LOBYTE(pThis_54) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pThis_54 + 152))(pThis_54, v67, v41, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
  }
  return pThis_54;  // pThis_54=this+1236 field_04D4
}


// ============================================================
// 【分区 6】界面管理器辅助（0x469DD0-0x46ABB0）
// 深拷贝/容器克隆类操作（~630 行）【推断】。
// ============================================================
// ------------------------------------------------------------
// 0x469DD0 sub_469DD0 —— 界面管理器初始化（控件工厂与资源装载）
// sub_460590 统计初始化；Block 存 +4；自 dword_99FCC8+20 上下文取 +12/+68/+208 图容器。
// 循环 operator new(0x68) 加 sub_426BD0（nengine::IControl 构造，自证）建控件，以 sub_69A5F0 定尺寸位置、sub_69A840 登记。
// 资源：Common/Etc/pingsign.img、Common/Etc/Category.img、Animation 下 Connecting/QuestFinish1-3/Shake1-2/PVPStartCount.ani（路径自证）。
// ------------------------------------------------------------
int /*thiscall*/ sub_469DD0(int this, void *Block)  // 函数: 界面管理器初始化（控件工厂与资源装载）
{
  void *pMem; // eax
  int v4; // eax
  int *pThis_C; // edi
  void *pMem2; // eax
  int v7; // eax
  int *pThis_24; // edi
  void *pMem3; // eax
  int v10; // eax
  int i; // edi
  uint32_t *v12; // eax
  uint32_t *pMem4; // eax
  uint32_t *pMem42; // edi
  uint32_t *pMem422; // ecx
  int *pThis_54; // edi
  void *pMem5; // eax
  int v18; // eax
  uint8_t *pMem6; // eax
  uint8_t *pMem62; // edi
  uint8_t *pMem7; // edi
  uint8_t *pMem8; // edi
  int *pThis_CC; // edi
  void *pMem9; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // eax
  uint8_t *pThis_254; // eax
  int j; // ecx
  uint32_t *pMem10; // edi
  uint32_t *pMem11; // eax
  uint32_t *pMem112; // edi
  uint32_t *pMem1122; // ecx
  void *pMem12; // eax
  int v37; // eax
  int v38; // eax
  int pThis_3F0; // edi
  int v40; // eax
  int v41; // eax
  int v42; // ecx
  int pThis_402; // eax
  uint32_t *pMem13; // eax
  uint32_t *pMem132; // edi
  uint32_t *pMem1322; // ecx
  void *pMem14; // eax
  int v48; // eax
  int fld_510; // eax
  uint8_t *pMem15; // eax
  uint8_t *pMem152; // edi
  uint8_t *pMem1522; // ecx
  int pObj; // eax
  int v54; // edi
  int v55; // ecx
  uint32_t *pMem16; // edi
  uint32_t *pMem162; // ecx
  int result; // eax
  uint32_t v59[3]; // [esp+Ch] [ebp-34h]
  uint32_t v60[3]; // [esp+18h] [ebp-28h]
  void *pMem153; // [esp+24h] [ebp-1Ch]
  void *pMem22; // [esp+28h] [ebp-18h]
  int fld_64; // [esp+2Ch] [ebp-14h]
  int pThis_504; // [esp+30h] [ebp-10h]
  int v65; // [esp+3Ch] [ebp-4h]
  int Blocka; // [esp+48h] [ebp+8h]
  int Blockb; // [esp+48h] [ebp+8h]
  uint32_t *Blockc; // [esp+48h] [ebp+8h]
  void *Blockh; // [esp+48h] [ebp+8h]
  int Blockd; // [esp+48h] [ebp+8h]
  void *Blocki; // [esp+48h] [ebp+8h]
  void *Blockj; // [esp+48h] [ebp+8h]
  void *Blockk; // [esp+48h] [ebp+8h]
  int Blocke; // [esp+48h] [ebp+8h]
  void *Blockl; // [esp+48h] [ebp+8h]
  void *Blockm; // [esp+48h] [ebp+8h]
  int Blockf; // [esp+48h] [ebp+8h]
  void *Blockn; // [esp+48h] [ebp+8h]
  int Blockg; // [esp+48h] [ebp+8h]
  void *Blocko; // [esp+48h] [ebp+8h]

  sub_460590();  // 调 统计初始化
  *(uint32_t *)(this + 4) = Block;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 100) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 12);  // this+100〔bEnchantDone(推断)〕
  *(uint32_t *)(this + 108) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 68);  // this+108〔nAdd108(推断)〕
  *(uint32_t *)(this + 1276) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
                               dword_8F84B8,  // dword_8F84B8＝vt+60
                               "Common/Etc/pingsign.img");  // 资源路径 Common/Etc/pingsign.img
  *(uint32_t *)(this + 104) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 208);  // this+104〔nTimerEnd(推断)〕
  pMem = operator new(0x68u);  // operator new 分配 104 字节
  v65 = 0;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v4 = sub_426BD0(pMem);  // 调 nengine::IControl 构造
  else
    v4 = 0;
  *(uint32_t *)(this + 8) = v4;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(v4 + 28) = 640;
  *(uint32_t *)(v4 + 32) = 64;
  v65 = -1;
  sub_69A5F0(0, 416);  // 调 设位、sub_69A840 登记
  *(uint32_t *)(*(uint32_t *)(this + 8) + 68) = this;  // this+8〔nSkillRec8(推断)〕等 2 字段
  Blocka = 76;
  pThis_C = (int *)(this + 12);  // this+12〔nSkillRec12(推断)〕等 2 字段
  do
  {
    pMem2 = operator new(0x68u);  // operator new 分配 104 字节
    pMem22 = pMem2;
    v65 = 1;
    if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
      v7 = sub_426BD0(pMem2);  // 调 nengine::IControl 构造
    else
      v7 = 0;
    *pThis_C = v7;  // pThis_C=this+12 nSkillRec12
    *(uint32_t *)(v7 + 28) = 28;
    *(uint32_t *)(v7 + 32) = 28;
    v65 = -1;
    sub_69A5F0(Blocka, 447);  // 调 设位、sub_69A840 登记
    sub_69A840(*pThis_C++);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    Blocka += 31;  // Blocka 前进 31
  }
  while ( Blocka < 262 );
  Blockb = 381;
  pThis_24 = (int *)(this + 36);  // this+144 = pFrameList144
  do
  {
    pMem3 = operator new(0x68u);  // operator new 分配 104 字节
    pMem22 = pMem3;
    v65 = 2;
    if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
      v10 = sub_426BD0(pMem3);  // 调 nengine::IControl 构造
    else
      v10 = 0;
    *pThis_24 = v10;  // pThis_24=this+144 第 4 组·+1040 增量子倍率
    *(uint32_t *)(v10 + 28) = 28;
    *(uint32_t *)(v10 + 32) = 28;
    v65 = -1;
    sub_69A5F0(Blockb, 447);  // 调 设位、sub_69A840 登记
    sub_69A840(*pThis_24++);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    Blockb += 31;  // Blockb 前进 31
  }
  while ( Blockb < 567 );
  for ( i = 0; i < 5; ++i )  // 循环：i 从 0 递增到 5
  {
    Blockc = operator new(0x84u);  // operator new 分配 132 字节
    v65 = 3;
    if ( Blockc != nullptr )  // 若 Blockc 有效（非空）
    {
      if ( i == 2 )
        pThis_504 = 61;
      else
        pThis_504 = 3 * i + 10;
      fld_64 = *(uint32_t *)(this + 100);  // this+100〔bEnchantDone(推断)〕
      sub_426BD0(Blockc);  // 调 nengine::IControl 构造
      LOBYTE(v65) = 4;  // 调 取 16 位值低 8 位
      *Blockc = &nengine::CNButton::`vftable';  // vftable 复位
      ((void (*)(void))sub_69C780)();  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(v63, 3 * i + 10, 3 * i + 11, 3 * i + 12, v64, 0, 0);
      v12 = Blockc;
    }
    else
    {
      v12 = nullptr;
    }
    *(uint32_t *)(this + 4 * i + 60) = v12;  // this+4 宿主对象
    v65 = -1;
    sub_69A840(v12);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  }
  sub_69C980(*(uint32_t *)(this + 100), 16, 17, 18, 61, 0, 0);  // 调 换 191/190/190 号图
  sub_69A5F0(277, 460);  // 调 设位、sub_69A840 登记
  sub_69A5F0(287, 436);  // 调 设位、sub_69A840 登记
  sub_69A5F0(311, 426);  // 调 设位、sub_69A840 登记
  sub_69A5F0(335, 436);  // 调 设位、sub_69A840 登记
  sub_69A5F0(345, 460);  // 调 设位、sub_69A840 登记
  v13 = operator new(0x84u);  // operator new 分配 132 字节
  v14 = v13;
  v62 = v13;
  v65 = 5;
  if ( v13 != nullptr )  // 若 v13 有效（非空）
  {
    Blockh = *(void **)(this + 100);  // this+100 插值终点 Y
    sub_426BD0(v13);  // 调 nengine::IControl 构造
    LOBYTE(v65) = 6;  // 调 取 16 位值低 8 位
    *v14 = &nengine::CNButton::`vftable';  // vftable 复位
    sub_69C780(pMem42);  // 调 初始化 → ·vmt20(nArg2..nArg8
    sub_69C7B0(Blockh, 50, 50, 50, 50, 0, 0);  // Blockh=this+100 插值终点 Y
    pMem422 = pMem42;
  }
  else
  {
    pMem422 = nullptr;
  }
  v65 = -1;
  *(uint32_t *)(this + 80) = pMem422;  // this+80〔nAuraStage(推断)〕
  sub_69A5F0(404, 428);  // 调 设位、sub_69A840 登记
  sub_69A840(*(uint32_t *)(this + 80));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  Blockd = 443;
  pThis_54 = (int *)(this + 84);  // this+84〔pFxObjA(推断)〕
  do
  {
    pMem5 = operator new(0x68u);  // operator new 分配 104 字节
    pMem22 = pMem5;
    v65 = 7;
    if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
      v18 = sub_426BD0(pMem5);  // 调 nengine::IControl 构造
    else
      v18 = 0;
    *pThis_54 = v18;  // pThis_54=this+84 pFxObjA
    *(uint32_t *)(v18 + 28) = 36;
    *(uint32_t *)(v18 + 32) = 12;
    *(uint32_t *)(*pThis_54 + 68) = this;  // this+68 角色数
    v65 = -1;
    sub_69A5F0(Blockd, 428);  // 调 设位、sub_69A840 登记
    sub_69A840(*pThis_54++);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    Blockd += 38;  // Blockd 前进 38
  }
  while ( Blockd < 557 );
  pMem6 = operator new(0x2Cu);  // operator new 分配 44 字节
  pMem62 = pMem6;
  pMem22 = pMem6;
  v65 = 8;
  if ( pMem6 != nullptr )  // 若 pMem6 有效（非空）
  {
    Blocki = *(void **)(this + 100);  // this+100 插值终点 Y
    fld_64 = dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    pMem6[4] = 0;
    LOBYTE(v65) = 9;  // 调 取 16 位值低 8 位
    *(uint32_t *)pMem6 = &nengine::CNNumberSet::`vftable';  // vftable 复位
    sub_699E20(v19);  // 调 本体初始化 + sub_699E40(a2..a5)
    sub_699E40(v63, Blocki, 25, 4);  // Blocki=this+100 插值终点 Y
  }
  else
  {
    v20 = nullptr;
  }
  *(uint32_t *)(this + 112) = v20;  // this+112〔pHostComp112〕
  v21 = operator new(0x2Cu);  // operator new 分配 44 字节
  v62 = v21;
  v65 = 10;
  if ( v21 != nullptr )  // 若 v21 有效（非空）
  {
    Blockj = *(void **)(this + 100);  // this+100 插值终点 Y
    v63 = dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    v21[4] = 0;
    LOBYTE(v65) = 11;  // 调 取 16 位值低 8 位
    *(uint32_t *)v21 = &nengine::CNNumberSet::`vftable';  // vftable 复位
    sub_699E20(pMem7);  // 调 本体初始化 + sub_699E40(a2..a5)
    sub_699E40(fld_64, Blockj, 72, 4);  // fld_64=this+100 bEnchantDone
  }
  else
  {
    pMem7 = nullptr;
  }
  *(uint32_t *)(this + 116) = pMem7;  // this+116〔会话上下文〕
  pMem8 = operator new(0x2Cu);  // operator new 分配 44 字节
  pMem22 = pMem8;
  v65 = 12;
  if ( pMem8 != nullptr )  // 若 pMem8 有效（非空）
  {
    Blockk = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 84);  // nengine::CNSlider 全局实例
    fld_64 = dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
    pMem8[4] = 0;
    LOBYTE(v65) = 13;  // 调 取 16 位值低 8 位
    *(uint32_t *)pMem8 = &nengine::CNNumberSet::`vftable';  // vftable 复位
    sub_699E20(v22);  // 调 本体初始化 + sub_699E40(a2..a5)
    sub_699E40(v63, Blockk, 4, 2);
  }
  else
  {
    v22 = nullptr;
  }
  *(uint32_t *)(this + 120) = v22;  // this+120〔pAnimObj〕
  v22[24] = 0;
  *(uint32_t *)(*(uint32_t *)(this + 120) + 36) = 2;  // this+120〔pAnimObj〕
  *(uint8_t *)(this + 124) = 0;  // this+124〔pAuraAnim(推断)〕
  *(uint8_t *)(this + 125) = 0;  // this+125〔field_007D〕
  *(uint8_t *)(this + 126) = 0;  // this+126〔field_007E〕
  *(uint8_t *)(this + 127) = 0;  // this+508〔uPetFlag(推断)〕
  *(uint32_t *)(this + 136) = 0;  // this+136〔nCtx136(推断)〕等 2 字段
  *(uint32_t *)(this + 140) = 6;  // this+140〔nAdd140(推断)〕
  *(uint32_t *)(this + 144) = 12;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 0;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 152) = 1600;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 156) = 0;  // this+156〔nAdd156(推断)〕
  *(uint32_t *)(this + 160) = 0;  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 164) = 0;  // this+164〔fAdd164(推断)〕
  *(uint32_t *)(this + 168) = 0;  // this+672 = 拾取/交互目标有效标志
  *(uint32_t *)(this + 172) = 0;  // this+688 = 表现/名字快照[2]
  v65 = -1;
  *(uint32_t *)(this + 172) = dword_99FCCC;  // this+688 = 表现/名字快照[2]
  *(uint8_t *)(this + 126) = 1;  // this+126〔field_007E〕
  *(uint32_t *)(this + 128) = -16777216;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  Blocke = 4;
  v23 = (int *)(this + 204);  // this+204〔pSubAnim204(推断)〕
  do
  {
    v24 = operator new(0x68u);  // operator new 分配 104 字节
    v62 = v24;
    v65 = 14;
    if ( v24 != nullptr )  // 若 v24 有效（非空）
      v25 = sub_426BD0(v24);  // 调 nengine::IControl 构造
    else
      v25 = 0;
    *v23 = v25;  // v23=this+204 pSubAnim204
    *(uint32_t *)(v25 + 28) = 92;
    *(uint32_t *)(v25 + 32) = 29;
    v65 = -1;
    sub_69A5F0(Blocke, 4);  // 调 设位、sub_69A840 登记
    *(uint8_t *)(*v23 + 16) = 0;  // v23=this+204 pSubAnim204
    sub_69A840(*v23++);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    Blocke += 95;  // Blocke 前进 95
  }
  while ( Blocke < 384 );
  v65 = 15;
  if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
    v26 = sub_431860((char)"Common/Etc/Animation/Connecting.ani", 1);  // 调 动画件构造（资源 id 版）
  else
    v26 = 0;
  *(uint32_t *)(this + 220) = v26;  // this+220〔nSnapDst220(推断)〕
  sub_699070(0);  // clock_bind_domain(clk, newDomainId) (新发现)
  *(uint8_t *)(this + 456) = 0;  // this+456〔pKeyVecEnd(推断)〕
  *(uint8_t *)(this + 457) = 0;
  *(uint8_t *)(this + 458) = 0;
  *(uint8_t *)(this + 459) = 0;
  *(uint32_t *)(this + 468) = 0;
  *(uint32_t *)(this + 472) = 6;
  *(uint32_t *)(this + 476) = 12;
  *(uint32_t *)(this + 480) = 0;
  *(uint32_t *)(this + 484) = 1600;
  *(uint32_t *)(this + 488) = 0;
  *(uint32_t *)(this + 492) = 0;
  *(uint32_t *)(this + 496) = 0;
  *(uint32_t *)(this + 500) = 0;
  *(uint32_t *)(this + 504) = 0;
  *(uint32_t *)(this + 504) = dword_99FCCC;  // dword_99FCCC＝与字距
  *(uint32_t *)(this + 492) = 3;
  *(uint8_t *)(this + 524) = 0;  // this+524〔fAbilityScale(推断)〕
  *(uint8_t *)(this + 552) = 0;  // this+552〔bItemAlarm(推断)〕
  v65 = 16;
  if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
    v27 = sub_431860((char)"Common/Etc/Animation/QuestFinish1.ani", 1);  // 调 动画件构造（资源 id 版）
  else
    v27 = 0;
  *(uint32_t *)(this + 572) = v27;  // this+572 最后一次受击
  v65 = 17;
  if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
    v28 = sub_431860((char)"Common/Etc/Animation/QuestFinish2.ani", 1);  // 调 动画件构造（资源 id 版）
  else
    v28 = 0;
  *(uint32_t *)(this + 576) = v28;  // this+576〔uOffset576〕
  v65 = 18;
  if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
    v29 = sub_431860((char)"Common/Etc/Animation/QuestFinish3.ani", 1);  // 调 动画件构造（资源 id 版）
  else
    v29 = 0;
  *(uint32_t *)(this + 580) = v29;  // this+580〔uOffset580〕
  v65 = -1;
  v30 = (uint8_t *)(this + 596);
  for ( j = 3; j != 0; --j )  // 循环：j 从 3 递减到 0
  {
    *v30 = 0;
    v30 += 28;
  }
  *(uint8_t *)(this + 681) = 0;
  *(uint8_t *)(this + 682) = 0;
  sub_698F90(0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
  *(uint32_t *)(this + 728) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 调用虚函数（虚表槽 +60）【推断: 取默认共享组件 this+112（研究第 12 轮直证：观察者兜…】
                              dword_8F84B8,  // dword_8F84B8＝vt+60
                              "Common/Etc/Category.img");  // 资源路径 Common/Etc/Category.img
  *(uint8_t *)(this + 772) = 0;  // this+772〔uVal772(推断)〕
  *(uint8_t *)(this + 773) = 0;
  *(uint8_t *)(this + 774) = 0;
  *(uint8_t *)(this + 775) = 0;
  *(uint32_t *)(this + 784) = 0;
  *(uint32_t *)(this + 788) = 6;
  *(uint32_t *)(this + 792) = 12;
  *(uint32_t *)(this + 796) = 0;
  *(uint32_t *)(this + 800) = 1600;
  *(uint32_t *)(this + 804) = 0;
  *(uint32_t *)(this + 808) = 0;
  *(uint32_t *)(this + 812) = 0;
  *(uint32_t *)(this + 816) = 0;
  *(uint32_t *)(this + 820) = 0;
  *(uint32_t *)(this + 820) = dword_99FCCC;  // dword_99FCCC＝与字距
  *(uint8_t *)(this + 774) = 1;
  *(uint32_t *)(this + 776) = -16777216;
  *(uint32_t *)(this + 992) = sub_418DD0(4);  // 调 资源句柄 (101)
  *(uint8_t *)(this + 912) = 0;
  *(uint8_t *)(this + 913) = 0;
  *(uint8_t *)(this + 914) = 0;
  *(uint8_t *)(this + 915) = 0;
  *(uint32_t *)(this + 924) = 0;
  *(uint32_t *)(this + 928) = 6;
  *(uint32_t *)(this + 932) = 12;
  *(uint32_t *)(this + 936) = 0;
  *(uint32_t *)(this + 940) = 1600;  // this+940〔nNameBufCap〕
  *(uint32_t *)(this + 944) = 0;  // this+944〔bNamePlayed〕
  *(uint32_t *)(this + 948) = 0;
  *(uint32_t *)(this + 952) = 0;
  *(uint32_t *)(this + 956) = 0;
  *(uint32_t *)(this + 960) = 0;  // this+960〔nBigStateMirror960(推断)〕
  *(uint32_t *)(this + 960) = dword_99FCCC;  // this+960〔nBigStateMirror960(推断)〕
  *(uint32_t *)(this + 940) = 200;  // this+940〔nNameBufCap〕
  *(uint32_t *)(this + 924) = 1;
  *(uint8_t *)(this + 914) = 1;
  *(uint32_t *)(this + 916) = -16777216;
  if ( byte_98B758 == 0 )
  {
    dword_98B740 = 0;  // dword_98B740＝标出首个可用。
    dword_98B748 = 0;
    word_98B744 = 0;
    word_98B74C = 0;
    byte_98B758 = 1;
  }
  v32 = operator new(0x84u);  // operator new 分配 132 字节
  v62 = v32;
  v65 = 19;
  if ( v32 != nullptr )  // 若 v32 有效（非空）
  {
    Blockl = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 172);  // nengine::CNSlider 全局实例
    sub_426BD0(v32);  // 调 nengine::IControl 构造
    LOBYTE(v65) = 20;  // 调 取 16 位值低 8 位
    *v32 = &nengine::CNButton::`vftable';  // vftable 复位
    sub_69C780(pMem10);  // 调 初始化 → ·vmt20(nArg2..nArg8
    sub_69C7B0(Blockl, 18, 19, 19, -1, 0, 0);
  }
  else
  {
    pMem10 = nullptr;
  }
  v65 = -1;
  *(uint32_t *)(this + 1220) = pMem10;  // this+1220〔pLvTagCtrl〕
  sub_69A5F0(357, 421);  // 调 设位、sub_69A840 登记
  sub_69A840(*(uint32_t *)(this + 1220));  // this+1220〔pLvTagCtrl〕
  *(uint8_t *)(*(uint32_t *)(this + 1220) + 17) = 0;  // this+1220〔pLvTagCtrl〕
  pMem11 = operator new(0x84u);  // operator new 分配 132 字节
  pMem112 = pMem11;
  pMem22 = pMem11;
  v65 = 21;
  if ( pMem11 != nullptr )  // 若 pMem11 有效（非空）
  {
    Blockm = *(void **)(this + 100);  // this+100 插值终点 Y
    sub_426BD0(pMem11);  // 调 nengine::IControl 构造
    LOBYTE(v65) = 22;  // 调 取 16 位值低 8 位
    *pMem112 = &nengine::CNButton::`vftable';  // vftable 复位
    sub_69C780(v34);  // 调 初始化 → ·vmt20(nArg2..nArg8
    sub_69C7B0(Blockm, 189, 182, 182, -1, 0, 0);  // Blockm=this+100 插值终点 Y
    v35 = v34;
  }
  else
  {
    v35 = nullptr;
  }
  v65 = -1;
  *(uint32_t *)(this + 1232) = v35;  // this+1232〔pNameTagCtrl〕
  sub_69A5F0(63, 424);  // 调 设位、sub_69A840 登记
  *(uint32_t *)(*(uint32_t *)(this + 1232) + 68) = this;  // this+1232〔pNameTagCtrl〕
  sub_69A840(*(uint32_t *)(this + 1232));  // this+1232〔pNameTagCtrl〕
  *(uint32_t *)(this + 1236) = 0;  // this+1236〔field_04D4〕
  v36 = operator new(0x68u);  // operator new 分配 104 字节
  v65 = 23;
  if ( v36 != nullptr )  // 若 v36 有效（非空）
    v37 = sub_426BD0(v36);  // 调 nengine::IControl 构造
  else
    v37 = 0;
  *(uint32_t *)(this + 964) = v37;  // this+964〔nBlobSize〕
  *(uint32_t *)(v37 + 68) = this;
  sub_69A840(*(uint32_t *)(this + 964));  // this+964〔nBlobSize〕
  *(uint32_t *)(this + 972) = 4;  // this+972〔uCfgD972(推断)〕
  *(uint32_t *)(this + 968) = 0;  // this+968〔pBlobData〕
  *(uint32_t *)(this + 980) = 15;  // this+980〔uCfgF980(推断)〕
  *(uint32_t *)(this + 976) = 0;  // this+976〔uCfgE976(推断)〕
  *(uint32_t *)(this + 988) = 10;  // this+988〔uCfgA988(推断)〕
  *(uint32_t *)(this + 984) = 0;  // this+984〔aStateBlk984(推断)〕
  v65 = 24;
  if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
    v38 = sub_431860((char)"Common/Etc/Animation/Shake1.ani", 1);  // 调 动画件构造（资源 id 版）
  else
    v38 = 0;
  v39 = this + 1008;  // this+1008 完成门字节
  *(uint32_t *)(this + 1008) = v38;  // this+1008〔bVineDone1008(推断)〕
  v65 = 25;
  if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
    v40 = sub_431860((char)"Common/Etc/Animation/Shake2.ani", 1);  // 调 动画件构造（资源 id 版）
  else
    v40 = 0;
  v65 = -1;
  *(uint32_t *)(this + 1012) = v40;  // this+1012〔uGrabA1012〕
  for ( Blockf = 2; Blockf != 0; --Blockf )  // 循环：Blockf 从 2 递减到 0
  {
    sub_699070(2);  // clock_bind_domain(clk, newDomainId) (新发现)
    v39 += 4;  // v39=this+1008 完成门字节
  }
  v65 = 26;
  if ( sub_42FCB0(228) != 0 )  // 调 CRT 一次性初始化
    v41 = sub_431860((char)"Common/Etc/Animation/PVPStartCount.ani", 1);  // 调 动画件构造（资源 id 版）
  else
    v41 = 0;
  v65 = -1;
  *(uint32_t *)(this + 1016) = v41;  // this+1016〔uGrabB1016(推断)〕
  sub_699070(2);  // clock_bind_domain(clk, newDomainId) (新发现)
  v42 = 0;
  v43 = this + 1026;
  do
  {
    *(uint8_t *)(v43 - 2) = 0;
    *(uint8_t *)(v43 - 1) = 0;
    *(uint8_t *)v43 = 0;  // *v43 = 0
    *(uint8_t *)(v43 + 1) = 0;
    *(uint32_t *)(v43 + 10) = 0;
    *(uint32_t *)(v43 + 14) = 6;
    *(uint32_t *)(v43 + 18) = 12;
    *(uint32_t *)(v43 + 22) = 0;
    *(uint32_t *)(v43 + 26) = 1600;
    *(uint32_t *)(v43 + 30) = 0;
    *(uint32_t *)(v43 + 34) = 0;
    *(uint32_t *)(v43 + 38) = 0;
    *(uint32_t *)(v43 + 42) = 0;
    *(uint32_t *)(v43 + 46) = 0;
    *(uint32_t *)(v43 + 46) = dword_99FCCC;  // dword_99FCCC＝与字距
    *(uint32_t *)(v43 + 26) = 72;
    *(uint32_t *)(v43 + 10) = v42 != 0 ? 2 : 0;
    *(uint8_t *)v43 = 1;  // *v43 = 1
    *(uint32_t *)(v43 + 2) = -16777216;
    ++v42;
    v43 += 52;
  }
  while ( v42 < 2 );
  v44 = operator new(0x84u);  // operator new 分配 132 字节
  v45 = v44;
  v62 = v44;
  v65 = 27;
  if ( v44 != nullptr )  // 若 v44 有效（非空）
  {
    Blockn = *(void **)(this + 104);  // this+104 插值终点 Z
    sub_426BD0(v44);  // 调 nengine::IControl 构造
    LOBYTE(v65) = 28;  // 调 取 16 位值低 8 位
    *v45 = &nengine::CNButton::`vftable';  // vftable 复位
    sub_69C780(pMem132);  // 调 初始化 → ·vmt20(nArg2..nArg8
    sub_69C7B0(Blockn, 57, 58, 59, -1, 0, 0);  // Blockn=this+104 插值终点 Z
    pMem1322 = pMem132;
  }
  else
  {
    pMem1322 = nullptr;
  }
  v65 = -1;
  *(uint32_t *)(this + 1280) = pMem1322;
  sub_69A5F0(0, 387);  // 调 设位、sub_69A840 登记
  sub_69A840(*(uint32_t *)(this + 1280));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  *(uint8_t *)(*(uint32_t *)(this + 1280) + 16) = 0;
  pMem14 = operator new(0x68u);  // operator new 分配 104 字节
  v65 = 29;
  if ( pMem14 != nullptr )  // 若 pMem14 有效（非空）
    v48 = sub_426BD0(pMem14);  // 调 nengine::IControl 构造
  else
    v48 = 0;
  v65 = -1;
  *(uint32_t *)(this + 1296) = v48;
  sub_69A5F0(446, 61);  // 调 设位、sub_69A840 登记
  fld_510 = *(uint32_t *)(this + 1296);
  *(uint32_t *)(fld_510 + 28) = 24;
  *(uint32_t *)(fld_510 + 32) = 34;
  sub_69A840(*(uint32_t *)(this + 1296));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  v60[0] = 32;
  v60[1] = 42;
  v60[2] = 77;
  v59[0] = -6;
  v59[1] = -5;
  v59[2] = -2;
  pThis_504 = this + 1284;  // this+1284〔nEffectCount1284〕
  for ( Blockg = 0; Blockg < 3; ++Blockg )  // 循环：Blockg 从 0 递增到 3
  {
    pMem15 = operator new(0x2Cu);  // operator new 分配 44 字节
    pMem152 = pMem15;
    pMem153 = pMem15;
    v65 = 30;
    if ( pMem15 != nullptr )  // 若 pMem15 有效（非空）
    {
      fld_64 = *(uint32_t *)(this + 104);  // this+104〔nTimerEnd(推断)〕
      pMem22 = (void *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
      pMem15[4] = 0;
      LOBYTE(v65) = 31;  // 调 取 16 位值低 8 位
      *(uint32_t *)pMem15 = &nengine::CNNumberSet::`vftable';  // vftable 复位
      sub_699E20(v50);  // 调 本体初始化 + sub_699E40(a2..a5)
      sub_699E40(v62, v63, v60[Blockg], 4);
      v52 = v51;
    }
    else
    {
      v52 = nullptr;
    }
    v53 = v64;
    v54 = v59[Blockg];
    *(uint32_t *)v64 = v52;  // *v64 = v52
    *((uint32_t *)v52 + 10) = v54;
    *(uint32_t *)(*(uint32_t *)v53 + 36) = 2;
    v55 = *(uint32_t *)v53;
    v65 = -1;
    *(uint8_t *)(v55 + 24) = 0;
    v64 = v53 + 4;
  }
  *(uint8_t *)(this + 1416) = 0;
  v56 = operator new(0x84u);  // operator new 分配 132 字节
  v61 = v56;
  v65 = 32;
  if ( v56 != nullptr )  // 若 v56 有效（非空）
  {
    Blocko = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 84);  // nengine::CNSlider 全局实例
    sub_426BD0(v56);  // 调 nengine::IControl 构造
    LOBYTE(v65) = 33;  // 调 取 16 位值低 8 位
    *v56 = &nengine::CNButton::`vftable';  // vftable 复位
    sub_69C780(pMem16);  // 调 初始化 → ·vmt20(nArg2..nArg8
    sub_69C7B0(Blocko, 24, 24, 26, 24, 0, 0);
    pMem162 = pMem16;
  }
  else
  {
    pMem162 = nullptr;
  }
  v65 = -1;
  *(uint32_t *)(this + 96) = pMem162;  // this+384 = 动画件名 SSO 容量判据
  sub_69A5F0(605, 23);  // 调 设位、sub_69A840 登记
  *(uint32_t *)(*(uint32_t *)(this + 96) + 68) = this;  // this+384 = 动画件名 SSO 容量判据
  *(uint8_t *)(*(uint32_t *)(this + 96) + 16) = 0;  // this+384 = 动画件名 SSO 容量判据
  result = sub_69A840(*(uint32_t *)(this + 96));  // this+384 = 动画件名 SSO 容量判据
  *(uint8_t *)(this + 1445) = 0;
  *(uint8_t *)(this + 1446) = 0;
  return result;  // result=this+384 动画件名 SSO 容量判据
}


// ============================================================
// 【分区 7】选角界面辅助（0x46ABB0-0x46BCB0）
// 光标/条目状态 0x46B0E0、条目计数 0x46B060 等。
// ============================================================
// ------------------------------------------------------------
// 0x46ABB0 sub_46ABB0 —— 界面管理器逐槽析构清理
// 对 this+8、+12 起 6 件、+36 起一批、+96 等持有控件逐个以 vt 槽 0（析构，实参 1）释放并写 0。
// 其中含 sub_42AF90 帧对象析构（帧数组与元素数组）。
// ------------------------------------------------------------
int /*thiscall*/ sub_46ABB0(int this)  // 函数: 界面管理器逐槽析构清理
{
  void (/*thiscall*/ ***pThis_8)(uint32_t, int); // ecx
  uint32_t *pThis_C; // esi
  int i; // ebx
  uint32_t *pThis_24; // esi
  int j; // ebx
  uint32_t *pThis_3C; // esi
  int k; // ebx
  void (/*thiscall*/ ***pThis_50)(uint32_t, int); // ecx
  uint32_t *pThis_54; // esi
  int m; // ebx
  uint32_t *pThis_CC; // esi
  int n; // ebx
  int fld_DC; // esi
  void ***pThis_23C; // esi
  void **v16; // ebx
  void ***pThis_3F0; // esi
  void (/*thiscall*/ ***v18)(uint32_t, int); // ecx
  void **v19; // ebx
  bool v20; // zf
  int result; // eax
  int (/*thiscall*/ ***pThis_78)(uint32_t, int); // ecx
  void **fld_3F8; // esi
  int (/*thiscall*/ ***pThis_3C4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_4C4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_4D0)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_510)(uint32_t, int); // ecx
  int (/*thiscall*/ ***pThis_500)(uint32_t, int); // ecx
  uint32_t *pThis_504; // esi
  int jj; // ebx
  int (/*thiscall*/ ***pThis_60)(uint32_t, int); // ecx
  int ii; // [esp+4h] [ebp-4h]
  int v33; // [esp+4h] [ebp-4h]

  pThis_8 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8);  // this+32〔nHeight(推断)〕
  if ( pThis_8 != nullptr )  // 若 pThis_8 有效（非空）
    (**pThis_8)(pThis_8, 1);  // 调 pThis_8 的虚函数（vt+0）
  *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  pThis_C = (uint32_t *)(this + 12);  // this+12〔nSkillRec12(推断)〕等 2 字段
  for ( i = 6; i != 0; --i )  // 循环：i 从 6 递减到 0
  {
    if ( *pThis_C != 0 )  // pThis_C=this+12 nSkillRec12
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_C)(*pThis_C, 1);  // pThis_C=this+12 nSkillRec12
    *pThis_C++ = 0;  // pThis_C=this+12 nSkillRec12
  }
  pThis_24 = (uint32_t *)(this + 36);  // this+144 = pFrameList144
  for ( j = 6; j != 0; --j )  // 循环：j 从 6 递减到 0
  {
    if ( *pThis_24 != 0 )  // pThis_24=this+144 第 4 组·+1040 增量子倍率
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_24)(*pThis_24, 1);  // pThis_24=this+144 第 4 组·+1040 增量子倍率
    *pThis_24++ = 0;  // pThis_24=this+144 第 4 组·+1040 增量子倍率
  }
  pThis_3C = (uint32_t *)(this + 60);  // this+240 = 基类时刻同步参数 B
  for ( k = 5; k != 0; --k )  // 循环：k 从 5 递减到 0
  {
    if ( *pThis_3C != 0 )  // pThis_3C=this+240 动画同步参数 B
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_3C)(*pThis_3C, 1);  // pThis_3C=this+240 动画同步参数 B
    *pThis_3C++ = 0;  // pThis_3C=this+240 动画同步参数 B
  }
  pThis_50 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 80);  // this+80 关联角色对象
  if ( pThis_50 != nullptr )  // 若 pThis_50 有效（非空）
    (**pThis_50)(pThis_50, 1);  // 调 pThis_50 的虚函数（vt+0）
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  pThis_54 = (uint32_t *)(this + 84);  // this+84〔pFxObjA(推断)〕
  for ( m = 3; m != 0; --m )  // 循环：m 从 3 递减到 0
  {
    if ( *pThis_54 != 0 )  // pThis_54=this+84 pFxObjA
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_54)(*pThis_54, 1);  // pThis_54=this+84 pFxObjA
    *pThis_54++ = 0;  // pThis_54=this+84 pFxObjA
  }
  pThis_CC = (uint32_t *)(this + 204);  // this+204〔pSubAnim204(推断)〕
  for ( n = 4; n != 0; --n )  // 循环：n 从 4 递减到 0
  {
    if ( *pThis_CC != 0 )  // pThis_CC=this+204 pSubAnim204
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_CC)(*pThis_CC, 1);  // pThis_CC=this+204 pSubAnim204
    *pThis_CC++ = 0;  // pThis_CC=this+204 pSubAnim204
  }
  fld_DC = *(uint32_t *)(this + 220);  // this+220〔nSnapDst220(推断)〕
  if ( fld_DC != 0 )  // fld_DC=this+220 nSnapDst220
  {
    sub_42AF90(*(void ***)(this + 220));  // 调 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_DC, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
  }
  *(uint32_t *)(this + 220) = 0;  // this+220〔nSnapDst220(推断)〕
  pThis_23C = (void ***)(this + 572);  // this+572 最后一次受击
  for ( ii = 3; ii != 0; --ii )  // 循环：ii 从 3 递减到 0
  {
    v16 = *pThis_23C;  // pThis_23C=this+572 最后一次受击
    if ( *pThis_23C != nullptr )  // pThis_23C=this+572 最后一次受击
    {
      sub_42AF90(*pThis_23C);  // 调 帧对象析构（帧数组 + 元素数组）
      sub_657740(v16, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_23C++ = nullptr;  // pThis_23C=this+572 最后一次受击
  }
  pThis_3F0 = (void ***)(this + 1008);  // this+1008 完成门字节
  v33 = 2;
  do
  {
    v18 = (void (/*thiscall*/ ***)(uint32_t, int))*(pThis_3F0 - 224);  // pThis_3F0=this+1008 完成门字节
    if ( v18 != nullptr )  // 若 v18 有效（非空）
      (**v18)(v18, 1);  // 调 v18 的虚函数（vt+0）
    v19 = *pThis_3F0;  // pThis_3F0=this+1008 完成门字节
    v20 = *pThis_3F0 == nullptr;  // pThis_3F0=this+1008 完成门字节
    *(pThis_3F0 - 224) = nullptr;  // pThis_3F0=this+1008 完成门字节
    if ( !v20 )
    {
      sub_42AF90(v19);  // 调 帧对象析构（帧数组 + 元素数组）
      sub_657740(v19, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_3F0++ = nullptr;  // pThis_3F0=this+1008 完成门字节
    result = v33 - 1;
    v33 = result;
  }
  while ( result != 0 );
  pThis_78 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 120);  // this+120〔pAnimObj〕
  if ( pThis_78 != nullptr )  // 若 pThis_78 有效（非空）
    result = (**pThis_78)(pThis_78, 1);  // 调 pThis_78 的虚函数（vt+0）
  fld_3F8 = *(void ***)(this + 1016);  // this+1016 【推断】抓取参数 B
  *(uint32_t *)(this + 120) = 0;  // this+120〔pAnimObj〕
  if ( fld_3F8 != nullptr )  // 若 fld_3F8 有效（非空）
  {
    sub_42AF90(fld_3F8);  // 调 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_3F8, 228);  // 调 池化结点弹出（写魔术标记后挂入链头）
  }
  pThis_3C4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 964);  // this+964〔nBlobSize〕
  *(uint32_t *)(this + 1016) = 0;  // this+1016〔uGrabB1016(推断)〕
  if ( pThis_3C4 != nullptr )  // 若 pThis_3C4 有效（非空）
    result = (**pThis_3C4)(pThis_3C4, 1);  // 调 pThis_3C4 的虚函数（vt+0）
  pThis_4C4 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 1220);  // this+1220〔pLvTagCtrl〕
  *(uint32_t *)(this + 964) = 0;  // this+964〔nBlobSize〕
  if ( pThis_4C4 != nullptr )  // 若 pThis_4C4 有效（非空）
    result = (**pThis_4C4)(pThis_4C4, 1);  // 调 pThis_4C4 的虚函数（vt+0）
  pThis_4D0 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 1232);  // this+1232〔pNameTagCtrl〕
  *(uint32_t *)(this + 1220) = 0;  // this+1220〔pLvTagCtrl〕
  if ( pThis_4D0 != nullptr )  // 若 pThis_4D0 有效（非空）
    result = (**pThis_4D0)(pThis_4D0, 1);  // 调 pThis_4D0 的虚函数（vt+0）
  pThis_510 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 1296);
  *(uint32_t *)(this + 1232) = 0;  // this+1232〔pNameTagCtrl〕
  if ( pThis_510 != nullptr )  // 若 pThis_510 有效（非空）
    result = (**pThis_510)(pThis_510, 1);  // 调 pThis_510 的虚函数（vt+0）
  pThis_500 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 1280);
  *(uint32_t *)(this + 1296) = 0;
  if ( pThis_500 != nullptr )  // 若 pThis_500 有效（非空）
    result = (**pThis_500)(pThis_500, 1);  // 调 pThis_500 的虚函数（vt+0）
  *(uint32_t *)(this + 1280) = 0;
  pThis_504 = (uint32_t *)(this + 1284);  // this+1284〔nEffectCount1284〕
  for ( jj = 3; jj != 0; --jj )  // 循环：jj 从 3 递减到 0
  {
    if ( *pThis_504 != 0 )  // pThis_504=this+1284 nEffectCount1284
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_504)(*pThis_504, 1);  // pThis_504=this+1284 nEffectCount1284
    *pThis_504++ = 0;  // pThis_504=this+1284 nEffectCount1284
  }
  pThis_60 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 96);  // this+384 = 动画件名 SSO 容量判据
  if ( pThis_60 != nullptr )  // 若 pThis_60 有效（非空）
    result = (**pThis_60)(pThis_60, 1);  // 调 pThis_60 的虚函数（vt+0）
  *(uint32_t *)(this + 96) = 0;  // this+384 = 动画件名 SSO 容量判据
  return result;
}


// ------------------------------------------------------------
// 0x46AE40 sub_46AE40 —— 子对象数值写入（clong 赋值）
// sub_41A5E0 读 uArg2 后 sub_41A590 写入 this（P24 防篡改读写闭环）。
// ------------------------------------------------------------
int /*thiscall*/ sub_46AE40(void *this, unsigned int uArg2)  // 函数: 子对象数值写入（clong 赋值）
{
  int v3; // esi
  int v4; // edx

  v3 = sub_41A5E0(uArg2);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)this, v4, v3);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  return v3;
}



// ------------------------------------------------------------
// 0x46AE70 sub_46AE70 —— 管理器状态批量复位
// 仅当 +4 为 0（未激活）时执行：+12..+272 一大批槽清零。
// 另置 +92/+172 为 -1（下标哨兵）、+180 为 4（默认档）、+48..+56 显示标志清零。
// ------------------------------------------------------------
int /*thiscall*/ sub_46AE70(int this)  // 函数: 管理器状态批量复位
{
  int result; // eax
  uint32_t *pThis_D8; // esi
  uint32_t *pThis_D0; // edx
  int i; // [esp+0h] [ebp-4h]

  result = 0;
  if ( *(uint8_t *)(this + 4) == 0 )  // this+4〔宿主对象〕等 2 字段
  {
    *(uint32_t *)(this + 92) = -1;  // this+92〔pFxObjC(推断)〕等 2 字段
    *(uint32_t *)(this + 172) = -1;  // this+688 = 表现/名字快照[2]
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
    *(uint8_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    *(uint8_t *)(this + 49) = 0;  // this+49〔bUdpReported〕
    *(uint8_t *)(this + 50) = 0;  // this+50〔bCharSelSent〕
    *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
    *(uint8_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
    *(uint8_t *)(this + 96) = 0;  // this+384 = 动画件名 SSO 容量判据
    *(uint32_t *)(this + 100) = 0;  // this+100〔bEnchantDone(推断)〕
    *(uint32_t *)(this + 104) = 0;  // this+104〔nTimerEnd(推断)〕
    *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
    *(uint32_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
    *(uint32_t *)(this + 116) = 0;  // this+116〔会话上下文〕
    *(uint32_t *)(this + 176) = 0;  // this+704 = 表现/名字快照[24]
    *(uint32_t *)(this + 180) = 4;  // this+180〔nRadius(推断)〕
    *(uint32_t *)(this + 184) = 0;  // this+184〔bSingleTarget(推断)〕
    *(uint32_t *)(this + 188) = 0;  // this+188〔nStatusIdx(推断)〕
    *(uint32_t *)(this + 192) = 0;  // this+192〔nDlgId(推断)〕
    *(uint32_t *)(this + 196) = 0;
    *(uint32_t *)(this + 200) = 0;  // this+200〔nMainState(推断)〕
    *(uint32_t *)(this + 204) = 0;  // this+204〔pSubAnim204(推断)〕
    pThis_D8 = (uint32_t *)(this + 216);  // this+216〔bField216(推断)〕
    pThis_D0 = (uint32_t *)(this + 208);  // this+208〔nField208(推断)〕
    for ( i = 2; i != 0; --i )  // 循环：i 从 2 递减到 0
    {
      *pThis_D0 = 0;  // pThis_D0=this+208 nField208
      *pThis_D8 = 0;  // pThis_D8=this+216 bField216
      pThis_D8[1] = 0;  // pThis_D8=this+216 bField216
      ++pThis_D0;  // pThis_D0=this+208 nField208
      pThis_D8 += 2;  // pThis_D8=this+216 bField216
    }
    *(uint32_t *)(this + 232) = 0;  // this+232〔bSyncFlag〕
    *(uint32_t *)(this + 236) = 0;  // this+944 = 名字已播出标志
    *(uint32_t *)(this + 240) = 0;  // this+240〔nSyncArgB〕
    *(uint32_t *)(this + 244) = 0;  // this+976 = uCfgE976
    *(uint32_t *)(this + 248) = 0;  // this+992 = uCfgB992
    *(uint32_t *)(this + 252) = 0;  // this+252〔nQuad2〕
    *(uint32_t *)(this + 256) = 0;  // this+256〔bQuad3〕
    *(uint32_t *)(this + 260) = 0;  // this+260〔nQuad4〕
    *(uint32_t *)(this + 264) = 0;  // this+264〔nAnimHandle(推断)〕
    *(uint32_t *)(this + 268) = 0;  // this+268〔field_10C〕
    *(uint32_t *)(this + 272) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x46AF70 sub_46AF70 —— 鼠标坐标转 8 格下标
// 按 pt 命中 4 列 2 行（x=125*i+64..189，y 上排 46..226 下排 226..406）返回 0..7，全不中返回 -1。
// ------------------------------------------------------------
int sub_46AF70()  // 函数: 鼠标坐标转 8 格下标
{
  int result; // eax

  result = 0;
  while ( pt.x < 125 * (result % 4) + 64
       || pt.x >= 125 * (result % 4) + 189
       || pt.y < (result >= 4 ? 226 : 46)  // 鼠标坐标转 8 格下标
       || pt.y >= (result >= 4 ? 406 : 226) )
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x46AFD0 sub_46AFD0 —— 去空格小写归一化
// 逐字符把 pArg2 拷入 uArg1，跳过空格(32) 并 tolower，末尾补 0；供频道名比较。
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_46AFD0(uint8_t *uArg1, const char *pArg2)  // 函数: 去空格小写归一化
{
  unsigned int v2; // esi
  int v3; // ebx
  char v4; // al
  unsigned int result; // eax
  char v6; // cl

  v2 = 0;
  v3 = 0;
  if ( strlen(pArg2) != 0 )  // 调 返回字符串长度（逐字节扫描）
  {
    do
    {
      v4 = pArg2[v2];
      if ( v4 != 32 )
        uArg1[v3++] = tolower(v4);  // 调 按当前 locale 的 ctype 表映射为小写
      ++v2;
      result = strlen(pArg2);  // 调 返回字符串长度（逐字节扫描）
    }
    while ( v2 < result );
    uArg1[v3] = v6;
  }
  else
  {
    *uArg1 = 0;
    return (unsigned int)uArg1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x46B040 sub_46B040 —— 144 字节项数组计数
// 返回 (this+2 - this+1)/144，即频道与角色条目（144 字节每项）个数。
// ------------------------------------------------------------
int /*thiscall*/ sub_46B040(int *this)  // 函数: 144 字节项数组计数
{
  int result; // eax

  result = *(this + 1);  // this+4 = pHostObj
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(this + 2) - result) / 144;  // this+8 = 技能槽记录首字
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x46B060 sub_46B060 —— 4 字节项数组计数
// 返回 (this+17 - this+16) 右移 2，空则 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_46B060(uint32_t *this)  // 函数: 4 字节项数组计数
{
  int fld_e16; // edx

  fld_e16 = *(this + 16);  // this+64〔apServerTabBtn(推断)〕
  if ( fld_e16 != 0 )  // fld_e16=this+64 apServerTabBtn
    return (*(this + 17) - fld_e16) >> 2;  // this+68〔nCharCount(推断)〕
  else
    return 0;
}



// ------------------------------------------------------------
// 0x46B080 sub_46B080 —— clong 构造与初值写入
// sub_41A630 起构后写 vftbl_clong，再 sub_41A5E0(uArg2) 与 sub_41A590 设初值；与 ·sub_461750 同构。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_46B080(uint32_t *this, unsigned int uArg2)  // 函数: clong 构造与初值写入
{
  int v3; // eax
  int v4; // edx

  sub_41A630((unsigned int)this);  // 调 防篡改字段读校验（crypt 逆运算链）
  *this = &vftbl_clong;  // 构造装配 vftable：clong
  v3 = sub_41A5E0(uArg2);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590((unsigned int)this, v4, v3);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  return this;
}



// ------------------------------------------------------------
// 0x46B0E0 sub_46B0E0 —— 频道列表选中态 setter
// nArg2 超出 +16/+17 项数则不动；否则写 +23，并把 +27 对象 +17 与 +28 对象 +16 反向置位（-1 视为取消）。
// 末尾 sub_44E850(dword_8F8528, 30) 通知刷新。
// ------------------------------------------------------------
char /*thiscall*/ sub_46B0E0(uint32_t *this, int nArg2)  // 函数: 频道列表选中态 setter
{
  int fld_e16; // edx
  int fld_e17; // eax

  fld_e16 = *(this + 16);  // this+64〔apServerTabBtn(推断)〕
  if ( fld_e16 != 0 )  // fld_e16=this+64 apServerTabBtn
    fld_e17 = (*(this + 17) - fld_e16) >> 2;  // this+68〔nCharCount(推断)〕
  else
    fld_e17 = 0;  // fld_e17=this+68 nCharCount
  if ( nArg2 < fld_e17 )  // fld_e17=this+68 nCharCount
  {
    *(this + 23) = nArg2;  // this+92 = pFxObjC
    if ( nArg2 == -1 )
    {
      *(uint8_t *)(*(this + 27) + 17) = 0;  // this+108〔nAdd108(推断)〕
      *(uint8_t *)(*(this + 28) + 16) = 0;  // this+112 = pHostComp
    }
    else
    {
      *(uint8_t *)(*(this + 27) + 17) = 1;  // this+108〔nAdd108(推断)〕
      *(uint8_t *)(*(this + 28) + 16) = 1;  // this+112 = pHostComp
    }
    LOBYTE(fld_e17) = sub_44E850(dword_8F8528, 30);  // 调 按池号批量回收活动对象
  }
  return fld_e17;  // fld_e17=this+68 nCharCount
}



// ------------------------------------------------------------
// 0x46B150 sub_46B150 —— 频道栏选中恢复与提示文本
// +276 标志（取消或回滚）时列表非空选末项、否则选 -1。
// 否则读调试配置 sub_48B740(11) 决定选中，再 sub_568A70(byte_99FCD0, byte_99FCD1) 组装条目。
// 与 [none]（自证）比对（sub_40BF00），命中则以 sub_422E70(1244) 格式串 sprintf 后 sub_44E8D0(dword_8F8528, 0x1B) 作 UI 文本通知。
// ------------------------------------------------------------
char /*thiscall*/ sub_46B150(int this)  // 函数: 频道栏选中恢复与提示文本
{
  char fld_114; // al
  int fld_40; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // esi
  int v7; // esi
  char *v8; // eax
  char Buffer[256]; // [esp+4h] [ebp-104h] BYREF
  int dword_796E502; // [esp+104h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  fld_114 = *(uint8_t *)(this + 276);  // this+276〔pMapEntry〕
  *(uint8_t *)(this + 56) = 1;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  if ( fld_114 != 0 )  // fld_114=this+276 pMapEntry
  {
    fld_40 = *(uint32_t *)(this + 64);  // this+256 = 基类四元组字节槽 3
    if ( fld_40 != 0 )  // fld_40=this+256 参数灌入槽 3
      LOBYTE(v4) = sub_46B0E0((uint32_t *)this, ((*(uint32_t *)(this + 68) - fld_40) >> 2) - 1);  // 调 频道列表选中态 setter
    else
      LOBYTE(v4) = sub_46B0E0((uint32_t *)this, -1);  // 调 频道列表选中态 setter
  }
  else
  {
    v5 = sub_48B740(11);  // 调 调试配置项读取并夹取上下限
    sub_46B0E0((uint32_t *)this, v5);  // 调 频道列表选中态 setter
    v4 = sub_568A70((uint8_t)byte_99FCD0, (uint8_t)byte_99FCD1);  // 调 频道条目组装（568940/568800）
    v6 = v4;
    if ( v4 != 0 )
    {
      v4 = sub_40BF00((std::_String_base *)(v4 + 32), 0, *(uint32_t *)(v4 + 52), "[none]", 6u);  // 调 std::string 比较（memcmp + 长度序；越界走 _Xran）
      if ( v4 != 0 )
      {
        if ( *(uint32_t *)(v6 + 84) < 0x10u )
          v7 = v6 + 64;
        else
          v7 = *(uint32_t *)(v6 + 64);
        v8 = sub_422E70(1244);  // 调 存 CStringManager::getStr 取本地化串
        sprintf(Buffer, v8, v7);  // 调 格式化到缓冲
        LOBYTE(v4) = sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);  // 调 对象池借出（按池号取可用对象）
      }
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x46B250 sub_46B250 —— 频道名忽略大小写查找
// 把 pArg1 与 dword_98BA0C..98BA10 指针数组每项（sub_41ACF0 取串）分别归一化后 strcmp，命中返回非 0。
// ------------------------------------------------------------
char /*stdcall*/ sub_46B250(const char *pArg1)  // 函数: 频道名忽略大小写查找
{
  char *v1; // edi
  const char *v2; // eax
  char psz2[64]; // [esp+Ch] [ebp-84h] BYREF
  char psz[64]; // [esp+4Ch] [ebp-44h] BYREF
  int dword_796E502; // [esp+8Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  sub_46AFD0(psz2, pArg1);  // 调 去空格小写归一化
  v1 = (char *)dword_98BA0C;
  if ( dword_98BA0C == (void *)dword_98BA10 )
    return 0;
  while ( 1 )  // 无限循环
  {
    v2 = (const char *)sub_41ACF0(v1);  // 调 驻留串句柄 → 字符串指针
    sub_46AFD0(psz, v2);  // 调 去空格小写归一化
    if ( strcmp(psz2, psz) == 0 )  // 调 串比较
      break;
    v1 += 4;
    if ( v1 == (char *)dword_98BA10 )
      return 0;
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x46B310 sub_46B310 —— 频道列表行绘制
// nArg2 等于 +44（当前选中）时进入；sub_699000(this+8)*0.000033333334 得三万分之一秒相位。
// sub_491530/491630 包夹下绘 0/1 号图于 (149,10) 与 59/41 号图。
// 文本走 Lv.%d %s（自证），sub_46AF70 判定鼠标所在格以加亮光标。
// ------------------------------------------------------------
void /*thiscall*/ sub_46B310(int this, int nArg2)  // 函数: 频道列表行绘制
{
  int pObj12; // eax
  int pObj2; // eax
  int pObj8; // eax
  int pObj6; // eax
  int pObj4; // eax
  int fld_54; // eax
  int v9; // esi
  int v10; // ebx
  int pObj13; // eax
  int pObj7; // eax
  int v13; // esi
  int bInputEnable; // ecx  | +0x0038 → ★ 键盘输入使能（CNEntranceModule；va=0046C300）
  int fld_3C; // eax
  int i; // ebx
  int pObj; // eax
  int bInputEnable_; // ecx  | +0x0038 → ★ 键盘输入使能（CNEntranceModule；va=0046C300）
  int v19; // ebx
  int fld_383; // ecx  | +0x0038 → ★ 键盘输入使能（CNEntranceModule；va=0046C300）
  int fld_48; // eax
  int v22; // eax
  int v23; // esi
  int fld_482; // eax
  int pObj10; // eax
  int pObj3; // eax
  int fld_C4; // ecx
  int pObj14; // eax
  int pObj9; // eax
  int j; // esi
  int pObj5; // eax
  int fld_C8; // ecx
  int fld_CC; // ecx
  int v34; // esi
  DWORD Time; // eax
  uint8_t v36; // bl
  int v37; // eax
  int v38; // esi
  DWORD dwNow; // eax
  uint8_t v40; // bl
  int pObj11; // eax
  int v42; // [esp-4h] [ebp-20h]
  int v43; // [esp+Ch] [ebp-10h]
  int v44; // [esp+10h] [ebp-Ch]
  int fld_3C2; // [esp+14h] [ebp-8h]
  float pThis_8; // [esp+24h] [ebp+8h]
  int v47; // [esp+24h] [ebp+8h]
  float pThis_82; // [esp+24h] [ebp+8h]

  if ( nArg2 == *(uint32_t *)(this + 44) )  // this+44〔nExpireMs(推断)〕等 2 字段
  {
    pObj12 = sub_418DD0(0);  // 调 资源句柄 (101)
    if ( pObj12 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pObj12 + 152))(pObj12, 0, 0, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pThis_8 = (double)sub_699000(this + 8) * 0.000033333334;  // clock_now(clk)
    sub_491530(1, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    pObj2 = sub_418DD0(1);  // 调 资源句柄 (101)
    if ( pObj2 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, float, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 调用虚函数（虚表槽 +128）
        pObj2,
        149,
        10,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,  // 常量 1.0f
        1065353216,  // 常量 1.0f
        COERCE_FLOAT(LODWORD(pThis_8)),  // 调 取 64 位值低 32 位
        -1,
        1126891520,
        1126891520);
    sub_491630(1);  // 调 渲染层状态还原（与 ·0x491530 配对）
    pObj8 = sub_418DD0(0);  // 调 资源句柄 (101)
    if ( pObj8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, 59, 41, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    if ( *(uint8_t *)(*(uint32_t *)(this + 104) + 16) != 0 )  // this+104〔nTimerEnd(推断)〕
    {
      pObj6 = sub_418DD0(12);  // 调 资源句柄 (101)
      if ( pObj6 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, 267, 416, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    }
    pObj4 = sub_418DD0(16);  // 调 资源句柄 (101)
    if ( pObj4 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 222, 8, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    fld_54 = *(uint32_t *)(this + 84);  // this+84〔pFxObjA(推断)〕
    if ( fld_54 != -1 )  // fld_54=this+84 pFxObjA
    {
      v9 = 125 * (fld_54 % 4) + 64;
      v10 = fld_54 >= 4 ? 226 : 46;  // fld_54=this+84 pFxObjA
      pObj13 = sub_418DD0(14);  // 调 资源句柄 (101)
      if ( pObj13 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj13 + 152))(pObj13, v9, v10, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      sub_491530(1, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      pObj7 = sub_418DD0(15);  // 调 资源句柄 (101)
      if ( pObj7 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v9 + 3, v10 + 3, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
      sub_491630(1);  // 调 渲染层状态还原（与 ·0x491530 配对）
    }
    v13 = sub_46AF70(this - 8);  // 调 鼠标坐标转 8 格下标
    if ( v13 != -1 )
    {
      bInputEnable = *(uint32_t *)(this + 56);  // this+56〔pCmdVecCap56(推断)〕等 2 字段
      fld_3C = bInputEnable != 0 ? (*(uint32_t *)(this + 60) - bInputEnable) >> 2 : 0;  // this+240 = 基类时刻同步参数 B
      if ( v13 < fld_3C && v13 != *(uint32_t *)(this + 84) )  // this+84〔pFxObjA(推断)〕
      {
        sub_491530(1, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
        v42 = sub_418DD0(21);  // 调 资源句柄 (101)
        sub_40FC80(125 * (v13 % 4) + 67, v13 >= 4 ? 229 : 49, v42);  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
        sub_491630(1);  // 调 渲染层状态还原（与 ·0x491530 配对）
      }
    }
    sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    for ( i = 0; i < 8; ++i )  // 循环：i 从 0 递增到 8
    {
      if ( i == *(uint32_t *)(this + 84) )  // this+84〔pFxObjA(推断)〕
        pObj = sub_418DD0(13);  // 调 资源句柄 (101)
      else
        pObj = sub_418DD0(20);  // 调 资源句柄 (101)
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          pObj,
          125 * (i & 3) + 67,
          i >= 4 ? 335 : 155,
          dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
    }
    sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
    bInputEnable_ = *(uint32_t *)(this + 56);  // this+56〔pCmdVecCap56(推断)〕等 2 字段
    v19 = 0;
    if ( bInputEnable_ != 0 )  // fld_382=this+56 pCmdVecCap56
      fld_3C2 = (*(uint32_t *)(this + 60) - bInputEnable_) >> 2;  // this+240 = 基类时刻同步参数 B
    else
      fld_3C2 = 0;  // fld_3C2=this+240 pBtnScrollDown
    if ( fld_3C2 > 0 )  // fld_3C2=this+240 pBtnScrollDown
    {
      v47 = 0;
      do
      {
        fld_383 = *(uint32_t *)(*(uint32_t *)(this + 56) + 4 * v19);  // this+56〔pCmdVecCap56(推断)〕等 2 字段
        v43 = *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_383 + 344))(fld_383);  // 调用虚函数（虚表槽 +344）
        sub_4938F0(v43);  // 调 ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
        sub_491D00(dword_79C0B0, 125 * (v19 & 3) + 126, v19 >= 4 ? 358 : 178, 0.0);  // 调 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 112);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
        fld_48 = v47 + *(uint32_t *)(this + 72);  // this+72〔nSnapshot72(推断)〕等 2 字段
        if ( *(uint32_t *)(fld_48 + 24) < 0x10u )  // fld_48=this+72 nSnapshot72
          v44 = fld_48 + 4;  // fld_48=this+72 nSnapshot72
        else
          v44 = *(uint32_t *)(fld_48 + 4);  // fld_48=this+72 nSnapshot72
        v22 = sub_41A5E0(fld_48 + 37);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
        (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          125 * (v19 & 3) + 67,
          v19 >= 4 ? 375 : 195,
          -7030319,
          "Lv.%d %s",  // 日志模板 Lv.%d %s
          v22,
          v44);
        v23 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 = 文本/图像绘制对象
        fld_482 = sub_4B0EC0(*(uint32_t *)(*(uint32_t *)(this + 72) + v47 + 28), *(uint32_t *)(*(uint32_t *)(this + 72) + v47 + 32));  // 调 表记录字符串取值（28 字节/条）
        (*(void (**)(int, int, int, int, const char *, ...))(v23 + 80))(  // 调用虚函数（虚表槽 +80）
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          125 * (v19 & 3) + 67,
          v19 >= 4 ? 386 : 206,
          -7030319,
          "%s",
          fld_482);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
        ++v19;
        v47 += 144;
      }
      while ( v19 < fld_3C2 );  // fld_3C2=this+240 pBtnScrollDown
    }
  }
  else if ( nArg2 == *(uint32_t *)(this + 168) )  // this+672 = 拾取/交互目标有效标志
  {
    pObj10 = sub_418DD0(0);  // 调 资源句柄 (101)
    if ( pObj10 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pObj10 + 152))(pObj10, 0, 0, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pThis_82 = (double)sub_699000(this + 8) * 0.000033333334;  // clock_now(clk)
    sub_491530(1, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    pObj3 = sub_418DD0(1);  // 调 资源句柄 (101)
    if ( pObj3 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, float, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 调用虚函数（虚表槽 +128）
        pObj3,
        149,
        10,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,  // 常量 1.0f
        1065353216,  // 常量 1.0f
        COERCE_FLOAT(LODWORD(pThis_82)),  // 调 取 64 位值低 32 位
        -1,
        1126891520,
        1126891520);
    sub_491630(1);  // 调 渲染层状态还原（与 ·0x491530 配对）
    if ( *(uint32_t *)(this + 172) != 4 )  // this+688 = 表现/名字快照[2]
    {
      fld_C4 = *(uint32_t *)(this + 196);
      if ( fld_C4 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)fld_C4 + 152))(fld_C4, 0, 0, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    }
    pObj14 = sub_418DD0(10);  // 调 资源句柄 (101)
    if ( pObj14 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj14 + 152))(pObj14, 242, 352, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    pObj9 = sub_418DD0(2);  // 调 资源句柄 (101)
    if ( pObj9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj9 + 152))(pObj9, 89, 377, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    for ( j = 404; j < 556; j += 76 )
    {
      pObj5 = sub_418DD0(3);  // 调 资源句柄 (101)
      if ( pObj5 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, j, 388, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    }
    if ( *(uint32_t *)(this + 172) != 4 )  // this+688 = 表现/名字快照[2]
    {
      sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      fld_C8 = *(uint32_t *)(this + 200);  // this+200〔nMainState(推断)〕
      if ( fld_C8 != 0 )  // fld_C8=this+200 nMainState
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)fld_C8 + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          fld_C8,  // fld_C8=this+200 nMainState
          *(uint32_t *)(this + 208),  // this+208 【推断】子链状态槽
          *(uint32_t *)(this + 212),  // this+212 【推断】子链状态槽
          dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
      sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
      fld_CC = *(uint32_t *)(this + 204);  // this+204〔pSubAnim204(推断)〕
      if ( fld_CC != 0 )  // fld_CC=this+204 pSubAnim204
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)fld_CC + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
          fld_CC,  // fld_CC=this+204 pSubAnim204
          *(uint32_t *)(this + 216),  // this+216 【推断】子链标志字节
          *(uint32_t *)(this + 220),  // this+220 己方就绪标签控件
          dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
    }
  }
  else if ( nArg2 == *(uint32_t *)(this + 96) )  // this+384 = 动画件名 SSO 容量判据
  {
    if ( *(uint8_t *)(this + 48) != 0 && (uint8_t)sub_484F10(this + 52) != 0 )  // 调 32 字节对象列表空判定（+4 为 0 或元素数 0）
    {
      v34 = (uint8_t)sub_43BCB0(nArg2) != 0 ? 255 : 150;  // 调 焦点窗口判定（三选）
      Time = timeGetTime();  // 调 取系统毫秒时刻
      v36 = sub_42B420(0, v34, Time, 400);  // 调 往返插值（三角波）
      sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      v37 = sub_418DD0(22);  // 调 资源句柄 (101)
      sub_43B560(54, 402, v37, 1065353216, 1065353216, 0, (v36 << 24) | 0xFFFFFF, 1333788672, 1333788672);  // 调 绘制转发（vt+128）
      sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
    }
  }
  else if ( nArg2 == *(uint32_t *)(this + 240) )  // this+240〔nSyncArgB〕
  {
    v38 = (uint8_t)sub_43BCB0(nArg2) != 0 ? 255 : 150;  // 调 焦点窗口判定（三选）
    dwNow = timeGetTime();  // 调 取系统毫秒时刻
    v40 = sub_42B420(0, v38, dwNow, 400);  // 调 往返插值（三角波）
    sub_491530(2, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    pObj11 = sub_418DD0(40);  // 调 资源句柄 (101)
    if ( pObj11 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj11 + 128))(  // 调用虚函数（虚表槽 +128）
        pObj11,
        261,
        296,
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        1065353216,  // 常量 1.0f
        1065353216,  // 常量 1.0f
        0,
        (v40 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491630(2);  // 调 渲染层状态还原（与 ·0x491530 配对）
  }
}


// ------------------------------------------------------------
// 0x46BA60 sub_46BA60 —— 频道类型页签切换与按钮态
// +45 记 nArg2；为 4 隐藏 +58 控件，否则显示并 sub_69C340(-1)/69C400(0)/69C360(dword_98BA18[nArg2]) 重设文本链。
// +47..+50 四按钮按 nArg2 反相可见性；场景 dword_8F8528+7 的 +256 为 0 时同步 dword_79BE4C/79BE54。
// CNCommandChecker__vmt40(0,1) 后按 nArg2 分派设槽 53..57 的图号与坐标。
// ------------------------------------------------------------
int /*thiscall*/ sub_46BA60(uint32_t *this, int nArg2)  // 函数: 频道类型页签切换与按钮态
{
  int v3; // eax
  int result; // eax
  int v5; // eax
  int v6; // [esp-4h] [ebp-Ch]

  *(this + 45) = nArg2;  // this+180〔nRadius(推断)〕
  if ( nArg2 == 4 )
  {
    *(uint8_t *)(*(this + 58) + 16) = 0;  // this+232 = 基类时刻同步开关位
  }
  else
  {
    *(uint8_t *)(*(this + 58) + 16) = 1;  // this+232 = 基类时刻同步开关位
    sub_69C340(-1);
    sub_69C400(0);
    sub_69C360(dword_98BA18[nArg2], 0);
  }
  *(uint8_t *)(*(this + 47) + 17) = nArg2 != 0;  // this+188〔nStatusIdx(推断)〕
  *(uint8_t *)(*(this + 48) + 17) = nArg2 != 1;  // this+192〔nDlgId(推断)〕
  *(uint8_t *)(*(this + 49) + 17) = nArg2 != 2;  // this+49 UDP 已上报标志
  *(uint8_t *)(*(this + 50) + 17) = nArg2 != 3;  // this+200〔nMainState(推断)〕
  *(uint8_t *)(*(this + 63) + 16) = 0;  // this+252 = 基类四元组 dword 槽 2
  v3 = *((uint32_t *)dword_8F8528 + 7);  // dword_8F8528 = 主管理器
  if ( *(uint8_t *)(v3 + 256) == 0 )
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v3 + 124) + 12);  // 通用对象全局槽 1
    dword_79BE54 = dword_79BE4C;  // 通用对象全局槽 2
  }
  result = CNCommandChecker__vmt40(0, 1);  // result = 调 CNCommandChecker__vmt40
  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      *(this + 51) = sub_418DD0(0);  // 调 资源句柄 (101)
      v5 = sub_418DD0(17);  // 调 资源句柄 (101)
      v6 = 19;
LABEL_10:
      *(this + 52) = v5;  // this+208〔nField208(推断)〕
      *(this + 54) = 256;  // this+216〔bField216(推断)〕
      *(this + 55) = 72;  // this+220〔nSnapDst220(推断)〕
      result = sub_418DD0(v6);  // 调 资源句柄 (101)
      *(this + 56) = 263;  // this+224〔nSnapDst224(推断)〕
      *(this + 57) = 102;  // this+228〔nSnapDst228(推断)〕
      *(this + 53) = result;  // this+212〔nField212(推断)〕
      return result;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      *(this + 51) = sub_418DD0(1);  // 调 资源句柄 (101)
      v5 = sub_418DD0(18);  // 调 资源句柄 (101)
      v6 = 20;
      goto LABEL_10;
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      *(this + 51) = sub_418DD0(2);  // 调 资源句柄 (101)
      *(this + 52) = sub_418DD0(35);  // 调 资源句柄 (101)
      *(this + 54) = 247;  // this+216〔bField216(推断)〕
      *(this + 55) = 63;  // this+220〔nSnapDst220(推断)〕
      result = sub_418DD0(36);  // 调 资源句柄 (101)
      *(this + 56) = 278;  // this+224〔nSnapDst224(推断)〕
      *(this + 57) = 101;  // this+228〔nSnapDst228(推断)〕
      *(this + 53) = result;  // this+212〔nField212(推断)〕
      break;
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      *(this + 51) = sub_418DD0(3);  // 调 资源句柄 (101)
      *(this + 52) = sub_418DD0(41);  // 调 资源句柄 (101)
      *(this + 54) = 236;  // this+216〔bField216(推断)〕
      *(this + 55) = 23;  // this+220〔nSnapDst220(推断)〕
      result = sub_418DD0(42);  // 调 资源句柄 (101)
      *(this + 56) = 299;  // this+224〔nSnapDst224(推断)〕
      *(this + 57) = 93;  // this+228〔nSnapDst228(推断)〕
      *(this + 53) = result;  // this+212〔nField212(推断)〕
      break;
    default:
      break;
  }
  return result;
}



// ============================================================
// 【分区 8】选角输入（0x46BCB0-0x46C300）
// 键盘导航 0x46BD70（SELECT_CHARACTER/CLICK_BUTTON4 自证）。
// ============================================================
// ------------------------------------------------------------
// 0x46BCB0 sub_46BCB0 —— 频道选定提交（发包与配置写入）
// nArg3 非 0，或 +96 未锁且 nArg2 小于列表项数时：sub_423200(dword_8F7B08,4) 开包、sub_423290 写槽号、sub_423380 发包。
// sub_48B7C0(11, nArg2) 写调试配置、+96=1、dword_8F7A24+288 = +92。
// 并把 (this+80 + 144*nArg2) 项的名称串经 off_77F3FC 分发。
// ------------------------------------------------------------
char /*thiscall*/ sub_46BCB0(int this, int nArg2, int nArg3)  // 函数: 频道选定提交（发包与配置写入）
{
  int v4; // eax
  int fld_40; // ecx
  int fld_5C; // ecx
  int fld_50; // eax
  int v8; // eax

  if ( (uint8_t)nArg3 != 0
    || (LOBYTE(v4) = *(uint8_t *)(this + 96), (uint8_t)v4 == 0)  // this+384 = 动画件名 SSO 容量判据
    && ((fld_40 = *(uint32_t *)(this + 64)) != 0 ? (v4 = (*(uint32_t *)(this + 68) - fld_40) >> 2) : (v4 = 0), nArg2 < v4) )  // this+256 = 基类四元组字节槽 3
  {
    sub_423200(dword_8F7B08, 4);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    HIBYTE(nArg3) = nArg2;  // 调 取 16 位值高 8 位
    sub_423290(dword_8F7B08, (int)&nArg3 + 3, 1);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    sub_48B7C0(11, nArg2);  // 调 调试配置项写入并刷新（·sub_48B830 联动）
    fld_5C = *(uint32_t *)(this + 92);  // this+92〔pFxObjC(推断)〕等 2 字段
    *(uint8_t *)(this + 96) = 1;  // this+384 = 动画件名 SSO 容量判据
    *(uint32_t *)(dword_8F7A24 + 288) = fld_5C;  // dword_8F7A24 = 当前场景状态对象
    fld_50 = *(uint32_t *)(this + 80) + 144 * nArg2;  // this+80〔nAuraStage(推断)〕
    if ( *(uint32_t *)(fld_50 + 24) < 0x10u )  // fld_50=this+80 nAuraStage
      v8 = fld_50 + 4;  // fld_50=this+80 nAuraStage
    else
      v8 = *(uint32_t *)(fld_50 + 4);  // fld_50=this+80 nAuraStage
    LOBYTE(v4) = off_77F3FC((char *)&byte_6C7A40, v8);  // 调 取 16 位值低 8 位
  }
  return v4;
}



// ------------------------------------------------------------
// 0x46BD70 sub_46BD70
// ------------------------------------------------------------
// 选角键盘导航：VK_LEFT(37)/VK_UP(38)/VK_RIGHT(39)/VK_DOWN(40)，
// 左右 ±1、上下 ±4（4 列网格）→ SELECT_CHARACTER 音效 + 0x46B0E0 置光标；
// Enter(13) → sub_46BCB0 确认 + CLICK_BUTTON4；ESC 态经 0x44BCC0 关闭
char /*thiscall*/ sub_46BD70(int *this)  // 实现：Enter(13) → sub_46BCB0 确认 + CLICK_BUTTON4；ESC 态经 0x44BCC0 关闭
{
  int fld_e23; // eax
  int fld_e233; // esi
  int fld_e16; // ecx
  int fld_e17; // eax
  int fld_e232; // ecx

  LOBYTE(fld_e23) = dword_79C0A0;  // 调 取 16 位值低 8 位
  if ( *(uint32_t *)(dword_79C0A0 + 32) == 0 )
    return fld_e23;
  if ( sub_415660(37, byte_98BA04) != 0 )  // 调 GetAsyncKeyState 边沿锁存（按下置位 / 释放返回 1）
  {
    fld_e23 = *(this + 23);  // this+92 = pFxObjC
    if ( fld_e23 <= 0 )  // fld_e23=this+92 插值起点 Z
      return fld_e23;  // fld_e23=this+92 插值起点 Z
    fld_e233 = fld_e23 - 1;
    goto LABEL_5;
  }
  if ( sub_415660(39, &unk_98BA03) != 0 )  // 调 GetAsyncKeyState 边沿锁存（按下置位 / 释放返回 1）
  {
    fld_e16 = *(this + 16);  // this+64〔apServerTabBtn(推断)〕
    if ( fld_e16 != 0 )  // fld_e16=this+64 apServerTabBtn
      fld_e17 = (*(this + 17) - fld_e16) >> 2;  // this+68〔nCharCount(推断)〕
    else
      fld_e17 = 0;  // fld_e17=this+68 nCharCount
    fld_e232 = *(this + 23);  // this+92 = pFxObjC
    fld_e23 = fld_e17 - 1;
    if ( fld_e232 < fld_e23 )  // fld_e232=this+92 插值起点 Z
    {
      fld_e233 = fld_e232 + 1;  // fld_e232=this+92 插值起点 Z
LABEL_5:
      LOBYTE(fld_e23) = (uint8_t)sub_432EA0("SELECT_CHARACTER", -1, 0, 0);  // 调 音效播放包装（非空判定）
      if ( fld_e233 != -1 )
        LOBYTE(fld_e23) = sub_46B0E0(fld_e233);  // 调 频道列表选中态 setter
    }
  }
  else
  {
    if ( sub_415660(38, &unk_98BA02) != 0 )  // 调 GetAsyncKeyState 边沿锁存（按下置位 / 释放返回 1）
    {
      fld_e233 = *(this + 23) - 4;  // this+92 = pFxObjC
      if ( fld_e233 < 0 )  // fld_e233=this+92 插值起点 Z
        fld_e233 = 0;  // fld_e233=this+92 插值起点 Z
      goto LABEL_5;
    }
    if ( sub_415660(40, &unk_98BA01) != 0 )  // 调 GetAsyncKeyState 边沿锁存（按下置位 / 释放返回 1）
    {
      fld_e233 = *(this + 23) + 4;  // this+92 = pFxObjC
      if ( fld_e233 > sub_46B060(this) - 1 )  // 调 4 字节项数组计数
        fld_e233 = sub_46B060(this) - 1;  // 调 4 字节项数组计数
      goto LABEL_5;
    }
    LOBYTE(fld_e23) = sub_44BCC0(dword_8F8528);  // 调 71 组条目表非空检查
    if ( (uint8_t)fld_e23 != 0 )  // fld_e23=this+92 插值起点 Z
    {
      byte_98BA00 = 0;
    }
    else
    {
      LOBYTE(fld_e23) = sub_415660(13, &byte_98BA00);  // 调 GetAsyncKeyState 边沿锁存（按下置位 / 释放返回 1）
      if ( (uint8_t)fld_e23 != 0 )  // fld_e23=this+92 插值起点 Z
      {
        fld_e23 = *(this + 23);  // this+92 = pFxObjC
        if ( fld_e23 != -1 && *(uint8_t *)(*(this + 63) + 16) == 0 )  // this+252 = 基类四元组 dword 槽 2
        {
          sub_46BCB0(fld_e23, 0);  // 调 频道选定提交（发包与配置写入）
          LOBYTE(fld_e23) = (uint8_t)sub_432EA0("CLICK_BUTTON4", -1, 0, 0);  // 调 音效播放包装（非空判定）
        }
      }
    }
  }
  return fld_e23;  // fld_e23=this+92 插值起点 Z
}



// ------------------------------------------------------------
// 0x46BED0 sub_46BED0 —— 选角界面控件逐槽析构
// +4 使能时对 +12/+52/+104/+108/+112/+116 等一批持有控件以 vt 槽 0（析构，实参 1）释放并写 0。
// +64 指针数组逐项释放后 j__free，+64/+68/+72 归零。
// ------------------------------------------------------------
char /*thiscall*/ sub_46BED0(int this)  // 函数: 选角界面控件逐槽析构
{
  char result; // al
  void (/*thiscall*/ ***pThis_C)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_34)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_68)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_6C)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_70)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_74)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_B0)(uint32_t, int); // ecx
  uint32_t *pThis_BC; // edi
  int i; // ebx
  void (/*thiscall*/ ***pThis_E8)(uint32_t, int); // ecx
  uint32_t *pThis_EC; // edi
  int j; // ebx
  void (/*thiscall*/ ***pThis_F4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_F8)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_FC)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_100)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_104)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_108)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_10C)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_110)(uint32_t, int); // ecx
  unsigned int v23; // edi
  int fld_40; // ecx
  void (/*thiscall*/ ***v25)(uint32_t, int); // ecx

  result = *(uint8_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( result != 0 )  // 若结果非 0（成功）
  {
    pThis_C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
    *(uint8_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
    if ( pThis_C != nullptr )  // 若 pThis_C 有效（非空）
      (**pThis_C)(pThis_C, 1);  // 调 pThis_C 的虚函数（vt+0）
    pThis_34 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 52);  // this+208〔nField208(推断)〕
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    if ( pThis_34 != nullptr )  // 若 pThis_34 有效（非空）
      (**pThis_34)(pThis_34, 1);  // 调 pThis_34 的虚函数（vt+0）
    pThis_68 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 104);  // this+104 插值终点 Z
    *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
    if ( pThis_68 != nullptr )  // 若 pThis_68 有效（非空）
      (**pThis_68)(pThis_68, 1);  // 调 pThis_68 的虚函数（vt+0）
    pThis_6C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 108);  // this+108 第 1 组·宿主属性 +886 增量
    *(uint32_t *)(this + 104) = 0;  // this+104〔nTimerEnd(推断)〕
    if ( pThis_6C != nullptr )  // 若 pThis_6C 有效（非空）
      (**pThis_6C)(pThis_6C, 1);  // 调 pThis_6C 的虚函数（vt+0）
    pThis_70 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 112);  // this+112〔pHostComp112〕
    *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
    if ( pThis_70 != nullptr )  // 若 pThis_70 有效（非空）
      (**pThis_70)(pThis_70, 1);  // 调 pThis_70 的虚函数（vt+0）
    pThis_74 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 116);  // this+116 观察者 vector 尾针
    *(uint32_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
    if ( pThis_74 != nullptr )  // 若 pThis_74 有效（非空）
      (**pThis_74)(pThis_74, 1);  // 调 pThis_74 的虚函数（vt+0）
    pThis_B0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 176);  // this+704 = 表现/名字快照[24]
    *(uint32_t *)(this + 116) = 0;  // this+116〔会话上下文〕
    if ( pThis_B0 != nullptr )  // 若 pThis_B0 有效（非空）
      (**pThis_B0)(pThis_B0, 1);  // 调 pThis_B0 的虚函数（vt+0）
    *(uint32_t *)(this + 176) = 0;  // this+704 = 表现/名字快照[24]
    pThis_BC = (uint32_t *)(this + 188);  // this+188〔nStatusIdx(推断)〕
    for ( i = 4; i != 0; --i )  // 循环：i 从 4 递减到 0
    {
      if ( *pThis_BC != 0 )  // pThis_BC=this+188 nStatusIdx
        (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_BC)(*pThis_BC, 1);  // pThis_BC=this+188 nStatusIdx
      *pThis_BC++ = 0;  // pThis_BC=this+188 nStatusIdx
    }
    pThis_E8 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 232);  // this+232〔bSyncFlag〕
    if ( pThis_E8 != nullptr )  // 若 pThis_E8 有效（非空）
      (**pThis_E8)(pThis_E8, 1);  // 调 pThis_E8 的虚函数（vt+0）
    *(uint32_t *)(this + 232) = 0;  // this+232〔bSyncFlag〕
    pThis_EC = (uint32_t *)(this + 236);  // this+944 = 名字已播出标志
    for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
    {
      if ( *pThis_EC != 0 )  // pThis_EC=this+944 名字已播出标志
        (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_EC)(*pThis_EC, 1);  // pThis_EC=this+944 名字已播出标志
      *pThis_EC++ = 0;  // pThis_EC=this+944 名字已播出标志
    }
    pThis_F4 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 244);  // this+976 = uCfgE976
    if ( pThis_F4 != nullptr )  // 若 pThis_F4 有效（非空）
      (**pThis_F4)(pThis_F4, 1);  // 调 pThis_F4 的虚函数（vt+0）
    pThis_F8 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 248);  // this+992 = uCfgB992
    *(uint32_t *)(this + 244) = 0;  // this+976 = uCfgE976
    if ( pThis_F8 != nullptr )  // 若 pThis_F8 有效（非空）
      (**pThis_F8)(pThis_F8, 1);  // 调 pThis_F8 的虚函数（vt+0）
    pThis_FC = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 252);  // this+252〔nQuad2〕
    *(uint32_t *)(this + 248) = 0;  // this+992 = uCfgB992
    if ( pThis_FC != nullptr )  // 若 pThis_FC 有效（非空）
      (**pThis_FC)(pThis_FC, 1);  // 调 pThis_FC 的虚函数（vt+0）
    pThis_100 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 256);  // this+256〔bQuad3〕
    *(uint32_t *)(this + 252) = 0;  // this+252〔nQuad2〕
    if ( pThis_100 != nullptr )  // 若 pThis_100 有效（非空）
      (**pThis_100)(pThis_100, 1);  // 调 pThis_100 的虚函数（vt+0）
    pThis_104 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 260);  // this+260〔nQuad4〕
    *(uint32_t *)(this + 256) = 0;  // this+256〔bQuad3〕
    if ( pThis_104 != nullptr )  // 若 pThis_104 有效（非空）
      (**pThis_104)(pThis_104, 1);  // 调 pThis_104 的虚函数（vt+0）
    pThis_108 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 264);  // this+264 动画句柄
    *(uint32_t *)(this + 260) = 0;  // this+260〔nQuad4〕
    if ( pThis_108 != nullptr )  // 若 pThis_108 有效（非空）
      (**pThis_108)(pThis_108, 1);  // 调 pThis_108 的虚函数（vt+0）
    pThis_10C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 268);
    *(uint32_t *)(this + 264) = 0;  // this+264〔nAnimHandle(推断)〕
    if ( pThis_10C != nullptr )  // 若 pThis_10C 有效（非空）
      (**pThis_10C)(pThis_10C, 1);  // 调 pThis_10C 的虚函数（vt+0）
    pThis_110 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 272);
    *(uint32_t *)(this + 268) = 0;  // this+268〔field_10C〕
    if ( pThis_110 != nullptr )  // 若 pThis_110 有效（非空）
      (**pThis_110)(pThis_110, 1);  // 调 pThis_110 的虚函数（vt+0）
    v23 = 0;
    *(uint32_t *)(this + 272) = 0;
    while ( 1 )  // 无限循环
    {
      fld_40 = *(uint32_t *)(this + 64);  // this+256 = 基类四元组字节槽 3
      if ( fld_40 == 0 || v23 >= (*(uint32_t *)(this + 68) - fld_40) >> 2 )  // this+68〔nCharCount(推断)〕
        break;
      v25 = *(void (/*thiscall*/ ****)(uint32_t, int))(fld_40 + 4 * v23);  // fld_40=this+256 参数灌入槽 3
      if ( v25 != nullptr )  // 若 v25 有效（非空）
        (**v25)(v25, 1);  // 调 v25 的虚函数（vt+0）
      ++v23;
    }
    if ( *(uint32_t *)(this + 64) != 0 )  // this+256 = 基类四元组字节槽 3
      j__free(*(void **)(this + 64));  // this+256 = 基类四元组字节槽 3
    *(uint32_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
    *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
    *(uint32_t *)(this + 72) = 0;  // this+72〔nSnapshot72(推断)〕等 2 字段
    return 0;
  }
  return result;  // result=this+4 宿主对象
}


// ------------------------------------------------------------
// 0x46C0E0 sub_46C0E0 —— 频道与角色页签切换
// +11 记 nArg2。为 0 分支：+52 对象显示、+176 隐藏、+172=-1、+108 对象 +17=0、+112 对象 +16=0、sub_44E850(30)。
// 为 1 分支：+13 隐藏、+176 显示、sub_46BA60(this, +45) 重设频道页签、sub_44E850(30)。
// ------------------------------------------------------------
char /*thiscall*/ sub_46C0E0(int *this, int nArg2)  // 函数: 频道与角色页签切换
{
  int fld_e17; // eax
  int fld_e16; // ecx
  int fld_e27; // eax

  LOBYTE(fld_e17) = nArg2;  // 调 取 16 位值低 8 位
  *(this + 11) = nArg2;  // this+44〔nExpireMs(推断)〕
  if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 )
    {
      *(uint8_t *)(*(this + 13) + 16) = 0;  // this+52 = bAuraState
      *(uint8_t *)(*(this + 44) + 16) = 1;  // this+176〔pAppendVecCap(推断)〕
      sub_46BA60(this, *(this + 45));  // 调 频道类型页签切换与按钮态
      LOBYTE(fld_e17) = sub_44E850(dword_8F8528, 30);  // 调 按池号批量回收活动对象
    }
  }
  else
  {
    *(uint8_t *)(*(this + 13) + 16) = 1;  // this+52 = bAuraState
    *(uint8_t *)(*(this + 44) + 16) = 0;  // this+176〔pAppendVecCap(推断)〕
    fld_e16 = *(this + 16);  // this+64〔apServerTabBtn(推断)〕
    if ( fld_e16 == 0 || (fld_e17 = (*(this + 17) - fld_e16) >> 2) > -1 )  // this+68〔nCharCount(推断)〕
    {
      fld_e27 = *(this + 27);  // this+108〔nAdd108(推断)〕
      *(this + 23) = -1;  // this+92 = pFxObjC
      *(uint8_t *)(fld_e27 + 17) = 0;  // fld_e27=this+108 nAdd108
      *(uint8_t *)(*(this + 28) + 16) = 0;  // this+112 = pHostComp
      LOBYTE(fld_e17) = sub_44E850(dword_8F8528, 30);  // 调 按池号批量回收活动对象
    }
    *(this + 43) = -1;  // this+172〔pAppendVecEnd(推断)〕
  }
  return fld_e17;
}



// ------------------------------------------------------------
// 0x46C180 sub_46C180 —— 条目深拷贝构造（144 字节）
// 首串 sub_4014D0 复制、+28/+32/+36 标量、+37 处 clong（·sub_46B080）、+52。
// qmemcpy(this+56, src+56, 0x35) 覆盖 +56..+108，末以 +116 处串初始化并复制。
// 条目固定 144 字节（见 ·sub_46CB70 步进）。
// ------------------------------------------------------------
int /*thiscall*/ sub_46C180(int this, int pArg2)  // 函数: 条目深拷贝构造（144 字节）
{
  *(uint32_t *)(this + 24) = 15;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 20) = 0;  // this+80 = nAuraStage
  *(uint8_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  sub_4014D0((std::_String_base *)this, pArg2, 0, -1);  // 调 std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *(uint32_t *)(this + 28) = *(uint32_t *)(pArg2 + 28);  // this+112 = pHostComp
  *(uint32_t *)(this + 32) = *(uint32_t *)(pArg2 + 32);  // this+32〔nHeight(推断)〕等 2 字段
  *(uint8_t *)(this + 36) = *(uint8_t *)(pArg2 + 36);  // this+144 = pFrameList144
  sub_46B080((uint32_t *)(this + 37), pArg2 + 37);  // 调 clong 构造与初值写入
  *(uint32_t *)(this + 52) = *(uint32_t *)(pArg2 + 52);  // this+52〔bAuraState(推断)〕等 2 字段
  qmemcpy((void *)(this + 56), (const void *)(pArg2 + 56), 0x35u);  // 调 内存块拷贝(内联展开)
  *(uint32_t *)(this + 112) = *(uint32_t *)(pArg2 + 112);  // this+112〔pHostComp112〕
  *(uint32_t *)(this + 140) = 15;  // this+140〔nAdd140(推断)〕
  *(uint32_t *)(this + 136) = 0;  // this+136〔nCtx136(推断)〕等 2 字段
  *(uint8_t *)(this + 120) = 0;  // this+120〔pAnimObj〕
  sub_4014D0((std::_String_base *)(this + 116), pArg2 + 116, 0, -1);  // 调 std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  return this;
}



// ------------------------------------------------------------
// 0x46C250 sub_46C250 —— 与 ·sub_46C180 同构（差异：浅拷贝域不同）
// 差异：+37 处 clong 走 sub_41A5E0 与 sub_41A590 而非 ·sub_46B080；
// +52..+112 逐字段复制替代 qmemcpy 且含 +108 字节，无 +20/+24 预置。
// ------------------------------------------------------------
int /*thiscall*/ sub_46C250(int this, int pArg2)  // 函数: 与 ·sub_46C180 同构（差异：浅拷贝域不同）
{
  int v3; // eax
  int v4; // edx

  sub_4014D0((std::_String_base *)this, pArg2, 0, -1);  // 调 std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *(uint32_t *)(this + 28) = *(uint32_t *)(pArg2 + 28);  // this+112 = pHostComp
  *(uint32_t *)(this + 32) = *(uint32_t *)(pArg2 + 32);  // this+32〔nHeight(推断)〕等 2 字段
  *(uint8_t *)(this + 36) = *(uint8_t *)(pArg2 + 36);  // this+144 = pFrameList144
  v3 = sub_41A5E0(pArg2 + 37);  // 调 crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(this + 37, v4, v3);  // 调 crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(uint32_t *)(this + 52) = *(uint32_t *)(pArg2 + 52);  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = *(uint32_t *)(pArg2 + 56);  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 60) = *(uint32_t *)(pArg2 + 60);  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 64) = *(uint32_t *)(pArg2 + 64);  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 68) = *(uint32_t *)(pArg2 + 68);  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 72) = *(uint32_t *)(pArg2 + 72);  // this+72〔nSnapshot72(推断)〕等 2 字段
  *(uint32_t *)(this + 76) = *(uint32_t *)(pArg2 + 76);  // this+76〔pBtnActionE〕
  *(uint32_t *)(this + 80) = *(uint32_t *)(pArg2 + 80);  // this+80〔nAuraStage(推断)〕
  *(uint32_t *)(this + 84) = *(uint32_t *)(pArg2 + 84);  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 88) = *(uint32_t *)(pArg2 + 88);  // this+88〔pFxObjB(推断)〕等 2 字段
  *(uint32_t *)(this + 92) = *(uint32_t *)(pArg2 + 92);  // this+92〔pFxObjC(推断)〕等 2 字段
  *(uint32_t *)(this + 96) = *(uint32_t *)(pArg2 + 96);  // this+384 = 动画件名 SSO 容量判据
  *(uint32_t *)(this + 100) = *(uint32_t *)(pArg2 + 100);  // this+100〔bEnchantDone(推断)〕
  *(uint32_t *)(this + 104) = *(uint32_t *)(pArg2 + 104);  // this+104〔nTimerEnd(推断)〕
  *(uint8_t *)(this + 108) = *(uint8_t *)(pArg2 + 108);  // this+108〔nAdd108(推断)〕
  *(uint32_t *)(this + 112) = *(uint32_t *)(pArg2 + 112);  // this+112〔pHostComp112〕
  sub_4014D0((std::_String_base *)(this + 116), pArg2 + 116, 0, -1);  // 调 std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  return this;
}



// ============================================================
// 【分区 9】CNEntranceModule 选角模块（0x46C300-0x46CB70）
// vmt4 = 选角界面帧（登录协议阶段⑤，见文件头）。
// ============================================================
// ------------------------------------------------------------
// 0x46C300 CNEntranceModule__vmt4
// ------------------------------------------------------------
// CNEntranceModule::vmt4 —— 选角界面帧（登录协议阶段⑤）：
// 主帧循环 → 退出确认(vt+20(10)/vt+16(84) 同 docs/13 §1) → 0x46BD70 键盘 →
// 一次性 M_CHARACTER_SELECT(+50) → sub_45DDA0(dword_8F8524,1) UDP 上报(+49) →
// 角色按钮（CLICK_BUTTON2，选中板 30 号/名字板 0x1E 号 dword_8F8528 vt）
uint8_t */*thiscall*/ sub_46C300(int this)  // 实现：角色按钮（CLICK_BUTTON2，选中板 30 号/名字板 0x1E 号 dword_8F8528 vt）
{
  uint8_t *result; // eax
  int pBtnCharBoard; // eax  | +0x0068 → ★ 角色选中板按钮（CNEntranceModule；va=0046C300）
  int pCharCardBoard; // edx  | +0x0034 → ★ 角色选中板（0x46C300: 其 +16 置 0 取消高亮）（CNEntranceModule；va=0046C300）
  int pBtnCharName; // eax  | +0x006C → ★ 角色名板按钮（CNEntranceModule；va=0046C300）
  int nCurChar; // ecx  | +0x005C → ★ 当前选中角色下标（0x46C300: ==-1 未选；44E8D0(0x1E) 名字板定位）（CNEntranceModule；va=0046C300）
  int pCharEntryArray; // eax  | +0x0050 → ★ 角色条目数组基址（0x46C300: *(this+80) + 144*nSelChar，144 字节/条）（CNEntranceModule；va=0046C300）
  int v8; // eax
  int pCharCardBoard_; // eax  | +0x0034 → ★ 角色选中板（0x46C300: 其 +16 置 0 取消高亮）（CNEntranceModule；va=0046C300）
  int v10; // edi
  int pCharEntryVecBegin; // ecx  | +0x0040 → ★ 角色条目数组 begin（CNEntranceModule；va=0046C300）
  int nCharCount; // eax  | +0x0044 → ★ 角色数（begin/end 差 >>2；>=8 时提示「角色已满」）（CNEntranceModule；va=0046C300）
  int pBtnCharCancel; // eax  | +0x0070 → ★ 取消选中按钮（CNEntranceModule；va=0046C300）
  int nCurChar_; // eax  | +0x005C → ★ 当前选中角色下标（0x46C300: ==-1 未选；44E8D0(0x1E) 名字板定位）（CNEntranceModule；va=0046C300）
  int pBtnBack; // esi  | +0x0074 → ★ 返回按钮（CNEntranceModule；va=0046C300）
  signed int fld_402; // ecx  | +0x0040 → ★ 角色条目数组 begin（CNEntranceModule；va=0046C300）
  int pThis_BC; // edx
  int pBtnScrollUp; // eax  | +0x00EC → 上滚按钮（0x46C300: SCROLL_ARROW → sub_69C400(当前-1)）（CNEntranceModule；va=0046C300）
  int pScrollCtrl; // eax  | +0x00F4 → 滚动条控件（0x46C300: sub_69C380/69C3A0/69C500 取值/步长/上限）（CNEntranceModule；va=0046C300）
  int pBtnScrollDown; // eax  | +0x00F0 → 下滚按钮（0x46C300: SCROLL_ARROW → sub_69C400(当前+1)）（CNEntranceModule；va=0046C300）
  int fld_F42; // edi  | +0x00F4 → 滚动条控件（0x46C300: sub_69C380/69C3A0/69C500 取值/步长/上限）（CNEntranceModule；va=0046C300）
  unsigned int fld_F43; // edi  | +0x00F4 → 滚动条控件（0x46C300: sub_69C380/69C3A0/69C500 取值/步长/上限）（CNEntranceModule；va=0046C300）
  int fld_F44; // eax  | +0x00F4 → 滚动条控件（0x46C300: sub_69C380/69C3A0/69C500 取值/步长/上限）（CNEntranceModule；va=0046C300）
  int pBtnNameEdit; // eax  | +0x00F8 → ★ 名字编辑按钮（0x46C300: 命中且角色数<8 → sub_422E70(140) 提示串）（CNEntranceModule；va=0046C300）
  const char *v25; // eax
  int pNameEditBox; // eax  | +0x00FC → ★ 名字输入框（CNEntranceModule；va=0046C300）
  int pNameEditCtrl; // eax  | +0x0100 → ★ 名字输入控件（CNEntranceModule；va=0046C300）
  int pBtnExitA; // eax  | +0x0104 → 退出按钮 A（0x46C300: 命中 → sub_41C860）（CNEntranceModule；va=0046C300）
  int pNameEditCtrl_; // eax  | +0x0100 → ★ 名字输入控件（CNEntranceModule；va=0046C300）
  int pCharEntryVecBegin_; // ecx  | +0x0040 → ★ 角色条目数组 begin（CNEntranceModule；va=0046C300）
  const char *v31; // eax
  int pNameEditCtrl_2; // ecx  | +0x0100 → ★ 名字输入控件（CNEntranceModule；va=0046C300）
  int v33; // eax
  int v34; // eax
  const char *psz; // edi
  int nLen; // edx
  int v37; // ecx
  char v38; // al
  const char *fld_1004; // eax
  DWORD v40; // ecx
  int v41; // eax
  int pBtnExitB; // eax  | +0x0108 → 退出按钮 B（与 +260 成组的退出/辅助按钮槽）【推断】（CNEntranceModule；va=0046C300）
  int v43; // eax
  int pCharCardBoard_2; // eax  | +0x0034 → ★ 角色选中板（0x46C300: 其 +16 置 0 取消高亮）（CNEntranceModule；va=0046C300）
  int pCharEntryVecBegin_2; // ecx  | +0x0040 → ★ 角色条目数组 begin（CNEntranceModule；va=0046C300）
  int pBtnCharName_; // edx  | +0x006C → ★ 角色名板按钮（CNEntranceModule；va=0046C300）
  uint8_t v47[4]; // [esp+Ch] [ebp-48h] BYREF
  char Buffer[64]; // [esp+10h] [ebp-44h] BYREF
  int dword_796E502; // [esp+50h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  sub_433690();  // 主帧循环（引擎心跳，被模块 vmt4 调用）
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, 10) != 0  // 调用虚函数（虚表槽 +20）【推断: 每帧表现主循环（子对象循环渲染）】
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 84) != 0 )  // 调用虚函数（虚表槽 +16）
  {
    sub_41C860((uint32_t *)dword_8F7A24);  // 调 断线/超时退出判定（重试上限 5）
  }
  if ( *(uint8_t *)(this + 56) != 0 )  // this+56〔bInputEnable〕
    sub_46BD70((int *)this);  // 调 Enter(13) → sub_46BCB0 确认 + CLICK_BUTTON4；ESC 态经 0x44BCC0 关闭
  if ( *(uint8_t *)(this + 50) == 0 )  // this+50〔bCharSelSent〕
  {
    sub_432EA0("M_CHARACTER_SELECT", -1, 0, 0);  // 调 音效播放包装（非空判定）
    *(uint8_t *)(this + 50) = 1;  // this+50〔bCharSelSent〕
  }
  if ( *(uint8_t *)(this + 48) != 0 && *(uint8_t *)(this + 49) == 0 )  // this+48〔bUdpReportOn〕
  {
    sub_45DDA0(dword_8F8524, 1);  // 调 连接自检状态机（目标态 nArg2）
    *(uint8_t *)(this + 49) = 1;  // this+49〔bUdpReported〕
  }
  result = *(uint8_t **)(this + 44);  // this+44〔nSelectedChar〕
  if ( result == nullptr )  // 若 result 为空
  {
    pBtnCharBoard = *(uint32_t *)(this + 104);  // this+104〔pBtnCharBoard〕
    if ( *(uint8_t *)(pBtnCharBoard + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnCharBoard + 12) && *(uint8_t *)(this + 56) != 0 )  // this+56〔bInputEnable〕
    {
      pCharCardBoard = *(uint32_t *)(this + 52);  // this+52〔pCharCardBoard〕
      *(uint32_t *)(this + 44) = 1;  // this+44〔nSelectedChar〕
      *(uint8_t *)(pCharCardBoard + 16) = 0;  // fld_34=this+52 pCharCardBoard
      *(uint8_t *)(*(uint32_t *)(this + 176) + 16) = 1;  // this+704 = 表现/名字快照[24]
      sub_46BA60(*(uint32_t *)(this + 180));  // 调 频道类型页签切换与按钮态
      sub_44E850(dword_8F8528, 30);  // 调 按池号批量回收活动对象
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    }
    pBtnCharName = *(uint32_t *)(this + 108);  // this+108〔pBtnCharName〕
    if ( *(uint8_t *)(pBtnCharName + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnCharName + 12) )  // 当前动画对象指针(帧同步比对基准)
    {
      nCurChar = *(uint32_t *)(this + 92);  // this+92〔nCurChar〕
      if ( nCurChar != -1 && *(uint8_t *)(this + 56) != 0 )  // this+56〔bInputEnable〕
      {
        pCharEntryArray = *(uint32_t *)(this + 80) + 144 * nCurChar;  // this+80〔pCharEntryArray〕
        if ( *(uint32_t *)(pCharEntryArray + 24) < 0x10u )  // fld_50=this+80 pCharEntryArray
          v8 = pCharEntryArray + 4;  // fld_50=this+80 pCharEntryArray
        else
          v8 = *(uint32_t *)(pCharEntryArray + 4);  // fld_50=this+80 pCharEntryArray
        sub_44E8D0((char *)dword_8F8528, (void *)0x1E, v8, *(uint32_t *)(this + 92));  // 调 对象池借出（按池号取可用对象）
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
      }
    }
    pCharCardBoard_ = *(uint32_t *)(this + 52);  // this+52〔pCharCardBoard〕
    if ( *(uint8_t *)(pCharCardBoard_ + 17) != 0 && dword_79BE34 == *(uint32_t *)(pCharCardBoard_ + 12) && *(uint8_t *)(this + 56) != 0 )  // this+56〔bInputEnable〕
    {
      v10 = sub_46AF70(this);  // 调 鼠标坐标转 8 格下标
      if ( v10 != -1 )
      {
        pCharEntryVecBegin = *(uint32_t *)(this + 64);  // this+256 = 基类四元组字节槽 3
        nCharCount = pCharEntryVecBegin != 0 ? (*(uint32_t *)(this + 68) - pCharEntryVecBegin) >> 2 : 0;  // this+68〔nCharCount〕
        if ( v10 < nCharCount )  // fld_44=this+68 nCharCount
        {
          if ( *(uint32_t *)(this + 172) == -1 || sub_699000(this + 16) > *(uint32_t *)(this + 172) + 300 )  // this+688 = 表现/名字快照[2]
          {
            *(uint32_t *)(this + 172) = sub_699000(this + 16);  // this+688 = 表现/名字快照[2]
            if ( v10 != *(uint32_t *)(this + 92) )  // this+92〔nCurChar〕
            {
              sub_46B0E0(v10);  // 调 频道列表选中态 setter
              sub_432EA0("SELECT_CHARACTER", -1, 0, 0);  // 调 音效播放包装（非空判定）
            }
          }
          else
          {
            sub_46BCB0(*(uint32_t *)(this + 92), 0);  // 调 频道选定提交（发包与配置写入）
            sub_432EA0("CLICK_BUTTON4", -1, 0, 0);  // 调 音效播放包装（非空判定）
          }
        }
      }
    }
    pBtnCharCancel = *(uint32_t *)(this + 112);  // this+112〔pBtnCharCancel〕
    if ( *(uint8_t *)(pBtnCharCancel + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnCharCancel + 12) )  // 当前动画对象指针(帧同步比对基准)
    {
      nCurChar_ = *(uint32_t *)(this + 92);  // this+92〔nCurChar〕
      if ( nCurChar_ != -1 && *(uint8_t *)(this + 56) != 0 )  // this+56〔bInputEnable〕
      {
        sub_46BCB0(nCurChar_, 0);  // 调 频道选定提交（发包与配置写入）
        sub_432EA0("CLICK_BUTTON4", -1, 0, 0);  // 调 音效播放包装（非空判定）
      }
    }
    result = *(uint8_t **)(this + 272);
    if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) && *(uint8_t *)(this + 56) != 0 )  // this+56〔bInputEnable〕
    {
      sub_41D520((int *)dword_8F7A24);  // 调 切换到模块 5 的切换流程
      result = sub_432EA0("CLICK_BUTTON4", -1, 0, 0);  // 调 音效播放包装（非空判定）
    }
    pBtnBack = *(uint32_t *)(this + 116);  // this+116〔pBtnBack〕
    if ( *(uint8_t *)(pBtnBack + 17) != 0 )  // fld_74=this+116 pBtnBack
    {
      result = (uint8_t *)dword_79BE34;  // 当前动画对象指针(帧同步比对基准)
      if ( dword_79BE34 == *(uint32_t *)(pBtnBack + 12) )  // 当前动画对象指针(帧同步比对基准)
      {
        sub_41C860((uint32_t *)dword_8F7A24);  // 调 断线/超时退出判定（重试上限 5）
        return sub_432EA0("CLICK_BUTTON3", -1, 0, 0);  // 调 音效播放包装（非空判定）
      }
    }
    return result;
  }
  if ( result != (uint8_t *)1 )
    return result;
  fld_402 = 0;
  pThis_BC = this + 188;  // this+188 状态槽索引
  while ( *(uint8_t *)(*(uint32_t *)pThis_BC + 17) == 0 || dword_79BE34 != *(uint32_t *)(*(uint32_t *)pThis_BC + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    ++fld_402;
    pThis_BC += 4;  // pThis_BC=this+188 状态槽索引
    if ( fld_402 >= 4 )
      goto LABEL_57;
  }
  if ( *(uint32_t *)(this + 180) != fld_402 )  // this+180〔pBtnCreateChar〕
  {
    sub_46BA60(fld_402);  // 调 频道类型页签切换与按钮态
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
LABEL_57:
  pBtnScrollUp = *(uint32_t *)(this + 236);  // this+944 = 名字已播出标志
  if ( *(uint8_t *)(pBtnScrollUp + 17) != 0 )  // fld_EC=this+944 名字已播出标志
  {
    fld_402 = dword_79BE34;  // 当前动画对象指针(帧同步比对基准)
    if ( dword_79BE34 == *(uint32_t *)(pBtnScrollUp + 12) )  // 当前动画对象指针(帧同步比对基准)
    {
      if ( sub_69C380(*(uint32_t *)(this + 244)) != 0 )  // this+976 = uCfgE976
      {
        pScrollCtrl = sub_69C380(*(uint32_t *)(this + 244));  // this+976 = uCfgE976
        sub_69C400(pScrollCtrl - 1);  // fld_F4=this+976 首帧门字节
      }
      sub_432EA0("SCROLL_ARROW", -1, 0, 0);  // 调 音效播放包装（非空判定）
    }
  }
  pBtnScrollDown = *(uint32_t *)(this + 240);  // this+240〔pBtnScrollDown〕
  if ( *(uint8_t *)(pBtnScrollDown + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnScrollDown + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    fld_F42 = sub_69C380(*(uint32_t *)(this + 244));  // this+976 = uCfgE976
    fld_F43 = sub_69C3A0(*(uint32_t *)(this + 244)) + fld_F42;  // this+976 = uCfgE976
    if ( fld_F43 < sub_69C500(*(uint32_t *)(this + 244)) )  // this+976 = uCfgE976
    {
      fld_F44 = sub_69C380(*(uint32_t *)(this + 244));  // this+976 = uCfgE976
      sub_69C400(fld_F44 + 1);  // fld_F44=this+976 首帧门字节
    }
    sub_432EA0("SCROLL_ARROW", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  pBtnNameEdit = *(uint32_t *)(this + 248);  // this+992 = uCfgB992
  if ( *(uint8_t *)(pBtnNameEdit + 17) != 0 )  // fld_F8=this+992 【推断】状态/配置表项 B
  {
    fld_402 = dword_79BE34;  // 当前动画对象指针(帧同步比对基准)
    if ( dword_79BE34 == *(uint32_t *)(pBtnNameEdit + 12) )  // 当前动画对象指针(帧同步比对基准)
    {
      fld_402 = *(uint32_t *)(this + 64);  // this+256 = 基类四元组字节槽 3
      if ( fld_402 != 0 && (*(uint32_t *)(this + 68) - fld_402) >> 2 >= 8 )  // this+68〔nCharCount〕
      {
        v25 = (const char *)sub_422E70(140);  // 调 存 CStringManager::getStr 取本地化串
        sprintf(Buffer, v25, 8);  // 调 格式化到缓冲
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);  // 调 对象池借出（按池号取可用对象）
      }
      else
      {
        pNameEditBox = *(uint32_t *)(this + 252);  // this+252〔pNameEditBox〕
        if ( *(uint8_t *)(pNameEditBox + 16) == 0 )  // fld_FC=this+252 pNameEditBox
        {
          *(uint8_t *)(pNameEditBox + 16) = 1;  // fld_FC=this+252 pNameEditBox
          sub_69BCC0(*(uint32_t *)(this + 256));  // this+256〔pNameEditCtrl〕
          dword_79BE4C = *(uint32_t *)(*(uint32_t *)(this + 256) + 12);  // this+256〔pNameEditCtrl〕
          dword_79BE54 = dword_79BE4C;  // 通用对象全局槽 2
          sub_4BF300(dword_8F8558, 0, 0);  // 调 槽写侧（+64 + 索引）
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
        }
      }
    }
  }
  if ( *(uint8_t *)(*(uint32_t *)(this + 252) + 16) != 0 && (uint8_t)sub_69AC60(*(uint32_t *)(this + 256)) != 0 )  // this+252〔pNameEditBox〕
  {
    pNameEditCtrl = sub_69AC70(*(uint32_t *)(this + 256));  // this+256〔pNameEditCtrl〕
    sub_464740(270, 172, pNameEditCtrl + 10, 11, 0, 0);  // 调 九宫格面板框绘制
  }
  pBtnExitA = *(uint32_t *)(this + 260);  // this+260〔pBtnExitA〕
  if ( *(uint8_t *)(pBtnExitA + 17) == 0 || (fld_402 = dword_79BE34, dword_79BE34 != *(uint32_t *)(pBtnExitA + 12)) )  // 若 fld_402 = dword_79BE34
  {
    pNameEditCtrl_ = *(uint32_t *)(this + 256);  // this+256〔pNameEditCtrl〕
    LOBYTE(fld_402) = *(uint8_t *)(pNameEditCtrl_ + 116);  // 调 取 16 位值低 8 位
    *(uint8_t *)(pNameEditCtrl_ + 116) = 0;  // fld_1002=this+256 pNameEditCtrl
    if ( (uint8_t)fld_402 == 0 )  // fld_402=this+256 pNameEditCtrl
      goto LABEL_150;
  }
  sub_40BE20(fld_402, "\n CNEntranceModule Enter");  // 日志/输出串: CNEntranceModule Enter
  pCharEntryVecBegin_ = *(uint32_t *)(this + 64);  // this+256 = 基类四元组字节槽 3
  if ( pCharEntryVecBegin_ != 0 && (*(uint32_t *)(this + 68) - pCharEntryVecBegin_) >> 2 >= 8 )  // this+68〔nCharCount〕
  {
    v31 = (const char *)sub_422E70(141);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v31, 8);  // 调 格式化到缓冲
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)Buffer, 0);  // 调 对象池借出（按池号取可用对象）
    goto LABEL_147;
  }
  pNameEditCtrl_2 = *(uint32_t *)(this + 256);  // this+256〔pNameEditCtrl〕
  v33 = pNameEditCtrl_2 + 160;  // fld_1003=this+256 pNameEditCtrl
  if ( *(uint32_t *)(pNameEditCtrl_2 + 192) != 0 )  // fld_1003=this+256 pNameEditCtrl
    v33 = pNameEditCtrl_2 + 180;  // fld_1003=this+256 pNameEditCtrl
  if ( *(uint32_t *)(v33 + 12) == 0 )
  {
    v34 = sub_422E70(142);  // 调 存 CStringManager::getStr 取本地化串
    goto LABEL_164;
  }
  psz = (const char *)sub_69B740(pNameEditCtrl_2);  // fld_1003=this+256 pNameEditCtrl
  if ( (uint8_t)sub_46B250(psz) != 0 )  // 调 频道名忽略大小写查找
  {
    v34 = sub_422E70(144);  // 调 存 CStringManager::getStr 取本地化串
    goto LABEL_164;
  }
  nLen = strlen(psz);  // 调 返回字符串长度（逐字节扫描）
  v37 = 0;
  if ( nLen <= 0 )
  {
LABEL_146:
    sub_423200(dword_8F7B08, 5);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    v47[0] = *(uint8_t *)(this + 180);  // this+180〔pBtnCreateChar〕
    sub_423290(v47, 1);  // 调 写 4B 长度
    fld_1004 = (const char *)sub_69B740(*(uint32_t *)(this + 256));  // this+256〔pNameEditCtrl〕
    sub_41C100(fld_1004);  // 调 写字符串到发送缓冲（4B 长度 + 内容）
    sub_423380(dword_8F7B08);  // dword_8F7B08 = 网络连接对象（发包 API 全局实例）
    sub_40BE20(v40, "\n Character Name send");  // 日志/输出串: Character Name send
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
    goto LABEL_147;
  }
  while ( 1 )  // 无限循环
  {
    v38 = psz[v37];
    if ( v38 >= 0
      || v38 != -127
      && v38 != -126
      && v38 != -125
      && v38 != -124
      && v38 != -121
      && v38 != -120
      && v38 != -119
      && v38 != -118
      && v38 != -117
      && v38 != -116
      && v38 != -115
      && v38 != -114
      && v38 != -113
      && v38 != -112
      && v38 != -111
      && v38 != -110
      && v38 != -109
      && v38 != -108
      && v38 != -107
      && v38 != -106
      && v38 != -105
      && v38 != -104
      && v38 != -103
      && v38 != -102
      && v38 != -101
      && v38 != -100
      && v38 != -99
      && v38 != -98
      && v38 != -97
      && v38 != -32
      && v38 != -31
      && v38 != -30
      && v38 != -29
      && v38 != -28
      && v38 != -27
      && v38 != -26
      && v38 != -25
      && v38 != -24
      && v38 != -23
      && v38 != -22
      && v38 != -19
      && v38 != -18
      && v38 != -6
      && v38 != -5
      && v38 != -4 )
    {
      break;
    }
    ++v37;
LABEL_145:
    if ( ++v37 >= nLen )
      goto LABEL_146;
  }
  if ( v38 != 39 && v38 != 32 && v38 != 9 && v38 != 92 && v38 != 37 && v38 != 60 && v38 != 62 && v38 != 34 )  // 若 v38 != 39 与/或 v38 != 32 与/或 v38 != 9
    goto LABEL_145;
  sub_40BE20(v38, "\n Character Name Error : 0x%x", v38);  // 日志/输出串: Character Name Error : 0xx
  v34 = sub_422E70(143);  // 调 存 CStringManager::getStr 取本地化串
LABEL_164:
  sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v34, 0);  // 调 对象池借出（按池号取可用对象）
LABEL_147:
  *(uint8_t *)(*(uint32_t *)(this + 252) + 16) = 0;  // this+252〔pNameEditBox〕
  v41 = *((uint32_t *)dword_8F8528 + 7);  // dword_8F8528 = 主管理器
  if ( *(uint8_t *)(v41 + 256) == 0 )
  {
    dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v41 + 124) + 12);  // 通用对象全局槽 1
    dword_79BE54 = dword_79BE4C;  // 通用对象全局槽 2
  }
  sub_4BF300(dword_8F8558, 0, 1);  // 调 槽写侧（+64 + 索引）
LABEL_150:
  pBtnExitB = *(uint32_t *)(this + 264);  // this+264〔pBtnExitB〕
  if ( *(uint8_t *)(pBtnExitB + 17) != 0 && dword_79BE34 == *(uint32_t *)(pBtnExitB + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    *(uint8_t *)(*(uint32_t *)(this + 252) + 16) = 0;  // this+252〔pNameEditBox〕
    v43 = *((uint32_t *)dword_8F8528 + 7);  // dword_8F8528 = 主管理器
    if ( *(uint8_t *)(v43 + 256) == 0 )
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v43 + 124) + 12);  // 通用对象全局槽 1
      dword_79BE54 = dword_79BE4C;  // 通用对象全局槽 2
    }
    sub_4BF300(dword_8F8558, 0, 1);  // 调 槽写侧（+64 + 索引）
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  result = *(uint8_t **)(this + 268);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 当前动画对象指针(帧同步比对基准)
  {
    pCharCardBoard_2 = *(uint32_t *)(this + 52);  // this+52〔pCharCardBoard〕
    *(uint32_t *)(this + 44) = 0;  // this+44〔nSelectedChar〕
    *(uint8_t *)(pCharCardBoard_2 + 16) = 1;  // fld_343=this+52 pCharCardBoard
    *(uint8_t *)(*(uint32_t *)(this + 176) + 16) = 0;  // this+704 = 表现/名字快照[24]
    pCharEntryVecBegin_2 = *(uint32_t *)(this + 64);  // this+256 = 基类四元组字节槽 3
    if ( pCharEntryVecBegin_2 == 0 || (*(uint32_t *)(this + 68) - pCharEntryVecBegin_2) >> 2 > -1 )  // this+68〔nCharCount〕
    {
      pBtnCharName_ = *(uint32_t *)(this + 108);  // this+108〔pBtnCharName〕
      *(uint32_t *)(this + 92) = -1;  // this+92〔nCurChar〕
      *(uint8_t *)(pBtnCharName_ + 17) = 0;  // fld_6C2=this+108 pBtnCharName
      *(uint8_t *)(*(uint32_t *)(this + 112) + 16) = 0;  // this+112〔pBtnCharCancel〕
      sub_44E850(dword_8F8528, 30);  // 调 按池号批量回收活动对象
    }
    *(uint32_t *)(this + 172) = -1;  // this+688 = 表现/名字快照[2]
    return sub_432EA0("CLICK_BUTTON3", -1, 0, 0);  // 调 音效播放包装（非空判定）
  }
  return result;
}


// ============================================================
// 【分区 10】界面杂项（0x46CB70-0x46DE70）
// ============================================================
// ------------------------------------------------------------
// 0x46CB70 sub_46CB70 —— 144 字节区间前向拷贝
// [nArg1, nArg2) 区间每 144 字节一项，经 ·sub_46C250 拷到 nArg3 起。
// ------------------------------------------------------------
int /*cdecl*/ sub_46CB70(int nArg1, int nArg2, int nArg3)  // 函数: 144 字节区间前向拷贝
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 144 )
    result = sub_46C250(i, nArg3);  // 调 与 ·sub_46C180 同构（差异：浅拷贝域不同）
  return result;
}



// ------------------------------------------------------------
// 0x46CBA0 sub_46CBA0 —— 144 字节区间反向拷贝（重叠安全）
// 自末项起 nArg2 与 nArg3 各减 144 逐项 ·sub_46C250，供自重叠搬移使用。
// ------------------------------------------------------------
int /*cdecl*/ sub_46CBA0(int nArg1, int nArg2, int nArg3)  // 函数: 144 字节区间反向拷贝（重叠安全）
{
  int nArg22; // esi
  int nArg32; // edi

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    nArg22 -= 144;
    nArg32 -= 144;
    sub_46C250(nArg32, nArg22);  // 调 与 ·sub_46C180 同构（差异：浅拷贝域不同）
  }
  while ( nArg22 != nArg1 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x46CBE0 sub_46CBE0 —— 144 字节区间移动构造
// [nArg1, nArg2) 每 144 字节经 ·sub_46C180 在 nArg3 起原位构造（不释放源）。
// 异常计数 v7 用于失败回滚。
// ------------------------------------------------------------
int /*cdecl*/ sub_46CBE0(int nArg1, int nArg2, int nArg3)  // 函数: 144 字节区间移动构造
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )  // 当 nArg1 != nArg2 循环
  {
    LOBYTE(v7) = 1;  // 调 取 16 位值低 8 位
    if ( nArg32 != 0 )
      sub_46C180(nArg32, nArg1);  // 调 条目深拷贝构造（144 字节）
    nArg32 += 144;
    LOBYTE(v7) = 0;  // 调 取 16 位值低 8 位
    nArg1 += 144;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x46CC80 sub_46CC80 —— 转发 ·sub_46CBA0（反向拷贝别名）
// store 系 vector 删除区间时的左移入口。
// ------------------------------------------------------------
int /*cdecl*/ sub_46CC80(int nArg1, int nArg2, int nArg3)  // 函数: 转发 ·sub_46CBA0（反向拷贝别名）
{
  return sub_46CBA0(nArg1, nArg2, nArg3);  // 调 144 字节区间反向拷贝（重叠安全）
}



// ------------------------------------------------------------
// 0x46CCA0 sub_46CCA0 —— 定长 144 字节移动构造
// nArg2 个 144 字节项自 nArg1 起逐项 ·sub_46C180 构造到 nArg3 起。
// ------------------------------------------------------------
int /*cdecl*/ sub_46CCA0(int nArg1, int nArg2, int nArg3)  // 函数: 定长 144 字节移动构造
{
  int nArg12; // esi
  int result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg12 = nArg1;
  v6[4] = v6;
  v6[3] = nArg1;
  v7 = 0;
  while ( nArg2 != 0 )  // 当 nArg2 != 0 循环
  {
    LOBYTE(v7) = 1;  // 调 取 16 位值低 8 位
    if ( nArg12 != 0 )
      result = sub_46C180(nArg12, nArg3);  // 调 条目深拷贝构造（144 字节）
    --nArg2;
    nArg12 += 144;
    LOBYTE(v7) = 0;  // 调 取 16 位值低 8 位
  }
  return result;
}



// ------------------------------------------------------------
// 0x46CD30 sub_46CD30 —— 定长移动构造并返回尾指针
// 转 ·sub_46CCA0 后返回 nArg1 + 144*nArg2（新尾址）。
// ------------------------------------------------------------
int /*stdcall*/ sub_46CD30(int nArg1, int nArg2, int nArg3)  // 函数: 定长移动构造并返回尾指针
{
  sub_46CCA0(nArg1, nArg2, nArg3);  // 调 定长 144 字节移动构造
  return nArg1 + 144 * nArg2;
}



// ------------------------------------------------------------
// 0x46CD60 sub_46CD60 —— 条目 vector 扩容与定点插入
// 先在栈上以 nArg4 构造临时副本（失败可回滚）；uArg3 为插入个数，上限 29826161 减现有小于 uArg3 时 sub_41D5A0 抛 vector 超长（串自证）。
// 尾部有余量则原位插入，否则重分配并分段移动构造（sub_46CBE0/46CC80/46CB70/46CD30/46CCA0）。
// 末 j__free 旧块并以 sub_41CBF0 回滚析构临时副本。
// ------------------------------------------------------------
void /*thiscall*/ sub_46CD60(int *this, int pArg2, unsigned int uArg3, int nArg4)  // 函数: 条目 vector 扩容与定点插入
{
  int pVecEnd_13; // ebx
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
  int fld_e12; // [esp-18h] [ebp-D4h]
  int fld_e28; // [esp-10h] [ebp-CCh]
  int fld_e25; // [esp-Ch] [ebp-C8h]
  unsigned int fld_e24; // [esp-8h] [ebp-C4h]
  int v23; // [esp+0h] [ebp-BCh] BYREF
  void *Block; // [esp+Ch] [ebp-B0h]
  int *pThis; // [esp+10h] [ebp-ACh]
  char *pMem2; // [esp+14h] [ebp-A8h]
  uint8_t v27[144]; // [esp+18h] [ebp-A4h] BYREF
  int dword_796E502; // [esp+A8h] [ebp-14h]
  int *v29; // [esp+ACh] [ebp-10h]
  int v30; // [esp+B8h] [ebp-4h]
  int v31; // [esp+C4h] [ebp+8h]
  int v32; // [esp+C8h] [ebp+Ch]
  int fld_e232; // [esp+CCh] [ebp+10h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  v29 = &v23;
  pThis = this;
  sub_46C180((int)v27, nArg4);  // 调 条目深拷贝构造（144 字节）
  pVecEnd_13 = *(this + 1);  // this+4 = pHostObj
  fld_e3 = 0;
  v30 = 0;
  if ( pVecEnd_13 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - pVecEnd_13) / 144;  // this+12 = 技能槽记录次字
  if ( uArg3 != 0 )
  {
    if ( pVecEnd_13 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - pVecEnd_13) / 144;  // this+8 = 技能槽记录首字
    else
      fld_e2 = 0;  // fld_e2=this+8 物品 id
    if ( 29826161 - fld_e2 < uArg3 )  // fld_e2=this+8 物品 id
      sub_41D5A0(this);  // 调 [串: vector<T> too long]
    if ( pVecEnd_13 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - pVecEnd_13) / 144;  // this+8 = 技能槽记录首字
    else
      fld_e22 = 0;  // fld_e22=this+8 物品 id
    if ( fld_e3 >= uArg3 + fld_e22 )  // fld_e3=this+12 物品类型号
    {
      fld_e23 = *(this + 2);  // this+8 = 技能槽记录首字
      fld_e232 = fld_e23;  // fld_e23=this+8 物品 id
      if ( (fld_e23 - pArg2) / 144 >= uArg3 )  // fld_e23=this+8 物品 id
      {
        v31 = fld_e23 - 144 * uArg3;  // fld_e23=this+8 物品 id
        *(this + 2) = sub_46CBE0(v31, fld_e23, fld_e23);  // 调 144 字节区间移动构造
        sub_46CC80(pArg2, v31, fld_e232);  // 调 转发 ·sub_46CBA0（反向拷贝别名）
        sub_46CB70(pArg2, pArg2 + 144 * uArg3, v27);  // 调 144 字节区间前向拷贝
      }
      else
      {
        sub_46CBE0(pArg2, fld_e23, pArg2 + 144 * uArg3);  // 调 144 字节区间移动构造
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 144;  // this+8 = 技能槽记录首字
        fld_e25 = *(this + 2);  // this+8 = 技能槽记录首字
        LOBYTE(v30) = 3;  // 调 取 16 位值低 8 位
        sub_46CD30(fld_e25, fld_e24, v27);  // 调 定长移动构造并返回尾指针
        fld_e26 = 144 * uArg3 + *(this + 2);  // this+8 = 技能槽记录首字
        *(this + 2) = fld_e26;  // this+8 = 技能槽记录首字
        v30 = 0;
        sub_46CB70(pArg2, fld_e26 - 144 * uArg3, v27);  // 调 144 字节区间前向拷贝
      }
    }
    else
    {
      if ( 29826161 - (fld_e3 >> 1) >= fld_e3 )  // fld_e3=this+12 物品类型号
        v10 = (fld_e3 >> 1) + fld_e3;  // fld_e3=this+12 物品类型号
      else
        v10 = 0;
      if ( pVecEnd_13 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - pVecEnd_13) / 144;  // this+8 = 技能槽记录首字
      else
        fld_e27 = 0;  // fld_e27=this+8 物品 id
      if ( v10 < uArg3 + fld_e27 )  // fld_e27=this+8 物品 id
        v10 = uArg3 + sub_46B040(this);  // 调 144 字节项数组计数
      v32 = 144 * v10;
      pMem = (char *)operator new(144 * v10);  // 分配 144 × v10 字节数组
      fld_e12 = *(this + 1);  // this+4 = pHostObj
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v30) = 1;  // 调 取 16 位值低 8 位
      pMem2 = (char *)sub_46CBE0(fld_e12, pArg2, (int)pMem);  // 调 144 字节区间移动构造
      sub_46CCA0((int)pMem2, uArg3, (int)v27);  // 调 定长 144 字节移动构造
      fld_e28 = *(this + 2);  // this+8 = 技能槽记录首字
      pMem2 += 144 * uArg3;
      sub_46CBE0(pArg2, fld_e28, (int)pMem2);  // 调 144 字节区间移动构造
      fld_e13 = *(this + 1);  // this+4 = pHostObj
      v30 = 0;
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 144;  // this+8 = 技能槽记录首字
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);  // this+4 = pHostObj
      if ( fld_e14 != 0 )  // fld_e14=this+4 宿主对象
      {
        sub_41DDD0(fld_e14, *(this + 2));  // 调 区间析构（步长 144B 逐元素 0x41CBF0）
        j__free((void *)*(this + 1));  // this+4 = pHostObj
      }
      *(this + 3) = (int)&pMem[v32];  // this+12 = 技能槽记录次字
      *(this + 2) = (int)&pMem[144 * v14];  // this+8 = 技能槽记录首字
      *(this + 1) = (int)pMem;  // this+4 = pHostObj
    }
  }
  v30 = -1;
  sub_41CBF0((int)v27);  // 调 成员析构（两个 std::string + crypt4byte 子对象）
}


// ------------------------------------------------------------
// 0x46D0A0 sub_46D0A0 —— 插入一格并返回新位置
// 先算目标下标 (nArg3 - 首址)/144（空容器记 0），调 ·sub_46CD60(this, nArg3, 1, nArg4)。
// 再经 *uArg2 返回重分配后的同位地址。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_46D0A0(int *this, uint32_t *uArg2, int nArg3, int nArg4)  // 函数: 插入一格并返回新位置
{
  int pVecEnd_5; // esi
  int v6; // esi

  pVecEnd_5 = *(this + 1);  // this+4 = pHostObj
  if ( pVecEnd_5 != 0 && (*(this + 2) - pVecEnd_5) / 144 != 0 )  // this+8 = 技能槽记录首字
    v6 = (nArg3 - pVecEnd_5) / 144;  // pVecEnd_5=this+4 宿主对象
  else
    v6 = 0;
  sub_46CD60(this, nArg3, 1u, nArg4);  // 调 条目 vector 扩容与定点插入
  *uArg2 = *(this + 1) + 144 * v6;  // this+4 = pHostObj
  return uArg2;
}



// ------------------------------------------------------------
// 0x46D110 sub_46D110 —— 尾部追加或插入（容量判定）
// 有可用容量时以 ·sub_46CCA0 在原尾原位构造并 +2 加 144；否则经 ·sub_46D0A0 走插入路径。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_46D110(int *this, int nArg2)  // 函数: 尾部追加或插入（容量判定）
{
  int pVecEnd_6; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  pVecEnd_6 = *(this + 1);  // this+4 = pHostObj
  if ( pVecEnd_6 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - pVecEnd_6) / 144;  // this+8 = 技能槽记录首字
  else
    fld_e2 = 0;  // fld_e2=this+8 物品 id
  if ( pVecEnd_6 == 0 || fld_e2 >= (*(this + 3) - pVecEnd_6) / 144 )  // this+12 = 技能槽记录次字
    return sub_46D0A0(this, &nArg2, *(this + 2), nArg2);  // 调 插入一格并返回新位置
  fld_e22 = *(this + 2);  // this+8 = 技能槽记录首字
  result = (uint32_t *)sub_46CCA0(fld_e22, 1, nArg2);  // 调 定长 144 字节移动构造
  *(this + 2) = fld_e22 + 144;  // this+8 = 技能槽记录首字
  return result;
}



// ------------------------------------------------------------
// 0x46D1A0 sub_46D1A0 —— 选角资源数组释放与状态复位
// this+64 指针数组逐项经 vt 析构(1) 后 j__free；+80..+84 区间逐项 sub_41CBF0 析构后释放 +80。
// 末段复位 +92=-1、+108 对象 +17=0、+112 对象 +16=0、sub_44E850(dword_8F8528,30)、+104 对象 +17=1。
// ------------------------------------------------------------
int /*thiscall*/ sub_46D1A0(int this)  // 函数: 选角资源数组释放与状态复位
{
  int fld_40; // eax
  int fld_44; // ebx
  int i; // edi
  void (/*thiscall*/ ***fld_402)(uint32_t, int); // ecx
  int fld_50; // edi
  int j; // ebx
  int fld_403; // ecx
  int result; // eax
  int fld_6C; // ecx

  fld_40 = *(uint32_t *)(this + 64);  // this+256 = 基类四元组字节槽 3
  if ( fld_40 != 0 )  // fld_40=this+256 参数灌入槽 3
    fld_44 = (*(uint32_t *)(this + 68) - fld_40) >> 2;  // this+68〔nCharCount(推断)〕
  else
    fld_44 = 0;  // fld_44=this+68 nCharCount
  for ( i = 0; i < fld_44; ++i )  // fld_44=this+68 nCharCount
  {
    fld_402 = *(void (/*thiscall*/ ****)(uint32_t, int))(*(uint32_t *)(this + 64) + 4 * i);  // this+256 = 基类四元组字节槽 3
    if ( fld_402 != nullptr )  // 若 fld_402 有效（非空）
      (**fld_402)(fld_402, 1);  // 调 fld_402 的虚函数（vt+0）
  }
  if ( *(uint32_t *)(this + 64) != 0 )  // this+256 = 基类四元组字节槽 3
    j__free(*(void **)(this + 64));  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 72) = 0;  // this+72〔nSnapshot72(推断)〕等 2 字段
  fld_50 = *(uint32_t *)(this + 80);  // this+80〔nAuraStage(推断)〕
  if ( fld_50 != 0 )  // fld_50=this+80 nAuraStage
  {
    for ( j = *(uint32_t *)(this + 84); fld_50 != j; fld_50 += 144 )  // this+84〔pFxObjA(推断)〕
      sub_41CBF0(fld_50);  // 调 成员析构（两个 std::string + crypt4byte 子对象）
    j__free(*(void **)(this + 80));  // 调 堆释放
  }
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  *(uint32_t *)(this + 84) = 0;  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 88) = 0;  // this+88〔pFxObjB(推断)〕等 2 字段
  fld_403 = *(uint32_t *)(this + 64);  // this+256 = 基类四元组字节槽 3
  if ( fld_403 != 0 && (result = (*(uint32_t *)(this + 68) - fld_403) >> 2) <= -1 )  // this+68〔nCharCount(推断)〕
  {
    *(uint8_t *)(*(uint32_t *)(this + 104) + 17) = 1;  // this+104〔nTimerEnd(推断)〕
  }
  else
  {
    fld_6C = *(uint32_t *)(this + 108);  // this+108〔nAdd108(推断)〕
    *(uint32_t *)(this + 92) = -1;  // this+92〔pFxObjC(推断)〕等 2 字段
    *(uint8_t *)(fld_6C + 17) = 0;  // fld_6C=this+108 nAdd108
    *(uint8_t *)(*(uint32_t *)(this + 112) + 16) = 0;  // this+112〔pHostComp112〕
    sub_44E850(dword_8F8528, 30);  // 调 按池号批量回收活动对象
    result = *(uint32_t *)(this + 104);  // this+104〔nTimerEnd(推断)〕
    *(uint8_t *)(result + 17) = 1;  // result=this+104 nTimerEnd
  }
  return result;  // result=this+104 nTimerEnd
}



// ------------------------------------------------------------
// 0x46D280 sub_46D280 —— 追加条目与提示阈值
// this+60 向量（4 字节项）有余量则原位写 nArg2，否则 sub_4BBBA0 定点插入。
// 再 sub_46D110(this+76, nArg3) 追加另一向量；本向量长度达 8 时把 +104 对象 +17 清 0（隐藏提示条）。
// ------------------------------------------------------------
int /*thiscall*/ sub_46D280(int *this, int nArg2, int nArg3)  // 函数: 追加条目与提示阈值
{
  int fld_e16; // edx
  uint32_t *pThis_F; // esi
  unsigned int fld_e17; // ecx
  int *nArg22; // eax
  int result; // eax

  fld_e16 = *(this + 16);  // this+64〔apServerTabBtn(推断)〕
  pThis_F = this + 15;  // this+60〔nFadeValue60〕
  if ( fld_e16 != 0 )  // fld_e16=this+64 apServerTabBtn
    fld_e17 = (*(this + 17) - fld_e16) >> 2;  // this+68〔nCharCount(推断)〕
  else
    fld_e17 = 0;  // fld_e17=this+68 nCharCount
  if ( fld_e16 != 0 && fld_e17 < (pThis_F[3] - fld_e16) >> 2 )  // fld_e16=this+64 apServerTabBtn
  {
    nArg22 = (int *)pThis_F[2];
    *nArg22 = nArg2;
    pThis_F[2] = nArg22 + 1;
  }
  else
  {
    sub_4BBBA0((void *)pThis_F[2], 1, (int)&nArg2);  // 调 uint32 vector 定点插入（_Insert_n 语义）
  }
  sub_46D110(this + 19, nArg3);  // 调 尾部追加或插入（容量判定）
  result = pThis_F[1];
  if ( result != 0 && (pThis_F[2] - result) >> 2 >= 8 )
    *(uint8_t *)(*(this + 26) + 17) = 0;  // this+104〔nTimerEnd(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x46D300 sub_46D300 —— 选角界面复位与资源释放
// +4 使能时：this+16 定时器归 0、+29/+30 清零、+44=0、+52 对象 +16=1、+176 对象 +16=0。
// +64 列表非空则 +92=-1、+108 对象 +17=0、+112 对象 +16=0、sub_44E850(30)。
// 再 +232 对象 +16=1、+172=-1、+180=0、sub_69C340(-1) 等控件族复位、+212 = sub_418DD0(19)、+224=263、+228=102，末 sub_46D1A0 释放并清 +172/+276。
// ------------------------------------------------------------
char /*thiscall*/ sub_46D300(int this)  // 函数: 选角界面复位与资源释放
{
  char result; // al
  int fld_34; // eax
  int fld_40; // ecx
  int fld_6C; // edx
  int fld_E8; // ecx
  int v7; // eax

  result = *(uint8_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( result != 0 )  // 若结果非 0（成功）
  {
    *(uint8_t *)(this + 29) = 0;  // this+116〔会话上下文〕
    *(uint8_t *)(this + 30) = 0;  // this+120 = 动画对象指针
    sub_698F90(this + 16, 0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
    fld_34 = *(uint32_t *)(this + 52);  // this+52〔bAuraState(推断)〕等 2 字段
    *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
    *(uint8_t *)(fld_34 + 16) = 1;  // fld_34=this+52 bAuraState
    *(uint8_t *)(*(uint32_t *)(this + 176) + 16) = 0;  // this+704 = 表现/名字快照[24]
    fld_40 = *(uint32_t *)(this + 64);  // this+256 = 基类四元组字节槽 3
    if ( fld_40 == 0 || (*(uint32_t *)(this + 68) - fld_40) >> 2 > -1 )  // this+68〔nCharCount(推断)〕
    {
      fld_6C = *(uint32_t *)(this + 108);  // this+108〔nAdd108(推断)〕
      *(uint32_t *)(this + 92) = -1;  // this+92〔pFxObjC(推断)〕等 2 字段
      *(uint8_t *)(fld_6C + 17) = 0;  // fld_6C=this+108 nAdd108
      *(uint8_t *)(*(uint32_t *)(this + 112) + 16) = 0;  // this+112〔pHostComp112〕
      sub_44E850(dword_8F8528, 30);  // 调 按池号批量回收活动对象
    }
    fld_E8 = *(uint32_t *)(this + 232);  // this+232〔bSyncFlag〕
    *(uint32_t *)(this + 172) = -1;  // this+688 = 表现/名字快照[2]
    *(uint32_t *)(this + 180) = 0;  // this+180〔nRadius(推断)〕
    *(uint8_t *)(fld_E8 + 16) = 1;  // fld_E8=this+232 bSyncFlag
    sub_69C340(-1);
    sub_69C400(0);
    sub_69C360(dword_98BA18[0], 0);
    *(uint8_t *)(*(uint32_t *)(this + 188) + 17) = 0;  // this+188〔nStatusIdx(推断)〕
    *(uint8_t *)(*(uint32_t *)(this + 192) + 17) = 1;  // this+192〔nDlgId(推断)〕
    *(uint8_t *)(*(uint32_t *)(this + 196) + 17) = 1;
    *(uint8_t *)(*(uint32_t *)(this + 200) + 17) = 1;  // this+200〔nMainState(推断)〕
    *(uint8_t *)(*(uint32_t *)(this + 252) + 16) = 0;  // this+252〔nQuad2〕
    v7 = *((uint32_t *)dword_8F8528 + 7);  // dword_8F8528 = 主管理器
    if ( *(uint8_t *)(v7 + 256) == 0 )
    {
      dword_79BE4C = *(uint32_t *)(*(uint32_t *)(v7 + 124) + 12);  // 通用对象全局槽 1
      dword_79BE54 = dword_79BE4C;  // 通用对象全局槽 2
    }
    CNCommandChecker__vmt40(0, 1);
    *(uint32_t *)(this + 204) = sub_418DD0(0);  // 调 资源句柄 (101)
    *(uint32_t *)(this + 208) = sub_418DD0(17);  // 调 资源句柄 (101)
    *(uint32_t *)(this + 216) = 256;  // this+216〔bField216(推断)〕
    *(uint32_t *)(this + 220) = 72;  // this+220〔nSnapDst220(推断)〕
    *(uint32_t *)(this + 212) = sub_418DD0(19);  // 调 资源句柄 (101)
    *(uint32_t *)(this + 224) = 263;  // this+224〔nSnapDst224(推断)〕
    *(uint32_t *)(this + 228) = 102;  // this+228〔nSnapDst228(推断)〕
    *(uint8_t *)(this + 50) = 0;  // this+50〔bCharSelSent〕
    *(uint8_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
    result = sub_46D1A0(this);  // 调 选角资源数组释放与状态复位
    *(uint32_t *)(this + 172) = -1;  // this+688 = 表现/名字快照[2]
    *(uint8_t *)(this + 276) = 0;  // this+276〔pMapEntry〕
  }
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x46D4A0 sub_46D4A0 —— 选角界面控件构建
// +4 使能时 operator new(0x68) 配 sub_426BD0（nengine::IControl 构造，自证）建多件，+100/+184 取自 dword_99FCC8+20 上下文。
// sub_43C410（nengine::CNButton，自证）、sub_43C250（nengine::CNFrame，自证）与 sub_69C780/69C7B0/69C2D0/69C520/69C440 控件族建齐。
// sub_69A5F0(561,429) 定位、sub_69A840 逐个登记（含 dword_8F8528 的 2/3 号件），末转 ·sub_46D300 收尾复位。
// ------------------------------------------------------------
char /*thiscall*/ sub_46D4A0(int this)  // 函数: 选角界面控件构建
{
  char result; // al
  void *pMem; // eax
  int v4; // eax
  void *pMem2; // eax
  int v6; // eax
  uint32_t *pMem3; // eax
  uint32_t *fld_64; // eax
  uint32_t *pMem4; // eax
  uint32_t *fld_642; // eax
  uint32_t *pMem5; // eax
  uint32_t *fld_643; // eax
  uint32_t *pMem6; // eax
  uint32_t *fld_644; // eax
  uint32_t *pMem7; // eax
  uint32_t *fld_645; // eax
  void *pMem8; // eax
  int v18; // eax
  uint32_t *pMem9; // eax
  uint32_t *fld_B8; // eax
  uint32_t *pMem10; // eax
  uint32_t *fld_B82; // eax
  uint32_t *pMem11; // eax
  uint32_t *fld_B83; // eax
  uint32_t *pMem12; // eax
  uint32_t *fld_B84; // eax
  int v27; // ebx
  uint32_t *pThis_BC; // edi
  uint32_t *fld_B85; // eax
  int v30; // ebx
  uint32_t *pMem13; // edi
  uint32_t *pMem14; // eax
  uint32_t *pMem142; // edi
  uint32_t *pMem1422; // ecx
  uint32_t *pMem15; // eax
  uint32_t *pMem152; // edi
  int fld_B86; // ebx
  uint32_t *pMem16; // eax
  uint32_t *pMem162; // edi
  uint32_t *pMem1622; // ecx
  int v41; // eax
  uint32_t *pMem17; // eax
  uint32_t *pMem172; // edi
  int fld_B87; // ebx
  uint32_t *pMem1722; // ecx
  uint32_t *pMem18; // eax
  uint32_t *pMem182; // edi
  int fld_B88; // ebx
  uint32_t *pMem1822; // ecx
  uint32_t *pMem19; // eax
  uint32_t *pMem192; // edi
  int fld_B89; // ebx
  void *Block; // [esp+8h] [ebp-14h]
  void *Blocka; // [esp+8h] [ebp-14h]
  uint32_t *pThis_EC; // [esp+Ch] [ebp-10h]

  result = *(uint8_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( result == 0 )  // result=this+4 宿主对象
  {
    *(uint8_t *)(this + 4) = 1;  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 100) = **(uint32_t **)(dword_99FCC8 + 20);  // this+100〔bEnchantDone(推断)〕
    *(uint32_t *)(this + 184) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 4);  // this+184〔bSingleTarget(推断)〕
    pMem = operator new(0x68u);  // operator new 分配 104 字节
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      v4 = sub_426BD0(pMem);  // 调 nengine::IControl 构造
    else
      v4 = 0;
    *(uint32_t *)(this + 12) = v4;  // this+12〔nSkillRec12(推断)〕等 2 字段
    pMem2 = operator new(0x68u);  // operator new 分配 104 字节
    if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
      v6 = sub_426BD0(pMem2);  // 调 nengine::IControl 构造
    else
      v6 = 0;
    *(uint32_t *)(this + 52) = v6;  // this+52〔bAuraState(推断)〕等 2 字段
    *(uint32_t *)(v6 + 28) = 640;
    *(uint32_t *)(v6 + 32) = 480;
    *(uint32_t *)(*(uint32_t *)(this + 52) + 68) = this + 8;  // this+52〔bAuraState(推断)〕等 2 字段
    sub_69A840(*(uint32_t *)(this + 52));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    pMem3 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
      fld_64 = sub_43C410(pMem3, *(uint32_t *)(this + 100), 5, 6, 7, 8, 0, 0);  // 调 nengine::CNButton 构造
    else
      fld_64 = nullptr;
    *(uint32_t *)(this + 104) = fld_64;  // this+104〔nTimerEnd(推断)〕
    sub_69A5F0(fld_64, 68, 417);  // 调 设位、sub_69A840 登记
    *(uint32_t *)(*(uint32_t *)(this + 104) + 68) = this + 8;  // this+104〔nTimerEnd(推断)〕
    sub_69A840(*(uint32_t *)(this + 104));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    pMem4 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
      fld_642 = sub_43C410(pMem4, *(uint32_t *)(this + 100), 1, 2, 3, 4, 0, 0);  // 调 nengine::CNButton 构造
    else
      fld_642 = nullptr;
    *(uint32_t *)(this + 108) = fld_642;  // this+108〔nAdd108(推断)〕
    sub_69A5F0(fld_642, 152, 417);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 108));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    pMem5 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
      fld_643 = sub_43C410(pMem5, *(uint32_t *)(this + 100), 9, 10, 11, 9, 0, 0);  // 调 nengine::CNButton 构造
    else
      fld_643 = nullptr;
    *(uint32_t *)(this + 112) = fld_643;  // this+112〔pHostComp112〕
    sub_69A5F0(fld_643, 277, 426);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 112));  // this+112〔pHostComp112〕
    pMem6 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem6 != nullptr )  // 若 pMem6 有效（非空）
      fld_644 = sub_43C410(pMem6, *(uint32_t *)(this + 100), 23, 24, 25, -1, 0, 0);  // 调 nengine::CNButton 构造
    else
      fld_644 = nullptr;
    *(uint32_t *)(this + 272) = fld_644;
    sub_69A5F0(fld_644, 438, 427);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 272));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    pMem7 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem7 != nullptr )  // 若 pMem7 有效（非空）
      fld_645 = sub_43C410(pMem7, *(uint32_t *)(this + 100), 17, 18, 19, 17, 0, 0);  // 调 nengine::CNButton 构造
    else
      fld_645 = nullptr;
    *(uint32_t *)(this + 116) = fld_645;  // this+116〔会话上下文〕
    sub_69A5F0(fld_645, 520, 427);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 116));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    *(uint8_t *)(this + 120) = 0;  // this+120〔pAnimObj〕
    *(uint8_t *)(this + 121) = 0;
    *(uint8_t *)(this + 122) = 0;
    *(uint8_t *)(this + 123) = 0;
    *(uint32_t *)(this + 132) = 0;  // this+132〔nAgeTicks〕
    *(uint32_t *)(this + 136) = 6;  // this+136〔nCtx136(推断)〕等 2 字段
    *(uint32_t *)(this + 140) = 12;  // this+140〔nAdd140(推断)〕
    *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
    *(uint32_t *)(this + 148) = 1600;  // this+148〔fAdd148(推断)〕
    *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
    *(uint32_t *)(this + 156) = 0;  // this+156〔nAdd156(推断)〕
    *(uint32_t *)(this + 160) = 0;  // this+160〔fAdd160(推断)〕
    *(uint32_t *)(this + 164) = 0;  // this+164〔fAdd164(推断)〕
    *(uint32_t *)(this + 168) = 0;  // this+672 = 拾取/交互目标有效标志
    *(uint32_t *)(this + 168) = dword_99FCCC;  // this+672 = 拾取/交互目标有效标志
    *(uint32_t *)(this + 148) = 120;  // this+148〔fAdd148(推断)〕
    *(uint32_t *)(this + 132) = 1;  // this+132〔nAgeTicks〕
    *(uint8_t *)(this + 122) = 1;
    *(uint32_t *)(this + 124) = -16777216;  // this+124〔pAuraAnim(推断)〕
    pMem8 = operator new(0x68u);  // operator new 分配 104 字节
    if ( pMem8 != nullptr )  // 若 pMem8 有效（非空）
      v18 = sub_426BD0(pMem8);  // 调 nengine::IControl 构造
    else
      v18 = 0;
    *(uint32_t *)(this + 176) = v18;  // this+704 = 表现/名字快照[24]
    *(uint32_t *)(v18 + 28) = 640;
    *(uint32_t *)(v18 + 32) = 480;
    *(uint32_t *)(*(uint32_t *)(this + 176) + 68) = this + 8;  // this+704 = 表现/名字快照[24]
    sub_69A840(*(uint32_t *)(this + 176));  // this+704 = 表现/名字快照[24]
    pMem9 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem9 != nullptr )  // 若 pMem9 有效（非空）
      fld_B8 = sub_43C410(pMem9, *(uint32_t *)(this + 184), 11, 12, 13, 13, 0, 0);  // 调 nengine::CNButton 构造
    else
      fld_B8 = nullptr;
    *(uint32_t *)(this + 188) = fld_B8;  // this+188〔nStatusIdx(推断)〕
    pMem10 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem10 != nullptr )  // 若 pMem10 有效（非空）
      fld_B82 = sub_43C410(pMem10, *(uint32_t *)(this + 184), 14, 15, 16, 16, 0, 0);  // 调 nengine::CNButton 构造
    else
      fld_B82 = nullptr;
    *(uint32_t *)(this + 192) = fld_B82;  // this+192〔nDlgId(推断)〕
    pMem11 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem11 != nullptr )  // 若 pMem11 有效（非空）
      fld_B83 = sub_43C410(pMem11, *(uint32_t *)(this + 184), 37, 38, 39, 39, 0, 0);  // 调 nengine::CNButton 构造
    else
      fld_B83 = nullptr;
    *(uint32_t *)(this + 196) = fld_B83;
    pMem12 = operator new(0x84u);  // operator new 分配 132 字节
    if ( pMem12 != nullptr )  // 若 pMem12 有效（非空）
      fld_B84 = sub_43C410(pMem12, *(uint32_t *)(this + 184), 43, 44, 45, 45, 0, 0);  // 调 nengine::CNButton 构造
    else
      fld_B84 = nullptr;
    *(uint32_t *)(this + 200) = fld_B84;  // this+200〔nMainState(推断)〕
    v27 = 100;
    pThis_BC = (uint32_t *)(this + 188);  // this+188〔nStatusIdx(推断)〕
    do
    {
      sub_69A5F0((uint32_t *)*pThis_BC, v27, 388);  // 调 设位、sub_69A840 登记
      sub_69A840(*pThis_BC);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
      v27 += 76;
      ++pThis_BC;  // pThis_BC=this+188 nStatusIdx
    }
    while ( v27 < 404 );
    *(uint8_t *)(*(uint32_t *)(this + 200) + 16) = 0;  // this+200〔nMainState(推断)〕
    if ( operator new(0x6Cu) != nullptr )  // operator new 分配 108 字节
      fld_B85 = (uint32_t *)sub_43C250(*(uint32_t *)(this + 184), 28);  // 调 nengine::CNFrame 构造
    else
      fld_B85 = nullptr;
    *(uint32_t *)(this + 232) = fld_B85;  // this+232〔bSyncFlag〕
    sub_69A5F0(fld_B85, 271, 129);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 232));  // this+232〔bSyncFlag〕
    v30 = 4;
    pThis_EC = (uint32_t *)(this + 236);  // this+944 = 名字已播出标志
    do
    {
      pMem13 = operator new(0x84u);  // operator new 分配 132 字节
      if ( pMem13 != nullptr )  // 若 pMem13 有效（非空）
      {
        Block = *(void **)(this + 184);  // this+184 单目标标志
        sub_426BD0(pMem13);  // 调 nengine::IControl 构造
        *pMem13 = &nengine::CNButton::`vftable';  // vftable 复位
        sub_69C780(v31);  // 调 初始化 → ·vmt20(nArg2..nArg8
        sub_69C7B0(Block, v30, v30 + 1, v30 + 2, v30, 0, 0);  // Block=this+184 单目标标志
      }
      else
      {
        v31 = nullptr;
      }
      *v55 = v31;
      sub_69A840(v31);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
      v30 += 3;
      ++v55;
    }
    while ( v30 < 10 );
    sub_69A5F0(*(uint32_t **)(this + 236), 528, 293);  // this+944 = 名字已播出标志
    sub_69A5F0(*(uint32_t **)(this + 240), 543, 292);  // this+240〔nSyncArgB〕
    v32 = operator new(0x6Cu);  // operator new 分配 108 字节
    v33 = v32;
    if ( v32 != nullptr )  // 若 v32 有效（非空）
    {
      sub_426BD0(v32);  // 调 nengine::IControl 构造
      *v33 = &nengine::CNTextBox::`vftable';  // vftable 复位
      sub_69C2D0(pMem142);  // 调 初始化 → ·vmt20(nArg2
      sub_69C520(280, 2048);
      pMem1422 = pMem142;
    }
    else
    {
      pMem1422 = nullptr;
    }
    *(uint32_t *)(this + 244) = pMem1422;  // this+976 = uCfgE976
    sub_69C440(-5512193);
    sub_69C460(1);
    sub_69C480(-16777216);
    sub_69C420(1);
    sub_69C3E0(11);
    sub_69C4C0(dword_99FCCC);  // dword_99FCCC＝与字距
    sub_69A5F0(*(uint32_t **)(this + 244), 282, 141);  // this+976 = uCfgE976
    sub_69A840(*(uint32_t *)(this + 244));  // this+976 = uCfgE976
    pMem15 = operator new(0x84u);  // operator new 分配 132 字节
    pMem152 = pMem15;
    if ( pMem15 != nullptr )  // 若 pMem15 有效（非空）
    {
      fld_B86 = *(uint32_t *)(this + 184);  // this+184〔bSingleTarget(推断)〕
      sub_426BD0(pMem15);  // 调 nengine::IControl 构造
      *pMem152 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(v36);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(v37, 29, 30, 31, 29, 0, 0);
    }
    else
    {
      v36 = nullptr;
    }
    *(uint32_t *)(this + 248) = v36;  // this+992 = uCfgB992
    v36[17] = this + 8;  // this+32〔nHeight〕
    sub_69A5F0(*(uint32_t **)(this + 248), 277, 311);  // this+992 = uCfgB992
    sub_69A840(*(uint32_t *)(this + 248));  // this+992 = uCfgB992
    v38 = operator new(0x6Cu);  // operator new 分配 108 字节
    v39 = v38;
    if ( v38 != nullptr )  // 若 v38 有效（非空）
    {
      Blocka = *(void **)(this + 184);  // this+184 单目标标志
      sub_426BD0(v38);  // 调 nengine::IControl 构造
      *v39 = &nengine::CNFrame::`vftable';  // vftable 复位
      sub_69C6B0(pMem162);  // 调 初始化 → ·vmt20(nArg2
      sub_69C6C0(Blocka, 21);  // Blocka=this+184 单目标标志
      pMem1622 = pMem162;
    }
    else
    {
      pMem1622 = nullptr;
    }
    *(uint32_t *)(this + 252) = pMem1622;  // this+252〔nQuad2〕
    sub_69A5F0(pMem1622, 221, 295);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 252));  // this+252〔nQuad2〕
    if ( operator new(0xE4u) != nullptr )  // operator new 分配 228 字节
      v41 = sub_43C060(12, 183);  // 调 nengine::CNEdit 构造
    else
      v41 = 0;
    *(uint32_t *)(this + 256) = v41;  // this+256〔bQuad3〕
    dword_9D3BD8 = dword_99FCCC;  // dword_9D3BD8＝vt+16
    sub_69A5F0(*(uint32_t **)(this + 256), 235, 322);  // this+256〔bQuad3〕
    sub_69A840(*(uint32_t *)(this + 256));  // this+256〔bQuad3〕
    pMem17 = operator new(0x84u);  // operator new 分配 132 字节
    pMem172 = pMem17;
    if ( pMem17 != nullptr )  // 若 pMem17 有效（非空）
    {
      fld_B87 = *(uint32_t *)(this + 184);  // this+184〔bSingleTarget(推断)〕
      sub_426BD0(pMem17);  // 调 nengine::IControl 构造
      *pMem172 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(v43);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(v44, 22, 23, 24, 22, 0, 0);
      v45 = v43;
    }
    else
    {
      v45 = nullptr;
    }
    *(uint32_t *)(this + 260) = v45;  // this+260〔nQuad4〕
    sub_69A5F0(v45, 263, 341);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 260));  // this+260〔nQuad4〕
    v46 = operator new(0x84u);  // operator new 分配 132 字节
    v47 = v46;
    if ( v46 != nullptr )  // 若 v46 有效（非空）
    {
      v48 = *(uint32_t *)(this + 184);  // this+184〔bSingleTarget(推断)〕
      sub_426BD0(v46);  // 调 nengine::IControl 构造
      *v47 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(pMem182);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(fld_B88, 25, 26, 27, 25, 0, 0);
      pMem1822 = pMem182;
    }
    else
    {
      pMem1822 = nullptr;
    }
    *(uint32_t *)(this + 264) = pMem1822;  // this+264〔nAnimHandle(推断)〕
    sub_69A5F0(pMem1822, 324, 341);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 264));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    pMem19 = operator new(0x84u);  // operator new 分配 132 字节
    pMem192 = pMem19;
    if ( pMem19 != nullptr )  // 若 pMem19 有效（非空）
    {
      fld_B89 = *(uint32_t *)(this + 184);  // this+184〔bSingleTarget(推断)〕
      sub_426BD0(pMem19);  // 调 nengine::IControl 构造
      *pMem192 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(pMem192);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(fld_B89, 32, 33, 34, 32, 0, 0);  // fld_B89=this+184 bSingleTarget
    }
    else
    {
      pMem192 = nullptr;
    }
    *(uint32_t *)(this + 268) = pMem192;  // this+268〔field_10C〕
    sub_69A5F0(pMem192, 561, 429);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 268));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    sub_69A840(*((uint32_t *)dword_8F8528 + 2));  // dword_8F8528 = 主管理器
    sub_69A840(*((uint32_t *)dword_8F8528 + 3));  // dword_8F8528 = 主管理器
    sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));  // dword_8F8528 = 主管理器
    return sub_46D300(this);  // 调 选角界面复位与资源释放
  }
  return result;  // result=this+4 宿主对象
}


// ============================================================
// 【分区 11】CNEntranceChannel 复位与助手（0x46DE70-0x46EB70）
// 复位（+12=6/+16=5）/ vmt8 离开清理 / 预约连接计时器 / reserveConnection。
// ============================================================
// ------------------------------------------------------------
// 0x46DE70 sub_46DE70
// ------------------------------------------------------------
// CNEntranceChannel 复位：+12=6（服务器型数上限）/+16=5（频道型数上限）——
// 与 connectServer 校验阈值一致；其余状态/页签槽清零
int /*thiscall*/ sub_46DE70(int this)  // 实现：与 connectServer 校验阈值一致；其余状态/页签槽清零
{
  *(uint32_t *)(this + 12) = 6;  // this+12〔nSkillRec12(推断)〕等 2 字段
  *(uint32_t *)(this + 16) = 5;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
  *(uint32_t *)(this + 28) = 0;  // this+112 = pHostComp
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  *(uint32_t *)(this + 36) = 0;  // this+144 = pFrameList144
  *(uint32_t *)(this + 40) = 0;  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
  *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 60) = 0;  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 72) = 0;  // this+72〔nSnapshot72(推断)〕等 2 字段
  *(uint32_t *)(this + 76) = 0;  // this+76〔pBtnActionE〕
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  *(uint32_t *)(this + 84) = 0;  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 88) = 0;  // this+88〔pFxObjB(推断)〕等 2 字段
  *(uint32_t *)(this + 92) = 0;  // this+92〔pFxObjC(推断)〕等 2 字段
  *(uint32_t *)(this + 96) = 0;  // this+384 = 动画件名 SSO 容量判据
  *(uint32_t *)(this + 100) = 0;  // this+100〔bEnchantDone(推断)〕
  *(uint32_t *)(this + 104) = 0;  // this+104〔nTimerEnd(推断)〕
  *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
  *(uint32_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(this + 116) = 0;  // this+116〔会话上下文〕
  *(uint32_t *)(this + 120) = 0;  // this+120〔pAnimObj〕
  *(uint32_t *)(this + 124) = 0;  // this+124〔pAuraAnim(推断)〕
  *(uint32_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  *(uint32_t *)(this + 132) = 0;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 136) = 0;  // this+136〔nCtx136(推断)〕等 2 字段
  *(uint32_t *)(this + 140) = 0;  // this+140〔nAdd140(推断)〕
  *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 0;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 156) = 0;  // this+156〔nAdd156(推断)〕
  *(uint32_t *)(this + 160) = 0;  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 164) = 0;  // this+164〔fAdd164(推断)〕
  *(uint32_t *)(this + 168) = 0;  // this+672 = 拾取/交互目标有效标志
  *(uint32_t *)(this + 172) = 0;  // this+688 = 表现/名字快照[2]
  *(uint32_t *)(this + 176) = 0;  // this+704 = 表现/名字快照[24]
  *(uint32_t *)(this + 180) = 0;  // this+180〔nRadius(推断)〕
  *(uint32_t *)(this + 288) = -1;  // this+288〔pMaster288(推断)〕
  *(uint8_t *)(this + 292) = 0;  // this+292〔nOpenMode292(推断)〕
  *(uint32_t *)(this + 300) = 6;  // this+300〔pAnim300〕
  *(uint32_t *)(this + 296) = 6;  // this+296〔bInitFlag296(推断)〕
  *(uint32_t *)(this + 308) = 5;  // this+1232〔pNameTagCtrl(推断)〕
  *(uint32_t *)(this + 304) = 5;  // this+304〔pLayer304(推断)〕
  *(uint32_t *)(this + 316) = -1;
  *(uint32_t *)(this + 312) = -1;
  *(uint8_t *)(this + 332) = 0;  // this+1328 = 动画宿主对象
  *(uint32_t *)(this + 1456) = 0;  // this+1456〔nUdpReportField〕
  return 0;
}



// ------------------------------------------------------------
// 0x46DF70 sub_46DF70 —— 频道对象析构（含临界区释放）
// +4 使能时逐槽以 vt 槽 0（析构，实参 1）释放：+48/+52/+56/+60 四件、+64 起 6 件、+88、+92 起 5 件、
// +112、+116 起 10 件、+156 起 2 件、+164/+168/+172 起 2 件、+180。
// 末尾 DeleteCriticalSection(&stru_98BA28) 释放对象锁并清 +4（线程结束收尾）。
// ------------------------------------------------------------
void /*thiscall*/ sub_46DF70(int this)  // 函数: 频道对象析构（含临界区释放）
{
  void (/*thiscall*/ ***pThis_30)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_34)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_38)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_3C)(uint32_t, int); // ecx
  uint32_t *pThis_40; // edi
  int i; // ebx
  void (/*thiscall*/ ***pThis_58)(uint32_t, int); // ecx
  uint32_t *pThis_5C; // edi
  int j; // ebx
  uint32_t *pThis_AC; // edi
  int k; // ebx
  void (/*thiscall*/ ***pThis_70)(uint32_t, int); // ecx
  uint32_t *pThis_74; // edi
  int m; // ebx
  uint32_t *pThis_9C; // edi
  int n; // ebx
  void (/*thiscall*/ ***pThis_A4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_A8)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_B4)(uint32_t, int); // ecx

  if ( *(uint8_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
  {
    pThis_30 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 48);  // this+192〔nDlgId(推断)〕
    if ( pThis_30 != nullptr )  // 若 pThis_30 有效（非空）
      (**pThis_30)(pThis_30, 1);  // 调 pThis_30 的虚函数（vt+0）
    pThis_34 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 52);  // this+208〔nField208(推断)〕
    *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    if ( pThis_34 != nullptr )  // 若 pThis_34 有效（非空）
      (**pThis_34)(pThis_34, 1);  // 调 pThis_34 的虚函数（vt+0）
    pThis_38 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 56);  // this+224〔nSnapDst224(推断)〕
    *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
    if ( pThis_38 != nullptr )  // 若 pThis_38 有效（非空）
      (**pThis_38)(pThis_38, 1);  // 调 pThis_38 的虚函数（vt+0）
    pThis_3C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 60);  // this+240 = 基类时刻同步参数 B
    *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
    if ( pThis_3C != nullptr )  // 若 pThis_3C 有效（非空）
      (**pThis_3C)(pThis_3C, 1);  // 调 pThis_3C 的虚函数（vt+0）
    *(uint32_t *)(this + 60) = 0;  // this+240 = 基类时刻同步参数 B
    pThis_40 = (uint32_t *)(this + 64);  // this+256 = 基类四元组字节槽 3
    for ( i = 6; i != 0; --i )  // 循环：i 从 6 递减到 0
    {
      if ( *pThis_40 != 0 )  // pThis_40=this+256 参数灌入槽 3
        (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_40)(*pThis_40, 1);  // pThis_40=this+256 参数灌入槽 3
      *pThis_40++ = 0;  // pThis_40=this+256 参数灌入槽 3
    }
    pThis_58 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 88);  // this+352〔uHitCtx352〕
    if ( pThis_58 != nullptr )  // 若 pThis_58 有效（非空）
      (**pThis_58)(pThis_58, 1);  // 调 pThis_58 的虚函数（vt+0）
    *(uint32_t *)(this + 88) = 0;  // this+88〔pFxObjB(推断)〕等 2 字段
    pThis_5C = (uint32_t *)(this + 92);  // this+92〔pFxObjC(推断)〕等 2 字段
    for ( j = 5; j != 0; --j )  // 循环：j 从 5 递减到 0
    {
      if ( *pThis_5C != 0 )  // pThis_5C=this+92 pFxObjC
        (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_5C)(*pThis_5C, 1);  // pThis_5C=this+92 pFxObjC
      *pThis_5C++ = 0;  // pThis_5C=this+92 pFxObjC
    }
    pThis_AC = (uint32_t *)(this + 172);  // this+688 = 表现/名字快照[2]
    for ( k = 2; k != 0; --k )  // 循环：k 从 2 递减到 0
    {
      if ( *pThis_AC != 0 )  // pThis_AC=this+688 表现/名字快照
        (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_AC)(*pThis_AC, 1);  // pThis_AC=this+688 表现/名字快照
      *pThis_AC++ = 0;  // pThis_AC=this+688 表现/名字快照
    }
    pThis_70 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 112);  // this+112〔pHostComp112〕
    if ( pThis_70 != nullptr )  // 若 pThis_70 有效（非空）
      (**pThis_70)(pThis_70, 1);  // 调 pThis_70 的虚函数（vt+0）
    *(uint32_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
    pThis_74 = (uint32_t *)(this + 116);  // this+116〔会话上下文〕
    for ( m = 10; m != 0; --m )  // 循环：m 从 10 递减到 0
    {
      if ( *pThis_74 != 0 )  // pThis_74=this+116 会话上下文
        (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_74)(*pThis_74, 1);  // pThis_74=this+116 会话上下文
      *pThis_74++ = 0;  // pThis_74=this+116 会话上下文
    }
    pThis_9C = (uint32_t *)(this + 156);  // this+156〔nAdd156(推断)〕
    for ( n = 2; n != 0; --n )  // 循环：n 从 2 递减到 0
    {
      if ( *pThis_9C != 0 )  // pThis_9C=this+156 nAdd156
        (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_9C)(*pThis_9C, 1);  // pThis_9C=this+156 nAdd156
      *pThis_9C++ = 0;  // pThis_9C=this+156 nAdd156
    }
    pThis_A4 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 164);  // this+164 第 5 组·+88 增量子倍率
    if ( pThis_A4 != nullptr )  // 若 pThis_A4 有效（非空）
      (**pThis_A4)(pThis_A4, 1);  // 调 pThis_A4 的虚函数（vt+0）
    pThis_A8 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 168);  // this+672 = 拾取/交互目标有效标志
    *(uint32_t *)(this + 164) = 0;  // this+164〔fAdd164(推断)〕
    if ( pThis_A8 != nullptr )  // 若 pThis_A8 有效（非空）
      (**pThis_A8)(pThis_A8, 1);  // 调 pThis_A8 的虚函数（vt+0）
    pThis_B4 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 180);  // this+180 半径/计数
    *(uint32_t *)(this + 168) = 0;  // this+672 = 拾取/交互目标有效标志
    if ( pThis_B4 != nullptr )  // 若 pThis_B4 有效（非空）
      (**pThis_B4)(pThis_B4, 1);  // 调 pThis_B4 的虚函数（vt+0）
    *(uint32_t *)(this + 180) = 0;  // this+180〔nRadius(推断)〕
    DeleteCriticalSection(&stru_98BA28);  // 调 删除临界区
    *(uint8_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  }
}



// ------------------------------------------------------------
// 0x46E100 sub_46E100 —— 界面控件批量隐藏
// 把 +16..+21 六件与 +23..+27 五件的可见字节（前者 +16、后者 +17）逐个非空校验后置 0。
// 再对 +29..+40、+43/+44 两批（共 14 件）直接取指针置 +16 = 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_46E100(uint32_t *this)  // 函数: 界面控件批量隐藏
{
  int fld_e16; // edx
  int result; // eax
  int fld_e17; // edx
  int fld_e18; // edx
  int fld_e19; // edx
  int fld_e20; // edx
  int fld_e21; // edx
  int fld_e23; // edx
  int fld_e24; // edx
  int fld_e25; // edx
  int fld_e26; // edx
  int fld_e27; // edx

  fld_e16 = *(this + 16);  // this+64〔apServerTabBtn(推断)〕
  result = 0;
  if ( fld_e16 != 0 )  // fld_e16=this+64 apServerTabBtn
    *(uint8_t *)(fld_e16 + 16) = 0;  // fld_e16=this+64 apServerTabBtn
  fld_e17 = *(this + 17);  // this+68〔nCharCount(推断)〕
  if ( fld_e17 != 0 )  // fld_e17=this+68 nCharCount
    *(uint8_t *)(fld_e17 + 16) = 0;  // fld_e17=this+68 nCharCount
  fld_e18 = *(this + 18);  // this+72〔nSnapshot72(推断)〕
  if ( fld_e18 != 0 )  // fld_e18=this+72 nSnapshot72
    *(uint8_t *)(fld_e18 + 16) = 0;  // fld_e18=this+72 nSnapshot72
  fld_e19 = *(this + 19);  // this+76〔pBtnActionE〕
  if ( fld_e19 != 0 )  // fld_e19=this+76 pBtnActionE
    *(uint8_t *)(fld_e19 + 16) = 0;  // fld_e19=this+76 pBtnActionE
  fld_e20 = *(this + 20);  // this+80 = nAuraStage
  if ( fld_e20 != 0 )  // fld_e20=this+80 关联角色对象
    *(uint8_t *)(fld_e20 + 16) = 0;  // fld_e20=this+80 关联角色对象
  fld_e21 = *(this + 21);  // this+84 = pFxObjA
  if ( fld_e21 != 0 )  // fld_e21=this+84 插值起点 X
    *(uint8_t *)(fld_e21 + 16) = 0;  // fld_e21=this+84 插值起点 X
  fld_e23 = *(this + 23);  // this+92 = pFxObjC
  if ( fld_e23 != 0 )  // fld_e23=this+92 插值起点 Z
    *(uint8_t *)(fld_e23 + 17) = 0;  // fld_e23=this+92 插值起点 Z
  fld_e24 = *(this + 24);  // this+96〔nStatusMode(推断)〕
  if ( fld_e24 != 0 )  // fld_e24=this+96 nStatusMode
    *(uint8_t *)(fld_e24 + 17) = 0;  // fld_e24=this+96 nStatusMode
  fld_e25 = *(this + 25);  // this+100〔bEnchantDone(推断)〕
  if ( fld_e25 != 0 )  // fld_e25=this+100 bEnchantDone
    *(uint8_t *)(fld_e25 + 17) = 0;  // fld_e25=this+100 bEnchantDone
  fld_e26 = *(this + 26);  // this+104〔nTimerEnd(推断)〕
  if ( fld_e26 != 0 )  // fld_e26=this+104 nTimerEnd
    *(uint8_t *)(fld_e26 + 17) = 0;  // fld_e26=this+104 nTimerEnd
  fld_e27 = *(this + 27);  // this+108〔nAdd108(推断)〕
  if ( fld_e27 != 0 )  // fld_e27=this+108 nAdd108
    *(uint8_t *)(fld_e27 + 17) = 0;  // fld_e27=this+108 nAdd108
  *(uint8_t *)(*(this + 39) + 16) = 0;  // this+156〔nAdd156(推断)〕
  *(uint8_t *)(*(this + 40) + 16) = 0;  // this+160〔fAdd160(推断)〕
  *(uint8_t *)(*(this + 29) + 16) = 0;  // this+116〔会话上下文〕
  *(uint8_t *)(*(this + 30) + 16) = 0;  // this+120 = 动画对象指针
  *(uint8_t *)(*(this + 31) + 16) = 0;  // this+124 = 光环动画件（0x64A190: * 非 0 且宿
  *(uint8_t *)(*(this + 32) + 16) = 0;  // this+128〔szStatusKeyBuf(推断)〕
  *(uint8_t *)(*(this + 33) + 16) = 0;  // this+132〔nAgeTicks〕
  *(uint8_t *)(*(this + 34) + 16) = 0;  // this+136〔nCtx136(推断)〕
  *(uint8_t *)(*(this + 35) + 16) = 0;  // this+140〔nAdd140(推断)〕
  *(uint8_t *)(*(this + 36) + 16) = 0;  // this+144 = pFrameList144
  *(uint8_t *)(*(this + 37) + 16) = 0;  // this+148〔fAdd148(推断)〕
  *(uint8_t *)(*(this + 38) + 16) = 0;  // this+152〔nAdd152(推断)〕
  *(uint8_t *)(*(this + 43) + 16) = 0;  // this+172〔pAppendVecEnd(推断)〕
  *(uint8_t *)(*(this + 44) + 16) = 0;  // this+176〔pAppendVecCap(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x46E1F0 CNEntranceChannel__vmt8
// ------------------------------------------------------------
// CNEntranceChannel::vmt8 —— 离开选区清理：声音通道停（dword_79C0B0 vt+84/88）+ sub_69AB00
int /*thiscall*/ CNEntranceChannel__vmt8(uint32_t *this)  // 实现：CNEntranceChannel::vmt8 —— 离开选区清理：声音通道停（dword_79C0B0 vt+84/88）+ su…
{
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B0 + 28))(dword_79C0B0, 0);  // 调用虚函数（虚表槽 +28）【推断: 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）】
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 84))(dword_79C0B0);  // 调用虚函数（虚表槽 +84）【推断: this+156 字节存取】
  sub_69AB00(*(this + 12));  // this+48〔pCmdVecBegin48(推断)〕
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 88))(dword_79C0B0);  // 调用虚函数（虚表槽 +88）【推断: 标志读 +156（vt+88）】
  return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_79C0A4 + 4))(dword_79C0A4, 0, 0);  // 调用虚函数（虚表槽 +4）
}



// ------------------------------------------------------------
// 0x46E230 sub_46E230 —— 登录串年龄档位（频道列表 user_age 分档）
// 登录串年龄档位：读 this+288（user_age——retrieveServerInfo 由频道列表首字段解析落表），
// <12 归 2、12..14 归 0、>=15 归 1；login_channel 0x470640 组登录串时取作首段 %d。
// ------------------------------------------------------------
int /*thiscall*/ sub_46E230(int *this)  // 函数: 登录串年龄档位（频道列表 user_age 分档）
{
  int fld_e72; // eax

  fld_e72 = *(this + 72);  // this+288〔pMaster288(推断)〕
  if ( fld_e72 < 12 )  // fld_e72=this+288 pMaster288
    return 2;
  if ( fld_e72 >= 15 )  // fld_e72=this+288 pMaster288
    return (fld_e72 < 15) + 1;  // fld_e72=this+288 pMaster288
  return 0;
}



// ------------------------------------------------------------
// 0x46E260 sub_46E260 —— 频道名抽数字 id
// 频道名抽数字 id：扫描入参串，把遇到的 0-9 字符按原序拼接成一串后 atol 返回数值。
// retrieveServerInfo（login_channel 0x471850）以 pBuf[0] = sub_46E260(&pBuf[1]) 填条目首字段。
// ------------------------------------------------------------
int /*stdcall*/ sub_46E260(const char *pArg1)  // 函数: 频道名抽数字 id
{
  signed int nLen; // edx
  signed int psz; // ebx
  char v3; // cl
  unsigned int nLen2; // eax
  char *v5; // edi
  char v6; // cl
  signed int i; // [esp+8h] [ebp-210h] BYREF
  char String[260]; // [esp+Ch] [ebp-20Ch] BYREF
  char Destination[260]; // [esp+110h] [ebp-108h] BYREF
  int dword_796E502; // [esp+214h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  memset(Destination, 0, sizeof(Destination));  // 调 内存按字节填充
  memset(String, 0, sizeof(String));  // 调 内存按字节填充
  nLen = strlen(pArg1);  // 调 返回字符串长度（逐字节扫描）
  psz = 0;
  for ( i = nLen; psz < nLen; ++psz )
  {
    v3 = pArg1[psz];
    if ( v3 >= 48 && v3 <= 57 )  // 若 v3 >= 48 与/或 v3 <= 57
    {
      strncpy(Destination, &pArg1[psz], 1u);  // 调 拷贝至多 Count 字节，不足补 0
      nLen2 = strlen(Destination) + 1;  // 调 返回字符串长度（逐字节扫描）
      v5 = (char *)&i + 3;
      do
        v6 = *++v5;
      while ( v6 != 0 );
      nLen = i;
      qmemcpy(v5, Destination, nLen2);  // 调 内存块拷贝(内联展开)
    }
  }
  return j__atol(String);  // 返回 调 j__atol
}



// ------------------------------------------------------------
// 0x46E350 sub_46E350 —— HTTP 频道列表线程空闲判定
// HTTP 频道列表线程空闲判定：运行旗标 byte_98BB64（线程结构 +268，sub_46EE10 启动时置 1、
// 复位/完成时清 0）为 0 即返真。PVP 频道列表窗 0x632540 据它在「数据就绪直接刷新」与
// 「继续轮询 0x471CC0」间择一。【推断 函数名】
// ------------------------------------------------------------
BOOL sub_46E350()  // 调 HTTP 频道列表线程空闲判定
{
  return byte_98BB64 == 0;  // byte_98BB64＝线程在跑
}



// ------------------------------------------------------------
// 0x46E360 sub_46E360
// ------------------------------------------------------------
// CNEntranceChannel::startTimerForReservedConnectChannel（日志串自证）——
// 阶段④：+332 使能 → sub_698F90(+320, 500ms, 0) 定时；vmt4 到点调
// processReservedConnection(0x470A80)
int /*thiscall*/ sub_46E360(int this)  // 实现：阶段④：+332 使能 → sub_698F90(+320, 500ms, 0) 定时；vmt4 到点调
{
  int pThis_140; // ecx

  if ( *(uint32_t *)(this + 316) == -1 )
    return off_77F3FC("CNEntranceChannel::startTimerForReservedConnectChannel - invalid reservation.");  // 调 off_77F3FC（引擎日志输出函数）
  *(uint8_t *)(this + 332) = 1;  // this+1328 = 动画宿主对象
  pThis_140 = this + 320;
  *(uint8_t *)(pThis_140 + 13) = 0;
  *(uint8_t *)(pThis_140 + 14) = 0;
  sub_698F90(pThis_140, 500, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
  return off_77F3FC("CNEntranceChannel::startTimerForReservedConnectChannel - reserved connection timer started.");  // 调 off_77F3FC（引擎日志输出函数）
}



// ------------------------------------------------------------
// 0x46E3B0 sub_46E3B0 —— 退出模块 5 清场（频道状态清零）
// 退出模块 5（承载 CNEntranceChannel 的频道模块）清场：this+1456 选区频道状态槽与全局
// 镜像 dword_8F8528+621 双双清零；与进入侧 0x46EF40 成对（onChangeModule from==5 分支调）。
// ------------------------------------------------------------
int /*thiscall*/ sub_46E3B0(uint32_t *this)  // 函数: 退出模块 5 清场（频道状态清零）
{
  *(this + 364) = 0;  // this+1456〔nUdpReportField〕
  *((uint32_t *)dword_8F8528 + 621) = 0;  // dword_8F8528 = 主管理器
  return 0;
}



// ------------------------------------------------------------
// 0x46E3D0 sub_46E3D0 —— 频道条目 vector 计数
// 频道条目 vector 元素数：(end - begin)/104（条目 104 字节）；begin 为空返 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_46E3D0(int *this)  // 函数: 频道条目 vector 计数
{
  int result; // eax

  result = *(this + 1);  // this+4 = pHostObj
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(this + 2) - result) / 104;  // this+8 = 技能槽记录首字
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x46E3F0 sub_46E3F0 —— RB 树左旋（+85 nil 旗标族）
// RB 树左旋（+84 双色/+85 nil 旗标族）：y = x->right → x->right = y->left → y 顶替 x 挂回
// 父/根槽；login_channel 0x470BB0 擦除修复循环 case1/2c 以「左旋」调用。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_46E3F0(uint32_t *this, int pArg2)  // 函数: RB 树左旋（+85 nil 旗标族）
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
  *(uint32_t *)(pArg2 + 8) = *result;  // pArg2+8〔nSkillRec8(推断)〕
  if ( *(uint8_t *)(*result + 85) == 0 )
    *(uint32_t *)(*result + 4) = pArg2;
  result[1] = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  fld_e1 = *(this + 1);  // this+4 = pHostObj
  if ( pArg2 == *(uint32_t *)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // fld_e1=this+4 宿主对象
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;  // pArg2+4〔宿主对象〕
  }
  else
  {
    v4 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( pArg2 == *v4 )
      *v4 = result;
    else
      v4[2] = result;
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;  // pArg2+4〔宿主对象〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x46E450 sub_46E450 —— 子树最大（rightmost）
// 子树最大（rightmost）：沿 +8 右孩游标一路下行；erase 用它修正 header.right。
// ------------------------------------------------------------
int /*cdecl*/ sub_46E450(int pArg1)  // 函数: 子树最大（rightmost）
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 85) == 0; i = *(uint32_t *)(i + 8) )  // pArg1+8〔nSkillRec8(推断)〕
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x46E470 sub_46E470 —— 子树最小（leftmost）
// 子树最小（leftmost）：沿 +0 左孩游标一路下行；erase 用它修正 header.left。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_46E470(uint32_t *pArg1)  // 函数: 子树最小（leftmost）
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 85) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 85) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x46E490 sub_46E490 —— RB 树右旋（+85 nil 旗标族）
// RB 树右旋（+85 nil 旗标族）：y = x->left → x->left = y->right → y 顶替 x 挂回父/根槽；
// login_channel 0x470BB0 修复循环 case2b/镜像 case1 以「右旋」调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_46E490(uint32_t *this, uint32_t *pArg2)  // 函数: RB 树右旋（+85 nil 旗标族）
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 85) == 0 )
    *(uint32_t *)(v3 + 4) = pArg2;
  *(uint32_t *)(result + 4) = pArg2[1];
  fld_e1 = *(this + 1);  // this+4 = pHostObj
  if ( pArg2 == *(uint32_t **)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // fld_e1=this+4 宿主对象
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
// 0x46E4F0 sub_46E4F0 —— RB 树左旋（+29 nil 旗标族）
// RB 树左旋（+28 双色/+29 nil 旗标族）：y = x->right → x->right = y->left → y 挂回父/根槽；
// login_channel 0x4725E0（同族擦除）修复循环 case1/2c 调用。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_46E4F0(uint32_t *this, int pArg2)  // 函数: RB 树左旋（+29 nil 旗标族）
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
  *(uint32_t *)(pArg2 + 8) = *result;  // pArg2+8〔nSkillRec8(推断)〕
  if ( *(uint8_t *)(*result + 29) == 0 )
    *(uint32_t *)(*result + 4) = pArg2;
  result[1] = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  fld_e1 = *(this + 1);  // this+4 = pHostObj
  if ( pArg2 == *(uint32_t *)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // fld_e1=this+4 宿主对象
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;  // pArg2+4〔宿主对象〕
  }
  else
  {
    v4 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( pArg2 == *v4 )
      *v4 = result;
    else
      v4[2] = result;
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;  // pArg2+4〔宿主对象〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x46E550 sub_46E550 —— 子树最大（rightmost，+29 族）
// 子树最大（rightmost，+29 nil 旗标族）：沿 +8 右孩下行；0x4725E0 修正 header.right。
// ------------------------------------------------------------
int /*cdecl*/ sub_46E550(int pArg1)  // 函数: 子树最大（rightmost，+29 族）
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 29) == 0; i = *(uint32_t *)(i + 8) )  // pArg1+8〔nSkillRec8(推断)〕
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x46E570 sub_46E570 —— 子树最小（leftmost，+29 族）
// 子树最小（leftmost，+29 nil 旗标族）：沿 +0 左孩下行；0x4725E0 修正 header.left。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_46E570(uint32_t *pArg1)  // 函数: 子树最小（leftmost，+29 族）
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 29) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 29) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x46E590 sub_46E590 —— RB 树右旋（+29 nil 旗标族）
// RB 树右旋（+29 nil 旗标族）：y = x->left → x->left = y->right → y 挂回父/根槽；
// ·0x4725E0 修复循环 case2b/镜像 case1 调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_46E590(uint32_t *this, uint32_t *pArg2)  // 函数: RB 树右旋（+29 nil 旗标族）
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 29) == 0 )
    *(uint32_t *)(v3 + 4) = pArg2;
  *(uint32_t *)(result + 4) = pArg2[1];
  fld_e1 = *(this + 1);  // this+4 = pHostObj
  if ( pArg2 == *(uint32_t **)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // fld_e1=this+4 宿主对象
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
// 0x46E5F0 sub_46E5F0 —— 迭代器后继（+85 族）
// 迭代器后继（+85 nil 旗标族，std::map 克隆的递增）：有右孩走右子树最左，否则向上爬到
// 首个左向祖先，原地推进 *this；0x470BB0 擦除两孩路径前先取后继 y。
// ------------------------------------------------------------
int */*thiscall*/ sub_46E5F0(int *this)  // 函数: 迭代器后继（+85 族）
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 85) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 85) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 85) == 0; result = (int *)result[1] )
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
      if ( *(uint8_t *)(*v2 + 85) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 85) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x46E650 sub_46E650 —— 迭代器后继（+29 族）
// 迭代器后继（+29 nil 旗标族，逻辑同 0x46E5F0）：原地推进 *this 到中序后继；
// login_channel 0x4725E0 擦除两孩路径前先取后继 y。
// ------------------------------------------------------------
int */*thiscall*/ sub_46E650(int *this)  // 函数: 迭代器后继（+29 族）
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 29) == 0 )  // this+29 pSessionCtx
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 29) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 29) == 0; result = (int *)result[1] )
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
      if ( *(uint8_t *)(*v2 + 29) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 29) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x46E6B0 sub_46E6B0 —— 条目区间填充（步长 104B）
// 频道条目区间填充：pszArg1 到 pszArg2（不含）按步长 104 逐条拷模板 pArg3（0x68 字节）。
// login_channel 0x470330 插入时用它把腾出的空洞写成新条目。
// ------------------------------------------------------------
char */*cdecl*/ sub_46E6B0(char *pszArg1, char *pszArg2, const void *pArg3)  // 函数: 条目区间填充（步长 104B）
{
  char *result; // eax
  void *v4; // edi

  for ( result = pszArg1; result != pszArg2; result += 104 )
  {
    v4 = result;
    qmemcpy(v4, pArg3, 0x68u);  // 调 内存块拷贝(内联展开)
  }
  return result;
}



// ------------------------------------------------------------
// 0x46E6E0 sub_46E6E0 —— 子树最大（rightmost，+153 族）
// 子树最大（rightmost，+153 nil 旗标族）：沿 +8 右孩下行；0x470ED0 修正 header.right。
// ------------------------------------------------------------
int /*cdecl*/ sub_46E6E0(int pArg1)  // 函数: 子树最大（rightmost，+153 族）
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 153) == 0; i = *(uint32_t *)(i + 8) )  // pArg1+8〔nSkillRec8(推断)〕
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x46E710 sub_46E710 —— 子树最小（leftmost，+153 族）
// 子树最小（leftmost，+153 nil 旗标族）：沿 +0 左孩下行；0x470ED0 修正 header.left。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_46E710(uint32_t *pArg1)  // 函数: 子树最小（leftmost，+153 族）
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 153) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 153) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x46E740 sub_46E740 —— RB 树右旋（+153 族）
// RB 树右旋（+152 双色/+153 nil 旗标族）：y = x->left → x->left = y->right → y 挂回父/根槽；
// ·0x470ED0（同族擦除）修复循环 case2b/镜像 case1 调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_46E740(uint32_t *this, uint32_t *pArg2)  // 函数: RB 树右旋（+153 族）
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 153) == 0 )
    *(uint32_t *)(v3 + 4) = pArg2;
  *(uint32_t *)(result + 4) = pArg2[1];
  fld_e1 = *(this + 1);  // this+4 = pHostObj
  if ( pArg2 == *(uint32_t **)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // fld_e1=this+4 宿主对象
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
// 0x46E7B0 sub_46E7B0 —— 迭代器后继（+153 族）
// 迭代器后继（+153 nil 旗标族）：原地推进 *this 到中序后继；0x470ED0 擦除两孩路径前取 y。
// ------------------------------------------------------------
int */*thiscall*/ sub_46E7B0(int *this)  // 函数: 迭代器后继（+153 族）
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 153) == 0 )  // this+153〔bCastFlagA〕
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 153) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 153) == 0; result = (int *)result[1] )
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
      if ( *(uint8_t *)(*v2 + 153) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 153) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x46E810 sub_46E810 —— 选区界面频道列表刷新
// 选区界面频道列表刷新（0x471CC0 拉取成功后与页签点击时调）：服务器型无频道则回哨兵 6（整组
// 隐藏）→ 6 服务器页签（+64 起）与 5 频道型页签（+92 起，类型 1 需 user_age>18，越界或
// age<=18 归 0 型）逐个启用/选中高亮 → 页数 = ceil(本型条目数/10)（>=1），>1 时显示翻页箭头。
// ------------------------------------------------------------
int /*thiscall*/ sub_46E810(uint32_t *this)  // 函数: 选区界面频道列表刷新
{
  int fld_e3; // eax
  int fld_e16; // eax
  int fld_e17; // eax
  int fld_e18; // eax
  int fld_e19; // eax
  int fld_e20; // eax
  int fld_e21; // eax
  int fld_e23; // eax
  int fld_e24; // eax
  int fld_e25; // eax
  int fld_e26; // eax
  uint64_t v13; // rax
  int fld_e42; // ecx
  int fld_e232; // eax
  int fld_e242; // eax
  int fld_e252; // eax
  int fld_e262; // eax
  int fld_e27; // eax
  int fld_e32; // eax
  int v21; // edx
  int v22; // eax

  sub_69CEB0(*(this + 28));  // this+112 = pHostComp
  fld_e3 = *(this + 3);  // this+12 = 技能槽记录次字
  if ( fld_e3 != 6 && *(this + 35 * fld_e3 + 167) == 0 )  // fld_e3=this+12 物品类型号
    *(this + 3) = 6;  // this+12 = 技能槽记录次字
  fld_e16 = *(this + 16);  // this+64〔apServerTabBtn(推断)〕
  if ( fld_e16 != 0 )  // fld_e16=this+64 apServerTabBtn
  {
    *(uint8_t *)(fld_e16 + 16) = 1;  // fld_e16=this+64 apServerTabBtn
    if ( *(this + 167) != 0 )  // this+668 = 拾取/交互目标坐标缓存
    {
      if ( *(this + 3) == 0 )  // this+12 = 技能槽记录次字
        *(uint8_t *)(*(this + 16) + 132) = 1;  // this+64〔apServerTabBtn(推断)〕
    }
    else
    {
      *(uint8_t *)(*(this + 16) + 17) = 0;  // this+64〔apServerTabBtn(推断)〕
    }
  }
  fld_e17 = *(this + 17);  // this+68〔nCharCount(推断)〕
  if ( fld_e17 != 0 )  // fld_e17=this+68 nCharCount
  {
    *(uint8_t *)(fld_e17 + 16) = 1;  // fld_e17=this+68 nCharCount
    if ( *(this + 202) != 0 )
    {
      if ( *(this + 3) == 1 )  // this+12 = 技能槽记录次字
        *(uint8_t *)(*(this + 17) + 132) = 1;  // this+68〔nCharCount(推断)〕
    }
    else
    {
      *(uint8_t *)(*(this + 17) + 17) = 0;  // this+68〔nCharCount(推断)〕
    }
  }
  fld_e18 = *(this + 18);  // this+72〔nSnapshot72(推断)〕
  if ( fld_e18 != 0 )  // fld_e18=this+72 nSnapshot72
  {
    *(uint8_t *)(fld_e18 + 16) = 1;  // fld_e18=this+72 nSnapshot72
    if ( *(this + 237) != 0 )
    {
      if ( *(this + 3) == 2 )  // this+12 = 技能槽记录次字
        *(uint8_t *)(*(this + 18) + 132) = 1;  // this+72〔nSnapshot72(推断)〕
    }
    else
    {
      *(uint8_t *)(*(this + 18) + 17) = 0;  // this+72〔nSnapshot72(推断)〕
    }
  }
  fld_e19 = *(this + 19);  // this+76〔pBtnActionE〕
  if ( fld_e19 != 0 )  // fld_e19=this+76 pBtnActionE
  {
    *(uint8_t *)(fld_e19 + 16) = 1;  // fld_e19=this+76 pBtnActionE
    if ( *(this + 272) != 0 )
    {
      if ( *(this + 3) == 3 )  // this+12 = 技能槽记录次字
        *(uint8_t *)(*(this + 19) + 132) = 1;  // this+76〔pBtnActionE〕
    }
    else
    {
      *(uint8_t *)(*(this + 19) + 17) = 0;  // this+76〔pBtnActionE〕
    }
  }
  fld_e20 = *(this + 20);  // this+80 = nAuraStage
  if ( fld_e20 != 0 )  // fld_e20=this+80 关联角色对象
  {
    *(uint8_t *)(fld_e20 + 16) = 1;  // fld_e20=this+80 关联角色对象
    if ( *(this + 307) != 0 )  // this+1228〔bLvTagInited〕
    {
      if ( *(this + 3) == 4 )  // this+12 = 技能槽记录次字
        *(uint8_t *)(*(this + 20) + 132) = 1;  // this+80 = nAuraStage
    }
    else
    {
      *(uint8_t *)(*(this + 20) + 17) = 0;  // this+80 = nAuraStage
    }
  }
  fld_e21 = *(this + 21);  // this+84 = pFxObjA
  if ( fld_e21 != 0 )  // fld_e21=this+84 插值起点 X
  {
    *(uint8_t *)(fld_e21 + 16) = 1;  // fld_e21=this+84 插值起点 X
    if ( *(this + 342) != 0 )
    {
      if ( *(this + 3) == 5 )  // this+12 = 技能槽记录次字
        *(uint8_t *)(*(this + 21) + 132) = 1;  // this+84 = pFxObjA
    }
    else
    {
      *(uint8_t *)(*(this + 21) + 17) = 0;  // this+84 = pFxObjA
    }
  }
  if ( *(this + 3) == 6 )  // this+12 = 技能槽记录次字
  {
    *(this + 4) = 5;  // this+16〔nChannelTypeSel(推断)〕
    fld_e23 = *(this + 23);  // this+92 = pFxObjC
    if ( fld_e23 != 0 )  // fld_e23=this+92 插值起点 Z
      *(uint8_t *)(fld_e23 + 17) = 0;  // fld_e23=this+92 插值起点 Z
    fld_e24 = *(this + 24);  // this+96〔nStatusMode(推断)〕
    if ( fld_e24 != 0 )  // fld_e24=this+96 nStatusMode
      *(uint8_t *)(fld_e24 + 17) = 0;  // fld_e24=this+96 nStatusMode
    fld_e25 = *(this + 25);  // this+100〔bEnchantDone(推断)〕
    if ( fld_e25 != 0 )  // fld_e25=this+100 bEnchantDone
      *(uint8_t *)(fld_e25 + 17) = 0;  // fld_e25=this+100 bEnchantDone
    fld_e26 = *(this + 26);  // this+104〔nTimerEnd(推断)〕
    if ( fld_e26 != 0 )  // fld_e26=this+104 nTimerEnd
      *(uint8_t *)(fld_e26 + 17) = 0;  // fld_e26=this+104 nTimerEnd
    LODWORD(v13) = *(this + 27);  // 调 取 64 位值低 32 位
    if ( (uint32_t)v13 != 0 )
      *(uint8_t *)(v13 + 17) = 0;
    fld_e42 = *(this + 42);  // this+168〔pAppendVec(推断)〕
    *(this + 5) = 0;  // this+20〔nPage(推断)〕
    *(this + 6) = 1;  // this+24〔nPageMax(推断)〕
    *(uint8_t *)(fld_e42 + 17) = 0;  // fld_e42=this+168 pAppendVec
  }
  else
  {
    if ( (int)*(this + 4) >= 5 || (int)*(this + 72) <= 18 )  // this+16〔nChannelTypeSel(推断)〕等 2 字段
      *(this + 4) = 0;  // this+16〔nChannelTypeSel(推断)〕
    fld_e232 = *(this + 23);  // this+92 = pFxObjC
    if ( fld_e232 != 0 )  // fld_e232=this+92 插值起点 Z
      *(uint8_t *)(fld_e232 + 17) = 1;  // fld_e232=this+92 插值起点 Z
    fld_e242 = *(this + 24);  // this+96〔nStatusMode(推断)〕
    if ( fld_e242 != 0 )  // fld_e242=this+96 nStatusMode
      *(uint8_t *)(fld_e242 + 17) = *(this + 72) > 18;  // this+288〔pMaster288(推断)〕
    fld_e252 = *(this + 25);  // this+100〔bEnchantDone(推断)〕
    if ( fld_e252 != 0 )  // fld_e252=this+100 bEnchantDone
      *(uint8_t *)(fld_e252 + 17) = 1;  // fld_e252=this+100 bEnchantDone
    fld_e262 = *(this + 26);  // this+104〔nTimerEnd(推断)〕
    if ( fld_e262 != 0 )  // fld_e262=this+104 nTimerEnd
      *(uint8_t *)(fld_e262 + 17) = 1;  // fld_e262=this+104 nTimerEnd
    fld_e27 = *(this + 27);  // this+108〔nAdd108(推断)〕
    if ( fld_e27 != 0 )  // fld_e27=this+108 nAdd108
      *(uint8_t *)(fld_e27 + 17) = 1;  // fld_e27=this+108 nAdd108
    *(uint8_t *)(*(this + *(this + 4) + 23) + 132) = 1;  // this+16〔nChannelTypeSel(推断)〕
    fld_e32 = (int)(this + 35 * *(this + 3) + 4 * *(this + 4) + 169);  // this+12 = 技能槽记录次字
    *(this + 5) = 0;  // this+20〔nPage(推断)〕
    v21 = *(uint32_t *)(fld_e32 + 4);  // fld_e32=this+12 物品类型号
    if ( v21 != 0 )
      v22 = (*(uint32_t *)(fld_e32 + 8) - v21) / 104;  // fld_e32=this+12 物品类型号
    else
      v22 = 0;
    v13 = (uint64_t)ceil((double)(unsigned int)v22 * 0.1);  // 调 向上取整
    *(this + 6) = v13;  // this+24〔nPageMax(推断)〕
    if ( (uint32_t)v13 == 0 )
      *(this + 6) = 1;  // this+24〔nPageMax(推断)〕
    *(uint8_t *)(*(this + 42) + 17) = 1;  // this+168〔pAppendVec(推断)〕
  }
  if ( (int)*(this + 6) > 1 )  // this+24〔nPageMax(推断)〕
  {
    *(uint8_t *)(*(this + 43) + 16) = 1;  // this+172〔pAppendVecEnd(推断)〕
    LODWORD(v13) = *(this + 44);  // 调 取 64 位值低 32 位
    *(uint8_t *)(v13 + 16) = 1;
  }
  return v13;
}


// ------------------------------------------------------------
// 0x46EAA0 sub_46EAA0
// ------------------------------------------------------------
// CNEntranceChannel::reserveConnection（日志串自证）—— 阶段④ 预约：
// 校验同 connectServer（server<6/channel<5/index 表内）→ 预约三元组 +75/+77/+79
int /*thiscall*/ sub_46EAA0(uint32_t *this, int ArgList, int nArg3, int nArg4)  // 实现：校验同 connectServer（server<6/channel<5/index 表内）→ 预约三元组 +75/+77/+79
{
  int fld_e3; // esi  | +0x000C → ★ 服务器页签选中索引（vmt4 0..5 循环比较命中后写 +12=v5；==6 时跳过频道型段）（CNEntranceChannel；va=00471280）

  if ( ArgList >= 6 )
    return off_77F3FC("CNEntranceChannel::reserveConnection - invalied server type.");  // 调 off_77F3FC（引擎日志输出函数）
  if ( nArg3 >= 5 )
    return off_77F3FC("CNEntranceChannel::reserveConnection - invalied channel type.");  // 调 off_77F3FC（引擎日志输出函数）
  if ( nArg4 < 0 )
    return off_77F3FC("CNEntranceChannel::reserveConnection - invalied channel index.");  // 调 off_77F3FC（引擎日志输出函数）
  fld_e3 = *(this + 35 * *(this + 3) + 4 * nArg3 + 170);  // this+12 = 技能槽记录次字
  if ( fld_e3 == 0 || (*(this + 35 * *(this + 3) + 4 * nArg3 + 171) - fld_e3) / 104 <= (unsigned int)nArg4 )  // this+12 = 技能槽记录次字
    return off_77F3FC("CNEntranceChannel::reserveConnection - unknown channel index.");  // 调 off_77F3FC（引擎日志输出函数）
  *(this + 75) = ArgList;  // this+300〔pAnim300〕
  *(this + 77) = nArg3;  // this+77 【推断】公会标志字节 B
  *(this + 79) = nArg4;
  return off_77F3FC(  // 调 off_77F3FC（引擎日志输出函数）
           "CNEntranceChannel::reserveConnection - connection reserved. server_type = %d, channel_type = %d, channel_index = %d",
           ArgList,
           nArg3,
           nArg4);
}



// ============================================================
// 【分区 12】HTTP 频道列表线程与频道表 vector（0x46EB70-0x46F800）
// StartAddress（"MERONG(0.9/;p)" 校验）→ 0x46EE10 线程启动包装 →
// 104 字节/条目的搬运族（0x46ECC0/0x46EF10/0x46E6B0/0x46ED50/0x46F6B0，
// 被 login_channel.cpp 0x470330 调用）。
// ============================================================
// ------------------------------------------------------------
// 0x46EB70 StartAddress
// ------------------------------------------------------------
// HTTP 频道列表下载线程入口（IDA 名 StartAddress）—— 阶段① 数据源：
// 临界区 stru_98BA28 → sub_5770B0 缓冲 → "MERONG(0.9/;p)" 口令校验
// （sub_576F10）→ 解密结果指针存 dword_98BA5C（retrieveServerInfo 的输入）；
// 退出码 1=成功 / -2=失败（checkHTTPChannelDataWork 0x471CC0 轮询）
int /*stdcall*/ StartAddress(LPVOID lpThreadParameter)  // 实现：退出码 1=成功 / -2=失败（checkHTTPChannelDataWork 0x471CC0 轮询）
{
  int v1; // edi
  int v2; // eax
  const char *psz; // eax
  signed int nLen; // ecx
  signed int i; // esi
  uint8_t v7[200044]; // [esp+4h] [ebp-30D7Ch] BYREF
  int dword_796E502; // [esp+30D70h] [ebp-10h]
  int v9; // [esp+30D7Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  EnterCriticalSection(&stru_98BA28);  // 调 进入临界区(加锁)
  v1 = -2;
  if ( (dword_99FB6C & 1) == 0 )  // 若 dword_99FB6C 位 1 清零
  {
    dword_99FB6C |= 1u;
    sub_577220(&unk_98BB68);  // 调 应答缓冲复位：+20480 XOR 密钥清零 + 两块 0xA000(40KB) 应答区清零（全局单例 unk_98BB68…
    atexit(sub_6BF740);  // 调 登记退出回调（表满返回非 0）
    v9 = -1;
  }
  sub_5770B0(v7);  // 调 GenericHTTPClient 平凡构造：清字段表指针与 50005/50006/50007 句柄（不装配 vftbl）
  v9 = 1;
  dword_99FB68 = 2857617;  // HTTP XOR 密钥
  if ( sub_576F10(v7, &unk_98BA60, 1, "MERONG(0.9/;p)") != 0 )  // 调 Request() 总入口：5763D0 解析 URL→575FF0 Connect→576E90 按模式发送→576180…
  {
    v2 = sub_576640(v7);
    psz = (const char *)sub_577250(v2);  // 调 应答解码：Base64 解码入 this（容量上限 40960）后按 dword 与密钥 this+20480 逐 4 字节…
    dword_98BA5C = (int)psz;
    if ( psz != nullptr )  // 若 psz 有效（非空）
    {
      nLen = strlen(psz);  // 调 返回字符串长度（逐字节扫描）
      for ( i = 0; i < nLen; ++i )
        ;
      v1 = 1;
    }
  }
  byte_98BB65 = 0;
  LeaveCriticalSection(&stru_98BA28);  // 调 离开临界区(解锁)
  v9 = -1;
  sub_576ED0(v7);  // 调 GenericHTTPClient 构造/复位：vftbl 装配、清句柄 50005/50006/50007（+200020…
  return v1;
}



// ------------------------------------------------------------
// 0x46ECC0 sub_46ECC0
// ------------------------------------------------------------
// 频道表 104 字节/条目逆向搬运（login_channel 0x470330 中插腾挪用）
char */*cdecl*/ sub_46ECC0(char *pszArg1, char *pszArg2, char *pszArg3)  // 实现：频道表 104 字节/条目逆向搬运（login_channel 0x470330 中插腾挪用）
{
  char *pszArg22; // edx
  char *result; // eax

  pszArg22 = pszArg2;
  result = pszArg3;
  while ( pszArg22 != pszArg1 )  // 当 pszArg22 != pszArg1 循环
  {
    pszArg22 -= 104;
    result -= 104;
    qmemcpy(result, pszArg22, 0x68u);  // 调 内存块拷贝(内联展开)
  }
  return result;
}



// ------------------------------------------------------------
// 0x46ECF0 sub_46ECF0 —— RB 树左旋（+153 nil 旗标族）
// RB 树左旋（+152 双色/+153 nil 旗标族）：y = x->right → x->right = y->left → y 挂回父/根槽；
// ·0x470ED0（同族擦除）修复循环 case1/2c 调用。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_46ECF0(uint32_t *this, int pArg2)  // 函数: RB 树左旋（+153 nil 旗标族）
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
  *(uint32_t *)(pArg2 + 8) = *result;  // pArg2+8〔nSkillRec8(推断)〕
  if ( *(uint8_t *)(*result + 153) == 0 )
    *(uint32_t *)(*result + 4) = pArg2;
  result[1] = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  fld_e1 = *(this + 1);  // this+4 = pHostObj
  if ( pArg2 == *(uint32_t *)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // fld_e1=this+4 宿主对象
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;  // pArg2+4〔宿主对象〕
  }
  else
  {
    v4 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( pArg2 == *v4 )
      *v4 = result;
    else
      v4[2] = result;
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;  // pArg2+4〔宿主对象〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x46ED50 sub_46ED50 —— 条目区间正向拷贝（步长 104B）
// 频道条目区间正向拷贝：pszArg1 到 pszArg2（不含）步长 104 搬到 pszArg3 起（空目标跳过）。
// login_channel 0x470330 扩容/腾挪时搬旧条目；0x46ECC0 是同族的尾部倒搬版本。
// ------------------------------------------------------------
char */*cdecl*/ sub_46ED50(char *pszArg1, char *pszArg2, char *pszArg3)  // 函数: 条目区间正向拷贝（步长 104B）
{
  char *pszArg12; // edx
  char *result; // eax

  pszArg12 = pszArg1;
  for ( result = pszArg3; pszArg12 != pszArg2; result += 104 )
  {
    if ( result != nullptr )  // 若 result 有效（非空）
      qmemcpy(result, pszArg12, 0x68u);  // 调 内存块拷贝(内联展开)
    pszArg12 += 104;
  }
  return result;
}



// ------------------------------------------------------------
// 0x46ED90 sub_46ED90 —— reserveConnectionToConnectionHistory（按连接历史预约）
// CNEntranceChannel::reserveConnectionToConnectionHistory（日志串自证）——用连接历史
// （+296/+304/+312 = server/type/index）调 reserveConnection 0x46EAA0 发起预约，随即把历史
// 置哨兵（6/5/-1）；历史越界仅打 invalid history 日志。PVP 房间列表等入口调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_46ED90(int *this)  // 函数: reserveConnectionToConnectionHistory（按连接历史预约）
{
  int fld_e74; // edx
  int fld_e76; // eax
  int result; // eax

  fld_e74 = *(this + 74);  // this+296〔bInitFlag296(推断)〕
  if ( fld_e74 >= 6 )  // fld_e74=this+296 bInitFlag296
    return off_77F3FC("CNEntranceChannel::reserveConnectionToConnectionHistory - invalid history.");  // 调 off_77F3FC（引擎日志输出函数）
  fld_e76 = *(this + 76);  // this+304〔pLayer304(推断)〕
  if ( fld_e76 >= 5 || *(this + 78) < 0 )  // this+78 【推断】公会标志字节 C
    return off_77F3FC("CNEntranceChannel::reserveConnectionToConnectionHistory - invalid history.");  // 调 off_77F3FC（引擎日志输出函数）
  sub_46EAA0(this, fld_e74, fld_e76, *(this + 78));  // this+78 【推断】公会标志字节 C
  result = off_77F3FC(  // 调 off_77F3FC（引擎日志输出函数）
             "CNEntranceChannel::reserveConnectionToConnectionHistory - connection history used. channel_type = %d, channel_index = %d",
             *(this + 76),  // this+76 纹章路径串
             *(this + 78));  // this+78 【推断】公会标志字节 C
  *(this + 74) = 6;  // this+296〔bInitFlag296(推断)〕
  *(this + 76) = 5;  // this+304〔pLayer304(推断)〕
  *(this + 78) = -1;  // this+78 【推断】公会标志字节 C
  return result;
}



// ------------------------------------------------------------
// 0x46EE10 sub_46EE10
// ------------------------------------------------------------
// HTTP 线程启动包装（CreateThread → StartAddress；句柄存 hObject）
HANDLE /*thiscall*/ sub_46EE10(int this, const char *pArg2)  // 调 启动时置 1、
{
  HANDLE result; // eax
  DWORD ThreadId; // [esp+4h] [ebp-8h] BYREF
  int Parameter; // [esp+8h] [ebp-4h] BYREF

  if ( *(uint32_t *)this != 0 )
    TerminateThread(*(HANDLE *)this, 0);  // 强制终止线程
  *(uint32_t *)this = 0;  // *this = 0
  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  memset((void *)(this + 8), 0, 0x104u);  // 调 内存按字节填充
  *(uint8_t *)(this + 269) = 0;
  *(uint8_t *)(this + 268) = 1;  // this+268〔field_10C〕
  strcpy((char *)(this + 8), pArg2);  // 调 字符串拷贝入口（跳到拷贝内核）
  Parameter = 0;
  result = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)StartAddress, &Parameter, 0, &ThreadId);  // 调 创建线程
  *(uint32_t *)this = result;  // *this = result
  return result;
}



// ------------------------------------------------------------
// 0x46EE90 sub_46EE90 —— RB 头/哨兵节点分配（+85 族，0x58 字节）
// RB 树头/哨兵节点分配（+85 nil 旗标族，0x58 字节）：三指针清零，+84=1（红）、+85=0；
// 调用方 login_channel 0x4729D0 再把 +85 置 1 并自环成 map 头节点。
// ------------------------------------------------------------
uint32_t *sub_46EE90()  // 调 RB 头/哨兵节点分配（+85 族，0x58 字节）
{
  uint32_t *result; // eax

  result = operator new(0x58u);  // operator new 分配 88 字节
  if ( result != nullptr )  // 若 result 有效（非空）
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;  // 对象头 [+4] 清零
  if ( result != (uint32_t *)-8 )
    result[2] = 0;  // 对象头 [+8] 清零
  *((uint8_t *)result + 84) = 1;
  *((uint8_t *)result + 85) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x46EED0 sub_46EED0 —— RB 头/哨兵节点分配（+29 族，0x20 字节）
// RB 树头/哨兵节点分配（+29 nil 旗标族，0x20 字节）：三指针清零，+28=1（红）、+29=0；
// 调用方 login_channel 0x4729D0 再把 +29 置 1 并自环成 map 头节点。
// ------------------------------------------------------------
uint32_t *sub_46EED0()  // 调 RB 头/哨兵节点分配（+29 族，0x20 字节）
{
  uint32_t *result; // eax

  result = operator new(0x20u);  // operator new 分配 32 字节
  if ( result != nullptr )  // 若 result 有效（非空）
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;  // 对象头 [+4] 清零
  if ( result != (uint32_t *)-8 )
    result[2] = 0;  // 对象头 [+8] 清零
  *((uint8_t *)result + 28) = 1;
  *((uint8_t *)result + 29) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x46EF10 sub_46EF10 —— 条目填充 N 条（步长 104B）
// 频道条目填充：pszArg1 起按步长 104 连续拷 0x68 字节模板，共 pszArg2 条（空目标跳过）。
// login_channel 0x470330 扩容路径在空洞处补新条目；0x46F6B0 为其返尾指针变体。
// ------------------------------------------------------------
char */*cdecl*/ sub_46EF10(char *pszArg1, char *pszArg2, const void *pArg3)  // 函数: 条目填充 N 条（步长 104B）
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
        qmemcpy(result, pArg3, 0x68u);  // 调 内存块拷贝(内联展开)
      result += 104;
      --pszArg22;
    }
    while ( pszArg22 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x46EF40 sub_46EF40 —— CNEntranceChannel 数据/HTTP 线程初始化（进模块 5）
// CNEntranceChannel 频道数据/HTTP 线程初始化（日志串自证 reset；进模块 5 调）：读配置 13/14
// 复位服务器型/频道型，清 6 组槽位与 +348/+376/+404 计时器并隐藏控件；无预约则拼
// game_pass.php 请求串启动 HTTP 频道列表线程，有预约则置 255 状态返回 -1（退出侧 0x46E3B0）。
// ------------------------------------------------------------
uint8_t /*thiscall*/ sub_46EF40(int this)  // 函数: CNEntranceChannel 数据/HTTP 线程初始化（进模块 5）
{
  uint8_t result; // al
  int v3; // eax
  unsigned int v4; // eax
  int v5; // eax
  uint8_t *pThis_1C6; // ecx

  result = *(uint8_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v3 = sub_48B740(13);  // 调 调试配置项读取并夹取上下限
    *(uint32_t *)(this + 12) = v3;  // this+12〔nSkillRec12(推断)〕等 2 字段
    if ( v3 >= 6 )
      *(uint32_t *)(this + 12) = 5;  // this+12〔nSkillRec12(推断)〕等 2 字段
    v4 = sub_48B740(14);  // 调 调试配置项读取并夹取上下限
    *(uint32_t *)(this + 16) = v4;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
    if ( v4 >= 2 )
      *(uint32_t *)(this + 16) = 0;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
    *(uint32_t *)(this + 432) = 0;  // this+1728〔nDblClickSlotA(推断)〕
    *(uint16_t *)(this + 436) = 0;  // this+436〔nAtkTableVal(推断)〕等 2 字段
    *(uint32_t *)(this + 1464) = -1;  // this+1464〔nSelState〕
    *(uint8_t *)(this + 361) = 0;
    *(uint8_t *)(this + 362) = 0;
    sub_698F90(this + 348, 0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
    *(uint8_t *)(this + 417) = 0;
    *(uint8_t *)(this + 418) = 0;
    sub_698F90(this + 404, 0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
    *(uint8_t *)(this + 389) = 0;
    *(uint8_t *)(this + 390) = 0;
    sub_698F90(this + 376, 0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
    *(uint8_t *)(this + 1460) = 0;  // this+1460〔bCharSelSent〕
    v5 = 0;
    pThis_1C6 = (uint8_t *)(this + 454);
    do
    {
      *(pThis_1C6 - 1) = 0;
      *pThis_1C6 = 0;
      *(uint8_t *)(this + v5++ + 608) = 0;
      pThis_1C6 += 28;
    }
    while ( v5 < 6 );
    sub_46E100((uint32_t *)this);  // 调 界面控件批量隐藏
    byte_98BB64 = 0;  // byte_98BB64＝线程在跑
    CloseHandle(hObject);  // 调 关闭句柄
    hObject = nullptr;
    if ( *(uint32_t *)(this + 316) == -1 )
    {
      memset((void *)(this + 1468), 0, 0x104u);  // 调 内存按字节填充
      if ( *(uint32_t *)(this + 288) == -1 )  // this+288〔pMaster288(推断)〕
        sprintf(  // 调 格式化到缓冲
          (char *const)(this + 1468),
          "%s%s%s",  // 日志模板 %s%s%s
          "http://ch.arad.jp:10900/FRM/game/game_pass.php?id=",
          (const char *)(dword_8F7A24 + 113),  // dword_8F7A24 = 当前场景状态对象
          szPassword);
      else
        sprintf((char *const)(this + 1468), "%s%s", "http://ch.arad.jp:10900/FRM/game/game_pass.php?", szPassword);
      *(uint8_t *)(this + 389) = 0;
      *(uint8_t *)(this + 390) = 0;
      sub_698F90(this + 376, 0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
      return (uint8_t)sub_46EE10((int)&hObject, (const char *)(this + 1468));  // 调 启动时置 1、
    }
    else
    {
      off_77F3FC("CNEntranceChannel::reset - reserved connection founded.");  // 调 off_77F3FC（引擎日志输出函数）
      *(uint32_t *)(this + 1456) = 255;  // this+1456〔nUdpReportField〕
      *((uint32_t *)dword_8F8528 + 621) = 255;  // dword_8F8528 = 主管理器
      return -1;
    }
  }
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x46F0E0 sub_46F0E0 —— 单条频道条目绘制（背景帧 + 频道名 + 负载条）
// 单条频道条目绘制（pArg2=槽按钮、pArg3=条目、nArg4=该服最大负载）：按条目 +92 类型与阵营名
// [elven_guard]/[granfloris]/[sky_catle]/[behemoth]/[Alfhlyra] 选背景帧（8/10/0/2/4/6/85，
// 未选中或满员用 +1 号帧），画 ch%02d.名字 与负载条（+56 上限/+60 当前，分母 max(上限×0.7, nArg4)）。
// ------------------------------------------------------------
int /*thiscall*/ sub_46F0E0(void *this, int pArg2, int pArg3, int nArg4)  // 函数: 单条频道条目绘制（背景帧 + 频道名 + 负载条）
{
  int result; // eax
  int v5; // ebx
  int v6; // edi
  int pObj2; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int pObj; // eax
  int v13; // eax
  const char *v14; // eax
  double v15; // st7
  uint64_t v16; // rax
  int v17; // eax
  char Buffer[128]; // [esp+4h] [ebp-84h] BYREF
  int dword_796E502; // [esp+84h] [ebp-4h]
  float v21; // [esp+90h] [ebp+8h]

  dword_796E502 = dword_796E50;  // dword_796E50 = 栈检 cookie 值
  result = pArg2;
  if ( pArg2 != 0 && pArg3 != 0 )  // 若 pArg2 != 0 与/或 pArg3 != 0
  {
    v5 = *(uint32_t *)(pArg2 + 24);  // pArg2+24〔nPageMax(推断)〕
    v6 = *(uint32_t *)(pArg2 + 20);  // pArg2+20〔nPage(推断)〕
    if ( *(uint8_t *)(pArg3 + 88) != 0 )  // pArg3+88〔pFxObjB(推断)〕
    {
      sub_491530(5, 0);  // 调 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      pObj2 = sub_418DD0(56);  // 调 资源句柄 (101)
      if ( pObj2 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 调用虚函数（虚表槽 +128）
          pObj2,
          v6,
          v5,
          dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
          1065353216,  // 常量 1.0f
          1065353216,  // 常量 1.0f
          0,
          -1610612736,
          1333788672,
          1333788672);
      sub_491630(5);  // 调 渲染层状态还原（与 ·0x491530 配对）
    }
    v8 = *(uint32_t *)(pArg3 + 92);  // pArg3+92〔pFxObjC(推断)〕
    v9 = *(uint32_t *)(v8 + 28);
    if ( v9 == 2 )
    {
      v10 = 8;
    }
    else if ( v9 == 3 )
    {
      v10 = 10;
    }
    else if ( (uint8_t)sub_423300(v8 + 32, "[elven_guard]") != 0 )  // 调 串首比较判定（相等）
    {
      v10 = 8;
    }
    else if ( (uint8_t)sub_423300(*(uint32_t *)(pArg3 + 92) + 32, "[granfloris]") != 0 )  // 调 串首比较判定（相等）
    {
      v10 = 0;
    }
    else if ( (uint8_t)sub_423300(*(uint32_t *)(pArg3 + 92) + 32, "[sky_catle]") != 0 )  // 调 串首比较判定（相等）
    {
      v10 = 2;
    }
    else if ( (uint8_t)sub_423300(*(uint32_t *)(pArg3 + 92) + 32, "[behemoth]") != 0 )  // 调 串首比较判定（相等）
    {
      v10 = 4;
    }
    else
    {
      v10 = (uint8_t)sub_423300(*(uint32_t *)(pArg3 + 92) + 32, "[Alfhlyra]") != 0 ? 6 : 85;  // 调 串首比较判定（相等）
    }
    if ( *(uint8_t *)(pArg2 + 132) == 0 || *(uint8_t *)(pArg3 + 88) != 0 )  // pArg2+132〔nAgeTicks〕
    {
      pObj = sub_418DD0(v10 + 1);  // 调 资源句柄 (101)
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v6 + 3, v5 + 3, dword_79C0B0);  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
    }
    else
    {
      v11 = sub_418DD0(v10);  // 调 资源句柄 (101)
      sub_40FC80(v6 + 3, v5 + 3, v11);  // 调 贴图转发（目标对象虚发 +152(this, x, y)）
    }
    v13 = *(uint32_t *)(pArg3 + 92);  // pArg3+92〔pFxObjC(推断)〕
    if ( *(uint32_t *)(v13 + 24) < 0x10u )
      v14 = (const char *)(v13 + 4);
    else
      v14 = *(const char **)(v13 + 4);
    sprintf(Buffer, "ch%02d.%s", *(uint32_t *)pArg3, v14);  // 调 格式化到缓冲
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (int)this + 184);  // 调用虚函数（虚表槽 +72）【推断: ★★ 全体时钟换域广播】
    if ( *(uint8_t *)(pArg2 + 132) == 0 || *(uint8_t *)(pArg3 + 88) != 0 )  // pArg2+132〔nAgeTicks〕
      (*(void (/*cdecl*/ **)(int, int, int, int, const char *, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        v6 + 37,
        v5 + 14,
        -6502170,
        "%s",
        Buffer);
    else
      (*(void (/*cdecl*/ **)(int, int, int, int, const char *, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 调用虚函数（虚表槽 +80）
        dword_79C0B0,  // dword_79C0B0 = 文本/图像绘制对象
        v6 + 37,
        v5 + 14,
        -1,
        "%s",
        Buffer);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数（虚表槽 +76）【推断: this+116 存取】
    v15 = (double)*(int *)(pArg3 + 56) * 0.69999999;  // pArg3+56〔pCmdVecCap56(推断)〕
    v21 = (float)nArg4;
    if ( v15 <= v21 )
      v15 = v21;
    v16 = (uint64_t)((double)*(int *)(pArg3 + 60) * 100.0 / (double)(int)(uint64_t)v15);  // pArg3+60〔nFadeValue60(推断)〕
    if ( *(uint8_t *)(pArg3 + 88) == 1 )  // pArg3+88〔pFxObjB(推断)〕
    {
      v17 = 274;
    }
    else if ( (int)v16 >= 30 )
    {
      if ( (int)v16 >= 50 )
        v17 = ((int)v16 < 75) + 240;
      else
        v17 = 242;
    }
    else
    {
      v17 = 243;
    }
    result = sub_418DD0(v17);  // 调 资源句柄 (101)
    if ( result != 0 )  // 若结果非 0（成功）
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(  // 调用虚函数（虚表槽 +152）【推断: 取条件字节】
               result,
               v6 + 152,
               v5 + 10,
               dword_79C0B0);  // dword_79C0B0 = 文本/图像绘制对象
  }
  return result;
}


// ------------------------------------------------------------
// 0x46F3E0 sub_46F3E0 —— 频道列表手动刷新（5000ms 节流）
// 频道列表手动刷新（节流 5000ms）：+404 计时器 clock_now 满 5000 才动手——隐藏控件
// （0x46E100）、清 +389/+390 等待旗标并用 +1468 请求串重启 HTTP 线程；选区界面刷新按钮调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_46F3E0(int this)  // 函数: 频道列表手动刷新（5000ms 节流）
{
  int pThis_194; // edi
  int result; // eax

  pThis_194 = this + 404;
  result = sub_699000(this + 404);  // clock_now(clk)
  if ( result >= 5000 )
  {
    sub_46E100((uint32_t *)this);  // 调 界面控件批量隐藏
    *(uint8_t *)(pThis_194 + 13) = 0;
    *(uint8_t *)(pThis_194 + 14) = 0;
    sub_698F90(pThis_194, 0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
    *(uint8_t *)(this + 389) = 0;
    *(uint8_t *)(this + 390) = 0;
    sub_698F90(this + 376, 0, 0);  // clock_set_countdown(clk, duration=a2, startTime=a3)
    return (int)sub_46EE10((int)&hObject, (const char *)(this + 1468));  // 调 启动时置 1、
  }
  return result;
}



// ------------------------------------------------------------
// 0x46F440 sub_46F440 —— 值对象析构（vector + 单串）
// 值对象析构/复位：释放 +32 处 vector 缓冲（ptr/end/cap）与 +0 处 std::string（cap>=16 才 free
// 堆块），随后 size/cap/首字节全复位。cashshop 组 map 值的失败路径以栈值对象调用。
// ------------------------------------------------------------
void /*thiscall*/ sub_46F440(int this)  // 函数: 值对象析构（vector + 单串）
{
  if ( *(uint32_t *)(this + 32) != 0 )  // this+32〔nHeight(推断)〕等 2 字段
    j__free(*(void **)(this + 32));  // 调 堆释放
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  *(uint32_t *)(this + 36) = 0;  // this+144 = pFrameList144
  *(uint32_t *)(this + 40) = 0;  // this+40〔bStateSub40(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 24) >= 0x10u )  // this+24〔nPageMax(推断)〕等 2 字段
    j__free(*(void **)(this + 4));  // 调 堆释放
  *(uint32_t *)(this + 20) = 0;  // this+80 = nAuraStage
  *(uint32_t *)(this + 24) = 15;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
}



// ------------------------------------------------------------
// 0x46F490 sub_46F490 —— 值对象析构（三串）
// 值对象析构/复位（三个 28 字节 std::string：+0/+32/+60）：cap>=16 时 free 各自堆块，
// size/cap/首字节复位；+153 nil 旗标树擦除（login_channel 0x470ED0）以 node+16 调用。
// ------------------------------------------------------------
void /*thiscall*/ sub_46F490(int this)  // 函数: 值对象析构（三串）
{
  if ( *(uint32_t *)(this + 84) >= 0x10u )  // this+84〔pFxObjA(推断)〕
    j__free(*(void **)(this + 64));  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 84) = 15;  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  *(uint8_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  if ( *(uint32_t *)(this + 56) >= 0x10u )  // this+56〔pCmdVecCap56(推断)〕等 2 字段
    j__free(*(void **)(this + 36));  // this+144 = pFrameList144
  *(uint32_t *)(this + 56) = 15;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint8_t *)(this + 36) = 0;  // this+144 = pFrameList144
  if ( *(uint32_t *)(this + 24) >= 0x10u )  // this+24〔nPageMax(推断)〕等 2 字段
    j__free(*(void **)(this + 4));  // 调 堆释放
  *(uint32_t *)(this + 20) = 0;  // this+80 = nAuraStage
  *(uint32_t *)(this + 24) = 15;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
}



// ------------------------------------------------------------
// 0x46F500 sub_46F500 —— 频道列表 10 槽按页刷新
// 频道列表 10 槽按钮按页刷新（登录过场绘制 0x471DB0 调；+1464==1 即 HTTP 线程退出码 1、
// 数据就绪才跑）：类型 2/3 特殊按钮（+156/+160）各画对应条目首条，其余 10 槽按页逐个
// ·0x46F0E0 绘制或置隐藏。
// ------------------------------------------------------------
void /*thiscall*/ sub_46F500(int *this)  // 函数: 频道列表 10 槽按页刷新
{
  int fld_e3; // ecx
  int fld_e5; // eax
  int fld_e52; // ecx
  int fld_e53; // ebx
  int *pThis_1D; // edi
  int fld_e32; // edx
  unsigned int v8; // eax
  unsigned int fld_e33; // edx
  int fld_e522; // [esp+4h] [ebp-8h]
  int v11; // [esp+8h] [ebp-4h]

  if ( *(this + 366) == 1 )  // this+1464〔nSelState〕
  {
    fld_e3 = *(this + 3);  // this+12 = 技能槽记录次字
    if ( fld_e3 != 6 && *(this + 4) != 5 )  // this+16〔nChannelTypeSel(推断)〕
    {
      fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
      if ( fld_e5 >= 0 && fld_e5 < *(this + 6) )  // this+24〔nPageMax(推断)〕
      {
        if ( sub_46E3D0(this + 35 * fld_e3 + 177) != 0 )  // 调 频道条目 vector 计数
        {
          *(uint8_t *)(*(this + 39) + 16) = 1;  // this+156〔nAdd156(推断)〕
          sub_46F0E0(this, *(this + 39), *(this + 35 * *(this + 3) + 178), *(this + 35 * *(this + 3) + 168));  // 调 单条频道条目绘制（背景帧 + 频道名 + 负载条）
        }
        else
        {
          *(uint8_t *)(*(this + 39) + 16) = 0;  // this+156〔nAdd156(推断)〕
        }
        if ( sub_46E3D0(this + 35 * *(this + 3) + 181) != 0 )  // 调 频道条目 vector 计数
        {
          *(uint8_t *)(*(this + 40) + 16) = 1;  // this+160〔fAdd160(推断)〕
          sub_46F0E0(this, *(this + 40), *(this + 35 * *(this + 3) + 182), *(this + 35 * *(this + 3) + 168));  // 调 单条频道条目绘制（背景帧 + 频道名 + 负载条）
        }
        else
        {
          *(uint8_t *)(*(this + 40) + 16) = 0;  // this+160〔fAdd160(推断)〕
        }
        fld_e52 = 10 * *(this + 5);  // this+20〔nPage〕
        fld_e53 = 1040 * *(this + 5);  // this+20〔nPage〕
        fld_e522 = fld_e52;
        v11 = 0;
        pThis_1D = this + 29;  // this+29 pSessionCtx
        while ( 1 )  // 无限循环
        {
          fld_e32 = *(this + 35 * *(this + 3) + 4 * *(this + 4) + 170);  // this+12 = 技能槽记录次字
          if ( fld_e32 != 0 )  // fld_e32=this+12 物品类型号
          {
            fld_e52 = fld_e522;
            fld_e33 = (int)((uint64_t)(1321528399LL * (*(this + 35 * *(this + 3) + 4 * *(this + 4) + 171) - fld_e32)) >> 32) >> 5;  // this+12 = 技能槽记录次字
            v8 = fld_e33 + (fld_e33 >> 31);  // fld_e33=this+12 物品类型号
          }
          else
          {
            v8 = 0;
          }
          if ( v8 > fld_e52 + v11 )
          {
            *(uint8_t *)(*pThis_1D + 16) = 1;  // this+16 频道型选中索引
            sub_46F0E0(  // 调 单条频道条目绘制（背景帧 + 频道名 + 负载条）
              this,
              *pThis_1D,  // pThis_1D=this+29 pSessionCtx
              fld_e53 + *(this + 35 * *(this + 3) + 4 * *(this + 4) + 170),  // this+12 = 技能槽记录次字
              *(this + 35 * *(this + 3) + 168));  // this+12 = 技能槽记录次字
          }
          else
          {
            *(uint8_t *)(*pThis_1D + 16) = 0;  // this+16 频道型选中索引
          }
          fld_e53 += 104;
          ++pThis_1D;  // pThis_1D=this+29 pSessionCtx
          if ( ++v11 >= 10 )
            break;
          fld_e52 = fld_e522;
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x46F6B0 sub_46F6B0 —— 条目填充 N 条并返尾指针
// 频道条目填充 N 条并返越过末条的指针：转发 0x46EF10 后返回 &pszArg1[104*pszArg2]；
// login_channel 0x470330 贴近旧 end 的补尾路径用它。
// ------------------------------------------------------------
char */*stdcall*/ sub_46F6B0(char *pszArg1, char *pszArg2, const void *pArg3)  // 函数: 条目填充 N 条并返尾指针
{
  sub_46EF10(pszArg1, pszArg2, pArg3);  // 调 条目填充 N 条（步长 104B）
  return &pszArg1[104 * (uint32_t)pszArg2];
}



// ------------------------------------------------------------
// 0x46F6E0 sub_46F6E0 —— 值对象析构（vector + 两串）
// 值对象析构/复位（+56 处 vector 与 +0/+28 两个 std::string）：+85 nil 旗标树擦除
// （login_channel 0x470BB0）以 node+12 调用；cashshop 组值路径亦调。
// ------------------------------------------------------------
void /*thiscall*/ sub_46F6E0(int this)  // 函数: 值对象析构（vector + 两串）
{
  if ( *(uint32_t *)(this + 60) != 0 )  // this+240 = 基类时刻同步参数 B
    j__free(*(void **)(this + 60));  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 60) = 0;  // this+240 = 基类时刻同步参数 B
  *(uint32_t *)(this + 64) = 0;  // this+256 = 基类四元组字节槽 3
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  if ( *(uint32_t *)(this + 52) >= 0x10u )  // this+52〔bAuraState(推断)〕等 2 字段
    j__free(*(void **)(this + 32));  // 调 堆释放
  *(uint32_t *)(this + 52) = 15;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *(uint8_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 24) >= 0x10u )  // this+24〔nPageMax(推断)〕等 2 字段
    j__free(*(void **)(this + 4));  // 调 堆释放
  *(uint32_t *)(this + 20) = 0;  // this+80 = nAuraStage
  *(uint32_t *)(this + 24) = 15;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
}



// ------------------------------------------------------------
// 0x46F740 sub_46F740 —— 值析构转发（this+4）
// 值析构转发：对 this+4 处的值对象调 0x46F490（三串值清理）；供值内嵌于 +4 的持有者复用【推断】。
// ------------------------------------------------------------
void /*thiscall*/ sub_46F740(void *this)  // 函数: 值析构转发（this+4）
{
  sub_46F490((int)this + 4);  // 调 值对象析构（三串）
}



// ------------------------------------------------------------
// 0x46F750 sub_46F750 —— nengine::CNButton 构造
// nengine::CNButton 构造：IControl 基构造（0x426BD0）→ 换 CNButton vftable → 按钮字段初始化
// （0x69C780：类型 1，+104..+124 与 +128/+129 清零）；被 eh vector 构造批量建按钮时调用。
// ------------------------------------------------------------
void /*thiscall*/ sub_46F750(uint32_t *this)  // 函数: nengine::CNButton 构造
{
  sub_426BD0(this);  // 调 nengine::IControl 构造
  *this = &vftbl_nengine__CNButton;  // 构造装配 vftable：nengine__CNButton
  sub_69C780(this);  // 调 初始化 → ·vmt20(nArg2..nArg8
}



// ------------------------------------------------------------
// 0x46F7A0 sub_46F7A0 —— nengine::CNRadioButton 构造
// nengine::CNRadioButton 构造：IControl 基构造 → 换 CNRadioButton vftable → 单选组字段
// （0x69CE10：类型 7、+104=-1 无选中）→ vmt20(0)。cashshop/trade_shop/选区界面批量建。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_46F7A0(uint8_t *this, int nArg2)  // 函数: nengine::CNRadioButton 构造
{
  sub_426BD0(this);  // 调 nengine::IControl 构造
  *(uint32_t *)this = &vftbl_nengine__CNRadioButton;  // 构造装配 vftable：nengine__CNRadioButton
  sub_69CE10(this);
  nengine__CNRadioButton__vmt20(0);
  return this;
}



// ============================================================
// 【分区 13】nengine 单选/复选按钮（0x46F800-0x470000）
// nengine__CNRadioButton__vmt0 / nengine__CNCheckBox__vmt0（RTTI 自证）。
// ============================================================
// ------------------------------------------------------------
// 0x46F800 nengine__CNRadioButton__vmt0
// ------------------------------------------------------------
// nengine::CNRadioButton::vmt0（RTTI 自证）
void */*thiscall*/ nengine__CNRadioButton__vmt0(void *Block, char pszArg2)  // 实现：nengine::CNRadioButton::vmt0（RTTI 自证）
{
  sub_46F830();  // 调 nengine::CNRadioButton 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x46F830 sub_46F830 —— nengine::CNRadioButton 析构体
// nengine::CNRadioButton 析构体：换回 CNRadioButton vftable → vmt8 子清理 → IControl 析构本体
// （0x426C90）；由 0x46F800 vmt0（free 包装）调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_46F830(void **this)  // 函数: nengine::CNRadioButton 析构体
{
  *this = &vftbl_nengine__CNRadioButton;  // 构造装配 vftable：nengine__CNRadioButton
  nengine__CNRadioButton__vmt8();
  return sub_426C90(this);  // 调 nengine::IControl 析构本体
}



// ------------------------------------------------------------
// 0x46F880 sub_46F880 —— nengine::CNCheckBox 构造
// nengine::CNCheckBox 构造：IControl → CNButton vftable/字段（0x69C780）→ 换 CNCheckBox
// vftable 与图片组字段（0x69CF80：类型 6）→ vmt20 传入常态/悬停/按下/禁用贴图组。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_46F880(uint8_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7, int nArg8)  // 函数: nengine::CNCheckBox 构造
{
  sub_426BD0(this);  // 调 nengine::IControl 构造
  *(uint32_t *)this = &vftbl_nengine__CNButton;  // 构造装配 vftable：nengine__CNButton
  sub_69C780(this);  // 调 初始化 → ·vmt20(nArg2..nArg8
  *(uint32_t *)this = &vftbl_nengine__CNCheckBox;  // 构造装配 vftable：nengine__CNCheckBox
  sub_69CF80(this);
  nengine__CNCheckBox__vmt20(nArg2, nArg3, nArg4, nArg5, nArg6, nArg7, nArg8);
  return this;
}



// ------------------------------------------------------------
// 0x46F910 nengine__CNCheckBox__vmt0
// ------------------------------------------------------------
// nengine::CNCheckBox::vmt0（RTTI 自证）
void */*thiscall*/ nengine__CNCheckBox__vmt0(void *Block, char pszArg2)  // 实现：nengine::CNCheckBox::vmt0（RTTI 自证）
{
  sub_46F940(Block);  // 调 nengine::CNCheckBox 析构体
  if ( (pszArg2 & 1) != 0 )  // 析构标志位 bit0（=1 时释放对象）
    j__free(Block);  // 调 堆释放
  return Block;
}



// ------------------------------------------------------------
// 0x46F940 sub_46F940 —— nengine::CNCheckBox 析构体
// nengine::CNCheckBox 析构体：换回 CNCheckBox vftable → vmt8 子清理 → CNButton 析构
// （0x43C480）；由 0x46F910 vmt0（free 包装）调用。
// ------------------------------------------------------------
void /*thiscall*/ sub_46F940(void **this)  // 函数: nengine::CNCheckBox 析构体
{
  *this = &vftbl_nengine__CNCheckBox;  // 构造装配 vftable：nengine__CNCheckBox
  nengine__CNCheckBox__vmt8();
  sub_43C480(this);  // 调 nengine::CNButton 析构
}



// ------------------------------------------------------------
// 0x46F990 sub_46F990 —— ★ CNEntranceChannel 界面控件构建（构造 0x41DE30 尾调）
// ·0x569F40 装载 Etc/channel_info.etc，抄全局 UI 件 dword_99FCC8+20 字段到 +28..+44；+4 已建即跳过；
// 再建 2 单选组（+88/+112）、6 服务器页签+5 频道型页签+10 频道槽+2 特殊（0x46F880）
// 与 5 底部按钮（0x69C7B0），末置 +4=1。
// ------------------------------------------------------------
void /*thiscall*/ sub_46F990(int this)  // 函数: ★ CNEntranceChannel 界面控件构建（构造 0x41DE30 尾调）
{
  void *pMem; // eax
  int v3; // eax
  void *pMem2; // eax
  int v5; // eax
  void *pMem3; // eax
  int v7; // eax
  int v8; // eax
  int *v9; // eax
  int v10; // edi
  uint32_t *fld_28; // eax
  uint32_t *pMem4; // eax
  uint32_t *pMem42; // edi
  int *v14; // eax
  uint32_t *pThis_5C; // edi
  uint32_t *fld_282; // eax
  uint32_t *pMem5; // eax
  uint32_t *pMem52; // edi
  uint32_t *pMem6; // eax
  uint32_t *pMem62; // edi
  uint32_t *pMem622; // ecx
  bool v22; // cc
  uint32_t *pMem7; // eax
  uint32_t *pMem72; // edi
  uint32_t *pMem8; // eax
  uint32_t *pMem82; // edi
  uint32_t *pThis_9C; // edi
  uint32_t *pMem9; // eax
  uint32_t *pMem92; // edi
  uint32_t *pMem922; // ecx
  uint32_t *pMem10; // eax
  uint32_t *pMem102; // edi
  uint32_t *pMem1022; // ecx
  uint32_t *pMem11; // eax
  uint32_t *pMem112; // edi
  uint32_t *pMem1122; // ecx
  uint32_t *pMem12; // eax
  uint32_t *pMem122; // edi
  uint32_t *pMem1222; // ecx
  uint32_t *pMem13; // eax
  uint32_t *pMem132; // edi
  uint32_t *pMem1322; // ecx
  void *Block; // [esp+8h] [ebp-20h]
  void *Blocka; // [esp+8h] [ebp-20h]
  void *Blockb; // [esp+8h] [ebp-20h]
  void *Blockc; // [esp+8h] [ebp-20h]
  void *Blockd; // [esp+8h] [ebp-20h]
  void *Blocke; // [esp+8h] [ebp-20h]
  void *Blockf; // [esp+8h] [ebp-20h]
  void *fld_283; // [esp+Ch] [ebp-1Ch]
  int *v51; // [esp+10h] [ebp-18h]
  uint32_t *pThis_74; // [esp+10h] [ebp-18h]
  int *v53; // [esp+14h] [ebp-14h]
  uint32_t *v54; // [esp+14h] [ebp-14h]
  unsigned int v55; // [esp+14h] [ebp-14h]
  int v56; // [esp+14h] [ebp-14h]
  int v57; // [esp+18h] [ebp-10h]
  int v58; // [esp+18h] [ebp-10h]

  if ( *(uint8_t *)(this + 4) != 1 )  // this+4〔宿主对象〕等 2 字段
  {
    sub_569F40(&unk_98BA40);  // 调 importChannelScript 主装载（311 行）：读取 Etc/channel_info.etc（442A10/…
    *(uint32_t *)(this + 28) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 4);  // this+112 = pHostComp
    *(uint32_t *)(this + 32) = **(uint32_t **)(dword_99FCC8 + 20);  // this+32〔nHeight(推断)〕等 2 字段
    *(uint32_t *)(this + 36) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+144 = pFrameList144
    *(uint32_t *)(this + 40) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 176);  // this+40〔bStateSub40(推断)〕等 2 字段
    *(uint32_t *)(this + 44) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 180);  // this+44〔nExpireMs(推断)〕等 2 字段
    pMem = operator new(0x68u);  // operator new 分配 104 字节
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      v3 = sub_426BD0(pMem);  // 调 nengine::IControl 构造
    else
      v3 = 0;
    *(uint32_t *)(this + 48) = v3;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    pMem2 = operator new(0x68u);  // operator new 分配 104 字节
    if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
      v5 = sub_426BD0(pMem2);  // 调 nengine::IControl 构造
    else
      v5 = 0;
    *(uint32_t *)(this + 52) = v5;  // this+52〔bAuraState(推断)〕等 2 字段
    *(uint32_t *)(v5 + 28) = 640;
    *(uint32_t *)(v5 + 32) = 480;
    *(uint32_t *)(*(uint32_t *)(this + 52) + 68) = this + 8;  // this+52〔bAuraState(推断)〕等 2 字段
    pMem3 = operator new(0x68u);  // operator new 分配 104 字节
    if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
      v7 = sub_426BD0(pMem3);  // 调 nengine::IControl 构造
    else
      v7 = 0;
    *(uint32_t *)(this + 56) = v7;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
    *(uint32_t *)(v7 + 68) = this + 8;  // this+8 物品 id
    sub_69A840(*(uint32_t *)(this + 52));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    sub_69A840(*(uint32_t *)(this + 56));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    sub_69A840(*((uint32_t *)dword_8F8528 + 2));  // dword_8F8528 = 主管理器
    sub_69A840(*((uint32_t *)dword_8F8528 + 3));  // dword_8F8528 = 主管理器
    sub_69A840(*(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 4));  // dword_8F8528 = 主管理器
    if ( operator new(0x70u) != nullptr )  // operator new 分配 112 字节
      v8 = sub_46F7A0(0);  // 调 nengine::CNRadioButton 构造
    else
      v8 = 0;
    *(uint32_t *)(this + 60) = v8;  // this+240 = 基类时刻同步参数 B
    sub_69A840(v8);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    v9 = (int *)&unk_6C7BA0;
    v57 = 73;
    v53 = (int *)&unk_6C7BA0;
    do
    {
      v10 = *v9;
      if ( dword_6C7B88[*v9] == 0 )
      {
        if ( operator new(0x88u) != nullptr )  // operator new 分配 136 字节
          fld_28 = (uint32_t *)sub_46F880(  // 调 nengine::CNCheckBox 构造
                            *(uint32_t *)(this + 40),  // this+40 物品状态附属标志
                            dword_6C7BC0[6 * v10],
                            dword_6C7BC0[6 * v10],
                            dword_6C7BB8[6 * v10],
                            dword_6C7BC8[6 * v10],
                            0,
                            0);
        else
          fld_28 = nullptr;
        *(uint32_t *)(this + 4 * v10 + 64) = fld_28;  // this+4 宿主对象
        sub_69A5F0(fld_28, 12, v57);  // 调 设位、sub_69A840 登记
        *(uint8_t *)(*(uint32_t *)(this + 4 * v10 + 64) + 132) = 0;  // this+4 宿主对象
        *(uint8_t *)(*(uint32_t *)(this + 4 * v10 + 64) + 16) = 0;  // this+4 宿主对象
        *(uint32_t *)(*(uint32_t *)(this + 4 * v10 + 64) + 68) = this + 8;  // this+4 宿主对象
        sub_69A840(*(uint32_t *)(this + 4 * v10 + 64));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
        v57 += 42;
        v9 = v53;
      }
      v53 = ++v9;
    }
    while ( (int)v9 < (int)dword_6C7BB8 );
    pMem4 = operator new(0x70u);  // operator new 分配 112 字节
    pMem42 = pMem4;
    if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    {
      sub_426BD0(pMem4);  // 调 nengine::IControl 构造
      *pMem42 = &nengine::CNRadioButton::`vftable';  // vftable 复位
      sub_69CE10(v13);
      sub_69CF50(0);
    }
    else
    {
      v13 = nullptr;
    }
    *(uint32_t *)(this + 88) = v13;  // this+88〔pFxObjB(推断)〕等 2 字段
    sub_69A840(v13);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    v14 = (int *)&unk_6C7B74;
    v58 = 170;
    v54 = &unk_6C7B38;
    v51 = (int *)&unk_6C7B74;
    v15 = (uint32_t *)(this + 92);  // this+92〔pFxObjC(推断)〕等 2 字段
    do
    {
      if ( *v14 == 0 )
      {
        if ( operator new(0x88u) != nullptr )  // operator new 分配 136 字节
          v16 = (uint32_t *)sub_46F880(*(uint32_t *)(this + 40), *v54, *v54, v54[1], v54[2], 0, 0);  // 调 nengine::CNCheckBox 构造
        else
          v16 = nullptr;
        *v15 = v16;  // v15=this+92 pFxObjC
        sub_69A5F0(v16, v58, 46);  // 调 设位、sub_69A840 登记
        *(uint8_t *)(*v15 + 132) = 0;  // v15=this+92 pFxObjC
        *(uint8_t *)(*v15 + 16) = 0;  // v15=this+92 pFxObjC
        *(uint32_t *)(*v15 + 68) = this + 8;  // this+8 物品 id
        sub_69A840(*v15);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
        v58 += 80;
        v14 = v51;
      }
      ++v14;
      ++v15;  // v15=this+92 pFxObjC
      v51 = v14;
      v54 += 3;
    }
    while ( (int)v14 < (int)dword_6C7B88 );
    v17 = operator new(0x70u);  // operator new 分配 112 字节
    v18 = v17;
    if ( v17 != nullptr )  // 若 v17 有效（非空）
    {
      sub_426BD0(v17);  // 调 nengine::IControl 构造
      *v18 = &nengine::CNRadioButton::`vftable';  // vftable 复位
      sub_69CE10(pMem52);
      sub_69CF50(0);
    }
    else
    {
      pMem52 = nullptr;
    }
    *(uint32_t *)(this + 112) = pMem52;  // this+112〔pHostComp112〕
    sub_69A840(pMem52);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    v55 = 0;
    pThis_74 = (uint32_t *)(this + 116);  // this+116〔会话上下文〕
    do
    {
      pMem6 = operator new(0x88u);  // operator new 分配 136 字节
      pMem62 = pMem6;
      if ( pMem6 != nullptr )  // 若 pMem6 有效（非空）
      {
        fld_283 = *(void **)(this + 40);  // this+160〔fAdd160(推断)〕
        sub_426BD0(pMem6);  // 调 nengine::IControl 构造
        *pMem62 = &nengine::CNButton::`vftable';  // vftable 复位
        sub_69C780(v20);  // 调 初始化 → ·vmt20(nArg2..nArg8
        *v20 = &nengine::CNCheckBox::`vftable';  // vftable 复位
        sub_69CF80(pMem62);
        sub_69CFB0(fld_283, 56, 56, 57, 56, 0, 0);  // 调 转发 sub_69C7B0（7 参同签名）
        pMem622 = pMem62;
      }
      else
      {
        pMem622 = nullptr;
      }
      *pThis_74 = pMem622;  // pThis_74=this+116 会话上下文
      sub_69A5F0(pMem622, 198 * (v55 % 2) + 182, 47 * (v55 / 2) + 138);  // 调 设位、sub_69A840 登记
      *(uint8_t *)(*pThis_74 + 132) = 0;  // this+132 第 3 组·+60 增量项
      *(uint8_t *)(*pThis_74 + 16) = 0;  // this+16 频道型选中索引
      sub_69A840(*pThis_74);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
      v22 = (int)++v55 < 10;
      ++pThis_74;  // pThis_74=this+116 会话上下文
    }
    while ( v22 );
    pMem7 = operator new(0x88u);  // operator new 分配 136 字节
    pMem72 = pMem7;
    if ( pMem7 != nullptr )  // 若 pMem7 有效（非空）
    {
      Block = *(void **)(this + 40);  // this+160〔fAdd160(推断)〕
      sub_426BD0(pMem7);  // 调 nengine::IControl 构造
      *pMem72 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(v24);  // 调 初始化 → ·vmt20(nArg2..nArg8
      *v24 = &nengine::CNCheckBox::`vftable';  // vftable 复位
      sub_69CF80(pMem72);
      sub_69CFB0(Block, 52, 52, 53, 52, 0, 0);  // 调 转发 sub_69C7B0（7 参同签名）
    }
    else
    {
      pMem72 = nullptr;
    }
    *(uint32_t *)(this + 156) = pMem72;  // this+156〔nAdd156(推断)〕
    pMem8 = operator new(0x88u);  // operator new 分配 136 字节
    pMem82 = pMem8;
    if ( pMem8 != nullptr )  // 若 pMem8 有效（非空）
    {
      Blocka = *(void **)(this + 40);  // this+160〔fAdd160(推断)〕
      sub_426BD0(pMem8);  // 调 nengine::IControl 构造
      *pMem82 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(v26);  // 调 初始化 → ·vmt20(nArg2..nArg8
      *v26 = &nengine::CNCheckBox::`vftable';  // vftable 复位
      sub_69CF80(pMem82);
      sub_69CFB0(Blocka, 54, 54, 55, 54, 0, 0);  // 调 转发 sub_69C7B0（7 参同签名）
    }
    else
    {
      pMem82 = nullptr;
    }
    *(uint32_t *)(this + 160) = pMem82;  // this+160〔fAdd160(推断)〕
    v56 = 182;
    pThis_9C = (uint32_t *)(this + 156);  // this+156〔nAdd156(推断)〕
    do
    {
      sub_69A5F0((uint32_t *)*pThis_9C, v56, 91);  // 调 设位、sub_69A840 登记
      *(uint8_t *)(*pThis_9C + 132) = 0;  // this+132 第 3 组·+60 增量项
      *(uint8_t *)(*pThis_9C + 16) = 0;  // this+16 频道型选中索引
      sub_69A840(*pThis_9C++);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
      v56 += 198;
    }
    while ( v56 < 578 );
    pMem9 = operator new(0x84u);  // operator new 分配 132 字节
    pMem92 = pMem9;
    if ( pMem9 != nullptr )  // 若 pMem9 有效（非空）
    {
      Blockb = *(void **)(this + 36);  // this+144 = pFrameList144
      sub_426BD0(pMem9);  // 调 nengine::IControl 构造
      *pMem92 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(v29);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(Blockb, 76, 77, 78, 76, 0, 0);  // Blockb=this+144 第 4 组·+1040 增量子倍率
      v30 = v29;
    }
    else
    {
      v30 = nullptr;
    }
    *(uint32_t *)(this + 172) = v30;  // this+688 = 表现/名字快照[2]
    sub_69A5F0(v30, 342, 382);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 172));  // this+688 = 表现/名字快照[2]
    v31 = operator new(0x84u);  // operator new 分配 132 字节
    v32 = v31;
    if ( v31 != nullptr )  // 若 v31 有效（非空）
    {
      Blockc = *(void **)(this + 36);  // this+144 = pFrameList144
      sub_426BD0(v31);  // 调 nengine::IControl 构造
      *v32 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(pMem102);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(Blockc, 79, 80, 81, 79, 0, 0);  // Blockc=this+144 第 4 组·+1040 增量子倍率
      pMem1022 = pMem102;
    }
    else
    {
      pMem1022 = nullptr;
    }
    *(uint32_t *)(this + 176) = pMem1022;  // this+704 = 表现/名字快照[24]
    sub_69A5F0(pMem1022, 402, 382);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 176));  // this+704 = 表现/名字快照[24]
    pMem11 = operator new(0x84u);  // operator new 分配 132 字节
    pMem112 = pMem11;
    if ( pMem11 != nullptr )  // 若 pMem11 有效（非空）
    {
      Blockd = *(void **)(this + 40);  // this+160〔fAdd160(推断)〕
      sub_426BD0(pMem11);  // 调 nengine::IControl 构造
      *pMem112 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(v35);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(Blockd, 42, 43, 44, 42, 0, 0);  // Blockd=this+160 fAdd160
      v36 = v35;
    }
    else
    {
      v36 = nullptr;
    }
    *(uint32_t *)(this + 164) = v36;  // this+164〔fAdd164(推断)〕
    sub_69A5F0(v36, 547, 376);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 164));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    v37 = operator new(0x84u);  // operator new 分配 132 字节
    v38 = v37;
    if ( v37 != nullptr )  // 若 v37 有效（非空）
    {
      Blocke = *(void **)(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
      sub_426BD0(v37);  // 调 nengine::IControl 构造
      *v38 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(pMem122);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(Blocke, 9, 10, 11, 9, 0, 0);  // Blocke=this+128 szStatusKeyBuf
      pMem1222 = pMem122;
    }
    else
    {
      pMem1222 = nullptr;
    }
    *(uint32_t *)(this + 168) = pMem1222;  // this+672 = 拾取/交互目标有效标志
    sub_69A5F0(pMem1222, 277, 426);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 168));  // this+672 = 拾取/交互目标有效标志
    pMem13 = operator new(0x84u);  // operator new 分配 132 字节
    pMem132 = pMem13;
    if ( pMem13 != nullptr )  // 若 pMem13 有效（非空）
    {
      Blockf = *(void **)(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
      sub_426BD0(pMem13);  // 调 nengine::IControl 构造
      *pMem132 = &nengine::CNButton::`vftable';  // vftable 复位
      sub_69C780(pMem132);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(Blockf, 17, 18, 19, 17, 0, 0);  // Blockf=this+128 szStatusKeyBuf
      pMem1322 = pMem132;
    }
    else
    {
      pMem1322 = nullptr;
    }
    *(uint32_t *)(this + 180) = pMem1322;  // this+180〔nRadius(推断)〕
    sub_69A5F0(pMem1322, 520, 427);  // 调 设位、sub_69A840 登记
    sub_69A840(*(uint32_t *)(this + 180));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    *(uint8_t *)(this + 184) = 0;  // this+184〔bSingleTarget(推断)〕
    *(uint8_t *)(this + 185) = 0;
    *(uint8_t *)(this + 186) = 0;
    *(uint8_t *)(this + 187) = 0;
    *(uint32_t *)(this + 196) = 0;
    *(uint32_t *)(this + 208) = 0;  // this+208〔nField208(推断)〕
    *(uint32_t *)(this + 216) = 0;  // this+216〔bField216(推断)〕
    *(uint32_t *)(this + 220) = 0;  // this+220〔nSnapDst220(推断)〕
    *(uint32_t *)(this + 224) = 0;  // this+224〔nSnapDst224(推断)〕
    *(uint32_t *)(this + 228) = 0;  // this+228〔nSnapDst228(推断)〕
    *(uint32_t *)(this + 232) = 0;  // this+232〔bSyncFlag〕
    *(uint32_t *)(this + 200) = 6;  // this+200〔nMainState(推断)〕
    *(uint32_t *)(this + 212) = 1600;  // this+212〔nField212(推断)〕
    *(uint32_t *)(this + 204) = 12;  // this+204〔pSubAnim204(推断)〕
    *(uint32_t *)(this + 232) = dword_99FCCC;  // this+232〔bSyncFlag〕
    *(uint32_t *)(this + 196) = 0;
    *(uint32_t *)(this + 188) = -16777216;  // this+188〔nStatusIdx(推断)〕
    *(uint32_t *)(this + 212) = 120;  // this+212〔nField212(推断)〕
    *(uint8_t *)(this + 236) = 0;  // this+944 = 名字已播出标志
    *(uint8_t *)(this + 237) = 0;
    *(uint8_t *)(this + 238) = 0;
    *(uint8_t *)(this + 239) = 0;
    *(uint32_t *)(this + 248) = 0;  // this+992 = uCfgB992
    *(uint32_t *)(this + 252) = 6;  // this+252〔nQuad2〕
    *(uint32_t *)(this + 256) = 12;  // this+256〔bQuad3〕
    *(uint32_t *)(this + 260) = 0;  // this+260〔nQuad4〕
    *(uint32_t *)(this + 264) = 1600;  // this+264〔nAnimHandle(推断)〕
    *(uint32_t *)(this + 268) = 0;  // this+268〔field_10C〕
    *(uint32_t *)(this + 272) = 0;
    *(uint32_t *)(this + 276) = 0;  // this+276〔pMapEntry〕
    *(uint32_t *)(this + 280) = 0;  // this+280〔pMapEntryVecEnd〕
    *(uint32_t *)(this + 284) = 0;  // this+284〔bBindGate284(推断)〕
    *(uint32_t *)(this + 284) = dword_99FCCC;  // this+284〔bBindGate284(推断)〕
    *(uint32_t *)(this + 264) = 120;  // this+264〔nAnimHandle(推断)〕
    *(uint32_t *)(this + 248) = 0;  // this+992 = uCfgB992
    *(uint32_t *)(this + 1744) = 500;  // this+1744〔nDblClickThresh〕
    InitializeCriticalSection(&stru_98BA28);  // 调 初始化临界区
    *(uint8_t *)(this + 4) = 1;  // this+4〔宿主对象〕等 2 字段
  }
}

